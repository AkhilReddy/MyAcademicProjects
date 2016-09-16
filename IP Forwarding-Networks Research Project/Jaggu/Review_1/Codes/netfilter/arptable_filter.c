<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/arptable_filter.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/arptable_filter.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/arptable_filter.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/arptable_filter.c">arptable_filter.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/arptable_filter.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/arptable_filter.c#L2">2</a> <b><i> * Filtering ARP tables module.</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/arptable_filter.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/arptable_filter.c#L4">4</a> <b><i> * Copyright (C) 2002 David S. Miller (davem@redhat.com)</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/arptable_filter.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/arptable_filter.c#L6">6</a> <b><i> */</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/arptable_filter.c#L7">7</a> 
  <a name="L8" href="source/net/ipv4/netfilter/arptable_filter.c#L8">8</a> #include &lt;linux/module.h&gt;
  <a name="L9" href="source/net/ipv4/netfilter/arptable_filter.c#L9">9</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/arptable_filter.c#L10">10</a> #include &lt;linux/netfilter_arp/arp_tables.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/arptable_filter.c#L11">11</a> #include &lt;linux/slab.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/arptable_filter.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/netfilter/arptable_filter.c#L13">13</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L14" href="source/net/ipv4/netfilter/arptable_filter.c#L14">14</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"David S. Miller &lt;davem@redhat.com&gt;"</i>);
 <a name="L15" href="source/net/ipv4/netfilter/arptable_filter.c#L15">15</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"arptables filter table"</i>);
 <a name="L16" href="source/net/ipv4/netfilter/arptable_filter.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/netfilter/arptable_filter.c#L17">17</a> #define <a href="ident?i=FILTER_VALID_HOOKS">FILTER_VALID_HOOKS</a> ((1 &lt;&lt; <a href="ident?i=NF_ARP_IN">NF_ARP_IN</a>) | (1 &lt;&lt; <a href="ident?i=NF_ARP_OUT">NF_ARP_OUT</a>) | \
 <a name="L18" href="source/net/ipv4/netfilter/arptable_filter.c#L18">18</a>                            (1 &lt;&lt; <a href="ident?i=NF_ARP_FORWARD">NF_ARP_FORWARD</a>))
 <a name="L19" href="source/net/ipv4/netfilter/arptable_filter.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/netfilter/arptable_filter.c#L20">20</a> static const struct <a href="ident?i=xt_table">xt_table</a> <a href="ident?i=packet_filter">packet_filter</a> = {
 <a name="L21" href="source/net/ipv4/netfilter/arptable_filter.c#L21">21</a>         .<a href="ident?i=name">name</a>           = <i>"filter"</i>,
 <a name="L22" href="source/net/ipv4/netfilter/arptable_filter.c#L22">22</a>         .valid_hooks    = <a href="ident?i=FILTER_VALID_HOOKS">FILTER_VALID_HOOKS</a>,
 <a name="L23" href="source/net/ipv4/netfilter/arptable_filter.c#L23">23</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L24" href="source/net/ipv4/netfilter/arptable_filter.c#L24">24</a>         .<a href="ident?i=af">af</a>             = NFPROTO_ARP,
 <a name="L25" href="source/net/ipv4/netfilter/arptable_filter.c#L25">25</a>         .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_FILTER,
 <a name="L26" href="source/net/ipv4/netfilter/arptable_filter.c#L26">26</a> };
 <a name="L27" href="source/net/ipv4/netfilter/arptable_filter.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/netfilter/arptable_filter.c#L28">28</a> <b><i>/* The work comes in here from netfilter.c */</i></b>
 <a name="L29" href="source/net/ipv4/netfilter/arptable_filter.c#L29">29</a> static unsigned int
 <a name="L30" href="source/net/ipv4/netfilter/arptable_filter.c#L30">30</a> <a href="ident?i=arptable_filter_hook">arptable_filter_hook</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L31" href="source/net/ipv4/netfilter/arptable_filter.c#L31">31</a>                      const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L32" href="source/net/ipv4/netfilter/arptable_filter.c#L32">32</a> {
 <a name="L33" href="source/net/ipv4/netfilter/arptable_filter.c#L33">33</a>         const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> : <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>);
 <a name="L34" href="source/net/ipv4/netfilter/arptable_filter.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/netfilter/arptable_filter.c#L35">35</a>         return <a href="ident?i=arpt_do_table">arpt_do_table</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=state">state</a>,
 <a name="L36" href="source/net/ipv4/netfilter/arptable_filter.c#L36">36</a>                              <a href="ident?i=net">net</a>-&gt;ipv4.arptable_filter);
 <a name="L37" href="source/net/ipv4/netfilter/arptable_filter.c#L37">37</a> }
 <a name="L38" href="source/net/ipv4/netfilter/arptable_filter.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/netfilter/arptable_filter.c#L39">39</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *arpfilter_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L40" href="source/net/ipv4/netfilter/arptable_filter.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/arptable_filter.c#L41">41</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=arptable_filter_net_init">arptable_filter_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L42" href="source/net/ipv4/netfilter/arptable_filter.c#L42">42</a> {
 <a name="L43" href="source/net/ipv4/netfilter/arptable_filter.c#L43">43</a>         struct <a href="ident?i=arpt_replace">arpt_replace</a> *repl;
 <a name="L44" href="source/net/ipv4/netfilter/arptable_filter.c#L44">44</a>         
 <a name="L45" href="source/net/ipv4/netfilter/arptable_filter.c#L45">45</a>         repl = <a href="ident?i=arpt_alloc_initial_table">arpt_alloc_initial_table</a>(&amp;<a href="ident?i=packet_filter">packet_filter</a>);
 <a name="L46" href="source/net/ipv4/netfilter/arptable_filter.c#L46">46</a>         if (repl == <a href="ident?i=NULL">NULL</a>)
 <a name="L47" href="source/net/ipv4/netfilter/arptable_filter.c#L47">47</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L48" href="source/net/ipv4/netfilter/arptable_filter.c#L48">48</a>         <a href="ident?i=net">net</a>-&gt;ipv4.arptable_filter =
 <a name="L49" href="source/net/ipv4/netfilter/arptable_filter.c#L49">49</a>                 <a href="ident?i=arpt_register_table">arpt_register_table</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=packet_filter">packet_filter</a>, repl);
 <a name="L50" href="source/net/ipv4/netfilter/arptable_filter.c#L50">50</a>         <a href="ident?i=kfree">kfree</a>(repl);
 <a name="L51" href="source/net/ipv4/netfilter/arptable_filter.c#L51">51</a>         return <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(<a href="ident?i=net">net</a>-&gt;ipv4.arptable_filter);
 <a name="L52" href="source/net/ipv4/netfilter/arptable_filter.c#L52">52</a> }
 <a name="L53" href="source/net/ipv4/netfilter/arptable_filter.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/netfilter/arptable_filter.c#L54">54</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=arptable_filter_net_exit">arptable_filter_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L55" href="source/net/ipv4/netfilter/arptable_filter.c#L55">55</a> {
 <a name="L56" href="source/net/ipv4/netfilter/arptable_filter.c#L56">56</a>         <a href="ident?i=arpt_unregister_table">arpt_unregister_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.arptable_filter);
 <a name="L57" href="source/net/ipv4/netfilter/arptable_filter.c#L57">57</a> }
 <a name="L58" href="source/net/ipv4/netfilter/arptable_filter.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/netfilter/arptable_filter.c#L59">59</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=arptable_filter_net_ops">arptable_filter_net_ops</a> = {
 <a name="L60" href="source/net/ipv4/netfilter/arptable_filter.c#L60">60</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=arptable_filter_net_init">arptable_filter_net_init</a>,
 <a name="L61" href="source/net/ipv4/netfilter/arptable_filter.c#L61">61</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=arptable_filter_net_exit">arptable_filter_net_exit</a>,
 <a name="L62" href="source/net/ipv4/netfilter/arptable_filter.c#L62">62</a> };
 <a name="L63" href="source/net/ipv4/netfilter/arptable_filter.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/netfilter/arptable_filter.c#L64">64</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=arptable_filter_init">arptable_filter_init</a>(void)
 <a name="L65" href="source/net/ipv4/netfilter/arptable_filter.c#L65">65</a> {
 <a name="L66" href="source/net/ipv4/netfilter/arptable_filter.c#L66">66</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L67" href="source/net/ipv4/netfilter/arptable_filter.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/arptable_filter.c#L68">68</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=arptable_filter_net_ops">arptable_filter_net_ops</a>);
 <a name="L69" href="source/net/ipv4/netfilter/arptable_filter.c#L69">69</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
 <a name="L70" href="source/net/ipv4/netfilter/arptable_filter.c#L70">70</a>                 return <a href="ident?i=ret">ret</a>;
 <a name="L71" href="source/net/ipv4/netfilter/arptable_filter.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/arptable_filter.c#L72">72</a>         arpfilter_ops = <a href="ident?i=xt_hook_link">xt_hook_link</a>(&amp;<a href="ident?i=packet_filter">packet_filter</a>, <a href="ident?i=arptable_filter_hook">arptable_filter_hook</a>);
 <a name="L73" href="source/net/ipv4/netfilter/arptable_filter.c#L73">73</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(arpfilter_ops)) {
 <a name="L74" href="source/net/ipv4/netfilter/arptable_filter.c#L74">74</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(arpfilter_ops);
 <a name="L75" href="source/net/ipv4/netfilter/arptable_filter.c#L75">75</a>                 goto cleanup_table;
 <a name="L76" href="source/net/ipv4/netfilter/arptable_filter.c#L76">76</a>         }
 <a name="L77" href="source/net/ipv4/netfilter/arptable_filter.c#L77">77</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L78" href="source/net/ipv4/netfilter/arptable_filter.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/arptable_filter.c#L79">79</a> cleanup_table:
 <a name="L80" href="source/net/ipv4/netfilter/arptable_filter.c#L80">80</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=arptable_filter_net_ops">arptable_filter_net_ops</a>);
 <a name="L81" href="source/net/ipv4/netfilter/arptable_filter.c#L81">81</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L82" href="source/net/ipv4/netfilter/arptable_filter.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/netfilter/arptable_filter.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/arptable_filter.c#L84">84</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=arptable_filter_fini">arptable_filter_fini</a>(void)
 <a name="L85" href="source/net/ipv4/netfilter/arptable_filter.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/netfilter/arptable_filter.c#L86">86</a>         <a href="ident?i=xt_hook_unlink">xt_hook_unlink</a>(&amp;<a href="ident?i=packet_filter">packet_filter</a>, arpfilter_ops);
 <a name="L87" href="source/net/ipv4/netfilter/arptable_filter.c#L87">87</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=arptable_filter_net_ops">arptable_filter_net_ops</a>);
 <a name="L88" href="source/net/ipv4/netfilter/arptable_filter.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/netfilter/arptable_filter.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/arptable_filter.c#L90">90</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=arptable_filter_init">arptable_filter_init</a>);
 <a name="L91" href="source/net/ipv4/netfilter/arptable_filter.c#L91">91</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=arptable_filter_fini">arptable_filter_fini</a>);
 <a name="L92" href="source/net/ipv4/netfilter/arptable_filter.c#L92">92</a> </pre></div><p>
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
