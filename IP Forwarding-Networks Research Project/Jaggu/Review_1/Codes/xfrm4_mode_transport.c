<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_mode_transport.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_mode_transport.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_mode_transport.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_mode_transport.c">xfrm4_mode_transport.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_mode_transport.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_mode_transport.c#L2">2</a> <b><i> * xfrm4_mode_transport.c - Transport mode encapsulation for IPv4.</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_mode_transport.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_mode_transport.c#L4">4</a> <b><i> * Copyright (c) 2004-2006 Herbert Xu &lt;herbert@gondor.apana.org.au&gt;</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_mode_transport.c#L5">5</a> <b><i> */</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_mode_transport.c#L6">6</a> 
  <a name="L7" href="source/net/ipv4/xfrm4_mode_transport.c#L7">7</a> #include &lt;linux/init.h&gt;
  <a name="L8" href="source/net/ipv4/xfrm4_mode_transport.c#L8">8</a> #include &lt;linux/kernel.h&gt;
  <a name="L9" href="source/net/ipv4/xfrm4_mode_transport.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/xfrm4_mode_transport.c#L10">10</a> #include &lt;linux/skbuff.h&gt;
 <a name="L11" href="source/net/ipv4/xfrm4_mode_transport.c#L11">11</a> #include &lt;linux/stringify.h&gt;
 <a name="L12" href="source/net/ipv4/xfrm4_mode_transport.c#L12">12</a> #include &lt;net/dst.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_mode_transport.c#L13">13</a> #include &lt;net/ip.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_mode_transport.c#L14">14</a> #include &lt;net/xfrm.h&gt;
 <a name="L15" href="source/net/ipv4/xfrm4_mode_transport.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/xfrm4_mode_transport.c#L16">16</a> <b><i>/* Add encapsulation header.</i></b>
 <a name="L17" href="source/net/ipv4/xfrm4_mode_transport.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/xfrm4_mode_transport.c#L18">18</a> <b><i> * The IP header will be moved forward to make space for the encapsulation</i></b>
 <a name="L19" href="source/net/ipv4/xfrm4_mode_transport.c#L19">19</a> <b><i> * header.</i></b>
 <a name="L20" href="source/net/ipv4/xfrm4_mode_transport.c#L20">20</a> <b><i> */</i></b>
 <a name="L21" href="source/net/ipv4/xfrm4_mode_transport.c#L21">21</a> static int <a href="ident?i=xfrm4_transport_output">xfrm4_transport_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L22" href="source/net/ipv4/xfrm4_mode_transport.c#L22">22</a> {
 <a name="L23" href="source/net/ipv4/xfrm4_mode_transport.c#L23">23</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L24" href="source/net/ipv4/xfrm4_mode_transport.c#L24">24</a>         int ihl = iph-&gt;ihl * 4;
 <a name="L25" href="source/net/ipv4/xfrm4_mode_transport.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/xfrm4_mode_transport.c#L26">26</a>         <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, -<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a>);
 <a name="L27" href="source/net/ipv4/xfrm4_mode_transport.c#L27">27</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mac_header">mac_header</a> = <a href="ident?i=skb">skb</a>-&gt;network_header +
 <a name="L28" href="source/net/ipv4/xfrm4_mode_transport.c#L28">28</a>                           <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=protocol">protocol</a>);
 <a name="L29" href="source/net/ipv4/xfrm4_mode_transport.c#L29">29</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header + ihl;
 <a name="L30" href="source/net/ipv4/xfrm4_mode_transport.c#L30">30</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, ihl);
 <a name="L31" href="source/net/ipv4/xfrm4_mode_transport.c#L31">31</a>         <a href="ident?i=memmove">memmove</a>(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>), iph, ihl);
 <a name="L32" href="source/net/ipv4/xfrm4_mode_transport.c#L32">32</a>         return 0;
 <a name="L33" href="source/net/ipv4/xfrm4_mode_transport.c#L33">33</a> }
 <a name="L34" href="source/net/ipv4/xfrm4_mode_transport.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/xfrm4_mode_transport.c#L35">35</a> <b><i>/* Remove encapsulation header.</i></b>
 <a name="L36" href="source/net/ipv4/xfrm4_mode_transport.c#L36">36</a> <b><i> *</i></b>
 <a name="L37" href="source/net/ipv4/xfrm4_mode_transport.c#L37">37</a> <b><i> * The IP header will be moved over the top of the encapsulation header.</i></b>
 <a name="L38" href="source/net/ipv4/xfrm4_mode_transport.c#L38">38</a> <b><i> *</i></b>
 <a name="L39" href="source/net/ipv4/xfrm4_mode_transport.c#L39">39</a> <b><i> * On entry, skb-&gt;h shall point to where the IP header should be and skb-&gt;nh</i></b>
 <a name="L40" href="source/net/ipv4/xfrm4_mode_transport.c#L40">40</a> <b><i> * shall be set to where the IP header currently is.  skb-&gt;data shall point</i></b>
 <a name="L41" href="source/net/ipv4/xfrm4_mode_transport.c#L41">41</a> <b><i> * to the start of the payload.</i></b>
 <a name="L42" href="source/net/ipv4/xfrm4_mode_transport.c#L42">42</a> <b><i> */</i></b>
 <a name="L43" href="source/net/ipv4/xfrm4_mode_transport.c#L43">43</a> static int <a href="ident?i=xfrm4_transport_input">xfrm4_transport_input</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L44" href="source/net/ipv4/xfrm4_mode_transport.c#L44">44</a> {
 <a name="L45" href="source/net/ipv4/xfrm4_mode_transport.c#L45">45</a>         int ihl = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> - <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L46" href="source/net/ipv4/xfrm4_mode_transport.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/xfrm4_mode_transport.c#L47">47</a>         if (<a href="ident?i=skb">skb</a>-&gt;transport_header != <a href="ident?i=skb">skb</a>-&gt;network_header) {
 <a name="L48" href="source/net/ipv4/xfrm4_mode_transport.c#L48">48</a>                 <a href="ident?i=memmove">memmove</a>(<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>),
 <a name="L49" href="source/net/ipv4/xfrm4_mode_transport.c#L49">49</a>                         <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>), ihl);
 <a name="L50" href="source/net/ipv4/xfrm4_mode_transport.c#L50">50</a>                 <a href="ident?i=skb">skb</a>-&gt;network_header = <a href="ident?i=skb">skb</a>-&gt;transport_header;
 <a name="L51" href="source/net/ipv4/xfrm4_mode_transport.c#L51">51</a>         }
 <a name="L52" href="source/net/ipv4/xfrm4_mode_transport.c#L52">52</a>         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + ihl);
 <a name="L53" href="source/net/ipv4/xfrm4_mode_transport.c#L53">53</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L54" href="source/net/ipv4/xfrm4_mode_transport.c#L54">54</a>         return 0;
 <a name="L55" href="source/net/ipv4/xfrm4_mode_transport.c#L55">55</a> }
 <a name="L56" href="source/net/ipv4/xfrm4_mode_transport.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/xfrm4_mode_transport.c#L57">57</a> static struct <a href="ident?i=xfrm_mode">xfrm_mode</a> <a href="ident?i=xfrm4_transport_mode">xfrm4_transport_mode</a> = {
 <a name="L58" href="source/net/ipv4/xfrm4_mode_transport.c#L58">58</a>         .<a href="ident?i=input">input</a> = <a href="ident?i=xfrm4_transport_input">xfrm4_transport_input</a>,
 <a name="L59" href="source/net/ipv4/xfrm4_mode_transport.c#L59">59</a>         .<a href="ident?i=output">output</a> = <a href="ident?i=xfrm4_transport_output">xfrm4_transport_output</a>,
 <a name="L60" href="source/net/ipv4/xfrm4_mode_transport.c#L60">60</a>         .owner = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L61" href="source/net/ipv4/xfrm4_mode_transport.c#L61">61</a>         .encap = <a href="ident?i=XFRM_MODE_TRANSPORT">XFRM_MODE_TRANSPORT</a>,
 <a name="L62" href="source/net/ipv4/xfrm4_mode_transport.c#L62">62</a> };
 <a name="L63" href="source/net/ipv4/xfrm4_mode_transport.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/xfrm4_mode_transport.c#L64">64</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=xfrm4_transport_init">xfrm4_transport_init</a>(void)
 <a name="L65" href="source/net/ipv4/xfrm4_mode_transport.c#L65">65</a> {
 <a name="L66" href="source/net/ipv4/xfrm4_mode_transport.c#L66">66</a>         return <a href="ident?i=xfrm_register_mode">xfrm_register_mode</a>(&amp;<a href="ident?i=xfrm4_transport_mode">xfrm4_transport_mode</a>, <a href="ident?i=AF_INET">AF_INET</a>);
 <a name="L67" href="source/net/ipv4/xfrm4_mode_transport.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/xfrm4_mode_transport.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/xfrm4_mode_transport.c#L69">69</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=xfrm4_transport_exit">xfrm4_transport_exit</a>(void)
 <a name="L70" href="source/net/ipv4/xfrm4_mode_transport.c#L70">70</a> {
 <a name="L71" href="source/net/ipv4/xfrm4_mode_transport.c#L71">71</a>         int <a href="ident?i=err">err</a>;
 <a name="L72" href="source/net/ipv4/xfrm4_mode_transport.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/xfrm4_mode_transport.c#L73">73</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm_unregister_mode">xfrm_unregister_mode</a>(&amp;<a href="ident?i=xfrm4_transport_mode">xfrm4_transport_mode</a>, <a href="ident?i=AF_INET">AF_INET</a>);
 <a name="L74" href="source/net/ipv4/xfrm4_mode_transport.c#L74">74</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=err">err</a>);
 <a name="L75" href="source/net/ipv4/xfrm4_mode_transport.c#L75">75</a> }
 <a name="L76" href="source/net/ipv4/xfrm4_mode_transport.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/xfrm4_mode_transport.c#L77">77</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=xfrm4_transport_init">xfrm4_transport_init</a>);
 <a name="L78" href="source/net/ipv4/xfrm4_mode_transport.c#L78">78</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=xfrm4_transport_exit">xfrm4_transport_exit</a>);
 <a name="L79" href="source/net/ipv4/xfrm4_mode_transport.c#L79">79</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L80" href="source/net/ipv4/xfrm4_mode_transport.c#L80">80</a> <a href="ident?i=MODULE_ALIAS_XFRM_MODE">MODULE_ALIAS_XFRM_MODE</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=XFRM_MODE_TRANSPORT">XFRM_MODE_TRANSPORT</a>);
 <a name="L81" href="source/net/ipv4/xfrm4_mode_transport.c#L81">81</a> </pre></div><p>
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
