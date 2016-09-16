<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_input.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_input.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_input.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_input.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_input.c">ip_input.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_input.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_input.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ip_input.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ip_input.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ip_input.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_input.c#L6">6</a> <b><i> *              The Internet Protocol (IP) module.</i></b>
  <a name="L7" href="source/net/ipv4/ip_input.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_input.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/ip_input.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/ip_input.c#L10">10</a> <b><i> *              Donald Becker, &lt;becker@super.org&gt;</i></b>
 <a name="L11" href="source/net/ipv4/ip_input.c#L11">11</a> <b><i> *              Alan Cox, &lt;alan@lxorguk.ukuu.org.uk&gt;</i></b>
 <a name="L12" href="source/net/ipv4/ip_input.c#L12">12</a> <b><i> *              Richard Underwood</i></b>
 <a name="L13" href="source/net/ipv4/ip_input.c#L13">13</a> <b><i> *              Stefan Becker, &lt;stefanb@yello.ping.de&gt;</i></b>
 <a name="L14" href="source/net/ipv4/ip_input.c#L14">14</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L15" href="source/net/ipv4/ip_input.c#L15">15</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L16" href="source/net/ipv4/ip_input.c#L16">16</a> <b><i> *</i></b>
 <a name="L17" href="source/net/ipv4/ip_input.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/ip_input.c#L18">18</a> <b><i> * Fixes:</i></b>
 <a name="L19" href="source/net/ipv4/ip_input.c#L19">19</a> <b><i> *              Alan Cox        :       Commented a couple of minor bits of surplus code</i></b>
 <a name="L20" href="source/net/ipv4/ip_input.c#L20">20</a> <b><i> *              Alan Cox        :       Undefining IP_FORWARD doesn't include the code</i></b>
 <a name="L21" href="source/net/ipv4/ip_input.c#L21">21</a> <b><i> *                                      (just stops a compiler warning).</i></b>
 <a name="L22" href="source/net/ipv4/ip_input.c#L22">22</a> <b><i> *              Alan Cox        :       Frames with &gt;=MAX_ROUTE record routes, strict routes or loose routes</i></b>
 <a name="L23" href="source/net/ipv4/ip_input.c#L23">23</a> <b><i> *                                      are junked rather than corrupting things.</i></b>
 <a name="L24" href="source/net/ipv4/ip_input.c#L24">24</a> <b><i> *              Alan Cox        :       Frames to bad broadcast subnets are dumped</i></b>
 <a name="L25" href="source/net/ipv4/ip_input.c#L25">25</a> <b><i> *                                      We used to process them non broadcast and</i></b>
 <a name="L26" href="source/net/ipv4/ip_input.c#L26">26</a> <b><i> *                                      boy could that cause havoc.</i></b>
 <a name="L27" href="source/net/ipv4/ip_input.c#L27">27</a> <b><i> *              Alan Cox        :       ip_forward sets the free flag on the</i></b>
 <a name="L28" href="source/net/ipv4/ip_input.c#L28">28</a> <b><i> *                                      new frame it queues. Still crap because</i></b>
 <a name="L29" href="source/net/ipv4/ip_input.c#L29">29</a> <b><i> *                                      it copies the frame but at least it</i></b>
 <a name="L30" href="source/net/ipv4/ip_input.c#L30">30</a> <b><i> *                                      doesn't eat memory too.</i></b>
 <a name="L31" href="source/net/ipv4/ip_input.c#L31">31</a> <b><i> *              Alan Cox        :       Generic queue code and memory fixes.</i></b>
 <a name="L32" href="source/net/ipv4/ip_input.c#L32">32</a> <b><i> *              Fred Van Kempen :       IP fragment support (borrowed from NET2E)</i></b>
 <a name="L33" href="source/net/ipv4/ip_input.c#L33">33</a> <b><i> *              Gerhard Koerting:       Forward fragmented frames correctly.</i></b>
 <a name="L34" href="source/net/ipv4/ip_input.c#L34">34</a> <b><i> *              Gerhard Koerting:       Fixes to my fix of the above 8-).</i></b>
 <a name="L35" href="source/net/ipv4/ip_input.c#L35">35</a> <b><i> *              Gerhard Koerting:       IP interface addressing fix.</i></b>
 <a name="L36" href="source/net/ipv4/ip_input.c#L36">36</a> <b><i> *              Linus Torvalds  :       More robustness checks</i></b>
 <a name="L37" href="source/net/ipv4/ip_input.c#L37">37</a> <b><i> *              Alan Cox        :       Even more checks: Still not as robust as it ought to be</i></b>
 <a name="L38" href="source/net/ipv4/ip_input.c#L38">38</a> <b><i> *              Alan Cox        :       Save IP header pointer for later</i></b>
 <a name="L39" href="source/net/ipv4/ip_input.c#L39">39</a> <b><i> *              Alan Cox        :       ip option setting</i></b>
 <a name="L40" href="source/net/ipv4/ip_input.c#L40">40</a> <b><i> *              Alan Cox        :       Use ip_tos/ip_ttl settings</i></b>
 <a name="L41" href="source/net/ipv4/ip_input.c#L41">41</a> <b><i> *              Alan Cox        :       Fragmentation bogosity removed</i></b>
 <a name="L42" href="source/net/ipv4/ip_input.c#L42">42</a> <b><i> *                                      (Thanks to Mark.Bush@prg.ox.ac.uk)</i></b>
 <a name="L43" href="source/net/ipv4/ip_input.c#L43">43</a> <b><i> *              Dmitry Gorodchanin :    Send of a raw packet crash fix.</i></b>
 <a name="L44" href="source/net/ipv4/ip_input.c#L44">44</a> <b><i> *              Alan Cox        :       Silly ip bug when an overlength</i></b>
 <a name="L45" href="source/net/ipv4/ip_input.c#L45">45</a> <b><i> *                                      fragment turns up. Now frees the</i></b>
 <a name="L46" href="source/net/ipv4/ip_input.c#L46">46</a> <b><i> *                                      queue.</i></b>
 <a name="L47" href="source/net/ipv4/ip_input.c#L47">47</a> <b><i> *              Linus Torvalds/ :       Memory leakage on fragmentation</i></b>
 <a name="L48" href="source/net/ipv4/ip_input.c#L48">48</a> <b><i> *              Alan Cox        :       handling.</i></b>
 <a name="L49" href="source/net/ipv4/ip_input.c#L49">49</a> <b><i> *              Gerhard Koerting:       Forwarding uses IP priority hints</i></b>
 <a name="L50" href="source/net/ipv4/ip_input.c#L50">50</a> <b><i> *              Teemu Rantanen  :       Fragment problems.</i></b>
 <a name="L51" href="source/net/ipv4/ip_input.c#L51">51</a> <b><i> *              Alan Cox        :       General cleanup, comments and reformat</i></b>
 <a name="L52" href="source/net/ipv4/ip_input.c#L52">52</a> <b><i> *              Alan Cox        :       SNMP statistics</i></b>
 <a name="L53" href="source/net/ipv4/ip_input.c#L53">53</a> <b><i> *              Alan Cox        :       BSD address rule semantics. Also see</i></b>
 <a name="L54" href="source/net/ipv4/ip_input.c#L54">54</a> <b><i> *                                      UDP as there is a nasty checksum issue</i></b>
 <a name="L55" href="source/net/ipv4/ip_input.c#L55">55</a> <b><i> *                                      if you do things the wrong way.</i></b>
 <a name="L56" href="source/net/ipv4/ip_input.c#L56">56</a> <b><i> *              Alan Cox        :       Always defrag, moved IP_FORWARD to the config.in file</i></b>
 <a name="L57" href="source/net/ipv4/ip_input.c#L57">57</a> <b><i> *              Alan Cox        :       IP options adjust sk-&gt;priority.</i></b>
 <a name="L58" href="source/net/ipv4/ip_input.c#L58">58</a> <b><i> *              Pedro Roque     :       Fix mtu/length error in ip_forward.</i></b>
 <a name="L59" href="source/net/ipv4/ip_input.c#L59">59</a> <b><i> *              Alan Cox        :       Avoid ip_chk_addr when possible.</i></b>
 <a name="L60" href="source/net/ipv4/ip_input.c#L60">60</a> <b><i> *      Richard Underwood       :       IP multicasting.</i></b>
 <a name="L61" href="source/net/ipv4/ip_input.c#L61">61</a> <b><i> *              Alan Cox        :       Cleaned up multicast handlers.</i></b>
 <a name="L62" href="source/net/ipv4/ip_input.c#L62">62</a> <b><i> *              Alan Cox        :       RAW sockets demultiplex in the BSD style.</i></b>
 <a name="L63" href="source/net/ipv4/ip_input.c#L63">63</a> <b><i> *              Gunther Mayer   :       Fix the SNMP reporting typo</i></b>
 <a name="L64" href="source/net/ipv4/ip_input.c#L64">64</a> <b><i> *              Alan Cox        :       Always in group 224.0.0.1</i></b>
 <a name="L65" href="source/net/ipv4/ip_input.c#L65">65</a> <b><i> *      Pauline Middelink       :       Fast ip_checksum update when forwarding</i></b>
 <a name="L66" href="source/net/ipv4/ip_input.c#L66">66</a> <b><i> *                                      Masquerading support.</i></b>
 <a name="L67" href="source/net/ipv4/ip_input.c#L67">67</a> <b><i> *              Alan Cox        :       Multicast loopback error for 224.0.0.1</i></b>
 <a name="L68" href="source/net/ipv4/ip_input.c#L68">68</a> <b><i> *              Alan Cox        :       IP_MULTICAST_LOOP option.</i></b>
 <a name="L69" href="source/net/ipv4/ip_input.c#L69">69</a> <b><i> *              Alan Cox        :       Use notifiers.</i></b>
 <a name="L70" href="source/net/ipv4/ip_input.c#L70">70</a> <b><i> *              Bjorn Ekwall    :       Removed ip_csum (from slhc.c too)</i></b>
 <a name="L71" href="source/net/ipv4/ip_input.c#L71">71</a> <b><i> *              Bjorn Ekwall    :       Moved ip_fast_csum to ip.h (inline!)</i></b>
 <a name="L72" href="source/net/ipv4/ip_input.c#L72">72</a> <b><i> *              Stefan Becker   :       Send out ICMP HOST REDIRECT</i></b>
 <a name="L73" href="source/net/ipv4/ip_input.c#L73">73</a> <b><i> *      Arnt Gulbrandsen        :       ip_build_xmit</i></b>
 <a name="L74" href="source/net/ipv4/ip_input.c#L74">74</a> <b><i> *              Alan Cox        :       Per socket routing cache</i></b>
 <a name="L75" href="source/net/ipv4/ip_input.c#L75">75</a> <b><i> *              Alan Cox        :       Fixed routing cache, added header cache.</i></b>
 <a name="L76" href="source/net/ipv4/ip_input.c#L76">76</a> <b><i> *              Alan Cox        :       Loopback didn't work right in original ip_build_xmit - fixed it.</i></b>
 <a name="L77" href="source/net/ipv4/ip_input.c#L77">77</a> <b><i> *              Alan Cox        :       Only send ICMP_REDIRECT if src/dest are the same net.</i></b>
 <a name="L78" href="source/net/ipv4/ip_input.c#L78">78</a> <b><i> *              Alan Cox        :       Incoming IP option handling.</i></b>
 <a name="L79" href="source/net/ipv4/ip_input.c#L79">79</a> <b><i> *              Alan Cox        :       Set saddr on raw output frames as per BSD.</i></b>
 <a name="L80" href="source/net/ipv4/ip_input.c#L80">80</a> <b><i> *              Alan Cox        :       Stopped broadcast source route explosions.</i></b>
 <a name="L81" href="source/net/ipv4/ip_input.c#L81">81</a> <b><i> *              Alan Cox        :       Can disable source routing</i></b>
 <a name="L82" href="source/net/ipv4/ip_input.c#L82">82</a> <b><i> *              Takeshi Sone    :       Masquerading didn't work.</i></b>
 <a name="L83" href="source/net/ipv4/ip_input.c#L83">83</a> <b><i> *      Dave Bonn,Alan Cox      :       Faster IP forwarding whenever possible.</i></b>
 <a name="L84" href="source/net/ipv4/ip_input.c#L84">84</a> <b><i> *              Alan Cox        :       Memory leaks, tramples, misc debugging.</i></b>
 <a name="L85" href="source/net/ipv4/ip_input.c#L85">85</a> <b><i> *              Alan Cox        :       Fixed multicast (by popular demand 8))</i></b>
 <a name="L86" href="source/net/ipv4/ip_input.c#L86">86</a> <b><i> *              Alan Cox        :       Fixed forwarding (by even more popular demand 8))</i></b>
 <a name="L87" href="source/net/ipv4/ip_input.c#L87">87</a> <b><i> *              Alan Cox        :       Fixed SNMP statistics [I think]</i></b>
 <a name="L88" href="source/net/ipv4/ip_input.c#L88">88</a> <b><i> *      Gerhard Koerting        :       IP fragmentation forwarding fix</i></b>
 <a name="L89" href="source/net/ipv4/ip_input.c#L89">89</a> <b><i> *              Alan Cox        :       Device lock against page fault.</i></b>
 <a name="L90" href="source/net/ipv4/ip_input.c#L90">90</a> <b><i> *              Alan Cox        :       IP_HDRINCL facility.</i></b>
 <a name="L91" href="source/net/ipv4/ip_input.c#L91">91</a> <b><i> *      Werner Almesberger      :       Zero fragment bug</i></b>
 <a name="L92" href="source/net/ipv4/ip_input.c#L92">92</a> <b><i> *              Alan Cox        :       RAW IP frame length bug</i></b>
 <a name="L93" href="source/net/ipv4/ip_input.c#L93">93</a> <b><i> *              Alan Cox        :       Outgoing firewall on build_xmit</i></b>
 <a name="L94" href="source/net/ipv4/ip_input.c#L94">94</a> <b><i> *              A.N.Kuznetsov   :       IP_OPTIONS support throughout the kernel</i></b>
 <a name="L95" href="source/net/ipv4/ip_input.c#L95">95</a> <b><i> *              Alan Cox        :       Multicast routing hooks</i></b>
 <a name="L96" href="source/net/ipv4/ip_input.c#L96">96</a> <b><i> *              Jos Vos         :       Do accounting *before* call_in_firewall</i></b>
 <a name="L97" href="source/net/ipv4/ip_input.c#L97">97</a> <b><i> *      Willy Konynenberg       :       Transparent proxying support</i></b>
 <a name="L98" href="source/net/ipv4/ip_input.c#L98">98</a> <b><i> *</i></b>
 <a name="L99" href="source/net/ipv4/ip_input.c#L99">99</a> <b><i> *</i></b>
<a name="L100" href="source/net/ipv4/ip_input.c#L100">100</a> <b><i> *</i></b>
<a name="L101" href="source/net/ipv4/ip_input.c#L101">101</a> <b><i> * To Fix:</i></b>
<a name="L102" href="source/net/ipv4/ip_input.c#L102">102</a> <b><i> *              IP fragmentation wants rewriting cleanly. The RFC815 algorithm is much more efficient</i></b>
<a name="L103" href="source/net/ipv4/ip_input.c#L103">103</a> <b><i> *              and could be made very efficient with the addition of some virtual memory hacks to permit</i></b>
<a name="L104" href="source/net/ipv4/ip_input.c#L104">104</a> <b><i> *              the allocation of a buffer that can then be 'grown' by twiddling page tables.</i></b>
<a name="L105" href="source/net/ipv4/ip_input.c#L105">105</a> <b><i> *              Output fragmentation wants updating along with the buffer management to use a single</i></b>
<a name="L106" href="source/net/ipv4/ip_input.c#L106">106</a> <b><i> *              interleaved copy algorithm so that fragmenting has a one copy overhead. Actual packet</i></b>
<a name="L107" href="source/net/ipv4/ip_input.c#L107">107</a> <b><i> *              output should probably do its own fragmentation at the UDP/RAW layer. TCP shouldn't cause</i></b>
<a name="L108" href="source/net/ipv4/ip_input.c#L108">108</a> <b><i> *              fragmentation anyway.</i></b>
<a name="L109" href="source/net/ipv4/ip_input.c#L109">109</a> <b><i> *</i></b>
<a name="L110" href="source/net/ipv4/ip_input.c#L110">110</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
<a name="L111" href="source/net/ipv4/ip_input.c#L111">111</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
<a name="L112" href="source/net/ipv4/ip_input.c#L112">112</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
<a name="L113" href="source/net/ipv4/ip_input.c#L113">113</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
<a name="L114" href="source/net/ipv4/ip_input.c#L114">114</a> <b><i> */</i></b>
<a name="L115" href="source/net/ipv4/ip_input.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/ip_input.c#L116">116</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPv4: "</i> <a href="ident?i=fmt">fmt</a>
<a name="L117" href="source/net/ipv4/ip_input.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/ip_input.c#L118">118</a> #include &lt;linux/module.h&gt;
<a name="L119" href="source/net/ipv4/ip_input.c#L119">119</a> #include &lt;linux/types.h&gt;
<a name="L120" href="source/net/ipv4/ip_input.c#L120">120</a> #include &lt;linux/kernel.h&gt;
<a name="L121" href="source/net/ipv4/ip_input.c#L121">121</a> #include &lt;linux/string.h&gt;
<a name="L122" href="source/net/ipv4/ip_input.c#L122">122</a> #include &lt;linux/errno.h&gt;
<a name="L123" href="source/net/ipv4/ip_input.c#L123">123</a> #include &lt;linux/slab.h&gt;
<a name="L124" href="source/net/ipv4/ip_input.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/ip_input.c#L125">125</a> #include &lt;linux/net.h&gt;
<a name="L126" href="source/net/ipv4/ip_input.c#L126">126</a> #include &lt;linux/socket.h&gt;
<a name="L127" href="source/net/ipv4/ip_input.c#L127">127</a> #include &lt;linux/sockios.h&gt;
<a name="L128" href="source/net/ipv4/ip_input.c#L128">128</a> #include &lt;linux/in.h&gt;
<a name="L129" href="source/net/ipv4/ip_input.c#L129">129</a> #include &lt;linux/inet.h&gt;
<a name="L130" href="source/net/ipv4/ip_input.c#L130">130</a> #include &lt;linux/inetdevice.h&gt;
<a name="L131" href="source/net/ipv4/ip_input.c#L131">131</a> #include &lt;linux/netdevice.h&gt;
<a name="L132" href="source/net/ipv4/ip_input.c#L132">132</a> #include &lt;linux/etherdevice.h&gt;
<a name="L133" href="source/net/ipv4/ip_input.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/ip_input.c#L134">134</a> #include &lt;net/snmp.h&gt;
<a name="L135" href="source/net/ipv4/ip_input.c#L135">135</a> #include &lt;net/ip.h&gt;
<a name="L136" href="source/net/ipv4/ip_input.c#L136">136</a> #include &lt;net/protocol.h&gt;
<a name="L137" href="source/net/ipv4/ip_input.c#L137">137</a> #include &lt;net/route.h&gt;
<a name="L138" href="source/net/ipv4/ip_input.c#L138">138</a> #include &lt;linux/skbuff.h&gt;
<a name="L139" href="source/net/ipv4/ip_input.c#L139">139</a> #include &lt;net/sock.h&gt;
<a name="L140" href="source/net/ipv4/ip_input.c#L140">140</a> #include &lt;net/arp.h&gt;
<a name="L141" href="source/net/ipv4/ip_input.c#L141">141</a> #include &lt;net/icmp.h&gt;
<a name="L142" href="source/net/ipv4/ip_input.c#L142">142</a> #include &lt;net/raw.h&gt;
<a name="L143" href="source/net/ipv4/ip_input.c#L143">143</a> #include &lt;net/checksum.h&gt;
<a name="L144" href="source/net/ipv4/ip_input.c#L144">144</a> #include &lt;net/inet_ecn.h&gt;
<a name="L145" href="source/net/ipv4/ip_input.c#L145">145</a> #include &lt;linux/netfilter_ipv4.h&gt;
<a name="L146" href="source/net/ipv4/ip_input.c#L146">146</a> #include &lt;net/xfrm.h&gt;
<a name="L147" href="source/net/ipv4/ip_input.c#L147">147</a> #include &lt;linux/mroute.h&gt;
<a name="L148" href="source/net/ipv4/ip_input.c#L148">148</a> #include &lt;linux/netlink.h&gt;
<a name="L149" href="source/net/ipv4/ip_input.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/ip_input.c#L150">150</a> <b><i>/*</i></b>
<a name="L151" href="source/net/ipv4/ip_input.c#L151">151</a> <b><i> *      Process Router Attention IP option (RFC 2113)</i></b>
<a name="L152" href="source/net/ipv4/ip_input.c#L152">152</a> <b><i> */</i></b>
<a name="L153" href="source/net/ipv4/ip_input.c#L153">153</a> <a href="ident?i=bool">bool</a> <a href="ident?i=ip_call_ra_chain">ip_call_ra_chain</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L154" href="source/net/ipv4/ip_input.c#L154">154</a> {
<a name="L155" href="source/net/ipv4/ip_input.c#L155">155</a>         struct <a href="ident?i=ip_ra_chain">ip_ra_chain</a> *<a href="ident?i=ra">ra</a>;
<a name="L156" href="source/net/ipv4/ip_input.c#L156">156</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L157" href="source/net/ipv4/ip_input.c#L157">157</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=last">last</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L158" href="source/net/ipv4/ip_input.c#L158">158</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L159" href="source/net/ipv4/ip_input.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/ip_input.c#L160">160</a>         for (<a href="ident?i=ra">ra</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=ip_ra_chain">ip_ra_chain</a>); <a href="ident?i=ra">ra</a>; <a href="ident?i=ra">ra</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=ra">ra</a>-&gt;<a href="ident?i=next">next</a>)) {
<a name="L161" href="source/net/ipv4/ip_input.c#L161">161</a>                 struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=ra">ra</a>-&gt;sk;
<a name="L162" href="source/net/ipv4/ip_input.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/ip_input.c#L163">163</a>                 <b><i>/* If socket is bound to an interface, only report</i></b>
<a name="L164" href="source/net/ipv4/ip_input.c#L164">164</a> <b><i>                 * the packet if it came  from that interface.</i></b>
<a name="L165" href="source/net/ipv4/ip_input.c#L165">165</a> <b><i>                 */</i></b>
<a name="L166" href="source/net/ipv4/ip_input.c#L166">166</a>                 if (sk &amp;&amp; <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> == <a href="ident?i=protocol">protocol</a> &amp;&amp;
<a name="L167" href="source/net/ipv4/ip_input.c#L167">167</a>                     (!sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> ||
<a name="L168" href="source/net/ipv4/ip_input.c#L168">168</a>                      sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> == <a href="ident?i=dev">dev</a>-&gt;ifindex) &amp;&amp;
<a name="L169" href="source/net/ipv4/ip_input.c#L169">169</a>                     <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>))) {
<a name="L170" href="source/net/ipv4/ip_input.c#L170">170</a>                         if (<a href="ident?i=ip_is_fragment">ip_is_fragment</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>))) {
<a name="L171" href="source/net/ipv4/ip_input.c#L171">171</a>                                 if (<a href="ident?i=ip_defrag">ip_defrag</a>(<a href="ident?i=skb">skb</a>, IP_DEFRAG_CALL_RA_CHAIN))
<a name="L172" href="source/net/ipv4/ip_input.c#L172">172</a>                                         return <a href="ident?i=true">true</a>;
<a name="L173" href="source/net/ipv4/ip_input.c#L173">173</a>                         }
<a name="L174" href="source/net/ipv4/ip_input.c#L174">174</a>                         if (<a href="ident?i=last">last</a>) {
<a name="L175" href="source/net/ipv4/ip_input.c#L175">175</a>                                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L176" href="source/net/ipv4/ip_input.c#L176">176</a>                                 if (skb2)
<a name="L177" href="source/net/ipv4/ip_input.c#L177">177</a>                                         <a href="ident?i=raw_rcv">raw_rcv</a>(<a href="ident?i=last">last</a>, skb2);
<a name="L178" href="source/net/ipv4/ip_input.c#L178">178</a>                         }
<a name="L179" href="source/net/ipv4/ip_input.c#L179">179</a>                         <a href="ident?i=last">last</a> = sk;
<a name="L180" href="source/net/ipv4/ip_input.c#L180">180</a>                 }
<a name="L181" href="source/net/ipv4/ip_input.c#L181">181</a>         }
<a name="L182" href="source/net/ipv4/ip_input.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/ip_input.c#L183">183</a>         if (<a href="ident?i=last">last</a>) {
<a name="L184" href="source/net/ipv4/ip_input.c#L184">184</a>                 <a href="ident?i=raw_rcv">raw_rcv</a>(<a href="ident?i=last">last</a>, <a href="ident?i=skb">skb</a>);
<a name="L185" href="source/net/ipv4/ip_input.c#L185">185</a>                 return <a href="ident?i=true">true</a>;
<a name="L186" href="source/net/ipv4/ip_input.c#L186">186</a>         }
<a name="L187" href="source/net/ipv4/ip_input.c#L187">187</a>         return <a href="ident?i=false">false</a>;
<a name="L188" href="source/net/ipv4/ip_input.c#L188">188</a> }
<a name="L189" href="source/net/ipv4/ip_input.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/ip_input.c#L190">190</a> static int <a href="ident?i=ip_local_deliver_finish">ip_local_deliver_finish</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L191" href="source/net/ipv4/ip_input.c#L191">191</a> {
<a name="L192" href="source/net/ipv4/ip_input.c#L192">192</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L193" href="source/net/ipv4/ip_input.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/ip_input.c#L194">194</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_network_header_len">skb_network_header_len</a>(<a href="ident?i=skb">skb</a>));
<a name="L195" href="source/net/ipv4/ip_input.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/ip_input.c#L196">196</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L197" href="source/net/ipv4/ip_input.c#L197">197</a>         {
<a name="L198" href="source/net/ipv4/ip_input.c#L198">198</a>                 int <a href="ident?i=protocol">protocol</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L199" href="source/net/ipv4/ip_input.c#L199">199</a>                 const struct <a href="ident?i=net_protocol">net_protocol</a> *ipprot;
<a name="L200" href="source/net/ipv4/ip_input.c#L200">200</a>                 int <a href="ident?i=raw">raw</a>;
<a name="L201" href="source/net/ipv4/ip_input.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/ip_input.c#L202">202</a>         resubmit:
<a name="L203" href="source/net/ipv4/ip_input.c#L203">203</a>                 <a href="ident?i=raw">raw</a> = <a href="ident?i=raw_local_deliver">raw_local_deliver</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=protocol">protocol</a>);
<a name="L204" href="source/net/ipv4/ip_input.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/ip_input.c#L205">205</a>                 ipprot = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=protocol">protocol</a>]);
<a name="L206" href="source/net/ipv4/ip_input.c#L206">206</a>                 if (ipprot) {
<a name="L207" href="source/net/ipv4/ip_input.c#L207">207</a>                         int <a href="ident?i=ret">ret</a>;
<a name="L208" href="source/net/ipv4/ip_input.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/ip_input.c#L209">209</a>                         if (!ipprot-&gt;no_policy) {
<a name="L210" href="source/net/ipv4/ip_input.c#L210">210</a>                                 if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>)) {
<a name="L211" href="source/net/ipv4/ip_input.c#L211">211</a>                                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L212" href="source/net/ipv4/ip_input.c#L212">212</a>                                         goto <a href="ident?i=out">out</a>;
<a name="L213" href="source/net/ipv4/ip_input.c#L213">213</a>                                 }
<a name="L214" href="source/net/ipv4/ip_input.c#L214">214</a>                                 <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L215" href="source/net/ipv4/ip_input.c#L215">215</a>                         }
<a name="L216" href="source/net/ipv4/ip_input.c#L216">216</a>                         <a href="ident?i=ret">ret</a> = ipprot-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>);
<a name="L217" href="source/net/ipv4/ip_input.c#L217">217</a>                         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L218" href="source/net/ipv4/ip_input.c#L218">218</a>                                 <a href="ident?i=protocol">protocol</a> = -<a href="ident?i=ret">ret</a>;
<a name="L219" href="source/net/ipv4/ip_input.c#L219">219</a>                                 goto resubmit;
<a name="L220" href="source/net/ipv4/ip_input.c#L220">220</a>                         }
<a name="L221" href="source/net/ipv4/ip_input.c#L221">221</a>                         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_INDELIVERS);
<a name="L222" href="source/net/ipv4/ip_input.c#L222">222</a>                 } else {
<a name="L223" href="source/net/ipv4/ip_input.c#L223">223</a>                         if (!<a href="ident?i=raw">raw</a>) {
<a name="L224" href="source/net/ipv4/ip_input.c#L224">224</a>                                 if (<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>)) {
<a name="L225" href="source/net/ipv4/ip_input.c#L225">225</a>                                         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_INUNKNOWNPROTOS);
<a name="L226" href="source/net/ipv4/ip_input.c#L226">226</a>                                         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>,
<a name="L227" href="source/net/ipv4/ip_input.c#L227">227</a>                                                   <a href="ident?i=ICMP_PROT_UNREACH">ICMP_PROT_UNREACH</a>, 0);
<a name="L228" href="source/net/ipv4/ip_input.c#L228">228</a>                                 }
<a name="L229" href="source/net/ipv4/ip_input.c#L229">229</a>                                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L230" href="source/net/ipv4/ip_input.c#L230">230</a>                         } else {
<a name="L231" href="source/net/ipv4/ip_input.c#L231">231</a>                                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_INDELIVERS);
<a name="L232" href="source/net/ipv4/ip_input.c#L232">232</a>                                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L233" href="source/net/ipv4/ip_input.c#L233">233</a>                         }
<a name="L234" href="source/net/ipv4/ip_input.c#L234">234</a>                 }
<a name="L235" href="source/net/ipv4/ip_input.c#L235">235</a>         }
<a name="L236" href="source/net/ipv4/ip_input.c#L236">236</a>  <a href="ident?i=out">out</a>:
<a name="L237" href="source/net/ipv4/ip_input.c#L237">237</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L238" href="source/net/ipv4/ip_input.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/ip_input.c#L239">239</a>         return 0;
<a name="L240" href="source/net/ipv4/ip_input.c#L240">240</a> }
<a name="L241" href="source/net/ipv4/ip_input.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/ip_input.c#L242">242</a> <b><i>/*</i></b>
<a name="L243" href="source/net/ipv4/ip_input.c#L243">243</a> <b><i> *      Deliver IP Packets to the higher protocol layers.</i></b>
<a name="L244" href="source/net/ipv4/ip_input.c#L244">244</a> <b><i> */</i></b>
<a name="L245" href="source/net/ipv4/ip_input.c#L245">245</a> int <a href="ident?i=ip_local_deliver">ip_local_deliver</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L246" href="source/net/ipv4/ip_input.c#L246">246</a> {
<a name="L247" href="source/net/ipv4/ip_input.c#L247">247</a>         <b><i>/*</i></b>
<a name="L248" href="source/net/ipv4/ip_input.c#L248">248</a> <b><i>         *      Reassemble IP fragments.</i></b>
<a name="L249" href="source/net/ipv4/ip_input.c#L249">249</a> <b><i>         */</i></b>
<a name="L250" href="source/net/ipv4/ip_input.c#L250">250</a> 
<a name="L251" href="source/net/ipv4/ip_input.c#L251">251</a>         if (<a href="ident?i=ip_is_fragment">ip_is_fragment</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>))) {
<a name="L252" href="source/net/ipv4/ip_input.c#L252">252</a>                 if (<a href="ident?i=ip_defrag">ip_defrag</a>(<a href="ident?i=skb">skb</a>, IP_DEFRAG_LOCAL_DELIVER))
<a name="L253" href="source/net/ipv4/ip_input.c#L253">253</a>                         return 0;
<a name="L254" href="source/net/ipv4/ip_input.c#L254">254</a>         }
<a name="L255" href="source/net/ipv4/ip_input.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/ip_input.c#L256">256</a>         return <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_LOCAL_IN, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
<a name="L257" href="source/net/ipv4/ip_input.c#L257">257</a>                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L258" href="source/net/ipv4/ip_input.c#L258">258</a>                        <a href="ident?i=ip_local_deliver_finish">ip_local_deliver_finish</a>);
<a name="L259" href="source/net/ipv4/ip_input.c#L259">259</a> }
<a name="L260" href="source/net/ipv4/ip_input.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/ip_input.c#L261">261</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=ip_rcv_options">ip_rcv_options</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L262" href="source/net/ipv4/ip_input.c#L262">262</a> {
<a name="L263" href="source/net/ipv4/ip_input.c#L263">263</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt;
<a name="L264" href="source/net/ipv4/ip_input.c#L264">264</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L265" href="source/net/ipv4/ip_input.c#L265">265</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L266" href="source/net/ipv4/ip_input.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/ip_input.c#L267">267</a>         <b><i>/* It looks as overkill, because not all</i></b>
<a name="L268" href="source/net/ipv4/ip_input.c#L268">268</a> <b><i>           IP options require packet mangling.</i></b>
<a name="L269" href="source/net/ipv4/ip_input.c#L269">269</a> <b><i>           But it is the easiest for now, especially taking</i></b>
<a name="L270" href="source/net/ipv4/ip_input.c#L270">270</a> <b><i>           into account that combination of IP options</i></b>
<a name="L271" href="source/net/ipv4/ip_input.c#L271">271</a> <b><i>           and running sniffer is extremely rare condition.</i></b>
<a name="L272" href="source/net/ipv4/ip_input.c#L272">272</a> <b><i>                                              --ANK (980813)</i></b>
<a name="L273" href="source/net/ipv4/ip_input.c#L273">273</a> <b><i>        */</i></b>
<a name="L274" href="source/net/ipv4/ip_input.c#L274">274</a>         if (<a href="ident?i=skb_cow">skb_cow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>))) {
<a name="L275" href="source/net/ipv4/ip_input.c#L275">275</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INDISCARDS);
<a name="L276" href="source/net/ipv4/ip_input.c#L276">276</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L277" href="source/net/ipv4/ip_input.c#L277">277</a>         }
<a name="L278" href="source/net/ipv4/ip_input.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/ip_input.c#L279">279</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L280" href="source/net/ipv4/ip_input.c#L280">280</a>         opt = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
<a name="L281" href="source/net/ipv4/ip_input.c#L281">281</a>         opt-&gt;<a href="ident?i=optlen">optlen</a> = iph-&gt;ihl*4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L282" href="source/net/ipv4/ip_input.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/ip_input.c#L283">283</a>         if (<a href="ident?i=ip_options_compile">ip_options_compile</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), opt, <a href="ident?i=skb">skb</a>)) {
<a name="L284" href="source/net/ipv4/ip_input.c#L284">284</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INHDRERRORS);
<a name="L285" href="source/net/ipv4/ip_input.c#L285">285</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L286" href="source/net/ipv4/ip_input.c#L286">286</a>         }
<a name="L287" href="source/net/ipv4/ip_input.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/ip_input.c#L288">288</a>         if (<a href="ident?i=unlikely">unlikely</a>(opt-&gt;<a href="ident?i=srr">srr</a>)) {
<a name="L289" href="source/net/ipv4/ip_input.c#L289">289</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L290" href="source/net/ipv4/ip_input.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/ip_input.c#L291">291</a>                 if (in_dev) {
<a name="L292" href="source/net/ipv4/ip_input.c#L292">292</a>                         if (!<a href="ident?i=IN_DEV_SOURCE_ROUTE">IN_DEV_SOURCE_ROUTE</a>(in_dev)) {
<a name="L293" href="source/net/ipv4/ip_input.c#L293">293</a>                                 if (<a href="ident?i=IN_DEV_LOG_MARTIANS">IN_DEV_LOG_MARTIANS</a>(in_dev))
<a name="L294" href="source/net/ipv4/ip_input.c#L294">294</a>                                         <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"source route option %pI4 -&gt; %pI4\n"</i>,
<a name="L295" href="source/net/ipv4/ip_input.c#L295">295</a>                                                              &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L296" href="source/net/ipv4/ip_input.c#L296">296</a>                                                              &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L297" href="source/net/ipv4/ip_input.c#L297">297</a>                                 goto <a href="ident?i=drop">drop</a>;
<a name="L298" href="source/net/ipv4/ip_input.c#L298">298</a>                         }
<a name="L299" href="source/net/ipv4/ip_input.c#L299">299</a>                 }
<a name="L300" href="source/net/ipv4/ip_input.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/ip_input.c#L301">301</a>                 if (<a href="ident?i=ip_options_rcv_srr">ip_options_rcv_srr</a>(<a href="ident?i=skb">skb</a>))
<a name="L302" href="source/net/ipv4/ip_input.c#L302">302</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L303" href="source/net/ipv4/ip_input.c#L303">303</a>         }
<a name="L304" href="source/net/ipv4/ip_input.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/ip_input.c#L305">305</a>         return <a href="ident?i=false">false</a>;
<a name="L306" href="source/net/ipv4/ip_input.c#L306">306</a> <a href="ident?i=drop">drop</a>:
<a name="L307" href="source/net/ipv4/ip_input.c#L307">307</a>         return <a href="ident?i=true">true</a>;
<a name="L308" href="source/net/ipv4/ip_input.c#L308">308</a> }
<a name="L309" href="source/net/ipv4/ip_input.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/ip_input.c#L310">310</a> int <a href="ident?i=sysctl_ip_early_demux">sysctl_ip_early_demux</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
<a name="L311" href="source/net/ipv4/ip_input.c#L311">311</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_ip_early_demux">sysctl_ip_early_demux</a>);
<a name="L312" href="source/net/ipv4/ip_input.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/ip_input.c#L313">313</a> static int <a href="ident?i=ip_rcv_finish">ip_rcv_finish</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L314" href="source/net/ipv4/ip_input.c#L314">314</a> {
<a name="L315" href="source/net/ipv4/ip_input.c#L315">315</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L316" href="source/net/ipv4/ip_input.c#L316">316</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L317" href="source/net/ipv4/ip_input.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/ip_input.c#L318">318</a>         if (<a href="ident?i=sysctl_ip_early_demux">sysctl_ip_early_demux</a> &amp;&amp; !<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>) &amp;&amp; !<a href="ident?i=skb">skb</a>-&gt;sk) {
<a name="L319" href="source/net/ipv4/ip_input.c#L319">319</a>                 const struct <a href="ident?i=net_protocol">net_protocol</a> *ipprot;
<a name="L320" href="source/net/ipv4/ip_input.c#L320">320</a>                 int <a href="ident?i=protocol">protocol</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L321" href="source/net/ipv4/ip_input.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/ip_input.c#L322">322</a>                 ipprot = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=protocol">protocol</a>]);
<a name="L323" href="source/net/ipv4/ip_input.c#L323">323</a>                 if (ipprot &amp;&amp; ipprot-&gt;early_demux) {
<a name="L324" href="source/net/ipv4/ip_input.c#L324">324</a>                         ipprot-&gt;early_demux(<a href="ident?i=skb">skb</a>);
<a name="L325" href="source/net/ipv4/ip_input.c#L325">325</a>                         <b><i>/* must reload iph, skb-&gt;head might have changed */</i></b>
<a name="L326" href="source/net/ipv4/ip_input.c#L326">326</a>                         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L327" href="source/net/ipv4/ip_input.c#L327">327</a>                 }
<a name="L328" href="source/net/ipv4/ip_input.c#L328">328</a>         }
<a name="L329" href="source/net/ipv4/ip_input.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/ip_input.c#L330">330</a>         <b><i>/*</i></b>
<a name="L331" href="source/net/ipv4/ip_input.c#L331">331</a> <b><i>         *      Initialise the virtual path cache for the packet. It describes</i></b>
<a name="L332" href="source/net/ipv4/ip_input.c#L332">332</a> <b><i>         *      how the packet travels inside Linux networking.</i></b>
<a name="L333" href="source/net/ipv4/ip_input.c#L333">333</a> <b><i>         */</i></b>
<a name="L334" href="source/net/ipv4/ip_input.c#L334">334</a>         if (!<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L335" href="source/net/ipv4/ip_input.c#L335">335</a>                 int <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_input_noref">ip_route_input_noref</a>(<a href="ident?i=skb">skb</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L336" href="source/net/ipv4/ip_input.c#L336">336</a>                                                iph-&gt;tos, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L337" href="source/net/ipv4/ip_input.c#L337">337</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>)) {
<a name="L338" href="source/net/ipv4/ip_input.c#L338">338</a>                         if (<a href="ident?i=err">err</a> == -<a href="ident?i=EXDEV">EXDEV</a>)
<a name="L339" href="source/net/ipv4/ip_input.c#L339">339</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>),
<a name="L340" href="source/net/ipv4/ip_input.c#L340">340</a>                                                  LINUX_MIB_IPRPFILTER);
<a name="L341" href="source/net/ipv4/ip_input.c#L341">341</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L342" href="source/net/ipv4/ip_input.c#L342">342</a>                 }
<a name="L343" href="source/net/ipv4/ip_input.c#L343">343</a>         }
<a name="L344" href="source/net/ipv4/ip_input.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/ip_input.c#L345">345</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L346" href="source/net/ipv4/ip_input.c#L346">346</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;tclassid)) {
<a name="L347" href="source/net/ipv4/ip_input.c#L347">347</a>                 struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a> *<a href="ident?i=st">st</a> = <a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(<a href="ident?i=ip_rt_acct">ip_rt_acct</a>);
<a name="L348" href="source/net/ipv4/ip_input.c#L348">348</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=idx">idx</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;tclassid;
<a name="L349" href="source/net/ipv4/ip_input.c#L349">349</a>                 <a href="ident?i=st">st</a>[<a href="ident?i=idx">idx</a>&amp;0xFF].o_packets++;
<a name="L350" href="source/net/ipv4/ip_input.c#L350">350</a>                 <a href="ident?i=st">st</a>[<a href="ident?i=idx">idx</a>&amp;0xFF].o_bytes += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L351" href="source/net/ipv4/ip_input.c#L351">351</a>                 <a href="ident?i=st">st</a>[(<a href="ident?i=idx">idx</a>&gt;&gt;16)&amp;0xFF].i_packets++;
<a name="L352" href="source/net/ipv4/ip_input.c#L352">352</a>                 <a href="ident?i=st">st</a>[(<a href="ident?i=idx">idx</a>&gt;&gt;16)&amp;0xFF].i_bytes += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L353" href="source/net/ipv4/ip_input.c#L353">353</a>         }
<a name="L354" href="source/net/ipv4/ip_input.c#L354">354</a> #endif
<a name="L355" href="source/net/ipv4/ip_input.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/ip_input.c#L356">356</a>         if (iph-&gt;ihl &gt; 5 &amp;&amp; <a href="ident?i=ip_rcv_options">ip_rcv_options</a>(<a href="ident?i=skb">skb</a>))
<a name="L357" href="source/net/ipv4/ip_input.c#L357">357</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L358" href="source/net/ipv4/ip_input.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/ip_input.c#L359">359</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L360" href="source/net/ipv4/ip_input.c#L360">360</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_type == RTN_MULTICAST) {
<a name="L361" href="source/net/ipv4/ip_input.c#L361">361</a>                 <a href="ident?i=IP_UPD_PO_STATS_BH">IP_UPD_PO_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INMCAST,
<a name="L362" href="source/net/ipv4/ip_input.c#L362">362</a>                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L363" href="source/net/ipv4/ip_input.c#L363">363</a>         } else if (<a href="ident?i=rt">rt</a>-&gt;rt_type == RTN_BROADCAST)
<a name="L364" href="source/net/ipv4/ip_input.c#L364">364</a>                 <a href="ident?i=IP_UPD_PO_STATS_BH">IP_UPD_PO_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INBCAST,
<a name="L365" href="source/net/ipv4/ip_input.c#L365">365</a>                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L366" href="source/net/ipv4/ip_input.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/ip_input.c#L367">367</a>         return <a href="ident?i=dst_input">dst_input</a>(<a href="ident?i=skb">skb</a>);
<a name="L368" href="source/net/ipv4/ip_input.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/ip_input.c#L369">369</a> <a href="ident?i=drop">drop</a>:
<a name="L370" href="source/net/ipv4/ip_input.c#L370">370</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L371" href="source/net/ipv4/ip_input.c#L371">371</a>         return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L372" href="source/net/ipv4/ip_input.c#L372">372</a> }
<a name="L373" href="source/net/ipv4/ip_input.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/ip_input.c#L374">374</a> <b><i>/*</i></b>
<a name="L375" href="source/net/ipv4/ip_input.c#L375">375</a> <b><i> *      Main IP Receive routine.</i></b>
<a name="L376" href="source/net/ipv4/ip_input.c#L376">376</a> <b><i> */</i></b>
<a name="L377" href="source/net/ipv4/ip_input.c#L377">377</a> int <a href="ident?i=ip_rcv">ip_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=packet_type">packet_type</a> *<a href="ident?i=pt">pt</a>, struct <a href="ident?i=net_device">net_device</a> *orig_dev)
<a name="L378" href="source/net/ipv4/ip_input.c#L378">378</a> {
<a name="L379" href="source/net/ipv4/ip_input.c#L379">379</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L380" href="source/net/ipv4/ip_input.c#L380">380</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>;
<a name="L381" href="source/net/ipv4/ip_input.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/ip_input.c#L382">382</a>         <b><i>/* When the interface is in promisc. mode, drop all the crap</i></b>
<a name="L383" href="source/net/ipv4/ip_input.c#L383">383</a> <b><i>         * that it receives, do not try to analyse it.</i></b>
<a name="L384" href="source/net/ipv4/ip_input.c#L384">384</a> <b><i>         */</i></b>
<a name="L385" href="source/net/ipv4/ip_input.c#L385">385</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_OTHERHOST">PACKET_OTHERHOST</a>)
<a name="L386" href="source/net/ipv4/ip_input.c#L386">386</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L387" href="source/net/ipv4/ip_input.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/ip_input.c#L388">388</a> 
<a name="L389" href="source/net/ipv4/ip_input.c#L389">389</a>         <a href="ident?i=IP_UPD_PO_STATS_BH">IP_UPD_PO_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_IN, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L390" href="source/net/ipv4/ip_input.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/ip_input.c#L391">391</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_share_check">skb_share_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L392" href="source/net/ipv4/ip_input.c#L392">392</a>         if (!<a href="ident?i=skb">skb</a>) {
<a name="L393" href="source/net/ipv4/ip_input.c#L393">393</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INDISCARDS);
<a name="L394" href="source/net/ipv4/ip_input.c#L394">394</a>                 goto <a href="ident?i=out">out</a>;
<a name="L395" href="source/net/ipv4/ip_input.c#L395">395</a>         }
<a name="L396" href="source/net/ipv4/ip_input.c#L396">396</a> 
<a name="L397" href="source/net/ipv4/ip_input.c#L397">397</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
<a name="L398" href="source/net/ipv4/ip_input.c#L398">398</a>                 goto inhdr_error;
<a name="L399" href="source/net/ipv4/ip_input.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/ip_input.c#L400">400</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L401" href="source/net/ipv4/ip_input.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/ip_input.c#L402">402</a>         <b><i>/*</i></b>
<a name="L403" href="source/net/ipv4/ip_input.c#L403">403</a> <b><i>         *      RFC1122: 3.2.1.2 MUST silently discard any IP frame that fails the checksum.</i></b>
<a name="L404" href="source/net/ipv4/ip_input.c#L404">404</a> <b><i>         *</i></b>
<a name="L405" href="source/net/ipv4/ip_input.c#L405">405</a> <b><i>         *      Is the datagram acceptable?</i></b>
<a name="L406" href="source/net/ipv4/ip_input.c#L406">406</a> <b><i>         *</i></b>
<a name="L407" href="source/net/ipv4/ip_input.c#L407">407</a> <b><i>         *      1.      Length at least the size of an ip header</i></b>
<a name="L408" href="source/net/ipv4/ip_input.c#L408">408</a> <b><i>         *      2.      Version of 4</i></b>
<a name="L409" href="source/net/ipv4/ip_input.c#L409">409</a> <b><i>         *      3.      Checksums correctly. [Speed optimisation for later, skip loopback checksums]</i></b>
<a name="L410" href="source/net/ipv4/ip_input.c#L410">410</a> <b><i>         *      4.      Doesn't have a bogus length</i></b>
<a name="L411" href="source/net/ipv4/ip_input.c#L411">411</a> <b><i>         */</i></b>
<a name="L412" href="source/net/ipv4/ip_input.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/ip_input.c#L413">413</a>         if (iph-&gt;ihl &lt; 5 || iph-&gt;<a href="ident?i=version">version</a> != 4)
<a name="L414" href="source/net/ipv4/ip_input.c#L414">414</a>                 goto inhdr_error;
<a name="L415" href="source/net/ipv4/ip_input.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/ip_input.c#L416">416</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(IPSTATS_MIB_ECT1PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_1);
<a name="L417" href="source/net/ipv4/ip_input.c#L417">417</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(IPSTATS_MIB_ECT0PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_0);
<a name="L418" href="source/net/ipv4/ip_input.c#L418">418</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(IPSTATS_MIB_CEPKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_CE);
<a name="L419" href="source/net/ipv4/ip_input.c#L419">419</a>         <a href="ident?i=IP_ADD_STATS_BH">IP_ADD_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>),
<a name="L420" href="source/net/ipv4/ip_input.c#L420">420</a>                         IPSTATS_MIB_NOECTPKTS + (iph-&gt;tos &amp; INET_ECN_MASK),
<a name="L421" href="source/net/ipv4/ip_input.c#L421">421</a>                         <a href="ident?i=max_t">max_t</a>(unsigned short, 1, <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs));
<a name="L422" href="source/net/ipv4/ip_input.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/ip_input.c#L423">423</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, iph-&gt;ihl*4))
<a name="L424" href="source/net/ipv4/ip_input.c#L424">424</a>                 goto inhdr_error;
<a name="L425" href="source/net/ipv4/ip_input.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/ip_input.c#L426">426</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L427" href="source/net/ipv4/ip_input.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/ip_input.c#L428">428</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=ip_fast_csum">ip_fast_csum</a>((<a href="ident?i=u8">u8</a> *)iph, iph-&gt;ihl)))
<a name="L429" href="source/net/ipv4/ip_input.c#L429">429</a>                 goto csum_error;
<a name="L430" href="source/net/ipv4/ip_input.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/ip_input.c#L431">431</a>         <a href="ident?i=len">len</a> = <a href="ident?i=ntohs">ntohs</a>(iph-&gt;tot_len);
<a name="L432" href="source/net/ipv4/ip_input.c#L432">432</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; <a href="ident?i=len">len</a>) {
<a name="L433" href="source/net/ipv4/ip_input.c#L433">433</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INTRUNCATEDPKTS);
<a name="L434" href="source/net/ipv4/ip_input.c#L434">434</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L435" href="source/net/ipv4/ip_input.c#L435">435</a>         } else if (<a href="ident?i=len">len</a> &lt; (iph-&gt;ihl*4))
<a name="L436" href="source/net/ipv4/ip_input.c#L436">436</a>                 goto inhdr_error;
<a name="L437" href="source/net/ipv4/ip_input.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ip_input.c#L438">438</a>         <b><i>/* Our transport medium may have padded the buffer out. Now we know it</i></b>
<a name="L439" href="source/net/ipv4/ip_input.c#L439">439</a> <b><i>         * is IP we can trim to the true length of the frame.</i></b>
<a name="L440" href="source/net/ipv4/ip_input.c#L440">440</a> <b><i>         * Note this now means skb-&gt;len holds ntohs(iph-&gt;tot_len).</i></b>
<a name="L441" href="source/net/ipv4/ip_input.c#L441">441</a> <b><i>         */</i></b>
<a name="L442" href="source/net/ipv4/ip_input.c#L442">442</a>         if (<a href="ident?i=pskb_trim_rcsum">pskb_trim_rcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>)) {
<a name="L443" href="source/net/ipv4/ip_input.c#L443">443</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INDISCARDS);
<a name="L444" href="source/net/ipv4/ip_input.c#L444">444</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L445" href="source/net/ipv4/ip_input.c#L445">445</a>         }
<a name="L446" href="source/net/ipv4/ip_input.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/ip_input.c#L447">447</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header + iph-&gt;ihl*4;
<a name="L448" href="source/net/ipv4/ip_input.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/ip_input.c#L449">449</a>         <b><i>/* Remove any debris in the socket control block */</i></b>
<a name="L450" href="source/net/ipv4/ip_input.c#L450">450</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(struct <a href="ident?i=inet_skb_parm">inet_skb_parm</a>));
<a name="L451" href="source/net/ipv4/ip_input.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/ip_input.c#L452">452</a>         <b><i>/* Must drop socket now because of tproxy. */</i></b>
<a name="L453" href="source/net/ipv4/ip_input.c#L453">453</a>         <a href="ident?i=skb_orphan">skb_orphan</a>(<a href="ident?i=skb">skb</a>);
<a name="L454" href="source/net/ipv4/ip_input.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/ip_input.c#L455">455</a>         return <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_PRE_ROUTING, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
<a name="L456" href="source/net/ipv4/ip_input.c#L456">456</a>                        <a href="ident?i=dev">dev</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L457" href="source/net/ipv4/ip_input.c#L457">457</a>                        <a href="ident?i=ip_rcv_finish">ip_rcv_finish</a>);
<a name="L458" href="source/net/ipv4/ip_input.c#L458">458</a> 
<a name="L459" href="source/net/ipv4/ip_input.c#L459">459</a> csum_error:
<a name="L460" href="source/net/ipv4/ip_input.c#L460">460</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_CSUMERRORS);
<a name="L461" href="source/net/ipv4/ip_input.c#L461">461</a> inhdr_error:
<a name="L462" href="source/net/ipv4/ip_input.c#L462">462</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INHDRERRORS);
<a name="L463" href="source/net/ipv4/ip_input.c#L463">463</a> <a href="ident?i=drop">drop</a>:
<a name="L464" href="source/net/ipv4/ip_input.c#L464">464</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L465" href="source/net/ipv4/ip_input.c#L465">465</a> <a href="ident?i=out">out</a>:
<a name="L466" href="source/net/ipv4/ip_input.c#L466">466</a>         return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L467" href="source/net/ipv4/ip_input.c#L467">467</a> }
<a name="L468" href="source/net/ipv4/ip_input.c#L468">468</a> </pre></div><p>
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
