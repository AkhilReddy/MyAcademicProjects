<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tunnel4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tunnel4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tunnel4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tunnel4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tunnel4.c">tunnel4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tunnel4.c#L1">1</a> <b><i>/* tunnel4.c: Generic IP tunnel transformer.</i></b>
  <a name="L2" href="source/net/ipv4/tunnel4.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/tunnel4.c#L3">3</a> <b><i> * Copyright (C) 2003 David S. Miller (davem@redhat.com)</i></b>
  <a name="L4" href="source/net/ipv4/tunnel4.c#L4">4</a> <b><i> */</i></b>
  <a name="L5" href="source/net/ipv4/tunnel4.c#L5">5</a> 
  <a name="L6" href="source/net/ipv4/tunnel4.c#L6">6</a> #include &lt;linux/init.h&gt;
  <a name="L7" href="source/net/ipv4/tunnel4.c#L7">7</a> #include &lt;linux/module.h&gt;
  <a name="L8" href="source/net/ipv4/tunnel4.c#L8">8</a> #include &lt;linux/mutex.h&gt;
  <a name="L9" href="source/net/ipv4/tunnel4.c#L9">9</a> #include &lt;linux/netdevice.h&gt;
 <a name="L10" href="source/net/ipv4/tunnel4.c#L10">10</a> #include &lt;linux/skbuff.h&gt;
 <a name="L11" href="source/net/ipv4/tunnel4.c#L11">11</a> #include &lt;linux/slab.h&gt;
 <a name="L12" href="source/net/ipv4/tunnel4.c#L12">12</a> #include &lt;net/icmp.h&gt;
 <a name="L13" href="source/net/ipv4/tunnel4.c#L13">13</a> #include &lt;net/ip.h&gt;
 <a name="L14" href="source/net/ipv4/tunnel4.c#L14">14</a> #include &lt;net/protocol.h&gt;
 <a name="L15" href="source/net/ipv4/tunnel4.c#L15">15</a> #include &lt;net/xfrm.h&gt;
 <a name="L16" href="source/net/ipv4/tunnel4.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/tunnel4.c#L17">17</a> static struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> <a href="ident?i=__rcu">__rcu</a> *tunnel4_handlers <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L18" href="source/net/ipv4/tunnel4.c#L18">18</a> static struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> <a href="ident?i=__rcu">__rcu</a> *tunnel64_handlers <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L19" href="source/net/ipv4/tunnel4.c#L19">19</a> static <a href="ident?i=DEFINE_MUTEX">DEFINE_MUTEX</a>(tunnel4_mutex);
 <a name="L20" href="source/net/ipv4/tunnel4.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tunnel4.c#L21">21</a> static inline struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=fam_handlers">fam_handlers</a>(unsigned short <a href="ident?i=family">family</a>)
 <a name="L22" href="source/net/ipv4/tunnel4.c#L22">22</a> {
 <a name="L23" href="source/net/ipv4/tunnel4.c#L23">23</a>         return (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) ? &amp;tunnel4_handlers : &amp;tunnel64_handlers;
 <a name="L24" href="source/net/ipv4/tunnel4.c#L24">24</a> }
 <a name="L25" href="source/net/ipv4/tunnel4.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/tunnel4.c#L26">26</a> int <a href="ident?i=xfrm4_tunnel_register">xfrm4_tunnel_register</a>(struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=handler">handler</a>, unsigned short <a href="ident?i=family">family</a>)
 <a name="L27" href="source/net/ipv4/tunnel4.c#L27">27</a> {
 <a name="L28" href="source/net/ipv4/tunnel4.c#L28">28</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> <a href="ident?i=__rcu">__rcu</a> **pprev;
 <a name="L29" href="source/net/ipv4/tunnel4.c#L29">29</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=t">t</a>;
 <a name="L30" href="source/net/ipv4/tunnel4.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/tunnel4.c#L31">31</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
 <a name="L32" href="source/net/ipv4/tunnel4.c#L32">32</a>         int <a href="ident?i=priority">priority</a> = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=priority">priority</a>;
 <a name="L33" href="source/net/ipv4/tunnel4.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/tunnel4.c#L34">34</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;tunnel4_mutex);
 <a name="L35" href="source/net/ipv4/tunnel4.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tunnel4.c#L36">36</a>         for (pprev = <a href="ident?i=fam_handlers">fam_handlers</a>(<a href="ident?i=family">family</a>);
 <a name="L37" href="source/net/ipv4/tunnel4.c#L37">37</a>              (<a href="ident?i=t">t</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*pprev,
 <a name="L38" href="source/net/ipv4/tunnel4.c#L38">38</a>                         <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;tunnel4_mutex))) != <a href="ident?i=NULL">NULL</a>;
 <a name="L39" href="source/net/ipv4/tunnel4.c#L39">39</a>              pprev = &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=next">next</a>) {
 <a name="L40" href="source/net/ipv4/tunnel4.c#L40">40</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=priority">priority</a> &gt; <a href="ident?i=priority">priority</a>)
 <a name="L41" href="source/net/ipv4/tunnel4.c#L41">41</a>                         break;
 <a name="L42" href="source/net/ipv4/tunnel4.c#L42">42</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=priority">priority</a> == <a href="ident?i=priority">priority</a>)
 <a name="L43" href="source/net/ipv4/tunnel4.c#L43">43</a>                         goto <a href="ident?i=err">err</a>;
 <a name="L44" href="source/net/ipv4/tunnel4.c#L44">44</a>         }
 <a name="L45" href="source/net/ipv4/tunnel4.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/tunnel4.c#L46">46</a>         <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=next">next</a> = *pprev;
 <a name="L47" href="source/net/ipv4/tunnel4.c#L47">47</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(*pprev, <a href="ident?i=handler">handler</a>);
 <a name="L48" href="source/net/ipv4/tunnel4.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/tunnel4.c#L49">49</a>         <a href="ident?i=ret">ret</a> = 0;
 <a name="L50" href="source/net/ipv4/tunnel4.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/tunnel4.c#L51">51</a> <a href="ident?i=err">err</a>:
 <a name="L52" href="source/net/ipv4/tunnel4.c#L52">52</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;tunnel4_mutex);
 <a name="L53" href="source/net/ipv4/tunnel4.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tunnel4.c#L54">54</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L55" href="source/net/ipv4/tunnel4.c#L55">55</a> }
 <a name="L56" href="source/net/ipv4/tunnel4.c#L56">56</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_tunnel_register">xfrm4_tunnel_register</a>);
 <a name="L57" href="source/net/ipv4/tunnel4.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/tunnel4.c#L58">58</a> int <a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>(struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=handler">handler</a>, unsigned short <a href="ident?i=family">family</a>)
 <a name="L59" href="source/net/ipv4/tunnel4.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/tunnel4.c#L60">60</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> <a href="ident?i=__rcu">__rcu</a> **pprev;
 <a name="L61" href="source/net/ipv4/tunnel4.c#L61">61</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=t">t</a>;
 <a name="L62" href="source/net/ipv4/tunnel4.c#L62">62</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
 <a name="L63" href="source/net/ipv4/tunnel4.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/tunnel4.c#L64">64</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;tunnel4_mutex);
 <a name="L65" href="source/net/ipv4/tunnel4.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/tunnel4.c#L66">66</a>         for (pprev = <a href="ident?i=fam_handlers">fam_handlers</a>(<a href="ident?i=family">family</a>);
 <a name="L67" href="source/net/ipv4/tunnel4.c#L67">67</a>              (<a href="ident?i=t">t</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*pprev,
 <a name="L68" href="source/net/ipv4/tunnel4.c#L68">68</a>                         <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;tunnel4_mutex))) != <a href="ident?i=NULL">NULL</a>;
 <a name="L69" href="source/net/ipv4/tunnel4.c#L69">69</a>              pprev = &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=next">next</a>) {
 <a name="L70" href="source/net/ipv4/tunnel4.c#L70">70</a>                 if (<a href="ident?i=t">t</a> == <a href="ident?i=handler">handler</a>) {
 <a name="L71" href="source/net/ipv4/tunnel4.c#L71">71</a>                         *pprev = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=next">next</a>;
 <a name="L72" href="source/net/ipv4/tunnel4.c#L72">72</a>                         <a href="ident?i=ret">ret</a> = 0;
 <a name="L73" href="source/net/ipv4/tunnel4.c#L73">73</a>                         break;
 <a name="L74" href="source/net/ipv4/tunnel4.c#L74">74</a>                 }
 <a name="L75" href="source/net/ipv4/tunnel4.c#L75">75</a>         }
 <a name="L76" href="source/net/ipv4/tunnel4.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/tunnel4.c#L77">77</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;tunnel4_mutex);
 <a name="L78" href="source/net/ipv4/tunnel4.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/tunnel4.c#L79">79</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
 <a name="L80" href="source/net/ipv4/tunnel4.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tunnel4.c#L81">81</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L82" href="source/net/ipv4/tunnel4.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/tunnel4.c#L83">83</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>);
 <a name="L84" href="source/net/ipv4/tunnel4.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/tunnel4.c#L85">85</a> #define <a href="ident?i=for_each_tunnel_rcu">for_each_tunnel_rcu</a>(<a href="ident?i=head">head</a>, <a href="ident?i=handler">handler</a>)              \
 <a name="L86" href="source/net/ipv4/tunnel4.c#L86">86</a>         for (<a href="ident?i=handler">handler</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=head">head</a>);           \
 <a name="L87" href="source/net/ipv4/tunnel4.c#L87">87</a>              <a href="ident?i=handler">handler</a> != <a href="ident?i=NULL">NULL</a>;                           \
 <a name="L88" href="source/net/ipv4/tunnel4.c#L88">88</a>              <a href="ident?i=handler">handler</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=next">next</a>))  \
 <a name="L89" href="source/net/ipv4/tunnel4.c#L89">89</a>         
 <a name="L90" href="source/net/ipv4/tunnel4.c#L90">90</a> static int tunnel4_rcv(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L91" href="source/net/ipv4/tunnel4.c#L91">91</a> {
 <a name="L92" href="source/net/ipv4/tunnel4.c#L92">92</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=handler">handler</a>;
 <a name="L93" href="source/net/ipv4/tunnel4.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/tunnel4.c#L94">94</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
 <a name="L95" href="source/net/ipv4/tunnel4.c#L95">95</a>                 goto <a href="ident?i=drop">drop</a>;
 <a name="L96" href="source/net/ipv4/tunnel4.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/tunnel4.c#L97">97</a>         <a href="ident?i=for_each_tunnel_rcu">for_each_tunnel_rcu</a>(tunnel4_handlers, <a href="ident?i=handler">handler</a>)
 <a name="L98" href="source/net/ipv4/tunnel4.c#L98">98</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>))
 <a name="L99" href="source/net/ipv4/tunnel4.c#L99">99</a>                         return 0;
<a name="L100" href="source/net/ipv4/tunnel4.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/tunnel4.c#L101">101</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L102" href="source/net/ipv4/tunnel4.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/tunnel4.c#L103">103</a> <a href="ident?i=drop">drop</a>:
<a name="L104" href="source/net/ipv4/tunnel4.c#L104">104</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L105" href="source/net/ipv4/tunnel4.c#L105">105</a>         return 0;
<a name="L106" href="source/net/ipv4/tunnel4.c#L106">106</a> }
<a name="L107" href="source/net/ipv4/tunnel4.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/tunnel4.c#L108">108</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L109" href="source/net/ipv4/tunnel4.c#L109">109</a> static int <a href="ident?i=tunnel64_rcv">tunnel64_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L110" href="source/net/ipv4/tunnel4.c#L110">110</a> {
<a name="L111" href="source/net/ipv4/tunnel4.c#L111">111</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=handler">handler</a>;
<a name="L112" href="source/net/ipv4/tunnel4.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/tunnel4.c#L113">113</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=ipv6hdr">ipv6hdr</a>)))
<a name="L114" href="source/net/ipv4/tunnel4.c#L114">114</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L115" href="source/net/ipv4/tunnel4.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/tunnel4.c#L116">116</a>         <a href="ident?i=for_each_tunnel_rcu">for_each_tunnel_rcu</a>(tunnel64_handlers, <a href="ident?i=handler">handler</a>)
<a name="L117" href="source/net/ipv4/tunnel4.c#L117">117</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>))
<a name="L118" href="source/net/ipv4/tunnel4.c#L118">118</a>                         return 0;
<a name="L119" href="source/net/ipv4/tunnel4.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tunnel4.c#L120">120</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L121" href="source/net/ipv4/tunnel4.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tunnel4.c#L122">122</a> <a href="ident?i=drop">drop</a>:
<a name="L123" href="source/net/ipv4/tunnel4.c#L123">123</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L124" href="source/net/ipv4/tunnel4.c#L124">124</a>         return 0;
<a name="L125" href="source/net/ipv4/tunnel4.c#L125">125</a> }
<a name="L126" href="source/net/ipv4/tunnel4.c#L126">126</a> #endif
<a name="L127" href="source/net/ipv4/tunnel4.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/tunnel4.c#L128">128</a> static void <a href="ident?i=tunnel4_err">tunnel4_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L129" href="source/net/ipv4/tunnel4.c#L129">129</a> {
<a name="L130" href="source/net/ipv4/tunnel4.c#L130">130</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=handler">handler</a>;
<a name="L131" href="source/net/ipv4/tunnel4.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/tunnel4.c#L132">132</a>         <a href="ident?i=for_each_tunnel_rcu">for_each_tunnel_rcu</a>(tunnel4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L133" href="source/net/ipv4/tunnel4.c#L133">133</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>))
<a name="L134" href="source/net/ipv4/tunnel4.c#L134">134</a>                         break;
<a name="L135" href="source/net/ipv4/tunnel4.c#L135">135</a> }
<a name="L136" href="source/net/ipv4/tunnel4.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/tunnel4.c#L137">137</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L138" href="source/net/ipv4/tunnel4.c#L138">138</a> static void <a href="ident?i=tunnel64_err">tunnel64_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L139" href="source/net/ipv4/tunnel4.c#L139">139</a> {
<a name="L140" href="source/net/ipv4/tunnel4.c#L140">140</a>         struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> *<a href="ident?i=handler">handler</a>;
<a name="L141" href="source/net/ipv4/tunnel4.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/tunnel4.c#L142">142</a>         <a href="ident?i=for_each_tunnel_rcu">for_each_tunnel_rcu</a>(tunnel64_handlers, <a href="ident?i=handler">handler</a>)
<a name="L143" href="source/net/ipv4/tunnel4.c#L143">143</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>))
<a name="L144" href="source/net/ipv4/tunnel4.c#L144">144</a>                         break;
<a name="L145" href="source/net/ipv4/tunnel4.c#L145">145</a> }
<a name="L146" href="source/net/ipv4/tunnel4.c#L146">146</a> #endif
<a name="L147" href="source/net/ipv4/tunnel4.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/tunnel4.c#L148">148</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=tunnel4_protocol">tunnel4_protocol</a> = {
<a name="L149" href="source/net/ipv4/tunnel4.c#L149">149</a>         .<a href="ident?i=handler">handler</a>        =       tunnel4_rcv,
<a name="L150" href="source/net/ipv4/tunnel4.c#L150">150</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=tunnel4_err">tunnel4_err</a>,
<a name="L151" href="source/net/ipv4/tunnel4.c#L151">151</a>         .no_policy      =       1,
<a name="L152" href="source/net/ipv4/tunnel4.c#L152">152</a>         .netns_ok       =       1,
<a name="L153" href="source/net/ipv4/tunnel4.c#L153">153</a> };
<a name="L154" href="source/net/ipv4/tunnel4.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tunnel4.c#L155">155</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L156" href="source/net/ipv4/tunnel4.c#L156">156</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=tunnel64_protocol">tunnel64_protocol</a> = {
<a name="L157" href="source/net/ipv4/tunnel4.c#L157">157</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=tunnel64_rcv">tunnel64_rcv</a>,
<a name="L158" href="source/net/ipv4/tunnel4.c#L158">158</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=tunnel64_err">tunnel64_err</a>,
<a name="L159" href="source/net/ipv4/tunnel4.c#L159">159</a>         .no_policy      =       1,
<a name="L160" href="source/net/ipv4/tunnel4.c#L160">160</a>         .netns_ok       =       1,
<a name="L161" href="source/net/ipv4/tunnel4.c#L161">161</a> };
<a name="L162" href="source/net/ipv4/tunnel4.c#L162">162</a> #endif
<a name="L163" href="source/net/ipv4/tunnel4.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/tunnel4.c#L164">164</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tunnel4_init">tunnel4_init</a>(void)
<a name="L165" href="source/net/ipv4/tunnel4.c#L165">165</a> {
<a name="L166" href="source/net/ipv4/tunnel4.c#L166">166</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=tunnel4_protocol">tunnel4_protocol</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>)) {
<a name="L167" href="source/net/ipv4/tunnel4.c#L167">167</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"%s: can't add protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L168" href="source/net/ipv4/tunnel4.c#L168">168</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L169" href="source/net/ipv4/tunnel4.c#L169">169</a>         }
<a name="L170" href="source/net/ipv4/tunnel4.c#L170">170</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L171" href="source/net/ipv4/tunnel4.c#L171">171</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=tunnel64_protocol">tunnel64_protocol</a>, <a href="ident?i=IPPROTO_IPV6">IPPROTO_IPV6</a>)) {
<a name="L172" href="source/net/ipv4/tunnel4.c#L172">172</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"tunnel64 init: can't add protocol\n"</i>);
<a name="L173" href="source/net/ipv4/tunnel4.c#L173">173</a>                 <a href="ident?i=inet_del_protocol">inet_del_protocol</a>(&amp;<a href="ident?i=tunnel4_protocol">tunnel4_protocol</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>);
<a name="L174" href="source/net/ipv4/tunnel4.c#L174">174</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L175" href="source/net/ipv4/tunnel4.c#L175">175</a>         }
<a name="L176" href="source/net/ipv4/tunnel4.c#L176">176</a> #endif
<a name="L177" href="source/net/ipv4/tunnel4.c#L177">177</a>         return 0;
<a name="L178" href="source/net/ipv4/tunnel4.c#L178">178</a> }
<a name="L179" href="source/net/ipv4/tunnel4.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/tunnel4.c#L180">180</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tunnel4_fini">tunnel4_fini</a>(void)
<a name="L181" href="source/net/ipv4/tunnel4.c#L181">181</a> {
<a name="L182" href="source/net/ipv4/tunnel4.c#L182">182</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L183" href="source/net/ipv4/tunnel4.c#L183">183</a>         if (<a href="ident?i=inet_del_protocol">inet_del_protocol</a>(&amp;<a href="ident?i=tunnel64_protocol">tunnel64_protocol</a>, <a href="ident?i=IPPROTO_IPV6">IPPROTO_IPV6</a>))
<a name="L184" href="source/net/ipv4/tunnel4.c#L184">184</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"tunnel64 close: can't remove protocol\n"</i>);
<a name="L185" href="source/net/ipv4/tunnel4.c#L185">185</a> #endif
<a name="L186" href="source/net/ipv4/tunnel4.c#L186">186</a>         if (<a href="ident?i=inet_del_protocol">inet_del_protocol</a>(&amp;<a href="ident?i=tunnel4_protocol">tunnel4_protocol</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>))
<a name="L187" href="source/net/ipv4/tunnel4.c#L187">187</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"tunnel4 close: can't remove protocol\n"</i>);
<a name="L188" href="source/net/ipv4/tunnel4.c#L188">188</a> }
<a name="L189" href="source/net/ipv4/tunnel4.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/tunnel4.c#L190">190</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tunnel4_init">tunnel4_init</a>);
<a name="L191" href="source/net/ipv4/tunnel4.c#L191">191</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tunnel4_fini">tunnel4_fini</a>);
<a name="L192" href="source/net/ipv4/tunnel4.c#L192">192</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L193" href="source/net/ipv4/tunnel4.c#L193">193</a> </pre></div><p>
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
