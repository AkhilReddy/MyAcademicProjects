<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/iptable_raw.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/iptable_raw.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_raw.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/iptable_raw.c">iptable_raw.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/iptable_raw.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/iptable_raw.c#L2">2</a> <b><i> * 'raw' table, which is the very first hooked in at PRE_ROUTING and LOCAL_OUT .</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/iptable_raw.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/iptable_raw.c#L4">4</a> <b><i> * Copyright (C) 2003 Jozsef Kadlecsik &lt;kadlec@blackhole.kfki.hu&gt;</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/iptable_raw.c#L5">5</a> <b><i> */</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/iptable_raw.c#L6">6</a> #include &lt;linux/module.h&gt;
  <a name="L7" href="source/net/ipv4/netfilter/iptable_raw.c#L7">7</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
  <a name="L8" href="source/net/ipv4/netfilter/iptable_raw.c#L8">8</a> #include &lt;linux/slab.h&gt;
  <a name="L9" href="source/net/ipv4/netfilter/iptable_raw.c#L9">9</a> #include &lt;net/ip.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/iptable_raw.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/netfilter/iptable_raw.c#L11">11</a> #define <a href="ident?i=RAW_VALID_HOOKS">RAW_VALID_HOOKS</a> ((1 &lt;&lt; NF_INET_PRE_ROUTING) | (1 &lt;&lt; NF_INET_LOCAL_OUT))
 <a name="L12" href="source/net/ipv4/netfilter/iptable_raw.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/netfilter/iptable_raw.c#L13">13</a> static const struct <a href="ident?i=xt_table">xt_table</a> <a href="ident?i=packet_raw">packet_raw</a> = {
 <a name="L14" href="source/net/ipv4/netfilter/iptable_raw.c#L14">14</a>         .<a href="ident?i=name">name</a> = <i>"raw"</i>,
 <a name="L15" href="source/net/ipv4/netfilter/iptable_raw.c#L15">15</a>         .valid_hooks =  <a href="ident?i=RAW_VALID_HOOKS">RAW_VALID_HOOKS</a>,
 <a name="L16" href="source/net/ipv4/netfilter/iptable_raw.c#L16">16</a>         .<a href="ident?i=me">me</a> = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L17" href="source/net/ipv4/netfilter/iptable_raw.c#L17">17</a>         .<a href="ident?i=af">af</a> = NFPROTO_IPV4,
 <a name="L18" href="source/net/ipv4/netfilter/iptable_raw.c#L18">18</a>         .<a href="ident?i=priority">priority</a> = NF_IP_PRI_RAW,
 <a name="L19" href="source/net/ipv4/netfilter/iptable_raw.c#L19">19</a> };
 <a name="L20" href="source/net/ipv4/netfilter/iptable_raw.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/netfilter/iptable_raw.c#L21">21</a> <b><i>/* The work comes in here from netfilter.c. */</i></b>
 <a name="L22" href="source/net/ipv4/netfilter/iptable_raw.c#L22">22</a> static unsigned int
 <a name="L23" href="source/net/ipv4/netfilter/iptable_raw.c#L23">23</a> <a href="ident?i=iptable_raw_hook">iptable_raw_hook</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L24" href="source/net/ipv4/netfilter/iptable_raw.c#L24">24</a>                  const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L25" href="source/net/ipv4/netfilter/iptable_raw.c#L25">25</a> {
 <a name="L26" href="source/net/ipv4/netfilter/iptable_raw.c#L26">26</a>         const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
 <a name="L27" href="source/net/ipv4/netfilter/iptable_raw.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/netfilter/iptable_raw.c#L28">28</a>         if (<a href="ident?i=ops">ops</a>-&gt;hooknum == NF_INET_LOCAL_OUT &amp;&amp;
 <a name="L29" href="source/net/ipv4/netfilter/iptable_raw.c#L29">29</a>             (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
 <a name="L30" href="source/net/ipv4/netfilter/iptable_raw.c#L30">30</a>              <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
 <a name="L31" href="source/net/ipv4/netfilter/iptable_raw.c#L31">31</a>                 <b><i>/* root is playing with raw sockets. */</i></b>
 <a name="L32" href="source/net/ipv4/netfilter/iptable_raw.c#L32">32</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L33" href="source/net/ipv4/netfilter/iptable_raw.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/netfilter/iptable_raw.c#L34">34</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> : <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>);
 <a name="L35" href="source/net/ipv4/netfilter/iptable_raw.c#L35">35</a>         return <a href="ident?i=ipt_do_table">ipt_do_table</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=state">state</a>, <a href="ident?i=net">net</a>-&gt;ipv4.iptable_raw);
 <a name="L36" href="source/net/ipv4/netfilter/iptable_raw.c#L36">36</a> }
 <a name="L37" href="source/net/ipv4/netfilter/iptable_raw.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/netfilter/iptable_raw.c#L38">38</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *rawtable_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L39" href="source/net/ipv4/netfilter/iptable_raw.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/netfilter/iptable_raw.c#L40">40</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=iptable_raw_net_init">iptable_raw_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L41" href="source/net/ipv4/netfilter/iptable_raw.c#L41">41</a> {
 <a name="L42" href="source/net/ipv4/netfilter/iptable_raw.c#L42">42</a>         struct <a href="ident?i=ipt_replace">ipt_replace</a> *repl;
 <a name="L43" href="source/net/ipv4/netfilter/iptable_raw.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/netfilter/iptable_raw.c#L44">44</a>         repl = <a href="ident?i=ipt_alloc_initial_table">ipt_alloc_initial_table</a>(&amp;<a href="ident?i=packet_raw">packet_raw</a>);
 <a name="L45" href="source/net/ipv4/netfilter/iptable_raw.c#L45">45</a>         if (repl == <a href="ident?i=NULL">NULL</a>)
 <a name="L46" href="source/net/ipv4/netfilter/iptable_raw.c#L46">46</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L47" href="source/net/ipv4/netfilter/iptable_raw.c#L47">47</a>         <a href="ident?i=net">net</a>-&gt;ipv4.iptable_raw =
 <a name="L48" href="source/net/ipv4/netfilter/iptable_raw.c#L48">48</a>                 <a href="ident?i=ipt_register_table">ipt_register_table</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=packet_raw">packet_raw</a>, repl);
 <a name="L49" href="source/net/ipv4/netfilter/iptable_raw.c#L49">49</a>         <a href="ident?i=kfree">kfree</a>(repl);
 <a name="L50" href="source/net/ipv4/netfilter/iptable_raw.c#L50">50</a>         return <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(<a href="ident?i=net">net</a>-&gt;ipv4.iptable_raw);
 <a name="L51" href="source/net/ipv4/netfilter/iptable_raw.c#L51">51</a> }
 <a name="L52" href="source/net/ipv4/netfilter/iptable_raw.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/iptable_raw.c#L53">53</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=iptable_raw_net_exit">iptable_raw_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L54" href="source/net/ipv4/netfilter/iptable_raw.c#L54">54</a> {
 <a name="L55" href="source/net/ipv4/netfilter/iptable_raw.c#L55">55</a>         <a href="ident?i=ipt_unregister_table">ipt_unregister_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=net">net</a>-&gt;ipv4.iptable_raw);
 <a name="L56" href="source/net/ipv4/netfilter/iptable_raw.c#L56">56</a> }
 <a name="L57" href="source/net/ipv4/netfilter/iptable_raw.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/netfilter/iptable_raw.c#L58">58</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=iptable_raw_net_ops">iptable_raw_net_ops</a> = {
 <a name="L59" href="source/net/ipv4/netfilter/iptable_raw.c#L59">59</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=iptable_raw_net_init">iptable_raw_net_init</a>,
 <a name="L60" href="source/net/ipv4/netfilter/iptable_raw.c#L60">60</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=iptable_raw_net_exit">iptable_raw_net_exit</a>,
 <a name="L61" href="source/net/ipv4/netfilter/iptable_raw.c#L61">61</a> };
 <a name="L62" href="source/net/ipv4/netfilter/iptable_raw.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/netfilter/iptable_raw.c#L63">63</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=iptable_raw_init">iptable_raw_init</a>(void)
 <a name="L64" href="source/net/ipv4/netfilter/iptable_raw.c#L64">64</a> {
 <a name="L65" href="source/net/ipv4/netfilter/iptable_raw.c#L65">65</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L66" href="source/net/ipv4/netfilter/iptable_raw.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/netfilter/iptable_raw.c#L67">67</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=iptable_raw_net_ops">iptable_raw_net_ops</a>);
 <a name="L68" href="source/net/ipv4/netfilter/iptable_raw.c#L68">68</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
 <a name="L69" href="source/net/ipv4/netfilter/iptable_raw.c#L69">69</a>                 return <a href="ident?i=ret">ret</a>;
 <a name="L70" href="source/net/ipv4/netfilter/iptable_raw.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/iptable_raw.c#L71">71</a>         <b><i>/* Register hooks */</i></b>
 <a name="L72" href="source/net/ipv4/netfilter/iptable_raw.c#L72">72</a>         rawtable_ops = <a href="ident?i=xt_hook_link">xt_hook_link</a>(&amp;<a href="ident?i=packet_raw">packet_raw</a>, <a href="ident?i=iptable_raw_hook">iptable_raw_hook</a>);
 <a name="L73" href="source/net/ipv4/netfilter/iptable_raw.c#L73">73</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(rawtable_ops)) {
 <a name="L74" href="source/net/ipv4/netfilter/iptable_raw.c#L74">74</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(rawtable_ops);
 <a name="L75" href="source/net/ipv4/netfilter/iptable_raw.c#L75">75</a>                 <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_raw_net_ops">iptable_raw_net_ops</a>);
 <a name="L76" href="source/net/ipv4/netfilter/iptable_raw.c#L76">76</a>         }
 <a name="L77" href="source/net/ipv4/netfilter/iptable_raw.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/netfilter/iptable_raw.c#L78">78</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L79" href="source/net/ipv4/netfilter/iptable_raw.c#L79">79</a> }
 <a name="L80" href="source/net/ipv4/netfilter/iptable_raw.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/netfilter/iptable_raw.c#L81">81</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=iptable_raw_fini">iptable_raw_fini</a>(void)
 <a name="L82" href="source/net/ipv4/netfilter/iptable_raw.c#L82">82</a> {
 <a name="L83" href="source/net/ipv4/netfilter/iptable_raw.c#L83">83</a>         <a href="ident?i=xt_hook_unlink">xt_hook_unlink</a>(&amp;<a href="ident?i=packet_raw">packet_raw</a>, rawtable_ops);
 <a name="L84" href="source/net/ipv4/netfilter/iptable_raw.c#L84">84</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_raw_net_ops">iptable_raw_net_ops</a>);
 <a name="L85" href="source/net/ipv4/netfilter/iptable_raw.c#L85">85</a> }
 <a name="L86" href="source/net/ipv4/netfilter/iptable_raw.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/netfilter/iptable_raw.c#L87">87</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=iptable_raw_init">iptable_raw_init</a>);
 <a name="L88" href="source/net/ipv4/netfilter/iptable_raw.c#L88">88</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=iptable_raw_fini">iptable_raw_fini</a>);
 <a name="L89" href="source/net/ipv4/netfilter/iptable_raw.c#L89">89</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L90" href="source/net/ipv4/netfilter/iptable_raw.c#L90">90</a> </pre></div><p>
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
