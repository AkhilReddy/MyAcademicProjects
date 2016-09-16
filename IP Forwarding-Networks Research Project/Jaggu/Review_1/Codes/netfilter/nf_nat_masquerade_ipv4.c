<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c">nf_nat_masquerade_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L1">1</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L2">2</a> <b><i> * (C) 2002-2006 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L9">9</a> #include &lt;linux/types.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L10">10</a> #include &lt;linux/module.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L11">11</a> #include &lt;linux/atomic.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L12">12</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L13">13</a> #include &lt;linux/ip.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L14">14</a> #include &lt;linux/timer.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L15">15</a> #include &lt;linux/netfilter.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L16">16</a> #include &lt;net/protocol.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L17">17</a> #include &lt;net/ip.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L18">18</a> #include &lt;net/checksum.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L19">19</a> #include &lt;net/route.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L20">20</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L21">21</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L22">22</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L23">23</a> #include &lt;net/netfilter/ipv4/nf_nat_masquerade.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L25">25</a> unsigned int
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L26">26</a> <a href="ident?i=nf_nat_masquerade_ipv4">nf_nat_masquerade_ipv4</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int hooknum,
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L27">27</a>                        const struct <a href="ident?i=nf_nat_range">nf_nat_range</a> *<a href="ident?i=range">range</a>,
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L28">28</a>                        const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=out">out</a>)
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L29">29</a> {
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L30">30</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L31">31</a>         struct <a href="ident?i=nf_conn_nat">nf_conn_nat</a> *nat;
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L32">32</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L33">33</a>         struct <a href="ident?i=nf_nat_range">nf_nat_range</a> newrange;
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L34">34</a>         const struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L35">35</a>         <a href="ident?i=__be32">__be32</a> newsrc, nh;
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L37">37</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(hooknum == NF_INET_POST_ROUTING);
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L39">39</a>         ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L40">40</a>         nat = <a href="ident?i=nfct_nat">nfct_nat</a>(ct);
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L42">42</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(ct &amp;&amp; (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L43">43</a>                             ctinfo == IP_CT_RELATED_REPLY));
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L45">45</a>         <b><i>/* Source address is 0.0.0.0 - locally generated packet that is</i></b>
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L46">46</a> <b><i>         * probably not supposed to be masqueraded.</i></b>
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L47">47</a> <b><i>         */</i></b>
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L48">48</a>         if (ct-&gt;tuplehash[IP_CT_DIR_ORIGINAL].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> == 0)
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L49">49</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L51">51</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L52">52</a>         nh = <a href="ident?i=rt_nexthop">rt_nexthop</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L53">53</a>         newsrc = <a href="ident?i=inet_select_addr">inet_select_addr</a>(<a href="ident?i=out">out</a>, nh, RT_SCOPE_UNIVERSE);
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L54">54</a>         if (!newsrc) {
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L55">55</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s ate my IP address\n"</i>, <a href="ident?i=out">out</a>-&gt;<a href="ident?i=name">name</a>);
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L56">56</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L57">57</a>         }
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L59">59</a>         nat-&gt;masq_index = <a href="ident?i=out">out</a>-&gt;ifindex;
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L61">61</a>         <b><i>/* Transfer from original range. */</i></b>
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L62">62</a>         <a href="ident?i=memset">memset</a>(&amp;newrange.<a href="ident?i=min_addr">min_addr</a>, 0, sizeof(newrange.<a href="ident?i=min_addr">min_addr</a>));
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L63">63</a>         <a href="ident?i=memset">memset</a>(&amp;newrange.<a href="ident?i=max_addr">max_addr</a>, 0, sizeof(newrange.<a href="ident?i=max_addr">max_addr</a>));
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L64">64</a>         newrange.<a href="ident?i=flags">flags</a>       = <a href="ident?i=range">range</a>-&gt;<a href="ident?i=flags">flags</a> | <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>;
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L65">65</a>         newrange.<a href="ident?i=min_addr">min_addr</a>.<a href="ident?i=ip">ip</a> = newsrc;
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L66">66</a>         newrange.<a href="ident?i=max_addr">max_addr</a>.<a href="ident?i=ip">ip</a> = newsrc;
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L67">67</a>         newrange.<a href="ident?i=min_proto">min_proto</a>   = <a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_proto">min_proto</a>;
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L68">68</a>         newrange.<a href="ident?i=max_proto">max_proto</a>   = <a href="ident?i=range">range</a>-&gt;<a href="ident?i=max_proto">max_proto</a>;
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L70">70</a>         <b><i>/* Hand modified range to generic setup. */</i></b>
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L71">71</a>         return <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(ct, &amp;newrange, NF_NAT_MANIP_SRC);
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L73">73</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_masquerade_ipv4">nf_nat_masquerade_ipv4</a>);
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L75">75</a> static int <a href="ident?i=device_cmp">device_cmp</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *<a href="ident?i=i">i</a>, void *ifindex)
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L76">76</a> {
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L77">77</a>         const struct <a href="ident?i=nf_conn_nat">nf_conn_nat</a> *nat = <a href="ident?i=nfct_nat">nfct_nat</a>(<a href="ident?i=i">i</a>);
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L79">79</a>         if (!nat)
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L80">80</a>                 return 0;
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L81">81</a>         if (<a href="ident?i=nf_ct_l3num">nf_ct_l3num</a>(<a href="ident?i=i">i</a>) != NFPROTO_IPV4)
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L82">82</a>                 return 0;
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L83">83</a>         return nat-&gt;masq_index == (int)(long)ifindex;
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L84">84</a> }
 <a name="L85" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L86">86</a> static int <a href="ident?i=masq_device_event">masq_device_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>,
 <a name="L87" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L87">87</a>                              unsigned long <a href="ident?i=event">event</a>,
 <a name="L88" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L88">88</a>                              void *<a href="ident?i=ptr">ptr</a>)
 <a name="L89" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L89">89</a> {
 <a name="L90" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L90">90</a>         const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=netdev_notifier_info_to_dev">netdev_notifier_info_to_dev</a>(<a href="ident?i=ptr">ptr</a>);
 <a name="L91" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L91">91</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
 <a name="L92" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L93">93</a>         if (<a href="ident?i=event">event</a> == <a href="ident?i=NETDEV_DOWN">NETDEV_DOWN</a>) {
 <a name="L94" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L94">94</a>                 <b><i>/* Device was downed.  Search entire table for</i></b>
 <a name="L95" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L95">95</a> <b><i>                 * conntracks which were associated with that device,</i></b>
 <a name="L96" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L96">96</a> <b><i>                 * and forget them.</i></b>
 <a name="L97" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L97">97</a> <b><i>                 */</i></b>
 <a name="L98" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L98">98</a>                 <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(<a href="ident?i=dev">dev</a>-&gt;ifindex != 0);
 <a name="L99" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L100">100</a>                 <a href="ident?i=nf_ct_iterate_cleanup">nf_ct_iterate_cleanup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=device_cmp">device_cmp</a>,
<a name="L101" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L101">101</a>                                       (void *)(long)<a href="ident?i=dev">dev</a>-&gt;ifindex, 0, 0);
<a name="L102" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L102">102</a>         }
<a name="L103" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L104">104</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L105" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L107">107</a> static int <a href="ident?i=masq_inet_event">masq_inet_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>,
<a name="L108" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L108">108</a>                            unsigned long <a href="ident?i=event">event</a>,
<a name="L109" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L109">109</a>                            void *<a href="ident?i=ptr">ptr</a>)
<a name="L110" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L110">110</a> {
<a name="L111" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L111">111</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = ((struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *)<a href="ident?i=ptr">ptr</a>)-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L112" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L112">112</a>         struct <a href="ident?i=netdev_notifier_info">netdev_notifier_info</a> <a href="ident?i=info">info</a>;
<a name="L113" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L114">114</a>         <a href="ident?i=netdev_notifier_info_init">netdev_notifier_info_init</a>(&amp;<a href="ident?i=info">info</a>, <a href="ident?i=dev">dev</a>);
<a name="L115" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L115">115</a>         return <a href="ident?i=masq_device_event">masq_device_event</a>(<a href="ident?i=this">this</a>, <a href="ident?i=event">event</a>, &amp;<a href="ident?i=info">info</a>);
<a name="L116" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L116">116</a> }
<a name="L117" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L118">118</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=masq_dev_notifier">masq_dev_notifier</a> = {
<a name="L119" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L119">119</a>         .notifier_call  = <a href="ident?i=masq_device_event">masq_device_event</a>,
<a name="L120" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L120">120</a> };
<a name="L121" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L122">122</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=masq_inet_notifier">masq_inet_notifier</a> = {
<a name="L123" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L123">123</a>         .notifier_call  = <a href="ident?i=masq_inet_event">masq_inet_event</a>,
<a name="L124" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L124">124</a> };
<a name="L125" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L126">126</a> static <a href="ident?i=atomic_t">atomic_t</a> <a href="ident?i=masquerade_notifier_refcount">masquerade_notifier_refcount</a> = <a href="ident?i=ATOMIC_INIT">ATOMIC_INIT</a>(0);
<a name="L127" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L128">128</a> void <a href="ident?i=nf_nat_masquerade_ipv4_register_notifier">nf_nat_masquerade_ipv4_register_notifier</a>(void)
<a name="L129" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L129">129</a> {
<a name="L130" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L130">130</a>         <b><i>/* check if the notifier was already set */</i></b>
<a name="L131" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L131">131</a>         if (<a href="ident?i=atomic_inc_return">atomic_inc_return</a>(&amp;<a href="ident?i=masquerade_notifier_refcount">masquerade_notifier_refcount</a>) &gt; 1)
<a name="L132" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L132">132</a>                 return;
<a name="L133" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L134">134</a>         <b><i>/* Register for device down reports */</i></b>
<a name="L135" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L135">135</a>         <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=masq_dev_notifier">masq_dev_notifier</a>);
<a name="L136" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L136">136</a>         <b><i>/* Register IP address change reports */</i></b>
<a name="L137" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L137">137</a>         <a href="ident?i=register_inetaddr_notifier">register_inetaddr_notifier</a>(&amp;<a href="ident?i=masq_inet_notifier">masq_inet_notifier</a>);
<a name="L138" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L138">138</a> }
<a name="L139" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L139">139</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_masquerade_ipv4_register_notifier">nf_nat_masquerade_ipv4_register_notifier</a>);
<a name="L140" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L141">141</a> void <a href="ident?i=nf_nat_masquerade_ipv4_unregister_notifier">nf_nat_masquerade_ipv4_unregister_notifier</a>(void)
<a name="L142" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L142">142</a> {
<a name="L143" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L143">143</a>         <b><i>/* check if the notifier still has clients */</i></b>
<a name="L144" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L144">144</a>         if (<a href="ident?i=atomic_dec_return">atomic_dec_return</a>(&amp;<a href="ident?i=masquerade_notifier_refcount">masquerade_notifier_refcount</a>) &gt; 0)
<a name="L145" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L145">145</a>                 return;
<a name="L146" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L147">147</a>         <a href="ident?i=unregister_netdevice_notifier">unregister_netdevice_notifier</a>(&amp;<a href="ident?i=masq_dev_notifier">masq_dev_notifier</a>);
<a name="L148" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L148">148</a>         <a href="ident?i=unregister_inetaddr_notifier">unregister_inetaddr_notifier</a>(&amp;<a href="ident?i=masq_inet_notifier">masq_inet_notifier</a>);
<a name="L149" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L149">149</a> }
<a name="L150" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L150">150</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_masquerade_ipv4_unregister_notifier">nf_nat_masquerade_ipv4_unregister_notifier</a>);
<a name="L151" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L152">152</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L153" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L153">153</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Rusty Russell &lt;rusty@rustcorp.com.au&gt;"</i>);
<a name="L154" href="source/net/ipv4/netfilter/nf_nat_masquerade_ipv4.c#L154">154</a> </pre></div><p>
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
