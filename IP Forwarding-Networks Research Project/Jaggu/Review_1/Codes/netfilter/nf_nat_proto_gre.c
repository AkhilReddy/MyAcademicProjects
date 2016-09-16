<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_nat_proto_gre.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_nat_proto_gre.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_nat_proto_gre.c">nf_nat_proto_gre.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L2">2</a> <b><i> * nf_nat_proto_gre.c</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L4">4</a> <b><i> * NAT protocol helper module for GRE.</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L6">6</a> <b><i> * GRE is a generic encapsulation protocol, which is generally not very</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L7">7</a> <b><i> * suited for NAT, as it has no protocol-specific part as port numbers.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L9">9</a> <b><i> * It has an optional key field, which may help us distinguishing two</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L10">10</a> <b><i> * connections between the same two hosts.</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L12">12</a> <b><i> * GRE is defined in RFC 1701 and RFC 1702, as well as RFC 2784</i></b>
 <a name="L13" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L14">14</a> <b><i> * PPTP is built on top of a modified version of GRE, and has a mandatory</i></b>
 <a name="L15" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L15">15</a> <b><i> * field called "CallID", which serves us for the same purpose as the key</i></b>
 <a name="L16" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L16">16</a> <b><i> * field in plain GRE.</i></b>
 <a name="L17" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L18">18</a> <b><i> * Documentation about PPTP can be found in RFC 2637</i></b>
 <a name="L19" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L20">20</a> <b><i> * (C) 2000-2005 by Harald Welte &lt;laforge@gnumonks.org&gt;</i></b>
 <a name="L21" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L21">21</a> <b><i> *</i></b>
 <a name="L22" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L22">22</a> <b><i> * Development of this code funded by Astaro AG (<a href="http://www.astaro.com/)">http://www.astaro.com/)</a></i></b>
 <a name="L23" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L23">23</a> <b><i> *</i></b>
 <a name="L24" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L24">24</a> <b><i> * (C) 2006-2012 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
 <a name="L25" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L25">25</a> <b><i> *</i></b>
 <a name="L26" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L26">26</a> <b><i> */</i></b>
 <a name="L27" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L28">28</a> #include &lt;linux/module.h&gt;
 <a name="L29" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L29">29</a> #include &lt;linux/skbuff.h&gt;
 <a name="L30" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L30">30</a> #include &lt;linux/ip.h&gt;
 <a name="L31" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L32">32</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L33" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L33">33</a> #include &lt;net/netfilter/nf_nat_l4proto.h&gt;
 <a name="L34" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L34">34</a> #include &lt;linux/netfilter/nf_conntrack_proto_gre.h&gt;
 <a name="L35" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L36">36</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L37" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L37">37</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Harald Welte &lt;laforge@gnumonks.org&gt;"</i>);
 <a name="L38" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L38">38</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Netfilter NAT protocol helper module for GRE"</i>);
 <a name="L39" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L40">40</a> <b><i>/* generate unique tuple ... */</i></b>
 <a name="L41" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L41">41</a> static void
 <a name="L42" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L42">42</a> <a href="ident?i=gre_unique_tuple">gre_unique_tuple</a>(const struct <a href="ident?i=nf_nat_l3proto">nf_nat_l3proto</a> *l3proto,
 <a name="L43" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L43">43</a>                  struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L44" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L44">44</a>                  const struct <a href="ident?i=nf_nat_range">nf_nat_range</a> *<a href="ident?i=range">range</a>,
 <a name="L45" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L45">45</a>                  enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype,
 <a name="L46" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L46">46</a>                  const struct <a href="ident?i=nf_conn">nf_conn</a> *ct)
 <a name="L47" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L47">47</a> {
 <a name="L48" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L48">48</a>         static <a href="ident?i=u_int16_t">u_int16_t</a> <a href="ident?i=key">key</a>;
 <a name="L49" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L49">49</a>         <a href="ident?i=__be16">__be16</a> *keyptr;
 <a name="L50" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L50">50</a>         unsigned int <a href="ident?i=min">min</a>, <a href="ident?i=i">i</a>, <a href="ident?i=range_size">range_size</a>;
 <a name="L51" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L52">52</a>         <b><i>/* If there is no master conntrack we are not PPTP,</i></b>
 <a name="L53" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L53">53</a> <b><i>           do not change tuples */</i></b>
 <a name="L54" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L54">54</a>         if (!ct-&gt;<a href="ident?i=master">master</a>)
 <a name="L55" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L55">55</a>                 return;
 <a name="L56" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L57">57</a>         if (maniptype == NF_NAT_MANIP_SRC)
 <a name="L58" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L58">58</a>                 keyptr = &amp;tuple-&gt;<a href="ident?i=src">src</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a>;
 <a name="L59" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L59">59</a>         else
 <a name="L60" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L60">60</a>                 keyptr = &amp;tuple-&gt;<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a>;
 <a name="L61" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L62">62</a>         if (!(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NF_NAT_RANGE_PROTO_SPECIFIED">NF_NAT_RANGE_PROTO_SPECIFIED</a>)) {
 <a name="L63" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L63">63</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"%p: NATing GRE PPTP\n"</i>, ct);
 <a name="L64" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L64">64</a>                 <a href="ident?i=min">min</a> = 1;
 <a name="L65" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L65">65</a>                 <a href="ident?i=range_size">range_size</a> = 0xffff;
 <a name="L66" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L66">66</a>         } else {
 <a name="L67" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L67">67</a>                 <a href="ident?i=min">min</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=min_proto">min_proto</a>.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a>);
 <a name="L68" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L68">68</a>                 <a href="ident?i=range_size">range_size</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=range">range</a>-&gt;<a href="ident?i=max_proto">max_proto</a>.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a>) - <a href="ident?i=min">min</a> + 1;
 <a name="L69" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L69">69</a>         }
 <a name="L70" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L71">71</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"min = %u, range_size = %u\n"</i>, <a href="ident?i=min">min</a>, <a href="ident?i=range_size">range_size</a>);
 <a name="L72" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L73">73</a>         for (<a href="ident?i=i">i</a> = 0; ; ++<a href="ident?i=key">key</a>) {
 <a name="L74" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L74">74</a>                 *keyptr = <a href="ident?i=htons">htons</a>(<a href="ident?i=min">min</a> + <a href="ident?i=key">key</a> % <a href="ident?i=range_size">range_size</a>);
 <a name="L75" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L75">75</a>                 if (++<a href="ident?i=i">i</a> == <a href="ident?i=range_size">range_size</a> || !<a href="ident?i=nf_nat_used_tuple">nf_nat_used_tuple</a>(tuple, ct))
 <a name="L76" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L76">76</a>                         return;
 <a name="L77" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L77">77</a>         }
 <a name="L78" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L79">79</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"%p: no NAT mapping\n"</i>, ct);
 <a name="L80" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L80">80</a>         return;
 <a name="L81" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L83">83</a> <b><i>/* manipulate a GRE packet according to maniptype */</i></b>
 <a name="L84" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L84">84</a> static <a href="ident?i=bool">bool</a>
 <a name="L85" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L85">85</a> <a href="ident?i=gre_manip_pkt">gre_manip_pkt</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L86" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L86">86</a>               const struct <a href="ident?i=nf_nat_l3proto">nf_nat_l3proto</a> *l3proto,
 <a name="L87" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L87">87</a>               unsigned int iphdroff, unsigned int hdroff,
 <a name="L88" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L88">88</a>               const struct <a href="ident?i=nf_conntrack_tuple">nf_conntrack_tuple</a> *tuple,
 <a name="L89" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L89">89</a>               enum <a href="ident?i=nf_nat_manip_type">nf_nat_manip_type</a> maniptype)
 <a name="L90" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L90">90</a> {
 <a name="L91" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L91">91</a>         const struct <a href="ident?i=gre_hdr">gre_hdr</a> *greh;
 <a name="L92" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L92">92</a>         struct <a href="ident?i=gre_hdr_pptp">gre_hdr_pptp</a> *pgreh;
 <a name="L93" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L94">94</a>         <b><i>/* pgreh includes two optional 32bit fields which are not required</i></b>
 <a name="L95" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L95">95</a> <b><i>         * to be there.  That's where the magic '8' comes from */</i></b>
 <a name="L96" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L96">96</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, hdroff + sizeof(*pgreh) - 8))
 <a name="L97" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L97">97</a>                 return <a href="ident?i=false">false</a>;
 <a name="L98" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L99">99</a>         greh = (void *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + hdroff;
<a name="L100" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L100">100</a>         pgreh = (struct <a href="ident?i=gre_hdr_pptp">gre_hdr_pptp</a> *)greh;
<a name="L101" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L102">102</a>         <b><i>/* we only have destination manip of a packet, since 'source key'</i></b>
<a name="L103" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L103">103</a> <b><i>         * is not present in the packet itself */</i></b>
<a name="L104" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L104">104</a>         if (maniptype != NF_NAT_MANIP_DST)
<a name="L105" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L105">105</a>                 return <a href="ident?i=true">true</a>;
<a name="L106" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L106">106</a>         switch (greh-&gt;<a href="ident?i=version">version</a>) {
<a name="L107" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L107">107</a>         case <a href="ident?i=GRE_VERSION_1701">GRE_VERSION_1701</a>:
<a name="L108" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L108">108</a>                 <b><i>/* We do not currently NAT any GREv0 packets.</i></b>
<a name="L109" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L109">109</a> <b><i>                 * Try to behave like "nf_nat_proto_unknown" */</i></b>
<a name="L110" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L110">110</a>                 break;
<a name="L111" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L111">111</a>         case <a href="ident?i=GRE_VERSION_PPTP">GRE_VERSION_PPTP</a>:
<a name="L112" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L112">112</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"call_id -&gt; 0x%04x\n"</i>, <a href="ident?i=ntohs">ntohs</a>(tuple-&gt;<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a>));
<a name="L113" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L113">113</a>                 pgreh-&gt;call_id = tuple-&gt;<a href="ident?i=dst">dst</a>.u.<a href="ident?i=gre">gre</a>.<a href="ident?i=key">key</a>;
<a name="L114" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L114">114</a>                 break;
<a name="L115" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L115">115</a>         default:
<a name="L116" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L116">116</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"can't nat unknown GRE version\n"</i>);
<a name="L117" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L117">117</a>                 return <a href="ident?i=false">false</a>;
<a name="L118" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L118">118</a>         }
<a name="L119" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L119">119</a>         return <a href="ident?i=true">true</a>;
<a name="L120" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L120">120</a> }
<a name="L121" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L122">122</a> static const struct <a href="ident?i=nf_nat_l4proto">nf_nat_l4proto</a> <a href="ident?i=gre">gre</a> = {
<a name="L123" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L123">123</a>         .l4proto                = <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>,
<a name="L124" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L124">124</a>         .manip_pkt              = <a href="ident?i=gre_manip_pkt">gre_manip_pkt</a>,
<a name="L125" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L125">125</a>         .<a href="ident?i=in_range">in_range</a>               = <a href="ident?i=nf_nat_l4proto_in_range">nf_nat_l4proto_in_range</a>,
<a name="L126" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L126">126</a>         .unique_tuple           = <a href="ident?i=gre_unique_tuple">gre_unique_tuple</a>,
<a name="L127" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L127">127</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NF_CT_NETLINK)
<a name="L128" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L128">128</a>         .nlattr_to_range        = <a href="ident?i=nf_nat_l4proto_nlattr_to_range">nf_nat_l4proto_nlattr_to_range</a>,
<a name="L129" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L129">129</a> #endif
<a name="L130" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L130">130</a> };
<a name="L131" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L132">132</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_nat_proto_gre_init">nf_nat_proto_gre_init</a>(void)
<a name="L133" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L134">134</a>         return <a href="ident?i=nf_nat_l4proto_register">nf_nat_l4proto_register</a>(NFPROTO_IPV4, &amp;<a href="ident?i=gre">gre</a>);
<a name="L135" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L135">135</a> }
<a name="L136" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L137">137</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_nat_proto_gre_fini">nf_nat_proto_gre_fini</a>(void)
<a name="L138" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L138">138</a> {
<a name="L139" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L139">139</a>         <a href="ident?i=nf_nat_l4proto_unregister">nf_nat_l4proto_unregister</a>(NFPROTO_IPV4, &amp;<a href="ident?i=gre">gre</a>);
<a name="L140" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L140">140</a> }
<a name="L141" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L142">142</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_nat_proto_gre_init">nf_nat_proto_gre_init</a>);
<a name="L143" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L143">143</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_nat_proto_gre_fini">nf_nat_proto_gre_fini</a>);
<a name="L144" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L145">145</a> void <a href="ident?i=nf_nat_need_gre">nf_nat_need_gre</a>(void)
<a name="L146" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L146">146</a> {
<a name="L147" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L147">147</a>         return;
<a name="L148" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L148">148</a> }
<a name="L149" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L149">149</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=nf_nat_need_gre">nf_nat_need_gre</a>);
<a name="L150" href="source/net/ipv4/netfilter/nf_nat_proto_gre.c#L150">150</a> </pre></div><p>
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
