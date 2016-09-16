<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_state.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_state.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_state.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_state.c">xfrm4_state.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_state.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_state.c#L2">2</a> <b><i> * xfrm4_state.c</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_state.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_state.c#L4">4</a> <b><i> * Changes:</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_state.c#L5">5</a> <b><i> *      YOSHIFUJI Hideaki @USAGI</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_state.c#L6">6</a> <b><i> *              Split up af-specific portion</i></b>
  <a name="L7" href="source/net/ipv4/xfrm4_state.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/xfrm4_state.c#L8">8</a> <b><i> */</i></b>
  <a name="L9" href="source/net/ipv4/xfrm4_state.c#L9">9</a> 
 <a name="L10" href="source/net/ipv4/xfrm4_state.c#L10">10</a> #include &lt;net/ip.h&gt;
 <a name="L11" href="source/net/ipv4/xfrm4_state.c#L11">11</a> #include &lt;net/xfrm.h&gt;
 <a name="L12" href="source/net/ipv4/xfrm4_state.c#L12">12</a> #include &lt;linux/pfkeyv2.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_state.c#L13">13</a> #include &lt;linux/ipsec.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_state.c#L14">14</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L15" href="source/net/ipv4/xfrm4_state.c#L15">15</a> #include &lt;linux/export.h&gt;
 <a name="L16" href="source/net/ipv4/xfrm4_state.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/xfrm4_state.c#L17">17</a> static int <a href="ident?i=xfrm4_init_flags">xfrm4_init_flags</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
 <a name="L18" href="source/net/ipv4/xfrm4_state.c#L18">18</a> {
 <a name="L19" href="source/net/ipv4/xfrm4_state.c#L19">19</a>         if (<a href="ident?i=xs_net">xs_net</a>(<a href="ident?i=x">x</a>)-&gt;ipv4.sysctl_ip_no_pmtu_disc)
 <a name="L20" href="source/net/ipv4/xfrm4_state.c#L20">20</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> |= <a href="ident?i=XFRM_STATE_NOPMTUDISC">XFRM_STATE_NOPMTUDISC</a>;
 <a name="L21" href="source/net/ipv4/xfrm4_state.c#L21">21</a>         return 0;
 <a name="L22" href="source/net/ipv4/xfrm4_state.c#L22">22</a> }
 <a name="L23" href="source/net/ipv4/xfrm4_state.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/xfrm4_state.c#L24">24</a> static void
 <a name="L25" href="source/net/ipv4/xfrm4_state.c#L25">25</a> <a href="ident?i=__xfrm4_init_tempsel">__xfrm4_init_tempsel</a>(struct <a href="ident?i=xfrm_selector">xfrm_selector</a> *sel, const struct <a href="ident?i=flowi">flowi</a> *fl)
 <a name="L26" href="source/net/ipv4/xfrm4_state.c#L26">26</a> {
 <a name="L27" href="source/net/ipv4/xfrm4_state.c#L27">27</a>         const struct <a href="ident?i=flowi4">flowi4</a> *fl4 = &amp;fl-&gt;u.ip4;
 <a name="L28" href="source/net/ipv4/xfrm4_state.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/xfrm4_state.c#L29">29</a>         sel-&gt;<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a> = fl4-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L30" href="source/net/ipv4/xfrm4_state.c#L30">30</a>         sel-&gt;<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L31" href="source/net/ipv4/xfrm4_state.c#L31">31</a>         sel-&gt;dport = <a href="ident?i=xfrm_flowi_dport">xfrm_flowi_dport</a>(fl, &amp;fl4-&gt;uli);
 <a name="L32" href="source/net/ipv4/xfrm4_state.c#L32">32</a>         sel-&gt;dport_mask = <a href="ident?i=htons">htons</a>(0xffff);
 <a name="L33" href="source/net/ipv4/xfrm4_state.c#L33">33</a>         sel-&gt;sport = <a href="ident?i=xfrm_flowi_sport">xfrm_flowi_sport</a>(fl, &amp;fl4-&gt;uli);
 <a name="L34" href="source/net/ipv4/xfrm4_state.c#L34">34</a>         sel-&gt;sport_mask = <a href="ident?i=htons">htons</a>(0xffff);
 <a name="L35" href="source/net/ipv4/xfrm4_state.c#L35">35</a>         sel-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L36" href="source/net/ipv4/xfrm4_state.c#L36">36</a>         sel-&gt;prefixlen_d = 32;
 <a name="L37" href="source/net/ipv4/xfrm4_state.c#L37">37</a>         sel-&gt;prefixlen_s = 32;
 <a name="L38" href="source/net/ipv4/xfrm4_state.c#L38">38</a>         sel-&gt;<a href="ident?i=proto">proto</a> = fl4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a>;
 <a name="L39" href="source/net/ipv4/xfrm4_state.c#L39">39</a>         sel-&gt;ifindex = fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a>;
 <a name="L40" href="source/net/ipv4/xfrm4_state.c#L40">40</a> }
 <a name="L41" href="source/net/ipv4/xfrm4_state.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/xfrm4_state.c#L42">42</a> static void
 <a name="L43" href="source/net/ipv4/xfrm4_state.c#L43">43</a> <a href="ident?i=xfrm4_init_temprop">xfrm4_init_temprop</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, const struct <a href="ident?i=xfrm_tmpl">xfrm_tmpl</a> *tmpl,
 <a name="L44" href="source/net/ipv4/xfrm4_state.c#L44">44</a>                    const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=daddr">daddr</a>, const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *<a href="ident?i=saddr">saddr</a>)
 <a name="L45" href="source/net/ipv4/xfrm4_state.c#L45">45</a> {
 <a name="L46" href="source/net/ipv4/xfrm4_state.c#L46">46</a>         <a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a> = tmpl-&gt;<a href="ident?i=id">id</a>;
 <a name="L47" href="source/net/ipv4/xfrm4_state.c#L47">47</a>         if (<a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a> == 0)
 <a name="L48" href="source/net/ipv4/xfrm4_state.c#L48">48</a>                 <a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=daddr">daddr</a>-&gt;<a href="ident?i=a4">a4</a>;
 <a name="L49" href="source/net/ipv4/xfrm4_state.c#L49">49</a>         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a> = tmpl-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L50" href="source/net/ipv4/xfrm4_state.c#L50">50</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a> == 0)
 <a name="L51" href="source/net/ipv4/xfrm4_state.c#L51">51</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=saddr">saddr</a>-&gt;<a href="ident?i=a4">a4</a>;
 <a name="L52" href="source/net/ipv4/xfrm4_state.c#L52">52</a>         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> = tmpl-&gt;<a href="ident?i=mode">mode</a>;
 <a name="L53" href="source/net/ipv4/xfrm4_state.c#L53">53</a>         <a href="ident?i=x">x</a>-&gt;props.reqid = tmpl-&gt;reqid;
 <a name="L54" href="source/net/ipv4/xfrm4_state.c#L54">54</a>         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L55" href="source/net/ipv4/xfrm4_state.c#L55">55</a> }
 <a name="L56" href="source/net/ipv4/xfrm4_state.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/xfrm4_state.c#L57">57</a> int <a href="ident?i=xfrm4_extract_header">xfrm4_extract_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L58" href="source/net/ipv4/xfrm4_state.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/xfrm4_state.c#L59">59</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L60" href="source/net/ipv4/xfrm4_state.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/xfrm4_state.c#L61">61</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ihl = sizeof(*iph);
 <a name="L62" href="source/net/ipv4/xfrm4_state.c#L62">62</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=id">id</a> = iph-&gt;<a href="ident?i=id">id</a>;
 <a name="L63" href="source/net/ipv4/xfrm4_state.c#L63">63</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_off = iph-&gt;frag_off;
 <a name="L64" href="source/net/ipv4/xfrm4_state.c#L64">64</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tos = iph-&gt;tos;
 <a name="L65" href="source/net/ipv4/xfrm4_state.c#L65">65</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a> = iph-&gt;<a href="ident?i=ttl">ttl</a>;
 <a name="L66" href="source/net/ipv4/xfrm4_state.c#L66">66</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=optlen">optlen</a> = iph-&gt;ihl * 4 - sizeof(*iph);
 <a name="L67" href="source/net/ipv4/xfrm4_state.c#L67">67</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;flow_lbl, 0,
 <a name="L68" href="source/net/ipv4/xfrm4_state.c#L68">68</a>                sizeof(<a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;flow_lbl));
 <a name="L69" href="source/net/ipv4/xfrm4_state.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/xfrm4_state.c#L70">70</a>         return 0;
 <a name="L71" href="source/net/ipv4/xfrm4_state.c#L71">71</a> }
 <a name="L72" href="source/net/ipv4/xfrm4_state.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/xfrm4_state.c#L73">73</a> static struct <a href="ident?i=xfrm_state_afinfo">xfrm_state_afinfo</a> <a href="ident?i=xfrm4_state_afinfo">xfrm4_state_afinfo</a> = {
 <a name="L74" href="source/net/ipv4/xfrm4_state.c#L74">74</a>         .<a href="ident?i=family">family</a>                 = <a href="ident?i=AF_INET">AF_INET</a>,
 <a name="L75" href="source/net/ipv4/xfrm4_state.c#L75">75</a>         .<a href="ident?i=proto">proto</a>                  = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>,
 <a name="L76" href="source/net/ipv4/xfrm4_state.c#L76">76</a>         .eth_proto              = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>),
 <a name="L77" href="source/net/ipv4/xfrm4_state.c#L77">77</a>         .owner                  = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L78" href="source/net/ipv4/xfrm4_state.c#L78">78</a>         .init_flags             = <a href="ident?i=xfrm4_init_flags">xfrm4_init_flags</a>,
 <a name="L79" href="source/net/ipv4/xfrm4_state.c#L79">79</a>         .init_tempsel           = <a href="ident?i=__xfrm4_init_tempsel">__xfrm4_init_tempsel</a>,
 <a name="L80" href="source/net/ipv4/xfrm4_state.c#L80">80</a>         .init_temprop           = <a href="ident?i=xfrm4_init_temprop">xfrm4_init_temprop</a>,
 <a name="L81" href="source/net/ipv4/xfrm4_state.c#L81">81</a>         .<a href="ident?i=output">output</a>                 = <a href="ident?i=xfrm4_output">xfrm4_output</a>,
 <a name="L82" href="source/net/ipv4/xfrm4_state.c#L82">82</a>         .output_finish          = <a href="ident?i=xfrm4_output_finish">xfrm4_output_finish</a>,
 <a name="L83" href="source/net/ipv4/xfrm4_state.c#L83">83</a>         .extract_input          = <a href="ident?i=xfrm4_extract_input">xfrm4_extract_input</a>,
 <a name="L84" href="source/net/ipv4/xfrm4_state.c#L84">84</a>         .extract_output         = <a href="ident?i=xfrm4_extract_output">xfrm4_extract_output</a>,
 <a name="L85" href="source/net/ipv4/xfrm4_state.c#L85">85</a>         .transport_finish       = <a href="ident?i=xfrm4_transport_finish">xfrm4_transport_finish</a>,
 <a name="L86" href="source/net/ipv4/xfrm4_state.c#L86">86</a>         .local_error            = <a href="ident?i=xfrm4_local_error">xfrm4_local_error</a>,
 <a name="L87" href="source/net/ipv4/xfrm4_state.c#L87">87</a> };
 <a name="L88" href="source/net/ipv4/xfrm4_state.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/xfrm4_state.c#L89">89</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=xfrm4_state_init">xfrm4_state_init</a>(void)
 <a name="L90" href="source/net/ipv4/xfrm4_state.c#L90">90</a> {
 <a name="L91" href="source/net/ipv4/xfrm4_state.c#L91">91</a>         <a href="ident?i=xfrm_state_register_afinfo">xfrm_state_register_afinfo</a>(&amp;<a href="ident?i=xfrm4_state_afinfo">xfrm4_state_afinfo</a>);
 <a name="L92" href="source/net/ipv4/xfrm4_state.c#L92">92</a> }
 <a name="L93" href="source/net/ipv4/xfrm4_state.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/xfrm4_state.c#L94">94</a> #if 0
 <a name="L95" href="source/net/ipv4/xfrm4_state.c#L95">95</a> void <a href="ident?i=__exit">__exit</a> <a href="ident?i=xfrm4_state_fini">xfrm4_state_fini</a>(void)
 <a name="L96" href="source/net/ipv4/xfrm4_state.c#L96">96</a> {
 <a name="L97" href="source/net/ipv4/xfrm4_state.c#L97">97</a>         <a href="ident?i=xfrm_state_unregister_afinfo">xfrm_state_unregister_afinfo</a>(&amp;<a href="ident?i=xfrm4_state_afinfo">xfrm4_state_afinfo</a>);
 <a name="L98" href="source/net/ipv4/xfrm4_state.c#L98">98</a> }
 <a name="L99" href="source/net/ipv4/xfrm4_state.c#L99">99</a> #endif  <b><i>/*  0  */</i></b>
<a name="L100" href="source/net/ipv4/xfrm4_state.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/xfrm4_state.c#L101">101</a> </pre></div><p>
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
