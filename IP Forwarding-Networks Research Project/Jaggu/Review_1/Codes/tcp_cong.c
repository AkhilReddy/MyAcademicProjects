<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_cong.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_cong.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_cong.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_cong.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_cong.c">tcp_cong.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_cong.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_cong.c#L2">2</a> <b><i> * Pluggable TCP congestion control support and newReno</i></b>
  <a name="L3" href="source/net/ipv4/tcp_cong.c#L3">3</a> <b><i> * congestion control.</i></b>
  <a name="L4" href="source/net/ipv4/tcp_cong.c#L4">4</a> <b><i> * Based on ideas from I/O scheduler support and Web100.</i></b>
  <a name="L5" href="source/net/ipv4/tcp_cong.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_cong.c#L6">6</a> <b><i> * Copyright (C) 2005 Stephen Hemminger &lt;shemminger@osdl.org&gt;</i></b>
  <a name="L7" href="source/net/ipv4/tcp_cong.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/tcp_cong.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/tcp_cong.c#L9">9</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"TCP: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L10" href="source/net/ipv4/tcp_cong.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/tcp_cong.c#L11">11</a> #include &lt;linux/module.h&gt;
 <a name="L12" href="source/net/ipv4/tcp_cong.c#L12">12</a> #include &lt;linux/mm.h&gt;
 <a name="L13" href="source/net/ipv4/tcp_cong.c#L13">13</a> #include &lt;linux/types.h&gt;
 <a name="L14" href="source/net/ipv4/tcp_cong.c#L14">14</a> #include &lt;linux/list.h&gt;
 <a name="L15" href="source/net/ipv4/tcp_cong.c#L15">15</a> #include &lt;linux/gfp.h&gt;
 <a name="L16" href="source/net/ipv4/tcp_cong.c#L16">16</a> #include &lt;linux/jhash.h&gt;
 <a name="L17" href="source/net/ipv4/tcp_cong.c#L17">17</a> #include &lt;net/tcp.h&gt;
 <a name="L18" href="source/net/ipv4/tcp_cong.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/tcp_cong.c#L19">19</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(tcp_cong_list_lock);
 <a name="L20" href="source/net/ipv4/tcp_cong.c#L20">20</a> static <a href="ident?i=LIST_HEAD">LIST_HEAD</a>(tcp_cong_list);
 <a name="L21" href="source/net/ipv4/tcp_cong.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/tcp_cong.c#L22">22</a> <b><i>/* Simple linear search, don't expect many entries! */</i></b>
 <a name="L23" href="source/net/ipv4/tcp_cong.c#L23">23</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=tcp_ca_find">tcp_ca_find</a>(const char *<a href="ident?i=name">name</a>)
 <a name="L24" href="source/net/ipv4/tcp_cong.c#L24">24</a> {
 <a name="L25" href="source/net/ipv4/tcp_cong.c#L25">25</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=e">e</a>;
 <a name="L26" href="source/net/ipv4/tcp_cong.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/tcp_cong.c#L27">27</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=e">e</a>, &amp;tcp_cong_list, <a href="ident?i=list">list</a>) {
 <a name="L28" href="source/net/ipv4/tcp_cong.c#L28">28</a>                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=name">name</a>) == 0)
 <a name="L29" href="source/net/ipv4/tcp_cong.c#L29">29</a>                         return <a href="ident?i=e">e</a>;
 <a name="L30" href="source/net/ipv4/tcp_cong.c#L30">30</a>         }
 <a name="L31" href="source/net/ipv4/tcp_cong.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/tcp_cong.c#L32">32</a>         return <a href="ident?i=NULL">NULL</a>;
 <a name="L33" href="source/net/ipv4/tcp_cong.c#L33">33</a> }
 <a name="L34" href="source/net/ipv4/tcp_cong.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/tcp_cong.c#L35">35</a> <b><i>/* Must be called with rcu lock held */</i></b>
 <a name="L36" href="source/net/ipv4/tcp_cong.c#L36">36</a> static const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=__tcp_ca_find_autoload">__tcp_ca_find_autoload</a>(const char *<a href="ident?i=name">name</a>)
 <a name="L37" href="source/net/ipv4/tcp_cong.c#L37">37</a> {
 <a name="L38" href="source/net/ipv4/tcp_cong.c#L38">38</a>         const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find">tcp_ca_find</a>(<a href="ident?i=name">name</a>);
 <a name="L39" href="source/net/ipv4/tcp_cong.c#L39">39</a> #ifdef CONFIG_MODULES
 <a name="L40" href="source/net/ipv4/tcp_cong.c#L40">40</a>         if (!<a href="ident?i=ca">ca</a> &amp;&amp; <a href="ident?i=capable">capable</a>(<a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>)) {
 <a name="L41" href="source/net/ipv4/tcp_cong.c#L41">41</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
 <a name="L42" href="source/net/ipv4/tcp_cong.c#L42">42</a>                 <a href="ident?i=request_module">request_module</a>(<i>"tcp_%s"</i>, <a href="ident?i=name">name</a>);
 <a name="L43" href="source/net/ipv4/tcp_cong.c#L43">43</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
 <a name="L44" href="source/net/ipv4/tcp_cong.c#L44">44</a>                 <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find">tcp_ca_find</a>(<a href="ident?i=name">name</a>);
 <a name="L45" href="source/net/ipv4/tcp_cong.c#L45">45</a>         }
 <a name="L46" href="source/net/ipv4/tcp_cong.c#L46">46</a> #endif
 <a name="L47" href="source/net/ipv4/tcp_cong.c#L47">47</a>         return <a href="ident?i=ca">ca</a>;
 <a name="L48" href="source/net/ipv4/tcp_cong.c#L48">48</a> }
 <a name="L49" href="source/net/ipv4/tcp_cong.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/tcp_cong.c#L50">50</a> <b><i>/* Simple linear search, not much in here. */</i></b>
 <a name="L51" href="source/net/ipv4/tcp_cong.c#L51">51</a> struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=tcp_ca_find_key">tcp_ca_find_key</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=key">key</a>)
 <a name="L52" href="source/net/ipv4/tcp_cong.c#L52">52</a> {
 <a name="L53" href="source/net/ipv4/tcp_cong.c#L53">53</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=e">e</a>;
 <a name="L54" href="source/net/ipv4/tcp_cong.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/tcp_cong.c#L55">55</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=e">e</a>, &amp;tcp_cong_list, <a href="ident?i=list">list</a>) {
 <a name="L56" href="source/net/ipv4/tcp_cong.c#L56">56</a>                 if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=key">key</a> == <a href="ident?i=key">key</a>)
 <a name="L57" href="source/net/ipv4/tcp_cong.c#L57">57</a>                         return <a href="ident?i=e">e</a>;
 <a name="L58" href="source/net/ipv4/tcp_cong.c#L58">58</a>         }
 <a name="L59" href="source/net/ipv4/tcp_cong.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/tcp_cong.c#L60">60</a>         return <a href="ident?i=NULL">NULL</a>;
 <a name="L61" href="source/net/ipv4/tcp_cong.c#L61">61</a> }
 <a name="L62" href="source/net/ipv4/tcp_cong.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/tcp_cong.c#L63">63</a> <b><i>/*</i></b>
 <a name="L64" href="source/net/ipv4/tcp_cong.c#L64">64</a> <b><i> * Attach new congestion control algorithm to the list</i></b>
 <a name="L65" href="source/net/ipv4/tcp_cong.c#L65">65</a> <b><i> * of available options.</i></b>
 <a name="L66" href="source/net/ipv4/tcp_cong.c#L66">66</a> <b><i> */</i></b>
 <a name="L67" href="source/net/ipv4/tcp_cong.c#L67">67</a> int <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>)
 <a name="L68" href="source/net/ipv4/tcp_cong.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/tcp_cong.c#L69">69</a>         int <a href="ident?i=ret">ret</a> = 0;
 <a name="L70" href="source/net/ipv4/tcp_cong.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/tcp_cong.c#L71">71</a>         <b><i>/* all algorithms must implement ssthresh and cong_avoid ops */</i></b>
 <a name="L72" href="source/net/ipv4/tcp_cong.c#L72">72</a>         if (!<a href="ident?i=ca">ca</a>-&gt;ssthresh || !<a href="ident?i=ca">ca</a>-&gt;cong_avoid) {
 <a name="L73" href="source/net/ipv4/tcp_cong.c#L73">73</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"%s does not implement required ops\n"</i>, <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>);
 <a name="L74" href="source/net/ipv4/tcp_cong.c#L74">74</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L75" href="source/net/ipv4/tcp_cong.c#L75">75</a>         }
 <a name="L76" href="source/net/ipv4/tcp_cong.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/tcp_cong.c#L77">77</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=key">key</a> = <a href="ident?i=jhash">jhash</a>(<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>, sizeof(<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>), <a href="ident?i=strlen">strlen</a>(<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>));
 <a name="L78" href="source/net/ipv4/tcp_cong.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/tcp_cong.c#L79">79</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;tcp_cong_list_lock);
 <a name="L80" href="source/net/ipv4/tcp_cong.c#L80">80</a>         if (<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=key">key</a> == <a href="ident?i=TCP_CA_UNSPEC">TCP_CA_UNSPEC</a> || <a href="ident?i=tcp_ca_find_key">tcp_ca_find_key</a>(<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=key">key</a>)) {
 <a name="L81" href="source/net/ipv4/tcp_cong.c#L81">81</a>                 <a href="ident?i=pr_notice">pr_notice</a>(<i>"%s already registered or non-unique key\n"</i>,
 <a name="L82" href="source/net/ipv4/tcp_cong.c#L82">82</a>                           <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>);
 <a name="L83" href="source/net/ipv4/tcp_cong.c#L83">83</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
 <a name="L84" href="source/net/ipv4/tcp_cong.c#L84">84</a>         } else {
 <a name="L85" href="source/net/ipv4/tcp_cong.c#L85">85</a>                 <a href="ident?i=list_add_tail_rcu">list_add_tail_rcu</a>(&amp;<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=list">list</a>, &amp;tcp_cong_list);
 <a name="L86" href="source/net/ipv4/tcp_cong.c#L86">86</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"%s registered\n"</i>, <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>);
 <a name="L87" href="source/net/ipv4/tcp_cong.c#L87">87</a>         }
 <a name="L88" href="source/net/ipv4/tcp_cong.c#L88">88</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;tcp_cong_list_lock);
 <a name="L89" href="source/net/ipv4/tcp_cong.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/tcp_cong.c#L90">90</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L91" href="source/net/ipv4/tcp_cong.c#L91">91</a> }
 <a name="L92" href="source/net/ipv4/tcp_cong.c#L92">92</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>);
 <a name="L93" href="source/net/ipv4/tcp_cong.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/tcp_cong.c#L94">94</a> <b><i>/*</i></b>
 <a name="L95" href="source/net/ipv4/tcp_cong.c#L95">95</a> <b><i> * Remove congestion control algorithm, called from</i></b>
 <a name="L96" href="source/net/ipv4/tcp_cong.c#L96">96</a> <b><i> * the module's remove function.  Module ref counts are used</i></b>
 <a name="L97" href="source/net/ipv4/tcp_cong.c#L97">97</a> <b><i> * to ensure that this can't be done till all sockets using</i></b>
 <a name="L98" href="source/net/ipv4/tcp_cong.c#L98">98</a> <b><i> * that method are closed.</i></b>
 <a name="L99" href="source/net/ipv4/tcp_cong.c#L99">99</a> <b><i> */</i></b>
<a name="L100" href="source/net/ipv4/tcp_cong.c#L100">100</a> void <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>)
<a name="L101" href="source/net/ipv4/tcp_cong.c#L101">101</a> {
<a name="L102" href="source/net/ipv4/tcp_cong.c#L102">102</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;tcp_cong_list_lock);
<a name="L103" href="source/net/ipv4/tcp_cong.c#L103">103</a>         <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L104" href="source/net/ipv4/tcp_cong.c#L104">104</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;tcp_cong_list_lock);
<a name="L105" href="source/net/ipv4/tcp_cong.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/tcp_cong.c#L106">106</a>         <b><i>/* Wait for outstanding readers to complete before the</i></b>
<a name="L107" href="source/net/ipv4/tcp_cong.c#L107">107</a> <b><i>         * module gets removed entirely.</i></b>
<a name="L108" href="source/net/ipv4/tcp_cong.c#L108">108</a> <b><i>         *</i></b>
<a name="L109" href="source/net/ipv4/tcp_cong.c#L109">109</a> <b><i>         * A try_module_get() should fail by now as our module is</i></b>
<a name="L110" href="source/net/ipv4/tcp_cong.c#L110">110</a> <b><i>         * in "going" state since no refs are held anymore and</i></b>
<a name="L111" href="source/net/ipv4/tcp_cong.c#L111">111</a> <b><i>         * module_exit() handler being called.</i></b>
<a name="L112" href="source/net/ipv4/tcp_cong.c#L112">112</a> <b><i>         */</i></b>
<a name="L113" href="source/net/ipv4/tcp_cong.c#L113">113</a>         <a href="ident?i=synchronize_rcu">synchronize_rcu</a>();
<a name="L114" href="source/net/ipv4/tcp_cong.c#L114">114</a> }
<a name="L115" href="source/net/ipv4/tcp_cong.c#L115">115</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>);
<a name="L116" href="source/net/ipv4/tcp_cong.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/tcp_cong.c#L117">117</a> <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_ca_get_key_by_name">tcp_ca_get_key_by_name</a>(const char *<a href="ident?i=name">name</a>)
<a name="L118" href="source/net/ipv4/tcp_cong.c#L118">118</a> {
<a name="L119" href="source/net/ipv4/tcp_cong.c#L119">119</a>         const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L120" href="source/net/ipv4/tcp_cong.c#L120">120</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=key">key</a>;
<a name="L121" href="source/net/ipv4/tcp_cong.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_cong.c#L122">122</a>         <a href="ident?i=might_sleep">might_sleep</a>();
<a name="L123" href="source/net/ipv4/tcp_cong.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/tcp_cong.c#L124">124</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L125" href="source/net/ipv4/tcp_cong.c#L125">125</a>         <a href="ident?i=ca">ca</a> = <a href="ident?i=__tcp_ca_find_autoload">__tcp_ca_find_autoload</a>(<a href="ident?i=name">name</a>);
<a name="L126" href="source/net/ipv4/tcp_cong.c#L126">126</a>         <a href="ident?i=key">key</a> = <a href="ident?i=ca">ca</a> ? <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=key">key</a> : <a href="ident?i=TCP_CA_UNSPEC">TCP_CA_UNSPEC</a>;
<a name="L127" href="source/net/ipv4/tcp_cong.c#L127">127</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L128" href="source/net/ipv4/tcp_cong.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/tcp_cong.c#L129">129</a>         return <a href="ident?i=key">key</a>;
<a name="L130" href="source/net/ipv4/tcp_cong.c#L130">130</a> }
<a name="L131" href="source/net/ipv4/tcp_cong.c#L131">131</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_ca_get_key_by_name">tcp_ca_get_key_by_name</a>);
<a name="L132" href="source/net/ipv4/tcp_cong.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/tcp_cong.c#L133">133</a> char *<a href="ident?i=tcp_ca_get_name_by_key">tcp_ca_get_name_by_key</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=key">key</a>, char *<a href="ident?i=buffer">buffer</a>)
<a name="L134" href="source/net/ipv4/tcp_cong.c#L134">134</a> {
<a name="L135" href="source/net/ipv4/tcp_cong.c#L135">135</a>         const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L136" href="source/net/ipv4/tcp_cong.c#L136">136</a>         char *<a href="ident?i=ret">ret</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L137" href="source/net/ipv4/tcp_cong.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/tcp_cong.c#L138">138</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L139" href="source/net/ipv4/tcp_cong.c#L139">139</a>         <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find_key">tcp_ca_find_key</a>(<a href="ident?i=key">key</a>);
<a name="L140" href="source/net/ipv4/tcp_cong.c#L140">140</a>         if (<a href="ident?i=ca">ca</a>)
<a name="L141" href="source/net/ipv4/tcp_cong.c#L141">141</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=strncpy">strncpy</a>(<a href="ident?i=buffer">buffer</a>, <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L142" href="source/net/ipv4/tcp_cong.c#L142">142</a>                               <a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>);
<a name="L143" href="source/net/ipv4/tcp_cong.c#L143">143</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L144" href="source/net/ipv4/tcp_cong.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/tcp_cong.c#L145">145</a>         return <a href="ident?i=ret">ret</a>;
<a name="L146" href="source/net/ipv4/tcp_cong.c#L146">146</a> }
<a name="L147" href="source/net/ipv4/tcp_cong.c#L147">147</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_ca_get_name_by_key">tcp_ca_get_name_by_key</a>);
<a name="L148" href="source/net/ipv4/tcp_cong.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/tcp_cong.c#L149">149</a> <b><i>/* Assign choice of congestion control. */</i></b>
<a name="L150" href="source/net/ipv4/tcp_cong.c#L150">150</a> void <a href="ident?i=tcp_assign_congestion_control">tcp_assign_congestion_control</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L151" href="source/net/ipv4/tcp_cong.c#L151">151</a> {
<a name="L152" href="source/net/ipv4/tcp_cong.c#L152">152</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L153" href="source/net/ipv4/tcp_cong.c#L153">153</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L154" href="source/net/ipv4/tcp_cong.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tcp_cong.c#L155">155</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L156" href="source/net/ipv4/tcp_cong.c#L156">156</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=ca">ca</a>, &amp;tcp_cong_list, <a href="ident?i=list">list</a>) {
<a name="L157" href="source/net/ipv4/tcp_cong.c#L157">157</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=try_module_get">try_module_get</a>(<a href="ident?i=ca">ca</a>-&gt;owner))) {
<a name="L158" href="source/net/ipv4/tcp_cong.c#L158">158</a>                         icsk-&gt;icsk_ca_ops = <a href="ident?i=ca">ca</a>;
<a name="L159" href="source/net/ipv4/tcp_cong.c#L159">159</a>                         goto <a href="ident?i=out">out</a>;
<a name="L160" href="source/net/ipv4/tcp_cong.c#L160">160</a>                 }
<a name="L161" href="source/net/ipv4/tcp_cong.c#L161">161</a>                 <b><i>/* Fallback to next available. The last really</i></b>
<a name="L162" href="source/net/ipv4/tcp_cong.c#L162">162</a> <b><i>                 * guaranteed fallback is Reno from this list.</i></b>
<a name="L163" href="source/net/ipv4/tcp_cong.c#L163">163</a> <b><i>                 */</i></b>
<a name="L164" href="source/net/ipv4/tcp_cong.c#L164">164</a>         }
<a name="L165" href="source/net/ipv4/tcp_cong.c#L165">165</a> <a href="ident?i=out">out</a>:
<a name="L166" href="source/net/ipv4/tcp_cong.c#L166">166</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L167" href="source/net/ipv4/tcp_cong.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/tcp_cong.c#L168">168</a>         <b><i>/* Clear out private data before diag gets it and</i></b>
<a name="L169" href="source/net/ipv4/tcp_cong.c#L169">169</a> <b><i>         * the ca has not been initialized.</i></b>
<a name="L170" href="source/net/ipv4/tcp_cong.c#L170">170</a> <b><i>         */</i></b>
<a name="L171" href="source/net/ipv4/tcp_cong.c#L171">171</a>         if (<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=get_info">get_info</a>)
<a name="L172" href="source/net/ipv4/tcp_cong.c#L172">172</a>                 <a href="ident?i=memset">memset</a>(icsk-&gt;icsk_ca_priv, 0, sizeof(icsk-&gt;icsk_ca_priv));
<a name="L173" href="source/net/ipv4/tcp_cong.c#L173">173</a> }
<a name="L174" href="source/net/ipv4/tcp_cong.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/tcp_cong.c#L175">175</a> void <a href="ident?i=tcp_init_congestion_control">tcp_init_congestion_control</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L176" href="source/net/ipv4/tcp_cong.c#L176">176</a> {
<a name="L177" href="source/net/ipv4/tcp_cong.c#L177">177</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L178" href="source/net/ipv4/tcp_cong.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/tcp_cong.c#L179">179</a>         if (icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=init">init</a>)
<a name="L180" href="source/net/ipv4/tcp_cong.c#L180">180</a>                 icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=init">init</a>(sk);
<a name="L181" href="source/net/ipv4/tcp_cong.c#L181">181</a> }
<a name="L182" href="source/net/ipv4/tcp_cong.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_cong.c#L183">183</a> static void <a href="ident?i=tcp_reinit_congestion_control">tcp_reinit_congestion_control</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L184" href="source/net/ipv4/tcp_cong.c#L184">184</a>                                           const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>)
<a name="L185" href="source/net/ipv4/tcp_cong.c#L185">185</a> {
<a name="L186" href="source/net/ipv4/tcp_cong.c#L186">186</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L187" href="source/net/ipv4/tcp_cong.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/tcp_cong.c#L188">188</a>         <a href="ident?i=tcp_cleanup_congestion_control">tcp_cleanup_congestion_control</a>(sk);
<a name="L189" href="source/net/ipv4/tcp_cong.c#L189">189</a>         icsk-&gt;icsk_ca_ops = <a href="ident?i=ca">ca</a>;
<a name="L190" href="source/net/ipv4/tcp_cong.c#L190">190</a>         icsk-&gt;icsk_ca_setsockopt = 1;
<a name="L191" href="source/net/ipv4/tcp_cong.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/tcp_cong.c#L192">192</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE &amp;&amp; icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=init">init</a>)
<a name="L193" href="source/net/ipv4/tcp_cong.c#L193">193</a>                 icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=init">init</a>(sk);
<a name="L194" href="source/net/ipv4/tcp_cong.c#L194">194</a> }
<a name="L195" href="source/net/ipv4/tcp_cong.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/tcp_cong.c#L196">196</a> <b><i>/* Manage refcounts on socket close. */</i></b>
<a name="L197" href="source/net/ipv4/tcp_cong.c#L197">197</a> void <a href="ident?i=tcp_cleanup_congestion_control">tcp_cleanup_congestion_control</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L198" href="source/net/ipv4/tcp_cong.c#L198">198</a> {
<a name="L199" href="source/net/ipv4/tcp_cong.c#L199">199</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L200" href="source/net/ipv4/tcp_cong.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/tcp_cong.c#L201">201</a>         if (icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=release">release</a>)
<a name="L202" href="source/net/ipv4/tcp_cong.c#L202">202</a>                 icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=release">release</a>(sk);
<a name="L203" href="source/net/ipv4/tcp_cong.c#L203">203</a>         <a href="ident?i=module_put">module_put</a>(icsk-&gt;icsk_ca_ops-&gt;owner);
<a name="L204" href="source/net/ipv4/tcp_cong.c#L204">204</a> }
<a name="L205" href="source/net/ipv4/tcp_cong.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/tcp_cong.c#L206">206</a> <b><i>/* Used by sysctl to change default congestion control */</i></b>
<a name="L207" href="source/net/ipv4/tcp_cong.c#L207">207</a> int <a href="ident?i=tcp_set_default_congestion_control">tcp_set_default_congestion_control</a>(const char *<a href="ident?i=name">name</a>)
<a name="L208" href="source/net/ipv4/tcp_cong.c#L208">208</a> {
<a name="L209" href="source/net/ipv4/tcp_cong.c#L209">209</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L210" href="source/net/ipv4/tcp_cong.c#L210">210</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L211" href="source/net/ipv4/tcp_cong.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/tcp_cong.c#L212">212</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;tcp_cong_list_lock);
<a name="L213" href="source/net/ipv4/tcp_cong.c#L213">213</a>         <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find">tcp_ca_find</a>(<a href="ident?i=name">name</a>);
<a name="L214" href="source/net/ipv4/tcp_cong.c#L214">214</a> #ifdef CONFIG_MODULES
<a name="L215" href="source/net/ipv4/tcp_cong.c#L215">215</a>         if (!<a href="ident?i=ca">ca</a> &amp;&amp; <a href="ident?i=capable">capable</a>(<a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>)) {
<a name="L216" href="source/net/ipv4/tcp_cong.c#L216">216</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;tcp_cong_list_lock);
<a name="L217" href="source/net/ipv4/tcp_cong.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/tcp_cong.c#L218">218</a>                 <a href="ident?i=request_module">request_module</a>(<i>"tcp_%s"</i>, <a href="ident?i=name">name</a>);
<a name="L219" href="source/net/ipv4/tcp_cong.c#L219">219</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;tcp_cong_list_lock);
<a name="L220" href="source/net/ipv4/tcp_cong.c#L220">220</a>                 <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find">tcp_ca_find</a>(<a href="ident?i=name">name</a>);
<a name="L221" href="source/net/ipv4/tcp_cong.c#L221">221</a>         }
<a name="L222" href="source/net/ipv4/tcp_cong.c#L222">222</a> #endif
<a name="L223" href="source/net/ipv4/tcp_cong.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/tcp_cong.c#L224">224</a>         if (<a href="ident?i=ca">ca</a>) {
<a name="L225" href="source/net/ipv4/tcp_cong.c#L225">225</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=TCP_CONG_NON_RESTRICTED">TCP_CONG_NON_RESTRICTED</a>;   <b><i>/* default is always allowed */</i></b>
<a name="L226" href="source/net/ipv4/tcp_cong.c#L226">226</a>                 <a href="ident?i=list_move">list_move</a>(&amp;<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=list">list</a>, &amp;tcp_cong_list);
<a name="L227" href="source/net/ipv4/tcp_cong.c#L227">227</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L228" href="source/net/ipv4/tcp_cong.c#L228">228</a>         }
<a name="L229" href="source/net/ipv4/tcp_cong.c#L229">229</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;tcp_cong_list_lock);
<a name="L230" href="source/net/ipv4/tcp_cong.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/tcp_cong.c#L231">231</a>         return <a href="ident?i=ret">ret</a>;
<a name="L232" href="source/net/ipv4/tcp_cong.c#L232">232</a> }
<a name="L233" href="source/net/ipv4/tcp_cong.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_cong.c#L234">234</a> <b><i>/* Set default value from kernel configuration at bootup */</i></b>
<a name="L235" href="source/net/ipv4/tcp_cong.c#L235">235</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_congestion_default">tcp_congestion_default</a>(void)
<a name="L236" href="source/net/ipv4/tcp_cong.c#L236">236</a> {
<a name="L237" href="source/net/ipv4/tcp_cong.c#L237">237</a>         return <a href="ident?i=tcp_set_default_congestion_control">tcp_set_default_congestion_control</a>(CONFIG_DEFAULT_TCP_CONG);
<a name="L238" href="source/net/ipv4/tcp_cong.c#L238">238</a> }
<a name="L239" href="source/net/ipv4/tcp_cong.c#L239">239</a> <a href="ident?i=late_initcall">late_initcall</a>(<a href="ident?i=tcp_congestion_default">tcp_congestion_default</a>);
<a name="L240" href="source/net/ipv4/tcp_cong.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/tcp_cong.c#L241">241</a> <b><i>/* Build string with list of available congestion control values */</i></b>
<a name="L242" href="source/net/ipv4/tcp_cong.c#L242">242</a> void <a href="ident?i=tcp_get_available_congestion_control">tcp_get_available_congestion_control</a>(char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> maxlen)
<a name="L243" href="source/net/ipv4/tcp_cong.c#L243">243</a> {
<a name="L244" href="source/net/ipv4/tcp_cong.c#L244">244</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L245" href="source/net/ipv4/tcp_cong.c#L245">245</a>         <a href="ident?i=size_t">size_t</a> offs = 0;
<a name="L246" href="source/net/ipv4/tcp_cong.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/tcp_cong.c#L247">247</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L248" href="source/net/ipv4/tcp_cong.c#L248">248</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=ca">ca</a>, &amp;tcp_cong_list, <a href="ident?i=list">list</a>) {
<a name="L249" href="source/net/ipv4/tcp_cong.c#L249">249</a>                 offs += <a href="ident?i=snprintf">snprintf</a>(<a href="ident?i=buf">buf</a> + offs, maxlen - offs,
<a name="L250" href="source/net/ipv4/tcp_cong.c#L250">250</a>                                  <i>"%s%s"</i>,
<a name="L251" href="source/net/ipv4/tcp_cong.c#L251">251</a>                                  offs == 0 ? <i>""</i> : <i>" "</i>, <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L252" href="source/net/ipv4/tcp_cong.c#L252">252</a>         }
<a name="L253" href="source/net/ipv4/tcp_cong.c#L253">253</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L254" href="source/net/ipv4/tcp_cong.c#L254">254</a> }
<a name="L255" href="source/net/ipv4/tcp_cong.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/tcp_cong.c#L256">256</a> <b><i>/* Get current default congestion control */</i></b>
<a name="L257" href="source/net/ipv4/tcp_cong.c#L257">257</a> void <a href="ident?i=tcp_get_default_congestion_control">tcp_get_default_congestion_control</a>(char *<a href="ident?i=name">name</a>)
<a name="L258" href="source/net/ipv4/tcp_cong.c#L258">258</a> {
<a name="L259" href="source/net/ipv4/tcp_cong.c#L259">259</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L260" href="source/net/ipv4/tcp_cong.c#L260">260</a>         <b><i>/* We will always have reno... */</i></b>
<a name="L261" href="source/net/ipv4/tcp_cong.c#L261">261</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=list_empty">list_empty</a>(&amp;tcp_cong_list));
<a name="L262" href="source/net/ipv4/tcp_cong.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/tcp_cong.c#L263">263</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L264" href="source/net/ipv4/tcp_cong.c#L264">264</a>         <a href="ident?i=ca">ca</a> = <a href="ident?i=list_entry">list_entry</a>(tcp_cong_list.<a href="ident?i=next">next</a>, struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a>, <a href="ident?i=list">list</a>);
<a name="L265" href="source/net/ipv4/tcp_cong.c#L265">265</a>         <a href="ident?i=strncpy">strncpy</a>(<a href="ident?i=name">name</a>, <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>);
<a name="L266" href="source/net/ipv4/tcp_cong.c#L266">266</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L267" href="source/net/ipv4/tcp_cong.c#L267">267</a> }
<a name="L268" href="source/net/ipv4/tcp_cong.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/tcp_cong.c#L269">269</a> <b><i>/* Built list of non-restricted congestion control values */</i></b>
<a name="L270" href="source/net/ipv4/tcp_cong.c#L270">270</a> void <a href="ident?i=tcp_get_allowed_congestion_control">tcp_get_allowed_congestion_control</a>(char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> maxlen)
<a name="L271" href="source/net/ipv4/tcp_cong.c#L271">271</a> {
<a name="L272" href="source/net/ipv4/tcp_cong.c#L272">272</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L273" href="source/net/ipv4/tcp_cong.c#L273">273</a>         <a href="ident?i=size_t">size_t</a> offs = 0;
<a name="L274" href="source/net/ipv4/tcp_cong.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/tcp_cong.c#L275">275</a>         *<a href="ident?i=buf">buf</a> = <i>'\0'</i>;
<a name="L276" href="source/net/ipv4/tcp_cong.c#L276">276</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L277" href="source/net/ipv4/tcp_cong.c#L277">277</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=ca">ca</a>, &amp;tcp_cong_list, <a href="ident?i=list">list</a>) {
<a name="L278" href="source/net/ipv4/tcp_cong.c#L278">278</a>                 if (!(<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TCP_CONG_NON_RESTRICTED">TCP_CONG_NON_RESTRICTED</a>))
<a name="L279" href="source/net/ipv4/tcp_cong.c#L279">279</a>                         continue;
<a name="L280" href="source/net/ipv4/tcp_cong.c#L280">280</a>                 offs += <a href="ident?i=snprintf">snprintf</a>(<a href="ident?i=buf">buf</a> + offs, maxlen - offs,
<a name="L281" href="source/net/ipv4/tcp_cong.c#L281">281</a>                                  <i>"%s%s"</i>,
<a name="L282" href="source/net/ipv4/tcp_cong.c#L282">282</a>                                  offs == 0 ? <i>""</i> : <i>" "</i>, <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L283" href="source/net/ipv4/tcp_cong.c#L283">283</a>         }
<a name="L284" href="source/net/ipv4/tcp_cong.c#L284">284</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L285" href="source/net/ipv4/tcp_cong.c#L285">285</a> }
<a name="L286" href="source/net/ipv4/tcp_cong.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/tcp_cong.c#L287">287</a> <b><i>/* Change list of non-restricted congestion control */</i></b>
<a name="L288" href="source/net/ipv4/tcp_cong.c#L288">288</a> int <a href="ident?i=tcp_set_allowed_congestion_control">tcp_set_allowed_congestion_control</a>(char *<a href="ident?i=val">val</a>)
<a name="L289" href="source/net/ipv4/tcp_cong.c#L289">289</a> {
<a name="L290" href="source/net/ipv4/tcp_cong.c#L290">290</a>         struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L291" href="source/net/ipv4/tcp_cong.c#L291">291</a>         char *saved_clone, *clone, *<a href="ident?i=name">name</a>;
<a name="L292" href="source/net/ipv4/tcp_cong.c#L292">292</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L293" href="source/net/ipv4/tcp_cong.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/tcp_cong.c#L294">294</a>         saved_clone = clone = <a href="ident?i=kstrdup">kstrdup</a>(<a href="ident?i=val">val</a>, <a href="ident?i=GFP_USER">GFP_USER</a>);
<a name="L295" href="source/net/ipv4/tcp_cong.c#L295">295</a>         if (!clone)
<a name="L296" href="source/net/ipv4/tcp_cong.c#L296">296</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L297" href="source/net/ipv4/tcp_cong.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/tcp_cong.c#L298">298</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;tcp_cong_list_lock);
<a name="L299" href="source/net/ipv4/tcp_cong.c#L299">299</a>         <b><i>/* pass 1 check for bad entries */</i></b>
<a name="L300" href="source/net/ipv4/tcp_cong.c#L300">300</a>         while ((<a href="ident?i=name">name</a> = <a href="ident?i=strsep">strsep</a>(&amp;clone, <i>" "</i>)) &amp;&amp; *<a href="ident?i=name">name</a>) {
<a name="L301" href="source/net/ipv4/tcp_cong.c#L301">301</a>                 <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find">tcp_ca_find</a>(<a href="ident?i=name">name</a>);
<a name="L302" href="source/net/ipv4/tcp_cong.c#L302">302</a>                 if (!<a href="ident?i=ca">ca</a>) {
<a name="L303" href="source/net/ipv4/tcp_cong.c#L303">303</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L304" href="source/net/ipv4/tcp_cong.c#L304">304</a>                         goto <a href="ident?i=out">out</a>;
<a name="L305" href="source/net/ipv4/tcp_cong.c#L305">305</a>                 }
<a name="L306" href="source/net/ipv4/tcp_cong.c#L306">306</a>         }
<a name="L307" href="source/net/ipv4/tcp_cong.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/tcp_cong.c#L308">308</a>         <b><i>/* pass 2 clear old values */</i></b>
<a name="L309" href="source/net/ipv4/tcp_cong.c#L309">309</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=ca">ca</a>, &amp;tcp_cong_list, <a href="ident?i=list">list</a>)
<a name="L310" href="source/net/ipv4/tcp_cong.c#L310">310</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=flags">flags</a> &amp;= ~TCP_CONG_NON_RESTRICTED;
<a name="L311" href="source/net/ipv4/tcp_cong.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/tcp_cong.c#L312">312</a>         <b><i>/* pass 3 mark as allowed */</i></b>
<a name="L313" href="source/net/ipv4/tcp_cong.c#L313">313</a>         while ((<a href="ident?i=name">name</a> = <a href="ident?i=strsep">strsep</a>(&amp;<a href="ident?i=val">val</a>, <i>" "</i>)) &amp;&amp; *<a href="ident?i=name">name</a>) {
<a name="L314" href="source/net/ipv4/tcp_cong.c#L314">314</a>                 <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find">tcp_ca_find</a>(<a href="ident?i=name">name</a>);
<a name="L315" href="source/net/ipv4/tcp_cong.c#L315">315</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=ca">ca</a>);
<a name="L316" href="source/net/ipv4/tcp_cong.c#L316">316</a>                 if (<a href="ident?i=ca">ca</a>)
<a name="L317" href="source/net/ipv4/tcp_cong.c#L317">317</a>                         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=TCP_CONG_NON_RESTRICTED">TCP_CONG_NON_RESTRICTED</a>;
<a name="L318" href="source/net/ipv4/tcp_cong.c#L318">318</a>         }
<a name="L319" href="source/net/ipv4/tcp_cong.c#L319">319</a> <a href="ident?i=out">out</a>:
<a name="L320" href="source/net/ipv4/tcp_cong.c#L320">320</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;tcp_cong_list_lock);
<a name="L321" href="source/net/ipv4/tcp_cong.c#L321">321</a>         <a href="ident?i=kfree">kfree</a>(saved_clone);
<a name="L322" href="source/net/ipv4/tcp_cong.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/tcp_cong.c#L323">323</a>         return <a href="ident?i=ret">ret</a>;
<a name="L324" href="source/net/ipv4/tcp_cong.c#L324">324</a> }
<a name="L325" href="source/net/ipv4/tcp_cong.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/tcp_cong.c#L326">326</a> <b><i>/* Change congestion control for socket */</i></b>
<a name="L327" href="source/net/ipv4/tcp_cong.c#L327">327</a> int <a href="ident?i=tcp_set_congestion_control">tcp_set_congestion_control</a>(struct <a href="ident?i=sock">sock</a> *sk, const char *<a href="ident?i=name">name</a>)
<a name="L328" href="source/net/ipv4/tcp_cong.c#L328">328</a> {
<a name="L329" href="source/net/ipv4/tcp_cong.c#L329">329</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L330" href="source/net/ipv4/tcp_cong.c#L330">330</a>         const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L331" href="source/net/ipv4/tcp_cong.c#L331">331</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L332" href="source/net/ipv4/tcp_cong.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/tcp_cong.c#L333">333</a>         if (icsk-&gt;icsk_ca_dst_locked)
<a name="L334" href="source/net/ipv4/tcp_cong.c#L334">334</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L335" href="source/net/ipv4/tcp_cong.c#L335">335</a> 
<a name="L336" href="source/net/ipv4/tcp_cong.c#L336">336</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L337" href="source/net/ipv4/tcp_cong.c#L337">337</a>         <a href="ident?i=ca">ca</a> = <a href="ident?i=__tcp_ca_find_autoload">__tcp_ca_find_autoload</a>(<a href="ident?i=name">name</a>);
<a name="L338" href="source/net/ipv4/tcp_cong.c#L338">338</a>         <b><i>/* No change asking for existing value */</i></b>
<a name="L339" href="source/net/ipv4/tcp_cong.c#L339">339</a>         if (<a href="ident?i=ca">ca</a> == icsk-&gt;icsk_ca_ops) {
<a name="L340" href="source/net/ipv4/tcp_cong.c#L340">340</a>                 icsk-&gt;icsk_ca_setsockopt = 1;
<a name="L341" href="source/net/ipv4/tcp_cong.c#L341">341</a>                 goto <a href="ident?i=out">out</a>;
<a name="L342" href="source/net/ipv4/tcp_cong.c#L342">342</a>         }
<a name="L343" href="source/net/ipv4/tcp_cong.c#L343">343</a>         if (!<a href="ident?i=ca">ca</a>)
<a name="L344" href="source/net/ipv4/tcp_cong.c#L344">344</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L345" href="source/net/ipv4/tcp_cong.c#L345">345</a>         else if (!((<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TCP_CONG_NON_RESTRICTED">TCP_CONG_NON_RESTRICTED</a>) ||
<a name="L346" href="source/net/ipv4/tcp_cong.c#L346">346</a>                    <a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>)))
<a name="L347" href="source/net/ipv4/tcp_cong.c#L347">347</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L348" href="source/net/ipv4/tcp_cong.c#L348">348</a>         else if (!<a href="ident?i=try_module_get">try_module_get</a>(<a href="ident?i=ca">ca</a>-&gt;owner))
<a name="L349" href="source/net/ipv4/tcp_cong.c#L349">349</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EBUSY">EBUSY</a>;
<a name="L350" href="source/net/ipv4/tcp_cong.c#L350">350</a>         else
<a name="L351" href="source/net/ipv4/tcp_cong.c#L351">351</a>                 <a href="ident?i=tcp_reinit_congestion_control">tcp_reinit_congestion_control</a>(sk, <a href="ident?i=ca">ca</a>);
<a name="L352" href="source/net/ipv4/tcp_cong.c#L352">352</a>  <a href="ident?i=out">out</a>:
<a name="L353" href="source/net/ipv4/tcp_cong.c#L353">353</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L354" href="source/net/ipv4/tcp_cong.c#L354">354</a>         return <a href="ident?i=err">err</a>;
<a name="L355" href="source/net/ipv4/tcp_cong.c#L355">355</a> }
<a name="L356" href="source/net/ipv4/tcp_cong.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/tcp_cong.c#L357">357</a> <b><i>/* Slow start is used when congestion window is no greater than the slow start</i></b>
<a name="L358" href="source/net/ipv4/tcp_cong.c#L358">358</a> <b><i> * threshold. We base on RFC2581 and also handle stretch ACKs properly.</i></b>
<a name="L359" href="source/net/ipv4/tcp_cong.c#L359">359</a> <b><i> * We do not implement RFC3465 Appropriate Byte Counting (ABC) per se but</i></b>
<a name="L360" href="source/net/ipv4/tcp_cong.c#L360">360</a> <b><i> * something better;) a packet is only considered (s)acked in its entirety to</i></b>
<a name="L361" href="source/net/ipv4/tcp_cong.c#L361">361</a> <b><i> * defend the ACK attacks described in the RFC. Slow start processes a stretch</i></b>
<a name="L362" href="source/net/ipv4/tcp_cong.c#L362">362</a> <b><i> * ACK of degree N as if N acks of degree 1 are received back to back except</i></b>
<a name="L363" href="source/net/ipv4/tcp_cong.c#L363">363</a> <b><i> * ABC caps N to 2. Slow start exits when cwnd grows over ssthresh and</i></b>
<a name="L364" href="source/net/ipv4/tcp_cong.c#L364">364</a> <b><i> * returns the leftover acks to adjust cwnd in congestion avoidance mode.</i></b>
<a name="L365" href="source/net/ipv4/tcp_cong.c#L365">365</a> <b><i> */</i></b>
<a name="L366" href="source/net/ipv4/tcp_cong.c#L366">366</a> <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> acked)
<a name="L367" href="source/net/ipv4/tcp_cong.c#L367">367</a> {
<a name="L368" href="source/net/ipv4/tcp_cong.c#L368">368</a>         <a href="ident?i=u32">u32</a> cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd + acked;
<a name="L369" href="source/net/ipv4/tcp_cong.c#L369">369</a> 
<a name="L370" href="source/net/ipv4/tcp_cong.c#L370">370</a>         if (cwnd &gt; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
<a name="L371" href="source/net/ipv4/tcp_cong.c#L371">371</a>                 cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh + 1;
<a name="L372" href="source/net/ipv4/tcp_cong.c#L372">372</a>         acked -= cwnd - <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L373" href="source/net/ipv4/tcp_cong.c#L373">373</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min">min</a>(cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp);
<a name="L374" href="source/net/ipv4/tcp_cong.c#L374">374</a> 
<a name="L375" href="source/net/ipv4/tcp_cong.c#L375">375</a>         return acked;
<a name="L376" href="source/net/ipv4/tcp_cong.c#L376">376</a> }
<a name="L377" href="source/net/ipv4/tcp_cong.c#L377">377</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_slow_start">tcp_slow_start</a>);
<a name="L378" href="source/net/ipv4/tcp_cong.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/tcp_cong.c#L379">379</a> <b><i>/* In theory this is tp-&gt;snd_cwnd += 1 / tp-&gt;snd_cwnd (or alternative w),</i></b>
<a name="L380" href="source/net/ipv4/tcp_cong.c#L380">380</a> <b><i> * for every packet that was ACKed.</i></b>
<a name="L381" href="source/net/ipv4/tcp_cong.c#L381">381</a> <b><i> */</i></b>
<a name="L382" href="source/net/ipv4/tcp_cong.c#L382">382</a> void <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=w">w</a>, <a href="ident?i=u32">u32</a> acked)
<a name="L383" href="source/net/ipv4/tcp_cong.c#L383">383</a> {
<a name="L384" href="source/net/ipv4/tcp_cong.c#L384">384</a>         <b><i>/* If credits accumulated at a higher w, apply them gently now. */</i></b>
<a name="L385" href="source/net/ipv4/tcp_cong.c#L385">385</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt &gt;= <a href="ident?i=w">w</a>) {
<a name="L386" href="source/net/ipv4/tcp_cong.c#L386">386</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L387" href="source/net/ipv4/tcp_cong.c#L387">387</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L388" href="source/net/ipv4/tcp_cong.c#L388">388</a>         }
<a name="L389" href="source/net/ipv4/tcp_cong.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/tcp_cong.c#L390">390</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt += acked;
<a name="L391" href="source/net/ipv4/tcp_cong.c#L391">391</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt &gt;= <a href="ident?i=w">w</a>) {
<a name="L392" href="source/net/ipv4/tcp_cong.c#L392">392</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a> = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt / <a href="ident?i=w">w</a>;
<a name="L393" href="source/net/ipv4/tcp_cong.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/tcp_cong.c#L394">394</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt -= <a href="ident?i=delta">delta</a> * <a href="ident?i=w">w</a>;
<a name="L395" href="source/net/ipv4/tcp_cong.c#L395">395</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd += <a href="ident?i=delta">delta</a>;
<a name="L396" href="source/net/ipv4/tcp_cong.c#L396">396</a>         }
<a name="L397" href="source/net/ipv4/tcp_cong.c#L397">397</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp);
<a name="L398" href="source/net/ipv4/tcp_cong.c#L398">398</a> }
<a name="L399" href="source/net/ipv4/tcp_cong.c#L399">399</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>);
<a name="L400" href="source/net/ipv4/tcp_cong.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/tcp_cong.c#L401">401</a> <b><i>/*</i></b>
<a name="L402" href="source/net/ipv4/tcp_cong.c#L402">402</a> <b><i> * TCP Reno congestion control</i></b>
<a name="L403" href="source/net/ipv4/tcp_cong.c#L403">403</a> <b><i> * This is special case used for fallback as well.</i></b>
<a name="L404" href="source/net/ipv4/tcp_cong.c#L404">404</a> <b><i> */</i></b>
<a name="L405" href="source/net/ipv4/tcp_cong.c#L405">405</a> <b><i>/* This is Jacobson's slow start and congestion avoidance.</i></b>
<a name="L406" href="source/net/ipv4/tcp_cong.c#L406">406</a> <b><i> * SIGCOMM '88, p. 328.</i></b>
<a name="L407" href="source/net/ipv4/tcp_cong.c#L407">407</a> <b><i> */</i></b>
<a name="L408" href="source/net/ipv4/tcp_cong.c#L408">408</a> void <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L409" href="source/net/ipv4/tcp_cong.c#L409">409</a> {
<a name="L410" href="source/net/ipv4/tcp_cong.c#L410">410</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L411" href="source/net/ipv4/tcp_cong.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/tcp_cong.c#L412">412</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L413" href="source/net/ipv4/tcp_cong.c#L413">413</a>                 return;
<a name="L414" href="source/net/ipv4/tcp_cong.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/tcp_cong.c#L415">415</a>         <b><i>/* In "safe" area, increase. */</i></b>
<a name="L416" href="source/net/ipv4/tcp_cong.c#L416">416</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L417" href="source/net/ipv4/tcp_cong.c#L417">417</a>                 acked = <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L418" href="source/net/ipv4/tcp_cong.c#L418">418</a>                 if (!acked)
<a name="L419" href="source/net/ipv4/tcp_cong.c#L419">419</a>                         return;
<a name="L420" href="source/net/ipv4/tcp_cong.c#L420">420</a>         }
<a name="L421" href="source/net/ipv4/tcp_cong.c#L421">421</a>         <b><i>/* In dangerous area, increase slowly. */</i></b>
<a name="L422" href="source/net/ipv4/tcp_cong.c#L422">422</a>         <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, acked);
<a name="L423" href="source/net/ipv4/tcp_cong.c#L423">423</a> }
<a name="L424" href="source/net/ipv4/tcp_cong.c#L424">424</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>);
<a name="L425" href="source/net/ipv4/tcp_cong.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/tcp_cong.c#L426">426</a> <b><i>/* Slow start threshold is half the congestion window (min 2) */</i></b>
<a name="L427" href="source/net/ipv4/tcp_cong.c#L427">427</a> <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L428" href="source/net/ipv4/tcp_cong.c#L428">428</a> {
<a name="L429" href="source/net/ipv4/tcp_cong.c#L429">429</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L430" href="source/net/ipv4/tcp_cong.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/tcp_cong.c#L431">431</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1U, 2U);
<a name="L432" href="source/net/ipv4/tcp_cong.c#L432">432</a> }
<a name="L433" href="source/net/ipv4/tcp_cong.c#L433">433</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>);
<a name="L434" href="source/net/ipv4/tcp_cong.c#L434">434</a> 
<a name="L435" href="source/net/ipv4/tcp_cong.c#L435">435</a> struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=tcp_reno">tcp_reno</a> = {
<a name="L436" href="source/net/ipv4/tcp_cong.c#L436">436</a>         .<a href="ident?i=flags">flags</a>          = <a href="ident?i=TCP_CONG_NON_RESTRICTED">TCP_CONG_NON_RESTRICTED</a>,
<a name="L437" href="source/net/ipv4/tcp_cong.c#L437">437</a>         .<a href="ident?i=name">name</a>           = <i>"reno"</i>,
<a name="L438" href="source/net/ipv4/tcp_cong.c#L438">438</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L439" href="source/net/ipv4/tcp_cong.c#L439">439</a>         .ssthresh       = <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>,
<a name="L440" href="source/net/ipv4/tcp_cong.c#L440">440</a>         .cong_avoid     = <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>,
<a name="L441" href="source/net/ipv4/tcp_cong.c#L441">441</a> };
<a name="L442" href="source/net/ipv4/tcp_cong.c#L442">442</a> </pre></div><p>
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
