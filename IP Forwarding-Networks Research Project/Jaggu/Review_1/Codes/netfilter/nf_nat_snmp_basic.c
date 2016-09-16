<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_snmp_basic.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_snmp_basic.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c">nf_nat_snmp_basic.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L2">2</a> <b><i> * nf_nat_snmp_basic.c</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L4">4</a> <b><i> * Basic SNMP Application Layer Gateway</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L6">6</a> <b><i> * This IP NAT module is intended for use with SNMP network</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L7">7</a> <b><i> * discovery and monitoring applications where target networks use</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L8">8</a> <b><i> * conflicting private address realms.</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L10">10</a> <b><i> * Static NAT is used to remap the networks from the view of the network</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L11">11</a> <b><i> * management system at the IP layer, and this module remaps some application</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L12">12</a> <b><i> * layer addresses to match.</i></b>
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L14">14</a> <b><i> * The simplest form of ALG is performed, where only tagged IP addresses</i></b>
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L15">15</a> <b><i> * are modified.  The module does not need to be MIB aware and only scans</i></b>
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L16">16</a> <b><i> * messages at the ASN.1/BER level.</i></b>
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L18">18</a> <b><i> * Currently, only SNMPv1 and SNMPv2 are supported.</i></b>
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L20">20</a> <b><i> * More information on ALG and associated issues can be found in</i></b>
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L21">21</a> <b><i> * RFC 2962</i></b>
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L22">22</a> <b><i> *</i></b>
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L23">23</a> <b><i> * The ASB.1/BER parsing code is derived from the gxsnmp package by Gregory</i></b>
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L24">24</a> <b><i> * McLean &amp; Jochen Friedrich, stripped down for use in the kernel.</i></b>
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L25">25</a> <b><i> *</i></b>
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L26">26</a> <b><i> * Copyright (c) 2000 RP Internet (www.rpi.net.au).</i></b>
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L27">27</a> <b><i> *</i></b>
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L28">28</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L29">29</a> <b><i> * it under the terms of the GNU General Public License as published by</i></b>
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L30">30</a> <b><i> * the Free Software Foundation; either version 2 of the License, or</i></b>
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L31">31</a> <b><i> * (at your option) any later version.</i></b>
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L32">32</a> <b><i> * This program is distributed in the hope that it will be useful,</i></b>
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L33">33</a> <b><i> * but WITHOUT ANY WARRANTY; without even the implied warranty of</i></b>
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L34">34</a> <b><i> * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</i></b>
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L35">35</a> <b><i> * GNU General Public License for more details.</i></b>
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L36">36</a> <b><i> * You should have received a copy of the GNU General Public License</i></b>
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L37">37</a> <b><i> * along with this program; if not, see &lt;<a href="http://www.gnu.org/licenses/&gt;">http://www.gnu.org/licenses/&gt;</a>.</i></b>
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L38">38</a> <b><i> *</i></b>
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L39">39</a> <b><i> * Author: James Morris &lt;jmorris@intercode.com.au&gt;</i></b>
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L40">40</a> <b><i> *</i></b>
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L41">41</a> <b><i> * Copyright (c) 2006-2010 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L42">42</a> <b><i> */</i></b>
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L43">43</a> #include &lt;linux/module.h&gt;
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L44">44</a> #include &lt;linux/moduleparam.h&gt;
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L45">45</a> #include &lt;linux/types.h&gt;
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L46">46</a> #include &lt;linux/kernel.h&gt;
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L47">47</a> #include &lt;linux/slab.h&gt;
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L48">48</a> #include &lt;linux/in.h&gt;
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L49">49</a> #include &lt;linux/ip.h&gt;
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L50">50</a> #include &lt;linux/udp.h&gt;
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L51">51</a> #include &lt;net/checksum.h&gt;
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L52">52</a> #include &lt;net/udp.h&gt;
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L54">54</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L55">55</a> #include &lt;net/netfilter/nf_conntrack_expect.h&gt;
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L56">56</a> #include &lt;net/netfilter/nf_conntrack_helper.h&gt;
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L57">57</a> #include &lt;net/netfilter/nf_nat_helper.h&gt;
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L58">58</a> #include &lt;linux/netfilter/nf_conntrack_snmp.h&gt;
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L60">60</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L61">61</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"James Morris &lt;jmorris@intercode.com.au&gt;"</i>);
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L62">62</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Basic SNMP Application Layer Gateway"</i>);
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L63">63</a> <a href="ident?i=MODULE_ALIAS">MODULE_ALIAS</a>(<i>"ip_nat_snmp_basic"</i>);
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L65">65</a> #define <a href="ident?i=SNMP_PORT">SNMP_PORT</a> 161
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L66">66</a> #define <a href="ident?i=SNMP_TRAP_PORT">SNMP_TRAP_PORT</a> 162
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L67">67</a> #define <a href="ident?i=NOCT1">NOCT1</a>(<a href="ident?i=n">n</a>) (*(<a href="ident?i=u8">u8</a> *)(<a href="ident?i=n">n</a>))
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L69">69</a> static int <a href="ident?i=debug">debug</a>;
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L70">70</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(snmp_lock);
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L72">72</a> <b><i>/*</i></b>
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L73">73</a> <b><i> * Application layer address mapping mimics the NAT mapping, but</i></b>
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L74">74</a> <b><i> * only for the first octet in this case (a more flexible system</i></b>
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L75">75</a> <b><i> * can be implemented if needed).</i></b>
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L76">76</a> <b><i> */</i></b>
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L77">77</a> struct <a href="ident?i=oct1_map">oct1_map</a>
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L78">78</a> {
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L79">79</a>         <a href="ident?i=u_int8_t">u_int8_t</a> from;
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L80">80</a>         <a href="ident?i=u_int8_t">u_int8_t</a> to;
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L81">81</a> };
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L84">84</a> <b><i>/*****************************************************************************</i></b>
 <a name="L85" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L85">85</a> <b><i> *</i></b>
 <a name="L86" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L86">86</a> <b><i> * Basic ASN.1 decoding routines (gxsnmp author Dirk Wisse)</i></b>
 <a name="L87" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L87">87</a> <b><i> *</i></b>
 <a name="L88" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L88">88</a> <b><i> *****************************************************************************/</i></b>
 <a name="L89" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L90">90</a> <b><i>/* Class */</i></b>
 <a name="L91" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L91">91</a> #define <a href="ident?i=ASN1_UNI">ASN1_UNI</a>        0       <b><i>/* Universal */</i></b>
 <a name="L92" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L92">92</a> #define <a href="ident?i=ASN1_APL">ASN1_APL</a>        1       <b><i>/* Application */</i></b>
 <a name="L93" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L93">93</a> #define <a href="ident?i=ASN1_CTX">ASN1_CTX</a>        2       <b><i>/* Context */</i></b>
 <a name="L94" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L94">94</a> #define <a href="ident?i=ASN1_PRV">ASN1_PRV</a>        3       <b><i>/* Private */</i></b>
 <a name="L95" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L96">96</a> <b><i>/* Tag */</i></b>
 <a name="L97" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L97">97</a> #define <a href="ident?i=ASN1_EOC">ASN1_EOC</a>        0       <b><i>/* End Of Contents */</i></b>
 <a name="L98" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L98">98</a> #define <a href="ident?i=ASN1_BOL">ASN1_BOL</a>        1       <b><i>/* Boolean */</i></b>
 <a name="L99" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L99">99</a> #define <a href="ident?i=ASN1_INT">ASN1_INT</a>        2       <b><i>/* Integer */</i></b>
<a name="L100" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L100">100</a> #define <a href="ident?i=ASN1_BTS">ASN1_BTS</a>        3       <b><i>/* Bit String */</i></b>
<a name="L101" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L101">101</a> #define <a href="ident?i=ASN1_OTS">ASN1_OTS</a>        4       <b><i>/* Octet String */</i></b>
<a name="L102" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L102">102</a> #define <a href="ident?i=ASN1_NUL">ASN1_NUL</a>        5       <b><i>/* Null */</i></b>
<a name="L103" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L103">103</a> #define <a href="ident?i=ASN1_OJI">ASN1_OJI</a>        6       <b><i>/* Object Identifier  */</i></b>
<a name="L104" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L104">104</a> #define <a href="ident?i=ASN1_OJD">ASN1_OJD</a>        7       <b><i>/* Object Description */</i></b>
<a name="L105" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L105">105</a> #define <a href="ident?i=ASN1_EXT">ASN1_EXT</a>        8       <b><i>/* External */</i></b>
<a name="L106" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L106">106</a> #define <a href="ident?i=ASN1_SEQ">ASN1_SEQ</a>        16      <b><i>/* Sequence */</i></b>
<a name="L107" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L107">107</a> #define <a href="ident?i=ASN1_SET">ASN1_SET</a>        17      <b><i>/* Set */</i></b>
<a name="L108" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L108">108</a> #define <a href="ident?i=ASN1_NUMSTR">ASN1_NUMSTR</a>     18      <b><i>/* Numerical String */</i></b>
<a name="L109" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L109">109</a> #define <a href="ident?i=ASN1_PRNSTR">ASN1_PRNSTR</a>     19      <b><i>/* Printable String */</i></b>
<a name="L110" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L110">110</a> #define <a href="ident?i=ASN1_TEXSTR">ASN1_TEXSTR</a>     20      <b><i>/* Teletext String */</i></b>
<a name="L111" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L111">111</a> #define <a href="ident?i=ASN1_VIDSTR">ASN1_VIDSTR</a>     21      <b><i>/* Video String */</i></b>
<a name="L112" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L112">112</a> #define <a href="ident?i=ASN1_IA5STR">ASN1_IA5STR</a>     22      <b><i>/* IA5 String */</i></b>
<a name="L113" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L113">113</a> #define <a href="ident?i=ASN1_UNITIM">ASN1_UNITIM</a>     23      <b><i>/* Universal Time */</i></b>
<a name="L114" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L114">114</a> #define <a href="ident?i=ASN1_GENTIM">ASN1_GENTIM</a>     24      <b><i>/* General Time */</i></b>
<a name="L115" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L115">115</a> #define <a href="ident?i=ASN1_GRASTR">ASN1_GRASTR</a>     25      <b><i>/* Graphical String */</i></b>
<a name="L116" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L116">116</a> #define <a href="ident?i=ASN1_VISSTR">ASN1_VISSTR</a>     26      <b><i>/* Visible String */</i></b>
<a name="L117" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L117">117</a> #define <a href="ident?i=ASN1_GENSTR">ASN1_GENSTR</a>     27      <b><i>/* General String */</i></b>
<a name="L118" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L119">119</a> <b><i>/* Primitive / Constructed methods*/</i></b>
<a name="L120" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L120">120</a> #define <a href="ident?i=ASN1_PRI">ASN1_PRI</a>        0       <b><i>/* Primitive */</i></b>
<a name="L121" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L121">121</a> #define <a href="ident?i=ASN1_CON">ASN1_CON</a>        1       <b><i>/* Constructed */</i></b>
<a name="L122" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L123">123</a> <b><i>/*</i></b>
<a name="L124" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L124">124</a> <b><i> * Error codes.</i></b>
<a name="L125" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L125">125</a> <b><i> */</i></b>
<a name="L126" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L126">126</a> #define <a href="ident?i=ASN1_ERR_NOERROR">ASN1_ERR_NOERROR</a>                0
<a name="L127" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L127">127</a> #define <a href="ident?i=ASN1_ERR_DEC_EMPTY">ASN1_ERR_DEC_EMPTY</a>              2
<a name="L128" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L128">128</a> #define <a href="ident?i=ASN1_ERR_DEC_EOC_MISMATCH">ASN1_ERR_DEC_EOC_MISMATCH</a>       3
<a name="L129" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L129">129</a> #define <a href="ident?i=ASN1_ERR_DEC_LENGTH_MISMATCH">ASN1_ERR_DEC_LENGTH_MISMATCH</a>    4
<a name="L130" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L130">130</a> #define <a href="ident?i=ASN1_ERR_DEC_BADVALUE">ASN1_ERR_DEC_BADVALUE</a>           5
<a name="L131" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L132">132</a> <b><i>/*</i></b>
<a name="L133" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L133">133</a> <b><i> * ASN.1 context.</i></b>
<a name="L134" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L134">134</a> <b><i> */</i></b>
<a name="L135" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L135">135</a> struct <a href="ident?i=asn1_ctx">asn1_ctx</a>
<a name="L136" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L136">136</a> {
<a name="L137" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L137">137</a>         int <a href="ident?i=error">error</a>;                      <b><i>/* Error condition */</i></b>
<a name="L138" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L138">138</a>         unsigned char *<a href="ident?i=pointer">pointer</a>;         <b><i>/* Octet just to be decoded */</i></b>
<a name="L139" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L139">139</a>         unsigned char *begin;           <b><i>/* First octet */</i></b>
<a name="L140" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L140">140</a>         unsigned char *<a href="ident?i=end">end</a>;             <b><i>/* Octet after last octet */</i></b>
<a name="L141" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L141">141</a> };
<a name="L142" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L143">143</a> <b><i>/*</i></b>
<a name="L144" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L144">144</a> <b><i> * Octet string (not null terminated)</i></b>
<a name="L145" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L145">145</a> <b><i> */</i></b>
<a name="L146" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L146">146</a> struct <a href="ident?i=asn1_octstr">asn1_octstr</a>
<a name="L147" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L147">147</a> {
<a name="L148" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L148">148</a>         unsigned char *<a href="ident?i=data">data</a>;
<a name="L149" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L149">149</a>         unsigned int <a href="ident?i=len">len</a>;
<a name="L150" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L150">150</a> };
<a name="L151" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L152">152</a> static void <a href="ident?i=asn1_open">asn1_open</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L153" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L153">153</a>                       unsigned char *<a href="ident?i=buf">buf</a>,
<a name="L154" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L154">154</a>                       unsigned int <a href="ident?i=len">len</a>)
<a name="L155" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L155">155</a> {
<a name="L156" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L156">156</a>         <a href="ident?i=ctx">ctx</a>-&gt;begin = <a href="ident?i=buf">buf</a>;
<a name="L157" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L157">157</a>         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=end">end</a> = <a href="ident?i=buf">buf</a> + <a href="ident?i=len">len</a>;
<a name="L158" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L158">158</a>         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> = <a href="ident?i=buf">buf</a>;
<a name="L159" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L159">159</a>         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_NOERROR">ASN1_ERR_NOERROR</a>;
<a name="L160" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L160">160</a> }
<a name="L161" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L162">162</a> static unsigned char <a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>, unsigned char *<a href="ident?i=ch">ch</a>)
<a name="L163" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L163">163</a> {
<a name="L164" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L164">164</a>         if (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> &gt;= <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=end">end</a>) {
<a name="L165" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L165">165</a>                 <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_EMPTY">ASN1_ERR_DEC_EMPTY</a>;
<a name="L166" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L166">166</a>                 return 0;
<a name="L167" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L167">167</a>         }
<a name="L168" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L168">168</a>         *<a href="ident?i=ch">ch</a> = *(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a>)++;
<a name="L169" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L169">169</a>         return 1;
<a name="L170" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L170">170</a> }
<a name="L171" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L172">172</a> static unsigned char <a href="ident?i=asn1_tag_decode">asn1_tag_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>, unsigned int *<a href="ident?i=tag">tag</a>)
<a name="L173" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L173">173</a> {
<a name="L174" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L174">174</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L175" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L176">176</a>         *<a href="ident?i=tag">tag</a> = 0;
<a name="L177" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L178">178</a>         do
<a name="L179" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L179">179</a>         {
<a name="L180" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L180">180</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L181" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L181">181</a>                         return 0;
<a name="L182" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L182">182</a>                 *<a href="ident?i=tag">tag</a> &lt;&lt;= 7;
<a name="L183" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L183">183</a>                 *<a href="ident?i=tag">tag</a> |= <a href="ident?i=ch">ch</a> &amp; 0x7F;
<a name="L184" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L184">184</a>         } while ((<a href="ident?i=ch">ch</a> &amp; 0x80) == 0x80);
<a name="L185" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L185">185</a>         return 1;
<a name="L186" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L186">186</a> }
<a name="L187" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L188">188</a> static unsigned char <a href="ident?i=asn1_id_decode">asn1_id_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L189" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L189">189</a>                                     unsigned int *cls,
<a name="L190" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L190">190</a>                                     unsigned int *con,
<a name="L191" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L191">191</a>                                     unsigned int *<a href="ident?i=tag">tag</a>)
<a name="L192" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L192">192</a> {
<a name="L193" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L193">193</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L194" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L195">195</a>         if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L196" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L196">196</a>                 return 0;
<a name="L197" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L198">198</a>         *cls = (<a href="ident?i=ch">ch</a> &amp; 0xC0) &gt;&gt; 6;
<a name="L199" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L199">199</a>         *con = (<a href="ident?i=ch">ch</a> &amp; 0x20) &gt;&gt; 5;
<a name="L200" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L200">200</a>         *<a href="ident?i=tag">tag</a> = (<a href="ident?i=ch">ch</a> &amp; 0x1F);
<a name="L201" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L202">202</a>         if (*<a href="ident?i=tag">tag</a> == 0x1F) {
<a name="L203" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L203">203</a>                 if (!<a href="ident?i=asn1_tag_decode">asn1_tag_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=tag">tag</a>))
<a name="L204" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L204">204</a>                         return 0;
<a name="L205" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L205">205</a>         }
<a name="L206" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L206">206</a>         return 1;
<a name="L207" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L207">207</a> }
<a name="L208" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L209">209</a> static unsigned char <a href="ident?i=asn1_length_decode">asn1_length_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L210" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L210">210</a>                                         unsigned int *def,
<a name="L211" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L211">211</a>                                         unsigned int *<a href="ident?i=len">len</a>)
<a name="L212" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L212">212</a> {
<a name="L213" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L213">213</a>         unsigned char <a href="ident?i=ch">ch</a>, cnt;
<a name="L214" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L215">215</a>         if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L216" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L216">216</a>                 return 0;
<a name="L217" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L218">218</a>         if (<a href="ident?i=ch">ch</a> == 0x80)
<a name="L219" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L219">219</a>                 *def = 0;
<a name="L220" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L220">220</a>         else {
<a name="L221" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L221">221</a>                 *def = 1;
<a name="L222" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L223">223</a>                 if (<a href="ident?i=ch">ch</a> &lt; 0x80)
<a name="L224" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L224">224</a>                         *<a href="ident?i=len">len</a> = <a href="ident?i=ch">ch</a>;
<a name="L225" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L225">225</a>                 else {
<a name="L226" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L226">226</a>                         cnt = <a href="ident?i=ch">ch</a> &amp; 0x7F;
<a name="L227" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L227">227</a>                         *<a href="ident?i=len">len</a> = 0;
<a name="L228" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L229">229</a>                         while (cnt &gt; 0) {
<a name="L230" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L230">230</a>                                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L231" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L231">231</a>                                         return 0;
<a name="L232" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L232">232</a>                                 *<a href="ident?i=len">len</a> &lt;&lt;= 8;
<a name="L233" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L233">233</a>                                 *<a href="ident?i=len">len</a> |= <a href="ident?i=ch">ch</a>;
<a name="L234" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L234">234</a>                                 cnt--;
<a name="L235" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L235">235</a>                         }
<a name="L236" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L236">236</a>                 }
<a name="L237" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L237">237</a>         }
<a name="L238" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L239">239</a>         <b><i>/* don't trust len bigger than ctx buffer */</i></b>
<a name="L240" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L240">240</a>         if (*<a href="ident?i=len">len</a> &gt; <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=end">end</a> - <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a>)
<a name="L241" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L241">241</a>                 return 0;
<a name="L242" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L243">243</a>         return 1;
<a name="L244" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L244">244</a> }
<a name="L245" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L246">246</a> static unsigned char <a href="ident?i=asn1_header_decode">asn1_header_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L247" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L247">247</a>                                         unsigned char **eoc,
<a name="L248" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L248">248</a>                                         unsigned int *cls,
<a name="L249" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L249">249</a>                                         unsigned int *con,
<a name="L250" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L250">250</a>                                         unsigned int *<a href="ident?i=tag">tag</a>)
<a name="L251" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L251">251</a> {
<a name="L252" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L252">252</a>         unsigned int def, <a href="ident?i=len">len</a>;
<a name="L253" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L254">254</a>         if (!<a href="ident?i=asn1_id_decode">asn1_id_decode</a>(<a href="ident?i=ctx">ctx</a>, cls, con, <a href="ident?i=tag">tag</a>))
<a name="L255" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L255">255</a>                 return 0;
<a name="L256" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L257">257</a>         def = <a href="ident?i=len">len</a> = 0;
<a name="L258" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L258">258</a>         if (!<a href="ident?i=asn1_length_decode">asn1_length_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;def, &amp;<a href="ident?i=len">len</a>))
<a name="L259" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L259">259</a>                 return 0;
<a name="L260" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L261">261</a>         <b><i>/* primitive shall be definite, indefinite shall be constructed */</i></b>
<a name="L262" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L262">262</a>         if (*con == <a href="ident?i=ASN1_PRI">ASN1_PRI</a> &amp;&amp; !def)
<a name="L263" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L263">263</a>                 return 0;
<a name="L264" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L265">265</a>         if (def)
<a name="L266" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L266">266</a>                 *eoc = <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> + <a href="ident?i=len">len</a>;
<a name="L267" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L267">267</a>         else
<a name="L268" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L268">268</a>                 *eoc = <a href="ident?i=NULL">NULL</a>;
<a name="L269" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L269">269</a>         return 1;
<a name="L270" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L270">270</a> }
<a name="L271" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L272">272</a> static unsigned char <a href="ident?i=asn1_eoc_decode">asn1_eoc_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>, unsigned char *eoc)
<a name="L273" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L273">273</a> {
<a name="L274" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L274">274</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L275" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L276">276</a>         if (eoc == <a href="ident?i=NULL">NULL</a>) {
<a name="L277" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L277">277</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L278" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L278">278</a>                         return 0;
<a name="L279" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L280">280</a>                 if (<a href="ident?i=ch">ch</a> != 0x00) {
<a name="L281" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L281">281</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_EOC_MISMATCH">ASN1_ERR_DEC_EOC_MISMATCH</a>;
<a name="L282" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L282">282</a>                         return 0;
<a name="L283" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L283">283</a>                 }
<a name="L284" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L285">285</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L286" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L286">286</a>                         return 0;
<a name="L287" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L288">288</a>                 if (<a href="ident?i=ch">ch</a> != 0x00) {
<a name="L289" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L289">289</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_EOC_MISMATCH">ASN1_ERR_DEC_EOC_MISMATCH</a>;
<a name="L290" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L290">290</a>                         return 0;
<a name="L291" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L291">291</a>                 }
<a name="L292" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L292">292</a>                 return 1;
<a name="L293" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L293">293</a>         } else {
<a name="L294" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L294">294</a>                 if (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> != eoc) {
<a name="L295" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L295">295</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_LENGTH_MISMATCH">ASN1_ERR_DEC_LENGTH_MISMATCH</a>;
<a name="L296" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L296">296</a>                         return 0;
<a name="L297" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L297">297</a>                 }
<a name="L298" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L298">298</a>                 return 1;
<a name="L299" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L299">299</a>         }
<a name="L300" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L300">300</a> }
<a name="L301" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L302">302</a> static unsigned char <a href="ident?i=asn1_null_decode">asn1_null_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>, unsigned char *eoc)
<a name="L303" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L303">303</a> {
<a name="L304" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L304">304</a>         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> = eoc;
<a name="L305" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L305">305</a>         return 1;
<a name="L306" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L306">306</a> }
<a name="L307" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L308">308</a> static unsigned char <a href="ident?i=asn1_long_decode">asn1_long_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L309" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L309">309</a>                                       unsigned char *eoc,
<a name="L310" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L310">310</a>                                       long *integer)
<a name="L311" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L311">311</a> {
<a name="L312" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L312">312</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L313" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L313">313</a>         unsigned int  <a href="ident?i=len">len</a>;
<a name="L314" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L315">315</a>         if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L316" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L316">316</a>                 return 0;
<a name="L317" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L318">318</a>         *integer = (signed char) <a href="ident?i=ch">ch</a>;
<a name="L319" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L319">319</a>         <a href="ident?i=len">len</a> = 1;
<a name="L320" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L321">321</a>         while (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> &lt; eoc) {
<a name="L322" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L322">322</a>                 if (++<a href="ident?i=len">len</a> &gt; sizeof (long)) {
<a name="L323" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L323">323</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_BADVALUE">ASN1_ERR_DEC_BADVALUE</a>;
<a name="L324" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L324">324</a>                         return 0;
<a name="L325" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L325">325</a>                 }
<a name="L326" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L327">327</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L328" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L328">328</a>                         return 0;
<a name="L329" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L330">330</a>                 *integer &lt;&lt;= 8;
<a name="L331" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L331">331</a>                 *integer |= <a href="ident?i=ch">ch</a>;
<a name="L332" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L332">332</a>         }
<a name="L333" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L333">333</a>         return 1;
<a name="L334" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L334">334</a> }
<a name="L335" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L335">335</a> 
<a name="L336" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L336">336</a> static unsigned char <a href="ident?i=asn1_uint_decode">asn1_uint_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L337" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L337">337</a>                                       unsigned char *eoc,
<a name="L338" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L338">338</a>                                       unsigned int *integer)
<a name="L339" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L339">339</a> {
<a name="L340" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L340">340</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L341" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L341">341</a>         unsigned int  <a href="ident?i=len">len</a>;
<a name="L342" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L343">343</a>         if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L344" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L344">344</a>                 return 0;
<a name="L345" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L345">345</a> 
<a name="L346" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L346">346</a>         *integer = <a href="ident?i=ch">ch</a>;
<a name="L347" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L347">347</a>         if (<a href="ident?i=ch">ch</a> == 0) <a href="ident?i=len">len</a> = 0;
<a name="L348" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L348">348</a>         else <a href="ident?i=len">len</a> = 1;
<a name="L349" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L349">349</a> 
<a name="L350" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L350">350</a>         while (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> &lt; eoc) {
<a name="L351" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L351">351</a>                 if (++<a href="ident?i=len">len</a> &gt; sizeof (unsigned int)) {
<a name="L352" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L352">352</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_BADVALUE">ASN1_ERR_DEC_BADVALUE</a>;
<a name="L353" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L353">353</a>                         return 0;
<a name="L354" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L354">354</a>                 }
<a name="L355" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L356">356</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L357" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L357">357</a>                         return 0;
<a name="L358" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L359">359</a>                 *integer &lt;&lt;= 8;
<a name="L360" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L360">360</a>                 *integer |= <a href="ident?i=ch">ch</a>;
<a name="L361" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L361">361</a>         }
<a name="L362" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L362">362</a>         return 1;
<a name="L363" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L363">363</a> }
<a name="L364" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L365">365</a> static unsigned char <a href="ident?i=asn1_ulong_decode">asn1_ulong_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L366" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L366">366</a>                                        unsigned char *eoc,
<a name="L367" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L367">367</a>                                        unsigned long *integer)
<a name="L368" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L368">368</a> {
<a name="L369" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L369">369</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L370" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L370">370</a>         unsigned int  <a href="ident?i=len">len</a>;
<a name="L371" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L372">372</a>         if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L373" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L373">373</a>                 return 0;
<a name="L374" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L374">374</a> 
<a name="L375" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L375">375</a>         *integer = <a href="ident?i=ch">ch</a>;
<a name="L376" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L376">376</a>         if (<a href="ident?i=ch">ch</a> == 0) <a href="ident?i=len">len</a> = 0;
<a name="L377" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L377">377</a>         else <a href="ident?i=len">len</a> = 1;
<a name="L378" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L379">379</a>         while (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> &lt; eoc) {
<a name="L380" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L380">380</a>                 if (++<a href="ident?i=len">len</a> &gt; sizeof (unsigned long)) {
<a name="L381" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L381">381</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_BADVALUE">ASN1_ERR_DEC_BADVALUE</a>;
<a name="L382" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L382">382</a>                         return 0;
<a name="L383" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L383">383</a>                 }
<a name="L384" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L385">385</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L386" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L386">386</a>                         return 0;
<a name="L387" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L388">388</a>                 *integer &lt;&lt;= 8;
<a name="L389" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L389">389</a>                 *integer |= <a href="ident?i=ch">ch</a>;
<a name="L390" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L390">390</a>         }
<a name="L391" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L391">391</a>         return 1;
<a name="L392" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L392">392</a> }
<a name="L393" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L394">394</a> static unsigned char <a href="ident?i=asn1_octets_decode">asn1_octets_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L395" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L395">395</a>                                         unsigned char *eoc,
<a name="L396" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L396">396</a>                                         unsigned char **octets,
<a name="L397" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L397">397</a>                                         unsigned int *<a href="ident?i=len">len</a>)
<a name="L398" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L398">398</a> {
<a name="L399" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L399">399</a>         unsigned char *<a href="ident?i=ptr">ptr</a>;
<a name="L400" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L401">401</a>         *<a href="ident?i=len">len</a> = 0;
<a name="L402" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L402">402</a> 
<a name="L403" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L403">403</a>         *octets = <a href="ident?i=kmalloc">kmalloc</a>(eoc - <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L404" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L404">404</a>         if (*octets == <a href="ident?i=NULL">NULL</a>)
<a name="L405" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L405">405</a>                 return 0;
<a name="L406" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L407">407</a>         <a href="ident?i=ptr">ptr</a> = *octets;
<a name="L408" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L408">408</a>         while (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> &lt; eoc) {
<a name="L409" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L409">409</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=ptr">ptr</a>++)) {
<a name="L410" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L410">410</a>                         <a href="ident?i=kfree">kfree</a>(*octets);
<a name="L411" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L411">411</a>                         *octets = <a href="ident?i=NULL">NULL</a>;
<a name="L412" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L412">412</a>                         return 0;
<a name="L413" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L413">413</a>                 }
<a name="L414" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L414">414</a>                 (*<a href="ident?i=len">len</a>)++;
<a name="L415" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L415">415</a>         }
<a name="L416" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L416">416</a>         return 1;
<a name="L417" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L417">417</a> }
<a name="L418" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L419">419</a> static unsigned char <a href="ident?i=asn1_subid_decode">asn1_subid_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L420" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L420">420</a>                                        unsigned long *subid)
<a name="L421" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L421">421</a> {
<a name="L422" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L422">422</a>         unsigned char <a href="ident?i=ch">ch</a>;
<a name="L423" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L424">424</a>         *subid = 0;
<a name="L425" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L426">426</a>         do {
<a name="L427" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L427">427</a>                 if (!<a href="ident?i=asn1_octet_decode">asn1_octet_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=ch">ch</a>))
<a name="L428" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L428">428</a>                         return 0;
<a name="L429" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L430">430</a>                 *subid &lt;&lt;= 7;
<a name="L431" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L431">431</a>                 *subid |= <a href="ident?i=ch">ch</a> &amp; 0x7F;
<a name="L432" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L432">432</a>         } while ((<a href="ident?i=ch">ch</a> &amp; 0x80) == 0x80);
<a name="L433" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L433">433</a>         return 1;
<a name="L434" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L434">434</a> }
<a name="L435" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L436">436</a> static unsigned char <a href="ident?i=asn1_oid_decode">asn1_oid_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L437" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L437">437</a>                                      unsigned char *eoc,
<a name="L438" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L438">438</a>                                      unsigned long **oid,
<a name="L439" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L439">439</a>                                      unsigned int *<a href="ident?i=len">len</a>)
<a name="L440" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L440">440</a> {
<a name="L441" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L441">441</a>         unsigned long subid;
<a name="L442" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L442">442</a>         unsigned long *optr;
<a name="L443" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L443">443</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>;
<a name="L444" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L445">445</a>         <a href="ident?i=size">size</a> = eoc - <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> + 1;
<a name="L446" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L447">447</a>         <b><i>/* first subid actually encodes first two subids */</i></b>
<a name="L448" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L448">448</a>         if (<a href="ident?i=size">size</a> &lt; 2 || <a href="ident?i=size">size</a> &gt; <a href="ident?i=ULONG_MAX">ULONG_MAX</a>/sizeof(unsigned long))
<a name="L449" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L449">449</a>                 return 0;
<a name="L450" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L450">450</a> 
<a name="L451" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L451">451</a>         *oid = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=size">size</a> * sizeof(unsigned long), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L452" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L452">452</a>         if (*oid == <a href="ident?i=NULL">NULL</a>)
<a name="L453" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L453">453</a>                 return 0;
<a name="L454" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L455">455</a>         optr = *oid;
<a name="L456" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L457">457</a>         if (!<a href="ident?i=asn1_subid_decode">asn1_subid_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;subid)) {
<a name="L458" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L458">458</a>                 <a href="ident?i=kfree">kfree</a>(*oid);
<a name="L459" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L459">459</a>                 *oid = <a href="ident?i=NULL">NULL</a>;
<a name="L460" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L460">460</a>                 return 0;
<a name="L461" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L461">461</a>         }
<a name="L462" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L462">462</a> 
<a name="L463" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L463">463</a>         if (subid &lt; 40) {
<a name="L464" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L464">464</a>                 optr[0] = 0;
<a name="L465" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L465">465</a>                 optr[1] = subid;
<a name="L466" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L466">466</a>         } else if (subid &lt; 80) {
<a name="L467" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L467">467</a>                 optr[0] = 1;
<a name="L468" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L468">468</a>                 optr[1] = subid - 40;
<a name="L469" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L469">469</a>         } else {
<a name="L470" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L470">470</a>                 optr[0] = 2;
<a name="L471" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L471">471</a>                 optr[1] = subid - 80;
<a name="L472" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L472">472</a>         }
<a name="L473" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L474">474</a>         *<a href="ident?i=len">len</a> = 2;
<a name="L475" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L475">475</a>         optr += 2;
<a name="L476" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L477">477</a>         while (<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> &lt; eoc) {
<a name="L478" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L478">478</a>                 if (++(*<a href="ident?i=len">len</a>) &gt; <a href="ident?i=size">size</a>) {
<a name="L479" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L479">479</a>                         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=error">error</a> = <a href="ident?i=ASN1_ERR_DEC_BADVALUE">ASN1_ERR_DEC_BADVALUE</a>;
<a name="L480" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L480">480</a>                         <a href="ident?i=kfree">kfree</a>(*oid);
<a name="L481" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L481">481</a>                         *oid = <a href="ident?i=NULL">NULL</a>;
<a name="L482" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L482">482</a>                         return 0;
<a name="L483" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L483">483</a>                 }
<a name="L484" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L484">484</a> 
<a name="L485" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L485">485</a>                 if (!<a href="ident?i=asn1_subid_decode">asn1_subid_decode</a>(<a href="ident?i=ctx">ctx</a>, optr++)) {
<a name="L486" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L486">486</a>                         <a href="ident?i=kfree">kfree</a>(*oid);
<a name="L487" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L487">487</a>                         *oid = <a href="ident?i=NULL">NULL</a>;
<a name="L488" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L488">488</a>                         return 0;
<a name="L489" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L489">489</a>                 }
<a name="L490" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L490">490</a>         }
<a name="L491" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L491">491</a>         return 1;
<a name="L492" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L492">492</a> }
<a name="L493" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L493">493</a> 
<a name="L494" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L494">494</a> <b><i>/*****************************************************************************</i></b>
<a name="L495" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L495">495</a> <b><i> *</i></b>
<a name="L496" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L496">496</a> <b><i> * SNMP decoding routines (gxsnmp author Dirk Wisse)</i></b>
<a name="L497" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L497">497</a> <b><i> *</i></b>
<a name="L498" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L498">498</a> <b><i> *****************************************************************************/</i></b>
<a name="L499" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L499">499</a> 
<a name="L500" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L500">500</a> <b><i>/* SNMP Versions */</i></b>
<a name="L501" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L501">501</a> #define <a href="ident?i=SNMP_V1">SNMP_V1</a>                         0
<a name="L502" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L502">502</a> #define <a href="ident?i=SNMP_V2C">SNMP_V2C</a>                        1
<a name="L503" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L503">503</a> #define <a href="ident?i=SNMP_V2">SNMP_V2</a>                         2
<a name="L504" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L504">504</a> #define <a href="ident?i=SNMP_V3">SNMP_V3</a>                         3
<a name="L505" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L505">505</a> 
<a name="L506" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L506">506</a> <b><i>/* Default Sizes */</i></b>
<a name="L507" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L507">507</a> #define <a href="ident?i=SNMP_SIZE_COMM">SNMP_SIZE_COMM</a>                  256
<a name="L508" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L508">508</a> #define <a href="ident?i=SNMP_SIZE_OBJECTID">SNMP_SIZE_OBJECTID</a>              128
<a name="L509" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L509">509</a> #define <a href="ident?i=SNMP_SIZE_BUFCHR">SNMP_SIZE_BUFCHR</a>                256
<a name="L510" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L510">510</a> #define <a href="ident?i=SNMP_SIZE_BUFINT">SNMP_SIZE_BUFINT</a>                128
<a name="L511" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L511">511</a> #define <a href="ident?i=SNMP_SIZE_SMALLOBJECTID">SNMP_SIZE_SMALLOBJECTID</a>         16
<a name="L512" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L513">513</a> <b><i>/* Requests */</i></b>
<a name="L514" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L514">514</a> #define <a href="ident?i=SNMP_PDU_GET">SNMP_PDU_GET</a>                    0
<a name="L515" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L515">515</a> #define <a href="ident?i=SNMP_PDU_NEXT">SNMP_PDU_NEXT</a>                   1
<a name="L516" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L516">516</a> #define <a href="ident?i=SNMP_PDU_RESPONSE">SNMP_PDU_RESPONSE</a>               2
<a name="L517" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L517">517</a> #define <a href="ident?i=SNMP_PDU_SET">SNMP_PDU_SET</a>                    3
<a name="L518" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L518">518</a> #define <a href="ident?i=SNMP_PDU_TRAP1">SNMP_PDU_TRAP1</a>                  4
<a name="L519" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L519">519</a> #define <a href="ident?i=SNMP_PDU_BULK">SNMP_PDU_BULK</a>                   5
<a name="L520" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L520">520</a> #define <a href="ident?i=SNMP_PDU_INFORM">SNMP_PDU_INFORM</a>                 6
<a name="L521" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L521">521</a> #define <a href="ident?i=SNMP_PDU_TRAP2">SNMP_PDU_TRAP2</a>                  7
<a name="L522" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L523">523</a> <b><i>/* Errors */</i></b>
<a name="L524" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L524">524</a> #define <a href="ident?i=SNMP_NOERROR">SNMP_NOERROR</a>                    0
<a name="L525" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L525">525</a> #define <a href="ident?i=SNMP_TOOBIG">SNMP_TOOBIG</a>                     1
<a name="L526" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L526">526</a> #define <a href="ident?i=SNMP_NOSUCHNAME">SNMP_NOSUCHNAME</a>                 2
<a name="L527" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L527">527</a> #define <a href="ident?i=SNMP_BADVALUE">SNMP_BADVALUE</a>                   3
<a name="L528" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L528">528</a> #define <a href="ident?i=SNMP_READONLY">SNMP_READONLY</a>                   4
<a name="L529" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L529">529</a> #define <a href="ident?i=SNMP_GENERROR">SNMP_GENERROR</a>                   5
<a name="L530" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L530">530</a> #define <a href="ident?i=SNMP_NOACCESS">SNMP_NOACCESS</a>                   6
<a name="L531" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L531">531</a> #define <a href="ident?i=SNMP_WRONGTYPE">SNMP_WRONGTYPE</a>                  7
<a name="L532" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L532">532</a> #define <a href="ident?i=SNMP_WRONGLENGTH">SNMP_WRONGLENGTH</a>                8
<a name="L533" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L533">533</a> #define <a href="ident?i=SNMP_WRONGENCODING">SNMP_WRONGENCODING</a>              9
<a name="L534" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L534">534</a> #define <a href="ident?i=SNMP_WRONGVALUE">SNMP_WRONGVALUE</a>                 10
<a name="L535" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L535">535</a> #define <a href="ident?i=SNMP_NOCREATION">SNMP_NOCREATION</a>                 11
<a name="L536" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L536">536</a> #define <a href="ident?i=SNMP_INCONSISTENTVALUE">SNMP_INCONSISTENTVALUE</a>          12
<a name="L537" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L537">537</a> #define <a href="ident?i=SNMP_RESOURCEUNAVAILABLE">SNMP_RESOURCEUNAVAILABLE</a>        13
<a name="L538" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L538">538</a> #define <a href="ident?i=SNMP_COMMITFAILED">SNMP_COMMITFAILED</a>               14
<a name="L539" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L539">539</a> #define <a href="ident?i=SNMP_UNDOFAILED">SNMP_UNDOFAILED</a>                 15
<a name="L540" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L540">540</a> #define <a href="ident?i=SNMP_AUTHORIZATIONERROR">SNMP_AUTHORIZATIONERROR</a>         16
<a name="L541" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L541">541</a> #define <a href="ident?i=SNMP_NOTWRITABLE">SNMP_NOTWRITABLE</a>                17
<a name="L542" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L542">542</a> #define <a href="ident?i=SNMP_INCONSISTENTNAME">SNMP_INCONSISTENTNAME</a>           18
<a name="L543" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L544">544</a> <b><i>/* General SNMP V1 Traps */</i></b>
<a name="L545" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L545">545</a> #define <a href="ident?i=SNMP_TRAP_COLDSTART">SNMP_TRAP_COLDSTART</a>             0
<a name="L546" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L546">546</a> #define <a href="ident?i=SNMP_TRAP_WARMSTART">SNMP_TRAP_WARMSTART</a>             1
<a name="L547" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L547">547</a> #define <a href="ident?i=SNMP_TRAP_LINKDOWN">SNMP_TRAP_LINKDOWN</a>              2
<a name="L548" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L548">548</a> #define <a href="ident?i=SNMP_TRAP_LINKUP">SNMP_TRAP_LINKUP</a>                3
<a name="L549" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L549">549</a> #define <a href="ident?i=SNMP_TRAP_AUTFAILURE">SNMP_TRAP_AUTFAILURE</a>            4
<a name="L550" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L550">550</a> #define <a href="ident?i=SNMP_TRAP_EQPNEIGHBORLOSS">SNMP_TRAP_EQPNEIGHBORLOSS</a>       5
<a name="L551" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L551">551</a> #define <a href="ident?i=SNMP_TRAP_ENTSPECIFIC">SNMP_TRAP_ENTSPECIFIC</a>           6
<a name="L552" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L553">553</a> <b><i>/* SNMPv1 Types */</i></b>
<a name="L554" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L554">554</a> #define <a href="ident?i=SNMP_NULL">SNMP_NULL</a>                0
<a name="L555" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L555">555</a> #define <a href="ident?i=SNMP_INTEGER">SNMP_INTEGER</a>             1    <b><i>/* l  */</i></b>
<a name="L556" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L556">556</a> #define <a href="ident?i=SNMP_OCTETSTR">SNMP_OCTETSTR</a>            2    <b><i>/* c  */</i></b>
<a name="L557" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L557">557</a> #define <a href="ident?i=SNMP_DISPLAYSTR">SNMP_DISPLAYSTR</a>          2    <b><i>/* c  */</i></b>
<a name="L558" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L558">558</a> #define <a href="ident?i=SNMP_OBJECTID">SNMP_OBJECTID</a>            3    <b><i>/* ul */</i></b>
<a name="L559" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L559">559</a> #define <a href="ident?i=SNMP_IPADDR">SNMP_IPADDR</a>              4    <b><i>/* uc */</i></b>
<a name="L560" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L560">560</a> #define <a href="ident?i=SNMP_COUNTER">SNMP_COUNTER</a>             5    <b><i>/* ul */</i></b>
<a name="L561" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L561">561</a> #define <a href="ident?i=SNMP_GAUGE">SNMP_GAUGE</a>               6    <b><i>/* ul */</i></b>
<a name="L562" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L562">562</a> #define <a href="ident?i=SNMP_TIMETICKS">SNMP_TIMETICKS</a>           7    <b><i>/* ul */</i></b>
<a name="L563" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L563">563</a> #define <a href="ident?i=SNMP_OPAQUE">SNMP_OPAQUE</a>              8    <b><i>/* c  */</i></b>
<a name="L564" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L564">564</a> 
<a name="L565" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L565">565</a> <b><i>/* Additional SNMPv2 Types */</i></b>
<a name="L566" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L566">566</a> #define <a href="ident?i=SNMP_UINTEGER">SNMP_UINTEGER</a>            5    <b><i>/* ul */</i></b>
<a name="L567" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L567">567</a> #define <a href="ident?i=SNMP_BITSTR">SNMP_BITSTR</a>              9    <b><i>/* uc */</i></b>
<a name="L568" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L568">568</a> #define <a href="ident?i=SNMP_NSAP">SNMP_NSAP</a>               10    <b><i>/* uc */</i></b>
<a name="L569" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L569">569</a> #define <a href="ident?i=SNMP_COUNTER64">SNMP_COUNTER64</a>          11    <b><i>/* ul */</i></b>
<a name="L570" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L570">570</a> #define <a href="ident?i=SNMP_NOSUCHOBJECT">SNMP_NOSUCHOBJECT</a>       12
<a name="L571" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L571">571</a> #define <a href="ident?i=SNMP_NOSUCHINSTANCE">SNMP_NOSUCHINSTANCE</a>     13
<a name="L572" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L572">572</a> #define <a href="ident?i=SNMP_ENDOFMIBVIEW">SNMP_ENDOFMIBVIEW</a>       14
<a name="L573" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L574">574</a> union <a href="ident?i=snmp_syntax">snmp_syntax</a>
<a name="L575" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L575">575</a> {
<a name="L576" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L576">576</a>         unsigned char uc[0];    <b><i>/* 8 bit unsigned */</i></b>
<a name="L577" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L577">577</a>         char <a href="ident?i=c">c</a>[0];              <b><i>/* 8 bit signed */</i></b>
<a name="L578" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L578">578</a>         unsigned long ul[0];    <b><i>/* 32 bit unsigned */</i></b>
<a name="L579" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L579">579</a>         long <a href="ident?i=l">l</a>[0];              <b><i>/* 32 bit signed */</i></b>
<a name="L580" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L580">580</a> };
<a name="L581" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L582">582</a> struct <a href="ident?i=snmp_object">snmp_object</a>
<a name="L583" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L583">583</a> {
<a name="L584" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L584">584</a>         unsigned long *<a href="ident?i=id">id</a>;
<a name="L585" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L585">585</a>         unsigned int id_len;
<a name="L586" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L586">586</a>         unsigned short <a href="ident?i=type">type</a>;
<a name="L587" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L587">587</a>         unsigned int syntax_len;
<a name="L588" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L588">588</a>         union <a href="ident?i=snmp_syntax">snmp_syntax</a> syntax;
<a name="L589" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L589">589</a> };
<a name="L590" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L590">590</a> 
<a name="L591" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L591">591</a> struct <a href="ident?i=snmp_request">snmp_request</a>
<a name="L592" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L592">592</a> {
<a name="L593" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L593">593</a>         unsigned long <a href="ident?i=id">id</a>;
<a name="L594" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L594">594</a>         unsigned int error_status;
<a name="L595" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L595">595</a>         unsigned int error_index;
<a name="L596" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L596">596</a> };
<a name="L597" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L598">598</a> struct <a href="ident?i=snmp_v1_trap">snmp_v1_trap</a>
<a name="L599" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L599">599</a> {
<a name="L600" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L600">600</a>         unsigned long *<a href="ident?i=id">id</a>;
<a name="L601" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L601">601</a>         unsigned int id_len;
<a name="L602" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L602">602</a>         unsigned long ip_address;       <b><i>/* pointer  */</i></b>
<a name="L603" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L603">603</a>         unsigned int <a href="ident?i=general">general</a>;
<a name="L604" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L604">604</a>         unsigned int specific;
<a name="L605" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L605">605</a>         unsigned long <a href="ident?i=time">time</a>;
<a name="L606" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L606">606</a> };
<a name="L607" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L607">607</a> 
<a name="L608" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L608">608</a> <b><i>/* SNMP types */</i></b>
<a name="L609" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L609">609</a> #define <a href="ident?i=SNMP_IPA">SNMP_IPA</a>    0
<a name="L610" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L610">610</a> #define <a href="ident?i=SNMP_CNT">SNMP_CNT</a>    1
<a name="L611" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L611">611</a> #define <a href="ident?i=SNMP_GGE">SNMP_GGE</a>    2
<a name="L612" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L612">612</a> #define <a href="ident?i=SNMP_TIT">SNMP_TIT</a>    3
<a name="L613" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L613">613</a> #define <a href="ident?i=SNMP_OPQ">SNMP_OPQ</a>    4
<a name="L614" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L614">614</a> #define <a href="ident?i=SNMP_C64">SNMP_C64</a>    6
<a name="L615" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L615">615</a> 
<a name="L616" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L616">616</a> <b><i>/* SNMP errors */</i></b>
<a name="L617" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L617">617</a> #define <a href="ident?i=SERR_NSO">SERR_NSO</a>    0
<a name="L618" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L618">618</a> #define <a href="ident?i=SERR_NSI">SERR_NSI</a>    1
<a name="L619" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L619">619</a> #define <a href="ident?i=SERR_EOM">SERR_EOM</a>    2
<a name="L620" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L621">621</a> static inline void <a href="ident?i=mangle_address">mangle_address</a>(unsigned char *begin,
<a name="L622" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L622">622</a>                                   unsigned char *<a href="ident?i=addr">addr</a>,
<a name="L623" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L623">623</a>                                   const struct <a href="ident?i=oct1_map">oct1_map</a> *<a href="ident?i=map">map</a>,
<a name="L624" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L624">624</a>                                   <a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=check">check</a>);
<a name="L625" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L625">625</a> struct <a href="ident?i=snmp_cnv">snmp_cnv</a>
<a name="L626" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L626">626</a> {
<a name="L627" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L627">627</a>         unsigned int class;
<a name="L628" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L628">628</a>         unsigned int <a href="ident?i=tag">tag</a>;
<a name="L629" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L629">629</a>         int syntax;
<a name="L630" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L630">630</a> };
<a name="L631" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L631">631</a> 
<a name="L632" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L632">632</a> static const struct <a href="ident?i=snmp_cnv">snmp_cnv</a> <a href="ident?i=snmp_conv">snmp_conv</a>[] = {
<a name="L633" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L633">633</a>         {<a href="ident?i=ASN1_UNI">ASN1_UNI</a>, <a href="ident?i=ASN1_NUL">ASN1_NUL</a>, <a href="ident?i=SNMP_NULL">SNMP_NULL</a>},
<a name="L634" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L634">634</a>         {<a href="ident?i=ASN1_UNI">ASN1_UNI</a>, <a href="ident?i=ASN1_INT">ASN1_INT</a>, <a href="ident?i=SNMP_INTEGER">SNMP_INTEGER</a>},
<a name="L635" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L635">635</a>         {<a href="ident?i=ASN1_UNI">ASN1_UNI</a>, <a href="ident?i=ASN1_OTS">ASN1_OTS</a>, <a href="ident?i=SNMP_OCTETSTR">SNMP_OCTETSTR</a>},
<a name="L636" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L636">636</a>         {<a href="ident?i=ASN1_UNI">ASN1_UNI</a>, <a href="ident?i=ASN1_OTS">ASN1_OTS</a>, <a href="ident?i=SNMP_DISPLAYSTR">SNMP_DISPLAYSTR</a>},
<a name="L637" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L637">637</a>         {<a href="ident?i=ASN1_UNI">ASN1_UNI</a>, <a href="ident?i=ASN1_OJI">ASN1_OJI</a>, <a href="ident?i=SNMP_OBJECTID">SNMP_OBJECTID</a>},
<a name="L638" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L638">638</a>         {<a href="ident?i=ASN1_APL">ASN1_APL</a>, <a href="ident?i=SNMP_IPA">SNMP_IPA</a>, <a href="ident?i=SNMP_IPADDR">SNMP_IPADDR</a>},
<a name="L639" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L639">639</a>         {<a href="ident?i=ASN1_APL">ASN1_APL</a>, <a href="ident?i=SNMP_CNT">SNMP_CNT</a>, <a href="ident?i=SNMP_COUNTER">SNMP_COUNTER</a>},     <b><i>/* Counter32 */</i></b>
<a name="L640" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L640">640</a>         {<a href="ident?i=ASN1_APL">ASN1_APL</a>, <a href="ident?i=SNMP_GGE">SNMP_GGE</a>, <a href="ident?i=SNMP_GAUGE">SNMP_GAUGE</a>},       <b><i>/* Gauge32 == Unsigned32  */</i></b>
<a name="L641" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L641">641</a>         {<a href="ident?i=ASN1_APL">ASN1_APL</a>, <a href="ident?i=SNMP_TIT">SNMP_TIT</a>, <a href="ident?i=SNMP_TIMETICKS">SNMP_TIMETICKS</a>},
<a name="L642" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L642">642</a>         {<a href="ident?i=ASN1_APL">ASN1_APL</a>, <a href="ident?i=SNMP_OPQ">SNMP_OPQ</a>, <a href="ident?i=SNMP_OPAQUE">SNMP_OPAQUE</a>},
<a name="L643" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L643">643</a> 
<a name="L644" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L644">644</a>         <b><i>/* SNMPv2 data types and errors */</i></b>
<a name="L645" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L645">645</a>         {<a href="ident?i=ASN1_UNI">ASN1_UNI</a>, <a href="ident?i=ASN1_BTS">ASN1_BTS</a>, <a href="ident?i=SNMP_BITSTR">SNMP_BITSTR</a>},
<a name="L646" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L646">646</a>         {<a href="ident?i=ASN1_APL">ASN1_APL</a>, <a href="ident?i=SNMP_C64">SNMP_C64</a>, <a href="ident?i=SNMP_COUNTER64">SNMP_COUNTER64</a>},
<a name="L647" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L647">647</a>         {<a href="ident?i=ASN1_CTX">ASN1_CTX</a>, <a href="ident?i=SERR_NSO">SERR_NSO</a>, <a href="ident?i=SNMP_NOSUCHOBJECT">SNMP_NOSUCHOBJECT</a>},
<a name="L648" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L648">648</a>         {<a href="ident?i=ASN1_CTX">ASN1_CTX</a>, <a href="ident?i=SERR_NSI">SERR_NSI</a>, <a href="ident?i=SNMP_NOSUCHINSTANCE">SNMP_NOSUCHINSTANCE</a>},
<a name="L649" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L649">649</a>         {<a href="ident?i=ASN1_CTX">ASN1_CTX</a>, <a href="ident?i=SERR_EOM">SERR_EOM</a>, <a href="ident?i=SNMP_ENDOFMIBVIEW">SNMP_ENDOFMIBVIEW</a>},
<a name="L650" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L650">650</a>         {0,       0,       -1}
<a name="L651" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L651">651</a> };
<a name="L652" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L652">652</a> 
<a name="L653" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L653">653</a> static unsigned char <a href="ident?i=snmp_tag_cls2syntax">snmp_tag_cls2syntax</a>(unsigned int <a href="ident?i=tag">tag</a>,
<a name="L654" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L654">654</a>                                          unsigned int cls,
<a name="L655" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L655">655</a>                                          unsigned short *syntax)
<a name="L656" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L656">656</a> {
<a name="L657" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L657">657</a>         const struct <a href="ident?i=snmp_cnv">snmp_cnv</a> *cnv;
<a name="L658" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L658">658</a> 
<a name="L659" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L659">659</a>         cnv = <a href="ident?i=snmp_conv">snmp_conv</a>;
<a name="L660" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L661">661</a>         while (cnv-&gt;syntax != -1) {
<a name="L662" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L662">662</a>                 if (cnv-&gt;<a href="ident?i=tag">tag</a> == <a href="ident?i=tag">tag</a> &amp;&amp; cnv-&gt;class == cls) {
<a name="L663" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L663">663</a>                         *syntax = cnv-&gt;syntax;
<a name="L664" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L664">664</a>                         return 1;
<a name="L665" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L665">665</a>                 }
<a name="L666" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L666">666</a>                 cnv++;
<a name="L667" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L667">667</a>         }
<a name="L668" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L668">668</a>         return 0;
<a name="L669" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L669">669</a> }
<a name="L670" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L670">670</a> 
<a name="L671" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L671">671</a> static unsigned char <a href="ident?i=snmp_object_decode">snmp_object_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L672" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L672">672</a>                                         struct <a href="ident?i=snmp_object">snmp_object</a> **<a href="ident?i=obj">obj</a>)
<a name="L673" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L673">673</a> {
<a name="L674" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L674">674</a>         unsigned int cls, con, <a href="ident?i=tag">tag</a>, <a href="ident?i=len">len</a>, idlen;
<a name="L675" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L675">675</a>         unsigned short <a href="ident?i=type">type</a>;
<a name="L676" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L676">676</a>         unsigned char *eoc, *<a href="ident?i=end">end</a>, *<a href="ident?i=p">p</a>;
<a name="L677" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L677">677</a>         unsigned long *<a href="ident?i=lp">lp</a>, *<a href="ident?i=id">id</a>;
<a name="L678" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L678">678</a>         unsigned long ul;
<a name="L679" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L679">679</a>         long <a href="ident?i=l">l</a>;
<a name="L680" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L680">680</a> 
<a name="L681" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L681">681</a>         *<a href="ident?i=obj">obj</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L682" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L682">682</a>         <a href="ident?i=id">id</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L683" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L683">683</a> 
<a name="L684" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L684">684</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;eoc, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L685" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L685">685</a>                 return 0;
<a name="L686" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L687">687</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_CON">ASN1_CON</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_SEQ">ASN1_SEQ</a>)
<a name="L688" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L688">688</a>                 return 0;
<a name="L689" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L689">689</a> 
<a name="L690" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L690">690</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L691" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L691">691</a>                 return 0;
<a name="L692" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L692">692</a> 
<a name="L693" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L693">693</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_OJI">ASN1_OJI</a>)
<a name="L694" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L694">694</a>                 return 0;
<a name="L695" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L696">696</a>         if (!<a href="ident?i=asn1_oid_decode">asn1_oid_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=id">id</a>, &amp;idlen))
<a name="L697" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L697">697</a>                 return 0;
<a name="L698" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L698">698</a> 
<a name="L699" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L699">699</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>)) {
<a name="L700" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L700">700</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L701" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L701">701</a>                 return 0;
<a name="L702" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L702">702</a>         }
<a name="L703" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L703">703</a> 
<a name="L704" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L704">704</a>         if (con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a>) {
<a name="L705" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L705">705</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L706" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L706">706</a>                 return 0;
<a name="L707" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L707">707</a>         }
<a name="L708" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L708">708</a> 
<a name="L709" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L709">709</a>         <a href="ident?i=type">type</a> = 0;
<a name="L710" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L710">710</a>         if (!<a href="ident?i=snmp_tag_cls2syntax">snmp_tag_cls2syntax</a>(<a href="ident?i=tag">tag</a>, cls, &amp;<a href="ident?i=type">type</a>)) {
<a name="L711" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L711">711</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L712" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L712">712</a>                 return 0;
<a name="L713" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L713">713</a>         }
<a name="L714" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L714">714</a> 
<a name="L715" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L715">715</a>         <a href="ident?i=l">l</a> = 0;
<a name="L716" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L716">716</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L717" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L717">717</a>         case <a href="ident?i=SNMP_INTEGER">SNMP_INTEGER</a>:
<a name="L718" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L718">718</a>                 <a href="ident?i=len">len</a> = sizeof(long);
<a name="L719" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L719">719</a>                 if (!<a href="ident?i=asn1_long_decode">asn1_long_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=l">l</a>)) {
<a name="L720" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L720">720</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L721" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L721">721</a>                         return 0;
<a name="L722" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L722">722</a>                 }
<a name="L723" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L723">723</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=snmp_object">snmp_object</a>) + <a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L724" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L724">724</a>                 if (*<a href="ident?i=obj">obj</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L725" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L725">725</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L726" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L726">726</a>                         return 0;
<a name="L727" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L727">727</a>                 }
<a name="L728" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L728">728</a>                 (*<a href="ident?i=obj">obj</a>)-&gt;syntax.<a href="ident?i=l">l</a>[0] = <a href="ident?i=l">l</a>;
<a name="L729" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L729">729</a>                 break;
<a name="L730" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L730">730</a>         case <a href="ident?i=SNMP_OCTETSTR">SNMP_OCTETSTR</a>:
<a name="L731" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L731">731</a>         case <a href="ident?i=SNMP_OPAQUE">SNMP_OPAQUE</a>:
<a name="L732" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L732">732</a>                 if (!<a href="ident?i=asn1_octets_decode">asn1_octets_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=p">p</a>, &amp;<a href="ident?i=len">len</a>)) {
<a name="L733" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L733">733</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L734" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L734">734</a>                         return 0;
<a name="L735" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L735">735</a>                 }
<a name="L736" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L736">736</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=snmp_object">snmp_object</a>) + <a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L737" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L737">737</a>                 if (*<a href="ident?i=obj">obj</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L738" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L738">738</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=p">p</a>);
<a name="L739" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L739">739</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L740" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L740">740</a>                         return 0;
<a name="L741" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L741">741</a>                 }
<a name="L742" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L742">742</a>                 <a href="ident?i=memcpy">memcpy</a>((*<a href="ident?i=obj">obj</a>)-&gt;syntax.<a href="ident?i=c">c</a>, <a href="ident?i=p">p</a>, <a href="ident?i=len">len</a>);
<a name="L743" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L743">743</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=p">p</a>);
<a name="L744" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L744">744</a>                 break;
<a name="L745" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L745">745</a>         case <a href="ident?i=SNMP_NULL">SNMP_NULL</a>:
<a name="L746" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L746">746</a>         case <a href="ident?i=SNMP_NOSUCHOBJECT">SNMP_NOSUCHOBJECT</a>:
<a name="L747" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L747">747</a>         case <a href="ident?i=SNMP_NOSUCHINSTANCE">SNMP_NOSUCHINSTANCE</a>:
<a name="L748" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L748">748</a>         case <a href="ident?i=SNMP_ENDOFMIBVIEW">SNMP_ENDOFMIBVIEW</a>:
<a name="L749" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L749">749</a>                 <a href="ident?i=len">len</a> = 0;
<a name="L750" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L750">750</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=snmp_object">snmp_object</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L751" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L751">751</a>                 if (*<a href="ident?i=obj">obj</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L752" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L752">752</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L753" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L753">753</a>                         return 0;
<a name="L754" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L754">754</a>                 }
<a name="L755" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L755">755</a>                 if (!<a href="ident?i=asn1_null_decode">asn1_null_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>)) {
<a name="L756" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L756">756</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L757" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L757">757</a>                         <a href="ident?i=kfree">kfree</a>(*<a href="ident?i=obj">obj</a>);
<a name="L758" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L758">758</a>                         *<a href="ident?i=obj">obj</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L759" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L759">759</a>                         return 0;
<a name="L760" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L760">760</a>                 }
<a name="L761" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L761">761</a>                 break;
<a name="L762" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L762">762</a>         case <a href="ident?i=SNMP_OBJECTID">SNMP_OBJECTID</a>:
<a name="L763" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L763">763</a>                 if (!<a href="ident?i=asn1_oid_decode">asn1_oid_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=lp">lp</a>, &amp;<a href="ident?i=len">len</a>)) {
<a name="L764" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L764">764</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L765" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L765">765</a>                         return 0;
<a name="L766" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L766">766</a>                 }
<a name="L767" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L767">767</a>                 <a href="ident?i=len">len</a> *= sizeof(unsigned long);
<a name="L768" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L768">768</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=snmp_object">snmp_object</a>) + <a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L769" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L769">769</a>                 if (*<a href="ident?i=obj">obj</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L770" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L770">770</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=lp">lp</a>);
<a name="L771" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L771">771</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L772" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L772">772</a>                         return 0;
<a name="L773" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L773">773</a>                 }
<a name="L774" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L774">774</a>                 <a href="ident?i=memcpy">memcpy</a>((*<a href="ident?i=obj">obj</a>)-&gt;syntax.ul, <a href="ident?i=lp">lp</a>, <a href="ident?i=len">len</a>);
<a name="L775" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L775">775</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=lp">lp</a>);
<a name="L776" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L776">776</a>                 break;
<a name="L777" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L777">777</a>         case <a href="ident?i=SNMP_IPADDR">SNMP_IPADDR</a>:
<a name="L778" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L778">778</a>                 if (!<a href="ident?i=asn1_octets_decode">asn1_octets_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=p">p</a>, &amp;<a href="ident?i=len">len</a>)) {
<a name="L779" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L779">779</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L780" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L780">780</a>                         return 0;
<a name="L781" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L781">781</a>                 }
<a name="L782" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L782">782</a>                 if (<a href="ident?i=len">len</a> != 4) {
<a name="L783" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L783">783</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=p">p</a>);
<a name="L784" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L784">784</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L785" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L785">785</a>                         return 0;
<a name="L786" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L786">786</a>                 }
<a name="L787" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L787">787</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=snmp_object">snmp_object</a>) + <a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L788" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L788">788</a>                 if (*<a href="ident?i=obj">obj</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L789" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L789">789</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=p">p</a>);
<a name="L790" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L790">790</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L791" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L791">791</a>                         return 0;
<a name="L792" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L792">792</a>                 }
<a name="L793" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L793">793</a>                 <a href="ident?i=memcpy">memcpy</a>((*<a href="ident?i=obj">obj</a>)-&gt;syntax.uc, <a href="ident?i=p">p</a>, <a href="ident?i=len">len</a>);
<a name="L794" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L794">794</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=p">p</a>);
<a name="L795" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L795">795</a>                 break;
<a name="L796" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L796">796</a>         case <a href="ident?i=SNMP_COUNTER">SNMP_COUNTER</a>:
<a name="L797" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L797">797</a>         case <a href="ident?i=SNMP_GAUGE">SNMP_GAUGE</a>:
<a name="L798" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L798">798</a>         case <a href="ident?i=SNMP_TIMETICKS">SNMP_TIMETICKS</a>:
<a name="L799" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L799">799</a>                 <a href="ident?i=len">len</a> = sizeof(unsigned long);
<a name="L800" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L800">800</a>                 if (!<a href="ident?i=asn1_ulong_decode">asn1_ulong_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;ul)) {
<a name="L801" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L801">801</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L802" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L802">802</a>                         return 0;
<a name="L803" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L803">803</a>                 }
<a name="L804" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L804">804</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=snmp_object">snmp_object</a>) + <a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L805" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L805">805</a>                 if (*<a href="ident?i=obj">obj</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L806" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L806">806</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L807" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L807">807</a>                         return 0;
<a name="L808" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L808">808</a>                 }
<a name="L809" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L809">809</a>                 (*<a href="ident?i=obj">obj</a>)-&gt;syntax.ul[0] = ul;
<a name="L810" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L810">810</a>                 break;
<a name="L811" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L811">811</a>         default:
<a name="L812" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L812">812</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L813" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L813">813</a>                 return 0;
<a name="L814" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L814">814</a>         }
<a name="L815" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L816">816</a>         (*<a href="ident?i=obj">obj</a>)-&gt;syntax_len = <a href="ident?i=len">len</a>;
<a name="L817" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L817">817</a>         (*<a href="ident?i=obj">obj</a>)-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=type">type</a>;
<a name="L818" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L818">818</a>         (*<a href="ident?i=obj">obj</a>)-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=id">id</a>;
<a name="L819" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L819">819</a>         (*<a href="ident?i=obj">obj</a>)-&gt;id_len = idlen;
<a name="L820" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L820">820</a> 
<a name="L821" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L821">821</a>         if (!<a href="ident?i=asn1_eoc_decode">asn1_eoc_decode</a>(<a href="ident?i=ctx">ctx</a>, eoc)) {
<a name="L822" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L822">822</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=id">id</a>);
<a name="L823" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L823">823</a>                 <a href="ident?i=kfree">kfree</a>(*<a href="ident?i=obj">obj</a>);
<a name="L824" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L824">824</a>                 *<a href="ident?i=obj">obj</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L825" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L825">825</a>                 return 0;
<a name="L826" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L826">826</a>         }
<a name="L827" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L827">827</a>         return 1;
<a name="L828" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L828">828</a> }
<a name="L829" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L830">830</a> static unsigned char <a href="ident?i=snmp_request_decode">snmp_request_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L831" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L831">831</a>                                          struct <a href="ident?i=snmp_request">snmp_request</a> *<a href="ident?i=request">request</a>)
<a name="L832" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L832">832</a> {
<a name="L833" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L833">833</a>         unsigned int cls, con, <a href="ident?i=tag">tag</a>;
<a name="L834" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L834">834</a>         unsigned char *<a href="ident?i=end">end</a>;
<a name="L835" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L835">835</a> 
<a name="L836" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L836">836</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L837" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L837">837</a>                 return 0;
<a name="L838" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L838">838</a> 
<a name="L839" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L839">839</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_INT">ASN1_INT</a>)
<a name="L840" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L840">840</a>                 return 0;
<a name="L841" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L841">841</a> 
<a name="L842" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L842">842</a>         if (!<a href="ident?i=asn1_ulong_decode">asn1_ulong_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=request">request</a>-&gt;<a href="ident?i=id">id</a>))
<a name="L843" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L843">843</a>                 return 0;
<a name="L844" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L844">844</a> 
<a name="L845" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L845">845</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L846" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L846">846</a>                 return 0;
<a name="L847" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L848">848</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_INT">ASN1_INT</a>)
<a name="L849" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L849">849</a>                 return 0;
<a name="L850" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L851">851</a>         if (!<a href="ident?i=asn1_uint_decode">asn1_uint_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=request">request</a>-&gt;error_status))
<a name="L852" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L852">852</a>                 return 0;
<a name="L853" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L853">853</a> 
<a name="L854" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L854">854</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L855" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L855">855</a>                 return 0;
<a name="L856" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L857">857</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_INT">ASN1_INT</a>)
<a name="L858" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L858">858</a>                 return 0;
<a name="L859" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L860">860</a>         if (!<a href="ident?i=asn1_uint_decode">asn1_uint_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=request">request</a>-&gt;error_index))
<a name="L861" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L861">861</a>                 return 0;
<a name="L862" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L863">863</a>         return 1;
<a name="L864" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L864">864</a> }
<a name="L865" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L865">865</a> 
<a name="L866" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L866">866</a> <b><i>/*</i></b>
<a name="L867" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L867">867</a> <b><i> * Fast checksum update for possibly oddly-aligned UDP byte, from the</i></b>
<a name="L868" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L868">868</a> <b><i> * code example in the draft.</i></b>
<a name="L869" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L869">869</a> <b><i> */</i></b>
<a name="L870" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L870">870</a> static void <a href="ident?i=fast_csum">fast_csum</a>(<a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=csum">csum</a>,
<a name="L871" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L871">871</a>                       const unsigned char *optr,
<a name="L872" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L872">872</a>                       const unsigned char *nptr,
<a name="L873" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L873">873</a>                       int <a href="ident?i=offset">offset</a>)
<a name="L874" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L874">874</a> {
<a name="L875" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L875">875</a>         unsigned char <a href="ident?i=s">s</a>[4];
<a name="L876" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L876">876</a> 
<a name="L877" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L877">877</a>         if (<a href="ident?i=offset">offset</a> &amp; 1) {
<a name="L878" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L878">878</a>                 <a href="ident?i=s">s</a>[0] = ~0;
<a name="L879" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L879">879</a>                 <a href="ident?i=s">s</a>[1] = ~*optr;
<a name="L880" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L880">880</a>                 <a href="ident?i=s">s</a>[2] = 0;
<a name="L881" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L881">881</a>                 <a href="ident?i=s">s</a>[3] = *nptr;
<a name="L882" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L882">882</a>         } else {
<a name="L883" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L883">883</a>                 <a href="ident?i=s">s</a>[0] = ~*optr;
<a name="L884" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L884">884</a>                 <a href="ident?i=s">s</a>[1] = ~0;
<a name="L885" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L885">885</a>                 <a href="ident?i=s">s</a>[2] = *nptr;
<a name="L886" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L886">886</a>                 <a href="ident?i=s">s</a>[3] = 0;
<a name="L887" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L887">887</a>         }
<a name="L888" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L888">888</a> 
<a name="L889" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L889">889</a>         *<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=csum_partial">csum_partial</a>(<a href="ident?i=s">s</a>, 4, ~csum_unfold(*<a href="ident?i=csum">csum</a>)));
<a name="L890" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L890">890</a> }
<a name="L891" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L892">892</a> <b><i>/*</i></b>
<a name="L893" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L893">893</a> <b><i> * Mangle IP address.</i></b>
<a name="L894" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L894">894</a> <b><i> *      - begin points to the start of the snmp messgae</i></b>
<a name="L895" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L895">895</a> <b><i> *      - addr points to the start of the address</i></b>
<a name="L896" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L896">896</a> <b><i> */</i></b>
<a name="L897" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L897">897</a> static inline void <a href="ident?i=mangle_address">mangle_address</a>(unsigned char *begin,
<a name="L898" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L898">898</a>                                   unsigned char *<a href="ident?i=addr">addr</a>,
<a name="L899" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L899">899</a>                                   const struct <a href="ident?i=oct1_map">oct1_map</a> *<a href="ident?i=map">map</a>,
<a name="L900" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L900">900</a>                                   <a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=check">check</a>)
<a name="L901" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L901">901</a> {
<a name="L902" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L902">902</a>         if (<a href="ident?i=map">map</a>-&gt;from == <a href="ident?i=NOCT1">NOCT1</a>(<a href="ident?i=addr">addr</a>)) {
<a name="L903" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L903">903</a>                 <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=old">old</a>;
<a name="L904" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L904">904</a> 
<a name="L905" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L905">905</a>                 if (<a href="ident?i=debug">debug</a>)
<a name="L906" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L906">906</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=old">old</a>, <a href="ident?i=addr">addr</a>, sizeof(<a href="ident?i=old">old</a>));
<a name="L907" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L907">907</a> 
<a name="L908" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L908">908</a>                 *<a href="ident?i=addr">addr</a> = <a href="ident?i=map">map</a>-&gt;to;
<a name="L909" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L909">909</a> 
<a name="L910" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L910">910</a>                 <b><i>/* Update UDP checksum if being used */</i></b>
<a name="L911" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L911">911</a>                 if (*<a href="ident?i=check">check</a>) {
<a name="L912" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L912">912</a>                         <a href="ident?i=fast_csum">fast_csum</a>(<a href="ident?i=check">check</a>,
<a name="L913" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L913">913</a>                                   &amp;<a href="ident?i=map">map</a>-&gt;from, &amp;<a href="ident?i=map">map</a>-&gt;to, <a href="ident?i=addr">addr</a> - begin);
<a name="L914" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L915">915</a>                 }
<a name="L916" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L916">916</a> 
<a name="L917" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L917">917</a>                 if (<a href="ident?i=debug">debug</a>)
<a name="L918" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L918">918</a>                         <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: mapped %pI4 to %pI4\n"</i>,
<a name="L919" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L919">919</a>                                &amp;<a href="ident?i=old">old</a>, <a href="ident?i=addr">addr</a>);
<a name="L920" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L920">920</a>         }
<a name="L921" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L921">921</a> }
<a name="L922" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L922">922</a> 
<a name="L923" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L923">923</a> static unsigned char <a href="ident?i=snmp_trap_decode">snmp_trap_decode</a>(struct <a href="ident?i=asn1_ctx">asn1_ctx</a> *<a href="ident?i=ctx">ctx</a>,
<a name="L924" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L924">924</a>                                       struct <a href="ident?i=snmp_v1_trap">snmp_v1_trap</a> *<a href="ident?i=trap">trap</a>,
<a name="L925" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L925">925</a>                                       const struct <a href="ident?i=oct1_map">oct1_map</a> *<a href="ident?i=map">map</a>,
<a name="L926" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L926">926</a>                                       <a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=check">check</a>)
<a name="L927" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L927">927</a> {
<a name="L928" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L928">928</a>         unsigned int cls, con, <a href="ident?i=tag">tag</a>, <a href="ident?i=len">len</a>;
<a name="L929" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L929">929</a>         unsigned char *<a href="ident?i=end">end</a>;
<a name="L930" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L931">931</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L932" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L932">932</a>                 return 0;
<a name="L933" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L933">933</a> 
<a name="L934" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L934">934</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_OJI">ASN1_OJI</a>)
<a name="L935" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L935">935</a>                 return 0;
<a name="L936" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L937">937</a>         if (!<a href="ident?i=asn1_oid_decode">asn1_oid_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=trap">trap</a>-&gt;<a href="ident?i=id">id</a>, &amp;<a href="ident?i=trap">trap</a>-&gt;id_len))
<a name="L938" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L938">938</a>                 return 0;
<a name="L939" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L939">939</a> 
<a name="L940" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L940">940</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L941" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L941">941</a>                 goto err_id_free;
<a name="L942" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L942">942</a> 
<a name="L943" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L943">943</a>         if (!((cls == <a href="ident?i=ASN1_APL">ASN1_APL</a> &amp;&amp; con == <a href="ident?i=ASN1_PRI">ASN1_PRI</a> &amp;&amp; <a href="ident?i=tag">tag</a> == <a href="ident?i=SNMP_IPA">SNMP_IPA</a>) ||
<a name="L944" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L944">944</a>               (cls == <a href="ident?i=ASN1_UNI">ASN1_UNI</a> &amp;&amp; con == <a href="ident?i=ASN1_PRI">ASN1_PRI</a> &amp;&amp; <a href="ident?i=tag">tag</a> == <a href="ident?i=ASN1_OTS">ASN1_OTS</a>)))
<a name="L945" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L945">945</a>                 goto err_id_free;
<a name="L946" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L946">946</a> 
<a name="L947" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L947">947</a>         if (!<a href="ident?i=asn1_octets_decode">asn1_octets_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, (unsigned char **)&amp;<a href="ident?i=trap">trap</a>-&gt;ip_address, &amp;<a href="ident?i=len">len</a>))
<a name="L948" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L948">948</a>                 goto err_id_free;
<a name="L949" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L949">949</a> 
<a name="L950" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L950">950</a>         <b><i>/* IPv4 only */</i></b>
<a name="L951" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L951">951</a>         if (<a href="ident?i=len">len</a> != 4)
<a name="L952" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L952">952</a>                 goto err_addr_free;
<a name="L953" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L954">954</a>         <a href="ident?i=mangle_address">mangle_address</a>(<a href="ident?i=ctx">ctx</a>-&gt;begin, <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=pointer">pointer</a> - 4, <a href="ident?i=map">map</a>, <a href="ident?i=check">check</a>);
<a name="L955" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L955">955</a> 
<a name="L956" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L956">956</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L957" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L957">957</a>                 goto err_addr_free;
<a name="L958" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L959">959</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_INT">ASN1_INT</a>)
<a name="L960" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L960">960</a>                 goto err_addr_free;
<a name="L961" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L962">962</a>         if (!<a href="ident?i=asn1_uint_decode">asn1_uint_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=trap">trap</a>-&gt;<a href="ident?i=general">general</a>))
<a name="L963" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L963">963</a>                 goto err_addr_free;
<a name="L964" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L965">965</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L966" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L966">966</a>                 goto err_addr_free;
<a name="L967" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L967">967</a> 
<a name="L968" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L968">968</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_INT">ASN1_INT</a>)
<a name="L969" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L969">969</a>                 goto err_addr_free;
<a name="L970" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L970">970</a> 
<a name="L971" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L971">971</a>         if (!<a href="ident?i=asn1_uint_decode">asn1_uint_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=trap">trap</a>-&gt;specific))
<a name="L972" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L972">972</a>                 goto err_addr_free;
<a name="L973" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L973">973</a> 
<a name="L974" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L974">974</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L975" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L975">975</a>                 goto err_addr_free;
<a name="L976" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L976">976</a> 
<a name="L977" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L977">977</a>         if (!((cls == <a href="ident?i=ASN1_APL">ASN1_APL</a> &amp;&amp; con == <a href="ident?i=ASN1_PRI">ASN1_PRI</a> &amp;&amp; <a href="ident?i=tag">tag</a> == <a href="ident?i=SNMP_TIT">SNMP_TIT</a>) ||
<a name="L978" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L978">978</a>               (cls == <a href="ident?i=ASN1_UNI">ASN1_UNI</a> &amp;&amp; con == <a href="ident?i=ASN1_PRI">ASN1_PRI</a> &amp;&amp; <a href="ident?i=tag">tag</a> == <a href="ident?i=ASN1_INT">ASN1_INT</a>)))
<a name="L979" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L979">979</a>                 goto err_addr_free;
<a name="L980" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L980">980</a> 
<a name="L981" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L981">981</a>         if (!<a href="ident?i=asn1_ulong_decode">asn1_ulong_decode</a>(<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=trap">trap</a>-&gt;<a href="ident?i=time">time</a>))
<a name="L982" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L982">982</a>                 goto err_addr_free;
<a name="L983" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L983">983</a> 
<a name="L984" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L984">984</a>         return 1;
<a name="L985" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L986">986</a> err_addr_free:
<a name="L987" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L987">987</a>         <a href="ident?i=kfree">kfree</a>((unsigned long *)<a href="ident?i=trap">trap</a>-&gt;ip_address);
<a name="L988" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L988">988</a> 
<a name="L989" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L989">989</a> err_id_free:
<a name="L990" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L990">990</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=trap">trap</a>-&gt;<a href="ident?i=id">id</a>);
<a name="L991" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L991">991</a> 
<a name="L992" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L992">992</a>         return 0;
<a name="L993" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L993">993</a> }
<a name="L994" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L994">994</a> 
<a name="L995" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L995">995</a> <b><i>/*****************************************************************************</i></b>
<a name="L996" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L996">996</a> <b><i> *</i></b>
<a name="L997" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L997">997</a> <b><i> * Misc. routines</i></b>
<a name="L998" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L998">998</a> <b><i> *</i></b>
<a name="L999" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L999">999</a> <b><i> *****************************************************************************/</i></b>
<a name="L1000" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1000">1000</a> 
<a name="L1001" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1001">1001</a> static void <a href="ident?i=hex_dump">hex_dump</a>(const unsigned char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>)
<a name="L1002" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1002">1002</a> {
<a name="L1003" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1003">1003</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=i">i</a>;
<a name="L1004" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1004">1004</a> 
<a name="L1005" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1005">1005</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=len">len</a>; <a href="ident?i=i">i</a>++) {
<a name="L1006" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1006">1006</a>                 if (<a href="ident?i=i">i</a> &amp;&amp; !(<a href="ident?i=i">i</a> % 16))
<a name="L1007" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1007">1007</a>                         <a href="ident?i=printk">printk</a>(<i>"\n"</i>);
<a name="L1008" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1008">1008</a>                 <a href="ident?i=printk">printk</a>(<i>"%02x "</i>, *(<a href="ident?i=buf">buf</a> + <a href="ident?i=i">i</a>));
<a name="L1009" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1009">1009</a>         }
<a name="L1010" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1010">1010</a>         <a href="ident?i=printk">printk</a>(<i>"\n"</i>);
<a name="L1011" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1011">1011</a> }
<a name="L1012" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1012">1012</a> 
<a name="L1013" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1013">1013</a> <b><i>/*</i></b>
<a name="L1014" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1014">1014</a> <b><i> * Parse and mangle SNMP message according to mapping.</i></b>
<a name="L1015" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1015">1015</a> <b><i> * (And this is the fucking 'basic' method).</i></b>
<a name="L1016" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1016">1016</a> <b><i> */</i></b>
<a name="L1017" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1017">1017</a> static int <a href="ident?i=snmp_parse_mangle">snmp_parse_mangle</a>(unsigned char *<a href="ident?i=msg">msg</a>,
<a name="L1018" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1018">1018</a>                              <a href="ident?i=u_int16_t">u_int16_t</a> <a href="ident?i=len">len</a>,
<a name="L1019" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1019">1019</a>                              const struct <a href="ident?i=oct1_map">oct1_map</a> *<a href="ident?i=map">map</a>,
<a name="L1020" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1020">1020</a>                              <a href="ident?i=__sum16">__sum16</a> *<a href="ident?i=check">check</a>)
<a name="L1021" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1021">1021</a> {
<a name="L1022" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1022">1022</a>         unsigned char *eoc, *<a href="ident?i=end">end</a>;
<a name="L1023" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1023">1023</a>         unsigned int cls, con, <a href="ident?i=tag">tag</a>, vers, pdutype;
<a name="L1024" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1024">1024</a>         struct <a href="ident?i=asn1_ctx">asn1_ctx</a> <a href="ident?i=ctx">ctx</a>;
<a name="L1025" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1025">1025</a>         struct <a href="ident?i=asn1_octstr">asn1_octstr</a> <a href="ident?i=comm">comm</a>;
<a name="L1026" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1026">1026</a>         struct <a href="ident?i=snmp_object">snmp_object</a> *<a href="ident?i=obj">obj</a>;
<a name="L1027" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1027">1027</a> 
<a name="L1028" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1028">1028</a>         if (<a href="ident?i=debug">debug</a> &gt; 1)
<a name="L1029" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1029">1029</a>                 <a href="ident?i=hex_dump">hex_dump</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>);
<a name="L1030" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1031">1031</a>         <a href="ident?i=asn1_open">asn1_open</a>(&amp;<a href="ident?i=ctx">ctx</a>, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>);
<a name="L1032" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1033">1033</a>         <b><i>/*</i></b>
<a name="L1034" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1034">1034</a> <b><i>         * Start of SNMP message.</i></b>
<a name="L1035" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1035">1035</a> <b><i>         */</i></b>
<a name="L1036" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1036">1036</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;eoc, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L1037" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1037">1037</a>                 return 0;
<a name="L1038" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1038">1038</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_CON">ASN1_CON</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_SEQ">ASN1_SEQ</a>)
<a name="L1039" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1039">1039</a>                 return 0;
<a name="L1040" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1041">1041</a>         <b><i>/*</i></b>
<a name="L1042" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1042">1042</a> <b><i>         * Version 1 or 2 handled.</i></b>
<a name="L1043" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1043">1043</a> <b><i>         */</i></b>
<a name="L1044" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1044">1044</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L1045" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1045">1045</a>                 return 0;
<a name="L1046" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1046">1046</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_INT">ASN1_INT</a>)
<a name="L1047" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1047">1047</a>                 return 0;
<a name="L1048" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1048">1048</a>         if (!<a href="ident?i=asn1_uint_decode">asn1_uint_decode</a> (&amp;<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;vers))
<a name="L1049" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1049">1049</a>                 return 0;
<a name="L1050" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1050">1050</a>         if (<a href="ident?i=debug">debug</a> &gt; 1)
<a name="L1051" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1051">1051</a>                 <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: snmp version: %u\n"</i>, vers + 1);
<a name="L1052" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1052">1052</a>         if (vers &gt; 1)
<a name="L1053" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1053">1053</a>                 return 1;
<a name="L1054" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1054">1054</a> 
<a name="L1055" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1055">1055</a>         <b><i>/*</i></b>
<a name="L1056" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1056">1056</a> <b><i>         * Community.</i></b>
<a name="L1057" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1057">1057</a> <b><i>         */</i></b>
<a name="L1058" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1058">1058</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a> (&amp;<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=end">end</a>, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L1059" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1059">1059</a>                 return 0;
<a name="L1060" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1060">1060</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_PRI">ASN1_PRI</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_OTS">ASN1_OTS</a>)
<a name="L1061" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1061">1061</a>                 return 0;
<a name="L1062" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1062">1062</a>         if (!<a href="ident?i=asn1_octets_decode">asn1_octets_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, <a href="ident?i=end">end</a>, &amp;<a href="ident?i=comm">comm</a>.<a href="ident?i=data">data</a>, &amp;<a href="ident?i=comm">comm</a>.<a href="ident?i=len">len</a>))
<a name="L1063" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1063">1063</a>                 return 0;
<a name="L1064" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1064">1064</a>         if (<a href="ident?i=debug">debug</a> &gt; 1) {
<a name="L1065" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1065">1065</a>                 unsigned int <a href="ident?i=i">i</a>;
<a name="L1066" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1066">1066</a> 
<a name="L1067" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1067">1067</a>                 <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: community: "</i>);
<a name="L1068" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1068">1068</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=comm">comm</a>.<a href="ident?i=len">len</a>; <a href="ident?i=i">i</a>++)
<a name="L1069" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1069">1069</a>                         <a href="ident?i=printk">printk</a>(<i>"%c"</i>, <a href="ident?i=comm">comm</a>.<a href="ident?i=data">data</a>[<a href="ident?i=i">i</a>]);
<a name="L1070" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1070">1070</a>                 <a href="ident?i=printk">printk</a>(<i>"\n"</i>);
<a name="L1071" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1071">1071</a>         }
<a name="L1072" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1072">1072</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=comm">comm</a>.<a href="ident?i=data">data</a>);
<a name="L1073" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1073">1073</a> 
<a name="L1074" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1074">1074</a>         <b><i>/*</i></b>
<a name="L1075" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1075">1075</a> <b><i>         * PDU type</i></b>
<a name="L1076" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1076">1076</a> <b><i>         */</i></b>
<a name="L1077" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1077">1077</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;eoc, &amp;cls, &amp;con, &amp;pdutype))
<a name="L1078" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1078">1078</a>                 return 0;
<a name="L1079" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1079">1079</a>         if (cls != <a href="ident?i=ASN1_CTX">ASN1_CTX</a> || con != <a href="ident?i=ASN1_CON">ASN1_CON</a>)
<a name="L1080" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1080">1080</a>                 return 0;
<a name="L1081" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1081">1081</a>         if (<a href="ident?i=debug">debug</a> &gt; 1) {
<a name="L1082" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1082">1082</a>                 static const unsigned char *const pdus[] = {
<a name="L1083" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1083">1083</a>                         [<a href="ident?i=SNMP_PDU_GET">SNMP_PDU_GET</a>] = <i>"get"</i>,
<a name="L1084" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1084">1084</a>                         [<a href="ident?i=SNMP_PDU_NEXT">SNMP_PDU_NEXT</a>] = <i>"get-next"</i>,
<a name="L1085" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1085">1085</a>                         [<a href="ident?i=SNMP_PDU_RESPONSE">SNMP_PDU_RESPONSE</a>] = <i>"response"</i>,
<a name="L1086" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1086">1086</a>                         [<a href="ident?i=SNMP_PDU_SET">SNMP_PDU_SET</a>] = <i>"set"</i>,
<a name="L1087" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1087">1087</a>                         [<a href="ident?i=SNMP_PDU_TRAP1">SNMP_PDU_TRAP1</a>] = <i>"trapv1"</i>,
<a name="L1088" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1088">1088</a>                         [<a href="ident?i=SNMP_PDU_BULK">SNMP_PDU_BULK</a>] = <i>"bulk"</i>,
<a name="L1089" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1089">1089</a>                         [<a href="ident?i=SNMP_PDU_INFORM">SNMP_PDU_INFORM</a>] = <i>"inform"</i>,
<a name="L1090" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1090">1090</a>                         [<a href="ident?i=SNMP_PDU_TRAP2">SNMP_PDU_TRAP2</a>] = <i>"trapv2"</i>
<a name="L1091" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1091">1091</a>                 };
<a name="L1092" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1092">1092</a> 
<a name="L1093" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1093">1093</a>                 if (pdutype &gt; <a href="ident?i=SNMP_PDU_TRAP2">SNMP_PDU_TRAP2</a>)
<a name="L1094" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1094">1094</a>                         <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: bad pdu type %u\n"</i>, pdutype);
<a name="L1095" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1095">1095</a>                 else
<a name="L1096" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1096">1096</a>                         <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: pdu: %s\n"</i>, pdus[pdutype]);
<a name="L1097" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1097">1097</a>         }
<a name="L1098" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1098">1098</a>         if (pdutype != <a href="ident?i=SNMP_PDU_RESPONSE">SNMP_PDU_RESPONSE</a> &amp;&amp;
<a name="L1099" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1099">1099</a>             pdutype != <a href="ident?i=SNMP_PDU_TRAP1">SNMP_PDU_TRAP1</a> &amp;&amp; pdutype != <a href="ident?i=SNMP_PDU_TRAP2">SNMP_PDU_TRAP2</a>)
<a name="L1100" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1100">1100</a>                 return 1;
<a name="L1101" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1101">1101</a> 
<a name="L1102" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1102">1102</a>         <b><i>/*</i></b>
<a name="L1103" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1103">1103</a> <b><i>         * Request header or v1 trap</i></b>
<a name="L1104" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1104">1104</a> <b><i>         */</i></b>
<a name="L1105" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1105">1105</a>         if (pdutype == <a href="ident?i=SNMP_PDU_TRAP1">SNMP_PDU_TRAP1</a>) {
<a name="L1106" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1106">1106</a>                 struct <a href="ident?i=snmp_v1_trap">snmp_v1_trap</a> <a href="ident?i=trap">trap</a>;
<a name="L1107" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1107">1107</a>                 unsigned char <a href="ident?i=ret">ret</a> = <a href="ident?i=snmp_trap_decode">snmp_trap_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=trap">trap</a>, <a href="ident?i=map">map</a>, <a href="ident?i=check">check</a>);
<a name="L1108" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1108">1108</a> 
<a name="L1109" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1109">1109</a>                 if (<a href="ident?i=ret">ret</a>) {
<a name="L1110" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1110">1110</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=trap">trap</a>.<a href="ident?i=id">id</a>);
<a name="L1111" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1111">1111</a>                         <a href="ident?i=kfree">kfree</a>((unsigned long *)<a href="ident?i=trap">trap</a>.ip_address);
<a name="L1112" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1112">1112</a>                 } else
<a name="L1113" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1113">1113</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L1114" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1115">1115</a>         } else {
<a name="L1116" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1116">1116</a>                 struct <a href="ident?i=snmp_request">snmp_request</a> <a href="ident?i=req">req</a>;
<a name="L1117" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1117">1117</a> 
<a name="L1118" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1118">1118</a>                 if (!<a href="ident?i=snmp_request_decode">snmp_request_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=req">req</a>))
<a name="L1119" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1119">1119</a>                         return 0;
<a name="L1120" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1120">1120</a> 
<a name="L1121" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1121">1121</a>                 if (<a href="ident?i=debug">debug</a> &gt; 1)
<a name="L1122" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1122">1122</a>                         <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: request: id=0x%lx error_status=%u "</i>
<a name="L1123" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1123">1123</a>                         <i>"error_index=%u\n"</i>, <a href="ident?i=req">req</a>.<a href="ident?i=id">id</a>, <a href="ident?i=req">req</a>.error_status,
<a name="L1124" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1124">1124</a>                         <a href="ident?i=req">req</a>.error_index);
<a name="L1125" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1125">1125</a>         }
<a name="L1126" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1126">1126</a> 
<a name="L1127" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1127">1127</a>         <b><i>/*</i></b>
<a name="L1128" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1128">1128</a> <b><i>         * Loop through objects, look for IP addresses to mangle.</i></b>
<a name="L1129" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1129">1129</a> <b><i>         */</i></b>
<a name="L1130" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1130">1130</a>         if (!<a href="ident?i=asn1_header_decode">asn1_header_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;eoc, &amp;cls, &amp;con, &amp;<a href="ident?i=tag">tag</a>))
<a name="L1131" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1131">1131</a>                 return 0;
<a name="L1132" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1132">1132</a> 
<a name="L1133" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1133">1133</a>         if (cls != <a href="ident?i=ASN1_UNI">ASN1_UNI</a> || con != <a href="ident?i=ASN1_CON">ASN1_CON</a> || <a href="ident?i=tag">tag</a> != <a href="ident?i=ASN1_SEQ">ASN1_SEQ</a>)
<a name="L1134" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1134">1134</a>                 return 0;
<a name="L1135" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1135">1135</a> 
<a name="L1136" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1136">1136</a>         while (!<a href="ident?i=asn1_eoc_decode">asn1_eoc_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, eoc)) {
<a name="L1137" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1137">1137</a>                 unsigned int <a href="ident?i=i">i</a>;
<a name="L1138" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1138">1138</a> 
<a name="L1139" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1139">1139</a>                 if (!<a href="ident?i=snmp_object_decode">snmp_object_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, &amp;<a href="ident?i=obj">obj</a>)) {
<a name="L1140" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1140">1140</a>                         if (<a href="ident?i=obj">obj</a>) {
<a name="L1141" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1141">1141</a>                                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=obj">obj</a>-&gt;<a href="ident?i=id">id</a>);
<a name="L1142" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1142">1142</a>                                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=obj">obj</a>);
<a name="L1143" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1143">1143</a>                         }
<a name="L1144" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1144">1144</a>                         return 0;
<a name="L1145" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1145">1145</a>                 }
<a name="L1146" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1146">1146</a> 
<a name="L1147" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1147">1147</a>                 if (<a href="ident?i=debug">debug</a> &gt; 1) {
<a name="L1148" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1148">1148</a>                         <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_DEBUG">KERN_DEBUG</a> <i>"bsalg: object: "</i>);
<a name="L1149" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1149">1149</a>                         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=obj">obj</a>-&gt;id_len; <a href="ident?i=i">i</a>++) {
<a name="L1150" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1150">1150</a>                                 if (<a href="ident?i=i">i</a> &gt; 0)
<a name="L1151" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1151">1151</a>                                         <a href="ident?i=printk">printk</a>(<i>"."</i>);
<a name="L1152" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1152">1152</a>                                 <a href="ident?i=printk">printk</a>(<i>"%lu"</i>, <a href="ident?i=obj">obj</a>-&gt;<a href="ident?i=id">id</a>[<a href="ident?i=i">i</a>]);
<a name="L1153" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1153">1153</a>                         }
<a name="L1154" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1154">1154</a>                         <a href="ident?i=printk">printk</a>(<i>": type=%u\n"</i>, <a href="ident?i=obj">obj</a>-&gt;<a href="ident?i=type">type</a>);
<a name="L1155" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1156">1156</a>                 }
<a name="L1157" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1158">1158</a>                 if (<a href="ident?i=obj">obj</a>-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=SNMP_IPADDR">SNMP_IPADDR</a>)
<a name="L1159" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1159">1159</a>                         <a href="ident?i=mangle_address">mangle_address</a>(<a href="ident?i=ctx">ctx</a>.begin, <a href="ident?i=ctx">ctx</a>.<a href="ident?i=pointer">pointer</a> - 4 , <a href="ident?i=map">map</a>, <a href="ident?i=check">check</a>);
<a name="L1160" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1160">1160</a> 
<a name="L1161" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1161">1161</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=obj">obj</a>-&gt;<a href="ident?i=id">id</a>);
<a name="L1162" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1162">1162</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=obj">obj</a>);
<a name="L1163" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1163">1163</a>         }
<a name="L1164" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1164">1164</a> 
<a name="L1165" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1165">1165</a>         if (!<a href="ident?i=asn1_eoc_decode">asn1_eoc_decode</a>(&amp;<a href="ident?i=ctx">ctx</a>, eoc))
<a name="L1166" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1166">1166</a>                 return 0;
<a name="L1167" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1167">1167</a> 
<a name="L1168" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1168">1168</a>         return 1;
<a name="L1169" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1169">1169</a> }
<a name="L1170" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1170">1170</a> 
<a name="L1171" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1171">1171</a> <b><i>/*****************************************************************************</i></b>
<a name="L1172" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1172">1172</a> <b><i> *</i></b>
<a name="L1173" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1173">1173</a> <b><i> * NAT routines.</i></b>
<a name="L1174" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1174">1174</a> <b><i> *</i></b>
<a name="L1175" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1175">1175</a> <b><i> *****************************************************************************/</i></b>
<a name="L1176" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1176">1176</a> 
<a name="L1177" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1177">1177</a> <b><i>/*</i></b>
<a name="L1178" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1178">1178</a> <b><i> * SNMP translation routine.</i></b>
<a name="L1179" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1179">1179</a> <b><i> */</i></b>
<a name="L1180" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1180">1180</a> static int <a href="ident?i=snmp_translate">snmp_translate</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L1181" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1181">1181</a>                           enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L1182" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1182">1182</a>                           struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1183" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1183">1183</a> {
<a name="L1184" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1184">1184</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1185" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1185">1185</a>         struct <a href="ident?i=udphdr">udphdr</a> *udph = (struct <a href="ident?i=udphdr">udphdr</a> *)((<a href="ident?i=__be32">__be32</a> *)iph + iph-&gt;ihl);
<a name="L1186" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1186">1186</a>         <a href="ident?i=u_int16_t">u_int16_t</a> udplen = <a href="ident?i=ntohs">ntohs</a>(udph-&gt;<a href="ident?i=len">len</a>);
<a name="L1187" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1187">1187</a>         <a href="ident?i=u_int16_t">u_int16_t</a> paylen = udplen - sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L1188" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1188">1188</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L1189" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1189">1189</a>         struct <a href="ident?i=oct1_map">oct1_map</a> <a href="ident?i=map">map</a>;
<a name="L1190" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1190">1190</a> 
<a name="L1191" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1191">1191</a>         <b><i>/*</i></b>
<a name="L1192" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1192">1192</a> <b><i>         * Determine mappping for application layer addresses based</i></b>
<a name="L1193" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1193">1193</a> <b><i>         * on NAT manipulations for the packet.</i></b>
<a name="L1194" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1194">1194</a> <b><i>         */</i></b>
<a name="L1195" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1195">1195</a>         if (<a href="ident?i=dir">dir</a> == IP_CT_DIR_ORIGINAL) {
<a name="L1196" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1196">1196</a>                 <b><i>/* SNAT traps */</i></b>
<a name="L1197" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1197">1197</a>                 <a href="ident?i=map">map</a>.from = <a href="ident?i=NOCT1">NOCT1</a>(&amp;ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>);
<a name="L1198" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1198">1198</a>                 <a href="ident?i=map">map</a>.to = <a href="ident?i=NOCT1">NOCT1</a>(&amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>);
<a name="L1199" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1199">1199</a>         } else {
<a name="L1200" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1200">1200</a>                 <b><i>/* DNAT replies */</i></b>
<a name="L1201" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1201">1201</a>                 <a href="ident?i=map">map</a>.from = <a href="ident?i=NOCT1">NOCT1</a>(&amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>);
<a name="L1202" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1202">1202</a>                 <a href="ident?i=map">map</a>.to = <a href="ident?i=NOCT1">NOCT1</a>(&amp;ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>);
<a name="L1203" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1203">1203</a>         }
<a name="L1204" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1204">1204</a> 
<a name="L1205" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1205">1205</a>         if (<a href="ident?i=map">map</a>.from == <a href="ident?i=map">map</a>.to)
<a name="L1206" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1206">1206</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L1207" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1207">1207</a> 
<a name="L1208" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1208">1208</a>         if (!<a href="ident?i=snmp_parse_mangle">snmp_parse_mangle</a>((unsigned char *)udph + sizeof(struct <a href="ident?i=udphdr">udphdr</a>),
<a name="L1209" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1209">1209</a>                                paylen, &amp;<a href="ident?i=map">map</a>, &amp;udph-&gt;<a href="ident?i=check">check</a>)) {
<a name="L1210" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1210">1210</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"bsalg: parser failed\n"</i>);
<a name="L1211" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1211">1211</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L1212" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1212">1212</a>         }
<a name="L1213" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1213">1213</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L1214" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1214">1214</a> }
<a name="L1215" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1215">1215</a> 
<a name="L1216" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1216">1216</a> <b><i>/* We don't actually set up expectations, just adjust internal IP</i></b>
<a name="L1217" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1217">1217</a> <b><i> * addresses if this is being NATted */</i></b>
<a name="L1218" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1218">1218</a> static int <a href="ident?i=help">help</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int protoff,
<a name="L1219" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1219">1219</a>                 struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L1220" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1220">1220</a>                 enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo)
<a name="L1221" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1221">1221</a> {
<a name="L1222" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1222">1222</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L1223" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1223">1223</a>         unsigned int <a href="ident?i=ret">ret</a>;
<a name="L1224" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1224">1224</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1225" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1225">1225</a>         const struct <a href="ident?i=udphdr">udphdr</a> *udph = (struct <a href="ident?i=udphdr">udphdr</a> *)((<a href="ident?i=__be32">__be32</a> *)iph + iph-&gt;ihl);
<a name="L1226" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1226">1226</a> 
<a name="L1227" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1227">1227</a>         <b><i>/* SNMP replies and originating SNMP traps get mangled */</i></b>
<a name="L1228" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1228">1228</a>         if (udph-&gt;source == <a href="ident?i=htons">htons</a>(<a href="ident?i=SNMP_PORT">SNMP_PORT</a>) &amp;&amp; <a href="ident?i=dir">dir</a> != IP_CT_DIR_REPLY)
<a name="L1229" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1229">1229</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L1230" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1230">1230</a>         if (udph-&gt;<a href="ident?i=dest">dest</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=SNMP_TRAP_PORT">SNMP_TRAP_PORT</a>) &amp;&amp; <a href="ident?i=dir">dir</a> != IP_CT_DIR_ORIGINAL)
<a name="L1231" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1231">1231</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L1232" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1232">1232</a> 
<a name="L1233" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1233">1233</a>         <b><i>/* No NAT? */</i></b>
<a name="L1234" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1234">1234</a>         if (!(ct-&gt;<a href="ident?i=status">status</a> &amp; IPS_NAT_MASK))
<a name="L1235" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1235">1235</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L1236" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1236">1236</a> 
<a name="L1237" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1237">1237</a>         <b><i>/*</i></b>
<a name="L1238" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1238">1238</a> <b><i>         * Make sure the packet length is ok.  So far, we were only guaranteed</i></b>
<a name="L1239" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1239">1239</a> <b><i>         * to have a valid length IP header plus 8 bytes, which means we have</i></b>
<a name="L1240" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1240">1240</a> <b><i>         * enough room for a UDP header.  Just verify the UDP length field so we</i></b>
<a name="L1241" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1241">1241</a> <b><i>         * can mess around with the payload.</i></b>
<a name="L1242" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1242">1242</a> <b><i>         */</i></b>
<a name="L1243" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1243">1243</a>         if (<a href="ident?i=ntohs">ntohs</a>(udph-&gt;<a href="ident?i=len">len</a>) != <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - (iph-&gt;ihl &lt;&lt; 2)) {
<a name="L1244" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1244">1244</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"SNMP: dropping malformed packet src=%pI4 dst=%pI4\n"</i>,
<a name="L1245" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1245">1245</a>                                      &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L1246" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1246">1246</a>                  return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L1247" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1247">1247</a>         }
<a name="L1248" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1248">1248</a> 
<a name="L1249" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1249">1249</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>))
<a name="L1250" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1250">1250</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L1251" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1251">1251</a> 
<a name="L1252" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1252">1252</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;snmp_lock);
<a name="L1253" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1253">1253</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=snmp_translate">snmp_translate</a>(ct, ctinfo, <a href="ident?i=skb">skb</a>);
<a name="L1254" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1254">1254</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;snmp_lock);
<a name="L1255" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1255">1255</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1256" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1256">1256</a> }
<a name="L1257" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1257">1257</a> 
<a name="L1258" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1258">1258</a> static const struct <a href="ident?i=nf_conntrack_expect_policy">nf_conntrack_expect_policy</a> <a href="ident?i=snmp_exp_policy">snmp_exp_policy</a> = {
<a name="L1259" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1259">1259</a>         .max_expected   = 0,
<a name="L1260" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1260">1260</a>         .<a href="ident?i=timeout">timeout</a>        = 180,
<a name="L1261" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1261">1261</a> };
<a name="L1262" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1262">1262</a> 
<a name="L1263" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1263">1263</a> static struct <a href="ident?i=nf_conntrack_helper">nf_conntrack_helper</a> snmp_helper <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1264" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1264">1264</a>         .<a href="ident?i=me">me</a>                     = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L1265" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1265">1265</a>         .<a href="ident?i=help">help</a>                   = <a href="ident?i=help">help</a>,
<a name="L1266" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1266">1266</a>         .expect_policy          = &amp;<a href="ident?i=snmp_exp_policy">snmp_exp_policy</a>,
<a name="L1267" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1267">1267</a>         .<a href="ident?i=name">name</a>                   = <i>"snmp"</i>,
<a name="L1268" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1268">1268</a>         .tuple.<a href="ident?i=src">src</a>.l3num        = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L1269" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1269">1269</a>         .tuple.<a href="ident?i=src">src</a>.u.udp.<a href="ident?i=port">port</a>   = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=SNMP_PORT">SNMP_PORT</a>),
<a name="L1270" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1270">1270</a>         .tuple.<a href="ident?i=dst">dst</a>.protonum     = <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>,
<a name="L1271" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1271">1271</a> };
<a name="L1272" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1272">1272</a> 
<a name="L1273" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1273">1273</a> static struct <a href="ident?i=nf_conntrack_helper">nf_conntrack_helper</a> snmp_trap_helper <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1274" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1274">1274</a>         .<a href="ident?i=me">me</a>                     = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L1275" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1275">1275</a>         .<a href="ident?i=help">help</a>                   = <a href="ident?i=help">help</a>,
<a name="L1276" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1276">1276</a>         .expect_policy          = &amp;<a href="ident?i=snmp_exp_policy">snmp_exp_policy</a>,
<a name="L1277" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1277">1277</a>         .<a href="ident?i=name">name</a>                   = <i>"snmp_trap"</i>,
<a name="L1278" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1278">1278</a>         .tuple.<a href="ident?i=src">src</a>.l3num        = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L1279" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1279">1279</a>         .tuple.<a href="ident?i=src">src</a>.u.udp.<a href="ident?i=port">port</a>   = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=SNMP_TRAP_PORT">SNMP_TRAP_PORT</a>),
<a name="L1280" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1280">1280</a>         .tuple.<a href="ident?i=dst">dst</a>.protonum     = <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>,
<a name="L1281" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1281">1281</a> };
<a name="L1282" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1282">1282</a> 
<a name="L1283" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1283">1283</a> <b><i>/*****************************************************************************</i></b>
<a name="L1284" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1284">1284</a> <b><i> *</i></b>
<a name="L1285" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1285">1285</a> <b><i> * Module stuff.</i></b>
<a name="L1286" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1286">1286</a> <b><i> *</i></b>
<a name="L1287" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1287">1287</a> <b><i> *****************************************************************************/</i></b>
<a name="L1288" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1288">1288</a> 
<a name="L1289" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1289">1289</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_nat_snmp_basic_init">nf_nat_snmp_basic_init</a>(void)
<a name="L1290" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1290">1290</a> {
<a name="L1291" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1291">1291</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1292" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1292">1292</a> 
<a name="L1293" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1293">1293</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nf_nat_snmp_hook">nf_nat_snmp_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L1294" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1294">1294</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_snmp_hook">nf_nat_snmp_hook</a>, <a href="ident?i=help">help</a>);
<a name="L1295" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1295">1295</a> 
<a name="L1296" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1296">1296</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_conntrack_helper_register">nf_conntrack_helper_register</a>(&amp;snmp_trap_helper);
<a name="L1297" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1297">1297</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L1298" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1298">1298</a>                 <a href="ident?i=nf_conntrack_helper_unregister">nf_conntrack_helper_unregister</a>(&amp;snmp_helper);
<a name="L1299" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1299">1299</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1300" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1300">1300</a>         }
<a name="L1301" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1301">1301</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1302" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1302">1302</a> }
<a name="L1303" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1303">1303</a> 
<a name="L1304" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1304">1304</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_nat_snmp_basic_fini">nf_nat_snmp_basic_fini</a>(void)
<a name="L1305" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1305">1305</a> {
<a name="L1306" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1306">1306</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_snmp_hook">nf_nat_snmp_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1307" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1307">1307</a>         <a href="ident?i=nf_conntrack_helper_unregister">nf_conntrack_helper_unregister</a>(&amp;snmp_trap_helper);
<a name="L1308" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1308">1308</a> }
<a name="L1309" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1309">1309</a> 
<a name="L1310" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1310">1310</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_nat_snmp_basic_init">nf_nat_snmp_basic_init</a>);
<a name="L1311" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1311">1311</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_nat_snmp_basic_fini">nf_nat_snmp_basic_fini</a>);
<a name="L1312" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1312">1312</a> 
<a name="L1313" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1313">1313</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=debug">debug</a>, int, 0600);
<a name="L1314" href="source/net/ipv4/netfilter/nf_nat_snmp_basic.c#L1314">1314</a> </pre></div><p>
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
