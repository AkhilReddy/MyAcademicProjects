<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ipconfig.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ipconfig.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ipconfig.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ipconfig.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ipconfig.c">ipconfig.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ipconfig.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ipconfig.c#L2">2</a> <b><i> *  Automatic Configuration of IP -- use DHCP, BOOTP, RARP, or</i></b>
  <a name="L3" href="source/net/ipv4/ipconfig.c#L3">3</a> <b><i> *  user-supplied information to configure own IP address and routes.</i></b>
  <a name="L4" href="source/net/ipv4/ipconfig.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/ipconfig.c#L5">5</a> <b><i> *  Copyright (C) 1996-1998 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;</i></b>
  <a name="L6" href="source/net/ipv4/ipconfig.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/ipconfig.c#L7">7</a> <b><i> *  Derived from network configuration code in fs/nfs/nfsroot.c,</i></b>
  <a name="L8" href="source/net/ipv4/ipconfig.c#L8">8</a> <b><i> *  originally Copyright (C) 1995, 1996 Gero Kuhlmann and me.</i></b>
  <a name="L9" href="source/net/ipv4/ipconfig.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/ipconfig.c#L10">10</a> <b><i> *  BOOTP rewritten to construct and analyse packets itself instead</i></b>
 <a name="L11" href="source/net/ipv4/ipconfig.c#L11">11</a> <b><i> *  of misusing the IP layer. num_bugs_causing_wrong_arp_replies--;</i></b>
 <a name="L12" href="source/net/ipv4/ipconfig.c#L12">12</a> <b><i> *                                           -- MJ, December 1998</i></b>
 <a name="L13" href="source/net/ipv4/ipconfig.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/ipconfig.c#L14">14</a> <b><i> *  Fixed ip_auto_config_setup calling at startup in the new "Linker Magic"</i></b>
 <a name="L15" href="source/net/ipv4/ipconfig.c#L15">15</a> <b><i> *  initialization scheme.</i></b>
 <a name="L16" href="source/net/ipv4/ipconfig.c#L16">16</a> <b><i> *      - Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;, 08/11/1999</i></b>
 <a name="L17" href="source/net/ipv4/ipconfig.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/ipconfig.c#L18">18</a> <b><i> *  DHCP support added.  To users this looks like a whole separate</i></b>
 <a name="L19" href="source/net/ipv4/ipconfig.c#L19">19</a> <b><i> *  protocol, but we know it's just a bag on the side of BOOTP.</i></b>
 <a name="L20" href="source/net/ipv4/ipconfig.c#L20">20</a> <b><i> *              -- Chip Salzenberg &lt;chip@valinux.com&gt;, May 2000</i></b>
 <a name="L21" href="source/net/ipv4/ipconfig.c#L21">21</a> <b><i> *</i></b>
 <a name="L22" href="source/net/ipv4/ipconfig.c#L22">22</a> <b><i> *  Ported DHCP support from 2.2.16 to 2.4.0-test4</i></b>
 <a name="L23" href="source/net/ipv4/ipconfig.c#L23">23</a> <b><i> *              -- Eric Biederman &lt;ebiederman@lnxi.com&gt;, 30 Aug 2000</i></b>
 <a name="L24" href="source/net/ipv4/ipconfig.c#L24">24</a> <b><i> *</i></b>
 <a name="L25" href="source/net/ipv4/ipconfig.c#L25">25</a> <b><i> *  Merged changes from 2.2.19 into 2.4.3</i></b>
 <a name="L26" href="source/net/ipv4/ipconfig.c#L26">26</a> <b><i> *              -- Eric Biederman &lt;ebiederman@lnxi.com&gt;, 22 April Aug 2001</i></b>
 <a name="L27" href="source/net/ipv4/ipconfig.c#L27">27</a> <b><i> *</i></b>
 <a name="L28" href="source/net/ipv4/ipconfig.c#L28">28</a> <b><i> *  Multiple Nameservers in /proc/net/pnp</i></b>
 <a name="L29" href="source/net/ipv4/ipconfig.c#L29">29</a> <b><i> *              --  Josef Siemes &lt;jsiemes@web.de&gt;, Aug 2002</i></b>
 <a name="L30" href="source/net/ipv4/ipconfig.c#L30">30</a> <b><i> */</i></b>
 <a name="L31" href="source/net/ipv4/ipconfig.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/ipconfig.c#L32">32</a> #include &lt;linux/types.h&gt;
 <a name="L33" href="source/net/ipv4/ipconfig.c#L33">33</a> #include &lt;linux/string.h&gt;
 <a name="L34" href="source/net/ipv4/ipconfig.c#L34">34</a> #include &lt;linux/kernel.h&gt;
 <a name="L35" href="source/net/ipv4/ipconfig.c#L35">35</a> #include &lt;linux/jiffies.h&gt;
 <a name="L36" href="source/net/ipv4/ipconfig.c#L36">36</a> #include &lt;linux/random.h&gt;
 <a name="L37" href="source/net/ipv4/ipconfig.c#L37">37</a> #include &lt;linux/init.h&gt;
 <a name="L38" href="source/net/ipv4/ipconfig.c#L38">38</a> #include &lt;linux/utsname.h&gt;
 <a name="L39" href="source/net/ipv4/ipconfig.c#L39">39</a> #include &lt;linux/in.h&gt;
 <a name="L40" href="source/net/ipv4/ipconfig.c#L40">40</a> #include &lt;linux/if.h&gt;
 <a name="L41" href="source/net/ipv4/ipconfig.c#L41">41</a> #include &lt;linux/inet.h&gt;
 <a name="L42" href="source/net/ipv4/ipconfig.c#L42">42</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L43" href="source/net/ipv4/ipconfig.c#L43">43</a> #include &lt;linux/netdevice.h&gt;
 <a name="L44" href="source/net/ipv4/ipconfig.c#L44">44</a> #include &lt;linux/if_arp.h&gt;
 <a name="L45" href="source/net/ipv4/ipconfig.c#L45">45</a> #include &lt;linux/skbuff.h&gt;
 <a name="L46" href="source/net/ipv4/ipconfig.c#L46">46</a> #include &lt;linux/ip.h&gt;
 <a name="L47" href="source/net/ipv4/ipconfig.c#L47">47</a> #include &lt;linux/socket.h&gt;
 <a name="L48" href="source/net/ipv4/ipconfig.c#L48">48</a> #include &lt;linux/route.h&gt;
 <a name="L49" href="source/net/ipv4/ipconfig.c#L49">49</a> #include &lt;linux/udp.h&gt;
 <a name="L50" href="source/net/ipv4/ipconfig.c#L50">50</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L51" href="source/net/ipv4/ipconfig.c#L51">51</a> #include &lt;linux/seq_file.h&gt;
 <a name="L52" href="source/net/ipv4/ipconfig.c#L52">52</a> #include &lt;linux/major.h&gt;
 <a name="L53" href="source/net/ipv4/ipconfig.c#L53">53</a> #include &lt;linux/root_dev.h&gt;
 <a name="L54" href="source/net/ipv4/ipconfig.c#L54">54</a> #include &lt;linux/delay.h&gt;
 <a name="L55" href="source/net/ipv4/ipconfig.c#L55">55</a> #include &lt;linux/nfs_fs.h&gt;
 <a name="L56" href="source/net/ipv4/ipconfig.c#L56">56</a> #include &lt;linux/slab.h&gt;
 <a name="L57" href="source/net/ipv4/ipconfig.c#L57">57</a> #include &lt;linux/export.h&gt;
 <a name="L58" href="source/net/ipv4/ipconfig.c#L58">58</a> #include &lt;net/net_namespace.h&gt;
 <a name="L59" href="source/net/ipv4/ipconfig.c#L59">59</a> #include &lt;net/arp.h&gt;
 <a name="L60" href="source/net/ipv4/ipconfig.c#L60">60</a> #include &lt;net/ip.h&gt;
 <a name="L61" href="source/net/ipv4/ipconfig.c#L61">61</a> #include &lt;net/ipconfig.h&gt;
 <a name="L62" href="source/net/ipv4/ipconfig.c#L62">62</a> #include &lt;net/route.h&gt;
 <a name="L63" href="source/net/ipv4/ipconfig.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/ipconfig.c#L64">64</a> #include &lt;asm/uaccess.h&gt;
 <a name="L65" href="source/net/ipv4/ipconfig.c#L65">65</a> #include &lt;net/checksum.h&gt;
 <a name="L66" href="source/net/ipv4/ipconfig.c#L66">66</a> #include &lt;asm/processor.h&gt;
 <a name="L67" href="source/net/ipv4/ipconfig.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/ipconfig.c#L68">68</a> <b><i>/* Define this to allow debugging output */</i></b>
 <a name="L69" href="source/net/ipv4/ipconfig.c#L69">69</a> #undef <a href="ident?i=IPCONFIG_DEBUG">IPCONFIG_DEBUG</a>
 <a name="L70" href="source/net/ipv4/ipconfig.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/ipconfig.c#L71">71</a> #ifdef <a href="ident?i=IPCONFIG_DEBUG">IPCONFIG_DEBUG</a>
 <a name="L72" href="source/net/ipv4/ipconfig.c#L72">72</a> #define <a href="ident?i=DBG">DBG</a>(<a href="ident?i=x">x</a>) <a href="ident?i=printk">printk</a> <a href="ident?i=x">x</a>
 <a name="L73" href="source/net/ipv4/ipconfig.c#L73">73</a> #else
 <a name="L74" href="source/net/ipv4/ipconfig.c#L74">74</a> #define <a href="ident?i=DBG">DBG</a>(<a href="ident?i=x">x</a>) do { } while(0)
 <a name="L75" href="source/net/ipv4/ipconfig.c#L75">75</a> #endif
 <a name="L76" href="source/net/ipv4/ipconfig.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/ipconfig.c#L77">77</a> #if defined(CONFIG_IP_PNP_DHCP)
 <a name="L78" href="source/net/ipv4/ipconfig.c#L78">78</a> #define <a href="ident?i=IPCONFIG_DHCP">IPCONFIG_DHCP</a>
 <a name="L79" href="source/net/ipv4/ipconfig.c#L79">79</a> #endif
 <a name="L80" href="source/net/ipv4/ipconfig.c#L80">80</a> #if defined(CONFIG_IP_PNP_BOOTP) || defined(CONFIG_IP_PNP_DHCP)
 <a name="L81" href="source/net/ipv4/ipconfig.c#L81">81</a> #define <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
 <a name="L82" href="source/net/ipv4/ipconfig.c#L82">82</a> #endif
 <a name="L83" href="source/net/ipv4/ipconfig.c#L83">83</a> #if defined(CONFIG_IP_PNP_RARP)
 <a name="L84" href="source/net/ipv4/ipconfig.c#L84">84</a> #define <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
 <a name="L85" href="source/net/ipv4/ipconfig.c#L85">85</a> #endif
 <a name="L86" href="source/net/ipv4/ipconfig.c#L86">86</a> #if defined(<a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>) || defined(<a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>)
 <a name="L87" href="source/net/ipv4/ipconfig.c#L87">87</a> #define <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
 <a name="L88" href="source/net/ipv4/ipconfig.c#L88">88</a> #endif
 <a name="L89" href="source/net/ipv4/ipconfig.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/ipconfig.c#L90">90</a> <b><i>/* Define the friendly delay before and after opening net devices */</i></b>
 <a name="L91" href="source/net/ipv4/ipconfig.c#L91">91</a> #define <a href="ident?i=CONF_POST_OPEN">CONF_POST_OPEN</a>          10      <b><i>/* After opening: 10 msecs */</i></b>
 <a name="L92" href="source/net/ipv4/ipconfig.c#L92">92</a> #define <a href="ident?i=CONF_CARRIER_TIMEOUT">CONF_CARRIER_TIMEOUT</a>    120000  <b><i>/* Wait for carrier timeout */</i></b>
 <a name="L93" href="source/net/ipv4/ipconfig.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ipconfig.c#L94">94</a> <b><i>/* Define the timeout for waiting for a DHCP/BOOTP/RARP reply */</i></b>
 <a name="L95" href="source/net/ipv4/ipconfig.c#L95">95</a> #define <a href="ident?i=CONF_OPEN_RETRIES">CONF_OPEN_RETRIES</a>       2       <b><i>/* (Re)open devices twice */</i></b>
 <a name="L96" href="source/net/ipv4/ipconfig.c#L96">96</a> #define <a href="ident?i=CONF_SEND_RETRIES">CONF_SEND_RETRIES</a>       6       <b><i>/* Send six requests per open */</i></b>
 <a name="L97" href="source/net/ipv4/ipconfig.c#L97">97</a> #define <a href="ident?i=CONF_INTER_TIMEOUT">CONF_INTER_TIMEOUT</a>      (<a href="ident?i=HZ">HZ</a>/2)  <b><i>/* Inter-device timeout: 1/2 second */</i></b>
 <a name="L98" href="source/net/ipv4/ipconfig.c#L98">98</a> #define <a href="ident?i=CONF_BASE_TIMEOUT">CONF_BASE_TIMEOUT</a>       (<a href="ident?i=HZ">HZ</a>*2)  <b><i>/* Initial timeout: 2 seconds */</i></b>
 <a name="L99" href="source/net/ipv4/ipconfig.c#L99">99</a> #define <a href="ident?i=CONF_TIMEOUT_RANDOM">CONF_TIMEOUT_RANDOM</a>     (<a href="ident?i=HZ">HZ</a>)    <b><i>/* Maximum amount of randomization */</i></b>
<a name="L100" href="source/net/ipv4/ipconfig.c#L100">100</a> #define <a href="ident?i=CONF_TIMEOUT_MULT">CONF_TIMEOUT_MULT</a>       *7/4    <b><i>/* Rate of timeout growth */</i></b>
<a name="L101" href="source/net/ipv4/ipconfig.c#L101">101</a> #define <a href="ident?i=CONF_TIMEOUT_MAX">CONF_TIMEOUT_MAX</a>        (<a href="ident?i=HZ">HZ</a>*30) <b><i>/* Maximum allowed timeout */</i></b>
<a name="L102" href="source/net/ipv4/ipconfig.c#L102">102</a> #define <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>   3       <b><i>/* Maximum number of nameservers</i></b>
<a name="L103" href="source/net/ipv4/ipconfig.c#L103">103</a> <b><i>                                           - '3' from resolv.h */</i></b>
<a name="L104" href="source/net/ipv4/ipconfig.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/ipconfig.c#L105">105</a> #define <a href="ident?i=NONE">NONE</a> <a href="ident?i=cpu_to_be32">cpu_to_be32</a>(<a href="ident?i=INADDR_NONE">INADDR_NONE</a>)
<a name="L106" href="source/net/ipv4/ipconfig.c#L106">106</a> #define <a href="ident?i=ANY">ANY</a> <a href="ident?i=cpu_to_be32">cpu_to_be32</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>)
<a name="L107" href="source/net/ipv4/ipconfig.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/ipconfig.c#L108">108</a> <b><i>/*</i></b>
<a name="L109" href="source/net/ipv4/ipconfig.c#L109">109</a> <b><i> * Public IP configuration</i></b>
<a name="L110" href="source/net/ipv4/ipconfig.c#L110">110</a> <b><i> */</i></b>
<a name="L111" href="source/net/ipv4/ipconfig.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/ipconfig.c#L112">112</a> <b><i>/* This is used by platforms which might be able to set the ipconfig</i></b>
<a name="L113" href="source/net/ipv4/ipconfig.c#L113">113</a> <b><i> * variables using firmware environment vars.  If this is set, it will</i></b>
<a name="L114" href="source/net/ipv4/ipconfig.c#L114">114</a> <b><i> * ignore such firmware variables.</i></b>
<a name="L115" href="source/net/ipv4/ipconfig.c#L115">115</a> <b><i> */</i></b>
<a name="L116" href="source/net/ipv4/ipconfig.c#L116">116</a> int <a href="ident?i=ic_set_manually">ic_set_manually</a> <a href="ident?i=__initdata">__initdata</a> = 0;             <b><i>/* IPconfig parameters set manually */</i></b>
<a name="L117" href="source/net/ipv4/ipconfig.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/ipconfig.c#L118">118</a> static int ic_enable <a href="ident?i=__initdata">__initdata</a>;                <b><i>/* IP config enabled? */</i></b>
<a name="L119" href="source/net/ipv4/ipconfig.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/ipconfig.c#L120">120</a> <b><i>/* Protocol choice */</i></b>
<a name="L121" href="source/net/ipv4/ipconfig.c#L121">121</a> int <a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> <a href="ident?i=__initdata">__initdata</a> = 0
<a name="L122" href="source/net/ipv4/ipconfig.c#L122">122</a> #ifdef <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
<a name="L123" href="source/net/ipv4/ipconfig.c#L123">123</a>                         | <a href="ident?i=IC_BOOTP">IC_BOOTP</a>
<a name="L124" href="source/net/ipv4/ipconfig.c#L124">124</a> #endif
<a name="L125" href="source/net/ipv4/ipconfig.c#L125">125</a> #ifdef CONFIG_IP_PNP_DHCP
<a name="L126" href="source/net/ipv4/ipconfig.c#L126">126</a>                         | <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>
<a name="L127" href="source/net/ipv4/ipconfig.c#L127">127</a> #endif
<a name="L128" href="source/net/ipv4/ipconfig.c#L128">128</a> #ifdef <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
<a name="L129" href="source/net/ipv4/ipconfig.c#L129">129</a>                         | <a href="ident?i=IC_RARP">IC_RARP</a>
<a name="L130" href="source/net/ipv4/ipconfig.c#L130">130</a> #endif
<a name="L131" href="source/net/ipv4/ipconfig.c#L131">131</a>                         ;
<a name="L132" href="source/net/ipv4/ipconfig.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/ipconfig.c#L133">133</a> static int ic_host_name_set <a href="ident?i=__initdata">__initdata</a>; <b><i>/* Host name set by us? */</i></b>
<a name="L134" href="source/net/ipv4/ipconfig.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/ipconfig.c#L135">135</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=NONE">NONE</a>;                <b><i>/* My IP address */</i></b>
<a name="L136" href="source/net/ipv4/ipconfig.c#L136">136</a> static <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_netmask">ic_netmask</a> = <a href="ident?i=NONE">NONE</a>;        <b><i>/* Netmask for local subnet */</i></b>
<a name="L137" href="source/net/ipv4/ipconfig.c#L137">137</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_gateway">ic_gateway</a> = <a href="ident?i=NONE">NONE</a>;       <b><i>/* Gateway IP address */</i></b>
<a name="L138" href="source/net/ipv4/ipconfig.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/ipconfig.c#L139">139</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_addrservaddr">ic_addrservaddr</a> = <a href="ident?i=NONE">NONE</a>;  <b><i>/* IP Address of the IP addresses'server */</i></b>
<a name="L140" href="source/net/ipv4/ipconfig.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/ipconfig.c#L141">141</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_servaddr">ic_servaddr</a> = <a href="ident?i=NONE">NONE</a>;      <b><i>/* Boot server IP address */</i></b>
<a name="L142" href="source/net/ipv4/ipconfig.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/ipconfig.c#L143">143</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=root_server_addr">root_server_addr</a> = <a href="ident?i=NONE">NONE</a>; <b><i>/* Address of NFS server */</i></b>
<a name="L144" href="source/net/ipv4/ipconfig.c#L144">144</a> <a href="ident?i=u8">u8</a> <a href="ident?i=root_server_path">root_server_path</a>[256] = { 0, };      <b><i>/* Path to mount as root */</i></b>
<a name="L145" href="source/net/ipv4/ipconfig.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/ipconfig.c#L146">146</a> <b><i>/* vendor class identifier */</i></b>
<a name="L147" href="source/net/ipv4/ipconfig.c#L147">147</a> static char vendor_class_identifier[253] <a href="ident?i=__initdata">__initdata</a>;
<a name="L148" href="source/net/ipv4/ipconfig.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/ipconfig.c#L149">149</a> <b><i>/* Persistent data: */</i></b>
<a name="L150" href="source/net/ipv4/ipconfig.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/ipconfig.c#L151">151</a> static int <a href="ident?i=ic_proto_used">ic_proto_used</a>;                       <b><i>/* Protocol used, if any */</i></b>
<a name="L152" href="source/net/ipv4/ipconfig.c#L152">152</a> static <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>]; <b><i>/* DNS Server IP addresses */</i></b>
<a name="L153" href="source/net/ipv4/ipconfig.c#L153">153</a> static <a href="ident?i=u8">u8</a> <a href="ident?i=ic_domain">ic_domain</a>[64];                <b><i>/* DNS (not NIS) domain name */</i></b>
<a name="L154" href="source/net/ipv4/ipconfig.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/ipconfig.c#L155">155</a> <b><i>/*</i></b>
<a name="L156" href="source/net/ipv4/ipconfig.c#L156">156</a> <b><i> * Private state.</i></b>
<a name="L157" href="source/net/ipv4/ipconfig.c#L157">157</a> <b><i> */</i></b>
<a name="L158" href="source/net/ipv4/ipconfig.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/ipconfig.c#L159">159</a> <b><i>/* Name of user-selected boot device */</i></b>
<a name="L160" href="source/net/ipv4/ipconfig.c#L160">160</a> static char user_dev_name[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>] <a href="ident?i=__initdata">__initdata</a> = { 0, };
<a name="L161" href="source/net/ipv4/ipconfig.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/ipconfig.c#L162">162</a> <b><i>/* Protocols supported by available interfaces */</i></b>
<a name="L163" href="source/net/ipv4/ipconfig.c#L163">163</a> static int ic_proto_have_if <a href="ident?i=__initdata">__initdata</a>;
<a name="L164" href="source/net/ipv4/ipconfig.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/ipconfig.c#L165">165</a> <b><i>/* MTU for boot device */</i></b>
<a name="L166" href="source/net/ipv4/ipconfig.c#L166">166</a> static int ic_dev_mtu <a href="ident?i=__initdata">__initdata</a>;
<a name="L167" href="source/net/ipv4/ipconfig.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/ipconfig.c#L168">168</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L169" href="source/net/ipv4/ipconfig.c#L169">169</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(ic_recv_lock);
<a name="L170" href="source/net/ipv4/ipconfig.c#L170">170</a> static volatile int ic_got_reply <a href="ident?i=__initdata">__initdata</a>;    <b><i>/* Proto(s) that replied */</i></b>
<a name="L171" href="source/net/ipv4/ipconfig.c#L171">171</a> #endif
<a name="L172" href="source/net/ipv4/ipconfig.c#L172">172</a> #ifdef <a href="ident?i=IPCONFIG_DHCP">IPCONFIG_DHCP</a>
<a name="L173" href="source/net/ipv4/ipconfig.c#L173">173</a> static int ic_dhcp_msgtype <a href="ident?i=__initdata">__initdata</a>;  <b><i>/* DHCP msg type received */</i></b>
<a name="L174" href="source/net/ipv4/ipconfig.c#L174">174</a> #endif
<a name="L175" href="source/net/ipv4/ipconfig.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/ipconfig.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/ipconfig.c#L177">177</a> <b><i>/*</i></b>
<a name="L178" href="source/net/ipv4/ipconfig.c#L178">178</a> <b><i> *      Network devices</i></b>
<a name="L179" href="source/net/ipv4/ipconfig.c#L179">179</a> <b><i> */</i></b>
<a name="L180" href="source/net/ipv4/ipconfig.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/ipconfig.c#L181">181</a> struct <a href="ident?i=ic_device">ic_device</a> {
<a name="L182" href="source/net/ipv4/ipconfig.c#L182">182</a>         struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=next">next</a>;
<a name="L183" href="source/net/ipv4/ipconfig.c#L183">183</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L184" href="source/net/ipv4/ipconfig.c#L184">184</a>         unsigned short <a href="ident?i=flags">flags</a>;
<a name="L185" href="source/net/ipv4/ipconfig.c#L185">185</a>         short able;
<a name="L186" href="source/net/ipv4/ipconfig.c#L186">186</a>         <a href="ident?i=__be32">__be32</a> xid;
<a name="L187" href="source/net/ipv4/ipconfig.c#L187">187</a> };
<a name="L188" href="source/net/ipv4/ipconfig.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/ipconfig.c#L189">189</a> static struct <a href="ident?i=ic_device">ic_device</a> *ic_first_dev <a href="ident?i=__initdata">__initdata</a>;       <b><i>/* List of open device */</i></b>
<a name="L190" href="source/net/ipv4/ipconfig.c#L190">190</a> static struct <a href="ident?i=net_device">net_device</a> *ic_dev <a href="ident?i=__initdata">__initdata</a>;            <b><i>/* Selected device */</i></b>
<a name="L191" href="source/net/ipv4/ipconfig.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/ipconfig.c#L192">192</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=__init">__init</a> <a href="ident?i=ic_is_init_dev">ic_is_init_dev</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L193" href="source/net/ipv4/ipconfig.c#L193">193</a> {
<a name="L194" href="source/net/ipv4/ipconfig.c#L194">194</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>)
<a name="L195" href="source/net/ipv4/ipconfig.c#L195">195</a>                 return <a href="ident?i=false">false</a>;
<a name="L196" href="source/net/ipv4/ipconfig.c#L196">196</a>         return user_dev_name[0] ? !<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, user_dev_name) :
<a name="L197" href="source/net/ipv4/ipconfig.c#L197">197</a>             (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>) &amp;&amp;
<a name="L198" href="source/net/ipv4/ipconfig.c#L198">198</a>              (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>|<a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>)) &amp;&amp;
<a name="L199" href="source/net/ipv4/ipconfig.c#L199">199</a>              <a href="ident?i=strncmp">strncmp</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <i>"dummy"</i>, 5));
<a name="L200" href="source/net/ipv4/ipconfig.c#L200">200</a> }
<a name="L201" href="source/net/ipv4/ipconfig.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/ipconfig.c#L202">202</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_open_devs">ic_open_devs</a>(void)
<a name="L203" href="source/net/ipv4/ipconfig.c#L203">203</a> {
<a name="L204" href="source/net/ipv4/ipconfig.c#L204">204</a>         struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>, **<a href="ident?i=last">last</a>;
<a name="L205" href="source/net/ipv4/ipconfig.c#L205">205</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L206" href="source/net/ipv4/ipconfig.c#L206">206</a>         unsigned short oflags;
<a name="L207" href="source/net/ipv4/ipconfig.c#L207">207</a>         unsigned long <a href="ident?i=start">start</a>, next_msg;
<a name="L208" href="source/net/ipv4/ipconfig.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/ipconfig.c#L209">209</a>         <a href="ident?i=last">last</a> = &amp;ic_first_dev;
<a name="L210" href="source/net/ipv4/ipconfig.c#L210">210</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L211" href="source/net/ipv4/ipconfig.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/ipconfig.c#L212">212</a>         <b><i>/* bring loopback and DSA master network devices up first */</i></b>
<a name="L213" href="source/net/ipv4/ipconfig.c#L213">213</a>         <a href="ident?i=for_each_netdev">for_each_netdev</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L214" href="source/net/ipv4/ipconfig.c#L214">214</a>                 if (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>) &amp;&amp; !<a href="ident?i=netdev_uses_dsa">netdev_uses_dsa</a>(<a href="ident?i=dev">dev</a>))
<a name="L215" href="source/net/ipv4/ipconfig.c#L215">215</a>                         continue;
<a name="L216" href="source/net/ipv4/ipconfig.c#L216">216</a>                 if (<a href="ident?i=dev_change_flags">dev_change_flags</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> | <a href="ident?i=IFF_UP">IFF_UP</a>) &lt; 0)
<a name="L217" href="source/net/ipv4/ipconfig.c#L217">217</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Failed to open %s\n"</i>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L218" href="source/net/ipv4/ipconfig.c#L218">218</a>         }
<a name="L219" href="source/net/ipv4/ipconfig.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/ipconfig.c#L220">220</a>         <a href="ident?i=for_each_netdev">for_each_netdev</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L221" href="source/net/ipv4/ipconfig.c#L221">221</a>                 if (<a href="ident?i=ic_is_init_dev">ic_is_init_dev</a>(<a href="ident?i=dev">dev</a>)) {
<a name="L222" href="source/net/ipv4/ipconfig.c#L222">222</a>                         int able = 0;
<a name="L223" href="source/net/ipv4/ipconfig.c#L223">223</a>                         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a> &gt;= 364)
<a name="L224" href="source/net/ipv4/ipconfig.c#L224">224</a>                                 able |= <a href="ident?i=IC_BOOTP">IC_BOOTP</a>;
<a name="L225" href="source/net/ipv4/ipconfig.c#L225">225</a>                         else
<a name="L226" href="source/net/ipv4/ipconfig.c#L226">226</a>                                 <a href="ident?i=pr_warn">pr_warn</a>(<i>"DHCP/BOOTP: Ignoring device %s, MTU %d too small"</i>,
<a name="L227" href="source/net/ipv4/ipconfig.c#L227">227</a>                                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>);
<a name="L228" href="source/net/ipv4/ipconfig.c#L228">228</a>                         if (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_NOARP">IFF_NOARP</a>))
<a name="L229" href="source/net/ipv4/ipconfig.c#L229">229</a>                                 able |= <a href="ident?i=IC_RARP">IC_RARP</a>;
<a name="L230" href="source/net/ipv4/ipconfig.c#L230">230</a>                         able &amp;= <a href="ident?i=ic_proto_enabled">ic_proto_enabled</a>;
<a name="L231" href="source/net/ipv4/ipconfig.c#L231">231</a>                         if (<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp;&amp; !able)
<a name="L232" href="source/net/ipv4/ipconfig.c#L232">232</a>                                 continue;
<a name="L233" href="source/net/ipv4/ipconfig.c#L233">233</a>                         oflags = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>;
<a name="L234" href="source/net/ipv4/ipconfig.c#L234">234</a>                         if (<a href="ident?i=dev_change_flags">dev_change_flags</a>(<a href="ident?i=dev">dev</a>, oflags | <a href="ident?i=IFF_UP">IFF_UP</a>) &lt; 0) {
<a name="L235" href="source/net/ipv4/ipconfig.c#L235">235</a>                                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Failed to open %s\n"</i>,
<a name="L236" href="source/net/ipv4/ipconfig.c#L236">236</a>                                        <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L237" href="source/net/ipv4/ipconfig.c#L237">237</a>                                 continue;
<a name="L238" href="source/net/ipv4/ipconfig.c#L238">238</a>                         }
<a name="L239" href="source/net/ipv4/ipconfig.c#L239">239</a>                         if (!(<a href="ident?i=d">d</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=ic_device">ic_device</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>))) {
<a name="L240" href="source/net/ipv4/ipconfig.c#L240">240</a>                                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L241" href="source/net/ipv4/ipconfig.c#L241">241</a>                                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L242" href="source/net/ipv4/ipconfig.c#L242">242</a>                         }
<a name="L243" href="source/net/ipv4/ipconfig.c#L243">243</a>                         <a href="ident?i=d">d</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L244" href="source/net/ipv4/ipconfig.c#L244">244</a>                         *<a href="ident?i=last">last</a> = <a href="ident?i=d">d</a>;
<a name="L245" href="source/net/ipv4/ipconfig.c#L245">245</a>                         <a href="ident?i=last">last</a> = &amp;<a href="ident?i=d">d</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L246" href="source/net/ipv4/ipconfig.c#L246">246</a>                         <a href="ident?i=d">d</a>-&gt;<a href="ident?i=flags">flags</a> = oflags;
<a name="L247" href="source/net/ipv4/ipconfig.c#L247">247</a>                         <a href="ident?i=d">d</a>-&gt;able = able;
<a name="L248" href="source/net/ipv4/ipconfig.c#L248">248</a>                         if (able &amp; <a href="ident?i=IC_BOOTP">IC_BOOTP</a>)
<a name="L249" href="source/net/ipv4/ipconfig.c#L249">249</a>                                 <a href="ident?i=get_random_bytes">get_random_bytes</a>(&amp;<a href="ident?i=d">d</a>-&gt;xid, sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L250" href="source/net/ipv4/ipconfig.c#L250">250</a>                         else
<a name="L251" href="source/net/ipv4/ipconfig.c#L251">251</a>                                 <a href="ident?i=d">d</a>-&gt;xid = 0;
<a name="L252" href="source/net/ipv4/ipconfig.c#L252">252</a>                         ic_proto_have_if |= able;
<a name="L253" href="source/net/ipv4/ipconfig.c#L253">253</a>                         <a href="ident?i=DBG">DBG</a>((<i>"IP-Config: %s UP (able=%d, xid=%08x)\n"</i>,
<a name="L254" href="source/net/ipv4/ipconfig.c#L254">254</a>                                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, able, <a href="ident?i=d">d</a>-&gt;xid));
<a name="L255" href="source/net/ipv4/ipconfig.c#L255">255</a>                 }
<a name="L256" href="source/net/ipv4/ipconfig.c#L256">256</a>         }
<a name="L257" href="source/net/ipv4/ipconfig.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/ipconfig.c#L258">258</a>         <b><i>/* no point in waiting if we could not bring up at least one device */</i></b>
<a name="L259" href="source/net/ipv4/ipconfig.c#L259">259</a>         if (!ic_first_dev)
<a name="L260" href="source/net/ipv4/ipconfig.c#L260">260</a>                 goto have_carrier;
<a name="L261" href="source/net/ipv4/ipconfig.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/ipconfig.c#L262">262</a>         <b><i>/* wait for a carrier on at least one device */</i></b>
<a name="L263" href="source/net/ipv4/ipconfig.c#L263">263</a>         <a href="ident?i=start">start</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L264" href="source/net/ipv4/ipconfig.c#L264">264</a>         next_msg = <a href="ident?i=start">start</a> + <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(<a href="ident?i=CONF_CARRIER_TIMEOUT">CONF_CARRIER_TIMEOUT</a>/12);
<a name="L265" href="source/net/ipv4/ipconfig.c#L265">265</a>         while (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, <a href="ident?i=start">start</a> +
<a name="L266" href="source/net/ipv4/ipconfig.c#L266">266</a>                            <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(<a href="ident?i=CONF_CARRIER_TIMEOUT">CONF_CARRIER_TIMEOUT</a>))) {
<a name="L267" href="source/net/ipv4/ipconfig.c#L267">267</a>                 int <a href="ident?i=wait">wait</a>, elapsed;
<a name="L268" href="source/net/ipv4/ipconfig.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/ipconfig.c#L269">269</a>                 <a href="ident?i=for_each_netdev">for_each_netdev</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=dev">dev</a>)
<a name="L270" href="source/net/ipv4/ipconfig.c#L270">270</a>                         if (<a href="ident?i=ic_is_init_dev">ic_is_init_dev</a>(<a href="ident?i=dev">dev</a>) &amp;&amp; <a href="ident?i=netif_carrier_ok">netif_carrier_ok</a>(<a href="ident?i=dev">dev</a>))
<a name="L271" href="source/net/ipv4/ipconfig.c#L271">271</a>                                 goto have_carrier;
<a name="L272" href="source/net/ipv4/ipconfig.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/ipconfig.c#L273">273</a>                 <a href="ident?i=msleep">msleep</a>(1);
<a name="L274" href="source/net/ipv4/ipconfig.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/ipconfig.c#L275">275</a>                 if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, next_msg))
<a name="L276" href="source/net/ipv4/ipconfig.c#L276">276</a>                         continue;
<a name="L277" href="source/net/ipv4/ipconfig.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/ipconfig.c#L278">278</a>                 elapsed = <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(<a href="ident?i=jiffies">jiffies</a> - <a href="ident?i=start">start</a>);
<a name="L279" href="source/net/ipv4/ipconfig.c#L279">279</a>                 <a href="ident?i=wait">wait</a> = (<a href="ident?i=CONF_CARRIER_TIMEOUT">CONF_CARRIER_TIMEOUT</a> - elapsed + 500)/1000;
<a name="L280" href="source/net/ipv4/ipconfig.c#L280">280</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"Waiting up to %d more seconds for network.\n"</i>, <a href="ident?i=wait">wait</a>);
<a name="L281" href="source/net/ipv4/ipconfig.c#L281">281</a>                 next_msg = <a href="ident?i=jiffies">jiffies</a> + <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(<a href="ident?i=CONF_CARRIER_TIMEOUT">CONF_CARRIER_TIMEOUT</a>/12);
<a name="L282" href="source/net/ipv4/ipconfig.c#L282">282</a>         }
<a name="L283" href="source/net/ipv4/ipconfig.c#L283">283</a> have_carrier:
<a name="L284" href="source/net/ipv4/ipconfig.c#L284">284</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L285" href="source/net/ipv4/ipconfig.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/ipconfig.c#L286">286</a>         *<a href="ident?i=last">last</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L287" href="source/net/ipv4/ipconfig.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/ipconfig.c#L288">288</a>         if (!ic_first_dev) {
<a name="L289" href="source/net/ipv4/ipconfig.c#L289">289</a>                 if (user_dev_name[0])
<a name="L290" href="source/net/ipv4/ipconfig.c#L290">290</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Device `%s' not found\n"</i>,
<a name="L291" href="source/net/ipv4/ipconfig.c#L291">291</a>                                user_dev_name);
<a name="L292" href="source/net/ipv4/ipconfig.c#L292">292</a>                 else
<a name="L293" href="source/net/ipv4/ipconfig.c#L293">293</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: No network devices available\n"</i>);
<a name="L294" href="source/net/ipv4/ipconfig.c#L294">294</a>                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L295" href="source/net/ipv4/ipconfig.c#L295">295</a>         }
<a name="L296" href="source/net/ipv4/ipconfig.c#L296">296</a>         return 0;
<a name="L297" href="source/net/ipv4/ipconfig.c#L297">297</a> }
<a name="L298" href="source/net/ipv4/ipconfig.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/ipconfig.c#L299">299</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_close_devs">ic_close_devs</a>(void)
<a name="L300" href="source/net/ipv4/ipconfig.c#L300">300</a> {
<a name="L301" href="source/net/ipv4/ipconfig.c#L301">301</a>         struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>, *<a href="ident?i=next">next</a>;
<a name="L302" href="source/net/ipv4/ipconfig.c#L302">302</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L303" href="source/net/ipv4/ipconfig.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/ipconfig.c#L304">304</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L305" href="source/net/ipv4/ipconfig.c#L305">305</a>         <a href="ident?i=next">next</a> = ic_first_dev;
<a name="L306" href="source/net/ipv4/ipconfig.c#L306">306</a>         while ((<a href="ident?i=d">d</a> = <a href="ident?i=next">next</a>)) {
<a name="L307" href="source/net/ipv4/ipconfig.c#L307">307</a>                 <a href="ident?i=next">next</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L308" href="source/net/ipv4/ipconfig.c#L308">308</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L309" href="source/net/ipv4/ipconfig.c#L309">309</a>                 if (<a href="ident?i=dev">dev</a> != ic_dev &amp;&amp; !<a href="ident?i=netdev_uses_dsa">netdev_uses_dsa</a>(<a href="ident?i=dev">dev</a>)) {
<a name="L310" href="source/net/ipv4/ipconfig.c#L310">310</a>                         <a href="ident?i=DBG">DBG</a>((<i>"IP-Config: Downing %s\n"</i>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>));
<a name="L311" href="source/net/ipv4/ipconfig.c#L311">311</a>                         <a href="ident?i=dev_change_flags">dev_change_flags</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=d">d</a>-&gt;<a href="ident?i=flags">flags</a>);
<a name="L312" href="source/net/ipv4/ipconfig.c#L312">312</a>                 }
<a name="L313" href="source/net/ipv4/ipconfig.c#L313">313</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=d">d</a>);
<a name="L314" href="source/net/ipv4/ipconfig.c#L314">314</a>         }
<a name="L315" href="source/net/ipv4/ipconfig.c#L315">315</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L316" href="source/net/ipv4/ipconfig.c#L316">316</a> }
<a name="L317" href="source/net/ipv4/ipconfig.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/ipconfig.c#L318">318</a> <b><i>/*</i></b>
<a name="L319" href="source/net/ipv4/ipconfig.c#L319">319</a> <b><i> *      Interface to various network functions.</i></b>
<a name="L320" href="source/net/ipv4/ipconfig.c#L320">320</a> <b><i> */</i></b>
<a name="L321" href="source/net/ipv4/ipconfig.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/ipconfig.c#L322">322</a> static inline void
<a name="L323" href="source/net/ipv4/ipconfig.c#L323">323</a> <a href="ident?i=set_sockaddr">set_sockaddr</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=sin">sin</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>)
<a name="L324" href="source/net/ipv4/ipconfig.c#L324">324</a> {
<a name="L325" href="source/net/ipv4/ipconfig.c#L325">325</a>         <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L326" href="source/net/ipv4/ipconfig.c#L326">326</a>         <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=addr">addr</a>;
<a name="L327" href="source/net/ipv4/ipconfig.c#L327">327</a>         <a href="ident?i=sin">sin</a>-&gt;sin_port = <a href="ident?i=port">port</a>;
<a name="L328" href="source/net/ipv4/ipconfig.c#L328">328</a> }
<a name="L329" href="source/net/ipv4/ipconfig.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/ipconfig.c#L330">330</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_devinet_ioctl">ic_devinet_ioctl</a>(unsigned int <a href="ident?i=cmd">cmd</a>, struct <a href="ident?i=ifreq">ifreq</a> *<a href="ident?i=arg">arg</a>)
<a name="L331" href="source/net/ipv4/ipconfig.c#L331">331</a> {
<a name="L332" href="source/net/ipv4/ipconfig.c#L332">332</a>         int <a href="ident?i=res">res</a>;
<a name="L333" href="source/net/ipv4/ipconfig.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/ipconfig.c#L334">334</a>         <a href="ident?i=mm_segment_t">mm_segment_t</a> oldfs = <a href="ident?i=get_fs">get_fs</a>();
<a name="L335" href="source/net/ipv4/ipconfig.c#L335">335</a>         <a href="ident?i=set_fs">set_fs</a>(<a href="ident?i=get_ds">get_ds</a>());
<a name="L336" href="source/net/ipv4/ipconfig.c#L336">336</a>         <a href="ident?i=res">res</a> = <a href="ident?i=devinet_ioctl">devinet_ioctl</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=cmd">cmd</a>, (struct <a href="ident?i=ifreq">ifreq</a> <a href="ident?i=__user">__user</a> *) <a href="ident?i=arg">arg</a>);
<a name="L337" href="source/net/ipv4/ipconfig.c#L337">337</a>         <a href="ident?i=set_fs">set_fs</a>(oldfs);
<a name="L338" href="source/net/ipv4/ipconfig.c#L338">338</a>         return <a href="ident?i=res">res</a>;
<a name="L339" href="source/net/ipv4/ipconfig.c#L339">339</a> }
<a name="L340" href="source/net/ipv4/ipconfig.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/ipconfig.c#L341">341</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_dev_ioctl">ic_dev_ioctl</a>(unsigned int <a href="ident?i=cmd">cmd</a>, struct <a href="ident?i=ifreq">ifreq</a> *<a href="ident?i=arg">arg</a>)
<a name="L342" href="source/net/ipv4/ipconfig.c#L342">342</a> {
<a name="L343" href="source/net/ipv4/ipconfig.c#L343">343</a>         int <a href="ident?i=res">res</a>;
<a name="L344" href="source/net/ipv4/ipconfig.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/ipconfig.c#L345">345</a>         <a href="ident?i=mm_segment_t">mm_segment_t</a> oldfs = <a href="ident?i=get_fs">get_fs</a>();
<a name="L346" href="source/net/ipv4/ipconfig.c#L346">346</a>         <a href="ident?i=set_fs">set_fs</a>(<a href="ident?i=get_ds">get_ds</a>());
<a name="L347" href="source/net/ipv4/ipconfig.c#L347">347</a>         <a href="ident?i=res">res</a> = <a href="ident?i=dev_ioctl">dev_ioctl</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=cmd">cmd</a>, (struct <a href="ident?i=ifreq">ifreq</a> <a href="ident?i=__user">__user</a> *) <a href="ident?i=arg">arg</a>);
<a name="L348" href="source/net/ipv4/ipconfig.c#L348">348</a>         <a href="ident?i=set_fs">set_fs</a>(oldfs);
<a name="L349" href="source/net/ipv4/ipconfig.c#L349">349</a>         return <a href="ident?i=res">res</a>;
<a name="L350" href="source/net/ipv4/ipconfig.c#L350">350</a> }
<a name="L351" href="source/net/ipv4/ipconfig.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/ipconfig.c#L352">352</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_route_ioctl">ic_route_ioctl</a>(unsigned int <a href="ident?i=cmd">cmd</a>, struct <a href="ident?i=rtentry">rtentry</a> *<a href="ident?i=arg">arg</a>)
<a name="L353" href="source/net/ipv4/ipconfig.c#L353">353</a> {
<a name="L354" href="source/net/ipv4/ipconfig.c#L354">354</a>         int <a href="ident?i=res">res</a>;
<a name="L355" href="source/net/ipv4/ipconfig.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/ipconfig.c#L356">356</a>         <a href="ident?i=mm_segment_t">mm_segment_t</a> oldfs = <a href="ident?i=get_fs">get_fs</a>();
<a name="L357" href="source/net/ipv4/ipconfig.c#L357">357</a>         <a href="ident?i=set_fs">set_fs</a>(<a href="ident?i=get_ds">get_ds</a>());
<a name="L358" href="source/net/ipv4/ipconfig.c#L358">358</a>         <a href="ident?i=res">res</a> = <a href="ident?i=ip_rt_ioctl">ip_rt_ioctl</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=cmd">cmd</a>, (void <a href="ident?i=__user">__user</a> *) <a href="ident?i=arg">arg</a>);
<a name="L359" href="source/net/ipv4/ipconfig.c#L359">359</a>         <a href="ident?i=set_fs">set_fs</a>(oldfs);
<a name="L360" href="source/net/ipv4/ipconfig.c#L360">360</a>         return <a href="ident?i=res">res</a>;
<a name="L361" href="source/net/ipv4/ipconfig.c#L361">361</a> }
<a name="L362" href="source/net/ipv4/ipconfig.c#L362">362</a> 
<a name="L363" href="source/net/ipv4/ipconfig.c#L363">363</a> <b><i>/*</i></b>
<a name="L364" href="source/net/ipv4/ipconfig.c#L364">364</a> <b><i> *      Set up interface addresses and routes.</i></b>
<a name="L365" href="source/net/ipv4/ipconfig.c#L365">365</a> <b><i> */</i></b>
<a name="L366" href="source/net/ipv4/ipconfig.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/ipconfig.c#L367">367</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_setup_if">ic_setup_if</a>(void)
<a name="L368" href="source/net/ipv4/ipconfig.c#L368">368</a> {
<a name="L369" href="source/net/ipv4/ipconfig.c#L369">369</a>         struct <a href="ident?i=ifreq">ifreq</a> <a href="ident?i=ir">ir</a>;
<a name="L370" href="source/net/ipv4/ipconfig.c#L370">370</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=sin">sin</a> = (void *) &amp;<a href="ident?i=ir">ir</a>.ifr_ifru.ifru_addr;
<a name="L371" href="source/net/ipv4/ipconfig.c#L371">371</a>         int <a href="ident?i=err">err</a>;
<a name="L372" href="source/net/ipv4/ipconfig.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/ipconfig.c#L373">373</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=ir">ir</a>, 0, sizeof(<a href="ident?i=ir">ir</a>));
<a name="L374" href="source/net/ipv4/ipconfig.c#L374">374</a>         <a href="ident?i=strcpy">strcpy</a>(<a href="ident?i=ir">ir</a>.ifr_ifrn.ifrn_name, ic_dev-&gt;<a href="ident?i=name">name</a>);
<a name="L375" href="source/net/ipv4/ipconfig.c#L375">375</a>         <a href="ident?i=set_sockaddr">set_sockaddr</a>(<a href="ident?i=sin">sin</a>, <a href="ident?i=ic_myaddr">ic_myaddr</a>, 0);
<a name="L376" href="source/net/ipv4/ipconfig.c#L376">376</a>         if ((<a href="ident?i=err">err</a> = <a href="ident?i=ic_devinet_ioctl">ic_devinet_ioctl</a>(<a href="ident?i=SIOCSIFADDR">SIOCSIFADDR</a>, &amp;<a href="ident?i=ir">ir</a>)) &lt; 0) {
<a name="L377" href="source/net/ipv4/ipconfig.c#L377">377</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Unable to set interface address (%d)\n"</i>,
<a name="L378" href="source/net/ipv4/ipconfig.c#L378">378</a>                        <a href="ident?i=err">err</a>);
<a name="L379" href="source/net/ipv4/ipconfig.c#L379">379</a>                 return -1;
<a name="L380" href="source/net/ipv4/ipconfig.c#L380">380</a>         }
<a name="L381" href="source/net/ipv4/ipconfig.c#L381">381</a>         <a href="ident?i=set_sockaddr">set_sockaddr</a>(<a href="ident?i=sin">sin</a>, <a href="ident?i=ic_netmask">ic_netmask</a>, 0);
<a name="L382" href="source/net/ipv4/ipconfig.c#L382">382</a>         if ((<a href="ident?i=err">err</a> = <a href="ident?i=ic_devinet_ioctl">ic_devinet_ioctl</a>(<a href="ident?i=SIOCSIFNETMASK">SIOCSIFNETMASK</a>, &amp;<a href="ident?i=ir">ir</a>)) &lt; 0) {
<a name="L383" href="source/net/ipv4/ipconfig.c#L383">383</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Unable to set interface netmask (%d)\n"</i>,
<a name="L384" href="source/net/ipv4/ipconfig.c#L384">384</a>                        <a href="ident?i=err">err</a>);
<a name="L385" href="source/net/ipv4/ipconfig.c#L385">385</a>                 return -1;
<a name="L386" href="source/net/ipv4/ipconfig.c#L386">386</a>         }
<a name="L387" href="source/net/ipv4/ipconfig.c#L387">387</a>         <a href="ident?i=set_sockaddr">set_sockaddr</a>(<a href="ident?i=sin">sin</a>, <a href="ident?i=ic_myaddr">ic_myaddr</a> | ~ic_netmask, 0);
<a name="L388" href="source/net/ipv4/ipconfig.c#L388">388</a>         if ((<a href="ident?i=err">err</a> = <a href="ident?i=ic_devinet_ioctl">ic_devinet_ioctl</a>(<a href="ident?i=SIOCSIFBRDADDR">SIOCSIFBRDADDR</a>, &amp;<a href="ident?i=ir">ir</a>)) &lt; 0) {
<a name="L389" href="source/net/ipv4/ipconfig.c#L389">389</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Unable to set interface broadcast address (%d)\n"</i>,
<a name="L390" href="source/net/ipv4/ipconfig.c#L390">390</a>                        <a href="ident?i=err">err</a>);
<a name="L391" href="source/net/ipv4/ipconfig.c#L391">391</a>                 return -1;
<a name="L392" href="source/net/ipv4/ipconfig.c#L392">392</a>         }
<a name="L393" href="source/net/ipv4/ipconfig.c#L393">393</a>         <b><i>/* Handle the case where we need non-standard MTU on the boot link (a network</i></b>
<a name="L394" href="source/net/ipv4/ipconfig.c#L394">394</a> <b><i>         * using jumbo frames, for instance).  If we can't set the mtu, don't error</i></b>
<a name="L395" href="source/net/ipv4/ipconfig.c#L395">395</a> <b><i>         * out, we'll try to muddle along.</i></b>
<a name="L396" href="source/net/ipv4/ipconfig.c#L396">396</a> <b><i>         */</i></b>
<a name="L397" href="source/net/ipv4/ipconfig.c#L397">397</a>         if (ic_dev_mtu != 0) {
<a name="L398" href="source/net/ipv4/ipconfig.c#L398">398</a>                 <a href="ident?i=strcpy">strcpy</a>(<a href="ident?i=ir">ir</a>.<a href="ident?i=ifr_name">ifr_name</a>, ic_dev-&gt;<a href="ident?i=name">name</a>);
<a name="L399" href="source/net/ipv4/ipconfig.c#L399">399</a>                 <a href="ident?i=ir">ir</a>.<a href="ident?i=ifr_mtu">ifr_mtu</a> = ic_dev_mtu;
<a name="L400" href="source/net/ipv4/ipconfig.c#L400">400</a>                 if ((<a href="ident?i=err">err</a> = <a href="ident?i=ic_dev_ioctl">ic_dev_ioctl</a>(<a href="ident?i=SIOCSIFMTU">SIOCSIFMTU</a>, &amp;<a href="ident?i=ir">ir</a>)) &lt; 0)
<a name="L401" href="source/net/ipv4/ipconfig.c#L401">401</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Unable to set interface mtu to %d (%d)\n"</i>,
<a name="L402" href="source/net/ipv4/ipconfig.c#L402">402</a>                                ic_dev_mtu, <a href="ident?i=err">err</a>);
<a name="L403" href="source/net/ipv4/ipconfig.c#L403">403</a>         }
<a name="L404" href="source/net/ipv4/ipconfig.c#L404">404</a>         return 0;
<a name="L405" href="source/net/ipv4/ipconfig.c#L405">405</a> }
<a name="L406" href="source/net/ipv4/ipconfig.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/ipconfig.c#L407">407</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_setup_routes">ic_setup_routes</a>(void)
<a name="L408" href="source/net/ipv4/ipconfig.c#L408">408</a> {
<a name="L409" href="source/net/ipv4/ipconfig.c#L409">409</a>         <b><i>/* No need to setup device routes, only the default route... */</i></b>
<a name="L410" href="source/net/ipv4/ipconfig.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/ipconfig.c#L411">411</a>         if (<a href="ident?i=ic_gateway">ic_gateway</a> != <a href="ident?i=NONE">NONE</a>) {
<a name="L412" href="source/net/ipv4/ipconfig.c#L412">412</a>                 struct <a href="ident?i=rtentry">rtentry</a> rm;
<a name="L413" href="source/net/ipv4/ipconfig.c#L413">413</a>                 int <a href="ident?i=err">err</a>;
<a name="L414" href="source/net/ipv4/ipconfig.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/ipconfig.c#L415">415</a>                 <a href="ident?i=memset">memset</a>(&amp;rm, 0, sizeof(rm));
<a name="L416" href="source/net/ipv4/ipconfig.c#L416">416</a>                 if ((<a href="ident?i=ic_gateway">ic_gateway</a> ^ <a href="ident?i=ic_myaddr">ic_myaddr</a>) &amp; <a href="ident?i=ic_netmask">ic_netmask</a>) {
<a name="L417" href="source/net/ipv4/ipconfig.c#L417">417</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Gateway not on directly connected network\n"</i>);
<a name="L418" href="source/net/ipv4/ipconfig.c#L418">418</a>                         return -1;
<a name="L419" href="source/net/ipv4/ipconfig.c#L419">419</a>                 }
<a name="L420" href="source/net/ipv4/ipconfig.c#L420">420</a>                 <a href="ident?i=set_sockaddr">set_sockaddr</a>((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) &amp;rm.rt_dst, 0, 0);
<a name="L421" href="source/net/ipv4/ipconfig.c#L421">421</a>                 <a href="ident?i=set_sockaddr">set_sockaddr</a>((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) &amp;rm.rt_genmask, 0, 0);
<a name="L422" href="source/net/ipv4/ipconfig.c#L422">422</a>                 <a href="ident?i=set_sockaddr">set_sockaddr</a>((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) &amp;rm.rt_gateway, <a href="ident?i=ic_gateway">ic_gateway</a>, 0);
<a name="L423" href="source/net/ipv4/ipconfig.c#L423">423</a>                 rm.rt_flags = <a href="ident?i=RTF_UP">RTF_UP</a> | <a href="ident?i=RTF_GATEWAY">RTF_GATEWAY</a>;
<a name="L424" href="source/net/ipv4/ipconfig.c#L424">424</a>                 if ((<a href="ident?i=err">err</a> = <a href="ident?i=ic_route_ioctl">ic_route_ioctl</a>(<a href="ident?i=SIOCADDRT">SIOCADDRT</a>, &amp;rm)) &lt; 0) {
<a name="L425" href="source/net/ipv4/ipconfig.c#L425">425</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Cannot add default route (%d)\n"</i>,
<a name="L426" href="source/net/ipv4/ipconfig.c#L426">426</a>                                <a href="ident?i=err">err</a>);
<a name="L427" href="source/net/ipv4/ipconfig.c#L427">427</a>                         return -1;
<a name="L428" href="source/net/ipv4/ipconfig.c#L428">428</a>                 }
<a name="L429" href="source/net/ipv4/ipconfig.c#L429">429</a>         }
<a name="L430" href="source/net/ipv4/ipconfig.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/ipconfig.c#L431">431</a>         return 0;
<a name="L432" href="source/net/ipv4/ipconfig.c#L432">432</a> }
<a name="L433" href="source/net/ipv4/ipconfig.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/ipconfig.c#L434">434</a> <b><i>/*</i></b>
<a name="L435" href="source/net/ipv4/ipconfig.c#L435">435</a> <b><i> *      Fill in default values for all missing parameters.</i></b>
<a name="L436" href="source/net/ipv4/ipconfig.c#L436">436</a> <b><i> */</i></b>
<a name="L437" href="source/net/ipv4/ipconfig.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ipconfig.c#L438">438</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_defaults">ic_defaults</a>(void)
<a name="L439" href="source/net/ipv4/ipconfig.c#L439">439</a> {
<a name="L440" href="source/net/ipv4/ipconfig.c#L440">440</a>         <b><i>/*</i></b>
<a name="L441" href="source/net/ipv4/ipconfig.c#L441">441</a> <b><i>         *      At this point we have no userspace running so need not</i></b>
<a name="L442" href="source/net/ipv4/ipconfig.c#L442">442</a> <b><i>         *      claim locks on system_utsname</i></b>
<a name="L443" href="source/net/ipv4/ipconfig.c#L443">443</a> <b><i>         */</i></b>
<a name="L444" href="source/net/ipv4/ipconfig.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/ipconfig.c#L445">445</a>         if (!ic_host_name_set)
<a name="L446" href="source/net/ipv4/ipconfig.c#L446">446</a>                 <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=init_utsname">init_utsname</a>()-&gt;nodename, <i>"%pI4"</i>, &amp;<a href="ident?i=ic_myaddr">ic_myaddr</a>);
<a name="L447" href="source/net/ipv4/ipconfig.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/ipconfig.c#L448">448</a>         if (<a href="ident?i=root_server_addr">root_server_addr</a> == <a href="ident?i=NONE">NONE</a>)
<a name="L449" href="source/net/ipv4/ipconfig.c#L449">449</a>                 <a href="ident?i=root_server_addr">root_server_addr</a> = <a href="ident?i=ic_servaddr">ic_servaddr</a>;
<a name="L450" href="source/net/ipv4/ipconfig.c#L450">450</a> 
<a name="L451" href="source/net/ipv4/ipconfig.c#L451">451</a>         if (<a href="ident?i=ic_netmask">ic_netmask</a> == <a href="ident?i=NONE">NONE</a>) {
<a name="L452" href="source/net/ipv4/ipconfig.c#L452">452</a>                 if (<a href="ident?i=IN_CLASSA">IN_CLASSA</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=ic_myaddr">ic_myaddr</a>)))
<a name="L453" href="source/net/ipv4/ipconfig.c#L453">453</a>                         <a href="ident?i=ic_netmask">ic_netmask</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=IN_CLASSA_NET">IN_CLASSA_NET</a>);
<a name="L454" href="source/net/ipv4/ipconfig.c#L454">454</a>                 else if (<a href="ident?i=IN_CLASSB">IN_CLASSB</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=ic_myaddr">ic_myaddr</a>)))
<a name="L455" href="source/net/ipv4/ipconfig.c#L455">455</a>                         <a href="ident?i=ic_netmask">ic_netmask</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=IN_CLASSB_NET">IN_CLASSB_NET</a>);
<a name="L456" href="source/net/ipv4/ipconfig.c#L456">456</a>                 else if (<a href="ident?i=IN_CLASSC">IN_CLASSC</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=ic_myaddr">ic_myaddr</a>)))
<a name="L457" href="source/net/ipv4/ipconfig.c#L457">457</a>                         <a href="ident?i=ic_netmask">ic_netmask</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=IN_CLASSC_NET">IN_CLASSC_NET</a>);
<a name="L458" href="source/net/ipv4/ipconfig.c#L458">458</a>                 else {
<a name="L459" href="source/net/ipv4/ipconfig.c#L459">459</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Unable to guess netmask for address %pI4\n"</i>,
<a name="L460" href="source/net/ipv4/ipconfig.c#L460">460</a>                                &amp;<a href="ident?i=ic_myaddr">ic_myaddr</a>);
<a name="L461" href="source/net/ipv4/ipconfig.c#L461">461</a>                         return -1;
<a name="L462" href="source/net/ipv4/ipconfig.c#L462">462</a>                 }
<a name="L463" href="source/net/ipv4/ipconfig.c#L463">463</a>                 <a href="ident?i=printk">printk</a>(<i>"IP-Config: Guessing netmask %pI4\n"</i>, &amp;<a href="ident?i=ic_netmask">ic_netmask</a>);
<a name="L464" href="source/net/ipv4/ipconfig.c#L464">464</a>         }
<a name="L465" href="source/net/ipv4/ipconfig.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/ipconfig.c#L466">466</a>         return 0;
<a name="L467" href="source/net/ipv4/ipconfig.c#L467">467</a> }
<a name="L468" href="source/net/ipv4/ipconfig.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/ipconfig.c#L469">469</a> <b><i>/*</i></b>
<a name="L470" href="source/net/ipv4/ipconfig.c#L470">470</a> <b><i> *      RARP support.</i></b>
<a name="L471" href="source/net/ipv4/ipconfig.c#L471">471</a> <b><i> */</i></b>
<a name="L472" href="source/net/ipv4/ipconfig.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/ipconfig.c#L473">473</a> #ifdef <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
<a name="L474" href="source/net/ipv4/ipconfig.c#L474">474</a> 
<a name="L475" href="source/net/ipv4/ipconfig.c#L475">475</a> static int <a href="ident?i=ic_rarp_recv">ic_rarp_recv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=packet_type">packet_type</a> *<a href="ident?i=pt">pt</a>, struct <a href="ident?i=net_device">net_device</a> *orig_dev);
<a name="L476" href="source/net/ipv4/ipconfig.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/ipconfig.c#L477">477</a> static struct <a href="ident?i=packet_type">packet_type</a> rarp_packet_type <a href="ident?i=__initdata">__initdata</a> = {
<a name="L478" href="source/net/ipv4/ipconfig.c#L478">478</a>         .<a href="ident?i=type">type</a> = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=ETH_P_RARP">ETH_P_RARP</a>),
<a name="L479" href="source/net/ipv4/ipconfig.c#L479">479</a>         .<a href="ident?i=func">func</a> = <a href="ident?i=ic_rarp_recv">ic_rarp_recv</a>,
<a name="L480" href="source/net/ipv4/ipconfig.c#L480">480</a> };
<a name="L481" href="source/net/ipv4/ipconfig.c#L481">481</a> 
<a name="L482" href="source/net/ipv4/ipconfig.c#L482">482</a> static inline void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_rarp_init">ic_rarp_init</a>(void)
<a name="L483" href="source/net/ipv4/ipconfig.c#L483">483</a> {
<a name="L484" href="source/net/ipv4/ipconfig.c#L484">484</a>         <a href="ident?i=dev_add_pack">dev_add_pack</a>(&amp;rarp_packet_type);
<a name="L485" href="source/net/ipv4/ipconfig.c#L485">485</a> }
<a name="L486" href="source/net/ipv4/ipconfig.c#L486">486</a> 
<a name="L487" href="source/net/ipv4/ipconfig.c#L487">487</a> static inline void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_rarp_cleanup">ic_rarp_cleanup</a>(void)
<a name="L488" href="source/net/ipv4/ipconfig.c#L488">488</a> {
<a name="L489" href="source/net/ipv4/ipconfig.c#L489">489</a>         <a href="ident?i=dev_remove_pack">dev_remove_pack</a>(&amp;rarp_packet_type);
<a name="L490" href="source/net/ipv4/ipconfig.c#L490">490</a> }
<a name="L491" href="source/net/ipv4/ipconfig.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/ipconfig.c#L492">492</a> <b><i>/*</i></b>
<a name="L493" href="source/net/ipv4/ipconfig.c#L493">493</a> <b><i> *  Process received RARP packet.</i></b>
<a name="L494" href="source/net/ipv4/ipconfig.c#L494">494</a> <b><i> */</i></b>
<a name="L495" href="source/net/ipv4/ipconfig.c#L495">495</a> static int <a href="ident?i=__init">__init</a>
<a name="L496" href="source/net/ipv4/ipconfig.c#L496">496</a> <a href="ident?i=ic_rarp_recv">ic_rarp_recv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=packet_type">packet_type</a> *<a href="ident?i=pt">pt</a>, struct <a href="ident?i=net_device">net_device</a> *orig_dev)
<a name="L497" href="source/net/ipv4/ipconfig.c#L497">497</a> {
<a name="L498" href="source/net/ipv4/ipconfig.c#L498">498</a>         struct <a href="ident?i=arphdr">arphdr</a> *rarp;
<a name="L499" href="source/net/ipv4/ipconfig.c#L499">499</a>         unsigned char *rarp_ptr;
<a name="L500" href="source/net/ipv4/ipconfig.c#L500">500</a>         <a href="ident?i=__be32">__be32</a> sip, tip;
<a name="L501" href="source/net/ipv4/ipconfig.c#L501">501</a>         unsigned char *tha;             <b><i>/* t for "target" */</i></b>
<a name="L502" href="source/net/ipv4/ipconfig.c#L502">502</a>         struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>;
<a name="L503" href="source/net/ipv4/ipconfig.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/ipconfig.c#L504">504</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L505" href="source/net/ipv4/ipconfig.c#L505">505</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L506" href="source/net/ipv4/ipconfig.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/ipconfig.c#L507">507</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_share_check">skb_share_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L508" href="source/net/ipv4/ipconfig.c#L508">508</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L509" href="source/net/ipv4/ipconfig.c#L509">509</a>                 return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L510" href="source/net/ipv4/ipconfig.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/ipconfig.c#L511">511</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=arphdr">arphdr</a>)))
<a name="L512" href="source/net/ipv4/ipconfig.c#L512">512</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L513" href="source/net/ipv4/ipconfig.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/ipconfig.c#L514">514</a>         <b><i>/* Basic sanity checks can be done without the lock.  */</i></b>
<a name="L515" href="source/net/ipv4/ipconfig.c#L515">515</a>         rarp = (struct <a href="ident?i=arphdr">arphdr</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L516" href="source/net/ipv4/ipconfig.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/ipconfig.c#L517">517</a>         <b><i>/* If this test doesn't pass, it's not IP, or we should</i></b>
<a name="L518" href="source/net/ipv4/ipconfig.c#L518">518</a> <b><i>         * ignore it anyway.</i></b>
<a name="L519" href="source/net/ipv4/ipconfig.c#L519">519</a> <b><i>         */</i></b>
<a name="L520" href="source/net/ipv4/ipconfig.c#L520">520</a>         if (rarp-&gt;ar_hln != <a href="ident?i=dev">dev</a>-&gt;addr_len || <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ntohs">ntohs</a>(rarp-&gt;ar_hrd))
<a name="L521" href="source/net/ipv4/ipconfig.c#L521">521</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L522" href="source/net/ipv4/ipconfig.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/ipconfig.c#L523">523</a>         <b><i>/* If it's not a RARP reply, delete it. */</i></b>
<a name="L524" href="source/net/ipv4/ipconfig.c#L524">524</a>         if (rarp-&gt;ar_op != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_RREPLY">ARPOP_RREPLY</a>))
<a name="L525" href="source/net/ipv4/ipconfig.c#L525">525</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L526" href="source/net/ipv4/ipconfig.c#L526">526</a> 
<a name="L527" href="source/net/ipv4/ipconfig.c#L527">527</a>         <b><i>/* If it's not Ethernet, delete it. */</i></b>
<a name="L528" href="source/net/ipv4/ipconfig.c#L528">528</a>         if (rarp-&gt;ar_pro != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L529" href="source/net/ipv4/ipconfig.c#L529">529</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L530" href="source/net/ipv4/ipconfig.c#L530">530</a> 
<a name="L531" href="source/net/ipv4/ipconfig.c#L531">531</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=arp_hdr_len">arp_hdr_len</a>(<a href="ident?i=dev">dev</a>)))
<a name="L532" href="source/net/ipv4/ipconfig.c#L532">532</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L533" href="source/net/ipv4/ipconfig.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/ipconfig.c#L534">534</a>         <b><i>/* OK, it is all there and looks valid, process... */</i></b>
<a name="L535" href="source/net/ipv4/ipconfig.c#L535">535</a>         rarp = (struct <a href="ident?i=arphdr">arphdr</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L536" href="source/net/ipv4/ipconfig.c#L536">536</a>         rarp_ptr = (unsigned char *) (rarp + 1);
<a name="L537" href="source/net/ipv4/ipconfig.c#L537">537</a> 
<a name="L538" href="source/net/ipv4/ipconfig.c#L538">538</a>         <b><i>/* One reply at a time, please. */</i></b>
<a name="L539" href="source/net/ipv4/ipconfig.c#L539">539</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;ic_recv_lock);
<a name="L540" href="source/net/ipv4/ipconfig.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/ipconfig.c#L541">541</a>         <b><i>/* If we already have a reply, just drop the packet */</i></b>
<a name="L542" href="source/net/ipv4/ipconfig.c#L542">542</a>         if (ic_got_reply)
<a name="L543" href="source/net/ipv4/ipconfig.c#L543">543</a>                 goto drop_unlock;
<a name="L544" href="source/net/ipv4/ipconfig.c#L544">544</a> 
<a name="L545" href="source/net/ipv4/ipconfig.c#L545">545</a>         <b><i>/* Find the ic_device that the packet arrived on */</i></b>
<a name="L546" href="source/net/ipv4/ipconfig.c#L546">546</a>         <a href="ident?i=d">d</a> = ic_first_dev;
<a name="L547" href="source/net/ipv4/ipconfig.c#L547">547</a>         while (<a href="ident?i=d">d</a> &amp;&amp; <a href="ident?i=d">d</a>-&gt;<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>)
<a name="L548" href="source/net/ipv4/ipconfig.c#L548">548</a>                 <a href="ident?i=d">d</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L549" href="source/net/ipv4/ipconfig.c#L549">549</a>         if (!<a href="ident?i=d">d</a>)
<a name="L550" href="source/net/ipv4/ipconfig.c#L550">550</a>                 goto drop_unlock;       <b><i>/* should never happen */</i></b>
<a name="L551" href="source/net/ipv4/ipconfig.c#L551">551</a> 
<a name="L552" href="source/net/ipv4/ipconfig.c#L552">552</a>         <b><i>/* Extract variable-width fields */</i></b>
<a name="L553" href="source/net/ipv4/ipconfig.c#L553">553</a>         rarp_ptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L554" href="source/net/ipv4/ipconfig.c#L554">554</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;sip, rarp_ptr, 4);
<a name="L555" href="source/net/ipv4/ipconfig.c#L555">555</a>         rarp_ptr += 4;
<a name="L556" href="source/net/ipv4/ipconfig.c#L556">556</a>         tha = rarp_ptr;
<a name="L557" href="source/net/ipv4/ipconfig.c#L557">557</a>         rarp_ptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L558" href="source/net/ipv4/ipconfig.c#L558">558</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;tip, rarp_ptr, 4);
<a name="L559" href="source/net/ipv4/ipconfig.c#L559">559</a> 
<a name="L560" href="source/net/ipv4/ipconfig.c#L560">560</a>         <b><i>/* Discard packets which are not meant for us. */</i></b>
<a name="L561" href="source/net/ipv4/ipconfig.c#L561">561</a>         if (<a href="ident?i=memcmp">memcmp</a>(tha, <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=dev">dev</a>-&gt;addr_len))
<a name="L562" href="source/net/ipv4/ipconfig.c#L562">562</a>                 goto drop_unlock;
<a name="L563" href="source/net/ipv4/ipconfig.c#L563">563</a> 
<a name="L564" href="source/net/ipv4/ipconfig.c#L564">564</a>         <b><i>/* Discard packets which are not from specified server. */</i></b>
<a name="L565" href="source/net/ipv4/ipconfig.c#L565">565</a>         if (<a href="ident?i=ic_servaddr">ic_servaddr</a> != <a href="ident?i=NONE">NONE</a> &amp;&amp; <a href="ident?i=ic_servaddr">ic_servaddr</a> != sip)
<a name="L566" href="source/net/ipv4/ipconfig.c#L566">566</a>                 goto drop_unlock;
<a name="L567" href="source/net/ipv4/ipconfig.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/ipconfig.c#L568">568</a>         <b><i>/* We have a winner! */</i></b>
<a name="L569" href="source/net/ipv4/ipconfig.c#L569">569</a>         ic_dev = <a href="ident?i=dev">dev</a>;
<a name="L570" href="source/net/ipv4/ipconfig.c#L570">570</a>         if (<a href="ident?i=ic_myaddr">ic_myaddr</a> == <a href="ident?i=NONE">NONE</a>)
<a name="L571" href="source/net/ipv4/ipconfig.c#L571">571</a>                 <a href="ident?i=ic_myaddr">ic_myaddr</a> = tip;
<a name="L572" href="source/net/ipv4/ipconfig.c#L572">572</a>         <a href="ident?i=ic_servaddr">ic_servaddr</a> = sip;
<a name="L573" href="source/net/ipv4/ipconfig.c#L573">573</a>         <a href="ident?i=ic_addrservaddr">ic_addrservaddr</a> = sip;
<a name="L574" href="source/net/ipv4/ipconfig.c#L574">574</a>         ic_got_reply = <a href="ident?i=IC_RARP">IC_RARP</a>;
<a name="L575" href="source/net/ipv4/ipconfig.c#L575">575</a> 
<a name="L576" href="source/net/ipv4/ipconfig.c#L576">576</a> drop_unlock:
<a name="L577" href="source/net/ipv4/ipconfig.c#L577">577</a>         <b><i>/* Show's over.  Nothing to see here.  */</i></b>
<a name="L578" href="source/net/ipv4/ipconfig.c#L578">578</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;ic_recv_lock);
<a name="L579" href="source/net/ipv4/ipconfig.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/ipconfig.c#L580">580</a> <a href="ident?i=drop">drop</a>:
<a name="L581" href="source/net/ipv4/ipconfig.c#L581">581</a>         <b><i>/* Throw the packet out. */</i></b>
<a name="L582" href="source/net/ipv4/ipconfig.c#L582">582</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L583" href="source/net/ipv4/ipconfig.c#L583">583</a>         return 0;
<a name="L584" href="source/net/ipv4/ipconfig.c#L584">584</a> }
<a name="L585" href="source/net/ipv4/ipconfig.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/ipconfig.c#L586">586</a> 
<a name="L587" href="source/net/ipv4/ipconfig.c#L587">587</a> <b><i>/*</i></b>
<a name="L588" href="source/net/ipv4/ipconfig.c#L588">588</a> <b><i> *  Send RARP request packet over a single interface.</i></b>
<a name="L589" href="source/net/ipv4/ipconfig.c#L589">589</a> <b><i> */</i></b>
<a name="L590" href="source/net/ipv4/ipconfig.c#L590">590</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_rarp_send_if">ic_rarp_send_if</a>(struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>)
<a name="L591" href="source/net/ipv4/ipconfig.c#L591">591</a> {
<a name="L592" href="source/net/ipv4/ipconfig.c#L592">592</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L593" href="source/net/ipv4/ipconfig.c#L593">593</a>         <a href="ident?i=arp_send">arp_send</a>(<a href="ident?i=ARPOP_RREQUEST">ARPOP_RREQUEST</a>, <a href="ident?i=ETH_P_RARP">ETH_P_RARP</a>, 0, <a href="ident?i=dev">dev</a>, 0, <a href="ident?i=NULL">NULL</a>,
<a name="L594" href="source/net/ipv4/ipconfig.c#L594">594</a>                  <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=dev">dev</a>-&gt;dev_addr);
<a name="L595" href="source/net/ipv4/ipconfig.c#L595">595</a> }
<a name="L596" href="source/net/ipv4/ipconfig.c#L596">596</a> #endif
<a name="L597" href="source/net/ipv4/ipconfig.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/ipconfig.c#L598">598</a> <b><i>/*</i></b>
<a name="L599" href="source/net/ipv4/ipconfig.c#L599">599</a> <b><i> *  Predefine Nameservers</i></b>
<a name="L600" href="source/net/ipv4/ipconfig.c#L600">600</a> <b><i> */</i></b>
<a name="L601" href="source/net/ipv4/ipconfig.c#L601">601</a> static inline void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_nameservers_predef">ic_nameservers_predef</a>(void)
<a name="L602" href="source/net/ipv4/ipconfig.c#L602">602</a> {
<a name="L603" href="source/net/ipv4/ipconfig.c#L603">603</a>         int <a href="ident?i=i">i</a>;
<a name="L604" href="source/net/ipv4/ipconfig.c#L604">604</a> 
<a name="L605" href="source/net/ipv4/ipconfig.c#L605">605</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>; <a href="ident?i=i">i</a>++)
<a name="L606" href="source/net/ipv4/ipconfig.c#L606">606</a>                 <a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>] = <a href="ident?i=NONE">NONE</a>;
<a name="L607" href="source/net/ipv4/ipconfig.c#L607">607</a> }
<a name="L608" href="source/net/ipv4/ipconfig.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/ipconfig.c#L609">609</a> <b><i>/*</i></b>
<a name="L610" href="source/net/ipv4/ipconfig.c#L610">610</a> <b><i> *      DHCP/BOOTP support.</i></b>
<a name="L611" href="source/net/ipv4/ipconfig.c#L611">611</a> <b><i> */</i></b>
<a name="L612" href="source/net/ipv4/ipconfig.c#L612">612</a> 
<a name="L613" href="source/net/ipv4/ipconfig.c#L613">613</a> #ifdef <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
<a name="L614" href="source/net/ipv4/ipconfig.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/ipconfig.c#L615">615</a> struct <a href="ident?i=bootp_pkt">bootp_pkt</a> {              <b><i>/* BOOTP packet format */</i></b>
<a name="L616" href="source/net/ipv4/ipconfig.c#L616">616</a>         struct <a href="ident?i=iphdr">iphdr</a> iph;       <b><i>/* IP header */</i></b>
<a name="L617" href="source/net/ipv4/ipconfig.c#L617">617</a>         struct <a href="ident?i=udphdr">udphdr</a> udph;     <b><i>/* UDP header */</i></b>
<a name="L618" href="source/net/ipv4/ipconfig.c#L618">618</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=op">op</a>;                  <b><i>/* 1=request, 2=reply */</i></b>
<a name="L619" href="source/net/ipv4/ipconfig.c#L619">619</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=htype">htype</a>;               <b><i>/* HW address type */</i></b>
<a name="L620" href="source/net/ipv4/ipconfig.c#L620">620</a>         <a href="ident?i=u8">u8</a> hlen;                <b><i>/* HW address length */</i></b>
<a name="L621" href="source/net/ipv4/ipconfig.c#L621">621</a>         <a href="ident?i=u8">u8</a> hops;                <b><i>/* Used only by gateways */</i></b>
<a name="L622" href="source/net/ipv4/ipconfig.c#L622">622</a>         <a href="ident?i=__be32">__be32</a> xid;             <b><i>/* Transaction ID */</i></b>
<a name="L623" href="source/net/ipv4/ipconfig.c#L623">623</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=secs">secs</a>;            <b><i>/* Seconds since we started */</i></b>
<a name="L624" href="source/net/ipv4/ipconfig.c#L624">624</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=flags">flags</a>;           <b><i>/* Just what it says */</i></b>
<a name="L625" href="source/net/ipv4/ipconfig.c#L625">625</a>         <a href="ident?i=__be32">__be32</a> client_ip;               <b><i>/* Client's IP address if known */</i></b>
<a name="L626" href="source/net/ipv4/ipconfig.c#L626">626</a>         <a href="ident?i=__be32">__be32</a> your_ip;         <b><i>/* Assigned IP address */</i></b>
<a name="L627" href="source/net/ipv4/ipconfig.c#L627">627</a>         <a href="ident?i=__be32">__be32</a> server_ip;               <b><i>/* (Next, e.g. NFS) Server's IP address */</i></b>
<a name="L628" href="source/net/ipv4/ipconfig.c#L628">628</a>         <a href="ident?i=__be32">__be32</a> relay_ip;                <b><i>/* IP address of BOOTP relay */</i></b>
<a name="L629" href="source/net/ipv4/ipconfig.c#L629">629</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=hw_addr">hw_addr</a>[16];         <b><i>/* Client's HW address */</i></b>
<a name="L630" href="source/net/ipv4/ipconfig.c#L630">630</a>         <a href="ident?i=u8">u8</a> serv_name[64];       <b><i>/* Server host name */</i></b>
<a name="L631" href="source/net/ipv4/ipconfig.c#L631">631</a>         <a href="ident?i=u8">u8</a> boot_file[128];      <b><i>/* Name of boot file */</i></b>
<a name="L632" href="source/net/ipv4/ipconfig.c#L632">632</a>         <a href="ident?i=u8">u8</a> exten[312];          <b><i>/* DHCP options / BOOTP vendor extensions */</i></b>
<a name="L633" href="source/net/ipv4/ipconfig.c#L633">633</a> };
<a name="L634" href="source/net/ipv4/ipconfig.c#L634">634</a> 
<a name="L635" href="source/net/ipv4/ipconfig.c#L635">635</a> <b><i>/* packet ops */</i></b>
<a name="L636" href="source/net/ipv4/ipconfig.c#L636">636</a> #define <a href="ident?i=BOOTP_REQUEST">BOOTP_REQUEST</a>   1
<a name="L637" href="source/net/ipv4/ipconfig.c#L637">637</a> #define <a href="ident?i=BOOTP_REPLY">BOOTP_REPLY</a>     2
<a name="L638" href="source/net/ipv4/ipconfig.c#L638">638</a> 
<a name="L639" href="source/net/ipv4/ipconfig.c#L639">639</a> <b><i>/* DHCP message types */</i></b>
<a name="L640" href="source/net/ipv4/ipconfig.c#L640">640</a> #define <a href="ident?i=DHCPDISCOVER">DHCPDISCOVER</a>    1
<a name="L641" href="source/net/ipv4/ipconfig.c#L641">641</a> #define <a href="ident?i=DHCPOFFER">DHCPOFFER</a>       2
<a name="L642" href="source/net/ipv4/ipconfig.c#L642">642</a> #define <a href="ident?i=DHCPREQUEST">DHCPREQUEST</a>     3
<a name="L643" href="source/net/ipv4/ipconfig.c#L643">643</a> #define <a href="ident?i=DHCPDECLINE">DHCPDECLINE</a>     4
<a name="L644" href="source/net/ipv4/ipconfig.c#L644">644</a> #define <a href="ident?i=DHCPACK">DHCPACK</a>         5
<a name="L645" href="source/net/ipv4/ipconfig.c#L645">645</a> #define <a href="ident?i=DHCPNAK">DHCPNAK</a>         6
<a name="L646" href="source/net/ipv4/ipconfig.c#L646">646</a> #define <a href="ident?i=DHCPRELEASE">DHCPRELEASE</a>     7
<a name="L647" href="source/net/ipv4/ipconfig.c#L647">647</a> #define <a href="ident?i=DHCPINFORM">DHCPINFORM</a>      8
<a name="L648" href="source/net/ipv4/ipconfig.c#L648">648</a> 
<a name="L649" href="source/net/ipv4/ipconfig.c#L649">649</a> static int <a href="ident?i=ic_bootp_recv">ic_bootp_recv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=packet_type">packet_type</a> *<a href="ident?i=pt">pt</a>, struct <a href="ident?i=net_device">net_device</a> *orig_dev);
<a name="L650" href="source/net/ipv4/ipconfig.c#L650">650</a> 
<a name="L651" href="source/net/ipv4/ipconfig.c#L651">651</a> static struct <a href="ident?i=packet_type">packet_type</a> bootp_packet_type <a href="ident?i=__initdata">__initdata</a> = {
<a name="L652" href="source/net/ipv4/ipconfig.c#L652">652</a>         .<a href="ident?i=type">type</a> = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>),
<a name="L653" href="source/net/ipv4/ipconfig.c#L653">653</a>         .<a href="ident?i=func">func</a> = <a href="ident?i=ic_bootp_recv">ic_bootp_recv</a>,
<a name="L654" href="source/net/ipv4/ipconfig.c#L654">654</a> };
<a name="L655" href="source/net/ipv4/ipconfig.c#L655">655</a> 
<a name="L656" href="source/net/ipv4/ipconfig.c#L656">656</a> static <a href="ident?i=__be32">__be32</a> <a href="ident?i=ic_dev_xid">ic_dev_xid</a>;               <b><i>/* Device under configuration */</i></b>
<a name="L657" href="source/net/ipv4/ipconfig.c#L657">657</a> 
<a name="L658" href="source/net/ipv4/ipconfig.c#L658">658</a> <b><i>/*</i></b>
<a name="L659" href="source/net/ipv4/ipconfig.c#L659">659</a> <b><i> *  Initialize DHCP/BOOTP extension fields in the request.</i></b>
<a name="L660" href="source/net/ipv4/ipconfig.c#L660">660</a> <b><i> */</i></b>
<a name="L661" href="source/net/ipv4/ipconfig.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/ipconfig.c#L662">662</a> static const <a href="ident?i=u8">u8</a> <a href="ident?i=ic_bootp_cookie">ic_bootp_cookie</a>[4] = { 99, 130, 83, 99 };
<a name="L663" href="source/net/ipv4/ipconfig.c#L663">663</a> 
<a name="L664" href="source/net/ipv4/ipconfig.c#L664">664</a> #ifdef <a href="ident?i=IPCONFIG_DHCP">IPCONFIG_DHCP</a>
<a name="L665" href="source/net/ipv4/ipconfig.c#L665">665</a> 
<a name="L666" href="source/net/ipv4/ipconfig.c#L666">666</a> static void <a href="ident?i=__init">__init</a>
<a name="L667" href="source/net/ipv4/ipconfig.c#L667">667</a> <a href="ident?i=ic_dhcp_init_options">ic_dhcp_init_options</a>(<a href="ident?i=u8">u8</a> *<a href="ident?i=options">options</a>)
<a name="L668" href="source/net/ipv4/ipconfig.c#L668">668</a> {
<a name="L669" href="source/net/ipv4/ipconfig.c#L669">669</a>         <a href="ident?i=u8">u8</a> mt = ((<a href="ident?i=ic_servaddr">ic_servaddr</a> == <a href="ident?i=NONE">NONE</a>)
<a name="L670" href="source/net/ipv4/ipconfig.c#L670">670</a>                  ? <a href="ident?i=DHCPDISCOVER">DHCPDISCOVER</a> : <a href="ident?i=DHCPREQUEST">DHCPREQUEST</a>);
<a name="L671" href="source/net/ipv4/ipconfig.c#L671">671</a>         <a href="ident?i=u8">u8</a> *<a href="ident?i=e">e</a> = <a href="ident?i=options">options</a>;
<a name="L672" href="source/net/ipv4/ipconfig.c#L672">672</a>         int <a href="ident?i=len">len</a>;
<a name="L673" href="source/net/ipv4/ipconfig.c#L673">673</a> 
<a name="L674" href="source/net/ipv4/ipconfig.c#L674">674</a> #ifdef <a href="ident?i=IPCONFIG_DEBUG">IPCONFIG_DEBUG</a>
<a name="L675" href="source/net/ipv4/ipconfig.c#L675">675</a>         <a href="ident?i=printk">printk</a>(<i>"DHCP: Sending message type %d\n"</i>, mt);
<a name="L676" href="source/net/ipv4/ipconfig.c#L676">676</a> #endif
<a name="L677" href="source/net/ipv4/ipconfig.c#L677">677</a> 
<a name="L678" href="source/net/ipv4/ipconfig.c#L678">678</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, <a href="ident?i=ic_bootp_cookie">ic_bootp_cookie</a>, 4);  <b><i>/* RFC1048 Magic Cookie */</i></b>
<a name="L679" href="source/net/ipv4/ipconfig.c#L679">679</a>         <a href="ident?i=e">e</a> += 4;
<a name="L680" href="source/net/ipv4/ipconfig.c#L680">680</a> 
<a name="L681" href="source/net/ipv4/ipconfig.c#L681">681</a>         *<a href="ident?i=e">e</a>++ = 53;              <b><i>/* DHCP message type */</i></b>
<a name="L682" href="source/net/ipv4/ipconfig.c#L682">682</a>         *<a href="ident?i=e">e</a>++ = 1;
<a name="L683" href="source/net/ipv4/ipconfig.c#L683">683</a>         *<a href="ident?i=e">e</a>++ = mt;
<a name="L684" href="source/net/ipv4/ipconfig.c#L684">684</a> 
<a name="L685" href="source/net/ipv4/ipconfig.c#L685">685</a>         if (mt == <a href="ident?i=DHCPREQUEST">DHCPREQUEST</a>) {
<a name="L686" href="source/net/ipv4/ipconfig.c#L686">686</a>                 *<a href="ident?i=e">e</a>++ = 54;      <b><i>/* Server ID (IP address) */</i></b>
<a name="L687" href="source/net/ipv4/ipconfig.c#L687">687</a>                 *<a href="ident?i=e">e</a>++ = 4;
<a name="L688" href="source/net/ipv4/ipconfig.c#L688">688</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, &amp;<a href="ident?i=ic_servaddr">ic_servaddr</a>, 4);
<a name="L689" href="source/net/ipv4/ipconfig.c#L689">689</a>                 <a href="ident?i=e">e</a> += 4;
<a name="L690" href="source/net/ipv4/ipconfig.c#L690">690</a> 
<a name="L691" href="source/net/ipv4/ipconfig.c#L691">691</a>                 *<a href="ident?i=e">e</a>++ = 50;      <b><i>/* Requested IP address */</i></b>
<a name="L692" href="source/net/ipv4/ipconfig.c#L692">692</a>                 *<a href="ident?i=e">e</a>++ = 4;
<a name="L693" href="source/net/ipv4/ipconfig.c#L693">693</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, &amp;<a href="ident?i=ic_myaddr">ic_myaddr</a>, 4);
<a name="L694" href="source/net/ipv4/ipconfig.c#L694">694</a>                 <a href="ident?i=e">e</a> += 4;
<a name="L695" href="source/net/ipv4/ipconfig.c#L695">695</a>         }
<a name="L696" href="source/net/ipv4/ipconfig.c#L696">696</a> 
<a name="L697" href="source/net/ipv4/ipconfig.c#L697">697</a>         <b><i>/* always? */</i></b>
<a name="L698" href="source/net/ipv4/ipconfig.c#L698">698</a>         {
<a name="L699" href="source/net/ipv4/ipconfig.c#L699">699</a>                 static const <a href="ident?i=u8">u8</a> ic_req_params[] = {
<a name="L700" href="source/net/ipv4/ipconfig.c#L700">700</a>                         1,      <b><i>/* Subnet mask */</i></b>
<a name="L701" href="source/net/ipv4/ipconfig.c#L701">701</a>                         3,      <b><i>/* Default gateway */</i></b>
<a name="L702" href="source/net/ipv4/ipconfig.c#L702">702</a>                         6,      <b><i>/* DNS server */</i></b>
<a name="L703" href="source/net/ipv4/ipconfig.c#L703">703</a>                         12,     <b><i>/* Host name */</i></b>
<a name="L704" href="source/net/ipv4/ipconfig.c#L704">704</a>                         15,     <b><i>/* Domain name */</i></b>
<a name="L705" href="source/net/ipv4/ipconfig.c#L705">705</a>                         17,     <b><i>/* Boot path */</i></b>
<a name="L706" href="source/net/ipv4/ipconfig.c#L706">706</a>                         26,     <b><i>/* MTU */</i></b>
<a name="L707" href="source/net/ipv4/ipconfig.c#L707">707</a>                         40,     <b><i>/* NIS domain name */</i></b>
<a name="L708" href="source/net/ipv4/ipconfig.c#L708">708</a>                 };
<a name="L709" href="source/net/ipv4/ipconfig.c#L709">709</a> 
<a name="L710" href="source/net/ipv4/ipconfig.c#L710">710</a>                 *<a href="ident?i=e">e</a>++ = 55;      <b><i>/* Parameter request list */</i></b>
<a name="L711" href="source/net/ipv4/ipconfig.c#L711">711</a>                 *<a href="ident?i=e">e</a>++ = sizeof(ic_req_params);
<a name="L712" href="source/net/ipv4/ipconfig.c#L712">712</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, ic_req_params, sizeof(ic_req_params));
<a name="L713" href="source/net/ipv4/ipconfig.c#L713">713</a>                 <a href="ident?i=e">e</a> += sizeof(ic_req_params);
<a name="L714" href="source/net/ipv4/ipconfig.c#L714">714</a> 
<a name="L715" href="source/net/ipv4/ipconfig.c#L715">715</a>                 if (ic_host_name_set) {
<a name="L716" href="source/net/ipv4/ipconfig.c#L716">716</a>                         *<a href="ident?i=e">e</a>++ = 12;      <b><i>/* host-name */</i></b>
<a name="L717" href="source/net/ipv4/ipconfig.c#L717">717</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=strlen">strlen</a>(<a href="ident?i=utsname">utsname</a>()-&gt;nodename);
<a name="L718" href="source/net/ipv4/ipconfig.c#L718">718</a>                         *<a href="ident?i=e">e</a>++ = <a href="ident?i=len">len</a>;
<a name="L719" href="source/net/ipv4/ipconfig.c#L719">719</a>                         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, <a href="ident?i=utsname">utsname</a>()-&gt;nodename, <a href="ident?i=len">len</a>);
<a name="L720" href="source/net/ipv4/ipconfig.c#L720">720</a>                         <a href="ident?i=e">e</a> += <a href="ident?i=len">len</a>;
<a name="L721" href="source/net/ipv4/ipconfig.c#L721">721</a>                 }
<a name="L722" href="source/net/ipv4/ipconfig.c#L722">722</a>                 if (*vendor_class_identifier) {
<a name="L723" href="source/net/ipv4/ipconfig.c#L723">723</a>                         <a href="ident?i=pr_info">pr_info</a>(<i>"DHCP: sending class identifier \"%s\"\n"</i>,
<a name="L724" href="source/net/ipv4/ipconfig.c#L724">724</a>                                 vendor_class_identifier);
<a name="L725" href="source/net/ipv4/ipconfig.c#L725">725</a>                         *<a href="ident?i=e">e</a>++ = 60;      <b><i>/* Class-identifier */</i></b>
<a name="L726" href="source/net/ipv4/ipconfig.c#L726">726</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=strlen">strlen</a>(vendor_class_identifier);
<a name="L727" href="source/net/ipv4/ipconfig.c#L727">727</a>                         *<a href="ident?i=e">e</a>++ = <a href="ident?i=len">len</a>;
<a name="L728" href="source/net/ipv4/ipconfig.c#L728">728</a>                         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, vendor_class_identifier, <a href="ident?i=len">len</a>);
<a name="L729" href="source/net/ipv4/ipconfig.c#L729">729</a>                         <a href="ident?i=e">e</a> += <a href="ident?i=len">len</a>;
<a name="L730" href="source/net/ipv4/ipconfig.c#L730">730</a>                 }
<a name="L731" href="source/net/ipv4/ipconfig.c#L731">731</a>         }
<a name="L732" href="source/net/ipv4/ipconfig.c#L732">732</a> 
<a name="L733" href="source/net/ipv4/ipconfig.c#L733">733</a>         *<a href="ident?i=e">e</a>++ = 255;     <b><i>/* End of the list */</i></b>
<a name="L734" href="source/net/ipv4/ipconfig.c#L734">734</a> }
<a name="L735" href="source/net/ipv4/ipconfig.c#L735">735</a> 
<a name="L736" href="source/net/ipv4/ipconfig.c#L736">736</a> #endif <b><i>/* IPCONFIG_DHCP */</i></b>
<a name="L737" href="source/net/ipv4/ipconfig.c#L737">737</a> 
<a name="L738" href="source/net/ipv4/ipconfig.c#L738">738</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_bootp_init_ext">ic_bootp_init_ext</a>(<a href="ident?i=u8">u8</a> *<a href="ident?i=e">e</a>)
<a name="L739" href="source/net/ipv4/ipconfig.c#L739">739</a> {
<a name="L740" href="source/net/ipv4/ipconfig.c#L740">740</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=e">e</a>, <a href="ident?i=ic_bootp_cookie">ic_bootp_cookie</a>, 4);  <b><i>/* RFC1048 Magic Cookie */</i></b>
<a name="L741" href="source/net/ipv4/ipconfig.c#L741">741</a>         <a href="ident?i=e">e</a> += 4;
<a name="L742" href="source/net/ipv4/ipconfig.c#L742">742</a>         *<a href="ident?i=e">e</a>++ = 1;               <b><i>/* Subnet mask request */</i></b>
<a name="L743" href="source/net/ipv4/ipconfig.c#L743">743</a>         *<a href="ident?i=e">e</a>++ = 4;
<a name="L744" href="source/net/ipv4/ipconfig.c#L744">744</a>         <a href="ident?i=e">e</a> += 4;
<a name="L745" href="source/net/ipv4/ipconfig.c#L745">745</a>         *<a href="ident?i=e">e</a>++ = 3;               <b><i>/* Default gateway request */</i></b>
<a name="L746" href="source/net/ipv4/ipconfig.c#L746">746</a>         *<a href="ident?i=e">e</a>++ = 4;
<a name="L747" href="source/net/ipv4/ipconfig.c#L747">747</a>         <a href="ident?i=e">e</a> += 4;
<a name="L748" href="source/net/ipv4/ipconfig.c#L748">748</a>         *<a href="ident?i=e">e</a>++ = 5;               <b><i>/* Name server request */</i></b>
<a name="L749" href="source/net/ipv4/ipconfig.c#L749">749</a>         *<a href="ident?i=e">e</a>++ = 8;
<a name="L750" href="source/net/ipv4/ipconfig.c#L750">750</a>         <a href="ident?i=e">e</a> += 8;
<a name="L751" href="source/net/ipv4/ipconfig.c#L751">751</a>         *<a href="ident?i=e">e</a>++ = 12;              <b><i>/* Host name request */</i></b>
<a name="L752" href="source/net/ipv4/ipconfig.c#L752">752</a>         *<a href="ident?i=e">e</a>++ = 32;
<a name="L753" href="source/net/ipv4/ipconfig.c#L753">753</a>         <a href="ident?i=e">e</a> += 32;
<a name="L754" href="source/net/ipv4/ipconfig.c#L754">754</a>         *<a href="ident?i=e">e</a>++ = 40;              <b><i>/* NIS Domain name request */</i></b>
<a name="L755" href="source/net/ipv4/ipconfig.c#L755">755</a>         *<a href="ident?i=e">e</a>++ = 32;
<a name="L756" href="source/net/ipv4/ipconfig.c#L756">756</a>         <a href="ident?i=e">e</a> += 32;
<a name="L757" href="source/net/ipv4/ipconfig.c#L757">757</a>         *<a href="ident?i=e">e</a>++ = 17;              <b><i>/* Boot path */</i></b>
<a name="L758" href="source/net/ipv4/ipconfig.c#L758">758</a>         *<a href="ident?i=e">e</a>++ = 40;
<a name="L759" href="source/net/ipv4/ipconfig.c#L759">759</a>         <a href="ident?i=e">e</a> += 40;
<a name="L760" href="source/net/ipv4/ipconfig.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/ipconfig.c#L761">761</a>         *<a href="ident?i=e">e</a>++ = 57;              <b><i>/* set extension buffer size for reply */</i></b>
<a name="L762" href="source/net/ipv4/ipconfig.c#L762">762</a>         *<a href="ident?i=e">e</a>++ = 2;
<a name="L763" href="source/net/ipv4/ipconfig.c#L763">763</a>         *<a href="ident?i=e">e</a>++ = 1;               <b><i>/* 128+236+8+20+14, see dhcpd sources */</i></b>
<a name="L764" href="source/net/ipv4/ipconfig.c#L764">764</a>         *<a href="ident?i=e">e</a>++ = 150;
<a name="L765" href="source/net/ipv4/ipconfig.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/ipconfig.c#L766">766</a>         *<a href="ident?i=e">e</a>++ = 255;             <b><i>/* End of the list */</i></b>
<a name="L767" href="source/net/ipv4/ipconfig.c#L767">767</a> }
<a name="L768" href="source/net/ipv4/ipconfig.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/ipconfig.c#L769">769</a> 
<a name="L770" href="source/net/ipv4/ipconfig.c#L770">770</a> <b><i>/*</i></b>
<a name="L771" href="source/net/ipv4/ipconfig.c#L771">771</a> <b><i> *  Initialize the DHCP/BOOTP mechanism.</i></b>
<a name="L772" href="source/net/ipv4/ipconfig.c#L772">772</a> <b><i> */</i></b>
<a name="L773" href="source/net/ipv4/ipconfig.c#L773">773</a> static inline void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_bootp_init">ic_bootp_init</a>(void)
<a name="L774" href="source/net/ipv4/ipconfig.c#L774">774</a> {
<a name="L775" href="source/net/ipv4/ipconfig.c#L775">775</a>         <a href="ident?i=ic_nameservers_predef">ic_nameservers_predef</a>();
<a name="L776" href="source/net/ipv4/ipconfig.c#L776">776</a> 
<a name="L777" href="source/net/ipv4/ipconfig.c#L777">777</a>         <a href="ident?i=dev_add_pack">dev_add_pack</a>(&amp;bootp_packet_type);
<a name="L778" href="source/net/ipv4/ipconfig.c#L778">778</a> }
<a name="L779" href="source/net/ipv4/ipconfig.c#L779">779</a> 
<a name="L780" href="source/net/ipv4/ipconfig.c#L780">780</a> 
<a name="L781" href="source/net/ipv4/ipconfig.c#L781">781</a> <b><i>/*</i></b>
<a name="L782" href="source/net/ipv4/ipconfig.c#L782">782</a> <b><i> *  DHCP/BOOTP cleanup.</i></b>
<a name="L783" href="source/net/ipv4/ipconfig.c#L783">783</a> <b><i> */</i></b>
<a name="L784" href="source/net/ipv4/ipconfig.c#L784">784</a> static inline void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_bootp_cleanup">ic_bootp_cleanup</a>(void)
<a name="L785" href="source/net/ipv4/ipconfig.c#L785">785</a> {
<a name="L786" href="source/net/ipv4/ipconfig.c#L786">786</a>         <a href="ident?i=dev_remove_pack">dev_remove_pack</a>(&amp;bootp_packet_type);
<a name="L787" href="source/net/ipv4/ipconfig.c#L787">787</a> }
<a name="L788" href="source/net/ipv4/ipconfig.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/ipconfig.c#L789">789</a> 
<a name="L790" href="source/net/ipv4/ipconfig.c#L790">790</a> <b><i>/*</i></b>
<a name="L791" href="source/net/ipv4/ipconfig.c#L791">791</a> <b><i> *  Send DHCP/BOOTP request to single interface.</i></b>
<a name="L792" href="source/net/ipv4/ipconfig.c#L792">792</a> <b><i> */</i></b>
<a name="L793" href="source/net/ipv4/ipconfig.c#L793">793</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_bootp_send_if">ic_bootp_send_if</a>(struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>, unsigned long jiffies_diff)
<a name="L794" href="source/net/ipv4/ipconfig.c#L794">794</a> {
<a name="L795" href="source/net/ipv4/ipconfig.c#L795">795</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L796" href="source/net/ipv4/ipconfig.c#L796">796</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L797" href="source/net/ipv4/ipconfig.c#L797">797</a>         struct <a href="ident?i=bootp_pkt">bootp_pkt</a> *<a href="ident?i=b">b</a>;
<a name="L798" href="source/net/ipv4/ipconfig.c#L798">798</a>         struct <a href="ident?i=iphdr">iphdr</a> *<a href="ident?i=h">h</a>;
<a name="L799" href="source/net/ipv4/ipconfig.c#L799">799</a>         int hlen = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>);
<a name="L800" href="source/net/ipv4/ipconfig.c#L800">800</a>         int tlen = <a href="ident?i=dev">dev</a>-&gt;needed_tailroom;
<a name="L801" href="source/net/ipv4/ipconfig.c#L801">801</a> 
<a name="L802" href="source/net/ipv4/ipconfig.c#L802">802</a>         <b><i>/* Allocate packet */</i></b>
<a name="L803" href="source/net/ipv4/ipconfig.c#L803">803</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(struct <a href="ident?i=bootp_pkt">bootp_pkt</a>) + hlen + tlen + 15,
<a name="L804" href="source/net/ipv4/ipconfig.c#L804">804</a>                         <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L805" href="source/net/ipv4/ipconfig.c#L805">805</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L806" href="source/net/ipv4/ipconfig.c#L806">806</a>                 return;
<a name="L807" href="source/net/ipv4/ipconfig.c#L807">807</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hlen);
<a name="L808" href="source/net/ipv4/ipconfig.c#L808">808</a>         <a href="ident?i=b">b</a> = (struct <a href="ident?i=bootp_pkt">bootp_pkt</a> *) <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=bootp_pkt">bootp_pkt</a>));
<a name="L809" href="source/net/ipv4/ipconfig.c#L809">809</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=b">b</a>, 0, sizeof(struct <a href="ident?i=bootp_pkt">bootp_pkt</a>));
<a name="L810" href="source/net/ipv4/ipconfig.c#L810">810</a> 
<a name="L811" href="source/net/ipv4/ipconfig.c#L811">811</a>         <b><i>/* Construct IP header */</i></b>
<a name="L812" href="source/net/ipv4/ipconfig.c#L812">812</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L813" href="source/net/ipv4/ipconfig.c#L813">813</a>         <a href="ident?i=h">h</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L814" href="source/net/ipv4/ipconfig.c#L814">814</a>         <a href="ident?i=h">h</a>-&gt;<a href="ident?i=version">version</a> = 4;
<a name="L815" href="source/net/ipv4/ipconfig.c#L815">815</a>         <a href="ident?i=h">h</a>-&gt;ihl = 5;
<a name="L816" href="source/net/ipv4/ipconfig.c#L816">816</a>         <a href="ident?i=h">h</a>-&gt;tot_len = <a href="ident?i=htons">htons</a>(sizeof(struct <a href="ident?i=bootp_pkt">bootp_pkt</a>));
<a name="L817" href="source/net/ipv4/ipconfig.c#L817">817</a>         <a href="ident?i=h">h</a>-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L818" href="source/net/ipv4/ipconfig.c#L818">818</a>         <a href="ident?i=h">h</a>-&gt;<a href="ident?i=ttl">ttl</a> = 64;
<a name="L819" href="source/net/ipv4/ipconfig.c#L819">819</a>         <a href="ident?i=h">h</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>;
<a name="L820" href="source/net/ipv4/ipconfig.c#L820">820</a>         <a href="ident?i=h">h</a>-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_BROADCAST">INADDR_BROADCAST</a>);
<a name="L821" href="source/net/ipv4/ipconfig.c#L821">821</a>         <a href="ident?i=h">h</a>-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=ip_fast_csum">ip_fast_csum</a>((unsigned char *) <a href="ident?i=h">h</a>, <a href="ident?i=h">h</a>-&gt;ihl);
<a name="L822" href="source/net/ipv4/ipconfig.c#L822">822</a> 
<a name="L823" href="source/net/ipv4/ipconfig.c#L823">823</a>         <b><i>/* Construct UDP header */</i></b>
<a name="L824" href="source/net/ipv4/ipconfig.c#L824">824</a>         <a href="ident?i=b">b</a>-&gt;udph.source = <a href="ident?i=htons">htons</a>(68);
<a name="L825" href="source/net/ipv4/ipconfig.c#L825">825</a>         <a href="ident?i=b">b</a>-&gt;udph.<a href="ident?i=dest">dest</a> = <a href="ident?i=htons">htons</a>(67);
<a name="L826" href="source/net/ipv4/ipconfig.c#L826">826</a>         <a href="ident?i=b">b</a>-&gt;udph.<a href="ident?i=len">len</a> = <a href="ident?i=htons">htons</a>(sizeof(struct <a href="ident?i=bootp_pkt">bootp_pkt</a>) - sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L827" href="source/net/ipv4/ipconfig.c#L827">827</a>         <b><i>/* UDP checksum not calculated -- explicitly allowed in BOOTP RFC */</i></b>
<a name="L828" href="source/net/ipv4/ipconfig.c#L828">828</a> 
<a name="L829" href="source/net/ipv4/ipconfig.c#L829">829</a>         <b><i>/* Construct DHCP/BOOTP header */</i></b>
<a name="L830" href="source/net/ipv4/ipconfig.c#L830">830</a>         <a href="ident?i=b">b</a>-&gt;<a href="ident?i=op">op</a> = <a href="ident?i=BOOTP_REQUEST">BOOTP_REQUEST</a>;
<a name="L831" href="source/net/ipv4/ipconfig.c#L831">831</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> &lt; 256) <b><i>/* check for false types */</i></b>
<a name="L832" href="source/net/ipv4/ipconfig.c#L832">832</a>                 <a href="ident?i=b">b</a>-&gt;<a href="ident?i=htype">htype</a> = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L833" href="source/net/ipv4/ipconfig.c#L833">833</a>         else if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ARPHRD_FDDI">ARPHRD_FDDI</a>)
<a name="L834" href="source/net/ipv4/ipconfig.c#L834">834</a>                 <a href="ident?i=b">b</a>-&gt;<a href="ident?i=htype">htype</a> = <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>;
<a name="L835" href="source/net/ipv4/ipconfig.c#L835">835</a>         else {
<a name="L836" href="source/net/ipv4/ipconfig.c#L836">836</a>                 <a href="ident?i=printk">printk</a>(<i>"Unknown ARP type 0x%04x for device %s\n"</i>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L837" href="source/net/ipv4/ipconfig.c#L837">837</a>                 <a href="ident?i=b">b</a>-&gt;<a href="ident?i=htype">htype</a> = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>; <b><i>/* can cause undefined behavior */</i></b>
<a name="L838" href="source/net/ipv4/ipconfig.c#L838">838</a>         }
<a name="L839" href="source/net/ipv4/ipconfig.c#L839">839</a> 
<a name="L840" href="source/net/ipv4/ipconfig.c#L840">840</a>         <b><i>/* server_ip and your_ip address are both already zero per RFC2131 */</i></b>
<a name="L841" href="source/net/ipv4/ipconfig.c#L841">841</a>         <a href="ident?i=b">b</a>-&gt;hlen = <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L842" href="source/net/ipv4/ipconfig.c#L842">842</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=b">b</a>-&gt;<a href="ident?i=hw_addr">hw_addr</a>, <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L843" href="source/net/ipv4/ipconfig.c#L843">843</a>         <a href="ident?i=b">b</a>-&gt;<a href="ident?i=secs">secs</a> = <a href="ident?i=htons">htons</a>(jiffies_diff / <a href="ident?i=HZ">HZ</a>);
<a name="L844" href="source/net/ipv4/ipconfig.c#L844">844</a>         <a href="ident?i=b">b</a>-&gt;xid = <a href="ident?i=d">d</a>-&gt;xid;
<a name="L845" href="source/net/ipv4/ipconfig.c#L845">845</a> 
<a name="L846" href="source/net/ipv4/ipconfig.c#L846">846</a>         <b><i>/* add DHCP options or BOOTP extensions */</i></b>
<a name="L847" href="source/net/ipv4/ipconfig.c#L847">847</a> #ifdef <a href="ident?i=IPCONFIG_DHCP">IPCONFIG_DHCP</a>
<a name="L848" href="source/net/ipv4/ipconfig.c#L848">848</a>         if (<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>)
<a name="L849" href="source/net/ipv4/ipconfig.c#L849">849</a>                 <a href="ident?i=ic_dhcp_init_options">ic_dhcp_init_options</a>(<a href="ident?i=b">b</a>-&gt;exten);
<a name="L850" href="source/net/ipv4/ipconfig.c#L850">850</a>         else
<a name="L851" href="source/net/ipv4/ipconfig.c#L851">851</a> #endif
<a name="L852" href="source/net/ipv4/ipconfig.c#L852">852</a>                 <a href="ident?i=ic_bootp_init_ext">ic_bootp_init_ext</a>(<a href="ident?i=b">b</a>-&gt;exten);
<a name="L853" href="source/net/ipv4/ipconfig.c#L853">853</a> 
<a name="L854" href="source/net/ipv4/ipconfig.c#L854">854</a>         <b><i>/* Chain packet down the line... */</i></b>
<a name="L855" href="source/net/ipv4/ipconfig.c#L855">855</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L856" href="source/net/ipv4/ipconfig.c#L856">856</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L857" href="source/net/ipv4/ipconfig.c#L857">857</a>         if (<a href="ident?i=dev_hard_header">dev_hard_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>),
<a name="L858" href="source/net/ipv4/ipconfig.c#L858">858</a>                             <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) &lt; 0) {
<a name="L859" href="source/net/ipv4/ipconfig.c#L859">859</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L860" href="source/net/ipv4/ipconfig.c#L860">860</a>                 <a href="ident?i=printk">printk</a>(<i>"E"</i>);
<a name="L861" href="source/net/ipv4/ipconfig.c#L861">861</a>                 return;
<a name="L862" href="source/net/ipv4/ipconfig.c#L862">862</a>         }
<a name="L863" href="source/net/ipv4/ipconfig.c#L863">863</a> 
<a name="L864" href="source/net/ipv4/ipconfig.c#L864">864</a>         if (<a href="ident?i=dev_queue_xmit">dev_queue_xmit</a>(<a href="ident?i=skb">skb</a>) &lt; 0)
<a name="L865" href="source/net/ipv4/ipconfig.c#L865">865</a>                 <a href="ident?i=printk">printk</a>(<i>"E"</i>);
<a name="L866" href="source/net/ipv4/ipconfig.c#L866">866</a> }
<a name="L867" href="source/net/ipv4/ipconfig.c#L867">867</a> 
<a name="L868" href="source/net/ipv4/ipconfig.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/ipconfig.c#L869">869</a> <b><i>/*</i></b>
<a name="L870" href="source/net/ipv4/ipconfig.c#L870">870</a> <b><i> *  Copy BOOTP-supplied string if not already set.</i></b>
<a name="L871" href="source/net/ipv4/ipconfig.c#L871">871</a> <b><i> */</i></b>
<a name="L872" href="source/net/ipv4/ipconfig.c#L872">872</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_bootp_string">ic_bootp_string</a>(char *<a href="ident?i=dest">dest</a>, char *<a href="ident?i=src">src</a>, int <a href="ident?i=len">len</a>, int <a href="ident?i=max">max</a>)
<a name="L873" href="source/net/ipv4/ipconfig.c#L873">873</a> {
<a name="L874" href="source/net/ipv4/ipconfig.c#L874">874</a>         if (!<a href="ident?i=len">len</a>)
<a name="L875" href="source/net/ipv4/ipconfig.c#L875">875</a>                 return 0;
<a name="L876" href="source/net/ipv4/ipconfig.c#L876">876</a>         if (<a href="ident?i=len">len</a> &gt; <a href="ident?i=max">max</a>-1)
<a name="L877" href="source/net/ipv4/ipconfig.c#L877">877</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=max">max</a>-1;
<a name="L878" href="source/net/ipv4/ipconfig.c#L878">878</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dest">dest</a>, <a href="ident?i=src">src</a>, <a href="ident?i=len">len</a>);
<a name="L879" href="source/net/ipv4/ipconfig.c#L879">879</a>         <a href="ident?i=dest">dest</a>[<a href="ident?i=len">len</a>] = <i>'\0'</i>;
<a name="L880" href="source/net/ipv4/ipconfig.c#L880">880</a>         return 1;
<a name="L881" href="source/net/ipv4/ipconfig.c#L881">881</a> }
<a name="L882" href="source/net/ipv4/ipconfig.c#L882">882</a> 
<a name="L883" href="source/net/ipv4/ipconfig.c#L883">883</a> 
<a name="L884" href="source/net/ipv4/ipconfig.c#L884">884</a> <b><i>/*</i></b>
<a name="L885" href="source/net/ipv4/ipconfig.c#L885">885</a> <b><i> *  Process BOOTP extensions.</i></b>
<a name="L886" href="source/net/ipv4/ipconfig.c#L886">886</a> <b><i> */</i></b>
<a name="L887" href="source/net/ipv4/ipconfig.c#L887">887</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ic_do_bootp_ext">ic_do_bootp_ext</a>(<a href="ident?i=u8">u8</a> *ext)
<a name="L888" href="source/net/ipv4/ipconfig.c#L888">888</a> {
<a name="L889" href="source/net/ipv4/ipconfig.c#L889">889</a>         <a href="ident?i=u8">u8</a> servers;
<a name="L890" href="source/net/ipv4/ipconfig.c#L890">890</a>         int <a href="ident?i=i">i</a>;
<a name="L891" href="source/net/ipv4/ipconfig.c#L891">891</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=mtu">mtu</a>;
<a name="L892" href="source/net/ipv4/ipconfig.c#L892">892</a> 
<a name="L893" href="source/net/ipv4/ipconfig.c#L893">893</a> #ifdef <a href="ident?i=IPCONFIG_DEBUG">IPCONFIG_DEBUG</a>
<a name="L894" href="source/net/ipv4/ipconfig.c#L894">894</a>         <a href="ident?i=u8">u8</a> *<a href="ident?i=c">c</a>;
<a name="L895" href="source/net/ipv4/ipconfig.c#L895">895</a> 
<a name="L896" href="source/net/ipv4/ipconfig.c#L896">896</a>         <a href="ident?i=printk">printk</a>(<i>"DHCP/BOOTP: Got extension %d:"</i>,*ext);
<a name="L897" href="source/net/ipv4/ipconfig.c#L897">897</a>         for (<a href="ident?i=c">c</a>=ext+2; <a href="ident?i=c">c</a>&lt;ext+2+ext[1]; <a href="ident?i=c">c</a>++)
<a name="L898" href="source/net/ipv4/ipconfig.c#L898">898</a>                 <a href="ident?i=printk">printk</a>(<i>" %02x"</i>, *<a href="ident?i=c">c</a>);
<a name="L899" href="source/net/ipv4/ipconfig.c#L899">899</a>         <a href="ident?i=printk">printk</a>(<i>"\n"</i>);
<a name="L900" href="source/net/ipv4/ipconfig.c#L900">900</a> #endif
<a name="L901" href="source/net/ipv4/ipconfig.c#L901">901</a> 
<a name="L902" href="source/net/ipv4/ipconfig.c#L902">902</a>         switch (*ext++) {
<a name="L903" href="source/net/ipv4/ipconfig.c#L903">903</a>         case 1:         <b><i>/* Subnet mask */</i></b>
<a name="L904" href="source/net/ipv4/ipconfig.c#L904">904</a>                 if (<a href="ident?i=ic_netmask">ic_netmask</a> == <a href="ident?i=NONE">NONE</a>)
<a name="L905" href="source/net/ipv4/ipconfig.c#L905">905</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=ic_netmask">ic_netmask</a>, ext+1, 4);
<a name="L906" href="source/net/ipv4/ipconfig.c#L906">906</a>                 break;
<a name="L907" href="source/net/ipv4/ipconfig.c#L907">907</a>         case 3:         <b><i>/* Default gateway */</i></b>
<a name="L908" href="source/net/ipv4/ipconfig.c#L908">908</a>                 if (<a href="ident?i=ic_gateway">ic_gateway</a> == <a href="ident?i=NONE">NONE</a>)
<a name="L909" href="source/net/ipv4/ipconfig.c#L909">909</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=ic_gateway">ic_gateway</a>, ext+1, 4);
<a name="L910" href="source/net/ipv4/ipconfig.c#L910">910</a>                 break;
<a name="L911" href="source/net/ipv4/ipconfig.c#L911">911</a>         case 6:         <b><i>/* DNS server */</i></b>
<a name="L912" href="source/net/ipv4/ipconfig.c#L912">912</a>                 servers= *ext/4;
<a name="L913" href="source/net/ipv4/ipconfig.c#L913">913</a>                 if (servers &gt; <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>)
<a name="L914" href="source/net/ipv4/ipconfig.c#L914">914</a>                         servers = <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>;
<a name="L915" href="source/net/ipv4/ipconfig.c#L915">915</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; servers; <a href="ident?i=i">i</a>++) {
<a name="L916" href="source/net/ipv4/ipconfig.c#L916">916</a>                         if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>] == <a href="ident?i=NONE">NONE</a>)
<a name="L917" href="source/net/ipv4/ipconfig.c#L917">917</a>                                 <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>], ext+1+4*<a href="ident?i=i">i</a>, 4);
<a name="L918" href="source/net/ipv4/ipconfig.c#L918">918</a>                 }
<a name="L919" href="source/net/ipv4/ipconfig.c#L919">919</a>                 break;
<a name="L920" href="source/net/ipv4/ipconfig.c#L920">920</a>         case 12:        <b><i>/* Host name */</i></b>
<a name="L921" href="source/net/ipv4/ipconfig.c#L921">921</a>                 <a href="ident?i=ic_bootp_string">ic_bootp_string</a>(<a href="ident?i=utsname">utsname</a>()-&gt;nodename, ext+1, *ext,
<a name="L922" href="source/net/ipv4/ipconfig.c#L922">922</a>                                 <a href="ident?i=__NEW_UTS_LEN">__NEW_UTS_LEN</a>);
<a name="L923" href="source/net/ipv4/ipconfig.c#L923">923</a>                 ic_host_name_set = 1;
<a name="L924" href="source/net/ipv4/ipconfig.c#L924">924</a>                 break;
<a name="L925" href="source/net/ipv4/ipconfig.c#L925">925</a>         case 15:        <b><i>/* Domain name (DNS) */</i></b>
<a name="L926" href="source/net/ipv4/ipconfig.c#L926">926</a>                 <a href="ident?i=ic_bootp_string">ic_bootp_string</a>(<a href="ident?i=ic_domain">ic_domain</a>, ext+1, *ext, sizeof(<a href="ident?i=ic_domain">ic_domain</a>));
<a name="L927" href="source/net/ipv4/ipconfig.c#L927">927</a>                 break;
<a name="L928" href="source/net/ipv4/ipconfig.c#L928">928</a>         case 17:        <b><i>/* Root path */</i></b>
<a name="L929" href="source/net/ipv4/ipconfig.c#L929">929</a>                 if (!<a href="ident?i=root_server_path">root_server_path</a>[0])
<a name="L930" href="source/net/ipv4/ipconfig.c#L930">930</a>                         <a href="ident?i=ic_bootp_string">ic_bootp_string</a>(<a href="ident?i=root_server_path">root_server_path</a>, ext+1, *ext,
<a name="L931" href="source/net/ipv4/ipconfig.c#L931">931</a>                                         sizeof(<a href="ident?i=root_server_path">root_server_path</a>));
<a name="L932" href="source/net/ipv4/ipconfig.c#L932">932</a>                 break;
<a name="L933" href="source/net/ipv4/ipconfig.c#L933">933</a>         case 26:        <b><i>/* Interface MTU */</i></b>
<a name="L934" href="source/net/ipv4/ipconfig.c#L934">934</a>                 <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=mtu">mtu</a>, ext+1, sizeof(<a href="ident?i=mtu">mtu</a>));
<a name="L935" href="source/net/ipv4/ipconfig.c#L935">935</a>                 ic_dev_mtu = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=mtu">mtu</a>);
<a name="L936" href="source/net/ipv4/ipconfig.c#L936">936</a>                 break;
<a name="L937" href="source/net/ipv4/ipconfig.c#L937">937</a>         case 40:        <b><i>/* NIS Domain name (_not_ DNS) */</i></b>
<a name="L938" href="source/net/ipv4/ipconfig.c#L938">938</a>                 <a href="ident?i=ic_bootp_string">ic_bootp_string</a>(<a href="ident?i=utsname">utsname</a>()-&gt;domainname, ext+1, *ext,
<a name="L939" href="source/net/ipv4/ipconfig.c#L939">939</a>                                 <a href="ident?i=__NEW_UTS_LEN">__NEW_UTS_LEN</a>);
<a name="L940" href="source/net/ipv4/ipconfig.c#L940">940</a>                 break;
<a name="L941" href="source/net/ipv4/ipconfig.c#L941">941</a>         }
<a name="L942" href="source/net/ipv4/ipconfig.c#L942">942</a> }
<a name="L943" href="source/net/ipv4/ipconfig.c#L943">943</a> 
<a name="L944" href="source/net/ipv4/ipconfig.c#L944">944</a> 
<a name="L945" href="source/net/ipv4/ipconfig.c#L945">945</a> <b><i>/*</i></b>
<a name="L946" href="source/net/ipv4/ipconfig.c#L946">946</a> <b><i> *  Receive BOOTP reply.</i></b>
<a name="L947" href="source/net/ipv4/ipconfig.c#L947">947</a> <b><i> */</i></b>
<a name="L948" href="source/net/ipv4/ipconfig.c#L948">948</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_bootp_recv">ic_bootp_recv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=packet_type">packet_type</a> *<a href="ident?i=pt">pt</a>, struct <a href="ident?i=net_device">net_device</a> *orig_dev)
<a name="L949" href="source/net/ipv4/ipconfig.c#L949">949</a> {
<a name="L950" href="source/net/ipv4/ipconfig.c#L950">950</a>         struct <a href="ident?i=bootp_pkt">bootp_pkt</a> *<a href="ident?i=b">b</a>;
<a name="L951" href="source/net/ipv4/ipconfig.c#L951">951</a>         struct <a href="ident?i=iphdr">iphdr</a> *<a href="ident?i=h">h</a>;
<a name="L952" href="source/net/ipv4/ipconfig.c#L952">952</a>         struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>;
<a name="L953" href="source/net/ipv4/ipconfig.c#L953">953</a>         int <a href="ident?i=len">len</a>, ext_len;
<a name="L954" href="source/net/ipv4/ipconfig.c#L954">954</a> 
<a name="L955" href="source/net/ipv4/ipconfig.c#L955">955</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L956" href="source/net/ipv4/ipconfig.c#L956">956</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L957" href="source/net/ipv4/ipconfig.c#L957">957</a> 
<a name="L958" href="source/net/ipv4/ipconfig.c#L958">958</a>         <b><i>/* Perform verifications before taking the lock.  */</i></b>
<a name="L959" href="source/net/ipv4/ipconfig.c#L959">959</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_OTHERHOST">PACKET_OTHERHOST</a>)
<a name="L960" href="source/net/ipv4/ipconfig.c#L960">960</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L961" href="source/net/ipv4/ipconfig.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/ipconfig.c#L962">962</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_share_check">skb_share_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L963" href="source/net/ipv4/ipconfig.c#L963">963</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L964" href="source/net/ipv4/ipconfig.c#L964">964</a>                 return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L965" href="source/net/ipv4/ipconfig.c#L965">965</a> 
<a name="L966" href="source/net/ipv4/ipconfig.c#L966">966</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>,
<a name="L967" href="source/net/ipv4/ipconfig.c#L967">967</a>                            sizeof(struct <a href="ident?i=iphdr">iphdr</a>) +
<a name="L968" href="source/net/ipv4/ipconfig.c#L968">968</a>                            sizeof(struct <a href="ident?i=udphdr">udphdr</a>)))
<a name="L969" href="source/net/ipv4/ipconfig.c#L969">969</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L970" href="source/net/ipv4/ipconfig.c#L970">970</a> 
<a name="L971" href="source/net/ipv4/ipconfig.c#L971">971</a>         <a href="ident?i=b">b</a> = (struct <a href="ident?i=bootp_pkt">bootp_pkt</a> *)<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L972" href="source/net/ipv4/ipconfig.c#L972">972</a>         <a href="ident?i=h">h</a> = &amp;<a href="ident?i=b">b</a>-&gt;iph;
<a name="L973" href="source/net/ipv4/ipconfig.c#L973">973</a> 
<a name="L974" href="source/net/ipv4/ipconfig.c#L974">974</a>         if (<a href="ident?i=h">h</a>-&gt;ihl != 5 || <a href="ident?i=h">h</a>-&gt;<a href="ident?i=version">version</a> != 4 || <a href="ident?i=h">h</a>-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>)
<a name="L975" href="source/net/ipv4/ipconfig.c#L975">975</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L976" href="source/net/ipv4/ipconfig.c#L976">976</a> 
<a name="L977" href="source/net/ipv4/ipconfig.c#L977">977</a>         <b><i>/* Fragments are not supported */</i></b>
<a name="L978" href="source/net/ipv4/ipconfig.c#L978">978</a>         if (<a href="ident?i=ip_is_fragment">ip_is_fragment</a>(<a href="ident?i=h">h</a>)) {
<a name="L979" href="source/net/ipv4/ipconfig.c#L979">979</a>                 <a href="ident?i=net_err_ratelimited">net_err_ratelimited</a>(<i>"DHCP/BOOTP: Ignoring fragmented reply\n"</i>);
<a name="L980" href="source/net/ipv4/ipconfig.c#L980">980</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L981" href="source/net/ipv4/ipconfig.c#L981">981</a>         }
<a name="L982" href="source/net/ipv4/ipconfig.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/ipconfig.c#L983">983</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=h">h</a>-&gt;tot_len))
<a name="L984" href="source/net/ipv4/ipconfig.c#L984">984</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L985" href="source/net/ipv4/ipconfig.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/ipconfig.c#L986">986</a>         if (<a href="ident?i=ip_fast_csum">ip_fast_csum</a>((char *) <a href="ident?i=h">h</a>, <a href="ident?i=h">h</a>-&gt;ihl))
<a name="L987" href="source/net/ipv4/ipconfig.c#L987">987</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L988" href="source/net/ipv4/ipconfig.c#L988">988</a> 
<a name="L989" href="source/net/ipv4/ipconfig.c#L989">989</a>         if (<a href="ident?i=b">b</a>-&gt;udph.source != <a href="ident?i=htons">htons</a>(67) || <a href="ident?i=b">b</a>-&gt;udph.<a href="ident?i=dest">dest</a> != <a href="ident?i=htons">htons</a>(68))
<a name="L990" href="source/net/ipv4/ipconfig.c#L990">990</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L991" href="source/net/ipv4/ipconfig.c#L991">991</a> 
<a name="L992" href="source/net/ipv4/ipconfig.c#L992">992</a>         if (<a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=h">h</a>-&gt;tot_len) &lt; <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=b">b</a>-&gt;udph.<a href="ident?i=len">len</a>) + sizeof(struct <a href="ident?i=iphdr">iphdr</a>))
<a name="L993" href="source/net/ipv4/ipconfig.c#L993">993</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L994" href="source/net/ipv4/ipconfig.c#L994">994</a> 
<a name="L995" href="source/net/ipv4/ipconfig.c#L995">995</a>         <a href="ident?i=len">len</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=b">b</a>-&gt;udph.<a href="ident?i=len">len</a>) - sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L996" href="source/net/ipv4/ipconfig.c#L996">996</a>         ext_len = <a href="ident?i=len">len</a> - (sizeof(*<a href="ident?i=b">b</a>) -
<a name="L997" href="source/net/ipv4/ipconfig.c#L997">997</a>                          sizeof(struct <a href="ident?i=iphdr">iphdr</a>) -
<a name="L998" href="source/net/ipv4/ipconfig.c#L998">998</a>                          sizeof(struct <a href="ident?i=udphdr">udphdr</a>) -
<a name="L999" href="source/net/ipv4/ipconfig.c#L999">999</a>                          sizeof(<a href="ident?i=b">b</a>-&gt;exten));
<a name="L1000" href="source/net/ipv4/ipconfig.c#L1000">1000</a>         if (ext_len &lt; 0)
<a name="L1001" href="source/net/ipv4/ipconfig.c#L1001">1001</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1002" href="source/net/ipv4/ipconfig.c#L1002">1002</a> 
<a name="L1003" href="source/net/ipv4/ipconfig.c#L1003">1003</a>         <b><i>/* Ok the front looks good, make sure we can get at the rest.  */</i></b>
<a name="L1004" href="source/net/ipv4/ipconfig.c#L1004">1004</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>))
<a name="L1005" href="source/net/ipv4/ipconfig.c#L1005">1005</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1006" href="source/net/ipv4/ipconfig.c#L1006">1006</a> 
<a name="L1007" href="source/net/ipv4/ipconfig.c#L1007">1007</a>         <a href="ident?i=b">b</a> = (struct <a href="ident?i=bootp_pkt">bootp_pkt</a> *)<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1008" href="source/net/ipv4/ipconfig.c#L1008">1008</a>         <a href="ident?i=h">h</a> = &amp;<a href="ident?i=b">b</a>-&gt;iph;
<a name="L1009" href="source/net/ipv4/ipconfig.c#L1009">1009</a> 
<a name="L1010" href="source/net/ipv4/ipconfig.c#L1010">1010</a>         <b><i>/* One reply at a time, please. */</i></b>
<a name="L1011" href="source/net/ipv4/ipconfig.c#L1011">1011</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;ic_recv_lock);
<a name="L1012" href="source/net/ipv4/ipconfig.c#L1012">1012</a> 
<a name="L1013" href="source/net/ipv4/ipconfig.c#L1013">1013</a>         <b><i>/* If we already have a reply, just drop the packet */</i></b>
<a name="L1014" href="source/net/ipv4/ipconfig.c#L1014">1014</a>         if (ic_got_reply)
<a name="L1015" href="source/net/ipv4/ipconfig.c#L1015">1015</a>                 goto drop_unlock;
<a name="L1016" href="source/net/ipv4/ipconfig.c#L1016">1016</a> 
<a name="L1017" href="source/net/ipv4/ipconfig.c#L1017">1017</a>         <b><i>/* Find the ic_device that the packet arrived on */</i></b>
<a name="L1018" href="source/net/ipv4/ipconfig.c#L1018">1018</a>         <a href="ident?i=d">d</a> = ic_first_dev;
<a name="L1019" href="source/net/ipv4/ipconfig.c#L1019">1019</a>         while (<a href="ident?i=d">d</a> &amp;&amp; <a href="ident?i=d">d</a>-&gt;<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>)
<a name="L1020" href="source/net/ipv4/ipconfig.c#L1020">1020</a>                 <a href="ident?i=d">d</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L1021" href="source/net/ipv4/ipconfig.c#L1021">1021</a>         if (!<a href="ident?i=d">d</a>)
<a name="L1022" href="source/net/ipv4/ipconfig.c#L1022">1022</a>                 goto drop_unlock;  <b><i>/* should never happen */</i></b>
<a name="L1023" href="source/net/ipv4/ipconfig.c#L1023">1023</a> 
<a name="L1024" href="source/net/ipv4/ipconfig.c#L1024">1024</a>         <b><i>/* Is it a reply to our BOOTP request? */</i></b>
<a name="L1025" href="source/net/ipv4/ipconfig.c#L1025">1025</a>         if (<a href="ident?i=b">b</a>-&gt;<a href="ident?i=op">op</a> != <a href="ident?i=BOOTP_REPLY">BOOTP_REPLY</a> ||
<a name="L1026" href="source/net/ipv4/ipconfig.c#L1026">1026</a>             <a href="ident?i=b">b</a>-&gt;xid != <a href="ident?i=d">d</a>-&gt;xid) {
<a name="L1027" href="source/net/ipv4/ipconfig.c#L1027">1027</a>                 <a href="ident?i=net_err_ratelimited">net_err_ratelimited</a>(<i>"DHCP/BOOTP: Reply not for us, op[%x] xid[%x]\n"</i>,
<a name="L1028" href="source/net/ipv4/ipconfig.c#L1028">1028</a>                                     <a href="ident?i=b">b</a>-&gt;<a href="ident?i=op">op</a>, <a href="ident?i=b">b</a>-&gt;xid);
<a name="L1029" href="source/net/ipv4/ipconfig.c#L1029">1029</a>                 goto drop_unlock;
<a name="L1030" href="source/net/ipv4/ipconfig.c#L1030">1030</a>         }
<a name="L1031" href="source/net/ipv4/ipconfig.c#L1031">1031</a> 
<a name="L1032" href="source/net/ipv4/ipconfig.c#L1032">1032</a>         <b><i>/* Is it a reply for the device we are configuring? */</i></b>
<a name="L1033" href="source/net/ipv4/ipconfig.c#L1033">1033</a>         if (<a href="ident?i=b">b</a>-&gt;xid != <a href="ident?i=ic_dev_xid">ic_dev_xid</a>) {
<a name="L1034" href="source/net/ipv4/ipconfig.c#L1034">1034</a>                 <a href="ident?i=net_err_ratelimited">net_err_ratelimited</a>(<i>"DHCP/BOOTP: Ignoring delayed packet\n"</i>);
<a name="L1035" href="source/net/ipv4/ipconfig.c#L1035">1035</a>                 goto drop_unlock;
<a name="L1036" href="source/net/ipv4/ipconfig.c#L1036">1036</a>         }
<a name="L1037" href="source/net/ipv4/ipconfig.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/ipconfig.c#L1038">1038</a>         <b><i>/* Parse extensions */</i></b>
<a name="L1039" href="source/net/ipv4/ipconfig.c#L1039">1039</a>         if (ext_len &gt;= 4 &amp;&amp;
<a name="L1040" href="source/net/ipv4/ipconfig.c#L1040">1040</a>             !<a href="ident?i=memcmp">memcmp</a>(<a href="ident?i=b">b</a>-&gt;exten, <a href="ident?i=ic_bootp_cookie">ic_bootp_cookie</a>, 4)) { <b><i>/* Check magic cookie */</i></b>
<a name="L1041" href="source/net/ipv4/ipconfig.c#L1041">1041</a>                 <a href="ident?i=u8">u8</a> *<a href="ident?i=end">end</a> = (<a href="ident?i=u8">u8</a> *) <a href="ident?i=b">b</a> + <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=b">b</a>-&gt;iph.tot_len);
<a name="L1042" href="source/net/ipv4/ipconfig.c#L1042">1042</a>                 <a href="ident?i=u8">u8</a> *ext;
<a name="L1043" href="source/net/ipv4/ipconfig.c#L1043">1043</a> 
<a name="L1044" href="source/net/ipv4/ipconfig.c#L1044">1044</a> #ifdef <a href="ident?i=IPCONFIG_DHCP">IPCONFIG_DHCP</a>
<a name="L1045" href="source/net/ipv4/ipconfig.c#L1045">1045</a>                 if (<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>) {
<a name="L1046" href="source/net/ipv4/ipconfig.c#L1046">1046</a>                         <a href="ident?i=__be32">__be32</a> server_id = <a href="ident?i=NONE">NONE</a>;
<a name="L1047" href="source/net/ipv4/ipconfig.c#L1047">1047</a>                         int mt = 0;
<a name="L1048" href="source/net/ipv4/ipconfig.c#L1048">1048</a> 
<a name="L1049" href="source/net/ipv4/ipconfig.c#L1049">1049</a>                         ext = &amp;<a href="ident?i=b">b</a>-&gt;exten[4];
<a name="L1050" href="source/net/ipv4/ipconfig.c#L1050">1050</a>                         while (ext &lt; <a href="ident?i=end">end</a> &amp;&amp; *ext != 0xff) {
<a name="L1051" href="source/net/ipv4/ipconfig.c#L1051">1051</a>                                 <a href="ident?i=u8">u8</a> *opt = ext++;
<a name="L1052" href="source/net/ipv4/ipconfig.c#L1052">1052</a>                                 if (*opt == 0)  <b><i>/* Padding */</i></b>
<a name="L1053" href="source/net/ipv4/ipconfig.c#L1053">1053</a>                                         continue;
<a name="L1054" href="source/net/ipv4/ipconfig.c#L1054">1054</a>                                 ext += *ext + 1;
<a name="L1055" href="source/net/ipv4/ipconfig.c#L1055">1055</a>                                 if (ext &gt;= <a href="ident?i=end">end</a>)
<a name="L1056" href="source/net/ipv4/ipconfig.c#L1056">1056</a>                                         break;
<a name="L1057" href="source/net/ipv4/ipconfig.c#L1057">1057</a>                                 switch (*opt) {
<a name="L1058" href="source/net/ipv4/ipconfig.c#L1058">1058</a>                                 case 53:        <b><i>/* Message type */</i></b>
<a name="L1059" href="source/net/ipv4/ipconfig.c#L1059">1059</a>                                         if (opt[1])
<a name="L1060" href="source/net/ipv4/ipconfig.c#L1060">1060</a>                                                 mt = opt[2];
<a name="L1061" href="source/net/ipv4/ipconfig.c#L1061">1061</a>                                         break;
<a name="L1062" href="source/net/ipv4/ipconfig.c#L1062">1062</a>                                 case 54:        <b><i>/* Server ID (IP address) */</i></b>
<a name="L1063" href="source/net/ipv4/ipconfig.c#L1063">1063</a>                                         if (opt[1] &gt;= 4)
<a name="L1064" href="source/net/ipv4/ipconfig.c#L1064">1064</a>                                                 <a href="ident?i=memcpy">memcpy</a>(&amp;server_id, opt + 2, 4);
<a name="L1065" href="source/net/ipv4/ipconfig.c#L1065">1065</a>                                         break;
<a name="L1066" href="source/net/ipv4/ipconfig.c#L1066">1066</a>                                 }
<a name="L1067" href="source/net/ipv4/ipconfig.c#L1067">1067</a>                         }
<a name="L1068" href="source/net/ipv4/ipconfig.c#L1068">1068</a> 
<a name="L1069" href="source/net/ipv4/ipconfig.c#L1069">1069</a> #ifdef <a href="ident?i=IPCONFIG_DEBUG">IPCONFIG_DEBUG</a>
<a name="L1070" href="source/net/ipv4/ipconfig.c#L1070">1070</a>                         <a href="ident?i=printk">printk</a>(<i>"DHCP: Got message type %d\n"</i>, mt);
<a name="L1071" href="source/net/ipv4/ipconfig.c#L1071">1071</a> #endif
<a name="L1072" href="source/net/ipv4/ipconfig.c#L1072">1072</a> 
<a name="L1073" href="source/net/ipv4/ipconfig.c#L1073">1073</a>                         switch (mt) {
<a name="L1074" href="source/net/ipv4/ipconfig.c#L1074">1074</a>                         case <a href="ident?i=DHCPOFFER">DHCPOFFER</a>:
<a name="L1075" href="source/net/ipv4/ipconfig.c#L1075">1075</a>                                 <b><i>/* While in the process of accepting one offer,</i></b>
<a name="L1076" href="source/net/ipv4/ipconfig.c#L1076">1076</a> <b><i>                                 * ignore all others.</i></b>
<a name="L1077" href="source/net/ipv4/ipconfig.c#L1077">1077</a> <b><i>                                 */</i></b>
<a name="L1078" href="source/net/ipv4/ipconfig.c#L1078">1078</a>                                 if (<a href="ident?i=ic_myaddr">ic_myaddr</a> != <a href="ident?i=NONE">NONE</a>)
<a name="L1079" href="source/net/ipv4/ipconfig.c#L1079">1079</a>                                         goto drop_unlock;
<a name="L1080" href="source/net/ipv4/ipconfig.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/ipconfig.c#L1081">1081</a>                                 <b><i>/* Let's accept that offer. */</i></b>
<a name="L1082" href="source/net/ipv4/ipconfig.c#L1082">1082</a>                                 <a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=b">b</a>-&gt;your_ip;
<a name="L1083" href="source/net/ipv4/ipconfig.c#L1083">1083</a>                                 <a href="ident?i=ic_servaddr">ic_servaddr</a> = server_id;
<a name="L1084" href="source/net/ipv4/ipconfig.c#L1084">1084</a> #ifdef <a href="ident?i=IPCONFIG_DEBUG">IPCONFIG_DEBUG</a>
<a name="L1085" href="source/net/ipv4/ipconfig.c#L1085">1085</a>                                 <a href="ident?i=printk">printk</a>(<i>"DHCP: Offered address %pI4 by server %pI4\n"</i>,
<a name="L1086" href="source/net/ipv4/ipconfig.c#L1086">1086</a>                                        &amp;<a href="ident?i=ic_myaddr">ic_myaddr</a>, &amp;<a href="ident?i=b">b</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>);
<a name="L1087" href="source/net/ipv4/ipconfig.c#L1087">1087</a> #endif
<a name="L1088" href="source/net/ipv4/ipconfig.c#L1088">1088</a>                                 <b><i>/* The DHCP indicated server address takes</i></b>
<a name="L1089" href="source/net/ipv4/ipconfig.c#L1089">1089</a> <b><i>                                 * precedence over the bootp header one if</i></b>
<a name="L1090" href="source/net/ipv4/ipconfig.c#L1090">1090</a> <b><i>                                 * they are different.</i></b>
<a name="L1091" href="source/net/ipv4/ipconfig.c#L1091">1091</a> <b><i>                                 */</i></b>
<a name="L1092" href="source/net/ipv4/ipconfig.c#L1092">1092</a>                                 if ((server_id != <a href="ident?i=NONE">NONE</a>) &amp;&amp;
<a name="L1093" href="source/net/ipv4/ipconfig.c#L1093">1093</a>                                     (<a href="ident?i=b">b</a>-&gt;server_ip != server_id))
<a name="L1094" href="source/net/ipv4/ipconfig.c#L1094">1094</a>                                         <a href="ident?i=b">b</a>-&gt;server_ip = <a href="ident?i=ic_servaddr">ic_servaddr</a>;
<a name="L1095" href="source/net/ipv4/ipconfig.c#L1095">1095</a>                                 break;
<a name="L1096" href="source/net/ipv4/ipconfig.c#L1096">1096</a> 
<a name="L1097" href="source/net/ipv4/ipconfig.c#L1097">1097</a>                         case <a href="ident?i=DHCPACK">DHCPACK</a>:
<a name="L1098" href="source/net/ipv4/ipconfig.c#L1098">1098</a>                                 if (<a href="ident?i=memcmp">memcmp</a>(<a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=b">b</a>-&gt;<a href="ident?i=hw_addr">hw_addr</a>, <a href="ident?i=dev">dev</a>-&gt;addr_len) != 0)
<a name="L1099" href="source/net/ipv4/ipconfig.c#L1099">1099</a>                                         goto drop_unlock;
<a name="L1100" href="source/net/ipv4/ipconfig.c#L1100">1100</a> 
<a name="L1101" href="source/net/ipv4/ipconfig.c#L1101">1101</a>                                 <b><i>/* Yeah! */</i></b>
<a name="L1102" href="source/net/ipv4/ipconfig.c#L1102">1102</a>                                 break;
<a name="L1103" href="source/net/ipv4/ipconfig.c#L1103">1103</a> 
<a name="L1104" href="source/net/ipv4/ipconfig.c#L1104">1104</a>                         default:
<a name="L1105" href="source/net/ipv4/ipconfig.c#L1105">1105</a>                                 <b><i>/* Urque.  Forget it*/</i></b>
<a name="L1106" href="source/net/ipv4/ipconfig.c#L1106">1106</a>                                 <a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1107" href="source/net/ipv4/ipconfig.c#L1107">1107</a>                                 <a href="ident?i=ic_servaddr">ic_servaddr</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1108" href="source/net/ipv4/ipconfig.c#L1108">1108</a>                                 goto drop_unlock;
<a name="L1109" href="source/net/ipv4/ipconfig.c#L1109">1109</a>                         }
<a name="L1110" href="source/net/ipv4/ipconfig.c#L1110">1110</a> 
<a name="L1111" href="source/net/ipv4/ipconfig.c#L1111">1111</a>                         ic_dhcp_msgtype = mt;
<a name="L1112" href="source/net/ipv4/ipconfig.c#L1112">1112</a> 
<a name="L1113" href="source/net/ipv4/ipconfig.c#L1113">1113</a>                 }
<a name="L1114" href="source/net/ipv4/ipconfig.c#L1114">1114</a> #endif <b><i>/* IPCONFIG_DHCP */</i></b>
<a name="L1115" href="source/net/ipv4/ipconfig.c#L1115">1115</a> 
<a name="L1116" href="source/net/ipv4/ipconfig.c#L1116">1116</a>                 ext = &amp;<a href="ident?i=b">b</a>-&gt;exten[4];
<a name="L1117" href="source/net/ipv4/ipconfig.c#L1117">1117</a>                 while (ext &lt; <a href="ident?i=end">end</a> &amp;&amp; *ext != 0xff) {
<a name="L1118" href="source/net/ipv4/ipconfig.c#L1118">1118</a>                         <a href="ident?i=u8">u8</a> *opt = ext++;
<a name="L1119" href="source/net/ipv4/ipconfig.c#L1119">1119</a>                         if (*opt == 0)  <b><i>/* Padding */</i></b>
<a name="L1120" href="source/net/ipv4/ipconfig.c#L1120">1120</a>                                 continue;
<a name="L1121" href="source/net/ipv4/ipconfig.c#L1121">1121</a>                         ext += *ext + 1;
<a name="L1122" href="source/net/ipv4/ipconfig.c#L1122">1122</a>                         if (ext &lt; <a href="ident?i=end">end</a>)
<a name="L1123" href="source/net/ipv4/ipconfig.c#L1123">1123</a>                                 <a href="ident?i=ic_do_bootp_ext">ic_do_bootp_ext</a>(opt);
<a name="L1124" href="source/net/ipv4/ipconfig.c#L1124">1124</a>                 }
<a name="L1125" href="source/net/ipv4/ipconfig.c#L1125">1125</a>         }
<a name="L1126" href="source/net/ipv4/ipconfig.c#L1126">1126</a> 
<a name="L1127" href="source/net/ipv4/ipconfig.c#L1127">1127</a>         <b><i>/* We have a winner! */</i></b>
<a name="L1128" href="source/net/ipv4/ipconfig.c#L1128">1128</a>         ic_dev = <a href="ident?i=dev">dev</a>;
<a name="L1129" href="source/net/ipv4/ipconfig.c#L1129">1129</a>         <a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=b">b</a>-&gt;your_ip;
<a name="L1130" href="source/net/ipv4/ipconfig.c#L1130">1130</a>         <a href="ident?i=ic_servaddr">ic_servaddr</a> = <a href="ident?i=b">b</a>-&gt;server_ip;
<a name="L1131" href="source/net/ipv4/ipconfig.c#L1131">1131</a>         <a href="ident?i=ic_addrservaddr">ic_addrservaddr</a> = <a href="ident?i=b">b</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>;
<a name="L1132" href="source/net/ipv4/ipconfig.c#L1132">1132</a>         if (<a href="ident?i=ic_gateway">ic_gateway</a> == <a href="ident?i=NONE">NONE</a> &amp;&amp; <a href="ident?i=b">b</a>-&gt;relay_ip)
<a name="L1133" href="source/net/ipv4/ipconfig.c#L1133">1133</a>                 <a href="ident?i=ic_gateway">ic_gateway</a> = <a href="ident?i=b">b</a>-&gt;relay_ip;
<a name="L1134" href="source/net/ipv4/ipconfig.c#L1134">1134</a>         if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[0] == <a href="ident?i=NONE">NONE</a>)
<a name="L1135" href="source/net/ipv4/ipconfig.c#L1135">1135</a>                 <a href="ident?i=ic_nameservers">ic_nameservers</a>[0] = <a href="ident?i=ic_servaddr">ic_servaddr</a>;
<a name="L1136" href="source/net/ipv4/ipconfig.c#L1136">1136</a>         ic_got_reply = <a href="ident?i=IC_BOOTP">IC_BOOTP</a>;
<a name="L1137" href="source/net/ipv4/ipconfig.c#L1137">1137</a> 
<a name="L1138" href="source/net/ipv4/ipconfig.c#L1138">1138</a> drop_unlock:
<a name="L1139" href="source/net/ipv4/ipconfig.c#L1139">1139</a>         <b><i>/* Show's over.  Nothing to see here.  */</i></b>
<a name="L1140" href="source/net/ipv4/ipconfig.c#L1140">1140</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;ic_recv_lock);
<a name="L1141" href="source/net/ipv4/ipconfig.c#L1141">1141</a> 
<a name="L1142" href="source/net/ipv4/ipconfig.c#L1142">1142</a> <a href="ident?i=drop">drop</a>:
<a name="L1143" href="source/net/ipv4/ipconfig.c#L1143">1143</a>         <b><i>/* Throw the packet out. */</i></b>
<a name="L1144" href="source/net/ipv4/ipconfig.c#L1144">1144</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1145" href="source/net/ipv4/ipconfig.c#L1145">1145</a> 
<a name="L1146" href="source/net/ipv4/ipconfig.c#L1146">1146</a>         return 0;
<a name="L1147" href="source/net/ipv4/ipconfig.c#L1147">1147</a> }
<a name="L1148" href="source/net/ipv4/ipconfig.c#L1148">1148</a> 
<a name="L1149" href="source/net/ipv4/ipconfig.c#L1149">1149</a> 
<a name="L1150" href="source/net/ipv4/ipconfig.c#L1150">1150</a> #endif
<a name="L1151" href="source/net/ipv4/ipconfig.c#L1151">1151</a> 
<a name="L1152" href="source/net/ipv4/ipconfig.c#L1152">1152</a> 
<a name="L1153" href="source/net/ipv4/ipconfig.c#L1153">1153</a> <b><i>/*</i></b>
<a name="L1154" href="source/net/ipv4/ipconfig.c#L1154">1154</a> <b><i> *      Dynamic IP configuration -- DHCP, BOOTP, RARP.</i></b>
<a name="L1155" href="source/net/ipv4/ipconfig.c#L1155">1155</a> <b><i> */</i></b>
<a name="L1156" href="source/net/ipv4/ipconfig.c#L1156">1156</a> 
<a name="L1157" href="source/net/ipv4/ipconfig.c#L1157">1157</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L1158" href="source/net/ipv4/ipconfig.c#L1158">1158</a> 
<a name="L1159" href="source/net/ipv4/ipconfig.c#L1159">1159</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_dynamic">ic_dynamic</a>(void)
<a name="L1160" href="source/net/ipv4/ipconfig.c#L1160">1160</a> {
<a name="L1161" href="source/net/ipv4/ipconfig.c#L1161">1161</a>         int <a href="ident?i=retries">retries</a>;
<a name="L1162" href="source/net/ipv4/ipconfig.c#L1162">1162</a>         struct <a href="ident?i=ic_device">ic_device</a> *<a href="ident?i=d">d</a>;
<a name="L1163" href="source/net/ipv4/ipconfig.c#L1163">1163</a>         unsigned long start_jiffies, <a href="ident?i=timeout">timeout</a>, jiff;
<a name="L1164" href="source/net/ipv4/ipconfig.c#L1164">1164</a>         int do_bootp = ic_proto_have_if &amp; <a href="ident?i=IC_BOOTP">IC_BOOTP</a>;
<a name="L1165" href="source/net/ipv4/ipconfig.c#L1165">1165</a>         int do_rarp = ic_proto_have_if &amp; <a href="ident?i=IC_RARP">IC_RARP</a>;
<a name="L1166" href="source/net/ipv4/ipconfig.c#L1166">1166</a> 
<a name="L1167" href="source/net/ipv4/ipconfig.c#L1167">1167</a>         <b><i>/*</i></b>
<a name="L1168" href="source/net/ipv4/ipconfig.c#L1168">1168</a> <b><i>         * If none of DHCP/BOOTP/RARP was selected, return with an error.</i></b>
<a name="L1169" href="source/net/ipv4/ipconfig.c#L1169">1169</a> <b><i>         * This routine gets only called when some pieces of information</i></b>
<a name="L1170" href="source/net/ipv4/ipconfig.c#L1170">1170</a> <b><i>         * are missing, and without DHCP/BOOTP/RARP we are unable to get it.</i></b>
<a name="L1171" href="source/net/ipv4/ipconfig.c#L1171">1171</a> <b><i>         */</i></b>
<a name="L1172" href="source/net/ipv4/ipconfig.c#L1172">1172</a>         if (!<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a>) {
<a name="L1173" href="source/net/ipv4/ipconfig.c#L1173">1173</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Incomplete network configuration information\n"</i>);
<a name="L1174" href="source/net/ipv4/ipconfig.c#L1174">1174</a>                 return -1;
<a name="L1175" href="source/net/ipv4/ipconfig.c#L1175">1175</a>         }
<a name="L1176" href="source/net/ipv4/ipconfig.c#L1176">1176</a> 
<a name="L1177" href="source/net/ipv4/ipconfig.c#L1177">1177</a> #ifdef <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
<a name="L1178" href="source/net/ipv4/ipconfig.c#L1178">1178</a>         if ((<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> ^ ic_proto_have_if) &amp; <a href="ident?i=IC_BOOTP">IC_BOOTP</a>)
<a name="L1179" href="source/net/ipv4/ipconfig.c#L1179">1179</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"DHCP/BOOTP: No suitable device found\n"</i>);
<a name="L1180" href="source/net/ipv4/ipconfig.c#L1180">1180</a> #endif
<a name="L1181" href="source/net/ipv4/ipconfig.c#L1181">1181</a> #ifdef <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
<a name="L1182" href="source/net/ipv4/ipconfig.c#L1182">1182</a>         if ((<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> ^ ic_proto_have_if) &amp; <a href="ident?i=IC_RARP">IC_RARP</a>)
<a name="L1183" href="source/net/ipv4/ipconfig.c#L1183">1183</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"RARP: No suitable device found\n"</i>);
<a name="L1184" href="source/net/ipv4/ipconfig.c#L1184">1184</a> #endif
<a name="L1185" href="source/net/ipv4/ipconfig.c#L1185">1185</a> 
<a name="L1186" href="source/net/ipv4/ipconfig.c#L1186">1186</a>         if (!ic_proto_have_if)
<a name="L1187" href="source/net/ipv4/ipconfig.c#L1187">1187</a>                 <b><i>/* Error message already printed */</i></b>
<a name="L1188" href="source/net/ipv4/ipconfig.c#L1188">1188</a>                 return -1;
<a name="L1189" href="source/net/ipv4/ipconfig.c#L1189">1189</a> 
<a name="L1190" href="source/net/ipv4/ipconfig.c#L1190">1190</a>         <b><i>/*</i></b>
<a name="L1191" href="source/net/ipv4/ipconfig.c#L1191">1191</a> <b><i>         * Setup protocols</i></b>
<a name="L1192" href="source/net/ipv4/ipconfig.c#L1192">1192</a> <b><i>         */</i></b>
<a name="L1193" href="source/net/ipv4/ipconfig.c#L1193">1193</a> #ifdef <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
<a name="L1194" href="source/net/ipv4/ipconfig.c#L1194">1194</a>         if (do_bootp)
<a name="L1195" href="source/net/ipv4/ipconfig.c#L1195">1195</a>                 <a href="ident?i=ic_bootp_init">ic_bootp_init</a>();
<a name="L1196" href="source/net/ipv4/ipconfig.c#L1196">1196</a> #endif
<a name="L1197" href="source/net/ipv4/ipconfig.c#L1197">1197</a> #ifdef <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
<a name="L1198" href="source/net/ipv4/ipconfig.c#L1198">1198</a>         if (do_rarp)
<a name="L1199" href="source/net/ipv4/ipconfig.c#L1199">1199</a>                 <a href="ident?i=ic_rarp_init">ic_rarp_init</a>();
<a name="L1200" href="source/net/ipv4/ipconfig.c#L1200">1200</a> #endif
<a name="L1201" href="source/net/ipv4/ipconfig.c#L1201">1201</a> 
<a name="L1202" href="source/net/ipv4/ipconfig.c#L1202">1202</a>         <b><i>/*</i></b>
<a name="L1203" href="source/net/ipv4/ipconfig.c#L1203">1203</a> <b><i>         * Send requests and wait, until we get an answer. This loop</i></b>
<a name="L1204" href="source/net/ipv4/ipconfig.c#L1204">1204</a> <b><i>         * seems to be a terrible waste of CPU time, but actually there is</i></b>
<a name="L1205" href="source/net/ipv4/ipconfig.c#L1205">1205</a> <b><i>         * only one process running at all, so we don't need to use any</i></b>
<a name="L1206" href="source/net/ipv4/ipconfig.c#L1206">1206</a> <b><i>         * scheduler functions.</i></b>
<a name="L1207" href="source/net/ipv4/ipconfig.c#L1207">1207</a> <b><i>         * [Actually we could now, but the nothing else running note still</i></b>
<a name="L1208" href="source/net/ipv4/ipconfig.c#L1208">1208</a> <b><i>         *  applies.. - AC]</i></b>
<a name="L1209" href="source/net/ipv4/ipconfig.c#L1209">1209</a> <b><i>         */</i></b>
<a name="L1210" href="source/net/ipv4/ipconfig.c#L1210">1210</a>         <a href="ident?i=pr_notice">pr_notice</a>(<i>"Sending %s%s%s requests ."</i>,
<a name="L1211" href="source/net/ipv4/ipconfig.c#L1211">1211</a>                   do_bootp
<a name="L1212" href="source/net/ipv4/ipconfig.c#L1212">1212</a>                   ? ((<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>) ? <i>"DHCP"</i> : <i>"BOOTP"</i>) : <i>""</i>,
<a name="L1213" href="source/net/ipv4/ipconfig.c#L1213">1213</a>                   (do_bootp &amp;&amp; do_rarp) ? <i>" and "</i> : <i>""</i>,
<a name="L1214" href="source/net/ipv4/ipconfig.c#L1214">1214</a>                   do_rarp ? <i>"RARP"</i> : <i>""</i>);
<a name="L1215" href="source/net/ipv4/ipconfig.c#L1215">1215</a> 
<a name="L1216" href="source/net/ipv4/ipconfig.c#L1216">1216</a>         start_jiffies = <a href="ident?i=jiffies">jiffies</a>;
<a name="L1217" href="source/net/ipv4/ipconfig.c#L1217">1217</a>         <a href="ident?i=d">d</a> = ic_first_dev;
<a name="L1218" href="source/net/ipv4/ipconfig.c#L1218">1218</a>         <a href="ident?i=retries">retries</a> = <a href="ident?i=CONF_SEND_RETRIES">CONF_SEND_RETRIES</a>;
<a name="L1219" href="source/net/ipv4/ipconfig.c#L1219">1219</a>         <a href="ident?i=get_random_bytes">get_random_bytes</a>(&amp;<a href="ident?i=timeout">timeout</a>, sizeof(<a href="ident?i=timeout">timeout</a>));
<a name="L1220" href="source/net/ipv4/ipconfig.c#L1220">1220</a>         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=CONF_BASE_TIMEOUT">CONF_BASE_TIMEOUT</a> + (<a href="ident?i=timeout">timeout</a> % (unsigned int) <a href="ident?i=CONF_TIMEOUT_RANDOM">CONF_TIMEOUT_RANDOM</a>);
<a name="L1221" href="source/net/ipv4/ipconfig.c#L1221">1221</a>         for (;;) {
<a name="L1222" href="source/net/ipv4/ipconfig.c#L1222">1222</a> #ifdef <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
<a name="L1223" href="source/net/ipv4/ipconfig.c#L1223">1223</a>                 <b><i>/* Track the device we are configuring */</i></b>
<a name="L1224" href="source/net/ipv4/ipconfig.c#L1224">1224</a>                 <a href="ident?i=ic_dev_xid">ic_dev_xid</a> = <a href="ident?i=d">d</a>-&gt;xid;
<a name="L1225" href="source/net/ipv4/ipconfig.c#L1225">1225</a> 
<a name="L1226" href="source/net/ipv4/ipconfig.c#L1226">1226</a>                 if (do_bootp &amp;&amp; (<a href="ident?i=d">d</a>-&gt;able &amp; <a href="ident?i=IC_BOOTP">IC_BOOTP</a>))
<a name="L1227" href="source/net/ipv4/ipconfig.c#L1227">1227</a>                         <a href="ident?i=ic_bootp_send_if">ic_bootp_send_if</a>(<a href="ident?i=d">d</a>, <a href="ident?i=jiffies">jiffies</a> - start_jiffies);
<a name="L1228" href="source/net/ipv4/ipconfig.c#L1228">1228</a> #endif
<a name="L1229" href="source/net/ipv4/ipconfig.c#L1229">1229</a> #ifdef <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
<a name="L1230" href="source/net/ipv4/ipconfig.c#L1230">1230</a>                 if (do_rarp &amp;&amp; (<a href="ident?i=d">d</a>-&gt;able &amp; <a href="ident?i=IC_RARP">IC_RARP</a>))
<a name="L1231" href="source/net/ipv4/ipconfig.c#L1231">1231</a>                         <a href="ident?i=ic_rarp_send_if">ic_rarp_send_if</a>(<a href="ident?i=d">d</a>);
<a name="L1232" href="source/net/ipv4/ipconfig.c#L1232">1232</a> #endif
<a name="L1233" href="source/net/ipv4/ipconfig.c#L1233">1233</a> 
<a name="L1234" href="source/net/ipv4/ipconfig.c#L1234">1234</a>                 jiff = <a href="ident?i=jiffies">jiffies</a> + (<a href="ident?i=d">d</a>-&gt;<a href="ident?i=next">next</a> ? <a href="ident?i=CONF_INTER_TIMEOUT">CONF_INTER_TIMEOUT</a> : <a href="ident?i=timeout">timeout</a>);
<a name="L1235" href="source/net/ipv4/ipconfig.c#L1235">1235</a>                 while (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, jiff) &amp;&amp; !ic_got_reply)
<a name="L1236" href="source/net/ipv4/ipconfig.c#L1236">1236</a>                         <a href="ident?i=schedule_timeout_uninterruptible">schedule_timeout_uninterruptible</a>(1);
<a name="L1237" href="source/net/ipv4/ipconfig.c#L1237">1237</a> #ifdef <a href="ident?i=IPCONFIG_DHCP">IPCONFIG_DHCP</a>
<a name="L1238" href="source/net/ipv4/ipconfig.c#L1238">1238</a>                 <b><i>/* DHCP isn't done until we get a DHCPACK. */</i></b>
<a name="L1239" href="source/net/ipv4/ipconfig.c#L1239">1239</a>                 if ((ic_got_reply &amp; <a href="ident?i=IC_BOOTP">IC_BOOTP</a>) &amp;&amp;
<a name="L1240" href="source/net/ipv4/ipconfig.c#L1240">1240</a>                     (<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>) &amp;&amp;
<a name="L1241" href="source/net/ipv4/ipconfig.c#L1241">1241</a>                     ic_dhcp_msgtype != <a href="ident?i=DHCPACK">DHCPACK</a>) {
<a name="L1242" href="source/net/ipv4/ipconfig.c#L1242">1242</a>                         ic_got_reply = 0;
<a name="L1243" href="source/net/ipv4/ipconfig.c#L1243">1243</a>                         <a href="ident?i=pr_cont">pr_cont</a>(<i>","</i>);
<a name="L1244" href="source/net/ipv4/ipconfig.c#L1244">1244</a>                         continue;
<a name="L1245" href="source/net/ipv4/ipconfig.c#L1245">1245</a>                 }
<a name="L1246" href="source/net/ipv4/ipconfig.c#L1246">1246</a> #endif <b><i>/* IPCONFIG_DHCP */</i></b>
<a name="L1247" href="source/net/ipv4/ipconfig.c#L1247">1247</a> 
<a name="L1248" href="source/net/ipv4/ipconfig.c#L1248">1248</a>                 if (ic_got_reply) {
<a name="L1249" href="source/net/ipv4/ipconfig.c#L1249">1249</a>                         <a href="ident?i=pr_cont">pr_cont</a>(<i>" OK\n"</i>);
<a name="L1250" href="source/net/ipv4/ipconfig.c#L1250">1250</a>                         break;
<a name="L1251" href="source/net/ipv4/ipconfig.c#L1251">1251</a>                 }
<a name="L1252" href="source/net/ipv4/ipconfig.c#L1252">1252</a> 
<a name="L1253" href="source/net/ipv4/ipconfig.c#L1253">1253</a>                 if ((<a href="ident?i=d">d</a> = <a href="ident?i=d">d</a>-&gt;<a href="ident?i=next">next</a>))
<a name="L1254" href="source/net/ipv4/ipconfig.c#L1254">1254</a>                         continue;
<a name="L1255" href="source/net/ipv4/ipconfig.c#L1255">1255</a> 
<a name="L1256" href="source/net/ipv4/ipconfig.c#L1256">1256</a>                 if (! --<a href="ident?i=retries">retries</a>) {
<a name="L1257" href="source/net/ipv4/ipconfig.c#L1257">1257</a>                         <a href="ident?i=pr_cont">pr_cont</a>(<i>" timed out!\n"</i>);
<a name="L1258" href="source/net/ipv4/ipconfig.c#L1258">1258</a>                         break;
<a name="L1259" href="source/net/ipv4/ipconfig.c#L1259">1259</a>                 }
<a name="L1260" href="source/net/ipv4/ipconfig.c#L1260">1260</a> 
<a name="L1261" href="source/net/ipv4/ipconfig.c#L1261">1261</a>                 <a href="ident?i=d">d</a> = ic_first_dev;
<a name="L1262" href="source/net/ipv4/ipconfig.c#L1262">1262</a> 
<a name="L1263" href="source/net/ipv4/ipconfig.c#L1263">1263</a>                 <a href="ident?i=timeout">timeout</a> = <a href="ident?i=timeout">timeout</a> <a href="ident?i=CONF_TIMEOUT_MULT">CONF_TIMEOUT_MULT</a>;
<a name="L1264" href="source/net/ipv4/ipconfig.c#L1264">1264</a>                 if (<a href="ident?i=timeout">timeout</a> &gt; <a href="ident?i=CONF_TIMEOUT_MAX">CONF_TIMEOUT_MAX</a>)
<a name="L1265" href="source/net/ipv4/ipconfig.c#L1265">1265</a>                         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=CONF_TIMEOUT_MAX">CONF_TIMEOUT_MAX</a>;
<a name="L1266" href="source/net/ipv4/ipconfig.c#L1266">1266</a> 
<a name="L1267" href="source/net/ipv4/ipconfig.c#L1267">1267</a>                 <a href="ident?i=pr_cont">pr_cont</a>(<i>"."</i>);
<a name="L1268" href="source/net/ipv4/ipconfig.c#L1268">1268</a>         }
<a name="L1269" href="source/net/ipv4/ipconfig.c#L1269">1269</a> 
<a name="L1270" href="source/net/ipv4/ipconfig.c#L1270">1270</a> #ifdef <a href="ident?i=IPCONFIG_BOOTP">IPCONFIG_BOOTP</a>
<a name="L1271" href="source/net/ipv4/ipconfig.c#L1271">1271</a>         if (do_bootp)
<a name="L1272" href="source/net/ipv4/ipconfig.c#L1272">1272</a>                 <a href="ident?i=ic_bootp_cleanup">ic_bootp_cleanup</a>();
<a name="L1273" href="source/net/ipv4/ipconfig.c#L1273">1273</a> #endif
<a name="L1274" href="source/net/ipv4/ipconfig.c#L1274">1274</a> #ifdef <a href="ident?i=IPCONFIG_RARP">IPCONFIG_RARP</a>
<a name="L1275" href="source/net/ipv4/ipconfig.c#L1275">1275</a>         if (do_rarp)
<a name="L1276" href="source/net/ipv4/ipconfig.c#L1276">1276</a>                 <a href="ident?i=ic_rarp_cleanup">ic_rarp_cleanup</a>();
<a name="L1277" href="source/net/ipv4/ipconfig.c#L1277">1277</a> #endif
<a name="L1278" href="source/net/ipv4/ipconfig.c#L1278">1278</a> 
<a name="L1279" href="source/net/ipv4/ipconfig.c#L1279">1279</a>         if (!ic_got_reply) {
<a name="L1280" href="source/net/ipv4/ipconfig.c#L1280">1280</a>                 <a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1281" href="source/net/ipv4/ipconfig.c#L1281">1281</a>                 return -1;
<a name="L1282" href="source/net/ipv4/ipconfig.c#L1282">1282</a>         }
<a name="L1283" href="source/net/ipv4/ipconfig.c#L1283">1283</a> 
<a name="L1284" href="source/net/ipv4/ipconfig.c#L1284">1284</a>         <a href="ident?i=printk">printk</a>(<i>"IP-Config: Got %s answer from %pI4, "</i>,
<a name="L1285" href="source/net/ipv4/ipconfig.c#L1285">1285</a>                 ((ic_got_reply &amp; <a href="ident?i=IC_RARP">IC_RARP</a>) ? <i>"RARP"</i>
<a name="L1286" href="source/net/ipv4/ipconfig.c#L1286">1286</a>                  : (<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>) ? <i>"DHCP"</i> : <i>"BOOTP"</i>),
<a name="L1287" href="source/net/ipv4/ipconfig.c#L1287">1287</a>                &amp;<a href="ident?i=ic_addrservaddr">ic_addrservaddr</a>);
<a name="L1288" href="source/net/ipv4/ipconfig.c#L1288">1288</a>         <a href="ident?i=pr_cont">pr_cont</a>(<i>"my address is %pI4\n"</i>, &amp;<a href="ident?i=ic_myaddr">ic_myaddr</a>);
<a name="L1289" href="source/net/ipv4/ipconfig.c#L1289">1289</a> 
<a name="L1290" href="source/net/ipv4/ipconfig.c#L1290">1290</a>         return 0;
<a name="L1291" href="source/net/ipv4/ipconfig.c#L1291">1291</a> }
<a name="L1292" href="source/net/ipv4/ipconfig.c#L1292">1292</a> 
<a name="L1293" href="source/net/ipv4/ipconfig.c#L1293">1293</a> #endif <b><i>/* IPCONFIG_DYNAMIC */</i></b>
<a name="L1294" href="source/net/ipv4/ipconfig.c#L1294">1294</a> 
<a name="L1295" href="source/net/ipv4/ipconfig.c#L1295">1295</a> #ifdef CONFIG_PROC_FS
<a name="L1296" href="source/net/ipv4/ipconfig.c#L1296">1296</a> 
<a name="L1297" href="source/net/ipv4/ipconfig.c#L1297">1297</a> static int <a href="ident?i=pnp_seq_show">pnp_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L1298" href="source/net/ipv4/ipconfig.c#L1298">1298</a> {
<a name="L1299" href="source/net/ipv4/ipconfig.c#L1299">1299</a>         int <a href="ident?i=i">i</a>;
<a name="L1300" href="source/net/ipv4/ipconfig.c#L1300">1300</a> 
<a name="L1301" href="source/net/ipv4/ipconfig.c#L1301">1301</a>         if (<a href="ident?i=ic_proto_used">ic_proto_used</a> &amp; <a href="ident?i=IC_PROTO">IC_PROTO</a>)
<a name="L1302" href="source/net/ipv4/ipconfig.c#L1302">1302</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"#PROTO: %s\n"</i>,
<a name="L1303" href="source/net/ipv4/ipconfig.c#L1303">1303</a>                            (<a href="ident?i=ic_proto_used">ic_proto_used</a> &amp; <a href="ident?i=IC_RARP">IC_RARP</a>) ? <i>"RARP"</i>
<a name="L1304" href="source/net/ipv4/ipconfig.c#L1304">1304</a>                            : (<a href="ident?i=ic_proto_used">ic_proto_used</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>) ? <i>"DHCP"</i> : <i>"BOOTP"</i>);
<a name="L1305" href="source/net/ipv4/ipconfig.c#L1305">1305</a>         else
<a name="L1306" href="source/net/ipv4/ipconfig.c#L1306">1306</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"#MANUAL\n"</i>);
<a name="L1307" href="source/net/ipv4/ipconfig.c#L1307">1307</a> 
<a name="L1308" href="source/net/ipv4/ipconfig.c#L1308">1308</a>         if (<a href="ident?i=ic_domain">ic_domain</a>[0])
<a name="L1309" href="source/net/ipv4/ipconfig.c#L1309">1309</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L1310" href="source/net/ipv4/ipconfig.c#L1310">1310</a>                            <i>"domain %s\n"</i>, <a href="ident?i=ic_domain">ic_domain</a>);
<a name="L1311" href="source/net/ipv4/ipconfig.c#L1311">1311</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>; <a href="ident?i=i">i</a>++) {
<a name="L1312" href="source/net/ipv4/ipconfig.c#L1312">1312</a>                 if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>] != <a href="ident?i=NONE">NONE</a>)
<a name="L1313" href="source/net/ipv4/ipconfig.c#L1313">1313</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"nameserver %pI4\n"</i>,
<a name="L1314" href="source/net/ipv4/ipconfig.c#L1314">1314</a>                                    &amp;<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>]);
<a name="L1315" href="source/net/ipv4/ipconfig.c#L1315">1315</a>         }
<a name="L1316" href="source/net/ipv4/ipconfig.c#L1316">1316</a>         if (<a href="ident?i=ic_servaddr">ic_servaddr</a> != <a href="ident?i=NONE">NONE</a>)
<a name="L1317" href="source/net/ipv4/ipconfig.c#L1317">1317</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"bootserver %pI4\n"</i>,
<a name="L1318" href="source/net/ipv4/ipconfig.c#L1318">1318</a>                            &amp;<a href="ident?i=ic_servaddr">ic_servaddr</a>);
<a name="L1319" href="source/net/ipv4/ipconfig.c#L1319">1319</a>         return 0;
<a name="L1320" href="source/net/ipv4/ipconfig.c#L1320">1320</a> }
<a name="L1321" href="source/net/ipv4/ipconfig.c#L1321">1321</a> 
<a name="L1322" href="source/net/ipv4/ipconfig.c#L1322">1322</a> static int <a href="ident?i=pnp_seq_open">pnp_seq_open</a>(struct <a href="ident?i=inode">inode</a> *indoe, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L1323" href="source/net/ipv4/ipconfig.c#L1323">1323</a> {
<a name="L1324" href="source/net/ipv4/ipconfig.c#L1324">1324</a>         return <a href="ident?i=single_open">single_open</a>(<a href="ident?i=file">file</a>, <a href="ident?i=pnp_seq_show">pnp_seq_show</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1325" href="source/net/ipv4/ipconfig.c#L1325">1325</a> }
<a name="L1326" href="source/net/ipv4/ipconfig.c#L1326">1326</a> 
<a name="L1327" href="source/net/ipv4/ipconfig.c#L1327">1327</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=pnp_seq_fops">pnp_seq_fops</a> = {
<a name="L1328" href="source/net/ipv4/ipconfig.c#L1328">1328</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L1329" href="source/net/ipv4/ipconfig.c#L1329">1329</a>         .<a href="ident?i=open">open</a>           = <a href="ident?i=pnp_seq_open">pnp_seq_open</a>,
<a name="L1330" href="source/net/ipv4/ipconfig.c#L1330">1330</a>         .<a href="ident?i=read">read</a>           = <a href="ident?i=seq_read">seq_read</a>,
<a name="L1331" href="source/net/ipv4/ipconfig.c#L1331">1331</a>         .llseek         = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L1332" href="source/net/ipv4/ipconfig.c#L1332">1332</a>         .<a href="ident?i=release">release</a>        = <a href="ident?i=single_release">single_release</a>,
<a name="L1333" href="source/net/ipv4/ipconfig.c#L1333">1333</a> };
<a name="L1334" href="source/net/ipv4/ipconfig.c#L1334">1334</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1335" href="source/net/ipv4/ipconfig.c#L1335">1335</a> 
<a name="L1336" href="source/net/ipv4/ipconfig.c#L1336">1336</a> <b><i>/*</i></b>
<a name="L1337" href="source/net/ipv4/ipconfig.c#L1337">1337</a> <b><i> *  Extract IP address from the parameter string if needed. Note that we</i></b>
<a name="L1338" href="source/net/ipv4/ipconfig.c#L1338">1338</a> <b><i> *  need to have root_server_addr set _before_ IPConfig gets called as it</i></b>
<a name="L1339" href="source/net/ipv4/ipconfig.c#L1339">1339</a> <b><i> *  can override it.</i></b>
<a name="L1340" href="source/net/ipv4/ipconfig.c#L1340">1340</a> <b><i> */</i></b>
<a name="L1341" href="source/net/ipv4/ipconfig.c#L1341">1341</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=__init">__init</a> <a href="ident?i=root_nfs_parse_addr">root_nfs_parse_addr</a>(char *<a href="ident?i=name">name</a>)
<a name="L1342" href="source/net/ipv4/ipconfig.c#L1342">1342</a> {
<a name="L1343" href="source/net/ipv4/ipconfig.c#L1343">1343</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>;
<a name="L1344" href="source/net/ipv4/ipconfig.c#L1344">1344</a>         int octets = 0;
<a name="L1345" href="source/net/ipv4/ipconfig.c#L1345">1345</a>         char *<a href="ident?i=cp">cp</a>, *cq;
<a name="L1346" href="source/net/ipv4/ipconfig.c#L1346">1346</a> 
<a name="L1347" href="source/net/ipv4/ipconfig.c#L1347">1347</a>         <a href="ident?i=cp">cp</a> = cq = <a href="ident?i=name">name</a>;
<a name="L1348" href="source/net/ipv4/ipconfig.c#L1348">1348</a>         while (octets &lt; 4) {
<a name="L1349" href="source/net/ipv4/ipconfig.c#L1349">1349</a>                 while (*<a href="ident?i=cp">cp</a> &gt;= <i>''</i> &amp;&amp; *<a href="ident?i=cp">cp</a> &lt;= <i>'9'</i>)
<a name="L1350" href="source/net/ipv4/ipconfig.c#L1350">1350</a>                         <a href="ident?i=cp">cp</a>++;
<a name="L1351" href="source/net/ipv4/ipconfig.c#L1351">1351</a>                 if (<a href="ident?i=cp">cp</a> == cq || <a href="ident?i=cp">cp</a> - cq &gt; 3)
<a name="L1352" href="source/net/ipv4/ipconfig.c#L1352">1352</a>                         break;
<a name="L1353" href="source/net/ipv4/ipconfig.c#L1353">1353</a>                 if (*<a href="ident?i=cp">cp</a> == <i>'.'</i> || octets == 3)
<a name="L1354" href="source/net/ipv4/ipconfig.c#L1354">1354</a>                         octets++;
<a name="L1355" href="source/net/ipv4/ipconfig.c#L1355">1355</a>                 if (octets &lt; 4)
<a name="L1356" href="source/net/ipv4/ipconfig.c#L1356">1356</a>                         <a href="ident?i=cp">cp</a>++;
<a name="L1357" href="source/net/ipv4/ipconfig.c#L1357">1357</a>                 cq = <a href="ident?i=cp">cp</a>;
<a name="L1358" href="source/net/ipv4/ipconfig.c#L1358">1358</a>         }
<a name="L1359" href="source/net/ipv4/ipconfig.c#L1359">1359</a>         if (octets == 4 &amp;&amp; (*<a href="ident?i=cp">cp</a> == <i>':'</i> || *<a href="ident?i=cp">cp</a> == <i>'\0'</i>)) {
<a name="L1360" href="source/net/ipv4/ipconfig.c#L1360">1360</a>                 if (*<a href="ident?i=cp">cp</a> == <i>':'</i>)
<a name="L1361" href="source/net/ipv4/ipconfig.c#L1361">1361</a>                         *<a href="ident?i=cp">cp</a>++ = <i>'\0'</i>;
<a name="L1362" href="source/net/ipv4/ipconfig.c#L1362">1362</a>                 <a href="ident?i=addr">addr</a> = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=name">name</a>);
<a name="L1363" href="source/net/ipv4/ipconfig.c#L1363">1363</a>                 <a href="ident?i=memmove">memmove</a>(<a href="ident?i=name">name</a>, <a href="ident?i=cp">cp</a>, <a href="ident?i=strlen">strlen</a>(<a href="ident?i=cp">cp</a>) + 1);
<a name="L1364" href="source/net/ipv4/ipconfig.c#L1364">1364</a>         } else
<a name="L1365" href="source/net/ipv4/ipconfig.c#L1365">1365</a>                 <a href="ident?i=addr">addr</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1366" href="source/net/ipv4/ipconfig.c#L1366">1366</a> 
<a name="L1367" href="source/net/ipv4/ipconfig.c#L1367">1367</a>         return <a href="ident?i=addr">addr</a>;
<a name="L1368" href="source/net/ipv4/ipconfig.c#L1368">1368</a> }
<a name="L1369" href="source/net/ipv4/ipconfig.c#L1369">1369</a> 
<a name="L1370" href="source/net/ipv4/ipconfig.c#L1370">1370</a> #define <a href="ident?i=DEVICE_WAIT_MAX">DEVICE_WAIT_MAX</a>         12 <b><i>/* 12 seconds */</i></b>
<a name="L1371" href="source/net/ipv4/ipconfig.c#L1371">1371</a> 
<a name="L1372" href="source/net/ipv4/ipconfig.c#L1372">1372</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=wait_for_devices">wait_for_devices</a>(void)
<a name="L1373" href="source/net/ipv4/ipconfig.c#L1373">1373</a> {
<a name="L1374" href="source/net/ipv4/ipconfig.c#L1374">1374</a>         int <a href="ident?i=i">i</a>;
<a name="L1375" href="source/net/ipv4/ipconfig.c#L1375">1375</a> 
<a name="L1376" href="source/net/ipv4/ipconfig.c#L1376">1376</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=DEVICE_WAIT_MAX">DEVICE_WAIT_MAX</a>; <a href="ident?i=i">i</a>++) {
<a name="L1377" href="source/net/ipv4/ipconfig.c#L1377">1377</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1378" href="source/net/ipv4/ipconfig.c#L1378">1378</a>                 int <a href="ident?i=found">found</a> = 0;
<a name="L1379" href="source/net/ipv4/ipconfig.c#L1379">1379</a> 
<a name="L1380" href="source/net/ipv4/ipconfig.c#L1380">1380</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1381" href="source/net/ipv4/ipconfig.c#L1381">1381</a>                 <a href="ident?i=for_each_netdev">for_each_netdev</a>(&amp;<a href="ident?i=init_net">init_net</a>, <a href="ident?i=dev">dev</a>) {
<a name="L1382" href="source/net/ipv4/ipconfig.c#L1382">1382</a>                         if (<a href="ident?i=ic_is_init_dev">ic_is_init_dev</a>(<a href="ident?i=dev">dev</a>)) {
<a name="L1383" href="source/net/ipv4/ipconfig.c#L1383">1383</a>                                 <a href="ident?i=found">found</a> = 1;
<a name="L1384" href="source/net/ipv4/ipconfig.c#L1384">1384</a>                                 break;
<a name="L1385" href="source/net/ipv4/ipconfig.c#L1385">1385</a>                         }
<a name="L1386" href="source/net/ipv4/ipconfig.c#L1386">1386</a>                 }
<a name="L1387" href="source/net/ipv4/ipconfig.c#L1387">1387</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1388" href="source/net/ipv4/ipconfig.c#L1388">1388</a>                 if (<a href="ident?i=found">found</a>)
<a name="L1389" href="source/net/ipv4/ipconfig.c#L1389">1389</a>                         return 0;
<a name="L1390" href="source/net/ipv4/ipconfig.c#L1390">1390</a>                 <a href="ident?i=ssleep">ssleep</a>(1);
<a name="L1391" href="source/net/ipv4/ipconfig.c#L1391">1391</a>         }
<a name="L1392" href="source/net/ipv4/ipconfig.c#L1392">1392</a>         return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1393" href="source/net/ipv4/ipconfig.c#L1393">1393</a> }
<a name="L1394" href="source/net/ipv4/ipconfig.c#L1394">1394</a> 
<a name="L1395" href="source/net/ipv4/ipconfig.c#L1395">1395</a> <b><i>/*</i></b>
<a name="L1396" href="source/net/ipv4/ipconfig.c#L1396">1396</a> <b><i> *      IP Autoconfig dispatcher.</i></b>
<a name="L1397" href="source/net/ipv4/ipconfig.c#L1397">1397</a> <b><i> */</i></b>
<a name="L1398" href="source/net/ipv4/ipconfig.c#L1398">1398</a> 
<a name="L1399" href="source/net/ipv4/ipconfig.c#L1399">1399</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_auto_config">ip_auto_config</a>(void)
<a name="L1400" href="source/net/ipv4/ipconfig.c#L1400">1400</a> {
<a name="L1401" href="source/net/ipv4/ipconfig.c#L1401">1401</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>;
<a name="L1402" href="source/net/ipv4/ipconfig.c#L1402">1402</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L1403" href="source/net/ipv4/ipconfig.c#L1403">1403</a>         int <a href="ident?i=retries">retries</a> = <a href="ident?i=CONF_OPEN_RETRIES">CONF_OPEN_RETRIES</a>;
<a name="L1404" href="source/net/ipv4/ipconfig.c#L1404">1404</a> #endif
<a name="L1405" href="source/net/ipv4/ipconfig.c#L1405">1405</a>         int <a href="ident?i=err">err</a>;
<a name="L1406" href="source/net/ipv4/ipconfig.c#L1406">1406</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L1407" href="source/net/ipv4/ipconfig.c#L1407">1407</a> 
<a name="L1408" href="source/net/ipv4/ipconfig.c#L1408">1408</a> #ifdef CONFIG_PROC_FS
<a name="L1409" href="source/net/ipv4/ipconfig.c#L1409">1409</a>         <a href="ident?i=proc_create">proc_create</a>(<i>"pnp"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=init_net">init_net</a>.proc_net, &amp;<a href="ident?i=pnp_seq_fops">pnp_seq_fops</a>);
<a name="L1410" href="source/net/ipv4/ipconfig.c#L1410">1410</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1411" href="source/net/ipv4/ipconfig.c#L1411">1411</a> 
<a name="L1412" href="source/net/ipv4/ipconfig.c#L1412">1412</a>         if (!ic_enable)
<a name="L1413" href="source/net/ipv4/ipconfig.c#L1413">1413</a>                 return 0;
<a name="L1414" href="source/net/ipv4/ipconfig.c#L1414">1414</a> 
<a name="L1415" href="source/net/ipv4/ipconfig.c#L1415">1415</a>         <a href="ident?i=DBG">DBG</a>((<i>"IP-Config: Entered.\n"</i>));
<a name="L1416" href="source/net/ipv4/ipconfig.c#L1416">1416</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L1417" href="source/net/ipv4/ipconfig.c#L1417">1417</a>  try_try_again:
<a name="L1418" href="source/net/ipv4/ipconfig.c#L1418">1418</a> #endif
<a name="L1419" href="source/net/ipv4/ipconfig.c#L1419">1419</a>         <b><i>/* Wait for devices to appear */</i></b>
<a name="L1420" href="source/net/ipv4/ipconfig.c#L1420">1420</a>         <a href="ident?i=err">err</a> = <a href="ident?i=wait_for_devices">wait_for_devices</a>();
<a name="L1421" href="source/net/ipv4/ipconfig.c#L1421">1421</a>         if (<a href="ident?i=err">err</a>)
<a name="L1422" href="source/net/ipv4/ipconfig.c#L1422">1422</a>                 return <a href="ident?i=err">err</a>;
<a name="L1423" href="source/net/ipv4/ipconfig.c#L1423">1423</a> 
<a name="L1424" href="source/net/ipv4/ipconfig.c#L1424">1424</a>         <b><i>/* Setup all network devices */</i></b>
<a name="L1425" href="source/net/ipv4/ipconfig.c#L1425">1425</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ic_open_devs">ic_open_devs</a>();
<a name="L1426" href="source/net/ipv4/ipconfig.c#L1426">1426</a>         if (<a href="ident?i=err">err</a>)
<a name="L1427" href="source/net/ipv4/ipconfig.c#L1427">1427</a>                 return <a href="ident?i=err">err</a>;
<a name="L1428" href="source/net/ipv4/ipconfig.c#L1428">1428</a> 
<a name="L1429" href="source/net/ipv4/ipconfig.c#L1429">1429</a>         <b><i>/* Give drivers a chance to settle */</i></b>
<a name="L1430" href="source/net/ipv4/ipconfig.c#L1430">1430</a>         <a href="ident?i=msleep">msleep</a>(<a href="ident?i=CONF_POST_OPEN">CONF_POST_OPEN</a>);
<a name="L1431" href="source/net/ipv4/ipconfig.c#L1431">1431</a> 
<a name="L1432" href="source/net/ipv4/ipconfig.c#L1432">1432</a>         <b><i>/*</i></b>
<a name="L1433" href="source/net/ipv4/ipconfig.c#L1433">1433</a> <b><i>         * If the config information is insufficient (e.g., our IP address or</i></b>
<a name="L1434" href="source/net/ipv4/ipconfig.c#L1434">1434</a> <b><i>         * IP address of the boot server is missing or we have multiple network</i></b>
<a name="L1435" href="source/net/ipv4/ipconfig.c#L1435">1435</a> <b><i>         * interfaces and no default was set), use BOOTP or RARP to get the</i></b>
<a name="L1436" href="source/net/ipv4/ipconfig.c#L1436">1436</a> <b><i>         * missing values.</i></b>
<a name="L1437" href="source/net/ipv4/ipconfig.c#L1437">1437</a> <b><i>         */</i></b>
<a name="L1438" href="source/net/ipv4/ipconfig.c#L1438">1438</a>         if (<a href="ident?i=ic_myaddr">ic_myaddr</a> == <a href="ident?i=NONE">NONE</a> ||
<a name="L1439" href="source/net/ipv4/ipconfig.c#L1439">1439</a> #ifdef CONFIG_ROOT_NFS
<a name="L1440" href="source/net/ipv4/ipconfig.c#L1440">1440</a>             (<a href="ident?i=root_server_addr">root_server_addr</a> == <a href="ident?i=NONE">NONE</a> &amp;&amp;
<a name="L1441" href="source/net/ipv4/ipconfig.c#L1441">1441</a>              <a href="ident?i=ic_servaddr">ic_servaddr</a> == <a href="ident?i=NONE">NONE</a> &amp;&amp;
<a name="L1442" href="source/net/ipv4/ipconfig.c#L1442">1442</a>              <a href="ident?i=ROOT_DEV">ROOT_DEV</a> == Root_NFS) ||
<a name="L1443" href="source/net/ipv4/ipconfig.c#L1443">1443</a> #endif
<a name="L1444" href="source/net/ipv4/ipconfig.c#L1444">1444</a>             ic_first_dev-&gt;<a href="ident?i=next">next</a>) {
<a name="L1445" href="source/net/ipv4/ipconfig.c#L1445">1445</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L1446" href="source/net/ipv4/ipconfig.c#L1446">1446</a>                 if (<a href="ident?i=ic_dynamic">ic_dynamic</a>() &lt; 0) {
<a name="L1447" href="source/net/ipv4/ipconfig.c#L1447">1447</a>                         <a href="ident?i=ic_close_devs">ic_close_devs</a>();
<a name="L1448" href="source/net/ipv4/ipconfig.c#L1448">1448</a> 
<a name="L1449" href="source/net/ipv4/ipconfig.c#L1449">1449</a>                         <b><i>/*</i></b>
<a name="L1450" href="source/net/ipv4/ipconfig.c#L1450">1450</a> <b><i>                         * I don't know why, but sometimes the</i></b>
<a name="L1451" href="source/net/ipv4/ipconfig.c#L1451">1451</a> <b><i>                         * eepro100 driver (at least) gets upset and</i></b>
<a name="L1452" href="source/net/ipv4/ipconfig.c#L1452">1452</a> <b><i>                         * doesn't work the first time it's opened.</i></b>
<a name="L1453" href="source/net/ipv4/ipconfig.c#L1453">1453</a> <b><i>                         * But then if you close it and reopen it, it</i></b>
<a name="L1454" href="source/net/ipv4/ipconfig.c#L1454">1454</a> <b><i>                         * works just fine.  So we need to try that at</i></b>
<a name="L1455" href="source/net/ipv4/ipconfig.c#L1455">1455</a> <b><i>                         * least once before giving up.</i></b>
<a name="L1456" href="source/net/ipv4/ipconfig.c#L1456">1456</a> <b><i>                         *</i></b>
<a name="L1457" href="source/net/ipv4/ipconfig.c#L1457">1457</a> <b><i>                         * Also, if the root will be NFS-mounted, we</i></b>
<a name="L1458" href="source/net/ipv4/ipconfig.c#L1458">1458</a> <b><i>                         * have nowhere to go if DHCP fails.  So we</i></b>
<a name="L1459" href="source/net/ipv4/ipconfig.c#L1459">1459</a> <b><i>                         * just have to keep trying forever.</i></b>
<a name="L1460" href="source/net/ipv4/ipconfig.c#L1460">1460</a> <b><i>                         *</i></b>
<a name="L1461" href="source/net/ipv4/ipconfig.c#L1461">1461</a> <b><i>                         *                              -- Chip</i></b>
<a name="L1462" href="source/net/ipv4/ipconfig.c#L1462">1462</a> <b><i>                         */</i></b>
<a name="L1463" href="source/net/ipv4/ipconfig.c#L1463">1463</a> #ifdef CONFIG_ROOT_NFS
<a name="L1464" href="source/net/ipv4/ipconfig.c#L1464">1464</a>                         if (<a href="ident?i=ROOT_DEV">ROOT_DEV</a> ==  Root_NFS) {
<a name="L1465" href="source/net/ipv4/ipconfig.c#L1465">1465</a>                                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Retrying forever (NFS root)...\n"</i>);
<a name="L1466" href="source/net/ipv4/ipconfig.c#L1466">1466</a>                                 goto try_try_again;
<a name="L1467" href="source/net/ipv4/ipconfig.c#L1467">1467</a>                         }
<a name="L1468" href="source/net/ipv4/ipconfig.c#L1468">1468</a> #endif
<a name="L1469" href="source/net/ipv4/ipconfig.c#L1469">1469</a> 
<a name="L1470" href="source/net/ipv4/ipconfig.c#L1470">1470</a>                         if (--<a href="ident?i=retries">retries</a>) {
<a name="L1471" href="source/net/ipv4/ipconfig.c#L1471">1471</a>                                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Reopening network devices...\n"</i>);
<a name="L1472" href="source/net/ipv4/ipconfig.c#L1472">1472</a>                                 goto try_try_again;
<a name="L1473" href="source/net/ipv4/ipconfig.c#L1473">1473</a>                         }
<a name="L1474" href="source/net/ipv4/ipconfig.c#L1474">1474</a> 
<a name="L1475" href="source/net/ipv4/ipconfig.c#L1475">1475</a>                         <b><i>/* Oh, well.  At least we tried. */</i></b>
<a name="L1476" href="source/net/ipv4/ipconfig.c#L1476">1476</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Auto-configuration of network failed\n"</i>);
<a name="L1477" href="source/net/ipv4/ipconfig.c#L1477">1477</a>                         return -1;
<a name="L1478" href="source/net/ipv4/ipconfig.c#L1478">1478</a>                 }
<a name="L1479" href="source/net/ipv4/ipconfig.c#L1479">1479</a> #else <b><i>/* !DYNAMIC */</i></b>
<a name="L1480" href="source/net/ipv4/ipconfig.c#L1480">1480</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"IP-Config: Incomplete network configuration information\n"</i>);
<a name="L1481" href="source/net/ipv4/ipconfig.c#L1481">1481</a>                 <a href="ident?i=ic_close_devs">ic_close_devs</a>();
<a name="L1482" href="source/net/ipv4/ipconfig.c#L1482">1482</a>                 return -1;
<a name="L1483" href="source/net/ipv4/ipconfig.c#L1483">1483</a> #endif <b><i>/* IPCONFIG_DYNAMIC */</i></b>
<a name="L1484" href="source/net/ipv4/ipconfig.c#L1484">1484</a>         } else {
<a name="L1485" href="source/net/ipv4/ipconfig.c#L1485">1485</a>                 <b><i>/* Device selected manually or only one device -&gt; use it */</i></b>
<a name="L1486" href="source/net/ipv4/ipconfig.c#L1486">1486</a>                 ic_dev = ic_first_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L1487" href="source/net/ipv4/ipconfig.c#L1487">1487</a>         }
<a name="L1488" href="source/net/ipv4/ipconfig.c#L1488">1488</a> 
<a name="L1489" href="source/net/ipv4/ipconfig.c#L1489">1489</a>         <a href="ident?i=addr">addr</a> = <a href="ident?i=root_nfs_parse_addr">root_nfs_parse_addr</a>(<a href="ident?i=root_server_path">root_server_path</a>);
<a name="L1490" href="source/net/ipv4/ipconfig.c#L1490">1490</a>         if (<a href="ident?i=root_server_addr">root_server_addr</a> == <a href="ident?i=NONE">NONE</a>)
<a name="L1491" href="source/net/ipv4/ipconfig.c#L1491">1491</a>                 <a href="ident?i=root_server_addr">root_server_addr</a> = <a href="ident?i=addr">addr</a>;
<a name="L1492" href="source/net/ipv4/ipconfig.c#L1492">1492</a> 
<a name="L1493" href="source/net/ipv4/ipconfig.c#L1493">1493</a>         <b><i>/*</i></b>
<a name="L1494" href="source/net/ipv4/ipconfig.c#L1494">1494</a> <b><i>         * Use defaults wherever applicable.</i></b>
<a name="L1495" href="source/net/ipv4/ipconfig.c#L1495">1495</a> <b><i>         */</i></b>
<a name="L1496" href="source/net/ipv4/ipconfig.c#L1496">1496</a>         if (<a href="ident?i=ic_defaults">ic_defaults</a>() &lt; 0)
<a name="L1497" href="source/net/ipv4/ipconfig.c#L1497">1497</a>                 return -1;
<a name="L1498" href="source/net/ipv4/ipconfig.c#L1498">1498</a> 
<a name="L1499" href="source/net/ipv4/ipconfig.c#L1499">1499</a>         <b><i>/*</i></b>
<a name="L1500" href="source/net/ipv4/ipconfig.c#L1500">1500</a> <b><i>         * Close all network devices except the device we've</i></b>
<a name="L1501" href="source/net/ipv4/ipconfig.c#L1501">1501</a> <b><i>         * autoconfigured and set up routes.</i></b>
<a name="L1502" href="source/net/ipv4/ipconfig.c#L1502">1502</a> <b><i>         */</i></b>
<a name="L1503" href="source/net/ipv4/ipconfig.c#L1503">1503</a>         <a href="ident?i=ic_close_devs">ic_close_devs</a>();
<a name="L1504" href="source/net/ipv4/ipconfig.c#L1504">1504</a>         if (<a href="ident?i=ic_setup_if">ic_setup_if</a>() &lt; 0 || <a href="ident?i=ic_setup_routes">ic_setup_routes</a>() &lt; 0)
<a name="L1505" href="source/net/ipv4/ipconfig.c#L1505">1505</a>                 return -1;
<a name="L1506" href="source/net/ipv4/ipconfig.c#L1506">1506</a> 
<a name="L1507" href="source/net/ipv4/ipconfig.c#L1507">1507</a>         <b><i>/*</i></b>
<a name="L1508" href="source/net/ipv4/ipconfig.c#L1508">1508</a> <b><i>         * Record which protocol was actually used.</i></b>
<a name="L1509" href="source/net/ipv4/ipconfig.c#L1509">1509</a> <b><i>         */</i></b>
<a name="L1510" href="source/net/ipv4/ipconfig.c#L1510">1510</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L1511" href="source/net/ipv4/ipconfig.c#L1511">1511</a>         <a href="ident?i=ic_proto_used">ic_proto_used</a> = ic_got_reply | (<a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp; <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>);
<a name="L1512" href="source/net/ipv4/ipconfig.c#L1512">1512</a> #endif
<a name="L1513" href="source/net/ipv4/ipconfig.c#L1513">1513</a> 
<a name="L1514" href="source/net/ipv4/ipconfig.c#L1514">1514</a> #ifndef IPCONFIG_SILENT
<a name="L1515" href="source/net/ipv4/ipconfig.c#L1515">1515</a>         <b><i>/*</i></b>
<a name="L1516" href="source/net/ipv4/ipconfig.c#L1516">1516</a> <b><i>         * Clue in the operator.</i></b>
<a name="L1517" href="source/net/ipv4/ipconfig.c#L1517">1517</a> <b><i>         */</i></b>
<a name="L1518" href="source/net/ipv4/ipconfig.c#L1518">1518</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"IP-Config: Complete:\n"</i>);
<a name="L1519" href="source/net/ipv4/ipconfig.c#L1519">1519</a> 
<a name="L1520" href="source/net/ipv4/ipconfig.c#L1520">1520</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"     device=%s, hwaddr=%*phC, ipaddr=%pI4, mask=%pI4, gw=%pI4\n"</i>,
<a name="L1521" href="source/net/ipv4/ipconfig.c#L1521">1521</a>                 ic_dev-&gt;<a href="ident?i=name">name</a>, ic_dev-&gt;addr_len, ic_dev-&gt;dev_addr,
<a name="L1522" href="source/net/ipv4/ipconfig.c#L1522">1522</a>                 &amp;<a href="ident?i=ic_myaddr">ic_myaddr</a>, &amp;<a href="ident?i=ic_netmask">ic_netmask</a>, &amp;<a href="ident?i=ic_gateway">ic_gateway</a>);
<a name="L1523" href="source/net/ipv4/ipconfig.c#L1523">1523</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"     host=%s, domain=%s, nis-domain=%s\n"</i>,
<a name="L1524" href="source/net/ipv4/ipconfig.c#L1524">1524</a>                 <a href="ident?i=utsname">utsname</a>()-&gt;nodename, <a href="ident?i=ic_domain">ic_domain</a>, <a href="ident?i=utsname">utsname</a>()-&gt;domainname);
<a name="L1525" href="source/net/ipv4/ipconfig.c#L1525">1525</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"     bootserver=%pI4, rootserver=%pI4, rootpath=%s"</i>,
<a name="L1526" href="source/net/ipv4/ipconfig.c#L1526">1526</a>                 &amp;<a href="ident?i=ic_servaddr">ic_servaddr</a>, &amp;<a href="ident?i=root_server_addr">root_server_addr</a>, <a href="ident?i=root_server_path">root_server_path</a>);
<a name="L1527" href="source/net/ipv4/ipconfig.c#L1527">1527</a>         if (ic_dev_mtu)
<a name="L1528" href="source/net/ipv4/ipconfig.c#L1528">1528</a>                 <a href="ident?i=pr_cont">pr_cont</a>(<i>", mtu=%d"</i>, ic_dev_mtu);
<a name="L1529" href="source/net/ipv4/ipconfig.c#L1529">1529</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>; <a href="ident?i=i">i</a>++)
<a name="L1530" href="source/net/ipv4/ipconfig.c#L1530">1530</a>                 if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>] != <a href="ident?i=NONE">NONE</a>) {
<a name="L1531" href="source/net/ipv4/ipconfig.c#L1531">1531</a>                         <a href="ident?i=pr_info">pr_info</a>(<i>"     nameserver%u=%pI4"</i>,
<a name="L1532" href="source/net/ipv4/ipconfig.c#L1532">1532</a>                                 <a href="ident?i=i">i</a>, &amp;<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>]);
<a name="L1533" href="source/net/ipv4/ipconfig.c#L1533">1533</a>                         break;
<a name="L1534" href="source/net/ipv4/ipconfig.c#L1534">1534</a>                 }
<a name="L1535" href="source/net/ipv4/ipconfig.c#L1535">1535</a>         for (<a href="ident?i=i">i</a>++; <a href="ident?i=i">i</a> &lt; <a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a>; <a href="ident?i=i">i</a>++)
<a name="L1536" href="source/net/ipv4/ipconfig.c#L1536">1536</a>                 if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>] != <a href="ident?i=NONE">NONE</a>)
<a name="L1537" href="source/net/ipv4/ipconfig.c#L1537">1537</a>                         <a href="ident?i=pr_cont">pr_cont</a>(<i>", nameserver%u=%pI4"</i>, <a href="ident?i=i">i</a>, &amp;<a href="ident?i=ic_nameservers">ic_nameservers</a>[<a href="ident?i=i">i</a>]);
<a name="L1538" href="source/net/ipv4/ipconfig.c#L1538">1538</a>         <a href="ident?i=pr_cont">pr_cont</a>(<i>"\n"</i>);
<a name="L1539" href="source/net/ipv4/ipconfig.c#L1539">1539</a> #endif <b><i>/* !SILENT */</i></b>
<a name="L1540" href="source/net/ipv4/ipconfig.c#L1540">1540</a> 
<a name="L1541" href="source/net/ipv4/ipconfig.c#L1541">1541</a>         return 0;
<a name="L1542" href="source/net/ipv4/ipconfig.c#L1542">1542</a> }
<a name="L1543" href="source/net/ipv4/ipconfig.c#L1543">1543</a> 
<a name="L1544" href="source/net/ipv4/ipconfig.c#L1544">1544</a> <a href="ident?i=late_initcall">late_initcall</a>(<a href="ident?i=ip_auto_config">ip_auto_config</a>);
<a name="L1545" href="source/net/ipv4/ipconfig.c#L1545">1545</a> 
<a name="L1546" href="source/net/ipv4/ipconfig.c#L1546">1546</a> 
<a name="L1547" href="source/net/ipv4/ipconfig.c#L1547">1547</a> <b><i>/*</i></b>
<a name="L1548" href="source/net/ipv4/ipconfig.c#L1548">1548</a> <b><i> *  Decode any IP configuration options in the "ip=" or "nfsaddrs=" kernel</i></b>
<a name="L1549" href="source/net/ipv4/ipconfig.c#L1549">1549</a> <b><i> *  command line parameter.  See Documentation/filesystems/nfs/nfsroot.txt.</i></b>
<a name="L1550" href="source/net/ipv4/ipconfig.c#L1550">1550</a> <b><i> */</i></b>
<a name="L1551" href="source/net/ipv4/ipconfig.c#L1551">1551</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ic_proto_name">ic_proto_name</a>(char *<a href="ident?i=name">name</a>)
<a name="L1552" href="source/net/ipv4/ipconfig.c#L1552">1552</a> {
<a name="L1553" href="source/net/ipv4/ipconfig.c#L1553">1553</a>         if (!<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"on"</i>) || !<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"any"</i>)) {
<a name="L1554" href="source/net/ipv4/ipconfig.c#L1554">1554</a>                 return 1;
<a name="L1555" href="source/net/ipv4/ipconfig.c#L1555">1555</a>         }
<a name="L1556" href="source/net/ipv4/ipconfig.c#L1556">1556</a>         if (!<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"off"</i>) || !<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"none"</i>)) {
<a name="L1557" href="source/net/ipv4/ipconfig.c#L1557">1557</a>                 return 0;
<a name="L1558" href="source/net/ipv4/ipconfig.c#L1558">1558</a>         }
<a name="L1559" href="source/net/ipv4/ipconfig.c#L1559">1559</a> #ifdef CONFIG_IP_PNP_DHCP
<a name="L1560" href="source/net/ipv4/ipconfig.c#L1560">1560</a>         else if (!<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"dhcp"</i>)) {
<a name="L1561" href="source/net/ipv4/ipconfig.c#L1561">1561</a>                 <a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp;= ~IC_RARP;
<a name="L1562" href="source/net/ipv4/ipconfig.c#L1562">1562</a>                 return 1;
<a name="L1563" href="source/net/ipv4/ipconfig.c#L1563">1563</a>         }
<a name="L1564" href="source/net/ipv4/ipconfig.c#L1564">1564</a> #endif
<a name="L1565" href="source/net/ipv4/ipconfig.c#L1565">1565</a> #ifdef CONFIG_IP_PNP_BOOTP
<a name="L1566" href="source/net/ipv4/ipconfig.c#L1566">1566</a>         else if (!<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"bootp"</i>)) {
<a name="L1567" href="source/net/ipv4/ipconfig.c#L1567">1567</a>                 <a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp;= ~(<a href="ident?i=IC_RARP">IC_RARP</a> | <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>);
<a name="L1568" href="source/net/ipv4/ipconfig.c#L1568">1568</a>                 return 1;
<a name="L1569" href="source/net/ipv4/ipconfig.c#L1569">1569</a>         }
<a name="L1570" href="source/net/ipv4/ipconfig.c#L1570">1570</a> #endif
<a name="L1571" href="source/net/ipv4/ipconfig.c#L1571">1571</a> #ifdef CONFIG_IP_PNP_RARP
<a name="L1572" href="source/net/ipv4/ipconfig.c#L1572">1572</a>         else if (!<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"rarp"</i>)) {
<a name="L1573" href="source/net/ipv4/ipconfig.c#L1573">1573</a>                 <a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp;= ~(<a href="ident?i=IC_BOOTP">IC_BOOTP</a> | <a href="ident?i=IC_USE_DHCP">IC_USE_DHCP</a>);
<a name="L1574" href="source/net/ipv4/ipconfig.c#L1574">1574</a>                 return 1;
<a name="L1575" href="source/net/ipv4/ipconfig.c#L1575">1575</a>         }
<a name="L1576" href="source/net/ipv4/ipconfig.c#L1576">1576</a> #endif
<a name="L1577" href="source/net/ipv4/ipconfig.c#L1577">1577</a> #ifdef <a href="ident?i=IPCONFIG_DYNAMIC">IPCONFIG_DYNAMIC</a>
<a name="L1578" href="source/net/ipv4/ipconfig.c#L1578">1578</a>         else if (!<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=name">name</a>, <i>"both"</i>)) {
<a name="L1579" href="source/net/ipv4/ipconfig.c#L1579">1579</a>                 <a href="ident?i=ic_proto_enabled">ic_proto_enabled</a> &amp;= ~IC_USE_DHCP; <b><i>/* backward compat :-( */</i></b>
<a name="L1580" href="source/net/ipv4/ipconfig.c#L1580">1580</a>                 return 1;
<a name="L1581" href="source/net/ipv4/ipconfig.c#L1581">1581</a>         }
<a name="L1582" href="source/net/ipv4/ipconfig.c#L1582">1582</a> #endif
<a name="L1583" href="source/net/ipv4/ipconfig.c#L1583">1583</a>         return 0;
<a name="L1584" href="source/net/ipv4/ipconfig.c#L1584">1584</a> }
<a name="L1585" href="source/net/ipv4/ipconfig.c#L1585">1585</a> 
<a name="L1586" href="source/net/ipv4/ipconfig.c#L1586">1586</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_auto_config_setup">ip_auto_config_setup</a>(char *<a href="ident?i=addrs">addrs</a>)
<a name="L1587" href="source/net/ipv4/ipconfig.c#L1587">1587</a> {
<a name="L1588" href="source/net/ipv4/ipconfig.c#L1588">1588</a>         char *<a href="ident?i=cp">cp</a>, *<a href="ident?i=ip">ip</a>, *dp;
<a name="L1589" href="source/net/ipv4/ipconfig.c#L1589">1589</a>         int <a href="ident?i=num">num</a> = 0;
<a name="L1590" href="source/net/ipv4/ipconfig.c#L1590">1590</a> 
<a name="L1591" href="source/net/ipv4/ipconfig.c#L1591">1591</a>         <a href="ident?i=ic_set_manually">ic_set_manually</a> = 1;
<a name="L1592" href="source/net/ipv4/ipconfig.c#L1592">1592</a>         ic_enable = 1;
<a name="L1593" href="source/net/ipv4/ipconfig.c#L1593">1593</a> 
<a name="L1594" href="source/net/ipv4/ipconfig.c#L1594">1594</a>         <b><i>/*</i></b>
<a name="L1595" href="source/net/ipv4/ipconfig.c#L1595">1595</a> <b><i>         * If any dhcp, bootp etc options are set, leave autoconfig on</i></b>
<a name="L1596" href="source/net/ipv4/ipconfig.c#L1596">1596</a> <b><i>         * and skip the below static IP processing.</i></b>
<a name="L1597" href="source/net/ipv4/ipconfig.c#L1597">1597</a> <b><i>         */</i></b>
<a name="L1598" href="source/net/ipv4/ipconfig.c#L1598">1598</a>         if (<a href="ident?i=ic_proto_name">ic_proto_name</a>(<a href="ident?i=addrs">addrs</a>))
<a name="L1599" href="source/net/ipv4/ipconfig.c#L1599">1599</a>                 return 1;
<a name="L1600" href="source/net/ipv4/ipconfig.c#L1600">1600</a> 
<a name="L1601" href="source/net/ipv4/ipconfig.c#L1601">1601</a>         <b><i>/* If no static IP is given, turn off autoconfig and bail.  */</i></b>
<a name="L1602" href="source/net/ipv4/ipconfig.c#L1602">1602</a>         if (*<a href="ident?i=addrs">addrs</a> == 0 ||
<a name="L1603" href="source/net/ipv4/ipconfig.c#L1603">1603</a>             <a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=addrs">addrs</a>, <i>"off"</i>) == 0 ||
<a name="L1604" href="source/net/ipv4/ipconfig.c#L1604">1604</a>             <a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=addrs">addrs</a>, <i>"none"</i>) == 0) {
<a name="L1605" href="source/net/ipv4/ipconfig.c#L1605">1605</a>                 ic_enable = 0;
<a name="L1606" href="source/net/ipv4/ipconfig.c#L1606">1606</a>                 return 1;
<a name="L1607" href="source/net/ipv4/ipconfig.c#L1607">1607</a>         }
<a name="L1608" href="source/net/ipv4/ipconfig.c#L1608">1608</a> 
<a name="L1609" href="source/net/ipv4/ipconfig.c#L1609">1609</a>         <a href="ident?i=ic_nameservers_predef">ic_nameservers_predef</a>();
<a name="L1610" href="source/net/ipv4/ipconfig.c#L1610">1610</a> 
<a name="L1611" href="source/net/ipv4/ipconfig.c#L1611">1611</a>         <b><i>/* Parse string for static IP assignment.  */</i></b>
<a name="L1612" href="source/net/ipv4/ipconfig.c#L1612">1612</a>         <a href="ident?i=ip">ip</a> = <a href="ident?i=addrs">addrs</a>;
<a name="L1613" href="source/net/ipv4/ipconfig.c#L1613">1613</a>         while (<a href="ident?i=ip">ip</a> &amp;&amp; *<a href="ident?i=ip">ip</a>) {
<a name="L1614" href="source/net/ipv4/ipconfig.c#L1614">1614</a>                 if ((<a href="ident?i=cp">cp</a> = <a href="ident?i=strchr">strchr</a>(<a href="ident?i=ip">ip</a>, <i>':'</i>)))
<a name="L1615" href="source/net/ipv4/ipconfig.c#L1615">1615</a>                         *<a href="ident?i=cp">cp</a>++ = <i>'\0'</i>;
<a name="L1616" href="source/net/ipv4/ipconfig.c#L1616">1616</a>                 if (<a href="ident?i=strlen">strlen</a>(<a href="ident?i=ip">ip</a>) &gt; 0) {
<a name="L1617" href="source/net/ipv4/ipconfig.c#L1617">1617</a>                         <a href="ident?i=DBG">DBG</a>((<i>"IP-Config: Parameter #%d: `%s'\n"</i>, <a href="ident?i=num">num</a>, <a href="ident?i=ip">ip</a>));
<a name="L1618" href="source/net/ipv4/ipconfig.c#L1618">1618</a>                         switch (<a href="ident?i=num">num</a>) {
<a name="L1619" href="source/net/ipv4/ipconfig.c#L1619">1619</a>                         case 0:
<a name="L1620" href="source/net/ipv4/ipconfig.c#L1620">1620</a>                                 if ((<a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=ip">ip</a>)) == <a href="ident?i=ANY">ANY</a>)
<a name="L1621" href="source/net/ipv4/ipconfig.c#L1621">1621</a>                                         <a href="ident?i=ic_myaddr">ic_myaddr</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1622" href="source/net/ipv4/ipconfig.c#L1622">1622</a>                                 break;
<a name="L1623" href="source/net/ipv4/ipconfig.c#L1623">1623</a>                         case 1:
<a name="L1624" href="source/net/ipv4/ipconfig.c#L1624">1624</a>                                 if ((<a href="ident?i=ic_servaddr">ic_servaddr</a> = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=ip">ip</a>)) == <a href="ident?i=ANY">ANY</a>)
<a name="L1625" href="source/net/ipv4/ipconfig.c#L1625">1625</a>                                         <a href="ident?i=ic_servaddr">ic_servaddr</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1626" href="source/net/ipv4/ipconfig.c#L1626">1626</a>                                 break;
<a name="L1627" href="source/net/ipv4/ipconfig.c#L1627">1627</a>                         case 2:
<a name="L1628" href="source/net/ipv4/ipconfig.c#L1628">1628</a>                                 if ((<a href="ident?i=ic_gateway">ic_gateway</a> = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=ip">ip</a>)) == <a href="ident?i=ANY">ANY</a>)
<a name="L1629" href="source/net/ipv4/ipconfig.c#L1629">1629</a>                                         <a href="ident?i=ic_gateway">ic_gateway</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1630" href="source/net/ipv4/ipconfig.c#L1630">1630</a>                                 break;
<a name="L1631" href="source/net/ipv4/ipconfig.c#L1631">1631</a>                         case 3:
<a name="L1632" href="source/net/ipv4/ipconfig.c#L1632">1632</a>                                 if ((<a href="ident?i=ic_netmask">ic_netmask</a> = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=ip">ip</a>)) == <a href="ident?i=ANY">ANY</a>)
<a name="L1633" href="source/net/ipv4/ipconfig.c#L1633">1633</a>                                         <a href="ident?i=ic_netmask">ic_netmask</a> = <a href="ident?i=NONE">NONE</a>;
<a name="L1634" href="source/net/ipv4/ipconfig.c#L1634">1634</a>                                 break;
<a name="L1635" href="source/net/ipv4/ipconfig.c#L1635">1635</a>                         case 4:
<a name="L1636" href="source/net/ipv4/ipconfig.c#L1636">1636</a>                                 if ((dp = <a href="ident?i=strchr">strchr</a>(<a href="ident?i=ip">ip</a>, <i>'.'</i>))) {
<a name="L1637" href="source/net/ipv4/ipconfig.c#L1637">1637</a>                                         *dp++ = <i>'\0'</i>;
<a name="L1638" href="source/net/ipv4/ipconfig.c#L1638">1638</a>                                         <a href="ident?i=strlcpy">strlcpy</a>(<a href="ident?i=utsname">utsname</a>()-&gt;domainname, dp,
<a name="L1639" href="source/net/ipv4/ipconfig.c#L1639">1639</a>                                                 sizeof(<a href="ident?i=utsname">utsname</a>()-&gt;domainname));
<a name="L1640" href="source/net/ipv4/ipconfig.c#L1640">1640</a>                                 }
<a name="L1641" href="source/net/ipv4/ipconfig.c#L1641">1641</a>                                 <a href="ident?i=strlcpy">strlcpy</a>(<a href="ident?i=utsname">utsname</a>()-&gt;nodename, <a href="ident?i=ip">ip</a>,
<a name="L1642" href="source/net/ipv4/ipconfig.c#L1642">1642</a>                                         sizeof(<a href="ident?i=utsname">utsname</a>()-&gt;nodename));
<a name="L1643" href="source/net/ipv4/ipconfig.c#L1643">1643</a>                                 ic_host_name_set = 1;
<a name="L1644" href="source/net/ipv4/ipconfig.c#L1644">1644</a>                                 break;
<a name="L1645" href="source/net/ipv4/ipconfig.c#L1645">1645</a>                         case 5:
<a name="L1646" href="source/net/ipv4/ipconfig.c#L1646">1646</a>                                 <a href="ident?i=strlcpy">strlcpy</a>(user_dev_name, <a href="ident?i=ip">ip</a>, sizeof(user_dev_name));
<a name="L1647" href="source/net/ipv4/ipconfig.c#L1647">1647</a>                                 break;
<a name="L1648" href="source/net/ipv4/ipconfig.c#L1648">1648</a>                         case 6:
<a name="L1649" href="source/net/ipv4/ipconfig.c#L1649">1649</a>                                 if (<a href="ident?i=ic_proto_name">ic_proto_name</a>(<a href="ident?i=ip">ip</a>) == 0 &amp;&amp;
<a name="L1650" href="source/net/ipv4/ipconfig.c#L1650">1650</a>                                     <a href="ident?i=ic_myaddr">ic_myaddr</a> == <a href="ident?i=NONE">NONE</a>) {
<a name="L1651" href="source/net/ipv4/ipconfig.c#L1651">1651</a>                                         ic_enable = 0;
<a name="L1652" href="source/net/ipv4/ipconfig.c#L1652">1652</a>                                 }
<a name="L1653" href="source/net/ipv4/ipconfig.c#L1653">1653</a>                                 break;
<a name="L1654" href="source/net/ipv4/ipconfig.c#L1654">1654</a>                         case 7:
<a name="L1655" href="source/net/ipv4/ipconfig.c#L1655">1655</a>                                 if (<a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a> &gt;= 1) {
<a name="L1656" href="source/net/ipv4/ipconfig.c#L1656">1656</a>                                         <a href="ident?i=ic_nameservers">ic_nameservers</a>[0] = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=ip">ip</a>);
<a name="L1657" href="source/net/ipv4/ipconfig.c#L1657">1657</a>                                         if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[0] == <a href="ident?i=ANY">ANY</a>)
<a name="L1658" href="source/net/ipv4/ipconfig.c#L1658">1658</a>                                                 <a href="ident?i=ic_nameservers">ic_nameservers</a>[0] = <a href="ident?i=NONE">NONE</a>;
<a name="L1659" href="source/net/ipv4/ipconfig.c#L1659">1659</a>                                 }
<a name="L1660" href="source/net/ipv4/ipconfig.c#L1660">1660</a>                                 break;
<a name="L1661" href="source/net/ipv4/ipconfig.c#L1661">1661</a>                         case 8:
<a name="L1662" href="source/net/ipv4/ipconfig.c#L1662">1662</a>                                 if (<a href="ident?i=CONF_NAMESERVERS_MAX">CONF_NAMESERVERS_MAX</a> &gt;= 2) {
<a name="L1663" href="source/net/ipv4/ipconfig.c#L1663">1663</a>                                         <a href="ident?i=ic_nameservers">ic_nameservers</a>[1] = <a href="ident?i=in_aton">in_aton</a>(<a href="ident?i=ip">ip</a>);
<a name="L1664" href="source/net/ipv4/ipconfig.c#L1664">1664</a>                                         if (<a href="ident?i=ic_nameservers">ic_nameservers</a>[1] == <a href="ident?i=ANY">ANY</a>)
<a name="L1665" href="source/net/ipv4/ipconfig.c#L1665">1665</a>                                                 <a href="ident?i=ic_nameservers">ic_nameservers</a>[1] = <a href="ident?i=NONE">NONE</a>;
<a name="L1666" href="source/net/ipv4/ipconfig.c#L1666">1666</a>                                 }
<a name="L1667" href="source/net/ipv4/ipconfig.c#L1667">1667</a>                                 break;
<a name="L1668" href="source/net/ipv4/ipconfig.c#L1668">1668</a>                         }
<a name="L1669" href="source/net/ipv4/ipconfig.c#L1669">1669</a>                 }
<a name="L1670" href="source/net/ipv4/ipconfig.c#L1670">1670</a>                 <a href="ident?i=ip">ip</a> = <a href="ident?i=cp">cp</a>;
<a name="L1671" href="source/net/ipv4/ipconfig.c#L1671">1671</a>                 <a href="ident?i=num">num</a>++;
<a name="L1672" href="source/net/ipv4/ipconfig.c#L1672">1672</a>         }
<a name="L1673" href="source/net/ipv4/ipconfig.c#L1673">1673</a> 
<a name="L1674" href="source/net/ipv4/ipconfig.c#L1674">1674</a>         return 1;
<a name="L1675" href="source/net/ipv4/ipconfig.c#L1675">1675</a> }
<a name="L1676" href="source/net/ipv4/ipconfig.c#L1676">1676</a> <a href="ident?i=__setup">__setup</a>(<i>"ip="</i>, <a href="ident?i=ip_auto_config_setup">ip_auto_config_setup</a>);
<a name="L1677" href="source/net/ipv4/ipconfig.c#L1677">1677</a> 
<a name="L1678" href="source/net/ipv4/ipconfig.c#L1678">1678</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nfsaddrs_config_setup">nfsaddrs_config_setup</a>(char *<a href="ident?i=addrs">addrs</a>)
<a name="L1679" href="source/net/ipv4/ipconfig.c#L1679">1679</a> {
<a name="L1680" href="source/net/ipv4/ipconfig.c#L1680">1680</a>         return <a href="ident?i=ip_auto_config_setup">ip_auto_config_setup</a>(<a href="ident?i=addrs">addrs</a>);
<a name="L1681" href="source/net/ipv4/ipconfig.c#L1681">1681</a> }
<a name="L1682" href="source/net/ipv4/ipconfig.c#L1682">1682</a> <a href="ident?i=__setup">__setup</a>(<i>"nfsaddrs="</i>, <a href="ident?i=nfsaddrs_config_setup">nfsaddrs_config_setup</a>);
<a name="L1683" href="source/net/ipv4/ipconfig.c#L1683">1683</a> 
<a name="L1684" href="source/net/ipv4/ipconfig.c#L1684">1684</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=vendor_class_identifier_setup">vendor_class_identifier_setup</a>(char *<a href="ident?i=addrs">addrs</a>)
<a name="L1685" href="source/net/ipv4/ipconfig.c#L1685">1685</a> {
<a name="L1686" href="source/net/ipv4/ipconfig.c#L1686">1686</a>         if (<a href="ident?i=strlcpy">strlcpy</a>(vendor_class_identifier, <a href="ident?i=addrs">addrs</a>,
<a name="L1687" href="source/net/ipv4/ipconfig.c#L1687">1687</a>                     sizeof(vendor_class_identifier))
<a name="L1688" href="source/net/ipv4/ipconfig.c#L1688">1688</a>             &gt;= sizeof(vendor_class_identifier))
<a name="L1689" href="source/net/ipv4/ipconfig.c#L1689">1689</a>                 <a href="ident?i=pr_warn">pr_warn</a>(<i>"DHCP: vendorclass too long, truncated to \"%s\""</i>,
<a name="L1690" href="source/net/ipv4/ipconfig.c#L1690">1690</a>                         vendor_class_identifier);
<a name="L1691" href="source/net/ipv4/ipconfig.c#L1691">1691</a>         return 1;
<a name="L1692" href="source/net/ipv4/ipconfig.c#L1692">1692</a> }
<a name="L1693" href="source/net/ipv4/ipconfig.c#L1693">1693</a> <a href="ident?i=__setup">__setup</a>(<i>"dhcpclass="</i>, <a href="ident?i=vendor_class_identifier_setup">vendor_class_identifier_setup</a>);
<a name="L1694" href="source/net/ipv4/ipconfig.c#L1694">1694</a> </pre></div><p>
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
