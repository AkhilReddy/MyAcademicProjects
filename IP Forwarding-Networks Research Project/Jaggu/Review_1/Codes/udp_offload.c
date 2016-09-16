<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/udp_offload.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/udp_offload.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/udp_offload.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/udp_offload.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/udp_offload.c">udp_offload.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/udp_offload.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/udp_offload.c#L2">2</a> <b><i> *      IPV4 GSO/GRO offload support</i></b>
  <a name="L3" href="source/net/ipv4/udp_offload.c#L3">3</a> <b><i> *      Linux INET implementation</i></b>
  <a name="L4" href="source/net/ipv4/udp_offload.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/udp_offload.c#L5">5</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L6" href="source/net/ipv4/udp_offload.c#L6">6</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L7" href="source/net/ipv4/udp_offload.c#L7">7</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L8" href="source/net/ipv4/udp_offload.c#L8">8</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
  <a name="L9" href="source/net/ipv4/udp_offload.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/udp_offload.c#L10">10</a> <b><i> *      UDPv4 GSO support</i></b>
 <a name="L11" href="source/net/ipv4/udp_offload.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/udp_offload.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/udp_offload.c#L13">13</a> #include &lt;linux/skbuff.h&gt;
 <a name="L14" href="source/net/ipv4/udp_offload.c#L14">14</a> #include &lt;net/udp.h&gt;
 <a name="L15" href="source/net/ipv4/udp_offload.c#L15">15</a> #include &lt;net/protocol.h&gt;
 <a name="L16" href="source/net/ipv4/udp_offload.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/udp_offload.c#L17">17</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(udp_offload_lock);
 <a name="L18" href="source/net/ipv4/udp_offload.c#L18">18</a> static struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> <a href="ident?i=__rcu">__rcu</a> *udp_offload_base <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L19" href="source/net/ipv4/udp_offload.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/udp_offload.c#L20">20</a> #define <a href="ident?i=udp_deref_protected">udp_deref_protected</a>(<a href="ident?i=X">X</a>) <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=X">X</a>, <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;udp_offload_lock))
 <a name="L21" href="source/net/ipv4/udp_offload.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/udp_offload.c#L22">22</a> struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> {
 <a name="L23" href="source/net/ipv4/udp_offload.c#L23">23</a>         struct <a href="ident?i=udp_offload">udp_offload</a>      *offload;
 <a name="L24" href="source/net/ipv4/udp_offload.c#L24">24</a>         struct <a href="ident?i=rcu_head">rcu_head</a>         rcu;
 <a name="L25" href="source/net/ipv4/udp_offload.c#L25">25</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=next">next</a>;
 <a name="L26" href="source/net/ipv4/udp_offload.c#L26">26</a> };
 <a name="L27" href="source/net/ipv4/udp_offload.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/udp_offload.c#L28">28</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=__skb_udp_tunnel_segment">__skb_udp_tunnel_segment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L29" href="source/net/ipv4/udp_offload.c#L29">29</a>         <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>,
 <a name="L30" href="source/net/ipv4/udp_offload.c#L30">30</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *(*gso_inner_segment)(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L31" href="source/net/ipv4/udp_offload.c#L31">31</a>                                              <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>),
 <a name="L32" href="source/net/ipv4/udp_offload.c#L32">32</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=new_protocol">new_protocol</a>, <a href="ident?i=bool">bool</a> is_ipv6)
 <a name="L33" href="source/net/ipv4/udp_offload.c#L33">33</a> {
 <a name="L34" href="source/net/ipv4/udp_offload.c#L34">34</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *segs = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
 <a name="L35" href="source/net/ipv4/udp_offload.c#L35">35</a>         <a href="ident?i=u16">u16</a> mac_offset = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mac_header">mac_header</a>;
 <a name="L36" href="source/net/ipv4/udp_offload.c#L36">36</a>         int mac_len = <a href="ident?i=skb">skb</a>-&gt;mac_len;
 <a name="L37" href="source/net/ipv4/udp_offload.c#L37">37</a>         int tnl_hlen = <a href="ident?i=skb_inner_mac_header">skb_inner_mac_header</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L38" href="source/net/ipv4/udp_offload.c#L38">38</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=protocol">protocol</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L39" href="source/net/ipv4/udp_offload.c#L39">39</a>         <a href="ident?i=netdev_features_t">netdev_features_t</a> enc_features;
 <a name="L40" href="source/net/ipv4/udp_offload.c#L40">40</a>         int udp_offset, outer_hlen;
 <a name="L41" href="source/net/ipv4/udp_offload.c#L41">41</a>         unsigned int oldlen;
 <a name="L42" href="source/net/ipv4/udp_offload.c#L42">42</a>         <a href="ident?i=bool">bool</a> need_csum = !!(<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type &amp;
 <a name="L43" href="source/net/ipv4/udp_offload.c#L43">43</a>                             SKB_GSO_UDP_TUNNEL_CSUM);
 <a name="L44" href="source/net/ipv4/udp_offload.c#L44">44</a>         <a href="ident?i=bool">bool</a> remcsum = !!(<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type &amp; SKB_GSO_TUNNEL_REMCSUM);
 <a name="L45" href="source/net/ipv4/udp_offload.c#L45">45</a>         <a href="ident?i=bool">bool</a> offload_csum = <a href="ident?i=false">false</a>, dont_encap = (need_csum || remcsum);
 <a name="L46" href="source/net/ipv4/udp_offload.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/udp_offload.c#L47">47</a>         oldlen = (<a href="ident?i=u16">u16</a>)~skb-&gt;<a href="ident?i=len">len</a>;
 <a name="L48" href="source/net/ipv4/udp_offload.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/udp_offload.c#L49">49</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, tnl_hlen)))
 <a name="L50" href="source/net/ipv4/udp_offload.c#L50">50</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L51" href="source/net/ipv4/udp_offload.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/udp_offload.c#L52">52</a>         <a href="ident?i=skb">skb</a>-&gt;encapsulation = 0;
 <a name="L53" href="source/net/ipv4/udp_offload.c#L53">53</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, tnl_hlen);
 <a name="L54" href="source/net/ipv4/udp_offload.c#L54">54</a>         <a href="ident?i=skb_reset_mac_header">skb_reset_mac_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L55" href="source/net/ipv4/udp_offload.c#L55">55</a>         <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_inner_network_offset">skb_inner_network_offset</a>(<a href="ident?i=skb">skb</a>));
 <a name="L56" href="source/net/ipv4/udp_offload.c#L56">56</a>         <a href="ident?i=skb">skb</a>-&gt;mac_len = <a href="ident?i=skb_inner_network_offset">skb_inner_network_offset</a>(<a href="ident?i=skb">skb</a>);
 <a name="L57" href="source/net/ipv4/udp_offload.c#L57">57</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=new_protocol">new_protocol</a>;
 <a name="L58" href="source/net/ipv4/udp_offload.c#L58">58</a>         <a href="ident?i=skb">skb</a>-&gt;encap_hdr_csum = need_csum;
 <a name="L59" href="source/net/ipv4/udp_offload.c#L59">59</a>         <a href="ident?i=skb">skb</a>-&gt;remcsum_offload = remcsum;
 <a name="L60" href="source/net/ipv4/udp_offload.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/udp_offload.c#L61">61</a>         <b><i>/* Try to offload checksum if possible */</i></b>
 <a name="L62" href="source/net/ipv4/udp_offload.c#L62">62</a>         offload_csum = !!(need_csum &amp;&amp;
 <a name="L63" href="source/net/ipv4/udp_offload.c#L63">63</a>                           (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> &amp;
 <a name="L64" href="source/net/ipv4/udp_offload.c#L64">64</a>                            (is_ipv6 ? <a href="ident?i=NETIF_F_V6_CSUM">NETIF_F_V6_CSUM</a> : <a href="ident?i=NETIF_F_V4_CSUM">NETIF_F_V4_CSUM</a>)));
 <a name="L65" href="source/net/ipv4/udp_offload.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/udp_offload.c#L66">66</a>         <b><i>/* segment inner packet. */</i></b>
 <a name="L67" href="source/net/ipv4/udp_offload.c#L67">67</a>         enc_features = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;hw_enc_features &amp; <a href="ident?i=features">features</a>;
 <a name="L68" href="source/net/ipv4/udp_offload.c#L68">68</a>         segs = gso_inner_segment(<a href="ident?i=skb">skb</a>, enc_features);
 <a name="L69" href="source/net/ipv4/udp_offload.c#L69">69</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(segs)) {
 <a name="L70" href="source/net/ipv4/udp_offload.c#L70">70</a>                 <a href="ident?i=skb_gso_error_unwind">skb_gso_error_unwind</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=protocol">protocol</a>, tnl_hlen, mac_offset,
 <a name="L71" href="source/net/ipv4/udp_offload.c#L71">71</a>                                      mac_len);
 <a name="L72" href="source/net/ipv4/udp_offload.c#L72">72</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L73" href="source/net/ipv4/udp_offload.c#L73">73</a>         }
 <a name="L74" href="source/net/ipv4/udp_offload.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/udp_offload.c#L75">75</a>         outer_hlen = <a href="ident?i=skb_tnl_header_len">skb_tnl_header_len</a>(<a href="ident?i=skb">skb</a>);
 <a name="L76" href="source/net/ipv4/udp_offload.c#L76">76</a>         udp_offset = outer_hlen - tnl_hlen;
 <a name="L77" href="source/net/ipv4/udp_offload.c#L77">77</a>         <a href="ident?i=skb">skb</a> = segs;
 <a name="L78" href="source/net/ipv4/udp_offload.c#L78">78</a>         do {
 <a name="L79" href="source/net/ipv4/udp_offload.c#L79">79</a>                 struct <a href="ident?i=udphdr">udphdr</a> *uh;
 <a name="L80" href="source/net/ipv4/udp_offload.c#L80">80</a>                 int <a href="ident?i=len">len</a>;
 <a name="L81" href="source/net/ipv4/udp_offload.c#L81">81</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=delta">delta</a>;
 <a name="L82" href="source/net/ipv4/udp_offload.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/udp_offload.c#L83">83</a>                 if (dont_encap) {
 <a name="L84" href="source/net/ipv4/udp_offload.c#L84">84</a>                         <a href="ident?i=skb">skb</a>-&gt;encapsulation = 0;
 <a name="L85" href="source/net/ipv4/udp_offload.c#L85">85</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
 <a name="L86" href="source/net/ipv4/udp_offload.c#L86">86</a>                 } else {
 <a name="L87" href="source/net/ipv4/udp_offload.c#L87">87</a>                         <b><i>/* Only set up inner headers if we might be offloading</i></b>
 <a name="L88" href="source/net/ipv4/udp_offload.c#L88">88</a> <b><i>                         * inner checksum.</i></b>
 <a name="L89" href="source/net/ipv4/udp_offload.c#L89">89</a> <b><i>                         */</i></b>
 <a name="L90" href="source/net/ipv4/udp_offload.c#L90">90</a>                         <a href="ident?i=skb_reset_inner_headers">skb_reset_inner_headers</a>(<a href="ident?i=skb">skb</a>);
 <a name="L91" href="source/net/ipv4/udp_offload.c#L91">91</a>                         <a href="ident?i=skb">skb</a>-&gt;encapsulation = 1;
 <a name="L92" href="source/net/ipv4/udp_offload.c#L92">92</a>                 }
 <a name="L93" href="source/net/ipv4/udp_offload.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/udp_offload.c#L94">94</a>                 <a href="ident?i=skb">skb</a>-&gt;mac_len = mac_len;
 <a name="L95" href="source/net/ipv4/udp_offload.c#L95">95</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=protocol">protocol</a>;
 <a name="L96" href="source/net/ipv4/udp_offload.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/udp_offload.c#L97">97</a>                 <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, outer_hlen);
 <a name="L98" href="source/net/ipv4/udp_offload.c#L98">98</a>                 <a href="ident?i=skb_reset_mac_header">skb_reset_mac_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L99" href="source/net/ipv4/udp_offload.c#L99">99</a>                 <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, mac_len);
<a name="L100" href="source/net/ipv4/udp_offload.c#L100">100</a>                 <a href="ident?i=skb_set_transport_header">skb_set_transport_header</a>(<a href="ident?i=skb">skb</a>, udp_offset);
<a name="L101" href="source/net/ipv4/udp_offload.c#L101">101</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - udp_offset;
<a name="L102" href="source/net/ipv4/udp_offload.c#L102">102</a>                 uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L103" href="source/net/ipv4/udp_offload.c#L103">103</a>                 uh-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=len">len</a>);
<a name="L104" href="source/net/ipv4/udp_offload.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/udp_offload.c#L105">105</a>                 if (!need_csum)
<a name="L106" href="source/net/ipv4/udp_offload.c#L106">106</a>                         continue;
<a name="L107" href="source/net/ipv4/udp_offload.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/udp_offload.c#L108">108</a>                 <a href="ident?i=delta">delta</a> = <a href="ident?i=htonl">htonl</a>(oldlen + <a href="ident?i=len">len</a>);
<a name="L109" href="source/net/ipv4/udp_offload.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/udp_offload.c#L110">110</a>                 uh-&gt;<a href="ident?i=check">check</a> = ~csum_fold((<a href="ident?i=__force">__force</a> <a href="ident?i=__wsum">__wsum</a>)
<a name="L111" href="source/net/ipv4/udp_offload.c#L111">111</a>                                        ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)uh-&gt;<a href="ident?i=check">check</a> +
<a name="L112" href="source/net/ipv4/udp_offload.c#L112">112</a>                                         (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=delta">delta</a>));
<a name="L113" href="source/net/ipv4/udp_offload.c#L113">113</a>                 if (offload_csum) {
<a name="L114" href="source/net/ipv4/udp_offload.c#L114">114</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L115" href="source/net/ipv4/udp_offload.c#L115">115</a>                         <a href="ident?i=skb">skb</a>-&gt;csum_start = <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=head">head</a>;
<a name="L116" href="source/net/ipv4/udp_offload.c#L116">116</a>                         <a href="ident?i=skb">skb</a>-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=udphdr">udphdr</a>, <a href="ident?i=check">check</a>);
<a name="L117" href="source/net/ipv4/udp_offload.c#L117">117</a>                 } else if (remcsum) {
<a name="L118" href="source/net/ipv4/udp_offload.c#L118">118</a>                         <b><i>/* Need to calculate checksum from scratch,</i></b>
<a name="L119" href="source/net/ipv4/udp_offload.c#L119">119</a> <b><i>                         * inner checksums are never when doing</i></b>
<a name="L120" href="source/net/ipv4/udp_offload.c#L120">120</a> <b><i>                         * remote_checksum_offload.</i></b>
<a name="L121" href="source/net/ipv4/udp_offload.c#L121">121</a> <b><i>                         */</i></b>
<a name="L122" href="source/net/ipv4/udp_offload.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/udp_offload.c#L123">123</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, udp_offset,
<a name="L124" href="source/net/ipv4/udp_offload.c#L124">124</a>                                                  <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - udp_offset,
<a name="L125" href="source/net/ipv4/udp_offload.c#L125">125</a>                                                  0);
<a name="L126" href="source/net/ipv4/udp_offload.c#L126">126</a>                         uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>);
<a name="L127" href="source/net/ipv4/udp_offload.c#L127">127</a>                         if (uh-&gt;<a href="ident?i=check">check</a> == 0)
<a name="L128" href="source/net/ipv4/udp_offload.c#L128">128</a>                                 uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L129" href="source/net/ipv4/udp_offload.c#L129">129</a>                 } else {
<a name="L130" href="source/net/ipv4/udp_offload.c#L130">130</a>                         uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=gso_make_checksum">gso_make_checksum</a>(<a href="ident?i=skb">skb</a>, ~uh-&gt;<a href="ident?i=check">check</a>);
<a name="L131" href="source/net/ipv4/udp_offload.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/udp_offload.c#L132">132</a>                         if (uh-&gt;<a href="ident?i=check">check</a> == 0)
<a name="L133" href="source/net/ipv4/udp_offload.c#L133">133</a>                                 uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L134" href="source/net/ipv4/udp_offload.c#L134">134</a>                 }
<a name="L135" href="source/net/ipv4/udp_offload.c#L135">135</a>         } while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>));
<a name="L136" href="source/net/ipv4/udp_offload.c#L136">136</a> <a href="ident?i=out">out</a>:
<a name="L137" href="source/net/ipv4/udp_offload.c#L137">137</a>         return segs;
<a name="L138" href="source/net/ipv4/udp_offload.c#L138">138</a> }
<a name="L139" href="source/net/ipv4/udp_offload.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/udp_offload.c#L140">140</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb_udp_tunnel_segment">skb_udp_tunnel_segment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L141" href="source/net/ipv4/udp_offload.c#L141">141</a>                                        <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>,
<a name="L142" href="source/net/ipv4/udp_offload.c#L142">142</a>                                        <a href="ident?i=bool">bool</a> is_ipv6)
<a name="L143" href="source/net/ipv4/udp_offload.c#L143">143</a> {
<a name="L144" href="source/net/ipv4/udp_offload.c#L144">144</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=protocol">protocol</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L145" href="source/net/ipv4/udp_offload.c#L145">145</a>         const struct <a href="ident?i=net_offload">net_offload</a> **offloads;
<a name="L146" href="source/net/ipv4/udp_offload.c#L146">146</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L147" href="source/net/ipv4/udp_offload.c#L147">147</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *segs = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L148" href="source/net/ipv4/udp_offload.c#L148">148</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *(*gso_inner_segment)(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L149" href="source/net/ipv4/udp_offload.c#L149">149</a>                                              <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>);
<a name="L150" href="source/net/ipv4/udp_offload.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/udp_offload.c#L151">151</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L152" href="source/net/ipv4/udp_offload.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/udp_offload.c#L153">153</a>         switch (<a href="ident?i=skb">skb</a>-&gt;inner_protocol_type) {
<a name="L154" href="source/net/ipv4/udp_offload.c#L154">154</a>         case <a href="ident?i=ENCAP_TYPE_ETHER">ENCAP_TYPE_ETHER</a>:
<a name="L155" href="source/net/ipv4/udp_offload.c#L155">155</a>                 <a href="ident?i=protocol">protocol</a> = <a href="ident?i=skb">skb</a>-&gt;inner_protocol;
<a name="L156" href="source/net/ipv4/udp_offload.c#L156">156</a>                 gso_inner_segment = <a href="ident?i=skb_mac_gso_segment">skb_mac_gso_segment</a>;
<a name="L157" href="source/net/ipv4/udp_offload.c#L157">157</a>                 break;
<a name="L158" href="source/net/ipv4/udp_offload.c#L158">158</a>         case <a href="ident?i=ENCAP_TYPE_IPPROTO">ENCAP_TYPE_IPPROTO</a>:
<a name="L159" href="source/net/ipv4/udp_offload.c#L159">159</a>                 offloads = is_ipv6 ? <a href="ident?i=inet6_offloads">inet6_offloads</a> : <a href="ident?i=inet_offloads">inet_offloads</a>;
<a name="L160" href="source/net/ipv4/udp_offload.c#L160">160</a>                 <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(offloads[<a href="ident?i=skb">skb</a>-&gt;inner_ipproto]);
<a name="L161" href="source/net/ipv4/udp_offload.c#L161">161</a>                 if (!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gso_segment)
<a name="L162" href="source/net/ipv4/udp_offload.c#L162">162</a>                         goto out_unlock;
<a name="L163" href="source/net/ipv4/udp_offload.c#L163">163</a>                 gso_inner_segment = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gso_segment;
<a name="L164" href="source/net/ipv4/udp_offload.c#L164">164</a>                 break;
<a name="L165" href="source/net/ipv4/udp_offload.c#L165">165</a>         default:
<a name="L166" href="source/net/ipv4/udp_offload.c#L166">166</a>                 goto out_unlock;
<a name="L167" href="source/net/ipv4/udp_offload.c#L167">167</a>         }
<a name="L168" href="source/net/ipv4/udp_offload.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/udp_offload.c#L169">169</a>         segs = <a href="ident?i=__skb_udp_tunnel_segment">__skb_udp_tunnel_segment</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a>, gso_inner_segment,
<a name="L170" href="source/net/ipv4/udp_offload.c#L170">170</a>                                         <a href="ident?i=protocol">protocol</a>, is_ipv6);
<a name="L171" href="source/net/ipv4/udp_offload.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/udp_offload.c#L172">172</a> out_unlock:
<a name="L173" href="source/net/ipv4/udp_offload.c#L173">173</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L174" href="source/net/ipv4/udp_offload.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/udp_offload.c#L175">175</a>         return segs;
<a name="L176" href="source/net/ipv4/udp_offload.c#L176">176</a> }
<a name="L177" href="source/net/ipv4/udp_offload.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/udp_offload.c#L178">178</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=udp4_ufo_fragment">udp4_ufo_fragment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L179" href="source/net/ipv4/udp_offload.c#L179">179</a>                                          <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>)
<a name="L180" href="source/net/ipv4/udp_offload.c#L180">180</a> {
<a name="L181" href="source/net/ipv4/udp_offload.c#L181">181</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *segs = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L182" href="source/net/ipv4/udp_offload.c#L182">182</a>         unsigned int mss;
<a name="L183" href="source/net/ipv4/udp_offload.c#L183">183</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a>;
<a name="L184" href="source/net/ipv4/udp_offload.c#L184">184</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh;
<a name="L185" href="source/net/ipv4/udp_offload.c#L185">185</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L186" href="source/net/ipv4/udp_offload.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/udp_offload.c#L187">187</a>         if (<a href="ident?i=skb">skb</a>-&gt;encapsulation &amp;&amp;
<a name="L188" href="source/net/ipv4/udp_offload.c#L188">188</a>             (<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type &amp;
<a name="L189" href="source/net/ipv4/udp_offload.c#L189">189</a>              (SKB_GSO_UDP_TUNNEL|SKB_GSO_UDP_TUNNEL_CSUM))) {
<a name="L190" href="source/net/ipv4/udp_offload.c#L190">190</a>                 segs = <a href="ident?i=skb_udp_tunnel_segment">skb_udp_tunnel_segment</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a>, <a href="ident?i=false">false</a>);
<a name="L191" href="source/net/ipv4/udp_offload.c#L191">191</a>                 goto <a href="ident?i=out">out</a>;
<a name="L192" href="source/net/ipv4/udp_offload.c#L192">192</a>         }
<a name="L193" href="source/net/ipv4/udp_offload.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/udp_offload.c#L194">194</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>)))
<a name="L195" href="source/net/ipv4/udp_offload.c#L195">195</a>                 goto <a href="ident?i=out">out</a>;
<a name="L196" href="source/net/ipv4/udp_offload.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/udp_offload.c#L197">197</a>         mss = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_size;
<a name="L198" href="source/net/ipv4/udp_offload.c#L198">198</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= mss))
<a name="L199" href="source/net/ipv4/udp_offload.c#L199">199</a>                 goto <a href="ident?i=out">out</a>;
<a name="L200" href="source/net/ipv4/udp_offload.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/udp_offload.c#L201">201</a>         if (<a href="ident?i=skb_gso_ok">skb_gso_ok</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a> | <a href="ident?i=NETIF_F_GSO_ROBUST">NETIF_F_GSO_ROBUST</a>)) {
<a name="L202" href="source/net/ipv4/udp_offload.c#L202">202</a>                 <b><i>/* Packet is from an untrusted source, reset gso_segs. */</i></b>
<a name="L203" href="source/net/ipv4/udp_offload.c#L203">203</a>                 int <a href="ident?i=type">type</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type;
<a name="L204" href="source/net/ipv4/udp_offload.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/udp_offload.c#L205">205</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=type">type</a> &amp; ~(SKB_GSO_UDP | SKB_GSO_DODGY |
<a name="L206" href="source/net/ipv4/udp_offload.c#L206">206</a>                                       SKB_GSO_UDP_TUNNEL |
<a name="L207" href="source/net/ipv4/udp_offload.c#L207">207</a>                                       SKB_GSO_UDP_TUNNEL_CSUM |
<a name="L208" href="source/net/ipv4/udp_offload.c#L208">208</a>                                       SKB_GSO_TUNNEL_REMCSUM |
<a name="L209" href="source/net/ipv4/udp_offload.c#L209">209</a>                                       SKB_GSO_IPIP |
<a name="L210" href="source/net/ipv4/udp_offload.c#L210">210</a>                                       SKB_GSO_GRE | SKB_GSO_GRE_CSUM) ||
<a name="L211" href="source/net/ipv4/udp_offload.c#L211">211</a>                              !(<a href="ident?i=type">type</a> &amp; (SKB_GSO_UDP))))
<a name="L212" href="source/net/ipv4/udp_offload.c#L212">212</a>                         goto <a href="ident?i=out">out</a>;
<a name="L213" href="source/net/ipv4/udp_offload.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/udp_offload.c#L214">214</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs = <a href="ident?i=DIV_ROUND_UP">DIV_ROUND_UP</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, mss);
<a name="L215" href="source/net/ipv4/udp_offload.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/udp_offload.c#L216">216</a>                 segs = <a href="ident?i=NULL">NULL</a>;
<a name="L217" href="source/net/ipv4/udp_offload.c#L217">217</a>                 goto <a href="ident?i=out">out</a>;
<a name="L218" href="source/net/ipv4/udp_offload.c#L218">218</a>         }
<a name="L219" href="source/net/ipv4/udp_offload.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/udp_offload.c#L220">220</a>         <b><i>/* Do software UFO. Complete and fill in the UDP checksum as</i></b>
<a name="L221" href="source/net/ipv4/udp_offload.c#L221">221</a> <b><i>         * HW cannot do checksum of UDP packets sent as multiple</i></b>
<a name="L222" href="source/net/ipv4/udp_offload.c#L222">222</a> <b><i>         * IP fragments.</i></b>
<a name="L223" href="source/net/ipv4/udp_offload.c#L223">223</a> <b><i>         */</i></b>
<a name="L224" href="source/net/ipv4/udp_offload.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/udp_offload.c#L225">225</a>         uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L226" href="source/net/ipv4/udp_offload.c#L226">226</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L227" href="source/net/ipv4/udp_offload.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/udp_offload.c#L228">228</a>         uh-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L229" href="source/net/ipv4/udp_offload.c#L229">229</a>         <a href="ident?i=csum">csum</a> = <a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, 0);
<a name="L230" href="source/net/ipv4/udp_offload.c#L230">230</a>         uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=udp_v4_check">udp_v4_check</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=csum">csum</a>);
<a name="L231" href="source/net/ipv4/udp_offload.c#L231">231</a>         if (uh-&gt;<a href="ident?i=check">check</a> == 0)
<a name="L232" href="source/net/ipv4/udp_offload.c#L232">232</a>                 uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L233" href="source/net/ipv4/udp_offload.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/udp_offload.c#L234">234</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L235" href="source/net/ipv4/udp_offload.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/udp_offload.c#L236">236</a>         <b><i>/* Fragment the skb. IP headers of the fragments are updated in</i></b>
<a name="L237" href="source/net/ipv4/udp_offload.c#L237">237</a> <b><i>         * inet_gso_segment()</i></b>
<a name="L238" href="source/net/ipv4/udp_offload.c#L238">238</a> <b><i>         */</i></b>
<a name="L239" href="source/net/ipv4/udp_offload.c#L239">239</a>         segs = <a href="ident?i=skb_segment">skb_segment</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a>);
<a name="L240" href="source/net/ipv4/udp_offload.c#L240">240</a> <a href="ident?i=out">out</a>:
<a name="L241" href="source/net/ipv4/udp_offload.c#L241">241</a>         return segs;
<a name="L242" href="source/net/ipv4/udp_offload.c#L242">242</a> }
<a name="L243" href="source/net/ipv4/udp_offload.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/udp_offload.c#L244">244</a> int <a href="ident?i=udp_add_offload">udp_add_offload</a>(struct <a href="ident?i=udp_offload">udp_offload</a> *uo)
<a name="L245" href="source/net/ipv4/udp_offload.c#L245">245</a> {
<a name="L246" href="source/net/ipv4/udp_offload.c#L246">246</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> *new_offload = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*new_offload), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L247" href="source/net/ipv4/udp_offload.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/udp_offload.c#L248">248</a>         if (!new_offload)
<a name="L249" href="source/net/ipv4/udp_offload.c#L249">249</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L250" href="source/net/ipv4/udp_offload.c#L250">250</a> 
<a name="L251" href="source/net/ipv4/udp_offload.c#L251">251</a>         new_offload-&gt;offload = uo;
<a name="L252" href="source/net/ipv4/udp_offload.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/udp_offload.c#L253">253</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;udp_offload_lock);
<a name="L254" href="source/net/ipv4/udp_offload.c#L254">254</a>         new_offload-&gt;<a href="ident?i=next">next</a> = udp_offload_base;
<a name="L255" href="source/net/ipv4/udp_offload.c#L255">255</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(udp_offload_base, new_offload);
<a name="L256" href="source/net/ipv4/udp_offload.c#L256">256</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;udp_offload_lock);
<a name="L257" href="source/net/ipv4/udp_offload.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/udp_offload.c#L258">258</a>         return 0;
<a name="L259" href="source/net/ipv4/udp_offload.c#L259">259</a> }
<a name="L260" href="source/net/ipv4/udp_offload.c#L260">260</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_add_offload">udp_add_offload</a>);
<a name="L261" href="source/net/ipv4/udp_offload.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/udp_offload.c#L262">262</a> static void <a href="ident?i=udp_offload_free_routine">udp_offload_free_routine</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L263" href="source/net/ipv4/udp_offload.c#L263">263</a> {
<a name="L264" href="source/net/ipv4/udp_offload.c#L264">264</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> *ou_priv = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a>, rcu);
<a name="L265" href="source/net/ipv4/udp_offload.c#L265">265</a>         <a href="ident?i=kfree">kfree</a>(ou_priv);
<a name="L266" href="source/net/ipv4/udp_offload.c#L266">266</a> }
<a name="L267" href="source/net/ipv4/udp_offload.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/udp_offload.c#L268">268</a> void <a href="ident?i=udp_del_offload">udp_del_offload</a>(struct <a href="ident?i=udp_offload">udp_offload</a> *uo)
<a name="L269" href="source/net/ipv4/udp_offload.c#L269">269</a> {
<a name="L270" href="source/net/ipv4/udp_offload.c#L270">270</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=head">head</a> = &amp;udp_offload_base;
<a name="L271" href="source/net/ipv4/udp_offload.c#L271">271</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> *uo_priv;
<a name="L272" href="source/net/ipv4/udp_offload.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/udp_offload.c#L273">273</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;udp_offload_lock);
<a name="L274" href="source/net/ipv4/udp_offload.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/udp_offload.c#L275">275</a>         uo_priv = <a href="ident?i=udp_deref_protected">udp_deref_protected</a>(*<a href="ident?i=head">head</a>);
<a name="L276" href="source/net/ipv4/udp_offload.c#L276">276</a>         for (; uo_priv != <a href="ident?i=NULL">NULL</a>;
<a name="L277" href="source/net/ipv4/udp_offload.c#L277">277</a>              uo_priv = <a href="ident?i=udp_deref_protected">udp_deref_protected</a>(*<a href="ident?i=head">head</a>)) {
<a name="L278" href="source/net/ipv4/udp_offload.c#L278">278</a>                 if (uo_priv-&gt;offload == uo) {
<a name="L279" href="source/net/ipv4/udp_offload.c#L279">279</a>                         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(*<a href="ident?i=head">head</a>,
<a name="L280" href="source/net/ipv4/udp_offload.c#L280">280</a>                                            <a href="ident?i=udp_deref_protected">udp_deref_protected</a>(uo_priv-&gt;<a href="ident?i=next">next</a>));
<a name="L281" href="source/net/ipv4/udp_offload.c#L281">281</a>                         goto unlock;
<a name="L282" href="source/net/ipv4/udp_offload.c#L282">282</a>                 }
<a name="L283" href="source/net/ipv4/udp_offload.c#L283">283</a>                 <a href="ident?i=head">head</a> = &amp;uo_priv-&gt;<a href="ident?i=next">next</a>;
<a name="L284" href="source/net/ipv4/udp_offload.c#L284">284</a>         }
<a name="L285" href="source/net/ipv4/udp_offload.c#L285">285</a>         <a href="ident?i=pr_warn">pr_warn</a>(<i>"udp_del_offload: didn't find offload for port %d\n"</i>, <a href="ident?i=ntohs">ntohs</a>(uo-&gt;<a href="ident?i=port">port</a>));
<a name="L286" href="source/net/ipv4/udp_offload.c#L286">286</a> unlock:
<a name="L287" href="source/net/ipv4/udp_offload.c#L287">287</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;udp_offload_lock);
<a name="L288" href="source/net/ipv4/udp_offload.c#L288">288</a>         if (uo_priv)
<a name="L289" href="source/net/ipv4/udp_offload.c#L289">289</a>                 <a href="ident?i=call_rcu">call_rcu</a>(&amp;uo_priv-&gt;rcu, <a href="ident?i=udp_offload_free_routine">udp_offload_free_routine</a>);
<a name="L290" href="source/net/ipv4/udp_offload.c#L290">290</a> }
<a name="L291" href="source/net/ipv4/udp_offload.c#L291">291</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_del_offload">udp_del_offload</a>);
<a name="L292" href="source/net/ipv4/udp_offload.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/udp_offload.c#L293">293</a> struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=udp_gro_receive">udp_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L294" href="source/net/ipv4/udp_offload.c#L294">294</a>                                  struct <a href="ident?i=udphdr">udphdr</a> *uh)
<a name="L295" href="source/net/ipv4/udp_offload.c#L295">295</a> {
<a name="L296" href="source/net/ipv4/udp_offload.c#L296">296</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> *uo_priv;
<a name="L297" href="source/net/ipv4/udp_offload.c#L297">297</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=p">p</a>, **pp = <a href="ident?i=NULL">NULL</a>;
<a name="L298" href="source/net/ipv4/udp_offload.c#L298">298</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh2;
<a name="L299" href="source/net/ipv4/udp_offload.c#L299">299</a>         unsigned int <a href="ident?i=off">off</a> = <a href="ident?i=skb_gro_offset">skb_gro_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L300" href="source/net/ipv4/udp_offload.c#L300">300</a>         int <a href="ident?i=flush">flush</a> = 1;
<a name="L301" href="source/net/ipv4/udp_offload.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/udp_offload.c#L302">302</a>         if (<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;udp_mark ||
<a name="L303" href="source/net/ipv4/udp_offload.c#L303">303</a>             (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a> &amp;&amp;
<a name="L304" href="source/net/ipv4/udp_offload.c#L304">304</a>              <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;csum_cnt == 0 &amp;&amp;
<a name="L305" href="source/net/ipv4/udp_offload.c#L305">305</a>              !<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;csum_valid))
<a name="L306" href="source/net/ipv4/udp_offload.c#L306">306</a>                 goto <a href="ident?i=out">out</a>;
<a name="L307" href="source/net/ipv4/udp_offload.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/udp_offload.c#L308">308</a>         <b><i>/* mark that this skb passed once through the udp gro layer */</i></b>
<a name="L309" href="source/net/ipv4/udp_offload.c#L309">309</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;udp_mark = 1;
<a name="L310" href="source/net/ipv4/udp_offload.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/udp_offload.c#L311">311</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L312" href="source/net/ipv4/udp_offload.c#L312">312</a>         uo_priv = <a href="ident?i=rcu_dereference">rcu_dereference</a>(udp_offload_base);
<a name="L313" href="source/net/ipv4/udp_offload.c#L313">313</a>         for (; uo_priv != <a href="ident?i=NULL">NULL</a>; uo_priv = <a href="ident?i=rcu_dereference">rcu_dereference</a>(uo_priv-&gt;<a href="ident?i=next">next</a>)) {
<a name="L314" href="source/net/ipv4/udp_offload.c#L314">314</a>                 if (uo_priv-&gt;offload-&gt;<a href="ident?i=port">port</a> == uh-&gt;<a href="ident?i=dest">dest</a> &amp;&amp;
<a name="L315" href="source/net/ipv4/udp_offload.c#L315">315</a>                     uo_priv-&gt;offload-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive)
<a name="L316" href="source/net/ipv4/udp_offload.c#L316">316</a>                         goto unflush;
<a name="L317" href="source/net/ipv4/udp_offload.c#L317">317</a>         }
<a name="L318" href="source/net/ipv4/udp_offload.c#L318">318</a>         goto out_unlock;
<a name="L319" href="source/net/ipv4/udp_offload.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/udp_offload.c#L320">320</a> unflush:
<a name="L321" href="source/net/ipv4/udp_offload.c#L321">321</a>         <a href="ident?i=flush">flush</a> = 0;
<a name="L322" href="source/net/ipv4/udp_offload.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/udp_offload.c#L323">323</a>         for (<a href="ident?i=p">p</a> = *<a href="ident?i=head">head</a>; <a href="ident?i=p">p</a>; <a href="ident?i=p">p</a> = <a href="ident?i=p">p</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L324" href="source/net/ipv4/udp_offload.c#L324">324</a>                 if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow)
<a name="L325" href="source/net/ipv4/udp_offload.c#L325">325</a>                         continue;
<a name="L326" href="source/net/ipv4/udp_offload.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/udp_offload.c#L327">327</a>                 uh2 = (struct <a href="ident?i=udphdr">udphdr</a>   *)(<a href="ident?i=p">p</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=off">off</a>);
<a name="L328" href="source/net/ipv4/udp_offload.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/udp_offload.c#L329">329</a>                 <b><i>/* Match ports and either checksums are either both zero</i></b>
<a name="L330" href="source/net/ipv4/udp_offload.c#L330">330</a> <b><i>                 * or nonzero.</i></b>
<a name="L331" href="source/net/ipv4/udp_offload.c#L331">331</a> <b><i>                 */</i></b>
<a name="L332" href="source/net/ipv4/udp_offload.c#L332">332</a>                 if ((*(<a href="ident?i=u32">u32</a> *)&amp;uh-&gt;source != *(<a href="ident?i=u32">u32</a> *)&amp;uh2-&gt;source) ||
<a name="L333" href="source/net/ipv4/udp_offload.c#L333">333</a>                     (!uh-&gt;<a href="ident?i=check">check</a> ^ !uh2-&gt;<a href="ident?i=check">check</a>)) {
<a name="L334" href="source/net/ipv4/udp_offload.c#L334">334</a>                         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow = 0;
<a name="L335" href="source/net/ipv4/udp_offload.c#L335">335</a>                         continue;
<a name="L336" href="source/net/ipv4/udp_offload.c#L336">336</a>                 }
<a name="L337" href="source/net/ipv4/udp_offload.c#L337">337</a>         }
<a name="L338" href="source/net/ipv4/udp_offload.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/udp_offload.c#L339">339</a>         <a href="ident?i=skb_gro_pull">skb_gro_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>)); <b><i>/* pull encapsulating udp header */</i></b>
<a name="L340" href="source/net/ipv4/udp_offload.c#L340">340</a>         <a href="ident?i=skb_gro_postpull_rcsum">skb_gro_postpull_rcsum</a>(<a href="ident?i=skb">skb</a>, uh, sizeof(struct <a href="ident?i=udphdr">udphdr</a>));
<a name="L341" href="source/net/ipv4/udp_offload.c#L341">341</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=proto">proto</a> = uo_priv-&gt;offload-&gt;ipproto;
<a name="L342" href="source/net/ipv4/udp_offload.c#L342">342</a>         pp = uo_priv-&gt;offload-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>,
<a name="L343" href="source/net/ipv4/udp_offload.c#L343">343</a>                                                      uo_priv-&gt;offload);
<a name="L344" href="source/net/ipv4/udp_offload.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/udp_offload.c#L345">345</a> out_unlock:
<a name="L346" href="source/net/ipv4/udp_offload.c#L346">346</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L347" href="source/net/ipv4/udp_offload.c#L347">347</a> <a href="ident?i=out">out</a>:
<a name="L348" href="source/net/ipv4/udp_offload.c#L348">348</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> |= <a href="ident?i=flush">flush</a>;
<a name="L349" href="source/net/ipv4/udp_offload.c#L349">349</a>         return pp;
<a name="L350" href="source/net/ipv4/udp_offload.c#L350">350</a> }
<a name="L351" href="source/net/ipv4/udp_offload.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/udp_offload.c#L352">352</a> static struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=udp4_gro_receive">udp4_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>,
<a name="L353" href="source/net/ipv4/udp_offload.c#L353">353</a>                                          struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L354" href="source/net/ipv4/udp_offload.c#L354">354</a> {
<a name="L355" href="source/net/ipv4/udp_offload.c#L355">355</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh = <a href="ident?i=udp_gro_udphdr">udp_gro_udphdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L356" href="source/net/ipv4/udp_offload.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/udp_offload.c#L357">357</a>         if (<a href="ident?i=unlikely">unlikely</a>(!uh))
<a name="L358" href="source/net/ipv4/udp_offload.c#L358">358</a>                 goto <a href="ident?i=flush">flush</a>;
<a name="L359" href="source/net/ipv4/udp_offload.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/udp_offload.c#L360">360</a>         <b><i>/* Don't bother verifying checksum if we're going to flush anyway. */</i></b>
<a name="L361" href="source/net/ipv4/udp_offload.c#L361">361</a>         if (<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a>)
<a name="L362" href="source/net/ipv4/udp_offload.c#L362">362</a>                 goto <a href="ident?i=skip">skip</a>;
<a name="L363" href="source/net/ipv4/udp_offload.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/udp_offload.c#L364">364</a>         if (<a href="ident?i=skb_gro_checksum_validate_zero_check">skb_gro_checksum_validate_zero_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>, uh-&gt;<a href="ident?i=check">check</a>,
<a name="L365" href="source/net/ipv4/udp_offload.c#L365">365</a>                                                  <a href="ident?i=inet_gro_compute_pseudo">inet_gro_compute_pseudo</a>))
<a name="L366" href="source/net/ipv4/udp_offload.c#L366">366</a>                 goto <a href="ident?i=flush">flush</a>;
<a name="L367" href="source/net/ipv4/udp_offload.c#L367">367</a>         else if (uh-&gt;<a href="ident?i=check">check</a>)
<a name="L368" href="source/net/ipv4/udp_offload.c#L368">368</a>                 <a href="ident?i=skb_gro_checksum_try_convert">skb_gro_checksum_try_convert</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>, uh-&gt;<a href="ident?i=check">check</a>,
<a name="L369" href="source/net/ipv4/udp_offload.c#L369">369</a>                                              <a href="ident?i=inet_gro_compute_pseudo">inet_gro_compute_pseudo</a>);
<a name="L370" href="source/net/ipv4/udp_offload.c#L370">370</a> <a href="ident?i=skip">skip</a>:
<a name="L371" href="source/net/ipv4/udp_offload.c#L371">371</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;is_ipv6 = 0;
<a name="L372" href="source/net/ipv4/udp_offload.c#L372">372</a>         return <a href="ident?i=udp_gro_receive">udp_gro_receive</a>(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>, uh);
<a name="L373" href="source/net/ipv4/udp_offload.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/udp_offload.c#L374">374</a> <a href="ident?i=flush">flush</a>:
<a name="L375" href="source/net/ipv4/udp_offload.c#L375">375</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> = 1;
<a name="L376" href="source/net/ipv4/udp_offload.c#L376">376</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L377" href="source/net/ipv4/udp_offload.c#L377">377</a> }
<a name="L378" href="source/net/ipv4/udp_offload.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/udp_offload.c#L379">379</a> int <a href="ident?i=udp_gro_complete">udp_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nhoff)
<a name="L380" href="source/net/ipv4/udp_offload.c#L380">380</a> {
<a name="L381" href="source/net/ipv4/udp_offload.c#L381">381</a>         struct <a href="ident?i=udp_offload_priv">udp_offload_priv</a> *uo_priv;
<a name="L382" href="source/net/ipv4/udp_offload.c#L382">382</a>         <a href="ident?i=__be16">__be16</a> newlen = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - nhoff);
<a name="L383" href="source/net/ipv4/udp_offload.c#L383">383</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh = (struct <a href="ident?i=udphdr">udphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + nhoff);
<a name="L384" href="source/net/ipv4/udp_offload.c#L384">384</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOSYS">ENOSYS</a>;
<a name="L385" href="source/net/ipv4/udp_offload.c#L385">385</a> 
<a name="L386" href="source/net/ipv4/udp_offload.c#L386">386</a>         uh-&gt;<a href="ident?i=len">len</a> = newlen;
<a name="L387" href="source/net/ipv4/udp_offload.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/udp_offload.c#L388">388</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L389" href="source/net/ipv4/udp_offload.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/udp_offload.c#L390">390</a>         uo_priv = <a href="ident?i=rcu_dereference">rcu_dereference</a>(udp_offload_base);
<a name="L391" href="source/net/ipv4/udp_offload.c#L391">391</a>         for (; uo_priv != <a href="ident?i=NULL">NULL</a>; uo_priv = <a href="ident?i=rcu_dereference">rcu_dereference</a>(uo_priv-&gt;<a href="ident?i=next">next</a>)) {
<a name="L392" href="source/net/ipv4/udp_offload.c#L392">392</a>                 if (uo_priv-&gt;offload-&gt;<a href="ident?i=port">port</a> == uh-&gt;<a href="ident?i=dest">dest</a> &amp;&amp;
<a name="L393" href="source/net/ipv4/udp_offload.c#L393">393</a>                     uo_priv-&gt;offload-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete)
<a name="L394" href="source/net/ipv4/udp_offload.c#L394">394</a>                         break;
<a name="L395" href="source/net/ipv4/udp_offload.c#L395">395</a>         }
<a name="L396" href="source/net/ipv4/udp_offload.c#L396">396</a> 
<a name="L397" href="source/net/ipv4/udp_offload.c#L397">397</a>         if (uo_priv) {
<a name="L398" href="source/net/ipv4/udp_offload.c#L398">398</a>                 <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=proto">proto</a> = uo_priv-&gt;offload-&gt;ipproto;
<a name="L399" href="source/net/ipv4/udp_offload.c#L399">399</a>                 <a href="ident?i=err">err</a> = uo_priv-&gt;offload-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete(<a href="ident?i=skb">skb</a>,
<a name="L400" href="source/net/ipv4/udp_offload.c#L400">400</a>                                 nhoff + sizeof(struct <a href="ident?i=udphdr">udphdr</a>),
<a name="L401" href="source/net/ipv4/udp_offload.c#L401">401</a>                                 uo_priv-&gt;offload);
<a name="L402" href="source/net/ipv4/udp_offload.c#L402">402</a>         }
<a name="L403" href="source/net/ipv4/udp_offload.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/udp_offload.c#L404">404</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L405" href="source/net/ipv4/udp_offload.c#L405">405</a> 
<a name="L406" href="source/net/ipv4/udp_offload.c#L406">406</a>         if (<a href="ident?i=skb">skb</a>-&gt;remcsum_offload)
<a name="L407" href="source/net/ipv4/udp_offload.c#L407">407</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= SKB_GSO_TUNNEL_REMCSUM;
<a name="L408" href="source/net/ipv4/udp_offload.c#L408">408</a> 
<a name="L409" href="source/net/ipv4/udp_offload.c#L409">409</a>         <a href="ident?i=skb">skb</a>-&gt;encapsulation = 1;
<a name="L410" href="source/net/ipv4/udp_offload.c#L410">410</a>         <a href="ident?i=skb_set_inner_mac_header">skb_set_inner_mac_header</a>(<a href="ident?i=skb">skb</a>, nhoff + sizeof(struct <a href="ident?i=udphdr">udphdr</a>));
<a name="L411" href="source/net/ipv4/udp_offload.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/udp_offload.c#L412">412</a>         return <a href="ident?i=err">err</a>;
<a name="L413" href="source/net/ipv4/udp_offload.c#L413">413</a> }
<a name="L414" href="source/net/ipv4/udp_offload.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/udp_offload.c#L415">415</a> static int <a href="ident?i=udp4_gro_complete">udp4_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nhoff)
<a name="L416" href="source/net/ipv4/udp_offload.c#L416">416</a> {
<a name="L417" href="source/net/ipv4/udp_offload.c#L417">417</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L418" href="source/net/ipv4/udp_offload.c#L418">418</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh = (struct <a href="ident?i=udphdr">udphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + nhoff);
<a name="L419" href="source/net/ipv4/udp_offload.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/udp_offload.c#L420">420</a>         if (uh-&gt;<a href="ident?i=check">check</a>) {
<a name="L421" href="source/net/ipv4/udp_offload.c#L421">421</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;
<a name="L422" href="source/net/ipv4/udp_offload.c#L422">422</a>                 uh-&gt;<a href="ident?i=check">check</a> = ~udp_v4_check(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - nhoff, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L423" href="source/net/ipv4/udp_offload.c#L423">423</a>                                           iph-&gt;<a href="ident?i=daddr">daddr</a>, 0);
<a name="L424" href="source/net/ipv4/udp_offload.c#L424">424</a>         } else {
<a name="L425" href="source/net/ipv4/udp_offload.c#L425">425</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= SKB_GSO_UDP_TUNNEL;
<a name="L426" href="source/net/ipv4/udp_offload.c#L426">426</a>         }
<a name="L427" href="source/net/ipv4/udp_offload.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/udp_offload.c#L428">428</a>         return <a href="ident?i=udp_gro_complete">udp_gro_complete</a>(<a href="ident?i=skb">skb</a>, nhoff);
<a name="L429" href="source/net/ipv4/udp_offload.c#L429">429</a> }
<a name="L430" href="source/net/ipv4/udp_offload.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/udp_offload.c#L431">431</a> static const struct <a href="ident?i=net_offload">net_offload</a> <a href="ident?i=udpv4_offload">udpv4_offload</a> = {
<a name="L432" href="source/net/ipv4/udp_offload.c#L432">432</a>         .<a href="ident?i=callbacks">callbacks</a> = {
<a name="L433" href="source/net/ipv4/udp_offload.c#L433">433</a>                 .gso_segment = <a href="ident?i=udp4_ufo_fragment">udp4_ufo_fragment</a>,
<a name="L434" href="source/net/ipv4/udp_offload.c#L434">434</a>                 .gro_receive  = <a href="ident?i=udp4_gro_receive">udp4_gro_receive</a>,
<a name="L435" href="source/net/ipv4/udp_offload.c#L435">435</a>                 .gro_complete = <a href="ident?i=udp4_gro_complete">udp4_gro_complete</a>,
<a name="L436" href="source/net/ipv4/udp_offload.c#L436">436</a>         },
<a name="L437" href="source/net/ipv4/udp_offload.c#L437">437</a> };
<a name="L438" href="source/net/ipv4/udp_offload.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/udp_offload.c#L439">439</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=udpv4_offload_init">udpv4_offload_init</a>(void)
<a name="L440" href="source/net/ipv4/udp_offload.c#L440">440</a> {
<a name="L441" href="source/net/ipv4/udp_offload.c#L441">441</a>         return <a href="ident?i=inet_add_offload">inet_add_offload</a>(&amp;<a href="ident?i=udpv4_offload">udpv4_offload</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>);
<a name="L442" href="source/net/ipv4/udp_offload.c#L442">442</a> }
<a name="L443" href="source/net/ipv4/udp_offload.c#L443">443</a> </pre></div><p>
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
