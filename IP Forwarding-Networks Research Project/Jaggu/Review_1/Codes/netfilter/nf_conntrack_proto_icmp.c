<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_conntrack_proto_icmp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_conntrack_proto_icmp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c">nf_conntrack_proto_icmp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L1">1</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L2">2</a> <b><i> * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L3">3</a> <b><i> * (C) 2006-2010 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L5">5</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L6">6</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L7">7</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L8">8</a> <b><i> */</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L9">9</a> 
 <a name="L10" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L10">10</a> #include &lt;linux/types.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L11">11</a> #include &lt;linux/timer.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L12">12</a> #include &lt;linux/netfilter.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L13">13</a> #include &lt;linux/in.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L14">14</a> #include &lt;linux/icmp.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L15">15</a> #include &lt;linux/seq_file.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L16">16</a> #include &lt;net/ip.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L17">17</a> #include &lt;net/checksum.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L18">18</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L19">19</a> #include &lt;net/netfilter/nf_conntrack_tuple.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L20">20</a> #include &lt;net/netfilter/nf_conntrack_l4proto.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L21">21</a> #include &lt;net/netfilter/nf_conntrack_core.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L22">22</a> #include &lt;net/netfilter/nf_conntrack_zones.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L23">23</a> #include &lt;net/netfilter/nf_log.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L25">25</a> static unsigned int nf_ct_icmp_timeout <a href="ident?i=__read_mostly">__read_mostly</a> = 30*<a href="ident?i=HZ">HZ</a>;
 <a name="L26" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L27">27</a> static inline struct <a href="ident?i=nf_icmp_net">nf_icmp_net</a> *<a href="ident?i=icmp_pernet">icmp_pernet</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L28" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L28">28</a> {
 <a name="L29" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L29">29</a>         return &amp;<a href="ident?i=net">net</a>-&gt;ct.nf_ct_proto.icmp;
 <a name="L30" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L30">30</a> }
 <a name="L31" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L32">32</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_pkt_to_tuple">icmp_pkt_to_tuple</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int dataoff,
 <a name="L33" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L33">33</a>                               struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple)
 <a name="L34" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L34">34</a> {
 <a name="L35" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L35">35</a>         const struct <a href="ident?i=icmphdr">icmphdr</a> *hp;
 <a name="L36" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L36">36</a>         struct <a href="ident?i=icmphdr">icmphdr</a> _hdr;
 <a name="L37" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L38">38</a>         hp = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, dataoff, sizeof(_hdr), &amp;_hdr);
 <a name="L39" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L39">39</a>         if (hp == <a href="ident?i=NULL">NULL</a>)
 <a name="L40" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L40">40</a>                 return <a href="ident?i=false">false</a>;
 <a name="L41" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L42">42</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a> = hp-&gt;<a href="ident?i=type">type</a>;
 <a name="L43" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L43">43</a>         tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a> = hp-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>;
 <a name="L44" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L44">44</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=code">code</a> = hp-&gt;<a href="ident?i=code">code</a>;
 <a name="L45" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L46">46</a>         return <a href="ident?i=true">true</a>;
 <a name="L47" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L47">47</a> }
 <a name="L48" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L49">49</a> <b><i>/* Add 1; spaces filled with 0. */</i></b>
 <a name="L50" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L50">50</a> static const <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=invmap">invmap</a>[] = {
 <a name="L51" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L51">51</a>         [<a href="ident?i=ICMP_ECHO">ICMP_ECHO</a>] = <a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a> + 1,
 <a name="L52" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L52">52</a>         [<a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a>] = <a href="ident?i=ICMP_ECHO">ICMP_ECHO</a> + 1,
 <a name="L53" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L53">53</a>         [<a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a>] = <a href="ident?i=ICMP_TIMESTAMPREPLY">ICMP_TIMESTAMPREPLY</a> + 1,
 <a name="L54" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L54">54</a>         [<a href="ident?i=ICMP_TIMESTAMPREPLY">ICMP_TIMESTAMPREPLY</a>] = <a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a> + 1,
 <a name="L55" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L55">55</a>         [<a href="ident?i=ICMP_INFO_REQUEST">ICMP_INFO_REQUEST</a>] = <a href="ident?i=ICMP_INFO_REPLY">ICMP_INFO_REPLY</a> + 1,
 <a name="L56" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L56">56</a>         [<a href="ident?i=ICMP_INFO_REPLY">ICMP_INFO_REPLY</a>] = <a href="ident?i=ICMP_INFO_REQUEST">ICMP_INFO_REQUEST</a> + 1,
 <a name="L57" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L57">57</a>         [<a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a>] = <a href="ident?i=ICMP_ADDRESSREPLY">ICMP_ADDRESSREPLY</a> + 1,
 <a name="L58" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L58">58</a>         [<a href="ident?i=ICMP_ADDRESSREPLY">ICMP_ADDRESSREPLY</a>] = <a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a> + 1
 <a name="L59" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L59">59</a> };
 <a name="L60" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L61">61</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_invert_tuple">icmp_invert_tuple</a>(struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L62" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L62">62</a>                               const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *orig)
 <a name="L63" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L63">63</a> {
 <a name="L64" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L64">64</a>         if (orig-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a> &gt;= sizeof(<a href="ident?i=invmap">invmap</a>) ||
 <a name="L65" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L65">65</a>             !<a href="ident?i=invmap">invmap</a>[orig-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>])
 <a name="L66" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L66">66</a>                 return <a href="ident?i=false">false</a>;
 <a name="L67" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L68">68</a>         tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a> = orig-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>;
 <a name="L69" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L69">69</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a> = <a href="ident?i=invmap">invmap</a>[orig-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>] - 1;
 <a name="L70" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L70">70</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=code">code</a> = orig-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=code">code</a>;
 <a name="L71" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L71">71</a>         return <a href="ident?i=true">true</a>;
 <a name="L72" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L74">74</a> <b><i>/* Print out the per-protocol part of the tuple. */</i></b>
 <a name="L75" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L75">75</a> static void <a href="ident?i=icmp_print_tuple">icmp_print_tuple</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>,
 <a name="L76" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L76">76</a>                             const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple)
 <a name="L77" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L77">77</a> {
 <a name="L78" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L78">78</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"type=%u code=%u id=%u "</i>,
 <a name="L79" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L79">79</a>                    tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>,
 <a name="L80" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L80">80</a>                    tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=code">code</a>,
 <a name="L81" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L81">81</a>                    <a href="ident?i=ntohs">ntohs</a>(tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>));
 <a name="L82" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L84">84</a> static unsigned int *<a href="ident?i=icmp_get_timeouts">icmp_get_timeouts</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L85" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L86">86</a>         return &amp;<a href="ident?i=icmp_pernet">icmp_pernet</a>(<a href="ident?i=net">net</a>)-&gt;<a href="ident?i=timeout">timeout</a>;
 <a name="L87" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L87">87</a> }
 <a name="L88" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L89">89</a> <b><i>/* Returns verdict for packet, or -1 for invalid. */</i></b>
 <a name="L90" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L90">90</a> static int <a href="ident?i=icmp_packet">icmp_packet</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
 <a name="L91" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L91">91</a>                        const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L92" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L92">92</a>                        unsigned int dataoff,
 <a name="L93" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L93">93</a>                        enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
 <a name="L94" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L94">94</a>                        <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=pf">pf</a>,
 <a name="L95" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L95">95</a>                        unsigned int hooknum,
 <a name="L96" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L96">96</a>                        unsigned int *<a href="ident?i=timeout">timeout</a>)
 <a name="L97" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L97">97</a> {
 <a name="L98" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L98">98</a>         <b><i>/* Do not immediately delete the connection after the first</i></b>
 <a name="L99" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L99">99</a> <b><i>           successful reply to avoid excessive conntrackd traffic</i></b>
<a name="L100" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L100">100</a> <b><i>           and also to handle correctly ICMP echo reply duplicates. */</i></b>
<a name="L101" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L101">101</a>         <a href="ident?i=nf_ct_refresh_acct">nf_ct_refresh_acct</a>(ct, ctinfo, <a href="ident?i=skb">skb</a>, *<a href="ident?i=timeout">timeout</a>);
<a name="L102" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L103">103</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L104" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L104">104</a> }
<a name="L105" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L106">106</a> <b><i>/* Called when a new connection for this protocol found. */</i></b>
<a name="L107" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L107">107</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_new">icmp_new</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *ct, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L108" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L108">108</a>                      unsigned int dataoff, unsigned int *<a href="ident?i=timeouts">timeouts</a>)
<a name="L109" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L109">109</a> {
<a name="L110" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L110">110</a>         static const <a href="ident?i=u_int8_t">u_int8_t</a> valid_new[] = {
<a name="L111" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L111">111</a>                 [<a href="ident?i=ICMP_ECHO">ICMP_ECHO</a>] = 1,
<a name="L112" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L112">112</a>                 [<a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a>] = 1,
<a name="L113" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L113">113</a>                 [<a href="ident?i=ICMP_INFO_REQUEST">ICMP_INFO_REQUEST</a>] = 1,
<a name="L114" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L114">114</a>                 [<a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a>] = 1
<a name="L115" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L115">115</a>         };
<a name="L116" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L117">117</a>         if (ct-&gt;tuplehash[0].tuple.<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a> &gt;= sizeof(valid_new) ||
<a name="L118" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L118">118</a>             !valid_new[ct-&gt;tuplehash[0].tuple.<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>]) {
<a name="L119" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L119">119</a>                 <b><i>/* Can't create a new ICMP `conn' with this. */</i></b>
<a name="L120" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L120">120</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"icmp: can't create new conn with type %u\n"</i>,
<a name="L121" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L121">121</a>                          ct-&gt;tuplehash[0].tuple.<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>);
<a name="L122" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L122">122</a>                 <a href="ident?i=nf_ct_dump_tuple_ip">nf_ct_dump_tuple_ip</a>(&amp;ct-&gt;tuplehash[0].tuple);
<a name="L123" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L123">123</a>                 return <a href="ident?i=false">false</a>;
<a name="L124" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L124">124</a>         }
<a name="L125" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L125">125</a>         return <a href="ident?i=true">true</a>;
<a name="L126" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L126">126</a> }
<a name="L127" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L128">128</a> <b><i>/* Returns conntrack if it dealt with ICMP, and filled in skb fields */</i></b>
<a name="L129" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L129">129</a> static int
<a name="L130" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L130">130</a> <a href="ident?i=icmp_error_message">icmp_error_message</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *tmpl, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L131" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L131">131</a>                  enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> *ctinfo,
<a name="L132" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L132">132</a>                  unsigned int hooknum)
<a name="L133" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L134">134</a>         struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> innertuple, origtuple;
<a name="L135" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L135">135</a>         const struct <a href="ident?i=nf_conntrack_l4proto">nf_conntrack_l4proto</a> *innerproto;
<a name="L136" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L136">136</a>         const struct <a href="ident?i=nf_conntrack_tuple_hash">nf_conntrack_tuple_hash</a> *<a href="ident?i=h">h</a>;
<a name="L137" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L137">137</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=zone">zone</a> = tmpl ? <a href="ident?i=nf_ct_zone">nf_ct_zone</a>(tmpl) : <a href="ident?i=NF_CT_DEFAULT_ZONE">NF_CT_DEFAULT_ZONE</a>;
<a name="L138" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L139">139</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(<a href="ident?i=skb">skb</a>-&gt;nfct == <a href="ident?i=NULL">NULL</a>);
<a name="L140" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L141">141</a>         <b><i>/* Are they talking about one of our connections? */</i></b>
<a name="L142" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L142">142</a>         if (!<a href="ident?i=nf_ct_get_tuplepr">nf_ct_get_tuplepr</a>(<a href="ident?i=skb">skb</a>,
<a name="L143" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L143">143</a>                                <a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>)
<a name="L144" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L144">144</a>                                                        + sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>),
<a name="L145" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L145">145</a>                                <a href="ident?i=PF_INET">PF_INET</a>, &amp;origtuple)) {
<a name="L146" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L146">146</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"icmp_error_message: failed to get tuple\n"</i>);
<a name="L147" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L147">147</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L148" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L148">148</a>         }
<a name="L149" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L150">150</a>         <b><i>/* rcu_read_lock()ed by nf_hook_slow */</i></b>
<a name="L151" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L151">151</a>         innerproto = <a href="ident?i=__nf_ct_l4proto_find">__nf_ct_l4proto_find</a>(<a href="ident?i=PF_INET">PF_INET</a>, origtuple.<a href="ident?i=dst">dst</a>.protonum);
<a name="L152" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L153">153</a>         <b><i>/* Ordinarily, we'd expect the inverted tupleproto, but it's</i></b>
<a name="L154" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L154">154</a> <b><i>           been preserved inside the ICMP. */</i></b>
<a name="L155" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L155">155</a>         if (!<a href="ident?i=nf_ct_invert_tuple">nf_ct_invert_tuple</a>(&amp;innertuple, &amp;origtuple,
<a name="L156" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L156">156</a>                                 &amp;<a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a>, innerproto)) {
<a name="L157" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L157">157</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"icmp_error_message: no match\n"</i>);
<a name="L158" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L158">158</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L159" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L159">159</a>         }
<a name="L160" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L161">161</a>         *ctinfo = IP_CT_RELATED;
<a name="L162" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L163">163</a>         <a href="ident?i=h">h</a> = <a href="ident?i=nf_conntrack_find_get">nf_conntrack_find_get</a>(<a href="ident?i=net">net</a>, <a href="ident?i=zone">zone</a>, &amp;innertuple);
<a name="L164" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L164">164</a>         if (!<a href="ident?i=h">h</a>) {
<a name="L165" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L165">165</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"icmp_error_message: no match\n"</i>);
<a name="L166" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L166">166</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L167" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L167">167</a>         }
<a name="L168" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L169">169</a>         if (<a href="ident?i=NF_CT_DIRECTION">NF_CT_DIRECTION</a>(<a href="ident?i=h">h</a>) == IP_CT_DIR_REPLY)
<a name="L170" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L170">170</a>                 *ctinfo += IP_CT_IS_REPLY;
<a name="L171" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L172">172</a>         <b><i>/* Update skb to refer to this connection */</i></b>
<a name="L173" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L173">173</a>         <a href="ident?i=skb">skb</a>-&gt;nfct = &amp;<a href="ident?i=nf_ct_tuplehash_to_ctrack">nf_ct_tuplehash_to_ctrack</a>(<a href="ident?i=h">h</a>)-&gt;ct_general;
<a name="L174" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L174">174</a>         <a href="ident?i=skb">skb</a>-&gt;nfctinfo = *ctinfo;
<a name="L175" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L175">175</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L176" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L176">176</a> }
<a name="L177" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L178">178</a> <b><i>/* Small and modified version of icmp_rcv */</i></b>
<a name="L179" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L179">179</a> static int
<a name="L180" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L180">180</a> <a href="ident?i=icmp_error">icmp_error</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *tmpl,
<a name="L181" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L181">181</a>            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int dataoff,
<a name="L182" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L182">182</a>            enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> *ctinfo, <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=pf">pf</a>, unsigned int hooknum)
<a name="L183" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L183">183</a> {
<a name="L184" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L184">184</a>         const struct <a href="ident?i=icmphdr">icmphdr</a> *icmph;
<a name="L185" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L185">185</a>         struct <a href="ident?i=icmphdr">icmphdr</a> _ih;
<a name="L186" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L187">187</a>         <b><i>/* Not enough header? */</i></b>
<a name="L188" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L188">188</a>         icmph = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>), sizeof(_ih), &amp;_ih);
<a name="L189" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L189">189</a>         if (icmph == <a href="ident?i=NULL">NULL</a>) {
<a name="L190" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L190">190</a>                 if (<a href="ident?i=LOG_INVALID">LOG_INVALID</a>(<a href="ident?i=net">net</a>, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>))
<a name="L191" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L191">191</a>                         <a href="ident?i=nf_log_packet">nf_log_packet</a>(<a href="ident?i=net">net</a>, <a href="ident?i=PF_INET">PF_INET</a>, 0, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L192" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L192">192</a>                                       <a href="ident?i=NULL">NULL</a>, <i>"nf_ct_icmp: short packet "</i>);
<a name="L193" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L193">193</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L194" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L194">194</a>         }
<a name="L195" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L196">196</a>         <b><i>/* See ip_conntrack_proto_tcp.c */</i></b>
<a name="L197" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L197">197</a>         if (<a href="ident?i=net">net</a>-&gt;ct.sysctl_checksum &amp;&amp; hooknum == NF_INET_PRE_ROUTING &amp;&amp;
<a name="L198" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L198">198</a>             <a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(<a href="ident?i=skb">skb</a>, hooknum, dataoff, 0)) {
<a name="L199" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L199">199</a>                 if (<a href="ident?i=LOG_INVALID">LOG_INVALID</a>(<a href="ident?i=net">net</a>, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>))
<a name="L200" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L200">200</a>                         <a href="ident?i=nf_log_packet">nf_log_packet</a>(<a href="ident?i=net">net</a>, <a href="ident?i=PF_INET">PF_INET</a>, 0, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L201" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L201">201</a>                                       <i>"nf_ct_icmp: bad HW ICMP checksum "</i>);
<a name="L202" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L202">202</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L203" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L203">203</a>         }
<a name="L204" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L205">205</a>         <b><i>/*</i></b>
<a name="L206" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L206">206</a> <b><i>         *      18 is the highest 'known' ICMP type. Anything else is a mystery</i></b>
<a name="L207" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L207">207</a> <b><i>         *</i></b>
<a name="L208" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L208">208</a> <b><i>         *      RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently</i></b>
<a name="L209" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L209">209</a> <b><i>         *                discarded.</i></b>
<a name="L210" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L210">210</a> <b><i>         */</i></b>
<a name="L211" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L211">211</a>         if (icmph-&gt;<a href="ident?i=type">type</a> &gt; <a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a>) {
<a name="L212" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L212">212</a>                 if (<a href="ident?i=LOG_INVALID">LOG_INVALID</a>(<a href="ident?i=net">net</a>, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>))
<a name="L213" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L213">213</a>                         <a href="ident?i=nf_log_packet">nf_log_packet</a>(<a href="ident?i=net">net</a>, <a href="ident?i=PF_INET">PF_INET</a>, 0, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L214" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L214">214</a>                                       <i>"nf_ct_icmp: invalid ICMP type "</i>);
<a name="L215" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L215">215</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L216" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L216">216</a>         }
<a name="L217" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L218">218</a>         <b><i>/* Need to track icmp error message? */</i></b>
<a name="L219" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L219">219</a>         if (icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp;
<a name="L220" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L220">220</a>             icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a> &amp;&amp;
<a name="L221" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L221">221</a>             icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a> &amp;&amp;
<a name="L222" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L222">222</a>             icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a> &amp;&amp;
<a name="L223" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L223">223</a>             icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>)
<a name="L224" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L224">224</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L225" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L226">226</a>         return <a href="ident?i=icmp_error_message">icmp_error_message</a>(<a href="ident?i=net">net</a>, tmpl, <a href="ident?i=skb">skb</a>, ctinfo, hooknum);
<a name="L227" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L227">227</a> }
<a name="L228" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L229">229</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L230" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L231">231</a> #include &lt;linux/netfilter/nfnetlink.h&gt;
<a name="L232" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L232">232</a> #include &lt;linux/netfilter/nfnetlink_conntrack.h&gt;
<a name="L233" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L234">234</a> static int <a href="ident?i=icmp_tuple_to_nlattr">icmp_tuple_to_nlattr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L235" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L235">235</a>                                 const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=t">t</a>)
<a name="L236" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L236">236</a> {
<a name="L237" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L237">237</a>         if (<a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, CTA_PROTO_ICMP_ID, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>) ||
<a name="L238" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L238">238</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, CTA_PROTO_ICMP_TYPE, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>) ||
<a name="L239" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L239">239</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, CTA_PROTO_ICMP_CODE, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=code">code</a>))
<a name="L240" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L240">240</a>                 goto nla_put_failure;
<a name="L241" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L241">241</a>         return 0;
<a name="L242" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L243">243</a> nla_put_failure:
<a name="L244" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L244">244</a>         return -1;
<a name="L245" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L245">245</a> }
<a name="L246" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L247">247</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=icmp_nla_policy">icmp_nla_policy</a>[<a href="ident?i=CTA_PROTO_MAX">CTA_PROTO_MAX</a>+1] = {
<a name="L248" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L248">248</a>         [CTA_PROTO_ICMP_TYPE]   = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L249" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L249">249</a>         [CTA_PROTO_ICMP_CODE]   = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L250" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L250">250</a>         [CTA_PROTO_ICMP_ID]     = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L251" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L251">251</a> };
<a name="L252" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L253">253</a> static int <a href="ident?i=icmp_nlattr_to_tuple">icmp_nlattr_to_tuple</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L254" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L254">254</a>                                 struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple)
<a name="L255" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L255">255</a> {
<a name="L256" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L256">256</a>         if (!<a href="ident?i=tb">tb</a>[CTA_PROTO_ICMP_TYPE] ||
<a name="L257" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L257">257</a>             !<a href="ident?i=tb">tb</a>[CTA_PROTO_ICMP_CODE] ||
<a name="L258" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L258">258</a>             !<a href="ident?i=tb">tb</a>[CTA_PROTO_ICMP_ID])
<a name="L259" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L259">259</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L260" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L261">261</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=tb">tb</a>[CTA_PROTO_ICMP_TYPE]);
<a name="L262" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L262">262</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=code">code</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=tb">tb</a>[CTA_PROTO_ICMP_CODE]);
<a name="L263" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L263">263</a>         tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a> = <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=tb">tb</a>[CTA_PROTO_ICMP_ID]);
<a name="L264" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L265">265</a>         if (tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a> &gt;= sizeof(<a href="ident?i=invmap">invmap</a>) ||
<a name="L266" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L266">266</a>             !<a href="ident?i=invmap">invmap</a>[tuple-&gt;<a href="ident?i=dst">dst</a>.u.icmp.<a href="ident?i=type">type</a>])
<a name="L267" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L267">267</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L268" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L269">269</a>         return 0;
<a name="L270" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L270">270</a> }
<a name="L271" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L272">272</a> static int <a href="ident?i=icmp_nlattr_tuple_size">icmp_nlattr_tuple_size</a>(void)
<a name="L273" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L273">273</a> {
<a name="L274" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L274">274</a>         return <a href="ident?i=nla_policy_len">nla_policy_len</a>(<a href="ident?i=icmp_nla_policy">icmp_nla_policy</a>, <a href="ident?i=CTA_PROTO_MAX">CTA_PROTO_MAX</a> + 1);
<a name="L275" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L275">275</a> }
<a name="L276" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L276">276</a> #endif
<a name="L277" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L278">278</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK_TIMEOUT)
<a name="L279" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L280">280</a> #include &lt;linux/netfilter/nfnetlink.h&gt;
<a name="L281" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L281">281</a> #include &lt;linux/netfilter/nfnetlink_cttimeout.h&gt;
<a name="L282" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L283">283</a> static int <a href="ident?i=icmp_timeout_nlattr_to_obj">icmp_timeout_nlattr_to_obj</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L284" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L284">284</a>                                       struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, void *<a href="ident?i=data">data</a>)
<a name="L285" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L285">285</a> {
<a name="L286" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L286">286</a>         unsigned int *<a href="ident?i=timeout">timeout</a> = <a href="ident?i=data">data</a>;
<a name="L287" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L287">287</a>         struct <a href="ident?i=nf_icmp_net">nf_icmp_net</a> *<a href="ident?i=in">in</a> = <a href="ident?i=icmp_pernet">icmp_pernet</a>(<a href="ident?i=net">net</a>);
<a name="L288" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L289">289</a>         if (<a href="ident?i=tb">tb</a>[CTA_TIMEOUT_ICMP_TIMEOUT]) {
<a name="L290" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L290">290</a>                 *<a href="ident?i=timeout">timeout</a> =
<a name="L291" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L291">291</a>                         <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=tb">tb</a>[CTA_TIMEOUT_ICMP_TIMEOUT])) * <a href="ident?i=HZ">HZ</a>;
<a name="L292" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L292">292</a>         } else {
<a name="L293" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L293">293</a>                 <b><i>/* Set default ICMP timeout. */</i></b>
<a name="L294" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L294">294</a>                 *<a href="ident?i=timeout">timeout</a> = <a href="ident?i=in">in</a>-&gt;<a href="ident?i=timeout">timeout</a>;
<a name="L295" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L295">295</a>         }
<a name="L296" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L296">296</a>         return 0;
<a name="L297" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L297">297</a> }
<a name="L298" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L299">299</a> static int
<a name="L300" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L300">300</a> <a href="ident?i=icmp_timeout_obj_to_nlattr">icmp_timeout_obj_to_nlattr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const void *<a href="ident?i=data">data</a>)
<a name="L301" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L301">301</a> {
<a name="L302" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L302">302</a>         const unsigned int *<a href="ident?i=timeout">timeout</a> = <a href="ident?i=data">data</a>;
<a name="L303" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L304">304</a>         if (<a href="ident?i=nla_put_be32">nla_put_be32</a>(<a href="ident?i=skb">skb</a>, CTA_TIMEOUT_ICMP_TIMEOUT, <a href="ident?i=htonl">htonl</a>(*<a href="ident?i=timeout">timeout</a> / <a href="ident?i=HZ">HZ</a>)))
<a name="L305" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L305">305</a>                 goto nla_put_failure;
<a name="L306" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L306">306</a>         return 0;
<a name="L307" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L308">308</a> nla_put_failure:
<a name="L309" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L309">309</a>         return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L310" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L310">310</a> }
<a name="L311" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L312">312</a> static const struct <a href="ident?i=nla_policy">nla_policy</a>
<a name="L313" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L313">313</a> <a href="ident?i=icmp_timeout_nla_policy">icmp_timeout_nla_policy</a>[<a href="ident?i=CTA_TIMEOUT_ICMP_MAX">CTA_TIMEOUT_ICMP_MAX</a>+1] = {
<a name="L314" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L314">314</a>         [CTA_TIMEOUT_ICMP_TIMEOUT]      = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L315" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L315">315</a> };
<a name="L316" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L316">316</a> #endif <b><i>/* CONFIG_NF_CT_NETLINK_TIMEOUT */</i></b>
<a name="L317" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L318">318</a> #ifdef CONFIG_SYSCTL
<a name="L319" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L319">319</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=icmp_sysctl_table">icmp_sysctl_table</a>[] = {
<a name="L320" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L320">320</a>         {
<a name="L321" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L321">321</a>                 .<a href="ident?i=procname">procname</a>       = <i>"nf_conntrack_icmp_timeout"</i>,
<a name="L322" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L322">322</a>                 .maxlen         = sizeof(unsigned int),
<a name="L323" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L323">323</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L324" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L324">324</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L325" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L325">325</a>         },
<a name="L326" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L326">326</a>         { }
<a name="L327" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L327">327</a> };
<a name="L328" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L328">328</a> #ifdef CONFIG_NF_CONNTRACK_PROC_COMPAT
<a name="L329" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L329">329</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=icmp_compat_sysctl_table">icmp_compat_sysctl_table</a>[] = {
<a name="L330" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L330">330</a>         {
<a name="L331" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L331">331</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_conntrack_icmp_timeout"</i>,
<a name="L332" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L332">332</a>                 .maxlen         = sizeof(unsigned int),
<a name="L333" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L333">333</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L334" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L334">334</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L335" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L335">335</a>         },
<a name="L336" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L336">336</a>         { }
<a name="L337" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L337">337</a> };
<a name="L338" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L338">338</a> #endif <b><i>/* CONFIG_NF_CONNTRACK_PROC_COMPAT */</i></b>
<a name="L339" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L339">339</a> #endif <b><i>/* CONFIG_SYSCTL */</i></b>
<a name="L340" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L341">341</a> static int <a href="ident?i=icmp_kmemdup_sysctl_table">icmp_kmemdup_sysctl_table</a>(struct <a href="ident?i=nf_proto_net">nf_proto_net</a> *pn,
<a name="L342" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L342">342</a>                                      struct <a href="ident?i=nf_icmp_net">nf_icmp_net</a> *<a href="ident?i=in">in</a>)
<a name="L343" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L343">343</a> {
<a name="L344" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L344">344</a> #ifdef CONFIG_SYSCTL
<a name="L345" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L345">345</a>         pn-&gt;<a href="ident?i=ctl_table">ctl_table</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=icmp_sysctl_table">icmp_sysctl_table</a>,
<a name="L346" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L346">346</a>                                 sizeof(<a href="ident?i=icmp_sysctl_table">icmp_sysctl_table</a>),
<a name="L347" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L347">347</a>                                 <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L348" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L348">348</a>         if (!pn-&gt;<a href="ident?i=ctl_table">ctl_table</a>)
<a name="L349" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L349">349</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L350" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L351">351</a>         pn-&gt;<a href="ident?i=ctl_table">ctl_table</a>[0].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=in">in</a>-&gt;<a href="ident?i=timeout">timeout</a>;
<a name="L352" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L352">352</a> #endif
<a name="L353" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L353">353</a>         return 0;
<a name="L354" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L354">354</a> }
<a name="L355" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L356">356</a> static int <a href="ident?i=icmp_kmemdup_compat_sysctl_table">icmp_kmemdup_compat_sysctl_table</a>(struct <a href="ident?i=nf_proto_net">nf_proto_net</a> *pn,
<a name="L357" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L357">357</a>                                             struct <a href="ident?i=nf_icmp_net">nf_icmp_net</a> *<a href="ident?i=in">in</a>)
<a name="L358" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L358">358</a> {
<a name="L359" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L359">359</a> #ifdef CONFIG_SYSCTL
<a name="L360" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L360">360</a> #ifdef CONFIG_NF_CONNTRACK_PROC_COMPAT
<a name="L361" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L361">361</a>         pn-&gt;ctl_compat_table = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=icmp_compat_sysctl_table">icmp_compat_sysctl_table</a>,
<a name="L362" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L362">362</a>                                        sizeof(<a href="ident?i=icmp_compat_sysctl_table">icmp_compat_sysctl_table</a>),
<a name="L363" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L363">363</a>                                        <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L364" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L364">364</a>         if (!pn-&gt;ctl_compat_table)
<a name="L365" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L365">365</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L366" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L367">367</a>         pn-&gt;ctl_compat_table[0].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=in">in</a>-&gt;<a href="ident?i=timeout">timeout</a>;
<a name="L368" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L368">368</a> #endif
<a name="L369" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L369">369</a> #endif
<a name="L370" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L370">370</a>         return 0;
<a name="L371" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L371">371</a> }
<a name="L372" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L373">373</a> static int <a href="ident?i=icmp_init_net">icmp_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u_int16_t">u_int16_t</a> <a href="ident?i=proto">proto</a>)
<a name="L374" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L374">374</a> {
<a name="L375" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L375">375</a>         int <a href="ident?i=ret">ret</a>;
<a name="L376" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L376">376</a>         struct <a href="ident?i=nf_icmp_net">nf_icmp_net</a> *<a href="ident?i=in">in</a> = <a href="ident?i=icmp_pernet">icmp_pernet</a>(<a href="ident?i=net">net</a>);
<a name="L377" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L377">377</a>         struct <a href="ident?i=nf_proto_net">nf_proto_net</a> *pn = &amp;<a href="ident?i=in">in</a>-&gt;pn;
<a name="L378" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L379">379</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=timeout">timeout</a> = nf_ct_icmp_timeout;
<a name="L380" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L380">380</a> 
<a name="L381" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L381">381</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=icmp_kmemdup_compat_sysctl_table">icmp_kmemdup_compat_sysctl_table</a>(pn, <a href="ident?i=in">in</a>);
<a name="L382" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L382">382</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L383" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L383">383</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L384" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L385">385</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=icmp_kmemdup_sysctl_table">icmp_kmemdup_sysctl_table</a>(pn, <a href="ident?i=in">in</a>);
<a name="L386" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L386">386</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L387" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L387">387</a>                 <a href="ident?i=nf_ct_kfree_compat_sysctl_table">nf_ct_kfree_compat_sysctl_table</a>(pn);
<a name="L388" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L388">388</a> 
<a name="L389" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L389">389</a>         return <a href="ident?i=ret">ret</a>;
<a name="L390" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L390">390</a> }
<a name="L391" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L392">392</a> static struct <a href="ident?i=nf_proto_net">nf_proto_net</a> *<a href="ident?i=icmp_get_net_proto">icmp_get_net_proto</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L393" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L393">393</a> {
<a name="L394" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L394">394</a>         return &amp;<a href="ident?i=net">net</a>-&gt;ct.nf_ct_proto.icmp.pn;
<a name="L395" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L395">395</a> }
<a name="L396" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L396">396</a> 
<a name="L397" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L397">397</a> struct <a href="ident?i=nf_conntrack_l4proto">nf_conntrack_l4proto</a> <a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a> <a href="ident?i=__read_mostly">__read_mostly</a> =
<a name="L398" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L398">398</a> {
<a name="L399" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L399">399</a>         .l3proto                = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L400" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L400">400</a>         .l4proto                = <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>,
<a name="L401" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L401">401</a>         .<a href="ident?i=name">name</a>                   = <i>"icmp"</i>,
<a name="L402" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L402">402</a>         .pkt_to_tuple           = <a href="ident?i=icmp_pkt_to_tuple">icmp_pkt_to_tuple</a>,
<a name="L403" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L403">403</a>         .invert_tuple           = <a href="ident?i=icmp_invert_tuple">icmp_invert_tuple</a>,
<a name="L404" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L404">404</a>         .<a href="ident?i=print_tuple">print_tuple</a>            = <a href="ident?i=icmp_print_tuple">icmp_print_tuple</a>,
<a name="L405" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L405">405</a>         .<a href="ident?i=packet">packet</a>                 = <a href="ident?i=icmp_packet">icmp_packet</a>,
<a name="L406" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L406">406</a>         .get_timeouts           = <a href="ident?i=icmp_get_timeouts">icmp_get_timeouts</a>,
<a name="L407" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L407">407</a>         .<a href="ident?i=new">new</a>                    = <a href="ident?i=icmp_new">icmp_new</a>,
<a name="L408" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L408">408</a>         .<a href="ident?i=error">error</a>                  = <a href="ident?i=icmp_error">icmp_error</a>,
<a name="L409" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L409">409</a>         .<a href="ident?i=destroy">destroy</a>                = <a href="ident?i=NULL">NULL</a>,
<a name="L410" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L410">410</a>         .<a href="ident?i=me">me</a>                     = <a href="ident?i=NULL">NULL</a>,
<a name="L411" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L411">411</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L412" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L412">412</a>         .tuple_to_nlattr        = <a href="ident?i=icmp_tuple_to_nlattr">icmp_tuple_to_nlattr</a>,
<a name="L413" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L413">413</a>         .nlattr_tuple_size      = <a href="ident?i=icmp_nlattr_tuple_size">icmp_nlattr_tuple_size</a>,
<a name="L414" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L414">414</a>         .nlattr_to_tuple        = <a href="ident?i=icmp_nlattr_to_tuple">icmp_nlattr_to_tuple</a>,
<a name="L415" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L415">415</a>         .<a href="ident?i=nla_policy">nla_policy</a>             = <a href="ident?i=icmp_nla_policy">icmp_nla_policy</a>,
<a name="L416" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L416">416</a> #endif
<a name="L417" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L417">417</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK_TIMEOUT)
<a name="L418" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L418">418</a>         .<a href="ident?i=ctnl_timeout">ctnl_timeout</a>           = {
<a name="L419" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L419">419</a>                 .nlattr_to_obj  = <a href="ident?i=icmp_timeout_nlattr_to_obj">icmp_timeout_nlattr_to_obj</a>,
<a name="L420" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L420">420</a>                 .obj_to_nlattr  = <a href="ident?i=icmp_timeout_obj_to_nlattr">icmp_timeout_obj_to_nlattr</a>,
<a name="L421" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L421">421</a>                 .nlattr_max     = <a href="ident?i=CTA_TIMEOUT_ICMP_MAX">CTA_TIMEOUT_ICMP_MAX</a>,
<a name="L422" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L422">422</a>                 .obj_size       = sizeof(unsigned int),
<a name="L423" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L423">423</a>                 .<a href="ident?i=nla_policy">nla_policy</a>     = <a href="ident?i=icmp_timeout_nla_policy">icmp_timeout_nla_policy</a>,
<a name="L424" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L424">424</a>         },
<a name="L425" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L425">425</a> #endif <b><i>/* CONFIG_NF_CT_NETLINK_TIMEOUT */</i></b>
<a name="L426" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L426">426</a>         .<a href="ident?i=init_net">init_net</a>               = <a href="ident?i=icmp_init_net">icmp_init_net</a>,
<a name="L427" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L427">427</a>         .get_net_proto          = <a href="ident?i=icmp_get_net_proto">icmp_get_net_proto</a>,
<a name="L428" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L428">428</a> };
<a name="L429" href="source/net/ipv4/netfilter/nf_conntrack_proto_icmp.c#L429">429</a> </pre></div><p>
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
