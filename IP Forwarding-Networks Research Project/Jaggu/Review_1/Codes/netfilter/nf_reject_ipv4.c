<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_reject_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_reject_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_reject_ipv4.c">nf_reject_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L1">1</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L2">2</a> <b><i> * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L10">10</a> #include &lt;net/ip.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L11">11</a> #include &lt;net/tcp.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L12">12</a> #include &lt;net/route.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L13">13</a> #include &lt;net/dst.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L14">14</a> #include &lt;net/netfilter/ipv4/nf_reject.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L15">15</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L16">16</a> #include &lt;linux/netfilter_bridge.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L17">17</a> #include &lt;net/netfilter/ipv4/nf_reject.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L19">19</a> const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=nf_reject_ip_tcphdr_get">nf_reject_ip_tcphdr_get</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *oldskb,
 <a name="L20" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L20">20</a>                                              struct <a href="ident?i=tcphdr">tcphdr</a> *_oth, int hook)
 <a name="L21" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L21">21</a> {
 <a name="L22" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L22">22</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *oth;
 <a name="L23" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L24">24</a>         <b><i>/* IP header checks: fragment. */</i></b>
 <a name="L25" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L25">25</a>         if (<a href="ident?i=ip_hdr">ip_hdr</a>(oldskb)-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_OFFSET">IP_OFFSET</a>))
 <a name="L26" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L26">26</a>                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L27" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L28">28</a>         oth = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(oldskb, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(oldskb),
 <a name="L29" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L29">29</a>                                  sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>), _oth);
 <a name="L30" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L30">30</a>         if (oth == <a href="ident?i=NULL">NULL</a>)
 <a name="L31" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L31">31</a>                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L32" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L33">33</a>         <b><i>/* No RST for RST. */</i></b>
 <a name="L34" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L34">34</a>         if (oth-&gt;rst)
 <a name="L35" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L35">35</a>                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L36" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L37">37</a>         <b><i>/* Check checksum */</i></b>
 <a name="L38" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L38">38</a>         if (<a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(oldskb, hook, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(oldskb), <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>))
 <a name="L39" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L39">39</a>                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L40" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L41">41</a>         return oth;
 <a name="L42" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L42">42</a> }
 <a name="L43" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L43">43</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_reject_ip_tcphdr_get">nf_reject_ip_tcphdr_get</a>);
 <a name="L44" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L45">45</a> struct <a href="ident?i=iphdr">iphdr</a> *<a href="ident?i=nf_reject_iphdr_put">nf_reject_iphdr_put</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *nskb,
 <a name="L46" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L46">46</a>                                   const struct <a href="ident?i=sk_buff">sk_buff</a> *oldskb,
 <a name="L47" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L47">47</a>                                   <a href="ident?i=__u8">__u8</a> <a href="ident?i=protocol">protocol</a>, int <a href="ident?i=ttl">ttl</a>)
 <a name="L48" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L48">48</a> {
 <a name="L49" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L49">49</a>         struct <a href="ident?i=iphdr">iphdr</a> *niph, *oiph = <a href="ident?i=ip_hdr">ip_hdr</a>(oldskb);
 <a name="L50" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L51">51</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(nskb);
 <a name="L52" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L52">52</a>         niph = (struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(nskb, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
 <a name="L53" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L53">53</a>         niph-&gt;<a href="ident?i=version">version</a>   = 4;
 <a name="L54" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L54">54</a>         niph-&gt;ihl       = sizeof(struct <a href="ident?i=iphdr">iphdr</a>) / 4;
 <a name="L55" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L55">55</a>         niph-&gt;tos       = 0;
 <a name="L56" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L56">56</a>         niph-&gt;<a href="ident?i=id">id</a>        = 0;
 <a name="L57" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L57">57</a>         niph-&gt;frag_off  = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
 <a name="L58" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L58">58</a>         niph-&gt;<a href="ident?i=protocol">protocol</a>  = <a href="ident?i=protocol">protocol</a>;
 <a name="L59" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L59">59</a>         niph-&gt;<a href="ident?i=check">check</a>     = 0;
 <a name="L60" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L60">60</a>         niph-&gt;<a href="ident?i=saddr">saddr</a>     = oiph-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L61" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L61">61</a>         niph-&gt;<a href="ident?i=daddr">daddr</a>     = oiph-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L62" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L62">62</a>         niph-&gt;<a href="ident?i=ttl">ttl</a>       = <a href="ident?i=ttl">ttl</a>;
 <a name="L63" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L64">64</a>         nskb-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
 <a name="L65" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L66">66</a>         return niph;
 <a name="L67" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L68">68</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_reject_iphdr_put">nf_reject_iphdr_put</a>);
 <a name="L69" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L70">70</a> void <a href="ident?i=nf_reject_ip_tcphdr_put">nf_reject_ip_tcphdr_put</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *nskb, const struct <a href="ident?i=sk_buff">sk_buff</a> *oldskb,
 <a name="L71" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L71">71</a>                           const struct <a href="ident?i=tcphdr">tcphdr</a> *oth)
 <a name="L72" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L72">72</a> {
 <a name="L73" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L73">73</a>         struct <a href="ident?i=iphdr">iphdr</a> *niph = <a href="ident?i=ip_hdr">ip_hdr</a>(nskb);
 <a name="L74" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L74">74</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *tcph;
 <a name="L75" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L76">76</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(nskb);
 <a name="L77" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L77">77</a>         tcph = (struct <a href="ident?i=tcphdr">tcphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(nskb, sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>));
 <a name="L78" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L78">78</a>         <a href="ident?i=memset">memset</a>(tcph, 0, sizeof(*tcph));
 <a name="L79" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L79">79</a>         tcph-&gt;source    = oth-&gt;<a href="ident?i=dest">dest</a>;
 <a name="L80" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L80">80</a>         tcph-&gt;<a href="ident?i=dest">dest</a>      = oth-&gt;source;
 <a name="L81" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L81">81</a>         tcph-&gt;doff      = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) / 4;
 <a name="L82" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L83">83</a>         if (oth-&gt;ack) {
 <a name="L84" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L84">84</a>                 tcph-&gt;<a href="ident?i=seq">seq</a> = oth-&gt;ack_seq;
 <a name="L85" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L85">85</a>         } else {
 <a name="L86" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L86">86</a>                 tcph-&gt;ack_seq = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(oth-&gt;<a href="ident?i=seq">seq</a>) + oth-&gt;syn + oth-&gt;fin +
 <a name="L87" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L87">87</a>                                       oldskb-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(oldskb) -
 <a name="L88" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L88">88</a>                                       (oth-&gt;doff &lt;&lt; 2));
 <a name="L89" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L89">89</a>                 tcph-&gt;ack = 1;
 <a name="L90" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L90">90</a>         }
 <a name="L91" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L92">92</a>         tcph-&gt;rst       = 1;
 <a name="L93" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L93">93</a>         tcph-&gt;<a href="ident?i=check">check</a> = ~tcp_v4_check(sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>), niph-&gt;<a href="ident?i=saddr">saddr</a>,
 <a name="L94" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L94">94</a>                                     niph-&gt;<a href="ident?i=daddr">daddr</a>, 0);
 <a name="L95" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L95">95</a>         nskb-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
 <a name="L96" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L96">96</a>         nskb-&gt;csum_start = (unsigned char *)tcph - nskb-&gt;<a href="ident?i=head">head</a>;
 <a name="L97" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L97">97</a>         nskb-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tcphdr">tcphdr</a>, <a href="ident?i=check">check</a>);
 <a name="L98" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L98">98</a> }
 <a name="L99" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L99">99</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_reject_ip_tcphdr_put">nf_reject_ip_tcphdr_put</a>);
<a name="L100" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L101">101</a> <b><i>/* Send RST reply */</i></b>
<a name="L102" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L102">102</a> void <a href="ident?i=nf_send_reset">nf_send_reset</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *oldskb, int hook)
<a name="L103" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L104">104</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
<a name="L105" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L105">105</a>         const struct <a href="ident?i=iphdr">iphdr</a> *oiph;
<a name="L106" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L106">106</a>         struct <a href="ident?i=iphdr">iphdr</a> *niph;
<a name="L107" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L107">107</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *oth;
<a name="L108" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L108">108</a>         struct <a href="ident?i=tcphdr">tcphdr</a> _oth;
<a name="L109" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L110">110</a>         oth = <a href="ident?i=nf_reject_ip_tcphdr_get">nf_reject_ip_tcphdr_get</a>(oldskb, &amp;_oth, hook);
<a name="L111" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L111">111</a>         if (!oth)
<a name="L112" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L112">112</a>                 return;
<a name="L113" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L114">114</a>         if (<a href="ident?i=skb_rtable">skb_rtable</a>(oldskb)-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>))
<a name="L115" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L115">115</a>                 return;
<a name="L116" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L117">117</a>         oiph = <a href="ident?i=ip_hdr">ip_hdr</a>(oldskb);
<a name="L118" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L119">119</a>         nskb = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) +
<a name="L120" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L120">120</a>                          <a href="ident?i=LL_MAX_HEADER">LL_MAX_HEADER</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L121" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L121">121</a>         if (!nskb)
<a name="L122" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L122">122</a>                 return;
<a name="L123" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L124">124</a>         <b><i>/* ip_route_me_harder expects skb-&gt;dst to be set */</i></b>
<a name="L125" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L125">125</a>         <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(nskb, <a href="ident?i=skb_dst">skb_dst</a>(oldskb));
<a name="L126" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L127">127</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(nskb, <a href="ident?i=LL_MAX_HEADER">LL_MAX_HEADER</a>);
<a name="L128" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L128">128</a>         niph = <a href="ident?i=nf_reject_iphdr_put">nf_reject_iphdr_put</a>(nskb, oldskb, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
<a name="L129" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L129">129</a>                                    <a href="ident?i=ip4_dst_hoplimit">ip4_dst_hoplimit</a>(<a href="ident?i=skb_dst">skb_dst</a>(nskb)));
<a name="L130" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L130">130</a>         <a href="ident?i=nf_reject_ip_tcphdr_put">nf_reject_ip_tcphdr_put</a>(nskb, oldskb, oth);
<a name="L131" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L132">132</a>         if (<a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(nskb, RTN_UNSPEC))
<a name="L133" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L133">133</a>                 goto free_nskb;
<a name="L134" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L135">135</a>         <b><i>/* "Never happens" */</i></b>
<a name="L136" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L136">136</a>         if (nskb-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=skb_dst">skb_dst</a>(nskb)))
<a name="L137" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L137">137</a>                 goto free_nskb;
<a name="L138" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L139">139</a>         <a href="ident?i=nf_ct_attach">nf_ct_attach</a>(nskb, oldskb);
<a name="L140" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L141">141</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_BRIDGE_NETFILTER)
<a name="L142" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L142">142</a>         <b><i>/* If we use ip_local_out for bridged traffic, the MAC source on</i></b>
<a name="L143" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L143">143</a> <b><i>         * the RST will be ours, instead of the destination's.  This confuses</i></b>
<a name="L144" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L144">144</a> <b><i>         * some routers/firewalls, and they drop the packet.  So we need to</i></b>
<a name="L145" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L145">145</a> <b><i>         * build the eth header using the original destination's MAC as the</i></b>
<a name="L146" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L146">146</a> <b><i>         * source, and send the RST packet directly.</i></b>
<a name="L147" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L147">147</a> <b><i>         */</i></b>
<a name="L148" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L148">148</a>         if (oldskb-&gt;nf_bridge) {
<a name="L149" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L149">149</a>                 struct <a href="ident?i=ethhdr">ethhdr</a> *oeth = <a href="ident?i=eth_hdr">eth_hdr</a>(oldskb);
<a name="L150" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L151">151</a>                 nskb-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=nf_bridge_get_physindev">nf_bridge_get_physindev</a>(oldskb);
<a name="L152" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L152">152</a>                 niph-&gt;tot_len = <a href="ident?i=htons">htons</a>(nskb-&gt;<a href="ident?i=len">len</a>);
<a name="L153" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L153">153</a>                 <a href="ident?i=ip_send_check">ip_send_check</a>(niph);
<a name="L154" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L154">154</a>                 if (<a href="ident?i=dev_hard_header">dev_hard_header</a>(nskb, nskb-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=ntohs">ntohs</a>(nskb-&gt;<a href="ident?i=protocol">protocol</a>),
<a name="L155" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L155">155</a>                                     oeth-&gt;h_source, oeth-&gt;h_dest, nskb-&gt;<a href="ident?i=len">len</a>) &lt; 0)
<a name="L156" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L156">156</a>                         goto free_nskb;
<a name="L157" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L157">157</a>                 <a href="ident?i=dev_queue_xmit">dev_queue_xmit</a>(nskb);
<a name="L158" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L158">158</a>         } else
<a name="L159" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L159">159</a> #endif
<a name="L160" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L160">160</a>                 <a href="ident?i=ip_local_out">ip_local_out</a>(nskb);
<a name="L161" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L162">162</a>         return;
<a name="L163" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L164">164</a>  free_nskb:
<a name="L165" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L165">165</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(nskb);
<a name="L166" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L166">166</a> }
<a name="L167" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L167">167</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_send_reset">nf_send_reset</a>);
<a name="L168" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L169">169</a> void <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *skb_in, int <a href="ident?i=code">code</a>, int hook)
<a name="L170" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L170">170</a> {
<a name="L171" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L171">171</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(skb_in);
<a name="L172" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L172">172</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=proto">proto</a>;
<a name="L173" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L174">174</a>         if (skb_in-&gt;csum_bad || iph-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_OFFSET">IP_OFFSET</a>))
<a name="L175" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L175">175</a>                 return;
<a name="L176" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L177">177</a>         if (<a href="ident?i=skb_csum_unnecessary">skb_csum_unnecessary</a>(skb_in)) {
<a name="L178" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L178">178</a>                 <a href="ident?i=icmp_send">icmp_send</a>(skb_in, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=code">code</a>, 0);
<a name="L179" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L179">179</a>                 return;
<a name="L180" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L180">180</a>         }
<a name="L181" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L182">182</a>         if (iph-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> || iph-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>)
<a name="L183" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L183">183</a>                 <a href="ident?i=proto">proto</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L184" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L184">184</a>         else
<a name="L185" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L185">185</a>                 <a href="ident?i=proto">proto</a> = 0;
<a name="L186" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L187">187</a>         if (<a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(skb_in, hook, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(skb_in), <a href="ident?i=proto">proto</a>) == 0)
<a name="L188" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L188">188</a>                 <a href="ident?i=icmp_send">icmp_send</a>(skb_in, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=code">code</a>, 0);
<a name="L189" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L189">189</a> }
<a name="L190" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L190">190</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_send_unreach">nf_send_unreach</a>);
<a name="L191" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L192">192</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L193" href="source/net/ipv4/netfilter/nf_reject_ipv4.c#L193">193</a> </pre></div><p>
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
