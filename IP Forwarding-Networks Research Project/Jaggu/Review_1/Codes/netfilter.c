<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter.c">netfilter.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter.c#L2">2</a> <b><i> * IPv4 specific functions of netfilter core</i></b>
  <a name="L3" href="source/net/ipv4/netfilter.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter.c#L4">4</a> <b><i> * Rusty Russell (C) 2000 -- This code is GPL.</i></b>
  <a name="L5" href="source/net/ipv4/netfilter.c#L5">5</a> <b><i> * Patrick McHardy (C) 2006-2012</i></b>
  <a name="L6" href="source/net/ipv4/netfilter.c#L6">6</a> <b><i> */</i></b>
  <a name="L7" href="source/net/ipv4/netfilter.c#L7">7</a> #include &lt;linux/kernel.h&gt;
  <a name="L8" href="source/net/ipv4/netfilter.c#L8">8</a> #include &lt;linux/netfilter.h&gt;
  <a name="L9" href="source/net/ipv4/netfilter.c#L9">9</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter.c#L10">10</a> #include &lt;linux/ip.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter.c#L11">11</a> #include &lt;linux/skbuff.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter.c#L12">12</a> #include &lt;linux/gfp.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter.c#L13">13</a> #include &lt;linux/export.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter.c#L14">14</a> #include &lt;net/route.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter.c#L15">15</a> #include &lt;net/xfrm.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter.c#L16">16</a> #include &lt;net/ip.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter.c#L17">17</a> #include &lt;net/netfilter/nf_queue.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/netfilter.c#L19">19</a> <b><i>/* route_me_harder function, used by iptable_nat, iptable_mangle + ip_queue */</i></b>
 <a name="L20" href="source/net/ipv4/netfilter.c#L20">20</a> int <a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int addr_type)
 <a name="L21" href="source/net/ipv4/netfilter.c#L21">21</a> {
 <a name="L22" href="source/net/ipv4/netfilter.c#L22">22</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>);
 <a name="L23" href="source/net/ipv4/netfilter.c#L23">23</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L24" href="source/net/ipv4/netfilter.c#L24">24</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
 <a name="L25" href="source/net/ipv4/netfilter.c#L25">25</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4 = {};
 <a name="L26" href="source/net/ipv4/netfilter.c#L26">26</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L27" href="source/net/ipv4/netfilter.c#L27">27</a>         <a href="ident?i=__u8">__u8</a> <a href="ident?i=flags">flags</a> = <a href="ident?i=skb">skb</a>-&gt;sk ? <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(<a href="ident?i=skb">skb</a>-&gt;sk) : 0;
 <a name="L28" href="source/net/ipv4/netfilter.c#L28">28</a>         unsigned int hh_len;
 <a name="L29" href="source/net/ipv4/netfilter.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/netfilter.c#L30">30</a>         if (addr_type == RTN_UNSPEC)
 <a name="L31" href="source/net/ipv4/netfilter.c#L31">31</a>                 addr_type = <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>);
 <a name="L32" href="source/net/ipv4/netfilter.c#L32">32</a>         if (addr_type == RTN_LOCAL || addr_type == RTN_UNICAST)
 <a name="L33" href="source/net/ipv4/netfilter.c#L33">33</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=FLOWI_FLAG_ANYSRC">FLOWI_FLAG_ANYSRC</a>;
 <a name="L34" href="source/net/ipv4/netfilter.c#L34">34</a>         else
 <a name="L35" href="source/net/ipv4/netfilter.c#L35">35</a>                 <a href="ident?i=saddr">saddr</a> = 0;
 <a name="L36" href="source/net/ipv4/netfilter.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter.c#L37">37</a>         <b><i>/* some non-standard hacks like ipt_REJECT.c:send_reset() can cause</i></b>
 <a name="L38" href="source/net/ipv4/netfilter.c#L38">38</a> <b><i>         * packets with foreign saddr to appear on the NF_INET_LOCAL_OUT hook.</i></b>
 <a name="L39" href="source/net/ipv4/netfilter.c#L39">39</a> <b><i>         */</i></b>
 <a name="L40" href="source/net/ipv4/netfilter.c#L40">40</a>         fl4.<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L41" href="source/net/ipv4/netfilter.c#L41">41</a>         fl4.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
 <a name="L42" href="source/net/ipv4/netfilter.c#L42">42</a>         fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos);
 <a name="L43" href="source/net/ipv4/netfilter.c#L43">43</a>         fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = <a href="ident?i=skb">skb</a>-&gt;sk ? <a href="ident?i=skb">skb</a>-&gt;sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> : 0;
 <a name="L44" href="source/net/ipv4/netfilter.c#L44">44</a>         fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
 <a name="L45" href="source/net/ipv4/netfilter.c#L45">45</a>         fl4.<a href="ident?i=flowi4_flags">flowi4_flags</a> = <a href="ident?i=flags">flags</a>;
 <a name="L46" href="source/net/ipv4/netfilter.c#L46">46</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4);
 <a name="L47" href="source/net/ipv4/netfilter.c#L47">47</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
 <a name="L48" href="source/net/ipv4/netfilter.c#L48">48</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
 <a name="L49" href="source/net/ipv4/netfilter.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/netfilter.c#L50">50</a>         <b><i>/* Drop old route. */</i></b>
 <a name="L51" href="source/net/ipv4/netfilter.c#L51">51</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
 <a name="L52" href="source/net/ipv4/netfilter.c#L52">52</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
 <a name="L53" href="source/net/ipv4/netfilter.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/netfilter.c#L54">54</a>         if (<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=error">error</a>)
 <a name="L55" href="source/net/ipv4/netfilter.c#L55">55</a>                 return <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=error">error</a>;
 <a name="L56" href="source/net/ipv4/netfilter.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/netfilter.c#L57">57</a> #ifdef CONFIG_XFRM
 <a name="L58" href="source/net/ipv4/netfilter.c#L58">58</a>         if (!(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_XFRM_TRANSFORMED">IPSKB_XFRM_TRANSFORMED</a>) &amp;&amp;
 <a name="L59" href="source/net/ipv4/netfilter.c#L59">59</a>             <a href="ident?i=xfrm_decode_session">xfrm_decode_session</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4), <a href="ident?i=AF_INET">AF_INET</a>) == 0) {
 <a name="L60" href="source/net/ipv4/netfilter.c#L60">60</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
 <a name="L61" href="source/net/ipv4/netfilter.c#L61">61</a>                 <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>);
 <a name="L62" href="source/net/ipv4/netfilter.c#L62">62</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=xfrm_lookup">xfrm_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4), <a href="ident?i=skb">skb</a>-&gt;sk, 0);
 <a name="L63" href="source/net/ipv4/netfilter.c#L63">63</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=dst">dst</a>))
 <a name="L64" href="source/net/ipv4/netfilter.c#L64">64</a>                         return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=dst">dst</a>);
 <a name="L65" href="source/net/ipv4/netfilter.c#L65">65</a>                 <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>);
 <a name="L66" href="source/net/ipv4/netfilter.c#L66">66</a>         }
 <a name="L67" href="source/net/ipv4/netfilter.c#L67">67</a> #endif
 <a name="L68" href="source/net/ipv4/netfilter.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/netfilter.c#L69">69</a>         <b><i>/* Change in oif may mean change in hh_len. */</i></b>
 <a name="L70" href="source/net/ipv4/netfilter.c#L70">70</a>         hh_len = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>-&gt;hard_header_len;
 <a name="L71" href="source/net/ipv4/netfilter.c#L71">71</a>         if (<a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>) &lt; hh_len &amp;&amp;
 <a name="L72" href="source/net/ipv4/netfilter.c#L72">72</a>             <a href="ident?i=pskb_expand_head">pskb_expand_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=HH_DATA_ALIGN">HH_DATA_ALIGN</a>(hh_len - <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>)),
 <a name="L73" href="source/net/ipv4/netfilter.c#L73">73</a>                                 0, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
 <a name="L74" href="source/net/ipv4/netfilter.c#L74">74</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L75" href="source/net/ipv4/netfilter.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter.c#L76">76</a>         return 0;
 <a name="L77" href="source/net/ipv4/netfilter.c#L77">77</a> }
 <a name="L78" href="source/net/ipv4/netfilter.c#L78">78</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>);
 <a name="L79" href="source/net/ipv4/netfilter.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/netfilter.c#L80">80</a> <b><i>/*</i></b>
 <a name="L81" href="source/net/ipv4/netfilter.c#L81">81</a> <b><i> * Extra routing may needed on local out, as the QUEUE target never</i></b>
 <a name="L82" href="source/net/ipv4/netfilter.c#L82">82</a> <b><i> * returns control to the table.</i></b>
 <a name="L83" href="source/net/ipv4/netfilter.c#L83">83</a> <b><i> */</i></b>
 <a name="L84" href="source/net/ipv4/netfilter.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter.c#L85">85</a> struct <a href="ident?i=ip_rt_info">ip_rt_info</a> {
 <a name="L86" href="source/net/ipv4/netfilter.c#L86">86</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>;
 <a name="L87" href="source/net/ipv4/netfilter.c#L87">87</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>;
 <a name="L88" href="source/net/ipv4/netfilter.c#L88">88</a>         <a href="ident?i=u_int8_t">u_int8_t</a> tos;
 <a name="L89" href="source/net/ipv4/netfilter.c#L89">89</a>         <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=mark">mark</a>;
 <a name="L90" href="source/net/ipv4/netfilter.c#L90">90</a> };
 <a name="L91" href="source/net/ipv4/netfilter.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/netfilter.c#L92">92</a> static void <a href="ident?i=nf_ip_saveroute">nf_ip_saveroute</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L93" href="source/net/ipv4/netfilter.c#L93">93</a>                             struct <a href="ident?i=nf_queue_entry">nf_queue_entry</a> *<a href="ident?i=entry">entry</a>)
 <a name="L94" href="source/net/ipv4/netfilter.c#L94">94</a> {
 <a name="L95" href="source/net/ipv4/netfilter.c#L95">95</a>         struct <a href="ident?i=ip_rt_info">ip_rt_info</a> *rt_info = <a href="ident?i=nf_queue_entry_reroute">nf_queue_entry_reroute</a>(<a href="ident?i=entry">entry</a>);
 <a name="L96" href="source/net/ipv4/netfilter.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/netfilter.c#L97">97</a>         if (<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=state">state</a>.hook == NF_INET_LOCAL_OUT) {
 <a name="L98" href="source/net/ipv4/netfilter.c#L98">98</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L99" href="source/net/ipv4/netfilter.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/netfilter.c#L100">100</a>                 rt_info-&gt;tos = iph-&gt;tos;
<a name="L101" href="source/net/ipv4/netfilter.c#L101">101</a>                 rt_info-&gt;<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L102" href="source/net/ipv4/netfilter.c#L102">102</a>                 rt_info-&gt;<a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L103" href="source/net/ipv4/netfilter.c#L103">103</a>                 rt_info-&gt;<a href="ident?i=mark">mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
<a name="L104" href="source/net/ipv4/netfilter.c#L104">104</a>         }
<a name="L105" href="source/net/ipv4/netfilter.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/netfilter.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/netfilter.c#L107">107</a> static int <a href="ident?i=nf_ip_reroute">nf_ip_reroute</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L108" href="source/net/ipv4/netfilter.c#L108">108</a>                          const struct <a href="ident?i=nf_queue_entry">nf_queue_entry</a> *<a href="ident?i=entry">entry</a>)
<a name="L109" href="source/net/ipv4/netfilter.c#L109">109</a> {
<a name="L110" href="source/net/ipv4/netfilter.c#L110">110</a>         const struct <a href="ident?i=ip_rt_info">ip_rt_info</a> *rt_info = <a href="ident?i=nf_queue_entry_reroute">nf_queue_entry_reroute</a>(<a href="ident?i=entry">entry</a>);
<a name="L111" href="source/net/ipv4/netfilter.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/netfilter.c#L112">112</a>         if (<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=state">state</a>.hook == NF_INET_LOCAL_OUT) {
<a name="L113" href="source/net/ipv4/netfilter.c#L113">113</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L114" href="source/net/ipv4/netfilter.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/netfilter.c#L115">115</a>                 if (!(iph-&gt;tos == rt_info-&gt;tos &amp;&amp;
<a name="L116" href="source/net/ipv4/netfilter.c#L116">116</a>                       <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> == rt_info-&gt;<a href="ident?i=mark">mark</a> &amp;&amp;
<a name="L117" href="source/net/ipv4/netfilter.c#L117">117</a>                       iph-&gt;<a href="ident?i=daddr">daddr</a> == rt_info-&gt;<a href="ident?i=daddr">daddr</a> &amp;&amp;
<a name="L118" href="source/net/ipv4/netfilter.c#L118">118</a>                       iph-&gt;<a href="ident?i=saddr">saddr</a> == rt_info-&gt;<a href="ident?i=saddr">saddr</a>))
<a name="L119" href="source/net/ipv4/netfilter.c#L119">119</a>                         return <a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(<a href="ident?i=skb">skb</a>, RTN_UNSPEC);
<a name="L120" href="source/net/ipv4/netfilter.c#L120">120</a>         }
<a name="L121" href="source/net/ipv4/netfilter.c#L121">121</a>         return 0;
<a name="L122" href="source/net/ipv4/netfilter.c#L122">122</a> }
<a name="L123" href="source/net/ipv4/netfilter.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/netfilter.c#L124">124</a> <a href="ident?i=__sum16">__sum16</a> <a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int hook,
<a name="L125" href="source/net/ipv4/netfilter.c#L125">125</a>                             unsigned int dataoff, <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=protocol">protocol</a>)
<a name="L126" href="source/net/ipv4/netfilter.c#L126">126</a> {
<a name="L127" href="source/net/ipv4/netfilter.c#L127">127</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L128" href="source/net/ipv4/netfilter.c#L128">128</a>         <a href="ident?i=__sum16">__sum16</a> <a href="ident?i=csum">csum</a> = 0;
<a name="L129" href="source/net/ipv4/netfilter.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/netfilter.c#L130">130</a>         switch (<a href="ident?i=skb">skb</a>-&gt;ip_summed) {
<a name="L131" href="source/net/ipv4/netfilter.c#L131">131</a>         case <a href="ident?i=CHECKSUM_COMPLETE">CHECKSUM_COMPLETE</a>:
<a name="L132" href="source/net/ipv4/netfilter.c#L132">132</a>                 if (hook != NF_INET_PRE_ROUTING &amp;&amp; hook != NF_INET_LOCAL_IN)
<a name="L133" href="source/net/ipv4/netfilter.c#L133">133</a>                         break;
<a name="L134" href="source/net/ipv4/netfilter.c#L134">134</a>                 if ((<a href="ident?i=protocol">protocol</a> == 0 &amp;&amp; !<a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>)) ||
<a name="L135" href="source/net/ipv4/netfilter.c#L135">135</a>                     !<a href="ident?i=csum_tcpudp_magic">csum_tcpudp_magic</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L136" href="source/net/ipv4/netfilter.c#L136">136</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - dataoff, <a href="ident?i=protocol">protocol</a>,
<a name="L137" href="source/net/ipv4/netfilter.c#L137">137</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>)) {
<a name="L138" href="source/net/ipv4/netfilter.c#L138">138</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_UNNECESSARY">CHECKSUM_UNNECESSARY</a>;
<a name="L139" href="source/net/ipv4/netfilter.c#L139">139</a>                         break;
<a name="L140" href="source/net/ipv4/netfilter.c#L140">140</a>                 }
<a name="L141" href="source/net/ipv4/netfilter.c#L141">141</a>                 <b><i>/* fall through */</i></b>
<a name="L142" href="source/net/ipv4/netfilter.c#L142">142</a>         case <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>:
<a name="L143" href="source/net/ipv4/netfilter.c#L143">143</a>                 if (<a href="ident?i=protocol">protocol</a> == 0)
<a name="L144" href="source/net/ipv4/netfilter.c#L144">144</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L145" href="source/net/ipv4/netfilter.c#L145">145</a>                 else
<a name="L146" href="source/net/ipv4/netfilter.c#L146">146</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_tcpudp_nofold">csum_tcpudp_nofold</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L147" href="source/net/ipv4/netfilter.c#L147">147</a>                                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - dataoff,
<a name="L148" href="source/net/ipv4/netfilter.c#L148">148</a>                                                        <a href="ident?i=protocol">protocol</a>, 0);
<a name="L149" href="source/net/ipv4/netfilter.c#L149">149</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=__skb_checksum_complete">__skb_checksum_complete</a>(<a href="ident?i=skb">skb</a>);
<a name="L150" href="source/net/ipv4/netfilter.c#L150">150</a>         }
<a name="L151" href="source/net/ipv4/netfilter.c#L151">151</a>         return <a href="ident?i=csum">csum</a>;
<a name="L152" href="source/net/ipv4/netfilter.c#L152">152</a> }
<a name="L153" href="source/net/ipv4/netfilter.c#L153">153</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>);
<a name="L154" href="source/net/ipv4/netfilter.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/netfilter.c#L155">155</a> static <a href="ident?i=__sum16">__sum16</a> <a href="ident?i=nf_ip_checksum_partial">nf_ip_checksum_partial</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int hook,
<a name="L156" href="source/net/ipv4/netfilter.c#L156">156</a>                                       unsigned int dataoff, unsigned int <a href="ident?i=len">len</a>,
<a name="L157" href="source/net/ipv4/netfilter.c#L157">157</a>                                       <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=protocol">protocol</a>)
<a name="L158" href="source/net/ipv4/netfilter.c#L158">158</a> {
<a name="L159" href="source/net/ipv4/netfilter.c#L159">159</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L160" href="source/net/ipv4/netfilter.c#L160">160</a>         <a href="ident?i=__sum16">__sum16</a> <a href="ident?i=csum">csum</a> = 0;
<a name="L161" href="source/net/ipv4/netfilter.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/netfilter.c#L162">162</a>         switch (<a href="ident?i=skb">skb</a>-&gt;ip_summed) {
<a name="L163" href="source/net/ipv4/netfilter.c#L163">163</a>         case <a href="ident?i=CHECKSUM_COMPLETE">CHECKSUM_COMPLETE</a>:
<a name="L164" href="source/net/ipv4/netfilter.c#L164">164</a>                 if (<a href="ident?i=len">len</a> == <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - dataoff)
<a name="L165" href="source/net/ipv4/netfilter.c#L165">165</a>                         return <a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(<a href="ident?i=skb">skb</a>, hook, dataoff, <a href="ident?i=protocol">protocol</a>);
<a name="L166" href="source/net/ipv4/netfilter.c#L166">166</a>                 <b><i>/* fall through */</i></b>
<a name="L167" href="source/net/ipv4/netfilter.c#L167">167</a>         case <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>:
<a name="L168" href="source/net/ipv4/netfilter.c#L168">168</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_tcpudp_nofold">csum_tcpudp_nofold</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=protocol">protocol</a>,
<a name="L169" href="source/net/ipv4/netfilter.c#L169">169</a>                                                <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - dataoff, 0);
<a name="L170" href="source/net/ipv4/netfilter.c#L170">170</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L171" href="source/net/ipv4/netfilter.c#L171">171</a>                 return <a href="ident?i=__skb_checksum_complete_head">__skb_checksum_complete_head</a>(<a href="ident?i=skb">skb</a>, dataoff + <a href="ident?i=len">len</a>);
<a name="L172" href="source/net/ipv4/netfilter.c#L172">172</a>         }
<a name="L173" href="source/net/ipv4/netfilter.c#L173">173</a>         return <a href="ident?i=csum">csum</a>;
<a name="L174" href="source/net/ipv4/netfilter.c#L174">174</a> }
<a name="L175" href="source/net/ipv4/netfilter.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/netfilter.c#L176">176</a> static int <a href="ident?i=nf_ip_route">nf_ip_route</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=dst_entry">dst_entry</a> **<a href="ident?i=dst">dst</a>,
<a name="L177" href="source/net/ipv4/netfilter.c#L177">177</a>                        struct <a href="ident?i=flowi">flowi</a> *fl, <a href="ident?i=bool">bool</a> strict <a href="ident?i=__always_unused">__always_unused</a>)
<a name="L178" href="source/net/ipv4/netfilter.c#L178">178</a> {
<a name="L179" href="source/net/ipv4/netfilter.c#L179">179</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl-&gt;u.ip4);
<a name="L180" href="source/net/ipv4/netfilter.c#L180">180</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L181" href="source/net/ipv4/netfilter.c#L181">181</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L182" href="source/net/ipv4/netfilter.c#L182">182</a>         *<a href="ident?i=dst">dst</a> = &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L183" href="source/net/ipv4/netfilter.c#L183">183</a>         return 0;
<a name="L184" href="source/net/ipv4/netfilter.c#L184">184</a> }
<a name="L185" href="source/net/ipv4/netfilter.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/netfilter.c#L186">186</a> static const struct <a href="ident?i=nf_afinfo">nf_afinfo</a> <a href="ident?i=nf_ip_afinfo">nf_ip_afinfo</a> = {
<a name="L187" href="source/net/ipv4/netfilter.c#L187">187</a>         .<a href="ident?i=family">family</a>                 = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L188" href="source/net/ipv4/netfilter.c#L188">188</a>         .<a href="ident?i=checksum">checksum</a>               = <a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>,
<a name="L189" href="source/net/ipv4/netfilter.c#L189">189</a>         .checksum_partial       = <a href="ident?i=nf_ip_checksum_partial">nf_ip_checksum_partial</a>,
<a name="L190" href="source/net/ipv4/netfilter.c#L190">190</a>         .route                  = <a href="ident?i=nf_ip_route">nf_ip_route</a>,
<a name="L191" href="source/net/ipv4/netfilter.c#L191">191</a>         .saveroute              = <a href="ident?i=nf_ip_saveroute">nf_ip_saveroute</a>,
<a name="L192" href="source/net/ipv4/netfilter.c#L192">192</a>         .reroute                = <a href="ident?i=nf_ip_reroute">nf_ip_reroute</a>,
<a name="L193" href="source/net/ipv4/netfilter.c#L193">193</a>         .route_key_size         = sizeof(struct <a href="ident?i=ip_rt_info">ip_rt_info</a>),
<a name="L194" href="source/net/ipv4/netfilter.c#L194">194</a> };
<a name="L195" href="source/net/ipv4/netfilter.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/netfilter.c#L196">196</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipv4_netfilter_init">ipv4_netfilter_init</a>(void)
<a name="L197" href="source/net/ipv4/netfilter.c#L197">197</a> {
<a name="L198" href="source/net/ipv4/netfilter.c#L198">198</a>         return <a href="ident?i=nf_register_afinfo">nf_register_afinfo</a>(&amp;<a href="ident?i=nf_ip_afinfo">nf_ip_afinfo</a>);
<a name="L199" href="source/net/ipv4/netfilter.c#L199">199</a> }
<a name="L200" href="source/net/ipv4/netfilter.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/netfilter.c#L201">201</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ipv4_netfilter_fini">ipv4_netfilter_fini</a>(void)
<a name="L202" href="source/net/ipv4/netfilter.c#L202">202</a> {
<a name="L203" href="source/net/ipv4/netfilter.c#L203">203</a>         <a href="ident?i=nf_unregister_afinfo">nf_unregister_afinfo</a>(&amp;<a href="ident?i=nf_ip_afinfo">nf_ip_afinfo</a>);
<a name="L204" href="source/net/ipv4/netfilter.c#L204">204</a> }
<a name="L205" href="source/net/ipv4/netfilter.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/netfilter.c#L206">206</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ipv4_netfilter_init">ipv4_netfilter_init</a>);
<a name="L207" href="source/net/ipv4/netfilter.c#L207">207</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ipv4_netfilter_fini">ipv4_netfilter_fini</a>);
<a name="L208" href="source/net/ipv4/netfilter.c#L208">208</a> </pre></div><p>
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
