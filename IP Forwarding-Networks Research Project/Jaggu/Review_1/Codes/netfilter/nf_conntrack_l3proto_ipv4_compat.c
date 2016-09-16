<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c">nf_conntrack_l3proto_ipv4_compat.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L1">1</a> <b><i>/* ip_conntrack proc compat - based on ip_conntrack_standalone.c</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L3">3</a> <b><i> * (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L4">4</a> <b><i> * (C) 2002-2006 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L5">5</a> <b><i> * (C) 2006-2010 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L7">7</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L8">8</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L9">9</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L11">11</a> #include &lt;linux/types.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L12">12</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L13">13</a> #include &lt;linux/seq_file.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L14">14</a> #include &lt;linux/percpu.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L15">15</a> #include &lt;linux/security.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L16">16</a> #include &lt;net/net_namespace.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L17">17</a> 
 <a name="L18" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L18">18</a> #include &lt;linux/netfilter.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L19">19</a> #include &lt;net/netfilter/nf_conntrack_core.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L20">20</a> #include &lt;net/netfilter/nf_conntrack_l3proto.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L21">21</a> #include &lt;net/netfilter/nf_conntrack_l4proto.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L22">22</a> #include &lt;net/netfilter/nf_conntrack_expect.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L23">23</a> #include &lt;net/netfilter/nf_conntrack_acct.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L24">24</a> #include &lt;linux/rculist_nulls.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L25">25</a> #include &lt;linux/export.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L27">27</a> struct <a href="ident?i=ct_iter_state">ct_iter_state</a> {
 <a name="L28" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L28">28</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
 <a name="L29" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L29">29</a>         unsigned int <a href="ident?i=bucket">bucket</a>;
 <a name="L30" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L30">30</a> };
 <a name="L31" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L32">32</a> static struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=ct_get_first">ct_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
 <a name="L33" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L33">33</a> {
 <a name="L34" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L34">34</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
 <a name="L35" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L35">35</a>         struct <a href="ident?i=ct_iter_state">ct_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
 <a name="L36" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L36">36</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=n">n</a>;
 <a name="L37" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L38">38</a>         for (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
 <a name="L39" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L39">39</a>              <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt; <a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=htable_size">htable_size</a>;
 <a name="L40" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L40">40</a>              <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>++) {
 <a name="L41" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L41">41</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(
 <a name="L42" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L42">42</a>                         <a href="ident?i=hlist_nulls_first_rcu">hlist_nulls_first_rcu</a>(&amp;<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=hash">hash</a>[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>]));
 <a name="L43" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L43">43</a>                 if (!<a href="ident?i=is_a_nulls">is_a_nulls</a>(<a href="ident?i=n">n</a>))
 <a name="L44" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L44">44</a>                         return <a href="ident?i=n">n</a>;
 <a name="L45" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L45">45</a>         }
 <a name="L46" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L46">46</a>         return <a href="ident?i=NULL">NULL</a>;
 <a name="L47" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L47">47</a> }
 <a name="L48" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L49">49</a> static struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=ct_get_next">ct_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>,
 <a name="L50" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L50">50</a>                                       struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=head">head</a>)
 <a name="L51" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L51">51</a> {
 <a name="L52" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L52">52</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
 <a name="L53" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L53">53</a>         struct <a href="ident?i=ct_iter_state">ct_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
 <a name="L54" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L55">55</a>         <a href="ident?i=head">head</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=hlist_nulls_next_rcu">hlist_nulls_next_rcu</a>(<a href="ident?i=head">head</a>));
 <a name="L56" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L56">56</a>         while (<a href="ident?i=is_a_nulls">is_a_nulls</a>(<a href="ident?i=head">head</a>)) {
 <a name="L57" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L57">57</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=head">head</a>) == <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>)) {
 <a name="L58" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L58">58</a>                         if (++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &gt;= <a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=htable_size">htable_size</a>)
 <a name="L59" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L59">59</a>                                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L60" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L60">60</a>                 }
 <a name="L61" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L61">61</a>                 <a href="ident?i=head">head</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(
 <a name="L62" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L62">62</a>                         <a href="ident?i=hlist_nulls_first_rcu">hlist_nulls_first_rcu</a>(&amp;<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=hash">hash</a>[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>]));
 <a name="L63" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L63">63</a>         }
 <a name="L64" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L64">64</a>         return <a href="ident?i=head">head</a>;
 <a name="L65" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L65">65</a> }
 <a name="L66" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L67">67</a> static struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=ct_get_idx">ct_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
 <a name="L68" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L69">69</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=head">head</a> = <a href="ident?i=ct_get_first">ct_get_first</a>(<a href="ident?i=seq">seq</a>);
 <a name="L70" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L71">71</a>         if (<a href="ident?i=head">head</a>)
 <a name="L72" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L72">72</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (<a href="ident?i=head">head</a> = <a href="ident?i=ct_get_next">ct_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=head">head</a>)))
 <a name="L73" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L73">73</a>                         <a href="ident?i=pos">pos</a>--;
 <a name="L74" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L74">74</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : <a href="ident?i=head">head</a>;
 <a name="L75" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L75">75</a> }
 <a name="L76" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L77">77</a> static void *ct_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
 <a name="L78" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L78">78</a>         <a href="ident?i=__acquires">__acquires</a>(RCU)
 <a name="L79" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L79">79</a> {
 <a name="L80" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L80">80</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
 <a name="L81" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L81">81</a>         return <a href="ident?i=ct_get_idx">ct_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a>);
 <a name="L82" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L84">84</a> static void *<a href="ident?i=ct_seq_next">ct_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
 <a name="L85" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L86">86</a>         (*<a href="ident?i=pos">pos</a>)++;
 <a name="L87" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L87">87</a>         return <a href="ident?i=ct_get_next">ct_get_next</a>(<a href="ident?i=s">s</a>, <a href="ident?i=v">v</a>);
 <a name="L88" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L90">90</a> static void ct_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>)
 <a name="L91" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L91">91</a>         <a href="ident?i=__releases">__releases</a>(RCU)
 <a name="L92" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L92">92</a> {
 <a name="L93" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L93">93</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
 <a name="L94" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L94">94</a> }
 <a name="L95" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L96">96</a> #ifdef CONFIG_NF_CONNTRACK_SECMARK
 <a name="L97" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L97">97</a> static void <a href="ident?i=ct_show_secctx">ct_show_secctx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, const struct <a href="ident?i=nf_conn">nf_conn</a> *ct)
 <a name="L98" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L98">98</a> {
 <a name="L99" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L99">99</a>         int <a href="ident?i=ret">ret</a>;
<a name="L100" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L100">100</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>;
<a name="L101" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L101">101</a>         char *secctx;
<a name="L102" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L103">103</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=security_secid_to_secctx">security_secid_to_secctx</a>(ct-&gt;secmark, &amp;secctx, &amp;<a href="ident?i=len">len</a>);
<a name="L104" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L104">104</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L105" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L105">105</a>                 return;
<a name="L106" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L107">107</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"secctx=%s "</i>, secctx);
<a name="L108" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L109">109</a>         <a href="ident?i=security_release_secctx">security_release_secctx</a>(secctx, <a href="ident?i=len">len</a>);
<a name="L110" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L111">111</a> #else
<a name="L112" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L112">112</a> static inline void <a href="ident?i=ct_show_secctx">ct_show_secctx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, const struct <a href="ident?i=nf_conn">nf_conn</a> *ct)
<a name="L113" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L113">113</a> {
<a name="L114" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L114">114</a> }
<a name="L115" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L115">115</a> #endif
<a name="L116" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L117">117</a> static int <a href="ident?i=ct_seq_show">ct_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>)
<a name="L118" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L118">118</a> {
<a name="L119" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L119">119</a>         struct <a href="ident?i=nf_conntrack_tuple_hash">nf_conntrack_tuple_hash</a> *<a href="ident?i=hash">hash</a> = <a href="ident?i=v">v</a>;
<a name="L120" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L120">120</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct = <a href="ident?i=nf_ct_tuplehash_to_ctrack">nf_ct_tuplehash_to_ctrack</a>(<a href="ident?i=hash">hash</a>);
<a name="L121" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L121">121</a>         const struct <a href="ident?i=nf_conntrack_l3proto">nf_conntrack_l3proto</a> *l3proto;
<a name="L122" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L122">122</a>         const struct <a href="ident?i=nf_conntrack_l4proto">nf_conntrack_l4proto</a> *l4proto;
<a name="L123" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L123">123</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L124" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L125">125</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(ct);
<a name="L126" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L126">126</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;ct-&gt;ct_general.use)))
<a name="L127" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L127">127</a>                 return 0;
<a name="L128" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L130">130</a>         <b><i>/* we only want to print DIR_ORIGINAL */</i></b>
<a name="L131" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L131">131</a>         if (<a href="ident?i=NF_CT_DIRECTION">NF_CT_DIRECTION</a>(<a href="ident?i=hash">hash</a>))
<a name="L132" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L132">132</a>                 goto <a href="ident?i=release">release</a>;
<a name="L133" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L133">133</a>         if (<a href="ident?i=nf_ct_l3num">nf_ct_l3num</a>(ct) != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L134" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L134">134</a>                 goto <a href="ident?i=release">release</a>;
<a name="L135" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L136">136</a>         l3proto = <a href="ident?i=__nf_ct_l3proto_find">__nf_ct_l3proto_find</a>(<a href="ident?i=nf_ct_l3num">nf_ct_l3num</a>(ct));
<a name="L137" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L137">137</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(l3proto);
<a name="L138" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L138">138</a>         l4proto = <a href="ident?i=__nf_ct_l4proto_find">__nf_ct_l4proto_find</a>(<a href="ident?i=nf_ct_l3num">nf_ct_l3num</a>(ct), <a href="ident?i=nf_ct_protonum">nf_ct_protonum</a>(ct));
<a name="L139" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L139">139</a>         <a href="ident?i=NF_CT_ASSERT">NF_CT_ASSERT</a>(l4proto);
<a name="L140" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L141">141</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L142" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L142">142</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"%-8s %u %ld "</i>,
<a name="L143" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L143">143</a>                    l4proto-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=nf_ct_protonum">nf_ct_protonum</a>(ct),
<a name="L144" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L144">144</a>                    <a href="ident?i=timer_pending">timer_pending</a>(&amp;ct-&gt;<a href="ident?i=timeout">timeout</a>)
<a name="L145" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L145">145</a>                    ? (long)(ct-&gt;<a href="ident?i=timeout">timeout</a>.expires - <a href="ident?i=jiffies">jiffies</a>)/<a href="ident?i=HZ">HZ</a> : 0);
<a name="L146" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L147">147</a>         if (l4proto-&gt;print_conntrack)
<a name="L148" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L148">148</a>                 l4proto-&gt;print_conntrack(<a href="ident?i=s">s</a>, ct);
<a name="L149" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L150">150</a>         if (<a href="ident?i=seq_has_overflowed">seq_has_overflowed</a>(<a href="ident?i=s">s</a>))
<a name="L151" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L151">151</a>                 goto <a href="ident?i=release">release</a>;
<a name="L152" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L153">153</a>         <a href="ident?i=print_tuple">print_tuple</a>(<a href="ident?i=s">s</a>, &amp;ct-&gt;tuplehash[IP_CT_DIR_ORIGINAL].tuple,
<a name="L154" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L154">154</a>                     l3proto, l4proto);
<a name="L155" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L156">156</a>         if (<a href="ident?i=seq_has_overflowed">seq_has_overflowed</a>(<a href="ident?i=s">s</a>))
<a name="L157" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L157">157</a>                 goto <a href="ident?i=release">release</a>;
<a name="L158" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L159">159</a>         if (<a href="ident?i=seq_print_acct">seq_print_acct</a>(<a href="ident?i=s">s</a>, ct, IP_CT_DIR_ORIGINAL))
<a name="L160" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L160">160</a>                 goto <a href="ident?i=release">release</a>;
<a name="L161" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L162">162</a>         if (!(<a href="ident?i=test_bit">test_bit</a>(IPS_SEEN_REPLY_BIT, &amp;ct-&gt;<a href="ident?i=status">status</a>)))
<a name="L163" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L163">163</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"[UNREPLIED] "</i>);
<a name="L164" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L165">165</a>         <a href="ident?i=print_tuple">print_tuple</a>(<a href="ident?i=s">s</a>, &amp;ct-&gt;tuplehash[IP_CT_DIR_REPLY].tuple,
<a name="L166" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L166">166</a>                     l3proto, l4proto);
<a name="L167" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L168">168</a>         if (<a href="ident?i=seq_has_overflowed">seq_has_overflowed</a>(<a href="ident?i=s">s</a>))
<a name="L169" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L169">169</a>                 goto <a href="ident?i=release">release</a>;
<a name="L170" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L171">171</a>         if (<a href="ident?i=seq_print_acct">seq_print_acct</a>(<a href="ident?i=s">s</a>, ct, IP_CT_DIR_REPLY))
<a name="L172" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L172">172</a>                 goto <a href="ident?i=release">release</a>;
<a name="L173" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L174">174</a>         if (<a href="ident?i=test_bit">test_bit</a>(IPS_ASSURED_BIT, &amp;ct-&gt;<a href="ident?i=status">status</a>))
<a name="L175" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L175">175</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"[ASSURED] "</i>);
<a name="L176" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L177">177</a> #ifdef CONFIG_NF_CONNTRACK_MARK
<a name="L178" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L178">178</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"mark=%u "</i>, ct-&gt;<a href="ident?i=mark">mark</a>);
<a name="L179" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L179">179</a> #endif
<a name="L180" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L181">181</a>         <a href="ident?i=ct_show_secctx">ct_show_secctx</a>(<a href="ident?i=s">s</a>, ct);
<a name="L182" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L183">183</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"use=%u\n"</i>, <a href="ident?i=atomic_read">atomic_read</a>(&amp;ct-&gt;ct_general.use));
<a name="L184" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L185">185</a>         if (<a href="ident?i=seq_has_overflowed">seq_has_overflowed</a>(<a href="ident?i=s">s</a>))
<a name="L186" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L186">186</a>                 goto <a href="ident?i=release">release</a>;
<a name="L187" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L188">188</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L189" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L189">189</a> <a href="ident?i=release">release</a>:
<a name="L190" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L190">190</a>         <a href="ident?i=nf_ct_put">nf_ct_put</a>(ct);
<a name="L191" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L191">191</a>         return <a href="ident?i=ret">ret</a>;
<a name="L192" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L192">192</a> }
<a name="L193" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L194">194</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=ct_seq_ops">ct_seq_ops</a> = {
<a name="L195" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L195">195</a>         .<a href="ident?i=start">start</a> = ct_seq_start,
<a name="L196" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L196">196</a>         .<a href="ident?i=next">next</a>  = <a href="ident?i=ct_seq_next">ct_seq_next</a>,
<a name="L197" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L197">197</a>         .<a href="ident?i=stop">stop</a>  = ct_seq_stop,
<a name="L198" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L198">198</a>         .<a href="ident?i=show">show</a>  = <a href="ident?i=ct_seq_show">ct_seq_show</a>
<a name="L199" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L199">199</a> };
<a name="L200" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L201">201</a> static int <a href="ident?i=ct_open">ct_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L202" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L202">202</a> {
<a name="L203" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L203">203</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=ct_seq_ops">ct_seq_ops</a>,
<a name="L204" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L204">204</a>                             sizeof(struct <a href="ident?i=ct_iter_state">ct_iter_state</a>));
<a name="L205" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L205">205</a> }
<a name="L206" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L207">207</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=ct_file_ops">ct_file_ops</a> = {
<a name="L208" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L208">208</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L209" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L209">209</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=ct_open">ct_open</a>,
<a name="L210" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L210">210</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L211" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L211">211</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L212" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L212">212</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L213" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L213">213</a> };
<a name="L214" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L215">215</a> <b><i>/* expects */</i></b>
<a name="L216" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L216">216</a> struct <a href="ident?i=ct_expect_iter_state">ct_expect_iter_state</a> {
<a name="L217" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L217">217</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L218" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L218">218</a>         unsigned int <a href="ident?i=bucket">bucket</a>;
<a name="L219" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L219">219</a> };
<a name="L220" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L221">221</a> static struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=ct_expect_get_first">ct_expect_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L222" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L222">222</a> {
<a name="L223" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L223">223</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L224" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L224">224</a>         struct <a href="ident?i=ct_expect_iter_state">ct_expect_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L225" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L225">225</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L226" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L227">227</a>         for (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0; <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt; <a href="ident?i=nf_ct_expect_hsize">nf_ct_expect_hsize</a>; <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>++) {
<a name="L228" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L228">228</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(
<a name="L229" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L229">229</a>                         <a href="ident?i=hlist_first_rcu">hlist_first_rcu</a>(&amp;<a href="ident?i=net">net</a>-&gt;ct.expect_hash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>]));
<a name="L230" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L230">230</a>                 if (<a href="ident?i=n">n</a>)
<a name="L231" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L231">231</a>                         return <a href="ident?i=n">n</a>;
<a name="L232" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L232">232</a>         }
<a name="L233" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L233">233</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L234" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L234">234</a> }
<a name="L235" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L236">236</a> static struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=ct_expect_get_next">ct_expect_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>,
<a name="L237" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L237">237</a>                                              struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=head">head</a>)
<a name="L238" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L238">238</a> {
<a name="L239" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L239">239</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L240" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L240">240</a>         struct <a href="ident?i=ct_expect_iter_state">ct_expect_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L241" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L242">242</a>         <a href="ident?i=head">head</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=hlist_next_rcu">hlist_next_rcu</a>(<a href="ident?i=head">head</a>));
<a name="L243" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L243">243</a>         while (<a href="ident?i=head">head</a> == <a href="ident?i=NULL">NULL</a>) {
<a name="L244" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L244">244</a>                 if (++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &gt;= <a href="ident?i=nf_ct_expect_hsize">nf_ct_expect_hsize</a>)
<a name="L245" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L245">245</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L246" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L246">246</a>                 <a href="ident?i=head">head</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(
<a name="L247" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L247">247</a>                         <a href="ident?i=hlist_first_rcu">hlist_first_rcu</a>(&amp;<a href="ident?i=net">net</a>-&gt;ct.expect_hash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>]));
<a name="L248" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L248">248</a>         }
<a name="L249" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L249">249</a>         return <a href="ident?i=head">head</a>;
<a name="L250" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L250">250</a> }
<a name="L251" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L252">252</a> static struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=ct_expect_get_idx">ct_expect_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L253" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L253">253</a> {
<a name="L254" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L254">254</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=head">head</a> = <a href="ident?i=ct_expect_get_first">ct_expect_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L255" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L256">256</a>         if (<a href="ident?i=head">head</a>)
<a name="L257" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L257">257</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (<a href="ident?i=head">head</a> = <a href="ident?i=ct_expect_get_next">ct_expect_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=head">head</a>)))
<a name="L258" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L258">258</a>                         <a href="ident?i=pos">pos</a>--;
<a name="L259" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L259">259</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : <a href="ident?i=head">head</a>;
<a name="L260" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L260">260</a> }
<a name="L261" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L262">262</a> static void *exp_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L263" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L263">263</a>         <a href="ident?i=__acquires">__acquires</a>(RCU)
<a name="L264" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L264">264</a> {
<a name="L265" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L265">265</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L266" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L266">266</a>         return <a href="ident?i=ct_expect_get_idx">ct_expect_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a>);
<a name="L267" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L267">267</a> }
<a name="L268" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L269">269</a> static void *<a href="ident?i=exp_seq_next">exp_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L270" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L270">270</a> {
<a name="L271" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L271">271</a>         (*<a href="ident?i=pos">pos</a>)++;
<a name="L272" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L272">272</a>         return <a href="ident?i=ct_expect_get_next">ct_expect_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L273" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L273">273</a> }
<a name="L274" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L275">275</a> static void exp_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L276" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L276">276</a>         <a href="ident?i=__releases">__releases</a>(RCU)
<a name="L277" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L277">277</a> {
<a name="L278" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L278">278</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L279" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L279">279</a> }
<a name="L280" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L281">281</a> static int <a href="ident?i=exp_seq_show">exp_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=s">s</a>, void *<a href="ident?i=v">v</a>)
<a name="L282" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L282">282</a> {
<a name="L283" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L283">283</a>         struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a> *exp;
<a name="L284" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L284">284</a>         const struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a> = <a href="ident?i=v">v</a>;
<a name="L285" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L286">286</a>         exp = <a href="ident?i=hlist_entry">hlist_entry</a>(<a href="ident?i=n">n</a>, struct <a href="ident?i=nf_conntrack_expect">nf_conntrack_expect</a>, hnode);
<a name="L287" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L288">288</a>         if (exp-&gt;tuple.<a href="ident?i=src">src</a>.l3num != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L289" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L289">289</a>                 return 0;
<a name="L290" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L291">291</a>         if (exp-&gt;<a href="ident?i=timeout">timeout</a>.function)
<a name="L292" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L292">292</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"%ld "</i>, <a href="ident?i=timer_pending">timer_pending</a>(&amp;exp-&gt;<a href="ident?i=timeout">timeout</a>)
<a name="L293" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L293">293</a>                            ? (long)(exp-&gt;<a href="ident?i=timeout">timeout</a>.expires - <a href="ident?i=jiffies">jiffies</a>)/<a href="ident?i=HZ">HZ</a> : 0);
<a name="L294" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L294">294</a>         else
<a name="L295" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L295">295</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"- "</i>);
<a name="L296" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L297">297</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=s">s</a>, <i>"proto=%u "</i>, exp-&gt;tuple.<a href="ident?i=dst">dst</a>.protonum);
<a name="L298" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L299">299</a>         <a href="ident?i=print_tuple">print_tuple</a>(<a href="ident?i=s">s</a>, &amp;exp-&gt;tuple,
<a name="L300" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L300">300</a>                     <a href="ident?i=__nf_ct_l3proto_find">__nf_ct_l3proto_find</a>(exp-&gt;tuple.<a href="ident?i=src">src</a>.l3num),
<a name="L301" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L301">301</a>                     <a href="ident?i=__nf_ct_l4proto_find">__nf_ct_l4proto_find</a>(exp-&gt;tuple.<a href="ident?i=src">src</a>.l3num,
<a name="L302" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L302">302</a>                                          exp-&gt;tuple.<a href="ident?i=dst">dst</a>.protonum));
<a name="L303" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L303">303</a>         <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=s">s</a>, <i>'\n'</i>);
<a name="L304" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L305">305</a>         return 0;
<a name="L306" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L306">306</a> }
<a name="L307" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L308">308</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=exp_seq_ops">exp_seq_ops</a> = {
<a name="L309" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L309">309</a>         .<a href="ident?i=start">start</a> = exp_seq_start,
<a name="L310" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L310">310</a>         .<a href="ident?i=next">next</a> = <a href="ident?i=exp_seq_next">exp_seq_next</a>,
<a name="L311" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L311">311</a>         .<a href="ident?i=stop">stop</a> = exp_seq_stop,
<a name="L312" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L312">312</a>         .<a href="ident?i=show">show</a> = <a href="ident?i=exp_seq_show">exp_seq_show</a>
<a name="L313" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L313">313</a> };
<a name="L314" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L315">315</a> static int <a href="ident?i=exp_open">exp_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L316" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L316">316</a> {
<a name="L317" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L317">317</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=exp_seq_ops">exp_seq_ops</a>,
<a name="L318" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L318">318</a>                             sizeof(struct <a href="ident?i=ct_expect_iter_state">ct_expect_iter_state</a>));
<a name="L319" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L319">319</a> }
<a name="L320" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L321">321</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=ip_exp_file_ops">ip_exp_file_ops</a> = {
<a name="L322" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L322">322</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L323" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L323">323</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=exp_open">exp_open</a>,
<a name="L324" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L324">324</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L325" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L325">325</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L326" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L326">326</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L327" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L327">327</a> };
<a name="L328" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L329">329</a> static void *<a href="ident?i=ct_cpu_seq_start">ct_cpu_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L330" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L330">330</a> {
<a name="L331" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L331">331</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L332" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L332">332</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L333" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L334">334</a>         if (*<a href="ident?i=pos">pos</a> == 0)
<a name="L335" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L335">335</a>                 return <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L336" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L337">337</a>         for (<a href="ident?i=cpu">cpu</a> = *<a href="ident?i=pos">pos</a>-1; <a href="ident?i=cpu">cpu</a> &lt; <a href="ident?i=nr_cpu_ids">nr_cpu_ids</a>; ++<a href="ident?i=cpu">cpu</a>) {
<a name="L338" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L338">338</a>                 if (!<a href="ident?i=cpu_possible">cpu_possible</a>(<a href="ident?i=cpu">cpu</a>))
<a name="L339" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L339">339</a>                         continue;
<a name="L340" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L340">340</a>                 *<a href="ident?i=pos">pos</a> = <a href="ident?i=cpu">cpu</a>+1;
<a name="L341" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L341">341</a>                 return <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=stat">stat</a>, <a href="ident?i=cpu">cpu</a>);
<a name="L342" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L342">342</a>         }
<a name="L343" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L344">344</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L345" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L345">345</a> }
<a name="L346" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L347">347</a> static void *<a href="ident?i=ct_cpu_seq_next">ct_cpu_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L348" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L348">348</a> {
<a name="L349" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L349">349</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L350" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L350">350</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L351" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L352">352</a>         for (<a href="ident?i=cpu">cpu</a> = *<a href="ident?i=pos">pos</a>; <a href="ident?i=cpu">cpu</a> &lt; <a href="ident?i=nr_cpu_ids">nr_cpu_ids</a>; ++<a href="ident?i=cpu">cpu</a>) {
<a name="L353" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L353">353</a>                 if (!<a href="ident?i=cpu_possible">cpu_possible</a>(<a href="ident?i=cpu">cpu</a>))
<a name="L354" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L354">354</a>                         continue;
<a name="L355" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L355">355</a>                 *<a href="ident?i=pos">pos</a> = <a href="ident?i=cpu">cpu</a>+1;
<a name="L356" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L356">356</a>                 return <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=stat">stat</a>, <a href="ident?i=cpu">cpu</a>);
<a name="L357" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L357">357</a>         }
<a name="L358" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L359">359</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L360" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L360">360</a> }
<a name="L361" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L362">362</a> static void <a href="ident?i=ct_cpu_seq_stop">ct_cpu_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L363" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L363">363</a> {
<a name="L364" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L364">364</a> }
<a name="L365" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L366">366</a> static int <a href="ident?i=ct_cpu_seq_show">ct_cpu_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L367" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L367">367</a> {
<a name="L368" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L368">368</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L369" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L369">369</a>         unsigned int nr_conntracks = <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=net">net</a>-&gt;ct.<a href="ident?i=count">count</a>);
<a name="L370" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L370">370</a>         const struct <a href="ident?i=ip_conntrack_stat">ip_conntrack_stat</a> *<a href="ident?i=st">st</a> = <a href="ident?i=v">v</a>;
<a name="L371" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L372">372</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L373" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L373">373</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"entries  searched found new invalid ignore delete delete_list insert insert_failed drop early_drop icmp_error  expect_new expect_create expect_delete search_restart\n"</i>);
<a name="L374" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L374">374</a>                 return 0;
<a name="L375" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L375">375</a>         }
<a name="L376" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L376">376</a> 
<a name="L377" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L377">377</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%08x  %08x %08x %08x %08x %08x %08x %08x "</i>
<a name="L378" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L378">378</a>                         <i>"%08x %08x %08x %08x %08x  %08x %08x %08x %08x\n"</i>,
<a name="L379" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L379">379</a>                    nr_conntracks,
<a name="L380" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L380">380</a>                    <a href="ident?i=st">st</a>-&gt;searched,
<a name="L381" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L381">381</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=found">found</a>,
<a name="L382" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L382">382</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=new">new</a>,
<a name="L383" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L383">383</a>                    <a href="ident?i=st">st</a>-&gt;invalid,
<a name="L384" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L384">384</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=ignore">ignore</a>,
<a name="L385" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L385">385</a>                    <a href="ident?i=st">st</a>-&gt;delete,
<a name="L386" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L386">386</a>                    <a href="ident?i=st">st</a>-&gt;delete_list,
<a name="L387" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L387">387</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=insert">insert</a>,
<a name="L388" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L388">388</a>                    <a href="ident?i=st">st</a>-&gt;insert_failed,
<a name="L389" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L389">389</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=drop">drop</a>,
<a name="L390" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L390">390</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=early_drop">early_drop</a>,
<a name="L391" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L391">391</a>                    <a href="ident?i=st">st</a>-&gt;<a href="ident?i=error">error</a>,
<a name="L392" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L393">393</a>                    <a href="ident?i=st">st</a>-&gt;expect_new,
<a name="L394" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L394">394</a>                    <a href="ident?i=st">st</a>-&gt;expect_create,
<a name="L395" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L395">395</a>                    <a href="ident?i=st">st</a>-&gt;expect_delete,
<a name="L396" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L396">396</a>                    <a href="ident?i=st">st</a>-&gt;search_restart
<a name="L397" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L397">397</a>                 );
<a name="L398" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L398">398</a>         return 0;
<a name="L399" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L399">399</a> }
<a name="L400" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L401">401</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=ct_cpu_seq_ops">ct_cpu_seq_ops</a> = {
<a name="L402" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L402">402</a>         .<a href="ident?i=start">start</a>  = <a href="ident?i=ct_cpu_seq_start">ct_cpu_seq_start</a>,
<a name="L403" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L403">403</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=ct_cpu_seq_next">ct_cpu_seq_next</a>,
<a name="L404" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L404">404</a>         .<a href="ident?i=stop">stop</a>   = <a href="ident?i=ct_cpu_seq_stop">ct_cpu_seq_stop</a>,
<a name="L405" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L405">405</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=ct_cpu_seq_show">ct_cpu_seq_show</a>,
<a name="L406" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L406">406</a> };
<a name="L407" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L408">408</a> static int <a href="ident?i=ct_cpu_seq_open">ct_cpu_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L409" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L409">409</a> {
<a name="L410" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L410">410</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=ct_cpu_seq_ops">ct_cpu_seq_ops</a>,
<a name="L411" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L411">411</a>                             sizeof(struct <a href="ident?i=seq_net_private">seq_net_private</a>));
<a name="L412" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L412">412</a> }
<a name="L413" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L414">414</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=ct_cpu_seq_fops">ct_cpu_seq_fops</a> = {
<a name="L415" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L415">415</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L416" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L416">416</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=ct_cpu_seq_open">ct_cpu_seq_open</a>,
<a name="L417" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L417">417</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L418" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L418">418</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L419" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L419">419</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L420" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L420">420</a> };
<a name="L421" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L422">422</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ip_conntrack_net_init">ip_conntrack_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L423" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L423">423</a> {
<a name="L424" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L424">424</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *proc, *proc_exp, *<a href="ident?i=proc_stat">proc_stat</a>;
<a name="L425" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L426">426</a>         proc = <a href="ident?i=proc_create">proc_create</a>(<i>"ip_conntrack"</i>, 0440, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=ct_file_ops">ct_file_ops</a>);
<a name="L427" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L427">427</a>         if (!proc)
<a name="L428" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L428">428</a>                 goto err1;
<a name="L429" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L430">430</a>         proc_exp = <a href="ident?i=proc_create">proc_create</a>(<i>"ip_conntrack_expect"</i>, 0440, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L431" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L431">431</a>                                &amp;<a href="ident?i=ip_exp_file_ops">ip_exp_file_ops</a>);
<a name="L432" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L432">432</a>         if (!proc_exp)
<a name="L433" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L433">433</a>                 goto err2;
<a name="L434" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L434">434</a> 
<a name="L435" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L435">435</a>         <a href="ident?i=proc_stat">proc_stat</a> = <a href="ident?i=proc_create">proc_create</a>(<i>"ip_conntrack"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>,
<a name="L436" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L436">436</a>                                 <a href="ident?i=net">net</a>-&gt;proc_net_stat, &amp;<a href="ident?i=ct_cpu_seq_fops">ct_cpu_seq_fops</a>);
<a name="L437" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L437">437</a>         if (!<a href="ident?i=proc_stat">proc_stat</a>)
<a name="L438" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L438">438</a>                 goto err3;
<a name="L439" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L439">439</a>         return 0;
<a name="L440" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L441">441</a> err3:
<a name="L442" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L442">442</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_conntrack_expect"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L443" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L443">443</a> err2:
<a name="L444" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L444">444</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_conntrack"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L445" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L445">445</a> err1:
<a name="L446" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L446">446</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L447" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L447">447</a> }
<a name="L448" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L449">449</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ip_conntrack_net_exit">ip_conntrack_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L450" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L450">450</a> {
<a name="L451" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L451">451</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_conntrack"</i>, <a href="ident?i=net">net</a>-&gt;proc_net_stat);
<a name="L452" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L452">452</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_conntrack_expect"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L453" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L453">453</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"ip_conntrack"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L454" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L454">454</a> }
<a name="L455" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L456">456</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ip_conntrack_net_ops">ip_conntrack_net_ops</a> = {
<a name="L457" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L457">457</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ip_conntrack_net_init">ip_conntrack_net_init</a>,
<a name="L458" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L458">458</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ip_conntrack_net_exit">ip_conntrack_net_exit</a>,
<a name="L459" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L459">459</a> };
<a name="L460" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L461">461</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_conntrack_ipv4_compat_init">nf_conntrack_ipv4_compat_init</a>(void)
<a name="L462" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L462">462</a> {
<a name="L463" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L463">463</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ip_conntrack_net_ops">ip_conntrack_net_ops</a>);
<a name="L464" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L464">464</a> }
<a name="L465" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L466">466</a> void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_conntrack_ipv4_compat_fini">nf_conntrack_ipv4_compat_fini</a>(void)
<a name="L467" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L467">467</a> {
<a name="L468" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L468">468</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ip_conntrack_net_ops">ip_conntrack_net_ops</a>);
<a name="L469" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L469">469</a> }
<a name="L470" href="source/net/ipv4/netfilter/nf_conntrack_l3proto_ipv4_compat.c#L470">470</a> </pre></div><p>
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
