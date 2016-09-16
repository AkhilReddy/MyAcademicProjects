<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inet_hashtables.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inet_hashtables.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inet_hashtables.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inet_hashtables.c">inet_hashtables.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inet_hashtables.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inet_hashtables.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/inet_hashtables.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/inet_hashtables.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/inet_hashtables.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/inet_hashtables.c#L6">6</a> <b><i> *              Generic INET transport hashtables</i></b>
  <a name="L7" href="source/net/ipv4/inet_hashtables.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/inet_hashtables.c#L8">8</a> <b><i> * Authors:     Lotsa people, from code originally in tcp</i></b>
  <a name="L9" href="source/net/ipv4/inet_hashtables.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/inet_hashtables.c#L10">10</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
 <a name="L11" href="source/net/ipv4/inet_hashtables.c#L11">11</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L12" href="source/net/ipv4/inet_hashtables.c#L12">12</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L13" href="source/net/ipv4/inet_hashtables.c#L13">13</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L14" href="source/net/ipv4/inet_hashtables.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/inet_hashtables.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/inet_hashtables.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/inet_hashtables.c#L17">17</a> #include &lt;linux/random.h&gt;
 <a name="L18" href="source/net/ipv4/inet_hashtables.c#L18">18</a> #include &lt;linux/sched.h&gt;
 <a name="L19" href="source/net/ipv4/inet_hashtables.c#L19">19</a> #include &lt;linux/slab.h&gt;
 <a name="L20" href="source/net/ipv4/inet_hashtables.c#L20">20</a> #include &lt;linux/wait.h&gt;
 <a name="L21" href="source/net/ipv4/inet_hashtables.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/inet_hashtables.c#L22">22</a> #include &lt;net/inet_connection_sock.h&gt;
 <a name="L23" href="source/net/ipv4/inet_hashtables.c#L23">23</a> #include &lt;net/inet_hashtables.h&gt;
 <a name="L24" href="source/net/ipv4/inet_hashtables.c#L24">24</a> #include &lt;net/secure_seq.h&gt;
 <a name="L25" href="source/net/ipv4/inet_hashtables.c#L25">25</a> #include &lt;net/ip.h&gt;
 <a name="L26" href="source/net/ipv4/inet_hashtables.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/inet_hashtables.c#L27">27</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=inet_ehashfn">inet_ehashfn</a>(const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const <a href="ident?i=__be32">__be32</a> <a href="ident?i=laddr">laddr</a>,
 <a name="L28" href="source/net/ipv4/inet_hashtables.c#L28">28</a>                         const <a href="ident?i=__u16">__u16</a> lport, const <a href="ident?i=__be32">__be32</a> faddr,
 <a name="L29" href="source/net/ipv4/inet_hashtables.c#L29">29</a>                         const <a href="ident?i=__be16">__be16</a> fport)
 <a name="L30" href="source/net/ipv4/inet_hashtables.c#L30">30</a> {
 <a name="L31" href="source/net/ipv4/inet_hashtables.c#L31">31</a>         static <a href="ident?i=u32">u32</a> inet_ehash_secret <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L32" href="source/net/ipv4/inet_hashtables.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/inet_hashtables.c#L33">33</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(&amp;inet_ehash_secret, sizeof(inet_ehash_secret));
 <a name="L34" href="source/net/ipv4/inet_hashtables.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/inet_hashtables.c#L35">35</a>         return <a href="ident?i=__inet_ehashfn">__inet_ehashfn</a>(<a href="ident?i=laddr">laddr</a>, lport, faddr, fport,
 <a name="L36" href="source/net/ipv4/inet_hashtables.c#L36">36</a>                               inet_ehash_secret + <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>));
 <a name="L37" href="source/net/ipv4/inet_hashtables.c#L37">37</a> }
 <a name="L38" href="source/net/ipv4/inet_hashtables.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/inet_hashtables.c#L39">39</a> <b><i>/* This function handles inet_sock, but also timewait and request sockets</i></b>
 <a name="L40" href="source/net/ipv4/inet_hashtables.c#L40">40</a> <b><i> * for IPv4/IPv6.</i></b>
 <a name="L41" href="source/net/ipv4/inet_hashtables.c#L41">41</a> <b><i> */</i></b>
 <a name="L42" href="source/net/ipv4/inet_hashtables.c#L42">42</a> <a href="ident?i=u32">u32</a> <a href="ident?i=sk_ehashfn">sk_ehashfn</a>(const struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L43" href="source/net/ipv4/inet_hashtables.c#L43">43</a> {
 <a name="L44" href="source/net/ipv4/inet_hashtables.c#L44">44</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L45" href="source/net/ipv4/inet_hashtables.c#L45">45</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a> &amp;&amp;
 <a name="L46" href="source/net/ipv4/inet_hashtables.c#L46">46</a>             !<a href="ident?i=ipv6_addr_v4mapped">ipv6_addr_v4mapped</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>))
 <a name="L47" href="source/net/ipv4/inet_hashtables.c#L47">47</a>                 return <a href="ident?i=inet6_ehashfn">inet6_ehashfn</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
 <a name="L48" href="source/net/ipv4/inet_hashtables.c#L48">48</a>                                      &amp;sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>, sk-&gt;<a href="ident?i=sk_num">sk_num</a>,
 <a name="L49" href="source/net/ipv4/inet_hashtables.c#L49">49</a>                                      &amp;sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>, sk-&gt;<a href="ident?i=sk_dport">sk_dport</a>);
 <a name="L50" href="source/net/ipv4/inet_hashtables.c#L50">50</a> #endif
 <a name="L51" href="source/net/ipv4/inet_hashtables.c#L51">51</a>         return <a href="ident?i=inet_ehashfn">inet_ehashfn</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
 <a name="L52" href="source/net/ipv4/inet_hashtables.c#L52">52</a>                             sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a>, sk-&gt;<a href="ident?i=sk_num">sk_num</a>,
 <a name="L53" href="source/net/ipv4/inet_hashtables.c#L53">53</a>                             sk-&gt;<a href="ident?i=sk_daddr">sk_daddr</a>, sk-&gt;<a href="ident?i=sk_dport">sk_dport</a>);
 <a name="L54" href="source/net/ipv4/inet_hashtables.c#L54">54</a> }
 <a name="L55" href="source/net/ipv4/inet_hashtables.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/inet_hashtables.c#L56">56</a> <b><i>/*</i></b>
 <a name="L57" href="source/net/ipv4/inet_hashtables.c#L57">57</a> <b><i> * Allocate and initialize a new local port bind bucket.</i></b>
 <a name="L58" href="source/net/ipv4/inet_hashtables.c#L58">58</a> <b><i> * The bindhash mutex for snum's hash chain must be held here.</i></b>
 <a name="L59" href="source/net/ipv4/inet_hashtables.c#L59">59</a> <b><i> */</i></b>
 <a name="L60" href="source/net/ipv4/inet_hashtables.c#L60">60</a> struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=inet_bind_bucket_create">inet_bind_bucket_create</a>(struct <a href="ident?i=kmem_cache">kmem_cache</a> *cachep,
 <a name="L61" href="source/net/ipv4/inet_hashtables.c#L61">61</a>                                                  struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
 <a name="L62" href="source/net/ipv4/inet_hashtables.c#L62">62</a>                                                  struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *<a href="ident?i=head">head</a>,
 <a name="L63" href="source/net/ipv4/inet_hashtables.c#L63">63</a>                                                  const unsigned short snum)
 <a name="L64" href="source/net/ipv4/inet_hashtables.c#L64">64</a> {
 <a name="L65" href="source/net/ipv4/inet_hashtables.c#L65">65</a>         struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a> = <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(cachep, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
 <a name="L66" href="source/net/ipv4/inet_hashtables.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/inet_hashtables.c#L67">67</a>         if (<a href="ident?i=tb">tb</a>) {
 <a name="L68" href="source/net/ipv4/inet_hashtables.c#L68">68</a>                 <a href="ident?i=write_pnet">write_pnet</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=ib_net">ib_net</a>, <a href="ident?i=net">net</a>);
 <a name="L69" href="source/net/ipv4/inet_hashtables.c#L69">69</a>                 <a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=port">port</a>      = snum;
 <a name="L70" href="source/net/ipv4/inet_hashtables.c#L70">70</a>                 <a href="ident?i=tb">tb</a>-&gt;fastreuse = 0;
 <a name="L71" href="source/net/ipv4/inet_hashtables.c#L71">71</a>                 <a href="ident?i=tb">tb</a>-&gt;fastreuseport = 0;
 <a name="L72" href="source/net/ipv4/inet_hashtables.c#L72">72</a>                 <a href="ident?i=tb">tb</a>-&gt;num_owners = 0;
 <a name="L73" href="source/net/ipv4/inet_hashtables.c#L73">73</a>                 <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;owners);
 <a name="L74" href="source/net/ipv4/inet_hashtables.c#L74">74</a>                 <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=node">node</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>);
 <a name="L75" href="source/net/ipv4/inet_hashtables.c#L75">75</a>         }
 <a name="L76" href="source/net/ipv4/inet_hashtables.c#L76">76</a>         return <a href="ident?i=tb">tb</a>;
 <a name="L77" href="source/net/ipv4/inet_hashtables.c#L77">77</a> }
 <a name="L78" href="source/net/ipv4/inet_hashtables.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/inet_hashtables.c#L79">79</a> <b><i>/*</i></b>
 <a name="L80" href="source/net/ipv4/inet_hashtables.c#L80">80</a> <b><i> * Caller must hold hashbucket lock for this tb with local BH disabled</i></b>
 <a name="L81" href="source/net/ipv4/inet_hashtables.c#L81">81</a> <b><i> */</i></b>
 <a name="L82" href="source/net/ipv4/inet_hashtables.c#L82">82</a> void <a href="ident?i=inet_bind_bucket_destroy">inet_bind_bucket_destroy</a>(struct <a href="ident?i=kmem_cache">kmem_cache</a> *cachep, struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>)
 <a name="L83" href="source/net/ipv4/inet_hashtables.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/inet_hashtables.c#L84">84</a>         if (<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;owners)) {
 <a name="L85" href="source/net/ipv4/inet_hashtables.c#L85">85</a>                 <a href="ident?i=__hlist_del">__hlist_del</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=node">node</a>);
 <a name="L86" href="source/net/ipv4/inet_hashtables.c#L86">86</a>                 <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(cachep, <a href="ident?i=tb">tb</a>);
 <a name="L87" href="source/net/ipv4/inet_hashtables.c#L87">87</a>         }
 <a name="L88" href="source/net/ipv4/inet_hashtables.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/inet_hashtables.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/inet_hashtables.c#L90">90</a> void <a href="ident?i=inet_bind_hash">inet_bind_hash</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>,
 <a name="L91" href="source/net/ipv4/inet_hashtables.c#L91">91</a>                     const unsigned short snum)
 <a name="L92" href="source/net/ipv4/inet_hashtables.c#L92">92</a> {
 <a name="L93" href="source/net/ipv4/inet_hashtables.c#L93">93</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
 <a name="L94" href="source/net/ipv4/inet_hashtables.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/inet_hashtables.c#L95">95</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;hashinfo-&gt;bsockets);
 <a name="L96" href="source/net/ipv4/inet_hashtables.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/inet_hashtables.c#L97">97</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> = snum;
 <a name="L98" href="source/net/ipv4/inet_hashtables.c#L98">98</a>         <a href="ident?i=sk_add_bind_node">sk_add_bind_node</a>(sk, &amp;<a href="ident?i=tb">tb</a>-&gt;owners);
 <a name="L99" href="source/net/ipv4/inet_hashtables.c#L99">99</a>         <a href="ident?i=tb">tb</a>-&gt;num_owners++;
<a name="L100" href="source/net/ipv4/inet_hashtables.c#L100">100</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash = <a href="ident?i=tb">tb</a>;
<a name="L101" href="source/net/ipv4/inet_hashtables.c#L101">101</a> }
<a name="L102" href="source/net/ipv4/inet_hashtables.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/inet_hashtables.c#L103">103</a> <b><i>/*</i></b>
<a name="L104" href="source/net/ipv4/inet_hashtables.c#L104">104</a> <b><i> * Get rid of any references to a local port held by the given sock.</i></b>
<a name="L105" href="source/net/ipv4/inet_hashtables.c#L105">105</a> <b><i> */</i></b>
<a name="L106" href="source/net/ipv4/inet_hashtables.c#L106">106</a> static void <a href="ident?i=__inet_put_port">__inet_put_port</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L107" href="source/net/ipv4/inet_hashtables.c#L107">107</a> {
<a name="L108" href="source/net/ipv4/inet_hashtables.c#L108">108</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
<a name="L109" href="source/net/ipv4/inet_hashtables.c#L109">109</a>         const int bhash = <a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a>,
<a name="L110" href="source/net/ipv4/inet_hashtables.c#L110">110</a>                         hashinfo-&gt;bhash_size);
<a name="L111" href="source/net/ipv4/inet_hashtables.c#L111">111</a>         struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *<a href="ident?i=head">head</a> = &amp;hashinfo-&gt;bhash[bhash];
<a name="L112" href="source/net/ipv4/inet_hashtables.c#L112">112</a>         struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>;
<a name="L113" href="source/net/ipv4/inet_hashtables.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/inet_hashtables.c#L114">114</a>         <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;hashinfo-&gt;bsockets);
<a name="L115" href="source/net/ipv4/inet_hashtables.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/inet_hashtables.c#L116">116</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L117" href="source/net/ipv4/inet_hashtables.c#L117">117</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash;
<a name="L118" href="source/net/ipv4/inet_hashtables.c#L118">118</a>         <a href="ident?i=__sk_del_bind_node">__sk_del_bind_node</a>(sk);
<a name="L119" href="source/net/ipv4/inet_hashtables.c#L119">119</a>         <a href="ident?i=tb">tb</a>-&gt;num_owners--;
<a name="L120" href="source/net/ipv4/inet_hashtables.c#L120">120</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash = <a href="ident?i=NULL">NULL</a>;
<a name="L121" href="source/net/ipv4/inet_hashtables.c#L121">121</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> = 0;
<a name="L122" href="source/net/ipv4/inet_hashtables.c#L122">122</a>         <a href="ident?i=inet_bind_bucket_destroy">inet_bind_bucket_destroy</a>(hashinfo-&gt;bind_bucket_cachep, <a href="ident?i=tb">tb</a>);
<a name="L123" href="source/net/ipv4/inet_hashtables.c#L123">123</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L124" href="source/net/ipv4/inet_hashtables.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/inet_hashtables.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/inet_hashtables.c#L126">126</a> void <a href="ident?i=inet_put_port">inet_put_port</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L127" href="source/net/ipv4/inet_hashtables.c#L127">127</a> {
<a name="L128" href="source/net/ipv4/inet_hashtables.c#L128">128</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L129" href="source/net/ipv4/inet_hashtables.c#L129">129</a>         <a href="ident?i=__inet_put_port">__inet_put_port</a>(sk);
<a name="L130" href="source/net/ipv4/inet_hashtables.c#L130">130</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L131" href="source/net/ipv4/inet_hashtables.c#L131">131</a> }
<a name="L132" href="source/net/ipv4/inet_hashtables.c#L132">132</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_put_port">inet_put_port</a>);
<a name="L133" href="source/net/ipv4/inet_hashtables.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/inet_hashtables.c#L134">134</a> int <a href="ident?i=__inet_inherit_port">__inet_inherit_port</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sock">sock</a> *<a href="ident?i=child">child</a>)
<a name="L135" href="source/net/ipv4/inet_hashtables.c#L135">135</a> {
<a name="L136" href="source/net/ipv4/inet_hashtables.c#L136">136</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *<a href="ident?i=table">table</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
<a name="L137" href="source/net/ipv4/inet_hashtables.c#L137">137</a>         unsigned short <a href="ident?i=port">port</a> = <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=child">child</a>)-&gt;<a href="ident?i=inet_num">inet_num</a>;
<a name="L138" href="source/net/ipv4/inet_hashtables.c#L138">138</a>         const int bhash = <a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=port">port</a>,
<a name="L139" href="source/net/ipv4/inet_hashtables.c#L139">139</a>                         <a href="ident?i=table">table</a>-&gt;bhash_size);
<a name="L140" href="source/net/ipv4/inet_hashtables.c#L140">140</a>         struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=table">table</a>-&gt;bhash[bhash];
<a name="L141" href="source/net/ipv4/inet_hashtables.c#L141">141</a>         struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>;
<a name="L142" href="source/net/ipv4/inet_hashtables.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/inet_hashtables.c#L143">143</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L144" href="source/net/ipv4/inet_hashtables.c#L144">144</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash;
<a name="L145" href="source/net/ipv4/inet_hashtables.c#L145">145</a>         if (<a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=port">port</a> != <a href="ident?i=port">port</a>) {
<a name="L146" href="source/net/ipv4/inet_hashtables.c#L146">146</a>                 <b><i>/* NOTE: using tproxy and redirecting skbs to a proxy</i></b>
<a name="L147" href="source/net/ipv4/inet_hashtables.c#L147">147</a> <b><i>                 * on a different listener port breaks the assumption</i></b>
<a name="L148" href="source/net/ipv4/inet_hashtables.c#L148">148</a> <b><i>                 * that the listener socket's icsk_bind_hash is the same</i></b>
<a name="L149" href="source/net/ipv4/inet_hashtables.c#L149">149</a> <b><i>                 * as that of the child socket. We have to look up or</i></b>
<a name="L150" href="source/net/ipv4/inet_hashtables.c#L150">150</a> <b><i>                 * create a new bind bucket for the child here. */</i></b>
<a name="L151" href="source/net/ipv4/inet_hashtables.c#L151">151</a>                 <a href="ident?i=inet_bind_bucket_for_each">inet_bind_bucket_for_each</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>) {
<a name="L152" href="source/net/ipv4/inet_hashtables.c#L152">152</a>                         if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=ib_net">ib_net</a>(<a href="ident?i=tb">tb</a>), <a href="ident?i=sock_net">sock_net</a>(sk)) &amp;&amp;
<a name="L153" href="source/net/ipv4/inet_hashtables.c#L153">153</a>                             <a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=port">port</a> == <a href="ident?i=port">port</a>)
<a name="L154" href="source/net/ipv4/inet_hashtables.c#L154">154</a>                                 break;
<a name="L155" href="source/net/ipv4/inet_hashtables.c#L155">155</a>                 }
<a name="L156" href="source/net/ipv4/inet_hashtables.c#L156">156</a>                 if (!<a href="ident?i=tb">tb</a>) {
<a name="L157" href="source/net/ipv4/inet_hashtables.c#L157">157</a>                         <a href="ident?i=tb">tb</a> = <a href="ident?i=inet_bind_bucket_create">inet_bind_bucket_create</a>(<a href="ident?i=table">table</a>-&gt;bind_bucket_cachep,
<a name="L158" href="source/net/ipv4/inet_hashtables.c#L158">158</a>                                                      <a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=head">head</a>, <a href="ident?i=port">port</a>);
<a name="L159" href="source/net/ipv4/inet_hashtables.c#L159">159</a>                         if (!<a href="ident?i=tb">tb</a>) {
<a name="L160" href="source/net/ipv4/inet_hashtables.c#L160">160</a>                                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L161" href="source/net/ipv4/inet_hashtables.c#L161">161</a>                                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L162" href="source/net/ipv4/inet_hashtables.c#L162">162</a>                         }
<a name="L163" href="source/net/ipv4/inet_hashtables.c#L163">163</a>                 }
<a name="L164" href="source/net/ipv4/inet_hashtables.c#L164">164</a>         }
<a name="L165" href="source/net/ipv4/inet_hashtables.c#L165">165</a>         <a href="ident?i=inet_bind_hash">inet_bind_hash</a>(<a href="ident?i=child">child</a>, <a href="ident?i=tb">tb</a>, <a href="ident?i=port">port</a>);
<a name="L166" href="source/net/ipv4/inet_hashtables.c#L166">166</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L167" href="source/net/ipv4/inet_hashtables.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/inet_hashtables.c#L168">168</a>         return 0;
<a name="L169" href="source/net/ipv4/inet_hashtables.c#L169">169</a> }
<a name="L170" href="source/net/ipv4/inet_hashtables.c#L170">170</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__inet_inherit_port">__inet_inherit_port</a>);
<a name="L171" href="source/net/ipv4/inet_hashtables.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/inet_hashtables.c#L172">172</a> static inline int <a href="ident?i=compute_score">compute_score</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L173" href="source/net/ipv4/inet_hashtables.c#L173">173</a>                                 const unsigned short hnum, const <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>,
<a name="L174" href="source/net/ipv4/inet_hashtables.c#L174">174</a>                                 const int dif)
<a name="L175" href="source/net/ipv4/inet_hashtables.c#L175">175</a> {
<a name="L176" href="source/net/ipv4/inet_hashtables.c#L176">176</a>         int <a href="ident?i=score">score</a> = -1;
<a name="L177" href="source/net/ipv4/inet_hashtables.c#L177">177</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L178" href="source/net/ipv4/inet_hashtables.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/inet_hashtables.c#L179">179</a>         if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) &amp;&amp; inet-&gt;<a href="ident?i=inet_num">inet_num</a> == hnum &amp;&amp;
<a name="L180" href="source/net/ipv4/inet_hashtables.c#L180">180</a>                         !<a href="ident?i=ipv6_only_sock">ipv6_only_sock</a>(sk)) {
<a name="L181" href="source/net/ipv4/inet_hashtables.c#L181">181</a>                 <a href="ident?i=__be32">__be32</a> rcv_saddr = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L182" href="source/net/ipv4/inet_hashtables.c#L182">182</a>                 <a href="ident?i=score">score</a> = sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=PF_INET">PF_INET</a> ? 2 : 1;
<a name="L183" href="source/net/ipv4/inet_hashtables.c#L183">183</a>                 if (rcv_saddr) {
<a name="L184" href="source/net/ipv4/inet_hashtables.c#L184">184</a>                         if (rcv_saddr != <a href="ident?i=daddr">daddr</a>)
<a name="L185" href="source/net/ipv4/inet_hashtables.c#L185">185</a>                                 return -1;
<a name="L186" href="source/net/ipv4/inet_hashtables.c#L186">186</a>                         <a href="ident?i=score">score</a> += 4;
<a name="L187" href="source/net/ipv4/inet_hashtables.c#L187">187</a>                 }
<a name="L188" href="source/net/ipv4/inet_hashtables.c#L188">188</a>                 if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>) {
<a name="L189" href="source/net/ipv4/inet_hashtables.c#L189">189</a>                         if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> != dif)
<a name="L190" href="source/net/ipv4/inet_hashtables.c#L190">190</a>                                 return -1;
<a name="L191" href="source/net/ipv4/inet_hashtables.c#L191">191</a>                         <a href="ident?i=score">score</a> += 4;
<a name="L192" href="source/net/ipv4/inet_hashtables.c#L192">192</a>                 }
<a name="L193" href="source/net/ipv4/inet_hashtables.c#L193">193</a>         }
<a name="L194" href="source/net/ipv4/inet_hashtables.c#L194">194</a>         return <a href="ident?i=score">score</a>;
<a name="L195" href="source/net/ipv4/inet_hashtables.c#L195">195</a> }
<a name="L196" href="source/net/ipv4/inet_hashtables.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/inet_hashtables.c#L197">197</a> <b><i>/*</i></b>
<a name="L198" href="source/net/ipv4/inet_hashtables.c#L198">198</a> <b><i> * Don't inline this cruft. Here are some nice properties to exploit here. The</i></b>
<a name="L199" href="source/net/ipv4/inet_hashtables.c#L199">199</a> <b><i> * BSD API does not allow a listening sock to specify the remote port nor the</i></b>
<a name="L200" href="source/net/ipv4/inet_hashtables.c#L200">200</a> <b><i> * remote address for the connection. So always assume those are both</i></b>
<a name="L201" href="source/net/ipv4/inet_hashtables.c#L201">201</a> <b><i> * wildcarded during the search since they can never be otherwise.</i></b>
<a name="L202" href="source/net/ipv4/inet_hashtables.c#L202">202</a> <b><i> */</i></b>
<a name="L203" href="source/net/ipv4/inet_hashtables.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/inet_hashtables.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/inet_hashtables.c#L205">205</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__inet_lookup_listener">__inet_lookup_listener</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L206" href="source/net/ipv4/inet_hashtables.c#L206">206</a>                                     struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo,
<a name="L207" href="source/net/ipv4/inet_hashtables.c#L207">207</a>                                     const <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be16">__be16</a> sport,
<a name="L208" href="source/net/ipv4/inet_hashtables.c#L208">208</a>                                     const <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, const unsigned short hnum,
<a name="L209" href="source/net/ipv4/inet_hashtables.c#L209">209</a>                                     const int dif)
<a name="L210" href="source/net/ipv4/inet_hashtables.c#L210">210</a> {
<a name="L211" href="source/net/ipv4/inet_hashtables.c#L211">211</a>         struct <a href="ident?i=sock">sock</a> *sk, *<a href="ident?i=result">result</a>;
<a name="L212" href="source/net/ipv4/inet_hashtables.c#L212">212</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L213" href="source/net/ipv4/inet_hashtables.c#L213">213</a>         unsigned int <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_lhashfn">inet_lhashfn</a>(<a href="ident?i=net">net</a>, hnum);
<a name="L214" href="source/net/ipv4/inet_hashtables.c#L214">214</a>         struct <a href="ident?i=inet_listen_hashbucket">inet_listen_hashbucket</a> *ilb = &amp;hashinfo-&gt;listening_hash[<a href="ident?i=hash">hash</a>];
<a name="L215" href="source/net/ipv4/inet_hashtables.c#L215">215</a>         int <a href="ident?i=score">score</a>, hiscore, <a href="ident?i=matches">matches</a> = 0, reuseport = 0;
<a name="L216" href="source/net/ipv4/inet_hashtables.c#L216">216</a>         <a href="ident?i=u32">u32</a> phash = 0;
<a name="L217" href="source/net/ipv4/inet_hashtables.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/inet_hashtables.c#L218">218</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L219" href="source/net/ipv4/inet_hashtables.c#L219">219</a> begin:
<a name="L220" href="source/net/ipv4/inet_hashtables.c#L220">220</a>         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L221" href="source/net/ipv4/inet_hashtables.c#L221">221</a>         hiscore = 0;
<a name="L222" href="source/net/ipv4/inet_hashtables.c#L222">222</a>         <a href="ident?i=sk_nulls_for_each_rcu">sk_nulls_for_each_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;ilb-&gt;<a href="ident?i=head">head</a>) {
<a name="L223" href="source/net/ipv4/inet_hashtables.c#L223">223</a>                 <a href="ident?i=score">score</a> = <a href="ident?i=compute_score">compute_score</a>(sk, <a href="ident?i=net">net</a>, hnum, <a href="ident?i=daddr">daddr</a>, dif);
<a name="L224" href="source/net/ipv4/inet_hashtables.c#L224">224</a>                 if (<a href="ident?i=score">score</a> &gt; hiscore) {
<a name="L225" href="source/net/ipv4/inet_hashtables.c#L225">225</a>                         <a href="ident?i=result">result</a> = sk;
<a name="L226" href="source/net/ipv4/inet_hashtables.c#L226">226</a>                         hiscore = <a href="ident?i=score">score</a>;
<a name="L227" href="source/net/ipv4/inet_hashtables.c#L227">227</a>                         reuseport = sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a>;
<a name="L228" href="source/net/ipv4/inet_hashtables.c#L228">228</a>                         if (reuseport) {
<a name="L229" href="source/net/ipv4/inet_hashtables.c#L229">229</a>                                 phash = <a href="ident?i=inet_ehashfn">inet_ehashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, hnum,
<a name="L230" href="source/net/ipv4/inet_hashtables.c#L230">230</a>                                                      <a href="ident?i=saddr">saddr</a>, sport);
<a name="L231" href="source/net/ipv4/inet_hashtables.c#L231">231</a>                                 <a href="ident?i=matches">matches</a> = 1;
<a name="L232" href="source/net/ipv4/inet_hashtables.c#L232">232</a>                         }
<a name="L233" href="source/net/ipv4/inet_hashtables.c#L233">233</a>                 } else if (<a href="ident?i=score">score</a> == hiscore &amp;&amp; reuseport) {
<a name="L234" href="source/net/ipv4/inet_hashtables.c#L234">234</a>                         <a href="ident?i=matches">matches</a>++;
<a name="L235" href="source/net/ipv4/inet_hashtables.c#L235">235</a>                         if (<a href="ident?i=reciprocal_scale">reciprocal_scale</a>(phash, <a href="ident?i=matches">matches</a>) == 0)
<a name="L236" href="source/net/ipv4/inet_hashtables.c#L236">236</a>                                 <a href="ident?i=result">result</a> = sk;
<a name="L237" href="source/net/ipv4/inet_hashtables.c#L237">237</a>                         phash = <a href="ident?i=next_pseudo_random32">next_pseudo_random32</a>(phash);
<a name="L238" href="source/net/ipv4/inet_hashtables.c#L238">238</a>                 }
<a name="L239" href="source/net/ipv4/inet_hashtables.c#L239">239</a>         }
<a name="L240" href="source/net/ipv4/inet_hashtables.c#L240">240</a>         <b><i>/*</i></b>
<a name="L241" href="source/net/ipv4/inet_hashtables.c#L241">241</a> <b><i>         * if the nulls value we got at the end of this lookup is</i></b>
<a name="L242" href="source/net/ipv4/inet_hashtables.c#L242">242</a> <b><i>         * not the expected one, we must restart lookup.</i></b>
<a name="L243" href="source/net/ipv4/inet_hashtables.c#L243">243</a> <b><i>         * We probably met an item that was moved to another chain.</i></b>
<a name="L244" href="source/net/ipv4/inet_hashtables.c#L244">244</a> <b><i>         */</i></b>
<a name="L245" href="source/net/ipv4/inet_hashtables.c#L245">245</a>         if (<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=node">node</a>) != <a href="ident?i=hash">hash</a> + <a href="ident?i=LISTENING_NULLS_BASE">LISTENING_NULLS_BASE</a>)
<a name="L246" href="source/net/ipv4/inet_hashtables.c#L246">246</a>                 goto begin;
<a name="L247" href="source/net/ipv4/inet_hashtables.c#L247">247</a>         if (<a href="ident?i=result">result</a>) {
<a name="L248" href="source/net/ipv4/inet_hashtables.c#L248">248</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;<a href="ident?i=result">result</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>)))
<a name="L249" href="source/net/ipv4/inet_hashtables.c#L249">249</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L250" href="source/net/ipv4/inet_hashtables.c#L250">250</a>                 else if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=compute_score">compute_score</a>(<a href="ident?i=result">result</a>, <a href="ident?i=net">net</a>, hnum, <a href="ident?i=daddr">daddr</a>,
<a name="L251" href="source/net/ipv4/inet_hashtables.c#L251">251</a>                                   dif) &lt; hiscore)) {
<a name="L252" href="source/net/ipv4/inet_hashtables.c#L252">252</a>                         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=result">result</a>);
<a name="L253" href="source/net/ipv4/inet_hashtables.c#L253">253</a>                         goto begin;
<a name="L254" href="source/net/ipv4/inet_hashtables.c#L254">254</a>                 }
<a name="L255" href="source/net/ipv4/inet_hashtables.c#L255">255</a>         }
<a name="L256" href="source/net/ipv4/inet_hashtables.c#L256">256</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L257" href="source/net/ipv4/inet_hashtables.c#L257">257</a>         return <a href="ident?i=result">result</a>;
<a name="L258" href="source/net/ipv4/inet_hashtables.c#L258">258</a> }
<a name="L259" href="source/net/ipv4/inet_hashtables.c#L259">259</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__inet_lookup_listener">__inet_lookup_listener</a>);
<a name="L260" href="source/net/ipv4/inet_hashtables.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/inet_hashtables.c#L261">261</a> <b><i>/* All sockets share common refcount, but have different destructors */</i></b>
<a name="L262" href="source/net/ipv4/inet_hashtables.c#L262">262</a> void <a href="ident?i=sock_gen_put">sock_gen_put</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L263" href="source/net/ipv4/inet_hashtables.c#L263">263</a> {
<a name="L264" href="source/net/ipv4/inet_hashtables.c#L264">264</a>         if (!<a href="ident?i=atomic_dec_and_test">atomic_dec_and_test</a>(&amp;sk-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>))
<a name="L265" href="source/net/ipv4/inet_hashtables.c#L265">265</a>                 return;
<a name="L266" href="source/net/ipv4/inet_hashtables.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/inet_hashtables.c#L267">267</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT)
<a name="L268" href="source/net/ipv4/inet_hashtables.c#L268">268</a>                 <a href="ident?i=inet_twsk_free">inet_twsk_free</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L269" href="source/net/ipv4/inet_hashtables.c#L269">269</a>         else if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_NEW_SYN_RECV)
<a name="L270" href="source/net/ipv4/inet_hashtables.c#L270">270</a>                 <a href="ident?i=reqsk_free">reqsk_free</a>(<a href="ident?i=inet_reqsk">inet_reqsk</a>(sk));
<a name="L271" href="source/net/ipv4/inet_hashtables.c#L271">271</a>         else
<a name="L272" href="source/net/ipv4/inet_hashtables.c#L272">272</a>                 <a href="ident?i=sk_free">sk_free</a>(sk);
<a name="L273" href="source/net/ipv4/inet_hashtables.c#L273">273</a> }
<a name="L274" href="source/net/ipv4/inet_hashtables.c#L274">274</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=sock_gen_put">sock_gen_put</a>);
<a name="L275" href="source/net/ipv4/inet_hashtables.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/inet_hashtables.c#L276">276</a> void <a href="ident?i=sock_edemux">sock_edemux</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L277" href="source/net/ipv4/inet_hashtables.c#L277">277</a> {
<a name="L278" href="source/net/ipv4/inet_hashtables.c#L278">278</a>         <a href="ident?i=sock_gen_put">sock_gen_put</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L279" href="source/net/ipv4/inet_hashtables.c#L279">279</a> }
<a name="L280" href="source/net/ipv4/inet_hashtables.c#L280">280</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sock_edemux">sock_edemux</a>);
<a name="L281" href="source/net/ipv4/inet_hashtables.c#L281">281</a> 
<a name="L282" href="source/net/ipv4/inet_hashtables.c#L282">282</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__inet_lookup_established">__inet_lookup_established</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L283" href="source/net/ipv4/inet_hashtables.c#L283">283</a>                                   struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo,
<a name="L284" href="source/net/ipv4/inet_hashtables.c#L284">284</a>                                   const <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, const <a href="ident?i=__be16">__be16</a> sport,
<a name="L285" href="source/net/ipv4/inet_hashtables.c#L285">285</a>                                   const <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, const <a href="ident?i=u16">u16</a> hnum,
<a name="L286" href="source/net/ipv4/inet_hashtables.c#L286">286</a>                                   const int dif)
<a name="L287" href="source/net/ipv4/inet_hashtables.c#L287">287</a> {
<a name="L288" href="source/net/ipv4/inet_hashtables.c#L288">288</a>         <a href="ident?i=INET_ADDR_COOKIE">INET_ADDR_COOKIE</a>(acookie, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>);
<a name="L289" href="source/net/ipv4/inet_hashtables.c#L289">289</a>         const <a href="ident?i=__portpair">__portpair</a> <a href="ident?i=ports">ports</a> = <a href="ident?i=INET_COMBINED_PORTS">INET_COMBINED_PORTS</a>(sport, hnum);
<a name="L290" href="source/net/ipv4/inet_hashtables.c#L290">290</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L291" href="source/net/ipv4/inet_hashtables.c#L291">291</a>         const struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L292" href="source/net/ipv4/inet_hashtables.c#L292">292</a>         <b><i>/* Optimize here for direct hit, only listening connections can</i></b>
<a name="L293" href="source/net/ipv4/inet_hashtables.c#L293">293</a> <b><i>         * have wildcards anyways.</i></b>
<a name="L294" href="source/net/ipv4/inet_hashtables.c#L294">294</a> <b><i>         */</i></b>
<a name="L295" href="source/net/ipv4/inet_hashtables.c#L295">295</a>         unsigned int <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_ehashfn">inet_ehashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, hnum, <a href="ident?i=saddr">saddr</a>, sport);
<a name="L296" href="source/net/ipv4/inet_hashtables.c#L296">296</a>         unsigned int <a href="ident?i=slot">slot</a> = <a href="ident?i=hash">hash</a> &amp; hashinfo-&gt;ehash_mask;
<a name="L297" href="source/net/ipv4/inet_hashtables.c#L297">297</a>         struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a> *<a href="ident?i=head">head</a> = &amp;hashinfo-&gt;ehash[<a href="ident?i=slot">slot</a>];
<a name="L298" href="source/net/ipv4/inet_hashtables.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/inet_hashtables.c#L299">299</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L300" href="source/net/ipv4/inet_hashtables.c#L300">300</a> begin:
<a name="L301" href="source/net/ipv4/inet_hashtables.c#L301">301</a>         <a href="ident?i=sk_nulls_for_each_rcu">sk_nulls_for_each_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>) {
<a name="L302" href="source/net/ipv4/inet_hashtables.c#L302">302</a>                 if (sk-&gt;<a href="ident?i=sk_hash">sk_hash</a> != <a href="ident?i=hash">hash</a>)
<a name="L303" href="source/net/ipv4/inet_hashtables.c#L303">303</a>                         continue;
<a name="L304" href="source/net/ipv4/inet_hashtables.c#L304">304</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=INET_MATCH">INET_MATCH</a>(sk, <a href="ident?i=net">net</a>, acookie,
<a name="L305" href="source/net/ipv4/inet_hashtables.c#L305">305</a>                                       <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=ports">ports</a>, dif))) {
<a name="L306" href="source/net/ipv4/inet_hashtables.c#L306">306</a>                         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;sk-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>)))
<a name="L307" href="source/net/ipv4/inet_hashtables.c#L307">307</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L308" href="source/net/ipv4/inet_hashtables.c#L308">308</a>                         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=INET_MATCH">INET_MATCH</a>(sk, <a href="ident?i=net">net</a>, acookie,
<a name="L309" href="source/net/ipv4/inet_hashtables.c#L309">309</a>                                                  <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=ports">ports</a>, dif))) {
<a name="L310" href="source/net/ipv4/inet_hashtables.c#L310">310</a>                                 <a href="ident?i=sock_gen_put">sock_gen_put</a>(sk);
<a name="L311" href="source/net/ipv4/inet_hashtables.c#L311">311</a>                                 goto begin;
<a name="L312" href="source/net/ipv4/inet_hashtables.c#L312">312</a>                         }
<a name="L313" href="source/net/ipv4/inet_hashtables.c#L313">313</a>                         goto <a href="ident?i=found">found</a>;
<a name="L314" href="source/net/ipv4/inet_hashtables.c#L314">314</a>                 }
<a name="L315" href="source/net/ipv4/inet_hashtables.c#L315">315</a>         }
<a name="L316" href="source/net/ipv4/inet_hashtables.c#L316">316</a>         <b><i>/*</i></b>
<a name="L317" href="source/net/ipv4/inet_hashtables.c#L317">317</a> <b><i>         * if the nulls value we got at the end of this lookup is</i></b>
<a name="L318" href="source/net/ipv4/inet_hashtables.c#L318">318</a> <b><i>         * not the expected one, we must restart lookup.</i></b>
<a name="L319" href="source/net/ipv4/inet_hashtables.c#L319">319</a> <b><i>         * We probably met an item that was moved to another chain.</i></b>
<a name="L320" href="source/net/ipv4/inet_hashtables.c#L320">320</a> <b><i>         */</i></b>
<a name="L321" href="source/net/ipv4/inet_hashtables.c#L321">321</a>         if (<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=node">node</a>) != <a href="ident?i=slot">slot</a>)
<a name="L322" href="source/net/ipv4/inet_hashtables.c#L322">322</a>                 goto begin;
<a name="L323" href="source/net/ipv4/inet_hashtables.c#L323">323</a> <a href="ident?i=out">out</a>:
<a name="L324" href="source/net/ipv4/inet_hashtables.c#L324">324</a>         sk = <a href="ident?i=NULL">NULL</a>;
<a name="L325" href="source/net/ipv4/inet_hashtables.c#L325">325</a> <a href="ident?i=found">found</a>:
<a name="L326" href="source/net/ipv4/inet_hashtables.c#L326">326</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L327" href="source/net/ipv4/inet_hashtables.c#L327">327</a>         return sk;
<a name="L328" href="source/net/ipv4/inet_hashtables.c#L328">328</a> }
<a name="L329" href="source/net/ipv4/inet_hashtables.c#L329">329</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__inet_lookup_established">__inet_lookup_established</a>);
<a name="L330" href="source/net/ipv4/inet_hashtables.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/inet_hashtables.c#L331">331</a> <b><i>/* called with local bh disabled */</i></b>
<a name="L332" href="source/net/ipv4/inet_hashtables.c#L332">332</a> static int <a href="ident?i=__inet_check_established">__inet_check_established</a>(struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> *death_row,
<a name="L333" href="source/net/ipv4/inet_hashtables.c#L333">333</a>                                     struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=__u16">__u16</a> lport,
<a name="L334" href="source/net/ipv4/inet_hashtables.c#L334">334</a>                                     struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> **twp)
<a name="L335" href="source/net/ipv4/inet_hashtables.c#L335">335</a> {
<a name="L336" href="source/net/ipv4/inet_hashtables.c#L336">336</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hinfo = death_row-&gt;hashinfo;
<a name="L337" href="source/net/ipv4/inet_hashtables.c#L337">337</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L338" href="source/net/ipv4/inet_hashtables.c#L338">338</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L339" href="source/net/ipv4/inet_hashtables.c#L339">339</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L340" href="source/net/ipv4/inet_hashtables.c#L340">340</a>         int dif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L341" href="source/net/ipv4/inet_hashtables.c#L341">341</a>         <a href="ident?i=INET_ADDR_COOKIE">INET_ADDR_COOKIE</a>(acookie, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>);
<a name="L342" href="source/net/ipv4/inet_hashtables.c#L342">342</a>         const <a href="ident?i=__portpair">__portpair</a> <a href="ident?i=ports">ports</a> = <a href="ident?i=INET_COMBINED_PORTS">INET_COMBINED_PORTS</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>, lport);
<a name="L343" href="source/net/ipv4/inet_hashtables.c#L343">343</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L344" href="source/net/ipv4/inet_hashtables.c#L344">344</a>         unsigned int <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_ehashfn">inet_ehashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, lport,
<a name="L345" href="source/net/ipv4/inet_hashtables.c#L345">345</a>                                          <a href="ident?i=saddr">saddr</a>, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>);
<a name="L346" href="source/net/ipv4/inet_hashtables.c#L346">346</a>         struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a> *<a href="ident?i=head">head</a> = <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a>(hinfo, <a href="ident?i=hash">hash</a>);
<a name="L347" href="source/net/ipv4/inet_hashtables.c#L347">347</a>         <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(hinfo, <a href="ident?i=hash">hash</a>);
<a name="L348" href="source/net/ipv4/inet_hashtables.c#L348">348</a>         struct <a href="ident?i=sock">sock</a> *sk2;
<a name="L349" href="source/net/ipv4/inet_hashtables.c#L349">349</a>         const struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L350" href="source/net/ipv4/inet_hashtables.c#L350">350</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L351" href="source/net/ipv4/inet_hashtables.c#L351">351</a>         int twrefcnt = 0;
<a name="L352" href="source/net/ipv4/inet_hashtables.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/inet_hashtables.c#L353">353</a>         <a href="ident?i=spin_lock">spin_lock</a>(<a href="ident?i=lock">lock</a>);
<a name="L354" href="source/net/ipv4/inet_hashtables.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/inet_hashtables.c#L355">355</a>         <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk2, <a href="ident?i=node">node</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>) {
<a name="L356" href="source/net/ipv4/inet_hashtables.c#L356">356</a>                 if (sk2-&gt;<a href="ident?i=sk_hash">sk_hash</a> != <a href="ident?i=hash">hash</a>)
<a name="L357" href="source/net/ipv4/inet_hashtables.c#L357">357</a>                         continue;
<a name="L358" href="source/net/ipv4/inet_hashtables.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/inet_hashtables.c#L359">359</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=INET_MATCH">INET_MATCH</a>(sk2, <a href="ident?i=net">net</a>, acookie,
<a name="L360" href="source/net/ipv4/inet_hashtables.c#L360">360</a>                                          <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=ports">ports</a>, dif))) {
<a name="L361" href="source/net/ipv4/inet_hashtables.c#L361">361</a>                         if (sk2-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT) {
<a name="L362" href="source/net/ipv4/inet_hashtables.c#L362">362</a>                                 <a href="ident?i=tw">tw</a> = <a href="ident?i=inet_twsk">inet_twsk</a>(sk2);
<a name="L363" href="source/net/ipv4/inet_hashtables.c#L363">363</a>                                 if (<a href="ident?i=twsk_unique">twsk_unique</a>(sk, sk2, twp))
<a name="L364" href="source/net/ipv4/inet_hashtables.c#L364">364</a>                                         break;
<a name="L365" href="source/net/ipv4/inet_hashtables.c#L365">365</a>                         }
<a name="L366" href="source/net/ipv4/inet_hashtables.c#L366">366</a>                         goto not_unique;
<a name="L367" href="source/net/ipv4/inet_hashtables.c#L367">367</a>                 }
<a name="L368" href="source/net/ipv4/inet_hashtables.c#L368">368</a>         }
<a name="L369" href="source/net/ipv4/inet_hashtables.c#L369">369</a> 
<a name="L370" href="source/net/ipv4/inet_hashtables.c#L370">370</a>         <b><i>/* Must record num and sport now. Otherwise we will see</i></b>
<a name="L371" href="source/net/ipv4/inet_hashtables.c#L371">371</a> <b><i>         * in hash table socket with a funny identity.</i></b>
<a name="L372" href="source/net/ipv4/inet_hashtables.c#L372">372</a> <b><i>         */</i></b>
<a name="L373" href="source/net/ipv4/inet_hashtables.c#L373">373</a>         inet-&gt;<a href="ident?i=inet_num">inet_num</a> = lport;
<a name="L374" href="source/net/ipv4/inet_hashtables.c#L374">374</a>         inet-&gt;inet_sport = <a href="ident?i=htons">htons</a>(lport);
<a name="L375" href="source/net/ipv4/inet_hashtables.c#L375">375</a>         sk-&gt;<a href="ident?i=sk_hash">sk_hash</a> = <a href="ident?i=hash">hash</a>;
<a name="L376" href="source/net/ipv4/inet_hashtables.c#L376">376</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk));
<a name="L377" href="source/net/ipv4/inet_hashtables.c#L377">377</a>         <a href="ident?i=__sk_nulls_add_node_rcu">__sk_nulls_add_node_rcu</a>(sk, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>);
<a name="L378" href="source/net/ipv4/inet_hashtables.c#L378">378</a>         if (<a href="ident?i=tw">tw</a>) {
<a name="L379" href="source/net/ipv4/inet_hashtables.c#L379">379</a>                 twrefcnt = <a href="ident?i=inet_twsk_unhash">inet_twsk_unhash</a>(<a href="ident?i=tw">tw</a>);
<a name="L380" href="source/net/ipv4/inet_hashtables.c#L380">380</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_TIMEWAITRECYCLED);
<a name="L381" href="source/net/ipv4/inet_hashtables.c#L381">381</a>         }
<a name="L382" href="source/net/ipv4/inet_hashtables.c#L382">382</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(<a href="ident?i=lock">lock</a>);
<a name="L383" href="source/net/ipv4/inet_hashtables.c#L383">383</a>         if (twrefcnt)
<a name="L384" href="source/net/ipv4/inet_hashtables.c#L384">384</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L385" href="source/net/ipv4/inet_hashtables.c#L385">385</a>         <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, 1);
<a name="L386" href="source/net/ipv4/inet_hashtables.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/inet_hashtables.c#L387">387</a>         if (twp) {
<a name="L388" href="source/net/ipv4/inet_hashtables.c#L388">388</a>                 *twp = <a href="ident?i=tw">tw</a>;
<a name="L389" href="source/net/ipv4/inet_hashtables.c#L389">389</a>         } else if (<a href="ident?i=tw">tw</a>) {
<a name="L390" href="source/net/ipv4/inet_hashtables.c#L390">390</a>                 <b><i>/* Silly. Should hash-dance instead... */</i></b>
<a name="L391" href="source/net/ipv4/inet_hashtables.c#L391">391</a>                 <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(<a href="ident?i=tw">tw</a>);
<a name="L392" href="source/net/ipv4/inet_hashtables.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/inet_hashtables.c#L393">393</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L394" href="source/net/ipv4/inet_hashtables.c#L394">394</a>         }
<a name="L395" href="source/net/ipv4/inet_hashtables.c#L395">395</a>         return 0;
<a name="L396" href="source/net/ipv4/inet_hashtables.c#L396">396</a> 
<a name="L397" href="source/net/ipv4/inet_hashtables.c#L397">397</a> not_unique:
<a name="L398" href="source/net/ipv4/inet_hashtables.c#L398">398</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(<a href="ident?i=lock">lock</a>);
<a name="L399" href="source/net/ipv4/inet_hashtables.c#L399">399</a>         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L400" href="source/net/ipv4/inet_hashtables.c#L400">400</a> }
<a name="L401" href="source/net/ipv4/inet_hashtables.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/inet_hashtables.c#L402">402</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=inet_sk_port_offset">inet_sk_port_offset</a>(const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L403" href="source/net/ipv4/inet_hashtables.c#L403">403</a> {
<a name="L404" href="source/net/ipv4/inet_hashtables.c#L404">404</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L405" href="source/net/ipv4/inet_hashtables.c#L405">405</a>         return <a href="ident?i=secure_ipv4_port_ephemeral">secure_ipv4_port_ephemeral</a>(inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>,
<a name="L406" href="source/net/ipv4/inet_hashtables.c#L406">406</a>                                           inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>,
<a name="L407" href="source/net/ipv4/inet_hashtables.c#L407">407</a>                                           inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>);
<a name="L408" href="source/net/ipv4/inet_hashtables.c#L408">408</a> }
<a name="L409" href="source/net/ipv4/inet_hashtables.c#L409">409</a> 
<a name="L410" href="source/net/ipv4/inet_hashtables.c#L410">410</a> int <a href="ident?i=__inet_hash_nolisten">__inet_hash_nolisten</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
<a name="L411" href="source/net/ipv4/inet_hashtables.c#L411">411</a> {
<a name="L412" href="source/net/ipv4/inet_hashtables.c#L412">412</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
<a name="L413" href="source/net/ipv4/inet_hashtables.c#L413">413</a>         struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> *<a href="ident?i=list">list</a>;
<a name="L414" href="source/net/ipv4/inet_hashtables.c#L414">414</a>         struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a> *<a href="ident?i=head">head</a>;
<a name="L415" href="source/net/ipv4/inet_hashtables.c#L415">415</a>         <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a>;
<a name="L416" href="source/net/ipv4/inet_hashtables.c#L416">416</a>         int twrefcnt = 0;
<a name="L417" href="source/net/ipv4/inet_hashtables.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/inet_hashtables.c#L418">418</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk));
<a name="L419" href="source/net/ipv4/inet_hashtables.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/inet_hashtables.c#L420">420</a>         sk-&gt;<a href="ident?i=sk_hash">sk_hash</a> = <a href="ident?i=sk_ehashfn">sk_ehashfn</a>(sk);
<a name="L421" href="source/net/ipv4/inet_hashtables.c#L421">421</a>         <a href="ident?i=head">head</a> = <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a>(hashinfo, sk-&gt;<a href="ident?i=sk_hash">sk_hash</a>);
<a name="L422" href="source/net/ipv4/inet_hashtables.c#L422">422</a>         <a href="ident?i=list">list</a> = &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>;
<a name="L423" href="source/net/ipv4/inet_hashtables.c#L423">423</a>         <a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(hashinfo, sk-&gt;<a href="ident?i=sk_hash">sk_hash</a>);
<a name="L424" href="source/net/ipv4/inet_hashtables.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/inet_hashtables.c#L425">425</a>         <a href="ident?i=spin_lock">spin_lock</a>(<a href="ident?i=lock">lock</a>);
<a name="L426" href="source/net/ipv4/inet_hashtables.c#L426">426</a>         <a href="ident?i=__sk_nulls_add_node_rcu">__sk_nulls_add_node_rcu</a>(sk, <a href="ident?i=list">list</a>);
<a name="L427" href="source/net/ipv4/inet_hashtables.c#L427">427</a>         if (<a href="ident?i=tw">tw</a>) {
<a name="L428" href="source/net/ipv4/inet_hashtables.c#L428">428</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(sk-&gt;<a href="ident?i=sk_hash">sk_hash</a> != <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_hash">tw_hash</a>);
<a name="L429" href="source/net/ipv4/inet_hashtables.c#L429">429</a>                 twrefcnt = <a href="ident?i=inet_twsk_unhash">inet_twsk_unhash</a>(<a href="ident?i=tw">tw</a>);
<a name="L430" href="source/net/ipv4/inet_hashtables.c#L430">430</a>         }
<a name="L431" href="source/net/ipv4/inet_hashtables.c#L431">431</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(<a href="ident?i=lock">lock</a>);
<a name="L432" href="source/net/ipv4/inet_hashtables.c#L432">432</a>         <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, 1);
<a name="L433" href="source/net/ipv4/inet_hashtables.c#L433">433</a>         return twrefcnt;
<a name="L434" href="source/net/ipv4/inet_hashtables.c#L434">434</a> }
<a name="L435" href="source/net/ipv4/inet_hashtables.c#L435">435</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__inet_hash_nolisten">__inet_hash_nolisten</a>);
<a name="L436" href="source/net/ipv4/inet_hashtables.c#L436">436</a> 
<a name="L437" href="source/net/ipv4/inet_hashtables.c#L437">437</a> int <a href="ident?i=__inet_hash">__inet_hash</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
<a name="L438" href="source/net/ipv4/inet_hashtables.c#L438">438</a> {
<a name="L439" href="source/net/ipv4/inet_hashtables.c#L439">439</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
<a name="L440" href="source/net/ipv4/inet_hashtables.c#L440">440</a>         struct <a href="ident?i=inet_listen_hashbucket">inet_listen_hashbucket</a> *ilb;
<a name="L441" href="source/net/ipv4/inet_hashtables.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/inet_hashtables.c#L442">442</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN)
<a name="L443" href="source/net/ipv4/inet_hashtables.c#L443">443</a>                 return <a href="ident?i=__inet_hash_nolisten">__inet_hash_nolisten</a>(sk, <a href="ident?i=tw">tw</a>);
<a name="L444" href="source/net/ipv4/inet_hashtables.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/inet_hashtables.c#L445">445</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk));
<a name="L446" href="source/net/ipv4/inet_hashtables.c#L446">446</a>         ilb = &amp;hashinfo-&gt;listening_hash[<a href="ident?i=inet_sk_listen_hashfn">inet_sk_listen_hashfn</a>(sk)];
<a name="L447" href="source/net/ipv4/inet_hashtables.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/inet_hashtables.c#L448">448</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L449" href="source/net/ipv4/inet_hashtables.c#L449">449</a>         <a href="ident?i=__sk_nulls_add_node_rcu">__sk_nulls_add_node_rcu</a>(sk, &amp;ilb-&gt;<a href="ident?i=head">head</a>);
<a name="L450" href="source/net/ipv4/inet_hashtables.c#L450">450</a>         <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, 1);
<a name="L451" href="source/net/ipv4/inet_hashtables.c#L451">451</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L452" href="source/net/ipv4/inet_hashtables.c#L452">452</a>         return 0;
<a name="L453" href="source/net/ipv4/inet_hashtables.c#L453">453</a> }
<a name="L454" href="source/net/ipv4/inet_hashtables.c#L454">454</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=__inet_hash">__inet_hash</a>);
<a name="L455" href="source/net/ipv4/inet_hashtables.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/inet_hashtables.c#L456">456</a> void <a href="ident?i=inet_hash">inet_hash</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L457" href="source/net/ipv4/inet_hashtables.c#L457">457</a> {
<a name="L458" href="source/net/ipv4/inet_hashtables.c#L458">458</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE) {
<a name="L459" href="source/net/ipv4/inet_hashtables.c#L459">459</a>                 <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L460" href="source/net/ipv4/inet_hashtables.c#L460">460</a>                 <a href="ident?i=__inet_hash">__inet_hash</a>(sk, <a href="ident?i=NULL">NULL</a>);
<a name="L461" href="source/net/ipv4/inet_hashtables.c#L461">461</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L462" href="source/net/ipv4/inet_hashtables.c#L462">462</a>         }
<a name="L463" href="source/net/ipv4/inet_hashtables.c#L463">463</a> }
<a name="L464" href="source/net/ipv4/inet_hashtables.c#L464">464</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_hash">inet_hash</a>);
<a name="L465" href="source/net/ipv4/inet_hashtables.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/inet_hashtables.c#L466">466</a> void <a href="ident?i=inet_unhash">inet_unhash</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L467" href="source/net/ipv4/inet_hashtables.c#L467">467</a> {
<a name="L468" href="source/net/ipv4/inet_hashtables.c#L468">468</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
<a name="L469" href="source/net/ipv4/inet_hashtables.c#L469">469</a>         <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a>;
<a name="L470" href="source/net/ipv4/inet_hashtables.c#L470">470</a>         int <a href="ident?i=done">done</a>;
<a name="L471" href="source/net/ipv4/inet_hashtables.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/inet_hashtables.c#L472">472</a>         if (<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk))
<a name="L473" href="source/net/ipv4/inet_hashtables.c#L473">473</a>                 return;
<a name="L474" href="source/net/ipv4/inet_hashtables.c#L474">474</a> 
<a name="L475" href="source/net/ipv4/inet_hashtables.c#L475">475</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L476" href="source/net/ipv4/inet_hashtables.c#L476">476</a>                 <a href="ident?i=lock">lock</a> = &amp;hashinfo-&gt;listening_hash[<a href="ident?i=inet_sk_listen_hashfn">inet_sk_listen_hashfn</a>(sk)].<a href="ident?i=lock">lock</a>;
<a name="L477" href="source/net/ipv4/inet_hashtables.c#L477">477</a>         else
<a name="L478" href="source/net/ipv4/inet_hashtables.c#L478">478</a>                 <a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(hashinfo, sk-&gt;<a href="ident?i=sk_hash">sk_hash</a>);
<a name="L479" href="source/net/ipv4/inet_hashtables.c#L479">479</a> 
<a name="L480" href="source/net/ipv4/inet_hashtables.c#L480">480</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L481" href="source/net/ipv4/inet_hashtables.c#L481">481</a>         <a href="ident?i=done">done</a> = <a href="ident?i=__sk_nulls_del_node_init_rcu">__sk_nulls_del_node_init_rcu</a>(sk);
<a name="L482" href="source/net/ipv4/inet_hashtables.c#L482">482</a>         if (<a href="ident?i=done">done</a>)
<a name="L483" href="source/net/ipv4/inet_hashtables.c#L483">483</a>                 <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, -1);
<a name="L484" href="source/net/ipv4/inet_hashtables.c#L484">484</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L485" href="source/net/ipv4/inet_hashtables.c#L485">485</a> }
<a name="L486" href="source/net/ipv4/inet_hashtables.c#L486">486</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_unhash">inet_unhash</a>);
<a name="L487" href="source/net/ipv4/inet_hashtables.c#L487">487</a> 
<a name="L488" href="source/net/ipv4/inet_hashtables.c#L488">488</a> int <a href="ident?i=__inet_hash_connect">__inet_hash_connect</a>(struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> *death_row,
<a name="L489" href="source/net/ipv4/inet_hashtables.c#L489">489</a>                 struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=port_offset">port_offset</a>,
<a name="L490" href="source/net/ipv4/inet_hashtables.c#L490">490</a>                 int (*check_established)(struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> *,
<a name="L491" href="source/net/ipv4/inet_hashtables.c#L491">491</a>                         struct <a href="ident?i=sock">sock</a> *, <a href="ident?i=__u16">__u16</a>, struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> **))
<a name="L492" href="source/net/ipv4/inet_hashtables.c#L492">492</a> {
<a name="L493" href="source/net/ipv4/inet_hashtables.c#L493">493</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hinfo = death_row-&gt;hashinfo;
<a name="L494" href="source/net/ipv4/inet_hashtables.c#L494">494</a>         const unsigned short snum = <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a>;
<a name="L495" href="source/net/ipv4/inet_hashtables.c#L495">495</a>         struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *<a href="ident?i=head">head</a>;
<a name="L496" href="source/net/ipv4/inet_hashtables.c#L496">496</a>         struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>;
<a name="L497" href="source/net/ipv4/inet_hashtables.c#L497">497</a>         int <a href="ident?i=ret">ret</a>;
<a name="L498" href="source/net/ipv4/inet_hashtables.c#L498">498</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L499" href="source/net/ipv4/inet_hashtables.c#L499">499</a>         int twrefcnt = 1;
<a name="L500" href="source/net/ipv4/inet_hashtables.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/inet_hashtables.c#L501">501</a>         if (!snum) {
<a name="L502" href="source/net/ipv4/inet_hashtables.c#L502">502</a>                 int <a href="ident?i=i">i</a>, <a href="ident?i=remaining">remaining</a>, low, <a href="ident?i=high">high</a>, <a href="ident?i=port">port</a>;
<a name="L503" href="source/net/ipv4/inet_hashtables.c#L503">503</a>                 static <a href="ident?i=u32">u32</a> <a href="ident?i=hint">hint</a>;
<a name="L504" href="source/net/ipv4/inet_hashtables.c#L504">504</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=offset">offset</a> = <a href="ident?i=hint">hint</a> + <a href="ident?i=port_offset">port_offset</a>;
<a name="L505" href="source/net/ipv4/inet_hashtables.c#L505">505</a>                 struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L506" href="source/net/ipv4/inet_hashtables.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/inet_hashtables.c#L507">507</a>                 <a href="ident?i=inet_get_local_port_range">inet_get_local_port_range</a>(<a href="ident?i=net">net</a>, &amp;low, &amp;<a href="ident?i=high">high</a>);
<a name="L508" href="source/net/ipv4/inet_hashtables.c#L508">508</a>                 <a href="ident?i=remaining">remaining</a> = (<a href="ident?i=high">high</a> - low) + 1;
<a name="L509" href="source/net/ipv4/inet_hashtables.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/inet_hashtables.c#L510">510</a>                 <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L511" href="source/net/ipv4/inet_hashtables.c#L511">511</a>                 for (<a href="ident?i=i">i</a> = 1; <a href="ident?i=i">i</a> &lt;= <a href="ident?i=remaining">remaining</a>; <a href="ident?i=i">i</a>++) {
<a name="L512" href="source/net/ipv4/inet_hashtables.c#L512">512</a>                         <a href="ident?i=port">port</a> = low + (<a href="ident?i=i">i</a> + <a href="ident?i=offset">offset</a>) % <a href="ident?i=remaining">remaining</a>;
<a name="L513" href="source/net/ipv4/inet_hashtables.c#L513">513</a>                         if (<a href="ident?i=inet_is_local_reserved_port">inet_is_local_reserved_port</a>(<a href="ident?i=net">net</a>, <a href="ident?i=port">port</a>))
<a name="L514" href="source/net/ipv4/inet_hashtables.c#L514">514</a>                                 continue;
<a name="L515" href="source/net/ipv4/inet_hashtables.c#L515">515</a>                         <a href="ident?i=head">head</a> = &amp;hinfo-&gt;bhash[<a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=port">port</a>,
<a name="L516" href="source/net/ipv4/inet_hashtables.c#L516">516</a>                                         hinfo-&gt;bhash_size)];
<a name="L517" href="source/net/ipv4/inet_hashtables.c#L517">517</a>                         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L518" href="source/net/ipv4/inet_hashtables.c#L518">518</a> 
<a name="L519" href="source/net/ipv4/inet_hashtables.c#L519">519</a>                         <b><i>/* Does not bother with rcv_saddr checks,</i></b>
<a name="L520" href="source/net/ipv4/inet_hashtables.c#L520">520</a> <b><i>                         * because the established check is already</i></b>
<a name="L521" href="source/net/ipv4/inet_hashtables.c#L521">521</a> <b><i>                         * unique enough.</i></b>
<a name="L522" href="source/net/ipv4/inet_hashtables.c#L522">522</a> <b><i>                         */</i></b>
<a name="L523" href="source/net/ipv4/inet_hashtables.c#L523">523</a>                         <a href="ident?i=inet_bind_bucket_for_each">inet_bind_bucket_for_each</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>) {
<a name="L524" href="source/net/ipv4/inet_hashtables.c#L524">524</a>                                 if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=ib_net">ib_net</a>(<a href="ident?i=tb">tb</a>), <a href="ident?i=net">net</a>) &amp;&amp;
<a name="L525" href="source/net/ipv4/inet_hashtables.c#L525">525</a>                                     <a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=port">port</a> == <a href="ident?i=port">port</a>) {
<a name="L526" href="source/net/ipv4/inet_hashtables.c#L526">526</a>                                         if (<a href="ident?i=tb">tb</a>-&gt;fastreuse &gt;= 0 ||
<a name="L527" href="source/net/ipv4/inet_hashtables.c#L527">527</a>                                             <a href="ident?i=tb">tb</a>-&gt;fastreuseport &gt;= 0)
<a name="L528" href="source/net/ipv4/inet_hashtables.c#L528">528</a>                                                 goto next_port;
<a name="L529" href="source/net/ipv4/inet_hashtables.c#L529">529</a>                                         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;owners));
<a name="L530" href="source/net/ipv4/inet_hashtables.c#L530">530</a>                                         if (!check_established(death_row, sk,
<a name="L531" href="source/net/ipv4/inet_hashtables.c#L531">531</a>                                                                 <a href="ident?i=port">port</a>, &amp;<a href="ident?i=tw">tw</a>))
<a name="L532" href="source/net/ipv4/inet_hashtables.c#L532">532</a>                                                 goto <a href="ident?i=ok">ok</a>;
<a name="L533" href="source/net/ipv4/inet_hashtables.c#L533">533</a>                                         goto next_port;
<a name="L534" href="source/net/ipv4/inet_hashtables.c#L534">534</a>                                 }
<a name="L535" href="source/net/ipv4/inet_hashtables.c#L535">535</a>                         }
<a name="L536" href="source/net/ipv4/inet_hashtables.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/inet_hashtables.c#L537">537</a>                         <a href="ident?i=tb">tb</a> = <a href="ident?i=inet_bind_bucket_create">inet_bind_bucket_create</a>(hinfo-&gt;bind_bucket_cachep,
<a name="L538" href="source/net/ipv4/inet_hashtables.c#L538">538</a>                                         <a href="ident?i=net">net</a>, <a href="ident?i=head">head</a>, <a href="ident?i=port">port</a>);
<a name="L539" href="source/net/ipv4/inet_hashtables.c#L539">539</a>                         if (!<a href="ident?i=tb">tb</a>) {
<a name="L540" href="source/net/ipv4/inet_hashtables.c#L540">540</a>                                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L541" href="source/net/ipv4/inet_hashtables.c#L541">541</a>                                 break;
<a name="L542" href="source/net/ipv4/inet_hashtables.c#L542">542</a>                         }
<a name="L543" href="source/net/ipv4/inet_hashtables.c#L543">543</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuse = -1;
<a name="L544" href="source/net/ipv4/inet_hashtables.c#L544">544</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuseport = -1;
<a name="L545" href="source/net/ipv4/inet_hashtables.c#L545">545</a>                         goto <a href="ident?i=ok">ok</a>;
<a name="L546" href="source/net/ipv4/inet_hashtables.c#L546">546</a> 
<a name="L547" href="source/net/ipv4/inet_hashtables.c#L547">547</a>                 next_port:
<a name="L548" href="source/net/ipv4/inet_hashtables.c#L548">548</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L549" href="source/net/ipv4/inet_hashtables.c#L549">549</a>                 }
<a name="L550" href="source/net/ipv4/inet_hashtables.c#L550">550</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L551" href="source/net/ipv4/inet_hashtables.c#L551">551</a> 
<a name="L552" href="source/net/ipv4/inet_hashtables.c#L552">552</a>                 return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L553" href="source/net/ipv4/inet_hashtables.c#L553">553</a> 
<a name="L554" href="source/net/ipv4/inet_hashtables.c#L554">554</a> <a href="ident?i=ok">ok</a>:
<a name="L555" href="source/net/ipv4/inet_hashtables.c#L555">555</a>                 <a href="ident?i=hint">hint</a> += <a href="ident?i=i">i</a>;
<a name="L556" href="source/net/ipv4/inet_hashtables.c#L556">556</a> 
<a name="L557" href="source/net/ipv4/inet_hashtables.c#L557">557</a>                 <b><i>/* Head lock still held and bh's disabled */</i></b>
<a name="L558" href="source/net/ipv4/inet_hashtables.c#L558">558</a>                 <a href="ident?i=inet_bind_hash">inet_bind_hash</a>(sk, <a href="ident?i=tb">tb</a>, <a href="ident?i=port">port</a>);
<a name="L559" href="source/net/ipv4/inet_hashtables.c#L559">559</a>                 if (<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk)) {
<a name="L560" href="source/net/ipv4/inet_hashtables.c#L560">560</a>                         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;inet_sport = <a href="ident?i=htons">htons</a>(<a href="ident?i=port">port</a>);
<a name="L561" href="source/net/ipv4/inet_hashtables.c#L561">561</a>                         twrefcnt += <a href="ident?i=__inet_hash_nolisten">__inet_hash_nolisten</a>(sk, <a href="ident?i=tw">tw</a>);
<a name="L562" href="source/net/ipv4/inet_hashtables.c#L562">562</a>                 }
<a name="L563" href="source/net/ipv4/inet_hashtables.c#L563">563</a>                 if (<a href="ident?i=tw">tw</a>)
<a name="L564" href="source/net/ipv4/inet_hashtables.c#L564">564</a>                         twrefcnt += <a href="ident?i=inet_twsk_bind_unhash">inet_twsk_bind_unhash</a>(<a href="ident?i=tw">tw</a>, hinfo);
<a name="L565" href="source/net/ipv4/inet_hashtables.c#L565">565</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L566" href="source/net/ipv4/inet_hashtables.c#L566">566</a> 
<a name="L567" href="source/net/ipv4/inet_hashtables.c#L567">567</a>                 if (<a href="ident?i=tw">tw</a>) {
<a name="L568" href="source/net/ipv4/inet_hashtables.c#L568">568</a>                         <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(<a href="ident?i=tw">tw</a>);
<a name="L569" href="source/net/ipv4/inet_hashtables.c#L569">569</a>                         while (twrefcnt) {
<a name="L570" href="source/net/ipv4/inet_hashtables.c#L570">570</a>                                 twrefcnt--;
<a name="L571" href="source/net/ipv4/inet_hashtables.c#L571">571</a>                                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L572" href="source/net/ipv4/inet_hashtables.c#L572">572</a>                         }
<a name="L573" href="source/net/ipv4/inet_hashtables.c#L573">573</a>                 }
<a name="L574" href="source/net/ipv4/inet_hashtables.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/inet_hashtables.c#L575">575</a>                 <a href="ident?i=ret">ret</a> = 0;
<a name="L576" href="source/net/ipv4/inet_hashtables.c#L576">576</a>                 goto <a href="ident?i=out">out</a>;
<a name="L577" href="source/net/ipv4/inet_hashtables.c#L577">577</a>         }
<a name="L578" href="source/net/ipv4/inet_hashtables.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/inet_hashtables.c#L579">579</a>         <a href="ident?i=head">head</a> = &amp;hinfo-&gt;bhash[<a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=net">net</a>, snum, hinfo-&gt;bhash_size)];
<a name="L580" href="source/net/ipv4/inet_hashtables.c#L580">580</a>         <a href="ident?i=tb">tb</a>  = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash;
<a name="L581" href="source/net/ipv4/inet_hashtables.c#L581">581</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L582" href="source/net/ipv4/inet_hashtables.c#L582">582</a>         if (<a href="ident?i=sk_head">sk_head</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;owners) == sk &amp;&amp; !sk-&gt;<a href="ident?i=sk_bind_node">sk_bind_node</a>.<a href="ident?i=next">next</a>) {
<a name="L583" href="source/net/ipv4/inet_hashtables.c#L583">583</a>                 <a href="ident?i=__inet_hash_nolisten">__inet_hash_nolisten</a>(sk, <a href="ident?i=NULL">NULL</a>);
<a name="L584" href="source/net/ipv4/inet_hashtables.c#L584">584</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L585" href="source/net/ipv4/inet_hashtables.c#L585">585</a>                 return 0;
<a name="L586" href="source/net/ipv4/inet_hashtables.c#L586">586</a>         } else {
<a name="L587" href="source/net/ipv4/inet_hashtables.c#L587">587</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L588" href="source/net/ipv4/inet_hashtables.c#L588">588</a>                 <b><i>/* No definite answer... Walk to established hash table */</i></b>
<a name="L589" href="source/net/ipv4/inet_hashtables.c#L589">589</a>                 <a href="ident?i=ret">ret</a> = check_established(death_row, sk, snum, <a href="ident?i=NULL">NULL</a>);
<a name="L590" href="source/net/ipv4/inet_hashtables.c#L590">590</a> <a href="ident?i=out">out</a>:
<a name="L591" href="source/net/ipv4/inet_hashtables.c#L591">591</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L592" href="source/net/ipv4/inet_hashtables.c#L592">592</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L593" href="source/net/ipv4/inet_hashtables.c#L593">593</a>         }
<a name="L594" href="source/net/ipv4/inet_hashtables.c#L594">594</a> }
<a name="L595" href="source/net/ipv4/inet_hashtables.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/inet_hashtables.c#L596">596</a> <b><i>/*</i></b>
<a name="L597" href="source/net/ipv4/inet_hashtables.c#L597">597</a> <b><i> * Bind a port for a connect operation and hash it.</i></b>
<a name="L598" href="source/net/ipv4/inet_hashtables.c#L598">598</a> <b><i> */</i></b>
<a name="L599" href="source/net/ipv4/inet_hashtables.c#L599">599</a> int <a href="ident?i=inet_hash_connect">inet_hash_connect</a>(struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> *death_row,
<a name="L600" href="source/net/ipv4/inet_hashtables.c#L600">600</a>                       struct <a href="ident?i=sock">sock</a> *sk)
<a name="L601" href="source/net/ipv4/inet_hashtables.c#L601">601</a> {
<a name="L602" href="source/net/ipv4/inet_hashtables.c#L602">602</a>         return <a href="ident?i=__inet_hash_connect">__inet_hash_connect</a>(death_row, sk, <a href="ident?i=inet_sk_port_offset">inet_sk_port_offset</a>(sk),
<a name="L603" href="source/net/ipv4/inet_hashtables.c#L603">603</a>                                    <a href="ident?i=__inet_check_established">__inet_check_established</a>);
<a name="L604" href="source/net/ipv4/inet_hashtables.c#L604">604</a> }
<a name="L605" href="source/net/ipv4/inet_hashtables.c#L605">605</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_hash_connect">inet_hash_connect</a>);
<a name="L606" href="source/net/ipv4/inet_hashtables.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/inet_hashtables.c#L607">607</a> void <a href="ident?i=inet_hashinfo_init">inet_hashinfo_init</a>(struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *<a href="ident?i=h">h</a>)
<a name="L608" href="source/net/ipv4/inet_hashtables.c#L608">608</a> {
<a name="L609" href="source/net/ipv4/inet_hashtables.c#L609">609</a>         int <a href="ident?i=i">i</a>;
<a name="L610" href="source/net/ipv4/inet_hashtables.c#L610">610</a> 
<a name="L611" href="source/net/ipv4/inet_hashtables.c#L611">611</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=h">h</a>-&gt;bsockets, 0);
<a name="L612" href="source/net/ipv4/inet_hashtables.c#L612">612</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=INET_LHTABLE_SIZE">INET_LHTABLE_SIZE</a>; <a href="ident?i=i">i</a>++) {
<a name="L613" href="source/net/ipv4/inet_hashtables.c#L613">613</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;<a href="ident?i=h">h</a>-&gt;listening_hash[<a href="ident?i=i">i</a>].<a href="ident?i=lock">lock</a>);
<a name="L614" href="source/net/ipv4/inet_hashtables.c#L614">614</a>                 <a href="ident?i=INIT_HLIST_NULLS_HEAD">INIT_HLIST_NULLS_HEAD</a>(&amp;<a href="ident?i=h">h</a>-&gt;listening_hash[<a href="ident?i=i">i</a>].<a href="ident?i=head">head</a>,
<a name="L615" href="source/net/ipv4/inet_hashtables.c#L615">615</a>                                       <a href="ident?i=i">i</a> + <a href="ident?i=LISTENING_NULLS_BASE">LISTENING_NULLS_BASE</a>);
<a name="L616" href="source/net/ipv4/inet_hashtables.c#L616">616</a>                 }
<a name="L617" href="source/net/ipv4/inet_hashtables.c#L617">617</a> }
<a name="L618" href="source/net/ipv4/inet_hashtables.c#L618">618</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_hashinfo_init">inet_hashinfo_init</a>);
<a name="L619" href="source/net/ipv4/inet_hashtables.c#L619">619</a> </pre></div><p>
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
