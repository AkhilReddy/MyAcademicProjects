<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_fragment.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_fragment.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_fragment.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_fragment.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_fragment.c">ip_fragment.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_fragment.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_fragment.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ip_fragment.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ip_fragment.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ip_fragment.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_fragment.c#L6">6</a> <b><i> *              The IP fragmentation functionality.</i></b>
  <a name="L7" href="source/net/ipv4/ip_fragment.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_fragment.c#L8">8</a> <b><i> * Authors:     Fred N. van Kempen &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
  <a name="L9" href="source/net/ipv4/ip_fragment.c#L9">9</a> <b><i> *              Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;</i></b>
 <a name="L10" href="source/net/ipv4/ip_fragment.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/ip_fragment.c#L11">11</a> <b><i> * Fixes:</i></b>
 <a name="L12" href="source/net/ipv4/ip_fragment.c#L12">12</a> <b><i> *              Alan Cox        :       Split from ip.c , see ip_input.c for history.</i></b>
 <a name="L13" href="source/net/ipv4/ip_fragment.c#L13">13</a> <b><i> *              David S. Miller :       Begin massive cleanup...</i></b>
 <a name="L14" href="source/net/ipv4/ip_fragment.c#L14">14</a> <b><i> *              Andi Kleen      :       Add sysctls.</i></b>
 <a name="L15" href="source/net/ipv4/ip_fragment.c#L15">15</a> <b><i> *              xxxx            :       Overlapfrag bug.</i></b>
 <a name="L16" href="source/net/ipv4/ip_fragment.c#L16">16</a> <b><i> *              Ultima          :       ip_expire() kernel panic.</i></b>
 <a name="L17" href="source/net/ipv4/ip_fragment.c#L17">17</a> <b><i> *              Bill Hawes      :       Frag accounting and evictor fixes.</i></b>
 <a name="L18" href="source/net/ipv4/ip_fragment.c#L18">18</a> <b><i> *              John McDonald   :       0 length frag bug.</i></b>
 <a name="L19" href="source/net/ipv4/ip_fragment.c#L19">19</a> <b><i> *              Alexey Kuznetsov:       SMP races, threading, cleanup.</i></b>
 <a name="L20" href="source/net/ipv4/ip_fragment.c#L20">20</a> <b><i> *              Patrick McHardy :       LRU queue of frag heads for evictor.</i></b>
 <a name="L21" href="source/net/ipv4/ip_fragment.c#L21">21</a> <b><i> */</i></b>
 <a name="L22" href="source/net/ipv4/ip_fragment.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/ip_fragment.c#L23">23</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPv4: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L24" href="source/net/ipv4/ip_fragment.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/ip_fragment.c#L25">25</a> #include &lt;linux/compiler.h&gt;
 <a name="L26" href="source/net/ipv4/ip_fragment.c#L26">26</a> #include &lt;linux/module.h&gt;
 <a name="L27" href="source/net/ipv4/ip_fragment.c#L27">27</a> #include &lt;linux/types.h&gt;
 <a name="L28" href="source/net/ipv4/ip_fragment.c#L28">28</a> #include &lt;linux/mm.h&gt;
 <a name="L29" href="source/net/ipv4/ip_fragment.c#L29">29</a> #include &lt;linux/jiffies.h&gt;
 <a name="L30" href="source/net/ipv4/ip_fragment.c#L30">30</a> #include &lt;linux/skbuff.h&gt;
 <a name="L31" href="source/net/ipv4/ip_fragment.c#L31">31</a> #include &lt;linux/list.h&gt;
 <a name="L32" href="source/net/ipv4/ip_fragment.c#L32">32</a> #include &lt;linux/ip.h&gt;
 <a name="L33" href="source/net/ipv4/ip_fragment.c#L33">33</a> #include &lt;linux/icmp.h&gt;
 <a name="L34" href="source/net/ipv4/ip_fragment.c#L34">34</a> #include &lt;linux/netdevice.h&gt;
 <a name="L35" href="source/net/ipv4/ip_fragment.c#L35">35</a> #include &lt;linux/jhash.h&gt;
 <a name="L36" href="source/net/ipv4/ip_fragment.c#L36">36</a> #include &lt;linux/random.h&gt;
 <a name="L37" href="source/net/ipv4/ip_fragment.c#L37">37</a> #include &lt;linux/slab.h&gt;
 <a name="L38" href="source/net/ipv4/ip_fragment.c#L38">38</a> #include &lt;net/route.h&gt;
 <a name="L39" href="source/net/ipv4/ip_fragment.c#L39">39</a> #include &lt;net/dst.h&gt;
 <a name="L40" href="source/net/ipv4/ip_fragment.c#L40">40</a> #include &lt;net/sock.h&gt;
 <a name="L41" href="source/net/ipv4/ip_fragment.c#L41">41</a> #include &lt;net/ip.h&gt;
 <a name="L42" href="source/net/ipv4/ip_fragment.c#L42">42</a> #include &lt;net/icmp.h&gt;
 <a name="L43" href="source/net/ipv4/ip_fragment.c#L43">43</a> #include &lt;net/checksum.h&gt;
 <a name="L44" href="source/net/ipv4/ip_fragment.c#L44">44</a> #include &lt;net/inetpeer.h&gt;
 <a name="L45" href="source/net/ipv4/ip_fragment.c#L45">45</a> #include &lt;net/inet_frag.h&gt;
 <a name="L46" href="source/net/ipv4/ip_fragment.c#L46">46</a> #include &lt;linux/tcp.h&gt;
 <a name="L47" href="source/net/ipv4/ip_fragment.c#L47">47</a> #include &lt;linux/udp.h&gt;
 <a name="L48" href="source/net/ipv4/ip_fragment.c#L48">48</a> #include &lt;linux/inet.h&gt;
 <a name="L49" href="source/net/ipv4/ip_fragment.c#L49">49</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L50" href="source/net/ipv4/ip_fragment.c#L50">50</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L51" href="source/net/ipv4/ip_fragment.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/ip_fragment.c#L52">52</a> <b><i>/* NOTE. Logic of IP defragmentation is parallel to corresponding IPv6</i></b>
 <a name="L53" href="source/net/ipv4/ip_fragment.c#L53">53</a> <b><i> * code now. If you change something here, _PLEASE_ update ipv6/reassembly.c</i></b>
 <a name="L54" href="source/net/ipv4/ip_fragment.c#L54">54</a> <b><i> * as well. Or notify me, at least. --ANK</i></b>
 <a name="L55" href="source/net/ipv4/ip_fragment.c#L55">55</a> <b><i> */</i></b>
 <a name="L56" href="source/net/ipv4/ip_fragment.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/ip_fragment.c#L57">57</a> static int sysctl_ipfrag_max_dist <a href="ident?i=__read_mostly">__read_mostly</a> = 64;
 <a name="L58" href="source/net/ipv4/ip_fragment.c#L58">58</a> static const char <a href="ident?i=ip_frag_cache_name">ip_frag_cache_name</a>[] = <i>"ip4-frags"</i>;
 <a name="L59" href="source/net/ipv4/ip_fragment.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/ip_fragment.c#L60">60</a> struct <a href="ident?i=ipfrag_skb_cb">ipfrag_skb_cb</a>
 <a name="L61" href="source/net/ipv4/ip_fragment.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/ip_fragment.c#L62">62</a>         struct <a href="ident?i=inet_skb_parm">inet_skb_parm</a>    <a href="ident?i=h">h</a>;
 <a name="L63" href="source/net/ipv4/ip_fragment.c#L63">63</a>         int                     <a href="ident?i=offset">offset</a>;
 <a name="L64" href="source/net/ipv4/ip_fragment.c#L64">64</a> };
 <a name="L65" href="source/net/ipv4/ip_fragment.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/ip_fragment.c#L66">66</a> #define <a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=skb">skb</a>)    ((struct <a href="ident?i=ipfrag_skb_cb">ipfrag_skb_cb</a> *)((<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=cb">cb</a>))
 <a name="L67" href="source/net/ipv4/ip_fragment.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/ip_fragment.c#L68">68</a> <b><i>/* Describe an entry in the "incomplete datagrams" queue. */</i></b>
 <a name="L69" href="source/net/ipv4/ip_fragment.c#L69">69</a> struct <a href="ident?i=ipq">ipq</a> {
 <a name="L70" href="source/net/ipv4/ip_fragment.c#L70">70</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> q;
 <a name="L71" href="source/net/ipv4/ip_fragment.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/ip_fragment.c#L72">72</a>         <a href="ident?i=u32">u32</a>             <a href="ident?i=user">user</a>;
 <a name="L73" href="source/net/ipv4/ip_fragment.c#L73">73</a>         <a href="ident?i=__be32">__be32</a>          <a href="ident?i=saddr">saddr</a>;
 <a name="L74" href="source/net/ipv4/ip_fragment.c#L74">74</a>         <a href="ident?i=__be32">__be32</a>          <a href="ident?i=daddr">daddr</a>;
 <a name="L75" href="source/net/ipv4/ip_fragment.c#L75">75</a>         <a href="ident?i=__be16">__be16</a>          <a href="ident?i=id">id</a>;
 <a name="L76" href="source/net/ipv4/ip_fragment.c#L76">76</a>         <a href="ident?i=u8">u8</a>              <a href="ident?i=protocol">protocol</a>;
 <a name="L77" href="source/net/ipv4/ip_fragment.c#L77">77</a>         <a href="ident?i=u8">u8</a>              ecn; <b><i>/* RFC3168 support */</i></b>
 <a name="L78" href="source/net/ipv4/ip_fragment.c#L78">78</a>         int             iif;
 <a name="L79" href="source/net/ipv4/ip_fragment.c#L79">79</a>         unsigned int    rid;
 <a name="L80" href="source/net/ipv4/ip_fragment.c#L80">80</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *peer;
 <a name="L81" href="source/net/ipv4/ip_fragment.c#L81">81</a> };
 <a name="L82" href="source/net/ipv4/ip_fragment.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/ip_fragment.c#L83">83</a> static <a href="ident?i=u8">u8</a> <a href="ident?i=ip4_frag_ecn">ip4_frag_ecn</a>(<a href="ident?i=u8">u8</a> tos)
 <a name="L84" href="source/net/ipv4/ip_fragment.c#L84">84</a> {
 <a name="L85" href="source/net/ipv4/ip_fragment.c#L85">85</a>         return 1 &lt;&lt; (tos &amp; INET_ECN_MASK);
 <a name="L86" href="source/net/ipv4/ip_fragment.c#L86">86</a> }
 <a name="L87" href="source/net/ipv4/ip_fragment.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/ip_fragment.c#L88">88</a> static struct <a href="ident?i=inet_frags">inet_frags</a> <a href="ident?i=ip4_frags">ip4_frags</a>;
 <a name="L89" href="source/net/ipv4/ip_fragment.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/ip_fragment.c#L90">90</a> int <a href="ident?i=ip_frag_mem">ip_frag_mem</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L91" href="source/net/ipv4/ip_fragment.c#L91">91</a> {
 <a name="L92" href="source/net/ipv4/ip_fragment.c#L92">92</a>         return <a href="ident?i=sum_frag_mem_limit">sum_frag_mem_limit</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags);
 <a name="L93" href="source/net/ipv4/ip_fragment.c#L93">93</a> }
 <a name="L94" href="source/net/ipv4/ip_fragment.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/ip_fragment.c#L95">95</a> static int <a href="ident?i=ip_frag_reasm">ip_frag_reasm</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *prev,
 <a name="L96" href="source/net/ipv4/ip_fragment.c#L96">96</a>                          struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>);
 <a name="L97" href="source/net/ipv4/ip_fragment.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/ip_fragment.c#L98">98</a> struct <a href="ident?i=ip4_create_arg">ip4_create_arg</a> {
 <a name="L99" href="source/net/ipv4/ip_fragment.c#L99">99</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L100" href="source/net/ipv4/ip_fragment.c#L100">100</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=user">user</a>;
<a name="L101" href="source/net/ipv4/ip_fragment.c#L101">101</a> };
<a name="L102" href="source/net/ipv4/ip_fragment.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/ip_fragment.c#L103">103</a> static unsigned int <a href="ident?i=ipqhashfn">ipqhashfn</a>(<a href="ident?i=__be16">__be16</a> <a href="ident?i=id">id</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=u8">u8</a> prot)
<a name="L104" href="source/net/ipv4/ip_fragment.c#L104">104</a> {
<a name="L105" href="source/net/ipv4/ip_fragment.c#L105">105</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(&amp;<a href="ident?i=ip4_frags">ip4_frags</a>.<a href="ident?i=rnd">rnd</a>, sizeof(<a href="ident?i=ip4_frags">ip4_frags</a>.<a href="ident?i=rnd">rnd</a>));
<a name="L106" href="source/net/ipv4/ip_fragment.c#L106">106</a>         return <a href="ident?i=jhash_3words">jhash_3words</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=id">id</a> &lt;&lt; 16 | prot,
<a name="L107" href="source/net/ipv4/ip_fragment.c#L107">107</a>                             (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=saddr">saddr</a>, (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=daddr">daddr</a>,
<a name="L108" href="source/net/ipv4/ip_fragment.c#L108">108</a>                             <a href="ident?i=ip4_frags">ip4_frags</a>.<a href="ident?i=rnd">rnd</a>);
<a name="L109" href="source/net/ipv4/ip_fragment.c#L109">109</a> }
<a name="L110" href="source/net/ipv4/ip_fragment.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/ip_fragment.c#L111">111</a> static unsigned int <a href="ident?i=ip4_hashfn">ip4_hashfn</a>(const struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q)
<a name="L112" href="source/net/ipv4/ip_fragment.c#L112">112</a> {
<a name="L113" href="source/net/ipv4/ip_fragment.c#L113">113</a>         const struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=ipq">ipq</a>;
<a name="L114" href="source/net/ipv4/ip_fragment.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/ip_fragment.c#L115">115</a>         <a href="ident?i=ipq">ipq</a> = <a href="ident?i=container_of">container_of</a>(q, struct <a href="ident?i=ipq">ipq</a>, q);
<a name="L116" href="source/net/ipv4/ip_fragment.c#L116">116</a>         return <a href="ident?i=ipqhashfn">ipqhashfn</a>(<a href="ident?i=ipq">ipq</a>-&gt;<a href="ident?i=id">id</a>, <a href="ident?i=ipq">ipq</a>-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ipq">ipq</a>-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=ipq">ipq</a>-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L117" href="source/net/ipv4/ip_fragment.c#L117">117</a> }
<a name="L118" href="source/net/ipv4/ip_fragment.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/ip_fragment.c#L119">119</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ip4_frag_match">ip4_frag_match</a>(const struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q, const void *<a href="ident?i=a">a</a>)
<a name="L120" href="source/net/ipv4/ip_fragment.c#L120">120</a> {
<a name="L121" href="source/net/ipv4/ip_fragment.c#L121">121</a>         const struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>;
<a name="L122" href="source/net/ipv4/ip_fragment.c#L122">122</a>         const struct <a href="ident?i=ip4_create_arg">ip4_create_arg</a> *<a href="ident?i=arg">arg</a> = <a href="ident?i=a">a</a>;
<a name="L123" href="source/net/ipv4/ip_fragment.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/ip_fragment.c#L124">124</a>         <a href="ident?i=qp">qp</a> = <a href="ident?i=container_of">container_of</a>(q, struct <a href="ident?i=ipq">ipq</a>, q);
<a name="L125" href="source/net/ipv4/ip_fragment.c#L125">125</a>         return  <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=id">id</a> == <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=id">id</a> &amp;&amp;
<a name="L126" href="source/net/ipv4/ip_fragment.c#L126">126</a>                 <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=saddr">saddr</a> == <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=saddr">saddr</a> &amp;&amp;
<a name="L127" href="source/net/ipv4/ip_fragment.c#L127">127</a>                 <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=daddr">daddr</a> == <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=daddr">daddr</a> &amp;&amp;
<a name="L128" href="source/net/ipv4/ip_fragment.c#L128">128</a>                 <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=protocol">protocol</a> &amp;&amp;
<a name="L129" href="source/net/ipv4/ip_fragment.c#L129">129</a>                 <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=user">user</a> == <a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=user">user</a>;
<a name="L130" href="source/net/ipv4/ip_fragment.c#L130">130</a> }
<a name="L131" href="source/net/ipv4/ip_fragment.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/ip_fragment.c#L132">132</a> static void <a href="ident?i=ip4_frag_init">ip4_frag_init</a>(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q, const void *<a href="ident?i=a">a</a>)
<a name="L133" href="source/net/ipv4/ip_fragment.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/ip_fragment.c#L134">134</a>         struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a> = <a href="ident?i=container_of">container_of</a>(q, struct <a href="ident?i=ipq">ipq</a>, q);
<a name="L135" href="source/net/ipv4/ip_fragment.c#L135">135</a>         struct <a href="ident?i=netns_ipv4">netns_ipv4</a> *ipv4 = <a href="ident?i=container_of">container_of</a>(q-&gt;<a href="ident?i=net">net</a>, struct <a href="ident?i=netns_ipv4">netns_ipv4</a>,
<a name="L136" href="source/net/ipv4/ip_fragment.c#L136">136</a>                                                frags);
<a name="L137" href="source/net/ipv4/ip_fragment.c#L137">137</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=container_of">container_of</a>(ipv4, struct <a href="ident?i=net">net</a>, ipv4);
<a name="L138" href="source/net/ipv4/ip_fragment.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/ip_fragment.c#L139">139</a>         const struct <a href="ident?i=ip4_create_arg">ip4_create_arg</a> *<a href="ident?i=arg">arg</a> = <a href="ident?i=a">a</a>;
<a name="L140" href="source/net/ipv4/ip_fragment.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/ip_fragment.c#L141">141</a>         <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L142" href="source/net/ipv4/ip_fragment.c#L142">142</a>         <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=id">id</a>;
<a name="L143" href="source/net/ipv4/ip_fragment.c#L143">143</a>         <a href="ident?i=qp">qp</a>-&gt;ecn = <a href="ident?i=ip4_frag_ecn">ip4_frag_ecn</a>(<a href="ident?i=arg">arg</a>-&gt;iph-&gt;tos);
<a name="L144" href="source/net/ipv4/ip_fragment.c#L144">144</a>         <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L145" href="source/net/ipv4/ip_fragment.c#L145">145</a>         <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L146" href="source/net/ipv4/ip_fragment.c#L146">146</a>         <a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=user">user</a> = <a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=user">user</a>;
<a name="L147" href="source/net/ipv4/ip_fragment.c#L147">147</a>         <a href="ident?i=qp">qp</a>-&gt;peer = sysctl_ipfrag_max_dist ?
<a name="L148" href="source/net/ipv4/ip_fragment.c#L148">148</a>                 <a href="ident?i=inet_getpeer_v4">inet_getpeer_v4</a>(<a href="ident?i=net">net</a>-&gt;ipv4.peers, <a href="ident?i=arg">arg</a>-&gt;iph-&gt;<a href="ident?i=saddr">saddr</a>, 1) : <a href="ident?i=NULL">NULL</a>;
<a name="L149" href="source/net/ipv4/ip_fragment.c#L149">149</a> }
<a name="L150" href="source/net/ipv4/ip_fragment.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/ip_fragment.c#L151">151</a> static void <a href="ident?i=ip4_frag_free">ip4_frag_free</a>(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q)
<a name="L152" href="source/net/ipv4/ip_fragment.c#L152">152</a> {
<a name="L153" href="source/net/ipv4/ip_fragment.c#L153">153</a>         struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>;
<a name="L154" href="source/net/ipv4/ip_fragment.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/ip_fragment.c#L155">155</a>         <a href="ident?i=qp">qp</a> = <a href="ident?i=container_of">container_of</a>(q, struct <a href="ident?i=ipq">ipq</a>, q);
<a name="L156" href="source/net/ipv4/ip_fragment.c#L156">156</a>         if (<a href="ident?i=qp">qp</a>-&gt;peer)
<a name="L157" href="source/net/ipv4/ip_fragment.c#L157">157</a>                 <a href="ident?i=inet_putpeer">inet_putpeer</a>(<a href="ident?i=qp">qp</a>-&gt;peer);
<a name="L158" href="source/net/ipv4/ip_fragment.c#L158">158</a> }
<a name="L159" href="source/net/ipv4/ip_fragment.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/ip_fragment.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/ip_fragment.c#L161">161</a> <b><i>/* Destruction primitives. */</i></b>
<a name="L162" href="source/net/ipv4/ip_fragment.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/ip_fragment.c#L163">163</a> static void <a href="ident?i=ipq_put">ipq_put</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=ipq">ipq</a>)
<a name="L164" href="source/net/ipv4/ip_fragment.c#L164">164</a> {
<a name="L165" href="source/net/ipv4/ip_fragment.c#L165">165</a>         <a href="ident?i=inet_frag_put">inet_frag_put</a>(&amp;<a href="ident?i=ipq">ipq</a>-&gt;q, &amp;<a href="ident?i=ip4_frags">ip4_frags</a>);
<a name="L166" href="source/net/ipv4/ip_fragment.c#L166">166</a> }
<a name="L167" href="source/net/ipv4/ip_fragment.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/ip_fragment.c#L168">168</a> <b><i>/* Kill ipq entry. It is not destroyed immediately,</i></b>
<a name="L169" href="source/net/ipv4/ip_fragment.c#L169">169</a> <b><i> * because caller (and someone more) holds reference count.</i></b>
<a name="L170" href="source/net/ipv4/ip_fragment.c#L170">170</a> <b><i> */</i></b>
<a name="L171" href="source/net/ipv4/ip_fragment.c#L171">171</a> static void <a href="ident?i=ipq_kill">ipq_kill</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=ipq">ipq</a>)
<a name="L172" href="source/net/ipv4/ip_fragment.c#L172">172</a> {
<a name="L173" href="source/net/ipv4/ip_fragment.c#L173">173</a>         <a href="ident?i=inet_frag_kill">inet_frag_kill</a>(&amp;<a href="ident?i=ipq">ipq</a>-&gt;q, &amp;<a href="ident?i=ip4_frags">ip4_frags</a>);
<a name="L174" href="source/net/ipv4/ip_fragment.c#L174">174</a> }
<a name="L175" href="source/net/ipv4/ip_fragment.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/ip_fragment.c#L176">176</a> <b><i>/*</i></b>
<a name="L177" href="source/net/ipv4/ip_fragment.c#L177">177</a> <b><i> * Oops, a fragment queue timed out.  Kill it and send an ICMP reply.</i></b>
<a name="L178" href="source/net/ipv4/ip_fragment.c#L178">178</a> <b><i> */</i></b>
<a name="L179" href="source/net/ipv4/ip_fragment.c#L179">179</a> static void <a href="ident?i=ip_expire">ip_expire</a>(unsigned long <a href="ident?i=arg">arg</a>)
<a name="L180" href="source/net/ipv4/ip_fragment.c#L180">180</a> {
<a name="L181" href="source/net/ipv4/ip_fragment.c#L181">181</a>         struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>;
<a name="L182" href="source/net/ipv4/ip_fragment.c#L182">182</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L183" href="source/net/ipv4/ip_fragment.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/ip_fragment.c#L184">184</a>         <a href="ident?i=qp">qp</a> = <a href="ident?i=container_of">container_of</a>((struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *) <a href="ident?i=arg">arg</a>, struct <a href="ident?i=ipq">ipq</a>, q);
<a name="L185" href="source/net/ipv4/ip_fragment.c#L185">185</a>         <a href="ident?i=net">net</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=net">net</a>, struct <a href="ident?i=net">net</a>, ipv4.frags);
<a name="L186" href="source/net/ipv4/ip_fragment.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/ip_fragment.c#L187">187</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=lock">lock</a>);
<a name="L188" href="source/net/ipv4/ip_fragment.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/ip_fragment.c#L189">189</a>         if (<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> &amp; INET_FRAG_COMPLETE)
<a name="L190" href="source/net/ipv4/ip_fragment.c#L190">190</a>                 goto <a href="ident?i=out">out</a>;
<a name="L191" href="source/net/ipv4/ip_fragment.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/ip_fragment.c#L192">192</a>         <a href="ident?i=ipq_kill">ipq_kill</a>(<a href="ident?i=qp">qp</a>);
<a name="L193" href="source/net/ipv4/ip_fragment.c#L193">193</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMFAILS);
<a name="L194" href="source/net/ipv4/ip_fragment.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/ip_fragment.c#L195">195</a>         if (!(<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> &amp; INET_FRAG_EVICTED)) {
<a name="L196" href="source/net/ipv4/ip_fragment.c#L196">196</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=head">head</a> = <a href="ident?i=qp">qp</a>-&gt;q.fragments;
<a name="L197" href="source/net/ipv4/ip_fragment.c#L197">197</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L198" href="source/net/ipv4/ip_fragment.c#L198">198</a>                 int <a href="ident?i=err">err</a>;
<a name="L199" href="source/net/ipv4/ip_fragment.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/ip_fragment.c#L200">200</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMTIMEOUT);
<a name="L201" href="source/net/ipv4/ip_fragment.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/ip_fragment.c#L202">202</a>                 if (!(<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> &amp; INET_FRAG_FIRST_IN) || !<a href="ident?i=qp">qp</a>-&gt;q.fragments)
<a name="L203" href="source/net/ipv4/ip_fragment.c#L203">203</a>                         goto <a href="ident?i=out">out</a>;
<a name="L204" href="source/net/ipv4/ip_fragment.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/ip_fragment.c#L205">205</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L206" href="source/net/ipv4/ip_fragment.c#L206">206</a>                 <a href="ident?i=head">head</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index_rcu">dev_get_by_index_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=qp">qp</a>-&gt;iif);
<a name="L207" href="source/net/ipv4/ip_fragment.c#L207">207</a>                 if (!<a href="ident?i=head">head</a>-&gt;<a href="ident?i=dev">dev</a>)
<a name="L208" href="source/net/ipv4/ip_fragment.c#L208">208</a>                         goto out_rcu_unlock;
<a name="L209" href="source/net/ipv4/ip_fragment.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/ip_fragment.c#L210">210</a>                 <b><i>/* skb has no dst, perform route lookup again */</i></b>
<a name="L211" href="source/net/ipv4/ip_fragment.c#L211">211</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=head">head</a>);
<a name="L212" href="source/net/ipv4/ip_fragment.c#L212">212</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_input_noref">ip_route_input_noref</a>(<a href="ident?i=head">head</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L213" href="source/net/ipv4/ip_fragment.c#L213">213</a>                                            iph-&gt;tos, <a href="ident?i=head">head</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L214" href="source/net/ipv4/ip_fragment.c#L214">214</a>                 if (<a href="ident?i=err">err</a>)
<a name="L215" href="source/net/ipv4/ip_fragment.c#L215">215</a>                         goto out_rcu_unlock;
<a name="L216" href="source/net/ipv4/ip_fragment.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/ip_fragment.c#L217">217</a>                 <b><i>/* Only an end host needs to send an ICMP</i></b>
<a name="L218" href="source/net/ipv4/ip_fragment.c#L218">218</a> <b><i>                 * "Fragment Reassembly Timeout" message, per RFC792.</i></b>
<a name="L219" href="source/net/ipv4/ip_fragment.c#L219">219</a> <b><i>                 */</i></b>
<a name="L220" href="source/net/ipv4/ip_fragment.c#L220">220</a>                 if (<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=user">user</a> == IP_DEFRAG_AF_PACKET ||
<a name="L221" href="source/net/ipv4/ip_fragment.c#L221">221</a>                     ((<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=user">user</a> &gt;= IP_DEFRAG_CONNTRACK_IN) &amp;&amp;
<a name="L222" href="source/net/ipv4/ip_fragment.c#L222">222</a>                      (<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=user">user</a> &lt;= __IP_DEFRAG_CONNTRACK_IN_END) &amp;&amp;
<a name="L223" href="source/net/ipv4/ip_fragment.c#L223">223</a>                      (<a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=head">head</a>)-&gt;rt_type != RTN_LOCAL)))
<a name="L224" href="source/net/ipv4/ip_fragment.c#L224">224</a>                         goto out_rcu_unlock;
<a name="L225" href="source/net/ipv4/ip_fragment.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/ip_fragment.c#L226">226</a>                 <b><i>/* Send an ICMP "Fragment Reassembly Timeout" message. */</i></b>
<a name="L227" href="source/net/ipv4/ip_fragment.c#L227">227</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=head">head</a>, <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>, <a href="ident?i=ICMP_EXC_FRAGTIME">ICMP_EXC_FRAGTIME</a>, 0);
<a name="L228" href="source/net/ipv4/ip_fragment.c#L228">228</a> out_rcu_unlock:
<a name="L229" href="source/net/ipv4/ip_fragment.c#L229">229</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L230" href="source/net/ipv4/ip_fragment.c#L230">230</a>         }
<a name="L231" href="source/net/ipv4/ip_fragment.c#L231">231</a> <a href="ident?i=out">out</a>:
<a name="L232" href="source/net/ipv4/ip_fragment.c#L232">232</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=lock">lock</a>);
<a name="L233" href="source/net/ipv4/ip_fragment.c#L233">233</a>         <a href="ident?i=ipq_put">ipq_put</a>(<a href="ident?i=qp">qp</a>);
<a name="L234" href="source/net/ipv4/ip_fragment.c#L234">234</a> }
<a name="L235" href="source/net/ipv4/ip_fragment.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/ip_fragment.c#L236">236</a> <b><i>/* Find the correct entry in the "incomplete datagrams" queue for</i></b>
<a name="L237" href="source/net/ipv4/ip_fragment.c#L237">237</a> <b><i> * this IP datagram, and create new one, if nothing is found.</i></b>
<a name="L238" href="source/net/ipv4/ip_fragment.c#L238">238</a> <b><i> */</i></b>
<a name="L239" href="source/net/ipv4/ip_fragment.c#L239">239</a> static struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=ip_find">ip_find</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=iphdr">iphdr</a> *iph, <a href="ident?i=u32">u32</a> <a href="ident?i=user">user</a>)
<a name="L240" href="source/net/ipv4/ip_fragment.c#L240">240</a> {
<a name="L241" href="source/net/ipv4/ip_fragment.c#L241">241</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q;
<a name="L242" href="source/net/ipv4/ip_fragment.c#L242">242</a>         struct <a href="ident?i=ip4_create_arg">ip4_create_arg</a> <a href="ident?i=arg">arg</a>;
<a name="L243" href="source/net/ipv4/ip_fragment.c#L243">243</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L244" href="source/net/ipv4/ip_fragment.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/ip_fragment.c#L245">245</a>         <a href="ident?i=arg">arg</a>.iph = iph;
<a name="L246" href="source/net/ipv4/ip_fragment.c#L246">246</a>         <a href="ident?i=arg">arg</a>.<a href="ident?i=user">user</a> = <a href="ident?i=user">user</a>;
<a name="L247" href="source/net/ipv4/ip_fragment.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/ip_fragment.c#L248">248</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=ipqhashfn">ipqhashfn</a>(iph-&gt;<a href="ident?i=id">id</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L249" href="source/net/ipv4/ip_fragment.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/ip_fragment.c#L250">250</a>         q = <a href="ident?i=inet_frag_find">inet_frag_find</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags, &amp;<a href="ident?i=ip4_frags">ip4_frags</a>, &amp;<a href="ident?i=arg">arg</a>, <a href="ident?i=hash">hash</a>);
<a name="L251" href="source/net/ipv4/ip_fragment.c#L251">251</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(q)) {
<a name="L252" href="source/net/ipv4/ip_fragment.c#L252">252</a>                 <a href="ident?i=inet_frag_maybe_warn_overflow">inet_frag_maybe_warn_overflow</a>(q, <a href="ident?i=pr_fmt">pr_fmt</a>());
<a name="L253" href="source/net/ipv4/ip_fragment.c#L253">253</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L254" href="source/net/ipv4/ip_fragment.c#L254">254</a>         }
<a name="L255" href="source/net/ipv4/ip_fragment.c#L255">255</a>         return <a href="ident?i=container_of">container_of</a>(q, struct <a href="ident?i=ipq">ipq</a>, q);
<a name="L256" href="source/net/ipv4/ip_fragment.c#L256">256</a> }
<a name="L257" href="source/net/ipv4/ip_fragment.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/ip_fragment.c#L258">258</a> <b><i>/* Is the fragment too far ahead to be part of ipq? */</i></b>
<a name="L259" href="source/net/ipv4/ip_fragment.c#L259">259</a> static int <a href="ident?i=ip_frag_too_far">ip_frag_too_far</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>)
<a name="L260" href="source/net/ipv4/ip_fragment.c#L260">260</a> {
<a name="L261" href="source/net/ipv4/ip_fragment.c#L261">261</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *peer = <a href="ident?i=qp">qp</a>-&gt;peer;
<a name="L262" href="source/net/ipv4/ip_fragment.c#L262">262</a>         unsigned int <a href="ident?i=max">max</a> = sysctl_ipfrag_max_dist;
<a name="L263" href="source/net/ipv4/ip_fragment.c#L263">263</a>         unsigned int <a href="ident?i=start">start</a>, <a href="ident?i=end">end</a>;
<a name="L264" href="source/net/ipv4/ip_fragment.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/ip_fragment.c#L265">265</a>         int <a href="ident?i=rc">rc</a>;
<a name="L266" href="source/net/ipv4/ip_fragment.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/ip_fragment.c#L267">267</a>         if (!peer || !<a href="ident?i=max">max</a>)
<a name="L268" href="source/net/ipv4/ip_fragment.c#L268">268</a>                 return 0;
<a name="L269" href="source/net/ipv4/ip_fragment.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/ip_fragment.c#L270">270</a>         <a href="ident?i=start">start</a> = <a href="ident?i=qp">qp</a>-&gt;rid;
<a name="L271" href="source/net/ipv4/ip_fragment.c#L271">271</a>         <a href="ident?i=end">end</a> = <a href="ident?i=atomic_inc_return">atomic_inc_return</a>(&amp;peer-&gt;rid);
<a name="L272" href="source/net/ipv4/ip_fragment.c#L272">272</a>         <a href="ident?i=qp">qp</a>-&gt;rid = <a href="ident?i=end">end</a>;
<a name="L273" href="source/net/ipv4/ip_fragment.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/ip_fragment.c#L274">274</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=qp">qp</a>-&gt;q.fragments &amp;&amp; (<a href="ident?i=end">end</a> - <a href="ident?i=start">start</a>) &gt; <a href="ident?i=max">max</a>;
<a name="L275" href="source/net/ipv4/ip_fragment.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/ip_fragment.c#L276">276</a>         if (<a href="ident?i=rc">rc</a>) {
<a name="L277" href="source/net/ipv4/ip_fragment.c#L277">277</a>                 struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L278" href="source/net/ipv4/ip_fragment.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/ip_fragment.c#L279">279</a>                 <a href="ident?i=net">net</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=net">net</a>, struct <a href="ident?i=net">net</a>, ipv4.frags);
<a name="L280" href="source/net/ipv4/ip_fragment.c#L280">280</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMFAILS);
<a name="L281" href="source/net/ipv4/ip_fragment.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/ip_fragment.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/ip_fragment.c#L283">283</a>         return <a href="ident?i=rc">rc</a>;
<a name="L284" href="source/net/ipv4/ip_fragment.c#L284">284</a> }
<a name="L285" href="source/net/ipv4/ip_fragment.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/ip_fragment.c#L286">286</a> static int <a href="ident?i=ip_frag_reinit">ip_frag_reinit</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>)
<a name="L287" href="source/net/ipv4/ip_fragment.c#L287">287</a> {
<a name="L288" href="source/net/ipv4/ip_fragment.c#L288">288</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=fp">fp</a>;
<a name="L289" href="source/net/ipv4/ip_fragment.c#L289">289</a>         unsigned int sum_truesize = 0;
<a name="L290" href="source/net/ipv4/ip_fragment.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/ip_fragment.c#L291">291</a>         if (!<a href="ident?i=mod_timer">mod_timer</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=timer">timer</a>, <a href="ident?i=jiffies">jiffies</a> + <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=net">net</a>-&gt;<a href="ident?i=timeout">timeout</a>)) {
<a name="L292" href="source/net/ipv4/ip_fragment.c#L292">292</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q.refcnt);
<a name="L293" href="source/net/ipv4/ip_fragment.c#L293">293</a>                 return -<a href="ident?i=ETIMEDOUT">ETIMEDOUT</a>;
<a name="L294" href="source/net/ipv4/ip_fragment.c#L294">294</a>         }
<a name="L295" href="source/net/ipv4/ip_fragment.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/ip_fragment.c#L296">296</a>         <a href="ident?i=fp">fp</a> = <a href="ident?i=qp">qp</a>-&gt;q.fragments;
<a name="L297" href="source/net/ipv4/ip_fragment.c#L297">297</a>         do {
<a name="L298" href="source/net/ipv4/ip_fragment.c#L298">298</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=xp">xp</a> = <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L299" href="source/net/ipv4/ip_fragment.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/ip_fragment.c#L300">300</a>                 sum_truesize += <a href="ident?i=fp">fp</a>-&gt;truesize;
<a name="L301" href="source/net/ipv4/ip_fragment.c#L301">301</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=fp">fp</a>);
<a name="L302" href="source/net/ipv4/ip_fragment.c#L302">302</a>                 <a href="ident?i=fp">fp</a> = <a href="ident?i=xp">xp</a>;
<a name="L303" href="source/net/ipv4/ip_fragment.c#L303">303</a>         } while (<a href="ident?i=fp">fp</a>);
<a name="L304" href="source/net/ipv4/ip_fragment.c#L304">304</a>         <a href="ident?i=sub_frag_mem_limit">sub_frag_mem_limit</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q, sum_truesize);
<a name="L305" href="source/net/ipv4/ip_fragment.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/ip_fragment.c#L306">306</a>         <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> = 0;
<a name="L307" href="source/net/ipv4/ip_fragment.c#L307">307</a>         <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a> = 0;
<a name="L308" href="source/net/ipv4/ip_fragment.c#L308">308</a>         <a href="ident?i=qp">qp</a>-&gt;q.meat = 0;
<a name="L309" href="source/net/ipv4/ip_fragment.c#L309">309</a>         <a href="ident?i=qp">qp</a>-&gt;q.fragments = <a href="ident?i=NULL">NULL</a>;
<a name="L310" href="source/net/ipv4/ip_fragment.c#L310">310</a>         <a href="ident?i=qp">qp</a>-&gt;q.fragments_tail = <a href="ident?i=NULL">NULL</a>;
<a name="L311" href="source/net/ipv4/ip_fragment.c#L311">311</a>         <a href="ident?i=qp">qp</a>-&gt;iif = 0;
<a name="L312" href="source/net/ipv4/ip_fragment.c#L312">312</a>         <a href="ident?i=qp">qp</a>-&gt;ecn = 0;
<a name="L313" href="source/net/ipv4/ip_fragment.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/ip_fragment.c#L314">314</a>         return 0;
<a name="L315" href="source/net/ipv4/ip_fragment.c#L315">315</a> }
<a name="L316" href="source/net/ipv4/ip_fragment.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/ip_fragment.c#L317">317</a> <b><i>/* Add new segment to existing queue. */</i></b>
<a name="L318" href="source/net/ipv4/ip_fragment.c#L318">318</a> static int <a href="ident?i=ip_frag_queue">ip_frag_queue</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L319" href="source/net/ipv4/ip_fragment.c#L319">319</a> {
<a name="L320" href="source/net/ipv4/ip_fragment.c#L320">320</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *prev, *<a href="ident?i=next">next</a>;
<a name="L321" href="source/net/ipv4/ip_fragment.c#L321">321</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L322" href="source/net/ipv4/ip_fragment.c#L322">322</a>         int <a href="ident?i=flags">flags</a>, <a href="ident?i=offset">offset</a>;
<a name="L323" href="source/net/ipv4/ip_fragment.c#L323">323</a>         int ihl, <a href="ident?i=end">end</a>;
<a name="L324" href="source/net/ipv4/ip_fragment.c#L324">324</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L325" href="source/net/ipv4/ip_fragment.c#L325">325</a>         <a href="ident?i=u8">u8</a> ecn;
<a name="L326" href="source/net/ipv4/ip_fragment.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/ip_fragment.c#L327">327</a>         if (<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> &amp; INET_FRAG_COMPLETE)
<a name="L328" href="source/net/ipv4/ip_fragment.c#L328">328</a>                 goto <a href="ident?i=err">err</a>;
<a name="L329" href="source/net/ipv4/ip_fragment.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/ip_fragment.c#L330">330</a>         if (!(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_FRAG_COMPLETE">IPSKB_FRAG_COMPLETE</a>) &amp;&amp;
<a name="L331" href="source/net/ipv4/ip_fragment.c#L331">331</a>             <a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=ip_frag_too_far">ip_frag_too_far</a>(<a href="ident?i=qp">qp</a>)) &amp;&amp;
<a name="L332" href="source/net/ipv4/ip_fragment.c#L332">332</a>             <a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a> = <a href="ident?i=ip_frag_reinit">ip_frag_reinit</a>(<a href="ident?i=qp">qp</a>))) {
<a name="L333" href="source/net/ipv4/ip_fragment.c#L333">333</a>                 <a href="ident?i=ipq_kill">ipq_kill</a>(<a href="ident?i=qp">qp</a>);
<a name="L334" href="source/net/ipv4/ip_fragment.c#L334">334</a>                 goto <a href="ident?i=err">err</a>;
<a name="L335" href="source/net/ipv4/ip_fragment.c#L335">335</a>         }
<a name="L336" href="source/net/ipv4/ip_fragment.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/ip_fragment.c#L337">337</a>         ecn = <a href="ident?i=ip4_frag_ecn">ip4_frag_ecn</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos);
<a name="L338" href="source/net/ipv4/ip_fragment.c#L338">338</a>         <a href="ident?i=offset">offset</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_off);
<a name="L339" href="source/net/ipv4/ip_fragment.c#L339">339</a>         <a href="ident?i=flags">flags</a> = <a href="ident?i=offset">offset</a> &amp; ~IP_OFFSET;
<a name="L340" href="source/net/ipv4/ip_fragment.c#L340">340</a>         <a href="ident?i=offset">offset</a> &amp;= <a href="ident?i=IP_OFFSET">IP_OFFSET</a>;
<a name="L341" href="source/net/ipv4/ip_fragment.c#L341">341</a>         <a href="ident?i=offset">offset</a> &lt;&lt;= 3;           <b><i>/* offset is in 8-byte chunks */</i></b>
<a name="L342" href="source/net/ipv4/ip_fragment.c#L342">342</a>         ihl = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L343" href="source/net/ipv4/ip_fragment.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/ip_fragment.c#L344">344</a>         <b><i>/* Determine the position of this fragment. */</i></b>
<a name="L345" href="source/net/ipv4/ip_fragment.c#L345">345</a>         <a href="ident?i=end">end</a> = <a href="ident?i=offset">offset</a> + <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - ihl;
<a name="L346" href="source/net/ipv4/ip_fragment.c#L346">346</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L347" href="source/net/ipv4/ip_fragment.c#L347">347</a> 
<a name="L348" href="source/net/ipv4/ip_fragment.c#L348">348</a>         <b><i>/* Is this the final fragment? */</i></b>
<a name="L349" href="source/net/ipv4/ip_fragment.c#L349">349</a>         if ((<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_MF">IP_MF</a>) == 0) {
<a name="L350" href="source/net/ipv4/ip_fragment.c#L350">350</a>                 <b><i>/* If we already have some bits beyond end</i></b>
<a name="L351" href="source/net/ipv4/ip_fragment.c#L351">351</a> <b><i>                 * or have different end, the segment is corrupted.</i></b>
<a name="L352" href="source/net/ipv4/ip_fragment.c#L352">352</a> <b><i>                 */</i></b>
<a name="L353" href="source/net/ipv4/ip_fragment.c#L353">353</a>                 if (<a href="ident?i=end">end</a> &lt; <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a> ||
<a name="L354" href="source/net/ipv4/ip_fragment.c#L354">354</a>                     ((<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> &amp; INET_FRAG_LAST_IN) &amp;&amp; <a href="ident?i=end">end</a> != <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a>))
<a name="L355" href="source/net/ipv4/ip_fragment.c#L355">355</a>                         goto <a href="ident?i=err">err</a>;
<a name="L356" href="source/net/ipv4/ip_fragment.c#L356">356</a>                 <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> |= INET_FRAG_LAST_IN;
<a name="L357" href="source/net/ipv4/ip_fragment.c#L357">357</a>                 <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a> = <a href="ident?i=end">end</a>;
<a name="L358" href="source/net/ipv4/ip_fragment.c#L358">358</a>         } else {
<a name="L359" href="source/net/ipv4/ip_fragment.c#L359">359</a>                 if (<a href="ident?i=end">end</a>&amp;7) {
<a name="L360" href="source/net/ipv4/ip_fragment.c#L360">360</a>                         <a href="ident?i=end">end</a> &amp;= ~7;
<a name="L361" href="source/net/ipv4/ip_fragment.c#L361">361</a>                         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_UNNECESSARY">CHECKSUM_UNNECESSARY</a>)
<a name="L362" href="source/net/ipv4/ip_fragment.c#L362">362</a>                                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L363" href="source/net/ipv4/ip_fragment.c#L363">363</a>                 }
<a name="L364" href="source/net/ipv4/ip_fragment.c#L364">364</a>                 if (<a href="ident?i=end">end</a> &gt; <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a>) {
<a name="L365" href="source/net/ipv4/ip_fragment.c#L365">365</a>                         <b><i>/* Some bits beyond end -&gt; corruption. */</i></b>
<a name="L366" href="source/net/ipv4/ip_fragment.c#L366">366</a>                         if (<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> &amp; INET_FRAG_LAST_IN)
<a name="L367" href="source/net/ipv4/ip_fragment.c#L367">367</a>                                 goto <a href="ident?i=err">err</a>;
<a name="L368" href="source/net/ipv4/ip_fragment.c#L368">368</a>                         <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a> = <a href="ident?i=end">end</a>;
<a name="L369" href="source/net/ipv4/ip_fragment.c#L369">369</a>                 }
<a name="L370" href="source/net/ipv4/ip_fragment.c#L370">370</a>         }
<a name="L371" href="source/net/ipv4/ip_fragment.c#L371">371</a>         if (<a href="ident?i=end">end</a> == <a href="ident?i=offset">offset</a>)
<a name="L372" href="source/net/ipv4/ip_fragment.c#L372">372</a>                 goto <a href="ident?i=err">err</a>;
<a name="L373" href="source/net/ipv4/ip_fragment.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/ip_fragment.c#L374">374</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L375" href="source/net/ipv4/ip_fragment.c#L375">375</a>         if (!<a href="ident?i=pskb_pull">pskb_pull</a>(<a href="ident?i=skb">skb</a>, ihl))
<a name="L376" href="source/net/ipv4/ip_fragment.c#L376">376</a>                 goto <a href="ident?i=err">err</a>;
<a name="L377" href="source/net/ipv4/ip_fragment.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/ip_fragment.c#L378">378</a>         <a href="ident?i=err">err</a> = <a href="ident?i=pskb_trim_rcsum">pskb_trim_rcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=end">end</a> - <a href="ident?i=offset">offset</a>);
<a name="L379" href="source/net/ipv4/ip_fragment.c#L379">379</a>         if (<a href="ident?i=err">err</a>)
<a name="L380" href="source/net/ipv4/ip_fragment.c#L380">380</a>                 goto <a href="ident?i=err">err</a>;
<a name="L381" href="source/net/ipv4/ip_fragment.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/ip_fragment.c#L382">382</a>         <b><i>/* Find out which fragments are in front and at the back of us</i></b>
<a name="L383" href="source/net/ipv4/ip_fragment.c#L383">383</a> <b><i>         * in the chain of fragments so far.  We must know where to put</i></b>
<a name="L384" href="source/net/ipv4/ip_fragment.c#L384">384</a> <b><i>         * this fragment, right?</i></b>
<a name="L385" href="source/net/ipv4/ip_fragment.c#L385">385</a> <b><i>         */</i></b>
<a name="L386" href="source/net/ipv4/ip_fragment.c#L386">386</a>         prev = <a href="ident?i=qp">qp</a>-&gt;q.fragments_tail;
<a name="L387" href="source/net/ipv4/ip_fragment.c#L387">387</a>         if (!prev || <a href="ident?i=FRAG_CB">FRAG_CB</a>(prev)-&gt;<a href="ident?i=offset">offset</a> &lt; <a href="ident?i=offset">offset</a>) {
<a name="L388" href="source/net/ipv4/ip_fragment.c#L388">388</a>                 <a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L389" href="source/net/ipv4/ip_fragment.c#L389">389</a>                 goto <a href="ident?i=found">found</a>;
<a name="L390" href="source/net/ipv4/ip_fragment.c#L390">390</a>         }
<a name="L391" href="source/net/ipv4/ip_fragment.c#L391">391</a>         prev = <a href="ident?i=NULL">NULL</a>;
<a name="L392" href="source/net/ipv4/ip_fragment.c#L392">392</a>         for (<a href="ident?i=next">next</a> = <a href="ident?i=qp">qp</a>-&gt;q.fragments; <a href="ident?i=next">next</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=next">next</a> = <a href="ident?i=next">next</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L393" href="source/net/ipv4/ip_fragment.c#L393">393</a>                 if (<a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=next">next</a>)-&gt;<a href="ident?i=offset">offset</a> &gt;= <a href="ident?i=offset">offset</a>)
<a name="L394" href="source/net/ipv4/ip_fragment.c#L394">394</a>                         break;  <b><i>/* bingo! */</i></b>
<a name="L395" href="source/net/ipv4/ip_fragment.c#L395">395</a>                 prev = <a href="ident?i=next">next</a>;
<a name="L396" href="source/net/ipv4/ip_fragment.c#L396">396</a>         }
<a name="L397" href="source/net/ipv4/ip_fragment.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/ip_fragment.c#L398">398</a> <a href="ident?i=found">found</a>:
<a name="L399" href="source/net/ipv4/ip_fragment.c#L399">399</a>         <b><i>/* We found where to put this one.  Check for overlap with</i></b>
<a name="L400" href="source/net/ipv4/ip_fragment.c#L400">400</a> <b><i>         * preceding fragment, and, if needed, align things so that</i></b>
<a name="L401" href="source/net/ipv4/ip_fragment.c#L401">401</a> <b><i>         * any overlaps are eliminated.</i></b>
<a name="L402" href="source/net/ipv4/ip_fragment.c#L402">402</a> <b><i>         */</i></b>
<a name="L403" href="source/net/ipv4/ip_fragment.c#L403">403</a>         if (prev) {
<a name="L404" href="source/net/ipv4/ip_fragment.c#L404">404</a>                 int <a href="ident?i=i">i</a> = (<a href="ident?i=FRAG_CB">FRAG_CB</a>(prev)-&gt;<a href="ident?i=offset">offset</a> + prev-&gt;<a href="ident?i=len">len</a>) - <a href="ident?i=offset">offset</a>;
<a name="L405" href="source/net/ipv4/ip_fragment.c#L405">405</a> 
<a name="L406" href="source/net/ipv4/ip_fragment.c#L406">406</a>                 if (<a href="ident?i=i">i</a> &gt; 0) {
<a name="L407" href="source/net/ipv4/ip_fragment.c#L407">407</a>                         <a href="ident?i=offset">offset</a> += <a href="ident?i=i">i</a>;
<a name="L408" href="source/net/ipv4/ip_fragment.c#L408">408</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L409" href="source/net/ipv4/ip_fragment.c#L409">409</a>                         if (<a href="ident?i=end">end</a> &lt;= <a href="ident?i=offset">offset</a>)
<a name="L410" href="source/net/ipv4/ip_fragment.c#L410">410</a>                                 goto <a href="ident?i=err">err</a>;
<a name="L411" href="source/net/ipv4/ip_fragment.c#L411">411</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L412" href="source/net/ipv4/ip_fragment.c#L412">412</a>                         if (!<a href="ident?i=pskb_pull">pskb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>))
<a name="L413" href="source/net/ipv4/ip_fragment.c#L413">413</a>                                 goto <a href="ident?i=err">err</a>;
<a name="L414" href="source/net/ipv4/ip_fragment.c#L414">414</a>                         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_UNNECESSARY">CHECKSUM_UNNECESSARY</a>)
<a name="L415" href="source/net/ipv4/ip_fragment.c#L415">415</a>                                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L416" href="source/net/ipv4/ip_fragment.c#L416">416</a>                 }
<a name="L417" href="source/net/ipv4/ip_fragment.c#L417">417</a>         }
<a name="L418" href="source/net/ipv4/ip_fragment.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/ip_fragment.c#L419">419</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L420" href="source/net/ipv4/ip_fragment.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/ip_fragment.c#L421">421</a>         while (<a href="ident?i=next">next</a> &amp;&amp; <a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=next">next</a>)-&gt;<a href="ident?i=offset">offset</a> &lt; <a href="ident?i=end">end</a>) {
<a name="L422" href="source/net/ipv4/ip_fragment.c#L422">422</a>                 int <a href="ident?i=i">i</a> = <a href="ident?i=end">end</a> - <a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=next">next</a>)-&gt;<a href="ident?i=offset">offset</a>; <b><i>/* overlap is 'i' bytes */</i></b>
<a name="L423" href="source/net/ipv4/ip_fragment.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/ip_fragment.c#L424">424</a>                 if (<a href="ident?i=i">i</a> &lt; <a href="ident?i=next">next</a>-&gt;<a href="ident?i=len">len</a>) {
<a name="L425" href="source/net/ipv4/ip_fragment.c#L425">425</a>                         <b><i>/* Eat head of the next overlapped fragment</i></b>
<a name="L426" href="source/net/ipv4/ip_fragment.c#L426">426</a> <b><i>                         * and leave the loop. The next ones cannot overlap.</i></b>
<a name="L427" href="source/net/ipv4/ip_fragment.c#L427">427</a> <b><i>                         */</i></b>
<a name="L428" href="source/net/ipv4/ip_fragment.c#L428">428</a>                         if (!<a href="ident?i=pskb_pull">pskb_pull</a>(<a href="ident?i=next">next</a>, <a href="ident?i=i">i</a>))
<a name="L429" href="source/net/ipv4/ip_fragment.c#L429">429</a>                                 goto <a href="ident?i=err">err</a>;
<a name="L430" href="source/net/ipv4/ip_fragment.c#L430">430</a>                         <a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=next">next</a>)-&gt;<a href="ident?i=offset">offset</a> += <a href="ident?i=i">i</a>;
<a name="L431" href="source/net/ipv4/ip_fragment.c#L431">431</a>                         <a href="ident?i=qp">qp</a>-&gt;q.meat -= <a href="ident?i=i">i</a>;
<a name="L432" href="source/net/ipv4/ip_fragment.c#L432">432</a>                         if (<a href="ident?i=next">next</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_UNNECESSARY">CHECKSUM_UNNECESSARY</a>)
<a name="L433" href="source/net/ipv4/ip_fragment.c#L433">433</a>                                 <a href="ident?i=next">next</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L434" href="source/net/ipv4/ip_fragment.c#L434">434</a>                         break;
<a name="L435" href="source/net/ipv4/ip_fragment.c#L435">435</a>                 } else {
<a name="L436" href="source/net/ipv4/ip_fragment.c#L436">436</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *free_it = <a href="ident?i=next">next</a>;
<a name="L437" href="source/net/ipv4/ip_fragment.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ip_fragment.c#L438">438</a>                         <b><i>/* Old fragment is completely overridden with</i></b>
<a name="L439" href="source/net/ipv4/ip_fragment.c#L439">439</a> <b><i>                         * new one drop it.</i></b>
<a name="L440" href="source/net/ipv4/ip_fragment.c#L440">440</a> <b><i>                         */</i></b>
<a name="L441" href="source/net/ipv4/ip_fragment.c#L441">441</a>                         <a href="ident?i=next">next</a> = <a href="ident?i=next">next</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L442" href="source/net/ipv4/ip_fragment.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/ip_fragment.c#L443">443</a>                         if (prev)
<a name="L444" href="source/net/ipv4/ip_fragment.c#L444">444</a>                                 prev-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=next">next</a>;
<a name="L445" href="source/net/ipv4/ip_fragment.c#L445">445</a>                         else
<a name="L446" href="source/net/ipv4/ip_fragment.c#L446">446</a>                                 <a href="ident?i=qp">qp</a>-&gt;q.fragments = <a href="ident?i=next">next</a>;
<a name="L447" href="source/net/ipv4/ip_fragment.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/ip_fragment.c#L448">448</a>                         <a href="ident?i=qp">qp</a>-&gt;q.meat -= free_it-&gt;<a href="ident?i=len">len</a>;
<a name="L449" href="source/net/ipv4/ip_fragment.c#L449">449</a>                         <a href="ident?i=sub_frag_mem_limit">sub_frag_mem_limit</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q, free_it-&gt;truesize);
<a name="L450" href="source/net/ipv4/ip_fragment.c#L450">450</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(free_it);
<a name="L451" href="source/net/ipv4/ip_fragment.c#L451">451</a>                 }
<a name="L452" href="source/net/ipv4/ip_fragment.c#L452">452</a>         }
<a name="L453" href="source/net/ipv4/ip_fragment.c#L453">453</a> 
<a name="L454" href="source/net/ipv4/ip_fragment.c#L454">454</a>         <a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=offset">offset</a> = <a href="ident?i=offset">offset</a>;
<a name="L455" href="source/net/ipv4/ip_fragment.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/ip_fragment.c#L456">456</a>         <b><i>/* Insert this fragment in the chain of fragments. */</i></b>
<a name="L457" href="source/net/ipv4/ip_fragment.c#L457">457</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=next">next</a>;
<a name="L458" href="source/net/ipv4/ip_fragment.c#L458">458</a>         if (!<a href="ident?i=next">next</a>)
<a name="L459" href="source/net/ipv4/ip_fragment.c#L459">459</a>                 <a href="ident?i=qp">qp</a>-&gt;q.fragments_tail = <a href="ident?i=skb">skb</a>;
<a name="L460" href="source/net/ipv4/ip_fragment.c#L460">460</a>         if (prev)
<a name="L461" href="source/net/ipv4/ip_fragment.c#L461">461</a>                 prev-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=skb">skb</a>;
<a name="L462" href="source/net/ipv4/ip_fragment.c#L462">462</a>         else
<a name="L463" href="source/net/ipv4/ip_fragment.c#L463">463</a>                 <a href="ident?i=qp">qp</a>-&gt;q.fragments = <a href="ident?i=skb">skb</a>;
<a name="L464" href="source/net/ipv4/ip_fragment.c#L464">464</a> 
<a name="L465" href="source/net/ipv4/ip_fragment.c#L465">465</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L466" href="source/net/ipv4/ip_fragment.c#L466">466</a>         if (<a href="ident?i=dev">dev</a>) {
<a name="L467" href="source/net/ipv4/ip_fragment.c#L467">467</a>                 <a href="ident?i=qp">qp</a>-&gt;iif = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L468" href="source/net/ipv4/ip_fragment.c#L468">468</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L469" href="source/net/ipv4/ip_fragment.c#L469">469</a>         }
<a name="L470" href="source/net/ipv4/ip_fragment.c#L470">470</a>         <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=stamp">stamp</a> = <a href="ident?i=skb">skb</a>-&gt;tstamp;
<a name="L471" href="source/net/ipv4/ip_fragment.c#L471">471</a>         <a href="ident?i=qp">qp</a>-&gt;q.meat += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L472" href="source/net/ipv4/ip_fragment.c#L472">472</a>         <a href="ident?i=qp">qp</a>-&gt;ecn |= ecn;
<a name="L473" href="source/net/ipv4/ip_fragment.c#L473">473</a>         <a href="ident?i=add_frag_mem_limit">add_frag_mem_limit</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q, <a href="ident?i=skb">skb</a>-&gt;truesize);
<a name="L474" href="source/net/ipv4/ip_fragment.c#L474">474</a>         if (<a href="ident?i=offset">offset</a> == 0)
<a name="L475" href="source/net/ipv4/ip_fragment.c#L475">475</a>                 <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> |= INET_FRAG_FIRST_IN;
<a name="L476" href="source/net/ipv4/ip_fragment.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/ip_fragment.c#L477">477</a>         if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>) &amp;&amp;
<a name="L478" href="source/net/ipv4/ip_fragment.c#L478">478</a>             <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + ihl &gt; <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=max_size">max_size</a>)
<a name="L479" href="source/net/ipv4/ip_fragment.c#L479">479</a>                 <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=max_size">max_size</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + ihl;
<a name="L480" href="source/net/ipv4/ip_fragment.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/ip_fragment.c#L481">481</a>         if (<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=flags">flags</a> == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &amp;&amp;
<a name="L482" href="source/net/ipv4/ip_fragment.c#L482">482</a>             <a href="ident?i=qp">qp</a>-&gt;q.meat == <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a>) {
<a name="L483" href="source/net/ipv4/ip_fragment.c#L483">483</a>                 unsigned long orefdst = <a href="ident?i=skb">skb</a>-&gt;_skb_refdst;
<a name="L484" href="source/net/ipv4/ip_fragment.c#L484">484</a> 
<a name="L485" href="source/net/ipv4/ip_fragment.c#L485">485</a>                 <a href="ident?i=skb">skb</a>-&gt;_skb_refdst = 0UL;
<a name="L486" href="source/net/ipv4/ip_fragment.c#L486">486</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_frag_reasm">ip_frag_reasm</a>(<a href="ident?i=qp">qp</a>, prev, <a href="ident?i=dev">dev</a>);
<a name="L487" href="source/net/ipv4/ip_fragment.c#L487">487</a>                 <a href="ident?i=skb">skb</a>-&gt;_skb_refdst = orefdst;
<a name="L488" href="source/net/ipv4/ip_fragment.c#L488">488</a>                 return <a href="ident?i=err">err</a>;
<a name="L489" href="source/net/ipv4/ip_fragment.c#L489">489</a>         }
<a name="L490" href="source/net/ipv4/ip_fragment.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/ip_fragment.c#L491">491</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L492" href="source/net/ipv4/ip_fragment.c#L492">492</a>         return -<a href="ident?i=EINPROGRESS">EINPROGRESS</a>;
<a name="L493" href="source/net/ipv4/ip_fragment.c#L493">493</a> 
<a name="L494" href="source/net/ipv4/ip_fragment.c#L494">494</a> <a href="ident?i=err">err</a>:
<a name="L495" href="source/net/ipv4/ip_fragment.c#L495">495</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L496" href="source/net/ipv4/ip_fragment.c#L496">496</a>         return <a href="ident?i=err">err</a>;
<a name="L497" href="source/net/ipv4/ip_fragment.c#L497">497</a> }
<a name="L498" href="source/net/ipv4/ip_fragment.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/ip_fragment.c#L499">499</a> 
<a name="L500" href="source/net/ipv4/ip_fragment.c#L500">500</a> <b><i>/* Build a new IP datagram from all its fragments. */</i></b>
<a name="L501" href="source/net/ipv4/ip_fragment.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/ip_fragment.c#L502">502</a> static int <a href="ident?i=ip_frag_reasm">ip_frag_reasm</a>(struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *prev,
<a name="L503" href="source/net/ipv4/ip_fragment.c#L503">503</a>                          struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L504" href="source/net/ipv4/ip_fragment.c#L504">504</a> {
<a name="L505" href="source/net/ipv4/ip_fragment.c#L505">505</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=net">net</a>, struct <a href="ident?i=net">net</a>, ipv4.frags);
<a name="L506" href="source/net/ipv4/ip_fragment.c#L506">506</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L507" href="source/net/ipv4/ip_fragment.c#L507">507</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=fp">fp</a>, *<a href="ident?i=head">head</a> = <a href="ident?i=qp">qp</a>-&gt;q.fragments;
<a name="L508" href="source/net/ipv4/ip_fragment.c#L508">508</a>         int <a href="ident?i=len">len</a>;
<a name="L509" href="source/net/ipv4/ip_fragment.c#L509">509</a>         int ihlen;
<a name="L510" href="source/net/ipv4/ip_fragment.c#L510">510</a>         int <a href="ident?i=err">err</a>;
<a name="L511" href="source/net/ipv4/ip_fragment.c#L511">511</a>         int sum_truesize;
<a name="L512" href="source/net/ipv4/ip_fragment.c#L512">512</a>         <a href="ident?i=u8">u8</a> ecn;
<a name="L513" href="source/net/ipv4/ip_fragment.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/ip_fragment.c#L514">514</a>         <a href="ident?i=ipq_kill">ipq_kill</a>(<a href="ident?i=qp">qp</a>);
<a name="L515" href="source/net/ipv4/ip_fragment.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/ip_fragment.c#L516">516</a>         ecn = <a href="ident?i=ip_frag_ecn_table">ip_frag_ecn_table</a>[<a href="ident?i=qp">qp</a>-&gt;ecn];
<a name="L517" href="source/net/ipv4/ip_fragment.c#L517">517</a>         if (<a href="ident?i=unlikely">unlikely</a>(ecn == 0xff)) {
<a name="L518" href="source/net/ipv4/ip_fragment.c#L518">518</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L519" href="source/net/ipv4/ip_fragment.c#L519">519</a>                 goto out_fail;
<a name="L520" href="source/net/ipv4/ip_fragment.c#L520">520</a>         }
<a name="L521" href="source/net/ipv4/ip_fragment.c#L521">521</a>         <b><i>/* Make the one we just received the head. */</i></b>
<a name="L522" href="source/net/ipv4/ip_fragment.c#L522">522</a>         if (prev) {
<a name="L523" href="source/net/ipv4/ip_fragment.c#L523">523</a>                 <a href="ident?i=head">head</a> = prev-&gt;<a href="ident?i=next">next</a>;
<a name="L524" href="source/net/ipv4/ip_fragment.c#L524">524</a>                 <a href="ident?i=fp">fp</a> = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=head">head</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L525" href="source/net/ipv4/ip_fragment.c#L525">525</a>                 if (!<a href="ident?i=fp">fp</a>)
<a name="L526" href="source/net/ipv4/ip_fragment.c#L526">526</a>                         goto out_nomem;
<a name="L527" href="source/net/ipv4/ip_fragment.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/ip_fragment.c#L528">528</a>                 <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L529" href="source/net/ipv4/ip_fragment.c#L529">529</a>                 if (!<a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=next">next</a>)
<a name="L530" href="source/net/ipv4/ip_fragment.c#L530">530</a>                         <a href="ident?i=qp">qp</a>-&gt;q.fragments_tail = <a href="ident?i=fp">fp</a>;
<a name="L531" href="source/net/ipv4/ip_fragment.c#L531">531</a>                 prev-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=fp">fp</a>;
<a name="L532" href="source/net/ipv4/ip_fragment.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/ip_fragment.c#L533">533</a>                 <a href="ident?i=skb_morph">skb_morph</a>(<a href="ident?i=head">head</a>, <a href="ident?i=qp">qp</a>-&gt;q.fragments);
<a name="L534" href="source/net/ipv4/ip_fragment.c#L534">534</a>                 <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=qp">qp</a>-&gt;q.fragments-&gt;<a href="ident?i=next">next</a>;
<a name="L535" href="source/net/ipv4/ip_fragment.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/ip_fragment.c#L536">536</a>                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=qp">qp</a>-&gt;q.fragments);
<a name="L537" href="source/net/ipv4/ip_fragment.c#L537">537</a>                 <a href="ident?i=qp">qp</a>-&gt;q.fragments = <a href="ident?i=head">head</a>;
<a name="L538" href="source/net/ipv4/ip_fragment.c#L538">538</a>         }
<a name="L539" href="source/net/ipv4/ip_fragment.c#L539">539</a> 
<a name="L540" href="source/net/ipv4/ip_fragment.c#L540">540</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=head">head</a>);
<a name="L541" href="source/net/ipv4/ip_fragment.c#L541">541</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=FRAG_CB">FRAG_CB</a>(<a href="ident?i=head">head</a>)-&gt;<a href="ident?i=offset">offset</a> != 0);
<a name="L542" href="source/net/ipv4/ip_fragment.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/ip_fragment.c#L543">543</a>         <b><i>/* Allocate a new buffer for the datagram. */</i></b>
<a name="L544" href="source/net/ipv4/ip_fragment.c#L544">544</a>         ihlen = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=head">head</a>);
<a name="L545" href="source/net/ipv4/ip_fragment.c#L545">545</a>         <a href="ident?i=len">len</a> = ihlen + <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=len">len</a>;
<a name="L546" href="source/net/ipv4/ip_fragment.c#L546">546</a> 
<a name="L547" href="source/net/ipv4/ip_fragment.c#L547">547</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=E2BIG">E2BIG</a>;
<a name="L548" href="source/net/ipv4/ip_fragment.c#L548">548</a>         if (<a href="ident?i=len">len</a> &gt; 65535)
<a name="L549" href="source/net/ipv4/ip_fragment.c#L549">549</a>                 goto out_oversize;
<a name="L550" href="source/net/ipv4/ip_fragment.c#L550">550</a> 
<a name="L551" href="source/net/ipv4/ip_fragment.c#L551">551</a>         <b><i>/* Head of list must not be cloned. */</i></b>
<a name="L552" href="source/net/ipv4/ip_fragment.c#L552">552</a>         if (<a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=head">head</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L553" href="source/net/ipv4/ip_fragment.c#L553">553</a>                 goto out_nomem;
<a name="L554" href="source/net/ipv4/ip_fragment.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/ip_fragment.c#L555">555</a>         <b><i>/* If the first fragment is fragmented itself, we split</i></b>
<a name="L556" href="source/net/ipv4/ip_fragment.c#L556">556</a> <b><i>         * it to two chunks: the first with data and paged part</i></b>
<a name="L557" href="source/net/ipv4/ip_fragment.c#L557">557</a> <b><i>         * and the second, holding only fragments. */</i></b>
<a name="L558" href="source/net/ipv4/ip_fragment.c#L558">558</a>         if (<a href="ident?i=skb_has_frag_list">skb_has_frag_list</a>(<a href="ident?i=head">head</a>)) {
<a name="L559" href="source/net/ipv4/ip_fragment.c#L559">559</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *clone;
<a name="L560" href="source/net/ipv4/ip_fragment.c#L560">560</a>                 int <a href="ident?i=i">i</a>, plen = 0;
<a name="L561" href="source/net/ipv4/ip_fragment.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/ip_fragment.c#L562">562</a>                 clone = <a href="ident?i=alloc_skb">alloc_skb</a>(0, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L563" href="source/net/ipv4/ip_fragment.c#L563">563</a>                 if (!clone)
<a name="L564" href="source/net/ipv4/ip_fragment.c#L564">564</a>                         goto out_nomem;
<a name="L565" href="source/net/ipv4/ip_fragment.c#L565">565</a>                 clone-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L566" href="source/net/ipv4/ip_fragment.c#L566">566</a>                 <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a> = clone;
<a name="L567" href="source/net/ipv4/ip_fragment.c#L567">567</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(clone)-&gt;frag_list = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=head">head</a>)-&gt;frag_list;
<a name="L568" href="source/net/ipv4/ip_fragment.c#L568">568</a>                 <a href="ident?i=skb_frag_list_init">skb_frag_list_init</a>(<a href="ident?i=head">head</a>);
<a name="L569" href="source/net/ipv4/ip_fragment.c#L569">569</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=head">head</a>)-&gt;nr_frags; <a href="ident?i=i">i</a>++)
<a name="L570" href="source/net/ipv4/ip_fragment.c#L570">570</a>                         plen += <a href="ident?i=skb_frag_size">skb_frag_size</a>(&amp;<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=head">head</a>)-&gt;frags[<a href="ident?i=i">i</a>]);
<a name="L571" href="source/net/ipv4/ip_fragment.c#L571">571</a>                 clone-&gt;<a href="ident?i=len">len</a> = clone-&gt;<a href="ident?i=data_len">data_len</a> = <a href="ident?i=head">head</a>-&gt;<a href="ident?i=data_len">data_len</a> - plen;
<a name="L572" href="source/net/ipv4/ip_fragment.c#L572">572</a>                 <a href="ident?i=head">head</a>-&gt;<a href="ident?i=data_len">data_len</a> -= clone-&gt;<a href="ident?i=len">len</a>;
<a name="L573" href="source/net/ipv4/ip_fragment.c#L573">573</a>                 <a href="ident?i=head">head</a>-&gt;<a href="ident?i=len">len</a> -= clone-&gt;<a href="ident?i=len">len</a>;
<a name="L574" href="source/net/ipv4/ip_fragment.c#L574">574</a>                 clone-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L575" href="source/net/ipv4/ip_fragment.c#L575">575</a>                 clone-&gt;ip_summed = <a href="ident?i=head">head</a>-&gt;ip_summed;
<a name="L576" href="source/net/ipv4/ip_fragment.c#L576">576</a>                 <a href="ident?i=add_frag_mem_limit">add_frag_mem_limit</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q, clone-&gt;truesize);
<a name="L577" href="source/net/ipv4/ip_fragment.c#L577">577</a>         }
<a name="L578" href="source/net/ipv4/ip_fragment.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/ip_fragment.c#L579">579</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=head">head</a>, <a href="ident?i=head">head</a>-&gt;<a href="ident?i=data">data</a> - <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=head">head</a>));
<a name="L580" href="source/net/ipv4/ip_fragment.c#L580">580</a> 
<a name="L581" href="source/net/ipv4/ip_fragment.c#L581">581</a>         sum_truesize = <a href="ident?i=head">head</a>-&gt;truesize;
<a name="L582" href="source/net/ipv4/ip_fragment.c#L582">582</a>         for (<a href="ident?i=fp">fp</a> = <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a>; <a href="ident?i=fp">fp</a>;) {
<a name="L583" href="source/net/ipv4/ip_fragment.c#L583">583</a>                 <a href="ident?i=bool">bool</a> headstolen;
<a name="L584" href="source/net/ipv4/ip_fragment.c#L584">584</a>                 int <a href="ident?i=delta">delta</a>;
<a name="L585" href="source/net/ipv4/ip_fragment.c#L585">585</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=next">next</a> = <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L586" href="source/net/ipv4/ip_fragment.c#L586">586</a> 
<a name="L587" href="source/net/ipv4/ip_fragment.c#L587">587</a>                 sum_truesize += <a href="ident?i=fp">fp</a>-&gt;truesize;
<a name="L588" href="source/net/ipv4/ip_fragment.c#L588">588</a>                 if (<a href="ident?i=head">head</a>-&gt;ip_summed != <a href="ident?i=fp">fp</a>-&gt;ip_summed)
<a name="L589" href="source/net/ipv4/ip_fragment.c#L589">589</a>                         <a href="ident?i=head">head</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L590" href="source/net/ipv4/ip_fragment.c#L590">590</a>                 else if (<a href="ident?i=head">head</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_COMPLETE">CHECKSUM_COMPLETE</a>)
<a name="L591" href="source/net/ipv4/ip_fragment.c#L591">591</a>                         <a href="ident?i=head">head</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_add">csum_add</a>(<a href="ident?i=head">head</a>-&gt;<a href="ident?i=csum">csum</a>, <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=csum">csum</a>);
<a name="L592" href="source/net/ipv4/ip_fragment.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/ip_fragment.c#L593">593</a>                 if (<a href="ident?i=skb_try_coalesce">skb_try_coalesce</a>(<a href="ident?i=head">head</a>, <a href="ident?i=fp">fp</a>, &amp;headstolen, &amp;<a href="ident?i=delta">delta</a>)) {
<a name="L594" href="source/net/ipv4/ip_fragment.c#L594">594</a>                         <a href="ident?i=kfree_skb_partial">kfree_skb_partial</a>(<a href="ident?i=fp">fp</a>, headstolen);
<a name="L595" href="source/net/ipv4/ip_fragment.c#L595">595</a>                 } else {
<a name="L596" href="source/net/ipv4/ip_fragment.c#L596">596</a>                         if (!<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=head">head</a>)-&gt;frag_list)
<a name="L597" href="source/net/ipv4/ip_fragment.c#L597">597</a>                                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=head">head</a>)-&gt;frag_list = <a href="ident?i=fp">fp</a>;
<a name="L598" href="source/net/ipv4/ip_fragment.c#L598">598</a>                         <a href="ident?i=head">head</a>-&gt;<a href="ident?i=data_len">data_len</a> += <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L599" href="source/net/ipv4/ip_fragment.c#L599">599</a>                         <a href="ident?i=head">head</a>-&gt;<a href="ident?i=len">len</a> += <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L600" href="source/net/ipv4/ip_fragment.c#L600">600</a>                         <a href="ident?i=head">head</a>-&gt;truesize += <a href="ident?i=fp">fp</a>-&gt;truesize;
<a name="L601" href="source/net/ipv4/ip_fragment.c#L601">601</a>                 }
<a name="L602" href="source/net/ipv4/ip_fragment.c#L602">602</a>                 <a href="ident?i=fp">fp</a> = <a href="ident?i=next">next</a>;
<a name="L603" href="source/net/ipv4/ip_fragment.c#L603">603</a>         }
<a name="L604" href="source/net/ipv4/ip_fragment.c#L604">604</a>         <a href="ident?i=sub_frag_mem_limit">sub_frag_mem_limit</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q, sum_truesize);
<a name="L605" href="source/net/ipv4/ip_fragment.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/ip_fragment.c#L606">606</a>         <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L607" href="source/net/ipv4/ip_fragment.c#L607">607</a>         <a href="ident?i=head">head</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L608" href="source/net/ipv4/ip_fragment.c#L608">608</a>         <a href="ident?i=head">head</a>-&gt;tstamp = <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=stamp">stamp</a>;
<a name="L609" href="source/net/ipv4/ip_fragment.c#L609">609</a>         <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=head">head</a>)-&gt;frag_max_size = <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=max_size">max_size</a>;
<a name="L610" href="source/net/ipv4/ip_fragment.c#L610">610</a> 
<a name="L611" href="source/net/ipv4/ip_fragment.c#L611">611</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=head">head</a>);
<a name="L612" href="source/net/ipv4/ip_fragment.c#L612">612</a>         <b><i>/* max_size != 0 implies at least one fragment had IP_DF set */</i></b>
<a name="L613" href="source/net/ipv4/ip_fragment.c#L613">613</a>         iph-&gt;frag_off = <a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=max_size">max_size</a> ? <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>) : 0;
<a name="L614" href="source/net/ipv4/ip_fragment.c#L614">614</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=len">len</a>);
<a name="L615" href="source/net/ipv4/ip_fragment.c#L615">615</a>         iph-&gt;tos |= ecn;
<a name="L616" href="source/net/ipv4/ip_fragment.c#L616">616</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMOKS);
<a name="L617" href="source/net/ipv4/ip_fragment.c#L617">617</a>         <a href="ident?i=qp">qp</a>-&gt;q.fragments = <a href="ident?i=NULL">NULL</a>;
<a name="L618" href="source/net/ipv4/ip_fragment.c#L618">618</a>         <a href="ident?i=qp">qp</a>-&gt;q.fragments_tail = <a href="ident?i=NULL">NULL</a>;
<a name="L619" href="source/net/ipv4/ip_fragment.c#L619">619</a>         return 0;
<a name="L620" href="source/net/ipv4/ip_fragment.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/ip_fragment.c#L621">621</a> out_nomem:
<a name="L622" href="source/net/ipv4/ip_fragment.c#L622">622</a>         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"queue_glue: no memory for gluing queue %p\n"</i>, <a href="ident?i=qp">qp</a>);
<a name="L623" href="source/net/ipv4/ip_fragment.c#L623">623</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L624" href="source/net/ipv4/ip_fragment.c#L624">624</a>         goto out_fail;
<a name="L625" href="source/net/ipv4/ip_fragment.c#L625">625</a> out_oversize:
<a name="L626" href="source/net/ipv4/ip_fragment.c#L626">626</a>         <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"Oversized IP packet from %pI4\n"</i>, &amp;<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=saddr">saddr</a>);
<a name="L627" href="source/net/ipv4/ip_fragment.c#L627">627</a> out_fail:
<a name="L628" href="source/net/ipv4/ip_fragment.c#L628">628</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMFAILS);
<a name="L629" href="source/net/ipv4/ip_fragment.c#L629">629</a>         return <a href="ident?i=err">err</a>;
<a name="L630" href="source/net/ipv4/ip_fragment.c#L630">630</a> }
<a name="L631" href="source/net/ipv4/ip_fragment.c#L631">631</a> 
<a name="L632" href="source/net/ipv4/ip_fragment.c#L632">632</a> <b><i>/* Process an incoming IP datagram fragment. */</i></b>
<a name="L633" href="source/net/ipv4/ip_fragment.c#L633">633</a> int <a href="ident?i=ip_defrag">ip_defrag</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=user">user</a>)
<a name="L634" href="source/net/ipv4/ip_fragment.c#L634">634</a> {
<a name="L635" href="source/net/ipv4/ip_fragment.c#L635">635</a>         struct <a href="ident?i=ipq">ipq</a> *<a href="ident?i=qp">qp</a>;
<a name="L636" href="source/net/ipv4/ip_fragment.c#L636">636</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L637" href="source/net/ipv4/ip_fragment.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/ip_fragment.c#L638">638</a>         <a href="ident?i=net">net</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> ? <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>) : <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>);
<a name="L639" href="source/net/ipv4/ip_fragment.c#L639">639</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMREQDS);
<a name="L640" href="source/net/ipv4/ip_fragment.c#L640">640</a> 
<a name="L641" href="source/net/ipv4/ip_fragment.c#L641">641</a>         <b><i>/* Lookup (or create) queue header */</i></b>
<a name="L642" href="source/net/ipv4/ip_fragment.c#L642">642</a>         <a href="ident?i=qp">qp</a> = <a href="ident?i=ip_find">ip_find</a>(<a href="ident?i=net">net</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=user">user</a>);
<a name="L643" href="source/net/ipv4/ip_fragment.c#L643">643</a>         if (<a href="ident?i=qp">qp</a>) {
<a name="L644" href="source/net/ipv4/ip_fragment.c#L644">644</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L645" href="source/net/ipv4/ip_fragment.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/ip_fragment.c#L646">646</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=lock">lock</a>);
<a name="L647" href="source/net/ipv4/ip_fragment.c#L647">647</a> 
<a name="L648" href="source/net/ipv4/ip_fragment.c#L648">648</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_frag_queue">ip_frag_queue</a>(<a href="ident?i=qp">qp</a>, <a href="ident?i=skb">skb</a>);
<a name="L649" href="source/net/ipv4/ip_fragment.c#L649">649</a> 
<a name="L650" href="source/net/ipv4/ip_fragment.c#L650">650</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;q.<a href="ident?i=lock">lock</a>);
<a name="L651" href="source/net/ipv4/ip_fragment.c#L651">651</a>                 <a href="ident?i=ipq_put">ipq_put</a>(<a href="ident?i=qp">qp</a>);
<a name="L652" href="source/net/ipv4/ip_fragment.c#L652">652</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L653" href="source/net/ipv4/ip_fragment.c#L653">653</a>         }
<a name="L654" href="source/net/ipv4/ip_fragment.c#L654">654</a> 
<a name="L655" href="source/net/ipv4/ip_fragment.c#L655">655</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_REASMFAILS);
<a name="L656" href="source/net/ipv4/ip_fragment.c#L656">656</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L657" href="source/net/ipv4/ip_fragment.c#L657">657</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L658" href="source/net/ipv4/ip_fragment.c#L658">658</a> }
<a name="L659" href="source/net/ipv4/ip_fragment.c#L659">659</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_defrag">ip_defrag</a>);
<a name="L660" href="source/net/ipv4/ip_fragment.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/ip_fragment.c#L661">661</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=ip_check_defrag">ip_check_defrag</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=user">user</a>)
<a name="L662" href="source/net/ipv4/ip_fragment.c#L662">662</a> {
<a name="L663" href="source/net/ipv4/ip_fragment.c#L663">663</a>         struct <a href="ident?i=iphdr">iphdr</a> iph;
<a name="L664" href="source/net/ipv4/ip_fragment.c#L664">664</a>         int netoff;
<a name="L665" href="source/net/ipv4/ip_fragment.c#L665">665</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>;
<a name="L666" href="source/net/ipv4/ip_fragment.c#L666">666</a> 
<a name="L667" href="source/net/ipv4/ip_fragment.c#L667">667</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L668" href="source/net/ipv4/ip_fragment.c#L668">668</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L669" href="source/net/ipv4/ip_fragment.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/ip_fragment.c#L670">670</a>         netoff = <a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L671" href="source/net/ipv4/ip_fragment.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/ip_fragment.c#L672">672</a>         if (<a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, netoff, &amp;iph, sizeof(iph)) &lt; 0)
<a name="L673" href="source/net/ipv4/ip_fragment.c#L673">673</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L674" href="source/net/ipv4/ip_fragment.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/ip_fragment.c#L675">675</a>         if (iph.ihl &lt; 5 || iph.<a href="ident?i=version">version</a> != 4)
<a name="L676" href="source/net/ipv4/ip_fragment.c#L676">676</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L677" href="source/net/ipv4/ip_fragment.c#L677">677</a> 
<a name="L678" href="source/net/ipv4/ip_fragment.c#L678">678</a>         <a href="ident?i=len">len</a> = <a href="ident?i=ntohs">ntohs</a>(iph.tot_len);
<a name="L679" href="source/net/ipv4/ip_fragment.c#L679">679</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; netoff + <a href="ident?i=len">len</a> || <a href="ident?i=len">len</a> &lt; (iph.ihl * 4))
<a name="L680" href="source/net/ipv4/ip_fragment.c#L680">680</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L681" href="source/net/ipv4/ip_fragment.c#L681">681</a> 
<a name="L682" href="source/net/ipv4/ip_fragment.c#L682">682</a>         if (<a href="ident?i=ip_is_fragment">ip_is_fragment</a>(&amp;iph)) {
<a name="L683" href="source/net/ipv4/ip_fragment.c#L683">683</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_share_check">skb_share_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L684" href="source/net/ipv4/ip_fragment.c#L684">684</a>                 if (<a href="ident?i=skb">skb</a>) {
<a name="L685" href="source/net/ipv4/ip_fragment.c#L685">685</a>                         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, netoff + iph.ihl * 4))
<a name="L686" href="source/net/ipv4/ip_fragment.c#L686">686</a>                                 return <a href="ident?i=skb">skb</a>;
<a name="L687" href="source/net/ipv4/ip_fragment.c#L687">687</a>                         if (<a href="ident?i=pskb_trim_rcsum">pskb_trim_rcsum</a>(<a href="ident?i=skb">skb</a>, netoff + <a href="ident?i=len">len</a>))
<a name="L688" href="source/net/ipv4/ip_fragment.c#L688">688</a>                                 return <a href="ident?i=skb">skb</a>;
<a name="L689" href="source/net/ipv4/ip_fragment.c#L689">689</a>                         <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(struct <a href="ident?i=inet_skb_parm">inet_skb_parm</a>));
<a name="L690" href="source/net/ipv4/ip_fragment.c#L690">690</a>                         if (<a href="ident?i=ip_defrag">ip_defrag</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=user">user</a>))
<a name="L691" href="source/net/ipv4/ip_fragment.c#L691">691</a>                                 return <a href="ident?i=NULL">NULL</a>;
<a name="L692" href="source/net/ipv4/ip_fragment.c#L692">692</a>                         <a href="ident?i=skb_clear_hash">skb_clear_hash</a>(<a href="ident?i=skb">skb</a>);
<a name="L693" href="source/net/ipv4/ip_fragment.c#L693">693</a>                 }
<a name="L694" href="source/net/ipv4/ip_fragment.c#L694">694</a>         }
<a name="L695" href="source/net/ipv4/ip_fragment.c#L695">695</a>         return <a href="ident?i=skb">skb</a>;
<a name="L696" href="source/net/ipv4/ip_fragment.c#L696">696</a> }
<a name="L697" href="source/net/ipv4/ip_fragment.c#L697">697</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_check_defrag">ip_check_defrag</a>);
<a name="L698" href="source/net/ipv4/ip_fragment.c#L698">698</a> 
<a name="L699" href="source/net/ipv4/ip_fragment.c#L699">699</a> #ifdef CONFIG_SYSCTL
<a name="L700" href="source/net/ipv4/ip_fragment.c#L700">700</a> static int <a href="ident?i=zero">zero</a>;
<a name="L701" href="source/net/ipv4/ip_fragment.c#L701">701</a> 
<a name="L702" href="source/net/ipv4/ip_fragment.c#L702">702</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ip4_frags_ns_ctl_table">ip4_frags_ns_ctl_table</a>[] = {
<a name="L703" href="source/net/ipv4/ip_fragment.c#L703">703</a>         {
<a name="L704" href="source/net/ipv4/ip_fragment.c#L704">704</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ipfrag_high_thresh"</i>,
<a name="L705" href="source/net/ipv4/ip_fragment.c#L705">705</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.frags.high_thresh,
<a name="L706" href="source/net/ipv4/ip_fragment.c#L706">706</a>                 .maxlen         = sizeof(int),
<a name="L707" href="source/net/ipv4/ip_fragment.c#L707">707</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L708" href="source/net/ipv4/ip_fragment.c#L708">708</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L709" href="source/net/ipv4/ip_fragment.c#L709">709</a>                 .extra1         = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.frags.low_thresh
<a name="L710" href="source/net/ipv4/ip_fragment.c#L710">710</a>         },
<a name="L711" href="source/net/ipv4/ip_fragment.c#L711">711</a>         {
<a name="L712" href="source/net/ipv4/ip_fragment.c#L712">712</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ipfrag_low_thresh"</i>,
<a name="L713" href="source/net/ipv4/ip_fragment.c#L713">713</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.frags.low_thresh,
<a name="L714" href="source/net/ipv4/ip_fragment.c#L714">714</a>                 .maxlen         = sizeof(int),
<a name="L715" href="source/net/ipv4/ip_fragment.c#L715">715</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L716" href="source/net/ipv4/ip_fragment.c#L716">716</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L717" href="source/net/ipv4/ip_fragment.c#L717">717</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>,
<a name="L718" href="source/net/ipv4/ip_fragment.c#L718">718</a>                 .extra2         = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.frags.high_thresh
<a name="L719" href="source/net/ipv4/ip_fragment.c#L719">719</a>         },
<a name="L720" href="source/net/ipv4/ip_fragment.c#L720">720</a>         {
<a name="L721" href="source/net/ipv4/ip_fragment.c#L721">721</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ipfrag_time"</i>,
<a name="L722" href="source/net/ipv4/ip_fragment.c#L722">722</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.frags.<a href="ident?i=timeout">timeout</a>,
<a name="L723" href="source/net/ipv4/ip_fragment.c#L723">723</a>                 .maxlen         = sizeof(int),
<a name="L724" href="source/net/ipv4/ip_fragment.c#L724">724</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L725" href="source/net/ipv4/ip_fragment.c#L725">725</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L726" href="source/net/ipv4/ip_fragment.c#L726">726</a>         },
<a name="L727" href="source/net/ipv4/ip_fragment.c#L727">727</a>         { }
<a name="L728" href="source/net/ipv4/ip_fragment.c#L728">728</a> };
<a name="L729" href="source/net/ipv4/ip_fragment.c#L729">729</a> 
<a name="L730" href="source/net/ipv4/ip_fragment.c#L730">730</a> <b><i>/* secret interval has been deprecated */</i></b>
<a name="L731" href="source/net/ipv4/ip_fragment.c#L731">731</a> static int <a href="ident?i=ip4_frags_secret_interval_unused">ip4_frags_secret_interval_unused</a>;
<a name="L732" href="source/net/ipv4/ip_fragment.c#L732">732</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ip4_frags_ctl_table">ip4_frags_ctl_table</a>[] = {
<a name="L733" href="source/net/ipv4/ip_fragment.c#L733">733</a>         {
<a name="L734" href="source/net/ipv4/ip_fragment.c#L734">734</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ipfrag_secret_interval"</i>,
<a name="L735" href="source/net/ipv4/ip_fragment.c#L735">735</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=ip4_frags_secret_interval_unused">ip4_frags_secret_interval_unused</a>,
<a name="L736" href="source/net/ipv4/ip_fragment.c#L736">736</a>                 .maxlen         = sizeof(int),
<a name="L737" href="source/net/ipv4/ip_fragment.c#L737">737</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L738" href="source/net/ipv4/ip_fragment.c#L738">738</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L739" href="source/net/ipv4/ip_fragment.c#L739">739</a>         },
<a name="L740" href="source/net/ipv4/ip_fragment.c#L740">740</a>         {
<a name="L741" href="source/net/ipv4/ip_fragment.c#L741">741</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ipfrag_max_dist"</i>,
<a name="L742" href="source/net/ipv4/ip_fragment.c#L742">742</a>                 .<a href="ident?i=data">data</a>           = &amp;sysctl_ipfrag_max_dist,
<a name="L743" href="source/net/ipv4/ip_fragment.c#L743">743</a>                 .maxlen         = sizeof(int),
<a name="L744" href="source/net/ipv4/ip_fragment.c#L744">744</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L745" href="source/net/ipv4/ip_fragment.c#L745">745</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L746" href="source/net/ipv4/ip_fragment.c#L746">746</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>
<a name="L747" href="source/net/ipv4/ip_fragment.c#L747">747</a>         },
<a name="L748" href="source/net/ipv4/ip_fragment.c#L748">748</a>         { }
<a name="L749" href="source/net/ipv4/ip_fragment.c#L749">749</a> };
<a name="L750" href="source/net/ipv4/ip_fragment.c#L750">750</a> 
<a name="L751" href="source/net/ipv4/ip_fragment.c#L751">751</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ip4_frags_ns_ctl_register">ip4_frags_ns_ctl_register</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L752" href="source/net/ipv4/ip_fragment.c#L752">752</a> {
<a name="L753" href="source/net/ipv4/ip_fragment.c#L753">753</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>;
<a name="L754" href="source/net/ipv4/ip_fragment.c#L754">754</a>         struct <a href="ident?i=ctl_table_header">ctl_table_header</a> *<a href="ident?i=hdr">hdr</a>;
<a name="L755" href="source/net/ipv4/ip_fragment.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/ip_fragment.c#L756">756</a>         <a href="ident?i=table">table</a> = <a href="ident?i=ip4_frags_ns_ctl_table">ip4_frags_ns_ctl_table</a>;
<a name="L757" href="source/net/ipv4/ip_fragment.c#L757">757</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>)) {
<a name="L758" href="source/net/ipv4/ip_fragment.c#L758">758</a>                 <a href="ident?i=table">table</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=table">table</a>, sizeof(<a href="ident?i=ip4_frags_ns_ctl_table">ip4_frags_ns_ctl_table</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L759" href="source/net/ipv4/ip_fragment.c#L759">759</a>                 if (!<a href="ident?i=table">table</a>)
<a name="L760" href="source/net/ipv4/ip_fragment.c#L760">760</a>                         goto err_alloc;
<a name="L761" href="source/net/ipv4/ip_fragment.c#L761">761</a> 
<a name="L762" href="source/net/ipv4/ip_fragment.c#L762">762</a>                 <a href="ident?i=table">table</a>[0].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags.high_thresh;
<a name="L763" href="source/net/ipv4/ip_fragment.c#L763">763</a>                 <a href="ident?i=table">table</a>[0].extra1 = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags.low_thresh;
<a name="L764" href="source/net/ipv4/ip_fragment.c#L764">764</a>                 <a href="ident?i=table">table</a>[0].extra2 = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.frags.high_thresh;
<a name="L765" href="source/net/ipv4/ip_fragment.c#L765">765</a>                 <a href="ident?i=table">table</a>[1].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags.low_thresh;
<a name="L766" href="source/net/ipv4/ip_fragment.c#L766">766</a>                 <a href="ident?i=table">table</a>[1].extra2 = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags.high_thresh;
<a name="L767" href="source/net/ipv4/ip_fragment.c#L767">767</a>                 <a href="ident?i=table">table</a>[2].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags.<a href="ident?i=timeout">timeout</a>;
<a name="L768" href="source/net/ipv4/ip_fragment.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/ip_fragment.c#L769">769</a>                 <b><i>/* Don't export sysctls to unprivileged users */</i></b>
<a name="L770" href="source/net/ipv4/ip_fragment.c#L770">770</a>                 if (<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a> != &amp;<a href="ident?i=init_user_ns">init_user_ns</a>)
<a name="L771" href="source/net/ipv4/ip_fragment.c#L771">771</a>                         <a href="ident?i=table">table</a>[0].<a href="ident?i=procname">procname</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L772" href="source/net/ipv4/ip_fragment.c#L772">772</a>         }
<a name="L773" href="source/net/ipv4/ip_fragment.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/ip_fragment.c#L774">774</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(<a href="ident?i=net">net</a>, <i>"net/ipv4"</i>, <a href="ident?i=table">table</a>);
<a name="L775" href="source/net/ipv4/ip_fragment.c#L775">775</a>         if (!<a href="ident?i=hdr">hdr</a>)
<a name="L776" href="source/net/ipv4/ip_fragment.c#L776">776</a>                 goto err_reg;
<a name="L777" href="source/net/ipv4/ip_fragment.c#L777">777</a> 
<a name="L778" href="source/net/ipv4/ip_fragment.c#L778">778</a>         <a href="ident?i=net">net</a>-&gt;ipv4.frags_hdr = <a href="ident?i=hdr">hdr</a>;
<a name="L779" href="source/net/ipv4/ip_fragment.c#L779">779</a>         return 0;
<a name="L780" href="source/net/ipv4/ip_fragment.c#L780">780</a> 
<a name="L781" href="source/net/ipv4/ip_fragment.c#L781">781</a> err_reg:
<a name="L782" href="source/net/ipv4/ip_fragment.c#L782">782</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L783" href="source/net/ipv4/ip_fragment.c#L783">783</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=table">table</a>);
<a name="L784" href="source/net/ipv4/ip_fragment.c#L784">784</a> err_alloc:
<a name="L785" href="source/net/ipv4/ip_fragment.c#L785">785</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L786" href="source/net/ipv4/ip_fragment.c#L786">786</a> }
<a name="L787" href="source/net/ipv4/ip_fragment.c#L787">787</a> 
<a name="L788" href="source/net/ipv4/ip_fragment.c#L788">788</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ip4_frags_ns_ctl_unregister">ip4_frags_ns_ctl_unregister</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L789" href="source/net/ipv4/ip_fragment.c#L789">789</a> {
<a name="L790" href="source/net/ipv4/ip_fragment.c#L790">790</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>;
<a name="L791" href="source/net/ipv4/ip_fragment.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/ip_fragment.c#L792">792</a>         <a href="ident?i=table">table</a> = <a href="ident?i=net">net</a>-&gt;ipv4.frags_hdr-&gt;ctl_table_arg;
<a name="L793" href="source/net/ipv4/ip_fragment.c#L793">793</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.frags_hdr);
<a name="L794" href="source/net/ipv4/ip_fragment.c#L794">794</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=table">table</a>);
<a name="L795" href="source/net/ipv4/ip_fragment.c#L795">795</a> }
<a name="L796" href="source/net/ipv4/ip_fragment.c#L796">796</a> 
<a name="L797" href="source/net/ipv4/ip_fragment.c#L797">797</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ip4_frags_ctl_register">ip4_frags_ctl_register</a>(void)
<a name="L798" href="source/net/ipv4/ip_fragment.c#L798">798</a> {
<a name="L799" href="source/net/ipv4/ip_fragment.c#L799">799</a>         <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(&amp;<a href="ident?i=init_net">init_net</a>, <i>"net/ipv4"</i>, <a href="ident?i=ip4_frags_ctl_table">ip4_frags_ctl_table</a>);
<a name="L800" href="source/net/ipv4/ip_fragment.c#L800">800</a> }
<a name="L801" href="source/net/ipv4/ip_fragment.c#L801">801</a> #else
<a name="L802" href="source/net/ipv4/ip_fragment.c#L802">802</a> static int <a href="ident?i=ip4_frags_ns_ctl_register">ip4_frags_ns_ctl_register</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L803" href="source/net/ipv4/ip_fragment.c#L803">803</a> {
<a name="L804" href="source/net/ipv4/ip_fragment.c#L804">804</a>         return 0;
<a name="L805" href="source/net/ipv4/ip_fragment.c#L805">805</a> }
<a name="L806" href="source/net/ipv4/ip_fragment.c#L806">806</a> 
<a name="L807" href="source/net/ipv4/ip_fragment.c#L807">807</a> static void <a href="ident?i=ip4_frags_ns_ctl_unregister">ip4_frags_ns_ctl_unregister</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L808" href="source/net/ipv4/ip_fragment.c#L808">808</a> {
<a name="L809" href="source/net/ipv4/ip_fragment.c#L809">809</a> }
<a name="L810" href="source/net/ipv4/ip_fragment.c#L810">810</a> 
<a name="L811" href="source/net/ipv4/ip_fragment.c#L811">811</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=ip4_frags_ctl_register">ip4_frags_ctl_register</a>(void)
<a name="L812" href="source/net/ipv4/ip_fragment.c#L812">812</a> {
<a name="L813" href="source/net/ipv4/ip_fragment.c#L813">813</a> }
<a name="L814" href="source/net/ipv4/ip_fragment.c#L814">814</a> #endif
<a name="L815" href="source/net/ipv4/ip_fragment.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/ip_fragment.c#L816">816</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipv4_frags_init_net">ipv4_frags_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L817" href="source/net/ipv4/ip_fragment.c#L817">817</a> {
<a name="L818" href="source/net/ipv4/ip_fragment.c#L818">818</a>         <b><i>/* Fragment cache limits.</i></b>
<a name="L819" href="source/net/ipv4/ip_fragment.c#L819">819</a> <b><i>         *</i></b>
<a name="L820" href="source/net/ipv4/ip_fragment.c#L820">820</a> <b><i>         * The fragment memory accounting code, (tries to) account for</i></b>
<a name="L821" href="source/net/ipv4/ip_fragment.c#L821">821</a> <b><i>         * the real memory usage, by measuring both the size of frag</i></b>
<a name="L822" href="source/net/ipv4/ip_fragment.c#L822">822</a> <b><i>         * queue struct (inet_frag_queue (ipv4:ipq/ipv6:frag_queue))</i></b>
<a name="L823" href="source/net/ipv4/ip_fragment.c#L823">823</a> <b><i>         * and the SKB's truesize.</i></b>
<a name="L824" href="source/net/ipv4/ip_fragment.c#L824">824</a> <b><i>         *</i></b>
<a name="L825" href="source/net/ipv4/ip_fragment.c#L825">825</a> <b><i>         * A 64K fragment consumes 129736 bytes (44*2944)+200</i></b>
<a name="L826" href="source/net/ipv4/ip_fragment.c#L826">826</a> <b><i>         * (1500 truesize == 2944, sizeof(struct ipq) == 200)</i></b>
<a name="L827" href="source/net/ipv4/ip_fragment.c#L827">827</a> <b><i>         *</i></b>
<a name="L828" href="source/net/ipv4/ip_fragment.c#L828">828</a> <b><i>         * We will commit 4MB at one time. Should we cross that limit</i></b>
<a name="L829" href="source/net/ipv4/ip_fragment.c#L829">829</a> <b><i>         * we will prune down to 3MB, making room for approx 8 big 64K</i></b>
<a name="L830" href="source/net/ipv4/ip_fragment.c#L830">830</a> <b><i>         * fragments 8x128k.</i></b>
<a name="L831" href="source/net/ipv4/ip_fragment.c#L831">831</a> <b><i>         */</i></b>
<a name="L832" href="source/net/ipv4/ip_fragment.c#L832">832</a>         <a href="ident?i=net">net</a>-&gt;ipv4.frags.high_thresh = 4 * 1024 * 1024;
<a name="L833" href="source/net/ipv4/ip_fragment.c#L833">833</a>         <a href="ident?i=net">net</a>-&gt;ipv4.frags.low_thresh  = 3 * 1024 * 1024;
<a name="L834" href="source/net/ipv4/ip_fragment.c#L834">834</a>         <b><i>/*</i></b>
<a name="L835" href="source/net/ipv4/ip_fragment.c#L835">835</a> <b><i>         * Important NOTE! Fragment queue must be destroyed before MSL expires.</i></b>
<a name="L836" href="source/net/ipv4/ip_fragment.c#L836">836</a> <b><i>         * RFC791 is wrong proposing to prolongate timer each fragment arrival</i></b>
<a name="L837" href="source/net/ipv4/ip_fragment.c#L837">837</a> <b><i>         * by TTL.</i></b>
<a name="L838" href="source/net/ipv4/ip_fragment.c#L838">838</a> <b><i>         */</i></b>
<a name="L839" href="source/net/ipv4/ip_fragment.c#L839">839</a>         <a href="ident?i=net">net</a>-&gt;ipv4.frags.<a href="ident?i=timeout">timeout</a> = <a href="ident?i=IP_FRAG_TIME">IP_FRAG_TIME</a>;
<a name="L840" href="source/net/ipv4/ip_fragment.c#L840">840</a> 
<a name="L841" href="source/net/ipv4/ip_fragment.c#L841">841</a>         <a href="ident?i=inet_frags_init_net">inet_frags_init_net</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags);
<a name="L842" href="source/net/ipv4/ip_fragment.c#L842">842</a> 
<a name="L843" href="source/net/ipv4/ip_fragment.c#L843">843</a>         return <a href="ident?i=ip4_frags_ns_ctl_register">ip4_frags_ns_ctl_register</a>(<a href="ident?i=net">net</a>);
<a name="L844" href="source/net/ipv4/ip_fragment.c#L844">844</a> }
<a name="L845" href="source/net/ipv4/ip_fragment.c#L845">845</a> 
<a name="L846" href="source/net/ipv4/ip_fragment.c#L846">846</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipv4_frags_exit_net">ipv4_frags_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L847" href="source/net/ipv4/ip_fragment.c#L847">847</a> {
<a name="L848" href="source/net/ipv4/ip_fragment.c#L848">848</a>         <a href="ident?i=ip4_frags_ns_ctl_unregister">ip4_frags_ns_ctl_unregister</a>(<a href="ident?i=net">net</a>);
<a name="L849" href="source/net/ipv4/ip_fragment.c#L849">849</a>         <a href="ident?i=inet_frags_exit_net">inet_frags_exit_net</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.frags, &amp;<a href="ident?i=ip4_frags">ip4_frags</a>);
<a name="L850" href="source/net/ipv4/ip_fragment.c#L850">850</a> }
<a name="L851" href="source/net/ipv4/ip_fragment.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/ip_fragment.c#L852">852</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ip4_frags_ops">ip4_frags_ops</a> = {
<a name="L853" href="source/net/ipv4/ip_fragment.c#L853">853</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipv4_frags_init_net">ipv4_frags_init_net</a>,
<a name="L854" href="source/net/ipv4/ip_fragment.c#L854">854</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipv4_frags_exit_net">ipv4_frags_exit_net</a>,
<a name="L855" href="source/net/ipv4/ip_fragment.c#L855">855</a> };
<a name="L856" href="source/net/ipv4/ip_fragment.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/ip_fragment.c#L857">857</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=ipfrag_init">ipfrag_init</a>(void)
<a name="L858" href="source/net/ipv4/ip_fragment.c#L858">858</a> {
<a name="L859" href="source/net/ipv4/ip_fragment.c#L859">859</a>         <a href="ident?i=ip4_frags_ctl_register">ip4_frags_ctl_register</a>();
<a name="L860" href="source/net/ipv4/ip_fragment.c#L860">860</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ip4_frags_ops">ip4_frags_ops</a>);
<a name="L861" href="source/net/ipv4/ip_fragment.c#L861">861</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.<a href="ident?i=hashfn">hashfn</a> = <a href="ident?i=ip4_hashfn">ip4_hashfn</a>;
<a name="L862" href="source/net/ipv4/ip_fragment.c#L862">862</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.constructor = <a href="ident?i=ip4_frag_init">ip4_frag_init</a>;
<a name="L863" href="source/net/ipv4/ip_fragment.c#L863">863</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.destructor = <a href="ident?i=ip4_frag_free">ip4_frag_free</a>;
<a name="L864" href="source/net/ipv4/ip_fragment.c#L864">864</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.skb_free = <a href="ident?i=NULL">NULL</a>;
<a name="L865" href="source/net/ipv4/ip_fragment.c#L865">865</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.qsize = sizeof(struct <a href="ident?i=ipq">ipq</a>);
<a name="L866" href="source/net/ipv4/ip_fragment.c#L866">866</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.<a href="ident?i=match">match</a> = <a href="ident?i=ip4_frag_match">ip4_frag_match</a>;
<a name="L867" href="source/net/ipv4/ip_fragment.c#L867">867</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.frag_expire = <a href="ident?i=ip_expire">ip_expire</a>;
<a name="L868" href="source/net/ipv4/ip_fragment.c#L868">868</a>         <a href="ident?i=ip4_frags">ip4_frags</a>.frags_cache_name = <a href="ident?i=ip_frag_cache_name">ip_frag_cache_name</a>;
<a name="L869" href="source/net/ipv4/ip_fragment.c#L869">869</a>         if (<a href="ident?i=inet_frags_init">inet_frags_init</a>(&amp;<a href="ident?i=ip4_frags">ip4_frags</a>))
<a name="L870" href="source/net/ipv4/ip_fragment.c#L870">870</a>                 <a href="ident?i=panic">panic</a>(<i>"IP: failed to allocate ip4_frags cache\n"</i>);
<a name="L871" href="source/net/ipv4/ip_fragment.c#L871">871</a> }
<a name="L872" href="source/net/ipv4/ip_fragment.c#L872">872</a> </pre></div><p>
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
