<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_vegas.h - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_vegas.h">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.h?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_vegas.h">tcp_vegas.h</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_vegas.h#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_vegas.h#L2">2</a> <b><i> * TCP Vegas congestion control interface</i></b>
  <a name="L3" href="source/net/ipv4/tcp_vegas.h#L3">3</a> <b><i> */</i></b>
  <a name="L4" href="source/net/ipv4/tcp_vegas.h#L4">4</a> #ifndef <a href="ident?i=__TCP_VEGAS_H">__TCP_VEGAS_H</a>
  <a name="L5" href="source/net/ipv4/tcp_vegas.h#L5">5</a> #define <a href="ident?i=__TCP_VEGAS_H">__TCP_VEGAS_H</a> 1
  <a name="L6" href="source/net/ipv4/tcp_vegas.h#L6">6</a> 
  <a name="L7" href="source/net/ipv4/tcp_vegas.h#L7">7</a> <b><i>/* Vegas variables */</i></b>
  <a name="L8" href="source/net/ipv4/tcp_vegas.h#L8">8</a> struct <a href="ident?i=vegas">vegas</a> {
  <a name="L9" href="source/net/ipv4/tcp_vegas.h#L9">9</a>         <a href="ident?i=u32">u32</a>     beg_snd_nxt;    <b><i>/* right edge during last RTT */</i></b>
 <a name="L10" href="source/net/ipv4/tcp_vegas.h#L10">10</a>         <a href="ident?i=u32">u32</a>     beg_snd_una;    <b><i>/* left edge  during last RTT */</i></b>
 <a name="L11" href="source/net/ipv4/tcp_vegas.h#L11">11</a>         <a href="ident?i=u32">u32</a>     beg_snd_cwnd;   <b><i>/* saves the size of the cwnd */</i></b>
 <a name="L12" href="source/net/ipv4/tcp_vegas.h#L12">12</a>         <a href="ident?i=u8">u8</a>      doing_vegas_now;<b><i>/* if true, do vegas for this RTT */</i></b>
 <a name="L13" href="source/net/ipv4/tcp_vegas.h#L13">13</a>         <a href="ident?i=u16">u16</a>     cntRTT;         <b><i>/* # of RTTs measured within last RTT */</i></b>
 <a name="L14" href="source/net/ipv4/tcp_vegas.h#L14">14</a>         <a href="ident?i=u32">u32</a>     minRTT;         <b><i>/* min of RTTs measured within last RTT (in usec) */</i></b>
 <a name="L15" href="source/net/ipv4/tcp_vegas.h#L15">15</a>         <a href="ident?i=u32">u32</a>     baseRTT;        <b><i>/* the min of all Vegas RTT measurements seen (in usec) */</i></b>
 <a name="L16" href="source/net/ipv4/tcp_vegas.h#L16">16</a> };
 <a name="L17" href="source/net/ipv4/tcp_vegas.h#L17">17</a> 
 <a name="L18" href="source/net/ipv4/tcp_vegas.h#L18">18</a> void <a href="ident?i=tcp_vegas_init">tcp_vegas_init</a>(struct <a href="ident?i=sock">sock</a> *sk);
 <a name="L19" href="source/net/ipv4/tcp_vegas.h#L19">19</a> void <a href="ident?i=tcp_vegas_state">tcp_vegas_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> ca_state);
 <a name="L20" href="source/net/ipv4/tcp_vegas.h#L20">20</a> void <a href="ident?i=tcp_vegas_pkts_acked">tcp_vegas_pkts_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> cnt, <a href="ident?i=s32">s32</a> rtt_us);
 <a name="L21" href="source/net/ipv4/tcp_vegas.h#L21">21</a> void <a href="ident?i=tcp_vegas_cwnd_event">tcp_vegas_cwnd_event</a>(struct <a href="ident?i=sock">sock</a> *sk, enum <a href="ident?i=tcp_ca_event">tcp_ca_event</a> <a href="ident?i=event">event</a>);
 <a name="L22" href="source/net/ipv4/tcp_vegas.h#L22">22</a> <a href="ident?i=size_t">size_t</a> <a href="ident?i=tcp_vegas_get_info">tcp_vegas_get_info</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ext, int *<a href="ident?i=attr">attr</a>,
 <a name="L23" href="source/net/ipv4/tcp_vegas.h#L23">23</a>                           union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> *<a href="ident?i=info">info</a>);
 <a name="L24" href="source/net/ipv4/tcp_vegas.h#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_vegas.h#L25">25</a> #endif  <b><i>/* __TCP_VEGAS_H */</i></b>
 <a name="L26" href="source/net/ipv4/tcp_vegas.h#L26">26</a> </pre></div><p>
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
