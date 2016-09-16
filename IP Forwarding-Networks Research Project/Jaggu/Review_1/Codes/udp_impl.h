<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/udp_impl.h - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/udp_impl.h">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/udp_impl.h?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/udp_impl.h?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/udp_impl.h">udp_impl.h</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/udp_impl.h#L1">1</a> #ifndef <a href="ident?i=_UDP4_IMPL_H">_UDP4_IMPL_H</a>
  <a name="L2" href="source/net/ipv4/udp_impl.h#L2">2</a> #define <a href="ident?i=_UDP4_IMPL_H">_UDP4_IMPL_H</a>
  <a name="L3" href="source/net/ipv4/udp_impl.h#L3">3</a> #include &lt;net/udp.h&gt;
  <a name="L4" href="source/net/ipv4/udp_impl.h#L4">4</a> #include &lt;net/udplite.h&gt;
  <a name="L5" href="source/net/ipv4/udp_impl.h#L5">5</a> #include &lt;net/protocol.h&gt;
  <a name="L6" href="source/net/ipv4/udp_impl.h#L6">6</a> #include &lt;net/inet_common.h&gt;
  <a name="L7" href="source/net/ipv4/udp_impl.h#L7">7</a> 
  <a name="L8" href="source/net/ipv4/udp_impl.h#L8">8</a> int <a href="ident?i=__udp4_lib_rcv">__udp4_lib_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *, struct <a href="ident?i=udp_table">udp_table</a> *, int);
  <a name="L9" href="source/net/ipv4/udp_impl.h#L9">9</a> void <a href="ident?i=__udp4_lib_err">__udp4_lib_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *, <a href="ident?i=u32">u32</a>, struct <a href="ident?i=udp_table">udp_table</a> *);
 <a name="L10" href="source/net/ipv4/udp_impl.h#L10">10</a> 
 <a name="L11" href="source/net/ipv4/udp_impl.h#L11">11</a> int <a href="ident?i=udp_v4_get_port">udp_v4_get_port</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned short snum);
 <a name="L12" href="source/net/ipv4/udp_impl.h#L12">12</a> 
 <a name="L13" href="source/net/ipv4/udp_impl.h#L13">13</a> int <a href="ident?i=udp_setsockopt">udp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
 <a name="L14" href="source/net/ipv4/udp_impl.h#L14">14</a>                    char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>);
 <a name="L15" href="source/net/ipv4/udp_impl.h#L15">15</a> int <a href="ident?i=udp_getsockopt">udp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
 <a name="L16" href="source/net/ipv4/udp_impl.h#L16">16</a>                    char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>);
 <a name="L17" href="source/net/ipv4/udp_impl.h#L17">17</a> 
 <a name="L18" href="source/net/ipv4/udp_impl.h#L18">18</a> #ifdef CONFIG_COMPAT
 <a name="L19" href="source/net/ipv4/udp_impl.h#L19">19</a> int <a href="ident?i=compat_udp_setsockopt">compat_udp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
 <a name="L20" href="source/net/ipv4/udp_impl.h#L20">20</a>                           char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>);
 <a name="L21" href="source/net/ipv4/udp_impl.h#L21">21</a> int <a href="ident?i=compat_udp_getsockopt">compat_udp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
 <a name="L22" href="source/net/ipv4/udp_impl.h#L22">22</a>                           char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>);
 <a name="L23" href="source/net/ipv4/udp_impl.h#L23">23</a> #endif
 <a name="L24" href="source/net/ipv4/udp_impl.h#L24">24</a> int <a href="ident?i=udp_recvmsg">udp_recvmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, int noblock,
 <a name="L25" href="source/net/ipv4/udp_impl.h#L25">25</a>                 int <a href="ident?i=flags">flags</a>, int *addr_len);
 <a name="L26" href="source/net/ipv4/udp_impl.h#L26">26</a> int <a href="ident?i=udp_sendpage">udp_sendpage</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>, int <a href="ident?i=offset">offset</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>,
 <a name="L27" href="source/net/ipv4/udp_impl.h#L27">27</a>                  int <a href="ident?i=flags">flags</a>);
 <a name="L28" href="source/net/ipv4/udp_impl.h#L28">28</a> int <a href="ident?i=udp_queue_rcv_skb">udp_queue_rcv_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
 <a name="L29" href="source/net/ipv4/udp_impl.h#L29">29</a> void <a href="ident?i=udp_destroy_sock">udp_destroy_sock</a>(struct <a href="ident?i=sock">sock</a> *sk);
 <a name="L30" href="source/net/ipv4/udp_impl.h#L30">30</a> 
 <a name="L31" href="source/net/ipv4/udp_impl.h#L31">31</a> #ifdef CONFIG_PROC_FS
 <a name="L32" href="source/net/ipv4/udp_impl.h#L32">32</a> int <a href="ident?i=udp4_seq_show">udp4_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>);
 <a name="L33" href="source/net/ipv4/udp_impl.h#L33">33</a> #endif
 <a name="L34" href="source/net/ipv4/udp_impl.h#L34">34</a> #endif  <b><i>/* _UDP4_IMPL_H */</i></b>
 <a name="L35" href="source/net/ipv4/udp_impl.h#L35">35</a> </pre></div><p>
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
