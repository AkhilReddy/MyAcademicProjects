<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/fib_lookup.h - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/fib_lookup.h">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/fib_lookup.h?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/fib_lookup.h?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/fib_lookup.h">fib_lookup.h</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/fib_lookup.h#L1">1</a> #ifndef <a href="ident?i=_FIB_LOOKUP_H">_FIB_LOOKUP_H</a>
  <a name="L2" href="source/net/ipv4/fib_lookup.h#L2">2</a> #define <a href="ident?i=_FIB_LOOKUP_H">_FIB_LOOKUP_H</a>
  <a name="L3" href="source/net/ipv4/fib_lookup.h#L3">3</a> 
  <a name="L4" href="source/net/ipv4/fib_lookup.h#L4">4</a> #include &lt;linux/types.h&gt;
  <a name="L5" href="source/net/ipv4/fib_lookup.h#L5">5</a> #include &lt;linux/list.h&gt;
  <a name="L6" href="source/net/ipv4/fib_lookup.h#L6">6</a> #include &lt;net/ip_fib.h&gt;
  <a name="L7" href="source/net/ipv4/fib_lookup.h#L7">7</a> 
  <a name="L8" href="source/net/ipv4/fib_lookup.h#L8">8</a> struct <a href="ident?i=fib_alias">fib_alias</a> {
  <a name="L9" href="source/net/ipv4/fib_lookup.h#L9">9</a>         struct <a href="ident?i=hlist_node">hlist_node</a>       fa_list;
 <a name="L10" href="source/net/ipv4/fib_lookup.h#L10">10</a>         struct <a href="ident?i=fib_info">fib_info</a>         *fa_info;
 <a name="L11" href="source/net/ipv4/fib_lookup.h#L11">11</a>         <a href="ident?i=u8">u8</a>                      fa_tos;
 <a name="L12" href="source/net/ipv4/fib_lookup.h#L12">12</a>         <a href="ident?i=u8">u8</a>                      fa_type;
 <a name="L13" href="source/net/ipv4/fib_lookup.h#L13">13</a>         <a href="ident?i=u8">u8</a>                      fa_state;
 <a name="L14" href="source/net/ipv4/fib_lookup.h#L14">14</a>         <a href="ident?i=u8">u8</a>                      fa_slen;
 <a name="L15" href="source/net/ipv4/fib_lookup.h#L15">15</a>         <a href="ident?i=u32">u32</a>                     tb_id;
 <a name="L16" href="source/net/ipv4/fib_lookup.h#L16">16</a>         struct <a href="ident?i=rcu_head">rcu_head</a>         rcu;
 <a name="L17" href="source/net/ipv4/fib_lookup.h#L17">17</a> };
 <a name="L18" href="source/net/ipv4/fib_lookup.h#L18">18</a> 
 <a name="L19" href="source/net/ipv4/fib_lookup.h#L19">19</a> #define <a href="ident?i=FA_S_ACCESSED">FA_S_ACCESSED</a>   0x01
 <a name="L20" href="source/net/ipv4/fib_lookup.h#L20">20</a> 
 <a name="L21" href="source/net/ipv4/fib_lookup.h#L21">21</a> <b><i>/* Dont write on fa_state unless needed, to keep it shared on all cpus */</i></b>
 <a name="L22" href="source/net/ipv4/fib_lookup.h#L22">22</a> static inline void <a href="ident?i=fib_alias_accessed">fib_alias_accessed</a>(struct <a href="ident?i=fib_alias">fib_alias</a> *fa)
 <a name="L23" href="source/net/ipv4/fib_lookup.h#L23">23</a> {
 <a name="L24" href="source/net/ipv4/fib_lookup.h#L24">24</a>         if (!(fa-&gt;fa_state &amp; <a href="ident?i=FA_S_ACCESSED">FA_S_ACCESSED</a>))
 <a name="L25" href="source/net/ipv4/fib_lookup.h#L25">25</a>                 fa-&gt;fa_state |= <a href="ident?i=FA_S_ACCESSED">FA_S_ACCESSED</a>;
 <a name="L26" href="source/net/ipv4/fib_lookup.h#L26">26</a> }
 <a name="L27" href="source/net/ipv4/fib_lookup.h#L27">27</a> 
 <a name="L28" href="source/net/ipv4/fib_lookup.h#L28">28</a> <b><i>/* Exported by fib_semantics.c */</i></b>
 <a name="L29" href="source/net/ipv4/fib_lookup.h#L29">29</a> void <a href="ident?i=fib_release_info">fib_release_info</a>(struct <a href="ident?i=fib_info">fib_info</a> *);
 <a name="L30" href="source/net/ipv4/fib_lookup.h#L30">30</a> struct <a href="ident?i=fib_info">fib_info</a> *<a href="ident?i=fib_create_info">fib_create_info</a>(struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>);
 <a name="L31" href="source/net/ipv4/fib_lookup.h#L31">31</a> int <a href="ident?i=fib_nh_match">fib_nh_match</a>(struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>, struct <a href="ident?i=fib_info">fib_info</a> *fi);
 <a name="L32" href="source/net/ipv4/fib_lookup.h#L32">32</a> int <a href="ident?i=fib_dump_info">fib_dump_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=pid">pid</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, int <a href="ident?i=event">event</a>, <a href="ident?i=u32">u32</a> tb_id,
 <a name="L33" href="source/net/ipv4/fib_lookup.h#L33">33</a>                   <a href="ident?i=u8">u8</a> <a href="ident?i=type">type</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, int dst_len, <a href="ident?i=u8">u8</a> tos, struct <a href="ident?i=fib_info">fib_info</a> *fi,
 <a name="L34" href="source/net/ipv4/fib_lookup.h#L34">34</a>                   unsigned int);
 <a name="L35" href="source/net/ipv4/fib_lookup.h#L35">35</a> void <a href="ident?i=rtmsg_fib">rtmsg_fib</a>(int <a href="ident?i=event">event</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a>, struct <a href="ident?i=fib_alias">fib_alias</a> *fa, int dst_len,
 <a name="L36" href="source/net/ipv4/fib_lookup.h#L36">36</a>                <a href="ident?i=u32">u32</a> tb_id, const struct <a href="ident?i=nl_info">nl_info</a> *<a href="ident?i=info">info</a>, unsigned int nlm_flags);
 <a name="L37" href="source/net/ipv4/fib_lookup.h#L37">37</a> 
 <a name="L38" href="source/net/ipv4/fib_lookup.h#L38">38</a> static inline void <a href="ident?i=fib_result_assign">fib_result_assign</a>(struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>,
 <a name="L39" href="source/net/ipv4/fib_lookup.h#L39">39</a>                                      struct <a href="ident?i=fib_info">fib_info</a> *fi)
 <a name="L40" href="source/net/ipv4/fib_lookup.h#L40">40</a> {
 <a name="L41" href="source/net/ipv4/fib_lookup.h#L41">41</a>         <b><i>/* we used to play games with refcounts, but we now use RCU */</i></b>
 <a name="L42" href="source/net/ipv4/fib_lookup.h#L42">42</a>         <a href="ident?i=res">res</a>-&gt;fi = fi;
 <a name="L43" href="source/net/ipv4/fib_lookup.h#L43">43</a> }
 <a name="L44" href="source/net/ipv4/fib_lookup.h#L44">44</a> 
 <a name="L45" href="source/net/ipv4/fib_lookup.h#L45">45</a> struct <a href="ident?i=fib_prop">fib_prop</a> {
 <a name="L46" href="source/net/ipv4/fib_lookup.h#L46">46</a>         int     <a href="ident?i=error">error</a>;
 <a name="L47" href="source/net/ipv4/fib_lookup.h#L47">47</a>         <a href="ident?i=u8">u8</a>      <a href="ident?i=scope">scope</a>;
 <a name="L48" href="source/net/ipv4/fib_lookup.h#L48">48</a> };
 <a name="L49" href="source/net/ipv4/fib_lookup.h#L49">49</a> 
 <a name="L50" href="source/net/ipv4/fib_lookup.h#L50">50</a> extern const struct <a href="ident?i=fib_prop">fib_prop</a> <a href="ident?i=fib_props">fib_props</a>[<a href="ident?i=RTN_MAX">RTN_MAX</a> + 1];
 <a name="L51" href="source/net/ipv4/fib_lookup.h#L51">51</a> 
 <a name="L52" href="source/net/ipv4/fib_lookup.h#L52">52</a> #endif <b><i>/* _FIB_LOOKUP_H */</i></b>
 <a name="L53" href="source/net/ipv4/fib_lookup.h#L53">53</a> </pre></div><p>
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
