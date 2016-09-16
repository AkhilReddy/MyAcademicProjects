<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/udp_tunnel.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/udp_tunnel.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/udp_tunnel.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/udp_tunnel.c">udp_tunnel.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/udp_tunnel.c#L1">1</a> #include &lt;linux/module.h&gt;
  <a name="L2" href="source/net/ipv4/udp_tunnel.c#L2">2</a> #include &lt;linux/errno.h&gt;
  <a name="L3" href="source/net/ipv4/udp_tunnel.c#L3">3</a> #include &lt;linux/socket.h&gt;
  <a name="L4" href="source/net/ipv4/udp_tunnel.c#L4">4</a> #include &lt;linux/udp.h&gt;
  <a name="L5" href="source/net/ipv4/udp_tunnel.c#L5">5</a> #include &lt;linux/types.h&gt;
  <a name="L6" href="source/net/ipv4/udp_tunnel.c#L6">6</a> #include &lt;linux/kernel.h&gt;
  <a name="L7" href="source/net/ipv4/udp_tunnel.c#L7">7</a> #include &lt;net/udp.h&gt;
  <a name="L8" href="source/net/ipv4/udp_tunnel.c#L8">8</a> #include &lt;net/udp_tunnel.h&gt;
  <a name="L9" href="source/net/ipv4/udp_tunnel.c#L9">9</a> #include &lt;net/net_namespace.h&gt;
 <a name="L10" href="source/net/ipv4/udp_tunnel.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/udp_tunnel.c#L11">11</a> int <a href="ident?i=udp_sock_create4">udp_sock_create4</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=udp_port_cfg">udp_port_cfg</a> *<a href="ident?i=cfg">cfg</a>,
 <a name="L12" href="source/net/ipv4/udp_tunnel.c#L12">12</a>                      struct <a href="ident?i=socket">socket</a> **sockp)
 <a name="L13" href="source/net/ipv4/udp_tunnel.c#L13">13</a> {
 <a name="L14" href="source/net/ipv4/udp_tunnel.c#L14">14</a>         int <a href="ident?i=err">err</a>;
 <a name="L15" href="source/net/ipv4/udp_tunnel.c#L15">15</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a> = <a href="ident?i=NULL">NULL</a>;
 <a name="L16" href="source/net/ipv4/udp_tunnel.c#L16">16</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> udp_addr;
 <a name="L17" href="source/net/ipv4/udp_tunnel.c#L17">17</a> 
 <a name="L18" href="source/net/ipv4/udp_tunnel.c#L18">18</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sock_create_kern">sock_create_kern</a>(<a href="ident?i=AF_INET">AF_INET</a>, SOCK_DGRAM, 0, &amp;<a href="ident?i=sock">sock</a>);
 <a name="L19" href="source/net/ipv4/udp_tunnel.c#L19">19</a>         if (<a href="ident?i=err">err</a> &lt; 0)
 <a name="L20" href="source/net/ipv4/udp_tunnel.c#L20">20</a>                 goto <a href="ident?i=error">error</a>;
 <a name="L21" href="source/net/ipv4/udp_tunnel.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/udp_tunnel.c#L22">22</a>         <a href="ident?i=sk_change_net">sk_change_net</a>(<a href="ident?i=sock">sock</a>-&gt;sk, <a href="ident?i=net">net</a>);
 <a name="L23" href="source/net/ipv4/udp_tunnel.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/udp_tunnel.c#L24">24</a>         udp_addr.sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L25" href="source/net/ipv4/udp_tunnel.c#L25">25</a>         udp_addr.sin_addr = <a href="ident?i=cfg">cfg</a>-&gt;local_ip;
 <a name="L26" href="source/net/ipv4/udp_tunnel.c#L26">26</a>         udp_addr.sin_port = <a href="ident?i=cfg">cfg</a>-&gt;local_udp_port;
 <a name="L27" href="source/net/ipv4/udp_tunnel.c#L27">27</a>         <a href="ident?i=err">err</a> = <a href="ident?i=kernel_bind">kernel_bind</a>(<a href="ident?i=sock">sock</a>, (struct <a href="ident?i=sockaddr">sockaddr</a> *)&amp;udp_addr,
 <a name="L28" href="source/net/ipv4/udp_tunnel.c#L28">28</a>                           sizeof(udp_addr));
 <a name="L29" href="source/net/ipv4/udp_tunnel.c#L29">29</a>         if (<a href="ident?i=err">err</a> &lt; 0)
 <a name="L30" href="source/net/ipv4/udp_tunnel.c#L30">30</a>                 goto <a href="ident?i=error">error</a>;
 <a name="L31" href="source/net/ipv4/udp_tunnel.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/udp_tunnel.c#L32">32</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;peer_udp_port) {
 <a name="L33" href="source/net/ipv4/udp_tunnel.c#L33">33</a>                 udp_addr.sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L34" href="source/net/ipv4/udp_tunnel.c#L34">34</a>                 udp_addr.sin_addr = <a href="ident?i=cfg">cfg</a>-&gt;peer_ip;
 <a name="L35" href="source/net/ipv4/udp_tunnel.c#L35">35</a>                 udp_addr.sin_port = <a href="ident?i=cfg">cfg</a>-&gt;peer_udp_port;
 <a name="L36" href="source/net/ipv4/udp_tunnel.c#L36">36</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=kernel_connect">kernel_connect</a>(<a href="ident?i=sock">sock</a>, (struct <a href="ident?i=sockaddr">sockaddr</a> *)&amp;udp_addr,
 <a name="L37" href="source/net/ipv4/udp_tunnel.c#L37">37</a>                                      sizeof(udp_addr), 0);
 <a name="L38" href="source/net/ipv4/udp_tunnel.c#L38">38</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
 <a name="L39" href="source/net/ipv4/udp_tunnel.c#L39">39</a>                         goto <a href="ident?i=error">error</a>;
 <a name="L40" href="source/net/ipv4/udp_tunnel.c#L40">40</a>         }
 <a name="L41" href="source/net/ipv4/udp_tunnel.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/udp_tunnel.c#L42">42</a>         <a href="ident?i=sock">sock</a>-&gt;sk-&gt;sk_no_check_tx = !<a href="ident?i=cfg">cfg</a>-&gt;use_udp_checksums;
 <a name="L43" href="source/net/ipv4/udp_tunnel.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/udp_tunnel.c#L44">44</a>         *sockp = <a href="ident?i=sock">sock</a>;
 <a name="L45" href="source/net/ipv4/udp_tunnel.c#L45">45</a>         return 0;
 <a name="L46" href="source/net/ipv4/udp_tunnel.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/udp_tunnel.c#L47">47</a> <a href="ident?i=error">error</a>:
 <a name="L48" href="source/net/ipv4/udp_tunnel.c#L48">48</a>         if (<a href="ident?i=sock">sock</a>) {
 <a name="L49" href="source/net/ipv4/udp_tunnel.c#L49">49</a>                 <a href="ident?i=kernel_sock_shutdown">kernel_sock_shutdown</a>(<a href="ident?i=sock">sock</a>, <a href="ident?i=SHUT_RDWR">SHUT_RDWR</a>);
 <a name="L50" href="source/net/ipv4/udp_tunnel.c#L50">50</a>                 <a href="ident?i=sk_release_kernel">sk_release_kernel</a>(<a href="ident?i=sock">sock</a>-&gt;sk);
 <a name="L51" href="source/net/ipv4/udp_tunnel.c#L51">51</a>         }
 <a name="L52" href="source/net/ipv4/udp_tunnel.c#L52">52</a>         *sockp = <a href="ident?i=NULL">NULL</a>;
 <a name="L53" href="source/net/ipv4/udp_tunnel.c#L53">53</a>         return <a href="ident?i=err">err</a>;
 <a name="L54" href="source/net/ipv4/udp_tunnel.c#L54">54</a> }
 <a name="L55" href="source/net/ipv4/udp_tunnel.c#L55">55</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_sock_create4">udp_sock_create4</a>);
 <a name="L56" href="source/net/ipv4/udp_tunnel.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/udp_tunnel.c#L57">57</a> void <a href="ident?i=setup_udp_tunnel_sock">setup_udp_tunnel_sock</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>,
 <a name="L58" href="source/net/ipv4/udp_tunnel.c#L58">58</a>                            struct <a href="ident?i=udp_tunnel_sock_cfg">udp_tunnel_sock_cfg</a> *<a href="ident?i=cfg">cfg</a>)
 <a name="L59" href="source/net/ipv4/udp_tunnel.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/udp_tunnel.c#L60">60</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
 <a name="L61" href="source/net/ipv4/udp_tunnel.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/udp_tunnel.c#L62">62</a>         <b><i>/* Disable multicast loopback */</i></b>
 <a name="L63" href="source/net/ipv4/udp_tunnel.c#L63">63</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;mc_loop = 0;
 <a name="L64" href="source/net/ipv4/udp_tunnel.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/udp_tunnel.c#L65">65</a>         <b><i>/* Enable CHECKSUM_UNNECESSARY to CHECKSUM_COMPLETE conversion */</i></b>
 <a name="L66" href="source/net/ipv4/udp_tunnel.c#L66">66</a>         <a href="ident?i=inet_inc_convert_csum">inet_inc_convert_csum</a>(sk);
 <a name="L67" href="source/net/ipv4/udp_tunnel.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/udp_tunnel.c#L68">68</a>         <a href="ident?i=rcu_assign_sk_user_data">rcu_assign_sk_user_data</a>(sk, <a href="ident?i=cfg">cfg</a>-&gt;sk_user_data);
 <a name="L69" href="source/net/ipv4/udp_tunnel.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/udp_tunnel.c#L70">70</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;encap_type = <a href="ident?i=cfg">cfg</a>-&gt;encap_type;
 <a name="L71" href="source/net/ipv4/udp_tunnel.c#L71">71</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;encap_rcv = <a href="ident?i=cfg">cfg</a>-&gt;encap_rcv;
 <a name="L72" href="source/net/ipv4/udp_tunnel.c#L72">72</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;encap_destroy = <a href="ident?i=cfg">cfg</a>-&gt;encap_destroy;
 <a name="L73" href="source/net/ipv4/udp_tunnel.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/udp_tunnel.c#L74">74</a>         <a href="ident?i=udp_tunnel_encap_enable">udp_tunnel_encap_enable</a>(<a href="ident?i=sock">sock</a>);
 <a name="L75" href="source/net/ipv4/udp_tunnel.c#L75">75</a> }
 <a name="L76" href="source/net/ipv4/udp_tunnel.c#L76">76</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=setup_udp_tunnel_sock">setup_udp_tunnel_sock</a>);
 <a name="L77" href="source/net/ipv4/udp_tunnel.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/udp_tunnel.c#L78">78</a> int <a href="ident?i=udp_tunnel_xmit_skb">udp_tunnel_xmit_skb</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L79" href="source/net/ipv4/udp_tunnel.c#L79">79</a>                         <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, <a href="ident?i=__u8">__u8</a> tos, <a href="ident?i=__u8">__u8</a> <a href="ident?i=ttl">ttl</a>,
 <a name="L80" href="source/net/ipv4/udp_tunnel.c#L80">80</a>                         <a href="ident?i=__be16">__be16</a> <a href="ident?i=df">df</a>, <a href="ident?i=__be16">__be16</a> src_port, <a href="ident?i=__be16">__be16</a> dst_port,
 <a name="L81" href="source/net/ipv4/udp_tunnel.c#L81">81</a>                         <a href="ident?i=bool">bool</a> xnet, <a href="ident?i=bool">bool</a> nocheck)
 <a name="L82" href="source/net/ipv4/udp_tunnel.c#L82">82</a> {
 <a name="L83" href="source/net/ipv4/udp_tunnel.c#L83">83</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh;
 <a name="L84" href="source/net/ipv4/udp_tunnel.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/udp_tunnel.c#L85">85</a>         <a href="ident?i=__skb_push">__skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(*uh));
 <a name="L86" href="source/net/ipv4/udp_tunnel.c#L86">86</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L87" href="source/net/ipv4/udp_tunnel.c#L87">87</a>         uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L88" href="source/net/ipv4/udp_tunnel.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/udp_tunnel.c#L89">89</a>         uh-&gt;<a href="ident?i=dest">dest</a> = dst_port;
 <a name="L90" href="source/net/ipv4/udp_tunnel.c#L90">90</a>         uh-&gt;source = src_port;
 <a name="L91" href="source/net/ipv4/udp_tunnel.c#L91">91</a>         uh-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
 <a name="L92" href="source/net/ipv4/udp_tunnel.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/udp_tunnel.c#L93">93</a>         <a href="ident?i=udp_set_csum">udp_set_csum</a>(nocheck, <a href="ident?i=skb">skb</a>, <a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
 <a name="L94" href="source/net/ipv4/udp_tunnel.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/udp_tunnel.c#L95">95</a>         return <a href="ident?i=iptunnel_xmit">iptunnel_xmit</a>(sk, <a href="ident?i=rt">rt</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>,
 <a name="L96" href="source/net/ipv4/udp_tunnel.c#L96">96</a>                              tos, <a href="ident?i=ttl">ttl</a>, <a href="ident?i=df">df</a>, xnet);
 <a name="L97" href="source/net/ipv4/udp_tunnel.c#L97">97</a> }
 <a name="L98" href="source/net/ipv4/udp_tunnel.c#L98">98</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=udp_tunnel_xmit_skb">udp_tunnel_xmit_skb</a>);
 <a name="L99" href="source/net/ipv4/udp_tunnel.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/udp_tunnel.c#L100">100</a> void <a href="ident?i=udp_tunnel_sock_release">udp_tunnel_sock_release</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>)
<a name="L101" href="source/net/ipv4/udp_tunnel.c#L101">101</a> {
<a name="L102" href="source/net/ipv4/udp_tunnel.c#L102">102</a>         <a href="ident?i=rcu_assign_sk_user_data">rcu_assign_sk_user_data</a>(<a href="ident?i=sock">sock</a>-&gt;sk, <a href="ident?i=NULL">NULL</a>);
<a name="L103" href="source/net/ipv4/udp_tunnel.c#L103">103</a>         <a href="ident?i=kernel_sock_shutdown">kernel_sock_shutdown</a>(<a href="ident?i=sock">sock</a>, <a href="ident?i=SHUT_RDWR">SHUT_RDWR</a>);
<a name="L104" href="source/net/ipv4/udp_tunnel.c#L104">104</a>         <a href="ident?i=sk_release_kernel">sk_release_kernel</a>(<a href="ident?i=sock">sock</a>-&gt;sk);
<a name="L105" href="source/net/ipv4/udp_tunnel.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/udp_tunnel.c#L106">106</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=udp_tunnel_sock_release">udp_tunnel_sock_release</a>);
<a name="L107" href="source/net/ipv4/udp_tunnel.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/udp_tunnel.c#L108">108</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L109" href="source/net/ipv4/udp_tunnel.c#L109">109</a> </pre></div><p>
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
