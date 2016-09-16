<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_tunnel.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_tunnel.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_tunnel.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_tunnel.c">ip_tunnel.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_tunnel.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_tunnel.c#L2">2</a> <b><i> * Copyright (c) 2013 Nicira, Inc.</i></b>
  <a name="L3" href="source/net/ipv4/ip_tunnel.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/ip_tunnel.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or</i></b>
  <a name="L5" href="source/net/ipv4/ip_tunnel.c#L5">5</a> <b><i> * modify it under the terms of version 2 of the GNU General Public</i></b>
  <a name="L6" href="source/net/ipv4/ip_tunnel.c#L6">6</a> <b><i> * License as published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/ip_tunnel.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_tunnel.c#L8">8</a> <b><i> * This program is distributed in the hope that it will be useful, but</i></b>
  <a name="L9" href="source/net/ipv4/ip_tunnel.c#L9">9</a> <b><i> * WITHOUT ANY WARRANTY; without even the implied warranty of</i></b>
 <a name="L10" href="source/net/ipv4/ip_tunnel.c#L10">10</a> <b><i> * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU</i></b>
 <a name="L11" href="source/net/ipv4/ip_tunnel.c#L11">11</a> <b><i> * General Public License for more details.</i></b>
 <a name="L12" href="source/net/ipv4/ip_tunnel.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/ip_tunnel.c#L13">13</a> <b><i> * You should have received a copy of the GNU General Public License</i></b>
 <a name="L14" href="source/net/ipv4/ip_tunnel.c#L14">14</a> <b><i> * along with this program; if not, write to the Free Software</i></b>
 <a name="L15" href="source/net/ipv4/ip_tunnel.c#L15">15</a> <b><i> * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA</i></b>
 <a name="L16" href="source/net/ipv4/ip_tunnel.c#L16">16</a> <b><i> * 02110-1301, USA</i></b>
 <a name="L17" href="source/net/ipv4/ip_tunnel.c#L17">17</a> <b><i> */</i></b>
 <a name="L18" href="source/net/ipv4/ip_tunnel.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/ip_tunnel.c#L19">19</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L20" href="source/net/ipv4/ip_tunnel.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/ip_tunnel.c#L21">21</a> #include &lt;linux/capability.h&gt;
 <a name="L22" href="source/net/ipv4/ip_tunnel.c#L22">22</a> #include &lt;linux/module.h&gt;
 <a name="L23" href="source/net/ipv4/ip_tunnel.c#L23">23</a> #include &lt;linux/types.h&gt;
 <a name="L24" href="source/net/ipv4/ip_tunnel.c#L24">24</a> #include &lt;linux/kernel.h&gt;
 <a name="L25" href="source/net/ipv4/ip_tunnel.c#L25">25</a> #include &lt;linux/slab.h&gt;
 <a name="L26" href="source/net/ipv4/ip_tunnel.c#L26">26</a> #include &lt;linux/uaccess.h&gt;
 <a name="L27" href="source/net/ipv4/ip_tunnel.c#L27">27</a> #include &lt;linux/skbuff.h&gt;
 <a name="L28" href="source/net/ipv4/ip_tunnel.c#L28">28</a> #include &lt;linux/netdevice.h&gt;
 <a name="L29" href="source/net/ipv4/ip_tunnel.c#L29">29</a> #include &lt;linux/in.h&gt;
 <a name="L30" href="source/net/ipv4/ip_tunnel.c#L30">30</a> #include &lt;linux/tcp.h&gt;
 <a name="L31" href="source/net/ipv4/ip_tunnel.c#L31">31</a> #include &lt;linux/udp.h&gt;
 <a name="L32" href="source/net/ipv4/ip_tunnel.c#L32">32</a> #include &lt;linux/if_arp.h&gt;
 <a name="L33" href="source/net/ipv4/ip_tunnel.c#L33">33</a> #include &lt;linux/mroute.h&gt;
 <a name="L34" href="source/net/ipv4/ip_tunnel.c#L34">34</a> #include &lt;linux/init.h&gt;
 <a name="L35" href="source/net/ipv4/ip_tunnel.c#L35">35</a> #include &lt;linux/in6.h&gt;
 <a name="L36" href="source/net/ipv4/ip_tunnel.c#L36">36</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L37" href="source/net/ipv4/ip_tunnel.c#L37">37</a> #include &lt;linux/igmp.h&gt;
 <a name="L38" href="source/net/ipv4/ip_tunnel.c#L38">38</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L39" href="source/net/ipv4/ip_tunnel.c#L39">39</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L40" href="source/net/ipv4/ip_tunnel.c#L40">40</a> #include &lt;linux/if_ether.h&gt;
 <a name="L41" href="source/net/ipv4/ip_tunnel.c#L41">41</a> #include &lt;linux/if_vlan.h&gt;
 <a name="L42" href="source/net/ipv4/ip_tunnel.c#L42">42</a> #include &lt;linux/rculist.h&gt;
 <a name="L43" href="source/net/ipv4/ip_tunnel.c#L43">43</a> #include &lt;linux/err.h&gt;
 <a name="L44" href="source/net/ipv4/ip_tunnel.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/ip_tunnel.c#L45">45</a> #include &lt;net/sock.h&gt;
 <a name="L46" href="source/net/ipv4/ip_tunnel.c#L46">46</a> #include &lt;net/ip.h&gt;
 <a name="L47" href="source/net/ipv4/ip_tunnel.c#L47">47</a> #include &lt;net/icmp.h&gt;
 <a name="L48" href="source/net/ipv4/ip_tunnel.c#L48">48</a> #include &lt;net/protocol.h&gt;
 <a name="L49" href="source/net/ipv4/ip_tunnel.c#L49">49</a> #include &lt;net/ip_tunnels.h&gt;
 <a name="L50" href="source/net/ipv4/ip_tunnel.c#L50">50</a> #include &lt;net/arp.h&gt;
 <a name="L51" href="source/net/ipv4/ip_tunnel.c#L51">51</a> #include &lt;net/checksum.h&gt;
 <a name="L52" href="source/net/ipv4/ip_tunnel.c#L52">52</a> #include &lt;net/dsfield.h&gt;
 <a name="L53" href="source/net/ipv4/ip_tunnel.c#L53">53</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L54" href="source/net/ipv4/ip_tunnel.c#L54">54</a> #include &lt;net/xfrm.h&gt;
 <a name="L55" href="source/net/ipv4/ip_tunnel.c#L55">55</a> #include &lt;net/net_namespace.h&gt;
 <a name="L56" href="source/net/ipv4/ip_tunnel.c#L56">56</a> #include &lt;net/netns/generic.h&gt;
 <a name="L57" href="source/net/ipv4/ip_tunnel.c#L57">57</a> #include &lt;net/rtnetlink.h&gt;
 <a name="L58" href="source/net/ipv4/ip_tunnel.c#L58">58</a> #include &lt;net/udp.h&gt;
 <a name="L59" href="source/net/ipv4/ip_tunnel.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/ip_tunnel.c#L60">60</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L61" href="source/net/ipv4/ip_tunnel.c#L61">61</a> #include &lt;net/ipv6.h&gt;
 <a name="L62" href="source/net/ipv4/ip_tunnel.c#L62">62</a> #include &lt;net/ip6_fib.h&gt;
 <a name="L63" href="source/net/ipv4/ip_tunnel.c#L63">63</a> #include &lt;net/ip6_route.h&gt;
 <a name="L64" href="source/net/ipv4/ip_tunnel.c#L64">64</a> #endif
 <a name="L65" href="source/net/ipv4/ip_tunnel.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/ip_tunnel.c#L66">66</a> static unsigned int <a href="ident?i=ip_tunnel_hash">ip_tunnel_hash</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=remote">remote</a>)
 <a name="L67" href="source/net/ipv4/ip_tunnel.c#L67">67</a> {
 <a name="L68" href="source/net/ipv4/ip_tunnel.c#L68">68</a>         return <a href="ident?i=hash_32">hash_32</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=key">key</a> ^ (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=remote">remote</a>,
 <a name="L69" href="source/net/ipv4/ip_tunnel.c#L69">69</a>                          <a href="ident?i=IP_TNL_HASH_BITS">IP_TNL_HASH_BITS</a>);
 <a name="L70" href="source/net/ipv4/ip_tunnel.c#L70">70</a> }
 <a name="L71" href="source/net/ipv4/ip_tunnel.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/ip_tunnel.c#L72">72</a> static void <a href="ident?i=__tunnel_dst_set">__tunnel_dst_set</a>(struct <a href="ident?i=ip_tunnel_dst">ip_tunnel_dst</a> *idst,
 <a name="L73" href="source/net/ipv4/ip_tunnel.c#L73">73</a>                              struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>)
 <a name="L74" href="source/net/ipv4/ip_tunnel.c#L74">74</a> {
 <a name="L75" href="source/net/ipv4/ip_tunnel.c#L75">75</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *old_dst;
 <a name="L76" href="source/net/ipv4/ip_tunnel.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/ip_tunnel.c#L77">77</a>         <a href="ident?i=dst_clone">dst_clone</a>(<a href="ident?i=dst">dst</a>);
 <a name="L78" href="source/net/ipv4/ip_tunnel.c#L78">78</a>         old_dst = <a href="ident?i=xchg">xchg</a>((<a href="ident?i=__force">__force</a> struct <a href="ident?i=dst_entry">dst_entry</a> **)&amp;idst-&gt;<a href="ident?i=dst">dst</a>, <a href="ident?i=dst">dst</a>);
 <a name="L79" href="source/net/ipv4/ip_tunnel.c#L79">79</a>         <a href="ident?i=dst_release">dst_release</a>(old_dst);
 <a name="L80" href="source/net/ipv4/ip_tunnel.c#L80">80</a>         idst-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
 <a name="L81" href="source/net/ipv4/ip_tunnel.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/ip_tunnel.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/ip_tunnel.c#L83">83</a> static <a href="ident?i=noinline">noinline</a> void <a href="ident?i=tunnel_dst_set">tunnel_dst_set</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>,
 <a name="L84" href="source/net/ipv4/ip_tunnel.c#L84">84</a>                            struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>)
 <a name="L85" href="source/net/ipv4/ip_tunnel.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/ip_tunnel.c#L86">86</a>         <a href="ident?i=__tunnel_dst_set">__tunnel_dst_set</a>(<a href="ident?i=raw_cpu_ptr">raw_cpu_ptr</a>(<a href="ident?i=t">t</a>-&gt;dst_cache), <a href="ident?i=dst">dst</a>, <a href="ident?i=saddr">saddr</a>);
 <a name="L87" href="source/net/ipv4/ip_tunnel.c#L87">87</a> }
 <a name="L88" href="source/net/ipv4/ip_tunnel.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/ip_tunnel.c#L89">89</a> static void <a href="ident?i=tunnel_dst_reset">tunnel_dst_reset</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>)
 <a name="L90" href="source/net/ipv4/ip_tunnel.c#L90">90</a> {
 <a name="L91" href="source/net/ipv4/ip_tunnel.c#L91">91</a>         <a href="ident?i=tunnel_dst_set">tunnel_dst_set</a>(<a href="ident?i=t">t</a>, <a href="ident?i=NULL">NULL</a>, 0);
 <a name="L92" href="source/net/ipv4/ip_tunnel.c#L92">92</a> }
 <a name="L93" href="source/net/ipv4/ip_tunnel.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ip_tunnel.c#L94">94</a> void <a href="ident?i=ip_tunnel_dst_reset_all">ip_tunnel_dst_reset_all</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>)
 <a name="L95" href="source/net/ipv4/ip_tunnel.c#L95">95</a> {
 <a name="L96" href="source/net/ipv4/ip_tunnel.c#L96">96</a>         int <a href="ident?i=i">i</a>;
 <a name="L97" href="source/net/ipv4/ip_tunnel.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/ip_tunnel.c#L98">98</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>)
 <a name="L99" href="source/net/ipv4/ip_tunnel.c#L99">99</a>                 <a href="ident?i=__tunnel_dst_set">__tunnel_dst_set</a>(<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=t">t</a>-&gt;dst_cache, <a href="ident?i=i">i</a>), <a href="ident?i=NULL">NULL</a>, 0);
<a name="L100" href="source/net/ipv4/ip_tunnel.c#L100">100</a> }
<a name="L101" href="source/net/ipv4/ip_tunnel.c#L101">101</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tunnel_dst_reset_all">ip_tunnel_dst_reset_all</a>);
<a name="L102" href="source/net/ipv4/ip_tunnel.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/ip_tunnel.c#L103">103</a> static struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=tunnel_rtable_get">tunnel_rtable_get</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>,
<a name="L104" href="source/net/ipv4/ip_tunnel.c#L104">104</a>                                         <a href="ident?i=u32">u32</a> cookie, <a href="ident?i=__be32">__be32</a> *<a href="ident?i=saddr">saddr</a>)
<a name="L105" href="source/net/ipv4/ip_tunnel.c#L105">105</a> {
<a name="L106" href="source/net/ipv4/ip_tunnel.c#L106">106</a>         struct <a href="ident?i=ip_tunnel_dst">ip_tunnel_dst</a> *idst;
<a name="L107" href="source/net/ipv4/ip_tunnel.c#L107">107</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L108" href="source/net/ipv4/ip_tunnel.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/ip_tunnel.c#L109">109</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L110" href="source/net/ipv4/ip_tunnel.c#L110">110</a>         idst = <a href="ident?i=raw_cpu_ptr">raw_cpu_ptr</a>(<a href="ident?i=t">t</a>-&gt;dst_cache);
<a name="L111" href="source/net/ipv4/ip_tunnel.c#L111">111</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(idst-&gt;<a href="ident?i=dst">dst</a>);
<a name="L112" href="source/net/ipv4/ip_tunnel.c#L112">112</a>         if (<a href="ident?i=dst">dst</a> &amp;&amp; !<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;<a href="ident?i=dst">dst</a>-&gt;__refcnt))
<a name="L113" href="source/net/ipv4/ip_tunnel.c#L113">113</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L114" href="source/net/ipv4/ip_tunnel.c#L114">114</a>         if (<a href="ident?i=dst">dst</a>) {
<a name="L115" href="source/net/ipv4/ip_tunnel.c#L115">115</a>                 if (!<a href="ident?i=dst">dst</a>-&gt;obsolete || <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=check">check</a>(<a href="ident?i=dst">dst</a>, cookie)) {
<a name="L116" href="source/net/ipv4/ip_tunnel.c#L116">116</a>                         *<a href="ident?i=saddr">saddr</a> = idst-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L117" href="source/net/ipv4/ip_tunnel.c#L117">117</a>                 } else {
<a name="L118" href="source/net/ipv4/ip_tunnel.c#L118">118</a>                         <a href="ident?i=tunnel_dst_reset">tunnel_dst_reset</a>(<a href="ident?i=t">t</a>);
<a name="L119" href="source/net/ipv4/ip_tunnel.c#L119">119</a>                         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L120" href="source/net/ipv4/ip_tunnel.c#L120">120</a>                         <a href="ident?i=dst">dst</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L121" href="source/net/ipv4/ip_tunnel.c#L121">121</a>                 }
<a name="L122" href="source/net/ipv4/ip_tunnel.c#L122">122</a>         }
<a name="L123" href="source/net/ipv4/ip_tunnel.c#L123">123</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L124" href="source/net/ipv4/ip_tunnel.c#L124">124</a>         return (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=dst">dst</a>;
<a name="L125" href="source/net/ipv4/ip_tunnel.c#L125">125</a> }
<a name="L126" href="source/net/ipv4/ip_tunnel.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/ip_tunnel.c#L127">127</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ip_tunnel_key_match">ip_tunnel_key_match</a>(const struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a>,
<a name="L128" href="source/net/ipv4/ip_tunnel.c#L128">128</a>                                 <a href="ident?i=__be16">__be16</a> <a href="ident?i=flags">flags</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a>)
<a name="L129" href="source/net/ipv4/ip_tunnel.c#L129">129</a> {
<a name="L130" href="source/net/ipv4/ip_tunnel.c#L130">130</a>         if (<a href="ident?i=p">p</a>-&gt;i_flags &amp; <a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>) {
<a name="L131" href="source/net/ipv4/ip_tunnel.c#L131">131</a>                 if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>)
<a name="L132" href="source/net/ipv4/ip_tunnel.c#L132">132</a>                         return <a href="ident?i=key">key</a> == <a href="ident?i=p">p</a>-&gt;i_key;
<a name="L133" href="source/net/ipv4/ip_tunnel.c#L133">133</a>                 else
<a name="L134" href="source/net/ipv4/ip_tunnel.c#L134">134</a>                         <b><i>/* key expected, none present */</i></b>
<a name="L135" href="source/net/ipv4/ip_tunnel.c#L135">135</a>                         return <a href="ident?i=false">false</a>;
<a name="L136" href="source/net/ipv4/ip_tunnel.c#L136">136</a>         } else
<a name="L137" href="source/net/ipv4/ip_tunnel.c#L137">137</a>                 return !(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>);
<a name="L138" href="source/net/ipv4/ip_tunnel.c#L138">138</a> }
<a name="L139" href="source/net/ipv4/ip_tunnel.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/ip_tunnel.c#L140">140</a> <b><i>/* Fallback tunnel: no source, no destination, no key, no options</i></b>
<a name="L141" href="source/net/ipv4/ip_tunnel.c#L141">141</a> <b><i></i></b>
<a name="L142" href="source/net/ipv4/ip_tunnel.c#L142">142</a> <b><i>   Tunnel hash table:</i></b>
<a name="L143" href="source/net/ipv4/ip_tunnel.c#L143">143</a> <b><i>   We require exact key match i.e. if a key is present in packet</i></b>
<a name="L144" href="source/net/ipv4/ip_tunnel.c#L144">144</a> <b><i>   it will match only tunnel with the same key; if it is not present,</i></b>
<a name="L145" href="source/net/ipv4/ip_tunnel.c#L145">145</a> <b><i>   it will match only keyless tunnel.</i></b>
<a name="L146" href="source/net/ipv4/ip_tunnel.c#L146">146</a> <b><i></i></b>
<a name="L147" href="source/net/ipv4/ip_tunnel.c#L147">147</a> <b><i>   All keysless packets, if not matched configured keyless tunnels</i></b>
<a name="L148" href="source/net/ipv4/ip_tunnel.c#L148">148</a> <b><i>   will match fallback tunnel.</i></b>
<a name="L149" href="source/net/ipv4/ip_tunnel.c#L149">149</a> <b><i>   Given src, dst and key, find appropriate for input tunnel.</i></b>
<a name="L150" href="source/net/ipv4/ip_tunnel.c#L150">150</a> <b><i>*/</i></b>
<a name="L151" href="source/net/ipv4/ip_tunnel.c#L151">151</a> struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn,
<a name="L152" href="source/net/ipv4/ip_tunnel.c#L152">152</a>                                    int <a href="ident?i=link">link</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=flags">flags</a>,
<a name="L153" href="source/net/ipv4/ip_tunnel.c#L153">153</a>                                    <a href="ident?i=__be32">__be32</a> <a href="ident?i=remote">remote</a>, <a href="ident?i=__be32">__be32</a> local,
<a name="L154" href="source/net/ipv4/ip_tunnel.c#L154">154</a>                                    <a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a>)
<a name="L155" href="source/net/ipv4/ip_tunnel.c#L155">155</a> {
<a name="L156" href="source/net/ipv4/ip_tunnel.c#L156">156</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L157" href="source/net/ipv4/ip_tunnel.c#L157">157</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>, *<a href="ident?i=cand">cand</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L158" href="source/net/ipv4/ip_tunnel.c#L158">158</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L159" href="source/net/ipv4/ip_tunnel.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/ip_tunnel.c#L160">160</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=ip_tunnel_hash">ip_tunnel_hash</a>(<a href="ident?i=key">key</a>, <a href="ident?i=remote">remote</a>);
<a name="L161" href="source/net/ipv4/ip_tunnel.c#L161">161</a>         <a href="ident?i=head">head</a> = &amp;itn-&gt;<a href="ident?i=tunnels">tunnels</a>[<a href="ident?i=hash">hash</a>];
<a name="L162" href="source/net/ipv4/ip_tunnel.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/ip_tunnel.c#L163">163</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=t">t</a>, <a href="ident?i=head">head</a>, hash_node) {
<a name="L164" href="source/net/ipv4/ip_tunnel.c#L164">164</a>                 if (local != <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a> ||
<a name="L165" href="source/net/ipv4/ip_tunnel.c#L165">165</a>                     <a href="ident?i=remote">remote</a> != <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> ||
<a name="L166" href="source/net/ipv4/ip_tunnel.c#L166">166</a>                     !(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L167" href="source/net/ipv4/ip_tunnel.c#L167">167</a>                         continue;
<a name="L168" href="source/net/ipv4/ip_tunnel.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/ip_tunnel.c#L169">169</a>                 if (!<a href="ident?i=ip_tunnel_key_match">ip_tunnel_key_match</a>(&amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>, <a href="ident?i=flags">flags</a>, <a href="ident?i=key">key</a>))
<a name="L170" href="source/net/ipv4/ip_tunnel.c#L170">170</a>                         continue;
<a name="L171" href="source/net/ipv4/ip_tunnel.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/ip_tunnel.c#L172">172</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> == <a href="ident?i=link">link</a>)
<a name="L173" href="source/net/ipv4/ip_tunnel.c#L173">173</a>                         return <a href="ident?i=t">t</a>;
<a name="L174" href="source/net/ipv4/ip_tunnel.c#L174">174</a>                 else
<a name="L175" href="source/net/ipv4/ip_tunnel.c#L175">175</a>                         <a href="ident?i=cand">cand</a> = <a href="ident?i=t">t</a>;
<a name="L176" href="source/net/ipv4/ip_tunnel.c#L176">176</a>         }
<a name="L177" href="source/net/ipv4/ip_tunnel.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/ip_tunnel.c#L178">178</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=t">t</a>, <a href="ident?i=head">head</a>, hash_node) {
<a name="L179" href="source/net/ipv4/ip_tunnel.c#L179">179</a>                 if (<a href="ident?i=remote">remote</a> != <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> ||
<a name="L180" href="source/net/ipv4/ip_tunnel.c#L180">180</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a> != 0 ||
<a name="L181" href="source/net/ipv4/ip_tunnel.c#L181">181</a>                     !(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L182" href="source/net/ipv4/ip_tunnel.c#L182">182</a>                         continue;
<a name="L183" href="source/net/ipv4/ip_tunnel.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/ip_tunnel.c#L184">184</a>                 if (!<a href="ident?i=ip_tunnel_key_match">ip_tunnel_key_match</a>(&amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>, <a href="ident?i=flags">flags</a>, <a href="ident?i=key">key</a>))
<a name="L185" href="source/net/ipv4/ip_tunnel.c#L185">185</a>                         continue;
<a name="L186" href="source/net/ipv4/ip_tunnel.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/ip_tunnel.c#L187">187</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> == <a href="ident?i=link">link</a>)
<a name="L188" href="source/net/ipv4/ip_tunnel.c#L188">188</a>                         return <a href="ident?i=t">t</a>;
<a name="L189" href="source/net/ipv4/ip_tunnel.c#L189">189</a>                 else if (!<a href="ident?i=cand">cand</a>)
<a name="L190" href="source/net/ipv4/ip_tunnel.c#L190">190</a>                         <a href="ident?i=cand">cand</a> = <a href="ident?i=t">t</a>;
<a name="L191" href="source/net/ipv4/ip_tunnel.c#L191">191</a>         }
<a name="L192" href="source/net/ipv4/ip_tunnel.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/ip_tunnel.c#L193">193</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=ip_tunnel_hash">ip_tunnel_hash</a>(<a href="ident?i=key">key</a>, 0);
<a name="L194" href="source/net/ipv4/ip_tunnel.c#L194">194</a>         <a href="ident?i=head">head</a> = &amp;itn-&gt;<a href="ident?i=tunnels">tunnels</a>[<a href="ident?i=hash">hash</a>];
<a name="L195" href="source/net/ipv4/ip_tunnel.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/ip_tunnel.c#L196">196</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=t">t</a>, <a href="ident?i=head">head</a>, hash_node) {
<a name="L197" href="source/net/ipv4/ip_tunnel.c#L197">197</a>                 if ((local != <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a> || <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> != 0) &amp;&amp;
<a name="L198" href="source/net/ipv4/ip_tunnel.c#L198">198</a>                     (local != <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> || !<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(local)))
<a name="L199" href="source/net/ipv4/ip_tunnel.c#L199">199</a>                         continue;
<a name="L200" href="source/net/ipv4/ip_tunnel.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/ip_tunnel.c#L201">201</a>                 if (!(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L202" href="source/net/ipv4/ip_tunnel.c#L202">202</a>                         continue;
<a name="L203" href="source/net/ipv4/ip_tunnel.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ip_tunnel.c#L204">204</a>                 if (!<a href="ident?i=ip_tunnel_key_match">ip_tunnel_key_match</a>(&amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>, <a href="ident?i=flags">flags</a>, <a href="ident?i=key">key</a>))
<a name="L205" href="source/net/ipv4/ip_tunnel.c#L205">205</a>                         continue;
<a name="L206" href="source/net/ipv4/ip_tunnel.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/ip_tunnel.c#L207">207</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> == <a href="ident?i=link">link</a>)
<a name="L208" href="source/net/ipv4/ip_tunnel.c#L208">208</a>                         return <a href="ident?i=t">t</a>;
<a name="L209" href="source/net/ipv4/ip_tunnel.c#L209">209</a>                 else if (!<a href="ident?i=cand">cand</a>)
<a name="L210" href="source/net/ipv4/ip_tunnel.c#L210">210</a>                         <a href="ident?i=cand">cand</a> = <a href="ident?i=t">t</a>;
<a name="L211" href="source/net/ipv4/ip_tunnel.c#L211">211</a>         }
<a name="L212" href="source/net/ipv4/ip_tunnel.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/ip_tunnel.c#L213">213</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_NO_KEY">TUNNEL_NO_KEY</a>)
<a name="L214" href="source/net/ipv4/ip_tunnel.c#L214">214</a>                 goto skip_key_lookup;
<a name="L215" href="source/net/ipv4/ip_tunnel.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/ip_tunnel.c#L216">216</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=t">t</a>, <a href="ident?i=head">head</a>, hash_node) {
<a name="L217" href="source/net/ipv4/ip_tunnel.c#L217">217</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.i_key != <a href="ident?i=key">key</a> ||
<a name="L218" href="source/net/ipv4/ip_tunnel.c#L218">218</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a> != 0 ||
<a name="L219" href="source/net/ipv4/ip_tunnel.c#L219">219</a>                     <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> != 0 ||
<a name="L220" href="source/net/ipv4/ip_tunnel.c#L220">220</a>                     !(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L221" href="source/net/ipv4/ip_tunnel.c#L221">221</a>                         continue;
<a name="L222" href="source/net/ipv4/ip_tunnel.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/ip_tunnel.c#L223">223</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> == <a href="ident?i=link">link</a>)
<a name="L224" href="source/net/ipv4/ip_tunnel.c#L224">224</a>                         return <a href="ident?i=t">t</a>;
<a name="L225" href="source/net/ipv4/ip_tunnel.c#L225">225</a>                 else if (!<a href="ident?i=cand">cand</a>)
<a name="L226" href="source/net/ipv4/ip_tunnel.c#L226">226</a>                         <a href="ident?i=cand">cand</a> = <a href="ident?i=t">t</a>;
<a name="L227" href="source/net/ipv4/ip_tunnel.c#L227">227</a>         }
<a name="L228" href="source/net/ipv4/ip_tunnel.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/ip_tunnel.c#L229">229</a> skip_key_lookup:
<a name="L230" href="source/net/ipv4/ip_tunnel.c#L230">230</a>         if (<a href="ident?i=cand">cand</a>)
<a name="L231" href="source/net/ipv4/ip_tunnel.c#L231">231</a>                 return <a href="ident?i=cand">cand</a>;
<a name="L232" href="source/net/ipv4/ip_tunnel.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/ip_tunnel.c#L233">233</a>         if (itn-&gt;fb_tunnel_dev &amp;&amp; itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>)
<a name="L234" href="source/net/ipv4/ip_tunnel.c#L234">234</a>                 return <a href="ident?i=netdev_priv">netdev_priv</a>(itn-&gt;fb_tunnel_dev);
<a name="L235" href="source/net/ipv4/ip_tunnel.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/ip_tunnel.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/ip_tunnel.c#L237">237</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L238" href="source/net/ipv4/ip_tunnel.c#L238">238</a> }
<a name="L239" href="source/net/ipv4/ip_tunnel.c#L239">239</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>);
<a name="L240" href="source/net/ipv4/ip_tunnel.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/ip_tunnel.c#L241">241</a> static struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=ip_bucket">ip_bucket</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn,
<a name="L242" href="source/net/ipv4/ip_tunnel.c#L242">242</a>                                     struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>)
<a name="L243" href="source/net/ipv4/ip_tunnel.c#L243">243</a> {
<a name="L244" href="source/net/ipv4/ip_tunnel.c#L244">244</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L245" href="source/net/ipv4/ip_tunnel.c#L245">245</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=remote">remote</a>;
<a name="L246" href="source/net/ipv4/ip_tunnel.c#L246">246</a>         <a href="ident?i=__be32">__be32</a> i_key = <a href="ident?i=parms">parms</a>-&gt;i_key;
<a name="L247" href="source/net/ipv4/ip_tunnel.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/ip_tunnel.c#L248">248</a>         if (<a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a> &amp;&amp; !<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>))
<a name="L249" href="source/net/ipv4/ip_tunnel.c#L249">249</a>                 <a href="ident?i=remote">remote</a> = <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>;
<a name="L250" href="source/net/ipv4/ip_tunnel.c#L250">250</a>         else
<a name="L251" href="source/net/ipv4/ip_tunnel.c#L251">251</a>                 <a href="ident?i=remote">remote</a> = 0;
<a name="L252" href="source/net/ipv4/ip_tunnel.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/ip_tunnel.c#L253">253</a>         if (!(<a href="ident?i=parms">parms</a>-&gt;i_flags &amp; <a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>) &amp;&amp; (<a href="ident?i=parms">parms</a>-&gt;i_flags &amp; <a href="ident?i=VTI_ISVTI">VTI_ISVTI</a>))
<a name="L254" href="source/net/ipv4/ip_tunnel.c#L254">254</a>                 i_key = 0;
<a name="L255" href="source/net/ipv4/ip_tunnel.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/ip_tunnel.c#L256">256</a>         <a href="ident?i=h">h</a> = <a href="ident?i=ip_tunnel_hash">ip_tunnel_hash</a>(i_key, <a href="ident?i=remote">remote</a>);
<a name="L257" href="source/net/ipv4/ip_tunnel.c#L257">257</a>         return &amp;itn-&gt;<a href="ident?i=tunnels">tunnels</a>[<a href="ident?i=h">h</a>];
<a name="L258" href="source/net/ipv4/ip_tunnel.c#L258">258</a> }
<a name="L259" href="source/net/ipv4/ip_tunnel.c#L259">259</a> 
<a name="L260" href="source/net/ipv4/ip_tunnel.c#L260">260</a> static void <a href="ident?i=ip_tunnel_add">ip_tunnel_add</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn, struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>)
<a name="L261" href="source/net/ipv4/ip_tunnel.c#L261">261</a> {
<a name="L262" href="source/net/ipv4/ip_tunnel.c#L262">262</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = <a href="ident?i=ip_bucket">ip_bucket</a>(itn, &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>);
<a name="L263" href="source/net/ipv4/ip_tunnel.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/ip_tunnel.c#L264">264</a>         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;<a href="ident?i=t">t</a>-&gt;hash_node, <a href="ident?i=head">head</a>);
<a name="L265" href="source/net/ipv4/ip_tunnel.c#L265">265</a> }
<a name="L266" href="source/net/ipv4/ip_tunnel.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/ip_tunnel.c#L267">267</a> static void <a href="ident?i=ip_tunnel_del">ip_tunnel_del</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>)
<a name="L268" href="source/net/ipv4/ip_tunnel.c#L268">268</a> {
<a name="L269" href="source/net/ipv4/ip_tunnel.c#L269">269</a>         <a href="ident?i=hlist_del_init_rcu">hlist_del_init_rcu</a>(&amp;<a href="ident?i=t">t</a>-&gt;hash_node);
<a name="L270" href="source/net/ipv4/ip_tunnel.c#L270">270</a> }
<a name="L271" href="source/net/ipv4/ip_tunnel.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/ip_tunnel.c#L272">272</a> static struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=ip_tunnel_find">ip_tunnel_find</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn,
<a name="L273" href="source/net/ipv4/ip_tunnel.c#L273">273</a>                                         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>,
<a name="L274" href="source/net/ipv4/ip_tunnel.c#L274">274</a>                                         int <a href="ident?i=type">type</a>)
<a name="L275" href="source/net/ipv4/ip_tunnel.c#L275">275</a> {
<a name="L276" href="source/net/ipv4/ip_tunnel.c#L276">276</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=remote">remote</a> = <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>;
<a name="L277" href="source/net/ipv4/ip_tunnel.c#L277">277</a>         <a href="ident?i=__be32">__be32</a> local = <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>;
<a name="L278" href="source/net/ipv4/ip_tunnel.c#L278">278</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a> = <a href="ident?i=parms">parms</a>-&gt;i_key;
<a name="L279" href="source/net/ipv4/ip_tunnel.c#L279">279</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=flags">flags</a> = <a href="ident?i=parms">parms</a>-&gt;i_flags;
<a name="L280" href="source/net/ipv4/ip_tunnel.c#L280">280</a>         int <a href="ident?i=link">link</a> = <a href="ident?i=parms">parms</a>-&gt;<a href="ident?i=link">link</a>;
<a name="L281" href="source/net/ipv4/ip_tunnel.c#L281">281</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L282" href="source/net/ipv4/ip_tunnel.c#L282">282</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = <a href="ident?i=ip_bucket">ip_bucket</a>(itn, <a href="ident?i=parms">parms</a>);
<a name="L283" href="source/net/ipv4/ip_tunnel.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/ip_tunnel.c#L284">284</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=t">t</a>, <a href="ident?i=head">head</a>, hash_node) {
<a name="L285" href="source/net/ipv4/ip_tunnel.c#L285">285</a>                 if (local == <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a> &amp;&amp;
<a name="L286" href="source/net/ipv4/ip_tunnel.c#L286">286</a>                     <a href="ident?i=remote">remote</a> == <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> &amp;&amp;
<a name="L287" href="source/net/ipv4/ip_tunnel.c#L287">287</a>                     <a href="ident?i=link">link</a> == <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> &amp;&amp;
<a name="L288" href="source/net/ipv4/ip_tunnel.c#L288">288</a>                     <a href="ident?i=type">type</a> == <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> &amp;&amp;
<a name="L289" href="source/net/ipv4/ip_tunnel.c#L289">289</a>                     <a href="ident?i=ip_tunnel_key_match">ip_tunnel_key_match</a>(&amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>, <a href="ident?i=flags">flags</a>, <a href="ident?i=key">key</a>))
<a name="L290" href="source/net/ipv4/ip_tunnel.c#L290">290</a>                         break;
<a name="L291" href="source/net/ipv4/ip_tunnel.c#L291">291</a>         }
<a name="L292" href="source/net/ipv4/ip_tunnel.c#L292">292</a>         return <a href="ident?i=t">t</a>;
<a name="L293" href="source/net/ipv4/ip_tunnel.c#L293">293</a> }
<a name="L294" href="source/net/ipv4/ip_tunnel.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/ip_tunnel.c#L295">295</a> static struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=__ip_tunnel_create">__ip_tunnel_create</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L296" href="source/net/ipv4/ip_tunnel.c#L296">296</a>                                              const struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L297" href="source/net/ipv4/ip_tunnel.c#L297">297</a>                                              struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>)
<a name="L298" href="source/net/ipv4/ip_tunnel.c#L298">298</a> {
<a name="L299" href="source/net/ipv4/ip_tunnel.c#L299">299</a>         int <a href="ident?i=err">err</a>;
<a name="L300" href="source/net/ipv4/ip_tunnel.c#L300">300</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel;
<a name="L301" href="source/net/ipv4/ip_tunnel.c#L301">301</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L302" href="source/net/ipv4/ip_tunnel.c#L302">302</a>         char <a href="ident?i=name">name</a>[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>];
<a name="L303" href="source/net/ipv4/ip_tunnel.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/ip_tunnel.c#L304">304</a>         if (<a href="ident?i=parms">parms</a>-&gt;<a href="ident?i=name">name</a>[0])
<a name="L305" href="source/net/ipv4/ip_tunnel.c#L305">305</a>                 <a href="ident?i=strlcpy">strlcpy</a>(<a href="ident?i=name">name</a>, <a href="ident?i=parms">parms</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L306" href="source/net/ipv4/ip_tunnel.c#L306">306</a>         else {
<a name="L307" href="source/net/ipv4/ip_tunnel.c#L307">307</a>                 if (<a href="ident?i=strlen">strlen</a>(<a href="ident?i=ops">ops</a>-&gt;kind) &gt; (<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a> - 3)) {
<a name="L308" href="source/net/ipv4/ip_tunnel.c#L308">308</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=E2BIG">E2BIG</a>;
<a name="L309" href="source/net/ipv4/ip_tunnel.c#L309">309</a>                         goto <a href="ident?i=failed">failed</a>;
<a name="L310" href="source/net/ipv4/ip_tunnel.c#L310">310</a>                 }
<a name="L311" href="source/net/ipv4/ip_tunnel.c#L311">311</a>                 <a href="ident?i=strlcpy">strlcpy</a>(<a href="ident?i=name">name</a>, <a href="ident?i=ops">ops</a>-&gt;kind, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L312" href="source/net/ipv4/ip_tunnel.c#L312">312</a>                 <a href="ident?i=strncat">strncat</a>(<a href="ident?i=name">name</a>, <i>"%d"</i>, 2);
<a name="L313" href="source/net/ipv4/ip_tunnel.c#L313">313</a>         }
<a name="L314" href="source/net/ipv4/ip_tunnel.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/ip_tunnel.c#L315">315</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L316" href="source/net/ipv4/ip_tunnel.c#L316">316</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=alloc_netdev">alloc_netdev</a>(<a href="ident?i=ops">ops</a>-&gt;priv_size, <a href="ident?i=name">name</a>, <a href="ident?i=NET_NAME_UNKNOWN">NET_NAME_UNKNOWN</a>, <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=setup">setup</a>);
<a name="L317" href="source/net/ipv4/ip_tunnel.c#L317">317</a>         if (!<a href="ident?i=dev">dev</a>) {
<a name="L318" href="source/net/ipv4/ip_tunnel.c#L318">318</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L319" href="source/net/ipv4/ip_tunnel.c#L319">319</a>                 goto <a href="ident?i=failed">failed</a>;
<a name="L320" href="source/net/ipv4/ip_tunnel.c#L320">320</a>         }
<a name="L321" href="source/net/ipv4/ip_tunnel.c#L321">321</a>         <a href="ident?i=dev_net_set">dev_net_set</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=net">net</a>);
<a name="L322" href="source/net/ipv4/ip_tunnel.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/ip_tunnel.c#L323">323</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> = <a href="ident?i=ops">ops</a>;
<a name="L324" href="source/net/ipv4/ip_tunnel.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/ip_tunnel.c#L325">325</a>         tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L326" href="source/net/ipv4/ip_tunnel.c#L326">326</a>         tunnel-&gt;<a href="ident?i=parms">parms</a> = *<a href="ident?i=parms">parms</a>;
<a name="L327" href="source/net/ipv4/ip_tunnel.c#L327">327</a>         tunnel-&gt;<a href="ident?i=net">net</a> = <a href="ident?i=net">net</a>;
<a name="L328" href="source/net/ipv4/ip_tunnel.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/ip_tunnel.c#L329">329</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_netdevice">register_netdevice</a>(<a href="ident?i=dev">dev</a>);
<a name="L330" href="source/net/ipv4/ip_tunnel.c#L330">330</a>         if (<a href="ident?i=err">err</a>)
<a name="L331" href="source/net/ipv4/ip_tunnel.c#L331">331</a>                 goto failed_free;
<a name="L332" href="source/net/ipv4/ip_tunnel.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/ip_tunnel.c#L333">333</a>         return <a href="ident?i=dev">dev</a>;
<a name="L334" href="source/net/ipv4/ip_tunnel.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/ip_tunnel.c#L335">335</a> failed_free:
<a name="L336" href="source/net/ipv4/ip_tunnel.c#L336">336</a>         <a href="ident?i=free_netdev">free_netdev</a>(<a href="ident?i=dev">dev</a>);
<a name="L337" href="source/net/ipv4/ip_tunnel.c#L337">337</a> <a href="ident?i=failed">failed</a>:
<a name="L338" href="source/net/ipv4/ip_tunnel.c#L338">338</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L339" href="source/net/ipv4/ip_tunnel.c#L339">339</a> }
<a name="L340" href="source/net/ipv4/ip_tunnel.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/ip_tunnel.c#L341">341</a> static inline void <a href="ident?i=init_tunnel_flow">init_tunnel_flow</a>(struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L342" href="source/net/ipv4/ip_tunnel.c#L342">342</a>                                     int <a href="ident?i=proto">proto</a>,
<a name="L343" href="source/net/ipv4/ip_tunnel.c#L343">343</a>                                     <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L344" href="source/net/ipv4/ip_tunnel.c#L344">344</a>                                     <a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a>, <a href="ident?i=__u8">__u8</a> tos, int oif)
<a name="L345" href="source/net/ipv4/ip_tunnel.c#L345">345</a> {
<a name="L346" href="source/net/ipv4/ip_tunnel.c#L346">346</a>         <a href="ident?i=memset">memset</a>(fl4, 0, sizeof(*fl4));
<a name="L347" href="source/net/ipv4/ip_tunnel.c#L347">347</a>         fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> = oif;
<a name="L348" href="source/net/ipv4/ip_tunnel.c#L348">348</a>         fl4-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L349" href="source/net/ipv4/ip_tunnel.c#L349">349</a>         fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L350" href="source/net/ipv4/ip_tunnel.c#L350">350</a>         fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a> = tos;
<a name="L351" href="source/net/ipv4/ip_tunnel.c#L351">351</a>         fl4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a> = <a href="ident?i=proto">proto</a>;
<a name="L352" href="source/net/ipv4/ip_tunnel.c#L352">352</a>         fl4-&gt;<a href="ident?i=fl4_gre_key">fl4_gre_key</a> = <a href="ident?i=key">key</a>;
<a name="L353" href="source/net/ipv4/ip_tunnel.c#L353">353</a> }
<a name="L354" href="source/net/ipv4/ip_tunnel.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/ip_tunnel.c#L355">355</a> static int <a href="ident?i=ip_tunnel_bind_dev">ip_tunnel_bind_dev</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L356" href="source/net/ipv4/ip_tunnel.c#L356">356</a> {
<a name="L357" href="source/net/ipv4/ip_tunnel.c#L357">357</a>         struct <a href="ident?i=net_device">net_device</a> *tdev = <a href="ident?i=NULL">NULL</a>;
<a name="L358" href="source/net/ipv4/ip_tunnel.c#L358">358</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L359" href="source/net/ipv4/ip_tunnel.c#L359">359</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L360" href="source/net/ipv4/ip_tunnel.c#L360">360</a>         int hlen = <a href="ident?i=LL_MAX_HEADER">LL_MAX_HEADER</a>;
<a name="L361" href="source/net/ipv4/ip_tunnel.c#L361">361</a>         int <a href="ident?i=mtu">mtu</a> = <a href="ident?i=ETH_DATA_LEN">ETH_DATA_LEN</a>;
<a name="L362" href="source/net/ipv4/ip_tunnel.c#L362">362</a>         int t_hlen = tunnel-&gt;hlen + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L363" href="source/net/ipv4/ip_tunnel.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/ip_tunnel.c#L364">364</a>         iph = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L365" href="source/net/ipv4/ip_tunnel.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/ip_tunnel.c#L366">366</a>         <b><i>/* Guess output device to choose reasonable mtu and needed_headroom */</i></b>
<a name="L367" href="source/net/ipv4/ip_tunnel.c#L367">367</a>         if (iph-&gt;<a href="ident?i=daddr">daddr</a>) {
<a name="L368" href="source/net/ipv4/ip_tunnel.c#L368">368</a>                 struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L369" href="source/net/ipv4/ip_tunnel.c#L369">369</a>                 struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L370" href="source/net/ipv4/ip_tunnel.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/ip_tunnel.c#L371">371</a>                 <a href="ident?i=init_tunnel_flow">init_tunnel_flow</a>(&amp;fl4, iph-&gt;<a href="ident?i=protocol">protocol</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L372" href="source/net/ipv4/ip_tunnel.c#L372">372</a>                                  iph-&gt;<a href="ident?i=saddr">saddr</a>, tunnel-&gt;<a href="ident?i=parms">parms</a>.o_key,
<a name="L373" href="source/net/ipv4/ip_tunnel.c#L373">373</a>                                  <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos), tunnel-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>);
<a name="L374" href="source/net/ipv4/ip_tunnel.c#L374">374</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(tunnel-&gt;<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L375" href="source/net/ipv4/ip_tunnel.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/ip_tunnel.c#L376">376</a>                 if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L377" href="source/net/ipv4/ip_tunnel.c#L377">377</a>                         tdev = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L378" href="source/net/ipv4/ip_tunnel.c#L378">378</a>                         <a href="ident?i=tunnel_dst_set">tunnel_dst_set</a>(tunnel, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, fl4.<a href="ident?i=saddr">saddr</a>);
<a name="L379" href="source/net/ipv4/ip_tunnel.c#L379">379</a>                         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L380" href="source/net/ipv4/ip_tunnel.c#L380">380</a>                 }
<a name="L381" href="source/net/ipv4/ip_tunnel.c#L381">381</a>                 if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>)
<a name="L382" href="source/net/ipv4/ip_tunnel.c#L382">382</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>;
<a name="L383" href="source/net/ipv4/ip_tunnel.c#L383">383</a>         }
<a name="L384" href="source/net/ipv4/ip_tunnel.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/ip_tunnel.c#L385">385</a>         if (!tdev &amp;&amp; tunnel-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>)
<a name="L386" href="source/net/ipv4/ip_tunnel.c#L386">386</a>                 tdev = <a href="ident?i=__dev_get_by_index">__dev_get_by_index</a>(tunnel-&gt;<a href="ident?i=net">net</a>, tunnel-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>);
<a name="L387" href="source/net/ipv4/ip_tunnel.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/ip_tunnel.c#L388">388</a>         if (tdev) {
<a name="L389" href="source/net/ipv4/ip_tunnel.c#L389">389</a>                 hlen = tdev-&gt;hard_header_len + tdev-&gt;needed_headroom;
<a name="L390" href="source/net/ipv4/ip_tunnel.c#L390">390</a>                 <a href="ident?i=mtu">mtu</a> = tdev-&gt;<a href="ident?i=mtu">mtu</a>;
<a name="L391" href="source/net/ipv4/ip_tunnel.c#L391">391</a>         }
<a name="L392" href="source/net/ipv4/ip_tunnel.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/ip_tunnel.c#L393">393</a>         <a href="ident?i=dev">dev</a>-&gt;needed_headroom = t_hlen + hlen;
<a name="L394" href="source/net/ipv4/ip_tunnel.c#L394">394</a>         <a href="ident?i=mtu">mtu</a> -= (<a href="ident?i=dev">dev</a>-&gt;hard_header_len + t_hlen);
<a name="L395" href="source/net/ipv4/ip_tunnel.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/ip_tunnel.c#L396">396</a>         if (<a href="ident?i=mtu">mtu</a> &lt; 68)
<a name="L397" href="source/net/ipv4/ip_tunnel.c#L397">397</a>                 <a href="ident?i=mtu">mtu</a> = 68;
<a name="L398" href="source/net/ipv4/ip_tunnel.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/ip_tunnel.c#L399">399</a>         return <a href="ident?i=mtu">mtu</a>;
<a name="L400" href="source/net/ipv4/ip_tunnel.c#L400">400</a> }
<a name="L401" href="source/net/ipv4/ip_tunnel.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/ip_tunnel.c#L402">402</a> static struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=ip_tunnel_create">ip_tunnel_create</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L403" href="source/net/ipv4/ip_tunnel.c#L403">403</a>                                           struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn,
<a name="L404" href="source/net/ipv4/ip_tunnel.c#L404">404</a>                                           struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>)
<a name="L405" href="source/net/ipv4/ip_tunnel.c#L405">405</a> {
<a name="L406" href="source/net/ipv4/ip_tunnel.c#L406">406</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *nt;
<a name="L407" href="source/net/ipv4/ip_tunnel.c#L407">407</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L408" href="source/net/ipv4/ip_tunnel.c#L408">408</a> 
<a name="L409" href="source/net/ipv4/ip_tunnel.c#L409">409</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!itn-&gt;fb_tunnel_dev);
<a name="L410" href="source/net/ipv4/ip_tunnel.c#L410">410</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=__ip_tunnel_create">__ip_tunnel_create</a>(<a href="ident?i=net">net</a>, itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=rtnl_link_ops">rtnl_link_ops</a>, <a href="ident?i=parms">parms</a>);
<a name="L411" href="source/net/ipv4/ip_tunnel.c#L411">411</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=dev">dev</a>))
<a name="L412" href="source/net/ipv4/ip_tunnel.c#L412">412</a>                 return <a href="ident?i=ERR_CAST">ERR_CAST</a>(<a href="ident?i=dev">dev</a>);
<a name="L413" href="source/net/ipv4/ip_tunnel.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/ip_tunnel.c#L414">414</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a> = <a href="ident?i=ip_tunnel_bind_dev">ip_tunnel_bind_dev</a>(<a href="ident?i=dev">dev</a>);
<a name="L415" href="source/net/ipv4/ip_tunnel.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/ip_tunnel.c#L416">416</a>         nt = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L417" href="source/net/ipv4/ip_tunnel.c#L417">417</a>         <a href="ident?i=ip_tunnel_add">ip_tunnel_add</a>(itn, nt);
<a name="L418" href="source/net/ipv4/ip_tunnel.c#L418">418</a>         return nt;
<a name="L419" href="source/net/ipv4/ip_tunnel.c#L419">419</a> }
<a name="L420" href="source/net/ipv4/ip_tunnel.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/ip_tunnel.c#L421">421</a> int <a href="ident?i=ip_tunnel_rcv">ip_tunnel_rcv</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L422" href="source/net/ipv4/ip_tunnel.c#L422">422</a>                   const struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> *<a href="ident?i=tpi">tpi</a>, <a href="ident?i=bool">bool</a> <a href="ident?i=log_ecn_error">log_ecn_error</a>)
<a name="L423" href="source/net/ipv4/ip_tunnel.c#L423">423</a> {
<a name="L424" href="source/net/ipv4/ip_tunnel.c#L424">424</a>         struct <a href="ident?i=pcpu_sw_netstats">pcpu_sw_netstats</a> *tstats;
<a name="L425" href="source/net/ipv4/ip_tunnel.c#L425">425</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L426" href="source/net/ipv4/ip_tunnel.c#L426">426</a>         int <a href="ident?i=err">err</a>;
<a name="L427" href="source/net/ipv4/ip_tunnel.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/ip_tunnel.c#L428">428</a> #ifdef CONFIG_NET_IPGRE_BROADCAST
<a name="L429" href="source/net/ipv4/ip_tunnel.c#L429">429</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(iph-&gt;<a href="ident?i=daddr">daddr</a>)) {
<a name="L430" href="source/net/ipv4/ip_tunnel.c#L430">430</a>                 tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.multicast++;
<a name="L431" href="source/net/ipv4/ip_tunnel.c#L431">431</a>                 <a href="ident?i=skb">skb</a>-&gt;pkt_type = <a href="ident?i=PACKET_BROADCAST">PACKET_BROADCAST</a>;
<a name="L432" href="source/net/ipv4/ip_tunnel.c#L432">432</a>         }
<a name="L433" href="source/net/ipv4/ip_tunnel.c#L433">433</a> #endif
<a name="L434" href="source/net/ipv4/ip_tunnel.c#L434">434</a> 
<a name="L435" href="source/net/ipv4/ip_tunnel.c#L435">435</a>         if ((!(<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>) &amp;&amp;  (tunnel-&gt;<a href="ident?i=parms">parms</a>.i_flags&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>)) ||
<a name="L436" href="source/net/ipv4/ip_tunnel.c#L436">436</a>              ((<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>) &amp;&amp; !(tunnel-&gt;<a href="ident?i=parms">parms</a>.i_flags&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>))) {
<a name="L437" href="source/net/ipv4/ip_tunnel.c#L437">437</a>                 tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_crc_errors++;
<a name="L438" href="source/net/ipv4/ip_tunnel.c#L438">438</a>                 tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_errors++;
<a name="L439" href="source/net/ipv4/ip_tunnel.c#L439">439</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L440" href="source/net/ipv4/ip_tunnel.c#L440">440</a>         }
<a name="L441" href="source/net/ipv4/ip_tunnel.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/ip_tunnel.c#L442">442</a>         if (tunnel-&gt;<a href="ident?i=parms">parms</a>.i_flags&amp;<a href="ident?i=TUNNEL_SEQ">TUNNEL_SEQ</a>) {
<a name="L443" href="source/net/ipv4/ip_tunnel.c#L443">443</a>                 if (!(<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=TUNNEL_SEQ">TUNNEL_SEQ</a>) ||
<a name="L444" href="source/net/ipv4/ip_tunnel.c#L444">444</a>                     (tunnel-&gt;i_seqno &amp;&amp; (<a href="ident?i=s32">s32</a>)(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=seq">seq</a>) - tunnel-&gt;i_seqno) &lt; 0)) {
<a name="L445" href="source/net/ipv4/ip_tunnel.c#L445">445</a>                         tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_fifo_errors++;
<a name="L446" href="source/net/ipv4/ip_tunnel.c#L446">446</a>                         tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_errors++;
<a name="L447" href="source/net/ipv4/ip_tunnel.c#L447">447</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L448" href="source/net/ipv4/ip_tunnel.c#L448">448</a>                 }
<a name="L449" href="source/net/ipv4/ip_tunnel.c#L449">449</a>                 tunnel-&gt;i_seqno = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=seq">seq</a>) + 1;
<a name="L450" href="source/net/ipv4/ip_tunnel.c#L450">450</a>         }
<a name="L451" href="source/net/ipv4/ip_tunnel.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/ip_tunnel.c#L452">452</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L453" href="source/net/ipv4/ip_tunnel.c#L453">453</a> 
<a name="L454" href="source/net/ipv4/ip_tunnel.c#L454">454</a>         <a href="ident?i=err">err</a> = <a href="ident?i=IP_ECN_decapsulate">IP_ECN_decapsulate</a>(iph, <a href="ident?i=skb">skb</a>);
<a name="L455" href="source/net/ipv4/ip_tunnel.c#L455">455</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>)) {
<a name="L456" href="source/net/ipv4/ip_tunnel.c#L456">456</a>                 if (<a href="ident?i=log_ecn_error">log_ecn_error</a>)
<a name="L457" href="source/net/ipv4/ip_tunnel.c#L457">457</a>                         <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"non-ECT from %pI4 with TOS=%#x\n"</i>,
<a name="L458" href="source/net/ipv4/ip_tunnel.c#L458">458</a>                                         &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;tos);
<a name="L459" href="source/net/ipv4/ip_tunnel.c#L459">459</a>                 if (<a href="ident?i=err">err</a> &gt; 1) {
<a name="L460" href="source/net/ipv4/ip_tunnel.c#L460">460</a>                         ++tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_frame_errors;
<a name="L461" href="source/net/ipv4/ip_tunnel.c#L461">461</a>                         ++tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_errors;
<a name="L462" href="source/net/ipv4/ip_tunnel.c#L462">462</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L463" href="source/net/ipv4/ip_tunnel.c#L463">463</a>                 }
<a name="L464" href="source/net/ipv4/ip_tunnel.c#L464">464</a>         }
<a name="L465" href="source/net/ipv4/ip_tunnel.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/ip_tunnel.c#L466">466</a>         tstats = <a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L467" href="source/net/ipv4/ip_tunnel.c#L467">467</a>         <a href="ident?i=u64_stats_update_begin">u64_stats_update_begin</a>(&amp;tstats-&gt;syncp);
<a name="L468" href="source/net/ipv4/ip_tunnel.c#L468">468</a>         tstats-&gt;rx_packets++;
<a name="L469" href="source/net/ipv4/ip_tunnel.c#L469">469</a>         tstats-&gt;<a href="ident?i=rx_bytes">rx_bytes</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L470" href="source/net/ipv4/ip_tunnel.c#L470">470</a>         <a href="ident?i=u64_stats_update_end">u64_stats_update_end</a>(&amp;tstats-&gt;syncp);
<a name="L471" href="source/net/ipv4/ip_tunnel.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/ip_tunnel.c#L472">472</a>         <a href="ident?i=skb_scrub_packet">skb_scrub_packet</a>(<a href="ident?i=skb">skb</a>, !<a href="ident?i=net_eq">net_eq</a>(tunnel-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=dev_net">dev_net</a>(tunnel-&gt;<a href="ident?i=dev">dev</a>)));
<a name="L473" href="source/net/ipv4/ip_tunnel.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/ip_tunnel.c#L474">474</a>         if (tunnel-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>) {
<a name="L475" href="source/net/ipv4/ip_tunnel.c#L475">475</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=eth_type_trans">eth_type_trans</a>(<a href="ident?i=skb">skb</a>, tunnel-&gt;<a href="ident?i=dev">dev</a>);
<a name="L476" href="source/net/ipv4/ip_tunnel.c#L476">476</a>                 <a href="ident?i=skb_postpull_rcsum">skb_postpull_rcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=eth_hdr">eth_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=ETH_HLEN">ETH_HLEN</a>);
<a name="L477" href="source/net/ipv4/ip_tunnel.c#L477">477</a>         } else {
<a name="L478" href="source/net/ipv4/ip_tunnel.c#L478">478</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = tunnel-&gt;<a href="ident?i=dev">dev</a>;
<a name="L479" href="source/net/ipv4/ip_tunnel.c#L479">479</a>         }
<a name="L480" href="source/net/ipv4/ip_tunnel.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/ip_tunnel.c#L481">481</a>         <a href="ident?i=gro_cells_receive">gro_cells_receive</a>(&amp;tunnel-&gt;<a href="ident?i=gro_cells">gro_cells</a>, <a href="ident?i=skb">skb</a>);
<a name="L482" href="source/net/ipv4/ip_tunnel.c#L482">482</a>         return 0;
<a name="L483" href="source/net/ipv4/ip_tunnel.c#L483">483</a> 
<a name="L484" href="source/net/ipv4/ip_tunnel.c#L484">484</a> <a href="ident?i=drop">drop</a>:
<a name="L485" href="source/net/ipv4/ip_tunnel.c#L485">485</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L486" href="source/net/ipv4/ip_tunnel.c#L486">486</a>         return 0;
<a name="L487" href="source/net/ipv4/ip_tunnel.c#L487">487</a> }
<a name="L488" href="source/net/ipv4/ip_tunnel.c#L488">488</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_rcv">ip_tunnel_rcv</a>);
<a name="L489" href="source/net/ipv4/ip_tunnel.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/ip_tunnel.c#L490">490</a> static int <a href="ident?i=ip_encap_hlen">ip_encap_hlen</a>(struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *<a href="ident?i=e">e</a>)
<a name="L491" href="source/net/ipv4/ip_tunnel.c#L491">491</a> {
<a name="L492" href="source/net/ipv4/ip_tunnel.c#L492">492</a>         const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> *<a href="ident?i=ops">ops</a>;
<a name="L493" href="source/net/ipv4/ip_tunnel.c#L493">493</a>         int hlen = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L494" href="source/net/ipv4/ip_tunnel.c#L494">494</a> 
<a name="L495" href="source/net/ipv4/ip_tunnel.c#L495">495</a>         if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=type">type</a> == TUNNEL_ENCAP_NONE)
<a name="L496" href="source/net/ipv4/ip_tunnel.c#L496">496</a>                 return 0;
<a name="L497" href="source/net/ipv4/ip_tunnel.c#L497">497</a> 
<a name="L498" href="source/net/ipv4/ip_tunnel.c#L498">498</a>         if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=type">type</a> &gt;= <a href="ident?i=MAX_IPTUN_ENCAP_OPS">MAX_IPTUN_ENCAP_OPS</a>)
<a name="L499" href="source/net/ipv4/ip_tunnel.c#L499">499</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L500" href="source/net/ipv4/ip_tunnel.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/ip_tunnel.c#L501">501</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L502" href="source/net/ipv4/ip_tunnel.c#L502">502</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=iptun_encaps">iptun_encaps</a>[<a href="ident?i=e">e</a>-&gt;<a href="ident?i=type">type</a>]);
<a name="L503" href="source/net/ipv4/ip_tunnel.c#L503">503</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=ops">ops</a> &amp;&amp; <a href="ident?i=ops">ops</a>-&gt;encap_hlen))
<a name="L504" href="source/net/ipv4/ip_tunnel.c#L504">504</a>                 hlen = <a href="ident?i=ops">ops</a>-&gt;encap_hlen(<a href="ident?i=e">e</a>);
<a name="L505" href="source/net/ipv4/ip_tunnel.c#L505">505</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L506" href="source/net/ipv4/ip_tunnel.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/ip_tunnel.c#L507">507</a>         return hlen;
<a name="L508" href="source/net/ipv4/ip_tunnel.c#L508">508</a> }
<a name="L509" href="source/net/ipv4/ip_tunnel.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/ip_tunnel.c#L510">510</a> const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> <a href="ident?i=__rcu">__rcu</a> *
<a name="L511" href="source/net/ipv4/ip_tunnel.c#L511">511</a>                 <a href="ident?i=iptun_encaps">iptun_encaps</a>[<a href="ident?i=MAX_IPTUN_ENCAP_OPS">MAX_IPTUN_ENCAP_OPS</a>] <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L512" href="source/net/ipv4/ip_tunnel.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/ip_tunnel.c#L513">513</a> int <a href="ident?i=ip_tunnel_encap_add_ops">ip_tunnel_encap_add_ops</a>(const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L514" href="source/net/ipv4/ip_tunnel.c#L514">514</a>                             unsigned int <a href="ident?i=num">num</a>)
<a name="L515" href="source/net/ipv4/ip_tunnel.c#L515">515</a> {
<a name="L516" href="source/net/ipv4/ip_tunnel.c#L516">516</a>         if (<a href="ident?i=num">num</a> &gt;= <a href="ident?i=MAX_IPTUN_ENCAP_OPS">MAX_IPTUN_ENCAP_OPS</a>)
<a name="L517" href="source/net/ipv4/ip_tunnel.c#L517">517</a>                 return -<a href="ident?i=ERANGE">ERANGE</a>;
<a name="L518" href="source/net/ipv4/ip_tunnel.c#L518">518</a> 
<a name="L519" href="source/net/ipv4/ip_tunnel.c#L519">519</a>         return !<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> **)
<a name="L520" href="source/net/ipv4/ip_tunnel.c#L520">520</a>                         &amp;<a href="ident?i=iptun_encaps">iptun_encaps</a>[<a href="ident?i=num">num</a>],
<a name="L521" href="source/net/ipv4/ip_tunnel.c#L521">521</a>                         <a href="ident?i=NULL">NULL</a>, <a href="ident?i=ops">ops</a>) ? 0 : -1;
<a name="L522" href="source/net/ipv4/ip_tunnel.c#L522">522</a> }
<a name="L523" href="source/net/ipv4/ip_tunnel.c#L523">523</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tunnel_encap_add_ops">ip_tunnel_encap_add_ops</a>);
<a name="L524" href="source/net/ipv4/ip_tunnel.c#L524">524</a> 
<a name="L525" href="source/net/ipv4/ip_tunnel.c#L525">525</a> int <a href="ident?i=ip_tunnel_encap_del_ops">ip_tunnel_encap_del_ops</a>(const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L526" href="source/net/ipv4/ip_tunnel.c#L526">526</a>                             unsigned int <a href="ident?i=num">num</a>)
<a name="L527" href="source/net/ipv4/ip_tunnel.c#L527">527</a> {
<a name="L528" href="source/net/ipv4/ip_tunnel.c#L528">528</a>         int <a href="ident?i=ret">ret</a>;
<a name="L529" href="source/net/ipv4/ip_tunnel.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/ip_tunnel.c#L530">530</a>         if (<a href="ident?i=num">num</a> &gt;= <a href="ident?i=MAX_IPTUN_ENCAP_OPS">MAX_IPTUN_ENCAP_OPS</a>)
<a name="L531" href="source/net/ipv4/ip_tunnel.c#L531">531</a>                 return -<a href="ident?i=ERANGE">ERANGE</a>;
<a name="L532" href="source/net/ipv4/ip_tunnel.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/ip_tunnel.c#L533">533</a>         <a href="ident?i=ret">ret</a> = (<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> **)
<a name="L534" href="source/net/ipv4/ip_tunnel.c#L534">534</a>                        &amp;<a href="ident?i=iptun_encaps">iptun_encaps</a>[<a href="ident?i=num">num</a>],
<a name="L535" href="source/net/ipv4/ip_tunnel.c#L535">535</a>                        <a href="ident?i=ops">ops</a>, <a href="ident?i=NULL">NULL</a>) == <a href="ident?i=ops">ops</a>) ? 0 : -1;
<a name="L536" href="source/net/ipv4/ip_tunnel.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/ip_tunnel.c#L537">537</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
<a name="L538" href="source/net/ipv4/ip_tunnel.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/ip_tunnel.c#L539">539</a>         return <a href="ident?i=ret">ret</a>;
<a name="L540" href="source/net/ipv4/ip_tunnel.c#L540">540</a> }
<a name="L541" href="source/net/ipv4/ip_tunnel.c#L541">541</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tunnel_encap_del_ops">ip_tunnel_encap_del_ops</a>);
<a name="L542" href="source/net/ipv4/ip_tunnel.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/ip_tunnel.c#L543">543</a> int <a href="ident?i=ip_tunnel_encap_setup">ip_tunnel_encap_setup</a>(struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>,
<a name="L544" href="source/net/ipv4/ip_tunnel.c#L544">544</a>                           struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *ipencap)
<a name="L545" href="source/net/ipv4/ip_tunnel.c#L545">545</a> {
<a name="L546" href="source/net/ipv4/ip_tunnel.c#L546">546</a>         int hlen;
<a name="L547" href="source/net/ipv4/ip_tunnel.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/ip_tunnel.c#L548">548</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=t">t</a>-&gt;encap, 0, sizeof(<a href="ident?i=t">t</a>-&gt;encap));
<a name="L549" href="source/net/ipv4/ip_tunnel.c#L549">549</a> 
<a name="L550" href="source/net/ipv4/ip_tunnel.c#L550">550</a>         hlen = <a href="ident?i=ip_encap_hlen">ip_encap_hlen</a>(ipencap);
<a name="L551" href="source/net/ipv4/ip_tunnel.c#L551">551</a>         if (hlen &lt; 0)
<a name="L552" href="source/net/ipv4/ip_tunnel.c#L552">552</a>                 return hlen;
<a name="L553" href="source/net/ipv4/ip_tunnel.c#L553">553</a> 
<a name="L554" href="source/net/ipv4/ip_tunnel.c#L554">554</a>         <a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=type">type</a> = ipencap-&gt;<a href="ident?i=type">type</a>;
<a name="L555" href="source/net/ipv4/ip_tunnel.c#L555">555</a>         <a href="ident?i=t">t</a>-&gt;encap.sport = ipencap-&gt;sport;
<a name="L556" href="source/net/ipv4/ip_tunnel.c#L556">556</a>         <a href="ident?i=t">t</a>-&gt;encap.dport = ipencap-&gt;dport;
<a name="L557" href="source/net/ipv4/ip_tunnel.c#L557">557</a>         <a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=flags">flags</a> = ipencap-&gt;<a href="ident?i=flags">flags</a>;
<a name="L558" href="source/net/ipv4/ip_tunnel.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/ip_tunnel.c#L559">559</a>         <a href="ident?i=t">t</a>-&gt;encap_hlen = hlen;
<a name="L560" href="source/net/ipv4/ip_tunnel.c#L560">560</a>         <a href="ident?i=t">t</a>-&gt;hlen = <a href="ident?i=t">t</a>-&gt;encap_hlen + <a href="ident?i=t">t</a>-&gt;tun_hlen;
<a name="L561" href="source/net/ipv4/ip_tunnel.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/ip_tunnel.c#L562">562</a>         return 0;
<a name="L563" href="source/net/ipv4/ip_tunnel.c#L563">563</a> }
<a name="L564" href="source/net/ipv4/ip_tunnel.c#L564">564</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_encap_setup">ip_tunnel_encap_setup</a>);
<a name="L565" href="source/net/ipv4/ip_tunnel.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/ip_tunnel.c#L566">566</a> int <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>,
<a name="L567" href="source/net/ipv4/ip_tunnel.c#L567">567</a>                     <a href="ident?i=u8">u8</a> *<a href="ident?i=protocol">protocol</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L568" href="source/net/ipv4/ip_tunnel.c#L568">568</a> {
<a name="L569" href="source/net/ipv4/ip_tunnel.c#L569">569</a>         const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> *<a href="ident?i=ops">ops</a>;
<a name="L570" href="source/net/ipv4/ip_tunnel.c#L570">570</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L571" href="source/net/ipv4/ip_tunnel.c#L571">571</a> 
<a name="L572" href="source/net/ipv4/ip_tunnel.c#L572">572</a>         if (<a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=type">type</a> == TUNNEL_ENCAP_NONE)
<a name="L573" href="source/net/ipv4/ip_tunnel.c#L573">573</a>                 return 0;
<a name="L574" href="source/net/ipv4/ip_tunnel.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/ip_tunnel.c#L575">575</a>         if (<a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=type">type</a> &gt;= <a href="ident?i=MAX_IPTUN_ENCAP_OPS">MAX_IPTUN_ENCAP_OPS</a>)
<a name="L576" href="source/net/ipv4/ip_tunnel.c#L576">576</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L577" href="source/net/ipv4/ip_tunnel.c#L577">577</a> 
<a name="L578" href="source/net/ipv4/ip_tunnel.c#L578">578</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L579" href="source/net/ipv4/ip_tunnel.c#L579">579</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=iptun_encaps">iptun_encaps</a>[<a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=type">type</a>]);
<a name="L580" href="source/net/ipv4/ip_tunnel.c#L580">580</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=ops">ops</a> &amp;&amp; <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=build_header">build_header</a>))
<a name="L581" href="source/net/ipv4/ip_tunnel.c#L581">581</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=build_header">build_header</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=t">t</a>-&gt;encap, <a href="ident?i=protocol">protocol</a>, fl4);
<a name="L582" href="source/net/ipv4/ip_tunnel.c#L582">582</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L583" href="source/net/ipv4/ip_tunnel.c#L583">583</a> 
<a name="L584" href="source/net/ipv4/ip_tunnel.c#L584">584</a>         return <a href="ident?i=ret">ret</a>;
<a name="L585" href="source/net/ipv4/ip_tunnel.c#L585">585</a> }
<a name="L586" href="source/net/ipv4/ip_tunnel.c#L586">586</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a>);
<a name="L587" href="source/net/ipv4/ip_tunnel.c#L587">587</a> 
<a name="L588" href="source/net/ipv4/ip_tunnel.c#L588">588</a> static int <a href="ident?i=tnl_update_pmtu">tnl_update_pmtu</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L589" href="source/net/ipv4/ip_tunnel.c#L589">589</a>                             struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=df">df</a>)
<a name="L590" href="source/net/ipv4/ip_tunnel.c#L590">590</a> {
<a name="L591" href="source/net/ipv4/ip_tunnel.c#L591">591</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L592" href="source/net/ipv4/ip_tunnel.c#L592">592</a>         int pkt_size = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - tunnel-&gt;hlen - <a href="ident?i=dev">dev</a>-&gt;hard_header_len;
<a name="L593" href="source/net/ipv4/ip_tunnel.c#L593">593</a>         int <a href="ident?i=mtu">mtu</a>;
<a name="L594" href="source/net/ipv4/ip_tunnel.c#L594">594</a> 
<a name="L595" href="source/net/ipv4/ip_tunnel.c#L595">595</a>         if (<a href="ident?i=df">df</a>)
<a name="L596" href="source/net/ipv4/ip_tunnel.c#L596">596</a>                 <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst_mtu">dst_mtu</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>) - <a href="ident?i=dev">dev</a>-&gt;hard_header_len
<a name="L597" href="source/net/ipv4/ip_tunnel.c#L597">597</a>                                         - sizeof(struct <a href="ident?i=iphdr">iphdr</a>) - tunnel-&gt;hlen;
<a name="L598" href="source/net/ipv4/ip_tunnel.c#L598">598</a>         else
<a name="L599" href="source/net/ipv4/ip_tunnel.c#L599">599</a>                 <a href="ident?i=mtu">mtu</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>) ? <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)) : <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>;
<a name="L600" href="source/net/ipv4/ip_tunnel.c#L600">600</a> 
<a name="L601" href="source/net/ipv4/ip_tunnel.c#L601">601</a>         if (<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>))
<a name="L602" href="source/net/ipv4/ip_tunnel.c#L602">602</a>                 <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ops">ops</a>-&gt;update_pmtu(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=mtu">mtu</a>);
<a name="L603" href="source/net/ipv4/ip_tunnel.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/ip_tunnel.c#L604">604</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L605" href="source/net/ipv4/ip_tunnel.c#L605">605</a>                 if (!<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>) &amp;&amp;
<a name="L606" href="source/net/ipv4/ip_tunnel.c#L606">606</a>                     (<a href="ident?i=df">df</a> &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>)) &amp;&amp; <a href="ident?i=mtu">mtu</a> &lt; pkt_size) {
<a name="L607" href="source/net/ipv4/ip_tunnel.c#L607">607</a>                         <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(*<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)));
<a name="L608" href="source/net/ipv4/ip_tunnel.c#L608">608</a>                         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=mtu">mtu</a>));
<a name="L609" href="source/net/ipv4/ip_tunnel.c#L609">609</a>                         return -<a href="ident?i=E2BIG">E2BIG</a>;
<a name="L610" href="source/net/ipv4/ip_tunnel.c#L610">610</a>                 }
<a name="L611" href="source/net/ipv4/ip_tunnel.c#L611">611</a>         }
<a name="L612" href="source/net/ipv4/ip_tunnel.c#L612">612</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L613" href="source/net/ipv4/ip_tunnel.c#L613">613</a>         else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>)) {
<a name="L614" href="source/net/ipv4/ip_tunnel.c#L614">614</a>                 struct <a href="ident?i=rt6_info">rt6_info</a> *rt6 = (struct <a href="ident?i=rt6_info">rt6_info</a> *)<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L615" href="source/net/ipv4/ip_tunnel.c#L615">615</a> 
<a name="L616" href="source/net/ipv4/ip_tunnel.c#L616">616</a>                 if (rt6 &amp;&amp; <a href="ident?i=mtu">mtu</a> &lt; <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)) &amp;&amp;
<a name="L617" href="source/net/ipv4/ip_tunnel.c#L617">617</a>                            <a href="ident?i=mtu">mtu</a> &gt;= <a href="ident?i=IPV6_MIN_MTU">IPV6_MIN_MTU</a>) {
<a name="L618" href="source/net/ipv4/ip_tunnel.c#L618">618</a>                         if ((tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> &amp;&amp;
<a name="L619" href="source/net/ipv4/ip_tunnel.c#L619">619</a>                             !<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>)) ||
<a name="L620" href="source/net/ipv4/ip_tunnel.c#L620">620</a>                             rt6-&gt;rt6i_dst.plen == 128) {
<a name="L621" href="source/net/ipv4/ip_tunnel.c#L621">621</a>                                 rt6-&gt;rt6i_flags |= <a href="ident?i=RTF_MODIFIED">RTF_MODIFIED</a>;
<a name="L622" href="source/net/ipv4/ip_tunnel.c#L622">622</a>                                 <a href="ident?i=dst_metric_set">dst_metric_set</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=RTAX_MTU">RTAX_MTU</a>, <a href="ident?i=mtu">mtu</a>);
<a name="L623" href="source/net/ipv4/ip_tunnel.c#L623">623</a>                         }
<a name="L624" href="source/net/ipv4/ip_tunnel.c#L624">624</a>                 }
<a name="L625" href="source/net/ipv4/ip_tunnel.c#L625">625</a> 
<a name="L626" href="source/net/ipv4/ip_tunnel.c#L626">626</a>                 if (!<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>) &amp;&amp; <a href="ident?i=mtu">mtu</a> &gt;= <a href="ident?i=IPV6_MIN_MTU">IPV6_MIN_MTU</a> &amp;&amp;
<a name="L627" href="source/net/ipv4/ip_tunnel.c#L627">627</a>                                         <a href="ident?i=mtu">mtu</a> &lt; pkt_size) {
<a name="L628" href="source/net/ipv4/ip_tunnel.c#L628">628</a>                         <a href="ident?i=icmpv6_send">icmpv6_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMPV6_PKT_TOOBIG">ICMPV6_PKT_TOOBIG</a>, 0, <a href="ident?i=mtu">mtu</a>);
<a name="L629" href="source/net/ipv4/ip_tunnel.c#L629">629</a>                         return -<a href="ident?i=E2BIG">E2BIG</a>;
<a name="L630" href="source/net/ipv4/ip_tunnel.c#L630">630</a>                 }
<a name="L631" href="source/net/ipv4/ip_tunnel.c#L631">631</a>         }
<a name="L632" href="source/net/ipv4/ip_tunnel.c#L632">632</a> #endif
<a name="L633" href="source/net/ipv4/ip_tunnel.c#L633">633</a>         return 0;
<a name="L634" href="source/net/ipv4/ip_tunnel.c#L634">634</a> }
<a name="L635" href="source/net/ipv4/ip_tunnel.c#L635">635</a> 
<a name="L636" href="source/net/ipv4/ip_tunnel.c#L636">636</a> void <a href="ident?i=ip_tunnel_xmit">ip_tunnel_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L637" href="source/net/ipv4/ip_tunnel.c#L637">637</a>                     const struct <a href="ident?i=iphdr">iphdr</a> *tnl_params, <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>)
<a name="L638" href="source/net/ipv4/ip_tunnel.c#L638">638</a> {
<a name="L639" href="source/net/ipv4/ip_tunnel.c#L639">639</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L640" href="source/net/ipv4/ip_tunnel.c#L640">640</a>         const struct <a href="ident?i=iphdr">iphdr</a> *inner_iph;
<a name="L641" href="source/net/ipv4/ip_tunnel.c#L641">641</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L642" href="source/net/ipv4/ip_tunnel.c#L642">642</a>         <a href="ident?i=u8">u8</a>     tos, <a href="ident?i=ttl">ttl</a>;
<a name="L643" href="source/net/ipv4/ip_tunnel.c#L643">643</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=df">df</a>;
<a name="L644" href="source/net/ipv4/ip_tunnel.c#L644">644</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;              <b><i>/* Route to the other host */</i></b>
<a name="L645" href="source/net/ipv4/ip_tunnel.c#L645">645</a>         unsigned int max_headroom;      <b><i>/* The extra header space needed */</i></b>
<a name="L646" href="source/net/ipv4/ip_tunnel.c#L646">646</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>;
<a name="L647" href="source/net/ipv4/ip_tunnel.c#L647">647</a>         int <a href="ident?i=err">err</a>;
<a name="L648" href="source/net/ipv4/ip_tunnel.c#L648">648</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=connected">connected</a>;
<a name="L649" href="source/net/ipv4/ip_tunnel.c#L649">649</a> 
<a name="L650" href="source/net/ipv4/ip_tunnel.c#L650">650</a>         inner_iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb_inner_network_header">skb_inner_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L651" href="source/net/ipv4/ip_tunnel.c#L651">651</a>         <a href="ident?i=connected">connected</a> = (tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> != 0);
<a name="L652" href="source/net/ipv4/ip_tunnel.c#L652">652</a> 
<a name="L653" href="source/net/ipv4/ip_tunnel.c#L653">653</a>         <a href="ident?i=dst">dst</a> = tnl_params-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L654" href="source/net/ipv4/ip_tunnel.c#L654">654</a>         if (<a href="ident?i=dst">dst</a> == 0) {
<a name="L655" href="source/net/ipv4/ip_tunnel.c#L655">655</a>                 <b><i>/* NBMA tunnel */</i></b>
<a name="L656" href="source/net/ipv4/ip_tunnel.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/ip_tunnel.c#L657">657</a>                 if (!<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L658" href="source/net/ipv4/ip_tunnel.c#L658">658</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_fifo_errors++;
<a name="L659" href="source/net/ipv4/ip_tunnel.c#L659">659</a>                         goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L660" href="source/net/ipv4/ip_tunnel.c#L660">660</a>                 }
<a name="L661" href="source/net/ipv4/ip_tunnel.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/ip_tunnel.c#L662">662</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L663" href="source/net/ipv4/ip_tunnel.c#L663">663</a>                         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L664" href="source/net/ipv4/ip_tunnel.c#L664">664</a>                         <a href="ident?i=dst">dst</a> = <a href="ident?i=rt_nexthop">rt_nexthop</a>(<a href="ident?i=rt">rt</a>, inner_iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L665" href="source/net/ipv4/ip_tunnel.c#L665">665</a>                 }
<a name="L666" href="source/net/ipv4/ip_tunnel.c#L666">666</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L667" href="source/net/ipv4/ip_tunnel.c#L667">667</a>                 else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>)) {
<a name="L668" href="source/net/ipv4/ip_tunnel.c#L668">668</a>                         const struct <a href="ident?i=in6_addr">in6_addr</a> *addr6;
<a name="L669" href="source/net/ipv4/ip_tunnel.c#L669">669</a>                         struct <a href="ident?i=neighbour">neighbour</a> *neigh;
<a name="L670" href="source/net/ipv4/ip_tunnel.c#L670">670</a>                         <a href="ident?i=bool">bool</a> do_tx_error_icmp;
<a name="L671" href="source/net/ipv4/ip_tunnel.c#L671">671</a>                         int addr_type;
<a name="L672" href="source/net/ipv4/ip_tunnel.c#L672">672</a> 
<a name="L673" href="source/net/ipv4/ip_tunnel.c#L673">673</a>                         neigh = <a href="ident?i=dst_neigh_lookup">dst_neigh_lookup</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>),
<a name="L674" href="source/net/ipv4/ip_tunnel.c#L674">674</a>                                                  &amp;<a href="ident?i=ipv6_hdr">ipv6_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L675" href="source/net/ipv4/ip_tunnel.c#L675">675</a>                         if (!neigh)
<a name="L676" href="source/net/ipv4/ip_tunnel.c#L676">676</a>                                 goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L677" href="source/net/ipv4/ip_tunnel.c#L677">677</a> 
<a name="L678" href="source/net/ipv4/ip_tunnel.c#L678">678</a>                         addr6 = (const struct <a href="ident?i=in6_addr">in6_addr</a> *)&amp;neigh-&gt;primary_key;
<a name="L679" href="source/net/ipv4/ip_tunnel.c#L679">679</a>                         addr_type = <a href="ident?i=ipv6_addr_type">ipv6_addr_type</a>(addr6);
<a name="L680" href="source/net/ipv4/ip_tunnel.c#L680">680</a> 
<a name="L681" href="source/net/ipv4/ip_tunnel.c#L681">681</a>                         if (addr_type == <a href="ident?i=IPV6_ADDR_ANY">IPV6_ADDR_ANY</a>) {
<a name="L682" href="source/net/ipv4/ip_tunnel.c#L682">682</a>                                 addr6 = &amp;<a href="ident?i=ipv6_hdr">ipv6_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L683" href="source/net/ipv4/ip_tunnel.c#L683">683</a>                                 addr_type = <a href="ident?i=ipv6_addr_type">ipv6_addr_type</a>(addr6);
<a name="L684" href="source/net/ipv4/ip_tunnel.c#L684">684</a>                         }
<a name="L685" href="source/net/ipv4/ip_tunnel.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/ip_tunnel.c#L686">686</a>                         if ((addr_type &amp; <a href="ident?i=IPV6_ADDR_COMPATv4">IPV6_ADDR_COMPATv4</a>) == 0)
<a name="L687" href="source/net/ipv4/ip_tunnel.c#L687">687</a>                                 do_tx_error_icmp = <a href="ident?i=true">true</a>;
<a name="L688" href="source/net/ipv4/ip_tunnel.c#L688">688</a>                         else {
<a name="L689" href="source/net/ipv4/ip_tunnel.c#L689">689</a>                                 do_tx_error_icmp = <a href="ident?i=false">false</a>;
<a name="L690" href="source/net/ipv4/ip_tunnel.c#L690">690</a>                                 <a href="ident?i=dst">dst</a> = addr6-&gt;<a href="ident?i=s6_addr32">s6_addr32</a>[3];
<a name="L691" href="source/net/ipv4/ip_tunnel.c#L691">691</a>                         }
<a name="L692" href="source/net/ipv4/ip_tunnel.c#L692">692</a>                         <a href="ident?i=neigh_release">neigh_release</a>(neigh);
<a name="L693" href="source/net/ipv4/ip_tunnel.c#L693">693</a>                         if (do_tx_error_icmp)
<a name="L694" href="source/net/ipv4/ip_tunnel.c#L694">694</a>                                 goto tx_error_icmp;
<a name="L695" href="source/net/ipv4/ip_tunnel.c#L695">695</a>                 }
<a name="L696" href="source/net/ipv4/ip_tunnel.c#L696">696</a> #endif
<a name="L697" href="source/net/ipv4/ip_tunnel.c#L697">697</a>                 else
<a name="L698" href="source/net/ipv4/ip_tunnel.c#L698">698</a>                         goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L699" href="source/net/ipv4/ip_tunnel.c#L699">699</a> 
<a name="L700" href="source/net/ipv4/ip_tunnel.c#L700">700</a>                 <a href="ident?i=connected">connected</a> = <a href="ident?i=false">false</a>;
<a name="L701" href="source/net/ipv4/ip_tunnel.c#L701">701</a>         }
<a name="L702" href="source/net/ipv4/ip_tunnel.c#L702">702</a> 
<a name="L703" href="source/net/ipv4/ip_tunnel.c#L703">703</a>         tos = tnl_params-&gt;tos;
<a name="L704" href="source/net/ipv4/ip_tunnel.c#L704">704</a>         if (tos &amp; 0x1) {
<a name="L705" href="source/net/ipv4/ip_tunnel.c#L705">705</a>                 tos &amp;= ~0x1;
<a name="L706" href="source/net/ipv4/ip_tunnel.c#L706">706</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L707" href="source/net/ipv4/ip_tunnel.c#L707">707</a>                         tos = inner_iph-&gt;tos;
<a name="L708" href="source/net/ipv4/ip_tunnel.c#L708">708</a>                         <a href="ident?i=connected">connected</a> = <a href="ident?i=false">false</a>;
<a name="L709" href="source/net/ipv4/ip_tunnel.c#L709">709</a>                 } else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>)) {
<a name="L710" href="source/net/ipv4/ip_tunnel.c#L710">710</a>                         tos = <a href="ident?i=ipv6_get_dsfield">ipv6_get_dsfield</a>((const struct <a href="ident?i=ipv6hdr">ipv6hdr</a> *)inner_iph);
<a name="L711" href="source/net/ipv4/ip_tunnel.c#L711">711</a>                         <a href="ident?i=connected">connected</a> = <a href="ident?i=false">false</a>;
<a name="L712" href="source/net/ipv4/ip_tunnel.c#L712">712</a>                 }
<a name="L713" href="source/net/ipv4/ip_tunnel.c#L713">713</a>         }
<a name="L714" href="source/net/ipv4/ip_tunnel.c#L714">714</a> 
<a name="L715" href="source/net/ipv4/ip_tunnel.c#L715">715</a>         <a href="ident?i=init_tunnel_flow">init_tunnel_flow</a>(&amp;fl4, <a href="ident?i=protocol">protocol</a>, <a href="ident?i=dst">dst</a>, tnl_params-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L716" href="source/net/ipv4/ip_tunnel.c#L716">716</a>                          tunnel-&gt;<a href="ident?i=parms">parms</a>.o_key, <a href="ident?i=RT_TOS">RT_TOS</a>(tos), tunnel-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>);
<a name="L717" href="source/net/ipv4/ip_tunnel.c#L717">717</a> 
<a name="L718" href="source/net/ipv4/ip_tunnel.c#L718">718</a>         if (<a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a>(<a href="ident?i=skb">skb</a>, tunnel, &amp;<a href="ident?i=protocol">protocol</a>, &amp;fl4) &lt; 0)
<a name="L719" href="source/net/ipv4/ip_tunnel.c#L719">719</a>                 goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L720" href="source/net/ipv4/ip_tunnel.c#L720">720</a> 
<a name="L721" href="source/net/ipv4/ip_tunnel.c#L721">721</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=connected">connected</a> ? <a href="ident?i=tunnel_rtable_get">tunnel_rtable_get</a>(tunnel, 0, &amp;fl4.<a href="ident?i=saddr">saddr</a>) : <a href="ident?i=NULL">NULL</a>;
<a name="L722" href="source/net/ipv4/ip_tunnel.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/ip_tunnel.c#L723">723</a>         if (!<a href="ident?i=rt">rt</a>) {
<a name="L724" href="source/net/ipv4/ip_tunnel.c#L724">724</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(tunnel-&gt;<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L725" href="source/net/ipv4/ip_tunnel.c#L725">725</a> 
<a name="L726" href="source/net/ipv4/ip_tunnel.c#L726">726</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L727" href="source/net/ipv4/ip_tunnel.c#L727">727</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_carrier_errors++;
<a name="L728" href="source/net/ipv4/ip_tunnel.c#L728">728</a>                         goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L729" href="source/net/ipv4/ip_tunnel.c#L729">729</a>                 }
<a name="L730" href="source/net/ipv4/ip_tunnel.c#L730">730</a>                 if (<a href="ident?i=connected">connected</a>)
<a name="L731" href="source/net/ipv4/ip_tunnel.c#L731">731</a>                         <a href="ident?i=tunnel_dst_set">tunnel_dst_set</a>(tunnel, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, fl4.<a href="ident?i=saddr">saddr</a>);
<a name="L732" href="source/net/ipv4/ip_tunnel.c#L732">732</a>         }
<a name="L733" href="source/net/ipv4/ip_tunnel.c#L733">733</a> 
<a name="L734" href="source/net/ipv4/ip_tunnel.c#L734">734</a>         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> == <a href="ident?i=dev">dev</a>) {
<a name="L735" href="source/net/ipv4/ip_tunnel.c#L735">735</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L736" href="source/net/ipv4/ip_tunnel.c#L736">736</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.collisions++;
<a name="L737" href="source/net/ipv4/ip_tunnel.c#L737">737</a>                 goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L738" href="source/net/ipv4/ip_tunnel.c#L738">738</a>         }
<a name="L739" href="source/net/ipv4/ip_tunnel.c#L739">739</a> 
<a name="L740" href="source/net/ipv4/ip_tunnel.c#L740">740</a>         if (<a href="ident?i=tnl_update_pmtu">tnl_update_pmtu</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=rt">rt</a>, tnl_params-&gt;frag_off)) {
<a name="L741" href="source/net/ipv4/ip_tunnel.c#L741">741</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L742" href="source/net/ipv4/ip_tunnel.c#L742">742</a>                 goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L743" href="source/net/ipv4/ip_tunnel.c#L743">743</a>         }
<a name="L744" href="source/net/ipv4/ip_tunnel.c#L744">744</a> 
<a name="L745" href="source/net/ipv4/ip_tunnel.c#L745">745</a>         if (tunnel-&gt;err_count &gt; 0) {
<a name="L746" href="source/net/ipv4/ip_tunnel.c#L746">746</a>                 if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>,
<a name="L747" href="source/net/ipv4/ip_tunnel.c#L747">747</a>                                 tunnel-&gt;err_time + <a href="ident?i=IPTUNNEL_ERR_TIMEO">IPTUNNEL_ERR_TIMEO</a>)) {
<a name="L748" href="source/net/ipv4/ip_tunnel.c#L748">748</a>                         tunnel-&gt;err_count--;
<a name="L749" href="source/net/ipv4/ip_tunnel.c#L749">749</a> 
<a name="L750" href="source/net/ipv4/ip_tunnel.c#L750">750</a>                         <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(*<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)));
<a name="L751" href="source/net/ipv4/ip_tunnel.c#L751">751</a>                         <a href="ident?i=dst_link_failure">dst_link_failure</a>(<a href="ident?i=skb">skb</a>);
<a name="L752" href="source/net/ipv4/ip_tunnel.c#L752">752</a>                 } else
<a name="L753" href="source/net/ipv4/ip_tunnel.c#L753">753</a>                         tunnel-&gt;err_count = 0;
<a name="L754" href="source/net/ipv4/ip_tunnel.c#L754">754</a>         }
<a name="L755" href="source/net/ipv4/ip_tunnel.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/ip_tunnel.c#L756">756</a>         tos = <a href="ident?i=ip_tunnel_ecn_encap">ip_tunnel_ecn_encap</a>(tos, inner_iph, <a href="ident?i=skb">skb</a>);
<a name="L757" href="source/net/ipv4/ip_tunnel.c#L757">757</a>         <a href="ident?i=ttl">ttl</a> = tnl_params-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L758" href="source/net/ipv4/ip_tunnel.c#L758">758</a>         if (<a href="ident?i=ttl">ttl</a> == 0) {
<a name="L759" href="source/net/ipv4/ip_tunnel.c#L759">759</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L760" href="source/net/ipv4/ip_tunnel.c#L760">760</a>                         <a href="ident?i=ttl">ttl</a> = inner_iph-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L761" href="source/net/ipv4/ip_tunnel.c#L761">761</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L762" href="source/net/ipv4/ip_tunnel.c#L762">762</a>                 else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>))
<a name="L763" href="source/net/ipv4/ip_tunnel.c#L763">763</a>                         <a href="ident?i=ttl">ttl</a> = ((const struct <a href="ident?i=ipv6hdr">ipv6hdr</a> *)inner_iph)-&gt;hop_limit;
<a name="L764" href="source/net/ipv4/ip_tunnel.c#L764">764</a> #endif
<a name="L765" href="source/net/ipv4/ip_tunnel.c#L765">765</a>                 else
<a name="L766" href="source/net/ipv4/ip_tunnel.c#L766">766</a>                         <a href="ident?i=ttl">ttl</a> = <a href="ident?i=ip4_dst_hoplimit">ip4_dst_hoplimit</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L767" href="source/net/ipv4/ip_tunnel.c#L767">767</a>         }
<a name="L768" href="source/net/ipv4/ip_tunnel.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/ip_tunnel.c#L769">769</a>         <a href="ident?i=df">df</a> = tnl_params-&gt;frag_off;
<a name="L770" href="source/net/ipv4/ip_tunnel.c#L770">770</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L771" href="source/net/ipv4/ip_tunnel.c#L771">771</a>                 <a href="ident?i=df">df</a> |= (inner_iph-&gt;frag_off&amp;<a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>));
<a name="L772" href="source/net/ipv4/ip_tunnel.c#L772">772</a> 
<a name="L773" href="source/net/ipv4/ip_tunnel.c#L773">773</a>         max_headroom = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>) + sizeof(struct <a href="ident?i=iphdr">iphdr</a>)
<a name="L774" href="source/net/ipv4/ip_tunnel.c#L774">774</a>                         + <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=header_len">header_len</a> + <a href="ident?i=ip_encap_hlen">ip_encap_hlen</a>(&amp;tunnel-&gt;encap);
<a name="L775" href="source/net/ipv4/ip_tunnel.c#L775">775</a>         if (max_headroom &gt; <a href="ident?i=dev">dev</a>-&gt;needed_headroom)
<a name="L776" href="source/net/ipv4/ip_tunnel.c#L776">776</a>                 <a href="ident?i=dev">dev</a>-&gt;needed_headroom = max_headroom;
<a name="L777" href="source/net/ipv4/ip_tunnel.c#L777">777</a> 
<a name="L778" href="source/net/ipv4/ip_tunnel.c#L778">778</a>         if (<a href="ident?i=skb_cow_head">skb_cow_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>-&gt;needed_headroom)) {
<a name="L779" href="source/net/ipv4/ip_tunnel.c#L779">779</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L780" href="source/net/ipv4/ip_tunnel.c#L780">780</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_dropped++;
<a name="L781" href="source/net/ipv4/ip_tunnel.c#L781">781</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L782" href="source/net/ipv4/ip_tunnel.c#L782">782</a>                 return;
<a name="L783" href="source/net/ipv4/ip_tunnel.c#L783">783</a>         }
<a name="L784" href="source/net/ipv4/ip_tunnel.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/ip_tunnel.c#L785">785</a>         <a href="ident?i=err">err</a> = <a href="ident?i=iptunnel_xmit">iptunnel_xmit</a>(<a href="ident?i=NULL">NULL</a>, <a href="ident?i=rt">rt</a>, <a href="ident?i=skb">skb</a>, fl4.<a href="ident?i=saddr">saddr</a>, fl4.<a href="ident?i=daddr">daddr</a>, <a href="ident?i=protocol">protocol</a>,
<a name="L786" href="source/net/ipv4/ip_tunnel.c#L786">786</a>                             tos, <a href="ident?i=ttl">ttl</a>, <a href="ident?i=df">df</a>, !<a href="ident?i=net_eq">net_eq</a>(tunnel-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>)));
<a name="L787" href="source/net/ipv4/ip_tunnel.c#L787">787</a>         <a href="ident?i=iptunnel_xmit_stats">iptunnel_xmit_stats</a>(<a href="ident?i=err">err</a>, &amp;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>, <a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L788" href="source/net/ipv4/ip_tunnel.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/ip_tunnel.c#L789">789</a>         return;
<a name="L790" href="source/net/ipv4/ip_tunnel.c#L790">790</a> 
<a name="L791" href="source/net/ipv4/ip_tunnel.c#L791">791</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L792" href="source/net/ipv4/ip_tunnel.c#L792">792</a> tx_error_icmp:
<a name="L793" href="source/net/ipv4/ip_tunnel.c#L793">793</a>         <a href="ident?i=dst_link_failure">dst_link_failure</a>(<a href="ident?i=skb">skb</a>);
<a name="L794" href="source/net/ipv4/ip_tunnel.c#L794">794</a> #endif
<a name="L795" href="source/net/ipv4/ip_tunnel.c#L795">795</a> <a href="ident?i=tx_error">tx_error</a>:
<a name="L796" href="source/net/ipv4/ip_tunnel.c#L796">796</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_errors++;
<a name="L797" href="source/net/ipv4/ip_tunnel.c#L797">797</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L798" href="source/net/ipv4/ip_tunnel.c#L798">798</a> }
<a name="L799" href="source/net/ipv4/ip_tunnel.c#L799">799</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_xmit">ip_tunnel_xmit</a>);
<a name="L800" href="source/net/ipv4/ip_tunnel.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/ip_tunnel.c#L801">801</a> static void <a href="ident?i=ip_tunnel_update">ip_tunnel_update</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn,
<a name="L802" href="source/net/ipv4/ip_tunnel.c#L802">802</a>                              struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>,
<a name="L803" href="source/net/ipv4/ip_tunnel.c#L803">803</a>                              struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L804" href="source/net/ipv4/ip_tunnel.c#L804">804</a>                              struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a>,
<a name="L805" href="source/net/ipv4/ip_tunnel.c#L805">805</a>                              <a href="ident?i=bool">bool</a> set_mtu)
<a name="L806" href="source/net/ipv4/ip_tunnel.c#L806">806</a> {
<a name="L807" href="source/net/ipv4/ip_tunnel.c#L807">807</a>         <a href="ident?i=ip_tunnel_del">ip_tunnel_del</a>(<a href="ident?i=t">t</a>);
<a name="L808" href="source/net/ipv4/ip_tunnel.c#L808">808</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>;
<a name="L809" href="source/net/ipv4/ip_tunnel.c#L809">809</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>;
<a name="L810" href="source/net/ipv4/ip_tunnel.c#L810">810</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.i_key = <a href="ident?i=p">p</a>-&gt;i_key;
<a name="L811" href="source/net/ipv4/ip_tunnel.c#L811">811</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.o_key = <a href="ident?i=p">p</a>-&gt;o_key;
<a name="L812" href="source/net/ipv4/ip_tunnel.c#L812">812</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>) {
<a name="L813" href="source/net/ipv4/ip_tunnel.c#L813">813</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;dev_addr, &amp;<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>, 4);
<a name="L814" href="source/net/ipv4/ip_tunnel.c#L814">814</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, &amp;<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>, 4);
<a name="L815" href="source/net/ipv4/ip_tunnel.c#L815">815</a>         }
<a name="L816" href="source/net/ipv4/ip_tunnel.c#L816">816</a>         <a href="ident?i=ip_tunnel_add">ip_tunnel_add</a>(itn, <a href="ident?i=t">t</a>);
<a name="L817" href="source/net/ipv4/ip_tunnel.c#L817">817</a> 
<a name="L818" href="source/net/ipv4/ip_tunnel.c#L818">818</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=ttl">ttl</a> = <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=ttl">ttl</a>;
<a name="L819" href="source/net/ipv4/ip_tunnel.c#L819">819</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.tos = <a href="ident?i=p">p</a>-&gt;iph.tos;
<a name="L820" href="source/net/ipv4/ip_tunnel.c#L820">820</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.frag_off = <a href="ident?i=p">p</a>-&gt;iph.frag_off;
<a name="L821" href="source/net/ipv4/ip_tunnel.c#L821">821</a> 
<a name="L822" href="source/net/ipv4/ip_tunnel.c#L822">822</a>         if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> != <a href="ident?i=p">p</a>-&gt;<a href="ident?i=link">link</a>) {
<a name="L823" href="source/net/ipv4/ip_tunnel.c#L823">823</a>                 int <a href="ident?i=mtu">mtu</a>;
<a name="L824" href="source/net/ipv4/ip_tunnel.c#L824">824</a> 
<a name="L825" href="source/net/ipv4/ip_tunnel.c#L825">825</a>                 <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a> = <a href="ident?i=p">p</a>-&gt;<a href="ident?i=link">link</a>;
<a name="L826" href="source/net/ipv4/ip_tunnel.c#L826">826</a>                 <a href="ident?i=mtu">mtu</a> = <a href="ident?i=ip_tunnel_bind_dev">ip_tunnel_bind_dev</a>(<a href="ident?i=dev">dev</a>);
<a name="L827" href="source/net/ipv4/ip_tunnel.c#L827">827</a>                 if (set_mtu)
<a name="L828" href="source/net/ipv4/ip_tunnel.c#L828">828</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a> = <a href="ident?i=mtu">mtu</a>;
<a name="L829" href="source/net/ipv4/ip_tunnel.c#L829">829</a>         }
<a name="L830" href="source/net/ipv4/ip_tunnel.c#L830">830</a>         <a href="ident?i=ip_tunnel_dst_reset_all">ip_tunnel_dst_reset_all</a>(<a href="ident?i=t">t</a>);
<a name="L831" href="source/net/ipv4/ip_tunnel.c#L831">831</a>         <a href="ident?i=netdev_state_change">netdev_state_change</a>(<a href="ident?i=dev">dev</a>);
<a name="L832" href="source/net/ipv4/ip_tunnel.c#L832">832</a> }
<a name="L833" href="source/net/ipv4/ip_tunnel.c#L833">833</a> 
<a name="L834" href="source/net/ipv4/ip_tunnel.c#L834">834</a> int <a href="ident?i=ip_tunnel_ioctl">ip_tunnel_ioctl</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a>, int <a href="ident?i=cmd">cmd</a>)
<a name="L835" href="source/net/ipv4/ip_tunnel.c#L835">835</a> {
<a name="L836" href="source/net/ipv4/ip_tunnel.c#L836">836</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L837" href="source/net/ipv4/ip_tunnel.c#L837">837</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L838" href="source/net/ipv4/ip_tunnel.c#L838">838</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=net">net</a>;
<a name="L839" href="source/net/ipv4/ip_tunnel.c#L839">839</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=t">t</a>-&gt;ip_tnl_net_id);
<a name="L840" href="source/net/ipv4/ip_tunnel.c#L840">840</a> 
<a name="L841" href="source/net/ipv4/ip_tunnel.c#L841">841</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!itn-&gt;fb_tunnel_dev);
<a name="L842" href="source/net/ipv4/ip_tunnel.c#L842">842</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L843" href="source/net/ipv4/ip_tunnel.c#L843">843</a>         case <a href="ident?i=SIOCGETTUNNEL">SIOCGETTUNNEL</a>:
<a name="L844" href="source/net/ipv4/ip_tunnel.c#L844">844</a>                 if (<a href="ident?i=dev">dev</a> == itn-&gt;fb_tunnel_dev) {
<a name="L845" href="source/net/ipv4/ip_tunnel.c#L845">845</a>                         <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_find">ip_tunnel_find</a>(itn, <a href="ident?i=p">p</a>, itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=type">type</a>);
<a name="L846" href="source/net/ipv4/ip_tunnel.c#L846">846</a>                         if (!<a href="ident?i=t">t</a>)
<a name="L847" href="source/net/ipv4/ip_tunnel.c#L847">847</a>                                 <a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L848" href="source/net/ipv4/ip_tunnel.c#L848">848</a>                 }
<a name="L849" href="source/net/ipv4/ip_tunnel.c#L849">849</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=p">p</a>, &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>, sizeof(*<a href="ident?i=p">p</a>));
<a name="L850" href="source/net/ipv4/ip_tunnel.c#L850">850</a>                 break;
<a name="L851" href="source/net/ipv4/ip_tunnel.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/ip_tunnel.c#L852">852</a>         case <a href="ident?i=SIOCADDTUNNEL">SIOCADDTUNNEL</a>:
<a name="L853" href="source/net/ipv4/ip_tunnel.c#L853">853</a>         case <a href="ident?i=SIOCCHGTUNNEL">SIOCCHGTUNNEL</a>:
<a name="L854" href="source/net/ipv4/ip_tunnel.c#L854">854</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L855" href="source/net/ipv4/ip_tunnel.c#L855">855</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L856" href="source/net/ipv4/ip_tunnel.c#L856">856</a>                         goto <a href="ident?i=done">done</a>;
<a name="L857" href="source/net/ipv4/ip_tunnel.c#L857">857</a>                 if (<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=ttl">ttl</a>)
<a name="L858" href="source/net/ipv4/ip_tunnel.c#L858">858</a>                         <a href="ident?i=p">p</a>-&gt;iph.frag_off |= <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L859" href="source/net/ipv4/ip_tunnel.c#L859">859</a>                 if (!(<a href="ident?i=p">p</a>-&gt;i_flags &amp; <a href="ident?i=VTI_ISVTI">VTI_ISVTI</a>)) {
<a name="L860" href="source/net/ipv4/ip_tunnel.c#L860">860</a>                         if (!(<a href="ident?i=p">p</a>-&gt;i_flags &amp; <a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>))
<a name="L861" href="source/net/ipv4/ip_tunnel.c#L861">861</a>                                 <a href="ident?i=p">p</a>-&gt;i_key = 0;
<a name="L862" href="source/net/ipv4/ip_tunnel.c#L862">862</a>                         if (!(<a href="ident?i=p">p</a>-&gt;o_flags &amp; <a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>))
<a name="L863" href="source/net/ipv4/ip_tunnel.c#L863">863</a>                                 <a href="ident?i=p">p</a>-&gt;o_key = 0;
<a name="L864" href="source/net/ipv4/ip_tunnel.c#L864">864</a>                 }
<a name="L865" href="source/net/ipv4/ip_tunnel.c#L865">865</a> 
<a name="L866" href="source/net/ipv4/ip_tunnel.c#L866">866</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_find">ip_tunnel_find</a>(itn, <a href="ident?i=p">p</a>, itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=type">type</a>);
<a name="L867" href="source/net/ipv4/ip_tunnel.c#L867">867</a> 
<a name="L868" href="source/net/ipv4/ip_tunnel.c#L868">868</a>                 if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCADDTUNNEL">SIOCADDTUNNEL</a>) {
<a name="L869" href="source/net/ipv4/ip_tunnel.c#L869">869</a>                         if (!<a href="ident?i=t">t</a>) {
<a name="L870" href="source/net/ipv4/ip_tunnel.c#L870">870</a>                                 <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_create">ip_tunnel_create</a>(<a href="ident?i=net">net</a>, itn, <a href="ident?i=p">p</a>);
<a name="L871" href="source/net/ipv4/ip_tunnel.c#L871">871</a>                                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(<a href="ident?i=t">t</a>);
<a name="L872" href="source/net/ipv4/ip_tunnel.c#L872">872</a>                                 break;
<a name="L873" href="source/net/ipv4/ip_tunnel.c#L873">873</a>                         }
<a name="L874" href="source/net/ipv4/ip_tunnel.c#L874">874</a> 
<a name="L875" href="source/net/ipv4/ip_tunnel.c#L875">875</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L876" href="source/net/ipv4/ip_tunnel.c#L876">876</a>                         break;
<a name="L877" href="source/net/ipv4/ip_tunnel.c#L877">877</a>                 }
<a name="L878" href="source/net/ipv4/ip_tunnel.c#L878">878</a>                 if (<a href="ident?i=dev">dev</a> != itn-&gt;fb_tunnel_dev &amp;&amp; <a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCCHGTUNNEL">SIOCCHGTUNNEL</a>) {
<a name="L879" href="source/net/ipv4/ip_tunnel.c#L879">879</a>                         if (<a href="ident?i=t">t</a>) {
<a name="L880" href="source/net/ipv4/ip_tunnel.c#L880">880</a>                                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>) {
<a name="L881" href="source/net/ipv4/ip_tunnel.c#L881">881</a>                                         <a href="ident?i=err">err</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L882" href="source/net/ipv4/ip_tunnel.c#L882">882</a>                                         break;
<a name="L883" href="source/net/ipv4/ip_tunnel.c#L883">883</a>                                 }
<a name="L884" href="source/net/ipv4/ip_tunnel.c#L884">884</a>                         } else {
<a name="L885" href="source/net/ipv4/ip_tunnel.c#L885">885</a>                                 unsigned int nflags = 0;
<a name="L886" href="source/net/ipv4/ip_tunnel.c#L886">886</a> 
<a name="L887" href="source/net/ipv4/ip_tunnel.c#L887">887</a>                                 if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>))
<a name="L888" href="source/net/ipv4/ip_tunnel.c#L888">888</a>                                         nflags = <a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>;
<a name="L889" href="source/net/ipv4/ip_tunnel.c#L889">889</a>                                 else if (<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>)
<a name="L890" href="source/net/ipv4/ip_tunnel.c#L890">890</a>                                         nflags = <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>;
<a name="L891" href="source/net/ipv4/ip_tunnel.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/ip_tunnel.c#L892">892</a>                                 if ((<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>^nflags)&amp;(<a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>|<a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>)) {
<a name="L893" href="source/net/ipv4/ip_tunnel.c#L893">893</a>                                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L894" href="source/net/ipv4/ip_tunnel.c#L894">894</a>                                         break;
<a name="L895" href="source/net/ipv4/ip_tunnel.c#L895">895</a>                                 }
<a name="L896" href="source/net/ipv4/ip_tunnel.c#L896">896</a> 
<a name="L897" href="source/net/ipv4/ip_tunnel.c#L897">897</a>                                 <a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L898" href="source/net/ipv4/ip_tunnel.c#L898">898</a>                         }
<a name="L899" href="source/net/ipv4/ip_tunnel.c#L899">899</a>                 }
<a name="L900" href="source/net/ipv4/ip_tunnel.c#L900">900</a> 
<a name="L901" href="source/net/ipv4/ip_tunnel.c#L901">901</a>                 if (<a href="ident?i=t">t</a>) {
<a name="L902" href="source/net/ipv4/ip_tunnel.c#L902">902</a>                         <a href="ident?i=err">err</a> = 0;
<a name="L903" href="source/net/ipv4/ip_tunnel.c#L903">903</a>                         <a href="ident?i=ip_tunnel_update">ip_tunnel_update</a>(itn, <a href="ident?i=t">t</a>, <a href="ident?i=dev">dev</a>, <a href="ident?i=p">p</a>, <a href="ident?i=true">true</a>);
<a name="L904" href="source/net/ipv4/ip_tunnel.c#L904">904</a>                 } else {
<a name="L905" href="source/net/ipv4/ip_tunnel.c#L905">905</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L906" href="source/net/ipv4/ip_tunnel.c#L906">906</a>                 }
<a name="L907" href="source/net/ipv4/ip_tunnel.c#L907">907</a>                 break;
<a name="L908" href="source/net/ipv4/ip_tunnel.c#L908">908</a> 
<a name="L909" href="source/net/ipv4/ip_tunnel.c#L909">909</a>         case <a href="ident?i=SIOCDELTUNNEL">SIOCDELTUNNEL</a>:
<a name="L910" href="source/net/ipv4/ip_tunnel.c#L910">910</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L911" href="source/net/ipv4/ip_tunnel.c#L911">911</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L912" href="source/net/ipv4/ip_tunnel.c#L912">912</a>                         goto <a href="ident?i=done">done</a>;
<a name="L913" href="source/net/ipv4/ip_tunnel.c#L913">913</a> 
<a name="L914" href="source/net/ipv4/ip_tunnel.c#L914">914</a>                 if (<a href="ident?i=dev">dev</a> == itn-&gt;fb_tunnel_dev) {
<a name="L915" href="source/net/ipv4/ip_tunnel.c#L915">915</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L916" href="source/net/ipv4/ip_tunnel.c#L916">916</a>                         <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_find">ip_tunnel_find</a>(itn, <a href="ident?i=p">p</a>, itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=type">type</a>);
<a name="L917" href="source/net/ipv4/ip_tunnel.c#L917">917</a>                         if (!<a href="ident?i=t">t</a>)
<a name="L918" href="source/net/ipv4/ip_tunnel.c#L918">918</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L919" href="source/net/ipv4/ip_tunnel.c#L919">919</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L920" href="source/net/ipv4/ip_tunnel.c#L920">920</a>                         if (<a href="ident?i=t">t</a> == <a href="ident?i=netdev_priv">netdev_priv</a>(itn-&gt;fb_tunnel_dev))
<a name="L921" href="source/net/ipv4/ip_tunnel.c#L921">921</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L922" href="source/net/ipv4/ip_tunnel.c#L922">922</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L923" href="source/net/ipv4/ip_tunnel.c#L923">923</a>                 }
<a name="L924" href="source/net/ipv4/ip_tunnel.c#L924">924</a>                 <a href="ident?i=unregister_netdevice">unregister_netdevice</a>(<a href="ident?i=dev">dev</a>);
<a name="L925" href="source/net/ipv4/ip_tunnel.c#L925">925</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L926" href="source/net/ipv4/ip_tunnel.c#L926">926</a>                 break;
<a name="L927" href="source/net/ipv4/ip_tunnel.c#L927">927</a> 
<a name="L928" href="source/net/ipv4/ip_tunnel.c#L928">928</a>         default:
<a name="L929" href="source/net/ipv4/ip_tunnel.c#L929">929</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L930" href="source/net/ipv4/ip_tunnel.c#L930">930</a>         }
<a name="L931" href="source/net/ipv4/ip_tunnel.c#L931">931</a> 
<a name="L932" href="source/net/ipv4/ip_tunnel.c#L932">932</a> <a href="ident?i=done">done</a>:
<a name="L933" href="source/net/ipv4/ip_tunnel.c#L933">933</a>         return <a href="ident?i=err">err</a>;
<a name="L934" href="source/net/ipv4/ip_tunnel.c#L934">934</a> }
<a name="L935" href="source/net/ipv4/ip_tunnel.c#L935">935</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_ioctl">ip_tunnel_ioctl</a>);
<a name="L936" href="source/net/ipv4/ip_tunnel.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/ip_tunnel.c#L937">937</a> int <a href="ident?i=ip_tunnel_change_mtu">ip_tunnel_change_mtu</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int new_mtu)
<a name="L938" href="source/net/ipv4/ip_tunnel.c#L938">938</a> {
<a name="L939" href="source/net/ipv4/ip_tunnel.c#L939">939</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L940" href="source/net/ipv4/ip_tunnel.c#L940">940</a>         int t_hlen = tunnel-&gt;hlen + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L941" href="source/net/ipv4/ip_tunnel.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/ip_tunnel.c#L942">942</a>         if (new_mtu &lt; 68 ||
<a name="L943" href="source/net/ipv4/ip_tunnel.c#L943">943</a>             new_mtu &gt; 0xFFF8 - <a href="ident?i=dev">dev</a>-&gt;hard_header_len - t_hlen)
<a name="L944" href="source/net/ipv4/ip_tunnel.c#L944">944</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L945" href="source/net/ipv4/ip_tunnel.c#L945">945</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a> = new_mtu;
<a name="L946" href="source/net/ipv4/ip_tunnel.c#L946">946</a>         return 0;
<a name="L947" href="source/net/ipv4/ip_tunnel.c#L947">947</a> }
<a name="L948" href="source/net/ipv4/ip_tunnel.c#L948">948</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_change_mtu">ip_tunnel_change_mtu</a>);
<a name="L949" href="source/net/ipv4/ip_tunnel.c#L949">949</a> 
<a name="L950" href="source/net/ipv4/ip_tunnel.c#L950">950</a> static void <a href="ident?i=ip_tunnel_dev_free">ip_tunnel_dev_free</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L951" href="source/net/ipv4/ip_tunnel.c#L951">951</a> {
<a name="L952" href="source/net/ipv4/ip_tunnel.c#L952">952</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L953" href="source/net/ipv4/ip_tunnel.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/ip_tunnel.c#L954">954</a>         <a href="ident?i=gro_cells_destroy">gro_cells_destroy</a>(&amp;tunnel-&gt;<a href="ident?i=gro_cells">gro_cells</a>);
<a name="L955" href="source/net/ipv4/ip_tunnel.c#L955">955</a>         <a href="ident?i=free_percpu">free_percpu</a>(tunnel-&gt;dst_cache);
<a name="L956" href="source/net/ipv4/ip_tunnel.c#L956">956</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L957" href="source/net/ipv4/ip_tunnel.c#L957">957</a>         <a href="ident?i=free_netdev">free_netdev</a>(<a href="ident?i=dev">dev</a>);
<a name="L958" href="source/net/ipv4/ip_tunnel.c#L958">958</a> }
<a name="L959" href="source/net/ipv4/ip_tunnel.c#L959">959</a> 
<a name="L960" href="source/net/ipv4/ip_tunnel.c#L960">960</a> void <a href="ident?i=ip_tunnel_dellink">ip_tunnel_dellink</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=list_head">list_head</a> *<a href="ident?i=head">head</a>)
<a name="L961" href="source/net/ipv4/ip_tunnel.c#L961">961</a> {
<a name="L962" href="source/net/ipv4/ip_tunnel.c#L962">962</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L963" href="source/net/ipv4/ip_tunnel.c#L963">963</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn;
<a name="L964" href="source/net/ipv4/ip_tunnel.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/ip_tunnel.c#L965">965</a>         itn = <a href="ident?i=net_generic">net_generic</a>(tunnel-&gt;<a href="ident?i=net">net</a>, tunnel-&gt;ip_tnl_net_id);
<a name="L966" href="source/net/ipv4/ip_tunnel.c#L966">966</a> 
<a name="L967" href="source/net/ipv4/ip_tunnel.c#L967">967</a>         if (itn-&gt;fb_tunnel_dev != <a href="ident?i=dev">dev</a>) {
<a name="L968" href="source/net/ipv4/ip_tunnel.c#L968">968</a>                 <a href="ident?i=ip_tunnel_del">ip_tunnel_del</a>(<a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>));
<a name="L969" href="source/net/ipv4/ip_tunnel.c#L969">969</a>                 <a href="ident?i=unregister_netdevice_queue">unregister_netdevice_queue</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=head">head</a>);
<a name="L970" href="source/net/ipv4/ip_tunnel.c#L970">970</a>         }
<a name="L971" href="source/net/ipv4/ip_tunnel.c#L971">971</a> }
<a name="L972" href="source/net/ipv4/ip_tunnel.c#L972">972</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_dellink">ip_tunnel_dellink</a>);
<a name="L973" href="source/net/ipv4/ip_tunnel.c#L973">973</a> 
<a name="L974" href="source/net/ipv4/ip_tunnel.c#L974">974</a> struct <a href="ident?i=net">net</a> *<a href="ident?i=ip_tunnel_get_link_net">ip_tunnel_get_link_net</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L975" href="source/net/ipv4/ip_tunnel.c#L975">975</a> {
<a name="L976" href="source/net/ipv4/ip_tunnel.c#L976">976</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L977" href="source/net/ipv4/ip_tunnel.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/ip_tunnel.c#L978">978</a>         return tunnel-&gt;<a href="ident?i=net">net</a>;
<a name="L979" href="source/net/ipv4/ip_tunnel.c#L979">979</a> }
<a name="L980" href="source/net/ipv4/ip_tunnel.c#L980">980</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tunnel_get_link_net">ip_tunnel_get_link_net</a>);
<a name="L981" href="source/net/ipv4/ip_tunnel.c#L981">981</a> 
<a name="L982" href="source/net/ipv4/ip_tunnel.c#L982">982</a> int <a href="ident?i=ip_tunnel_get_iflink">ip_tunnel_get_iflink</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L983" href="source/net/ipv4/ip_tunnel.c#L983">983</a> {
<a name="L984" href="source/net/ipv4/ip_tunnel.c#L984">984</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L985" href="source/net/ipv4/ip_tunnel.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/ip_tunnel.c#L986">986</a>         return tunnel-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>;
<a name="L987" href="source/net/ipv4/ip_tunnel.c#L987">987</a> }
<a name="L988" href="source/net/ipv4/ip_tunnel.c#L988">988</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tunnel_get_iflink">ip_tunnel_get_iflink</a>);
<a name="L989" href="source/net/ipv4/ip_tunnel.c#L989">989</a> 
<a name="L990" href="source/net/ipv4/ip_tunnel.c#L990">990</a> int <a href="ident?i=ip_tunnel_init_net">ip_tunnel_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int ip_tnl_net_id,
<a name="L991" href="source/net/ipv4/ip_tunnel.c#L991">991</a>                                   struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> *<a href="ident?i=ops">ops</a>, char *<a href="ident?i=devname">devname</a>)
<a name="L992" href="source/net/ipv4/ip_tunnel.c#L992">992</a> {
<a name="L993" href="source/net/ipv4/ip_tunnel.c#L993">993</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ip_tnl_net_id);
<a name="L994" href="source/net/ipv4/ip_tunnel.c#L994">994</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=parms">parms</a>;
<a name="L995" href="source/net/ipv4/ip_tunnel.c#L995">995</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L996" href="source/net/ipv4/ip_tunnel.c#L996">996</a> 
<a name="L997" href="source/net/ipv4/ip_tunnel.c#L997">997</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=IP_TNL_HASH_SIZE">IP_TNL_HASH_SIZE</a>; <a href="ident?i=i">i</a>++)
<a name="L998" href="source/net/ipv4/ip_tunnel.c#L998">998</a>                 <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;itn-&gt;<a href="ident?i=tunnels">tunnels</a>[<a href="ident?i=i">i</a>]);
<a name="L999" href="source/net/ipv4/ip_tunnel.c#L999">999</a> 
<a name="L1000" href="source/net/ipv4/ip_tunnel.c#L1000">1000</a>         if (!<a href="ident?i=ops">ops</a>) {
<a name="L1001" href="source/net/ipv4/ip_tunnel.c#L1001">1001</a>                 itn-&gt;fb_tunnel_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L1002" href="source/net/ipv4/ip_tunnel.c#L1002">1002</a>                 return 0;
<a name="L1003" href="source/net/ipv4/ip_tunnel.c#L1003">1003</a>         }
<a name="L1004" href="source/net/ipv4/ip_tunnel.c#L1004">1004</a> 
<a name="L1005" href="source/net/ipv4/ip_tunnel.c#L1005">1005</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=parms">parms</a>, 0, sizeof(<a href="ident?i=parms">parms</a>));
<a name="L1006" href="source/net/ipv4/ip_tunnel.c#L1006">1006</a>         if (<a href="ident?i=devname">devname</a>)
<a name="L1007" href="source/net/ipv4/ip_tunnel.c#L1007">1007</a>                 <a href="ident?i=strlcpy">strlcpy</a>(<a href="ident?i=parms">parms</a>.<a href="ident?i=name">name</a>, <a href="ident?i=devname">devname</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L1008" href="source/net/ipv4/ip_tunnel.c#L1008">1008</a> 
<a name="L1009" href="source/net/ipv4/ip_tunnel.c#L1009">1009</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1010" href="source/net/ipv4/ip_tunnel.c#L1010">1010</a>         itn-&gt;fb_tunnel_dev = <a href="ident?i=__ip_tunnel_create">__ip_tunnel_create</a>(<a href="ident?i=net">net</a>, <a href="ident?i=ops">ops</a>, &amp;<a href="ident?i=parms">parms</a>);
<a name="L1011" href="source/net/ipv4/ip_tunnel.c#L1011">1011</a>         <b><i>/* FB netdevice is special: we have one, and only one per netns.</i></b>
<a name="L1012" href="source/net/ipv4/ip_tunnel.c#L1012">1012</a> <b><i>         * Allowing to move it to another netns is clearly unsafe.</i></b>
<a name="L1013" href="source/net/ipv4/ip_tunnel.c#L1013">1013</a> <b><i>         */</i></b>
<a name="L1014" href="source/net/ipv4/ip_tunnel.c#L1014">1014</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(itn-&gt;fb_tunnel_dev)) {
<a name="L1015" href="source/net/ipv4/ip_tunnel.c#L1015">1015</a>                 itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=features">features</a> |= <a href="ident?i=NETIF_F_NETNS_LOCAL">NETIF_F_NETNS_LOCAL</a>;
<a name="L1016" href="source/net/ipv4/ip_tunnel.c#L1016">1016</a>                 itn-&gt;fb_tunnel_dev-&gt;<a href="ident?i=mtu">mtu</a> = <a href="ident?i=ip_tunnel_bind_dev">ip_tunnel_bind_dev</a>(itn-&gt;fb_tunnel_dev);
<a name="L1017" href="source/net/ipv4/ip_tunnel.c#L1017">1017</a>                 <a href="ident?i=ip_tunnel_add">ip_tunnel_add</a>(itn, <a href="ident?i=netdev_priv">netdev_priv</a>(itn-&gt;fb_tunnel_dev));
<a name="L1018" href="source/net/ipv4/ip_tunnel.c#L1018">1018</a>         }
<a name="L1019" href="source/net/ipv4/ip_tunnel.c#L1019">1019</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1020" href="source/net/ipv4/ip_tunnel.c#L1020">1020</a> 
<a name="L1021" href="source/net/ipv4/ip_tunnel.c#L1021">1021</a>         return <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(itn-&gt;fb_tunnel_dev);
<a name="L1022" href="source/net/ipv4/ip_tunnel.c#L1022">1022</a> }
<a name="L1023" href="source/net/ipv4/ip_tunnel.c#L1023">1023</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_init_net">ip_tunnel_init_net</a>);
<a name="L1024" href="source/net/ipv4/ip_tunnel.c#L1024">1024</a> 
<a name="L1025" href="source/net/ipv4/ip_tunnel.c#L1025">1025</a> static void <a href="ident?i=ip_tunnel_destroy">ip_tunnel_destroy</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn, struct <a href="ident?i=list_head">list_head</a> *<a href="ident?i=head">head</a>,
<a name="L1026" href="source/net/ipv4/ip_tunnel.c#L1026">1026</a>                               struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> *<a href="ident?i=ops">ops</a>)
<a name="L1027" href="source/net/ipv4/ip_tunnel.c#L1027">1027</a> {
<a name="L1028" href="source/net/ipv4/ip_tunnel.c#L1028">1028</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(itn-&gt;fb_tunnel_dev);
<a name="L1029" href="source/net/ipv4/ip_tunnel.c#L1029">1029</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, *aux;
<a name="L1030" href="source/net/ipv4/ip_tunnel.c#L1030">1030</a>         int <a href="ident?i=h">h</a>;
<a name="L1031" href="source/net/ipv4/ip_tunnel.c#L1031">1031</a> 
<a name="L1032" href="source/net/ipv4/ip_tunnel.c#L1032">1032</a>         <a href="ident?i=for_each_netdev_safe">for_each_netdev_safe</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>, aux)
<a name="L1033" href="source/net/ipv4/ip_tunnel.c#L1033">1033</a>                 if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> == <a href="ident?i=ops">ops</a>)
<a name="L1034" href="source/net/ipv4/ip_tunnel.c#L1034">1034</a>                         <a href="ident?i=unregister_netdevice_queue">unregister_netdevice_queue</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=head">head</a>);
<a name="L1035" href="source/net/ipv4/ip_tunnel.c#L1035">1035</a> 
<a name="L1036" href="source/net/ipv4/ip_tunnel.c#L1036">1036</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=IP_TNL_HASH_SIZE">IP_TNL_HASH_SIZE</a>; <a href="ident?i=h">h</a>++) {
<a name="L1037" href="source/net/ipv4/ip_tunnel.c#L1037">1037</a>                 struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>;
<a name="L1038" href="source/net/ipv4/ip_tunnel.c#L1038">1038</a>                 struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L1039" href="source/net/ipv4/ip_tunnel.c#L1039">1039</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *thead = &amp;itn-&gt;<a href="ident?i=tunnels">tunnels</a>[<a href="ident?i=h">h</a>];
<a name="L1040" href="source/net/ipv4/ip_tunnel.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/ip_tunnel.c#L1041">1041</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(<a href="ident?i=t">t</a>, <a href="ident?i=n">n</a>, thead, hash_node)
<a name="L1042" href="source/net/ipv4/ip_tunnel.c#L1042">1042</a>                         <b><i>/* If dev is in the same netns, it has already</i></b>
<a name="L1043" href="source/net/ipv4/ip_tunnel.c#L1043">1043</a> <b><i>                         * been added to the list by the previous loop.</i></b>
<a name="L1044" href="source/net/ipv4/ip_tunnel.c#L1044">1044</a> <b><i>                         */</i></b>
<a name="L1045" href="source/net/ipv4/ip_tunnel.c#L1045">1045</a>                         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=net">net</a>))
<a name="L1046" href="source/net/ipv4/ip_tunnel.c#L1046">1046</a>                                 <a href="ident?i=unregister_netdevice_queue">unregister_netdevice_queue</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=head">head</a>);
<a name="L1047" href="source/net/ipv4/ip_tunnel.c#L1047">1047</a>         }
<a name="L1048" href="source/net/ipv4/ip_tunnel.c#L1048">1048</a> }
<a name="L1049" href="source/net/ipv4/ip_tunnel.c#L1049">1049</a> 
<a name="L1050" href="source/net/ipv4/ip_tunnel.c#L1050">1050</a> void <a href="ident?i=ip_tunnel_delete_net">ip_tunnel_delete_net</a>(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn, struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> *<a href="ident?i=ops">ops</a>)
<a name="L1051" href="source/net/ipv4/ip_tunnel.c#L1051">1051</a> {
<a name="L1052" href="source/net/ipv4/ip_tunnel.c#L1052">1052</a>         <a href="ident?i=LIST_HEAD">LIST_HEAD</a>(<a href="ident?i=list">list</a>);
<a name="L1053" href="source/net/ipv4/ip_tunnel.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/ip_tunnel.c#L1054">1054</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1055" href="source/net/ipv4/ip_tunnel.c#L1055">1055</a>         <a href="ident?i=ip_tunnel_destroy">ip_tunnel_destroy</a>(itn, &amp;<a href="ident?i=list">list</a>, <a href="ident?i=ops">ops</a>);
<a name="L1056" href="source/net/ipv4/ip_tunnel.c#L1056">1056</a>         <a href="ident?i=unregister_netdevice_many">unregister_netdevice_many</a>(&amp;<a href="ident?i=list">list</a>);
<a name="L1057" href="source/net/ipv4/ip_tunnel.c#L1057">1057</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1058" href="source/net/ipv4/ip_tunnel.c#L1058">1058</a> }
<a name="L1059" href="source/net/ipv4/ip_tunnel.c#L1059">1059</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_delete_net">ip_tunnel_delete_net</a>);
<a name="L1060" href="source/net/ipv4/ip_tunnel.c#L1060">1060</a> 
<a name="L1061" href="source/net/ipv4/ip_tunnel.c#L1061">1061</a> int <a href="ident?i=ip_tunnel_newlink">ip_tunnel_newlink</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L1062" href="source/net/ipv4/ip_tunnel.c#L1062">1062</a>                       struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a>)
<a name="L1063" href="source/net/ipv4/ip_tunnel.c#L1063">1063</a> {
<a name="L1064" href="source/net/ipv4/ip_tunnel.c#L1064">1064</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *nt;
<a name="L1065" href="source/net/ipv4/ip_tunnel.c#L1065">1065</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1066" href="source/net/ipv4/ip_tunnel.c#L1066">1066</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn;
<a name="L1067" href="source/net/ipv4/ip_tunnel.c#L1067">1067</a>         int <a href="ident?i=mtu">mtu</a>;
<a name="L1068" href="source/net/ipv4/ip_tunnel.c#L1068">1068</a>         int <a href="ident?i=err">err</a>;
<a name="L1069" href="source/net/ipv4/ip_tunnel.c#L1069">1069</a> 
<a name="L1070" href="source/net/ipv4/ip_tunnel.c#L1070">1070</a>         nt = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L1071" href="source/net/ipv4/ip_tunnel.c#L1071">1071</a>         itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, nt-&gt;ip_tnl_net_id);
<a name="L1072" href="source/net/ipv4/ip_tunnel.c#L1072">1072</a> 
<a name="L1073" href="source/net/ipv4/ip_tunnel.c#L1073">1073</a>         if (<a href="ident?i=ip_tunnel_find">ip_tunnel_find</a>(itn, <a href="ident?i=p">p</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>))
<a name="L1074" href="source/net/ipv4/ip_tunnel.c#L1074">1074</a>                 return -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L1075" href="source/net/ipv4/ip_tunnel.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/ip_tunnel.c#L1076">1076</a>         nt-&gt;<a href="ident?i=net">net</a> = <a href="ident?i=net">net</a>;
<a name="L1077" href="source/net/ipv4/ip_tunnel.c#L1077">1077</a>         nt-&gt;<a href="ident?i=parms">parms</a> = *<a href="ident?i=p">p</a>;
<a name="L1078" href="source/net/ipv4/ip_tunnel.c#L1078">1078</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_netdevice">register_netdevice</a>(<a href="ident?i=dev">dev</a>);
<a name="L1079" href="source/net/ipv4/ip_tunnel.c#L1079">1079</a>         if (<a href="ident?i=err">err</a>)
<a name="L1080" href="source/net/ipv4/ip_tunnel.c#L1080">1080</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1081" href="source/net/ipv4/ip_tunnel.c#L1081">1081</a> 
<a name="L1082" href="source/net/ipv4/ip_tunnel.c#L1082">1082</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a> &amp;&amp; !<a href="ident?i=tb">tb</a>[IFLA_ADDRESS])
<a name="L1083" href="source/net/ipv4/ip_tunnel.c#L1083">1083</a>                 <a href="ident?i=eth_hw_addr_random">eth_hw_addr_random</a>(<a href="ident?i=dev">dev</a>);
<a name="L1084" href="source/net/ipv4/ip_tunnel.c#L1084">1084</a> 
<a name="L1085" href="source/net/ipv4/ip_tunnel.c#L1085">1085</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=ip_tunnel_bind_dev">ip_tunnel_bind_dev</a>(<a href="ident?i=dev">dev</a>);
<a name="L1086" href="source/net/ipv4/ip_tunnel.c#L1086">1086</a>         if (!<a href="ident?i=tb">tb</a>[IFLA_MTU])
<a name="L1087" href="source/net/ipv4/ip_tunnel.c#L1087">1087</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a> = <a href="ident?i=mtu">mtu</a>;
<a name="L1088" href="source/net/ipv4/ip_tunnel.c#L1088">1088</a> 
<a name="L1089" href="source/net/ipv4/ip_tunnel.c#L1089">1089</a>         <a href="ident?i=ip_tunnel_add">ip_tunnel_add</a>(itn, nt);
<a name="L1090" href="source/net/ipv4/ip_tunnel.c#L1090">1090</a> 
<a name="L1091" href="source/net/ipv4/ip_tunnel.c#L1091">1091</a> <a href="ident?i=out">out</a>:
<a name="L1092" href="source/net/ipv4/ip_tunnel.c#L1092">1092</a>         return <a href="ident?i=err">err</a>;
<a name="L1093" href="source/net/ipv4/ip_tunnel.c#L1093">1093</a> }
<a name="L1094" href="source/net/ipv4/ip_tunnel.c#L1094">1094</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_newlink">ip_tunnel_newlink</a>);
<a name="L1095" href="source/net/ipv4/ip_tunnel.c#L1095">1095</a> 
<a name="L1096" href="source/net/ipv4/ip_tunnel.c#L1096">1096</a> int <a href="ident?i=ip_tunnel_changelink">ip_tunnel_changelink</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L1097" href="source/net/ipv4/ip_tunnel.c#L1097">1097</a>                          struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a>)
<a name="L1098" href="source/net/ipv4/ip_tunnel.c#L1098">1098</a> {
<a name="L1099" href="source/net/ipv4/ip_tunnel.c#L1099">1099</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>;
<a name="L1100" href="source/net/ipv4/ip_tunnel.c#L1100">1100</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L1101" href="source/net/ipv4/ip_tunnel.c#L1101">1101</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = tunnel-&gt;<a href="ident?i=net">net</a>;
<a name="L1102" href="source/net/ipv4/ip_tunnel.c#L1102">1102</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, tunnel-&gt;ip_tnl_net_id);
<a name="L1103" href="source/net/ipv4/ip_tunnel.c#L1103">1103</a> 
<a name="L1104" href="source/net/ipv4/ip_tunnel.c#L1104">1104</a>         if (<a href="ident?i=dev">dev</a> == itn-&gt;fb_tunnel_dev)
<a name="L1105" href="source/net/ipv4/ip_tunnel.c#L1105">1105</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1106" href="source/net/ipv4/ip_tunnel.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/ip_tunnel.c#L1107">1107</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_find">ip_tunnel_find</a>(itn, <a href="ident?i=p">p</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>);
<a name="L1108" href="source/net/ipv4/ip_tunnel.c#L1108">1108</a> 
<a name="L1109" href="source/net/ipv4/ip_tunnel.c#L1109">1109</a>         if (<a href="ident?i=t">t</a>) {
<a name="L1110" href="source/net/ipv4/ip_tunnel.c#L1110">1110</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>)
<a name="L1111" href="source/net/ipv4/ip_tunnel.c#L1111">1111</a>                         return -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L1112" href="source/net/ipv4/ip_tunnel.c#L1112">1112</a>         } else {
<a name="L1113" href="source/net/ipv4/ip_tunnel.c#L1113">1113</a>                 <a href="ident?i=t">t</a> = tunnel;
<a name="L1114" href="source/net/ipv4/ip_tunnel.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/ip_tunnel.c#L1115">1115</a>                 if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>) {
<a name="L1116" href="source/net/ipv4/ip_tunnel.c#L1116">1116</a>                         unsigned int nflags = 0;
<a name="L1117" href="source/net/ipv4/ip_tunnel.c#L1117">1117</a> 
<a name="L1118" href="source/net/ipv4/ip_tunnel.c#L1118">1118</a>                         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>))
<a name="L1119" href="source/net/ipv4/ip_tunnel.c#L1119">1119</a>                                 nflags = <a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>;
<a name="L1120" href="source/net/ipv4/ip_tunnel.c#L1120">1120</a>                         else if (<a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>)
<a name="L1121" href="source/net/ipv4/ip_tunnel.c#L1121">1121</a>                                 nflags = <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>;
<a name="L1122" href="source/net/ipv4/ip_tunnel.c#L1122">1122</a> 
<a name="L1123" href="source/net/ipv4/ip_tunnel.c#L1123">1123</a>                         if ((<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> ^ nflags) &amp;
<a name="L1124" href="source/net/ipv4/ip_tunnel.c#L1124">1124</a>                             (<a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a> | <a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>))
<a name="L1125" href="source/net/ipv4/ip_tunnel.c#L1125">1125</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1126" href="source/net/ipv4/ip_tunnel.c#L1126">1126</a>                 }
<a name="L1127" href="source/net/ipv4/ip_tunnel.c#L1127">1127</a>         }
<a name="L1128" href="source/net/ipv4/ip_tunnel.c#L1128">1128</a> 
<a name="L1129" href="source/net/ipv4/ip_tunnel.c#L1129">1129</a>         <a href="ident?i=ip_tunnel_update">ip_tunnel_update</a>(itn, <a href="ident?i=t">t</a>, <a href="ident?i=dev">dev</a>, <a href="ident?i=p">p</a>, !<a href="ident?i=tb">tb</a>[IFLA_MTU]);
<a name="L1130" href="source/net/ipv4/ip_tunnel.c#L1130">1130</a>         return 0;
<a name="L1131" href="source/net/ipv4/ip_tunnel.c#L1131">1131</a> }
<a name="L1132" href="source/net/ipv4/ip_tunnel.c#L1132">1132</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_changelink">ip_tunnel_changelink</a>);
<a name="L1133" href="source/net/ipv4/ip_tunnel.c#L1133">1133</a> 
<a name="L1134" href="source/net/ipv4/ip_tunnel.c#L1134">1134</a> int <a href="ident?i=ip_tunnel_init">ip_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1135" href="source/net/ipv4/ip_tunnel.c#L1135">1135</a> {
<a name="L1136" href="source/net/ipv4/ip_tunnel.c#L1136">1136</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L1137" href="source/net/ipv4/ip_tunnel.c#L1137">1137</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L1138" href="source/net/ipv4/ip_tunnel.c#L1138">1138</a>         int <a href="ident?i=err">err</a>;
<a name="L1139" href="source/net/ipv4/ip_tunnel.c#L1139">1139</a> 
<a name="L1140" href="source/net/ipv4/ip_tunnel.c#L1140">1140</a>         <a href="ident?i=dev">dev</a>-&gt;destructor = <a href="ident?i=ip_tunnel_dev_free">ip_tunnel_dev_free</a>;
<a name="L1141" href="source/net/ipv4/ip_tunnel.c#L1141">1141</a>         <a href="ident?i=dev">dev</a>-&gt;tstats = <a href="ident?i=netdev_alloc_pcpu_stats">netdev_alloc_pcpu_stats</a>(struct <a href="ident?i=pcpu_sw_netstats">pcpu_sw_netstats</a>);
<a name="L1142" href="source/net/ipv4/ip_tunnel.c#L1142">1142</a>         if (!<a href="ident?i=dev">dev</a>-&gt;tstats)
<a name="L1143" href="source/net/ipv4/ip_tunnel.c#L1143">1143</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1144" href="source/net/ipv4/ip_tunnel.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/ip_tunnel.c#L1145">1145</a>         tunnel-&gt;dst_cache = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=ip_tunnel_dst">ip_tunnel_dst</a>);
<a name="L1146" href="source/net/ipv4/ip_tunnel.c#L1146">1146</a>         if (!tunnel-&gt;dst_cache) {
<a name="L1147" href="source/net/ipv4/ip_tunnel.c#L1147">1147</a>                 <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L1148" href="source/net/ipv4/ip_tunnel.c#L1148">1148</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1149" href="source/net/ipv4/ip_tunnel.c#L1149">1149</a>         }
<a name="L1150" href="source/net/ipv4/ip_tunnel.c#L1150">1150</a> 
<a name="L1151" href="source/net/ipv4/ip_tunnel.c#L1151">1151</a>         <a href="ident?i=err">err</a> = <a href="ident?i=gro_cells_init">gro_cells_init</a>(&amp;tunnel-&gt;<a href="ident?i=gro_cells">gro_cells</a>, <a href="ident?i=dev">dev</a>);
<a name="L1152" href="source/net/ipv4/ip_tunnel.c#L1152">1152</a>         if (<a href="ident?i=err">err</a>) {
<a name="L1153" href="source/net/ipv4/ip_tunnel.c#L1153">1153</a>                 <a href="ident?i=free_percpu">free_percpu</a>(tunnel-&gt;dst_cache);
<a name="L1154" href="source/net/ipv4/ip_tunnel.c#L1154">1154</a>                 <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L1155" href="source/net/ipv4/ip_tunnel.c#L1155">1155</a>                 return <a href="ident?i=err">err</a>;
<a name="L1156" href="source/net/ipv4/ip_tunnel.c#L1156">1156</a>         }
<a name="L1157" href="source/net/ipv4/ip_tunnel.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/ip_tunnel.c#L1158">1158</a>         tunnel-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L1159" href="source/net/ipv4/ip_tunnel.c#L1159">1159</a>         tunnel-&gt;<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1160" href="source/net/ipv4/ip_tunnel.c#L1160">1160</a>         <a href="ident?i=strcpy">strcpy</a>(tunnel-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=name">name</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L1161" href="source/net/ipv4/ip_tunnel.c#L1161">1161</a>         iph-&gt;<a href="ident?i=version">version</a>            = 4;
<a name="L1162" href="source/net/ipv4/ip_tunnel.c#L1162">1162</a>         iph-&gt;ihl                = 5;
<a name="L1163" href="source/net/ipv4/ip_tunnel.c#L1163">1163</a> 
<a name="L1164" href="source/net/ipv4/ip_tunnel.c#L1164">1164</a>         return 0;
<a name="L1165" href="source/net/ipv4/ip_tunnel.c#L1165">1165</a> }
<a name="L1166" href="source/net/ipv4/ip_tunnel.c#L1166">1166</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_init">ip_tunnel_init</a>);
<a name="L1167" href="source/net/ipv4/ip_tunnel.c#L1167">1167</a> 
<a name="L1168" href="source/net/ipv4/ip_tunnel.c#L1168">1168</a> void <a href="ident?i=ip_tunnel_uninit">ip_tunnel_uninit</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1169" href="source/net/ipv4/ip_tunnel.c#L1169">1169</a> {
<a name="L1170" href="source/net/ipv4/ip_tunnel.c#L1170">1170</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L1171" href="source/net/ipv4/ip_tunnel.c#L1171">1171</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = tunnel-&gt;<a href="ident?i=net">net</a>;
<a name="L1172" href="source/net/ipv4/ip_tunnel.c#L1172">1172</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn;
<a name="L1173" href="source/net/ipv4/ip_tunnel.c#L1173">1173</a> 
<a name="L1174" href="source/net/ipv4/ip_tunnel.c#L1174">1174</a>         itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, tunnel-&gt;ip_tnl_net_id);
<a name="L1175" href="source/net/ipv4/ip_tunnel.c#L1175">1175</a>         <b><i>/* fb_tunnel_dev will be unregisted in net-exit call. */</i></b>
<a name="L1176" href="source/net/ipv4/ip_tunnel.c#L1176">1176</a>         if (itn-&gt;fb_tunnel_dev != <a href="ident?i=dev">dev</a>)
<a name="L1177" href="source/net/ipv4/ip_tunnel.c#L1177">1177</a>                 <a href="ident?i=ip_tunnel_del">ip_tunnel_del</a>(<a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>));
<a name="L1178" href="source/net/ipv4/ip_tunnel.c#L1178">1178</a> 
<a name="L1179" href="source/net/ipv4/ip_tunnel.c#L1179">1179</a>         <a href="ident?i=ip_tunnel_dst_reset_all">ip_tunnel_dst_reset_all</a>(tunnel);
<a name="L1180" href="source/net/ipv4/ip_tunnel.c#L1180">1180</a> }
<a name="L1181" href="source/net/ipv4/ip_tunnel.c#L1181">1181</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_uninit">ip_tunnel_uninit</a>);
<a name="L1182" href="source/net/ipv4/ip_tunnel.c#L1182">1182</a> 
<a name="L1183" href="source/net/ipv4/ip_tunnel.c#L1183">1183</a> <b><i>/* Do least required initialization, rest of init is done in tunnel_init call */</i></b>
<a name="L1184" href="source/net/ipv4/ip_tunnel.c#L1184">1184</a> void <a href="ident?i=ip_tunnel_setup">ip_tunnel_setup</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int <a href="ident?i=net_id">net_id</a>)
<a name="L1185" href="source/net/ipv4/ip_tunnel.c#L1185">1185</a> {
<a name="L1186" href="source/net/ipv4/ip_tunnel.c#L1186">1186</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L1187" href="source/net/ipv4/ip_tunnel.c#L1187">1187</a>         tunnel-&gt;ip_tnl_net_id = <a href="ident?i=net_id">net_id</a>;
<a name="L1188" href="source/net/ipv4/ip_tunnel.c#L1188">1188</a> }
<a name="L1189" href="source/net/ipv4/ip_tunnel.c#L1189">1189</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_setup">ip_tunnel_setup</a>);
<a name="L1190" href="source/net/ipv4/ip_tunnel.c#L1190">1190</a> 
<a name="L1191" href="source/net/ipv4/ip_tunnel.c#L1191">1191</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L1192" href="source/net/ipv4/ip_tunnel.c#L1192">1192</a> </pre></div><p>
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
