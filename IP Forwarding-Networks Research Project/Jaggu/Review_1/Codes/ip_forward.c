<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_forward.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_forward.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_forward.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_forward.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_forward.c">ip_forward.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_forward.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_forward.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ip_forward.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ip_forward.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ip_forward.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_forward.c#L6">6</a> <b><i> *              The IP forwarding functionality.</i></b>
  <a name="L7" href="source/net/ipv4/ip_forward.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_forward.c#L8">8</a> <b><i> * Authors:     see ip.c</i></b>
  <a name="L9" href="source/net/ipv4/ip_forward.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/ip_forward.c#L10">10</a> <b><i> * Fixes:</i></b>
 <a name="L11" href="source/net/ipv4/ip_forward.c#L11">11</a> <b><i> *              Many            :       Split from ip.c , see ip_input.c for</i></b>
 <a name="L12" href="source/net/ipv4/ip_forward.c#L12">12</a> <b><i> *                                      history.</i></b>
 <a name="L13" href="source/net/ipv4/ip_forward.c#L13">13</a> <b><i> *              Dave Gregorich  :       NULL ip_rt_put fix for multicast</i></b>
 <a name="L14" href="source/net/ipv4/ip_forward.c#L14">14</a> <b><i> *                                      routing.</i></b>
 <a name="L15" href="source/net/ipv4/ip_forward.c#L15">15</a> <b><i> *              Jos Vos         :       Add call_out_firewall before sending,</i></b>
 <a name="L16" href="source/net/ipv4/ip_forward.c#L16">16</a> <b><i> *                                      use output device for accounting.</i></b>
 <a name="L17" href="source/net/ipv4/ip_forward.c#L17">17</a> <b><i> *              Jos Vos         :       Call forward firewall after routing</i></b>
 <a name="L18" href="source/net/ipv4/ip_forward.c#L18">18</a> <b><i> *                                      (always use output device).</i></b>
 <a name="L19" href="source/net/ipv4/ip_forward.c#L19">19</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L20" href="source/net/ipv4/ip_forward.c#L20">20</a> <b><i> */</i></b>
 <a name="L21" href="source/net/ipv4/ip_forward.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/ip_forward.c#L22">22</a> #include &lt;linux/types.h&gt;
 <a name="L23" href="source/net/ipv4/ip_forward.c#L23">23</a> #include &lt;linux/mm.h&gt;
 <a name="L24" href="source/net/ipv4/ip_forward.c#L24">24</a> #include &lt;linux/skbuff.h&gt;
 <a name="L25" href="source/net/ipv4/ip_forward.c#L25">25</a> #include &lt;linux/ip.h&gt;
 <a name="L26" href="source/net/ipv4/ip_forward.c#L26">26</a> #include &lt;linux/icmp.h&gt;
 <a name="L27" href="source/net/ipv4/ip_forward.c#L27">27</a> #include &lt;linux/netdevice.h&gt;
 <a name="L28" href="source/net/ipv4/ip_forward.c#L28">28</a> #include &lt;linux/slab.h&gt;
 <a name="L29" href="source/net/ipv4/ip_forward.c#L29">29</a> #include &lt;net/sock.h&gt;
 <a name="L30" href="source/net/ipv4/ip_forward.c#L30">30</a> #include &lt;net/ip.h&gt;
 <a name="L31" href="source/net/ipv4/ip_forward.c#L31">31</a> #include &lt;net/tcp.h&gt;
 <a name="L32" href="source/net/ipv4/ip_forward.c#L32">32</a> #include &lt;net/udp.h&gt;
 <a name="L33" href="source/net/ipv4/ip_forward.c#L33">33</a> #include &lt;net/icmp.h&gt;
 <a name="L34" href="source/net/ipv4/ip_forward.c#L34">34</a> #include &lt;linux/tcp.h&gt;
 <a name="L35" href="source/net/ipv4/ip_forward.c#L35">35</a> #include &lt;linux/udp.h&gt;
 <a name="L36" href="source/net/ipv4/ip_forward.c#L36">36</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L37" href="source/net/ipv4/ip_forward.c#L37">37</a> #include &lt;net/checksum.h&gt;
 <a name="L38" href="source/net/ipv4/ip_forward.c#L38">38</a> #include &lt;linux/route.h&gt;
 <a name="L39" href="source/net/ipv4/ip_forward.c#L39">39</a> #include &lt;net/route.h&gt;
 <a name="L40" href="source/net/ipv4/ip_forward.c#L40">40</a> #include &lt;net/xfrm.h&gt;
 <a name="L41" href="source/net/ipv4/ip_forward.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/ip_forward.c#L42">42</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ip_may_fragment">ip_may_fragment</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L43" href="source/net/ipv4/ip_forward.c#L43">43</a> {
 <a name="L44" href="source/net/ipv4/ip_forward.c#L44">44</a>         return <a href="ident?i=unlikely">unlikely</a>((<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>)) == 0) ||
 <a name="L45" href="source/net/ipv4/ip_forward.c#L45">45</a>                 <a href="ident?i=skb">skb</a>-&gt;ignore_df;
 <a name="L46" href="source/net/ipv4/ip_forward.c#L46">46</a> }
 <a name="L47" href="source/net/ipv4/ip_forward.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/ip_forward.c#L48">48</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ip_exceeds_mtu">ip_exceeds_mtu</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int <a href="ident?i=mtu">mtu</a>)
 <a name="L49" href="source/net/ipv4/ip_forward.c#L49">49</a> {
 <a name="L50" href="source/net/ipv4/ip_forward.c#L50">50</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= <a href="ident?i=mtu">mtu</a>)
 <a name="L51" href="source/net/ipv4/ip_forward.c#L51">51</a>                 return <a href="ident?i=false">false</a>;
 <a name="L52" href="source/net/ipv4/ip_forward.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/ip_forward.c#L53">53</a>         if (<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>) &amp;&amp; <a href="ident?i=skb_gso_network_seglen">skb_gso_network_seglen</a>(<a href="ident?i=skb">skb</a>) &lt;= <a href="ident?i=mtu">mtu</a>)
 <a name="L54" href="source/net/ipv4/ip_forward.c#L54">54</a>                 return <a href="ident?i=false">false</a>;
 <a name="L55" href="source/net/ipv4/ip_forward.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/ip_forward.c#L56">56</a>         return <a href="ident?i=true">true</a>;
 <a name="L57" href="source/net/ipv4/ip_forward.c#L57">57</a> }
 <a name="L58" href="source/net/ipv4/ip_forward.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/ip_forward.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/ip_forward.c#L60">60</a> static int <a href="ident?i=ip_forward_finish">ip_forward_finish</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L61" href="source/net/ipv4/ip_forward.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/ip_forward.c#L62">62</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt  = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
 <a name="L63" href="source/net/ipv4/ip_forward.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/ip_forward.c#L64">64</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUTFORWDATAGRAMS);
 <a name="L65" href="source/net/ipv4/ip_forward.c#L65">65</a>         <a href="ident?i=IP_ADD_STATS_BH">IP_ADD_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUTOCTETS, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
 <a name="L66" href="source/net/ipv4/ip_forward.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/ip_forward.c#L67">67</a>         if (<a href="ident?i=unlikely">unlikely</a>(opt-&gt;<a href="ident?i=optlen">optlen</a>))
 <a name="L68" href="source/net/ipv4/ip_forward.c#L68">68</a>                 <a href="ident?i=ip_forward_options">ip_forward_options</a>(<a href="ident?i=skb">skb</a>);
 <a name="L69" href="source/net/ipv4/ip_forward.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/ip_forward.c#L70">70</a>         <a href="ident?i=skb_sender_cpu_clear">skb_sender_cpu_clear</a>(<a href="ident?i=skb">skb</a>);
 <a name="L71" href="source/net/ipv4/ip_forward.c#L71">71</a>         return <a href="ident?i=dst_output_sk">dst_output_sk</a>(sk, <a href="ident?i=skb">skb</a>);
 <a name="L72" href="source/net/ipv4/ip_forward.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/ip_forward.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/ip_forward.c#L74">74</a> int <a href="ident?i=ip_forward">ip_forward</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L75" href="source/net/ipv4/ip_forward.c#L75">75</a> {
 <a name="L76" href="source/net/ipv4/ip_forward.c#L76">76</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>;
 <a name="L77" href="source/net/ipv4/ip_forward.c#L77">77</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;      <b><i>/* Our header */</i></b>
 <a name="L78" href="source/net/ipv4/ip_forward.c#L78">78</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;      <b><i>/* Route we use */</i></b>
 <a name="L79" href="source/net/ipv4/ip_forward.c#L79">79</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt  = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
 <a name="L80" href="source/net/ipv4/ip_forward.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/ip_forward.c#L81">81</a>         <b><i>/* that should never happen */</i></b>
 <a name="L82" href="source/net/ipv4/ip_forward.c#L82">82</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type != <a href="ident?i=PACKET_HOST">PACKET_HOST</a>)
 <a name="L83" href="source/net/ipv4/ip_forward.c#L83">83</a>                 goto <a href="ident?i=drop">drop</a>;
 <a name="L84" href="source/net/ipv4/ip_forward.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/ip_forward.c#L85">85</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;sk))
 <a name="L86" href="source/net/ipv4/ip_forward.c#L86">86</a>                 goto <a href="ident?i=drop">drop</a>;
 <a name="L87" href="source/net/ipv4/ip_forward.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/ip_forward.c#L88">88</a>         if (<a href="ident?i=skb_warn_if_lro">skb_warn_if_lro</a>(<a href="ident?i=skb">skb</a>))
 <a name="L89" href="source/net/ipv4/ip_forward.c#L89">89</a>                 goto <a href="ident?i=drop">drop</a>;
 <a name="L90" href="source/net/ipv4/ip_forward.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/ip_forward.c#L91">91</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_FWD, <a href="ident?i=skb">skb</a>))
 <a name="L92" href="source/net/ipv4/ip_forward.c#L92">92</a>                 goto <a href="ident?i=drop">drop</a>;
 <a name="L93" href="source/net/ipv4/ip_forward.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ip_forward.c#L94">94</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt.router_alert &amp;&amp; <a href="ident?i=ip_call_ra_chain">ip_call_ra_chain</a>(<a href="ident?i=skb">skb</a>))
 <a name="L95" href="source/net/ipv4/ip_forward.c#L95">95</a>                 return <a href="ident?i=NET_RX_SUCCESS">NET_RX_SUCCESS</a>;
 <a name="L96" href="source/net/ipv4/ip_forward.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/ip_forward.c#L97">97</a>         <a href="ident?i=skb_forward_csum">skb_forward_csum</a>(<a href="ident?i=skb">skb</a>);
 <a name="L98" href="source/net/ipv4/ip_forward.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/ip_forward.c#L99">99</a>         <b><i>/*</i></b>
<a name="L100" href="source/net/ipv4/ip_forward.c#L100">100</a> <b><i>         *      According to the RFC, we must first decrease the TTL field. If</i></b>
<a name="L101" href="source/net/ipv4/ip_forward.c#L101">101</a> <b><i>         *      that reaches zero, we must reply an ICMP control message telling</i></b>
<a name="L102" href="source/net/ipv4/ip_forward.c#L102">102</a> <b><i>         *      that the packet's lifetime expired.</i></b>
<a name="L103" href="source/net/ipv4/ip_forward.c#L103">103</a> <b><i>         */</i></b>
<a name="L104" href="source/net/ipv4/ip_forward.c#L104">104</a>         if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a> &lt;= 1)
<a name="L105" href="source/net/ipv4/ip_forward.c#L105">105</a>                 goto too_many_hops;
<a name="L106" href="source/net/ipv4/ip_forward.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/ip_forward.c#L107">107</a>         if (!<a href="ident?i=xfrm4_route_forward">xfrm4_route_forward</a>(<a href="ident?i=skb">skb</a>))
<a name="L108" href="source/net/ipv4/ip_forward.c#L108">108</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L109" href="source/net/ipv4/ip_forward.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/ip_forward.c#L110">110</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L111" href="source/net/ipv4/ip_forward.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/ip_forward.c#L112">112</a>         if (opt-&gt;is_strictroute &amp;&amp; <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway)
<a name="L113" href="source/net/ipv4/ip_forward.c#L113">113</a>                 goto sr_failed;
<a name="L114" href="source/net/ipv4/ip_forward.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/ip_forward.c#L115">115</a>         <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_FORWARDED">IPSKB_FORWARDED</a>;
<a name="L116" href="source/net/ipv4/ip_forward.c#L116">116</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=ip_dst_mtu_maybe_forward">ip_dst_mtu_maybe_forward</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L117" href="source/net/ipv4/ip_forward.c#L117">117</a>         if (!<a href="ident?i=ip_may_fragment">ip_may_fragment</a>(<a href="ident?i=skb">skb</a>) &amp;&amp; <a href="ident?i=ip_exceeds_mtu">ip_exceeds_mtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=mtu">mtu</a>)) {
<a name="L118" href="source/net/ipv4/ip_forward.c#L118">118</a>                 <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGFAILS);
<a name="L119" href="source/net/ipv4/ip_forward.c#L119">119</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>,
<a name="L120" href="source/net/ipv4/ip_forward.c#L120">120</a>                           <a href="ident?i=htonl">htonl</a>(<a href="ident?i=mtu">mtu</a>));
<a name="L121" href="source/net/ipv4/ip_forward.c#L121">121</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L122" href="source/net/ipv4/ip_forward.c#L122">122</a>         }
<a name="L123" href="source/net/ipv4/ip_forward.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/ip_forward.c#L124">124</a>         <b><i>/* We are about to mangle packet. Copy it! */</i></b>
<a name="L125" href="source/net/ipv4/ip_forward.c#L125">125</a>         if (<a href="ident?i=skb_cow">skb_cow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>)+<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=header_len">header_len</a>))
<a name="L126" href="source/net/ipv4/ip_forward.c#L126">126</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L127" href="source/net/ipv4/ip_forward.c#L127">127</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L128" href="source/net/ipv4/ip_forward.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/ip_forward.c#L129">129</a>         <b><i>/* Decrease ttl after skb cow done */</i></b>
<a name="L130" href="source/net/ipv4/ip_forward.c#L130">130</a>         <a href="ident?i=ip_decrease_ttl">ip_decrease_ttl</a>(iph);
<a name="L131" href="source/net/ipv4/ip_forward.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/ip_forward.c#L132">132</a>         <b><i>/*</i></b>
<a name="L133" href="source/net/ipv4/ip_forward.c#L133">133</a> <b><i>         *      We now generate an ICMP HOST REDIRECT giving the route</i></b>
<a name="L134" href="source/net/ipv4/ip_forward.c#L134">134</a> <b><i>         *      we calculated.</i></b>
<a name="L135" href="source/net/ipv4/ip_forward.c#L135">135</a> <b><i>         */</i></b>
<a name="L136" href="source/net/ipv4/ip_forward.c#L136">136</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_DOREDIRECT">IPSKB_DOREDIRECT</a> &amp;&amp; !opt-&gt;<a href="ident?i=srr">srr</a> &amp;&amp;
<a name="L137" href="source/net/ipv4/ip_forward.c#L137">137</a>             !<a href="ident?i=skb_sec_path">skb_sec_path</a>(<a href="ident?i=skb">skb</a>))
<a name="L138" href="source/net/ipv4/ip_forward.c#L138">138</a>                 <a href="ident?i=ip_rt_send_redirect">ip_rt_send_redirect</a>(<a href="ident?i=skb">skb</a>);
<a name="L139" href="source/net/ipv4/ip_forward.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/ip_forward.c#L140">140</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = <a href="ident?i=rt_tos2priority">rt_tos2priority</a>(iph-&gt;tos);
<a name="L141" href="source/net/ipv4/ip_forward.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/ip_forward.c#L142">142</a>         return <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_FORWARD, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
<a name="L143" href="source/net/ipv4/ip_forward.c#L143">143</a>                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>, <a href="ident?i=ip_forward_finish">ip_forward_finish</a>);
<a name="L144" href="source/net/ipv4/ip_forward.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/ip_forward.c#L145">145</a> sr_failed:
<a name="L146" href="source/net/ipv4/ip_forward.c#L146">146</a>         <b><i>/*</i></b>
<a name="L147" href="source/net/ipv4/ip_forward.c#L147">147</a> <b><i>         *      Strict routing permits no gatewaying</i></b>
<a name="L148" href="source/net/ipv4/ip_forward.c#L148">148</a> <b><i>         */</i></b>
<a name="L149" href="source/net/ipv4/ip_forward.c#L149">149</a>          <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_SR_FAILED">ICMP_SR_FAILED</a>, 0);
<a name="L150" href="source/net/ipv4/ip_forward.c#L150">150</a>          goto <a href="ident?i=drop">drop</a>;
<a name="L151" href="source/net/ipv4/ip_forward.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/ip_forward.c#L152">152</a> too_many_hops:
<a name="L153" href="source/net/ipv4/ip_forward.c#L153">153</a>         <b><i>/* Tell the sender its packet died... */</i></b>
<a name="L154" href="source/net/ipv4/ip_forward.c#L154">154</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), IPSTATS_MIB_INHDRERRORS);
<a name="L155" href="source/net/ipv4/ip_forward.c#L155">155</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>, <a href="ident?i=ICMP_EXC_TTL">ICMP_EXC_TTL</a>, 0);
<a name="L156" href="source/net/ipv4/ip_forward.c#L156">156</a> <a href="ident?i=drop">drop</a>:
<a name="L157" href="source/net/ipv4/ip_forward.c#L157">157</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L158" href="source/net/ipv4/ip_forward.c#L158">158</a>         return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L159" href="source/net/ipv4/ip_forward.c#L159">159</a> }
<a name="L160" href="source/net/ipv4/ip_forward.c#L160">160</a> </pre></div><p>
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
