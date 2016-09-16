<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/fou.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/fou.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/fou.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/fou.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/fou.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/fou.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/fou.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/fou.c">fou.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/fou.c#L1">1</a> #include &lt;linux/module.h&gt;
  <a name="L2" href="source/net/ipv4/fou.c#L2">2</a> #include &lt;linux/errno.h&gt;
  <a name="L3" href="source/net/ipv4/fou.c#L3">3</a> #include &lt;linux/socket.h&gt;
  <a name="L4" href="source/net/ipv4/fou.c#L4">4</a> #include &lt;linux/skbuff.h&gt;
  <a name="L5" href="source/net/ipv4/fou.c#L5">5</a> #include &lt;linux/ip.h&gt;
  <a name="L6" href="source/net/ipv4/fou.c#L6">6</a> #include &lt;linux/udp.h&gt;
  <a name="L7" href="source/net/ipv4/fou.c#L7">7</a> #include &lt;linux/types.h&gt;
  <a name="L8" href="source/net/ipv4/fou.c#L8">8</a> #include &lt;linux/kernel.h&gt;
  <a name="L9" href="source/net/ipv4/fou.c#L9">9</a> #include &lt;net/genetlink.h&gt;
 <a name="L10" href="source/net/ipv4/fou.c#L10">10</a> #include &lt;net/gue.h&gt;
 <a name="L11" href="source/net/ipv4/fou.c#L11">11</a> #include &lt;net/ip.h&gt;
 <a name="L12" href="source/net/ipv4/fou.c#L12">12</a> #include &lt;net/protocol.h&gt;
 <a name="L13" href="source/net/ipv4/fou.c#L13">13</a> #include &lt;net/udp.h&gt;
 <a name="L14" href="source/net/ipv4/fou.c#L14">14</a> #include &lt;net/udp_tunnel.h&gt;
 <a name="L15" href="source/net/ipv4/fou.c#L15">15</a> #include &lt;net/xfrm.h&gt;
 <a name="L16" href="source/net/ipv4/fou.c#L16">16</a> #include &lt;uapi/linux/fou.h&gt;
 <a name="L17" href="source/net/ipv4/fou.c#L17">17</a> #include &lt;uapi/linux/genetlink.h&gt;
 <a name="L18" href="source/net/ipv4/fou.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/fou.c#L19">19</a> struct <a href="ident?i=fou">fou</a> {
 <a name="L20" href="source/net/ipv4/fou.c#L20">20</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>;
 <a name="L21" href="source/net/ipv4/fou.c#L21">21</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>;
 <a name="L22" href="source/net/ipv4/fou.c#L22">22</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=flags">flags</a>;
 <a name="L23" href="source/net/ipv4/fou.c#L23">23</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>;
 <a name="L24" href="source/net/ipv4/fou.c#L24">24</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=type">type</a>;
 <a name="L25" href="source/net/ipv4/fou.c#L25">25</a>         struct <a href="ident?i=udp_offload">udp_offload</a> udp_offloads;
 <a name="L26" href="source/net/ipv4/fou.c#L26">26</a>         struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=list">list</a>;
 <a name="L27" href="source/net/ipv4/fou.c#L27">27</a> };
 <a name="L28" href="source/net/ipv4/fou.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/fou.c#L29">29</a> #define <a href="ident?i=FOU_F_REMCSUM_NOPARTIAL">FOU_F_REMCSUM_NOPARTIAL</a> <a href="ident?i=BIT">BIT</a>(0)
 <a name="L30" href="source/net/ipv4/fou.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/fou.c#L31">31</a> struct <a href="ident?i=fou_cfg">fou_cfg</a> {
 <a name="L32" href="source/net/ipv4/fou.c#L32">32</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=type">type</a>;
 <a name="L33" href="source/net/ipv4/fou.c#L33">33</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>;
 <a name="L34" href="source/net/ipv4/fou.c#L34">34</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=flags">flags</a>;
 <a name="L35" href="source/net/ipv4/fou.c#L35">35</a>         struct <a href="ident?i=udp_port_cfg">udp_port_cfg</a> udp_config;
 <a name="L36" href="source/net/ipv4/fou.c#L36">36</a> };
 <a name="L37" href="source/net/ipv4/fou.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/fou.c#L38">38</a> static unsigned int <a href="ident?i=fou_net_id">fou_net_id</a>;
 <a name="L39" href="source/net/ipv4/fou.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/fou.c#L40">40</a> struct <a href="ident?i=fou_net">fou_net</a> {
 <a name="L41" href="source/net/ipv4/fou.c#L41">41</a>         struct <a href="ident?i=list_head">list_head</a> fou_list;
 <a name="L42" href="source/net/ipv4/fou.c#L42">42</a>         struct <a href="ident?i=mutex">mutex</a> fou_lock;
 <a name="L43" href="source/net/ipv4/fou.c#L43">43</a> };
 <a name="L44" href="source/net/ipv4/fou.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/fou.c#L45">45</a> static inline struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou_from_sock">fou_from_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L46" href="source/net/ipv4/fou.c#L46">46</a> {
 <a name="L47" href="source/net/ipv4/fou.c#L47">47</a>         return sk-&gt;sk_user_data;
 <a name="L48" href="source/net/ipv4/fou.c#L48">48</a> }
 <a name="L49" href="source/net/ipv4/fou.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/fou.c#L50">50</a> static void <a href="ident?i=fou_recv_pull">fou_recv_pull</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>)
 <a name="L51" href="source/net/ipv4/fou.c#L51">51</a> {
 <a name="L52" href="source/net/ipv4/fou.c#L52">52</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L53" href="source/net/ipv4/fou.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/fou.c#L54">54</a>         <b><i>/* Remove 'len' bytes from the packet (UDP header and</i></b>
 <a name="L55" href="source/net/ipv4/fou.c#L55">55</a> <b><i>         * FOU header if present).</i></b>
 <a name="L56" href="source/net/ipv4/fou.c#L56">56</a> <b><i>         */</i></b>
 <a name="L57" href="source/net/ipv4/fou.c#L57">57</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(iph-&gt;tot_len) - <a href="ident?i=len">len</a>);
 <a name="L58" href="source/net/ipv4/fou.c#L58">58</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>);
 <a name="L59" href="source/net/ipv4/fou.c#L59">59</a>         <a href="ident?i=skb_postpull_rcsum">skb_postpull_rcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=len">len</a>);
 <a name="L60" href="source/net/ipv4/fou.c#L60">60</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L61" href="source/net/ipv4/fou.c#L61">61</a> }
 <a name="L62" href="source/net/ipv4/fou.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/fou.c#L63">63</a> static int <a href="ident?i=fou_udp_recv">fou_udp_recv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L64" href="source/net/ipv4/fou.c#L64">64</a> {
 <a name="L65" href="source/net/ipv4/fou.c#L65">65</a>         struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a> = <a href="ident?i=fou_from_sock">fou_from_sock</a>(sk);
 <a name="L66" href="source/net/ipv4/fou.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/fou.c#L67">67</a>         if (!<a href="ident?i=fou">fou</a>)
 <a name="L68" href="source/net/ipv4/fou.c#L68">68</a>                 return 1;
 <a name="L69" href="source/net/ipv4/fou.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/fou.c#L70">70</a>         <a href="ident?i=fou_recv_pull">fou_recv_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>));
 <a name="L71" href="source/net/ipv4/fou.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/fou.c#L72">72</a>         return -<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L73" href="source/net/ipv4/fou.c#L73">73</a> }
 <a name="L74" href="source/net/ipv4/fou.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/fou.c#L75">75</a> static struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=gue_remcsum">gue_remcsum</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a>,
 <a name="L76" href="source/net/ipv4/fou.c#L76">76</a>                                   void *<a href="ident?i=data">data</a>, <a href="ident?i=size_t">size_t</a> hdrlen, <a href="ident?i=u8">u8</a> ipproto,
 <a name="L77" href="source/net/ipv4/fou.c#L77">77</a>                                   <a href="ident?i=bool">bool</a> nopartial)
 <a name="L78" href="source/net/ipv4/fou.c#L78">78</a> {
 <a name="L79" href="source/net/ipv4/fou.c#L79">79</a>         <a href="ident?i=__be16">__be16</a> *<a href="ident?i=pd">pd</a> = <a href="ident?i=data">data</a>;
 <a name="L80" href="source/net/ipv4/fou.c#L80">80</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=start">start</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=pd">pd</a>[0]);
 <a name="L81" href="source/net/ipv4/fou.c#L81">81</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=offset">offset</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=pd">pd</a>[1]);
 <a name="L82" href="source/net/ipv4/fou.c#L82">82</a>         <a href="ident?i=size_t">size_t</a> plen = hdrlen + <a href="ident?i=max_t">max_t</a>(<a href="ident?i=size_t">size_t</a>, <a href="ident?i=offset">offset</a> + sizeof(<a href="ident?i=u16">u16</a>), <a href="ident?i=start">start</a>);
 <a name="L83" href="source/net/ipv4/fou.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/fou.c#L84">84</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, plen))
 <a name="L85" href="source/net/ipv4/fou.c#L85">85</a>                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L86" href="source/net/ipv4/fou.c#L86">86</a>         <a href="ident?i=guehdr">guehdr</a> = (struct <a href="ident?i=guehdr">guehdr</a> *)&amp;<a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>)[1];
 <a name="L87" href="source/net/ipv4/fou.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/fou.c#L88">88</a>         <a href="ident?i=skb_remcsum_process">skb_remcsum_process</a>(<a href="ident?i=skb">skb</a>, (void *)<a href="ident?i=guehdr">guehdr</a> + hdrlen,
 <a name="L89" href="source/net/ipv4/fou.c#L89">89</a>                             <a href="ident?i=start">start</a>, <a href="ident?i=offset">offset</a>, nopartial);
 <a name="L90" href="source/net/ipv4/fou.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/fou.c#L91">91</a>         return <a href="ident?i=guehdr">guehdr</a>;
 <a name="L92" href="source/net/ipv4/fou.c#L92">92</a> }
 <a name="L93" href="source/net/ipv4/fou.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/fou.c#L94">94</a> static int <a href="ident?i=gue_control_message">gue_control_message</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a>)
 <a name="L95" href="source/net/ipv4/fou.c#L95">95</a> {
 <a name="L96" href="source/net/ipv4/fou.c#L96">96</a>         <b><i>/* No support yet */</i></b>
 <a name="L97" href="source/net/ipv4/fou.c#L97">97</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
 <a name="L98" href="source/net/ipv4/fou.c#L98">98</a>         return 0;
 <a name="L99" href="source/net/ipv4/fou.c#L99">99</a> }
<a name="L100" href="source/net/ipv4/fou.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/fou.c#L101">101</a> static int <a href="ident?i=gue_udp_recv">gue_udp_recv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L102" href="source/net/ipv4/fou.c#L102">102</a> {
<a name="L103" href="source/net/ipv4/fou.c#L103">103</a>         struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a> = <a href="ident?i=fou_from_sock">fou_from_sock</a>(sk);
<a name="L104" href="source/net/ipv4/fou.c#L104">104</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>, hdrlen;
<a name="L105" href="source/net/ipv4/fou.c#L105">105</a>         struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a>;
<a name="L106" href="source/net/ipv4/fou.c#L106">106</a>         void *<a href="ident?i=data">data</a>;
<a name="L107" href="source/net/ipv4/fou.c#L107">107</a>         <a href="ident?i=u16">u16</a> doffset = 0;
<a name="L108" href="source/net/ipv4/fou.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/fou.c#L109">109</a>         if (!<a href="ident?i=fou">fou</a>)
<a name="L110" href="source/net/ipv4/fou.c#L110">110</a>                 return 1;
<a name="L111" href="source/net/ipv4/fou.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/fou.c#L112">112</a>         <a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=udphdr">udphdr</a>) + sizeof(struct <a href="ident?i=guehdr">guehdr</a>);
<a name="L113" href="source/net/ipv4/fou.c#L113">113</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>))
<a name="L114" href="source/net/ipv4/fou.c#L114">114</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L115" href="source/net/ipv4/fou.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/fou.c#L116">116</a>         <a href="ident?i=guehdr">guehdr</a> = (struct <a href="ident?i=guehdr">guehdr</a> *)&amp;<a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>)[1];
<a name="L117" href="source/net/ipv4/fou.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/fou.c#L118">118</a>         <a href="ident?i=optlen">optlen</a> = <a href="ident?i=guehdr">guehdr</a>-&gt;hlen &lt;&lt; 2;
<a name="L119" href="source/net/ipv4/fou.c#L119">119</a>         <a href="ident?i=len">len</a> += <a href="ident?i=optlen">optlen</a>;
<a name="L120" href="source/net/ipv4/fou.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/fou.c#L121">121</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>))
<a name="L122" href="source/net/ipv4/fou.c#L122">122</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L123" href="source/net/ipv4/fou.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/fou.c#L124">124</a>         <b><i>/* guehdr may change after pull */</i></b>
<a name="L125" href="source/net/ipv4/fou.c#L125">125</a>         <a href="ident?i=guehdr">guehdr</a> = (struct <a href="ident?i=guehdr">guehdr</a> *)&amp;<a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>)[1];
<a name="L126" href="source/net/ipv4/fou.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/fou.c#L127">127</a>         hdrlen = sizeof(struct <a href="ident?i=guehdr">guehdr</a>) + <a href="ident?i=optlen">optlen</a>;
<a name="L128" href="source/net/ipv4/fou.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/fou.c#L129">129</a>         if (<a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=version">version</a> != 0 || <a href="ident?i=validate_gue_flags">validate_gue_flags</a>(<a href="ident?i=guehdr">guehdr</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L130" href="source/net/ipv4/fou.c#L130">130</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L131" href="source/net/ipv4/fou.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/fou.c#L132">132</a>         hdrlen = sizeof(struct <a href="ident?i=guehdr">guehdr</a>) + <a href="ident?i=optlen">optlen</a>;
<a name="L133" href="source/net/ipv4/fou.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/fou.c#L134">134</a>         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tot_len) - <a href="ident?i=len">len</a>);
<a name="L135" href="source/net/ipv4/fou.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/fou.c#L136">136</a>         <b><i>/* Pull csum through the guehdr now . This can be used if</i></b>
<a name="L137" href="source/net/ipv4/fou.c#L137">137</a> <b><i>         * there is a remote checksum offload.</i></b>
<a name="L138" href="source/net/ipv4/fou.c#L138">138</a> <b><i>         */</i></b>
<a name="L139" href="source/net/ipv4/fou.c#L139">139</a>         <a href="ident?i=skb_postpull_rcsum">skb_postpull_rcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=len">len</a>);
<a name="L140" href="source/net/ipv4/fou.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/fou.c#L141">141</a>         <a href="ident?i=data">data</a> = &amp;<a href="ident?i=guehdr">guehdr</a>[1];
<a name="L142" href="source/net/ipv4/fou.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/fou.c#L143">143</a>         if (<a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GUE_FLAG_PRIV">GUE_FLAG_PRIV</a>) {
<a name="L144" href="source/net/ipv4/fou.c#L144">144</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=flags">flags</a> = *(<a href="ident?i=__be32">__be32</a> *)(<a href="ident?i=data">data</a> + doffset);
<a name="L145" href="source/net/ipv4/fou.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/fou.c#L146">146</a>                 doffset += <a href="ident?i=GUE_LEN_PRIV">GUE_LEN_PRIV</a>;
<a name="L147" href="source/net/ipv4/fou.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/fou.c#L148">148</a>                 if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GUE_PFLAG_REMCSUM">GUE_PFLAG_REMCSUM</a>) {
<a name="L149" href="source/net/ipv4/fou.c#L149">149</a>                         <a href="ident?i=guehdr">guehdr</a> = <a href="ident?i=gue_remcsum">gue_remcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=guehdr">guehdr</a>, <a href="ident?i=data">data</a> + doffset,
<a name="L150" href="source/net/ipv4/fou.c#L150">150</a>                                              hdrlen, <a href="ident?i=guehdr">guehdr</a>-&gt;proto_ctype,
<a name="L151" href="source/net/ipv4/fou.c#L151">151</a>                                              !!(<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=flags">flags</a> &amp;
<a name="L152" href="source/net/ipv4/fou.c#L152">152</a>                                                 <a href="ident?i=FOU_F_REMCSUM_NOPARTIAL">FOU_F_REMCSUM_NOPARTIAL</a>));
<a name="L153" href="source/net/ipv4/fou.c#L153">153</a>                         if (!<a href="ident?i=guehdr">guehdr</a>)
<a name="L154" href="source/net/ipv4/fou.c#L154">154</a>                                 goto <a href="ident?i=drop">drop</a>;
<a name="L155" href="source/net/ipv4/fou.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/fou.c#L156">156</a>                         <a href="ident?i=data">data</a> = &amp;<a href="ident?i=guehdr">guehdr</a>[1];
<a name="L157" href="source/net/ipv4/fou.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/fou.c#L158">158</a>                         doffset += <a href="ident?i=GUE_PLEN_REMCSUM">GUE_PLEN_REMCSUM</a>;
<a name="L159" href="source/net/ipv4/fou.c#L159">159</a>                 }
<a name="L160" href="source/net/ipv4/fou.c#L160">160</a>         }
<a name="L161" href="source/net/ipv4/fou.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/fou.c#L162">162</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=guehdr">guehdr</a>-&gt;control))
<a name="L163" href="source/net/ipv4/fou.c#L163">163</a>                 return <a href="ident?i=gue_control_message">gue_control_message</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=guehdr">guehdr</a>);
<a name="L164" href="source/net/ipv4/fou.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/fou.c#L165">165</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>) + hdrlen);
<a name="L166" href="source/net/ipv4/fou.c#L166">166</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L167" href="source/net/ipv4/fou.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/fou.c#L168">168</a>         return -<a href="ident?i=guehdr">guehdr</a>-&gt;proto_ctype;
<a name="L169" href="source/net/ipv4/fou.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/fou.c#L170">170</a> <a href="ident?i=drop">drop</a>:
<a name="L171" href="source/net/ipv4/fou.c#L171">171</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L172" href="source/net/ipv4/fou.c#L172">172</a>         return 0;
<a name="L173" href="source/net/ipv4/fou.c#L173">173</a> }
<a name="L174" href="source/net/ipv4/fou.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/fou.c#L175">175</a> static struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=fou_gro_receive">fou_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>,
<a name="L176" href="source/net/ipv4/fou.c#L176">176</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L177" href="source/net/ipv4/fou.c#L177">177</a>                                         struct <a href="ident?i=udp_offload">udp_offload</a> *uoff)
<a name="L178" href="source/net/ipv4/fou.c#L178">178</a> {
<a name="L179" href="source/net/ipv4/fou.c#L179">179</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L180" href="source/net/ipv4/fou.c#L180">180</a>         struct <a href="ident?i=sk_buff">sk_buff</a> **pp = <a href="ident?i=NULL">NULL</a>;
<a name="L181" href="source/net/ipv4/fou.c#L181">181</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=proto">proto</a> = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=proto">proto</a>;
<a name="L182" href="source/net/ipv4/fou.c#L182">182</a>         const struct <a href="ident?i=net_offload">net_offload</a> **offloads;
<a name="L183" href="source/net/ipv4/fou.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/fou.c#L184">184</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L185" href="source/net/ipv4/fou.c#L185">185</a>         offloads = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;is_ipv6 ? <a href="ident?i=inet6_offloads">inet6_offloads</a> : <a href="ident?i=inet_offloads">inet_offloads</a>;
<a name="L186" href="source/net/ipv4/fou.c#L186">186</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(offloads[<a href="ident?i=proto">proto</a>]);
<a name="L187" href="source/net/ipv4/fou.c#L187">187</a>         if (!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive)
<a name="L188" href="source/net/ipv4/fou.c#L188">188</a>                 goto out_unlock;
<a name="L189" href="source/net/ipv4/fou.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/fou.c#L190">190</a>         pp = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>);
<a name="L191" href="source/net/ipv4/fou.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/fou.c#L192">192</a> out_unlock:
<a name="L193" href="source/net/ipv4/fou.c#L193">193</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L194" href="source/net/ipv4/fou.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/fou.c#L195">195</a>         return pp;
<a name="L196" href="source/net/ipv4/fou.c#L196">196</a> }
<a name="L197" href="source/net/ipv4/fou.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/fou.c#L198">198</a> static int <a href="ident?i=fou_gro_complete">fou_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nhoff,
<a name="L199" href="source/net/ipv4/fou.c#L199">199</a>                             struct <a href="ident?i=udp_offload">udp_offload</a> *uoff)
<a name="L200" href="source/net/ipv4/fou.c#L200">200</a> {
<a name="L201" href="source/net/ipv4/fou.c#L201">201</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L202" href="source/net/ipv4/fou.c#L202">202</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=proto">proto</a> = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=proto">proto</a>;
<a name="L203" href="source/net/ipv4/fou.c#L203">203</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOSYS">ENOSYS</a>;
<a name="L204" href="source/net/ipv4/fou.c#L204">204</a>         const struct <a href="ident?i=net_offload">net_offload</a> **offloads;
<a name="L205" href="source/net/ipv4/fou.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/fou.c#L206">206</a>         <a href="ident?i=udp_tunnel_gro_complete">udp_tunnel_gro_complete</a>(<a href="ident?i=skb">skb</a>, nhoff);
<a name="L207" href="source/net/ipv4/fou.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/fou.c#L208">208</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L209" href="source/net/ipv4/fou.c#L209">209</a>         offloads = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;is_ipv6 ? <a href="ident?i=inet6_offloads">inet6_offloads</a> : <a href="ident?i=inet_offloads">inet_offloads</a>;
<a name="L210" href="source/net/ipv4/fou.c#L210">210</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(offloads[<a href="ident?i=proto">proto</a>]);
<a name="L211" href="source/net/ipv4/fou.c#L211">211</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete))
<a name="L212" href="source/net/ipv4/fou.c#L212">212</a>                 goto out_unlock;
<a name="L213" href="source/net/ipv4/fou.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/fou.c#L214">214</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete(<a href="ident?i=skb">skb</a>, nhoff);
<a name="L215" href="source/net/ipv4/fou.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/fou.c#L216">216</a> out_unlock:
<a name="L217" href="source/net/ipv4/fou.c#L217">217</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L218" href="source/net/ipv4/fou.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/fou.c#L219">219</a>         return <a href="ident?i=err">err</a>;
<a name="L220" href="source/net/ipv4/fou.c#L220">220</a> }
<a name="L221" href="source/net/ipv4/fou.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/fou.c#L222">222</a> static struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=gue_gro_remcsum">gue_gro_remcsum</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int <a href="ident?i=off">off</a>,
<a name="L223" href="source/net/ipv4/fou.c#L223">223</a>                                       struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a>, void *<a href="ident?i=data">data</a>,
<a name="L224" href="source/net/ipv4/fou.c#L224">224</a>                                       <a href="ident?i=size_t">size_t</a> hdrlen, <a href="ident?i=u8">u8</a> ipproto,
<a name="L225" href="source/net/ipv4/fou.c#L225">225</a>                                       struct <a href="ident?i=gro_remcsum">gro_remcsum</a> *grc, <a href="ident?i=bool">bool</a> nopartial)
<a name="L226" href="source/net/ipv4/fou.c#L226">226</a> {
<a name="L227" href="source/net/ipv4/fou.c#L227">227</a>         <a href="ident?i=__be16">__be16</a> *<a href="ident?i=pd">pd</a> = <a href="ident?i=data">data</a>;
<a name="L228" href="source/net/ipv4/fou.c#L228">228</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=start">start</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=pd">pd</a>[0]);
<a name="L229" href="source/net/ipv4/fou.c#L229">229</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=offset">offset</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=pd">pd</a>[1]);
<a name="L230" href="source/net/ipv4/fou.c#L230">230</a>         <a href="ident?i=size_t">size_t</a> plen = hdrlen + <a href="ident?i=max_t">max_t</a>(<a href="ident?i=size_t">size_t</a>, <a href="ident?i=offset">offset</a> + sizeof(<a href="ident?i=u16">u16</a>), <a href="ident?i=start">start</a>);
<a name="L231" href="source/net/ipv4/fou.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/fou.c#L232">232</a>         if (<a href="ident?i=skb">skb</a>-&gt;remcsum_offload)
<a name="L233" href="source/net/ipv4/fou.c#L233">233</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L234" href="source/net/ipv4/fou.c#L234">234</a> 
<a name="L235" href="source/net/ipv4/fou.c#L235">235</a>         if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;csum_valid)
<a name="L236" href="source/net/ipv4/fou.c#L236">236</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L237" href="source/net/ipv4/fou.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/fou.c#L238">238</a>         <b><i>/* Pull checksum that will be written */</i></b>
<a name="L239" href="source/net/ipv4/fou.c#L239">239</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a> + plen)) {
<a name="L240" href="source/net/ipv4/fou.c#L240">240</a>                 <a href="ident?i=guehdr">guehdr</a> = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a> + plen, <a href="ident?i=off">off</a>);
<a name="L241" href="source/net/ipv4/fou.c#L241">241</a>                 if (!<a href="ident?i=guehdr">guehdr</a>)
<a name="L242" href="source/net/ipv4/fou.c#L242">242</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L243" href="source/net/ipv4/fou.c#L243">243</a>         }
<a name="L244" href="source/net/ipv4/fou.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/fou.c#L245">245</a>         <a href="ident?i=skb_gro_remcsum_process">skb_gro_remcsum_process</a>(<a href="ident?i=skb">skb</a>, (void *)<a href="ident?i=guehdr">guehdr</a> + hdrlen,
<a name="L246" href="source/net/ipv4/fou.c#L246">246</a>                                 <a href="ident?i=start">start</a>, <a href="ident?i=offset">offset</a>, grc, nopartial);
<a name="L247" href="source/net/ipv4/fou.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/fou.c#L248">248</a>         <a href="ident?i=skb">skb</a>-&gt;remcsum_offload = 1;
<a name="L249" href="source/net/ipv4/fou.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/fou.c#L250">250</a>         return <a href="ident?i=guehdr">guehdr</a>;
<a name="L251" href="source/net/ipv4/fou.c#L251">251</a> }
<a name="L252" href="source/net/ipv4/fou.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/fou.c#L253">253</a> static struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=gue_gro_receive">gue_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>,
<a name="L254" href="source/net/ipv4/fou.c#L254">254</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L255" href="source/net/ipv4/fou.c#L255">255</a>                                         struct <a href="ident?i=udp_offload">udp_offload</a> *uoff)
<a name="L256" href="source/net/ipv4/fou.c#L256">256</a> {
<a name="L257" href="source/net/ipv4/fou.c#L257">257</a>         const struct <a href="ident?i=net_offload">net_offload</a> **offloads;
<a name="L258" href="source/net/ipv4/fou.c#L258">258</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L259" href="source/net/ipv4/fou.c#L259">259</a>         struct <a href="ident?i=sk_buff">sk_buff</a> **pp = <a href="ident?i=NULL">NULL</a>;
<a name="L260" href="source/net/ipv4/fou.c#L260">260</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=p">p</a>;
<a name="L261" href="source/net/ipv4/fou.c#L261">261</a>         struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a>;
<a name="L262" href="source/net/ipv4/fou.c#L262">262</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>, hdrlen, <a href="ident?i=off">off</a>;
<a name="L263" href="source/net/ipv4/fou.c#L263">263</a>         void *<a href="ident?i=data">data</a>;
<a name="L264" href="source/net/ipv4/fou.c#L264">264</a>         <a href="ident?i=u16">u16</a> doffset = 0;
<a name="L265" href="source/net/ipv4/fou.c#L265">265</a>         int <a href="ident?i=flush">flush</a> = 1;
<a name="L266" href="source/net/ipv4/fou.c#L266">266</a>         struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a> = <a href="ident?i=container_of">container_of</a>(uoff, struct <a href="ident?i=fou">fou</a>, udp_offloads);
<a name="L267" href="source/net/ipv4/fou.c#L267">267</a>         struct <a href="ident?i=gro_remcsum">gro_remcsum</a> grc;
<a name="L268" href="source/net/ipv4/fou.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/fou.c#L269">269</a>         <a href="ident?i=skb_gro_remcsum_init">skb_gro_remcsum_init</a>(&amp;grc);
<a name="L270" href="source/net/ipv4/fou.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/fou.c#L271">271</a>         <a href="ident?i=off">off</a> = <a href="ident?i=skb_gro_offset">skb_gro_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L272" href="source/net/ipv4/fou.c#L272">272</a>         <a href="ident?i=len">len</a> = <a href="ident?i=off">off</a> + sizeof(*<a href="ident?i=guehdr">guehdr</a>);
<a name="L273" href="source/net/ipv4/fou.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/fou.c#L274">274</a>         <a href="ident?i=guehdr">guehdr</a> = <a href="ident?i=skb_gro_header_fast">skb_gro_header_fast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a>);
<a name="L275" href="source/net/ipv4/fou.c#L275">275</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>)) {
<a name="L276" href="source/net/ipv4/fou.c#L276">276</a>                 <a href="ident?i=guehdr">guehdr</a> = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>, <a href="ident?i=off">off</a>);
<a name="L277" href="source/net/ipv4/fou.c#L277">277</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=guehdr">guehdr</a>))
<a name="L278" href="source/net/ipv4/fou.c#L278">278</a>                         goto <a href="ident?i=out">out</a>;
<a name="L279" href="source/net/ipv4/fou.c#L279">279</a>         }
<a name="L280" href="source/net/ipv4/fou.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/fou.c#L281">281</a>         <a href="ident?i=optlen">optlen</a> = <a href="ident?i=guehdr">guehdr</a>-&gt;hlen &lt;&lt; 2;
<a name="L282" href="source/net/ipv4/fou.c#L282">282</a>         <a href="ident?i=len">len</a> += <a href="ident?i=optlen">optlen</a>;
<a name="L283" href="source/net/ipv4/fou.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/fou.c#L284">284</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>)) {
<a name="L285" href="source/net/ipv4/fou.c#L285">285</a>                 <a href="ident?i=guehdr">guehdr</a> = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>, <a href="ident?i=off">off</a>);
<a name="L286" href="source/net/ipv4/fou.c#L286">286</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=guehdr">guehdr</a>))
<a name="L287" href="source/net/ipv4/fou.c#L287">287</a>                         goto <a href="ident?i=out">out</a>;
<a name="L288" href="source/net/ipv4/fou.c#L288">288</a>         }
<a name="L289" href="source/net/ipv4/fou.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/fou.c#L290">290</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=guehdr">guehdr</a>-&gt;control) || <a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=version">version</a> != 0 ||
<a name="L291" href="source/net/ipv4/fou.c#L291">291</a>             <a href="ident?i=validate_gue_flags">validate_gue_flags</a>(<a href="ident?i=guehdr">guehdr</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L292" href="source/net/ipv4/fou.c#L292">292</a>                 goto <a href="ident?i=out">out</a>;
<a name="L293" href="source/net/ipv4/fou.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/fou.c#L294">294</a>         hdrlen = sizeof(*<a href="ident?i=guehdr">guehdr</a>) + <a href="ident?i=optlen">optlen</a>;
<a name="L295" href="source/net/ipv4/fou.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/fou.c#L296">296</a>         <b><i>/* Adjust NAPI_GRO_CB(skb)-&gt;csum to account for guehdr,</i></b>
<a name="L297" href="source/net/ipv4/fou.c#L297">297</a> <b><i>         * this is needed if there is a remote checkcsum offload.</i></b>
<a name="L298" href="source/net/ipv4/fou.c#L298">298</a> <b><i>         */</i></b>
<a name="L299" href="source/net/ipv4/fou.c#L299">299</a>         <a href="ident?i=skb_gro_postpull_rcsum">skb_gro_postpull_rcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=guehdr">guehdr</a>, hdrlen);
<a name="L300" href="source/net/ipv4/fou.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/fou.c#L301">301</a>         <a href="ident?i=data">data</a> = &amp;<a href="ident?i=guehdr">guehdr</a>[1];
<a name="L302" href="source/net/ipv4/fou.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/fou.c#L303">303</a>         if (<a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GUE_FLAG_PRIV">GUE_FLAG_PRIV</a>) {
<a name="L304" href="source/net/ipv4/fou.c#L304">304</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=flags">flags</a> = *(<a href="ident?i=__be32">__be32</a> *)(<a href="ident?i=data">data</a> + doffset);
<a name="L305" href="source/net/ipv4/fou.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/fou.c#L306">306</a>                 doffset += <a href="ident?i=GUE_LEN_PRIV">GUE_LEN_PRIV</a>;
<a name="L307" href="source/net/ipv4/fou.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/fou.c#L308">308</a>                 if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GUE_PFLAG_REMCSUM">GUE_PFLAG_REMCSUM</a>) {
<a name="L309" href="source/net/ipv4/fou.c#L309">309</a>                         <a href="ident?i=guehdr">guehdr</a> = <a href="ident?i=gue_gro_remcsum">gue_gro_remcsum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a>, <a href="ident?i=guehdr">guehdr</a>,
<a name="L310" href="source/net/ipv4/fou.c#L310">310</a>                                                  <a href="ident?i=data">data</a> + doffset, hdrlen,
<a name="L311" href="source/net/ipv4/fou.c#L311">311</a>                                                  <a href="ident?i=guehdr">guehdr</a>-&gt;proto_ctype, &amp;grc,
<a name="L312" href="source/net/ipv4/fou.c#L312">312</a>                                                  !!(<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=flags">flags</a> &amp;
<a name="L313" href="source/net/ipv4/fou.c#L313">313</a>                                                     <a href="ident?i=FOU_F_REMCSUM_NOPARTIAL">FOU_F_REMCSUM_NOPARTIAL</a>));
<a name="L314" href="source/net/ipv4/fou.c#L314">314</a>                         if (!<a href="ident?i=guehdr">guehdr</a>)
<a name="L315" href="source/net/ipv4/fou.c#L315">315</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L316" href="source/net/ipv4/fou.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/fou.c#L317">317</a>                         <a href="ident?i=data">data</a> = &amp;<a href="ident?i=guehdr">guehdr</a>[1];
<a name="L318" href="source/net/ipv4/fou.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/fou.c#L319">319</a>                         doffset += <a href="ident?i=GUE_PLEN_REMCSUM">GUE_PLEN_REMCSUM</a>;
<a name="L320" href="source/net/ipv4/fou.c#L320">320</a>                 }
<a name="L321" href="source/net/ipv4/fou.c#L321">321</a>         }
<a name="L322" href="source/net/ipv4/fou.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/fou.c#L323">323</a>         <a href="ident?i=skb_gro_pull">skb_gro_pull</a>(<a href="ident?i=skb">skb</a>, hdrlen);
<a name="L324" href="source/net/ipv4/fou.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/fou.c#L325">325</a>         <a href="ident?i=flush">flush</a> = 0;
<a name="L326" href="source/net/ipv4/fou.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/fou.c#L327">327</a>         for (<a href="ident?i=p">p</a> = *<a href="ident?i=head">head</a>; <a href="ident?i=p">p</a>; <a href="ident?i=p">p</a> = <a href="ident?i=p">p</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L328" href="source/net/ipv4/fou.c#L328">328</a>                 const struct <a href="ident?i=guehdr">guehdr</a> *guehdr2;
<a name="L329" href="source/net/ipv4/fou.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/fou.c#L330">330</a>                 if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow)
<a name="L331" href="source/net/ipv4/fou.c#L331">331</a>                         continue;
<a name="L332" href="source/net/ipv4/fou.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/fou.c#L333">333</a>                 guehdr2 = (struct <a href="ident?i=guehdr">guehdr</a> *)(<a href="ident?i=p">p</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=off">off</a>);
<a name="L334" href="source/net/ipv4/fou.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/fou.c#L335">335</a>                 <b><i>/* Compare base GUE header to be equal (covers</i></b>
<a name="L336" href="source/net/ipv4/fou.c#L336">336</a> <b><i>                 * hlen, version, proto_ctype, and flags.</i></b>
<a name="L337" href="source/net/ipv4/fou.c#L337">337</a> <b><i>                 */</i></b>
<a name="L338" href="source/net/ipv4/fou.c#L338">338</a>                 if (<a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=word">word</a> != guehdr2-&gt;<a href="ident?i=word">word</a>) {
<a name="L339" href="source/net/ipv4/fou.c#L339">339</a>                         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow = 0;
<a name="L340" href="source/net/ipv4/fou.c#L340">340</a>                         continue;
<a name="L341" href="source/net/ipv4/fou.c#L341">341</a>                 }
<a name="L342" href="source/net/ipv4/fou.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/fou.c#L343">343</a>                 <b><i>/* Compare optional fields are the same. */</i></b>
<a name="L344" href="source/net/ipv4/fou.c#L344">344</a>                 if (<a href="ident?i=guehdr">guehdr</a>-&gt;hlen &amp;&amp; <a href="ident?i=memcmp">memcmp</a>(&amp;<a href="ident?i=guehdr">guehdr</a>[1], &amp;guehdr2[1],
<a name="L345" href="source/net/ipv4/fou.c#L345">345</a>                                            <a href="ident?i=guehdr">guehdr</a>-&gt;hlen &lt;&lt; 2)) {
<a name="L346" href="source/net/ipv4/fou.c#L346">346</a>                         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow = 0;
<a name="L347" href="source/net/ipv4/fou.c#L347">347</a>                         continue;
<a name="L348" href="source/net/ipv4/fou.c#L348">348</a>                 }
<a name="L349" href="source/net/ipv4/fou.c#L349">349</a>         }
<a name="L350" href="source/net/ipv4/fou.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/fou.c#L351">351</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L352" href="source/net/ipv4/fou.c#L352">352</a>         offloads = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;is_ipv6 ? <a href="ident?i=inet6_offloads">inet6_offloads</a> : <a href="ident?i=inet_offloads">inet_offloads</a>;
<a name="L353" href="source/net/ipv4/fou.c#L353">353</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(offloads[<a href="ident?i=guehdr">guehdr</a>-&gt;proto_ctype]);
<a name="L354" href="source/net/ipv4/fou.c#L354">354</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive))
<a name="L355" href="source/net/ipv4/fou.c#L355">355</a>                 goto out_unlock;
<a name="L356" href="source/net/ipv4/fou.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/fou.c#L357">357</a>         pp = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>);
<a name="L358" href="source/net/ipv4/fou.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/fou.c#L359">359</a> out_unlock:
<a name="L360" href="source/net/ipv4/fou.c#L360">360</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L361" href="source/net/ipv4/fou.c#L361">361</a> <a href="ident?i=out">out</a>:
<a name="L362" href="source/net/ipv4/fou.c#L362">362</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> |= <a href="ident?i=flush">flush</a>;
<a name="L363" href="source/net/ipv4/fou.c#L363">363</a>         <a href="ident?i=skb_gro_remcsum_cleanup">skb_gro_remcsum_cleanup</a>(<a href="ident?i=skb">skb</a>, &amp;grc);
<a name="L364" href="source/net/ipv4/fou.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/fou.c#L365">365</a>         return pp;
<a name="L366" href="source/net/ipv4/fou.c#L366">366</a> }
<a name="L367" href="source/net/ipv4/fou.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/fou.c#L368">368</a> static int <a href="ident?i=gue_gro_complete">gue_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nhoff,
<a name="L369" href="source/net/ipv4/fou.c#L369">369</a>                             struct <a href="ident?i=udp_offload">udp_offload</a> *uoff)
<a name="L370" href="source/net/ipv4/fou.c#L370">370</a> {
<a name="L371" href="source/net/ipv4/fou.c#L371">371</a>         const struct <a href="ident?i=net_offload">net_offload</a> **offloads;
<a name="L372" href="source/net/ipv4/fou.c#L372">372</a>         struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a> = (struct <a href="ident?i=guehdr">guehdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + nhoff);
<a name="L373" href="source/net/ipv4/fou.c#L373">373</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L374" href="source/net/ipv4/fou.c#L374">374</a>         unsigned int guehlen;
<a name="L375" href="source/net/ipv4/fou.c#L375">375</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=proto">proto</a>;
<a name="L376" href="source/net/ipv4/fou.c#L376">376</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L377" href="source/net/ipv4/fou.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/fou.c#L378">378</a>         <a href="ident?i=proto">proto</a> = <a href="ident?i=guehdr">guehdr</a>-&gt;proto_ctype;
<a name="L379" href="source/net/ipv4/fou.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/fou.c#L380">380</a>         guehlen = sizeof(*<a href="ident?i=guehdr">guehdr</a>) + (<a href="ident?i=guehdr">guehdr</a>-&gt;hlen &lt;&lt; 2);
<a name="L381" href="source/net/ipv4/fou.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/fou.c#L382">382</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L383" href="source/net/ipv4/fou.c#L383">383</a>         offloads = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;is_ipv6 ? <a href="ident?i=inet6_offloads">inet6_offloads</a> : <a href="ident?i=inet_offloads">inet_offloads</a>;
<a name="L384" href="source/net/ipv4/fou.c#L384">384</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(offloads[<a href="ident?i=proto">proto</a>]);
<a name="L385" href="source/net/ipv4/fou.c#L385">385</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete))
<a name="L386" href="source/net/ipv4/fou.c#L386">386</a>                 goto out_unlock;
<a name="L387" href="source/net/ipv4/fou.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/fou.c#L388">388</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete(<a href="ident?i=skb">skb</a>, nhoff + guehlen);
<a name="L389" href="source/net/ipv4/fou.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/fou.c#L390">390</a> out_unlock:
<a name="L391" href="source/net/ipv4/fou.c#L391">391</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L392" href="source/net/ipv4/fou.c#L392">392</a>         return <a href="ident?i=err">err</a>;
<a name="L393" href="source/net/ipv4/fou.c#L393">393</a> }
<a name="L394" href="source/net/ipv4/fou.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/fou.c#L395">395</a> static int <a href="ident?i=fou_add_to_port_list">fou_add_to_port_list</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>)
<a name="L396" href="source/net/ipv4/fou.c#L396">396</a> {
<a name="L397" href="source/net/ipv4/fou.c#L397">397</a>         struct <a href="ident?i=fou_net">fou_net</a> *fn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou_net_id">fou_net_id</a>);
<a name="L398" href="source/net/ipv4/fou.c#L398">398</a>         struct <a href="ident?i=fou">fou</a> *fout;
<a name="L399" href="source/net/ipv4/fou.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/fou.c#L400">400</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;fn-&gt;fou_lock);
<a name="L401" href="source/net/ipv4/fou.c#L401">401</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(fout, &amp;fn-&gt;fou_list, <a href="ident?i=list">list</a>) {
<a name="L402" href="source/net/ipv4/fou.c#L402">402</a>                 if (<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=port">port</a> == fout-&gt;<a href="ident?i=port">port</a>) {
<a name="L403" href="source/net/ipv4/fou.c#L403">403</a>                         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;fn-&gt;fou_lock);
<a name="L404" href="source/net/ipv4/fou.c#L404">404</a>                         return -<a href="ident?i=EALREADY">EALREADY</a>;
<a name="L405" href="source/net/ipv4/fou.c#L405">405</a>                 }
<a name="L406" href="source/net/ipv4/fou.c#L406">406</a>         }
<a name="L407" href="source/net/ipv4/fou.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/fou.c#L408">408</a>         <a href="ident?i=list_add">list_add</a>(&amp;<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=list">list</a>, &amp;fn-&gt;fou_list);
<a name="L409" href="source/net/ipv4/fou.c#L409">409</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;fn-&gt;fou_lock);
<a name="L410" href="source/net/ipv4/fou.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/fou.c#L411">411</a>         return 0;
<a name="L412" href="source/net/ipv4/fou.c#L412">412</a> }
<a name="L413" href="source/net/ipv4/fou.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/fou.c#L414">414</a> static void <a href="ident?i=fou_release">fou_release</a>(struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>)
<a name="L415" href="source/net/ipv4/fou.c#L415">415</a> {
<a name="L416" href="source/net/ipv4/fou.c#L416">416</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a> = <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=sock">sock</a>;
<a name="L417" href="source/net/ipv4/fou.c#L417">417</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L418" href="source/net/ipv4/fou.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/fou.c#L419">419</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L420" href="source/net/ipv4/fou.c#L420">420</a>                 <a href="ident?i=udp_del_offload">udp_del_offload</a>(&amp;<a href="ident?i=fou">fou</a>-&gt;udp_offloads);
<a name="L421" href="source/net/ipv4/fou.c#L421">421</a>         <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L422" href="source/net/ipv4/fou.c#L422">422</a>         <a href="ident?i=udp_tunnel_sock_release">udp_tunnel_sock_release</a>(<a href="ident?i=sock">sock</a>);
<a name="L423" href="source/net/ipv4/fou.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/fou.c#L424">424</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=fou">fou</a>);
<a name="L425" href="source/net/ipv4/fou.c#L425">425</a> }
<a name="L426" href="source/net/ipv4/fou.c#L426">426</a> 
<a name="L427" href="source/net/ipv4/fou.c#L427">427</a> static int <a href="ident?i=fou_encap_init">fou_encap_init</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>, struct <a href="ident?i=fou_cfg">fou_cfg</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L428" href="source/net/ipv4/fou.c#L428">428</a> {
<a name="L429" href="source/net/ipv4/fou.c#L429">429</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;encap_rcv = <a href="ident?i=fou_udp_recv">fou_udp_recv</a>;
<a name="L430" href="source/net/ipv4/fou.c#L430">430</a>         <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L431" href="source/net/ipv4/fou.c#L431">431</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.<a href="ident?i=callbacks">callbacks</a>.gro_receive = <a href="ident?i=fou_gro_receive">fou_gro_receive</a>;
<a name="L432" href="source/net/ipv4/fou.c#L432">432</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.<a href="ident?i=callbacks">callbacks</a>.gro_complete = <a href="ident?i=fou_gro_complete">fou_gro_complete</a>;
<a name="L433" href="source/net/ipv4/fou.c#L433">433</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.<a href="ident?i=port">port</a> = <a href="ident?i=cfg">cfg</a>-&gt;udp_config.local_udp_port;
<a name="L434" href="source/net/ipv4/fou.c#L434">434</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.ipproto = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L435" href="source/net/ipv4/fou.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/fou.c#L436">436</a>         return 0;
<a name="L437" href="source/net/ipv4/fou.c#L437">437</a> }
<a name="L438" href="source/net/ipv4/fou.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/fou.c#L439">439</a> static int <a href="ident?i=gue_encap_init">gue_encap_init</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>, struct <a href="ident?i=fou_cfg">fou_cfg</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L440" href="source/net/ipv4/fou.c#L440">440</a> {
<a name="L441" href="source/net/ipv4/fou.c#L441">441</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;encap_rcv = <a href="ident?i=gue_udp_recv">gue_udp_recv</a>;
<a name="L442" href="source/net/ipv4/fou.c#L442">442</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.<a href="ident?i=callbacks">callbacks</a>.gro_receive = <a href="ident?i=gue_gro_receive">gue_gro_receive</a>;
<a name="L443" href="source/net/ipv4/fou.c#L443">443</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.<a href="ident?i=callbacks">callbacks</a>.gro_complete = <a href="ident?i=gue_gro_complete">gue_gro_complete</a>;
<a name="L444" href="source/net/ipv4/fou.c#L444">444</a>         <a href="ident?i=fou">fou</a>-&gt;udp_offloads.<a href="ident?i=port">port</a> = <a href="ident?i=cfg">cfg</a>-&gt;udp_config.local_udp_port;
<a name="L445" href="source/net/ipv4/fou.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/fou.c#L446">446</a>         return 0;
<a name="L447" href="source/net/ipv4/fou.c#L447">447</a> }
<a name="L448" href="source/net/ipv4/fou.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/fou.c#L449">449</a> static int <a href="ident?i=fou_create">fou_create</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=fou_cfg">fou_cfg</a> *<a href="ident?i=cfg">cfg</a>,
<a name="L450" href="source/net/ipv4/fou.c#L450">450</a>                       struct <a href="ident?i=socket">socket</a> **sockp)
<a name="L451" href="source/net/ipv4/fou.c#L451">451</a> {
<a name="L452" href="source/net/ipv4/fou.c#L452">452</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L453" href="source/net/ipv4/fou.c#L453">453</a>         struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L454" href="source/net/ipv4/fou.c#L454">454</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L455" href="source/net/ipv4/fou.c#L455">455</a>         int <a href="ident?i=err">err</a>;
<a name="L456" href="source/net/ipv4/fou.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/fou.c#L457">457</a>         <b><i>/* Open UDP socket */</i></b>
<a name="L458" href="source/net/ipv4/fou.c#L458">458</a>         <a href="ident?i=err">err</a> = <a href="ident?i=udp_sock_create">udp_sock_create</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=cfg">cfg</a>-&gt;udp_config, &amp;<a href="ident?i=sock">sock</a>);
<a name="L459" href="source/net/ipv4/fou.c#L459">459</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L460" href="source/net/ipv4/fou.c#L460">460</a>                 goto <a href="ident?i=error">error</a>;
<a name="L461" href="source/net/ipv4/fou.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/fou.c#L462">462</a>         <b><i>/* Allocate FOU port structure */</i></b>
<a name="L463" href="source/net/ipv4/fou.c#L463">463</a>         <a href="ident?i=fou">fou</a> = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*<a href="ident?i=fou">fou</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L464" href="source/net/ipv4/fou.c#L464">464</a>         if (!<a href="ident?i=fou">fou</a>) {
<a name="L465" href="source/net/ipv4/fou.c#L465">465</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L466" href="source/net/ipv4/fou.c#L466">466</a>                 goto <a href="ident?i=error">error</a>;
<a name="L467" href="source/net/ipv4/fou.c#L467">467</a>         }
<a name="L468" href="source/net/ipv4/fou.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/fou.c#L469">469</a>         sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L470" href="source/net/ipv4/fou.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/fou.c#L471">471</a>         <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=flags">flags</a>;
<a name="L472" href="source/net/ipv4/fou.c#L472">472</a>         <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=port">port</a> = <a href="ident?i=cfg">cfg</a>-&gt;udp_config.local_udp_port;
<a name="L473" href="source/net/ipv4/fou.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/fou.c#L474">474</a>         <b><i>/* Initial for fou type */</i></b>
<a name="L475" href="source/net/ipv4/fou.c#L475">475</a>         switch (<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L476" href="source/net/ipv4/fou.c#L476">476</a>         case FOU_ENCAP_DIRECT:
<a name="L477" href="source/net/ipv4/fou.c#L477">477</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fou_encap_init">fou_encap_init</a>(sk, <a href="ident?i=fou">fou</a>, <a href="ident?i=cfg">cfg</a>);
<a name="L478" href="source/net/ipv4/fou.c#L478">478</a>                 if (<a href="ident?i=err">err</a>)
<a name="L479" href="source/net/ipv4/fou.c#L479">479</a>                         goto <a href="ident?i=error">error</a>;
<a name="L480" href="source/net/ipv4/fou.c#L480">480</a>                 break;
<a name="L481" href="source/net/ipv4/fou.c#L481">481</a>         case FOU_ENCAP_GUE:
<a name="L482" href="source/net/ipv4/fou.c#L482">482</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=gue_encap_init">gue_encap_init</a>(sk, <a href="ident?i=fou">fou</a>, <a href="ident?i=cfg">cfg</a>);
<a name="L483" href="source/net/ipv4/fou.c#L483">483</a>                 if (<a href="ident?i=err">err</a>)
<a name="L484" href="source/net/ipv4/fou.c#L484">484</a>                         goto <a href="ident?i=error">error</a>;
<a name="L485" href="source/net/ipv4/fou.c#L485">485</a>                 break;
<a name="L486" href="source/net/ipv4/fou.c#L486">486</a>         default:
<a name="L487" href="source/net/ipv4/fou.c#L487">487</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L488" href="source/net/ipv4/fou.c#L488">488</a>                 goto <a href="ident?i=error">error</a>;
<a name="L489" href="source/net/ipv4/fou.c#L489">489</a>         }
<a name="L490" href="source/net/ipv4/fou.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/fou.c#L491">491</a>         <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L492" href="source/net/ipv4/fou.c#L492">492</a> 
<a name="L493" href="source/net/ipv4/fou.c#L493">493</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;encap_type = 1;
<a name="L494" href="source/net/ipv4/fou.c#L494">494</a>         <a href="ident?i=udp_encap_enable">udp_encap_enable</a>();
<a name="L495" href="source/net/ipv4/fou.c#L495">495</a> 
<a name="L496" href="source/net/ipv4/fou.c#L496">496</a>         sk-&gt;sk_user_data = <a href="ident?i=fou">fou</a>;
<a name="L497" href="source/net/ipv4/fou.c#L497">497</a>         <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=sock">sock</a> = <a href="ident?i=sock">sock</a>;
<a name="L498" href="source/net/ipv4/fou.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/fou.c#L499">499</a>         <a href="ident?i=inet_inc_convert_csum">inet_inc_convert_csum</a>(sk);
<a name="L500" href="source/net/ipv4/fou.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/fou.c#L501">501</a>         sk-&gt;sk_allocation = <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>;
<a name="L502" href="source/net/ipv4/fou.c#L502">502</a> 
<a name="L503" href="source/net/ipv4/fou.c#L503">503</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;udp_config.<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L504" href="source/net/ipv4/fou.c#L504">504</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=udp_add_offload">udp_add_offload</a>(&amp;<a href="ident?i=fou">fou</a>-&gt;udp_offloads);
<a name="L505" href="source/net/ipv4/fou.c#L505">505</a>                 if (<a href="ident?i=err">err</a>)
<a name="L506" href="source/net/ipv4/fou.c#L506">506</a>                         goto <a href="ident?i=error">error</a>;
<a name="L507" href="source/net/ipv4/fou.c#L507">507</a>         }
<a name="L508" href="source/net/ipv4/fou.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/fou.c#L509">509</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fou_add_to_port_list">fou_add_to_port_list</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou">fou</a>);
<a name="L510" href="source/net/ipv4/fou.c#L510">510</a>         if (<a href="ident?i=err">err</a>)
<a name="L511" href="source/net/ipv4/fou.c#L511">511</a>                 goto <a href="ident?i=error">error</a>;
<a name="L512" href="source/net/ipv4/fou.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/fou.c#L513">513</a>         if (sockp)
<a name="L514" href="source/net/ipv4/fou.c#L514">514</a>                 *sockp = <a href="ident?i=sock">sock</a>;
<a name="L515" href="source/net/ipv4/fou.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/fou.c#L516">516</a>         return 0;
<a name="L517" href="source/net/ipv4/fou.c#L517">517</a> 
<a name="L518" href="source/net/ipv4/fou.c#L518">518</a> <a href="ident?i=error">error</a>:
<a name="L519" href="source/net/ipv4/fou.c#L519">519</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=fou">fou</a>);
<a name="L520" href="source/net/ipv4/fou.c#L520">520</a>         if (<a href="ident?i=sock">sock</a>)
<a name="L521" href="source/net/ipv4/fou.c#L521">521</a>                 <a href="ident?i=udp_tunnel_sock_release">udp_tunnel_sock_release</a>(<a href="ident?i=sock">sock</a>);
<a name="L522" href="source/net/ipv4/fou.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/fou.c#L523">523</a>         return <a href="ident?i=err">err</a>;
<a name="L524" href="source/net/ipv4/fou.c#L524">524</a> }
<a name="L525" href="source/net/ipv4/fou.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/fou.c#L526">526</a> static int <a href="ident?i=fou_destroy">fou_destroy</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=fou_cfg">fou_cfg</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L527" href="source/net/ipv4/fou.c#L527">527</a> {
<a name="L528" href="source/net/ipv4/fou.c#L528">528</a>         struct <a href="ident?i=fou_net">fou_net</a> *fn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou_net_id">fou_net_id</a>);
<a name="L529" href="source/net/ipv4/fou.c#L529">529</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a> = <a href="ident?i=cfg">cfg</a>-&gt;udp_config.local_udp_port;
<a name="L530" href="source/net/ipv4/fou.c#L530">530</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L531" href="source/net/ipv4/fou.c#L531">531</a>         struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>;
<a name="L532" href="source/net/ipv4/fou.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/fou.c#L533">533</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;fn-&gt;fou_lock);
<a name="L534" href="source/net/ipv4/fou.c#L534">534</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(<a href="ident?i=fou">fou</a>, &amp;fn-&gt;fou_list, <a href="ident?i=list">list</a>) {
<a name="L535" href="source/net/ipv4/fou.c#L535">535</a>                 if (<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=port">port</a> == <a href="ident?i=port">port</a>) {
<a name="L536" href="source/net/ipv4/fou.c#L536">536</a>                         <a href="ident?i=fou_release">fou_release</a>(<a href="ident?i=fou">fou</a>);
<a name="L537" href="source/net/ipv4/fou.c#L537">537</a>                         <a href="ident?i=err">err</a> = 0;
<a name="L538" href="source/net/ipv4/fou.c#L538">538</a>                         break;
<a name="L539" href="source/net/ipv4/fou.c#L539">539</a>                 }
<a name="L540" href="source/net/ipv4/fou.c#L540">540</a>         }
<a name="L541" href="source/net/ipv4/fou.c#L541">541</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;fn-&gt;fou_lock);
<a name="L542" href="source/net/ipv4/fou.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/fou.c#L543">543</a>         return <a href="ident?i=err">err</a>;
<a name="L544" href="source/net/ipv4/fou.c#L544">544</a> }
<a name="L545" href="source/net/ipv4/fou.c#L545">545</a> 
<a name="L546" href="source/net/ipv4/fou.c#L546">546</a> static struct <a href="ident?i=genl_family">genl_family</a> <a href="ident?i=fou_nl_family">fou_nl_family</a> = {
<a name="L547" href="source/net/ipv4/fou.c#L547">547</a>         .<a href="ident?i=id">id</a>             = <a href="ident?i=GENL_ID_GENERATE">GENL_ID_GENERATE</a>,
<a name="L548" href="source/net/ipv4/fou.c#L548">548</a>         .hdrsize        = 0,
<a name="L549" href="source/net/ipv4/fou.c#L549">549</a>         .<a href="ident?i=name">name</a>           = <a href="ident?i=FOU_GENL_NAME">FOU_GENL_NAME</a>,
<a name="L550" href="source/net/ipv4/fou.c#L550">550</a>         .<a href="ident?i=version">version</a>        = <a href="ident?i=FOU_GENL_VERSION">FOU_GENL_VERSION</a>,
<a name="L551" href="source/net/ipv4/fou.c#L551">551</a>         .maxattr        = <a href="ident?i=FOU_ATTR_MAX">FOU_ATTR_MAX</a>,
<a name="L552" href="source/net/ipv4/fou.c#L552">552</a>         .netnsok        = <a href="ident?i=true">true</a>,
<a name="L553" href="source/net/ipv4/fou.c#L553">553</a> };
<a name="L554" href="source/net/ipv4/fou.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/fou.c#L555">555</a> static struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=fou_nl_policy">fou_nl_policy</a>[<a href="ident?i=FOU_ATTR_MAX">FOU_ATTR_MAX</a> + 1] = {
<a name="L556" href="source/net/ipv4/fou.c#L556">556</a>         [FOU_ATTR_PORT] = { .<a href="ident?i=type">type</a> = NLA_U16, },
<a name="L557" href="source/net/ipv4/fou.c#L557">557</a>         [FOU_ATTR_AF] = { .<a href="ident?i=type">type</a> = NLA_U8, },
<a name="L558" href="source/net/ipv4/fou.c#L558">558</a>         [FOU_ATTR_IPPROTO] = { .<a href="ident?i=type">type</a> = NLA_U8, },
<a name="L559" href="source/net/ipv4/fou.c#L559">559</a>         [FOU_ATTR_TYPE] = { .<a href="ident?i=type">type</a> = NLA_U8, },
<a name="L560" href="source/net/ipv4/fou.c#L560">560</a>         [FOU_ATTR_REMCSUM_NOPARTIAL] = { .<a href="ident?i=type">type</a> = NLA_FLAG, },
<a name="L561" href="source/net/ipv4/fou.c#L561">561</a> };
<a name="L562" href="source/net/ipv4/fou.c#L562">562</a> 
<a name="L563" href="source/net/ipv4/fou.c#L563">563</a> static int <a href="ident?i=parse_nl_config">parse_nl_config</a>(struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>,
<a name="L564" href="source/net/ipv4/fou.c#L564">564</a>                            struct <a href="ident?i=fou_cfg">fou_cfg</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L565" href="source/net/ipv4/fou.c#L565">565</a> {
<a name="L566" href="source/net/ipv4/fou.c#L566">566</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=cfg">cfg</a>, 0, sizeof(*<a href="ident?i=cfg">cfg</a>));
<a name="L567" href="source/net/ipv4/fou.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/fou.c#L568">568</a>         <a href="ident?i=cfg">cfg</a>-&gt;udp_config.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L569" href="source/net/ipv4/fou.c#L569">569</a> 
<a name="L570" href="source/net/ipv4/fou.c#L570">570</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_AF]) {
<a name="L571" href="source/net/ipv4/fou.c#L571">571</a>                 <a href="ident?i=u8">u8</a> <a href="ident?i=family">family</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_AF]);
<a name="L572" href="source/net/ipv4/fou.c#L572">572</a> 
<a name="L573" href="source/net/ipv4/fou.c#L573">573</a>                 if (<a href="ident?i=family">family</a> != <a href="ident?i=AF_INET">AF_INET</a> &amp;&amp; <a href="ident?i=family">family</a> != <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L574" href="source/net/ipv4/fou.c#L574">574</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L575" href="source/net/ipv4/fou.c#L575">575</a> 
<a name="L576" href="source/net/ipv4/fou.c#L576">576</a>                 <a href="ident?i=cfg">cfg</a>-&gt;udp_config.<a href="ident?i=family">family</a> = <a href="ident?i=family">family</a>;
<a name="L577" href="source/net/ipv4/fou.c#L577">577</a>         }
<a name="L578" href="source/net/ipv4/fou.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/fou.c#L579">579</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_PORT]) {
<a name="L580" href="source/net/ipv4/fou.c#L580">580</a>                 <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a> = <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_PORT]);
<a name="L581" href="source/net/ipv4/fou.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/fou.c#L582">582</a>                 <a href="ident?i=cfg">cfg</a>-&gt;udp_config.local_udp_port = <a href="ident?i=port">port</a>;
<a name="L583" href="source/net/ipv4/fou.c#L583">583</a>         }
<a name="L584" href="source/net/ipv4/fou.c#L584">584</a> 
<a name="L585" href="source/net/ipv4/fou.c#L585">585</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_IPPROTO])
<a name="L586" href="source/net/ipv4/fou.c#L586">586</a>                 <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_IPPROTO]);
<a name="L587" href="source/net/ipv4/fou.c#L587">587</a> 
<a name="L588" href="source/net/ipv4/fou.c#L588">588</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_TYPE])
<a name="L589" href="source/net/ipv4/fou.c#L589">589</a>                 <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_TYPE]);
<a name="L590" href="source/net/ipv4/fou.c#L590">590</a> 
<a name="L591" href="source/net/ipv4/fou.c#L591">591</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=attrs">attrs</a>[FOU_ATTR_REMCSUM_NOPARTIAL])
<a name="L592" href="source/net/ipv4/fou.c#L592">592</a>                 <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=FOU_F_REMCSUM_NOPARTIAL">FOU_F_REMCSUM_NOPARTIAL</a>;
<a name="L593" href="source/net/ipv4/fou.c#L593">593</a> 
<a name="L594" href="source/net/ipv4/fou.c#L594">594</a>         return 0;
<a name="L595" href="source/net/ipv4/fou.c#L595">595</a> }
<a name="L596" href="source/net/ipv4/fou.c#L596">596</a> 
<a name="L597" href="source/net/ipv4/fou.c#L597">597</a> static int <a href="ident?i=fou_nl_cmd_add_port">fou_nl_cmd_add_port</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>)
<a name="L598" href="source/net/ipv4/fou.c#L598">598</a> {
<a name="L599" href="source/net/ipv4/fou.c#L599">599</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=genl_info_net">genl_info_net</a>(<a href="ident?i=info">info</a>);
<a name="L600" href="source/net/ipv4/fou.c#L600">600</a>         struct <a href="ident?i=fou_cfg">fou_cfg</a> <a href="ident?i=cfg">cfg</a>;
<a name="L601" href="source/net/ipv4/fou.c#L601">601</a>         int <a href="ident?i=err">err</a>;
<a name="L602" href="source/net/ipv4/fou.c#L602">602</a> 
<a name="L603" href="source/net/ipv4/fou.c#L603">603</a>         <a href="ident?i=err">err</a> = <a href="ident?i=parse_nl_config">parse_nl_config</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L604" href="source/net/ipv4/fou.c#L604">604</a>         if (<a href="ident?i=err">err</a>)
<a name="L605" href="source/net/ipv4/fou.c#L605">605</a>                 return <a href="ident?i=err">err</a>;
<a name="L606" href="source/net/ipv4/fou.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/fou.c#L607">607</a>         return <a href="ident?i=fou_create">fou_create</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=cfg">cfg</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L608" href="source/net/ipv4/fou.c#L608">608</a> }
<a name="L609" href="source/net/ipv4/fou.c#L609">609</a> 
<a name="L610" href="source/net/ipv4/fou.c#L610">610</a> static int <a href="ident?i=fou_nl_cmd_rm_port">fou_nl_cmd_rm_port</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>)
<a name="L611" href="source/net/ipv4/fou.c#L611">611</a> {
<a name="L612" href="source/net/ipv4/fou.c#L612">612</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=genl_info_net">genl_info_net</a>(<a href="ident?i=info">info</a>);
<a name="L613" href="source/net/ipv4/fou.c#L613">613</a>         struct <a href="ident?i=fou_cfg">fou_cfg</a> <a href="ident?i=cfg">cfg</a>;
<a name="L614" href="source/net/ipv4/fou.c#L614">614</a>         int <a href="ident?i=err">err</a>;
<a name="L615" href="source/net/ipv4/fou.c#L615">615</a> 
<a name="L616" href="source/net/ipv4/fou.c#L616">616</a>         <a href="ident?i=err">err</a> = <a href="ident?i=parse_nl_config">parse_nl_config</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L617" href="source/net/ipv4/fou.c#L617">617</a>         if (<a href="ident?i=err">err</a>)
<a name="L618" href="source/net/ipv4/fou.c#L618">618</a>                 return <a href="ident?i=err">err</a>;
<a name="L619" href="source/net/ipv4/fou.c#L619">619</a> 
<a name="L620" href="source/net/ipv4/fou.c#L620">620</a>         return <a href="ident?i=fou_destroy">fou_destroy</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L621" href="source/net/ipv4/fou.c#L621">621</a> }
<a name="L622" href="source/net/ipv4/fou.c#L622">622</a> 
<a name="L623" href="source/net/ipv4/fou.c#L623">623</a> static int <a href="ident?i=fou_fill_info">fou_fill_info</a>(struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=msg">msg</a>)
<a name="L624" href="source/net/ipv4/fou.c#L624">624</a> {
<a name="L625" href="source/net/ipv4/fou.c#L625">625</a>         if (<a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=msg">msg</a>, FOU_ATTR_AF, <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=sock">sock</a>-&gt;sk-&gt;<a href="ident?i=sk_family">sk_family</a>) ||
<a name="L626" href="source/net/ipv4/fou.c#L626">626</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=msg">msg</a>, FOU_ATTR_PORT, <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=port">port</a>) ||
<a name="L627" href="source/net/ipv4/fou.c#L627">627</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=msg">msg</a>, FOU_ATTR_IPPROTO, <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=protocol">protocol</a>) ||
<a name="L628" href="source/net/ipv4/fou.c#L628">628</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=msg">msg</a>, FOU_ATTR_TYPE, <a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=type">type</a>))
<a name="L629" href="source/net/ipv4/fou.c#L629">629</a>                 return -1;
<a name="L630" href="source/net/ipv4/fou.c#L630">630</a> 
<a name="L631" href="source/net/ipv4/fou.c#L631">631</a>         if (<a href="ident?i=fou">fou</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=FOU_F_REMCSUM_NOPARTIAL">FOU_F_REMCSUM_NOPARTIAL</a>)
<a name="L632" href="source/net/ipv4/fou.c#L632">632</a>                 if (<a href="ident?i=nla_put_flag">nla_put_flag</a>(<a href="ident?i=msg">msg</a>, FOU_ATTR_REMCSUM_NOPARTIAL))
<a name="L633" href="source/net/ipv4/fou.c#L633">633</a>                         return -1;
<a name="L634" href="source/net/ipv4/fou.c#L634">634</a>         return 0;
<a name="L635" href="source/net/ipv4/fou.c#L635">635</a> }
<a name="L636" href="source/net/ipv4/fou.c#L636">636</a> 
<a name="L637" href="source/net/ipv4/fou.c#L637">637</a> static int <a href="ident?i=fou_dump_info">fou_dump_info</a>(struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>, <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>,
<a name="L638" href="source/net/ipv4/fou.c#L638">638</a>                          <a href="ident?i=u32">u32</a> <a href="ident?i=flags">flags</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=cmd">cmd</a>)
<a name="L639" href="source/net/ipv4/fou.c#L639">639</a> {
<a name="L640" href="source/net/ipv4/fou.c#L640">640</a>         void *<a href="ident?i=hdr">hdr</a>;
<a name="L641" href="source/net/ipv4/fou.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/fou.c#L642">642</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=genlmsg_put">genlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, &amp;<a href="ident?i=fou_nl_family">fou_nl_family</a>, <a href="ident?i=flags">flags</a>, <a href="ident?i=cmd">cmd</a>);
<a name="L643" href="source/net/ipv4/fou.c#L643">643</a>         if (!<a href="ident?i=hdr">hdr</a>)
<a name="L644" href="source/net/ipv4/fou.c#L644">644</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L645" href="source/net/ipv4/fou.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/fou.c#L646">646</a>         if (<a href="ident?i=fou_fill_info">fou_fill_info</a>(<a href="ident?i=fou">fou</a>, <a href="ident?i=skb">skb</a>) &lt; 0)
<a name="L647" href="source/net/ipv4/fou.c#L647">647</a>                 goto nla_put_failure;
<a name="L648" href="source/net/ipv4/fou.c#L648">648</a> 
<a name="L649" href="source/net/ipv4/fou.c#L649">649</a>         <a href="ident?i=genlmsg_end">genlmsg_end</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=hdr">hdr</a>);
<a name="L650" href="source/net/ipv4/fou.c#L650">650</a>         return 0;
<a name="L651" href="source/net/ipv4/fou.c#L651">651</a> 
<a name="L652" href="source/net/ipv4/fou.c#L652">652</a> nla_put_failure:
<a name="L653" href="source/net/ipv4/fou.c#L653">653</a>         <a href="ident?i=genlmsg_cancel">genlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=hdr">hdr</a>);
<a name="L654" href="source/net/ipv4/fou.c#L654">654</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L655" href="source/net/ipv4/fou.c#L655">655</a> }
<a name="L656" href="source/net/ipv4/fou.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/fou.c#L657">657</a> static int <a href="ident?i=fou_nl_cmd_get_port">fou_nl_cmd_get_port</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=genl_info">genl_info</a> *<a href="ident?i=info">info</a>)
<a name="L658" href="source/net/ipv4/fou.c#L658">658</a> {
<a name="L659" href="source/net/ipv4/fou.c#L659">659</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=genl_info_net">genl_info_net</a>(<a href="ident?i=info">info</a>);
<a name="L660" href="source/net/ipv4/fou.c#L660">660</a>         struct <a href="ident?i=fou_net">fou_net</a> *fn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou_net_id">fou_net_id</a>);
<a name="L661" href="source/net/ipv4/fou.c#L661">661</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=msg">msg</a>;
<a name="L662" href="source/net/ipv4/fou.c#L662">662</a>         struct <a href="ident?i=fou_cfg">fou_cfg</a> <a href="ident?i=cfg">cfg</a>;
<a name="L663" href="source/net/ipv4/fou.c#L663">663</a>         struct <a href="ident?i=fou">fou</a> *fout;
<a name="L664" href="source/net/ipv4/fou.c#L664">664</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>;
<a name="L665" href="source/net/ipv4/fou.c#L665">665</a>         int <a href="ident?i=ret">ret</a>;
<a name="L666" href="source/net/ipv4/fou.c#L666">666</a> 
<a name="L667" href="source/net/ipv4/fou.c#L667">667</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=parse_nl_config">parse_nl_config</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L668" href="source/net/ipv4/fou.c#L668">668</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L669" href="source/net/ipv4/fou.c#L669">669</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L670" href="source/net/ipv4/fou.c#L670">670</a>         <a href="ident?i=port">port</a> = <a href="ident?i=cfg">cfg</a>.udp_config.local_udp_port;
<a name="L671" href="source/net/ipv4/fou.c#L671">671</a>         if (<a href="ident?i=port">port</a> == 0)
<a name="L672" href="source/net/ipv4/fou.c#L672">672</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L673" href="source/net/ipv4/fou.c#L673">673</a> 
<a name="L674" href="source/net/ipv4/fou.c#L674">674</a>         <a href="ident?i=msg">msg</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=NLMSG_DEFAULT_SIZE">NLMSG_DEFAULT_SIZE</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L675" href="source/net/ipv4/fou.c#L675">675</a>         if (!<a href="ident?i=msg">msg</a>)
<a name="L676" href="source/net/ipv4/fou.c#L676">676</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L677" href="source/net/ipv4/fou.c#L677">677</a> 
<a name="L678" href="source/net/ipv4/fou.c#L678">678</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L679" href="source/net/ipv4/fou.c#L679">679</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;fn-&gt;fou_lock);
<a name="L680" href="source/net/ipv4/fou.c#L680">680</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(fout, &amp;fn-&gt;fou_list, <a href="ident?i=list">list</a>) {
<a name="L681" href="source/net/ipv4/fou.c#L681">681</a>                 if (<a href="ident?i=port">port</a> == fout-&gt;<a href="ident?i=port">port</a>) {
<a name="L682" href="source/net/ipv4/fou.c#L682">682</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=fou_dump_info">fou_dump_info</a>(fout, <a href="ident?i=info">info</a>-&gt;snd_portid,
<a name="L683" href="source/net/ipv4/fou.c#L683">683</a>                                             <a href="ident?i=info">info</a>-&gt;snd_seq, 0, <a href="ident?i=msg">msg</a>,
<a name="L684" href="source/net/ipv4/fou.c#L684">684</a>                                             <a href="ident?i=info">info</a>-&gt;genlhdr-&gt;<a href="ident?i=cmd">cmd</a>);
<a name="L685" href="source/net/ipv4/fou.c#L685">685</a>                         break;
<a name="L686" href="source/net/ipv4/fou.c#L686">686</a>                 }
<a name="L687" href="source/net/ipv4/fou.c#L687">687</a>         }
<a name="L688" href="source/net/ipv4/fou.c#L688">688</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;fn-&gt;fou_lock);
<a name="L689" href="source/net/ipv4/fou.c#L689">689</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L690" href="source/net/ipv4/fou.c#L690">690</a>                 goto out_free;
<a name="L691" href="source/net/ipv4/fou.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/fou.c#L692">692</a>         return <a href="ident?i=genlmsg_reply">genlmsg_reply</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=info">info</a>);
<a name="L693" href="source/net/ipv4/fou.c#L693">693</a> 
<a name="L694" href="source/net/ipv4/fou.c#L694">694</a> out_free:
<a name="L695" href="source/net/ipv4/fou.c#L695">695</a>         <a href="ident?i=nlmsg_free">nlmsg_free</a>(<a href="ident?i=msg">msg</a>);
<a name="L696" href="source/net/ipv4/fou.c#L696">696</a>         return <a href="ident?i=ret">ret</a>;
<a name="L697" href="source/net/ipv4/fou.c#L697">697</a> }
<a name="L698" href="source/net/ipv4/fou.c#L698">698</a> 
<a name="L699" href="source/net/ipv4/fou.c#L699">699</a> static int <a href="ident?i=fou_nl_dump">fou_nl_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L700" href="source/net/ipv4/fou.c#L700">700</a> {
<a name="L701" href="source/net/ipv4/fou.c#L701">701</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L702" href="source/net/ipv4/fou.c#L702">702</a>         struct <a href="ident?i=fou_net">fou_net</a> *fn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou_net_id">fou_net_id</a>);
<a name="L703" href="source/net/ipv4/fou.c#L703">703</a>         struct <a href="ident?i=fou">fou</a> *fout;
<a name="L704" href="source/net/ipv4/fou.c#L704">704</a>         int <a href="ident?i=idx">idx</a> = 0, <a href="ident?i=ret">ret</a>;
<a name="L705" href="source/net/ipv4/fou.c#L705">705</a> 
<a name="L706" href="source/net/ipv4/fou.c#L706">706</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;fn-&gt;fou_lock);
<a name="L707" href="source/net/ipv4/fou.c#L707">707</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(fout, &amp;fn-&gt;fou_list, <a href="ident?i=list">list</a>) {
<a name="L708" href="source/net/ipv4/fou.c#L708">708</a>                 if (<a href="ident?i=idx">idx</a>++ &lt; <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0])
<a name="L709" href="source/net/ipv4/fou.c#L709">709</a>                         continue;
<a name="L710" href="source/net/ipv4/fou.c#L710">710</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=fou_dump_info">fou_dump_info</a>(fout, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L711" href="source/net/ipv4/fou.c#L711">711</a>                                     <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>,
<a name="L712" href="source/net/ipv4/fou.c#L712">712</a>                                     <a href="ident?i=skb">skb</a>, FOU_CMD_GET);
<a name="L713" href="source/net/ipv4/fou.c#L713">713</a>                 if (<a href="ident?i=ret">ret</a>)
<a name="L714" href="source/net/ipv4/fou.c#L714">714</a>                         break;
<a name="L715" href="source/net/ipv4/fou.c#L715">715</a>         }
<a name="L716" href="source/net/ipv4/fou.c#L716">716</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;fn-&gt;fou_lock);
<a name="L717" href="source/net/ipv4/fou.c#L717">717</a> 
<a name="L718" href="source/net/ipv4/fou.c#L718">718</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = <a href="ident?i=idx">idx</a>;
<a name="L719" href="source/net/ipv4/fou.c#L719">719</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L720" href="source/net/ipv4/fou.c#L720">720</a> }
<a name="L721" href="source/net/ipv4/fou.c#L721">721</a> 
<a name="L722" href="source/net/ipv4/fou.c#L722">722</a> static const struct <a href="ident?i=genl_ops">genl_ops</a> <a href="ident?i=fou_nl_ops">fou_nl_ops</a>[] = {
<a name="L723" href="source/net/ipv4/fou.c#L723">723</a>         {
<a name="L724" href="source/net/ipv4/fou.c#L724">724</a>                 .<a href="ident?i=cmd">cmd</a> = FOU_CMD_ADD,
<a name="L725" href="source/net/ipv4/fou.c#L725">725</a>                 .doit = <a href="ident?i=fou_nl_cmd_add_port">fou_nl_cmd_add_port</a>,
<a name="L726" href="source/net/ipv4/fou.c#L726">726</a>                 .<a href="ident?i=policy">policy</a> = <a href="ident?i=fou_nl_policy">fou_nl_policy</a>,
<a name="L727" href="source/net/ipv4/fou.c#L727">727</a>                 .<a href="ident?i=flags">flags</a> = <a href="ident?i=GENL_ADMIN_PERM">GENL_ADMIN_PERM</a>,
<a name="L728" href="source/net/ipv4/fou.c#L728">728</a>         },
<a name="L729" href="source/net/ipv4/fou.c#L729">729</a>         {
<a name="L730" href="source/net/ipv4/fou.c#L730">730</a>                 .<a href="ident?i=cmd">cmd</a> = FOU_CMD_DEL,
<a name="L731" href="source/net/ipv4/fou.c#L731">731</a>                 .doit = <a href="ident?i=fou_nl_cmd_rm_port">fou_nl_cmd_rm_port</a>,
<a name="L732" href="source/net/ipv4/fou.c#L732">732</a>                 .<a href="ident?i=policy">policy</a> = <a href="ident?i=fou_nl_policy">fou_nl_policy</a>,
<a name="L733" href="source/net/ipv4/fou.c#L733">733</a>                 .<a href="ident?i=flags">flags</a> = <a href="ident?i=GENL_ADMIN_PERM">GENL_ADMIN_PERM</a>,
<a name="L734" href="source/net/ipv4/fou.c#L734">734</a>         },
<a name="L735" href="source/net/ipv4/fou.c#L735">735</a>         {
<a name="L736" href="source/net/ipv4/fou.c#L736">736</a>                 .<a href="ident?i=cmd">cmd</a> = FOU_CMD_GET,
<a name="L737" href="source/net/ipv4/fou.c#L737">737</a>                 .doit = <a href="ident?i=fou_nl_cmd_get_port">fou_nl_cmd_get_port</a>,
<a name="L738" href="source/net/ipv4/fou.c#L738">738</a>                 .dumpit = <a href="ident?i=fou_nl_dump">fou_nl_dump</a>,
<a name="L739" href="source/net/ipv4/fou.c#L739">739</a>                 .<a href="ident?i=policy">policy</a> = <a href="ident?i=fou_nl_policy">fou_nl_policy</a>,
<a name="L740" href="source/net/ipv4/fou.c#L740">740</a>         },
<a name="L741" href="source/net/ipv4/fou.c#L741">741</a> };
<a name="L742" href="source/net/ipv4/fou.c#L742">742</a> 
<a name="L743" href="source/net/ipv4/fou.c#L743">743</a> <a href="ident?i=size_t">size_t</a> <a href="ident?i=fou_encap_hlen">fou_encap_hlen</a>(struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *<a href="ident?i=e">e</a>)
<a name="L744" href="source/net/ipv4/fou.c#L744">744</a> {
<a name="L745" href="source/net/ipv4/fou.c#L745">745</a>         return sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L746" href="source/net/ipv4/fou.c#L746">746</a> }
<a name="L747" href="source/net/ipv4/fou.c#L747">747</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=fou_encap_hlen">fou_encap_hlen</a>);
<a name="L748" href="source/net/ipv4/fou.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/fou.c#L749">749</a> <a href="ident?i=size_t">size_t</a> <a href="ident?i=gue_encap_hlen">gue_encap_hlen</a>(struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *<a href="ident?i=e">e</a>)
<a name="L750" href="source/net/ipv4/fou.c#L750">750</a> {
<a name="L751" href="source/net/ipv4/fou.c#L751">751</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>;
<a name="L752" href="source/net/ipv4/fou.c#L752">752</a>         <a href="ident?i=bool">bool</a> need_priv = <a href="ident?i=false">false</a>;
<a name="L753" href="source/net/ipv4/fou.c#L753">753</a> 
<a name="L754" href="source/net/ipv4/fou.c#L754">754</a>         <a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=udphdr">udphdr</a>) + sizeof(struct <a href="ident?i=guehdr">guehdr</a>);
<a name="L755" href="source/net/ipv4/fou.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/fou.c#L756">756</a>         if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_ENCAP_FLAG_REMCSUM">TUNNEL_ENCAP_FLAG_REMCSUM</a>) {
<a name="L757" href="source/net/ipv4/fou.c#L757">757</a>                 <a href="ident?i=len">len</a> += <a href="ident?i=GUE_PLEN_REMCSUM">GUE_PLEN_REMCSUM</a>;
<a name="L758" href="source/net/ipv4/fou.c#L758">758</a>                 need_priv = <a href="ident?i=true">true</a>;
<a name="L759" href="source/net/ipv4/fou.c#L759">759</a>         }
<a name="L760" href="source/net/ipv4/fou.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/fou.c#L761">761</a>         <a href="ident?i=len">len</a> += need_priv ? <a href="ident?i=GUE_LEN_PRIV">GUE_LEN_PRIV</a> : 0;
<a name="L762" href="source/net/ipv4/fou.c#L762">762</a> 
<a name="L763" href="source/net/ipv4/fou.c#L763">763</a>         return <a href="ident?i=len">len</a>;
<a name="L764" href="source/net/ipv4/fou.c#L764">764</a> }
<a name="L765" href="source/net/ipv4/fou.c#L765">765</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=gue_encap_hlen">gue_encap_hlen</a>);
<a name="L766" href="source/net/ipv4/fou.c#L766">766</a> 
<a name="L767" href="source/net/ipv4/fou.c#L767">767</a> static void <a href="ident?i=fou_build_udp">fou_build_udp</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *<a href="ident?i=e">e</a>,
<a name="L768" href="source/net/ipv4/fou.c#L768">768</a>                           struct <a href="ident?i=flowi4">flowi4</a> *fl4, <a href="ident?i=u8">u8</a> *<a href="ident?i=protocol">protocol</a>, <a href="ident?i=__be16">__be16</a> sport)
<a name="L769" href="source/net/ipv4/fou.c#L769">769</a> {
<a name="L770" href="source/net/ipv4/fou.c#L770">770</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh;
<a name="L771" href="source/net/ipv4/fou.c#L771">771</a> 
<a name="L772" href="source/net/ipv4/fou.c#L772">772</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>));
<a name="L773" href="source/net/ipv4/fou.c#L773">773</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L774" href="source/net/ipv4/fou.c#L774">774</a> 
<a name="L775" href="source/net/ipv4/fou.c#L775">775</a>         uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L776" href="source/net/ipv4/fou.c#L776">776</a> 
<a name="L777" href="source/net/ipv4/fou.c#L777">777</a>         uh-&gt;<a href="ident?i=dest">dest</a> = <a href="ident?i=e">e</a>-&gt;dport;
<a name="L778" href="source/net/ipv4/fou.c#L778">778</a>         uh-&gt;source = sport;
<a name="L779" href="source/net/ipv4/fou.c#L779">779</a>         uh-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L780" href="source/net/ipv4/fou.c#L780">780</a>         uh-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L781" href="source/net/ipv4/fou.c#L781">781</a>         <a href="ident?i=udp_set_csum">udp_set_csum</a>(!(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_ENCAP_FLAG_CSUM">TUNNEL_ENCAP_FLAG_CSUM</a>), <a href="ident?i=skb">skb</a>,
<a name="L782" href="source/net/ipv4/fou.c#L782">782</a>                      fl4-&gt;<a href="ident?i=saddr">saddr</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L783" href="source/net/ipv4/fou.c#L783">783</a> 
<a name="L784" href="source/net/ipv4/fou.c#L784">784</a>         *<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>;
<a name="L785" href="source/net/ipv4/fou.c#L785">785</a> }
<a name="L786" href="source/net/ipv4/fou.c#L786">786</a> 
<a name="L787" href="source/net/ipv4/fou.c#L787">787</a> int <a href="ident?i=fou_build_header">fou_build_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *<a href="ident?i=e">e</a>,
<a name="L788" href="source/net/ipv4/fou.c#L788">788</a>                      <a href="ident?i=u8">u8</a> *<a href="ident?i=protocol">protocol</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L789" href="source/net/ipv4/fou.c#L789">789</a> {
<a name="L790" href="source/net/ipv4/fou.c#L790">790</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=csum">csum</a> = !!(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_ENCAP_FLAG_CSUM">TUNNEL_ENCAP_FLAG_CSUM</a>);
<a name="L791" href="source/net/ipv4/fou.c#L791">791</a>         int <a href="ident?i=type">type</a> = <a href="ident?i=csum">csum</a> ? SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;
<a name="L792" href="source/net/ipv4/fou.c#L792">792</a>         <a href="ident?i=__be16">__be16</a> sport;
<a name="L793" href="source/net/ipv4/fou.c#L793">793</a> 
<a name="L794" href="source/net/ipv4/fou.c#L794">794</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=iptunnel_handle_offloads">iptunnel_handle_offloads</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=csum">csum</a>, <a href="ident?i=type">type</a>);
<a name="L795" href="source/net/ipv4/fou.c#L795">795</a> 
<a name="L796" href="source/net/ipv4/fou.c#L796">796</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=skb">skb</a>))
<a name="L797" href="source/net/ipv4/fou.c#L797">797</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L798" href="source/net/ipv4/fou.c#L798">798</a> 
<a name="L799" href="source/net/ipv4/fou.c#L799">799</a>         sport = <a href="ident?i=e">e</a>-&gt;sport ? : <a href="ident?i=udp_flow_src_port">udp_flow_src_port</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>),
<a name="L800" href="source/net/ipv4/fou.c#L800">800</a>                                                <a href="ident?i=skb">skb</a>, 0, 0, <a href="ident?i=false">false</a>);
<a name="L801" href="source/net/ipv4/fou.c#L801">801</a>         <a href="ident?i=fou_build_udp">fou_build_udp</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=e">e</a>, fl4, <a href="ident?i=protocol">protocol</a>, sport);
<a name="L802" href="source/net/ipv4/fou.c#L802">802</a> 
<a name="L803" href="source/net/ipv4/fou.c#L803">803</a>         return 0;
<a name="L804" href="source/net/ipv4/fou.c#L804">804</a> }
<a name="L805" href="source/net/ipv4/fou.c#L805">805</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=fou_build_header">fou_build_header</a>);
<a name="L806" href="source/net/ipv4/fou.c#L806">806</a> 
<a name="L807" href="source/net/ipv4/fou.c#L807">807</a> int <a href="ident?i=gue_build_header">gue_build_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *<a href="ident?i=e">e</a>,
<a name="L808" href="source/net/ipv4/fou.c#L808">808</a>                      <a href="ident?i=u8">u8</a> *<a href="ident?i=protocol">protocol</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L809" href="source/net/ipv4/fou.c#L809">809</a> {
<a name="L810" href="source/net/ipv4/fou.c#L810">810</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=csum">csum</a> = !!(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_ENCAP_FLAG_CSUM">TUNNEL_ENCAP_FLAG_CSUM</a>);
<a name="L811" href="source/net/ipv4/fou.c#L811">811</a>         int <a href="ident?i=type">type</a> = <a href="ident?i=csum">csum</a> ? SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;
<a name="L812" href="source/net/ipv4/fou.c#L812">812</a>         struct <a href="ident?i=guehdr">guehdr</a> *<a href="ident?i=guehdr">guehdr</a>;
<a name="L813" href="source/net/ipv4/fou.c#L813">813</a>         <a href="ident?i=size_t">size_t</a> hdrlen, <a href="ident?i=optlen">optlen</a> = 0;
<a name="L814" href="source/net/ipv4/fou.c#L814">814</a>         <a href="ident?i=__be16">__be16</a> sport;
<a name="L815" href="source/net/ipv4/fou.c#L815">815</a>         void *<a href="ident?i=data">data</a>;
<a name="L816" href="source/net/ipv4/fou.c#L816">816</a>         <a href="ident?i=bool">bool</a> need_priv = <a href="ident?i=false">false</a>;
<a name="L817" href="source/net/ipv4/fou.c#L817">817</a> 
<a name="L818" href="source/net/ipv4/fou.c#L818">818</a>         if ((<a href="ident?i=e">e</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TUNNEL_ENCAP_FLAG_REMCSUM">TUNNEL_ENCAP_FLAG_REMCSUM</a>) &amp;&amp;
<a name="L819" href="source/net/ipv4/fou.c#L819">819</a>             <a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) {
<a name="L820" href="source/net/ipv4/fou.c#L820">820</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=false">false</a>;
<a name="L821" href="source/net/ipv4/fou.c#L821">821</a>                 <a href="ident?i=optlen">optlen</a> += <a href="ident?i=GUE_PLEN_REMCSUM">GUE_PLEN_REMCSUM</a>;
<a name="L822" href="source/net/ipv4/fou.c#L822">822</a>                 <a href="ident?i=type">type</a> |= SKB_GSO_TUNNEL_REMCSUM;
<a name="L823" href="source/net/ipv4/fou.c#L823">823</a>                 need_priv = <a href="ident?i=true">true</a>;
<a name="L824" href="source/net/ipv4/fou.c#L824">824</a>         }
<a name="L825" href="source/net/ipv4/fou.c#L825">825</a> 
<a name="L826" href="source/net/ipv4/fou.c#L826">826</a>         <a href="ident?i=optlen">optlen</a> += need_priv ? <a href="ident?i=GUE_LEN_PRIV">GUE_LEN_PRIV</a> : 0;
<a name="L827" href="source/net/ipv4/fou.c#L827">827</a> 
<a name="L828" href="source/net/ipv4/fou.c#L828">828</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=iptunnel_handle_offloads">iptunnel_handle_offloads</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=csum">csum</a>, <a href="ident?i=type">type</a>);
<a name="L829" href="source/net/ipv4/fou.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/fou.c#L830">830</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=skb">skb</a>))
<a name="L831" href="source/net/ipv4/fou.c#L831">831</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L832" href="source/net/ipv4/fou.c#L832">832</a> 
<a name="L833" href="source/net/ipv4/fou.c#L833">833</a>         <b><i>/* Get source port (based on flow hash) before skb_push */</i></b>
<a name="L834" href="source/net/ipv4/fou.c#L834">834</a>         sport = <a href="ident?i=e">e</a>-&gt;sport ? : <a href="ident?i=udp_flow_src_port">udp_flow_src_port</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>),
<a name="L835" href="source/net/ipv4/fou.c#L835">835</a>                                                <a href="ident?i=skb">skb</a>, 0, 0, <a href="ident?i=false">false</a>);
<a name="L836" href="source/net/ipv4/fou.c#L836">836</a> 
<a name="L837" href="source/net/ipv4/fou.c#L837">837</a>         hdrlen = sizeof(struct <a href="ident?i=guehdr">guehdr</a>) + <a href="ident?i=optlen">optlen</a>;
<a name="L838" href="source/net/ipv4/fou.c#L838">838</a> 
<a name="L839" href="source/net/ipv4/fou.c#L839">839</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, hdrlen);
<a name="L840" href="source/net/ipv4/fou.c#L840">840</a> 
<a name="L841" href="source/net/ipv4/fou.c#L841">841</a>         <a href="ident?i=guehdr">guehdr</a> = (struct <a href="ident?i=guehdr">guehdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L842" href="source/net/ipv4/fou.c#L842">842</a> 
<a name="L843" href="source/net/ipv4/fou.c#L843">843</a>         <a href="ident?i=guehdr">guehdr</a>-&gt;control = 0;
<a name="L844" href="source/net/ipv4/fou.c#L844">844</a>         <a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=version">version</a> = 0;
<a name="L845" href="source/net/ipv4/fou.c#L845">845</a>         <a href="ident?i=guehdr">guehdr</a>-&gt;hlen = <a href="ident?i=optlen">optlen</a> &gt;&gt; 2;
<a name="L846" href="source/net/ipv4/fou.c#L846">846</a>         <a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=flags">flags</a> = 0;
<a name="L847" href="source/net/ipv4/fou.c#L847">847</a>         <a href="ident?i=guehdr">guehdr</a>-&gt;proto_ctype = *<a href="ident?i=protocol">protocol</a>;
<a name="L848" href="source/net/ipv4/fou.c#L848">848</a> 
<a name="L849" href="source/net/ipv4/fou.c#L849">849</a>         <a href="ident?i=data">data</a> = &amp;<a href="ident?i=guehdr">guehdr</a>[1];
<a name="L850" href="source/net/ipv4/fou.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/fou.c#L851">851</a>         if (need_priv) {
<a name="L852" href="source/net/ipv4/fou.c#L852">852</a>                 <a href="ident?i=__be32">__be32</a> *<a href="ident?i=flags">flags</a> = <a href="ident?i=data">data</a>;
<a name="L853" href="source/net/ipv4/fou.c#L853">853</a> 
<a name="L854" href="source/net/ipv4/fou.c#L854">854</a>                 <a href="ident?i=guehdr">guehdr</a>-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=GUE_FLAG_PRIV">GUE_FLAG_PRIV</a>;
<a name="L855" href="source/net/ipv4/fou.c#L855">855</a>                 *<a href="ident?i=flags">flags</a> = 0;
<a name="L856" href="source/net/ipv4/fou.c#L856">856</a>                 <a href="ident?i=data">data</a> += <a href="ident?i=GUE_LEN_PRIV">GUE_LEN_PRIV</a>;
<a name="L857" href="source/net/ipv4/fou.c#L857">857</a> 
<a name="L858" href="source/net/ipv4/fou.c#L858">858</a>                 if (<a href="ident?i=type">type</a> &amp; SKB_GSO_TUNNEL_REMCSUM) {
<a name="L859" href="source/net/ipv4/fou.c#L859">859</a>                         <a href="ident?i=u16">u16</a> csum_start = <a href="ident?i=skb_checksum_start_offset">skb_checksum_start_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L860" href="source/net/ipv4/fou.c#L860">860</a>                         <a href="ident?i=__be16">__be16</a> *<a href="ident?i=pd">pd</a> = <a href="ident?i=data">data</a>;
<a name="L861" href="source/net/ipv4/fou.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/fou.c#L862">862</a>                         if (csum_start &lt; hdrlen)
<a name="L863" href="source/net/ipv4/fou.c#L863">863</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L864" href="source/net/ipv4/fou.c#L864">864</a> 
<a name="L865" href="source/net/ipv4/fou.c#L865">865</a>                         csum_start -= hdrlen;
<a name="L866" href="source/net/ipv4/fou.c#L866">866</a>                         <a href="ident?i=pd">pd</a>[0] = <a href="ident?i=htons">htons</a>(csum_start);
<a name="L867" href="source/net/ipv4/fou.c#L867">867</a>                         <a href="ident?i=pd">pd</a>[1] = <a href="ident?i=htons">htons</a>(csum_start + <a href="ident?i=skb">skb</a>-&gt;csum_offset);
<a name="L868" href="source/net/ipv4/fou.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/fou.c#L869">869</a>                         if (!<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L870" href="source/net/ipv4/fou.c#L870">870</a>                                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L871" href="source/net/ipv4/fou.c#L871">871</a>                                 <a href="ident?i=skb">skb</a>-&gt;encapsulation = 0;
<a name="L872" href="source/net/ipv4/fou.c#L872">872</a>                         }
<a name="L873" href="source/net/ipv4/fou.c#L873">873</a> 
<a name="L874" href="source/net/ipv4/fou.c#L874">874</a>                         *<a href="ident?i=flags">flags</a> |= <a href="ident?i=GUE_PFLAG_REMCSUM">GUE_PFLAG_REMCSUM</a>;
<a name="L875" href="source/net/ipv4/fou.c#L875">875</a>                         <a href="ident?i=data">data</a> += <a href="ident?i=GUE_PLEN_REMCSUM">GUE_PLEN_REMCSUM</a>;
<a name="L876" href="source/net/ipv4/fou.c#L876">876</a>                 }
<a name="L877" href="source/net/ipv4/fou.c#L877">877</a> 
<a name="L878" href="source/net/ipv4/fou.c#L878">878</a>         }
<a name="L879" href="source/net/ipv4/fou.c#L879">879</a> 
<a name="L880" href="source/net/ipv4/fou.c#L880">880</a>         <a href="ident?i=fou_build_udp">fou_build_udp</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=e">e</a>, fl4, <a href="ident?i=protocol">protocol</a>, sport);
<a name="L881" href="source/net/ipv4/fou.c#L881">881</a> 
<a name="L882" href="source/net/ipv4/fou.c#L882">882</a>         return 0;
<a name="L883" href="source/net/ipv4/fou.c#L883">883</a> }
<a name="L884" href="source/net/ipv4/fou.c#L884">884</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=gue_build_header">gue_build_header</a>);
<a name="L885" href="source/net/ipv4/fou.c#L885">885</a> 
<a name="L886" href="source/net/ipv4/fou.c#L886">886</a> #ifdef CONFIG_NET_FOU_IP_TUNNELS
<a name="L887" href="source/net/ipv4/fou.c#L887">887</a> 
<a name="L888" href="source/net/ipv4/fou.c#L888">888</a> static const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> <a href="ident?i=fou_iptun_ops">fou_iptun_ops</a> = {
<a name="L889" href="source/net/ipv4/fou.c#L889">889</a>         .encap_hlen = <a href="ident?i=fou_encap_hlen">fou_encap_hlen</a>,
<a name="L890" href="source/net/ipv4/fou.c#L890">890</a>         .<a href="ident?i=build_header">build_header</a> = <a href="ident?i=fou_build_header">fou_build_header</a>,
<a name="L891" href="source/net/ipv4/fou.c#L891">891</a> };
<a name="L892" href="source/net/ipv4/fou.c#L892">892</a> 
<a name="L893" href="source/net/ipv4/fou.c#L893">893</a> static const struct <a href="ident?i=ip_tunnel_encap_ops">ip_tunnel_encap_ops</a> <a href="ident?i=gue_iptun_ops">gue_iptun_ops</a> = {
<a name="L894" href="source/net/ipv4/fou.c#L894">894</a>         .encap_hlen = <a href="ident?i=gue_encap_hlen">gue_encap_hlen</a>,
<a name="L895" href="source/net/ipv4/fou.c#L895">895</a>         .<a href="ident?i=build_header">build_header</a> = <a href="ident?i=gue_build_header">gue_build_header</a>,
<a name="L896" href="source/net/ipv4/fou.c#L896">896</a> };
<a name="L897" href="source/net/ipv4/fou.c#L897">897</a> 
<a name="L898" href="source/net/ipv4/fou.c#L898">898</a> static int <a href="ident?i=ip_tunnel_encap_add_fou_ops">ip_tunnel_encap_add_fou_ops</a>(void)
<a name="L899" href="source/net/ipv4/fou.c#L899">899</a> {
<a name="L900" href="source/net/ipv4/fou.c#L900">900</a>         int <a href="ident?i=ret">ret</a>;
<a name="L901" href="source/net/ipv4/fou.c#L901">901</a> 
<a name="L902" href="source/net/ipv4/fou.c#L902">902</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_tunnel_encap_add_ops">ip_tunnel_encap_add_ops</a>(&amp;<a href="ident?i=fou_iptun_ops">fou_iptun_ops</a>, TUNNEL_ENCAP_FOU);
<a name="L903" href="source/net/ipv4/fou.c#L903">903</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L904" href="source/net/ipv4/fou.c#L904">904</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"can't add fou ops\n"</i>);
<a name="L905" href="source/net/ipv4/fou.c#L905">905</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L906" href="source/net/ipv4/fou.c#L906">906</a>         }
<a name="L907" href="source/net/ipv4/fou.c#L907">907</a> 
<a name="L908" href="source/net/ipv4/fou.c#L908">908</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_tunnel_encap_add_ops">ip_tunnel_encap_add_ops</a>(&amp;<a href="ident?i=gue_iptun_ops">gue_iptun_ops</a>, TUNNEL_ENCAP_GUE);
<a name="L909" href="source/net/ipv4/fou.c#L909">909</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L910" href="source/net/ipv4/fou.c#L910">910</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"can't add gue ops\n"</i>);
<a name="L911" href="source/net/ipv4/fou.c#L911">911</a>                 <a href="ident?i=ip_tunnel_encap_del_ops">ip_tunnel_encap_del_ops</a>(&amp;<a href="ident?i=fou_iptun_ops">fou_iptun_ops</a>, TUNNEL_ENCAP_FOU);
<a name="L912" href="source/net/ipv4/fou.c#L912">912</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L913" href="source/net/ipv4/fou.c#L913">913</a>         }
<a name="L914" href="source/net/ipv4/fou.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/fou.c#L915">915</a>         return 0;
<a name="L916" href="source/net/ipv4/fou.c#L916">916</a> }
<a name="L917" href="source/net/ipv4/fou.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/fou.c#L918">918</a> static void <a href="ident?i=ip_tunnel_encap_del_fou_ops">ip_tunnel_encap_del_fou_ops</a>(void)
<a name="L919" href="source/net/ipv4/fou.c#L919">919</a> {
<a name="L920" href="source/net/ipv4/fou.c#L920">920</a>         <a href="ident?i=ip_tunnel_encap_del_ops">ip_tunnel_encap_del_ops</a>(&amp;<a href="ident?i=fou_iptun_ops">fou_iptun_ops</a>, TUNNEL_ENCAP_FOU);
<a name="L921" href="source/net/ipv4/fou.c#L921">921</a>         <a href="ident?i=ip_tunnel_encap_del_ops">ip_tunnel_encap_del_ops</a>(&amp;<a href="ident?i=gue_iptun_ops">gue_iptun_ops</a>, TUNNEL_ENCAP_GUE);
<a name="L922" href="source/net/ipv4/fou.c#L922">922</a> }
<a name="L923" href="source/net/ipv4/fou.c#L923">923</a> 
<a name="L924" href="source/net/ipv4/fou.c#L924">924</a> #else
<a name="L925" href="source/net/ipv4/fou.c#L925">925</a> 
<a name="L926" href="source/net/ipv4/fou.c#L926">926</a> static int <a href="ident?i=ip_tunnel_encap_add_fou_ops">ip_tunnel_encap_add_fou_ops</a>(void)
<a name="L927" href="source/net/ipv4/fou.c#L927">927</a> {
<a name="L928" href="source/net/ipv4/fou.c#L928">928</a>         return 0;
<a name="L929" href="source/net/ipv4/fou.c#L929">929</a> }
<a name="L930" href="source/net/ipv4/fou.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/fou.c#L931">931</a> static void <a href="ident?i=ip_tunnel_encap_del_fou_ops">ip_tunnel_encap_del_fou_ops</a>(void)
<a name="L932" href="source/net/ipv4/fou.c#L932">932</a> {
<a name="L933" href="source/net/ipv4/fou.c#L933">933</a> }
<a name="L934" href="source/net/ipv4/fou.c#L934">934</a> 
<a name="L935" href="source/net/ipv4/fou.c#L935">935</a> #endif
<a name="L936" href="source/net/ipv4/fou.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/fou.c#L937">937</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=fou_init_net">fou_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L938" href="source/net/ipv4/fou.c#L938">938</a> {
<a name="L939" href="source/net/ipv4/fou.c#L939">939</a>         struct <a href="ident?i=fou_net">fou_net</a> *fn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou_net_id">fou_net_id</a>);
<a name="L940" href="source/net/ipv4/fou.c#L940">940</a> 
<a name="L941" href="source/net/ipv4/fou.c#L941">941</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;fn-&gt;fou_list);
<a name="L942" href="source/net/ipv4/fou.c#L942">942</a>         <a href="ident?i=mutex_init">mutex_init</a>(&amp;fn-&gt;fou_lock);
<a name="L943" href="source/net/ipv4/fou.c#L943">943</a>         return 0;
<a name="L944" href="source/net/ipv4/fou.c#L944">944</a> }
<a name="L945" href="source/net/ipv4/fou.c#L945">945</a> 
<a name="L946" href="source/net/ipv4/fou.c#L946">946</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=fou_exit_net">fou_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L947" href="source/net/ipv4/fou.c#L947">947</a> {
<a name="L948" href="source/net/ipv4/fou.c#L948">948</a>         struct <a href="ident?i=fou_net">fou_net</a> *fn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=fou_net_id">fou_net_id</a>);
<a name="L949" href="source/net/ipv4/fou.c#L949">949</a>         struct <a href="ident?i=fou">fou</a> *<a href="ident?i=fou">fou</a>, *<a href="ident?i=next">next</a>;
<a name="L950" href="source/net/ipv4/fou.c#L950">950</a> 
<a name="L951" href="source/net/ipv4/fou.c#L951">951</a>         <b><i>/* Close all the FOU sockets */</i></b>
<a name="L952" href="source/net/ipv4/fou.c#L952">952</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;fn-&gt;fou_lock);
<a name="L953" href="source/net/ipv4/fou.c#L953">953</a>         <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=fou">fou</a>, <a href="ident?i=next">next</a>, &amp;fn-&gt;fou_list, <a href="ident?i=list">list</a>)
<a name="L954" href="source/net/ipv4/fou.c#L954">954</a>                 <a href="ident?i=fou_release">fou_release</a>(<a href="ident?i=fou">fou</a>);
<a name="L955" href="source/net/ipv4/fou.c#L955">955</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;fn-&gt;fou_lock);
<a name="L956" href="source/net/ipv4/fou.c#L956">956</a> }
<a name="L957" href="source/net/ipv4/fou.c#L957">957</a> 
<a name="L958" href="source/net/ipv4/fou.c#L958">958</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=fou_net_ops">fou_net_ops</a> = {
<a name="L959" href="source/net/ipv4/fou.c#L959">959</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=fou_init_net">fou_init_net</a>,
<a name="L960" href="source/net/ipv4/fou.c#L960">960</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=fou_exit_net">fou_exit_net</a>,
<a name="L961" href="source/net/ipv4/fou.c#L961">961</a>         .<a href="ident?i=id">id</a>   = &amp;<a href="ident?i=fou_net_id">fou_net_id</a>,
<a name="L962" href="source/net/ipv4/fou.c#L962">962</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=fou_net">fou_net</a>),
<a name="L963" href="source/net/ipv4/fou.c#L963">963</a> };
<a name="L964" href="source/net/ipv4/fou.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/fou.c#L965">965</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=fou_init">fou_init</a>(void)
<a name="L966" href="source/net/ipv4/fou.c#L966">966</a> {
<a name="L967" href="source/net/ipv4/fou.c#L967">967</a>         int <a href="ident?i=ret">ret</a>;
<a name="L968" href="source/net/ipv4/fou.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/fou.c#L969">969</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_device">register_pernet_device</a>(&amp;<a href="ident?i=fou_net_ops">fou_net_ops</a>);
<a name="L970" href="source/net/ipv4/fou.c#L970">970</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L971" href="source/net/ipv4/fou.c#L971">971</a>                 goto <a href="ident?i=exit">exit</a>;
<a name="L972" href="source/net/ipv4/fou.c#L972">972</a> 
<a name="L973" href="source/net/ipv4/fou.c#L973">973</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=genl_register_family_with_ops">genl_register_family_with_ops</a>(&amp;<a href="ident?i=fou_nl_family">fou_nl_family</a>,
<a name="L974" href="source/net/ipv4/fou.c#L974">974</a>                                             <a href="ident?i=fou_nl_ops">fou_nl_ops</a>);
<a name="L975" href="source/net/ipv4/fou.c#L975">975</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L976" href="source/net/ipv4/fou.c#L976">976</a>                 goto unregister;
<a name="L977" href="source/net/ipv4/fou.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/fou.c#L978">978</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_tunnel_encap_add_fou_ops">ip_tunnel_encap_add_fou_ops</a>();
<a name="L979" href="source/net/ipv4/fou.c#L979">979</a>         if (<a href="ident?i=ret">ret</a> == 0)
<a name="L980" href="source/net/ipv4/fou.c#L980">980</a>                 return 0;
<a name="L981" href="source/net/ipv4/fou.c#L981">981</a> 
<a name="L982" href="source/net/ipv4/fou.c#L982">982</a>         <a href="ident?i=genl_unregister_family">genl_unregister_family</a>(&amp;<a href="ident?i=fou_nl_family">fou_nl_family</a>);
<a name="L983" href="source/net/ipv4/fou.c#L983">983</a> unregister:
<a name="L984" href="source/net/ipv4/fou.c#L984">984</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=fou_net_ops">fou_net_ops</a>);
<a name="L985" href="source/net/ipv4/fou.c#L985">985</a> <a href="ident?i=exit">exit</a>:
<a name="L986" href="source/net/ipv4/fou.c#L986">986</a>         return <a href="ident?i=ret">ret</a>;
<a name="L987" href="source/net/ipv4/fou.c#L987">987</a> }
<a name="L988" href="source/net/ipv4/fou.c#L988">988</a> 
<a name="L989" href="source/net/ipv4/fou.c#L989">989</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=fou_fini">fou_fini</a>(void)
<a name="L990" href="source/net/ipv4/fou.c#L990">990</a> {
<a name="L991" href="source/net/ipv4/fou.c#L991">991</a>         <a href="ident?i=ip_tunnel_encap_del_fou_ops">ip_tunnel_encap_del_fou_ops</a>();
<a name="L992" href="source/net/ipv4/fou.c#L992">992</a>         <a href="ident?i=genl_unregister_family">genl_unregister_family</a>(&amp;<a href="ident?i=fou_nl_family">fou_nl_family</a>);
<a name="L993" href="source/net/ipv4/fou.c#L993">993</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=fou_net_ops">fou_net_ops</a>);
<a name="L994" href="source/net/ipv4/fou.c#L994">994</a> }
<a name="L995" href="source/net/ipv4/fou.c#L995">995</a> 
<a name="L996" href="source/net/ipv4/fou.c#L996">996</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=fou_init">fou_init</a>);
<a name="L997" href="source/net/ipv4/fou.c#L997">997</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=fou_fini">fou_fini</a>);
<a name="L998" href="source/net/ipv4/fou.c#L998">998</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Tom Herbert &lt;therbert@google.com&gt;"</i>);
<a name="L999" href="source/net/ipv4/fou.c#L999">999</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L1000" href="source/net/ipv4/fou.c#L1000">1000</a> </pre></div><p>
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
