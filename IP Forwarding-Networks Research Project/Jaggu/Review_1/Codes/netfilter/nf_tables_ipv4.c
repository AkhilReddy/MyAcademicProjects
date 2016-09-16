<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_tables_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_tables_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_tables_ipv4.c">nf_tables_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L2">2</a> <b><i> * Copyright (c) 2008 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L3">3</a> <b><i> * Copyright (c) 2012-2013 Pablo Neira Ayuso &lt;pablo@netfilter.org&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L5">5</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L6">6</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L7">7</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L9">9</a> <b><i> * Development of this code funded by Astaro AG (<a href="http://www.astaro.com/)">http://www.astaro.com/)</a></i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L12">12</a> #include &lt;linux/init.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L14">14</a> #include &lt;linux/ip.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L15">15</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L16">16</a> #include &lt;net/netfilter/nf_tables.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L17">17</a> #include &lt;net/net_namespace.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L18">18</a> #include &lt;net/ip.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L19">19</a> #include &lt;net/netfilter/nf_tables_ipv4.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L21">21</a> static unsigned int <a href="ident?i=nft_do_chain_ipv4">nft_do_chain_ipv4</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L22" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L22">22</a>                                       struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L23" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L23">23</a>                                       const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L24" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L24">24</a> {
 <a name="L25" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L25">25</a>         struct <a href="ident?i=nft_pktinfo">nft_pktinfo</a> <a href="ident?i=pkt">pkt</a>;
 <a name="L26" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L27">27</a>         <a href="ident?i=nft_set_pktinfo_ipv4">nft_set_pktinfo_ipv4</a>(&amp;<a href="ident?i=pkt">pkt</a>, <a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>);
 <a name="L28" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L29">29</a>         return <a href="ident?i=nft_do_chain">nft_do_chain</a>(&amp;<a href="ident?i=pkt">pkt</a>, <a href="ident?i=ops">ops</a>);
 <a name="L30" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L30">30</a> }
 <a name="L31" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L32">32</a> static unsigned int <a href="ident?i=nft_ipv4_output">nft_ipv4_output</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L33" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L33">33</a>                                     struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L34" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L34">34</a>                                     const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L35" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L35">35</a> {
 <a name="L36" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L36">36</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
 <a name="L37" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L37">37</a>                      <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;ihl &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) / 4)) {
 <a name="L38" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L38">38</a>                 if (<a href="ident?i=net_ratelimit">net_ratelimit</a>())
 <a name="L39" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L39">39</a>                         <a href="ident?i=pr_info">pr_info</a>(<i>"nf_tables_ipv4: ignoring short SOCK_RAW "</i>
 <a name="L40" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L40">40</a>                                 <i>"packet\n"</i>);
 <a name="L41" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L41">41</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L42" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L42">42</a>         }
 <a name="L43" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L44">44</a>         return <a href="ident?i=nft_do_chain_ipv4">nft_do_chain_ipv4</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>);
 <a name="L45" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L45">45</a> }
 <a name="L46" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L47">47</a> struct <a href="ident?i=nft_af_info">nft_af_info</a> <a href="ident?i=nft_af_ipv4">nft_af_ipv4</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L48" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L48">48</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L49" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L49">49</a>         .nhooks         = NF_INET_NUMHOOKS,
 <a name="L50" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L50">50</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L51" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L51">51</a>         .nops           = 1,
 <a name="L52" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L52">52</a>         .<a href="ident?i=hooks">hooks</a>          = {
 <a name="L53" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L53">53</a>                 [NF_INET_LOCAL_IN]      = <a href="ident?i=nft_do_chain_ipv4">nft_do_chain_ipv4</a>,
 <a name="L54" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L54">54</a>                 [NF_INET_LOCAL_OUT]     = <a href="ident?i=nft_ipv4_output">nft_ipv4_output</a>,
 <a name="L55" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L55">55</a>                 [NF_INET_FORWARD]       = <a href="ident?i=nft_do_chain_ipv4">nft_do_chain_ipv4</a>,
 <a name="L56" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L56">56</a>                 [NF_INET_PRE_ROUTING]   = <a href="ident?i=nft_do_chain_ipv4">nft_do_chain_ipv4</a>,
 <a name="L57" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L57">57</a>                 [NF_INET_POST_ROUTING]  = <a href="ident?i=nft_do_chain_ipv4">nft_do_chain_ipv4</a>,
 <a name="L58" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L58">58</a>         },
 <a name="L59" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L59">59</a> };
 <a name="L60" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L60">60</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nft_af_ipv4">nft_af_ipv4</a>);
 <a name="L61" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L62">62</a> static int <a href="ident?i=nf_tables_ipv4_init_net">nf_tables_ipv4_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L63" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L63">63</a> {
 <a name="L64" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L64">64</a>         <a href="ident?i=net">net</a>-&gt;nft.ipv4 = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=nft_af_info">nft_af_info</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
 <a name="L65" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L65">65</a>         if (<a href="ident?i=net">net</a>-&gt;nft.ipv4 == <a href="ident?i=NULL">NULL</a>)
 <a name="L66" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L66">66</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L67" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L68">68</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=net">net</a>-&gt;nft.ipv4, &amp;<a href="ident?i=nft_af_ipv4">nft_af_ipv4</a>, sizeof(<a href="ident?i=nft_af_ipv4">nft_af_ipv4</a>));
 <a name="L69" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L70">70</a>         if (<a href="ident?i=nft_register_afinfo">nft_register_afinfo</a>(<a href="ident?i=net">net</a>, <a href="ident?i=net">net</a>-&gt;nft.ipv4) &lt; 0)
 <a name="L71" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L71">71</a>                 goto <a href="ident?i=err">err</a>;
 <a name="L72" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L73">73</a>         return 0;
 <a name="L74" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L74">74</a> <a href="ident?i=err">err</a>:
 <a name="L75" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L75">75</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;nft.ipv4);
 <a name="L76" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L76">76</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L77" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L77">77</a> }
 <a name="L78" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L79">79</a> static void <a href="ident?i=nf_tables_ipv4_exit_net">nf_tables_ipv4_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L80" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L80">80</a> {
 <a name="L81" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L81">81</a>         <a href="ident?i=nft_unregister_afinfo">nft_unregister_afinfo</a>(<a href="ident?i=net">net</a>-&gt;nft.ipv4);
 <a name="L82" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L82">82</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;nft.ipv4);
 <a name="L83" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L85">85</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=nf_tables_ipv4_net_ops">nf_tables_ipv4_net_ops</a> = {
 <a name="L86" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L86">86</a>         .<a href="ident?i=init">init</a>   = <a href="ident?i=nf_tables_ipv4_init_net">nf_tables_ipv4_init_net</a>,
 <a name="L87" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L87">87</a>         .<a href="ident?i=exit">exit</a>   = <a href="ident?i=nf_tables_ipv4_exit_net">nf_tables_ipv4_exit_net</a>,
 <a name="L88" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L88">88</a> };
 <a name="L89" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L90">90</a> static const struct <a href="ident?i=nf_chain_type">nf_chain_type</a> <a href="ident?i=filter_ipv4">filter_ipv4</a> = {
 <a name="L91" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L91">91</a>         .<a href="ident?i=name">name</a>           = <i>"filter"</i>,
 <a name="L92" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L92">92</a>         .<a href="ident?i=type">type</a>           = NFT_CHAIN_T_DEFAULT,
 <a name="L93" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L93">93</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L94" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L94">94</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L95" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L95">95</a>         .hook_mask      = (1 &lt;&lt; NF_INET_LOCAL_IN) |
 <a name="L96" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L96">96</a>                           (1 &lt;&lt; NF_INET_LOCAL_OUT) |
 <a name="L97" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L97">97</a>                           (1 &lt;&lt; NF_INET_FORWARD) |
 <a name="L98" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L98">98</a>                           (1 &lt;&lt; NF_INET_PRE_ROUTING) |
 <a name="L99" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L99">99</a>                           (1 &lt;&lt; NF_INET_POST_ROUTING),
<a name="L100" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L100">100</a> };
<a name="L101" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L102">102</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_tables_ipv4_init">nf_tables_ipv4_init</a>(void)
<a name="L103" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L104">104</a>         int <a href="ident?i=ret">ret</a>;
<a name="L105" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L106">106</a>         <a href="ident?i=nft_register_chain_type">nft_register_chain_type</a>(&amp;<a href="ident?i=filter_ipv4">filter_ipv4</a>);
<a name="L107" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L107">107</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=nf_tables_ipv4_net_ops">nf_tables_ipv4_net_ops</a>);
<a name="L108" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L108">108</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L109" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L109">109</a>                 <a href="ident?i=nft_unregister_chain_type">nft_unregister_chain_type</a>(&amp;<a href="ident?i=filter_ipv4">filter_ipv4</a>);
<a name="L110" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L111">111</a>         return <a href="ident?i=ret">ret</a>;
<a name="L112" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L112">112</a> }
<a name="L113" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L114">114</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_tables_ipv4_exit">nf_tables_ipv4_exit</a>(void)
<a name="L115" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L115">115</a> {
<a name="L116" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L116">116</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=nf_tables_ipv4_net_ops">nf_tables_ipv4_net_ops</a>);
<a name="L117" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L117">117</a>         <a href="ident?i=nft_unregister_chain_type">nft_unregister_chain_type</a>(&amp;<a href="ident?i=filter_ipv4">filter_ipv4</a>);
<a name="L118" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L120">120</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_tables_ipv4_init">nf_tables_ipv4_init</a>);
<a name="L121" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L121">121</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_tables_ipv4_exit">nf_tables_ipv4_exit</a>);
<a name="L122" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L123">123</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L124" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L124">124</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Patrick McHardy &lt;kaber@trash.net&gt;"</i>);
<a name="L125" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L125">125</a> <a href="ident?i=MODULE_ALIAS_NFT_FAMILY">MODULE_ALIAS_NFT_FAMILY</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L126" href="source/net/ipv4/netfilter/nf_tables_ipv4.c#L126">126</a> </pre></div><p>
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
