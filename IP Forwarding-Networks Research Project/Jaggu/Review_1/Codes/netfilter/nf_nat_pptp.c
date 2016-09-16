<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_pptp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_pptp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_pptp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_pptp.c">nf_nat_pptp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L2">2</a> <b><i> * nf_nat_pptp.c</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L4">4</a> <b><i> * NAT support for PPTP (Point to Point Tunneling Protocol).</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L5">5</a> <b><i> * PPTP is a a protocol for creating virtual private networks.</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L6">6</a> <b><i> * It is a specification defined by Microsoft and some vendors</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L7">7</a> <b><i> * working with Microsoft.  PPTP is built on top of a modified</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L8">8</a> <b><i> * version of the Internet Generic Routing Encapsulation Protocol.</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L9">9</a> <b><i> * GRE is defined in RFC 1701 and RFC 1702.  Documentation of</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L10">10</a> <b><i> * PPTP can be found in RFC 2637</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L12">12</a> <b><i> * (C) 2000-2005 by Harald Welte &lt;laforge@gnumonks.org&gt;</i></b>
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L14">14</a> <b><i> * Development of this code funded by Astaro AG (<a href="http://www.astaro.com/)">http://www.astaro.com/)</a></i></b>
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L16">16</a> <b><i> * (C) 2006-2012 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L18">18</a> <b><i> * TODO: - NAT to a unique tuple, not to TCP source port</i></b>
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L19">19</a> <b><i> *         (needs netfilter tuple reservation)</i></b>
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L20">20</a> <b><i> */</i></b>
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L22">22</a> #include &lt;linux/module.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L23">23</a> #include &lt;linux/tcp.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L25">25</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L26">26</a> #include &lt;net/netfilter/nf_nat_helper.h&gt;
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L27">27</a> #include &lt;net/netfilter/nf_conntrack_helper.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L28">28</a> #include &lt;net/netfilter/nf_conntrack_expect.h&gt;
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L29">29</a> #include &lt;net/netfilter/nf_conntrack_zones.h&gt;
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L30">30</a> #include &lt;linux/netfilter/nf_conntrack_proto_gre.h&gt;
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L31">31</a> #include &lt;linux/netfilter/nf_conntrack_pptp.h&gt;
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L33">33</a> #define <a href="ident?i=NF_NAT_PPTP_VERSION">NF_NAT_PPTP_VERSION</a> <i>"3.0"</i>
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L35">35</a> #define <a href="ident?i=REQ_CID">REQ_CID</a>(<a href="ident?i=req">req</a>, <a href="ident?i=off">off</a>)               (*(<a href="ident?i=__be16">__be16</a> *)((char *)(<a href="ident?i=req">req</a>) + (<a href="ident?i=off">off</a>)))
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L37">37</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L38">38</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Harald Welte &lt;laforge@gnumonks.org&gt;"</i>);
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L39">39</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Netfilter NAT helper module for PPTP"</i>);
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L40">40</a> <a href="ident?i=MODULE_ALIAS">MODULE_ALIAS</a>(<i>"ip_nat_pptp"</i>);
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L42">42</a> static void <a href="ident?i=pptp_nat_expected">pptp_nat_expected</a>(struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L43">43</a>                               struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *exp)
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L44">44</a> {
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L45">45</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=nf_ct_net">nf_ct_net</a>(ct);
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L46">46</a>         const struct <a href="ident?i=nf_conn">nf_conn</a> *<a href="ident?i=master">master</a> = ct-&gt;<a href="ident?i=master">master</a>;
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L47">47</a>         struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *other_exp;
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L48">48</a>         struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> <a href="ident?i=t">t</a>;
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L49">49</a>         const struct <a href="ident?i=nf_ct_pptp_master">nf_ct_pptp_master</a> *ct_pptp_info;
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L50">50</a>         const struct <a href="ident?i=nf_nat_pptp">nf_nat_pptp</a> *nat_pptp_info;
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L51">51</a>         struct <a href="ident?i=nf_nat_range">nf_nat_range</a> <a href="ident?i=range">range</a>;
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L53">53</a>         ct_pptp_info = <a href="ident?i=nfct_help_data">nfct_help_data</a>(<a href="ident?i=master">master</a>);
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L54">54</a>         nat_pptp_info = &amp;<a href="ident?i=nfct_nat">nfct_nat</a>(<a href="ident?i=master">master</a>)-&gt;<a href="ident?i=help">help</a>.nat_pptp_info;
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L56">56</a>         <b><i>/* And here goes the grand finale of corrosion... */</i></b>
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L57">57</a>         if (exp-&gt;<a href="ident?i=dir">dir</a> == IP_CT_DIR_ORIGINAL) {
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L58">58</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"we are PNS-&gt;PAC\n"</i>);
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L59">59</a>                 <b><i>/* therefore, build tuple for PAC-&gt;PNS */</i></b>
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L60">60</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=src">src</a>.l3num = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L61">61</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=master">master</a>-&gt;tuplehash[!exp-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L62">62</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=src">src</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = ct_pptp_info-&gt;pac_call_id;
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L63">63</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=master">master</a>-&gt;tuplehash[!exp-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L64">64</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = ct_pptp_info-&gt;pns_call_id;
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L65">65</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=dst">dst</a>.protonum = <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>;
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L66">66</a>         } else {
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L67">67</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"we are PAC-&gt;PNS\n"</i>);
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L68">68</a>                 <b><i>/* build tuple for PNS-&gt;PAC */</i></b>
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L69">69</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=src">src</a>.l3num = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L70">70</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=master">master</a>-&gt;tuplehash[!exp-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L71">71</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=src">src</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = nat_pptp_info-&gt;pns_call_id;
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L72">72</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a> = <a href="ident?i=master">master</a>-&gt;tuplehash[!exp-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3.<a href="ident?i=ip">ip</a>;
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L73">73</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = nat_pptp_info-&gt;pac_call_id;
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L74">74</a>                 <a href="ident?i=t">t</a>.<a href="ident?i=dst">dst</a>.protonum = <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>;
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L75">75</a>         }
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L77">77</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"trying to unexpect other dir: "</i>);
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L78">78</a>         <a href="ident?i=nf_ct_dump_tuple_ip">nf_ct_dump_tuple_ip</a>(&amp;<a href="ident?i=t">t</a>);
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L79">79</a>         other_exp = <a href="ident?i=nf_ct_expect_find_get">nf_ct_expect_find_get</a>(<a href="ident?i=net">net</a>, <a href="ident?i=nf_ct_zone">nf_ct_zone</a>(ct), &amp;<a href="ident?i=t">t</a>);
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L80">80</a>         if (other_exp) {
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L81">81</a>                 <a href="ident?i=nf_ct_unexpect_related">nf_ct_unexpect_related</a>(other_exp);
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L82">82</a>                 <a href="ident?i=nf_ct_expect_put">nf_ct_expect_put</a>(other_exp);
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L83">83</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"success\n"</i>);
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L84">84</a>         } else {
 <a name="L85" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L85">85</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"not found!\n"</i>);
 <a name="L86" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L86">86</a>         }
 <a name="L87" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L88">88</a>         <b><i>/* This must be a fresh one. */</i></b>
 <a name="L89" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L89">89</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(ct-&gt;<a href="ident?i=status">status</a> &amp; IPS_NAT_DONE_MASK);
 <a name="L90" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L91">91</a>         <b><i>/* Change src to where master sends to */</i></b>
 <a name="L92" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L92">92</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>;
 <a name="L93" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L93">93</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_addr">min_addr</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_addr">max_addr</a>
 <a name="L94" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L94">94</a>                 = ct-&gt;<a href="ident?i=master">master</a>-&gt;tuplehash[!exp-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=dst">dst</a>.u3;
 <a name="L95" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L95">95</a>         if (exp-&gt;<a href="ident?i=dir">dir</a> == IP_CT_DIR_ORIGINAL) {
 <a name="L96" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L96">96</a>                 <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> |= <a href="ident?i=NF_NAT_RANGE_PROTO_SPECIFIED">NF_NAT_RANGE_PROTO_SPECIFIED</a>;
 <a name="L97" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L97">97</a>                 <a href="ident?i=range">range</a>.<a href="ident?i=min_proto">min_proto</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_proto">max_proto</a> = exp-&gt;saved_proto;
 <a name="L98" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L98">98</a>         }
 <a name="L99" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L99">99</a>         <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(ct, &amp;<a href="ident?i=range">range</a>, NF_NAT_MANIP_SRC);
<a name="L100" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L101">101</a>         <b><i>/* For DST manip, map port here to where it's expected. */</i></b>
<a name="L102" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L102">102</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>;
<a name="L103" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L103">103</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_addr">min_addr</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_addr">max_addr</a>
<a name="L104" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L104">104</a>                 = ct-&gt;<a href="ident?i=master">master</a>-&gt;tuplehash[!exp-&gt;<a href="ident?i=dir">dir</a>].tuple.<a href="ident?i=src">src</a>.u3;
<a name="L105" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L105">105</a>         if (exp-&gt;<a href="ident?i=dir">dir</a> == IP_CT_DIR_REPLY) {
<a name="L106" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L106">106</a>                 <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> |= <a href="ident?i=NF_NAT_RANGE_PROTO_SPECIFIED">NF_NAT_RANGE_PROTO_SPECIFIED</a>;
<a name="L107" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L107">107</a>                 <a href="ident?i=range">range</a>.<a href="ident?i=min_proto">min_proto</a> = <a href="ident?i=range">range</a>.<a href="ident?i=max_proto">max_proto</a> = exp-&gt;saved_proto;
<a name="L108" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L108">108</a>         }
<a name="L109" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L109">109</a>         <a href="ident?i=nf_nat_setup_info">nf_nat_setup_info</a>(ct, &amp;<a href="ident?i=range">range</a>, NF_NAT_MANIP_DST);
<a name="L110" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L112">112</a> <b><i>/* outbound packets == from PNS to PAC */</i></b>
<a name="L113" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L113">113</a> static int
<a name="L114" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L114">114</a> <a href="ident?i=pptp_outbound_pkt">pptp_outbound_pkt</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L115" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L115">115</a>                   struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L116" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L116">116</a>                   enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L117" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L117">117</a>                   unsigned int protoff,
<a name="L118" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L118">118</a>                   struct <a href="ident?i=PptpControlHeader">PptpControlHeader</a> *ctlh,
<a name="L119" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L119">119</a>                   union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a> *pptpReq)
<a name="L120" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L121">121</a> {
<a name="L122" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L122">122</a>         struct <a href="ident?i=nf_ct_pptp_master">nf_ct_pptp_master</a> *ct_pptp_info;
<a name="L123" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L123">123</a>         struct <a href="ident?i=nf_nat_pptp">nf_nat_pptp</a> *nat_pptp_info;
<a name="L124" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L124">124</a>         <a href="ident?i=u_int16_t">u_int16_t</a> <a href="ident?i=msg">msg</a>;
<a name="L125" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L125">125</a>         <a href="ident?i=__be16">__be16</a> new_callid;
<a name="L126" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L126">126</a>         unsigned int cid_off;
<a name="L127" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L128">128</a>         ct_pptp_info = <a href="ident?i=nfct_help_data">nfct_help_data</a>(ct);
<a name="L129" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L129">129</a>         nat_pptp_info = &amp;<a href="ident?i=nfct_nat">nfct_nat</a>(ct)-&gt;<a href="ident?i=help">help</a>.nat_pptp_info;
<a name="L130" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L131">131</a>         new_callid = ct_pptp_info-&gt;pns_call_id;
<a name="L132" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L133">133</a>         switch (<a href="ident?i=msg">msg</a> = <a href="ident?i=ntohs">ntohs</a>(ctlh-&gt;messageType)) {
<a name="L134" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L134">134</a>         case <a href="ident?i=PPTP_OUT_CALL_REQUEST">PPTP_OUT_CALL_REQUEST</a>:
<a name="L135" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L135">135</a>                 cid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, ocreq.callID);
<a name="L136" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L136">136</a>                 <b><i>/* FIXME: ideally we would want to reserve a call ID</i></b>
<a name="L137" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L137">137</a> <b><i>                 * here.  current netfilter NAT core is not able to do</i></b>
<a name="L138" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L138">138</a> <b><i>                 * this :( For now we use TCP source port. This breaks</i></b>
<a name="L139" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L139">139</a> <b><i>                 * multiple calls within one control session */</i></b>
<a name="L140" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L141">141</a>                 <b><i>/* save original call ID in nat_info */</i></b>
<a name="L142" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L142">142</a>                 nat_pptp_info-&gt;pns_call_id = ct_pptp_info-&gt;pns_call_id;
<a name="L143" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L144">144</a>                 <b><i>/* don't use tcph-&gt;source since we are at a DSTmanip</i></b>
<a name="L145" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L145">145</a> <b><i>                 * hook (e.g. PREROUTING) and pkt is not mangled yet */</i></b>
<a name="L146" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L146">146</a>                 new_callid = ct-&gt;tuplehash[IP_CT_DIR_REPLY].tuple.<a href="ident?i=dst">dst</a>.u.tcp.<a href="ident?i=port">port</a>;
<a name="L147" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L148">148</a>                 <b><i>/* save new call ID in ct info */</i></b>
<a name="L149" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L149">149</a>                 ct_pptp_info-&gt;pns_call_id = new_callid;
<a name="L150" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L150">150</a>                 break;
<a name="L151" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L151">151</a>         case <a href="ident?i=PPTP_IN_CALL_REPLY">PPTP_IN_CALL_REPLY</a>:
<a name="L152" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L152">152</a>                 cid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, icack.callID);
<a name="L153" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L153">153</a>                 break;
<a name="L154" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L154">154</a>         case <a href="ident?i=PPTP_CALL_CLEAR_REQUEST">PPTP_CALL_CLEAR_REQUEST</a>:
<a name="L155" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L155">155</a>                 cid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, clrreq.callID);
<a name="L156" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L156">156</a>                 break;
<a name="L157" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L157">157</a>         default:
<a name="L158" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L158">158</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"unknown outbound packet 0x%04x:%s\n"</i>, <a href="ident?i=msg">msg</a>,
<a name="L159" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L159">159</a>                          <a href="ident?i=msg">msg</a> &lt;= <a href="ident?i=PPTP_MSG_MAX">PPTP_MSG_MAX</a> ? <a href="ident?i=pptp_msg_name">pptp_msg_name</a>[<a href="ident?i=msg">msg</a>] :
<a name="L160" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L160">160</a>                                                <a href="ident?i=pptp_msg_name">pptp_msg_name</a>[0]);
<a name="L161" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L161">161</a>                 <b><i>/* fall through */</i></b>
<a name="L162" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L162">162</a>         case <a href="ident?i=PPTP_SET_LINK_INFO">PPTP_SET_LINK_INFO</a>:
<a name="L163" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L163">163</a>                 <b><i>/* only need to NAT in case PAC is behind NAT box */</i></b>
<a name="L164" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L164">164</a>         case <a href="ident?i=PPTP_START_SESSION_REQUEST">PPTP_START_SESSION_REQUEST</a>:
<a name="L165" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L165">165</a>         case <a href="ident?i=PPTP_START_SESSION_REPLY">PPTP_START_SESSION_REPLY</a>:
<a name="L166" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L166">166</a>         case <a href="ident?i=PPTP_STOP_SESSION_REQUEST">PPTP_STOP_SESSION_REQUEST</a>:
<a name="L167" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L167">167</a>         case <a href="ident?i=PPTP_STOP_SESSION_REPLY">PPTP_STOP_SESSION_REPLY</a>:
<a name="L168" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L168">168</a>         case <a href="ident?i=PPTP_ECHO_REQUEST">PPTP_ECHO_REQUEST</a>:
<a name="L169" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L169">169</a>         case <a href="ident?i=PPTP_ECHO_REPLY">PPTP_ECHO_REPLY</a>:
<a name="L170" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L170">170</a>                 <b><i>/* no need to alter packet */</i></b>
<a name="L171" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L171">171</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L172" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L172">172</a>         }
<a name="L173" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L174">174</a>         <b><i>/* only OUT_CALL_REQUEST, IN_CALL_REPLY, CALL_CLEAR_REQUEST pass</i></b>
<a name="L175" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L175">175</a> <b><i>         * down to here */</i></b>
<a name="L176" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L176">176</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"altering call id from 0x%04x to 0x%04x\n"</i>,
<a name="L177" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L177">177</a>                  <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=REQ_CID">REQ_CID</a>(pptpReq, cid_off)), <a href="ident?i=ntohs">ntohs</a>(new_callid));
<a name="L178" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L179">179</a>         <b><i>/* mangle packet */</i></b>
<a name="L180" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L180">180</a>         if (<a href="ident?i=nf_nat_mangle_tcp_packet">nf_nat_mangle_tcp_packet</a>(<a href="ident?i=skb">skb</a>, ct, ctinfo, protoff,
<a name="L181" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L181">181</a>                                      cid_off + sizeof(struct <a href="ident?i=pptp_pkt_hdr">pptp_pkt_hdr</a>) +
<a name="L182" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L182">182</a>                                      sizeof(struct <a href="ident?i=PptpControlHeader">PptpControlHeader</a>),
<a name="L183" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L183">183</a>                                      sizeof(new_callid), (char *)&amp;new_callid,
<a name="L184" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L184">184</a>                                      sizeof(new_callid)) == 0)
<a name="L185" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L185">185</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L186" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L186">186</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L187" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L187">187</a> }
<a name="L188" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L189">189</a> static void
<a name="L190" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L190">190</a> <a href="ident?i=pptp_exp_gre">pptp_exp_gre</a>(struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *expect_orig,
<a name="L191" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L191">191</a>              struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *expect_reply)
<a name="L192" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L192">192</a> {
<a name="L193" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L193">193</a>         const struct <a href="ident?i=nf_conn">nf_conn</a> *ct = expect_orig-&gt;<a href="ident?i=master">master</a>;
<a name="L194" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L194">194</a>         struct <a href="ident?i=nf_ct_pptp_master">nf_ct_pptp_master</a> *ct_pptp_info;
<a name="L195" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L195">195</a>         struct <a href="ident?i=nf_nat_pptp">nf_nat_pptp</a> *nat_pptp_info;
<a name="L196" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L197">197</a>         ct_pptp_info = <a href="ident?i=nfct_help_data">nfct_help_data</a>(ct);
<a name="L198" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L198">198</a>         nat_pptp_info = &amp;<a href="ident?i=nfct_nat">nfct_nat</a>(ct)-&gt;<a href="ident?i=help">help</a>.nat_pptp_info;
<a name="L199" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L200">200</a>         <b><i>/* save original PAC call ID in nat_info */</i></b>
<a name="L201" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L201">201</a>         nat_pptp_info-&gt;pac_call_id = ct_pptp_info-&gt;pac_call_id;
<a name="L202" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L203">203</a>         <b><i>/* alter expectation for PNS-&gt;PAC direction */</i></b>
<a name="L204" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L204">204</a>         expect_orig-&gt;saved_proto.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = ct_pptp_info-&gt;pns_call_id;
<a name="L205" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L205">205</a>         expect_orig-&gt;tuple.<a href="ident?i=src">src</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = nat_pptp_info-&gt;pns_call_id;
<a name="L206" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L206">206</a>         expect_orig-&gt;tuple.<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = ct_pptp_info-&gt;pac_call_id;
<a name="L207" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L207">207</a>         expect_orig-&gt;<a href="ident?i=dir">dir</a> = IP_CT_DIR_ORIGINAL;
<a name="L208" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L209">209</a>         <b><i>/* alter expectation for PAC-&gt;PNS direction */</i></b>
<a name="L210" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L210">210</a>         expect_reply-&gt;saved_proto.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = nat_pptp_info-&gt;pns_call_id;
<a name="L211" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L211">211</a>         expect_reply-&gt;tuple.<a href="ident?i=src">src</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = nat_pptp_info-&gt;pac_call_id;
<a name="L212" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L212">212</a>         expect_reply-&gt;tuple.<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a> = ct_pptp_info-&gt;pns_call_id;
<a name="L213" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L213">213</a>         expect_reply-&gt;<a href="ident?i=dir">dir</a> = IP_CT_DIR_REPLY;
<a name="L214" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L214">214</a> }
<a name="L215" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L216">216</a> <b><i>/* inbound packets == from PAC to PNS */</i></b>
<a name="L217" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L217">217</a> static int
<a name="L218" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L218">218</a> <a href="ident?i=pptp_inbound_pkt">pptp_inbound_pkt</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L219" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L219">219</a>                  struct <a href="ident?i=nf_conn">nf_conn</a> *ct,
<a name="L220" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L220">220</a>                  enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
<a name="L221" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L221">221</a>                  unsigned int protoff,
<a name="L222" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L222">222</a>                  struct <a href="ident?i=PptpControlHeader">PptpControlHeader</a> *ctlh,
<a name="L223" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L223">223</a>                  union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a> *pptpReq)
<a name="L224" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L225">225</a>         const struct <a href="ident?i=nf_nat_pptp">nf_nat_pptp</a> *nat_pptp_info;
<a name="L226" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L226">226</a>         <a href="ident?i=u_int16_t">u_int16_t</a> <a href="ident?i=msg">msg</a>;
<a name="L227" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L227">227</a>         <a href="ident?i=__be16">__be16</a> new_pcid;
<a name="L228" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L228">228</a>         unsigned int pcid_off;
<a name="L229" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L230">230</a>         nat_pptp_info = &amp;<a href="ident?i=nfct_nat">nfct_nat</a>(ct)-&gt;<a href="ident?i=help">help</a>.nat_pptp_info;
<a name="L231" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L231">231</a>         new_pcid = nat_pptp_info-&gt;pns_call_id;
<a name="L232" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L233">233</a>         switch (<a href="ident?i=msg">msg</a> = <a href="ident?i=ntohs">ntohs</a>(ctlh-&gt;messageType)) {
<a name="L234" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L234">234</a>         case <a href="ident?i=PPTP_OUT_CALL_REPLY">PPTP_OUT_CALL_REPLY</a>:
<a name="L235" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L235">235</a>                 pcid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, ocack.peersCallID);
<a name="L236" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L236">236</a>                 break;
<a name="L237" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L237">237</a>         case <a href="ident?i=PPTP_IN_CALL_CONNECT">PPTP_IN_CALL_CONNECT</a>:
<a name="L238" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L238">238</a>                 pcid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, iccon.peersCallID);
<a name="L239" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L239">239</a>                 break;
<a name="L240" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L240">240</a>         case <a href="ident?i=PPTP_IN_CALL_REQUEST">PPTP_IN_CALL_REQUEST</a>:
<a name="L241" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L241">241</a>                 <b><i>/* only need to nat in case PAC is behind NAT box */</i></b>
<a name="L242" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L242">242</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L243" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L243">243</a>         case <a href="ident?i=PPTP_WAN_ERROR_NOTIFY">PPTP_WAN_ERROR_NOTIFY</a>:
<a name="L244" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L244">244</a>                 pcid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, wanerr.peersCallID);
<a name="L245" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L245">245</a>                 break;
<a name="L246" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L246">246</a>         case <a href="ident?i=PPTP_CALL_DISCONNECT_NOTIFY">PPTP_CALL_DISCONNECT_NOTIFY</a>:
<a name="L247" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L247">247</a>                 pcid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, disc.callID);
<a name="L248" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L248">248</a>                 break;
<a name="L249" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L249">249</a>         case <a href="ident?i=PPTP_SET_LINK_INFO">PPTP_SET_LINK_INFO</a>:
<a name="L250" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L250">250</a>                 pcid_off = <a href="ident?i=offsetof">offsetof</a>(union <a href="ident?i=pptp_ctrl_union">pptp_ctrl_union</a>, setlink.peersCallID);
<a name="L251" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L251">251</a>                 break;
<a name="L252" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L252">252</a>         default:
<a name="L253" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L253">253</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"unknown inbound packet %s\n"</i>,
<a name="L254" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L254">254</a>                          <a href="ident?i=msg">msg</a> &lt;= <a href="ident?i=PPTP_MSG_MAX">PPTP_MSG_MAX</a> ? <a href="ident?i=pptp_msg_name">pptp_msg_name</a>[<a href="ident?i=msg">msg</a>] :
<a name="L255" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L255">255</a>                                                <a href="ident?i=pptp_msg_name">pptp_msg_name</a>[0]);
<a name="L256" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L256">256</a>                 <b><i>/* fall through */</i></b>
<a name="L257" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L257">257</a>         case <a href="ident?i=PPTP_START_SESSION_REQUEST">PPTP_START_SESSION_REQUEST</a>:
<a name="L258" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L258">258</a>         case <a href="ident?i=PPTP_START_SESSION_REPLY">PPTP_START_SESSION_REPLY</a>:
<a name="L259" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L259">259</a>         case <a href="ident?i=PPTP_STOP_SESSION_REQUEST">PPTP_STOP_SESSION_REQUEST</a>:
<a name="L260" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L260">260</a>         case <a href="ident?i=PPTP_STOP_SESSION_REPLY">PPTP_STOP_SESSION_REPLY</a>:
<a name="L261" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L261">261</a>         case <a href="ident?i=PPTP_ECHO_REQUEST">PPTP_ECHO_REQUEST</a>:
<a name="L262" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L262">262</a>         case <a href="ident?i=PPTP_ECHO_REPLY">PPTP_ECHO_REPLY</a>:
<a name="L263" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L263">263</a>                 <b><i>/* no need to alter packet */</i></b>
<a name="L264" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L264">264</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L265" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L265">265</a>         }
<a name="L266" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L267">267</a>         <b><i>/* only OUT_CALL_REPLY, IN_CALL_CONNECT, IN_CALL_REQUEST,</i></b>
<a name="L268" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L268">268</a> <b><i>         * WAN_ERROR_NOTIFY, CALL_DISCONNECT_NOTIFY pass down here */</i></b>
<a name="L269" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L270">270</a>         <b><i>/* mangle packet */</i></b>
<a name="L271" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L271">271</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"altering peer call id from 0x%04x to 0x%04x\n"</i>,
<a name="L272" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L272">272</a>                  <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=REQ_CID">REQ_CID</a>(pptpReq, pcid_off)), <a href="ident?i=ntohs">ntohs</a>(new_pcid));
<a name="L273" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L274">274</a>         if (<a href="ident?i=nf_nat_mangle_tcp_packet">nf_nat_mangle_tcp_packet</a>(<a href="ident?i=skb">skb</a>, ct, ctinfo, protoff,
<a name="L275" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L275">275</a>                                      pcid_off + sizeof(struct <a href="ident?i=pptp_pkt_hdr">pptp_pkt_hdr</a>) +
<a name="L276" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L276">276</a>                                      sizeof(struct <a href="ident?i=PptpControlHeader">PptpControlHeader</a>),
<a name="L277" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L277">277</a>                                      sizeof(new_pcid), (char *)&amp;new_pcid,
<a name="L278" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L278">278</a>                                      sizeof(new_pcid)) == 0)
<a name="L279" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L279">279</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L280" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L280">280</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L281" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L281">281</a> }
<a name="L282" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L283">283</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_nat_helper_pptp_init">nf_nat_helper_pptp_init</a>(void)
<a name="L284" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L284">284</a> {
<a name="L285" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L285">285</a>         <a href="ident?i=nf_nat_need_gre">nf_nat_need_gre</a>();
<a name="L286" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L287">287</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nf_nat_pptp_hook_outbound">nf_nat_pptp_hook_outbound</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L288" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L288">288</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_outbound">nf_nat_pptp_hook_outbound</a>, <a href="ident?i=pptp_outbound_pkt">pptp_outbound_pkt</a>);
<a name="L289" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L290">290</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nf_nat_pptp_hook_inbound">nf_nat_pptp_hook_inbound</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L291" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L291">291</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_inbound">nf_nat_pptp_hook_inbound</a>, <a href="ident?i=pptp_inbound_pkt">pptp_inbound_pkt</a>);
<a name="L292" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L293">293</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nf_nat_pptp_hook_exp_gre">nf_nat_pptp_hook_exp_gre</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L294" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L294">294</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_exp_gre">nf_nat_pptp_hook_exp_gre</a>, <a href="ident?i=pptp_exp_gre">pptp_exp_gre</a>);
<a name="L295" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L296">296</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=nf_nat_pptp_hook_expectfn">nf_nat_pptp_hook_expectfn</a> != <a href="ident?i=NULL">NULL</a>);
<a name="L297" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L297">297</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_expectfn">nf_nat_pptp_hook_expectfn</a>, <a href="ident?i=pptp_nat_expected">pptp_nat_expected</a>);
<a name="L298" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L298">298</a>         return 0;
<a name="L299" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L299">299</a> }
<a name="L300" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L301">301</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_nat_helper_pptp_fini">nf_nat_helper_pptp_fini</a>(void)
<a name="L302" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L302">302</a> {
<a name="L303" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L303">303</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_expectfn">nf_nat_pptp_hook_expectfn</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L304" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L304">304</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_exp_gre">nf_nat_pptp_hook_exp_gre</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L305" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L305">305</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_inbound">nf_nat_pptp_hook_inbound</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L306" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L306">306</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=nf_nat_pptp_hook_outbound">nf_nat_pptp_hook_outbound</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L307" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L307">307</a>         <a href="ident?i=synchronize_rcu">synchronize_rcu</a>();
<a name="L308" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L308">308</a> }
<a name="L309" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L310">310</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_nat_helper_pptp_init">nf_nat_helper_pptp_init</a>);
<a name="L311" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L311">311</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_nat_helper_pptp_fini">nf_nat_helper_pptp_fini</a>);
<a name="L312" href="source/net/ipv4/netfilter/nf_nat_pptp.c#L312">312</a> </pre></div><p>
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
