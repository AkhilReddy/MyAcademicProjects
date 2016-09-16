<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nft_chain_route_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nft_chain_route_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c">nft_chain_route_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L2">2</a> <b><i> * Copyright (c) 2008 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L3">3</a> <b><i> * Copyright (c) 2012 Pablo Neira Ayuso &lt;pablo@netfilter.org&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L5">5</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L6">6</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L7">7</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L8">8</a> <b><i> */</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L9">9</a> 
 <a name="L10" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L10">10</a> #include &lt;linux/module.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L11">11</a> #include &lt;linux/init.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L12">12</a> #include &lt;linux/list.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L13">13</a> #include &lt;linux/skbuff.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L14">14</a> #include &lt;linux/netlink.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L15">15</a> #include &lt;linux/netfilter.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L16">16</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L17">17</a> #include &lt;linux/netfilter/nfnetlink.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L18">18</a> #include &lt;linux/netfilter/nf_tables.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L19">19</a> #include &lt;net/netfilter/nf_tables.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L20">20</a> #include &lt;net/netfilter/nf_tables_ipv4.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L21">21</a> #include &lt;net/route.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L22">22</a> #include &lt;net/ip.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L24">24</a> static unsigned int <a href="ident?i=nf_route_table_hook">nf_route_table_hook</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L25" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L25">25</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L26" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L26">26</a>                                         const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L27" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L27">27</a> {
 <a name="L28" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L28">28</a>         unsigned int <a href="ident?i=ret">ret</a>;
 <a name="L29" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L29">29</a>         struct <a href="ident?i=nft_pktinfo">nft_pktinfo</a> <a href="ident?i=pkt">pkt</a>;
 <a name="L30" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L30">30</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a>;
 <a name="L31" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L31">31</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
 <a name="L32" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L32">32</a>         <a href="ident?i=u_int8_t">u_int8_t</a> tos;
 <a name="L33" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L33">33</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L34" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L35">35</a>         <b><i>/* root is playing with raw sockets. */</i></b>
 <a name="L36" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L36">36</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
 <a name="L37" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L37">37</a>             <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>))
 <a name="L38" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L38">38</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L39" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L40">40</a>         <a href="ident?i=nft_set_pktinfo_ipv4">nft_set_pktinfo_ipv4</a>(&amp;<a href="ident?i=pkt">pkt</a>, <a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>);
 <a name="L41" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L42">42</a>         <a href="ident?i=mark">mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
 <a name="L43" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L43">43</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L44" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L44">44</a>         <a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L45" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L45">45</a>         <a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L46" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L46">46</a>         tos = iph-&gt;tos;
 <a name="L47" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L48">48</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nft_do_chain">nft_do_chain</a>(&amp;<a href="ident?i=pkt">pkt</a>, <a href="ident?i=ops">ops</a>);
 <a name="L49" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L49">49</a>         if (<a href="ident?i=ret">ret</a> != <a href="ident?i=NF_DROP">NF_DROP</a> &amp;&amp; <a href="ident?i=ret">ret</a> != <a href="ident?i=NF_QUEUE">NF_QUEUE</a>) {
 <a name="L50" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L50">50</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L51" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L52">52</a>                 if (iph-&gt;<a href="ident?i=saddr">saddr</a> != <a href="ident?i=saddr">saddr</a> ||
 <a name="L53" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L53">53</a>                     iph-&gt;<a href="ident?i=daddr">daddr</a> != <a href="ident?i=daddr">daddr</a> ||
 <a name="L54" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L54">54</a>                     <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> != <a href="ident?i=mark">mark</a> ||
 <a name="L55" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L55">55</a>                     iph-&gt;tos != tos)
 <a name="L56" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L56">56</a>                         if (<a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(<a href="ident?i=skb">skb</a>, RTN_UNSPEC))
 <a name="L57" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L57">57</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L58" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L58">58</a>         }
 <a name="L59" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L59">59</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L60" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L60">60</a> }
 <a name="L61" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L62">62</a> static const struct <a href="ident?i=nf_chain_type">nf_chain_type</a> <a href="ident?i=nft_chain_route_ipv4">nft_chain_route_ipv4</a> = {
 <a name="L63" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L63">63</a>         .<a href="ident?i=name">name</a>           = <i>"route"</i>,
 <a name="L64" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L64">64</a>         .<a href="ident?i=type">type</a>           = NFT_CHAIN_T_ROUTE,
 <a name="L65" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L65">65</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L66" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L66">66</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L67" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L67">67</a>         .hook_mask      = (1 &lt;&lt; NF_INET_LOCAL_OUT),
 <a name="L68" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L68">68</a>         .<a href="ident?i=hooks">hooks</a>          = {
 <a name="L69" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L69">69</a>                 [NF_INET_LOCAL_OUT]     = <a href="ident?i=nf_route_table_hook">nf_route_table_hook</a>,
 <a name="L70" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L70">70</a>         },
 <a name="L71" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L71">71</a> };
 <a name="L72" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L73">73</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nft_chain_route_init">nft_chain_route_init</a>(void)
 <a name="L74" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L74">74</a> {
 <a name="L75" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L75">75</a>         return <a href="ident?i=nft_register_chain_type">nft_register_chain_type</a>(&amp;<a href="ident?i=nft_chain_route_ipv4">nft_chain_route_ipv4</a>);
 <a name="L76" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L76">76</a> }
 <a name="L77" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L78">78</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nft_chain_route_exit">nft_chain_route_exit</a>(void)
 <a name="L79" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L79">79</a> {
 <a name="L80" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L80">80</a>         <a href="ident?i=nft_unregister_chain_type">nft_unregister_chain_type</a>(&amp;<a href="ident?i=nft_chain_route_ipv4">nft_chain_route_ipv4</a>);
 <a name="L81" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L83">83</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nft_chain_route_init">nft_chain_route_init</a>);
 <a name="L84" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L84">84</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nft_chain_route_exit">nft_chain_route_exit</a>);
 <a name="L85" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L86">86</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L87" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L87">87</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Patrick McHardy &lt;kaber@trash.net&gt;"</i>);
 <a name="L88" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L88">88</a> <a href="ident?i=MODULE_ALIAS_NFT_CHAIN">MODULE_ALIAS_NFT_CHAIN</a>(<a href="ident?i=AF_INET">AF_INET</a>, <i>"route"</i>);
 <a name="L89" href="source/net/ipv4/netfilter/nft_chain_route_ipv4.c#L89">89</a> </pre></div><p>
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
