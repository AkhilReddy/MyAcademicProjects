<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_probe.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_probe.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_probe.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_probe.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_probe.c">tcp_probe.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_probe.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_probe.c#L2">2</a> <b><i> * tcpprobe - Observe the TCP flow with kprobes.</i></b>
  <a name="L3" href="source/net/ipv4/tcp_probe.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_probe.c#L4">4</a> <b><i> * The idea for this came from Werner Almesberger's umlsim</i></b>
  <a name="L5" href="source/net/ipv4/tcp_probe.c#L5">5</a> <b><i> * Copyright (C) 2004, Stephen Hemminger &lt;shemminger@osdl.org&gt;</i></b>
  <a name="L6" href="source/net/ipv4/tcp_probe.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/tcp_probe.c#L7">7</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L8" href="source/net/ipv4/tcp_probe.c#L8">8</a> <b><i> * it under the terms of the GNU General Public License as published by</i></b>
  <a name="L9" href="source/net/ipv4/tcp_probe.c#L9">9</a> <b><i> * the Free Software Foundation; either version 2 of the License.</i></b>
 <a name="L10" href="source/net/ipv4/tcp_probe.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/tcp_probe.c#L11">11</a> <b><i> * This program is distributed in the hope that it will be useful,</i></b>
 <a name="L12" href="source/net/ipv4/tcp_probe.c#L12">12</a> <b><i> * but WITHOUT ANY WARRANTY; without even the implied warranty of</i></b>
 <a name="L13" href="source/net/ipv4/tcp_probe.c#L13">13</a> <b><i> * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</i></b>
 <a name="L14" href="source/net/ipv4/tcp_probe.c#L14">14</a> <b><i> * GNU General Public License for more details.</i></b>
 <a name="L15" href="source/net/ipv4/tcp_probe.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/tcp_probe.c#L16">16</a> <b><i> * You should have received a copy of the GNU General Public License</i></b>
 <a name="L17" href="source/net/ipv4/tcp_probe.c#L17">17</a> <b><i> * along with this program; if not, write to the Free Software</i></b>
 <a name="L18" href="source/net/ipv4/tcp_probe.c#L18">18</a> <b><i> * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.</i></b>
 <a name="L19" href="source/net/ipv4/tcp_probe.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_probe.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_probe.c#L21">21</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L22" href="source/net/ipv4/tcp_probe.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/tcp_probe.c#L23">23</a> #include &lt;linux/kernel.h&gt;
 <a name="L24" href="source/net/ipv4/tcp_probe.c#L24">24</a> #include &lt;linux/kprobes.h&gt;
 <a name="L25" href="source/net/ipv4/tcp_probe.c#L25">25</a> #include &lt;linux/socket.h&gt;
 <a name="L26" href="source/net/ipv4/tcp_probe.c#L26">26</a> #include &lt;linux/tcp.h&gt;
 <a name="L27" href="source/net/ipv4/tcp_probe.c#L27">27</a> #include &lt;linux/slab.h&gt;
 <a name="L28" href="source/net/ipv4/tcp_probe.c#L28">28</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L29" href="source/net/ipv4/tcp_probe.c#L29">29</a> #include &lt;linux/module.h&gt;
 <a name="L30" href="source/net/ipv4/tcp_probe.c#L30">30</a> #include &lt;linux/ktime.h&gt;
 <a name="L31" href="source/net/ipv4/tcp_probe.c#L31">31</a> #include &lt;linux/time.h&gt;
 <a name="L32" href="source/net/ipv4/tcp_probe.c#L32">32</a> #include &lt;net/net_namespace.h&gt;
 <a name="L33" href="source/net/ipv4/tcp_probe.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/tcp_probe.c#L34">34</a> #include &lt;net/tcp.h&gt;
 <a name="L35" href="source/net/ipv4/tcp_probe.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tcp_probe.c#L36">36</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Stephen Hemminger &lt;shemminger@linux-foundation.org&gt;"</i>);
 <a name="L37" href="source/net/ipv4/tcp_probe.c#L37">37</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP cwnd snooper"</i>);
 <a name="L38" href="source/net/ipv4/tcp_probe.c#L38">38</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L39" href="source/net/ipv4/tcp_probe.c#L39">39</a> <a href="ident?i=MODULE_VERSION">MODULE_VERSION</a>(<i>"1.1"</i>);
 <a name="L40" href="source/net/ipv4/tcp_probe.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/tcp_probe.c#L41">41</a> static int <a href="ident?i=port">port</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L42" href="source/net/ipv4/tcp_probe.c#L42">42</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=port">port</a>, <i>"Port to match (0=all)"</i>);
 <a name="L43" href="source/net/ipv4/tcp_probe.c#L43">43</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=port">port</a>, int, 0);
 <a name="L44" href="source/net/ipv4/tcp_probe.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/tcp_probe.c#L45">45</a> static unsigned int <a href="ident?i=bufsize">bufsize</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 4096;
 <a name="L46" href="source/net/ipv4/tcp_probe.c#L46">46</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=bufsize">bufsize</a>, <i>"Log buffer size in packets (4096)"</i>);
 <a name="L47" href="source/net/ipv4/tcp_probe.c#L47">47</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=bufsize">bufsize</a>, <a href="ident?i=uint">uint</a>, 0);
 <a name="L48" href="source/net/ipv4/tcp_probe.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/tcp_probe.c#L49">49</a> static unsigned int fwmark <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L50" href="source/net/ipv4/tcp_probe.c#L50">50</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(fwmark, <i>"skb mark to match (0=no mark)"</i>);
 <a name="L51" href="source/net/ipv4/tcp_probe.c#L51">51</a> <a href="ident?i=module_param">module_param</a>(fwmark, <a href="ident?i=uint">uint</a>, 0);
 <a name="L52" href="source/net/ipv4/tcp_probe.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/tcp_probe.c#L53">53</a> static int full <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L54" href="source/net/ipv4/tcp_probe.c#L54">54</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(full, <i>"Full log (1=every ack packet received,  0=only cwnd changes)"</i>);
 <a name="L55" href="source/net/ipv4/tcp_probe.c#L55">55</a> <a href="ident?i=module_param">module_param</a>(full, int, 0);
 <a name="L56" href="source/net/ipv4/tcp_probe.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/tcp_probe.c#L57">57</a> static const char <a href="ident?i=procname">procname</a>[] = <i>"tcpprobe"</i>;
 <a name="L58" href="source/net/ipv4/tcp_probe.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/tcp_probe.c#L59">59</a> struct <a href="ident?i=tcp_log">tcp_log</a> {
 <a name="L60" href="source/net/ipv4/tcp_probe.c#L60">60</a>         <a href="ident?i=ktime_t">ktime_t</a> tstamp;
 <a name="L61" href="source/net/ipv4/tcp_probe.c#L61">61</a>         union {
 <a name="L62" href="source/net/ipv4/tcp_probe.c#L62">62</a>                 struct <a href="ident?i=sockaddr">sockaddr</a>         <a href="ident?i=raw">raw</a>;
 <a name="L63" href="source/net/ipv4/tcp_probe.c#L63">63</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a>      <a href="ident?i=v4">v4</a>;
 <a name="L64" href="source/net/ipv4/tcp_probe.c#L64">64</a>                 struct <a href="ident?i=sockaddr_in6">sockaddr_in6</a>     <a href="ident?i=v6">v6</a>;
 <a name="L65" href="source/net/ipv4/tcp_probe.c#L65">65</a>         }       <a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>;
 <a name="L66" href="source/net/ipv4/tcp_probe.c#L66">66</a>         <a href="ident?i=u16">u16</a>     <a href="ident?i=length">length</a>;
 <a name="L67" href="source/net/ipv4/tcp_probe.c#L67">67</a>         <a href="ident?i=u32">u32</a>     snd_nxt;
 <a name="L68" href="source/net/ipv4/tcp_probe.c#L68">68</a>         <a href="ident?i=u32">u32</a>     snd_una;
 <a name="L69" href="source/net/ipv4/tcp_probe.c#L69">69</a>         <a href="ident?i=u32">u32</a>     snd_wnd;
 <a name="L70" href="source/net/ipv4/tcp_probe.c#L70">70</a>         <a href="ident?i=u32">u32</a>     rcv_wnd;
 <a name="L71" href="source/net/ipv4/tcp_probe.c#L71">71</a>         <a href="ident?i=u32">u32</a>     snd_cwnd;
 <a name="L72" href="source/net/ipv4/tcp_probe.c#L72">72</a>         <a href="ident?i=u32">u32</a>     ssthresh;
 <a name="L73" href="source/net/ipv4/tcp_probe.c#L73">73</a>         <a href="ident?i=u32">u32</a>     srtt;
 <a name="L74" href="source/net/ipv4/tcp_probe.c#L74">74</a> };
 <a name="L75" href="source/net/ipv4/tcp_probe.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/tcp_probe.c#L76">76</a> static struct {
 <a name="L77" href="source/net/ipv4/tcp_probe.c#L77">77</a>         <a href="ident?i=spinlock_t">spinlock_t</a>      <a href="ident?i=lock">lock</a>;
 <a name="L78" href="source/net/ipv4/tcp_probe.c#L78">78</a>         <a href="ident?i=wait_queue_head_t">wait_queue_head_t</a> <a href="ident?i=wait">wait</a>;
 <a name="L79" href="source/net/ipv4/tcp_probe.c#L79">79</a>         <a href="ident?i=ktime_t">ktime_t</a>         <a href="ident?i=start">start</a>;
 <a name="L80" href="source/net/ipv4/tcp_probe.c#L80">80</a>         <a href="ident?i=u32">u32</a>             lastcwnd;
 <a name="L81" href="source/net/ipv4/tcp_probe.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/tcp_probe.c#L82">82</a>         unsigned long   <a href="ident?i=head">head</a>, <a href="ident?i=tail">tail</a>;
 <a name="L83" href="source/net/ipv4/tcp_probe.c#L83">83</a>         struct <a href="ident?i=tcp_log">tcp_log</a>  *<a href="ident?i=log">log</a>;
 <a name="L84" href="source/net/ipv4/tcp_probe.c#L84">84</a> } <a href="ident?i=tcp_probe">tcp_probe</a>;
 <a name="L85" href="source/net/ipv4/tcp_probe.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/tcp_probe.c#L86">86</a> static inline int <a href="ident?i=tcp_probe_used">tcp_probe_used</a>(void)
 <a name="L87" href="source/net/ipv4/tcp_probe.c#L87">87</a> {
 <a name="L88" href="source/net/ipv4/tcp_probe.c#L88">88</a>         return (<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=head">head</a> - <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=tail">tail</a>) &amp; (<a href="ident?i=bufsize">bufsize</a> - 1);
 <a name="L89" href="source/net/ipv4/tcp_probe.c#L89">89</a> }
 <a name="L90" href="source/net/ipv4/tcp_probe.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_probe.c#L91">91</a> static inline int <a href="ident?i=tcp_probe_avail">tcp_probe_avail</a>(void)
 <a name="L92" href="source/net/ipv4/tcp_probe.c#L92">92</a> {
 <a name="L93" href="source/net/ipv4/tcp_probe.c#L93">93</a>         return <a href="ident?i=bufsize">bufsize</a> - <a href="ident?i=tcp_probe_used">tcp_probe_used</a>() - 1;
 <a name="L94" href="source/net/ipv4/tcp_probe.c#L94">94</a> }
 <a name="L95" href="source/net/ipv4/tcp_probe.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/tcp_probe.c#L96">96</a> #define <a href="ident?i=tcp_probe_copy_fl_to_si4">tcp_probe_copy_fl_to_si4</a>(inet, si4, <a href="ident?i=mem">mem</a>)                \
 <a name="L97" href="source/net/ipv4/tcp_probe.c#L97">97</a>         do {                                                    \
 <a name="L98" href="source/net/ipv4/tcp_probe.c#L98">98</a>                 si4.sin_family = <a href="ident?i=AF_INET">AF_INET</a>;                       \
 <a name="L99" href="source/net/ipv4/tcp_probe.c#L99">99</a>                 si4.sin_port = inet-&gt;inet_##mem##port;          \
<a name="L100" href="source/net/ipv4/tcp_probe.c#L100">100</a>                 si4.sin_addr.s_addr = inet-&gt;inet_##mem##addr;   \
<a name="L101" href="source/net/ipv4/tcp_probe.c#L101">101</a>         } while (0)                                             \
<a name="L102" href="source/net/ipv4/tcp_probe.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/tcp_probe.c#L103">103</a> <b><i>/*</i></b>
<a name="L104" href="source/net/ipv4/tcp_probe.c#L104">104</a> <b><i> * Hook inserted to be called before each receive packet.</i></b>
<a name="L105" href="source/net/ipv4/tcp_probe.c#L105">105</a> <b><i> * Note: arguments must match tcp_rcv_established()!</i></b>
<a name="L106" href="source/net/ipv4/tcp_probe.c#L106">106</a> <b><i> */</i></b>
<a name="L107" href="source/net/ipv4/tcp_probe.c#L107">107</a> static void jtcp_rcv_established(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L108" href="source/net/ipv4/tcp_probe.c#L108">108</a>                                  const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L109" href="source/net/ipv4/tcp_probe.c#L109">109</a> {
<a name="L110" href="source/net/ipv4/tcp_probe.c#L110">110</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L111" href="source/net/ipv4/tcp_probe.c#L111">111</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L112" href="source/net/ipv4/tcp_probe.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/tcp_probe.c#L113">113</a>         <b><i>/* Only update if port or skb mark matches */</i></b>
<a name="L114" href="source/net/ipv4/tcp_probe.c#L114">114</a>         if (((<a href="ident?i=port">port</a> == 0 &amp;&amp; fwmark == 0) ||
<a name="L115" href="source/net/ipv4/tcp_probe.c#L115">115</a>              <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>) == <a href="ident?i=port">port</a> ||
<a name="L116" href="source/net/ipv4/tcp_probe.c#L116">116</a>              <a href="ident?i=ntohs">ntohs</a>(inet-&gt;inet_sport) == <a href="ident?i=port">port</a> ||
<a name="L117" href="source/net/ipv4/tcp_probe.c#L117">117</a>              (fwmark &gt; 0 &amp;&amp; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> == fwmark)) &amp;&amp;
<a name="L118" href="source/net/ipv4/tcp_probe.c#L118">118</a>             (full || <a href="ident?i=tp">tp</a>-&gt;snd_cwnd != <a href="ident?i=tcp_probe">tcp_probe</a>.lastcwnd)) {
<a name="L119" href="source/net/ipv4/tcp_probe.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tcp_probe.c#L120">120</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L121" href="source/net/ipv4/tcp_probe.c#L121">121</a>                 <b><i>/* If log fills, just silently drop */</i></b>
<a name="L122" href="source/net/ipv4/tcp_probe.c#L122">122</a>                 if (<a href="ident?i=tcp_probe_avail">tcp_probe_avail</a>() &gt; 1) {
<a name="L123" href="source/net/ipv4/tcp_probe.c#L123">123</a>                         struct <a href="ident?i=tcp_log">tcp_log</a> *<a href="ident?i=p">p</a> = <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=log">log</a> + <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=head">head</a>;
<a name="L124" href="source/net/ipv4/tcp_probe.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/tcp_probe.c#L125">125</a>                         <a href="ident?i=p">p</a>-&gt;tstamp = <a href="ident?i=ktime_get">ktime_get</a>();
<a name="L126" href="source/net/ipv4/tcp_probe.c#L126">126</a>                         switch (sk-&gt;<a href="ident?i=sk_family">sk_family</a>) {
<a name="L127" href="source/net/ipv4/tcp_probe.c#L127">127</a>                         case <a href="ident?i=AF_INET">AF_INET</a>:
<a name="L128" href="source/net/ipv4/tcp_probe.c#L128">128</a>                                 <a href="ident?i=tcp_probe_copy_fl_to_si4">tcp_probe_copy_fl_to_si4</a>(inet, <a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>.<a href="ident?i=v4">v4</a>, <a href="ident?i=s">s</a>);
<a name="L129" href="source/net/ipv4/tcp_probe.c#L129">129</a>                                 <a href="ident?i=tcp_probe_copy_fl_to_si4">tcp_probe_copy_fl_to_si4</a>(inet, <a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=v4">v4</a>, <a href="ident?i=d">d</a>);
<a name="L130" href="source/net/ipv4/tcp_probe.c#L130">130</a>                                 break;
<a name="L131" href="source/net/ipv4/tcp_probe.c#L131">131</a>                         case <a href="ident?i=AF_INET6">AF_INET6</a>:
<a name="L132" href="source/net/ipv4/tcp_probe.c#L132">132</a>                                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>.<a href="ident?i=v6">v6</a>, 0, sizeof(<a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>.<a href="ident?i=v6">v6</a>));
<a name="L133" href="source/net/ipv4/tcp_probe.c#L133">133</a>                                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=v6">v6</a>, 0, sizeof(<a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=v6">v6</a>));
<a name="L134" href="source/net/ipv4/tcp_probe.c#L134">134</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L135" href="source/net/ipv4/tcp_probe.c#L135">135</a>                                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>.<a href="ident?i=v6">v6</a>.sin6_family = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L136" href="source/net/ipv4/tcp_probe.c#L136">136</a>                                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>.<a href="ident?i=v6">v6</a>.sin6_port = inet-&gt;inet_sport;
<a name="L137" href="source/net/ipv4/tcp_probe.c#L137">137</a>                                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>.<a href="ident?i=v6">v6</a>.sin6_addr = <a href="ident?i=inet6_sk">inet6_sk</a>(sk)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L138" href="source/net/ipv4/tcp_probe.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/tcp_probe.c#L139">139</a>                                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=v6">v6</a>.sin6_family = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L140" href="source/net/ipv4/tcp_probe.c#L140">140</a>                                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=v6">v6</a>.sin6_port = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L141" href="source/net/ipv4/tcp_probe.c#L141">141</a>                                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=v6">v6</a>.sin6_addr = sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>;
<a name="L142" href="source/net/ipv4/tcp_probe.c#L142">142</a> #endif
<a name="L143" href="source/net/ipv4/tcp_probe.c#L143">143</a>                                 break;
<a name="L144" href="source/net/ipv4/tcp_probe.c#L144">144</a>                         default:
<a name="L145" href="source/net/ipv4/tcp_probe.c#L145">145</a>                                 <a href="ident?i=BUG">BUG</a>();
<a name="L146" href="source/net/ipv4/tcp_probe.c#L146">146</a>                         }
<a name="L147" href="source/net/ipv4/tcp_probe.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/tcp_probe.c#L148">148</a>                         <a href="ident?i=p">p</a>-&gt;<a href="ident?i=length">length</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L149" href="source/net/ipv4/tcp_probe.c#L149">149</a>                         <a href="ident?i=p">p</a>-&gt;snd_nxt = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L150" href="source/net/ipv4/tcp_probe.c#L150">150</a>                         <a href="ident?i=p">p</a>-&gt;snd_una = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L151" href="source/net/ipv4/tcp_probe.c#L151">151</a>                         <a href="ident?i=p">p</a>-&gt;snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L152" href="source/net/ipv4/tcp_probe.c#L152">152</a>                         <a href="ident?i=p">p</a>-&gt;snd_wnd = <a href="ident?i=tp">tp</a>-&gt;snd_wnd;
<a name="L153" href="source/net/ipv4/tcp_probe.c#L153">153</a>                         <a href="ident?i=p">p</a>-&gt;rcv_wnd = <a href="ident?i=tp">tp</a>-&gt;rcv_wnd;
<a name="L154" href="source/net/ipv4/tcp_probe.c#L154">154</a>                         <a href="ident?i=p">p</a>-&gt;ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L155" href="source/net/ipv4/tcp_probe.c#L155">155</a>                         <a href="ident?i=p">p</a>-&gt;srtt = <a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 3;
<a name="L156" href="source/net/ipv4/tcp_probe.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/tcp_probe.c#L157">157</a>                         <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=head">head</a> = (<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=head">head</a> + 1) &amp; (<a href="ident?i=bufsize">bufsize</a> - 1);
<a name="L158" href="source/net/ipv4/tcp_probe.c#L158">158</a>                 }
<a name="L159" href="source/net/ipv4/tcp_probe.c#L159">159</a>                 <a href="ident?i=tcp_probe">tcp_probe</a>.lastcwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L160" href="source/net/ipv4/tcp_probe.c#L160">160</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L161" href="source/net/ipv4/tcp_probe.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/tcp_probe.c#L162">162</a>                 <a href="ident?i=wake_up">wake_up</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=wait">wait</a>);
<a name="L163" href="source/net/ipv4/tcp_probe.c#L163">163</a>         }
<a name="L164" href="source/net/ipv4/tcp_probe.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/tcp_probe.c#L165">165</a>         <a href="ident?i=jprobe_return">jprobe_return</a>();
<a name="L166" href="source/net/ipv4/tcp_probe.c#L166">166</a> }
<a name="L167" href="source/net/ipv4/tcp_probe.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/tcp_probe.c#L168">168</a> static struct <a href="ident?i=jprobe">jprobe</a> <a href="ident?i=tcp_jprobe">tcp_jprobe</a> = {
<a name="L169" href="source/net/ipv4/tcp_probe.c#L169">169</a>         .<a href="ident?i=kp">kp</a> = {
<a name="L170" href="source/net/ipv4/tcp_probe.c#L170">170</a>                 .symbol_name    = <i>"tcp_rcv_established"</i>,
<a name="L171" href="source/net/ipv4/tcp_probe.c#L171">171</a>         },
<a name="L172" href="source/net/ipv4/tcp_probe.c#L172">172</a>         .<a href="ident?i=entry">entry</a>  = jtcp_rcv_established,
<a name="L173" href="source/net/ipv4/tcp_probe.c#L173">173</a> };
<a name="L174" href="source/net/ipv4/tcp_probe.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/tcp_probe.c#L175">175</a> static int <a href="ident?i=tcpprobe_open">tcpprobe_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L176" href="source/net/ipv4/tcp_probe.c#L176">176</a> {
<a name="L177" href="source/net/ipv4/tcp_probe.c#L177">177</a>         <b><i>/* Reset (empty) log */</i></b>
<a name="L178" href="source/net/ipv4/tcp_probe.c#L178">178</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L179" href="source/net/ipv4/tcp_probe.c#L179">179</a>         <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=head">head</a> = <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=tail">tail</a> = 0;
<a name="L180" href="source/net/ipv4/tcp_probe.c#L180">180</a>         <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=start">start</a> = <a href="ident?i=ktime_get">ktime_get</a>();
<a name="L181" href="source/net/ipv4/tcp_probe.c#L181">181</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L182" href="source/net/ipv4/tcp_probe.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_probe.c#L183">183</a>         return 0;
<a name="L184" href="source/net/ipv4/tcp_probe.c#L184">184</a> }
<a name="L185" href="source/net/ipv4/tcp_probe.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/tcp_probe.c#L186">186</a> static int <a href="ident?i=tcpprobe_sprint">tcpprobe_sprint</a>(char *tbuf, int <a href="ident?i=n">n</a>)
<a name="L187" href="source/net/ipv4/tcp_probe.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/tcp_probe.c#L188">188</a>         const struct <a href="ident?i=tcp_log">tcp_log</a> *<a href="ident?i=p">p</a>
<a name="L189" href="source/net/ipv4/tcp_probe.c#L189">189</a>                 = <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=log">log</a> + <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=tail">tail</a>;
<a name="L190" href="source/net/ipv4/tcp_probe.c#L190">190</a>         struct <a href="ident?i=timespec">timespec</a> tv
<a name="L191" href="source/net/ipv4/tcp_probe.c#L191">191</a>                 = <a href="ident?i=ktime_to_timespec">ktime_to_timespec</a>(<a href="ident?i=ktime_sub">ktime_sub</a>(<a href="ident?i=p">p</a>-&gt;tstamp, <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=start">start</a>));
<a name="L192" href="source/net/ipv4/tcp_probe.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/tcp_probe.c#L193">193</a>         return <a href="ident?i=scnprintf">scnprintf</a>(tbuf, <a href="ident?i=n">n</a>,
<a name="L194" href="source/net/ipv4/tcp_probe.c#L194">194</a>                         <i>"%lu.%09lu %pISpc %pISpc %d %#x %#x %u %u %u %u %u\n"</i>,
<a name="L195" href="source/net/ipv4/tcp_probe.c#L195">195</a>                         (unsigned long)tv.tv_sec,
<a name="L196" href="source/net/ipv4/tcp_probe.c#L196">196</a>                         (unsigned long)tv.tv_nsec,
<a name="L197" href="source/net/ipv4/tcp_probe.c#L197">197</a>                         &amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=src">src</a>, &amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=dst">dst</a>, <a href="ident?i=p">p</a>-&gt;<a href="ident?i=length">length</a>, <a href="ident?i=p">p</a>-&gt;snd_nxt, <a href="ident?i=p">p</a>-&gt;snd_una,
<a name="L198" href="source/net/ipv4/tcp_probe.c#L198">198</a>                         <a href="ident?i=p">p</a>-&gt;snd_cwnd, <a href="ident?i=p">p</a>-&gt;ssthresh, <a href="ident?i=p">p</a>-&gt;snd_wnd, <a href="ident?i=p">p</a>-&gt;srtt, <a href="ident?i=p">p</a>-&gt;rcv_wnd);
<a name="L199" href="source/net/ipv4/tcp_probe.c#L199">199</a> }
<a name="L200" href="source/net/ipv4/tcp_probe.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/tcp_probe.c#L201">201</a> static <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=tcpprobe_read">tcpprobe_read</a>(struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>, char <a href="ident?i=__user">__user</a> *<a href="ident?i=buf">buf</a>,
<a name="L202" href="source/net/ipv4/tcp_probe.c#L202">202</a>                              <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L203" href="source/net/ipv4/tcp_probe.c#L203">203</a> {
<a name="L204" href="source/net/ipv4/tcp_probe.c#L204">204</a>         int <a href="ident?i=error">error</a> = 0;
<a name="L205" href="source/net/ipv4/tcp_probe.c#L205">205</a>         <a href="ident?i=size_t">size_t</a> cnt = 0;
<a name="L206" href="source/net/ipv4/tcp_probe.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/tcp_probe.c#L207">207</a>         if (!<a href="ident?i=buf">buf</a>)
<a name="L208" href="source/net/ipv4/tcp_probe.c#L208">208</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L209" href="source/net/ipv4/tcp_probe.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/tcp_probe.c#L210">210</a>         while (cnt &lt; <a href="ident?i=len">len</a>) {
<a name="L211" href="source/net/ipv4/tcp_probe.c#L211">211</a>                 char tbuf[256];
<a name="L212" href="source/net/ipv4/tcp_probe.c#L212">212</a>                 int <a href="ident?i=width">width</a>;
<a name="L213" href="source/net/ipv4/tcp_probe.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/tcp_probe.c#L214">214</a>                 <b><i>/* Wait for data in buffer */</i></b>
<a name="L215" href="source/net/ipv4/tcp_probe.c#L215">215</a>                 <a href="ident?i=error">error</a> = <a href="ident?i=wait_event_interruptible">wait_event_interruptible</a>(<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=wait">wait</a>,
<a name="L216" href="source/net/ipv4/tcp_probe.c#L216">216</a>                                                  <a href="ident?i=tcp_probe_used">tcp_probe_used</a>() &gt; 0);
<a name="L217" href="source/net/ipv4/tcp_probe.c#L217">217</a>                 if (<a href="ident?i=error">error</a>)
<a name="L218" href="source/net/ipv4/tcp_probe.c#L218">218</a>                         break;
<a name="L219" href="source/net/ipv4/tcp_probe.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/tcp_probe.c#L220">220</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L221" href="source/net/ipv4/tcp_probe.c#L221">221</a>                 if (<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=head">head</a> == <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=tail">tail</a>) {
<a name="L222" href="source/net/ipv4/tcp_probe.c#L222">222</a>                         <b><i>/* multiple readers race? */</i></b>
<a name="L223" href="source/net/ipv4/tcp_probe.c#L223">223</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L224" href="source/net/ipv4/tcp_probe.c#L224">224</a>                         continue;
<a name="L225" href="source/net/ipv4/tcp_probe.c#L225">225</a>                 }
<a name="L226" href="source/net/ipv4/tcp_probe.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/tcp_probe.c#L227">227</a>                 <a href="ident?i=width">width</a> = <a href="ident?i=tcpprobe_sprint">tcpprobe_sprint</a>(tbuf, sizeof(tbuf));
<a name="L228" href="source/net/ipv4/tcp_probe.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/tcp_probe.c#L229">229</a>                 if (cnt + <a href="ident?i=width">width</a> &lt; <a href="ident?i=len">len</a>)
<a name="L230" href="source/net/ipv4/tcp_probe.c#L230">230</a>                         <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=tail">tail</a> = (<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=tail">tail</a> + 1) &amp; (<a href="ident?i=bufsize">bufsize</a> - 1);
<a name="L231" href="source/net/ipv4/tcp_probe.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/tcp_probe.c#L232">232</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L233" href="source/net/ipv4/tcp_probe.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_probe.c#L234">234</a>                 <b><i>/* if record greater than space available</i></b>
<a name="L235" href="source/net/ipv4/tcp_probe.c#L235">235</a> <b><i>                   return partial buffer (so far) */</i></b>
<a name="L236" href="source/net/ipv4/tcp_probe.c#L236">236</a>                 if (cnt + <a href="ident?i=width">width</a> &gt;= <a href="ident?i=len">len</a>)
<a name="L237" href="source/net/ipv4/tcp_probe.c#L237">237</a>                         break;
<a name="L238" href="source/net/ipv4/tcp_probe.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/tcp_probe.c#L239">239</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=buf">buf</a> + cnt, tbuf, <a href="ident?i=width">width</a>))
<a name="L240" href="source/net/ipv4/tcp_probe.c#L240">240</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L241" href="source/net/ipv4/tcp_probe.c#L241">241</a>                 cnt += <a href="ident?i=width">width</a>;
<a name="L242" href="source/net/ipv4/tcp_probe.c#L242">242</a>         }
<a name="L243" href="source/net/ipv4/tcp_probe.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/tcp_probe.c#L244">244</a>         return cnt == 0 ? <a href="ident?i=error">error</a> : cnt;
<a name="L245" href="source/net/ipv4/tcp_probe.c#L245">245</a> }
<a name="L246" href="source/net/ipv4/tcp_probe.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/tcp_probe.c#L247">247</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=tcpprobe_fops">tcpprobe_fops</a> = {
<a name="L248" href="source/net/ipv4/tcp_probe.c#L248">248</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L249" href="source/net/ipv4/tcp_probe.c#L249">249</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=tcpprobe_open">tcpprobe_open</a>,
<a name="L250" href="source/net/ipv4/tcp_probe.c#L250">250</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=tcpprobe_read">tcpprobe_read</a>,
<a name="L251" href="source/net/ipv4/tcp_probe.c#L251">251</a>         .llseek  = <a href="ident?i=noop_llseek">noop_llseek</a>,
<a name="L252" href="source/net/ipv4/tcp_probe.c#L252">252</a> };
<a name="L253" href="source/net/ipv4/tcp_probe.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/tcp_probe.c#L254">254</a> static <a href="ident?i=__init">__init</a> int <a href="ident?i=tcpprobe_init">tcpprobe_init</a>(void)
<a name="L255" href="source/net/ipv4/tcp_probe.c#L255">255</a> {
<a name="L256" href="source/net/ipv4/tcp_probe.c#L256">256</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L257" href="source/net/ipv4/tcp_probe.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/tcp_probe.c#L258">258</a>         <b><i>/* Warning: if the function signature of tcp_rcv_established,</i></b>
<a name="L259" href="source/net/ipv4/tcp_probe.c#L259">259</a> <b><i>         * has been changed, you also have to change the signature of</i></b>
<a name="L260" href="source/net/ipv4/tcp_probe.c#L260">260</a> <b><i>         * jtcp_rcv_established, otherwise you end up right here!</i></b>
<a name="L261" href="source/net/ipv4/tcp_probe.c#L261">261</a> <b><i>         */</i></b>
<a name="L262" href="source/net/ipv4/tcp_probe.c#L262">262</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=__same_type">__same_type</a>(<a href="ident?i=tcp_rcv_established">tcp_rcv_established</a>,
<a name="L263" href="source/net/ipv4/tcp_probe.c#L263">263</a>                                  jtcp_rcv_established) == 0);
<a name="L264" href="source/net/ipv4/tcp_probe.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/tcp_probe.c#L265">265</a>         <a href="ident?i=init_waitqueue_head">init_waitqueue_head</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=wait">wait</a>);
<a name="L266" href="source/net/ipv4/tcp_probe.c#L266">266</a>         <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=lock">lock</a>);
<a name="L267" href="source/net/ipv4/tcp_probe.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/tcp_probe.c#L268">268</a>         if (<a href="ident?i=bufsize">bufsize</a> == 0)
<a name="L269" href="source/net/ipv4/tcp_probe.c#L269">269</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L270" href="source/net/ipv4/tcp_probe.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/tcp_probe.c#L271">271</a>         <a href="ident?i=bufsize">bufsize</a> = <a href="ident?i=roundup_pow_of_two">roundup_pow_of_two</a>(<a href="ident?i=bufsize">bufsize</a>);
<a name="L272" href="source/net/ipv4/tcp_probe.c#L272">272</a>         <a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=log">log</a> = <a href="ident?i=kcalloc">kcalloc</a>(<a href="ident?i=bufsize">bufsize</a>, sizeof(struct <a href="ident?i=tcp_log">tcp_log</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L273" href="source/net/ipv4/tcp_probe.c#L273">273</a>         if (!<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=log">log</a>)
<a name="L274" href="source/net/ipv4/tcp_probe.c#L274">274</a>                 goto err0;
<a name="L275" href="source/net/ipv4/tcp_probe.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/tcp_probe.c#L276">276</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<a href="ident?i=procname">procname</a>, <a href="ident?i=S_IRUSR">S_IRUSR</a>, <a href="ident?i=init_net">init_net</a>.proc_net, &amp;<a href="ident?i=tcpprobe_fops">tcpprobe_fops</a>))
<a name="L277" href="source/net/ipv4/tcp_probe.c#L277">277</a>                 goto err0;
<a name="L278" href="source/net/ipv4/tcp_probe.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/tcp_probe.c#L279">279</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_jprobe">register_jprobe</a>(&amp;<a href="ident?i=tcp_jprobe">tcp_jprobe</a>);
<a name="L280" href="source/net/ipv4/tcp_probe.c#L280">280</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L281" href="source/net/ipv4/tcp_probe.c#L281">281</a>                 goto err1;
<a name="L282" href="source/net/ipv4/tcp_probe.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/tcp_probe.c#L283">283</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"probe registered (port=%d/fwmark=%u) bufsize=%u\n"</i>,
<a name="L284" href="source/net/ipv4/tcp_probe.c#L284">284</a>                 <a href="ident?i=port">port</a>, fwmark, <a href="ident?i=bufsize">bufsize</a>);
<a name="L285" href="source/net/ipv4/tcp_probe.c#L285">285</a>         return 0;
<a name="L286" href="source/net/ipv4/tcp_probe.c#L286">286</a>  err1:
<a name="L287" href="source/net/ipv4/tcp_probe.c#L287">287</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<a href="ident?i=procname">procname</a>, <a href="ident?i=init_net">init_net</a>.proc_net);
<a name="L288" href="source/net/ipv4/tcp_probe.c#L288">288</a>  err0:
<a name="L289" href="source/net/ipv4/tcp_probe.c#L289">289</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=log">log</a>);
<a name="L290" href="source/net/ipv4/tcp_probe.c#L290">290</a>         return <a href="ident?i=ret">ret</a>;
<a name="L291" href="source/net/ipv4/tcp_probe.c#L291">291</a> }
<a name="L292" href="source/net/ipv4/tcp_probe.c#L292">292</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcpprobe_init">tcpprobe_init</a>);
<a name="L293" href="source/net/ipv4/tcp_probe.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/tcp_probe.c#L294">294</a> static <a href="ident?i=__exit">__exit</a> void <a href="ident?i=tcpprobe_exit">tcpprobe_exit</a>(void)
<a name="L295" href="source/net/ipv4/tcp_probe.c#L295">295</a> {
<a name="L296" href="source/net/ipv4/tcp_probe.c#L296">296</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<a href="ident?i=procname">procname</a>, <a href="ident?i=init_net">init_net</a>.proc_net);
<a name="L297" href="source/net/ipv4/tcp_probe.c#L297">297</a>         <a href="ident?i=unregister_jprobe">unregister_jprobe</a>(&amp;<a href="ident?i=tcp_jprobe">tcp_jprobe</a>);
<a name="L298" href="source/net/ipv4/tcp_probe.c#L298">298</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tcp_probe">tcp_probe</a>.<a href="ident?i=log">log</a>);
<a name="L299" href="source/net/ipv4/tcp_probe.c#L299">299</a> }
<a name="L300" href="source/net/ipv4/tcp_probe.c#L300">300</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcpprobe_exit">tcpprobe_exit</a>);
<a name="L301" href="source/net/ipv4/tcp_probe.c#L301">301</a> </pre></div><p>
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
