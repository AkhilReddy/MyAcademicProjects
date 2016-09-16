<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_h323.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_h323.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_h323.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_h323.c">nf_nat_h323.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_h323.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_h323.c#L2">2</a> <b><i> * H.323 extension for NAT alteration.</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_h323.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_h323.c#L4">4</a> <b><i> * Copyright (c) 2006 Jing Min Zhao &lt;zhaojingmin@users.sourceforge.net&gt;</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_h323.c#L5">5</a> <b><i> * Copyright (c) 2006-2012 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_h323.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_h323.c#L7">7</a> <b><i> * This source code is licensed under General Public License version 2.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_h323.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_h323.c#L9">9</a> <b><i> * Based on the 'brute force' H.323 NAT module by</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_h323.c#L10">10</a> <b><i> * Jozsef Kadlecsik &lt;kadlec@blackhole.kfki.hu&gt;</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_h323.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_h323.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_h323.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_h323.c#L14">14</a> #include &lt;linux/tcp.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_h323.c#L15">15</a> #include &lt;net/tcp.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_h323.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_h323.c#L17">17</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_h323.c#L18">18</a> #include &lt;net/netfilter/nf_nat_helper.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_h323.c#L19">19</a> #include &lt;net/netfilter/nf_conntrack_helper.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_h323.c#L20">20</a> #include &lt;net/netfilter/nf_conntrack_expect.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_h323.c#L21">21</a> #include &lt;linux/netfilter/nf_conntrack_h323.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_h323.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_h323.c#L23">23</a> <b><i>/****************************************************************************/</i></b>
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_h323.c#L24">24</a> static int <a href="ident?i=set_addr">set_addr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int protoff,
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_h323.c#L25">25</a>                     unsigned char **<a href="ident?i=data">data</a>, int dataoff,
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_h323.c#L26">26</a>                     unsigned int addroff, <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>)
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_h323.c#L27">27</a> {
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_h323.c#L28">28</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_h323.c#L29">29</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_h323.c#L30">30</a>         struct {
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_h323.c#L31">31</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a>;
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_h323.c#L32">32</a>                 <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>;
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_h323.c#L33">33</a>         } <a href="ident?i=__attribute__">__attribute__</a> ((__packed__)) <a href="ident?i=buf">buf</a>;
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_h323.c#L34">34</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_h323.c#L35">35</a>         struct <a href="ident?i=tcphdr">tcphdr</a> _tcph;
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_h323.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_h323.c#L37">37</a>         <a href="ident?i=buf">buf</a>.<a href="ident?i=ip">ip</a> = <a href="ident?i=ip">ip</a>;
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_h323.c#L38">38</a>         <a href="ident?i=buf">buf</a>.<a href="ident?i=port">port</a> = <a href="ident?i=port">port</a>;
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_h323.c#L39">39</a>         addroff += dataoff;
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_h323.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_h323.c#L41">41</a>         if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>) {
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_h323.c#L42">42</a>                 if (!<a href="ident?i=nf_nat_mangle_tcp_packet">nf_nat_mangle_tcp_packet</a>(<a href="ident?i=skb">skb</a>, ct, ctinfo,
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_h323.c#L43">43</a>                                               protoff, addroff, sizeof(<a href="ident?i=buf">buf</a>),
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_h323.c#L44">44</a>                                               (char *) &amp;<a href="ident?i=buf">buf</a>, sizeof(<a href="ident?i=buf">buf</a>))) {
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_h323.c#L45">45</a>                         <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_h323: nf_nat_mangle_tcp_packet error\n"</i>);
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_h323.c#L46">46</a>                         return -1;
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_h323.c#L47">47</a>                 }
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_h323.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_h323.c#L49">49</a>                 <b><i>/* Relocate data pointer */</i></b>
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_h323.c#L50">50</a>                 <a href="ident?i=th">th</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>),
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_h323.c#L51">51</a>                                         sizeof(_tcph), &amp;_tcph);
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_h323.c#L52">52</a>                 if (<a href="ident?i=th">th</a> == <a href="ident?i=NULL">NULL</a>)
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_h323.c#L53">53</a>                         return -1;
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_h323.c#L54">54</a>                 *<a href="ident?i=data">data</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=th">th</a>-&gt;doff * 4 + dataoff;
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_h323.c#L55">55</a>         } else {
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_h323.c#L56">56</a>                 if (!<a href="ident?i=nf_nat_mangle_udp_packet">nf_nat_mangle_udp_packet</a>(<a href="ident?i=skb">skb</a>, ct, ctinfo,
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_h323.c#L57">57</a>                                               protoff, addroff, sizeof(<a href="ident?i=buf">buf</a>),
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_h323.c#L58">58</a>                                               (char *) &amp;<a href="ident?i=buf">buf</a>, sizeof(<a href="ident?i=buf">buf</a>))) {
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_h323.c#L59">59</a>                         <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_h323: nf_nat_mangle_udp_packet error\n"</i>);
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_h323.c#L60">60</a>                         return -1;
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_h323.c#L61">61</a>                 }
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_h323.c#L62">62</a>                 <b><i>/* nf_nat_mangle_udp_packet uses skb_make_writable() to copy</i></b>
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_h323.c#L63">63</a> <b><i>                 * or pull everything in a linear buffer, so we can safely</i></b>
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_h323.c#L64">64</a> <b><i>                 * use the skb pointers now */</i></b>
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_h323.c#L65">65</a>                 *<a href="ident?i=data">data</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) + sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_h323.c#L66">66</a>         }
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_h323.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_h323.c#L68">68</a>         return 0;
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_h323.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_h323.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_h323.c#L71">71</a> <b><i>/****************************************************************************/</i></b>
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_h323.c#L72">72</a> static int <a href="ident?i=set_h225_addr">set_h225_addr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int protoff,
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_h323.c#L73">73</a>                          unsigned char **<a href="ident?i=data">data</a>, int dataoff,
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_h323.c#L74">74</a>                          <a href="ident?i=TransportAddress">TransportAddress</a> *taddr,
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_h323.c#L75">75</a>                          union <a href="ident?i=nf_inet_addr">nf_inet_addr</a> *<a href="ident?i=addr">addr</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>)
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_h323.c#L76">76</a> {
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_h323.c#L77">77</a>         return <a href="ident?i=set_addr">set_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, dataoff, taddr-&gt;ipAddress.<a href="ident?i=ip">ip</a>,
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_h323.c#L78">78</a>                         <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=ip">ip</a>, <a href="ident?i=port">port</a>);
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_h323.c#L79">79</a> }
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_h323.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_h323.c#L81">81</a> <b><i>/****************************************************************************/</i></b>
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_h323.c#L82">82</a> static int <a href="ident?i=set_h245_addr">set_h245_addr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned protoff,
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_h323.c#L83">83</a>                          unsigned char **<a href="ident?i=data">data</a>, int dataoff,
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_h323.c#L84">84</a>                          <a href="ident?i=H245_TransportAddress">H245_TransportAddress</a> *taddr,
 <a name="L85" href="source/net/ipv4/netfilter/nf_nat_h323.c#L85">85</a>                          union <a href="ident?i=nf_inet_addr">nf_inet_addr</a> *<a href="ident?i=addr">addr</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>)
 <a name="L86" href="source/net/ipv4/netfilter/nf_nat_h323.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/netfilter/nf_nat_h323.c#L87">87</a>         return <a href="ident?i=set_addr">set_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, dataoff,
 <a name="L88" href="source/net/ipv4/netfilter/nf_nat_h323.c#L88">88</a>                         taddr-&gt;unicastAddress.iPAddress.network,
 <a name="L89" href="source/net/ipv4/netfilter/nf_nat_h323.c#L89">89</a>                         <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=ip">ip</a>, <a href="ident?i=port">port</a>);
 <a name="L90" href="source/net/ipv4/netfilter/nf_nat_h323.c#L90">90</a> }
 <a name="L91" href="source/net/ipv4/netfilter/nf_nat_h323.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/netfilter/nf_nat_h323.c#L92">92</a> <b><i>/****************************************************************************/</i></b>
 <a name="L93" href="source/net/ipv4/netfilter/nf_nat_h323.c#L93">93</a> static int <a href="ident?i=set_sig_addr">set_sig_addr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
 <a name="L94" href="source/net/ipv4/netfilter/nf_nat_h323.c#L94">94</a>                         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
 <a name="L95" href="source/net/ipv4/netfilter/nf_nat_h323.c#L95">95</a>                         unsigned int protoff, unsigned char **<a href="ident?i=data">data</a>,
 <a name="L96" href="source/net/ipv4/netfilter/nf_nat_h323.c#L96">96</a>                         <a href="ident?i=TransportAddress">TransportAddress</a> *taddr, int <a href="ident?i=count">count</a>)
 <a name="L97" href="source/net/ipv4/netfilter/nf_nat_h323.c#L97">97</a> {
 <a name="L98" href="source/net/ipv4/netfilter/nf_nat_h323.c#L98">98</a>         const struct <a href="ident?i=nf_ct_h323_master">nf_ct_h323_master</a> *<a href="ident?i=info">info</a> = <a href="ident?i=nfct_help_data">nfct_help_data</a>(ct);
 <a name="L99" href="source/net/ipv4/netfilter/nf_nat_h323.c#L99">99</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L100" href="source/net/ipv4/netfilter/nf_nat_h323.c#L100">100</a>         int <a href="ident?i=i">i</a>;
<a name="L101" href="source/net/ipv4/netfilter/nf_nat_h323.c#L101">101</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>;
<a name="L102" href="source/net/ipv4/netfilter/nf_nat_h323.c#L102">102</a>         union <a href="ident?i=nf_inet_addr">nf_inet_addr</a> <a href="ident?i=addr">addr</a>;
<a name="L103" href="source/net/ipv4/netfilter/nf_nat_h323.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/netfilter/nf_nat_h323.c#L104">104</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=count">count</a>; <a href="ident?i=i">i</a>++) {
<a name="L105" href="source/net/ipv4/netfilter/nf_nat_h323.c#L105">105</a>                 if (<a href="ident?i=get_h225_addr">get_h225_addr</a>(ct, *<a href="ident?i=data">data</a>, &amp;taddr[<a href="ident?i=i">i</a>], &amp;<a href="ident?i=addr">addr</a>, &amp;<a href="ident?i=port">port</a>)) {
<a name="L106" href="source/net/ipv4/netfilter/nf_nat_h323.c#L106">106</a>                         if (<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a> == ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> &amp;&amp;
<a name="L107" href="source/net/ipv4/netfilter/nf_nat_h323.c#L107">107</a>                             <a href="ident?i=port">port</a> == <a href="ident?i=info">info</a>-&gt;sig_port[<a href="ident?i=dir">dir</a>]) {
<a name="L108" href="source/net/ipv4/netfilter/nf_nat_h323.c#L108">108</a>                                 <b><i>/* GW-&gt;GK */</i></b>
<a name="L109" href="source/net/ipv4/netfilter/nf_nat_h323.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/netfilter/nf_nat_h323.c#L110">110</a>                                 <b><i>/* Fix for Gnomemeeting */</i></b>
<a name="L111" href="source/net/ipv4/netfilter/nf_nat_h323.c#L111">111</a>                                 if (<a href="ident?i=i">i</a> &gt; 0 &amp;&amp;
<a name="L112" href="source/net/ipv4/netfilter/nf_nat_h323.c#L112">112</a>                                     <a href="ident?i=get_h225_addr">get_h225_addr</a>(ct, *<a href="ident?i=data">data</a>, &amp;taddr[0],
<a name="L113" href="source/net/ipv4/netfilter/nf_nat_h323.c#L113">113</a>                                                   &amp;<a href="ident?i=addr">addr</a>, &amp;<a href="ident?i=port">port</a>) &amp;&amp;
<a name="L114" href="source/net/ipv4/netfilter/nf_nat_h323.c#L114">114</a>                                     (<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a>) &amp; 0xff000000) == 0x7f000000)
<a name="L115" href="source/net/ipv4/netfilter/nf_nat_h323.c#L115">115</a>                                         <a href="ident?i=i">i</a> = 0;
<a name="L116" href="source/net/ipv4/netfilter/nf_nat_h323.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/netfilter/nf_nat_h323.c#L117">117</a>                                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_ras: set signal address %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L118" href="source/net/ipv4/netfilter/nf_nat_h323.c#L118">118</a>                                          &amp;<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a>, <a href="ident?i=port">port</a>,
<a name="L119" href="source/net/ipv4/netfilter/nf_nat_h323.c#L119">119</a>                                          &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L120" href="source/net/ipv4/netfilter/nf_nat_h323.c#L120">120</a>                                          <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L121" href="source/net/ipv4/netfilter/nf_nat_h323.c#L121">121</a>                                 return <a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, 0,
<a name="L122" href="source/net/ipv4/netfilter/nf_nat_h323.c#L122">122</a>                                                      &amp;taddr[<a href="ident?i=i">i</a>],
<a name="L123" href="source/net/ipv4/netfilter/nf_nat_h323.c#L123">123</a>                                                      &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].
<a name="L124" href="source/net/ipv4/netfilter/nf_nat_h323.c#L124">124</a>                                                      tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L125" href="source/net/ipv4/netfilter/nf_nat_h323.c#L125">125</a>                                                      <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L126" href="source/net/ipv4/netfilter/nf_nat_h323.c#L126">126</a>                         } else if (<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a> == ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> &amp;&amp;
<a name="L127" href="source/net/ipv4/netfilter/nf_nat_h323.c#L127">127</a>                                    <a href="ident?i=port">port</a> == <a href="ident?i=info">info</a>-&gt;sig_port[<a href="ident?i=dir">dir</a>]) {
<a name="L128" href="source/net/ipv4/netfilter/nf_nat_h323.c#L128">128</a>                                 <b><i>/* GK-&gt;GW */</i></b>
<a name="L129" href="source/net/ipv4/netfilter/nf_nat_h323.c#L129">129</a>                                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_ras: set signal address %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L130" href="source/net/ipv4/netfilter/nf_nat_h323.c#L130">130</a>                                          &amp;<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a>, <a href="ident?i=port">port</a>,
<a name="L131" href="source/net/ipv4/netfilter/nf_nat_h323.c#L131">131</a>                                          &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L132" href="source/net/ipv4/netfilter/nf_nat_h323.c#L132">132</a>                                          <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L133" href="source/net/ipv4/netfilter/nf_nat_h323.c#L133">133</a>                                 return <a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, 0,
<a name="L134" href="source/net/ipv4/netfilter/nf_nat_h323.c#L134">134</a>                                                      &amp;taddr[<a href="ident?i=i">i</a>],
<a name="L135" href="source/net/ipv4/netfilter/nf_nat_h323.c#L135">135</a>                                                      &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].
<a name="L136" href="source/net/ipv4/netfilter/nf_nat_h323.c#L136">136</a>                                                      tuple.<a href="ident?i=src">src</a>.u3,
<a name="L137" href="source/net/ipv4/netfilter/nf_nat_h323.c#L137">137</a>                                                      <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L138" href="source/net/ipv4/netfilter/nf_nat_h323.c#L138">138</a>                         }
<a name="L139" href="source/net/ipv4/netfilter/nf_nat_h323.c#L139">139</a>                 }
<a name="L140" href="source/net/ipv4/netfilter/nf_nat_h323.c#L140">140</a>         }
<a name="L141" href="source/net/ipv4/netfilter/nf_nat_h323.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/netfilter/nf_nat_h323.c#L142">142</a>         return 0;
<a name="L143" href="source/net/ipv4/netfilter/nf_nat_h323.c#L143">143</a> }
<a name="L144" href="source/net/ipv4/netfilter/nf_nat_h323.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/netfilter/nf_nat_h323.c#L145">145</a> <b><i>/****************************************************************************/</i></b>
<a name="L146" href="source/net/ipv4/netfilter/nf_nat_h323.c#L146">146</a> static int <a href="ident?i=set_ras_addr">set_ras_addr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L147" href="source/net/ipv4/netfilter/nf_nat_h323.c#L147">147</a>                         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L148" href="source/net/ipv4/netfilter/nf_nat_h323.c#L148">148</a>                         unsigned int protoff, unsigned char **<a href="ident?i=data">data</a>,
<a name="L149" href="source/net/ipv4/netfilter/nf_nat_h323.c#L149">149</a>                         <a href="ident?i=TransportAddress">TransportAddress</a> *taddr, int <a href="ident?i=count">count</a>)
<a name="L150" href="source/net/ipv4/netfilter/nf_nat_h323.c#L150">150</a> {
<a name="L151" href="source/net/ipv4/netfilter/nf_nat_h323.c#L151">151</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L152" href="source/net/ipv4/netfilter/nf_nat_h323.c#L152">152</a>         int <a href="ident?i=i">i</a>;
<a name="L153" href="source/net/ipv4/netfilter/nf_nat_h323.c#L153">153</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>;
<a name="L154" href="source/net/ipv4/netfilter/nf_nat_h323.c#L154">154</a>         union <a href="ident?i=nf_inet_addr">nf_inet_addr</a> <a href="ident?i=addr">addr</a>;
<a name="L155" href="source/net/ipv4/netfilter/nf_nat_h323.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/netfilter/nf_nat_h323.c#L156">156</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=count">count</a>; <a href="ident?i=i">i</a>++) {
<a name="L157" href="source/net/ipv4/netfilter/nf_nat_h323.c#L157">157</a>                 if (<a href="ident?i=get_h225_addr">get_h225_addr</a>(ct, *<a href="ident?i=data">data</a>, &amp;taddr[<a href="ident?i=i">i</a>], &amp;<a href="ident?i=addr">addr</a>, &amp;<a href="ident?i=port">port</a>) &amp;&amp;
<a name="L158" href="source/net/ipv4/netfilter/nf_nat_h323.c#L158">158</a>                     <a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a> == ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> &amp;&amp;
<a name="L159" href="source/net/ipv4/netfilter/nf_nat_h323.c#L159">159</a>                     <a href="ident?i=port">port</a> == ct-&gt;tuplehash[<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u.udp.<a href="ident?i=port">port</a>) {
<a name="L160" href="source/net/ipv4/netfilter/nf_nat_h323.c#L160">160</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_ras: set rasAddress %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L161" href="source/net/ipv4/netfilter/nf_nat_h323.c#L161">161</a>                                  &amp;<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=port">port</a>),
<a name="L162" href="source/net/ipv4/netfilter/nf_nat_h323.c#L162">162</a>                                  &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L163" href="source/net/ipv4/netfilter/nf_nat_h323.c#L163">163</a>                                  <a href="ident?i=ntohs">ntohs</a>(ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>));
<a name="L164" href="source/net/ipv4/netfilter/nf_nat_h323.c#L164">164</a>                         return <a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, 0, &amp;taddr[<a href="ident?i=i">i</a>],
<a name="L165" href="source/net/ipv4/netfilter/nf_nat_h323.c#L165">165</a>                                              &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L166" href="source/net/ipv4/netfilter/nf_nat_h323.c#L166">166</a>                                              ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.
<a name="L167" href="source/net/ipv4/netfilter/nf_nat_h323.c#L167">167</a>                                                                 <a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>);
<a name="L168" href="source/net/ipv4/netfilter/nf_nat_h323.c#L168">168</a>                 }
<a name="L169" href="source/net/ipv4/netfilter/nf_nat_h323.c#L169">169</a>         }
<a name="L170" href="source/net/ipv4/netfilter/nf_nat_h323.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/netfilter/nf_nat_h323.c#L171">171</a>         return 0;
<a name="L172" href="source/net/ipv4/netfilter/nf_nat_h323.c#L172">172</a> }
<a name="L173" href="source/net/ipv4/netfilter/nf_nat_h323.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/netfilter/nf_nat_h323.c#L174">174</a> <b><i>/****************************************************************************/</i></b>
<a name="L175" href="source/net/ipv4/netfilter/nf_nat_h323.c#L175">175</a> static int <a href="ident?i=nat_rtp_rtcp">nat_rtp_rtcp</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L176" href="source/net/ipv4/netfilter/nf_nat_h323.c#L176">176</a>                         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L177" href="source/net/ipv4/netfilter/nf_nat_h323.c#L177">177</a>                         unsigned int protoff, unsigned char **<a href="ident?i=data">data</a>, int dataoff,
<a name="L178" href="source/net/ipv4/netfilter/nf_nat_h323.c#L178">178</a>                         <a href="ident?i=H245_TransportAddress">H245_TransportAddress</a> *taddr,
<a name="L179" href="source/net/ipv4/netfilter/nf_nat_h323.c#L179">179</a>                         <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>, <a href="ident?i=__be16">__be16</a> rtp_port,
<a name="L180" href="source/net/ipv4/netfilter/nf_nat_h323.c#L180">180</a>                         struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *rtp_exp,
<a name="L181" href="source/net/ipv4/netfilter/nf_nat_h323.c#L181">181</a>                         struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *rtcp_exp)
<a name="L182" href="source/net/ipv4/netfilter/nf_nat_h323.c#L182">182</a> {
<a name="L183" href="source/net/ipv4/netfilter/nf_nat_h323.c#L183">183</a>         struct <a href="ident?i=nf_ct_h323_master">nf_ct_h323_master</a> *<a href="ident?i=info">info</a> = <a href="ident?i=nfct_help_data">nfct_help_data</a>(ct);
<a name="L184" href="source/net/ipv4/netfilter/nf_nat_h323.c#L184">184</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L185" href="source/net/ipv4/netfilter/nf_nat_h323.c#L185">185</a>         int <a href="ident?i=i">i</a>;
<a name="L186" href="source/net/ipv4/netfilter/nf_nat_h323.c#L186">186</a>         <a href="ident?i=u_int16_t">u_int16_t</a> nated_port;
<a name="L187" href="source/net/ipv4/netfilter/nf_nat_h323.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/netfilter/nf_nat_h323.c#L188">188</a>         <b><i>/* Set expectations for NAT */</i></b>
<a name="L189" href="source/net/ipv4/netfilter/nf_nat_h323.c#L189">189</a>         rtp_exp-&gt;saved_proto.udp.<a href="ident?i=port">port</a> = rtp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>;
<a name="L190" href="source/net/ipv4/netfilter/nf_nat_h323.c#L190">190</a>         rtp_exp-&gt;expectfn = <a href="ident?i=nf_nat_follow_master">nf_nat_follow_master</a>;
<a name="L191" href="source/net/ipv4/netfilter/nf_nat_h323.c#L191">191</a>         rtp_exp-&gt;<a href="ident?i=dir">dir</a> = !<a href="ident?i=dir">dir</a>;
<a name="L192" href="source/net/ipv4/netfilter/nf_nat_h323.c#L192">192</a>         rtcp_exp-&gt;saved_proto.udp.<a href="ident?i=port">port</a> = rtcp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>;
<a name="L193" href="source/net/ipv4/netfilter/nf_nat_h323.c#L193">193</a>         rtcp_exp-&gt;expectfn = <a href="ident?i=nf_nat_follow_master">nf_nat_follow_master</a>;
<a name="L194" href="source/net/ipv4/netfilter/nf_nat_h323.c#L194">194</a>         rtcp_exp-&gt;<a href="ident?i=dir">dir</a> = !<a href="ident?i=dir">dir</a>;
<a name="L195" href="source/net/ipv4/netfilter/nf_nat_h323.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/netfilter/nf_nat_h323.c#L196">196</a>         <b><i>/* Lookup existing expects */</i></b>
<a name="L197" href="source/net/ipv4/netfilter/nf_nat_h323.c#L197">197</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=H323_RTP_CHANNEL_MAX">H323_RTP_CHANNEL_MAX</a>; <a href="ident?i=i">i</a>++) {
<a name="L198" href="source/net/ipv4/netfilter/nf_nat_h323.c#L198">198</a>                 if (<a href="ident?i=info">info</a>-&gt;rtp_port[<a href="ident?i=i">i</a>][<a href="ident?i=dir">dir</a>] == rtp_port) {
<a name="L199" href="source/net/ipv4/netfilter/nf_nat_h323.c#L199">199</a>                         <b><i>/* Expected */</i></b>
<a name="L200" href="source/net/ipv4/netfilter/nf_nat_h323.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/netfilter/nf_nat_h323.c#L201">201</a>                         <b><i>/* Use allocated ports first. This will refresh</i></b>
<a name="L202" href="source/net/ipv4/netfilter/nf_nat_h323.c#L202">202</a> <b><i>                         * the expects */</i></b>
<a name="L203" href="source/net/ipv4/netfilter/nf_nat_h323.c#L203">203</a>                         rtp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a> = <a href="ident?i=info">info</a>-&gt;rtp_port[<a href="ident?i=i">i</a>][<a href="ident?i=dir">dir</a>];
<a name="L204" href="source/net/ipv4/netfilter/nf_nat_h323.c#L204">204</a>                         rtcp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a> =
<a name="L205" href="source/net/ipv4/netfilter/nf_nat_h323.c#L205">205</a>                             <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=info">info</a>-&gt;rtp_port[<a href="ident?i=i">i</a>][<a href="ident?i=dir">dir</a>]) + 1);
<a name="L206" href="source/net/ipv4/netfilter/nf_nat_h323.c#L206">206</a>                         break;
<a name="L207" href="source/net/ipv4/netfilter/nf_nat_h323.c#L207">207</a>                 } else if (<a href="ident?i=info">info</a>-&gt;rtp_port[<a href="ident?i=i">i</a>][<a href="ident?i=dir">dir</a>] == 0) {
<a name="L208" href="source/net/ipv4/netfilter/nf_nat_h323.c#L208">208</a>                         <b><i>/* Not expected */</i></b>
<a name="L209" href="source/net/ipv4/netfilter/nf_nat_h323.c#L209">209</a>                         break;
<a name="L210" href="source/net/ipv4/netfilter/nf_nat_h323.c#L210">210</a>                 }
<a name="L211" href="source/net/ipv4/netfilter/nf_nat_h323.c#L211">211</a>         }
<a name="L212" href="source/net/ipv4/netfilter/nf_nat_h323.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/netfilter/nf_nat_h323.c#L213">213</a>         <b><i>/* Run out of expectations */</i></b>
<a name="L214" href="source/net/ipv4/netfilter/nf_nat_h323.c#L214">214</a>         if (<a href="ident?i=i">i</a> &gt;= <a href="ident?i=H323_RTP_CHANNEL_MAX">H323_RTP_CHANNEL_MAX</a>) {
<a name="L215" href="source/net/ipv4/netfilter/nf_nat_h323.c#L215">215</a>                 <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_h323: out of expectations\n"</i>);
<a name="L216" href="source/net/ipv4/netfilter/nf_nat_h323.c#L216">216</a>                 return 0;
<a name="L217" href="source/net/ipv4/netfilter/nf_nat_h323.c#L217">217</a>         }
<a name="L218" href="source/net/ipv4/netfilter/nf_nat_h323.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/netfilter/nf_nat_h323.c#L219">219</a>         <b><i>/* Try to get a pair of ports. */</i></b>
<a name="L220" href="source/net/ipv4/netfilter/nf_nat_h323.c#L220">220</a>         for (nated_port = <a href="ident?i=ntohs">ntohs</a>(rtp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>);
<a name="L221" href="source/net/ipv4/netfilter/nf_nat_h323.c#L221">221</a>              nated_port != 0; nated_port += 2) {
<a name="L222" href="source/net/ipv4/netfilter/nf_nat_h323.c#L222">222</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L223" href="source/net/ipv4/netfilter/nf_nat_h323.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/netfilter/nf_nat_h323.c#L224">224</a>                 rtp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a> = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L225" href="source/net/ipv4/netfilter/nf_nat_h323.c#L225">225</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_expect_related">nf_ct_expect_related</a>(rtp_exp);
<a name="L226" href="source/net/ipv4/netfilter/nf_nat_h323.c#L226">226</a>                 if (<a href="ident?i=ret">ret</a> == 0) {
<a name="L227" href="source/net/ipv4/netfilter/nf_nat_h323.c#L227">227</a>                         rtcp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a> =
<a name="L228" href="source/net/ipv4/netfilter/nf_nat_h323.c#L228">228</a>                             <a href="ident?i=htons">htons</a>(nated_port + 1);
<a name="L229" href="source/net/ipv4/netfilter/nf_nat_h323.c#L229">229</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_expect_related">nf_ct_expect_related</a>(rtcp_exp);
<a name="L230" href="source/net/ipv4/netfilter/nf_nat_h323.c#L230">230</a>                         if (<a href="ident?i=ret">ret</a> == 0)
<a name="L231" href="source/net/ipv4/netfilter/nf_nat_h323.c#L231">231</a>                                 break;
<a name="L232" href="source/net/ipv4/netfilter/nf_nat_h323.c#L232">232</a>                         else if (<a href="ident?i=ret">ret</a> == -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L233" href="source/net/ipv4/netfilter/nf_nat_h323.c#L233">233</a>                                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(rtp_exp);
<a name="L234" href="source/net/ipv4/netfilter/nf_nat_h323.c#L234">234</a>                                 continue;
<a name="L235" href="source/net/ipv4/netfilter/nf_nat_h323.c#L235">235</a>                         } else if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L236" href="source/net/ipv4/netfilter/nf_nat_h323.c#L236">236</a>                                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(rtp_exp);
<a name="L237" href="source/net/ipv4/netfilter/nf_nat_h323.c#L237">237</a>                                 nated_port = 0;
<a name="L238" href="source/net/ipv4/netfilter/nf_nat_h323.c#L238">238</a>                                 break;
<a name="L239" href="source/net/ipv4/netfilter/nf_nat_h323.c#L239">239</a>                         }
<a name="L240" href="source/net/ipv4/netfilter/nf_nat_h323.c#L240">240</a>                 } else if (<a href="ident?i=ret">ret</a> != -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L241" href="source/net/ipv4/netfilter/nf_nat_h323.c#L241">241</a>                         nated_port = 0;
<a name="L242" href="source/net/ipv4/netfilter/nf_nat_h323.c#L242">242</a>                         break;
<a name="L243" href="source/net/ipv4/netfilter/nf_nat_h323.c#L243">243</a>                 }
<a name="L244" href="source/net/ipv4/netfilter/nf_nat_h323.c#L244">244</a>         }
<a name="L245" href="source/net/ipv4/netfilter/nf_nat_h323.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/netfilter/nf_nat_h323.c#L246">246</a>         if (nated_port == 0) {  <b><i>/* No port available */</i></b>
<a name="L247" href="source/net/ipv4/netfilter/nf_nat_h323.c#L247">247</a>                 <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_h323: out of RTP ports\n"</i>);
<a name="L248" href="source/net/ipv4/netfilter/nf_nat_h323.c#L248">248</a>                 return 0;
<a name="L249" href="source/net/ipv4/netfilter/nf_nat_h323.c#L249">249</a>         }
<a name="L250" href="source/net/ipv4/netfilter/nf_nat_h323.c#L250">250</a> 
<a name="L251" href="source/net/ipv4/netfilter/nf_nat_h323.c#L251">251</a>         <b><i>/* Modify signal */</i></b>
<a name="L252" href="source/net/ipv4/netfilter/nf_nat_h323.c#L252">252</a>         if (<a href="ident?i=set_h245_addr">set_h245_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, dataoff, taddr,
<a name="L253" href="source/net/ipv4/netfilter/nf_nat_h323.c#L253">253</a>                           &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L254" href="source/net/ipv4/netfilter/nf_nat_h323.c#L254">254</a>                           <a href="ident?i=htons">htons</a>((<a href="ident?i=port">port</a> &amp; <a href="ident?i=htons">htons</a>(1)) ? nated_port + 1 :
<a name="L255" href="source/net/ipv4/netfilter/nf_nat_h323.c#L255">255</a>                                                     nated_port)) == 0) {
<a name="L256" href="source/net/ipv4/netfilter/nf_nat_h323.c#L256">256</a>                 <b><i>/* Save ports */</i></b>
<a name="L257" href="source/net/ipv4/netfilter/nf_nat_h323.c#L257">257</a>                 <a href="ident?i=info">info</a>-&gt;rtp_port[<a href="ident?i=i">i</a>][<a href="ident?i=dir">dir</a>] = rtp_port;
<a name="L258" href="source/net/ipv4/netfilter/nf_nat_h323.c#L258">258</a>                 <a href="ident?i=info">info</a>-&gt;rtp_port[<a href="ident?i=i">i</a>][!<a href="ident?i=dir">dir</a>] = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L259" href="source/net/ipv4/netfilter/nf_nat_h323.c#L259">259</a>         } else {
<a name="L260" href="source/net/ipv4/netfilter/nf_nat_h323.c#L260">260</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(rtp_exp);
<a name="L261" href="source/net/ipv4/netfilter/nf_nat_h323.c#L261">261</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(rtcp_exp);
<a name="L262" href="source/net/ipv4/netfilter/nf_nat_h323.c#L262">262</a>                 return -1;
<a name="L263" href="source/net/ipv4/netfilter/nf_nat_h323.c#L263">263</a>         }
<a name="L264" href="source/net/ipv4/netfilter/nf_nat_h323.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/netfilter/nf_nat_h323.c#L265">265</a>         <b><i>/* Success */</i></b>
<a name="L266" href="source/net/ipv4/netfilter/nf_nat_h323.c#L266">266</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_h323: expect RTP %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L267" href="source/net/ipv4/netfilter/nf_nat_h323.c#L267">267</a>                  &amp;rtp_exp-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L268" href="source/net/ipv4/netfilter/nf_nat_h323.c#L268">268</a>                  <a href="ident?i=ntohs">ntohs</a>(rtp_exp-&gt;tuple.<a href="ident?i=src">src</a>.u.udp.<a href="ident?i=port">port</a>),
<a name="L269" href="source/net/ipv4/netfilter/nf_nat_h323.c#L269">269</a>                  &amp;rtp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L270" href="source/net/ipv4/netfilter/nf_nat_h323.c#L270">270</a>                  <a href="ident?i=ntohs">ntohs</a>(rtp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>));
<a name="L271" href="source/net/ipv4/netfilter/nf_nat_h323.c#L271">271</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_h323: expect RTCP %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L272" href="source/net/ipv4/netfilter/nf_nat_h323.c#L272">272</a>                  &amp;rtcp_exp-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L273" href="source/net/ipv4/netfilter/nf_nat_h323.c#L273">273</a>                  <a href="ident?i=ntohs">ntohs</a>(rtcp_exp-&gt;tuple.<a href="ident?i=src">src</a>.u.udp.<a href="ident?i=port">port</a>),
<a name="L274" href="source/net/ipv4/netfilter/nf_nat_h323.c#L274">274</a>                  &amp;rtcp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L275" href="source/net/ipv4/netfilter/nf_nat_h323.c#L275">275</a>                  <a href="ident?i=ntohs">ntohs</a>(rtcp_exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.udp.<a href="ident?i=port">port</a>));
<a name="L276" href="source/net/ipv4/netfilter/nf_nat_h323.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/netfilter/nf_nat_h323.c#L277">277</a>         return 0;
<a name="L278" href="source/net/ipv4/netfilter/nf_nat_h323.c#L278">278</a> }
<a name="L279" href="source/net/ipv4/netfilter/nf_nat_h323.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/netfilter/nf_nat_h323.c#L280">280</a> <b><i>/****************************************************************************/</i></b>
<a name="L281" href="source/net/ipv4/netfilter/nf_nat_h323.c#L281">281</a> static int <a href="ident?i=nat_t120">nat_t120</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L282" href="source/net/ipv4/netfilter/nf_nat_h323.c#L282">282</a>                     enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L283" href="source/net/ipv4/netfilter/nf_nat_h323.c#L283">283</a>                     unsigned int protoff, unsigned char **<a href="ident?i=data">data</a>, int dataoff,
<a name="L284" href="source/net/ipv4/netfilter/nf_nat_h323.c#L284">284</a>                     <a href="ident?i=H245_TransportAddress">H245_TransportAddress</a> *taddr, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>,
<a name="L285" href="source/net/ipv4/netfilter/nf_nat_h323.c#L285">285</a>                     struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *exp)
<a name="L286" href="source/net/ipv4/netfilter/nf_nat_h323.c#L286">286</a> {
<a name="L287" href="source/net/ipv4/netfilter/nf_nat_h323.c#L287">287</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L288" href="source/net/ipv4/netfilter/nf_nat_h323.c#L288">288</a>         <a href="ident?i=u_int16_t">u_int16_t</a> nated_port = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=port">port</a>);
<a name="L289" href="source/net/ipv4/netfilter/nf_nat_h323.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/netfilter/nf_nat_h323.c#L290">290</a>         <b><i>/* Set expectations for NAT */</i></b>
<a name="L291" href="source/net/ipv4/netfilter/nf_nat_h323.c#L291">291</a>         exp-&gt;saved_proto.tcp.<a href="ident?i=port">port</a> = exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>;
<a name="L292" href="source/net/ipv4/netfilter/nf_nat_h323.c#L292">292</a>         exp-&gt;expectfn = <a href="ident?i=nf_nat_follow_master">nf_nat_follow_master</a>;
<a name="L293" href="source/net/ipv4/netfilter/nf_nat_h323.c#L293">293</a>         exp-&gt;<a href="ident?i=dir">dir</a> = !<a href="ident?i=dir">dir</a>;
<a name="L294" href="source/net/ipv4/netfilter/nf_nat_h323.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/netfilter/nf_nat_h323.c#L295">295</a>         <b><i>/* Try to get same port: if not, try to change it. */</i></b>
<a name="L296" href="source/net/ipv4/netfilter/nf_nat_h323.c#L296">296</a>         for (; nated_port != 0; nated_port++) {
<a name="L297" href="source/net/ipv4/netfilter/nf_nat_h323.c#L297">297</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L298" href="source/net/ipv4/netfilter/nf_nat_h323.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/netfilter/nf_nat_h323.c#L299">299</a>                 exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a> = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L300" href="source/net/ipv4/netfilter/nf_nat_h323.c#L300">300</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_expect_related">nf_ct_expect_related</a>(exp);
<a name="L301" href="source/net/ipv4/netfilter/nf_nat_h323.c#L301">301</a>                 if (<a href="ident?i=ret">ret</a> == 0)
<a name="L302" href="source/net/ipv4/netfilter/nf_nat_h323.c#L302">302</a>                         break;
<a name="L303" href="source/net/ipv4/netfilter/nf_nat_h323.c#L303">303</a>                 else if (<a href="ident?i=ret">ret</a> != -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L304" href="source/net/ipv4/netfilter/nf_nat_h323.c#L304">304</a>                         nated_port = 0;
<a name="L305" href="source/net/ipv4/netfilter/nf_nat_h323.c#L305">305</a>                         break;
<a name="L306" href="source/net/ipv4/netfilter/nf_nat_h323.c#L306">306</a>                 }
<a name="L307" href="source/net/ipv4/netfilter/nf_nat_h323.c#L307">307</a>         }
<a name="L308" href="source/net/ipv4/netfilter/nf_nat_h323.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/netfilter/nf_nat_h323.c#L309">309</a>         if (nated_port == 0) {  <b><i>/* No port available */</i></b>
<a name="L310" href="source/net/ipv4/netfilter/nf_nat_h323.c#L310">310</a>                 <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_h323: out of TCP ports\n"</i>);
<a name="L311" href="source/net/ipv4/netfilter/nf_nat_h323.c#L311">311</a>                 return 0;
<a name="L312" href="source/net/ipv4/netfilter/nf_nat_h323.c#L312">312</a>         }
<a name="L313" href="source/net/ipv4/netfilter/nf_nat_h323.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/netfilter/nf_nat_h323.c#L314">314</a>         <b><i>/* Modify signal */</i></b>
<a name="L315" href="source/net/ipv4/netfilter/nf_nat_h323.c#L315">315</a>         if (<a href="ident?i=set_h245_addr">set_h245_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, dataoff, taddr,
<a name="L316" href="source/net/ipv4/netfilter/nf_nat_h323.c#L316">316</a>                           &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L317" href="source/net/ipv4/netfilter/nf_nat_h323.c#L317">317</a>                           <a href="ident?i=htons">htons</a>(nated_port)) &lt; 0) {
<a name="L318" href="source/net/ipv4/netfilter/nf_nat_h323.c#L318">318</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(exp);
<a name="L319" href="source/net/ipv4/netfilter/nf_nat_h323.c#L319">319</a>                 return -1;
<a name="L320" href="source/net/ipv4/netfilter/nf_nat_h323.c#L320">320</a>         }
<a name="L321" href="source/net/ipv4/netfilter/nf_nat_h323.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/netfilter/nf_nat_h323.c#L322">322</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_h323: expect T.120 %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L323" href="source/net/ipv4/netfilter/nf_nat_h323.c#L323">323</a>                  &amp;exp-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L324" href="source/net/ipv4/netfilter/nf_nat_h323.c#L324">324</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=src">src</a>.u.tcp.<a href="ident?i=port">port</a>),
<a name="L325" href="source/net/ipv4/netfilter/nf_nat_h323.c#L325">325</a>                  &amp;exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L326" href="source/net/ipv4/netfilter/nf_nat_h323.c#L326">326</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>));
<a name="L327" href="source/net/ipv4/netfilter/nf_nat_h323.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/netfilter/nf_nat_h323.c#L328">328</a>         return 0;
<a name="L329" href="source/net/ipv4/netfilter/nf_nat_h323.c#L329">329</a> }
<a name="L330" href="source/net/ipv4/netfilter/nf_nat_h323.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/netfilter/nf_nat_h323.c#L331">331</a> <b><i>/****************************************************************************/</i></b>
<a name="L332" href="source/net/ipv4/netfilter/nf_nat_h323.c#L332">332</a> static int <a href="ident?i=nat_h245">nat_h245</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L333" href="source/net/ipv4/netfilter/nf_nat_h323.c#L333">333</a>                     enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L334" href="source/net/ipv4/netfilter/nf_nat_h323.c#L334">334</a>                     unsigned int protoff, unsigned char **<a href="ident?i=data">data</a>, int dataoff,
<a name="L335" href="source/net/ipv4/netfilter/nf_nat_h323.c#L335">335</a>                     <a href="ident?i=TransportAddress">TransportAddress</a> *taddr, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>,
<a name="L336" href="source/net/ipv4/netfilter/nf_nat_h323.c#L336">336</a>                     struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *exp)
<a name="L337" href="source/net/ipv4/netfilter/nf_nat_h323.c#L337">337</a> {
<a name="L338" href="source/net/ipv4/netfilter/nf_nat_h323.c#L338">338</a>         struct <a href="ident?i=nf_ct_h323_master">nf_ct_h323_master</a> *<a href="ident?i=info">info</a> = <a href="ident?i=nfct_help_data">nfct_help_data</a>(ct);
<a name="L339" href="source/net/ipv4/netfilter/nf_nat_h323.c#L339">339</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L340" href="source/net/ipv4/netfilter/nf_nat_h323.c#L340">340</a>         <a href="ident?i=u_int16_t">u_int16_t</a> nated_port = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=port">port</a>);
<a name="L341" href="source/net/ipv4/netfilter/nf_nat_h323.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/netfilter/nf_nat_h323.c#L342">342</a>         <b><i>/* Set expectations for NAT */</i></b>
<a name="L343" href="source/net/ipv4/netfilter/nf_nat_h323.c#L343">343</a>         exp-&gt;saved_proto.tcp.<a href="ident?i=port">port</a> = exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>;
<a name="L344" href="source/net/ipv4/netfilter/nf_nat_h323.c#L344">344</a>         exp-&gt;expectfn = <a href="ident?i=nf_nat_follow_master">nf_nat_follow_master</a>;
<a name="L345" href="source/net/ipv4/netfilter/nf_nat_h323.c#L345">345</a>         exp-&gt;<a href="ident?i=dir">dir</a> = !<a href="ident?i=dir">dir</a>;
<a name="L346" href="source/net/ipv4/netfilter/nf_nat_h323.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/netfilter/nf_nat_h323.c#L347">347</a>         <b><i>/* Check existing expects */</i></b>
<a name="L348" href="source/net/ipv4/netfilter/nf_nat_h323.c#L348">348</a>         if (<a href="ident?i=info">info</a>-&gt;sig_port[<a href="ident?i=dir">dir</a>] == <a href="ident?i=port">port</a>)
<a name="L349" href="source/net/ipv4/netfilter/nf_nat_h323.c#L349">349</a>                 nated_port = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L350" href="source/net/ipv4/netfilter/nf_nat_h323.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/netfilter/nf_nat_h323.c#L351">351</a>         <b><i>/* Try to get same port: if not, try to change it. */</i></b>
<a name="L352" href="source/net/ipv4/netfilter/nf_nat_h323.c#L352">352</a>         for (; nated_port != 0; nated_port++) {
<a name="L353" href="source/net/ipv4/netfilter/nf_nat_h323.c#L353">353</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L354" href="source/net/ipv4/netfilter/nf_nat_h323.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/netfilter/nf_nat_h323.c#L355">355</a>                 exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a> = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L356" href="source/net/ipv4/netfilter/nf_nat_h323.c#L356">356</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_expect_related">nf_ct_expect_related</a>(exp);
<a name="L357" href="source/net/ipv4/netfilter/nf_nat_h323.c#L357">357</a>                 if (<a href="ident?i=ret">ret</a> == 0)
<a name="L358" href="source/net/ipv4/netfilter/nf_nat_h323.c#L358">358</a>                         break;
<a name="L359" href="source/net/ipv4/netfilter/nf_nat_h323.c#L359">359</a>                 else if (<a href="ident?i=ret">ret</a> != -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L360" href="source/net/ipv4/netfilter/nf_nat_h323.c#L360">360</a>                         nated_port = 0;
<a name="L361" href="source/net/ipv4/netfilter/nf_nat_h323.c#L361">361</a>                         break;
<a name="L362" href="source/net/ipv4/netfilter/nf_nat_h323.c#L362">362</a>                 }
<a name="L363" href="source/net/ipv4/netfilter/nf_nat_h323.c#L363">363</a>         }
<a name="L364" href="source/net/ipv4/netfilter/nf_nat_h323.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/netfilter/nf_nat_h323.c#L365">365</a>         if (nated_port == 0) {  <b><i>/* No port available */</i></b>
<a name="L366" href="source/net/ipv4/netfilter/nf_nat_h323.c#L366">366</a>                 <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_q931: out of TCP ports\n"</i>);
<a name="L367" href="source/net/ipv4/netfilter/nf_nat_h323.c#L367">367</a>                 return 0;
<a name="L368" href="source/net/ipv4/netfilter/nf_nat_h323.c#L368">368</a>         }
<a name="L369" href="source/net/ipv4/netfilter/nf_nat_h323.c#L369">369</a> 
<a name="L370" href="source/net/ipv4/netfilter/nf_nat_h323.c#L370">370</a>         <b><i>/* Modify signal */</i></b>
<a name="L371" href="source/net/ipv4/netfilter/nf_nat_h323.c#L371">371</a>         if (<a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, dataoff, taddr,
<a name="L372" href="source/net/ipv4/netfilter/nf_nat_h323.c#L372">372</a>                           &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L373" href="source/net/ipv4/netfilter/nf_nat_h323.c#L373">373</a>                           <a href="ident?i=htons">htons</a>(nated_port)) == 0) {
<a name="L374" href="source/net/ipv4/netfilter/nf_nat_h323.c#L374">374</a>                 <b><i>/* Save ports */</i></b>
<a name="L375" href="source/net/ipv4/netfilter/nf_nat_h323.c#L375">375</a>                 <a href="ident?i=info">info</a>-&gt;sig_port[<a href="ident?i=dir">dir</a>] = <a href="ident?i=port">port</a>;
<a name="L376" href="source/net/ipv4/netfilter/nf_nat_h323.c#L376">376</a>                 <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>] = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L377" href="source/net/ipv4/netfilter/nf_nat_h323.c#L377">377</a>         } else {
<a name="L378" href="source/net/ipv4/netfilter/nf_nat_h323.c#L378">378</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(exp);
<a name="L379" href="source/net/ipv4/netfilter/nf_nat_h323.c#L379">379</a>                 return -1;
<a name="L380" href="source/net/ipv4/netfilter/nf_nat_h323.c#L380">380</a>         }
<a name="L381" href="source/net/ipv4/netfilter/nf_nat_h323.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/netfilter/nf_nat_h323.c#L382">382</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_q931: expect H.245 %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L383" href="source/net/ipv4/netfilter/nf_nat_h323.c#L383">383</a>                  &amp;exp-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L384" href="source/net/ipv4/netfilter/nf_nat_h323.c#L384">384</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=src">src</a>.u.tcp.<a href="ident?i=port">port</a>),
<a name="L385" href="source/net/ipv4/netfilter/nf_nat_h323.c#L385">385</a>                  &amp;exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L386" href="source/net/ipv4/netfilter/nf_nat_h323.c#L386">386</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>));
<a name="L387" href="source/net/ipv4/netfilter/nf_nat_h323.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/netfilter/nf_nat_h323.c#L388">388</a>         return 0;
<a name="L389" href="source/net/ipv4/netfilter/nf_nat_h323.c#L389">389</a> }
<a name="L390" href="source/net/ipv4/netfilter/nf_nat_h323.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/netfilter/nf_nat_h323.c#L391">391</a> <b><i>/****************************************************************************</i></b>
<a name="L392" href="source/net/ipv4/netfilter/nf_nat_h323.c#L392">392</a> <b><i> * This conntrack expect function replaces nf_conntrack_q931_expect()</i></b>
<a name="L393" href="source/net/ipv4/netfilter/nf_nat_h323.c#L393">393</a> <b><i> * which was set by nf_conntrack_h323.c.</i></b>
<a name="L394" href="source/net/ipv4/netfilter/nf_nat_h323.c#L394">394</a> <b><i> ****************************************************************************/</i></b>
<a name="L395" href="source/net/ipv4/netfilter/nf_nat_h323.c#L395">395</a> static void <a href="ident?i=ip_nat_q931_expect">ip_nat_q931_expect</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *<a href="ident?i=new">new</a>,
<a name="L396" href="source/net/ipv4/netfilter/nf_nat_h323.c#L396">396</a>                                struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *<a href="ident?i=this">this</a>)
<a name="L397" href="source/net/ipv4/netfilter/nf_nat_h323.c#L397">397</a> {
<a name="L398" href="source/net/ipv4/netfilter/nf_nat_h323.c#L398">398</a>         struct <a href="ident?i=nf_nat_range">nf_nat_range</a> <a href="ident?i=range">range</a>;
<a name="L399" href="source/net/ipv4/netfilter/nf_nat_h323.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/netfilter/nf_nat_h323.c#L400">400</a>         if (<a href="ident?i=this">this</a>-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> != 0) {       <b><i>/* Only accept calls from GK */</i></b>
<a name="L401" href="source/net/ipv4/netfilter/nf_nat_h323.c#L401">401</a>                 <a href="ident?i=nf_nat_follow_master">nf_nat_follow_master</a>(<a href="ident?i=new">new</a>, <a href="ident?i=this">this</a>);
<a name="L402" href="source/net/ipv4/netfilter/nf_nat_h323.c#L402">402</a>                 return;
<a name="L403" href="source/net/ipv4/netfilter/nf_nat_h323.c#L403">403</a>         }
<a name="L404" href="source/net/ipv4/netfilter/nf_nat_h323.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/netfilter/nf_nat_h323.c#L405">405</a>         <b><i>/* This must be a fresh one. */</i></b>
<a name="L406" href="source/net/ipv4/netfilter/nf_nat_h323.c#L406">406</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=new">new</a>-&gt;<a href="ident?i=status">status</a> &amp; IPS_NAT_DONE_MASK);
<a name="L407" href="source/net/ipv4/netfilter/nf_nat_h323.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/netfilter/nf_nat_h323.c#L408">408</a>         <b><i>/* Change src to where master sends to */</i></b>
<a name="L409" href="source/net/ipv4/netfilter/nf_nat_h323.c#L409">409</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>;
<a name="L410" href="source/net/ipv4/netfilter/nf_nat_h323.c#L410">410</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_addr">min_addr</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_addr">max_addr</a> =
<a name="L411" href="source/net/ipv4/netfilter/nf_nat_h323.c#L411">411</a>             <a href="ident?i=new">new</a>-&gt;tuplehash[!<a href="ident?i=this">this</a>-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3;
<a name="L412" href="source/net/ipv4/netfilter/nf_nat_h323.c#L412">412</a>         <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(<a href="ident?i=new">new</a>, &amp;<a href="ident?i=range">range</a>, NF_NAT_MANIP_SRC);
<a name="L413" href="source/net/ipv4/netfilter/nf_nat_h323.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/netfilter/nf_nat_h323.c#L414">414</a>         <b><i>/* For DST manip, map port here to where it's expected. */</i></b>
<a name="L415" href="source/net/ipv4/netfilter/nf_nat_h323.c#L415">415</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = (<a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a> | <a href="ident?i=NF_NAT_RANGE_PROTO_SPECIFIED">NF_NAT_RANGE_PROTO_SPECIFIED</a>);
<a name="L416" href="source/net/ipv4/netfilter/nf_nat_h323.c#L416">416</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_proto">min_proto</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_proto">max_proto</a> = <a href="ident?i=this">this</a>-&gt;saved_proto;
<a name="L417" href="source/net/ipv4/netfilter/nf_nat_h323.c#L417">417</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_addr">min_addr</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_addr">max_addr</a> =
<a name="L418" href="source/net/ipv4/netfilter/nf_nat_h323.c#L418">418</a>             <a href="ident?i=new">new</a>-&gt;<a href="ident?i=master">master</a>-&gt;tuplehash[!<a href="ident?i=this">this</a>-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3;
<a name="L419" href="source/net/ipv4/netfilter/nf_nat_h323.c#L419">419</a>         <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(<a href="ident?i=new">new</a>, &amp;<a href="ident?i=range">range</a>, NF_NAT_MANIP_DST);
<a name="L420" href="source/net/ipv4/netfilter/nf_nat_h323.c#L420">420</a> }
<a name="L421" href="source/net/ipv4/netfilter/nf_nat_h323.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/netfilter/nf_nat_h323.c#L422">422</a> <b><i>/****************************************************************************/</i></b>
<a name="L423" href="source/net/ipv4/netfilter/nf_nat_h323.c#L423">423</a> static int <a href="ident?i=nat_q931">nat_q931</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L424" href="source/net/ipv4/netfilter/nf_nat_h323.c#L424">424</a>                     enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L425" href="source/net/ipv4/netfilter/nf_nat_h323.c#L425">425</a>                     unsigned int protoff, unsigned char **<a href="ident?i=data">data</a>,
<a name="L426" href="source/net/ipv4/netfilter/nf_nat_h323.c#L426">426</a>                     <a href="ident?i=TransportAddress">TransportAddress</a> *taddr, int <a href="ident?i=idx">idx</a>,
<a name="L427" href="source/net/ipv4/netfilter/nf_nat_h323.c#L427">427</a>                     <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>, struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *exp)
<a name="L428" href="source/net/ipv4/netfilter/nf_nat_h323.c#L428">428</a> {
<a name="L429" href="source/net/ipv4/netfilter/nf_nat_h323.c#L429">429</a>         struct <a href="ident?i=nf_ct_h323_master">nf_ct_h323_master</a> *<a href="ident?i=info">info</a> = <a href="ident?i=nfct_help_data">nfct_help_data</a>(ct);
<a name="L430" href="source/net/ipv4/netfilter/nf_nat_h323.c#L430">430</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L431" href="source/net/ipv4/netfilter/nf_nat_h323.c#L431">431</a>         <a href="ident?i=u_int16_t">u_int16_t</a> nated_port = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=port">port</a>);
<a name="L432" href="source/net/ipv4/netfilter/nf_nat_h323.c#L432">432</a>         union <a href="ident?i=nf_inet_addr">nf_inet_addr</a> <a href="ident?i=addr">addr</a>;
<a name="L433" href="source/net/ipv4/netfilter/nf_nat_h323.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/netfilter/nf_nat_h323.c#L434">434</a>         <b><i>/* Set expectations for NAT */</i></b>
<a name="L435" href="source/net/ipv4/netfilter/nf_nat_h323.c#L435">435</a>         exp-&gt;saved_proto.tcp.<a href="ident?i=port">port</a> = exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>;
<a name="L436" href="source/net/ipv4/netfilter/nf_nat_h323.c#L436">436</a>         exp-&gt;expectfn = <a href="ident?i=ip_nat_q931_expect">ip_nat_q931_expect</a>;
<a name="L437" href="source/net/ipv4/netfilter/nf_nat_h323.c#L437">437</a>         exp-&gt;<a href="ident?i=dir">dir</a> = !<a href="ident?i=dir">dir</a>;
<a name="L438" href="source/net/ipv4/netfilter/nf_nat_h323.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/netfilter/nf_nat_h323.c#L439">439</a>         <b><i>/* Check existing expects */</i></b>
<a name="L440" href="source/net/ipv4/netfilter/nf_nat_h323.c#L440">440</a>         if (<a href="ident?i=info">info</a>-&gt;sig_port[<a href="ident?i=dir">dir</a>] == <a href="ident?i=port">port</a>)
<a name="L441" href="source/net/ipv4/netfilter/nf_nat_h323.c#L441">441</a>                 nated_port = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L442" href="source/net/ipv4/netfilter/nf_nat_h323.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/netfilter/nf_nat_h323.c#L443">443</a>         <b><i>/* Try to get same port: if not, try to change it. */</i></b>
<a name="L444" href="source/net/ipv4/netfilter/nf_nat_h323.c#L444">444</a>         for (; nated_port != 0; nated_port++) {
<a name="L445" href="source/net/ipv4/netfilter/nf_nat_h323.c#L445">445</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L446" href="source/net/ipv4/netfilter/nf_nat_h323.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/netfilter/nf_nat_h323.c#L447">447</a>                 exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a> = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L448" href="source/net/ipv4/netfilter/nf_nat_h323.c#L448">448</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_expect_related">nf_ct_expect_related</a>(exp);
<a name="L449" href="source/net/ipv4/netfilter/nf_nat_h323.c#L449">449</a>                 if (<a href="ident?i=ret">ret</a> == 0)
<a name="L450" href="source/net/ipv4/netfilter/nf_nat_h323.c#L450">450</a>                         break;
<a name="L451" href="source/net/ipv4/netfilter/nf_nat_h323.c#L451">451</a>                 else if (<a href="ident?i=ret">ret</a> != -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L452" href="source/net/ipv4/netfilter/nf_nat_h323.c#L452">452</a>                         nated_port = 0;
<a name="L453" href="source/net/ipv4/netfilter/nf_nat_h323.c#L453">453</a>                         break;
<a name="L454" href="source/net/ipv4/netfilter/nf_nat_h323.c#L454">454</a>                 }
<a name="L455" href="source/net/ipv4/netfilter/nf_nat_h323.c#L455">455</a>         }
<a name="L456" href="source/net/ipv4/netfilter/nf_nat_h323.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/netfilter/nf_nat_h323.c#L457">457</a>         if (nated_port == 0) {  <b><i>/* No port available */</i></b>
<a name="L458" href="source/net/ipv4/netfilter/nf_nat_h323.c#L458">458</a>                 <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_ras: out of TCP ports\n"</i>);
<a name="L459" href="source/net/ipv4/netfilter/nf_nat_h323.c#L459">459</a>                 return 0;
<a name="L460" href="source/net/ipv4/netfilter/nf_nat_h323.c#L460">460</a>         }
<a name="L461" href="source/net/ipv4/netfilter/nf_nat_h323.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/netfilter/nf_nat_h323.c#L462">462</a>         <b><i>/* Modify signal */</i></b>
<a name="L463" href="source/net/ipv4/netfilter/nf_nat_h323.c#L463">463</a>         if (<a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, 0, &amp;taddr[<a href="ident?i=idx">idx</a>],
<a name="L464" href="source/net/ipv4/netfilter/nf_nat_h323.c#L464">464</a>                           &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L465" href="source/net/ipv4/netfilter/nf_nat_h323.c#L465">465</a>                           <a href="ident?i=htons">htons</a>(nated_port)) == 0) {
<a name="L466" href="source/net/ipv4/netfilter/nf_nat_h323.c#L466">466</a>                 <b><i>/* Save ports */</i></b>
<a name="L467" href="source/net/ipv4/netfilter/nf_nat_h323.c#L467">467</a>                 <a href="ident?i=info">info</a>-&gt;sig_port[<a href="ident?i=dir">dir</a>] = <a href="ident?i=port">port</a>;
<a name="L468" href="source/net/ipv4/netfilter/nf_nat_h323.c#L468">468</a>                 <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>] = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L469" href="source/net/ipv4/netfilter/nf_nat_h323.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/netfilter/nf_nat_h323.c#L470">470</a>                 <b><i>/* Fix for Gnomemeeting */</i></b>
<a name="L471" href="source/net/ipv4/netfilter/nf_nat_h323.c#L471">471</a>                 if (<a href="ident?i=idx">idx</a> &gt; 0 &amp;&amp;
<a name="L472" href="source/net/ipv4/netfilter/nf_nat_h323.c#L472">472</a>                     <a href="ident?i=get_h225_addr">get_h225_addr</a>(ct, *<a href="ident?i=data">data</a>, &amp;taddr[0], &amp;<a href="ident?i=addr">addr</a>, &amp;<a href="ident?i=port">port</a>) &amp;&amp;
<a name="L473" href="source/net/ipv4/netfilter/nf_nat_h323.c#L473">473</a>                     (<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=addr">addr</a>.<a href="ident?i=ip">ip</a>) &amp; 0xff000000) == 0x7f000000) {
<a name="L474" href="source/net/ipv4/netfilter/nf_nat_h323.c#L474">474</a>                         <a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, 0, &amp;taddr[0],
<a name="L475" href="source/net/ipv4/netfilter/nf_nat_h323.c#L475">475</a>                                       &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L476" href="source/net/ipv4/netfilter/nf_nat_h323.c#L476">476</a>                                       <a href="ident?i=info">info</a>-&gt;sig_port[!<a href="ident?i=dir">dir</a>]);
<a name="L477" href="source/net/ipv4/netfilter/nf_nat_h323.c#L477">477</a>                 }
<a name="L478" href="source/net/ipv4/netfilter/nf_nat_h323.c#L478">478</a>         } else {
<a name="L479" href="source/net/ipv4/netfilter/nf_nat_h323.c#L479">479</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(exp);
<a name="L480" href="source/net/ipv4/netfilter/nf_nat_h323.c#L480">480</a>                 return -1;
<a name="L481" href="source/net/ipv4/netfilter/nf_nat_h323.c#L481">481</a>         }
<a name="L482" href="source/net/ipv4/netfilter/nf_nat_h323.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/netfilter/nf_nat_h323.c#L483">483</a>         <b><i>/* Success */</i></b>
<a name="L484" href="source/net/ipv4/netfilter/nf_nat_h323.c#L484">484</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_ras: expect Q.931 %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L485" href="source/net/ipv4/netfilter/nf_nat_h323.c#L485">485</a>                  &amp;exp-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L486" href="source/net/ipv4/netfilter/nf_nat_h323.c#L486">486</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=src">src</a>.u.tcp.<a href="ident?i=port">port</a>),
<a name="L487" href="source/net/ipv4/netfilter/nf_nat_h323.c#L487">487</a>                  &amp;exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L488" href="source/net/ipv4/netfilter/nf_nat_h323.c#L488">488</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>));
<a name="L489" href="source/net/ipv4/netfilter/nf_nat_h323.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/netfilter/nf_nat_h323.c#L490">490</a>         return 0;
<a name="L491" href="source/net/ipv4/netfilter/nf_nat_h323.c#L491">491</a> }
<a name="L492" href="source/net/ipv4/netfilter/nf_nat_h323.c#L492">492</a> 
<a name="L493" href="source/net/ipv4/netfilter/nf_nat_h323.c#L493">493</a> <b><i>/****************************************************************************/</i></b>
<a name="L494" href="source/net/ipv4/netfilter/nf_nat_h323.c#L494">494</a> static void <a href="ident?i=ip_nat_callforwarding_expect">ip_nat_callforwarding_expect</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *<a href="ident?i=new">new</a>,
<a name="L495" href="source/net/ipv4/netfilter/nf_nat_h323.c#L495">495</a>                                          struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *<a href="ident?i=this">this</a>)
<a name="L496" href="source/net/ipv4/netfilter/nf_nat_h323.c#L496">496</a> {
<a name="L497" href="source/net/ipv4/netfilter/nf_nat_h323.c#L497">497</a>         struct <a href="ident?i=nf_nat_range">nf_nat_range</a> <a href="ident?i=range">range</a>;
<a name="L498" href="source/net/ipv4/netfilter/nf_nat_h323.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/netfilter/nf_nat_h323.c#L499">499</a>         <b><i>/* This must be a fresh one. */</i></b>
<a name="L500" href="source/net/ipv4/netfilter/nf_nat_h323.c#L500">500</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=new">new</a>-&gt;<a href="ident?i=status">status</a> &amp; IPS_NAT_DONE_MASK);
<a name="L501" href="source/net/ipv4/netfilter/nf_nat_h323.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/netfilter/nf_nat_h323.c#L502">502</a>         <b><i>/* Change src to where master sends to */</i></b>
<a name="L503" href="source/net/ipv4/netfilter/nf_nat_h323.c#L503">503</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>;
<a name="L504" href="source/net/ipv4/netfilter/nf_nat_h323.c#L504">504</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_addr">min_addr</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_addr">max_addr</a> =
<a name="L505" href="source/net/ipv4/netfilter/nf_nat_h323.c#L505">505</a>             <a href="ident?i=new">new</a>-&gt;tuplehash[!<a href="ident?i=this">this</a>-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3;
<a name="L506" href="source/net/ipv4/netfilter/nf_nat_h323.c#L506">506</a>         <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(<a href="ident?i=new">new</a>, &amp;<a href="ident?i=range">range</a>, NF_NAT_MANIP_SRC);
<a name="L507" href="source/net/ipv4/netfilter/nf_nat_h323.c#L507">507</a> 
<a name="L508" href="source/net/ipv4/netfilter/nf_nat_h323.c#L508">508</a>         <b><i>/* For DST manip, map port here to where it's expected. */</i></b>
<a name="L509" href="source/net/ipv4/netfilter/nf_nat_h323.c#L509">509</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = (<a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a> | <a href="ident?i=NF_NAT_RANGE_PROTO_SPECIFIED">NF_NAT_RANGE_PROTO_SPECIFIED</a>);
<a name="L510" href="source/net/ipv4/netfilter/nf_nat_h323.c#L510">510</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_proto">min_proto</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_proto">max_proto</a> = <a href="ident?i=this">this</a>-&gt;saved_proto;
<a name="L511" href="source/net/ipv4/netfilter/nf_nat_h323.c#L511">511</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_addr">min_addr</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_addr">max_addr</a> = <a href="ident?i=this">this</a>-&gt;saved_addr;
<a name="L512" href="source/net/ipv4/netfilter/nf_nat_h323.c#L512">512</a>         <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(<a href="ident?i=new">new</a>, &amp;<a href="ident?i=range">range</a>, NF_NAT_MANIP_DST);
<a name="L513" href="source/net/ipv4/netfilter/nf_nat_h323.c#L513">513</a> }
<a name="L514" href="source/net/ipv4/netfilter/nf_nat_h323.c#L514">514</a> 
<a name="L515" href="source/net/ipv4/netfilter/nf_nat_h323.c#L515">515</a> <b><i>/****************************************************************************/</i></b>
<a name="L516" href="source/net/ipv4/netfilter/nf_nat_h323.c#L516">516</a> static int <a href="ident?i=nat_callforwarding">nat_callforwarding</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L517" href="source/net/ipv4/netfilter/nf_nat_h323.c#L517">517</a>                               enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L518" href="source/net/ipv4/netfilter/nf_nat_h323.c#L518">518</a>                               unsigned int protoff,
<a name="L519" href="source/net/ipv4/netfilter/nf_nat_h323.c#L519">519</a>                               unsigned char **<a href="ident?i=data">data</a>, int dataoff,
<a name="L520" href="source/net/ipv4/netfilter/nf_nat_h323.c#L520">520</a>                               <a href="ident?i=TransportAddress">TransportAddress</a> *taddr, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>,
<a name="L521" href="source/net/ipv4/netfilter/nf_nat_h323.c#L521">521</a>                               struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *exp)
<a name="L522" href="source/net/ipv4/netfilter/nf_nat_h323.c#L522">522</a> {
<a name="L523" href="source/net/ipv4/netfilter/nf_nat_h323.c#L523">523</a>         int <a href="ident?i=dir">dir</a> = <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo);
<a name="L524" href="source/net/ipv4/netfilter/nf_nat_h323.c#L524">524</a>         <a href="ident?i=u_int16_t">u_int16_t</a> nated_port;
<a name="L525" href="source/net/ipv4/netfilter/nf_nat_h323.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/netfilter/nf_nat_h323.c#L526">526</a>         <b><i>/* Set expectations for NAT */</i></b>
<a name="L527" href="source/net/ipv4/netfilter/nf_nat_h323.c#L527">527</a>         exp-&gt;saved_addr = exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3;
<a name="L528" href="source/net/ipv4/netfilter/nf_nat_h323.c#L528">528</a>         exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
<a name="L529" href="source/net/ipv4/netfilter/nf_nat_h323.c#L529">529</a>         exp-&gt;saved_proto.tcp.<a href="ident?i=port">port</a> = exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>;
<a name="L530" href="source/net/ipv4/netfilter/nf_nat_h323.c#L530">530</a>         exp-&gt;expectfn = <a href="ident?i=ip_nat_callforwarding_expect">ip_nat_callforwarding_expect</a>;
<a name="L531" href="source/net/ipv4/netfilter/nf_nat_h323.c#L531">531</a>         exp-&gt;<a href="ident?i=dir">dir</a> = !<a href="ident?i=dir">dir</a>;
<a name="L532" href="source/net/ipv4/netfilter/nf_nat_h323.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/netfilter/nf_nat_h323.c#L533">533</a>         <b><i>/* Try to get same port: if not, try to change it. */</i></b>
<a name="L534" href="source/net/ipv4/netfilter/nf_nat_h323.c#L534">534</a>         for (nated_port = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=port">port</a>); nated_port != 0; nated_port++) {
<a name="L535" href="source/net/ipv4/netfilter/nf_nat_h323.c#L535">535</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L536" href="source/net/ipv4/netfilter/nf_nat_h323.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/netfilter/nf_nat_h323.c#L537">537</a>                 exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a> = <a href="ident?i=htons">htons</a>(nated_port);
<a name="L538" href="source/net/ipv4/netfilter/nf_nat_h323.c#L538">538</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_expect_related">nf_ct_expect_related</a>(exp);
<a name="L539" href="source/net/ipv4/netfilter/nf_nat_h323.c#L539">539</a>                 if (<a href="ident?i=ret">ret</a> == 0)
<a name="L540" href="source/net/ipv4/netfilter/nf_nat_h323.c#L540">540</a>                         break;
<a name="L541" href="source/net/ipv4/netfilter/nf_nat_h323.c#L541">541</a>                 else if (<a href="ident?i=ret">ret</a> != -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L542" href="source/net/ipv4/netfilter/nf_nat_h323.c#L542">542</a>                         nated_port = 0;
<a name="L543" href="source/net/ipv4/netfilter/nf_nat_h323.c#L543">543</a>                         break;
<a name="L544" href="source/net/ipv4/netfilter/nf_nat_h323.c#L544">544</a>                 }
<a name="L545" href="source/net/ipv4/netfilter/nf_nat_h323.c#L545">545</a>         }
<a name="L546" href="source/net/ipv4/netfilter/nf_nat_h323.c#L546">546</a> 
<a name="L547" href="source/net/ipv4/netfilter/nf_nat_h323.c#L547">547</a>         if (nated_port == 0) {  <b><i>/* No port available */</i></b>
<a name="L548" href="source/net/ipv4/netfilter/nf_nat_h323.c#L548">548</a>                 <a href="ident?i=net_notice_ratelimited">net_notice_ratelimited</a>(<i>"nf_nat_q931: out of TCP ports\n"</i>);
<a name="L549" href="source/net/ipv4/netfilter/nf_nat_h323.c#L549">549</a>                 return 0;
<a name="L550" href="source/net/ipv4/netfilter/nf_nat_h323.c#L550">550</a>         }
<a name="L551" href="source/net/ipv4/netfilter/nf_nat_h323.c#L551">551</a> 
<a name="L552" href="source/net/ipv4/netfilter/nf_nat_h323.c#L552">552</a>         <b><i>/* Modify signal */</i></b>
<a name="L553" href="source/net/ipv4/netfilter/nf_nat_h323.c#L553">553</a>         if (!<a href="ident?i=set_h225_addr">set_h225_addr</a>(<a href="ident?i=skb">skb</a>, protoff, <a href="ident?i=data">data</a>, dataoff, taddr,
<a name="L554" href="source/net/ipv4/netfilter/nf_nat_h323.c#L554">554</a>                            &amp;ct-&gt;tuplehash[!<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3,
<a name="L555" href="source/net/ipv4/netfilter/nf_nat_h323.c#L555">555</a>                            <a href="ident?i=htons">htons</a>(nated_port)) == 0) {
<a name="L556" href="source/net/ipv4/netfilter/nf_nat_h323.c#L556">556</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(exp);
<a name="L557" href="source/net/ipv4/netfilter/nf_nat_h323.c#L557">557</a>                 return -1;
<a name="L558" href="source/net/ipv4/netfilter/nf_nat_h323.c#L558">558</a>         }
<a name="L559" href="source/net/ipv4/netfilter/nf_nat_h323.c#L559">559</a> 
<a name="L560" href="source/net/ipv4/netfilter/nf_nat_h323.c#L560">560</a>         <b><i>/* Success */</i></b>
<a name="L561" href="source/net/ipv4/netfilter/nf_nat_h323.c#L561">561</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"nf_nat_q931: expect Call Forwarding %pI4:%hu-&gt;%pI4:%hu\n"</i>,
<a name="L562" href="source/net/ipv4/netfilter/nf_nat_h323.c#L562">562</a>                  &amp;exp-&gt;tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L563" href="source/net/ipv4/netfilter/nf_nat_h323.c#L563">563</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=src">src</a>.u.tcp.<a href="ident?i=port">port</a>),
<a name="L564" href="source/net/ipv4/netfilter/nf_nat_h323.c#L564">564</a>                  &amp;exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>,
<a name="L565" href="source/net/ipv4/netfilter/nf_nat_h323.c#L565">565</a>                  <a href="ident?i=ntohs">ntohs</a>(exp-&gt;tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>));
<a name="L566" href="source/net/ipv4/netfilter/nf_nat_h323.c#L566">566</a> 
<a name="L567" href="source/net/ipv4/netfilter/nf_nat_h323.c#L567">567</a>         return 0;
<a name="L568" href="source/net/ipv4/netfilter/nf_nat_h323.c#L568">568</a> }
<a name="L569" href="source/net/ipv4/netfilter/nf_nat_h323.c#L569">569</a> 
<a name="L570" href="source/net/ipv4/netfilter/nf_nat_h323.c#L570">570</a> static struct <a href="ident?i=nf_ct_helper_expectfn">nf_ct_helper_expectfn</a> <a href="ident?i=q931_nat">q931_nat</a> = {
<a name="L571" href="source/net/ipv4/netfilter/nf_nat_h323.c#L571">571</a>         .<a href="ident?i=name">name</a>           = <i>"Q.931"</i>,
<a name="L572" href="source/net/ipv4/netfilter/nf_nat_h323.c#L572">572</a>         .expectfn       = <a href="ident?i=ip_nat_q931_expect">ip_nat_q931_expect</a>,
<a name="L573" href="source/net/ipv4/netfilter/nf_nat_h323.c#L573">573</a> };
<a name="L574" href="source/net/ipv4/netfilter/nf_nat_h323.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/netfilter/nf_nat_h323.c#L575">575</a> static struct <a href="ident?i=nf_ct_helper_expectfn">nf_ct_helper_expectfn</a> <a href="ident?i=callforwarding_nat">callforwarding_nat</a> = {
<a name="L576" href="source/net/ipv4/netfilter/nf_nat_h323.c#L576">576</a>         .<a href="ident?i=name">name</a>           = <i>"callforwarding"</i>,
<a name="L577" href="source/net/ipv4/netfilter/nf_nat_h323.c#L577">577</a>         .expectfn       = <a href="ident?i=ip_nat_callforwarding_expect">ip_nat_callforwarding_expect</a>,
<a name="L578" href="source/net/ipv4/netfilter/nf_nat_h323.c#L578">578</a> };
<a name="L579" href="source/net/ipv4/netfilter/nf_nat_h323.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/netfilter/nf_nat_h323.c#L580">580</a> <b><i>/****************************************************************************/</i></b>
<a name="L581" href="source/net/ipv4/netfilter/nf_nat_h323.c#L581">581</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=init">init</a>(void)
<a name="L582" href="source/net/ipv4/netfilter/nf_nat_h323.c#L582">582</a> {
<a name="L583" href="source/net/ipv4/netfilter/nf_nat_h323.c#L583">583</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=set_h245_addr_hook">set_h245_addr_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L584" href="source/net/ipv4/netfilter/nf_nat_h323.c#L584">584</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=set_h225_addr_hook">set_h225_addr_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L585" href="source/net/ipv4/netfilter/nf_nat_h323.c#L585">585</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=set_sig_addr_hook">set_sig_addr_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L586" href="source/net/ipv4/netfilter/nf_nat_h323.c#L586">586</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=set_ras_addr_hook">set_ras_addr_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L587" href="source/net/ipv4/netfilter/nf_nat_h323.c#L587">587</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nat_rtp_rtcp_hook">nat_rtp_rtcp_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L588" href="source/net/ipv4/netfilter/nf_nat_h323.c#L588">588</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nat_t120_hook">nat_t120_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L589" href="source/net/ipv4/netfilter/nf_nat_h323.c#L589">589</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nat_h245_hook">nat_h245_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L590" href="source/net/ipv4/netfilter/nf_nat_h323.c#L590">590</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nat_callforwarding_hook">nat_callforwarding_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L591" href="source/net/ipv4/netfilter/nf_nat_h323.c#L591">591</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nat_q931_hook">nat_q931_hook</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L592" href="source/net/ipv4/netfilter/nf_nat_h323.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/netfilter/nf_nat_h323.c#L593">593</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_h245_addr_hook">set_h245_addr_hook</a>, <a href="ident?i=set_h245_addr">set_h245_addr</a>);
<a name="L594" href="source/net/ipv4/netfilter/nf_nat_h323.c#L594">594</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_h225_addr_hook">set_h225_addr_hook</a>, <a href="ident?i=set_h225_addr">set_h225_addr</a>);
<a name="L595" href="source/net/ipv4/netfilter/nf_nat_h323.c#L595">595</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_sig_addr_hook">set_sig_addr_hook</a>, <a href="ident?i=set_sig_addr">set_sig_addr</a>);
<a name="L596" href="source/net/ipv4/netfilter/nf_nat_h323.c#L596">596</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_ras_addr_hook">set_ras_addr_hook</a>, <a href="ident?i=set_ras_addr">set_ras_addr</a>);
<a name="L597" href="source/net/ipv4/netfilter/nf_nat_h323.c#L597">597</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_rtp_rtcp_hook">nat_rtp_rtcp_hook</a>, <a href="ident?i=nat_rtp_rtcp">nat_rtp_rtcp</a>);
<a name="L598" href="source/net/ipv4/netfilter/nf_nat_h323.c#L598">598</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_t120_hook">nat_t120_hook</a>, <a href="ident?i=nat_t120">nat_t120</a>);
<a name="L599" href="source/net/ipv4/netfilter/nf_nat_h323.c#L599">599</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_h245_hook">nat_h245_hook</a>, <a href="ident?i=nat_h245">nat_h245</a>);
<a name="L600" href="source/net/ipv4/netfilter/nf_nat_h323.c#L600">600</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_callforwarding_hook">nat_callforwarding_hook</a>, <a href="ident?i=nat_callforwarding">nat_callforwarding</a>);
<a name="L601" href="source/net/ipv4/netfilter/nf_nat_h323.c#L601">601</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_q931_hook">nat_q931_hook</a>, <a href="ident?i=nat_q931">nat_q931</a>);
<a name="L602" href="source/net/ipv4/netfilter/nf_nat_h323.c#L602">602</a>         <a href="ident?i=nf_ct_helper_expectfn_register">nf_ct_helper_expectfn_register</a>(&amp;<a href="ident?i=q931_nat">q931_nat</a>);
<a name="L603" href="source/net/ipv4/netfilter/nf_nat_h323.c#L603">603</a>         <a href="ident?i=nf_ct_helper_expectfn_register">nf_ct_helper_expectfn_register</a>(&amp;<a href="ident?i=callforwarding_nat">callforwarding_nat</a>);
<a name="L604" href="source/net/ipv4/netfilter/nf_nat_h323.c#L604">604</a>         return 0;
<a name="L605" href="source/net/ipv4/netfilter/nf_nat_h323.c#L605">605</a> }
<a name="L606" href="source/net/ipv4/netfilter/nf_nat_h323.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/netfilter/nf_nat_h323.c#L607">607</a> <b><i>/****************************************************************************/</i></b>
<a name="L608" href="source/net/ipv4/netfilter/nf_nat_h323.c#L608">608</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=fini">fini</a>(void)
<a name="L609" href="source/net/ipv4/netfilter/nf_nat_h323.c#L609">609</a> {
<a name="L610" href="source/net/ipv4/netfilter/nf_nat_h323.c#L610">610</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_h245_addr_hook">set_h245_addr_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L611" href="source/net/ipv4/netfilter/nf_nat_h323.c#L611">611</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_h225_addr_hook">set_h225_addr_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L612" href="source/net/ipv4/netfilter/nf_nat_h323.c#L612">612</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_sig_addr_hook">set_sig_addr_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L613" href="source/net/ipv4/netfilter/nf_nat_h323.c#L613">613</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=set_ras_addr_hook">set_ras_addr_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L614" href="source/net/ipv4/netfilter/nf_nat_h323.c#L614">614</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_rtp_rtcp_hook">nat_rtp_rtcp_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L615" href="source/net/ipv4/netfilter/nf_nat_h323.c#L615">615</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_t120_hook">nat_t120_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L616" href="source/net/ipv4/netfilter/nf_nat_h323.c#L616">616</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_h245_hook">nat_h245_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L617" href="source/net/ipv4/netfilter/nf_nat_h323.c#L617">617</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_callforwarding_hook">nat_callforwarding_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L618" href="source/net/ipv4/netfilter/nf_nat_h323.c#L618">618</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nat_q931_hook">nat_q931_hook</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L619" href="source/net/ipv4/netfilter/nf_nat_h323.c#L619">619</a>         <a href="ident?i=nf_ct_helper_expectfn_unregister">nf_ct_helper_expectfn_unregister</a>(&amp;<a href="ident?i=q931_nat">q931_nat</a>);
<a name="L620" href="source/net/ipv4/netfilter/nf_nat_h323.c#L620">620</a>         <a href="ident?i=nf_ct_helper_expectfn_unregister">nf_ct_helper_expectfn_unregister</a>(&amp;<a href="ident?i=callforwarding_nat">callforwarding_nat</a>);
<a name="L621" href="source/net/ipv4/netfilter/nf_nat_h323.c#L621">621</a>         <a href="ident?i=synchronize_rcu">synchronize_rcu</a>();
<a name="L622" href="source/net/ipv4/netfilter/nf_nat_h323.c#L622">622</a> }
<a name="L623" href="source/net/ipv4/netfilter/nf_nat_h323.c#L623">623</a> 
<a name="L624" href="source/net/ipv4/netfilter/nf_nat_h323.c#L624">624</a> <b><i>/****************************************************************************/</i></b>
<a name="L625" href="source/net/ipv4/netfilter/nf_nat_h323.c#L625">625</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=init">init</a>);
<a name="L626" href="source/net/ipv4/netfilter/nf_nat_h323.c#L626">626</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=fini">fini</a>);
<a name="L627" href="source/net/ipv4/netfilter/nf_nat_h323.c#L627">627</a> 
<a name="L628" href="source/net/ipv4/netfilter/nf_nat_h323.c#L628">628</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Jing Min Zhao &lt;zhaojingmin@users.sourceforge.net&gt;"</i>);
<a name="L629" href="source/net/ipv4/netfilter/nf_nat_h323.c#L629">629</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"H.323 NAT helper"</i>);
<a name="L630" href="source/net/ipv4/netfilter/nf_nat_h323.c#L630">630</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L631" href="source/net/ipv4/netfilter/nf_nat_h323.c#L631">631</a> <a href="ident?i=MODULE_ALIAS">MODULE_ALIAS</a>(<i>"ip_nat_h323"</i>);
<a name="L632" href="source/net/ipv4/netfilter/nf_nat_h323.c#L632">632</a> </pre></div><p>
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
