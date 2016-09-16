<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/iptable_mangle.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/iptable_mangle.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_mangle.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/iptable_mangle.c">iptable_mangle.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/iptable_mangle.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/iptable_mangle.c#L2">2</a> <b><i> * This is the 1999 rewrite of IP Firewalling, aiming for kernel 2.3.x.</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/iptable_mangle.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/iptable_mangle.c#L4">4</a> <b><i> * Copyright (C) 1999 Paul `Rusty' Russell &amp; Michael J. Neuling</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/iptable_mangle.c#L5">5</a> <b><i> * Copyright (C) 2000-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/iptable_mangle.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/iptable_mangle.c#L7">7</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/iptable_mangle.c#L8">8</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/iptable_mangle.c#L9">9</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/iptable_mangle.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/iptable_mangle.c#L11">11</a> #include &lt;linux/module.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/iptable_mangle.c#L12">12</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/iptable_mangle.c#L13">13</a> #include &lt;linux/netdevice.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/iptable_mangle.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/iptable_mangle.c#L15">15</a> #include &lt;linux/slab.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/iptable_mangle.c#L16">16</a> #include &lt;net/sock.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/iptable_mangle.c#L17">17</a> #include &lt;net/route.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/iptable_mangle.c#L18">18</a> #include &lt;linux/ip.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/iptable_mangle.c#L19">19</a> #include &lt;net/ip.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/iptable_mangle.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/netfilter/iptable_mangle.c#L21">21</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L22" href="source/net/ipv4/netfilter/iptable_mangle.c#L22">22</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Netfilter Core Team &lt;coreteam@netfilter.org&gt;"</i>);
 <a name="L23" href="source/net/ipv4/netfilter/iptable_mangle.c#L23">23</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"iptables mangle table"</i>);
 <a name="L24" href="source/net/ipv4/netfilter/iptable_mangle.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/netfilter/iptable_mangle.c#L25">25</a> #define <a href="ident?i=MANGLE_VALID_HOOKS">MANGLE_VALID_HOOKS</a> ((1 &lt;&lt; NF_INET_PRE_ROUTING) | \
 <a name="L26" href="source/net/ipv4/netfilter/iptable_mangle.c#L26">26</a>                             (1 &lt;&lt; NF_INET_LOCAL_IN) | \
 <a name="L27" href="source/net/ipv4/netfilter/iptable_mangle.c#L27">27</a>                             (1 &lt;&lt; NF_INET_FORWARD) | \
 <a name="L28" href="source/net/ipv4/netfilter/iptable_mangle.c#L28">28</a>                             (1 &lt;&lt; NF_INET_LOCAL_OUT) | \
 <a name="L29" href="source/net/ipv4/netfilter/iptable_mangle.c#L29">29</a>                             (1 &lt;&lt; NF_INET_POST_ROUTING))
 <a name="L30" href="source/net/ipv4/netfilter/iptable_mangle.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/netfilter/iptable_mangle.c#L31">31</a> static const struct <a href="ident?i=xt_table">xt_table</a> <a href="ident?i=packet_mangler">packet_mangler</a> = {
 <a name="L32" href="source/net/ipv4/netfilter/iptable_mangle.c#L32">32</a>         .<a href="ident?i=name">name</a>           = <i>"mangle"</i>,
 <a name="L33" href="source/net/ipv4/netfilter/iptable_mangle.c#L33">33</a>         .valid_hooks    = <a href="ident?i=MANGLE_VALID_HOOKS">MANGLE_VALID_HOOKS</a>,
 <a name="L34" href="source/net/ipv4/netfilter/iptable_mangle.c#L34">34</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L35" href="source/net/ipv4/netfilter/iptable_mangle.c#L35">35</a>         .<a href="ident?i=af">af</a>             = NFPROTO_IPV4,
 <a name="L36" href="source/net/ipv4/netfilter/iptable_mangle.c#L36">36</a>         .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_MANGLE,
 <a name="L37" href="source/net/ipv4/netfilter/iptable_mangle.c#L37">37</a> };
 <a name="L38" href="source/net/ipv4/netfilter/iptable_mangle.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/netfilter/iptable_mangle.c#L39">39</a> static unsigned int
 <a name="L40" href="source/net/ipv4/netfilter/iptable_mangle.c#L40">40</a> <a href="ident?i=ipt_mangle_out">ipt_mangle_out</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L41" href="source/net/ipv4/netfilter/iptable_mangle.c#L41">41</a> {
 <a name="L42" href="source/net/ipv4/netfilter/iptable_mangle.c#L42">42</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=out">out</a> = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>;
 <a name="L43" href="source/net/ipv4/netfilter/iptable_mangle.c#L43">43</a>         unsigned int <a href="ident?i=ret">ret</a>;
 <a name="L44" href="source/net/ipv4/netfilter/iptable_mangle.c#L44">44</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L45" href="source/net/ipv4/netfilter/iptable_mangle.c#L45">45</a>         <a href="ident?i=u_int8_t">u_int8_t</a> tos;
 <a name="L46" href="source/net/ipv4/netfilter/iptable_mangle.c#L46">46</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
 <a name="L47" href="source/net/ipv4/netfilter/iptable_mangle.c#L47">47</a>         <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=mark">mark</a>;
 <a name="L48" href="source/net/ipv4/netfilter/iptable_mangle.c#L48">48</a>         int <a href="ident?i=err">err</a>;
 <a name="L49" href="source/net/ipv4/netfilter/iptable_mangle.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/netfilter/iptable_mangle.c#L50">50</a>         <b><i>/* root is playing with raw sockets. */</i></b>
 <a name="L51" href="source/net/ipv4/netfilter/iptable_mangle.c#L51">51</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
 <a name="L52" href="source/net/ipv4/netfilter/iptable_mangle.c#L52">52</a>             <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>))
 <a name="L53" href="source/net/ipv4/netfilter/iptable_mangle.c#L53">53</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L54" href="source/net/ipv4/netfilter/iptable_mangle.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/netfilter/iptable_mangle.c#L55">55</a>         <b><i>/* Save things which could affect route */</i></b>
 <a name="L56" href="source/net/ipv4/netfilter/iptable_mangle.c#L56">56</a>         <a href="ident?i=mark">mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
 <a name="L57" href="source/net/ipv4/netfilter/iptable_mangle.c#L57">57</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L58" href="source/net/ipv4/netfilter/iptable_mangle.c#L58">58</a>         <a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L59" href="source/net/ipv4/netfilter/iptable_mangle.c#L59">59</a>         <a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L60" href="source/net/ipv4/netfilter/iptable_mangle.c#L60">60</a>         tos = iph-&gt;tos;
 <a name="L61" href="source/net/ipv4/netfilter/iptable_mangle.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/iptable_mangle.c#L62">62</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ipt_do_table">ipt_do_table</a>(<a href="ident?i=skb">skb</a>, NF_INET_LOCAL_OUT, <a href="ident?i=state">state</a>,
 <a name="L63" href="source/net/ipv4/netfilter/iptable_mangle.c#L63">63</a>                            <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=out">out</a>)-&gt;ipv4.iptable_mangle);
 <a name="L64" href="source/net/ipv4/netfilter/iptable_mangle.c#L64">64</a>         <b><i>/* Reroute for ANY change. */</i></b>
 <a name="L65" href="source/net/ipv4/netfilter/iptable_mangle.c#L65">65</a>         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_DROP">NF_DROP</a> &amp;&amp; <a href="ident?i=ret">ret</a> != <a href="ident?i=NF_STOLEN">NF_STOLEN</a>) {
 <a name="L66" href="source/net/ipv4/netfilter/iptable_mangle.c#L66">66</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L67" href="source/net/ipv4/netfilter/iptable_mangle.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/iptable_mangle.c#L68">68</a>                 if (iph-&gt;<a href="ident?i=saddr">saddr</a> != <a href="ident?i=saddr">saddr</a> ||
 <a name="L69" href="source/net/ipv4/netfilter/iptable_mangle.c#L69">69</a>                     iph-&gt;<a href="ident?i=daddr">daddr</a> != <a href="ident?i=daddr">daddr</a> ||
 <a name="L70" href="source/net/ipv4/netfilter/iptable_mangle.c#L70">70</a>                     <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> != <a href="ident?i=mark">mark</a> ||
 <a name="L71" href="source/net/ipv4/netfilter/iptable_mangle.c#L71">71</a>                     iph-&gt;tos != tos) {
 <a name="L72" href="source/net/ipv4/netfilter/iptable_mangle.c#L72">72</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(<a href="ident?i=skb">skb</a>, RTN_UNSPEC);
 <a name="L73" href="source/net/ipv4/netfilter/iptable_mangle.c#L73">73</a>                         if (<a href="ident?i=err">err</a> &lt; 0)
 <a name="L74" href="source/net/ipv4/netfilter/iptable_mangle.c#L74">74</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=NF_DROP_ERR">NF_DROP_ERR</a>(<a href="ident?i=err">err</a>);
 <a name="L75" href="source/net/ipv4/netfilter/iptable_mangle.c#L75">75</a>                 }
 <a name="L76" href="source/net/ipv4/netfilter/iptable_mangle.c#L76">76</a>         }
 <a name="L77" href="source/net/ipv4/netfilter/iptable_mangle.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/netfilter/iptable_mangle.c#L78">78</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L79" href="source/net/ipv4/netfilter/iptable_mangle.c#L79">79</a> }
 <a name="L80" href="source/net/ipv4/netfilter/iptable_mangle.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/netfilter/iptable_mangle.c#L81">81</a> <b><i>/* The work comes in here from netfilter.c. */</i></b>
 <a name="L82" href="source/net/ipv4/netfilter/iptable_mangle.c#L82">82</a> static unsigned int
 <a name="L83" href="source/net/ipv4/netfilter/iptable_mangle.c#L83">83</a> <a href="ident?i=iptable_mangle_hook">iptable_mangle_hook</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L84" href="source/net/ipv4/netfilter/iptable_mangle.c#L84">84</a>                      struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L85" href="source/net/ipv4/netfilter/iptable_mangle.c#L85">85</a>                      const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L86" href="source/net/ipv4/netfilter/iptable_mangle.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/netfilter/iptable_mangle.c#L87">87</a>         if (<a href="ident?i=ops">ops</a>-&gt;hooknum == NF_INET_LOCAL_OUT)
 <a name="L88" href="source/net/ipv4/netfilter/iptable_mangle.c#L88">88</a>                 return <a href="ident?i=ipt_mangle_out">ipt_mangle_out</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>);
 <a name="L89" href="source/net/ipv4/netfilter/iptable_mangle.c#L89">89</a>         if (<a href="ident?i=ops">ops</a>-&gt;hooknum == NF_INET_POST_ROUTING)
 <a name="L90" href="source/net/ipv4/netfilter/iptable_mangle.c#L90">90</a>                 return <a href="ident?i=ipt_do_table">ipt_do_table</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=state">state</a>,
 <a name="L91" href="source/net/ipv4/netfilter/iptable_mangle.c#L91">91</a>                                     <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>)-&gt;ipv4.iptable_mangle);
 <a name="L92" href="source/net/ipv4/netfilter/iptable_mangle.c#L92">92</a>         <b><i>/* PREROUTING/INPUT/FORWARD: */</i></b>
 <a name="L93" href="source/net/ipv4/netfilter/iptable_mangle.c#L93">93</a>         return <a href="ident?i=ipt_do_table">ipt_do_table</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=state">state</a>,
 <a name="L94" href="source/net/ipv4/netfilter/iptable_mangle.c#L94">94</a>                             <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>)-&gt;ipv4.iptable_mangle);
 <a name="L95" href="source/net/ipv4/netfilter/iptable_mangle.c#L95">95</a> }
 <a name="L96" href="source/net/ipv4/netfilter/iptable_mangle.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/netfilter/iptable_mangle.c#L97">97</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *mangle_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L98" href="source/net/ipv4/netfilter/iptable_mangle.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/netfilter/iptable_mangle.c#L99">99</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=iptable_mangle_net_init">iptable_mangle_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L100" href="source/net/ipv4/netfilter/iptable_mangle.c#L100">100</a> {
<a name="L101" href="source/net/ipv4/netfilter/iptable_mangle.c#L101">101</a>         struct <a href="ident?i=ipt_replace">ipt_replace</a> *repl;
<a name="L102" href="source/net/ipv4/netfilter/iptable_mangle.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/netfilter/iptable_mangle.c#L103">103</a>         repl = <a href="ident?i=ipt_alloc_initial_table">ipt_alloc_initial_table</a>(&amp;<a href="ident?i=packet_mangler">packet_mangler</a>);
<a name="L104" href="source/net/ipv4/netfilter/iptable_mangle.c#L104">104</a>         if (repl == <a href="ident?i=NULL">NULL</a>)
<a name="L105" href="source/net/ipv4/netfilter/iptable_mangle.c#L105">105</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L106" href="source/net/ipv4/netfilter/iptable_mangle.c#L106">106</a>         <a href="ident?i=net">net</a>-&gt;ipv4.iptable_mangle =
<a name="L107" href="source/net/ipv4/netfilter/iptable_mangle.c#L107">107</a>                 <a href="ident?i=ipt_register_table">ipt_register_table</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=packet_mangler">packet_mangler</a>, repl);
<a name="L108" href="source/net/ipv4/netfilter/iptable_mangle.c#L108">108</a>         <a href="ident?i=kfree">kfree</a>(repl);
<a name="L109" href="source/net/ipv4/netfilter/iptable_mangle.c#L109">109</a>         return <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(<a href="ident?i=net">net</a>-&gt;ipv4.iptable_mangle);
<a name="L110" href="source/net/ipv4/netfilter/iptable_mangle.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/netfilter/iptable_mangle.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/netfilter/iptable_mangle.c#L112">112</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=iptable_mangle_net_exit">iptable_mangle_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L113" href="source/net/ipv4/netfilter/iptable_mangle.c#L113">113</a> {
<a name="L114" href="source/net/ipv4/netfilter/iptable_mangle.c#L114">114</a>         <a href="ident?i=ipt_unregister_table">ipt_unregister_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=net">net</a>-&gt;ipv4.iptable_mangle);
<a name="L115" href="source/net/ipv4/netfilter/iptable_mangle.c#L115">115</a> }
<a name="L116" href="source/net/ipv4/netfilter/iptable_mangle.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/netfilter/iptable_mangle.c#L117">117</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=iptable_mangle_net_ops">iptable_mangle_net_ops</a> = {
<a name="L118" href="source/net/ipv4/netfilter/iptable_mangle.c#L118">118</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=iptable_mangle_net_init">iptable_mangle_net_init</a>,
<a name="L119" href="source/net/ipv4/netfilter/iptable_mangle.c#L119">119</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=iptable_mangle_net_exit">iptable_mangle_net_exit</a>,
<a name="L120" href="source/net/ipv4/netfilter/iptable_mangle.c#L120">120</a> };
<a name="L121" href="source/net/ipv4/netfilter/iptable_mangle.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/netfilter/iptable_mangle.c#L122">122</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=iptable_mangle_init">iptable_mangle_init</a>(void)
<a name="L123" href="source/net/ipv4/netfilter/iptable_mangle.c#L123">123</a> {
<a name="L124" href="source/net/ipv4/netfilter/iptable_mangle.c#L124">124</a>         int <a href="ident?i=ret">ret</a>;
<a name="L125" href="source/net/ipv4/netfilter/iptable_mangle.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/netfilter/iptable_mangle.c#L126">126</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=iptable_mangle_net_ops">iptable_mangle_net_ops</a>);
<a name="L127" href="source/net/ipv4/netfilter/iptable_mangle.c#L127">127</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L128" href="source/net/ipv4/netfilter/iptable_mangle.c#L128">128</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L129" href="source/net/ipv4/netfilter/iptable_mangle.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/netfilter/iptable_mangle.c#L130">130</a>         <b><i>/* Register hooks */</i></b>
<a name="L131" href="source/net/ipv4/netfilter/iptable_mangle.c#L131">131</a>         mangle_ops = <a href="ident?i=xt_hook_link">xt_hook_link</a>(&amp;<a href="ident?i=packet_mangler">packet_mangler</a>, <a href="ident?i=iptable_mangle_hook">iptable_mangle_hook</a>);
<a name="L132" href="source/net/ipv4/netfilter/iptable_mangle.c#L132">132</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(mangle_ops)) {
<a name="L133" href="source/net/ipv4/netfilter/iptable_mangle.c#L133">133</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(mangle_ops);
<a name="L134" href="source/net/ipv4/netfilter/iptable_mangle.c#L134">134</a>                 <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_mangle_net_ops">iptable_mangle_net_ops</a>);
<a name="L135" href="source/net/ipv4/netfilter/iptable_mangle.c#L135">135</a>         }
<a name="L136" href="source/net/ipv4/netfilter/iptable_mangle.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/netfilter/iptable_mangle.c#L137">137</a>         return <a href="ident?i=ret">ret</a>;
<a name="L138" href="source/net/ipv4/netfilter/iptable_mangle.c#L138">138</a> }
<a name="L139" href="source/net/ipv4/netfilter/iptable_mangle.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/netfilter/iptable_mangle.c#L140">140</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=iptable_mangle_fini">iptable_mangle_fini</a>(void)
<a name="L141" href="source/net/ipv4/netfilter/iptable_mangle.c#L141">141</a> {
<a name="L142" href="source/net/ipv4/netfilter/iptable_mangle.c#L142">142</a>         <a href="ident?i=xt_hook_unlink">xt_hook_unlink</a>(&amp;<a href="ident?i=packet_mangler">packet_mangler</a>, mangle_ops);
<a name="L143" href="source/net/ipv4/netfilter/iptable_mangle.c#L143">143</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_mangle_net_ops">iptable_mangle_net_ops</a>);
<a name="L144" href="source/net/ipv4/netfilter/iptable_mangle.c#L144">144</a> }
<a name="L145" href="source/net/ipv4/netfilter/iptable_mangle.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/netfilter/iptable_mangle.c#L146">146</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=iptable_mangle_init">iptable_mangle_init</a>);
<a name="L147" href="source/net/ipv4/netfilter/iptable_mangle.c#L147">147</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=iptable_mangle_fini">iptable_mangle_fini</a>);
<a name="L148" href="source/net/ipv4/netfilter/iptable_mangle.c#L148">148</a> </pre></div><p>
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
