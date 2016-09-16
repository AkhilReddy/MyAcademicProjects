<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c">nf_conntrack_l3proto_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L1">1</a> 
  <a name="L2" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L2">2</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L3">3</a> <b><i> * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L4">4</a> <b><i> * (C) 2006-2012 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L6">6</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L7">7</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L8">8</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L11">11</a> #include &lt;linux/types.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L12">12</a> #include &lt;linux/ip.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L13">13</a> #include &lt;linux/netfilter.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L14">14</a> #include &lt;linux/module.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L15">15</a> #include &lt;linux/skbuff.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L16">16</a> #include &lt;linux/icmp.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L17">17</a> #include &lt;linux/sysctl.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L18">18</a> #include &lt;net/route.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L19">19</a> #include &lt;net/ip.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L21">21</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L22">22</a> #include &lt;net/netfilter/nf_conntrack.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L23">23</a> #include &lt;net/netfilter/nf_conntrack_helper.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L24">24</a> #include &lt;net/netfilter/nf_conntrack_l4proto.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L25">25</a> #include &lt;net/netfilter/nf_conntrack_l3proto.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L26">26</a> #include &lt;net/netfilter/nf_conntrack_zones.h&gt;
 <a name="L27" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L27">27</a> #include &lt;net/netfilter/nf_conntrack_core.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L28">28</a> #include &lt;net/netfilter/nf_conntrack_seqadj.h&gt;
 <a name="L29" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L29">29</a> #include &lt;net/netfilter/ipv4/nf_conntrack_ipv4.h&gt;
 <a name="L30" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L30">30</a> #include &lt;net/netfilter/nf_nat_helper.h&gt;
 <a name="L31" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L31">31</a> #include &lt;net/netfilter/ipv4/nf_defrag_ipv4.h&gt;
 <a name="L32" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L32">32</a> #include &lt;net/netfilter/nf_log.h&gt;
 <a name="L33" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L34">34</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ipv4_pkt_to_tuple">ipv4_pkt_to_tuple</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int nhoff,
 <a name="L35" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L35">35</a>                               struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple)
 <a name="L36" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L36">36</a> {
 <a name="L37" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L37">37</a>         const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=ap">ap</a>;
 <a name="L38" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L38">38</a>         <a href="ident?i=__be32">__be32</a> _addrs[2];
 <a name="L39" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L39">39</a>         <a href="ident?i=ap">ap</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, nhoff + <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=saddr">saddr</a>),
 <a name="L40" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L40">40</a>                                 sizeof(<a href="ident?i=u_int32_t">u_int32_t</a>) * 2, _addrs);
 <a name="L41" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L41">41</a>         if (<a href="ident?i=ap">ap</a> == <a href="ident?i=NULL">NULL</a>)
 <a name="L42" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L42">42</a>                 return <a href="ident?i=false">false</a>;
 <a name="L43" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L44">44</a>         tuple-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=ap">ap</a>[0];
 <a name="L45" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L45">45</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=ap">ap</a>[1];
 <a name="L46" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L47">47</a>         return <a href="ident?i=true">true</a>;
 <a name="L48" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L48">48</a> }
 <a name="L49" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L50">50</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ipv4_invert_tuple">ipv4_invert_tuple</a>(struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L51" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L51">51</a>                               const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *orig)
 <a name="L52" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L52">52</a> {
 <a name="L53" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L53">53</a>         tuple-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> = orig-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L54" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L54">54</a>         tuple-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = orig-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L55" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L56">56</a>         return <a href="ident?i=true">true</a>;
 <a name="L57" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L57">57</a> }
 <a name="L58" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L59">59</a> static void <a href="ident?i=ipv4_print_tuple">ipv4_print_tuple</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>,
 <a name="L60" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L60">60</a>                             const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple)
 <a name="L61" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L62">62</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"src=%pI4 dst=%pI4 "</i>,
 <a name="L63" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L63">63</a>                    &amp;tuple-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>, &amp;tuple-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>);
 <a name="L64" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L64">64</a> }
 <a name="L65" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L66">66</a> static int <a href="ident?i=ipv4_get_l4proto">ipv4_get_l4proto</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int nhoff,
 <a name="L67" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L67">67</a>                             unsigned int *dataoff, <a href="ident?i=u_int8_t">u_int8_t</a> *protonum)
 <a name="L68" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L69">69</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L70" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L70">70</a>         struct <a href="ident?i=iphdr">iphdr</a> _iph;
 <a name="L71" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L72">72</a>         iph = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, nhoff, sizeof(_iph), &amp;_iph);
 <a name="L73" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L73">73</a>         if (iph == <a href="ident?i=NULL">NULL</a>)
 <a name="L74" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L74">74</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L75" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L76">76</a>         <b><i>/* Conntrack defragments packets, we might still see fragments</i></b>
 <a name="L77" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L77">77</a> <b><i>         * inside ICMP packets though. */</i></b>
 <a name="L78" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L78">78</a>         if (iph-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_OFFSET">IP_OFFSET</a>))
 <a name="L79" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L79">79</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L80" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L81">81</a>         *dataoff = nhoff + (iph-&gt;ihl &lt;&lt; 2);
 <a name="L82" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L82">82</a>         *protonum = iph-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L83" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L84">84</a>         <b><i>/* Check bogus IP headers */</i></b>
 <a name="L85" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L85">85</a>         if (*dataoff &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) {
 <a name="L86" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L86">86</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_conntrack_ipv4: bogus IPv4 packet: "</i>
 <a name="L87" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L87">87</a>                          <i>"nhoff %u, ihl %u, skblen %u\n"</i>,
 <a name="L88" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L88">88</a>                          nhoff, iph-&gt;ihl &lt;&lt; 2, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
 <a name="L89" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L89">89</a>                 return -<a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L90" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L90">90</a>         }
 <a name="L91" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L92">92</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L93" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L93">93</a> }
 <a name="L94" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L95">95</a> static unsigned int <a href="ident?i=ipv4_helper">ipv4_helper</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L96" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L96">96</a>                                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L97" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L97">97</a>                                 const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L98" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L98">98</a> {
 <a name="L99" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L99">99</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L100" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L100">100</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L101" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L101">101</a>         const struct <a href="ident?i=nf_conn_help">nf_conn_help</a> *<a href="ident?i=help">help</a>;
<a name="L102" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L102">102</a>         const struct <a href="ident?i=nf_conntrack_helper">nf_conntrack_helper</a> *helper;
<a name="L103" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L104">104</a>         <b><i>/* This is where we call the helper: as the packet goes out. */</i></b>
<a name="L105" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L105">105</a>         ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
<a name="L106" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L106">106</a>         if (!ct || ctinfo == IP_CT_RELATED_REPLY)
<a name="L107" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L107">107</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L108" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L109">109</a>         <a href="ident?i=help">help</a> = <a href="ident?i=nfct_help">nfct_help</a>(ct);
<a name="L110" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L110">110</a>         if (!<a href="ident?i=help">help</a>)
<a name="L111" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L111">111</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L112" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L113">113</a>         <b><i>/* rcu_read_lock()ed by nf_hook_slow */</i></b>
<a name="L114" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L114">114</a>         helper = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=help">help</a>-&gt;helper);
<a name="L115" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L115">115</a>         if (!helper)
<a name="L116" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L116">116</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L117" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L118">118</a>         return helper-&gt;<a href="ident?i=help">help</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>),
<a name="L119" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L119">119</a>                             ct, ctinfo);
<a name="L120" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L120">120</a> }
<a name="L121" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L122">122</a> static unsigned int <a href="ident?i=ipv4_confirm">ipv4_confirm</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L123" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L123">123</a>                                  struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L124" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L124">124</a>                                  const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
<a name="L125" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L125">125</a> {
<a name="L126" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L126">126</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L127" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L127">127</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L128" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L129">129</a>         ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
<a name="L130" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L130">130</a>         if (!ct || ctinfo == IP_CT_RELATED_REPLY)
<a name="L131" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L131">131</a>                 goto <a href="ident?i=out">out</a>;
<a name="L132" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L133">133</a>         <b><i>/* adjust seqs for loopback traffic only in outgoing direction */</i></b>
<a name="L134" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L134">134</a>         if (<a href="ident?i=test_bit">test_bit</a>(IPS_SEQ_ADJUST_BIT, &amp;ct-&gt;<a href="ident?i=status">status</a>) &amp;&amp;
<a name="L135" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L135">135</a>             !<a href="ident?i=nf_is_loopback_packet">nf_is_loopback_packet</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L136" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L136">136</a>                 if (!<a href="ident?i=nf_ct_seq_adjust">nf_ct_seq_adjust</a>(<a href="ident?i=skb">skb</a>, ct, ctinfo, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>))) {
<a name="L137" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L137">137</a>                         <a href="ident?i=NF_CT_STAT_INC_ATOMIC">NF_CT_STAT_INC_ATOMIC</a>(<a href="ident?i=nf_ct_net">nf_ct_net</a>(ct), <a href="ident?i=drop">drop</a>);
<a name="L138" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L138">138</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L139" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L139">139</a>                 }
<a name="L140" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L140">140</a>         }
<a name="L141" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L141">141</a> <a href="ident?i=out">out</a>:
<a name="L142" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L142">142</a>         <b><i>/* We've seen it coming out the other side: confirm it */</i></b>
<a name="L143" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L143">143</a>         return <a href="ident?i=nf_conntrack_confirm">nf_conntrack_confirm</a>(<a href="ident?i=skb">skb</a>);
<a name="L144" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L144">144</a> }
<a name="L145" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L146">146</a> static unsigned int <a href="ident?i=ipv4_conntrack_in">ipv4_conntrack_in</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L147" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L147">147</a>                                       struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L148" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L148">148</a>                                       const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
<a name="L149" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L149">149</a> {
<a name="L150" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L150">150</a>         return <a href="ident?i=nf_conntrack_in">nf_conntrack_in</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>), <a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=skb">skb</a>);
<a name="L151" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L151">151</a> }
<a name="L152" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L153">153</a> static unsigned int <a href="ident?i=ipv4_conntrack_local">ipv4_conntrack_local</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L154" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L154">154</a>                                          struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L155" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L155">155</a>                                          const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
<a name="L156" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L156">156</a> {
<a name="L157" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L157">157</a>         <b><i>/* root is playing with raw sockets. */</i></b>
<a name="L158" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L158">158</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
<a name="L159" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L159">159</a>             <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>))
<a name="L160" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L160">160</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L161" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L161">161</a>         return <a href="ident?i=nf_conntrack_in">nf_conntrack_in</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>), <a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=skb">skb</a>);
<a name="L162" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L162">162</a> }
<a name="L163" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L164">164</a> <b><i>/* Connection tracking may drop packets, but never alters them, so</i></b>
<a name="L165" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L165">165</a> <b><i>   make it the first hook. */</i></b>
<a name="L166" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L166">166</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> ipv4_conntrack_ops[] <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L167" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L167">167</a>         {
<a name="L168" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L168">168</a>                 .hook           = <a href="ident?i=ipv4_conntrack_in">ipv4_conntrack_in</a>,
<a name="L169" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L169">169</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L170" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L170">170</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L171" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L171">171</a>                 .hooknum        = NF_INET_PRE_ROUTING,
<a name="L172" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L172">172</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK,
<a name="L173" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L173">173</a>         },
<a name="L174" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L174">174</a>         {
<a name="L175" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L175">175</a>                 .hook           = <a href="ident?i=ipv4_conntrack_local">ipv4_conntrack_local</a>,
<a name="L176" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L176">176</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L177" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L177">177</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L178" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L178">178</a>                 .hooknum        = NF_INET_LOCAL_OUT,
<a name="L179" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L179">179</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK,
<a name="L180" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L180">180</a>         },
<a name="L181" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L181">181</a>         {
<a name="L182" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L182">182</a>                 .hook           = <a href="ident?i=ipv4_helper">ipv4_helper</a>,
<a name="L183" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L183">183</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L184" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L184">184</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L185" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L185">185</a>                 .hooknum        = NF_INET_POST_ROUTING,
<a name="L186" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L186">186</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK_HELPER,
<a name="L187" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L187">187</a>         },
<a name="L188" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L188">188</a>         {
<a name="L189" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L189">189</a>                 .hook           = <a href="ident?i=ipv4_confirm">ipv4_confirm</a>,
<a name="L190" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L190">190</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L191" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L191">191</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L192" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L192">192</a>                 .hooknum        = NF_INET_POST_ROUTING,
<a name="L193" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L193">193</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK_CONFIRM,
<a name="L194" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L194">194</a>         },
<a name="L195" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L195">195</a>         {
<a name="L196" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L196">196</a>                 .hook           = <a href="ident?i=ipv4_helper">ipv4_helper</a>,
<a name="L197" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L197">197</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L198" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L198">198</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L199" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L199">199</a>                 .hooknum        = NF_INET_LOCAL_IN,
<a name="L200" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L200">200</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK_HELPER,
<a name="L201" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L201">201</a>         },
<a name="L202" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L202">202</a>         {
<a name="L203" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L203">203</a>                 .hook           = <a href="ident?i=ipv4_confirm">ipv4_confirm</a>,
<a name="L204" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L204">204</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L205" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L205">205</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L206" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L206">206</a>                 .hooknum        = NF_INET_LOCAL_IN,
<a name="L207" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L207">207</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK_CONFIRM,
<a name="L208" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L208">208</a>         },
<a name="L209" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L209">209</a> };
<a name="L210" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L211">211</a> #if defined(CONFIG_SYSCTL) &amp;&amp; defined(CONFIG_NF_CONNTRACK_PROC_COMPAT)
<a name="L212" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L212">212</a> static int <a href="ident?i=log_invalid_proto_min">log_invalid_proto_min</a> = 0;
<a name="L213" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L213">213</a> static int <a href="ident?i=log_invalid_proto_max">log_invalid_proto_max</a> = 255;
<a name="L214" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L215">215</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ip_ct_sysctl_table">ip_ct_sysctl_table</a>[] = {
<a name="L216" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L216">216</a>         {
<a name="L217" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L217">217</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_conntrack_max"</i>,
<a name="L218" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L218">218</a>                 .maxlen         = sizeof(int),
<a name="L219" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L219">219</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L220" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L220">220</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L221" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L221">221</a>         },
<a name="L222" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L222">222</a>         {
<a name="L223" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L223">223</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_conntrack_count"</i>,
<a name="L224" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L224">224</a>                 .maxlen         = sizeof(int),
<a name="L225" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L225">225</a>                 .<a href="ident?i=mode">mode</a>           = 0444,
<a name="L226" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L226">226</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L227" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L227">227</a>         },
<a name="L228" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L228">228</a>         {
<a name="L229" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L229">229</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_conntrack_buckets"</i>,
<a name="L230" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L230">230</a>                 .maxlen         = sizeof(unsigned int),
<a name="L231" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L231">231</a>                 .<a href="ident?i=mode">mode</a>           = 0444,
<a name="L232" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L232">232</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L233" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L233">233</a>         },
<a name="L234" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L234">234</a>         {
<a name="L235" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L235">235</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_conntrack_checksum"</i>,
<a name="L236" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L236">236</a>                 .maxlen         = sizeof(int),
<a name="L237" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L237">237</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L238" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L238">238</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L239" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L239">239</a>         },
<a name="L240" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L240">240</a>         {
<a name="L241" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L241">241</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_conntrack_log_invalid"</i>,
<a name="L242" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L242">242</a>                 .maxlen         = sizeof(unsigned int),
<a name="L243" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L243">243</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L244" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L244">244</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L245" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L245">245</a>                 .extra1         = &amp;<a href="ident?i=log_invalid_proto_min">log_invalid_proto_min</a>,
<a name="L246" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L246">246</a>                 .extra2         = &amp;<a href="ident?i=log_invalid_proto_max">log_invalid_proto_max</a>,
<a name="L247" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L247">247</a>         },
<a name="L248" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L248">248</a>         { }
<a name="L249" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L249">249</a> };
<a name="L250" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L250">250</a> #endif <b><i>/* CONFIG_SYSCTL &amp;&amp; CONFIG_NF_CONNTRACK_PROC_COMPAT */</i></b>
<a name="L251" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L252">252</a> <b><i>/* Fast function for those who don't want to parse /proc (and I don't</i></b>
<a name="L253" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L253">253</a> <b><i>   blame them). */</i></b>
<a name="L254" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L254">254</a> <b><i>/* Reversing the socket's dst/src point of view gives us the reply</i></b>
<a name="L255" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L255">255</a> <b><i>   mapping. */</i></b>
<a name="L256" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L256">256</a> static int
<a name="L257" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L257">257</a> <a href="ident?i=getorigdst">getorigdst</a>(struct <a href="ident?i=sock">sock</a> *sk, int optval, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, int *<a href="ident?i=len">len</a>)
<a name="L258" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L258">258</a> {
<a name="L259" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L259">259</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L260" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L260">260</a>         const struct <a href="ident?i=nf_conntrack_tuple_hash">nf_conntrack_tuple_hash</a> *<a href="ident?i=h">h</a>;
<a name="L261" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L261">261</a>         struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> tuple;
<a name="L262" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L263">263</a>         <a href="ident?i=memset">memset</a>(&amp;tuple, 0, sizeof(tuple));
<a name="L264" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L264">264</a>         tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L265" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L265">265</a>         tuple.<a href="ident?i=src">src</a>.u.tcp.<a href="ident?i=port">port</a> = inet-&gt;inet_sport;
<a name="L266" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L266">266</a>         tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L267" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L267">267</a>         tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a> = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L268" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L268">268</a>         tuple.<a href="ident?i=src">src</a>.l3num = <a href="ident?i=PF_INET">PF_INET</a>;
<a name="L269" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L269">269</a>         tuple.<a href="ident?i=dst">dst</a>.protonum = sk-&gt;sk_protocol;
<a name="L270" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L271">271</a>         <b><i>/* We only do TCP and SCTP at the moment: is there a better way? */</i></b>
<a name="L272" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L272">272</a>         if (sk-&gt;sk_protocol != <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> &amp;&amp; sk-&gt;sk_protocol != <a href="ident?i=IPPROTO_SCTP">IPPROTO_SCTP</a>) {
<a name="L273" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L273">273</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"SO_ORIGINAL_DST: Not a TCP/SCTP socket\n"</i>);
<a name="L274" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L274">274</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L275" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L275">275</a>         }
<a name="L276" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L277">277</a>         if ((unsigned int) *<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=sockaddr_in">sockaddr_in</a>)) {
<a name="L278" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L278">278</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"SO_ORIGINAL_DST: len %d not %Zu\n"</i>,
<a name="L279" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L279">279</a>                          *<a href="ident?i=len">len</a>, sizeof(struct <a href="ident?i=sockaddr_in">sockaddr_in</a>));
<a name="L280" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L280">280</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L281" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L283">283</a>         <a href="ident?i=h">h</a> = <a href="ident?i=nf_conntrack_find_get">nf_conntrack_find_get</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=NF_CT_DEFAULT_ZONE">NF_CT_DEFAULT_ZONE</a>, &amp;tuple);
<a name="L284" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L284">284</a>         if (<a href="ident?i=h">h</a>) {
<a name="L285" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L285">285</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a> <a href="ident?i=sin">sin</a>;
<a name="L286" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L286">286</a>                 struct <a href="ident?i=nf_conn">nf_conn</a> *ct = <a href="ident?i=nf_ct_tuplehash_to_ctrack">nf_ct_tuplehash_to_ctrack</a>(<a href="ident?i=h">h</a>);
<a name="L287" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L288">288</a>                 <a href="ident?i=sin">sin</a>.sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L289" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L289">289</a>                 <a href="ident?i=sin">sin</a>.sin_port = ct-&gt;tuplehash[IP_CT_DIR_ORIGINAL]
<a name="L290" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L290">290</a>                         .tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>;
<a name="L291" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L291">291</a>                 <a href="ident?i=sin">sin</a>.sin_addr.s_addr = ct-&gt;tuplehash[IP_CT_DIR_ORIGINAL]
<a name="L292" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L292">292</a>                         .tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
<a name="L293" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L293">293</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>.<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>.<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L294" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L295">295</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"SO_ORIGINAL_DST: %pI4 %u\n"</i>,
<a name="L296" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L296">296</a>                          &amp;<a href="ident?i=sin">sin</a>.sin_addr.s_addr, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=sin">sin</a>.sin_port));
<a name="L297" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L297">297</a>                 <a href="ident?i=nf_ct_put">nf_ct_put</a>(ct);
<a name="L298" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L298">298</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=user">user</a>, &amp;<a href="ident?i=sin">sin</a>, sizeof(<a href="ident?i=sin">sin</a>)) != 0)
<a name="L299" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L299">299</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L300" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L300">300</a>                 else
<a name="L301" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L301">301</a>                         return 0;
<a name="L302" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L302">302</a>         }
<a name="L303" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L303">303</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"SO_ORIGINAL_DST: Can't find %pI4/%u-%pI4/%u.\n"</i>,
<a name="L304" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L304">304</a>                  &amp;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>, <a href="ident?i=ntohs">ntohs</a>(tuple.<a href="ident?i=src">src</a>.u.tcp.<a href="ident?i=port">port</a>),
<a name="L305" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L305">305</a>                  &amp;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>, <a href="ident?i=ntohs">ntohs</a>(tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>));
<a name="L306" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L306">306</a>         return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L307" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L307">307</a> }
<a name="L308" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L309">309</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L310" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L311">311</a> #include &lt;linux/netfilter/nfnetlink.h&gt;
<a name="L312" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L312">312</a> #include &lt;linux/netfilter/nfnetlink_conntrack.h&gt;
<a name="L313" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L314">314</a> static int <a href="ident?i=ipv4_tuple_to_nlattr">ipv4_tuple_to_nlattr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L315" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L315">315</a>                                 const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple)
<a name="L316" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L316">316</a> {
<a name="L317" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L317">317</a>         if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, CTA_IP_V4_SRC, tuple-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>) ||
<a name="L318" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L318">318</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, CTA_IP_V4_DST, tuple-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>))
<a name="L319" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L319">319</a>                 goto nla_put_failure;
<a name="L320" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L320">320</a>         return 0;
<a name="L321" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L322">322</a> nla_put_failure:
<a name="L323" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L323">323</a>         return -1;
<a name="L324" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L324">324</a> }
<a name="L325" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L326">326</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=ipv4_nla_policy">ipv4_nla_policy</a>[<a href="ident?i=CTA_IP_MAX">CTA_IP_MAX</a>+1] = {
<a name="L327" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L327">327</a>         [CTA_IP_V4_SRC] = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L328" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L328">328</a>         [CTA_IP_V4_DST] = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L329" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L329">329</a> };
<a name="L330" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L331">331</a> static int <a href="ident?i=ipv4_nlattr_to_tuple">ipv4_nlattr_to_tuple</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L332" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L332">332</a>                                 struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=t">t</a>)
<a name="L333" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L333">333</a> {
<a name="L334" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L334">334</a>         if (!<a href="ident?i=tb">tb</a>[CTA_IP_V4_SRC] || !<a href="ident?i=tb">tb</a>[CTA_IP_V4_DST])
<a name="L335" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L335">335</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L336" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L337">337</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[CTA_IP_V4_SRC]);
<a name="L338" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L338">338</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[CTA_IP_V4_DST]);
<a name="L339" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L339">339</a> 
<a name="L340" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L340">340</a>         return 0;
<a name="L341" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L341">341</a> }
<a name="L342" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L343">343</a> static int <a href="ident?i=ipv4_nlattr_tuple_size">ipv4_nlattr_tuple_size</a>(void)
<a name="L344" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L344">344</a> {
<a name="L345" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L345">345</a>         return <a href="ident?i=nla_policy_len">nla_policy_len</a>(<a href="ident?i=ipv4_nla_policy">ipv4_nla_policy</a>, <a href="ident?i=CTA_IP_MAX">CTA_IP_MAX</a> + 1);
<a name="L346" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L346">346</a> }
<a name="L347" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L347">347</a> #endif
<a name="L348" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L349">349</a> static struct <a href="ident?i=nf_sockopt_ops">nf_sockopt_ops</a> <a href="ident?i=so_getorigdst">so_getorigdst</a> = {
<a name="L350" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L350">350</a>         .<a href="ident?i=pf">pf</a>             = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L351" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L351">351</a>         .get_optmin     = <a href="ident?i=SO_ORIGINAL_DST">SO_ORIGINAL_DST</a>,
<a name="L352" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L352">352</a>         .get_optmax     = <a href="ident?i=SO_ORIGINAL_DST">SO_ORIGINAL_DST</a>+1,
<a name="L353" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L353">353</a>         .<a href="ident?i=get">get</a>            = <a href="ident?i=getorigdst">getorigdst</a>,
<a name="L354" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L354">354</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L355" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L355">355</a> };
<a name="L356" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L357">357</a> static int <a href="ident?i=ipv4_init_net">ipv4_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L358" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L358">358</a> {
<a name="L359" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L359">359</a> #if defined(CONFIG_SYSCTL) &amp;&amp; defined(CONFIG_NF_CONNTRACK_PROC_COMPAT)
<a name="L360" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L360">360</a>         struct <a href="ident?i=nf_ip_net">nf_ip_net</a> *<a href="ident?i=in">in</a> = &amp;<a href="ident?i=net">net</a>-&gt;ct.nf_ct_proto;
<a name="L361" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L361">361</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=ip_ct_sysctl_table">ip_ct_sysctl_table</a>,
<a name="L362" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L362">362</a>                                 sizeof(<a href="ident?i=ip_ct_sysctl_table">ip_ct_sysctl_table</a>),
<a name="L363" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L363">363</a>                                 <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L364" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L364">364</a>         if (!<a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a>)
<a name="L365" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L365">365</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L366" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L367">367</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a>[0].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=nf_conntrack_max">nf_conntrack_max</a>;
<a name="L368" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L368">368</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a>[1].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=count">count</a>;
<a name="L369" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L369">369</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a>[2].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=htable_size">htable_size</a>;
<a name="L370" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L370">370</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a>[3].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ct.sysctl_checksum;
<a name="L371" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L371">371</a>         <a href="ident?i=in">in</a>-&gt;<a href="ident?i=ctl_table">ctl_table</a>[4].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ct.sysctl_log_invalid;
<a name="L372" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L372">372</a> #endif
<a name="L373" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L373">373</a>         return 0;
<a name="L374" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L374">374</a> }
<a name="L375" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L376">376</a> struct <a href="ident?i=nf_conntrack_l3proto">nf_conntrack_l3proto</a> <a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L377" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L377">377</a>         .l3proto         = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L378" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L378">378</a>         .<a href="ident?i=name">name</a>            = <i>"ipv4"</i>,
<a name="L379" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L379">379</a>         .pkt_to_tuple    = <a href="ident?i=ipv4_pkt_to_tuple">ipv4_pkt_to_tuple</a>,
<a name="L380" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L380">380</a>         .invert_tuple    = <a href="ident?i=ipv4_invert_tuple">ipv4_invert_tuple</a>,
<a name="L381" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L381">381</a>         .<a href="ident?i=print_tuple">print_tuple</a>     = <a href="ident?i=ipv4_print_tuple">ipv4_print_tuple</a>,
<a name="L382" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L382">382</a>         .get_l4proto     = <a href="ident?i=ipv4_get_l4proto">ipv4_get_l4proto</a>,
<a name="L383" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L383">383</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L384" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L384">384</a>         .tuple_to_nlattr = <a href="ident?i=ipv4_tuple_to_nlattr">ipv4_tuple_to_nlattr</a>,
<a name="L385" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L385">385</a>         .nlattr_tuple_size = <a href="ident?i=ipv4_nlattr_tuple_size">ipv4_nlattr_tuple_size</a>,
<a name="L386" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L386">386</a>         .nlattr_to_tuple = <a href="ident?i=ipv4_nlattr_to_tuple">ipv4_nlattr_to_tuple</a>,
<a name="L387" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L387">387</a>         .<a href="ident?i=nla_policy">nla_policy</a>      = <a href="ident?i=ipv4_nla_policy">ipv4_nla_policy</a>,
<a name="L388" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L388">388</a> #endif
<a name="L389" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L389">389</a> #if defined(CONFIG_SYSCTL) &amp;&amp; defined(CONFIG_NF_CONNTRACK_PROC_COMPAT)
<a name="L390" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L390">390</a>         .ctl_table_path  = <i>"net/ipv4/netfilter"</i>,
<a name="L391" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L391">391</a> #endif
<a name="L392" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L392">392</a>         .<a href="ident?i=init_net">init_net</a>        = <a href="ident?i=ipv4_init_net">ipv4_init_net</a>,
<a name="L393" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L393">393</a>         .<a href="ident?i=me">me</a>              = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L394" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L394">394</a> };
<a name="L395" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L396">396</a> <a href="ident?i=module_param_call">module_param_call</a>(hashsize, <a href="ident?i=nf_conntrack_set_hashsize">nf_conntrack_set_hashsize</a>, <a href="ident?i=param_get_uint">param_get_uint</a>,
<a name="L397" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L397">397</a>                   &amp;<a href="ident?i=nf_conntrack_htable_size">nf_conntrack_htable_size</a>, 0600);
<a name="L398" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L399">399</a> <a href="ident?i=MODULE_ALIAS">MODULE_ALIAS</a>(<i>"nf_conntrack-"</i> <a href="ident?i=__stringify">__stringify</a>(<a href="ident?i=AF_INET">AF_INET</a>));
<a name="L400" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L400">400</a> <a href="ident?i=MODULE_ALIAS">MODULE_ALIAS</a>(<i>"ip_conntrack"</i>);
<a name="L401" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L401">401</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L402" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L402">402</a> 
<a name="L403" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L403">403</a> static int <a href="ident?i=ipv4_net_init">ipv4_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L404" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L404">404</a> {
<a name="L405" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L405">405</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L406" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L407">407</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l4proto_pernet_register">nf_ct_l4proto_pernet_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_tcp4">nf_conntrack_l4proto_tcp4</a>);
<a name="L408" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L408">408</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L409" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L409">409</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_tcp4: pernet registration failed\n"</i>);
<a name="L410" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L410">410</a>                 goto out_tcp;
<a name="L411" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L411">411</a>         }
<a name="L412" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L412">412</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l4proto_pernet_register">nf_ct_l4proto_pernet_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_udp4">nf_conntrack_l4proto_udp4</a>);
<a name="L413" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L413">413</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L414" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L414">414</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_udp4: pernet registration failed\n"</i>);
<a name="L415" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L415">415</a>                 goto out_udp;
<a name="L416" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L416">416</a>         }
<a name="L417" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L417">417</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l4proto_pernet_register">nf_ct_l4proto_pernet_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a>);
<a name="L418" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L418">418</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L419" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L419">419</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_icmp4: pernet registration failed\n"</i>);
<a name="L420" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L420">420</a>                 goto out_icmp;
<a name="L421" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L421">421</a>         }
<a name="L422" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L422">422</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l3proto_pernet_register">nf_ct_l3proto_pernet_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a>);
<a name="L423" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L423">423</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L424" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L424">424</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: pernet registration failed\n"</i>);
<a name="L425" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L425">425</a>                 goto out_ipv4;
<a name="L426" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L426">426</a>         }
<a name="L427" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L427">427</a>         return 0;
<a name="L428" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L428">428</a> out_ipv4:
<a name="L429" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L429">429</a>         <a href="ident?i=nf_ct_l4proto_pernet_unregister">nf_ct_l4proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a>);
<a name="L430" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L430">430</a> out_icmp:
<a name="L431" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L431">431</a>         <a href="ident?i=nf_ct_l4proto_pernet_unregister">nf_ct_l4proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_udp4">nf_conntrack_l4proto_udp4</a>);
<a name="L432" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L432">432</a> out_udp:
<a name="L433" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L433">433</a>         <a href="ident?i=nf_ct_l4proto_pernet_unregister">nf_ct_l4proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_tcp4">nf_conntrack_l4proto_tcp4</a>);
<a name="L434" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L434">434</a> out_tcp:
<a name="L435" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L435">435</a>         return <a href="ident?i=ret">ret</a>;
<a name="L436" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L436">436</a> }
<a name="L437" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L438">438</a> static void <a href="ident?i=ipv4_net_exit">ipv4_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L439" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L439">439</a> {
<a name="L440" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L440">440</a>         <a href="ident?i=nf_ct_l3proto_pernet_unregister">nf_ct_l3proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a>);
<a name="L441" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L441">441</a>         <a href="ident?i=nf_ct_l4proto_pernet_unregister">nf_ct_l4proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a>);
<a name="L442" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L442">442</a>         <a href="ident?i=nf_ct_l4proto_pernet_unregister">nf_ct_l4proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_udp4">nf_conntrack_l4proto_udp4</a>);
<a name="L443" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L443">443</a>         <a href="ident?i=nf_ct_l4proto_pernet_unregister">nf_ct_l4proto_pernet_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_conntrack_l4proto_tcp4">nf_conntrack_l4proto_tcp4</a>);
<a name="L444" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L444">444</a> }
<a name="L445" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L446">446</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipv4_net_ops">ipv4_net_ops</a> = {
<a name="L447" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L447">447</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipv4_net_init">ipv4_net_init</a>,
<a name="L448" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L448">448</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipv4_net_exit">ipv4_net_exit</a>,
<a name="L449" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L449">449</a> };
<a name="L450" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L450">450</a> 
<a name="L451" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L451">451</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_conntrack_l3proto_ipv4_init">nf_conntrack_l3proto_ipv4_init</a>(void)
<a name="L452" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L452">452</a> {
<a name="L453" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L453">453</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L454" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L455">455</a>         <a href="ident?i=need_conntrack">need_conntrack</a>();
<a name="L456" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L456">456</a>         <a href="ident?i=nf_defrag_ipv4_enable">nf_defrag_ipv4_enable</a>();
<a name="L457" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L458">458</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_register_sockopt">nf_register_sockopt</a>(&amp;<a href="ident?i=so_getorigdst">so_getorigdst</a>);
<a name="L459" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L459">459</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L460" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L460">460</a>                 <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_ERR">KERN_ERR</a> <i>"Unable to register netfilter socket option\n"</i>);
<a name="L461" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L461">461</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L462" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L462">462</a>         }
<a name="L463" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L463">463</a> 
<a name="L464" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L464">464</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ipv4_net_ops">ipv4_net_ops</a>);
<a name="L465" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L465">465</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L466" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L466">466</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: can't register pernet ops\n"</i>);
<a name="L467" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L467">467</a>                 goto cleanup_sockopt;
<a name="L468" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L468">468</a>         }
<a name="L469" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L470">470</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_register_hooks">nf_register_hooks</a>(ipv4_conntrack_ops,
<a name="L471" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L471">471</a>                                 <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipv4_conntrack_ops));
<a name="L472" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L472">472</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L473" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L473">473</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: can't register hooks.\n"</i>);
<a name="L474" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L474">474</a>                 goto cleanup_pernet;
<a name="L475" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L475">475</a>         }
<a name="L476" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L477">477</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l4proto_register">nf_ct_l4proto_register</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_tcp4">nf_conntrack_l4proto_tcp4</a>);
<a name="L478" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L478">478</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L479" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L479">479</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: can't register tcp4 proto.\n"</i>);
<a name="L480" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L480">480</a>                 goto cleanup_hooks;
<a name="L481" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L481">481</a>         }
<a name="L482" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L483">483</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l4proto_register">nf_ct_l4proto_register</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_udp4">nf_conntrack_l4proto_udp4</a>);
<a name="L484" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L484">484</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L485" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L485">485</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: can't register udp4 proto.\n"</i>);
<a name="L486" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L486">486</a>                 goto cleanup_tcp4;
<a name="L487" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L487">487</a>         }
<a name="L488" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L488">488</a> 
<a name="L489" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L489">489</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l4proto_register">nf_ct_l4proto_register</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a>);
<a name="L490" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L490">490</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L491" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L491">491</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: can't register icmpv4 proto.\n"</i>);
<a name="L492" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L492">492</a>                 goto cleanup_udp4;
<a name="L493" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L493">493</a>         }
<a name="L494" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L494">494</a> 
<a name="L495" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L495">495</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l3proto_register">nf_ct_l3proto_register</a>(&amp;<a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a>);
<a name="L496" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L496">496</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L497" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L497">497</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"nf_conntrack_ipv4: can't register ipv4 proto.\n"</i>);
<a name="L498" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L498">498</a>                 goto cleanup_icmpv4;
<a name="L499" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L499">499</a>         }
<a name="L500" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L501">501</a> #if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_NF_CONNTRACK_PROC_COMPAT)
<a name="L502" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L502">502</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_conntrack_ipv4_compat_init">nf_conntrack_ipv4_compat_init</a>();
<a name="L503" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L503">503</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L504" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L504">504</a>                 goto cleanup_proto;
<a name="L505" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L505">505</a> #endif
<a name="L506" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L506">506</a>         return <a href="ident?i=ret">ret</a>;
<a name="L507" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L507">507</a> #if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_NF_CONNTRACK_PROC_COMPAT)
<a name="L508" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L508">508</a>  cleanup_proto:
<a name="L509" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L509">509</a>         <a href="ident?i=nf_ct_l3proto_unregister">nf_ct_l3proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a>);
<a name="L510" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L510">510</a> #endif
<a name="L511" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L511">511</a>  cleanup_icmpv4:
<a name="L512" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L512">512</a>         <a href="ident?i=nf_ct_l4proto_unregister">nf_ct_l4proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a>);
<a name="L513" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L513">513</a>  cleanup_udp4:
<a name="L514" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L514">514</a>         <a href="ident?i=nf_ct_l4proto_unregister">nf_ct_l4proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_udp4">nf_conntrack_l4proto_udp4</a>);
<a name="L515" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L515">515</a>  cleanup_tcp4:
<a name="L516" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L516">516</a>         <a href="ident?i=nf_ct_l4proto_unregister">nf_ct_l4proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_tcp4">nf_conntrack_l4proto_tcp4</a>);
<a name="L517" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L517">517</a>  cleanup_hooks:
<a name="L518" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L518">518</a>         <a href="ident?i=nf_unregister_hooks">nf_unregister_hooks</a>(ipv4_conntrack_ops, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipv4_conntrack_ops));
<a name="L519" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L519">519</a>  cleanup_pernet:
<a name="L520" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L520">520</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ipv4_net_ops">ipv4_net_ops</a>);
<a name="L521" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L521">521</a>  cleanup_sockopt:
<a name="L522" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L522">522</a>         <a href="ident?i=nf_unregister_sockopt">nf_unregister_sockopt</a>(&amp;<a href="ident?i=so_getorigdst">so_getorigdst</a>);
<a name="L523" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L523">523</a>         return <a href="ident?i=ret">ret</a>;
<a name="L524" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L524">524</a> }
<a name="L525" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L526">526</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_conntrack_l3proto_ipv4_fini">nf_conntrack_l3proto_ipv4_fini</a>(void)
<a name="L527" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L527">527</a> {
<a name="L528" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L528">528</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
<a name="L529" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L529">529</a> #if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_NF_CONNTRACK_PROC_COMPAT)
<a name="L530" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L530">530</a>         <a href="ident?i=nf_conntrack_ipv4_compat_fini">nf_conntrack_ipv4_compat_fini</a>();
<a name="L531" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L531">531</a> #endif
<a name="L532" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L532">532</a>         <a href="ident?i=nf_ct_l3proto_unregister">nf_ct_l3proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l3proto_ipv4">nf_conntrack_l3proto_ipv4</a>);
<a name="L533" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L533">533</a>         <a href="ident?i=nf_ct_l4proto_unregister">nf_ct_l4proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_icmp">nf_conntrack_l4proto_icmp</a>);
<a name="L534" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L534">534</a>         <a href="ident?i=nf_ct_l4proto_unregister">nf_ct_l4proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_udp4">nf_conntrack_l4proto_udp4</a>);
<a name="L535" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L535">535</a>         <a href="ident?i=nf_ct_l4proto_unregister">nf_ct_l4proto_unregister</a>(&amp;<a href="ident?i=nf_conntrack_l4proto_tcp4">nf_conntrack_l4proto_tcp4</a>);
<a name="L536" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L536">536</a>         <a href="ident?i=nf_unregister_hooks">nf_unregister_hooks</a>(ipv4_conntrack_ops, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipv4_conntrack_ops));
<a name="L537" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L537">537</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ipv4_net_ops">ipv4_net_ops</a>);
<a name="L538" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L538">538</a>         <a href="ident?i=nf_unregister_sockopt">nf_unregister_sockopt</a>(&amp;<a href="ident?i=so_getorigdst">so_getorigdst</a>);
<a name="L539" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L539">539</a> }
<a name="L540" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L541">541</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_conntrack_l3proto_ipv4_init">nf_conntrack_l3proto_ipv4_init</a>);
<a name="L542" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L542">542</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_conntrack_l3proto_ipv4_fini">nf_conntrack_l3proto_ipv4_fini</a>);
<a name="L543" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4.c#L543">543</a> </pre></div><p>
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
