<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_metrics.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_metrics.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_metrics.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_metrics.c">tcp_metrics.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_metrics.c#L1">1</a> #include &lt;linux/rcupdate.h&gt;
  <a name="L2" href="source/net/ipv4/tcp_metrics.c#L2">2</a> #include &lt;linux/spinlock.h&gt;
  <a name="L3" href="source/net/ipv4/tcp_metrics.c#L3">3</a> #include &lt;linux/jiffies.h&gt;
  <a name="L4" href="source/net/ipv4/tcp_metrics.c#L4">4</a> #include &lt;linux/module.h&gt;
  <a name="L5" href="source/net/ipv4/tcp_metrics.c#L5">5</a> #include &lt;linux/cache.h&gt;
  <a name="L6" href="source/net/ipv4/tcp_metrics.c#L6">6</a> #include &lt;linux/slab.h&gt;
  <a name="L7" href="source/net/ipv4/tcp_metrics.c#L7">7</a> #include &lt;linux/init.h&gt;
  <a name="L8" href="source/net/ipv4/tcp_metrics.c#L8">8</a> #include &lt;linux/tcp.h&gt;
  <a name="L9" href="source/net/ipv4/tcp_metrics.c#L9">9</a> #include &lt;linux/hash.h&gt;
 <a name="L10" href="source/net/ipv4/tcp_metrics.c#L10">10</a> #include &lt;linux/tcp_metrics.h&gt;
 <a name="L11" href="source/net/ipv4/tcp_metrics.c#L11">11</a> #include &lt;linux/vmalloc.h&gt;
 <a name="L12" href="source/net/ipv4/tcp_metrics.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/tcp_metrics.c#L13">13</a> #include &lt;net/inet_connection_sock.h&gt;
 <a name="L14" href="source/net/ipv4/tcp_metrics.c#L14">14</a> #include &lt;net/net_namespace.h&gt;
 <a name="L15" href="source/net/ipv4/tcp_metrics.c#L15">15</a> #include &lt;net/request_sock.h&gt;
 <a name="L16" href="source/net/ipv4/tcp_metrics.c#L16">16</a> #include &lt;net/inetpeer.h&gt;
 <a name="L17" href="source/net/ipv4/tcp_metrics.c#L17">17</a> #include &lt;net/sock.h&gt;
 <a name="L18" href="source/net/ipv4/tcp_metrics.c#L18">18</a> #include &lt;net/ipv6.h&gt;
 <a name="L19" href="source/net/ipv4/tcp_metrics.c#L19">19</a> #include &lt;net/dst.h&gt;
 <a name="L20" href="source/net/ipv4/tcp_metrics.c#L20">20</a> #include &lt;net/tcp.h&gt;
 <a name="L21" href="source/net/ipv4/tcp_metrics.c#L21">21</a> #include &lt;net/genetlink.h&gt;
 <a name="L22" href="source/net/ipv4/tcp_metrics.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/tcp_metrics.c#L23">23</a> int <a href="ident?i=sysctl_tcp_nometrics_save">sysctl_tcp_nometrics_save</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L24" href="source/net/ipv4/tcp_metrics.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_metrics.c#L25">25</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=__tcp_get_metrics">__tcp_get_metrics</a>(const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=saddr">saddr</a>,
 <a name="L26" href="source/net/ipv4/tcp_metrics.c#L26">26</a>                                                    const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=daddr">daddr</a>,
 <a name="L27" href="source/net/ipv4/tcp_metrics.c#L27">27</a>                                                    struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned int <a href="ident?i=hash">hash</a>);
 <a name="L28" href="source/net/ipv4/tcp_metrics.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/tcp_metrics.c#L29">29</a> struct <a href="ident?i=tcp_fastopen_metrics">tcp_fastopen_metrics</a> {
 <a name="L30" href="source/net/ipv4/tcp_metrics.c#L30">30</a>         <a href="ident?i=u16">u16</a>     mss;
 <a name="L31" href="source/net/ipv4/tcp_metrics.c#L31">31</a>         <a href="ident?i=u16">u16</a>     syn_loss:10,            <b><i>/* Recurring Fast Open SYN losses */</i></b>
 <a name="L32" href="source/net/ipv4/tcp_metrics.c#L32">32</a>                 try_exp:2;              <b><i>/* Request w/ exp. option (once) */</i></b>
 <a name="L33" href="source/net/ipv4/tcp_metrics.c#L33">33</a>         unsigned long   last_syn_loss;  <b><i>/* Last Fast Open SYN loss */</i></b>
 <a name="L34" href="source/net/ipv4/tcp_metrics.c#L34">34</a>         struct  <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a>     cookie;
 <a name="L35" href="source/net/ipv4/tcp_metrics.c#L35">35</a> };
 <a name="L36" href="source/net/ipv4/tcp_metrics.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/tcp_metrics.c#L37">37</a> <b><i>/* TCP_METRIC_MAX includes 2 extra fields for userspace compatibility</i></b>
 <a name="L38" href="source/net/ipv4/tcp_metrics.c#L38">38</a> <b><i> * Kernel only stores RTT and RTTVAR in usec resolution</i></b>
 <a name="L39" href="source/net/ipv4/tcp_metrics.c#L39">39</a> <b><i> */</i></b>
 <a name="L40" href="source/net/ipv4/tcp_metrics.c#L40">40</a> #define <a href="ident?i=TCP_METRIC_MAX_KERNEL">TCP_METRIC_MAX_KERNEL</a> (<a href="ident?i=TCP_METRIC_MAX">TCP_METRIC_MAX</a> - 2)
 <a name="L41" href="source/net/ipv4/tcp_metrics.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/tcp_metrics.c#L42">42</a> struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> {
 <a name="L43" href="source/net/ipv4/tcp_metrics.c#L43">43</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> <a href="ident?i=__rcu">__rcu</a>  *tcpm_next;
 <a name="L44" href="source/net/ipv4/tcp_metrics.c#L44">44</a>         <a href="ident?i=possible_net_t">possible_net_t</a>                  tcpm_net;
 <a name="L45" href="source/net/ipv4/tcp_metrics.c#L45">45</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a>            tcpm_saddr;
 <a name="L46" href="source/net/ipv4/tcp_metrics.c#L46">46</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a>            tcpm_daddr;
 <a name="L47" href="source/net/ipv4/tcp_metrics.c#L47">47</a>         unsigned long                   tcpm_stamp;
 <a name="L48" href="source/net/ipv4/tcp_metrics.c#L48">48</a>         <a href="ident?i=u32">u32</a>                             tcpm_ts;
 <a name="L49" href="source/net/ipv4/tcp_metrics.c#L49">49</a>         <a href="ident?i=u32">u32</a>                             tcpm_ts_stamp;
 <a name="L50" href="source/net/ipv4/tcp_metrics.c#L50">50</a>         <a href="ident?i=u32">u32</a>                             tcpm_lock;
 <a name="L51" href="source/net/ipv4/tcp_metrics.c#L51">51</a>         <a href="ident?i=u32">u32</a>                             tcpm_vals[<a href="ident?i=TCP_METRIC_MAX_KERNEL">TCP_METRIC_MAX_KERNEL</a> + 1];
 <a name="L52" href="source/net/ipv4/tcp_metrics.c#L52">52</a>         struct <a href="ident?i=tcp_fastopen_metrics">tcp_fastopen_metrics</a>     tcpm_fastopen;
 <a name="L53" href="source/net/ipv4/tcp_metrics.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tcp_metrics.c#L54">54</a>         struct <a href="ident?i=rcu_head">rcu_head</a>                 <a href="ident?i=rcu_head">rcu_head</a>;
 <a name="L55" href="source/net/ipv4/tcp_metrics.c#L55">55</a> };
 <a name="L56" href="source/net/ipv4/tcp_metrics.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/tcp_metrics.c#L57">57</a> static inline struct <a href="ident?i=net">net</a> *<a href="ident?i=tm_net">tm_net</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>)
 <a name="L58" href="source/net/ipv4/tcp_metrics.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/tcp_metrics.c#L59">59</a>         return <a href="ident?i=read_pnet">read_pnet</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_net);
 <a name="L60" href="source/net/ipv4/tcp_metrics.c#L60">60</a> }
 <a name="L61" href="source/net/ipv4/tcp_metrics.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/tcp_metrics.c#L62">62</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>,
 <a name="L63" href="source/net/ipv4/tcp_metrics.c#L63">63</a>                               enum <a href="ident?i=tcp_metric_index">tcp_metric_index</a> <a href="ident?i=idx">idx</a>)
 <a name="L64" href="source/net/ipv4/tcp_metrics.c#L64">64</a> {
 <a name="L65" href="source/net/ipv4/tcp_metrics.c#L65">65</a>         return <a href="ident?i=tm">tm</a>-&gt;tcpm_lock &amp; (1 &lt;&lt; <a href="ident?i=idx">idx</a>);
 <a name="L66" href="source/net/ipv4/tcp_metrics.c#L66">66</a> }
 <a name="L67" href="source/net/ipv4/tcp_metrics.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/tcp_metrics.c#L68">68</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>,
 <a name="L69" href="source/net/ipv4/tcp_metrics.c#L69">69</a>                           enum <a href="ident?i=tcp_metric_index">tcp_metric_index</a> <a href="ident?i=idx">idx</a>)
 <a name="L70" href="source/net/ipv4/tcp_metrics.c#L70">70</a> {
 <a name="L71" href="source/net/ipv4/tcp_metrics.c#L71">71</a>         return <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[<a href="ident?i=idx">idx</a>];
 <a name="L72" href="source/net/ipv4/tcp_metrics.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/tcp_metrics.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/tcp_metrics.c#L74">74</a> static void <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>,
 <a name="L75" href="source/net/ipv4/tcp_metrics.c#L75">75</a>                            enum <a href="ident?i=tcp_metric_index">tcp_metric_index</a> <a href="ident?i=idx">idx</a>,
 <a name="L76" href="source/net/ipv4/tcp_metrics.c#L76">76</a>                            <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a>)
 <a name="L77" href="source/net/ipv4/tcp_metrics.c#L77">77</a> {
 <a name="L78" href="source/net/ipv4/tcp_metrics.c#L78">78</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[<a href="ident?i=idx">idx</a>] = <a href="ident?i=val">val</a>;
 <a name="L79" href="source/net/ipv4/tcp_metrics.c#L79">79</a> }
 <a name="L80" href="source/net/ipv4/tcp_metrics.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_metrics.c#L81">81</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=addr_same">addr_same</a>(const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=a">a</a>,
 <a name="L82" href="source/net/ipv4/tcp_metrics.c#L82">82</a>                       const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=b">b</a>)
 <a name="L83" href="source/net/ipv4/tcp_metrics.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/tcp_metrics.c#L84">84</a>         if (<a href="ident?i=a">a</a>-&gt;<a href="ident?i=family">family</a> != <a href="ident?i=b">b</a>-&gt;<a href="ident?i=family">family</a>)
 <a name="L85" href="source/net/ipv4/tcp_metrics.c#L85">85</a>                 return <a href="ident?i=false">false</a>;
 <a name="L86" href="source/net/ipv4/tcp_metrics.c#L86">86</a>         if (<a href="ident?i=a">a</a>-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>)
 <a name="L87" href="source/net/ipv4/tcp_metrics.c#L87">87</a>                 return <a href="ident?i=a">a</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> == <a href="ident?i=b">b</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
 <a name="L88" href="source/net/ipv4/tcp_metrics.c#L88">88</a>         return <a href="ident?i=ipv6_addr_equal">ipv6_addr_equal</a>(&amp;<a href="ident?i=a">a</a>-&gt;<a href="ident?i=addr">addr</a>.in6, &amp;<a href="ident?i=b">b</a>-&gt;<a href="ident?i=addr">addr</a>.in6);
 <a name="L89" href="source/net/ipv4/tcp_metrics.c#L89">89</a> }
 <a name="L90" href="source/net/ipv4/tcp_metrics.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_metrics.c#L91">91</a> struct <a href="ident?i=tcpm_hash_bucket">tcpm_hash_bucket</a> {
 <a name="L92" href="source/net/ipv4/tcp_metrics.c#L92">92</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> <a href="ident?i=__rcu">__rcu</a>  *<a href="ident?i=chain">chain</a>;
 <a name="L93" href="source/net/ipv4/tcp_metrics.c#L93">93</a> };
 <a name="L94" href="source/net/ipv4/tcp_metrics.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/tcp_metrics.c#L95">95</a> static struct <a href="ident?i=tcpm_hash_bucket">tcpm_hash_bucket</a>  *tcp_metrics_hash <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L96" href="source/net/ipv4/tcp_metrics.c#L96">96</a> static unsigned int             tcp_metrics_hash_log <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L97" href="source/net/ipv4/tcp_metrics.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/tcp_metrics.c#L98">98</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(tcp_metrics_lock);
 <a name="L99" href="source/net/ipv4/tcp_metrics.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/tcp_metrics.c#L100">100</a> static void <a href="ident?i=tcpm_suck_dst">tcpm_suck_dst</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>,
<a name="L101" href="source/net/ipv4/tcp_metrics.c#L101">101</a>                           const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L102" href="source/net/ipv4/tcp_metrics.c#L102">102</a>                           <a href="ident?i=bool">bool</a> fastopen_clear)
<a name="L103" href="source/net/ipv4/tcp_metrics.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/tcp_metrics.c#L104">104</a>         <a href="ident?i=u32">u32</a> msval;
<a name="L105" href="source/net/ipv4/tcp_metrics.c#L105">105</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a>;
<a name="L106" href="source/net/ipv4/tcp_metrics.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/tcp_metrics.c#L107">107</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_stamp = <a href="ident?i=jiffies">jiffies</a>;
<a name="L108" href="source/net/ipv4/tcp_metrics.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/tcp_metrics.c#L109">109</a>         <a href="ident?i=val">val</a> = 0;
<a name="L110" href="source/net/ipv4/tcp_metrics.c#L110">110</a>         if (<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_RTT">RTAX_RTT</a>))
<a name="L111" href="source/net/ipv4/tcp_metrics.c#L111">111</a>                 <a href="ident?i=val">val</a> |= 1 &lt;&lt; TCP_METRIC_RTT;
<a name="L112" href="source/net/ipv4/tcp_metrics.c#L112">112</a>         if (<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_RTTVAR">RTAX_RTTVAR</a>))
<a name="L113" href="source/net/ipv4/tcp_metrics.c#L113">113</a>                 <a href="ident?i=val">val</a> |= 1 &lt;&lt; TCP_METRIC_RTTVAR;
<a name="L114" href="source/net/ipv4/tcp_metrics.c#L114">114</a>         if (<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_SSTHRESH">RTAX_SSTHRESH</a>))
<a name="L115" href="source/net/ipv4/tcp_metrics.c#L115">115</a>                 <a href="ident?i=val">val</a> |= 1 &lt;&lt; TCP_METRIC_SSTHRESH;
<a name="L116" href="source/net/ipv4/tcp_metrics.c#L116">116</a>         if (<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_CWND">RTAX_CWND</a>))
<a name="L117" href="source/net/ipv4/tcp_metrics.c#L117">117</a>                 <a href="ident?i=val">val</a> |= 1 &lt;&lt; TCP_METRIC_CWND;
<a name="L118" href="source/net/ipv4/tcp_metrics.c#L118">118</a>         if (<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_REORDERING">RTAX_REORDERING</a>))
<a name="L119" href="source/net/ipv4/tcp_metrics.c#L119">119</a>                 <a href="ident?i=val">val</a> |= 1 &lt;&lt; TCP_METRIC_REORDERING;
<a name="L120" href="source/net/ipv4/tcp_metrics.c#L120">120</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_lock = <a href="ident?i=val">val</a>;
<a name="L121" href="source/net/ipv4/tcp_metrics.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_metrics.c#L122">122</a>         msval = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_RTT">RTAX_RTT</a>);
<a name="L123" href="source/net/ipv4/tcp_metrics.c#L123">123</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[TCP_METRIC_RTT] = msval * <a href="ident?i=USEC_PER_MSEC">USEC_PER_MSEC</a>;
<a name="L124" href="source/net/ipv4/tcp_metrics.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/tcp_metrics.c#L125">125</a>         msval = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_RTTVAR">RTAX_RTTVAR</a>);
<a name="L126" href="source/net/ipv4/tcp_metrics.c#L126">126</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[TCP_METRIC_RTTVAR] = msval * <a href="ident?i=USEC_PER_MSEC">USEC_PER_MSEC</a>;
<a name="L127" href="source/net/ipv4/tcp_metrics.c#L127">127</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[TCP_METRIC_SSTHRESH] = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_SSTHRESH">RTAX_SSTHRESH</a>);
<a name="L128" href="source/net/ipv4/tcp_metrics.c#L128">128</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[TCP_METRIC_CWND] = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_CWND">RTAX_CWND</a>);
<a name="L129" href="source/net/ipv4/tcp_metrics.c#L129">129</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[TCP_METRIC_REORDERING] = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_REORDERING">RTAX_REORDERING</a>);
<a name="L130" href="source/net/ipv4/tcp_metrics.c#L130">130</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_ts = 0;
<a name="L131" href="source/net/ipv4/tcp_metrics.c#L131">131</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp = 0;
<a name="L132" href="source/net/ipv4/tcp_metrics.c#L132">132</a>         if (fastopen_clear) {
<a name="L133" href="source/net/ipv4/tcp_metrics.c#L133">133</a>                 <a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen.mss = 0;
<a name="L134" href="source/net/ipv4/tcp_metrics.c#L134">134</a>                 <a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen.syn_loss = 0;
<a name="L135" href="source/net/ipv4/tcp_metrics.c#L135">135</a>                 <a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen.try_exp = 0;
<a name="L136" href="source/net/ipv4/tcp_metrics.c#L136">136</a>                 <a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen.cookie.exp = <a href="ident?i=false">false</a>;
<a name="L137" href="source/net/ipv4/tcp_metrics.c#L137">137</a>                 <a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen.cookie.<a href="ident?i=len">len</a> = 0;
<a name="L138" href="source/net/ipv4/tcp_metrics.c#L138">138</a>         }
<a name="L139" href="source/net/ipv4/tcp_metrics.c#L139">139</a> }
<a name="L140" href="source/net/ipv4/tcp_metrics.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/tcp_metrics.c#L141">141</a> #define <a href="ident?i=TCP_METRICS_TIMEOUT">TCP_METRICS_TIMEOUT</a>             (60 * 60 * <a href="ident?i=HZ">HZ</a>)
<a name="L142" href="source/net/ipv4/tcp_metrics.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/tcp_metrics.c#L143">143</a> static void <a href="ident?i=tcpm_check_stamp">tcpm_check_stamp</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L144" href="source/net/ipv4/tcp_metrics.c#L144">144</a> {
<a name="L145" href="source/net/ipv4/tcp_metrics.c#L145">145</a>         if (<a href="ident?i=tm">tm</a> &amp;&amp; <a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=time_after">time_after</a>(<a href="ident?i=jiffies">jiffies</a>, <a href="ident?i=tm">tm</a>-&gt;tcpm_stamp + <a href="ident?i=TCP_METRICS_TIMEOUT">TCP_METRICS_TIMEOUT</a>)))
<a name="L146" href="source/net/ipv4/tcp_metrics.c#L146">146</a>                 <a href="ident?i=tcpm_suck_dst">tcpm_suck_dst</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=false">false</a>);
<a name="L147" href="source/net/ipv4/tcp_metrics.c#L147">147</a> }
<a name="L148" href="source/net/ipv4/tcp_metrics.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/tcp_metrics.c#L149">149</a> #define <a href="ident?i=TCP_METRICS_RECLAIM_DEPTH">TCP_METRICS_RECLAIM_DEPTH</a>       5
<a name="L150" href="source/net/ipv4/tcp_metrics.c#L150">150</a> #define <a href="ident?i=TCP_METRICS_RECLAIM_PTR">TCP_METRICS_RECLAIM_PTR</a>         (struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *) 0x1UL
<a name="L151" href="source/net/ipv4/tcp_metrics.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/tcp_metrics.c#L152">152</a> #define <a href="ident?i=deref_locked">deref_locked</a>(<a href="ident?i=p">p</a>) \
<a name="L153" href="source/net/ipv4/tcp_metrics.c#L153">153</a>         <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=p">p</a>, <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;tcp_metrics_lock))
<a name="L154" href="source/net/ipv4/tcp_metrics.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tcp_metrics.c#L155">155</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tcpm_new">tcpm_new</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L156" href="source/net/ipv4/tcp_metrics.c#L156">156</a>                                           struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=saddr">saddr</a>,
<a name="L157" href="source/net/ipv4/tcp_metrics.c#L157">157</a>                                           struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=daddr">daddr</a>,
<a name="L158" href="source/net/ipv4/tcp_metrics.c#L158">158</a>                                           unsigned int <a href="ident?i=hash">hash</a>)
<a name="L159" href="source/net/ipv4/tcp_metrics.c#L159">159</a> {
<a name="L160" href="source/net/ipv4/tcp_metrics.c#L160">160</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L161" href="source/net/ipv4/tcp_metrics.c#L161">161</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L162" href="source/net/ipv4/tcp_metrics.c#L162">162</a>         <a href="ident?i=bool">bool</a> reclaim = <a href="ident?i=false">false</a>;
<a name="L163" href="source/net/ipv4/tcp_metrics.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/tcp_metrics.c#L164">164</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;tcp_metrics_lock);
<a name="L165" href="source/net/ipv4/tcp_metrics.c#L165">165</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L166" href="source/net/ipv4/tcp_metrics.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/tcp_metrics.c#L167">167</a>         <b><i>/* While waiting for the spin-lock the cache might have been populated</i></b>
<a name="L168" href="source/net/ipv4/tcp_metrics.c#L168">168</a> <b><i>         * with this entry and so we have to check again.</i></b>
<a name="L169" href="source/net/ipv4/tcp_metrics.c#L169">169</a> <b><i>         */</i></b>
<a name="L170" href="source/net/ipv4/tcp_metrics.c#L170">170</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=__tcp_get_metrics">__tcp_get_metrics</a>(<a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=net">net</a>, <a href="ident?i=hash">hash</a>);
<a name="L171" href="source/net/ipv4/tcp_metrics.c#L171">171</a>         if (<a href="ident?i=tm">tm</a> == <a href="ident?i=TCP_METRICS_RECLAIM_PTR">TCP_METRICS_RECLAIM_PTR</a>) {
<a name="L172" href="source/net/ipv4/tcp_metrics.c#L172">172</a>                 reclaim = <a href="ident?i=true">true</a>;
<a name="L173" href="source/net/ipv4/tcp_metrics.c#L173">173</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L174" href="source/net/ipv4/tcp_metrics.c#L174">174</a>         }
<a name="L175" href="source/net/ipv4/tcp_metrics.c#L175">175</a>         if (<a href="ident?i=tm">tm</a>) {
<a name="L176" href="source/net/ipv4/tcp_metrics.c#L176">176</a>                 <a href="ident?i=tcpm_check_stamp">tcpm_check_stamp</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=dst">dst</a>);
<a name="L177" href="source/net/ipv4/tcp_metrics.c#L177">177</a>                 goto out_unlock;
<a name="L178" href="source/net/ipv4/tcp_metrics.c#L178">178</a>         }
<a name="L179" href="source/net/ipv4/tcp_metrics.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/tcp_metrics.c#L180">180</a>         if (<a href="ident?i=unlikely">unlikely</a>(reclaim)) {
<a name="L181" href="source/net/ipv4/tcp_metrics.c#L181">181</a>                 struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *oldest;
<a name="L182" href="source/net/ipv4/tcp_metrics.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_metrics.c#L183">183</a>                 oldest = <a href="ident?i=deref_locked">deref_locked</a>(tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>);
<a name="L184" href="source/net/ipv4/tcp_metrics.c#L184">184</a>                 for (<a href="ident?i=tm">tm</a> = <a href="ident?i=deref_locked">deref_locked</a>(oldest-&gt;tcpm_next); <a href="ident?i=tm">tm</a>;
<a name="L185" href="source/net/ipv4/tcp_metrics.c#L185">185</a>                      <a href="ident?i=tm">tm</a> = <a href="ident?i=deref_locked">deref_locked</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_next)) {
<a name="L186" href="source/net/ipv4/tcp_metrics.c#L186">186</a>                         if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_stamp, oldest-&gt;tcpm_stamp))
<a name="L187" href="source/net/ipv4/tcp_metrics.c#L187">187</a>                                 oldest = <a href="ident?i=tm">tm</a>;
<a name="L188" href="source/net/ipv4/tcp_metrics.c#L188">188</a>                 }
<a name="L189" href="source/net/ipv4/tcp_metrics.c#L189">189</a>                 <a href="ident?i=tm">tm</a> = oldest;
<a name="L190" href="source/net/ipv4/tcp_metrics.c#L190">190</a>         } else {
<a name="L191" href="source/net/ipv4/tcp_metrics.c#L191">191</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*<a href="ident?i=tm">tm</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L192" href="source/net/ipv4/tcp_metrics.c#L192">192</a>                 if (!<a href="ident?i=tm">tm</a>)
<a name="L193" href="source/net/ipv4/tcp_metrics.c#L193">193</a>                         goto out_unlock;
<a name="L194" href="source/net/ipv4/tcp_metrics.c#L194">194</a>         }
<a name="L195" href="source/net/ipv4/tcp_metrics.c#L195">195</a>         <a href="ident?i=write_pnet">write_pnet</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_net, <a href="ident?i=net">net</a>);
<a name="L196" href="source/net/ipv4/tcp_metrics.c#L196">196</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_saddr = *<a href="ident?i=saddr">saddr</a>;
<a name="L197" href="source/net/ipv4/tcp_metrics.c#L197">197</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_daddr = *<a href="ident?i=daddr">daddr</a>;
<a name="L198" href="source/net/ipv4/tcp_metrics.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/tcp_metrics.c#L199">199</a>         <a href="ident?i=tcpm_suck_dst">tcpm_suck_dst</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L200" href="source/net/ipv4/tcp_metrics.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/tcp_metrics.c#L201">201</a>         if (<a href="ident?i=likely">likely</a>(!reclaim)) {
<a name="L202" href="source/net/ipv4/tcp_metrics.c#L202">202</a>                 <a href="ident?i=tm">tm</a>-&gt;tcpm_next = tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>;
<a name="L203" href="source/net/ipv4/tcp_metrics.c#L203">203</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>, <a href="ident?i=tm">tm</a>);
<a name="L204" href="source/net/ipv4/tcp_metrics.c#L204">204</a>         }
<a name="L205" href="source/net/ipv4/tcp_metrics.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/tcp_metrics.c#L206">206</a> out_unlock:
<a name="L207" href="source/net/ipv4/tcp_metrics.c#L207">207</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;tcp_metrics_lock);
<a name="L208" href="source/net/ipv4/tcp_metrics.c#L208">208</a>         return <a href="ident?i=tm">tm</a>;
<a name="L209" href="source/net/ipv4/tcp_metrics.c#L209">209</a> }
<a name="L210" href="source/net/ipv4/tcp_metrics.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/tcp_metrics.c#L211">211</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tcp_get_encode">tcp_get_encode</a>(struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>, int <a href="ident?i=depth">depth</a>)
<a name="L212" href="source/net/ipv4/tcp_metrics.c#L212">212</a> {
<a name="L213" href="source/net/ipv4/tcp_metrics.c#L213">213</a>         if (<a href="ident?i=tm">tm</a>)
<a name="L214" href="source/net/ipv4/tcp_metrics.c#L214">214</a>                 return <a href="ident?i=tm">tm</a>;
<a name="L215" href="source/net/ipv4/tcp_metrics.c#L215">215</a>         if (<a href="ident?i=depth">depth</a> &gt; <a href="ident?i=TCP_METRICS_RECLAIM_DEPTH">TCP_METRICS_RECLAIM_DEPTH</a>)
<a name="L216" href="source/net/ipv4/tcp_metrics.c#L216">216</a>                 return <a href="ident?i=TCP_METRICS_RECLAIM_PTR">TCP_METRICS_RECLAIM_PTR</a>;
<a name="L217" href="source/net/ipv4/tcp_metrics.c#L217">217</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L218" href="source/net/ipv4/tcp_metrics.c#L218">218</a> }
<a name="L219" href="source/net/ipv4/tcp_metrics.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/tcp_metrics.c#L220">220</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=__tcp_get_metrics">__tcp_get_metrics</a>(const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=saddr">saddr</a>,
<a name="L221" href="source/net/ipv4/tcp_metrics.c#L221">221</a>                                                    const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=daddr">daddr</a>,
<a name="L222" href="source/net/ipv4/tcp_metrics.c#L222">222</a>                                                    struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned int <a href="ident?i=hash">hash</a>)
<a name="L223" href="source/net/ipv4/tcp_metrics.c#L223">223</a> {
<a name="L224" href="source/net/ipv4/tcp_metrics.c#L224">224</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L225" href="source/net/ipv4/tcp_metrics.c#L225">225</a>         int <a href="ident?i=depth">depth</a> = 0;
<a name="L226" href="source/net/ipv4/tcp_metrics.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/tcp_metrics.c#L227">227</a>         for (<a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>); <a href="ident?i=tm">tm</a>;
<a name="L228" href="source/net/ipv4/tcp_metrics.c#L228">228</a>              <a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_next)) {
<a name="L229" href="source/net/ipv4/tcp_metrics.c#L229">229</a>                 if (<a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_saddr, <a href="ident?i=saddr">saddr</a>) &amp;&amp;
<a name="L230" href="source/net/ipv4/tcp_metrics.c#L230">230</a>                     <a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr, <a href="ident?i=daddr">daddr</a>) &amp;&amp;
<a name="L231" href="source/net/ipv4/tcp_metrics.c#L231">231</a>                     <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>))
<a name="L232" href="source/net/ipv4/tcp_metrics.c#L232">232</a>                         break;
<a name="L233" href="source/net/ipv4/tcp_metrics.c#L233">233</a>                 <a href="ident?i=depth">depth</a>++;
<a name="L234" href="source/net/ipv4/tcp_metrics.c#L234">234</a>         }
<a name="L235" href="source/net/ipv4/tcp_metrics.c#L235">235</a>         return <a href="ident?i=tcp_get_encode">tcp_get_encode</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=depth">depth</a>);
<a name="L236" href="source/net/ipv4/tcp_metrics.c#L236">236</a> }
<a name="L237" href="source/net/ipv4/tcp_metrics.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/tcp_metrics.c#L238">238</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=__tcp_get_metrics_req">__tcp_get_metrics_req</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L239" href="source/net/ipv4/tcp_metrics.c#L239">239</a>                                                        struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L240" href="source/net/ipv4/tcp_metrics.c#L240">240</a> {
<a name="L241" href="source/net/ipv4/tcp_metrics.c#L241">241</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L242" href="source/net/ipv4/tcp_metrics.c#L242">242</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L243" href="source/net/ipv4/tcp_metrics.c#L243">243</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L244" href="source/net/ipv4/tcp_metrics.c#L244">244</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L245" href="source/net/ipv4/tcp_metrics.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/tcp_metrics.c#L246">246</a>         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=family">family</a>;
<a name="L247" href="source/net/ipv4/tcp_metrics.c#L247">247</a>         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=family">family</a>;
<a name="L248" href="source/net/ipv4/tcp_metrics.c#L248">248</a>         switch (<a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a>) {
<a name="L249" href="source/net/ipv4/tcp_metrics.c#L249">249</a>         case <a href="ident?i=AF_INET">AF_INET</a>:
<a name="L250" href="source/net/ipv4/tcp_metrics.c#L250">250</a>                 <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>;
<a name="L251" href="source/net/ipv4/tcp_metrics.c#L251">251</a>                 <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>;
<a name="L252" href="source/net/ipv4/tcp_metrics.c#L252">252</a>                 <a href="ident?i=hash">hash</a> = (<a href="ident?i=__force">__force</a> unsigned int) <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
<a name="L253" href="source/net/ipv4/tcp_metrics.c#L253">253</a>                 break;
<a name="L254" href="source/net/ipv4/tcp_metrics.c#L254">254</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L255" href="source/net/ipv4/tcp_metrics.c#L255">255</a>         case <a href="ident?i=AF_INET6">AF_INET6</a>:
<a name="L256" href="source/net/ipv4/tcp_metrics.c#L256">256</a>                 <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.in6 = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_v6_loc_addr">ir_v6_loc_addr</a>;
<a name="L257" href="source/net/ipv4/tcp_metrics.c#L257">257</a>                 <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.in6 = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_v6_rmt_addr">ir_v6_rmt_addr</a>;
<a name="L258" href="source/net/ipv4/tcp_metrics.c#L258">258</a>                 <a href="ident?i=hash">hash</a> = <a href="ident?i=ipv6_addr_hash">ipv6_addr_hash</a>(&amp;<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_v6_rmt_addr">ir_v6_rmt_addr</a>);
<a name="L259" href="source/net/ipv4/tcp_metrics.c#L259">259</a>                 break;
<a name="L260" href="source/net/ipv4/tcp_metrics.c#L260">260</a> #endif
<a name="L261" href="source/net/ipv4/tcp_metrics.c#L261">261</a>         default:
<a name="L262" href="source/net/ipv4/tcp_metrics.c#L262">262</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L263" href="source/net/ipv4/tcp_metrics.c#L263">263</a>         }
<a name="L264" href="source/net/ipv4/tcp_metrics.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/tcp_metrics.c#L265">265</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L266" href="source/net/ipv4/tcp_metrics.c#L266">266</a>         <a href="ident?i=hash">hash</a> ^= <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>);
<a name="L267" href="source/net/ipv4/tcp_metrics.c#L267">267</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=hash_32">hash_32</a>(<a href="ident?i=hash">hash</a>, tcp_metrics_hash_log);
<a name="L268" href="source/net/ipv4/tcp_metrics.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/tcp_metrics.c#L269">269</a>         for (<a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>); <a href="ident?i=tm">tm</a>;
<a name="L270" href="source/net/ipv4/tcp_metrics.c#L270">270</a>              <a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_next)) {
<a name="L271" href="source/net/ipv4/tcp_metrics.c#L271">271</a>                 if (<a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_saddr, &amp;<a href="ident?i=saddr">saddr</a>) &amp;&amp;
<a name="L272" href="source/net/ipv4/tcp_metrics.c#L272">272</a>                     <a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr, &amp;<a href="ident?i=daddr">daddr</a>) &amp;&amp;
<a name="L273" href="source/net/ipv4/tcp_metrics.c#L273">273</a>                     <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>))
<a name="L274" href="source/net/ipv4/tcp_metrics.c#L274">274</a>                         break;
<a name="L275" href="source/net/ipv4/tcp_metrics.c#L275">275</a>         }
<a name="L276" href="source/net/ipv4/tcp_metrics.c#L276">276</a>         <a href="ident?i=tcpm_check_stamp">tcpm_check_stamp</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=dst">dst</a>);
<a name="L277" href="source/net/ipv4/tcp_metrics.c#L277">277</a>         return <a href="ident?i=tm">tm</a>;
<a name="L278" href="source/net/ipv4/tcp_metrics.c#L278">278</a> }
<a name="L279" href="source/net/ipv4/tcp_metrics.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/tcp_metrics.c#L280">280</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=__tcp_get_metrics_tw">__tcp_get_metrics_tw</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
<a name="L281" href="source/net/ipv4/tcp_metrics.c#L281">281</a> {
<a name="L282" href="source/net/ipv4/tcp_metrics.c#L282">282</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L283" href="source/net/ipv4/tcp_metrics.c#L283">283</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L284" href="source/net/ipv4/tcp_metrics.c#L284">284</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L285" href="source/net/ipv4/tcp_metrics.c#L285">285</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L286" href="source/net/ipv4/tcp_metrics.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/tcp_metrics.c#L287">287</a>         if (<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_family">tw_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L288" href="source/net/ipv4/tcp_metrics.c#L288">288</a>                 <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L289" href="source/net/ipv4/tcp_metrics.c#L289">289</a>                 <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_rcv_saddr">tw_rcv_saddr</a>;
<a name="L290" href="source/net/ipv4/tcp_metrics.c#L290">290</a>                 <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L291" href="source/net/ipv4/tcp_metrics.c#L291">291</a>                 <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_daddr">tw_daddr</a>;
<a name="L292" href="source/net/ipv4/tcp_metrics.c#L292">292</a>                 <a href="ident?i=hash">hash</a> = (<a href="ident?i=__force">__force</a> unsigned int) <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
<a name="L293" href="source/net/ipv4/tcp_metrics.c#L293">293</a>         }
<a name="L294" href="source/net/ipv4/tcp_metrics.c#L294">294</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L295" href="source/net/ipv4/tcp_metrics.c#L295">295</a>         else if (<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_family">tw_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L296" href="source/net/ipv4/tcp_metrics.c#L296">296</a>                 if (<a href="ident?i=ipv6_addr_v4mapped">ipv6_addr_v4mapped</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_v6_daddr">tw_v6_daddr</a>)) {
<a name="L297" href="source/net/ipv4/tcp_metrics.c#L297">297</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L298" href="source/net/ipv4/tcp_metrics.c#L298">298</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_rcv_saddr">tw_rcv_saddr</a>;
<a name="L299" href="source/net/ipv4/tcp_metrics.c#L299">299</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L300" href="source/net/ipv4/tcp_metrics.c#L300">300</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_daddr">tw_daddr</a>;
<a name="L301" href="source/net/ipv4/tcp_metrics.c#L301">301</a>                         <a href="ident?i=hash">hash</a> = (<a href="ident?i=__force">__force</a> unsigned int) <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
<a name="L302" href="source/net/ipv4/tcp_metrics.c#L302">302</a>                 } else {
<a name="L303" href="source/net/ipv4/tcp_metrics.c#L303">303</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L304" href="source/net/ipv4/tcp_metrics.c#L304">304</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.in6 = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_v6_rcv_saddr">tw_v6_rcv_saddr</a>;
<a name="L305" href="source/net/ipv4/tcp_metrics.c#L305">305</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L306" href="source/net/ipv4/tcp_metrics.c#L306">306</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.in6 = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_v6_daddr">tw_v6_daddr</a>;
<a name="L307" href="source/net/ipv4/tcp_metrics.c#L307">307</a>                         <a href="ident?i=hash">hash</a> = <a href="ident?i=ipv6_addr_hash">ipv6_addr_hash</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_v6_daddr">tw_v6_daddr</a>);
<a name="L308" href="source/net/ipv4/tcp_metrics.c#L308">308</a>                 }
<a name="L309" href="source/net/ipv4/tcp_metrics.c#L309">309</a>         }
<a name="L310" href="source/net/ipv4/tcp_metrics.c#L310">310</a> #endif
<a name="L311" href="source/net/ipv4/tcp_metrics.c#L311">311</a>         else
<a name="L312" href="source/net/ipv4/tcp_metrics.c#L312">312</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L313" href="source/net/ipv4/tcp_metrics.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/tcp_metrics.c#L314">314</a>         <a href="ident?i=net">net</a> = <a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>);
<a name="L315" href="source/net/ipv4/tcp_metrics.c#L315">315</a>         <a href="ident?i=hash">hash</a> ^= <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>);
<a name="L316" href="source/net/ipv4/tcp_metrics.c#L316">316</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=hash_32">hash_32</a>(<a href="ident?i=hash">hash</a>, tcp_metrics_hash_log);
<a name="L317" href="source/net/ipv4/tcp_metrics.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/tcp_metrics.c#L318">318</a>         for (<a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>); <a href="ident?i=tm">tm</a>;
<a name="L319" href="source/net/ipv4/tcp_metrics.c#L319">319</a>              <a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_next)) {
<a name="L320" href="source/net/ipv4/tcp_metrics.c#L320">320</a>                 if (<a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_saddr, &amp;<a href="ident?i=saddr">saddr</a>) &amp;&amp;
<a name="L321" href="source/net/ipv4/tcp_metrics.c#L321">321</a>                     <a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr, &amp;<a href="ident?i=daddr">daddr</a>) &amp;&amp;
<a name="L322" href="source/net/ipv4/tcp_metrics.c#L322">322</a>                     <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>))
<a name="L323" href="source/net/ipv4/tcp_metrics.c#L323">323</a>                         break;
<a name="L324" href="source/net/ipv4/tcp_metrics.c#L324">324</a>         }
<a name="L325" href="source/net/ipv4/tcp_metrics.c#L325">325</a>         return <a href="ident?i=tm">tm</a>;
<a name="L326" href="source/net/ipv4/tcp_metrics.c#L326">326</a> }
<a name="L327" href="source/net/ipv4/tcp_metrics.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/tcp_metrics.c#L328">328</a> static struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L329" href="source/net/ipv4/tcp_metrics.c#L329">329</a>                                                  struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L330" href="source/net/ipv4/tcp_metrics.c#L330">330</a>                                                  <a href="ident?i=bool">bool</a> <a href="ident?i=create">create</a>)
<a name="L331" href="source/net/ipv4/tcp_metrics.c#L331">331</a> {
<a name="L332" href="source/net/ipv4/tcp_metrics.c#L332">332</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L333" href="source/net/ipv4/tcp_metrics.c#L333">333</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L334" href="source/net/ipv4/tcp_metrics.c#L334">334</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L335" href="source/net/ipv4/tcp_metrics.c#L335">335</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L336" href="source/net/ipv4/tcp_metrics.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/tcp_metrics.c#L337">337</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L338" href="source/net/ipv4/tcp_metrics.c#L338">338</a>                 <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L339" href="source/net/ipv4/tcp_metrics.c#L339">339</a>                 <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;inet_saddr;
<a name="L340" href="source/net/ipv4/tcp_metrics.c#L340">340</a>                 <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L341" href="source/net/ipv4/tcp_metrics.c#L341">341</a>                 <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L342" href="source/net/ipv4/tcp_metrics.c#L342">342</a>                 <a href="ident?i=hash">hash</a> = (<a href="ident?i=__force">__force</a> unsigned int) <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
<a name="L343" href="source/net/ipv4/tcp_metrics.c#L343">343</a>         }
<a name="L344" href="source/net/ipv4/tcp_metrics.c#L344">344</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L345" href="source/net/ipv4/tcp_metrics.c#L345">345</a>         else if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L346" href="source/net/ipv4/tcp_metrics.c#L346">346</a>                 if (<a href="ident?i=ipv6_addr_v4mapped">ipv6_addr_v4mapped</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>)) {
<a name="L347" href="source/net/ipv4/tcp_metrics.c#L347">347</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L348" href="source/net/ipv4/tcp_metrics.c#L348">348</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;inet_saddr;
<a name="L349" href="source/net/ipv4/tcp_metrics.c#L349">349</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L350" href="source/net/ipv4/tcp_metrics.c#L350">350</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L351" href="source/net/ipv4/tcp_metrics.c#L351">351</a>                         <a href="ident?i=hash">hash</a> = (<a href="ident?i=__force">__force</a> unsigned int) <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
<a name="L352" href="source/net/ipv4/tcp_metrics.c#L352">352</a>                 } else {
<a name="L353" href="source/net/ipv4/tcp_metrics.c#L353">353</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L354" href="source/net/ipv4/tcp_metrics.c#L354">354</a>                         <a href="ident?i=saddr">saddr</a>.<a href="ident?i=addr">addr</a>.in6 = sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>;
<a name="L355" href="source/net/ipv4/tcp_metrics.c#L355">355</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L356" href="source/net/ipv4/tcp_metrics.c#L356">356</a>                         <a href="ident?i=daddr">daddr</a>.<a href="ident?i=addr">addr</a>.in6 = sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>;
<a name="L357" href="source/net/ipv4/tcp_metrics.c#L357">357</a>                         <a href="ident?i=hash">hash</a> = <a href="ident?i=ipv6_addr_hash">ipv6_addr_hash</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>);
<a name="L358" href="source/net/ipv4/tcp_metrics.c#L358">358</a>                 }
<a name="L359" href="source/net/ipv4/tcp_metrics.c#L359">359</a>         }
<a name="L360" href="source/net/ipv4/tcp_metrics.c#L360">360</a> #endif
<a name="L361" href="source/net/ipv4/tcp_metrics.c#L361">361</a>         else
<a name="L362" href="source/net/ipv4/tcp_metrics.c#L362">362</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L363" href="source/net/ipv4/tcp_metrics.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/tcp_metrics.c#L364">364</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L365" href="source/net/ipv4/tcp_metrics.c#L365">365</a>         <a href="ident?i=hash">hash</a> ^= <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>);
<a name="L366" href="source/net/ipv4/tcp_metrics.c#L366">366</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=hash_32">hash_32</a>(<a href="ident?i=hash">hash</a>, tcp_metrics_hash_log);
<a name="L367" href="source/net/ipv4/tcp_metrics.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/tcp_metrics.c#L368">368</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=__tcp_get_metrics">__tcp_get_metrics</a>(&amp;<a href="ident?i=saddr">saddr</a>, &amp;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=net">net</a>, <a href="ident?i=hash">hash</a>);
<a name="L369" href="source/net/ipv4/tcp_metrics.c#L369">369</a>         if (<a href="ident?i=tm">tm</a> == <a href="ident?i=TCP_METRICS_RECLAIM_PTR">TCP_METRICS_RECLAIM_PTR</a>)
<a name="L370" href="source/net/ipv4/tcp_metrics.c#L370">370</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L371" href="source/net/ipv4/tcp_metrics.c#L371">371</a>         if (!<a href="ident?i=tm">tm</a> &amp;&amp; <a href="ident?i=create">create</a>)
<a name="L372" href="source/net/ipv4/tcp_metrics.c#L372">372</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=tcpm_new">tcpm_new</a>(<a href="ident?i=dst">dst</a>, &amp;<a href="ident?i=saddr">saddr</a>, &amp;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=hash">hash</a>);
<a name="L373" href="source/net/ipv4/tcp_metrics.c#L373">373</a>         else
<a name="L374" href="source/net/ipv4/tcp_metrics.c#L374">374</a>                 <a href="ident?i=tcpm_check_stamp">tcpm_check_stamp</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=dst">dst</a>);
<a name="L375" href="source/net/ipv4/tcp_metrics.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/tcp_metrics.c#L376">376</a>         return <a href="ident?i=tm">tm</a>;
<a name="L377" href="source/net/ipv4/tcp_metrics.c#L377">377</a> }
<a name="L378" href="source/net/ipv4/tcp_metrics.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/tcp_metrics.c#L379">379</a> <b><i>/* Save metrics learned by this TCP session.  This function is called</i></b>
<a name="L380" href="source/net/ipv4/tcp_metrics.c#L380">380</a> <b><i> * only, when TCP finishes successfully i.e. when it enters TIME-WAIT</i></b>
<a name="L381" href="source/net/ipv4/tcp_metrics.c#L381">381</a> <b><i> * or goes from LAST-ACK to CLOSE.</i></b>
<a name="L382" href="source/net/ipv4/tcp_metrics.c#L382">382</a> <b><i> */</i></b>
<a name="L383" href="source/net/ipv4/tcp_metrics.c#L383">383</a> void <a href="ident?i=tcp_update_metrics">tcp_update_metrics</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L384" href="source/net/ipv4/tcp_metrics.c#L384">384</a> {
<a name="L385" href="source/net/ipv4/tcp_metrics.c#L385">385</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L386" href="source/net/ipv4/tcp_metrics.c#L386">386</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L387" href="source/net/ipv4/tcp_metrics.c#L387">387</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L388" href="source/net/ipv4/tcp_metrics.c#L388">388</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L389" href="source/net/ipv4/tcp_metrics.c#L389">389</a>         unsigned long rtt;
<a name="L390" href="source/net/ipv4/tcp_metrics.c#L390">390</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a>;
<a name="L391" href="source/net/ipv4/tcp_metrics.c#L391">391</a>         int <a href="ident?i=m">m</a>;
<a name="L392" href="source/net/ipv4/tcp_metrics.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/tcp_metrics.c#L393">393</a>         if (<a href="ident?i=sysctl_tcp_nometrics_save">sysctl_tcp_nometrics_save</a> || !<a href="ident?i=dst">dst</a>)
<a name="L394" href="source/net/ipv4/tcp_metrics.c#L394">394</a>                 return;
<a name="L395" href="source/net/ipv4/tcp_metrics.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/tcp_metrics.c#L396">396</a>         if (<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=DST_HOST">DST_HOST</a>)
<a name="L397" href="source/net/ipv4/tcp_metrics.c#L397">397</a>                 <a href="ident?i=dst_confirm">dst_confirm</a>(<a href="ident?i=dst">dst</a>);
<a name="L398" href="source/net/ipv4/tcp_metrics.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/tcp_metrics.c#L399">399</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L400" href="source/net/ipv4/tcp_metrics.c#L400">400</a>         if (icsk-&gt;icsk_backoff || !<a href="ident?i=tp">tp</a>-&gt;srtt_us) {
<a name="L401" href="source/net/ipv4/tcp_metrics.c#L401">401</a>                 <b><i>/* This session failed to estimate rtt. Why?</i></b>
<a name="L402" href="source/net/ipv4/tcp_metrics.c#L402">402</a> <b><i>                 * Probably, no packets returned in time.  Reset our</i></b>
<a name="L403" href="source/net/ipv4/tcp_metrics.c#L403">403</a> <b><i>                 * results.</i></b>
<a name="L404" href="source/net/ipv4/tcp_metrics.c#L404">404</a> <b><i>                 */</i></b>
<a name="L405" href="source/net/ipv4/tcp_metrics.c#L405">405</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=false">false</a>);
<a name="L406" href="source/net/ipv4/tcp_metrics.c#L406">406</a>                 if (<a href="ident?i=tm">tm</a> &amp;&amp; !<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT))
<a name="L407" href="source/net/ipv4/tcp_metrics.c#L407">407</a>                         <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT, 0);
<a name="L408" href="source/net/ipv4/tcp_metrics.c#L408">408</a>                 goto out_unlock;
<a name="L409" href="source/net/ipv4/tcp_metrics.c#L409">409</a>         } else
<a name="L410" href="source/net/ipv4/tcp_metrics.c#L410">410</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L411" href="source/net/ipv4/tcp_metrics.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/tcp_metrics.c#L412">412</a>         if (!<a href="ident?i=tm">tm</a>)
<a name="L413" href="source/net/ipv4/tcp_metrics.c#L413">413</a>                 goto out_unlock;
<a name="L414" href="source/net/ipv4/tcp_metrics.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/tcp_metrics.c#L415">415</a>         rtt = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT);
<a name="L416" href="source/net/ipv4/tcp_metrics.c#L416">416</a>         <a href="ident?i=m">m</a> = rtt - <a href="ident?i=tp">tp</a>-&gt;srtt_us;
<a name="L417" href="source/net/ipv4/tcp_metrics.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/tcp_metrics.c#L418">418</a>         <b><i>/* If newly calculated rtt larger than stored one, store new</i></b>
<a name="L419" href="source/net/ipv4/tcp_metrics.c#L419">419</a> <b><i>         * one. Otherwise, use EWMA. Remember, rtt overestimation is</i></b>
<a name="L420" href="source/net/ipv4/tcp_metrics.c#L420">420</a> <b><i>         * always better than underestimation.</i></b>
<a name="L421" href="source/net/ipv4/tcp_metrics.c#L421">421</a> <b><i>         */</i></b>
<a name="L422" href="source/net/ipv4/tcp_metrics.c#L422">422</a>         if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT)) {
<a name="L423" href="source/net/ipv4/tcp_metrics.c#L423">423</a>                 if (<a href="ident?i=m">m</a> &lt;= 0)
<a name="L424" href="source/net/ipv4/tcp_metrics.c#L424">424</a>                         rtt = <a href="ident?i=tp">tp</a>-&gt;srtt_us;
<a name="L425" href="source/net/ipv4/tcp_metrics.c#L425">425</a>                 else
<a name="L426" href="source/net/ipv4/tcp_metrics.c#L426">426</a>                         rtt -= (<a href="ident?i=m">m</a> &gt;&gt; 3);
<a name="L427" href="source/net/ipv4/tcp_metrics.c#L427">427</a>                 <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT, rtt);
<a name="L428" href="source/net/ipv4/tcp_metrics.c#L428">428</a>         }
<a name="L429" href="source/net/ipv4/tcp_metrics.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/tcp_metrics.c#L430">430</a>         if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTTVAR)) {
<a name="L431" href="source/net/ipv4/tcp_metrics.c#L431">431</a>                 unsigned long <a href="ident?i=var">var</a>;
<a name="L432" href="source/net/ipv4/tcp_metrics.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/tcp_metrics.c#L433">433</a>                 if (<a href="ident?i=m">m</a> &lt; 0)
<a name="L434" href="source/net/ipv4/tcp_metrics.c#L434">434</a>                         <a href="ident?i=m">m</a> = -<a href="ident?i=m">m</a>;
<a name="L435" href="source/net/ipv4/tcp_metrics.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/tcp_metrics.c#L436">436</a>                 <b><i>/* Scale deviation to rttvar fixed point */</i></b>
<a name="L437" href="source/net/ipv4/tcp_metrics.c#L437">437</a>                 <a href="ident?i=m">m</a> &gt;&gt;= 1;
<a name="L438" href="source/net/ipv4/tcp_metrics.c#L438">438</a>                 if (<a href="ident?i=m">m</a> &lt; <a href="ident?i=tp">tp</a>-&gt;mdev_us)
<a name="L439" href="source/net/ipv4/tcp_metrics.c#L439">439</a>                         <a href="ident?i=m">m</a> = <a href="ident?i=tp">tp</a>-&gt;mdev_us;
<a name="L440" href="source/net/ipv4/tcp_metrics.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/tcp_metrics.c#L441">441</a>                 <a href="ident?i=var">var</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTTVAR);
<a name="L442" href="source/net/ipv4/tcp_metrics.c#L442">442</a>                 if (<a href="ident?i=m">m</a> &gt;= <a href="ident?i=var">var</a>)
<a name="L443" href="source/net/ipv4/tcp_metrics.c#L443">443</a>                         <a href="ident?i=var">var</a> = <a href="ident?i=m">m</a>;
<a name="L444" href="source/net/ipv4/tcp_metrics.c#L444">444</a>                 else
<a name="L445" href="source/net/ipv4/tcp_metrics.c#L445">445</a>                         <a href="ident?i=var">var</a> -= (<a href="ident?i=var">var</a> - <a href="ident?i=m">m</a>) &gt;&gt; 2;
<a name="L446" href="source/net/ipv4/tcp_metrics.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/tcp_metrics.c#L447">447</a>                 <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTTVAR, <a href="ident?i=var">var</a>);
<a name="L448" href="source/net/ipv4/tcp_metrics.c#L448">448</a>         }
<a name="L449" href="source/net/ipv4/tcp_metrics.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/tcp_metrics.c#L450">450</a>         if (<a href="ident?i=tcp_in_initial_slowstart">tcp_in_initial_slowstart</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L451" href="source/net/ipv4/tcp_metrics.c#L451">451</a>                 <b><i>/* Slow start still did not finish. */</i></b>
<a name="L452" href="source/net/ipv4/tcp_metrics.c#L452">452</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH)) {
<a name="L453" href="source/net/ipv4/tcp_metrics.c#L453">453</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH);
<a name="L454" href="source/net/ipv4/tcp_metrics.c#L454">454</a>                         if (<a href="ident?i=val">val</a> &amp;&amp; (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1) &gt; <a href="ident?i=val">val</a>)
<a name="L455" href="source/net/ipv4/tcp_metrics.c#L455">455</a>                                 <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH,
<a name="L456" href="source/net/ipv4/tcp_metrics.c#L456">456</a>                                                <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1);
<a name="L457" href="source/net/ipv4/tcp_metrics.c#L457">457</a>                 }
<a name="L458" href="source/net/ipv4/tcp_metrics.c#L458">458</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND)) {
<a name="L459" href="source/net/ipv4/tcp_metrics.c#L459">459</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND);
<a name="L460" href="source/net/ipv4/tcp_metrics.c#L460">460</a>                         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=val">val</a>)
<a name="L461" href="source/net/ipv4/tcp_metrics.c#L461">461</a>                                 <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND,
<a name="L462" href="source/net/ipv4/tcp_metrics.c#L462">462</a>                                                <a href="ident?i=tp">tp</a>-&gt;snd_cwnd);
<a name="L463" href="source/net/ipv4/tcp_metrics.c#L463">463</a>                 }
<a name="L464" href="source/net/ipv4/tcp_metrics.c#L464">464</a>         } else if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &amp;&amp;
<a name="L465" href="source/net/ipv4/tcp_metrics.c#L465">465</a>                    icsk-&gt;icsk_ca_state == TCP_CA_Open) {
<a name="L466" href="source/net/ipv4/tcp_metrics.c#L466">466</a>                 <b><i>/* Cong. avoidance phase, cwnd is reliable. */</i></b>
<a name="L467" href="source/net/ipv4/tcp_metrics.c#L467">467</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH))
<a name="L468" href="source/net/ipv4/tcp_metrics.c#L468">468</a>                         <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH,
<a name="L469" href="source/net/ipv4/tcp_metrics.c#L469">469</a>                                        <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1, <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh));
<a name="L470" href="source/net/ipv4/tcp_metrics.c#L470">470</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND)) {
<a name="L471" href="source/net/ipv4/tcp_metrics.c#L471">471</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND);
<a name="L472" href="source/net/ipv4/tcp_metrics.c#L472">472</a>                         <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND, (<a href="ident?i=val">val</a> + <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) &gt;&gt; 1);
<a name="L473" href="source/net/ipv4/tcp_metrics.c#L473">473</a>                 }
<a name="L474" href="source/net/ipv4/tcp_metrics.c#L474">474</a>         } else {
<a name="L475" href="source/net/ipv4/tcp_metrics.c#L475">475</a>                 <b><i>/* Else slow start did not finish, cwnd is non-sense,</i></b>
<a name="L476" href="source/net/ipv4/tcp_metrics.c#L476">476</a> <b><i>                 * ssthresh may be also invalid.</i></b>
<a name="L477" href="source/net/ipv4/tcp_metrics.c#L477">477</a> <b><i>                 */</i></b>
<a name="L478" href="source/net/ipv4/tcp_metrics.c#L478">478</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND)) {
<a name="L479" href="source/net/ipv4/tcp_metrics.c#L479">479</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND);
<a name="L480" href="source/net/ipv4/tcp_metrics.c#L480">480</a>                         <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND,
<a name="L481" href="source/net/ipv4/tcp_metrics.c#L481">481</a>                                        (<a href="ident?i=val">val</a> + <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) &gt;&gt; 1);
<a name="L482" href="source/net/ipv4/tcp_metrics.c#L482">482</a>                 }
<a name="L483" href="source/net/ipv4/tcp_metrics.c#L483">483</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH)) {
<a name="L484" href="source/net/ipv4/tcp_metrics.c#L484">484</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH);
<a name="L485" href="source/net/ipv4/tcp_metrics.c#L485">485</a>                         if (<a href="ident?i=val">val</a> &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &gt; <a href="ident?i=val">val</a>)
<a name="L486" href="source/net/ipv4/tcp_metrics.c#L486">486</a>                                 <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH,
<a name="L487" href="source/net/ipv4/tcp_metrics.c#L487">487</a>                                                <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh);
<a name="L488" href="source/net/ipv4/tcp_metrics.c#L488">488</a>                 }
<a name="L489" href="source/net/ipv4/tcp_metrics.c#L489">489</a>                 if (!<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_REORDERING)) {
<a name="L490" href="source/net/ipv4/tcp_metrics.c#L490">490</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_REORDERING);
<a name="L491" href="source/net/ipv4/tcp_metrics.c#L491">491</a>                         if (<a href="ident?i=val">val</a> &lt; <a href="ident?i=tp">tp</a>-&gt;reordering &amp;&amp;
<a name="L492" href="source/net/ipv4/tcp_metrics.c#L492">492</a>                             <a href="ident?i=tp">tp</a>-&gt;reordering != <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>)
<a name="L493" href="source/net/ipv4/tcp_metrics.c#L493">493</a>                                 <a href="ident?i=tcp_metric_set">tcp_metric_set</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_REORDERING,
<a name="L494" href="source/net/ipv4/tcp_metrics.c#L494">494</a>                                                <a href="ident?i=tp">tp</a>-&gt;reordering);
<a name="L495" href="source/net/ipv4/tcp_metrics.c#L495">495</a>                 }
<a name="L496" href="source/net/ipv4/tcp_metrics.c#L496">496</a>         }
<a name="L497" href="source/net/ipv4/tcp_metrics.c#L497">497</a>         <a href="ident?i=tm">tm</a>-&gt;tcpm_stamp = <a href="ident?i=jiffies">jiffies</a>;
<a name="L498" href="source/net/ipv4/tcp_metrics.c#L498">498</a> out_unlock:
<a name="L499" href="source/net/ipv4/tcp_metrics.c#L499">499</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L500" href="source/net/ipv4/tcp_metrics.c#L500">500</a> }
<a name="L501" href="source/net/ipv4/tcp_metrics.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/tcp_metrics.c#L502">502</a> <b><i>/* Initialize metrics on socket. */</i></b>
<a name="L503" href="source/net/ipv4/tcp_metrics.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/tcp_metrics.c#L504">504</a> void <a href="ident?i=tcp_init_metrics">tcp_init_metrics</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L505" href="source/net/ipv4/tcp_metrics.c#L505">505</a> {
<a name="L506" href="source/net/ipv4/tcp_metrics.c#L506">506</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L507" href="source/net/ipv4/tcp_metrics.c#L507">507</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L508" href="source/net/ipv4/tcp_metrics.c#L508">508</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L509" href="source/net/ipv4/tcp_metrics.c#L509">509</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a>, crtt = 0; <b><i>/* cached RTT scaled by 8 */</i></b>
<a name="L510" href="source/net/ipv4/tcp_metrics.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/tcp_metrics.c#L511">511</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L512" href="source/net/ipv4/tcp_metrics.c#L512">512</a>                 goto <a href="ident?i=reset">reset</a>;
<a name="L513" href="source/net/ipv4/tcp_metrics.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/tcp_metrics.c#L514">514</a>         <a href="ident?i=dst_confirm">dst_confirm</a>(<a href="ident?i=dst">dst</a>);
<a name="L515" href="source/net/ipv4/tcp_metrics.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/tcp_metrics.c#L516">516</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L517" href="source/net/ipv4/tcp_metrics.c#L517">517</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L518" href="source/net/ipv4/tcp_metrics.c#L518">518</a>         if (!<a href="ident?i=tm">tm</a>) {
<a name="L519" href="source/net/ipv4/tcp_metrics.c#L519">519</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L520" href="source/net/ipv4/tcp_metrics.c#L520">520</a>                 goto <a href="ident?i=reset">reset</a>;
<a name="L521" href="source/net/ipv4/tcp_metrics.c#L521">521</a>         }
<a name="L522" href="source/net/ipv4/tcp_metrics.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/tcp_metrics.c#L523">523</a>         if (<a href="ident?i=tcp_metric_locked">tcp_metric_locked</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND))
<a name="L524" href="source/net/ipv4/tcp_metrics.c#L524">524</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_CWND);
<a name="L525" href="source/net/ipv4/tcp_metrics.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/tcp_metrics.c#L526">526</a>         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_SSTHRESH);
<a name="L527" href="source/net/ipv4/tcp_metrics.c#L527">527</a>         if (<a href="ident?i=val">val</a>) {
<a name="L528" href="source/net/ipv4/tcp_metrics.c#L528">528</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=val">val</a>;
<a name="L529" href="source/net/ipv4/tcp_metrics.c#L529">529</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &gt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp)
<a name="L530" href="source/net/ipv4/tcp_metrics.c#L530">530</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp;
<a name="L531" href="source/net/ipv4/tcp_metrics.c#L531">531</a>         } else {
<a name="L532" href="source/net/ipv4/tcp_metrics.c#L532">532</a>                 <b><i>/* ssthresh may have been reduced unnecessarily during.</i></b>
<a name="L533" href="source/net/ipv4/tcp_metrics.c#L533">533</a> <b><i>                 * 3WHS. Restore it back to its initial default.</i></b>
<a name="L534" href="source/net/ipv4/tcp_metrics.c#L534">534</a> <b><i>                 */</i></b>
<a name="L535" href="source/net/ipv4/tcp_metrics.c#L535">535</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=TCP_INFINITE_SSTHRESH">TCP_INFINITE_SSTHRESH</a>;
<a name="L536" href="source/net/ipv4/tcp_metrics.c#L536">536</a>         }
<a name="L537" href="source/net/ipv4/tcp_metrics.c#L537">537</a>         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_REORDERING);
<a name="L538" href="source/net/ipv4/tcp_metrics.c#L538">538</a>         if (<a href="ident?i=val">val</a> &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;reordering != <a href="ident?i=val">val</a>) {
<a name="L539" href="source/net/ipv4/tcp_metrics.c#L539">539</a>                 <a href="ident?i=tcp_disable_fack">tcp_disable_fack</a>(<a href="ident?i=tp">tp</a>);
<a name="L540" href="source/net/ipv4/tcp_metrics.c#L540">540</a>                 <a href="ident?i=tcp_disable_early_retrans">tcp_disable_early_retrans</a>(<a href="ident?i=tp">tp</a>);
<a name="L541" href="source/net/ipv4/tcp_metrics.c#L541">541</a>                 <a href="ident?i=tp">tp</a>-&gt;reordering = <a href="ident?i=val">val</a>;
<a name="L542" href="source/net/ipv4/tcp_metrics.c#L542">542</a>         }
<a name="L543" href="source/net/ipv4/tcp_metrics.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/tcp_metrics.c#L544">544</a>         crtt = <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT);
<a name="L545" href="source/net/ipv4/tcp_metrics.c#L545">545</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L546" href="source/net/ipv4/tcp_metrics.c#L546">546</a> <a href="ident?i=reset">reset</a>:
<a name="L547" href="source/net/ipv4/tcp_metrics.c#L547">547</a>         <b><i>/* The initial RTT measurement from the SYN/SYN-ACK is not ideal</i></b>
<a name="L548" href="source/net/ipv4/tcp_metrics.c#L548">548</a> <b><i>         * to seed the RTO for later data packets because SYN packets are</i></b>
<a name="L549" href="source/net/ipv4/tcp_metrics.c#L549">549</a> <b><i>         * small. Use the per-dst cached values to seed the RTO but keep</i></b>
<a name="L550" href="source/net/ipv4/tcp_metrics.c#L550">550</a> <b><i>         * the RTT estimator variables intact (e.g., srtt, mdev, rttvar).</i></b>
<a name="L551" href="source/net/ipv4/tcp_metrics.c#L551">551</a> <b><i>         * Later the RTO will be updated immediately upon obtaining the first</i></b>
<a name="L552" href="source/net/ipv4/tcp_metrics.c#L552">552</a> <b><i>         * data RTT sample (tcp_rtt_estimator()). Hence the cached RTT only</i></b>
<a name="L553" href="source/net/ipv4/tcp_metrics.c#L553">553</a> <b><i>         * influences the first RTO but not later RTT estimation.</i></b>
<a name="L554" href="source/net/ipv4/tcp_metrics.c#L554">554</a> <b><i>         *</i></b>
<a name="L555" href="source/net/ipv4/tcp_metrics.c#L555">555</a> <b><i>         * But if RTT is not available from the SYN (due to retransmits or</i></b>
<a name="L556" href="source/net/ipv4/tcp_metrics.c#L556">556</a> <b><i>         * syn cookies) or the cache, force a conservative 3secs timeout.</i></b>
<a name="L557" href="source/net/ipv4/tcp_metrics.c#L557">557</a> <b><i>         *</i></b>
<a name="L558" href="source/net/ipv4/tcp_metrics.c#L558">558</a> <b><i>         * A bit of theory. RTT is time passed after "normal" sized packet</i></b>
<a name="L559" href="source/net/ipv4/tcp_metrics.c#L559">559</a> <b><i>         * is sent until it is ACKed. In normal circumstances sending small</i></b>
<a name="L560" href="source/net/ipv4/tcp_metrics.c#L560">560</a> <b><i>         * packets force peer to delay ACKs and calculation is correct too.</i></b>
<a name="L561" href="source/net/ipv4/tcp_metrics.c#L561">561</a> <b><i>         * The algorithm is adaptive and, provided we follow specs, it</i></b>
<a name="L562" href="source/net/ipv4/tcp_metrics.c#L562">562</a> <b><i>         * NEVER underestimate RTT. BUT! If peer tries to make some clever</i></b>
<a name="L563" href="source/net/ipv4/tcp_metrics.c#L563">563</a> <b><i>         * tricks sort of "quick acks" for time long enough to decrease RTT</i></b>
<a name="L564" href="source/net/ipv4/tcp_metrics.c#L564">564</a> <b><i>         * to low value, and then abruptly stops to do it and starts to delay</i></b>
<a name="L565" href="source/net/ipv4/tcp_metrics.c#L565">565</a> <b><i>         * ACKs, wait for troubles.</i></b>
<a name="L566" href="source/net/ipv4/tcp_metrics.c#L566">566</a> <b><i>         */</i></b>
<a name="L567" href="source/net/ipv4/tcp_metrics.c#L567">567</a>         if (crtt &gt; <a href="ident?i=tp">tp</a>-&gt;srtt_us) {
<a name="L568" href="source/net/ipv4/tcp_metrics.c#L568">568</a>                 <b><i>/* Set RTO like tcp_rtt_estimator(), but from cached RTT. */</i></b>
<a name="L569" href="source/net/ipv4/tcp_metrics.c#L569">569</a>                 crtt /= 8 * <a href="ident?i=USEC_PER_MSEC">USEC_PER_MSEC</a>;
<a name="L570" href="source/net/ipv4/tcp_metrics.c#L570">570</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto = crtt + <a href="ident?i=max">max</a>(2 * crtt, <a href="ident?i=tcp_rto_min">tcp_rto_min</a>(sk));
<a name="L571" href="source/net/ipv4/tcp_metrics.c#L571">571</a>         } else if (<a href="ident?i=tp">tp</a>-&gt;srtt_us == 0) {
<a name="L572" href="source/net/ipv4/tcp_metrics.c#L572">572</a>                 <b><i>/* RFC6298: 5.7 We've failed to get a valid RTT sample from</i></b>
<a name="L573" href="source/net/ipv4/tcp_metrics.c#L573">573</a> <b><i>                 * 3WHS. This is most likely due to retransmission,</i></b>
<a name="L574" href="source/net/ipv4/tcp_metrics.c#L574">574</a> <b><i>                 * including spurious one. Reset the RTO back to 3secs</i></b>
<a name="L575" href="source/net/ipv4/tcp_metrics.c#L575">575</a> <b><i>                 * from the more aggressive 1sec to avoid more spurious</i></b>
<a name="L576" href="source/net/ipv4/tcp_metrics.c#L576">576</a> <b><i>                 * retransmission.</i></b>
<a name="L577" href="source/net/ipv4/tcp_metrics.c#L577">577</a> <b><i>                 */</i></b>
<a name="L578" href="source/net/ipv4/tcp_metrics.c#L578">578</a>                 <a href="ident?i=tp">tp</a>-&gt;rttvar_us = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=TCP_TIMEOUT_FALLBACK">TCP_TIMEOUT_FALLBACK</a>);
<a name="L579" href="source/net/ipv4/tcp_metrics.c#L579">579</a>                 <a href="ident?i=tp">tp</a>-&gt;mdev_us = <a href="ident?i=tp">tp</a>-&gt;mdev_max_us = <a href="ident?i=tp">tp</a>-&gt;rttvar_us;
<a name="L580" href="source/net/ipv4/tcp_metrics.c#L580">580</a> 
<a name="L581" href="source/net/ipv4/tcp_metrics.c#L581">581</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto = <a href="ident?i=TCP_TIMEOUT_FALLBACK">TCP_TIMEOUT_FALLBACK</a>;
<a name="L582" href="source/net/ipv4/tcp_metrics.c#L582">582</a>         }
<a name="L583" href="source/net/ipv4/tcp_metrics.c#L583">583</a>         <b><i>/* Cut cwnd down to 1 per RFC5681 if SYN or SYN-ACK has been</i></b>
<a name="L584" href="source/net/ipv4/tcp_metrics.c#L584">584</a> <b><i>         * retransmitted. In light of RFC6298 more aggressive 1sec</i></b>
<a name="L585" href="source/net/ipv4/tcp_metrics.c#L585">585</a> <b><i>         * initRTO, we only reset cwnd when more than 1 SYN/SYN-ACK</i></b>
<a name="L586" href="source/net/ipv4/tcp_metrics.c#L586">586</a> <b><i>         * retransmission has occurred.</i></b>
<a name="L587" href="source/net/ipv4/tcp_metrics.c#L587">587</a> <b><i>         */</i></b>
<a name="L588" href="source/net/ipv4/tcp_metrics.c#L588">588</a>         if (<a href="ident?i=tp">tp</a>-&gt;total_retrans &gt; 1)
<a name="L589" href="source/net/ipv4/tcp_metrics.c#L589">589</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = 1;
<a name="L590" href="source/net/ipv4/tcp_metrics.c#L590">590</a>         else
<a name="L591" href="source/net/ipv4/tcp_metrics.c#L591">591</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tcp_init_cwnd">tcp_init_cwnd</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=dst">dst</a>);
<a name="L592" href="source/net/ipv4/tcp_metrics.c#L592">592</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L593" href="source/net/ipv4/tcp_metrics.c#L593">593</a> }
<a name="L594" href="source/net/ipv4/tcp_metrics.c#L594">594</a> 
<a name="L595" href="source/net/ipv4/tcp_metrics.c#L595">595</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_peer_is_proven">tcp_peer_is_proven</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L596" href="source/net/ipv4/tcp_metrics.c#L596">596</a>                         <a href="ident?i=bool">bool</a> paws_check, <a href="ident?i=bool">bool</a> timestamps)
<a name="L597" href="source/net/ipv4/tcp_metrics.c#L597">597</a> {
<a name="L598" href="source/net/ipv4/tcp_metrics.c#L598">598</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L599" href="source/net/ipv4/tcp_metrics.c#L599">599</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a>;
<a name="L600" href="source/net/ipv4/tcp_metrics.c#L600">600</a> 
<a name="L601" href="source/net/ipv4/tcp_metrics.c#L601">601</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L602" href="source/net/ipv4/tcp_metrics.c#L602">602</a>                 return <a href="ident?i=false">false</a>;
<a name="L603" href="source/net/ipv4/tcp_metrics.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/tcp_metrics.c#L604">604</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L605" href="source/net/ipv4/tcp_metrics.c#L605">605</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=__tcp_get_metrics_req">__tcp_get_metrics_req</a>(<a href="ident?i=req">req</a>, <a href="ident?i=dst">dst</a>);
<a name="L606" href="source/net/ipv4/tcp_metrics.c#L606">606</a>         if (paws_check) {
<a name="L607" href="source/net/ipv4/tcp_metrics.c#L607">607</a>                 if (<a href="ident?i=tm">tm</a> &amp;&amp;
<a name="L608" href="source/net/ipv4/tcp_metrics.c#L608">608</a>                     (<a href="ident?i=u32">u32</a>)<a href="ident?i=get_seconds">get_seconds</a>() - <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp &lt; <a href="ident?i=TCP_PAWS_MSL">TCP_PAWS_MSL</a> &amp;&amp;
<a name="L609" href="source/net/ipv4/tcp_metrics.c#L609">609</a>                     ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tm">tm</a>-&gt;tcpm_ts - <a href="ident?i=req">req</a>-&gt;ts_recent) &gt; <a href="ident?i=TCP_PAWS_WINDOW">TCP_PAWS_WINDOW</a> ||
<a name="L610" href="source/net/ipv4/tcp_metrics.c#L610">610</a>                      !timestamps))
<a name="L611" href="source/net/ipv4/tcp_metrics.c#L611">611</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L612" href="source/net/ipv4/tcp_metrics.c#L612">612</a>                 else
<a name="L613" href="source/net/ipv4/tcp_metrics.c#L613">613</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L614" href="source/net/ipv4/tcp_metrics.c#L614">614</a>         } else {
<a name="L615" href="source/net/ipv4/tcp_metrics.c#L615">615</a>                 if (<a href="ident?i=tm">tm</a> &amp;&amp; <a href="ident?i=tcp_metric_get">tcp_metric_get</a>(<a href="ident?i=tm">tm</a>, TCP_METRIC_RTT) &amp;&amp; <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp)
<a name="L616" href="source/net/ipv4/tcp_metrics.c#L616">616</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L617" href="source/net/ipv4/tcp_metrics.c#L617">617</a>                 else
<a name="L618" href="source/net/ipv4/tcp_metrics.c#L618">618</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L619" href="source/net/ipv4/tcp_metrics.c#L619">619</a>         }
<a name="L620" href="source/net/ipv4/tcp_metrics.c#L620">620</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L621" href="source/net/ipv4/tcp_metrics.c#L621">621</a> 
<a name="L622" href="source/net/ipv4/tcp_metrics.c#L622">622</a>         return <a href="ident?i=ret">ret</a>;
<a name="L623" href="source/net/ipv4/tcp_metrics.c#L623">623</a> }
<a name="L624" href="source/net/ipv4/tcp_metrics.c#L624">624</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_peer_is_proven">tcp_peer_is_proven</a>);
<a name="L625" href="source/net/ipv4/tcp_metrics.c#L625">625</a> 
<a name="L626" href="source/net/ipv4/tcp_metrics.c#L626">626</a> void <a href="ident?i=tcp_fetch_timewait_stamp">tcp_fetch_timewait_stamp</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L627" href="source/net/ipv4/tcp_metrics.c#L627">627</a> {
<a name="L628" href="source/net/ipv4/tcp_metrics.c#L628">628</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L629" href="source/net/ipv4/tcp_metrics.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/tcp_metrics.c#L630">630</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L631" href="source/net/ipv4/tcp_metrics.c#L631">631</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L632" href="source/net/ipv4/tcp_metrics.c#L632">632</a>         if (<a href="ident?i=tm">tm</a>) {
<a name="L633" href="source/net/ipv4/tcp_metrics.c#L633">633</a>                 struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L634" href="source/net/ipv4/tcp_metrics.c#L634">634</a> 
<a name="L635" href="source/net/ipv4/tcp_metrics.c#L635">635</a>                 if ((<a href="ident?i=u32">u32</a>)<a href="ident?i=get_seconds">get_seconds</a>() - <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp &lt;= <a href="ident?i=TCP_PAWS_MSL">TCP_PAWS_MSL</a>) {
<a name="L636" href="source/net/ipv4/tcp_metrics.c#L636">636</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp = <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp;
<a name="L637" href="source/net/ipv4/tcp_metrics.c#L637">637</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent = <a href="ident?i=tm">tm</a>-&gt;tcpm_ts;
<a name="L638" href="source/net/ipv4/tcp_metrics.c#L638">638</a>                 }
<a name="L639" href="source/net/ipv4/tcp_metrics.c#L639">639</a>         }
<a name="L640" href="source/net/ipv4/tcp_metrics.c#L640">640</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L641" href="source/net/ipv4/tcp_metrics.c#L641">641</a> }
<a name="L642" href="source/net/ipv4/tcp_metrics.c#L642">642</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_fetch_timewait_stamp">tcp_fetch_timewait_stamp</a>);
<a name="L643" href="source/net/ipv4/tcp_metrics.c#L643">643</a> 
<a name="L644" href="source/net/ipv4/tcp_metrics.c#L644">644</a> <b><i>/* VJ's idea. Save last timestamp seen from this destination and hold</i></b>
<a name="L645" href="source/net/ipv4/tcp_metrics.c#L645">645</a> <b><i> * it at least for normal timewait interval to use for duplicate</i></b>
<a name="L646" href="source/net/ipv4/tcp_metrics.c#L646">646</a> <b><i> * segment detection in subsequent connections, before they enter</i></b>
<a name="L647" href="source/net/ipv4/tcp_metrics.c#L647">647</a> <b><i> * synchronized state.</i></b>
<a name="L648" href="source/net/ipv4/tcp_metrics.c#L648">648</a> <b><i> */</i></b>
<a name="L649" href="source/net/ipv4/tcp_metrics.c#L649">649</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_remember_stamp">tcp_remember_stamp</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L650" href="source/net/ipv4/tcp_metrics.c#L650">650</a> {
<a name="L651" href="source/net/ipv4/tcp_metrics.c#L651">651</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L652" href="source/net/ipv4/tcp_metrics.c#L652">652</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L653" href="source/net/ipv4/tcp_metrics.c#L653">653</a> 
<a name="L654" href="source/net/ipv4/tcp_metrics.c#L654">654</a>         if (<a href="ident?i=dst">dst</a>) {
<a name="L655" href="source/net/ipv4/tcp_metrics.c#L655">655</a>                 struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L656" href="source/net/ipv4/tcp_metrics.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/tcp_metrics.c#L657">657</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L658" href="source/net/ipv4/tcp_metrics.c#L658">658</a>                 <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L659" href="source/net/ipv4/tcp_metrics.c#L659">659</a>                 if (<a href="ident?i=tm">tm</a>) {
<a name="L660" href="source/net/ipv4/tcp_metrics.c#L660">660</a>                         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L661" href="source/net/ipv4/tcp_metrics.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/tcp_metrics.c#L662">662</a>                         if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tm">tm</a>-&gt;tcpm_ts - <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent) &lt;= 0 ||
<a name="L663" href="source/net/ipv4/tcp_metrics.c#L663">663</a>                             ((<a href="ident?i=u32">u32</a>)<a href="ident?i=get_seconds">get_seconds</a>() - <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp &gt; <a href="ident?i=TCP_PAWS_MSL">TCP_PAWS_MSL</a> &amp;&amp;
<a name="L664" href="source/net/ipv4/tcp_metrics.c#L664">664</a>                              <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp &lt;= (<a href="ident?i=u32">u32</a>)<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp)) {
<a name="L665" href="source/net/ipv4/tcp_metrics.c#L665">665</a>                                 <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp = (<a href="ident?i=u32">u32</a>)<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp;
<a name="L666" href="source/net/ipv4/tcp_metrics.c#L666">666</a>                                 <a href="ident?i=tm">tm</a>-&gt;tcpm_ts = <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent;
<a name="L667" href="source/net/ipv4/tcp_metrics.c#L667">667</a>                         }
<a name="L668" href="source/net/ipv4/tcp_metrics.c#L668">668</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L669" href="source/net/ipv4/tcp_metrics.c#L669">669</a>                 }
<a name="L670" href="source/net/ipv4/tcp_metrics.c#L670">670</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L671" href="source/net/ipv4/tcp_metrics.c#L671">671</a>         }
<a name="L672" href="source/net/ipv4/tcp_metrics.c#L672">672</a>         return <a href="ident?i=ret">ret</a>;
<a name="L673" href="source/net/ipv4/tcp_metrics.c#L673">673</a> }
<a name="L674" href="source/net/ipv4/tcp_metrics.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/tcp_metrics.c#L675">675</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_tw_remember_stamp">tcp_tw_remember_stamp</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
<a name="L676" href="source/net/ipv4/tcp_metrics.c#L676">676</a> {
<a name="L677" href="source/net/ipv4/tcp_metrics.c#L677">677</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L678" href="source/net/ipv4/tcp_metrics.c#L678">678</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L679" href="source/net/ipv4/tcp_metrics.c#L679">679</a> 
<a name="L680" href="source/net/ipv4/tcp_metrics.c#L680">680</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L681" href="source/net/ipv4/tcp_metrics.c#L681">681</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=__tcp_get_metrics_tw">__tcp_get_metrics_tw</a>(<a href="ident?i=tw">tw</a>);
<a name="L682" href="source/net/ipv4/tcp_metrics.c#L682">682</a>         if (<a href="ident?i=tm">tm</a>) {
<a name="L683" href="source/net/ipv4/tcp_metrics.c#L683">683</a>                 const struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *tcptw;
<a name="L684" href="source/net/ipv4/tcp_metrics.c#L684">684</a>                 struct <a href="ident?i=sock">sock</a> *sk = (struct <a href="ident?i=sock">sock</a> *) <a href="ident?i=tw">tw</a>;
<a name="L685" href="source/net/ipv4/tcp_metrics.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/tcp_metrics.c#L686">686</a>                 tcptw = <a href="ident?i=tcp_twsk">tcp_twsk</a>(sk);
<a name="L687" href="source/net/ipv4/tcp_metrics.c#L687">687</a>                 if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tm">tm</a>-&gt;tcpm_ts - tcptw-&gt;tw_ts_recent) &lt;= 0 ||
<a name="L688" href="source/net/ipv4/tcp_metrics.c#L688">688</a>                     ((<a href="ident?i=u32">u32</a>)<a href="ident?i=get_seconds">get_seconds</a>() - <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp &gt; <a href="ident?i=TCP_PAWS_MSL">TCP_PAWS_MSL</a> &amp;&amp;
<a name="L689" href="source/net/ipv4/tcp_metrics.c#L689">689</a>                      <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp &lt;= (<a href="ident?i=u32">u32</a>)tcptw-&gt;tw_ts_recent_stamp)) {
<a name="L690" href="source/net/ipv4/tcp_metrics.c#L690">690</a>                         <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp = (<a href="ident?i=u32">u32</a>)tcptw-&gt;tw_ts_recent_stamp;
<a name="L691" href="source/net/ipv4/tcp_metrics.c#L691">691</a>                         <a href="ident?i=tm">tm</a>-&gt;tcpm_ts        = tcptw-&gt;tw_ts_recent;
<a name="L692" href="source/net/ipv4/tcp_metrics.c#L692">692</a>                 }
<a name="L693" href="source/net/ipv4/tcp_metrics.c#L693">693</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L694" href="source/net/ipv4/tcp_metrics.c#L694">694</a>         }
<a name="L695" href="source/net/ipv4/tcp_metrics.c#L695">695</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L696" href="source/net/ipv4/tcp_metrics.c#L696">696</a> 
<a name="L697" href="source/net/ipv4/tcp_metrics.c#L697">697</a>         return <a href="ident?i=ret">ret</a>;
<a name="L698" href="source/net/ipv4/tcp_metrics.c#L698">698</a> }
<a name="L699" href="source/net/ipv4/tcp_metrics.c#L699">699</a> 
<a name="L700" href="source/net/ipv4/tcp_metrics.c#L700">700</a> static <a href="ident?i=DEFINE_SEQLOCK">DEFINE_SEQLOCK</a>(fastopen_seqlock);
<a name="L701" href="source/net/ipv4/tcp_metrics.c#L701">701</a> 
<a name="L702" href="source/net/ipv4/tcp_metrics.c#L702">702</a> void <a href="ident?i=tcp_fastopen_cache_get">tcp_fastopen_cache_get</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u16">u16</a> *mss,
<a name="L703" href="source/net/ipv4/tcp_metrics.c#L703">703</a>                             struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *cookie,
<a name="L704" href="source/net/ipv4/tcp_metrics.c#L704">704</a>                             int *syn_loss, unsigned long *last_syn_loss)
<a name="L705" href="source/net/ipv4/tcp_metrics.c#L705">705</a> {
<a name="L706" href="source/net/ipv4/tcp_metrics.c#L706">706</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L707" href="source/net/ipv4/tcp_metrics.c#L707">707</a> 
<a name="L708" href="source/net/ipv4/tcp_metrics.c#L708">708</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L709" href="source/net/ipv4/tcp_metrics.c#L709">709</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk), <a href="ident?i=false">false</a>);
<a name="L710" href="source/net/ipv4/tcp_metrics.c#L710">710</a>         if (<a href="ident?i=tm">tm</a>) {
<a name="L711" href="source/net/ipv4/tcp_metrics.c#L711">711</a>                 struct <a href="ident?i=tcp_fastopen_metrics">tcp_fastopen_metrics</a> *tfom = &amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen;
<a name="L712" href="source/net/ipv4/tcp_metrics.c#L712">712</a>                 unsigned int <a href="ident?i=seq">seq</a>;
<a name="L713" href="source/net/ipv4/tcp_metrics.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/tcp_metrics.c#L714">714</a>                 do {
<a name="L715" href="source/net/ipv4/tcp_metrics.c#L715">715</a>                         <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;fastopen_seqlock);
<a name="L716" href="source/net/ipv4/tcp_metrics.c#L716">716</a>                         if (tfom-&gt;mss)
<a name="L717" href="source/net/ipv4/tcp_metrics.c#L717">717</a>                                 *mss = tfom-&gt;mss;
<a name="L718" href="source/net/ipv4/tcp_metrics.c#L718">718</a>                         *cookie = tfom-&gt;cookie;
<a name="L719" href="source/net/ipv4/tcp_metrics.c#L719">719</a>                         if (cookie-&gt;<a href="ident?i=len">len</a> &lt;= 0 &amp;&amp; tfom-&gt;try_exp == 1)
<a name="L720" href="source/net/ipv4/tcp_metrics.c#L720">720</a>                                 cookie-&gt;exp = <a href="ident?i=true">true</a>;
<a name="L721" href="source/net/ipv4/tcp_metrics.c#L721">721</a>                         *syn_loss = tfom-&gt;syn_loss;
<a name="L722" href="source/net/ipv4/tcp_metrics.c#L722">722</a>                         *last_syn_loss = *syn_loss ? tfom-&gt;last_syn_loss : 0;
<a name="L723" href="source/net/ipv4/tcp_metrics.c#L723">723</a>                 } while (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;fastopen_seqlock, <a href="ident?i=seq">seq</a>));
<a name="L724" href="source/net/ipv4/tcp_metrics.c#L724">724</a>         }
<a name="L725" href="source/net/ipv4/tcp_metrics.c#L725">725</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L726" href="source/net/ipv4/tcp_metrics.c#L726">726</a> }
<a name="L727" href="source/net/ipv4/tcp_metrics.c#L727">727</a> 
<a name="L728" href="source/net/ipv4/tcp_metrics.c#L728">728</a> void <a href="ident?i=tcp_fastopen_cache_set">tcp_fastopen_cache_set</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u16">u16</a> mss,
<a name="L729" href="source/net/ipv4/tcp_metrics.c#L729">729</a>                             struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *cookie, <a href="ident?i=bool">bool</a> syn_lost,
<a name="L730" href="source/net/ipv4/tcp_metrics.c#L730">730</a>                             <a href="ident?i=u16">u16</a> try_exp)
<a name="L731" href="source/net/ipv4/tcp_metrics.c#L731">731</a> {
<a name="L732" href="source/net/ipv4/tcp_metrics.c#L732">732</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L733" href="source/net/ipv4/tcp_metrics.c#L733">733</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L734" href="source/net/ipv4/tcp_metrics.c#L734">734</a> 
<a name="L735" href="source/net/ipv4/tcp_metrics.c#L735">735</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L736" href="source/net/ipv4/tcp_metrics.c#L736">736</a>                 return;
<a name="L737" href="source/net/ipv4/tcp_metrics.c#L737">737</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L738" href="source/net/ipv4/tcp_metrics.c#L738">738</a>         <a href="ident?i=tm">tm</a> = <a href="ident?i=tcp_get_metrics">tcp_get_metrics</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>);
<a name="L739" href="source/net/ipv4/tcp_metrics.c#L739">739</a>         if (<a href="ident?i=tm">tm</a>) {
<a name="L740" href="source/net/ipv4/tcp_metrics.c#L740">740</a>                 struct <a href="ident?i=tcp_fastopen_metrics">tcp_fastopen_metrics</a> *tfom = &amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen;
<a name="L741" href="source/net/ipv4/tcp_metrics.c#L741">741</a> 
<a name="L742" href="source/net/ipv4/tcp_metrics.c#L742">742</a>                 <a href="ident?i=write_seqlock_bh">write_seqlock_bh</a>(&amp;fastopen_seqlock);
<a name="L743" href="source/net/ipv4/tcp_metrics.c#L743">743</a>                 if (mss)
<a name="L744" href="source/net/ipv4/tcp_metrics.c#L744">744</a>                         tfom-&gt;mss = mss;
<a name="L745" href="source/net/ipv4/tcp_metrics.c#L745">745</a>                 if (cookie &amp;&amp; cookie-&gt;<a href="ident?i=len">len</a> &gt; 0)
<a name="L746" href="source/net/ipv4/tcp_metrics.c#L746">746</a>                         tfom-&gt;cookie = *cookie;
<a name="L747" href="source/net/ipv4/tcp_metrics.c#L747">747</a>                 else if (try_exp &gt; tfom-&gt;try_exp &amp;&amp;
<a name="L748" href="source/net/ipv4/tcp_metrics.c#L748">748</a>                          tfom-&gt;cookie.<a href="ident?i=len">len</a> &lt;= 0 &amp;&amp; !tfom-&gt;cookie.exp)
<a name="L749" href="source/net/ipv4/tcp_metrics.c#L749">749</a>                         tfom-&gt;try_exp = try_exp;
<a name="L750" href="source/net/ipv4/tcp_metrics.c#L750">750</a>                 if (syn_lost) {
<a name="L751" href="source/net/ipv4/tcp_metrics.c#L751">751</a>                         ++tfom-&gt;syn_loss;
<a name="L752" href="source/net/ipv4/tcp_metrics.c#L752">752</a>                         tfom-&gt;last_syn_loss = <a href="ident?i=jiffies">jiffies</a>;
<a name="L753" href="source/net/ipv4/tcp_metrics.c#L753">753</a>                 } else
<a name="L754" href="source/net/ipv4/tcp_metrics.c#L754">754</a>                         tfom-&gt;syn_loss = 0;
<a name="L755" href="source/net/ipv4/tcp_metrics.c#L755">755</a>                 <a href="ident?i=write_sequnlock_bh">write_sequnlock_bh</a>(&amp;fastopen_seqlock);
<a name="L756" href="source/net/ipv4/tcp_metrics.c#L756">756</a>         }
<a name="L757" href="source/net/ipv4/tcp_metrics.c#L757">757</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L758" href="source/net/ipv4/tcp_metrics.c#L758">758</a> }
<a name="L759" href="source/net/ipv4/tcp_metrics.c#L759">759</a> 
<a name="L760" href="source/net/ipv4/tcp_metrics.c#L760">760</a> static struct <a href="ident?i=genl_family">genl_family</a> <a href="ident?i=tcp_metrics_nl_family">tcp_metrics_nl_family</a> = {
<a name="L761" href="source/net/ipv4/tcp_metrics.c#L761">761</a>         .<a href="ident?i=id">id</a>             = <a href="ident?i=GENL_ID_GENERATE">GENL_ID_GENERATE</a>,
<a name="L762" href="source/net/ipv4/tcp_metrics.c#L762">762</a>         .hdrsize        = 0,
<a name="L763" href="source/net/ipv4/tcp_metrics.c#L763">763</a>         .<a href="ident?i=name">name</a>           = <a href="ident?i=TCP_METRICS_GENL_NAME">TCP_METRICS_GENL_NAME</a>,
<a name="L764" href="source/net/ipv4/tcp_metrics.c#L764">764</a>         .<a href="ident?i=version">version</a>        = <a href="ident?i=TCP_METRICS_GENL_VERSION">TCP_METRICS_GENL_VERSION</a>,
<a name="L765" href="source/net/ipv4/tcp_metrics.c#L765">765</a>         .maxattr        = <a href="ident?i=TCP_METRICS_ATTR_MAX">TCP_METRICS_ATTR_MAX</a>,
<a name="L766" href="source/net/ipv4/tcp_metrics.c#L766">766</a>         .netnsok        = <a href="ident?i=true">true</a>,
<a name="L767" href="source/net/ipv4/tcp_metrics.c#L767">767</a> };
<a name="L768" href="source/net/ipv4/tcp_metrics.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/tcp_metrics.c#L769">769</a> static struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=tcp_metrics_nl_policy">tcp_metrics_nl_policy</a>[<a href="ident?i=TCP_METRICS_ATTR_MAX">TCP_METRICS_ATTR_MAX</a> + 1] = {
<a name="L770" href="source/net/ipv4/tcp_metrics.c#L770">770</a>         [TCP_METRICS_ATTR_ADDR_IPV4]    = { .<a href="ident?i=type">type</a> = NLA_U32, },
<a name="L771" href="source/net/ipv4/tcp_metrics.c#L771">771</a>         [TCP_METRICS_ATTR_ADDR_IPV6]    = { .<a href="ident?i=type">type</a> = NLA_BINARY,
<a name="L772" href="source/net/ipv4/tcp_metrics.c#L772">772</a>                                             .<a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=in6_addr">in6_addr</a>), },
<a name="L773" href="source/net/ipv4/tcp_metrics.c#L773">773</a>         <b><i>/* Following attributes are not received for GET/DEL,</i></b>
<a name="L774" href="source/net/ipv4/tcp_metrics.c#L774">774</a> <b><i>         * we keep them for reference</i></b>
<a name="L775" href="source/net/ipv4/tcp_metrics.c#L775">775</a> <b><i>         */</i></b>
<a name="L776" href="source/net/ipv4/tcp_metrics.c#L776">776</a> #if 0
<a name="L777" href="source/net/ipv4/tcp_metrics.c#L777">777</a>         [TCP_METRICS_ATTR_AGE]          = { .<a href="ident?i=type">type</a> = NLA_MSECS, },
<a name="L778" href="source/net/ipv4/tcp_metrics.c#L778">778</a>         [TCP_METRICS_ATTR_TW_TSVAL]     = { .<a href="ident?i=type">type</a> = NLA_U32, },
<a name="L779" href="source/net/ipv4/tcp_metrics.c#L779">779</a>         [TCP_METRICS_ATTR_TW_TS_STAMP]  = { .<a href="ident?i=type">type</a> = NLA_S32, },
<a name="L780" href="source/net/ipv4/tcp_metrics.c#L780">780</a>         [TCP_METRICS_ATTR_VALS]         = { .<a href="ident?i=type">type</a> = NLA_NESTED, },
<a name="L781" href="source/net/ipv4/tcp_metrics.c#L781">781</a>         [TCP_METRICS_ATTR_FOPEN_MSS]    = { .<a href="ident?i=type">type</a> = NLA_U16, },
<a name="L782" href="source/net/ipv4/tcp_metrics.c#L782">782</a>         [TCP_METRICS_ATTR_FOPEN_SYN_DROPS]      = { .<a href="ident?i=type">type</a> = NLA_U16, },
<a name="L783" href="source/net/ipv4/tcp_metrics.c#L783">783</a>         [TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS]    = { .<a href="ident?i=type">type</a> = NLA_MSECS, },
<a name="L784" href="source/net/ipv4/tcp_metrics.c#L784">784</a>         [TCP_METRICS_ATTR_FOPEN_COOKIE] = { .<a href="ident?i=type">type</a> = NLA_BINARY,
<a name="L785" href="source/net/ipv4/tcp_metrics.c#L785">785</a>                                             .<a href="ident?i=len">len</a> = <a href="ident?i=TCP_FASTOPEN_COOKIE_MAX">TCP_FASTOPEN_COOKIE_MAX</a>, },
<a name="L786" href="source/net/ipv4/tcp_metrics.c#L786">786</a> #endif
<a name="L787" href="source/net/ipv4/tcp_metrics.c#L787">787</a> };
<a name="L788" href="source/net/ipv4/tcp_metrics.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/tcp_metrics.c#L789">789</a> <b><i>/* Add attributes, caller cancels its header on failure */</i></b>
<a name="L790" href="source/net/ipv4/tcp_metrics.c#L790">790</a> static int <a href="ident?i=tcp_metrics_fill_info">tcp_metrics_fill_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=msg">msg</a>,
<a name="L791" href="source/net/ipv4/tcp_metrics.c#L791">791</a>                                  struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>)
<a name="L792" href="source/net/ipv4/tcp_metrics.c#L792">792</a> {
<a name="L793" href="source/net/ipv4/tcp_metrics.c#L793">793</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=nest">nest</a>;
<a name="L794" href="source/net/ipv4/tcp_metrics.c#L794">794</a>         int <a href="ident?i=i">i</a>;
<a name="L795" href="source/net/ipv4/tcp_metrics.c#L795">795</a> 
<a name="L796" href="source/net/ipv4/tcp_metrics.c#L796">796</a>         switch (<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr.<a href="ident?i=family">family</a>) {
<a name="L797" href="source/net/ipv4/tcp_metrics.c#L797">797</a>         case <a href="ident?i=AF_INET">AF_INET</a>:
<a name="L798" href="source/net/ipv4/tcp_metrics.c#L798">798</a>                 if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_ADDR_IPV4,
<a name="L799" href="source/net/ipv4/tcp_metrics.c#L799">799</a>                                     <a href="ident?i=tm">tm</a>-&gt;tcpm_daddr.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>) &lt; 0)
<a name="L800" href="source/net/ipv4/tcp_metrics.c#L800">800</a>                         goto nla_put_failure;
<a name="L801" href="source/net/ipv4/tcp_metrics.c#L801">801</a>                 if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_SADDR_IPV4,
<a name="L802" href="source/net/ipv4/tcp_metrics.c#L802">802</a>                                     <a href="ident?i=tm">tm</a>-&gt;tcpm_saddr.<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>) &lt; 0)
<a name="L803" href="source/net/ipv4/tcp_metrics.c#L803">803</a>                         goto nla_put_failure;
<a name="L804" href="source/net/ipv4/tcp_metrics.c#L804">804</a>                 break;
<a name="L805" href="source/net/ipv4/tcp_metrics.c#L805">805</a>         case <a href="ident?i=AF_INET6">AF_INET6</a>:
<a name="L806" href="source/net/ipv4/tcp_metrics.c#L806">806</a>                 if (<a href="ident?i=nla_put_in6_addr">nla_put_in6_addr</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_ADDR_IPV6,
<a name="L807" href="source/net/ipv4/tcp_metrics.c#L807">807</a>                                      &amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr.<a href="ident?i=addr">addr</a>.in6) &lt; 0)
<a name="L808" href="source/net/ipv4/tcp_metrics.c#L808">808</a>                         goto nla_put_failure;
<a name="L809" href="source/net/ipv4/tcp_metrics.c#L809">809</a>                 if (<a href="ident?i=nla_put_in6_addr">nla_put_in6_addr</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_SADDR_IPV6,
<a name="L810" href="source/net/ipv4/tcp_metrics.c#L810">810</a>                                      &amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_saddr.<a href="ident?i=addr">addr</a>.in6) &lt; 0)
<a name="L811" href="source/net/ipv4/tcp_metrics.c#L811">811</a>                         goto nla_put_failure;
<a name="L812" href="source/net/ipv4/tcp_metrics.c#L812">812</a>                 break;
<a name="L813" href="source/net/ipv4/tcp_metrics.c#L813">813</a>         default:
<a name="L814" href="source/net/ipv4/tcp_metrics.c#L814">814</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L815" href="source/net/ipv4/tcp_metrics.c#L815">815</a>         }
<a name="L816" href="source/net/ipv4/tcp_metrics.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/tcp_metrics.c#L817">817</a>         if (<a href="ident?i=nla_put_msecs">nla_put_msecs</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_AGE,
<a name="L818" href="source/net/ipv4/tcp_metrics.c#L818">818</a>                           <a href="ident?i=jiffies">jiffies</a> - <a href="ident?i=tm">tm</a>-&gt;tcpm_stamp) &lt; 0)
<a name="L819" href="source/net/ipv4/tcp_metrics.c#L819">819</a>                 goto nla_put_failure;
<a name="L820" href="source/net/ipv4/tcp_metrics.c#L820">820</a>         if (<a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp) {
<a name="L821" href="source/net/ipv4/tcp_metrics.c#L821">821</a>                 if (<a href="ident?i=nla_put_s32">nla_put_s32</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_TW_TS_STAMP,
<a name="L822" href="source/net/ipv4/tcp_metrics.c#L822">822</a>                                 (<a href="ident?i=s32">s32</a>) (<a href="ident?i=get_seconds">get_seconds</a>() - <a href="ident?i=tm">tm</a>-&gt;tcpm_ts_stamp)) &lt; 0)
<a name="L823" href="source/net/ipv4/tcp_metrics.c#L823">823</a>                         goto nla_put_failure;
<a name="L824" href="source/net/ipv4/tcp_metrics.c#L824">824</a>                 if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_TW_TSVAL,
<a name="L825" href="source/net/ipv4/tcp_metrics.c#L825">825</a>                                 <a href="ident?i=tm">tm</a>-&gt;tcpm_ts) &lt; 0)
<a name="L826" href="source/net/ipv4/tcp_metrics.c#L826">826</a>                         goto nla_put_failure;
<a name="L827" href="source/net/ipv4/tcp_metrics.c#L827">827</a>         }
<a name="L828" href="source/net/ipv4/tcp_metrics.c#L828">828</a> 
<a name="L829" href="source/net/ipv4/tcp_metrics.c#L829">829</a>         {
<a name="L830" href="source/net/ipv4/tcp_metrics.c#L830">830</a>                 int <a href="ident?i=n">n</a> = 0;
<a name="L831" href="source/net/ipv4/tcp_metrics.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/tcp_metrics.c#L832">832</a>                 <a href="ident?i=nest">nest</a> = <a href="ident?i=nla_nest_start">nla_nest_start</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_VALS);
<a name="L833" href="source/net/ipv4/tcp_metrics.c#L833">833</a>                 if (!<a href="ident?i=nest">nest</a>)
<a name="L834" href="source/net/ipv4/tcp_metrics.c#L834">834</a>                         goto nla_put_failure;
<a name="L835" href="source/net/ipv4/tcp_metrics.c#L835">835</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=TCP_METRIC_MAX_KERNEL">TCP_METRIC_MAX_KERNEL</a> + 1; <a href="ident?i=i">i</a>++) {
<a name="L836" href="source/net/ipv4/tcp_metrics.c#L836">836</a>                         <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a> = <a href="ident?i=tm">tm</a>-&gt;tcpm_vals[<a href="ident?i=i">i</a>];
<a name="L837" href="source/net/ipv4/tcp_metrics.c#L837">837</a> 
<a name="L838" href="source/net/ipv4/tcp_metrics.c#L838">838</a>                         if (!<a href="ident?i=val">val</a>)
<a name="L839" href="source/net/ipv4/tcp_metrics.c#L839">839</a>                                 continue;
<a name="L840" href="source/net/ipv4/tcp_metrics.c#L840">840</a>                         if (<a href="ident?i=i">i</a> == TCP_METRIC_RTT) {
<a name="L841" href="source/net/ipv4/tcp_metrics.c#L841">841</a>                                 if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=msg">msg</a>, TCP_METRIC_RTT_US + 1,
<a name="L842" href="source/net/ipv4/tcp_metrics.c#L842">842</a>                                                 <a href="ident?i=val">val</a>) &lt; 0)
<a name="L843" href="source/net/ipv4/tcp_metrics.c#L843">843</a>                                         goto nla_put_failure;
<a name="L844" href="source/net/ipv4/tcp_metrics.c#L844">844</a>                                 <a href="ident?i=n">n</a>++;
<a name="L845" href="source/net/ipv4/tcp_metrics.c#L845">845</a>                                 <a href="ident?i=val">val</a> = <a href="ident?i=max">max</a>(<a href="ident?i=val">val</a> / 1000, 1U);
<a name="L846" href="source/net/ipv4/tcp_metrics.c#L846">846</a>                         }
<a name="L847" href="source/net/ipv4/tcp_metrics.c#L847">847</a>                         if (<a href="ident?i=i">i</a> == TCP_METRIC_RTTVAR) {
<a name="L848" href="source/net/ipv4/tcp_metrics.c#L848">848</a>                                 if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=msg">msg</a>, TCP_METRIC_RTTVAR_US + 1,
<a name="L849" href="source/net/ipv4/tcp_metrics.c#L849">849</a>                                                 <a href="ident?i=val">val</a>) &lt; 0)
<a name="L850" href="source/net/ipv4/tcp_metrics.c#L850">850</a>                                         goto nla_put_failure;
<a name="L851" href="source/net/ipv4/tcp_metrics.c#L851">851</a>                                 <a href="ident?i=n">n</a>++;
<a name="L852" href="source/net/ipv4/tcp_metrics.c#L852">852</a>                                 <a href="ident?i=val">val</a> = <a href="ident?i=max">max</a>(<a href="ident?i=val">val</a> / 1000, 1U);
<a name="L853" href="source/net/ipv4/tcp_metrics.c#L853">853</a>                         }
<a name="L854" href="source/net/ipv4/tcp_metrics.c#L854">854</a>                         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=i">i</a> + 1, <a href="ident?i=val">val</a>) &lt; 0)
<a name="L855" href="source/net/ipv4/tcp_metrics.c#L855">855</a>                                 goto nla_put_failure;
<a name="L856" href="source/net/ipv4/tcp_metrics.c#L856">856</a>                         <a href="ident?i=n">n</a>++;
<a name="L857" href="source/net/ipv4/tcp_metrics.c#L857">857</a>                 }
<a name="L858" href="source/net/ipv4/tcp_metrics.c#L858">858</a>                 if (<a href="ident?i=n">n</a>)
<a name="L859" href="source/net/ipv4/tcp_metrics.c#L859">859</a>                         <a href="ident?i=nla_nest_end">nla_nest_end</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=nest">nest</a>);
<a name="L860" href="source/net/ipv4/tcp_metrics.c#L860">860</a>                 else
<a name="L861" href="source/net/ipv4/tcp_metrics.c#L861">861</a>                         <a href="ident?i=nla_nest_cancel">nla_nest_cancel</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=nest">nest</a>);
<a name="L862" href="source/net/ipv4/tcp_metrics.c#L862">862</a>         }
<a name="L863" href="source/net/ipv4/tcp_metrics.c#L863">863</a> 
<a name="L864" href="source/net/ipv4/tcp_metrics.c#L864">864</a>         {
<a name="L865" href="source/net/ipv4/tcp_metrics.c#L865">865</a>                 struct <a href="ident?i=tcp_fastopen_metrics">tcp_fastopen_metrics</a> tfom_copy[1], *tfom;
<a name="L866" href="source/net/ipv4/tcp_metrics.c#L866">866</a>                 unsigned int <a href="ident?i=seq">seq</a>;
<a name="L867" href="source/net/ipv4/tcp_metrics.c#L867">867</a> 
<a name="L868" href="source/net/ipv4/tcp_metrics.c#L868">868</a>                 do {
<a name="L869" href="source/net/ipv4/tcp_metrics.c#L869">869</a>                         <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;fastopen_seqlock);
<a name="L870" href="source/net/ipv4/tcp_metrics.c#L870">870</a>                         tfom_copy[0] = <a href="ident?i=tm">tm</a>-&gt;tcpm_fastopen;
<a name="L871" href="source/net/ipv4/tcp_metrics.c#L871">871</a>                 } while (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;fastopen_seqlock, <a href="ident?i=seq">seq</a>));
<a name="L872" href="source/net/ipv4/tcp_metrics.c#L872">872</a> 
<a name="L873" href="source/net/ipv4/tcp_metrics.c#L873">873</a>                 tfom = tfom_copy;
<a name="L874" href="source/net/ipv4/tcp_metrics.c#L874">874</a>                 if (tfom-&gt;mss &amp;&amp;
<a name="L875" href="source/net/ipv4/tcp_metrics.c#L875">875</a>                     <a href="ident?i=nla_put_u16">nla_put_u16</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_FOPEN_MSS,
<a name="L876" href="source/net/ipv4/tcp_metrics.c#L876">876</a>                                 tfom-&gt;mss) &lt; 0)
<a name="L877" href="source/net/ipv4/tcp_metrics.c#L877">877</a>                         goto nla_put_failure;
<a name="L878" href="source/net/ipv4/tcp_metrics.c#L878">878</a>                 if (tfom-&gt;syn_loss &amp;&amp;
<a name="L879" href="source/net/ipv4/tcp_metrics.c#L879">879</a>                     (<a href="ident?i=nla_put_u16">nla_put_u16</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_FOPEN_SYN_DROPS,
<a name="L880" href="source/net/ipv4/tcp_metrics.c#L880">880</a>                                 tfom-&gt;syn_loss) &lt; 0 ||
<a name="L881" href="source/net/ipv4/tcp_metrics.c#L881">881</a>                      <a href="ident?i=nla_put_msecs">nla_put_msecs</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS,
<a name="L882" href="source/net/ipv4/tcp_metrics.c#L882">882</a>                                 <a href="ident?i=jiffies">jiffies</a> - tfom-&gt;last_syn_loss) &lt; 0))
<a name="L883" href="source/net/ipv4/tcp_metrics.c#L883">883</a>                         goto nla_put_failure;
<a name="L884" href="source/net/ipv4/tcp_metrics.c#L884">884</a>                 if (tfom-&gt;cookie.<a href="ident?i=len">len</a> &gt; 0 &amp;&amp;
<a name="L885" href="source/net/ipv4/tcp_metrics.c#L885">885</a>                     <a href="ident?i=nla_put">nla_put</a>(<a href="ident?i=msg">msg</a>, TCP_METRICS_ATTR_FOPEN_COOKIE,
<a name="L886" href="source/net/ipv4/tcp_metrics.c#L886">886</a>                             tfom-&gt;cookie.<a href="ident?i=len">len</a>, tfom-&gt;cookie.<a href="ident?i=val">val</a>) &lt; 0)
<a name="L887" href="source/net/ipv4/tcp_metrics.c#L887">887</a>                         goto nla_put_failure;
<a name="L888" href="source/net/ipv4/tcp_metrics.c#L888">888</a>         }
<a name="L889" href="source/net/ipv4/tcp_metrics.c#L889">889</a> 
<a name="L890" href="source/net/ipv4/tcp_metrics.c#L890">890</a>         return 0;
<a name="L891" href="source/net/ipv4/tcp_metrics.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/tcp_metrics.c#L892">892</a> nla_put_failure:
<a name="L893" href="source/net/ipv4/tcp_metrics.c#L893">893</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L894" href="source/net/ipv4/tcp_metrics.c#L894">894</a> }
<a name="L895" href="source/net/ipv4/tcp_metrics.c#L895">895</a> 
<a name="L896" href="source/net/ipv4/tcp_metrics.c#L896">896</a> static int <a href="ident?i=tcp_metrics_dump_info">tcp_metrics_dump_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L897" href="source/net/ipv4/tcp_metrics.c#L897">897</a>                                  struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L898" href="source/net/ipv4/tcp_metrics.c#L898">898</a>                                  struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>)
<a name="L899" href="source/net/ipv4/tcp_metrics.c#L899">899</a> {
<a name="L900" href="source/net/ipv4/tcp_metrics.c#L900">900</a>         void *<a href="ident?i=hdr">hdr</a>;
<a name="L901" href="source/net/ipv4/tcp_metrics.c#L901">901</a> 
<a name="L902" href="source/net/ipv4/tcp_metrics.c#L902">902</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=genlmsg_put">genlmsg_put</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid, <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L903" href="source/net/ipv4/tcp_metrics.c#L903">903</a>                           &amp;<a href="ident?i=tcp_metrics_nl_family">tcp_metrics_nl_family</a>, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>,
<a name="L904" href="source/net/ipv4/tcp_metrics.c#L904">904</a>                           TCP_METRICS_CMD_GET);
<a name="L905" href="source/net/ipv4/tcp_metrics.c#L905">905</a>         if (!<a href="ident?i=hdr">hdr</a>)
<a name="L906" href="source/net/ipv4/tcp_metrics.c#L906">906</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L907" href="source/net/ipv4/tcp_metrics.c#L907">907</a> 
<a name="L908" href="source/net/ipv4/tcp_metrics.c#L908">908</a>         if (<a href="ident?i=tcp_metrics_fill_info">tcp_metrics_fill_info</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tm">tm</a>) &lt; 0)
<a name="L909" href="source/net/ipv4/tcp_metrics.c#L909">909</a>                 goto nla_put_failure;
<a name="L910" href="source/net/ipv4/tcp_metrics.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/tcp_metrics.c#L911">911</a>         <a href="ident?i=genlmsg_end">genlmsg_end</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=hdr">hdr</a>);
<a name="L912" href="source/net/ipv4/tcp_metrics.c#L912">912</a>         return 0;
<a name="L913" href="source/net/ipv4/tcp_metrics.c#L913">913</a> 
<a name="L914" href="source/net/ipv4/tcp_metrics.c#L914">914</a> nla_put_failure:
<a name="L915" href="source/net/ipv4/tcp_metrics.c#L915">915</a>         <a href="ident?i=genlmsg_cancel">genlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=hdr">hdr</a>);
<a name="L916" href="source/net/ipv4/tcp_metrics.c#L916">916</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L917" href="source/net/ipv4/tcp_metrics.c#L917">917</a> }
<a name="L918" href="source/net/ipv4/tcp_metrics.c#L918">918</a> 
<a name="L919" href="source/net/ipv4/tcp_metrics.c#L919">919</a> static int <a href="ident?i=tcp_metrics_nl_dump">tcp_metrics_nl_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L920" href="source/net/ipv4/tcp_metrics.c#L920">920</a>                                struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L921" href="source/net/ipv4/tcp_metrics.c#L921">921</a> {
<a name="L922" href="source/net/ipv4/tcp_metrics.c#L922">922</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L923" href="source/net/ipv4/tcp_metrics.c#L923">923</a>         unsigned int max_rows = 1U &lt;&lt; tcp_metrics_hash_log;
<a name="L924" href="source/net/ipv4/tcp_metrics.c#L924">924</a>         unsigned int row, s_row = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0];
<a name="L925" href="source/net/ipv4/tcp_metrics.c#L925">925</a>         int s_col = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1], col = s_col;
<a name="L926" href="source/net/ipv4/tcp_metrics.c#L926">926</a> 
<a name="L927" href="source/net/ipv4/tcp_metrics.c#L927">927</a>         for (row = s_row; row &lt; max_rows; row++, s_col = 0) {
<a name="L928" href="source/net/ipv4/tcp_metrics.c#L928">928</a>                 struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L929" href="source/net/ipv4/tcp_metrics.c#L929">929</a>                 struct <a href="ident?i=tcpm_hash_bucket">tcpm_hash_bucket</a> *hb = tcp_metrics_hash + row;
<a name="L930" href="source/net/ipv4/tcp_metrics.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/tcp_metrics.c#L931">931</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L932" href="source/net/ipv4/tcp_metrics.c#L932">932</a>                 for (col = 0, <a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(hb-&gt;<a href="ident?i=chain">chain</a>); <a href="ident?i=tm">tm</a>;
<a name="L933" href="source/net/ipv4/tcp_metrics.c#L933">933</a>                      <a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_next), col++) {
<a name="L934" href="source/net/ipv4/tcp_metrics.c#L934">934</a>                         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>))
<a name="L935" href="source/net/ipv4/tcp_metrics.c#L935">935</a>                                 continue;
<a name="L936" href="source/net/ipv4/tcp_metrics.c#L936">936</a>                         if (col &lt; s_col)
<a name="L937" href="source/net/ipv4/tcp_metrics.c#L937">937</a>                                 continue;
<a name="L938" href="source/net/ipv4/tcp_metrics.c#L938">938</a>                         if (<a href="ident?i=tcp_metrics_dump_info">tcp_metrics_dump_info</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=tm">tm</a>) &lt; 0) {
<a name="L939" href="source/net/ipv4/tcp_metrics.c#L939">939</a>                                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L940" href="source/net/ipv4/tcp_metrics.c#L940">940</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L941" href="source/net/ipv4/tcp_metrics.c#L941">941</a>                         }
<a name="L942" href="source/net/ipv4/tcp_metrics.c#L942">942</a>                 }
<a name="L943" href="source/net/ipv4/tcp_metrics.c#L943">943</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L944" href="source/net/ipv4/tcp_metrics.c#L944">944</a>         }
<a name="L945" href="source/net/ipv4/tcp_metrics.c#L945">945</a> 
<a name="L946" href="source/net/ipv4/tcp_metrics.c#L946">946</a> <a href="ident?i=done">done</a>:
<a name="L947" href="source/net/ipv4/tcp_metrics.c#L947">947</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = row;
<a name="L948" href="source/net/ipv4/tcp_metrics.c#L948">948</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = col;
<a name="L949" href="source/net/ipv4/tcp_metrics.c#L949">949</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L950" href="source/net/ipv4/tcp_metrics.c#L950">950</a> }
<a name="L951" href="source/net/ipv4/tcp_metrics.c#L951">951</a> 
<a name="L952" href="source/net/ipv4/tcp_metrics.c#L952">952</a> static int <a href="ident?i=__parse_nl_addr">__parse_nl_addr</a>(struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>, struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=addr">addr</a>,
<a name="L953" href="source/net/ipv4/tcp_metrics.c#L953">953</a>                            unsigned int *<a href="ident?i=hash">hash</a>, int optional, int <a href="ident?i=v4">v4</a>, int <a href="ident?i=v6">v6</a>)
<a name="L954" href="source/net/ipv4/tcp_metrics.c#L954">954</a> {
<a name="L955" href="source/net/ipv4/tcp_metrics.c#L955">955</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=a">a</a>;
<a name="L956" href="source/net/ipv4/tcp_metrics.c#L956">956</a> 
<a name="L957" href="source/net/ipv4/tcp_metrics.c#L957">957</a>         <a href="ident?i=a">a</a> = <a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[<a href="ident?i=v4">v4</a>];
<a name="L958" href="source/net/ipv4/tcp_metrics.c#L958">958</a>         if (<a href="ident?i=a">a</a>) {
<a name="L959" href="source/net/ipv4/tcp_metrics.c#L959">959</a>                 <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L960" href="source/net/ipv4/tcp_metrics.c#L960">960</a>                 <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=a">a</a>);
<a name="L961" href="source/net/ipv4/tcp_metrics.c#L961">961</a>                 if (<a href="ident?i=hash">hash</a>)
<a name="L962" href="source/net/ipv4/tcp_metrics.c#L962">962</a>                         *<a href="ident?i=hash">hash</a> = (<a href="ident?i=__force">__force</a> unsigned int) <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a4">a4</a>;
<a name="L963" href="source/net/ipv4/tcp_metrics.c#L963">963</a>                 return 0;
<a name="L964" href="source/net/ipv4/tcp_metrics.c#L964">964</a>         }
<a name="L965" href="source/net/ipv4/tcp_metrics.c#L965">965</a>         <a href="ident?i=a">a</a> = <a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[<a href="ident?i=v6">v6</a>];
<a name="L966" href="source/net/ipv4/tcp_metrics.c#L966">966</a>         if (<a href="ident?i=a">a</a>) {
<a name="L967" href="source/net/ipv4/tcp_metrics.c#L967">967</a>                 if (<a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=a">a</a>) != sizeof(struct <a href="ident?i=in6_addr">in6_addr</a>))
<a name="L968" href="source/net/ipv4/tcp_metrics.c#L968">968</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L969" href="source/net/ipv4/tcp_metrics.c#L969">969</a>                 <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L970" href="source/net/ipv4/tcp_metrics.c#L970">970</a>                 <a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=addr">addr</a>.in6 = <a href="ident?i=nla_get_in6_addr">nla_get_in6_addr</a>(<a href="ident?i=a">a</a>);
<a name="L971" href="source/net/ipv4/tcp_metrics.c#L971">971</a>                 if (<a href="ident?i=hash">hash</a>)
<a name="L972" href="source/net/ipv4/tcp_metrics.c#L972">972</a>                         *<a href="ident?i=hash">hash</a> = <a href="ident?i=ipv6_addr_hash">ipv6_addr_hash</a>(&amp;<a href="ident?i=addr">addr</a>-&gt;<a href="ident?i=addr">addr</a>.in6);
<a name="L973" href="source/net/ipv4/tcp_metrics.c#L973">973</a>                 return 0;
<a name="L974" href="source/net/ipv4/tcp_metrics.c#L974">974</a>         }
<a name="L975" href="source/net/ipv4/tcp_metrics.c#L975">975</a>         return optional ? 1 : -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L976" href="source/net/ipv4/tcp_metrics.c#L976">976</a> }
<a name="L977" href="source/net/ipv4/tcp_metrics.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/tcp_metrics.c#L978">978</a> static int <a href="ident?i=parse_nl_addr">parse_nl_addr</a>(struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>, struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=addr">addr</a>,
<a name="L979" href="source/net/ipv4/tcp_metrics.c#L979">979</a>                          unsigned int *<a href="ident?i=hash">hash</a>, int optional)
<a name="L980" href="source/net/ipv4/tcp_metrics.c#L980">980</a> {
<a name="L981" href="source/net/ipv4/tcp_metrics.c#L981">981</a>         return <a href="ident?i=__parse_nl_addr">__parse_nl_addr</a>(<a href="ident?i=info">info</a>, <a href="ident?i=addr">addr</a>, <a href="ident?i=hash">hash</a>, optional,
<a name="L982" href="source/net/ipv4/tcp_metrics.c#L982">982</a>                                TCP_METRICS_ATTR_ADDR_IPV4,
<a name="L983" href="source/net/ipv4/tcp_metrics.c#L983">983</a>                                TCP_METRICS_ATTR_ADDR_IPV6);
<a name="L984" href="source/net/ipv4/tcp_metrics.c#L984">984</a> }
<a name="L985" href="source/net/ipv4/tcp_metrics.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/tcp_metrics.c#L986">986</a> static int <a href="ident?i=parse_nl_saddr">parse_nl_saddr</a>(struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>, struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=addr">addr</a>)
<a name="L987" href="source/net/ipv4/tcp_metrics.c#L987">987</a> {
<a name="L988" href="source/net/ipv4/tcp_metrics.c#L988">988</a>         return <a href="ident?i=__parse_nl_addr">__parse_nl_addr</a>(<a href="ident?i=info">info</a>, <a href="ident?i=addr">addr</a>, <a href="ident?i=NULL">NULL</a>, 0,
<a name="L989" href="source/net/ipv4/tcp_metrics.c#L989">989</a>                                TCP_METRICS_ATTR_SADDR_IPV4,
<a name="L990" href="source/net/ipv4/tcp_metrics.c#L990">990</a>                                TCP_METRICS_ATTR_SADDR_IPV6);
<a name="L991" href="source/net/ipv4/tcp_metrics.c#L991">991</a> }
<a name="L992" href="source/net/ipv4/tcp_metrics.c#L992">992</a> 
<a name="L993" href="source/net/ipv4/tcp_metrics.c#L993">993</a> static int <a href="ident?i=tcp_metrics_nl_cmd_get">tcp_metrics_nl_cmd_get</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>)
<a name="L994" href="source/net/ipv4/tcp_metrics.c#L994">994</a> {
<a name="L995" href="source/net/ipv4/tcp_metrics.c#L995">995</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L996" href="source/net/ipv4/tcp_metrics.c#L996">996</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L997" href="source/net/ipv4/tcp_metrics.c#L997">997</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L998" href="source/net/ipv4/tcp_metrics.c#L998">998</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=msg">msg</a>;
<a name="L999" href="source/net/ipv4/tcp_metrics.c#L999">999</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=genl_info_net">genl_info_net</a>(<a href="ident?i=info">info</a>);
<a name="L1000" href="source/net/ipv4/tcp_metrics.c#L1000">1000</a>         void *<a href="ident?i=reply">reply</a>;
<a name="L1001" href="source/net/ipv4/tcp_metrics.c#L1001">1001</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1002" href="source/net/ipv4/tcp_metrics.c#L1002">1002</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=src">src</a> = <a href="ident?i=true">true</a>;
<a name="L1003" href="source/net/ipv4/tcp_metrics.c#L1003">1003</a> 
<a name="L1004" href="source/net/ipv4/tcp_metrics.c#L1004">1004</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=parse_nl_addr">parse_nl_addr</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=daddr">daddr</a>, &amp;<a href="ident?i=hash">hash</a>, 0);
<a name="L1005" href="source/net/ipv4/tcp_metrics.c#L1005">1005</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1006" href="source/net/ipv4/tcp_metrics.c#L1006">1006</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1007" href="source/net/ipv4/tcp_metrics.c#L1007">1007</a> 
<a name="L1008" href="source/net/ipv4/tcp_metrics.c#L1008">1008</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=parse_nl_saddr">parse_nl_saddr</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=saddr">saddr</a>);
<a name="L1009" href="source/net/ipv4/tcp_metrics.c#L1009">1009</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1010" href="source/net/ipv4/tcp_metrics.c#L1010">1010</a>                 <a href="ident?i=src">src</a> = <a href="ident?i=false">false</a>;
<a name="L1011" href="source/net/ipv4/tcp_metrics.c#L1011">1011</a> 
<a name="L1012" href="source/net/ipv4/tcp_metrics.c#L1012">1012</a>         <a href="ident?i=msg">msg</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=NLMSG_DEFAULT_SIZE">NLMSG_DEFAULT_SIZE</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1013" href="source/net/ipv4/tcp_metrics.c#L1013">1013</a>         if (!<a href="ident?i=msg">msg</a>)
<a name="L1014" href="source/net/ipv4/tcp_metrics.c#L1014">1014</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1015" href="source/net/ipv4/tcp_metrics.c#L1015">1015</a> 
<a name="L1016" href="source/net/ipv4/tcp_metrics.c#L1016">1016</a>         <a href="ident?i=reply">reply</a> = <a href="ident?i=genlmsg_put_reply">genlmsg_put_reply</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=info">info</a>, &amp;<a href="ident?i=tcp_metrics_nl_family">tcp_metrics_nl_family</a>, 0,
<a name="L1017" href="source/net/ipv4/tcp_metrics.c#L1017">1017</a>                                   <a href="ident?i=info">info</a>-&gt;genlhdr-&gt;<a href="ident?i=cmd">cmd</a>);
<a name="L1018" href="source/net/ipv4/tcp_metrics.c#L1018">1018</a>         if (!<a href="ident?i=reply">reply</a>)
<a name="L1019" href="source/net/ipv4/tcp_metrics.c#L1019">1019</a>                 goto nla_put_failure;
<a name="L1020" href="source/net/ipv4/tcp_metrics.c#L1020">1020</a> 
<a name="L1021" href="source/net/ipv4/tcp_metrics.c#L1021">1021</a>         <a href="ident?i=hash">hash</a> ^= <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>);
<a name="L1022" href="source/net/ipv4/tcp_metrics.c#L1022">1022</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=hash_32">hash_32</a>(<a href="ident?i=hash">hash</a>, tcp_metrics_hash_log);
<a name="L1023" href="source/net/ipv4/tcp_metrics.c#L1023">1023</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1024" href="source/net/ipv4/tcp_metrics.c#L1024">1024</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1025" href="source/net/ipv4/tcp_metrics.c#L1025">1025</a>         for (<a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(tcp_metrics_hash[<a href="ident?i=hash">hash</a>].<a href="ident?i=chain">chain</a>); <a href="ident?i=tm">tm</a>;
<a name="L1026" href="source/net/ipv4/tcp_metrics.c#L1026">1026</a>              <a href="ident?i=tm">tm</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tm">tm</a>-&gt;tcpm_next)) {
<a name="L1027" href="source/net/ipv4/tcp_metrics.c#L1027">1027</a>                 if (<a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr, &amp;<a href="ident?i=daddr">daddr</a>) &amp;&amp;
<a name="L1028" href="source/net/ipv4/tcp_metrics.c#L1028">1028</a>                     (!<a href="ident?i=src">src</a> || <a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_saddr, &amp;<a href="ident?i=saddr">saddr</a>)) &amp;&amp;
<a name="L1029" href="source/net/ipv4/tcp_metrics.c#L1029">1029</a>                     <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>)) {
<a name="L1030" href="source/net/ipv4/tcp_metrics.c#L1030">1030</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=tcp_metrics_fill_info">tcp_metrics_fill_info</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=tm">tm</a>);
<a name="L1031" href="source/net/ipv4/tcp_metrics.c#L1031">1031</a>                         break;
<a name="L1032" href="source/net/ipv4/tcp_metrics.c#L1032">1032</a>                 }
<a name="L1033" href="source/net/ipv4/tcp_metrics.c#L1033">1033</a>         }
<a name="L1034" href="source/net/ipv4/tcp_metrics.c#L1034">1034</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1035" href="source/net/ipv4/tcp_metrics.c#L1035">1035</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1036" href="source/net/ipv4/tcp_metrics.c#L1036">1036</a>                 goto out_free;
<a name="L1037" href="source/net/ipv4/tcp_metrics.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/tcp_metrics.c#L1038">1038</a>         <a href="ident?i=genlmsg_end">genlmsg_end</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=reply">reply</a>);
<a name="L1039" href="source/net/ipv4/tcp_metrics.c#L1039">1039</a>         return <a href="ident?i=genlmsg_reply">genlmsg_reply</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=info">info</a>);
<a name="L1040" href="source/net/ipv4/tcp_metrics.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/tcp_metrics.c#L1041">1041</a> nla_put_failure:
<a name="L1042" href="source/net/ipv4/tcp_metrics.c#L1042">1042</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1043" href="source/net/ipv4/tcp_metrics.c#L1043">1043</a> 
<a name="L1044" href="source/net/ipv4/tcp_metrics.c#L1044">1044</a> out_free:
<a name="L1045" href="source/net/ipv4/tcp_metrics.c#L1045">1045</a>         <a href="ident?i=nlmsg_free">nlmsg_free</a>(<a href="ident?i=msg">msg</a>);
<a name="L1046" href="source/net/ipv4/tcp_metrics.c#L1046">1046</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1047" href="source/net/ipv4/tcp_metrics.c#L1047">1047</a> }
<a name="L1048" href="source/net/ipv4/tcp_metrics.c#L1048">1048</a> 
<a name="L1049" href="source/net/ipv4/tcp_metrics.c#L1049">1049</a> static void <a href="ident?i=tcp_metrics_flush_all">tcp_metrics_flush_all</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1050" href="source/net/ipv4/tcp_metrics.c#L1050">1050</a> {
<a name="L1051" href="source/net/ipv4/tcp_metrics.c#L1051">1051</a>         unsigned int max_rows = 1U &lt;&lt; tcp_metrics_hash_log;
<a name="L1052" href="source/net/ipv4/tcp_metrics.c#L1052">1052</a>         struct <a href="ident?i=tcpm_hash_bucket">tcpm_hash_bucket</a> *hb = tcp_metrics_hash;
<a name="L1053" href="source/net/ipv4/tcp_metrics.c#L1053">1053</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L1054" href="source/net/ipv4/tcp_metrics.c#L1054">1054</a>         unsigned int row;
<a name="L1055" href="source/net/ipv4/tcp_metrics.c#L1055">1055</a> 
<a name="L1056" href="source/net/ipv4/tcp_metrics.c#L1056">1056</a>         for (row = 0; row &lt; max_rows; row++, hb++) {
<a name="L1057" href="source/net/ipv4/tcp_metrics.c#L1057">1057</a>                 struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> <a href="ident?i=__rcu">__rcu</a> **pp;
<a name="L1058" href="source/net/ipv4/tcp_metrics.c#L1058">1058</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;tcp_metrics_lock);
<a name="L1059" href="source/net/ipv4/tcp_metrics.c#L1059">1059</a>                 pp = &amp;hb-&gt;<a href="ident?i=chain">chain</a>;
<a name="L1060" href="source/net/ipv4/tcp_metrics.c#L1060">1060</a>                 for (<a href="ident?i=tm">tm</a> = <a href="ident?i=deref_locked">deref_locked</a>(*pp); <a href="ident?i=tm">tm</a>; <a href="ident?i=tm">tm</a> = <a href="ident?i=deref_locked">deref_locked</a>(*pp)) {
<a name="L1061" href="source/net/ipv4/tcp_metrics.c#L1061">1061</a>                         if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>)) {
<a name="L1062" href="source/net/ipv4/tcp_metrics.c#L1062">1062</a>                                 *pp = <a href="ident?i=tm">tm</a>-&gt;tcpm_next;
<a name="L1063" href="source/net/ipv4/tcp_metrics.c#L1063">1063</a>                                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=rcu_head">rcu_head</a>);
<a name="L1064" href="source/net/ipv4/tcp_metrics.c#L1064">1064</a>                         } else {
<a name="L1065" href="source/net/ipv4/tcp_metrics.c#L1065">1065</a>                                 pp = &amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_next;
<a name="L1066" href="source/net/ipv4/tcp_metrics.c#L1066">1066</a>                         }
<a name="L1067" href="source/net/ipv4/tcp_metrics.c#L1067">1067</a>                 }
<a name="L1068" href="source/net/ipv4/tcp_metrics.c#L1068">1068</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;tcp_metrics_lock);
<a name="L1069" href="source/net/ipv4/tcp_metrics.c#L1069">1069</a>         }
<a name="L1070" href="source/net/ipv4/tcp_metrics.c#L1070">1070</a> }
<a name="L1071" href="source/net/ipv4/tcp_metrics.c#L1071">1071</a> 
<a name="L1072" href="source/net/ipv4/tcp_metrics.c#L1072">1072</a> static int <a href="ident?i=tcp_metrics_nl_cmd_del">tcp_metrics_nl_cmd_del</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>)
<a name="L1073" href="source/net/ipv4/tcp_metrics.c#L1073">1073</a> {
<a name="L1074" href="source/net/ipv4/tcp_metrics.c#L1074">1074</a>         struct <a href="ident?i=tcpm_hash_bucket">tcpm_hash_bucket</a> *hb;
<a name="L1075" href="source/net/ipv4/tcp_metrics.c#L1075">1075</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> *<a href="ident?i=tm">tm</a>;
<a name="L1076" href="source/net/ipv4/tcp_metrics.c#L1076">1076</a>         struct <a href="ident?i=tcp_metrics_block">tcp_metrics_block</a> <a href="ident?i=__rcu">__rcu</a> **pp;
<a name="L1077" href="source/net/ipv4/tcp_metrics.c#L1077">1077</a>         struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L1078" href="source/net/ipv4/tcp_metrics.c#L1078">1078</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L1079" href="source/net/ipv4/tcp_metrics.c#L1079">1079</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=genl_info_net">genl_info_net</a>(<a href="ident?i=info">info</a>);
<a name="L1080" href="source/net/ipv4/tcp_metrics.c#L1080">1080</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1081" href="source/net/ipv4/tcp_metrics.c#L1081">1081</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=src">src</a> = <a href="ident?i=true">true</a>, <a href="ident?i=found">found</a> = <a href="ident?i=false">false</a>;
<a name="L1082" href="source/net/ipv4/tcp_metrics.c#L1082">1082</a> 
<a name="L1083" href="source/net/ipv4/tcp_metrics.c#L1083">1083</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=parse_nl_addr">parse_nl_addr</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=daddr">daddr</a>, &amp;<a href="ident?i=hash">hash</a>, 1);
<a name="L1084" href="source/net/ipv4/tcp_metrics.c#L1084">1084</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1085" href="source/net/ipv4/tcp_metrics.c#L1085">1085</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1086" href="source/net/ipv4/tcp_metrics.c#L1086">1086</a>         if (<a href="ident?i=ret">ret</a> &gt; 0) {
<a name="L1087" href="source/net/ipv4/tcp_metrics.c#L1087">1087</a>                 <a href="ident?i=tcp_metrics_flush_all">tcp_metrics_flush_all</a>(<a href="ident?i=net">net</a>);
<a name="L1088" href="source/net/ipv4/tcp_metrics.c#L1088">1088</a>                 return 0;
<a name="L1089" href="source/net/ipv4/tcp_metrics.c#L1089">1089</a>         }
<a name="L1090" href="source/net/ipv4/tcp_metrics.c#L1090">1090</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=parse_nl_saddr">parse_nl_saddr</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=saddr">saddr</a>);
<a name="L1091" href="source/net/ipv4/tcp_metrics.c#L1091">1091</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1092" href="source/net/ipv4/tcp_metrics.c#L1092">1092</a>                 <a href="ident?i=src">src</a> = <a href="ident?i=false">false</a>;
<a name="L1093" href="source/net/ipv4/tcp_metrics.c#L1093">1093</a> 
<a name="L1094" href="source/net/ipv4/tcp_metrics.c#L1094">1094</a>         <a href="ident?i=hash">hash</a> ^= <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>);
<a name="L1095" href="source/net/ipv4/tcp_metrics.c#L1095">1095</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=hash_32">hash_32</a>(<a href="ident?i=hash">hash</a>, tcp_metrics_hash_log);
<a name="L1096" href="source/net/ipv4/tcp_metrics.c#L1096">1096</a>         hb = tcp_metrics_hash + <a href="ident?i=hash">hash</a>;
<a name="L1097" href="source/net/ipv4/tcp_metrics.c#L1097">1097</a>         pp = &amp;hb-&gt;<a href="ident?i=chain">chain</a>;
<a name="L1098" href="source/net/ipv4/tcp_metrics.c#L1098">1098</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;tcp_metrics_lock);
<a name="L1099" href="source/net/ipv4/tcp_metrics.c#L1099">1099</a>         for (<a href="ident?i=tm">tm</a> = <a href="ident?i=deref_locked">deref_locked</a>(*pp); <a href="ident?i=tm">tm</a>; <a href="ident?i=tm">tm</a> = <a href="ident?i=deref_locked">deref_locked</a>(*pp)) {
<a name="L1100" href="source/net/ipv4/tcp_metrics.c#L1100">1100</a>                 if (<a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_daddr, &amp;<a href="ident?i=daddr">daddr</a>) &amp;&amp;
<a name="L1101" href="source/net/ipv4/tcp_metrics.c#L1101">1101</a>                     (!<a href="ident?i=src">src</a> || <a href="ident?i=addr_same">addr_same</a>(&amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_saddr, &amp;<a href="ident?i=saddr">saddr</a>)) &amp;&amp;
<a name="L1102" href="source/net/ipv4/tcp_metrics.c#L1102">1102</a>                     <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=tm_net">tm_net</a>(<a href="ident?i=tm">tm</a>), <a href="ident?i=net">net</a>)) {
<a name="L1103" href="source/net/ipv4/tcp_metrics.c#L1103">1103</a>                         *pp = <a href="ident?i=tm">tm</a>-&gt;tcpm_next;
<a name="L1104" href="source/net/ipv4/tcp_metrics.c#L1104">1104</a>                         <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=tm">tm</a>, <a href="ident?i=rcu_head">rcu_head</a>);
<a name="L1105" href="source/net/ipv4/tcp_metrics.c#L1105">1105</a>                         <a href="ident?i=found">found</a> = <a href="ident?i=true">true</a>;
<a name="L1106" href="source/net/ipv4/tcp_metrics.c#L1106">1106</a>                 } else {
<a name="L1107" href="source/net/ipv4/tcp_metrics.c#L1107">1107</a>                         pp = &amp;<a href="ident?i=tm">tm</a>-&gt;tcpm_next;
<a name="L1108" href="source/net/ipv4/tcp_metrics.c#L1108">1108</a>                 }
<a name="L1109" href="source/net/ipv4/tcp_metrics.c#L1109">1109</a>         }
<a name="L1110" href="source/net/ipv4/tcp_metrics.c#L1110">1110</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;tcp_metrics_lock);
<a name="L1111" href="source/net/ipv4/tcp_metrics.c#L1111">1111</a>         if (!<a href="ident?i=found">found</a>)
<a name="L1112" href="source/net/ipv4/tcp_metrics.c#L1112">1112</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1113" href="source/net/ipv4/tcp_metrics.c#L1113">1113</a>         return 0;
<a name="L1114" href="source/net/ipv4/tcp_metrics.c#L1114">1114</a> }
<a name="L1115" href="source/net/ipv4/tcp_metrics.c#L1115">1115</a> 
<a name="L1116" href="source/net/ipv4/tcp_metrics.c#L1116">1116</a> static const struct <a href="ident?i=genl_ops">genl_ops</a> <a href="ident?i=tcp_metrics_nl_ops">tcp_metrics_nl_ops</a>[] = {
<a name="L1117" href="source/net/ipv4/tcp_metrics.c#L1117">1117</a>         {
<a name="L1118" href="source/net/ipv4/tcp_metrics.c#L1118">1118</a>                 .<a href="ident?i=cmd">cmd</a> = TCP_METRICS_CMD_GET,
<a name="L1119" href="source/net/ipv4/tcp_metrics.c#L1119">1119</a>                 .doit = <a href="ident?i=tcp_metrics_nl_cmd_get">tcp_metrics_nl_cmd_get</a>,
<a name="L1120" href="source/net/ipv4/tcp_metrics.c#L1120">1120</a>                 .dumpit = <a href="ident?i=tcp_metrics_nl_dump">tcp_metrics_nl_dump</a>,
<a name="L1121" href="source/net/ipv4/tcp_metrics.c#L1121">1121</a>                 .<a href="ident?i=policy">policy</a> = <a href="ident?i=tcp_metrics_nl_policy">tcp_metrics_nl_policy</a>,
<a name="L1122" href="source/net/ipv4/tcp_metrics.c#L1122">1122</a>         },
<a name="L1123" href="source/net/ipv4/tcp_metrics.c#L1123">1123</a>         {
<a name="L1124" href="source/net/ipv4/tcp_metrics.c#L1124">1124</a>                 .<a href="ident?i=cmd">cmd</a> = TCP_METRICS_CMD_DEL,
<a name="L1125" href="source/net/ipv4/tcp_metrics.c#L1125">1125</a>                 .doit = <a href="ident?i=tcp_metrics_nl_cmd_del">tcp_metrics_nl_cmd_del</a>,
<a name="L1126" href="source/net/ipv4/tcp_metrics.c#L1126">1126</a>                 .<a href="ident?i=policy">policy</a> = <a href="ident?i=tcp_metrics_nl_policy">tcp_metrics_nl_policy</a>,
<a name="L1127" href="source/net/ipv4/tcp_metrics.c#L1127">1127</a>                 .<a href="ident?i=flags">flags</a> = <a href="ident?i=GENL_ADMIN_PERM">GENL_ADMIN_PERM</a>,
<a name="L1128" href="source/net/ipv4/tcp_metrics.c#L1128">1128</a>         },
<a name="L1129" href="source/net/ipv4/tcp_metrics.c#L1129">1129</a> };
<a name="L1130" href="source/net/ipv4/tcp_metrics.c#L1130">1130</a> 
<a name="L1131" href="source/net/ipv4/tcp_metrics.c#L1131">1131</a> static unsigned int <a href="ident?i=tcpmhash_entries">tcpmhash_entries</a>;
<a name="L1132" href="source/net/ipv4/tcp_metrics.c#L1132">1132</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=set_tcpmhash_entries">set_tcpmhash_entries</a>(char *<a href="ident?i=str">str</a>)
<a name="L1133" href="source/net/ipv4/tcp_metrics.c#L1133">1133</a> {
<a name="L1134" href="source/net/ipv4/tcp_metrics.c#L1134">1134</a>         <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=ret">ret</a>;
<a name="L1135" href="source/net/ipv4/tcp_metrics.c#L1135">1135</a> 
<a name="L1136" href="source/net/ipv4/tcp_metrics.c#L1136">1136</a>         if (!<a href="ident?i=str">str</a>)
<a name="L1137" href="source/net/ipv4/tcp_metrics.c#L1137">1137</a>                 return 0;
<a name="L1138" href="source/net/ipv4/tcp_metrics.c#L1138">1138</a> 
<a name="L1139" href="source/net/ipv4/tcp_metrics.c#L1139">1139</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=kstrtouint">kstrtouint</a>(<a href="ident?i=str">str</a>, 0, &amp;<a href="ident?i=tcpmhash_entries">tcpmhash_entries</a>);
<a name="L1140" href="source/net/ipv4/tcp_metrics.c#L1140">1140</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1141" href="source/net/ipv4/tcp_metrics.c#L1141">1141</a>                 return 0;
<a name="L1142" href="source/net/ipv4/tcp_metrics.c#L1142">1142</a> 
<a name="L1143" href="source/net/ipv4/tcp_metrics.c#L1143">1143</a>         return 1;
<a name="L1144" href="source/net/ipv4/tcp_metrics.c#L1144">1144</a> }
<a name="L1145" href="source/net/ipv4/tcp_metrics.c#L1145">1145</a> <a href="ident?i=__setup">__setup</a>(<i>"tcpmhash_entries="</i>, <a href="ident?i=set_tcpmhash_entries">set_tcpmhash_entries</a>);
<a name="L1146" href="source/net/ipv4/tcp_metrics.c#L1146">1146</a> 
<a name="L1147" href="source/net/ipv4/tcp_metrics.c#L1147">1147</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=tcp_net_metrics_init">tcp_net_metrics_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1148" href="source/net/ipv4/tcp_metrics.c#L1148">1148</a> {
<a name="L1149" href="source/net/ipv4/tcp_metrics.c#L1149">1149</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>;
<a name="L1150" href="source/net/ipv4/tcp_metrics.c#L1150">1150</a>         unsigned int <a href="ident?i=slots">slots</a>;
<a name="L1151" href="source/net/ipv4/tcp_metrics.c#L1151">1151</a> 
<a name="L1152" href="source/net/ipv4/tcp_metrics.c#L1152">1152</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L1153" href="source/net/ipv4/tcp_metrics.c#L1153">1153</a>                 return 0;
<a name="L1154" href="source/net/ipv4/tcp_metrics.c#L1154">1154</a> 
<a name="L1155" href="source/net/ipv4/tcp_metrics.c#L1155">1155</a>         <a href="ident?i=slots">slots</a> = <a href="ident?i=tcpmhash_entries">tcpmhash_entries</a>;
<a name="L1156" href="source/net/ipv4/tcp_metrics.c#L1156">1156</a>         if (!<a href="ident?i=slots">slots</a>) {
<a name="L1157" href="source/net/ipv4/tcp_metrics.c#L1157">1157</a>                 if (<a href="ident?i=totalram_pages">totalram_pages</a> &gt;= 128 * 1024)
<a name="L1158" href="source/net/ipv4/tcp_metrics.c#L1158">1158</a>                         <a href="ident?i=slots">slots</a> = 16 * 1024;
<a name="L1159" href="source/net/ipv4/tcp_metrics.c#L1159">1159</a>                 else
<a name="L1160" href="source/net/ipv4/tcp_metrics.c#L1160">1160</a>                         <a href="ident?i=slots">slots</a> = 8 * 1024;
<a name="L1161" href="source/net/ipv4/tcp_metrics.c#L1161">1161</a>         }
<a name="L1162" href="source/net/ipv4/tcp_metrics.c#L1162">1162</a> 
<a name="L1163" href="source/net/ipv4/tcp_metrics.c#L1163">1163</a>         tcp_metrics_hash_log = <a href="ident?i=order_base_2">order_base_2</a>(<a href="ident?i=slots">slots</a>);
<a name="L1164" href="source/net/ipv4/tcp_metrics.c#L1164">1164</a>         <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=tcpm_hash_bucket">tcpm_hash_bucket</a>) &lt;&lt; tcp_metrics_hash_log;
<a name="L1165" href="source/net/ipv4/tcp_metrics.c#L1165">1165</a> 
<a name="L1166" href="source/net/ipv4/tcp_metrics.c#L1166">1166</a>         tcp_metrics_hash = <a href="ident?i=kzalloc">kzalloc</a>(<a href="ident?i=size">size</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a> | <a href="ident?i=__GFP_NOWARN">__GFP_NOWARN</a>);
<a name="L1167" href="source/net/ipv4/tcp_metrics.c#L1167">1167</a>         if (!tcp_metrics_hash)
<a name="L1168" href="source/net/ipv4/tcp_metrics.c#L1168">1168</a>                 tcp_metrics_hash = <a href="ident?i=vzalloc">vzalloc</a>(<a href="ident?i=size">size</a>);
<a name="L1169" href="source/net/ipv4/tcp_metrics.c#L1169">1169</a> 
<a name="L1170" href="source/net/ipv4/tcp_metrics.c#L1170">1170</a>         if (!tcp_metrics_hash)
<a name="L1171" href="source/net/ipv4/tcp_metrics.c#L1171">1171</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1172" href="source/net/ipv4/tcp_metrics.c#L1172">1172</a> 
<a name="L1173" href="source/net/ipv4/tcp_metrics.c#L1173">1173</a>         return 0;
<a name="L1174" href="source/net/ipv4/tcp_metrics.c#L1174">1174</a> }
<a name="L1175" href="source/net/ipv4/tcp_metrics.c#L1175">1175</a> 
<a name="L1176" href="source/net/ipv4/tcp_metrics.c#L1176">1176</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=tcp_net_metrics_exit">tcp_net_metrics_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1177" href="source/net/ipv4/tcp_metrics.c#L1177">1177</a> {
<a name="L1178" href="source/net/ipv4/tcp_metrics.c#L1178">1178</a>         <a href="ident?i=tcp_metrics_flush_all">tcp_metrics_flush_all</a>(<a href="ident?i=net">net</a>);
<a name="L1179" href="source/net/ipv4/tcp_metrics.c#L1179">1179</a> }
<a name="L1180" href="source/net/ipv4/tcp_metrics.c#L1180">1180</a> 
<a name="L1181" href="source/net/ipv4/tcp_metrics.c#L1181">1181</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=tcp_net_metrics_ops">tcp_net_metrics_ops</a> = {
<a name="L1182" href="source/net/ipv4/tcp_metrics.c#L1182">1182</a>         .<a href="ident?i=init">init</a>   =       <a href="ident?i=tcp_net_metrics_init">tcp_net_metrics_init</a>,
<a name="L1183" href="source/net/ipv4/tcp_metrics.c#L1183">1183</a>         .<a href="ident?i=exit">exit</a>   =       <a href="ident?i=tcp_net_metrics_exit">tcp_net_metrics_exit</a>,
<a name="L1184" href="source/net/ipv4/tcp_metrics.c#L1184">1184</a> };
<a name="L1185" href="source/net/ipv4/tcp_metrics.c#L1185">1185</a> 
<a name="L1186" href="source/net/ipv4/tcp_metrics.c#L1186">1186</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_metrics_init">tcp_metrics_init</a>(void)
<a name="L1187" href="source/net/ipv4/tcp_metrics.c#L1187">1187</a> {
<a name="L1188" href="source/net/ipv4/tcp_metrics.c#L1188">1188</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1189" href="source/net/ipv4/tcp_metrics.c#L1189">1189</a> 
<a name="L1190" href="source/net/ipv4/tcp_metrics.c#L1190">1190</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=tcp_net_metrics_ops">tcp_net_metrics_ops</a>);
<a name="L1191" href="source/net/ipv4/tcp_metrics.c#L1191">1191</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1192" href="source/net/ipv4/tcp_metrics.c#L1192">1192</a>                 <a href="ident?i=panic">panic</a>(<i>"Could not allocate the tcp_metrics hash table\n"</i>);
<a name="L1193" href="source/net/ipv4/tcp_metrics.c#L1193">1193</a> 
<a name="L1194" href="source/net/ipv4/tcp_metrics.c#L1194">1194</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=genl_register_family_with_ops">genl_register_family_with_ops</a>(&amp;<a href="ident?i=tcp_metrics_nl_family">tcp_metrics_nl_family</a>,
<a name="L1195" href="source/net/ipv4/tcp_metrics.c#L1195">1195</a>                                             <a href="ident?i=tcp_metrics_nl_ops">tcp_metrics_nl_ops</a>);
<a name="L1196" href="source/net/ipv4/tcp_metrics.c#L1196">1196</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1197" href="source/net/ipv4/tcp_metrics.c#L1197">1197</a>                 <a href="ident?i=panic">panic</a>(<i>"Could not register tcp_metrics generic netlink\n"</i>);
<a name="L1198" href="source/net/ipv4/tcp_metrics.c#L1198">1198</a> }
<a name="L1199" href="source/net/ipv4/tcp_metrics.c#L1199">1199</a> </pre></div><p>
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
