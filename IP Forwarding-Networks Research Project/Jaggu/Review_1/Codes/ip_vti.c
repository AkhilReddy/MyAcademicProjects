<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_vti.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_vti.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_vti.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_vti.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_vti.c">ip_vti.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_vti.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_vti.c#L2">2</a> <b><i> *      Linux NET3: IP/IP protocol decoder modified to support</i></b>
  <a name="L3" href="source/net/ipv4/ip_vti.c#L3">3</a> <b><i> *                  virtual tunnel interface</i></b>
  <a name="L4" href="source/net/ipv4/ip_vti.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/ip_vti.c#L5">5</a> <b><i> *      Authors:</i></b>
  <a name="L6" href="source/net/ipv4/ip_vti.c#L6">6</a> <b><i> *              Saurabh Mohan (saurabh.mohan@vyatta.com) 05/07/2012</i></b>
  <a name="L7" href="source/net/ipv4/ip_vti.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_vti.c#L8">8</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L9" href="source/net/ipv4/ip_vti.c#L9">9</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L10" href="source/net/ipv4/ip_vti.c#L10">10</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L11" href="source/net/ipv4/ip_vti.c#L11">11</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L12" href="source/net/ipv4/ip_vti.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/ip_vti.c#L13">13</a> <b><i> */</i></b>
 <a name="L14" href="source/net/ipv4/ip_vti.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/ip_vti.c#L15">15</a> <b><i>/*</i></b>
 <a name="L16" href="source/net/ipv4/ip_vti.c#L16">16</a> <b><i>   This version of net/ipv4/ip_vti.c is cloned of net/ipv4/ipip.c</i></b>
 <a name="L17" href="source/net/ipv4/ip_vti.c#L17">17</a> <b><i></i></b>
 <a name="L18" href="source/net/ipv4/ip_vti.c#L18">18</a> <b><i>   For comments look at net/ipv4/ip_gre.c --ANK</i></b>
 <a name="L19" href="source/net/ipv4/ip_vti.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/ip_vti.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/ip_vti.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/ip_vti.c#L22">22</a> #include &lt;linux/capability.h&gt;
 <a name="L23" href="source/net/ipv4/ip_vti.c#L23">23</a> #include &lt;linux/module.h&gt;
 <a name="L24" href="source/net/ipv4/ip_vti.c#L24">24</a> #include &lt;linux/types.h&gt;
 <a name="L25" href="source/net/ipv4/ip_vti.c#L25">25</a> #include &lt;linux/kernel.h&gt;
 <a name="L26" href="source/net/ipv4/ip_vti.c#L26">26</a> #include &lt;linux/uaccess.h&gt;
 <a name="L27" href="source/net/ipv4/ip_vti.c#L27">27</a> #include &lt;linux/skbuff.h&gt;
 <a name="L28" href="source/net/ipv4/ip_vti.c#L28">28</a> #include &lt;linux/netdevice.h&gt;
 <a name="L29" href="source/net/ipv4/ip_vti.c#L29">29</a> #include &lt;linux/in.h&gt;
 <a name="L30" href="source/net/ipv4/ip_vti.c#L30">30</a> #include &lt;linux/tcp.h&gt;
 <a name="L31" href="source/net/ipv4/ip_vti.c#L31">31</a> #include &lt;linux/udp.h&gt;
 <a name="L32" href="source/net/ipv4/ip_vti.c#L32">32</a> #include &lt;linux/if_arp.h&gt;
 <a name="L33" href="source/net/ipv4/ip_vti.c#L33">33</a> #include &lt;linux/mroute.h&gt;
 <a name="L34" href="source/net/ipv4/ip_vti.c#L34">34</a> #include &lt;linux/init.h&gt;
 <a name="L35" href="source/net/ipv4/ip_vti.c#L35">35</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L36" href="source/net/ipv4/ip_vti.c#L36">36</a> #include &lt;linux/if_ether.h&gt;
 <a name="L37" href="source/net/ipv4/ip_vti.c#L37">37</a> #include &lt;linux/icmpv6.h&gt;
 <a name="L38" href="source/net/ipv4/ip_vti.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/ip_vti.c#L39">39</a> #include &lt;net/sock.h&gt;
 <a name="L40" href="source/net/ipv4/ip_vti.c#L40">40</a> #include &lt;net/ip.h&gt;
 <a name="L41" href="source/net/ipv4/ip_vti.c#L41">41</a> #include &lt;net/icmp.h&gt;
 <a name="L42" href="source/net/ipv4/ip_vti.c#L42">42</a> #include &lt;net/ip_tunnels.h&gt;
 <a name="L43" href="source/net/ipv4/ip_vti.c#L43">43</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L44" href="source/net/ipv4/ip_vti.c#L44">44</a> #include &lt;net/xfrm.h&gt;
 <a name="L45" href="source/net/ipv4/ip_vti.c#L45">45</a> #include &lt;net/net_namespace.h&gt;
 <a name="L46" href="source/net/ipv4/ip_vti.c#L46">46</a> #include &lt;net/netns/generic.h&gt;
 <a name="L47" href="source/net/ipv4/ip_vti.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/ip_vti.c#L48">48</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> vti_link_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L49" href="source/net/ipv4/ip_vti.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/ip_vti.c#L50">50</a> static int vti_net_id <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L51" href="source/net/ipv4/ip_vti.c#L51">51</a> static int <a href="ident?i=vti_tunnel_init">vti_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>);
 <a name="L52" href="source/net/ipv4/ip_vti.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/ip_vti.c#L53">53</a> static int <a href="ident?i=vti_input">vti_input</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nexthdr, <a href="ident?i=__be32">__be32</a> <a href="ident?i=spi">spi</a>,
 <a name="L54" href="source/net/ipv4/ip_vti.c#L54">54</a>                      int encap_type)
 <a name="L55" href="source/net/ipv4/ip_vti.c#L55">55</a> {
 <a name="L56" href="source/net/ipv4/ip_vti.c#L56">56</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel;
 <a name="L57" href="source/net/ipv4/ip_vti.c#L57">57</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L58" href="source/net/ipv4/ip_vti.c#L58">58</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
 <a name="L59" href="source/net/ipv4/ip_vti.c#L59">59</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, vti_net_id);
 <a name="L60" href="source/net/ipv4/ip_vti.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/ip_vti.c#L61">61</a>         tunnel = <a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(itn, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=TUNNEL_NO_KEY">TUNNEL_NO_KEY</a>,
 <a name="L62" href="source/net/ipv4/ip_vti.c#L62">62</a>                                   iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, 0);
 <a name="L63" href="source/net/ipv4/ip_vti.c#L63">63</a>         if (tunnel) {
 <a name="L64" href="source/net/ipv4/ip_vti.c#L64">64</a>                 if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
 <a name="L65" href="source/net/ipv4/ip_vti.c#L65">65</a>                         goto <a href="ident?i=drop">drop</a>;
 <a name="L66" href="source/net/ipv4/ip_vti.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/ip_vti.c#L67">67</a>                 <a href="ident?i=XFRM_TUNNEL_SKB_CB">XFRM_TUNNEL_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tunnel.ip4 = tunnel;
 <a name="L68" href="source/net/ipv4/ip_vti.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/ip_vti.c#L69">69</a>                 return <a href="ident?i=xfrm_input">xfrm_input</a>(<a href="ident?i=skb">skb</a>, nexthdr, <a href="ident?i=spi">spi</a>, encap_type);
 <a name="L70" href="source/net/ipv4/ip_vti.c#L70">70</a>         }
 <a name="L71" href="source/net/ipv4/ip_vti.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/ip_vti.c#L72">72</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L73" href="source/net/ipv4/ip_vti.c#L73">73</a> <a href="ident?i=drop">drop</a>:
 <a name="L74" href="source/net/ipv4/ip_vti.c#L74">74</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
 <a name="L75" href="source/net/ipv4/ip_vti.c#L75">75</a>         return 0;
 <a name="L76" href="source/net/ipv4/ip_vti.c#L76">76</a> }
 <a name="L77" href="source/net/ipv4/ip_vti.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/ip_vti.c#L78">78</a> static int <a href="ident?i=vti_rcv">vti_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L79" href="source/net/ipv4/ip_vti.c#L79">79</a> {
 <a name="L80" href="source/net/ipv4/ip_vti.c#L80">80</a>         <a href="ident?i=XFRM_SPI_SKB_CB">XFRM_SPI_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L81" href="source/net/ipv4/ip_vti.c#L81">81</a>         <a href="ident?i=XFRM_SPI_SKB_CB">XFRM_SPI_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;daddroff = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=daddr">daddr</a>);
 <a name="L82" href="source/net/ipv4/ip_vti.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/ip_vti.c#L83">83</a>         return <a href="ident?i=vti_input">vti_input</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>, 0, 0);
 <a name="L84" href="source/net/ipv4/ip_vti.c#L84">84</a> }
 <a name="L85" href="source/net/ipv4/ip_vti.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/ip_vti.c#L86">86</a> static int <a href="ident?i=vti_rcv_cb">vti_rcv_cb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=err">err</a>)
 <a name="L87" href="source/net/ipv4/ip_vti.c#L87">87</a> {
 <a name="L88" href="source/net/ipv4/ip_vti.c#L88">88</a>         unsigned short <a href="ident?i=family">family</a>;
 <a name="L89" href="source/net/ipv4/ip_vti.c#L89">89</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
 <a name="L90" href="source/net/ipv4/ip_vti.c#L90">90</a>         struct <a href="ident?i=pcpu_sw_netstats">pcpu_sw_netstats</a> *tstats;
 <a name="L91" href="source/net/ipv4/ip_vti.c#L91">91</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>;
 <a name="L92" href="source/net/ipv4/ip_vti.c#L92">92</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=XFRM_TUNNEL_SKB_CB">XFRM_TUNNEL_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tunnel.ip4;
 <a name="L93" href="source/net/ipv4/ip_vti.c#L93">93</a>         <a href="ident?i=u32">u32</a> orig_mark = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
 <a name="L94" href="source/net/ipv4/ip_vti.c#L94">94</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L95" href="source/net/ipv4/ip_vti.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/ip_vti.c#L96">96</a>         if (!tunnel)
 <a name="L97" href="source/net/ipv4/ip_vti.c#L97">97</a>                 return 1;
 <a name="L98" href="source/net/ipv4/ip_vti.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/ip_vti.c#L99">99</a>         <a href="ident?i=dev">dev</a> = tunnel-&gt;<a href="ident?i=dev">dev</a>;
<a name="L100" href="source/net/ipv4/ip_vti.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/ip_vti.c#L101">101</a>         if (<a href="ident?i=err">err</a>) {
<a name="L102" href="source/net/ipv4/ip_vti.c#L102">102</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_errors++;
<a name="L103" href="source/net/ipv4/ip_vti.c#L103">103</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_dropped++;
<a name="L104" href="source/net/ipv4/ip_vti.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/ip_vti.c#L105">105</a>                 return 0;
<a name="L106" href="source/net/ipv4/ip_vti.c#L106">106</a>         }
<a name="L107" href="source/net/ipv4/ip_vti.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/ip_vti.c#L108">108</a>         <a href="ident?i=x">x</a> = <a href="ident?i=xfrm_input_state">xfrm_input_state</a>(<a href="ident?i=skb">skb</a>);
<a name="L109" href="source/net/ipv4/ip_vti.c#L109">109</a>         <a href="ident?i=family">family</a> = <a href="ident?i=x">x</a>-&gt;inner_mode-&gt;afinfo-&gt;<a href="ident?i=family">family</a>;
<a name="L110" href="source/net/ipv4/ip_vti.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/ip_vti.c#L111">111</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> = <a href="ident?i=be32_to_cpu">be32_to_cpu</a>(tunnel-&gt;<a href="ident?i=parms">parms</a>.i_key);
<a name="L112" href="source/net/ipv4/ip_vti.c#L112">112</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xfrm_policy_check">xfrm_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>, <a href="ident?i=family">family</a>);
<a name="L113" href="source/net/ipv4/ip_vti.c#L113">113</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> = orig_mark;
<a name="L114" href="source/net/ipv4/ip_vti.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/ip_vti.c#L115">115</a>         if (!<a href="ident?i=ret">ret</a>)
<a name="L116" href="source/net/ipv4/ip_vti.c#L116">116</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L117" href="source/net/ipv4/ip_vti.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/ip_vti.c#L118">118</a>         <a href="ident?i=skb_scrub_packet">skb_scrub_packet</a>(<a href="ident?i=skb">skb</a>, !<a href="ident?i=net_eq">net_eq</a>(tunnel-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>)));
<a name="L119" href="source/net/ipv4/ip_vti.c#L119">119</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L120" href="source/net/ipv4/ip_vti.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/ip_vti.c#L121">121</a>         tstats = <a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(<a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L122" href="source/net/ipv4/ip_vti.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/ip_vti.c#L123">123</a>         <a href="ident?i=u64_stats_update_begin">u64_stats_update_begin</a>(&amp;tstats-&gt;syncp);
<a name="L124" href="source/net/ipv4/ip_vti.c#L124">124</a>         tstats-&gt;rx_packets++;
<a name="L125" href="source/net/ipv4/ip_vti.c#L125">125</a>         tstats-&gt;<a href="ident?i=rx_bytes">rx_bytes</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L126" href="source/net/ipv4/ip_vti.c#L126">126</a>         <a href="ident?i=u64_stats_update_end">u64_stats_update_end</a>(&amp;tstats-&gt;syncp);
<a name="L127" href="source/net/ipv4/ip_vti.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/ip_vti.c#L128">128</a>         return 0;
<a name="L129" href="source/net/ipv4/ip_vti.c#L129">129</a> }
<a name="L130" href="source/net/ipv4/ip_vti.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/ip_vti.c#L131">131</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=vti_state_check">vti_state_check</a>(const struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>)
<a name="L132" href="source/net/ipv4/ip_vti.c#L132">132</a> {
<a name="L133" href="source/net/ipv4/ip_vti.c#L133">133</a>         <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=daddr">daddr</a> = (<a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;<a href="ident?i=dst">dst</a>;
<a name="L134" href="source/net/ipv4/ip_vti.c#L134">134</a>         <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=saddr">saddr</a> = (<a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;<a href="ident?i=src">src</a>;
<a name="L135" href="source/net/ipv4/ip_vti.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/ip_vti.c#L136">136</a>         <b><i>/* if there is no transform then this tunnel is not functional.</i></b>
<a name="L137" href="source/net/ipv4/ip_vti.c#L137">137</a> <b><i>         * Or if the xfrm is not mode tunnel.</i></b>
<a name="L138" href="source/net/ipv4/ip_vti.c#L138">138</a> <b><i>         */</i></b>
<a name="L139" href="source/net/ipv4/ip_vti.c#L139">139</a>         if (!<a href="ident?i=x">x</a> || <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> != <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a> ||
<a name="L140" href="source/net/ipv4/ip_vti.c#L140">140</a>             <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=family">family</a> != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L141" href="source/net/ipv4/ip_vti.c#L141">141</a>                 return <a href="ident?i=false">false</a>;
<a name="L142" href="source/net/ipv4/ip_vti.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/ip_vti.c#L143">143</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L144" href="source/net/ipv4/ip_vti.c#L144">144</a>                 return <a href="ident?i=xfrm_addr_equal">xfrm_addr_equal</a>(<a href="ident?i=saddr">saddr</a>, &amp;<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L145" href="source/net/ipv4/ip_vti.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/ip_vti.c#L146">146</a>         if (!<a href="ident?i=xfrm_state_addr_check">xfrm_state_addr_check</a>(<a href="ident?i=x">x</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=AF_INET">AF_INET</a>))
<a name="L147" href="source/net/ipv4/ip_vti.c#L147">147</a>                 return <a href="ident?i=false">false</a>;
<a name="L148" href="source/net/ipv4/ip_vti.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/ip_vti.c#L149">149</a>         return <a href="ident?i=true">true</a>;
<a name="L150" href="source/net/ipv4/ip_vti.c#L150">150</a> }
<a name="L151" href="source/net/ipv4/ip_vti.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/ip_vti.c#L152">152</a> static <a href="ident?i=netdev_tx_t">netdev_tx_t</a> <a href="ident?i=vti_xmit">vti_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L153" href="source/net/ipv4/ip_vti.c#L153">153</a>                             struct <a href="ident?i=flowi">flowi</a> *fl)
<a name="L154" href="source/net/ipv4/ip_vti.c#L154">154</a> {
<a name="L155" href="source/net/ipv4/ip_vti.c#L155">155</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L156" href="source/net/ipv4/ip_vti.c#L156">156</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a> = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>;
<a name="L157" href="source/net/ipv4/ip_vti.c#L157">157</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L158" href="source/net/ipv4/ip_vti.c#L158">158</a>         struct <a href="ident?i=net_device">net_device</a> *tdev;        <b><i>/* Device to other host */</i></b>
<a name="L159" href="source/net/ipv4/ip_vti.c#L159">159</a>         int <a href="ident?i=err">err</a>;
<a name="L160" href="source/net/ipv4/ip_vti.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/ip_vti.c#L161">161</a>         if (!<a href="ident?i=dst">dst</a>) {
<a name="L162" href="source/net/ipv4/ip_vti.c#L162">162</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_carrier_errors++;
<a name="L163" href="source/net/ipv4/ip_vti.c#L163">163</a>                 goto tx_error_icmp;
<a name="L164" href="source/net/ipv4/ip_vti.c#L164">164</a>         }
<a name="L165" href="source/net/ipv4/ip_vti.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/ip_vti.c#L166">166</a>         <a href="ident?i=dst_hold">dst_hold</a>(<a href="ident?i=dst">dst</a>);
<a name="L167" href="source/net/ipv4/ip_vti.c#L167">167</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=xfrm_lookup">xfrm_lookup</a>(tunnel-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=dst">dst</a>, fl, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L168" href="source/net/ipv4/ip_vti.c#L168">168</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=dst">dst</a>)) {
<a name="L169" href="source/net/ipv4/ip_vti.c#L169">169</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_carrier_errors++;
<a name="L170" href="source/net/ipv4/ip_vti.c#L170">170</a>                 goto tx_error_icmp;
<a name="L171" href="source/net/ipv4/ip_vti.c#L171">171</a>         }
<a name="L172" href="source/net/ipv4/ip_vti.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/ip_vti.c#L173">173</a>         if (!<a href="ident?i=vti_state_check">vti_state_check</a>(<a href="ident?i=dst">dst</a>-&gt;xfrm, <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>, <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>)) {
<a name="L174" href="source/net/ipv4/ip_vti.c#L174">174</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_carrier_errors++;
<a name="L175" href="source/net/ipv4/ip_vti.c#L175">175</a>                 <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L176" href="source/net/ipv4/ip_vti.c#L176">176</a>                 goto tx_error_icmp;
<a name="L177" href="source/net/ipv4/ip_vti.c#L177">177</a>         }
<a name="L178" href="source/net/ipv4/ip_vti.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/ip_vti.c#L179">179</a>         tdev = <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L180" href="source/net/ipv4/ip_vti.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/ip_vti.c#L181">181</a>         if (tdev == <a href="ident?i=dev">dev</a>) {
<a name="L182" href="source/net/ipv4/ip_vti.c#L182">182</a>                 <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L183" href="source/net/ipv4/ip_vti.c#L183">183</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.collisions++;
<a name="L184" href="source/net/ipv4/ip_vti.c#L184">184</a>                 goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L185" href="source/net/ipv4/ip_vti.c#L185">185</a>         }
<a name="L186" href="source/net/ipv4/ip_vti.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/ip_vti.c#L187">187</a>         if (tunnel-&gt;err_count &gt; 0) {
<a name="L188" href="source/net/ipv4/ip_vti.c#L188">188</a>                 if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>,
<a name="L189" href="source/net/ipv4/ip_vti.c#L189">189</a>                                 tunnel-&gt;err_time + <a href="ident?i=IPTUNNEL_ERR_TIMEO">IPTUNNEL_ERR_TIMEO</a>)) {
<a name="L190" href="source/net/ipv4/ip_vti.c#L190">190</a>                         tunnel-&gt;err_count--;
<a name="L191" href="source/net/ipv4/ip_vti.c#L191">191</a>                         <a href="ident?i=dst_link_failure">dst_link_failure</a>(<a href="ident?i=skb">skb</a>);
<a name="L192" href="source/net/ipv4/ip_vti.c#L192">192</a>                 } else
<a name="L193" href="source/net/ipv4/ip_vti.c#L193">193</a>                         tunnel-&gt;err_count = 0;
<a name="L194" href="source/net/ipv4/ip_vti.c#L194">194</a>         }
<a name="L195" href="source/net/ipv4/ip_vti.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/ip_vti.c#L196">196</a>         <a href="ident?i=skb_scrub_packet">skb_scrub_packet</a>(<a href="ident?i=skb">skb</a>, !<a href="ident?i=net_eq">net_eq</a>(tunnel-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>)));
<a name="L197" href="source/net/ipv4/ip_vti.c#L197">197</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>);
<a name="L198" href="source/net/ipv4/ip_vti.c#L198">198</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>;
<a name="L199" href="source/net/ipv4/ip_vti.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/ip_vti.c#L200">200</a>         <a href="ident?i=err">err</a> = <a href="ident?i=dst_output">dst_output</a>(<a href="ident?i=skb">skb</a>);
<a name="L201" href="source/net/ipv4/ip_vti.c#L201">201</a>         if (<a href="ident?i=net_xmit_eval">net_xmit_eval</a>(<a href="ident?i=err">err</a>) == 0)
<a name="L202" href="source/net/ipv4/ip_vti.c#L202">202</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L203" href="source/net/ipv4/ip_vti.c#L203">203</a>         <a href="ident?i=iptunnel_xmit_stats">iptunnel_xmit_stats</a>(<a href="ident?i=err">err</a>, &amp;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>, <a href="ident?i=dev">dev</a>-&gt;tstats);
<a name="L204" href="source/net/ipv4/ip_vti.c#L204">204</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L205" href="source/net/ipv4/ip_vti.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/ip_vti.c#L206">206</a> tx_error_icmp:
<a name="L207" href="source/net/ipv4/ip_vti.c#L207">207</a>         <a href="ident?i=dst_link_failure">dst_link_failure</a>(<a href="ident?i=skb">skb</a>);
<a name="L208" href="source/net/ipv4/ip_vti.c#L208">208</a> <a href="ident?i=tx_error">tx_error</a>:
<a name="L209" href="source/net/ipv4/ip_vti.c#L209">209</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_errors++;
<a name="L210" href="source/net/ipv4/ip_vti.c#L210">210</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L211" href="source/net/ipv4/ip_vti.c#L211">211</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L212" href="source/net/ipv4/ip_vti.c#L212">212</a> }
<a name="L213" href="source/net/ipv4/ip_vti.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/ip_vti.c#L214">214</a> <b><i>/* This function assumes it is being called from dev_queue_xmit()</i></b>
<a name="L215" href="source/net/ipv4/ip_vti.c#L215">215</a> <b><i> * and that skb is filled properly by that function.</i></b>
<a name="L216" href="source/net/ipv4/ip_vti.c#L216">216</a> <b><i> */</i></b>
<a name="L217" href="source/net/ipv4/ip_vti.c#L217">217</a> static <a href="ident?i=netdev_tx_t">netdev_tx_t</a> <a href="ident?i=vti_tunnel_xmit">vti_tunnel_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L218" href="source/net/ipv4/ip_vti.c#L218">218</a> {
<a name="L219" href="source/net/ipv4/ip_vti.c#L219">219</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L220" href="source/net/ipv4/ip_vti.c#L220">220</a>         struct <a href="ident?i=flowi">flowi</a> fl;
<a name="L221" href="source/net/ipv4/ip_vti.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/ip_vti.c#L222">222</a>         <a href="ident?i=memset">memset</a>(&amp;fl, 0, sizeof(fl));
<a name="L223" href="source/net/ipv4/ip_vti.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/ip_vti.c#L224">224</a>         switch (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>) {
<a name="L225" href="source/net/ipv4/ip_vti.c#L225">225</a>         case <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>):
<a name="L226" href="source/net/ipv4/ip_vti.c#L226">226</a>                 <a href="ident?i=xfrm_decode_session">xfrm_decode_session</a>(<a href="ident?i=skb">skb</a>, &amp;fl, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L227" href="source/net/ipv4/ip_vti.c#L227">227</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(*<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)));
<a name="L228" href="source/net/ipv4/ip_vti.c#L228">228</a>                 break;
<a name="L229" href="source/net/ipv4/ip_vti.c#L229">229</a>         case <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>):
<a name="L230" href="source/net/ipv4/ip_vti.c#L230">230</a>                 <a href="ident?i=xfrm_decode_session">xfrm_decode_session</a>(<a href="ident?i=skb">skb</a>, &amp;fl, <a href="ident?i=AF_INET6">AF_INET6</a>);
<a name="L231" href="source/net/ipv4/ip_vti.c#L231">231</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=IP6CB">IP6CB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(*<a href="ident?i=IP6CB">IP6CB</a>(<a href="ident?i=skb">skb</a>)));
<a name="L232" href="source/net/ipv4/ip_vti.c#L232">232</a>                 break;
<a name="L233" href="source/net/ipv4/ip_vti.c#L233">233</a>         default:
<a name="L234" href="source/net/ipv4/ip_vti.c#L234">234</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_errors++;
<a name="L235" href="source/net/ipv4/ip_vti.c#L235">235</a>                 <a href="ident?i=dev_kfree_skb">dev_kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L236" href="source/net/ipv4/ip_vti.c#L236">236</a>                 return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L237" href="source/net/ipv4/ip_vti.c#L237">237</a>         }
<a name="L238" href="source/net/ipv4/ip_vti.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/ip_vti.c#L239">239</a>         <b><i>/* override mark with tunnel output key */</i></b>
<a name="L240" href="source/net/ipv4/ip_vti.c#L240">240</a>         fl.<a href="ident?i=flowi_mark">flowi_mark</a> = <a href="ident?i=be32_to_cpu">be32_to_cpu</a>(tunnel-&gt;<a href="ident?i=parms">parms</a>.o_key);
<a name="L241" href="source/net/ipv4/ip_vti.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/ip_vti.c#L242">242</a>         return <a href="ident?i=vti_xmit">vti_xmit</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, &amp;fl);
<a name="L243" href="source/net/ipv4/ip_vti.c#L243">243</a> }
<a name="L244" href="source/net/ipv4/ip_vti.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/ip_vti.c#L245">245</a> static int <a href="ident?i=vti4_err">vti4_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L246" href="source/net/ipv4/ip_vti.c#L246">246</a> {
<a name="L247" href="source/net/ipv4/ip_vti.c#L247">247</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=spi">spi</a>;
<a name="L248" href="source/net/ipv4/ip_vti.c#L248">248</a>         <a href="ident?i=__u32">__u32</a> <a href="ident?i=mark">mark</a>;
<a name="L249" href="source/net/ipv4/ip_vti.c#L249">249</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>;
<a name="L250" href="source/net/ipv4/ip_vti.c#L250">250</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel;
<a name="L251" href="source/net/ipv4/ip_vti.c#L251">251</a>         struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *esph;
<a name="L252" href="source/net/ipv4/ip_vti.c#L252">252</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah ;
<a name="L253" href="source/net/ipv4/ip_vti.c#L253">253</a>         struct <a href="ident?i=ip_comp_hdr">ip_comp_hdr</a> *ipch;
<a name="L254" href="source/net/ipv4/ip_vti.c#L254">254</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L255" href="source/net/ipv4/ip_vti.c#L255">255</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L256" href="source/net/ipv4/ip_vti.c#L256">256</a>         int <a href="ident?i=protocol">protocol</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L257" href="source/net/ipv4/ip_vti.c#L257">257</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, vti_net_id);
<a name="L258" href="source/net/ipv4/ip_vti.c#L258">258</a> 
<a name="L259" href="source/net/ipv4/ip_vti.c#L259">259</a>         tunnel = <a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(itn, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=TUNNEL_NO_KEY">TUNNEL_NO_KEY</a>,
<a name="L260" href="source/net/ipv4/ip_vti.c#L260">260</a>                                   iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, 0);
<a name="L261" href="source/net/ipv4/ip_vti.c#L261">261</a>         if (!tunnel)
<a name="L262" href="source/net/ipv4/ip_vti.c#L262">262</a>                 return -1;
<a name="L263" href="source/net/ipv4/ip_vti.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/ip_vti.c#L264">264</a>         <a href="ident?i=mark">mark</a> = <a href="ident?i=be32_to_cpu">be32_to_cpu</a>(tunnel-&gt;<a href="ident?i=parms">parms</a>.o_key);
<a name="L265" href="source/net/ipv4/ip_vti.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/ip_vti.c#L266">266</a>         switch (<a href="ident?i=protocol">protocol</a>) {
<a name="L267" href="source/net/ipv4/ip_vti.c#L267">267</a>         case <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>:
<a name="L268" href="source/net/ipv4/ip_vti.c#L268">268</a>                 esph = (struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
<a name="L269" href="source/net/ipv4/ip_vti.c#L269">269</a>                 <a href="ident?i=spi">spi</a> = esph-&gt;<a href="ident?i=spi">spi</a>;
<a name="L270" href="source/net/ipv4/ip_vti.c#L270">270</a>                 break;
<a name="L271" href="source/net/ipv4/ip_vti.c#L271">271</a>         case <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>:
<a name="L272" href="source/net/ipv4/ip_vti.c#L272">272</a>                 ah = (struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
<a name="L273" href="source/net/ipv4/ip_vti.c#L273">273</a>                 <a href="ident?i=spi">spi</a> = ah-&gt;<a href="ident?i=spi">spi</a>;
<a name="L274" href="source/net/ipv4/ip_vti.c#L274">274</a>                 break;
<a name="L275" href="source/net/ipv4/ip_vti.c#L275">275</a>         case <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>:
<a name="L276" href="source/net/ipv4/ip_vti.c#L276">276</a>                 ipch = (struct <a href="ident?i=ip_comp_hdr">ip_comp_hdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
<a name="L277" href="source/net/ipv4/ip_vti.c#L277">277</a>                 <a href="ident?i=spi">spi</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohs">ntohs</a>(ipch-&gt;cpi));
<a name="L278" href="source/net/ipv4/ip_vti.c#L278">278</a>                 break;
<a name="L279" href="source/net/ipv4/ip_vti.c#L279">279</a>         default:
<a name="L280" href="source/net/ipv4/ip_vti.c#L280">280</a>                 return 0;
<a name="L281" href="source/net/ipv4/ip_vti.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/ip_vti.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/ip_vti.c#L283">283</a>         switch (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>) {
<a name="L284" href="source/net/ipv4/ip_vti.c#L284">284</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L285" href="source/net/ipv4/ip_vti.c#L285">285</a>                 if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a> != <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
<a name="L286" href="source/net/ipv4/ip_vti.c#L286">286</a>                         return 0;
<a name="L287" href="source/net/ipv4/ip_vti.c#L287">287</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L288" href="source/net/ipv4/ip_vti.c#L288">288</a>                 break;
<a name="L289" href="source/net/ipv4/ip_vti.c#L289">289</a>         default:
<a name="L290" href="source/net/ipv4/ip_vti.c#L290">290</a>                 return 0;
<a name="L291" href="source/net/ipv4/ip_vti.c#L291">291</a>         }
<a name="L292" href="source/net/ipv4/ip_vti.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/ip_vti.c#L293">293</a>         <a href="ident?i=x">x</a> = <a href="ident?i=xfrm_state_lookup">xfrm_state_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=mark">mark</a>, (const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L294" href="source/net/ipv4/ip_vti.c#L294">294</a>                               <a href="ident?i=spi">spi</a>, <a href="ident?i=protocol">protocol</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L295" href="source/net/ipv4/ip_vti.c#L295">295</a>         if (!<a href="ident?i=x">x</a>)
<a name="L296" href="source/net/ipv4/ip_vti.c#L296">296</a>                 return 0;
<a name="L297" href="source/net/ipv4/ip_vti.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/ip_vti.c#L298">298</a>         if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>)
<a name="L299" href="source/net/ipv4/ip_vti.c#L299">299</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=info">info</a>, 0, 0, <a href="ident?i=protocol">protocol</a>, 0);
<a name="L300" href="source/net/ipv4/ip_vti.c#L300">300</a>         else
<a name="L301" href="source/net/ipv4/ip_vti.c#L301">301</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, 0, <a href="ident?i=protocol">protocol</a>, 0);
<a name="L302" href="source/net/ipv4/ip_vti.c#L302">302</a>         <a href="ident?i=xfrm_state_put">xfrm_state_put</a>(<a href="ident?i=x">x</a>);
<a name="L303" href="source/net/ipv4/ip_vti.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/ip_vti.c#L304">304</a>         return 0;
<a name="L305" href="source/net/ipv4/ip_vti.c#L305">305</a> }
<a name="L306" href="source/net/ipv4/ip_vti.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/ip_vti.c#L307">307</a> static int
<a name="L308" href="source/net/ipv4/ip_vti.c#L308">308</a> <a href="ident?i=vti_tunnel_ioctl">vti_tunnel_ioctl</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=ifreq">ifreq</a> *ifr, int <a href="ident?i=cmd">cmd</a>)
<a name="L309" href="source/net/ipv4/ip_vti.c#L309">309</a> {
<a name="L310" href="source/net/ipv4/ip_vti.c#L310">310</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L311" href="source/net/ipv4/ip_vti.c#L311">311</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L312" href="source/net/ipv4/ip_vti.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/ip_vti.c#L313">313</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=p">p</a>, ifr-&gt;ifr_ifru.ifru_data, sizeof(<a href="ident?i=p">p</a>)))
<a name="L314" href="source/net/ipv4/ip_vti.c#L314">314</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L315" href="source/net/ipv4/ip_vti.c#L315">315</a> 
<a name="L316" href="source/net/ipv4/ip_vti.c#L316">316</a>         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCADDTUNNEL">SIOCADDTUNNEL</a> || <a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCCHGTUNNEL">SIOCCHGTUNNEL</a>) {
<a name="L317" href="source/net/ipv4/ip_vti.c#L317">317</a>                 if (<a href="ident?i=p">p</a>.iph.<a href="ident?i=version">version</a> != 4 || <a href="ident?i=p">p</a>.iph.<a href="ident?i=protocol">protocol</a> != <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a> ||
<a name="L318" href="source/net/ipv4/ip_vti.c#L318">318</a>                     <a href="ident?i=p">p</a>.iph.ihl != 5)
<a name="L319" href="source/net/ipv4/ip_vti.c#L319">319</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L320" href="source/net/ipv4/ip_vti.c#L320">320</a>         }
<a name="L321" href="source/net/ipv4/ip_vti.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/ip_vti.c#L322">322</a>         if (!(<a href="ident?i=p">p</a>.i_flags &amp; <a href="ident?i=GRE_KEY">GRE_KEY</a>))
<a name="L323" href="source/net/ipv4/ip_vti.c#L323">323</a>                 <a href="ident?i=p">p</a>.i_key = 0;
<a name="L324" href="source/net/ipv4/ip_vti.c#L324">324</a>         if (!(<a href="ident?i=p">p</a>.o_flags &amp; <a href="ident?i=GRE_KEY">GRE_KEY</a>))
<a name="L325" href="source/net/ipv4/ip_vti.c#L325">325</a>                 <a href="ident?i=p">p</a>.o_key = 0;
<a name="L326" href="source/net/ipv4/ip_vti.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/ip_vti.c#L327">327</a>         <a href="ident?i=p">p</a>.i_flags = <a href="ident?i=VTI_ISVTI">VTI_ISVTI</a>;
<a name="L328" href="source/net/ipv4/ip_vti.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/ip_vti.c#L329">329</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_ioctl">ip_tunnel_ioctl</a>(<a href="ident?i=dev">dev</a>, &amp;<a href="ident?i=p">p</a>, <a href="ident?i=cmd">cmd</a>);
<a name="L330" href="source/net/ipv4/ip_vti.c#L330">330</a>         if (<a href="ident?i=err">err</a>)
<a name="L331" href="source/net/ipv4/ip_vti.c#L331">331</a>                 return <a href="ident?i=err">err</a>;
<a name="L332" href="source/net/ipv4/ip_vti.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/ip_vti.c#L333">333</a>         if (<a href="ident?i=cmd">cmd</a> != <a href="ident?i=SIOCDELTUNNEL">SIOCDELTUNNEL</a>) {
<a name="L334" href="source/net/ipv4/ip_vti.c#L334">334</a>                 <a href="ident?i=p">p</a>.i_flags |= <a href="ident?i=GRE_KEY">GRE_KEY</a>;
<a name="L335" href="source/net/ipv4/ip_vti.c#L335">335</a>                 <a href="ident?i=p">p</a>.o_flags |= <a href="ident?i=GRE_KEY">GRE_KEY</a>;
<a name="L336" href="source/net/ipv4/ip_vti.c#L336">336</a>         }
<a name="L337" href="source/net/ipv4/ip_vti.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/ip_vti.c#L338">338</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(ifr-&gt;ifr_ifru.ifru_data, &amp;<a href="ident?i=p">p</a>, sizeof(<a href="ident?i=p">p</a>)))
<a name="L339" href="source/net/ipv4/ip_vti.c#L339">339</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L340" href="source/net/ipv4/ip_vti.c#L340">340</a>         return 0;
<a name="L341" href="source/net/ipv4/ip_vti.c#L341">341</a> }
<a name="L342" href="source/net/ipv4/ip_vti.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/ip_vti.c#L343">343</a> static const struct <a href="ident?i=net_device_ops">net_device_ops</a> <a href="ident?i=vti_netdev_ops">vti_netdev_ops</a> = {
<a name="L344" href="source/net/ipv4/ip_vti.c#L344">344</a>         .ndo_init       = <a href="ident?i=vti_tunnel_init">vti_tunnel_init</a>,
<a name="L345" href="source/net/ipv4/ip_vti.c#L345">345</a>         .ndo_uninit     = <a href="ident?i=ip_tunnel_uninit">ip_tunnel_uninit</a>,
<a name="L346" href="source/net/ipv4/ip_vti.c#L346">346</a>         .ndo_start_xmit = <a href="ident?i=vti_tunnel_xmit">vti_tunnel_xmit</a>,
<a name="L347" href="source/net/ipv4/ip_vti.c#L347">347</a>         .ndo_do_ioctl   = <a href="ident?i=vti_tunnel_ioctl">vti_tunnel_ioctl</a>,
<a name="L348" href="source/net/ipv4/ip_vti.c#L348">348</a>         .ndo_change_mtu = <a href="ident?i=ip_tunnel_change_mtu">ip_tunnel_change_mtu</a>,
<a name="L349" href="source/net/ipv4/ip_vti.c#L349">349</a>         .ndo_get_stats64 = <a href="ident?i=ip_tunnel_get_stats64">ip_tunnel_get_stats64</a>,
<a name="L350" href="source/net/ipv4/ip_vti.c#L350">350</a>         .ndo_get_iflink = <a href="ident?i=ip_tunnel_get_iflink">ip_tunnel_get_iflink</a>,
<a name="L351" href="source/net/ipv4/ip_vti.c#L351">351</a> };
<a name="L352" href="source/net/ipv4/ip_vti.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/ip_vti.c#L353">353</a> static void <a href="ident?i=vti_tunnel_setup">vti_tunnel_setup</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L354" href="source/net/ipv4/ip_vti.c#L354">354</a> {
<a name="L355" href="source/net/ipv4/ip_vti.c#L355">355</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>         = &amp;<a href="ident?i=vti_netdev_ops">vti_netdev_ops</a>;
<a name="L356" href="source/net/ipv4/ip_vti.c#L356">356</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>               = <a href="ident?i=ARPHRD_TUNNEL">ARPHRD_TUNNEL</a>;
<a name="L357" href="source/net/ipv4/ip_vti.c#L357">357</a>         <a href="ident?i=ip_tunnel_setup">ip_tunnel_setup</a>(<a href="ident?i=dev">dev</a>, vti_net_id);
<a name="L358" href="source/net/ipv4/ip_vti.c#L358">358</a> }
<a name="L359" href="source/net/ipv4/ip_vti.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/ip_vti.c#L360">360</a> static int <a href="ident?i=vti_tunnel_init">vti_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L361" href="source/net/ipv4/ip_vti.c#L361">361</a> {
<a name="L362" href="source/net/ipv4/ip_vti.c#L362">362</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L363" href="source/net/ipv4/ip_vti.c#L363">363</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L364" href="source/net/ipv4/ip_vti.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/ip_vti.c#L365">365</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;dev_addr, &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, 4);
<a name="L366" href="source/net/ipv4/ip_vti.c#L366">366</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>, 4);
<a name="L367" href="source/net/ipv4/ip_vti.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/ip_vti.c#L368">368</a>         <a href="ident?i=dev">dev</a>-&gt;hard_header_len    = <a href="ident?i=LL_MAX_HEADER">LL_MAX_HEADER</a> + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L369" href="source/net/ipv4/ip_vti.c#L369">369</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>                = <a href="ident?i=ETH_DATA_LEN">ETH_DATA_LEN</a>;
<a name="L370" href="source/net/ipv4/ip_vti.c#L370">370</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>              = <a href="ident?i=IFF_NOARP">IFF_NOARP</a>;
<a name="L371" href="source/net/ipv4/ip_vti.c#L371">371</a>         <a href="ident?i=dev">dev</a>-&gt;addr_len           = 4;
<a name="L372" href="source/net/ipv4/ip_vti.c#L372">372</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>           |= <a href="ident?i=NETIF_F_LLTX">NETIF_F_LLTX</a>;
<a name="L373" href="source/net/ipv4/ip_vti.c#L373">373</a>         <a href="ident?i=netif_keep_dst">netif_keep_dst</a>(<a href="ident?i=dev">dev</a>);
<a name="L374" href="source/net/ipv4/ip_vti.c#L374">374</a> 
<a name="L375" href="source/net/ipv4/ip_vti.c#L375">375</a>         return <a href="ident?i=ip_tunnel_init">ip_tunnel_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L376" href="source/net/ipv4/ip_vti.c#L376">376</a> }
<a name="L377" href="source/net/ipv4/ip_vti.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/ip_vti.c#L378">378</a> static void <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=vti_fb_tunnel_init">vti_fb_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L379" href="source/net/ipv4/ip_vti.c#L379">379</a> {
<a name="L380" href="source/net/ipv4/ip_vti.c#L380">380</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L381" href="source/net/ipv4/ip_vti.c#L381">381</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L382" href="source/net/ipv4/ip_vti.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/ip_vti.c#L383">383</a>         iph-&gt;<a href="ident?i=version">version</a>            = 4;
<a name="L384" href="source/net/ipv4/ip_vti.c#L384">384</a>         iph-&gt;<a href="ident?i=protocol">protocol</a>           = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L385" href="source/net/ipv4/ip_vti.c#L385">385</a>         iph-&gt;ihl                = 5;
<a name="L386" href="source/net/ipv4/ip_vti.c#L386">386</a> }
<a name="L387" href="source/net/ipv4/ip_vti.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/ip_vti.c#L388">388</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> vti_esp4_protocol <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L389" href="source/net/ipv4/ip_vti.c#L389">389</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=vti_rcv">vti_rcv</a>,
<a name="L390" href="source/net/ipv4/ip_vti.c#L390">390</a>         .<a href="ident?i=input_handler">input_handler</a>  =       <a href="ident?i=vti_input">vti_input</a>,
<a name="L391" href="source/net/ipv4/ip_vti.c#L391">391</a>         .cb_handler     =       <a href="ident?i=vti_rcv_cb">vti_rcv_cb</a>,
<a name="L392" href="source/net/ipv4/ip_vti.c#L392">392</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=vti4_err">vti4_err</a>,
<a name="L393" href="source/net/ipv4/ip_vti.c#L393">393</a>         .<a href="ident?i=priority">priority</a>       =       100,
<a name="L394" href="source/net/ipv4/ip_vti.c#L394">394</a> };
<a name="L395" href="source/net/ipv4/ip_vti.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/ip_vti.c#L396">396</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> vti_ah4_protocol <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L397" href="source/net/ipv4/ip_vti.c#L397">397</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=vti_rcv">vti_rcv</a>,
<a name="L398" href="source/net/ipv4/ip_vti.c#L398">398</a>         .<a href="ident?i=input_handler">input_handler</a>  =       <a href="ident?i=vti_input">vti_input</a>,
<a name="L399" href="source/net/ipv4/ip_vti.c#L399">399</a>         .cb_handler     =       <a href="ident?i=vti_rcv_cb">vti_rcv_cb</a>,
<a name="L400" href="source/net/ipv4/ip_vti.c#L400">400</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=vti4_err">vti4_err</a>,
<a name="L401" href="source/net/ipv4/ip_vti.c#L401">401</a>         .<a href="ident?i=priority">priority</a>       =       100,
<a name="L402" href="source/net/ipv4/ip_vti.c#L402">402</a> };
<a name="L403" href="source/net/ipv4/ip_vti.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/ip_vti.c#L404">404</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> vti_ipcomp4_protocol <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L405" href="source/net/ipv4/ip_vti.c#L405">405</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=vti_rcv">vti_rcv</a>,
<a name="L406" href="source/net/ipv4/ip_vti.c#L406">406</a>         .<a href="ident?i=input_handler">input_handler</a>  =       <a href="ident?i=vti_input">vti_input</a>,
<a name="L407" href="source/net/ipv4/ip_vti.c#L407">407</a>         .cb_handler     =       <a href="ident?i=vti_rcv_cb">vti_rcv_cb</a>,
<a name="L408" href="source/net/ipv4/ip_vti.c#L408">408</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=vti4_err">vti4_err</a>,
<a name="L409" href="source/net/ipv4/ip_vti.c#L409">409</a>         .<a href="ident?i=priority">priority</a>       =       100,
<a name="L410" href="source/net/ipv4/ip_vti.c#L410">410</a> };
<a name="L411" href="source/net/ipv4/ip_vti.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/ip_vti.c#L412">412</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=vti_init_net">vti_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L413" href="source/net/ipv4/ip_vti.c#L413">413</a> {
<a name="L414" href="source/net/ipv4/ip_vti.c#L414">414</a>         int <a href="ident?i=err">err</a>;
<a name="L415" href="source/net/ipv4/ip_vti.c#L415">415</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn;
<a name="L416" href="source/net/ipv4/ip_vti.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/ip_vti.c#L417">417</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_init_net">ip_tunnel_init_net</a>(<a href="ident?i=net">net</a>, vti_net_id, &amp;vti_link_ops, <i>"ip_vti0"</i>);
<a name="L418" href="source/net/ipv4/ip_vti.c#L418">418</a>         if (<a href="ident?i=err">err</a>)
<a name="L419" href="source/net/ipv4/ip_vti.c#L419">419</a>                 return <a href="ident?i=err">err</a>;
<a name="L420" href="source/net/ipv4/ip_vti.c#L420">420</a>         itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, vti_net_id);
<a name="L421" href="source/net/ipv4/ip_vti.c#L421">421</a>         <a href="ident?i=vti_fb_tunnel_init">vti_fb_tunnel_init</a>(itn-&gt;fb_tunnel_dev);
<a name="L422" href="source/net/ipv4/ip_vti.c#L422">422</a>         return 0;
<a name="L423" href="source/net/ipv4/ip_vti.c#L423">423</a> }
<a name="L424" href="source/net/ipv4/ip_vti.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/ip_vti.c#L425">425</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=vti_exit_net">vti_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L426" href="source/net/ipv4/ip_vti.c#L426">426</a> {
<a name="L427" href="source/net/ipv4/ip_vti.c#L427">427</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, vti_net_id);
<a name="L428" href="source/net/ipv4/ip_vti.c#L428">428</a>         <a href="ident?i=ip_tunnel_delete_net">ip_tunnel_delete_net</a>(itn, &amp;vti_link_ops);
<a name="L429" href="source/net/ipv4/ip_vti.c#L429">429</a> }
<a name="L430" href="source/net/ipv4/ip_vti.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/ip_vti.c#L431">431</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=vti_net_ops">vti_net_ops</a> = {
<a name="L432" href="source/net/ipv4/ip_vti.c#L432">432</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=vti_init_net">vti_init_net</a>,
<a name="L433" href="source/net/ipv4/ip_vti.c#L433">433</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=vti_exit_net">vti_exit_net</a>,
<a name="L434" href="source/net/ipv4/ip_vti.c#L434">434</a>         .<a href="ident?i=id">id</a>   = &amp;vti_net_id,
<a name="L435" href="source/net/ipv4/ip_vti.c#L435">435</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a>),
<a name="L436" href="source/net/ipv4/ip_vti.c#L436">436</a> };
<a name="L437" href="source/net/ipv4/ip_vti.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ip_vti.c#L438">438</a> static int <a href="ident?i=vti_tunnel_validate">vti_tunnel_validate</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L439" href="source/net/ipv4/ip_vti.c#L439">439</a> {
<a name="L440" href="source/net/ipv4/ip_vti.c#L440">440</a>         return 0;
<a name="L441" href="source/net/ipv4/ip_vti.c#L441">441</a> }
<a name="L442" href="source/net/ipv4/ip_vti.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/ip_vti.c#L443">443</a> static void <a href="ident?i=vti_netlink_parms">vti_netlink_parms</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[],
<a name="L444" href="source/net/ipv4/ip_vti.c#L444">444</a>                               struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>)
<a name="L445" href="source/net/ipv4/ip_vti.c#L445">445</a> {
<a name="L446" href="source/net/ipv4/ip_vti.c#L446">446</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=parms">parms</a>, 0, sizeof(*<a href="ident?i=parms">parms</a>));
<a name="L447" href="source/net/ipv4/ip_vti.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/ip_vti.c#L448">448</a>         <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L449" href="source/net/ipv4/ip_vti.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/ip_vti.c#L450">450</a>         if (!<a href="ident?i=data">data</a>)
<a name="L451" href="source/net/ipv4/ip_vti.c#L451">451</a>                 return;
<a name="L452" href="source/net/ipv4/ip_vti.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/ip_vti.c#L453">453</a>         <a href="ident?i=parms">parms</a>-&gt;i_flags = <a href="ident?i=VTI_ISVTI">VTI_ISVTI</a>;
<a name="L454" href="source/net/ipv4/ip_vti.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/ip_vti.c#L455">455</a>         if (<a href="ident?i=data">data</a>[IFLA_VTI_LINK])
<a name="L456" href="source/net/ipv4/ip_vti.c#L456">456</a>                 <a href="ident?i=parms">parms</a>-&gt;<a href="ident?i=link">link</a> = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=data">data</a>[IFLA_VTI_LINK]);
<a name="L457" href="source/net/ipv4/ip_vti.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/ip_vti.c#L458">458</a>         if (<a href="ident?i=data">data</a>[IFLA_VTI_IKEY])
<a name="L459" href="source/net/ipv4/ip_vti.c#L459">459</a>                 <a href="ident?i=parms">parms</a>-&gt;i_key = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=data">data</a>[IFLA_VTI_IKEY]);
<a name="L460" href="source/net/ipv4/ip_vti.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/ip_vti.c#L461">461</a>         if (<a href="ident?i=data">data</a>[IFLA_VTI_OKEY])
<a name="L462" href="source/net/ipv4/ip_vti.c#L462">462</a>                 <a href="ident?i=parms">parms</a>-&gt;o_key = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=data">data</a>[IFLA_VTI_OKEY]);
<a name="L463" href="source/net/ipv4/ip_vti.c#L463">463</a> 
<a name="L464" href="source/net/ipv4/ip_vti.c#L464">464</a>         if (<a href="ident?i=data">data</a>[IFLA_VTI_LOCAL])
<a name="L465" href="source/net/ipv4/ip_vti.c#L465">465</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=data">data</a>[IFLA_VTI_LOCAL]);
<a name="L466" href="source/net/ipv4/ip_vti.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/ip_vti.c#L467">467</a>         if (<a href="ident?i=data">data</a>[IFLA_VTI_REMOTE])
<a name="L468" href="source/net/ipv4/ip_vti.c#L468">468</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=data">data</a>[IFLA_VTI_REMOTE]);
<a name="L469" href="source/net/ipv4/ip_vti.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/ip_vti.c#L470">470</a> }
<a name="L471" href="source/net/ipv4/ip_vti.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/ip_vti.c#L472">472</a> static int <a href="ident?i=vti_newlink">vti_newlink</a>(struct <a href="ident?i=net">net</a> *src_net, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L473" href="source/net/ipv4/ip_vti.c#L473">473</a>                        struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L474" href="source/net/ipv4/ip_vti.c#L474">474</a> {
<a name="L475" href="source/net/ipv4/ip_vti.c#L475">475</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=parms">parms</a>;
<a name="L476" href="source/net/ipv4/ip_vti.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/ip_vti.c#L477">477</a>         <a href="ident?i=vti_netlink_parms">vti_netlink_parms</a>(<a href="ident?i=data">data</a>, &amp;<a href="ident?i=parms">parms</a>);
<a name="L478" href="source/net/ipv4/ip_vti.c#L478">478</a>         return <a href="ident?i=ip_tunnel_newlink">ip_tunnel_newlink</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=parms">parms</a>);
<a name="L479" href="source/net/ipv4/ip_vti.c#L479">479</a> }
<a name="L480" href="source/net/ipv4/ip_vti.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/ip_vti.c#L481">481</a> static int <a href="ident?i=vti_changelink">vti_changelink</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L482" href="source/net/ipv4/ip_vti.c#L482">482</a>                           struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L483" href="source/net/ipv4/ip_vti.c#L483">483</a> {
<a name="L484" href="source/net/ipv4/ip_vti.c#L484">484</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L485" href="source/net/ipv4/ip_vti.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/ip_vti.c#L486">486</a>         <a href="ident?i=vti_netlink_parms">vti_netlink_parms</a>(<a href="ident?i=data">data</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L487" href="source/net/ipv4/ip_vti.c#L487">487</a>         return <a href="ident?i=ip_tunnel_changelink">ip_tunnel_changelink</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L488" href="source/net/ipv4/ip_vti.c#L488">488</a> }
<a name="L489" href="source/net/ipv4/ip_vti.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/ip_vti.c#L490">490</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=vti_get_size">vti_get_size</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L491" href="source/net/ipv4/ip_vti.c#L491">491</a> {
<a name="L492" href="source/net/ipv4/ip_vti.c#L492">492</a>         return
<a name="L493" href="source/net/ipv4/ip_vti.c#L493">493</a>                 <b><i>/* IFLA_VTI_LINK */</i></b>
<a name="L494" href="source/net/ipv4/ip_vti.c#L494">494</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L495" href="source/net/ipv4/ip_vti.c#L495">495</a>                 <b><i>/* IFLA_VTI_IKEY */</i></b>
<a name="L496" href="source/net/ipv4/ip_vti.c#L496">496</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L497" href="source/net/ipv4/ip_vti.c#L497">497</a>                 <b><i>/* IFLA_VTI_OKEY */</i></b>
<a name="L498" href="source/net/ipv4/ip_vti.c#L498">498</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L499" href="source/net/ipv4/ip_vti.c#L499">499</a>                 <b><i>/* IFLA_VTI_LOCAL */</i></b>
<a name="L500" href="source/net/ipv4/ip_vti.c#L500">500</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L501" href="source/net/ipv4/ip_vti.c#L501">501</a>                 <b><i>/* IFLA_VTI_REMOTE */</i></b>
<a name="L502" href="source/net/ipv4/ip_vti.c#L502">502</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L503" href="source/net/ipv4/ip_vti.c#L503">503</a>                 0;
<a name="L504" href="source/net/ipv4/ip_vti.c#L504">504</a> }
<a name="L505" href="source/net/ipv4/ip_vti.c#L505">505</a> 
<a name="L506" href="source/net/ipv4/ip_vti.c#L506">506</a> static int <a href="ident?i=vti_fill_info">vti_fill_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L507" href="source/net/ipv4/ip_vti.c#L507">507</a> {
<a name="L508" href="source/net/ipv4/ip_vti.c#L508">508</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L509" href="source/net/ipv4/ip_vti.c#L509">509</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a> = &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>;
<a name="L510" href="source/net/ipv4/ip_vti.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/ip_vti.c#L511">511</a>         <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, IFLA_VTI_LINK, <a href="ident?i=p">p</a>-&gt;<a href="ident?i=link">link</a>);
<a name="L512" href="source/net/ipv4/ip_vti.c#L512">512</a>         <a href="ident?i=nla_put_be32">nla_put_be32</a>(<a href="ident?i=skb">skb</a>, IFLA_VTI_IKEY, <a href="ident?i=p">p</a>-&gt;i_key);
<a name="L513" href="source/net/ipv4/ip_vti.c#L513">513</a>         <a href="ident?i=nla_put_be32">nla_put_be32</a>(<a href="ident?i=skb">skb</a>, IFLA_VTI_OKEY, <a href="ident?i=p">p</a>-&gt;o_key);
<a name="L514" href="source/net/ipv4/ip_vti.c#L514">514</a>         <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFLA_VTI_LOCAL, <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>);
<a name="L515" href="source/net/ipv4/ip_vti.c#L515">515</a>         <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFLA_VTI_REMOTE, <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>);
<a name="L516" href="source/net/ipv4/ip_vti.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/ip_vti.c#L517">517</a>         return 0;
<a name="L518" href="source/net/ipv4/ip_vti.c#L518">518</a> }
<a name="L519" href="source/net/ipv4/ip_vti.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/ip_vti.c#L520">520</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=vti_policy">vti_policy</a>[<a href="ident?i=IFLA_VTI_MAX">IFLA_VTI_MAX</a> + 1] = {
<a name="L521" href="source/net/ipv4/ip_vti.c#L521">521</a>         [IFLA_VTI_LINK]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L522" href="source/net/ipv4/ip_vti.c#L522">522</a>         [IFLA_VTI_IKEY]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L523" href="source/net/ipv4/ip_vti.c#L523">523</a>         [IFLA_VTI_OKEY]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L524" href="source/net/ipv4/ip_vti.c#L524">524</a>         [IFLA_VTI_LOCAL]        = { .<a href="ident?i=len">len</a> = <a href="ident?i=FIELD_SIZEOF">FIELD_SIZEOF</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=saddr">saddr</a>) },
<a name="L525" href="source/net/ipv4/ip_vti.c#L525">525</a>         [IFLA_VTI_REMOTE]       = { .<a href="ident?i=len">len</a> = <a href="ident?i=FIELD_SIZEOF">FIELD_SIZEOF</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=daddr">daddr</a>) },
<a name="L526" href="source/net/ipv4/ip_vti.c#L526">526</a> };
<a name="L527" href="source/net/ipv4/ip_vti.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/ip_vti.c#L528">528</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> vti_link_ops <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L529" href="source/net/ipv4/ip_vti.c#L529">529</a>         .kind           = <i>"vti"</i>,
<a name="L530" href="source/net/ipv4/ip_vti.c#L530">530</a>         .maxtype        = <a href="ident?i=IFLA_VTI_MAX">IFLA_VTI_MAX</a>,
<a name="L531" href="source/net/ipv4/ip_vti.c#L531">531</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=vti_policy">vti_policy</a>,
<a name="L532" href="source/net/ipv4/ip_vti.c#L532">532</a>         .priv_size      = sizeof(struct <a href="ident?i=ip_tunnel">ip_tunnel</a>),
<a name="L533" href="source/net/ipv4/ip_vti.c#L533">533</a>         .<a href="ident?i=setup">setup</a>          = <a href="ident?i=vti_tunnel_setup">vti_tunnel_setup</a>,
<a name="L534" href="source/net/ipv4/ip_vti.c#L534">534</a>         .<a href="ident?i=validate">validate</a>       = <a href="ident?i=vti_tunnel_validate">vti_tunnel_validate</a>,
<a name="L535" href="source/net/ipv4/ip_vti.c#L535">535</a>         .newlink        = <a href="ident?i=vti_newlink">vti_newlink</a>,
<a name="L536" href="source/net/ipv4/ip_vti.c#L536">536</a>         .changelink     = <a href="ident?i=vti_changelink">vti_changelink</a>,
<a name="L537" href="source/net/ipv4/ip_vti.c#L537">537</a>         .dellink        = <a href="ident?i=ip_tunnel_dellink">ip_tunnel_dellink</a>,
<a name="L538" href="source/net/ipv4/ip_vti.c#L538">538</a>         .<a href="ident?i=get_size">get_size</a>       = <a href="ident?i=vti_get_size">vti_get_size</a>,
<a name="L539" href="source/net/ipv4/ip_vti.c#L539">539</a>         .fill_info      = <a href="ident?i=vti_fill_info">vti_fill_info</a>,
<a name="L540" href="source/net/ipv4/ip_vti.c#L540">540</a>         .get_link_net   = <a href="ident?i=ip_tunnel_get_link_net">ip_tunnel_get_link_net</a>,
<a name="L541" href="source/net/ipv4/ip_vti.c#L541">541</a> };
<a name="L542" href="source/net/ipv4/ip_vti.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/ip_vti.c#L543">543</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=vti_init">vti_init</a>(void)
<a name="L544" href="source/net/ipv4/ip_vti.c#L544">544</a> {
<a name="L545" href="source/net/ipv4/ip_vti.c#L545">545</a>         const char *<a href="ident?i=msg">msg</a>;
<a name="L546" href="source/net/ipv4/ip_vti.c#L546">546</a>         int <a href="ident?i=err">err</a>;
<a name="L547" href="source/net/ipv4/ip_vti.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/ip_vti.c#L548">548</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"IPv4 over IPsec tunneling driver\n"</i>);
<a name="L549" href="source/net/ipv4/ip_vti.c#L549">549</a> 
<a name="L550" href="source/net/ipv4/ip_vti.c#L550">550</a>         <a href="ident?i=msg">msg</a> = <i>"tunnel device"</i>;
<a name="L551" href="source/net/ipv4/ip_vti.c#L551">551</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_device">register_pernet_device</a>(&amp;<a href="ident?i=vti_net_ops">vti_net_ops</a>);
<a name="L552" href="source/net/ipv4/ip_vti.c#L552">552</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L553" href="source/net/ipv4/ip_vti.c#L553">553</a>                 goto pernet_dev_failed;
<a name="L554" href="source/net/ipv4/ip_vti.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/ip_vti.c#L555">555</a>         <a href="ident?i=msg">msg</a> = <i>"tunnel protocols"</i>;
<a name="L556" href="source/net/ipv4/ip_vti.c#L556">556</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(&amp;vti_esp4_protocol, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>);
<a name="L557" href="source/net/ipv4/ip_vti.c#L557">557</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L558" href="source/net/ipv4/ip_vti.c#L558">558</a>                 goto xfrm_proto_esp_failed;
<a name="L559" href="source/net/ipv4/ip_vti.c#L559">559</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(&amp;vti_ah4_protocol, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>);
<a name="L560" href="source/net/ipv4/ip_vti.c#L560">560</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L561" href="source/net/ipv4/ip_vti.c#L561">561</a>                 goto xfrm_proto_ah_failed;
<a name="L562" href="source/net/ipv4/ip_vti.c#L562">562</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(&amp;vti_ipcomp4_protocol, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>);
<a name="L563" href="source/net/ipv4/ip_vti.c#L563">563</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L564" href="source/net/ipv4/ip_vti.c#L564">564</a>                 goto xfrm_proto_comp_failed;
<a name="L565" href="source/net/ipv4/ip_vti.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/ip_vti.c#L566">566</a>         <a href="ident?i=msg">msg</a> = <i>"netlink interface"</i>;
<a name="L567" href="source/net/ipv4/ip_vti.c#L567">567</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtnl_link_register">rtnl_link_register</a>(&amp;vti_link_ops);
<a name="L568" href="source/net/ipv4/ip_vti.c#L568">568</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L569" href="source/net/ipv4/ip_vti.c#L569">569</a>                 goto rtnl_link_failed;
<a name="L570" href="source/net/ipv4/ip_vti.c#L570">570</a> 
<a name="L571" href="source/net/ipv4/ip_vti.c#L571">571</a>         return <a href="ident?i=err">err</a>;
<a name="L572" href="source/net/ipv4/ip_vti.c#L572">572</a> 
<a name="L573" href="source/net/ipv4/ip_vti.c#L573">573</a> rtnl_link_failed:
<a name="L574" href="source/net/ipv4/ip_vti.c#L574">574</a>         <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;vti_ipcomp4_protocol, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>);
<a name="L575" href="source/net/ipv4/ip_vti.c#L575">575</a> xfrm_proto_comp_failed:
<a name="L576" href="source/net/ipv4/ip_vti.c#L576">576</a>         <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;vti_ah4_protocol, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>);
<a name="L577" href="source/net/ipv4/ip_vti.c#L577">577</a> xfrm_proto_ah_failed:
<a name="L578" href="source/net/ipv4/ip_vti.c#L578">578</a>         <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;vti_esp4_protocol, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>);
<a name="L579" href="source/net/ipv4/ip_vti.c#L579">579</a> xfrm_proto_esp_failed:
<a name="L580" href="source/net/ipv4/ip_vti.c#L580">580</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=vti_net_ops">vti_net_ops</a>);
<a name="L581" href="source/net/ipv4/ip_vti.c#L581">581</a> pernet_dev_failed:
<a name="L582" href="source/net/ipv4/ip_vti.c#L582">582</a>         <a href="ident?i=pr_err">pr_err</a>(<i>"vti init: failed to register %s\n"</i>, <a href="ident?i=msg">msg</a>);
<a name="L583" href="source/net/ipv4/ip_vti.c#L583">583</a>         return <a href="ident?i=err">err</a>;
<a name="L584" href="source/net/ipv4/ip_vti.c#L584">584</a> }
<a name="L585" href="source/net/ipv4/ip_vti.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/ip_vti.c#L586">586</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=vti_fini">vti_fini</a>(void)
<a name="L587" href="source/net/ipv4/ip_vti.c#L587">587</a> {
<a name="L588" href="source/net/ipv4/ip_vti.c#L588">588</a>         <a href="ident?i=rtnl_link_unregister">rtnl_link_unregister</a>(&amp;vti_link_ops);
<a name="L589" href="source/net/ipv4/ip_vti.c#L589">589</a>         <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;vti_ipcomp4_protocol, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>);
<a name="L590" href="source/net/ipv4/ip_vti.c#L590">590</a>         <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;vti_ah4_protocol, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>);
<a name="L591" href="source/net/ipv4/ip_vti.c#L591">591</a>         <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;vti_esp4_protocol, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>);
<a name="L592" href="source/net/ipv4/ip_vti.c#L592">592</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=vti_net_ops">vti_net_ops</a>);
<a name="L593" href="source/net/ipv4/ip_vti.c#L593">593</a> }
<a name="L594" href="source/net/ipv4/ip_vti.c#L594">594</a> 
<a name="L595" href="source/net/ipv4/ip_vti.c#L595">595</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=vti_init">vti_init</a>);
<a name="L596" href="source/net/ipv4/ip_vti.c#L596">596</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=vti_fini">vti_fini</a>);
<a name="L597" href="source/net/ipv4/ip_vti.c#L597">597</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L598" href="source/net/ipv4/ip_vti.c#L598">598</a> <a href="ident?i=MODULE_ALIAS_RTNL_LINK">MODULE_ALIAS_RTNL_LINK</a>(<i>"vti"</i>);
<a name="L599" href="source/net/ipv4/ip_vti.c#L599">599</a> <a href="ident?i=MODULE_ALIAS_NETDEV">MODULE_ALIAS_NETDEV</a>(<i>"ip_vti0"</i>);
<a name="L600" href="source/net/ipv4/ip_vti.c#L600">600</a> </pre></div><p>
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
