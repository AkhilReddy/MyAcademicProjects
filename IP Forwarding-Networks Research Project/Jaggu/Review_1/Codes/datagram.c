<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/datagram.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/datagram.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/datagram.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/datagram.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/datagram.c">datagram.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/datagram.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/datagram.c#L2">2</a> <b><i> *      common UDP/RAW code</i></b>
  <a name="L3" href="source/net/ipv4/datagram.c#L3">3</a> <b><i> *      Linux INET implementation</i></b>
  <a name="L4" href="source/net/ipv4/datagram.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/datagram.c#L5">5</a> <b><i> * Authors:</i></b>
  <a name="L6" href="source/net/ipv4/datagram.c#L6">6</a> <b><i> *      Hideaki YOSHIFUJI &lt;yoshfuji@linux-ipv6.org&gt;</i></b>
  <a name="L7" href="source/net/ipv4/datagram.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/datagram.c#L8">8</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L9" href="source/net/ipv4/datagram.c#L9">9</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L10" href="source/net/ipv4/datagram.c#L10">10</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L11" href="source/net/ipv4/datagram.c#L11">11</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L12" href="source/net/ipv4/datagram.c#L12">12</a> <b><i> */</i></b>
 <a name="L13" href="source/net/ipv4/datagram.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/datagram.c#L14">14</a> #include &lt;linux/types.h&gt;
 <a name="L15" href="source/net/ipv4/datagram.c#L15">15</a> #include &lt;linux/module.h&gt;
 <a name="L16" href="source/net/ipv4/datagram.c#L16">16</a> #include &lt;linux/ip.h&gt;
 <a name="L17" href="source/net/ipv4/datagram.c#L17">17</a> #include &lt;linux/in.h&gt;
 <a name="L18" href="source/net/ipv4/datagram.c#L18">18</a> #include &lt;net/ip.h&gt;
 <a name="L19" href="source/net/ipv4/datagram.c#L19">19</a> #include &lt;net/sock.h&gt;
 <a name="L20" href="source/net/ipv4/datagram.c#L20">20</a> #include &lt;net/route.h&gt;
 <a name="L21" href="source/net/ipv4/datagram.c#L21">21</a> #include &lt;net/tcp_states.h&gt;
 <a name="L22" href="source/net/ipv4/datagram.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/datagram.c#L23">23</a> int <a href="ident?i=ip4_datagram_connect">ip4_datagram_connect</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>, int addr_len)
 <a name="L24" href="source/net/ipv4/datagram.c#L24">24</a> {
 <a name="L25" href="source/net/ipv4/datagram.c#L25">25</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
 <a name="L26" href="source/net/ipv4/datagram.c#L26">26</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *usin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) <a href="ident?i=uaddr">uaddr</a>;
 <a name="L27" href="source/net/ipv4/datagram.c#L27">27</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
 <a name="L28" href="source/net/ipv4/datagram.c#L28">28</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
 <a name="L29" href="source/net/ipv4/datagram.c#L29">29</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>;
 <a name="L30" href="source/net/ipv4/datagram.c#L30">30</a>         int oif;
 <a name="L31" href="source/net/ipv4/datagram.c#L31">31</a>         int <a href="ident?i=err">err</a>;
 <a name="L32" href="source/net/ipv4/datagram.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/datagram.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/datagram.c#L34">34</a>         if (addr_len &lt; sizeof(*usin))
 <a name="L35" href="source/net/ipv4/datagram.c#L35">35</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L36" href="source/net/ipv4/datagram.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/datagram.c#L37">37</a>         if (usin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
 <a name="L38" href="source/net/ipv4/datagram.c#L38">38</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
 <a name="L39" href="source/net/ipv4/datagram.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/datagram.c#L40">40</a>         <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
 <a name="L41" href="source/net/ipv4/datagram.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/datagram.c#L42">42</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
 <a name="L43" href="source/net/ipv4/datagram.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/datagram.c#L44">44</a>         oif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
 <a name="L45" href="source/net/ipv4/datagram.c#L45">45</a>         <a href="ident?i=saddr">saddr</a> = inet-&gt;inet_saddr;
 <a name="L46" href="source/net/ipv4/datagram.c#L46">46</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(usin-&gt;sin_addr.s_addr)) {
 <a name="L47" href="source/net/ipv4/datagram.c#L47">47</a>                 if (!oif)
 <a name="L48" href="source/net/ipv4/datagram.c#L48">48</a>                         oif = inet-&gt;mc_index;
 <a name="L49" href="source/net/ipv4/datagram.c#L49">49</a>                 if (!<a href="ident?i=saddr">saddr</a>)
 <a name="L50" href="source/net/ipv4/datagram.c#L50">50</a>                         <a href="ident?i=saddr">saddr</a> = inet-&gt;mc_addr;
 <a name="L51" href="source/net/ipv4/datagram.c#L51">51</a>         }
 <a name="L52" href="source/net/ipv4/datagram.c#L52">52</a>         fl4 = &amp;inet-&gt;cork.fl.u.ip4;
 <a name="L53" href="source/net/ipv4/datagram.c#L53">53</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_connect">ip_route_connect</a>(fl4, usin-&gt;sin_addr.s_addr, <a href="ident?i=saddr">saddr</a>,
 <a name="L54" href="source/net/ipv4/datagram.c#L54">54</a>                               <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), oif,
 <a name="L55" href="source/net/ipv4/datagram.c#L55">55</a>                               sk-&gt;sk_protocol,
 <a name="L56" href="source/net/ipv4/datagram.c#L56">56</a>                               inet-&gt;inet_sport, usin-&gt;sin_port, sk);
 <a name="L57" href="source/net/ipv4/datagram.c#L57">57</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
 <a name="L58" href="source/net/ipv4/datagram.c#L58">58</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
 <a name="L59" href="source/net/ipv4/datagram.c#L59">59</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>)
 <a name="L60" href="source/net/ipv4/datagram.c#L60">60</a>                         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), IPSTATS_MIB_OUTNOROUTES);
 <a name="L61" href="source/net/ipv4/datagram.c#L61">61</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L62" href="source/net/ipv4/datagram.c#L62">62</a>         }
 <a name="L63" href="source/net/ipv4/datagram.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/datagram.c#L64">64</a>         if ((<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>) &amp;&amp; !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_BROADCAST)) {
 <a name="L65" href="source/net/ipv4/datagram.c#L65">65</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
 <a name="L66" href="source/net/ipv4/datagram.c#L66">66</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EACCES">EACCES</a>;
 <a name="L67" href="source/net/ipv4/datagram.c#L67">67</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L68" href="source/net/ipv4/datagram.c#L68">68</a>         }
 <a name="L69" href="source/net/ipv4/datagram.c#L69">69</a>         if (!inet-&gt;inet_saddr)
 <a name="L70" href="source/net/ipv4/datagram.c#L70">70</a>                 inet-&gt;inet_saddr = fl4-&gt;<a href="ident?i=saddr">saddr</a>;  <b><i>/* Update source address */</i></b>
 <a name="L71" href="source/net/ipv4/datagram.c#L71">71</a>         if (!inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>) {
 <a name="L72" href="source/net/ipv4/datagram.c#L72">72</a>                 inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L73" href="source/net/ipv4/datagram.c#L73">73</a>                 if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;rehash)
 <a name="L74" href="source/net/ipv4/datagram.c#L74">74</a>                         sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;rehash(sk);
 <a name="L75" href="source/net/ipv4/datagram.c#L75">75</a>         }
 <a name="L76" href="source/net/ipv4/datagram.c#L76">76</a>         inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> = fl4-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L77" href="source/net/ipv4/datagram.c#L77">77</a>         inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> = usin-&gt;sin_port;
 <a name="L78" href="source/net/ipv4/datagram.c#L78">78</a>         sk-&gt;<a href="ident?i=sk_state">sk_state</a> = TCP_ESTABLISHED;
 <a name="L79" href="source/net/ipv4/datagram.c#L79">79</a>         <a href="ident?i=inet_set_txhash">inet_set_txhash</a>(sk);
 <a name="L80" href="source/net/ipv4/datagram.c#L80">80</a>         inet-&gt;inet_id = <a href="ident?i=jiffies">jiffies</a>;
 <a name="L81" href="source/net/ipv4/datagram.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/datagram.c#L82">82</a>         <a href="ident?i=sk_dst_set">sk_dst_set</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
 <a name="L83" href="source/net/ipv4/datagram.c#L83">83</a>         <a href="ident?i=err">err</a> = 0;
 <a name="L84" href="source/net/ipv4/datagram.c#L84">84</a> <a href="ident?i=out">out</a>:
 <a name="L85" href="source/net/ipv4/datagram.c#L85">85</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
 <a name="L86" href="source/net/ipv4/datagram.c#L86">86</a>         return <a href="ident?i=err">err</a>;
 <a name="L87" href="source/net/ipv4/datagram.c#L87">87</a> }
 <a name="L88" href="source/net/ipv4/datagram.c#L88">88</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip4_datagram_connect">ip4_datagram_connect</a>);
 <a name="L89" href="source/net/ipv4/datagram.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/datagram.c#L90">90</a> <b><i>/* Because UDP xmit path can manipulate sk_dst_cache without holding</i></b>
 <a name="L91" href="source/net/ipv4/datagram.c#L91">91</a> <b><i> * socket lock, we need to use sk_dst_set() here,</i></b>
 <a name="L92" href="source/net/ipv4/datagram.c#L92">92</a> <b><i> * even if we own the socket lock.</i></b>
 <a name="L93" href="source/net/ipv4/datagram.c#L93">93</a> <b><i> */</i></b>
 <a name="L94" href="source/net/ipv4/datagram.c#L94">94</a> void <a href="ident?i=ip4_datagram_release_cb">ip4_datagram_release_cb</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L95" href="source/net/ipv4/datagram.c#L95">95</a> {
 <a name="L96" href="source/net/ipv4/datagram.c#L96">96</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
 <a name="L97" href="source/net/ipv4/datagram.c#L97">97</a>         const struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
 <a name="L98" href="source/net/ipv4/datagram.c#L98">98</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
 <a name="L99" href="source/net/ipv4/datagram.c#L99">99</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L100" href="source/net/ipv4/datagram.c#L100">100</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L101" href="source/net/ipv4/datagram.c#L101">101</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L102" href="source/net/ipv4/datagram.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/datagram.c#L103">103</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L104" href="source/net/ipv4/datagram.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/datagram.c#L105">105</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L106" href="source/net/ipv4/datagram.c#L106">106</a>         if (!<a href="ident?i=dst">dst</a> || !<a href="ident?i=dst">dst</a>-&gt;obsolete || <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=check">check</a>(<a href="ident?i=dst">dst</a>, 0)) {
<a name="L107" href="source/net/ipv4/datagram.c#L107">107</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L108" href="source/net/ipv4/datagram.c#L108">108</a>                 return;
<a name="L109" href="source/net/ipv4/datagram.c#L109">109</a>         }
<a name="L110" href="source/net/ipv4/datagram.c#L110">110</a>         inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L111" href="source/net/ipv4/datagram.c#L111">111</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L112" href="source/net/ipv4/datagram.c#L112">112</a>                 <a href="ident?i=daddr">daddr</a> = inet_opt-&gt;opt.faddr;
<a name="L113" href="source/net/ipv4/datagram.c#L113">113</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4, sk, <a href="ident?i=daddr">daddr</a>,
<a name="L114" href="source/net/ipv4/datagram.c#L114">114</a>                                    inet-&gt;inet_saddr, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>,
<a name="L115" href="source/net/ipv4/datagram.c#L115">115</a>                                    inet-&gt;inet_sport, sk-&gt;sk_protocol,
<a name="L116" href="source/net/ipv4/datagram.c#L116">116</a>                                    <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L117" href="source/net/ipv4/datagram.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/datagram.c#L118">118</a>         <a href="ident?i=dst">dst</a> = !<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>) ? &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a> : <a href="ident?i=NULL">NULL</a>;
<a name="L119" href="source/net/ipv4/datagram.c#L119">119</a>         <a href="ident?i=sk_dst_set">sk_dst_set</a>(sk, <a href="ident?i=dst">dst</a>);
<a name="L120" href="source/net/ipv4/datagram.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/datagram.c#L121">121</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L122" href="source/net/ipv4/datagram.c#L122">122</a> }
<a name="L123" href="source/net/ipv4/datagram.c#L123">123</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip4_datagram_release_cb">ip4_datagram_release_cb</a>);
<a name="L124" href="source/net/ipv4/datagram.c#L124">124</a> </pre></div><p>
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
