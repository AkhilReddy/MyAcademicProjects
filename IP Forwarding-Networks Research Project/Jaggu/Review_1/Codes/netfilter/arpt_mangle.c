<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/arpt_mangle.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/arpt_mangle.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/arpt_mangle.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/arpt_mangle.c">arpt_mangle.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/arpt_mangle.c#L1">1</a> <b><i>/* module that allows mangling of the arp payload */</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/arpt_mangle.c#L2">2</a> #include &lt;linux/module.h&gt;
  <a name="L3" href="source/net/ipv4/netfilter/arpt_mangle.c#L3">3</a> #include &lt;linux/netfilter.h&gt;
  <a name="L4" href="source/net/ipv4/netfilter/arpt_mangle.c#L4">4</a> #include &lt;linux/netfilter_arp/arpt_mangle.h&gt;
  <a name="L5" href="source/net/ipv4/netfilter/arpt_mangle.c#L5">5</a> #include &lt;net/sock.h&gt;
  <a name="L6" href="source/net/ipv4/netfilter/arpt_mangle.c#L6">6</a> 
  <a name="L7" href="source/net/ipv4/netfilter/arpt_mangle.c#L7">7</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
  <a name="L8" href="source/net/ipv4/netfilter/arpt_mangle.c#L8">8</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Bart De Schuymer &lt;bdschuym@pandora.be&gt;"</i>);
  <a name="L9" href="source/net/ipv4/netfilter/arpt_mangle.c#L9">9</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"arptables arp payload mangle target"</i>);
 <a name="L10" href="source/net/ipv4/netfilter/arpt_mangle.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/netfilter/arpt_mangle.c#L11">11</a> static unsigned int
 <a name="L12" href="source/net/ipv4/netfilter/arpt_mangle.c#L12">12</a> <a href="ident?i=target">target</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
 <a name="L13" href="source/net/ipv4/netfilter/arpt_mangle.c#L13">13</a> {
 <a name="L14" href="source/net/ipv4/netfilter/arpt_mangle.c#L14">14</a>         const struct <a href="ident?i=arpt_mangle">arpt_mangle</a> *<a href="ident?i=mangle">mangle</a> = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L15" href="source/net/ipv4/netfilter/arpt_mangle.c#L15">15</a>         const struct <a href="ident?i=arphdr">arphdr</a> *arp;
 <a name="L16" href="source/net/ipv4/netfilter/arpt_mangle.c#L16">16</a>         unsigned char *arpptr;
 <a name="L17" href="source/net/ipv4/netfilter/arpt_mangle.c#L17">17</a>         int pln, hln;
 <a name="L18" href="source/net/ipv4/netfilter/arpt_mangle.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/netfilter/arpt_mangle.c#L19">19</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>))
 <a name="L20" href="source/net/ipv4/netfilter/arpt_mangle.c#L20">20</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L21" href="source/net/ipv4/netfilter/arpt_mangle.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/netfilter/arpt_mangle.c#L22">22</a>         arp = <a href="ident?i=arp_hdr">arp_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L23" href="source/net/ipv4/netfilter/arpt_mangle.c#L23">23</a>         arpptr = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) + sizeof(*arp);
 <a name="L24" href="source/net/ipv4/netfilter/arpt_mangle.c#L24">24</a>         pln = arp-&gt;ar_pln;
 <a name="L25" href="source/net/ipv4/netfilter/arpt_mangle.c#L25">25</a>         hln = arp-&gt;ar_hln;
 <a name="L26" href="source/net/ipv4/netfilter/arpt_mangle.c#L26">26</a>         <b><i>/* We assume that pln and hln were checked in the match */</i></b>
 <a name="L27" href="source/net/ipv4/netfilter/arpt_mangle.c#L27">27</a>         if (<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=ARPT_MANGLE_SDEV">ARPT_MANGLE_SDEV</a>) {
 <a name="L28" href="source/net/ipv4/netfilter/arpt_mangle.c#L28">28</a>                 if (<a href="ident?i=ARPT_DEV_ADDR_LEN_MAX">ARPT_DEV_ADDR_LEN_MAX</a> &lt; hln ||
 <a name="L29" href="source/net/ipv4/netfilter/arpt_mangle.c#L29">29</a>                    (arpptr + hln &gt; <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>)))
 <a name="L30" href="source/net/ipv4/netfilter/arpt_mangle.c#L30">30</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L31" href="source/net/ipv4/netfilter/arpt_mangle.c#L31">31</a>                 <a href="ident?i=memcpy">memcpy</a>(arpptr, <a href="ident?i=mangle">mangle</a>-&gt;src_devaddr, hln);
 <a name="L32" href="source/net/ipv4/netfilter/arpt_mangle.c#L32">32</a>         }
 <a name="L33" href="source/net/ipv4/netfilter/arpt_mangle.c#L33">33</a>         arpptr += hln;
 <a name="L34" href="source/net/ipv4/netfilter/arpt_mangle.c#L34">34</a>         if (<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=ARPT_MANGLE_SIP">ARPT_MANGLE_SIP</a>) {
 <a name="L35" href="source/net/ipv4/netfilter/arpt_mangle.c#L35">35</a>                 if (<a href="ident?i=ARPT_MANGLE_ADDR_LEN_MAX">ARPT_MANGLE_ADDR_LEN_MAX</a> &lt; pln ||
 <a name="L36" href="source/net/ipv4/netfilter/arpt_mangle.c#L36">36</a>                    (arpptr + pln &gt; <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>)))
 <a name="L37" href="source/net/ipv4/netfilter/arpt_mangle.c#L37">37</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L38" href="source/net/ipv4/netfilter/arpt_mangle.c#L38">38</a>                 <a href="ident?i=memcpy">memcpy</a>(arpptr, &amp;<a href="ident?i=mangle">mangle</a>-&gt;u_s.src_ip, pln);
 <a name="L39" href="source/net/ipv4/netfilter/arpt_mangle.c#L39">39</a>         }
 <a name="L40" href="source/net/ipv4/netfilter/arpt_mangle.c#L40">40</a>         arpptr += pln;
 <a name="L41" href="source/net/ipv4/netfilter/arpt_mangle.c#L41">41</a>         if (<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=ARPT_MANGLE_TDEV">ARPT_MANGLE_TDEV</a>) {
 <a name="L42" href="source/net/ipv4/netfilter/arpt_mangle.c#L42">42</a>                 if (<a href="ident?i=ARPT_DEV_ADDR_LEN_MAX">ARPT_DEV_ADDR_LEN_MAX</a> &lt; hln ||
 <a name="L43" href="source/net/ipv4/netfilter/arpt_mangle.c#L43">43</a>                    (arpptr + hln &gt; <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>)))
 <a name="L44" href="source/net/ipv4/netfilter/arpt_mangle.c#L44">44</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L45" href="source/net/ipv4/netfilter/arpt_mangle.c#L45">45</a>                 <a href="ident?i=memcpy">memcpy</a>(arpptr, <a href="ident?i=mangle">mangle</a>-&gt;tgt_devaddr, hln);
 <a name="L46" href="source/net/ipv4/netfilter/arpt_mangle.c#L46">46</a>         }
 <a name="L47" href="source/net/ipv4/netfilter/arpt_mangle.c#L47">47</a>         arpptr += hln;
 <a name="L48" href="source/net/ipv4/netfilter/arpt_mangle.c#L48">48</a>         if (<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=ARPT_MANGLE_TIP">ARPT_MANGLE_TIP</a>) {
 <a name="L49" href="source/net/ipv4/netfilter/arpt_mangle.c#L49">49</a>                 if (<a href="ident?i=ARPT_MANGLE_ADDR_LEN_MAX">ARPT_MANGLE_ADDR_LEN_MAX</a> &lt; pln ||
 <a name="L50" href="source/net/ipv4/netfilter/arpt_mangle.c#L50">50</a>                    (arpptr + pln &gt; <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>)))
 <a name="L51" href="source/net/ipv4/netfilter/arpt_mangle.c#L51">51</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L52" href="source/net/ipv4/netfilter/arpt_mangle.c#L52">52</a>                 <a href="ident?i=memcpy">memcpy</a>(arpptr, &amp;<a href="ident?i=mangle">mangle</a>-&gt;u_t.tgt_ip, pln);
 <a name="L53" href="source/net/ipv4/netfilter/arpt_mangle.c#L53">53</a>         }
 <a name="L54" href="source/net/ipv4/netfilter/arpt_mangle.c#L54">54</a>         return <a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=target">target</a>;
 <a name="L55" href="source/net/ipv4/netfilter/arpt_mangle.c#L55">55</a> }
 <a name="L56" href="source/net/ipv4/netfilter/arpt_mangle.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/netfilter/arpt_mangle.c#L57">57</a> static int <a href="ident?i=checkentry">checkentry</a>(const struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> *<a href="ident?i=par">par</a>)
 <a name="L58" href="source/net/ipv4/netfilter/arpt_mangle.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/netfilter/arpt_mangle.c#L59">59</a>         const struct <a href="ident?i=arpt_mangle">arpt_mangle</a> *<a href="ident?i=mangle">mangle</a> = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L60" href="source/net/ipv4/netfilter/arpt_mangle.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/netfilter/arpt_mangle.c#L61">61</a>         if (<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=flags">flags</a> &amp; ~ARPT_MANGLE_MASK ||
 <a name="L62" href="source/net/ipv4/netfilter/arpt_mangle.c#L62">62</a>             !(<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=ARPT_MANGLE_MASK">ARPT_MANGLE_MASK</a>))
 <a name="L63" href="source/net/ipv4/netfilter/arpt_mangle.c#L63">63</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L64" href="source/net/ipv4/netfilter/arpt_mangle.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/netfilter/arpt_mangle.c#L65">65</a>         if (<a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=target">target</a> != <a href="ident?i=NF_DROP">NF_DROP</a> &amp;&amp; <a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=target">target</a> != <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a> &amp;&amp;
 <a name="L66" href="source/net/ipv4/netfilter/arpt_mangle.c#L66">66</a>            <a href="ident?i=mangle">mangle</a>-&gt;<a href="ident?i=target">target</a> != <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>)
 <a name="L67" href="source/net/ipv4/netfilter/arpt_mangle.c#L67">67</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L68" href="source/net/ipv4/netfilter/arpt_mangle.c#L68">68</a>         return 0;
 <a name="L69" href="source/net/ipv4/netfilter/arpt_mangle.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/netfilter/arpt_mangle.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/arpt_mangle.c#L71">71</a> static struct <a href="ident?i=xt_target">xt_target</a> arpt_mangle_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L72" href="source/net/ipv4/netfilter/arpt_mangle.c#L72">72</a>         .<a href="ident?i=name">name</a>           = <i>"mangle"</i>,
 <a name="L73" href="source/net/ipv4/netfilter/arpt_mangle.c#L73">73</a>         .<a href="ident?i=family">family</a>         = NFPROTO_ARP,
 <a name="L74" href="source/net/ipv4/netfilter/arpt_mangle.c#L74">74</a>         .<a href="ident?i=target">target</a>         = <a href="ident?i=target">target</a>,
 <a name="L75" href="source/net/ipv4/netfilter/arpt_mangle.c#L75">75</a>         .targetsize     = sizeof(struct <a href="ident?i=arpt_mangle">arpt_mangle</a>),
 <a name="L76" href="source/net/ipv4/netfilter/arpt_mangle.c#L76">76</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=checkentry">checkentry</a>,
 <a name="L77" href="source/net/ipv4/netfilter/arpt_mangle.c#L77">77</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L78" href="source/net/ipv4/netfilter/arpt_mangle.c#L78">78</a> };
 <a name="L79" href="source/net/ipv4/netfilter/arpt_mangle.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/netfilter/arpt_mangle.c#L80">80</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=arpt_mangle_init">arpt_mangle_init</a>(void)
 <a name="L81" href="source/net/ipv4/netfilter/arpt_mangle.c#L81">81</a> {
 <a name="L82" href="source/net/ipv4/netfilter/arpt_mangle.c#L82">82</a>         return <a href="ident?i=xt_register_target">xt_register_target</a>(&amp;arpt_mangle_reg);
 <a name="L83" href="source/net/ipv4/netfilter/arpt_mangle.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/netfilter/arpt_mangle.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/arpt_mangle.c#L85">85</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=arpt_mangle_fini">arpt_mangle_fini</a>(void)
 <a name="L86" href="source/net/ipv4/netfilter/arpt_mangle.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/netfilter/arpt_mangle.c#L87">87</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;arpt_mangle_reg);
 <a name="L88" href="source/net/ipv4/netfilter/arpt_mangle.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/netfilter/arpt_mangle.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/arpt_mangle.c#L90">90</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=arpt_mangle_init">arpt_mangle_init</a>);
 <a name="L91" href="source/net/ipv4/netfilter/arpt_mangle.c#L91">91</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=arpt_mangle_fini">arpt_mangle_fini</a>);
 <a name="L92" href="source/net/ipv4/netfilter/arpt_mangle.c#L92">92</a> </pre></div><p>
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
