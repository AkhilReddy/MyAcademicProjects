<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_proto_icmp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_proto_icmp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c">nf_nat_proto_icmp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L1">1</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L2">2</a> <b><i> * (C) 2002-2006 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L9">9</a> #include &lt;linux/types.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L10">10</a> #include &lt;linux/init.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L11">11</a> #include &lt;linux/export.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L12">12</a> #include &lt;linux/ip.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L13">13</a> #include &lt;linux/icmp.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L15">15</a> #include &lt;linux/netfilter.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L16">16</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L17">17</a> #include &lt;net/netfilter/nf_nat_core.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L18">18</a> #include &lt;net/netfilter/nf_nat_l4proto.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L20">20</a> static <a href="ident?i=bool">bool</a>
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L21">21</a> <a href="ident?i=icmp_in_range">icmp_in_range</a>(const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L22">22</a>               enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype,
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L23">23</a>               const union <a href="ident?i=nf_conntrack_man_proto">nf_conntrack_man_proto</a> *<a href="ident?i=min">min</a>,
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L24">24</a>               const union <a href="ident?i=nf_conntrack_man_proto">nf_conntrack_man_proto</a> *<a href="ident?i=max">max</a>)
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L25">25</a> {
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L26">26</a>         return <a href="ident?i=ntohs">ntohs</a>(tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>) &gt;= <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=min">min</a>-&gt;icmp.<a href="ident?i=id">id</a>) &amp;&amp;
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L27">27</a>                <a href="ident?i=ntohs">ntohs</a>(tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>) &lt;= <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=max">max</a>-&gt;icmp.<a href="ident?i=id">id</a>);
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L28">28</a> }
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L30">30</a> static void
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L31">31</a> <a href="ident?i=icmp_unique_tuple">icmp_unique_tuple</a>(const struct <a href="ident?i=nf_nat_l3proto">nf_nat_l3proto</a> *l3proto,
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L32">32</a>                   struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L33">33</a>                   const struct <a href="ident?i=nf_nat_range">nf_nat_range</a> *<a href="ident?i=range">range</a>,
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L34">34</a>                   enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype,
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L35">35</a>                   const struct <a href="ident?i=nf_conn">nf_conn</a> *ct)
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L36">36</a> {
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L37">37</a>         static <a href="ident?i=u_int16_t">u_int16_t</a> <a href="ident?i=id">id</a>;
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L38">38</a>         unsigned int <a href="ident?i=range_size">range_size</a>;
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L39">39</a>         unsigned int <a href="ident?i=i">i</a>;
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L41">41</a>         <a href="ident?i=range_size">range_size</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=max_proto">max_proto</a>.icmp.<a href="ident?i=id">id</a>) -
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L42">42</a>                      <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_proto">min_proto</a>.icmp.<a href="ident?i=id">id</a>) + 1;
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L43">43</a>         <b><i>/* If no range specified... */</i></b>
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L44">44</a>         if (!(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NF_NAT_RANGE_PROTO_SPECIFIED">NF_NAT_RANGE_PROTO_SPECIFIED</a>))
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L45">45</a>                 <a href="ident?i=range_size">range_size</a> = 0xFFFF;
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L47">47</a>         for (<a href="ident?i=i">i</a> = 0; ; ++<a href="ident?i=id">id</a>) {
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L48">48</a>                 tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_proto">min_proto</a>.icmp.<a href="ident?i=id">id</a>) +
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L49">49</a>                                              (<a href="ident?i=id">id</a> % <a href="ident?i=range_size">range_size</a>));
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L50">50</a>                 if (++<a href="ident?i=i">i</a> == <a href="ident?i=range_size">range_size</a> || !<a href="ident?i=nf_nat_used_tuple">nf_nat_used_tuple</a>(tuple, ct))
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L51">51</a>                         return;
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L52">52</a>         }
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L53">53</a>         return;
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L54">54</a> }
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L56">56</a> static <a href="ident?i=bool">bool</a>
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L57">57</a> <a href="ident?i=icmp_manip_pkt">icmp_manip_pkt</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L58">58</a>                const struct <a href="ident?i=nf_nat_l3proto">nf_nat_l3proto</a> *l3proto,
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L59">59</a>                unsigned int iphdroff, unsigned int hdroff,
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L60">60</a>                const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L61">61</a>                enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype)
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L62">62</a> {
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L63">63</a>         struct <a href="ident?i=icmphdr">icmphdr</a> *<a href="ident?i=hdr">hdr</a>;
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L65">65</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, hdroff + sizeof(*<a href="ident?i=hdr">hdr</a>)))
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L66">66</a>                 return <a href="ident?i=false">false</a>;
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L68">68</a>         <a href="ident?i=hdr">hdr</a> = (struct <a href="ident?i=icmphdr">icmphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + hdroff);
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L69">69</a>         <a href="ident?i=inet_proto_csum_replace2">inet_proto_csum_replace2</a>(&amp;<a href="ident?i=hdr">hdr</a>-&gt;<a href="ident?i=checksum">checksum</a>, <a href="ident?i=skb">skb</a>,
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L70">70</a>                                  <a href="ident?i=hdr">hdr</a>-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>, tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>, 0);
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L71">71</a>         <a href="ident?i=hdr">hdr</a>-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a> = tuple-&gt;<a href="ident?i=src">src</a>.u.icmp.<a href="ident?i=id">id</a>;
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L72">72</a>         return <a href="ident?i=true">true</a>;
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L73">73</a> }
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L75">75</a> const struct <a href="ident?i=nf_nat_l4proto">nf_nat_l4proto</a> <a href="ident?i=nf_nat_l4proto_icmp">nf_nat_l4proto_icmp</a> = {
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L76">76</a>         .l4proto                = <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>,
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L77">77</a>         .manip_pkt              = <a href="ident?i=icmp_manip_pkt">icmp_manip_pkt</a>,
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L78">78</a>         .<a href="ident?i=in_range">in_range</a>               = <a href="ident?i=icmp_in_range">icmp_in_range</a>,
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L79">79</a>         .unique_tuple           = <a href="ident?i=icmp_unique_tuple">icmp_unique_tuple</a>,
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L80">80</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L81">81</a>         .nlattr_to_range        = <a href="ident?i=nf_nat_l4proto_nlattr_to_range">nf_nat_l4proto_nlattr_to_range</a>,
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L82">82</a> #endif
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L83">83</a> };
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_proto_icmp.c#L84">84</a> </pre></div><p>
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
