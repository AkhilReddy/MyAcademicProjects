<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/devinet.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/devinet.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/devinet.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/devinet.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/devinet.c">devinet.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/devinet.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/devinet.c#L2">2</a> <b><i> *      NET3    IP device support routines.</i></b>
  <a name="L3" href="source/net/ipv4/devinet.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/devinet.c#L4">4</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
  <a name="L5" href="source/net/ipv4/devinet.c#L5">5</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
  <a name="L6" href="source/net/ipv4/devinet.c#L6">6</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
  <a name="L7" href="source/net/ipv4/devinet.c#L7">7</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
  <a name="L8" href="source/net/ipv4/devinet.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/devinet.c#L9">9</a> <b><i> *      Derived from the IP parts of dev.c 1.0.19</i></b>
 <a name="L10" href="source/net/ipv4/devinet.c#L10">10</a> <b><i> *              Authors:        Ross Biro</i></b>
 <a name="L11" href="source/net/ipv4/devinet.c#L11">11</a> <b><i> *                              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L12" href="source/net/ipv4/devinet.c#L12">12</a> <b><i> *                              Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;</i></b>
 <a name="L13" href="source/net/ipv4/devinet.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/devinet.c#L14">14</a> <b><i> *      Additional Authors:</i></b>
 <a name="L15" href="source/net/ipv4/devinet.c#L15">15</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L16" href="source/net/ipv4/devinet.c#L16">16</a> <b><i> *              Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
 <a name="L17" href="source/net/ipv4/devinet.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/devinet.c#L18">18</a> <b><i> *      Changes:</i></b>
 <a name="L19" href="source/net/ipv4/devinet.c#L19">19</a> <b><i> *              Alexey Kuznetsov:       pa_* fields are replaced with ifaddr</i></b>
 <a name="L20" href="source/net/ipv4/devinet.c#L20">20</a> <b><i> *                                      lists.</i></b>
 <a name="L21" href="source/net/ipv4/devinet.c#L21">21</a> <b><i> *              Cyrus Durgin:           updated for kmod</i></b>
 <a name="L22" href="source/net/ipv4/devinet.c#L22">22</a> <b><i> *              Matthias Andree:        in devinet_ioctl, compare label and</i></b>
 <a name="L23" href="source/net/ipv4/devinet.c#L23">23</a> <b><i> *                                      address (4.4BSD alias style support),</i></b>
 <a name="L24" href="source/net/ipv4/devinet.c#L24">24</a> <b><i> *                                      fall back to comparing just the label</i></b>
 <a name="L25" href="source/net/ipv4/devinet.c#L25">25</a> <b><i> *                                      if no match found.</i></b>
 <a name="L26" href="source/net/ipv4/devinet.c#L26">26</a> <b><i> */</i></b>
 <a name="L27" href="source/net/ipv4/devinet.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/devinet.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/devinet.c#L29">29</a> #include &lt;asm/uaccess.h&gt;
 <a name="L30" href="source/net/ipv4/devinet.c#L30">30</a> #include &lt;linux/bitops.h&gt;
 <a name="L31" href="source/net/ipv4/devinet.c#L31">31</a> #include &lt;linux/capability.h&gt;
 <a name="L32" href="source/net/ipv4/devinet.c#L32">32</a> #include &lt;linux/module.h&gt;
 <a name="L33" href="source/net/ipv4/devinet.c#L33">33</a> #include &lt;linux/types.h&gt;
 <a name="L34" href="source/net/ipv4/devinet.c#L34">34</a> #include &lt;linux/kernel.h&gt;
 <a name="L35" href="source/net/ipv4/devinet.c#L35">35</a> #include &lt;linux/string.h&gt;
 <a name="L36" href="source/net/ipv4/devinet.c#L36">36</a> #include &lt;linux/mm.h&gt;
 <a name="L37" href="source/net/ipv4/devinet.c#L37">37</a> #include &lt;linux/socket.h&gt;
 <a name="L38" href="source/net/ipv4/devinet.c#L38">38</a> #include &lt;linux/sockios.h&gt;
 <a name="L39" href="source/net/ipv4/devinet.c#L39">39</a> #include &lt;linux/in.h&gt;
 <a name="L40" href="source/net/ipv4/devinet.c#L40">40</a> #include &lt;linux/errno.h&gt;
 <a name="L41" href="source/net/ipv4/devinet.c#L41">41</a> #include &lt;linux/interrupt.h&gt;
 <a name="L42" href="source/net/ipv4/devinet.c#L42">42</a> #include &lt;linux/if_addr.h&gt;
 <a name="L43" href="source/net/ipv4/devinet.c#L43">43</a> #include &lt;linux/if_ether.h&gt;
 <a name="L44" href="source/net/ipv4/devinet.c#L44">44</a> #include &lt;linux/inet.h&gt;
 <a name="L45" href="source/net/ipv4/devinet.c#L45">45</a> #include &lt;linux/netdevice.h&gt;
 <a name="L46" href="source/net/ipv4/devinet.c#L46">46</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L47" href="source/net/ipv4/devinet.c#L47">47</a> #include &lt;linux/skbuff.h&gt;
 <a name="L48" href="source/net/ipv4/devinet.c#L48">48</a> #include &lt;linux/init.h&gt;
 <a name="L49" href="source/net/ipv4/devinet.c#L49">49</a> #include &lt;linux/notifier.h&gt;
 <a name="L50" href="source/net/ipv4/devinet.c#L50">50</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L51" href="source/net/ipv4/devinet.c#L51">51</a> #include &lt;linux/igmp.h&gt;
 <a name="L52" href="source/net/ipv4/devinet.c#L52">52</a> #include &lt;linux/slab.h&gt;
 <a name="L53" href="source/net/ipv4/devinet.c#L53">53</a> #include &lt;linux/hash.h&gt;
 <a name="L54" href="source/net/ipv4/devinet.c#L54">54</a> #ifdef CONFIG_SYSCTL
 <a name="L55" href="source/net/ipv4/devinet.c#L55">55</a> #include &lt;linux/sysctl.h&gt;
 <a name="L56" href="source/net/ipv4/devinet.c#L56">56</a> #endif
 <a name="L57" href="source/net/ipv4/devinet.c#L57">57</a> #include &lt;linux/kmod.h&gt;
 <a name="L58" href="source/net/ipv4/devinet.c#L58">58</a> #include &lt;linux/netconf.h&gt;
 <a name="L59" href="source/net/ipv4/devinet.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/devinet.c#L60">60</a> #include &lt;net/arp.h&gt;
 <a name="L61" href="source/net/ipv4/devinet.c#L61">61</a> #include &lt;net/ip.h&gt;
 <a name="L62" href="source/net/ipv4/devinet.c#L62">62</a> #include &lt;net/route.h&gt;
 <a name="L63" href="source/net/ipv4/devinet.c#L63">63</a> #include &lt;net/ip_fib.h&gt;
 <a name="L64" href="source/net/ipv4/devinet.c#L64">64</a> #include &lt;net/rtnetlink.h&gt;
 <a name="L65" href="source/net/ipv4/devinet.c#L65">65</a> #include &lt;net/net_namespace.h&gt;
 <a name="L66" href="source/net/ipv4/devinet.c#L66">66</a> #include &lt;net/addrconf.h&gt;
 <a name="L67" href="source/net/ipv4/devinet.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/devinet.c#L68">68</a> #include "<a href="source/net/ipv4/fib_lookup.h">fib_lookup.h</a>"
 <a name="L69" href="source/net/ipv4/devinet.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/devinet.c#L70">70</a> static struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> <a href="ident?i=ipv4_devconf">ipv4_devconf</a> = {
 <a name="L71" href="source/net/ipv4/devinet.c#L71">71</a>         .<a href="ident?i=data">data</a> = {
 <a name="L72" href="source/net/ipv4/devinet.c#L72">72</a>                 [IPV4_DEVCONF_ACCEPT_REDIRECTS - 1] = 1,
 <a name="L73" href="source/net/ipv4/devinet.c#L73">73</a>                 [IPV4_DEVCONF_SEND_REDIRECTS - 1] = 1,
 <a name="L74" href="source/net/ipv4/devinet.c#L74">74</a>                 [IPV4_DEVCONF_SECURE_REDIRECTS - 1] = 1,
 <a name="L75" href="source/net/ipv4/devinet.c#L75">75</a>                 [IPV4_DEVCONF_SHARED_MEDIA - 1] = 1,
 <a name="L76" href="source/net/ipv4/devinet.c#L76">76</a>                 [IPV4_DEVCONF_IGMPV2_UNSOLICITED_REPORT_INTERVAL - 1] = 10000 <b><i>/*ms*/</i></b>,
 <a name="L77" href="source/net/ipv4/devinet.c#L77">77</a>                 [IPV4_DEVCONF_IGMPV3_UNSOLICITED_REPORT_INTERVAL - 1] =  1000 <b><i>/*ms*/</i></b>,
 <a name="L78" href="source/net/ipv4/devinet.c#L78">78</a>         },
 <a name="L79" href="source/net/ipv4/devinet.c#L79">79</a> };
 <a name="L80" href="source/net/ipv4/devinet.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/devinet.c#L81">81</a> static struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> <a href="ident?i=ipv4_devconf_dflt">ipv4_devconf_dflt</a> = {
 <a name="L82" href="source/net/ipv4/devinet.c#L82">82</a>         .<a href="ident?i=data">data</a> = {
 <a name="L83" href="source/net/ipv4/devinet.c#L83">83</a>                 [IPV4_DEVCONF_ACCEPT_REDIRECTS - 1] = 1,
 <a name="L84" href="source/net/ipv4/devinet.c#L84">84</a>                 [IPV4_DEVCONF_SEND_REDIRECTS - 1] = 1,
 <a name="L85" href="source/net/ipv4/devinet.c#L85">85</a>                 [IPV4_DEVCONF_SECURE_REDIRECTS - 1] = 1,
 <a name="L86" href="source/net/ipv4/devinet.c#L86">86</a>                 [IPV4_DEVCONF_SHARED_MEDIA - 1] = 1,
 <a name="L87" href="source/net/ipv4/devinet.c#L87">87</a>                 [IPV4_DEVCONF_ACCEPT_SOURCE_ROUTE - 1] = 1,
 <a name="L88" href="source/net/ipv4/devinet.c#L88">88</a>                 [IPV4_DEVCONF_IGMPV2_UNSOLICITED_REPORT_INTERVAL - 1] = 10000 <b><i>/*ms*/</i></b>,
 <a name="L89" href="source/net/ipv4/devinet.c#L89">89</a>                 [IPV4_DEVCONF_IGMPV3_UNSOLICITED_REPORT_INTERVAL - 1] =  1000 <b><i>/*ms*/</i></b>,
 <a name="L90" href="source/net/ipv4/devinet.c#L90">90</a>         },
 <a name="L91" href="source/net/ipv4/devinet.c#L91">91</a> };
 <a name="L92" href="source/net/ipv4/devinet.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/devinet.c#L93">93</a> #define <a href="ident?i=IPV4_DEVCONF_DFLT">IPV4_DEVCONF_DFLT</a>(<a href="ident?i=net">net</a>, <a href="ident?i=attr">attr</a>) \
 <a name="L94" href="source/net/ipv4/devinet.c#L94">94</a>         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>((*<a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt), <a href="ident?i=attr">attr</a>)
 <a name="L95" href="source/net/ipv4/devinet.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/devinet.c#L96">96</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=ifa_ipv4_policy">ifa_ipv4_policy</a>[<a href="ident?i=IFA_MAX">IFA_MAX</a>+1] = {
 <a name="L97" href="source/net/ipv4/devinet.c#L97">97</a>         [IFA_LOCAL]             = { .<a href="ident?i=type">type</a> = NLA_U32 },
 <a name="L98" href="source/net/ipv4/devinet.c#L98">98</a>         [IFA_ADDRESS]           = { .<a href="ident?i=type">type</a> = NLA_U32 },
 <a name="L99" href="source/net/ipv4/devinet.c#L99">99</a>         [IFA_BROADCAST]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L100" href="source/net/ipv4/devinet.c#L100">100</a>         [IFA_LABEL]             = { .<a href="ident?i=type">type</a> = NLA_STRING, .<a href="ident?i=len">len</a> = <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a> - 1 },
<a name="L101" href="source/net/ipv4/devinet.c#L101">101</a>         [IFA_CACHEINFO]         = { .<a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=ifa_cacheinfo">ifa_cacheinfo</a>) },
<a name="L102" href="source/net/ipv4/devinet.c#L102">102</a>         [IFA_FLAGS]             = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L103" href="source/net/ipv4/devinet.c#L103">103</a> };
<a name="L104" href="source/net/ipv4/devinet.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/devinet.c#L105">105</a> #define <a href="ident?i=IN4_ADDR_HSIZE_SHIFT">IN4_ADDR_HSIZE_SHIFT</a>    8
<a name="L106" href="source/net/ipv4/devinet.c#L106">106</a> #define <a href="ident?i=IN4_ADDR_HSIZE">IN4_ADDR_HSIZE</a>          (1U &lt;&lt; <a href="ident?i=IN4_ADDR_HSIZE_SHIFT">IN4_ADDR_HSIZE_SHIFT</a>)
<a name="L107" href="source/net/ipv4/devinet.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/devinet.c#L108">108</a> static struct <a href="ident?i=hlist_head">hlist_head</a> <a href="ident?i=inet_addr_lst">inet_addr_lst</a>[<a href="ident?i=IN4_ADDR_HSIZE">IN4_ADDR_HSIZE</a>];
<a name="L109" href="source/net/ipv4/devinet.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/devinet.c#L110">110</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=inet_addr_hash">inet_addr_hash</a>(const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L111" href="source/net/ipv4/devinet.c#L111">111</a> {
<a name="L112" href="source/net/ipv4/devinet.c#L112">112</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a> = (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>) <a href="ident?i=addr">addr</a> ^ <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>);
<a name="L113" href="source/net/ipv4/devinet.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/devinet.c#L114">114</a>         return <a href="ident?i=hash_32">hash_32</a>(<a href="ident?i=val">val</a>, <a href="ident?i=IN4_ADDR_HSIZE_SHIFT">IN4_ADDR_HSIZE_SHIFT</a>);
<a name="L115" href="source/net/ipv4/devinet.c#L115">115</a> }
<a name="L116" href="source/net/ipv4/devinet.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/devinet.c#L117">117</a> static void <a href="ident?i=inet_hash_insert">inet_hash_insert</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L118" href="source/net/ipv4/devinet.c#L118">118</a> {
<a name="L119" href="source/net/ipv4/devinet.c#L119">119</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_addr_hash">inet_addr_hash</a>(<a href="ident?i=net">net</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_local);
<a name="L120" href="source/net/ipv4/devinet.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/devinet.c#L121">121</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L122" href="source/net/ipv4/devinet.c#L122">122</a>         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;<a href="ident?i=ifa">ifa</a>-&gt;<a href="ident?i=hash">hash</a>, &amp;<a href="ident?i=inet_addr_lst">inet_addr_lst</a>[<a href="ident?i=hash">hash</a>]);
<a name="L123" href="source/net/ipv4/devinet.c#L123">123</a> }
<a name="L124" href="source/net/ipv4/devinet.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/devinet.c#L125">125</a> static void <a href="ident?i=inet_hash_remove">inet_hash_remove</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L126" href="source/net/ipv4/devinet.c#L126">126</a> {
<a name="L127" href="source/net/ipv4/devinet.c#L127">127</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L128" href="source/net/ipv4/devinet.c#L128">128</a>         <a href="ident?i=hlist_del_init_rcu">hlist_del_init_rcu</a>(&amp;<a href="ident?i=ifa">ifa</a>-&gt;<a href="ident?i=hash">hash</a>);
<a name="L129" href="source/net/ipv4/devinet.c#L129">129</a> }
<a name="L130" href="source/net/ipv4/devinet.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/devinet.c#L131">131</a> <b><i>/**</i></b>
<a name="L132" href="source/net/ipv4/devinet.c#L132">132</a> <b><i> * __ip_dev_find - find the first device with a given source address.</i></b>
<a name="L133" href="source/net/ipv4/devinet.c#L133">133</a> <b><i> * @net: the net namespace</i></b>
<a name="L134" href="source/net/ipv4/devinet.c#L134">134</a> <b><i> * @addr: the source address</i></b>
<a name="L135" href="source/net/ipv4/devinet.c#L135">135</a> <b><i> * @devref: if true, take a reference on the found device</i></b>
<a name="L136" href="source/net/ipv4/devinet.c#L136">136</a> <b><i> *</i></b>
<a name="L137" href="source/net/ipv4/devinet.c#L137">137</a> <b><i> * If a caller uses devref=false, it should be protected by RCU, or RTNL</i></b>
<a name="L138" href="source/net/ipv4/devinet.c#L138">138</a> <b><i> */</i></b>
<a name="L139" href="source/net/ipv4/devinet.c#L139">139</a> struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=__ip_dev_find">__ip_dev_find</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>, <a href="ident?i=bool">bool</a> devref)
<a name="L140" href="source/net/ipv4/devinet.c#L140">140</a> {
<a name="L141" href="source/net/ipv4/devinet.c#L141">141</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_addr_hash">inet_addr_hash</a>(<a href="ident?i=net">net</a>, <a href="ident?i=addr">addr</a>);
<a name="L142" href="source/net/ipv4/devinet.c#L142">142</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L143" href="source/net/ipv4/devinet.c#L143">143</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L144" href="source/net/ipv4/devinet.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/devinet.c#L145">145</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L146" href="source/net/ipv4/devinet.c#L146">146</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=ifa">ifa</a>, &amp;<a href="ident?i=inet_addr_lst">inet_addr_lst</a>[<a href="ident?i=hash">hash</a>], <a href="ident?i=hash">hash</a>) {
<a name="L147" href="source/net/ipv4/devinet.c#L147">147</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_local == <a href="ident?i=addr">addr</a>) {
<a name="L148" href="source/net/ipv4/devinet.c#L148">148</a>                         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L149" href="source/net/ipv4/devinet.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/devinet.c#L150">150</a>                         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), <a href="ident?i=net">net</a>))
<a name="L151" href="source/net/ipv4/devinet.c#L151">151</a>                                 continue;
<a name="L152" href="source/net/ipv4/devinet.c#L152">152</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=dev">dev</a>;
<a name="L153" href="source/net/ipv4/devinet.c#L153">153</a>                         break;
<a name="L154" href="source/net/ipv4/devinet.c#L154">154</a>                 }
<a name="L155" href="source/net/ipv4/devinet.c#L155">155</a>         }
<a name="L156" href="source/net/ipv4/devinet.c#L156">156</a>         if (!<a href="ident?i=result">result</a>) {
<a name="L157" href="source/net/ipv4/devinet.c#L157">157</a>                 struct <a href="ident?i=flowi4">flowi4</a> fl4 = { .<a href="ident?i=daddr">daddr</a> = <a href="ident?i=addr">addr</a> };
<a name="L158" href="source/net/ipv4/devinet.c#L158">158</a>                 struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a> = { 0 };
<a name="L159" href="source/net/ipv4/devinet.c#L159">159</a>                 struct <a href="ident?i=fib_table">fib_table</a> *local;
<a name="L160" href="source/net/ipv4/devinet.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/devinet.c#L161">161</a>                 <b><i>/* Fallback to FIB local table so that communication</i></b>
<a name="L162" href="source/net/ipv4/devinet.c#L162">162</a> <b><i>                 * over loopback subnets work.</i></b>
<a name="L163" href="source/net/ipv4/devinet.c#L163">163</a> <b><i>                 */</i></b>
<a name="L164" href="source/net/ipv4/devinet.c#L164">164</a>                 local = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_LOCAL);
<a name="L165" href="source/net/ipv4/devinet.c#L165">165</a>                 if (local &amp;&amp;
<a name="L166" href="source/net/ipv4/devinet.c#L166">166</a>                     !<a href="ident?i=fib_table_lookup">fib_table_lookup</a>(local, &amp;fl4, &amp;<a href="ident?i=res">res</a>, <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>) &amp;&amp;
<a name="L167" href="source/net/ipv4/devinet.c#L167">167</a>                     <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_LOCAL)
<a name="L168" href="source/net/ipv4/devinet.c#L168">168</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=FIB_RES_DEV">FIB_RES_DEV</a>(<a href="ident?i=res">res</a>);
<a name="L169" href="source/net/ipv4/devinet.c#L169">169</a>         }
<a name="L170" href="source/net/ipv4/devinet.c#L170">170</a>         if (<a href="ident?i=result">result</a> &amp;&amp; devref)
<a name="L171" href="source/net/ipv4/devinet.c#L171">171</a>                 <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=result">result</a>);
<a name="L172" href="source/net/ipv4/devinet.c#L172">172</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L173" href="source/net/ipv4/devinet.c#L173">173</a>         return <a href="ident?i=result">result</a>;
<a name="L174" href="source/net/ipv4/devinet.c#L174">174</a> }
<a name="L175" href="source/net/ipv4/devinet.c#L175">175</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=__ip_dev_find">__ip_dev_find</a>);
<a name="L176" href="source/net/ipv4/devinet.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/devinet.c#L177">177</a> static void <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(int <a href="ident?i=event">event</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *, <a href="ident?i=u32">u32</a>);
<a name="L178" href="source/net/ipv4/devinet.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/devinet.c#L179">179</a> static <a href="ident?i=BLOCKING_NOTIFIER_HEAD">BLOCKING_NOTIFIER_HEAD</a>(inetaddr_chain);
<a name="L180" href="source/net/ipv4/devinet.c#L180">180</a> static void <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> **ifap,
<a name="L181" href="source/net/ipv4/devinet.c#L181">181</a>                          int <a href="ident?i=destroy">destroy</a>);
<a name="L182" href="source/net/ipv4/devinet.c#L182">182</a> #ifdef CONFIG_SYSCTL
<a name="L183" href="source/net/ipv4/devinet.c#L183">183</a> static int <a href="ident?i=devinet_sysctl_register">devinet_sysctl_register</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>);
<a name="L184" href="source/net/ipv4/devinet.c#L184">184</a> static void <a href="ident?i=devinet_sysctl_unregister">devinet_sysctl_unregister</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>);
<a name="L185" href="source/net/ipv4/devinet.c#L185">185</a> #else
<a name="L186" href="source/net/ipv4/devinet.c#L186">186</a> static int <a href="ident?i=devinet_sysctl_register">devinet_sysctl_register</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>)
<a name="L187" href="source/net/ipv4/devinet.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/devinet.c#L188">188</a>         return 0;
<a name="L189" href="source/net/ipv4/devinet.c#L189">189</a> }
<a name="L190" href="source/net/ipv4/devinet.c#L190">190</a> static void <a href="ident?i=devinet_sysctl_unregister">devinet_sysctl_unregister</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>)
<a name="L191" href="source/net/ipv4/devinet.c#L191">191</a> {
<a name="L192" href="source/net/ipv4/devinet.c#L192">192</a> }
<a name="L193" href="source/net/ipv4/devinet.c#L193">193</a> #endif
<a name="L194" href="source/net/ipv4/devinet.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/devinet.c#L195">195</a> <b><i>/* Locks all the inet devices. */</i></b>
<a name="L196" href="source/net/ipv4/devinet.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/devinet.c#L197">197</a> static struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=inet_alloc_ifa">inet_alloc_ifa</a>(void)
<a name="L198" href="source/net/ipv4/devinet.c#L198">198</a> {
<a name="L199" href="source/net/ipv4/devinet.c#L199">199</a>         return <a href="ident?i=kzalloc">kzalloc</a>(sizeof(struct <a href="ident?i=in_ifaddr">in_ifaddr</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L200" href="source/net/ipv4/devinet.c#L200">200</a> }
<a name="L201" href="source/net/ipv4/devinet.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/devinet.c#L202">202</a> static void <a href="ident?i=inet_rcu_free_ifa">inet_rcu_free_ifa</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L203" href="source/net/ipv4/devinet.c#L203">203</a> {
<a name="L204" href="source/net/ipv4/devinet.c#L204">204</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a>, <a href="ident?i=rcu_head">rcu_head</a>);
<a name="L205" href="source/net/ipv4/devinet.c#L205">205</a>         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev)
<a name="L206" href="source/net/ipv4/devinet.c#L206">206</a>                 <a href="ident?i=in_dev_put">in_dev_put</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev);
<a name="L207" href="source/net/ipv4/devinet.c#L207">207</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L208" href="source/net/ipv4/devinet.c#L208">208</a> }
<a name="L209" href="source/net/ipv4/devinet.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/devinet.c#L210">210</a> static void <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L211" href="source/net/ipv4/devinet.c#L211">211</a> {
<a name="L212" href="source/net/ipv4/devinet.c#L212">212</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=ifa">ifa</a>-&gt;<a href="ident?i=rcu_head">rcu_head</a>, <a href="ident?i=inet_rcu_free_ifa">inet_rcu_free_ifa</a>);
<a name="L213" href="source/net/ipv4/devinet.c#L213">213</a> }
<a name="L214" href="source/net/ipv4/devinet.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/devinet.c#L215">215</a> void <a href="ident?i=in_dev_finish_destroy">in_dev_finish_destroy</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>)
<a name="L216" href="source/net/ipv4/devinet.c#L216">216</a> {
<a name="L217" href="source/net/ipv4/devinet.c#L217">217</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L218" href="source/net/ipv4/devinet.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/devinet.c#L219">219</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=idev">idev</a>-&gt;ifa_list);
<a name="L220" href="source/net/ipv4/devinet.c#L220">220</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=idev">idev</a>-&gt;mc_list);
<a name="L221" href="source/net/ipv4/devinet.c#L221">221</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=mc_hash">mc_hash</a>, 1));
<a name="L222" href="source/net/ipv4/devinet.c#L222">222</a> #ifdef NET_REFCNT_DEBUG
<a name="L223" href="source/net/ipv4/devinet.c#L223">223</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"%s: %p=%s\n"</i>, <a href="ident?i=__func__">__func__</a>, <a href="ident?i=idev">idev</a>, <a href="ident?i=dev">dev</a> ? <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a> : <i>"NIL"</i>);
<a name="L224" href="source/net/ipv4/devinet.c#L224">224</a> #endif
<a name="L225" href="source/net/ipv4/devinet.c#L225">225</a>         <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L226" href="source/net/ipv4/devinet.c#L226">226</a>         if (!<a href="ident?i=idev">idev</a>-&gt;dead)
<a name="L227" href="source/net/ipv4/devinet.c#L227">227</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Freeing alive in_device %p\n"</i>, <a href="ident?i=idev">idev</a>);
<a name="L228" href="source/net/ipv4/devinet.c#L228">228</a>         else
<a name="L229" href="source/net/ipv4/devinet.c#L229">229</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=idev">idev</a>);
<a name="L230" href="source/net/ipv4/devinet.c#L230">230</a> }
<a name="L231" href="source/net/ipv4/devinet.c#L231">231</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=in_dev_finish_destroy">in_dev_finish_destroy</a>);
<a name="L232" href="source/net/ipv4/devinet.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/devinet.c#L233">233</a> static struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=inetdev_init">inetdev_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L234" href="source/net/ipv4/devinet.c#L234">234</a> {
<a name="L235" href="source/net/ipv4/devinet.c#L235">235</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L236" href="source/net/ipv4/devinet.c#L236">236</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L237" href="source/net/ipv4/devinet.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/devinet.c#L238">238</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L239" href="source/net/ipv4/devinet.c#L239">239</a> 
<a name="L240" href="source/net/ipv4/devinet.c#L240">240</a>         in_dev = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*in_dev), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L241" href="source/net/ipv4/devinet.c#L241">241</a>         if (!in_dev)
<a name="L242" href="source/net/ipv4/devinet.c#L242">242</a>                 goto <a href="ident?i=out">out</a>;
<a name="L243" href="source/net/ipv4/devinet.c#L243">243</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;in_dev-&gt;cnf, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>)-&gt;ipv4.devconf_dflt,
<a name="L244" href="source/net/ipv4/devinet.c#L244">244</a>                         sizeof(in_dev-&gt;cnf));
<a name="L245" href="source/net/ipv4/devinet.c#L245">245</a>         in_dev-&gt;cnf.sysctl = <a href="ident?i=NULL">NULL</a>;
<a name="L246" href="source/net/ipv4/devinet.c#L246">246</a>         in_dev-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L247" href="source/net/ipv4/devinet.c#L247">247</a>         in_dev-&gt;arp_parms = <a href="ident?i=neigh_parms_alloc">neigh_parms_alloc</a>(<a href="ident?i=dev">dev</a>, &amp;<a href="ident?i=arp_tbl">arp_tbl</a>);
<a name="L248" href="source/net/ipv4/devinet.c#L248">248</a>         if (!in_dev-&gt;arp_parms)
<a name="L249" href="source/net/ipv4/devinet.c#L249">249</a>                 goto out_kfree;
<a name="L250" href="source/net/ipv4/devinet.c#L250">250</a>         if (<a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(in_dev-&gt;cnf, FORWARDING))
<a name="L251" href="source/net/ipv4/devinet.c#L251">251</a>                 <a href="ident?i=dev_disable_lro">dev_disable_lro</a>(<a href="ident?i=dev">dev</a>);
<a name="L252" href="source/net/ipv4/devinet.c#L252">252</a>         <b><i>/* Reference in_dev-&gt;dev */</i></b>
<a name="L253" href="source/net/ipv4/devinet.c#L253">253</a>         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=dev">dev</a>);
<a name="L254" href="source/net/ipv4/devinet.c#L254">254</a>         <b><i>/* Account for reference dev-&gt;ip_ptr (below) */</i></b>
<a name="L255" href="source/net/ipv4/devinet.c#L255">255</a>         <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L256" href="source/net/ipv4/devinet.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/devinet.c#L257">257</a>         <a href="ident?i=err">err</a> = <a href="ident?i=devinet_sysctl_register">devinet_sysctl_register</a>(in_dev);
<a name="L258" href="source/net/ipv4/devinet.c#L258">258</a>         if (<a href="ident?i=err">err</a>) {
<a name="L259" href="source/net/ipv4/devinet.c#L259">259</a>                 in_dev-&gt;dead = 1;
<a name="L260" href="source/net/ipv4/devinet.c#L260">260</a>                 <a href="ident?i=in_dev_put">in_dev_put</a>(in_dev);
<a name="L261" href="source/net/ipv4/devinet.c#L261">261</a>                 in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L262" href="source/net/ipv4/devinet.c#L262">262</a>                 goto <a href="ident?i=out">out</a>;
<a name="L263" href="source/net/ipv4/devinet.c#L263">263</a>         }
<a name="L264" href="source/net/ipv4/devinet.c#L264">264</a>         <a href="ident?i=ip_mc_init_dev">ip_mc_init_dev</a>(in_dev);
<a name="L265" href="source/net/ipv4/devinet.c#L265">265</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>)
<a name="L266" href="source/net/ipv4/devinet.c#L266">266</a>                 <a href="ident?i=ip_mc_up">ip_mc_up</a>(in_dev);
<a name="L267" href="source/net/ipv4/devinet.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/devinet.c#L268">268</a>         <b><i>/* we can receive as soon as ip_ptr is set -- do this last */</i></b>
<a name="L269" href="source/net/ipv4/devinet.c#L269">269</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=dev">dev</a>-&gt;ip_ptr, in_dev);
<a name="L270" href="source/net/ipv4/devinet.c#L270">270</a> <a href="ident?i=out">out</a>:
<a name="L271" href="source/net/ipv4/devinet.c#L271">271</a>         return in_dev ?: <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L272" href="source/net/ipv4/devinet.c#L272">272</a> out_kfree:
<a name="L273" href="source/net/ipv4/devinet.c#L273">273</a>         <a href="ident?i=kfree">kfree</a>(in_dev);
<a name="L274" href="source/net/ipv4/devinet.c#L274">274</a>         in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L275" href="source/net/ipv4/devinet.c#L275">275</a>         goto <a href="ident?i=out">out</a>;
<a name="L276" href="source/net/ipv4/devinet.c#L276">276</a> }
<a name="L277" href="source/net/ipv4/devinet.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/devinet.c#L278">278</a> static void <a href="ident?i=in_dev_rcu_put">in_dev_rcu_put</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L279" href="source/net/ipv4/devinet.c#L279">279</a> {
<a name="L280" href="source/net/ipv4/devinet.c#L280">280</a>         struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=in_device">in_device</a>, <a href="ident?i=rcu_head">rcu_head</a>);
<a name="L281" href="source/net/ipv4/devinet.c#L281">281</a>         <a href="ident?i=in_dev_put">in_dev_put</a>(<a href="ident?i=idev">idev</a>);
<a name="L282" href="source/net/ipv4/devinet.c#L282">282</a> }
<a name="L283" href="source/net/ipv4/devinet.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/devinet.c#L284">284</a> static void <a href="ident?i=inetdev_destroy">inetdev_destroy</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L285" href="source/net/ipv4/devinet.c#L285">285</a> {
<a name="L286" href="source/net/ipv4/devinet.c#L286">286</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L287" href="source/net/ipv4/devinet.c#L287">287</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L288" href="source/net/ipv4/devinet.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/devinet.c#L289">289</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L290" href="source/net/ipv4/devinet.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/devinet.c#L291">291</a>         <a href="ident?i=dev">dev</a> = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L292" href="source/net/ipv4/devinet.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/devinet.c#L293">293</a>         in_dev-&gt;dead = 1;
<a name="L294" href="source/net/ipv4/devinet.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/devinet.c#L295">295</a>         <a href="ident?i=ip_mc_destroy_dev">ip_mc_destroy_dev</a>(in_dev);
<a name="L296" href="source/net/ipv4/devinet.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/devinet.c#L297">297</a>         while ((<a href="ident?i=ifa">ifa</a> = in_dev-&gt;ifa_list) != <a href="ident?i=NULL">NULL</a>) {
<a name="L298" href="source/net/ipv4/devinet.c#L298">298</a>                 <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(in_dev, &amp;in_dev-&gt;ifa_list, 0);
<a name="L299" href="source/net/ipv4/devinet.c#L299">299</a>                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L300" href="source/net/ipv4/devinet.c#L300">300</a>         }
<a name="L301" href="source/net/ipv4/devinet.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/devinet.c#L302">302</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=dev">dev</a>-&gt;ip_ptr, <a href="ident?i=NULL">NULL</a>);
<a name="L303" href="source/net/ipv4/devinet.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/devinet.c#L304">304</a>         <a href="ident?i=devinet_sysctl_unregister">devinet_sysctl_unregister</a>(in_dev);
<a name="L305" href="source/net/ipv4/devinet.c#L305">305</a>         <a href="ident?i=neigh_parms_release">neigh_parms_release</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, in_dev-&gt;arp_parms);
<a name="L306" href="source/net/ipv4/devinet.c#L306">306</a>         <a href="ident?i=arp_ifdown">arp_ifdown</a>(<a href="ident?i=dev">dev</a>);
<a name="L307" href="source/net/ipv4/devinet.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/devinet.c#L308">308</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;in_dev-&gt;<a href="ident?i=rcu_head">rcu_head</a>, <a href="ident?i=in_dev_rcu_put">in_dev_rcu_put</a>);
<a name="L309" href="source/net/ipv4/devinet.c#L309">309</a> }
<a name="L310" href="source/net/ipv4/devinet.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/devinet.c#L311">311</a> int <a href="ident?i=inet_addr_onlink">inet_addr_onlink</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=a">a</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=b">b</a>)
<a name="L312" href="source/net/ipv4/devinet.c#L312">312</a> {
<a name="L313" href="source/net/ipv4/devinet.c#L313">313</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L314" href="source/net/ipv4/devinet.c#L314">314</a>         <a href="ident?i=for_primary_ifa">for_primary_ifa</a>(in_dev) {
<a name="L315" href="source/net/ipv4/devinet.c#L315">315</a>                 if (<a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=a">a</a>, <a href="ident?i=ifa">ifa</a>)) {
<a name="L316" href="source/net/ipv4/devinet.c#L316">316</a>                         if (!<a href="ident?i=b">b</a> || <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=b">b</a>, <a href="ident?i=ifa">ifa</a>)) {
<a name="L317" href="source/net/ipv4/devinet.c#L317">317</a>                                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L318" href="source/net/ipv4/devinet.c#L318">318</a>                                 return 1;
<a name="L319" href="source/net/ipv4/devinet.c#L319">319</a>                         }
<a name="L320" href="source/net/ipv4/devinet.c#L320">320</a>                 }
<a name="L321" href="source/net/ipv4/devinet.c#L321">321</a>         } <a href="ident?i=endfor_ifa">endfor_ifa</a>(in_dev);
<a name="L322" href="source/net/ipv4/devinet.c#L322">322</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L323" href="source/net/ipv4/devinet.c#L323">323</a>         return 0;
<a name="L324" href="source/net/ipv4/devinet.c#L324">324</a> }
<a name="L325" href="source/net/ipv4/devinet.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/devinet.c#L326">326</a> static void <a href="ident?i=__inet_del_ifa">__inet_del_ifa</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> **ifap,
<a name="L327" href="source/net/ipv4/devinet.c#L327">327</a>                          int <a href="ident?i=destroy">destroy</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh, <a href="ident?i=u32">u32</a> portid)
<a name="L328" href="source/net/ipv4/devinet.c#L328">328</a> {
<a name="L329" href="source/net/ipv4/devinet.c#L329">329</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=promote">promote</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L330" href="source/net/ipv4/devinet.c#L330">330</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>, *ifa1 = *ifap;
<a name="L331" href="source/net/ipv4/devinet.c#L331">331</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *last_prim = in_dev-&gt;ifa_list;
<a name="L332" href="source/net/ipv4/devinet.c#L332">332</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *prev_prom = <a href="ident?i=NULL">NULL</a>;
<a name="L333" href="source/net/ipv4/devinet.c#L333">333</a>         int do_promote = <a href="ident?i=IN_DEV_PROMOTE_SECONDARIES">IN_DEV_PROMOTE_SECONDARIES</a>(in_dev);
<a name="L334" href="source/net/ipv4/devinet.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/devinet.c#L335">335</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L336" href="source/net/ipv4/devinet.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/devinet.c#L337">337</a>         <b><i>/* 1. Deleting primary ifaddr forces deletion all secondaries</i></b>
<a name="L338" href="source/net/ipv4/devinet.c#L338">338</a> <b><i>         * unless alias promotion is set</i></b>
<a name="L339" href="source/net/ipv4/devinet.c#L339">339</a> <b><i>         **/</i></b>
<a name="L340" href="source/net/ipv4/devinet.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/devinet.c#L341">341</a>         if (!(ifa1-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>)) {
<a name="L342" href="source/net/ipv4/devinet.c#L342">342</a>                 struct <a href="ident?i=in_ifaddr">in_ifaddr</a> **ifap1 = &amp;ifa1-&gt;ifa_next;
<a name="L343" href="source/net/ipv4/devinet.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/devinet.c#L344">344</a>                 while ((<a href="ident?i=ifa">ifa</a> = *ifap1) != <a href="ident?i=NULL">NULL</a>) {
<a name="L345" href="source/net/ipv4/devinet.c#L345">345</a>                         if (!(<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) &amp;&amp;
<a name="L346" href="source/net/ipv4/devinet.c#L346">346</a>                             ifa1-&gt;ifa_scope &lt;= <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope)
<a name="L347" href="source/net/ipv4/devinet.c#L347">347</a>                                 last_prim = <a href="ident?i=ifa">ifa</a>;
<a name="L348" href="source/net/ipv4/devinet.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/devinet.c#L349">349</a>                         if (!(<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) ||
<a name="L350" href="source/net/ipv4/devinet.c#L350">350</a>                             ifa1-&gt;ifa_mask != <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask ||
<a name="L351" href="source/net/ipv4/devinet.c#L351">351</a>                             !<a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, <a href="ident?i=ifa">ifa</a>)) {
<a name="L352" href="source/net/ipv4/devinet.c#L352">352</a>                                 ifap1 = &amp;<a href="ident?i=ifa">ifa</a>-&gt;ifa_next;
<a name="L353" href="source/net/ipv4/devinet.c#L353">353</a>                                 prev_prom = <a href="ident?i=ifa">ifa</a>;
<a name="L354" href="source/net/ipv4/devinet.c#L354">354</a>                                 continue;
<a name="L355" href="source/net/ipv4/devinet.c#L355">355</a>                         }
<a name="L356" href="source/net/ipv4/devinet.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/devinet.c#L357">357</a>                         if (!do_promote) {
<a name="L358" href="source/net/ipv4/devinet.c#L358">358</a>                                 <a href="ident?i=inet_hash_remove">inet_hash_remove</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L359" href="source/net/ipv4/devinet.c#L359">359</a>                                 *ifap1 = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next;
<a name="L360" href="source/net/ipv4/devinet.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/devinet.c#L361">361</a>                                 <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_DELADDR">RTM_DELADDR</a>, <a href="ident?i=ifa">ifa</a>, nlh, portid);
<a name="L362" href="source/net/ipv4/devinet.c#L362">362</a>                                 <a href="ident?i=blocking_notifier_call_chain">blocking_notifier_call_chain</a>(&amp;inetaddr_chain,
<a name="L363" href="source/net/ipv4/devinet.c#L363">363</a>                                                 <a href="ident?i=NETDEV_DOWN">NETDEV_DOWN</a>, <a href="ident?i=ifa">ifa</a>);
<a name="L364" href="source/net/ipv4/devinet.c#L364">364</a>                                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L365" href="source/net/ipv4/devinet.c#L365">365</a>                         } else {
<a name="L366" href="source/net/ipv4/devinet.c#L366">366</a>                                 <a href="ident?i=promote">promote</a> = <a href="ident?i=ifa">ifa</a>;
<a name="L367" href="source/net/ipv4/devinet.c#L367">367</a>                                 break;
<a name="L368" href="source/net/ipv4/devinet.c#L368">368</a>                         }
<a name="L369" href="source/net/ipv4/devinet.c#L369">369</a>                 }
<a name="L370" href="source/net/ipv4/devinet.c#L370">370</a>         }
<a name="L371" href="source/net/ipv4/devinet.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/devinet.c#L372">372</a>         <b><i>/* On promotion all secondaries from subnet are changing</i></b>
<a name="L373" href="source/net/ipv4/devinet.c#L373">373</a> <b><i>         * the primary IP, we must remove all their routes silently</i></b>
<a name="L374" href="source/net/ipv4/devinet.c#L374">374</a> <b><i>         * and later to add them back with new prefsrc. Do this</i></b>
<a name="L375" href="source/net/ipv4/devinet.c#L375">375</a> <b><i>         * while all addresses are on the device list.</i></b>
<a name="L376" href="source/net/ipv4/devinet.c#L376">376</a> <b><i>         */</i></b>
<a name="L377" href="source/net/ipv4/devinet.c#L377">377</a>         for (<a href="ident?i=ifa">ifa</a> = <a href="ident?i=promote">promote</a>; <a href="ident?i=ifa">ifa</a>; <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L378" href="source/net/ipv4/devinet.c#L378">378</a>                 if (ifa1-&gt;ifa_mask == <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask &amp;&amp;
<a name="L379" href="source/net/ipv4/devinet.c#L379">379</a>                     <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, <a href="ident?i=ifa">ifa</a>))
<a name="L380" href="source/net/ipv4/devinet.c#L380">380</a>                         <a href="ident?i=fib_del_ifaddr">fib_del_ifaddr</a>(<a href="ident?i=ifa">ifa</a>, ifa1);
<a name="L381" href="source/net/ipv4/devinet.c#L381">381</a>         }
<a name="L382" href="source/net/ipv4/devinet.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/devinet.c#L383">383</a>         <b><i>/* 2. Unlink it */</i></b>
<a name="L384" href="source/net/ipv4/devinet.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/devinet.c#L385">385</a>         *ifap = ifa1-&gt;ifa_next;
<a name="L386" href="source/net/ipv4/devinet.c#L386">386</a>         <a href="ident?i=inet_hash_remove">inet_hash_remove</a>(ifa1);
<a name="L387" href="source/net/ipv4/devinet.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/devinet.c#L388">388</a>         <b><i>/* 3. Announce address deletion */</i></b>
<a name="L389" href="source/net/ipv4/devinet.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/devinet.c#L390">390</a>         <b><i>/* Send message first, then call notifier.</i></b>
<a name="L391" href="source/net/ipv4/devinet.c#L391">391</a> <b><i>           At first sight, FIB update triggered by notifier</i></b>
<a name="L392" href="source/net/ipv4/devinet.c#L392">392</a> <b><i>           will refer to already deleted ifaddr, that could confuse</i></b>
<a name="L393" href="source/net/ipv4/devinet.c#L393">393</a> <b><i>           netlink listeners. It is not true: look, gated sees</i></b>
<a name="L394" href="source/net/ipv4/devinet.c#L394">394</a> <b><i>           that route deleted and if it still thinks that ifaddr</i></b>
<a name="L395" href="source/net/ipv4/devinet.c#L395">395</a> <b><i>           is valid, it will try to restore deleted routes... Grr.</i></b>
<a name="L396" href="source/net/ipv4/devinet.c#L396">396</a> <b><i>           So that, this order is correct.</i></b>
<a name="L397" href="source/net/ipv4/devinet.c#L397">397</a> <b><i>         */</i></b>
<a name="L398" href="source/net/ipv4/devinet.c#L398">398</a>         <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_DELADDR">RTM_DELADDR</a>, ifa1, nlh, portid);
<a name="L399" href="source/net/ipv4/devinet.c#L399">399</a>         <a href="ident?i=blocking_notifier_call_chain">blocking_notifier_call_chain</a>(&amp;inetaddr_chain, <a href="ident?i=NETDEV_DOWN">NETDEV_DOWN</a>, ifa1);
<a name="L400" href="source/net/ipv4/devinet.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/devinet.c#L401">401</a>         if (<a href="ident?i=promote">promote</a>) {
<a name="L402" href="source/net/ipv4/devinet.c#L402">402</a>                 struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *next_sec = <a href="ident?i=promote">promote</a>-&gt;ifa_next;
<a name="L403" href="source/net/ipv4/devinet.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/devinet.c#L404">404</a>                 if (prev_prom) {
<a name="L405" href="source/net/ipv4/devinet.c#L405">405</a>                         prev_prom-&gt;ifa_next = <a href="ident?i=promote">promote</a>-&gt;ifa_next;
<a name="L406" href="source/net/ipv4/devinet.c#L406">406</a>                         <a href="ident?i=promote">promote</a>-&gt;ifa_next = last_prim-&gt;ifa_next;
<a name="L407" href="source/net/ipv4/devinet.c#L407">407</a>                         last_prim-&gt;ifa_next = <a href="ident?i=promote">promote</a>;
<a name="L408" href="source/net/ipv4/devinet.c#L408">408</a>                 }
<a name="L409" href="source/net/ipv4/devinet.c#L409">409</a> 
<a name="L410" href="source/net/ipv4/devinet.c#L410">410</a>                 <a href="ident?i=promote">promote</a>-&gt;ifa_flags &amp;= ~IFA_F_SECONDARY;
<a name="L411" href="source/net/ipv4/devinet.c#L411">411</a>                 <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=promote">promote</a>, nlh, portid);
<a name="L412" href="source/net/ipv4/devinet.c#L412">412</a>                 <a href="ident?i=blocking_notifier_call_chain">blocking_notifier_call_chain</a>(&amp;inetaddr_chain,
<a name="L413" href="source/net/ipv4/devinet.c#L413">413</a>                                 <a href="ident?i=NETDEV_UP">NETDEV_UP</a>, <a href="ident?i=promote">promote</a>);
<a name="L414" href="source/net/ipv4/devinet.c#L414">414</a>                 for (<a href="ident?i=ifa">ifa</a> = next_sec; <a href="ident?i=ifa">ifa</a>; <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L415" href="source/net/ipv4/devinet.c#L415">415</a>                         if (ifa1-&gt;ifa_mask != <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask ||
<a name="L416" href="source/net/ipv4/devinet.c#L416">416</a>                             !<a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, <a href="ident?i=ifa">ifa</a>))
<a name="L417" href="source/net/ipv4/devinet.c#L417">417</a>                                         continue;
<a name="L418" href="source/net/ipv4/devinet.c#L418">418</a>                         <a href="ident?i=fib_add_ifaddr">fib_add_ifaddr</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L419" href="source/net/ipv4/devinet.c#L419">419</a>                 }
<a name="L420" href="source/net/ipv4/devinet.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/devinet.c#L421">421</a>         }
<a name="L422" href="source/net/ipv4/devinet.c#L422">422</a>         if (<a href="ident?i=destroy">destroy</a>)
<a name="L423" href="source/net/ipv4/devinet.c#L423">423</a>                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(ifa1);
<a name="L424" href="source/net/ipv4/devinet.c#L424">424</a> }
<a name="L425" href="source/net/ipv4/devinet.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/devinet.c#L426">426</a> static void <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> **ifap,
<a name="L427" href="source/net/ipv4/devinet.c#L427">427</a>                          int <a href="ident?i=destroy">destroy</a>)
<a name="L428" href="source/net/ipv4/devinet.c#L428">428</a> {
<a name="L429" href="source/net/ipv4/devinet.c#L429">429</a>         <a href="ident?i=__inet_del_ifa">__inet_del_ifa</a>(in_dev, ifap, <a href="ident?i=destroy">destroy</a>, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L430" href="source/net/ipv4/devinet.c#L430">430</a> }
<a name="L431" href="source/net/ipv4/devinet.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/devinet.c#L432">432</a> static void <a href="ident?i=check_lifetime">check_lifetime</a>(struct <a href="ident?i=work_struct">work_struct</a> *<a href="ident?i=work">work</a>);
<a name="L433" href="source/net/ipv4/devinet.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/devinet.c#L434">434</a> static <a href="ident?i=DECLARE_DELAYED_WORK">DECLARE_DELAYED_WORK</a>(check_lifetime_work, <a href="ident?i=check_lifetime">check_lifetime</a>);
<a name="L435" href="source/net/ipv4/devinet.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/devinet.c#L436">436</a> static int <a href="ident?i=__inet_insert_ifa">__inet_insert_ifa</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L437" href="source/net/ipv4/devinet.c#L437">437</a>                              <a href="ident?i=u32">u32</a> portid)
<a name="L438" href="source/net/ipv4/devinet.c#L438">438</a> {
<a name="L439" href="source/net/ipv4/devinet.c#L439">439</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev;
<a name="L440" href="source/net/ipv4/devinet.c#L440">440</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *ifa1, **ifap, **last_primary;
<a name="L441" href="source/net/ipv4/devinet.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/devinet.c#L442">442</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L443" href="source/net/ipv4/devinet.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/devinet.c#L444">444</a>         if (!<a href="ident?i=ifa">ifa</a>-&gt;ifa_local) {
<a name="L445" href="source/net/ipv4/devinet.c#L445">445</a>                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L446" href="source/net/ipv4/devinet.c#L446">446</a>                 return 0;
<a name="L447" href="source/net/ipv4/devinet.c#L447">447</a>         }
<a name="L448" href="source/net/ipv4/devinet.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/devinet.c#L449">449</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp;= ~IFA_F_SECONDARY;
<a name="L450" href="source/net/ipv4/devinet.c#L450">450</a>         last_primary = &amp;in_dev-&gt;ifa_list;
<a name="L451" href="source/net/ipv4/devinet.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/devinet.c#L452">452</a>         for (ifap = &amp;in_dev-&gt;ifa_list; (ifa1 = *ifap) != <a href="ident?i=NULL">NULL</a>;
<a name="L453" href="source/net/ipv4/devinet.c#L453">453</a>              ifap = &amp;ifa1-&gt;ifa_next) {
<a name="L454" href="source/net/ipv4/devinet.c#L454">454</a>                 if (!(ifa1-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) &amp;&amp;
<a name="L455" href="source/net/ipv4/devinet.c#L455">455</a>                     <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope &lt;= ifa1-&gt;ifa_scope)
<a name="L456" href="source/net/ipv4/devinet.c#L456">456</a>                         last_primary = &amp;ifa1-&gt;ifa_next;
<a name="L457" href="source/net/ipv4/devinet.c#L457">457</a>                 if (ifa1-&gt;ifa_mask == <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask &amp;&amp;
<a name="L458" href="source/net/ipv4/devinet.c#L458">458</a>                     <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, <a href="ident?i=ifa">ifa</a>)) {
<a name="L459" href="source/net/ipv4/devinet.c#L459">459</a>                         if (ifa1-&gt;ifa_local == <a href="ident?i=ifa">ifa</a>-&gt;ifa_local) {
<a name="L460" href="source/net/ipv4/devinet.c#L460">460</a>                                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L461" href="source/net/ipv4/devinet.c#L461">461</a>                                 return -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L462" href="source/net/ipv4/devinet.c#L462">462</a>                         }
<a name="L463" href="source/net/ipv4/devinet.c#L463">463</a>                         if (ifa1-&gt;ifa_scope != <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope) {
<a name="L464" href="source/net/ipv4/devinet.c#L464">464</a>                                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L465" href="source/net/ipv4/devinet.c#L465">465</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L466" href="source/net/ipv4/devinet.c#L466">466</a>                         }
<a name="L467" href="source/net/ipv4/devinet.c#L467">467</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags |= <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>;
<a name="L468" href="source/net/ipv4/devinet.c#L468">468</a>                 }
<a name="L469" href="source/net/ipv4/devinet.c#L469">469</a>         }
<a name="L470" href="source/net/ipv4/devinet.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/devinet.c#L471">471</a>         if (!(<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>)) {
<a name="L472" href="source/net/ipv4/devinet.c#L472">472</a>                 <a href="ident?i=prandom_seed">prandom_seed</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>) <a href="ident?i=ifa">ifa</a>-&gt;ifa_local);
<a name="L473" href="source/net/ipv4/devinet.c#L473">473</a>                 ifap = last_primary;
<a name="L474" href="source/net/ipv4/devinet.c#L474">474</a>         }
<a name="L475" href="source/net/ipv4/devinet.c#L475">475</a> 
<a name="L476" href="source/net/ipv4/devinet.c#L476">476</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_next = *ifap;
<a name="L477" href="source/net/ipv4/devinet.c#L477">477</a>         *ifap = <a href="ident?i=ifa">ifa</a>;
<a name="L478" href="source/net/ipv4/devinet.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/devinet.c#L479">479</a>         <a href="ident?i=inet_hash_insert">inet_hash_insert</a>(<a href="ident?i=dev_net">dev_net</a>(in_dev-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=ifa">ifa</a>);
<a name="L480" href="source/net/ipv4/devinet.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/devinet.c#L481">481</a>         <a href="ident?i=cancel_delayed_work">cancel_delayed_work</a>(&amp;check_lifetime_work);
<a name="L482" href="source/net/ipv4/devinet.c#L482">482</a>         <a href="ident?i=queue_delayed_work">queue_delayed_work</a>(<a href="ident?i=system_power_efficient_wq">system_power_efficient_wq</a>, &amp;check_lifetime_work, 0);
<a name="L483" href="source/net/ipv4/devinet.c#L483">483</a> 
<a name="L484" href="source/net/ipv4/devinet.c#L484">484</a>         <b><i>/* Send message first, then call notifier.</i></b>
<a name="L485" href="source/net/ipv4/devinet.c#L485">485</a> <b><i>           Notifier will trigger FIB update, so that</i></b>
<a name="L486" href="source/net/ipv4/devinet.c#L486">486</a> <b><i>           listeners of netlink will know about new ifaddr */</i></b>
<a name="L487" href="source/net/ipv4/devinet.c#L487">487</a>         <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=ifa">ifa</a>, nlh, portid);
<a name="L488" href="source/net/ipv4/devinet.c#L488">488</a>         <a href="ident?i=blocking_notifier_call_chain">blocking_notifier_call_chain</a>(&amp;inetaddr_chain, <a href="ident?i=NETDEV_UP">NETDEV_UP</a>, <a href="ident?i=ifa">ifa</a>);
<a name="L489" href="source/net/ipv4/devinet.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/devinet.c#L490">490</a>         return 0;
<a name="L491" href="source/net/ipv4/devinet.c#L491">491</a> }
<a name="L492" href="source/net/ipv4/devinet.c#L492">492</a> 
<a name="L493" href="source/net/ipv4/devinet.c#L493">493</a> static int <a href="ident?i=inet_insert_ifa">inet_insert_ifa</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L494" href="source/net/ipv4/devinet.c#L494">494</a> {
<a name="L495" href="source/net/ipv4/devinet.c#L495">495</a>         return <a href="ident?i=__inet_insert_ifa">__inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L496" href="source/net/ipv4/devinet.c#L496">496</a> }
<a name="L497" href="source/net/ipv4/devinet.c#L497">497</a> 
<a name="L498" href="source/net/ipv4/devinet.c#L498">498</a> static int <a href="ident?i=inet_set_ifa">inet_set_ifa</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L499" href="source/net/ipv4/devinet.c#L499">499</a> {
<a name="L500" href="source/net/ipv4/devinet.c#L500">500</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L501" href="source/net/ipv4/devinet.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/devinet.c#L502">502</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L503" href="source/net/ipv4/devinet.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/devinet.c#L504">504</a>         if (!in_dev) {
<a name="L505" href="source/net/ipv4/devinet.c#L505">505</a>                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L506" href="source/net/ipv4/devinet.c#L506">506</a>                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L507" href="source/net/ipv4/devinet.c#L507">507</a>         }
<a name="L508" href="source/net/ipv4/devinet.c#L508">508</a>         <a href="ident?i=ipv4_devconf_setall">ipv4_devconf_setall</a>(in_dev);
<a name="L509" href="source/net/ipv4/devinet.c#L509">509</a>         <a href="ident?i=neigh_parms_data_state_setall">neigh_parms_data_state_setall</a>(in_dev-&gt;arp_parms);
<a name="L510" href="source/net/ipv4/devinet.c#L510">510</a>         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev != in_dev) {
<a name="L511" href="source/net/ipv4/devinet.c#L511">511</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev);
<a name="L512" href="source/net/ipv4/devinet.c#L512">512</a>                 <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L513" href="source/net/ipv4/devinet.c#L513">513</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev = in_dev;
<a name="L514" href="source/net/ipv4/devinet.c#L514">514</a>         }
<a name="L515" href="source/net/ipv4/devinet.c#L515">515</a>         if (<a href="ident?i=ipv4_is_loopback">ipv4_is_loopback</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_local))
<a name="L516" href="source/net/ipv4/devinet.c#L516">516</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope = RT_SCOPE_HOST;
<a name="L517" href="source/net/ipv4/devinet.c#L517">517</a>         return <a href="ident?i=inet_insert_ifa">inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L518" href="source/net/ipv4/devinet.c#L518">518</a> }
<a name="L519" href="source/net/ipv4/devinet.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/devinet.c#L520">520</a> <b><i>/* Caller must hold RCU or RTNL :</i></b>
<a name="L521" href="source/net/ipv4/devinet.c#L521">521</a> <b><i> * We dont take a reference on found in_device</i></b>
<a name="L522" href="source/net/ipv4/devinet.c#L522">522</a> <b><i> */</i></b>
<a name="L523" href="source/net/ipv4/devinet.c#L523">523</a> struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=inetdev_by_index">inetdev_by_index</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int ifindex)
<a name="L524" href="source/net/ipv4/devinet.c#L524">524</a> {
<a name="L525" href="source/net/ipv4/devinet.c#L525">525</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L526" href="source/net/ipv4/devinet.c#L526">526</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L527" href="source/net/ipv4/devinet.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/devinet.c#L528">528</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L529" href="source/net/ipv4/devinet.c#L529">529</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index_rcu">dev_get_by_index_rcu</a>(<a href="ident?i=net">net</a>, ifindex);
<a name="L530" href="source/net/ipv4/devinet.c#L530">530</a>         if (<a href="ident?i=dev">dev</a>)
<a name="L531" href="source/net/ipv4/devinet.c#L531">531</a>                 in_dev = <a href="ident?i=rcu_dereference_rtnl">rcu_dereference_rtnl</a>(<a href="ident?i=dev">dev</a>-&gt;ip_ptr);
<a name="L532" href="source/net/ipv4/devinet.c#L532">532</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L533" href="source/net/ipv4/devinet.c#L533">533</a>         return in_dev;
<a name="L534" href="source/net/ipv4/devinet.c#L534">534</a> }
<a name="L535" href="source/net/ipv4/devinet.c#L535">535</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inetdev_by_index">inetdev_by_index</a>);
<a name="L536" href="source/net/ipv4/devinet.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/devinet.c#L537">537</a> <b><i>/* Called only from RTNL semaphored context. No locks. */</i></b>
<a name="L538" href="source/net/ipv4/devinet.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/devinet.c#L539">539</a> struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=inet_ifa_byprefix">inet_ifa_byprefix</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=prefix">prefix</a>,
<a name="L540" href="source/net/ipv4/devinet.c#L540">540</a>                                     <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a>)
<a name="L541" href="source/net/ipv4/devinet.c#L541">541</a> {
<a name="L542" href="source/net/ipv4/devinet.c#L542">542</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L543" href="source/net/ipv4/devinet.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/devinet.c#L544">544</a>         <a href="ident?i=for_primary_ifa">for_primary_ifa</a>(in_dev) {
<a name="L545" href="source/net/ipv4/devinet.c#L545">545</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_mask == <a href="ident?i=mask">mask</a> &amp;&amp; <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=prefix">prefix</a>, <a href="ident?i=ifa">ifa</a>))
<a name="L546" href="source/net/ipv4/devinet.c#L546">546</a>                         return <a href="ident?i=ifa">ifa</a>;
<a name="L547" href="source/net/ipv4/devinet.c#L547">547</a>         } <a href="ident?i=endfor_ifa">endfor_ifa</a>(in_dev);
<a name="L548" href="source/net/ipv4/devinet.c#L548">548</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L549" href="source/net/ipv4/devinet.c#L549">549</a> }
<a name="L550" href="source/net/ipv4/devinet.c#L550">550</a> 
<a name="L551" href="source/net/ipv4/devinet.c#L551">551</a> static int <a href="ident?i=ip_mc_config">ip_mc_config</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> <a href="ident?i=join">join</a>, const struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L552" href="source/net/ipv4/devinet.c#L552">552</a> {
<a name="L553" href="source/net/ipv4/devinet.c#L553">553</a>         struct <a href="ident?i=ip_mreqn">ip_mreqn</a> mreq = {
<a name="L554" href="source/net/ipv4/devinet.c#L554">554</a>                 .imr_multiaddr.s_addr = <a href="ident?i=ifa">ifa</a>-&gt;ifa_address,
<a name="L555" href="source/net/ipv4/devinet.c#L555">555</a>                 .imr_ifindex = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex,
<a name="L556" href="source/net/ipv4/devinet.c#L556">556</a>         };
<a name="L557" href="source/net/ipv4/devinet.c#L557">557</a>         int <a href="ident?i=ret">ret</a>;
<a name="L558" href="source/net/ipv4/devinet.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/devinet.c#L559">559</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L560" href="source/net/ipv4/devinet.c#L560">560</a> 
<a name="L561" href="source/net/ipv4/devinet.c#L561">561</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L562" href="source/net/ipv4/devinet.c#L562">562</a>         if (<a href="ident?i=join">join</a>)
<a name="L563" href="source/net/ipv4/devinet.c#L563">563</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>(sk, &amp;mreq);
<a name="L564" href="source/net/ipv4/devinet.c#L564">564</a>         else
<a name="L565" href="source/net/ipv4/devinet.c#L565">565</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>(sk, &amp;mreq);
<a name="L566" href="source/net/ipv4/devinet.c#L566">566</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L567" href="source/net/ipv4/devinet.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/devinet.c#L568">568</a>         return <a href="ident?i=ret">ret</a>;
<a name="L569" href="source/net/ipv4/devinet.c#L569">569</a> }
<a name="L570" href="source/net/ipv4/devinet.c#L570">570</a> 
<a name="L571" href="source/net/ipv4/devinet.c#L571">571</a> static int <a href="ident?i=inet_rtm_deladdr">inet_rtm_deladdr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L572" href="source/net/ipv4/devinet.c#L572">572</a> {
<a name="L573" href="source/net/ipv4/devinet.c#L573">573</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L574" href="source/net/ipv4/devinet.c#L574">574</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[<a href="ident?i=IFA_MAX">IFA_MAX</a>+1];
<a name="L575" href="source/net/ipv4/devinet.c#L575">575</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L576" href="source/net/ipv4/devinet.c#L576">576</a>         struct <a href="ident?i=ifaddrmsg">ifaddrmsg</a> *ifm;
<a name="L577" href="source/net/ipv4/devinet.c#L577">577</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>, **ifap;
<a name="L578" href="source/net/ipv4/devinet.c#L578">578</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L579" href="source/net/ipv4/devinet.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/devinet.c#L580">580</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L581" href="source/net/ipv4/devinet.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/devinet.c#L582">582</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nlmsg_parse">nlmsg_parse</a>(nlh, sizeof(*ifm), <a href="ident?i=tb">tb</a>, <a href="ident?i=IFA_MAX">IFA_MAX</a>, <a href="ident?i=ifa_ipv4_policy">ifa_ipv4_policy</a>);
<a name="L583" href="source/net/ipv4/devinet.c#L583">583</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L584" href="source/net/ipv4/devinet.c#L584">584</a>                 goto errout;
<a name="L585" href="source/net/ipv4/devinet.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/devinet.c#L586">586</a>         ifm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L587" href="source/net/ipv4/devinet.c#L587">587</a>         in_dev = <a href="ident?i=inetdev_by_index">inetdev_by_index</a>(<a href="ident?i=net">net</a>, ifm-&gt;ifa_index);
<a name="L588" href="source/net/ipv4/devinet.c#L588">588</a>         if (!in_dev) {
<a name="L589" href="source/net/ipv4/devinet.c#L589">589</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L590" href="source/net/ipv4/devinet.c#L590">590</a>                 goto errout;
<a name="L591" href="source/net/ipv4/devinet.c#L591">591</a>         }
<a name="L592" href="source/net/ipv4/devinet.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/devinet.c#L593">593</a>         for (ifap = &amp;in_dev-&gt;ifa_list; (<a href="ident?i=ifa">ifa</a> = *ifap) != <a href="ident?i=NULL">NULL</a>;
<a name="L594" href="source/net/ipv4/devinet.c#L594">594</a>              ifap = &amp;<a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L595" href="source/net/ipv4/devinet.c#L595">595</a>                 if (<a href="ident?i=tb">tb</a>[IFA_LOCAL] &amp;&amp;
<a name="L596" href="source/net/ipv4/devinet.c#L596">596</a>                     <a href="ident?i=ifa">ifa</a>-&gt;ifa_local != <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[IFA_LOCAL]))
<a name="L597" href="source/net/ipv4/devinet.c#L597">597</a>                         continue;
<a name="L598" href="source/net/ipv4/devinet.c#L598">598</a> 
<a name="L599" href="source/net/ipv4/devinet.c#L599">599</a>                 if (<a href="ident?i=tb">tb</a>[IFA_LABEL] &amp;&amp; <a href="ident?i=nla_strcmp">nla_strcmp</a>(<a href="ident?i=tb">tb</a>[IFA_LABEL], <a href="ident?i=ifa">ifa</a>-&gt;ifa_label))
<a name="L600" href="source/net/ipv4/devinet.c#L600">600</a>                         continue;
<a name="L601" href="source/net/ipv4/devinet.c#L601">601</a> 
<a name="L602" href="source/net/ipv4/devinet.c#L602">602</a>                 if (<a href="ident?i=tb">tb</a>[IFA_ADDRESS] &amp;&amp;
<a name="L603" href="source/net/ipv4/devinet.c#L603">603</a>                     (ifm-&gt;ifa_prefixlen != <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen ||
<a name="L604" href="source/net/ipv4/devinet.c#L604">604</a>                     !<a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[IFA_ADDRESS]), <a href="ident?i=ifa">ifa</a>)))
<a name="L605" href="source/net/ipv4/devinet.c#L605">605</a>                         continue;
<a name="L606" href="source/net/ipv4/devinet.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/devinet.c#L607">607</a>                 if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_address))
<a name="L608" href="source/net/ipv4/devinet.c#L608">608</a>                         <a href="ident?i=ip_mc_config">ip_mc_config</a>(<a href="ident?i=net">net</a>-&gt;ipv4.mc_autojoin_sk, <a href="ident?i=false">false</a>, <a href="ident?i=ifa">ifa</a>);
<a name="L609" href="source/net/ipv4/devinet.c#L609">609</a>                 <a href="ident?i=__inet_del_ifa">__inet_del_ifa</a>(in_dev, ifap, 1, nlh, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid);
<a name="L610" href="source/net/ipv4/devinet.c#L610">610</a>                 return 0;
<a name="L611" href="source/net/ipv4/devinet.c#L611">611</a>         }
<a name="L612" href="source/net/ipv4/devinet.c#L612">612</a> 
<a name="L613" href="source/net/ipv4/devinet.c#L613">613</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L614" href="source/net/ipv4/devinet.c#L614">614</a> errout:
<a name="L615" href="source/net/ipv4/devinet.c#L615">615</a>         return <a href="ident?i=err">err</a>;
<a name="L616" href="source/net/ipv4/devinet.c#L616">616</a> }
<a name="L617" href="source/net/ipv4/devinet.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/devinet.c#L618">618</a> #define <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>      0xFFFFFFFF
<a name="L619" href="source/net/ipv4/devinet.c#L619">619</a> 
<a name="L620" href="source/net/ipv4/devinet.c#L620">620</a> static void <a href="ident?i=check_lifetime">check_lifetime</a>(struct <a href="ident?i=work_struct">work_struct</a> *<a href="ident?i=work">work</a>)
<a name="L621" href="source/net/ipv4/devinet.c#L621">621</a> {
<a name="L622" href="source/net/ipv4/devinet.c#L622">622</a>         unsigned long <a href="ident?i=now">now</a>, <a href="ident?i=next">next</a>, next_sec, next_sched;
<a name="L623" href="source/net/ipv4/devinet.c#L623">623</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L624" href="source/net/ipv4/devinet.c#L624">624</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L625" href="source/net/ipv4/devinet.c#L625">625</a>         int <a href="ident?i=i">i</a>;
<a name="L626" href="source/net/ipv4/devinet.c#L626">626</a> 
<a name="L627" href="source/net/ipv4/devinet.c#L627">627</a>         <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L628" href="source/net/ipv4/devinet.c#L628">628</a>         <a href="ident?i=next">next</a> = <a href="ident?i=round_jiffies_up">round_jiffies_up</a>(<a href="ident?i=now">now</a> + <a href="ident?i=ADDR_CHECK_FREQUENCY">ADDR_CHECK_FREQUENCY</a>);
<a name="L629" href="source/net/ipv4/devinet.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/devinet.c#L630">630</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=IN4_ADDR_HSIZE">IN4_ADDR_HSIZE</a>; <a href="ident?i=i">i</a>++) {
<a name="L631" href="source/net/ipv4/devinet.c#L631">631</a>                 <a href="ident?i=bool">bool</a> change_needed = <a href="ident?i=false">false</a>;
<a name="L632" href="source/net/ipv4/devinet.c#L632">632</a> 
<a name="L633" href="source/net/ipv4/devinet.c#L633">633</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L634" href="source/net/ipv4/devinet.c#L634">634</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=ifa">ifa</a>, &amp;<a href="ident?i=inet_addr_lst">inet_addr_lst</a>[<a href="ident?i=i">i</a>], <a href="ident?i=hash">hash</a>) {
<a name="L635" href="source/net/ipv4/devinet.c#L635">635</a>                         unsigned long age;
<a name="L636" href="source/net/ipv4/devinet.c#L636">636</a> 
<a name="L637" href="source/net/ipv4/devinet.c#L637">637</a>                         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_PERMANENT">IFA_F_PERMANENT</a>)
<a name="L638" href="source/net/ipv4/devinet.c#L638">638</a>                                 continue;
<a name="L639" href="source/net/ipv4/devinet.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/devinet.c#L640">640</a>                         <b><i>/* We try to batch several events at once. */</i></b>
<a name="L641" href="source/net/ipv4/devinet.c#L641">641</a>                         age = (<a href="ident?i=now">now</a> - <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp +
<a name="L642" href="source/net/ipv4/devinet.c#L642">642</a>                                <a href="ident?i=ADDRCONF_TIMER_FUZZ_MINUS">ADDRCONF_TIMER_FUZZ_MINUS</a>) / <a href="ident?i=HZ">HZ</a>;
<a name="L643" href="source/net/ipv4/devinet.c#L643">643</a> 
<a name="L644" href="source/net/ipv4/devinet.c#L644">644</a>                         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft != <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a> &amp;&amp;
<a name="L645" href="source/net/ipv4/devinet.c#L645">645</a>                             age &gt;= <a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft) {
<a name="L646" href="source/net/ipv4/devinet.c#L646">646</a>                                 change_needed = <a href="ident?i=true">true</a>;
<a name="L647" href="source/net/ipv4/devinet.c#L647">647</a>                         } else if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft ==
<a name="L648" href="source/net/ipv4/devinet.c#L648">648</a>                                    <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>) {
<a name="L649" href="source/net/ipv4/devinet.c#L649">649</a>                                 continue;
<a name="L650" href="source/net/ipv4/devinet.c#L650">650</a>                         } else if (age &gt;= <a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft) {
<a name="L651" href="source/net/ipv4/devinet.c#L651">651</a>                                 if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp +
<a name="L652" href="source/net/ipv4/devinet.c#L652">652</a>                                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft * <a href="ident?i=HZ">HZ</a>, <a href="ident?i=next">next</a>))
<a name="L653" href="source/net/ipv4/devinet.c#L653">653</a>                                         <a href="ident?i=next">next</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp +
<a name="L654" href="source/net/ipv4/devinet.c#L654">654</a>                                                <a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft * <a href="ident?i=HZ">HZ</a>;
<a name="L655" href="source/net/ipv4/devinet.c#L655">655</a> 
<a name="L656" href="source/net/ipv4/devinet.c#L656">656</a>                                 if (!(<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_DEPRECATED">IFA_F_DEPRECATED</a>))
<a name="L657" href="source/net/ipv4/devinet.c#L657">657</a>                                         change_needed = <a href="ident?i=true">true</a>;
<a name="L658" href="source/net/ipv4/devinet.c#L658">658</a>                         } else if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp +
<a name="L659" href="source/net/ipv4/devinet.c#L659">659</a>                                                <a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft * <a href="ident?i=HZ">HZ</a>,
<a name="L660" href="source/net/ipv4/devinet.c#L660">660</a>                                                <a href="ident?i=next">next</a>)) {
<a name="L661" href="source/net/ipv4/devinet.c#L661">661</a>                                 <a href="ident?i=next">next</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp +
<a name="L662" href="source/net/ipv4/devinet.c#L662">662</a>                                        <a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft * <a href="ident?i=HZ">HZ</a>;
<a name="L663" href="source/net/ipv4/devinet.c#L663">663</a>                         }
<a name="L664" href="source/net/ipv4/devinet.c#L664">664</a>                 }
<a name="L665" href="source/net/ipv4/devinet.c#L665">665</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L666" href="source/net/ipv4/devinet.c#L666">666</a>                 if (!change_needed)
<a name="L667" href="source/net/ipv4/devinet.c#L667">667</a>                         continue;
<a name="L668" href="source/net/ipv4/devinet.c#L668">668</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L669" href="source/net/ipv4/devinet.c#L669">669</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(<a href="ident?i=ifa">ifa</a>, <a href="ident?i=n">n</a>, &amp;<a href="ident?i=inet_addr_lst">inet_addr_lst</a>[<a href="ident?i=i">i</a>], <a href="ident?i=hash">hash</a>) {
<a name="L670" href="source/net/ipv4/devinet.c#L670">670</a>                         unsigned long age;
<a name="L671" href="source/net/ipv4/devinet.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/devinet.c#L672">672</a>                         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_PERMANENT">IFA_F_PERMANENT</a>)
<a name="L673" href="source/net/ipv4/devinet.c#L673">673</a>                                 continue;
<a name="L674" href="source/net/ipv4/devinet.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/devinet.c#L675">675</a>                         <b><i>/* We try to batch several events at once. */</i></b>
<a name="L676" href="source/net/ipv4/devinet.c#L676">676</a>                         age = (<a href="ident?i=now">now</a> - <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp +
<a name="L677" href="source/net/ipv4/devinet.c#L677">677</a>                                <a href="ident?i=ADDRCONF_TIMER_FUZZ_MINUS">ADDRCONF_TIMER_FUZZ_MINUS</a>) / <a href="ident?i=HZ">HZ</a>;
<a name="L678" href="source/net/ipv4/devinet.c#L678">678</a> 
<a name="L679" href="source/net/ipv4/devinet.c#L679">679</a>                         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft != <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a> &amp;&amp;
<a name="L680" href="source/net/ipv4/devinet.c#L680">680</a>                             age &gt;= <a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft) {
<a name="L681" href="source/net/ipv4/devinet.c#L681">681</a>                                 struct <a href="ident?i=in_ifaddr">in_ifaddr</a> **ifap;
<a name="L682" href="source/net/ipv4/devinet.c#L682">682</a> 
<a name="L683" href="source/net/ipv4/devinet.c#L683">683</a>                                 for (ifap = &amp;<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;ifa_list;
<a name="L684" href="source/net/ipv4/devinet.c#L684">684</a>                                      *ifap != <a href="ident?i=NULL">NULL</a>; ifap = &amp;(*ifap)-&gt;ifa_next) {
<a name="L685" href="source/net/ipv4/devinet.c#L685">685</a>                                         if (*ifap == <a href="ident?i=ifa">ifa</a>) {
<a name="L686" href="source/net/ipv4/devinet.c#L686">686</a>                                                 <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev,
<a name="L687" href="source/net/ipv4/devinet.c#L687">687</a>                                                              ifap, 1);
<a name="L688" href="source/net/ipv4/devinet.c#L688">688</a>                                                 break;
<a name="L689" href="source/net/ipv4/devinet.c#L689">689</a>                                         }
<a name="L690" href="source/net/ipv4/devinet.c#L690">690</a>                                 }
<a name="L691" href="source/net/ipv4/devinet.c#L691">691</a>                         } else if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft !=
<a name="L692" href="source/net/ipv4/devinet.c#L692">692</a>                                    <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a> &amp;&amp;
<a name="L693" href="source/net/ipv4/devinet.c#L693">693</a>                                    age &gt;= <a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft &amp;&amp;
<a name="L694" href="source/net/ipv4/devinet.c#L694">694</a>                                    !(<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_DEPRECATED">IFA_F_DEPRECATED</a>)) {
<a name="L695" href="source/net/ipv4/devinet.c#L695">695</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags |= <a href="ident?i=IFA_F_DEPRECATED">IFA_F_DEPRECATED</a>;
<a name="L696" href="source/net/ipv4/devinet.c#L696">696</a>                                 <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=ifa">ifa</a>, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L697" href="source/net/ipv4/devinet.c#L697">697</a>                         }
<a name="L698" href="source/net/ipv4/devinet.c#L698">698</a>                 }
<a name="L699" href="source/net/ipv4/devinet.c#L699">699</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L700" href="source/net/ipv4/devinet.c#L700">700</a>         }
<a name="L701" href="source/net/ipv4/devinet.c#L701">701</a> 
<a name="L702" href="source/net/ipv4/devinet.c#L702">702</a>         next_sec = <a href="ident?i=round_jiffies_up">round_jiffies_up</a>(<a href="ident?i=next">next</a>);
<a name="L703" href="source/net/ipv4/devinet.c#L703">703</a>         next_sched = <a href="ident?i=next">next</a>;
<a name="L704" href="source/net/ipv4/devinet.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/devinet.c#L705">705</a>         <b><i>/* If rounded timeout is accurate enough, accept it. */</i></b>
<a name="L706" href="source/net/ipv4/devinet.c#L706">706</a>         if (<a href="ident?i=time_before">time_before</a>(next_sec, <a href="ident?i=next">next</a> + <a href="ident?i=ADDRCONF_TIMER_FUZZ">ADDRCONF_TIMER_FUZZ</a>))
<a name="L707" href="source/net/ipv4/devinet.c#L707">707</a>                 next_sched = next_sec;
<a name="L708" href="source/net/ipv4/devinet.c#L708">708</a> 
<a name="L709" href="source/net/ipv4/devinet.c#L709">709</a>         <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L710" href="source/net/ipv4/devinet.c#L710">710</a>         <b><i>/* And minimum interval is ADDRCONF_TIMER_FUZZ_MAX. */</i></b>
<a name="L711" href="source/net/ipv4/devinet.c#L711">711</a>         if (<a href="ident?i=time_before">time_before</a>(next_sched, <a href="ident?i=now">now</a> + <a href="ident?i=ADDRCONF_TIMER_FUZZ_MAX">ADDRCONF_TIMER_FUZZ_MAX</a>))
<a name="L712" href="source/net/ipv4/devinet.c#L712">712</a>                 next_sched = <a href="ident?i=now">now</a> + <a href="ident?i=ADDRCONF_TIMER_FUZZ_MAX">ADDRCONF_TIMER_FUZZ_MAX</a>;
<a name="L713" href="source/net/ipv4/devinet.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/devinet.c#L714">714</a>         <a href="ident?i=queue_delayed_work">queue_delayed_work</a>(<a href="ident?i=system_power_efficient_wq">system_power_efficient_wq</a>, &amp;check_lifetime_work,
<a name="L715" href="source/net/ipv4/devinet.c#L715">715</a>                         next_sched - <a href="ident?i=now">now</a>);
<a name="L716" href="source/net/ipv4/devinet.c#L716">716</a> }
<a name="L717" href="source/net/ipv4/devinet.c#L717">717</a> 
<a name="L718" href="source/net/ipv4/devinet.c#L718">718</a> static void <a href="ident?i=set_ifa_lifetime">set_ifa_lifetime</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>, <a href="ident?i=__u32">__u32</a> valid_lft,
<a name="L719" href="source/net/ipv4/devinet.c#L719">719</a>                              <a href="ident?i=__u32">__u32</a> prefered_lft)
<a name="L720" href="source/net/ipv4/devinet.c#L720">720</a> {
<a name="L721" href="source/net/ipv4/devinet.c#L721">721</a>         unsigned long <a href="ident?i=timeout">timeout</a>;
<a name="L722" href="source/net/ipv4/devinet.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/devinet.c#L723">723</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp;= ~(<a href="ident?i=IFA_F_PERMANENT">IFA_F_PERMANENT</a> | <a href="ident?i=IFA_F_DEPRECATED">IFA_F_DEPRECATED</a>);
<a name="L724" href="source/net/ipv4/devinet.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/devinet.c#L725">725</a>         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=addrconf_timeout_fixup">addrconf_timeout_fixup</a>(valid_lft, <a href="ident?i=HZ">HZ</a>);
<a name="L726" href="source/net/ipv4/devinet.c#L726">726</a>         if (<a href="ident?i=addrconf_finite_timeout">addrconf_finite_timeout</a>(<a href="ident?i=timeout">timeout</a>))
<a name="L727" href="source/net/ipv4/devinet.c#L727">727</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft = <a href="ident?i=timeout">timeout</a>;
<a name="L728" href="source/net/ipv4/devinet.c#L728">728</a>         else
<a name="L729" href="source/net/ipv4/devinet.c#L729">729</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags |= <a href="ident?i=IFA_F_PERMANENT">IFA_F_PERMANENT</a>;
<a name="L730" href="source/net/ipv4/devinet.c#L730">730</a> 
<a name="L731" href="source/net/ipv4/devinet.c#L731">731</a>         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=addrconf_timeout_fixup">addrconf_timeout_fixup</a>(prefered_lft, <a href="ident?i=HZ">HZ</a>);
<a name="L732" href="source/net/ipv4/devinet.c#L732">732</a>         if (<a href="ident?i=addrconf_finite_timeout">addrconf_finite_timeout</a>(<a href="ident?i=timeout">timeout</a>)) {
<a name="L733" href="source/net/ipv4/devinet.c#L733">733</a>                 if (<a href="ident?i=timeout">timeout</a> == 0)
<a name="L734" href="source/net/ipv4/devinet.c#L734">734</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags |= <a href="ident?i=IFA_F_DEPRECATED">IFA_F_DEPRECATED</a>;
<a name="L735" href="source/net/ipv4/devinet.c#L735">735</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft = <a href="ident?i=timeout">timeout</a>;
<a name="L736" href="source/net/ipv4/devinet.c#L736">736</a>         }
<a name="L737" href="source/net/ipv4/devinet.c#L737">737</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp = <a href="ident?i=jiffies">jiffies</a>;
<a name="L738" href="source/net/ipv4/devinet.c#L738">738</a>         if (!<a href="ident?i=ifa">ifa</a>-&gt;ifa_cstamp)
<a name="L739" href="source/net/ipv4/devinet.c#L739">739</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_cstamp = <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp;
<a name="L740" href="source/net/ipv4/devinet.c#L740">740</a> }
<a name="L741" href="source/net/ipv4/devinet.c#L741">741</a> 
<a name="L742" href="source/net/ipv4/devinet.c#L742">742</a> static struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=rtm_to_ifaddr">rtm_to_ifaddr</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L743" href="source/net/ipv4/devinet.c#L743">743</a>                                        <a href="ident?i=__u32">__u32</a> *pvalid_lft, <a href="ident?i=__u32">__u32</a> *pprefered_lft)
<a name="L744" href="source/net/ipv4/devinet.c#L744">744</a> {
<a name="L745" href="source/net/ipv4/devinet.c#L745">745</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[<a href="ident?i=IFA_MAX">IFA_MAX</a>+1];
<a name="L746" href="source/net/ipv4/devinet.c#L746">746</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L747" href="source/net/ipv4/devinet.c#L747">747</a>         struct <a href="ident?i=ifaddrmsg">ifaddrmsg</a> *ifm;
<a name="L748" href="source/net/ipv4/devinet.c#L748">748</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L749" href="source/net/ipv4/devinet.c#L749">749</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L750" href="source/net/ipv4/devinet.c#L750">750</a>         int <a href="ident?i=err">err</a>;
<a name="L751" href="source/net/ipv4/devinet.c#L751">751</a> 
<a name="L752" href="source/net/ipv4/devinet.c#L752">752</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nlmsg_parse">nlmsg_parse</a>(nlh, sizeof(*ifm), <a href="ident?i=tb">tb</a>, <a href="ident?i=IFA_MAX">IFA_MAX</a>, <a href="ident?i=ifa_ipv4_policy">ifa_ipv4_policy</a>);
<a name="L753" href="source/net/ipv4/devinet.c#L753">753</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L754" href="source/net/ipv4/devinet.c#L754">754</a>                 goto errout;
<a name="L755" href="source/net/ipv4/devinet.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/devinet.c#L756">756</a>         ifm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L757" href="source/net/ipv4/devinet.c#L757">757</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L758" href="source/net/ipv4/devinet.c#L758">758</a>         if (ifm-&gt;ifa_prefixlen &gt; 32 || !<a href="ident?i=tb">tb</a>[IFA_LOCAL])
<a name="L759" href="source/net/ipv4/devinet.c#L759">759</a>                 goto errout;
<a name="L760" href="source/net/ipv4/devinet.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/devinet.c#L761">761</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_index">__dev_get_by_index</a>(<a href="ident?i=net">net</a>, ifm-&gt;ifa_index);
<a name="L762" href="source/net/ipv4/devinet.c#L762">762</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L763" href="source/net/ipv4/devinet.c#L763">763</a>         if (!<a href="ident?i=dev">dev</a>)
<a name="L764" href="source/net/ipv4/devinet.c#L764">764</a>                 goto errout;
<a name="L765" href="source/net/ipv4/devinet.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/devinet.c#L766">766</a>         in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L767" href="source/net/ipv4/devinet.c#L767">767</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L768" href="source/net/ipv4/devinet.c#L768">768</a>         if (!in_dev)
<a name="L769" href="source/net/ipv4/devinet.c#L769">769</a>                 goto errout;
<a name="L770" href="source/net/ipv4/devinet.c#L770">770</a> 
<a name="L771" href="source/net/ipv4/devinet.c#L771">771</a>         <a href="ident?i=ifa">ifa</a> = <a href="ident?i=inet_alloc_ifa">inet_alloc_ifa</a>();
<a name="L772" href="source/net/ipv4/devinet.c#L772">772</a>         if (!<a href="ident?i=ifa">ifa</a>)
<a name="L773" href="source/net/ipv4/devinet.c#L773">773</a>                 <b><i>/*</i></b>
<a name="L774" href="source/net/ipv4/devinet.c#L774">774</a> <b><i>                 * A potential indev allocation can be left alive, it stays</i></b>
<a name="L775" href="source/net/ipv4/devinet.c#L775">775</a> <b><i>                 * assigned to its device and is destroy with it.</i></b>
<a name="L776" href="source/net/ipv4/devinet.c#L776">776</a> <b><i>                 */</i></b>
<a name="L777" href="source/net/ipv4/devinet.c#L777">777</a>                 goto errout;
<a name="L778" href="source/net/ipv4/devinet.c#L778">778</a> 
<a name="L779" href="source/net/ipv4/devinet.c#L779">779</a>         <a href="ident?i=ipv4_devconf_setall">ipv4_devconf_setall</a>(in_dev);
<a name="L780" href="source/net/ipv4/devinet.c#L780">780</a>         <a href="ident?i=neigh_parms_data_state_setall">neigh_parms_data_state_setall</a>(in_dev-&gt;arp_parms);
<a name="L781" href="source/net/ipv4/devinet.c#L781">781</a>         <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L782" href="source/net/ipv4/devinet.c#L782">782</a> 
<a name="L783" href="source/net/ipv4/devinet.c#L783">783</a>         if (!<a href="ident?i=tb">tb</a>[IFA_ADDRESS])
<a name="L784" href="source/net/ipv4/devinet.c#L784">784</a>                 <a href="ident?i=tb">tb</a>[IFA_ADDRESS] = <a href="ident?i=tb">tb</a>[IFA_LOCAL];
<a name="L785" href="source/net/ipv4/devinet.c#L785">785</a> 
<a name="L786" href="source/net/ipv4/devinet.c#L786">786</a>         <a href="ident?i=INIT_HLIST_NODE">INIT_HLIST_NODE</a>(&amp;<a href="ident?i=ifa">ifa</a>-&gt;<a href="ident?i=hash">hash</a>);
<a name="L787" href="source/net/ipv4/devinet.c#L787">787</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen = ifm-&gt;ifa_prefixlen;
<a name="L788" href="source/net/ipv4/devinet.c#L788">788</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask = <a href="ident?i=inet_make_mask">inet_make_mask</a>(ifm-&gt;ifa_prefixlen);
<a name="L789" href="source/net/ipv4/devinet.c#L789">789</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags = <a href="ident?i=tb">tb</a>[IFA_FLAGS] ? <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=tb">tb</a>[IFA_FLAGS]) :
<a name="L790" href="source/net/ipv4/devinet.c#L790">790</a>                                          ifm-&gt;ifa_flags;
<a name="L791" href="source/net/ipv4/devinet.c#L791">791</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope = ifm-&gt;ifa_scope;
<a name="L792" href="source/net/ipv4/devinet.c#L792">792</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev = in_dev;
<a name="L793" href="source/net/ipv4/devinet.c#L793">793</a> 
<a name="L794" href="source/net/ipv4/devinet.c#L794">794</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_local = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[IFA_LOCAL]);
<a name="L795" href="source/net/ipv4/devinet.c#L795">795</a>         <a href="ident?i=ifa">ifa</a>-&gt;ifa_address = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[IFA_ADDRESS]);
<a name="L796" href="source/net/ipv4/devinet.c#L796">796</a> 
<a name="L797" href="source/net/ipv4/devinet.c#L797">797</a>         if (<a href="ident?i=tb">tb</a>[IFA_BROADCAST])
<a name="L798" href="source/net/ipv4/devinet.c#L798">798</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[IFA_BROADCAST]);
<a name="L799" href="source/net/ipv4/devinet.c#L799">799</a> 
<a name="L800" href="source/net/ipv4/devinet.c#L800">800</a>         if (<a href="ident?i=tb">tb</a>[IFA_LABEL])
<a name="L801" href="source/net/ipv4/devinet.c#L801">801</a>                 <a href="ident?i=nla_strlcpy">nla_strlcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=tb">tb</a>[IFA_LABEL], <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L802" href="source/net/ipv4/devinet.c#L802">802</a>         else
<a name="L803" href="source/net/ipv4/devinet.c#L803">803</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L804" href="source/net/ipv4/devinet.c#L804">804</a> 
<a name="L805" href="source/net/ipv4/devinet.c#L805">805</a>         if (<a href="ident?i=tb">tb</a>[IFA_CACHEINFO]) {
<a name="L806" href="source/net/ipv4/devinet.c#L806">806</a>                 struct <a href="ident?i=ifa_cacheinfo">ifa_cacheinfo</a> *ci;
<a name="L807" href="source/net/ipv4/devinet.c#L807">807</a> 
<a name="L808" href="source/net/ipv4/devinet.c#L808">808</a>                 ci = <a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=tb">tb</a>[IFA_CACHEINFO]);
<a name="L809" href="source/net/ipv4/devinet.c#L809">809</a>                 if (!ci-&gt;ifa_valid || ci-&gt;ifa_prefered &gt; ci-&gt;ifa_valid) {
<a name="L810" href="source/net/ipv4/devinet.c#L810">810</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L811" href="source/net/ipv4/devinet.c#L811">811</a>                         goto errout_free;
<a name="L812" href="source/net/ipv4/devinet.c#L812">812</a>                 }
<a name="L813" href="source/net/ipv4/devinet.c#L813">813</a>                 *pvalid_lft = ci-&gt;ifa_valid;
<a name="L814" href="source/net/ipv4/devinet.c#L814">814</a>                 *pprefered_lft = ci-&gt;ifa_prefered;
<a name="L815" href="source/net/ipv4/devinet.c#L815">815</a>         }
<a name="L816" href="source/net/ipv4/devinet.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/devinet.c#L817">817</a>         return <a href="ident?i=ifa">ifa</a>;
<a name="L818" href="source/net/ipv4/devinet.c#L818">818</a> 
<a name="L819" href="source/net/ipv4/devinet.c#L819">819</a> errout_free:
<a name="L820" href="source/net/ipv4/devinet.c#L820">820</a>         <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L821" href="source/net/ipv4/devinet.c#L821">821</a> errout:
<a name="L822" href="source/net/ipv4/devinet.c#L822">822</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L823" href="source/net/ipv4/devinet.c#L823">823</a> }
<a name="L824" href="source/net/ipv4/devinet.c#L824">824</a> 
<a name="L825" href="source/net/ipv4/devinet.c#L825">825</a> static struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=find_matching_ifa">find_matching_ifa</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L826" href="source/net/ipv4/devinet.c#L826">826</a> {
<a name="L827" href="source/net/ipv4/devinet.c#L827">827</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev;
<a name="L828" href="source/net/ipv4/devinet.c#L828">828</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *ifa1, **ifap;
<a name="L829" href="source/net/ipv4/devinet.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/devinet.c#L830">830</a>         if (!<a href="ident?i=ifa">ifa</a>-&gt;ifa_local)
<a name="L831" href="source/net/ipv4/devinet.c#L831">831</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L832" href="source/net/ipv4/devinet.c#L832">832</a> 
<a name="L833" href="source/net/ipv4/devinet.c#L833">833</a>         for (ifap = &amp;in_dev-&gt;ifa_list; (ifa1 = *ifap) != <a href="ident?i=NULL">NULL</a>;
<a name="L834" href="source/net/ipv4/devinet.c#L834">834</a>              ifap = &amp;ifa1-&gt;ifa_next) {
<a name="L835" href="source/net/ipv4/devinet.c#L835">835</a>                 if (ifa1-&gt;ifa_mask == <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask &amp;&amp;
<a name="L836" href="source/net/ipv4/devinet.c#L836">836</a>                     <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, <a href="ident?i=ifa">ifa</a>) &amp;&amp;
<a name="L837" href="source/net/ipv4/devinet.c#L837">837</a>                     ifa1-&gt;ifa_local == <a href="ident?i=ifa">ifa</a>-&gt;ifa_local)
<a name="L838" href="source/net/ipv4/devinet.c#L838">838</a>                         return ifa1;
<a name="L839" href="source/net/ipv4/devinet.c#L839">839</a>         }
<a name="L840" href="source/net/ipv4/devinet.c#L840">840</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L841" href="source/net/ipv4/devinet.c#L841">841</a> }
<a name="L842" href="source/net/ipv4/devinet.c#L842">842</a> 
<a name="L843" href="source/net/ipv4/devinet.c#L843">843</a> static int <a href="ident?i=inet_rtm_newaddr">inet_rtm_newaddr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L844" href="source/net/ipv4/devinet.c#L844">844</a> {
<a name="L845" href="source/net/ipv4/devinet.c#L845">845</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L846" href="source/net/ipv4/devinet.c#L846">846</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L847" href="source/net/ipv4/devinet.c#L847">847</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *ifa_existing;
<a name="L848" href="source/net/ipv4/devinet.c#L848">848</a>         <a href="ident?i=__u32">__u32</a> valid_lft = <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>;
<a name="L849" href="source/net/ipv4/devinet.c#L849">849</a>         <a href="ident?i=__u32">__u32</a> prefered_lft = <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>;
<a name="L850" href="source/net/ipv4/devinet.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/devinet.c#L851">851</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L852" href="source/net/ipv4/devinet.c#L852">852</a> 
<a name="L853" href="source/net/ipv4/devinet.c#L853">853</a>         <a href="ident?i=ifa">ifa</a> = <a href="ident?i=rtm_to_ifaddr">rtm_to_ifaddr</a>(<a href="ident?i=net">net</a>, nlh, &amp;valid_lft, &amp;prefered_lft);
<a name="L854" href="source/net/ipv4/devinet.c#L854">854</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=ifa">ifa</a>))
<a name="L855" href="source/net/ipv4/devinet.c#L855">855</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L856" href="source/net/ipv4/devinet.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/devinet.c#L857">857</a>         ifa_existing = <a href="ident?i=find_matching_ifa">find_matching_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L858" href="source/net/ipv4/devinet.c#L858">858</a>         if (!ifa_existing) {
<a name="L859" href="source/net/ipv4/devinet.c#L859">859</a>                 <b><i>/* It would be best to check for !NLM_F_CREATE here but</i></b>
<a name="L860" href="source/net/ipv4/devinet.c#L860">860</a> <b><i>                 * userspace already relies on not having to provide this.</i></b>
<a name="L861" href="source/net/ipv4/devinet.c#L861">861</a> <b><i>                 */</i></b>
<a name="L862" href="source/net/ipv4/devinet.c#L862">862</a>                 <a href="ident?i=set_ifa_lifetime">set_ifa_lifetime</a>(<a href="ident?i=ifa">ifa</a>, valid_lft, prefered_lft);
<a name="L863" href="source/net/ipv4/devinet.c#L863">863</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_MCAUTOJOIN">IFA_F_MCAUTOJOIN</a>) {
<a name="L864" href="source/net/ipv4/devinet.c#L864">864</a>                         int <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_mc_config">ip_mc_config</a>(<a href="ident?i=net">net</a>-&gt;ipv4.mc_autojoin_sk,
<a name="L865" href="source/net/ipv4/devinet.c#L865">865</a>                                                <a href="ident?i=true">true</a>, <a href="ident?i=ifa">ifa</a>);
<a name="L866" href="source/net/ipv4/devinet.c#L866">866</a> 
<a name="L867" href="source/net/ipv4/devinet.c#L867">867</a>                         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L868" href="source/net/ipv4/devinet.c#L868">868</a>                                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L869" href="source/net/ipv4/devinet.c#L869">869</a>                                 return <a href="ident?i=ret">ret</a>;
<a name="L870" href="source/net/ipv4/devinet.c#L870">870</a>                         }
<a name="L871" href="source/net/ipv4/devinet.c#L871">871</a>                 }
<a name="L872" href="source/net/ipv4/devinet.c#L872">872</a>                 return <a href="ident?i=__inet_insert_ifa">__inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>, nlh, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid);
<a name="L873" href="source/net/ipv4/devinet.c#L873">873</a>         } else {
<a name="L874" href="source/net/ipv4/devinet.c#L874">874</a>                 <a href="ident?i=inet_free_ifa">inet_free_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L875" href="source/net/ipv4/devinet.c#L875">875</a> 
<a name="L876" href="source/net/ipv4/devinet.c#L876">876</a>                 if (nlh-&gt;nlmsg_flags &amp; <a href="ident?i=NLM_F_EXCL">NLM_F_EXCL</a> ||
<a name="L877" href="source/net/ipv4/devinet.c#L877">877</a>                     !(nlh-&gt;nlmsg_flags &amp; <a href="ident?i=NLM_F_REPLACE">NLM_F_REPLACE</a>))
<a name="L878" href="source/net/ipv4/devinet.c#L878">878</a>                         return -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L879" href="source/net/ipv4/devinet.c#L879">879</a>                 <a href="ident?i=ifa">ifa</a> = ifa_existing;
<a name="L880" href="source/net/ipv4/devinet.c#L880">880</a>                 <a href="ident?i=set_ifa_lifetime">set_ifa_lifetime</a>(<a href="ident?i=ifa">ifa</a>, valid_lft, prefered_lft);
<a name="L881" href="source/net/ipv4/devinet.c#L881">881</a>                 <a href="ident?i=cancel_delayed_work">cancel_delayed_work</a>(&amp;check_lifetime_work);
<a name="L882" href="source/net/ipv4/devinet.c#L882">882</a>                 <a href="ident?i=queue_delayed_work">queue_delayed_work</a>(<a href="ident?i=system_power_efficient_wq">system_power_efficient_wq</a>,
<a name="L883" href="source/net/ipv4/devinet.c#L883">883</a>                                 &amp;check_lifetime_work, 0);
<a name="L884" href="source/net/ipv4/devinet.c#L884">884</a>                 <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=ifa">ifa</a>, nlh, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid);
<a name="L885" href="source/net/ipv4/devinet.c#L885">885</a>                 <a href="ident?i=blocking_notifier_call_chain">blocking_notifier_call_chain</a>(&amp;inetaddr_chain, <a href="ident?i=NETDEV_UP">NETDEV_UP</a>, <a href="ident?i=ifa">ifa</a>);
<a name="L886" href="source/net/ipv4/devinet.c#L886">886</a>         }
<a name="L887" href="source/net/ipv4/devinet.c#L887">887</a>         return 0;
<a name="L888" href="source/net/ipv4/devinet.c#L888">888</a> }
<a name="L889" href="source/net/ipv4/devinet.c#L889">889</a> 
<a name="L890" href="source/net/ipv4/devinet.c#L890">890</a> <b><i>/*</i></b>
<a name="L891" href="source/net/ipv4/devinet.c#L891">891</a> <b><i> *      Determine a default network mask, based on the IP address.</i></b>
<a name="L892" href="source/net/ipv4/devinet.c#L892">892</a> <b><i> */</i></b>
<a name="L893" href="source/net/ipv4/devinet.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/devinet.c#L894">894</a> static int <a href="ident?i=inet_abc_len">inet_abc_len</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L895" href="source/net/ipv4/devinet.c#L895">895</a> {
<a name="L896" href="source/net/ipv4/devinet.c#L896">896</a>         int <a href="ident?i=rc">rc</a> = -1;    <b><i>/* Something else, probably a multicast. */</i></b>
<a name="L897" href="source/net/ipv4/devinet.c#L897">897</a> 
<a name="L898" href="source/net/ipv4/devinet.c#L898">898</a>         if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=addr">addr</a>))
<a name="L899" href="source/net/ipv4/devinet.c#L899">899</a>                 <a href="ident?i=rc">rc</a> = 0;
<a name="L900" href="source/net/ipv4/devinet.c#L900">900</a>         else {
<a name="L901" href="source/net/ipv4/devinet.c#L901">901</a>                 <a href="ident?i=__u32">__u32</a> haddr = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=addr">addr</a>);
<a name="L902" href="source/net/ipv4/devinet.c#L902">902</a> 
<a name="L903" href="source/net/ipv4/devinet.c#L903">903</a>                 if (<a href="ident?i=IN_CLASSA">IN_CLASSA</a>(haddr))
<a name="L904" href="source/net/ipv4/devinet.c#L904">904</a>                         <a href="ident?i=rc">rc</a> = 8;
<a name="L905" href="source/net/ipv4/devinet.c#L905">905</a>                 else if (<a href="ident?i=IN_CLASSB">IN_CLASSB</a>(haddr))
<a name="L906" href="source/net/ipv4/devinet.c#L906">906</a>                         <a href="ident?i=rc">rc</a> = 16;
<a name="L907" href="source/net/ipv4/devinet.c#L907">907</a>                 else if (<a href="ident?i=IN_CLASSC">IN_CLASSC</a>(haddr))
<a name="L908" href="source/net/ipv4/devinet.c#L908">908</a>                         <a href="ident?i=rc">rc</a> = 24;
<a name="L909" href="source/net/ipv4/devinet.c#L909">909</a>         }
<a name="L910" href="source/net/ipv4/devinet.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/devinet.c#L911">911</a>         return <a href="ident?i=rc">rc</a>;
<a name="L912" href="source/net/ipv4/devinet.c#L912">912</a> }
<a name="L913" href="source/net/ipv4/devinet.c#L913">913</a> 
<a name="L914" href="source/net/ipv4/devinet.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/devinet.c#L915">915</a> int <a href="ident?i=devinet_ioctl">devinet_ioctl</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=arg">arg</a>)
<a name="L916" href="source/net/ipv4/devinet.c#L916">916</a> {
<a name="L917" href="source/net/ipv4/devinet.c#L917">917</a>         struct <a href="ident?i=ifreq">ifreq</a> ifr;
<a name="L918" href="source/net/ipv4/devinet.c#L918">918</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> sin_orig;
<a name="L919" href="source/net/ipv4/devinet.c#L919">919</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=sin">sin</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;ifr.<a href="ident?i=ifr_addr">ifr_addr</a>;
<a name="L920" href="source/net/ipv4/devinet.c#L920">920</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L921" href="source/net/ipv4/devinet.c#L921">921</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> **ifap = <a href="ident?i=NULL">NULL</a>;
<a name="L922" href="source/net/ipv4/devinet.c#L922">922</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L923" href="source/net/ipv4/devinet.c#L923">923</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L924" href="source/net/ipv4/devinet.c#L924">924</a>         char *colon;
<a name="L925" href="source/net/ipv4/devinet.c#L925">925</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L926" href="source/net/ipv4/devinet.c#L926">926</a>         int tryaddrmatch = 0;
<a name="L927" href="source/net/ipv4/devinet.c#L927">927</a> 
<a name="L928" href="source/net/ipv4/devinet.c#L928">928</a>         <b><i>/*</i></b>
<a name="L929" href="source/net/ipv4/devinet.c#L929">929</a> <b><i>         *      Fetch the caller's info block into kernel space</i></b>
<a name="L930" href="source/net/ipv4/devinet.c#L930">930</a> <b><i>         */</i></b>
<a name="L931" href="source/net/ipv4/devinet.c#L931">931</a> 
<a name="L932" href="source/net/ipv4/devinet.c#L932">932</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;ifr, <a href="ident?i=arg">arg</a>, sizeof(struct <a href="ident?i=ifreq">ifreq</a>)))
<a name="L933" href="source/net/ipv4/devinet.c#L933">933</a>                 goto <a href="ident?i=out">out</a>;
<a name="L934" href="source/net/ipv4/devinet.c#L934">934</a>         ifr.<a href="ident?i=ifr_name">ifr_name</a>[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a> - 1] = 0;
<a name="L935" href="source/net/ipv4/devinet.c#L935">935</a> 
<a name="L936" href="source/net/ipv4/devinet.c#L936">936</a>         <b><i>/* save original address for comparison */</i></b>
<a name="L937" href="source/net/ipv4/devinet.c#L937">937</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;sin_orig, <a href="ident?i=sin">sin</a>, sizeof(*<a href="ident?i=sin">sin</a>));
<a name="L938" href="source/net/ipv4/devinet.c#L938">938</a> 
<a name="L939" href="source/net/ipv4/devinet.c#L939">939</a>         colon = <a href="ident?i=strchr">strchr</a>(ifr.<a href="ident?i=ifr_name">ifr_name</a>, <i>':'</i>);
<a name="L940" href="source/net/ipv4/devinet.c#L940">940</a>         if (colon)
<a name="L941" href="source/net/ipv4/devinet.c#L941">941</a>                 *colon = 0;
<a name="L942" href="source/net/ipv4/devinet.c#L942">942</a> 
<a name="L943" href="source/net/ipv4/devinet.c#L943">943</a>         <a href="ident?i=dev_load">dev_load</a>(<a href="ident?i=net">net</a>, ifr.<a href="ident?i=ifr_name">ifr_name</a>);
<a name="L944" href="source/net/ipv4/devinet.c#L944">944</a> 
<a name="L945" href="source/net/ipv4/devinet.c#L945">945</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L946" href="source/net/ipv4/devinet.c#L946">946</a>         case <a href="ident?i=SIOCGIFADDR">SIOCGIFADDR</a>:       <b><i>/* Get interface address */</i></b>
<a name="L947" href="source/net/ipv4/devinet.c#L947">947</a>         case <a href="ident?i=SIOCGIFBRDADDR">SIOCGIFBRDADDR</a>:    <b><i>/* Get the broadcast address */</i></b>
<a name="L948" href="source/net/ipv4/devinet.c#L948">948</a>         case <a href="ident?i=SIOCGIFDSTADDR">SIOCGIFDSTADDR</a>:    <b><i>/* Get the destination address */</i></b>
<a name="L949" href="source/net/ipv4/devinet.c#L949">949</a>         case <a href="ident?i=SIOCGIFNETMASK">SIOCGIFNETMASK</a>:    <b><i>/* Get the netmask for the interface */</i></b>
<a name="L950" href="source/net/ipv4/devinet.c#L950">950</a>                 <b><i>/* Note that these ioctls will not sleep,</i></b>
<a name="L951" href="source/net/ipv4/devinet.c#L951">951</a> <b><i>                   so that we do not impose a lock.</i></b>
<a name="L952" href="source/net/ipv4/devinet.c#L952">952</a> <b><i>                   One day we will be forced to put shlock here (I mean SMP)</i></b>
<a name="L953" href="source/net/ipv4/devinet.c#L953">953</a> <b><i>                 */</i></b>
<a name="L954" href="source/net/ipv4/devinet.c#L954">954</a>                 tryaddrmatch = (sin_orig.sin_family == <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L955" href="source/net/ipv4/devinet.c#L955">955</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>, 0, sizeof(*<a href="ident?i=sin">sin</a>));
<a name="L956" href="source/net/ipv4/devinet.c#L956">956</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L957" href="source/net/ipv4/devinet.c#L957">957</a>                 break;
<a name="L958" href="source/net/ipv4/devinet.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/devinet.c#L959">959</a>         case <a href="ident?i=SIOCSIFFLAGS">SIOCSIFFLAGS</a>:
<a name="L960" href="source/net/ipv4/devinet.c#L960">960</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L961" href="source/net/ipv4/devinet.c#L961">961</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L962" href="source/net/ipv4/devinet.c#L962">962</a>                         goto <a href="ident?i=out">out</a>;
<a name="L963" href="source/net/ipv4/devinet.c#L963">963</a>                 break;
<a name="L964" href="source/net/ipv4/devinet.c#L964">964</a>         case <a href="ident?i=SIOCSIFADDR">SIOCSIFADDR</a>:       <b><i>/* Set interface address (and family) */</i></b>
<a name="L965" href="source/net/ipv4/devinet.c#L965">965</a>         case <a href="ident?i=SIOCSIFBRDADDR">SIOCSIFBRDADDR</a>:    <b><i>/* Set the broadcast address */</i></b>
<a name="L966" href="source/net/ipv4/devinet.c#L966">966</a>         case <a href="ident?i=SIOCSIFDSTADDR">SIOCSIFDSTADDR</a>:    <b><i>/* Set the destination address */</i></b>
<a name="L967" href="source/net/ipv4/devinet.c#L967">967</a>         case <a href="ident?i=SIOCSIFNETMASK">SIOCSIFNETMASK</a>:    <b><i>/* Set the netmask for the interface */</i></b>
<a name="L968" href="source/net/ipv4/devinet.c#L968">968</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L969" href="source/net/ipv4/devinet.c#L969">969</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L970" href="source/net/ipv4/devinet.c#L970">970</a>                         goto <a href="ident?i=out">out</a>;
<a name="L971" href="source/net/ipv4/devinet.c#L971">971</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L972" href="source/net/ipv4/devinet.c#L972">972</a>                 if (<a href="ident?i=sin">sin</a>-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L973" href="source/net/ipv4/devinet.c#L973">973</a>                         goto <a href="ident?i=out">out</a>;
<a name="L974" href="source/net/ipv4/devinet.c#L974">974</a>                 break;
<a name="L975" href="source/net/ipv4/devinet.c#L975">975</a>         default:
<a name="L976" href="source/net/ipv4/devinet.c#L976">976</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L977" href="source/net/ipv4/devinet.c#L977">977</a>                 goto <a href="ident?i=out">out</a>;
<a name="L978" href="source/net/ipv4/devinet.c#L978">978</a>         }
<a name="L979" href="source/net/ipv4/devinet.c#L979">979</a> 
<a name="L980" href="source/net/ipv4/devinet.c#L980">980</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L981" href="source/net/ipv4/devinet.c#L981">981</a> 
<a name="L982" href="source/net/ipv4/devinet.c#L982">982</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L983" href="source/net/ipv4/devinet.c#L983">983</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_name">__dev_get_by_name</a>(<a href="ident?i=net">net</a>, ifr.<a href="ident?i=ifr_name">ifr_name</a>);
<a name="L984" href="source/net/ipv4/devinet.c#L984">984</a>         if (!<a href="ident?i=dev">dev</a>)
<a name="L985" href="source/net/ipv4/devinet.c#L985">985</a>                 goto <a href="ident?i=done">done</a>;
<a name="L986" href="source/net/ipv4/devinet.c#L986">986</a> 
<a name="L987" href="source/net/ipv4/devinet.c#L987">987</a>         if (colon)
<a name="L988" href="source/net/ipv4/devinet.c#L988">988</a>                 *colon = <i>':'</i>;
<a name="L989" href="source/net/ipv4/devinet.c#L989">989</a> 
<a name="L990" href="source/net/ipv4/devinet.c#L990">990</a>         in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L991" href="source/net/ipv4/devinet.c#L991">991</a>         if (in_dev) {
<a name="L992" href="source/net/ipv4/devinet.c#L992">992</a>                 if (tryaddrmatch) {
<a name="L993" href="source/net/ipv4/devinet.c#L993">993</a>                         <b><i>/* Matthias Andree */</i></b>
<a name="L994" href="source/net/ipv4/devinet.c#L994">994</a>                         <b><i>/* compare label and address (4.4BSD style) */</i></b>
<a name="L995" href="source/net/ipv4/devinet.c#L995">995</a>                         <b><i>/* note: we only do this for a limited set of ioctls</i></b>
<a name="L996" href="source/net/ipv4/devinet.c#L996">996</a> <b><i>                           and only if the original address family was AF_INET.</i></b>
<a name="L997" href="source/net/ipv4/devinet.c#L997">997</a> <b><i>                           This is checked above. */</i></b>
<a name="L998" href="source/net/ipv4/devinet.c#L998">998</a>                         for (ifap = &amp;in_dev-&gt;ifa_list; (<a href="ident?i=ifa">ifa</a> = *ifap) != <a href="ident?i=NULL">NULL</a>;
<a name="L999" href="source/net/ipv4/devinet.c#L999">999</a>                              ifap = &amp;<a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L1000" href="source/net/ipv4/devinet.c#L1000">1000</a>                                 if (!<a href="ident?i=strcmp">strcmp</a>(ifr.<a href="ident?i=ifr_name">ifr_name</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_label) &amp;&amp;
<a name="L1001" href="source/net/ipv4/devinet.c#L1001">1001</a>                                     sin_orig.sin_addr.s_addr ==
<a name="L1002" href="source/net/ipv4/devinet.c#L1002">1002</a>                                                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_local) {
<a name="L1003" href="source/net/ipv4/devinet.c#L1003">1003</a>                                         break; <b><i>/* found */</i></b>
<a name="L1004" href="source/net/ipv4/devinet.c#L1004">1004</a>                                 }
<a name="L1005" href="source/net/ipv4/devinet.c#L1005">1005</a>                         }
<a name="L1006" href="source/net/ipv4/devinet.c#L1006">1006</a>                 }
<a name="L1007" href="source/net/ipv4/devinet.c#L1007">1007</a>                 <b><i>/* we didn't get a match, maybe the application is</i></b>
<a name="L1008" href="source/net/ipv4/devinet.c#L1008">1008</a> <b><i>                   4.3BSD-style and passed in junk so we fall back to</i></b>
<a name="L1009" href="source/net/ipv4/devinet.c#L1009">1009</a> <b><i>                   comparing just the label */</i></b>
<a name="L1010" href="source/net/ipv4/devinet.c#L1010">1010</a>                 if (!<a href="ident?i=ifa">ifa</a>) {
<a name="L1011" href="source/net/ipv4/devinet.c#L1011">1011</a>                         for (ifap = &amp;in_dev-&gt;ifa_list; (<a href="ident?i=ifa">ifa</a> = *ifap) != <a href="ident?i=NULL">NULL</a>;
<a name="L1012" href="source/net/ipv4/devinet.c#L1012">1012</a>                              ifap = &amp;<a href="ident?i=ifa">ifa</a>-&gt;ifa_next)
<a name="L1013" href="source/net/ipv4/devinet.c#L1013">1013</a>                                 if (!<a href="ident?i=strcmp">strcmp</a>(ifr.<a href="ident?i=ifr_name">ifr_name</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_label))
<a name="L1014" href="source/net/ipv4/devinet.c#L1014">1014</a>                                         break;
<a name="L1015" href="source/net/ipv4/devinet.c#L1015">1015</a>                 }
<a name="L1016" href="source/net/ipv4/devinet.c#L1016">1016</a>         }
<a name="L1017" href="source/net/ipv4/devinet.c#L1017">1017</a> 
<a name="L1018" href="source/net/ipv4/devinet.c#L1018">1018</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1019" href="source/net/ipv4/devinet.c#L1019">1019</a>         if (!<a href="ident?i=ifa">ifa</a> &amp;&amp; <a href="ident?i=cmd">cmd</a> != <a href="ident?i=SIOCSIFADDR">SIOCSIFADDR</a> &amp;&amp; <a href="ident?i=cmd">cmd</a> != <a href="ident?i=SIOCSIFFLAGS">SIOCSIFFLAGS</a>)
<a name="L1020" href="source/net/ipv4/devinet.c#L1020">1020</a>                 goto <a href="ident?i=done">done</a>;
<a name="L1021" href="source/net/ipv4/devinet.c#L1021">1021</a> 
<a name="L1022" href="source/net/ipv4/devinet.c#L1022">1022</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1023" href="source/net/ipv4/devinet.c#L1023">1023</a>         case <a href="ident?i=SIOCGIFADDR">SIOCGIFADDR</a>:       <b><i>/* Get interface address */</i></b>
<a name="L1024" href="source/net/ipv4/devinet.c#L1024">1024</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1025" href="source/net/ipv4/devinet.c#L1025">1025</a>                 goto rarok;
<a name="L1026" href="source/net/ipv4/devinet.c#L1026">1026</a> 
<a name="L1027" href="source/net/ipv4/devinet.c#L1027">1027</a>         case <a href="ident?i=SIOCGIFBRDADDR">SIOCGIFBRDADDR</a>:    <b><i>/* Get the broadcast address */</i></b>
<a name="L1028" href="source/net/ipv4/devinet.c#L1028">1028</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast;
<a name="L1029" href="source/net/ipv4/devinet.c#L1029">1029</a>                 goto rarok;
<a name="L1030" href="source/net/ipv4/devinet.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/devinet.c#L1031">1031</a>         case <a href="ident?i=SIOCGIFDSTADDR">SIOCGIFDSTADDR</a>:    <b><i>/* Get the destination address */</i></b>
<a name="L1032" href="source/net/ipv4/devinet.c#L1032">1032</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ifa">ifa</a>-&gt;ifa_address;
<a name="L1033" href="source/net/ipv4/devinet.c#L1033">1033</a>                 goto rarok;
<a name="L1034" href="source/net/ipv4/devinet.c#L1034">1034</a> 
<a name="L1035" href="source/net/ipv4/devinet.c#L1035">1035</a>         case <a href="ident?i=SIOCGIFNETMASK">SIOCGIFNETMASK</a>:    <b><i>/* Get the netmask for the interface */</i></b>
<a name="L1036" href="source/net/ipv4/devinet.c#L1036">1036</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask;
<a name="L1037" href="source/net/ipv4/devinet.c#L1037">1037</a>                 goto rarok;
<a name="L1038" href="source/net/ipv4/devinet.c#L1038">1038</a> 
<a name="L1039" href="source/net/ipv4/devinet.c#L1039">1039</a>         case <a href="ident?i=SIOCSIFFLAGS">SIOCSIFFLAGS</a>:
<a name="L1040" href="source/net/ipv4/devinet.c#L1040">1040</a>                 if (colon) {
<a name="L1041" href="source/net/ipv4/devinet.c#L1041">1041</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1042" href="source/net/ipv4/devinet.c#L1042">1042</a>                         if (!<a href="ident?i=ifa">ifa</a>)
<a name="L1043" href="source/net/ipv4/devinet.c#L1043">1043</a>                                 break;
<a name="L1044" href="source/net/ipv4/devinet.c#L1044">1044</a>                         <a href="ident?i=ret">ret</a> = 0;
<a name="L1045" href="source/net/ipv4/devinet.c#L1045">1045</a>                         if (!(ifr.<a href="ident?i=ifr_flags">ifr_flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L1046" href="source/net/ipv4/devinet.c#L1046">1046</a>                                 <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(in_dev, ifap, 1);
<a name="L1047" href="source/net/ipv4/devinet.c#L1047">1047</a>                         break;
<a name="L1048" href="source/net/ipv4/devinet.c#L1048">1048</a>                 }
<a name="L1049" href="source/net/ipv4/devinet.c#L1049">1049</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=dev_change_flags">dev_change_flags</a>(<a href="ident?i=dev">dev</a>, ifr.<a href="ident?i=ifr_flags">ifr_flags</a>);
<a name="L1050" href="source/net/ipv4/devinet.c#L1050">1050</a>                 break;
<a name="L1051" href="source/net/ipv4/devinet.c#L1051">1051</a> 
<a name="L1052" href="source/net/ipv4/devinet.c#L1052">1052</a>         case <a href="ident?i=SIOCSIFADDR">SIOCSIFADDR</a>:       <b><i>/* Set interface address (and family) */</i></b>
<a name="L1053" href="source/net/ipv4/devinet.c#L1053">1053</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1054" href="source/net/ipv4/devinet.c#L1054">1054</a>                 if (<a href="ident?i=inet_abc_len">inet_abc_len</a>(<a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr) &lt; 0)
<a name="L1055" href="source/net/ipv4/devinet.c#L1055">1055</a>                         break;
<a name="L1056" href="source/net/ipv4/devinet.c#L1056">1056</a> 
<a name="L1057" href="source/net/ipv4/devinet.c#L1057">1057</a>                 if (!<a href="ident?i=ifa">ifa</a>) {
<a name="L1058" href="source/net/ipv4/devinet.c#L1058">1058</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1059" href="source/net/ipv4/devinet.c#L1059">1059</a>                         <a href="ident?i=ifa">ifa</a> = <a href="ident?i=inet_alloc_ifa">inet_alloc_ifa</a>();
<a name="L1060" href="source/net/ipv4/devinet.c#L1060">1060</a>                         if (!<a href="ident?i=ifa">ifa</a>)
<a name="L1061" href="source/net/ipv4/devinet.c#L1061">1061</a>                                 break;
<a name="L1062" href="source/net/ipv4/devinet.c#L1062">1062</a>                         <a href="ident?i=INIT_HLIST_NODE">INIT_HLIST_NODE</a>(&amp;<a href="ident?i=ifa">ifa</a>-&gt;<a href="ident?i=hash">hash</a>);
<a name="L1063" href="source/net/ipv4/devinet.c#L1063">1063</a>                         if (colon)
<a name="L1064" href="source/net/ipv4/devinet.c#L1064">1064</a>                                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, ifr.<a href="ident?i=ifr_name">ifr_name</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L1065" href="source/net/ipv4/devinet.c#L1065">1065</a>                         else
<a name="L1066" href="source/net/ipv4/devinet.c#L1066">1066</a>                                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L1067" href="source/net/ipv4/devinet.c#L1067">1067</a>                 } else {
<a name="L1068" href="source/net/ipv4/devinet.c#L1068">1068</a>                         <a href="ident?i=ret">ret</a> = 0;
<a name="L1069" href="source/net/ipv4/devinet.c#L1069">1069</a>                         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_local == <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr)
<a name="L1070" href="source/net/ipv4/devinet.c#L1070">1070</a>                                 break;
<a name="L1071" href="source/net/ipv4/devinet.c#L1071">1071</a>                         <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(in_dev, ifap, 0);
<a name="L1072" href="source/net/ipv4/devinet.c#L1072">1072</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast = 0;
<a name="L1073" href="source/net/ipv4/devinet.c#L1073">1073</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope = 0;
<a name="L1074" href="source/net/ipv4/devinet.c#L1074">1074</a>                 }
<a name="L1075" href="source/net/ipv4/devinet.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/devinet.c#L1076">1076</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_address = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local = <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr;
<a name="L1077" href="source/net/ipv4/devinet.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/devinet.c#L1078">1078</a>                 if (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>)) {
<a name="L1079" href="source/net/ipv4/devinet.c#L1079">1079</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen = <a href="ident?i=inet_abc_len">inet_abc_len</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_address);
<a name="L1080" href="source/net/ipv4/devinet.c#L1080">1080</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask = <a href="ident?i=inet_make_mask">inet_make_mask</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen);
<a name="L1081" href="source/net/ipv4/devinet.c#L1081">1081</a>                         if ((<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>) &amp;&amp;
<a name="L1082" href="source/net/ipv4/devinet.c#L1082">1082</a>                             <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen &lt; 31)
<a name="L1083" href="source/net/ipv4/devinet.c#L1083">1083</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast = <a href="ident?i=ifa">ifa</a>-&gt;ifa_address |
<a name="L1084" href="source/net/ipv4/devinet.c#L1084">1084</a>                                                      ~ifa-&gt;ifa_mask;
<a name="L1085" href="source/net/ipv4/devinet.c#L1085">1085</a>                 } else {
<a name="L1086" href="source/net/ipv4/devinet.c#L1086">1086</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen = 32;
<a name="L1087" href="source/net/ipv4/devinet.c#L1087">1087</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask = <a href="ident?i=inet_make_mask">inet_make_mask</a>(32);
<a name="L1088" href="source/net/ipv4/devinet.c#L1088">1088</a>                 }
<a name="L1089" href="source/net/ipv4/devinet.c#L1089">1089</a>                 <a href="ident?i=set_ifa_lifetime">set_ifa_lifetime</a>(<a href="ident?i=ifa">ifa</a>, <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>, <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>);
<a name="L1090" href="source/net/ipv4/devinet.c#L1090">1090</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=inet_set_ifa">inet_set_ifa</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=ifa">ifa</a>);
<a name="L1091" href="source/net/ipv4/devinet.c#L1091">1091</a>                 break;
<a name="L1092" href="source/net/ipv4/devinet.c#L1092">1092</a> 
<a name="L1093" href="source/net/ipv4/devinet.c#L1093">1093</a>         case <a href="ident?i=SIOCSIFBRDADDR">SIOCSIFBRDADDR</a>:    <b><i>/* Set the broadcast address */</i></b>
<a name="L1094" href="source/net/ipv4/devinet.c#L1094">1094</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L1095" href="source/net/ipv4/devinet.c#L1095">1095</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast != <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr) {
<a name="L1096" href="source/net/ipv4/devinet.c#L1096">1096</a>                         <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(in_dev, ifap, 0);
<a name="L1097" href="source/net/ipv4/devinet.c#L1097">1097</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast = <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr;
<a name="L1098" href="source/net/ipv4/devinet.c#L1098">1098</a>                         <a href="ident?i=inet_insert_ifa">inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L1099" href="source/net/ipv4/devinet.c#L1099">1099</a>                 }
<a name="L1100" href="source/net/ipv4/devinet.c#L1100">1100</a>                 break;
<a name="L1101" href="source/net/ipv4/devinet.c#L1101">1101</a> 
<a name="L1102" href="source/net/ipv4/devinet.c#L1102">1102</a>         case <a href="ident?i=SIOCSIFDSTADDR">SIOCSIFDSTADDR</a>:    <b><i>/* Set the destination address */</i></b>
<a name="L1103" href="source/net/ipv4/devinet.c#L1103">1103</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L1104" href="source/net/ipv4/devinet.c#L1104">1104</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_address == <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr)
<a name="L1105" href="source/net/ipv4/devinet.c#L1105">1105</a>                         break;
<a name="L1106" href="source/net/ipv4/devinet.c#L1106">1106</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1107" href="source/net/ipv4/devinet.c#L1107">1107</a>                 if (<a href="ident?i=inet_abc_len">inet_abc_len</a>(<a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr) &lt; 0)
<a name="L1108" href="source/net/ipv4/devinet.c#L1108">1108</a>                         break;
<a name="L1109" href="source/net/ipv4/devinet.c#L1109">1109</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L1110" href="source/net/ipv4/devinet.c#L1110">1110</a>                 <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(in_dev, ifap, 0);
<a name="L1111" href="source/net/ipv4/devinet.c#L1111">1111</a>                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_address = <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr;
<a name="L1112" href="source/net/ipv4/devinet.c#L1112">1112</a>                 <a href="ident?i=inet_insert_ifa">inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L1113" href="source/net/ipv4/devinet.c#L1113">1113</a>                 break;
<a name="L1114" href="source/net/ipv4/devinet.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/devinet.c#L1115">1115</a>         case <a href="ident?i=SIOCSIFNETMASK">SIOCSIFNETMASK</a>:    <b><i>/* Set the netmask for the interface */</i></b>
<a name="L1116" href="source/net/ipv4/devinet.c#L1116">1116</a> 
<a name="L1117" href="source/net/ipv4/devinet.c#L1117">1117</a>                 <b><i>/*</i></b>
<a name="L1118" href="source/net/ipv4/devinet.c#L1118">1118</a> <b><i>                 *      The mask we set must be legal.</i></b>
<a name="L1119" href="source/net/ipv4/devinet.c#L1119">1119</a> <b><i>                 */</i></b>
<a name="L1120" href="source/net/ipv4/devinet.c#L1120">1120</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1121" href="source/net/ipv4/devinet.c#L1121">1121</a>                 if (<a href="ident?i=bad_mask">bad_mask</a>(<a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr, 0))
<a name="L1122" href="source/net/ipv4/devinet.c#L1122">1122</a>                         break;
<a name="L1123" href="source/net/ipv4/devinet.c#L1123">1123</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L1124" href="source/net/ipv4/devinet.c#L1124">1124</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_mask != <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr) {
<a name="L1125" href="source/net/ipv4/devinet.c#L1125">1125</a>                         <a href="ident?i=__be32">__be32</a> old_mask = <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask;
<a name="L1126" href="source/net/ipv4/devinet.c#L1126">1126</a>                         <a href="ident?i=inet_del_ifa">inet_del_ifa</a>(in_dev, ifap, 0);
<a name="L1127" href="source/net/ipv4/devinet.c#L1127">1127</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask = <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr;
<a name="L1128" href="source/net/ipv4/devinet.c#L1128">1128</a>                         <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen = <a href="ident?i=inet_mask_len">inet_mask_len</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_mask);
<a name="L1129" href="source/net/ipv4/devinet.c#L1129">1129</a> 
<a name="L1130" href="source/net/ipv4/devinet.c#L1130">1130</a>                         <b><i>/* See if current broadcast address matches</i></b>
<a name="L1131" href="source/net/ipv4/devinet.c#L1131">1131</a> <b><i>                         * with current netmask, then recalculate</i></b>
<a name="L1132" href="source/net/ipv4/devinet.c#L1132">1132</a> <b><i>                         * the broadcast address. Otherwise it's a</i></b>
<a name="L1133" href="source/net/ipv4/devinet.c#L1133">1133</a> <b><i>                         * funny address, so don't touch it since</i></b>
<a name="L1134" href="source/net/ipv4/devinet.c#L1134">1134</a> <b><i>                         * the user seems to know what (s)he's doing...</i></b>
<a name="L1135" href="source/net/ipv4/devinet.c#L1135">1135</a> <b><i>                         */</i></b>
<a name="L1136" href="source/net/ipv4/devinet.c#L1136">1136</a>                         if ((<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>) &amp;&amp;
<a name="L1137" href="source/net/ipv4/devinet.c#L1137">1137</a>                             (<a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen &lt; 31) &amp;&amp;
<a name="L1138" href="source/net/ipv4/devinet.c#L1138">1138</a>                             (<a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast ==
<a name="L1139" href="source/net/ipv4/devinet.c#L1139">1139</a>                              (<a href="ident?i=ifa">ifa</a>-&gt;ifa_local|~old_mask))) {
<a name="L1140" href="source/net/ipv4/devinet.c#L1140">1140</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast = (<a href="ident?i=ifa">ifa</a>-&gt;ifa_local |
<a name="L1141" href="source/net/ipv4/devinet.c#L1141">1141</a>                                                       ~sin-&gt;sin_addr.s_addr);
<a name="L1142" href="source/net/ipv4/devinet.c#L1142">1142</a>                         }
<a name="L1143" href="source/net/ipv4/devinet.c#L1143">1143</a>                         <a href="ident?i=inet_insert_ifa">inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L1144" href="source/net/ipv4/devinet.c#L1144">1144</a>                 }
<a name="L1145" href="source/net/ipv4/devinet.c#L1145">1145</a>                 break;
<a name="L1146" href="source/net/ipv4/devinet.c#L1146">1146</a>         }
<a name="L1147" href="source/net/ipv4/devinet.c#L1147">1147</a> <a href="ident?i=done">done</a>:
<a name="L1148" href="source/net/ipv4/devinet.c#L1148">1148</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1149" href="source/net/ipv4/devinet.c#L1149">1149</a> <a href="ident?i=out">out</a>:
<a name="L1150" href="source/net/ipv4/devinet.c#L1150">1150</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1151" href="source/net/ipv4/devinet.c#L1151">1151</a> rarok:
<a name="L1152" href="source/net/ipv4/devinet.c#L1152">1152</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1153" href="source/net/ipv4/devinet.c#L1153">1153</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=arg">arg</a>, &amp;ifr, sizeof(struct <a href="ident?i=ifreq">ifreq</a>)) ? -<a href="ident?i=EFAULT">EFAULT</a> : 0;
<a name="L1154" href="source/net/ipv4/devinet.c#L1154">1154</a>         goto <a href="ident?i=out">out</a>;
<a name="L1155" href="source/net/ipv4/devinet.c#L1155">1155</a> }
<a name="L1156" href="source/net/ipv4/devinet.c#L1156">1156</a> 
<a name="L1157" href="source/net/ipv4/devinet.c#L1157">1157</a> static int <a href="ident?i=inet_gifconf">inet_gifconf</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, char <a href="ident?i=__user">__user</a> *<a href="ident?i=buf">buf</a>, int <a href="ident?i=len">len</a>)
<a name="L1158" href="source/net/ipv4/devinet.c#L1158">1158</a> {
<a name="L1159" href="source/net/ipv4/devinet.c#L1159">1159</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L1160" href="source/net/ipv4/devinet.c#L1160">1160</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L1161" href="source/net/ipv4/devinet.c#L1161">1161</a>         struct <a href="ident?i=ifreq">ifreq</a> ifr;
<a name="L1162" href="source/net/ipv4/devinet.c#L1162">1162</a>         int <a href="ident?i=done">done</a> = 0;
<a name="L1163" href="source/net/ipv4/devinet.c#L1163">1163</a> 
<a name="L1164" href="source/net/ipv4/devinet.c#L1164">1164</a>         if (!in_dev)
<a name="L1165" href="source/net/ipv4/devinet.c#L1165">1165</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1166" href="source/net/ipv4/devinet.c#L1166">1166</a> 
<a name="L1167" href="source/net/ipv4/devinet.c#L1167">1167</a>         for (<a href="ident?i=ifa">ifa</a> = in_dev-&gt;ifa_list; <a href="ident?i=ifa">ifa</a>; <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L1168" href="source/net/ipv4/devinet.c#L1168">1168</a>                 if (!<a href="ident?i=buf">buf</a>) {
<a name="L1169" href="source/net/ipv4/devinet.c#L1169">1169</a>                         <a href="ident?i=done">done</a> += sizeof(ifr);
<a name="L1170" href="source/net/ipv4/devinet.c#L1170">1170</a>                         continue;
<a name="L1171" href="source/net/ipv4/devinet.c#L1171">1171</a>                 }
<a name="L1172" href="source/net/ipv4/devinet.c#L1172">1172</a>                 if (<a href="ident?i=len">len</a> &lt; (int) sizeof(ifr))
<a name="L1173" href="source/net/ipv4/devinet.c#L1173">1173</a>                         break;
<a name="L1174" href="source/net/ipv4/devinet.c#L1174">1174</a>                 <a href="ident?i=memset">memset</a>(&amp;ifr, 0, sizeof(struct <a href="ident?i=ifreq">ifreq</a>));
<a name="L1175" href="source/net/ipv4/devinet.c#L1175">1175</a>                 <a href="ident?i=strcpy">strcpy</a>(ifr.<a href="ident?i=ifr_name">ifr_name</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_label);
<a name="L1176" href="source/net/ipv4/devinet.c#L1176">1176</a> 
<a name="L1177" href="source/net/ipv4/devinet.c#L1177">1177</a>                 (*(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;ifr.<a href="ident?i=ifr_addr">ifr_addr</a>).sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L1178" href="source/net/ipv4/devinet.c#L1178">1178</a>                 (*(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;ifr.<a href="ident?i=ifr_addr">ifr_addr</a>).sin_addr.s_addr =
<a name="L1179" href="source/net/ipv4/devinet.c#L1179">1179</a>                                                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1180" href="source/net/ipv4/devinet.c#L1180">1180</a> 
<a name="L1181" href="source/net/ipv4/devinet.c#L1181">1181</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=buf">buf</a>, &amp;ifr, sizeof(struct <a href="ident?i=ifreq">ifreq</a>))) {
<a name="L1182" href="source/net/ipv4/devinet.c#L1182">1182</a>                         <a href="ident?i=done">done</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1183" href="source/net/ipv4/devinet.c#L1183">1183</a>                         break;
<a name="L1184" href="source/net/ipv4/devinet.c#L1184">1184</a>                 }
<a name="L1185" href="source/net/ipv4/devinet.c#L1185">1185</a>                 <a href="ident?i=buf">buf</a>  += sizeof(struct <a href="ident?i=ifreq">ifreq</a>);
<a name="L1186" href="source/net/ipv4/devinet.c#L1186">1186</a>                 <a href="ident?i=len">len</a>  -= sizeof(struct <a href="ident?i=ifreq">ifreq</a>);
<a name="L1187" href="source/net/ipv4/devinet.c#L1187">1187</a>                 <a href="ident?i=done">done</a> += sizeof(struct <a href="ident?i=ifreq">ifreq</a>);
<a name="L1188" href="source/net/ipv4/devinet.c#L1188">1188</a>         }
<a name="L1189" href="source/net/ipv4/devinet.c#L1189">1189</a> <a href="ident?i=out">out</a>:
<a name="L1190" href="source/net/ipv4/devinet.c#L1190">1190</a>         return <a href="ident?i=done">done</a>;
<a name="L1191" href="source/net/ipv4/devinet.c#L1191">1191</a> }
<a name="L1192" href="source/net/ipv4/devinet.c#L1192">1192</a> 
<a name="L1193" href="source/net/ipv4/devinet.c#L1193">1193</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=inet_select_addr">inet_select_addr</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, int <a href="ident?i=scope">scope</a>)
<a name="L1194" href="source/net/ipv4/devinet.c#L1194">1194</a> {
<a name="L1195" href="source/net/ipv4/devinet.c#L1195">1195</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = 0;
<a name="L1196" href="source/net/ipv4/devinet.c#L1196">1196</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1197" href="source/net/ipv4/devinet.c#L1197">1197</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1198" href="source/net/ipv4/devinet.c#L1198">1198</a> 
<a name="L1199" href="source/net/ipv4/devinet.c#L1199">1199</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1200" href="source/net/ipv4/devinet.c#L1200">1200</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1201" href="source/net/ipv4/devinet.c#L1201">1201</a>         if (!in_dev)
<a name="L1202" href="source/net/ipv4/devinet.c#L1202">1202</a>                 goto no_in_dev;
<a name="L1203" href="source/net/ipv4/devinet.c#L1203">1203</a> 
<a name="L1204" href="source/net/ipv4/devinet.c#L1204">1204</a>         <a href="ident?i=for_primary_ifa">for_primary_ifa</a>(in_dev) {
<a name="L1205" href="source/net/ipv4/devinet.c#L1205">1205</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_scope &gt; <a href="ident?i=scope">scope</a>)
<a name="L1206" href="source/net/ipv4/devinet.c#L1206">1206</a>                         continue;
<a name="L1207" href="source/net/ipv4/devinet.c#L1207">1207</a>                 if (!<a href="ident?i=dst">dst</a> || <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=ifa">ifa</a>)) {
<a name="L1208" href="source/net/ipv4/devinet.c#L1208">1208</a>                         <a href="ident?i=addr">addr</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1209" href="source/net/ipv4/devinet.c#L1209">1209</a>                         break;
<a name="L1210" href="source/net/ipv4/devinet.c#L1210">1210</a>                 }
<a name="L1211" href="source/net/ipv4/devinet.c#L1211">1211</a>                 if (!<a href="ident?i=addr">addr</a>)
<a name="L1212" href="source/net/ipv4/devinet.c#L1212">1212</a>                         <a href="ident?i=addr">addr</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1213" href="source/net/ipv4/devinet.c#L1213">1213</a>         } <a href="ident?i=endfor_ifa">endfor_ifa</a>(in_dev);
<a name="L1214" href="source/net/ipv4/devinet.c#L1214">1214</a> 
<a name="L1215" href="source/net/ipv4/devinet.c#L1215">1215</a>         if (<a href="ident?i=addr">addr</a>)
<a name="L1216" href="source/net/ipv4/devinet.c#L1216">1216</a>                 goto out_unlock;
<a name="L1217" href="source/net/ipv4/devinet.c#L1217">1217</a> no_in_dev:
<a name="L1218" href="source/net/ipv4/devinet.c#L1218">1218</a> 
<a name="L1219" href="source/net/ipv4/devinet.c#L1219">1219</a>         <b><i>/* Not loopback addresses on loopback should be preferred</i></b>
<a name="L1220" href="source/net/ipv4/devinet.c#L1220">1220</a> <b><i>           in this case. It is important that lo is the first interface</i></b>
<a name="L1221" href="source/net/ipv4/devinet.c#L1221">1221</a> <b><i>           in dev_base list.</i></b>
<a name="L1222" href="source/net/ipv4/devinet.c#L1222">1222</a> <b><i>         */</i></b>
<a name="L1223" href="source/net/ipv4/devinet.c#L1223">1223</a>         <a href="ident?i=for_each_netdev_rcu">for_each_netdev_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L1224" href="source/net/ipv4/devinet.c#L1224">1224</a>                 in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1225" href="source/net/ipv4/devinet.c#L1225">1225</a>                 if (!in_dev)
<a name="L1226" href="source/net/ipv4/devinet.c#L1226">1226</a>                         continue;
<a name="L1227" href="source/net/ipv4/devinet.c#L1227">1227</a> 
<a name="L1228" href="source/net/ipv4/devinet.c#L1228">1228</a>                 <a href="ident?i=for_primary_ifa">for_primary_ifa</a>(in_dev) {
<a name="L1229" href="source/net/ipv4/devinet.c#L1229">1229</a>                         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_scope != RT_SCOPE_LINK &amp;&amp;
<a name="L1230" href="source/net/ipv4/devinet.c#L1230">1230</a>                             <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope &lt;= <a href="ident?i=scope">scope</a>) {
<a name="L1231" href="source/net/ipv4/devinet.c#L1231">1231</a>                                 <a href="ident?i=addr">addr</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1232" href="source/net/ipv4/devinet.c#L1232">1232</a>                                 goto out_unlock;
<a name="L1233" href="source/net/ipv4/devinet.c#L1233">1233</a>                         }
<a name="L1234" href="source/net/ipv4/devinet.c#L1234">1234</a>                 } <a href="ident?i=endfor_ifa">endfor_ifa</a>(in_dev);
<a name="L1235" href="source/net/ipv4/devinet.c#L1235">1235</a>         }
<a name="L1236" href="source/net/ipv4/devinet.c#L1236">1236</a> out_unlock:
<a name="L1237" href="source/net/ipv4/devinet.c#L1237">1237</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1238" href="source/net/ipv4/devinet.c#L1238">1238</a>         return <a href="ident?i=addr">addr</a>;
<a name="L1239" href="source/net/ipv4/devinet.c#L1239">1239</a> }
<a name="L1240" href="source/net/ipv4/devinet.c#L1240">1240</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_select_addr">inet_select_addr</a>);
<a name="L1241" href="source/net/ipv4/devinet.c#L1241">1241</a> 
<a name="L1242" href="source/net/ipv4/devinet.c#L1242">1242</a> static <a href="ident?i=__be32">__be32</a> <a href="ident?i=confirm_addr_indev">confirm_addr_indev</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>,
<a name="L1243" href="source/net/ipv4/devinet.c#L1243">1243</a>                               <a href="ident?i=__be32">__be32</a> local, int <a href="ident?i=scope">scope</a>)
<a name="L1244" href="source/net/ipv4/devinet.c#L1244">1244</a> {
<a name="L1245" href="source/net/ipv4/devinet.c#L1245">1245</a>         int same = 0;
<a name="L1246" href="source/net/ipv4/devinet.c#L1246">1246</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = 0;
<a name="L1247" href="source/net/ipv4/devinet.c#L1247">1247</a> 
<a name="L1248" href="source/net/ipv4/devinet.c#L1248">1248</a>         <a href="ident?i=for_ifa">for_ifa</a>(in_dev) {
<a name="L1249" href="source/net/ipv4/devinet.c#L1249">1249</a>                 if (!<a href="ident?i=addr">addr</a> &amp;&amp;
<a name="L1250" href="source/net/ipv4/devinet.c#L1250">1250</a>                     (local == <a href="ident?i=ifa">ifa</a>-&gt;ifa_local || !local) &amp;&amp;
<a name="L1251" href="source/net/ipv4/devinet.c#L1251">1251</a>                     <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope &lt;= <a href="ident?i=scope">scope</a>) {
<a name="L1252" href="source/net/ipv4/devinet.c#L1252">1252</a>                         <a href="ident?i=addr">addr</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1253" href="source/net/ipv4/devinet.c#L1253">1253</a>                         if (same)
<a name="L1254" href="source/net/ipv4/devinet.c#L1254">1254</a>                                 break;
<a name="L1255" href="source/net/ipv4/devinet.c#L1255">1255</a>                 }
<a name="L1256" href="source/net/ipv4/devinet.c#L1256">1256</a>                 if (!same) {
<a name="L1257" href="source/net/ipv4/devinet.c#L1257">1257</a>                         same = (!local || <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(local, <a href="ident?i=ifa">ifa</a>)) &amp;&amp;
<a name="L1258" href="source/net/ipv4/devinet.c#L1258">1258</a>                                 (!<a href="ident?i=dst">dst</a> || <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=ifa">ifa</a>));
<a name="L1259" href="source/net/ipv4/devinet.c#L1259">1259</a>                         if (same &amp;&amp; <a href="ident?i=addr">addr</a>) {
<a name="L1260" href="source/net/ipv4/devinet.c#L1260">1260</a>                                 if (local || !<a href="ident?i=dst">dst</a>)
<a name="L1261" href="source/net/ipv4/devinet.c#L1261">1261</a>                                         break;
<a name="L1262" href="source/net/ipv4/devinet.c#L1262">1262</a>                                 <b><i>/* Is the selected addr into dst subnet? */</i></b>
<a name="L1263" href="source/net/ipv4/devinet.c#L1263">1263</a>                                 if (<a href="ident?i=inet_ifa_match">inet_ifa_match</a>(<a href="ident?i=addr">addr</a>, <a href="ident?i=ifa">ifa</a>))
<a name="L1264" href="source/net/ipv4/devinet.c#L1264">1264</a>                                         break;
<a name="L1265" href="source/net/ipv4/devinet.c#L1265">1265</a>                                 <b><i>/* No, then can we use new local src? */</i></b>
<a name="L1266" href="source/net/ipv4/devinet.c#L1266">1266</a>                                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_scope &lt;= <a href="ident?i=scope">scope</a>) {
<a name="L1267" href="source/net/ipv4/devinet.c#L1267">1267</a>                                         <a href="ident?i=addr">addr</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L1268" href="source/net/ipv4/devinet.c#L1268">1268</a>                                         break;
<a name="L1269" href="source/net/ipv4/devinet.c#L1269">1269</a>                                 }
<a name="L1270" href="source/net/ipv4/devinet.c#L1270">1270</a>                                 <b><i>/* search for large dst subnet for addr */</i></b>
<a name="L1271" href="source/net/ipv4/devinet.c#L1271">1271</a>                                 same = 0;
<a name="L1272" href="source/net/ipv4/devinet.c#L1272">1272</a>                         }
<a name="L1273" href="source/net/ipv4/devinet.c#L1273">1273</a>                 }
<a name="L1274" href="source/net/ipv4/devinet.c#L1274">1274</a>         } <a href="ident?i=endfor_ifa">endfor_ifa</a>(in_dev);
<a name="L1275" href="source/net/ipv4/devinet.c#L1275">1275</a> 
<a name="L1276" href="source/net/ipv4/devinet.c#L1276">1276</a>         return same ? <a href="ident?i=addr">addr</a> : 0;
<a name="L1277" href="source/net/ipv4/devinet.c#L1277">1277</a> }
<a name="L1278" href="source/net/ipv4/devinet.c#L1278">1278</a> 
<a name="L1279" href="source/net/ipv4/devinet.c#L1279">1279</a> <b><i>/*</i></b>
<a name="L1280" href="source/net/ipv4/devinet.c#L1280">1280</a> <b><i> * Confirm that local IP address exists using wildcards:</i></b>
<a name="L1281" href="source/net/ipv4/devinet.c#L1281">1281</a> <b><i> * - net: netns to check, cannot be NULL</i></b>
<a name="L1282" href="source/net/ipv4/devinet.c#L1282">1282</a> <b><i> * - in_dev: only on this interface, NULL=any interface</i></b>
<a name="L1283" href="source/net/ipv4/devinet.c#L1283">1283</a> <b><i> * - dst: only in the same subnet as dst, 0=any dst</i></b>
<a name="L1284" href="source/net/ipv4/devinet.c#L1284">1284</a> <b><i> * - local: address, 0=autoselect the local address</i></b>
<a name="L1285" href="source/net/ipv4/devinet.c#L1285">1285</a> <b><i> * - scope: maximum allowed scope value for the local address</i></b>
<a name="L1286" href="source/net/ipv4/devinet.c#L1286">1286</a> <b><i> */</i></b>
<a name="L1287" href="source/net/ipv4/devinet.c#L1287">1287</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=inet_confirm_addr">inet_confirm_addr</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L1288" href="source/net/ipv4/devinet.c#L1288">1288</a>                          <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, <a href="ident?i=__be32">__be32</a> local, int <a href="ident?i=scope">scope</a>)
<a name="L1289" href="source/net/ipv4/devinet.c#L1289">1289</a> {
<a name="L1290" href="source/net/ipv4/devinet.c#L1290">1290</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = 0;
<a name="L1291" href="source/net/ipv4/devinet.c#L1291">1291</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1292" href="source/net/ipv4/devinet.c#L1292">1292</a> 
<a name="L1293" href="source/net/ipv4/devinet.c#L1293">1293</a>         if (in_dev)
<a name="L1294" href="source/net/ipv4/devinet.c#L1294">1294</a>                 return <a href="ident?i=confirm_addr_indev">confirm_addr_indev</a>(in_dev, <a href="ident?i=dst">dst</a>, local, <a href="ident?i=scope">scope</a>);
<a name="L1295" href="source/net/ipv4/devinet.c#L1295">1295</a> 
<a name="L1296" href="source/net/ipv4/devinet.c#L1296">1296</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1297" href="source/net/ipv4/devinet.c#L1297">1297</a>         <a href="ident?i=for_each_netdev_rcu">for_each_netdev_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L1298" href="source/net/ipv4/devinet.c#L1298">1298</a>                 in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1299" href="source/net/ipv4/devinet.c#L1299">1299</a>                 if (in_dev) {
<a name="L1300" href="source/net/ipv4/devinet.c#L1300">1300</a>                         <a href="ident?i=addr">addr</a> = <a href="ident?i=confirm_addr_indev">confirm_addr_indev</a>(in_dev, <a href="ident?i=dst">dst</a>, local, <a href="ident?i=scope">scope</a>);
<a name="L1301" href="source/net/ipv4/devinet.c#L1301">1301</a>                         if (<a href="ident?i=addr">addr</a>)
<a name="L1302" href="source/net/ipv4/devinet.c#L1302">1302</a>                                 break;
<a name="L1303" href="source/net/ipv4/devinet.c#L1303">1303</a>                 }
<a name="L1304" href="source/net/ipv4/devinet.c#L1304">1304</a>         }
<a name="L1305" href="source/net/ipv4/devinet.c#L1305">1305</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1306" href="source/net/ipv4/devinet.c#L1306">1306</a> 
<a name="L1307" href="source/net/ipv4/devinet.c#L1307">1307</a>         return <a href="ident?i=addr">addr</a>;
<a name="L1308" href="source/net/ipv4/devinet.c#L1308">1308</a> }
<a name="L1309" href="source/net/ipv4/devinet.c#L1309">1309</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_confirm_addr">inet_confirm_addr</a>);
<a name="L1310" href="source/net/ipv4/devinet.c#L1310">1310</a> 
<a name="L1311" href="source/net/ipv4/devinet.c#L1311">1311</a> <b><i>/*</i></b>
<a name="L1312" href="source/net/ipv4/devinet.c#L1312">1312</a> <b><i> *      Device notifier</i></b>
<a name="L1313" href="source/net/ipv4/devinet.c#L1313">1313</a> <b><i> */</i></b>
<a name="L1314" href="source/net/ipv4/devinet.c#L1314">1314</a> 
<a name="L1315" href="source/net/ipv4/devinet.c#L1315">1315</a> int <a href="ident?i=register_inetaddr_notifier">register_inetaddr_notifier</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=nb">nb</a>)
<a name="L1316" href="source/net/ipv4/devinet.c#L1316">1316</a> {
<a name="L1317" href="source/net/ipv4/devinet.c#L1317">1317</a>         return <a href="ident?i=blocking_notifier_chain_register">blocking_notifier_chain_register</a>(&amp;inetaddr_chain, <a href="ident?i=nb">nb</a>);
<a name="L1318" href="source/net/ipv4/devinet.c#L1318">1318</a> }
<a name="L1319" href="source/net/ipv4/devinet.c#L1319">1319</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=register_inetaddr_notifier">register_inetaddr_notifier</a>);
<a name="L1320" href="source/net/ipv4/devinet.c#L1320">1320</a> 
<a name="L1321" href="source/net/ipv4/devinet.c#L1321">1321</a> int <a href="ident?i=unregister_inetaddr_notifier">unregister_inetaddr_notifier</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=nb">nb</a>)
<a name="L1322" href="source/net/ipv4/devinet.c#L1322">1322</a> {
<a name="L1323" href="source/net/ipv4/devinet.c#L1323">1323</a>         return <a href="ident?i=blocking_notifier_chain_unregister">blocking_notifier_chain_unregister</a>(&amp;inetaddr_chain, <a href="ident?i=nb">nb</a>);
<a name="L1324" href="source/net/ipv4/devinet.c#L1324">1324</a> }
<a name="L1325" href="source/net/ipv4/devinet.c#L1325">1325</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=unregister_inetaddr_notifier">unregister_inetaddr_notifier</a>);
<a name="L1326" href="source/net/ipv4/devinet.c#L1326">1326</a> 
<a name="L1327" href="source/net/ipv4/devinet.c#L1327">1327</a> <b><i>/* Rename ifa_labels for a device name change. Make some effort to preserve</i></b>
<a name="L1328" href="source/net/ipv4/devinet.c#L1328">1328</a> <b><i> * existing alias numbering and to create unique labels if possible.</i></b>
<a name="L1329" href="source/net/ipv4/devinet.c#L1329">1329</a> <b><i>*/</i></b>
<a name="L1330" href="source/net/ipv4/devinet.c#L1330">1330</a> static void <a href="ident?i=inetdev_changename">inetdev_changename</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1331" href="source/net/ipv4/devinet.c#L1331">1331</a> {
<a name="L1332" href="source/net/ipv4/devinet.c#L1332">1332</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L1333" href="source/net/ipv4/devinet.c#L1333">1333</a>         int named = 0;
<a name="L1334" href="source/net/ipv4/devinet.c#L1334">1334</a> 
<a name="L1335" href="source/net/ipv4/devinet.c#L1335">1335</a>         for (<a href="ident?i=ifa">ifa</a> = in_dev-&gt;ifa_list; <a href="ident?i=ifa">ifa</a>; <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L1336" href="source/net/ipv4/devinet.c#L1336">1336</a>                 char <a href="ident?i=old">old</a>[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>], *dot;
<a name="L1337" href="source/net/ipv4/devinet.c#L1337">1337</a> 
<a name="L1338" href="source/net/ipv4/devinet.c#L1338">1338</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=old">old</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L1339" href="source/net/ipv4/devinet.c#L1339">1339</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L1340" href="source/net/ipv4/devinet.c#L1340">1340</a>                 if (named++ == 0)
<a name="L1341" href="source/net/ipv4/devinet.c#L1341">1341</a>                         goto <a href="ident?i=skip">skip</a>;
<a name="L1342" href="source/net/ipv4/devinet.c#L1342">1342</a>                 dot = <a href="ident?i=strchr">strchr</a>(<a href="ident?i=old">old</a>, <i>':'</i>);
<a name="L1343" href="source/net/ipv4/devinet.c#L1343">1343</a>                 if (!dot) {
<a name="L1344" href="source/net/ipv4/devinet.c#L1344">1344</a>                         <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=old">old</a>, <i>":%d"</i>, named);
<a name="L1345" href="source/net/ipv4/devinet.c#L1345">1345</a>                         dot = <a href="ident?i=old">old</a>;
<a name="L1346" href="source/net/ipv4/devinet.c#L1346">1346</a>                 }
<a name="L1347" href="source/net/ipv4/devinet.c#L1347">1347</a>                 if (<a href="ident?i=strlen">strlen</a>(dot) + <a href="ident?i=strlen">strlen</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>) &lt; <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>)
<a name="L1348" href="source/net/ipv4/devinet.c#L1348">1348</a>                         <a href="ident?i=strcat">strcat</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, dot);
<a name="L1349" href="source/net/ipv4/devinet.c#L1349">1349</a>                 else
<a name="L1350" href="source/net/ipv4/devinet.c#L1350">1350</a>                         <a href="ident?i=strcpy">strcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label + (<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a> - <a href="ident?i=strlen">strlen</a>(dot) - 1), dot);
<a name="L1351" href="source/net/ipv4/devinet.c#L1351">1351</a> <a href="ident?i=skip">skip</a>:
<a name="L1352" href="source/net/ipv4/devinet.c#L1352">1352</a>                 <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(<a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=ifa">ifa</a>, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L1353" href="source/net/ipv4/devinet.c#L1353">1353</a>         }
<a name="L1354" href="source/net/ipv4/devinet.c#L1354">1354</a> }
<a name="L1355" href="source/net/ipv4/devinet.c#L1355">1355</a> 
<a name="L1356" href="source/net/ipv4/devinet.c#L1356">1356</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=inetdev_valid_mtu">inetdev_valid_mtu</a>(unsigned int <a href="ident?i=mtu">mtu</a>)
<a name="L1357" href="source/net/ipv4/devinet.c#L1357">1357</a> {
<a name="L1358" href="source/net/ipv4/devinet.c#L1358">1358</a>         return <a href="ident?i=mtu">mtu</a> &gt;= 68;
<a name="L1359" href="source/net/ipv4/devinet.c#L1359">1359</a> }
<a name="L1360" href="source/net/ipv4/devinet.c#L1360">1360</a> 
<a name="L1361" href="source/net/ipv4/devinet.c#L1361">1361</a> static void <a href="ident?i=inetdev_send_gratuitous_arp">inetdev_send_gratuitous_arp</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L1362" href="source/net/ipv4/devinet.c#L1362">1362</a>                                         struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1363" href="source/net/ipv4/devinet.c#L1363">1363</a> 
<a name="L1364" href="source/net/ipv4/devinet.c#L1364">1364</a> {
<a name="L1365" href="source/net/ipv4/devinet.c#L1365">1365</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L1366" href="source/net/ipv4/devinet.c#L1366">1366</a> 
<a name="L1367" href="source/net/ipv4/devinet.c#L1367">1367</a>         for (<a href="ident?i=ifa">ifa</a> = in_dev-&gt;ifa_list; <a href="ident?i=ifa">ifa</a>;
<a name="L1368" href="source/net/ipv4/devinet.c#L1368">1368</a>              <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next) {
<a name="L1369" href="source/net/ipv4/devinet.c#L1369">1369</a>                 <a href="ident?i=arp_send">arp_send</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>, <a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>,
<a name="L1370" href="source/net/ipv4/devinet.c#L1370">1370</a>                          <a href="ident?i=ifa">ifa</a>-&gt;ifa_local, <a href="ident?i=dev">dev</a>,
<a name="L1371" href="source/net/ipv4/devinet.c#L1371">1371</a>                          <a href="ident?i=ifa">ifa</a>-&gt;ifa_local, <a href="ident?i=NULL">NULL</a>,
<a name="L1372" href="source/net/ipv4/devinet.c#L1372">1372</a>                          <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=NULL">NULL</a>);
<a name="L1373" href="source/net/ipv4/devinet.c#L1373">1373</a>         }
<a name="L1374" href="source/net/ipv4/devinet.c#L1374">1374</a> }
<a name="L1375" href="source/net/ipv4/devinet.c#L1375">1375</a> 
<a name="L1376" href="source/net/ipv4/devinet.c#L1376">1376</a> <b><i>/* Called only under RTNL semaphore */</i></b>
<a name="L1377" href="source/net/ipv4/devinet.c#L1377">1377</a> 
<a name="L1378" href="source/net/ipv4/devinet.c#L1378">1378</a> static int <a href="ident?i=inetdev_event">inetdev_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>, unsigned long <a href="ident?i=event">event</a>,
<a name="L1379" href="source/net/ipv4/devinet.c#L1379">1379</a>                          void *<a href="ident?i=ptr">ptr</a>)
<a name="L1380" href="source/net/ipv4/devinet.c#L1380">1380</a> {
<a name="L1381" href="source/net/ipv4/devinet.c#L1381">1381</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=netdev_notifier_info_to_dev">netdev_notifier_info_to_dev</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L1382" href="source/net/ipv4/devinet.c#L1382">1382</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L1383" href="source/net/ipv4/devinet.c#L1383">1383</a> 
<a name="L1384" href="source/net/ipv4/devinet.c#L1384">1384</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1385" href="source/net/ipv4/devinet.c#L1385">1385</a> 
<a name="L1386" href="source/net/ipv4/devinet.c#L1386">1386</a>         if (!in_dev) {
<a name="L1387" href="source/net/ipv4/devinet.c#L1387">1387</a>                 if (<a href="ident?i=event">event</a> == <a href="ident?i=NETDEV_REGISTER">NETDEV_REGISTER</a>) {
<a name="L1388" href="source/net/ipv4/devinet.c#L1388">1388</a>                         in_dev = <a href="ident?i=inetdev_init">inetdev_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L1389" href="source/net/ipv4/devinet.c#L1389">1389</a>                         if (<a href="ident?i=IS_ERR">IS_ERR</a>(in_dev))
<a name="L1390" href="source/net/ipv4/devinet.c#L1390">1390</a>                                 return <a href="ident?i=notifier_from_errno">notifier_from_errno</a>(<a href="ident?i=PTR_ERR">PTR_ERR</a>(in_dev));
<a name="L1391" href="source/net/ipv4/devinet.c#L1391">1391</a>                         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>) {
<a name="L1392" href="source/net/ipv4/devinet.c#L1392">1392</a>                                 <a href="ident?i=IN_DEV_CONF_SET">IN_DEV_CONF_SET</a>(in_dev, NOXFRM, 1);
<a name="L1393" href="source/net/ipv4/devinet.c#L1393">1393</a>                                 <a href="ident?i=IN_DEV_CONF_SET">IN_DEV_CONF_SET</a>(in_dev, NOPOLICY, 1);
<a name="L1394" href="source/net/ipv4/devinet.c#L1394">1394</a>                         }
<a name="L1395" href="source/net/ipv4/devinet.c#L1395">1395</a>                 } else if (<a href="ident?i=event">event</a> == <a href="ident?i=NETDEV_CHANGEMTU">NETDEV_CHANGEMTU</a>) {
<a name="L1396" href="source/net/ipv4/devinet.c#L1396">1396</a>                         <b><i>/* Re-enabling IP */</i></b>
<a name="L1397" href="source/net/ipv4/devinet.c#L1397">1397</a>                         if (<a href="ident?i=inetdev_valid_mtu">inetdev_valid_mtu</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>))
<a name="L1398" href="source/net/ipv4/devinet.c#L1398">1398</a>                                 in_dev = <a href="ident?i=inetdev_init">inetdev_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L1399" href="source/net/ipv4/devinet.c#L1399">1399</a>                 }
<a name="L1400" href="source/net/ipv4/devinet.c#L1400">1400</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1401" href="source/net/ipv4/devinet.c#L1401">1401</a>         }
<a name="L1402" href="source/net/ipv4/devinet.c#L1402">1402</a> 
<a name="L1403" href="source/net/ipv4/devinet.c#L1403">1403</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L1404" href="source/net/ipv4/devinet.c#L1404">1404</a>         case <a href="ident?i=NETDEV_REGISTER">NETDEV_REGISTER</a>:
<a name="L1405" href="source/net/ipv4/devinet.c#L1405">1405</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"%s: bug\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1406" href="source/net/ipv4/devinet.c#L1406">1406</a>                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=dev">dev</a>-&gt;ip_ptr, <a href="ident?i=NULL">NULL</a>);
<a name="L1407" href="source/net/ipv4/devinet.c#L1407">1407</a>                 break;
<a name="L1408" href="source/net/ipv4/devinet.c#L1408">1408</a>         case <a href="ident?i=NETDEV_UP">NETDEV_UP</a>:
<a name="L1409" href="source/net/ipv4/devinet.c#L1409">1409</a>                 if (!<a href="ident?i=inetdev_valid_mtu">inetdev_valid_mtu</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>))
<a name="L1410" href="source/net/ipv4/devinet.c#L1410">1410</a>                         break;
<a name="L1411" href="source/net/ipv4/devinet.c#L1411">1411</a>                 if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>) {
<a name="L1412" href="source/net/ipv4/devinet.c#L1412">1412</a>                         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a> = <a href="ident?i=inet_alloc_ifa">inet_alloc_ifa</a>();
<a name="L1413" href="source/net/ipv4/devinet.c#L1413">1413</a> 
<a name="L1414" href="source/net/ipv4/devinet.c#L1414">1414</a>                         if (<a href="ident?i=ifa">ifa</a>) {
<a name="L1415" href="source/net/ipv4/devinet.c#L1415">1415</a>                                 <a href="ident?i=INIT_HLIST_NODE">INIT_HLIST_NODE</a>(&amp;<a href="ident?i=ifa">ifa</a>-&gt;<a href="ident?i=hash">hash</a>);
<a name="L1416" href="source/net/ipv4/devinet.c#L1416">1416</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_local =
<a name="L1417" href="source/net/ipv4/devinet.c#L1417">1417</a>                                   <a href="ident?i=ifa">ifa</a>-&gt;ifa_address = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_LOOPBACK">INADDR_LOOPBACK</a>);
<a name="L1418" href="source/net/ipv4/devinet.c#L1418">1418</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen = 8;
<a name="L1419" href="source/net/ipv4/devinet.c#L1419">1419</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask = <a href="ident?i=inet_make_mask">inet_make_mask</a>(8);
<a name="L1420" href="source/net/ipv4/devinet.c#L1420">1420</a>                                 <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L1421" href="source/net/ipv4/devinet.c#L1421">1421</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev = in_dev;
<a name="L1422" href="source/net/ipv4/devinet.c#L1422">1422</a>                                 <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope = RT_SCOPE_HOST;
<a name="L1423" href="source/net/ipv4/devinet.c#L1423">1423</a>                                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>);
<a name="L1424" href="source/net/ipv4/devinet.c#L1424">1424</a>                                 <a href="ident?i=set_ifa_lifetime">set_ifa_lifetime</a>(<a href="ident?i=ifa">ifa</a>, <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>,
<a name="L1425" href="source/net/ipv4/devinet.c#L1425">1425</a>                                                  <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>);
<a name="L1426" href="source/net/ipv4/devinet.c#L1426">1426</a>                                 <a href="ident?i=ipv4_devconf_setall">ipv4_devconf_setall</a>(in_dev);
<a name="L1427" href="source/net/ipv4/devinet.c#L1427">1427</a>                                 <a href="ident?i=neigh_parms_data_state_setall">neigh_parms_data_state_setall</a>(in_dev-&gt;arp_parms);
<a name="L1428" href="source/net/ipv4/devinet.c#L1428">1428</a>                                 <a href="ident?i=inet_insert_ifa">inet_insert_ifa</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L1429" href="source/net/ipv4/devinet.c#L1429">1429</a>                         }
<a name="L1430" href="source/net/ipv4/devinet.c#L1430">1430</a>                 }
<a name="L1431" href="source/net/ipv4/devinet.c#L1431">1431</a>                 <a href="ident?i=ip_mc_up">ip_mc_up</a>(in_dev);
<a name="L1432" href="source/net/ipv4/devinet.c#L1432">1432</a>                 <b><i>/* fall through */</i></b>
<a name="L1433" href="source/net/ipv4/devinet.c#L1433">1433</a>         case <a href="ident?i=NETDEV_CHANGEADDR">NETDEV_CHANGEADDR</a>:
<a name="L1434" href="source/net/ipv4/devinet.c#L1434">1434</a>                 if (!<a href="ident?i=IN_DEV_ARP_NOTIFY">IN_DEV_ARP_NOTIFY</a>(in_dev))
<a name="L1435" href="source/net/ipv4/devinet.c#L1435">1435</a>                         break;
<a name="L1436" href="source/net/ipv4/devinet.c#L1436">1436</a>                 <b><i>/* fall through */</i></b>
<a name="L1437" href="source/net/ipv4/devinet.c#L1437">1437</a>         case <a href="ident?i=NETDEV_NOTIFY_PEERS">NETDEV_NOTIFY_PEERS</a>:
<a name="L1438" href="source/net/ipv4/devinet.c#L1438">1438</a>                 <b><i>/* Send gratuitous ARP to notify of link change */</i></b>
<a name="L1439" href="source/net/ipv4/devinet.c#L1439">1439</a>                 <a href="ident?i=inetdev_send_gratuitous_arp">inetdev_send_gratuitous_arp</a>(<a href="ident?i=dev">dev</a>, in_dev);
<a name="L1440" href="source/net/ipv4/devinet.c#L1440">1440</a>                 break;
<a name="L1441" href="source/net/ipv4/devinet.c#L1441">1441</a>         case <a href="ident?i=NETDEV_DOWN">NETDEV_DOWN</a>:
<a name="L1442" href="source/net/ipv4/devinet.c#L1442">1442</a>                 <a href="ident?i=ip_mc_down">ip_mc_down</a>(in_dev);
<a name="L1443" href="source/net/ipv4/devinet.c#L1443">1443</a>                 break;
<a name="L1444" href="source/net/ipv4/devinet.c#L1444">1444</a>         case <a href="ident?i=NETDEV_PRE_TYPE_CHANGE">NETDEV_PRE_TYPE_CHANGE</a>:
<a name="L1445" href="source/net/ipv4/devinet.c#L1445">1445</a>                 <a href="ident?i=ip_mc_unmap">ip_mc_unmap</a>(in_dev);
<a name="L1446" href="source/net/ipv4/devinet.c#L1446">1446</a>                 break;
<a name="L1447" href="source/net/ipv4/devinet.c#L1447">1447</a>         case <a href="ident?i=NETDEV_POST_TYPE_CHANGE">NETDEV_POST_TYPE_CHANGE</a>:
<a name="L1448" href="source/net/ipv4/devinet.c#L1448">1448</a>                 <a href="ident?i=ip_mc_remap">ip_mc_remap</a>(in_dev);
<a name="L1449" href="source/net/ipv4/devinet.c#L1449">1449</a>                 break;
<a name="L1450" href="source/net/ipv4/devinet.c#L1450">1450</a>         case <a href="ident?i=NETDEV_CHANGEMTU">NETDEV_CHANGEMTU</a>:
<a name="L1451" href="source/net/ipv4/devinet.c#L1451">1451</a>                 if (<a href="ident?i=inetdev_valid_mtu">inetdev_valid_mtu</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>))
<a name="L1452" href="source/net/ipv4/devinet.c#L1452">1452</a>                         break;
<a name="L1453" href="source/net/ipv4/devinet.c#L1453">1453</a>                 <b><i>/* disable IP when MTU is not enough */</i></b>
<a name="L1454" href="source/net/ipv4/devinet.c#L1454">1454</a>         case <a href="ident?i=NETDEV_UNREGISTER">NETDEV_UNREGISTER</a>:
<a name="L1455" href="source/net/ipv4/devinet.c#L1455">1455</a>                 <a href="ident?i=inetdev_destroy">inetdev_destroy</a>(in_dev);
<a name="L1456" href="source/net/ipv4/devinet.c#L1456">1456</a>                 break;
<a name="L1457" href="source/net/ipv4/devinet.c#L1457">1457</a>         case <a href="ident?i=NETDEV_CHANGENAME">NETDEV_CHANGENAME</a>:
<a name="L1458" href="source/net/ipv4/devinet.c#L1458">1458</a>                 <b><i>/* Do not notify about label change, this event is</i></b>
<a name="L1459" href="source/net/ipv4/devinet.c#L1459">1459</a> <b><i>                 * not interesting to applications using netlink.</i></b>
<a name="L1460" href="source/net/ipv4/devinet.c#L1460">1460</a> <b><i>                 */</i></b>
<a name="L1461" href="source/net/ipv4/devinet.c#L1461">1461</a>                 <a href="ident?i=inetdev_changename">inetdev_changename</a>(<a href="ident?i=dev">dev</a>, in_dev);
<a name="L1462" href="source/net/ipv4/devinet.c#L1462">1462</a> 
<a name="L1463" href="source/net/ipv4/devinet.c#L1463">1463</a>                 <a href="ident?i=devinet_sysctl_unregister">devinet_sysctl_unregister</a>(in_dev);
<a name="L1464" href="source/net/ipv4/devinet.c#L1464">1464</a>                 <a href="ident?i=devinet_sysctl_register">devinet_sysctl_register</a>(in_dev);
<a name="L1465" href="source/net/ipv4/devinet.c#L1465">1465</a>                 break;
<a name="L1466" href="source/net/ipv4/devinet.c#L1466">1466</a>         }
<a name="L1467" href="source/net/ipv4/devinet.c#L1467">1467</a> <a href="ident?i=out">out</a>:
<a name="L1468" href="source/net/ipv4/devinet.c#L1468">1468</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1469" href="source/net/ipv4/devinet.c#L1469">1469</a> }
<a name="L1470" href="source/net/ipv4/devinet.c#L1470">1470</a> 
<a name="L1471" href="source/net/ipv4/devinet.c#L1471">1471</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=ip_netdev_notifier">ip_netdev_notifier</a> = {
<a name="L1472" href="source/net/ipv4/devinet.c#L1472">1472</a>         .notifier_call = <a href="ident?i=inetdev_event">inetdev_event</a>,
<a name="L1473" href="source/net/ipv4/devinet.c#L1473">1473</a> };
<a name="L1474" href="source/net/ipv4/devinet.c#L1474">1474</a> 
<a name="L1475" href="source/net/ipv4/devinet.c#L1475">1475</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=inet_nlmsg_size">inet_nlmsg_size</a>(void)
<a name="L1476" href="source/net/ipv4/devinet.c#L1476">1476</a> {
<a name="L1477" href="source/net/ipv4/devinet.c#L1477">1477</a>         return <a href="ident?i=NLMSG_ALIGN">NLMSG_ALIGN</a>(sizeof(struct <a href="ident?i=ifaddrmsg">ifaddrmsg</a>))
<a name="L1478" href="source/net/ipv4/devinet.c#L1478">1478</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* IFA_ADDRESS */</i></b>
<a name="L1479" href="source/net/ipv4/devinet.c#L1479">1479</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* IFA_LOCAL */</i></b>
<a name="L1480" href="source/net/ipv4/devinet.c#L1480">1480</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* IFA_BROADCAST */</i></b>
<a name="L1481" href="source/net/ipv4/devinet.c#L1481">1481</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>) <b><i>/* IFA_LABEL */</i></b>
<a name="L1482" href="source/net/ipv4/devinet.c#L1482">1482</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(4)  <b><i>/* IFA_FLAGS */</i></b>
<a name="L1483" href="source/net/ipv4/devinet.c#L1483">1483</a>                + <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=ifa_cacheinfo">ifa_cacheinfo</a>)); <b><i>/* IFA_CACHEINFO */</i></b>
<a name="L1484" href="source/net/ipv4/devinet.c#L1484">1484</a> }
<a name="L1485" href="source/net/ipv4/devinet.c#L1485">1485</a> 
<a name="L1486" href="source/net/ipv4/devinet.c#L1486">1486</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=cstamp_delta">cstamp_delta</a>(unsigned long cstamp)
<a name="L1487" href="source/net/ipv4/devinet.c#L1487">1487</a> {
<a name="L1488" href="source/net/ipv4/devinet.c#L1488">1488</a>         return (cstamp - <a href="ident?i=INITIAL_JIFFIES">INITIAL_JIFFIES</a>) * 100UL / <a href="ident?i=HZ">HZ</a>;
<a name="L1489" href="source/net/ipv4/devinet.c#L1489">1489</a> }
<a name="L1490" href="source/net/ipv4/devinet.c#L1490">1490</a> 
<a name="L1491" href="source/net/ipv4/devinet.c#L1491">1491</a> static int <a href="ident?i=put_cacheinfo">put_cacheinfo</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned long cstamp,
<a name="L1492" href="source/net/ipv4/devinet.c#L1492">1492</a>                          unsigned long tstamp, <a href="ident?i=u32">u32</a> preferred, <a href="ident?i=u32">u32</a> <a href="ident?i=valid">valid</a>)
<a name="L1493" href="source/net/ipv4/devinet.c#L1493">1493</a> {
<a name="L1494" href="source/net/ipv4/devinet.c#L1494">1494</a>         struct <a href="ident?i=ifa_cacheinfo">ifa_cacheinfo</a> ci;
<a name="L1495" href="source/net/ipv4/devinet.c#L1495">1495</a> 
<a name="L1496" href="source/net/ipv4/devinet.c#L1496">1496</a>         ci.cstamp = <a href="ident?i=cstamp_delta">cstamp_delta</a>(cstamp);
<a name="L1497" href="source/net/ipv4/devinet.c#L1497">1497</a>         ci.tstamp = <a href="ident?i=cstamp_delta">cstamp_delta</a>(tstamp);
<a name="L1498" href="source/net/ipv4/devinet.c#L1498">1498</a>         ci.ifa_prefered = preferred;
<a name="L1499" href="source/net/ipv4/devinet.c#L1499">1499</a>         ci.ifa_valid = <a href="ident?i=valid">valid</a>;
<a name="L1500" href="source/net/ipv4/devinet.c#L1500">1500</a> 
<a name="L1501" href="source/net/ipv4/devinet.c#L1501">1501</a>         return <a href="ident?i=nla_put">nla_put</a>(<a href="ident?i=skb">skb</a>, IFA_CACHEINFO, sizeof(ci), &amp;ci);
<a name="L1502" href="source/net/ipv4/devinet.c#L1502">1502</a> }
<a name="L1503" href="source/net/ipv4/devinet.c#L1503">1503</a> 
<a name="L1504" href="source/net/ipv4/devinet.c#L1504">1504</a> static int <a href="ident?i=inet_fill_ifaddr">inet_fill_ifaddr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>,
<a name="L1505" href="source/net/ipv4/devinet.c#L1505">1505</a>                             <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, int <a href="ident?i=event">event</a>, unsigned int <a href="ident?i=flags">flags</a>)
<a name="L1506" href="source/net/ipv4/devinet.c#L1506">1506</a> {
<a name="L1507" href="source/net/ipv4/devinet.c#L1507">1507</a>         struct <a href="ident?i=ifaddrmsg">ifaddrmsg</a> *ifm;
<a name="L1508" href="source/net/ipv4/devinet.c#L1508">1508</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a>  *nlh;
<a name="L1509" href="source/net/ipv4/devinet.c#L1509">1509</a>         <a href="ident?i=u32">u32</a> preferred, <a href="ident?i=valid">valid</a>;
<a name="L1510" href="source/net/ipv4/devinet.c#L1510">1510</a> 
<a name="L1511" href="source/net/ipv4/devinet.c#L1511">1511</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=event">event</a>, sizeof(*ifm), <a href="ident?i=flags">flags</a>);
<a name="L1512" href="source/net/ipv4/devinet.c#L1512">1512</a>         if (!nlh)
<a name="L1513" href="source/net/ipv4/devinet.c#L1513">1513</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1514" href="source/net/ipv4/devinet.c#L1514">1514</a> 
<a name="L1515" href="source/net/ipv4/devinet.c#L1515">1515</a>         ifm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L1516" href="source/net/ipv4/devinet.c#L1516">1516</a>         ifm-&gt;ifa_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L1517" href="source/net/ipv4/devinet.c#L1517">1517</a>         ifm-&gt;ifa_prefixlen = <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen;
<a name="L1518" href="source/net/ipv4/devinet.c#L1518">1518</a>         ifm-&gt;ifa_flags = <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags;
<a name="L1519" href="source/net/ipv4/devinet.c#L1519">1519</a>         ifm-&gt;ifa_scope = <a href="ident?i=ifa">ifa</a>-&gt;ifa_scope;
<a name="L1520" href="source/net/ipv4/devinet.c#L1520">1520</a>         ifm-&gt;ifa_index = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1521" href="source/net/ipv4/devinet.c#L1521">1521</a> 
<a name="L1522" href="source/net/ipv4/devinet.c#L1522">1522</a>         if (!(ifm-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_PERMANENT">IFA_F_PERMANENT</a>)) {
<a name="L1523" href="source/net/ipv4/devinet.c#L1523">1523</a>                 preferred = <a href="ident?i=ifa">ifa</a>-&gt;ifa_preferred_lft;
<a name="L1524" href="source/net/ipv4/devinet.c#L1524">1524</a>                 <a href="ident?i=valid">valid</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_valid_lft;
<a name="L1525" href="source/net/ipv4/devinet.c#L1525">1525</a>                 if (preferred != <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>) {
<a name="L1526" href="source/net/ipv4/devinet.c#L1526">1526</a>                         long tval = (<a href="ident?i=jiffies">jiffies</a> - <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp) / <a href="ident?i=HZ">HZ</a>;
<a name="L1527" href="source/net/ipv4/devinet.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/devinet.c#L1528">1528</a>                         if (preferred &gt; tval)
<a name="L1529" href="source/net/ipv4/devinet.c#L1529">1529</a>                                 preferred -= tval;
<a name="L1530" href="source/net/ipv4/devinet.c#L1530">1530</a>                         else
<a name="L1531" href="source/net/ipv4/devinet.c#L1531">1531</a>                                 preferred = 0;
<a name="L1532" href="source/net/ipv4/devinet.c#L1532">1532</a>                         if (<a href="ident?i=valid">valid</a> != <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>) {
<a name="L1533" href="source/net/ipv4/devinet.c#L1533">1533</a>                                 if (<a href="ident?i=valid">valid</a> &gt; tval)
<a name="L1534" href="source/net/ipv4/devinet.c#L1534">1534</a>                                         <a href="ident?i=valid">valid</a> -= tval;
<a name="L1535" href="source/net/ipv4/devinet.c#L1535">1535</a>                                 else
<a name="L1536" href="source/net/ipv4/devinet.c#L1536">1536</a>                                         <a href="ident?i=valid">valid</a> = 0;
<a name="L1537" href="source/net/ipv4/devinet.c#L1537">1537</a>                         }
<a name="L1538" href="source/net/ipv4/devinet.c#L1538">1538</a>                 }
<a name="L1539" href="source/net/ipv4/devinet.c#L1539">1539</a>         } else {
<a name="L1540" href="source/net/ipv4/devinet.c#L1540">1540</a>                 preferred = <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>;
<a name="L1541" href="source/net/ipv4/devinet.c#L1541">1541</a>                 <a href="ident?i=valid">valid</a> = <a href="ident?i=INFINITY_LIFE_TIME">INFINITY_LIFE_TIME</a>;
<a name="L1542" href="source/net/ipv4/devinet.c#L1542">1542</a>         }
<a name="L1543" href="source/net/ipv4/devinet.c#L1543">1543</a>         if ((<a href="ident?i=ifa">ifa</a>-&gt;ifa_address &amp;&amp;
<a name="L1544" href="source/net/ipv4/devinet.c#L1544">1544</a>              <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFA_ADDRESS, <a href="ident?i=ifa">ifa</a>-&gt;ifa_address)) ||
<a name="L1545" href="source/net/ipv4/devinet.c#L1545">1545</a>             (<a href="ident?i=ifa">ifa</a>-&gt;ifa_local &amp;&amp;
<a name="L1546" href="source/net/ipv4/devinet.c#L1546">1546</a>              <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFA_LOCAL, <a href="ident?i=ifa">ifa</a>-&gt;ifa_local)) ||
<a name="L1547" href="source/net/ipv4/devinet.c#L1547">1547</a>             (<a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast &amp;&amp;
<a name="L1548" href="source/net/ipv4/devinet.c#L1548">1548</a>              <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFA_BROADCAST, <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast)) ||
<a name="L1549" href="source/net/ipv4/devinet.c#L1549">1549</a>             (<a href="ident?i=ifa">ifa</a>-&gt;ifa_label[0] &amp;&amp;
<a name="L1550" href="source/net/ipv4/devinet.c#L1550">1550</a>              <a href="ident?i=nla_put_string">nla_put_string</a>(<a href="ident?i=skb">skb</a>, IFA_LABEL, <a href="ident?i=ifa">ifa</a>-&gt;ifa_label)) ||
<a name="L1551" href="source/net/ipv4/devinet.c#L1551">1551</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, IFA_FLAGS, <a href="ident?i=ifa">ifa</a>-&gt;ifa_flags) ||
<a name="L1552" href="source/net/ipv4/devinet.c#L1552">1552</a>             <a href="ident?i=put_cacheinfo">put_cacheinfo</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_cstamp, <a href="ident?i=ifa">ifa</a>-&gt;ifa_tstamp,
<a name="L1553" href="source/net/ipv4/devinet.c#L1553">1553</a>                           preferred, <a href="ident?i=valid">valid</a>))
<a name="L1554" href="source/net/ipv4/devinet.c#L1554">1554</a>                 goto nla_put_failure;
<a name="L1555" href="source/net/ipv4/devinet.c#L1555">1555</a> 
<a name="L1556" href="source/net/ipv4/devinet.c#L1556">1556</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1557" href="source/net/ipv4/devinet.c#L1557">1557</a>         return 0;
<a name="L1558" href="source/net/ipv4/devinet.c#L1558">1558</a> 
<a name="L1559" href="source/net/ipv4/devinet.c#L1559">1559</a> nla_put_failure:
<a name="L1560" href="source/net/ipv4/devinet.c#L1560">1560</a>         <a href="ident?i=nlmsg_cancel">nlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1561" href="source/net/ipv4/devinet.c#L1561">1561</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1562" href="source/net/ipv4/devinet.c#L1562">1562</a> }
<a name="L1563" href="source/net/ipv4/devinet.c#L1563">1563</a> 
<a name="L1564" href="source/net/ipv4/devinet.c#L1564">1564</a> static int <a href="ident?i=inet_dump_ifaddr">inet_dump_ifaddr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L1565" href="source/net/ipv4/devinet.c#L1565">1565</a> {
<a name="L1566" href="source/net/ipv4/devinet.c#L1566">1566</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L1567" href="source/net/ipv4/devinet.c#L1567">1567</a>         int <a href="ident?i=h">h</a>, s_h;
<a name="L1568" href="source/net/ipv4/devinet.c#L1568">1568</a>         int <a href="ident?i=idx">idx</a>, s_idx;
<a name="L1569" href="source/net/ipv4/devinet.c#L1569">1569</a>         int ip_idx, s_ip_idx;
<a name="L1570" href="source/net/ipv4/devinet.c#L1570">1570</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1571" href="source/net/ipv4/devinet.c#L1571">1571</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1572" href="source/net/ipv4/devinet.c#L1572">1572</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L1573" href="source/net/ipv4/devinet.c#L1573">1573</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L1574" href="source/net/ipv4/devinet.c#L1574">1574</a> 
<a name="L1575" href="source/net/ipv4/devinet.c#L1575">1575</a>         s_h = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0];
<a name="L1576" href="source/net/ipv4/devinet.c#L1576">1576</a>         s_idx = <a href="ident?i=idx">idx</a> = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1];
<a name="L1577" href="source/net/ipv4/devinet.c#L1577">1577</a>         s_ip_idx = ip_idx = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2];
<a name="L1578" href="source/net/ipv4/devinet.c#L1578">1578</a> 
<a name="L1579" href="source/net/ipv4/devinet.c#L1579">1579</a>         for (<a href="ident?i=h">h</a> = s_h; <a href="ident?i=h">h</a> &lt; <a href="ident?i=NETDEV_HASHENTRIES">NETDEV_HASHENTRIES</a>; <a href="ident?i=h">h</a>++, s_idx = 0) {
<a name="L1580" href="source/net/ipv4/devinet.c#L1580">1580</a>                 <a href="ident?i=idx">idx</a> = 0;
<a name="L1581" href="source/net/ipv4/devinet.c#L1581">1581</a>                 <a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;dev_index_head[<a href="ident?i=h">h</a>];
<a name="L1582" href="source/net/ipv4/devinet.c#L1582">1582</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1583" href="source/net/ipv4/devinet.c#L1583">1583</a>                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid) ^
<a name="L1584" href="source/net/ipv4/devinet.c#L1584">1584</a>                           <a href="ident?i=net">net</a>-&gt;dev_base_seq;
<a name="L1585" href="source/net/ipv4/devinet.c#L1585">1585</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=head">head</a>, index_hlist) {
<a name="L1586" href="source/net/ipv4/devinet.c#L1586">1586</a>                         if (<a href="ident?i=idx">idx</a> &lt; s_idx)
<a name="L1587" href="source/net/ipv4/devinet.c#L1587">1587</a>                                 goto <a href="ident?i=cont">cont</a>;
<a name="L1588" href="source/net/ipv4/devinet.c#L1588">1588</a>                         if (<a href="ident?i=h">h</a> &gt; s_h || <a href="ident?i=idx">idx</a> &gt; s_idx)
<a name="L1589" href="source/net/ipv4/devinet.c#L1589">1589</a>                                 s_ip_idx = 0;
<a name="L1590" href="source/net/ipv4/devinet.c#L1590">1590</a>                         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1591" href="source/net/ipv4/devinet.c#L1591">1591</a>                         if (!in_dev)
<a name="L1592" href="source/net/ipv4/devinet.c#L1592">1592</a>                                 goto <a href="ident?i=cont">cont</a>;
<a name="L1593" href="source/net/ipv4/devinet.c#L1593">1593</a> 
<a name="L1594" href="source/net/ipv4/devinet.c#L1594">1594</a>                         for (<a href="ident?i=ifa">ifa</a> = in_dev-&gt;ifa_list, ip_idx = 0; <a href="ident?i=ifa">ifa</a>;
<a name="L1595" href="source/net/ipv4/devinet.c#L1595">1595</a>                              <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next, ip_idx++) {
<a name="L1596" href="source/net/ipv4/devinet.c#L1596">1596</a>                                 if (ip_idx &lt; s_ip_idx)
<a name="L1597" href="source/net/ipv4/devinet.c#L1597">1597</a>                                         continue;
<a name="L1598" href="source/net/ipv4/devinet.c#L1598">1598</a>                                 if (<a href="ident?i=inet_fill_ifaddr">inet_fill_ifaddr</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ifa">ifa</a>,
<a name="L1599" href="source/net/ipv4/devinet.c#L1599">1599</a>                                              <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L1600" href="source/net/ipv4/devinet.c#L1600">1600</a>                                              <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L1601" href="source/net/ipv4/devinet.c#L1601">1601</a>                                              <a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>) &lt; 0) {
<a name="L1602" href="source/net/ipv4/devinet.c#L1602">1602</a>                                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1603" href="source/net/ipv4/devinet.c#L1603">1603</a>                                         goto <a href="ident?i=done">done</a>;
<a name="L1604" href="source/net/ipv4/devinet.c#L1604">1604</a>                                 }
<a name="L1605" href="source/net/ipv4/devinet.c#L1605">1605</a>                                 <a href="ident?i=nl_dump_check_consistent">nl_dump_check_consistent</a>(<a href="ident?i=cb">cb</a>, <a href="ident?i=nlmsg_hdr">nlmsg_hdr</a>(<a href="ident?i=skb">skb</a>));
<a name="L1606" href="source/net/ipv4/devinet.c#L1606">1606</a>                         }
<a name="L1607" href="source/net/ipv4/devinet.c#L1607">1607</a> <a href="ident?i=cont">cont</a>:
<a name="L1608" href="source/net/ipv4/devinet.c#L1608">1608</a>                         <a href="ident?i=idx">idx</a>++;
<a name="L1609" href="source/net/ipv4/devinet.c#L1609">1609</a>                 }
<a name="L1610" href="source/net/ipv4/devinet.c#L1610">1610</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1611" href="source/net/ipv4/devinet.c#L1611">1611</a>         }
<a name="L1612" href="source/net/ipv4/devinet.c#L1612">1612</a> 
<a name="L1613" href="source/net/ipv4/devinet.c#L1613">1613</a> <a href="ident?i=done">done</a>:
<a name="L1614" href="source/net/ipv4/devinet.c#L1614">1614</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = <a href="ident?i=h">h</a>;
<a name="L1615" href="source/net/ipv4/devinet.c#L1615">1615</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = <a href="ident?i=idx">idx</a>;
<a name="L1616" href="source/net/ipv4/devinet.c#L1616">1616</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2] = ip_idx;
<a name="L1617" href="source/net/ipv4/devinet.c#L1617">1617</a> 
<a name="L1618" href="source/net/ipv4/devinet.c#L1618">1618</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1619" href="source/net/ipv4/devinet.c#L1619">1619</a> }
<a name="L1620" href="source/net/ipv4/devinet.c#L1620">1620</a> 
<a name="L1621" href="source/net/ipv4/devinet.c#L1621">1621</a> static void <a href="ident?i=rtmsg_ifa">rtmsg_ifa</a>(int <a href="ident?i=event">event</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L1622" href="source/net/ipv4/devinet.c#L1622">1622</a>                       <a href="ident?i=u32">u32</a> portid)
<a name="L1623" href="source/net/ipv4/devinet.c#L1623">1623</a> {
<a name="L1624" href="source/net/ipv4/devinet.c#L1624">1624</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1625" href="source/net/ipv4/devinet.c#L1625">1625</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a> = nlh ? nlh-&gt;nlmsg_seq : 0;
<a name="L1626" href="source/net/ipv4/devinet.c#L1626">1626</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1627" href="source/net/ipv4/devinet.c#L1627">1627</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L1628" href="source/net/ipv4/devinet.c#L1628">1628</a> 
<a name="L1629" href="source/net/ipv4/devinet.c#L1629">1629</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1630" href="source/net/ipv4/devinet.c#L1630">1630</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=inet_nlmsg_size">inet_nlmsg_size</a>(), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1631" href="source/net/ipv4/devinet.c#L1631">1631</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1632" href="source/net/ipv4/devinet.c#L1632">1632</a>                 goto errout;
<a name="L1633" href="source/net/ipv4/devinet.c#L1633">1633</a> 
<a name="L1634" href="source/net/ipv4/devinet.c#L1634">1634</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_fill_ifaddr">inet_fill_ifaddr</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ifa">ifa</a>, portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=event">event</a>, 0);
<a name="L1635" href="source/net/ipv4/devinet.c#L1635">1635</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L1636" href="source/net/ipv4/devinet.c#L1636">1636</a>                 <b><i>/* -EMSGSIZE implies BUG in inet_nlmsg_size() */</i></b>
<a name="L1637" href="source/net/ipv4/devinet.c#L1637">1637</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>);
<a name="L1638" href="source/net/ipv4/devinet.c#L1638">1638</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1639" href="source/net/ipv4/devinet.c#L1639">1639</a>                 goto errout;
<a name="L1640" href="source/net/ipv4/devinet.c#L1640">1640</a>         }
<a name="L1641" href="source/net/ipv4/devinet.c#L1641">1641</a>         <a href="ident?i=rtnl_notify">rtnl_notify</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, portid, <a href="ident?i=RTNLGRP_IPV4_IFADDR">RTNLGRP_IPV4_IFADDR</a>, nlh, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1642" href="source/net/ipv4/devinet.c#L1642">1642</a>         return;
<a name="L1643" href="source/net/ipv4/devinet.c#L1643">1643</a> errout:
<a name="L1644" href="source/net/ipv4/devinet.c#L1644">1644</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1645" href="source/net/ipv4/devinet.c#L1645">1645</a>                 <a href="ident?i=rtnl_set_sk_err">rtnl_set_sk_err</a>(<a href="ident?i=net">net</a>, <a href="ident?i=RTNLGRP_IPV4_IFADDR">RTNLGRP_IPV4_IFADDR</a>, <a href="ident?i=err">err</a>);
<a name="L1646" href="source/net/ipv4/devinet.c#L1646">1646</a> }
<a name="L1647" href="source/net/ipv4/devinet.c#L1647">1647</a> 
<a name="L1648" href="source/net/ipv4/devinet.c#L1648">1648</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=inet_get_link_af_size">inet_get_link_af_size</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1649" href="source/net/ipv4/devinet.c#L1649">1649</a> {
<a name="L1650" href="source/net/ipv4/devinet.c#L1650">1650</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=rcu_dereference_rtnl">rcu_dereference_rtnl</a>(<a href="ident?i=dev">dev</a>-&gt;ip_ptr);
<a name="L1651" href="source/net/ipv4/devinet.c#L1651">1651</a> 
<a name="L1652" href="source/net/ipv4/devinet.c#L1652">1652</a>         if (!in_dev)
<a name="L1653" href="source/net/ipv4/devinet.c#L1653">1653</a>                 return 0;
<a name="L1654" href="source/net/ipv4/devinet.c#L1654">1654</a> 
<a name="L1655" href="source/net/ipv4/devinet.c#L1655">1655</a>         return <a href="ident?i=nla_total_size">nla_total_size</a>(<a href="ident?i=IPV4_DEVCONF_MAX">IPV4_DEVCONF_MAX</a> * 4); <b><i>/* IFLA_INET_CONF */</i></b>
<a name="L1656" href="source/net/ipv4/devinet.c#L1656">1656</a> }
<a name="L1657" href="source/net/ipv4/devinet.c#L1657">1657</a> 
<a name="L1658" href="source/net/ipv4/devinet.c#L1658">1658</a> static int <a href="ident?i=inet_fill_link_af">inet_fill_link_af</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1659" href="source/net/ipv4/devinet.c#L1659">1659</a> {
<a name="L1660" href="source/net/ipv4/devinet.c#L1660">1660</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=rcu_dereference_rtnl">rcu_dereference_rtnl</a>(<a href="ident?i=dev">dev</a>-&gt;ip_ptr);
<a name="L1661" href="source/net/ipv4/devinet.c#L1661">1661</a>         struct <a href="ident?i=nlattr">nlattr</a> *nla;
<a name="L1662" href="source/net/ipv4/devinet.c#L1662">1662</a>         int <a href="ident?i=i">i</a>;
<a name="L1663" href="source/net/ipv4/devinet.c#L1663">1663</a> 
<a name="L1664" href="source/net/ipv4/devinet.c#L1664">1664</a>         if (!in_dev)
<a name="L1665" href="source/net/ipv4/devinet.c#L1665">1665</a>                 return -<a href="ident?i=ENODATA">ENODATA</a>;
<a name="L1666" href="source/net/ipv4/devinet.c#L1666">1666</a> 
<a name="L1667" href="source/net/ipv4/devinet.c#L1667">1667</a>         nla = <a href="ident?i=nla_reserve">nla_reserve</a>(<a href="ident?i=skb">skb</a>, IFLA_INET_CONF, <a href="ident?i=IPV4_DEVCONF_MAX">IPV4_DEVCONF_MAX</a> * 4);
<a name="L1668" href="source/net/ipv4/devinet.c#L1668">1668</a>         if (!nla)
<a name="L1669" href="source/net/ipv4/devinet.c#L1669">1669</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1670" href="source/net/ipv4/devinet.c#L1670">1670</a> 
<a name="L1671" href="source/net/ipv4/devinet.c#L1671">1671</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=IPV4_DEVCONF_MAX">IPV4_DEVCONF_MAX</a>; <a href="ident?i=i">i</a>++)
<a name="L1672" href="source/net/ipv4/devinet.c#L1672">1672</a>                 ((<a href="ident?i=u32">u32</a> *) <a href="ident?i=nla_data">nla_data</a>(nla))[<a href="ident?i=i">i</a>] = in_dev-&gt;cnf.<a href="ident?i=data">data</a>[<a href="ident?i=i">i</a>];
<a name="L1673" href="source/net/ipv4/devinet.c#L1673">1673</a> 
<a name="L1674" href="source/net/ipv4/devinet.c#L1674">1674</a>         return 0;
<a name="L1675" href="source/net/ipv4/devinet.c#L1675">1675</a> }
<a name="L1676" href="source/net/ipv4/devinet.c#L1676">1676</a> 
<a name="L1677" href="source/net/ipv4/devinet.c#L1677">1677</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=inet_af_policy">inet_af_policy</a>[<a href="ident?i=IFLA_INET_MAX">IFLA_INET_MAX</a>+1] = {
<a name="L1678" href="source/net/ipv4/devinet.c#L1678">1678</a>         [IFLA_INET_CONF]        = { .<a href="ident?i=type">type</a> = NLA_NESTED },
<a name="L1679" href="source/net/ipv4/devinet.c#L1679">1679</a> };
<a name="L1680" href="source/net/ipv4/devinet.c#L1680">1680</a> 
<a name="L1681" href="source/net/ipv4/devinet.c#L1681">1681</a> static int <a href="ident?i=inet_validate_link_af">inet_validate_link_af</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L1682" href="source/net/ipv4/devinet.c#L1682">1682</a>                                  const struct <a href="ident?i=nlattr">nlattr</a> *nla)
<a name="L1683" href="source/net/ipv4/devinet.c#L1683">1683</a> {
<a name="L1684" href="source/net/ipv4/devinet.c#L1684">1684</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=a">a</a>, *<a href="ident?i=tb">tb</a>[<a href="ident?i=IFLA_INET_MAX">IFLA_INET_MAX</a>+1];
<a name="L1685" href="source/net/ipv4/devinet.c#L1685">1685</a>         int <a href="ident?i=err">err</a>, rem;
<a name="L1686" href="source/net/ipv4/devinet.c#L1686">1686</a> 
<a name="L1687" href="source/net/ipv4/devinet.c#L1687">1687</a>         if (<a href="ident?i=dev">dev</a> &amp;&amp; !<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>))
<a name="L1688" href="source/net/ipv4/devinet.c#L1688">1688</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L1689" href="source/net/ipv4/devinet.c#L1689">1689</a> 
<a name="L1690" href="source/net/ipv4/devinet.c#L1690">1690</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nla_parse_nested">nla_parse_nested</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=IFLA_INET_MAX">IFLA_INET_MAX</a>, nla, <a href="ident?i=inet_af_policy">inet_af_policy</a>);
<a name="L1691" href="source/net/ipv4/devinet.c#L1691">1691</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1692" href="source/net/ipv4/devinet.c#L1692">1692</a>                 return <a href="ident?i=err">err</a>;
<a name="L1693" href="source/net/ipv4/devinet.c#L1693">1693</a> 
<a name="L1694" href="source/net/ipv4/devinet.c#L1694">1694</a>         if (<a href="ident?i=tb">tb</a>[IFLA_INET_CONF]) {
<a name="L1695" href="source/net/ipv4/devinet.c#L1695">1695</a>                 <a href="ident?i=nla_for_each_nested">nla_for_each_nested</a>(<a href="ident?i=a">a</a>, <a href="ident?i=tb">tb</a>[IFLA_INET_CONF], rem) {
<a name="L1696" href="source/net/ipv4/devinet.c#L1696">1696</a>                         int cfgid = <a href="ident?i=nla_type">nla_type</a>(<a href="ident?i=a">a</a>);
<a name="L1697" href="source/net/ipv4/devinet.c#L1697">1697</a> 
<a name="L1698" href="source/net/ipv4/devinet.c#L1698">1698</a>                         if (<a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=a">a</a>) &lt; 4)
<a name="L1699" href="source/net/ipv4/devinet.c#L1699">1699</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1700" href="source/net/ipv4/devinet.c#L1700">1700</a> 
<a name="L1701" href="source/net/ipv4/devinet.c#L1701">1701</a>                         if (cfgid &lt;= 0 || cfgid &gt; <a href="ident?i=IPV4_DEVCONF_MAX">IPV4_DEVCONF_MAX</a>)
<a name="L1702" href="source/net/ipv4/devinet.c#L1702">1702</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1703" href="source/net/ipv4/devinet.c#L1703">1703</a>                 }
<a name="L1704" href="source/net/ipv4/devinet.c#L1704">1704</a>         }
<a name="L1705" href="source/net/ipv4/devinet.c#L1705">1705</a> 
<a name="L1706" href="source/net/ipv4/devinet.c#L1706">1706</a>         return 0;
<a name="L1707" href="source/net/ipv4/devinet.c#L1707">1707</a> }
<a name="L1708" href="source/net/ipv4/devinet.c#L1708">1708</a> 
<a name="L1709" href="source/net/ipv4/devinet.c#L1709">1709</a> static int <a href="ident?i=inet_set_link_af">inet_set_link_af</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, const struct <a href="ident?i=nlattr">nlattr</a> *nla)
<a name="L1710" href="source/net/ipv4/devinet.c#L1710">1710</a> {
<a name="L1711" href="source/net/ipv4/devinet.c#L1711">1711</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L1712" href="source/net/ipv4/devinet.c#L1712">1712</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=a">a</a>, *<a href="ident?i=tb">tb</a>[<a href="ident?i=IFLA_INET_MAX">IFLA_INET_MAX</a>+1];
<a name="L1713" href="source/net/ipv4/devinet.c#L1713">1713</a>         int rem;
<a name="L1714" href="source/net/ipv4/devinet.c#L1714">1714</a> 
<a name="L1715" href="source/net/ipv4/devinet.c#L1715">1715</a>         if (!in_dev)
<a name="L1716" href="source/net/ipv4/devinet.c#L1716">1716</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L1717" href="source/net/ipv4/devinet.c#L1717">1717</a> 
<a name="L1718" href="source/net/ipv4/devinet.c#L1718">1718</a>         if (<a href="ident?i=nla_parse_nested">nla_parse_nested</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=IFLA_INET_MAX">IFLA_INET_MAX</a>, nla, <a href="ident?i=NULL">NULL</a>) &lt; 0)
<a name="L1719" href="source/net/ipv4/devinet.c#L1719">1719</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L1720" href="source/net/ipv4/devinet.c#L1720">1720</a> 
<a name="L1721" href="source/net/ipv4/devinet.c#L1721">1721</a>         if (<a href="ident?i=tb">tb</a>[IFLA_INET_CONF]) {
<a name="L1722" href="source/net/ipv4/devinet.c#L1722">1722</a>                 <a href="ident?i=nla_for_each_nested">nla_for_each_nested</a>(<a href="ident?i=a">a</a>, <a href="ident?i=tb">tb</a>[IFLA_INET_CONF], rem)
<a name="L1723" href="source/net/ipv4/devinet.c#L1723">1723</a>                         <a href="ident?i=ipv4_devconf_set">ipv4_devconf_set</a>(in_dev, <a href="ident?i=nla_type">nla_type</a>(<a href="ident?i=a">a</a>), <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=a">a</a>));
<a name="L1724" href="source/net/ipv4/devinet.c#L1724">1724</a>         }
<a name="L1725" href="source/net/ipv4/devinet.c#L1725">1725</a> 
<a name="L1726" href="source/net/ipv4/devinet.c#L1726">1726</a>         return 0;
<a name="L1727" href="source/net/ipv4/devinet.c#L1727">1727</a> }
<a name="L1728" href="source/net/ipv4/devinet.c#L1728">1728</a> 
<a name="L1729" href="source/net/ipv4/devinet.c#L1729">1729</a> static int <a href="ident?i=inet_netconf_msgsize_devconf">inet_netconf_msgsize_devconf</a>(int <a href="ident?i=type">type</a>)
<a name="L1730" href="source/net/ipv4/devinet.c#L1730">1730</a> {
<a name="L1731" href="source/net/ipv4/devinet.c#L1731">1731</a>         int <a href="ident?i=size">size</a> = <a href="ident?i=NLMSG_ALIGN">NLMSG_ALIGN</a>(sizeof(struct <a href="ident?i=netconfmsg">netconfmsg</a>))
<a name="L1732" href="source/net/ipv4/devinet.c#L1732">1732</a>                    + <a href="ident?i=nla_total_size">nla_total_size</a>(4); <b><i>/* NETCONFA_IFINDEX */</i></b>
<a name="L1733" href="source/net/ipv4/devinet.c#L1733">1733</a> 
<a name="L1734" href="source/net/ipv4/devinet.c#L1734">1734</a>         <b><i>/* type -1 is used for ALL */</i></b>
<a name="L1735" href="source/net/ipv4/devinet.c#L1735">1735</a>         if (<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_FORWARDING)
<a name="L1736" href="source/net/ipv4/devinet.c#L1736">1736</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=nla_total_size">nla_total_size</a>(4);
<a name="L1737" href="source/net/ipv4/devinet.c#L1737">1737</a>         if (<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_RP_FILTER)
<a name="L1738" href="source/net/ipv4/devinet.c#L1738">1738</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=nla_total_size">nla_total_size</a>(4);
<a name="L1739" href="source/net/ipv4/devinet.c#L1739">1739</a>         if (<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_MC_FORWARDING)
<a name="L1740" href="source/net/ipv4/devinet.c#L1740">1740</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=nla_total_size">nla_total_size</a>(4);
<a name="L1741" href="source/net/ipv4/devinet.c#L1741">1741</a>         if (<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_PROXY_NEIGH)
<a name="L1742" href="source/net/ipv4/devinet.c#L1742">1742</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=nla_total_size">nla_total_size</a>(4);
<a name="L1743" href="source/net/ipv4/devinet.c#L1743">1743</a> 
<a name="L1744" href="source/net/ipv4/devinet.c#L1744">1744</a>         return <a href="ident?i=size">size</a>;
<a name="L1745" href="source/net/ipv4/devinet.c#L1745">1745</a> }
<a name="L1746" href="source/net/ipv4/devinet.c#L1746">1746</a> 
<a name="L1747" href="source/net/ipv4/devinet.c#L1747">1747</a> static int <a href="ident?i=inet_netconf_fill_devconf">inet_netconf_fill_devconf</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int ifindex,
<a name="L1748" href="source/net/ipv4/devinet.c#L1748">1748</a>                                      struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *devconf, <a href="ident?i=u32">u32</a> portid,
<a name="L1749" href="source/net/ipv4/devinet.c#L1749">1749</a>                                      <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, int <a href="ident?i=event">event</a>, unsigned int <a href="ident?i=flags">flags</a>,
<a name="L1750" href="source/net/ipv4/devinet.c#L1750">1750</a>                                      int <a href="ident?i=type">type</a>)
<a name="L1751" href="source/net/ipv4/devinet.c#L1751">1751</a> {
<a name="L1752" href="source/net/ipv4/devinet.c#L1752">1752</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a>  *nlh;
<a name="L1753" href="source/net/ipv4/devinet.c#L1753">1753</a>         struct <a href="ident?i=netconfmsg">netconfmsg</a> *ncm;
<a name="L1754" href="source/net/ipv4/devinet.c#L1754">1754</a> 
<a name="L1755" href="source/net/ipv4/devinet.c#L1755">1755</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=event">event</a>, sizeof(struct <a href="ident?i=netconfmsg">netconfmsg</a>),
<a name="L1756" href="source/net/ipv4/devinet.c#L1756">1756</a>                         <a href="ident?i=flags">flags</a>);
<a name="L1757" href="source/net/ipv4/devinet.c#L1757">1757</a>         if (!nlh)
<a name="L1758" href="source/net/ipv4/devinet.c#L1758">1758</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1759" href="source/net/ipv4/devinet.c#L1759">1759</a> 
<a name="L1760" href="source/net/ipv4/devinet.c#L1760">1760</a>         ncm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L1761" href="source/net/ipv4/devinet.c#L1761">1761</a>         ncm-&gt;ncm_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L1762" href="source/net/ipv4/devinet.c#L1762">1762</a> 
<a name="L1763" href="source/net/ipv4/devinet.c#L1763">1763</a>         if (<a href="ident?i=nla_put_s32">nla_put_s32</a>(<a href="ident?i=skb">skb</a>, NETCONFA_IFINDEX, ifindex) &lt; 0)
<a name="L1764" href="source/net/ipv4/devinet.c#L1764">1764</a>                 goto nla_put_failure;
<a name="L1765" href="source/net/ipv4/devinet.c#L1765">1765</a> 
<a name="L1766" href="source/net/ipv4/devinet.c#L1766">1766</a>         <b><i>/* type -1 is used for ALL */</i></b>
<a name="L1767" href="source/net/ipv4/devinet.c#L1767">1767</a>         if ((<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_FORWARDING) &amp;&amp;
<a name="L1768" href="source/net/ipv4/devinet.c#L1768">1768</a>             <a href="ident?i=nla_put_s32">nla_put_s32</a>(<a href="ident?i=skb">skb</a>, NETCONFA_FORWARDING,
<a name="L1769" href="source/net/ipv4/devinet.c#L1769">1769</a>                         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(*devconf, FORWARDING)) &lt; 0)
<a name="L1770" href="source/net/ipv4/devinet.c#L1770">1770</a>                 goto nla_put_failure;
<a name="L1771" href="source/net/ipv4/devinet.c#L1771">1771</a>         if ((<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_RP_FILTER) &amp;&amp;
<a name="L1772" href="source/net/ipv4/devinet.c#L1772">1772</a>             <a href="ident?i=nla_put_s32">nla_put_s32</a>(<a href="ident?i=skb">skb</a>, NETCONFA_RP_FILTER,
<a name="L1773" href="source/net/ipv4/devinet.c#L1773">1773</a>                         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(*devconf, RP_FILTER)) &lt; 0)
<a name="L1774" href="source/net/ipv4/devinet.c#L1774">1774</a>                 goto nla_put_failure;
<a name="L1775" href="source/net/ipv4/devinet.c#L1775">1775</a>         if ((<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_MC_FORWARDING) &amp;&amp;
<a name="L1776" href="source/net/ipv4/devinet.c#L1776">1776</a>             <a href="ident?i=nla_put_s32">nla_put_s32</a>(<a href="ident?i=skb">skb</a>, NETCONFA_MC_FORWARDING,
<a name="L1777" href="source/net/ipv4/devinet.c#L1777">1777</a>                         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(*devconf, MC_FORWARDING)) &lt; 0)
<a name="L1778" href="source/net/ipv4/devinet.c#L1778">1778</a>                 goto nla_put_failure;
<a name="L1779" href="source/net/ipv4/devinet.c#L1779">1779</a>         if ((<a href="ident?i=type">type</a> == -1 || <a href="ident?i=type">type</a> == NETCONFA_PROXY_NEIGH) &amp;&amp;
<a name="L1780" href="source/net/ipv4/devinet.c#L1780">1780</a>             <a href="ident?i=nla_put_s32">nla_put_s32</a>(<a href="ident?i=skb">skb</a>, NETCONFA_PROXY_NEIGH,
<a name="L1781" href="source/net/ipv4/devinet.c#L1781">1781</a>                         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(*devconf, PROXY_ARP)) &lt; 0)
<a name="L1782" href="source/net/ipv4/devinet.c#L1782">1782</a>                 goto nla_put_failure;
<a name="L1783" href="source/net/ipv4/devinet.c#L1783">1783</a> 
<a name="L1784" href="source/net/ipv4/devinet.c#L1784">1784</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1785" href="source/net/ipv4/devinet.c#L1785">1785</a>         return 0;
<a name="L1786" href="source/net/ipv4/devinet.c#L1786">1786</a> 
<a name="L1787" href="source/net/ipv4/devinet.c#L1787">1787</a> nla_put_failure:
<a name="L1788" href="source/net/ipv4/devinet.c#L1788">1788</a>         <a href="ident?i=nlmsg_cancel">nlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1789" href="source/net/ipv4/devinet.c#L1789">1789</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1790" href="source/net/ipv4/devinet.c#L1790">1790</a> }
<a name="L1791" href="source/net/ipv4/devinet.c#L1791">1791</a> 
<a name="L1792" href="source/net/ipv4/devinet.c#L1792">1792</a> void <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int <a href="ident?i=type">type</a>, int ifindex,
<a name="L1793" href="source/net/ipv4/devinet.c#L1793">1793</a>                                  struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *devconf)
<a name="L1794" href="source/net/ipv4/devinet.c#L1794">1794</a> {
<a name="L1795" href="source/net/ipv4/devinet.c#L1795">1795</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1796" href="source/net/ipv4/devinet.c#L1796">1796</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1797" href="source/net/ipv4/devinet.c#L1797">1797</a> 
<a name="L1798" href="source/net/ipv4/devinet.c#L1798">1798</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=inet_netconf_msgsize_devconf">inet_netconf_msgsize_devconf</a>(<a href="ident?i=type">type</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1799" href="source/net/ipv4/devinet.c#L1799">1799</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1800" href="source/net/ipv4/devinet.c#L1800">1800</a>                 goto errout;
<a name="L1801" href="source/net/ipv4/devinet.c#L1801">1801</a> 
<a name="L1802" href="source/net/ipv4/devinet.c#L1802">1802</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_netconf_fill_devconf">inet_netconf_fill_devconf</a>(<a href="ident?i=skb">skb</a>, ifindex, devconf, 0, 0,
<a name="L1803" href="source/net/ipv4/devinet.c#L1803">1803</a>                                         <a href="ident?i=RTM_NEWNETCONF">RTM_NEWNETCONF</a>, 0, <a href="ident?i=type">type</a>);
<a name="L1804" href="source/net/ipv4/devinet.c#L1804">1804</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L1805" href="source/net/ipv4/devinet.c#L1805">1805</a>                 <b><i>/* -EMSGSIZE implies BUG in inet_netconf_msgsize_devconf() */</i></b>
<a name="L1806" href="source/net/ipv4/devinet.c#L1806">1806</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>);
<a name="L1807" href="source/net/ipv4/devinet.c#L1807">1807</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1808" href="source/net/ipv4/devinet.c#L1808">1808</a>                 goto errout;
<a name="L1809" href="source/net/ipv4/devinet.c#L1809">1809</a>         }
<a name="L1810" href="source/net/ipv4/devinet.c#L1810">1810</a>         <a href="ident?i=rtnl_notify">rtnl_notify</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, <a href="ident?i=RTNLGRP_IPV4_NETCONF">RTNLGRP_IPV4_NETCONF</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1811" href="source/net/ipv4/devinet.c#L1811">1811</a>         return;
<a name="L1812" href="source/net/ipv4/devinet.c#L1812">1812</a> errout:
<a name="L1813" href="source/net/ipv4/devinet.c#L1813">1813</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1814" href="source/net/ipv4/devinet.c#L1814">1814</a>                 <a href="ident?i=rtnl_set_sk_err">rtnl_set_sk_err</a>(<a href="ident?i=net">net</a>, <a href="ident?i=RTNLGRP_IPV4_NETCONF">RTNLGRP_IPV4_NETCONF</a>, <a href="ident?i=err">err</a>);
<a name="L1815" href="source/net/ipv4/devinet.c#L1815">1815</a> }
<a name="L1816" href="source/net/ipv4/devinet.c#L1816">1816</a> 
<a name="L1817" href="source/net/ipv4/devinet.c#L1817">1817</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=devconf_ipv4_policy">devconf_ipv4_policy</a>[<a href="ident?i=NETCONFA_MAX">NETCONFA_MAX</a>+1] = {
<a name="L1818" href="source/net/ipv4/devinet.c#L1818">1818</a>         [NETCONFA_IFINDEX]      = { .<a href="ident?i=len">len</a> = sizeof(int) },
<a name="L1819" href="source/net/ipv4/devinet.c#L1819">1819</a>         [NETCONFA_FORWARDING]   = { .<a href="ident?i=len">len</a> = sizeof(int) },
<a name="L1820" href="source/net/ipv4/devinet.c#L1820">1820</a>         [NETCONFA_RP_FILTER]    = { .<a href="ident?i=len">len</a> = sizeof(int) },
<a name="L1821" href="source/net/ipv4/devinet.c#L1821">1821</a>         [NETCONFA_PROXY_NEIGH]  = { .<a href="ident?i=len">len</a> = sizeof(int) },
<a name="L1822" href="source/net/ipv4/devinet.c#L1822">1822</a> };
<a name="L1823" href="source/net/ipv4/devinet.c#L1823">1823</a> 
<a name="L1824" href="source/net/ipv4/devinet.c#L1824">1824</a> static int <a href="ident?i=inet_netconf_get_devconf">inet_netconf_get_devconf</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb,
<a name="L1825" href="source/net/ipv4/devinet.c#L1825">1825</a>                                     struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L1826" href="source/net/ipv4/devinet.c#L1826">1826</a> {
<a name="L1827" href="source/net/ipv4/devinet.c#L1827">1827</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(in_skb-&gt;sk);
<a name="L1828" href="source/net/ipv4/devinet.c#L1828">1828</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[<a href="ident?i=NETCONFA_MAX">NETCONFA_MAX</a>+1];
<a name="L1829" href="source/net/ipv4/devinet.c#L1829">1829</a>         struct <a href="ident?i=netconfmsg">netconfmsg</a> *ncm;
<a name="L1830" href="source/net/ipv4/devinet.c#L1830">1830</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1831" href="source/net/ipv4/devinet.c#L1831">1831</a>         struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *devconf;
<a name="L1832" href="source/net/ipv4/devinet.c#L1832">1832</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1833" href="source/net/ipv4/devinet.c#L1833">1833</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1834" href="source/net/ipv4/devinet.c#L1834">1834</a>         int ifindex;
<a name="L1835" href="source/net/ipv4/devinet.c#L1835">1835</a>         int <a href="ident?i=err">err</a>;
<a name="L1836" href="source/net/ipv4/devinet.c#L1836">1836</a> 
<a name="L1837" href="source/net/ipv4/devinet.c#L1837">1837</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nlmsg_parse">nlmsg_parse</a>(nlh, sizeof(*ncm), <a href="ident?i=tb">tb</a>, <a href="ident?i=NETCONFA_MAX">NETCONFA_MAX</a>,
<a name="L1838" href="source/net/ipv4/devinet.c#L1838">1838</a>                           <a href="ident?i=devconf_ipv4_policy">devconf_ipv4_policy</a>);
<a name="L1839" href="source/net/ipv4/devinet.c#L1839">1839</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1840" href="source/net/ipv4/devinet.c#L1840">1840</a>                 goto errout;
<a name="L1841" href="source/net/ipv4/devinet.c#L1841">1841</a> 
<a name="L1842" href="source/net/ipv4/devinet.c#L1842">1842</a>         <a href="ident?i=err">err</a> = <a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1843" href="source/net/ipv4/devinet.c#L1843">1843</a>         if (!<a href="ident?i=tb">tb</a>[NETCONFA_IFINDEX])
<a name="L1844" href="source/net/ipv4/devinet.c#L1844">1844</a>                 goto errout;
<a name="L1845" href="source/net/ipv4/devinet.c#L1845">1845</a> 
<a name="L1846" href="source/net/ipv4/devinet.c#L1846">1846</a>         ifindex = <a href="ident?i=nla_get_s32">nla_get_s32</a>(<a href="ident?i=tb">tb</a>[NETCONFA_IFINDEX]);
<a name="L1847" href="source/net/ipv4/devinet.c#L1847">1847</a>         switch (ifindex) {
<a name="L1848" href="source/net/ipv4/devinet.c#L1848">1848</a>         case <a href="ident?i=NETCONFA_IFINDEX_ALL">NETCONFA_IFINDEX_ALL</a>:
<a name="L1849" href="source/net/ipv4/devinet.c#L1849">1849</a>                 devconf = <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all;
<a name="L1850" href="source/net/ipv4/devinet.c#L1850">1850</a>                 break;
<a name="L1851" href="source/net/ipv4/devinet.c#L1851">1851</a>         case <a href="ident?i=NETCONFA_IFINDEX_DEFAULT">NETCONFA_IFINDEX_DEFAULT</a>:
<a name="L1852" href="source/net/ipv4/devinet.c#L1852">1852</a>                 devconf = <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt;
<a name="L1853" href="source/net/ipv4/devinet.c#L1853">1853</a>                 break;
<a name="L1854" href="source/net/ipv4/devinet.c#L1854">1854</a>         default:
<a name="L1855" href="source/net/ipv4/devinet.c#L1855">1855</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_index">__dev_get_by_index</a>(<a href="ident?i=net">net</a>, ifindex);
<a name="L1856" href="source/net/ipv4/devinet.c#L1856">1856</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L1857" href="source/net/ipv4/devinet.c#L1857">1857</a>                         goto errout;
<a name="L1858" href="source/net/ipv4/devinet.c#L1858">1858</a>                 in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L1859" href="source/net/ipv4/devinet.c#L1859">1859</a>                 if (!in_dev)
<a name="L1860" href="source/net/ipv4/devinet.c#L1860">1860</a>                         goto errout;
<a name="L1861" href="source/net/ipv4/devinet.c#L1861">1861</a>                 devconf = &amp;in_dev-&gt;cnf;
<a name="L1862" href="source/net/ipv4/devinet.c#L1862">1862</a>                 break;
<a name="L1863" href="source/net/ipv4/devinet.c#L1863">1863</a>         }
<a name="L1864" href="source/net/ipv4/devinet.c#L1864">1864</a> 
<a name="L1865" href="source/net/ipv4/devinet.c#L1865">1865</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1866" href="source/net/ipv4/devinet.c#L1866">1866</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=inet_netconf_msgsize_devconf">inet_netconf_msgsize_devconf</a>(-1), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1867" href="source/net/ipv4/devinet.c#L1867">1867</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1868" href="source/net/ipv4/devinet.c#L1868">1868</a>                 goto errout;
<a name="L1869" href="source/net/ipv4/devinet.c#L1869">1869</a> 
<a name="L1870" href="source/net/ipv4/devinet.c#L1870">1870</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_netconf_fill_devconf">inet_netconf_fill_devconf</a>(<a href="ident?i=skb">skb</a>, ifindex, devconf,
<a name="L1871" href="source/net/ipv4/devinet.c#L1871">1871</a>                                         <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid,
<a name="L1872" href="source/net/ipv4/devinet.c#L1872">1872</a>                                         nlh-&gt;nlmsg_seq, <a href="ident?i=RTM_NEWNETCONF">RTM_NEWNETCONF</a>, 0,
<a name="L1873" href="source/net/ipv4/devinet.c#L1873">1873</a>                                         -1);
<a name="L1874" href="source/net/ipv4/devinet.c#L1874">1874</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L1875" href="source/net/ipv4/devinet.c#L1875">1875</a>                 <b><i>/* -EMSGSIZE implies BUG in inet_netconf_msgsize_devconf() */</i></b>
<a name="L1876" href="source/net/ipv4/devinet.c#L1876">1876</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>);
<a name="L1877" href="source/net/ipv4/devinet.c#L1877">1877</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1878" href="source/net/ipv4/devinet.c#L1878">1878</a>                 goto errout;
<a name="L1879" href="source/net/ipv4/devinet.c#L1879">1879</a>         }
<a name="L1880" href="source/net/ipv4/devinet.c#L1880">1880</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtnl_unicast">rtnl_unicast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid);
<a name="L1881" href="source/net/ipv4/devinet.c#L1881">1881</a> errout:
<a name="L1882" href="source/net/ipv4/devinet.c#L1882">1882</a>         return <a href="ident?i=err">err</a>;
<a name="L1883" href="source/net/ipv4/devinet.c#L1883">1883</a> }
<a name="L1884" href="source/net/ipv4/devinet.c#L1884">1884</a> 
<a name="L1885" href="source/net/ipv4/devinet.c#L1885">1885</a> static int <a href="ident?i=inet_netconf_dump_devconf">inet_netconf_dump_devconf</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1886" href="source/net/ipv4/devinet.c#L1886">1886</a>                                      struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L1887" href="source/net/ipv4/devinet.c#L1887">1887</a> {
<a name="L1888" href="source/net/ipv4/devinet.c#L1888">1888</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L1889" href="source/net/ipv4/devinet.c#L1889">1889</a>         int <a href="ident?i=h">h</a>, s_h;
<a name="L1890" href="source/net/ipv4/devinet.c#L1890">1890</a>         int <a href="ident?i=idx">idx</a>, s_idx;
<a name="L1891" href="source/net/ipv4/devinet.c#L1891">1891</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1892" href="source/net/ipv4/devinet.c#L1892">1892</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1893" href="source/net/ipv4/devinet.c#L1893">1893</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L1894" href="source/net/ipv4/devinet.c#L1894">1894</a> 
<a name="L1895" href="source/net/ipv4/devinet.c#L1895">1895</a>         s_h = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0];
<a name="L1896" href="source/net/ipv4/devinet.c#L1896">1896</a>         s_idx = <a href="ident?i=idx">idx</a> = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1];
<a name="L1897" href="source/net/ipv4/devinet.c#L1897">1897</a> 
<a name="L1898" href="source/net/ipv4/devinet.c#L1898">1898</a>         for (<a href="ident?i=h">h</a> = s_h; <a href="ident?i=h">h</a> &lt; <a href="ident?i=NETDEV_HASHENTRIES">NETDEV_HASHENTRIES</a>; <a href="ident?i=h">h</a>++, s_idx = 0) {
<a name="L1899" href="source/net/ipv4/devinet.c#L1899">1899</a>                 <a href="ident?i=idx">idx</a> = 0;
<a name="L1900" href="source/net/ipv4/devinet.c#L1900">1900</a>                 <a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;dev_index_head[<a href="ident?i=h">h</a>];
<a name="L1901" href="source/net/ipv4/devinet.c#L1901">1901</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1902" href="source/net/ipv4/devinet.c#L1902">1902</a>                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid) ^
<a name="L1903" href="source/net/ipv4/devinet.c#L1903">1903</a>                           <a href="ident?i=net">net</a>-&gt;dev_base_seq;
<a name="L1904" href="source/net/ipv4/devinet.c#L1904">1904</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=head">head</a>, index_hlist) {
<a name="L1905" href="source/net/ipv4/devinet.c#L1905">1905</a>                         if (<a href="ident?i=idx">idx</a> &lt; s_idx)
<a name="L1906" href="source/net/ipv4/devinet.c#L1906">1906</a>                                 goto <a href="ident?i=cont">cont</a>;
<a name="L1907" href="source/net/ipv4/devinet.c#L1907">1907</a>                         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1908" href="source/net/ipv4/devinet.c#L1908">1908</a>                         if (!in_dev)
<a name="L1909" href="source/net/ipv4/devinet.c#L1909">1909</a>                                 goto <a href="ident?i=cont">cont</a>;
<a name="L1910" href="source/net/ipv4/devinet.c#L1910">1910</a> 
<a name="L1911" href="source/net/ipv4/devinet.c#L1911">1911</a>                         if (<a href="ident?i=inet_netconf_fill_devconf">inet_netconf_fill_devconf</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>-&gt;ifindex,
<a name="L1912" href="source/net/ipv4/devinet.c#L1912">1912</a>                                                       &amp;in_dev-&gt;cnf,
<a name="L1913" href="source/net/ipv4/devinet.c#L1913">1913</a>                                                       <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L1914" href="source/net/ipv4/devinet.c#L1914">1914</a>                                                       <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L1915" href="source/net/ipv4/devinet.c#L1915">1915</a>                                                       <a href="ident?i=RTM_NEWNETCONF">RTM_NEWNETCONF</a>,
<a name="L1916" href="source/net/ipv4/devinet.c#L1916">1916</a>                                                       <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>,
<a name="L1917" href="source/net/ipv4/devinet.c#L1917">1917</a>                                                       -1) &lt; 0) {
<a name="L1918" href="source/net/ipv4/devinet.c#L1918">1918</a>                                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1919" href="source/net/ipv4/devinet.c#L1919">1919</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L1920" href="source/net/ipv4/devinet.c#L1920">1920</a>                         }
<a name="L1921" href="source/net/ipv4/devinet.c#L1921">1921</a>                         <a href="ident?i=nl_dump_check_consistent">nl_dump_check_consistent</a>(<a href="ident?i=cb">cb</a>, <a href="ident?i=nlmsg_hdr">nlmsg_hdr</a>(<a href="ident?i=skb">skb</a>));
<a name="L1922" href="source/net/ipv4/devinet.c#L1922">1922</a> <a href="ident?i=cont">cont</a>:
<a name="L1923" href="source/net/ipv4/devinet.c#L1923">1923</a>                         <a href="ident?i=idx">idx</a>++;
<a name="L1924" href="source/net/ipv4/devinet.c#L1924">1924</a>                 }
<a name="L1925" href="source/net/ipv4/devinet.c#L1925">1925</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1926" href="source/net/ipv4/devinet.c#L1926">1926</a>         }
<a name="L1927" href="source/net/ipv4/devinet.c#L1927">1927</a>         if (<a href="ident?i=h">h</a> == <a href="ident?i=NETDEV_HASHENTRIES">NETDEV_HASHENTRIES</a>) {
<a name="L1928" href="source/net/ipv4/devinet.c#L1928">1928</a>                 if (<a href="ident?i=inet_netconf_fill_devconf">inet_netconf_fill_devconf</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NETCONFA_IFINDEX_ALL">NETCONFA_IFINDEX_ALL</a>,
<a name="L1929" href="source/net/ipv4/devinet.c#L1929">1929</a>                                               <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all,
<a name="L1930" href="source/net/ipv4/devinet.c#L1930">1930</a>                                               <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L1931" href="source/net/ipv4/devinet.c#L1931">1931</a>                                               <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L1932" href="source/net/ipv4/devinet.c#L1932">1932</a>                                               <a href="ident?i=RTM_NEWNETCONF">RTM_NEWNETCONF</a>, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>,
<a name="L1933" href="source/net/ipv4/devinet.c#L1933">1933</a>                                               -1) &lt; 0)
<a name="L1934" href="source/net/ipv4/devinet.c#L1934">1934</a>                         goto <a href="ident?i=done">done</a>;
<a name="L1935" href="source/net/ipv4/devinet.c#L1935">1935</a>                 else
<a name="L1936" href="source/net/ipv4/devinet.c#L1936">1936</a>                         <a href="ident?i=h">h</a>++;
<a name="L1937" href="source/net/ipv4/devinet.c#L1937">1937</a>         }
<a name="L1938" href="source/net/ipv4/devinet.c#L1938">1938</a>         if (<a href="ident?i=h">h</a> == <a href="ident?i=NETDEV_HASHENTRIES">NETDEV_HASHENTRIES</a> + 1) {
<a name="L1939" href="source/net/ipv4/devinet.c#L1939">1939</a>                 if (<a href="ident?i=inet_netconf_fill_devconf">inet_netconf_fill_devconf</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NETCONFA_IFINDEX_DEFAULT">NETCONFA_IFINDEX_DEFAULT</a>,
<a name="L1940" href="source/net/ipv4/devinet.c#L1940">1940</a>                                               <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt,
<a name="L1941" href="source/net/ipv4/devinet.c#L1941">1941</a>                                               <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L1942" href="source/net/ipv4/devinet.c#L1942">1942</a>                                               <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L1943" href="source/net/ipv4/devinet.c#L1943">1943</a>                                               <a href="ident?i=RTM_NEWNETCONF">RTM_NEWNETCONF</a>, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>,
<a name="L1944" href="source/net/ipv4/devinet.c#L1944">1944</a>                                               -1) &lt; 0)
<a name="L1945" href="source/net/ipv4/devinet.c#L1945">1945</a>                         goto <a href="ident?i=done">done</a>;
<a name="L1946" href="source/net/ipv4/devinet.c#L1946">1946</a>                 else
<a name="L1947" href="source/net/ipv4/devinet.c#L1947">1947</a>                         <a href="ident?i=h">h</a>++;
<a name="L1948" href="source/net/ipv4/devinet.c#L1948">1948</a>         }
<a name="L1949" href="source/net/ipv4/devinet.c#L1949">1949</a> <a href="ident?i=done">done</a>:
<a name="L1950" href="source/net/ipv4/devinet.c#L1950">1950</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = <a href="ident?i=h">h</a>;
<a name="L1951" href="source/net/ipv4/devinet.c#L1951">1951</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = <a href="ident?i=idx">idx</a>;
<a name="L1952" href="source/net/ipv4/devinet.c#L1952">1952</a> 
<a name="L1953" href="source/net/ipv4/devinet.c#L1953">1953</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1954" href="source/net/ipv4/devinet.c#L1954">1954</a> }
<a name="L1955" href="source/net/ipv4/devinet.c#L1955">1955</a> 
<a name="L1956" href="source/net/ipv4/devinet.c#L1956">1956</a> #ifdef CONFIG_SYSCTL
<a name="L1957" href="source/net/ipv4/devinet.c#L1957">1957</a> 
<a name="L1958" href="source/net/ipv4/devinet.c#L1958">1958</a> static void <a href="ident?i=devinet_copy_dflt_conf">devinet_copy_dflt_conf</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int <a href="ident?i=i">i</a>)
<a name="L1959" href="source/net/ipv4/devinet.c#L1959">1959</a> {
<a name="L1960" href="source/net/ipv4/devinet.c#L1960">1960</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1961" href="source/net/ipv4/devinet.c#L1961">1961</a> 
<a name="L1962" href="source/net/ipv4/devinet.c#L1962">1962</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1963" href="source/net/ipv4/devinet.c#L1963">1963</a>         <a href="ident?i=for_each_netdev_rcu">for_each_netdev_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L1964" href="source/net/ipv4/devinet.c#L1964">1964</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1965" href="source/net/ipv4/devinet.c#L1965">1965</a> 
<a name="L1966" href="source/net/ipv4/devinet.c#L1966">1966</a>                 in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1967" href="source/net/ipv4/devinet.c#L1967">1967</a>                 if (in_dev &amp;&amp; !<a href="ident?i=test_bit">test_bit</a>(<a href="ident?i=i">i</a>, in_dev-&gt;cnf.<a href="ident?i=state">state</a>))
<a name="L1968" href="source/net/ipv4/devinet.c#L1968">1968</a>                         in_dev-&gt;cnf.<a href="ident?i=data">data</a>[<a href="ident?i=i">i</a>] = <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt-&gt;<a href="ident?i=data">data</a>[<a href="ident?i=i">i</a>];
<a name="L1969" href="source/net/ipv4/devinet.c#L1969">1969</a>         }
<a name="L1970" href="source/net/ipv4/devinet.c#L1970">1970</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1971" href="source/net/ipv4/devinet.c#L1971">1971</a> }
<a name="L1972" href="source/net/ipv4/devinet.c#L1972">1972</a> 
<a name="L1973" href="source/net/ipv4/devinet.c#L1973">1973</a> <b><i>/* called with RTNL locked */</i></b>
<a name="L1974" href="source/net/ipv4/devinet.c#L1974">1974</a> static void <a href="ident?i=inet_forward_change">inet_forward_change</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1975" href="source/net/ipv4/devinet.c#L1975">1975</a> {
<a name="L1976" href="source/net/ipv4/devinet.c#L1976">1976</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1977" href="source/net/ipv4/devinet.c#L1977">1977</a>         int <a href="ident?i=on">on</a> = <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, FORWARDING);
<a name="L1978" href="source/net/ipv4/devinet.c#L1978">1978</a> 
<a name="L1979" href="source/net/ipv4/devinet.c#L1979">1979</a>         <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, ACCEPT_REDIRECTS) = !<a href="ident?i=on">on</a>;
<a name="L1980" href="source/net/ipv4/devinet.c#L1980">1980</a>         <a href="ident?i=IPV4_DEVCONF_DFLT">IPV4_DEVCONF_DFLT</a>(<a href="ident?i=net">net</a>, FORWARDING) = <a href="ident?i=on">on</a>;
<a name="L1981" href="source/net/ipv4/devinet.c#L1981">1981</a>         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_FORWARDING,
<a name="L1982" href="source/net/ipv4/devinet.c#L1982">1982</a>                                     <a href="ident?i=NETCONFA_IFINDEX_ALL">NETCONFA_IFINDEX_ALL</a>,
<a name="L1983" href="source/net/ipv4/devinet.c#L1983">1983</a>                                     <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all);
<a name="L1984" href="source/net/ipv4/devinet.c#L1984">1984</a>         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_FORWARDING,
<a name="L1985" href="source/net/ipv4/devinet.c#L1985">1985</a>                                     <a href="ident?i=NETCONFA_IFINDEX_DEFAULT">NETCONFA_IFINDEX_DEFAULT</a>,
<a name="L1986" href="source/net/ipv4/devinet.c#L1986">1986</a>                                     <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt);
<a name="L1987" href="source/net/ipv4/devinet.c#L1987">1987</a> 
<a name="L1988" href="source/net/ipv4/devinet.c#L1988">1988</a>         <a href="ident?i=for_each_netdev">for_each_netdev</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L1989" href="source/net/ipv4/devinet.c#L1989">1989</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1990" href="source/net/ipv4/devinet.c#L1990">1990</a>                 if (<a href="ident?i=on">on</a>)
<a name="L1991" href="source/net/ipv4/devinet.c#L1991">1991</a>                         <a href="ident?i=dev_disable_lro">dev_disable_lro</a>(<a href="ident?i=dev">dev</a>);
<a name="L1992" href="source/net/ipv4/devinet.c#L1992">1992</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1993" href="source/net/ipv4/devinet.c#L1993">1993</a>                 in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1994" href="source/net/ipv4/devinet.c#L1994">1994</a>                 if (in_dev) {
<a name="L1995" href="source/net/ipv4/devinet.c#L1995">1995</a>                         <a href="ident?i=IN_DEV_CONF_SET">IN_DEV_CONF_SET</a>(in_dev, FORWARDING, <a href="ident?i=on">on</a>);
<a name="L1996" href="source/net/ipv4/devinet.c#L1996">1996</a>                         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_FORWARDING,
<a name="L1997" href="source/net/ipv4/devinet.c#L1997">1997</a>                                                     <a href="ident?i=dev">dev</a>-&gt;ifindex, &amp;in_dev-&gt;cnf);
<a name="L1998" href="source/net/ipv4/devinet.c#L1998">1998</a>                 }
<a name="L1999" href="source/net/ipv4/devinet.c#L1999">1999</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2000" href="source/net/ipv4/devinet.c#L2000">2000</a>         }
<a name="L2001" href="source/net/ipv4/devinet.c#L2001">2001</a> }
<a name="L2002" href="source/net/ipv4/devinet.c#L2002">2002</a> 
<a name="L2003" href="source/net/ipv4/devinet.c#L2003">2003</a> static int <a href="ident?i=devinet_conf_ifindex">devinet_conf_ifindex</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *cnf)
<a name="L2004" href="source/net/ipv4/devinet.c#L2004">2004</a> {
<a name="L2005" href="source/net/ipv4/devinet.c#L2005">2005</a>         if (cnf == <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt)
<a name="L2006" href="source/net/ipv4/devinet.c#L2006">2006</a>                 return <a href="ident?i=NETCONFA_IFINDEX_DEFAULT">NETCONFA_IFINDEX_DEFAULT</a>;
<a name="L2007" href="source/net/ipv4/devinet.c#L2007">2007</a>         else if (cnf == <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all)
<a name="L2008" href="source/net/ipv4/devinet.c#L2008">2008</a>                 return <a href="ident?i=NETCONFA_IFINDEX_ALL">NETCONFA_IFINDEX_ALL</a>;
<a name="L2009" href="source/net/ipv4/devinet.c#L2009">2009</a>         else {
<a name="L2010" href="source/net/ipv4/devinet.c#L2010">2010</a>                 struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>
<a name="L2011" href="source/net/ipv4/devinet.c#L2011">2011</a>                         = <a href="ident?i=container_of">container_of</a>(cnf, struct <a href="ident?i=in_device">in_device</a>, cnf);
<a name="L2012" href="source/net/ipv4/devinet.c#L2012">2012</a>                 return <a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L2013" href="source/net/ipv4/devinet.c#L2013">2013</a>         }
<a name="L2014" href="source/net/ipv4/devinet.c#L2014">2014</a> }
<a name="L2015" href="source/net/ipv4/devinet.c#L2015">2015</a> 
<a name="L2016" href="source/net/ipv4/devinet.c#L2016">2016</a> static int <a href="ident?i=devinet_conf_proc">devinet_conf_proc</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>, int <a href="ident?i=write">write</a>,
<a name="L2017" href="source/net/ipv4/devinet.c#L2017">2017</a>                              void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>,
<a name="L2018" href="source/net/ipv4/devinet.c#L2018">2018</a>                              <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L2019" href="source/net/ipv4/devinet.c#L2019">2019</a> {
<a name="L2020" href="source/net/ipv4/devinet.c#L2020">2020</a>         int old_value = *(int *)<a href="ident?i=ctl">ctl</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L2021" href="source/net/ipv4/devinet.c#L2021">2021</a>         int <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dointvec">proc_dointvec</a>(<a href="ident?i=ctl">ctl</a>, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L2022" href="source/net/ipv4/devinet.c#L2022">2022</a>         int new_value = *(int *)<a href="ident?i=ctl">ctl</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L2023" href="source/net/ipv4/devinet.c#L2023">2023</a> 
<a name="L2024" href="source/net/ipv4/devinet.c#L2024">2024</a>         if (<a href="ident?i=write">write</a>) {
<a name="L2025" href="source/net/ipv4/devinet.c#L2025">2025</a>                 struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *cnf = <a href="ident?i=ctl">ctl</a>-&gt;extra1;
<a name="L2026" href="source/net/ipv4/devinet.c#L2026">2026</a>                 struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=ctl">ctl</a>-&gt;extra2;
<a name="L2027" href="source/net/ipv4/devinet.c#L2027">2027</a>                 int <a href="ident?i=i">i</a> = (int *)<a href="ident?i=ctl">ctl</a>-&gt;<a href="ident?i=data">data</a> - cnf-&gt;<a href="ident?i=data">data</a>;
<a name="L2028" href="source/net/ipv4/devinet.c#L2028">2028</a>                 int ifindex;
<a name="L2029" href="source/net/ipv4/devinet.c#L2029">2029</a> 
<a name="L2030" href="source/net/ipv4/devinet.c#L2030">2030</a>                 <a href="ident?i=set_bit">set_bit</a>(<a href="ident?i=i">i</a>, cnf-&gt;<a href="ident?i=state">state</a>);
<a name="L2031" href="source/net/ipv4/devinet.c#L2031">2031</a> 
<a name="L2032" href="source/net/ipv4/devinet.c#L2032">2032</a>                 if (cnf == <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt)
<a name="L2033" href="source/net/ipv4/devinet.c#L2033">2033</a>                         <a href="ident?i=devinet_copy_dflt_conf">devinet_copy_dflt_conf</a>(<a href="ident?i=net">net</a>, <a href="ident?i=i">i</a>);
<a name="L2034" href="source/net/ipv4/devinet.c#L2034">2034</a>                 if (<a href="ident?i=i">i</a> == IPV4_DEVCONF_ACCEPT_LOCAL - 1 ||
<a name="L2035" href="source/net/ipv4/devinet.c#L2035">2035</a>                     <a href="ident?i=i">i</a> == IPV4_DEVCONF_ROUTE_LOCALNET - 1)
<a name="L2036" href="source/net/ipv4/devinet.c#L2036">2036</a>                         if ((new_value == 0) &amp;&amp; (old_value != 0))
<a name="L2037" href="source/net/ipv4/devinet.c#L2037">2037</a>                                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L2038" href="source/net/ipv4/devinet.c#L2038">2038</a> 
<a name="L2039" href="source/net/ipv4/devinet.c#L2039">2039</a>                 if (<a href="ident?i=i">i</a> == IPV4_DEVCONF_RP_FILTER - 1 &amp;&amp;
<a name="L2040" href="source/net/ipv4/devinet.c#L2040">2040</a>                     new_value != old_value) {
<a name="L2041" href="source/net/ipv4/devinet.c#L2041">2041</a>                         ifindex = <a href="ident?i=devinet_conf_ifindex">devinet_conf_ifindex</a>(<a href="ident?i=net">net</a>, cnf);
<a name="L2042" href="source/net/ipv4/devinet.c#L2042">2042</a>                         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_RP_FILTER,
<a name="L2043" href="source/net/ipv4/devinet.c#L2043">2043</a>                                                     ifindex, cnf);
<a name="L2044" href="source/net/ipv4/devinet.c#L2044">2044</a>                 }
<a name="L2045" href="source/net/ipv4/devinet.c#L2045">2045</a>                 if (<a href="ident?i=i">i</a> == IPV4_DEVCONF_PROXY_ARP - 1 &amp;&amp;
<a name="L2046" href="source/net/ipv4/devinet.c#L2046">2046</a>                     new_value != old_value) {
<a name="L2047" href="source/net/ipv4/devinet.c#L2047">2047</a>                         ifindex = <a href="ident?i=devinet_conf_ifindex">devinet_conf_ifindex</a>(<a href="ident?i=net">net</a>, cnf);
<a name="L2048" href="source/net/ipv4/devinet.c#L2048">2048</a>                         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_PROXY_NEIGH,
<a name="L2049" href="source/net/ipv4/devinet.c#L2049">2049</a>                                                     ifindex, cnf);
<a name="L2050" href="source/net/ipv4/devinet.c#L2050">2050</a>                 }
<a name="L2051" href="source/net/ipv4/devinet.c#L2051">2051</a>         }
<a name="L2052" href="source/net/ipv4/devinet.c#L2052">2052</a> 
<a name="L2053" href="source/net/ipv4/devinet.c#L2053">2053</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2054" href="source/net/ipv4/devinet.c#L2054">2054</a> }
<a name="L2055" href="source/net/ipv4/devinet.c#L2055">2055</a> 
<a name="L2056" href="source/net/ipv4/devinet.c#L2056">2056</a> static int <a href="ident?i=devinet_sysctl_forward">devinet_sysctl_forward</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>, int <a href="ident?i=write">write</a>,
<a name="L2057" href="source/net/ipv4/devinet.c#L2057">2057</a>                                   void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>,
<a name="L2058" href="source/net/ipv4/devinet.c#L2058">2058</a>                                   <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L2059" href="source/net/ipv4/devinet.c#L2059">2059</a> {
<a name="L2060" href="source/net/ipv4/devinet.c#L2060">2060</a>         int *valp = <a href="ident?i=ctl">ctl</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L2061" href="source/net/ipv4/devinet.c#L2061">2061</a>         int <a href="ident?i=val">val</a> = *valp;
<a name="L2062" href="source/net/ipv4/devinet.c#L2062">2062</a>         <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a> = *<a href="ident?i=ppos">ppos</a>;
<a name="L2063" href="source/net/ipv4/devinet.c#L2063">2063</a>         int <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dointvec">proc_dointvec</a>(<a href="ident?i=ctl">ctl</a>, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L2064" href="source/net/ipv4/devinet.c#L2064">2064</a> 
<a name="L2065" href="source/net/ipv4/devinet.c#L2065">2065</a>         if (<a href="ident?i=write">write</a> &amp;&amp; *valp != <a href="ident?i=val">val</a>) {
<a name="L2066" href="source/net/ipv4/devinet.c#L2066">2066</a>                 struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=ctl">ctl</a>-&gt;extra2;
<a name="L2067" href="source/net/ipv4/devinet.c#L2067">2067</a> 
<a name="L2068" href="source/net/ipv4/devinet.c#L2068">2068</a>                 if (valp != &amp;<a href="ident?i=IPV4_DEVCONF_DFLT">IPV4_DEVCONF_DFLT</a>(<a href="ident?i=net">net</a>, FORWARDING)) {
<a name="L2069" href="source/net/ipv4/devinet.c#L2069">2069</a>                         if (!<a href="ident?i=rtnl_trylock">rtnl_trylock</a>()) {
<a name="L2070" href="source/net/ipv4/devinet.c#L2070">2070</a>                                 <b><i>/* Restore the original values before restarting */</i></b>
<a name="L2071" href="source/net/ipv4/devinet.c#L2071">2071</a>                                 *valp = <a href="ident?i=val">val</a>;
<a name="L2072" href="source/net/ipv4/devinet.c#L2072">2072</a>                                 *<a href="ident?i=ppos">ppos</a> = <a href="ident?i=pos">pos</a>;
<a name="L2073" href="source/net/ipv4/devinet.c#L2073">2073</a>                                 return <a href="ident?i=restart_syscall">restart_syscall</a>();
<a name="L2074" href="source/net/ipv4/devinet.c#L2074">2074</a>                         }
<a name="L2075" href="source/net/ipv4/devinet.c#L2075">2075</a>                         if (valp == &amp;<a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, FORWARDING)) {
<a name="L2076" href="source/net/ipv4/devinet.c#L2076">2076</a>                                 <a href="ident?i=inet_forward_change">inet_forward_change</a>(<a href="ident?i=net">net</a>);
<a name="L2077" href="source/net/ipv4/devinet.c#L2077">2077</a>                         } else {
<a name="L2078" href="source/net/ipv4/devinet.c#L2078">2078</a>                                 struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *cnf = <a href="ident?i=ctl">ctl</a>-&gt;extra1;
<a name="L2079" href="source/net/ipv4/devinet.c#L2079">2079</a>                                 struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a> =
<a name="L2080" href="source/net/ipv4/devinet.c#L2080">2080</a>                                         <a href="ident?i=container_of">container_of</a>(cnf, struct <a href="ident?i=in_device">in_device</a>, cnf);
<a name="L2081" href="source/net/ipv4/devinet.c#L2081">2081</a>                                 if (*valp)
<a name="L2082" href="source/net/ipv4/devinet.c#L2082">2082</a>                                         <a href="ident?i=dev_disable_lro">dev_disable_lro</a>(<a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2083" href="source/net/ipv4/devinet.c#L2083">2083</a>                                 <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>,
<a name="L2084" href="source/net/ipv4/devinet.c#L2084">2084</a>                                                             NETCONFA_FORWARDING,
<a name="L2085" href="source/net/ipv4/devinet.c#L2085">2085</a>                                                             <a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex,
<a name="L2086" href="source/net/ipv4/devinet.c#L2086">2086</a>                                                             cnf);
<a name="L2087" href="source/net/ipv4/devinet.c#L2087">2087</a>                         }
<a name="L2088" href="source/net/ipv4/devinet.c#L2088">2088</a>                         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L2089" href="source/net/ipv4/devinet.c#L2089">2089</a>                         <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L2090" href="source/net/ipv4/devinet.c#L2090">2090</a>                 } else
<a name="L2091" href="source/net/ipv4/devinet.c#L2091">2091</a>                         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_FORWARDING,
<a name="L2092" href="source/net/ipv4/devinet.c#L2092">2092</a>                                                     <a href="ident?i=NETCONFA_IFINDEX_DEFAULT">NETCONFA_IFINDEX_DEFAULT</a>,
<a name="L2093" href="source/net/ipv4/devinet.c#L2093">2093</a>                                                     <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt);
<a name="L2094" href="source/net/ipv4/devinet.c#L2094">2094</a>         }
<a name="L2095" href="source/net/ipv4/devinet.c#L2095">2095</a> 
<a name="L2096" href="source/net/ipv4/devinet.c#L2096">2096</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2097" href="source/net/ipv4/devinet.c#L2097">2097</a> }
<a name="L2098" href="source/net/ipv4/devinet.c#L2098">2098</a> 
<a name="L2099" href="source/net/ipv4/devinet.c#L2099">2099</a> static int <a href="ident?i=ipv4_doint_and_flush">ipv4_doint_and_flush</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>, int <a href="ident?i=write">write</a>,
<a name="L2100" href="source/net/ipv4/devinet.c#L2100">2100</a>                                 void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>,
<a name="L2101" href="source/net/ipv4/devinet.c#L2101">2101</a>                                 <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L2102" href="source/net/ipv4/devinet.c#L2102">2102</a> {
<a name="L2103" href="source/net/ipv4/devinet.c#L2103">2103</a>         int *valp = <a href="ident?i=ctl">ctl</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L2104" href="source/net/ipv4/devinet.c#L2104">2104</a>         int <a href="ident?i=val">val</a> = *valp;
<a name="L2105" href="source/net/ipv4/devinet.c#L2105">2105</a>         int <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dointvec">proc_dointvec</a>(<a href="ident?i=ctl">ctl</a>, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L2106" href="source/net/ipv4/devinet.c#L2106">2106</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=ctl">ctl</a>-&gt;extra2;
<a name="L2107" href="source/net/ipv4/devinet.c#L2107">2107</a> 
<a name="L2108" href="source/net/ipv4/devinet.c#L2108">2108</a>         if (<a href="ident?i=write">write</a> &amp;&amp; *valp != <a href="ident?i=val">val</a>)
<a name="L2109" href="source/net/ipv4/devinet.c#L2109">2109</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L2110" href="source/net/ipv4/devinet.c#L2110">2110</a> 
<a name="L2111" href="source/net/ipv4/devinet.c#L2111">2111</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2112" href="source/net/ipv4/devinet.c#L2112">2112</a> }
<a name="L2113" href="source/net/ipv4/devinet.c#L2113">2113</a> 
<a name="L2114" href="source/net/ipv4/devinet.c#L2114">2114</a> #define <a href="ident?i=DEVINET_SYSCTL_ENTRY">DEVINET_SYSCTL_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>, <a href="ident?i=mval">mval</a>, proc) \
<a name="L2115" href="source/net/ipv4/devinet.c#L2115">2115</a>         { \
<a name="L2116" href="source/net/ipv4/devinet.c#L2116">2116</a>                 .<a href="ident?i=procname">procname</a>       = <a href="ident?i=name">name</a>, \
<a name="L2117" href="source/net/ipv4/devinet.c#L2117">2117</a>                 .<a href="ident?i=data">data</a>           = <a href="ident?i=ipv4_devconf">ipv4_devconf</a>.<a href="ident?i=data">data</a> + \
<a name="L2118" href="source/net/ipv4/devinet.c#L2118">2118</a>                                   IPV4_DEVCONF_ ## <a href="ident?i=attr">attr</a> - 1, \
<a name="L2119" href="source/net/ipv4/devinet.c#L2119">2119</a>                 .maxlen         = sizeof(int), \
<a name="L2120" href="source/net/ipv4/devinet.c#L2120">2120</a>                 .<a href="ident?i=mode">mode</a>           = <a href="ident?i=mval">mval</a>, \
<a name="L2121" href="source/net/ipv4/devinet.c#L2121">2121</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = proc, \
<a name="L2122" href="source/net/ipv4/devinet.c#L2122">2122</a>                 .extra1         = &amp;<a href="ident?i=ipv4_devconf">ipv4_devconf</a>, \
<a name="L2123" href="source/net/ipv4/devinet.c#L2123">2123</a>         }
<a name="L2124" href="source/net/ipv4/devinet.c#L2124">2124</a> 
<a name="L2125" href="source/net/ipv4/devinet.c#L2125">2125</a> #define <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>) \
<a name="L2126" href="source/net/ipv4/devinet.c#L2126">2126</a>         <a href="ident?i=DEVINET_SYSCTL_ENTRY">DEVINET_SYSCTL_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>, 0644, <a href="ident?i=devinet_conf_proc">devinet_conf_proc</a>)
<a name="L2127" href="source/net/ipv4/devinet.c#L2127">2127</a> 
<a name="L2128" href="source/net/ipv4/devinet.c#L2128">2128</a> #define <a href="ident?i=DEVINET_SYSCTL_RO_ENTRY">DEVINET_SYSCTL_RO_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>) \
<a name="L2129" href="source/net/ipv4/devinet.c#L2129">2129</a>         <a href="ident?i=DEVINET_SYSCTL_ENTRY">DEVINET_SYSCTL_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>, 0444, <a href="ident?i=devinet_conf_proc">devinet_conf_proc</a>)
<a name="L2130" href="source/net/ipv4/devinet.c#L2130">2130</a> 
<a name="L2131" href="source/net/ipv4/devinet.c#L2131">2131</a> #define <a href="ident?i=DEVINET_SYSCTL_COMPLEX_ENTRY">DEVINET_SYSCTL_COMPLEX_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>, proc) \
<a name="L2132" href="source/net/ipv4/devinet.c#L2132">2132</a>         <a href="ident?i=DEVINET_SYSCTL_ENTRY">DEVINET_SYSCTL_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>, 0644, proc)
<a name="L2133" href="source/net/ipv4/devinet.c#L2133">2133</a> 
<a name="L2134" href="source/net/ipv4/devinet.c#L2134">2134</a> #define <a href="ident?i=DEVINET_SYSCTL_FLUSHING_ENTRY">DEVINET_SYSCTL_FLUSHING_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>) \
<a name="L2135" href="source/net/ipv4/devinet.c#L2135">2135</a>         <a href="ident?i=DEVINET_SYSCTL_COMPLEX_ENTRY">DEVINET_SYSCTL_COMPLEX_ENTRY</a>(<a href="ident?i=attr">attr</a>, <a href="ident?i=name">name</a>, <a href="ident?i=ipv4_doint_and_flush">ipv4_doint_and_flush</a>)
<a name="L2136" href="source/net/ipv4/devinet.c#L2136">2136</a> 
<a name="L2137" href="source/net/ipv4/devinet.c#L2137">2137</a> static struct <a href="ident?i=devinet_sysctl_table">devinet_sysctl_table</a> {
<a name="L2138" href="source/net/ipv4/devinet.c#L2138">2138</a>         struct <a href="ident?i=ctl_table_header">ctl_table_header</a> *<a href="ident?i=sysctl_header">sysctl_header</a>;
<a name="L2139" href="source/net/ipv4/devinet.c#L2139">2139</a>         struct <a href="ident?i=ctl_table">ctl_table</a> devinet_vars[__IPV4_DEVCONF_MAX];
<a name="L2140" href="source/net/ipv4/devinet.c#L2140">2140</a> } <a href="ident?i=devinet_sysctl">devinet_sysctl</a> = {
<a name="L2141" href="source/net/ipv4/devinet.c#L2141">2141</a>         .devinet_vars = {
<a name="L2142" href="source/net/ipv4/devinet.c#L2142">2142</a>                 <a href="ident?i=DEVINET_SYSCTL_COMPLEX_ENTRY">DEVINET_SYSCTL_COMPLEX_ENTRY</a>(FORWARDING, <i>"forwarding"</i>,
<a name="L2143" href="source/net/ipv4/devinet.c#L2143">2143</a>                                              <a href="ident?i=devinet_sysctl_forward">devinet_sysctl_forward</a>),
<a name="L2144" href="source/net/ipv4/devinet.c#L2144">2144</a>                 <a href="ident?i=DEVINET_SYSCTL_RO_ENTRY">DEVINET_SYSCTL_RO_ENTRY</a>(MC_FORWARDING, <i>"mc_forwarding"</i>),
<a name="L2145" href="source/net/ipv4/devinet.c#L2145">2145</a> 
<a name="L2146" href="source/net/ipv4/devinet.c#L2146">2146</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ACCEPT_REDIRECTS, <i>"accept_redirects"</i>),
<a name="L2147" href="source/net/ipv4/devinet.c#L2147">2147</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(SECURE_REDIRECTS, <i>"secure_redirects"</i>),
<a name="L2148" href="source/net/ipv4/devinet.c#L2148">2148</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(SHARED_MEDIA, <i>"shared_media"</i>),
<a name="L2149" href="source/net/ipv4/devinet.c#L2149">2149</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(RP_FILTER, <i>"rp_filter"</i>),
<a name="L2150" href="source/net/ipv4/devinet.c#L2150">2150</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(SEND_REDIRECTS, <i>"send_redirects"</i>),
<a name="L2151" href="source/net/ipv4/devinet.c#L2151">2151</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ACCEPT_SOURCE_ROUTE,
<a name="L2152" href="source/net/ipv4/devinet.c#L2152">2152</a>                                         <i>"accept_source_route"</i>),
<a name="L2153" href="source/net/ipv4/devinet.c#L2153">2153</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ACCEPT_LOCAL, <i>"accept_local"</i>),
<a name="L2154" href="source/net/ipv4/devinet.c#L2154">2154</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(SRC_VMARK, <i>"src_valid_mark"</i>),
<a name="L2155" href="source/net/ipv4/devinet.c#L2155">2155</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(PROXY_ARP, <i>"proxy_arp"</i>),
<a name="L2156" href="source/net/ipv4/devinet.c#L2156">2156</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(MEDIUM_ID, <i>"medium_id"</i>),
<a name="L2157" href="source/net/ipv4/devinet.c#L2157">2157</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(BOOTP_RELAY, <i>"bootp_relay"</i>),
<a name="L2158" href="source/net/ipv4/devinet.c#L2158">2158</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(LOG_MARTIANS, <i>"log_martians"</i>),
<a name="L2159" href="source/net/ipv4/devinet.c#L2159">2159</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(<a href="ident?i=TAG">TAG</a>, <i>"tag"</i>),
<a name="L2160" href="source/net/ipv4/devinet.c#L2160">2160</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ARPFILTER, <i>"arp_filter"</i>),
<a name="L2161" href="source/net/ipv4/devinet.c#L2161">2161</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ARP_ANNOUNCE, <i>"arp_announce"</i>),
<a name="L2162" href="source/net/ipv4/devinet.c#L2162">2162</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ARP_IGNORE, <i>"arp_ignore"</i>),
<a name="L2163" href="source/net/ipv4/devinet.c#L2163">2163</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ARP_ACCEPT, <i>"arp_accept"</i>),
<a name="L2164" href="source/net/ipv4/devinet.c#L2164">2164</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(ARP_NOTIFY, <i>"arp_notify"</i>),
<a name="L2165" href="source/net/ipv4/devinet.c#L2165">2165</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(PROXY_ARP_PVLAN, <i>"proxy_arp_pvlan"</i>),
<a name="L2166" href="source/net/ipv4/devinet.c#L2166">2166</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(FORCE_IGMP_VERSION,
<a name="L2167" href="source/net/ipv4/devinet.c#L2167">2167</a>                                         <i>"force_igmp_version"</i>),
<a name="L2168" href="source/net/ipv4/devinet.c#L2168">2168</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(IGMPV2_UNSOLICITED_REPORT_INTERVAL,
<a name="L2169" href="source/net/ipv4/devinet.c#L2169">2169</a>                                         <i>"igmpv2_unsolicited_report_interval"</i>),
<a name="L2170" href="source/net/ipv4/devinet.c#L2170">2170</a>                 <a href="ident?i=DEVINET_SYSCTL_RW_ENTRY">DEVINET_SYSCTL_RW_ENTRY</a>(IGMPV3_UNSOLICITED_REPORT_INTERVAL,
<a name="L2171" href="source/net/ipv4/devinet.c#L2171">2171</a>                                         <i>"igmpv3_unsolicited_report_interval"</i>),
<a name="L2172" href="source/net/ipv4/devinet.c#L2172">2172</a> 
<a name="L2173" href="source/net/ipv4/devinet.c#L2173">2173</a>                 <a href="ident?i=DEVINET_SYSCTL_FLUSHING_ENTRY">DEVINET_SYSCTL_FLUSHING_ENTRY</a>(NOXFRM, <i>"disable_xfrm"</i>),
<a name="L2174" href="source/net/ipv4/devinet.c#L2174">2174</a>                 <a href="ident?i=DEVINET_SYSCTL_FLUSHING_ENTRY">DEVINET_SYSCTL_FLUSHING_ENTRY</a>(NOPOLICY, <i>"disable_policy"</i>),
<a name="L2175" href="source/net/ipv4/devinet.c#L2175">2175</a>                 <a href="ident?i=DEVINET_SYSCTL_FLUSHING_ENTRY">DEVINET_SYSCTL_FLUSHING_ENTRY</a>(PROMOTE_SECONDARIES,
<a name="L2176" href="source/net/ipv4/devinet.c#L2176">2176</a>                                               <i>"promote_secondaries"</i>),
<a name="L2177" href="source/net/ipv4/devinet.c#L2177">2177</a>                 <a href="ident?i=DEVINET_SYSCTL_FLUSHING_ENTRY">DEVINET_SYSCTL_FLUSHING_ENTRY</a>(ROUTE_LOCALNET,
<a name="L2178" href="source/net/ipv4/devinet.c#L2178">2178</a>                                               <i>"route_localnet"</i>),
<a name="L2179" href="source/net/ipv4/devinet.c#L2179">2179</a>         },
<a name="L2180" href="source/net/ipv4/devinet.c#L2180">2180</a> };
<a name="L2181" href="source/net/ipv4/devinet.c#L2181">2181</a> 
<a name="L2182" href="source/net/ipv4/devinet.c#L2182">2182</a> static int <a href="ident?i=__devinet_sysctl_register">__devinet_sysctl_register</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, char *<a href="ident?i=dev_name">dev_name</a>,
<a name="L2183" href="source/net/ipv4/devinet.c#L2183">2183</a>                                         struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *<a href="ident?i=p">p</a>)
<a name="L2184" href="source/net/ipv4/devinet.c#L2184">2184</a> {
<a name="L2185" href="source/net/ipv4/devinet.c#L2185">2185</a>         int <a href="ident?i=i">i</a>;
<a name="L2186" href="source/net/ipv4/devinet.c#L2186">2186</a>         struct <a href="ident?i=devinet_sysctl_table">devinet_sysctl_table</a> *<a href="ident?i=t">t</a>;
<a name="L2187" href="source/net/ipv4/devinet.c#L2187">2187</a>         char <a href="ident?i=path">path</a>[sizeof(<i>"net/ipv4/conf/"</i>) + <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>];
<a name="L2188" href="source/net/ipv4/devinet.c#L2188">2188</a> 
<a name="L2189" href="source/net/ipv4/devinet.c#L2189">2189</a>         <a href="ident?i=t">t</a> = <a href="ident?i=kmemdup">kmemdup</a>(&amp;<a href="ident?i=devinet_sysctl">devinet_sysctl</a>, sizeof(*<a href="ident?i=t">t</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2190" href="source/net/ipv4/devinet.c#L2190">2190</a>         if (!<a href="ident?i=t">t</a>)
<a name="L2191" href="source/net/ipv4/devinet.c#L2191">2191</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2192" href="source/net/ipv4/devinet.c#L2192">2192</a> 
<a name="L2193" href="source/net/ipv4/devinet.c#L2193">2193</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=t">t</a>-&gt;devinet_vars) - 1; <a href="ident?i=i">i</a>++) {
<a name="L2194" href="source/net/ipv4/devinet.c#L2194">2194</a>                 <a href="ident?i=t">t</a>-&gt;devinet_vars[<a href="ident?i=i">i</a>].<a href="ident?i=data">data</a> += (char *)<a href="ident?i=p">p</a> - (char *)&amp;<a href="ident?i=ipv4_devconf">ipv4_devconf</a>;
<a name="L2195" href="source/net/ipv4/devinet.c#L2195">2195</a>                 <a href="ident?i=t">t</a>-&gt;devinet_vars[<a href="ident?i=i">i</a>].extra1 = <a href="ident?i=p">p</a>;
<a name="L2196" href="source/net/ipv4/devinet.c#L2196">2196</a>                 <a href="ident?i=t">t</a>-&gt;devinet_vars[<a href="ident?i=i">i</a>].extra2 = <a href="ident?i=net">net</a>;
<a name="L2197" href="source/net/ipv4/devinet.c#L2197">2197</a>         }
<a name="L2198" href="source/net/ipv4/devinet.c#L2198">2198</a> 
<a name="L2199" href="source/net/ipv4/devinet.c#L2199">2199</a>         <a href="ident?i=snprintf">snprintf</a>(<a href="ident?i=path">path</a>, sizeof(<a href="ident?i=path">path</a>), <i>"net/ipv4/conf/%s"</i>, <a href="ident?i=dev_name">dev_name</a>);
<a name="L2200" href="source/net/ipv4/devinet.c#L2200">2200</a> 
<a name="L2201" href="source/net/ipv4/devinet.c#L2201">2201</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=sysctl_header">sysctl_header</a> = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(<a href="ident?i=net">net</a>, <a href="ident?i=path">path</a>, <a href="ident?i=t">t</a>-&gt;devinet_vars);
<a name="L2202" href="source/net/ipv4/devinet.c#L2202">2202</a>         if (!<a href="ident?i=t">t</a>-&gt;<a href="ident?i=sysctl_header">sysctl_header</a>)
<a name="L2203" href="source/net/ipv4/devinet.c#L2203">2203</a>                 goto <a href="ident?i=free">free</a>;
<a name="L2204" href="source/net/ipv4/devinet.c#L2204">2204</a> 
<a name="L2205" href="source/net/ipv4/devinet.c#L2205">2205</a>         <a href="ident?i=p">p</a>-&gt;sysctl = <a href="ident?i=t">t</a>;
<a name="L2206" href="source/net/ipv4/devinet.c#L2206">2206</a>         return 0;
<a name="L2207" href="source/net/ipv4/devinet.c#L2207">2207</a> 
<a name="L2208" href="source/net/ipv4/devinet.c#L2208">2208</a> <a href="ident?i=free">free</a>:
<a name="L2209" href="source/net/ipv4/devinet.c#L2209">2209</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=t">t</a>);
<a name="L2210" href="source/net/ipv4/devinet.c#L2210">2210</a> <a href="ident?i=out">out</a>:
<a name="L2211" href="source/net/ipv4/devinet.c#L2211">2211</a>         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2212" href="source/net/ipv4/devinet.c#L2212">2212</a> }
<a name="L2213" href="source/net/ipv4/devinet.c#L2213">2213</a> 
<a name="L2214" href="source/net/ipv4/devinet.c#L2214">2214</a> static void <a href="ident?i=__devinet_sysctl_unregister">__devinet_sysctl_unregister</a>(struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *cnf)
<a name="L2215" href="source/net/ipv4/devinet.c#L2215">2215</a> {
<a name="L2216" href="source/net/ipv4/devinet.c#L2216">2216</a>         struct <a href="ident?i=devinet_sysctl_table">devinet_sysctl_table</a> *<a href="ident?i=t">t</a> = cnf-&gt;sysctl;
<a name="L2217" href="source/net/ipv4/devinet.c#L2217">2217</a> 
<a name="L2218" href="source/net/ipv4/devinet.c#L2218">2218</a>         if (!<a href="ident?i=t">t</a>)
<a name="L2219" href="source/net/ipv4/devinet.c#L2219">2219</a>                 return;
<a name="L2220" href="source/net/ipv4/devinet.c#L2220">2220</a> 
<a name="L2221" href="source/net/ipv4/devinet.c#L2221">2221</a>         cnf-&gt;sysctl = <a href="ident?i=NULL">NULL</a>;
<a name="L2222" href="source/net/ipv4/devinet.c#L2222">2222</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=sysctl_header">sysctl_header</a>);
<a name="L2223" href="source/net/ipv4/devinet.c#L2223">2223</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=t">t</a>);
<a name="L2224" href="source/net/ipv4/devinet.c#L2224">2224</a> }
<a name="L2225" href="source/net/ipv4/devinet.c#L2225">2225</a> 
<a name="L2226" href="source/net/ipv4/devinet.c#L2226">2226</a> static int <a href="ident?i=devinet_sysctl_register">devinet_sysctl_register</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>)
<a name="L2227" href="source/net/ipv4/devinet.c#L2227">2227</a> {
<a name="L2228" href="source/net/ipv4/devinet.c#L2228">2228</a>         int <a href="ident?i=err">err</a>;
<a name="L2229" href="source/net/ipv4/devinet.c#L2229">2229</a> 
<a name="L2230" href="source/net/ipv4/devinet.c#L2230">2230</a>         if (!<a href="ident?i=sysctl_dev_name_is_allowed">sysctl_dev_name_is_allowed</a>(<a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>))
<a name="L2231" href="source/net/ipv4/devinet.c#L2231">2231</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2232" href="source/net/ipv4/devinet.c#L2232">2232</a> 
<a name="L2233" href="source/net/ipv4/devinet.c#L2233">2233</a>         <a href="ident?i=err">err</a> = <a href="ident?i=neigh_sysctl_register">neigh_sysctl_register</a>(<a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=idev">idev</a>-&gt;arp_parms, <a href="ident?i=NULL">NULL</a>);
<a name="L2234" href="source/net/ipv4/devinet.c#L2234">2234</a>         if (<a href="ident?i=err">err</a>)
<a name="L2235" href="source/net/ipv4/devinet.c#L2235">2235</a>                 return <a href="ident?i=err">err</a>;
<a name="L2236" href="source/net/ipv4/devinet.c#L2236">2236</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__devinet_sysctl_register">__devinet_sysctl_register</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=idev">idev</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L2237" href="source/net/ipv4/devinet.c#L2237">2237</a>                                         &amp;<a href="ident?i=idev">idev</a>-&gt;cnf);
<a name="L2238" href="source/net/ipv4/devinet.c#L2238">2238</a>         if (<a href="ident?i=err">err</a>)
<a name="L2239" href="source/net/ipv4/devinet.c#L2239">2239</a>                 <a href="ident?i=neigh_sysctl_unregister">neigh_sysctl_unregister</a>(<a href="ident?i=idev">idev</a>-&gt;arp_parms);
<a name="L2240" href="source/net/ipv4/devinet.c#L2240">2240</a>         return <a href="ident?i=err">err</a>;
<a name="L2241" href="source/net/ipv4/devinet.c#L2241">2241</a> }
<a name="L2242" href="source/net/ipv4/devinet.c#L2242">2242</a> 
<a name="L2243" href="source/net/ipv4/devinet.c#L2243">2243</a> static void <a href="ident?i=devinet_sysctl_unregister">devinet_sysctl_unregister</a>(struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>)
<a name="L2244" href="source/net/ipv4/devinet.c#L2244">2244</a> {
<a name="L2245" href="source/net/ipv4/devinet.c#L2245">2245</a>         <a href="ident?i=__devinet_sysctl_unregister">__devinet_sysctl_unregister</a>(&amp;<a href="ident?i=idev">idev</a>-&gt;cnf);
<a name="L2246" href="source/net/ipv4/devinet.c#L2246">2246</a>         <a href="ident?i=neigh_sysctl_unregister">neigh_sysctl_unregister</a>(<a href="ident?i=idev">idev</a>-&gt;arp_parms);
<a name="L2247" href="source/net/ipv4/devinet.c#L2247">2247</a> }
<a name="L2248" href="source/net/ipv4/devinet.c#L2248">2248</a> 
<a name="L2249" href="source/net/ipv4/devinet.c#L2249">2249</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ctl_forward_entry">ctl_forward_entry</a>[] = {
<a name="L2250" href="source/net/ipv4/devinet.c#L2250">2250</a>         {
<a name="L2251" href="source/net/ipv4/devinet.c#L2251">2251</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_forward"</i>,
<a name="L2252" href="source/net/ipv4/devinet.c#L2252">2252</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=ipv4_devconf">ipv4_devconf</a>.<a href="ident?i=data">data</a>[
<a name="L2253" href="source/net/ipv4/devinet.c#L2253">2253</a>                                         IPV4_DEVCONF_FORWARDING - 1],
<a name="L2254" href="source/net/ipv4/devinet.c#L2254">2254</a>                 .maxlen         = sizeof(int),
<a name="L2255" href="source/net/ipv4/devinet.c#L2255">2255</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2256" href="source/net/ipv4/devinet.c#L2256">2256</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=devinet_sysctl_forward">devinet_sysctl_forward</a>,
<a name="L2257" href="source/net/ipv4/devinet.c#L2257">2257</a>                 .extra1         = &amp;<a href="ident?i=ipv4_devconf">ipv4_devconf</a>,
<a name="L2258" href="source/net/ipv4/devinet.c#L2258">2258</a>                 .extra2         = &amp;<a href="ident?i=init_net">init_net</a>,
<a name="L2259" href="source/net/ipv4/devinet.c#L2259">2259</a>         },
<a name="L2260" href="source/net/ipv4/devinet.c#L2260">2260</a>         { },
<a name="L2261" href="source/net/ipv4/devinet.c#L2261">2261</a> };
<a name="L2262" href="source/net/ipv4/devinet.c#L2262">2262</a> #endif
<a name="L2263" href="source/net/ipv4/devinet.c#L2263">2263</a> 
<a name="L2264" href="source/net/ipv4/devinet.c#L2264">2264</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=devinet_init_net">devinet_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2265" href="source/net/ipv4/devinet.c#L2265">2265</a> {
<a name="L2266" href="source/net/ipv4/devinet.c#L2266">2266</a>         int <a href="ident?i=err">err</a>;
<a name="L2267" href="source/net/ipv4/devinet.c#L2267">2267</a>         struct <a href="ident?i=ipv4_devconf">ipv4_devconf</a> *<a href="ident?i=all">all</a>, *<a href="ident?i=dflt">dflt</a>;
<a name="L2268" href="source/net/ipv4/devinet.c#L2268">2268</a> #ifdef CONFIG_SYSCTL
<a name="L2269" href="source/net/ipv4/devinet.c#L2269">2269</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *tbl = <a href="ident?i=ctl_forward_entry">ctl_forward_entry</a>;
<a name="L2270" href="source/net/ipv4/devinet.c#L2270">2270</a>         struct <a href="ident?i=ctl_table_header">ctl_table_header</a> *forw_hdr;
<a name="L2271" href="source/net/ipv4/devinet.c#L2271">2271</a> #endif
<a name="L2272" href="source/net/ipv4/devinet.c#L2272">2272</a> 
<a name="L2273" href="source/net/ipv4/devinet.c#L2273">2273</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2274" href="source/net/ipv4/devinet.c#L2274">2274</a>         <a href="ident?i=all">all</a> = &amp;<a href="ident?i=ipv4_devconf">ipv4_devconf</a>;
<a name="L2275" href="source/net/ipv4/devinet.c#L2275">2275</a>         <a href="ident?i=dflt">dflt</a> = &amp;<a href="ident?i=ipv4_devconf_dflt">ipv4_devconf_dflt</a>;
<a name="L2276" href="source/net/ipv4/devinet.c#L2276">2276</a> 
<a name="L2277" href="source/net/ipv4/devinet.c#L2277">2277</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>)) {
<a name="L2278" href="source/net/ipv4/devinet.c#L2278">2278</a>                 <a href="ident?i=all">all</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=all">all</a>, sizeof(<a href="ident?i=ipv4_devconf">ipv4_devconf</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2279" href="source/net/ipv4/devinet.c#L2279">2279</a>                 if (!<a href="ident?i=all">all</a>)
<a name="L2280" href="source/net/ipv4/devinet.c#L2280">2280</a>                         goto err_alloc_all;
<a name="L2281" href="source/net/ipv4/devinet.c#L2281">2281</a> 
<a name="L2282" href="source/net/ipv4/devinet.c#L2282">2282</a>                 <a href="ident?i=dflt">dflt</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=dflt">dflt</a>, sizeof(<a href="ident?i=ipv4_devconf_dflt">ipv4_devconf_dflt</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2283" href="source/net/ipv4/devinet.c#L2283">2283</a>                 if (!<a href="ident?i=dflt">dflt</a>)
<a name="L2284" href="source/net/ipv4/devinet.c#L2284">2284</a>                         goto err_alloc_dflt;
<a name="L2285" href="source/net/ipv4/devinet.c#L2285">2285</a> 
<a name="L2286" href="source/net/ipv4/devinet.c#L2286">2286</a> #ifdef CONFIG_SYSCTL
<a name="L2287" href="source/net/ipv4/devinet.c#L2287">2287</a>                 tbl = <a href="ident?i=kmemdup">kmemdup</a>(tbl, sizeof(<a href="ident?i=ctl_forward_entry">ctl_forward_entry</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2288" href="source/net/ipv4/devinet.c#L2288">2288</a>                 if (!tbl)
<a name="L2289" href="source/net/ipv4/devinet.c#L2289">2289</a>                         goto err_alloc_ctl;
<a name="L2290" href="source/net/ipv4/devinet.c#L2290">2290</a> 
<a name="L2291" href="source/net/ipv4/devinet.c#L2291">2291</a>                 tbl[0].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=all">all</a>-&gt;<a href="ident?i=data">data</a>[IPV4_DEVCONF_FORWARDING - 1];
<a name="L2292" href="source/net/ipv4/devinet.c#L2292">2292</a>                 tbl[0].extra1 = <a href="ident?i=all">all</a>;
<a name="L2293" href="source/net/ipv4/devinet.c#L2293">2293</a>                 tbl[0].extra2 = <a href="ident?i=net">net</a>;
<a name="L2294" href="source/net/ipv4/devinet.c#L2294">2294</a> #endif
<a name="L2295" href="source/net/ipv4/devinet.c#L2295">2295</a>         }
<a name="L2296" href="source/net/ipv4/devinet.c#L2296">2296</a> 
<a name="L2297" href="source/net/ipv4/devinet.c#L2297">2297</a> #ifdef CONFIG_SYSCTL
<a name="L2298" href="source/net/ipv4/devinet.c#L2298">2298</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__devinet_sysctl_register">__devinet_sysctl_register</a>(<a href="ident?i=net">net</a>, <i>"all"</i>, <a href="ident?i=all">all</a>);
<a name="L2299" href="source/net/ipv4/devinet.c#L2299">2299</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2300" href="source/net/ipv4/devinet.c#L2300">2300</a>                 goto err_reg_all;
<a name="L2301" href="source/net/ipv4/devinet.c#L2301">2301</a> 
<a name="L2302" href="source/net/ipv4/devinet.c#L2302">2302</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__devinet_sysctl_register">__devinet_sysctl_register</a>(<a href="ident?i=net">net</a>, <i>"default"</i>, <a href="ident?i=dflt">dflt</a>);
<a name="L2303" href="source/net/ipv4/devinet.c#L2303">2303</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2304" href="source/net/ipv4/devinet.c#L2304">2304</a>                 goto err_reg_dflt;
<a name="L2305" href="source/net/ipv4/devinet.c#L2305">2305</a> 
<a name="L2306" href="source/net/ipv4/devinet.c#L2306">2306</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2307" href="source/net/ipv4/devinet.c#L2307">2307</a>         forw_hdr = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(<a href="ident?i=net">net</a>, <i>"net/ipv4"</i>, tbl);
<a name="L2308" href="source/net/ipv4/devinet.c#L2308">2308</a>         if (!forw_hdr)
<a name="L2309" href="source/net/ipv4/devinet.c#L2309">2309</a>                 goto err_reg_ctl;
<a name="L2310" href="source/net/ipv4/devinet.c#L2310">2310</a>         <a href="ident?i=net">net</a>-&gt;ipv4.forw_hdr = forw_hdr;
<a name="L2311" href="source/net/ipv4/devinet.c#L2311">2311</a> #endif
<a name="L2312" href="source/net/ipv4/devinet.c#L2312">2312</a> 
<a name="L2313" href="source/net/ipv4/devinet.c#L2313">2313</a>         <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all = <a href="ident?i=all">all</a>;
<a name="L2314" href="source/net/ipv4/devinet.c#L2314">2314</a>         <a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt = <a href="ident?i=dflt">dflt</a>;
<a name="L2315" href="source/net/ipv4/devinet.c#L2315">2315</a>         return 0;
<a name="L2316" href="source/net/ipv4/devinet.c#L2316">2316</a> 
<a name="L2317" href="source/net/ipv4/devinet.c#L2317">2317</a> #ifdef CONFIG_SYSCTL
<a name="L2318" href="source/net/ipv4/devinet.c#L2318">2318</a> err_reg_ctl:
<a name="L2319" href="source/net/ipv4/devinet.c#L2319">2319</a>         <a href="ident?i=__devinet_sysctl_unregister">__devinet_sysctl_unregister</a>(<a href="ident?i=dflt">dflt</a>);
<a name="L2320" href="source/net/ipv4/devinet.c#L2320">2320</a> err_reg_dflt:
<a name="L2321" href="source/net/ipv4/devinet.c#L2321">2321</a>         <a href="ident?i=__devinet_sysctl_unregister">__devinet_sysctl_unregister</a>(<a href="ident?i=all">all</a>);
<a name="L2322" href="source/net/ipv4/devinet.c#L2322">2322</a> err_reg_all:
<a name="L2323" href="source/net/ipv4/devinet.c#L2323">2323</a>         if (tbl != <a href="ident?i=ctl_forward_entry">ctl_forward_entry</a>)
<a name="L2324" href="source/net/ipv4/devinet.c#L2324">2324</a>                 <a href="ident?i=kfree">kfree</a>(tbl);
<a name="L2325" href="source/net/ipv4/devinet.c#L2325">2325</a> err_alloc_ctl:
<a name="L2326" href="source/net/ipv4/devinet.c#L2326">2326</a> #endif
<a name="L2327" href="source/net/ipv4/devinet.c#L2327">2327</a>         if (<a href="ident?i=dflt">dflt</a> != &amp;<a href="ident?i=ipv4_devconf_dflt">ipv4_devconf_dflt</a>)
<a name="L2328" href="source/net/ipv4/devinet.c#L2328">2328</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=dflt">dflt</a>);
<a name="L2329" href="source/net/ipv4/devinet.c#L2329">2329</a> err_alloc_dflt:
<a name="L2330" href="source/net/ipv4/devinet.c#L2330">2330</a>         if (<a href="ident?i=all">all</a> != &amp;<a href="ident?i=ipv4_devconf">ipv4_devconf</a>)
<a name="L2331" href="source/net/ipv4/devinet.c#L2331">2331</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=all">all</a>);
<a name="L2332" href="source/net/ipv4/devinet.c#L2332">2332</a> err_alloc_all:
<a name="L2333" href="source/net/ipv4/devinet.c#L2333">2333</a>         return <a href="ident?i=err">err</a>;
<a name="L2334" href="source/net/ipv4/devinet.c#L2334">2334</a> }
<a name="L2335" href="source/net/ipv4/devinet.c#L2335">2335</a> 
<a name="L2336" href="source/net/ipv4/devinet.c#L2336">2336</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=devinet_exit_net">devinet_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2337" href="source/net/ipv4/devinet.c#L2337">2337</a> {
<a name="L2338" href="source/net/ipv4/devinet.c#L2338">2338</a> #ifdef CONFIG_SYSCTL
<a name="L2339" href="source/net/ipv4/devinet.c#L2339">2339</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *tbl;
<a name="L2340" href="source/net/ipv4/devinet.c#L2340">2340</a> 
<a name="L2341" href="source/net/ipv4/devinet.c#L2341">2341</a>         tbl = <a href="ident?i=net">net</a>-&gt;ipv4.forw_hdr-&gt;ctl_table_arg;
<a name="L2342" href="source/net/ipv4/devinet.c#L2342">2342</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.forw_hdr);
<a name="L2343" href="source/net/ipv4/devinet.c#L2343">2343</a>         <a href="ident?i=__devinet_sysctl_unregister">__devinet_sysctl_unregister</a>(<a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt);
<a name="L2344" href="source/net/ipv4/devinet.c#L2344">2344</a>         <a href="ident?i=__devinet_sysctl_unregister">__devinet_sysctl_unregister</a>(<a href="ident?i=net">net</a>-&gt;ipv4.devconf_all);
<a name="L2345" href="source/net/ipv4/devinet.c#L2345">2345</a>         <a href="ident?i=kfree">kfree</a>(tbl);
<a name="L2346" href="source/net/ipv4/devinet.c#L2346">2346</a> #endif
<a name="L2347" href="source/net/ipv4/devinet.c#L2347">2347</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;ipv4.devconf_dflt);
<a name="L2348" href="source/net/ipv4/devinet.c#L2348">2348</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;ipv4.devconf_all);
<a name="L2349" href="source/net/ipv4/devinet.c#L2349">2349</a> }
<a name="L2350" href="source/net/ipv4/devinet.c#L2350">2350</a> 
<a name="L2351" href="source/net/ipv4/devinet.c#L2351">2351</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=devinet_ops">devinet_ops</a> = {
<a name="L2352" href="source/net/ipv4/devinet.c#L2352">2352</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=devinet_init_net">devinet_init_net</a>,
<a name="L2353" href="source/net/ipv4/devinet.c#L2353">2353</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=devinet_exit_net">devinet_exit_net</a>,
<a name="L2354" href="source/net/ipv4/devinet.c#L2354">2354</a> };
<a name="L2355" href="source/net/ipv4/devinet.c#L2355">2355</a> 
<a name="L2356" href="source/net/ipv4/devinet.c#L2356">2356</a> static struct <a href="ident?i=rtnl_af_ops">rtnl_af_ops</a> inet_af_ops <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L2357" href="source/net/ipv4/devinet.c#L2357">2357</a>         .<a href="ident?i=family">family</a>           = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L2358" href="source/net/ipv4/devinet.c#L2358">2358</a>         .fill_link_af     = <a href="ident?i=inet_fill_link_af">inet_fill_link_af</a>,
<a name="L2359" href="source/net/ipv4/devinet.c#L2359">2359</a>         .get_link_af_size = <a href="ident?i=inet_get_link_af_size">inet_get_link_af_size</a>,
<a name="L2360" href="source/net/ipv4/devinet.c#L2360">2360</a>         .validate_link_af = <a href="ident?i=inet_validate_link_af">inet_validate_link_af</a>,
<a name="L2361" href="source/net/ipv4/devinet.c#L2361">2361</a>         .set_link_af      = <a href="ident?i=inet_set_link_af">inet_set_link_af</a>,
<a name="L2362" href="source/net/ipv4/devinet.c#L2362">2362</a> };
<a name="L2363" href="source/net/ipv4/devinet.c#L2363">2363</a> 
<a name="L2364" href="source/net/ipv4/devinet.c#L2364">2364</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=devinet_init">devinet_init</a>(void)
<a name="L2365" href="source/net/ipv4/devinet.c#L2365">2365</a> {
<a name="L2366" href="source/net/ipv4/devinet.c#L2366">2366</a>         int <a href="ident?i=i">i</a>;
<a name="L2367" href="source/net/ipv4/devinet.c#L2367">2367</a> 
<a name="L2368" href="source/net/ipv4/devinet.c#L2368">2368</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=IN4_ADDR_HSIZE">IN4_ADDR_HSIZE</a>; <a href="ident?i=i">i</a>++)
<a name="L2369" href="source/net/ipv4/devinet.c#L2369">2369</a>                 <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;<a href="ident?i=inet_addr_lst">inet_addr_lst</a>[<a href="ident?i=i">i</a>]);
<a name="L2370" href="source/net/ipv4/devinet.c#L2370">2370</a> 
<a name="L2371" href="source/net/ipv4/devinet.c#L2371">2371</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=devinet_ops">devinet_ops</a>);
<a name="L2372" href="source/net/ipv4/devinet.c#L2372">2372</a> 
<a name="L2373" href="source/net/ipv4/devinet.c#L2373">2373</a>         <a href="ident?i=register_gifconf">register_gifconf</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=inet_gifconf">inet_gifconf</a>);
<a name="L2374" href="source/net/ipv4/devinet.c#L2374">2374</a>         <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=ip_netdev_notifier">ip_netdev_notifier</a>);
<a name="L2375" href="source/net/ipv4/devinet.c#L2375">2375</a> 
<a name="L2376" href="source/net/ipv4/devinet.c#L2376">2376</a>         <a href="ident?i=queue_delayed_work">queue_delayed_work</a>(<a href="ident?i=system_power_efficient_wq">system_power_efficient_wq</a>, &amp;check_lifetime_work, 0);
<a name="L2377" href="source/net/ipv4/devinet.c#L2377">2377</a> 
<a name="L2378" href="source/net/ipv4/devinet.c#L2378">2378</a>         <a href="ident?i=rtnl_af_register">rtnl_af_register</a>(&amp;inet_af_ops);
<a name="L2379" href="source/net/ipv4/devinet.c#L2379">2379</a> 
<a name="L2380" href="source/net/ipv4/devinet.c#L2380">2380</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_NEWADDR">RTM_NEWADDR</a>, <a href="ident?i=inet_rtm_newaddr">inet_rtm_newaddr</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2381" href="source/net/ipv4/devinet.c#L2381">2381</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_DELADDR">RTM_DELADDR</a>, <a href="ident?i=inet_rtm_deladdr">inet_rtm_deladdr</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2382" href="source/net/ipv4/devinet.c#L2382">2382</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_GETADDR">RTM_GETADDR</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=inet_dump_ifaddr">inet_dump_ifaddr</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2383" href="source/net/ipv4/devinet.c#L2383">2383</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_GETNETCONF">RTM_GETNETCONF</a>, <a href="ident?i=inet_netconf_get_devconf">inet_netconf_get_devconf</a>,
<a name="L2384" href="source/net/ipv4/devinet.c#L2384">2384</a>                       <a href="ident?i=inet_netconf_dump_devconf">inet_netconf_dump_devconf</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2385" href="source/net/ipv4/devinet.c#L2385">2385</a> }
<a name="L2386" href="source/net/ipv4/devinet.c#L2386">2386</a> 
<a name="L2387" href="source/net/ipv4/devinet.c#L2387">2387</a> </pre></div><p>
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
