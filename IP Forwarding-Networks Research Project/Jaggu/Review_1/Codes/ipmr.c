<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ipmr.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ipmr.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ipmr.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ipmr.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ipmr.c">ipmr.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ipmr.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ipmr.c#L2">2</a> <b><i> *      IP multicast routing support for mrouted 3.6/3.8</i></b>
  <a name="L3" href="source/net/ipv4/ipmr.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/ipmr.c#L4">4</a> <b><i> *              (c) 1995 Alan Cox, &lt;alan@lxorguk.ukuu.org.uk&gt;</i></b>
  <a name="L5" href="source/net/ipv4/ipmr.c#L5">5</a> <b><i> *        Linux Consultancy and Custom Driver Development</i></b>
  <a name="L6" href="source/net/ipv4/ipmr.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/ipmr.c#L7">7</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L8" href="source/net/ipv4/ipmr.c#L8">8</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L9" href="source/net/ipv4/ipmr.c#L9">9</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L10" href="source/net/ipv4/ipmr.c#L10">10</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L11" href="source/net/ipv4/ipmr.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/ipmr.c#L12">12</a> <b><i> *      Fixes:</i></b>
 <a name="L13" href="source/net/ipv4/ipmr.c#L13">13</a> <b><i> *      Michael Chastain        :       Incorrect size of copying.</i></b>
 <a name="L14" href="source/net/ipv4/ipmr.c#L14">14</a> <b><i> *      Alan Cox                :       Added the cache manager code</i></b>
 <a name="L15" href="source/net/ipv4/ipmr.c#L15">15</a> <b><i> *      Alan Cox                :       Fixed the clone/copy bug and device race.</i></b>
 <a name="L16" href="source/net/ipv4/ipmr.c#L16">16</a> <b><i> *      Mike McLagan            :       Routing by source</i></b>
 <a name="L17" href="source/net/ipv4/ipmr.c#L17">17</a> <b><i> *      Malcolm Beattie         :       Buffer handling fixes.</i></b>
 <a name="L18" href="source/net/ipv4/ipmr.c#L18">18</a> <b><i> *      Alexey Kuznetsov        :       Double buffer free and other fixes.</i></b>
 <a name="L19" href="source/net/ipv4/ipmr.c#L19">19</a> <b><i> *      SVR Anand               :       Fixed several multicast bugs and problems.</i></b>
 <a name="L20" href="source/net/ipv4/ipmr.c#L20">20</a> <b><i> *      Alexey Kuznetsov        :       Status, optimisations and more.</i></b>
 <a name="L21" href="source/net/ipv4/ipmr.c#L21">21</a> <b><i> *      Brad Parker             :       Better behaviour on mrouted upcall</i></b>
 <a name="L22" href="source/net/ipv4/ipmr.c#L22">22</a> <b><i> *                                      overflow.</i></b>
 <a name="L23" href="source/net/ipv4/ipmr.c#L23">23</a> <b><i> *      Carlos Picoto           :       PIMv1 Support</i></b>
 <a name="L24" href="source/net/ipv4/ipmr.c#L24">24</a> <b><i> *      Pavlin Ivanov Radoslavov:       PIMv2 Registers must checksum only PIM header</i></b>
 <a name="L25" href="source/net/ipv4/ipmr.c#L25">25</a> <b><i> *                                      Relax this requirement to work with older peers.</i></b>
 <a name="L26" href="source/net/ipv4/ipmr.c#L26">26</a> <b><i> *</i></b>
 <a name="L27" href="source/net/ipv4/ipmr.c#L27">27</a> <b><i> */</i></b>
 <a name="L28" href="source/net/ipv4/ipmr.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/ipmr.c#L29">29</a> #include &lt;asm/uaccess.h&gt;
 <a name="L30" href="source/net/ipv4/ipmr.c#L30">30</a> #include &lt;linux/types.h&gt;
 <a name="L31" href="source/net/ipv4/ipmr.c#L31">31</a> #include &lt;linux/capability.h&gt;
 <a name="L32" href="source/net/ipv4/ipmr.c#L32">32</a> #include &lt;linux/errno.h&gt;
 <a name="L33" href="source/net/ipv4/ipmr.c#L33">33</a> #include &lt;linux/timer.h&gt;
 <a name="L34" href="source/net/ipv4/ipmr.c#L34">34</a> #include &lt;linux/mm.h&gt;
 <a name="L35" href="source/net/ipv4/ipmr.c#L35">35</a> #include &lt;linux/kernel.h&gt;
 <a name="L36" href="source/net/ipv4/ipmr.c#L36">36</a> #include &lt;linux/fcntl.h&gt;
 <a name="L37" href="source/net/ipv4/ipmr.c#L37">37</a> #include &lt;linux/stat.h&gt;
 <a name="L38" href="source/net/ipv4/ipmr.c#L38">38</a> #include &lt;linux/socket.h&gt;
 <a name="L39" href="source/net/ipv4/ipmr.c#L39">39</a> #include &lt;linux/in.h&gt;
 <a name="L40" href="source/net/ipv4/ipmr.c#L40">40</a> #include &lt;linux/inet.h&gt;
 <a name="L41" href="source/net/ipv4/ipmr.c#L41">41</a> #include &lt;linux/netdevice.h&gt;
 <a name="L42" href="source/net/ipv4/ipmr.c#L42">42</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L43" href="source/net/ipv4/ipmr.c#L43">43</a> #include &lt;linux/igmp.h&gt;
 <a name="L44" href="source/net/ipv4/ipmr.c#L44">44</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L45" href="source/net/ipv4/ipmr.c#L45">45</a> #include &lt;linux/seq_file.h&gt;
 <a name="L46" href="source/net/ipv4/ipmr.c#L46">46</a> #include &lt;linux/mroute.h&gt;
 <a name="L47" href="source/net/ipv4/ipmr.c#L47">47</a> #include &lt;linux/init.h&gt;
 <a name="L48" href="source/net/ipv4/ipmr.c#L48">48</a> #include &lt;linux/if_ether.h&gt;
 <a name="L49" href="source/net/ipv4/ipmr.c#L49">49</a> #include &lt;linux/slab.h&gt;
 <a name="L50" href="source/net/ipv4/ipmr.c#L50">50</a> #include &lt;net/net_namespace.h&gt;
 <a name="L51" href="source/net/ipv4/ipmr.c#L51">51</a> #include &lt;net/ip.h&gt;
 <a name="L52" href="source/net/ipv4/ipmr.c#L52">52</a> #include &lt;net/protocol.h&gt;
 <a name="L53" href="source/net/ipv4/ipmr.c#L53">53</a> #include &lt;linux/skbuff.h&gt;
 <a name="L54" href="source/net/ipv4/ipmr.c#L54">54</a> #include &lt;net/route.h&gt;
 <a name="L55" href="source/net/ipv4/ipmr.c#L55">55</a> #include &lt;net/sock.h&gt;
 <a name="L56" href="source/net/ipv4/ipmr.c#L56">56</a> #include &lt;net/icmp.h&gt;
 <a name="L57" href="source/net/ipv4/ipmr.c#L57">57</a> #include &lt;net/udp.h&gt;
 <a name="L58" href="source/net/ipv4/ipmr.c#L58">58</a> #include &lt;net/raw.h&gt;
 <a name="L59" href="source/net/ipv4/ipmr.c#L59">59</a> #include &lt;linux/notifier.h&gt;
 <a name="L60" href="source/net/ipv4/ipmr.c#L60">60</a> #include &lt;linux/if_arp.h&gt;
 <a name="L61" href="source/net/ipv4/ipmr.c#L61">61</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L62" href="source/net/ipv4/ipmr.c#L62">62</a> #include &lt;linux/compat.h&gt;
 <a name="L63" href="source/net/ipv4/ipmr.c#L63">63</a> #include &lt;linux/export.h&gt;
 <a name="L64" href="source/net/ipv4/ipmr.c#L64">64</a> #include &lt;net/ip_tunnels.h&gt;
 <a name="L65" href="source/net/ipv4/ipmr.c#L65">65</a> #include &lt;net/checksum.h&gt;
 <a name="L66" href="source/net/ipv4/ipmr.c#L66">66</a> #include &lt;net/netlink.h&gt;
 <a name="L67" href="source/net/ipv4/ipmr.c#L67">67</a> #include &lt;net/fib_rules.h&gt;
 <a name="L68" href="source/net/ipv4/ipmr.c#L68">68</a> #include &lt;linux/netconf.h&gt;
 <a name="L69" href="source/net/ipv4/ipmr.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/ipmr.c#L70">70</a> #if defined(CONFIG_IP_PIMSM_V1) || defined(CONFIG_IP_PIMSM_V2)
 <a name="L71" href="source/net/ipv4/ipmr.c#L71">71</a> #define <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a> 1
 <a name="L72" href="source/net/ipv4/ipmr.c#L72">72</a> #endif
 <a name="L73" href="source/net/ipv4/ipmr.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/ipmr.c#L74">74</a> struct <a href="ident?i=mr_table">mr_table</a> {
 <a name="L75" href="source/net/ipv4/ipmr.c#L75">75</a>         struct <a href="ident?i=list_head">list_head</a>        <a href="ident?i=list">list</a>;
 <a name="L76" href="source/net/ipv4/ipmr.c#L76">76</a>         <a href="ident?i=possible_net_t">possible_net_t</a>          <a href="ident?i=net">net</a>;
 <a name="L77" href="source/net/ipv4/ipmr.c#L77">77</a>         <a href="ident?i=u32">u32</a>                     <a href="ident?i=id">id</a>;
 <a name="L78" href="source/net/ipv4/ipmr.c#L78">78</a>         struct <a href="ident?i=sock">sock</a> <a href="ident?i=__rcu">__rcu</a>       *mroute_sk;
 <a name="L79" href="source/net/ipv4/ipmr.c#L79">79</a>         struct <a href="ident?i=timer_list">timer_list</a>       ipmr_expire_timer;
 <a name="L80" href="source/net/ipv4/ipmr.c#L80">80</a>         struct <a href="ident?i=list_head">list_head</a>        mfc_unres_queue;
 <a name="L81" href="source/net/ipv4/ipmr.c#L81">81</a>         struct <a href="ident?i=list_head">list_head</a>        mfc_cache_array[<a href="ident?i=MFC_LINES">MFC_LINES</a>];
 <a name="L82" href="source/net/ipv4/ipmr.c#L82">82</a>         struct <a href="ident?i=vif_device">vif_device</a>       vif_table[<a href="ident?i=MAXVIFS">MAXVIFS</a>];
 <a name="L83" href="source/net/ipv4/ipmr.c#L83">83</a>         int                     maxvif;
 <a name="L84" href="source/net/ipv4/ipmr.c#L84">84</a>         <a href="ident?i=atomic_t">atomic_t</a>                cache_resolve_queue_len;
 <a name="L85" href="source/net/ipv4/ipmr.c#L85">85</a>         <a href="ident?i=bool">bool</a>                    mroute_do_assert;
 <a name="L86" href="source/net/ipv4/ipmr.c#L86">86</a>         <a href="ident?i=bool">bool</a>                    mroute_do_pim;
 <a name="L87" href="source/net/ipv4/ipmr.c#L87">87</a> #if defined(CONFIG_IP_PIMSM_V1) || defined(CONFIG_IP_PIMSM_V2)
 <a name="L88" href="source/net/ipv4/ipmr.c#L88">88</a>         int                     mroute_reg_vif_num;
 <a name="L89" href="source/net/ipv4/ipmr.c#L89">89</a> #endif
 <a name="L90" href="source/net/ipv4/ipmr.c#L90">90</a> };
 <a name="L91" href="source/net/ipv4/ipmr.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/ipmr.c#L92">92</a> struct <a href="ident?i=ipmr_rule">ipmr_rule</a> {
 <a name="L93" href="source/net/ipv4/ipmr.c#L93">93</a>         struct <a href="ident?i=fib_rule">fib_rule</a>         <a href="ident?i=common">common</a>;
 <a name="L94" href="source/net/ipv4/ipmr.c#L94">94</a> };
 <a name="L95" href="source/net/ipv4/ipmr.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/ipmr.c#L96">96</a> struct <a href="ident?i=ipmr_result">ipmr_result</a> {
 <a name="L97" href="source/net/ipv4/ipmr.c#L97">97</a>         struct <a href="ident?i=mr_table">mr_table</a>         *mrt;
 <a name="L98" href="source/net/ipv4/ipmr.c#L98">98</a> };
 <a name="L99" href="source/net/ipv4/ipmr.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/ipmr.c#L100">100</a> <b><i>/* Big lock, protecting vif table, mrt cache and mroute socket state.</i></b>
<a name="L101" href="source/net/ipv4/ipmr.c#L101">101</a> <b><i> * Note that the changes are semaphored via rtnl_lock.</i></b>
<a name="L102" href="source/net/ipv4/ipmr.c#L102">102</a> <b><i> */</i></b>
<a name="L103" href="source/net/ipv4/ipmr.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/ipmr.c#L104">104</a> static <a href="ident?i=DEFINE_RWLOCK">DEFINE_RWLOCK</a>(mrt_lock);
<a name="L105" href="source/net/ipv4/ipmr.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/ipmr.c#L106">106</a> <b><i>/*</i></b>
<a name="L107" href="source/net/ipv4/ipmr.c#L107">107</a> <b><i> *      Multicast router control variables</i></b>
<a name="L108" href="source/net/ipv4/ipmr.c#L108">108</a> <b><i> */</i></b>
<a name="L109" href="source/net/ipv4/ipmr.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/ipmr.c#L110">110</a> #define <a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(_mrt, _idx) ((_mrt)-&gt;vif_table[_idx].<a href="ident?i=dev">dev</a> != <a href="ident?i=NULL">NULL</a>)
<a name="L111" href="source/net/ipv4/ipmr.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/ipmr.c#L112">112</a> <b><i>/* Special spinlock for queue of unresolved entries */</i></b>
<a name="L113" href="source/net/ipv4/ipmr.c#L113">113</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(mfc_unres_lock);
<a name="L114" href="source/net/ipv4/ipmr.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/ipmr.c#L115">115</a> <b><i>/* We return to original Alan's scheme. Hash table of resolved</i></b>
<a name="L116" href="source/net/ipv4/ipmr.c#L116">116</a> <b><i> * entries is changed only in process context and protected</i></b>
<a name="L117" href="source/net/ipv4/ipmr.c#L117">117</a> <b><i> * with weak lock mrt_lock. Queue of unresolved entries is protected</i></b>
<a name="L118" href="source/net/ipv4/ipmr.c#L118">118</a> <b><i> * with strong spinlock mfc_unres_lock.</i></b>
<a name="L119" href="source/net/ipv4/ipmr.c#L119">119</a> <b><i> *</i></b>
<a name="L120" href="source/net/ipv4/ipmr.c#L120">120</a> <b><i> * In this case data path is free of exclusive locks at all.</i></b>
<a name="L121" href="source/net/ipv4/ipmr.c#L121">121</a> <b><i> */</i></b>
<a name="L122" href="source/net/ipv4/ipmr.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/ipmr.c#L123">123</a> static struct <a href="ident?i=kmem_cache">kmem_cache</a> *mrt_cachep <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L124" href="source/net/ipv4/ipmr.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/ipmr.c#L125">125</a> static struct <a href="ident?i=mr_table">mr_table</a> *<a href="ident?i=ipmr_new_table">ipmr_new_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>);
<a name="L126" href="source/net/ipv4/ipmr.c#L126">126</a> static void <a href="ident?i=ipmr_free_table">ipmr_free_table</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt);
<a name="L127" href="source/net/ipv4/ipmr.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/ipmr.c#L128">128</a> static void <a href="ident?i=ip_mr_forward">ip_mr_forward</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L129" href="source/net/ipv4/ipmr.c#L129">129</a>                           struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=cache">cache</a>,
<a name="L130" href="source/net/ipv4/ipmr.c#L130">130</a>                           int local);
<a name="L131" href="source/net/ipv4/ipmr.c#L131">131</a> static int <a href="ident?i=ipmr_cache_report">ipmr_cache_report</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L132" href="source/net/ipv4/ipmr.c#L132">132</a>                              struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=pkt">pkt</a>, <a href="ident?i=vifi_t">vifi_t</a> vifi, int <a href="ident?i=assert">assert</a>);
<a name="L133" href="source/net/ipv4/ipmr.c#L133">133</a> static int <a href="ident?i=__ipmr_fill_mroute">__ipmr_fill_mroute</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L134" href="source/net/ipv4/ipmr.c#L134">134</a>                               struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, struct <a href="ident?i=rtmsg">rtmsg</a> *rtm);
<a name="L135" href="source/net/ipv4/ipmr.c#L135">135</a> static void <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=mfc_cache">mfc_cache</a> *mfc,
<a name="L136" href="source/net/ipv4/ipmr.c#L136">136</a>                                  int <a href="ident?i=cmd">cmd</a>);
<a name="L137" href="source/net/ipv4/ipmr.c#L137">137</a> static void <a href="ident?i=mroute_clean_tables">mroute_clean_tables</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt);
<a name="L138" href="source/net/ipv4/ipmr.c#L138">138</a> static void <a href="ident?i=ipmr_expire_process">ipmr_expire_process</a>(unsigned long <a href="ident?i=arg">arg</a>);
<a name="L139" href="source/net/ipv4/ipmr.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/ipmr.c#L140">140</a> #ifdef CONFIG_IP_MROUTE_MULTIPLE_TABLES
<a name="L141" href="source/net/ipv4/ipmr.c#L141">141</a> #define <a href="ident?i=ipmr_for_each_table">ipmr_for_each_table</a>(mrt, <a href="ident?i=net">net</a>) \
<a name="L142" href="source/net/ipv4/ipmr.c#L142">142</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(mrt, &amp;<a href="ident?i=net">net</a>-&gt;ipv4.mr_tables, <a href="ident?i=list">list</a>)
<a name="L143" href="source/net/ipv4/ipmr.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/ipmr.c#L144">144</a> static struct <a href="ident?i=mr_table">mr_table</a> *<a href="ident?i=ipmr_get_table">ipmr_get_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>)
<a name="L145" href="source/net/ipv4/ipmr.c#L145">145</a> {
<a name="L146" href="source/net/ipv4/ipmr.c#L146">146</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L147" href="source/net/ipv4/ipmr.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/ipmr.c#L148">148</a>         <a href="ident?i=ipmr_for_each_table">ipmr_for_each_table</a>(mrt, <a href="ident?i=net">net</a>) {
<a name="L149" href="source/net/ipv4/ipmr.c#L149">149</a>                 if (mrt-&gt;<a href="ident?i=id">id</a> == <a href="ident?i=id">id</a>)
<a name="L150" href="source/net/ipv4/ipmr.c#L150">150</a>                         return mrt;
<a name="L151" href="source/net/ipv4/ipmr.c#L151">151</a>         }
<a name="L152" href="source/net/ipv4/ipmr.c#L152">152</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L153" href="source/net/ipv4/ipmr.c#L153">153</a> }
<a name="L154" href="source/net/ipv4/ipmr.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/ipmr.c#L155">155</a> static int <a href="ident?i=ipmr_fib_lookup">ipmr_fib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=flowi4">flowi4</a> *flp4,
<a name="L156" href="source/net/ipv4/ipmr.c#L156">156</a>                            struct <a href="ident?i=mr_table">mr_table</a> **mrt)
<a name="L157" href="source/net/ipv4/ipmr.c#L157">157</a> {
<a name="L158" href="source/net/ipv4/ipmr.c#L158">158</a>         int <a href="ident?i=err">err</a>;
<a name="L159" href="source/net/ipv4/ipmr.c#L159">159</a>         struct <a href="ident?i=ipmr_result">ipmr_result</a> <a href="ident?i=res">res</a>;
<a name="L160" href="source/net/ipv4/ipmr.c#L160">160</a>         struct <a href="ident?i=fib_lookup_arg">fib_lookup_arg</a> <a href="ident?i=arg">arg</a> = {
<a name="L161" href="source/net/ipv4/ipmr.c#L161">161</a>                 .<a href="ident?i=result">result</a> = &amp;<a href="ident?i=res">res</a>,
<a name="L162" href="source/net/ipv4/ipmr.c#L162">162</a>                 .<a href="ident?i=flags">flags</a> = <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>,
<a name="L163" href="source/net/ipv4/ipmr.c#L163">163</a>         };
<a name="L164" href="source/net/ipv4/ipmr.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/ipmr.c#L165">165</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_rules_lookup">fib_rules_lookup</a>(<a href="ident?i=net">net</a>-&gt;ipv4.mr_rules_ops,
<a name="L166" href="source/net/ipv4/ipmr.c#L166">166</a>                                <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(flp4), 0, &amp;<a href="ident?i=arg">arg</a>);
<a name="L167" href="source/net/ipv4/ipmr.c#L167">167</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L168" href="source/net/ipv4/ipmr.c#L168">168</a>                 return <a href="ident?i=err">err</a>;
<a name="L169" href="source/net/ipv4/ipmr.c#L169">169</a>         *mrt = <a href="ident?i=res">res</a>.mrt;
<a name="L170" href="source/net/ipv4/ipmr.c#L170">170</a>         return 0;
<a name="L171" href="source/net/ipv4/ipmr.c#L171">171</a> }
<a name="L172" href="source/net/ipv4/ipmr.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/ipmr.c#L173">173</a> static int <a href="ident?i=ipmr_rule_action">ipmr_rule_action</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=flowi">flowi</a> *flp,
<a name="L174" href="source/net/ipv4/ipmr.c#L174">174</a>                             int <a href="ident?i=flags">flags</a>, struct <a href="ident?i=fib_lookup_arg">fib_lookup_arg</a> *<a href="ident?i=arg">arg</a>)
<a name="L175" href="source/net/ipv4/ipmr.c#L175">175</a> {
<a name="L176" href="source/net/ipv4/ipmr.c#L176">176</a>         struct <a href="ident?i=ipmr_result">ipmr_result</a> *<a href="ident?i=res">res</a> = <a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=result">result</a>;
<a name="L177" href="source/net/ipv4/ipmr.c#L177">177</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L178" href="source/net/ipv4/ipmr.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/ipmr.c#L179">179</a>         switch (rule-&gt;<a href="ident?i=action">action</a>) {
<a name="L180" href="source/net/ipv4/ipmr.c#L180">180</a>         case FR_ACT_TO_TBL:
<a name="L181" href="source/net/ipv4/ipmr.c#L181">181</a>                 break;
<a name="L182" href="source/net/ipv4/ipmr.c#L182">182</a>         case FR_ACT_UNREACHABLE:
<a name="L183" href="source/net/ipv4/ipmr.c#L183">183</a>                 return -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>;
<a name="L184" href="source/net/ipv4/ipmr.c#L184">184</a>         case FR_ACT_PROHIBIT:
<a name="L185" href="source/net/ipv4/ipmr.c#L185">185</a>                 return -<a href="ident?i=EACCES">EACCES</a>;
<a name="L186" href="source/net/ipv4/ipmr.c#L186">186</a>         case FR_ACT_BLACKHOLE:
<a name="L187" href="source/net/ipv4/ipmr.c#L187">187</a>         default:
<a name="L188" href="source/net/ipv4/ipmr.c#L188">188</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L189" href="source/net/ipv4/ipmr.c#L189">189</a>         }
<a name="L190" href="source/net/ipv4/ipmr.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/ipmr.c#L191">191</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(rule-&gt;fr_net, rule-&gt;<a href="ident?i=table">table</a>);
<a name="L192" href="source/net/ipv4/ipmr.c#L192">192</a>         if (!mrt)
<a name="L193" href="source/net/ipv4/ipmr.c#L193">193</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L194" href="source/net/ipv4/ipmr.c#L194">194</a>         <a href="ident?i=res">res</a>-&gt;mrt = mrt;
<a name="L195" href="source/net/ipv4/ipmr.c#L195">195</a>         return 0;
<a name="L196" href="source/net/ipv4/ipmr.c#L196">196</a> }
<a name="L197" href="source/net/ipv4/ipmr.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/ipmr.c#L198">198</a> static int <a href="ident?i=ipmr_rule_match">ipmr_rule_match</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=flowi">flowi</a> *fl, int <a href="ident?i=flags">flags</a>)
<a name="L199" href="source/net/ipv4/ipmr.c#L199">199</a> {
<a name="L200" href="source/net/ipv4/ipmr.c#L200">200</a>         return 1;
<a name="L201" href="source/net/ipv4/ipmr.c#L201">201</a> }
<a name="L202" href="source/net/ipv4/ipmr.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/ipmr.c#L203">203</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=ipmr_rule_policy">ipmr_rule_policy</a>[<a href="ident?i=FRA_MAX">FRA_MAX</a> + 1] = {
<a name="L204" href="source/net/ipv4/ipmr.c#L204">204</a>         <a href="ident?i=FRA_GENERIC_POLICY">FRA_GENERIC_POLICY</a>,
<a name="L205" href="source/net/ipv4/ipmr.c#L205">205</a> };
<a name="L206" href="source/net/ipv4/ipmr.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/ipmr.c#L207">207</a> static int <a href="ident?i=ipmr_rule_configure">ipmr_rule_configure</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L208" href="source/net/ipv4/ipmr.c#L208">208</a>                                struct <a href="ident?i=fib_rule_hdr">fib_rule_hdr</a> *frh, struct <a href="ident?i=nlattr">nlattr</a> **<a href="ident?i=tb">tb</a>)
<a name="L209" href="source/net/ipv4/ipmr.c#L209">209</a> {
<a name="L210" href="source/net/ipv4/ipmr.c#L210">210</a>         return 0;
<a name="L211" href="source/net/ipv4/ipmr.c#L211">211</a> }
<a name="L212" href="source/net/ipv4/ipmr.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/ipmr.c#L213">213</a> static int <a href="ident?i=ipmr_rule_compare">ipmr_rule_compare</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=fib_rule_hdr">fib_rule_hdr</a> *frh,
<a name="L214" href="source/net/ipv4/ipmr.c#L214">214</a>                              struct <a href="ident?i=nlattr">nlattr</a> **<a href="ident?i=tb">tb</a>)
<a name="L215" href="source/net/ipv4/ipmr.c#L215">215</a> {
<a name="L216" href="source/net/ipv4/ipmr.c#L216">216</a>         return 1;
<a name="L217" href="source/net/ipv4/ipmr.c#L217">217</a> }
<a name="L218" href="source/net/ipv4/ipmr.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/ipmr.c#L219">219</a> static int <a href="ident?i=ipmr_rule_fill">ipmr_rule_fill</a>(struct <a href="ident?i=fib_rule">fib_rule</a> *rule, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L220" href="source/net/ipv4/ipmr.c#L220">220</a>                           struct <a href="ident?i=fib_rule_hdr">fib_rule_hdr</a> *frh)
<a name="L221" href="source/net/ipv4/ipmr.c#L221">221</a> {
<a name="L222" href="source/net/ipv4/ipmr.c#L222">222</a>         frh-&gt;dst_len = 0;
<a name="L223" href="source/net/ipv4/ipmr.c#L223">223</a>         frh-&gt;src_len = 0;
<a name="L224" href="source/net/ipv4/ipmr.c#L224">224</a>         frh-&gt;tos     = 0;
<a name="L225" href="source/net/ipv4/ipmr.c#L225">225</a>         return 0;
<a name="L226" href="source/net/ipv4/ipmr.c#L226">226</a> }
<a name="L227" href="source/net/ipv4/ipmr.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/ipmr.c#L228">228</a> static const struct <a href="ident?i=fib_rules_ops">fib_rules_ops</a> <a href="ident?i=__net_initconst">__net_initconst</a> <a href="ident?i=ipmr_rules_ops_template">ipmr_rules_ops_template</a> = {
<a name="L229" href="source/net/ipv4/ipmr.c#L229">229</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=RTNL_FAMILY_IPMR">RTNL_FAMILY_IPMR</a>,
<a name="L230" href="source/net/ipv4/ipmr.c#L230">230</a>         .rule_size      = sizeof(struct <a href="ident?i=ipmr_rule">ipmr_rule</a>),
<a name="L231" href="source/net/ipv4/ipmr.c#L231">231</a>         .addr_size      = sizeof(<a href="ident?i=u32">u32</a>),
<a name="L232" href="source/net/ipv4/ipmr.c#L232">232</a>         .<a href="ident?i=action">action</a>         = <a href="ident?i=ipmr_rule_action">ipmr_rule_action</a>,
<a name="L233" href="source/net/ipv4/ipmr.c#L233">233</a>         .<a href="ident?i=match">match</a>          = <a href="ident?i=ipmr_rule_match">ipmr_rule_match</a>,
<a name="L234" href="source/net/ipv4/ipmr.c#L234">234</a>         .<a href="ident?i=configure">configure</a>      = <a href="ident?i=ipmr_rule_configure">ipmr_rule_configure</a>,
<a name="L235" href="source/net/ipv4/ipmr.c#L235">235</a>         .<a href="ident?i=compare">compare</a>        = <a href="ident?i=ipmr_rule_compare">ipmr_rule_compare</a>,
<a name="L236" href="source/net/ipv4/ipmr.c#L236">236</a>         .default_pref   = <a href="ident?i=fib_default_rule_pref">fib_default_rule_pref</a>,
<a name="L237" href="source/net/ipv4/ipmr.c#L237">237</a>         .<a href="ident?i=fill">fill</a>           = <a href="ident?i=ipmr_rule_fill">ipmr_rule_fill</a>,
<a name="L238" href="source/net/ipv4/ipmr.c#L238">238</a>         .nlgroup        = <a href="ident?i=RTNLGRP_IPV4_RULE">RTNLGRP_IPV4_RULE</a>,
<a name="L239" href="source/net/ipv4/ipmr.c#L239">239</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=ipmr_rule_policy">ipmr_rule_policy</a>,
<a name="L240" href="source/net/ipv4/ipmr.c#L240">240</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L241" href="source/net/ipv4/ipmr.c#L241">241</a> };
<a name="L242" href="source/net/ipv4/ipmr.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/ipmr.c#L243">243</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipmr_rules_init">ipmr_rules_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L244" href="source/net/ipv4/ipmr.c#L244">244</a> {
<a name="L245" href="source/net/ipv4/ipmr.c#L245">245</a>         struct <a href="ident?i=fib_rules_ops">fib_rules_ops</a> *<a href="ident?i=ops">ops</a>;
<a name="L246" href="source/net/ipv4/ipmr.c#L246">246</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L247" href="source/net/ipv4/ipmr.c#L247">247</a>         int <a href="ident?i=err">err</a>;
<a name="L248" href="source/net/ipv4/ipmr.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/ipmr.c#L249">249</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=fib_rules_register">fib_rules_register</a>(&amp;<a href="ident?i=ipmr_rules_ops_template">ipmr_rules_ops_template</a>, <a href="ident?i=net">net</a>);
<a name="L250" href="source/net/ipv4/ipmr.c#L250">250</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=ops">ops</a>))
<a name="L251" href="source/net/ipv4/ipmr.c#L251">251</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=ops">ops</a>);
<a name="L252" href="source/net/ipv4/ipmr.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/ipmr.c#L253">253</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.mr_tables);
<a name="L254" href="source/net/ipv4/ipmr.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/ipmr.c#L255">255</a>         mrt = <a href="ident?i=ipmr_new_table">ipmr_new_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_DEFAULT);
<a name="L256" href="source/net/ipv4/ipmr.c#L256">256</a>         if (!mrt) {
<a name="L257" href="source/net/ipv4/ipmr.c#L257">257</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L258" href="source/net/ipv4/ipmr.c#L258">258</a>                 goto err1;
<a name="L259" href="source/net/ipv4/ipmr.c#L259">259</a>         }
<a name="L260" href="source/net/ipv4/ipmr.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/ipmr.c#L261">261</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_default_rule_add">fib_default_rule_add</a>(<a href="ident?i=ops">ops</a>, 0x7fff, RT_TABLE_DEFAULT, 0);
<a name="L262" href="source/net/ipv4/ipmr.c#L262">262</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L263" href="source/net/ipv4/ipmr.c#L263">263</a>                 goto err2;
<a name="L264" href="source/net/ipv4/ipmr.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/ipmr.c#L265">265</a>         <a href="ident?i=net">net</a>-&gt;ipv4.mr_rules_ops = <a href="ident?i=ops">ops</a>;
<a name="L266" href="source/net/ipv4/ipmr.c#L266">266</a>         return 0;
<a name="L267" href="source/net/ipv4/ipmr.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/ipmr.c#L268">268</a> err2:
<a name="L269" href="source/net/ipv4/ipmr.c#L269">269</a>         <a href="ident?i=ipmr_free_table">ipmr_free_table</a>(mrt);
<a name="L270" href="source/net/ipv4/ipmr.c#L270">270</a> err1:
<a name="L271" href="source/net/ipv4/ipmr.c#L271">271</a>         <a href="ident?i=fib_rules_unregister">fib_rules_unregister</a>(<a href="ident?i=ops">ops</a>);
<a name="L272" href="source/net/ipv4/ipmr.c#L272">272</a>         return <a href="ident?i=err">err</a>;
<a name="L273" href="source/net/ipv4/ipmr.c#L273">273</a> }
<a name="L274" href="source/net/ipv4/ipmr.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/ipmr.c#L275">275</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipmr_rules_exit">ipmr_rules_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L276" href="source/net/ipv4/ipmr.c#L276">276</a> {
<a name="L277" href="source/net/ipv4/ipmr.c#L277">277</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt, *<a href="ident?i=next">next</a>;
<a name="L278" href="source/net/ipv4/ipmr.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/ipmr.c#L279">279</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L280" href="source/net/ipv4/ipmr.c#L280">280</a>         <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(mrt, <a href="ident?i=next">next</a>, &amp;<a href="ident?i=net">net</a>-&gt;ipv4.mr_tables, <a href="ident?i=list">list</a>) {
<a name="L281" href="source/net/ipv4/ipmr.c#L281">281</a>                 <a href="ident?i=list_del">list_del</a>(&amp;mrt-&gt;<a href="ident?i=list">list</a>);
<a name="L282" href="source/net/ipv4/ipmr.c#L282">282</a>                 <a href="ident?i=ipmr_free_table">ipmr_free_table</a>(mrt);
<a name="L283" href="source/net/ipv4/ipmr.c#L283">283</a>         }
<a name="L284" href="source/net/ipv4/ipmr.c#L284">284</a>         <a href="ident?i=fib_rules_unregister">fib_rules_unregister</a>(<a href="ident?i=net">net</a>-&gt;ipv4.mr_rules_ops);
<a name="L285" href="source/net/ipv4/ipmr.c#L285">285</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L286" href="source/net/ipv4/ipmr.c#L286">286</a> }
<a name="L287" href="source/net/ipv4/ipmr.c#L287">287</a> #else
<a name="L288" href="source/net/ipv4/ipmr.c#L288">288</a> #define <a href="ident?i=ipmr_for_each_table">ipmr_for_each_table</a>(mrt, <a href="ident?i=net">net</a>) \
<a name="L289" href="source/net/ipv4/ipmr.c#L289">289</a>         for (mrt = <a href="ident?i=net">net</a>-&gt;ipv4.mrt; mrt; mrt = <a href="ident?i=NULL">NULL</a>)
<a name="L290" href="source/net/ipv4/ipmr.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/ipmr.c#L291">291</a> static struct <a href="ident?i=mr_table">mr_table</a> *<a href="ident?i=ipmr_get_table">ipmr_get_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>)
<a name="L292" href="source/net/ipv4/ipmr.c#L292">292</a> {
<a name="L293" href="source/net/ipv4/ipmr.c#L293">293</a>         return <a href="ident?i=net">net</a>-&gt;ipv4.mrt;
<a name="L294" href="source/net/ipv4/ipmr.c#L294">294</a> }
<a name="L295" href="source/net/ipv4/ipmr.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/ipmr.c#L296">296</a> static int <a href="ident?i=ipmr_fib_lookup">ipmr_fib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=flowi4">flowi4</a> *flp4,
<a name="L297" href="source/net/ipv4/ipmr.c#L297">297</a>                            struct <a href="ident?i=mr_table">mr_table</a> **mrt)
<a name="L298" href="source/net/ipv4/ipmr.c#L298">298</a> {
<a name="L299" href="source/net/ipv4/ipmr.c#L299">299</a>         *mrt = <a href="ident?i=net">net</a>-&gt;ipv4.mrt;
<a name="L300" href="source/net/ipv4/ipmr.c#L300">300</a>         return 0;
<a name="L301" href="source/net/ipv4/ipmr.c#L301">301</a> }
<a name="L302" href="source/net/ipv4/ipmr.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/ipmr.c#L303">303</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipmr_rules_init">ipmr_rules_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L304" href="source/net/ipv4/ipmr.c#L304">304</a> {
<a name="L305" href="source/net/ipv4/ipmr.c#L305">305</a>         <a href="ident?i=net">net</a>-&gt;ipv4.mrt = <a href="ident?i=ipmr_new_table">ipmr_new_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_DEFAULT);
<a name="L306" href="source/net/ipv4/ipmr.c#L306">306</a>         return <a href="ident?i=net">net</a>-&gt;ipv4.mrt ? 0 : -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L307" href="source/net/ipv4/ipmr.c#L307">307</a> }
<a name="L308" href="source/net/ipv4/ipmr.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/ipmr.c#L309">309</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipmr_rules_exit">ipmr_rules_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L310" href="source/net/ipv4/ipmr.c#L310">310</a> {
<a name="L311" href="source/net/ipv4/ipmr.c#L311">311</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L312" href="source/net/ipv4/ipmr.c#L312">312</a>         <a href="ident?i=ipmr_free_table">ipmr_free_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.mrt);
<a name="L313" href="source/net/ipv4/ipmr.c#L313">313</a>         <a href="ident?i=net">net</a>-&gt;ipv4.mrt = <a href="ident?i=NULL">NULL</a>;
<a name="L314" href="source/net/ipv4/ipmr.c#L314">314</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L315" href="source/net/ipv4/ipmr.c#L315">315</a> }
<a name="L316" href="source/net/ipv4/ipmr.c#L316">316</a> #endif
<a name="L317" href="source/net/ipv4/ipmr.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/ipmr.c#L318">318</a> static struct <a href="ident?i=mr_table">mr_table</a> *<a href="ident?i=ipmr_new_table">ipmr_new_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>)
<a name="L319" href="source/net/ipv4/ipmr.c#L319">319</a> {
<a name="L320" href="source/net/ipv4/ipmr.c#L320">320</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L321" href="source/net/ipv4/ipmr.c#L321">321</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L322" href="source/net/ipv4/ipmr.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/ipmr.c#L323">323</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=id">id</a>);
<a name="L324" href="source/net/ipv4/ipmr.c#L324">324</a>         if (mrt)
<a name="L325" href="source/net/ipv4/ipmr.c#L325">325</a>                 return mrt;
<a name="L326" href="source/net/ipv4/ipmr.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/ipmr.c#L327">327</a>         mrt = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*mrt), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L328" href="source/net/ipv4/ipmr.c#L328">328</a>         if (!mrt)
<a name="L329" href="source/net/ipv4/ipmr.c#L329">329</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L330" href="source/net/ipv4/ipmr.c#L330">330</a>         <a href="ident?i=write_pnet">write_pnet</a>(&amp;mrt-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=net">net</a>);
<a name="L331" href="source/net/ipv4/ipmr.c#L331">331</a>         mrt-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=id">id</a>;
<a name="L332" href="source/net/ipv4/ipmr.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/ipmr.c#L333">333</a>         <b><i>/* Forwarding cache */</i></b>
<a name="L334" href="source/net/ipv4/ipmr.c#L334">334</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=MFC_LINES">MFC_LINES</a>; <a href="ident?i=i">i</a>++)
<a name="L335" href="source/net/ipv4/ipmr.c#L335">335</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;mrt-&gt;mfc_cache_array[<a href="ident?i=i">i</a>]);
<a name="L336" href="source/net/ipv4/ipmr.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/ipmr.c#L337">337</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;mrt-&gt;mfc_unres_queue);
<a name="L338" href="source/net/ipv4/ipmr.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/ipmr.c#L339">339</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;mrt-&gt;ipmr_expire_timer, <a href="ident?i=ipmr_expire_process">ipmr_expire_process</a>,
<a name="L340" href="source/net/ipv4/ipmr.c#L340">340</a>                     (unsigned long)mrt);
<a name="L341" href="source/net/ipv4/ipmr.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/ipmr.c#L342">342</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L343" href="source/net/ipv4/ipmr.c#L343">343</a>         mrt-&gt;mroute_reg_vif_num = -1;
<a name="L344" href="source/net/ipv4/ipmr.c#L344">344</a> #endif
<a name="L345" href="source/net/ipv4/ipmr.c#L345">345</a> #ifdef CONFIG_IP_MROUTE_MULTIPLE_TABLES
<a name="L346" href="source/net/ipv4/ipmr.c#L346">346</a>         <a href="ident?i=list_add_tail_rcu">list_add_tail_rcu</a>(&amp;mrt-&gt;<a href="ident?i=list">list</a>, &amp;<a href="ident?i=net">net</a>-&gt;ipv4.mr_tables);
<a name="L347" href="source/net/ipv4/ipmr.c#L347">347</a> #endif
<a name="L348" href="source/net/ipv4/ipmr.c#L348">348</a>         return mrt;
<a name="L349" href="source/net/ipv4/ipmr.c#L349">349</a> }
<a name="L350" href="source/net/ipv4/ipmr.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/ipmr.c#L351">351</a> static void <a href="ident?i=ipmr_free_table">ipmr_free_table</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt)
<a name="L352" href="source/net/ipv4/ipmr.c#L352">352</a> {
<a name="L353" href="source/net/ipv4/ipmr.c#L353">353</a>         <a href="ident?i=del_timer_sync">del_timer_sync</a>(&amp;mrt-&gt;ipmr_expire_timer);
<a name="L354" href="source/net/ipv4/ipmr.c#L354">354</a>         <a href="ident?i=mroute_clean_tables">mroute_clean_tables</a>(mrt);
<a name="L355" href="source/net/ipv4/ipmr.c#L355">355</a>         <a href="ident?i=kfree">kfree</a>(mrt);
<a name="L356" href="source/net/ipv4/ipmr.c#L356">356</a> }
<a name="L357" href="source/net/ipv4/ipmr.c#L357">357</a> 
<a name="L358" href="source/net/ipv4/ipmr.c#L358">358</a> <b><i>/* Service routines creating virtual interfaces: DVMRP tunnels and PIMREG */</i></b>
<a name="L359" href="source/net/ipv4/ipmr.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/ipmr.c#L360">360</a> static void <a href="ident?i=ipmr_del_tunnel">ipmr_del_tunnel</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=vifctl">vifctl</a> *<a href="ident?i=v">v</a>)
<a name="L361" href="source/net/ipv4/ipmr.c#L361">361</a> {
<a name="L362" href="source/net/ipv4/ipmr.c#L362">362</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L363" href="source/net/ipv4/ipmr.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/ipmr.c#L364">364</a>         <a href="ident?i=dev_close">dev_close</a>(<a href="ident?i=dev">dev</a>);
<a name="L365" href="source/net/ipv4/ipmr.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/ipmr.c#L366">366</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_name">__dev_get_by_name</a>(<a href="ident?i=net">net</a>, <i>"tunl0"</i>);
<a name="L367" href="source/net/ipv4/ipmr.c#L367">367</a>         if (<a href="ident?i=dev">dev</a>) {
<a name="L368" href="source/net/ipv4/ipmr.c#L368">368</a>                 const struct <a href="ident?i=net_device_ops">net_device_ops</a> *<a href="ident?i=ops">ops</a> = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>;
<a name="L369" href="source/net/ipv4/ipmr.c#L369">369</a>                 struct <a href="ident?i=ifreq">ifreq</a> ifr;
<a name="L370" href="source/net/ipv4/ipmr.c#L370">370</a>                 struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L371" href="source/net/ipv4/ipmr.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/ipmr.c#L372">372</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=p">p</a>, 0, sizeof(<a href="ident?i=p">p</a>));
<a name="L373" href="source/net/ipv4/ipmr.c#L373">373</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=v">v</a>-&gt;vifc_rmt_addr.s_addr;
<a name="L374" href="source/net/ipv4/ipmr.c#L374">374</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=v">v</a>-&gt;vifc_lcl_addr.s_addr;
<a name="L375" href="source/net/ipv4/ipmr.c#L375">375</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=version">version</a> = 4;
<a name="L376" href="source/net/ipv4/ipmr.c#L376">376</a>                 <a href="ident?i=p">p</a>.iph.ihl = 5;
<a name="L377" href="source/net/ipv4/ipmr.c#L377">377</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L378" href="source/net/ipv4/ipmr.c#L378">378</a>                 <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=p">p</a>.<a href="ident?i=name">name</a>, <i>"dvmrp%d"</i>, <a href="ident?i=v">v</a>-&gt;vifc_vifi);
<a name="L379" href="source/net/ipv4/ipmr.c#L379">379</a>                 ifr.ifr_ifru.ifru_data = (<a href="ident?i=__force">__force</a> void <a href="ident?i=__user">__user</a> *)&amp;<a href="ident?i=p">p</a>;
<a name="L380" href="source/net/ipv4/ipmr.c#L380">380</a> 
<a name="L381" href="source/net/ipv4/ipmr.c#L381">381</a>                 if (<a href="ident?i=ops">ops</a>-&gt;ndo_do_ioctl) {
<a name="L382" href="source/net/ipv4/ipmr.c#L382">382</a>                         <a href="ident?i=mm_segment_t">mm_segment_t</a> oldfs = <a href="ident?i=get_fs">get_fs</a>();
<a name="L383" href="source/net/ipv4/ipmr.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/ipmr.c#L384">384</a>                         <a href="ident?i=set_fs">set_fs</a>(<a href="ident?i=KERNEL_DS">KERNEL_DS</a>);
<a name="L385" href="source/net/ipv4/ipmr.c#L385">385</a>                         <a href="ident?i=ops">ops</a>-&gt;ndo_do_ioctl(<a href="ident?i=dev">dev</a>, &amp;ifr, <a href="ident?i=SIOCDELTUNNEL">SIOCDELTUNNEL</a>);
<a name="L386" href="source/net/ipv4/ipmr.c#L386">386</a>                         <a href="ident?i=set_fs">set_fs</a>(oldfs);
<a name="L387" href="source/net/ipv4/ipmr.c#L387">387</a>                 }
<a name="L388" href="source/net/ipv4/ipmr.c#L388">388</a>         }
<a name="L389" href="source/net/ipv4/ipmr.c#L389">389</a> }
<a name="L390" href="source/net/ipv4/ipmr.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/ipmr.c#L391">391</a> static
<a name="L392" href="source/net/ipv4/ipmr.c#L392">392</a> struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=ipmr_new_tunnel">ipmr_new_tunnel</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=vifctl">vifctl</a> *<a href="ident?i=v">v</a>)
<a name="L393" href="source/net/ipv4/ipmr.c#L393">393</a> {
<a name="L394" href="source/net/ipv4/ipmr.c#L394">394</a>         struct <a href="ident?i=net_device">net_device</a>  *<a href="ident?i=dev">dev</a>;
<a name="L395" href="source/net/ipv4/ipmr.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/ipmr.c#L396">396</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_name">__dev_get_by_name</a>(<a href="ident?i=net">net</a>, <i>"tunl0"</i>);
<a name="L397" href="source/net/ipv4/ipmr.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/ipmr.c#L398">398</a>         if (<a href="ident?i=dev">dev</a>) {
<a name="L399" href="source/net/ipv4/ipmr.c#L399">399</a>                 const struct <a href="ident?i=net_device_ops">net_device_ops</a> *<a href="ident?i=ops">ops</a> = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>;
<a name="L400" href="source/net/ipv4/ipmr.c#L400">400</a>                 int <a href="ident?i=err">err</a>;
<a name="L401" href="source/net/ipv4/ipmr.c#L401">401</a>                 struct <a href="ident?i=ifreq">ifreq</a> ifr;
<a name="L402" href="source/net/ipv4/ipmr.c#L402">402</a>                 struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L403" href="source/net/ipv4/ipmr.c#L403">403</a>                 struct <a href="ident?i=in_device">in_device</a>  *in_dev;
<a name="L404" href="source/net/ipv4/ipmr.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/ipmr.c#L405">405</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=p">p</a>, 0, sizeof(<a href="ident?i=p">p</a>));
<a name="L406" href="source/net/ipv4/ipmr.c#L406">406</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=v">v</a>-&gt;vifc_rmt_addr.s_addr;
<a name="L407" href="source/net/ipv4/ipmr.c#L407">407</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=v">v</a>-&gt;vifc_lcl_addr.s_addr;
<a name="L408" href="source/net/ipv4/ipmr.c#L408">408</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=version">version</a> = 4;
<a name="L409" href="source/net/ipv4/ipmr.c#L409">409</a>                 <a href="ident?i=p">p</a>.iph.ihl = 5;
<a name="L410" href="source/net/ipv4/ipmr.c#L410">410</a>                 <a href="ident?i=p">p</a>.iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L411" href="source/net/ipv4/ipmr.c#L411">411</a>                 <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=p">p</a>.<a href="ident?i=name">name</a>, <i>"dvmrp%d"</i>, <a href="ident?i=v">v</a>-&gt;vifc_vifi);
<a name="L412" href="source/net/ipv4/ipmr.c#L412">412</a>                 ifr.ifr_ifru.ifru_data = (<a href="ident?i=__force">__force</a> void <a href="ident?i=__user">__user</a> *)&amp;<a href="ident?i=p">p</a>;
<a name="L413" href="source/net/ipv4/ipmr.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/ipmr.c#L414">414</a>                 if (<a href="ident?i=ops">ops</a>-&gt;ndo_do_ioctl) {
<a name="L415" href="source/net/ipv4/ipmr.c#L415">415</a>                         <a href="ident?i=mm_segment_t">mm_segment_t</a> oldfs = <a href="ident?i=get_fs">get_fs</a>();
<a name="L416" href="source/net/ipv4/ipmr.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/ipmr.c#L417">417</a>                         <a href="ident?i=set_fs">set_fs</a>(<a href="ident?i=KERNEL_DS">KERNEL_DS</a>);
<a name="L418" href="source/net/ipv4/ipmr.c#L418">418</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ops">ops</a>-&gt;ndo_do_ioctl(<a href="ident?i=dev">dev</a>, &amp;ifr, <a href="ident?i=SIOCADDTUNNEL">SIOCADDTUNNEL</a>);
<a name="L419" href="source/net/ipv4/ipmr.c#L419">419</a>                         <a href="ident?i=set_fs">set_fs</a>(oldfs);
<a name="L420" href="source/net/ipv4/ipmr.c#L420">420</a>                 } else {
<a name="L421" href="source/net/ipv4/ipmr.c#L421">421</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L422" href="source/net/ipv4/ipmr.c#L422">422</a>                 }
<a name="L423" href="source/net/ipv4/ipmr.c#L423">423</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L424" href="source/net/ipv4/ipmr.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/ipmr.c#L425">425</a>                 if (<a href="ident?i=err">err</a> == 0 &amp;&amp;
<a name="L426" href="source/net/ipv4/ipmr.c#L426">426</a>                     (<a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_name">__dev_get_by_name</a>(<a href="ident?i=net">net</a>, <a href="ident?i=p">p</a>.<a href="ident?i=name">name</a>)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L427" href="source/net/ipv4/ipmr.c#L427">427</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IFF_MULTICAST">IFF_MULTICAST</a>;
<a name="L428" href="source/net/ipv4/ipmr.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/ipmr.c#L429">429</a>                         in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L430" href="source/net/ipv4/ipmr.c#L430">430</a>                         if (!in_dev)
<a name="L431" href="source/net/ipv4/ipmr.c#L431">431</a>                                 goto failure;
<a name="L432" href="source/net/ipv4/ipmr.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/ipmr.c#L433">433</a>                         <a href="ident?i=ipv4_devconf_setall">ipv4_devconf_setall</a>(in_dev);
<a name="L434" href="source/net/ipv4/ipmr.c#L434">434</a>                         <a href="ident?i=neigh_parms_data_state_setall">neigh_parms_data_state_setall</a>(in_dev-&gt;arp_parms);
<a name="L435" href="source/net/ipv4/ipmr.c#L435">435</a>                         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(in_dev-&gt;cnf, RP_FILTER) = 0;
<a name="L436" href="source/net/ipv4/ipmr.c#L436">436</a> 
<a name="L437" href="source/net/ipv4/ipmr.c#L437">437</a>                         if (<a href="ident?i=dev_open">dev_open</a>(<a href="ident?i=dev">dev</a>))
<a name="L438" href="source/net/ipv4/ipmr.c#L438">438</a>                                 goto failure;
<a name="L439" href="source/net/ipv4/ipmr.c#L439">439</a>                         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=dev">dev</a>);
<a name="L440" href="source/net/ipv4/ipmr.c#L440">440</a>                 }
<a name="L441" href="source/net/ipv4/ipmr.c#L441">441</a>         }
<a name="L442" href="source/net/ipv4/ipmr.c#L442">442</a>         return <a href="ident?i=dev">dev</a>;
<a name="L443" href="source/net/ipv4/ipmr.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/ipmr.c#L444">444</a> failure:
<a name="L445" href="source/net/ipv4/ipmr.c#L445">445</a>         <b><i>/* allow the register to be completed before unregistering. */</i></b>
<a name="L446" href="source/net/ipv4/ipmr.c#L446">446</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L447" href="source/net/ipv4/ipmr.c#L447">447</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L448" href="source/net/ipv4/ipmr.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/ipmr.c#L449">449</a>         <a href="ident?i=unregister_netdevice">unregister_netdevice</a>(<a href="ident?i=dev">dev</a>);
<a name="L450" href="source/net/ipv4/ipmr.c#L450">450</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L451" href="source/net/ipv4/ipmr.c#L451">451</a> }
<a name="L452" href="source/net/ipv4/ipmr.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/ipmr.c#L453">453</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L454" href="source/net/ipv4/ipmr.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/ipmr.c#L455">455</a> static <a href="ident?i=netdev_tx_t">netdev_tx_t</a> <a href="ident?i=reg_vif_xmit">reg_vif_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L456" href="source/net/ipv4/ipmr.c#L456">456</a> {
<a name="L457" href="source/net/ipv4/ipmr.c#L457">457</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L458" href="source/net/ipv4/ipmr.c#L458">458</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L459" href="source/net/ipv4/ipmr.c#L459">459</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4 = {
<a name="L460" href="source/net/ipv4/ipmr.c#L460">460</a>                 .<a href="ident?i=flowi4_oif">flowi4_oif</a>     = <a href="ident?i=dev">dev</a>-&gt;ifindex,
<a name="L461" href="source/net/ipv4/ipmr.c#L461">461</a>                 .<a href="ident?i=flowi4_iif">flowi4_iif</a>     = <a href="ident?i=skb">skb</a>-&gt;skb_iif ? : <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>,
<a name="L462" href="source/net/ipv4/ipmr.c#L462">462</a>                 .<a href="ident?i=flowi4_mark">flowi4_mark</a>    = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>,
<a name="L463" href="source/net/ipv4/ipmr.c#L463">463</a>         };
<a name="L464" href="source/net/ipv4/ipmr.c#L464">464</a>         int <a href="ident?i=err">err</a>;
<a name="L465" href="source/net/ipv4/ipmr.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/ipmr.c#L466">466</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_fib_lookup">ipmr_fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;mrt);
<a name="L467" href="source/net/ipv4/ipmr.c#L467">467</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L468" href="source/net/ipv4/ipmr.c#L468">468</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L469" href="source/net/ipv4/ipmr.c#L469">469</a>                 return <a href="ident?i=err">err</a>;
<a name="L470" href="source/net/ipv4/ipmr.c#L470">470</a>         }
<a name="L471" href="source/net/ipv4/ipmr.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/ipmr.c#L472">472</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L473" href="source/net/ipv4/ipmr.c#L473">473</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.<a href="ident?i=tx_bytes">tx_bytes</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L474" href="source/net/ipv4/ipmr.c#L474">474</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_packets++;
<a name="L475" href="source/net/ipv4/ipmr.c#L475">475</a>         <a href="ident?i=ipmr_cache_report">ipmr_cache_report</a>(mrt, <a href="ident?i=skb">skb</a>, mrt-&gt;mroute_reg_vif_num, <a href="ident?i=IGMPMSG_WHOLEPKT">IGMPMSG_WHOLEPKT</a>);
<a name="L476" href="source/net/ipv4/ipmr.c#L476">476</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L477" href="source/net/ipv4/ipmr.c#L477">477</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L478" href="source/net/ipv4/ipmr.c#L478">478</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L479" href="source/net/ipv4/ipmr.c#L479">479</a> }
<a name="L480" href="source/net/ipv4/ipmr.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/ipmr.c#L481">481</a> static int <a href="ident?i=reg_vif_get_iflink">reg_vif_get_iflink</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L482" href="source/net/ipv4/ipmr.c#L482">482</a> {
<a name="L483" href="source/net/ipv4/ipmr.c#L483">483</a>         return 0;
<a name="L484" href="source/net/ipv4/ipmr.c#L484">484</a> }
<a name="L485" href="source/net/ipv4/ipmr.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/ipmr.c#L486">486</a> static const struct <a href="ident?i=net_device_ops">net_device_ops</a> <a href="ident?i=reg_vif_netdev_ops">reg_vif_netdev_ops</a> = {
<a name="L487" href="source/net/ipv4/ipmr.c#L487">487</a>         .ndo_start_xmit = <a href="ident?i=reg_vif_xmit">reg_vif_xmit</a>,
<a name="L488" href="source/net/ipv4/ipmr.c#L488">488</a>         .ndo_get_iflink = <a href="ident?i=reg_vif_get_iflink">reg_vif_get_iflink</a>,
<a name="L489" href="source/net/ipv4/ipmr.c#L489">489</a> };
<a name="L490" href="source/net/ipv4/ipmr.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/ipmr.c#L491">491</a> static void <a href="ident?i=reg_vif_setup">reg_vif_setup</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L492" href="source/net/ipv4/ipmr.c#L492">492</a> {
<a name="L493" href="source/net/ipv4/ipmr.c#L493">493</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>               = <a href="ident?i=ARPHRD_PIMREG">ARPHRD_PIMREG</a>;
<a name="L494" href="source/net/ipv4/ipmr.c#L494">494</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>                = <a href="ident?i=ETH_DATA_LEN">ETH_DATA_LEN</a> - sizeof(struct <a href="ident?i=iphdr">iphdr</a>) - 8;
<a name="L495" href="source/net/ipv4/ipmr.c#L495">495</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>              = <a href="ident?i=IFF_NOARP">IFF_NOARP</a>;
<a name="L496" href="source/net/ipv4/ipmr.c#L496">496</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>         = &amp;<a href="ident?i=reg_vif_netdev_ops">reg_vif_netdev_ops</a>;
<a name="L497" href="source/net/ipv4/ipmr.c#L497">497</a>         <a href="ident?i=dev">dev</a>-&gt;destructor         = <a href="ident?i=free_netdev">free_netdev</a>;
<a name="L498" href="source/net/ipv4/ipmr.c#L498">498</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>           |= <a href="ident?i=NETIF_F_NETNS_LOCAL">NETIF_F_NETNS_LOCAL</a>;
<a name="L499" href="source/net/ipv4/ipmr.c#L499">499</a> }
<a name="L500" href="source/net/ipv4/ipmr.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/ipmr.c#L501">501</a> static struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=ipmr_reg_vif">ipmr_reg_vif</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt)
<a name="L502" href="source/net/ipv4/ipmr.c#L502">502</a> {
<a name="L503" href="source/net/ipv4/ipmr.c#L503">503</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L504" href="source/net/ipv4/ipmr.c#L504">504</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L505" href="source/net/ipv4/ipmr.c#L505">505</a>         char <a href="ident?i=name">name</a>[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>];
<a name="L506" href="source/net/ipv4/ipmr.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/ipmr.c#L507">507</a>         if (mrt-&gt;<a href="ident?i=id">id</a> == RT_TABLE_DEFAULT)
<a name="L508" href="source/net/ipv4/ipmr.c#L508">508</a>                 <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=name">name</a>, <i>"pimreg"</i>);
<a name="L509" href="source/net/ipv4/ipmr.c#L509">509</a>         else
<a name="L510" href="source/net/ipv4/ipmr.c#L510">510</a>                 <a href="ident?i=sprintf">sprintf</a>(<a href="ident?i=name">name</a>, <i>"pimreg%u"</i>, mrt-&gt;<a href="ident?i=id">id</a>);
<a name="L511" href="source/net/ipv4/ipmr.c#L511">511</a> 
<a name="L512" href="source/net/ipv4/ipmr.c#L512">512</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=alloc_netdev">alloc_netdev</a>(0, <a href="ident?i=name">name</a>, <a href="ident?i=NET_NAME_UNKNOWN">NET_NAME_UNKNOWN</a>, <a href="ident?i=reg_vif_setup">reg_vif_setup</a>);
<a name="L513" href="source/net/ipv4/ipmr.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/ipmr.c#L514">514</a>         if (!<a href="ident?i=dev">dev</a>)
<a name="L515" href="source/net/ipv4/ipmr.c#L515">515</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L516" href="source/net/ipv4/ipmr.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/ipmr.c#L517">517</a>         <a href="ident?i=dev_net_set">dev_net_set</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=net">net</a>);
<a name="L518" href="source/net/ipv4/ipmr.c#L518">518</a> 
<a name="L519" href="source/net/ipv4/ipmr.c#L519">519</a>         if (<a href="ident?i=register_netdevice">register_netdevice</a>(<a href="ident?i=dev">dev</a>)) {
<a name="L520" href="source/net/ipv4/ipmr.c#L520">520</a>                 <a href="ident?i=free_netdev">free_netdev</a>(<a href="ident?i=dev">dev</a>);
<a name="L521" href="source/net/ipv4/ipmr.c#L521">521</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L522" href="source/net/ipv4/ipmr.c#L522">522</a>         }
<a name="L523" href="source/net/ipv4/ipmr.c#L523">523</a> 
<a name="L524" href="source/net/ipv4/ipmr.c#L524">524</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L525" href="source/net/ipv4/ipmr.c#L525">525</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L526" href="source/net/ipv4/ipmr.c#L526">526</a>         if (!in_dev) {
<a name="L527" href="source/net/ipv4/ipmr.c#L527">527</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L528" href="source/net/ipv4/ipmr.c#L528">528</a>                 goto failure;
<a name="L529" href="source/net/ipv4/ipmr.c#L529">529</a>         }
<a name="L530" href="source/net/ipv4/ipmr.c#L530">530</a> 
<a name="L531" href="source/net/ipv4/ipmr.c#L531">531</a>         <a href="ident?i=ipv4_devconf_setall">ipv4_devconf_setall</a>(in_dev);
<a name="L532" href="source/net/ipv4/ipmr.c#L532">532</a>         <a href="ident?i=neigh_parms_data_state_setall">neigh_parms_data_state_setall</a>(in_dev-&gt;arp_parms);
<a name="L533" href="source/net/ipv4/ipmr.c#L533">533</a>         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(in_dev-&gt;cnf, RP_FILTER) = 0;
<a name="L534" href="source/net/ipv4/ipmr.c#L534">534</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L535" href="source/net/ipv4/ipmr.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/ipmr.c#L536">536</a>         if (<a href="ident?i=dev_open">dev_open</a>(<a href="ident?i=dev">dev</a>))
<a name="L537" href="source/net/ipv4/ipmr.c#L537">537</a>                 goto failure;
<a name="L538" href="source/net/ipv4/ipmr.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/ipmr.c#L539">539</a>         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=dev">dev</a>);
<a name="L540" href="source/net/ipv4/ipmr.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/ipmr.c#L541">541</a>         return <a href="ident?i=dev">dev</a>;
<a name="L542" href="source/net/ipv4/ipmr.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/ipmr.c#L543">543</a> failure:
<a name="L544" href="source/net/ipv4/ipmr.c#L544">544</a>         <b><i>/* allow the register to be completed before unregistering. */</i></b>
<a name="L545" href="source/net/ipv4/ipmr.c#L545">545</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L546" href="source/net/ipv4/ipmr.c#L546">546</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L547" href="source/net/ipv4/ipmr.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/ipmr.c#L548">548</a>         <a href="ident?i=unregister_netdevice">unregister_netdevice</a>(<a href="ident?i=dev">dev</a>);
<a name="L549" href="source/net/ipv4/ipmr.c#L549">549</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L550" href="source/net/ipv4/ipmr.c#L550">550</a> }
<a name="L551" href="source/net/ipv4/ipmr.c#L551">551</a> #endif
<a name="L552" href="source/net/ipv4/ipmr.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/ipmr.c#L553">553</a> <b><i>/**</i></b>
<a name="L554" href="source/net/ipv4/ipmr.c#L554">554</a> <b><i> *      vif_delete - Delete a VIF entry</i></b>
<a name="L555" href="source/net/ipv4/ipmr.c#L555">555</a> <b><i> *      @notify: Set to 1, if the caller is a notifier_call</i></b>
<a name="L556" href="source/net/ipv4/ipmr.c#L556">556</a> <b><i> */</i></b>
<a name="L557" href="source/net/ipv4/ipmr.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/ipmr.c#L558">558</a> static int <a href="ident?i=vif_delete">vif_delete</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, int vifi, int <a href="ident?i=notify">notify</a>,
<a name="L559" href="source/net/ipv4/ipmr.c#L559">559</a>                       struct <a href="ident?i=list_head">list_head</a> *<a href="ident?i=head">head</a>)
<a name="L560" href="source/net/ipv4/ipmr.c#L560">560</a> {
<a name="L561" href="source/net/ipv4/ipmr.c#L561">561</a>         struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=v">v</a>;
<a name="L562" href="source/net/ipv4/ipmr.c#L562">562</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L563" href="source/net/ipv4/ipmr.c#L563">563</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L564" href="source/net/ipv4/ipmr.c#L564">564</a> 
<a name="L565" href="source/net/ipv4/ipmr.c#L565">565</a>         if (vifi &lt; 0 || vifi &gt;= mrt-&gt;maxvif)
<a name="L566" href="source/net/ipv4/ipmr.c#L566">566</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L567" href="source/net/ipv4/ipmr.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/ipmr.c#L568">568</a>         <a href="ident?i=v">v</a> = &amp;mrt-&gt;vif_table[vifi];
<a name="L569" href="source/net/ipv4/ipmr.c#L569">569</a> 
<a name="L570" href="source/net/ipv4/ipmr.c#L570">570</a>         <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;mrt_lock);
<a name="L571" href="source/net/ipv4/ipmr.c#L571">571</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=v">v</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L572" href="source/net/ipv4/ipmr.c#L572">572</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L573" href="source/net/ipv4/ipmr.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/ipmr.c#L574">574</a>         if (!<a href="ident?i=dev">dev</a>) {
<a name="L575" href="source/net/ipv4/ipmr.c#L575">575</a>                 <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;mrt_lock);
<a name="L576" href="source/net/ipv4/ipmr.c#L576">576</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L577" href="source/net/ipv4/ipmr.c#L577">577</a>         }
<a name="L578" href="source/net/ipv4/ipmr.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/ipmr.c#L579">579</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L580" href="source/net/ipv4/ipmr.c#L580">580</a>         if (vifi == mrt-&gt;mroute_reg_vif_num)
<a name="L581" href="source/net/ipv4/ipmr.c#L581">581</a>                 mrt-&gt;mroute_reg_vif_num = -1;
<a name="L582" href="source/net/ipv4/ipmr.c#L582">582</a> #endif
<a name="L583" href="source/net/ipv4/ipmr.c#L583">583</a> 
<a name="L584" href="source/net/ipv4/ipmr.c#L584">584</a>         if (vifi + 1 == mrt-&gt;maxvif) {
<a name="L585" href="source/net/ipv4/ipmr.c#L585">585</a>                 int <a href="ident?i=tmp">tmp</a>;
<a name="L586" href="source/net/ipv4/ipmr.c#L586">586</a> 
<a name="L587" href="source/net/ipv4/ipmr.c#L587">587</a>                 for (<a href="ident?i=tmp">tmp</a> = vifi - 1; <a href="ident?i=tmp">tmp</a> &gt;= 0; <a href="ident?i=tmp">tmp</a>--) {
<a name="L588" href="source/net/ipv4/ipmr.c#L588">588</a>                         if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, <a href="ident?i=tmp">tmp</a>))
<a name="L589" href="source/net/ipv4/ipmr.c#L589">589</a>                                 break;
<a name="L590" href="source/net/ipv4/ipmr.c#L590">590</a>                 }
<a name="L591" href="source/net/ipv4/ipmr.c#L591">591</a>                 mrt-&gt;maxvif = <a href="ident?i=tmp">tmp</a>+1;
<a name="L592" href="source/net/ipv4/ipmr.c#L592">592</a>         }
<a name="L593" href="source/net/ipv4/ipmr.c#L593">593</a> 
<a name="L594" href="source/net/ipv4/ipmr.c#L594">594</a>         <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;mrt_lock);
<a name="L595" href="source/net/ipv4/ipmr.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/ipmr.c#L596">596</a>         <a href="ident?i=dev_set_allmulti">dev_set_allmulti</a>(<a href="ident?i=dev">dev</a>, -1);
<a name="L597" href="source/net/ipv4/ipmr.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/ipmr.c#L598">598</a>         in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L599" href="source/net/ipv4/ipmr.c#L599">599</a>         if (in_dev) {
<a name="L600" href="source/net/ipv4/ipmr.c#L600">600</a>                 <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(in_dev-&gt;cnf, MC_FORWARDING)--;
<a name="L601" href="source/net/ipv4/ipmr.c#L601">601</a>                 <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>),
<a name="L602" href="source/net/ipv4/ipmr.c#L602">602</a>                                             NETCONFA_MC_FORWARDING,
<a name="L603" href="source/net/ipv4/ipmr.c#L603">603</a>                                             <a href="ident?i=dev">dev</a>-&gt;ifindex, &amp;in_dev-&gt;cnf);
<a name="L604" href="source/net/ipv4/ipmr.c#L604">604</a>                 <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(in_dev);
<a name="L605" href="source/net/ipv4/ipmr.c#L605">605</a>         }
<a name="L606" href="source/net/ipv4/ipmr.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/ipmr.c#L607">607</a>         if (<a href="ident?i=v">v</a>-&gt;<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=VIFF_TUNNEL">VIFF_TUNNEL</a> | <a href="ident?i=VIFF_REGISTER">VIFF_REGISTER</a>) &amp;&amp; !<a href="ident?i=notify">notify</a>)
<a name="L608" href="source/net/ipv4/ipmr.c#L608">608</a>                 <a href="ident?i=unregister_netdevice_queue">unregister_netdevice_queue</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=head">head</a>);
<a name="L609" href="source/net/ipv4/ipmr.c#L609">609</a> 
<a name="L610" href="source/net/ipv4/ipmr.c#L610">610</a>         <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L611" href="source/net/ipv4/ipmr.c#L611">611</a>         return 0;
<a name="L612" href="source/net/ipv4/ipmr.c#L612">612</a> }
<a name="L613" href="source/net/ipv4/ipmr.c#L613">613</a> 
<a name="L614" href="source/net/ipv4/ipmr.c#L614">614</a> static void <a href="ident?i=ipmr_cache_free_rcu">ipmr_cache_free_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L615" href="source/net/ipv4/ipmr.c#L615">615</a> {
<a name="L616" href="source/net/ipv4/ipmr.c#L616">616</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a>, rcu);
<a name="L617" href="source/net/ipv4/ipmr.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/ipmr.c#L618">618</a>         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(mrt_cachep, <a href="ident?i=c">c</a>);
<a name="L619" href="source/net/ipv4/ipmr.c#L619">619</a> }
<a name="L620" href="source/net/ipv4/ipmr.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/ipmr.c#L621">621</a> static inline void <a href="ident?i=ipmr_cache_free">ipmr_cache_free</a>(struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>)
<a name="L622" href="source/net/ipv4/ipmr.c#L622">622</a> {
<a name="L623" href="source/net/ipv4/ipmr.c#L623">623</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=c">c</a>-&gt;rcu, <a href="ident?i=ipmr_cache_free_rcu">ipmr_cache_free_rcu</a>);
<a name="L624" href="source/net/ipv4/ipmr.c#L624">624</a> }
<a name="L625" href="source/net/ipv4/ipmr.c#L625">625</a> 
<a name="L626" href="source/net/ipv4/ipmr.c#L626">626</a> <b><i>/* Destroy an unresolved cache entry, killing queued skbs</i></b>
<a name="L627" href="source/net/ipv4/ipmr.c#L627">627</a> <b><i> * and reporting error to netlink readers.</i></b>
<a name="L628" href="source/net/ipv4/ipmr.c#L628">628</a> <b><i> */</i></b>
<a name="L629" href="source/net/ipv4/ipmr.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/ipmr.c#L630">630</a> static void <a href="ident?i=ipmr_destroy_unres">ipmr_destroy_unres</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>)
<a name="L631" href="source/net/ipv4/ipmr.c#L631">631</a> {
<a name="L632" href="source/net/ipv4/ipmr.c#L632">632</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=read_pnet">read_pnet</a>(&amp;mrt-&gt;<a href="ident?i=net">net</a>);
<a name="L633" href="source/net/ipv4/ipmr.c#L633">633</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L634" href="source/net/ipv4/ipmr.c#L634">634</a>         struct <a href="ident?i=nlmsgerr">nlmsgerr</a> *<a href="ident?i=e">e</a>;
<a name="L635" href="source/net/ipv4/ipmr.c#L635">635</a> 
<a name="L636" href="source/net/ipv4/ipmr.c#L636">636</a>         <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;mrt-&gt;cache_resolve_queue_len);
<a name="L637" href="source/net/ipv4/ipmr.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/ipmr.c#L638">638</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_dequeue">skb_dequeue</a>(&amp;<a href="ident?i=c">c</a>-&gt;mfc_un.unres.<a href="ident?i=unresolved">unresolved</a>))) {
<a name="L639" href="source/net/ipv4/ipmr.c#L639">639</a>                 if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=version">version</a> == 0) {
<a name="L640" href="source/net/ipv4/ipmr.c#L640">640</a>                         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh = (struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *)<a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L641" href="source/net/ipv4/ipmr.c#L641">641</a>                         nlh-&gt;nlmsg_type = <a href="ident?i=NLMSG_ERROR">NLMSG_ERROR</a>;
<a name="L642" href="source/net/ipv4/ipmr.c#L642">642</a>                         nlh-&gt;<a href="ident?i=nlmsg_len">nlmsg_len</a> = <a href="ident?i=nlmsg_msg_size">nlmsg_msg_size</a>(sizeof(struct <a href="ident?i=nlmsgerr">nlmsgerr</a>));
<a name="L643" href="source/net/ipv4/ipmr.c#L643">643</a>                         <a href="ident?i=skb_trim">skb_trim</a>(<a href="ident?i=skb">skb</a>, nlh-&gt;<a href="ident?i=nlmsg_len">nlmsg_len</a>);
<a name="L644" href="source/net/ipv4/ipmr.c#L644">644</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L645" href="source/net/ipv4/ipmr.c#L645">645</a>                         <a href="ident?i=e">e</a>-&gt;<a href="ident?i=error">error</a> = -<a href="ident?i=ETIMEDOUT">ETIMEDOUT</a>;
<a name="L646" href="source/net/ipv4/ipmr.c#L646">646</a>                         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=msg">msg</a>, 0, sizeof(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=msg">msg</a>));
<a name="L647" href="source/net/ipv4/ipmr.c#L647">647</a> 
<a name="L648" href="source/net/ipv4/ipmr.c#L648">648</a>                         <a href="ident?i=rtnl_unicast">rtnl_unicast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid);
<a name="L649" href="source/net/ipv4/ipmr.c#L649">649</a>                 } else {
<a name="L650" href="source/net/ipv4/ipmr.c#L650">650</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L651" href="source/net/ipv4/ipmr.c#L651">651</a>                 }
<a name="L652" href="source/net/ipv4/ipmr.c#L652">652</a>         }
<a name="L653" href="source/net/ipv4/ipmr.c#L653">653</a> 
<a name="L654" href="source/net/ipv4/ipmr.c#L654">654</a>         <a href="ident?i=ipmr_cache_free">ipmr_cache_free</a>(<a href="ident?i=c">c</a>);
<a name="L655" href="source/net/ipv4/ipmr.c#L655">655</a> }
<a name="L656" href="source/net/ipv4/ipmr.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/ipmr.c#L657">657</a> 
<a name="L658" href="source/net/ipv4/ipmr.c#L658">658</a> <b><i>/* Timer process for the unresolved queue. */</i></b>
<a name="L659" href="source/net/ipv4/ipmr.c#L659">659</a> 
<a name="L660" href="source/net/ipv4/ipmr.c#L660">660</a> static void <a href="ident?i=ipmr_expire_process">ipmr_expire_process</a>(unsigned long <a href="ident?i=arg">arg</a>)
<a name="L661" href="source/net/ipv4/ipmr.c#L661">661</a> {
<a name="L662" href="source/net/ipv4/ipmr.c#L662">662</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = (struct <a href="ident?i=mr_table">mr_table</a> *)<a href="ident?i=arg">arg</a>;
<a name="L663" href="source/net/ipv4/ipmr.c#L663">663</a>         unsigned long <a href="ident?i=now">now</a>;
<a name="L664" href="source/net/ipv4/ipmr.c#L664">664</a>         unsigned long expires;
<a name="L665" href="source/net/ipv4/ipmr.c#L665">665</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, *<a href="ident?i=next">next</a>;
<a name="L666" href="source/net/ipv4/ipmr.c#L666">666</a> 
<a name="L667" href="source/net/ipv4/ipmr.c#L667">667</a>         if (!<a href="ident?i=spin_trylock">spin_trylock</a>(&amp;mfc_unres_lock)) {
<a name="L668" href="source/net/ipv4/ipmr.c#L668">668</a>                 <a href="ident?i=mod_timer">mod_timer</a>(&amp;mrt-&gt;ipmr_expire_timer, <a href="ident?i=jiffies">jiffies</a>+<a href="ident?i=HZ">HZ</a>/10);
<a name="L669" href="source/net/ipv4/ipmr.c#L669">669</a>                 return;
<a name="L670" href="source/net/ipv4/ipmr.c#L670">670</a>         }
<a name="L671" href="source/net/ipv4/ipmr.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/ipmr.c#L672">672</a>         if (<a href="ident?i=list_empty">list_empty</a>(&amp;mrt-&gt;mfc_unres_queue))
<a name="L673" href="source/net/ipv4/ipmr.c#L673">673</a>                 goto <a href="ident?i=out">out</a>;
<a name="L674" href="source/net/ipv4/ipmr.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/ipmr.c#L675">675</a>         <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L676" href="source/net/ipv4/ipmr.c#L676">676</a>         expires = 10*<a href="ident?i=HZ">HZ</a>;
<a name="L677" href="source/net/ipv4/ipmr.c#L677">677</a> 
<a name="L678" href="source/net/ipv4/ipmr.c#L678">678</a>         <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=c">c</a>, <a href="ident?i=next">next</a>, &amp;mrt-&gt;mfc_unres_queue, <a href="ident?i=list">list</a>) {
<a name="L679" href="source/net/ipv4/ipmr.c#L679">679</a>                 if (<a href="ident?i=time_after">time_after</a>(<a href="ident?i=c">c</a>-&gt;mfc_un.unres.expires, <a href="ident?i=now">now</a>)) {
<a name="L680" href="source/net/ipv4/ipmr.c#L680">680</a>                         unsigned long <a href="ident?i=interval">interval</a> = <a href="ident?i=c">c</a>-&gt;mfc_un.unres.expires - <a href="ident?i=now">now</a>;
<a name="L681" href="source/net/ipv4/ipmr.c#L681">681</a>                         if (<a href="ident?i=interval">interval</a> &lt; expires)
<a name="L682" href="source/net/ipv4/ipmr.c#L682">682</a>                                 expires = <a href="ident?i=interval">interval</a>;
<a name="L683" href="source/net/ipv4/ipmr.c#L683">683</a>                         continue;
<a name="L684" href="source/net/ipv4/ipmr.c#L684">684</a>                 }
<a name="L685" href="source/net/ipv4/ipmr.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/ipmr.c#L686">686</a>                 <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L687" href="source/net/ipv4/ipmr.c#L687">687</a>                 <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>);
<a name="L688" href="source/net/ipv4/ipmr.c#L688">688</a>                 <a href="ident?i=ipmr_destroy_unres">ipmr_destroy_unres</a>(mrt, <a href="ident?i=c">c</a>);
<a name="L689" href="source/net/ipv4/ipmr.c#L689">689</a>         }
<a name="L690" href="source/net/ipv4/ipmr.c#L690">690</a> 
<a name="L691" href="source/net/ipv4/ipmr.c#L691">691</a>         if (!<a href="ident?i=list_empty">list_empty</a>(&amp;mrt-&gt;mfc_unres_queue))
<a name="L692" href="source/net/ipv4/ipmr.c#L692">692</a>                 <a href="ident?i=mod_timer">mod_timer</a>(&amp;mrt-&gt;ipmr_expire_timer, <a href="ident?i=jiffies">jiffies</a> + expires);
<a name="L693" href="source/net/ipv4/ipmr.c#L693">693</a> 
<a name="L694" href="source/net/ipv4/ipmr.c#L694">694</a> <a href="ident?i=out">out</a>:
<a name="L695" href="source/net/ipv4/ipmr.c#L695">695</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;mfc_unres_lock);
<a name="L696" href="source/net/ipv4/ipmr.c#L696">696</a> }
<a name="L697" href="source/net/ipv4/ipmr.c#L697">697</a> 
<a name="L698" href="source/net/ipv4/ipmr.c#L698">698</a> <b><i>/* Fill oifs list. It is called under write locked mrt_lock. */</i></b>
<a name="L699" href="source/net/ipv4/ipmr.c#L699">699</a> 
<a name="L700" href="source/net/ipv4/ipmr.c#L700">700</a> static void <a href="ident?i=ipmr_update_thresholds">ipmr_update_thresholds</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=cache">cache</a>,
<a name="L701" href="source/net/ipv4/ipmr.c#L701">701</a>                                    unsigned char *ttls)
<a name="L702" href="source/net/ipv4/ipmr.c#L702">702</a> {
<a name="L703" href="source/net/ipv4/ipmr.c#L703">703</a>         int vifi;
<a name="L704" href="source/net/ipv4/ipmr.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/ipmr.c#L705">705</a>         <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif = <a href="ident?i=MAXVIFS">MAXVIFS</a>;
<a name="L706" href="source/net/ipv4/ipmr.c#L706">706</a>         <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.maxvif = 0;
<a name="L707" href="source/net/ipv4/ipmr.c#L707">707</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls, 255, <a href="ident?i=MAXVIFS">MAXVIFS</a>);
<a name="L708" href="source/net/ipv4/ipmr.c#L708">708</a> 
<a name="L709" href="source/net/ipv4/ipmr.c#L709">709</a>         for (vifi = 0; vifi &lt; mrt-&gt;maxvif; vifi++) {
<a name="L710" href="source/net/ipv4/ipmr.c#L710">710</a>                 if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, vifi) &amp;&amp;
<a name="L711" href="source/net/ipv4/ipmr.c#L711">711</a>                     ttls[vifi] &amp;&amp; ttls[vifi] &lt; 255) {
<a name="L712" href="source/net/ipv4/ipmr.c#L712">712</a>                         <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[vifi] = ttls[vifi];
<a name="L713" href="source/net/ipv4/ipmr.c#L713">713</a>                         if (<a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif &gt; vifi)
<a name="L714" href="source/net/ipv4/ipmr.c#L714">714</a>                                 <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif = vifi;
<a name="L715" href="source/net/ipv4/ipmr.c#L715">715</a>                         if (<a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.maxvif &lt;= vifi)
<a name="L716" href="source/net/ipv4/ipmr.c#L716">716</a>                                 <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.maxvif = vifi + 1;
<a name="L717" href="source/net/ipv4/ipmr.c#L717">717</a>                 }
<a name="L718" href="source/net/ipv4/ipmr.c#L718">718</a>         }
<a name="L719" href="source/net/ipv4/ipmr.c#L719">719</a> }
<a name="L720" href="source/net/ipv4/ipmr.c#L720">720</a> 
<a name="L721" href="source/net/ipv4/ipmr.c#L721">721</a> static int <a href="ident?i=vif_add">vif_add</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L722" href="source/net/ipv4/ipmr.c#L722">722</a>                    struct <a href="ident?i=vifctl">vifctl</a> *vifc, int mrtsock)
<a name="L723" href="source/net/ipv4/ipmr.c#L723">723</a> {
<a name="L724" href="source/net/ipv4/ipmr.c#L724">724</a>         int vifi = vifc-&gt;vifc_vifi;
<a name="L725" href="source/net/ipv4/ipmr.c#L725">725</a>         struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=v">v</a> = &amp;mrt-&gt;vif_table[vifi];
<a name="L726" href="source/net/ipv4/ipmr.c#L726">726</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L727" href="source/net/ipv4/ipmr.c#L727">727</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L728" href="source/net/ipv4/ipmr.c#L728">728</a>         int <a href="ident?i=err">err</a>;
<a name="L729" href="source/net/ipv4/ipmr.c#L729">729</a> 
<a name="L730" href="source/net/ipv4/ipmr.c#L730">730</a>         <b><i>/* Is vif busy ? */</i></b>
<a name="L731" href="source/net/ipv4/ipmr.c#L731">731</a>         if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, vifi))
<a name="L732" href="source/net/ipv4/ipmr.c#L732">732</a>                 return -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L733" href="source/net/ipv4/ipmr.c#L733">733</a> 
<a name="L734" href="source/net/ipv4/ipmr.c#L734">734</a>         switch (vifc-&gt;vifc_flags) {
<a name="L735" href="source/net/ipv4/ipmr.c#L735">735</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L736" href="source/net/ipv4/ipmr.c#L736">736</a>         case <a href="ident?i=VIFF_REGISTER">VIFF_REGISTER</a>:
<a name="L737" href="source/net/ipv4/ipmr.c#L737">737</a>                 <b><i>/*</i></b>
<a name="L738" href="source/net/ipv4/ipmr.c#L738">738</a> <b><i>                 * Special Purpose VIF in PIM</i></b>
<a name="L739" href="source/net/ipv4/ipmr.c#L739">739</a> <b><i>                 * All the packets will be sent to the daemon</i></b>
<a name="L740" href="source/net/ipv4/ipmr.c#L740">740</a> <b><i>                 */</i></b>
<a name="L741" href="source/net/ipv4/ipmr.c#L741">741</a>                 if (mrt-&gt;mroute_reg_vif_num &gt;= 0)
<a name="L742" href="source/net/ipv4/ipmr.c#L742">742</a>                         return -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L743" href="source/net/ipv4/ipmr.c#L743">743</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=ipmr_reg_vif">ipmr_reg_vif</a>(<a href="ident?i=net">net</a>, mrt);
<a name="L744" href="source/net/ipv4/ipmr.c#L744">744</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L745" href="source/net/ipv4/ipmr.c#L745">745</a>                         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L746" href="source/net/ipv4/ipmr.c#L746">746</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=dev_set_allmulti">dev_set_allmulti</a>(<a href="ident?i=dev">dev</a>, 1);
<a name="L747" href="source/net/ipv4/ipmr.c#L747">747</a>                 if (<a href="ident?i=err">err</a>) {
<a name="L748" href="source/net/ipv4/ipmr.c#L748">748</a>                         <a href="ident?i=unregister_netdevice">unregister_netdevice</a>(<a href="ident?i=dev">dev</a>);
<a name="L749" href="source/net/ipv4/ipmr.c#L749">749</a>                         <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L750" href="source/net/ipv4/ipmr.c#L750">750</a>                         return <a href="ident?i=err">err</a>;
<a name="L751" href="source/net/ipv4/ipmr.c#L751">751</a>                 }
<a name="L752" href="source/net/ipv4/ipmr.c#L752">752</a>                 break;
<a name="L753" href="source/net/ipv4/ipmr.c#L753">753</a> #endif
<a name="L754" href="source/net/ipv4/ipmr.c#L754">754</a>         case <a href="ident?i=VIFF_TUNNEL">VIFF_TUNNEL</a>:
<a name="L755" href="source/net/ipv4/ipmr.c#L755">755</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=ipmr_new_tunnel">ipmr_new_tunnel</a>(<a href="ident?i=net">net</a>, vifc);
<a name="L756" href="source/net/ipv4/ipmr.c#L756">756</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L757" href="source/net/ipv4/ipmr.c#L757">757</a>                         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L758" href="source/net/ipv4/ipmr.c#L758">758</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=dev_set_allmulti">dev_set_allmulti</a>(<a href="ident?i=dev">dev</a>, 1);
<a name="L759" href="source/net/ipv4/ipmr.c#L759">759</a>                 if (<a href="ident?i=err">err</a>) {
<a name="L760" href="source/net/ipv4/ipmr.c#L760">760</a>                         <a href="ident?i=ipmr_del_tunnel">ipmr_del_tunnel</a>(<a href="ident?i=dev">dev</a>, vifc);
<a name="L761" href="source/net/ipv4/ipmr.c#L761">761</a>                         <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L762" href="source/net/ipv4/ipmr.c#L762">762</a>                         return <a href="ident?i=err">err</a>;
<a name="L763" href="source/net/ipv4/ipmr.c#L763">763</a>                 }
<a name="L764" href="source/net/ipv4/ipmr.c#L764">764</a>                 break;
<a name="L765" href="source/net/ipv4/ipmr.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/ipmr.c#L766">766</a>         case <a href="ident?i=VIFF_USE_IFINDEX">VIFF_USE_IFINDEX</a>:
<a name="L767" href="source/net/ipv4/ipmr.c#L767">767</a>         case 0:
<a name="L768" href="source/net/ipv4/ipmr.c#L768">768</a>                 if (vifc-&gt;vifc_flags == <a href="ident?i=VIFF_USE_IFINDEX">VIFF_USE_IFINDEX</a>) {
<a name="L769" href="source/net/ipv4/ipmr.c#L769">769</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index">dev_get_by_index</a>(<a href="ident?i=net">net</a>, vifc-&gt;vifc_lcl_ifindex);
<a name="L770" href="source/net/ipv4/ipmr.c#L770">770</a>                         if (<a href="ident?i=dev">dev</a> &amp;&amp; !<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>)) {
<a name="L771" href="source/net/ipv4/ipmr.c#L771">771</a>                                 <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L772" href="source/net/ipv4/ipmr.c#L772">772</a>                                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L773" href="source/net/ipv4/ipmr.c#L773">773</a>                         }
<a name="L774" href="source/net/ipv4/ipmr.c#L774">774</a>                 } else {
<a name="L775" href="source/net/ipv4/ipmr.c#L775">775</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=ip_dev_find">ip_dev_find</a>(<a href="ident?i=net">net</a>, vifc-&gt;vifc_lcl_addr.s_addr);
<a name="L776" href="source/net/ipv4/ipmr.c#L776">776</a>                 }
<a name="L777" href="source/net/ipv4/ipmr.c#L777">777</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L778" href="source/net/ipv4/ipmr.c#L778">778</a>                         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L779" href="source/net/ipv4/ipmr.c#L779">779</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=dev_set_allmulti">dev_set_allmulti</a>(<a href="ident?i=dev">dev</a>, 1);
<a name="L780" href="source/net/ipv4/ipmr.c#L780">780</a>                 if (<a href="ident?i=err">err</a>) {
<a name="L781" href="source/net/ipv4/ipmr.c#L781">781</a>                         <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L782" href="source/net/ipv4/ipmr.c#L782">782</a>                         return <a href="ident?i=err">err</a>;
<a name="L783" href="source/net/ipv4/ipmr.c#L783">783</a>                 }
<a name="L784" href="source/net/ipv4/ipmr.c#L784">784</a>                 break;
<a name="L785" href="source/net/ipv4/ipmr.c#L785">785</a>         default:
<a name="L786" href="source/net/ipv4/ipmr.c#L786">786</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L787" href="source/net/ipv4/ipmr.c#L787">787</a>         }
<a name="L788" href="source/net/ipv4/ipmr.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/ipmr.c#L789">789</a>         in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L790" href="source/net/ipv4/ipmr.c#L790">790</a>         if (!in_dev) {
<a name="L791" href="source/net/ipv4/ipmr.c#L791">791</a>                 <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L792" href="source/net/ipv4/ipmr.c#L792">792</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L793" href="source/net/ipv4/ipmr.c#L793">793</a>         }
<a name="L794" href="source/net/ipv4/ipmr.c#L794">794</a>         <a href="ident?i=IPV4_DEVCONF">IPV4_DEVCONF</a>(in_dev-&gt;cnf, MC_FORWARDING)++;
<a name="L795" href="source/net/ipv4/ipmr.c#L795">795</a>         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_MC_FORWARDING, <a href="ident?i=dev">dev</a>-&gt;ifindex,
<a name="L796" href="source/net/ipv4/ipmr.c#L796">796</a>                                     &amp;in_dev-&gt;cnf);
<a name="L797" href="source/net/ipv4/ipmr.c#L797">797</a>         <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(in_dev);
<a name="L798" href="source/net/ipv4/ipmr.c#L798">798</a> 
<a name="L799" href="source/net/ipv4/ipmr.c#L799">799</a>         <b><i>/* Fill in the VIF structures */</i></b>
<a name="L800" href="source/net/ipv4/ipmr.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/ipmr.c#L801">801</a>         <a href="ident?i=v">v</a>-&gt;rate_limit = vifc-&gt;vifc_rate_limit;
<a name="L802" href="source/net/ipv4/ipmr.c#L802">802</a>         <a href="ident?i=v">v</a>-&gt;local = vifc-&gt;vifc_lcl_addr.s_addr;
<a name="L803" href="source/net/ipv4/ipmr.c#L803">803</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=remote">remote</a> = vifc-&gt;vifc_rmt_addr.s_addr;
<a name="L804" href="source/net/ipv4/ipmr.c#L804">804</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=flags">flags</a> = vifc-&gt;vifc_flags;
<a name="L805" href="source/net/ipv4/ipmr.c#L805">805</a>         if (!mrtsock)
<a name="L806" href="source/net/ipv4/ipmr.c#L806">806</a>                 <a href="ident?i=v">v</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=VIFF_STATIC">VIFF_STATIC</a>;
<a name="L807" href="source/net/ipv4/ipmr.c#L807">807</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=threshold">threshold</a> = vifc-&gt;vifc_threshold;
<a name="L808" href="source/net/ipv4/ipmr.c#L808">808</a>         <a href="ident?i=v">v</a>-&gt;bytes_in = 0;
<a name="L809" href="source/net/ipv4/ipmr.c#L809">809</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=bytes_out">bytes_out</a> = 0;
<a name="L810" href="source/net/ipv4/ipmr.c#L810">810</a>         <a href="ident?i=v">v</a>-&gt;pkt_in = 0;
<a name="L811" href="source/net/ipv4/ipmr.c#L811">811</a>         <a href="ident?i=v">v</a>-&gt;pkt_out = 0;
<a name="L812" href="source/net/ipv4/ipmr.c#L812">812</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=link">link</a> = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L813" href="source/net/ipv4/ipmr.c#L813">813</a>         if (<a href="ident?i=v">v</a>-&gt;<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=VIFF_TUNNEL">VIFF_TUNNEL</a> | <a href="ident?i=VIFF_REGISTER">VIFF_REGISTER</a>))
<a name="L814" href="source/net/ipv4/ipmr.c#L814">814</a>                 <a href="ident?i=v">v</a>-&gt;<a href="ident?i=link">link</a> = <a href="ident?i=dev_get_iflink">dev_get_iflink</a>(<a href="ident?i=dev">dev</a>);
<a name="L815" href="source/net/ipv4/ipmr.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/ipmr.c#L816">816</a>         <b><i>/* And finish update writing critical data */</i></b>
<a name="L817" href="source/net/ipv4/ipmr.c#L817">817</a>         <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;mrt_lock);
<a name="L818" href="source/net/ipv4/ipmr.c#L818">818</a>         <a href="ident?i=v">v</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L819" href="source/net/ipv4/ipmr.c#L819">819</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L820" href="source/net/ipv4/ipmr.c#L820">820</a>         if (<a href="ident?i=v">v</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=VIFF_REGISTER">VIFF_REGISTER</a>)
<a name="L821" href="source/net/ipv4/ipmr.c#L821">821</a>                 mrt-&gt;mroute_reg_vif_num = vifi;
<a name="L822" href="source/net/ipv4/ipmr.c#L822">822</a> #endif
<a name="L823" href="source/net/ipv4/ipmr.c#L823">823</a>         if (vifi+1 &gt; mrt-&gt;maxvif)
<a name="L824" href="source/net/ipv4/ipmr.c#L824">824</a>                 mrt-&gt;maxvif = vifi+1;
<a name="L825" href="source/net/ipv4/ipmr.c#L825">825</a>         <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;mrt_lock);
<a name="L826" href="source/net/ipv4/ipmr.c#L826">826</a>         return 0;
<a name="L827" href="source/net/ipv4/ipmr.c#L827">827</a> }
<a name="L828" href="source/net/ipv4/ipmr.c#L828">828</a> 
<a name="L829" href="source/net/ipv4/ipmr.c#L829">829</a> <b><i>/* called with rcu_read_lock() */</i></b>
<a name="L830" href="source/net/ipv4/ipmr.c#L830">830</a> static struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=ipmr_cache_find">ipmr_cache_find</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L831" href="source/net/ipv4/ipmr.c#L831">831</a>                                          <a href="ident?i=__be32">__be32</a> <a href="ident?i=origin">origin</a>,
<a name="L832" href="source/net/ipv4/ipmr.c#L832">832</a>                                          <a href="ident?i=__be32">__be32</a> mcastgrp)
<a name="L833" href="source/net/ipv4/ipmr.c#L833">833</a> {
<a name="L834" href="source/net/ipv4/ipmr.c#L834">834</a>         int <a href="ident?i=line">line</a> = <a href="ident?i=MFC_HASH">MFC_HASH</a>(mcastgrp, <a href="ident?i=origin">origin</a>);
<a name="L835" href="source/net/ipv4/ipmr.c#L835">835</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>;
<a name="L836" href="source/net/ipv4/ipmr.c#L836">836</a> 
<a name="L837" href="source/net/ipv4/ipmr.c#L837">837</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=c">c</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=line">line</a>], <a href="ident?i=list">list</a>) {
<a name="L838" href="source/net/ipv4/ipmr.c#L838">838</a>                 if (<a href="ident?i=c">c</a>-&gt;mfc_origin == <a href="ident?i=origin">origin</a> &amp;&amp; <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp == mcastgrp)
<a name="L839" href="source/net/ipv4/ipmr.c#L839">839</a>                         return <a href="ident?i=c">c</a>;
<a name="L840" href="source/net/ipv4/ipmr.c#L840">840</a>         }
<a name="L841" href="source/net/ipv4/ipmr.c#L841">841</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L842" href="source/net/ipv4/ipmr.c#L842">842</a> }
<a name="L843" href="source/net/ipv4/ipmr.c#L843">843</a> 
<a name="L844" href="source/net/ipv4/ipmr.c#L844">844</a> <b><i>/* Look for a (*,*,oif) entry */</i></b>
<a name="L845" href="source/net/ipv4/ipmr.c#L845">845</a> static struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=ipmr_cache_find_any_parent">ipmr_cache_find_any_parent</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L846" href="source/net/ipv4/ipmr.c#L846">846</a>                                                     int vifi)
<a name="L847" href="source/net/ipv4/ipmr.c#L847">847</a> {
<a name="L848" href="source/net/ipv4/ipmr.c#L848">848</a>         int <a href="ident?i=line">line</a> = <a href="ident?i=MFC_HASH">MFC_HASH</a>(<a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>), <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>));
<a name="L849" href="source/net/ipv4/ipmr.c#L849">849</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>;
<a name="L850" href="source/net/ipv4/ipmr.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/ipmr.c#L851">851</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=c">c</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=line">line</a>], <a href="ident?i=list">list</a>)
<a name="L852" href="source/net/ipv4/ipmr.c#L852">852</a>                 if (<a href="ident?i=c">c</a>-&gt;mfc_origin == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp;
<a name="L853" href="source/net/ipv4/ipmr.c#L853">853</a>                     <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp;
<a name="L854" href="source/net/ipv4/ipmr.c#L854">854</a>                     <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[vifi] &lt; 255)
<a name="L855" href="source/net/ipv4/ipmr.c#L855">855</a>                         return <a href="ident?i=c">c</a>;
<a name="L856" href="source/net/ipv4/ipmr.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/ipmr.c#L857">857</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L858" href="source/net/ipv4/ipmr.c#L858">858</a> }
<a name="L859" href="source/net/ipv4/ipmr.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/ipmr.c#L860">860</a> <b><i>/* Look for a (*,G) entry */</i></b>
<a name="L861" href="source/net/ipv4/ipmr.c#L861">861</a> static struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=ipmr_cache_find_any">ipmr_cache_find_any</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L862" href="source/net/ipv4/ipmr.c#L862">862</a>                                              <a href="ident?i=__be32">__be32</a> mcastgrp, int vifi)
<a name="L863" href="source/net/ipv4/ipmr.c#L863">863</a> {
<a name="L864" href="source/net/ipv4/ipmr.c#L864">864</a>         int <a href="ident?i=line">line</a> = <a href="ident?i=MFC_HASH">MFC_HASH</a>(mcastgrp, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>));
<a name="L865" href="source/net/ipv4/ipmr.c#L865">865</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, *proxy;
<a name="L866" href="source/net/ipv4/ipmr.c#L866">866</a> 
<a name="L867" href="source/net/ipv4/ipmr.c#L867">867</a>         if (mcastgrp == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>))
<a name="L868" href="source/net/ipv4/ipmr.c#L868">868</a>                 goto <a href="ident?i=skip">skip</a>;
<a name="L869" href="source/net/ipv4/ipmr.c#L869">869</a> 
<a name="L870" href="source/net/ipv4/ipmr.c#L870">870</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=c">c</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=line">line</a>], <a href="ident?i=list">list</a>)
<a name="L871" href="source/net/ipv4/ipmr.c#L871">871</a>                 if (<a href="ident?i=c">c</a>-&gt;mfc_origin == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp;
<a name="L872" href="source/net/ipv4/ipmr.c#L872">872</a>                     <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp == mcastgrp) {
<a name="L873" href="source/net/ipv4/ipmr.c#L873">873</a>                         if (<a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[vifi] &lt; 255)
<a name="L874" href="source/net/ipv4/ipmr.c#L874">874</a>                                 return <a href="ident?i=c">c</a>;
<a name="L875" href="source/net/ipv4/ipmr.c#L875">875</a> 
<a name="L876" href="source/net/ipv4/ipmr.c#L876">876</a>                         <b><i>/* It's ok if the vifi is part of the static tree */</i></b>
<a name="L877" href="source/net/ipv4/ipmr.c#L877">877</a>                         proxy = <a href="ident?i=ipmr_cache_find_any_parent">ipmr_cache_find_any_parent</a>(mrt,
<a name="L878" href="source/net/ipv4/ipmr.c#L878">878</a>                                                            <a href="ident?i=c">c</a>-&gt;mfc_parent);
<a name="L879" href="source/net/ipv4/ipmr.c#L879">879</a>                         if (proxy &amp;&amp; proxy-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[vifi] &lt; 255)
<a name="L880" href="source/net/ipv4/ipmr.c#L880">880</a>                                 return <a href="ident?i=c">c</a>;
<a name="L881" href="source/net/ipv4/ipmr.c#L881">881</a>                 }
<a name="L882" href="source/net/ipv4/ipmr.c#L882">882</a> 
<a name="L883" href="source/net/ipv4/ipmr.c#L883">883</a> <a href="ident?i=skip">skip</a>:
<a name="L884" href="source/net/ipv4/ipmr.c#L884">884</a>         return <a href="ident?i=ipmr_cache_find_any_parent">ipmr_cache_find_any_parent</a>(mrt, vifi);
<a name="L885" href="source/net/ipv4/ipmr.c#L885">885</a> }
<a name="L886" href="source/net/ipv4/ipmr.c#L886">886</a> 
<a name="L887" href="source/net/ipv4/ipmr.c#L887">887</a> <b><i>/*</i></b>
<a name="L888" href="source/net/ipv4/ipmr.c#L888">888</a> <b><i> *      Allocate a multicast cache entry</i></b>
<a name="L889" href="source/net/ipv4/ipmr.c#L889">889</a> <b><i> */</i></b>
<a name="L890" href="source/net/ipv4/ipmr.c#L890">890</a> static struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=ipmr_cache_alloc">ipmr_cache_alloc</a>(void)
<a name="L891" href="source/net/ipv4/ipmr.c#L891">891</a> {
<a name="L892" href="source/net/ipv4/ipmr.c#L892">892</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a> = <a href="ident?i=kmem_cache_zalloc">kmem_cache_zalloc</a>(mrt_cachep, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L893" href="source/net/ipv4/ipmr.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/ipmr.c#L894">894</a>         if (<a href="ident?i=c">c</a>)
<a name="L895" href="source/net/ipv4/ipmr.c#L895">895</a>                 <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif = <a href="ident?i=MAXVIFS">MAXVIFS</a>;
<a name="L896" href="source/net/ipv4/ipmr.c#L896">896</a>         return <a href="ident?i=c">c</a>;
<a name="L897" href="source/net/ipv4/ipmr.c#L897">897</a> }
<a name="L898" href="source/net/ipv4/ipmr.c#L898">898</a> 
<a name="L899" href="source/net/ipv4/ipmr.c#L899">899</a> static struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=ipmr_cache_alloc_unres">ipmr_cache_alloc_unres</a>(void)
<a name="L900" href="source/net/ipv4/ipmr.c#L900">900</a> {
<a name="L901" href="source/net/ipv4/ipmr.c#L901">901</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a> = <a href="ident?i=kmem_cache_zalloc">kmem_cache_zalloc</a>(mrt_cachep, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L902" href="source/net/ipv4/ipmr.c#L902">902</a> 
<a name="L903" href="source/net/ipv4/ipmr.c#L903">903</a>         if (<a href="ident?i=c">c</a>) {
<a name="L904" href="source/net/ipv4/ipmr.c#L904">904</a>                 <a href="ident?i=skb_queue_head_init">skb_queue_head_init</a>(&amp;<a href="ident?i=c">c</a>-&gt;mfc_un.unres.<a href="ident?i=unresolved">unresolved</a>);
<a name="L905" href="source/net/ipv4/ipmr.c#L905">905</a>                 <a href="ident?i=c">c</a>-&gt;mfc_un.unres.expires = <a href="ident?i=jiffies">jiffies</a> + 10*<a href="ident?i=HZ">HZ</a>;
<a name="L906" href="source/net/ipv4/ipmr.c#L906">906</a>         }
<a name="L907" href="source/net/ipv4/ipmr.c#L907">907</a>         return <a href="ident?i=c">c</a>;
<a name="L908" href="source/net/ipv4/ipmr.c#L908">908</a> }
<a name="L909" href="source/net/ipv4/ipmr.c#L909">909</a> 
<a name="L910" href="source/net/ipv4/ipmr.c#L910">910</a> <b><i>/*</i></b>
<a name="L911" href="source/net/ipv4/ipmr.c#L911">911</a> <b><i> *      A cache entry has gone into a resolved state from queued</i></b>
<a name="L912" href="source/net/ipv4/ipmr.c#L912">912</a> <b><i> */</i></b>
<a name="L913" href="source/net/ipv4/ipmr.c#L913">913</a> 
<a name="L914" href="source/net/ipv4/ipmr.c#L914">914</a> static void <a href="ident?i=ipmr_cache_resolve">ipmr_cache_resolve</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L915" href="source/net/ipv4/ipmr.c#L915">915</a>                                struct <a href="ident?i=mfc_cache">mfc_cache</a> *uc, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>)
<a name="L916" href="source/net/ipv4/ipmr.c#L916">916</a> {
<a name="L917" href="source/net/ipv4/ipmr.c#L917">917</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L918" href="source/net/ipv4/ipmr.c#L918">918</a>         struct <a href="ident?i=nlmsgerr">nlmsgerr</a> *<a href="ident?i=e">e</a>;
<a name="L919" href="source/net/ipv4/ipmr.c#L919">919</a> 
<a name="L920" href="source/net/ipv4/ipmr.c#L920">920</a>         <b><i>/* Play the pending entries through our router */</i></b>
<a name="L921" href="source/net/ipv4/ipmr.c#L921">921</a> 
<a name="L922" href="source/net/ipv4/ipmr.c#L922">922</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(&amp;uc-&gt;mfc_un.unres.<a href="ident?i=unresolved">unresolved</a>))) {
<a name="L923" href="source/net/ipv4/ipmr.c#L923">923</a>                 if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=version">version</a> == 0) {
<a name="L924" href="source/net/ipv4/ipmr.c#L924">924</a>                         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh = (struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *)<a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L925" href="source/net/ipv4/ipmr.c#L925">925</a> 
<a name="L926" href="source/net/ipv4/ipmr.c#L926">926</a>                         if (<a href="ident?i=__ipmr_fill_mroute">__ipmr_fill_mroute</a>(mrt, <a href="ident?i=skb">skb</a>, <a href="ident?i=c">c</a>, <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh)) &gt; 0) {
<a name="L927" href="source/net/ipv4/ipmr.c#L927">927</a>                                 nlh-&gt;<a href="ident?i=nlmsg_len">nlmsg_len</a> = <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>) -
<a name="L928" href="source/net/ipv4/ipmr.c#L928">928</a>                                                  (<a href="ident?i=u8">u8</a> *)nlh;
<a name="L929" href="source/net/ipv4/ipmr.c#L929">929</a>                         } else {
<a name="L930" href="source/net/ipv4/ipmr.c#L930">930</a>                                 nlh-&gt;nlmsg_type = <a href="ident?i=NLMSG_ERROR">NLMSG_ERROR</a>;
<a name="L931" href="source/net/ipv4/ipmr.c#L931">931</a>                                 nlh-&gt;<a href="ident?i=nlmsg_len">nlmsg_len</a> = <a href="ident?i=nlmsg_msg_size">nlmsg_msg_size</a>(sizeof(struct <a href="ident?i=nlmsgerr">nlmsgerr</a>));
<a name="L932" href="source/net/ipv4/ipmr.c#L932">932</a>                                 <a href="ident?i=skb_trim">skb_trim</a>(<a href="ident?i=skb">skb</a>, nlh-&gt;<a href="ident?i=nlmsg_len">nlmsg_len</a>);
<a name="L933" href="source/net/ipv4/ipmr.c#L933">933</a>                                 <a href="ident?i=e">e</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L934" href="source/net/ipv4/ipmr.c#L934">934</a>                                 <a href="ident?i=e">e</a>-&gt;<a href="ident?i=error">error</a> = -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L935" href="source/net/ipv4/ipmr.c#L935">935</a>                                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=msg">msg</a>, 0, sizeof(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=msg">msg</a>));
<a name="L936" href="source/net/ipv4/ipmr.c#L936">936</a>                         }
<a name="L937" href="source/net/ipv4/ipmr.c#L937">937</a> 
<a name="L938" href="source/net/ipv4/ipmr.c#L938">938</a>                         <a href="ident?i=rtnl_unicast">rtnl_unicast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid);
<a name="L939" href="source/net/ipv4/ipmr.c#L939">939</a>                 } else {
<a name="L940" href="source/net/ipv4/ipmr.c#L940">940</a>                         <a href="ident?i=ip_mr_forward">ip_mr_forward</a>(<a href="ident?i=net">net</a>, mrt, <a href="ident?i=skb">skb</a>, <a href="ident?i=c">c</a>, 0);
<a name="L941" href="source/net/ipv4/ipmr.c#L941">941</a>                 }
<a name="L942" href="source/net/ipv4/ipmr.c#L942">942</a>         }
<a name="L943" href="source/net/ipv4/ipmr.c#L943">943</a> }
<a name="L944" href="source/net/ipv4/ipmr.c#L944">944</a> 
<a name="L945" href="source/net/ipv4/ipmr.c#L945">945</a> <b><i>/*</i></b>
<a name="L946" href="source/net/ipv4/ipmr.c#L946">946</a> <b><i> *      Bounce a cache query up to mrouted. We could use netlink for this but mrouted</i></b>
<a name="L947" href="source/net/ipv4/ipmr.c#L947">947</a> <b><i> *      expects the following bizarre scheme.</i></b>
<a name="L948" href="source/net/ipv4/ipmr.c#L948">948</a> <b><i> *</i></b>
<a name="L949" href="source/net/ipv4/ipmr.c#L949">949</a> <b><i> *      Called under mrt_lock.</i></b>
<a name="L950" href="source/net/ipv4/ipmr.c#L950">950</a> <b><i> */</i></b>
<a name="L951" href="source/net/ipv4/ipmr.c#L951">951</a> 
<a name="L952" href="source/net/ipv4/ipmr.c#L952">952</a> static int <a href="ident?i=ipmr_cache_report">ipmr_cache_report</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L953" href="source/net/ipv4/ipmr.c#L953">953</a>                              struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=pkt">pkt</a>, <a href="ident?i=vifi_t">vifi_t</a> vifi, int <a href="ident?i=assert">assert</a>)
<a name="L954" href="source/net/ipv4/ipmr.c#L954">954</a> {
<a name="L955" href="source/net/ipv4/ipmr.c#L955">955</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L956" href="source/net/ipv4/ipmr.c#L956">956</a>         const int ihl = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=pkt">pkt</a>);
<a name="L957" href="source/net/ipv4/ipmr.c#L957">957</a>         struct <a href="ident?i=igmphdr">igmphdr</a> *igmp;
<a name="L958" href="source/net/ipv4/ipmr.c#L958">958</a>         struct <a href="ident?i=igmpmsg">igmpmsg</a> *<a href="ident?i=msg">msg</a>;
<a name="L959" href="source/net/ipv4/ipmr.c#L959">959</a>         struct <a href="ident?i=sock">sock</a> *mroute_sk;
<a name="L960" href="source/net/ipv4/ipmr.c#L960">960</a>         int <a href="ident?i=ret">ret</a>;
<a name="L961" href="source/net/ipv4/ipmr.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/ipmr.c#L962">962</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L963" href="source/net/ipv4/ipmr.c#L963">963</a>         if (<a href="ident?i=assert">assert</a> == <a href="ident?i=IGMPMSG_WHOLEPKT">IGMPMSG_WHOLEPKT</a>)
<a name="L964" href="source/net/ipv4/ipmr.c#L964">964</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_realloc_headroom">skb_realloc_headroom</a>(<a href="ident?i=pkt">pkt</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L965" href="source/net/ipv4/ipmr.c#L965">965</a>         else
<a name="L966" href="source/net/ipv4/ipmr.c#L966">966</a> #endif
<a name="L967" href="source/net/ipv4/ipmr.c#L967">967</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(128, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L968" href="source/net/ipv4/ipmr.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/ipmr.c#L969">969</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L970" href="source/net/ipv4/ipmr.c#L970">970</a>                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L971" href="source/net/ipv4/ipmr.c#L971">971</a> 
<a name="L972" href="source/net/ipv4/ipmr.c#L972">972</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L973" href="source/net/ipv4/ipmr.c#L973">973</a>         if (<a href="ident?i=assert">assert</a> == <a href="ident?i=IGMPMSG_WHOLEPKT">IGMPMSG_WHOLEPKT</a>) {
<a name="L974" href="source/net/ipv4/ipmr.c#L974">974</a>                 <b><i>/* Ugly, but we have no choice with this interface.</i></b>
<a name="L975" href="source/net/ipv4/ipmr.c#L975">975</a> <b><i>                 * Duplicate old header, fix ihl, length etc.</i></b>
<a name="L976" href="source/net/ipv4/ipmr.c#L976">976</a> <b><i>                 * And all this only to mangle msg-&gt;im_msgtype and</i></b>
<a name="L977" href="source/net/ipv4/ipmr.c#L977">977</a> <b><i>                 * to set msg-&gt;im_mbz to "mbz" :-)</i></b>
<a name="L978" href="source/net/ipv4/ipmr.c#L978">978</a> <b><i>                 */</i></b>
<a name="L979" href="source/net/ipv4/ipmr.c#L979">979</a>                 <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L980" href="source/net/ipv4/ipmr.c#L980">980</a>                 <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L981" href="source/net/ipv4/ipmr.c#L981">981</a>                 <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L982" href="source/net/ipv4/ipmr.c#L982">982</a>                 <a href="ident?i=msg">msg</a> = (struct <a href="ident?i=igmpmsg">igmpmsg</a> *)<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L983" href="source/net/ipv4/ipmr.c#L983">983</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=pkt">pkt</a>), sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L984" href="source/net/ipv4/ipmr.c#L984">984</a>                 <a href="ident?i=msg">msg</a>-&gt;im_msgtype = <a href="ident?i=IGMPMSG_WHOLEPKT">IGMPMSG_WHOLEPKT</a>;
<a name="L985" href="source/net/ipv4/ipmr.c#L985">985</a>                 <a href="ident?i=msg">msg</a>-&gt;im_mbz = 0;
<a name="L986" href="source/net/ipv4/ipmr.c#L986">986</a>                 <a href="ident?i=msg">msg</a>-&gt;im_vif = mrt-&gt;mroute_reg_vif_num;
<a name="L987" href="source/net/ipv4/ipmr.c#L987">987</a>                 <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;ihl = sizeof(struct <a href="ident?i=iphdr">iphdr</a>) &gt;&gt; 2;
<a name="L988" href="source/net/ipv4/ipmr.c#L988">988</a>                 <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=pkt">pkt</a>)-&gt;tot_len) +
<a name="L989" href="source/net/ipv4/ipmr.c#L989">989</a>                                              sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L990" href="source/net/ipv4/ipmr.c#L990">990</a>         } else
<a name="L991" href="source/net/ipv4/ipmr.c#L991">991</a> #endif
<a name="L992" href="source/net/ipv4/ipmr.c#L992">992</a>         {
<a name="L993" href="source/net/ipv4/ipmr.c#L993">993</a> 
<a name="L994" href="source/net/ipv4/ipmr.c#L994">994</a>         <b><i>/* Copy the IP header */</i></b>
<a name="L995" href="source/net/ipv4/ipmr.c#L995">995</a> 
<a name="L996" href="source/net/ipv4/ipmr.c#L996">996</a>         <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L997" href="source/net/ipv4/ipmr.c#L997">997</a>         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, ihl);
<a name="L998" href="source/net/ipv4/ipmr.c#L998">998</a>         <a href="ident?i=skb_copy_to_linear_data">skb_copy_to_linear_data</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pkt">pkt</a>-&gt;<a href="ident?i=data">data</a>, ihl);
<a name="L999" href="source/net/ipv4/ipmr.c#L999">999</a>         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> = 0;      <b><i>/* Flag to the kernel this is a route add */</i></b>
<a name="L1000" href="source/net/ipv4/ipmr.c#L1000">1000</a>         <a href="ident?i=msg">msg</a> = (struct <a href="ident?i=igmpmsg">igmpmsg</a> *)<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1001" href="source/net/ipv4/ipmr.c#L1001">1001</a>         <a href="ident?i=msg">msg</a>-&gt;im_vif = vifi;
<a name="L1002" href="source/net/ipv4/ipmr.c#L1002">1002</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst_clone">dst_clone</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=pkt">pkt</a>)));
<a name="L1003" href="source/net/ipv4/ipmr.c#L1003">1003</a> 
<a name="L1004" href="source/net/ipv4/ipmr.c#L1004">1004</a>         <b><i>/* Add our header */</i></b>
<a name="L1005" href="source/net/ipv4/ipmr.c#L1005">1005</a> 
<a name="L1006" href="source/net/ipv4/ipmr.c#L1006">1006</a>         igmp = (struct <a href="ident?i=igmphdr">igmphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=igmphdr">igmphdr</a>));
<a name="L1007" href="source/net/ipv4/ipmr.c#L1007">1007</a>         igmp-&gt;<a href="ident?i=type">type</a>      =
<a name="L1008" href="source/net/ipv4/ipmr.c#L1008">1008</a>         <a href="ident?i=msg">msg</a>-&gt;im_msgtype = <a href="ident?i=assert">assert</a>;
<a name="L1009" href="source/net/ipv4/ipmr.c#L1009">1009</a>         igmp-&gt;<a href="ident?i=code">code</a>      = 0;
<a name="L1010" href="source/net/ipv4/ipmr.c#L1010">1010</a>         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);         <b><i>/* Fix the length */</i></b>
<a name="L1011" href="source/net/ipv4/ipmr.c#L1011">1011</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header;
<a name="L1012" href="source/net/ipv4/ipmr.c#L1012">1012</a>         }
<a name="L1013" href="source/net/ipv4/ipmr.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/ipmr.c#L1014">1014</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1015" href="source/net/ipv4/ipmr.c#L1015">1015</a>         mroute_sk = <a href="ident?i=rcu_dereference">rcu_dereference</a>(mrt-&gt;mroute_sk);
<a name="L1016" href="source/net/ipv4/ipmr.c#L1016">1016</a>         if (!mroute_sk) {
<a name="L1017" href="source/net/ipv4/ipmr.c#L1017">1017</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1018" href="source/net/ipv4/ipmr.c#L1018">1018</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1019" href="source/net/ipv4/ipmr.c#L1019">1019</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1020" href="source/net/ipv4/ipmr.c#L1020">1020</a>         }
<a name="L1021" href="source/net/ipv4/ipmr.c#L1021">1021</a> 
<a name="L1022" href="source/net/ipv4/ipmr.c#L1022">1022</a>         <b><i>/* Deliver to mrouted */</i></b>
<a name="L1023" href="source/net/ipv4/ipmr.c#L1023">1023</a> 
<a name="L1024" href="source/net/ipv4/ipmr.c#L1024">1024</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=sock_queue_rcv_skb">sock_queue_rcv_skb</a>(mroute_sk, <a href="ident?i=skb">skb</a>);
<a name="L1025" href="source/net/ipv4/ipmr.c#L1025">1025</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1026" href="source/net/ipv4/ipmr.c#L1026">1026</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L1027" href="source/net/ipv4/ipmr.c#L1027">1027</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"mroute: pending queue full, dropping entries\n"</i>);
<a name="L1028" href="source/net/ipv4/ipmr.c#L1028">1028</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1029" href="source/net/ipv4/ipmr.c#L1029">1029</a>         }
<a name="L1030" href="source/net/ipv4/ipmr.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/ipmr.c#L1031">1031</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1032" href="source/net/ipv4/ipmr.c#L1032">1032</a> }
<a name="L1033" href="source/net/ipv4/ipmr.c#L1033">1033</a> 
<a name="L1034" href="source/net/ipv4/ipmr.c#L1034">1034</a> <b><i>/*</i></b>
<a name="L1035" href="source/net/ipv4/ipmr.c#L1035">1035</a> <b><i> *      Queue a packet for resolution. It gets locked cache entry!</i></b>
<a name="L1036" href="source/net/ipv4/ipmr.c#L1036">1036</a> <b><i> */</i></b>
<a name="L1037" href="source/net/ipv4/ipmr.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/ipmr.c#L1038">1038</a> static int
<a name="L1039" href="source/net/ipv4/ipmr.c#L1039">1039</a> <a href="ident?i=ipmr_cache_unresolved">ipmr_cache_unresolved</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, <a href="ident?i=vifi_t">vifi_t</a> vifi, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1040" href="source/net/ipv4/ipmr.c#L1040">1040</a> {
<a name="L1041" href="source/net/ipv4/ipmr.c#L1041">1041</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=found">found</a> = <a href="ident?i=false">false</a>;
<a name="L1042" href="source/net/ipv4/ipmr.c#L1042">1042</a>         int <a href="ident?i=err">err</a>;
<a name="L1043" href="source/net/ipv4/ipmr.c#L1043">1043</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>;
<a name="L1044" href="source/net/ipv4/ipmr.c#L1044">1044</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1045" href="source/net/ipv4/ipmr.c#L1045">1045</a> 
<a name="L1046" href="source/net/ipv4/ipmr.c#L1046">1046</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;mfc_unres_lock);
<a name="L1047" href="source/net/ipv4/ipmr.c#L1047">1047</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(<a href="ident?i=c">c</a>, &amp;mrt-&gt;mfc_unres_queue, <a href="ident?i=list">list</a>) {
<a name="L1048" href="source/net/ipv4/ipmr.c#L1048">1048</a>                 if (<a href="ident?i=c">c</a>-&gt;mfc_mcastgrp == iph-&gt;<a href="ident?i=daddr">daddr</a> &amp;&amp;
<a name="L1049" href="source/net/ipv4/ipmr.c#L1049">1049</a>                     <a href="ident?i=c">c</a>-&gt;mfc_origin == iph-&gt;<a href="ident?i=saddr">saddr</a>) {
<a name="L1050" href="source/net/ipv4/ipmr.c#L1050">1050</a>                         <a href="ident?i=found">found</a> = <a href="ident?i=true">true</a>;
<a name="L1051" href="source/net/ipv4/ipmr.c#L1051">1051</a>                         break;
<a name="L1052" href="source/net/ipv4/ipmr.c#L1052">1052</a>                 }
<a name="L1053" href="source/net/ipv4/ipmr.c#L1053">1053</a>         }
<a name="L1054" href="source/net/ipv4/ipmr.c#L1054">1054</a> 
<a name="L1055" href="source/net/ipv4/ipmr.c#L1055">1055</a>         if (!<a href="ident?i=found">found</a>) {
<a name="L1056" href="source/net/ipv4/ipmr.c#L1056">1056</a>                 <b><i>/* Create a new entry if allowable */</i></b>
<a name="L1057" href="source/net/ipv4/ipmr.c#L1057">1057</a> 
<a name="L1058" href="source/net/ipv4/ipmr.c#L1058">1058</a>                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;mrt-&gt;cache_resolve_queue_len) &gt;= 10 ||
<a name="L1059" href="source/net/ipv4/ipmr.c#L1059">1059</a>                     (<a href="ident?i=c">c</a> = <a href="ident?i=ipmr_cache_alloc_unres">ipmr_cache_alloc_unres</a>()) == <a href="ident?i=NULL">NULL</a>) {
<a name="L1060" href="source/net/ipv4/ipmr.c#L1060">1060</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L1061" href="source/net/ipv4/ipmr.c#L1061">1061</a> 
<a name="L1062" href="source/net/ipv4/ipmr.c#L1062">1062</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1063" href="source/net/ipv4/ipmr.c#L1063">1063</a>                         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1064" href="source/net/ipv4/ipmr.c#L1064">1064</a>                 }
<a name="L1065" href="source/net/ipv4/ipmr.c#L1065">1065</a> 
<a name="L1066" href="source/net/ipv4/ipmr.c#L1066">1066</a>                 <b><i>/* Fill in the new cache entry */</i></b>
<a name="L1067" href="source/net/ipv4/ipmr.c#L1067">1067</a> 
<a name="L1068" href="source/net/ipv4/ipmr.c#L1068">1068</a>                 <a href="ident?i=c">c</a>-&gt;mfc_parent   = -1;
<a name="L1069" href="source/net/ipv4/ipmr.c#L1069">1069</a>                 <a href="ident?i=c">c</a>-&gt;mfc_origin   = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1070" href="source/net/ipv4/ipmr.c#L1070">1070</a>                 <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L1071" href="source/net/ipv4/ipmr.c#L1071">1071</a> 
<a name="L1072" href="source/net/ipv4/ipmr.c#L1072">1072</a>                 <b><i>/* Reflect first query at mrouted. */</i></b>
<a name="L1073" href="source/net/ipv4/ipmr.c#L1073">1073</a> 
<a name="L1074" href="source/net/ipv4/ipmr.c#L1074">1074</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_cache_report">ipmr_cache_report</a>(mrt, <a href="ident?i=skb">skb</a>, vifi, <a href="ident?i=IGMPMSG_NOCACHE">IGMPMSG_NOCACHE</a>);
<a name="L1075" href="source/net/ipv4/ipmr.c#L1075">1075</a>                 if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L1076" href="source/net/ipv4/ipmr.c#L1076">1076</a>                         <b><i>/* If the report failed throw the cache entry</i></b>
<a name="L1077" href="source/net/ipv4/ipmr.c#L1077">1077</a> <b><i>                           out - Brad Parker</i></b>
<a name="L1078" href="source/net/ipv4/ipmr.c#L1078">1078</a> <b><i>                         */</i></b>
<a name="L1079" href="source/net/ipv4/ipmr.c#L1079">1079</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L1080" href="source/net/ipv4/ipmr.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/ipmr.c#L1081">1081</a>                         <a href="ident?i=ipmr_cache_free">ipmr_cache_free</a>(<a href="ident?i=c">c</a>);
<a name="L1082" href="source/net/ipv4/ipmr.c#L1082">1082</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1083" href="source/net/ipv4/ipmr.c#L1083">1083</a>                         return <a href="ident?i=err">err</a>;
<a name="L1084" href="source/net/ipv4/ipmr.c#L1084">1084</a>                 }
<a name="L1085" href="source/net/ipv4/ipmr.c#L1085">1085</a> 
<a name="L1086" href="source/net/ipv4/ipmr.c#L1086">1086</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;mrt-&gt;cache_resolve_queue_len);
<a name="L1087" href="source/net/ipv4/ipmr.c#L1087">1087</a>                 <a href="ident?i=list_add">list_add</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>, &amp;mrt-&gt;mfc_unres_queue);
<a name="L1088" href="source/net/ipv4/ipmr.c#L1088">1088</a>                 <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>);
<a name="L1089" href="source/net/ipv4/ipmr.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/ipmr.c#L1090">1090</a>                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;mrt-&gt;cache_resolve_queue_len) == 1)
<a name="L1091" href="source/net/ipv4/ipmr.c#L1091">1091</a>                         <a href="ident?i=mod_timer">mod_timer</a>(&amp;mrt-&gt;ipmr_expire_timer, <a href="ident?i=c">c</a>-&gt;mfc_un.unres.expires);
<a name="L1092" href="source/net/ipv4/ipmr.c#L1092">1092</a>         }
<a name="L1093" href="source/net/ipv4/ipmr.c#L1093">1093</a> 
<a name="L1094" href="source/net/ipv4/ipmr.c#L1094">1094</a>         <b><i>/* See if we can append the packet */</i></b>
<a name="L1095" href="source/net/ipv4/ipmr.c#L1095">1095</a> 
<a name="L1096" href="source/net/ipv4/ipmr.c#L1096">1096</a>         if (<a href="ident?i=c">c</a>-&gt;mfc_un.unres.<a href="ident?i=unresolved">unresolved</a>.<a href="ident?i=qlen">qlen</a> &gt; 3) {
<a name="L1097" href="source/net/ipv4/ipmr.c#L1097">1097</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1098" href="source/net/ipv4/ipmr.c#L1098">1098</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1099" href="source/net/ipv4/ipmr.c#L1099">1099</a>         } else {
<a name="L1100" href="source/net/ipv4/ipmr.c#L1100">1100</a>                 <a href="ident?i=skb_queue_tail">skb_queue_tail</a>(&amp;<a href="ident?i=c">c</a>-&gt;mfc_un.unres.<a href="ident?i=unresolved">unresolved</a>, <a href="ident?i=skb">skb</a>);
<a name="L1101" href="source/net/ipv4/ipmr.c#L1101">1101</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L1102" href="source/net/ipv4/ipmr.c#L1102">1102</a>         }
<a name="L1103" href="source/net/ipv4/ipmr.c#L1103">1103</a> 
<a name="L1104" href="source/net/ipv4/ipmr.c#L1104">1104</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L1105" href="source/net/ipv4/ipmr.c#L1105">1105</a>         return <a href="ident?i=err">err</a>;
<a name="L1106" href="source/net/ipv4/ipmr.c#L1106">1106</a> }
<a name="L1107" href="source/net/ipv4/ipmr.c#L1107">1107</a> 
<a name="L1108" href="source/net/ipv4/ipmr.c#L1108">1108</a> <b><i>/*</i></b>
<a name="L1109" href="source/net/ipv4/ipmr.c#L1109">1109</a> <b><i> *      MFC cache manipulation by user space mroute daemon</i></b>
<a name="L1110" href="source/net/ipv4/ipmr.c#L1110">1110</a> <b><i> */</i></b>
<a name="L1111" href="source/net/ipv4/ipmr.c#L1111">1111</a> 
<a name="L1112" href="source/net/ipv4/ipmr.c#L1112">1112</a> static int <a href="ident?i=ipmr_mfc_delete">ipmr_mfc_delete</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=mfcctl">mfcctl</a> *mfc, int <a href="ident?i=parent">parent</a>)
<a name="L1113" href="source/net/ipv4/ipmr.c#L1113">1113</a> {
<a name="L1114" href="source/net/ipv4/ipmr.c#L1114">1114</a>         int <a href="ident?i=line">line</a>;
<a name="L1115" href="source/net/ipv4/ipmr.c#L1115">1115</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, *<a href="ident?i=next">next</a>;
<a name="L1116" href="source/net/ipv4/ipmr.c#L1116">1116</a> 
<a name="L1117" href="source/net/ipv4/ipmr.c#L1117">1117</a>         <a href="ident?i=line">line</a> = <a href="ident?i=MFC_HASH">MFC_HASH</a>(mfc-&gt;mfcc_mcastgrp.s_addr, mfc-&gt;mfcc_origin.s_addr);
<a name="L1118" href="source/net/ipv4/ipmr.c#L1118">1118</a> 
<a name="L1119" href="source/net/ipv4/ipmr.c#L1119">1119</a>         <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=c">c</a>, <a href="ident?i=next">next</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=line">line</a>], <a href="ident?i=list">list</a>) {
<a name="L1120" href="source/net/ipv4/ipmr.c#L1120">1120</a>                 if (<a href="ident?i=c">c</a>-&gt;mfc_origin == mfc-&gt;mfcc_origin.s_addr &amp;&amp;
<a name="L1121" href="source/net/ipv4/ipmr.c#L1121">1121</a>                     <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp == mfc-&gt;mfcc_mcastgrp.s_addr &amp;&amp;
<a name="L1122" href="source/net/ipv4/ipmr.c#L1122">1122</a>                     (<a href="ident?i=parent">parent</a> == -1 || <a href="ident?i=parent">parent</a> == <a href="ident?i=c">c</a>-&gt;mfc_parent)) {
<a name="L1123" href="source/net/ipv4/ipmr.c#L1123">1123</a>                         <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L1124" href="source/net/ipv4/ipmr.c#L1124">1124</a>                         <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>);
<a name="L1125" href="source/net/ipv4/ipmr.c#L1125">1125</a>                         <a href="ident?i=ipmr_cache_free">ipmr_cache_free</a>(<a href="ident?i=c">c</a>);
<a name="L1126" href="source/net/ipv4/ipmr.c#L1126">1126</a>                         return 0;
<a name="L1127" href="source/net/ipv4/ipmr.c#L1127">1127</a>                 }
<a name="L1128" href="source/net/ipv4/ipmr.c#L1128">1128</a>         }
<a name="L1129" href="source/net/ipv4/ipmr.c#L1129">1129</a>         return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1130" href="source/net/ipv4/ipmr.c#L1130">1130</a> }
<a name="L1131" href="source/net/ipv4/ipmr.c#L1131">1131</a> 
<a name="L1132" href="source/net/ipv4/ipmr.c#L1132">1132</a> static int <a href="ident?i=ipmr_mfc_add">ipmr_mfc_add</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L1133" href="source/net/ipv4/ipmr.c#L1133">1133</a>                         struct <a href="ident?i=mfcctl">mfcctl</a> *mfc, int mrtsock, int <a href="ident?i=parent">parent</a>)
<a name="L1134" href="source/net/ipv4/ipmr.c#L1134">1134</a> {
<a name="L1135" href="source/net/ipv4/ipmr.c#L1135">1135</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=found">found</a> = <a href="ident?i=false">false</a>;
<a name="L1136" href="source/net/ipv4/ipmr.c#L1136">1136</a>         int <a href="ident?i=line">line</a>;
<a name="L1137" href="source/net/ipv4/ipmr.c#L1137">1137</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *uc, *<a href="ident?i=c">c</a>;
<a name="L1138" href="source/net/ipv4/ipmr.c#L1138">1138</a> 
<a name="L1139" href="source/net/ipv4/ipmr.c#L1139">1139</a>         if (mfc-&gt;mfcc_parent &gt;= <a href="ident?i=MAXVIFS">MAXVIFS</a>)
<a name="L1140" href="source/net/ipv4/ipmr.c#L1140">1140</a>                 return -<a href="ident?i=ENFILE">ENFILE</a>;
<a name="L1141" href="source/net/ipv4/ipmr.c#L1141">1141</a> 
<a name="L1142" href="source/net/ipv4/ipmr.c#L1142">1142</a>         <a href="ident?i=line">line</a> = <a href="ident?i=MFC_HASH">MFC_HASH</a>(mfc-&gt;mfcc_mcastgrp.s_addr, mfc-&gt;mfcc_origin.s_addr);
<a name="L1143" href="source/net/ipv4/ipmr.c#L1143">1143</a> 
<a name="L1144" href="source/net/ipv4/ipmr.c#L1144">1144</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(<a href="ident?i=c">c</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=line">line</a>], <a href="ident?i=list">list</a>) {
<a name="L1145" href="source/net/ipv4/ipmr.c#L1145">1145</a>                 if (<a href="ident?i=c">c</a>-&gt;mfc_origin == mfc-&gt;mfcc_origin.s_addr &amp;&amp;
<a name="L1146" href="source/net/ipv4/ipmr.c#L1146">1146</a>                     <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp == mfc-&gt;mfcc_mcastgrp.s_addr &amp;&amp;
<a name="L1147" href="source/net/ipv4/ipmr.c#L1147">1147</a>                     (<a href="ident?i=parent">parent</a> == -1 || <a href="ident?i=parent">parent</a> == <a href="ident?i=c">c</a>-&gt;mfc_parent)) {
<a name="L1148" href="source/net/ipv4/ipmr.c#L1148">1148</a>                         <a href="ident?i=found">found</a> = <a href="ident?i=true">true</a>;
<a name="L1149" href="source/net/ipv4/ipmr.c#L1149">1149</a>                         break;
<a name="L1150" href="source/net/ipv4/ipmr.c#L1150">1150</a>                 }
<a name="L1151" href="source/net/ipv4/ipmr.c#L1151">1151</a>         }
<a name="L1152" href="source/net/ipv4/ipmr.c#L1152">1152</a> 
<a name="L1153" href="source/net/ipv4/ipmr.c#L1153">1153</a>         if (<a href="ident?i=found">found</a>) {
<a name="L1154" href="source/net/ipv4/ipmr.c#L1154">1154</a>                 <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;mrt_lock);
<a name="L1155" href="source/net/ipv4/ipmr.c#L1155">1155</a>                 <a href="ident?i=c">c</a>-&gt;mfc_parent = mfc-&gt;mfcc_parent;
<a name="L1156" href="source/net/ipv4/ipmr.c#L1156">1156</a>                 <a href="ident?i=ipmr_update_thresholds">ipmr_update_thresholds</a>(mrt, <a href="ident?i=c">c</a>, mfc-&gt;mfcc_ttls);
<a name="L1157" href="source/net/ipv4/ipmr.c#L1157">1157</a>                 if (!mrtsock)
<a name="L1158" href="source/net/ipv4/ipmr.c#L1158">1158</a>                         <a href="ident?i=c">c</a>-&gt;mfc_flags |= <a href="ident?i=MFC_STATIC">MFC_STATIC</a>;
<a name="L1159" href="source/net/ipv4/ipmr.c#L1159">1159</a>                 <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;mrt_lock);
<a name="L1160" href="source/net/ipv4/ipmr.c#L1160">1160</a>                 <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>);
<a name="L1161" href="source/net/ipv4/ipmr.c#L1161">1161</a>                 return 0;
<a name="L1162" href="source/net/ipv4/ipmr.c#L1162">1162</a>         }
<a name="L1163" href="source/net/ipv4/ipmr.c#L1163">1163</a> 
<a name="L1164" href="source/net/ipv4/ipmr.c#L1164">1164</a>         if (mfc-&gt;mfcc_mcastgrp.s_addr != <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp;
<a name="L1165" href="source/net/ipv4/ipmr.c#L1165">1165</a>             !<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(mfc-&gt;mfcc_mcastgrp.s_addr))
<a name="L1166" href="source/net/ipv4/ipmr.c#L1166">1166</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1167" href="source/net/ipv4/ipmr.c#L1167">1167</a> 
<a name="L1168" href="source/net/ipv4/ipmr.c#L1168">1168</a>         <a href="ident?i=c">c</a> = <a href="ident?i=ipmr_cache_alloc">ipmr_cache_alloc</a>();
<a name="L1169" href="source/net/ipv4/ipmr.c#L1169">1169</a>         if (!<a href="ident?i=c">c</a>)
<a name="L1170" href="source/net/ipv4/ipmr.c#L1170">1170</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1171" href="source/net/ipv4/ipmr.c#L1171">1171</a> 
<a name="L1172" href="source/net/ipv4/ipmr.c#L1172">1172</a>         <a href="ident?i=c">c</a>-&gt;mfc_origin = mfc-&gt;mfcc_origin.s_addr;
<a name="L1173" href="source/net/ipv4/ipmr.c#L1173">1173</a>         <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp = mfc-&gt;mfcc_mcastgrp.s_addr;
<a name="L1174" href="source/net/ipv4/ipmr.c#L1174">1174</a>         <a href="ident?i=c">c</a>-&gt;mfc_parent = mfc-&gt;mfcc_parent;
<a name="L1175" href="source/net/ipv4/ipmr.c#L1175">1175</a>         <a href="ident?i=ipmr_update_thresholds">ipmr_update_thresholds</a>(mrt, <a href="ident?i=c">c</a>, mfc-&gt;mfcc_ttls);
<a name="L1176" href="source/net/ipv4/ipmr.c#L1176">1176</a>         if (!mrtsock)
<a name="L1177" href="source/net/ipv4/ipmr.c#L1177">1177</a>                 <a href="ident?i=c">c</a>-&gt;mfc_flags |= <a href="ident?i=MFC_STATIC">MFC_STATIC</a>;
<a name="L1178" href="source/net/ipv4/ipmr.c#L1178">1178</a> 
<a name="L1179" href="source/net/ipv4/ipmr.c#L1179">1179</a>         <a href="ident?i=list_add_rcu">list_add_rcu</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=line">line</a>]);
<a name="L1180" href="source/net/ipv4/ipmr.c#L1180">1180</a> 
<a name="L1181" href="source/net/ipv4/ipmr.c#L1181">1181</a>         <b><i>/*</i></b>
<a name="L1182" href="source/net/ipv4/ipmr.c#L1182">1182</a> <b><i>         *      Check to see if we resolved a queued list. If so we</i></b>
<a name="L1183" href="source/net/ipv4/ipmr.c#L1183">1183</a> <b><i>         *      need to send on the frames and tidy up.</i></b>
<a name="L1184" href="source/net/ipv4/ipmr.c#L1184">1184</a> <b><i>         */</i></b>
<a name="L1185" href="source/net/ipv4/ipmr.c#L1185">1185</a>         <a href="ident?i=found">found</a> = <a href="ident?i=false">false</a>;
<a name="L1186" href="source/net/ipv4/ipmr.c#L1186">1186</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;mfc_unres_lock);
<a name="L1187" href="source/net/ipv4/ipmr.c#L1187">1187</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(uc, &amp;mrt-&gt;mfc_unres_queue, <a href="ident?i=list">list</a>) {
<a name="L1188" href="source/net/ipv4/ipmr.c#L1188">1188</a>                 if (uc-&gt;mfc_origin == <a href="ident?i=c">c</a>-&gt;mfc_origin &amp;&amp;
<a name="L1189" href="source/net/ipv4/ipmr.c#L1189">1189</a>                     uc-&gt;mfc_mcastgrp == <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp) {
<a name="L1190" href="source/net/ipv4/ipmr.c#L1190">1190</a>                         <a href="ident?i=list_del">list_del</a>(&amp;uc-&gt;<a href="ident?i=list">list</a>);
<a name="L1191" href="source/net/ipv4/ipmr.c#L1191">1191</a>                         <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;mrt-&gt;cache_resolve_queue_len);
<a name="L1192" href="source/net/ipv4/ipmr.c#L1192">1192</a>                         <a href="ident?i=found">found</a> = <a href="ident?i=true">true</a>;
<a name="L1193" href="source/net/ipv4/ipmr.c#L1193">1193</a>                         break;
<a name="L1194" href="source/net/ipv4/ipmr.c#L1194">1194</a>                 }
<a name="L1195" href="source/net/ipv4/ipmr.c#L1195">1195</a>         }
<a name="L1196" href="source/net/ipv4/ipmr.c#L1196">1196</a>         if (<a href="ident?i=list_empty">list_empty</a>(&amp;mrt-&gt;mfc_unres_queue))
<a name="L1197" href="source/net/ipv4/ipmr.c#L1197">1197</a>                 <a href="ident?i=del_timer">del_timer</a>(&amp;mrt-&gt;ipmr_expire_timer);
<a name="L1198" href="source/net/ipv4/ipmr.c#L1198">1198</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L1199" href="source/net/ipv4/ipmr.c#L1199">1199</a> 
<a name="L1200" href="source/net/ipv4/ipmr.c#L1200">1200</a>         if (<a href="ident?i=found">found</a>) {
<a name="L1201" href="source/net/ipv4/ipmr.c#L1201">1201</a>                 <a href="ident?i=ipmr_cache_resolve">ipmr_cache_resolve</a>(<a href="ident?i=net">net</a>, mrt, uc, <a href="ident?i=c">c</a>);
<a name="L1202" href="source/net/ipv4/ipmr.c#L1202">1202</a>                 <a href="ident?i=ipmr_cache_free">ipmr_cache_free</a>(uc);
<a name="L1203" href="source/net/ipv4/ipmr.c#L1203">1203</a>         }
<a name="L1204" href="source/net/ipv4/ipmr.c#L1204">1204</a>         <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>);
<a name="L1205" href="source/net/ipv4/ipmr.c#L1205">1205</a>         return 0;
<a name="L1206" href="source/net/ipv4/ipmr.c#L1206">1206</a> }
<a name="L1207" href="source/net/ipv4/ipmr.c#L1207">1207</a> 
<a name="L1208" href="source/net/ipv4/ipmr.c#L1208">1208</a> <b><i>/*</i></b>
<a name="L1209" href="source/net/ipv4/ipmr.c#L1209">1209</a> <b><i> *      Close the multicast socket, and clear the vif tables etc</i></b>
<a name="L1210" href="source/net/ipv4/ipmr.c#L1210">1210</a> <b><i> */</i></b>
<a name="L1211" href="source/net/ipv4/ipmr.c#L1211">1211</a> 
<a name="L1212" href="source/net/ipv4/ipmr.c#L1212">1212</a> static void <a href="ident?i=mroute_clean_tables">mroute_clean_tables</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt)
<a name="L1213" href="source/net/ipv4/ipmr.c#L1213">1213</a> {
<a name="L1214" href="source/net/ipv4/ipmr.c#L1214">1214</a>         int <a href="ident?i=i">i</a>;
<a name="L1215" href="source/net/ipv4/ipmr.c#L1215">1215</a>         <a href="ident?i=LIST_HEAD">LIST_HEAD</a>(<a href="ident?i=list">list</a>);
<a name="L1216" href="source/net/ipv4/ipmr.c#L1216">1216</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, *<a href="ident?i=next">next</a>;
<a name="L1217" href="source/net/ipv4/ipmr.c#L1217">1217</a> 
<a name="L1218" href="source/net/ipv4/ipmr.c#L1218">1218</a>         <b><i>/* Shut down all active vif entries */</i></b>
<a name="L1219" href="source/net/ipv4/ipmr.c#L1219">1219</a> 
<a name="L1220" href="source/net/ipv4/ipmr.c#L1220">1220</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; mrt-&gt;maxvif; <a href="ident?i=i">i</a>++) {
<a name="L1221" href="source/net/ipv4/ipmr.c#L1221">1221</a>                 if (!(mrt-&gt;vif_table[<a href="ident?i=i">i</a>].<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=VIFF_STATIC">VIFF_STATIC</a>))
<a name="L1222" href="source/net/ipv4/ipmr.c#L1222">1222</a>                         <a href="ident?i=vif_delete">vif_delete</a>(mrt, <a href="ident?i=i">i</a>, 0, &amp;<a href="ident?i=list">list</a>);
<a name="L1223" href="source/net/ipv4/ipmr.c#L1223">1223</a>         }
<a name="L1224" href="source/net/ipv4/ipmr.c#L1224">1224</a>         <a href="ident?i=unregister_netdevice_many">unregister_netdevice_many</a>(&amp;<a href="ident?i=list">list</a>);
<a name="L1225" href="source/net/ipv4/ipmr.c#L1225">1225</a> 
<a name="L1226" href="source/net/ipv4/ipmr.c#L1226">1226</a>         <b><i>/* Wipe the cache */</i></b>
<a name="L1227" href="source/net/ipv4/ipmr.c#L1227">1227</a> 
<a name="L1228" href="source/net/ipv4/ipmr.c#L1228">1228</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=MFC_LINES">MFC_LINES</a>; <a href="ident?i=i">i</a>++) {
<a name="L1229" href="source/net/ipv4/ipmr.c#L1229">1229</a>                 <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=c">c</a>, <a href="ident?i=next">next</a>, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=i">i</a>], <a href="ident?i=list">list</a>) {
<a name="L1230" href="source/net/ipv4/ipmr.c#L1230">1230</a>                         if (<a href="ident?i=c">c</a>-&gt;mfc_flags &amp; <a href="ident?i=MFC_STATIC">MFC_STATIC</a>)
<a name="L1231" href="source/net/ipv4/ipmr.c#L1231">1231</a>                                 continue;
<a name="L1232" href="source/net/ipv4/ipmr.c#L1232">1232</a>                         <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L1233" href="source/net/ipv4/ipmr.c#L1233">1233</a>                         <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>);
<a name="L1234" href="source/net/ipv4/ipmr.c#L1234">1234</a>                         <a href="ident?i=ipmr_cache_free">ipmr_cache_free</a>(<a href="ident?i=c">c</a>);
<a name="L1235" href="source/net/ipv4/ipmr.c#L1235">1235</a>                 }
<a name="L1236" href="source/net/ipv4/ipmr.c#L1236">1236</a>         }
<a name="L1237" href="source/net/ipv4/ipmr.c#L1237">1237</a> 
<a name="L1238" href="source/net/ipv4/ipmr.c#L1238">1238</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;mrt-&gt;cache_resolve_queue_len) != 0) {
<a name="L1239" href="source/net/ipv4/ipmr.c#L1239">1239</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;mfc_unres_lock);
<a name="L1240" href="source/net/ipv4/ipmr.c#L1240">1240</a>                 <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=c">c</a>, <a href="ident?i=next">next</a>, &amp;mrt-&gt;mfc_unres_queue, <a href="ident?i=list">list</a>) {
<a name="L1241" href="source/net/ipv4/ipmr.c#L1241">1241</a>                         <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=c">c</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L1242" href="source/net/ipv4/ipmr.c#L1242">1242</a>                         <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(mrt, <a href="ident?i=c">c</a>, <a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>);
<a name="L1243" href="source/net/ipv4/ipmr.c#L1243">1243</a>                         <a href="ident?i=ipmr_destroy_unres">ipmr_destroy_unres</a>(mrt, <a href="ident?i=c">c</a>);
<a name="L1244" href="source/net/ipv4/ipmr.c#L1244">1244</a>                 }
<a name="L1245" href="source/net/ipv4/ipmr.c#L1245">1245</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L1246" href="source/net/ipv4/ipmr.c#L1246">1246</a>         }
<a name="L1247" href="source/net/ipv4/ipmr.c#L1247">1247</a> }
<a name="L1248" href="source/net/ipv4/ipmr.c#L1248">1248</a> 
<a name="L1249" href="source/net/ipv4/ipmr.c#L1249">1249</a> <b><i>/* called from ip_ra_control(), before an RCU grace period,</i></b>
<a name="L1250" href="source/net/ipv4/ipmr.c#L1250">1250</a> <b><i> * we dont need to call synchronize_rcu() here</i></b>
<a name="L1251" href="source/net/ipv4/ipmr.c#L1251">1251</a> <b><i> */</i></b>
<a name="L1252" href="source/net/ipv4/ipmr.c#L1252">1252</a> static void <a href="ident?i=mrtsock_destruct">mrtsock_destruct</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1253" href="source/net/ipv4/ipmr.c#L1253">1253</a> {
<a name="L1254" href="source/net/ipv4/ipmr.c#L1254">1254</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1255" href="source/net/ipv4/ipmr.c#L1255">1255</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1256" href="source/net/ipv4/ipmr.c#L1256">1256</a> 
<a name="L1257" href="source/net/ipv4/ipmr.c#L1257">1257</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1258" href="source/net/ipv4/ipmr.c#L1258">1258</a>         <a href="ident?i=ipmr_for_each_table">ipmr_for_each_table</a>(mrt, <a href="ident?i=net">net</a>) {
<a name="L1259" href="source/net/ipv4/ipmr.c#L1259">1259</a>                 if (sk == <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(mrt-&gt;mroute_sk)) {
<a name="L1260" href="source/net/ipv4/ipmr.c#L1260">1260</a>                         <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, MC_FORWARDING)--;
<a name="L1261" href="source/net/ipv4/ipmr.c#L1261">1261</a>                         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_MC_FORWARDING,
<a name="L1262" href="source/net/ipv4/ipmr.c#L1262">1262</a>                                                     <a href="ident?i=NETCONFA_IFINDEX_ALL">NETCONFA_IFINDEX_ALL</a>,
<a name="L1263" href="source/net/ipv4/ipmr.c#L1263">1263</a>                                                     <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all);
<a name="L1264" href="source/net/ipv4/ipmr.c#L1264">1264</a>                         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(mrt-&gt;mroute_sk, <a href="ident?i=NULL">NULL</a>);
<a name="L1265" href="source/net/ipv4/ipmr.c#L1265">1265</a>                         <a href="ident?i=mroute_clean_tables">mroute_clean_tables</a>(mrt);
<a name="L1266" href="source/net/ipv4/ipmr.c#L1266">1266</a>                 }
<a name="L1267" href="source/net/ipv4/ipmr.c#L1267">1267</a>         }
<a name="L1268" href="source/net/ipv4/ipmr.c#L1268">1268</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1269" href="source/net/ipv4/ipmr.c#L1269">1269</a> }
<a name="L1270" href="source/net/ipv4/ipmr.c#L1270">1270</a> 
<a name="L1271" href="source/net/ipv4/ipmr.c#L1271">1271</a> <b><i>/*</i></b>
<a name="L1272" href="source/net/ipv4/ipmr.c#L1272">1272</a> <b><i> *      Socket options and virtual interface manipulation. The whole</i></b>
<a name="L1273" href="source/net/ipv4/ipmr.c#L1273">1273</a> <b><i> *      virtual interface system is a complete heap, but unfortunately</i></b>
<a name="L1274" href="source/net/ipv4/ipmr.c#L1274">1274</a> <b><i> *      that's how BSD mrouted happens to think. Maybe one day with a proper</i></b>
<a name="L1275" href="source/net/ipv4/ipmr.c#L1275">1275</a> <b><i> *      MOSPF/PIM router set up we can clean this up.</i></b>
<a name="L1276" href="source/net/ipv4/ipmr.c#L1276">1276</a> <b><i> */</i></b>
<a name="L1277" href="source/net/ipv4/ipmr.c#L1277">1277</a> 
<a name="L1278" href="source/net/ipv4/ipmr.c#L1278">1278</a> int <a href="ident?i=ip_mroute_setsockopt">ip_mroute_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int optname, char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L1279" href="source/net/ipv4/ipmr.c#L1279">1279</a> {
<a name="L1280" href="source/net/ipv4/ipmr.c#L1280">1280</a>         int <a href="ident?i=ret">ret</a>, <a href="ident?i=parent">parent</a> = 0;
<a name="L1281" href="source/net/ipv4/ipmr.c#L1281">1281</a>         struct <a href="ident?i=vifctl">vifctl</a> <a href="ident?i=vif">vif</a>;
<a name="L1282" href="source/net/ipv4/ipmr.c#L1282">1282</a>         struct <a href="ident?i=mfcctl">mfcctl</a> mfc;
<a name="L1283" href="source/net/ipv4/ipmr.c#L1283">1283</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1284" href="source/net/ipv4/ipmr.c#L1284">1284</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1285" href="source/net/ipv4/ipmr.c#L1285">1285</a> 
<a name="L1286" href="source/net/ipv4/ipmr.c#L1286">1286</a>         if (sk-&gt;sk_type != SOCK_RAW ||
<a name="L1287" href="source/net/ipv4/ipmr.c#L1287">1287</a>             <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> != <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>)
<a name="L1288" href="source/net/ipv4/ipmr.c#L1288">1288</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L1289" href="source/net/ipv4/ipmr.c#L1289">1289</a> 
<a name="L1290" href="source/net/ipv4/ipmr.c#L1290">1290</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;ipmr_table ? : RT_TABLE_DEFAULT);
<a name="L1291" href="source/net/ipv4/ipmr.c#L1291">1291</a>         if (!mrt)
<a name="L1292" href="source/net/ipv4/ipmr.c#L1292">1292</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1293" href="source/net/ipv4/ipmr.c#L1293">1293</a> 
<a name="L1294" href="source/net/ipv4/ipmr.c#L1294">1294</a>         if (optname != <a href="ident?i=MRT_INIT">MRT_INIT</a>) {
<a name="L1295" href="source/net/ipv4/ipmr.c#L1295">1295</a>                 if (sk != <a href="ident?i=rcu_access_pointer">rcu_access_pointer</a>(mrt-&gt;mroute_sk) &amp;&amp;
<a name="L1296" href="source/net/ipv4/ipmr.c#L1296">1296</a>                     !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1297" href="source/net/ipv4/ipmr.c#L1297">1297</a>                         return -<a href="ident?i=EACCES">EACCES</a>;
<a name="L1298" href="source/net/ipv4/ipmr.c#L1298">1298</a>         }
<a name="L1299" href="source/net/ipv4/ipmr.c#L1299">1299</a> 
<a name="L1300" href="source/net/ipv4/ipmr.c#L1300">1300</a>         switch (optname) {
<a name="L1301" href="source/net/ipv4/ipmr.c#L1301">1301</a>         case <a href="ident?i=MRT_INIT">MRT_INIT</a>:
<a name="L1302" href="source/net/ipv4/ipmr.c#L1302">1302</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(int))
<a name="L1303" href="source/net/ipv4/ipmr.c#L1303">1303</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1304" href="source/net/ipv4/ipmr.c#L1304">1304</a> 
<a name="L1305" href="source/net/ipv4/ipmr.c#L1305">1305</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1306" href="source/net/ipv4/ipmr.c#L1306">1306</a>                 if (<a href="ident?i=rtnl_dereference">rtnl_dereference</a>(mrt-&gt;mroute_sk)) {
<a name="L1307" href="source/net/ipv4/ipmr.c#L1307">1307</a>                         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1308" href="source/net/ipv4/ipmr.c#L1308">1308</a>                         return -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L1309" href="source/net/ipv4/ipmr.c#L1309">1309</a>                 }
<a name="L1310" href="source/net/ipv4/ipmr.c#L1310">1310</a> 
<a name="L1311" href="source/net/ipv4/ipmr.c#L1311">1311</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_ra_control">ip_ra_control</a>(sk, 1, <a href="ident?i=mrtsock_destruct">mrtsock_destruct</a>);
<a name="L1312" href="source/net/ipv4/ipmr.c#L1312">1312</a>                 if (<a href="ident?i=ret">ret</a> == 0) {
<a name="L1313" href="source/net/ipv4/ipmr.c#L1313">1313</a>                         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(mrt-&gt;mroute_sk, sk);
<a name="L1314" href="source/net/ipv4/ipmr.c#L1314">1314</a>                         <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, MC_FORWARDING)++;
<a name="L1315" href="source/net/ipv4/ipmr.c#L1315">1315</a>                         <a href="ident?i=inet_netconf_notify_devconf">inet_netconf_notify_devconf</a>(<a href="ident?i=net">net</a>, NETCONFA_MC_FORWARDING,
<a name="L1316" href="source/net/ipv4/ipmr.c#L1316">1316</a>                                                     <a href="ident?i=NETCONFA_IFINDEX_ALL">NETCONFA_IFINDEX_ALL</a>,
<a name="L1317" href="source/net/ipv4/ipmr.c#L1317">1317</a>                                                     <a href="ident?i=net">net</a>-&gt;ipv4.devconf_all);
<a name="L1318" href="source/net/ipv4/ipmr.c#L1318">1318</a>                 }
<a name="L1319" href="source/net/ipv4/ipmr.c#L1319">1319</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1320" href="source/net/ipv4/ipmr.c#L1320">1320</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1321" href="source/net/ipv4/ipmr.c#L1321">1321</a>         case <a href="ident?i=MRT_DONE">MRT_DONE</a>:
<a name="L1322" href="source/net/ipv4/ipmr.c#L1322">1322</a>                 if (sk != <a href="ident?i=rcu_access_pointer">rcu_access_pointer</a>(mrt-&gt;mroute_sk))
<a name="L1323" href="source/net/ipv4/ipmr.c#L1323">1323</a>                         return -<a href="ident?i=EACCES">EACCES</a>;
<a name="L1324" href="source/net/ipv4/ipmr.c#L1324">1324</a>                 return <a href="ident?i=ip_ra_control">ip_ra_control</a>(sk, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L1325" href="source/net/ipv4/ipmr.c#L1325">1325</a>         case <a href="ident?i=MRT_ADD_VIF">MRT_ADD_VIF</a>:
<a name="L1326" href="source/net/ipv4/ipmr.c#L1326">1326</a>         case <a href="ident?i=MRT_DEL_VIF">MRT_DEL_VIF</a>:
<a name="L1327" href="source/net/ipv4/ipmr.c#L1327">1327</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(<a href="ident?i=vif">vif</a>))
<a name="L1328" href="source/net/ipv4/ipmr.c#L1328">1328</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1329" href="source/net/ipv4/ipmr.c#L1329">1329</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=vif">vif</a>, optval, sizeof(<a href="ident?i=vif">vif</a>)))
<a name="L1330" href="source/net/ipv4/ipmr.c#L1330">1330</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1331" href="source/net/ipv4/ipmr.c#L1331">1331</a>                 if (<a href="ident?i=vif">vif</a>.vifc_vifi &gt;= <a href="ident?i=MAXVIFS">MAXVIFS</a>)
<a name="L1332" href="source/net/ipv4/ipmr.c#L1332">1332</a>                         return -<a href="ident?i=ENFILE">ENFILE</a>;
<a name="L1333" href="source/net/ipv4/ipmr.c#L1333">1333</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1334" href="source/net/ipv4/ipmr.c#L1334">1334</a>                 if (optname == <a href="ident?i=MRT_ADD_VIF">MRT_ADD_VIF</a>) {
<a name="L1335" href="source/net/ipv4/ipmr.c#L1335">1335</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=vif_add">vif_add</a>(<a href="ident?i=net">net</a>, mrt, &amp;<a href="ident?i=vif">vif</a>,
<a name="L1336" href="source/net/ipv4/ipmr.c#L1336">1336</a>                                       sk == <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(mrt-&gt;mroute_sk));
<a name="L1337" href="source/net/ipv4/ipmr.c#L1337">1337</a>                 } else {
<a name="L1338" href="source/net/ipv4/ipmr.c#L1338">1338</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=vif_delete">vif_delete</a>(mrt, <a href="ident?i=vif">vif</a>.vifc_vifi, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L1339" href="source/net/ipv4/ipmr.c#L1339">1339</a>                 }
<a name="L1340" href="source/net/ipv4/ipmr.c#L1340">1340</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1341" href="source/net/ipv4/ipmr.c#L1341">1341</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1342" href="source/net/ipv4/ipmr.c#L1342">1342</a> 
<a name="L1343" href="source/net/ipv4/ipmr.c#L1343">1343</a>                 <b><i>/*</i></b>
<a name="L1344" href="source/net/ipv4/ipmr.c#L1344">1344</a> <b><i>                 *      Manipulate the forwarding caches. These live</i></b>
<a name="L1345" href="source/net/ipv4/ipmr.c#L1345">1345</a> <b><i>                 *      in a sort of kernel/user symbiosis.</i></b>
<a name="L1346" href="source/net/ipv4/ipmr.c#L1346">1346</a> <b><i>                 */</i></b>
<a name="L1347" href="source/net/ipv4/ipmr.c#L1347">1347</a>         case <a href="ident?i=MRT_ADD_MFC">MRT_ADD_MFC</a>:
<a name="L1348" href="source/net/ipv4/ipmr.c#L1348">1348</a>         case <a href="ident?i=MRT_DEL_MFC">MRT_DEL_MFC</a>:
<a name="L1349" href="source/net/ipv4/ipmr.c#L1349">1349</a>                 <a href="ident?i=parent">parent</a> = -1;
<a name="L1350" href="source/net/ipv4/ipmr.c#L1350">1350</a>         case <a href="ident?i=MRT_ADD_MFC_PROXY">MRT_ADD_MFC_PROXY</a>:
<a name="L1351" href="source/net/ipv4/ipmr.c#L1351">1351</a>         case <a href="ident?i=MRT_DEL_MFC_PROXY">MRT_DEL_MFC_PROXY</a>:
<a name="L1352" href="source/net/ipv4/ipmr.c#L1352">1352</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(mfc))
<a name="L1353" href="source/net/ipv4/ipmr.c#L1353">1353</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1354" href="source/net/ipv4/ipmr.c#L1354">1354</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mfc, optval, sizeof(mfc)))
<a name="L1355" href="source/net/ipv4/ipmr.c#L1355">1355</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1356" href="source/net/ipv4/ipmr.c#L1356">1356</a>                 if (<a href="ident?i=parent">parent</a> == 0)
<a name="L1357" href="source/net/ipv4/ipmr.c#L1357">1357</a>                         <a href="ident?i=parent">parent</a> = mfc.mfcc_parent;
<a name="L1358" href="source/net/ipv4/ipmr.c#L1358">1358</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1359" href="source/net/ipv4/ipmr.c#L1359">1359</a>                 if (optname == <a href="ident?i=MRT_DEL_MFC">MRT_DEL_MFC</a> || optname == <a href="ident?i=MRT_DEL_MFC_PROXY">MRT_DEL_MFC_PROXY</a>)
<a name="L1360" href="source/net/ipv4/ipmr.c#L1360">1360</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=ipmr_mfc_delete">ipmr_mfc_delete</a>(mrt, &amp;mfc, <a href="ident?i=parent">parent</a>);
<a name="L1361" href="source/net/ipv4/ipmr.c#L1361">1361</a>                 else
<a name="L1362" href="source/net/ipv4/ipmr.c#L1362">1362</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=ipmr_mfc_add">ipmr_mfc_add</a>(<a href="ident?i=net">net</a>, mrt, &amp;mfc,
<a name="L1363" href="source/net/ipv4/ipmr.c#L1363">1363</a>                                            sk == <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(mrt-&gt;mroute_sk),
<a name="L1364" href="source/net/ipv4/ipmr.c#L1364">1364</a>                                            <a href="ident?i=parent">parent</a>);
<a name="L1365" href="source/net/ipv4/ipmr.c#L1365">1365</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1366" href="source/net/ipv4/ipmr.c#L1366">1366</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1367" href="source/net/ipv4/ipmr.c#L1367">1367</a>                 <b><i>/*</i></b>
<a name="L1368" href="source/net/ipv4/ipmr.c#L1368">1368</a> <b><i>                 *      Control PIM assert.</i></b>
<a name="L1369" href="source/net/ipv4/ipmr.c#L1369">1369</a> <b><i>                 */</i></b>
<a name="L1370" href="source/net/ipv4/ipmr.c#L1370">1370</a>         case <a href="ident?i=MRT_ASSERT">MRT_ASSERT</a>:
<a name="L1371" href="source/net/ipv4/ipmr.c#L1371">1371</a>         {
<a name="L1372" href="source/net/ipv4/ipmr.c#L1372">1372</a>                 int <a href="ident?i=v">v</a>;
<a name="L1373" href="source/net/ipv4/ipmr.c#L1373">1373</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(<a href="ident?i=v">v</a>))
<a name="L1374" href="source/net/ipv4/ipmr.c#L1374">1374</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1375" href="source/net/ipv4/ipmr.c#L1375">1375</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=v">v</a>, (int <a href="ident?i=__user">__user</a> *)optval))
<a name="L1376" href="source/net/ipv4/ipmr.c#L1376">1376</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1377" href="source/net/ipv4/ipmr.c#L1377">1377</a>                 mrt-&gt;mroute_do_assert = <a href="ident?i=v">v</a>;
<a name="L1378" href="source/net/ipv4/ipmr.c#L1378">1378</a>                 return 0;
<a name="L1379" href="source/net/ipv4/ipmr.c#L1379">1379</a>         }
<a name="L1380" href="source/net/ipv4/ipmr.c#L1380">1380</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L1381" href="source/net/ipv4/ipmr.c#L1381">1381</a>         case <a href="ident?i=MRT_PIM">MRT_PIM</a>:
<a name="L1382" href="source/net/ipv4/ipmr.c#L1382">1382</a>         {
<a name="L1383" href="source/net/ipv4/ipmr.c#L1383">1383</a>                 int <a href="ident?i=v">v</a>;
<a name="L1384" href="source/net/ipv4/ipmr.c#L1384">1384</a> 
<a name="L1385" href="source/net/ipv4/ipmr.c#L1385">1385</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(<a href="ident?i=v">v</a>))
<a name="L1386" href="source/net/ipv4/ipmr.c#L1386">1386</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1387" href="source/net/ipv4/ipmr.c#L1387">1387</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=v">v</a>, (int <a href="ident?i=__user">__user</a> *)optval))
<a name="L1388" href="source/net/ipv4/ipmr.c#L1388">1388</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1389" href="source/net/ipv4/ipmr.c#L1389">1389</a>                 <a href="ident?i=v">v</a> = !!<a href="ident?i=v">v</a>;
<a name="L1390" href="source/net/ipv4/ipmr.c#L1390">1390</a> 
<a name="L1391" href="source/net/ipv4/ipmr.c#L1391">1391</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1392" href="source/net/ipv4/ipmr.c#L1392">1392</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L1393" href="source/net/ipv4/ipmr.c#L1393">1393</a>                 if (<a href="ident?i=v">v</a> != mrt-&gt;mroute_do_pim) {
<a name="L1394" href="source/net/ipv4/ipmr.c#L1394">1394</a>                         mrt-&gt;mroute_do_pim = <a href="ident?i=v">v</a>;
<a name="L1395" href="source/net/ipv4/ipmr.c#L1395">1395</a>                         mrt-&gt;mroute_do_assert = <a href="ident?i=v">v</a>;
<a name="L1396" href="source/net/ipv4/ipmr.c#L1396">1396</a>                 }
<a name="L1397" href="source/net/ipv4/ipmr.c#L1397">1397</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1398" href="source/net/ipv4/ipmr.c#L1398">1398</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1399" href="source/net/ipv4/ipmr.c#L1399">1399</a>         }
<a name="L1400" href="source/net/ipv4/ipmr.c#L1400">1400</a> #endif
<a name="L1401" href="source/net/ipv4/ipmr.c#L1401">1401</a> #ifdef CONFIG_IP_MROUTE_MULTIPLE_TABLES
<a name="L1402" href="source/net/ipv4/ipmr.c#L1402">1402</a>         case <a href="ident?i=MRT_TABLE">MRT_TABLE</a>:
<a name="L1403" href="source/net/ipv4/ipmr.c#L1403">1403</a>         {
<a name="L1404" href="source/net/ipv4/ipmr.c#L1404">1404</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=v">v</a>;
<a name="L1405" href="source/net/ipv4/ipmr.c#L1405">1405</a> 
<a name="L1406" href="source/net/ipv4/ipmr.c#L1406">1406</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(<a href="ident?i=u32">u32</a>))
<a name="L1407" href="source/net/ipv4/ipmr.c#L1407">1407</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1408" href="source/net/ipv4/ipmr.c#L1408">1408</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=v">v</a>, (<a href="ident?i=u32">u32</a> <a href="ident?i=__user">__user</a> *)optval))
<a name="L1409" href="source/net/ipv4/ipmr.c#L1409">1409</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1410" href="source/net/ipv4/ipmr.c#L1410">1410</a> 
<a name="L1411" href="source/net/ipv4/ipmr.c#L1411">1411</a>                 <b><i>/* "pimreg%u" should not exceed 16 bytes (IFNAMSIZ) */</i></b>
<a name="L1412" href="source/net/ipv4/ipmr.c#L1412">1412</a>                 if (<a href="ident?i=v">v</a> != RT_TABLE_DEFAULT &amp;&amp; <a href="ident?i=v">v</a> &gt;= 1000000000)
<a name="L1413" href="source/net/ipv4/ipmr.c#L1413">1413</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1414" href="source/net/ipv4/ipmr.c#L1414">1414</a> 
<a name="L1415" href="source/net/ipv4/ipmr.c#L1415">1415</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1416" href="source/net/ipv4/ipmr.c#L1416">1416</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L1417" href="source/net/ipv4/ipmr.c#L1417">1417</a>                 if (sk == <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(mrt-&gt;mroute_sk)) {
<a name="L1418" href="source/net/ipv4/ipmr.c#L1418">1418</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EBUSY">EBUSY</a>;
<a name="L1419" href="source/net/ipv4/ipmr.c#L1419">1419</a>                 } else {
<a name="L1420" href="source/net/ipv4/ipmr.c#L1420">1420</a>                         if (!<a href="ident?i=ipmr_new_table">ipmr_new_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=v">v</a>))
<a name="L1421" href="source/net/ipv4/ipmr.c#L1421">1421</a>                                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1422" href="source/net/ipv4/ipmr.c#L1422">1422</a>                         else
<a name="L1423" href="source/net/ipv4/ipmr.c#L1423">1423</a>                                 <a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;ipmr_table = <a href="ident?i=v">v</a>;
<a name="L1424" href="source/net/ipv4/ipmr.c#L1424">1424</a>                 }
<a name="L1425" href="source/net/ipv4/ipmr.c#L1425">1425</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1426" href="source/net/ipv4/ipmr.c#L1426">1426</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1427" href="source/net/ipv4/ipmr.c#L1427">1427</a>         }
<a name="L1428" href="source/net/ipv4/ipmr.c#L1428">1428</a> #endif
<a name="L1429" href="source/net/ipv4/ipmr.c#L1429">1429</a>         <b><i>/*</i></b>
<a name="L1430" href="source/net/ipv4/ipmr.c#L1430">1430</a> <b><i>         *      Spurious command, or MRT_VERSION which you cannot</i></b>
<a name="L1431" href="source/net/ipv4/ipmr.c#L1431">1431</a> <b><i>         *      set.</i></b>
<a name="L1432" href="source/net/ipv4/ipmr.c#L1432">1432</a> <b><i>         */</i></b>
<a name="L1433" href="source/net/ipv4/ipmr.c#L1433">1433</a>         default:
<a name="L1434" href="source/net/ipv4/ipmr.c#L1434">1434</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1435" href="source/net/ipv4/ipmr.c#L1435">1435</a>         }
<a name="L1436" href="source/net/ipv4/ipmr.c#L1436">1436</a> }
<a name="L1437" href="source/net/ipv4/ipmr.c#L1437">1437</a> 
<a name="L1438" href="source/net/ipv4/ipmr.c#L1438">1438</a> <b><i>/*</i></b>
<a name="L1439" href="source/net/ipv4/ipmr.c#L1439">1439</a> <b><i> *      Getsock opt support for the multicast routing system.</i></b>
<a name="L1440" href="source/net/ipv4/ipmr.c#L1440">1440</a> <b><i> */</i></b>
<a name="L1441" href="source/net/ipv4/ipmr.c#L1441">1441</a> 
<a name="L1442" href="source/net/ipv4/ipmr.c#L1442">1442</a> int <a href="ident?i=ip_mroute_getsockopt">ip_mroute_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int optname, char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L1443" href="source/net/ipv4/ipmr.c#L1443">1443</a> {
<a name="L1444" href="source/net/ipv4/ipmr.c#L1444">1444</a>         int olr;
<a name="L1445" href="source/net/ipv4/ipmr.c#L1445">1445</a>         int <a href="ident?i=val">val</a>;
<a name="L1446" href="source/net/ipv4/ipmr.c#L1446">1446</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1447" href="source/net/ipv4/ipmr.c#L1447">1447</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1448" href="source/net/ipv4/ipmr.c#L1448">1448</a> 
<a name="L1449" href="source/net/ipv4/ipmr.c#L1449">1449</a>         if (sk-&gt;sk_type != SOCK_RAW ||
<a name="L1450" href="source/net/ipv4/ipmr.c#L1450">1450</a>             <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> != <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>)
<a name="L1451" href="source/net/ipv4/ipmr.c#L1451">1451</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L1452" href="source/net/ipv4/ipmr.c#L1452">1452</a> 
<a name="L1453" href="source/net/ipv4/ipmr.c#L1453">1453</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;ipmr_table ? : RT_TABLE_DEFAULT);
<a name="L1454" href="source/net/ipv4/ipmr.c#L1454">1454</a>         if (!mrt)
<a name="L1455" href="source/net/ipv4/ipmr.c#L1455">1455</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1456" href="source/net/ipv4/ipmr.c#L1456">1456</a> 
<a name="L1457" href="source/net/ipv4/ipmr.c#L1457">1457</a>         if (optname != <a href="ident?i=MRT_VERSION">MRT_VERSION</a> &amp;&amp;
<a name="L1458" href="source/net/ipv4/ipmr.c#L1458">1458</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L1459" href="source/net/ipv4/ipmr.c#L1459">1459</a>            optname != <a href="ident?i=MRT_PIM">MRT_PIM</a> &amp;&amp;
<a name="L1460" href="source/net/ipv4/ipmr.c#L1460">1460</a> #endif
<a name="L1461" href="source/net/ipv4/ipmr.c#L1461">1461</a>            optname != <a href="ident?i=MRT_ASSERT">MRT_ASSERT</a>)
<a name="L1462" href="source/net/ipv4/ipmr.c#L1462">1462</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1463" href="source/net/ipv4/ipmr.c#L1463">1463</a> 
<a name="L1464" href="source/net/ipv4/ipmr.c#L1464">1464</a>         if (<a href="ident?i=get_user">get_user</a>(olr, <a href="ident?i=optlen">optlen</a>))
<a name="L1465" href="source/net/ipv4/ipmr.c#L1465">1465</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1466" href="source/net/ipv4/ipmr.c#L1466">1466</a> 
<a name="L1467" href="source/net/ipv4/ipmr.c#L1467">1467</a>         olr = <a href="ident?i=min_t">min_t</a>(unsigned int, olr, sizeof(int));
<a name="L1468" href="source/net/ipv4/ipmr.c#L1468">1468</a>         if (olr &lt; 0)
<a name="L1469" href="source/net/ipv4/ipmr.c#L1469">1469</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1470" href="source/net/ipv4/ipmr.c#L1470">1470</a> 
<a name="L1471" href="source/net/ipv4/ipmr.c#L1471">1471</a>         if (<a href="ident?i=put_user">put_user</a>(olr, <a href="ident?i=optlen">optlen</a>))
<a name="L1472" href="source/net/ipv4/ipmr.c#L1472">1472</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1473" href="source/net/ipv4/ipmr.c#L1473">1473</a>         if (optname == <a href="ident?i=MRT_VERSION">MRT_VERSION</a>)
<a name="L1474" href="source/net/ipv4/ipmr.c#L1474">1474</a>                 <a href="ident?i=val">val</a> = 0x0305;
<a name="L1475" href="source/net/ipv4/ipmr.c#L1475">1475</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L1476" href="source/net/ipv4/ipmr.c#L1476">1476</a>         else if (optname == <a href="ident?i=MRT_PIM">MRT_PIM</a>)
<a name="L1477" href="source/net/ipv4/ipmr.c#L1477">1477</a>                 <a href="ident?i=val">val</a> = mrt-&gt;mroute_do_pim;
<a name="L1478" href="source/net/ipv4/ipmr.c#L1478">1478</a> #endif
<a name="L1479" href="source/net/ipv4/ipmr.c#L1479">1479</a>         else
<a name="L1480" href="source/net/ipv4/ipmr.c#L1480">1480</a>                 <a href="ident?i=val">val</a> = mrt-&gt;mroute_do_assert;
<a name="L1481" href="source/net/ipv4/ipmr.c#L1481">1481</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=val">val</a>, olr))
<a name="L1482" href="source/net/ipv4/ipmr.c#L1482">1482</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1483" href="source/net/ipv4/ipmr.c#L1483">1483</a>         return 0;
<a name="L1484" href="source/net/ipv4/ipmr.c#L1484">1484</a> }
<a name="L1485" href="source/net/ipv4/ipmr.c#L1485">1485</a> 
<a name="L1486" href="source/net/ipv4/ipmr.c#L1486">1486</a> <b><i>/*</i></b>
<a name="L1487" href="source/net/ipv4/ipmr.c#L1487">1487</a> <b><i> *      The IP multicast ioctl support routines.</i></b>
<a name="L1488" href="source/net/ipv4/ipmr.c#L1488">1488</a> <b><i> */</i></b>
<a name="L1489" href="source/net/ipv4/ipmr.c#L1489">1489</a> 
<a name="L1490" href="source/net/ipv4/ipmr.c#L1490">1490</a> int <a href="ident?i=ipmr_ioctl">ipmr_ioctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=arg">arg</a>)
<a name="L1491" href="source/net/ipv4/ipmr.c#L1491">1491</a> {
<a name="L1492" href="source/net/ipv4/ipmr.c#L1492">1492</a>         struct <a href="ident?i=sioc_sg_req">sioc_sg_req</a> <a href="ident?i=sr">sr</a>;
<a name="L1493" href="source/net/ipv4/ipmr.c#L1493">1493</a>         struct <a href="ident?i=sioc_vif_req">sioc_vif_req</a> vr;
<a name="L1494" href="source/net/ipv4/ipmr.c#L1494">1494</a>         struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=vif">vif</a>;
<a name="L1495" href="source/net/ipv4/ipmr.c#L1495">1495</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>;
<a name="L1496" href="source/net/ipv4/ipmr.c#L1496">1496</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1497" href="source/net/ipv4/ipmr.c#L1497">1497</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1498" href="source/net/ipv4/ipmr.c#L1498">1498</a> 
<a name="L1499" href="source/net/ipv4/ipmr.c#L1499">1499</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;ipmr_table ? : RT_TABLE_DEFAULT);
<a name="L1500" href="source/net/ipv4/ipmr.c#L1500">1500</a>         if (!mrt)
<a name="L1501" href="source/net/ipv4/ipmr.c#L1501">1501</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1502" href="source/net/ipv4/ipmr.c#L1502">1502</a> 
<a name="L1503" href="source/net/ipv4/ipmr.c#L1503">1503</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1504" href="source/net/ipv4/ipmr.c#L1504">1504</a>         case <a href="ident?i=SIOCGETVIFCNT">SIOCGETVIFCNT</a>:
<a name="L1505" href="source/net/ipv4/ipmr.c#L1505">1505</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;vr, <a href="ident?i=arg">arg</a>, sizeof(vr)))
<a name="L1506" href="source/net/ipv4/ipmr.c#L1506">1506</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1507" href="source/net/ipv4/ipmr.c#L1507">1507</a>                 if (vr.vifi &gt;= mrt-&gt;maxvif)
<a name="L1508" href="source/net/ipv4/ipmr.c#L1508">1508</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1509" href="source/net/ipv4/ipmr.c#L1509">1509</a>                 <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L1510" href="source/net/ipv4/ipmr.c#L1510">1510</a>                 <a href="ident?i=vif">vif</a> = &amp;mrt-&gt;vif_table[vr.vifi];
<a name="L1511" href="source/net/ipv4/ipmr.c#L1511">1511</a>                 if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, vr.vifi)) {
<a name="L1512" href="source/net/ipv4/ipmr.c#L1512">1512</a>                         vr.icount = <a href="ident?i=vif">vif</a>-&gt;pkt_in;
<a name="L1513" href="source/net/ipv4/ipmr.c#L1513">1513</a>                         vr.ocount = <a href="ident?i=vif">vif</a>-&gt;pkt_out;
<a name="L1514" href="source/net/ipv4/ipmr.c#L1514">1514</a>                         vr.ibytes = <a href="ident?i=vif">vif</a>-&gt;bytes_in;
<a name="L1515" href="source/net/ipv4/ipmr.c#L1515">1515</a>                         vr.obytes = <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=bytes_out">bytes_out</a>;
<a name="L1516" href="source/net/ipv4/ipmr.c#L1516">1516</a>                         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L1517" href="source/net/ipv4/ipmr.c#L1517">1517</a> 
<a name="L1518" href="source/net/ipv4/ipmr.c#L1518">1518</a>                         if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=arg">arg</a>, &amp;vr, sizeof(vr)))
<a name="L1519" href="source/net/ipv4/ipmr.c#L1519">1519</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1520" href="source/net/ipv4/ipmr.c#L1520">1520</a>                         return 0;
<a name="L1521" href="source/net/ipv4/ipmr.c#L1521">1521</a>                 }
<a name="L1522" href="source/net/ipv4/ipmr.c#L1522">1522</a>                 <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L1523" href="source/net/ipv4/ipmr.c#L1523">1523</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1524" href="source/net/ipv4/ipmr.c#L1524">1524</a>         case <a href="ident?i=SIOCGETSGCNT">SIOCGETSGCNT</a>:
<a name="L1525" href="source/net/ipv4/ipmr.c#L1525">1525</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=sr">sr</a>, <a href="ident?i=arg">arg</a>, sizeof(<a href="ident?i=sr">sr</a>)))
<a name="L1526" href="source/net/ipv4/ipmr.c#L1526">1526</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1527" href="source/net/ipv4/ipmr.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/ipmr.c#L1528">1528</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1529" href="source/net/ipv4/ipmr.c#L1529">1529</a>                 <a href="ident?i=c">c</a> = <a href="ident?i=ipmr_cache_find">ipmr_cache_find</a>(mrt, <a href="ident?i=sr">sr</a>.<a href="ident?i=src">src</a>.s_addr, <a href="ident?i=sr">sr</a>.grp.s_addr);
<a name="L1530" href="source/net/ipv4/ipmr.c#L1530">1530</a>                 if (<a href="ident?i=c">c</a>) {
<a name="L1531" href="source/net/ipv4/ipmr.c#L1531">1531</a>                         <a href="ident?i=sr">sr</a>.pktcnt = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=pkt">pkt</a>;
<a name="L1532" href="source/net/ipv4/ipmr.c#L1532">1532</a>                         <a href="ident?i=sr">sr</a>.bytecnt = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=bytes">bytes</a>;
<a name="L1533" href="source/net/ipv4/ipmr.c#L1533">1533</a>                         <a href="ident?i=sr">sr</a>.wrong_if = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.wrong_if;
<a name="L1534" href="source/net/ipv4/ipmr.c#L1534">1534</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1535" href="source/net/ipv4/ipmr.c#L1535">1535</a> 
<a name="L1536" href="source/net/ipv4/ipmr.c#L1536">1536</a>                         if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=arg">arg</a>, &amp;<a href="ident?i=sr">sr</a>, sizeof(<a href="ident?i=sr">sr</a>)))
<a name="L1537" href="source/net/ipv4/ipmr.c#L1537">1537</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1538" href="source/net/ipv4/ipmr.c#L1538">1538</a>                         return 0;
<a name="L1539" href="source/net/ipv4/ipmr.c#L1539">1539</a>                 }
<a name="L1540" href="source/net/ipv4/ipmr.c#L1540">1540</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1541" href="source/net/ipv4/ipmr.c#L1541">1541</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1542" href="source/net/ipv4/ipmr.c#L1542">1542</a>         default:
<a name="L1543" href="source/net/ipv4/ipmr.c#L1543">1543</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L1544" href="source/net/ipv4/ipmr.c#L1544">1544</a>         }
<a name="L1545" href="source/net/ipv4/ipmr.c#L1545">1545</a> }
<a name="L1546" href="source/net/ipv4/ipmr.c#L1546">1546</a> 
<a name="L1547" href="source/net/ipv4/ipmr.c#L1547">1547</a> #ifdef CONFIG_COMPAT
<a name="L1548" href="source/net/ipv4/ipmr.c#L1548">1548</a> struct <a href="ident?i=compat_sioc_sg_req">compat_sioc_sg_req</a> {
<a name="L1549" href="source/net/ipv4/ipmr.c#L1549">1549</a>         struct <a href="ident?i=in_addr">in_addr</a> <a href="ident?i=src">src</a>;
<a name="L1550" href="source/net/ipv4/ipmr.c#L1550">1550</a>         struct <a href="ident?i=in_addr">in_addr</a> grp;
<a name="L1551" href="source/net/ipv4/ipmr.c#L1551">1551</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> pktcnt;
<a name="L1552" href="source/net/ipv4/ipmr.c#L1552">1552</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> bytecnt;
<a name="L1553" href="source/net/ipv4/ipmr.c#L1553">1553</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> wrong_if;
<a name="L1554" href="source/net/ipv4/ipmr.c#L1554">1554</a> };
<a name="L1555" href="source/net/ipv4/ipmr.c#L1555">1555</a> 
<a name="L1556" href="source/net/ipv4/ipmr.c#L1556">1556</a> struct <a href="ident?i=compat_sioc_vif_req">compat_sioc_vif_req</a> {
<a name="L1557" href="source/net/ipv4/ipmr.c#L1557">1557</a>         <a href="ident?i=vifi_t">vifi_t</a>  vifi;           <b><i>/* Which iface */</i></b>
<a name="L1558" href="source/net/ipv4/ipmr.c#L1558">1558</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> icount;
<a name="L1559" href="source/net/ipv4/ipmr.c#L1559">1559</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> ocount;
<a name="L1560" href="source/net/ipv4/ipmr.c#L1560">1560</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> ibytes;
<a name="L1561" href="source/net/ipv4/ipmr.c#L1561">1561</a>         <a href="ident?i=compat_ulong_t">compat_ulong_t</a> obytes;
<a name="L1562" href="source/net/ipv4/ipmr.c#L1562">1562</a> };
<a name="L1563" href="source/net/ipv4/ipmr.c#L1563">1563</a> 
<a name="L1564" href="source/net/ipv4/ipmr.c#L1564">1564</a> int <a href="ident?i=ipmr_compat_ioctl">ipmr_compat_ioctl</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=arg">arg</a>)
<a name="L1565" href="source/net/ipv4/ipmr.c#L1565">1565</a> {
<a name="L1566" href="source/net/ipv4/ipmr.c#L1566">1566</a>         struct <a href="ident?i=compat_sioc_sg_req">compat_sioc_sg_req</a> <a href="ident?i=sr">sr</a>;
<a name="L1567" href="source/net/ipv4/ipmr.c#L1567">1567</a>         struct <a href="ident?i=compat_sioc_vif_req">compat_sioc_vif_req</a> vr;
<a name="L1568" href="source/net/ipv4/ipmr.c#L1568">1568</a>         struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=vif">vif</a>;
<a name="L1569" href="source/net/ipv4/ipmr.c#L1569">1569</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>;
<a name="L1570" href="source/net/ipv4/ipmr.c#L1570">1570</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1571" href="source/net/ipv4/ipmr.c#L1571">1571</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1572" href="source/net/ipv4/ipmr.c#L1572">1572</a> 
<a name="L1573" href="source/net/ipv4/ipmr.c#L1573">1573</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;ipmr_table ? : RT_TABLE_DEFAULT);
<a name="L1574" href="source/net/ipv4/ipmr.c#L1574">1574</a>         if (!mrt)
<a name="L1575" href="source/net/ipv4/ipmr.c#L1575">1575</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1576" href="source/net/ipv4/ipmr.c#L1576">1576</a> 
<a name="L1577" href="source/net/ipv4/ipmr.c#L1577">1577</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1578" href="source/net/ipv4/ipmr.c#L1578">1578</a>         case <a href="ident?i=SIOCGETVIFCNT">SIOCGETVIFCNT</a>:
<a name="L1579" href="source/net/ipv4/ipmr.c#L1579">1579</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;vr, <a href="ident?i=arg">arg</a>, sizeof(vr)))
<a name="L1580" href="source/net/ipv4/ipmr.c#L1580">1580</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1581" href="source/net/ipv4/ipmr.c#L1581">1581</a>                 if (vr.vifi &gt;= mrt-&gt;maxvif)
<a name="L1582" href="source/net/ipv4/ipmr.c#L1582">1582</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1583" href="source/net/ipv4/ipmr.c#L1583">1583</a>                 <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L1584" href="source/net/ipv4/ipmr.c#L1584">1584</a>                 <a href="ident?i=vif">vif</a> = &amp;mrt-&gt;vif_table[vr.vifi];
<a name="L1585" href="source/net/ipv4/ipmr.c#L1585">1585</a>                 if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, vr.vifi)) {
<a name="L1586" href="source/net/ipv4/ipmr.c#L1586">1586</a>                         vr.icount = <a href="ident?i=vif">vif</a>-&gt;pkt_in;
<a name="L1587" href="source/net/ipv4/ipmr.c#L1587">1587</a>                         vr.ocount = <a href="ident?i=vif">vif</a>-&gt;pkt_out;
<a name="L1588" href="source/net/ipv4/ipmr.c#L1588">1588</a>                         vr.ibytes = <a href="ident?i=vif">vif</a>-&gt;bytes_in;
<a name="L1589" href="source/net/ipv4/ipmr.c#L1589">1589</a>                         vr.obytes = <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=bytes_out">bytes_out</a>;
<a name="L1590" href="source/net/ipv4/ipmr.c#L1590">1590</a>                         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L1591" href="source/net/ipv4/ipmr.c#L1591">1591</a> 
<a name="L1592" href="source/net/ipv4/ipmr.c#L1592">1592</a>                         if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=arg">arg</a>, &amp;vr, sizeof(vr)))
<a name="L1593" href="source/net/ipv4/ipmr.c#L1593">1593</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1594" href="source/net/ipv4/ipmr.c#L1594">1594</a>                         return 0;
<a name="L1595" href="source/net/ipv4/ipmr.c#L1595">1595</a>                 }
<a name="L1596" href="source/net/ipv4/ipmr.c#L1596">1596</a>                 <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L1597" href="source/net/ipv4/ipmr.c#L1597">1597</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1598" href="source/net/ipv4/ipmr.c#L1598">1598</a>         case <a href="ident?i=SIOCGETSGCNT">SIOCGETSGCNT</a>:
<a name="L1599" href="source/net/ipv4/ipmr.c#L1599">1599</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=sr">sr</a>, <a href="ident?i=arg">arg</a>, sizeof(<a href="ident?i=sr">sr</a>)))
<a name="L1600" href="source/net/ipv4/ipmr.c#L1600">1600</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1601" href="source/net/ipv4/ipmr.c#L1601">1601</a> 
<a name="L1602" href="source/net/ipv4/ipmr.c#L1602">1602</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1603" href="source/net/ipv4/ipmr.c#L1603">1603</a>                 <a href="ident?i=c">c</a> = <a href="ident?i=ipmr_cache_find">ipmr_cache_find</a>(mrt, <a href="ident?i=sr">sr</a>.<a href="ident?i=src">src</a>.s_addr, <a href="ident?i=sr">sr</a>.grp.s_addr);
<a name="L1604" href="source/net/ipv4/ipmr.c#L1604">1604</a>                 if (<a href="ident?i=c">c</a>) {
<a name="L1605" href="source/net/ipv4/ipmr.c#L1605">1605</a>                         <a href="ident?i=sr">sr</a>.pktcnt = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=pkt">pkt</a>;
<a name="L1606" href="source/net/ipv4/ipmr.c#L1606">1606</a>                         <a href="ident?i=sr">sr</a>.bytecnt = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=bytes">bytes</a>;
<a name="L1607" href="source/net/ipv4/ipmr.c#L1607">1607</a>                         <a href="ident?i=sr">sr</a>.wrong_if = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.wrong_if;
<a name="L1608" href="source/net/ipv4/ipmr.c#L1608">1608</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1609" href="source/net/ipv4/ipmr.c#L1609">1609</a> 
<a name="L1610" href="source/net/ipv4/ipmr.c#L1610">1610</a>                         if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=arg">arg</a>, &amp;<a href="ident?i=sr">sr</a>, sizeof(<a href="ident?i=sr">sr</a>)))
<a name="L1611" href="source/net/ipv4/ipmr.c#L1611">1611</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1612" href="source/net/ipv4/ipmr.c#L1612">1612</a>                         return 0;
<a name="L1613" href="source/net/ipv4/ipmr.c#L1613">1613</a>                 }
<a name="L1614" href="source/net/ipv4/ipmr.c#L1614">1614</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1615" href="source/net/ipv4/ipmr.c#L1615">1615</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1616" href="source/net/ipv4/ipmr.c#L1616">1616</a>         default:
<a name="L1617" href="source/net/ipv4/ipmr.c#L1617">1617</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L1618" href="source/net/ipv4/ipmr.c#L1618">1618</a>         }
<a name="L1619" href="source/net/ipv4/ipmr.c#L1619">1619</a> }
<a name="L1620" href="source/net/ipv4/ipmr.c#L1620">1620</a> #endif
<a name="L1621" href="source/net/ipv4/ipmr.c#L1621">1621</a> 
<a name="L1622" href="source/net/ipv4/ipmr.c#L1622">1622</a> 
<a name="L1623" href="source/net/ipv4/ipmr.c#L1623">1623</a> static int <a href="ident?i=ipmr_device_event">ipmr_device_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>, unsigned long <a href="ident?i=event">event</a>, void *<a href="ident?i=ptr">ptr</a>)
<a name="L1624" href="source/net/ipv4/ipmr.c#L1624">1624</a> {
<a name="L1625" href="source/net/ipv4/ipmr.c#L1625">1625</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=netdev_notifier_info_to_dev">netdev_notifier_info_to_dev</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L1626" href="source/net/ipv4/ipmr.c#L1626">1626</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1627" href="source/net/ipv4/ipmr.c#L1627">1627</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1628" href="source/net/ipv4/ipmr.c#L1628">1628</a>         struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=v">v</a>;
<a name="L1629" href="source/net/ipv4/ipmr.c#L1629">1629</a>         int ct;
<a name="L1630" href="source/net/ipv4/ipmr.c#L1630">1630</a> 
<a name="L1631" href="source/net/ipv4/ipmr.c#L1631">1631</a>         if (<a href="ident?i=event">event</a> != <a href="ident?i=NETDEV_UNREGISTER">NETDEV_UNREGISTER</a>)
<a name="L1632" href="source/net/ipv4/ipmr.c#L1632">1632</a>                 return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1633" href="source/net/ipv4/ipmr.c#L1633">1633</a> 
<a name="L1634" href="source/net/ipv4/ipmr.c#L1634">1634</a>         <a href="ident?i=ipmr_for_each_table">ipmr_for_each_table</a>(mrt, <a href="ident?i=net">net</a>) {
<a name="L1635" href="source/net/ipv4/ipmr.c#L1635">1635</a>                 <a href="ident?i=v">v</a> = &amp;mrt-&gt;vif_table[0];
<a name="L1636" href="source/net/ipv4/ipmr.c#L1636">1636</a>                 for (ct = 0; ct &lt; mrt-&gt;maxvif; ct++, <a href="ident?i=v">v</a>++) {
<a name="L1637" href="source/net/ipv4/ipmr.c#L1637">1637</a>                         if (<a href="ident?i=v">v</a>-&gt;<a href="ident?i=dev">dev</a> == <a href="ident?i=dev">dev</a>)
<a name="L1638" href="source/net/ipv4/ipmr.c#L1638">1638</a>                                 <a href="ident?i=vif_delete">vif_delete</a>(mrt, ct, 1, <a href="ident?i=NULL">NULL</a>);
<a name="L1639" href="source/net/ipv4/ipmr.c#L1639">1639</a>                 }
<a name="L1640" href="source/net/ipv4/ipmr.c#L1640">1640</a>         }
<a name="L1641" href="source/net/ipv4/ipmr.c#L1641">1641</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1642" href="source/net/ipv4/ipmr.c#L1642">1642</a> }
<a name="L1643" href="source/net/ipv4/ipmr.c#L1643">1643</a> 
<a name="L1644" href="source/net/ipv4/ipmr.c#L1644">1644</a> 
<a name="L1645" href="source/net/ipv4/ipmr.c#L1645">1645</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=ip_mr_notifier">ip_mr_notifier</a> = {
<a name="L1646" href="source/net/ipv4/ipmr.c#L1646">1646</a>         .notifier_call = <a href="ident?i=ipmr_device_event">ipmr_device_event</a>,
<a name="L1647" href="source/net/ipv4/ipmr.c#L1647">1647</a> };
<a name="L1648" href="source/net/ipv4/ipmr.c#L1648">1648</a> 
<a name="L1649" href="source/net/ipv4/ipmr.c#L1649">1649</a> <b><i>/*</i></b>
<a name="L1650" href="source/net/ipv4/ipmr.c#L1650">1650</a> <b><i> *      Encapsulate a packet by attaching a valid IPIP header to it.</i></b>
<a name="L1651" href="source/net/ipv4/ipmr.c#L1651">1651</a> <b><i> *      This avoids tunnel drivers and other mess and gives us the speed so</i></b>
<a name="L1652" href="source/net/ipv4/ipmr.c#L1652">1652</a> <b><i> *      important for multicast video.</i></b>
<a name="L1653" href="source/net/ipv4/ipmr.c#L1653">1653</a> <b><i> */</i></b>
<a name="L1654" href="source/net/ipv4/ipmr.c#L1654">1654</a> 
<a name="L1655" href="source/net/ipv4/ipmr.c#L1655">1655</a> static void <a href="ident?i=ip_encap">ip_encap</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1656" href="source/net/ipv4/ipmr.c#L1656">1656</a>                      <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>)
<a name="L1657" href="source/net/ipv4/ipmr.c#L1657">1657</a> {
<a name="L1658" href="source/net/ipv4/ipmr.c#L1658">1658</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1659" href="source/net/ipv4/ipmr.c#L1659">1659</a>         const struct <a href="ident?i=iphdr">iphdr</a> *old_iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1660" href="source/net/ipv4/ipmr.c#L1660">1660</a> 
<a name="L1661" href="source/net/ipv4/ipmr.c#L1661">1661</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L1662" href="source/net/ipv4/ipmr.c#L1662">1662</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header;
<a name="L1663" href="source/net/ipv4/ipmr.c#L1663">1663</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1664" href="source/net/ipv4/ipmr.c#L1664">1664</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1665" href="source/net/ipv4/ipmr.c#L1665">1665</a> 
<a name="L1666" href="source/net/ipv4/ipmr.c#L1666">1666</a>         iph-&gt;<a href="ident?i=version">version</a>    =       4;
<a name="L1667" href="source/net/ipv4/ipmr.c#L1667">1667</a>         iph-&gt;tos        =       old_iph-&gt;tos;
<a name="L1668" href="source/net/ipv4/ipmr.c#L1668">1668</a>         iph-&gt;<a href="ident?i=ttl">ttl</a>        =       old_iph-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L1669" href="source/net/ipv4/ipmr.c#L1669">1669</a>         iph-&gt;frag_off   =       0;
<a name="L1670" href="source/net/ipv4/ipmr.c#L1670">1670</a>         iph-&gt;<a href="ident?i=daddr">daddr</a>      =       <a href="ident?i=daddr">daddr</a>;
<a name="L1671" href="source/net/ipv4/ipmr.c#L1671">1671</a>         iph-&gt;<a href="ident?i=saddr">saddr</a>      =       <a href="ident?i=saddr">saddr</a>;
<a name="L1672" href="source/net/ipv4/ipmr.c#L1672">1672</a>         iph-&gt;<a href="ident?i=protocol">protocol</a>   =       <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L1673" href="source/net/ipv4/ipmr.c#L1673">1673</a>         iph-&gt;ihl        =       5;
<a name="L1674" href="source/net/ipv4/ipmr.c#L1674">1674</a>         iph-&gt;tot_len    =       <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1675" href="source/net/ipv4/ipmr.c#L1675">1675</a>         <a href="ident?i=ip_select_ident">ip_select_ident</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1676" href="source/net/ipv4/ipmr.c#L1676">1676</a>         <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L1677" href="source/net/ipv4/ipmr.c#L1677">1677</a> 
<a name="L1678" href="source/net/ipv4/ipmr.c#L1678">1678</a>         <a href="ident?i=memset">memset</a>(&amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt), 0, sizeof(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt));
<a name="L1679" href="source/net/ipv4/ipmr.c#L1679">1679</a>         <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L1680" href="source/net/ipv4/ipmr.c#L1680">1680</a> }
<a name="L1681" href="source/net/ipv4/ipmr.c#L1681">1681</a> 
<a name="L1682" href="source/net/ipv4/ipmr.c#L1682">1682</a> static inline int <a href="ident?i=ipmr_forward_finish">ipmr_forward_finish</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1683" href="source/net/ipv4/ipmr.c#L1683">1683</a> {
<a name="L1684" href="source/net/ipv4/ipmr.c#L1684">1684</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
<a name="L1685" href="source/net/ipv4/ipmr.c#L1685">1685</a> 
<a name="L1686" href="source/net/ipv4/ipmr.c#L1686">1686</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUTFORWDATAGRAMS);
<a name="L1687" href="source/net/ipv4/ipmr.c#L1687">1687</a>         <a href="ident?i=IP_ADD_STATS_BH">IP_ADD_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUTOCTETS, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1688" href="source/net/ipv4/ipmr.c#L1688">1688</a> 
<a name="L1689" href="source/net/ipv4/ipmr.c#L1689">1689</a>         if (<a href="ident?i=unlikely">unlikely</a>(opt-&gt;<a href="ident?i=optlen">optlen</a>))
<a name="L1690" href="source/net/ipv4/ipmr.c#L1690">1690</a>                 <a href="ident?i=ip_forward_options">ip_forward_options</a>(<a href="ident?i=skb">skb</a>);
<a name="L1691" href="source/net/ipv4/ipmr.c#L1691">1691</a> 
<a name="L1692" href="source/net/ipv4/ipmr.c#L1692">1692</a>         return <a href="ident?i=dst_output_sk">dst_output_sk</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1693" href="source/net/ipv4/ipmr.c#L1693">1693</a> }
<a name="L1694" href="source/net/ipv4/ipmr.c#L1694">1694</a> 
<a name="L1695" href="source/net/ipv4/ipmr.c#L1695">1695</a> <b><i>/*</i></b>
<a name="L1696" href="source/net/ipv4/ipmr.c#L1696">1696</a> <b><i> *      Processing handlers for ipmr_forward</i></b>
<a name="L1697" href="source/net/ipv4/ipmr.c#L1697">1697</a> <b><i> */</i></b>
<a name="L1698" href="source/net/ipv4/ipmr.c#L1698">1698</a> 
<a name="L1699" href="source/net/ipv4/ipmr.c#L1699">1699</a> static void <a href="ident?i=ipmr_queue_xmit">ipmr_queue_xmit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L1700" href="source/net/ipv4/ipmr.c#L1700">1700</a>                             struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, int vifi)
<a name="L1701" href="source/net/ipv4/ipmr.c#L1701">1701</a> {
<a name="L1702" href="source/net/ipv4/ipmr.c#L1702">1702</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1703" href="source/net/ipv4/ipmr.c#L1703">1703</a>         struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=vif">vif</a> = &amp;mrt-&gt;vif_table[vifi];
<a name="L1704" href="source/net/ipv4/ipmr.c#L1704">1704</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L1705" href="source/net/ipv4/ipmr.c#L1705">1705</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1706" href="source/net/ipv4/ipmr.c#L1706">1706</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1707" href="source/net/ipv4/ipmr.c#L1707">1707</a>         int    encap = 0;
<a name="L1708" href="source/net/ipv4/ipmr.c#L1708">1708</a> 
<a name="L1709" href="source/net/ipv4/ipmr.c#L1709">1709</a>         if (!<a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a>)
<a name="L1710" href="source/net/ipv4/ipmr.c#L1710">1710</a>                 goto out_free;
<a name="L1711" href="source/net/ipv4/ipmr.c#L1711">1711</a> 
<a name="L1712" href="source/net/ipv4/ipmr.c#L1712">1712</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L1713" href="source/net/ipv4/ipmr.c#L1713">1713</a>         if (<a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=VIFF_REGISTER">VIFF_REGISTER</a>) {
<a name="L1714" href="source/net/ipv4/ipmr.c#L1714">1714</a>                 <a href="ident?i=vif">vif</a>-&gt;pkt_out++;
<a name="L1715" href="source/net/ipv4/ipmr.c#L1715">1715</a>                 <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=bytes_out">bytes_out</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1716" href="source/net/ipv4/ipmr.c#L1716">1716</a>                 <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.<a href="ident?i=tx_bytes">tx_bytes</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1717" href="source/net/ipv4/ipmr.c#L1717">1717</a>                 <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_packets++;
<a name="L1718" href="source/net/ipv4/ipmr.c#L1718">1718</a>                 <a href="ident?i=ipmr_cache_report">ipmr_cache_report</a>(mrt, <a href="ident?i=skb">skb</a>, vifi, <a href="ident?i=IGMPMSG_WHOLEPKT">IGMPMSG_WHOLEPKT</a>);
<a name="L1719" href="source/net/ipv4/ipmr.c#L1719">1719</a>                 goto out_free;
<a name="L1720" href="source/net/ipv4/ipmr.c#L1720">1720</a>         }
<a name="L1721" href="source/net/ipv4/ipmr.c#L1721">1721</a> #endif
<a name="L1722" href="source/net/ipv4/ipmr.c#L1722">1722</a> 
<a name="L1723" href="source/net/ipv4/ipmr.c#L1723">1723</a>         if (<a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=VIFF_TUNNEL">VIFF_TUNNEL</a>) {
<a name="L1724" href="source/net/ipv4/ipmr.c#L1724">1724</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=net">net</a>, &amp;fl4, <a href="ident?i=NULL">NULL</a>,
<a name="L1725" href="source/net/ipv4/ipmr.c#L1725">1725</a>                                            <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=remote">remote</a>, <a href="ident?i=vif">vif</a>-&gt;local,
<a name="L1726" href="source/net/ipv4/ipmr.c#L1726">1726</a>                                            0, 0,
<a name="L1727" href="source/net/ipv4/ipmr.c#L1727">1727</a>                                            <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>,
<a name="L1728" href="source/net/ipv4/ipmr.c#L1728">1728</a>                                            <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos), <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=link">link</a>);
<a name="L1729" href="source/net/ipv4/ipmr.c#L1729">1729</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1730" href="source/net/ipv4/ipmr.c#L1730">1730</a>                         goto out_free;
<a name="L1731" href="source/net/ipv4/ipmr.c#L1731">1731</a>                 encap = sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L1732" href="source/net/ipv4/ipmr.c#L1732">1732</a>         } else {
<a name="L1733" href="source/net/ipv4/ipmr.c#L1733">1733</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=net">net</a>, &amp;fl4, <a href="ident?i=NULL">NULL</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, 0,
<a name="L1734" href="source/net/ipv4/ipmr.c#L1734">1734</a>                                            0, 0,
<a name="L1735" href="source/net/ipv4/ipmr.c#L1735">1735</a>                                            <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>,
<a name="L1736" href="source/net/ipv4/ipmr.c#L1736">1736</a>                                            <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos), <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=link">link</a>);
<a name="L1737" href="source/net/ipv4/ipmr.c#L1737">1737</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1738" href="source/net/ipv4/ipmr.c#L1738">1738</a>                         goto out_free;
<a name="L1739" href="source/net/ipv4/ipmr.c#L1739">1739</a>         }
<a name="L1740" href="source/net/ipv4/ipmr.c#L1740">1740</a> 
<a name="L1741" href="source/net/ipv4/ipmr.c#L1741">1741</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L1742" href="source/net/ipv4/ipmr.c#L1742">1742</a> 
<a name="L1743" href="source/net/ipv4/ipmr.c#L1743">1743</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>+encap &gt; <a href="ident?i=dst_mtu">dst_mtu</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>) &amp;&amp; (<a href="ident?i=ntohs">ntohs</a>(iph-&gt;frag_off) &amp; <a href="ident?i=IP_DF">IP_DF</a>)) {
<a name="L1744" href="source/net/ipv4/ipmr.c#L1744">1744</a>                 <b><i>/* Do not fragment multicasts. Alas, IPv4 does not</i></b>
<a name="L1745" href="source/net/ipv4/ipmr.c#L1745">1745</a> <b><i>                 * allow to send ICMP, so that packets will disappear</i></b>
<a name="L1746" href="source/net/ipv4/ipmr.c#L1746">1746</a> <b><i>                 * to blackhole.</i></b>
<a name="L1747" href="source/net/ipv4/ipmr.c#L1747">1747</a> <b><i>                 */</i></b>
<a name="L1748" href="source/net/ipv4/ipmr.c#L1748">1748</a> 
<a name="L1749" href="source/net/ipv4/ipmr.c#L1749">1749</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGFAILS);
<a name="L1750" href="source/net/ipv4/ipmr.c#L1750">1750</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1751" href="source/net/ipv4/ipmr.c#L1751">1751</a>                 goto out_free;
<a name="L1752" href="source/net/ipv4/ipmr.c#L1752">1752</a>         }
<a name="L1753" href="source/net/ipv4/ipmr.c#L1753">1753</a> 
<a name="L1754" href="source/net/ipv4/ipmr.c#L1754">1754</a>         encap += <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>) + <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=header_len">header_len</a>;
<a name="L1755" href="source/net/ipv4/ipmr.c#L1755">1755</a> 
<a name="L1756" href="source/net/ipv4/ipmr.c#L1756">1756</a>         if (<a href="ident?i=skb_cow">skb_cow</a>(<a href="ident?i=skb">skb</a>, encap)) {
<a name="L1757" href="source/net/ipv4/ipmr.c#L1757">1757</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1758" href="source/net/ipv4/ipmr.c#L1758">1758</a>                 goto out_free;
<a name="L1759" href="source/net/ipv4/ipmr.c#L1759">1759</a>         }
<a name="L1760" href="source/net/ipv4/ipmr.c#L1760">1760</a> 
<a name="L1761" href="source/net/ipv4/ipmr.c#L1761">1761</a>         <a href="ident?i=vif">vif</a>-&gt;pkt_out++;
<a name="L1762" href="source/net/ipv4/ipmr.c#L1762">1762</a>         <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=bytes_out">bytes_out</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1763" href="source/net/ipv4/ipmr.c#L1763">1763</a> 
<a name="L1764" href="source/net/ipv4/ipmr.c#L1764">1764</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L1765" href="source/net/ipv4/ipmr.c#L1765">1765</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1766" href="source/net/ipv4/ipmr.c#L1766">1766</a>         <a href="ident?i=ip_decrease_ttl">ip_decrease_ttl</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>));
<a name="L1767" href="source/net/ipv4/ipmr.c#L1767">1767</a> 
<a name="L1768" href="source/net/ipv4/ipmr.c#L1768">1768</a>         <b><i>/* FIXME: forward and output firewalls used to be called here.</i></b>
<a name="L1769" href="source/net/ipv4/ipmr.c#L1769">1769</a> <b><i>         * What do we do with netfilter? -- RR</i></b>
<a name="L1770" href="source/net/ipv4/ipmr.c#L1770">1770</a> <b><i>         */</i></b>
<a name="L1771" href="source/net/ipv4/ipmr.c#L1771">1771</a>         if (<a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=VIFF_TUNNEL">VIFF_TUNNEL</a>) {
<a name="L1772" href="source/net/ipv4/ipmr.c#L1772">1772</a>                 <a href="ident?i=ip_encap">ip_encap</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=vif">vif</a>-&gt;local, <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=remote">remote</a>);
<a name="L1773" href="source/net/ipv4/ipmr.c#L1773">1773</a>                 <b><i>/* FIXME: extra output firewall step used to be here. --RR */</i></b>
<a name="L1774" href="source/net/ipv4/ipmr.c#L1774">1774</a>                 <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_packets++;
<a name="L1775" href="source/net/ipv4/ipmr.c#L1775">1775</a>                 <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.<a href="ident?i=tx_bytes">tx_bytes</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1776" href="source/net/ipv4/ipmr.c#L1776">1776</a>         }
<a name="L1777" href="source/net/ipv4/ipmr.c#L1777">1777</a> 
<a name="L1778" href="source/net/ipv4/ipmr.c#L1778">1778</a>         <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_FORWARDED">IPSKB_FORWARDED</a>;
<a name="L1779" href="source/net/ipv4/ipmr.c#L1779">1779</a> 
<a name="L1780" href="source/net/ipv4/ipmr.c#L1780">1780</a>         <b><i>/*</i></b>
<a name="L1781" href="source/net/ipv4/ipmr.c#L1781">1781</a> <b><i>         * RFC1584 teaches, that DVMRP/PIM router must deliver packets locally</i></b>
<a name="L1782" href="source/net/ipv4/ipmr.c#L1782">1782</a> <b><i>         * not only before forwarding, but after forwarding on all output</i></b>
<a name="L1783" href="source/net/ipv4/ipmr.c#L1783">1783</a> <b><i>         * interfaces. It is clear, if mrouter runs a multicasting</i></b>
<a name="L1784" href="source/net/ipv4/ipmr.c#L1784">1784</a> <b><i>         * program, it should receive packets not depending to what interface</i></b>
<a name="L1785" href="source/net/ipv4/ipmr.c#L1785">1785</a> <b><i>         * program is joined.</i></b>
<a name="L1786" href="source/net/ipv4/ipmr.c#L1786">1786</a> <b><i>         * If we will not make it, the program will have to join on all</i></b>
<a name="L1787" href="source/net/ipv4/ipmr.c#L1787">1787</a> <b><i>         * interfaces. On the other hand, multihoming host (or router, but</i></b>
<a name="L1788" href="source/net/ipv4/ipmr.c#L1788">1788</a> <b><i>         * not mrouter) cannot join to more than one interface - it will</i></b>
<a name="L1789" href="source/net/ipv4/ipmr.c#L1789">1789</a> <b><i>         * result in receiving multiple packets.</i></b>
<a name="L1790" href="source/net/ipv4/ipmr.c#L1790">1790</a> <b><i>         */</i></b>
<a name="L1791" href="source/net/ipv4/ipmr.c#L1791">1791</a>         <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_FORWARD, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
<a name="L1792" href="source/net/ipv4/ipmr.c#L1792">1792</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=dev">dev</a>,
<a name="L1793" href="source/net/ipv4/ipmr.c#L1793">1793</a>                 <a href="ident?i=ipmr_forward_finish">ipmr_forward_finish</a>);
<a name="L1794" href="source/net/ipv4/ipmr.c#L1794">1794</a>         return;
<a name="L1795" href="source/net/ipv4/ipmr.c#L1795">1795</a> 
<a name="L1796" href="source/net/ipv4/ipmr.c#L1796">1796</a> out_free:
<a name="L1797" href="source/net/ipv4/ipmr.c#L1797">1797</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1798" href="source/net/ipv4/ipmr.c#L1798">1798</a> }
<a name="L1799" href="source/net/ipv4/ipmr.c#L1799">1799</a> 
<a name="L1800" href="source/net/ipv4/ipmr.c#L1800">1800</a> static int <a href="ident?i=ipmr_find_vif">ipmr_find_vif</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1801" href="source/net/ipv4/ipmr.c#L1801">1801</a> {
<a name="L1802" href="source/net/ipv4/ipmr.c#L1802">1802</a>         int ct;
<a name="L1803" href="source/net/ipv4/ipmr.c#L1803">1803</a> 
<a name="L1804" href="source/net/ipv4/ipmr.c#L1804">1804</a>         for (ct = mrt-&gt;maxvif-1; ct &gt;= 0; ct--) {
<a name="L1805" href="source/net/ipv4/ipmr.c#L1805">1805</a>                 if (mrt-&gt;vif_table[ct].<a href="ident?i=dev">dev</a> == <a href="ident?i=dev">dev</a>)
<a name="L1806" href="source/net/ipv4/ipmr.c#L1806">1806</a>                         break;
<a name="L1807" href="source/net/ipv4/ipmr.c#L1807">1807</a>         }
<a name="L1808" href="source/net/ipv4/ipmr.c#L1808">1808</a>         return ct;
<a name="L1809" href="source/net/ipv4/ipmr.c#L1809">1809</a> }
<a name="L1810" href="source/net/ipv4/ipmr.c#L1810">1810</a> 
<a name="L1811" href="source/net/ipv4/ipmr.c#L1811">1811</a> <b><i>/* "local" means that we should preserve one skb (for local delivery) */</i></b>
<a name="L1812" href="source/net/ipv4/ipmr.c#L1812">1812</a> 
<a name="L1813" href="source/net/ipv4/ipmr.c#L1813">1813</a> static void <a href="ident?i=ip_mr_forward">ip_mr_forward</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=mr_table">mr_table</a> *mrt,
<a name="L1814" href="source/net/ipv4/ipmr.c#L1814">1814</a>                           struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=cache">cache</a>,
<a name="L1815" href="source/net/ipv4/ipmr.c#L1815">1815</a>                           int local)
<a name="L1816" href="source/net/ipv4/ipmr.c#L1816">1816</a> {
<a name="L1817" href="source/net/ipv4/ipmr.c#L1817">1817</a>         int <a href="ident?i=psend">psend</a> = -1;
<a name="L1818" href="source/net/ipv4/ipmr.c#L1818">1818</a>         int <a href="ident?i=vif">vif</a>, ct;
<a name="L1819" href="source/net/ipv4/ipmr.c#L1819">1819</a>         int true_vifi = <a href="ident?i=ipmr_find_vif">ipmr_find_vif</a>(mrt, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1820" href="source/net/ipv4/ipmr.c#L1820">1820</a> 
<a name="L1821" href="source/net/ipv4/ipmr.c#L1821">1821</a>         <a href="ident?i=vif">vif</a> = <a href="ident?i=cache">cache</a>-&gt;mfc_parent;
<a name="L1822" href="source/net/ipv4/ipmr.c#L1822">1822</a>         <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=pkt">pkt</a>++;
<a name="L1823" href="source/net/ipv4/ipmr.c#L1823">1823</a>         <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=bytes">bytes</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1824" href="source/net/ipv4/ipmr.c#L1824">1824</a> 
<a name="L1825" href="source/net/ipv4/ipmr.c#L1825">1825</a>         if (<a href="ident?i=cache">cache</a>-&gt;mfc_origin == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp; true_vifi &gt;= 0) {
<a name="L1826" href="source/net/ipv4/ipmr.c#L1826">1826</a>                 struct <a href="ident?i=mfc_cache">mfc_cache</a> *cache_proxy;
<a name="L1827" href="source/net/ipv4/ipmr.c#L1827">1827</a> 
<a name="L1828" href="source/net/ipv4/ipmr.c#L1828">1828</a>                 <b><i>/* For an (*,G) entry, we only check that the incomming</i></b>
<a name="L1829" href="source/net/ipv4/ipmr.c#L1829">1829</a> <b><i>                 * interface is part of the static tree.</i></b>
<a name="L1830" href="source/net/ipv4/ipmr.c#L1830">1830</a> <b><i>                 */</i></b>
<a name="L1831" href="source/net/ipv4/ipmr.c#L1831">1831</a>                 cache_proxy = <a href="ident?i=ipmr_cache_find_any_parent">ipmr_cache_find_any_parent</a>(mrt, <a href="ident?i=vif">vif</a>);
<a name="L1832" href="source/net/ipv4/ipmr.c#L1832">1832</a>                 if (cache_proxy &amp;&amp;
<a name="L1833" href="source/net/ipv4/ipmr.c#L1833">1833</a>                     cache_proxy-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[true_vifi] &lt; 255)
<a name="L1834" href="source/net/ipv4/ipmr.c#L1834">1834</a>                         goto <a href="ident?i=forward">forward</a>;
<a name="L1835" href="source/net/ipv4/ipmr.c#L1835">1835</a>         }
<a name="L1836" href="source/net/ipv4/ipmr.c#L1836">1836</a> 
<a name="L1837" href="source/net/ipv4/ipmr.c#L1837">1837</a>         <b><i>/*</i></b>
<a name="L1838" href="source/net/ipv4/ipmr.c#L1838">1838</a> <b><i>         * Wrong interface: drop packet and (maybe) send PIM assert.</i></b>
<a name="L1839" href="source/net/ipv4/ipmr.c#L1839">1839</a> <b><i>         */</i></b>
<a name="L1840" href="source/net/ipv4/ipmr.c#L1840">1840</a>         if (mrt-&gt;vif_table[<a href="ident?i=vif">vif</a>].<a href="ident?i=dev">dev</a> != <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>) {
<a name="L1841" href="source/net/ipv4/ipmr.c#L1841">1841</a>                 if (<a href="ident?i=rt_is_output_route">rt_is_output_route</a>(<a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>))) {
<a name="L1842" href="source/net/ipv4/ipmr.c#L1842">1842</a>                         <b><i>/* It is our own packet, looped back.</i></b>
<a name="L1843" href="source/net/ipv4/ipmr.c#L1843">1843</a> <b><i>                         * Very complicated situation...</i></b>
<a name="L1844" href="source/net/ipv4/ipmr.c#L1844">1844</a> <b><i>                         *</i></b>
<a name="L1845" href="source/net/ipv4/ipmr.c#L1845">1845</a> <b><i>                         * The best workaround until routing daemons will be</i></b>
<a name="L1846" href="source/net/ipv4/ipmr.c#L1846">1846</a> <b><i>                         * fixed is not to redistribute packet, if it was</i></b>
<a name="L1847" href="source/net/ipv4/ipmr.c#L1847">1847</a> <b><i>                         * send through wrong interface. It means, that</i></b>
<a name="L1848" href="source/net/ipv4/ipmr.c#L1848">1848</a> <b><i>                         * multicast applications WILL NOT work for</i></b>
<a name="L1849" href="source/net/ipv4/ipmr.c#L1849">1849</a> <b><i>                         * (S,G), which have default multicast route pointing</i></b>
<a name="L1850" href="source/net/ipv4/ipmr.c#L1850">1850</a> <b><i>                         * to wrong oif. In any case, it is not a good</i></b>
<a name="L1851" href="source/net/ipv4/ipmr.c#L1851">1851</a> <b><i>                         * idea to use multicasting applications on router.</i></b>
<a name="L1852" href="source/net/ipv4/ipmr.c#L1852">1852</a> <b><i>                         */</i></b>
<a name="L1853" href="source/net/ipv4/ipmr.c#L1853">1853</a>                         goto dont_forward;
<a name="L1854" href="source/net/ipv4/ipmr.c#L1854">1854</a>                 }
<a name="L1855" href="source/net/ipv4/ipmr.c#L1855">1855</a> 
<a name="L1856" href="source/net/ipv4/ipmr.c#L1856">1856</a>                 <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.wrong_if++;
<a name="L1857" href="source/net/ipv4/ipmr.c#L1857">1857</a> 
<a name="L1858" href="source/net/ipv4/ipmr.c#L1858">1858</a>                 if (true_vifi &gt;= 0 &amp;&amp; mrt-&gt;mroute_do_assert &amp;&amp;
<a name="L1859" href="source/net/ipv4/ipmr.c#L1859">1859</a>                     <b><i>/* pimsm uses asserts, when switching from RPT to SPT,</i></b>
<a name="L1860" href="source/net/ipv4/ipmr.c#L1860">1860</a> <b><i>                     * so that we cannot check that packet arrived on an oif.</i></b>
<a name="L1861" href="source/net/ipv4/ipmr.c#L1861">1861</a> <b><i>                     * It is bad, but otherwise we would need to move pretty</i></b>
<a name="L1862" href="source/net/ipv4/ipmr.c#L1862">1862</a> <b><i>                     * large chunk of pimd to kernel. Ough... --ANK</i></b>
<a name="L1863" href="source/net/ipv4/ipmr.c#L1863">1863</a> <b><i>                     */</i></b>
<a name="L1864" href="source/net/ipv4/ipmr.c#L1864">1864</a>                     (mrt-&gt;mroute_do_pim ||
<a name="L1865" href="source/net/ipv4/ipmr.c#L1865">1865</a>                      <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[true_vifi] &lt; 255) &amp;&amp;
<a name="L1866" href="source/net/ipv4/ipmr.c#L1866">1866</a>                     <a href="ident?i=time_after">time_after</a>(<a href="ident?i=jiffies">jiffies</a>,
<a name="L1867" href="source/net/ipv4/ipmr.c#L1867">1867</a>                                <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.last_assert + <a href="ident?i=MFC_ASSERT_THRESH">MFC_ASSERT_THRESH</a>)) {
<a name="L1868" href="source/net/ipv4/ipmr.c#L1868">1868</a>                         <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.last_assert = <a href="ident?i=jiffies">jiffies</a>;
<a name="L1869" href="source/net/ipv4/ipmr.c#L1869">1869</a>                         <a href="ident?i=ipmr_cache_report">ipmr_cache_report</a>(mrt, <a href="ident?i=skb">skb</a>, true_vifi, <a href="ident?i=IGMPMSG_WRONGVIF">IGMPMSG_WRONGVIF</a>);
<a name="L1870" href="source/net/ipv4/ipmr.c#L1870">1870</a>                 }
<a name="L1871" href="source/net/ipv4/ipmr.c#L1871">1871</a>                 goto dont_forward;
<a name="L1872" href="source/net/ipv4/ipmr.c#L1872">1872</a>         }
<a name="L1873" href="source/net/ipv4/ipmr.c#L1873">1873</a> 
<a name="L1874" href="source/net/ipv4/ipmr.c#L1874">1874</a> <a href="ident?i=forward">forward</a>:
<a name="L1875" href="source/net/ipv4/ipmr.c#L1875">1875</a>         mrt-&gt;vif_table[<a href="ident?i=vif">vif</a>].pkt_in++;
<a name="L1876" href="source/net/ipv4/ipmr.c#L1876">1876</a>         mrt-&gt;vif_table[<a href="ident?i=vif">vif</a>].bytes_in += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1877" href="source/net/ipv4/ipmr.c#L1877">1877</a> 
<a name="L1878" href="source/net/ipv4/ipmr.c#L1878">1878</a>         <b><i>/*</i></b>
<a name="L1879" href="source/net/ipv4/ipmr.c#L1879">1879</a> <b><i>         *      Forward the frame</i></b>
<a name="L1880" href="source/net/ipv4/ipmr.c#L1880">1880</a> <b><i>         */</i></b>
<a name="L1881" href="source/net/ipv4/ipmr.c#L1881">1881</a>         if (<a href="ident?i=cache">cache</a>-&gt;mfc_origin == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp;
<a name="L1882" href="source/net/ipv4/ipmr.c#L1882">1882</a>             <a href="ident?i=cache">cache</a>-&gt;mfc_mcastgrp == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>)) {
<a name="L1883" href="source/net/ipv4/ipmr.c#L1883">1883</a>                 if (true_vifi &gt;= 0 &amp;&amp;
<a name="L1884" href="source/net/ipv4/ipmr.c#L1884">1884</a>                     true_vifi != <a href="ident?i=cache">cache</a>-&gt;mfc_parent &amp;&amp;
<a name="L1885" href="source/net/ipv4/ipmr.c#L1885">1885</a>                     <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a> &gt;
<a name="L1886" href="source/net/ipv4/ipmr.c#L1886">1886</a>                                 <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[<a href="ident?i=cache">cache</a>-&gt;mfc_parent]) {
<a name="L1887" href="source/net/ipv4/ipmr.c#L1887">1887</a>                         <b><i>/* It's an (*,*) entry and the packet is not coming from</i></b>
<a name="L1888" href="source/net/ipv4/ipmr.c#L1888">1888</a> <b><i>                         * the upstream: forward the packet to the upstream</i></b>
<a name="L1889" href="source/net/ipv4/ipmr.c#L1889">1889</a> <b><i>                         * only.</i></b>
<a name="L1890" href="source/net/ipv4/ipmr.c#L1890">1890</a> <b><i>                         */</i></b>
<a name="L1891" href="source/net/ipv4/ipmr.c#L1891">1891</a>                         <a href="ident?i=psend">psend</a> = <a href="ident?i=cache">cache</a>-&gt;mfc_parent;
<a name="L1892" href="source/net/ipv4/ipmr.c#L1892">1892</a>                         goto last_forward;
<a name="L1893" href="source/net/ipv4/ipmr.c#L1893">1893</a>                 }
<a name="L1894" href="source/net/ipv4/ipmr.c#L1894">1894</a>                 goto dont_forward;
<a name="L1895" href="source/net/ipv4/ipmr.c#L1895">1895</a>         }
<a name="L1896" href="source/net/ipv4/ipmr.c#L1896">1896</a>         for (ct = <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.maxvif - 1;
<a name="L1897" href="source/net/ipv4/ipmr.c#L1897">1897</a>              ct &gt;= <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif; ct--) {
<a name="L1898" href="source/net/ipv4/ipmr.c#L1898">1898</a>                 <b><i>/* For (*,G) entry, don't forward to the incoming interface */</i></b>
<a name="L1899" href="source/net/ipv4/ipmr.c#L1899">1899</a>                 if ((<a href="ident?i=cache">cache</a>-&gt;mfc_origin != <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) ||
<a name="L1900" href="source/net/ipv4/ipmr.c#L1900">1900</a>                      ct != true_vifi) &amp;&amp;
<a name="L1901" href="source/net/ipv4/ipmr.c#L1901">1901</a>                     <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a> &gt; <a href="ident?i=cache">cache</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[ct]) {
<a name="L1902" href="source/net/ipv4/ipmr.c#L1902">1902</a>                         if (<a href="ident?i=psend">psend</a> != -1) {
<a name="L1903" href="source/net/ipv4/ipmr.c#L1903">1903</a>                                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1904" href="source/net/ipv4/ipmr.c#L1904">1904</a> 
<a name="L1905" href="source/net/ipv4/ipmr.c#L1905">1905</a>                                 if (skb2)
<a name="L1906" href="source/net/ipv4/ipmr.c#L1906">1906</a>                                         <a href="ident?i=ipmr_queue_xmit">ipmr_queue_xmit</a>(<a href="ident?i=net">net</a>, mrt, skb2, <a href="ident?i=cache">cache</a>,
<a name="L1907" href="source/net/ipv4/ipmr.c#L1907">1907</a>                                                         <a href="ident?i=psend">psend</a>);
<a name="L1908" href="source/net/ipv4/ipmr.c#L1908">1908</a>                         }
<a name="L1909" href="source/net/ipv4/ipmr.c#L1909">1909</a>                         <a href="ident?i=psend">psend</a> = ct;
<a name="L1910" href="source/net/ipv4/ipmr.c#L1910">1910</a>                 }
<a name="L1911" href="source/net/ipv4/ipmr.c#L1911">1911</a>         }
<a name="L1912" href="source/net/ipv4/ipmr.c#L1912">1912</a> last_forward:
<a name="L1913" href="source/net/ipv4/ipmr.c#L1913">1913</a>         if (<a href="ident?i=psend">psend</a> != -1) {
<a name="L1914" href="source/net/ipv4/ipmr.c#L1914">1914</a>                 if (local) {
<a name="L1915" href="source/net/ipv4/ipmr.c#L1915">1915</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1916" href="source/net/ipv4/ipmr.c#L1916">1916</a> 
<a name="L1917" href="source/net/ipv4/ipmr.c#L1917">1917</a>                         if (skb2)
<a name="L1918" href="source/net/ipv4/ipmr.c#L1918">1918</a>                                 <a href="ident?i=ipmr_queue_xmit">ipmr_queue_xmit</a>(<a href="ident?i=net">net</a>, mrt, skb2, <a href="ident?i=cache">cache</a>, <a href="ident?i=psend">psend</a>);
<a name="L1919" href="source/net/ipv4/ipmr.c#L1919">1919</a>                 } else {
<a name="L1920" href="source/net/ipv4/ipmr.c#L1920">1920</a>                         <a href="ident?i=ipmr_queue_xmit">ipmr_queue_xmit</a>(<a href="ident?i=net">net</a>, mrt, <a href="ident?i=skb">skb</a>, <a href="ident?i=cache">cache</a>, <a href="ident?i=psend">psend</a>);
<a name="L1921" href="source/net/ipv4/ipmr.c#L1921">1921</a>                         return;
<a name="L1922" href="source/net/ipv4/ipmr.c#L1922">1922</a>                 }
<a name="L1923" href="source/net/ipv4/ipmr.c#L1923">1923</a>         }
<a name="L1924" href="source/net/ipv4/ipmr.c#L1924">1924</a> 
<a name="L1925" href="source/net/ipv4/ipmr.c#L1925">1925</a> dont_forward:
<a name="L1926" href="source/net/ipv4/ipmr.c#L1926">1926</a>         if (!local)
<a name="L1927" href="source/net/ipv4/ipmr.c#L1927">1927</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1928" href="source/net/ipv4/ipmr.c#L1928">1928</a> }
<a name="L1929" href="source/net/ipv4/ipmr.c#L1929">1929</a> 
<a name="L1930" href="source/net/ipv4/ipmr.c#L1930">1930</a> static struct <a href="ident?i=mr_table">mr_table</a> *<a href="ident?i=ipmr_rt_fib_lookup">ipmr_rt_fib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1931" href="source/net/ipv4/ipmr.c#L1931">1931</a> {
<a name="L1932" href="source/net/ipv4/ipmr.c#L1932">1932</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L1933" href="source/net/ipv4/ipmr.c#L1933">1933</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1934" href="source/net/ipv4/ipmr.c#L1934">1934</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4 = {
<a name="L1935" href="source/net/ipv4/ipmr.c#L1935">1935</a>                 .<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L1936" href="source/net/ipv4/ipmr.c#L1936">1936</a>                 .<a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L1937" href="source/net/ipv4/ipmr.c#L1937">1937</a>                 .<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos),
<a name="L1938" href="source/net/ipv4/ipmr.c#L1938">1938</a>                 .<a href="ident?i=flowi4_oif">flowi4_oif</a> = (<a href="ident?i=rt_is_output_route">rt_is_output_route</a>(<a href="ident?i=rt">rt</a>) ?
<a name="L1939" href="source/net/ipv4/ipmr.c#L1939">1939</a>                                <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex : 0),
<a name="L1940" href="source/net/ipv4/ipmr.c#L1940">1940</a>                 .<a href="ident?i=flowi4_iif">flowi4_iif</a> = (<a href="ident?i=rt_is_output_route">rt_is_output_route</a>(<a href="ident?i=rt">rt</a>) ?
<a name="L1941" href="source/net/ipv4/ipmr.c#L1941">1941</a>                                <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a> :
<a name="L1942" href="source/net/ipv4/ipmr.c#L1942">1942</a>                                <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex),
<a name="L1943" href="source/net/ipv4/ipmr.c#L1943">1943</a>                 .<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>,
<a name="L1944" href="source/net/ipv4/ipmr.c#L1944">1944</a>         };
<a name="L1945" href="source/net/ipv4/ipmr.c#L1945">1945</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1946" href="source/net/ipv4/ipmr.c#L1946">1946</a>         int <a href="ident?i=err">err</a>;
<a name="L1947" href="source/net/ipv4/ipmr.c#L1947">1947</a> 
<a name="L1948" href="source/net/ipv4/ipmr.c#L1948">1948</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_fib_lookup">ipmr_fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;mrt);
<a name="L1949" href="source/net/ipv4/ipmr.c#L1949">1949</a>         if (<a href="ident?i=err">err</a>)
<a name="L1950" href="source/net/ipv4/ipmr.c#L1950">1950</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L1951" href="source/net/ipv4/ipmr.c#L1951">1951</a>         return mrt;
<a name="L1952" href="source/net/ipv4/ipmr.c#L1952">1952</a> }
<a name="L1953" href="source/net/ipv4/ipmr.c#L1953">1953</a> 
<a name="L1954" href="source/net/ipv4/ipmr.c#L1954">1954</a> <b><i>/*</i></b>
<a name="L1955" href="source/net/ipv4/ipmr.c#L1955">1955</a> <b><i> *      Multicast packets for forwarding arrive here</i></b>
<a name="L1956" href="source/net/ipv4/ipmr.c#L1956">1956</a> <b><i> *      Called with rcu_read_lock();</i></b>
<a name="L1957" href="source/net/ipv4/ipmr.c#L1957">1957</a> <b><i> */</i></b>
<a name="L1958" href="source/net/ipv4/ipmr.c#L1958">1958</a> 
<a name="L1959" href="source/net/ipv4/ipmr.c#L1959">1959</a> int <a href="ident?i=ip_mr_input">ip_mr_input</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1960" href="source/net/ipv4/ipmr.c#L1960">1960</a> {
<a name="L1961" href="source/net/ipv4/ipmr.c#L1961">1961</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=cache">cache</a>;
<a name="L1962" href="source/net/ipv4/ipmr.c#L1962">1962</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1963" href="source/net/ipv4/ipmr.c#L1963">1963</a>         int local = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>)-&gt;rt_flags &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L1964" href="source/net/ipv4/ipmr.c#L1964">1964</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L1965" href="source/net/ipv4/ipmr.c#L1965">1965</a> 
<a name="L1966" href="source/net/ipv4/ipmr.c#L1966">1966</a>         <b><i>/* Packet is looped back after forward, it should not be</i></b>
<a name="L1967" href="source/net/ipv4/ipmr.c#L1967">1967</a> <b><i>         * forwarded second time, but still can be delivered locally.</i></b>
<a name="L1968" href="source/net/ipv4/ipmr.c#L1968">1968</a> <b><i>         */</i></b>
<a name="L1969" href="source/net/ipv4/ipmr.c#L1969">1969</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_FORWARDED">IPSKB_FORWARDED</a>)
<a name="L1970" href="source/net/ipv4/ipmr.c#L1970">1970</a>                 goto dont_forward;
<a name="L1971" href="source/net/ipv4/ipmr.c#L1971">1971</a> 
<a name="L1972" href="source/net/ipv4/ipmr.c#L1972">1972</a>         mrt = <a href="ident?i=ipmr_rt_fib_lookup">ipmr_rt_fib_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>);
<a name="L1973" href="source/net/ipv4/ipmr.c#L1973">1973</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(mrt)) {
<a name="L1974" href="source/net/ipv4/ipmr.c#L1974">1974</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1975" href="source/net/ipv4/ipmr.c#L1975">1975</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(mrt);
<a name="L1976" href="source/net/ipv4/ipmr.c#L1976">1976</a>         }
<a name="L1977" href="source/net/ipv4/ipmr.c#L1977">1977</a>         if (!local) {
<a name="L1978" href="source/net/ipv4/ipmr.c#L1978">1978</a>                 if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt.router_alert) {
<a name="L1979" href="source/net/ipv4/ipmr.c#L1979">1979</a>                         if (<a href="ident?i=ip_call_ra_chain">ip_call_ra_chain</a>(<a href="ident?i=skb">skb</a>))
<a name="L1980" href="source/net/ipv4/ipmr.c#L1980">1980</a>                                 return 0;
<a name="L1981" href="source/net/ipv4/ipmr.c#L1981">1981</a>                 } else if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>) {
<a name="L1982" href="source/net/ipv4/ipmr.c#L1982">1982</a>                         <b><i>/* IGMPv1 (and broken IGMPv2 implementations sort of</i></b>
<a name="L1983" href="source/net/ipv4/ipmr.c#L1983">1983</a> <b><i>                         * Cisco IOS &lt;= 11.2(8)) do not put router alert</i></b>
<a name="L1984" href="source/net/ipv4/ipmr.c#L1984">1984</a> <b><i>                         * option to IGMP packets destined to routable</i></b>
<a name="L1985" href="source/net/ipv4/ipmr.c#L1985">1985</a> <b><i>                         * groups. It is very bad, because it means</i></b>
<a name="L1986" href="source/net/ipv4/ipmr.c#L1986">1986</a> <b><i>                         * that we can forward NO IGMP messages.</i></b>
<a name="L1987" href="source/net/ipv4/ipmr.c#L1987">1987</a> <b><i>                         */</i></b>
<a name="L1988" href="source/net/ipv4/ipmr.c#L1988">1988</a>                         struct <a href="ident?i=sock">sock</a> *mroute_sk;
<a name="L1989" href="source/net/ipv4/ipmr.c#L1989">1989</a> 
<a name="L1990" href="source/net/ipv4/ipmr.c#L1990">1990</a>                         mroute_sk = <a href="ident?i=rcu_dereference">rcu_dereference</a>(mrt-&gt;mroute_sk);
<a name="L1991" href="source/net/ipv4/ipmr.c#L1991">1991</a>                         if (mroute_sk) {
<a name="L1992" href="source/net/ipv4/ipmr.c#L1992">1992</a>                                 <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L1993" href="source/net/ipv4/ipmr.c#L1993">1993</a>                                 <a href="ident?i=raw_rcv">raw_rcv</a>(mroute_sk, <a href="ident?i=skb">skb</a>);
<a name="L1994" href="source/net/ipv4/ipmr.c#L1994">1994</a>                                 return 0;
<a name="L1995" href="source/net/ipv4/ipmr.c#L1995">1995</a>                         }
<a name="L1996" href="source/net/ipv4/ipmr.c#L1996">1996</a>                     }
<a name="L1997" href="source/net/ipv4/ipmr.c#L1997">1997</a>         }
<a name="L1998" href="source/net/ipv4/ipmr.c#L1998">1998</a> 
<a name="L1999" href="source/net/ipv4/ipmr.c#L1999">1999</a>         <b><i>/* already under rcu_read_lock() */</i></b>
<a name="L2000" href="source/net/ipv4/ipmr.c#L2000">2000</a>         <a href="ident?i=cache">cache</a> = <a href="ident?i=ipmr_cache_find">ipmr_cache_find</a>(mrt, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L2001" href="source/net/ipv4/ipmr.c#L2001">2001</a>         if (!<a href="ident?i=cache">cache</a>) {
<a name="L2002" href="source/net/ipv4/ipmr.c#L2002">2002</a>                 int <a href="ident?i=vif">vif</a> = <a href="ident?i=ipmr_find_vif">ipmr_find_vif</a>(mrt, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2003" href="source/net/ipv4/ipmr.c#L2003">2003</a> 
<a name="L2004" href="source/net/ipv4/ipmr.c#L2004">2004</a>                 if (<a href="ident?i=vif">vif</a> &gt;= 0)
<a name="L2005" href="source/net/ipv4/ipmr.c#L2005">2005</a>                         <a href="ident?i=cache">cache</a> = <a href="ident?i=ipmr_cache_find_any">ipmr_cache_find_any</a>(mrt, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L2006" href="source/net/ipv4/ipmr.c#L2006">2006</a>                                                     <a href="ident?i=vif">vif</a>);
<a name="L2007" href="source/net/ipv4/ipmr.c#L2007">2007</a>         }
<a name="L2008" href="source/net/ipv4/ipmr.c#L2008">2008</a> 
<a name="L2009" href="source/net/ipv4/ipmr.c#L2009">2009</a>         <b><i>/*</i></b>
<a name="L2010" href="source/net/ipv4/ipmr.c#L2010">2010</a> <b><i>         *      No usable cache entry</i></b>
<a name="L2011" href="source/net/ipv4/ipmr.c#L2011">2011</a> <b><i>         */</i></b>
<a name="L2012" href="source/net/ipv4/ipmr.c#L2012">2012</a>         if (!<a href="ident?i=cache">cache</a>) {
<a name="L2013" href="source/net/ipv4/ipmr.c#L2013">2013</a>                 int <a href="ident?i=vif">vif</a>;
<a name="L2014" href="source/net/ipv4/ipmr.c#L2014">2014</a> 
<a name="L2015" href="source/net/ipv4/ipmr.c#L2015">2015</a>                 if (local) {
<a name="L2016" href="source/net/ipv4/ipmr.c#L2016">2016</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2017" href="source/net/ipv4/ipmr.c#L2017">2017</a>                         <a href="ident?i=ip_local_deliver">ip_local_deliver</a>(<a href="ident?i=skb">skb</a>);
<a name="L2018" href="source/net/ipv4/ipmr.c#L2018">2018</a>                         if (!skb2)
<a name="L2019" href="source/net/ipv4/ipmr.c#L2019">2019</a>                                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2020" href="source/net/ipv4/ipmr.c#L2020">2020</a>                         <a href="ident?i=skb">skb</a> = skb2;
<a name="L2021" href="source/net/ipv4/ipmr.c#L2021">2021</a>                 }
<a name="L2022" href="source/net/ipv4/ipmr.c#L2022">2022</a> 
<a name="L2023" href="source/net/ipv4/ipmr.c#L2023">2023</a>                 <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L2024" href="source/net/ipv4/ipmr.c#L2024">2024</a>                 <a href="ident?i=vif">vif</a> = <a href="ident?i=ipmr_find_vif">ipmr_find_vif</a>(mrt, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2025" href="source/net/ipv4/ipmr.c#L2025">2025</a>                 if (<a href="ident?i=vif">vif</a> &gt;= 0) {
<a name="L2026" href="source/net/ipv4/ipmr.c#L2026">2026</a>                         int err2 = <a href="ident?i=ipmr_cache_unresolved">ipmr_cache_unresolved</a>(mrt, <a href="ident?i=vif">vif</a>, <a href="ident?i=skb">skb</a>);
<a name="L2027" href="source/net/ipv4/ipmr.c#L2027">2027</a>                         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2028" href="source/net/ipv4/ipmr.c#L2028">2028</a> 
<a name="L2029" href="source/net/ipv4/ipmr.c#L2029">2029</a>                         return err2;
<a name="L2030" href="source/net/ipv4/ipmr.c#L2030">2030</a>                 }
<a name="L2031" href="source/net/ipv4/ipmr.c#L2031">2031</a>                 <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2032" href="source/net/ipv4/ipmr.c#L2032">2032</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2033" href="source/net/ipv4/ipmr.c#L2033">2033</a>                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L2034" href="source/net/ipv4/ipmr.c#L2034">2034</a>         }
<a name="L2035" href="source/net/ipv4/ipmr.c#L2035">2035</a> 
<a name="L2036" href="source/net/ipv4/ipmr.c#L2036">2036</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L2037" href="source/net/ipv4/ipmr.c#L2037">2037</a>         <a href="ident?i=ip_mr_forward">ip_mr_forward</a>(<a href="ident?i=net">net</a>, mrt, <a href="ident?i=skb">skb</a>, <a href="ident?i=cache">cache</a>, local);
<a name="L2038" href="source/net/ipv4/ipmr.c#L2038">2038</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2039" href="source/net/ipv4/ipmr.c#L2039">2039</a> 
<a name="L2040" href="source/net/ipv4/ipmr.c#L2040">2040</a>         if (local)
<a name="L2041" href="source/net/ipv4/ipmr.c#L2041">2041</a>                 return <a href="ident?i=ip_local_deliver">ip_local_deliver</a>(<a href="ident?i=skb">skb</a>);
<a name="L2042" href="source/net/ipv4/ipmr.c#L2042">2042</a> 
<a name="L2043" href="source/net/ipv4/ipmr.c#L2043">2043</a>         return 0;
<a name="L2044" href="source/net/ipv4/ipmr.c#L2044">2044</a> 
<a name="L2045" href="source/net/ipv4/ipmr.c#L2045">2045</a> dont_forward:
<a name="L2046" href="source/net/ipv4/ipmr.c#L2046">2046</a>         if (local)
<a name="L2047" href="source/net/ipv4/ipmr.c#L2047">2047</a>                 return <a href="ident?i=ip_local_deliver">ip_local_deliver</a>(<a href="ident?i=skb">skb</a>);
<a name="L2048" href="source/net/ipv4/ipmr.c#L2048">2048</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2049" href="source/net/ipv4/ipmr.c#L2049">2049</a>         return 0;
<a name="L2050" href="source/net/ipv4/ipmr.c#L2050">2050</a> }
<a name="L2051" href="source/net/ipv4/ipmr.c#L2051">2051</a> 
<a name="L2052" href="source/net/ipv4/ipmr.c#L2052">2052</a> #ifdef <a href="ident?i=CONFIG_IP_PIMSM">CONFIG_IP_PIMSM</a>
<a name="L2053" href="source/net/ipv4/ipmr.c#L2053">2053</a> <b><i>/* called with rcu_read_lock() */</i></b>
<a name="L2054" href="source/net/ipv4/ipmr.c#L2054">2054</a> static int <a href="ident?i=__pim_rcv">__pim_rcv</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L2055" href="source/net/ipv4/ipmr.c#L2055">2055</a>                      unsigned int pimlen)
<a name="L2056" href="source/net/ipv4/ipmr.c#L2056">2056</a> {
<a name="L2057" href="source/net/ipv4/ipmr.c#L2057">2057</a>         struct <a href="ident?i=net_device">net_device</a> *reg_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L2058" href="source/net/ipv4/ipmr.c#L2058">2058</a>         struct <a href="ident?i=iphdr">iphdr</a> *encap;
<a name="L2059" href="source/net/ipv4/ipmr.c#L2059">2059</a> 
<a name="L2060" href="source/net/ipv4/ipmr.c#L2060">2060</a>         encap = (struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>) + pimlen);
<a name="L2061" href="source/net/ipv4/ipmr.c#L2061">2061</a>         <b><i>/*</i></b>
<a name="L2062" href="source/net/ipv4/ipmr.c#L2062">2062</a> <b><i>         * Check that:</i></b>
<a name="L2063" href="source/net/ipv4/ipmr.c#L2063">2063</a> <b><i>         * a. packet is really sent to a multicast group</i></b>
<a name="L2064" href="source/net/ipv4/ipmr.c#L2064">2064</a> <b><i>         * b. packet is not a NULL-REGISTER</i></b>
<a name="L2065" href="source/net/ipv4/ipmr.c#L2065">2065</a> <b><i>         * c. packet is not truncated</i></b>
<a name="L2066" href="source/net/ipv4/ipmr.c#L2066">2066</a> <b><i>         */</i></b>
<a name="L2067" href="source/net/ipv4/ipmr.c#L2067">2067</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(encap-&gt;<a href="ident?i=daddr">daddr</a>) ||
<a name="L2068" href="source/net/ipv4/ipmr.c#L2068">2068</a>             encap-&gt;tot_len == 0 ||
<a name="L2069" href="source/net/ipv4/ipmr.c#L2069">2069</a>             <a href="ident?i=ntohs">ntohs</a>(encap-&gt;tot_len) + pimlen &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L2070" href="source/net/ipv4/ipmr.c#L2070">2070</a>                 return 1;
<a name="L2071" href="source/net/ipv4/ipmr.c#L2071">2071</a> 
<a name="L2072" href="source/net/ipv4/ipmr.c#L2072">2072</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L2073" href="source/net/ipv4/ipmr.c#L2073">2073</a>         if (mrt-&gt;mroute_reg_vif_num &gt;= 0)
<a name="L2074" href="source/net/ipv4/ipmr.c#L2074">2074</a>                 reg_dev = mrt-&gt;vif_table[mrt-&gt;mroute_reg_vif_num].<a href="ident?i=dev">dev</a>;
<a name="L2075" href="source/net/ipv4/ipmr.c#L2075">2075</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2076" href="source/net/ipv4/ipmr.c#L2076">2076</a> 
<a name="L2077" href="source/net/ipv4/ipmr.c#L2077">2077</a>         if (!reg_dev)
<a name="L2078" href="source/net/ipv4/ipmr.c#L2078">2078</a>                 return 1;
<a name="L2079" href="source/net/ipv4/ipmr.c#L2079">2079</a> 
<a name="L2080" href="source/net/ipv4/ipmr.c#L2080">2080</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mac_header">mac_header</a> = <a href="ident?i=skb">skb</a>-&gt;network_header;
<a name="L2081" href="source/net/ipv4/ipmr.c#L2081">2081</a>         <a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, (<a href="ident?i=u8">u8</a> *)encap - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>);
<a name="L2082" href="source/net/ipv4/ipmr.c#L2082">2082</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L2083" href="source/net/ipv4/ipmr.c#L2083">2083</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L2084" href="source/net/ipv4/ipmr.c#L2084">2084</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L2085" href="source/net/ipv4/ipmr.c#L2085">2085</a> 
<a name="L2086" href="source/net/ipv4/ipmr.c#L2086">2086</a>         <a href="ident?i=skb_tunnel_rx">skb_tunnel_rx</a>(<a href="ident?i=skb">skb</a>, reg_dev, <a href="ident?i=dev_net">dev_net</a>(reg_dev));
<a name="L2087" href="source/net/ipv4/ipmr.c#L2087">2087</a> 
<a name="L2088" href="source/net/ipv4/ipmr.c#L2088">2088</a>         <a href="ident?i=netif_rx">netif_rx</a>(<a href="ident?i=skb">skb</a>);
<a name="L2089" href="source/net/ipv4/ipmr.c#L2089">2089</a> 
<a name="L2090" href="source/net/ipv4/ipmr.c#L2090">2090</a>         return <a href="ident?i=NET_RX_SUCCESS">NET_RX_SUCCESS</a>;
<a name="L2091" href="source/net/ipv4/ipmr.c#L2091">2091</a> }
<a name="L2092" href="source/net/ipv4/ipmr.c#L2092">2092</a> #endif
<a name="L2093" href="source/net/ipv4/ipmr.c#L2093">2093</a> 
<a name="L2094" href="source/net/ipv4/ipmr.c#L2094">2094</a> #ifdef CONFIG_IP_PIMSM_V1
<a name="L2095" href="source/net/ipv4/ipmr.c#L2095">2095</a> <b><i>/*</i></b>
<a name="L2096" href="source/net/ipv4/ipmr.c#L2096">2096</a> <b><i> * Handle IGMP messages of PIMv1</i></b>
<a name="L2097" href="source/net/ipv4/ipmr.c#L2097">2097</a> <b><i> */</i></b>
<a name="L2098" href="source/net/ipv4/ipmr.c#L2098">2098</a> 
<a name="L2099" href="source/net/ipv4/ipmr.c#L2099">2099</a> int <a href="ident?i=pim_rcv_v1">pim_rcv_v1</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2100" href="source/net/ipv4/ipmr.c#L2100">2100</a> {
<a name="L2101" href="source/net/ipv4/ipmr.c#L2101">2101</a>         struct <a href="ident?i=igmphdr">igmphdr</a> *pim;
<a name="L2102" href="source/net/ipv4/ipmr.c#L2102">2102</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2103" href="source/net/ipv4/ipmr.c#L2103">2103</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2104" href="source/net/ipv4/ipmr.c#L2104">2104</a> 
<a name="L2105" href="source/net/ipv4/ipmr.c#L2105">2105</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*pim) + sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
<a name="L2106" href="source/net/ipv4/ipmr.c#L2106">2106</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L2107" href="source/net/ipv4/ipmr.c#L2107">2107</a> 
<a name="L2108" href="source/net/ipv4/ipmr.c#L2108">2108</a>         pim = <a href="ident?i=igmp_hdr">igmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2109" href="source/net/ipv4/ipmr.c#L2109">2109</a> 
<a name="L2110" href="source/net/ipv4/ipmr.c#L2110">2110</a>         mrt = <a href="ident?i=ipmr_rt_fib_lookup">ipmr_rt_fib_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>);
<a name="L2111" href="source/net/ipv4/ipmr.c#L2111">2111</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(mrt))
<a name="L2112" href="source/net/ipv4/ipmr.c#L2112">2112</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L2113" href="source/net/ipv4/ipmr.c#L2113">2113</a>         if (!mrt-&gt;mroute_do_pim ||
<a name="L2114" href="source/net/ipv4/ipmr.c#L2114">2114</a>             pim-&gt;<a href="ident?i=group">group</a> != <a href="ident?i=PIM_V1_VERSION">PIM_V1_VERSION</a> || pim-&gt;<a href="ident?i=code">code</a> != <a href="ident?i=PIM_V1_REGISTER">PIM_V1_REGISTER</a>)
<a name="L2115" href="source/net/ipv4/ipmr.c#L2115">2115</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L2116" href="source/net/ipv4/ipmr.c#L2116">2116</a> 
<a name="L2117" href="source/net/ipv4/ipmr.c#L2117">2117</a>         if (<a href="ident?i=__pim_rcv">__pim_rcv</a>(mrt, <a href="ident?i=skb">skb</a>, sizeof(*pim))) {
<a name="L2118" href="source/net/ipv4/ipmr.c#L2118">2118</a> <a href="ident?i=drop">drop</a>:
<a name="L2119" href="source/net/ipv4/ipmr.c#L2119">2119</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2120" href="source/net/ipv4/ipmr.c#L2120">2120</a>         }
<a name="L2121" href="source/net/ipv4/ipmr.c#L2121">2121</a>         return 0;
<a name="L2122" href="source/net/ipv4/ipmr.c#L2122">2122</a> }
<a name="L2123" href="source/net/ipv4/ipmr.c#L2123">2123</a> #endif
<a name="L2124" href="source/net/ipv4/ipmr.c#L2124">2124</a> 
<a name="L2125" href="source/net/ipv4/ipmr.c#L2125">2125</a> #ifdef CONFIG_IP_PIMSM_V2
<a name="L2126" href="source/net/ipv4/ipmr.c#L2126">2126</a> static int <a href="ident?i=pim_rcv">pim_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2127" href="source/net/ipv4/ipmr.c#L2127">2127</a> {
<a name="L2128" href="source/net/ipv4/ipmr.c#L2128">2128</a>         struct <a href="ident?i=pimreghdr">pimreghdr</a> *pim;
<a name="L2129" href="source/net/ipv4/ipmr.c#L2129">2129</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2130" href="source/net/ipv4/ipmr.c#L2130">2130</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2131" href="source/net/ipv4/ipmr.c#L2131">2131</a> 
<a name="L2132" href="source/net/ipv4/ipmr.c#L2132">2132</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*pim) + sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
<a name="L2133" href="source/net/ipv4/ipmr.c#L2133">2133</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L2134" href="source/net/ipv4/ipmr.c#L2134">2134</a> 
<a name="L2135" href="source/net/ipv4/ipmr.c#L2135">2135</a>         pim = (struct <a href="ident?i=pimreghdr">pimreghdr</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L2136" href="source/net/ipv4/ipmr.c#L2136">2136</a>         if (pim-&gt;<a href="ident?i=type">type</a> != ((<a href="ident?i=PIM_VERSION">PIM_VERSION</a> &lt;&lt; 4) | (<a href="ident?i=PIM_REGISTER">PIM_REGISTER</a>)) ||
<a name="L2137" href="source/net/ipv4/ipmr.c#L2137">2137</a>             (pim-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=PIM_NULL_REGISTER">PIM_NULL_REGISTER</a>) ||
<a name="L2138" href="source/net/ipv4/ipmr.c#L2138">2138</a>             (<a href="ident?i=ip_compute_csum">ip_compute_csum</a>((void *)pim, sizeof(*pim)) != 0 &amp;&amp;
<a name="L2139" href="source/net/ipv4/ipmr.c#L2139">2139</a>              <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, 0))))
<a name="L2140" href="source/net/ipv4/ipmr.c#L2140">2140</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L2141" href="source/net/ipv4/ipmr.c#L2141">2141</a> 
<a name="L2142" href="source/net/ipv4/ipmr.c#L2142">2142</a>         mrt = <a href="ident?i=ipmr_rt_fib_lookup">ipmr_rt_fib_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>);
<a name="L2143" href="source/net/ipv4/ipmr.c#L2143">2143</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(mrt))
<a name="L2144" href="source/net/ipv4/ipmr.c#L2144">2144</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L2145" href="source/net/ipv4/ipmr.c#L2145">2145</a>         if (<a href="ident?i=__pim_rcv">__pim_rcv</a>(mrt, <a href="ident?i=skb">skb</a>, sizeof(*pim))) {
<a name="L2146" href="source/net/ipv4/ipmr.c#L2146">2146</a> <a href="ident?i=drop">drop</a>:
<a name="L2147" href="source/net/ipv4/ipmr.c#L2147">2147</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2148" href="source/net/ipv4/ipmr.c#L2148">2148</a>         }
<a name="L2149" href="source/net/ipv4/ipmr.c#L2149">2149</a>         return 0;
<a name="L2150" href="source/net/ipv4/ipmr.c#L2150">2150</a> }
<a name="L2151" href="source/net/ipv4/ipmr.c#L2151">2151</a> #endif
<a name="L2152" href="source/net/ipv4/ipmr.c#L2152">2152</a> 
<a name="L2153" href="source/net/ipv4/ipmr.c#L2153">2153</a> static int <a href="ident?i=__ipmr_fill_mroute">__ipmr_fill_mroute</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L2154" href="source/net/ipv4/ipmr.c#L2154">2154</a>                               struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, struct <a href="ident?i=rtmsg">rtmsg</a> *rtm)
<a name="L2155" href="source/net/ipv4/ipmr.c#L2155">2155</a> {
<a name="L2156" href="source/net/ipv4/ipmr.c#L2156">2156</a>         int ct;
<a name="L2157" href="source/net/ipv4/ipmr.c#L2157">2157</a>         struct <a href="ident?i=rtnexthop">rtnexthop</a> *nhp;
<a name="L2158" href="source/net/ipv4/ipmr.c#L2158">2158</a>         struct <a href="ident?i=nlattr">nlattr</a> *mp_attr;
<a name="L2159" href="source/net/ipv4/ipmr.c#L2159">2159</a>         struct <a href="ident?i=rta_mfc_stats">rta_mfc_stats</a> mfcs;
<a name="L2160" href="source/net/ipv4/ipmr.c#L2160">2160</a> 
<a name="L2161" href="source/net/ipv4/ipmr.c#L2161">2161</a>         <b><i>/* If cache is unresolved, don't try to parse IIF and OIF */</i></b>
<a name="L2162" href="source/net/ipv4/ipmr.c#L2162">2162</a>         if (<a href="ident?i=c">c</a>-&gt;mfc_parent &gt;= <a href="ident?i=MAXVIFS">MAXVIFS</a>)
<a name="L2163" href="source/net/ipv4/ipmr.c#L2163">2163</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L2164" href="source/net/ipv4/ipmr.c#L2164">2164</a> 
<a name="L2165" href="source/net/ipv4/ipmr.c#L2165">2165</a>         if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, <a href="ident?i=c">c</a>-&gt;mfc_parent) &amp;&amp;
<a name="L2166" href="source/net/ipv4/ipmr.c#L2166">2166</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_IIF, mrt-&gt;vif_table[<a href="ident?i=c">c</a>-&gt;mfc_parent].<a href="ident?i=dev">dev</a>-&gt;ifindex) &lt; 0)
<a name="L2167" href="source/net/ipv4/ipmr.c#L2167">2167</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2168" href="source/net/ipv4/ipmr.c#L2168">2168</a> 
<a name="L2169" href="source/net/ipv4/ipmr.c#L2169">2169</a>         if (!(mp_attr = <a href="ident?i=nla_nest_start">nla_nest_start</a>(<a href="ident?i=skb">skb</a>, RTA_MULTIPATH)))
<a name="L2170" href="source/net/ipv4/ipmr.c#L2170">2170</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2171" href="source/net/ipv4/ipmr.c#L2171">2171</a> 
<a name="L2172" href="source/net/ipv4/ipmr.c#L2172">2172</a>         for (ct = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif; ct &lt; <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.maxvif; ct++) {
<a name="L2173" href="source/net/ipv4/ipmr.c#L2173">2173</a>                 if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, ct) &amp;&amp; <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[ct] &lt; 255) {
<a name="L2174" href="source/net/ipv4/ipmr.c#L2174">2174</a>                         if (!(nhp = <a href="ident?i=nla_reserve_nohdr">nla_reserve_nohdr</a>(<a href="ident?i=skb">skb</a>, sizeof(*nhp)))) {
<a name="L2175" href="source/net/ipv4/ipmr.c#L2175">2175</a>                                 <a href="ident?i=nla_nest_cancel">nla_nest_cancel</a>(<a href="ident?i=skb">skb</a>, mp_attr);
<a name="L2176" href="source/net/ipv4/ipmr.c#L2176">2176</a>                                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2177" href="source/net/ipv4/ipmr.c#L2177">2177</a>                         }
<a name="L2178" href="source/net/ipv4/ipmr.c#L2178">2178</a> 
<a name="L2179" href="source/net/ipv4/ipmr.c#L2179">2179</a>                         nhp-&gt;rtnh_flags = 0;
<a name="L2180" href="source/net/ipv4/ipmr.c#L2180">2180</a>                         nhp-&gt;rtnh_hops = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[ct];
<a name="L2181" href="source/net/ipv4/ipmr.c#L2181">2181</a>                         nhp-&gt;rtnh_ifindex = mrt-&gt;vif_table[ct].<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L2182" href="source/net/ipv4/ipmr.c#L2182">2182</a>                         nhp-&gt;rtnh_len = sizeof(*nhp);
<a name="L2183" href="source/net/ipv4/ipmr.c#L2183">2183</a>                 }
<a name="L2184" href="source/net/ipv4/ipmr.c#L2184">2184</a>         }
<a name="L2185" href="source/net/ipv4/ipmr.c#L2185">2185</a> 
<a name="L2186" href="source/net/ipv4/ipmr.c#L2186">2186</a>         <a href="ident?i=nla_nest_end">nla_nest_end</a>(<a href="ident?i=skb">skb</a>, mp_attr);
<a name="L2187" href="source/net/ipv4/ipmr.c#L2187">2187</a> 
<a name="L2188" href="source/net/ipv4/ipmr.c#L2188">2188</a>         mfcs.mfcs_packets = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=pkt">pkt</a>;
<a name="L2189" href="source/net/ipv4/ipmr.c#L2189">2189</a>         mfcs.mfcs_bytes = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=bytes">bytes</a>;
<a name="L2190" href="source/net/ipv4/ipmr.c#L2190">2190</a>         mfcs.mfcs_wrong_if = <a href="ident?i=c">c</a>-&gt;mfc_un.<a href="ident?i=res">res</a>.wrong_if;
<a name="L2191" href="source/net/ipv4/ipmr.c#L2191">2191</a>         if (<a href="ident?i=nla_put">nla_put</a>(<a href="ident?i=skb">skb</a>, RTA_MFC_STATS, sizeof(mfcs), &amp;mfcs) &lt; 0)
<a name="L2192" href="source/net/ipv4/ipmr.c#L2192">2192</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2193" href="source/net/ipv4/ipmr.c#L2193">2193</a> 
<a name="L2194" href="source/net/ipv4/ipmr.c#L2194">2194</a>         rtm-&gt;rtm_type = RTN_MULTICAST;
<a name="L2195" href="source/net/ipv4/ipmr.c#L2195">2195</a>         return 1;
<a name="L2196" href="source/net/ipv4/ipmr.c#L2196">2196</a> }
<a name="L2197" href="source/net/ipv4/ipmr.c#L2197">2197</a> 
<a name="L2198" href="source/net/ipv4/ipmr.c#L2198">2198</a> int <a href="ident?i=ipmr_get_route">ipmr_get_route</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L2199" href="source/net/ipv4/ipmr.c#L2199">2199</a>                    <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>,
<a name="L2200" href="source/net/ipv4/ipmr.c#L2200">2200</a>                    struct <a href="ident?i=rtmsg">rtmsg</a> *rtm, int <a href="ident?i=nowait">nowait</a>)
<a name="L2201" href="source/net/ipv4/ipmr.c#L2201">2201</a> {
<a name="L2202" href="source/net/ipv4/ipmr.c#L2202">2202</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=cache">cache</a>;
<a name="L2203" href="source/net/ipv4/ipmr.c#L2203">2203</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2204" href="source/net/ipv4/ipmr.c#L2204">2204</a>         int <a href="ident?i=err">err</a>;
<a name="L2205" href="source/net/ipv4/ipmr.c#L2205">2205</a> 
<a name="L2206" href="source/net/ipv4/ipmr.c#L2206">2206</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_DEFAULT);
<a name="L2207" href="source/net/ipv4/ipmr.c#L2207">2207</a>         if (!mrt)
<a name="L2208" href="source/net/ipv4/ipmr.c#L2208">2208</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L2209" href="source/net/ipv4/ipmr.c#L2209">2209</a> 
<a name="L2210" href="source/net/ipv4/ipmr.c#L2210">2210</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2211" href="source/net/ipv4/ipmr.c#L2211">2211</a>         <a href="ident?i=cache">cache</a> = <a href="ident?i=ipmr_cache_find">ipmr_cache_find</a>(mrt, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>);
<a name="L2212" href="source/net/ipv4/ipmr.c#L2212">2212</a>         if (!<a href="ident?i=cache">cache</a> &amp;&amp; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>) {
<a name="L2213" href="source/net/ipv4/ipmr.c#L2213">2213</a>                 int <a href="ident?i=vif">vif</a> = <a href="ident?i=ipmr_find_vif">ipmr_find_vif</a>(mrt, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2214" href="source/net/ipv4/ipmr.c#L2214">2214</a> 
<a name="L2215" href="source/net/ipv4/ipmr.c#L2215">2215</a>                 if (<a href="ident?i=vif">vif</a> &gt;= 0)
<a name="L2216" href="source/net/ipv4/ipmr.c#L2216">2216</a>                         <a href="ident?i=cache">cache</a> = <a href="ident?i=ipmr_cache_find_any">ipmr_cache_find_any</a>(mrt, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=vif">vif</a>);
<a name="L2217" href="source/net/ipv4/ipmr.c#L2217">2217</a>         }
<a name="L2218" href="source/net/ipv4/ipmr.c#L2218">2218</a>         if (!<a href="ident?i=cache">cache</a>) {
<a name="L2219" href="source/net/ipv4/ipmr.c#L2219">2219</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb2;
<a name="L2220" href="source/net/ipv4/ipmr.c#L2220">2220</a>                 struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L2221" href="source/net/ipv4/ipmr.c#L2221">2221</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L2222" href="source/net/ipv4/ipmr.c#L2222">2222</a>                 int <a href="ident?i=vif">vif</a> = -1;
<a name="L2223" href="source/net/ipv4/ipmr.c#L2223">2223</a> 
<a name="L2224" href="source/net/ipv4/ipmr.c#L2224">2224</a>                 if (<a href="ident?i=nowait">nowait</a>) {
<a name="L2225" href="source/net/ipv4/ipmr.c#L2225">2225</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2226" href="source/net/ipv4/ipmr.c#L2226">2226</a>                         return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L2227" href="source/net/ipv4/ipmr.c#L2227">2227</a>                 }
<a name="L2228" href="source/net/ipv4/ipmr.c#L2228">2228</a> 
<a name="L2229" href="source/net/ipv4/ipmr.c#L2229">2229</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L2230" href="source/net/ipv4/ipmr.c#L2230">2230</a>                 <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L2231" href="source/net/ipv4/ipmr.c#L2231">2231</a>                 if (<a href="ident?i=dev">dev</a>)
<a name="L2232" href="source/net/ipv4/ipmr.c#L2232">2232</a>                         <a href="ident?i=vif">vif</a> = <a href="ident?i=ipmr_find_vif">ipmr_find_vif</a>(mrt, <a href="ident?i=dev">dev</a>);
<a name="L2233" href="source/net/ipv4/ipmr.c#L2233">2233</a>                 if (<a href="ident?i=vif">vif</a> &lt; 0) {
<a name="L2234" href="source/net/ipv4/ipmr.c#L2234">2234</a>                         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2235" href="source/net/ipv4/ipmr.c#L2235">2235</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2236" href="source/net/ipv4/ipmr.c#L2236">2236</a>                         return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L2237" href="source/net/ipv4/ipmr.c#L2237">2237</a>                 }
<a name="L2238" href="source/net/ipv4/ipmr.c#L2238">2238</a>                 skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2239" href="source/net/ipv4/ipmr.c#L2239">2239</a>                 if (!skb2) {
<a name="L2240" href="source/net/ipv4/ipmr.c#L2240">2240</a>                         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2241" href="source/net/ipv4/ipmr.c#L2241">2241</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2242" href="source/net/ipv4/ipmr.c#L2242">2242</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2243" href="source/net/ipv4/ipmr.c#L2243">2243</a>                 }
<a name="L2244" href="source/net/ipv4/ipmr.c#L2244">2244</a> 
<a name="L2245" href="source/net/ipv4/ipmr.c#L2245">2245</a>                 <a href="ident?i=skb_push">skb_push</a>(skb2, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L2246" href="source/net/ipv4/ipmr.c#L2246">2246</a>                 <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(skb2);
<a name="L2247" href="source/net/ipv4/ipmr.c#L2247">2247</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(skb2);
<a name="L2248" href="source/net/ipv4/ipmr.c#L2248">2248</a>                 iph-&gt;ihl = sizeof(struct <a href="ident?i=iphdr">iphdr</a>) &gt;&gt; 2;
<a name="L2249" href="source/net/ipv4/ipmr.c#L2249">2249</a>                 iph-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L2250" href="source/net/ipv4/ipmr.c#L2250">2250</a>                 iph-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L2251" href="source/net/ipv4/ipmr.c#L2251">2251</a>                 iph-&gt;<a href="ident?i=version">version</a> = 0;
<a name="L2252" href="source/net/ipv4/ipmr.c#L2252">2252</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_cache_unresolved">ipmr_cache_unresolved</a>(mrt, <a href="ident?i=vif">vif</a>, skb2);
<a name="L2253" href="source/net/ipv4/ipmr.c#L2253">2253</a>                 <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2254" href="source/net/ipv4/ipmr.c#L2254">2254</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2255" href="source/net/ipv4/ipmr.c#L2255">2255</a>                 return <a href="ident?i=err">err</a>;
<a name="L2256" href="source/net/ipv4/ipmr.c#L2256">2256</a>         }
<a name="L2257" href="source/net/ipv4/ipmr.c#L2257">2257</a> 
<a name="L2258" href="source/net/ipv4/ipmr.c#L2258">2258</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L2259" href="source/net/ipv4/ipmr.c#L2259">2259</a>         if (!<a href="ident?i=nowait">nowait</a> &amp;&amp; (rtm-&gt;rtm_flags &amp; <a href="ident?i=RTM_F_NOTIFY">RTM_F_NOTIFY</a>))
<a name="L2260" href="source/net/ipv4/ipmr.c#L2260">2260</a>                 <a href="ident?i=cache">cache</a>-&gt;mfc_flags |= <a href="ident?i=MFC_NOTIFY">MFC_NOTIFY</a>;
<a name="L2261" href="source/net/ipv4/ipmr.c#L2261">2261</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__ipmr_fill_mroute">__ipmr_fill_mroute</a>(mrt, <a href="ident?i=skb">skb</a>, <a href="ident?i=cache">cache</a>, rtm);
<a name="L2262" href="source/net/ipv4/ipmr.c#L2262">2262</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2263" href="source/net/ipv4/ipmr.c#L2263">2263</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2264" href="source/net/ipv4/ipmr.c#L2264">2264</a>         return <a href="ident?i=err">err</a>;
<a name="L2265" href="source/net/ipv4/ipmr.c#L2265">2265</a> }
<a name="L2266" href="source/net/ipv4/ipmr.c#L2266">2266</a> 
<a name="L2267" href="source/net/ipv4/ipmr.c#L2267">2267</a> static int <a href="ident?i=ipmr_fill_mroute">ipmr_fill_mroute</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L2268" href="source/net/ipv4/ipmr.c#L2268">2268</a>                             <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=c">c</a>, int <a href="ident?i=cmd">cmd</a>,
<a name="L2269" href="source/net/ipv4/ipmr.c#L2269">2269</a>                             int <a href="ident?i=flags">flags</a>)
<a name="L2270" href="source/net/ipv4/ipmr.c#L2270">2270</a> {
<a name="L2271" href="source/net/ipv4/ipmr.c#L2271">2271</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh;
<a name="L2272" href="source/net/ipv4/ipmr.c#L2272">2272</a>         struct <a href="ident?i=rtmsg">rtmsg</a> *rtm;
<a name="L2273" href="source/net/ipv4/ipmr.c#L2273">2273</a>         int <a href="ident?i=err">err</a>;
<a name="L2274" href="source/net/ipv4/ipmr.c#L2274">2274</a> 
<a name="L2275" href="source/net/ipv4/ipmr.c#L2275">2275</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=cmd">cmd</a>, sizeof(*rtm), <a href="ident?i=flags">flags</a>);
<a name="L2276" href="source/net/ipv4/ipmr.c#L2276">2276</a>         if (!nlh)
<a name="L2277" href="source/net/ipv4/ipmr.c#L2277">2277</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2278" href="source/net/ipv4/ipmr.c#L2278">2278</a> 
<a name="L2279" href="source/net/ipv4/ipmr.c#L2279">2279</a>         rtm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L2280" href="source/net/ipv4/ipmr.c#L2280">2280</a>         rtm-&gt;rtm_family   = <a href="ident?i=RTNL_FAMILY_IPMR">RTNL_FAMILY_IPMR</a>;
<a name="L2281" href="source/net/ipv4/ipmr.c#L2281">2281</a>         rtm-&gt;rtm_dst_len  = 32;
<a name="L2282" href="source/net/ipv4/ipmr.c#L2282">2282</a>         rtm-&gt;rtm_src_len  = 32;
<a name="L2283" href="source/net/ipv4/ipmr.c#L2283">2283</a>         rtm-&gt;rtm_tos      = 0;
<a name="L2284" href="source/net/ipv4/ipmr.c#L2284">2284</a>         rtm-&gt;rtm_table    = mrt-&gt;<a href="ident?i=id">id</a>;
<a name="L2285" href="source/net/ipv4/ipmr.c#L2285">2285</a>         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_TABLE, mrt-&gt;<a href="ident?i=id">id</a>))
<a name="L2286" href="source/net/ipv4/ipmr.c#L2286">2286</a>                 goto nla_put_failure;
<a name="L2287" href="source/net/ipv4/ipmr.c#L2287">2287</a>         rtm-&gt;rtm_type     = RTN_MULTICAST;
<a name="L2288" href="source/net/ipv4/ipmr.c#L2288">2288</a>         rtm-&gt;rtm_scope    = RT_SCOPE_UNIVERSE;
<a name="L2289" href="source/net/ipv4/ipmr.c#L2289">2289</a>         if (<a href="ident?i=c">c</a>-&gt;mfc_flags &amp; <a href="ident?i=MFC_STATIC">MFC_STATIC</a>)
<a name="L2290" href="source/net/ipv4/ipmr.c#L2290">2290</a>                 rtm-&gt;rtm_protocol = <a href="ident?i=RTPROT_STATIC">RTPROT_STATIC</a>;
<a name="L2291" href="source/net/ipv4/ipmr.c#L2291">2291</a>         else
<a name="L2292" href="source/net/ipv4/ipmr.c#L2292">2292</a>                 rtm-&gt;rtm_protocol = <a href="ident?i=RTPROT_MROUTED">RTPROT_MROUTED</a>;
<a name="L2293" href="source/net/ipv4/ipmr.c#L2293">2293</a>         rtm-&gt;rtm_flags    = 0;
<a name="L2294" href="source/net/ipv4/ipmr.c#L2294">2294</a> 
<a name="L2295" href="source/net/ipv4/ipmr.c#L2295">2295</a>         if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_SRC, <a href="ident?i=c">c</a>-&gt;mfc_origin) ||
<a name="L2296" href="source/net/ipv4/ipmr.c#L2296">2296</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_DST, <a href="ident?i=c">c</a>-&gt;mfc_mcastgrp))
<a name="L2297" href="source/net/ipv4/ipmr.c#L2297">2297</a>                 goto nla_put_failure;
<a name="L2298" href="source/net/ipv4/ipmr.c#L2298">2298</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__ipmr_fill_mroute">__ipmr_fill_mroute</a>(mrt, <a href="ident?i=skb">skb</a>, <a href="ident?i=c">c</a>, rtm);
<a name="L2299" href="source/net/ipv4/ipmr.c#L2299">2299</a>         <b><i>/* do not break the dump if cache is unresolved */</i></b>
<a name="L2300" href="source/net/ipv4/ipmr.c#L2300">2300</a>         if (<a href="ident?i=err">err</a> &lt; 0 &amp;&amp; <a href="ident?i=err">err</a> != -<a href="ident?i=ENOENT">ENOENT</a>)
<a name="L2301" href="source/net/ipv4/ipmr.c#L2301">2301</a>                 goto nla_put_failure;
<a name="L2302" href="source/net/ipv4/ipmr.c#L2302">2302</a> 
<a name="L2303" href="source/net/ipv4/ipmr.c#L2303">2303</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L2304" href="source/net/ipv4/ipmr.c#L2304">2304</a>         return 0;
<a name="L2305" href="source/net/ipv4/ipmr.c#L2305">2305</a> 
<a name="L2306" href="source/net/ipv4/ipmr.c#L2306">2306</a> nla_put_failure:
<a name="L2307" href="source/net/ipv4/ipmr.c#L2307">2307</a>         <a href="ident?i=nlmsg_cancel">nlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L2308" href="source/net/ipv4/ipmr.c#L2308">2308</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2309" href="source/net/ipv4/ipmr.c#L2309">2309</a> }
<a name="L2310" href="source/net/ipv4/ipmr.c#L2310">2310</a> 
<a name="L2311" href="source/net/ipv4/ipmr.c#L2311">2311</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=mroute_msgsize">mroute_msgsize</a>(<a href="ident?i=bool">bool</a> <a href="ident?i=unresolved">unresolved</a>, int maxvif)
<a name="L2312" href="source/net/ipv4/ipmr.c#L2312">2312</a> {
<a name="L2313" href="source/net/ipv4/ipmr.c#L2313">2313</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a> =
<a name="L2314" href="source/net/ipv4/ipmr.c#L2314">2314</a>                 <a href="ident?i=NLMSG_ALIGN">NLMSG_ALIGN</a>(sizeof(struct <a href="ident?i=rtmsg">rtmsg</a>))
<a name="L2315" href="source/net/ipv4/ipmr.c#L2315">2315</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(4)     <b><i>/* RTA_TABLE */</i></b>
<a name="L2316" href="source/net/ipv4/ipmr.c#L2316">2316</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(4)     <b><i>/* RTA_SRC */</i></b>
<a name="L2317" href="source/net/ipv4/ipmr.c#L2317">2317</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(4)     <b><i>/* RTA_DST */</i></b>
<a name="L2318" href="source/net/ipv4/ipmr.c#L2318">2318</a>                 ;
<a name="L2319" href="source/net/ipv4/ipmr.c#L2319">2319</a> 
<a name="L2320" href="source/net/ipv4/ipmr.c#L2320">2320</a>         if (!<a href="ident?i=unresolved">unresolved</a>)
<a name="L2321" href="source/net/ipv4/ipmr.c#L2321">2321</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=len">len</a>
<a name="L2322" href="source/net/ipv4/ipmr.c#L2322">2322</a>                       + <a href="ident?i=nla_total_size">nla_total_size</a>(4)       <b><i>/* RTA_IIF */</i></b>
<a name="L2323" href="source/net/ipv4/ipmr.c#L2323">2323</a>                       + <a href="ident?i=nla_total_size">nla_total_size</a>(0)       <b><i>/* RTA_MULTIPATH */</i></b>
<a name="L2324" href="source/net/ipv4/ipmr.c#L2324">2324</a>                       + maxvif * <a href="ident?i=NLA_ALIGN">NLA_ALIGN</a>(sizeof(struct <a href="ident?i=rtnexthop">rtnexthop</a>))
<a name="L2325" href="source/net/ipv4/ipmr.c#L2325">2325</a>                                                 <b><i>/* RTA_MFC_STATS */</i></b>
<a name="L2326" href="source/net/ipv4/ipmr.c#L2326">2326</a>                       + <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=rta_mfc_stats">rta_mfc_stats</a>))
<a name="L2327" href="source/net/ipv4/ipmr.c#L2327">2327</a>                 ;
<a name="L2328" href="source/net/ipv4/ipmr.c#L2328">2328</a> 
<a name="L2329" href="source/net/ipv4/ipmr.c#L2329">2329</a>         return <a href="ident?i=len">len</a>;
<a name="L2330" href="source/net/ipv4/ipmr.c#L2330">2330</a> }
<a name="L2331" href="source/net/ipv4/ipmr.c#L2331">2331</a> 
<a name="L2332" href="source/net/ipv4/ipmr.c#L2332">2332</a> static void <a href="ident?i=mroute_netlink_event">mroute_netlink_event</a>(struct <a href="ident?i=mr_table">mr_table</a> *mrt, struct <a href="ident?i=mfc_cache">mfc_cache</a> *mfc,
<a name="L2333" href="source/net/ipv4/ipmr.c#L2333">2333</a>                                  int <a href="ident?i=cmd">cmd</a>)
<a name="L2334" href="source/net/ipv4/ipmr.c#L2334">2334</a> {
<a name="L2335" href="source/net/ipv4/ipmr.c#L2335">2335</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=read_pnet">read_pnet</a>(&amp;mrt-&gt;<a href="ident?i=net">net</a>);
<a name="L2336" href="source/net/ipv4/ipmr.c#L2336">2336</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2337" href="source/net/ipv4/ipmr.c#L2337">2337</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2338" href="source/net/ipv4/ipmr.c#L2338">2338</a> 
<a name="L2339" href="source/net/ipv4/ipmr.c#L2339">2339</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=mroute_msgsize">mroute_msgsize</a>(mfc-&gt;mfc_parent &gt;= <a href="ident?i=MAXVIFS">MAXVIFS</a>, mrt-&gt;maxvif),
<a name="L2340" href="source/net/ipv4/ipmr.c#L2340">2340</a>                         <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2341" href="source/net/ipv4/ipmr.c#L2341">2341</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L2342" href="source/net/ipv4/ipmr.c#L2342">2342</a>                 goto errout;
<a name="L2343" href="source/net/ipv4/ipmr.c#L2343">2343</a> 
<a name="L2344" href="source/net/ipv4/ipmr.c#L2344">2344</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_fill_mroute">ipmr_fill_mroute</a>(mrt, <a href="ident?i=skb">skb</a>, 0, 0, mfc, <a href="ident?i=cmd">cmd</a>, 0);
<a name="L2345" href="source/net/ipv4/ipmr.c#L2345">2345</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2346" href="source/net/ipv4/ipmr.c#L2346">2346</a>                 goto errout;
<a name="L2347" href="source/net/ipv4/ipmr.c#L2347">2347</a> 
<a name="L2348" href="source/net/ipv4/ipmr.c#L2348">2348</a>         <a href="ident?i=rtnl_notify">rtnl_notify</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, <a href="ident?i=RTNLGRP_IPV4_MROUTE">RTNLGRP_IPV4_MROUTE</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2349" href="source/net/ipv4/ipmr.c#L2349">2349</a>         return;
<a name="L2350" href="source/net/ipv4/ipmr.c#L2350">2350</a> 
<a name="L2351" href="source/net/ipv4/ipmr.c#L2351">2351</a> errout:
<a name="L2352" href="source/net/ipv4/ipmr.c#L2352">2352</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2353" href="source/net/ipv4/ipmr.c#L2353">2353</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2354" href="source/net/ipv4/ipmr.c#L2354">2354</a>                 <a href="ident?i=rtnl_set_sk_err">rtnl_set_sk_err</a>(<a href="ident?i=net">net</a>, <a href="ident?i=RTNLGRP_IPV4_MROUTE">RTNLGRP_IPV4_MROUTE</a>, <a href="ident?i=err">err</a>);
<a name="L2355" href="source/net/ipv4/ipmr.c#L2355">2355</a> }
<a name="L2356" href="source/net/ipv4/ipmr.c#L2356">2356</a> 
<a name="L2357" href="source/net/ipv4/ipmr.c#L2357">2357</a> static int <a href="ident?i=ipmr_rtm_dumproute">ipmr_rtm_dumproute</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L2358" href="source/net/ipv4/ipmr.c#L2358">2358</a> {
<a name="L2359" href="source/net/ipv4/ipmr.c#L2359">2359</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L2360" href="source/net/ipv4/ipmr.c#L2360">2360</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2361" href="source/net/ipv4/ipmr.c#L2361">2361</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *mfc;
<a name="L2362" href="source/net/ipv4/ipmr.c#L2362">2362</a>         unsigned int <a href="ident?i=t">t</a> = 0, s_t;
<a name="L2363" href="source/net/ipv4/ipmr.c#L2363">2363</a>         unsigned int <a href="ident?i=h">h</a> = 0, s_h;
<a name="L2364" href="source/net/ipv4/ipmr.c#L2364">2364</a>         unsigned int <a href="ident?i=e">e</a> = 0, s_e;
<a name="L2365" href="source/net/ipv4/ipmr.c#L2365">2365</a> 
<a name="L2366" href="source/net/ipv4/ipmr.c#L2366">2366</a>         s_t = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0];
<a name="L2367" href="source/net/ipv4/ipmr.c#L2367">2367</a>         s_h = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1];
<a name="L2368" href="source/net/ipv4/ipmr.c#L2368">2368</a>         s_e = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2];
<a name="L2369" href="source/net/ipv4/ipmr.c#L2369">2369</a> 
<a name="L2370" href="source/net/ipv4/ipmr.c#L2370">2370</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2371" href="source/net/ipv4/ipmr.c#L2371">2371</a>         <a href="ident?i=ipmr_for_each_table">ipmr_for_each_table</a>(mrt, <a href="ident?i=net">net</a>) {
<a name="L2372" href="source/net/ipv4/ipmr.c#L2372">2372</a>                 if (<a href="ident?i=t">t</a> &lt; s_t)
<a name="L2373" href="source/net/ipv4/ipmr.c#L2373">2373</a>                         goto next_table;
<a name="L2374" href="source/net/ipv4/ipmr.c#L2374">2374</a>                 if (<a href="ident?i=t">t</a> &gt; s_t)
<a name="L2375" href="source/net/ipv4/ipmr.c#L2375">2375</a>                         s_h = 0;
<a name="L2376" href="source/net/ipv4/ipmr.c#L2376">2376</a>                 for (<a href="ident?i=h">h</a> = s_h; <a href="ident?i=h">h</a> &lt; <a href="ident?i=MFC_LINES">MFC_LINES</a>; <a href="ident?i=h">h</a>++) {
<a name="L2377" href="source/net/ipv4/ipmr.c#L2377">2377</a>                         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(mfc, &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=h">h</a>], <a href="ident?i=list">list</a>) {
<a name="L2378" href="source/net/ipv4/ipmr.c#L2378">2378</a>                                 if (<a href="ident?i=e">e</a> &lt; s_e)
<a name="L2379" href="source/net/ipv4/ipmr.c#L2379">2379</a>                                         goto <a href="ident?i=next_entry">next_entry</a>;
<a name="L2380" href="source/net/ipv4/ipmr.c#L2380">2380</a>                                 if (<a href="ident?i=ipmr_fill_mroute">ipmr_fill_mroute</a>(mrt, <a href="ident?i=skb">skb</a>,
<a name="L2381" href="source/net/ipv4/ipmr.c#L2381">2381</a>                                                      <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L2382" href="source/net/ipv4/ipmr.c#L2382">2382</a>                                                      <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L2383" href="source/net/ipv4/ipmr.c#L2383">2383</a>                                                      mfc, <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>,
<a name="L2384" href="source/net/ipv4/ipmr.c#L2384">2384</a>                                                      <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>) &lt; 0)
<a name="L2385" href="source/net/ipv4/ipmr.c#L2385">2385</a>                                         goto <a href="ident?i=done">done</a>;
<a name="L2386" href="source/net/ipv4/ipmr.c#L2386">2386</a> <a href="ident?i=next_entry">next_entry</a>:
<a name="L2387" href="source/net/ipv4/ipmr.c#L2387">2387</a>                                 <a href="ident?i=e">e</a>++;
<a name="L2388" href="source/net/ipv4/ipmr.c#L2388">2388</a>                         }
<a name="L2389" href="source/net/ipv4/ipmr.c#L2389">2389</a>                         <a href="ident?i=e">e</a> = s_e = 0;
<a name="L2390" href="source/net/ipv4/ipmr.c#L2390">2390</a>                 }
<a name="L2391" href="source/net/ipv4/ipmr.c#L2391">2391</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;mfc_unres_lock);
<a name="L2392" href="source/net/ipv4/ipmr.c#L2392">2392</a>                 <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(mfc, &amp;mrt-&gt;mfc_unres_queue, <a href="ident?i=list">list</a>) {
<a name="L2393" href="source/net/ipv4/ipmr.c#L2393">2393</a>                         if (<a href="ident?i=e">e</a> &lt; s_e)
<a name="L2394" href="source/net/ipv4/ipmr.c#L2394">2394</a>                                 goto next_entry2;
<a name="L2395" href="source/net/ipv4/ipmr.c#L2395">2395</a>                         if (<a href="ident?i=ipmr_fill_mroute">ipmr_fill_mroute</a>(mrt, <a href="ident?i=skb">skb</a>,
<a name="L2396" href="source/net/ipv4/ipmr.c#L2396">2396</a>                                              <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L2397" href="source/net/ipv4/ipmr.c#L2397">2397</a>                                              <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L2398" href="source/net/ipv4/ipmr.c#L2398">2398</a>                                              mfc, <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>,
<a name="L2399" href="source/net/ipv4/ipmr.c#L2399">2399</a>                                              <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>) &lt; 0) {
<a name="L2400" href="source/net/ipv4/ipmr.c#L2400">2400</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L2401" href="source/net/ipv4/ipmr.c#L2401">2401</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L2402" href="source/net/ipv4/ipmr.c#L2402">2402</a>                         }
<a name="L2403" href="source/net/ipv4/ipmr.c#L2403">2403</a> next_entry2:
<a name="L2404" href="source/net/ipv4/ipmr.c#L2404">2404</a>                         <a href="ident?i=e">e</a>++;
<a name="L2405" href="source/net/ipv4/ipmr.c#L2405">2405</a>                 }
<a name="L2406" href="source/net/ipv4/ipmr.c#L2406">2406</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L2407" href="source/net/ipv4/ipmr.c#L2407">2407</a>                 <a href="ident?i=e">e</a> = s_e = 0;
<a name="L2408" href="source/net/ipv4/ipmr.c#L2408">2408</a>                 s_h = 0;
<a name="L2409" href="source/net/ipv4/ipmr.c#L2409">2409</a> next_table:
<a name="L2410" href="source/net/ipv4/ipmr.c#L2410">2410</a>                 <a href="ident?i=t">t</a>++;
<a name="L2411" href="source/net/ipv4/ipmr.c#L2411">2411</a>         }
<a name="L2412" href="source/net/ipv4/ipmr.c#L2412">2412</a> <a href="ident?i=done">done</a>:
<a name="L2413" href="source/net/ipv4/ipmr.c#L2413">2413</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2414" href="source/net/ipv4/ipmr.c#L2414">2414</a> 
<a name="L2415" href="source/net/ipv4/ipmr.c#L2415">2415</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2] = <a href="ident?i=e">e</a>;
<a name="L2416" href="source/net/ipv4/ipmr.c#L2416">2416</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = <a href="ident?i=h">h</a>;
<a name="L2417" href="source/net/ipv4/ipmr.c#L2417">2417</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = <a href="ident?i=t">t</a>;
<a name="L2418" href="source/net/ipv4/ipmr.c#L2418">2418</a> 
<a name="L2419" href="source/net/ipv4/ipmr.c#L2419">2419</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L2420" href="source/net/ipv4/ipmr.c#L2420">2420</a> }
<a name="L2421" href="source/net/ipv4/ipmr.c#L2421">2421</a> 
<a name="L2422" href="source/net/ipv4/ipmr.c#L2422">2422</a> #ifdef CONFIG_PROC_FS
<a name="L2423" href="source/net/ipv4/ipmr.c#L2423">2423</a> <b><i>/*</i></b>
<a name="L2424" href="source/net/ipv4/ipmr.c#L2424">2424</a> <b><i> *      The /proc interfaces to multicast routing :</i></b>
<a name="L2425" href="source/net/ipv4/ipmr.c#L2425">2425</a> <b><i> *      /proc/net/ip_mr_cache &amp; /proc/net/ip_mr_vif</i></b>
<a name="L2426" href="source/net/ipv4/ipmr.c#L2426">2426</a> <b><i> */</i></b>
<a name="L2427" href="source/net/ipv4/ipmr.c#L2427">2427</a> struct <a href="ident?i=ipmr_vif_iter">ipmr_vif_iter</a> {
<a name="L2428" href="source/net/ipv4/ipmr.c#L2428">2428</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L2429" href="source/net/ipv4/ipmr.c#L2429">2429</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2430" href="source/net/ipv4/ipmr.c#L2430">2430</a>         int ct;
<a name="L2431" href="source/net/ipv4/ipmr.c#L2431">2431</a> };
<a name="L2432" href="source/net/ipv4/ipmr.c#L2432">2432</a> 
<a name="L2433" href="source/net/ipv4/ipmr.c#L2433">2433</a> static struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=ipmr_vif_seq_idx">ipmr_vif_seq_idx</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L2434" href="source/net/ipv4/ipmr.c#L2434">2434</a>                                            struct <a href="ident?i=ipmr_vif_iter">ipmr_vif_iter</a> *iter,
<a name="L2435" href="source/net/ipv4/ipmr.c#L2435">2435</a>                                            <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2436" href="source/net/ipv4/ipmr.c#L2436">2436</a> {
<a name="L2437" href="source/net/ipv4/ipmr.c#L2437">2437</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = iter-&gt;mrt;
<a name="L2438" href="source/net/ipv4/ipmr.c#L2438">2438</a> 
<a name="L2439" href="source/net/ipv4/ipmr.c#L2439">2439</a>         for (iter-&gt;ct = 0; iter-&gt;ct &lt; mrt-&gt;maxvif; ++iter-&gt;ct) {
<a name="L2440" href="source/net/ipv4/ipmr.c#L2440">2440</a>                 if (!<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, iter-&gt;ct))
<a name="L2441" href="source/net/ipv4/ipmr.c#L2441">2441</a>                         continue;
<a name="L2442" href="source/net/ipv4/ipmr.c#L2442">2442</a>                 if (<a href="ident?i=pos">pos</a>-- == 0)
<a name="L2443" href="source/net/ipv4/ipmr.c#L2443">2443</a>                         return &amp;mrt-&gt;vif_table[iter-&gt;ct];
<a name="L2444" href="source/net/ipv4/ipmr.c#L2444">2444</a>         }
<a name="L2445" href="source/net/ipv4/ipmr.c#L2445">2445</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2446" href="source/net/ipv4/ipmr.c#L2446">2446</a> }
<a name="L2447" href="source/net/ipv4/ipmr.c#L2447">2447</a> 
<a name="L2448" href="source/net/ipv4/ipmr.c#L2448">2448</a> static void *ipmr_vif_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2449" href="source/net/ipv4/ipmr.c#L2449">2449</a>         <a href="ident?i=__acquires">__acquires</a>(mrt_lock)
<a name="L2450" href="source/net/ipv4/ipmr.c#L2450">2450</a> {
<a name="L2451" href="source/net/ipv4/ipmr.c#L2451">2451</a>         struct <a href="ident?i=ipmr_vif_iter">ipmr_vif_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2452" href="source/net/ipv4/ipmr.c#L2452">2452</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2453" href="source/net/ipv4/ipmr.c#L2453">2453</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2454" href="source/net/ipv4/ipmr.c#L2454">2454</a> 
<a name="L2455" href="source/net/ipv4/ipmr.c#L2455">2455</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_DEFAULT);
<a name="L2456" href="source/net/ipv4/ipmr.c#L2456">2456</a>         if (!mrt)
<a name="L2457" href="source/net/ipv4/ipmr.c#L2457">2457</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOENT">ENOENT</a>);
<a name="L2458" href="source/net/ipv4/ipmr.c#L2458">2458</a> 
<a name="L2459" href="source/net/ipv4/ipmr.c#L2459">2459</a>         iter-&gt;mrt = mrt;
<a name="L2460" href="source/net/ipv4/ipmr.c#L2460">2460</a> 
<a name="L2461" href="source/net/ipv4/ipmr.c#L2461">2461</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;mrt_lock);
<a name="L2462" href="source/net/ipv4/ipmr.c#L2462">2462</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=ipmr_vif_seq_idx">ipmr_vif_seq_idx</a>(<a href="ident?i=net">net</a>, <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>, *<a href="ident?i=pos">pos</a> - 1)
<a name="L2463" href="source/net/ipv4/ipmr.c#L2463">2463</a>                 : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2464" href="source/net/ipv4/ipmr.c#L2464">2464</a> }
<a name="L2465" href="source/net/ipv4/ipmr.c#L2465">2465</a> 
<a name="L2466" href="source/net/ipv4/ipmr.c#L2466">2466</a> static void *<a href="ident?i=ipmr_vif_seq_next">ipmr_vif_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2467" href="source/net/ipv4/ipmr.c#L2467">2467</a> {
<a name="L2468" href="source/net/ipv4/ipmr.c#L2468">2468</a>         struct <a href="ident?i=ipmr_vif_iter">ipmr_vif_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2469" href="source/net/ipv4/ipmr.c#L2469">2469</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2470" href="source/net/ipv4/ipmr.c#L2470">2470</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = iter-&gt;mrt;
<a name="L2471" href="source/net/ipv4/ipmr.c#L2471">2471</a> 
<a name="L2472" href="source/net/ipv4/ipmr.c#L2472">2472</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2473" href="source/net/ipv4/ipmr.c#L2473">2473</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2474" href="source/net/ipv4/ipmr.c#L2474">2474</a>                 return <a href="ident?i=ipmr_vif_seq_idx">ipmr_vif_seq_idx</a>(<a href="ident?i=net">net</a>, iter, 0);
<a name="L2475" href="source/net/ipv4/ipmr.c#L2475">2475</a> 
<a name="L2476" href="source/net/ipv4/ipmr.c#L2476">2476</a>         while (++iter-&gt;ct &lt; mrt-&gt;maxvif) {
<a name="L2477" href="source/net/ipv4/ipmr.c#L2477">2477</a>                 if (!<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, iter-&gt;ct))
<a name="L2478" href="source/net/ipv4/ipmr.c#L2478">2478</a>                         continue;
<a name="L2479" href="source/net/ipv4/ipmr.c#L2479">2479</a>                 return &amp;mrt-&gt;vif_table[iter-&gt;ct];
<a name="L2480" href="source/net/ipv4/ipmr.c#L2480">2480</a>         }
<a name="L2481" href="source/net/ipv4/ipmr.c#L2481">2481</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2482" href="source/net/ipv4/ipmr.c#L2482">2482</a> }
<a name="L2483" href="source/net/ipv4/ipmr.c#L2483">2483</a> 
<a name="L2484" href="source/net/ipv4/ipmr.c#L2484">2484</a> static void ipmr_vif_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2485" href="source/net/ipv4/ipmr.c#L2485">2485</a>         <a href="ident?i=__releases">__releases</a>(mrt_lock)
<a name="L2486" href="source/net/ipv4/ipmr.c#L2486">2486</a> {
<a name="L2487" href="source/net/ipv4/ipmr.c#L2487">2487</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;mrt_lock);
<a name="L2488" href="source/net/ipv4/ipmr.c#L2488">2488</a> }
<a name="L2489" href="source/net/ipv4/ipmr.c#L2489">2489</a> 
<a name="L2490" href="source/net/ipv4/ipmr.c#L2490">2490</a> static int <a href="ident?i=ipmr_vif_seq_show">ipmr_vif_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2491" href="source/net/ipv4/ipmr.c#L2491">2491</a> {
<a name="L2492" href="source/net/ipv4/ipmr.c#L2492">2492</a>         struct <a href="ident?i=ipmr_vif_iter">ipmr_vif_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2493" href="source/net/ipv4/ipmr.c#L2493">2493</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = iter-&gt;mrt;
<a name="L2494" href="source/net/ipv4/ipmr.c#L2494">2494</a> 
<a name="L2495" href="source/net/ipv4/ipmr.c#L2495">2495</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L2496" href="source/net/ipv4/ipmr.c#L2496">2496</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>,
<a name="L2497" href="source/net/ipv4/ipmr.c#L2497">2497</a>                          <i>"Interface      BytesIn  PktsIn  BytesOut PktsOut Flags Local    Remote\n"</i>);
<a name="L2498" href="source/net/ipv4/ipmr.c#L2498">2498</a>         } else {
<a name="L2499" href="source/net/ipv4/ipmr.c#L2499">2499</a>                 const struct <a href="ident?i=vif_device">vif_device</a> *<a href="ident?i=vif">vif</a> = <a href="ident?i=v">v</a>;
<a name="L2500" href="source/net/ipv4/ipmr.c#L2500">2500</a>                 const char *<a href="ident?i=name">name</a> =  <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a> ? <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a> : <i>"none"</i>;
<a name="L2501" href="source/net/ipv4/ipmr.c#L2501">2501</a> 
<a name="L2502" href="source/net/ipv4/ipmr.c#L2502">2502</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2503" href="source/net/ipv4/ipmr.c#L2503">2503</a>                            <i>"%2Zd %-10s %8ld %7ld  %8ld %7ld %05X %08X %08X\n"</i>,
<a name="L2504" href="source/net/ipv4/ipmr.c#L2504">2504</a>                            <a href="ident?i=vif">vif</a> - mrt-&gt;vif_table,
<a name="L2505" href="source/net/ipv4/ipmr.c#L2505">2505</a>                            <a href="ident?i=name">name</a>, <a href="ident?i=vif">vif</a>-&gt;bytes_in, <a href="ident?i=vif">vif</a>-&gt;pkt_in,
<a name="L2506" href="source/net/ipv4/ipmr.c#L2506">2506</a>                            <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=bytes_out">bytes_out</a>, <a href="ident?i=vif">vif</a>-&gt;pkt_out,
<a name="L2507" href="source/net/ipv4/ipmr.c#L2507">2507</a>                            <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=flags">flags</a>, <a href="ident?i=vif">vif</a>-&gt;local, <a href="ident?i=vif">vif</a>-&gt;<a href="ident?i=remote">remote</a>);
<a name="L2508" href="source/net/ipv4/ipmr.c#L2508">2508</a>         }
<a name="L2509" href="source/net/ipv4/ipmr.c#L2509">2509</a>         return 0;
<a name="L2510" href="source/net/ipv4/ipmr.c#L2510">2510</a> }
<a name="L2511" href="source/net/ipv4/ipmr.c#L2511">2511</a> 
<a name="L2512" href="source/net/ipv4/ipmr.c#L2512">2512</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=ipmr_vif_seq_ops">ipmr_vif_seq_ops</a> = {
<a name="L2513" href="source/net/ipv4/ipmr.c#L2513">2513</a>         .<a href="ident?i=start">start</a> = ipmr_vif_seq_start,
<a name="L2514" href="source/net/ipv4/ipmr.c#L2514">2514</a>         .<a href="ident?i=next">next</a>  = <a href="ident?i=ipmr_vif_seq_next">ipmr_vif_seq_next</a>,
<a name="L2515" href="source/net/ipv4/ipmr.c#L2515">2515</a>         .<a href="ident?i=stop">stop</a>  = ipmr_vif_seq_stop,
<a name="L2516" href="source/net/ipv4/ipmr.c#L2516">2516</a>         .<a href="ident?i=show">show</a>  = <a href="ident?i=ipmr_vif_seq_show">ipmr_vif_seq_show</a>,
<a name="L2517" href="source/net/ipv4/ipmr.c#L2517">2517</a> };
<a name="L2518" href="source/net/ipv4/ipmr.c#L2518">2518</a> 
<a name="L2519" href="source/net/ipv4/ipmr.c#L2519">2519</a> static int <a href="ident?i=ipmr_vif_open">ipmr_vif_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2520" href="source/net/ipv4/ipmr.c#L2520">2520</a> {
<a name="L2521" href="source/net/ipv4/ipmr.c#L2521">2521</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=ipmr_vif_seq_ops">ipmr_vif_seq_ops</a>,
<a name="L2522" href="source/net/ipv4/ipmr.c#L2522">2522</a>                             sizeof(struct <a href="ident?i=ipmr_vif_iter">ipmr_vif_iter</a>));
<a name="L2523" href="source/net/ipv4/ipmr.c#L2523">2523</a> }
<a name="L2524" href="source/net/ipv4/ipmr.c#L2524">2524</a> 
<a name="L2525" href="source/net/ipv4/ipmr.c#L2525">2525</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=ipmr_vif_fops">ipmr_vif_fops</a> = {
<a name="L2526" href="source/net/ipv4/ipmr.c#L2526">2526</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2527" href="source/net/ipv4/ipmr.c#L2527">2527</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=ipmr_vif_open">ipmr_vif_open</a>,
<a name="L2528" href="source/net/ipv4/ipmr.c#L2528">2528</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2529" href="source/net/ipv4/ipmr.c#L2529">2529</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2530" href="source/net/ipv4/ipmr.c#L2530">2530</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L2531" href="source/net/ipv4/ipmr.c#L2531">2531</a> };
<a name="L2532" href="source/net/ipv4/ipmr.c#L2532">2532</a> 
<a name="L2533" href="source/net/ipv4/ipmr.c#L2533">2533</a> struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a> {
<a name="L2534" href="source/net/ipv4/ipmr.c#L2534">2534</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L2535" href="source/net/ipv4/ipmr.c#L2535">2535</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2536" href="source/net/ipv4/ipmr.c#L2536">2536</a>         struct <a href="ident?i=list_head">list_head</a> *<a href="ident?i=cache">cache</a>;
<a name="L2537" href="source/net/ipv4/ipmr.c#L2537">2537</a>         int ct;
<a name="L2538" href="source/net/ipv4/ipmr.c#L2538">2538</a> };
<a name="L2539" href="source/net/ipv4/ipmr.c#L2539">2539</a> 
<a name="L2540" href="source/net/ipv4/ipmr.c#L2540">2540</a> 
<a name="L2541" href="source/net/ipv4/ipmr.c#L2541">2541</a> static struct <a href="ident?i=mfc_cache">mfc_cache</a> *<a href="ident?i=ipmr_mfc_seq_idx">ipmr_mfc_seq_idx</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L2542" href="source/net/ipv4/ipmr.c#L2542">2542</a>                                           struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a> *<a href="ident?i=it">it</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2543" href="source/net/ipv4/ipmr.c#L2543">2543</a> {
<a name="L2544" href="source/net/ipv4/ipmr.c#L2544">2544</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = <a href="ident?i=it">it</a>-&gt;mrt;
<a name="L2545" href="source/net/ipv4/ipmr.c#L2545">2545</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *mfc;
<a name="L2546" href="source/net/ipv4/ipmr.c#L2546">2546</a> 
<a name="L2547" href="source/net/ipv4/ipmr.c#L2547">2547</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2548" href="source/net/ipv4/ipmr.c#L2548">2548</a>         for (<a href="ident?i=it">it</a>-&gt;ct = 0; <a href="ident?i=it">it</a>-&gt;ct &lt; <a href="ident?i=MFC_LINES">MFC_LINES</a>; <a href="ident?i=it">it</a>-&gt;ct++) {
<a name="L2549" href="source/net/ipv4/ipmr.c#L2549">2549</a>                 <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=it">it</a>-&gt;ct];
<a name="L2550" href="source/net/ipv4/ipmr.c#L2550">2550</a>                 <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(mfc, <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>, <a href="ident?i=list">list</a>)
<a name="L2551" href="source/net/ipv4/ipmr.c#L2551">2551</a>                         if (<a href="ident?i=pos">pos</a>-- == 0)
<a name="L2552" href="source/net/ipv4/ipmr.c#L2552">2552</a>                                 return mfc;
<a name="L2553" href="source/net/ipv4/ipmr.c#L2553">2553</a>         }
<a name="L2554" href="source/net/ipv4/ipmr.c#L2554">2554</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2555" href="source/net/ipv4/ipmr.c#L2555">2555</a> 
<a name="L2556" href="source/net/ipv4/ipmr.c#L2556">2556</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;mfc_unres_lock);
<a name="L2557" href="source/net/ipv4/ipmr.c#L2557">2557</a>         <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = &amp;mrt-&gt;mfc_unres_queue;
<a name="L2558" href="source/net/ipv4/ipmr.c#L2558">2558</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(mfc, <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>, <a href="ident?i=list">list</a>)
<a name="L2559" href="source/net/ipv4/ipmr.c#L2559">2559</a>                 if (<a href="ident?i=pos">pos</a>-- == 0)
<a name="L2560" href="source/net/ipv4/ipmr.c#L2560">2560</a>                         return mfc;
<a name="L2561" href="source/net/ipv4/ipmr.c#L2561">2561</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L2562" href="source/net/ipv4/ipmr.c#L2562">2562</a> 
<a name="L2563" href="source/net/ipv4/ipmr.c#L2563">2563</a>         <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2564" href="source/net/ipv4/ipmr.c#L2564">2564</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2565" href="source/net/ipv4/ipmr.c#L2565">2565</a> }
<a name="L2566" href="source/net/ipv4/ipmr.c#L2566">2566</a> 
<a name="L2567" href="source/net/ipv4/ipmr.c#L2567">2567</a> 
<a name="L2568" href="source/net/ipv4/ipmr.c#L2568">2568</a> static void *<a href="ident?i=ipmr_mfc_seq_start">ipmr_mfc_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2569" href="source/net/ipv4/ipmr.c#L2569">2569</a> {
<a name="L2570" href="source/net/ipv4/ipmr.c#L2570">2570</a>         struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a> *<a href="ident?i=it">it</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2571" href="source/net/ipv4/ipmr.c#L2571">2571</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2572" href="source/net/ipv4/ipmr.c#L2572">2572</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt;
<a name="L2573" href="source/net/ipv4/ipmr.c#L2573">2573</a> 
<a name="L2574" href="source/net/ipv4/ipmr.c#L2574">2574</a>         mrt = <a href="ident?i=ipmr_get_table">ipmr_get_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_DEFAULT);
<a name="L2575" href="source/net/ipv4/ipmr.c#L2575">2575</a>         if (!mrt)
<a name="L2576" href="source/net/ipv4/ipmr.c#L2576">2576</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOENT">ENOENT</a>);
<a name="L2577" href="source/net/ipv4/ipmr.c#L2577">2577</a> 
<a name="L2578" href="source/net/ipv4/ipmr.c#L2578">2578</a>         <a href="ident?i=it">it</a>-&gt;mrt = mrt;
<a name="L2579" href="source/net/ipv4/ipmr.c#L2579">2579</a>         <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2580" href="source/net/ipv4/ipmr.c#L2580">2580</a>         <a href="ident?i=it">it</a>-&gt;ct = 0;
<a name="L2581" href="source/net/ipv4/ipmr.c#L2581">2581</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=ipmr_mfc_seq_idx">ipmr_mfc_seq_idx</a>(<a href="ident?i=net">net</a>, <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>, *<a href="ident?i=pos">pos</a> - 1)
<a name="L2582" href="source/net/ipv4/ipmr.c#L2582">2582</a>                 : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2583" href="source/net/ipv4/ipmr.c#L2583">2583</a> }
<a name="L2584" href="source/net/ipv4/ipmr.c#L2584">2584</a> 
<a name="L2585" href="source/net/ipv4/ipmr.c#L2585">2585</a> static void *<a href="ident?i=ipmr_mfc_seq_next">ipmr_mfc_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2586" href="source/net/ipv4/ipmr.c#L2586">2586</a> {
<a name="L2587" href="source/net/ipv4/ipmr.c#L2587">2587</a>         struct <a href="ident?i=mfc_cache">mfc_cache</a> *mfc = <a href="ident?i=v">v</a>;
<a name="L2588" href="source/net/ipv4/ipmr.c#L2588">2588</a>         struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a> *<a href="ident?i=it">it</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2589" href="source/net/ipv4/ipmr.c#L2589">2589</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2590" href="source/net/ipv4/ipmr.c#L2590">2590</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = <a href="ident?i=it">it</a>-&gt;mrt;
<a name="L2591" href="source/net/ipv4/ipmr.c#L2591">2591</a> 
<a name="L2592" href="source/net/ipv4/ipmr.c#L2592">2592</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2593" href="source/net/ipv4/ipmr.c#L2593">2593</a> 
<a name="L2594" href="source/net/ipv4/ipmr.c#L2594">2594</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2595" href="source/net/ipv4/ipmr.c#L2595">2595</a>                 return <a href="ident?i=ipmr_mfc_seq_idx">ipmr_mfc_seq_idx</a>(<a href="ident?i=net">net</a>, <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>, 0);
<a name="L2596" href="source/net/ipv4/ipmr.c#L2596">2596</a> 
<a name="L2597" href="source/net/ipv4/ipmr.c#L2597">2597</a>         if (mfc-&gt;<a href="ident?i=list">list</a>.<a href="ident?i=next">next</a> != <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>)
<a name="L2598" href="source/net/ipv4/ipmr.c#L2598">2598</a>                 return <a href="ident?i=list_entry">list_entry</a>(mfc-&gt;<a href="ident?i=list">list</a>.<a href="ident?i=next">next</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a>, <a href="ident?i=list">list</a>);
<a name="L2599" href="source/net/ipv4/ipmr.c#L2599">2599</a> 
<a name="L2600" href="source/net/ipv4/ipmr.c#L2600">2600</a>         if (<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> == &amp;mrt-&gt;mfc_unres_queue)
<a name="L2601" href="source/net/ipv4/ipmr.c#L2601">2601</a>                 goto end_of_list;
<a name="L2602" href="source/net/ipv4/ipmr.c#L2602">2602</a> 
<a name="L2603" href="source/net/ipv4/ipmr.c#L2603">2603</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> != &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=it">it</a>-&gt;ct]);
<a name="L2604" href="source/net/ipv4/ipmr.c#L2604">2604</a> 
<a name="L2605" href="source/net/ipv4/ipmr.c#L2605">2605</a>         while (++<a href="ident?i=it">it</a>-&gt;ct &lt; <a href="ident?i=MFC_LINES">MFC_LINES</a>) {
<a name="L2606" href="source/net/ipv4/ipmr.c#L2606">2606</a>                 <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=it">it</a>-&gt;ct];
<a name="L2607" href="source/net/ipv4/ipmr.c#L2607">2607</a>                 if (<a href="ident?i=list_empty">list_empty</a>(<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>))
<a name="L2608" href="source/net/ipv4/ipmr.c#L2608">2608</a>                         continue;
<a name="L2609" href="source/net/ipv4/ipmr.c#L2609">2609</a>                 return <a href="ident?i=list_first_entry">list_first_entry</a>(<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a>, <a href="ident?i=list">list</a>);
<a name="L2610" href="source/net/ipv4/ipmr.c#L2610">2610</a>         }
<a name="L2611" href="source/net/ipv4/ipmr.c#L2611">2611</a> 
<a name="L2612" href="source/net/ipv4/ipmr.c#L2612">2612</a>         <b><i>/* exhausted cache_array, show unresolved */</i></b>
<a name="L2613" href="source/net/ipv4/ipmr.c#L2613">2613</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2614" href="source/net/ipv4/ipmr.c#L2614">2614</a>         <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = &amp;mrt-&gt;mfc_unres_queue;
<a name="L2615" href="source/net/ipv4/ipmr.c#L2615">2615</a>         <a href="ident?i=it">it</a>-&gt;ct = 0;
<a name="L2616" href="source/net/ipv4/ipmr.c#L2616">2616</a> 
<a name="L2617" href="source/net/ipv4/ipmr.c#L2617">2617</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;mfc_unres_lock);
<a name="L2618" href="source/net/ipv4/ipmr.c#L2618">2618</a>         if (!<a href="ident?i=list_empty">list_empty</a>(<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>))
<a name="L2619" href="source/net/ipv4/ipmr.c#L2619">2619</a>                 return <a href="ident?i=list_first_entry">list_first_entry</a>(<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a>, struct <a href="ident?i=mfc_cache">mfc_cache</a>, <a href="ident?i=list">list</a>);
<a name="L2620" href="source/net/ipv4/ipmr.c#L2620">2620</a> 
<a name="L2621" href="source/net/ipv4/ipmr.c#L2621">2621</a> end_of_list:
<a name="L2622" href="source/net/ipv4/ipmr.c#L2622">2622</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L2623" href="source/net/ipv4/ipmr.c#L2623">2623</a>         <a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2624" href="source/net/ipv4/ipmr.c#L2624">2624</a> 
<a name="L2625" href="source/net/ipv4/ipmr.c#L2625">2625</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2626" href="source/net/ipv4/ipmr.c#L2626">2626</a> }
<a name="L2627" href="source/net/ipv4/ipmr.c#L2627">2627</a> 
<a name="L2628" href="source/net/ipv4/ipmr.c#L2628">2628</a> static void <a href="ident?i=ipmr_mfc_seq_stop">ipmr_mfc_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2629" href="source/net/ipv4/ipmr.c#L2629">2629</a> {
<a name="L2630" href="source/net/ipv4/ipmr.c#L2630">2630</a>         struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a> *<a href="ident?i=it">it</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2631" href="source/net/ipv4/ipmr.c#L2631">2631</a>         struct <a href="ident?i=mr_table">mr_table</a> *mrt = <a href="ident?i=it">it</a>-&gt;mrt;
<a name="L2632" href="source/net/ipv4/ipmr.c#L2632">2632</a> 
<a name="L2633" href="source/net/ipv4/ipmr.c#L2633">2633</a>         if (<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> == &amp;mrt-&gt;mfc_unres_queue)
<a name="L2634" href="source/net/ipv4/ipmr.c#L2634">2634</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;mfc_unres_lock);
<a name="L2635" href="source/net/ipv4/ipmr.c#L2635">2635</a>         else if (<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> == &amp;mrt-&gt;mfc_cache_array[<a href="ident?i=it">it</a>-&gt;ct])
<a name="L2636" href="source/net/ipv4/ipmr.c#L2636">2636</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2637" href="source/net/ipv4/ipmr.c#L2637">2637</a> }
<a name="L2638" href="source/net/ipv4/ipmr.c#L2638">2638</a> 
<a name="L2639" href="source/net/ipv4/ipmr.c#L2639">2639</a> static int <a href="ident?i=ipmr_mfc_seq_show">ipmr_mfc_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2640" href="source/net/ipv4/ipmr.c#L2640">2640</a> {
<a name="L2641" href="source/net/ipv4/ipmr.c#L2641">2641</a>         int <a href="ident?i=n">n</a>;
<a name="L2642" href="source/net/ipv4/ipmr.c#L2642">2642</a> 
<a name="L2643" href="source/net/ipv4/ipmr.c#L2643">2643</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L2644" href="source/net/ipv4/ipmr.c#L2644">2644</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>,
<a name="L2645" href="source/net/ipv4/ipmr.c#L2645">2645</a>                  <i>"Group    Origin   Iif     Pkts    Bytes    Wrong Oifs\n"</i>);
<a name="L2646" href="source/net/ipv4/ipmr.c#L2646">2646</a>         } else {
<a name="L2647" href="source/net/ipv4/ipmr.c#L2647">2647</a>                 const struct <a href="ident?i=mfc_cache">mfc_cache</a> *mfc = <a href="ident?i=v">v</a>;
<a name="L2648" href="source/net/ipv4/ipmr.c#L2648">2648</a>                 const struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a> *<a href="ident?i=it">it</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2649" href="source/net/ipv4/ipmr.c#L2649">2649</a>                 const struct <a href="ident?i=mr_table">mr_table</a> *mrt = <a href="ident?i=it">it</a>-&gt;mrt;
<a name="L2650" href="source/net/ipv4/ipmr.c#L2650">2650</a> 
<a name="L2651" href="source/net/ipv4/ipmr.c#L2651">2651</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%08X %08X %-3hd"</i>,
<a name="L2652" href="source/net/ipv4/ipmr.c#L2652">2652</a>                            (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>) mfc-&gt;mfc_mcastgrp,
<a name="L2653" href="source/net/ipv4/ipmr.c#L2653">2653</a>                            (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>) mfc-&gt;mfc_origin,
<a name="L2654" href="source/net/ipv4/ipmr.c#L2654">2654</a>                            mfc-&gt;mfc_parent);
<a name="L2655" href="source/net/ipv4/ipmr.c#L2655">2655</a> 
<a name="L2656" href="source/net/ipv4/ipmr.c#L2656">2656</a>                 if (<a href="ident?i=it">it</a>-&gt;<a href="ident?i=cache">cache</a> != &amp;mrt-&gt;mfc_unres_queue) {
<a name="L2657" href="source/net/ipv4/ipmr.c#L2657">2657</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %8lu %8lu %8lu"</i>,
<a name="L2658" href="source/net/ipv4/ipmr.c#L2658">2658</a>                                    mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=pkt">pkt</a>,
<a name="L2659" href="source/net/ipv4/ipmr.c#L2659">2659</a>                                    mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.<a href="ident?i=bytes">bytes</a>,
<a name="L2660" href="source/net/ipv4/ipmr.c#L2660">2660</a>                                    mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.wrong_if);
<a name="L2661" href="source/net/ipv4/ipmr.c#L2661">2661</a>                         for (<a href="ident?i=n">n</a> = mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.minvif;
<a name="L2662" href="source/net/ipv4/ipmr.c#L2662">2662</a>                              <a href="ident?i=n">n</a> &lt; mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.maxvif; <a href="ident?i=n">n</a>++) {
<a name="L2663" href="source/net/ipv4/ipmr.c#L2663">2663</a>                                 if (<a href="ident?i=VIF_EXISTS">VIF_EXISTS</a>(mrt, <a href="ident?i=n">n</a>) &amp;&amp;
<a name="L2664" href="source/net/ipv4/ipmr.c#L2664">2664</a>                                     mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[<a href="ident?i=n">n</a>] &lt; 255)
<a name="L2665" href="source/net/ipv4/ipmr.c#L2665">2665</a>                                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2666" href="source/net/ipv4/ipmr.c#L2666">2666</a>                                            <i>" %2d:%-3d"</i>,
<a name="L2667" href="source/net/ipv4/ipmr.c#L2667">2667</a>                                            <a href="ident?i=n">n</a>, mfc-&gt;mfc_un.<a href="ident?i=res">res</a>.ttls[<a href="ident?i=n">n</a>]);
<a name="L2668" href="source/net/ipv4/ipmr.c#L2668">2668</a>                         }
<a name="L2669" href="source/net/ipv4/ipmr.c#L2669">2669</a>                 } else {
<a name="L2670" href="source/net/ipv4/ipmr.c#L2670">2670</a>                         <b><i>/* unresolved mfc_caches don't contain</i></b>
<a name="L2671" href="source/net/ipv4/ipmr.c#L2671">2671</a> <b><i>                         * pkt, bytes and wrong_if values</i></b>
<a name="L2672" href="source/net/ipv4/ipmr.c#L2672">2672</a> <b><i>                         */</i></b>
<a name="L2673" href="source/net/ipv4/ipmr.c#L2673">2673</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %8lu %8lu %8lu"</i>, 0ul, 0ul, 0ul);
<a name="L2674" href="source/net/ipv4/ipmr.c#L2674">2674</a>                 }
<a name="L2675" href="source/net/ipv4/ipmr.c#L2675">2675</a>                 <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L2676" href="source/net/ipv4/ipmr.c#L2676">2676</a>         }
<a name="L2677" href="source/net/ipv4/ipmr.c#L2677">2677</a>         return 0;
<a name="L2678" href="source/net/ipv4/ipmr.c#L2678">2678</a> }
<a name="L2679" href="source/net/ipv4/ipmr.c#L2679">2679</a> 
<a name="L2680" href="source/net/ipv4/ipmr.c#L2680">2680</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=ipmr_mfc_seq_ops">ipmr_mfc_seq_ops</a> = {
<a name="L2681" href="source/net/ipv4/ipmr.c#L2681">2681</a>         .<a href="ident?i=start">start</a> = <a href="ident?i=ipmr_mfc_seq_start">ipmr_mfc_seq_start</a>,
<a name="L2682" href="source/net/ipv4/ipmr.c#L2682">2682</a>         .<a href="ident?i=next">next</a>  = <a href="ident?i=ipmr_mfc_seq_next">ipmr_mfc_seq_next</a>,
<a name="L2683" href="source/net/ipv4/ipmr.c#L2683">2683</a>         .<a href="ident?i=stop">stop</a>  = <a href="ident?i=ipmr_mfc_seq_stop">ipmr_mfc_seq_stop</a>,
<a name="L2684" href="source/net/ipv4/ipmr.c#L2684">2684</a>         .<a href="ident?i=show">show</a>  = <a href="ident?i=ipmr_mfc_seq_show">ipmr_mfc_seq_show</a>,
<a name="L2685" href="source/net/ipv4/ipmr.c#L2685">2685</a> };
<a name="L2686" href="source/net/ipv4/ipmr.c#L2686">2686</a> 
<a name="L2687" href="source/net/ipv4/ipmr.c#L2687">2687</a> static int <a href="ident?i=ipmr_mfc_open">ipmr_mfc_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2688" href="source/net/ipv4/ipmr.c#L2688">2688</a> {
<a name="L2689" href="source/net/ipv4/ipmr.c#L2689">2689</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=ipmr_mfc_seq_ops">ipmr_mfc_seq_ops</a>,
<a name="L2690" href="source/net/ipv4/ipmr.c#L2690">2690</a>                             sizeof(struct <a href="ident?i=ipmr_mfc_iter">ipmr_mfc_iter</a>));
<a name="L2691" href="source/net/ipv4/ipmr.c#L2691">2691</a> }
<a name="L2692" href="source/net/ipv4/ipmr.c#L2692">2692</a> 
<a name="L2693" href="source/net/ipv4/ipmr.c#L2693">2693</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=ipmr_mfc_fops">ipmr_mfc_fops</a> = {
<a name="L2694" href="source/net/ipv4/ipmr.c#L2694">2694</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2695" href="source/net/ipv4/ipmr.c#L2695">2695</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=ipmr_mfc_open">ipmr_mfc_open</a>,
<a name="L2696" href="source/net/ipv4/ipmr.c#L2696">2696</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2697" href="source/net/ipv4/ipmr.c#L2697">2697</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2698" href="source/net/ipv4/ipmr.c#L2698">2698</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L2699" href="source/net/ipv4/ipmr.c#L2699">2699</a> };
<a name="L2700" href="source/net/ipv4/ipmr.c#L2700">2700</a> #endif
<a name="L2701" href="source/net/ipv4/ipmr.c#L2701">2701</a> 
<a name="L2702" href="source/net/ipv4/ipmr.c#L2702">2702</a> #ifdef CONFIG_IP_PIMSM_V2
<a name="L2703" href="source/net/ipv4/ipmr.c#L2703">2703</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=pim_protocol">pim_protocol</a> = {
<a name="L2704" href="source/net/ipv4/ipmr.c#L2704">2704</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=pim_rcv">pim_rcv</a>,
<a name="L2705" href="source/net/ipv4/ipmr.c#L2705">2705</a>         .netns_ok       =       1,
<a name="L2706" href="source/net/ipv4/ipmr.c#L2706">2706</a> };
<a name="L2707" href="source/net/ipv4/ipmr.c#L2707">2707</a> #endif
<a name="L2708" href="source/net/ipv4/ipmr.c#L2708">2708</a> 
<a name="L2709" href="source/net/ipv4/ipmr.c#L2709">2709</a> 
<a name="L2710" href="source/net/ipv4/ipmr.c#L2710">2710</a> <b><i>/*</i></b>
<a name="L2711" href="source/net/ipv4/ipmr.c#L2711">2711</a> <b><i> *      Setup for IP multicast routing</i></b>
<a name="L2712" href="source/net/ipv4/ipmr.c#L2712">2712</a> <b><i> */</i></b>
<a name="L2713" href="source/net/ipv4/ipmr.c#L2713">2713</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipmr_net_init">ipmr_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2714" href="source/net/ipv4/ipmr.c#L2714">2714</a> {
<a name="L2715" href="source/net/ipv4/ipmr.c#L2715">2715</a>         int <a href="ident?i=err">err</a>;
<a name="L2716" href="source/net/ipv4/ipmr.c#L2716">2716</a> 
<a name="L2717" href="source/net/ipv4/ipmr.c#L2717">2717</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_rules_init">ipmr_rules_init</a>(<a href="ident?i=net">net</a>);
<a name="L2718" href="source/net/ipv4/ipmr.c#L2718">2718</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2719" href="source/net/ipv4/ipmr.c#L2719">2719</a>                 goto <a href="ident?i=fail">fail</a>;
<a name="L2720" href="source/net/ipv4/ipmr.c#L2720">2720</a> 
<a name="L2721" href="source/net/ipv4/ipmr.c#L2721">2721</a> #ifdef CONFIG_PROC_FS
<a name="L2722" href="source/net/ipv4/ipmr.c#L2722">2722</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2723" href="source/net/ipv4/ipmr.c#L2723">2723</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"ip_mr_vif"</i>, 0, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=ipmr_vif_fops">ipmr_vif_fops</a>))
<a name="L2724" href="source/net/ipv4/ipmr.c#L2724">2724</a>                 goto proc_vif_fail;
<a name="L2725" href="source/net/ipv4/ipmr.c#L2725">2725</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"ip_mr_cache"</i>, 0, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=ipmr_mfc_fops">ipmr_mfc_fops</a>))
<a name="L2726" href="source/net/ipv4/ipmr.c#L2726">2726</a>                 goto proc_cache_fail;
<a name="L2727" href="source/net/ipv4/ipmr.c#L2727">2727</a> #endif
<a name="L2728" href="source/net/ipv4/ipmr.c#L2728">2728</a>         return 0;
<a name="L2729" href="source/net/ipv4/ipmr.c#L2729">2729</a> 
<a name="L2730" href="source/net/ipv4/ipmr.c#L2730">2730</a> #ifdef CONFIG_PROC_FS
<a name="L2731" href="source/net/ipv4/ipmr.c#L2731">2731</a> proc_cache_fail:
<a name="L2732" href="source/net/ipv4/ipmr.c#L2732">2732</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_mr_vif"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2733" href="source/net/ipv4/ipmr.c#L2733">2733</a> proc_vif_fail:
<a name="L2734" href="source/net/ipv4/ipmr.c#L2734">2734</a>         <a href="ident?i=ipmr_rules_exit">ipmr_rules_exit</a>(<a href="ident?i=net">net</a>);
<a name="L2735" href="source/net/ipv4/ipmr.c#L2735">2735</a> #endif
<a name="L2736" href="source/net/ipv4/ipmr.c#L2736">2736</a> <a href="ident?i=fail">fail</a>:
<a name="L2737" href="source/net/ipv4/ipmr.c#L2737">2737</a>         return <a href="ident?i=err">err</a>;
<a name="L2738" href="source/net/ipv4/ipmr.c#L2738">2738</a> }
<a name="L2739" href="source/net/ipv4/ipmr.c#L2739">2739</a> 
<a name="L2740" href="source/net/ipv4/ipmr.c#L2740">2740</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipmr_net_exit">ipmr_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2741" href="source/net/ipv4/ipmr.c#L2741">2741</a> {
<a name="L2742" href="source/net/ipv4/ipmr.c#L2742">2742</a> #ifdef CONFIG_PROC_FS
<a name="L2743" href="source/net/ipv4/ipmr.c#L2743">2743</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_mr_cache"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2744" href="source/net/ipv4/ipmr.c#L2744">2744</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_mr_vif"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2745" href="source/net/ipv4/ipmr.c#L2745">2745</a> #endif
<a name="L2746" href="source/net/ipv4/ipmr.c#L2746">2746</a>         <a href="ident?i=ipmr_rules_exit">ipmr_rules_exit</a>(<a href="ident?i=net">net</a>);
<a name="L2747" href="source/net/ipv4/ipmr.c#L2747">2747</a> }
<a name="L2748" href="source/net/ipv4/ipmr.c#L2748">2748</a> 
<a name="L2749" href="source/net/ipv4/ipmr.c#L2749">2749</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipmr_net_ops">ipmr_net_ops</a> = {
<a name="L2750" href="source/net/ipv4/ipmr.c#L2750">2750</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipmr_net_init">ipmr_net_init</a>,
<a name="L2751" href="source/net/ipv4/ipmr.c#L2751">2751</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipmr_net_exit">ipmr_net_exit</a>,
<a name="L2752" href="source/net/ipv4/ipmr.c#L2752">2752</a> };
<a name="L2753" href="source/net/ipv4/ipmr.c#L2753">2753</a> 
<a name="L2754" href="source/net/ipv4/ipmr.c#L2754">2754</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_mr_init">ip_mr_init</a>(void)
<a name="L2755" href="source/net/ipv4/ipmr.c#L2755">2755</a> {
<a name="L2756" href="source/net/ipv4/ipmr.c#L2756">2756</a>         int <a href="ident?i=err">err</a>;
<a name="L2757" href="source/net/ipv4/ipmr.c#L2757">2757</a> 
<a name="L2758" href="source/net/ipv4/ipmr.c#L2758">2758</a>         mrt_cachep = <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<i>"ip_mrt_cache"</i>,
<a name="L2759" href="source/net/ipv4/ipmr.c#L2759">2759</a>                                        sizeof(struct <a href="ident?i=mfc_cache">mfc_cache</a>),
<a name="L2760" href="source/net/ipv4/ipmr.c#L2760">2760</a>                                        0, <a href="ident?i=SLAB_HWCACHE_ALIGN">SLAB_HWCACHE_ALIGN</a> | <a href="ident?i=SLAB_PANIC">SLAB_PANIC</a>,
<a name="L2761" href="source/net/ipv4/ipmr.c#L2761">2761</a>                                        <a href="ident?i=NULL">NULL</a>);
<a name="L2762" href="source/net/ipv4/ipmr.c#L2762">2762</a>         if (!mrt_cachep)
<a name="L2763" href="source/net/ipv4/ipmr.c#L2763">2763</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2764" href="source/net/ipv4/ipmr.c#L2764">2764</a> 
<a name="L2765" href="source/net/ipv4/ipmr.c#L2765">2765</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ipmr_net_ops">ipmr_net_ops</a>);
<a name="L2766" href="source/net/ipv4/ipmr.c#L2766">2766</a>         if (<a href="ident?i=err">err</a>)
<a name="L2767" href="source/net/ipv4/ipmr.c#L2767">2767</a>                 goto reg_pernet_fail;
<a name="L2768" href="source/net/ipv4/ipmr.c#L2768">2768</a> 
<a name="L2769" href="source/net/ipv4/ipmr.c#L2769">2769</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=ip_mr_notifier">ip_mr_notifier</a>);
<a name="L2770" href="source/net/ipv4/ipmr.c#L2770">2770</a>         if (<a href="ident?i=err">err</a>)
<a name="L2771" href="source/net/ipv4/ipmr.c#L2771">2771</a>                 goto reg_notif_fail;
<a name="L2772" href="source/net/ipv4/ipmr.c#L2772">2772</a> #ifdef CONFIG_IP_PIMSM_V2
<a name="L2773" href="source/net/ipv4/ipmr.c#L2773">2773</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=pim_protocol">pim_protocol</a>, <a href="ident?i=IPPROTO_PIM">IPPROTO_PIM</a>) &lt; 0) {
<a name="L2774" href="source/net/ipv4/ipmr.c#L2774">2774</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"%s: can't add PIM protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L2775" href="source/net/ipv4/ipmr.c#L2775">2775</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L2776" href="source/net/ipv4/ipmr.c#L2776">2776</a>                 goto add_proto_fail;
<a name="L2777" href="source/net/ipv4/ipmr.c#L2777">2777</a>         }
<a name="L2778" href="source/net/ipv4/ipmr.c#L2778">2778</a> #endif
<a name="L2779" href="source/net/ipv4/ipmr.c#L2779">2779</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=RTNL_FAMILY_IPMR">RTNL_FAMILY_IPMR</a>, <a href="ident?i=RTM_GETROUTE">RTM_GETROUTE</a>,
<a name="L2780" href="source/net/ipv4/ipmr.c#L2780">2780</a>                       <a href="ident?i=NULL">NULL</a>, <a href="ident?i=ipmr_rtm_dumproute">ipmr_rtm_dumproute</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2781" href="source/net/ipv4/ipmr.c#L2781">2781</a>         return 0;
<a name="L2782" href="source/net/ipv4/ipmr.c#L2782">2782</a> 
<a name="L2783" href="source/net/ipv4/ipmr.c#L2783">2783</a> #ifdef CONFIG_IP_PIMSM_V2
<a name="L2784" href="source/net/ipv4/ipmr.c#L2784">2784</a> add_proto_fail:
<a name="L2785" href="source/net/ipv4/ipmr.c#L2785">2785</a>         <a href="ident?i=unregister_netdevice_notifier">unregister_netdevice_notifier</a>(&amp;<a href="ident?i=ip_mr_notifier">ip_mr_notifier</a>);
<a name="L2786" href="source/net/ipv4/ipmr.c#L2786">2786</a> #endif
<a name="L2787" href="source/net/ipv4/ipmr.c#L2787">2787</a> reg_notif_fail:
<a name="L2788" href="source/net/ipv4/ipmr.c#L2788">2788</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ipmr_net_ops">ipmr_net_ops</a>);
<a name="L2789" href="source/net/ipv4/ipmr.c#L2789">2789</a> reg_pernet_fail:
<a name="L2790" href="source/net/ipv4/ipmr.c#L2790">2790</a>         <a href="ident?i=kmem_cache_destroy">kmem_cache_destroy</a>(mrt_cachep);
<a name="L2791" href="source/net/ipv4/ipmr.c#L2791">2791</a>         return <a href="ident?i=err">err</a>;
<a name="L2792" href="source/net/ipv4/ipmr.c#L2792">2792</a> }
<a name="L2793" href="source/net/ipv4/ipmr.c#L2793">2793</a> </pre></div><p>
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
