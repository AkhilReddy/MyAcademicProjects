<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inet_timewait_sock.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inet_timewait_sock.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inet_timewait_sock.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inet_timewait_sock.c">inet_timewait_sock.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inet_timewait_sock.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inet_timewait_sock.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/inet_timewait_sock.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/inet_timewait_sock.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/inet_timewait_sock.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/inet_timewait_sock.c#L6">6</a> <b><i> *              Generic TIME_WAIT sockets functions</i></b>
  <a name="L7" href="source/net/ipv4/inet_timewait_sock.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/inet_timewait_sock.c#L8">8</a> <b><i> *              From code orinally in TCP</i></b>
  <a name="L9" href="source/net/ipv4/inet_timewait_sock.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/inet_timewait_sock.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/inet_timewait_sock.c#L11">11</a> #include &lt;linux/kernel.h&gt;
 <a name="L12" href="source/net/ipv4/inet_timewait_sock.c#L12">12</a> #include &lt;linux/kmemcheck.h&gt;
 <a name="L13" href="source/net/ipv4/inet_timewait_sock.c#L13">13</a> #include &lt;linux/slab.h&gt;
 <a name="L14" href="source/net/ipv4/inet_timewait_sock.c#L14">14</a> #include &lt;linux/module.h&gt;
 <a name="L15" href="source/net/ipv4/inet_timewait_sock.c#L15">15</a> #include &lt;net/inet_hashtables.h&gt;
 <a name="L16" href="source/net/ipv4/inet_timewait_sock.c#L16">16</a> #include &lt;net/inet_timewait_sock.h&gt;
 <a name="L17" href="source/net/ipv4/inet_timewait_sock.c#L17">17</a> #include &lt;net/ip.h&gt;
 <a name="L18" href="source/net/ipv4/inet_timewait_sock.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/inet_timewait_sock.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/inet_timewait_sock.c#L20">20</a> <b><i>/**</i></b>
 <a name="L21" href="source/net/ipv4/inet_timewait_sock.c#L21">21</a> <b><i> *      inet_twsk_unhash - unhash a timewait socket from established hash</i></b>
 <a name="L22" href="source/net/ipv4/inet_timewait_sock.c#L22">22</a> <b><i> *      @tw: timewait socket</i></b>
 <a name="L23" href="source/net/ipv4/inet_timewait_sock.c#L23">23</a> <b><i> *</i></b>
 <a name="L24" href="source/net/ipv4/inet_timewait_sock.c#L24">24</a> <b><i> *      unhash a timewait socket from established hash, if hashed.</i></b>
 <a name="L25" href="source/net/ipv4/inet_timewait_sock.c#L25">25</a> <b><i> *      ehash lock must be held by caller.</i></b>
 <a name="L26" href="source/net/ipv4/inet_timewait_sock.c#L26">26</a> <b><i> *      Returns 1 if caller should call inet_twsk_put() after lock release.</i></b>
 <a name="L27" href="source/net/ipv4/inet_timewait_sock.c#L27">27</a> <b><i> */</i></b>
 <a name="L28" href="source/net/ipv4/inet_timewait_sock.c#L28">28</a> int <a href="ident?i=inet_twsk_unhash">inet_twsk_unhash</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
 <a name="L29" href="source/net/ipv4/inet_timewait_sock.c#L29">29</a> {
 <a name="L30" href="source/net/ipv4/inet_timewait_sock.c#L30">30</a>         if (<a href="ident?i=hlist_nulls_unhashed">hlist_nulls_unhashed</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_node">tw_node</a>))
 <a name="L31" href="source/net/ipv4/inet_timewait_sock.c#L31">31</a>                 return 0;
 <a name="L32" href="source/net/ipv4/inet_timewait_sock.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/inet_timewait_sock.c#L33">33</a>         <a href="ident?i=hlist_nulls_del_rcu">hlist_nulls_del_rcu</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_node">tw_node</a>);
 <a name="L34" href="source/net/ipv4/inet_timewait_sock.c#L34">34</a>         <a href="ident?i=sk_nulls_node_init">sk_nulls_node_init</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_node">tw_node</a>);
 <a name="L35" href="source/net/ipv4/inet_timewait_sock.c#L35">35</a>         <b><i>/*</i></b>
 <a name="L36" href="source/net/ipv4/inet_timewait_sock.c#L36">36</a> <b><i>         * We cannot call inet_twsk_put() ourself under lock,</i></b>
 <a name="L37" href="source/net/ipv4/inet_timewait_sock.c#L37">37</a> <b><i>         * caller must call it for us.</i></b>
 <a name="L38" href="source/net/ipv4/inet_timewait_sock.c#L38">38</a> <b><i>         */</i></b>
 <a name="L39" href="source/net/ipv4/inet_timewait_sock.c#L39">39</a>         return 1;
 <a name="L40" href="source/net/ipv4/inet_timewait_sock.c#L40">40</a> }
 <a name="L41" href="source/net/ipv4/inet_timewait_sock.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/inet_timewait_sock.c#L42">42</a> <b><i>/**</i></b>
 <a name="L43" href="source/net/ipv4/inet_timewait_sock.c#L43">43</a> <b><i> *      inet_twsk_bind_unhash - unhash a timewait socket from bind hash</i></b>
 <a name="L44" href="source/net/ipv4/inet_timewait_sock.c#L44">44</a> <b><i> *      @tw: timewait socket</i></b>
 <a name="L45" href="source/net/ipv4/inet_timewait_sock.c#L45">45</a> <b><i> *      @hashinfo: hashinfo pointer</i></b>
 <a name="L46" href="source/net/ipv4/inet_timewait_sock.c#L46">46</a> <b><i> *</i></b>
 <a name="L47" href="source/net/ipv4/inet_timewait_sock.c#L47">47</a> <b><i> *      unhash a timewait socket from bind hash, if hashed.</i></b>
 <a name="L48" href="source/net/ipv4/inet_timewait_sock.c#L48">48</a> <b><i> *      bind hash lock must be held by caller.</i></b>
 <a name="L49" href="source/net/ipv4/inet_timewait_sock.c#L49">49</a> <b><i> *      Returns 1 if caller should call inet_twsk_put() after lock release.</i></b>
 <a name="L50" href="source/net/ipv4/inet_timewait_sock.c#L50">50</a> <b><i> */</i></b>
 <a name="L51" href="source/net/ipv4/inet_timewait_sock.c#L51">51</a> int <a href="ident?i=inet_twsk_bind_unhash">inet_twsk_bind_unhash</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>,
 <a name="L52" href="source/net/ipv4/inet_timewait_sock.c#L52">52</a>                           struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo)
 <a name="L53" href="source/net/ipv4/inet_timewait_sock.c#L53">53</a> {
 <a name="L54" href="source/net/ipv4/inet_timewait_sock.c#L54">54</a>         struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a> = <a href="ident?i=tw">tw</a>-&gt;tw_tb;
 <a name="L55" href="source/net/ipv4/inet_timewait_sock.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/inet_timewait_sock.c#L56">56</a>         if (!<a href="ident?i=tb">tb</a>)
 <a name="L57" href="source/net/ipv4/inet_timewait_sock.c#L57">57</a>                 return 0;
 <a name="L58" href="source/net/ipv4/inet_timewait_sock.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/inet_timewait_sock.c#L59">59</a>         <a href="ident?i=__hlist_del">__hlist_del</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_bind_node">tw_bind_node</a>);
 <a name="L60" href="source/net/ipv4/inet_timewait_sock.c#L60">60</a>         <a href="ident?i=tw">tw</a>-&gt;tw_tb = <a href="ident?i=NULL">NULL</a>;
 <a name="L61" href="source/net/ipv4/inet_timewait_sock.c#L61">61</a>         <a href="ident?i=inet_bind_bucket_destroy">inet_bind_bucket_destroy</a>(hashinfo-&gt;bind_bucket_cachep, <a href="ident?i=tb">tb</a>);
 <a name="L62" href="source/net/ipv4/inet_timewait_sock.c#L62">62</a>         <b><i>/*</i></b>
 <a name="L63" href="source/net/ipv4/inet_timewait_sock.c#L63">63</a> <b><i>         * We cannot call inet_twsk_put() ourself under lock,</i></b>
 <a name="L64" href="source/net/ipv4/inet_timewait_sock.c#L64">64</a> <b><i>         * caller must call it for us.</i></b>
 <a name="L65" href="source/net/ipv4/inet_timewait_sock.c#L65">65</a> <b><i>         */</i></b>
 <a name="L66" href="source/net/ipv4/inet_timewait_sock.c#L66">66</a>         return 1;
 <a name="L67" href="source/net/ipv4/inet_timewait_sock.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/inet_timewait_sock.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/inet_timewait_sock.c#L69">69</a> <b><i>/* Must be called with locally disabled BHs. */</i></b>
 <a name="L70" href="source/net/ipv4/inet_timewait_sock.c#L70">70</a> static void <a href="ident?i=inet_twsk_kill">inet_twsk_kill</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
 <a name="L71" href="source/net/ipv4/inet_timewait_sock.c#L71">71</a> {
 <a name="L72" href="source/net/ipv4/inet_timewait_sock.c#L72">72</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = <a href="ident?i=tw">tw</a>-&gt;tw_dr-&gt;hashinfo;
 <a name="L73" href="source/net/ipv4/inet_timewait_sock.c#L73">73</a>         struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *bhead;
 <a name="L74" href="source/net/ipv4/inet_timewait_sock.c#L74">74</a>         int refcnt;
 <a name="L75" href="source/net/ipv4/inet_timewait_sock.c#L75">75</a>         <b><i>/* Unlink from established hashes. */</i></b>
 <a name="L76" href="source/net/ipv4/inet_timewait_sock.c#L76">76</a>         <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(hashinfo, <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_hash">tw_hash</a>);
 <a name="L77" href="source/net/ipv4/inet_timewait_sock.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/inet_timewait_sock.c#L78">78</a>         <a href="ident?i=spin_lock">spin_lock</a>(<a href="ident?i=lock">lock</a>);
 <a name="L79" href="source/net/ipv4/inet_timewait_sock.c#L79">79</a>         refcnt = <a href="ident?i=inet_twsk_unhash">inet_twsk_unhash</a>(<a href="ident?i=tw">tw</a>);
 <a name="L80" href="source/net/ipv4/inet_timewait_sock.c#L80">80</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(<a href="ident?i=lock">lock</a>);
 <a name="L81" href="source/net/ipv4/inet_timewait_sock.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/inet_timewait_sock.c#L82">82</a>         <b><i>/* Disassociate with bind bucket. */</i></b>
 <a name="L83" href="source/net/ipv4/inet_timewait_sock.c#L83">83</a>         bhead = &amp;hashinfo-&gt;bhash[<a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>), <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_num">tw_num</a>,
 <a name="L84" href="source/net/ipv4/inet_timewait_sock.c#L84">84</a>                         hashinfo-&gt;bhash_size)];
 <a name="L85" href="source/net/ipv4/inet_timewait_sock.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/inet_timewait_sock.c#L86">86</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;bhead-&gt;<a href="ident?i=lock">lock</a>);
 <a name="L87" href="source/net/ipv4/inet_timewait_sock.c#L87">87</a>         refcnt += <a href="ident?i=inet_twsk_bind_unhash">inet_twsk_bind_unhash</a>(<a href="ident?i=tw">tw</a>, hashinfo);
 <a name="L88" href="source/net/ipv4/inet_timewait_sock.c#L88">88</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;bhead-&gt;<a href="ident?i=lock">lock</a>);
 <a name="L89" href="source/net/ipv4/inet_timewait_sock.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/inet_timewait_sock.c#L90">90</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(refcnt &gt;= <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>));
 <a name="L91" href="source/net/ipv4/inet_timewait_sock.c#L91">91</a>         <a href="ident?i=atomic_sub">atomic_sub</a>(refcnt, &amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>);
 <a name="L92" href="source/net/ipv4/inet_timewait_sock.c#L92">92</a>         <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;tw_dr-&gt;tw_count);
 <a name="L93" href="source/net/ipv4/inet_timewait_sock.c#L93">93</a>         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
 <a name="L94" href="source/net/ipv4/inet_timewait_sock.c#L94">94</a> }
 <a name="L95" href="source/net/ipv4/inet_timewait_sock.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/inet_timewait_sock.c#L96">96</a> void <a href="ident?i=inet_twsk_free">inet_twsk_free</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
 <a name="L97" href="source/net/ipv4/inet_timewait_sock.c#L97">97</a> {
 <a name="L98" href="source/net/ipv4/inet_timewait_sock.c#L98">98</a>         struct <a href="ident?i=module">module</a> *owner = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_prot">tw_prot</a>-&gt;owner;
 <a name="L99" href="source/net/ipv4/inet_timewait_sock.c#L99">99</a>         <a href="ident?i=twsk_destructor">twsk_destructor</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tw">tw</a>);
<a name="L100" href="source/net/ipv4/inet_timewait_sock.c#L100">100</a> #ifdef SOCK_REFCNT_DEBUG
<a name="L101" href="source/net/ipv4/inet_timewait_sock.c#L101">101</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"%s timewait_sock %p released\n"</i>, <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_prot">tw_prot</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=tw">tw</a>);
<a name="L102" href="source/net/ipv4/inet_timewait_sock.c#L102">102</a> #endif
<a name="L103" href="source/net/ipv4/inet_timewait_sock.c#L103">103</a>         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_prot">tw_prot</a>-&gt;twsk_prot-&gt;twsk_slab, <a href="ident?i=tw">tw</a>);
<a name="L104" href="source/net/ipv4/inet_timewait_sock.c#L104">104</a>         <a href="ident?i=module_put">module_put</a>(owner);
<a name="L105" href="source/net/ipv4/inet_timewait_sock.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/inet_timewait_sock.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/inet_timewait_sock.c#L107">107</a> void <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
<a name="L108" href="source/net/ipv4/inet_timewait_sock.c#L108">108</a> {
<a name="L109" href="source/net/ipv4/inet_timewait_sock.c#L109">109</a>         if (<a href="ident?i=atomic_dec_and_test">atomic_dec_and_test</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>))
<a name="L110" href="source/net/ipv4/inet_timewait_sock.c#L110">110</a>                 <a href="ident?i=inet_twsk_free">inet_twsk_free</a>(<a href="ident?i=tw">tw</a>);
<a name="L111" href="source/net/ipv4/inet_timewait_sock.c#L111">111</a> }
<a name="L112" href="source/net/ipv4/inet_timewait_sock.c#L112">112</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_twsk_put">inet_twsk_put</a>);
<a name="L113" href="source/net/ipv4/inet_timewait_sock.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/inet_timewait_sock.c#L114">114</a> static void <a href="ident?i=inet_twsk_add_node_rcu">inet_twsk_add_node_rcu</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>,
<a name="L115" href="source/net/ipv4/inet_timewait_sock.c#L115">115</a>                                    struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> *<a href="ident?i=list">list</a>)
<a name="L116" href="source/net/ipv4/inet_timewait_sock.c#L116">116</a> {
<a name="L117" href="source/net/ipv4/inet_timewait_sock.c#L117">117</a>         <a href="ident?i=hlist_nulls_add_head_rcu">hlist_nulls_add_head_rcu</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_node">tw_node</a>, <a href="ident?i=list">list</a>);
<a name="L118" href="source/net/ipv4/inet_timewait_sock.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/inet_timewait_sock.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/inet_timewait_sock.c#L120">120</a> static void <a href="ident?i=inet_twsk_add_bind_node">inet_twsk_add_bind_node</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>,
<a name="L121" href="source/net/ipv4/inet_timewait_sock.c#L121">121</a>                                     struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=list">list</a>)
<a name="L122" href="source/net/ipv4/inet_timewait_sock.c#L122">122</a> {
<a name="L123" href="source/net/ipv4/inet_timewait_sock.c#L123">123</a>         <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_bind_node">tw_bind_node</a>, <a href="ident?i=list">list</a>);
<a name="L124" href="source/net/ipv4/inet_timewait_sock.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/inet_timewait_sock.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/inet_timewait_sock.c#L126">126</a> <b><i>/*</i></b>
<a name="L127" href="source/net/ipv4/inet_timewait_sock.c#L127">127</a> <b><i> * Enter the time wait state. This is called with locally disabled BH.</i></b>
<a name="L128" href="source/net/ipv4/inet_timewait_sock.c#L128">128</a> <b><i> * Essentially we whip up a timewait bucket, copy the relevant info into it</i></b>
<a name="L129" href="source/net/ipv4/inet_timewait_sock.c#L129">129</a> <b><i> * from the SK, and mess with hash chains and list linkage.</i></b>
<a name="L130" href="source/net/ipv4/inet_timewait_sock.c#L130">130</a> <b><i> */</i></b>
<a name="L131" href="source/net/ipv4/inet_timewait_sock.c#L131">131</a> void <a href="ident?i=__inet_twsk_hashdance">__inet_twsk_hashdance</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L132" href="source/net/ipv4/inet_timewait_sock.c#L132">132</a>                            struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo)
<a name="L133" href="source/net/ipv4/inet_timewait_sock.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/inet_timewait_sock.c#L134">134</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L135" href="source/net/ipv4/inet_timewait_sock.c#L135">135</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L136" href="source/net/ipv4/inet_timewait_sock.c#L136">136</a>         struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a> *ehead = <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a>(hashinfo, sk-&gt;<a href="ident?i=sk_hash">sk_hash</a>);
<a name="L137" href="source/net/ipv4/inet_timewait_sock.c#L137">137</a>         <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(hashinfo, sk-&gt;<a href="ident?i=sk_hash">sk_hash</a>);
<a name="L138" href="source/net/ipv4/inet_timewait_sock.c#L138">138</a>         struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *bhead;
<a name="L139" href="source/net/ipv4/inet_timewait_sock.c#L139">139</a>         <b><i>/* Step 1: Put TW into bind hash. Original socket stays there too.</i></b>
<a name="L140" href="source/net/ipv4/inet_timewait_sock.c#L140">140</a> <b><i>           Note, that any socket with inet-&gt;num != 0 MUST be bound in</i></b>
<a name="L141" href="source/net/ipv4/inet_timewait_sock.c#L141">141</a> <b><i>           binding cache, even if it is closed.</i></b>
<a name="L142" href="source/net/ipv4/inet_timewait_sock.c#L142">142</a> <b><i>         */</i></b>
<a name="L143" href="source/net/ipv4/inet_timewait_sock.c#L143">143</a>         bhead = &amp;hashinfo-&gt;bhash[<a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>), inet-&gt;<a href="ident?i=inet_num">inet_num</a>,
<a name="L144" href="source/net/ipv4/inet_timewait_sock.c#L144">144</a>                         hashinfo-&gt;bhash_size)];
<a name="L145" href="source/net/ipv4/inet_timewait_sock.c#L145">145</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;bhead-&gt;<a href="ident?i=lock">lock</a>);
<a name="L146" href="source/net/ipv4/inet_timewait_sock.c#L146">146</a>         <a href="ident?i=tw">tw</a>-&gt;tw_tb = icsk-&gt;icsk_bind_hash;
<a name="L147" href="source/net/ipv4/inet_timewait_sock.c#L147">147</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!icsk-&gt;icsk_bind_hash);
<a name="L148" href="source/net/ipv4/inet_timewait_sock.c#L148">148</a>         <a href="ident?i=inet_twsk_add_bind_node">inet_twsk_add_bind_node</a>(<a href="ident?i=tw">tw</a>, &amp;<a href="ident?i=tw">tw</a>-&gt;tw_tb-&gt;owners);
<a name="L149" href="source/net/ipv4/inet_timewait_sock.c#L149">149</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;bhead-&gt;<a href="ident?i=lock">lock</a>);
<a name="L150" href="source/net/ipv4/inet_timewait_sock.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/inet_timewait_sock.c#L151">151</a>         <a href="ident?i=spin_lock">spin_lock</a>(<a href="ident?i=lock">lock</a>);
<a name="L152" href="source/net/ipv4/inet_timewait_sock.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/inet_timewait_sock.c#L153">153</a>         <b><i>/*</i></b>
<a name="L154" href="source/net/ipv4/inet_timewait_sock.c#L154">154</a> <b><i>         * Step 2: Hash TW into tcp ehash chain.</i></b>
<a name="L155" href="source/net/ipv4/inet_timewait_sock.c#L155">155</a> <b><i>         * Notes :</i></b>
<a name="L156" href="source/net/ipv4/inet_timewait_sock.c#L156">156</a> <b><i>         * - tw_refcnt is set to 3 because :</i></b>
<a name="L157" href="source/net/ipv4/inet_timewait_sock.c#L157">157</a> <b><i>         * - We have one reference from bhash chain.</i></b>
<a name="L158" href="source/net/ipv4/inet_timewait_sock.c#L158">158</a> <b><i>         * - We have one reference from ehash chain.</i></b>
<a name="L159" href="source/net/ipv4/inet_timewait_sock.c#L159">159</a> <b><i>         * We can use atomic_set() because prior spin_lock()/spin_unlock()</i></b>
<a name="L160" href="source/net/ipv4/inet_timewait_sock.c#L160">160</a> <b><i>         * committed into memory all tw fields.</i></b>
<a name="L161" href="source/net/ipv4/inet_timewait_sock.c#L161">161</a> <b><i>         */</i></b>
<a name="L162" href="source/net/ipv4/inet_timewait_sock.c#L162">162</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>, 1 + 1 + 1);
<a name="L163" href="source/net/ipv4/inet_timewait_sock.c#L163">163</a>         <a href="ident?i=inet_twsk_add_node_rcu">inet_twsk_add_node_rcu</a>(<a href="ident?i=tw">tw</a>, &amp;ehead-&gt;<a href="ident?i=chain">chain</a>);
<a name="L164" href="source/net/ipv4/inet_timewait_sock.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/inet_timewait_sock.c#L165">165</a>         <b><i>/* Step 3: Remove SK from hash chain */</i></b>
<a name="L166" href="source/net/ipv4/inet_timewait_sock.c#L166">166</a>         if (<a href="ident?i=__sk_nulls_del_node_init_rcu">__sk_nulls_del_node_init_rcu</a>(sk))
<a name="L167" href="source/net/ipv4/inet_timewait_sock.c#L167">167</a>                 <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, -1);
<a name="L168" href="source/net/ipv4/inet_timewait_sock.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/inet_timewait_sock.c#L169">169</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(<a href="ident?i=lock">lock</a>);
<a name="L170" href="source/net/ipv4/inet_timewait_sock.c#L170">170</a> }
<a name="L171" href="source/net/ipv4/inet_timewait_sock.c#L171">171</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__inet_twsk_hashdance">__inet_twsk_hashdance</a>);
<a name="L172" href="source/net/ipv4/inet_timewait_sock.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/inet_timewait_sock.c#L173">173</a> void <a href="ident?i=tw_timer_handler">tw_timer_handler</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L174" href="source/net/ipv4/inet_timewait_sock.c#L174">174</a> {
<a name="L175" href="source/net/ipv4/inet_timewait_sock.c#L175">175</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a> = (struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *)<a href="ident?i=data">data</a>;
<a name="L176" href="source/net/ipv4/inet_timewait_sock.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/inet_timewait_sock.c#L177">177</a>         if (<a href="ident?i=tw">tw</a>-&gt;tw_kill)
<a name="L178" href="source/net/ipv4/inet_timewait_sock.c#L178">178</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>), LINUX_MIB_TIMEWAITKILLED);
<a name="L179" href="source/net/ipv4/inet_timewait_sock.c#L179">179</a>         else
<a name="L180" href="source/net/ipv4/inet_timewait_sock.c#L180">180</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>), LINUX_MIB_TIMEWAITED);
<a name="L181" href="source/net/ipv4/inet_timewait_sock.c#L181">181</a>         <a href="ident?i=inet_twsk_kill">inet_twsk_kill</a>(<a href="ident?i=tw">tw</a>);
<a name="L182" href="source/net/ipv4/inet_timewait_sock.c#L182">182</a> }
<a name="L183" href="source/net/ipv4/inet_timewait_sock.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/inet_timewait_sock.c#L184">184</a> struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=inet_twsk_alloc">inet_twsk_alloc</a>(const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L185" href="source/net/ipv4/inet_timewait_sock.c#L185">185</a>                                            struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> *dr,
<a name="L186" href="source/net/ipv4/inet_timewait_sock.c#L186">186</a>                                            const int <a href="ident?i=state">state</a>)
<a name="L187" href="source/net/ipv4/inet_timewait_sock.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/inet_timewait_sock.c#L188">188</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>;
<a name="L189" href="source/net/ipv4/inet_timewait_sock.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/inet_timewait_sock.c#L190">190</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;dr-&gt;tw_count) &gt;= dr-&gt;sysctl_max_tw_buckets)
<a name="L191" href="source/net/ipv4/inet_timewait_sock.c#L191">191</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L192" href="source/net/ipv4/inet_timewait_sock.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/inet_timewait_sock.c#L193">193</a>         <a href="ident?i=tw">tw</a> = <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(sk-&gt;sk_prot_creator-&gt;twsk_prot-&gt;twsk_slab,
<a name="L194" href="source/net/ipv4/inet_timewait_sock.c#L194">194</a>                               <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L195" href="source/net/ipv4/inet_timewait_sock.c#L195">195</a>         if (<a href="ident?i=tw">tw</a>) {
<a name="L196" href="source/net/ipv4/inet_timewait_sock.c#L196">196</a>                 const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L197" href="source/net/ipv4/inet_timewait_sock.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/inet_timewait_sock.c#L198">198</a>                 <a href="ident?i=kmemcheck_annotate_bitfield">kmemcheck_annotate_bitfield</a>(<a href="ident?i=tw">tw</a>, <a href="ident?i=flags">flags</a>);
<a name="L199" href="source/net/ipv4/inet_timewait_sock.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/inet_timewait_sock.c#L200">200</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_dr           = dr;
<a name="L201" href="source/net/ipv4/inet_timewait_sock.c#L201">201</a>                 <b><i>/* Give us an identity. */</i></b>
<a name="L202" href="source/net/ipv4/inet_timewait_sock.c#L202">202</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_daddr">tw_daddr</a>        = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L203" href="source/net/ipv4/inet_timewait_sock.c#L203">203</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_rcv_saddr">tw_rcv_saddr</a>    = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L204" href="source/net/ipv4/inet_timewait_sock.c#L204">204</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_bound_dev_if">tw_bound_dev_if</a> = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L205" href="source/net/ipv4/inet_timewait_sock.c#L205">205</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_tos          = inet-&gt;tos;
<a name="L206" href="source/net/ipv4/inet_timewait_sock.c#L206">206</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_num">tw_num</a>          = inet-&gt;<a href="ident?i=inet_num">inet_num</a>;
<a name="L207" href="source/net/ipv4/inet_timewait_sock.c#L207">207</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_state">tw_state</a>        = TCP_TIME_WAIT;
<a name="L208" href="source/net/ipv4/inet_timewait_sock.c#L208">208</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_substate     = <a href="ident?i=state">state</a>;
<a name="L209" href="source/net/ipv4/inet_timewait_sock.c#L209">209</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_sport        = inet-&gt;inet_sport;
<a name="L210" href="source/net/ipv4/inet_timewait_sock.c#L210">210</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_dport">tw_dport</a>        = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L211" href="source/net/ipv4/inet_timewait_sock.c#L211">211</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_family">tw_family</a>       = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L212" href="source/net/ipv4/inet_timewait_sock.c#L212">212</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_reuse">tw_reuse</a>        = sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a>;
<a name="L213" href="source/net/ipv4/inet_timewait_sock.c#L213">213</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_hash">tw_hash</a>         = sk-&gt;<a href="ident?i=sk_hash">sk_hash</a>;
<a name="L214" href="source/net/ipv4/inet_timewait_sock.c#L214">214</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_ipv6only">tw_ipv6only</a>     = 0;
<a name="L215" href="source/net/ipv4/inet_timewait_sock.c#L215">215</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_transparent  = inet-&gt;transparent;
<a name="L216" href="source/net/ipv4/inet_timewait_sock.c#L216">216</a>                 <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_prot">tw_prot</a>         = sk-&gt;sk_prot_creator;
<a name="L217" href="source/net/ipv4/inet_timewait_sock.c#L217">217</a>                 <a href="ident?i=atomic64_set">atomic64_set</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_cookie">tw_cookie</a>, <a href="ident?i=atomic64_read">atomic64_read</a>(&amp;sk-&gt;<a href="ident?i=sk_cookie">sk_cookie</a>));
<a name="L218" href="source/net/ipv4/inet_timewait_sock.c#L218">218</a>                 <a href="ident?i=twsk_net_set">twsk_net_set</a>(<a href="ident?i=tw">tw</a>, <a href="ident?i=sock_net">sock_net</a>(sk));
<a name="L219" href="source/net/ipv4/inet_timewait_sock.c#L219">219</a>                 <a href="ident?i=setup_timer">setup_timer</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;tw_timer, <a href="ident?i=tw_timer_handler">tw_timer_handler</a>, (unsigned long)<a href="ident?i=tw">tw</a>);
<a name="L220" href="source/net/ipv4/inet_timewait_sock.c#L220">220</a>                 <b><i>/*</i></b>
<a name="L221" href="source/net/ipv4/inet_timewait_sock.c#L221">221</a> <b><i>                 * Because we use RCU lookups, we should not set tw_refcnt</i></b>
<a name="L222" href="source/net/ipv4/inet_timewait_sock.c#L222">222</a> <b><i>                 * to a non null value before everything is setup for this</i></b>
<a name="L223" href="source/net/ipv4/inet_timewait_sock.c#L223">223</a> <b><i>                 * timewait socket.</i></b>
<a name="L224" href="source/net/ipv4/inet_timewait_sock.c#L224">224</a> <b><i>                 */</i></b>
<a name="L225" href="source/net/ipv4/inet_timewait_sock.c#L225">225</a>                 <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>, 0);
<a name="L226" href="source/net/ipv4/inet_timewait_sock.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/inet_timewait_sock.c#L227">227</a>                 <a href="ident?i=__module_get">__module_get</a>(<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_prot">tw_prot</a>-&gt;owner);
<a name="L228" href="source/net/ipv4/inet_timewait_sock.c#L228">228</a>         }
<a name="L229" href="source/net/ipv4/inet_timewait_sock.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/inet_timewait_sock.c#L230">230</a>         return <a href="ident?i=tw">tw</a>;
<a name="L231" href="source/net/ipv4/inet_timewait_sock.c#L231">231</a> }
<a name="L232" href="source/net/ipv4/inet_timewait_sock.c#L232">232</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_twsk_alloc">inet_twsk_alloc</a>);
<a name="L233" href="source/net/ipv4/inet_timewait_sock.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/inet_timewait_sock.c#L234">234</a> <b><i>/* These are always called from BH context.  See callers in</i></b>
<a name="L235" href="source/net/ipv4/inet_timewait_sock.c#L235">235</a> <b><i> * tcp_input.c to verify this.</i></b>
<a name="L236" href="source/net/ipv4/inet_timewait_sock.c#L236">236</a> <b><i> */</i></b>
<a name="L237" href="source/net/ipv4/inet_timewait_sock.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/inet_timewait_sock.c#L238">238</a> <b><i>/* This is for handling early-kills of TIME_WAIT sockets. */</i></b>
<a name="L239" href="source/net/ipv4/inet_timewait_sock.c#L239">239</a> void <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>)
<a name="L240" href="source/net/ipv4/inet_timewait_sock.c#L240">240</a> {
<a name="L241" href="source/net/ipv4/inet_timewait_sock.c#L241">241</a>         if (<a href="ident?i=del_timer_sync">del_timer_sync</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;tw_timer))
<a name="L242" href="source/net/ipv4/inet_timewait_sock.c#L242">242</a>                 <a href="ident?i=inet_twsk_kill">inet_twsk_kill</a>(<a href="ident?i=tw">tw</a>);
<a name="L243" href="source/net/ipv4/inet_timewait_sock.c#L243">243</a> }
<a name="L244" href="source/net/ipv4/inet_timewait_sock.c#L244">244</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>);
<a name="L245" href="source/net/ipv4/inet_timewait_sock.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/inet_timewait_sock.c#L246">246</a> void <a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>, const int timeo)
<a name="L247" href="source/net/ipv4/inet_timewait_sock.c#L247">247</a> {
<a name="L248" href="source/net/ipv4/inet_timewait_sock.c#L248">248</a>         <b><i>/* timeout := RTO * 3.5</i></b>
<a name="L249" href="source/net/ipv4/inet_timewait_sock.c#L249">249</a> <b><i>         *</i></b>
<a name="L250" href="source/net/ipv4/inet_timewait_sock.c#L250">250</a> <b><i>         * 3.5 = 1+2+0.5 to wait for two retransmits.</i></b>
<a name="L251" href="source/net/ipv4/inet_timewait_sock.c#L251">251</a> <b><i>         *</i></b>
<a name="L252" href="source/net/ipv4/inet_timewait_sock.c#L252">252</a> <b><i>         * RATIONALE: if FIN arrived and we entered TIME-WAIT state,</i></b>
<a name="L253" href="source/net/ipv4/inet_timewait_sock.c#L253">253</a> <b><i>         * our ACK acking that FIN can be lost. If N subsequent retransmitted</i></b>
<a name="L254" href="source/net/ipv4/inet_timewait_sock.c#L254">254</a> <b><i>         * FINs (or previous seqments) are lost (probability of such event</i></b>
<a name="L255" href="source/net/ipv4/inet_timewait_sock.c#L255">255</a> <b><i>         * is p^(N+1), where p is probability to lose single packet and</i></b>
<a name="L256" href="source/net/ipv4/inet_timewait_sock.c#L256">256</a> <b><i>         * time to detect the loss is about RTO*(2^N - 1) with exponential</i></b>
<a name="L257" href="source/net/ipv4/inet_timewait_sock.c#L257">257</a> <b><i>         * backoff). Normal timewait length is calculated so, that we</i></b>
<a name="L258" href="source/net/ipv4/inet_timewait_sock.c#L258">258</a> <b><i>         * waited at least for one retransmitted FIN (maximal RTO is 120sec).</i></b>
<a name="L259" href="source/net/ipv4/inet_timewait_sock.c#L259">259</a> <b><i>         * [ BTW Linux. following BSD, violates this requirement waiting</i></b>
<a name="L260" href="source/net/ipv4/inet_timewait_sock.c#L260">260</a> <b><i>         *   only for 60sec, we should wait at least for 240 secs.</i></b>
<a name="L261" href="source/net/ipv4/inet_timewait_sock.c#L261">261</a> <b><i>         *   Well, 240 consumes too much of resources 8)</i></b>
<a name="L262" href="source/net/ipv4/inet_timewait_sock.c#L262">262</a> <b><i>         * ]</i></b>
<a name="L263" href="source/net/ipv4/inet_timewait_sock.c#L263">263</a> <b><i>         * This interval is not reduced to catch old duplicate and</i></b>
<a name="L264" href="source/net/ipv4/inet_timewait_sock.c#L264">264</a> <b><i>         * responces to our wandering segments living for two MSLs.</i></b>
<a name="L265" href="source/net/ipv4/inet_timewait_sock.c#L265">265</a> <b><i>         * However, if we use PAWS to detect</i></b>
<a name="L266" href="source/net/ipv4/inet_timewait_sock.c#L266">266</a> <b><i>         * old duplicates, we can reduce the interval to bounds required</i></b>
<a name="L267" href="source/net/ipv4/inet_timewait_sock.c#L267">267</a> <b><i>         * by RTO, rather than MSL. So, if peer understands PAWS, we</i></b>
<a name="L268" href="source/net/ipv4/inet_timewait_sock.c#L268">268</a> <b><i>         * kill tw bucket after 3.5*RTO (it is important that this number</i></b>
<a name="L269" href="source/net/ipv4/inet_timewait_sock.c#L269">269</a> <b><i>         * is greater than TS tick!) and detect old duplicates with help</i></b>
<a name="L270" href="source/net/ipv4/inet_timewait_sock.c#L270">270</a> <b><i>         * of PAWS.</i></b>
<a name="L271" href="source/net/ipv4/inet_timewait_sock.c#L271">271</a> <b><i>         */</i></b>
<a name="L272" href="source/net/ipv4/inet_timewait_sock.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/inet_timewait_sock.c#L273">273</a>         <a href="ident?i=tw">tw</a>-&gt;tw_kill = timeo &lt;= 4*<a href="ident?i=HZ">HZ</a>;
<a name="L274" href="source/net/ipv4/inet_timewait_sock.c#L274">274</a>         if (!<a href="ident?i=mod_timer_pinned">mod_timer_pinned</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;tw_timer, <a href="ident?i=jiffies">jiffies</a> + timeo)) {
<a name="L275" href="source/net/ipv4/inet_timewait_sock.c#L275">275</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>);
<a name="L276" href="source/net/ipv4/inet_timewait_sock.c#L276">276</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;tw_dr-&gt;tw_count);
<a name="L277" href="source/net/ipv4/inet_timewait_sock.c#L277">277</a>         }
<a name="L278" href="source/net/ipv4/inet_timewait_sock.c#L278">278</a> }
<a name="L279" href="source/net/ipv4/inet_timewait_sock.c#L279">279</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>);
<a name="L280" href="source/net/ipv4/inet_timewait_sock.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/inet_timewait_sock.c#L281">281</a> void <a href="ident?i=inet_twsk_purge">inet_twsk_purge</a>(struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo,
<a name="L282" href="source/net/ipv4/inet_timewait_sock.c#L282">282</a>                      struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> *twdr, int <a href="ident?i=family">family</a>)
<a name="L283" href="source/net/ipv4/inet_timewait_sock.c#L283">283</a> {
<a name="L284" href="source/net/ipv4/inet_timewait_sock.c#L284">284</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>;
<a name="L285" href="source/net/ipv4/inet_timewait_sock.c#L285">285</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L286" href="source/net/ipv4/inet_timewait_sock.c#L286">286</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L287" href="source/net/ipv4/inet_timewait_sock.c#L287">287</a>         unsigned int <a href="ident?i=slot">slot</a>;
<a name="L288" href="source/net/ipv4/inet_timewait_sock.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/inet_timewait_sock.c#L289">289</a>         for (<a href="ident?i=slot">slot</a> = 0; <a href="ident?i=slot">slot</a> &lt;= hashinfo-&gt;ehash_mask; <a href="ident?i=slot">slot</a>++) {
<a name="L290" href="source/net/ipv4/inet_timewait_sock.c#L290">290</a>                 struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a> *<a href="ident?i=head">head</a> = &amp;hashinfo-&gt;ehash[<a href="ident?i=slot">slot</a>];
<a name="L291" href="source/net/ipv4/inet_timewait_sock.c#L291">291</a> restart_rcu:
<a name="L292" href="source/net/ipv4/inet_timewait_sock.c#L292">292</a>                 <a href="ident?i=cond_resched">cond_resched</a>();
<a name="L293" href="source/net/ipv4/inet_timewait_sock.c#L293">293</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L294" href="source/net/ipv4/inet_timewait_sock.c#L294">294</a> <a href="ident?i=restart">restart</a>:
<a name="L295" href="source/net/ipv4/inet_timewait_sock.c#L295">295</a>                 <a href="ident?i=sk_nulls_for_each_rcu">sk_nulls_for_each_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>) {
<a name="L296" href="source/net/ipv4/inet_timewait_sock.c#L296">296</a>                         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_TIME_WAIT)
<a name="L297" href="source/net/ipv4/inet_timewait_sock.c#L297">297</a>                                 continue;
<a name="L298" href="source/net/ipv4/inet_timewait_sock.c#L298">298</a>                         <a href="ident?i=tw">tw</a> = <a href="ident?i=inet_twsk">inet_twsk</a>(sk);
<a name="L299" href="source/net/ipv4/inet_timewait_sock.c#L299">299</a>                         if ((<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_family">tw_family</a> != <a href="ident?i=family">family</a>) ||
<a name="L300" href="source/net/ipv4/inet_timewait_sock.c#L300">300</a>                                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>)-&gt;<a href="ident?i=count">count</a>))
<a name="L301" href="source/net/ipv4/inet_timewait_sock.c#L301">301</a>                                 continue;
<a name="L302" href="source/net/ipv4/inet_timewait_sock.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/inet_timewait_sock.c#L303">303</a>                         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>)))
<a name="L304" href="source/net/ipv4/inet_timewait_sock.c#L304">304</a>                                 continue;
<a name="L305" href="source/net/ipv4/inet_timewait_sock.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/inet_timewait_sock.c#L306">306</a>                         if (<a href="ident?i=unlikely">unlikely</a>((<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_family">tw_family</a> != <a href="ident?i=family">family</a>) ||
<a name="L307" href="source/net/ipv4/inet_timewait_sock.c#L307">307</a>                                      <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>)-&gt;<a href="ident?i=count">count</a>))) {
<a name="L308" href="source/net/ipv4/inet_timewait_sock.c#L308">308</a>                                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L309" href="source/net/ipv4/inet_timewait_sock.c#L309">309</a>                                 goto <a href="ident?i=restart">restart</a>;
<a name="L310" href="source/net/ipv4/inet_timewait_sock.c#L310">310</a>                         }
<a name="L311" href="source/net/ipv4/inet_timewait_sock.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/inet_timewait_sock.c#L312">312</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L313" href="source/net/ipv4/inet_timewait_sock.c#L313">313</a>                         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L314" href="source/net/ipv4/inet_timewait_sock.c#L314">314</a>                         <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(<a href="ident?i=tw">tw</a>);
<a name="L315" href="source/net/ipv4/inet_timewait_sock.c#L315">315</a>                         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L316" href="source/net/ipv4/inet_timewait_sock.c#L316">316</a>                         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L317" href="source/net/ipv4/inet_timewait_sock.c#L317">317</a>                         goto restart_rcu;
<a name="L318" href="source/net/ipv4/inet_timewait_sock.c#L318">318</a>                 }
<a name="L319" href="source/net/ipv4/inet_timewait_sock.c#L319">319</a>                 <b><i>/* If the nulls value we got at the end of this lookup is</i></b>
<a name="L320" href="source/net/ipv4/inet_timewait_sock.c#L320">320</a> <b><i>                 * not the expected one, we must restart lookup.</i></b>
<a name="L321" href="source/net/ipv4/inet_timewait_sock.c#L321">321</a> <b><i>                 * We probably met an item that was moved to another chain.</i></b>
<a name="L322" href="source/net/ipv4/inet_timewait_sock.c#L322">322</a> <b><i>                 */</i></b>
<a name="L323" href="source/net/ipv4/inet_timewait_sock.c#L323">323</a>                 if (<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=node">node</a>) != <a href="ident?i=slot">slot</a>)
<a name="L324" href="source/net/ipv4/inet_timewait_sock.c#L324">324</a>                         goto <a href="ident?i=restart">restart</a>;
<a name="L325" href="source/net/ipv4/inet_timewait_sock.c#L325">325</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L326" href="source/net/ipv4/inet_timewait_sock.c#L326">326</a>         }
<a name="L327" href="source/net/ipv4/inet_timewait_sock.c#L327">327</a> }
<a name="L328" href="source/net/ipv4/inet_timewait_sock.c#L328">328</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_twsk_purge">inet_twsk_purge</a>);
<a name="L329" href="source/net/ipv4/inet_timewait_sock.c#L329">329</a> </pre></div><p>
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
