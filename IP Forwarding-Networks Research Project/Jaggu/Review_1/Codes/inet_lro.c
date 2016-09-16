<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inet_lro.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inet_lro.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inet_lro.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inet_lro.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inet_lro.c">inet_lro.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inet_lro.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inet_lro.c#L2">2</a> <b><i> *  linux/net/ipv4/inet_lro.c</i></b>
  <a name="L3" href="source/net/ipv4/inet_lro.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/inet_lro.c#L4">4</a> <b><i> *  Large Receive Offload (ipv4 / tcp)</i></b>
  <a name="L5" href="source/net/ipv4/inet_lro.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/inet_lro.c#L6">6</a> <b><i> *  (C) Copyright IBM Corp. 2007</i></b>
  <a name="L7" href="source/net/ipv4/inet_lro.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/inet_lro.c#L8">8</a> <b><i> *  Authors:</i></b>
  <a name="L9" href="source/net/ipv4/inet_lro.c#L9">9</a> <b><i> *       Jan-Bernd Themann &lt;themann@de.ibm.com&gt;</i></b>
 <a name="L10" href="source/net/ipv4/inet_lro.c#L10">10</a> <b><i> *       Christoph Raisch &lt;raisch@de.ibm.com&gt;</i></b>
 <a name="L11" href="source/net/ipv4/inet_lro.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/inet_lro.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/inet_lro.c#L13">13</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
 <a name="L14" href="source/net/ipv4/inet_lro.c#L14">14</a> <b><i> * it under the terms of the GNU General Public License as published by</i></b>
 <a name="L15" href="source/net/ipv4/inet_lro.c#L15">15</a> <b><i> * the Free Software Foundation; either version 2, or (at your option)</i></b>
 <a name="L16" href="source/net/ipv4/inet_lro.c#L16">16</a> <b><i> * any later version.</i></b>
 <a name="L17" href="source/net/ipv4/inet_lro.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/inet_lro.c#L18">18</a> <b><i> * This program is distributed in the hope that it will be useful,</i></b>
 <a name="L19" href="source/net/ipv4/inet_lro.c#L19">19</a> <b><i> * but WITHOUT ANY WARRANTY; without even the implied warranty of</i></b>
 <a name="L20" href="source/net/ipv4/inet_lro.c#L20">20</a> <b><i> * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</i></b>
 <a name="L21" href="source/net/ipv4/inet_lro.c#L21">21</a> <b><i> * GNU General Public License for more details.</i></b>
 <a name="L22" href="source/net/ipv4/inet_lro.c#L22">22</a> <b><i> *</i></b>
 <a name="L23" href="source/net/ipv4/inet_lro.c#L23">23</a> <b><i> * You should have received a copy of the GNU General Public License</i></b>
 <a name="L24" href="source/net/ipv4/inet_lro.c#L24">24</a> <b><i> * along with this program; if not, write to the Free Software</i></b>
 <a name="L25" href="source/net/ipv4/inet_lro.c#L25">25</a> <b><i> * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.</i></b>
 <a name="L26" href="source/net/ipv4/inet_lro.c#L26">26</a> <b><i> */</i></b>
 <a name="L27" href="source/net/ipv4/inet_lro.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/inet_lro.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/inet_lro.c#L29">29</a> #include &lt;linux/module.h&gt;
 <a name="L30" href="source/net/ipv4/inet_lro.c#L30">30</a> #include &lt;linux/if_vlan.h&gt;
 <a name="L31" href="source/net/ipv4/inet_lro.c#L31">31</a> #include &lt;linux/inet_lro.h&gt;
 <a name="L32" href="source/net/ipv4/inet_lro.c#L32">32</a> #include &lt;net/checksum.h&gt;
 <a name="L33" href="source/net/ipv4/inet_lro.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/inet_lro.c#L34">34</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L35" href="source/net/ipv4/inet_lro.c#L35">35</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Jan-Bernd Themann &lt;themann@de.ibm.com&gt;"</i>);
 <a name="L36" href="source/net/ipv4/inet_lro.c#L36">36</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Large Receive Offload (ipv4 / tcp)"</i>);
 <a name="L37" href="source/net/ipv4/inet_lro.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/inet_lro.c#L38">38</a> #define <a href="ident?i=TCP_HDR_LEN">TCP_HDR_LEN</a>(tcph) (tcph-&gt;doff &lt;&lt; 2)
 <a name="L39" href="source/net/ipv4/inet_lro.c#L39">39</a> #define <a href="ident?i=IP_HDR_LEN">IP_HDR_LEN</a>(iph) (iph-&gt;ihl &lt;&lt; 2)
 <a name="L40" href="source/net/ipv4/inet_lro.c#L40">40</a> #define <a href="ident?i=TCP_PAYLOAD_LENGTH">TCP_PAYLOAD_LENGTH</a>(iph, tcph) \
 <a name="L41" href="source/net/ipv4/inet_lro.c#L41">41</a>         (<a href="ident?i=ntohs">ntohs</a>(iph-&gt;tot_len) - <a href="ident?i=IP_HDR_LEN">IP_HDR_LEN</a>(iph) - <a href="ident?i=TCP_HDR_LEN">TCP_HDR_LEN</a>(tcph))
 <a name="L42" href="source/net/ipv4/inet_lro.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/inet_lro.c#L43">43</a> #define <a href="ident?i=IPH_LEN_WO_OPTIONS">IPH_LEN_WO_OPTIONS</a> 5
 <a name="L44" href="source/net/ipv4/inet_lro.c#L44">44</a> #define <a href="ident?i=TCPH_LEN_WO_OPTIONS">TCPH_LEN_WO_OPTIONS</a> 5
 <a name="L45" href="source/net/ipv4/inet_lro.c#L45">45</a> #define <a href="ident?i=TCPH_LEN_W_TIMESTAMP">TCPH_LEN_W_TIMESTAMP</a> 8
 <a name="L46" href="source/net/ipv4/inet_lro.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/inet_lro.c#L47">47</a> #define <a href="ident?i=LRO_MAX_PG_HLEN">LRO_MAX_PG_HLEN</a> 64
 <a name="L48" href="source/net/ipv4/inet_lro.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/inet_lro.c#L49">49</a> #define <a href="ident?i=LRO_INC_STATS">LRO_INC_STATS</a>(lro_mgr, <a href="ident?i=attr">attr</a>) { lro_mgr-&gt;<a href="ident?i=stats">stats</a>.<a href="ident?i=attr">attr</a>++; }
 <a name="L50" href="source/net/ipv4/inet_lro.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/inet_lro.c#L51">51</a> <b><i>/*</i></b>
 <a name="L52" href="source/net/ipv4/inet_lro.c#L52">52</a> <b><i> * Basic tcp checks whether packet is suitable for LRO</i></b>
 <a name="L53" href="source/net/ipv4/inet_lro.c#L53">53</a> <b><i> */</i></b>
 <a name="L54" href="source/net/ipv4/inet_lro.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/inet_lro.c#L55">55</a> static int <a href="ident?i=lro_tcp_ip_check">lro_tcp_ip_check</a>(const struct <a href="ident?i=iphdr">iphdr</a> *iph, const struct <a href="ident?i=tcphdr">tcphdr</a> *tcph,
 <a name="L56" href="source/net/ipv4/inet_lro.c#L56">56</a>                             int <a href="ident?i=len">len</a>, const struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc)
 <a name="L57" href="source/net/ipv4/inet_lro.c#L57">57</a> {
 <a name="L58" href="source/net/ipv4/inet_lro.c#L58">58</a>         <b><i>/* check ip header: don't aggregate padded frames */</i></b>
 <a name="L59" href="source/net/ipv4/inet_lro.c#L59">59</a>         if (<a href="ident?i=ntohs">ntohs</a>(iph-&gt;tot_len) != <a href="ident?i=len">len</a>)
 <a name="L60" href="source/net/ipv4/inet_lro.c#L60">60</a>                 return -1;
 <a name="L61" href="source/net/ipv4/inet_lro.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/inet_lro.c#L62">62</a>         if (<a href="ident?i=TCP_PAYLOAD_LENGTH">TCP_PAYLOAD_LENGTH</a>(iph, tcph) == 0)
 <a name="L63" href="source/net/ipv4/inet_lro.c#L63">63</a>                 return -1;
 <a name="L64" href="source/net/ipv4/inet_lro.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/inet_lro.c#L65">65</a>         if (iph-&gt;ihl != <a href="ident?i=IPH_LEN_WO_OPTIONS">IPH_LEN_WO_OPTIONS</a>)
 <a name="L66" href="source/net/ipv4/inet_lro.c#L66">66</a>                 return -1;
 <a name="L67" href="source/net/ipv4/inet_lro.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/inet_lro.c#L68">68</a>         if (tcph-&gt;cwr || tcph-&gt;ece || tcph-&gt;urg || !tcph-&gt;ack ||
 <a name="L69" href="source/net/ipv4/inet_lro.c#L69">69</a>             tcph-&gt;rst || tcph-&gt;syn || tcph-&gt;fin)
 <a name="L70" href="source/net/ipv4/inet_lro.c#L70">70</a>                 return -1;
 <a name="L71" href="source/net/ipv4/inet_lro.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/inet_lro.c#L72">72</a>         if (<a href="ident?i=INET_ECN_is_ce">INET_ECN_is_ce</a>(<a href="ident?i=ipv4_get_dsfield">ipv4_get_dsfield</a>(iph)))
 <a name="L73" href="source/net/ipv4/inet_lro.c#L73">73</a>                 return -1;
 <a name="L74" href="source/net/ipv4/inet_lro.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/inet_lro.c#L75">75</a>         if (tcph-&gt;doff != <a href="ident?i=TCPH_LEN_WO_OPTIONS">TCPH_LEN_WO_OPTIONS</a> &amp;&amp;
 <a name="L76" href="source/net/ipv4/inet_lro.c#L76">76</a>             tcph-&gt;doff != <a href="ident?i=TCPH_LEN_W_TIMESTAMP">TCPH_LEN_W_TIMESTAMP</a>)
 <a name="L77" href="source/net/ipv4/inet_lro.c#L77">77</a>                 return -1;
 <a name="L78" href="source/net/ipv4/inet_lro.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/inet_lro.c#L79">79</a>         <b><i>/* check tcp options (only timestamp allowed) */</i></b>
 <a name="L80" href="source/net/ipv4/inet_lro.c#L80">80</a>         if (tcph-&gt;doff == <a href="ident?i=TCPH_LEN_W_TIMESTAMP">TCPH_LEN_W_TIMESTAMP</a>) {
 <a name="L81" href="source/net/ipv4/inet_lro.c#L81">81</a>                 <a href="ident?i=__be32">__be32</a> *topt = (<a href="ident?i=__be32">__be32</a> *)(tcph + 1);
 <a name="L82" href="source/net/ipv4/inet_lro.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/inet_lro.c#L83">83</a>                 if (*topt != <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) | (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16)
 <a name="L84" href="source/net/ipv4/inet_lro.c#L84">84</a>                                    | (<a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a> &lt;&lt; 8)
 <a name="L85" href="source/net/ipv4/inet_lro.c#L85">85</a>                                    | <a href="ident?i=TCPOLEN_TIMESTAMP">TCPOLEN_TIMESTAMP</a>))
 <a name="L86" href="source/net/ipv4/inet_lro.c#L86">86</a>                         return -1;
 <a name="L87" href="source/net/ipv4/inet_lro.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/inet_lro.c#L88">88</a>                 <b><i>/* timestamp should be in right order */</i></b>
 <a name="L89" href="source/net/ipv4/inet_lro.c#L89">89</a>                 topt++;
 <a name="L90" href="source/net/ipv4/inet_lro.c#L90">90</a>                 if (lro_desc &amp;&amp; <a href="ident?i=after">after</a>(<a href="ident?i=ntohl">ntohl</a>(lro_desc-&gt;tcp_rcv_tsval),
 <a name="L91" href="source/net/ipv4/inet_lro.c#L91">91</a>                                       <a href="ident?i=ntohl">ntohl</a>(*topt)))
 <a name="L92" href="source/net/ipv4/inet_lro.c#L92">92</a>                         return -1;
 <a name="L93" href="source/net/ipv4/inet_lro.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/inet_lro.c#L94">94</a>                 <b><i>/* timestamp reply should not be zero */</i></b>
 <a name="L95" href="source/net/ipv4/inet_lro.c#L95">95</a>                 topt++;
 <a name="L96" href="source/net/ipv4/inet_lro.c#L96">96</a>                 if (*topt == 0)
 <a name="L97" href="source/net/ipv4/inet_lro.c#L97">97</a>                         return -1;
 <a name="L98" href="source/net/ipv4/inet_lro.c#L98">98</a>         }
 <a name="L99" href="source/net/ipv4/inet_lro.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/inet_lro.c#L100">100</a>         return 0;
<a name="L101" href="source/net/ipv4/inet_lro.c#L101">101</a> }
<a name="L102" href="source/net/ipv4/inet_lro.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/inet_lro.c#L103">103</a> static void <a href="ident?i=lro_update_tcp_ip_header">lro_update_tcp_ip_header</a>(struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc)
<a name="L104" href="source/net/ipv4/inet_lro.c#L104">104</a> {
<a name="L105" href="source/net/ipv4/inet_lro.c#L105">105</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = lro_desc-&gt;iph;
<a name="L106" href="source/net/ipv4/inet_lro.c#L106">106</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *tcph = lro_desc-&gt;tcph;
<a name="L107" href="source/net/ipv4/inet_lro.c#L107">107</a>         <a href="ident?i=__be32">__be32</a> *<a href="ident?i=p">p</a>;
<a name="L108" href="source/net/ipv4/inet_lro.c#L108">108</a>         <a href="ident?i=__wsum">__wsum</a> tcp_hdr_csum;
<a name="L109" href="source/net/ipv4/inet_lro.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/inet_lro.c#L110">110</a>         tcph-&gt;ack_seq = lro_desc-&gt;<a href="ident?i=tcp_ack">tcp_ack</a>;
<a name="L111" href="source/net/ipv4/inet_lro.c#L111">111</a>         tcph-&gt;<a href="ident?i=window">window</a> = lro_desc-&gt;tcp_window;
<a name="L112" href="source/net/ipv4/inet_lro.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/inet_lro.c#L113">113</a>         if (lro_desc-&gt;tcp_saw_tstamp) {
<a name="L114" href="source/net/ipv4/inet_lro.c#L114">114</a>                 <a href="ident?i=p">p</a> = (<a href="ident?i=__be32">__be32</a> *)(tcph + 1);
<a name="L115" href="source/net/ipv4/inet_lro.c#L115">115</a>                 *(<a href="ident?i=p">p</a>+2) = lro_desc-&gt;tcp_rcv_tsecr;
<a name="L116" href="source/net/ipv4/inet_lro.c#L116">116</a>         }
<a name="L117" href="source/net/ipv4/inet_lro.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/inet_lro.c#L118">118</a>         <a href="ident?i=csum_replace2">csum_replace2</a>(&amp;iph-&gt;<a href="ident?i=check">check</a>, iph-&gt;tot_len, <a href="ident?i=htons">htons</a>(lro_desc-&gt;ip_tot_len));
<a name="L119" href="source/net/ipv4/inet_lro.c#L119">119</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(lro_desc-&gt;ip_tot_len);
<a name="L120" href="source/net/ipv4/inet_lro.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/inet_lro.c#L121">121</a>         tcph-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L122" href="source/net/ipv4/inet_lro.c#L122">122</a>         tcp_hdr_csum = <a href="ident?i=csum_partial">csum_partial</a>(tcph, <a href="ident?i=TCP_HDR_LEN">TCP_HDR_LEN</a>(tcph), 0);
<a name="L123" href="source/net/ipv4/inet_lro.c#L123">123</a>         lro_desc-&gt;data_csum = <a href="ident?i=csum_add">csum_add</a>(lro_desc-&gt;data_csum, tcp_hdr_csum);
<a name="L124" href="source/net/ipv4/inet_lro.c#L124">124</a>         tcph-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=csum_tcpudp_magic">csum_tcpudp_magic</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L125" href="source/net/ipv4/inet_lro.c#L125">125</a>                                         lro_desc-&gt;ip_tot_len -
<a name="L126" href="source/net/ipv4/inet_lro.c#L126">126</a>                                         <a href="ident?i=IP_HDR_LEN">IP_HDR_LEN</a>(iph), <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
<a name="L127" href="source/net/ipv4/inet_lro.c#L127">127</a>                                         lro_desc-&gt;data_csum);
<a name="L128" href="source/net/ipv4/inet_lro.c#L128">128</a> }
<a name="L129" href="source/net/ipv4/inet_lro.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/inet_lro.c#L130">130</a> static <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=lro_tcp_data_csum">lro_tcp_data_csum</a>(struct <a href="ident?i=iphdr">iphdr</a> *iph, struct <a href="ident?i=tcphdr">tcphdr</a> *tcph, int <a href="ident?i=len">len</a>)
<a name="L131" href="source/net/ipv4/inet_lro.c#L131">131</a> {
<a name="L132" href="source/net/ipv4/inet_lro.c#L132">132</a>         <a href="ident?i=__wsum">__wsum</a> tcp_csum;
<a name="L133" href="source/net/ipv4/inet_lro.c#L133">133</a>         <a href="ident?i=__wsum">__wsum</a> tcp_hdr_csum;
<a name="L134" href="source/net/ipv4/inet_lro.c#L134">134</a>         <a href="ident?i=__wsum">__wsum</a> tcp_ps_hdr_csum;
<a name="L135" href="source/net/ipv4/inet_lro.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/inet_lro.c#L136">136</a>         tcp_csum = ~csum_unfold(tcph-&gt;<a href="ident?i=check">check</a>);
<a name="L137" href="source/net/ipv4/inet_lro.c#L137">137</a>         tcp_hdr_csum = <a href="ident?i=csum_partial">csum_partial</a>(tcph, <a href="ident?i=TCP_HDR_LEN">TCP_HDR_LEN</a>(tcph), tcp_csum);
<a name="L138" href="source/net/ipv4/inet_lro.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/inet_lro.c#L139">139</a>         tcp_ps_hdr_csum = <a href="ident?i=csum_tcpudp_nofold">csum_tcpudp_nofold</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L140" href="source/net/ipv4/inet_lro.c#L140">140</a>                                              <a href="ident?i=len">len</a> + <a href="ident?i=TCP_HDR_LEN">TCP_HDR_LEN</a>(tcph),
<a name="L141" href="source/net/ipv4/inet_lro.c#L141">141</a>                                              <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>, 0);
<a name="L142" href="source/net/ipv4/inet_lro.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/inet_lro.c#L143">143</a>         return <a href="ident?i=csum_sub">csum_sub</a>(<a href="ident?i=csum_sub">csum_sub</a>(tcp_csum, tcp_hdr_csum),
<a name="L144" href="source/net/ipv4/inet_lro.c#L144">144</a>                         tcp_ps_hdr_csum);
<a name="L145" href="source/net/ipv4/inet_lro.c#L145">145</a> }
<a name="L146" href="source/net/ipv4/inet_lro.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/inet_lro.c#L147">147</a> static void <a href="ident?i=lro_init_desc">lro_init_desc</a>(struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L148" href="source/net/ipv4/inet_lro.c#L148">148</a>                           struct <a href="ident?i=iphdr">iphdr</a> *iph, struct <a href="ident?i=tcphdr">tcphdr</a> *tcph)
<a name="L149" href="source/net/ipv4/inet_lro.c#L149">149</a> {
<a name="L150" href="source/net/ipv4/inet_lro.c#L150">150</a>         int nr_frags;
<a name="L151" href="source/net/ipv4/inet_lro.c#L151">151</a>         <a href="ident?i=__be32">__be32</a> *<a href="ident?i=ptr">ptr</a>;
<a name="L152" href="source/net/ipv4/inet_lro.c#L152">152</a>         <a href="ident?i=u32">u32</a> tcp_data_len = <a href="ident?i=TCP_PAYLOAD_LENGTH">TCP_PAYLOAD_LENGTH</a>(iph, tcph);
<a name="L153" href="source/net/ipv4/inet_lro.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/inet_lro.c#L154">154</a>         nr_frags = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags;
<a name="L155" href="source/net/ipv4/inet_lro.c#L155">155</a>         lro_desc-&gt;<a href="ident?i=parent">parent</a> = <a href="ident?i=skb">skb</a>;
<a name="L156" href="source/net/ipv4/inet_lro.c#L156">156</a>         lro_desc-&gt;next_frag = &amp;(<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frags[nr_frags]);
<a name="L157" href="source/net/ipv4/inet_lro.c#L157">157</a>         lro_desc-&gt;iph = iph;
<a name="L158" href="source/net/ipv4/inet_lro.c#L158">158</a>         lro_desc-&gt;tcph = tcph;
<a name="L159" href="source/net/ipv4/inet_lro.c#L159">159</a>         lro_desc-&gt;tcp_next_seq = <a href="ident?i=ntohl">ntohl</a>(tcph-&gt;<a href="ident?i=seq">seq</a>) + tcp_data_len;
<a name="L160" href="source/net/ipv4/inet_lro.c#L160">160</a>         lro_desc-&gt;<a href="ident?i=tcp_ack">tcp_ack</a> = tcph-&gt;ack_seq;
<a name="L161" href="source/net/ipv4/inet_lro.c#L161">161</a>         lro_desc-&gt;tcp_window = tcph-&gt;<a href="ident?i=window">window</a>;
<a name="L162" href="source/net/ipv4/inet_lro.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/inet_lro.c#L163">163</a>         lro_desc-&gt;pkt_aggr_cnt = 1;
<a name="L164" href="source/net/ipv4/inet_lro.c#L164">164</a>         lro_desc-&gt;ip_tot_len = <a href="ident?i=ntohs">ntohs</a>(iph-&gt;tot_len);
<a name="L165" href="source/net/ipv4/inet_lro.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/inet_lro.c#L166">166</a>         if (tcph-&gt;doff == 8) {
<a name="L167" href="source/net/ipv4/inet_lro.c#L167">167</a>                 <a href="ident?i=ptr">ptr</a> = (<a href="ident?i=__be32">__be32</a> *)(tcph+1);
<a name="L168" href="source/net/ipv4/inet_lro.c#L168">168</a>                 lro_desc-&gt;tcp_saw_tstamp = 1;
<a name="L169" href="source/net/ipv4/inet_lro.c#L169">169</a>                 lro_desc-&gt;tcp_rcv_tsval = *(<a href="ident?i=ptr">ptr</a>+1);
<a name="L170" href="source/net/ipv4/inet_lro.c#L170">170</a>                 lro_desc-&gt;tcp_rcv_tsecr = *(<a href="ident?i=ptr">ptr</a>+2);
<a name="L171" href="source/net/ipv4/inet_lro.c#L171">171</a>         }
<a name="L172" href="source/net/ipv4/inet_lro.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/inet_lro.c#L173">173</a>         lro_desc-&gt;mss = tcp_data_len;
<a name="L174" href="source/net/ipv4/inet_lro.c#L174">174</a>         lro_desc-&gt;<a href="ident?i=active">active</a> = 1;
<a name="L175" href="source/net/ipv4/inet_lro.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/inet_lro.c#L176">176</a>         lro_desc-&gt;data_csum = <a href="ident?i=lro_tcp_data_csum">lro_tcp_data_csum</a>(iph, tcph,
<a name="L177" href="source/net/ipv4/inet_lro.c#L177">177</a>                                                 tcp_data_len);
<a name="L178" href="source/net/ipv4/inet_lro.c#L178">178</a> }
<a name="L179" href="source/net/ipv4/inet_lro.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/inet_lro.c#L180">180</a> static inline void <a href="ident?i=lro_clear_desc">lro_clear_desc</a>(struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc)
<a name="L181" href="source/net/ipv4/inet_lro.c#L181">181</a> {
<a name="L182" href="source/net/ipv4/inet_lro.c#L182">182</a>         <a href="ident?i=memset">memset</a>(lro_desc, 0, sizeof(struct <a href="ident?i=net_lro_desc">net_lro_desc</a>));
<a name="L183" href="source/net/ipv4/inet_lro.c#L183">183</a> }
<a name="L184" href="source/net/ipv4/inet_lro.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/inet_lro.c#L185">185</a> static void <a href="ident?i=lro_add_common">lro_add_common</a>(struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc, struct <a href="ident?i=iphdr">iphdr</a> *iph,
<a name="L186" href="source/net/ipv4/inet_lro.c#L186">186</a>                            struct <a href="ident?i=tcphdr">tcphdr</a> *tcph, int tcp_data_len)
<a name="L187" href="source/net/ipv4/inet_lro.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/inet_lro.c#L188">188</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=parent">parent</a> = lro_desc-&gt;<a href="ident?i=parent">parent</a>;
<a name="L189" href="source/net/ipv4/inet_lro.c#L189">189</a>         <a href="ident?i=__be32">__be32</a> *topt;
<a name="L190" href="source/net/ipv4/inet_lro.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/inet_lro.c#L191">191</a>         lro_desc-&gt;pkt_aggr_cnt++;
<a name="L192" href="source/net/ipv4/inet_lro.c#L192">192</a>         lro_desc-&gt;ip_tot_len += tcp_data_len;
<a name="L193" href="source/net/ipv4/inet_lro.c#L193">193</a>         lro_desc-&gt;tcp_next_seq += tcp_data_len;
<a name="L194" href="source/net/ipv4/inet_lro.c#L194">194</a>         lro_desc-&gt;tcp_window = tcph-&gt;<a href="ident?i=window">window</a>;
<a name="L195" href="source/net/ipv4/inet_lro.c#L195">195</a>         lro_desc-&gt;<a href="ident?i=tcp_ack">tcp_ack</a> = tcph-&gt;ack_seq;
<a name="L196" href="source/net/ipv4/inet_lro.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/inet_lro.c#L197">197</a>         <b><i>/* don't update tcp_rcv_tsval, would not work with PAWS */</i></b>
<a name="L198" href="source/net/ipv4/inet_lro.c#L198">198</a>         if (lro_desc-&gt;tcp_saw_tstamp) {
<a name="L199" href="source/net/ipv4/inet_lro.c#L199">199</a>                 topt = (<a href="ident?i=__be32">__be32</a> *) (tcph + 1);
<a name="L200" href="source/net/ipv4/inet_lro.c#L200">200</a>                 lro_desc-&gt;tcp_rcv_tsecr = *(topt + 2);
<a name="L201" href="source/net/ipv4/inet_lro.c#L201">201</a>         }
<a name="L202" href="source/net/ipv4/inet_lro.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/inet_lro.c#L203">203</a>         lro_desc-&gt;data_csum = <a href="ident?i=csum_block_add">csum_block_add</a>(lro_desc-&gt;data_csum,
<a name="L204" href="source/net/ipv4/inet_lro.c#L204">204</a>                                              <a href="ident?i=lro_tcp_data_csum">lro_tcp_data_csum</a>(iph, tcph,
<a name="L205" href="source/net/ipv4/inet_lro.c#L205">205</a>                                                                tcp_data_len),
<a name="L206" href="source/net/ipv4/inet_lro.c#L206">206</a>                                              <a href="ident?i=parent">parent</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L207" href="source/net/ipv4/inet_lro.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/inet_lro.c#L208">208</a>         <a href="ident?i=parent">parent</a>-&gt;<a href="ident?i=len">len</a> += tcp_data_len;
<a name="L209" href="source/net/ipv4/inet_lro.c#L209">209</a>         <a href="ident?i=parent">parent</a>-&gt;<a href="ident?i=data_len">data_len</a> += tcp_data_len;
<a name="L210" href="source/net/ipv4/inet_lro.c#L210">210</a>         if (tcp_data_len &gt; lro_desc-&gt;mss)
<a name="L211" href="source/net/ipv4/inet_lro.c#L211">211</a>                 lro_desc-&gt;mss = tcp_data_len;
<a name="L212" href="source/net/ipv4/inet_lro.c#L212">212</a> }
<a name="L213" href="source/net/ipv4/inet_lro.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/inet_lro.c#L214">214</a> static void <a href="ident?i=lro_add_packet">lro_add_packet</a>(struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L215" href="source/net/ipv4/inet_lro.c#L215">215</a>                            struct <a href="ident?i=iphdr">iphdr</a> *iph, struct <a href="ident?i=tcphdr">tcphdr</a> *tcph)
<a name="L216" href="source/net/ipv4/inet_lro.c#L216">216</a> {
<a name="L217" href="source/net/ipv4/inet_lro.c#L217">217</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=parent">parent</a> = lro_desc-&gt;<a href="ident?i=parent">parent</a>;
<a name="L218" href="source/net/ipv4/inet_lro.c#L218">218</a>         int tcp_data_len = <a href="ident?i=TCP_PAYLOAD_LENGTH">TCP_PAYLOAD_LENGTH</a>(iph, tcph);
<a name="L219" href="source/net/ipv4/inet_lro.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/inet_lro.c#L220">220</a>         <a href="ident?i=lro_add_common">lro_add_common</a>(lro_desc, iph, tcph, tcp_data_len);
<a name="L221" href="source/net/ipv4/inet_lro.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/inet_lro.c#L222">222</a>         <a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - tcp_data_len));
<a name="L223" href="source/net/ipv4/inet_lro.c#L223">223</a>         <a href="ident?i=parent">parent</a>-&gt;truesize += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L224" href="source/net/ipv4/inet_lro.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/inet_lro.c#L225">225</a>         if (lro_desc-&gt;last_skb)
<a name="L226" href="source/net/ipv4/inet_lro.c#L226">226</a>                 lro_desc-&gt;last_skb-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=skb">skb</a>;
<a name="L227" href="source/net/ipv4/inet_lro.c#L227">227</a>         else
<a name="L228" href="source/net/ipv4/inet_lro.c#L228">228</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=parent">parent</a>)-&gt;frag_list = <a href="ident?i=skb">skb</a>;
<a name="L229" href="source/net/ipv4/inet_lro.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/inet_lro.c#L230">230</a>         lro_desc-&gt;last_skb = <a href="ident?i=skb">skb</a>;
<a name="L231" href="source/net/ipv4/inet_lro.c#L231">231</a> }
<a name="L232" href="source/net/ipv4/inet_lro.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/inet_lro.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/inet_lro.c#L234">234</a> static int <a href="ident?i=lro_check_tcp_conn">lro_check_tcp_conn</a>(struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc,
<a name="L235" href="source/net/ipv4/inet_lro.c#L235">235</a>                               struct <a href="ident?i=iphdr">iphdr</a> *iph,
<a name="L236" href="source/net/ipv4/inet_lro.c#L236">236</a>                               struct <a href="ident?i=tcphdr">tcphdr</a> *tcph)
<a name="L237" href="source/net/ipv4/inet_lro.c#L237">237</a> {
<a name="L238" href="source/net/ipv4/inet_lro.c#L238">238</a>         if ((lro_desc-&gt;iph-&gt;<a href="ident?i=saddr">saddr</a> != iph-&gt;<a href="ident?i=saddr">saddr</a>) ||
<a name="L239" href="source/net/ipv4/inet_lro.c#L239">239</a>             (lro_desc-&gt;iph-&gt;<a href="ident?i=daddr">daddr</a> != iph-&gt;<a href="ident?i=daddr">daddr</a>) ||
<a name="L240" href="source/net/ipv4/inet_lro.c#L240">240</a>             (lro_desc-&gt;tcph-&gt;source != tcph-&gt;source) ||
<a name="L241" href="source/net/ipv4/inet_lro.c#L241">241</a>             (lro_desc-&gt;tcph-&gt;<a href="ident?i=dest">dest</a> != tcph-&gt;<a href="ident?i=dest">dest</a>))
<a name="L242" href="source/net/ipv4/inet_lro.c#L242">242</a>                 return -1;
<a name="L243" href="source/net/ipv4/inet_lro.c#L243">243</a>         return 0;
<a name="L244" href="source/net/ipv4/inet_lro.c#L244">244</a> }
<a name="L245" href="source/net/ipv4/inet_lro.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/inet_lro.c#L246">246</a> static struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *<a href="ident?i=lro_get_desc">lro_get_desc</a>(struct <a href="ident?i=net_lro_mgr">net_lro_mgr</a> *lro_mgr,
<a name="L247" href="source/net/ipv4/inet_lro.c#L247">247</a>                                          struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_arr,
<a name="L248" href="source/net/ipv4/inet_lro.c#L248">248</a>                                          struct <a href="ident?i=iphdr">iphdr</a> *iph,
<a name="L249" href="source/net/ipv4/inet_lro.c#L249">249</a>                                          struct <a href="ident?i=tcphdr">tcphdr</a> *tcph)
<a name="L250" href="source/net/ipv4/inet_lro.c#L250">250</a> {
<a name="L251" href="source/net/ipv4/inet_lro.c#L251">251</a>         struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc = <a href="ident?i=NULL">NULL</a>;
<a name="L252" href="source/net/ipv4/inet_lro.c#L252">252</a>         struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L253" href="source/net/ipv4/inet_lro.c#L253">253</a>         int max_desc = lro_mgr-&gt;max_desc;
<a name="L254" href="source/net/ipv4/inet_lro.c#L254">254</a>         int <a href="ident?i=i">i</a>;
<a name="L255" href="source/net/ipv4/inet_lro.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/inet_lro.c#L256">256</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; max_desc; <a href="ident?i=i">i</a>++) {
<a name="L257" href="source/net/ipv4/inet_lro.c#L257">257</a>                 <a href="ident?i=tmp">tmp</a> = &amp;lro_arr[<a href="ident?i=i">i</a>];
<a name="L258" href="source/net/ipv4/inet_lro.c#L258">258</a>                 if (<a href="ident?i=tmp">tmp</a>-&gt;<a href="ident?i=active">active</a>)
<a name="L259" href="source/net/ipv4/inet_lro.c#L259">259</a>                         if (!<a href="ident?i=lro_check_tcp_conn">lro_check_tcp_conn</a>(<a href="ident?i=tmp">tmp</a>, iph, tcph)) {
<a name="L260" href="source/net/ipv4/inet_lro.c#L260">260</a>                                 lro_desc = <a href="ident?i=tmp">tmp</a>;
<a name="L261" href="source/net/ipv4/inet_lro.c#L261">261</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L262" href="source/net/ipv4/inet_lro.c#L262">262</a>                         }
<a name="L263" href="source/net/ipv4/inet_lro.c#L263">263</a>         }
<a name="L264" href="source/net/ipv4/inet_lro.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/inet_lro.c#L265">265</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; max_desc; <a href="ident?i=i">i</a>++) {
<a name="L266" href="source/net/ipv4/inet_lro.c#L266">266</a>                 if (!lro_arr[<a href="ident?i=i">i</a>].<a href="ident?i=active">active</a>) {
<a name="L267" href="source/net/ipv4/inet_lro.c#L267">267</a>                         lro_desc = &amp;lro_arr[<a href="ident?i=i">i</a>];
<a name="L268" href="source/net/ipv4/inet_lro.c#L268">268</a>                         goto <a href="ident?i=out">out</a>;
<a name="L269" href="source/net/ipv4/inet_lro.c#L269">269</a>                 }
<a name="L270" href="source/net/ipv4/inet_lro.c#L270">270</a>         }
<a name="L271" href="source/net/ipv4/inet_lro.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/inet_lro.c#L272">272</a>         <a href="ident?i=LRO_INC_STATS">LRO_INC_STATS</a>(lro_mgr, no_desc);
<a name="L273" href="source/net/ipv4/inet_lro.c#L273">273</a> <a href="ident?i=out">out</a>:
<a name="L274" href="source/net/ipv4/inet_lro.c#L274">274</a>         return lro_desc;
<a name="L275" href="source/net/ipv4/inet_lro.c#L275">275</a> }
<a name="L276" href="source/net/ipv4/inet_lro.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/inet_lro.c#L277">277</a> static void <a href="ident?i=lro_flush">lro_flush</a>(struct <a href="ident?i=net_lro_mgr">net_lro_mgr</a> *lro_mgr,
<a name="L278" href="source/net/ipv4/inet_lro.c#L278">278</a>                       struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc)
<a name="L279" href="source/net/ipv4/inet_lro.c#L279">279</a> {
<a name="L280" href="source/net/ipv4/inet_lro.c#L280">280</a>         if (lro_desc-&gt;pkt_aggr_cnt &gt; 1)
<a name="L281" href="source/net/ipv4/inet_lro.c#L281">281</a>                 <a href="ident?i=lro_update_tcp_ip_header">lro_update_tcp_ip_header</a>(lro_desc);
<a name="L282" href="source/net/ipv4/inet_lro.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/inet_lro.c#L283">283</a>         <a href="ident?i=skb_shinfo">skb_shinfo</a>(lro_desc-&gt;<a href="ident?i=parent">parent</a>)-&gt;gso_size = lro_desc-&gt;mss;
<a name="L284" href="source/net/ipv4/inet_lro.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/inet_lro.c#L285">285</a>         if (lro_mgr-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=LRO_F_NAPI">LRO_F_NAPI</a>)
<a name="L286" href="source/net/ipv4/inet_lro.c#L286">286</a>                 <a href="ident?i=netif_receive_skb">netif_receive_skb</a>(lro_desc-&gt;<a href="ident?i=parent">parent</a>);
<a name="L287" href="source/net/ipv4/inet_lro.c#L287">287</a>         else
<a name="L288" href="source/net/ipv4/inet_lro.c#L288">288</a>                 <a href="ident?i=netif_rx">netif_rx</a>(lro_desc-&gt;<a href="ident?i=parent">parent</a>);
<a name="L289" href="source/net/ipv4/inet_lro.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/inet_lro.c#L290">290</a>         <a href="ident?i=LRO_INC_STATS">LRO_INC_STATS</a>(lro_mgr, flushed);
<a name="L291" href="source/net/ipv4/inet_lro.c#L291">291</a>         <a href="ident?i=lro_clear_desc">lro_clear_desc</a>(lro_desc);
<a name="L292" href="source/net/ipv4/inet_lro.c#L292">292</a> }
<a name="L293" href="source/net/ipv4/inet_lro.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/inet_lro.c#L294">294</a> static int <a href="ident?i=__lro_proc_skb">__lro_proc_skb</a>(struct <a href="ident?i=net_lro_mgr">net_lro_mgr</a> *lro_mgr, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L295" href="source/net/ipv4/inet_lro.c#L295">295</a>                           void *<a href="ident?i=priv">priv</a>)
<a name="L296" href="source/net/ipv4/inet_lro.c#L296">296</a> {
<a name="L297" href="source/net/ipv4/inet_lro.c#L297">297</a>         struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc;
<a name="L298" href="source/net/ipv4/inet_lro.c#L298">298</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L299" href="source/net/ipv4/inet_lro.c#L299">299</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *tcph;
<a name="L300" href="source/net/ipv4/inet_lro.c#L300">300</a>         <a href="ident?i=u64">u64</a> <a href="ident?i=flags">flags</a>;
<a name="L301" href="source/net/ipv4/inet_lro.c#L301">301</a>         int vlan_hdr_len = 0;
<a name="L302" href="source/net/ipv4/inet_lro.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/inet_lro.c#L303">303</a>         if (!lro_mgr-&gt;get_skb_header ||
<a name="L304" href="source/net/ipv4/inet_lro.c#L304">304</a>             lro_mgr-&gt;get_skb_header(<a href="ident?i=skb">skb</a>, (void *)&amp;iph, (void *)&amp;tcph,
<a name="L305" href="source/net/ipv4/inet_lro.c#L305">305</a>                                     &amp;<a href="ident?i=flags">flags</a>, <a href="ident?i=priv">priv</a>))
<a name="L306" href="source/net/ipv4/inet_lro.c#L306">306</a>                 goto <a href="ident?i=out">out</a>;
<a name="L307" href="source/net/ipv4/inet_lro.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/inet_lro.c#L308">308</a>         if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=LRO_IPV4">LRO_IPV4</a>) || !(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=LRO_TCP">LRO_TCP</a>))
<a name="L309" href="source/net/ipv4/inet_lro.c#L309">309</a>                 goto <a href="ident?i=out">out</a>;
<a name="L310" href="source/net/ipv4/inet_lro.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/inet_lro.c#L311">311</a>         lro_desc = <a href="ident?i=lro_get_desc">lro_get_desc</a>(lro_mgr, lro_mgr-&gt;lro_arr, iph, tcph);
<a name="L312" href="source/net/ipv4/inet_lro.c#L312">312</a>         if (!lro_desc)
<a name="L313" href="source/net/ipv4/inet_lro.c#L313">313</a>                 goto <a href="ident?i=out">out</a>;
<a name="L314" href="source/net/ipv4/inet_lro.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/inet_lro.c#L315">315</a>         if ((<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_8021Q">ETH_P_8021Q</a>)) &amp;&amp;
<a name="L316" href="source/net/ipv4/inet_lro.c#L316">316</a>             !(lro_mgr-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=LRO_F_EXTRACT_VLAN_ID">LRO_F_EXTRACT_VLAN_ID</a>))
<a name="L317" href="source/net/ipv4/inet_lro.c#L317">317</a>                 vlan_hdr_len = <a href="ident?i=VLAN_HLEN">VLAN_HLEN</a>;
<a name="L318" href="source/net/ipv4/inet_lro.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/inet_lro.c#L319">319</a>         if (!lro_desc-&gt;<a href="ident?i=active">active</a>) { <b><i>/* start new lro session */</i></b>
<a name="L320" href="source/net/ipv4/inet_lro.c#L320">320</a>                 if (<a href="ident?i=lro_tcp_ip_check">lro_tcp_ip_check</a>(iph, tcph, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - vlan_hdr_len, <a href="ident?i=NULL">NULL</a>))
<a name="L321" href="source/net/ipv4/inet_lro.c#L321">321</a>                         goto <a href="ident?i=out">out</a>;
<a name="L322" href="source/net/ipv4/inet_lro.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/inet_lro.c#L323">323</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = lro_mgr-&gt;ip_summed_aggr;
<a name="L324" href="source/net/ipv4/inet_lro.c#L324">324</a>                 <a href="ident?i=lro_init_desc">lro_init_desc</a>(lro_desc, <a href="ident?i=skb">skb</a>, iph, tcph);
<a name="L325" href="source/net/ipv4/inet_lro.c#L325">325</a>                 <a href="ident?i=LRO_INC_STATS">LRO_INC_STATS</a>(lro_mgr, aggregated);
<a name="L326" href="source/net/ipv4/inet_lro.c#L326">326</a>                 return 0;
<a name="L327" href="source/net/ipv4/inet_lro.c#L327">327</a>         }
<a name="L328" href="source/net/ipv4/inet_lro.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/inet_lro.c#L329">329</a>         if (lro_desc-&gt;tcp_next_seq != <a href="ident?i=ntohl">ntohl</a>(tcph-&gt;<a href="ident?i=seq">seq</a>))
<a name="L330" href="source/net/ipv4/inet_lro.c#L330">330</a>                 goto out2;
<a name="L331" href="source/net/ipv4/inet_lro.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/inet_lro.c#L332">332</a>         if (<a href="ident?i=lro_tcp_ip_check">lro_tcp_ip_check</a>(iph, tcph, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, lro_desc))
<a name="L333" href="source/net/ipv4/inet_lro.c#L333">333</a>                 goto out2;
<a name="L334" href="source/net/ipv4/inet_lro.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/inet_lro.c#L335">335</a>         <a href="ident?i=lro_add_packet">lro_add_packet</a>(lro_desc, <a href="ident?i=skb">skb</a>, iph, tcph);
<a name="L336" href="source/net/ipv4/inet_lro.c#L336">336</a>         <a href="ident?i=LRO_INC_STATS">LRO_INC_STATS</a>(lro_mgr, aggregated);
<a name="L337" href="source/net/ipv4/inet_lro.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/inet_lro.c#L338">338</a>         if ((lro_desc-&gt;pkt_aggr_cnt &gt;= lro_mgr-&gt;max_aggr) ||
<a name="L339" href="source/net/ipv4/inet_lro.c#L339">339</a>             lro_desc-&gt;<a href="ident?i=parent">parent</a>-&gt;<a href="ident?i=len">len</a> &gt; (0xFFFF - lro_mgr-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>))
<a name="L340" href="source/net/ipv4/inet_lro.c#L340">340</a>                 <a href="ident?i=lro_flush">lro_flush</a>(lro_mgr, lro_desc);
<a name="L341" href="source/net/ipv4/inet_lro.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/inet_lro.c#L342">342</a>         return 0;
<a name="L343" href="source/net/ipv4/inet_lro.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/inet_lro.c#L344">344</a> out2: <b><i>/* send aggregated SKBs to stack */</i></b>
<a name="L345" href="source/net/ipv4/inet_lro.c#L345">345</a>         <a href="ident?i=lro_flush">lro_flush</a>(lro_mgr, lro_desc);
<a name="L346" href="source/net/ipv4/inet_lro.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/inet_lro.c#L347">347</a> <a href="ident?i=out">out</a>:
<a name="L348" href="source/net/ipv4/inet_lro.c#L348">348</a>         return 1;
<a name="L349" href="source/net/ipv4/inet_lro.c#L349">349</a> }
<a name="L350" href="source/net/ipv4/inet_lro.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/inet_lro.c#L351">351</a> void <a href="ident?i=lro_receive_skb">lro_receive_skb</a>(struct <a href="ident?i=net_lro_mgr">net_lro_mgr</a> *lro_mgr,
<a name="L352" href="source/net/ipv4/inet_lro.c#L352">352</a>                      struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L353" href="source/net/ipv4/inet_lro.c#L353">353</a>                      void *<a href="ident?i=priv">priv</a>)
<a name="L354" href="source/net/ipv4/inet_lro.c#L354">354</a> {
<a name="L355" href="source/net/ipv4/inet_lro.c#L355">355</a>         if (<a href="ident?i=__lro_proc_skb">__lro_proc_skb</a>(lro_mgr, <a href="ident?i=skb">skb</a>, <a href="ident?i=priv">priv</a>)) {
<a name="L356" href="source/net/ipv4/inet_lro.c#L356">356</a>                 if (lro_mgr-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=LRO_F_NAPI">LRO_F_NAPI</a>)
<a name="L357" href="source/net/ipv4/inet_lro.c#L357">357</a>                         <a href="ident?i=netif_receive_skb">netif_receive_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L358" href="source/net/ipv4/inet_lro.c#L358">358</a>                 else
<a name="L359" href="source/net/ipv4/inet_lro.c#L359">359</a>                         <a href="ident?i=netif_rx">netif_rx</a>(<a href="ident?i=skb">skb</a>);
<a name="L360" href="source/net/ipv4/inet_lro.c#L360">360</a>         }
<a name="L361" href="source/net/ipv4/inet_lro.c#L361">361</a> }
<a name="L362" href="source/net/ipv4/inet_lro.c#L362">362</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=lro_receive_skb">lro_receive_skb</a>);
<a name="L363" href="source/net/ipv4/inet_lro.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/inet_lro.c#L364">364</a> void <a href="ident?i=lro_flush_all">lro_flush_all</a>(struct <a href="ident?i=net_lro_mgr">net_lro_mgr</a> *lro_mgr)
<a name="L365" href="source/net/ipv4/inet_lro.c#L365">365</a> {
<a name="L366" href="source/net/ipv4/inet_lro.c#L366">366</a>         int <a href="ident?i=i">i</a>;
<a name="L367" href="source/net/ipv4/inet_lro.c#L367">367</a>         struct <a href="ident?i=net_lro_desc">net_lro_desc</a> *lro_desc = lro_mgr-&gt;lro_arr;
<a name="L368" href="source/net/ipv4/inet_lro.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/inet_lro.c#L369">369</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; lro_mgr-&gt;max_desc; <a href="ident?i=i">i</a>++) {
<a name="L370" href="source/net/ipv4/inet_lro.c#L370">370</a>                 if (lro_desc[<a href="ident?i=i">i</a>].<a href="ident?i=active">active</a>)
<a name="L371" href="source/net/ipv4/inet_lro.c#L371">371</a>                         <a href="ident?i=lro_flush">lro_flush</a>(lro_mgr, &amp;lro_desc[<a href="ident?i=i">i</a>]);
<a name="L372" href="source/net/ipv4/inet_lro.c#L372">372</a>         }
<a name="L373" href="source/net/ipv4/inet_lro.c#L373">373</a> }
<a name="L374" href="source/net/ipv4/inet_lro.c#L374">374</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=lro_flush_all">lro_flush_all</a>);
<a name="L375" href="source/net/ipv4/inet_lro.c#L375">375</a> </pre></div><p>
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
