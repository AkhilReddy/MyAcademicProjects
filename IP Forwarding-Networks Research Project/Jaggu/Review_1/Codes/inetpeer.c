<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inetpeer.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inetpeer.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inetpeer.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inetpeer.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inetpeer.c">inetpeer.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inetpeer.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inetpeer.c#L2">2</a> <b><i> *              INETPEER - A storage for permanent information about peers</i></b>
  <a name="L3" href="source/net/ipv4/inetpeer.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/inetpeer.c#L4">4</a> <b><i> *  This source is covered by the GNU GPL, the same as all kernel sources.</i></b>
  <a name="L5" href="source/net/ipv4/inetpeer.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/inetpeer.c#L6">6</a> <b><i> *  Authors:    Andrey V. Savochkin &lt;saw@msu.ru&gt;</i></b>
  <a name="L7" href="source/net/ipv4/inetpeer.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/inetpeer.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/inetpeer.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/inetpeer.c#L10">10</a> #include &lt;linux/types.h&gt;
 <a name="L11" href="source/net/ipv4/inetpeer.c#L11">11</a> #include &lt;linux/slab.h&gt;
 <a name="L12" href="source/net/ipv4/inetpeer.c#L12">12</a> #include &lt;linux/interrupt.h&gt;
 <a name="L13" href="source/net/ipv4/inetpeer.c#L13">13</a> #include &lt;linux/spinlock.h&gt;
 <a name="L14" href="source/net/ipv4/inetpeer.c#L14">14</a> #include &lt;linux/random.h&gt;
 <a name="L15" href="source/net/ipv4/inetpeer.c#L15">15</a> #include &lt;linux/timer.h&gt;
 <a name="L16" href="source/net/ipv4/inetpeer.c#L16">16</a> #include &lt;linux/time.h&gt;
 <a name="L17" href="source/net/ipv4/inetpeer.c#L17">17</a> #include &lt;linux/kernel.h&gt;
 <a name="L18" href="source/net/ipv4/inetpeer.c#L18">18</a> #include &lt;linux/mm.h&gt;
 <a name="L19" href="source/net/ipv4/inetpeer.c#L19">19</a> #include &lt;linux/net.h&gt;
 <a name="L20" href="source/net/ipv4/inetpeer.c#L20">20</a> #include &lt;linux/workqueue.h&gt;
 <a name="L21" href="source/net/ipv4/inetpeer.c#L21">21</a> #include &lt;net/ip.h&gt;
 <a name="L22" href="source/net/ipv4/inetpeer.c#L22">22</a> #include &lt;net/inetpeer.h&gt;
 <a name="L23" href="source/net/ipv4/inetpeer.c#L23">23</a> #include &lt;net/secure_seq.h&gt;
 <a name="L24" href="source/net/ipv4/inetpeer.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/inetpeer.c#L25">25</a> <b><i>/*</i></b>
 <a name="L26" href="source/net/ipv4/inetpeer.c#L26">26</a> <b><i> *  Theory of operations.</i></b>
 <a name="L27" href="source/net/ipv4/inetpeer.c#L27">27</a> <b><i> *  We keep one entry for each peer IP address.  The nodes contains long-living</i></b>
 <a name="L28" href="source/net/ipv4/inetpeer.c#L28">28</a> <b><i> *  information about the peer which doesn't depend on routes.</i></b>
 <a name="L29" href="source/net/ipv4/inetpeer.c#L29">29</a> <b><i> *</i></b>
 <a name="L30" href="source/net/ipv4/inetpeer.c#L30">30</a> <b><i> *  Nodes are removed only when reference counter goes to 0.</i></b>
 <a name="L31" href="source/net/ipv4/inetpeer.c#L31">31</a> <b><i> *  When it's happened the node may be removed when a sufficient amount of</i></b>
 <a name="L32" href="source/net/ipv4/inetpeer.c#L32">32</a> <b><i> *  time has been passed since its last use.  The less-recently-used entry can</i></b>
 <a name="L33" href="source/net/ipv4/inetpeer.c#L33">33</a> <b><i> *  also be removed if the pool is overloaded i.e. if the total amount of</i></b>
 <a name="L34" href="source/net/ipv4/inetpeer.c#L34">34</a> <b><i> *  entries is greater-or-equal than the threshold.</i></b>
 <a name="L35" href="source/net/ipv4/inetpeer.c#L35">35</a> <b><i> *</i></b>
 <a name="L36" href="source/net/ipv4/inetpeer.c#L36">36</a> <b><i> *  Node pool is organised as an AVL tree.</i></b>
 <a name="L37" href="source/net/ipv4/inetpeer.c#L37">37</a> <b><i> *  Such an implementation has been chosen not just for fun.  It's a way to</i></b>
 <a name="L38" href="source/net/ipv4/inetpeer.c#L38">38</a> <b><i> *  prevent easy and efficient DoS attacks by creating hash collisions.  A huge</i></b>
 <a name="L39" href="source/net/ipv4/inetpeer.c#L39">39</a> <b><i> *  amount of long living nodes in a single hash slot would significantly delay</i></b>
 <a name="L40" href="source/net/ipv4/inetpeer.c#L40">40</a> <b><i> *  lookups performed with disabled BHs.</i></b>
 <a name="L41" href="source/net/ipv4/inetpeer.c#L41">41</a> <b><i> *</i></b>
 <a name="L42" href="source/net/ipv4/inetpeer.c#L42">42</a> <b><i> *  Serialisation issues.</i></b>
 <a name="L43" href="source/net/ipv4/inetpeer.c#L43">43</a> <b><i> *  1.  Nodes may appear in the tree only with the pool lock held.</i></b>
 <a name="L44" href="source/net/ipv4/inetpeer.c#L44">44</a> <b><i> *  2.  Nodes may disappear from the tree only with the pool lock held</i></b>
 <a name="L45" href="source/net/ipv4/inetpeer.c#L45">45</a> <b><i> *      AND reference count being 0.</i></b>
 <a name="L46" href="source/net/ipv4/inetpeer.c#L46">46</a> <b><i> *  3.  Global variable peer_total is modified under the pool lock.</i></b>
 <a name="L47" href="source/net/ipv4/inetpeer.c#L47">47</a> <b><i> *  4.  struct inet_peer fields modification:</i></b>
 <a name="L48" href="source/net/ipv4/inetpeer.c#L48">48</a> <b><i> *              avl_left, avl_right, avl_parent, avl_height: pool lock</i></b>
 <a name="L49" href="source/net/ipv4/inetpeer.c#L49">49</a> <b><i> *              refcnt: atomically against modifications on other CPU;</i></b>
 <a name="L50" href="source/net/ipv4/inetpeer.c#L50">50</a> <b><i> *                 usually under some other lock to prevent node disappearing</i></b>
 <a name="L51" href="source/net/ipv4/inetpeer.c#L51">51</a> <b><i> *              daddr: unchangeable</i></b>
 <a name="L52" href="source/net/ipv4/inetpeer.c#L52">52</a> <b><i> */</i></b>
 <a name="L53" href="source/net/ipv4/inetpeer.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/inetpeer.c#L54">54</a> static struct <a href="ident?i=kmem_cache">kmem_cache</a> *peer_cachep <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L55" href="source/net/ipv4/inetpeer.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/inetpeer.c#L56">56</a> static <a href="ident?i=LIST_HEAD">LIST_HEAD</a>(gc_list);
 <a name="L57" href="source/net/ipv4/inetpeer.c#L57">57</a> static const int <a href="ident?i=gc_delay">gc_delay</a> = 60 * <a href="ident?i=HZ">HZ</a>;
 <a name="L58" href="source/net/ipv4/inetpeer.c#L58">58</a> static struct <a href="ident?i=delayed_work">delayed_work</a> <a href="ident?i=gc_work">gc_work</a>;
 <a name="L59" href="source/net/ipv4/inetpeer.c#L59">59</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(gc_lock);
 <a name="L60" href="source/net/ipv4/inetpeer.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/inetpeer.c#L61">61</a> #define <a href="ident?i=node_height">node_height</a>(<a href="ident?i=x">x</a>) <a href="ident?i=x">x</a>-&gt;avl_height
 <a name="L62" href="source/net/ipv4/inetpeer.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/inetpeer.c#L63">63</a> #define <a href="ident?i=peer_avl_empty">peer_avl_empty</a> ((struct <a href="ident?i=inet_peer">inet_peer</a> *)&amp;<a href="ident?i=peer_fake_node">peer_fake_node</a>)
 <a name="L64" href="source/net/ipv4/inetpeer.c#L64">64</a> #define <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a> ((struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> <a href="ident?i=__force">__force</a> *)&amp;<a href="ident?i=peer_fake_node">peer_fake_node</a>)
 <a name="L65" href="source/net/ipv4/inetpeer.c#L65">65</a> static const struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=peer_fake_node">peer_fake_node</a> = {
 <a name="L66" href="source/net/ipv4/inetpeer.c#L66">66</a>         .avl_left       = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>,
 <a name="L67" href="source/net/ipv4/inetpeer.c#L67">67</a>         .avl_right      = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>,
 <a name="L68" href="source/net/ipv4/inetpeer.c#L68">68</a>         .avl_height     = 0
 <a name="L69" href="source/net/ipv4/inetpeer.c#L69">69</a> };
 <a name="L70" href="source/net/ipv4/inetpeer.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/inetpeer.c#L71">71</a> void <a href="ident?i=inet_peer_base_init">inet_peer_base_init</a>(struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *bp)
 <a name="L72" href="source/net/ipv4/inetpeer.c#L72">72</a> {
 <a name="L73" href="source/net/ipv4/inetpeer.c#L73">73</a>         bp-&gt;<a href="ident?i=root">root</a> = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;
 <a name="L74" href="source/net/ipv4/inetpeer.c#L74">74</a>         <a href="ident?i=seqlock_init">seqlock_init</a>(&amp;bp-&gt;<a href="ident?i=lock">lock</a>);
 <a name="L75" href="source/net/ipv4/inetpeer.c#L75">75</a>         bp-&gt;total = 0;
 <a name="L76" href="source/net/ipv4/inetpeer.c#L76">76</a> }
 <a name="L77" href="source/net/ipv4/inetpeer.c#L77">77</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_peer_base_init">inet_peer_base_init</a>);
 <a name="L78" href="source/net/ipv4/inetpeer.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/inetpeer.c#L79">79</a> #define <a href="ident?i=PEER_MAXDEPTH">PEER_MAXDEPTH</a> 40 <b><i>/* sufficient for about 2^27 nodes */</i></b>
 <a name="L80" href="source/net/ipv4/inetpeer.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/inetpeer.c#L81">81</a> <b><i>/* Exported for sysctl_net_ipv4.  */</i></b>
 <a name="L82" href="source/net/ipv4/inetpeer.c#L82">82</a> int <a href="ident?i=inet_peer_threshold">inet_peer_threshold</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 65536 + 128;    <b><i>/* start to throw entries more</i></b>
 <a name="L83" href="source/net/ipv4/inetpeer.c#L83">83</a> <b><i>                                         * aggressively at this stage */</i></b>
 <a name="L84" href="source/net/ipv4/inetpeer.c#L84">84</a> int <a href="ident?i=inet_peer_minttl">inet_peer_minttl</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 120 * <a href="ident?i=HZ">HZ</a>;  <b><i>/* TTL under high load: 120 sec */</i></b>
 <a name="L85" href="source/net/ipv4/inetpeer.c#L85">85</a> int <a href="ident?i=inet_peer_maxttl">inet_peer_maxttl</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 10 * 60 * <a href="ident?i=HZ">HZ</a>;      <b><i>/* usual time to live: 10 min */</i></b>
 <a name="L86" href="source/net/ipv4/inetpeer.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/inetpeer.c#L87">87</a> static void <a href="ident?i=inetpeer_gc_worker">inetpeer_gc_worker</a>(struct <a href="ident?i=work_struct">work_struct</a> *<a href="ident?i=work">work</a>)
 <a name="L88" href="source/net/ipv4/inetpeer.c#L88">88</a> {
 <a name="L89" href="source/net/ipv4/inetpeer.c#L89">89</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=p">p</a>, *<a href="ident?i=n">n</a>, *<a href="ident?i=c">c</a>;
 <a name="L90" href="source/net/ipv4/inetpeer.c#L90">90</a>         struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=list">list</a>;
 <a name="L91" href="source/net/ipv4/inetpeer.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/inetpeer.c#L92">92</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;gc_lock);
 <a name="L93" href="source/net/ipv4/inetpeer.c#L93">93</a>         <a href="ident?i=list_replace_init">list_replace_init</a>(&amp;gc_list, &amp;<a href="ident?i=list">list</a>);
 <a name="L94" href="source/net/ipv4/inetpeer.c#L94">94</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;gc_lock);
 <a name="L95" href="source/net/ipv4/inetpeer.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/inetpeer.c#L96">96</a>         if (<a href="ident?i=list_empty">list_empty</a>(&amp;<a href="ident?i=list">list</a>))
 <a name="L97" href="source/net/ipv4/inetpeer.c#L97">97</a>                 return;
 <a name="L98" href="source/net/ipv4/inetpeer.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/inetpeer.c#L99">99</a>         <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=p">p</a>, <a href="ident?i=n">n</a>, &amp;<a href="ident?i=list">list</a>, gc_list) {
<a name="L100" href="source/net/ipv4/inetpeer.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/inetpeer.c#L101">101</a>                 if (<a href="ident?i=need_resched">need_resched</a>())
<a name="L102" href="source/net/ipv4/inetpeer.c#L102">102</a>                         <a href="ident?i=cond_resched">cond_resched</a>();
<a name="L103" href="source/net/ipv4/inetpeer.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/inetpeer.c#L104">104</a>                 <a href="ident?i=c">c</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=p">p</a>-&gt;avl_left, 1);
<a name="L105" href="source/net/ipv4/inetpeer.c#L105">105</a>                 if (<a href="ident?i=c">c</a> != <a href="ident?i=peer_avl_empty">peer_avl_empty</a>) {
<a name="L106" href="source/net/ipv4/inetpeer.c#L106">106</a>                         <a href="ident?i=list_add_tail">list_add_tail</a>(&amp;<a href="ident?i=c">c</a>-&gt;gc_list, &amp;<a href="ident?i=list">list</a>);
<a name="L107" href="source/net/ipv4/inetpeer.c#L107">107</a>                         <a href="ident?i=p">p</a>-&gt;avl_left = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;
<a name="L108" href="source/net/ipv4/inetpeer.c#L108">108</a>                 }
<a name="L109" href="source/net/ipv4/inetpeer.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/inetpeer.c#L110">110</a>                 <a href="ident?i=c">c</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=p">p</a>-&gt;avl_right, 1);
<a name="L111" href="source/net/ipv4/inetpeer.c#L111">111</a>                 if (<a href="ident?i=c">c</a> != <a href="ident?i=peer_avl_empty">peer_avl_empty</a>) {
<a name="L112" href="source/net/ipv4/inetpeer.c#L112">112</a>                         <a href="ident?i=list_add_tail">list_add_tail</a>(&amp;<a href="ident?i=c">c</a>-&gt;gc_list, &amp;<a href="ident?i=list">list</a>);
<a name="L113" href="source/net/ipv4/inetpeer.c#L113">113</a>                         <a href="ident?i=p">p</a>-&gt;avl_right = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;
<a name="L114" href="source/net/ipv4/inetpeer.c#L114">114</a>                 }
<a name="L115" href="source/net/ipv4/inetpeer.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/inetpeer.c#L116">116</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=list_entry">list_entry</a>(<a href="ident?i=p">p</a>-&gt;gc_list.<a href="ident?i=next">next</a>, struct <a href="ident?i=inet_peer">inet_peer</a>, gc_list);
<a name="L117" href="source/net/ipv4/inetpeer.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/inetpeer.c#L118">118</a>                 if (!<a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=p">p</a>-&gt;refcnt)) {
<a name="L119" href="source/net/ipv4/inetpeer.c#L119">119</a>                         <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=p">p</a>-&gt;gc_list);
<a name="L120" href="source/net/ipv4/inetpeer.c#L120">120</a>                         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(peer_cachep, <a href="ident?i=p">p</a>);
<a name="L121" href="source/net/ipv4/inetpeer.c#L121">121</a>                 }
<a name="L122" href="source/net/ipv4/inetpeer.c#L122">122</a>         }
<a name="L123" href="source/net/ipv4/inetpeer.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/inetpeer.c#L124">124</a>         if (<a href="ident?i=list_empty">list_empty</a>(&amp;<a href="ident?i=list">list</a>))
<a name="L125" href="source/net/ipv4/inetpeer.c#L125">125</a>                 return;
<a name="L126" href="source/net/ipv4/inetpeer.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/inetpeer.c#L127">127</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;gc_lock);
<a name="L128" href="source/net/ipv4/inetpeer.c#L128">128</a>         <a href="ident?i=list_splice">list_splice</a>(&amp;<a href="ident?i=list">list</a>, &amp;gc_list);
<a name="L129" href="source/net/ipv4/inetpeer.c#L129">129</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;gc_lock);
<a name="L130" href="source/net/ipv4/inetpeer.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/inetpeer.c#L131">131</a>         <a href="ident?i=schedule_delayed_work">schedule_delayed_work</a>(&amp;<a href="ident?i=gc_work">gc_work</a>, <a href="ident?i=gc_delay">gc_delay</a>);
<a name="L132" href="source/net/ipv4/inetpeer.c#L132">132</a> }
<a name="L133" href="source/net/ipv4/inetpeer.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/inetpeer.c#L134">134</a> <b><i>/* Called from ip_output.c:ip_init  */</i></b>
<a name="L135" href="source/net/ipv4/inetpeer.c#L135">135</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=inet_initpeers">inet_initpeers</a>(void)
<a name="L136" href="source/net/ipv4/inetpeer.c#L136">136</a> {
<a name="L137" href="source/net/ipv4/inetpeer.c#L137">137</a>         struct <a href="ident?i=sysinfo">sysinfo</a> si;
<a name="L138" href="source/net/ipv4/inetpeer.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/inetpeer.c#L139">139</a>         <b><i>/* Use the straight interface to information about memory. */</i></b>
<a name="L140" href="source/net/ipv4/inetpeer.c#L140">140</a>         <a href="ident?i=si_meminfo">si_meminfo</a>(&amp;si);
<a name="L141" href="source/net/ipv4/inetpeer.c#L141">141</a>         <b><i>/* The values below were suggested by Alexey Kuznetsov</i></b>
<a name="L142" href="source/net/ipv4/inetpeer.c#L142">142</a> <b><i>         * &lt;kuznet@ms2.inr.ac.ru&gt;.  I don't have any opinion about the values</i></b>
<a name="L143" href="source/net/ipv4/inetpeer.c#L143">143</a> <b><i>         * myself.  --SAW</i></b>
<a name="L144" href="source/net/ipv4/inetpeer.c#L144">144</a> <b><i>         */</i></b>
<a name="L145" href="source/net/ipv4/inetpeer.c#L145">145</a>         if (si.totalram &lt;= (32768*1024)/<a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L146" href="source/net/ipv4/inetpeer.c#L146">146</a>                 <a href="ident?i=inet_peer_threshold">inet_peer_threshold</a> &gt;&gt;= 1; <b><i>/* max pool size about 1MB on IA32 */</i></b>
<a name="L147" href="source/net/ipv4/inetpeer.c#L147">147</a>         if (si.totalram &lt;= (16384*1024)/<a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L148" href="source/net/ipv4/inetpeer.c#L148">148</a>                 <a href="ident?i=inet_peer_threshold">inet_peer_threshold</a> &gt;&gt;= 1; <b><i>/* about 512KB */</i></b>
<a name="L149" href="source/net/ipv4/inetpeer.c#L149">149</a>         if (si.totalram &lt;= (8192*1024)/<a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L150" href="source/net/ipv4/inetpeer.c#L150">150</a>                 <a href="ident?i=inet_peer_threshold">inet_peer_threshold</a> &gt;&gt;= 2; <b><i>/* about 128KB */</i></b>
<a name="L151" href="source/net/ipv4/inetpeer.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/inetpeer.c#L152">152</a>         peer_cachep = <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<i>"inet_peer_cache"</i>,
<a name="L153" href="source/net/ipv4/inetpeer.c#L153">153</a>                         sizeof(struct <a href="ident?i=inet_peer">inet_peer</a>),
<a name="L154" href="source/net/ipv4/inetpeer.c#L154">154</a>                         0, <a href="ident?i=SLAB_HWCACHE_ALIGN">SLAB_HWCACHE_ALIGN</a> | <a href="ident?i=SLAB_PANIC">SLAB_PANIC</a>,
<a name="L155" href="source/net/ipv4/inetpeer.c#L155">155</a>                         <a href="ident?i=NULL">NULL</a>);
<a name="L156" href="source/net/ipv4/inetpeer.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/inetpeer.c#L157">157</a>         <a href="ident?i=INIT_DEFERRABLE_WORK">INIT_DEFERRABLE_WORK</a>(&amp;<a href="ident?i=gc_work">gc_work</a>, <a href="ident?i=inetpeer_gc_worker">inetpeer_gc_worker</a>);
<a name="L158" href="source/net/ipv4/inetpeer.c#L158">158</a> }
<a name="L159" href="source/net/ipv4/inetpeer.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/inetpeer.c#L160">160</a> static int <a href="ident?i=addr_compare">addr_compare</a>(const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=a">a</a>,
<a name="L161" href="source/net/ipv4/inetpeer.c#L161">161</a>                         const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=b">b</a>)
<a name="L162" href="source/net/ipv4/inetpeer.c#L162">162</a> {
<a name="L163" href="source/net/ipv4/inetpeer.c#L163">163</a>         int <a href="ident?i=i">i</a>, <a href="ident?i=n">n</a> = (<a href="ident?i=a">a</a>-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a> ? 1 : 4);
<a name="L164" href="source/net/ipv4/inetpeer.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/inetpeer.c#L165">165</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=n">n</a>; <a href="ident?i=i">i</a>++) {
<a name="L166" href="source/net/ipv4/inetpeer.c#L166">166</a>                 if (<a href="ident?i=a">a</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a6">a6</a>[<a href="ident?i=i">i</a>] == <a href="ident?i=b">b</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a6">a6</a>[<a href="ident?i=i">i</a>])
<a name="L167" href="source/net/ipv4/inetpeer.c#L167">167</a>                         continue;
<a name="L168" href="source/net/ipv4/inetpeer.c#L168">168</a>                 if ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=a">a</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a6">a6</a>[<a href="ident?i=i">i</a>] &lt; (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=b">b</a>-&gt;<a href="ident?i=addr">addr</a>.<a href="ident?i=a6">a6</a>[<a href="ident?i=i">i</a>])
<a name="L169" href="source/net/ipv4/inetpeer.c#L169">169</a>                         return -1;
<a name="L170" href="source/net/ipv4/inetpeer.c#L170">170</a>                 return 1;
<a name="L171" href="source/net/ipv4/inetpeer.c#L171">171</a>         }
<a name="L172" href="source/net/ipv4/inetpeer.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/inetpeer.c#L173">173</a>         return 0;
<a name="L174" href="source/net/ipv4/inetpeer.c#L174">174</a> }
<a name="L175" href="source/net/ipv4/inetpeer.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/inetpeer.c#L176">176</a> #define <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=X">X</a>, <a href="ident?i=BASE">BASE</a>)                               \
<a name="L177" href="source/net/ipv4/inetpeer.c#L177">177</a>         <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=X">X</a>, <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;(<a href="ident?i=BASE">BASE</a>)-&gt;<a href="ident?i=lock">lock</a>.<a href="ident?i=lock">lock</a>))
<a name="L178" href="source/net/ipv4/inetpeer.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/inetpeer.c#L179">179</a> <b><i>/*</i></b>
<a name="L180" href="source/net/ipv4/inetpeer.c#L180">180</a> <b><i> * Called with local BH disabled and the pool lock held.</i></b>
<a name="L181" href="source/net/ipv4/inetpeer.c#L181">181</a> <b><i> */</i></b>
<a name="L182" href="source/net/ipv4/inetpeer.c#L182">182</a> #define <a href="ident?i=lookup">lookup</a>(_daddr, _stack, _base)                           \
<a name="L183" href="source/net/ipv4/inetpeer.c#L183">183</a> ({                                                              \
<a name="L184" href="source/net/ipv4/inetpeer.c#L184">184</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *u;                                    \
<a name="L185" href="source/net/ipv4/inetpeer.c#L185">185</a>         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=v">v</a>;                             \
<a name="L186" href="source/net/ipv4/inetpeer.c#L186">186</a>                                                                 \
<a name="L187" href="source/net/ipv4/inetpeer.c#L187">187</a>         stackptr = _stack;                                      \
<a name="L188" href="source/net/ipv4/inetpeer.c#L188">188</a>         *stackptr++ = &amp;_base-&gt;<a href="ident?i=root">root</a>;                             \
<a name="L189" href="source/net/ipv4/inetpeer.c#L189">189</a>         for (u = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(_base-&gt;<a href="ident?i=root">root</a>, _base);          \
<a name="L190" href="source/net/ipv4/inetpeer.c#L190">190</a>              u != <a href="ident?i=peer_avl_empty">peer_avl_empty</a>;) {                            \
<a name="L191" href="source/net/ipv4/inetpeer.c#L191">191</a>                 int <a href="ident?i=cmp">cmp</a> = <a href="ident?i=addr_compare">addr_compare</a>(_daddr, &amp;u-&gt;<a href="ident?i=daddr">daddr</a>);      \
<a name="L192" href="source/net/ipv4/inetpeer.c#L192">192</a>                 if (<a href="ident?i=cmp">cmp</a> == 0)                                   \
<a name="L193" href="source/net/ipv4/inetpeer.c#L193">193</a>                         break;                                  \
<a name="L194" href="source/net/ipv4/inetpeer.c#L194">194</a>                 if (<a href="ident?i=cmp">cmp</a> == -1)                                  \
<a name="L195" href="source/net/ipv4/inetpeer.c#L195">195</a>                         <a href="ident?i=v">v</a> = &amp;u-&gt;avl_left;                       \
<a name="L196" href="source/net/ipv4/inetpeer.c#L196">196</a>                 else                                            \
<a name="L197" href="source/net/ipv4/inetpeer.c#L197">197</a>                         <a href="ident?i=v">v</a> = &amp;u-&gt;avl_right;                      \
<a name="L198" href="source/net/ipv4/inetpeer.c#L198">198</a>                 *stackptr++ = <a href="ident?i=v">v</a>;                                \
<a name="L199" href="source/net/ipv4/inetpeer.c#L199">199</a>                 u = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(*<a href="ident?i=v">v</a>, _base);                \
<a name="L200" href="source/net/ipv4/inetpeer.c#L200">200</a>         }                                                       \
<a name="L201" href="source/net/ipv4/inetpeer.c#L201">201</a>         u;                                                      \
<a name="L202" href="source/net/ipv4/inetpeer.c#L202">202</a> })
<a name="L203" href="source/net/ipv4/inetpeer.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/inetpeer.c#L204">204</a> <b><i>/*</i></b>
<a name="L205" href="source/net/ipv4/inetpeer.c#L205">205</a> <b><i> * Called with rcu_read_lock()</i></b>
<a name="L206" href="source/net/ipv4/inetpeer.c#L206">206</a> <b><i> * Because we hold no lock against a writer, its quite possible we fall</i></b>
<a name="L207" href="source/net/ipv4/inetpeer.c#L207">207</a> <b><i> * in an endless loop.</i></b>
<a name="L208" href="source/net/ipv4/inetpeer.c#L208">208</a> <b><i> * But every pointer we follow is guaranteed to be valid thanks to RCU.</i></b>
<a name="L209" href="source/net/ipv4/inetpeer.c#L209">209</a> <b><i> * We exit from this function if number of links exceeds PEER_MAXDEPTH</i></b>
<a name="L210" href="source/net/ipv4/inetpeer.c#L210">210</a> <b><i> */</i></b>
<a name="L211" href="source/net/ipv4/inetpeer.c#L211">211</a> static struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=lookup_rcu">lookup_rcu</a>(const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=daddr">daddr</a>,
<a name="L212" href="source/net/ipv4/inetpeer.c#L212">212</a>                                     struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *<a href="ident?i=base">base</a>)
<a name="L213" href="source/net/ipv4/inetpeer.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/inetpeer.c#L214">214</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *u = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=base">base</a>-&gt;<a href="ident?i=root">root</a>);
<a name="L215" href="source/net/ipv4/inetpeer.c#L215">215</a>         int <a href="ident?i=count">count</a> = 0;
<a name="L216" href="source/net/ipv4/inetpeer.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/inetpeer.c#L217">217</a>         while (u != <a href="ident?i=peer_avl_empty">peer_avl_empty</a>) {
<a name="L218" href="source/net/ipv4/inetpeer.c#L218">218</a>                 int <a href="ident?i=cmp">cmp</a> = <a href="ident?i=addr_compare">addr_compare</a>(<a href="ident?i=daddr">daddr</a>, &amp;u-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L219" href="source/net/ipv4/inetpeer.c#L219">219</a>                 if (<a href="ident?i=cmp">cmp</a> == 0) {
<a name="L220" href="source/net/ipv4/inetpeer.c#L220">220</a>                         <b><i>/* Before taking a reference, check if this entry was</i></b>
<a name="L221" href="source/net/ipv4/inetpeer.c#L221">221</a> <b><i>                         * deleted (refcnt=-1)</i></b>
<a name="L222" href="source/net/ipv4/inetpeer.c#L222">222</a> <b><i>                         */</i></b>
<a name="L223" href="source/net/ipv4/inetpeer.c#L223">223</a>                         if (!<a href="ident?i=atomic_add_unless">atomic_add_unless</a>(&amp;u-&gt;refcnt, 1, -1))
<a name="L224" href="source/net/ipv4/inetpeer.c#L224">224</a>                                 u = <a href="ident?i=NULL">NULL</a>;
<a name="L225" href="source/net/ipv4/inetpeer.c#L225">225</a>                         return u;
<a name="L226" href="source/net/ipv4/inetpeer.c#L226">226</a>                 }
<a name="L227" href="source/net/ipv4/inetpeer.c#L227">227</a>                 if (<a href="ident?i=cmp">cmp</a> == -1)
<a name="L228" href="source/net/ipv4/inetpeer.c#L228">228</a>                         u = <a href="ident?i=rcu_dereference">rcu_dereference</a>(u-&gt;avl_left);
<a name="L229" href="source/net/ipv4/inetpeer.c#L229">229</a>                 else
<a name="L230" href="source/net/ipv4/inetpeer.c#L230">230</a>                         u = <a href="ident?i=rcu_dereference">rcu_dereference</a>(u-&gt;avl_right);
<a name="L231" href="source/net/ipv4/inetpeer.c#L231">231</a>                 if (<a href="ident?i=unlikely">unlikely</a>(++<a href="ident?i=count">count</a> == <a href="ident?i=PEER_MAXDEPTH">PEER_MAXDEPTH</a>))
<a name="L232" href="source/net/ipv4/inetpeer.c#L232">232</a>                         break;
<a name="L233" href="source/net/ipv4/inetpeer.c#L233">233</a>         }
<a name="L234" href="source/net/ipv4/inetpeer.c#L234">234</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L235" href="source/net/ipv4/inetpeer.c#L235">235</a> }
<a name="L236" href="source/net/ipv4/inetpeer.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/inetpeer.c#L237">237</a> <b><i>/* Called with local BH disabled and the pool lock held. */</i></b>
<a name="L238" href="source/net/ipv4/inetpeer.c#L238">238</a> #define <a href="ident?i=lookup_rightempty">lookup_rightempty</a>(<a href="ident?i=start">start</a>, <a href="ident?i=base">base</a>)                          \
<a name="L239" href="source/net/ipv4/inetpeer.c#L239">239</a> ({                                                              \
<a name="L240" href="source/net/ipv4/inetpeer.c#L240">240</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *u;                                    \
<a name="L241" href="source/net/ipv4/inetpeer.c#L241">241</a>         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=v">v</a>;                             \
<a name="L242" href="source/net/ipv4/inetpeer.c#L242">242</a>         *stackptr++ = &amp;<a href="ident?i=start">start</a>-&gt;avl_left;                         \
<a name="L243" href="source/net/ipv4/inetpeer.c#L243">243</a>         <a href="ident?i=v">v</a> = &amp;<a href="ident?i=start">start</a>-&gt;avl_left;                                   \
<a name="L244" href="source/net/ipv4/inetpeer.c#L244">244</a>         for (u = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(*<a href="ident?i=v">v</a>, <a href="ident?i=base">base</a>);                    \
<a name="L245" href="source/net/ipv4/inetpeer.c#L245">245</a>              u-&gt;avl_right != <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;) {             \
<a name="L246" href="source/net/ipv4/inetpeer.c#L246">246</a>                 <a href="ident?i=v">v</a> = &amp;u-&gt;avl_right;                              \
<a name="L247" href="source/net/ipv4/inetpeer.c#L247">247</a>                 *stackptr++ = <a href="ident?i=v">v</a>;                                \
<a name="L248" href="source/net/ipv4/inetpeer.c#L248">248</a>                 u = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(*<a href="ident?i=v">v</a>, <a href="ident?i=base">base</a>);                 \
<a name="L249" href="source/net/ipv4/inetpeer.c#L249">249</a>         }                                                       \
<a name="L250" href="source/net/ipv4/inetpeer.c#L250">250</a>         u;                                                      \
<a name="L251" href="source/net/ipv4/inetpeer.c#L251">251</a> })
<a name="L252" href="source/net/ipv4/inetpeer.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/inetpeer.c#L253">253</a> <b><i>/* Called with local BH disabled and the pool lock held.</i></b>
<a name="L254" href="source/net/ipv4/inetpeer.c#L254">254</a> <b><i> * Variable names are the proof of operation correctness.</i></b>
<a name="L255" href="source/net/ipv4/inetpeer.c#L255">255</a> <b><i> * Look into mm/map_avl.c for more detail description of the ideas.</i></b>
<a name="L256" href="source/net/ipv4/inetpeer.c#L256">256</a> <b><i> */</i></b>
<a name="L257" href="source/net/ipv4/inetpeer.c#L257">257</a> static void <a href="ident?i=peer_avl_rebalance">peer_avl_rebalance</a>(struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=stack">stack</a>[],
<a name="L258" href="source/net/ipv4/inetpeer.c#L258">258</a>                                struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> ***stackend,
<a name="L259" href="source/net/ipv4/inetpeer.c#L259">259</a>                                struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *<a href="ident?i=base">base</a>)
<a name="L260" href="source/net/ipv4/inetpeer.c#L260">260</a> {
<a name="L261" href="source/net/ipv4/inetpeer.c#L261">261</a>         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **nodep;
<a name="L262" href="source/net/ipv4/inetpeer.c#L262">262</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=node">node</a>, *<a href="ident?i=l">l</a>, *<a href="ident?i=r">r</a>;
<a name="L263" href="source/net/ipv4/inetpeer.c#L263">263</a>         int lh, rh;
<a name="L264" href="source/net/ipv4/inetpeer.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/inetpeer.c#L265">265</a>         while (stackend &gt; <a href="ident?i=stack">stack</a>) {
<a name="L266" href="source/net/ipv4/inetpeer.c#L266">266</a>                 nodep = *--stackend;
<a name="L267" href="source/net/ipv4/inetpeer.c#L267">267</a>                 <a href="ident?i=node">node</a> = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(*nodep, <a href="ident?i=base">base</a>);
<a name="L268" href="source/net/ipv4/inetpeer.c#L268">268</a>                 <a href="ident?i=l">l</a> = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=node">node</a>-&gt;avl_left, <a href="ident?i=base">base</a>);
<a name="L269" href="source/net/ipv4/inetpeer.c#L269">269</a>                 <a href="ident?i=r">r</a> = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=node">node</a>-&gt;avl_right, <a href="ident?i=base">base</a>);
<a name="L270" href="source/net/ipv4/inetpeer.c#L270">270</a>                 lh = <a href="ident?i=node_height">node_height</a>(<a href="ident?i=l">l</a>);
<a name="L271" href="source/net/ipv4/inetpeer.c#L271">271</a>                 rh = <a href="ident?i=node_height">node_height</a>(<a href="ident?i=r">r</a>);
<a name="L272" href="source/net/ipv4/inetpeer.c#L272">272</a>                 if (lh &gt; rh + 1) { <b><i>/* l: RH+2 */</i></b>
<a name="L273" href="source/net/ipv4/inetpeer.c#L273">273</a>                         struct <a href="ident?i=inet_peer">inet_peer</a> *ll, *<a href="ident?i=lr">lr</a>, *lrl, *lrr;
<a name="L274" href="source/net/ipv4/inetpeer.c#L274">274</a>                         int lrh;
<a name="L275" href="source/net/ipv4/inetpeer.c#L275">275</a>                         ll = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=l">l</a>-&gt;avl_left, <a href="ident?i=base">base</a>);
<a name="L276" href="source/net/ipv4/inetpeer.c#L276">276</a>                         <a href="ident?i=lr">lr</a> = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=l">l</a>-&gt;avl_right, <a href="ident?i=base">base</a>);
<a name="L277" href="source/net/ipv4/inetpeer.c#L277">277</a>                         lrh = <a href="ident?i=node_height">node_height</a>(<a href="ident?i=lr">lr</a>);
<a name="L278" href="source/net/ipv4/inetpeer.c#L278">278</a>                         if (lrh &lt;= <a href="ident?i=node_height">node_height</a>(ll)) {   <b><i>/* ll: RH+1 */</i></b>
<a name="L279" href="source/net/ipv4/inetpeer.c#L279">279</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_left, <a href="ident?i=lr">lr</a>);   <b><i>/* lr: RH or RH+1 */</i></b>
<a name="L280" href="source/net/ipv4/inetpeer.c#L280">280</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_right, <a href="ident?i=r">r</a>);   <b><i>/* r: RH */</i></b>
<a name="L281" href="source/net/ipv4/inetpeer.c#L281">281</a>                                 <a href="ident?i=node">node</a>-&gt;avl_height = lrh + 1; <b><i>/* RH+1 or RH+2 */</i></b>
<a name="L282" href="source/net/ipv4/inetpeer.c#L282">282</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=l">l</a>-&gt;avl_left, ll);       <b><i>/* ll: RH+1 */</i></b>
<a name="L283" href="source/net/ipv4/inetpeer.c#L283">283</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=l">l</a>-&gt;avl_right, <a href="ident?i=node">node</a>);   <b><i>/* node: RH+1 or RH+2 */</i></b>
<a name="L284" href="source/net/ipv4/inetpeer.c#L284">284</a>                                 <a href="ident?i=l">l</a>-&gt;avl_height = <a href="ident?i=node">node</a>-&gt;avl_height + 1;
<a name="L285" href="source/net/ipv4/inetpeer.c#L285">285</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(*nodep, <a href="ident?i=l">l</a>);
<a name="L286" href="source/net/ipv4/inetpeer.c#L286">286</a>                         } else { <b><i>/* ll: RH, lr: RH+1 */</i></b>
<a name="L287" href="source/net/ipv4/inetpeer.c#L287">287</a>                                 lrl = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=lr">lr</a>-&gt;avl_left, <a href="ident?i=base">base</a>);<b><i>/* lrl: RH or RH-1 */</i></b>
<a name="L288" href="source/net/ipv4/inetpeer.c#L288">288</a>                                 lrr = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=lr">lr</a>-&gt;avl_right, <a href="ident?i=base">base</a>);<b><i>/* lrr: RH or RH-1 */</i></b>
<a name="L289" href="source/net/ipv4/inetpeer.c#L289">289</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_left, lrr);  <b><i>/* lrr: RH or RH-1 */</i></b>
<a name="L290" href="source/net/ipv4/inetpeer.c#L290">290</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_right, <a href="ident?i=r">r</a>);   <b><i>/* r: RH */</i></b>
<a name="L291" href="source/net/ipv4/inetpeer.c#L291">291</a>                                 <a href="ident?i=node">node</a>-&gt;avl_height = rh + 1; <b><i>/* node: RH+1 */</i></b>
<a name="L292" href="source/net/ipv4/inetpeer.c#L292">292</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=l">l</a>-&gt;avl_left, ll);      <b><i>/* ll: RH */</i></b>
<a name="L293" href="source/net/ipv4/inetpeer.c#L293">293</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=l">l</a>-&gt;avl_right, lrl);    <b><i>/* lrl: RH or RH-1 */</i></b>
<a name="L294" href="source/net/ipv4/inetpeer.c#L294">294</a>                                 <a href="ident?i=l">l</a>-&gt;avl_height = rh + 1; <b><i>/* l: RH+1 */</i></b>
<a name="L295" href="source/net/ipv4/inetpeer.c#L295">295</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=lr">lr</a>-&gt;avl_left, <a href="ident?i=l">l</a>);      <b><i>/* l: RH+1 */</i></b>
<a name="L296" href="source/net/ipv4/inetpeer.c#L296">296</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=lr">lr</a>-&gt;avl_right, <a href="ident?i=node">node</a>);  <b><i>/* node: RH+1 */</i></b>
<a name="L297" href="source/net/ipv4/inetpeer.c#L297">297</a>                                 <a href="ident?i=lr">lr</a>-&gt;avl_height = rh + 2;
<a name="L298" href="source/net/ipv4/inetpeer.c#L298">298</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(*nodep, <a href="ident?i=lr">lr</a>);
<a name="L299" href="source/net/ipv4/inetpeer.c#L299">299</a>                         }
<a name="L300" href="source/net/ipv4/inetpeer.c#L300">300</a>                 } else if (rh &gt; lh + 1) { <b><i>/* r: LH+2 */</i></b>
<a name="L301" href="source/net/ipv4/inetpeer.c#L301">301</a>                         struct <a href="ident?i=inet_peer">inet_peer</a> *rr, *rl, *rlr, *rll;
<a name="L302" href="source/net/ipv4/inetpeer.c#L302">302</a>                         int rlh;
<a name="L303" href="source/net/ipv4/inetpeer.c#L303">303</a>                         rr = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=r">r</a>-&gt;avl_right, <a href="ident?i=base">base</a>);
<a name="L304" href="source/net/ipv4/inetpeer.c#L304">304</a>                         rl = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=r">r</a>-&gt;avl_left, <a href="ident?i=base">base</a>);
<a name="L305" href="source/net/ipv4/inetpeer.c#L305">305</a>                         rlh = <a href="ident?i=node_height">node_height</a>(rl);
<a name="L306" href="source/net/ipv4/inetpeer.c#L306">306</a>                         if (rlh &lt;= <a href="ident?i=node_height">node_height</a>(rr)) {   <b><i>/* rr: LH+1 */</i></b>
<a name="L307" href="source/net/ipv4/inetpeer.c#L307">307</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_right, rl);  <b><i>/* rl: LH or LH+1 */</i></b>
<a name="L308" href="source/net/ipv4/inetpeer.c#L308">308</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_left, <a href="ident?i=l">l</a>);    <b><i>/* l: LH */</i></b>
<a name="L309" href="source/net/ipv4/inetpeer.c#L309">309</a>                                 <a href="ident?i=node">node</a>-&gt;avl_height = rlh + 1; <b><i>/* LH+1 or LH+2 */</i></b>
<a name="L310" href="source/net/ipv4/inetpeer.c#L310">310</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=r">r</a>-&gt;avl_right, rr);     <b><i>/* rr: LH+1 */</i></b>
<a name="L311" href="source/net/ipv4/inetpeer.c#L311">311</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=r">r</a>-&gt;avl_left, <a href="ident?i=node">node</a>);    <b><i>/* node: LH+1 or LH+2 */</i></b>
<a name="L312" href="source/net/ipv4/inetpeer.c#L312">312</a>                                 <a href="ident?i=r">r</a>-&gt;avl_height = <a href="ident?i=node">node</a>-&gt;avl_height + 1;
<a name="L313" href="source/net/ipv4/inetpeer.c#L313">313</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(*nodep, <a href="ident?i=r">r</a>);
<a name="L314" href="source/net/ipv4/inetpeer.c#L314">314</a>                         } else { <b><i>/* rr: RH, rl: RH+1 */</i></b>
<a name="L315" href="source/net/ipv4/inetpeer.c#L315">315</a>                                 rlr = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(rl-&gt;avl_right, <a href="ident?i=base">base</a>);<b><i>/* rlr: LH or LH-1 */</i></b>
<a name="L316" href="source/net/ipv4/inetpeer.c#L316">316</a>                                 rll = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(rl-&gt;avl_left, <a href="ident?i=base">base</a>);<b><i>/* rll: LH or LH-1 */</i></b>
<a name="L317" href="source/net/ipv4/inetpeer.c#L317">317</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_right, rll); <b><i>/* rll: LH or LH-1 */</i></b>
<a name="L318" href="source/net/ipv4/inetpeer.c#L318">318</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=node">node</a>-&gt;avl_left, <a href="ident?i=l">l</a>);    <b><i>/* l: LH */</i></b>
<a name="L319" href="source/net/ipv4/inetpeer.c#L319">319</a>                                 <a href="ident?i=node">node</a>-&gt;avl_height = lh + 1; <b><i>/* node: LH+1 */</i></b>
<a name="L320" href="source/net/ipv4/inetpeer.c#L320">320</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=r">r</a>-&gt;avl_right, rr);     <b><i>/* rr: LH */</i></b>
<a name="L321" href="source/net/ipv4/inetpeer.c#L321">321</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=r">r</a>-&gt;avl_left, rlr);     <b><i>/* rlr: LH or LH-1 */</i></b>
<a name="L322" href="source/net/ipv4/inetpeer.c#L322">322</a>                                 <a href="ident?i=r">r</a>-&gt;avl_height = lh + 1; <b><i>/* r: LH+1 */</i></b>
<a name="L323" href="source/net/ipv4/inetpeer.c#L323">323</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(rl-&gt;avl_right, <a href="ident?i=r">r</a>);     <b><i>/* r: LH+1 */</i></b>
<a name="L324" href="source/net/ipv4/inetpeer.c#L324">324</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(rl-&gt;avl_left, <a href="ident?i=node">node</a>);   <b><i>/* node: LH+1 */</i></b>
<a name="L325" href="source/net/ipv4/inetpeer.c#L325">325</a>                                 rl-&gt;avl_height = lh + 2;
<a name="L326" href="source/net/ipv4/inetpeer.c#L326">326</a>                                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(*nodep, rl);
<a name="L327" href="source/net/ipv4/inetpeer.c#L327">327</a>                         }
<a name="L328" href="source/net/ipv4/inetpeer.c#L328">328</a>                 } else {
<a name="L329" href="source/net/ipv4/inetpeer.c#L329">329</a>                         <a href="ident?i=node">node</a>-&gt;avl_height = (lh &gt; rh ? lh : rh) + 1;
<a name="L330" href="source/net/ipv4/inetpeer.c#L330">330</a>                 }
<a name="L331" href="source/net/ipv4/inetpeer.c#L331">331</a>         }
<a name="L332" href="source/net/ipv4/inetpeer.c#L332">332</a> }
<a name="L333" href="source/net/ipv4/inetpeer.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/inetpeer.c#L334">334</a> <b><i>/* Called with local BH disabled and the pool lock held. */</i></b>
<a name="L335" href="source/net/ipv4/inetpeer.c#L335">335</a> #define <a href="ident?i=link_to_pool">link_to_pool</a>(<a href="ident?i=n">n</a>, <a href="ident?i=base">base</a>)                                   \
<a name="L336" href="source/net/ipv4/inetpeer.c#L336">336</a> do {                                                            \
<a name="L337" href="source/net/ipv4/inetpeer.c#L337">337</a>         <a href="ident?i=n">n</a>-&gt;avl_height = 1;                                      \
<a name="L338" href="source/net/ipv4/inetpeer.c#L338">338</a>         <a href="ident?i=n">n</a>-&gt;avl_left = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;                       \
<a name="L339" href="source/net/ipv4/inetpeer.c#L339">339</a>         <a href="ident?i=n">n</a>-&gt;avl_right = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;                      \
<a name="L340" href="source/net/ipv4/inetpeer.c#L340">340</a>         <b><i>/* lockless readers can catch us now */</i></b>                 \
<a name="L341" href="source/net/ipv4/inetpeer.c#L341">341</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(**--stackptr, <a href="ident?i=n">n</a>);                    \
<a name="L342" href="source/net/ipv4/inetpeer.c#L342">342</a>         <a href="ident?i=peer_avl_rebalance">peer_avl_rebalance</a>(<a href="ident?i=stack">stack</a>, stackptr, <a href="ident?i=base">base</a>);              \
<a name="L343" href="source/net/ipv4/inetpeer.c#L343">343</a> } while (0)
<a name="L344" href="source/net/ipv4/inetpeer.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/inetpeer.c#L345">345</a> static void <a href="ident?i=inetpeer_free_rcu">inetpeer_free_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L346" href="source/net/ipv4/inetpeer.c#L346">346</a> {
<a name="L347" href="source/net/ipv4/inetpeer.c#L347">347</a>         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(peer_cachep, <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=inet_peer">inet_peer</a>, rcu));
<a name="L348" href="source/net/ipv4/inetpeer.c#L348">348</a> }
<a name="L349" href="source/net/ipv4/inetpeer.c#L349">349</a> 
<a name="L350" href="source/net/ipv4/inetpeer.c#L350">350</a> static void <a href="ident?i=unlink_from_pool">unlink_from_pool</a>(struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=p">p</a>, struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *<a href="ident?i=base">base</a>,
<a name="L351" href="source/net/ipv4/inetpeer.c#L351">351</a>                              struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=stack">stack</a>[<a href="ident?i=PEER_MAXDEPTH">PEER_MAXDEPTH</a>])
<a name="L352" href="source/net/ipv4/inetpeer.c#L352">352</a> {
<a name="L353" href="source/net/ipv4/inetpeer.c#L353">353</a>         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> ***stackptr, ***delp;
<a name="L354" href="source/net/ipv4/inetpeer.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/inetpeer.c#L355">355</a>         if (<a href="ident?i=lookup">lookup</a>(&amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=stack">stack</a>, <a href="ident?i=base">base</a>) != <a href="ident?i=p">p</a>)
<a name="L356" href="source/net/ipv4/inetpeer.c#L356">356</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L357" href="source/net/ipv4/inetpeer.c#L357">357</a>         delp = stackptr - 1; <b><i>/* *delp[0] == p */</i></b>
<a name="L358" href="source/net/ipv4/inetpeer.c#L358">358</a>         if (<a href="ident?i=p">p</a>-&gt;avl_left == <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>) {
<a name="L359" href="source/net/ipv4/inetpeer.c#L359">359</a>                 *delp[0] = <a href="ident?i=p">p</a>-&gt;avl_right;
<a name="L360" href="source/net/ipv4/inetpeer.c#L360">360</a>                 --stackptr;
<a name="L361" href="source/net/ipv4/inetpeer.c#L361">361</a>         } else {
<a name="L362" href="source/net/ipv4/inetpeer.c#L362">362</a>                 <b><i>/* look for a node to insert instead of p */</i></b>
<a name="L363" href="source/net/ipv4/inetpeer.c#L363">363</a>                 struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=t">t</a>;
<a name="L364" href="source/net/ipv4/inetpeer.c#L364">364</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=lookup_rightempty">lookup_rightempty</a>(<a href="ident?i=p">p</a>, <a href="ident?i=base">base</a>);
<a name="L365" href="source/net/ipv4/inetpeer.c#L365">365</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(*stackptr[-1], <a href="ident?i=base">base</a>) != <a href="ident?i=t">t</a>);
<a name="L366" href="source/net/ipv4/inetpeer.c#L366">366</a>                 **--stackptr = <a href="ident?i=t">t</a>-&gt;avl_left;
<a name="L367" href="source/net/ipv4/inetpeer.c#L367">367</a>                 <b><i>/* t is removed, t-&gt;daddr &gt; x-&gt;daddr for any</i></b>
<a name="L368" href="source/net/ipv4/inetpeer.c#L368">368</a> <b><i>                 * x in p-&gt;avl_left subtree.</i></b>
<a name="L369" href="source/net/ipv4/inetpeer.c#L369">369</a> <b><i>                 * Put t in the old place of p. */</i></b>
<a name="L370" href="source/net/ipv4/inetpeer.c#L370">370</a>                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(*delp[0], <a href="ident?i=t">t</a>);
<a name="L371" href="source/net/ipv4/inetpeer.c#L371">371</a>                 <a href="ident?i=t">t</a>-&gt;avl_left = <a href="ident?i=p">p</a>-&gt;avl_left;
<a name="L372" href="source/net/ipv4/inetpeer.c#L372">372</a>                 <a href="ident?i=t">t</a>-&gt;avl_right = <a href="ident?i=p">p</a>-&gt;avl_right;
<a name="L373" href="source/net/ipv4/inetpeer.c#L373">373</a>                 <a href="ident?i=t">t</a>-&gt;avl_height = <a href="ident?i=p">p</a>-&gt;avl_height;
<a name="L374" href="source/net/ipv4/inetpeer.c#L374">374</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(delp[1] != &amp;<a href="ident?i=p">p</a>-&gt;avl_left);
<a name="L375" href="source/net/ipv4/inetpeer.c#L375">375</a>                 delp[1] = &amp;<a href="ident?i=t">t</a>-&gt;avl_left; <b><i>/* was &amp;p-&gt;avl_left */</i></b>
<a name="L376" href="source/net/ipv4/inetpeer.c#L376">376</a>         }
<a name="L377" href="source/net/ipv4/inetpeer.c#L377">377</a>         <a href="ident?i=peer_avl_rebalance">peer_avl_rebalance</a>(<a href="ident?i=stack">stack</a>, stackptr, <a href="ident?i=base">base</a>);
<a name="L378" href="source/net/ipv4/inetpeer.c#L378">378</a>         <a href="ident?i=base">base</a>-&gt;total--;
<a name="L379" href="source/net/ipv4/inetpeer.c#L379">379</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=p">p</a>-&gt;rcu, <a href="ident?i=inetpeer_free_rcu">inetpeer_free_rcu</a>);
<a name="L380" href="source/net/ipv4/inetpeer.c#L380">380</a> }
<a name="L381" href="source/net/ipv4/inetpeer.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/inetpeer.c#L382">382</a> <b><i>/* perform garbage collect on all items stacked during a lookup */</i></b>
<a name="L383" href="source/net/ipv4/inetpeer.c#L383">383</a> static int <a href="ident?i=inet_peer_gc">inet_peer_gc</a>(struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *<a href="ident?i=base">base</a>,
<a name="L384" href="source/net/ipv4/inetpeer.c#L384">384</a>                         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=stack">stack</a>[<a href="ident?i=PEER_MAXDEPTH">PEER_MAXDEPTH</a>],
<a name="L385" href="source/net/ipv4/inetpeer.c#L385">385</a>                         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> ***stackptr)
<a name="L386" href="source/net/ipv4/inetpeer.c#L386">386</a> {
<a name="L387" href="source/net/ipv4/inetpeer.c#L387">387</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=p">p</a>, *gchead = <a href="ident?i=NULL">NULL</a>;
<a name="L388" href="source/net/ipv4/inetpeer.c#L388">388</a>         <a href="ident?i=__u32">__u32</a> <a href="ident?i=delta">delta</a>, <a href="ident?i=ttl">ttl</a>;
<a name="L389" href="source/net/ipv4/inetpeer.c#L389">389</a>         int cnt = 0;
<a name="L390" href="source/net/ipv4/inetpeer.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/inetpeer.c#L391">391</a>         if (<a href="ident?i=base">base</a>-&gt;total &gt;= <a href="ident?i=inet_peer_threshold">inet_peer_threshold</a>)
<a name="L392" href="source/net/ipv4/inetpeer.c#L392">392</a>                 <a href="ident?i=ttl">ttl</a> = 0; <b><i>/* be aggressive */</i></b>
<a name="L393" href="source/net/ipv4/inetpeer.c#L393">393</a>         else
<a name="L394" href="source/net/ipv4/inetpeer.c#L394">394</a>                 <a href="ident?i=ttl">ttl</a> = <a href="ident?i=inet_peer_maxttl">inet_peer_maxttl</a>
<a name="L395" href="source/net/ipv4/inetpeer.c#L395">395</a>                                 - (<a href="ident?i=inet_peer_maxttl">inet_peer_maxttl</a> - <a href="ident?i=inet_peer_minttl">inet_peer_minttl</a>) / <a href="ident?i=HZ">HZ</a> *
<a name="L396" href="source/net/ipv4/inetpeer.c#L396">396</a>                                         <a href="ident?i=base">base</a>-&gt;total / <a href="ident?i=inet_peer_threshold">inet_peer_threshold</a> * <a href="ident?i=HZ">HZ</a>;
<a name="L397" href="source/net/ipv4/inetpeer.c#L397">397</a>         stackptr--; <b><i>/* last stack slot is peer_avl_empty */</i></b>
<a name="L398" href="source/net/ipv4/inetpeer.c#L398">398</a>         while (stackptr &gt; <a href="ident?i=stack">stack</a>) {
<a name="L399" href="source/net/ipv4/inetpeer.c#L399">399</a>                 stackptr--;
<a name="L400" href="source/net/ipv4/inetpeer.c#L400">400</a>                 <a href="ident?i=p">p</a> = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(**stackptr, <a href="ident?i=base">base</a>);
<a name="L401" href="source/net/ipv4/inetpeer.c#L401">401</a>                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=p">p</a>-&gt;refcnt) == 0) {
<a name="L402" href="source/net/ipv4/inetpeer.c#L402">402</a>                         <a href="ident?i=smp_rmb">smp_rmb</a>();
<a name="L403" href="source/net/ipv4/inetpeer.c#L403">403</a>                         <a href="ident?i=delta">delta</a> = (<a href="ident?i=__u32">__u32</a>)<a href="ident?i=jiffies">jiffies</a> - <a href="ident?i=p">p</a>-&gt;dtime;
<a name="L404" href="source/net/ipv4/inetpeer.c#L404">404</a>                         if (<a href="ident?i=delta">delta</a> &gt;= <a href="ident?i=ttl">ttl</a> &amp;&amp;
<a name="L405" href="source/net/ipv4/inetpeer.c#L405">405</a>                             <a href="ident?i=atomic_cmpxchg">atomic_cmpxchg</a>(&amp;<a href="ident?i=p">p</a>-&gt;refcnt, 0, -1) == 0) {
<a name="L406" href="source/net/ipv4/inetpeer.c#L406">406</a>                                 <a href="ident?i=p">p</a>-&gt;gc_next = gchead;
<a name="L407" href="source/net/ipv4/inetpeer.c#L407">407</a>                                 gchead = <a href="ident?i=p">p</a>;
<a name="L408" href="source/net/ipv4/inetpeer.c#L408">408</a>                         }
<a name="L409" href="source/net/ipv4/inetpeer.c#L409">409</a>                 }
<a name="L410" href="source/net/ipv4/inetpeer.c#L410">410</a>         }
<a name="L411" href="source/net/ipv4/inetpeer.c#L411">411</a>         while ((<a href="ident?i=p">p</a> = gchead) != <a href="ident?i=NULL">NULL</a>) {
<a name="L412" href="source/net/ipv4/inetpeer.c#L412">412</a>                 gchead = <a href="ident?i=p">p</a>-&gt;gc_next;
<a name="L413" href="source/net/ipv4/inetpeer.c#L413">413</a>                 cnt++;
<a name="L414" href="source/net/ipv4/inetpeer.c#L414">414</a>                 <a href="ident?i=unlink_from_pool">unlink_from_pool</a>(<a href="ident?i=p">p</a>, <a href="ident?i=base">base</a>, <a href="ident?i=stack">stack</a>);
<a name="L415" href="source/net/ipv4/inetpeer.c#L415">415</a>         }
<a name="L416" href="source/net/ipv4/inetpeer.c#L416">416</a>         return cnt;
<a name="L417" href="source/net/ipv4/inetpeer.c#L417">417</a> }
<a name="L418" href="source/net/ipv4/inetpeer.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/inetpeer.c#L419">419</a> struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=inet_getpeer">inet_getpeer</a>(struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *<a href="ident?i=base">base</a>,
<a name="L420" href="source/net/ipv4/inetpeer.c#L420">420</a>                                const struct <a href="ident?i=inetpeer_addr">inetpeer_addr</a> *<a href="ident?i=daddr">daddr</a>,
<a name="L421" href="source/net/ipv4/inetpeer.c#L421">421</a>                                int <a href="ident?i=create">create</a>)
<a name="L422" href="source/net/ipv4/inetpeer.c#L422">422</a> {
<a name="L423" href="source/net/ipv4/inetpeer.c#L423">423</a>         struct <a href="ident?i=inet_peer">inet_peer</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=stack">stack</a>[<a href="ident?i=PEER_MAXDEPTH">PEER_MAXDEPTH</a>], ***stackptr;
<a name="L424" href="source/net/ipv4/inetpeer.c#L424">424</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=p">p</a>;
<a name="L425" href="source/net/ipv4/inetpeer.c#L425">425</a>         unsigned int <a href="ident?i=sequence">sequence</a>;
<a name="L426" href="source/net/ipv4/inetpeer.c#L426">426</a>         int invalidated, gccnt = 0;
<a name="L427" href="source/net/ipv4/inetpeer.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/inetpeer.c#L428">428</a>         <b><i>/* Attempt a lockless lookup first.</i></b>
<a name="L429" href="source/net/ipv4/inetpeer.c#L429">429</a> <b><i>         * Because of a concurrent writer, we might not find an existing entry.</i></b>
<a name="L430" href="source/net/ipv4/inetpeer.c#L430">430</a> <b><i>         */</i></b>
<a name="L431" href="source/net/ipv4/inetpeer.c#L431">431</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L432" href="source/net/ipv4/inetpeer.c#L432">432</a>         <a href="ident?i=sequence">sequence</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L433" href="source/net/ipv4/inetpeer.c#L433">433</a>         <a href="ident?i=p">p</a> = <a href="ident?i=lookup_rcu">lookup_rcu</a>(<a href="ident?i=daddr">daddr</a>, <a href="ident?i=base">base</a>);
<a name="L434" href="source/net/ipv4/inetpeer.c#L434">434</a>         invalidated = <a href="ident?i=read_seqretry">read_seqretry</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>, <a href="ident?i=sequence">sequence</a>);
<a name="L435" href="source/net/ipv4/inetpeer.c#L435">435</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L436" href="source/net/ipv4/inetpeer.c#L436">436</a> 
<a name="L437" href="source/net/ipv4/inetpeer.c#L437">437</a>         if (<a href="ident?i=p">p</a>)
<a name="L438" href="source/net/ipv4/inetpeer.c#L438">438</a>                 return <a href="ident?i=p">p</a>;
<a name="L439" href="source/net/ipv4/inetpeer.c#L439">439</a> 
<a name="L440" href="source/net/ipv4/inetpeer.c#L440">440</a>         <b><i>/* If no writer did a change during our lookup, we can return early. */</i></b>
<a name="L441" href="source/net/ipv4/inetpeer.c#L441">441</a>         if (!<a href="ident?i=create">create</a> &amp;&amp; !invalidated)
<a name="L442" href="source/net/ipv4/inetpeer.c#L442">442</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L443" href="source/net/ipv4/inetpeer.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/inetpeer.c#L444">444</a>         <b><i>/* retry an exact lookup, taking the lock before.</i></b>
<a name="L445" href="source/net/ipv4/inetpeer.c#L445">445</a> <b><i>         * At least, nodes should be hot in our cache.</i></b>
<a name="L446" href="source/net/ipv4/inetpeer.c#L446">446</a> <b><i>         */</i></b>
<a name="L447" href="source/net/ipv4/inetpeer.c#L447">447</a>         <a href="ident?i=write_seqlock_bh">write_seqlock_bh</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L448" href="source/net/ipv4/inetpeer.c#L448">448</a> relookup:
<a name="L449" href="source/net/ipv4/inetpeer.c#L449">449</a>         <a href="ident?i=p">p</a> = <a href="ident?i=lookup">lookup</a>(<a href="ident?i=daddr">daddr</a>, <a href="ident?i=stack">stack</a>, <a href="ident?i=base">base</a>);
<a name="L450" href="source/net/ipv4/inetpeer.c#L450">450</a>         if (<a href="ident?i=p">p</a> != <a href="ident?i=peer_avl_empty">peer_avl_empty</a>) {
<a name="L451" href="source/net/ipv4/inetpeer.c#L451">451</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=p">p</a>-&gt;refcnt);
<a name="L452" href="source/net/ipv4/inetpeer.c#L452">452</a>                 <a href="ident?i=write_sequnlock_bh">write_sequnlock_bh</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L453" href="source/net/ipv4/inetpeer.c#L453">453</a>                 return <a href="ident?i=p">p</a>;
<a name="L454" href="source/net/ipv4/inetpeer.c#L454">454</a>         }
<a name="L455" href="source/net/ipv4/inetpeer.c#L455">455</a>         if (!gccnt) {
<a name="L456" href="source/net/ipv4/inetpeer.c#L456">456</a>                 gccnt = <a href="ident?i=inet_peer_gc">inet_peer_gc</a>(<a href="ident?i=base">base</a>, <a href="ident?i=stack">stack</a>, stackptr);
<a name="L457" href="source/net/ipv4/inetpeer.c#L457">457</a>                 if (gccnt &amp;&amp; <a href="ident?i=create">create</a>)
<a name="L458" href="source/net/ipv4/inetpeer.c#L458">458</a>                         goto relookup;
<a name="L459" href="source/net/ipv4/inetpeer.c#L459">459</a>         }
<a name="L460" href="source/net/ipv4/inetpeer.c#L460">460</a>         <a href="ident?i=p">p</a> = <a href="ident?i=create">create</a> ? <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(peer_cachep, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>) : <a href="ident?i=NULL">NULL</a>;
<a name="L461" href="source/net/ipv4/inetpeer.c#L461">461</a>         if (<a href="ident?i=p">p</a>) {
<a name="L462" href="source/net/ipv4/inetpeer.c#L462">462</a>                 <a href="ident?i=p">p</a>-&gt;<a href="ident?i=daddr">daddr</a> = *<a href="ident?i=daddr">daddr</a>;
<a name="L463" href="source/net/ipv4/inetpeer.c#L463">463</a>                 <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=p">p</a>-&gt;refcnt, 1);
<a name="L464" href="source/net/ipv4/inetpeer.c#L464">464</a>                 <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=p">p</a>-&gt;rid, 0);
<a name="L465" href="source/net/ipv4/inetpeer.c#L465">465</a>                 <a href="ident?i=p">p</a>-&gt;metrics[<a href="ident?i=RTAX_LOCK">RTAX_LOCK</a>-1] = <a href="ident?i=INETPEER_METRICS_NEW">INETPEER_METRICS_NEW</a>;
<a name="L466" href="source/net/ipv4/inetpeer.c#L466">466</a>                 <a href="ident?i=p">p</a>-&gt;rate_tokens = 0;
<a name="L467" href="source/net/ipv4/inetpeer.c#L467">467</a>                 <b><i>/* 60*HZ is arbitrary, but chosen enough high so that the first</i></b>
<a name="L468" href="source/net/ipv4/inetpeer.c#L468">468</a> <b><i>                 * calculation of tokens is at its maximum.</i></b>
<a name="L469" href="source/net/ipv4/inetpeer.c#L469">469</a> <b><i>                 */</i></b>
<a name="L470" href="source/net/ipv4/inetpeer.c#L470">470</a>                 <a href="ident?i=p">p</a>-&gt;rate_last = <a href="ident?i=jiffies">jiffies</a> - 60*<a href="ident?i=HZ">HZ</a>;
<a name="L471" href="source/net/ipv4/inetpeer.c#L471">471</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;<a href="ident?i=p">p</a>-&gt;gc_list);
<a name="L472" href="source/net/ipv4/inetpeer.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/inetpeer.c#L473">473</a>                 <b><i>/* Link the node. */</i></b>
<a name="L474" href="source/net/ipv4/inetpeer.c#L474">474</a>                 <a href="ident?i=link_to_pool">link_to_pool</a>(<a href="ident?i=p">p</a>, <a href="ident?i=base">base</a>);
<a name="L475" href="source/net/ipv4/inetpeer.c#L475">475</a>                 <a href="ident?i=base">base</a>-&gt;total++;
<a name="L476" href="source/net/ipv4/inetpeer.c#L476">476</a>         }
<a name="L477" href="source/net/ipv4/inetpeer.c#L477">477</a>         <a href="ident?i=write_sequnlock_bh">write_sequnlock_bh</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L478" href="source/net/ipv4/inetpeer.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/inetpeer.c#L479">479</a>         return <a href="ident?i=p">p</a>;
<a name="L480" href="source/net/ipv4/inetpeer.c#L480">480</a> }
<a name="L481" href="source/net/ipv4/inetpeer.c#L481">481</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_getpeer">inet_getpeer</a>);
<a name="L482" href="source/net/ipv4/inetpeer.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/inetpeer.c#L483">483</a> void <a href="ident?i=inet_putpeer">inet_putpeer</a>(struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=p">p</a>)
<a name="L484" href="source/net/ipv4/inetpeer.c#L484">484</a> {
<a name="L485" href="source/net/ipv4/inetpeer.c#L485">485</a>         <a href="ident?i=p">p</a>-&gt;dtime = (<a href="ident?i=__u32">__u32</a>)<a href="ident?i=jiffies">jiffies</a>;
<a name="L486" href="source/net/ipv4/inetpeer.c#L486">486</a>         <a href="ident?i=smp_mb__before_atomic">smp_mb__before_atomic</a>();
<a name="L487" href="source/net/ipv4/inetpeer.c#L487">487</a>         <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;<a href="ident?i=p">p</a>-&gt;refcnt);
<a name="L488" href="source/net/ipv4/inetpeer.c#L488">488</a> }
<a name="L489" href="source/net/ipv4/inetpeer.c#L489">489</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_putpeer">inet_putpeer</a>);
<a name="L490" href="source/net/ipv4/inetpeer.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/inetpeer.c#L491">491</a> <b><i>/*</i></b>
<a name="L492" href="source/net/ipv4/inetpeer.c#L492">492</a> <b><i> *      Check transmit rate limitation for given message.</i></b>
<a name="L493" href="source/net/ipv4/inetpeer.c#L493">493</a> <b><i> *      The rate information is held in the inet_peer entries now.</i></b>
<a name="L494" href="source/net/ipv4/inetpeer.c#L494">494</a> <b><i> *      This function is generic and could be used for other purposes</i></b>
<a name="L495" href="source/net/ipv4/inetpeer.c#L495">495</a> <b><i> *      too. It uses a Token bucket filter as suggested by Alexey Kuznetsov.</i></b>
<a name="L496" href="source/net/ipv4/inetpeer.c#L496">496</a> <b><i> *</i></b>
<a name="L497" href="source/net/ipv4/inetpeer.c#L497">497</a> <b><i> *      Note that the same inet_peer fields are modified by functions in</i></b>
<a name="L498" href="source/net/ipv4/inetpeer.c#L498">498</a> <b><i> *      route.c too, but these work for packet destinations while xrlim_allow</i></b>
<a name="L499" href="source/net/ipv4/inetpeer.c#L499">499</a> <b><i> *      works for icmp destinations. This means the rate limiting information</i></b>
<a name="L500" href="source/net/ipv4/inetpeer.c#L500">500</a> <b><i> *      for one "ip object" is shared - and these ICMPs are twice limited:</i></b>
<a name="L501" href="source/net/ipv4/inetpeer.c#L501">501</a> <b><i> *      by source and by destination.</i></b>
<a name="L502" href="source/net/ipv4/inetpeer.c#L502">502</a> <b><i> *</i></b>
<a name="L503" href="source/net/ipv4/inetpeer.c#L503">503</a> <b><i> *      RFC 1812: 4.3.2.8 SHOULD be able to limit error message rate</i></b>
<a name="L504" href="source/net/ipv4/inetpeer.c#L504">504</a> <b><i> *                        SHOULD allow setting of rate limits</i></b>
<a name="L505" href="source/net/ipv4/inetpeer.c#L505">505</a> <b><i> *</i></b>
<a name="L506" href="source/net/ipv4/inetpeer.c#L506">506</a> <b><i> *      Shared between ICMPv4 and ICMPv6.</i></b>
<a name="L507" href="source/net/ipv4/inetpeer.c#L507">507</a> <b><i> */</i></b>
<a name="L508" href="source/net/ipv4/inetpeer.c#L508">508</a> #define <a href="ident?i=XRLIM_BURST_FACTOR">XRLIM_BURST_FACTOR</a> 6
<a name="L509" href="source/net/ipv4/inetpeer.c#L509">509</a> <a href="ident?i=bool">bool</a> <a href="ident?i=inet_peer_xrlim_allow">inet_peer_xrlim_allow</a>(struct <a href="ident?i=inet_peer">inet_peer</a> *peer, int <a href="ident?i=timeout">timeout</a>)
<a name="L510" href="source/net/ipv4/inetpeer.c#L510">510</a> {
<a name="L511" href="source/net/ipv4/inetpeer.c#L511">511</a>         unsigned long <a href="ident?i=now">now</a>, <a href="ident?i=token">token</a>;
<a name="L512" href="source/net/ipv4/inetpeer.c#L512">512</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=rc">rc</a> = <a href="ident?i=false">false</a>;
<a name="L513" href="source/net/ipv4/inetpeer.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/inetpeer.c#L514">514</a>         if (!peer)
<a name="L515" href="source/net/ipv4/inetpeer.c#L515">515</a>                 return <a href="ident?i=true">true</a>;
<a name="L516" href="source/net/ipv4/inetpeer.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/inetpeer.c#L517">517</a>         <a href="ident?i=token">token</a> = peer-&gt;rate_tokens;
<a name="L518" href="source/net/ipv4/inetpeer.c#L518">518</a>         <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L519" href="source/net/ipv4/inetpeer.c#L519">519</a>         <a href="ident?i=token">token</a> += <a href="ident?i=now">now</a> - peer-&gt;rate_last;
<a name="L520" href="source/net/ipv4/inetpeer.c#L520">520</a>         peer-&gt;rate_last = <a href="ident?i=now">now</a>;
<a name="L521" href="source/net/ipv4/inetpeer.c#L521">521</a>         if (<a href="ident?i=token">token</a> &gt; <a href="ident?i=XRLIM_BURST_FACTOR">XRLIM_BURST_FACTOR</a> * <a href="ident?i=timeout">timeout</a>)
<a name="L522" href="source/net/ipv4/inetpeer.c#L522">522</a>                 <a href="ident?i=token">token</a> = <a href="ident?i=XRLIM_BURST_FACTOR">XRLIM_BURST_FACTOR</a> * <a href="ident?i=timeout">timeout</a>;
<a name="L523" href="source/net/ipv4/inetpeer.c#L523">523</a>         if (<a href="ident?i=token">token</a> &gt;= <a href="ident?i=timeout">timeout</a>) {
<a name="L524" href="source/net/ipv4/inetpeer.c#L524">524</a>                 <a href="ident?i=token">token</a> -= <a href="ident?i=timeout">timeout</a>;
<a name="L525" href="source/net/ipv4/inetpeer.c#L525">525</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=true">true</a>;
<a name="L526" href="source/net/ipv4/inetpeer.c#L526">526</a>         }
<a name="L527" href="source/net/ipv4/inetpeer.c#L527">527</a>         peer-&gt;rate_tokens = <a href="ident?i=token">token</a>;
<a name="L528" href="source/net/ipv4/inetpeer.c#L528">528</a>         return <a href="ident?i=rc">rc</a>;
<a name="L529" href="source/net/ipv4/inetpeer.c#L529">529</a> }
<a name="L530" href="source/net/ipv4/inetpeer.c#L530">530</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_peer_xrlim_allow">inet_peer_xrlim_allow</a>);
<a name="L531" href="source/net/ipv4/inetpeer.c#L531">531</a> 
<a name="L532" href="source/net/ipv4/inetpeer.c#L532">532</a> static void <a href="ident?i=inetpeer_inval_rcu">inetpeer_inval_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L533" href="source/net/ipv4/inetpeer.c#L533">533</a> {
<a name="L534" href="source/net/ipv4/inetpeer.c#L534">534</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=p">p</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=inet_peer">inet_peer</a>, gc_rcu);
<a name="L535" href="source/net/ipv4/inetpeer.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/inetpeer.c#L536">536</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;gc_lock);
<a name="L537" href="source/net/ipv4/inetpeer.c#L537">537</a>         <a href="ident?i=list_add_tail">list_add_tail</a>(&amp;<a href="ident?i=p">p</a>-&gt;gc_list, &amp;gc_list);
<a name="L538" href="source/net/ipv4/inetpeer.c#L538">538</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;gc_lock);
<a name="L539" href="source/net/ipv4/inetpeer.c#L539">539</a> 
<a name="L540" href="source/net/ipv4/inetpeer.c#L540">540</a>         <a href="ident?i=schedule_delayed_work">schedule_delayed_work</a>(&amp;<a href="ident?i=gc_work">gc_work</a>, <a href="ident?i=gc_delay">gc_delay</a>);
<a name="L541" href="source/net/ipv4/inetpeer.c#L541">541</a> }
<a name="L542" href="source/net/ipv4/inetpeer.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/inetpeer.c#L543">543</a> void <a href="ident?i=inetpeer_invalidate_tree">inetpeer_invalidate_tree</a>(struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *<a href="ident?i=base">base</a>)
<a name="L544" href="source/net/ipv4/inetpeer.c#L544">544</a> {
<a name="L545" href="source/net/ipv4/inetpeer.c#L545">545</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *<a href="ident?i=root">root</a>;
<a name="L546" href="source/net/ipv4/inetpeer.c#L546">546</a> 
<a name="L547" href="source/net/ipv4/inetpeer.c#L547">547</a>         <a href="ident?i=write_seqlock_bh">write_seqlock_bh</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L548" href="source/net/ipv4/inetpeer.c#L548">548</a> 
<a name="L549" href="source/net/ipv4/inetpeer.c#L549">549</a>         <a href="ident?i=root">root</a> = <a href="ident?i=rcu_deref_locked">rcu_deref_locked</a>(<a href="ident?i=base">base</a>-&gt;<a href="ident?i=root">root</a>, <a href="ident?i=base">base</a>);
<a name="L550" href="source/net/ipv4/inetpeer.c#L550">550</a>         if (<a href="ident?i=root">root</a> != <a href="ident?i=peer_avl_empty">peer_avl_empty</a>) {
<a name="L551" href="source/net/ipv4/inetpeer.c#L551">551</a>                 <a href="ident?i=base">base</a>-&gt;<a href="ident?i=root">root</a> = <a href="ident?i=peer_avl_empty_rcu">peer_avl_empty_rcu</a>;
<a name="L552" href="source/net/ipv4/inetpeer.c#L552">552</a>                 <a href="ident?i=base">base</a>-&gt;total = 0;
<a name="L553" href="source/net/ipv4/inetpeer.c#L553">553</a>                 <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=root">root</a>-&gt;gc_rcu, <a href="ident?i=inetpeer_inval_rcu">inetpeer_inval_rcu</a>);
<a name="L554" href="source/net/ipv4/inetpeer.c#L554">554</a>         }
<a name="L555" href="source/net/ipv4/inetpeer.c#L555">555</a> 
<a name="L556" href="source/net/ipv4/inetpeer.c#L556">556</a>         <a href="ident?i=write_sequnlock_bh">write_sequnlock_bh</a>(&amp;<a href="ident?i=base">base</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L557" href="source/net/ipv4/inetpeer.c#L557">557</a> }
<a name="L558" href="source/net/ipv4/inetpeer.c#L558">558</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inetpeer_invalidate_tree">inetpeer_invalidate_tree</a>);
<a name="L559" href="source/net/ipv4/inetpeer.c#L559">559</a> </pre></div><p>
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
