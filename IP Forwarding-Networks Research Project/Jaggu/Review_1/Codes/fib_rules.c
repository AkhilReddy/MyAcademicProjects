<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/fib_rules.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/fib_rules.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/fib_rules.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/fib_rules.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/fib_rules.c">fib_rules.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/fib_rules.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/fib_rules.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/fib_rules.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/fib_rules.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/fib_rules.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/fib_rules.c#L6">6</a> <b><i> *              IPv4 Forwarding Information Base: policy rules.</i></b>
  <a name="L7" href="source/net/ipv4/fib_rules.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/fib_rules.c#L8">8</a> <b><i> * Authors:     Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
  <a name="L9" href="source/net/ipv4/fib_rules.c#L9">9</a> <b><i> *              Thomas Graf &lt;tgraf@suug.ch&gt;</i></b>
 <a name="L10" href="source/net/ipv4/fib_rules.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/fib_rules.c#L11">11</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L12" href="source/net/ipv4/fib_rules.c#L12">12</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L13" href="source/net/ipv4/fib_rules.c#L13">13</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L14" href="source/net/ipv4/fib_rules.c#L14">14</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L15" href="source/net/ipv4/fib_rules.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/fib_rules.c#L16">16</a> <b><i> * Fixes:</i></b>
 <a name="L17" href="source/net/ipv4/fib_rules.c#L17">17</a> <b><i> *              Rani Assaf      :       local_rule cannot be deleted</i></b>
 <a name="L18" href="source/net/ipv4/fib_rules.c#L18">18</a> <b><i> *              Marc Boucher    :       routing by fwmark</i></b>
 <a name="L19" href="source/net/ipv4/fib_rules.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/fib_rules.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/fib_rules.c#L21">21</a> #include &lt;linux/types.h&gt;
 <a name="L22" href="source/net/ipv4/fib_rules.c#L22">22</a> #include &lt;linux/kernel.h&gt;
 <a name="L23" href="source/net/ipv4/fib_rules.c#L23">23</a> #include &lt;linux/netdevice.h&gt;
 <a name="L24" href="source/net/ipv4/fib_rules.c#L24">24</a> #include &lt;linux/netlink.h&gt;
 <a name="L25" href="source/net/ipv4/fib_rules.c#L25">25</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L26" href="source/net/ipv4/fib_rules.c#L26">26</a> #include &lt;linux/init.h&gt;
 <a name="L27" href="source/net/ipv4/fib_rules.c#L27">27</a> #include &lt;linux/list.h&gt;
 <a name="L28" href="source/net/ipv4/fib_rules.c#L28">28</a> #include &lt;linux/rcupdate.h&gt;
 <a name="L29" href="source/net/ipv4/fib_rules.c#L29">29</a> #include &lt;linux/export.h&gt;
 <a name="L30" href="source/net/ipv4/fib_rules.c#L30">30</a> #include &lt;net/ip.h&gt;
 <a name="L31" href="source/net/ipv4/fib_rules.c#L31">31</a> #include &lt;net/route.h&gt;
 <a name="L32" href="source/net/ipv4/fib_rules.c#L32">32</a> #include &lt;net/tcp.h&gt;
 <a name="L33" href="source/net/ipv4/fib_rules.c#L33">33</a> #include &lt;net/ip_fib.h&gt;
 <a name="L34" href="source/net/ipv4/fib_rules.c#L34">34</a> #include &lt;net/fib_rules.h&gt;
 <a name="L35" href="source/net/ipv4/fib_rules.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/fib_rules.c#L36">36</a> struct <a href="ident?i=fib4_rule">fib4_rule</a> {
 <a name="L37" href="source/net/ipv4/fib_rules.c#L37">37</a>         struct <a href="ident?i=fib_rule">fib_rule</a>         <a href="ident?i=common">common</a>;
 <a name="L38" href="source/net/ipv4/fib_rules.c#L38">38</a>         <a href="ident?i=u8">u8</a>                      dst_len;
 <a name="L39" href="source/net/ipv4/fib_rules.c#L39">39</a>         <a href="ident?i=u8">u8</a>                      src_len;
 <a name="L40" href="source/net/ipv4/fib_rules.c#L40">40</a>         <a href="ident?i=u8">u8</a>                      tos;
 <a name="L41" href="source/net/ipv4/fib_rules.c#L41">41</a>         <a href="ident?i=__be32">__be32</a>                  <a href="ident?i=src">src</a>;
 <a name="L42" href="source/net/ipv4/fib_rules.c#L42">42</a>         <a href="ident?i=__be32">__be32</a>                  srcmask;
 <a name="L43" href="source/net/ipv4/fib_rules.c#L43">43</a>         <a href="ident?i=__be32">__be32</a>                  <a href="ident?i=dst">dst</a>;
 <a name="L44" href="source/net/ipv4/fib_rules.c#L44">44</a>         <a href="ident?i=__be32">__be32</a>                  dstmask;
 <a name="L45" href="source/net/ipv4/fib_rules.c#L45">45</a> #ifdef CONFIG_IP_ROUTE_CLASSID
 <a name="L46" href="source/net/ipv4/fib_rules.c#L46">46</a>         <a href="ident?i=u32">u32</a>                     tclassid;
 <a name="L47" href="source/net/ipv4/fib_rules.c#L47">47</a> #endif
 <a name="L48" href="source/net/ipv4/fib_rules.c#L48">48</a> };
 <a name="L49" href="source/net/ipv4/fib_rules.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/fib_rules.c#L50">50</a> int <a href="ident?i=__fib_lookup">__fib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=flowi4">flowi4</a> *flp, struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>)
 <a name="L51" href="source/net/ipv4/fib_rules.c#L51">51</a> {
 <a name="L52" href="source/net/ipv4/fib_rules.c#L52">52</a>         struct <a href="ident?i=fib_lookup_arg">fib_lookup_arg</a> <a href="ident?i=arg">arg</a> = {
 <a name="L53" href="source/net/ipv4/fib_rules.c#L53">53</a>                 .<a href="ident?i=result">result</a> = <a href="ident?i=res">res</a>,
 <a name="L54" href="source/net/ipv4/fib_rules.c#L54">54</a>                 .<a href="ident?i=flags">flags</a> = <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>,
 <a name="L55" href="source/net/ipv4/fib_rules.c#L55">55</a>         };
 <a name="L56" href="source/net/ipv4/fib_rules.c#L56">56</a>         int <a href="ident?i=err">err</a>;
 <a name="L57" href="source/net/ipv4/fib_rules.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/fib_rules.c#L58">58</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_rules_lookup">fib_rules_lookup</a>(<a href="ident?i=net">net</a>-&gt;ipv4.rules_ops, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(flp), 0, &amp;<a href="ident?i=arg">arg</a>);
 <a name="L59" href="source/net/ipv4/fib_rules.c#L59">59</a> #ifdef CONFIG_IP_ROUTE_CLASSID
 <a name="L60" href="source/net/ipv4/fib_rules.c#L60">60</a>         if (<a href="ident?i=arg">arg</a>.rule)
 <a name="L61" href="source/net/ipv4/fib_rules.c#L61">61</a>                 <a href="ident?i=res">res</a>-&gt;tclassid = ((struct <a href="ident?i=fib4_rule">fib4_rule</a> *)<a href="ident?i=arg">arg</a>.rule)-&gt;tclassid;
 <a name="L62" href="source/net/ipv4/fib_rules.c#L62">62</a>         else
 <a name="L63" href="source/net/ipv4/fib_rules.c#L63">63</a>                 <a href="ident?i=res">res</a>-&gt;tclassid = 0;
 <a name="L64" href="source/net/ipv4/fib_rules.c#L64">64</a> #endif
 <a name="L65" href="source/net/ipv4/fib_rules.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/fib_rules.c#L66">66</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ESRCH">ESRCH</a>)
 <a name="L67" href="source/net/ipv4/fib_rules.c#L67">67</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>;
 <a name="L68" href="source/net/ipv4/fib_rules.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/fib_rules.c#L69">69</a>         return <a href="ident?i=err">err</a>;
 <a name="L70" href="source/net/ipv4/fib_rules.c#L70">70</a> }
 <a name="L71" href="source/net/ipv4/fib_rules.c#L71">71</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__fib_lookup">__fib_lookup</a>);
 <a name="L72" href="source/net/ipv4/fib_rules.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/fib_rules.c#L73">73</a> static int <a href="ident?i=fib4_rule_action">fib4_rule_action</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=flowi">flowi</a> *flp,
 <a name="L74" href="source/net/ipv4/fib_rules.c#L74">74</a>                             int <a href="ident?i=flags">flags</a>, struct <a href="ident?i=fib_lookup_arg">fib_lookup_arg</a> *<a href="ident?i=arg">arg</a>)
 <a name="L75" href="source/net/ipv4/fib_rules.c#L75">75</a> {
 <a name="L76" href="source/net/ipv4/fib_rules.c#L76">76</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
 <a name="L77" href="source/net/ipv4/fib_rules.c#L77">77</a>         struct <a href="ident?i=fib_table">fib_table</a> *tbl;
 <a name="L78" href="source/net/ipv4/fib_rules.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/fib_rules.c#L79">79</a>         switch (rule-&gt;<a href="ident?i=action">action</a>) {
 <a name="L80" href="source/net/ipv4/fib_rules.c#L80">80</a>         case FR_ACT_TO_TBL:
 <a name="L81" href="source/net/ipv4/fib_rules.c#L81">81</a>                 break;
 <a name="L82" href="source/net/ipv4/fib_rules.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/fib_rules.c#L83">83</a>         case FR_ACT_UNREACHABLE:
 <a name="L84" href="source/net/ipv4/fib_rules.c#L84">84</a>                 return -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>;
 <a name="L85" href="source/net/ipv4/fib_rules.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/fib_rules.c#L86">86</a>         case FR_ACT_PROHIBIT:
 <a name="L87" href="source/net/ipv4/fib_rules.c#L87">87</a>                 return -<a href="ident?i=EACCES">EACCES</a>;
 <a name="L88" href="source/net/ipv4/fib_rules.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/fib_rules.c#L89">89</a>         case FR_ACT_BLACKHOLE:
 <a name="L90" href="source/net/ipv4/fib_rules.c#L90">90</a>         default:
 <a name="L91" href="source/net/ipv4/fib_rules.c#L91">91</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L92" href="source/net/ipv4/fib_rules.c#L92">92</a>         }
 <a name="L93" href="source/net/ipv4/fib_rules.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/fib_rules.c#L94">94</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
 <a name="L95" href="source/net/ipv4/fib_rules.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/fib_rules.c#L96">96</a>         tbl = <a href="ident?i=fib_get_table">fib_get_table</a>(rule-&gt;fr_net, rule-&gt;<a href="ident?i=table">table</a>);
 <a name="L97" href="source/net/ipv4/fib_rules.c#L97">97</a>         if (tbl)
 <a name="L98" href="source/net/ipv4/fib_rules.c#L98">98</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fib_table_lookup">fib_table_lookup</a>(tbl, &amp;flp-&gt;u.ip4,
 <a name="L99" href="source/net/ipv4/fib_rules.c#L99">99</a>                                        (struct <a href="ident?i=fib_result">fib_result</a> *)<a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=result">result</a>,
<a name="L100" href="source/net/ipv4/fib_rules.c#L100">100</a>                                        <a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=flags">flags</a>);
<a name="L101" href="source/net/ipv4/fib_rules.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/fib_rules.c#L102">102</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L103" href="source/net/ipv4/fib_rules.c#L103">103</a>         return <a href="ident?i=err">err</a>;
<a name="L104" href="source/net/ipv4/fib_rules.c#L104">104</a> }
<a name="L105" href="source/net/ipv4/fib_rules.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/fib_rules.c#L106">106</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=fib4_rule_suppress">fib4_rule_suppress</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=fib_lookup_arg">fib_lookup_arg</a> *<a href="ident?i=arg">arg</a>)
<a name="L107" href="source/net/ipv4/fib_rules.c#L107">107</a> {
<a name="L108" href="source/net/ipv4/fib_rules.c#L108">108</a>         struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=result">result</a> = (struct <a href="ident?i=fib_result">fib_result</a> *) <a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=result">result</a>;
<a name="L109" href="source/net/ipv4/fib_rules.c#L109">109</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L110" href="source/net/ipv4/fib_rules.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/fib_rules.c#L111">111</a>         if (<a href="ident?i=result">result</a>-&gt;fi)
<a name="L112" href="source/net/ipv4/fib_rules.c#L112">112</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=result">result</a>-&gt;fi-&gt;<a href="ident?i=fib_dev">fib_dev</a>;
<a name="L113" href="source/net/ipv4/fib_rules.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/fib_rules.c#L114">114</a>         <b><i>/* do not accept result if the route does</i></b>
<a name="L115" href="source/net/ipv4/fib_rules.c#L115">115</a> <b><i>         * not meet the required prefix length</i></b>
<a name="L116" href="source/net/ipv4/fib_rules.c#L116">116</a> <b><i>         */</i></b>
<a name="L117" href="source/net/ipv4/fib_rules.c#L117">117</a>         if (<a href="ident?i=result">result</a>-&gt;prefixlen &lt;= rule-&gt;suppress_prefixlen)
<a name="L118" href="source/net/ipv4/fib_rules.c#L118">118</a>                 goto suppress_route;
<a name="L119" href="source/net/ipv4/fib_rules.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/fib_rules.c#L120">120</a>         <b><i>/* do not accept result if the route uses a device</i></b>
<a name="L121" href="source/net/ipv4/fib_rules.c#L121">121</a> <b><i>         * belonging to a forbidden interface group</i></b>
<a name="L122" href="source/net/ipv4/fib_rules.c#L122">122</a> <b><i>         */</i></b>
<a name="L123" href="source/net/ipv4/fib_rules.c#L123">123</a>         if (rule-&gt;suppress_ifgroup != -1 &amp;&amp; <a href="ident?i=dev">dev</a> &amp;&amp; <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=group">group</a> == rule-&gt;suppress_ifgroup)
<a name="L124" href="source/net/ipv4/fib_rules.c#L124">124</a>                 goto suppress_route;
<a name="L125" href="source/net/ipv4/fib_rules.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/fib_rules.c#L126">126</a>         return <a href="ident?i=false">false</a>;
<a name="L127" href="source/net/ipv4/fib_rules.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/fib_rules.c#L128">128</a> suppress_route:
<a name="L129" href="source/net/ipv4/fib_rules.c#L129">129</a>         if (!(<a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>))
<a name="L130" href="source/net/ipv4/fib_rules.c#L130">130</a>                 <a href="ident?i=fib_info_put">fib_info_put</a>(<a href="ident?i=result">result</a>-&gt;fi);
<a name="L131" href="source/net/ipv4/fib_rules.c#L131">131</a>         return <a href="ident?i=true">true</a>;
<a name="L132" href="source/net/ipv4/fib_rules.c#L132">132</a> }
<a name="L133" href="source/net/ipv4/fib_rules.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/fib_rules.c#L134">134</a> static int <a href="ident?i=fib4_rule_match">fib4_rule_match</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=flowi">flowi</a> *fl, int <a href="ident?i=flags">flags</a>)
<a name="L135" href="source/net/ipv4/fib_rules.c#L135">135</a> {
<a name="L136" href="source/net/ipv4/fib_rules.c#L136">136</a>         struct <a href="ident?i=fib4_rule">fib4_rule</a> *<a href="ident?i=r">r</a> = (struct <a href="ident?i=fib4_rule">fib4_rule</a> *) rule;
<a name="L137" href="source/net/ipv4/fib_rules.c#L137">137</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4 = &amp;fl-&gt;u.ip4;
<a name="L138" href="source/net/ipv4/fib_rules.c#L138">138</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = fl4-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L139" href="source/net/ipv4/fib_rules.c#L139">139</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L140" href="source/net/ipv4/fib_rules.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/fib_rules.c#L141">141</a>         if (((<a href="ident?i=saddr">saddr</a> ^ <a href="ident?i=r">r</a>-&gt;<a href="ident?i=src">src</a>) &amp; <a href="ident?i=r">r</a>-&gt;srcmask) ||
<a name="L142" href="source/net/ipv4/fib_rules.c#L142">142</a>             ((<a href="ident?i=daddr">daddr</a> ^ <a href="ident?i=r">r</a>-&gt;<a href="ident?i=dst">dst</a>) &amp; <a href="ident?i=r">r</a>-&gt;dstmask))
<a name="L143" href="source/net/ipv4/fib_rules.c#L143">143</a>                 return 0;
<a name="L144" href="source/net/ipv4/fib_rules.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/fib_rules.c#L145">145</a>         if (<a href="ident?i=r">r</a>-&gt;tos &amp;&amp; (<a href="ident?i=r">r</a>-&gt;tos != fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a>))
<a name="L146" href="source/net/ipv4/fib_rules.c#L146">146</a>                 return 0;
<a name="L147" href="source/net/ipv4/fib_rules.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/fib_rules.c#L148">148</a>         return 1;
<a name="L149" href="source/net/ipv4/fib_rules.c#L149">149</a> }
<a name="L150" href="source/net/ipv4/fib_rules.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/fib_rules.c#L151">151</a> static struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=fib_empty_table">fib_empty_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L152" href="source/net/ipv4/fib_rules.c#L152">152</a> {
<a name="L153" href="source/net/ipv4/fib_rules.c#L153">153</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>;
<a name="L154" href="source/net/ipv4/fib_rules.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/fib_rules.c#L155">155</a>         for (<a href="ident?i=id">id</a> = 1; <a href="ident?i=id">id</a> &lt;= RT_TABLE_MAX; <a href="ident?i=id">id</a>++)
<a name="L156" href="source/net/ipv4/fib_rules.c#L156">156</a>                 if (!<a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=id">id</a>))
<a name="L157" href="source/net/ipv4/fib_rules.c#L157">157</a>                         return <a href="ident?i=fib_new_table">fib_new_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=id">id</a>);
<a name="L158" href="source/net/ipv4/fib_rules.c#L158">158</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L159" href="source/net/ipv4/fib_rules.c#L159">159</a> }
<a name="L160" href="source/net/ipv4/fib_rules.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/fib_rules.c#L161">161</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=fib4_rule_policy">fib4_rule_policy</a>[<a href="ident?i=FRA_MAX">FRA_MAX</a>+1] = {
<a name="L162" href="source/net/ipv4/fib_rules.c#L162">162</a>         <a href="ident?i=FRA_GENERIC_POLICY">FRA_GENERIC_POLICY</a>,
<a name="L163" href="source/net/ipv4/fib_rules.c#L163">163</a>         [FRA_FLOW]      = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L164" href="source/net/ipv4/fib_rules.c#L164">164</a> };
<a name="L165" href="source/net/ipv4/fib_rules.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/fib_rules.c#L166">166</a> static int <a href="ident?i=fib4_rule_configure">fib4_rule_configure</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L167" href="source/net/ipv4/fib_rules.c#L167">167</a>                                struct <a href="ident?i=fib_rule_hdr">fib_rule_hdr</a> *frh,
<a name="L168" href="source/net/ipv4/fib_rules.c#L168">168</a>                                struct <a href="ident?i=nlattr">nlattr</a> **<a href="ident?i=tb">tb</a>)
<a name="L169" href="source/net/ipv4/fib_rules.c#L169">169</a> {
<a name="L170" href="source/net/ipv4/fib_rules.c#L170">170</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L171" href="source/net/ipv4/fib_rules.c#L171">171</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L172" href="source/net/ipv4/fib_rules.c#L172">172</a>         struct <a href="ident?i=fib4_rule">fib4_rule</a> *rule4 = (struct <a href="ident?i=fib4_rule">fib4_rule</a> *) rule;
<a name="L173" href="source/net/ipv4/fib_rules.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/fib_rules.c#L174">174</a>         if (frh-&gt;tos &amp; ~IPTOS_TOS_MASK)
<a name="L175" href="source/net/ipv4/fib_rules.c#L175">175</a>                 goto errout;
<a name="L176" href="source/net/ipv4/fib_rules.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/fib_rules.c#L177">177</a>         <b><i>/* split local/main if they are not already split */</i></b>
<a name="L178" href="source/net/ipv4/fib_rules.c#L178">178</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_unmerge">fib_unmerge</a>(<a href="ident?i=net">net</a>);
<a name="L179" href="source/net/ipv4/fib_rules.c#L179">179</a>         if (<a href="ident?i=err">err</a>)
<a name="L180" href="source/net/ipv4/fib_rules.c#L180">180</a>                 goto errout;
<a name="L181" href="source/net/ipv4/fib_rules.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/fib_rules.c#L182">182</a>         if (rule-&gt;<a href="ident?i=table">table</a> == RT_TABLE_UNSPEC) {
<a name="L183" href="source/net/ipv4/fib_rules.c#L183">183</a>                 if (rule-&gt;<a href="ident?i=action">action</a> == FR_ACT_TO_TBL) {
<a name="L184" href="source/net/ipv4/fib_rules.c#L184">184</a>                         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=table">table</a>;
<a name="L185" href="source/net/ipv4/fib_rules.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/fib_rules.c#L186">186</a>                         <a href="ident?i=table">table</a> = <a href="ident?i=fib_empty_table">fib_empty_table</a>(<a href="ident?i=net">net</a>);
<a name="L187" href="source/net/ipv4/fib_rules.c#L187">187</a>                         if (!<a href="ident?i=table">table</a>) {
<a name="L188" href="source/net/ipv4/fib_rules.c#L188">188</a>                                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L189" href="source/net/ipv4/fib_rules.c#L189">189</a>                                 goto errout;
<a name="L190" href="source/net/ipv4/fib_rules.c#L190">190</a>                         }
<a name="L191" href="source/net/ipv4/fib_rules.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/fib_rules.c#L192">192</a>                         rule-&gt;<a href="ident?i=table">table</a> = <a href="ident?i=table">table</a>-&gt;tb_id;
<a name="L193" href="source/net/ipv4/fib_rules.c#L193">193</a>                 }
<a name="L194" href="source/net/ipv4/fib_rules.c#L194">194</a>         }
<a name="L195" href="source/net/ipv4/fib_rules.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/fib_rules.c#L196">196</a>         if (frh-&gt;src_len)
<a name="L197" href="source/net/ipv4/fib_rules.c#L197">197</a>                 rule4-&gt;<a href="ident?i=src">src</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[FRA_SRC]);
<a name="L198" href="source/net/ipv4/fib_rules.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/fib_rules.c#L199">199</a>         if (frh-&gt;dst_len)
<a name="L200" href="source/net/ipv4/fib_rules.c#L200">200</a>                 rule4-&gt;<a href="ident?i=dst">dst</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[FRA_DST]);
<a name="L201" href="source/net/ipv4/fib_rules.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/fib_rules.c#L202">202</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L203" href="source/net/ipv4/fib_rules.c#L203">203</a>         if (<a href="ident?i=tb">tb</a>[FRA_FLOW]) {
<a name="L204" href="source/net/ipv4/fib_rules.c#L204">204</a>                 rule4-&gt;tclassid = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=tb">tb</a>[FRA_FLOW]);
<a name="L205" href="source/net/ipv4/fib_rules.c#L205">205</a>                 if (rule4-&gt;tclassid)
<a name="L206" href="source/net/ipv4/fib_rules.c#L206">206</a>                         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>++;
<a name="L207" href="source/net/ipv4/fib_rules.c#L207">207</a>         }
<a name="L208" href="source/net/ipv4/fib_rules.c#L208">208</a> #endif
<a name="L209" href="source/net/ipv4/fib_rules.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/fib_rules.c#L210">210</a>         rule4-&gt;src_len = frh-&gt;src_len;
<a name="L211" href="source/net/ipv4/fib_rules.c#L211">211</a>         rule4-&gt;srcmask = <a href="ident?i=inet_make_mask">inet_make_mask</a>(rule4-&gt;src_len);
<a name="L212" href="source/net/ipv4/fib_rules.c#L212">212</a>         rule4-&gt;dst_len = frh-&gt;dst_len;
<a name="L213" href="source/net/ipv4/fib_rules.c#L213">213</a>         rule4-&gt;dstmask = <a href="ident?i=inet_make_mask">inet_make_mask</a>(rule4-&gt;dst_len);
<a name="L214" href="source/net/ipv4/fib_rules.c#L214">214</a>         rule4-&gt;tos = frh-&gt;tos;
<a name="L215" href="source/net/ipv4/fib_rules.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/fib_rules.c#L216">216</a>         <a href="ident?i=net">net</a>-&gt;ipv4.fib_has_custom_rules = <a href="ident?i=true">true</a>;
<a name="L217" href="source/net/ipv4/fib_rules.c#L217">217</a>         <a href="ident?i=fib_flush_external">fib_flush_external</a>(rule-&gt;fr_net);
<a name="L218" href="source/net/ipv4/fib_rules.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/fib_rules.c#L219">219</a>         <a href="ident?i=err">err</a> = 0;
<a name="L220" href="source/net/ipv4/fib_rules.c#L220">220</a> errout:
<a name="L221" href="source/net/ipv4/fib_rules.c#L221">221</a>         return <a href="ident?i=err">err</a>;
<a name="L222" href="source/net/ipv4/fib_rules.c#L222">222</a> }
<a name="L223" href="source/net/ipv4/fib_rules.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/fib_rules.c#L224">224</a> static int <a href="ident?i=fib4_rule_delete">fib4_rule_delete</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule)
<a name="L225" href="source/net/ipv4/fib_rules.c#L225">225</a> {
<a name="L226" href="source/net/ipv4/fib_rules.c#L226">226</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = rule-&gt;fr_net;
<a name="L227" href="source/net/ipv4/fib_rules.c#L227">227</a>         int <a href="ident?i=err">err</a>;
<a name="L228" href="source/net/ipv4/fib_rules.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/fib_rules.c#L229">229</a>         <b><i>/* split local/main if they are not already split */</i></b>
<a name="L230" href="source/net/ipv4/fib_rules.c#L230">230</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_unmerge">fib_unmerge</a>(<a href="ident?i=net">net</a>);
<a name="L231" href="source/net/ipv4/fib_rules.c#L231">231</a>         if (<a href="ident?i=err">err</a>)
<a name="L232" href="source/net/ipv4/fib_rules.c#L232">232</a>                 goto errout;
<a name="L233" href="source/net/ipv4/fib_rules.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/fib_rules.c#L234">234</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L235" href="source/net/ipv4/fib_rules.c#L235">235</a>         if (((struct <a href="ident?i=fib4_rule">fib4_rule</a> *)rule)-&gt;tclassid)
<a name="L236" href="source/net/ipv4/fib_rules.c#L236">236</a>                 <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>--;
<a name="L237" href="source/net/ipv4/fib_rules.c#L237">237</a> #endif
<a name="L238" href="source/net/ipv4/fib_rules.c#L238">238</a>         <a href="ident?i=net">net</a>-&gt;ipv4.fib_has_custom_rules = <a href="ident?i=true">true</a>;
<a name="L239" href="source/net/ipv4/fib_rules.c#L239">239</a>         <a href="ident?i=fib_flush_external">fib_flush_external</a>(rule-&gt;fr_net);
<a name="L240" href="source/net/ipv4/fib_rules.c#L240">240</a> errout:
<a name="L241" href="source/net/ipv4/fib_rules.c#L241">241</a>         return <a href="ident?i=err">err</a>;
<a name="L242" href="source/net/ipv4/fib_rules.c#L242">242</a> }
<a name="L243" href="source/net/ipv4/fib_rules.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/fib_rules.c#L244">244</a> static int <a href="ident?i=fib4_rule_compare">fib4_rule_compare</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=fib_rule_hdr">fib_rule_hdr</a> *frh,
<a name="L245" href="source/net/ipv4/fib_rules.c#L245">245</a>                              struct <a href="ident?i=nlattr">nlattr</a> **<a href="ident?i=tb">tb</a>)
<a name="L246" href="source/net/ipv4/fib_rules.c#L246">246</a> {
<a name="L247" href="source/net/ipv4/fib_rules.c#L247">247</a>         struct <a href="ident?i=fib4_rule">fib4_rule</a> *rule4 = (struct <a href="ident?i=fib4_rule">fib4_rule</a> *) rule;
<a name="L248" href="source/net/ipv4/fib_rules.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/fib_rules.c#L249">249</a>         if (frh-&gt;src_len &amp;&amp; (rule4-&gt;src_len != frh-&gt;src_len))
<a name="L250" href="source/net/ipv4/fib_rules.c#L250">250</a>                 return 0;
<a name="L251" href="source/net/ipv4/fib_rules.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/fib_rules.c#L252">252</a>         if (frh-&gt;dst_len &amp;&amp; (rule4-&gt;dst_len != frh-&gt;dst_len))
<a name="L253" href="source/net/ipv4/fib_rules.c#L253">253</a>                 return 0;
<a name="L254" href="source/net/ipv4/fib_rules.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/fib_rules.c#L255">255</a>         if (frh-&gt;tos &amp;&amp; (rule4-&gt;tos != frh-&gt;tos))
<a name="L256" href="source/net/ipv4/fib_rules.c#L256">256</a>                 return 0;
<a name="L257" href="source/net/ipv4/fib_rules.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/fib_rules.c#L258">258</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L259" href="source/net/ipv4/fib_rules.c#L259">259</a>         if (<a href="ident?i=tb">tb</a>[FRA_FLOW] &amp;&amp; (rule4-&gt;tclassid != <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=tb">tb</a>[FRA_FLOW])))
<a name="L260" href="source/net/ipv4/fib_rules.c#L260">260</a>                 return 0;
<a name="L261" href="source/net/ipv4/fib_rules.c#L261">261</a> #endif
<a name="L262" href="source/net/ipv4/fib_rules.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/fib_rules.c#L263">263</a>         if (frh-&gt;src_len &amp;&amp; (rule4-&gt;<a href="ident?i=src">src</a> != <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[FRA_SRC])))
<a name="L264" href="source/net/ipv4/fib_rules.c#L264">264</a>                 return 0;
<a name="L265" href="source/net/ipv4/fib_rules.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/fib_rules.c#L266">266</a>         if (frh-&gt;dst_len &amp;&amp; (rule4-&gt;<a href="ident?i=dst">dst</a> != <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[FRA_DST])))
<a name="L267" href="source/net/ipv4/fib_rules.c#L267">267</a>                 return 0;
<a name="L268" href="source/net/ipv4/fib_rules.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/fib_rules.c#L269">269</a>         return 1;
<a name="L270" href="source/net/ipv4/fib_rules.c#L270">270</a> }
<a name="L271" href="source/net/ipv4/fib_rules.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/fib_rules.c#L272">272</a> static int <a href="ident?i=fib4_rule_fill">fib4_rule_fill</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L273" href="source/net/ipv4/fib_rules.c#L273">273</a>                           struct <a href="ident?i=fib_rule_hdr">fib_rule_hdr</a> *frh)
<a name="L274" href="source/net/ipv4/fib_rules.c#L274">274</a> {
<a name="L275" href="source/net/ipv4/fib_rules.c#L275">275</a>         struct <a href="ident?i=fib4_rule">fib4_rule</a> *rule4 = (struct <a href="ident?i=fib4_rule">fib4_rule</a> *) rule;
<a name="L276" href="source/net/ipv4/fib_rules.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/fib_rules.c#L277">277</a>         frh-&gt;dst_len = rule4-&gt;dst_len;
<a name="L278" href="source/net/ipv4/fib_rules.c#L278">278</a>         frh-&gt;src_len = rule4-&gt;src_len;
<a name="L279" href="source/net/ipv4/fib_rules.c#L279">279</a>         frh-&gt;tos = rule4-&gt;tos;
<a name="L280" href="source/net/ipv4/fib_rules.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/fib_rules.c#L281">281</a>         if ((rule4-&gt;dst_len &amp;&amp;
<a name="L282" href="source/net/ipv4/fib_rules.c#L282">282</a>              <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, FRA_DST, rule4-&gt;<a href="ident?i=dst">dst</a>)) ||
<a name="L283" href="source/net/ipv4/fib_rules.c#L283">283</a>             (rule4-&gt;src_len &amp;&amp;
<a name="L284" href="source/net/ipv4/fib_rules.c#L284">284</a>              <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, FRA_SRC, rule4-&gt;<a href="ident?i=src">src</a>)))
<a name="L285" href="source/net/ipv4/fib_rules.c#L285">285</a>                 goto nla_put_failure;
<a name="L286" href="source/net/ipv4/fib_rules.c#L286">286</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L287" href="source/net/ipv4/fib_rules.c#L287">287</a>         if (rule4-&gt;tclassid &amp;&amp;
<a name="L288" href="source/net/ipv4/fib_rules.c#L288">288</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, FRA_FLOW, rule4-&gt;tclassid))
<a name="L289" href="source/net/ipv4/fib_rules.c#L289">289</a>                 goto nla_put_failure;
<a name="L290" href="source/net/ipv4/fib_rules.c#L290">290</a> #endif
<a name="L291" href="source/net/ipv4/fib_rules.c#L291">291</a>         return 0;
<a name="L292" href="source/net/ipv4/fib_rules.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/fib_rules.c#L293">293</a> nla_put_failure:
<a name="L294" href="source/net/ipv4/fib_rules.c#L294">294</a>         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L295" href="source/net/ipv4/fib_rules.c#L295">295</a> }
<a name="L296" href="source/net/ipv4/fib_rules.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/fib_rules.c#L297">297</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=fib4_rule_nlmsg_payload">fib4_rule_nlmsg_payload</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule)
<a name="L298" href="source/net/ipv4/fib_rules.c#L298">298</a> {
<a name="L299" href="source/net/ipv4/fib_rules.c#L299">299</a>         return <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* dst */</i></b>
<a name="L300" href="source/net/ipv4/fib_rules.c#L300">300</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* src */</i></b>
<a name="L301" href="source/net/ipv4/fib_rules.c#L301">301</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(4); <b><i>/* flow */</i></b>
<a name="L302" href="source/net/ipv4/fib_rules.c#L302">302</a> }
<a name="L303" href="source/net/ipv4/fib_rules.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/fib_rules.c#L304">304</a> static void <a href="ident?i=fib4_rule_flush_cache">fib4_rule_flush_cache</a>(struct <a href="ident?i=fib_rules_ops">fib_rules_ops</a> *<a href="ident?i=ops">ops</a>)
<a name="L305" href="source/net/ipv4/fib_rules.c#L305">305</a> {
<a name="L306" href="source/net/ipv4/fib_rules.c#L306">306</a>         <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=ops">ops</a>-&gt;fro_net);
<a name="L307" href="source/net/ipv4/fib_rules.c#L307">307</a> }
<a name="L308" href="source/net/ipv4/fib_rules.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/fib_rules.c#L309">309</a> static const struct <a href="ident?i=fib_rules_ops">fib_rules_ops</a> <a href="ident?i=__net_initconst">__net_initconst</a> <a href="ident?i=fib4_rules_ops_template">fib4_rules_ops_template</a> = {
<a name="L310" href="source/net/ipv4/fib_rules.c#L310">310</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L311" href="source/net/ipv4/fib_rules.c#L311">311</a>         .rule_size      = sizeof(struct <a href="ident?i=fib4_rule">fib4_rule</a>),
<a name="L312" href="source/net/ipv4/fib_rules.c#L312">312</a>         .addr_size      = sizeof(<a href="ident?i=u32">u32</a>),
<a name="L313" href="source/net/ipv4/fib_rules.c#L313">313</a>         .<a href="ident?i=action">action</a>         = <a href="ident?i=fib4_rule_action">fib4_rule_action</a>,
<a name="L314" href="source/net/ipv4/fib_rules.c#L314">314</a>         .suppress       = <a href="ident?i=fib4_rule_suppress">fib4_rule_suppress</a>,
<a name="L315" href="source/net/ipv4/fib_rules.c#L315">315</a>         .<a href="ident?i=match">match</a>          = <a href="ident?i=fib4_rule_match">fib4_rule_match</a>,
<a name="L316" href="source/net/ipv4/fib_rules.c#L316">316</a>         .<a href="ident?i=configure">configure</a>      = <a href="ident?i=fib4_rule_configure">fib4_rule_configure</a>,
<a name="L317" href="source/net/ipv4/fib_rules.c#L317">317</a>         .delete         = <a href="ident?i=fib4_rule_delete">fib4_rule_delete</a>,
<a name="L318" href="source/net/ipv4/fib_rules.c#L318">318</a>         .<a href="ident?i=compare">compare</a>        = <a href="ident?i=fib4_rule_compare">fib4_rule_compare</a>,
<a name="L319" href="source/net/ipv4/fib_rules.c#L319">319</a>         .<a href="ident?i=fill">fill</a>           = <a href="ident?i=fib4_rule_fill">fib4_rule_fill</a>,
<a name="L320" href="source/net/ipv4/fib_rules.c#L320">320</a>         .default_pref   = <a href="ident?i=fib_default_rule_pref">fib_default_rule_pref</a>,
<a name="L321" href="source/net/ipv4/fib_rules.c#L321">321</a>         .nlmsg_payload  = <a href="ident?i=fib4_rule_nlmsg_payload">fib4_rule_nlmsg_payload</a>,
<a name="L322" href="source/net/ipv4/fib_rules.c#L322">322</a>         .<a href="ident?i=flush_cache">flush_cache</a>    = <a href="ident?i=fib4_rule_flush_cache">fib4_rule_flush_cache</a>,
<a name="L323" href="source/net/ipv4/fib_rules.c#L323">323</a>         .nlgroup        = <a href="ident?i=RTNLGRP_IPV4_RULE">RTNLGRP_IPV4_RULE</a>,
<a name="L324" href="source/net/ipv4/fib_rules.c#L324">324</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=fib4_rule_policy">fib4_rule_policy</a>,
<a name="L325" href="source/net/ipv4/fib_rules.c#L325">325</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L326" href="source/net/ipv4/fib_rules.c#L326">326</a> };
<a name="L327" href="source/net/ipv4/fib_rules.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/fib_rules.c#L328">328</a> static int <a href="ident?i=fib_default_rules_init">fib_default_rules_init</a>(struct <a href="ident?i=fib_rules_ops">fib_rules_ops</a> *<a href="ident?i=ops">ops</a>)
<a name="L329" href="source/net/ipv4/fib_rules.c#L329">329</a> {
<a name="L330" href="source/net/ipv4/fib_rules.c#L330">330</a>         int <a href="ident?i=err">err</a>;
<a name="L331" href="source/net/ipv4/fib_rules.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/fib_rules.c#L332">332</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_default_rule_add">fib_default_rule_add</a>(<a href="ident?i=ops">ops</a>, 0, RT_TABLE_LOCAL, 0);
<a name="L333" href="source/net/ipv4/fib_rules.c#L333">333</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L334" href="source/net/ipv4/fib_rules.c#L334">334</a>                 return <a href="ident?i=err">err</a>;
<a name="L335" href="source/net/ipv4/fib_rules.c#L335">335</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_default_rule_add">fib_default_rule_add</a>(<a href="ident?i=ops">ops</a>, 0x7FFE, RT_TABLE_MAIN, 0);
<a name="L336" href="source/net/ipv4/fib_rules.c#L336">336</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L337" href="source/net/ipv4/fib_rules.c#L337">337</a>                 return <a href="ident?i=err">err</a>;
<a name="L338" href="source/net/ipv4/fib_rules.c#L338">338</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_default_rule_add">fib_default_rule_add</a>(<a href="ident?i=ops">ops</a>, 0x7FFF, RT_TABLE_DEFAULT, 0);
<a name="L339" href="source/net/ipv4/fib_rules.c#L339">339</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L340" href="source/net/ipv4/fib_rules.c#L340">340</a>                 return <a href="ident?i=err">err</a>;
<a name="L341" href="source/net/ipv4/fib_rules.c#L341">341</a>         return 0;
<a name="L342" href="source/net/ipv4/fib_rules.c#L342">342</a> }
<a name="L343" href="source/net/ipv4/fib_rules.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/fib_rules.c#L344">344</a> int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=fib4_rules_init">fib4_rules_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L345" href="source/net/ipv4/fib_rules.c#L345">345</a> {
<a name="L346" href="source/net/ipv4/fib_rules.c#L346">346</a>         int <a href="ident?i=err">err</a>;
<a name="L347" href="source/net/ipv4/fib_rules.c#L347">347</a>         struct <a href="ident?i=fib_rules_ops">fib_rules_ops</a> *<a href="ident?i=ops">ops</a>;
<a name="L348" href="source/net/ipv4/fib_rules.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/fib_rules.c#L349">349</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=fib_rules_register">fib_rules_register</a>(&amp;<a href="ident?i=fib4_rules_ops_template">fib4_rules_ops_template</a>, <a href="ident?i=net">net</a>);
<a name="L350" href="source/net/ipv4/fib_rules.c#L350">350</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=ops">ops</a>))
<a name="L351" href="source/net/ipv4/fib_rules.c#L351">351</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=ops">ops</a>);
<a name="L352" href="source/net/ipv4/fib_rules.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/fib_rules.c#L353">353</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_default_rules_init">fib_default_rules_init</a>(<a href="ident?i=ops">ops</a>);
<a name="L354" href="source/net/ipv4/fib_rules.c#L354">354</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L355" href="source/net/ipv4/fib_rules.c#L355">355</a>                 goto <a href="ident?i=fail">fail</a>;
<a name="L356" href="source/net/ipv4/fib_rules.c#L356">356</a>         <a href="ident?i=net">net</a>-&gt;ipv4.rules_ops = <a href="ident?i=ops">ops</a>;
<a name="L357" href="source/net/ipv4/fib_rules.c#L357">357</a>         <a href="ident?i=net">net</a>-&gt;ipv4.fib_has_custom_rules = <a href="ident?i=false">false</a>;
<a name="L358" href="source/net/ipv4/fib_rules.c#L358">358</a>         return 0;
<a name="L359" href="source/net/ipv4/fib_rules.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/fib_rules.c#L360">360</a> <a href="ident?i=fail">fail</a>:
<a name="L361" href="source/net/ipv4/fib_rules.c#L361">361</a>         <b><i>/* also cleans all rules already added */</i></b>
<a name="L362" href="source/net/ipv4/fib_rules.c#L362">362</a>         <a href="ident?i=fib_rules_unregister">fib_rules_unregister</a>(<a href="ident?i=ops">ops</a>);
<a name="L363" href="source/net/ipv4/fib_rules.c#L363">363</a>         return <a href="ident?i=err">err</a>;
<a name="L364" href="source/net/ipv4/fib_rules.c#L364">364</a> }
<a name="L365" href="source/net/ipv4/fib_rules.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/fib_rules.c#L366">366</a> void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=fib4_rules_exit">fib4_rules_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L367" href="source/net/ipv4/fib_rules.c#L367">367</a> {
<a name="L368" href="source/net/ipv4/fib_rules.c#L368">368</a>         <a href="ident?i=fib_rules_unregister">fib_rules_unregister</a>(<a href="ident?i=net">net</a>-&gt;ipv4.rules_ops);
<a name="L369" href="source/net/ipv4/fib_rules.c#L369">369</a> }
<a name="L370" href="source/net/ipv4/fib_rules.c#L370">370</a> </pre></div><p>
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
