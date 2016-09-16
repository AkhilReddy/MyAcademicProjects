<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c">nf_nat_l3proto_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L2">2</a> <b><i> * (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L3">3</a> <b><i> * (C) 2002-2006 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L4">4</a> <b><i> * (C) 2011 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L6">6</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L7">7</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L8">8</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L11">11</a> #include &lt;linux/types.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L12">12</a> #include &lt;linux/module.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L13">13</a> #include &lt;linux/skbuff.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L14">14</a> #include &lt;linux/ip.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L15">15</a> #include &lt;linux/icmp.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L16">16</a> #include &lt;linux/netfilter.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L17">17</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L18">18</a> #include &lt;net/secure_seq.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L19">19</a> #include &lt;net/checksum.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L20">20</a> #include &lt;net/route.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L21">21</a> #include &lt;net/ip.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L23">23</a> #include &lt;net/netfilter/nf_conntrack_core.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L24">24</a> #include &lt;net/netfilter/nf_conntrack.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L25">25</a> #include &lt;net/netfilter/nf_nat_core.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L26">26</a> #include &lt;net/netfilter/nf_nat_l3proto.h&gt;
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L27">27</a> #include &lt;net/netfilter/nf_nat_l4proto.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L29">29</a> static const struct <a href="ident?i=nf_nat_l3proto">nf_nat_l3proto</a> <a href="ident?i=nf_nat_l3proto_ipv4">nf_nat_l3proto_ipv4</a>;
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L31">31</a> #ifdef CONFIG_XFRM
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L32">32</a> static void <a href="ident?i=nf_nat_ipv4_decode_session">nf_nat_ipv4_decode_session</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L33">33</a>                                        const struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L34">34</a>                                        enum <a href="ident?i=ip_conntrack_dir">ip_conntrack_dir</a> <a href="ident?i=dir">dir</a>,
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L35">35</a>                                        unsigned long statusbit,
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L36">36</a>                                        struct <a href="ident?i=flowi">flowi</a> *fl)
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L37">37</a> {
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L38">38</a>         const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=t">t</a> = &amp;ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple;
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L39">39</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4 = &amp;fl-&gt;u.ip4;
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L41">41</a>         if (ct-&gt;<a href="ident?i=status">status</a> &amp; statusbit) {
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L42">42</a>                 fl4-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L43">43</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> ||
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L44">44</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a> ||
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L45">45</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a> ||
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L46">46</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_DCCP">IPPROTO_DCCP</a> ||
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L47">47</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_SCTP">IPPROTO_SCTP</a>)
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L48">48</a>                         fl4-&gt;<a href="ident?i=fl4_dport">fl4_dport</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u.<a href="ident?i=all">all</a>;
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L49">49</a>         }
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L51">51</a>         statusbit ^= IPS_NAT_MASK;
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L53">53</a>         if (ct-&gt;<a href="ident?i=status">status</a> &amp; statusbit) {
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L54">54</a>                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L55">55</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> ||
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L56">56</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a> ||
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L57">57</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a> ||
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L58">58</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_DCCP">IPPROTO_DCCP</a> ||
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L59">59</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.protonum == <a href="ident?i=IPPROTO_SCTP">IPPROTO_SCTP</a>)
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L60">60</a>                         fl4-&gt;<a href="ident?i=fl4_sport">fl4_sport</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u.<a href="ident?i=all">all</a>;
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L61">61</a>         }
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L62">62</a> }
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L63">63</a> #endif <b><i>/* CONFIG_XFRM */</i></b>
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L65">65</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=nf_nat_ipv4_in_range">nf_nat_ipv4_in_range</a>(const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=t">t</a>,
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L66">66</a>                                  const struct <a href="ident?i=nf_nat_range">nf_nat_range</a> *<a href="ident?i=range">range</a>)
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L67">67</a> {
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L68">68</a>         return <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>) &gt;= <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_addr">min_addr</a>.<a href="ident?i=ip">ip</a>) &amp;&amp;
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L69">69</a>                <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>) &lt;= <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=max_addr">max_addr</a>.<a href="ident?i=ip">ip</a>);
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L70">70</a> }
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L72">72</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=nf_nat_ipv4_secure_port">nf_nat_ipv4_secure_port</a>(const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=t">t</a>,
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L73">73</a>                                    <a href="ident?i=__be16">__be16</a> dport)
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L74">74</a> {
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L75">75</a>         return <a href="ident?i=secure_ipv4_port_ephemeral">secure_ipv4_port_ephemeral</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>, dport);
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L76">76</a> }
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L78">78</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=nf_nat_ipv4_manip_pkt">nf_nat_ipv4_manip_pkt</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L79">79</a>                                   unsigned int iphdroff,
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L80">80</a>                                   const struct <a href="ident?i=nf_nat_l4proto">nf_nat_l4proto</a> *l4proto,
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L81">81</a>                                   const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=target">target</a>,
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L82">82</a>                                   enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype)
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L84">84</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L85" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L85">85</a>         unsigned int hdroff;
 <a name="L86" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L87">87</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, iphdroff + sizeof(*iph)))
 <a name="L88" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L88">88</a>                 return <a href="ident?i=false">false</a>;
 <a name="L89" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L90">90</a>         iph = (void *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + iphdroff;
 <a name="L91" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L91">91</a>         hdroff = iphdroff + iph-&gt;ihl * 4;
 <a name="L92" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L93">93</a>         if (!l4proto-&gt;manip_pkt(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=nf_nat_l3proto_ipv4">nf_nat_l3proto_ipv4</a>, iphdroff, hdroff,
 <a name="L94" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L94">94</a>                                 <a href="ident?i=target">target</a>, maniptype))
 <a name="L95" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L95">95</a>                 return <a href="ident?i=false">false</a>;
 <a name="L96" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L96">96</a>         iph = (void *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + iphdroff;
 <a name="L97" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L98">98</a>         if (maniptype == NF_NAT_MANIP_SRC) {
 <a name="L99" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L99">99</a>                 <a href="ident?i=csum_replace4">csum_replace4</a>(&amp;iph-&gt;<a href="ident?i=check">check</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=target">target</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>);
<a name="L100" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L100">100</a>                 iph-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=target">target</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>;
<a name="L101" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L101">101</a>         } else {
<a name="L102" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L102">102</a>                 <a href="ident?i=csum_replace4">csum_replace4</a>(&amp;iph-&gt;<a href="ident?i=check">check</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=target">target</a>-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>);
<a name="L103" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L103">103</a>                 iph-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=target">target</a>-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
<a name="L104" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L104">104</a>         }
<a name="L105" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L105">105</a>         return <a href="ident?i=true">true</a>;
<a name="L106" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L106">106</a> }
<a name="L107" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L108">108</a> static void <a href="ident?i=nf_nat_ipv4_csum_update">nf_nat_ipv4_csum_update</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L109" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L109">109</a>                                     unsigned int iphdroff, <a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=check">check</a>,
<a name="L110" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L110">110</a>                                     const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *<a href="ident?i=t">t</a>,
<a name="L111" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L111">111</a>                                     enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype)
<a name="L112" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L112">112</a> {
<a name="L113" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L113">113</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = (struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + iphdroff);
<a name="L114" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L114">114</a>         <a href="ident?i=__be32">__be32</a> oldip, newip;
<a name="L115" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L116">116</a>         if (maniptype == NF_NAT_MANIP_SRC) {
<a name="L117" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L117">117</a>                 oldip = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L118" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L118">118</a>                 newip = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>;
<a name="L119" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L119">119</a>         } else {
<a name="L120" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L120">120</a>                 oldip = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L121" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L121">121</a>                 newip = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
<a name="L122" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L122">122</a>         }
<a name="L123" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L123">123</a>         <a href="ident?i=inet_proto_csum_replace4">inet_proto_csum_replace4</a>(<a href="ident?i=check">check</a>, <a href="ident?i=skb">skb</a>, oldip, newip, 1);
<a name="L124" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L126">126</a> static void <a href="ident?i=nf_nat_ipv4_csum_recalc">nf_nat_ipv4_csum_recalc</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L127" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L127">127</a>                                     <a href="ident?i=u8">u8</a> <a href="ident?i=proto">proto</a>, void *<a href="ident?i=data">data</a>, <a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=check">check</a>,
<a name="L128" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L128">128</a>                                     int datalen, int oldlen)
<a name="L129" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L129">129</a> {
<a name="L130" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L130">130</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L131" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L131">131</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L132" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L133">133</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) {
<a name="L134" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L134">134</a>                 if (!(<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>) &amp;&amp;
<a name="L135" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L135">135</a>                     (!<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> || <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=NETIF_F_V4_CSUM">NETIF_F_V4_CSUM</a>)) {
<a name="L136" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L136">136</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L137" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L137">137</a>                         <a href="ident?i=skb">skb</a>-&gt;csum_start = <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>) +
<a name="L138" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L138">138</a>                                           <a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>) +
<a name="L139" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L139">139</a>                                           <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L140" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L140">140</a>                         <a href="ident?i=skb">skb</a>-&gt;csum_offset = (void *)<a href="ident?i=check">check</a> - <a href="ident?i=data">data</a>;
<a name="L141" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L141">141</a>                         *<a href="ident?i=check">check</a> = ~csum_tcpudp_magic(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L142" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L142">142</a>                                                     datalen, <a href="ident?i=proto">proto</a>, 0);
<a name="L143" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L143">143</a>                 } else {
<a name="L144" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L144">144</a>                         *<a href="ident?i=check">check</a> = 0;
<a name="L145" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L145">145</a>                         *<a href="ident?i=check">check</a> = <a href="ident?i=csum_tcpudp_magic">csum_tcpudp_magic</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L146" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L146">146</a>                                                    datalen, <a href="ident?i=proto">proto</a>,
<a name="L147" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L147">147</a>                                                    <a href="ident?i=csum_partial">csum_partial</a>(<a href="ident?i=data">data</a>, datalen,
<a name="L148" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L148">148</a>                                                                 0));
<a name="L149" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L149">149</a>                         if (<a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a> &amp;&amp; !*<a href="ident?i=check">check</a>)
<a name="L150" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L150">150</a>                                 *<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L151" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L151">151</a>                 }
<a name="L152" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L152">152</a>         } else
<a name="L153" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L153">153</a>                 <a href="ident?i=inet_proto_csum_replace2">inet_proto_csum_replace2</a>(<a href="ident?i=check">check</a>, <a href="ident?i=skb">skb</a>,
<a name="L154" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L154">154</a>                                          <a href="ident?i=htons">htons</a>(oldlen), <a href="ident?i=htons">htons</a>(datalen), 1);
<a name="L155" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L155">155</a> }
<a name="L156" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L157">157</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L158" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L158">158</a> static int <a href="ident?i=nf_nat_ipv4_nlattr_to_range">nf_nat_ipv4_nlattr_to_range</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L159" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L159">159</a>                                        struct <a href="ident?i=nf_nat_range">nf_nat_range</a> *<a href="ident?i=range">range</a>)
<a name="L160" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L160">160</a> {
<a name="L161" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L161">161</a>         if (<a href="ident?i=tb">tb</a>[CTA_NAT_V4_MINIP]) {
<a name="L162" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L162">162</a>                 <a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_addr">min_addr</a>.<a href="ident?i=ip">ip</a> = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=tb">tb</a>[CTA_NAT_V4_MINIP]);
<a name="L163" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L163">163</a>                 <a href="ident?i=range">range</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>;
<a name="L164" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L164">164</a>         }
<a name="L165" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L166">166</a>         if (<a href="ident?i=tb">tb</a>[CTA_NAT_V4_MAXIP])
<a name="L167" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L167">167</a>                 <a href="ident?i=range">range</a>-&gt;<a href="ident?i=max_addr">max_addr</a>.<a href="ident?i=ip">ip</a> = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=tb">tb</a>[CTA_NAT_V4_MAXIP]);
<a name="L168" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L168">168</a>         else
<a name="L169" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L169">169</a>                 <a href="ident?i=range">range</a>-&gt;<a href="ident?i=max_addr">max_addr</a>.<a href="ident?i=ip">ip</a> = <a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_addr">min_addr</a>.<a href="ident?i=ip">ip</a>;
<a name="L170" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L171">171</a>         return 0;
<a name="L172" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L172">172</a> }
<a name="L173" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L173">173</a> #endif
<a name="L174" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L175">175</a> static const struct <a href="ident?i=nf_nat_l3proto">nf_nat_l3proto</a> <a href="ident?i=nf_nat_l3proto_ipv4">nf_nat_l3proto_ipv4</a> = {
<a name="L176" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L176">176</a>         .l3proto                = NFPROTO_IPV4,
<a name="L177" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L177">177</a>         .<a href="ident?i=in_range">in_range</a>               = <a href="ident?i=nf_nat_ipv4_in_range">nf_nat_ipv4_in_range</a>,
<a name="L178" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L178">178</a>         .secure_port            = <a href="ident?i=nf_nat_ipv4_secure_port">nf_nat_ipv4_secure_port</a>,
<a name="L179" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L179">179</a>         .manip_pkt              = <a href="ident?i=nf_nat_ipv4_manip_pkt">nf_nat_ipv4_manip_pkt</a>,
<a name="L180" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L180">180</a>         .csum_update            = <a href="ident?i=nf_nat_ipv4_csum_update">nf_nat_ipv4_csum_update</a>,
<a name="L181" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L181">181</a>         .csum_recalc            = <a href="ident?i=nf_nat_ipv4_csum_recalc">nf_nat_ipv4_csum_recalc</a>,
<a name="L182" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L182">182</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L183" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L183">183</a>         .nlattr_to_range        = <a href="ident?i=nf_nat_ipv4_nlattr_to_range">nf_nat_ipv4_nlattr_to_range</a>,
<a name="L184" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L184">184</a> #endif
<a name="L185" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L185">185</a> #ifdef CONFIG_XFRM
<a name="L186" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L186">186</a>         .decode_session         = <a href="ident?i=nf_nat_ipv4_decode_session">nf_nat_ipv4_decode_session</a>,
<a name="L187" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L187">187</a> #endif
<a name="L188" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L188">188</a> };
<a name="L189" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L190">190</a> int <a href="ident?i=nf_nat_icmp_reply_translation">nf_nat_icmp_reply_translation</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L191" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L191">191</a>                                   struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L192" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L192">192</a>                                   enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L193" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L193">193</a>                                   unsigned int hooknum)
<a name="L194" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L194">194</a> {
<a name="L195" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L195">195</a>         struct {
<a name="L196" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L196">196</a>                 struct <a href="ident?i=icmphdr">icmphdr</a>  icmp;
<a name="L197" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L197">197</a>                 struct <a href="ident?i=iphdr">iphdr</a>    <a href="ident?i=ip">ip</a>;
<a name="L198" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L198">198</a>         } *<a href="ident?i=inside">inside</a>;
<a name="L199" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L199">199</a>         enum <a href="ident?i=ip_conntrack_dir">ip_conntrack_dir</a> <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L200" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L200">200</a>         enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> manip = <a href="ident?i=HOOK2MANIP">HOOK2MANIP</a>(hooknum);
<a name="L201" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L201">201</a>         unsigned int hdrlen = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L202" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L202">202</a>         const struct <a href="ident?i=nf_nat_l4proto">nf_nat_l4proto</a> *l4proto;
<a name="L203" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L203">203</a>         struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> <a href="ident?i=target">target</a>;
<a name="L204" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L204">204</a>         unsigned long statusbit;
<a name="L205" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L206">206</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(ctinfo == IP_CT_RELATED || ctinfo == IP_CT_RELATED_REPLY);
<a name="L207" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L208">208</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, hdrlen + sizeof(*<a href="ident?i=inside">inside</a>)))
<a name="L209" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L209">209</a>                 return 0;
<a name="L210" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L210">210</a>         if (<a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(<a href="ident?i=skb">skb</a>, hooknum, hdrlen, 0))
<a name="L211" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L211">211</a>                 return 0;
<a name="L212" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L213">213</a>         <a href="ident?i=inside">inside</a> = (void *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + hdrlen;
<a name="L214" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L214">214</a>         if (<a href="ident?i=inside">inside</a>-&gt;icmp.<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>) {
<a name="L215" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L215">215</a>                 if ((ct-&gt;<a href="ident?i=status">status</a> &amp; IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
<a name="L216" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L216">216</a>                         return 0;
<a name="L217" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L217">217</a>                 if (ct-&gt;<a href="ident?i=status">status</a> &amp; IPS_NAT_MASK)
<a name="L218" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L218">218</a>                         return 0;
<a name="L219" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L219">219</a>         }
<a name="L220" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L221">221</a>         if (manip == NF_NAT_MANIP_SRC)
<a name="L222" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L222">222</a>                 statusbit = IPS_SRC_NAT;
<a name="L223" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L223">223</a>         else
<a name="L224" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L224">224</a>                 statusbit = IPS_DST_NAT;
<a name="L225" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L226">226</a>         <b><i>/* Invert if this is reply direction */</i></b>
<a name="L227" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L227">227</a>         if (<a href="ident?i=dir">dir</a> == IP_CT_DIR_REPLY)
<a name="L228" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L228">228</a>                 statusbit ^= IPS_NAT_MASK;
<a name="L229" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L230">230</a>         if (!(ct-&gt;<a href="ident?i=status">status</a> &amp; statusbit))
<a name="L231" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L231">231</a>                 return 1;
<a name="L232" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L233">233</a>         l4proto = <a href="ident?i=__nf_nat_l4proto_find">__nf_nat_l4proto_find</a>(NFPROTO_IPV4, <a href="ident?i=inside">inside</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=protocol">protocol</a>);
<a name="L234" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L234">234</a>         if (!<a href="ident?i=nf_nat_ipv4_manip_pkt">nf_nat_ipv4_manip_pkt</a>(<a href="ident?i=skb">skb</a>, hdrlen + sizeof(<a href="ident?i=inside">inside</a>-&gt;icmp),
<a name="L235" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L235">235</a>                                    l4proto, &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple, !manip))
<a name="L236" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L236">236</a>                 return 0;
<a name="L237" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L238">238</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) {
<a name="L239" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L239">239</a>                 <b><i>/* Reloading "inside" here since manip_pkt may reallocate */</i></b>
<a name="L240" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L240">240</a>                 <a href="ident?i=inside">inside</a> = (void *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + hdrlen;
<a name="L241" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L241">241</a>                 <a href="ident?i=inside">inside</a>-&gt;icmp.<a href="ident?i=checksum">checksum</a> = 0;
<a name="L242" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L242">242</a>                 <a href="ident?i=inside">inside</a>-&gt;icmp.<a href="ident?i=checksum">checksum</a> =
<a name="L243" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L243">243</a>                         <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, hdrlen,
<a name="L244" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L244">244</a>                                                <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - hdrlen, 0));
<a name="L245" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L245">245</a>         }
<a name="L246" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L247">247</a>         <b><i>/* Change outer to look like the reply to an incoming packet */</i></b>
<a name="L248" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L248">248</a>         <a href="ident?i=nf_ct_invert_tuplepr">nf_ct_invert_tuplepr</a>(&amp;<a href="ident?i=target">target</a>, &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple);
<a name="L249" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L249">249</a>         l4proto = <a href="ident?i=__nf_nat_l4proto_find">__nf_nat_l4proto_find</a>(NFPROTO_IPV4, 0);
<a name="L250" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L250">250</a>         if (!<a href="ident?i=nf_nat_ipv4_manip_pkt">nf_nat_ipv4_manip_pkt</a>(<a href="ident?i=skb">skb</a>, 0, l4proto, &amp;<a href="ident?i=target">target</a>, manip))
<a name="L251" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L251">251</a>                 return 0;
<a name="L252" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L253">253</a>         return 1;
<a name="L254" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L254">254</a> }
<a name="L255" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L255">255</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_icmp_reply_translation">nf_nat_icmp_reply_translation</a>);
<a name="L256" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L257">257</a> unsigned int
<a name="L258" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L258">258</a> <a href="ident?i=nf_nat_ipv4_fn">nf_nat_ipv4_fn</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L259" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L259">259</a>                const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L260" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L260">260</a>                unsigned int (*do_chain)(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L261" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L261">261</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L262" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L262">262</a>                                         const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L263" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L263">263</a>                                         struct <a href="ident?i=nf_conn">nf_conn</a> *ct))
<a name="L264" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L264">264</a> {
<a name="L265" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L265">265</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L266" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L266">266</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L267" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L267">267</a>         struct <a href="ident?i=nf_conn_nat">nf_conn_nat</a> *nat;
<a name="L268" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L268">268</a>         <b><i>/* maniptype == SRC for postrouting. */</i></b>
<a name="L269" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L269">269</a>         enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype = <a href="ident?i=HOOK2MANIP">HOOK2MANIP</a>(<a href="ident?i=ops">ops</a>-&gt;hooknum);
<a name="L270" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L271">271</a>         <b><i>/* We never see fragments: conntrack defrags on pre-routing</i></b>
<a name="L272" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L272">272</a> <b><i>         * and local-out, and nf_nat_out protects post-routing.</i></b>
<a name="L273" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L273">273</a> <b><i>         */</i></b>
<a name="L274" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L274">274</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(!<a href="ident?i=ip_is_fragment">ip_is_fragment</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)));
<a name="L275" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L276">276</a>         ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
<a name="L277" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L277">277</a>         <b><i>/* Can't track?  It's not due to stress, or conntrack would</i></b>
<a name="L278" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L278">278</a> <b><i>         * have dropped it.  Hence it's the user's responsibilty to</i></b>
<a name="L279" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L279">279</a> <b><i>         * packet filter it out, or implement conntrack/NAT for that</i></b>
<a name="L280" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L280">280</a> <b><i>         * protocol. 8) --RR</i></b>
<a name="L281" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L281">281</a> <b><i>         */</i></b>
<a name="L282" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L282">282</a>         if (!ct)
<a name="L283" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L283">283</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L284" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L285">285</a>         <b><i>/* Don't try to NAT if this packet is not conntracked */</i></b>
<a name="L286" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L286">286</a>         if (<a href="ident?i=nf_ct_is_untracked">nf_ct_is_untracked</a>(ct))
<a name="L287" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L287">287</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L288" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L289">289</a>         nat = <a href="ident?i=nf_ct_nat_ext_add">nf_ct_nat_ext_add</a>(ct);
<a name="L290" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L290">290</a>         if (nat == <a href="ident?i=NULL">NULL</a>)
<a name="L291" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L291">291</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L292" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L293">293</a>         switch (ctinfo) {
<a name="L294" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L294">294</a>         case IP_CT_RELATED:
<a name="L295" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L295">295</a>         case IP_CT_RELATED_REPLY:
<a name="L296" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L296">296</a>                 if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>) {
<a name="L297" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L297">297</a>                         if (!<a href="ident?i=nf_nat_icmp_reply_translation">nf_nat_icmp_reply_translation</a>(<a href="ident?i=skb">skb</a>, ct, ctinfo,
<a name="L298" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L298">298</a>                                                            <a href="ident?i=ops">ops</a>-&gt;hooknum))
<a name="L299" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L299">299</a>                                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L300" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L300">300</a>                         else
<a name="L301" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L301">301</a>                                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L302" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L302">302</a>                 }
<a name="L303" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L303">303</a>                 <b><i>/* Fall thru... (Only ICMPs can be IP_CT_IS_REPLY) */</i></b>
<a name="L304" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L304">304</a>         case IP_CT_NEW:
<a name="L305" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L305">305</a>                 <b><i>/* Seen it before?  This can happen for loopback, retrans,</i></b>
<a name="L306" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L306">306</a> <b><i>                 * or local packets.</i></b>
<a name="L307" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L307">307</a> <b><i>                 */</i></b>
<a name="L308" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L308">308</a>                 if (!<a href="ident?i=nf_nat_initialized">nf_nat_initialized</a>(ct, maniptype)) {
<a name="L309" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L309">309</a>                         unsigned int <a href="ident?i=ret">ret</a>;
<a name="L310" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L311">311</a>                         <a href="ident?i=ret">ret</a> = do_chain(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, ct);
<a name="L312" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L312">312</a>                         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>)
<a name="L313" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L313">313</a>                                 return <a href="ident?i=ret">ret</a>;
<a name="L314" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L315">315</a>                         if (<a href="ident?i=nf_nat_initialized">nf_nat_initialized</a>(ct, <a href="ident?i=HOOK2MANIP">HOOK2MANIP</a>(<a href="ident?i=ops">ops</a>-&gt;hooknum)))
<a name="L316" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L316">316</a>                                 break;
<a name="L317" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L318">318</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_nat_alloc_null_binding">nf_nat_alloc_null_binding</a>(ct, <a href="ident?i=ops">ops</a>-&gt;hooknum);
<a name="L319" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L319">319</a>                         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>)
<a name="L320" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L320">320</a>                                 return <a href="ident?i=ret">ret</a>;
<a name="L321" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L321">321</a>                 } else {
<a name="L322" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L322">322</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Already setup manip %s for ct %p\n"</i>,
<a name="L323" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L323">323</a>                                  maniptype == NF_NAT_MANIP_SRC ? <i>"SRC"</i> : <i>"DST"</i>,
<a name="L324" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L324">324</a>                                  ct);
<a name="L325" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L325">325</a>                         if (<a href="ident?i=nf_nat_oif_changed">nf_nat_oif_changed</a>(<a href="ident?i=ops">ops</a>-&gt;hooknum, ctinfo, nat,
<a name="L326" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L326">326</a>                                                <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>))
<a name="L327" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L327">327</a>                                 goto oif_changed;
<a name="L328" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L328">328</a>                 }
<a name="L329" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L329">329</a>                 break;
<a name="L330" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L331">331</a>         default:
<a name="L332" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L332">332</a>                 <b><i>/* ESTABLISHED */</i></b>
<a name="L333" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L333">333</a>                 <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(ctinfo == IP_CT_ESTABLISHED ||
<a name="L334" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L334">334</a>                              ctinfo == IP_CT_ESTABLISHED_REPLY);
<a name="L335" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L335">335</a>                 if (<a href="ident?i=nf_nat_oif_changed">nf_nat_oif_changed</a>(<a href="ident?i=ops">ops</a>-&gt;hooknum, ctinfo, nat, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>))
<a name="L336" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L336">336</a>                         goto oif_changed;
<a name="L337" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L337">337</a>         }
<a name="L338" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L339">339</a>         return <a href="ident?i=nf_nat_packet">nf_nat_packet</a>(ct, ctinfo, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=skb">skb</a>);
<a name="L340" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L341">341</a> oif_changed:
<a name="L342" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L342">342</a>         <a href="ident?i=nf_ct_kill_acct">nf_ct_kill_acct</a>(ct, ctinfo, <a href="ident?i=skb">skb</a>);
<a name="L343" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L343">343</a>         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L344" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L344">344</a> }
<a name="L345" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L345">345</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_ipv4_fn">nf_nat_ipv4_fn</a>);
<a name="L346" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L347">347</a> unsigned int
<a name="L348" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L348">348</a> <a href="ident?i=nf_nat_ipv4_in">nf_nat_ipv4_in</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L349" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L349">349</a>                const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L350" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L350">350</a>                unsigned int (*do_chain)(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L351" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L351">351</a>                                          struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L352" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L352">352</a>                                          const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L353" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L353">353</a>                                          struct <a href="ident?i=nf_conn">nf_conn</a> *ct))
<a name="L354" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L354">354</a> {
<a name="L355" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L355">355</a>         unsigned int <a href="ident?i=ret">ret</a>;
<a name="L356" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L356">356</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L357" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L357">357</a> 
<a name="L358" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L358">358</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_nat_ipv4_fn">nf_nat_ipv4_fn</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, do_chain);
<a name="L359" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L359">359</a>         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_DROP">NF_DROP</a> &amp;&amp; <a href="ident?i=ret">ret</a> != <a href="ident?i=NF_STOLEN">NF_STOLEN</a> &amp;&amp;
<a name="L360" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L360">360</a>             <a href="ident?i=daddr">daddr</a> != <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>)
<a name="L361" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L361">361</a>                 <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L362" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L362">362</a> 
<a name="L363" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L363">363</a>         return <a href="ident?i=ret">ret</a>;
<a name="L364" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L364">364</a> }
<a name="L365" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L365">365</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_ipv4_in">nf_nat_ipv4_in</a>);
<a name="L366" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L367">367</a> unsigned int
<a name="L368" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L368">368</a> <a href="ident?i=nf_nat_ipv4_out">nf_nat_ipv4_out</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L369" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L369">369</a>                 const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L370" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L370">370</a>                 unsigned int (*do_chain)(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L371" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L371">371</a>                                           struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L372" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L372">372</a>                                           const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L373" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L373">373</a>                                           struct <a href="ident?i=nf_conn">nf_conn</a> *ct))
<a name="L374" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L374">374</a> {
<a name="L375" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L375">375</a> #ifdef CONFIG_XFRM
<a name="L376" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L376">376</a>         const struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L377" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L377">377</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L378" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L378">378</a>         int <a href="ident?i=err">err</a>;
<a name="L379" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L379">379</a> #endif
<a name="L380" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L380">380</a>         unsigned int <a href="ident?i=ret">ret</a>;
<a name="L381" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L382">382</a>         <b><i>/* root is playing with raw sockets. */</i></b>
<a name="L383" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L383">383</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
<a name="L384" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L384">384</a>             <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>))
<a name="L385" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L385">385</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L386" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L387">387</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_nat_ipv4_fn">nf_nat_ipv4_fn</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, do_chain);
<a name="L388" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L388">388</a> #ifdef CONFIG_XFRM
<a name="L389" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L389">389</a>         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_DROP">NF_DROP</a> &amp;&amp; <a href="ident?i=ret">ret</a> != <a href="ident?i=NF_STOLEN">NF_STOLEN</a> &amp;&amp;
<a name="L390" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L390">390</a>             !(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_XFRM_TRANSFORMED">IPSKB_XFRM_TRANSFORMED</a>) &amp;&amp;
<a name="L391" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L391">391</a>             (ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L392" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L392">392</a>                 enum <a href="ident?i=ip_conntrack_dir">ip_conntrack_dir</a> <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L393" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L394">394</a>                 if ((ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> !=
<a name="L395" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L395">395</a>                      ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>) ||
<a name="L396" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L396">396</a>                     (ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.protonum != <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a> &amp;&amp;
<a name="L397" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L397">397</a>                      ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u.<a href="ident?i=all">all</a> !=
<a name="L398" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L398">398</a>                      ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u.<a href="ident?i=all">all</a>)) {
<a name="L399" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L399">399</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=nf_xfrm_me_harder">nf_xfrm_me_harder</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L400" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L400">400</a>                         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L401" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L401">401</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=NF_DROP_ERR">NF_DROP_ERR</a>(<a href="ident?i=err">err</a>);
<a name="L402" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L402">402</a>                 }
<a name="L403" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L403">403</a>         }
<a name="L404" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L404">404</a> #endif
<a name="L405" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L405">405</a>         return <a href="ident?i=ret">ret</a>;
<a name="L406" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L406">406</a> }
<a name="L407" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L407">407</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_ipv4_out">nf_nat_ipv4_out</a>);
<a name="L408" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L408">408</a> 
<a name="L409" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L409">409</a> unsigned int
<a name="L410" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L410">410</a> <a href="ident?i=nf_nat_ipv4_local_fn">nf_nat_ipv4_local_fn</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L411" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L411">411</a>                      const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L412" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L412">412</a>                      unsigned int (*do_chain)(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L413" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L413">413</a>                                                struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L414" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L414">414</a>                                                const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L415" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L415">415</a>                                                struct <a href="ident?i=nf_conn">nf_conn</a> *ct))
<a name="L416" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L416">416</a> {
<a name="L417" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L417">417</a>         const struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L418" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L418">418</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L419" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L419">419</a>         unsigned int <a href="ident?i=ret">ret</a>;
<a name="L420" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L420">420</a>         int <a href="ident?i=err">err</a>;
<a name="L421" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L422">422</a>         <b><i>/* root is playing with raw sockets. */</i></b>
<a name="L423" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L423">423</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
<a name="L424" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L424">424</a>             <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>))
<a name="L425" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L425">425</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L426" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L426">426</a> 
<a name="L427" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L427">427</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_nat_ipv4_fn">nf_nat_ipv4_fn</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, do_chain);
<a name="L428" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L428">428</a>         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_DROP">NF_DROP</a> &amp;&amp; <a href="ident?i=ret">ret</a> != <a href="ident?i=NF_STOLEN">NF_STOLEN</a> &amp;&amp;
<a name="L429" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L429">429</a>             (ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L430" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L430">430</a>                 enum <a href="ident?i=ip_conntrack_dir">ip_conntrack_dir</a> <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L431" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L432">432</a>                 if (ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> !=
<a name="L433" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L433">433</a>                     ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>) {
<a name="L434" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L434">434</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(<a href="ident?i=skb">skb</a>, RTN_UNSPEC);
<a name="L435" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L435">435</a>                         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L436" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L436">436</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=NF_DROP_ERR">NF_DROP_ERR</a>(<a href="ident?i=err">err</a>);
<a name="L437" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L437">437</a>                 }
<a name="L438" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L438">438</a> #ifdef CONFIG_XFRM
<a name="L439" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L439">439</a>                 else if (!(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_XFRM_TRANSFORMED">IPSKB_XFRM_TRANSFORMED</a>) &amp;&amp;
<a name="L440" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L440">440</a>                          ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.protonum != <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a> &amp;&amp;
<a name="L441" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L441">441</a>                          ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u.<a href="ident?i=all">all</a> !=
<a name="L442" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L442">442</a>                          ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u.<a href="ident?i=all">all</a>) {
<a name="L443" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L443">443</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=nf_xfrm_me_harder">nf_xfrm_me_harder</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L444" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L444">444</a>                         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L445" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L445">445</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=NF_DROP_ERR">NF_DROP_ERR</a>(<a href="ident?i=err">err</a>);
<a name="L446" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L446">446</a>                 }
<a name="L447" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L447">447</a> #endif
<a name="L448" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L448">448</a>         }
<a name="L449" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L449">449</a>         return <a href="ident?i=ret">ret</a>;
<a name="L450" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L450">450</a> }
<a name="L451" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L451">451</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_ipv4_local_fn">nf_nat_ipv4_local_fn</a>);
<a name="L452" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L453">453</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_nat_l3proto_ipv4_init">nf_nat_l3proto_ipv4_init</a>(void)
<a name="L454" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L454">454</a> {
<a name="L455" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L455">455</a>         int <a href="ident?i=err">err</a>;
<a name="L456" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L457">457</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nf_nat_l4proto_register">nf_nat_l4proto_register</a>(NFPROTO_IPV4, &amp;<a href="ident?i=nf_nat_l4proto_icmp">nf_nat_l4proto_icmp</a>);
<a name="L458" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L458">458</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L459" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L459">459</a>                 goto err1;
<a name="L460" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L460">460</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nf_nat_l3proto_register">nf_nat_l3proto_register</a>(&amp;<a href="ident?i=nf_nat_l3proto_ipv4">nf_nat_l3proto_ipv4</a>);
<a name="L461" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L461">461</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L462" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L462">462</a>                 goto err2;
<a name="L463" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L463">463</a>         return <a href="ident?i=err">err</a>;
<a name="L464" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L464">464</a> 
<a name="L465" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L465">465</a> err2:
<a name="L466" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L466">466</a>         <a href="ident?i=nf_nat_l4proto_unregister">nf_nat_l4proto_unregister</a>(NFPROTO_IPV4, &amp;<a href="ident?i=nf_nat_l4proto_icmp">nf_nat_l4proto_icmp</a>);
<a name="L467" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L467">467</a> err1:
<a name="L468" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L468">468</a>         return <a href="ident?i=err">err</a>;
<a name="L469" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L469">469</a> }
<a name="L470" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L471">471</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_nat_l3proto_ipv4_exit">nf_nat_l3proto_ipv4_exit</a>(void)
<a name="L472" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L472">472</a> {
<a name="L473" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L473">473</a>         <a href="ident?i=nf_nat_l3proto_unregister">nf_nat_l3proto_unregister</a>(&amp;<a href="ident?i=nf_nat_l3proto_ipv4">nf_nat_l3proto_ipv4</a>);
<a name="L474" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L474">474</a>         <a href="ident?i=nf_nat_l4proto_unregister">nf_nat_l4proto_unregister</a>(NFPROTO_IPV4, &amp;<a href="ident?i=nf_nat_l4proto_icmp">nf_nat_l4proto_icmp</a>);
<a name="L475" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L475">475</a> }
<a name="L476" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L477">477</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L478" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L478">478</a> <a href="ident?i=MODULE_ALIAS">MODULE_ALIAS</a>(<i>"nf-nat-"</i> <a href="ident?i=__stringify">__stringify</a>(<a href="ident?i=AF_INET">AF_INET</a>));
<a name="L479" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L479">479</a> 
<a name="L480" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L480">480</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_nat_l3proto_ipv4_init">nf_nat_l3proto_ipv4_init</a>);
<a name="L481" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L481">481</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_nat_l3proto_ipv4_exit">nf_nat_l3proto_ipv4_exit</a>);
<a name="L482" href="source/net/ipv4/netfilter/nf_nat_l3proto_ipv4.c#L482">482</a> </pre></div><p>
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
