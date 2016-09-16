<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_fastopen.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_fastopen.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_fastopen.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_fastopen.c">tcp_fastopen.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_fastopen.c#L1">1</a> #include &lt;linux/err.h&gt;
  <a name="L2" href="source/net/ipv4/tcp_fastopen.c#L2">2</a> #include &lt;linux/init.h&gt;
  <a name="L3" href="source/net/ipv4/tcp_fastopen.c#L3">3</a> #include &lt;linux/kernel.h&gt;
  <a name="L4" href="source/net/ipv4/tcp_fastopen.c#L4">4</a> #include &lt;linux/list.h&gt;
  <a name="L5" href="source/net/ipv4/tcp_fastopen.c#L5">5</a> #include &lt;linux/tcp.h&gt;
  <a name="L6" href="source/net/ipv4/tcp_fastopen.c#L6">6</a> #include &lt;linux/rcupdate.h&gt;
  <a name="L7" href="source/net/ipv4/tcp_fastopen.c#L7">7</a> #include &lt;linux/rculist.h&gt;
  <a name="L8" href="source/net/ipv4/tcp_fastopen.c#L8">8</a> #include &lt;net/inetpeer.h&gt;
  <a name="L9" href="source/net/ipv4/tcp_fastopen.c#L9">9</a> #include &lt;net/tcp.h&gt;
 <a name="L10" href="source/net/ipv4/tcp_fastopen.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/tcp_fastopen.c#L11">11</a> int <a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TFO_CLIENT_ENABLE">TFO_CLIENT_ENABLE</a>;
 <a name="L12" href="source/net/ipv4/tcp_fastopen.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/tcp_fastopen.c#L13">13</a> struct <a href="ident?i=tcp_fastopen_context">tcp_fastopen_context</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=tcp_fastopen_ctx">tcp_fastopen_ctx</a>;
 <a name="L14" href="source/net/ipv4/tcp_fastopen.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/tcp_fastopen.c#L15">15</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(tcp_fastopen_ctx_lock);
 <a name="L16" href="source/net/ipv4/tcp_fastopen.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/tcp_fastopen.c#L17">17</a> void <a href="ident?i=tcp_fastopen_init_key_once">tcp_fastopen_init_key_once</a>(<a href="ident?i=bool">bool</a> publish)
 <a name="L18" href="source/net/ipv4/tcp_fastopen.c#L18">18</a> {
 <a name="L19" href="source/net/ipv4/tcp_fastopen.c#L19">19</a>         static <a href="ident?i=u8">u8</a> <a href="ident?i=key">key</a>[<a href="ident?i=TCP_FASTOPEN_KEY_LENGTH">TCP_FASTOPEN_KEY_LENGTH</a>];
 <a name="L20" href="source/net/ipv4/tcp_fastopen.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_fastopen.c#L21">21</a>         <b><i>/* tcp_fastopen_reset_cipher publishes the new context</i></b>
 <a name="L22" href="source/net/ipv4/tcp_fastopen.c#L22">22</a> <b><i>         * atomically, so we allow this race happening here.</i></b>
 <a name="L23" href="source/net/ipv4/tcp_fastopen.c#L23">23</a> <b><i>         *</i></b>
 <a name="L24" href="source/net/ipv4/tcp_fastopen.c#L24">24</a> <b><i>         * All call sites of tcp_fastopen_cookie_gen also check</i></b>
 <a name="L25" href="source/net/ipv4/tcp_fastopen.c#L25">25</a> <b><i>         * for a valid cookie, so this is an acceptable risk.</i></b>
 <a name="L26" href="source/net/ipv4/tcp_fastopen.c#L26">26</a> <b><i>         */</i></b>
 <a name="L27" href="source/net/ipv4/tcp_fastopen.c#L27">27</a>         if (<a href="ident?i=net_get_random_once">net_get_random_once</a>(<a href="ident?i=key">key</a>, sizeof(<a href="ident?i=key">key</a>)) &amp;&amp; publish)
 <a name="L28" href="source/net/ipv4/tcp_fastopen.c#L28">28</a>                 <a href="ident?i=tcp_fastopen_reset_cipher">tcp_fastopen_reset_cipher</a>(<a href="ident?i=key">key</a>, sizeof(<a href="ident?i=key">key</a>));
 <a name="L29" href="source/net/ipv4/tcp_fastopen.c#L29">29</a> }
 <a name="L30" href="source/net/ipv4/tcp_fastopen.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/tcp_fastopen.c#L31">31</a> static void <a href="ident?i=tcp_fastopen_ctx_free">tcp_fastopen_ctx_free</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
 <a name="L32" href="source/net/ipv4/tcp_fastopen.c#L32">32</a> {
 <a name="L33" href="source/net/ipv4/tcp_fastopen.c#L33">33</a>         struct <a href="ident?i=tcp_fastopen_context">tcp_fastopen_context</a> *<a href="ident?i=ctx">ctx</a> =
 <a name="L34" href="source/net/ipv4/tcp_fastopen.c#L34">34</a>             <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=tcp_fastopen_context">tcp_fastopen_context</a>, rcu);
 <a name="L35" href="source/net/ipv4/tcp_fastopen.c#L35">35</a>         <a href="ident?i=crypto_free_cipher">crypto_free_cipher</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a>);
 <a name="L36" href="source/net/ipv4/tcp_fastopen.c#L36">36</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=ctx">ctx</a>);
 <a name="L37" href="source/net/ipv4/tcp_fastopen.c#L37">37</a> }
 <a name="L38" href="source/net/ipv4/tcp_fastopen.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/tcp_fastopen.c#L39">39</a> int <a href="ident?i=tcp_fastopen_reset_cipher">tcp_fastopen_reset_cipher</a>(void *<a href="ident?i=key">key</a>, unsigned int <a href="ident?i=len">len</a>)
 <a name="L40" href="source/net/ipv4/tcp_fastopen.c#L40">40</a> {
 <a name="L41" href="source/net/ipv4/tcp_fastopen.c#L41">41</a>         int <a href="ident?i=err">err</a>;
 <a name="L42" href="source/net/ipv4/tcp_fastopen.c#L42">42</a>         struct <a href="ident?i=tcp_fastopen_context">tcp_fastopen_context</a> *<a href="ident?i=ctx">ctx</a>, *octx;
 <a name="L43" href="source/net/ipv4/tcp_fastopen.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/tcp_fastopen.c#L44">44</a>         <a href="ident?i=ctx">ctx</a> = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*<a href="ident?i=ctx">ctx</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
 <a name="L45" href="source/net/ipv4/tcp_fastopen.c#L45">45</a>         if (!<a href="ident?i=ctx">ctx</a>)
 <a name="L46" href="source/net/ipv4/tcp_fastopen.c#L46">46</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L47" href="source/net/ipv4/tcp_fastopen.c#L47">47</a>         <a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a> = <a href="ident?i=crypto_alloc_cipher">crypto_alloc_cipher</a>(<i>"aes"</i>, 0, 0);
 <a name="L48" href="source/net/ipv4/tcp_fastopen.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/tcp_fastopen.c#L49">49</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a>)) {
 <a name="L50" href="source/net/ipv4/tcp_fastopen.c#L50">50</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a>);
 <a name="L51" href="source/net/ipv4/tcp_fastopen.c#L51">51</a> <a href="ident?i=error">error</a>:          <a href="ident?i=kfree">kfree</a>(<a href="ident?i=ctx">ctx</a>);
 <a name="L52" href="source/net/ipv4/tcp_fastopen.c#L52">52</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"TCP: TFO aes cipher alloc error: %d\n"</i>, <a href="ident?i=err">err</a>);
 <a name="L53" href="source/net/ipv4/tcp_fastopen.c#L53">53</a>                 return <a href="ident?i=err">err</a>;
 <a name="L54" href="source/net/ipv4/tcp_fastopen.c#L54">54</a>         }
 <a name="L55" href="source/net/ipv4/tcp_fastopen.c#L55">55</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_cipher_setkey">crypto_cipher_setkey</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a>, <a href="ident?i=key">key</a>, <a href="ident?i=len">len</a>);
 <a name="L56" href="source/net/ipv4/tcp_fastopen.c#L56">56</a>         if (<a href="ident?i=err">err</a>) {
 <a name="L57" href="source/net/ipv4/tcp_fastopen.c#L57">57</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"TCP: TFO cipher key error: %d\n"</i>, <a href="ident?i=err">err</a>);
 <a name="L58" href="source/net/ipv4/tcp_fastopen.c#L58">58</a>                 <a href="ident?i=crypto_free_cipher">crypto_free_cipher</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a>);
 <a name="L59" href="source/net/ipv4/tcp_fastopen.c#L59">59</a>                 goto <a href="ident?i=error">error</a>;
 <a name="L60" href="source/net/ipv4/tcp_fastopen.c#L60">60</a>         }
 <a name="L61" href="source/net/ipv4/tcp_fastopen.c#L61">61</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=key">key</a>, <a href="ident?i=len">len</a>);
 <a name="L62" href="source/net/ipv4/tcp_fastopen.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/tcp_fastopen.c#L63">63</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;tcp_fastopen_ctx_lock);
 <a name="L64" href="source/net/ipv4/tcp_fastopen.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/tcp_fastopen.c#L65">65</a>         octx = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=tcp_fastopen_ctx">tcp_fastopen_ctx</a>,
 <a name="L66" href="source/net/ipv4/tcp_fastopen.c#L66">66</a>                                 <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;tcp_fastopen_ctx_lock));
 <a name="L67" href="source/net/ipv4/tcp_fastopen.c#L67">67</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=tcp_fastopen_ctx">tcp_fastopen_ctx</a>, <a href="ident?i=ctx">ctx</a>);
 <a name="L68" href="source/net/ipv4/tcp_fastopen.c#L68">68</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;tcp_fastopen_ctx_lock);
 <a name="L69" href="source/net/ipv4/tcp_fastopen.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/tcp_fastopen.c#L70">70</a>         if (octx)
 <a name="L71" href="source/net/ipv4/tcp_fastopen.c#L71">71</a>                 <a href="ident?i=call_rcu">call_rcu</a>(&amp;octx-&gt;rcu, <a href="ident?i=tcp_fastopen_ctx_free">tcp_fastopen_ctx_free</a>);
 <a name="L72" href="source/net/ipv4/tcp_fastopen.c#L72">72</a>         return <a href="ident?i=err">err</a>;
 <a name="L73" href="source/net/ipv4/tcp_fastopen.c#L73">73</a> }
 <a name="L74" href="source/net/ipv4/tcp_fastopen.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/tcp_fastopen.c#L75">75</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=__tcp_fastopen_cookie_gen">__tcp_fastopen_cookie_gen</a>(const void *<a href="ident?i=path">path</a>,
 <a name="L76" href="source/net/ipv4/tcp_fastopen.c#L76">76</a>                                       struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc)
 <a name="L77" href="source/net/ipv4/tcp_fastopen.c#L77">77</a> {
 <a name="L78" href="source/net/ipv4/tcp_fastopen.c#L78">78</a>         struct <a href="ident?i=tcp_fastopen_context">tcp_fastopen_context</a> *<a href="ident?i=ctx">ctx</a>;
 <a name="L79" href="source/net/ipv4/tcp_fastopen.c#L79">79</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ok">ok</a> = <a href="ident?i=false">false</a>;
 <a name="L80" href="source/net/ipv4/tcp_fastopen.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_fastopen.c#L81">81</a>         <a href="ident?i=tcp_fastopen_init_key_once">tcp_fastopen_init_key_once</a>(<a href="ident?i=true">true</a>);
 <a name="L82" href="source/net/ipv4/tcp_fastopen.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/tcp_fastopen.c#L83">83</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
 <a name="L84" href="source/net/ipv4/tcp_fastopen.c#L84">84</a>         <a href="ident?i=ctx">ctx</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tcp_fastopen_ctx">tcp_fastopen_ctx</a>);
 <a name="L85" href="source/net/ipv4/tcp_fastopen.c#L85">85</a>         if (<a href="ident?i=ctx">ctx</a>) {
 <a name="L86" href="source/net/ipv4/tcp_fastopen.c#L86">86</a>                 <a href="ident?i=crypto_cipher_encrypt_one">crypto_cipher_encrypt_one</a>(<a href="ident?i=ctx">ctx</a>-&gt;<a href="ident?i=tfm">tfm</a>, foc-&gt;<a href="ident?i=val">val</a>, <a href="ident?i=path">path</a>);
 <a name="L87" href="source/net/ipv4/tcp_fastopen.c#L87">87</a>                 foc-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=TCP_FASTOPEN_COOKIE_SIZE">TCP_FASTOPEN_COOKIE_SIZE</a>;
 <a name="L88" href="source/net/ipv4/tcp_fastopen.c#L88">88</a>                 <a href="ident?i=ok">ok</a> = <a href="ident?i=true">true</a>;
 <a name="L89" href="source/net/ipv4/tcp_fastopen.c#L89">89</a>         }
 <a name="L90" href="source/net/ipv4/tcp_fastopen.c#L90">90</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
 <a name="L91" href="source/net/ipv4/tcp_fastopen.c#L91">91</a>         return <a href="ident?i=ok">ok</a>;
 <a name="L92" href="source/net/ipv4/tcp_fastopen.c#L92">92</a> }
 <a name="L93" href="source/net/ipv4/tcp_fastopen.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/tcp_fastopen.c#L94">94</a> <b><i>/* Generate the fastopen cookie by doing aes128 encryption on both</i></b>
 <a name="L95" href="source/net/ipv4/tcp_fastopen.c#L95">95</a> <b><i> * the source and destination addresses. Pad 0s for IPv4 or IPv4-mapped-IPv6</i></b>
 <a name="L96" href="source/net/ipv4/tcp_fastopen.c#L96">96</a> <b><i> * addresses. For the longer IPv6 addresses use CBC-MAC.</i></b>
 <a name="L97" href="source/net/ipv4/tcp_fastopen.c#L97">97</a> <b><i> *</i></b>
 <a name="L98" href="source/net/ipv4/tcp_fastopen.c#L98">98</a> <b><i> * XXX (TFO) - refactor when TCP_FASTOPEN_COOKIE_SIZE != AES_BLOCK_SIZE.</i></b>
 <a name="L99" href="source/net/ipv4/tcp_fastopen.c#L99">99</a> <b><i> */</i></b>
<a name="L100" href="source/net/ipv4/tcp_fastopen.c#L100">100</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_fastopen_cookie_gen">tcp_fastopen_cookie_gen</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L101" href="source/net/ipv4/tcp_fastopen.c#L101">101</a>                                     struct <a href="ident?i=sk_buff">sk_buff</a> *syn,
<a name="L102" href="source/net/ipv4/tcp_fastopen.c#L102">102</a>                                     struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc)
<a name="L103" href="source/net/ipv4/tcp_fastopen.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/tcp_fastopen.c#L104">104</a>         if (<a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L105" href="source/net/ipv4/tcp_fastopen.c#L105">105</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(syn);
<a name="L106" href="source/net/ipv4/tcp_fastopen.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/tcp_fastopen.c#L107">107</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=path">path</a>[4] = { iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, 0, 0 };
<a name="L108" href="source/net/ipv4/tcp_fastopen.c#L108">108</a>                 return <a href="ident?i=__tcp_fastopen_cookie_gen">__tcp_fastopen_cookie_gen</a>(<a href="ident?i=path">path</a>, foc);
<a name="L109" href="source/net/ipv4/tcp_fastopen.c#L109">109</a>         }
<a name="L110" href="source/net/ipv4/tcp_fastopen.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/tcp_fastopen.c#L111">111</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L112" href="source/net/ipv4/tcp_fastopen.c#L112">112</a>         if (<a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L113" href="source/net/ipv4/tcp_fastopen.c#L113">113</a>                 const struct <a href="ident?i=ipv6hdr">ipv6hdr</a> *ip6h = <a href="ident?i=ipv6_hdr">ipv6_hdr</a>(syn);
<a name="L114" href="source/net/ipv4/tcp_fastopen.c#L114">114</a>                 struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> <a href="ident?i=tmp">tmp</a>;
<a name="L115" href="source/net/ipv4/tcp_fastopen.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/tcp_fastopen.c#L116">116</a>                 if (<a href="ident?i=__tcp_fastopen_cookie_gen">__tcp_fastopen_cookie_gen</a>(&amp;ip6h-&gt;<a href="ident?i=saddr">saddr</a>, &amp;<a href="ident?i=tmp">tmp</a>)) {
<a name="L117" href="source/net/ipv4/tcp_fastopen.c#L117">117</a>                         struct <a href="ident?i=in6_addr">in6_addr</a> *<a href="ident?i=buf">buf</a> = (struct <a href="ident?i=in6_addr">in6_addr</a> *) <a href="ident?i=tmp">tmp</a>.<a href="ident?i=val">val</a>;
<a name="L118" href="source/net/ipv4/tcp_fastopen.c#L118">118</a>                         int <a href="ident?i=i">i</a>;
<a name="L119" href="source/net/ipv4/tcp_fastopen.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tcp_fastopen.c#L120">120</a>                         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; 4; <a href="ident?i=i">i</a>++)
<a name="L121" href="source/net/ipv4/tcp_fastopen.c#L121">121</a>                                 <a href="ident?i=buf">buf</a>-&gt;<a href="ident?i=s6_addr32">s6_addr32</a>[<a href="ident?i=i">i</a>] ^= ip6h-&gt;<a href="ident?i=daddr">daddr</a>.<a href="ident?i=s6_addr32">s6_addr32</a>[<a href="ident?i=i">i</a>];
<a name="L122" href="source/net/ipv4/tcp_fastopen.c#L122">122</a>                         return <a href="ident?i=__tcp_fastopen_cookie_gen">__tcp_fastopen_cookie_gen</a>(<a href="ident?i=buf">buf</a>, foc);
<a name="L123" href="source/net/ipv4/tcp_fastopen.c#L123">123</a>                 }
<a name="L124" href="source/net/ipv4/tcp_fastopen.c#L124">124</a>         }
<a name="L125" href="source/net/ipv4/tcp_fastopen.c#L125">125</a> #endif
<a name="L126" href="source/net/ipv4/tcp_fastopen.c#L126">126</a>         return <a href="ident?i=false">false</a>;
<a name="L127" href="source/net/ipv4/tcp_fastopen.c#L127">127</a> }
<a name="L128" href="source/net/ipv4/tcp_fastopen.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/tcp_fastopen.c#L129">129</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_fastopen_create_child">tcp_fastopen_create_child</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L130" href="source/net/ipv4/tcp_fastopen.c#L130">130</a>                                       struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L131" href="source/net/ipv4/tcp_fastopen.c#L131">131</a>                                       struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L132" href="source/net/ipv4/tcp_fastopen.c#L132">132</a>                                       struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L133" href="source/net/ipv4/tcp_fastopen.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/tcp_fastopen.c#L134">134</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>;
<a name="L135" href="source/net/ipv4/tcp_fastopen.c#L135">135</a>         struct <a href="ident?i=request_sock_queue">request_sock_queue</a> *<a href="ident?i=queue">queue</a> = &amp;<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue;
<a name="L136" href="source/net/ipv4/tcp_fastopen.c#L136">136</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=child">child</a>;
<a name="L137" href="source/net/ipv4/tcp_fastopen.c#L137">137</a>         <a href="ident?i=u32">u32</a> end_seq;
<a name="L138" href="source/net/ipv4/tcp_fastopen.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/tcp_fastopen.c#L139">139</a>         <a href="ident?i=req">req</a>-&gt;num_retrans = 0;
<a name="L140" href="source/net/ipv4/tcp_fastopen.c#L140">140</a>         <a href="ident?i=req">req</a>-&gt;num_timeout = 0;
<a name="L141" href="source/net/ipv4/tcp_fastopen.c#L141">141</a>         <a href="ident?i=req">req</a>-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L142" href="source/net/ipv4/tcp_fastopen.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/tcp_fastopen.c#L143">143</a>         <a href="ident?i=child">child</a> = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;syn_recv_sock(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L144" href="source/net/ipv4/tcp_fastopen.c#L144">144</a>         if (!<a href="ident?i=child">child</a>)
<a name="L145" href="source/net/ipv4/tcp_fastopen.c#L145">145</a>                 return <a href="ident?i=false">false</a>;
<a name="L146" href="source/net/ipv4/tcp_fastopen.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_fastopen.c#L147">147</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L148" href="source/net/ipv4/tcp_fastopen.c#L148">148</a>         <a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=qlen">qlen</a>++;
<a name="L149" href="source/net/ipv4/tcp_fastopen.c#L149">149</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L150" href="source/net/ipv4/tcp_fastopen.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/tcp_fastopen.c#L151">151</a>         <b><i>/* Initialize the child socket. Have to fix some values to take</i></b>
<a name="L152" href="source/net/ipv4/tcp_fastopen.c#L152">152</a> <b><i>         * into account the child is a Fast Open socket and is created</i></b>
<a name="L153" href="source/net/ipv4/tcp_fastopen.c#L153">153</a> <b><i>         * only out of the bits carried in the SYN packet.</i></b>
<a name="L154" href="source/net/ipv4/tcp_fastopen.c#L154">154</a> <b><i>         */</i></b>
<a name="L155" href="source/net/ipv4/tcp_fastopen.c#L155">155</a>         <a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(<a href="ident?i=child">child</a>);
<a name="L156" href="source/net/ipv4/tcp_fastopen.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/tcp_fastopen.c#L157">157</a>         <a href="ident?i=tp">tp</a>-&gt;fastopen_rsk = <a href="ident?i=req">req</a>;
<a name="L158" href="source/net/ipv4/tcp_fastopen.c#L158">158</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;tfo_listener = <a href="ident?i=true">true</a>;
<a name="L159" href="source/net/ipv4/tcp_fastopen.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/tcp_fastopen.c#L160">160</a>         <b><i>/* RFC1323: The window in SYN &amp; SYN/ACK segments is never</i></b>
<a name="L161" href="source/net/ipv4/tcp_fastopen.c#L161">161</a> <b><i>         * scaled. So correct it appropriately.</i></b>
<a name="L162" href="source/net/ipv4/tcp_fastopen.c#L162">162</a> <b><i>         */</i></b>
<a name="L163" href="source/net/ipv4/tcp_fastopen.c#L163">163</a>         <a href="ident?i=tp">tp</a>-&gt;snd_wnd = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=window">window</a>);
<a name="L164" href="source/net/ipv4/tcp_fastopen.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/tcp_fastopen.c#L165">165</a>         <b><i>/* Activate the retrans timer so that SYNACK can be retransmitted.</i></b>
<a name="L166" href="source/net/ipv4/tcp_fastopen.c#L166">166</a> <b><i>         * The request socket is not added to the SYN table of the parent</i></b>
<a name="L167" href="source/net/ipv4/tcp_fastopen.c#L167">167</a> <b><i>         * because it's been added to the accept queue directly.</i></b>
<a name="L168" href="source/net/ipv4/tcp_fastopen.c#L168">168</a> <b><i>         */</i></b>
<a name="L169" href="source/net/ipv4/tcp_fastopen.c#L169">169</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(<a href="ident?i=child">child</a>, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L170" href="source/net/ipv4/tcp_fastopen.c#L170">170</a>                                   <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L171" href="source/net/ipv4/tcp_fastopen.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/tcp_fastopen.c#L172">172</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=req">req</a>-&gt;<a href="ident?i=rsk_refcnt">rsk_refcnt</a>, 1);
<a name="L173" href="source/net/ipv4/tcp_fastopen.c#L173">173</a>         <b><i>/* Add the child socket directly into the accept queue */</i></b>
<a name="L174" href="source/net/ipv4/tcp_fastopen.c#L174">174</a>         <a href="ident?i=inet_csk_reqsk_queue_add">inet_csk_reqsk_queue_add</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=child">child</a>);
<a name="L175" href="source/net/ipv4/tcp_fastopen.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/tcp_fastopen.c#L176">176</a>         <b><i>/* Now finish processing the fastopen child socket. */</i></b>
<a name="L177" href="source/net/ipv4/tcp_fastopen.c#L177">177</a>         <a href="ident?i=inet_csk">inet_csk</a>(<a href="ident?i=child">child</a>)-&gt;icsk_af_ops-&gt;rebuild_header(<a href="ident?i=child">child</a>);
<a name="L178" href="source/net/ipv4/tcp_fastopen.c#L178">178</a>         <a href="ident?i=tcp_init_congestion_control">tcp_init_congestion_control</a>(<a href="ident?i=child">child</a>);
<a name="L179" href="source/net/ipv4/tcp_fastopen.c#L179">179</a>         <a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>(<a href="ident?i=child">child</a>);
<a name="L180" href="source/net/ipv4/tcp_fastopen.c#L180">180</a>         <a href="ident?i=tcp_init_metrics">tcp_init_metrics</a>(<a href="ident?i=child">child</a>);
<a name="L181" href="source/net/ipv4/tcp_fastopen.c#L181">181</a>         <a href="ident?i=tcp_init_buffer_space">tcp_init_buffer_space</a>(<a href="ident?i=child">child</a>);
<a name="L182" href="source/net/ipv4/tcp_fastopen.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_fastopen.c#L183">183</a>         <b><i>/* Queue the data carried in the SYN packet. We need to first</i></b>
<a name="L184" href="source/net/ipv4/tcp_fastopen.c#L184">184</a> <b><i>         * bump skb's refcnt because the caller will attempt to free it.</i></b>
<a name="L185" href="source/net/ipv4/tcp_fastopen.c#L185">185</a> <b><i>         * Note that IPv6 might also have used skb_get() trick</i></b>
<a name="L186" href="source/net/ipv4/tcp_fastopen.c#L186">186</a> <b><i>         * in tcp_v6_conn_request() to keep this SYN around (treq-&gt;pktopts)</i></b>
<a name="L187" href="source/net/ipv4/tcp_fastopen.c#L187">187</a> <b><i>         * So we need to eventually get a clone of the packet,</i></b>
<a name="L188" href="source/net/ipv4/tcp_fastopen.c#L188">188</a> <b><i>         * before inserting it in sk_receive_queue.</i></b>
<a name="L189" href="source/net/ipv4/tcp_fastopen.c#L189">189</a> <b><i>         *</i></b>
<a name="L190" href="source/net/ipv4/tcp_fastopen.c#L190">190</a> <b><i>         * XXX (TFO) - we honor a zero-payload TFO request for now,</i></b>
<a name="L191" href="source/net/ipv4/tcp_fastopen.c#L191">191</a> <b><i>         * (any reason not to?) but no need to queue the skb since</i></b>
<a name="L192" href="source/net/ipv4/tcp_fastopen.c#L192">192</a> <b><i>         * there is no data. How about SYN+FIN?</i></b>
<a name="L193" href="source/net/ipv4/tcp_fastopen.c#L193">193</a> <b><i>         */</i></b>
<a name="L194" href="source/net/ipv4/tcp_fastopen.c#L194">194</a>         end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L195" href="source/net/ipv4/tcp_fastopen.c#L195">195</a>         if (end_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1) {
<a name="L196" href="source/net/ipv4/tcp_fastopen.c#L196">196</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb2;
<a name="L197" href="source/net/ipv4/tcp_fastopen.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/tcp_fastopen.c#L198">198</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_shared">skb_shared</a>(<a href="ident?i=skb">skb</a>)))
<a name="L199" href="source/net/ipv4/tcp_fastopen.c#L199">199</a>                         skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L200" href="source/net/ipv4/tcp_fastopen.c#L200">200</a>                 else
<a name="L201" href="source/net/ipv4/tcp_fastopen.c#L201">201</a>                         skb2 = <a href="ident?i=skb_get">skb_get</a>(<a href="ident?i=skb">skb</a>);
<a name="L202" href="source/net/ipv4/tcp_fastopen.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/tcp_fastopen.c#L203">203</a>                 if (<a href="ident?i=likely">likely</a>(skb2)) {
<a name="L204" href="source/net/ipv4/tcp_fastopen.c#L204">204</a>                         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(skb2);
<a name="L205" href="source/net/ipv4/tcp_fastopen.c#L205">205</a>                         <a href="ident?i=__skb_pull">__skb_pull</a>(skb2, <a href="ident?i=tcp_hdrlen">tcp_hdrlen</a>(<a href="ident?i=skb">skb</a>));
<a name="L206" href="source/net/ipv4/tcp_fastopen.c#L206">206</a>                         <a href="ident?i=skb_set_owner_r">skb_set_owner_r</a>(skb2, <a href="ident?i=child">child</a>);
<a name="L207" href="source/net/ipv4/tcp_fastopen.c#L207">207</a>                         <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(&amp;<a href="ident?i=child">child</a>-&gt;sk_receive_queue, skb2);
<a name="L208" href="source/net/ipv4/tcp_fastopen.c#L208">208</a>                         <a href="ident?i=tp">tp</a>-&gt;syn_data_acked = 1;
<a name="L209" href="source/net/ipv4/tcp_fastopen.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/tcp_fastopen.c#L210">210</a>                         <b><i>/* u64_stats_update_begin(&amp;tp-&gt;syncp) not needed here,</i></b>
<a name="L211" href="source/net/ipv4/tcp_fastopen.c#L211">211</a> <b><i>                         * as we certainly are not changing upper 32bit value (0)</i></b>
<a name="L212" href="source/net/ipv4/tcp_fastopen.c#L212">212</a> <b><i>                         */</i></b>
<a name="L213" href="source/net/ipv4/tcp_fastopen.c#L213">213</a>                         <a href="ident?i=tp">tp</a>-&gt;bytes_received = end_seq - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> - 1;
<a name="L214" href="source/net/ipv4/tcp_fastopen.c#L214">214</a>                 } else {
<a name="L215" href="source/net/ipv4/tcp_fastopen.c#L215">215</a>                         end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L216" href="source/net/ipv4/tcp_fastopen.c#L216">216</a>                 }
<a name="L217" href="source/net/ipv4/tcp_fastopen.c#L217">217</a>         }
<a name="L218" href="source/net/ipv4/tcp_fastopen.c#L218">218</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = end_seq;
<a name="L219" href="source/net/ipv4/tcp_fastopen.c#L219">219</a>         sk-&gt;sk_data_ready(sk);
<a name="L220" href="source/net/ipv4/tcp_fastopen.c#L220">220</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(<a href="ident?i=child">child</a>);
<a name="L221" href="source/net/ipv4/tcp_fastopen.c#L221">221</a>         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=child">child</a>);
<a name="L222" href="source/net/ipv4/tcp_fastopen.c#L222">222</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=req">req</a>-&gt;sk);
<a name="L223" href="source/net/ipv4/tcp_fastopen.c#L223">223</a>         return <a href="ident?i=true">true</a>;
<a name="L224" href="source/net/ipv4/tcp_fastopen.c#L224">224</a> }
<a name="L225" href="source/net/ipv4/tcp_fastopen.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/tcp_fastopen.c#L226">226</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_fastopen_queue_check">tcp_fastopen_queue_check</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L227" href="source/net/ipv4/tcp_fastopen.c#L227">227</a> {
<a name="L228" href="source/net/ipv4/tcp_fastopen.c#L228">228</a>         struct <a href="ident?i=fastopen_queue">fastopen_queue</a> *fastopenq;
<a name="L229" href="source/net/ipv4/tcp_fastopen.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/tcp_fastopen.c#L230">230</a>         <b><i>/* Make sure the listener has enabled fastopen, and we don't</i></b>
<a name="L231" href="source/net/ipv4/tcp_fastopen.c#L231">231</a> <b><i>         * exceed the max # of pending TFO requests allowed before trying</i></b>
<a name="L232" href="source/net/ipv4/tcp_fastopen.c#L232">232</a> <b><i>         * to validating the cookie in order to avoid burning CPU cycles</i></b>
<a name="L233" href="source/net/ipv4/tcp_fastopen.c#L233">233</a> <b><i>         * unnecessarily.</i></b>
<a name="L234" href="source/net/ipv4/tcp_fastopen.c#L234">234</a> <b><i>         *</i></b>
<a name="L235" href="source/net/ipv4/tcp_fastopen.c#L235">235</a> <b><i>         * XXX (TFO) - The implication of checking the max_qlen before</i></b>
<a name="L236" href="source/net/ipv4/tcp_fastopen.c#L236">236</a> <b><i>         * processing a cookie request is that clients can't differentiate</i></b>
<a name="L237" href="source/net/ipv4/tcp_fastopen.c#L237">237</a> <b><i>         * between qlen overflow causing Fast Open to be disabled</i></b>
<a name="L238" href="source/net/ipv4/tcp_fastopen.c#L238">238</a> <b><i>         * temporarily vs a server not supporting Fast Open at all.</i></b>
<a name="L239" href="source/net/ipv4/tcp_fastopen.c#L239">239</a> <b><i>         */</i></b>
<a name="L240" href="source/net/ipv4/tcp_fastopen.c#L240">240</a>         fastopenq = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue.fastopenq;
<a name="L241" href="source/net/ipv4/tcp_fastopen.c#L241">241</a>         if (!fastopenq || fastopenq-&gt;max_qlen == 0)
<a name="L242" href="source/net/ipv4/tcp_fastopen.c#L242">242</a>                 return <a href="ident?i=false">false</a>;
<a name="L243" href="source/net/ipv4/tcp_fastopen.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/tcp_fastopen.c#L244">244</a>         if (fastopenq-&gt;<a href="ident?i=qlen">qlen</a> &gt;= fastopenq-&gt;max_qlen) {
<a name="L245" href="source/net/ipv4/tcp_fastopen.c#L245">245</a>                 struct <a href="ident?i=request_sock">request_sock</a> *req1;
<a name="L246" href="source/net/ipv4/tcp_fastopen.c#L246">246</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L247" href="source/net/ipv4/tcp_fastopen.c#L247">247</a>                 req1 = fastopenq-&gt;rskq_rst_head;
<a name="L248" href="source/net/ipv4/tcp_fastopen.c#L248">248</a>                 if (!req1 || <a href="ident?i=time_after">time_after</a>(req1-&gt;rsk_timer.expires, <a href="ident?i=jiffies">jiffies</a>)) {
<a name="L249" href="source/net/ipv4/tcp_fastopen.c#L249">249</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L250" href="source/net/ipv4/tcp_fastopen.c#L250">250</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L251" href="source/net/ipv4/tcp_fastopen.c#L251">251</a>                                          LINUX_MIB_TCPFASTOPENLISTENOVERFLOW);
<a name="L252" href="source/net/ipv4/tcp_fastopen.c#L252">252</a>                         return <a href="ident?i=false">false</a>;
<a name="L253" href="source/net/ipv4/tcp_fastopen.c#L253">253</a>                 }
<a name="L254" href="source/net/ipv4/tcp_fastopen.c#L254">254</a>                 fastopenq-&gt;rskq_rst_head = req1-&gt;dl_next;
<a name="L255" href="source/net/ipv4/tcp_fastopen.c#L255">255</a>                 fastopenq-&gt;<a href="ident?i=qlen">qlen</a>--;
<a name="L256" href="source/net/ipv4/tcp_fastopen.c#L256">256</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L257" href="source/net/ipv4/tcp_fastopen.c#L257">257</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(req1);
<a name="L258" href="source/net/ipv4/tcp_fastopen.c#L258">258</a>         }
<a name="L259" href="source/net/ipv4/tcp_fastopen.c#L259">259</a>         return <a href="ident?i=true">true</a>;
<a name="L260" href="source/net/ipv4/tcp_fastopen.c#L260">260</a> }
<a name="L261" href="source/net/ipv4/tcp_fastopen.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/tcp_fastopen.c#L262">262</a> <b><i>/* Returns true if we should perform Fast Open on the SYN. The cookie (foc)</i></b>
<a name="L263" href="source/net/ipv4/tcp_fastopen.c#L263">263</a> <b><i> * may be updated and return the client in the SYN-ACK later. E.g., Fast Open</i></b>
<a name="L264" href="source/net/ipv4/tcp_fastopen.c#L264">264</a> <b><i> * cookie request (foc-&gt;len == 0).</i></b>
<a name="L265" href="source/net/ipv4/tcp_fastopen.c#L265">265</a> <b><i> */</i></b>
<a name="L266" href="source/net/ipv4/tcp_fastopen.c#L266">266</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_try_fastopen">tcp_try_fastopen</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L267" href="source/net/ipv4/tcp_fastopen.c#L267">267</a>                       struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L268" href="source/net/ipv4/tcp_fastopen.c#L268">268</a>                       struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc,
<a name="L269" href="source/net/ipv4/tcp_fastopen.c#L269">269</a>                       struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L270" href="source/net/ipv4/tcp_fastopen.c#L270">270</a> {
<a name="L271" href="source/net/ipv4/tcp_fastopen.c#L271">271</a>         struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> valid_foc = { .<a href="ident?i=len">len</a> = -1 };
<a name="L272" href="source/net/ipv4/tcp_fastopen.c#L272">272</a>         <a href="ident?i=bool">bool</a> syn_data = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L273" href="source/net/ipv4/tcp_fastopen.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/tcp_fastopen.c#L274">274</a>         if (foc-&gt;<a href="ident?i=len">len</a> == 0) <b><i>/* Client requests a cookie */</i></b>
<a name="L275" href="source/net/ipv4/tcp_fastopen.c#L275">275</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPFASTOPENCOOKIEREQD);
<a name="L276" href="source/net/ipv4/tcp_fastopen.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/tcp_fastopen.c#L277">277</a>         if (!((<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp; <a href="ident?i=TFO_SERVER_ENABLE">TFO_SERVER_ENABLE</a>) &amp;&amp;
<a name="L278" href="source/net/ipv4/tcp_fastopen.c#L278">278</a>               (syn_data || foc-&gt;<a href="ident?i=len">len</a> &gt;= 0) &amp;&amp;
<a name="L279" href="source/net/ipv4/tcp_fastopen.c#L279">279</a>               <a href="ident?i=tcp_fastopen_queue_check">tcp_fastopen_queue_check</a>(sk))) {
<a name="L280" href="source/net/ipv4/tcp_fastopen.c#L280">280</a>                 foc-&gt;<a href="ident?i=len">len</a> = -1;
<a name="L281" href="source/net/ipv4/tcp_fastopen.c#L281">281</a>                 return <a href="ident?i=false">false</a>;
<a name="L282" href="source/net/ipv4/tcp_fastopen.c#L282">282</a>         }
<a name="L283" href="source/net/ipv4/tcp_fastopen.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/tcp_fastopen.c#L284">284</a>         if (syn_data &amp;&amp; (<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp; <a href="ident?i=TFO_SERVER_COOKIE_NOT_REQD">TFO_SERVER_COOKIE_NOT_REQD</a>))
<a name="L285" href="source/net/ipv4/tcp_fastopen.c#L285">285</a>                 goto fastopen;
<a name="L286" href="source/net/ipv4/tcp_fastopen.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/tcp_fastopen.c#L287">287</a>         if (foc-&gt;<a href="ident?i=len">len</a> &gt;= 0 &amp;&amp;  <b><i>/* Client presents or requests a cookie */</i></b>
<a name="L288" href="source/net/ipv4/tcp_fastopen.c#L288">288</a>             <a href="ident?i=tcp_fastopen_cookie_gen">tcp_fastopen_cookie_gen</a>(<a href="ident?i=req">req</a>, <a href="ident?i=skb">skb</a>, &amp;valid_foc) &amp;&amp;
<a name="L289" href="source/net/ipv4/tcp_fastopen.c#L289">289</a>             foc-&gt;<a href="ident?i=len">len</a> == <a href="ident?i=TCP_FASTOPEN_COOKIE_SIZE">TCP_FASTOPEN_COOKIE_SIZE</a> &amp;&amp;
<a name="L290" href="source/net/ipv4/tcp_fastopen.c#L290">290</a>             foc-&gt;<a href="ident?i=len">len</a> == valid_foc.<a href="ident?i=len">len</a> &amp;&amp;
<a name="L291" href="source/net/ipv4/tcp_fastopen.c#L291">291</a>             !<a href="ident?i=memcmp">memcmp</a>(foc-&gt;<a href="ident?i=val">val</a>, valid_foc.<a href="ident?i=val">val</a>, foc-&gt;<a href="ident?i=len">len</a>)) {
<a name="L292" href="source/net/ipv4/tcp_fastopen.c#L292">292</a>                 <b><i>/* Cookie is valid. Create a (full) child socket to accept</i></b>
<a name="L293" href="source/net/ipv4/tcp_fastopen.c#L293">293</a> <b><i>                 * the data in SYN before returning a SYN-ACK to ack the</i></b>
<a name="L294" href="source/net/ipv4/tcp_fastopen.c#L294">294</a> <b><i>                 * data. If we fail to create the socket, fall back and</i></b>
<a name="L295" href="source/net/ipv4/tcp_fastopen.c#L295">295</a> <b><i>                 * ack the ISN only but includes the same cookie.</i></b>
<a name="L296" href="source/net/ipv4/tcp_fastopen.c#L296">296</a> <b><i>                 *</i></b>
<a name="L297" href="source/net/ipv4/tcp_fastopen.c#L297">297</a> <b><i>                 * Note: Data-less SYN with valid cookie is allowed to send</i></b>
<a name="L298" href="source/net/ipv4/tcp_fastopen.c#L298">298</a> <b><i>                 * data in SYN_RECV state.</i></b>
<a name="L299" href="source/net/ipv4/tcp_fastopen.c#L299">299</a> <b><i>                 */</i></b>
<a name="L300" href="source/net/ipv4/tcp_fastopen.c#L300">300</a> fastopen:
<a name="L301" href="source/net/ipv4/tcp_fastopen.c#L301">301</a>                 if (<a href="ident?i=tcp_fastopen_create_child">tcp_fastopen_create_child</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=req">req</a>)) {
<a name="L302" href="source/net/ipv4/tcp_fastopen.c#L302">302</a>                         foc-&gt;<a href="ident?i=len">len</a> = -1;
<a name="L303" href="source/net/ipv4/tcp_fastopen.c#L303">303</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L304" href="source/net/ipv4/tcp_fastopen.c#L304">304</a>                                          LINUX_MIB_TCPFASTOPENPASSIVE);
<a name="L305" href="source/net/ipv4/tcp_fastopen.c#L305">305</a>                         return <a href="ident?i=true">true</a>;
<a name="L306" href="source/net/ipv4/tcp_fastopen.c#L306">306</a>                 }
<a name="L307" href="source/net/ipv4/tcp_fastopen.c#L307">307</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPFASTOPENPASSIVEFAIL);
<a name="L308" href="source/net/ipv4/tcp_fastopen.c#L308">308</a>         } else if (foc-&gt;<a href="ident?i=len">len</a> &gt; 0) <b><i>/* Client presents an invalid cookie */</i></b>
<a name="L309" href="source/net/ipv4/tcp_fastopen.c#L309">309</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPFASTOPENPASSIVEFAIL);
<a name="L310" href="source/net/ipv4/tcp_fastopen.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/tcp_fastopen.c#L311">311</a>         valid_foc.exp = foc-&gt;exp;
<a name="L312" href="source/net/ipv4/tcp_fastopen.c#L312">312</a>         *foc = valid_foc;
<a name="L313" href="source/net/ipv4/tcp_fastopen.c#L313">313</a>         return <a href="ident?i=false">false</a>;
<a name="L314" href="source/net/ipv4/tcp_fastopen.c#L314">314</a> }
<a name="L315" href="source/net/ipv4/tcp_fastopen.c#L315">315</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_try_fastopen">tcp_try_fastopen</a>);
<a name="L316" href="source/net/ipv4/tcp_fastopen.c#L316">316</a> </pre></div><p>
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
