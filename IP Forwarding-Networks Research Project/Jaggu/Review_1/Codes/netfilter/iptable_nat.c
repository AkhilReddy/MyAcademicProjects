<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/iptable_nat.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/iptable_nat.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_nat.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/iptable_nat.c">iptable_nat.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/iptable_nat.c#L1">1</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/iptable_nat.c#L2">2</a> <b><i> * (C) 2002-2006 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/iptable_nat.c#L3">3</a> <b><i> * (C) 2011 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/iptable_nat.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/iptable_nat.c#L5">5</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/iptable_nat.c#L6">6</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/iptable_nat.c#L7">7</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/iptable_nat.c#L8">8</a> <b><i> */</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/iptable_nat.c#L9">9</a> 
 <a name="L10" href="source/net/ipv4/netfilter/iptable_nat.c#L10">10</a> #include &lt;linux/module.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/iptable_nat.c#L11">11</a> #include &lt;linux/netfilter.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/iptable_nat.c#L12">12</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/iptable_nat.c#L13">13</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/iptable_nat.c#L14">14</a> #include &lt;linux/ip.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/iptable_nat.c#L15">15</a> #include &lt;net/ip.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/iptable_nat.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/netfilter/iptable_nat.c#L17">17</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/iptable_nat.c#L18">18</a> #include &lt;net/netfilter/nf_nat_core.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/iptable_nat.c#L19">19</a> #include &lt;net/netfilter/nf_nat_l3proto.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/iptable_nat.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/netfilter/iptable_nat.c#L21">21</a> static const struct <a href="ident?i=xt_table">xt_table</a> <a href="ident?i=nf_nat_ipv4_table">nf_nat_ipv4_table</a> = {
 <a name="L22" href="source/net/ipv4/netfilter/iptable_nat.c#L22">22</a>         .<a href="ident?i=name">name</a>           = <i>"nat"</i>,
 <a name="L23" href="source/net/ipv4/netfilter/iptable_nat.c#L23">23</a>         .valid_hooks    = (1 &lt;&lt; NF_INET_PRE_ROUTING) |
 <a name="L24" href="source/net/ipv4/netfilter/iptable_nat.c#L24">24</a>                           (1 &lt;&lt; NF_INET_POST_ROUTING) |
 <a name="L25" href="source/net/ipv4/netfilter/iptable_nat.c#L25">25</a>                           (1 &lt;&lt; NF_INET_LOCAL_OUT) |
 <a name="L26" href="source/net/ipv4/netfilter/iptable_nat.c#L26">26</a>                           (1 &lt;&lt; NF_INET_LOCAL_IN),
 <a name="L27" href="source/net/ipv4/netfilter/iptable_nat.c#L27">27</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L28" href="source/net/ipv4/netfilter/iptable_nat.c#L28">28</a>         .<a href="ident?i=af">af</a>             = NFPROTO_IPV4,
 <a name="L29" href="source/net/ipv4/netfilter/iptable_nat.c#L29">29</a> };
 <a name="L30" href="source/net/ipv4/netfilter/iptable_nat.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/netfilter/iptable_nat.c#L31">31</a> static unsigned int <a href="ident?i=iptable_nat_do_chain">iptable_nat_do_chain</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L32" href="source/net/ipv4/netfilter/iptable_nat.c#L32">32</a>                                          struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L33" href="source/net/ipv4/netfilter/iptable_nat.c#L33">33</a>                                          const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
 <a name="L34" href="source/net/ipv4/netfilter/iptable_nat.c#L34">34</a>                                          struct <a href="ident?i=nf_conn">nf_conn</a> *ct)
 <a name="L35" href="source/net/ipv4/netfilter/iptable_nat.c#L35">35</a> {
 <a name="L36" href="source/net/ipv4/netfilter/iptable_nat.c#L36">36</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=nf_ct_net">nf_ct_net</a>(ct);
 <a name="L37" href="source/net/ipv4/netfilter/iptable_nat.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/netfilter/iptable_nat.c#L38">38</a>         return <a href="ident?i=ipt_do_table">ipt_do_table</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=state">state</a>, <a href="ident?i=net">net</a>-&gt;ipv4.nat_table);
 <a name="L39" href="source/net/ipv4/netfilter/iptable_nat.c#L39">39</a> }
 <a name="L40" href="source/net/ipv4/netfilter/iptable_nat.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/iptable_nat.c#L41">41</a> static unsigned int <a href="ident?i=iptable_nat_ipv4_fn">iptable_nat_ipv4_fn</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L42" href="source/net/ipv4/netfilter/iptable_nat.c#L42">42</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L43" href="source/net/ipv4/netfilter/iptable_nat.c#L43">43</a>                                         const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L44" href="source/net/ipv4/netfilter/iptable_nat.c#L44">44</a> {
 <a name="L45" href="source/net/ipv4/netfilter/iptable_nat.c#L45">45</a>         return <a href="ident?i=nf_nat_ipv4_fn">nf_nat_ipv4_fn</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, <a href="ident?i=iptable_nat_do_chain">iptable_nat_do_chain</a>);
 <a name="L46" href="source/net/ipv4/netfilter/iptable_nat.c#L46">46</a> }
 <a name="L47" href="source/net/ipv4/netfilter/iptable_nat.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/netfilter/iptable_nat.c#L48">48</a> static unsigned int <a href="ident?i=iptable_nat_ipv4_in">iptable_nat_ipv4_in</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L49" href="source/net/ipv4/netfilter/iptable_nat.c#L49">49</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L50" href="source/net/ipv4/netfilter/iptable_nat.c#L50">50</a>                                         const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L51" href="source/net/ipv4/netfilter/iptable_nat.c#L51">51</a> {
 <a name="L52" href="source/net/ipv4/netfilter/iptable_nat.c#L52">52</a>         return <a href="ident?i=nf_nat_ipv4_in">nf_nat_ipv4_in</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, <a href="ident?i=iptable_nat_do_chain">iptable_nat_do_chain</a>);
 <a name="L53" href="source/net/ipv4/netfilter/iptable_nat.c#L53">53</a> }
 <a name="L54" href="source/net/ipv4/netfilter/iptable_nat.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/netfilter/iptable_nat.c#L55">55</a> static unsigned int <a href="ident?i=iptable_nat_ipv4_out">iptable_nat_ipv4_out</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L56" href="source/net/ipv4/netfilter/iptable_nat.c#L56">56</a>                                          struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L57" href="source/net/ipv4/netfilter/iptable_nat.c#L57">57</a>                                          const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L58" href="source/net/ipv4/netfilter/iptable_nat.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/netfilter/iptable_nat.c#L59">59</a>         return <a href="ident?i=nf_nat_ipv4_out">nf_nat_ipv4_out</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, <a href="ident?i=iptable_nat_do_chain">iptable_nat_do_chain</a>);
 <a name="L60" href="source/net/ipv4/netfilter/iptable_nat.c#L60">60</a> }
 <a name="L61" href="source/net/ipv4/netfilter/iptable_nat.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/iptable_nat.c#L62">62</a> static unsigned int <a href="ident?i=iptable_nat_ipv4_local_fn">iptable_nat_ipv4_local_fn</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
 <a name="L63" href="source/net/ipv4/netfilter/iptable_nat.c#L63">63</a>                                               struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L64" href="source/net/ipv4/netfilter/iptable_nat.c#L64">64</a>                                               const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L65" href="source/net/ipv4/netfilter/iptable_nat.c#L65">65</a> {
 <a name="L66" href="source/net/ipv4/netfilter/iptable_nat.c#L66">66</a>         return <a href="ident?i=nf_nat_ipv4_local_fn">nf_nat_ipv4_local_fn</a>(<a href="ident?i=ops">ops</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, <a href="ident?i=iptable_nat_do_chain">iptable_nat_do_chain</a>);
 <a name="L67" href="source/net/ipv4/netfilter/iptable_nat.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/netfilter/iptable_nat.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/netfilter/iptable_nat.c#L69">69</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> nf_nat_ipv4_ops[] <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L70" href="source/net/ipv4/netfilter/iptable_nat.c#L70">70</a>         <b><i>/* Before packet filtering, change destination */</i></b>
 <a name="L71" href="source/net/ipv4/netfilter/iptable_nat.c#L71">71</a>         {
 <a name="L72" href="source/net/ipv4/netfilter/iptable_nat.c#L72">72</a>                 .hook           = <a href="ident?i=iptable_nat_ipv4_in">iptable_nat_ipv4_in</a>,
 <a name="L73" href="source/net/ipv4/netfilter/iptable_nat.c#L73">73</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L74" href="source/net/ipv4/netfilter/iptable_nat.c#L74">74</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
 <a name="L75" href="source/net/ipv4/netfilter/iptable_nat.c#L75">75</a>                 .hooknum        = NF_INET_PRE_ROUTING,
 <a name="L76" href="source/net/ipv4/netfilter/iptable_nat.c#L76">76</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_NAT_DST,
 <a name="L77" href="source/net/ipv4/netfilter/iptable_nat.c#L77">77</a>         },
 <a name="L78" href="source/net/ipv4/netfilter/iptable_nat.c#L78">78</a>         <b><i>/* After packet filtering, change source */</i></b>
 <a name="L79" href="source/net/ipv4/netfilter/iptable_nat.c#L79">79</a>         {
 <a name="L80" href="source/net/ipv4/netfilter/iptable_nat.c#L80">80</a>                 .hook           = <a href="ident?i=iptable_nat_ipv4_out">iptable_nat_ipv4_out</a>,
 <a name="L81" href="source/net/ipv4/netfilter/iptable_nat.c#L81">81</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L82" href="source/net/ipv4/netfilter/iptable_nat.c#L82">82</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
 <a name="L83" href="source/net/ipv4/netfilter/iptable_nat.c#L83">83</a>                 .hooknum        = NF_INET_POST_ROUTING,
 <a name="L84" href="source/net/ipv4/netfilter/iptable_nat.c#L84">84</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_NAT_SRC,
 <a name="L85" href="source/net/ipv4/netfilter/iptable_nat.c#L85">85</a>         },
 <a name="L86" href="source/net/ipv4/netfilter/iptable_nat.c#L86">86</a>         <b><i>/* Before packet filtering, change destination */</i></b>
 <a name="L87" href="source/net/ipv4/netfilter/iptable_nat.c#L87">87</a>         {
 <a name="L88" href="source/net/ipv4/netfilter/iptable_nat.c#L88">88</a>                 .hook           = <a href="ident?i=iptable_nat_ipv4_local_fn">iptable_nat_ipv4_local_fn</a>,
 <a name="L89" href="source/net/ipv4/netfilter/iptable_nat.c#L89">89</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L90" href="source/net/ipv4/netfilter/iptable_nat.c#L90">90</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
 <a name="L91" href="source/net/ipv4/netfilter/iptable_nat.c#L91">91</a>                 .hooknum        = NF_INET_LOCAL_OUT,
 <a name="L92" href="source/net/ipv4/netfilter/iptable_nat.c#L92">92</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_NAT_DST,
 <a name="L93" href="source/net/ipv4/netfilter/iptable_nat.c#L93">93</a>         },
 <a name="L94" href="source/net/ipv4/netfilter/iptable_nat.c#L94">94</a>         <b><i>/* After packet filtering, change source */</i></b>
 <a name="L95" href="source/net/ipv4/netfilter/iptable_nat.c#L95">95</a>         {
 <a name="L96" href="source/net/ipv4/netfilter/iptable_nat.c#L96">96</a>                 .hook           = <a href="ident?i=iptable_nat_ipv4_fn">iptable_nat_ipv4_fn</a>,
 <a name="L97" href="source/net/ipv4/netfilter/iptable_nat.c#L97">97</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L98" href="source/net/ipv4/netfilter/iptable_nat.c#L98">98</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
 <a name="L99" href="source/net/ipv4/netfilter/iptable_nat.c#L99">99</a>                 .hooknum        = NF_INET_LOCAL_IN,
<a name="L100" href="source/net/ipv4/netfilter/iptable_nat.c#L100">100</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_NAT_SRC,
<a name="L101" href="source/net/ipv4/netfilter/iptable_nat.c#L101">101</a>         },
<a name="L102" href="source/net/ipv4/netfilter/iptable_nat.c#L102">102</a> };
<a name="L103" href="source/net/ipv4/netfilter/iptable_nat.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/netfilter/iptable_nat.c#L104">104</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=iptable_nat_net_init">iptable_nat_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L105" href="source/net/ipv4/netfilter/iptable_nat.c#L105">105</a> {
<a name="L106" href="source/net/ipv4/netfilter/iptable_nat.c#L106">106</a>         struct <a href="ident?i=ipt_replace">ipt_replace</a> *repl;
<a name="L107" href="source/net/ipv4/netfilter/iptable_nat.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/netfilter/iptable_nat.c#L108">108</a>         repl = <a href="ident?i=ipt_alloc_initial_table">ipt_alloc_initial_table</a>(&amp;<a href="ident?i=nf_nat_ipv4_table">nf_nat_ipv4_table</a>);
<a name="L109" href="source/net/ipv4/netfilter/iptable_nat.c#L109">109</a>         if (repl == <a href="ident?i=NULL">NULL</a>)
<a name="L110" href="source/net/ipv4/netfilter/iptable_nat.c#L110">110</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L111" href="source/net/ipv4/netfilter/iptable_nat.c#L111">111</a>         <a href="ident?i=net">net</a>-&gt;ipv4.nat_table = <a href="ident?i=ipt_register_table">ipt_register_table</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=nf_nat_ipv4_table">nf_nat_ipv4_table</a>, repl);
<a name="L112" href="source/net/ipv4/netfilter/iptable_nat.c#L112">112</a>         <a href="ident?i=kfree">kfree</a>(repl);
<a name="L113" href="source/net/ipv4/netfilter/iptable_nat.c#L113">113</a>         return <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(<a href="ident?i=net">net</a>-&gt;ipv4.nat_table);
<a name="L114" href="source/net/ipv4/netfilter/iptable_nat.c#L114">114</a> }
<a name="L115" href="source/net/ipv4/netfilter/iptable_nat.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/netfilter/iptable_nat.c#L116">116</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=iptable_nat_net_exit">iptable_nat_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L117" href="source/net/ipv4/netfilter/iptable_nat.c#L117">117</a> {
<a name="L118" href="source/net/ipv4/netfilter/iptable_nat.c#L118">118</a>         <a href="ident?i=ipt_unregister_table">ipt_unregister_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=net">net</a>-&gt;ipv4.nat_table);
<a name="L119" href="source/net/ipv4/netfilter/iptable_nat.c#L119">119</a> }
<a name="L120" href="source/net/ipv4/netfilter/iptable_nat.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/netfilter/iptable_nat.c#L121">121</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=iptable_nat_net_ops">iptable_nat_net_ops</a> = {
<a name="L122" href="source/net/ipv4/netfilter/iptable_nat.c#L122">122</a>         .<a href="ident?i=init">init</a>   = <a href="ident?i=iptable_nat_net_init">iptable_nat_net_init</a>,
<a name="L123" href="source/net/ipv4/netfilter/iptable_nat.c#L123">123</a>         .<a href="ident?i=exit">exit</a>   = <a href="ident?i=iptable_nat_net_exit">iptable_nat_net_exit</a>,
<a name="L124" href="source/net/ipv4/netfilter/iptable_nat.c#L124">124</a> };
<a name="L125" href="source/net/ipv4/netfilter/iptable_nat.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/netfilter/iptable_nat.c#L126">126</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=iptable_nat_init">iptable_nat_init</a>(void)
<a name="L127" href="source/net/ipv4/netfilter/iptable_nat.c#L127">127</a> {
<a name="L128" href="source/net/ipv4/netfilter/iptable_nat.c#L128">128</a>         int <a href="ident?i=err">err</a>;
<a name="L129" href="source/net/ipv4/netfilter/iptable_nat.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/netfilter/iptable_nat.c#L130">130</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=iptable_nat_net_ops">iptable_nat_net_ops</a>);
<a name="L131" href="source/net/ipv4/netfilter/iptable_nat.c#L131">131</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L132" href="source/net/ipv4/netfilter/iptable_nat.c#L132">132</a>                 goto err1;
<a name="L133" href="source/net/ipv4/netfilter/iptable_nat.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/netfilter/iptable_nat.c#L134">134</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nf_register_hooks">nf_register_hooks</a>(nf_nat_ipv4_ops, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(nf_nat_ipv4_ops));
<a name="L135" href="source/net/ipv4/netfilter/iptable_nat.c#L135">135</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L136" href="source/net/ipv4/netfilter/iptable_nat.c#L136">136</a>                 goto err2;
<a name="L137" href="source/net/ipv4/netfilter/iptable_nat.c#L137">137</a>         return 0;
<a name="L138" href="source/net/ipv4/netfilter/iptable_nat.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/netfilter/iptable_nat.c#L139">139</a> err2:
<a name="L140" href="source/net/ipv4/netfilter/iptable_nat.c#L140">140</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_nat_net_ops">iptable_nat_net_ops</a>);
<a name="L141" href="source/net/ipv4/netfilter/iptable_nat.c#L141">141</a> err1:
<a name="L142" href="source/net/ipv4/netfilter/iptable_nat.c#L142">142</a>         return <a href="ident?i=err">err</a>;
<a name="L143" href="source/net/ipv4/netfilter/iptable_nat.c#L143">143</a> }
<a name="L144" href="source/net/ipv4/netfilter/iptable_nat.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/netfilter/iptable_nat.c#L145">145</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=iptable_nat_exit">iptable_nat_exit</a>(void)
<a name="L146" href="source/net/ipv4/netfilter/iptable_nat.c#L146">146</a> {
<a name="L147" href="source/net/ipv4/netfilter/iptable_nat.c#L147">147</a>         <a href="ident?i=nf_unregister_hooks">nf_unregister_hooks</a>(nf_nat_ipv4_ops, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(nf_nat_ipv4_ops));
<a name="L148" href="source/net/ipv4/netfilter/iptable_nat.c#L148">148</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_nat_net_ops">iptable_nat_net_ops</a>);
<a name="L149" href="source/net/ipv4/netfilter/iptable_nat.c#L149">149</a> }
<a name="L150" href="source/net/ipv4/netfilter/iptable_nat.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/netfilter/iptable_nat.c#L151">151</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=iptable_nat_init">iptable_nat_init</a>);
<a name="L152" href="source/net/ipv4/netfilter/iptable_nat.c#L152">152</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=iptable_nat_exit">iptable_nat_exit</a>);
<a name="L153" href="source/net/ipv4/netfilter/iptable_nat.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/netfilter/iptable_nat.c#L154">154</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L155" href="source/net/ipv4/netfilter/iptable_nat.c#L155">155</a> </pre></div><p>
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
