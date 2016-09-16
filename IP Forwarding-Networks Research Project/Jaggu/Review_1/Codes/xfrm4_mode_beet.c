<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_mode_beet.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_mode_beet.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_beet.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_mode_beet.c">xfrm4_mode_beet.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_mode_beet.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_mode_beet.c#L2">2</a> <b><i> * xfrm4_mode_beet.c - BEET mode encapsulation for IPv4.</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_mode_beet.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_mode_beet.c#L4">4</a> <b><i> * Copyright (c) 2006 Diego Beltrami &lt;diego.beltrami@gmail.com&gt;</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_mode_beet.c#L5">5</a> <b><i> *                    Miika Komu     &lt;miika@iki.fi&gt;</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_mode_beet.c#L6">6</a> <b><i> *                    Herbert Xu     &lt;herbert@gondor.apana.org.au&gt;</i></b>
  <a name="L7" href="source/net/ipv4/xfrm4_mode_beet.c#L7">7</a> <b><i> *                    Abhinav Pathak &lt;abhinav.pathak@hiit.fi&gt;</i></b>
  <a name="L8" href="source/net/ipv4/xfrm4_mode_beet.c#L8">8</a> <b><i> *                    Jeff Ahrenholz &lt;ahrenholz@gmail.com&gt;</i></b>
  <a name="L9" href="source/net/ipv4/xfrm4_mode_beet.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/xfrm4_mode_beet.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/xfrm4_mode_beet.c#L11">11</a> #include &lt;linux/init.h&gt;
 <a name="L12" href="source/net/ipv4/xfrm4_mode_beet.c#L12">12</a> #include &lt;linux/kernel.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_mode_beet.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_mode_beet.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/xfrm4_mode_beet.c#L15">15</a> #include &lt;linux/stringify.h&gt;
 <a name="L16" href="source/net/ipv4/xfrm4_mode_beet.c#L16">16</a> #include &lt;net/dst.h&gt;
 <a name="L17" href="source/net/ipv4/xfrm4_mode_beet.c#L17">17</a> #include &lt;net/ip.h&gt;
 <a name="L18" href="source/net/ipv4/xfrm4_mode_beet.c#L18">18</a> #include &lt;net/xfrm.h&gt;
 <a name="L19" href="source/net/ipv4/xfrm4_mode_beet.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/xfrm4_mode_beet.c#L20">20</a> static void <a href="ident?i=xfrm4_beet_make_header">xfrm4_beet_make_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L21" href="source/net/ipv4/xfrm4_mode_beet.c#L21">21</a> {
 <a name="L22" href="source/net/ipv4/xfrm4_mode_beet.c#L22">22</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L23" href="source/net/ipv4/xfrm4_mode_beet.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/xfrm4_mode_beet.c#L24">24</a>         iph-&gt;ihl = 5;
 <a name="L25" href="source/net/ipv4/xfrm4_mode_beet.c#L25">25</a>         iph-&gt;<a href="ident?i=version">version</a> = 4;
 <a name="L26" href="source/net/ipv4/xfrm4_mode_beet.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/xfrm4_mode_beet.c#L27">27</a>         iph-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L28" href="source/net/ipv4/xfrm4_mode_beet.c#L28">28</a>         iph-&gt;tos = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tos;
 <a name="L29" href="source/net/ipv4/xfrm4_mode_beet.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/xfrm4_mode_beet.c#L30">30</a>         iph-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=id">id</a>;
 <a name="L31" href="source/net/ipv4/xfrm4_mode_beet.c#L31">31</a>         iph-&gt;frag_off = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_off;
 <a name="L32" href="source/net/ipv4/xfrm4_mode_beet.c#L32">32</a>         iph-&gt;<a href="ident?i=ttl">ttl</a> = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a>;
 <a name="L33" href="source/net/ipv4/xfrm4_mode_beet.c#L33">33</a> }
 <a name="L34" href="source/net/ipv4/xfrm4_mode_beet.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/xfrm4_mode_beet.c#L35">35</a> <b><i>/* Add encapsulation header.</i></b>
 <a name="L36" href="source/net/ipv4/xfrm4_mode_beet.c#L36">36</a> <b><i> *</i></b>
 <a name="L37" href="source/net/ipv4/xfrm4_mode_beet.c#L37">37</a> <b><i> * The top IP header will be constructed per draft-nikander-esp-beet-mode-06.txt.</i></b>
 <a name="L38" href="source/net/ipv4/xfrm4_mode_beet.c#L38">38</a> <b><i> */</i></b>
 <a name="L39" href="source/net/ipv4/xfrm4_mode_beet.c#L39">39</a> static int <a href="ident?i=xfrm4_beet_output">xfrm4_beet_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L40" href="source/net/ipv4/xfrm4_mode_beet.c#L40">40</a> {
 <a name="L41" href="source/net/ipv4/xfrm4_mode_beet.c#L41">41</a>         struct <a href="ident?i=ip_beet_phdr">ip_beet_phdr</a> *ph;
 <a name="L42" href="source/net/ipv4/xfrm4_mode_beet.c#L42">42</a>         struct <a href="ident?i=iphdr">iphdr</a> *top_iph;
 <a name="L43" href="source/net/ipv4/xfrm4_mode_beet.c#L43">43</a>         int hdrlen, <a href="ident?i=optlen">optlen</a>;
 <a name="L44" href="source/net/ipv4/xfrm4_mode_beet.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/xfrm4_mode_beet.c#L45">45</a>         hdrlen = 0;
 <a name="L46" href="source/net/ipv4/xfrm4_mode_beet.c#L46">46</a>         <a href="ident?i=optlen">optlen</a> = <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=optlen">optlen</a>;
 <a name="L47" href="source/net/ipv4/xfrm4_mode_beet.c#L47">47</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=optlen">optlen</a>))
 <a name="L48" href="source/net/ipv4/xfrm4_mode_beet.c#L48">48</a>                 hdrlen += <a href="ident?i=IPV4_BEET_PHMAXLEN">IPV4_BEET_PHMAXLEN</a> - (<a href="ident?i=optlen">optlen</a> &amp; 4);
 <a name="L49" href="source/net/ipv4/xfrm4_mode_beet.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/xfrm4_mode_beet.c#L50">50</a>         <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, -<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> -
 <a name="L51" href="source/net/ipv4/xfrm4_mode_beet.c#L51">51</a>                                     hdrlen + (<a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ihl - sizeof(*top_iph)));
 <a name="L52" href="source/net/ipv4/xfrm4_mode_beet.c#L52">52</a>         if (<a href="ident?i=x">x</a>-&gt;sel.<a href="ident?i=family">family</a> != <a href="ident?i=AF_INET6">AF_INET6</a>)
 <a name="L53" href="source/net/ipv4/xfrm4_mode_beet.c#L53">53</a>                 <a href="ident?i=skb">skb</a>-&gt;network_header += <a href="ident?i=IPV4_BEET_PHMAXLEN">IPV4_BEET_PHMAXLEN</a>;
 <a name="L54" href="source/net/ipv4/xfrm4_mode_beet.c#L54">54</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mac_header">mac_header</a> = <a href="ident?i=skb">skb</a>-&gt;network_header +
 <a name="L55" href="source/net/ipv4/xfrm4_mode_beet.c#L55">55</a>                           <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=protocol">protocol</a>);
 <a name="L56" href="source/net/ipv4/xfrm4_mode_beet.c#L56">56</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header + sizeof(*top_iph);
 <a name="L57" href="source/net/ipv4/xfrm4_mode_beet.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/xfrm4_mode_beet.c#L58">58</a>         <a href="ident?i=xfrm4_beet_make_header">xfrm4_beet_make_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L59" href="source/net/ipv4/xfrm4_mode_beet.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/xfrm4_mode_beet.c#L60">60</a>         ph = (struct <a href="ident?i=ip_beet_phdr">ip_beet_phdr</a> *)
 <a name="L61" href="source/net/ipv4/xfrm4_mode_beet.c#L61">61</a>                 <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ihl - hdrlen);
 <a name="L62" href="source/net/ipv4/xfrm4_mode_beet.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/xfrm4_mode_beet.c#L63">63</a>         top_iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L64" href="source/net/ipv4/xfrm4_mode_beet.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/xfrm4_mode_beet.c#L65">65</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=optlen">optlen</a>)) {
 <a name="L66" href="source/net/ipv4/xfrm4_mode_beet.c#L66">66</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=optlen">optlen</a> &lt; 0);
 <a name="L67" href="source/net/ipv4/xfrm4_mode_beet.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/xfrm4_mode_beet.c#L68">68</a>                 ph-&gt;padlen = 4 - (<a href="ident?i=optlen">optlen</a> &amp; 4);
 <a name="L69" href="source/net/ipv4/xfrm4_mode_beet.c#L69">69</a>                 ph-&gt;hdrlen = <a href="ident?i=optlen">optlen</a> / 8;
 <a name="L70" href="source/net/ipv4/xfrm4_mode_beet.c#L70">70</a>                 ph-&gt;nexthdr = top_iph-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L71" href="source/net/ipv4/xfrm4_mode_beet.c#L71">71</a>                 if (ph-&gt;padlen)
 <a name="L72" href="source/net/ipv4/xfrm4_mode_beet.c#L72">72</a>                         <a href="ident?i=memset">memset</a>(ph + 1, <a href="ident?i=IPOPT_NOP">IPOPT_NOP</a>, ph-&gt;padlen);
 <a name="L73" href="source/net/ipv4/xfrm4_mode_beet.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/xfrm4_mode_beet.c#L74">74</a>                 top_iph-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_BEETPH">IPPROTO_BEETPH</a>;
 <a name="L75" href="source/net/ipv4/xfrm4_mode_beet.c#L75">75</a>                 top_iph-&gt;ihl = sizeof(struct <a href="ident?i=iphdr">iphdr</a>) / 4;
 <a name="L76" href="source/net/ipv4/xfrm4_mode_beet.c#L76">76</a>         }
 <a name="L77" href="source/net/ipv4/xfrm4_mode_beet.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/xfrm4_mode_beet.c#L78">78</a>         top_iph-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a>;
 <a name="L79" href="source/net/ipv4/xfrm4_mode_beet.c#L79">79</a>         top_iph-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a>;
 <a name="L80" href="source/net/ipv4/xfrm4_mode_beet.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/xfrm4_mode_beet.c#L81">81</a>         return 0;
 <a name="L82" href="source/net/ipv4/xfrm4_mode_beet.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/xfrm4_mode_beet.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/xfrm4_mode_beet.c#L84">84</a> static int <a href="ident?i=xfrm4_beet_input">xfrm4_beet_input</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L85" href="source/net/ipv4/xfrm4_mode_beet.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/xfrm4_mode_beet.c#L86">86</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L87" href="source/net/ipv4/xfrm4_mode_beet.c#L87">87</a>         int <a href="ident?i=optlen">optlen</a> = 0;
 <a name="L88" href="source/net/ipv4/xfrm4_mode_beet.c#L88">88</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L89" href="source/net/ipv4/xfrm4_mode_beet.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/xfrm4_mode_beet.c#L90">90</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_BEETPH">IPPROTO_BEETPH</a>)) {
 <a name="L91" href="source/net/ipv4/xfrm4_mode_beet.c#L91">91</a>                 struct <a href="ident?i=ip_beet_phdr">ip_beet_phdr</a> *ph;
 <a name="L92" href="source/net/ipv4/xfrm4_mode_beet.c#L92">92</a>                 int phlen;
 <a name="L93" href="source/net/ipv4/xfrm4_mode_beet.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/xfrm4_mode_beet.c#L94">94</a>                 if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*ph)))
 <a name="L95" href="source/net/ipv4/xfrm4_mode_beet.c#L95">95</a>                         goto <a href="ident?i=out">out</a>;
 <a name="L96" href="source/net/ipv4/xfrm4_mode_beet.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/xfrm4_mode_beet.c#L97">97</a>                 ph = (struct <a href="ident?i=ip_beet_phdr">ip_beet_phdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
 <a name="L98" href="source/net/ipv4/xfrm4_mode_beet.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/xfrm4_mode_beet.c#L99">99</a>                 phlen = sizeof(*ph) + ph-&gt;padlen;
<a name="L100" href="source/net/ipv4/xfrm4_mode_beet.c#L100">100</a>                 <a href="ident?i=optlen">optlen</a> = ph-&gt;hdrlen * 8 + (<a href="ident?i=IPV4_BEET_PHMAXLEN">IPV4_BEET_PHMAXLEN</a> - phlen);
<a name="L101" href="source/net/ipv4/xfrm4_mode_beet.c#L101">101</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 0 || <a href="ident?i=optlen">optlen</a> &amp; 3 || <a href="ident?i=optlen">optlen</a> &gt; 250)
<a name="L102" href="source/net/ipv4/xfrm4_mode_beet.c#L102">102</a>                         goto <a href="ident?i=out">out</a>;
<a name="L103" href="source/net/ipv4/xfrm4_mode_beet.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/xfrm4_mode_beet.c#L104">104</a>                 <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> = ph-&gt;nexthdr;
<a name="L105" href="source/net/ipv4/xfrm4_mode_beet.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/xfrm4_mode_beet.c#L106">106</a>                 if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, phlen))
<a name="L107" href="source/net/ipv4/xfrm4_mode_beet.c#L107">107</a>                         goto <a href="ident?i=out">out</a>;
<a name="L108" href="source/net/ipv4/xfrm4_mode_beet.c#L108">108</a>                 <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, phlen);
<a name="L109" href="source/net/ipv4/xfrm4_mode_beet.c#L109">109</a>         }
<a name="L110" href="source/net/ipv4/xfrm4_mode_beet.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/xfrm4_mode_beet.c#L111">111</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(*iph));
<a name="L112" href="source/net/ipv4/xfrm4_mode_beet.c#L112">112</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L113" href="source/net/ipv4/xfrm4_mode_beet.c#L113">113</a>         <a href="ident?i=skb_mac_header_rebuild">skb_mac_header_rebuild</a>(<a href="ident?i=skb">skb</a>);
<a name="L114" href="source/net/ipv4/xfrm4_mode_beet.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/xfrm4_mode_beet.c#L115">115</a>         <a href="ident?i=xfrm4_beet_make_header">xfrm4_beet_make_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L116" href="source/net/ipv4/xfrm4_mode_beet.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/xfrm4_mode_beet.c#L117">117</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L118" href="source/net/ipv4/xfrm4_mode_beet.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/xfrm4_mode_beet.c#L119">119</a>         iph-&gt;ihl += <a href="ident?i=optlen">optlen</a> / 4;
<a name="L120" href="source/net/ipv4/xfrm4_mode_beet.c#L120">120</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L121" href="source/net/ipv4/xfrm4_mode_beet.c#L121">121</a>         iph-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=x">x</a>-&gt;sel.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a>;
<a name="L122" href="source/net/ipv4/xfrm4_mode_beet.c#L122">122</a>         iph-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=x">x</a>-&gt;sel.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a>;
<a name="L123" href="source/net/ipv4/xfrm4_mode_beet.c#L123">123</a>         iph-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L124" href="source/net/ipv4/xfrm4_mode_beet.c#L124">124</a>         iph-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=ip_fast_csum">ip_fast_csum</a>(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>), iph-&gt;ihl);
<a name="L125" href="source/net/ipv4/xfrm4_mode_beet.c#L125">125</a>         <a href="ident?i=err">err</a> = 0;
<a name="L126" href="source/net/ipv4/xfrm4_mode_beet.c#L126">126</a> <a href="ident?i=out">out</a>:
<a name="L127" href="source/net/ipv4/xfrm4_mode_beet.c#L127">127</a>         return <a href="ident?i=err">err</a>;
<a name="L128" href="source/net/ipv4/xfrm4_mode_beet.c#L128">128</a> }
<a name="L129" href="source/net/ipv4/xfrm4_mode_beet.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/xfrm4_mode_beet.c#L130">130</a> static struct <a href="ident?i=xfrm_mode">xfrm_mode</a> <a href="ident?i=xfrm4_beet_mode">xfrm4_beet_mode</a> = {
<a name="L131" href="source/net/ipv4/xfrm4_mode_beet.c#L131">131</a>         .input2 = <a href="ident?i=xfrm4_beet_input">xfrm4_beet_input</a>,
<a name="L132" href="source/net/ipv4/xfrm4_mode_beet.c#L132">132</a>         .<a href="ident?i=input">input</a> = <a href="ident?i=xfrm_prepare_input">xfrm_prepare_input</a>,
<a name="L133" href="source/net/ipv4/xfrm4_mode_beet.c#L133">133</a>         .output2 = <a href="ident?i=xfrm4_beet_output">xfrm4_beet_output</a>,
<a name="L134" href="source/net/ipv4/xfrm4_mode_beet.c#L134">134</a>         .<a href="ident?i=output">output</a> = <a href="ident?i=xfrm4_prepare_output">xfrm4_prepare_output</a>,
<a name="L135" href="source/net/ipv4/xfrm4_mode_beet.c#L135">135</a>         .owner = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L136" href="source/net/ipv4/xfrm4_mode_beet.c#L136">136</a>         .encap = <a href="ident?i=XFRM_MODE_BEET">XFRM_MODE_BEET</a>,
<a name="L137" href="source/net/ipv4/xfrm4_mode_beet.c#L137">137</a>         .<a href="ident?i=flags">flags</a> = XFRM_MODE_FLAG_TUNNEL,
<a name="L138" href="source/net/ipv4/xfrm4_mode_beet.c#L138">138</a> };
<a name="L139" href="source/net/ipv4/xfrm4_mode_beet.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/xfrm4_mode_beet.c#L140">140</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=xfrm4_beet_init">xfrm4_beet_init</a>(void)
<a name="L141" href="source/net/ipv4/xfrm4_mode_beet.c#L141">141</a> {
<a name="L142" href="source/net/ipv4/xfrm4_mode_beet.c#L142">142</a>         return <a href="ident?i=xfrm_register_mode">xfrm_register_mode</a>(&amp;<a href="ident?i=xfrm4_beet_mode">xfrm4_beet_mode</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L143" href="source/net/ipv4/xfrm4_mode_beet.c#L143">143</a> }
<a name="L144" href="source/net/ipv4/xfrm4_mode_beet.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/xfrm4_mode_beet.c#L145">145</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=xfrm4_beet_exit">xfrm4_beet_exit</a>(void)
<a name="L146" href="source/net/ipv4/xfrm4_mode_beet.c#L146">146</a> {
<a name="L147" href="source/net/ipv4/xfrm4_mode_beet.c#L147">147</a>         int <a href="ident?i=err">err</a>;
<a name="L148" href="source/net/ipv4/xfrm4_mode_beet.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/xfrm4_mode_beet.c#L149">149</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm_unregister_mode">xfrm_unregister_mode</a>(&amp;<a href="ident?i=xfrm4_beet_mode">xfrm4_beet_mode</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L150" href="source/net/ipv4/xfrm4_mode_beet.c#L150">150</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=err">err</a>);
<a name="L151" href="source/net/ipv4/xfrm4_mode_beet.c#L151">151</a> }
<a name="L152" href="source/net/ipv4/xfrm4_mode_beet.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/xfrm4_mode_beet.c#L153">153</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=xfrm4_beet_init">xfrm4_beet_init</a>);
<a name="L154" href="source/net/ipv4/xfrm4_mode_beet.c#L154">154</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=xfrm4_beet_exit">xfrm4_beet_exit</a>);
<a name="L155" href="source/net/ipv4/xfrm4_mode_beet.c#L155">155</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L156" href="source/net/ipv4/xfrm4_mode_beet.c#L156">156</a> <a href="ident?i=MODULE_ALIAS_XFRM_MODE">MODULE_ALIAS_XFRM_MODE</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=XFRM_MODE_BEET">XFRM_MODE_BEET</a>);
<a name="L157" href="source/net/ipv4/xfrm4_mode_beet.c#L157">157</a> </pre></div><p>
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
