<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_CLUSTERIP.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_CLUSTERIP.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c">ipt_CLUSTERIP.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L1">1</a> <b><i>/* Cluster IP hashmark target</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L2">2</a> <b><i> * (C) 2003-2004 by Harald Welte &lt;laforge@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L3">3</a> <b><i> * based on ideas of Fabio Olive Leite &lt;olive@unixforge.org&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L5">5</a> <b><i> * Development of this code funded by SuSE Linux AG, <a href="http://www.suse.com/">http://www.suse.com/</a></i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L7">7</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L8">8</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L9">9</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L12">12</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L13" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L14">14</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L15">15</a> #include &lt;linux/jhash.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L16">16</a> #include &lt;linux/bitops.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L17">17</a> #include &lt;linux/skbuff.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L18">18</a> #include &lt;linux/slab.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L19">19</a> #include &lt;linux/ip.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L20">20</a> #include &lt;linux/tcp.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L21">21</a> #include &lt;linux/udp.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L22">22</a> #include &lt;linux/icmp.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L23">23</a> #include &lt;linux/if_arp.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L24">24</a> #include &lt;linux/seq_file.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L25">25</a> #include &lt;linux/netfilter_arp.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L26">26</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L27" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L27">27</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L28">28</a> #include &lt;linux/netfilter_ipv4/ipt_CLUSTERIP.h&gt;
 <a name="L29" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L29">29</a> #include &lt;net/netfilter/nf_conntrack.h&gt;
 <a name="L30" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L30">30</a> #include &lt;net/net_namespace.h&gt;
 <a name="L31" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L31">31</a> #include &lt;net/netns/generic.h&gt;
 <a name="L32" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L32">32</a> #include &lt;net/checksum.h&gt;
 <a name="L33" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L33">33</a> #include &lt;net/ip.h&gt;
 <a name="L34" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L35">35</a> #define <a href="ident?i=CLUSTERIP_VERSION">CLUSTERIP_VERSION</a> <i>"0.8"</i>
 <a name="L36" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L37">37</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L38" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L38">38</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Harald Welte &lt;laforge@netfilter.org&gt;"</i>);
 <a name="L39" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L39">39</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Xtables: CLUSTERIP target"</i>);
 <a name="L40" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L41">41</a> struct <a href="ident?i=clusterip_config">clusterip_config</a> {
 <a name="L42" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L42">42</a>         struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=list">list</a>;                  <b><i>/* list of all configs */</i></b>
 <a name="L43" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L43">43</a>         <a href="ident?i=atomic_t">atomic_t</a> refcount;                      <b><i>/* reference count */</i></b>
 <a name="L44" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L44">44</a>         <a href="ident?i=atomic_t">atomic_t</a> <a href="ident?i=entries">entries</a>;                       <b><i>/* number of entries/rules</i></b>
 <a name="L45" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L45">45</a> <b><i>                                                 * referencing us */</i></b>
 <a name="L46" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L47">47</a>         <a href="ident?i=__be32">__be32</a> clusterip;                       <b><i>/* the IP address */</i></b>
 <a name="L48" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L48">48</a>         <a href="ident?i=u_int8_t">u_int8_t</a> clustermac[<a href="ident?i=ETH_ALEN">ETH_ALEN</a>];          <b><i>/* the MAC address */</i></b>
 <a name="L49" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L49">49</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;                 <b><i>/* device */</i></b>
 <a name="L50" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L50">50</a>         <a href="ident?i=u_int16_t">u_int16_t</a> num_total_nodes;              <b><i>/* total number of nodes */</i></b>
 <a name="L51" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L51">51</a>         unsigned long local_nodes;              <b><i>/* node number array */</i></b>
 <a name="L52" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L53">53</a> #ifdef CONFIG_PROC_FS
 <a name="L54" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L54">54</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *pde;             <b><i>/* proc dir entry */</i></b>
 <a name="L55" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L55">55</a> #endif
 <a name="L56" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L56">56</a>         enum <a href="ident?i=clusterip_hashmode">clusterip_hashmode</a> <a href="ident?i=hash_mode">hash_mode</a>;      <b><i>/* which hashing mode */</i></b>
 <a name="L57" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L57">57</a>         <a href="ident?i=u_int32_t">u_int32_t</a> hash_initval;                 <b><i>/* hash initialization */</i></b>
 <a name="L58" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L58">58</a>         struct <a href="ident?i=rcu_head">rcu_head</a> rcu;
 <a name="L59" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L59">59</a> };
 <a name="L60" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L61">61</a> #ifdef CONFIG_PROC_FS
 <a name="L62" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L62">62</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=clusterip_proc_fops">clusterip_proc_fops</a>;
 <a name="L63" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L63">63</a> #endif
 <a name="L64" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L65">65</a> static int clusterip_net_id <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L66" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L67">67</a> struct <a href="ident?i=clusterip_net">clusterip_net</a> {
 <a name="L68" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L68">68</a>         struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=configs">configs</a>;
 <a name="L69" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L69">69</a>         <b><i>/* lock protects the configs list */</i></b>
 <a name="L70" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L70">70</a>         <a href="ident?i=spinlock_t">spinlock_t</a> <a href="ident?i=lock">lock</a>;
 <a name="L71" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L72">72</a> #ifdef CONFIG_PROC_FS
 <a name="L73" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L73">73</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *procdir;
 <a name="L74" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L74">74</a> #endif
 <a name="L75" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L75">75</a> };
 <a name="L76" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L77">77</a> static inline void
 <a name="L78" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L78">78</a> <a href="ident?i=clusterip_config_get">clusterip_config_get</a>(struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>)
 <a name="L79" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L79">79</a> {
 <a name="L80" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L80">80</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=c">c</a>-&gt;refcount);
 <a name="L81" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L84">84</a> static void <a href="ident?i=clusterip_config_rcu_free">clusterip_config_rcu_free</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
 <a name="L85" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L86">86</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=clusterip_config">clusterip_config</a>, rcu));
 <a name="L87" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L87">87</a> }
 <a name="L88" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L89">89</a> static inline void
 <a name="L90" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L90">90</a> <a href="ident?i=clusterip_config_put">clusterip_config_put</a>(struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>)
 <a name="L91" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L91">91</a> {
 <a name="L92" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L92">92</a>         if (<a href="ident?i=atomic_dec_and_test">atomic_dec_and_test</a>(&amp;<a href="ident?i=c">c</a>-&gt;refcount))
 <a name="L93" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L93">93</a>                 <a href="ident?i=call_rcu_bh">call_rcu_bh</a>(&amp;<a href="ident?i=c">c</a>-&gt;rcu, <a href="ident?i=clusterip_config_rcu_free">clusterip_config_rcu_free</a>);
 <a name="L94" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L94">94</a> }
 <a name="L95" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L96">96</a> <b><i>/* decrease the count of entries using/referencing this config.  If last</i></b>
 <a name="L97" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L97">97</a> <b><i> * entry(rule) is removed, remove the config from lists, but don't free it</i></b>
 <a name="L98" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L98">98</a> <b><i> * yet, since proc-files could still be holding references */</i></b>
 <a name="L99" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L99">99</a> static inline void
<a name="L100" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L100">100</a> <a href="ident?i=clusterip_config_entry_put">clusterip_config_entry_put</a>(struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>)
<a name="L101" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L101">101</a> {
<a name="L102" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L102">102</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=c">c</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L103" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L103">103</a>         struct <a href="ident?i=clusterip_net">clusterip_net</a> *cn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, clusterip_net_id);
<a name="L104" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L105">105</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L106" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L106">106</a>         if (<a href="ident?i=atomic_dec_and_lock">atomic_dec_and_lock</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=entries">entries</a>, &amp;cn-&gt;<a href="ident?i=lock">lock</a>)) {
<a name="L107" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L107">107</a>                 <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L108" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L108">108</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cn-&gt;<a href="ident?i=lock">lock</a>);
<a name="L109" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L109">109</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L110" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L111">111</a>                 <a href="ident?i=dev_mc_del">dev_mc_del</a>(<a href="ident?i=c">c</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=c">c</a>-&gt;clustermac);
<a name="L112" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L112">112</a>                 <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=c">c</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L113" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L114">114</a>                 <b><i>/* In case anyone still accesses the file, the open/close</i></b>
<a name="L115" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L115">115</a> <b><i>                 * functions are also incrementing the refcount on their own,</i></b>
<a name="L116" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L116">116</a> <b><i>                 * so it's safe to remove the entry even if it's in use. */</i></b>
<a name="L117" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L117">117</a> #ifdef CONFIG_PROC_FS
<a name="L118" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L118">118</a>                 <a href="ident?i=proc_remove">proc_remove</a>(<a href="ident?i=c">c</a>-&gt;pde);
<a name="L119" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L119">119</a> #endif
<a name="L120" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L120">120</a>                 return;
<a name="L121" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L121">121</a>         }
<a name="L122" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L122">122</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L123" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L123">123</a> }
<a name="L124" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L125">125</a> static struct <a href="ident?i=clusterip_config">clusterip_config</a> *
<a name="L126" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L126">126</a> <a href="ident?i=__clusterip_config_find">__clusterip_config_find</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> clusterip)
<a name="L127" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L127">127</a> {
<a name="L128" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L128">128</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>;
<a name="L129" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L129">129</a>         struct <a href="ident?i=clusterip_net">clusterip_net</a> *cn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, clusterip_net_id);
<a name="L130" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L131">131</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=c">c</a>, &amp;cn-&gt;<a href="ident?i=configs">configs</a>, <a href="ident?i=list">list</a>) {
<a name="L132" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L132">132</a>                 if (<a href="ident?i=c">c</a>-&gt;clusterip == clusterip)
<a name="L133" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L133">133</a>                         return <a href="ident?i=c">c</a>;
<a name="L134" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L134">134</a>         }
<a name="L135" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L136">136</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L137" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L137">137</a> }
<a name="L138" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L139">139</a> static inline struct <a href="ident?i=clusterip_config">clusterip_config</a> *
<a name="L140" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L140">140</a> <a href="ident?i=clusterip_config_find_get">clusterip_config_find_get</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> clusterip, int <a href="ident?i=entry">entry</a>)
<a name="L141" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L141">141</a> {
<a name="L142" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L142">142</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>;
<a name="L143" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L144">144</a>         <a href="ident?i=rcu_read_lock_bh">rcu_read_lock_bh</a>();
<a name="L145" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L145">145</a>         <a href="ident?i=c">c</a> = <a href="ident?i=__clusterip_config_find">__clusterip_config_find</a>(<a href="ident?i=net">net</a>, clusterip);
<a name="L146" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L146">146</a>         if (<a href="ident?i=c">c</a>) {
<a name="L147" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L147">147</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;<a href="ident?i=c">c</a>-&gt;refcount)))
<a name="L148" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L148">148</a>                         <a href="ident?i=c">c</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L149" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L149">149</a>                 else if (<a href="ident?i=entry">entry</a>)
<a name="L150" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L150">150</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=entries">entries</a>);
<a name="L151" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L151">151</a>         }
<a name="L152" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L152">152</a>         <a href="ident?i=rcu_read_unlock_bh">rcu_read_unlock_bh</a>();
<a name="L153" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L154">154</a>         return <a href="ident?i=c">c</a>;
<a name="L155" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L155">155</a> }
<a name="L156" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L157">157</a> static void
<a name="L158" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L158">158</a> <a href="ident?i=clusterip_config_init_nodelist">clusterip_config_init_nodelist</a>(struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>,
<a name="L159" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L159">159</a>                                const struct <a href="ident?i=ipt_clusterip_tgt_info">ipt_clusterip_tgt_info</a> *<a href="ident?i=i">i</a>)
<a name="L160" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L160">160</a> {
<a name="L161" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L161">161</a>         int <a href="ident?i=n">n</a>;
<a name="L162" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L163">163</a>         for (<a href="ident?i=n">n</a> = 0; <a href="ident?i=n">n</a> &lt; <a href="ident?i=i">i</a>-&gt;num_local_nodes; <a href="ident?i=n">n</a>++)
<a name="L164" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L164">164</a>                 <a href="ident?i=set_bit">set_bit</a>(<a href="ident?i=i">i</a>-&gt;local_nodes[<a href="ident?i=n">n</a>] - 1, &amp;<a href="ident?i=c">c</a>-&gt;local_nodes);
<a name="L165" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L165">165</a> }
<a name="L166" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L167">167</a> static struct <a href="ident?i=clusterip_config">clusterip_config</a> *
<a name="L168" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L168">168</a> <a href="ident?i=clusterip_config_init">clusterip_config_init</a>(const struct <a href="ident?i=ipt_clusterip_tgt_info">ipt_clusterip_tgt_info</a> *<a href="ident?i=i">i</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a>,
<a name="L169" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L169">169</a>                         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L170" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L170">170</a> {
<a name="L171" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L171">171</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>;
<a name="L172" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L172">172</a>         struct <a href="ident?i=clusterip_net">clusterip_net</a> *cn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), clusterip_net_id);
<a name="L173" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L174">174</a>         <a href="ident?i=c">c</a> = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*<a href="ident?i=c">c</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L175" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L175">175</a>         if (!<a href="ident?i=c">c</a>)
<a name="L176" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L176">176</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L177" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L178">178</a>         <a href="ident?i=c">c</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L179" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L179">179</a>         <a href="ident?i=c">c</a>-&gt;clusterip = <a href="ident?i=ip">ip</a>;
<a name="L180" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L180">180</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=c">c</a>-&gt;clustermac, &amp;<a href="ident?i=i">i</a>-&gt;clustermac, <a href="ident?i=ETH_ALEN">ETH_ALEN</a>);
<a name="L181" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L181">181</a>         <a href="ident?i=c">c</a>-&gt;num_total_nodes = <a href="ident?i=i">i</a>-&gt;num_total_nodes;
<a name="L182" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L182">182</a>         <a href="ident?i=clusterip_config_init_nodelist">clusterip_config_init_nodelist</a>(<a href="ident?i=c">c</a>, <a href="ident?i=i">i</a>);
<a name="L183" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L183">183</a>         <a href="ident?i=c">c</a>-&gt;<a href="ident?i=hash_mode">hash_mode</a> = <a href="ident?i=i">i</a>-&gt;<a href="ident?i=hash_mode">hash_mode</a>;
<a name="L184" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L184">184</a>         <a href="ident?i=c">c</a>-&gt;hash_initval = <a href="ident?i=i">i</a>-&gt;hash_initval;
<a name="L185" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L185">185</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=c">c</a>-&gt;refcount, 1);
<a name="L186" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L186">186</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=entries">entries</a>, 1);
<a name="L187" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L188">188</a> #ifdef CONFIG_PROC_FS
<a name="L189" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L189">189</a>         {
<a name="L190" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L190">190</a>                 char <a href="ident?i=buffer">buffer</a>[16];
<a name="L191" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L192">192</a>                 <b><i>/* create proc dir entry */</i></b>
<a name="L193" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L193">193</a>                 <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=buffer">buffer</a>, <i>"%pI4"</i>, &amp;<a href="ident?i=ip">ip</a>);
<a name="L194" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L194">194</a>                 <a href="ident?i=c">c</a>-&gt;pde = <a href="ident?i=proc_create_data">proc_create_data</a>(<a href="ident?i=buffer">buffer</a>, <a href="ident?i=S_IWUSR">S_IWUSR</a>|<a href="ident?i=S_IRUSR">S_IRUSR</a>,
<a name="L195" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L195">195</a>                                           cn-&gt;procdir,
<a name="L196" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L196">196</a>                                           &amp;<a href="ident?i=clusterip_proc_fops">clusterip_proc_fops</a>, <a href="ident?i=c">c</a>);
<a name="L197" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L197">197</a>                 if (!<a href="ident?i=c">c</a>-&gt;pde) {
<a name="L198" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L198">198</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=c">c</a>);
<a name="L199" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L199">199</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L200" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L200">200</a>                 }
<a name="L201" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L201">201</a>         }
<a name="L202" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L202">202</a> #endif
<a name="L203" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L204">204</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;cn-&gt;<a href="ident?i=lock">lock</a>);
<a name="L205" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L205">205</a>         <a href="ident?i=list_add_rcu">list_add_rcu</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>, &amp;cn-&gt;<a href="ident?i=configs">configs</a>);
<a name="L206" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L206">206</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;cn-&gt;<a href="ident?i=lock">lock</a>);
<a name="L207" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L208">208</a>         return <a href="ident?i=c">c</a>;
<a name="L209" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L209">209</a> }
<a name="L210" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L211">211</a> #ifdef CONFIG_PROC_FS
<a name="L212" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L212">212</a> static int
<a name="L213" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L213">213</a> <a href="ident?i=clusterip_add_node">clusterip_add_node</a>(struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>, <a href="ident?i=u_int16_t">u_int16_t</a> nodenum)
<a name="L214" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L214">214</a> {
<a name="L215" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L216">216</a>         if (nodenum == 0 ||
<a name="L217" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L217">217</a>             nodenum &gt; <a href="ident?i=c">c</a>-&gt;num_total_nodes)
<a name="L218" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L218">218</a>                 return 1;
<a name="L219" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L220">220</a>         <b><i>/* check if we already have this number in our bitfield */</i></b>
<a name="L221" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L221">221</a>         if (<a href="ident?i=test_and_set_bit">test_and_set_bit</a>(nodenum - 1, &amp;<a href="ident?i=c">c</a>-&gt;local_nodes))
<a name="L222" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L222">222</a>                 return 1;
<a name="L223" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L224">224</a>         return 0;
<a name="L225" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L225">225</a> }
<a name="L226" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L227">227</a> static <a href="ident?i=bool">bool</a>
<a name="L228" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L228">228</a> <a href="ident?i=clusterip_del_node">clusterip_del_node</a>(struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>, <a href="ident?i=u_int16_t">u_int16_t</a> nodenum)
<a name="L229" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L229">229</a> {
<a name="L230" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L230">230</a>         if (nodenum == 0 ||
<a name="L231" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L231">231</a>             nodenum &gt; <a href="ident?i=c">c</a>-&gt;num_total_nodes)
<a name="L232" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L232">232</a>                 return <a href="ident?i=true">true</a>;
<a name="L233" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L234">234</a>         if (<a href="ident?i=test_and_clear_bit">test_and_clear_bit</a>(nodenum - 1, &amp;<a href="ident?i=c">c</a>-&gt;local_nodes))
<a name="L235" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L235">235</a>                 return <a href="ident?i=false">false</a>;
<a name="L236" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L237">237</a>         return <a href="ident?i=true">true</a>;
<a name="L238" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L238">238</a> }
<a name="L239" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L239">239</a> #endif
<a name="L240" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L241">241</a> static inline <a href="ident?i=u_int32_t">u_int32_t</a>
<a name="L242" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L242">242</a> <a href="ident?i=clusterip_hashfn">clusterip_hashfn</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L243" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L243">243</a>                  const struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=config">config</a>)
<a name="L244" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L244">244</a> {
<a name="L245" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L245">245</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L246" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L246">246</a>         unsigned long hashval;
<a name="L247" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L247">247</a>         <a href="ident?i=u_int16_t">u_int16_t</a> sport = 0, dport = 0;
<a name="L248" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L248">248</a>         int poff;
<a name="L249" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L250">250</a>         poff = <a href="ident?i=proto_ports_offset">proto_ports_offset</a>(iph-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L251" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L251">251</a>         if (poff &gt;= 0) {
<a name="L252" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L252">252</a>                 const <a href="ident?i=u_int16_t">u_int16_t</a> *<a href="ident?i=ports">ports</a>;
<a name="L253" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L253">253</a>                 <a href="ident?i=u16">u16</a> _ports[2];
<a name="L254" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L255">255</a>                 <a href="ident?i=ports">ports</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, iph-&gt;ihl * 4 + poff, 4, _ports);
<a name="L256" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L256">256</a>                 if (<a href="ident?i=ports">ports</a>) {
<a name="L257" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L257">257</a>                         sport = <a href="ident?i=ports">ports</a>[0];
<a name="L258" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L258">258</a>                         dport = <a href="ident?i=ports">ports</a>[1];
<a name="L259" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L259">259</a>                 }
<a name="L260" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L260">260</a>         } else {
<a name="L261" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L261">261</a>                 <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"unknown protocol %u\n"</i>, iph-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L262" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L262">262</a>         }
<a name="L263" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L264">264</a>         switch (<a href="ident?i=config">config</a>-&gt;<a href="ident?i=hash_mode">hash_mode</a>) {
<a name="L265" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L265">265</a>         case CLUSTERIP_HASHMODE_SIP:
<a name="L266" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L266">266</a>                 hashval = <a href="ident?i=jhash_1word">jhash_1word</a>(<a href="ident?i=ntohl">ntohl</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>),
<a name="L267" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L267">267</a>                                       <a href="ident?i=config">config</a>-&gt;hash_initval);
<a name="L268" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L268">268</a>                 break;
<a name="L269" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L269">269</a>         case CLUSTERIP_HASHMODE_SIP_SPT:
<a name="L270" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L270">270</a>                 hashval = <a href="ident?i=jhash_2words">jhash_2words</a>(<a href="ident?i=ntohl">ntohl</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>), sport,
<a name="L271" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L271">271</a>                                        <a href="ident?i=config">config</a>-&gt;hash_initval);
<a name="L272" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L272">272</a>                 break;
<a name="L273" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L273">273</a>         case CLUSTERIP_HASHMODE_SIP_SPT_DPT:
<a name="L274" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L274">274</a>                 hashval = <a href="ident?i=jhash_3words">jhash_3words</a>(<a href="ident?i=ntohl">ntohl</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>), sport, dport,
<a name="L275" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L275">275</a>                                        <a href="ident?i=config">config</a>-&gt;hash_initval);
<a name="L276" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L276">276</a>                 break;
<a name="L277" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L277">277</a>         default:
<a name="L278" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L278">278</a>                 <b><i>/* to make gcc happy */</i></b>
<a name="L279" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L279">279</a>                 hashval = 0;
<a name="L280" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L280">280</a>                 <b><i>/* This cannot happen, unless the check function wasn't called</i></b>
<a name="L281" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L281">281</a> <b><i>                 * at rule load time */</i></b>
<a name="L282" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L282">282</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"unknown mode %u\n"</i>, <a href="ident?i=config">config</a>-&gt;<a href="ident?i=hash_mode">hash_mode</a>);
<a name="L283" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L283">283</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L284" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L284">284</a>                 break;
<a name="L285" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L285">285</a>         }
<a name="L286" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L287">287</a>         <b><i>/* node numbers are 1..n, not 0..n */</i></b>
<a name="L288" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L288">288</a>         return <a href="ident?i=reciprocal_scale">reciprocal_scale</a>(hashval, <a href="ident?i=config">config</a>-&gt;num_total_nodes) + 1;
<a name="L289" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L289">289</a> }
<a name="L290" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L291">291</a> static inline int
<a name="L292" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L292">292</a> <a href="ident?i=clusterip_responsible">clusterip_responsible</a>(const struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=config">config</a>, <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=hash">hash</a>)
<a name="L293" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L293">293</a> {
<a name="L294" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L294">294</a>         return <a href="ident?i=test_bit">test_bit</a>(<a href="ident?i=hash">hash</a> - 1, &amp;<a href="ident?i=config">config</a>-&gt;local_nodes);
<a name="L295" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L295">295</a> }
<a name="L296" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L297">297</a> <b><i>/***********************************************************************</i></b>
<a name="L298" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L298">298</a> <b><i> * IPTABLES TARGET</i></b>
<a name="L299" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L299">299</a> <b><i> ***********************************************************************/</i></b>
<a name="L300" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L301">301</a> static unsigned int
<a name="L302" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L302">302</a> <a href="ident?i=clusterip_tg">clusterip_tg</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
<a name="L303" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L303">303</a> {
<a name="L304" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L304">304</a>         const struct <a href="ident?i=ipt_clusterip_tgt_info">ipt_clusterip_tgt_info</a> *cipinfo = <a href="ident?i=par">par</a>-&gt;targinfo;
<a name="L305" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L305">305</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L306" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L306">306</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L307" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L307">307</a>         <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=hash">hash</a>;
<a name="L308" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L309">309</a>         <b><i>/* don't need to clusterip_config_get() here, since refcount</i></b>
<a name="L310" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L310">310</a> <b><i>         * is only decremented by destroy() - and ip_tables guarantees</i></b>
<a name="L311" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L311">311</a> <b><i>         * that the -&gt;target() function isn't called after -&gt;destroy() */</i></b>
<a name="L312" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L313">313</a>         ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
<a name="L314" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L314">314</a>         if (ct == <a href="ident?i=NULL">NULL</a>)
<a name="L315" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L315">315</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L316" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L317">317</a>         <b><i>/* special case: ICMP error handling. conntrack distinguishes between</i></b>
<a name="L318" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L318">318</a> <b><i>         * error messages (RELATED) and information requests (see below) */</i></b>
<a name="L319" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L319">319</a>         if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a> &amp;&amp;
<a name="L320" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L320">320</a>             (ctinfo == IP_CT_RELATED ||
<a name="L321" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L321">321</a>              ctinfo == IP_CT_RELATED_REPLY))
<a name="L322" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L322">322</a>                 return <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>;
<a name="L323" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L324">324</a>         <b><i>/* ip_conntrack_icmp guarantees us that we only have ICMP_ECHO,</i></b>
<a name="L325" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L325">325</a> <b><i>         * TIMESTAMP, INFO_REQUEST or ADDRESS type icmp packets from here</i></b>
<a name="L326" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L326">326</a> <b><i>         * on, which all have an ID field [relevant for hashing]. */</i></b>
<a name="L327" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L328">328</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=clusterip_hashfn">clusterip_hashfn</a>(<a href="ident?i=skb">skb</a>, cipinfo-&gt;<a href="ident?i=config">config</a>);
<a name="L329" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L330">330</a>         switch (ctinfo) {
<a name="L331" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L331">331</a>         case IP_CT_NEW:
<a name="L332" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L332">332</a>                 ct-&gt;<a href="ident?i=mark">mark</a> = <a href="ident?i=hash">hash</a>;
<a name="L333" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L333">333</a>                 break;
<a name="L334" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L334">334</a>         case IP_CT_RELATED:
<a name="L335" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L335">335</a>         case IP_CT_RELATED_REPLY:
<a name="L336" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L336">336</a>                 <b><i>/* FIXME: we don't handle expectations at the moment.</i></b>
<a name="L337" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L337">337</a> <b><i>                 * They can arrive on a different node than</i></b>
<a name="L338" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L338">338</a> <b><i>                 * the master connection (e.g. FTP passive mode) */</i></b>
<a name="L339" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L339">339</a>         case IP_CT_ESTABLISHED:
<a name="L340" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L340">340</a>         case IP_CT_ESTABLISHED_REPLY:
<a name="L341" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L341">341</a>                 break;
<a name="L342" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L342">342</a>         default:                        <b><i>/* Prevent gcc warnings */</i></b>
<a name="L343" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L343">343</a>                 break;
<a name="L344" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L344">344</a>         }
<a name="L345" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L345">345</a> 
<a name="L346" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L346">346</a> #ifdef <a href="ident?i=DEBUG">DEBUG</a>
<a name="L347" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L347">347</a>         <a href="ident?i=nf_ct_dump_tuple_ip">nf_ct_dump_tuple_ip</a>(&amp;ct-&gt;tuplehash[IP_CT_DIR_ORIGINAL].tuple);
<a name="L348" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L348">348</a> #endif
<a name="L349" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L349">349</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"hash=%u ct_hash=%u "</i>, <a href="ident?i=hash">hash</a>, ct-&gt;<a href="ident?i=mark">mark</a>);
<a name="L350" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L350">350</a>         if (!<a href="ident?i=clusterip_responsible">clusterip_responsible</a>(cipinfo-&gt;<a href="ident?i=config">config</a>, <a href="ident?i=hash">hash</a>)) {
<a name="L351" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L351">351</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"not responsible\n"</i>);
<a name="L352" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L352">352</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L353" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L353">353</a>         }
<a name="L354" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L354">354</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"responsible\n"</i>);
<a name="L355" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L356">356</a>         <b><i>/* despite being received via linklayer multicast, this is</i></b>
<a name="L357" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L357">357</a> <b><i>         * actually a unicast IP packet. TCP doesn't like PACKET_MULTICAST */</i></b>
<a name="L358" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L358">358</a>         <a href="ident?i=skb">skb</a>-&gt;pkt_type = <a href="ident?i=PACKET_HOST">PACKET_HOST</a>;
<a name="L359" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L360">360</a>         return <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>;
<a name="L361" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L361">361</a> }
<a name="L362" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L362">362</a> 
<a name="L363" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L363">363</a> static int <a href="ident?i=clusterip_tg_check">clusterip_tg_check</a>(const struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> *<a href="ident?i=par">par</a>)
<a name="L364" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L364">364</a> {
<a name="L365" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L365">365</a>         struct <a href="ident?i=ipt_clusterip_tgt_info">ipt_clusterip_tgt_info</a> *cipinfo = <a href="ident?i=par">par</a>-&gt;targinfo;
<a name="L366" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L366">366</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a> = <a href="ident?i=par">par</a>-&gt;entryinfo;
<a name="L367" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L367">367</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=config">config</a>;
<a name="L368" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L368">368</a>         int <a href="ident?i=ret">ret</a>;
<a name="L369" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L369">369</a> 
<a name="L370" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L370">370</a>         if (cipinfo-&gt;<a href="ident?i=hash_mode">hash_mode</a> != CLUSTERIP_HASHMODE_SIP &amp;&amp;
<a name="L371" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L371">371</a>             cipinfo-&gt;<a href="ident?i=hash_mode">hash_mode</a> != CLUSTERIP_HASHMODE_SIP_SPT &amp;&amp;
<a name="L372" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L372">372</a>             cipinfo-&gt;<a href="ident?i=hash_mode">hash_mode</a> != CLUSTERIP_HASHMODE_SIP_SPT_DPT) {
<a name="L373" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L373">373</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"unknown mode %u\n"</i>, cipinfo-&gt;<a href="ident?i=hash_mode">hash_mode</a>);
<a name="L374" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L374">374</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L375" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L376">376</a>         }
<a name="L377" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L377">377</a>         if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.dmsk.s_addr != <a href="ident?i=htonl">htonl</a>(0xffffffff) ||
<a name="L378" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L378">378</a>             <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=dst">dst</a>.s_addr == 0) {
<a name="L379" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L379">379</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"Please specify destination IP\n"</i>);
<a name="L380" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L380">380</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L381" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L381">381</a>         }
<a name="L382" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L383">383</a>         <b><i>/* FIXME: further sanity checks */</i></b>
<a name="L384" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L385">385</a>         <a href="ident?i=config">config</a> = <a href="ident?i=clusterip_config_find_get">clusterip_config_find_get</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=dst">dst</a>.s_addr, 1);
<a name="L386" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L386">386</a>         if (!<a href="ident?i=config">config</a>) {
<a name="L387" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L387">387</a>                 if (!(cipinfo-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=CLUSTERIP_FLAG_NEW">CLUSTERIP_FLAG_NEW</a>)) {
<a name="L388" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L388">388</a>                         <a href="ident?i=pr_info">pr_info</a>(<i>"no config found for %pI4, need 'new'\n"</i>,
<a name="L389" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L389">389</a>                                 &amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=dst">dst</a>.s_addr);
<a name="L390" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L390">390</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L391" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L391">391</a>                 } else {
<a name="L392" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L392">392</a>                         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L393" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L394">394</a>                         if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.iniface[0] == <i>'\0'</i>) {
<a name="L395" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L395">395</a>                                 <a href="ident?i=pr_info">pr_info</a>(<i>"Please specify an interface name\n"</i>);
<a name="L396" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L396">396</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L397" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L397">397</a>                         }
<a name="L398" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L399">399</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_name">dev_get_by_name</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.iniface);
<a name="L400" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L400">400</a>                         if (!<a href="ident?i=dev">dev</a>) {
<a name="L401" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L401">401</a>                                 <a href="ident?i=pr_info">pr_info</a>(<i>"no such interface %s\n"</i>,
<a name="L402" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L402">402</a>                                         <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.iniface);
<a name="L403" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L403">403</a>                                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L404" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L404">404</a>                         }
<a name="L405" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L405">405</a> 
<a name="L406" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L406">406</a>                         <a href="ident?i=config">config</a> = <a href="ident?i=clusterip_config_init">clusterip_config_init</a>(cipinfo,
<a name="L407" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L407">407</a>                                                         <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=dst">dst</a>.s_addr, <a href="ident?i=dev">dev</a>);
<a name="L408" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L408">408</a>                         if (!<a href="ident?i=config">config</a>) {
<a name="L409" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L409">409</a>                                 <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L410" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L410">410</a>                                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L411" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L411">411</a>                         }
<a name="L412" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L412">412</a>                         <a href="ident?i=dev_mc_add">dev_mc_add</a>(<a href="ident?i=config">config</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=config">config</a>-&gt;clustermac);
<a name="L413" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L413">413</a>                 }
<a name="L414" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L414">414</a>         }
<a name="L415" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L415">415</a>         cipinfo-&gt;<a href="ident?i=config">config</a> = <a href="ident?i=config">config</a>;
<a name="L416" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L417">417</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_ct_l3proto_try_module_get">nf_ct_l3proto_try_module_get</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=family">family</a>);
<a name="L418" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L418">418</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L419" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L419">419</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"cannot load conntrack support for proto=%u\n"</i>,
<a name="L420" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L420">420</a>                         <a href="ident?i=par">par</a>-&gt;<a href="ident?i=family">family</a>);
<a name="L421" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L422">422</a>         if (!<a href="ident?i=par">par</a>-&gt;<a href="ident?i=net">net</a>-&gt;<a href="ident?i=xt">xt</a>.clusterip_deprecated_warning) {
<a name="L423" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L423">423</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"ipt_CLUSTERIP is deprecated and it will removed soon, "</i>
<a name="L424" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L424">424</a>                         <i>"use xt_cluster instead\n"</i>);
<a name="L425" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L425">425</a>                 <a href="ident?i=par">par</a>-&gt;<a href="ident?i=net">net</a>-&gt;<a href="ident?i=xt">xt</a>.clusterip_deprecated_warning = <a href="ident?i=true">true</a>;
<a name="L426" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L426">426</a>         }
<a name="L427" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L428">428</a>         return <a href="ident?i=ret">ret</a>;
<a name="L429" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L429">429</a> }
<a name="L430" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L431">431</a> <b><i>/* drop reference count of cluster config when rule is deleted */</i></b>
<a name="L432" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L432">432</a> static void <a href="ident?i=clusterip_tg_destroy">clusterip_tg_destroy</a>(const struct <a href="ident?i=xt_tgdtor_param">xt_tgdtor_param</a> *<a href="ident?i=par">par</a>)
<a name="L433" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L433">433</a> {
<a name="L434" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L434">434</a>         const struct <a href="ident?i=ipt_clusterip_tgt_info">ipt_clusterip_tgt_info</a> *cipinfo = <a href="ident?i=par">par</a>-&gt;targinfo;
<a name="L435" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L436">436</a>         <b><i>/* if no more entries are referencing the config, remove it</i></b>
<a name="L437" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L437">437</a> <b><i>         * from the list and destroy the proc entry */</i></b>
<a name="L438" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L438">438</a>         <a href="ident?i=clusterip_config_entry_put">clusterip_config_entry_put</a>(cipinfo-&gt;<a href="ident?i=config">config</a>);
<a name="L439" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L439">439</a> 
<a name="L440" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L440">440</a>         <a href="ident?i=clusterip_config_put">clusterip_config_put</a>(cipinfo-&gt;<a href="ident?i=config">config</a>);
<a name="L441" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L442">442</a>         <a href="ident?i=nf_ct_l3proto_module_put">nf_ct_l3proto_module_put</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=family">family</a>);
<a name="L443" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L443">443</a> }
<a name="L444" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L445">445</a> #ifdef CONFIG_COMPAT
<a name="L446" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L446">446</a> struct <a href="ident?i=compat_ipt_clusterip_tgt_info">compat_ipt_clusterip_tgt_info</a>
<a name="L447" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L447">447</a> {
<a name="L448" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L448">448</a>         <a href="ident?i=u_int32_t">u_int32_t</a>       <a href="ident?i=flags">flags</a>;
<a name="L449" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L449">449</a>         <a href="ident?i=u_int8_t">u_int8_t</a>        clustermac[6];
<a name="L450" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L450">450</a>         <a href="ident?i=u_int16_t">u_int16_t</a>       num_total_nodes;
<a name="L451" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L451">451</a>         <a href="ident?i=u_int16_t">u_int16_t</a>       num_local_nodes;
<a name="L452" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L452">452</a>         <a href="ident?i=u_int16_t">u_int16_t</a>       local_nodes[<a href="ident?i=CLUSTERIP_MAX_NODES">CLUSTERIP_MAX_NODES</a>];
<a name="L453" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L453">453</a>         <a href="ident?i=u_int32_t">u_int32_t</a>       <a href="ident?i=hash_mode">hash_mode</a>;
<a name="L454" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L454">454</a>         <a href="ident?i=u_int32_t">u_int32_t</a>       hash_initval;
<a name="L455" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L455">455</a>         <a href="ident?i=compat_uptr_t">compat_uptr_t</a>   <a href="ident?i=config">config</a>;
<a name="L456" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L456">456</a> };
<a name="L457" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L457">457</a> #endif <b><i>/* CONFIG_COMPAT */</i></b>
<a name="L458" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L458">458</a> 
<a name="L459" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L459">459</a> static struct <a href="ident?i=xt_target">xt_target</a> clusterip_tg_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L460" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L460">460</a>         .<a href="ident?i=name">name</a>           = <i>"CLUSTERIP"</i>,
<a name="L461" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L461">461</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
<a name="L462" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L462">462</a>         .<a href="ident?i=target">target</a>         = <a href="ident?i=clusterip_tg">clusterip_tg</a>,
<a name="L463" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L463">463</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=clusterip_tg_check">clusterip_tg_check</a>,
<a name="L464" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L464">464</a>         .<a href="ident?i=destroy">destroy</a>        = <a href="ident?i=clusterip_tg_destroy">clusterip_tg_destroy</a>,
<a name="L465" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L465">465</a>         .targetsize     = sizeof(struct <a href="ident?i=ipt_clusterip_tgt_info">ipt_clusterip_tgt_info</a>),
<a name="L466" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L466">466</a> #ifdef CONFIG_COMPAT
<a name="L467" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L467">467</a>         .compatsize     = sizeof(struct <a href="ident?i=compat_ipt_clusterip_tgt_info">compat_ipt_clusterip_tgt_info</a>),
<a name="L468" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L468">468</a> #endif <b><i>/* CONFIG_COMPAT */</i></b>
<a name="L469" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L469">469</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>
<a name="L470" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L470">470</a> };
<a name="L471" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L473">473</a> <b><i>/***********************************************************************</i></b>
<a name="L474" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L474">474</a> <b><i> * ARP MANGLING CODE</i></b>
<a name="L475" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L475">475</a> <b><i> ***********************************************************************/</i></b>
<a name="L476" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L477">477</a> <b><i>/* hardcoded for 48bit ethernet and 32bit ipv4 addresses */</i></b>
<a name="L478" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L478">478</a> struct <a href="ident?i=arp_payload">arp_payload</a> {
<a name="L479" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L479">479</a>         <a href="ident?i=u_int8_t">u_int8_t</a> src_hw[<a href="ident?i=ETH_ALEN">ETH_ALEN</a>];
<a name="L480" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L480">480</a>         <a href="ident?i=__be32">__be32</a> src_ip;
<a name="L481" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L481">481</a>         <a href="ident?i=u_int8_t">u_int8_t</a> dst_hw[<a href="ident?i=ETH_ALEN">ETH_ALEN</a>];
<a name="L482" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L482">482</a>         <a href="ident?i=__be32">__be32</a> dst_ip;
<a name="L483" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L483">483</a> } <a href="ident?i=__packed">__packed</a>;
<a name="L484" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L484">484</a> 
<a name="L485" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L485">485</a> #ifdef <a href="ident?i=DEBUG">DEBUG</a>
<a name="L486" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L486">486</a> static void <a href="ident?i=arp_print">arp_print</a>(struct <a href="ident?i=arp_payload">arp_payload</a> *<a href="ident?i=payload">payload</a>)
<a name="L487" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L487">487</a> {
<a name="L488" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L488">488</a> #define <a href="ident?i=HBUFFERLEN">HBUFFERLEN</a> 30
<a name="L489" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L489">489</a>         char hbuffer[<a href="ident?i=HBUFFERLEN">HBUFFERLEN</a>];
<a name="L490" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L490">490</a>         int j,k;
<a name="L491" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L492">492</a>         for (k=0, j=0; k &lt; <a href="ident?i=HBUFFERLEN">HBUFFERLEN</a>-3 &amp;&amp; j &lt; <a href="ident?i=ETH_ALEN">ETH_ALEN</a>; j++) {
<a name="L493" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L493">493</a>                 hbuffer[k++] = <a href="ident?i=hex_asc_hi">hex_asc_hi</a>(<a href="ident?i=payload">payload</a>-&gt;src_hw[j]);
<a name="L494" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L494">494</a>                 hbuffer[k++] = <a href="ident?i=hex_asc_lo">hex_asc_lo</a>(<a href="ident?i=payload">payload</a>-&gt;src_hw[j]);
<a name="L495" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L495">495</a>                 hbuffer[k++]=<i>':'</i>;
<a name="L496" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L496">496</a>         }
<a name="L497" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L497">497</a>         hbuffer[--k]=<i>'\0'</i>;
<a name="L498" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L499">499</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"src %pI4@%s, dst %pI4\n"</i>,
<a name="L500" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L500">500</a>                  &amp;<a href="ident?i=payload">payload</a>-&gt;src_ip, hbuffer, &amp;<a href="ident?i=payload">payload</a>-&gt;dst_ip);
<a name="L501" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L501">501</a> }
<a name="L502" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L502">502</a> #endif
<a name="L503" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L504">504</a> static unsigned int
<a name="L505" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L505">505</a> <a href="ident?i=arp_mangle">arp_mangle</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L506" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L506">506</a>            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L507" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L507">507</a>            const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
<a name="L508" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L508">508</a> {
<a name="L509" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L509">509</a>         struct <a href="ident?i=arphdr">arphdr</a> *arp = <a href="ident?i=arp_hdr">arp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L510" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L510">510</a>         struct <a href="ident?i=arp_payload">arp_payload</a> *<a href="ident?i=payload">payload</a>;
<a name="L511" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L511">511</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a>;
<a name="L512" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L512">512</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> : <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>);
<a name="L513" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L514">514</a>         <b><i>/* we don't care about non-ethernet and non-ipv4 ARP */</i></b>
<a name="L515" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L515">515</a>         if (arp-&gt;ar_hrd != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>) ||
<a name="L516" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L516">516</a>             arp-&gt;ar_pro != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>) ||
<a name="L517" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L517">517</a>             arp-&gt;ar_pln != 4 || arp-&gt;ar_hln != <a href="ident?i=ETH_ALEN">ETH_ALEN</a>)
<a name="L518" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L518">518</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L519" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L520">520</a>         <b><i>/* we only want to mangle arp requests and replies */</i></b>
<a name="L521" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L521">521</a>         if (arp-&gt;ar_op != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>) &amp;&amp;
<a name="L522" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L522">522</a>             arp-&gt;ar_op != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>))
<a name="L523" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L523">523</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L524" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L524">524</a> 
<a name="L525" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L525">525</a>         <a href="ident?i=payload">payload</a> = (void *)(arp+1);
<a name="L526" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L526">526</a> 
<a name="L527" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L527">527</a>         <b><i>/* if there is no clusterip configuration for the arp reply's</i></b>
<a name="L528" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L528">528</a> <b><i>         * source ip, we don't want to mangle it */</i></b>
<a name="L529" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L529">529</a>         <a href="ident?i=c">c</a> = <a href="ident?i=clusterip_config_find_get">clusterip_config_find_get</a>(<a href="ident?i=net">net</a>, <a href="ident?i=payload">payload</a>-&gt;src_ip, 0);
<a name="L530" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L530">530</a>         if (!<a href="ident?i=c">c</a>)
<a name="L531" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L531">531</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L532" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L533">533</a>         <b><i>/* normally the linux kernel always replies to arp queries of</i></b>
<a name="L534" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L534">534</a> <b><i>         * addresses on different interfacs.  However, in the CLUSTERIP case</i></b>
<a name="L535" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L535">535</a> <b><i>         * this wouldn't work, since we didn't subscribe the mcast group on</i></b>
<a name="L536" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L536">536</a> <b><i>         * other interfaces */</i></b>
<a name="L537" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L537">537</a>         if (<a href="ident?i=c">c</a>-&gt;<a href="ident?i=dev">dev</a> != <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>) {
<a name="L538" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L538">538</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"not mangling arp reply on different "</i>
<a name="L539" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L539">539</a>                          <i>"interface: cip'%s'-skb'%s'\n"</i>,
<a name="L540" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L540">540</a>                          <a href="ident?i=c">c</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L541" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L541">541</a>                 <a href="ident?i=clusterip_config_put">clusterip_config_put</a>(<a href="ident?i=c">c</a>);
<a name="L542" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L542">542</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L543" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L543">543</a>         }
<a name="L544" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L544">544</a> 
<a name="L545" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L545">545</a>         <b><i>/* mangle reply hardware address */</i></b>
<a name="L546" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L546">546</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=payload">payload</a>-&gt;src_hw, <a href="ident?i=c">c</a>-&gt;clustermac, arp-&gt;ar_hln);
<a name="L547" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L548">548</a> #ifdef <a href="ident?i=DEBUG">DEBUG</a>
<a name="L549" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L549">549</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"mangled arp reply: "</i>);
<a name="L550" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L550">550</a>         <a href="ident?i=arp_print">arp_print</a>(<a href="ident?i=payload">payload</a>);
<a name="L551" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L551">551</a> #endif
<a name="L552" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L553">553</a>         <a href="ident?i=clusterip_config_put">clusterip_config_put</a>(<a href="ident?i=c">c</a>);
<a name="L554" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L555">555</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L556" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L556">556</a> }
<a name="L557" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L558">558</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> cip_arp_ops <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L559" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L559">559</a>         .hook = <a href="ident?i=arp_mangle">arp_mangle</a>,
<a name="L560" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L560">560</a>         .<a href="ident?i=pf">pf</a> = NFPROTO_ARP,
<a name="L561" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L561">561</a>         .hooknum = <a href="ident?i=NF_ARP_OUT">NF_ARP_OUT</a>,
<a name="L562" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L562">562</a>         .<a href="ident?i=priority">priority</a> = -1
<a name="L563" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L563">563</a> };
<a name="L564" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L564">564</a> 
<a name="L565" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L565">565</a> <b><i>/***********************************************************************</i></b>
<a name="L566" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L566">566</a> <b><i> * PROC DIR HANDLING</i></b>
<a name="L567" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L567">567</a> <b><i> ***********************************************************************/</i></b>
<a name="L568" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L568">568</a> 
<a name="L569" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L569">569</a> #ifdef CONFIG_PROC_FS
<a name="L570" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L570">570</a> 
<a name="L571" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L571">571</a> struct <a href="ident?i=clusterip_seq_position">clusterip_seq_position</a> {
<a name="L572" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L572">572</a>         unsigned int <a href="ident?i=pos">pos</a>;       <b><i>/* position */</i></b>
<a name="L573" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L573">573</a>         unsigned int <a href="ident?i=weight">weight</a>;    <b><i>/* number of bits set == size */</i></b>
<a name="L574" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L574">574</a>         unsigned int <a href="ident?i=bit">bit</a>;       <b><i>/* current bit */</i></b>
<a name="L575" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L575">575</a>         unsigned long <a href="ident?i=val">val</a>;      <b><i>/* current value */</i></b>
<a name="L576" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L576">576</a> };
<a name="L577" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L577">577</a> 
<a name="L578" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L578">578</a> static void *<a href="ident?i=clusterip_seq_start">clusterip_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L579" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L579">579</a> {
<a name="L580" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L580">580</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a> = <a href="ident?i=s">s</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L581" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L581">581</a>         unsigned int <a href="ident?i=weight">weight</a>;
<a name="L582" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L582">582</a>         <a href="ident?i=u_int32_t">u_int32_t</a> local_nodes;
<a name="L583" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L583">583</a>         struct <a href="ident?i=clusterip_seq_position">clusterip_seq_position</a> *<a href="ident?i=idx">idx</a>;
<a name="L584" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L584">584</a> 
<a name="L585" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L585">585</a>         <b><i>/* FIXME: possible race */</i></b>
<a name="L586" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L586">586</a>         local_nodes = <a href="ident?i=c">c</a>-&gt;local_nodes;
<a name="L587" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L587">587</a>         <a href="ident?i=weight">weight</a> = <a href="ident?i=hweight32">hweight32</a>(local_nodes);
<a name="L588" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L588">588</a>         if (*<a href="ident?i=pos">pos</a> &gt;= <a href="ident?i=weight">weight</a>)
<a name="L589" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L589">589</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L590" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L590">590</a> 
<a name="L591" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L591">591</a>         <a href="ident?i=idx">idx</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=clusterip_seq_position">clusterip_seq_position</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L592" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L592">592</a>         if (!<a href="ident?i=idx">idx</a>)
<a name="L593" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L593">593</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOMEM">ENOMEM</a>);
<a name="L594" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L594">594</a> 
<a name="L595" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L595">595</a>         <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=pos">pos</a> = *<a href="ident?i=pos">pos</a>;
<a name="L596" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L596">596</a>         <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=weight">weight</a> = <a href="ident?i=weight">weight</a>;
<a name="L597" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L597">597</a>         <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=bit">bit</a> = <a href="ident?i=ffs">ffs</a>(local_nodes);
<a name="L598" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L598">598</a>         <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=val">val</a> = local_nodes;
<a name="L599" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L599">599</a>         <a href="ident?i=clear_bit">clear_bit</a>(<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=bit">bit</a> - 1, &amp;<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=val">val</a>);
<a name="L600" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L600">600</a> 
<a name="L601" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L601">601</a>         return <a href="ident?i=idx">idx</a>;
<a name="L602" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L602">602</a> }
<a name="L603" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L604">604</a> static void *<a href="ident?i=clusterip_seq_next">clusterip_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L605" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L605">605</a> {
<a name="L606" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L606">606</a>         struct <a href="ident?i=clusterip_seq_position">clusterip_seq_position</a> *<a href="ident?i=idx">idx</a> = <a href="ident?i=v">v</a>;
<a name="L607" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L607">607</a> 
<a name="L608" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L608">608</a>         *<a href="ident?i=pos">pos</a> = ++<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=pos">pos</a>;
<a name="L609" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L609">609</a>         if (*<a href="ident?i=pos">pos</a> &gt;= <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=weight">weight</a>) {
<a name="L610" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L610">610</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=v">v</a>);
<a name="L611" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L611">611</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L612" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L612">612</a>         }
<a name="L613" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L613">613</a>         <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=bit">bit</a> = <a href="ident?i=ffs">ffs</a>(<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=val">val</a>);
<a name="L614" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L614">614</a>         <a href="ident?i=clear_bit">clear_bit</a>(<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=bit">bit</a> - 1, &amp;<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=val">val</a>);
<a name="L615" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L615">615</a>         return <a href="ident?i=idx">idx</a>;
<a name="L616" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L616">616</a> }
<a name="L617" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L618">618</a> static void <a href="ident?i=clusterip_seq_stop">clusterip_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>)
<a name="L619" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L619">619</a> {
<a name="L620" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L620">620</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=v">v</a>))
<a name="L621" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L621">621</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=v">v</a>);
<a name="L622" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L622">622</a> }
<a name="L623" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L623">623</a> 
<a name="L624" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L624">624</a> static int <a href="ident?i=clusterip_seq_show">clusterip_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>)
<a name="L625" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L625">625</a> {
<a name="L626" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L626">626</a>         struct <a href="ident?i=clusterip_seq_position">clusterip_seq_position</a> *<a href="ident?i=idx">idx</a> = <a href="ident?i=v">v</a>;
<a name="L627" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L627">627</a> 
<a name="L628" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L628">628</a>         if (<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=pos">pos</a> != 0)
<a name="L629" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L629">629</a>                 <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=s">s</a>, <i>','</i>);
<a name="L630" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L630">630</a> 
<a name="L631" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L631">631</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"%u"</i>, <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=bit">bit</a>);
<a name="L632" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L632">632</a> 
<a name="L633" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L633">633</a>         if (<a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=pos">pos</a> == <a href="ident?i=idx">idx</a>-&gt;<a href="ident?i=weight">weight</a> - 1)
<a name="L634" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L634">634</a>                 <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=s">s</a>, <i>'\n'</i>);
<a name="L635" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L635">635</a> 
<a name="L636" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L636">636</a>         return 0;
<a name="L637" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L637">637</a> }
<a name="L638" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L638">638</a> 
<a name="L639" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L639">639</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=clusterip_seq_ops">clusterip_seq_ops</a> = {
<a name="L640" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L640">640</a>         .<a href="ident?i=start">start</a>  = <a href="ident?i=clusterip_seq_start">clusterip_seq_start</a>,
<a name="L641" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L641">641</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=clusterip_seq_next">clusterip_seq_next</a>,
<a name="L642" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L642">642</a>         .<a href="ident?i=stop">stop</a>   = <a href="ident?i=clusterip_seq_stop">clusterip_seq_stop</a>,
<a name="L643" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L643">643</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=clusterip_seq_show">clusterip_seq_show</a>,
<a name="L644" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L644">644</a> };
<a name="L645" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L646">646</a> static int <a href="ident?i=clusterip_proc_open">clusterip_proc_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L647" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L647">647</a> {
<a name="L648" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L648">648</a>         int <a href="ident?i=ret">ret</a> = <a href="ident?i=seq_open">seq_open</a>(<a href="ident?i=file">file</a>, &amp;<a href="ident?i=clusterip_seq_ops">clusterip_seq_ops</a>);
<a name="L649" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L649">649</a> 
<a name="L650" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L650">650</a>         if (!<a href="ident?i=ret">ret</a>) {
<a name="L651" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L651">651</a>                 struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=sf">sf</a> = <a href="ident?i=file">file</a>-&gt;<a href="ident?i=private_data">private_data</a>;
<a name="L652" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L652">652</a>                 struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a> = <a href="ident?i=PDE_DATA">PDE_DATA</a>(<a href="ident?i=inode">inode</a>);
<a name="L653" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L653">653</a> 
<a name="L654" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L654">654</a>                 <a href="ident?i=sf">sf</a>-&gt;<a href="ident?i=private">private</a> = <a href="ident?i=c">c</a>;
<a name="L655" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L655">655</a> 
<a name="L656" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L656">656</a>                 <a href="ident?i=clusterip_config_get">clusterip_config_get</a>(<a href="ident?i=c">c</a>);
<a name="L657" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L657">657</a>         }
<a name="L658" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L658">658</a> 
<a name="L659" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L659">659</a>         return <a href="ident?i=ret">ret</a>;
<a name="L660" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L660">660</a> }
<a name="L661" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L662">662</a> static int <a href="ident?i=clusterip_proc_release">clusterip_proc_release</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L663" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L663">663</a> {
<a name="L664" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L664">664</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a> = <a href="ident?i=PDE_DATA">PDE_DATA</a>(<a href="ident?i=inode">inode</a>);
<a name="L665" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L665">665</a>         int <a href="ident?i=ret">ret</a>;
<a name="L666" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L666">666</a> 
<a name="L667" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L667">667</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=seq_release">seq_release</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>);
<a name="L668" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L668">668</a> 
<a name="L669" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L669">669</a>         if (!<a href="ident?i=ret">ret</a>)
<a name="L670" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L670">670</a>                 <a href="ident?i=clusterip_config_put">clusterip_config_put</a>(<a href="ident?i=c">c</a>);
<a name="L671" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L672">672</a>         return <a href="ident?i=ret">ret</a>;
<a name="L673" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L673">673</a> }
<a name="L674" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L675">675</a> static <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=clusterip_proc_write">clusterip_proc_write</a>(struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>, const char <a href="ident?i=__user">__user</a> *<a href="ident?i=input">input</a>,
<a name="L676" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L676">676</a>                                 <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ofs">ofs</a>)
<a name="L677" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L677">677</a> {
<a name="L678" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L678">678</a>         struct <a href="ident?i=clusterip_config">clusterip_config</a> *<a href="ident?i=c">c</a> = <a href="ident?i=PDE_DATA">PDE_DATA</a>(<a href="ident?i=file_inode">file_inode</a>(<a href="ident?i=file">file</a>));
<a name="L679" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L679">679</a> #define <a href="ident?i=PROC_WRITELEN">PROC_WRITELEN</a>   10
<a name="L680" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L680">680</a>         char <a href="ident?i=buffer">buffer</a>[<a href="ident?i=PROC_WRITELEN">PROC_WRITELEN</a>+1];
<a name="L681" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L681">681</a>         unsigned long nodenum;
<a name="L682" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L682">682</a>         int <a href="ident?i=rc">rc</a>;
<a name="L683" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L683">683</a> 
<a name="L684" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L684">684</a>         if (<a href="ident?i=size">size</a> &gt; <a href="ident?i=PROC_WRITELEN">PROC_WRITELEN</a>)
<a name="L685" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L685">685</a>                 return -<a href="ident?i=EIO">EIO</a>;
<a name="L686" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L686">686</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(<a href="ident?i=buffer">buffer</a>, <a href="ident?i=input">input</a>, <a href="ident?i=size">size</a>))
<a name="L687" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L687">687</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L688" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L688">688</a>         <a href="ident?i=buffer">buffer</a>[<a href="ident?i=size">size</a>] = 0;
<a name="L689" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L689">689</a> 
<a name="L690" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L690">690</a>         if (*<a href="ident?i=buffer">buffer</a> == <i>'+'</i>) {
<a name="L691" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L691">691</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=kstrtoul">kstrtoul</a>(<a href="ident?i=buffer">buffer</a>+1, 10, &amp;nodenum);
<a name="L692" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L692">692</a>                 if (<a href="ident?i=rc">rc</a>)
<a name="L693" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L693">693</a>                         return <a href="ident?i=rc">rc</a>;
<a name="L694" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L694">694</a>                 if (<a href="ident?i=clusterip_add_node">clusterip_add_node</a>(<a href="ident?i=c">c</a>, nodenum))
<a name="L695" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L695">695</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L696" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L696">696</a>         } else if (*<a href="ident?i=buffer">buffer</a> == <i>'-'</i>) {
<a name="L697" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L697">697</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=kstrtoul">kstrtoul</a>(<a href="ident?i=buffer">buffer</a>+1, 10, &amp;nodenum);
<a name="L698" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L698">698</a>                 if (<a href="ident?i=rc">rc</a>)
<a name="L699" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L699">699</a>                         return <a href="ident?i=rc">rc</a>;
<a name="L700" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L700">700</a>                 if (<a href="ident?i=clusterip_del_node">clusterip_del_node</a>(<a href="ident?i=c">c</a>, nodenum))
<a name="L701" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L701">701</a>                         return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L702" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L702">702</a>         } else
<a name="L703" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L703">703</a>                 return -<a href="ident?i=EIO">EIO</a>;
<a name="L704" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L705">705</a>         return <a href="ident?i=size">size</a>;
<a name="L706" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L706">706</a> }
<a name="L707" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L707">707</a> 
<a name="L708" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L708">708</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=clusterip_proc_fops">clusterip_proc_fops</a> = {
<a name="L709" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L709">709</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L710" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L710">710</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=clusterip_proc_open">clusterip_proc_open</a>,
<a name="L711" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L711">711</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L712" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L712">712</a>         .<a href="ident?i=write">write</a>   = <a href="ident?i=clusterip_proc_write">clusterip_proc_write</a>,
<a name="L713" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L713">713</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L714" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L714">714</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=clusterip_proc_release">clusterip_proc_release</a>,
<a name="L715" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L715">715</a> };
<a name="L716" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L716">716</a> 
<a name="L717" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L717">717</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L718" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L719">719</a> static int <a href="ident?i=clusterip_net_init">clusterip_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L720" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L720">720</a> {
<a name="L721" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L721">721</a>         struct <a href="ident?i=clusterip_net">clusterip_net</a> *cn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, clusterip_net_id);
<a name="L722" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L723">723</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;cn-&gt;<a href="ident?i=configs">configs</a>);
<a name="L724" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L725">725</a>         <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;cn-&gt;<a href="ident?i=lock">lock</a>);
<a name="L726" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L726">726</a> 
<a name="L727" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L727">727</a> #ifdef CONFIG_PROC_FS
<a name="L728" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L728">728</a>         cn-&gt;procdir = <a href="ident?i=proc_mkdir">proc_mkdir</a>(<i>"ipt_CLUSTERIP"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L729" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L729">729</a>         if (!cn-&gt;procdir) {
<a name="L730" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L730">730</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Unable to proc dir entry\n"</i>);
<a name="L731" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L731">731</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L732" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L732">732</a>         }
<a name="L733" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L733">733</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L734" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L734">734</a> 
<a name="L735" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L735">735</a>         return 0;
<a name="L736" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L736">736</a> }
<a name="L737" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L737">737</a> 
<a name="L738" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L738">738</a> static void <a href="ident?i=clusterip_net_exit">clusterip_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L739" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L739">739</a> {
<a name="L740" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L740">740</a> #ifdef CONFIG_PROC_FS
<a name="L741" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L741">741</a>         struct <a href="ident?i=clusterip_net">clusterip_net</a> *cn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, clusterip_net_id);
<a name="L742" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L742">742</a>         <a href="ident?i=proc_remove">proc_remove</a>(cn-&gt;procdir);
<a name="L743" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L743">743</a> #endif
<a name="L744" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L744">744</a> }
<a name="L745" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L745">745</a> 
<a name="L746" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L746">746</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=clusterip_net_ops">clusterip_net_ops</a> = {
<a name="L747" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L747">747</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=clusterip_net_init">clusterip_net_init</a>,
<a name="L748" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L748">748</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=clusterip_net_exit">clusterip_net_exit</a>,
<a name="L749" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L749">749</a>         .<a href="ident?i=id">id</a>   = &amp;clusterip_net_id,
<a name="L750" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L750">750</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=clusterip_net">clusterip_net</a>),
<a name="L751" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L751">751</a> };
<a name="L752" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L752">752</a> 
<a name="L753" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L753">753</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=clusterip_tg_init">clusterip_tg_init</a>(void)
<a name="L754" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L754">754</a> {
<a name="L755" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L755">755</a>         int <a href="ident?i=ret">ret</a>;
<a name="L756" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L756">756</a> 
<a name="L757" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L757">757</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=clusterip_net_ops">clusterip_net_ops</a>);
<a name="L758" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L758">758</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L759" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L759">759</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L760" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L761">761</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_register_target">xt_register_target</a>(&amp;clusterip_tg_reg);
<a name="L762" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L762">762</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L763" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L763">763</a>                 goto cleanup_subsys;
<a name="L764" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L764">764</a> 
<a name="L765" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L765">765</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_register_hook">nf_register_hook</a>(&amp;cip_arp_ops);
<a name="L766" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L766">766</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L767" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L767">767</a>                 goto cleanup_target;
<a name="L768" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L769">769</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"ClusterIP Version %s loaded successfully\n"</i>,
<a name="L770" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L770">770</a>                 <a href="ident?i=CLUSTERIP_VERSION">CLUSTERIP_VERSION</a>);
<a name="L771" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L771">771</a> 
<a name="L772" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L772">772</a>         return 0;
<a name="L773" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L774">774</a> cleanup_target:
<a name="L775" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L775">775</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;clusterip_tg_reg);
<a name="L776" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L776">776</a> cleanup_subsys:
<a name="L777" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L777">777</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=clusterip_net_ops">clusterip_net_ops</a>);
<a name="L778" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L778">778</a>         return <a href="ident?i=ret">ret</a>;
<a name="L779" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L779">779</a> }
<a name="L780" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L780">780</a> 
<a name="L781" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L781">781</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=clusterip_tg_exit">clusterip_tg_exit</a>(void)
<a name="L782" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L782">782</a> {
<a name="L783" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L783">783</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"ClusterIP Version %s unloading\n"</i>, <a href="ident?i=CLUSTERIP_VERSION">CLUSTERIP_VERSION</a>);
<a name="L784" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L785">785</a>         <a href="ident?i=nf_unregister_hook">nf_unregister_hook</a>(&amp;cip_arp_ops);
<a name="L786" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L786">786</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;clusterip_tg_reg);
<a name="L787" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L787">787</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=clusterip_net_ops">clusterip_net_ops</a>);
<a name="L788" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L789">789</a>         <b><i>/* Wait for completion of call_rcu_bh()'s (clusterip_config_rcu_free) */</i></b>
<a name="L790" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L790">790</a>         <a href="ident?i=rcu_barrier_bh">rcu_barrier_bh</a>();
<a name="L791" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L791">791</a> }
<a name="L792" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L792">792</a> 
<a name="L793" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L793">793</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=clusterip_tg_init">clusterip_tg_init</a>);
<a name="L794" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L794">794</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=clusterip_tg_exit">clusterip_tg_exit</a>);
<a name="L795" href="source/net/ipv4/netfilter/ipt_CLUSTERIP.c#L795">795</a> </pre></div><p>
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
