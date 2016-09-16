<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_memcontrol.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_memcontrol.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_memcontrol.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_memcontrol.c">tcp_memcontrol.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_memcontrol.c#L1">1</a> #include &lt;net/tcp.h&gt;
  <a name="L2" href="source/net/ipv4/tcp_memcontrol.c#L2">2</a> #include &lt;net/tcp_memcontrol.h&gt;
  <a name="L3" href="source/net/ipv4/tcp_memcontrol.c#L3">3</a> #include &lt;net/sock.h&gt;
  <a name="L4" href="source/net/ipv4/tcp_memcontrol.c#L4">4</a> #include &lt;net/ip.h&gt;
  <a name="L5" href="source/net/ipv4/tcp_memcontrol.c#L5">5</a> #include &lt;linux/nsproxy.h&gt;
  <a name="L6" href="source/net/ipv4/tcp_memcontrol.c#L6">6</a> #include &lt;linux/memcontrol.h&gt;
  <a name="L7" href="source/net/ipv4/tcp_memcontrol.c#L7">7</a> #include &lt;linux/module.h&gt;
  <a name="L8" href="source/net/ipv4/tcp_memcontrol.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/tcp_memcontrol.c#L9">9</a> int <a href="ident?i=tcp_init_cgroup">tcp_init_cgroup</a>(struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *memcg, struct <a href="ident?i=cgroup_subsys">cgroup_subsys</a> *ss)
 <a name="L10" href="source/net/ipv4/tcp_memcontrol.c#L10">10</a> {
 <a name="L11" href="source/net/ipv4/tcp_memcontrol.c#L11">11</a>         <b><i>/*</i></b>
 <a name="L12" href="source/net/ipv4/tcp_memcontrol.c#L12">12</a> <b><i>         * The root cgroup does not use page_counters, but rather,</i></b>
 <a name="L13" href="source/net/ipv4/tcp_memcontrol.c#L13">13</a> <b><i>         * rely on the data already collected by the network</i></b>
 <a name="L14" href="source/net/ipv4/tcp_memcontrol.c#L14">14</a> <b><i>         * subsystem</i></b>
 <a name="L15" href="source/net/ipv4/tcp_memcontrol.c#L15">15</a> <b><i>         */</i></b>
 <a name="L16" href="source/net/ipv4/tcp_memcontrol.c#L16">16</a>         struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *<a href="ident?i=parent">parent</a> = <a href="ident?i=parent_mem_cgroup">parent_mem_cgroup</a>(memcg);
 <a name="L17" href="source/net/ipv4/tcp_memcontrol.c#L17">17</a>         struct <a href="ident?i=page_counter">page_counter</a> *counter_parent = <a href="ident?i=NULL">NULL</a>;
 <a name="L18" href="source/net/ipv4/tcp_memcontrol.c#L18">18</a>         struct <a href="ident?i=cg_proto">cg_proto</a> *<a href="ident?i=cg_proto">cg_proto</a>, *parent_cg;
 <a name="L19" href="source/net/ipv4/tcp_memcontrol.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/tcp_memcontrol.c#L20">20</a>         <a href="ident?i=cg_proto">cg_proto</a> = <a href="ident?i=tcp_prot">tcp_prot</a>.proto_cgroup(memcg);
 <a name="L21" href="source/net/ipv4/tcp_memcontrol.c#L21">21</a>         if (!<a href="ident?i=cg_proto">cg_proto</a>)
 <a name="L22" href="source/net/ipv4/tcp_memcontrol.c#L22">22</a>                 return 0;
 <a name="L23" href="source/net/ipv4/tcp_memcontrol.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/tcp_memcontrol.c#L24">24</a>         <a href="ident?i=cg_proto">cg_proto</a>-&gt;sysctl_mem[0] = <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[0];
 <a name="L25" href="source/net/ipv4/tcp_memcontrol.c#L25">25</a>         <a href="ident?i=cg_proto">cg_proto</a>-&gt;sysctl_mem[1] = <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[1];
 <a name="L26" href="source/net/ipv4/tcp_memcontrol.c#L26">26</a>         <a href="ident?i=cg_proto">cg_proto</a>-&gt;sysctl_mem[2] = <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[2];
 <a name="L27" href="source/net/ipv4/tcp_memcontrol.c#L27">27</a>         <a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_pressure = 0;
 <a name="L28" href="source/net/ipv4/tcp_memcontrol.c#L28">28</a>         <a href="ident?i=cg_proto">cg_proto</a>-&gt;memcg = memcg;
 <a name="L29" href="source/net/ipv4/tcp_memcontrol.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/tcp_memcontrol.c#L30">30</a>         parent_cg = <a href="ident?i=tcp_prot">tcp_prot</a>.proto_cgroup(<a href="ident?i=parent">parent</a>);
 <a name="L31" href="source/net/ipv4/tcp_memcontrol.c#L31">31</a>         if (parent_cg)
 <a name="L32" href="source/net/ipv4/tcp_memcontrol.c#L32">32</a>                 counter_parent = &amp;parent_cg-&gt;memory_allocated;
 <a name="L33" href="source/net/ipv4/tcp_memcontrol.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/tcp_memcontrol.c#L34">34</a>         <a href="ident?i=page_counter_init">page_counter_init</a>(&amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated, counter_parent);
 <a name="L35" href="source/net/ipv4/tcp_memcontrol.c#L35">35</a>         <a href="ident?i=percpu_counter_init">percpu_counter_init</a>(&amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;sockets_allocated, 0, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
 <a name="L36" href="source/net/ipv4/tcp_memcontrol.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/tcp_memcontrol.c#L37">37</a>         return 0;
 <a name="L38" href="source/net/ipv4/tcp_memcontrol.c#L38">38</a> }
 <a name="L39" href="source/net/ipv4/tcp_memcontrol.c#L39">39</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_init_cgroup">tcp_init_cgroup</a>);
 <a name="L40" href="source/net/ipv4/tcp_memcontrol.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/tcp_memcontrol.c#L41">41</a> void <a href="ident?i=tcp_destroy_cgroup">tcp_destroy_cgroup</a>(struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *memcg)
 <a name="L42" href="source/net/ipv4/tcp_memcontrol.c#L42">42</a> {
 <a name="L43" href="source/net/ipv4/tcp_memcontrol.c#L43">43</a>         struct <a href="ident?i=cg_proto">cg_proto</a> *<a href="ident?i=cg_proto">cg_proto</a>;
 <a name="L44" href="source/net/ipv4/tcp_memcontrol.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/tcp_memcontrol.c#L45">45</a>         <a href="ident?i=cg_proto">cg_proto</a> = <a href="ident?i=tcp_prot">tcp_prot</a>.proto_cgroup(memcg);
 <a name="L46" href="source/net/ipv4/tcp_memcontrol.c#L46">46</a>         if (!<a href="ident?i=cg_proto">cg_proto</a>)
 <a name="L47" href="source/net/ipv4/tcp_memcontrol.c#L47">47</a>                 return;
 <a name="L48" href="source/net/ipv4/tcp_memcontrol.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/tcp_memcontrol.c#L49">49</a>         <a href="ident?i=percpu_counter_destroy">percpu_counter_destroy</a>(&amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;sockets_allocated);
 <a name="L50" href="source/net/ipv4/tcp_memcontrol.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/tcp_memcontrol.c#L51">51</a>         if (<a href="ident?i=test_bit">test_bit</a>(MEMCG_SOCK_ACTIVATED, &amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;<a href="ident?i=flags">flags</a>))
 <a name="L52" href="source/net/ipv4/tcp_memcontrol.c#L52">52</a>                 <a href="ident?i=static_key_slow_dec">static_key_slow_dec</a>(&amp;<a href="ident?i=memcg_socket_limit_enabled">memcg_socket_limit_enabled</a>);
 <a name="L53" href="source/net/ipv4/tcp_memcontrol.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tcp_memcontrol.c#L54">54</a> }
 <a name="L55" href="source/net/ipv4/tcp_memcontrol.c#L55">55</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_destroy_cgroup">tcp_destroy_cgroup</a>);
 <a name="L56" href="source/net/ipv4/tcp_memcontrol.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/tcp_memcontrol.c#L57">57</a> static int <a href="ident?i=tcp_update_limit">tcp_update_limit</a>(struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *memcg, unsigned long <a href="ident?i=nr_pages">nr_pages</a>)
 <a name="L58" href="source/net/ipv4/tcp_memcontrol.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/tcp_memcontrol.c#L59">59</a>         struct <a href="ident?i=cg_proto">cg_proto</a> *<a href="ident?i=cg_proto">cg_proto</a>;
 <a name="L60" href="source/net/ipv4/tcp_memcontrol.c#L60">60</a>         int <a href="ident?i=i">i</a>;
 <a name="L61" href="source/net/ipv4/tcp_memcontrol.c#L61">61</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L62" href="source/net/ipv4/tcp_memcontrol.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/tcp_memcontrol.c#L63">63</a>         <a href="ident?i=cg_proto">cg_proto</a> = <a href="ident?i=tcp_prot">tcp_prot</a>.proto_cgroup(memcg);
 <a name="L64" href="source/net/ipv4/tcp_memcontrol.c#L64">64</a>         if (!<a href="ident?i=cg_proto">cg_proto</a>)
 <a name="L65" href="source/net/ipv4/tcp_memcontrol.c#L65">65</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L66" href="source/net/ipv4/tcp_memcontrol.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/tcp_memcontrol.c#L67">67</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=page_counter_limit">page_counter_limit</a>(&amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated, <a href="ident?i=nr_pages">nr_pages</a>);
 <a name="L68" href="source/net/ipv4/tcp_memcontrol.c#L68">68</a>         if (<a href="ident?i=ret">ret</a>)
 <a name="L69" href="source/net/ipv4/tcp_memcontrol.c#L69">69</a>                 return <a href="ident?i=ret">ret</a>;
 <a name="L70" href="source/net/ipv4/tcp_memcontrol.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/tcp_memcontrol.c#L71">71</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; 3; <a href="ident?i=i">i</a>++)
 <a name="L72" href="source/net/ipv4/tcp_memcontrol.c#L72">72</a>                 <a href="ident?i=cg_proto">cg_proto</a>-&gt;sysctl_mem[<a href="ident?i=i">i</a>] = <a href="ident?i=min_t">min_t</a>(long, <a href="ident?i=nr_pages">nr_pages</a>,
 <a name="L73" href="source/net/ipv4/tcp_memcontrol.c#L73">73</a>                                                 <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[<a href="ident?i=i">i</a>]);
 <a name="L74" href="source/net/ipv4/tcp_memcontrol.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/tcp_memcontrol.c#L75">75</a>         if (<a href="ident?i=nr_pages">nr_pages</a> == <a href="ident?i=PAGE_COUNTER_MAX">PAGE_COUNTER_MAX</a>)
 <a name="L76" href="source/net/ipv4/tcp_memcontrol.c#L76">76</a>                 <a href="ident?i=clear_bit">clear_bit</a>(MEMCG_SOCK_ACTIVE, &amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;<a href="ident?i=flags">flags</a>);
 <a name="L77" href="source/net/ipv4/tcp_memcontrol.c#L77">77</a>         else {
 <a name="L78" href="source/net/ipv4/tcp_memcontrol.c#L78">78</a>                 <b><i>/*</i></b>
 <a name="L79" href="source/net/ipv4/tcp_memcontrol.c#L79">79</a> <b><i>                 * The active bit needs to be written after the static_key</i></b>
 <a name="L80" href="source/net/ipv4/tcp_memcontrol.c#L80">80</a> <b><i>                 * update. This is what guarantees that the socket activation</i></b>
 <a name="L81" href="source/net/ipv4/tcp_memcontrol.c#L81">81</a> <b><i>                 * function is the last one to run. See sock_update_memcg() for</i></b>
 <a name="L82" href="source/net/ipv4/tcp_memcontrol.c#L82">82</a> <b><i>                 * details, and note that we don't mark any socket as belonging</i></b>
 <a name="L83" href="source/net/ipv4/tcp_memcontrol.c#L83">83</a> <b><i>                 * to this memcg until that flag is up.</i></b>
 <a name="L84" href="source/net/ipv4/tcp_memcontrol.c#L84">84</a> <b><i>                 *</i></b>
 <a name="L85" href="source/net/ipv4/tcp_memcontrol.c#L85">85</a> <b><i>                 * We need to do this, because static_keys will span multiple</i></b>
 <a name="L86" href="source/net/ipv4/tcp_memcontrol.c#L86">86</a> <b><i>                 * sites, but we can't control their order. If we mark a socket</i></b>
 <a name="L87" href="source/net/ipv4/tcp_memcontrol.c#L87">87</a> <b><i>                 * as accounted, but the accounting functions are not patched in</i></b>
 <a name="L88" href="source/net/ipv4/tcp_memcontrol.c#L88">88</a> <b><i>                 * yet, we'll lose accounting.</i></b>
 <a name="L89" href="source/net/ipv4/tcp_memcontrol.c#L89">89</a> <b><i>                 *</i></b>
 <a name="L90" href="source/net/ipv4/tcp_memcontrol.c#L90">90</a> <b><i>                 * We never race with the readers in sock_update_memcg(),</i></b>
 <a name="L91" href="source/net/ipv4/tcp_memcontrol.c#L91">91</a> <b><i>                 * because when this value change, the code to process it is not</i></b>
 <a name="L92" href="source/net/ipv4/tcp_memcontrol.c#L92">92</a> <b><i>                 * patched in yet.</i></b>
 <a name="L93" href="source/net/ipv4/tcp_memcontrol.c#L93">93</a> <b><i>                 *</i></b>
 <a name="L94" href="source/net/ipv4/tcp_memcontrol.c#L94">94</a> <b><i>                 * The activated bit is used to guarantee that no two writers</i></b>
 <a name="L95" href="source/net/ipv4/tcp_memcontrol.c#L95">95</a> <b><i>                 * will do the update in the same memcg. Without that, we can't</i></b>
 <a name="L96" href="source/net/ipv4/tcp_memcontrol.c#L96">96</a> <b><i>                 * properly shutdown the static key.</i></b>
 <a name="L97" href="source/net/ipv4/tcp_memcontrol.c#L97">97</a> <b><i>                 */</i></b>
 <a name="L98" href="source/net/ipv4/tcp_memcontrol.c#L98">98</a>                 if (!<a href="ident?i=test_and_set_bit">test_and_set_bit</a>(MEMCG_SOCK_ACTIVATED, &amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;<a href="ident?i=flags">flags</a>))
 <a name="L99" href="source/net/ipv4/tcp_memcontrol.c#L99">99</a>                         <a href="ident?i=static_key_slow_inc">static_key_slow_inc</a>(&amp;<a href="ident?i=memcg_socket_limit_enabled">memcg_socket_limit_enabled</a>);
<a name="L100" href="source/net/ipv4/tcp_memcontrol.c#L100">100</a>                 <a href="ident?i=set_bit">set_bit</a>(MEMCG_SOCK_ACTIVE, &amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;<a href="ident?i=flags">flags</a>);
<a name="L101" href="source/net/ipv4/tcp_memcontrol.c#L101">101</a>         }
<a name="L102" href="source/net/ipv4/tcp_memcontrol.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/tcp_memcontrol.c#L103">103</a>         return 0;
<a name="L104" href="source/net/ipv4/tcp_memcontrol.c#L104">104</a> }
<a name="L105" href="source/net/ipv4/tcp_memcontrol.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/tcp_memcontrol.c#L106">106</a> enum {
<a name="L107" href="source/net/ipv4/tcp_memcontrol.c#L107">107</a>         RES_USAGE,
<a name="L108" href="source/net/ipv4/tcp_memcontrol.c#L108">108</a>         RES_LIMIT,
<a name="L109" href="source/net/ipv4/tcp_memcontrol.c#L109">109</a>         RES_MAX_USAGE,
<a name="L110" href="source/net/ipv4/tcp_memcontrol.c#L110">110</a>         RES_FAILCNT,
<a name="L111" href="source/net/ipv4/tcp_memcontrol.c#L111">111</a> };
<a name="L112" href="source/net/ipv4/tcp_memcontrol.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/tcp_memcontrol.c#L113">113</a> static <a href="ident?i=DEFINE_MUTEX">DEFINE_MUTEX</a>(tcp_limit_mutex);
<a name="L114" href="source/net/ipv4/tcp_memcontrol.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/tcp_memcontrol.c#L115">115</a> static <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=tcp_cgroup_write">tcp_cgroup_write</a>(struct <a href="ident?i=kernfs_open_file">kernfs_open_file</a> *<a href="ident?i=of">of</a>,
<a name="L116" href="source/net/ipv4/tcp_memcontrol.c#L116">116</a>                                 char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> nbytes, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=off">off</a>)
<a name="L117" href="source/net/ipv4/tcp_memcontrol.c#L117">117</a> {
<a name="L118" href="source/net/ipv4/tcp_memcontrol.c#L118">118</a>         struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *memcg = <a href="ident?i=mem_cgroup_from_css">mem_cgroup_from_css</a>(<a href="ident?i=of_css">of_css</a>(<a href="ident?i=of">of</a>));
<a name="L119" href="source/net/ipv4/tcp_memcontrol.c#L119">119</a>         unsigned long <a href="ident?i=nr_pages">nr_pages</a>;
<a name="L120" href="source/net/ipv4/tcp_memcontrol.c#L120">120</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L121" href="source/net/ipv4/tcp_memcontrol.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_memcontrol.c#L122">122</a>         <a href="ident?i=buf">buf</a> = <a href="ident?i=strstrip">strstrip</a>(<a href="ident?i=buf">buf</a>);
<a name="L123" href="source/net/ipv4/tcp_memcontrol.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/tcp_memcontrol.c#L124">124</a>         switch (<a href="ident?i=of_cft">of_cft</a>(<a href="ident?i=of">of</a>)-&gt;<a href="ident?i=private">private</a>) {
<a name="L125" href="source/net/ipv4/tcp_memcontrol.c#L125">125</a>         case RES_LIMIT:
<a name="L126" href="source/net/ipv4/tcp_memcontrol.c#L126">126</a>                 <b><i>/* see memcontrol.c */</i></b>
<a name="L127" href="source/net/ipv4/tcp_memcontrol.c#L127">127</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=page_counter_memparse">page_counter_memparse</a>(<a href="ident?i=buf">buf</a>, <i>"-1"</i>, &amp;<a href="ident?i=nr_pages">nr_pages</a>);
<a name="L128" href="source/net/ipv4/tcp_memcontrol.c#L128">128</a>                 if (<a href="ident?i=ret">ret</a>)
<a name="L129" href="source/net/ipv4/tcp_memcontrol.c#L129">129</a>                         break;
<a name="L130" href="source/net/ipv4/tcp_memcontrol.c#L130">130</a>                 <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;tcp_limit_mutex);
<a name="L131" href="source/net/ipv4/tcp_memcontrol.c#L131">131</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=tcp_update_limit">tcp_update_limit</a>(memcg, <a href="ident?i=nr_pages">nr_pages</a>);
<a name="L132" href="source/net/ipv4/tcp_memcontrol.c#L132">132</a>                 <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;tcp_limit_mutex);
<a name="L133" href="source/net/ipv4/tcp_memcontrol.c#L133">133</a>                 break;
<a name="L134" href="source/net/ipv4/tcp_memcontrol.c#L134">134</a>         default:
<a name="L135" href="source/net/ipv4/tcp_memcontrol.c#L135">135</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L136" href="source/net/ipv4/tcp_memcontrol.c#L136">136</a>                 break;
<a name="L137" href="source/net/ipv4/tcp_memcontrol.c#L137">137</a>         }
<a name="L138" href="source/net/ipv4/tcp_memcontrol.c#L138">138</a>         return <a href="ident?i=ret">ret</a> ?: nbytes;
<a name="L139" href="source/net/ipv4/tcp_memcontrol.c#L139">139</a> }
<a name="L140" href="source/net/ipv4/tcp_memcontrol.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/tcp_memcontrol.c#L141">141</a> static <a href="ident?i=u64">u64</a> <a href="ident?i=tcp_cgroup_read">tcp_cgroup_read</a>(struct <a href="ident?i=cgroup_subsys_state">cgroup_subsys_state</a> *css, struct <a href="ident?i=cftype">cftype</a> *cft)
<a name="L142" href="source/net/ipv4/tcp_memcontrol.c#L142">142</a> {
<a name="L143" href="source/net/ipv4/tcp_memcontrol.c#L143">143</a>         struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *memcg = <a href="ident?i=mem_cgroup_from_css">mem_cgroup_from_css</a>(css);
<a name="L144" href="source/net/ipv4/tcp_memcontrol.c#L144">144</a>         struct <a href="ident?i=cg_proto">cg_proto</a> *<a href="ident?i=cg_proto">cg_proto</a> = <a href="ident?i=tcp_prot">tcp_prot</a>.proto_cgroup(memcg);
<a name="L145" href="source/net/ipv4/tcp_memcontrol.c#L145">145</a>         <a href="ident?i=u64">u64</a> <a href="ident?i=val">val</a>;
<a name="L146" href="source/net/ipv4/tcp_memcontrol.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_memcontrol.c#L147">147</a>         switch (cft-&gt;<a href="ident?i=private">private</a>) {
<a name="L148" href="source/net/ipv4/tcp_memcontrol.c#L148">148</a>         case RES_LIMIT:
<a name="L149" href="source/net/ipv4/tcp_memcontrol.c#L149">149</a>                 if (!<a href="ident?i=cg_proto">cg_proto</a>)
<a name="L150" href="source/net/ipv4/tcp_memcontrol.c#L150">150</a>                         return <a href="ident?i=PAGE_COUNTER_MAX">PAGE_COUNTER_MAX</a>;
<a name="L151" href="source/net/ipv4/tcp_memcontrol.c#L151">151</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated.<a href="ident?i=limit">limit</a>;
<a name="L152" href="source/net/ipv4/tcp_memcontrol.c#L152">152</a>                 <a href="ident?i=val">val</a> *= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>;
<a name="L153" href="source/net/ipv4/tcp_memcontrol.c#L153">153</a>                 break;
<a name="L154" href="source/net/ipv4/tcp_memcontrol.c#L154">154</a>         case RES_USAGE:
<a name="L155" href="source/net/ipv4/tcp_memcontrol.c#L155">155</a>                 if (!<a href="ident?i=cg_proto">cg_proto</a>)
<a name="L156" href="source/net/ipv4/tcp_memcontrol.c#L156">156</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=atomic_long_read">atomic_long_read</a>(&amp;<a href="ident?i=tcp_memory_allocated">tcp_memory_allocated</a>);
<a name="L157" href="source/net/ipv4/tcp_memcontrol.c#L157">157</a>                 else
<a name="L158" href="source/net/ipv4/tcp_memcontrol.c#L158">158</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=page_counter_read">page_counter_read</a>(&amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated);
<a name="L159" href="source/net/ipv4/tcp_memcontrol.c#L159">159</a>                 <a href="ident?i=val">val</a> *= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>;
<a name="L160" href="source/net/ipv4/tcp_memcontrol.c#L160">160</a>                 break;
<a name="L161" href="source/net/ipv4/tcp_memcontrol.c#L161">161</a>         case RES_FAILCNT:
<a name="L162" href="source/net/ipv4/tcp_memcontrol.c#L162">162</a>                 if (!<a href="ident?i=cg_proto">cg_proto</a>)
<a name="L163" href="source/net/ipv4/tcp_memcontrol.c#L163">163</a>                         return 0;
<a name="L164" href="source/net/ipv4/tcp_memcontrol.c#L164">164</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated.failcnt;
<a name="L165" href="source/net/ipv4/tcp_memcontrol.c#L165">165</a>                 break;
<a name="L166" href="source/net/ipv4/tcp_memcontrol.c#L166">166</a>         case RES_MAX_USAGE:
<a name="L167" href="source/net/ipv4/tcp_memcontrol.c#L167">167</a>                 if (!<a href="ident?i=cg_proto">cg_proto</a>)
<a name="L168" href="source/net/ipv4/tcp_memcontrol.c#L168">168</a>                         return 0;
<a name="L169" href="source/net/ipv4/tcp_memcontrol.c#L169">169</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated.watermark;
<a name="L170" href="source/net/ipv4/tcp_memcontrol.c#L170">170</a>                 <a href="ident?i=val">val</a> *= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>;
<a name="L171" href="source/net/ipv4/tcp_memcontrol.c#L171">171</a>                 break;
<a name="L172" href="source/net/ipv4/tcp_memcontrol.c#L172">172</a>         default:
<a name="L173" href="source/net/ipv4/tcp_memcontrol.c#L173">173</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L174" href="source/net/ipv4/tcp_memcontrol.c#L174">174</a>         }
<a name="L175" href="source/net/ipv4/tcp_memcontrol.c#L175">175</a>         return <a href="ident?i=val">val</a>;
<a name="L176" href="source/net/ipv4/tcp_memcontrol.c#L176">176</a> }
<a name="L177" href="source/net/ipv4/tcp_memcontrol.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/tcp_memcontrol.c#L178">178</a> static <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=tcp_cgroup_reset">tcp_cgroup_reset</a>(struct <a href="ident?i=kernfs_open_file">kernfs_open_file</a> *<a href="ident?i=of">of</a>,
<a name="L179" href="source/net/ipv4/tcp_memcontrol.c#L179">179</a>                                 char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> nbytes, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=off">off</a>)
<a name="L180" href="source/net/ipv4/tcp_memcontrol.c#L180">180</a> {
<a name="L181" href="source/net/ipv4/tcp_memcontrol.c#L181">181</a>         struct <a href="ident?i=mem_cgroup">mem_cgroup</a> *memcg;
<a name="L182" href="source/net/ipv4/tcp_memcontrol.c#L182">182</a>         struct <a href="ident?i=cg_proto">cg_proto</a> *<a href="ident?i=cg_proto">cg_proto</a>;
<a name="L183" href="source/net/ipv4/tcp_memcontrol.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/tcp_memcontrol.c#L184">184</a>         memcg = <a href="ident?i=mem_cgroup_from_css">mem_cgroup_from_css</a>(<a href="ident?i=of_css">of_css</a>(<a href="ident?i=of">of</a>));
<a name="L185" href="source/net/ipv4/tcp_memcontrol.c#L185">185</a>         <a href="ident?i=cg_proto">cg_proto</a> = <a href="ident?i=tcp_prot">tcp_prot</a>.proto_cgroup(memcg);
<a name="L186" href="source/net/ipv4/tcp_memcontrol.c#L186">186</a>         if (!<a href="ident?i=cg_proto">cg_proto</a>)
<a name="L187" href="source/net/ipv4/tcp_memcontrol.c#L187">187</a>                 return nbytes;
<a name="L188" href="source/net/ipv4/tcp_memcontrol.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/tcp_memcontrol.c#L189">189</a>         switch (<a href="ident?i=of_cft">of_cft</a>(<a href="ident?i=of">of</a>)-&gt;<a href="ident?i=private">private</a>) {
<a name="L190" href="source/net/ipv4/tcp_memcontrol.c#L190">190</a>         case RES_MAX_USAGE:
<a name="L191" href="source/net/ipv4/tcp_memcontrol.c#L191">191</a>                 <a href="ident?i=page_counter_reset_watermark">page_counter_reset_watermark</a>(&amp;<a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated);
<a name="L192" href="source/net/ipv4/tcp_memcontrol.c#L192">192</a>                 break;
<a name="L193" href="source/net/ipv4/tcp_memcontrol.c#L193">193</a>         case RES_FAILCNT:
<a name="L194" href="source/net/ipv4/tcp_memcontrol.c#L194">194</a>                 <a href="ident?i=cg_proto">cg_proto</a>-&gt;memory_allocated.failcnt = 0;
<a name="L195" href="source/net/ipv4/tcp_memcontrol.c#L195">195</a>                 break;
<a name="L196" href="source/net/ipv4/tcp_memcontrol.c#L196">196</a>         }
<a name="L197" href="source/net/ipv4/tcp_memcontrol.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/tcp_memcontrol.c#L198">198</a>         return nbytes;
<a name="L199" href="source/net/ipv4/tcp_memcontrol.c#L199">199</a> }
<a name="L200" href="source/net/ipv4/tcp_memcontrol.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/tcp_memcontrol.c#L201">201</a> static struct <a href="ident?i=cftype">cftype</a> <a href="ident?i=tcp_files">tcp_files</a>[] = {
<a name="L202" href="source/net/ipv4/tcp_memcontrol.c#L202">202</a>         {
<a name="L203" href="source/net/ipv4/tcp_memcontrol.c#L203">203</a>                 .<a href="ident?i=name">name</a> = <i>"kmem.tcp.limit_in_bytes"</i>,
<a name="L204" href="source/net/ipv4/tcp_memcontrol.c#L204">204</a>                 .<a href="ident?i=write">write</a> = <a href="ident?i=tcp_cgroup_write">tcp_cgroup_write</a>,
<a name="L205" href="source/net/ipv4/tcp_memcontrol.c#L205">205</a>                 .read_u64 = <a href="ident?i=tcp_cgroup_read">tcp_cgroup_read</a>,
<a name="L206" href="source/net/ipv4/tcp_memcontrol.c#L206">206</a>                 .<a href="ident?i=private">private</a> = RES_LIMIT,
<a name="L207" href="source/net/ipv4/tcp_memcontrol.c#L207">207</a>         },
<a name="L208" href="source/net/ipv4/tcp_memcontrol.c#L208">208</a>         {
<a name="L209" href="source/net/ipv4/tcp_memcontrol.c#L209">209</a>                 .<a href="ident?i=name">name</a> = <i>"kmem.tcp.usage_in_bytes"</i>,
<a name="L210" href="source/net/ipv4/tcp_memcontrol.c#L210">210</a>                 .read_u64 = <a href="ident?i=tcp_cgroup_read">tcp_cgroup_read</a>,
<a name="L211" href="source/net/ipv4/tcp_memcontrol.c#L211">211</a>                 .<a href="ident?i=private">private</a> = RES_USAGE,
<a name="L212" href="source/net/ipv4/tcp_memcontrol.c#L212">212</a>         },
<a name="L213" href="source/net/ipv4/tcp_memcontrol.c#L213">213</a>         {
<a name="L214" href="source/net/ipv4/tcp_memcontrol.c#L214">214</a>                 .<a href="ident?i=name">name</a> = <i>"kmem.tcp.failcnt"</i>,
<a name="L215" href="source/net/ipv4/tcp_memcontrol.c#L215">215</a>                 .<a href="ident?i=private">private</a> = RES_FAILCNT,
<a name="L216" href="source/net/ipv4/tcp_memcontrol.c#L216">216</a>                 .<a href="ident?i=write">write</a> = <a href="ident?i=tcp_cgroup_reset">tcp_cgroup_reset</a>,
<a name="L217" href="source/net/ipv4/tcp_memcontrol.c#L217">217</a>                 .read_u64 = <a href="ident?i=tcp_cgroup_read">tcp_cgroup_read</a>,
<a name="L218" href="source/net/ipv4/tcp_memcontrol.c#L218">218</a>         },
<a name="L219" href="source/net/ipv4/tcp_memcontrol.c#L219">219</a>         {
<a name="L220" href="source/net/ipv4/tcp_memcontrol.c#L220">220</a>                 .<a href="ident?i=name">name</a> = <i>"kmem.tcp.max_usage_in_bytes"</i>,
<a name="L221" href="source/net/ipv4/tcp_memcontrol.c#L221">221</a>                 .<a href="ident?i=private">private</a> = RES_MAX_USAGE,
<a name="L222" href="source/net/ipv4/tcp_memcontrol.c#L222">222</a>                 .<a href="ident?i=write">write</a> = <a href="ident?i=tcp_cgroup_reset">tcp_cgroup_reset</a>,
<a name="L223" href="source/net/ipv4/tcp_memcontrol.c#L223">223</a>                 .read_u64 = <a href="ident?i=tcp_cgroup_read">tcp_cgroup_read</a>,
<a name="L224" href="source/net/ipv4/tcp_memcontrol.c#L224">224</a>         },
<a name="L225" href="source/net/ipv4/tcp_memcontrol.c#L225">225</a>         { }     <b><i>/* terminate */</i></b>
<a name="L226" href="source/net/ipv4/tcp_memcontrol.c#L226">226</a> };
<a name="L227" href="source/net/ipv4/tcp_memcontrol.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/tcp_memcontrol.c#L228">228</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_memcontrol_init">tcp_memcontrol_init</a>(void)
<a name="L229" href="source/net/ipv4/tcp_memcontrol.c#L229">229</a> {
<a name="L230" href="source/net/ipv4/tcp_memcontrol.c#L230">230</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=cgroup_add_legacy_cftypes">cgroup_add_legacy_cftypes</a>(&amp;<a href="ident?i=memory_cgrp_subsys">memory_cgrp_subsys</a>, <a href="ident?i=tcp_files">tcp_files</a>));
<a name="L231" href="source/net/ipv4/tcp_memcontrol.c#L231">231</a>         return 0;
<a name="L232" href="source/net/ipv4/tcp_memcontrol.c#L232">232</a> }
<a name="L233" href="source/net/ipv4/tcp_memcontrol.c#L233">233</a> <a href="ident?i=__initcall">__initcall</a>(<a href="ident?i=tcp_memcontrol_init">tcp_memcontrol_init</a>);
<a name="L234" href="source/net/ipv4/tcp_memcontrol.c#L234">234</a> </pre></div><p>
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
