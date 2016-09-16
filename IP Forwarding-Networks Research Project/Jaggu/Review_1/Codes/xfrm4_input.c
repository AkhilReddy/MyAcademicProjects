<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_input.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_input.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_input.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_input.c">xfrm4_input.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_input.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_input.c#L2">2</a> <b><i> * xfrm4_input.c</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_input.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_input.c#L4">4</a> <b><i> * Changes:</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_input.c#L5">5</a> <b><i> *      YOSHIFUJI Hideaki @USAGI</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_input.c#L6">6</a> <b><i> *              Split up af-specific portion</i></b>
  <a name="L7" href="source/net/ipv4/xfrm4_input.c#L7">7</a> <b><i> *      Derek Atkins &lt;derek@ihtfp.com&gt;</i></b>
  <a name="L8" href="source/net/ipv4/xfrm4_input.c#L8">8</a> <b><i> *              Add Encapsulation support</i></b>
  <a name="L9" href="source/net/ipv4/xfrm4_input.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/xfrm4_input.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/xfrm4_input.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/xfrm4_input.c#L12">12</a> #include &lt;linux/slab.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_input.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_input.c#L14">14</a> #include &lt;linux/string.h&gt;
 <a name="L15" href="source/net/ipv4/xfrm4_input.c#L15">15</a> #include &lt;linux/netfilter.h&gt;
 <a name="L16" href="source/net/ipv4/xfrm4_input.c#L16">16</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L17" href="source/net/ipv4/xfrm4_input.c#L17">17</a> #include &lt;net/ip.h&gt;
 <a name="L18" href="source/net/ipv4/xfrm4_input.c#L18">18</a> #include &lt;net/xfrm.h&gt;
 <a name="L19" href="source/net/ipv4/xfrm4_input.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/xfrm4_input.c#L20">20</a> int <a href="ident?i=xfrm4_extract_input">xfrm4_extract_input</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L21" href="source/net/ipv4/xfrm4_input.c#L21">21</a> {
 <a name="L22" href="source/net/ipv4/xfrm4_input.c#L22">22</a>         return <a href="ident?i=xfrm4_extract_header">xfrm4_extract_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L23" href="source/net/ipv4/xfrm4_input.c#L23">23</a> }
 <a name="L24" href="source/net/ipv4/xfrm4_input.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/xfrm4_input.c#L25">25</a> static inline int <a href="ident?i=xfrm4_rcv_encap_finish">xfrm4_rcv_encap_finish</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L26" href="source/net/ipv4/xfrm4_input.c#L26">26</a> {
 <a name="L27" href="source/net/ipv4/xfrm4_input.c#L27">27</a>         if (!<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)) {
 <a name="L28" href="source/net/ipv4/xfrm4_input.c#L28">28</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L29" href="source/net/ipv4/xfrm4_input.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/xfrm4_input.c#L30">30</a>                 if (<a href="ident?i=ip_route_input_noref">ip_route_input_noref</a>(<a href="ident?i=skb">skb</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
 <a name="L31" href="source/net/ipv4/xfrm4_input.c#L31">31</a>                                          iph-&gt;tos, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>))
 <a name="L32" href="source/net/ipv4/xfrm4_input.c#L32">32</a>                         goto <a href="ident?i=drop">drop</a>;
 <a name="L33" href="source/net/ipv4/xfrm4_input.c#L33">33</a>         }
 <a name="L34" href="source/net/ipv4/xfrm4_input.c#L34">34</a>         return <a href="ident?i=dst_input">dst_input</a>(<a href="ident?i=skb">skb</a>);
 <a name="L35" href="source/net/ipv4/xfrm4_input.c#L35">35</a> <a href="ident?i=drop">drop</a>:
 <a name="L36" href="source/net/ipv4/xfrm4_input.c#L36">36</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
 <a name="L37" href="source/net/ipv4/xfrm4_input.c#L37">37</a>         return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
 <a name="L38" href="source/net/ipv4/xfrm4_input.c#L38">38</a> }
 <a name="L39" href="source/net/ipv4/xfrm4_input.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/xfrm4_input.c#L40">40</a> int <a href="ident?i=xfrm4_transport_finish">xfrm4_transport_finish</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=async">async</a>)
 <a name="L41" href="source/net/ipv4/xfrm4_input.c#L41">41</a> {
 <a name="L42" href="source/net/ipv4/xfrm4_input.c#L42">42</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L43" href="source/net/ipv4/xfrm4_input.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/xfrm4_input.c#L44">44</a>         iph-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L45" href="source/net/ipv4/xfrm4_input.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/xfrm4_input.c#L46">46</a> #ifndef CONFIG_NETFILTER
 <a name="L47" href="source/net/ipv4/xfrm4_input.c#L47">47</a>         if (!<a href="ident?i=async">async</a>)
 <a name="L48" href="source/net/ipv4/xfrm4_input.c#L48">48</a>                 return -iph-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L49" href="source/net/ipv4/xfrm4_input.c#L49">49</a> #endif
 <a name="L50" href="source/net/ipv4/xfrm4_input.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/xfrm4_input.c#L51">51</a>         <a href="ident?i=__skb_push">__skb_push</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> - <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>));
 <a name="L52" href="source/net/ipv4/xfrm4_input.c#L52">52</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
 <a name="L53" href="source/net/ipv4/xfrm4_input.c#L53">53</a>         <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
 <a name="L54" href="source/net/ipv4/xfrm4_input.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/xfrm4_input.c#L55">55</a>         <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_PRE_ROUTING, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
 <a name="L56" href="source/net/ipv4/xfrm4_input.c#L56">56</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=NULL">NULL</a>,
 <a name="L57" href="source/net/ipv4/xfrm4_input.c#L57">57</a>                 <a href="ident?i=xfrm4_rcv_encap_finish">xfrm4_rcv_encap_finish</a>);
 <a name="L58" href="source/net/ipv4/xfrm4_input.c#L58">58</a>         return 0;
 <a name="L59" href="source/net/ipv4/xfrm4_input.c#L59">59</a> }
 <a name="L60" href="source/net/ipv4/xfrm4_input.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/xfrm4_input.c#L61">61</a> <b><i>/* If it's a keepalive packet, then just eat it.</i></b>
 <a name="L62" href="source/net/ipv4/xfrm4_input.c#L62">62</a> <b><i> * If it's an encapsulated packet, then pass it to the</i></b>
 <a name="L63" href="source/net/ipv4/xfrm4_input.c#L63">63</a> <b><i> * IPsec xfrm input.</i></b>
 <a name="L64" href="source/net/ipv4/xfrm4_input.c#L64">64</a> <b><i> * Returns 0 if skb passed to xfrm or was dropped.</i></b>
 <a name="L65" href="source/net/ipv4/xfrm4_input.c#L65">65</a> <b><i> * Returns &gt;0 if skb should be passed to UDP.</i></b>
 <a name="L66" href="source/net/ipv4/xfrm4_input.c#L66">66</a> <b><i> * Returns &lt;0 if skb should be resubmitted (-ret is protocol)</i></b>
 <a name="L67" href="source/net/ipv4/xfrm4_input.c#L67">67</a> <b><i> */</i></b>
 <a name="L68" href="source/net/ipv4/xfrm4_input.c#L68">68</a> int <a href="ident?i=xfrm4_udp_encap_rcv">xfrm4_udp_encap_rcv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L69" href="source/net/ipv4/xfrm4_input.c#L69">69</a> {
 <a name="L70" href="source/net/ipv4/xfrm4_input.c#L70">70</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
 <a name="L71" href="source/net/ipv4/xfrm4_input.c#L71">71</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh;
 <a name="L72" href="source/net/ipv4/xfrm4_input.c#L72">72</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L73" href="source/net/ipv4/xfrm4_input.c#L73">73</a>         int iphlen, <a href="ident?i=len">len</a>;
 <a name="L74" href="source/net/ipv4/xfrm4_input.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/xfrm4_input.c#L75">75</a>         <a href="ident?i=__u8">__u8</a> *udpdata;
 <a name="L76" href="source/net/ipv4/xfrm4_input.c#L76">76</a>         <a href="ident?i=__be32">__be32</a> *udpdata32;
 <a name="L77" href="source/net/ipv4/xfrm4_input.c#L77">77</a>         <a href="ident?i=__u16">__u16</a> encap_type = <a href="ident?i=up">up</a>-&gt;encap_type;
 <a name="L78" href="source/net/ipv4/xfrm4_input.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/xfrm4_input.c#L79">79</a>         <b><i>/* if this is not encapsulated socket, then just return now */</i></b>
 <a name="L80" href="source/net/ipv4/xfrm4_input.c#L80">80</a>         if (!encap_type)
 <a name="L81" href="source/net/ipv4/xfrm4_input.c#L81">81</a>                 return 1;
 <a name="L82" href="source/net/ipv4/xfrm4_input.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/xfrm4_input.c#L83">83</a>         <b><i>/* If this is a paged skb, make sure we pull up</i></b>
 <a name="L84" href="source/net/ipv4/xfrm4_input.c#L84">84</a> <b><i>         * whatever data we need to look at. */</i></b>
 <a name="L85" href="source/net/ipv4/xfrm4_input.c#L85">85</a>         <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
 <a name="L86" href="source/net/ipv4/xfrm4_input.c#L86">86</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>) + <a href="ident?i=min">min</a>(<a href="ident?i=len">len</a>, 8)))
 <a name="L87" href="source/net/ipv4/xfrm4_input.c#L87">87</a>                 return 1;
 <a name="L88" href="source/net/ipv4/xfrm4_input.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/xfrm4_input.c#L89">89</a>         <b><i>/* Now we can get the pointers */</i></b>
 <a name="L90" href="source/net/ipv4/xfrm4_input.c#L90">90</a>         uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L91" href="source/net/ipv4/xfrm4_input.c#L91">91</a>         udpdata = (<a href="ident?i=__u8">__u8</a> *)uh + sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
 <a name="L92" href="source/net/ipv4/xfrm4_input.c#L92">92</a>         udpdata32 = (<a href="ident?i=__be32">__be32</a> *)udpdata;
 <a name="L93" href="source/net/ipv4/xfrm4_input.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/xfrm4_input.c#L94">94</a>         switch (encap_type) {
 <a name="L95" href="source/net/ipv4/xfrm4_input.c#L95">95</a>         default:
 <a name="L96" href="source/net/ipv4/xfrm4_input.c#L96">96</a>         case <a href="ident?i=UDP_ENCAP_ESPINUDP">UDP_ENCAP_ESPINUDP</a>:
 <a name="L97" href="source/net/ipv4/xfrm4_input.c#L97">97</a>                 <b><i>/* Check if this is a keepalive packet.  If so, eat it. */</i></b>
 <a name="L98" href="source/net/ipv4/xfrm4_input.c#L98">98</a>                 if (<a href="ident?i=len">len</a> == 1 &amp;&amp; udpdata[0] == 0xff) {
 <a name="L99" href="source/net/ipv4/xfrm4_input.c#L99">99</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L100" href="source/net/ipv4/xfrm4_input.c#L100">100</a>                 } else if (<a href="ident?i=len">len</a> &gt; sizeof(struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a>) &amp;&amp; udpdata32[0] != 0) {
<a name="L101" href="source/net/ipv4/xfrm4_input.c#L101">101</a>                         <b><i>/* ESP Packet without Non-ESP header */</i></b>
<a name="L102" href="source/net/ipv4/xfrm4_input.c#L102">102</a>                         <a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L103" href="source/net/ipv4/xfrm4_input.c#L103">103</a>                 } else
<a name="L104" href="source/net/ipv4/xfrm4_input.c#L104">104</a>                         <b><i>/* Must be an IKE packet.. pass it through */</i></b>
<a name="L105" href="source/net/ipv4/xfrm4_input.c#L105">105</a>                         return 1;
<a name="L106" href="source/net/ipv4/xfrm4_input.c#L106">106</a>                 break;
<a name="L107" href="source/net/ipv4/xfrm4_input.c#L107">107</a>         case <a href="ident?i=UDP_ENCAP_ESPINUDP_NON_IKE">UDP_ENCAP_ESPINUDP_NON_IKE</a>:
<a name="L108" href="source/net/ipv4/xfrm4_input.c#L108">108</a>                 <b><i>/* Check if this is a keepalive packet.  If so, eat it. */</i></b>
<a name="L109" href="source/net/ipv4/xfrm4_input.c#L109">109</a>                 if (<a href="ident?i=len">len</a> == 1 &amp;&amp; udpdata[0] == 0xff) {
<a name="L110" href="source/net/ipv4/xfrm4_input.c#L110">110</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L111" href="source/net/ipv4/xfrm4_input.c#L111">111</a>                 } else if (<a href="ident?i=len">len</a> &gt; 2 * sizeof(<a href="ident?i=u32">u32</a>) + sizeof(struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a>) &amp;&amp;
<a name="L112" href="source/net/ipv4/xfrm4_input.c#L112">112</a>                            udpdata32[0] == 0 &amp;&amp; udpdata32[1] == 0) {
<a name="L113" href="source/net/ipv4/xfrm4_input.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/xfrm4_input.c#L114">114</a>                         <b><i>/* ESP Packet with Non-IKE marker */</i></b>
<a name="L115" href="source/net/ipv4/xfrm4_input.c#L115">115</a>                         <a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=udphdr">udphdr</a>) + 2 * sizeof(<a href="ident?i=u32">u32</a>);
<a name="L116" href="source/net/ipv4/xfrm4_input.c#L116">116</a>                 } else
<a name="L117" href="source/net/ipv4/xfrm4_input.c#L117">117</a>                         <b><i>/* Must be an IKE packet.. pass it through */</i></b>
<a name="L118" href="source/net/ipv4/xfrm4_input.c#L118">118</a>                         return 1;
<a name="L119" href="source/net/ipv4/xfrm4_input.c#L119">119</a>                 break;
<a name="L120" href="source/net/ipv4/xfrm4_input.c#L120">120</a>         }
<a name="L121" href="source/net/ipv4/xfrm4_input.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/xfrm4_input.c#L122">122</a>         <b><i>/* At this point we are sure that this is an ESPinUDP packet,</i></b>
<a name="L123" href="source/net/ipv4/xfrm4_input.c#L123">123</a> <b><i>         * so we need to remove 'len' bytes from the packet (the UDP</i></b>
<a name="L124" href="source/net/ipv4/xfrm4_input.c#L124">124</a> <b><i>         * header and optional ESP marker bytes) and then modify the</i></b>
<a name="L125" href="source/net/ipv4/xfrm4_input.c#L125">125</a> <b><i>         * protocol to ESP, and then call into the transform receiver.</i></b>
<a name="L126" href="source/net/ipv4/xfrm4_input.c#L126">126</a> <b><i>         */</i></b>
<a name="L127" href="source/net/ipv4/xfrm4_input.c#L127">127</a>         if (<a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L128" href="source/net/ipv4/xfrm4_input.c#L128">128</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L129" href="source/net/ipv4/xfrm4_input.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/xfrm4_input.c#L130">130</a>         <b><i>/* Now we can update and verify the packet length... */</i></b>
<a name="L131" href="source/net/ipv4/xfrm4_input.c#L131">131</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L132" href="source/net/ipv4/xfrm4_input.c#L132">132</a>         iphlen = iph-&gt;ihl &lt;&lt; 2;
<a name="L133" href="source/net/ipv4/xfrm4_input.c#L133">133</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(iph-&gt;tot_len) - <a href="ident?i=len">len</a>);
<a name="L134" href="source/net/ipv4/xfrm4_input.c#L134">134</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; iphlen + <a href="ident?i=len">len</a>) {
<a name="L135" href="source/net/ipv4/xfrm4_input.c#L135">135</a>                 <b><i>/* packet is too small!?! */</i></b>
<a name="L136" href="source/net/ipv4/xfrm4_input.c#L136">136</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L137" href="source/net/ipv4/xfrm4_input.c#L137">137</a>         }
<a name="L138" href="source/net/ipv4/xfrm4_input.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/xfrm4_input.c#L139">139</a>         <b><i>/* pull the data buffer up to the ESP header and set the</i></b>
<a name="L140" href="source/net/ipv4/xfrm4_input.c#L140">140</a> <b><i>         * transport header to point to ESP.  Keep UDP on the stack</i></b>
<a name="L141" href="source/net/ipv4/xfrm4_input.c#L141">141</a> <b><i>         * for later.</i></b>
<a name="L142" href="source/net/ipv4/xfrm4_input.c#L142">142</a> <b><i>         */</i></b>
<a name="L143" href="source/net/ipv4/xfrm4_input.c#L143">143</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>);
<a name="L144" href="source/net/ipv4/xfrm4_input.c#L144">144</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L145" href="source/net/ipv4/xfrm4_input.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/xfrm4_input.c#L146">146</a>         <b><i>/* process ESP */</i></b>
<a name="L147" href="source/net/ipv4/xfrm4_input.c#L147">147</a>         return <a href="ident?i=xfrm4_rcv_encap">xfrm4_rcv_encap</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>, 0, encap_type);
<a name="L148" href="source/net/ipv4/xfrm4_input.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/xfrm4_input.c#L149">149</a> <a href="ident?i=drop">drop</a>:
<a name="L150" href="source/net/ipv4/xfrm4_input.c#L150">150</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L151" href="source/net/ipv4/xfrm4_input.c#L151">151</a>         return 0;
<a name="L152" href="source/net/ipv4/xfrm4_input.c#L152">152</a> }
<a name="L153" href="source/net/ipv4/xfrm4_input.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/xfrm4_input.c#L154">154</a> int <a href="ident?i=xfrm4_rcv">xfrm4_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L155" href="source/net/ipv4/xfrm4_input.c#L155">155</a> {
<a name="L156" href="source/net/ipv4/xfrm4_input.c#L156">156</a>         return <a href="ident?i=xfrm4_rcv_spi">xfrm4_rcv_spi</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>, 0);
<a name="L157" href="source/net/ipv4/xfrm4_input.c#L157">157</a> }
<a name="L158" href="source/net/ipv4/xfrm4_input.c#L158">158</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_rcv">xfrm4_rcv</a>);
<a name="L159" href="source/net/ipv4/xfrm4_input.c#L159">159</a> </pre></div><p>
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
