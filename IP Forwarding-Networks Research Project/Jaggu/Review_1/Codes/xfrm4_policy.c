<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_policy.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_policy.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_policy.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_policy.c">xfrm4_policy.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_policy.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_policy.c#L2">2</a> <b><i> * xfrm4_policy.c</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_policy.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_policy.c#L4">4</a> <b><i> * Changes:</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_policy.c#L5">5</a> <b><i> *      Kazunori MIYAZAWA @USAGI</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_policy.c#L6">6</a> <b><i> *      YOSHIFUJI Hideaki @USAGI</i></b>
  <a name="L7" href="source/net/ipv4/xfrm4_policy.c#L7">7</a> <b><i> *              Split up af-specific portion</i></b>
  <a name="L8" href="source/net/ipv4/xfrm4_policy.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/xfrm4_policy.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/xfrm4_policy.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/xfrm4_policy.c#L11">11</a> #include &lt;linux/err.h&gt;
 <a name="L12" href="source/net/ipv4/xfrm4_policy.c#L12">12</a> #include &lt;linux/kernel.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_policy.c#L13">13</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_policy.c#L14">14</a> #include &lt;linux/if_tunnel.h&gt;
 <a name="L15" href="source/net/ipv4/xfrm4_policy.c#L15">15</a> #include &lt;net/dst.h&gt;
 <a name="L16" href="source/net/ipv4/xfrm4_policy.c#L16">16</a> #include &lt;net/xfrm.h&gt;
 <a name="L17" href="source/net/ipv4/xfrm4_policy.c#L17">17</a> #include &lt;net/ip.h&gt;
 <a name="L18" href="source/net/ipv4/xfrm4_policy.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/xfrm4_policy.c#L19">19</a> static struct <a href="ident?i=xfrm_policy_afinfo">xfrm_policy_afinfo</a> <a href="ident?i=xfrm4_policy_afinfo">xfrm4_policy_afinfo</a>;
 <a name="L20" href="source/net/ipv4/xfrm4_policy.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/xfrm4_policy.c#L21">21</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=__xfrm4_dst_lookup">__xfrm4_dst_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4,
 <a name="L22" href="source/net/ipv4/xfrm4_policy.c#L22">22</a>                                             int tos,
 <a name="L23" href="source/net/ipv4/xfrm4_policy.c#L23">23</a>                                             const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=saddr">saddr</a>,
 <a name="L24" href="source/net/ipv4/xfrm4_policy.c#L24">24</a>                                             const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=daddr">daddr</a>)
 <a name="L25" href="source/net/ipv4/xfrm4_policy.c#L25">25</a> {
 <a name="L26" href="source/net/ipv4/xfrm4_policy.c#L26">26</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
 <a name="L27" href="source/net/ipv4/xfrm4_policy.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/xfrm4_policy.c#L28">28</a>         <a href="ident?i=memset">memset</a>(fl4, 0, sizeof(*fl4));
 <a name="L29" href="source/net/ipv4/xfrm4_policy.c#L29">29</a>         fl4-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>-&gt;<a href="ident?i=a4">a4</a>;
 <a name="L30" href="source/net/ipv4/xfrm4_policy.c#L30">30</a>         fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a> = tos;
 <a name="L31" href="source/net/ipv4/xfrm4_policy.c#L31">31</a>         if (<a href="ident?i=saddr">saddr</a>)
 <a name="L32" href="source/net/ipv4/xfrm4_policy.c#L32">32</a>                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>-&gt;<a href="ident?i=a4">a4</a>;
 <a name="L33" href="source/net/ipv4/xfrm4_policy.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/xfrm4_policy.c#L34">34</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=net">net</a>, fl4);
 <a name="L35" href="source/net/ipv4/xfrm4_policy.c#L35">35</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
 <a name="L36" href="source/net/ipv4/xfrm4_policy.c#L36">36</a>                 return &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
 <a name="L37" href="source/net/ipv4/xfrm4_policy.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/xfrm4_policy.c#L38">38</a>         return <a href="ident?i=ERR_CAST">ERR_CAST</a>(<a href="ident?i=rt">rt</a>);
 <a name="L39" href="source/net/ipv4/xfrm4_policy.c#L39">39</a> }
 <a name="L40" href="source/net/ipv4/xfrm4_policy.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/xfrm4_policy.c#L41">41</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=xfrm4_dst_lookup">xfrm4_dst_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int tos,
 <a name="L42" href="source/net/ipv4/xfrm4_policy.c#L42">42</a>                                           const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=saddr">saddr</a>,
 <a name="L43" href="source/net/ipv4/xfrm4_policy.c#L43">43</a>                                           const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=daddr">daddr</a>)
 <a name="L44" href="source/net/ipv4/xfrm4_policy.c#L44">44</a> {
 <a name="L45" href="source/net/ipv4/xfrm4_policy.c#L45">45</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
 <a name="L46" href="source/net/ipv4/xfrm4_policy.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/xfrm4_policy.c#L47">47</a>         return <a href="ident?i=__xfrm4_dst_lookup">__xfrm4_dst_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, tos, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>);
 <a name="L48" href="source/net/ipv4/xfrm4_policy.c#L48">48</a> }
 <a name="L49" href="source/net/ipv4/xfrm4_policy.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/xfrm4_policy.c#L50">50</a> static int <a href="ident?i=xfrm4_get_saddr">xfrm4_get_saddr</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
 <a name="L51" href="source/net/ipv4/xfrm4_policy.c#L51">51</a>                            <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=saddr">saddr</a>, <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=daddr">daddr</a>)
 <a name="L52" href="source/net/ipv4/xfrm4_policy.c#L52">52</a> {
 <a name="L53" href="source/net/ipv4/xfrm4_policy.c#L53">53</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
 <a name="L54" href="source/net/ipv4/xfrm4_policy.c#L54">54</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
 <a name="L55" href="source/net/ipv4/xfrm4_policy.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/xfrm4_policy.c#L56">56</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=__xfrm4_dst_lookup">__xfrm4_dst_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, 0, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=daddr">daddr</a>);
 <a name="L57" href="source/net/ipv4/xfrm4_policy.c#L57">57</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=dst">dst</a>))
 <a name="L58" href="source/net/ipv4/xfrm4_policy.c#L58">58</a>                 return -<a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
 <a name="L59" href="source/net/ipv4/xfrm4_policy.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/xfrm4_policy.c#L60">60</a>         <a href="ident?i=saddr">saddr</a>-&gt;<a href="ident?i=a4">a4</a> = fl4.<a href="ident?i=saddr">saddr</a>;
 <a name="L61" href="source/net/ipv4/xfrm4_policy.c#L61">61</a>         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
 <a name="L62" href="source/net/ipv4/xfrm4_policy.c#L62">62</a>         return 0;
 <a name="L63" href="source/net/ipv4/xfrm4_policy.c#L63">63</a> }
 <a name="L64" href="source/net/ipv4/xfrm4_policy.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/xfrm4_policy.c#L65">65</a> static int <a href="ident?i=xfrm4_get_tos">xfrm4_get_tos</a>(const struct <a href="ident?i=flowi">flowi</a> *fl)
 <a name="L66" href="source/net/ipv4/xfrm4_policy.c#L66">66</a> {
 <a name="L67" href="source/net/ipv4/xfrm4_policy.c#L67">67</a>         return <a href="ident?i=IPTOS_RT_MASK">IPTOS_RT_MASK</a> &amp; fl-&gt;u.ip4.<a href="ident?i=flowi4_tos">flowi4_tos</a>; <b><i>/* Strip ECN bits */</i></b>
 <a name="L68" href="source/net/ipv4/xfrm4_policy.c#L68">68</a> }
 <a name="L69" href="source/net/ipv4/xfrm4_policy.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/xfrm4_policy.c#L70">70</a> static int <a href="ident?i=xfrm4_init_path">xfrm4_init_path</a>(struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *<a href="ident?i=path">path</a>, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
 <a name="L71" href="source/net/ipv4/xfrm4_policy.c#L71">71</a>                            int nfheader_len)
 <a name="L72" href="source/net/ipv4/xfrm4_policy.c#L72">72</a> {
 <a name="L73" href="source/net/ipv4/xfrm4_policy.c#L73">73</a>         return 0;
 <a name="L74" href="source/net/ipv4/xfrm4_policy.c#L74">74</a> }
 <a name="L75" href="source/net/ipv4/xfrm4_policy.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/xfrm4_policy.c#L76">76</a> static int <a href="ident?i=xfrm4_fill_dst">xfrm4_fill_dst</a>(struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *xdst, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
 <a name="L77" href="source/net/ipv4/xfrm4_policy.c#L77">77</a>                           const struct <a href="ident?i=flowi">flowi</a> *fl)
 <a name="L78" href="source/net/ipv4/xfrm4_policy.c#L78">78</a> {
 <a name="L79" href="source/net/ipv4/xfrm4_policy.c#L79">79</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)xdst-&gt;route;
 <a name="L80" href="source/net/ipv4/xfrm4_policy.c#L80">80</a>         const struct <a href="ident?i=flowi4">flowi4</a> *fl4 = &amp;fl-&gt;u.ip4;
 <a name="L81" href="source/net/ipv4/xfrm4_policy.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/xfrm4_policy.c#L82">82</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_iif = fl4-&gt;<a href="ident?i=flowi4_iif">flowi4_iif</a>;
 <a name="L83" href="source/net/ipv4/xfrm4_policy.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/xfrm4_policy.c#L84">84</a>         xdst-&gt;u.<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
 <a name="L85" href="source/net/ipv4/xfrm4_policy.c#L85">85</a>         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=dev">dev</a>);
 <a name="L86" href="source/net/ipv4/xfrm4_policy.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/xfrm4_policy.c#L87">87</a>         <b><i>/* Sheit... I remember I did this right. Apparently,</i></b>
 <a name="L88" href="source/net/ipv4/xfrm4_policy.c#L88">88</a> <b><i>         * it was magically lost, so this code needs audit */</i></b>
 <a name="L89" href="source/net/ipv4/xfrm4_policy.c#L89">89</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_is_input = <a href="ident?i=rt">rt</a>-&gt;rt_is_input;
 <a name="L90" href="source/net/ipv4/xfrm4_policy.c#L90">90</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_flags = <a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a> |
 <a name="L91" href="source/net/ipv4/xfrm4_policy.c#L91">91</a>                                               <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>);
 <a name="L92" href="source/net/ipv4/xfrm4_policy.c#L92">92</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_type = <a href="ident?i=rt">rt</a>-&gt;rt_type;
 <a name="L93" href="source/net/ipv4/xfrm4_policy.c#L93">93</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_gateway = <a href="ident?i=rt">rt</a>-&gt;rt_gateway;
 <a name="L94" href="source/net/ipv4/xfrm4_policy.c#L94">94</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_uses_gateway = <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway;
 <a name="L95" href="source/net/ipv4/xfrm4_policy.c#L95">95</a>         xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_pmtu = <a href="ident?i=rt">rt</a>-&gt;rt_pmtu;
 <a name="L96" href="source/net/ipv4/xfrm4_policy.c#L96">96</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;xdst-&gt;u.<a href="ident?i=rt">rt</a>.rt_uncached);
 <a name="L97" href="source/net/ipv4/xfrm4_policy.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/xfrm4_policy.c#L98">98</a>         return 0;
 <a name="L99" href="source/net/ipv4/xfrm4_policy.c#L99">99</a> }
<a name="L100" href="source/net/ipv4/xfrm4_policy.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/xfrm4_policy.c#L101">101</a> static void
<a name="L102" href="source/net/ipv4/xfrm4_policy.c#L102">102</a> <a href="ident?i=_decode_session4">_decode_session4</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=flowi">flowi</a> *fl, int <a href="ident?i=reverse">reverse</a>)
<a name="L103" href="source/net/ipv4/xfrm4_policy.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/xfrm4_policy.c#L104">104</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L105" href="source/net/ipv4/xfrm4_policy.c#L105">105</a>         <a href="ident?i=u8">u8</a> *xprth = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) + iph-&gt;ihl * 4;
<a name="L106" href="source/net/ipv4/xfrm4_policy.c#L106">106</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4 = &amp;fl-&gt;u.ip4;
<a name="L107" href="source/net/ipv4/xfrm4_policy.c#L107">107</a>         int oif = 0;
<a name="L108" href="source/net/ipv4/xfrm4_policy.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/xfrm4_policy.c#L109">109</a>         if (<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>))
<a name="L110" href="source/net/ipv4/xfrm4_policy.c#L110">110</a>                 oif = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L111" href="source/net/ipv4/xfrm4_policy.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/xfrm4_policy.c#L112">112</a>         <a href="ident?i=memset">memset</a>(fl4, 0, sizeof(struct <a href="ident?i=flowi4">flowi4</a>));
<a name="L113" href="source/net/ipv4/xfrm4_policy.c#L113">113</a>         fl4-&gt;<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
<a name="L114" href="source/net/ipv4/xfrm4_policy.c#L114">114</a>         fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> = <a href="ident?i=reverse">reverse</a> ? <a href="ident?i=skb">skb</a>-&gt;skb_iif : oif;
<a name="L115" href="source/net/ipv4/xfrm4_policy.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/xfrm4_policy.c#L116">116</a>         if (!<a href="ident?i=ip_is_fragment">ip_is_fragment</a>(iph)) {
<a name="L117" href="source/net/ipv4/xfrm4_policy.c#L117">117</a>                 switch (iph-&gt;<a href="ident?i=protocol">protocol</a>) {
<a name="L118" href="source/net/ipv4/xfrm4_policy.c#L118">118</a>                 case <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>:
<a name="L119" href="source/net/ipv4/xfrm4_policy.c#L119">119</a>                 case <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>:
<a name="L120" href="source/net/ipv4/xfrm4_policy.c#L120">120</a>                 case <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>:
<a name="L121" href="source/net/ipv4/xfrm4_policy.c#L121">121</a>                 case <a href="ident?i=IPPROTO_SCTP">IPPROTO_SCTP</a>:
<a name="L122" href="source/net/ipv4/xfrm4_policy.c#L122">122</a>                 case <a href="ident?i=IPPROTO_DCCP">IPPROTO_DCCP</a>:
<a name="L123" href="source/net/ipv4/xfrm4_policy.c#L123">123</a>                         if (xprth + 4 &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> ||
<a name="L124" href="source/net/ipv4/xfrm4_policy.c#L124">124</a>                             <a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, xprth + 4 - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L125" href="source/net/ipv4/xfrm4_policy.c#L125">125</a>                                 <a href="ident?i=__be16">__be16</a> *<a href="ident?i=ports">ports</a> = (<a href="ident?i=__be16">__be16</a> *)xprth;
<a name="L126" href="source/net/ipv4/xfrm4_policy.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/xfrm4_policy.c#L127">127</a>                                 fl4-&gt;<a href="ident?i=fl4_sport">fl4_sport</a> = <a href="ident?i=ports">ports</a>[!!<a href="ident?i=reverse">reverse</a>];
<a name="L128" href="source/net/ipv4/xfrm4_policy.c#L128">128</a>                                 fl4-&gt;<a href="ident?i=fl4_dport">fl4_dport</a> = <a href="ident?i=ports">ports</a>[!<a href="ident?i=reverse">reverse</a>];
<a name="L129" href="source/net/ipv4/xfrm4_policy.c#L129">129</a>                         }
<a name="L130" href="source/net/ipv4/xfrm4_policy.c#L130">130</a>                         break;
<a name="L131" href="source/net/ipv4/xfrm4_policy.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/xfrm4_policy.c#L132">132</a>                 case <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>:
<a name="L133" href="source/net/ipv4/xfrm4_policy.c#L133">133</a>                         if (<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, xprth + 2 - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L134" href="source/net/ipv4/xfrm4_policy.c#L134">134</a>                                 <a href="ident?i=u8">u8</a> *icmp = xprth;
<a name="L135" href="source/net/ipv4/xfrm4_policy.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/xfrm4_policy.c#L136">136</a>                                 fl4-&gt;<a href="ident?i=fl4_icmp_type">fl4_icmp_type</a> = icmp[0];
<a name="L137" href="source/net/ipv4/xfrm4_policy.c#L137">137</a>                                 fl4-&gt;<a href="ident?i=fl4_icmp_code">fl4_icmp_code</a> = icmp[1];
<a name="L138" href="source/net/ipv4/xfrm4_policy.c#L138">138</a>                         }
<a name="L139" href="source/net/ipv4/xfrm4_policy.c#L139">139</a>                         break;
<a name="L140" href="source/net/ipv4/xfrm4_policy.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/xfrm4_policy.c#L141">141</a>                 case <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>:
<a name="L142" href="source/net/ipv4/xfrm4_policy.c#L142">142</a>                         if (<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, xprth + 4 - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L143" href="source/net/ipv4/xfrm4_policy.c#L143">143</a>                                 <a href="ident?i=__be32">__be32</a> *<a href="ident?i=ehdr">ehdr</a> = (<a href="ident?i=__be32">__be32</a> *)xprth;
<a name="L144" href="source/net/ipv4/xfrm4_policy.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/xfrm4_policy.c#L145">145</a>                                 fl4-&gt;<a href="ident?i=fl4_ipsec_spi">fl4_ipsec_spi</a> = <a href="ident?i=ehdr">ehdr</a>[0];
<a name="L146" href="source/net/ipv4/xfrm4_policy.c#L146">146</a>                         }
<a name="L147" href="source/net/ipv4/xfrm4_policy.c#L147">147</a>                         break;
<a name="L148" href="source/net/ipv4/xfrm4_policy.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/xfrm4_policy.c#L149">149</a>                 case <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>:
<a name="L150" href="source/net/ipv4/xfrm4_policy.c#L150">150</a>                         if (<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, xprth + 8 - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L151" href="source/net/ipv4/xfrm4_policy.c#L151">151</a>                                 <a href="ident?i=__be32">__be32</a> *ah_hdr = (<a href="ident?i=__be32">__be32</a> *)xprth;
<a name="L152" href="source/net/ipv4/xfrm4_policy.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/xfrm4_policy.c#L153">153</a>                                 fl4-&gt;<a href="ident?i=fl4_ipsec_spi">fl4_ipsec_spi</a> = ah_hdr[1];
<a name="L154" href="source/net/ipv4/xfrm4_policy.c#L154">154</a>                         }
<a name="L155" href="source/net/ipv4/xfrm4_policy.c#L155">155</a>                         break;
<a name="L156" href="source/net/ipv4/xfrm4_policy.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/xfrm4_policy.c#L157">157</a>                 case <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>:
<a name="L158" href="source/net/ipv4/xfrm4_policy.c#L158">158</a>                         if (<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, xprth + 4 - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L159" href="source/net/ipv4/xfrm4_policy.c#L159">159</a>                                 <a href="ident?i=__be16">__be16</a> *ipcomp_hdr = (<a href="ident?i=__be16">__be16</a> *)xprth;
<a name="L160" href="source/net/ipv4/xfrm4_policy.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/xfrm4_policy.c#L161">161</a>                                 fl4-&gt;<a href="ident?i=fl4_ipsec_spi">fl4_ipsec_spi</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohs">ntohs</a>(ipcomp_hdr[1]));
<a name="L162" href="source/net/ipv4/xfrm4_policy.c#L162">162</a>                         }
<a name="L163" href="source/net/ipv4/xfrm4_policy.c#L163">163</a>                         break;
<a name="L164" href="source/net/ipv4/xfrm4_policy.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/xfrm4_policy.c#L165">165</a>                 case <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>:
<a name="L166" href="source/net/ipv4/xfrm4_policy.c#L166">166</a>                         if (<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, xprth + 12 - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L167" href="source/net/ipv4/xfrm4_policy.c#L167">167</a>                                 <a href="ident?i=__be16">__be16</a> *greflags = (<a href="ident?i=__be16">__be16</a> *)xprth;
<a name="L168" href="source/net/ipv4/xfrm4_policy.c#L168">168</a>                                 <a href="ident?i=__be32">__be32</a> *<a href="ident?i=gre_hdr">gre_hdr</a> = (<a href="ident?i=__be32">__be32</a> *)xprth;
<a name="L169" href="source/net/ipv4/xfrm4_policy.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/xfrm4_policy.c#L170">170</a>                                 if (greflags[0] &amp; <a href="ident?i=GRE_KEY">GRE_KEY</a>) {
<a name="L171" href="source/net/ipv4/xfrm4_policy.c#L171">171</a>                                         if (greflags[0] &amp; <a href="ident?i=GRE_CSUM">GRE_CSUM</a>)
<a name="L172" href="source/net/ipv4/xfrm4_policy.c#L172">172</a>                                                 <a href="ident?i=gre_hdr">gre_hdr</a>++;
<a name="L173" href="source/net/ipv4/xfrm4_policy.c#L173">173</a>                                         fl4-&gt;<a href="ident?i=fl4_gre_key">fl4_gre_key</a> = <a href="ident?i=gre_hdr">gre_hdr</a>[1];
<a name="L174" href="source/net/ipv4/xfrm4_policy.c#L174">174</a>                                 }
<a name="L175" href="source/net/ipv4/xfrm4_policy.c#L175">175</a>                         }
<a name="L176" href="source/net/ipv4/xfrm4_policy.c#L176">176</a>                         break;
<a name="L177" href="source/net/ipv4/xfrm4_policy.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/xfrm4_policy.c#L178">178</a>                 default:
<a name="L179" href="source/net/ipv4/xfrm4_policy.c#L179">179</a>                         fl4-&gt;<a href="ident?i=fl4_ipsec_spi">fl4_ipsec_spi</a> = 0;
<a name="L180" href="source/net/ipv4/xfrm4_policy.c#L180">180</a>                         break;
<a name="L181" href="source/net/ipv4/xfrm4_policy.c#L181">181</a>                 }
<a name="L182" href="source/net/ipv4/xfrm4_policy.c#L182">182</a>         }
<a name="L183" href="source/net/ipv4/xfrm4_policy.c#L183">183</a>         fl4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L184" href="source/net/ipv4/xfrm4_policy.c#L184">184</a>         fl4-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=reverse">reverse</a> ? iph-&gt;<a href="ident?i=saddr">saddr</a> : iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L185" href="source/net/ipv4/xfrm4_policy.c#L185">185</a>         fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=reverse">reverse</a> ? iph-&gt;<a href="ident?i=daddr">daddr</a> : iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L186" href="source/net/ipv4/xfrm4_policy.c#L186">186</a>         fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a> = iph-&gt;tos;
<a name="L187" href="source/net/ipv4/xfrm4_policy.c#L187">187</a> }
<a name="L188" href="source/net/ipv4/xfrm4_policy.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/xfrm4_policy.c#L189">189</a> static inline int <a href="ident?i=xfrm4_garbage_collect">xfrm4_garbage_collect</a>(struct <a href="ident?i=dst_ops">dst_ops</a> *<a href="ident?i=ops">ops</a>)
<a name="L190" href="source/net/ipv4/xfrm4_policy.c#L190">190</a> {
<a name="L191" href="source/net/ipv4/xfrm4_policy.c#L191">191</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=ops">ops</a>, struct <a href="ident?i=net">net</a>, xfrm.<a href="ident?i=xfrm4_dst_ops">xfrm4_dst_ops</a>);
<a name="L192" href="source/net/ipv4/xfrm4_policy.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/xfrm4_policy.c#L193">193</a>         <a href="ident?i=xfrm4_policy_afinfo">xfrm4_policy_afinfo</a>.garbage_collect(<a href="ident?i=net">net</a>);
<a name="L194" href="source/net/ipv4/xfrm4_policy.c#L194">194</a>         return (<a href="ident?i=dst_entries_get_slow">dst_entries_get_slow</a>(<a href="ident?i=ops">ops</a>) &gt; <a href="ident?i=ops">ops</a>-&gt;gc_thresh * 2);
<a name="L195" href="source/net/ipv4/xfrm4_policy.c#L195">195</a> }
<a name="L196" href="source/net/ipv4/xfrm4_policy.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/xfrm4_policy.c#L197">197</a> static void <a href="ident?i=xfrm4_update_pmtu">xfrm4_update_pmtu</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L198" href="source/net/ipv4/xfrm4_policy.c#L198">198</a>                               struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L199" href="source/net/ipv4/xfrm4_policy.c#L199">199</a> {
<a name="L200" href="source/net/ipv4/xfrm4_policy.c#L200">200</a>         struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *xdst = (struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *)<a href="ident?i=dst">dst</a>;
<a name="L201" href="source/net/ipv4/xfrm4_policy.c#L201">201</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=path">path</a> = xdst-&gt;route;
<a name="L202" href="source/net/ipv4/xfrm4_policy.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/xfrm4_policy.c#L203">203</a>         <a href="ident?i=path">path</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;update_pmtu(<a href="ident?i=path">path</a>, sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=mtu">mtu</a>);
<a name="L204" href="source/net/ipv4/xfrm4_policy.c#L204">204</a> }
<a name="L205" href="source/net/ipv4/xfrm4_policy.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/xfrm4_policy.c#L206">206</a> static void <a href="ident?i=xfrm4_redirect">xfrm4_redirect</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L207" href="source/net/ipv4/xfrm4_policy.c#L207">207</a>                            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L208" href="source/net/ipv4/xfrm4_policy.c#L208">208</a> {
<a name="L209" href="source/net/ipv4/xfrm4_policy.c#L209">209</a>         struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *xdst = (struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *)<a href="ident?i=dst">dst</a>;
<a name="L210" href="source/net/ipv4/xfrm4_policy.c#L210">210</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=path">path</a> = xdst-&gt;route;
<a name="L211" href="source/net/ipv4/xfrm4_policy.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/xfrm4_policy.c#L212">212</a>         <a href="ident?i=path">path</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=redirect">redirect</a>(<a href="ident?i=path">path</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L213" href="source/net/ipv4/xfrm4_policy.c#L213">213</a> }
<a name="L214" href="source/net/ipv4/xfrm4_policy.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/xfrm4_policy.c#L215">215</a> static void <a href="ident?i=xfrm4_dst_destroy">xfrm4_dst_destroy</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L216" href="source/net/ipv4/xfrm4_policy.c#L216">216</a> {
<a name="L217" href="source/net/ipv4/xfrm4_policy.c#L217">217</a>         struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *xdst = (struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *)<a href="ident?i=dst">dst</a>;
<a name="L218" href="source/net/ipv4/xfrm4_policy.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/xfrm4_policy.c#L219">219</a>         <a href="ident?i=dst_destroy_metrics_generic">dst_destroy_metrics_generic</a>(<a href="ident?i=dst">dst</a>);
<a name="L220" href="source/net/ipv4/xfrm4_policy.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/xfrm4_policy.c#L221">221</a>         <a href="ident?i=xfrm_dst_destroy">xfrm_dst_destroy</a>(xdst);
<a name="L222" href="source/net/ipv4/xfrm4_policy.c#L222">222</a> }
<a name="L223" href="source/net/ipv4/xfrm4_policy.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/xfrm4_policy.c#L224">224</a> static void <a href="ident?i=xfrm4_dst_ifdown">xfrm4_dst_ifdown</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L225" href="source/net/ipv4/xfrm4_policy.c#L225">225</a>                              int unregister)
<a name="L226" href="source/net/ipv4/xfrm4_policy.c#L226">226</a> {
<a name="L227" href="source/net/ipv4/xfrm4_policy.c#L227">227</a>         if (!unregister)
<a name="L228" href="source/net/ipv4/xfrm4_policy.c#L228">228</a>                 return;
<a name="L229" href="source/net/ipv4/xfrm4_policy.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/xfrm4_policy.c#L230">230</a>         <a href="ident?i=xfrm_dst_ifdown">xfrm_dst_ifdown</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=dev">dev</a>);
<a name="L231" href="source/net/ipv4/xfrm4_policy.c#L231">231</a> }
<a name="L232" href="source/net/ipv4/xfrm4_policy.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/xfrm4_policy.c#L233">233</a> static struct <a href="ident?i=dst_ops">dst_ops</a> <a href="ident?i=xfrm4_dst_ops">xfrm4_dst_ops</a> = {
<a name="L234" href="source/net/ipv4/xfrm4_policy.c#L234">234</a>         .<a href="ident?i=family">family</a> =               <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L235" href="source/net/ipv4/xfrm4_policy.c#L235">235</a>         .<a href="ident?i=gc">gc</a> =                   <a href="ident?i=xfrm4_garbage_collect">xfrm4_garbage_collect</a>,
<a name="L236" href="source/net/ipv4/xfrm4_policy.c#L236">236</a>         .update_pmtu =          <a href="ident?i=xfrm4_update_pmtu">xfrm4_update_pmtu</a>,
<a name="L237" href="source/net/ipv4/xfrm4_policy.c#L237">237</a>         .<a href="ident?i=redirect">redirect</a> =             <a href="ident?i=xfrm4_redirect">xfrm4_redirect</a>,
<a name="L238" href="source/net/ipv4/xfrm4_policy.c#L238">238</a>         .cow_metrics =          <a href="ident?i=dst_cow_metrics_generic">dst_cow_metrics_generic</a>,
<a name="L239" href="source/net/ipv4/xfrm4_policy.c#L239">239</a>         .<a href="ident?i=destroy">destroy</a> =              <a href="ident?i=xfrm4_dst_destroy">xfrm4_dst_destroy</a>,
<a name="L240" href="source/net/ipv4/xfrm4_policy.c#L240">240</a>         .<a href="ident?i=ifdown">ifdown</a> =               <a href="ident?i=xfrm4_dst_ifdown">xfrm4_dst_ifdown</a>,
<a name="L241" href="source/net/ipv4/xfrm4_policy.c#L241">241</a>         .local_out =            <a href="ident?i=__ip_local_out">__ip_local_out</a>,
<a name="L242" href="source/net/ipv4/xfrm4_policy.c#L242">242</a>         .gc_thresh =            32768,
<a name="L243" href="source/net/ipv4/xfrm4_policy.c#L243">243</a> };
<a name="L244" href="source/net/ipv4/xfrm4_policy.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/xfrm4_policy.c#L245">245</a> static struct <a href="ident?i=xfrm_policy_afinfo">xfrm_policy_afinfo</a> <a href="ident?i=xfrm4_policy_afinfo">xfrm4_policy_afinfo</a> = {
<a name="L246" href="source/net/ipv4/xfrm4_policy.c#L246">246</a>         .<a href="ident?i=family">family</a> =               <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L247" href="source/net/ipv4/xfrm4_policy.c#L247">247</a>         .<a href="ident?i=dst_ops">dst_ops</a> =              &amp;<a href="ident?i=xfrm4_dst_ops">xfrm4_dst_ops</a>,
<a name="L248" href="source/net/ipv4/xfrm4_policy.c#L248">248</a>         .dst_lookup =           <a href="ident?i=xfrm4_dst_lookup">xfrm4_dst_lookup</a>,
<a name="L249" href="source/net/ipv4/xfrm4_policy.c#L249">249</a>         .get_saddr =            <a href="ident?i=xfrm4_get_saddr">xfrm4_get_saddr</a>,
<a name="L250" href="source/net/ipv4/xfrm4_policy.c#L250">250</a>         .decode_session =       <a href="ident?i=_decode_session4">_decode_session4</a>,
<a name="L251" href="source/net/ipv4/xfrm4_policy.c#L251">251</a>         .get_tos =              <a href="ident?i=xfrm4_get_tos">xfrm4_get_tos</a>,
<a name="L252" href="source/net/ipv4/xfrm4_policy.c#L252">252</a>         .init_path =            <a href="ident?i=xfrm4_init_path">xfrm4_init_path</a>,
<a name="L253" href="source/net/ipv4/xfrm4_policy.c#L253">253</a>         .fill_dst =             <a href="ident?i=xfrm4_fill_dst">xfrm4_fill_dst</a>,
<a name="L254" href="source/net/ipv4/xfrm4_policy.c#L254">254</a>         .blackhole_route =      <a href="ident?i=ipv4_blackhole_route">ipv4_blackhole_route</a>,
<a name="L255" href="source/net/ipv4/xfrm4_policy.c#L255">255</a> };
<a name="L256" href="source/net/ipv4/xfrm4_policy.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/xfrm4_policy.c#L257">257</a> #ifdef CONFIG_SYSCTL
<a name="L258" href="source/net/ipv4/xfrm4_policy.c#L258">258</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=xfrm4_policy_table">xfrm4_policy_table</a>[] = {
<a name="L259" href="source/net/ipv4/xfrm4_policy.c#L259">259</a>         {
<a name="L260" href="source/net/ipv4/xfrm4_policy.c#L260">260</a>                 .<a href="ident?i=procname">procname</a>       = <i>"xfrm4_gc_thresh"</i>,
<a name="L261" href="source/net/ipv4/xfrm4_policy.c#L261">261</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.xfrm.<a href="ident?i=xfrm4_dst_ops">xfrm4_dst_ops</a>.gc_thresh,
<a name="L262" href="source/net/ipv4/xfrm4_policy.c#L262">262</a>                 .maxlen         = sizeof(int),
<a name="L263" href="source/net/ipv4/xfrm4_policy.c#L263">263</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L264" href="source/net/ipv4/xfrm4_policy.c#L264">264</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L265" href="source/net/ipv4/xfrm4_policy.c#L265">265</a>         },
<a name="L266" href="source/net/ipv4/xfrm4_policy.c#L266">266</a>         { }
<a name="L267" href="source/net/ipv4/xfrm4_policy.c#L267">267</a> };
<a name="L268" href="source/net/ipv4/xfrm4_policy.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/xfrm4_policy.c#L269">269</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=xfrm4_net_init">xfrm4_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L270" href="source/net/ipv4/xfrm4_policy.c#L270">270</a> {
<a name="L271" href="source/net/ipv4/xfrm4_policy.c#L271">271</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>;
<a name="L272" href="source/net/ipv4/xfrm4_policy.c#L272">272</a>         struct <a href="ident?i=ctl_table_header">ctl_table_header</a> *<a href="ident?i=hdr">hdr</a>;
<a name="L273" href="source/net/ipv4/xfrm4_policy.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/xfrm4_policy.c#L274">274</a>         <a href="ident?i=table">table</a> = <a href="ident?i=xfrm4_policy_table">xfrm4_policy_table</a>;
<a name="L275" href="source/net/ipv4/xfrm4_policy.c#L275">275</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>)) {
<a name="L276" href="source/net/ipv4/xfrm4_policy.c#L276">276</a>                 <a href="ident?i=table">table</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=table">table</a>, sizeof(<a href="ident?i=xfrm4_policy_table">xfrm4_policy_table</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L277" href="source/net/ipv4/xfrm4_policy.c#L277">277</a>                 if (!<a href="ident?i=table">table</a>)
<a name="L278" href="source/net/ipv4/xfrm4_policy.c#L278">278</a>                         goto err_alloc;
<a name="L279" href="source/net/ipv4/xfrm4_policy.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/xfrm4_policy.c#L280">280</a>                 <a href="ident?i=table">table</a>[0].<a href="ident?i=data">data</a> = &amp;<a href="ident?i=net">net</a>-&gt;xfrm.<a href="ident?i=xfrm4_dst_ops">xfrm4_dst_ops</a>.gc_thresh;
<a name="L281" href="source/net/ipv4/xfrm4_policy.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/xfrm4_policy.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/xfrm4_policy.c#L283">283</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(<a href="ident?i=net">net</a>, <i>"net/ipv4"</i>, <a href="ident?i=table">table</a>);
<a name="L284" href="source/net/ipv4/xfrm4_policy.c#L284">284</a>         if (!<a href="ident?i=hdr">hdr</a>)
<a name="L285" href="source/net/ipv4/xfrm4_policy.c#L285">285</a>                 goto err_reg;
<a name="L286" href="source/net/ipv4/xfrm4_policy.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/xfrm4_policy.c#L287">287</a>         <a href="ident?i=net">net</a>-&gt;ipv4.xfrm4_hdr = <a href="ident?i=hdr">hdr</a>;
<a name="L288" href="source/net/ipv4/xfrm4_policy.c#L288">288</a>         return 0;
<a name="L289" href="source/net/ipv4/xfrm4_policy.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/xfrm4_policy.c#L290">290</a> err_reg:
<a name="L291" href="source/net/ipv4/xfrm4_policy.c#L291">291</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L292" href="source/net/ipv4/xfrm4_policy.c#L292">292</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=table">table</a>);
<a name="L293" href="source/net/ipv4/xfrm4_policy.c#L293">293</a> err_alloc:
<a name="L294" href="source/net/ipv4/xfrm4_policy.c#L294">294</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L295" href="source/net/ipv4/xfrm4_policy.c#L295">295</a> }
<a name="L296" href="source/net/ipv4/xfrm4_policy.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/xfrm4_policy.c#L297">297</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=xfrm4_net_exit">xfrm4_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L298" href="source/net/ipv4/xfrm4_policy.c#L298">298</a> {
<a name="L299" href="source/net/ipv4/xfrm4_policy.c#L299">299</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>;
<a name="L300" href="source/net/ipv4/xfrm4_policy.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/xfrm4_policy.c#L301">301</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.xfrm4_hdr)
<a name="L302" href="source/net/ipv4/xfrm4_policy.c#L302">302</a>                 return;
<a name="L303" href="source/net/ipv4/xfrm4_policy.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/xfrm4_policy.c#L304">304</a>         <a href="ident?i=table">table</a> = <a href="ident?i=net">net</a>-&gt;ipv4.xfrm4_hdr-&gt;ctl_table_arg;
<a name="L305" href="source/net/ipv4/xfrm4_policy.c#L305">305</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.xfrm4_hdr);
<a name="L306" href="source/net/ipv4/xfrm4_policy.c#L306">306</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L307" href="source/net/ipv4/xfrm4_policy.c#L307">307</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=table">table</a>);
<a name="L308" href="source/net/ipv4/xfrm4_policy.c#L308">308</a> }
<a name="L309" href="source/net/ipv4/xfrm4_policy.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/xfrm4_policy.c#L310">310</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=__net_initdata">__net_initdata</a> <a href="ident?i=xfrm4_net_ops">xfrm4_net_ops</a> = {
<a name="L311" href="source/net/ipv4/xfrm4_policy.c#L311">311</a>         .<a href="ident?i=init">init</a>   = <a href="ident?i=xfrm4_net_init">xfrm4_net_init</a>,
<a name="L312" href="source/net/ipv4/xfrm4_policy.c#L312">312</a>         .<a href="ident?i=exit">exit</a>   = <a href="ident?i=xfrm4_net_exit">xfrm4_net_exit</a>,
<a name="L313" href="source/net/ipv4/xfrm4_policy.c#L313">313</a> };
<a name="L314" href="source/net/ipv4/xfrm4_policy.c#L314">314</a> #endif
<a name="L315" href="source/net/ipv4/xfrm4_policy.c#L315">315</a> 
<a name="L316" href="source/net/ipv4/xfrm4_policy.c#L316">316</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=xfrm4_policy_init">xfrm4_policy_init</a>(void)
<a name="L317" href="source/net/ipv4/xfrm4_policy.c#L317">317</a> {
<a name="L318" href="source/net/ipv4/xfrm4_policy.c#L318">318</a>         <a href="ident?i=xfrm_policy_register_afinfo">xfrm_policy_register_afinfo</a>(&amp;<a href="ident?i=xfrm4_policy_afinfo">xfrm4_policy_afinfo</a>);
<a name="L319" href="source/net/ipv4/xfrm4_policy.c#L319">319</a> }
<a name="L320" href="source/net/ipv4/xfrm4_policy.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/xfrm4_policy.c#L321">321</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=xfrm4_init">xfrm4_init</a>(void)
<a name="L322" href="source/net/ipv4/xfrm4_policy.c#L322">322</a> {
<a name="L323" href="source/net/ipv4/xfrm4_policy.c#L323">323</a>         <a href="ident?i=dst_entries_init">dst_entries_init</a>(&amp;<a href="ident?i=xfrm4_dst_ops">xfrm4_dst_ops</a>);
<a name="L324" href="source/net/ipv4/xfrm4_policy.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/xfrm4_policy.c#L325">325</a>         <a href="ident?i=xfrm4_state_init">xfrm4_state_init</a>();
<a name="L326" href="source/net/ipv4/xfrm4_policy.c#L326">326</a>         <a href="ident?i=xfrm4_policy_init">xfrm4_policy_init</a>();
<a name="L327" href="source/net/ipv4/xfrm4_policy.c#L327">327</a>         <a href="ident?i=xfrm4_protocol_init">xfrm4_protocol_init</a>();
<a name="L328" href="source/net/ipv4/xfrm4_policy.c#L328">328</a> #ifdef CONFIG_SYSCTL
<a name="L329" href="source/net/ipv4/xfrm4_policy.c#L329">329</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=xfrm4_net_ops">xfrm4_net_ops</a>);
<a name="L330" href="source/net/ipv4/xfrm4_policy.c#L330">330</a> #endif
<a name="L331" href="source/net/ipv4/xfrm4_policy.c#L331">331</a> }
<a name="L332" href="source/net/ipv4/xfrm4_policy.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/xfrm4_policy.c#L333">333</a> </pre></div><p>
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
