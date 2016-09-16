<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_diag.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_diag.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_diag.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_diag.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_diag.c">tcp_diag.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_diag.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_diag.c#L2">2</a> <b><i> * tcp_diag.c   Module for monitoring TCP transport protocols sockets.</i></b>
  <a name="L3" href="source/net/ipv4/tcp_diag.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_diag.c#L4">4</a> <b><i> * Authors:     Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
  <a name="L5" href="source/net/ipv4/tcp_diag.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_diag.c#L6">6</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/tcp_diag.c#L7">7</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/tcp_diag.c#L8">8</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/tcp_diag.c#L9">9</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/tcp_diag.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/tcp_diag.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/tcp_diag.c#L12">12</a> #include &lt;linux/module.h&gt;
 <a name="L13" href="source/net/ipv4/tcp_diag.c#L13">13</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L14" href="source/net/ipv4/tcp_diag.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/tcp_diag.c#L15">15</a> #include &lt;linux/tcp.h&gt;
 <a name="L16" href="source/net/ipv4/tcp_diag.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/tcp_diag.c#L17">17</a> #include &lt;net/tcp.h&gt;
 <a name="L18" href="source/net/ipv4/tcp_diag.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/tcp_diag.c#L19">19</a> static void <a href="ident?i=tcp_diag_get_info">tcp_diag_get_info</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a> *<a href="ident?i=r">r</a>,
 <a name="L20" href="source/net/ipv4/tcp_diag.c#L20">20</a>                               void *_info)
 <a name="L21" href="source/net/ipv4/tcp_diag.c#L21">21</a> {
 <a name="L22" href="source/net/ipv4/tcp_diag.c#L22">22</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L23" href="source/net/ipv4/tcp_diag.c#L23">23</a>         struct <a href="ident?i=tcp_info">tcp_info</a> *<a href="ident?i=info">info</a> = _info;
 <a name="L24" href="source/net/ipv4/tcp_diag.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_diag.c#L25">25</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) {
 <a name="L26" href="source/net/ipv4/tcp_diag.c#L26">26</a>                 <a href="ident?i=r">r</a>-&gt;idiag_rqueue = sk-&gt;sk_ack_backlog;
 <a name="L27" href="source/net/ipv4/tcp_diag.c#L27">27</a>                 <a href="ident?i=r">r</a>-&gt;idiag_wqueue = sk-&gt;sk_max_ack_backlog;
 <a name="L28" href="source/net/ipv4/tcp_diag.c#L28">28</a>         } else {
 <a name="L29" href="source/net/ipv4/tcp_diag.c#L29">29</a>                 <a href="ident?i=r">r</a>-&gt;idiag_rqueue = <a href="ident?i=max_t">max_t</a>(int, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt - <a href="ident?i=tp">tp</a>-&gt;copied_seq, 0);
 <a name="L30" href="source/net/ipv4/tcp_diag.c#L30">30</a>                 <a href="ident?i=r">r</a>-&gt;idiag_wqueue = <a href="ident?i=tp">tp</a>-&gt;write_seq - <a href="ident?i=tp">tp</a>-&gt;snd_una;
 <a name="L31" href="source/net/ipv4/tcp_diag.c#L31">31</a>         }
 <a name="L32" href="source/net/ipv4/tcp_diag.c#L32">32</a>         if (<a href="ident?i=info">info</a>)
 <a name="L33" href="source/net/ipv4/tcp_diag.c#L33">33</a>                 <a href="ident?i=tcp_get_info">tcp_get_info</a>(sk, <a href="ident?i=info">info</a>);
 <a name="L34" href="source/net/ipv4/tcp_diag.c#L34">34</a> }
 <a name="L35" href="source/net/ipv4/tcp_diag.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tcp_diag.c#L36">36</a> static void <a href="ident?i=tcp_diag_dump">tcp_diag_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
 <a name="L37" href="source/net/ipv4/tcp_diag.c#L37">37</a>                           const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
 <a name="L38" href="source/net/ipv4/tcp_diag.c#L38">38</a> {
 <a name="L39" href="source/net/ipv4/tcp_diag.c#L39">39</a>         <a href="ident?i=inet_diag_dump_icsk">inet_diag_dump_icsk</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>);
 <a name="L40" href="source/net/ipv4/tcp_diag.c#L40">40</a> }
 <a name="L41" href="source/net/ipv4/tcp_diag.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/tcp_diag.c#L42">42</a> static int <a href="ident?i=tcp_diag_dump_one">tcp_diag_dump_one</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb, const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
 <a name="L43" href="source/net/ipv4/tcp_diag.c#L43">43</a>                              const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>)
 <a name="L44" href="source/net/ipv4/tcp_diag.c#L44">44</a> {
 <a name="L45" href="source/net/ipv4/tcp_diag.c#L45">45</a>         return <a href="ident?i=inet_diag_dump_one_icsk">inet_diag_dump_one_icsk</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, in_skb, nlh, <a href="ident?i=req">req</a>);
 <a name="L46" href="source/net/ipv4/tcp_diag.c#L46">46</a> }
 <a name="L47" href="source/net/ipv4/tcp_diag.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/tcp_diag.c#L48">48</a> static const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> <a href="ident?i=tcp_diag_handler">tcp_diag_handler</a> = {
 <a name="L49" href="source/net/ipv4/tcp_diag.c#L49">49</a>         .<a href="ident?i=dump">dump</a>            = <a href="ident?i=tcp_diag_dump">tcp_diag_dump</a>,
 <a name="L50" href="source/net/ipv4/tcp_diag.c#L50">50</a>         .dump_one        = <a href="ident?i=tcp_diag_dump_one">tcp_diag_dump_one</a>,
 <a name="L51" href="source/net/ipv4/tcp_diag.c#L51">51</a>         .idiag_get_info  = <a href="ident?i=tcp_diag_get_info">tcp_diag_get_info</a>,
 <a name="L52" href="source/net/ipv4/tcp_diag.c#L52">52</a>         .idiag_type      = <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
 <a name="L53" href="source/net/ipv4/tcp_diag.c#L53">53</a> };
 <a name="L54" href="source/net/ipv4/tcp_diag.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/tcp_diag.c#L55">55</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_diag_init">tcp_diag_init</a>(void)
 <a name="L56" href="source/net/ipv4/tcp_diag.c#L56">56</a> {
 <a name="L57" href="source/net/ipv4/tcp_diag.c#L57">57</a>         return <a href="ident?i=inet_diag_register">inet_diag_register</a>(&amp;<a href="ident?i=tcp_diag_handler">tcp_diag_handler</a>);
 <a name="L58" href="source/net/ipv4/tcp_diag.c#L58">58</a> }
 <a name="L59" href="source/net/ipv4/tcp_diag.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/tcp_diag.c#L60">60</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_diag_exit">tcp_diag_exit</a>(void)
 <a name="L61" href="source/net/ipv4/tcp_diag.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/tcp_diag.c#L62">62</a>         <a href="ident?i=inet_diag_unregister">inet_diag_unregister</a>(&amp;<a href="ident?i=tcp_diag_handler">tcp_diag_handler</a>);
 <a name="L63" href="source/net/ipv4/tcp_diag.c#L63">63</a> }
 <a name="L64" href="source/net/ipv4/tcp_diag.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/tcp_diag.c#L65">65</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_diag_init">tcp_diag_init</a>);
 <a name="L66" href="source/net/ipv4/tcp_diag.c#L66">66</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_diag_exit">tcp_diag_exit</a>);
 <a name="L67" href="source/net/ipv4/tcp_diag.c#L67">67</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L68" href="source/net/ipv4/tcp_diag.c#L68">68</a> <a href="ident?i=MODULE_ALIAS_NET_PF_PROTO_TYPE">MODULE_ALIAS_NET_PF_PROTO_TYPE</a>(<a href="ident?i=PF_NETLINK">PF_NETLINK</a>, <a href="ident?i=NETLINK_SOCK_DIAG">NETLINK_SOCK_DIAG</a>, 2-6 <b><i>/* AF_INET - IPPROTO_TCP */</i></b>);
 <a name="L69" href="source/net/ipv4/tcp_diag.c#L69">69</a> </pre></div><p>
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
