<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/protocol.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/protocol.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/protocol.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/protocol.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/protocol.c">protocol.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/protocol.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/protocol.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/protocol.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/protocol.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/protocol.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/protocol.c#L6">6</a> <b><i> *              INET protocol dispatch tables.</i></b>
  <a name="L7" href="source/net/ipv4/protocol.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/protocol.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/protocol.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/protocol.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/protocol.c#L11">11</a> <b><i> * Fixes:</i></b>
 <a name="L12" href="source/net/ipv4/protocol.c#L12">12</a> <b><i> *              Alan Cox        : Ahah! udp icmp errors don't work because</i></b>
 <a name="L13" href="source/net/ipv4/protocol.c#L13">13</a> <b><i> *                                udp_err is never called!</i></b>
 <a name="L14" href="source/net/ipv4/protocol.c#L14">14</a> <b><i> *              Alan Cox        : Added new fields for init and ready for</i></b>
 <a name="L15" href="source/net/ipv4/protocol.c#L15">15</a> <b><i> *                                proper fragmentation (_NO_ 4K limits!)</i></b>
 <a name="L16" href="source/net/ipv4/protocol.c#L16">16</a> <b><i> *              Richard Colella : Hang on hash collision</i></b>
 <a name="L17" href="source/net/ipv4/protocol.c#L17">17</a> <b><i> *              Vince Laviano   : Modified inet_del_protocol() to correctly</i></b>
 <a name="L18" href="source/net/ipv4/protocol.c#L18">18</a> <b><i> *                                maintain copy bit.</i></b>
 <a name="L19" href="source/net/ipv4/protocol.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/protocol.c#L20">20</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L21" href="source/net/ipv4/protocol.c#L21">21</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L22" href="source/net/ipv4/protocol.c#L22">22</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L23" href="source/net/ipv4/protocol.c#L23">23</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L24" href="source/net/ipv4/protocol.c#L24">24</a> <b><i> */</i></b>
 <a name="L25" href="source/net/ipv4/protocol.c#L25">25</a> #include &lt;linux/cache.h&gt;
 <a name="L26" href="source/net/ipv4/protocol.c#L26">26</a> #include &lt;linux/module.h&gt;
 <a name="L27" href="source/net/ipv4/protocol.c#L27">27</a> #include &lt;linux/netdevice.h&gt;
 <a name="L28" href="source/net/ipv4/protocol.c#L28">28</a> #include &lt;linux/spinlock.h&gt;
 <a name="L29" href="source/net/ipv4/protocol.c#L29">29</a> #include &lt;net/protocol.h&gt;
 <a name="L30" href="source/net/ipv4/protocol.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/protocol.c#L31">31</a> const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=MAX_INET_PROTOS">MAX_INET_PROTOS</a>] <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L32" href="source/net/ipv4/protocol.c#L32">32</a> const struct <a href="ident?i=net_offload">net_offload</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=inet_offloads">inet_offloads</a>[<a href="ident?i=MAX_INET_PROTOS">MAX_INET_PROTOS</a>] <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L33" href="source/net/ipv4/protocol.c#L33">33</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_offloads">inet_offloads</a>);
 <a name="L34" href="source/net/ipv4/protocol.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/protocol.c#L35">35</a> int <a href="ident?i=inet_add_protocol">inet_add_protocol</a>(const struct <a href="ident?i=net_protocol">net_protocol</a> *prot, unsigned char <a href="ident?i=protocol">protocol</a>)
 <a name="L36" href="source/net/ipv4/protocol.c#L36">36</a> {
 <a name="L37" href="source/net/ipv4/protocol.c#L37">37</a>         if (!prot-&gt;netns_ok) {
 <a name="L38" href="source/net/ipv4/protocol.c#L38">38</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Protocol %u is not namespace aware, cannot register.\n"</i>,
 <a name="L39" href="source/net/ipv4/protocol.c#L39">39</a>                         <a href="ident?i=protocol">protocol</a>);
 <a name="L40" href="source/net/ipv4/protocol.c#L40">40</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L41" href="source/net/ipv4/protocol.c#L41">41</a>         }
 <a name="L42" href="source/net/ipv4/protocol.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/protocol.c#L43">43</a>         return !<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=net_protocol">net_protocol</a> **)&amp;<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=protocol">protocol</a>],
 <a name="L44" href="source/net/ipv4/protocol.c#L44">44</a>                         <a href="ident?i=NULL">NULL</a>, prot) ? 0 : -1;
 <a name="L45" href="source/net/ipv4/protocol.c#L45">45</a> }
 <a name="L46" href="source/net/ipv4/protocol.c#L46">46</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_add_protocol">inet_add_protocol</a>);
 <a name="L47" href="source/net/ipv4/protocol.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/protocol.c#L48">48</a> int <a href="ident?i=inet_add_offload">inet_add_offload</a>(const struct <a href="ident?i=net_offload">net_offload</a> *prot, unsigned char <a href="ident?i=protocol">protocol</a>)
 <a name="L49" href="source/net/ipv4/protocol.c#L49">49</a> {
 <a name="L50" href="source/net/ipv4/protocol.c#L50">50</a>         return !<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=net_offload">net_offload</a> **)&amp;<a href="ident?i=inet_offloads">inet_offloads</a>[<a href="ident?i=protocol">protocol</a>],
 <a name="L51" href="source/net/ipv4/protocol.c#L51">51</a>                         <a href="ident?i=NULL">NULL</a>, prot) ? 0 : -1;
 <a name="L52" href="source/net/ipv4/protocol.c#L52">52</a> }
 <a name="L53" href="source/net/ipv4/protocol.c#L53">53</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_add_offload">inet_add_offload</a>);
 <a name="L54" href="source/net/ipv4/protocol.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/protocol.c#L55">55</a> int <a href="ident?i=inet_del_protocol">inet_del_protocol</a>(const struct <a href="ident?i=net_protocol">net_protocol</a> *prot, unsigned char <a href="ident?i=protocol">protocol</a>)
 <a name="L56" href="source/net/ipv4/protocol.c#L56">56</a> {
 <a name="L57" href="source/net/ipv4/protocol.c#L57">57</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L58" href="source/net/ipv4/protocol.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/protocol.c#L59">59</a>         <a href="ident?i=ret">ret</a> = (<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=net_protocol">net_protocol</a> **)&amp;<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=protocol">protocol</a>],
 <a name="L60" href="source/net/ipv4/protocol.c#L60">60</a>                        prot, <a href="ident?i=NULL">NULL</a>) == prot) ? 0 : -1;
 <a name="L61" href="source/net/ipv4/protocol.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/protocol.c#L62">62</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
 <a name="L63" href="source/net/ipv4/protocol.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/protocol.c#L64">64</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L65" href="source/net/ipv4/protocol.c#L65">65</a> }
 <a name="L66" href="source/net/ipv4/protocol.c#L66">66</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_del_protocol">inet_del_protocol</a>);
 <a name="L67" href="source/net/ipv4/protocol.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/protocol.c#L68">68</a> int <a href="ident?i=inet_del_offload">inet_del_offload</a>(const struct <a href="ident?i=net_offload">net_offload</a> *prot, unsigned char <a href="ident?i=protocol">protocol</a>)
 <a name="L69" href="source/net/ipv4/protocol.c#L69">69</a> {
 <a name="L70" href="source/net/ipv4/protocol.c#L70">70</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L71" href="source/net/ipv4/protocol.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/protocol.c#L72">72</a>         <a href="ident?i=ret">ret</a> = (<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=net_offload">net_offload</a> **)&amp;<a href="ident?i=inet_offloads">inet_offloads</a>[<a href="ident?i=protocol">protocol</a>],
 <a name="L73" href="source/net/ipv4/protocol.c#L73">73</a>                        prot, <a href="ident?i=NULL">NULL</a>) == prot) ? 0 : -1;
 <a name="L74" href="source/net/ipv4/protocol.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/protocol.c#L75">75</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
 <a name="L76" href="source/net/ipv4/protocol.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/protocol.c#L77">77</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L78" href="source/net/ipv4/protocol.c#L78">78</a> }
 <a name="L79" href="source/net/ipv4/protocol.c#L79">79</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_del_offload">inet_del_offload</a>);
 <a name="L80" href="source/net/ipv4/protocol.c#L80">80</a> </pre></div><p>
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
