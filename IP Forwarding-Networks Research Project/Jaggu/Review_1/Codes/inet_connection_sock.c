<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inet_connection_sock.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inet_connection_sock.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inet_connection_sock.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inet_connection_sock.c">inet_connection_sock.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inet_connection_sock.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inet_connection_sock.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/inet_connection_sock.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/inet_connection_sock.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/inet_connection_sock.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/inet_connection_sock.c#L6">6</a> <b><i> *              Support for INET connection oriented protocols.</i></b>
  <a name="L7" href="source/net/ipv4/inet_connection_sock.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/inet_connection_sock.c#L8">8</a> <b><i> * Authors:     See the TCP sources</i></b>
  <a name="L9" href="source/net/ipv4/inet_connection_sock.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/inet_connection_sock.c#L10">10</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L11" href="source/net/ipv4/inet_connection_sock.c#L11">11</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L12" href="source/net/ipv4/inet_connection_sock.c#L12">12</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L13" href="source/net/ipv4/inet_connection_sock.c#L13">13</a> <b><i> *              2 of the License, or(at your option) any later version.</i></b>
 <a name="L14" href="source/net/ipv4/inet_connection_sock.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/inet_connection_sock.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/inet_connection_sock.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/inet_connection_sock.c#L17">17</a> #include &lt;linux/jhash.h&gt;
 <a name="L18" href="source/net/ipv4/inet_connection_sock.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/inet_connection_sock.c#L19">19</a> #include &lt;net/inet_connection_sock.h&gt;
 <a name="L20" href="source/net/ipv4/inet_connection_sock.c#L20">20</a> #include &lt;net/inet_hashtables.h&gt;
 <a name="L21" href="source/net/ipv4/inet_connection_sock.c#L21">21</a> #include &lt;net/inet_timewait_sock.h&gt;
 <a name="L22" href="source/net/ipv4/inet_connection_sock.c#L22">22</a> #include &lt;net/ip.h&gt;
 <a name="L23" href="source/net/ipv4/inet_connection_sock.c#L23">23</a> #include &lt;net/route.h&gt;
 <a name="L24" href="source/net/ipv4/inet_connection_sock.c#L24">24</a> #include &lt;net/tcp_states.h&gt;
 <a name="L25" href="source/net/ipv4/inet_connection_sock.c#L25">25</a> #include &lt;net/xfrm.h&gt;
 <a name="L26" href="source/net/ipv4/inet_connection_sock.c#L26">26</a> #include &lt;net/tcp.h&gt;
 <a name="L27" href="source/net/ipv4/inet_connection_sock.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/inet_connection_sock.c#L28">28</a> #ifdef <a href="ident?i=INET_CSK_DEBUG">INET_CSK_DEBUG</a>
 <a name="L29" href="source/net/ipv4/inet_connection_sock.c#L29">29</a> const char <a href="ident?i=inet_csk_timer_bug_msg">inet_csk_timer_bug_msg</a>[] = <i>"inet_csk BUG: unknown timer value\n"</i>;
 <a name="L30" href="source/net/ipv4/inet_connection_sock.c#L30">30</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_timer_bug_msg">inet_csk_timer_bug_msg</a>);
 <a name="L31" href="source/net/ipv4/inet_connection_sock.c#L31">31</a> #endif
 <a name="L32" href="source/net/ipv4/inet_connection_sock.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/inet_connection_sock.c#L33">33</a> void <a href="ident?i=inet_get_local_port_range">inet_get_local_port_range</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int *low, int *<a href="ident?i=high">high</a>)
 <a name="L34" href="source/net/ipv4/inet_connection_sock.c#L34">34</a> {
 <a name="L35" href="source/net/ipv4/inet_connection_sock.c#L35">35</a>         unsigned int <a href="ident?i=seq">seq</a>;
 <a name="L36" href="source/net/ipv4/inet_connection_sock.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/inet_connection_sock.c#L37">37</a>         do {
 <a name="L38" href="source/net/ipv4/inet_connection_sock.c#L38">38</a>                 <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
 <a name="L39" href="source/net/ipv4/inet_connection_sock.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/inet_connection_sock.c#L40">40</a>                 *low = <a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=range">range</a>[0];
 <a name="L41" href="source/net/ipv4/inet_connection_sock.c#L41">41</a>                 *<a href="ident?i=high">high</a> = <a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=range">range</a>[1];
 <a name="L42" href="source/net/ipv4/inet_connection_sock.c#L42">42</a>         } while (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>, <a href="ident?i=seq">seq</a>));
 <a name="L43" href="source/net/ipv4/inet_connection_sock.c#L43">43</a> }
 <a name="L44" href="source/net/ipv4/inet_connection_sock.c#L44">44</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_get_local_port_range">inet_get_local_port_range</a>);
 <a name="L45" href="source/net/ipv4/inet_connection_sock.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/inet_connection_sock.c#L46">46</a> int <a href="ident?i=inet_csk_bind_conflict">inet_csk_bind_conflict</a>(const struct <a href="ident?i=sock">sock</a> *sk,
 <a name="L47" href="source/net/ipv4/inet_connection_sock.c#L47">47</a>                            const struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>, <a href="ident?i=bool">bool</a> <a href="ident?i=relax">relax</a>)
 <a name="L48" href="source/net/ipv4/inet_connection_sock.c#L48">48</a> {
 <a name="L49" href="source/net/ipv4/inet_connection_sock.c#L49">49</a>         struct <a href="ident?i=sock">sock</a> *sk2;
 <a name="L50" href="source/net/ipv4/inet_connection_sock.c#L50">50</a>         int reuse = sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a>;
 <a name="L51" href="source/net/ipv4/inet_connection_sock.c#L51">51</a>         int reuseport = sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a>;
 <a name="L52" href="source/net/ipv4/inet_connection_sock.c#L52">52</a>         <a href="ident?i=kuid_t">kuid_t</a> <a href="ident?i=uid">uid</a> = <a href="ident?i=sock_i_uid">sock_i_uid</a>((struct <a href="ident?i=sock">sock</a> *)sk);
 <a name="L53" href="source/net/ipv4/inet_connection_sock.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/inet_connection_sock.c#L54">54</a>         <b><i>/*</i></b>
 <a name="L55" href="source/net/ipv4/inet_connection_sock.c#L55">55</a> <b><i>         * Unlike other sk lookup places we do not check</i></b>
 <a name="L56" href="source/net/ipv4/inet_connection_sock.c#L56">56</a> <b><i>         * for sk_net here, since _all_ the socks listed</i></b>
 <a name="L57" href="source/net/ipv4/inet_connection_sock.c#L57">57</a> <b><i>         * in tb-&gt;owners list belong to the same net - the</i></b>
 <a name="L58" href="source/net/ipv4/inet_connection_sock.c#L58">58</a> <b><i>         * one this bucket belongs to.</i></b>
 <a name="L59" href="source/net/ipv4/inet_connection_sock.c#L59">59</a> <b><i>         */</i></b>
 <a name="L60" href="source/net/ipv4/inet_connection_sock.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/inet_connection_sock.c#L61">61</a>         <a href="ident?i=sk_for_each_bound">sk_for_each_bound</a>(sk2, &amp;<a href="ident?i=tb">tb</a>-&gt;owners) {
 <a name="L62" href="source/net/ipv4/inet_connection_sock.c#L62">62</a>                 if (sk != sk2 &amp;&amp;
 <a name="L63" href="source/net/ipv4/inet_connection_sock.c#L63">63</a>                     !<a href="ident?i=inet_v6_ipv6only">inet_v6_ipv6only</a>(sk2) &amp;&amp;
 <a name="L64" href="source/net/ipv4/inet_connection_sock.c#L64">64</a>                     (!sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> ||
 <a name="L65" href="source/net/ipv4/inet_connection_sock.c#L65">65</a>                      !sk2-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> ||
 <a name="L66" href="source/net/ipv4/inet_connection_sock.c#L66">66</a>                      sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> == sk2-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>)) {
 <a name="L67" href="source/net/ipv4/inet_connection_sock.c#L67">67</a>                         if ((!reuse || !sk2-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> ||
 <a name="L68" href="source/net/ipv4/inet_connection_sock.c#L68">68</a>                             sk2-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) &amp;&amp;
 <a name="L69" href="source/net/ipv4/inet_connection_sock.c#L69">69</a>                             (!reuseport || !sk2-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> ||
 <a name="L70" href="source/net/ipv4/inet_connection_sock.c#L70">70</a>                             (sk2-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_TIME_WAIT &amp;&amp;
 <a name="L71" href="source/net/ipv4/inet_connection_sock.c#L71">71</a>                              !<a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=uid">uid</a>, <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk2))))) {
 <a name="L72" href="source/net/ipv4/inet_connection_sock.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/inet_connection_sock.c#L73">73</a>                                 if (!sk2-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a> || !sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a> ||
 <a name="L74" href="source/net/ipv4/inet_connection_sock.c#L74">74</a>                                     sk2-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a> == sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a>)
 <a name="L75" href="source/net/ipv4/inet_connection_sock.c#L75">75</a>                                         break;
 <a name="L76" href="source/net/ipv4/inet_connection_sock.c#L76">76</a>                         }
 <a name="L77" href="source/net/ipv4/inet_connection_sock.c#L77">77</a>                         if (!<a href="ident?i=relax">relax</a> &amp;&amp; reuse &amp;&amp; sk2-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> &amp;&amp;
 <a name="L78" href="source/net/ipv4/inet_connection_sock.c#L78">78</a>                             sk2-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN) {
 <a name="L79" href="source/net/ipv4/inet_connection_sock.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/inet_connection_sock.c#L80">80</a>                                 if (!sk2-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a> || !sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a> ||
 <a name="L81" href="source/net/ipv4/inet_connection_sock.c#L81">81</a>                                     sk2-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a> == sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a>)
 <a name="L82" href="source/net/ipv4/inet_connection_sock.c#L82">82</a>                                         break;
 <a name="L83" href="source/net/ipv4/inet_connection_sock.c#L83">83</a>                         }
 <a name="L84" href="source/net/ipv4/inet_connection_sock.c#L84">84</a>                 }
 <a name="L85" href="source/net/ipv4/inet_connection_sock.c#L85">85</a>         }
 <a name="L86" href="source/net/ipv4/inet_connection_sock.c#L86">86</a>         return sk2 != <a href="ident?i=NULL">NULL</a>;
 <a name="L87" href="source/net/ipv4/inet_connection_sock.c#L87">87</a> }
 <a name="L88" href="source/net/ipv4/inet_connection_sock.c#L88">88</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_bind_conflict">inet_csk_bind_conflict</a>);
 <a name="L89" href="source/net/ipv4/inet_connection_sock.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/inet_connection_sock.c#L90">90</a> <b><i>/* Obtain a reference to a local port for the given sock,</i></b>
 <a name="L91" href="source/net/ipv4/inet_connection_sock.c#L91">91</a> <b><i> * if snum is zero it means select any available local port.</i></b>
 <a name="L92" href="source/net/ipv4/inet_connection_sock.c#L92">92</a> <b><i> */</i></b>
 <a name="L93" href="source/net/ipv4/inet_connection_sock.c#L93">93</a> int <a href="ident?i=inet_csk_get_port">inet_csk_get_port</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned short snum)
 <a name="L94" href="source/net/ipv4/inet_connection_sock.c#L94">94</a> {
 <a name="L95" href="source/net/ipv4/inet_connection_sock.c#L95">95</a>         struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.hashinfo;
 <a name="L96" href="source/net/ipv4/inet_connection_sock.c#L96">96</a>         struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a> *<a href="ident?i=head">head</a>;
 <a name="L97" href="source/net/ipv4/inet_connection_sock.c#L97">97</a>         struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a> *<a href="ident?i=tb">tb</a>;
 <a name="L98" href="source/net/ipv4/inet_connection_sock.c#L98">98</a>         int <a href="ident?i=ret">ret</a>, attempts = 5;
 <a name="L99" href="source/net/ipv4/inet_connection_sock.c#L99">99</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L100" href="source/net/ipv4/inet_connection_sock.c#L100">100</a>         int smallest_size = -1, smallest_rover;
<a name="L101" href="source/net/ipv4/inet_connection_sock.c#L101">101</a>         <a href="ident?i=kuid_t">kuid_t</a> <a href="ident?i=uid">uid</a> = <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk);
<a name="L102" href="source/net/ipv4/inet_connection_sock.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/inet_connection_sock.c#L103">103</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L104" href="source/net/ipv4/inet_connection_sock.c#L104">104</a>         if (!snum) {
<a name="L105" href="source/net/ipv4/inet_connection_sock.c#L105">105</a>                 int <a href="ident?i=remaining">remaining</a>, rover, low, <a href="ident?i=high">high</a>;
<a name="L106" href="source/net/ipv4/inet_connection_sock.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/inet_connection_sock.c#L107">107</a> <a href="ident?i=again">again</a>:
<a name="L108" href="source/net/ipv4/inet_connection_sock.c#L108">108</a>                 <a href="ident?i=inet_get_local_port_range">inet_get_local_port_range</a>(<a href="ident?i=net">net</a>, &amp;low, &amp;<a href="ident?i=high">high</a>);
<a name="L109" href="source/net/ipv4/inet_connection_sock.c#L109">109</a>                 <a href="ident?i=remaining">remaining</a> = (<a href="ident?i=high">high</a> - low) + 1;
<a name="L110" href="source/net/ipv4/inet_connection_sock.c#L110">110</a>                 smallest_rover = rover = <a href="ident?i=prandom_u32">prandom_u32</a>() % <a href="ident?i=remaining">remaining</a> + low;
<a name="L111" href="source/net/ipv4/inet_connection_sock.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/inet_connection_sock.c#L112">112</a>                 smallest_size = -1;
<a name="L113" href="source/net/ipv4/inet_connection_sock.c#L113">113</a>                 do {
<a name="L114" href="source/net/ipv4/inet_connection_sock.c#L114">114</a>                         if (<a href="ident?i=inet_is_local_reserved_port">inet_is_local_reserved_port</a>(<a href="ident?i=net">net</a>, rover))
<a name="L115" href="source/net/ipv4/inet_connection_sock.c#L115">115</a>                                 goto next_nolock;
<a name="L116" href="source/net/ipv4/inet_connection_sock.c#L116">116</a>                         <a href="ident?i=head">head</a> = &amp;hashinfo-&gt;bhash[<a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=net">net</a>, rover,
<a name="L117" href="source/net/ipv4/inet_connection_sock.c#L117">117</a>                                         hashinfo-&gt;bhash_size)];
<a name="L118" href="source/net/ipv4/inet_connection_sock.c#L118">118</a>                         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L119" href="source/net/ipv4/inet_connection_sock.c#L119">119</a>                         <a href="ident?i=inet_bind_bucket_for_each">inet_bind_bucket_for_each</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>)
<a name="L120" href="source/net/ipv4/inet_connection_sock.c#L120">120</a>                                 if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=ib_net">ib_net</a>(<a href="ident?i=tb">tb</a>), <a href="ident?i=net">net</a>) &amp;&amp; <a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=port">port</a> == rover) {
<a name="L121" href="source/net/ipv4/inet_connection_sock.c#L121">121</a>                                         if (((<a href="ident?i=tb">tb</a>-&gt;fastreuse &gt; 0 &amp;&amp;
<a name="L122" href="source/net/ipv4/inet_connection_sock.c#L122">122</a>                                               sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> &amp;&amp;
<a name="L123" href="source/net/ipv4/inet_connection_sock.c#L123">123</a>                                               sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN) ||
<a name="L124" href="source/net/ipv4/inet_connection_sock.c#L124">124</a>                                              (<a href="ident?i=tb">tb</a>-&gt;fastreuseport &gt; 0 &amp;&amp;
<a name="L125" href="source/net/ipv4/inet_connection_sock.c#L125">125</a>                                               sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> &amp;&amp;
<a name="L126" href="source/net/ipv4/inet_connection_sock.c#L126">126</a>                                               <a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=tb">tb</a>-&gt;fastuid, <a href="ident?i=uid">uid</a>))) &amp;&amp;
<a name="L127" href="source/net/ipv4/inet_connection_sock.c#L127">127</a>                                             (<a href="ident?i=tb">tb</a>-&gt;num_owners &lt; smallest_size || smallest_size == -1)) {
<a name="L128" href="source/net/ipv4/inet_connection_sock.c#L128">128</a>                                                 smallest_size = <a href="ident?i=tb">tb</a>-&gt;num_owners;
<a name="L129" href="source/net/ipv4/inet_connection_sock.c#L129">129</a>                                                 smallest_rover = rover;
<a name="L130" href="source/net/ipv4/inet_connection_sock.c#L130">130</a>                                                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;hashinfo-&gt;bsockets) &gt; (<a href="ident?i=high">high</a> - low) + 1 &amp;&amp;
<a name="L131" href="source/net/ipv4/inet_connection_sock.c#L131">131</a>                                                     !<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;bind_conflict(sk, <a href="ident?i=tb">tb</a>, <a href="ident?i=false">false</a>)) {
<a name="L132" href="source/net/ipv4/inet_connection_sock.c#L132">132</a>                                                         snum = smallest_rover;
<a name="L133" href="source/net/ipv4/inet_connection_sock.c#L133">133</a>                                                         goto tb_found;
<a name="L134" href="source/net/ipv4/inet_connection_sock.c#L134">134</a>                                                 }
<a name="L135" href="source/net/ipv4/inet_connection_sock.c#L135">135</a>                                         }
<a name="L136" href="source/net/ipv4/inet_connection_sock.c#L136">136</a>                                         if (!<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;bind_conflict(sk, <a href="ident?i=tb">tb</a>, <a href="ident?i=false">false</a>)) {
<a name="L137" href="source/net/ipv4/inet_connection_sock.c#L137">137</a>                                                 snum = rover;
<a name="L138" href="source/net/ipv4/inet_connection_sock.c#L138">138</a>                                                 goto tb_found;
<a name="L139" href="source/net/ipv4/inet_connection_sock.c#L139">139</a>                                         }
<a name="L140" href="source/net/ipv4/inet_connection_sock.c#L140">140</a>                                         goto <a href="ident?i=next">next</a>;
<a name="L141" href="source/net/ipv4/inet_connection_sock.c#L141">141</a>                                 }
<a name="L142" href="source/net/ipv4/inet_connection_sock.c#L142">142</a>                         break;
<a name="L143" href="source/net/ipv4/inet_connection_sock.c#L143">143</a>                 <a href="ident?i=next">next</a>:
<a name="L144" href="source/net/ipv4/inet_connection_sock.c#L144">144</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L145" href="source/net/ipv4/inet_connection_sock.c#L145">145</a>                 next_nolock:
<a name="L146" href="source/net/ipv4/inet_connection_sock.c#L146">146</a>                         if (++rover &gt; <a href="ident?i=high">high</a>)
<a name="L147" href="source/net/ipv4/inet_connection_sock.c#L147">147</a>                                 rover = low;
<a name="L148" href="source/net/ipv4/inet_connection_sock.c#L148">148</a>                 } while (--<a href="ident?i=remaining">remaining</a> &gt; 0);
<a name="L149" href="source/net/ipv4/inet_connection_sock.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/inet_connection_sock.c#L150">150</a>                 <b><i>/* Exhausted local port range during search?  It is not</i></b>
<a name="L151" href="source/net/ipv4/inet_connection_sock.c#L151">151</a> <b><i>                 * possible for us to be holding one of the bind hash</i></b>
<a name="L152" href="source/net/ipv4/inet_connection_sock.c#L152">152</a> <b><i>                 * locks if this test triggers, because if 'remaining'</i></b>
<a name="L153" href="source/net/ipv4/inet_connection_sock.c#L153">153</a> <b><i>                 * drops to zero, we broke out of the do/while loop at</i></b>
<a name="L154" href="source/net/ipv4/inet_connection_sock.c#L154">154</a> <b><i>                 * the top level, not from the 'break;' statement.</i></b>
<a name="L155" href="source/net/ipv4/inet_connection_sock.c#L155">155</a> <b><i>                 */</i></b>
<a name="L156" href="source/net/ipv4/inet_connection_sock.c#L156">156</a>                 <a href="ident?i=ret">ret</a> = 1;
<a name="L157" href="source/net/ipv4/inet_connection_sock.c#L157">157</a>                 if (<a href="ident?i=remaining">remaining</a> &lt;= 0) {
<a name="L158" href="source/net/ipv4/inet_connection_sock.c#L158">158</a>                         if (smallest_size != -1) {
<a name="L159" href="source/net/ipv4/inet_connection_sock.c#L159">159</a>                                 snum = smallest_rover;
<a name="L160" href="source/net/ipv4/inet_connection_sock.c#L160">160</a>                                 goto have_snum;
<a name="L161" href="source/net/ipv4/inet_connection_sock.c#L161">161</a>                         }
<a name="L162" href="source/net/ipv4/inet_connection_sock.c#L162">162</a>                         goto <a href="ident?i=fail">fail</a>;
<a name="L163" href="source/net/ipv4/inet_connection_sock.c#L163">163</a>                 }
<a name="L164" href="source/net/ipv4/inet_connection_sock.c#L164">164</a>                 <b><i>/* OK, here is the one we will use.  HEAD is</i></b>
<a name="L165" href="source/net/ipv4/inet_connection_sock.c#L165">165</a> <b><i>                 * non-NULL and we hold it's mutex.</i></b>
<a name="L166" href="source/net/ipv4/inet_connection_sock.c#L166">166</a> <b><i>                 */</i></b>
<a name="L167" href="source/net/ipv4/inet_connection_sock.c#L167">167</a>                 snum = rover;
<a name="L168" href="source/net/ipv4/inet_connection_sock.c#L168">168</a>         } else {
<a name="L169" href="source/net/ipv4/inet_connection_sock.c#L169">169</a> have_snum:
<a name="L170" href="source/net/ipv4/inet_connection_sock.c#L170">170</a>                 <a href="ident?i=head">head</a> = &amp;hashinfo-&gt;bhash[<a href="ident?i=inet_bhashfn">inet_bhashfn</a>(<a href="ident?i=net">net</a>, snum,
<a name="L171" href="source/net/ipv4/inet_connection_sock.c#L171">171</a>                                 hashinfo-&gt;bhash_size)];
<a name="L172" href="source/net/ipv4/inet_connection_sock.c#L172">172</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L173" href="source/net/ipv4/inet_connection_sock.c#L173">173</a>                 <a href="ident?i=inet_bind_bucket_for_each">inet_bind_bucket_for_each</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>)
<a name="L174" href="source/net/ipv4/inet_connection_sock.c#L174">174</a>                         if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=ib_net">ib_net</a>(<a href="ident?i=tb">tb</a>), <a href="ident?i=net">net</a>) &amp;&amp; <a href="ident?i=tb">tb</a>-&gt;<a href="ident?i=port">port</a> == snum)
<a name="L175" href="source/net/ipv4/inet_connection_sock.c#L175">175</a>                                 goto tb_found;
<a name="L176" href="source/net/ipv4/inet_connection_sock.c#L176">176</a>         }
<a name="L177" href="source/net/ipv4/inet_connection_sock.c#L177">177</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L178" href="source/net/ipv4/inet_connection_sock.c#L178">178</a>         goto tb_not_found;
<a name="L179" href="source/net/ipv4/inet_connection_sock.c#L179">179</a> tb_found:
<a name="L180" href="source/net/ipv4/inet_connection_sock.c#L180">180</a>         if (!<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;owners)) {
<a name="L181" href="source/net/ipv4/inet_connection_sock.c#L181">181</a>                 if (sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> == <a href="ident?i=SK_FORCE_REUSE">SK_FORCE_REUSE</a>)
<a name="L182" href="source/net/ipv4/inet_connection_sock.c#L182">182</a>                         goto success;
<a name="L183" href="source/net/ipv4/inet_connection_sock.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/inet_connection_sock.c#L184">184</a>                 if (((<a href="ident?i=tb">tb</a>-&gt;fastreuse &gt; 0 &amp;&amp;
<a name="L185" href="source/net/ipv4/inet_connection_sock.c#L185">185</a>                       sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> &amp;&amp; sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN) ||
<a name="L186" href="source/net/ipv4/inet_connection_sock.c#L186">186</a>                      (<a href="ident?i=tb">tb</a>-&gt;fastreuseport &gt; 0 &amp;&amp;
<a name="L187" href="source/net/ipv4/inet_connection_sock.c#L187">187</a>                       sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> &amp;&amp; <a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=tb">tb</a>-&gt;fastuid, <a href="ident?i=uid">uid</a>))) &amp;&amp;
<a name="L188" href="source/net/ipv4/inet_connection_sock.c#L188">188</a>                     smallest_size == -1) {
<a name="L189" href="source/net/ipv4/inet_connection_sock.c#L189">189</a>                         goto success;
<a name="L190" href="source/net/ipv4/inet_connection_sock.c#L190">190</a>                 } else {
<a name="L191" href="source/net/ipv4/inet_connection_sock.c#L191">191</a>                         <a href="ident?i=ret">ret</a> = 1;
<a name="L192" href="source/net/ipv4/inet_connection_sock.c#L192">192</a>                         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;bind_conflict(sk, <a href="ident?i=tb">tb</a>, <a href="ident?i=true">true</a>)) {
<a name="L193" href="source/net/ipv4/inet_connection_sock.c#L193">193</a>                                 if (((sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> &amp;&amp; sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN) ||
<a name="L194" href="source/net/ipv4/inet_connection_sock.c#L194">194</a>                                      (<a href="ident?i=tb">tb</a>-&gt;fastreuseport &gt; 0 &amp;&amp;
<a name="L195" href="source/net/ipv4/inet_connection_sock.c#L195">195</a>                                       sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> &amp;&amp; <a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=tb">tb</a>-&gt;fastuid, <a href="ident?i=uid">uid</a>))) &amp;&amp;
<a name="L196" href="source/net/ipv4/inet_connection_sock.c#L196">196</a>                                     smallest_size != -1 &amp;&amp; --attempts &gt;= 0) {
<a name="L197" href="source/net/ipv4/inet_connection_sock.c#L197">197</a>                                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L198" href="source/net/ipv4/inet_connection_sock.c#L198">198</a>                                         goto <a href="ident?i=again">again</a>;
<a name="L199" href="source/net/ipv4/inet_connection_sock.c#L199">199</a>                                 }
<a name="L200" href="source/net/ipv4/inet_connection_sock.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/inet_connection_sock.c#L201">201</a>                                 goto fail_unlock;
<a name="L202" href="source/net/ipv4/inet_connection_sock.c#L202">202</a>                         }
<a name="L203" href="source/net/ipv4/inet_connection_sock.c#L203">203</a>                 }
<a name="L204" href="source/net/ipv4/inet_connection_sock.c#L204">204</a>         }
<a name="L205" href="source/net/ipv4/inet_connection_sock.c#L205">205</a> tb_not_found:
<a name="L206" href="source/net/ipv4/inet_connection_sock.c#L206">206</a>         <a href="ident?i=ret">ret</a> = 1;
<a name="L207" href="source/net/ipv4/inet_connection_sock.c#L207">207</a>         if (!<a href="ident?i=tb">tb</a> &amp;&amp; (<a href="ident?i=tb">tb</a> = <a href="ident?i=inet_bind_bucket_create">inet_bind_bucket_create</a>(hashinfo-&gt;bind_bucket_cachep,
<a name="L208" href="source/net/ipv4/inet_connection_sock.c#L208">208</a>                                         <a href="ident?i=net">net</a>, <a href="ident?i=head">head</a>, snum)) == <a href="ident?i=NULL">NULL</a>)
<a name="L209" href="source/net/ipv4/inet_connection_sock.c#L209">209</a>                 goto fail_unlock;
<a name="L210" href="source/net/ipv4/inet_connection_sock.c#L210">210</a>         if (<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;owners)) {
<a name="L211" href="source/net/ipv4/inet_connection_sock.c#L211">211</a>                 if (sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> &amp;&amp; sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN)
<a name="L212" href="source/net/ipv4/inet_connection_sock.c#L212">212</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuse = 1;
<a name="L213" href="source/net/ipv4/inet_connection_sock.c#L213">213</a>                 else
<a name="L214" href="source/net/ipv4/inet_connection_sock.c#L214">214</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuse = 0;
<a name="L215" href="source/net/ipv4/inet_connection_sock.c#L215">215</a>                 if (sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a>) {
<a name="L216" href="source/net/ipv4/inet_connection_sock.c#L216">216</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuseport = 1;
<a name="L217" href="source/net/ipv4/inet_connection_sock.c#L217">217</a>                         <a href="ident?i=tb">tb</a>-&gt;fastuid = <a href="ident?i=uid">uid</a>;
<a name="L218" href="source/net/ipv4/inet_connection_sock.c#L218">218</a>                 } else
<a name="L219" href="source/net/ipv4/inet_connection_sock.c#L219">219</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuseport = 0;
<a name="L220" href="source/net/ipv4/inet_connection_sock.c#L220">220</a>         } else {
<a name="L221" href="source/net/ipv4/inet_connection_sock.c#L221">221</a>                 if (<a href="ident?i=tb">tb</a>-&gt;fastreuse &amp;&amp;
<a name="L222" href="source/net/ipv4/inet_connection_sock.c#L222">222</a>                     (!sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> || sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN))
<a name="L223" href="source/net/ipv4/inet_connection_sock.c#L223">223</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuse = 0;
<a name="L224" href="source/net/ipv4/inet_connection_sock.c#L224">224</a>                 if (<a href="ident?i=tb">tb</a>-&gt;fastreuseport &amp;&amp;
<a name="L225" href="source/net/ipv4/inet_connection_sock.c#L225">225</a>                     (!sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> || !<a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=tb">tb</a>-&gt;fastuid, <a href="ident?i=uid">uid</a>)))
<a name="L226" href="source/net/ipv4/inet_connection_sock.c#L226">226</a>                         <a href="ident?i=tb">tb</a>-&gt;fastreuseport = 0;
<a name="L227" href="source/net/ipv4/inet_connection_sock.c#L227">227</a>         }
<a name="L228" href="source/net/ipv4/inet_connection_sock.c#L228">228</a> success:
<a name="L229" href="source/net/ipv4/inet_connection_sock.c#L229">229</a>         if (!<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash)
<a name="L230" href="source/net/ipv4/inet_connection_sock.c#L230">230</a>                 <a href="ident?i=inet_bind_hash">inet_bind_hash</a>(sk, <a href="ident?i=tb">tb</a>, snum);
<a name="L231" href="source/net/ipv4/inet_connection_sock.c#L231">231</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash != <a href="ident?i=tb">tb</a>);
<a name="L232" href="source/net/ipv4/inet_connection_sock.c#L232">232</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L233" href="source/net/ipv4/inet_connection_sock.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/inet_connection_sock.c#L234">234</a> fail_unlock:
<a name="L235" href="source/net/ipv4/inet_connection_sock.c#L235">235</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L236" href="source/net/ipv4/inet_connection_sock.c#L236">236</a> <a href="ident?i=fail">fail</a>:
<a name="L237" href="source/net/ipv4/inet_connection_sock.c#L237">237</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L238" href="source/net/ipv4/inet_connection_sock.c#L238">238</a>         return <a href="ident?i=ret">ret</a>;
<a name="L239" href="source/net/ipv4/inet_connection_sock.c#L239">239</a> }
<a name="L240" href="source/net/ipv4/inet_connection_sock.c#L240">240</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_get_port">inet_csk_get_port</a>);
<a name="L241" href="source/net/ipv4/inet_connection_sock.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/inet_connection_sock.c#L242">242</a> <b><i>/*</i></b>
<a name="L243" href="source/net/ipv4/inet_connection_sock.c#L243">243</a> <b><i> * Wait for an incoming connection, avoid race conditions. This must be called</i></b>
<a name="L244" href="source/net/ipv4/inet_connection_sock.c#L244">244</a> <b><i> * with the socket locked.</i></b>
<a name="L245" href="source/net/ipv4/inet_connection_sock.c#L245">245</a> <b><i> */</i></b>
<a name="L246" href="source/net/ipv4/inet_connection_sock.c#L246">246</a> static int <a href="ident?i=inet_csk_wait_for_connect">inet_csk_wait_for_connect</a>(struct <a href="ident?i=sock">sock</a> *sk, long timeo)
<a name="L247" href="source/net/ipv4/inet_connection_sock.c#L247">247</a> {
<a name="L248" href="source/net/ipv4/inet_connection_sock.c#L248">248</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L249" href="source/net/ipv4/inet_connection_sock.c#L249">249</a>         <a href="ident?i=DEFINE_WAIT">DEFINE_WAIT</a>(<a href="ident?i=wait">wait</a>);
<a name="L250" href="source/net/ipv4/inet_connection_sock.c#L250">250</a>         int <a href="ident?i=err">err</a>;
<a name="L251" href="source/net/ipv4/inet_connection_sock.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/inet_connection_sock.c#L252">252</a>         <b><i>/*</i></b>
<a name="L253" href="source/net/ipv4/inet_connection_sock.c#L253">253</a> <b><i>         * True wake-one mechanism for incoming connections: only</i></b>
<a name="L254" href="source/net/ipv4/inet_connection_sock.c#L254">254</a> <b><i>         * one process gets woken up, not the 'whole herd'.</i></b>
<a name="L255" href="source/net/ipv4/inet_connection_sock.c#L255">255</a> <b><i>         * Since we do not 'race &amp; poll' for established sockets</i></b>
<a name="L256" href="source/net/ipv4/inet_connection_sock.c#L256">256</a> <b><i>         * anymore, the common case will execute the loop only once.</i></b>
<a name="L257" href="source/net/ipv4/inet_connection_sock.c#L257">257</a> <b><i>         *</i></b>
<a name="L258" href="source/net/ipv4/inet_connection_sock.c#L258">258</a> <b><i>         * Subtle issue: "add_wait_queue_exclusive()" will be added</i></b>
<a name="L259" href="source/net/ipv4/inet_connection_sock.c#L259">259</a> <b><i>         * after any current non-exclusive waiters, and we know that</i></b>
<a name="L260" href="source/net/ipv4/inet_connection_sock.c#L260">260</a> <b><i>         * it will always _stay_ after any new non-exclusive waiters</i></b>
<a name="L261" href="source/net/ipv4/inet_connection_sock.c#L261">261</a> <b><i>         * because all non-exclusive waiters are added at the</i></b>
<a name="L262" href="source/net/ipv4/inet_connection_sock.c#L262">262</a> <b><i>         * beginning of the wait-queue. As such, it's ok to "drop"</i></b>
<a name="L263" href="source/net/ipv4/inet_connection_sock.c#L263">263</a> <b><i>         * our exclusiveness temporarily when we get woken up without</i></b>
<a name="L264" href="source/net/ipv4/inet_connection_sock.c#L264">264</a> <b><i>         * having to remove and re-insert us on the wait queue.</i></b>
<a name="L265" href="source/net/ipv4/inet_connection_sock.c#L265">265</a> <b><i>         */</i></b>
<a name="L266" href="source/net/ipv4/inet_connection_sock.c#L266">266</a>         for (;;) {
<a name="L267" href="source/net/ipv4/inet_connection_sock.c#L267">267</a>                 <a href="ident?i=prepare_to_wait_exclusive">prepare_to_wait_exclusive</a>(<a href="ident?i=sk_sleep">sk_sleep</a>(sk), &amp;<a href="ident?i=wait">wait</a>,
<a name="L268" href="source/net/ipv4/inet_connection_sock.c#L268">268</a>                                           <a href="ident?i=TASK_INTERRUPTIBLE">TASK_INTERRUPTIBLE</a>);
<a name="L269" href="source/net/ipv4/inet_connection_sock.c#L269">269</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L270" href="source/net/ipv4/inet_connection_sock.c#L270">270</a>                 if (<a href="ident?i=reqsk_queue_empty">reqsk_queue_empty</a>(&amp;icsk-&gt;icsk_accept_queue))
<a name="L271" href="source/net/ipv4/inet_connection_sock.c#L271">271</a>                         timeo = <a href="ident?i=schedule_timeout">schedule_timeout</a>(timeo);
<a name="L272" href="source/net/ipv4/inet_connection_sock.c#L272">272</a>                 <a href="ident?i=sched_annotate_sleep">sched_annotate_sleep</a>();
<a name="L273" href="source/net/ipv4/inet_connection_sock.c#L273">273</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L274" href="source/net/ipv4/inet_connection_sock.c#L274">274</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L275" href="source/net/ipv4/inet_connection_sock.c#L275">275</a>                 if (!<a href="ident?i=reqsk_queue_empty">reqsk_queue_empty</a>(&amp;icsk-&gt;icsk_accept_queue))
<a name="L276" href="source/net/ipv4/inet_connection_sock.c#L276">276</a>                         break;
<a name="L277" href="source/net/ipv4/inet_connection_sock.c#L277">277</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L278" href="source/net/ipv4/inet_connection_sock.c#L278">278</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN)
<a name="L279" href="source/net/ipv4/inet_connection_sock.c#L279">279</a>                         break;
<a name="L280" href="source/net/ipv4/inet_connection_sock.c#L280">280</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=sock_intr_errno">sock_intr_errno</a>(timeo);
<a name="L281" href="source/net/ipv4/inet_connection_sock.c#L281">281</a>                 if (<a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>))
<a name="L282" href="source/net/ipv4/inet_connection_sock.c#L282">282</a>                         break;
<a name="L283" href="source/net/ipv4/inet_connection_sock.c#L283">283</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L284" href="source/net/ipv4/inet_connection_sock.c#L284">284</a>                 if (!timeo)
<a name="L285" href="source/net/ipv4/inet_connection_sock.c#L285">285</a>                         break;
<a name="L286" href="source/net/ipv4/inet_connection_sock.c#L286">286</a>         }
<a name="L287" href="source/net/ipv4/inet_connection_sock.c#L287">287</a>         <a href="ident?i=finish_wait">finish_wait</a>(<a href="ident?i=sk_sleep">sk_sleep</a>(sk), &amp;<a href="ident?i=wait">wait</a>);
<a name="L288" href="source/net/ipv4/inet_connection_sock.c#L288">288</a>         return <a href="ident?i=err">err</a>;
<a name="L289" href="source/net/ipv4/inet_connection_sock.c#L289">289</a> }
<a name="L290" href="source/net/ipv4/inet_connection_sock.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/inet_connection_sock.c#L291">291</a> <b><i>/*</i></b>
<a name="L292" href="source/net/ipv4/inet_connection_sock.c#L292">292</a> <b><i> * This will accept the next outstanding connection.</i></b>
<a name="L293" href="source/net/ipv4/inet_connection_sock.c#L293">293</a> <b><i> */</i></b>
<a name="L294" href="source/net/ipv4/inet_connection_sock.c#L294">294</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=inet_csk_accept">inet_csk_accept</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flags">flags</a>, int *<a href="ident?i=err">err</a>)
<a name="L295" href="source/net/ipv4/inet_connection_sock.c#L295">295</a> {
<a name="L296" href="source/net/ipv4/inet_connection_sock.c#L296">296</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L297" href="source/net/ipv4/inet_connection_sock.c#L297">297</a>         struct <a href="ident?i=request_sock_queue">request_sock_queue</a> *<a href="ident?i=queue">queue</a> = &amp;icsk-&gt;icsk_accept_queue;
<a name="L298" href="source/net/ipv4/inet_connection_sock.c#L298">298</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L299" href="source/net/ipv4/inet_connection_sock.c#L299">299</a>         struct <a href="ident?i=sock">sock</a> *newsk;
<a name="L300" href="source/net/ipv4/inet_connection_sock.c#L300">300</a>         int <a href="ident?i=error">error</a>;
<a name="L301" href="source/net/ipv4/inet_connection_sock.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/inet_connection_sock.c#L302">302</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L303" href="source/net/ipv4/inet_connection_sock.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/inet_connection_sock.c#L304">304</a>         <b><i>/* We need to make sure that this socket is listening,</i></b>
<a name="L305" href="source/net/ipv4/inet_connection_sock.c#L305">305</a> <b><i>         * and that it has something pending.</i></b>
<a name="L306" href="source/net/ipv4/inet_connection_sock.c#L306">306</a> <b><i>         */</i></b>
<a name="L307" href="source/net/ipv4/inet_connection_sock.c#L307">307</a>         <a href="ident?i=error">error</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L308" href="source/net/ipv4/inet_connection_sock.c#L308">308</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN)
<a name="L309" href="source/net/ipv4/inet_connection_sock.c#L309">309</a>                 goto out_err;
<a name="L310" href="source/net/ipv4/inet_connection_sock.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/inet_connection_sock.c#L311">311</a>         <b><i>/* Find already established connection */</i></b>
<a name="L312" href="source/net/ipv4/inet_connection_sock.c#L312">312</a>         if (<a href="ident?i=reqsk_queue_empty">reqsk_queue_empty</a>(<a href="ident?i=queue">queue</a>)) {
<a name="L313" href="source/net/ipv4/inet_connection_sock.c#L313">313</a>                 long timeo = <a href="ident?i=sock_rcvtimeo">sock_rcvtimeo</a>(sk, <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a>);
<a name="L314" href="source/net/ipv4/inet_connection_sock.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/inet_connection_sock.c#L315">315</a>                 <b><i>/* If this is a non blocking socket don't sleep */</i></b>
<a name="L316" href="source/net/ipv4/inet_connection_sock.c#L316">316</a>                 <a href="ident?i=error">error</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L317" href="source/net/ipv4/inet_connection_sock.c#L317">317</a>                 if (!timeo)
<a name="L318" href="source/net/ipv4/inet_connection_sock.c#L318">318</a>                         goto out_err;
<a name="L319" href="source/net/ipv4/inet_connection_sock.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/inet_connection_sock.c#L320">320</a>                 <a href="ident?i=error">error</a> = <a href="ident?i=inet_csk_wait_for_connect">inet_csk_wait_for_connect</a>(sk, timeo);
<a name="L321" href="source/net/ipv4/inet_connection_sock.c#L321">321</a>                 if (<a href="ident?i=error">error</a>)
<a name="L322" href="source/net/ipv4/inet_connection_sock.c#L322">322</a>                         goto out_err;
<a name="L323" href="source/net/ipv4/inet_connection_sock.c#L323">323</a>         }
<a name="L324" href="source/net/ipv4/inet_connection_sock.c#L324">324</a>         <a href="ident?i=req">req</a> = <a href="ident?i=reqsk_queue_remove">reqsk_queue_remove</a>(<a href="ident?i=queue">queue</a>);
<a name="L325" href="source/net/ipv4/inet_connection_sock.c#L325">325</a>         newsk = <a href="ident?i=req">req</a>-&gt;sk;
<a name="L326" href="source/net/ipv4/inet_connection_sock.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/inet_connection_sock.c#L327">327</a>         <a href="ident?i=sk_acceptq_removed">sk_acceptq_removed</a>(sk);
<a name="L328" href="source/net/ipv4/inet_connection_sock.c#L328">328</a>         if (sk-&gt;sk_protocol == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> &amp;&amp;
<a name="L329" href="source/net/ipv4/inet_connection_sock.c#L329">329</a>             <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;tfo_listener &amp;&amp;
<a name="L330" href="source/net/ipv4/inet_connection_sock.c#L330">330</a>             <a href="ident?i=queue">queue</a>-&gt;fastopenq) {
<a name="L331" href="source/net/ipv4/inet_connection_sock.c#L331">331</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L332" href="source/net/ipv4/inet_connection_sock.c#L332">332</a>                 if (<a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;tfo_listener) {
<a name="L333" href="source/net/ipv4/inet_connection_sock.c#L333">333</a>                         <b><i>/* We are still waiting for the final ACK from 3WHS</i></b>
<a name="L334" href="source/net/ipv4/inet_connection_sock.c#L334">334</a> <b><i>                         * so can't free req now. Instead, we set req-&gt;sk to</i></b>
<a name="L335" href="source/net/ipv4/inet_connection_sock.c#L335">335</a> <b><i>                         * NULL to signify that the child socket is taken</i></b>
<a name="L336" href="source/net/ipv4/inet_connection_sock.c#L336">336</a> <b><i>                         * so reqsk_fastopen_remove() will free the req</i></b>
<a name="L337" href="source/net/ipv4/inet_connection_sock.c#L337">337</a> <b><i>                         * when 3WHS finishes (or is aborted).</i></b>
<a name="L338" href="source/net/ipv4/inet_connection_sock.c#L338">338</a> <b><i>                         */</i></b>
<a name="L339" href="source/net/ipv4/inet_connection_sock.c#L339">339</a>                         <a href="ident?i=req">req</a>-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L340" href="source/net/ipv4/inet_connection_sock.c#L340">340</a>                         <a href="ident?i=req">req</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L341" href="source/net/ipv4/inet_connection_sock.c#L341">341</a>                 }
<a name="L342" href="source/net/ipv4/inet_connection_sock.c#L342">342</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L343" href="source/net/ipv4/inet_connection_sock.c#L343">343</a>         }
<a name="L344" href="source/net/ipv4/inet_connection_sock.c#L344">344</a> <a href="ident?i=out">out</a>:
<a name="L345" href="source/net/ipv4/inet_connection_sock.c#L345">345</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L346" href="source/net/ipv4/inet_connection_sock.c#L346">346</a>         if (<a href="ident?i=req">req</a>)
<a name="L347" href="source/net/ipv4/inet_connection_sock.c#L347">347</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L348" href="source/net/ipv4/inet_connection_sock.c#L348">348</a>         return newsk;
<a name="L349" href="source/net/ipv4/inet_connection_sock.c#L349">349</a> out_err:
<a name="L350" href="source/net/ipv4/inet_connection_sock.c#L350">350</a>         newsk = <a href="ident?i=NULL">NULL</a>;
<a name="L351" href="source/net/ipv4/inet_connection_sock.c#L351">351</a>         <a href="ident?i=req">req</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L352" href="source/net/ipv4/inet_connection_sock.c#L352">352</a>         *<a href="ident?i=err">err</a> = <a href="ident?i=error">error</a>;
<a name="L353" href="source/net/ipv4/inet_connection_sock.c#L353">353</a>         goto <a href="ident?i=out">out</a>;
<a name="L354" href="source/net/ipv4/inet_connection_sock.c#L354">354</a> }
<a name="L355" href="source/net/ipv4/inet_connection_sock.c#L355">355</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_accept">inet_csk_accept</a>);
<a name="L356" href="source/net/ipv4/inet_connection_sock.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/inet_connection_sock.c#L357">357</a> <b><i>/*</i></b>
<a name="L358" href="source/net/ipv4/inet_connection_sock.c#L358">358</a> <b><i> * Using different timers for retransmit, delayed acks and probes</i></b>
<a name="L359" href="source/net/ipv4/inet_connection_sock.c#L359">359</a> <b><i> * We may wish use just one timer maintaining a list of expire jiffies</i></b>
<a name="L360" href="source/net/ipv4/inet_connection_sock.c#L360">360</a> <b><i> * to optimize.</i></b>
<a name="L361" href="source/net/ipv4/inet_connection_sock.c#L361">361</a> <b><i> */</i></b>
<a name="L362" href="source/net/ipv4/inet_connection_sock.c#L362">362</a> void <a href="ident?i=inet_csk_init_xmit_timers">inet_csk_init_xmit_timers</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L363" href="source/net/ipv4/inet_connection_sock.c#L363">363</a>                                void (*retransmit_handler)(unsigned long),
<a name="L364" href="source/net/ipv4/inet_connection_sock.c#L364">364</a>                                void (*delack_handler)(unsigned long),
<a name="L365" href="source/net/ipv4/inet_connection_sock.c#L365">365</a>                                void (*keepalive_handler)(unsigned long))
<a name="L366" href="source/net/ipv4/inet_connection_sock.c#L366">366</a> {
<a name="L367" href="source/net/ipv4/inet_connection_sock.c#L367">367</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L368" href="source/net/ipv4/inet_connection_sock.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/inet_connection_sock.c#L369">369</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;icsk-&gt;icsk_retransmit_timer, retransmit_handler,
<a name="L370" href="source/net/ipv4/inet_connection_sock.c#L370">370</a>                         (unsigned long)sk);
<a name="L371" href="source/net/ipv4/inet_connection_sock.c#L371">371</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;icsk-&gt;icsk_delack_timer, delack_handler,
<a name="L372" href="source/net/ipv4/inet_connection_sock.c#L372">372</a>                         (unsigned long)sk);
<a name="L373" href="source/net/ipv4/inet_connection_sock.c#L373">373</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;sk-&gt;sk_timer, keepalive_handler, (unsigned long)sk);
<a name="L374" href="source/net/ipv4/inet_connection_sock.c#L374">374</a>         icsk-&gt;icsk_pending = icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> = 0;
<a name="L375" href="source/net/ipv4/inet_connection_sock.c#L375">375</a> }
<a name="L376" href="source/net/ipv4/inet_connection_sock.c#L376">376</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_init_xmit_timers">inet_csk_init_xmit_timers</a>);
<a name="L377" href="source/net/ipv4/inet_connection_sock.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/inet_connection_sock.c#L378">378</a> void <a href="ident?i=inet_csk_clear_xmit_timers">inet_csk_clear_xmit_timers</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L379" href="source/net/ipv4/inet_connection_sock.c#L379">379</a> {
<a name="L380" href="source/net/ipv4/inet_connection_sock.c#L380">380</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L381" href="source/net/ipv4/inet_connection_sock.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/inet_connection_sock.c#L382">382</a>         icsk-&gt;icsk_pending = icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> = icsk-&gt;icsk_ack.blocked = 0;
<a name="L383" href="source/net/ipv4/inet_connection_sock.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/inet_connection_sock.c#L384">384</a>         <a href="ident?i=sk_stop_timer">sk_stop_timer</a>(sk, &amp;icsk-&gt;icsk_retransmit_timer);
<a name="L385" href="source/net/ipv4/inet_connection_sock.c#L385">385</a>         <a href="ident?i=sk_stop_timer">sk_stop_timer</a>(sk, &amp;icsk-&gt;icsk_delack_timer);
<a name="L386" href="source/net/ipv4/inet_connection_sock.c#L386">386</a>         <a href="ident?i=sk_stop_timer">sk_stop_timer</a>(sk, &amp;sk-&gt;sk_timer);
<a name="L387" href="source/net/ipv4/inet_connection_sock.c#L387">387</a> }
<a name="L388" href="source/net/ipv4/inet_connection_sock.c#L388">388</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_clear_xmit_timers">inet_csk_clear_xmit_timers</a>);
<a name="L389" href="source/net/ipv4/inet_connection_sock.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/inet_connection_sock.c#L390">390</a> void <a href="ident?i=inet_csk_delete_keepalive_timer">inet_csk_delete_keepalive_timer</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L391" href="source/net/ipv4/inet_connection_sock.c#L391">391</a> {
<a name="L392" href="source/net/ipv4/inet_connection_sock.c#L392">392</a>         <a href="ident?i=sk_stop_timer">sk_stop_timer</a>(sk, &amp;sk-&gt;sk_timer);
<a name="L393" href="source/net/ipv4/inet_connection_sock.c#L393">393</a> }
<a name="L394" href="source/net/ipv4/inet_connection_sock.c#L394">394</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_delete_keepalive_timer">inet_csk_delete_keepalive_timer</a>);
<a name="L395" href="source/net/ipv4/inet_connection_sock.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/inet_connection_sock.c#L396">396</a> void <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned long <a href="ident?i=len">len</a>)
<a name="L397" href="source/net/ipv4/inet_connection_sock.c#L397">397</a> {
<a name="L398" href="source/net/ipv4/inet_connection_sock.c#L398">398</a>         <a href="ident?i=sk_reset_timer">sk_reset_timer</a>(sk, &amp;sk-&gt;sk_timer, <a href="ident?i=jiffies">jiffies</a> + <a href="ident?i=len">len</a>);
<a name="L399" href="source/net/ipv4/inet_connection_sock.c#L399">399</a> }
<a name="L400" href="source/net/ipv4/inet_connection_sock.c#L400">400</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>);
<a name="L401" href="source/net/ipv4/inet_connection_sock.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/inet_connection_sock.c#L402">402</a> struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=inet_csk_route_req">inet_csk_route_req</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L403" href="source/net/ipv4/inet_connection_sock.c#L403">403</a>                                      struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L404" href="source/net/ipv4/inet_connection_sock.c#L404">404</a>                                      const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L405" href="source/net/ipv4/inet_connection_sock.c#L405">405</a> {
<a name="L406" href="source/net/ipv4/inet_connection_sock.c#L406">406</a>         const struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L407" href="source/net/ipv4/inet_connection_sock.c#L407">407</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=read_pnet">read_pnet</a>(&amp;ireq-&gt;<a href="ident?i=ireq_net">ireq_net</a>);
<a name="L408" href="source/net/ipv4/inet_connection_sock.c#L408">408</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt = ireq-&gt;opt;
<a name="L409" href="source/net/ipv4/inet_connection_sock.c#L409">409</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L410" href="source/net/ipv4/inet_connection_sock.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/inet_connection_sock.c#L411">411</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(fl4, ireq-&gt;<a href="ident?i=ir_iif">ir_iif</a>, ireq-&gt;ir_mark,
<a name="L412" href="source/net/ipv4/inet_connection_sock.c#L412">412</a>                            <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), RT_SCOPE_UNIVERSE,
<a name="L413" href="source/net/ipv4/inet_connection_sock.c#L413">413</a>                            sk-&gt;sk_protocol, <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk),
<a name="L414" href="source/net/ipv4/inet_connection_sock.c#L414">414</a>                            (opt &amp;&amp; opt-&gt;opt.<a href="ident?i=srr">srr</a>) ? opt-&gt;opt.faddr : ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>,
<a name="L415" href="source/net/ipv4/inet_connection_sock.c#L415">415</a>                            ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>, ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>,
<a name="L416" href="source/net/ipv4/inet_connection_sock.c#L416">416</a>                            <a href="ident?i=htons">htons</a>(ireq-&gt;<a href="ident?i=ir_num">ir_num</a>));
<a name="L417" href="source/net/ipv4/inet_connection_sock.c#L417">417</a>         <a href="ident?i=security_req_classify_flow">security_req_classify_flow</a>(<a href="ident?i=req">req</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(fl4));
<a name="L418" href="source/net/ipv4/inet_connection_sock.c#L418">418</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=net">net</a>, fl4, sk);
<a name="L419" href="source/net/ipv4/inet_connection_sock.c#L419">419</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L420" href="source/net/ipv4/inet_connection_sock.c#L420">420</a>                 goto no_route;
<a name="L421" href="source/net/ipv4/inet_connection_sock.c#L421">421</a>         if (opt &amp;&amp; opt-&gt;opt.is_strictroute &amp;&amp; <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway)
<a name="L422" href="source/net/ipv4/inet_connection_sock.c#L422">422</a>                 goto route_err;
<a name="L423" href="source/net/ipv4/inet_connection_sock.c#L423">423</a>         return &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L424" href="source/net/ipv4/inet_connection_sock.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/inet_connection_sock.c#L425">425</a> route_err:
<a name="L426" href="source/net/ipv4/inet_connection_sock.c#L426">426</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L427" href="source/net/ipv4/inet_connection_sock.c#L427">427</a> no_route:
<a name="L428" href="source/net/ipv4/inet_connection_sock.c#L428">428</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_OUTNOROUTES);
<a name="L429" href="source/net/ipv4/inet_connection_sock.c#L429">429</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L430" href="source/net/ipv4/inet_connection_sock.c#L430">430</a> }
<a name="L431" href="source/net/ipv4/inet_connection_sock.c#L431">431</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_route_req">inet_csk_route_req</a>);
<a name="L432" href="source/net/ipv4/inet_connection_sock.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/inet_connection_sock.c#L433">433</a> struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=inet_csk_route_child_sock">inet_csk_route_child_sock</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L434" href="source/net/ipv4/inet_connection_sock.c#L434">434</a>                                             struct <a href="ident?i=sock">sock</a> *newsk,
<a name="L435" href="source/net/ipv4/inet_connection_sock.c#L435">435</a>                                             const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L436" href="source/net/ipv4/inet_connection_sock.c#L436">436</a> {
<a name="L437" href="source/net/ipv4/inet_connection_sock.c#L437">437</a>         const struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L438" href="source/net/ipv4/inet_connection_sock.c#L438">438</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=read_pnet">read_pnet</a>(&amp;ireq-&gt;<a href="ident?i=ireq_net">ireq_net</a>);
<a name="L439" href="source/net/ipv4/inet_connection_sock.c#L439">439</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *newinet = <a href="ident?i=inet_sk">inet_sk</a>(newsk);
<a name="L440" href="source/net/ipv4/inet_connection_sock.c#L440">440</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt;
<a name="L441" href="source/net/ipv4/inet_connection_sock.c#L441">441</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L442" href="source/net/ipv4/inet_connection_sock.c#L442">442</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L443" href="source/net/ipv4/inet_connection_sock.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/inet_connection_sock.c#L444">444</a>         fl4 = &amp;newinet-&gt;cork.fl.u.ip4;
<a name="L445" href="source/net/ipv4/inet_connection_sock.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/inet_connection_sock.c#L446">446</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L447" href="source/net/ipv4/inet_connection_sock.c#L447">447</a>         opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(newinet-&gt;inet_opt);
<a name="L448" href="source/net/ipv4/inet_connection_sock.c#L448">448</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(fl4, ireq-&gt;<a href="ident?i=ir_iif">ir_iif</a>, ireq-&gt;ir_mark,
<a name="L449" href="source/net/ipv4/inet_connection_sock.c#L449">449</a>                            <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), RT_SCOPE_UNIVERSE,
<a name="L450" href="source/net/ipv4/inet_connection_sock.c#L450">450</a>                            sk-&gt;sk_protocol, <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk),
<a name="L451" href="source/net/ipv4/inet_connection_sock.c#L451">451</a>                            (opt &amp;&amp; opt-&gt;opt.<a href="ident?i=srr">srr</a>) ? opt-&gt;opt.faddr : ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>,
<a name="L452" href="source/net/ipv4/inet_connection_sock.c#L452">452</a>                            ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>, ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>,
<a name="L453" href="source/net/ipv4/inet_connection_sock.c#L453">453</a>                            <a href="ident?i=htons">htons</a>(ireq-&gt;<a href="ident?i=ir_num">ir_num</a>));
<a name="L454" href="source/net/ipv4/inet_connection_sock.c#L454">454</a>         <a href="ident?i=security_req_classify_flow">security_req_classify_flow</a>(<a href="ident?i=req">req</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(fl4));
<a name="L455" href="source/net/ipv4/inet_connection_sock.c#L455">455</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=net">net</a>, fl4, sk);
<a name="L456" href="source/net/ipv4/inet_connection_sock.c#L456">456</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L457" href="source/net/ipv4/inet_connection_sock.c#L457">457</a>                 goto no_route;
<a name="L458" href="source/net/ipv4/inet_connection_sock.c#L458">458</a>         if (opt &amp;&amp; opt-&gt;opt.is_strictroute &amp;&amp; <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway)
<a name="L459" href="source/net/ipv4/inet_connection_sock.c#L459">459</a>                 goto route_err;
<a name="L460" href="source/net/ipv4/inet_connection_sock.c#L460">460</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L461" href="source/net/ipv4/inet_connection_sock.c#L461">461</a>         return &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L462" href="source/net/ipv4/inet_connection_sock.c#L462">462</a> 
<a name="L463" href="source/net/ipv4/inet_connection_sock.c#L463">463</a> route_err:
<a name="L464" href="source/net/ipv4/inet_connection_sock.c#L464">464</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L465" href="source/net/ipv4/inet_connection_sock.c#L465">465</a> no_route:
<a name="L466" href="source/net/ipv4/inet_connection_sock.c#L466">466</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L467" href="source/net/ipv4/inet_connection_sock.c#L467">467</a>         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_OUTNOROUTES);
<a name="L468" href="source/net/ipv4/inet_connection_sock.c#L468">468</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L469" href="source/net/ipv4/inet_connection_sock.c#L469">469</a> }
<a name="L470" href="source/net/ipv4/inet_connection_sock.c#L470">470</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_route_child_sock">inet_csk_route_child_sock</a>);
<a name="L471" href="source/net/ipv4/inet_connection_sock.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/inet_connection_sock.c#L472">472</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=inet_synq_hash">inet_synq_hash</a>(const <a href="ident?i=__be32">__be32</a> raddr, const <a href="ident?i=__be16">__be16</a> rport,
<a name="L473" href="source/net/ipv4/inet_connection_sock.c#L473">473</a>                                  const <a href="ident?i=u32">u32</a> <a href="ident?i=rnd">rnd</a>, const <a href="ident?i=u32">u32</a> synq_hsize)
<a name="L474" href="source/net/ipv4/inet_connection_sock.c#L474">474</a> {
<a name="L475" href="source/net/ipv4/inet_connection_sock.c#L475">475</a>         return <a href="ident?i=jhash_2words">jhash_2words</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)raddr, (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)rport, <a href="ident?i=rnd">rnd</a>) &amp; (synq_hsize - 1);
<a name="L476" href="source/net/ipv4/inet_connection_sock.c#L476">476</a> }
<a name="L477" href="source/net/ipv4/inet_connection_sock.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/inet_connection_sock.c#L478">478</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L479" href="source/net/ipv4/inet_connection_sock.c#L479">479</a> #define <a href="ident?i=AF_INET_FAMILY">AF_INET_FAMILY</a>(fam) ((fam) == <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L480" href="source/net/ipv4/inet_connection_sock.c#L480">480</a> #else
<a name="L481" href="source/net/ipv4/inet_connection_sock.c#L481">481</a> #define <a href="ident?i=AF_INET_FAMILY">AF_INET_FAMILY</a>(fam) <a href="ident?i=true">true</a>
<a name="L482" href="source/net/ipv4/inet_connection_sock.c#L482">482</a> #endif
<a name="L483" href="source/net/ipv4/inet_connection_sock.c#L483">483</a> 
<a name="L484" href="source/net/ipv4/inet_connection_sock.c#L484">484</a> <b><i>/* Note: this is temporary :</i></b>
<a name="L485" href="source/net/ipv4/inet_connection_sock.c#L485">485</a> <b><i> * req sock will no longer be in listener hash table</i></b>
<a name="L486" href="source/net/ipv4/inet_connection_sock.c#L486">486</a> <b><i>*/</i></b>
<a name="L487" href="source/net/ipv4/inet_connection_sock.c#L487">487</a> struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=inet_csk_search_req">inet_csk_search_req</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L488" href="source/net/ipv4/inet_connection_sock.c#L488">488</a>                                          const <a href="ident?i=__be16">__be16</a> rport,
<a name="L489" href="source/net/ipv4/inet_connection_sock.c#L489">489</a>                                          const <a href="ident?i=__be32">__be32</a> raddr,
<a name="L490" href="source/net/ipv4/inet_connection_sock.c#L490">490</a>                                          const <a href="ident?i=__be32">__be32</a> <a href="ident?i=laddr">laddr</a>)
<a name="L491" href="source/net/ipv4/inet_connection_sock.c#L491">491</a> {
<a name="L492" href="source/net/ipv4/inet_connection_sock.c#L492">492</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L493" href="source/net/ipv4/inet_connection_sock.c#L493">493</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt = icsk-&gt;icsk_accept_queue.listen_opt;
<a name="L494" href="source/net/ipv4/inet_connection_sock.c#L494">494</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L495" href="source/net/ipv4/inet_connection_sock.c#L495">495</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_synq_hash">inet_synq_hash</a>(raddr, rport, lopt-&gt;hash_rnd,
<a name="L496" href="source/net/ipv4/inet_connection_sock.c#L496">496</a>                                   lopt-&gt;nr_table_entries);
<a name="L497" href="source/net/ipv4/inet_connection_sock.c#L497">497</a> 
<a name="L498" href="source/net/ipv4/inet_connection_sock.c#L498">498</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L499" href="source/net/ipv4/inet_connection_sock.c#L499">499</a>         for (<a href="ident?i=req">req</a> = lopt-&gt;syn_table[<a href="ident?i=hash">hash</a>]; <a href="ident?i=req">req</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=req">req</a> = <a href="ident?i=req">req</a>-&gt;dl_next) {
<a name="L500" href="source/net/ipv4/inet_connection_sock.c#L500">500</a>                 const struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L501" href="source/net/ipv4/inet_connection_sock.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/inet_connection_sock.c#L502">502</a>                 if (ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a> == rport &amp;&amp;
<a name="L503" href="source/net/ipv4/inet_connection_sock.c#L503">503</a>                     ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a> == raddr &amp;&amp;
<a name="L504" href="source/net/ipv4/inet_connection_sock.c#L504">504</a>                     ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a> == <a href="ident?i=laddr">laddr</a> &amp;&amp;
<a name="L505" href="source/net/ipv4/inet_connection_sock.c#L505">505</a>                     <a href="ident?i=AF_INET_FAMILY">AF_INET_FAMILY</a>(<a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=family">family</a>)) {
<a name="L506" href="source/net/ipv4/inet_connection_sock.c#L506">506</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=req">req</a>-&gt;<a href="ident?i=rsk_refcnt">rsk_refcnt</a>);
<a name="L507" href="source/net/ipv4/inet_connection_sock.c#L507">507</a>                         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=req">req</a>-&gt;sk);
<a name="L508" href="source/net/ipv4/inet_connection_sock.c#L508">508</a>                         break;
<a name="L509" href="source/net/ipv4/inet_connection_sock.c#L509">509</a>                 }
<a name="L510" href="source/net/ipv4/inet_connection_sock.c#L510">510</a>         }
<a name="L511" href="source/net/ipv4/inet_connection_sock.c#L511">511</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L512" href="source/net/ipv4/inet_connection_sock.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/inet_connection_sock.c#L513">513</a>         return <a href="ident?i=req">req</a>;
<a name="L514" href="source/net/ipv4/inet_connection_sock.c#L514">514</a> }
<a name="L515" href="source/net/ipv4/inet_connection_sock.c#L515">515</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_search_req">inet_csk_search_req</a>);
<a name="L516" href="source/net/ipv4/inet_connection_sock.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/inet_connection_sock.c#L517">517</a> void <a href="ident?i=inet_csk_reqsk_queue_hash_add">inet_csk_reqsk_queue_hash_add</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L518" href="source/net/ipv4/inet_connection_sock.c#L518">518</a>                                    unsigned long <a href="ident?i=timeout">timeout</a>)
<a name="L519" href="source/net/ipv4/inet_connection_sock.c#L519">519</a> {
<a name="L520" href="source/net/ipv4/inet_connection_sock.c#L520">520</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L521" href="source/net/ipv4/inet_connection_sock.c#L521">521</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt = icsk-&gt;icsk_accept_queue.listen_opt;
<a name="L522" href="source/net/ipv4/inet_connection_sock.c#L522">522</a>         const <a href="ident?i=u32">u32</a> <a href="ident?i=h">h</a> = <a href="ident?i=inet_synq_hash">inet_synq_hash</a>(<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>,
<a name="L523" href="source/net/ipv4/inet_connection_sock.c#L523">523</a>                                      <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>,
<a name="L524" href="source/net/ipv4/inet_connection_sock.c#L524">524</a>                                      lopt-&gt;hash_rnd, lopt-&gt;nr_table_entries);
<a name="L525" href="source/net/ipv4/inet_connection_sock.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/inet_connection_sock.c#L526">526</a>         <a href="ident?i=reqsk_queue_hash_req">reqsk_queue_hash_req</a>(&amp;icsk-&gt;icsk_accept_queue, <a href="ident?i=h">h</a>, <a href="ident?i=req">req</a>, <a href="ident?i=timeout">timeout</a>);
<a name="L527" href="source/net/ipv4/inet_connection_sock.c#L527">527</a>         <a href="ident?i=inet_csk_reqsk_queue_added">inet_csk_reqsk_queue_added</a>(sk, <a href="ident?i=timeout">timeout</a>);
<a name="L528" href="source/net/ipv4/inet_connection_sock.c#L528">528</a> }
<a name="L529" href="source/net/ipv4/inet_connection_sock.c#L529">529</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_reqsk_queue_hash_add">inet_csk_reqsk_queue_hash_add</a>);
<a name="L530" href="source/net/ipv4/inet_connection_sock.c#L530">530</a> 
<a name="L531" href="source/net/ipv4/inet_connection_sock.c#L531">531</a> <b><i>/* Only thing we need from tcp.h */</i></b>
<a name="L532" href="source/net/ipv4/inet_connection_sock.c#L532">532</a> extern int <a href="ident?i=sysctl_tcp_synack_retries">sysctl_tcp_synack_retries</a>;
<a name="L533" href="source/net/ipv4/inet_connection_sock.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/inet_connection_sock.c#L534">534</a> 
<a name="L535" href="source/net/ipv4/inet_connection_sock.c#L535">535</a> <b><i>/* Decide when to expire the request and when to resend SYN-ACK */</i></b>
<a name="L536" href="source/net/ipv4/inet_connection_sock.c#L536">536</a> static inline void <a href="ident?i=syn_ack_recalc">syn_ack_recalc</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, const int thresh,
<a name="L537" href="source/net/ipv4/inet_connection_sock.c#L537">537</a>                                   const int max_retries,
<a name="L538" href="source/net/ipv4/inet_connection_sock.c#L538">538</a>                                   const <a href="ident?i=u8">u8</a> rskq_defer_accept,
<a name="L539" href="source/net/ipv4/inet_connection_sock.c#L539">539</a>                                   int *expire, int *<a href="ident?i=resend">resend</a>)
<a name="L540" href="source/net/ipv4/inet_connection_sock.c#L540">540</a> {
<a name="L541" href="source/net/ipv4/inet_connection_sock.c#L541">541</a>         if (!rskq_defer_accept) {
<a name="L542" href="source/net/ipv4/inet_connection_sock.c#L542">542</a>                 *expire = <a href="ident?i=req">req</a>-&gt;num_timeout &gt;= thresh;
<a name="L543" href="source/net/ipv4/inet_connection_sock.c#L543">543</a>                 *<a href="ident?i=resend">resend</a> = 1;
<a name="L544" href="source/net/ipv4/inet_connection_sock.c#L544">544</a>                 return;
<a name="L545" href="source/net/ipv4/inet_connection_sock.c#L545">545</a>         }
<a name="L546" href="source/net/ipv4/inet_connection_sock.c#L546">546</a>         *expire = <a href="ident?i=req">req</a>-&gt;num_timeout &gt;= thresh &amp;&amp;
<a name="L547" href="source/net/ipv4/inet_connection_sock.c#L547">547</a>                   (!<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;acked || <a href="ident?i=req">req</a>-&gt;num_timeout &gt;= max_retries);
<a name="L548" href="source/net/ipv4/inet_connection_sock.c#L548">548</a>         <b><i>/*</i></b>
<a name="L549" href="source/net/ipv4/inet_connection_sock.c#L549">549</a> <b><i>         * Do not resend while waiting for data after ACK,</i></b>
<a name="L550" href="source/net/ipv4/inet_connection_sock.c#L550">550</a> <b><i>         * start to resend on end of deferring period to give</i></b>
<a name="L551" href="source/net/ipv4/inet_connection_sock.c#L551">551</a> <b><i>         * last chance for data or ACK to create established socket.</i></b>
<a name="L552" href="source/net/ipv4/inet_connection_sock.c#L552">552</a> <b><i>         */</i></b>
<a name="L553" href="source/net/ipv4/inet_connection_sock.c#L553">553</a>         *<a href="ident?i=resend">resend</a> = !<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;acked ||
<a name="L554" href="source/net/ipv4/inet_connection_sock.c#L554">554</a>                   <a href="ident?i=req">req</a>-&gt;num_timeout &gt;= rskq_defer_accept - 1;
<a name="L555" href="source/net/ipv4/inet_connection_sock.c#L555">555</a> }
<a name="L556" href="source/net/ipv4/inet_connection_sock.c#L556">556</a> 
<a name="L557" href="source/net/ipv4/inet_connection_sock.c#L557">557</a> int <a href="ident?i=inet_rtx_syn_ack">inet_rtx_syn_ack</a>(struct <a href="ident?i=sock">sock</a> *<a href="ident?i=parent">parent</a>, struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L558" href="source/net/ipv4/inet_connection_sock.c#L558">558</a> {
<a name="L559" href="source/net/ipv4/inet_connection_sock.c#L559">559</a>         int <a href="ident?i=err">err</a> = <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;rtx_syn_ack(<a href="ident?i=parent">parent</a>, <a href="ident?i=req">req</a>);
<a name="L560" href="source/net/ipv4/inet_connection_sock.c#L560">560</a> 
<a name="L561" href="source/net/ipv4/inet_connection_sock.c#L561">561</a>         if (!<a href="ident?i=err">err</a>)
<a name="L562" href="source/net/ipv4/inet_connection_sock.c#L562">562</a>                 <a href="ident?i=req">req</a>-&gt;num_retrans++;
<a name="L563" href="source/net/ipv4/inet_connection_sock.c#L563">563</a>         return <a href="ident?i=err">err</a>;
<a name="L564" href="source/net/ipv4/inet_connection_sock.c#L564">564</a> }
<a name="L565" href="source/net/ipv4/inet_connection_sock.c#L565">565</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_rtx_syn_ack">inet_rtx_syn_ack</a>);
<a name="L566" href="source/net/ipv4/inet_connection_sock.c#L566">566</a> 
<a name="L567" href="source/net/ipv4/inet_connection_sock.c#L567">567</a> <b><i>/* return true if req was found in the syn_table[] */</i></b>
<a name="L568" href="source/net/ipv4/inet_connection_sock.c#L568">568</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=reqsk_queue_unlink">reqsk_queue_unlink</a>(struct <a href="ident?i=request_sock_queue">request_sock_queue</a> *<a href="ident?i=queue">queue</a>,
<a name="L569" href="source/net/ipv4/inet_connection_sock.c#L569">569</a>                                struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L570" href="source/net/ipv4/inet_connection_sock.c#L570">570</a> {
<a name="L571" href="source/net/ipv4/inet_connection_sock.c#L571">571</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt = <a href="ident?i=queue">queue</a>-&gt;listen_opt;
<a name="L572" href="source/net/ipv4/inet_connection_sock.c#L572">572</a>         struct <a href="ident?i=request_sock">request_sock</a> **prev;
<a name="L573" href="source/net/ipv4/inet_connection_sock.c#L573">573</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=found">found</a> = <a href="ident?i=false">false</a>;
<a name="L574" href="source/net/ipv4/inet_connection_sock.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/inet_connection_sock.c#L575">575</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;syn_wait_lock);
<a name="L576" href="source/net/ipv4/inet_connection_sock.c#L576">576</a> 
<a name="L577" href="source/net/ipv4/inet_connection_sock.c#L577">577</a>         for (prev = &amp;lopt-&gt;syn_table[<a href="ident?i=req">req</a>-&gt;<a href="ident?i=rsk_hash">rsk_hash</a>]; *prev != <a href="ident?i=NULL">NULL</a>;
<a name="L578" href="source/net/ipv4/inet_connection_sock.c#L578">578</a>              prev = &amp;(*prev)-&gt;dl_next) {
<a name="L579" href="source/net/ipv4/inet_connection_sock.c#L579">579</a>                 if (*prev == <a href="ident?i=req">req</a>) {
<a name="L580" href="source/net/ipv4/inet_connection_sock.c#L580">580</a>                         *prev = <a href="ident?i=req">req</a>-&gt;dl_next;
<a name="L581" href="source/net/ipv4/inet_connection_sock.c#L581">581</a>                         <a href="ident?i=found">found</a> = <a href="ident?i=true">true</a>;
<a name="L582" href="source/net/ipv4/inet_connection_sock.c#L582">582</a>                         break;
<a name="L583" href="source/net/ipv4/inet_connection_sock.c#L583">583</a>                 }
<a name="L584" href="source/net/ipv4/inet_connection_sock.c#L584">584</a>         }
<a name="L585" href="source/net/ipv4/inet_connection_sock.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/inet_connection_sock.c#L586">586</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;syn_wait_lock);
<a name="L587" href="source/net/ipv4/inet_connection_sock.c#L587">587</a>         if (<a href="ident?i=del_timer">del_timer</a>(&amp;<a href="ident?i=req">req</a>-&gt;rsk_timer))
<a name="L588" href="source/net/ipv4/inet_connection_sock.c#L588">588</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L589" href="source/net/ipv4/inet_connection_sock.c#L589">589</a>         return <a href="ident?i=found">found</a>;
<a name="L590" href="source/net/ipv4/inet_connection_sock.c#L590">590</a> }
<a name="L591" href="source/net/ipv4/inet_connection_sock.c#L591">591</a> 
<a name="L592" href="source/net/ipv4/inet_connection_sock.c#L592">592</a> void <a href="ident?i=inet_csk_reqsk_queue_drop">inet_csk_reqsk_queue_drop</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L593" href="source/net/ipv4/inet_connection_sock.c#L593">593</a> {
<a name="L594" href="source/net/ipv4/inet_connection_sock.c#L594">594</a>         if (<a href="ident?i=reqsk_queue_unlink">reqsk_queue_unlink</a>(&amp;<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue, <a href="ident?i=req">req</a>)) {
<a name="L595" href="source/net/ipv4/inet_connection_sock.c#L595">595</a>                 <a href="ident?i=reqsk_queue_removed">reqsk_queue_removed</a>(&amp;<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue, <a href="ident?i=req">req</a>);
<a name="L596" href="source/net/ipv4/inet_connection_sock.c#L596">596</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L597" href="source/net/ipv4/inet_connection_sock.c#L597">597</a>         }
<a name="L598" href="source/net/ipv4/inet_connection_sock.c#L598">598</a> }
<a name="L599" href="source/net/ipv4/inet_connection_sock.c#L599">599</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_reqsk_queue_drop">inet_csk_reqsk_queue_drop</a>);
<a name="L600" href="source/net/ipv4/inet_connection_sock.c#L600">600</a> 
<a name="L601" href="source/net/ipv4/inet_connection_sock.c#L601">601</a> static void <a href="ident?i=reqsk_timer_handler">reqsk_timer_handler</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L602" href="source/net/ipv4/inet_connection_sock.c#L602">602</a> {
<a name="L603" href="source/net/ipv4/inet_connection_sock.c#L603">603</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a> = (struct <a href="ident?i=request_sock">request_sock</a> *)<a href="ident?i=data">data</a>;
<a name="L604" href="source/net/ipv4/inet_connection_sock.c#L604">604</a>         struct <a href="ident?i=sock">sock</a> *sk_listener = <a href="ident?i=req">req</a>-&gt;rsk_listener;
<a name="L605" href="source/net/ipv4/inet_connection_sock.c#L605">605</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk_listener);
<a name="L606" href="source/net/ipv4/inet_connection_sock.c#L606">606</a>         struct <a href="ident?i=request_sock_queue">request_sock_queue</a> *<a href="ident?i=queue">queue</a> = &amp;icsk-&gt;icsk_accept_queue;
<a name="L607" href="source/net/ipv4/inet_connection_sock.c#L607">607</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt = <a href="ident?i=queue">queue</a>-&gt;listen_opt;
<a name="L608" href="source/net/ipv4/inet_connection_sock.c#L608">608</a>         int <a href="ident?i=qlen">qlen</a>, expire = 0, <a href="ident?i=resend">resend</a> = 0;
<a name="L609" href="source/net/ipv4/inet_connection_sock.c#L609">609</a>         int max_retries, thresh;
<a name="L610" href="source/net/ipv4/inet_connection_sock.c#L610">610</a>         <a href="ident?i=u8">u8</a> defer_accept;
<a name="L611" href="source/net/ipv4/inet_connection_sock.c#L611">611</a> 
<a name="L612" href="source/net/ipv4/inet_connection_sock.c#L612">612</a>         if (sk_listener-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN || !lopt) {
<a name="L613" href="source/net/ipv4/inet_connection_sock.c#L613">613</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L614" href="source/net/ipv4/inet_connection_sock.c#L614">614</a>                 return;
<a name="L615" href="source/net/ipv4/inet_connection_sock.c#L615">615</a>         }
<a name="L616" href="source/net/ipv4/inet_connection_sock.c#L616">616</a> 
<a name="L617" href="source/net/ipv4/inet_connection_sock.c#L617">617</a>         max_retries = icsk-&gt;icsk_syn_retries ? : <a href="ident?i=sysctl_tcp_synack_retries">sysctl_tcp_synack_retries</a>;
<a name="L618" href="source/net/ipv4/inet_connection_sock.c#L618">618</a>         thresh = max_retries;
<a name="L619" href="source/net/ipv4/inet_connection_sock.c#L619">619</a>         <b><i>/* Normally all the openreqs are young and become mature</i></b>
<a name="L620" href="source/net/ipv4/inet_connection_sock.c#L620">620</a> <b><i>         * (i.e. converted to established socket) for first timeout.</i></b>
<a name="L621" href="source/net/ipv4/inet_connection_sock.c#L621">621</a> <b><i>         * If synack was not acknowledged for 1 second, it means</i></b>
<a name="L622" href="source/net/ipv4/inet_connection_sock.c#L622">622</a> <b><i>         * one of the following things: synack was lost, ack was lost,</i></b>
<a name="L623" href="source/net/ipv4/inet_connection_sock.c#L623">623</a> <b><i>         * rtt is high or nobody planned to ack (i.e. synflood).</i></b>
<a name="L624" href="source/net/ipv4/inet_connection_sock.c#L624">624</a> <b><i>         * When server is a bit loaded, queue is populated with old</i></b>
<a name="L625" href="source/net/ipv4/inet_connection_sock.c#L625">625</a> <b><i>         * open requests, reducing effective size of queue.</i></b>
<a name="L626" href="source/net/ipv4/inet_connection_sock.c#L626">626</a> <b><i>         * When server is well loaded, queue size reduces to zero</i></b>
<a name="L627" href="source/net/ipv4/inet_connection_sock.c#L627">627</a> <b><i>         * after several minutes of work. It is not synflood,</i></b>
<a name="L628" href="source/net/ipv4/inet_connection_sock.c#L628">628</a> <b><i>         * it is normal operation. The solution is pruning</i></b>
<a name="L629" href="source/net/ipv4/inet_connection_sock.c#L629">629</a> <b><i>         * too old entries overriding normal timeout, when</i></b>
<a name="L630" href="source/net/ipv4/inet_connection_sock.c#L630">630</a> <b><i>         * situation becomes dangerous.</i></b>
<a name="L631" href="source/net/ipv4/inet_connection_sock.c#L631">631</a> <b><i>         *</i></b>
<a name="L632" href="source/net/ipv4/inet_connection_sock.c#L632">632</a> <b><i>         * Essentially, we reserve half of room for young</i></b>
<a name="L633" href="source/net/ipv4/inet_connection_sock.c#L633">633</a> <b><i>         * embrions; and abort old ones without pity, if old</i></b>
<a name="L634" href="source/net/ipv4/inet_connection_sock.c#L634">634</a> <b><i>         * ones are about to clog our table.</i></b>
<a name="L635" href="source/net/ipv4/inet_connection_sock.c#L635">635</a> <b><i>         */</i></b>
<a name="L636" href="source/net/ipv4/inet_connection_sock.c#L636">636</a>         <a href="ident?i=qlen">qlen</a> = <a href="ident?i=listen_sock_qlen">listen_sock_qlen</a>(lopt);
<a name="L637" href="source/net/ipv4/inet_connection_sock.c#L637">637</a>         if (<a href="ident?i=qlen">qlen</a> &gt;&gt; (lopt-&gt;max_qlen_log - 1)) {
<a name="L638" href="source/net/ipv4/inet_connection_sock.c#L638">638</a>                 int young = <a href="ident?i=listen_sock_young">listen_sock_young</a>(lopt) &lt;&lt; 1;
<a name="L639" href="source/net/ipv4/inet_connection_sock.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/inet_connection_sock.c#L640">640</a>                 while (thresh &gt; 2) {
<a name="L641" href="source/net/ipv4/inet_connection_sock.c#L641">641</a>                         if (<a href="ident?i=qlen">qlen</a> &lt; young)
<a name="L642" href="source/net/ipv4/inet_connection_sock.c#L642">642</a>                                 break;
<a name="L643" href="source/net/ipv4/inet_connection_sock.c#L643">643</a>                         thresh--;
<a name="L644" href="source/net/ipv4/inet_connection_sock.c#L644">644</a>                         young &lt;&lt;= 1;
<a name="L645" href="source/net/ipv4/inet_connection_sock.c#L645">645</a>                 }
<a name="L646" href="source/net/ipv4/inet_connection_sock.c#L646">646</a>         }
<a name="L647" href="source/net/ipv4/inet_connection_sock.c#L647">647</a>         defer_accept = <a href="ident?i=READ_ONCE">READ_ONCE</a>(<a href="ident?i=queue">queue</a>-&gt;rskq_defer_accept);
<a name="L648" href="source/net/ipv4/inet_connection_sock.c#L648">648</a>         if (defer_accept)
<a name="L649" href="source/net/ipv4/inet_connection_sock.c#L649">649</a>                 max_retries = defer_accept;
<a name="L650" href="source/net/ipv4/inet_connection_sock.c#L650">650</a>         <a href="ident?i=syn_ack_recalc">syn_ack_recalc</a>(<a href="ident?i=req">req</a>, thresh, max_retries, defer_accept,
<a name="L651" href="source/net/ipv4/inet_connection_sock.c#L651">651</a>                        &amp;expire, &amp;<a href="ident?i=resend">resend</a>);
<a name="L652" href="source/net/ipv4/inet_connection_sock.c#L652">652</a>         <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;syn_ack_timeout(<a href="ident?i=req">req</a>);
<a name="L653" href="source/net/ipv4/inet_connection_sock.c#L653">653</a>         if (!expire &amp;&amp;
<a name="L654" href="source/net/ipv4/inet_connection_sock.c#L654">654</a>             (!<a href="ident?i=resend">resend</a> ||
<a name="L655" href="source/net/ipv4/inet_connection_sock.c#L655">655</a>              !<a href="ident?i=inet_rtx_syn_ack">inet_rtx_syn_ack</a>(sk_listener, <a href="ident?i=req">req</a>) ||
<a name="L656" href="source/net/ipv4/inet_connection_sock.c#L656">656</a>              <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;acked)) {
<a name="L657" href="source/net/ipv4/inet_connection_sock.c#L657">657</a>                 unsigned long timeo;
<a name="L658" href="source/net/ipv4/inet_connection_sock.c#L658">658</a> 
<a name="L659" href="source/net/ipv4/inet_connection_sock.c#L659">659</a>                 if (<a href="ident?i=req">req</a>-&gt;num_timeout++ == 0)
<a name="L660" href="source/net/ipv4/inet_connection_sock.c#L660">660</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;lopt-&gt;young_dec);
<a name="L661" href="source/net/ipv4/inet_connection_sock.c#L661">661</a>                 timeo = <a href="ident?i=min">min</a>(<a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a> &lt;&lt; <a href="ident?i=req">req</a>-&gt;num_timeout, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L662" href="source/net/ipv4/inet_connection_sock.c#L662">662</a>                 <a href="ident?i=mod_timer_pinned">mod_timer_pinned</a>(&amp;<a href="ident?i=req">req</a>-&gt;rsk_timer, <a href="ident?i=jiffies">jiffies</a> + timeo);
<a name="L663" href="source/net/ipv4/inet_connection_sock.c#L663">663</a>                 return;
<a name="L664" href="source/net/ipv4/inet_connection_sock.c#L664">664</a>         }
<a name="L665" href="source/net/ipv4/inet_connection_sock.c#L665">665</a>         <a href="ident?i=inet_csk_reqsk_queue_drop">inet_csk_reqsk_queue_drop</a>(sk_listener, <a href="ident?i=req">req</a>);
<a name="L666" href="source/net/ipv4/inet_connection_sock.c#L666">666</a>         <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L667" href="source/net/ipv4/inet_connection_sock.c#L667">667</a> }
<a name="L668" href="source/net/ipv4/inet_connection_sock.c#L668">668</a> 
<a name="L669" href="source/net/ipv4/inet_connection_sock.c#L669">669</a> void <a href="ident?i=reqsk_queue_hash_req">reqsk_queue_hash_req</a>(struct <a href="ident?i=request_sock_queue">request_sock_queue</a> *<a href="ident?i=queue">queue</a>,
<a name="L670" href="source/net/ipv4/inet_connection_sock.c#L670">670</a>                           <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a>, struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L671" href="source/net/ipv4/inet_connection_sock.c#L671">671</a>                           unsigned long <a href="ident?i=timeout">timeout</a>)
<a name="L672" href="source/net/ipv4/inet_connection_sock.c#L672">672</a> {
<a name="L673" href="source/net/ipv4/inet_connection_sock.c#L673">673</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt = <a href="ident?i=queue">queue</a>-&gt;listen_opt;
<a name="L674" href="source/net/ipv4/inet_connection_sock.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/inet_connection_sock.c#L675">675</a>         <a href="ident?i=req">req</a>-&gt;num_retrans = 0;
<a name="L676" href="source/net/ipv4/inet_connection_sock.c#L676">676</a>         <a href="ident?i=req">req</a>-&gt;num_timeout = 0;
<a name="L677" href="source/net/ipv4/inet_connection_sock.c#L677">677</a>         <a href="ident?i=req">req</a>-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L678" href="source/net/ipv4/inet_connection_sock.c#L678">678</a> 
<a name="L679" href="source/net/ipv4/inet_connection_sock.c#L679">679</a>         <b><i>/* before letting lookups find us, make sure all req fields</i></b>
<a name="L680" href="source/net/ipv4/inet_connection_sock.c#L680">680</a> <b><i>         * are committed to memory and refcnt initialized.</i></b>
<a name="L681" href="source/net/ipv4/inet_connection_sock.c#L681">681</a> <b><i>         */</i></b>
<a name="L682" href="source/net/ipv4/inet_connection_sock.c#L682">682</a>         <a href="ident?i=smp_wmb">smp_wmb</a>();
<a name="L683" href="source/net/ipv4/inet_connection_sock.c#L683">683</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=req">req</a>-&gt;<a href="ident?i=rsk_refcnt">rsk_refcnt</a>, 2);
<a name="L684" href="source/net/ipv4/inet_connection_sock.c#L684">684</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;<a href="ident?i=req">req</a>-&gt;rsk_timer, <a href="ident?i=reqsk_timer_handler">reqsk_timer_handler</a>, (unsigned long)<a href="ident?i=req">req</a>);
<a name="L685" href="source/net/ipv4/inet_connection_sock.c#L685">685</a>         <a href="ident?i=req">req</a>-&gt;<a href="ident?i=rsk_hash">rsk_hash</a> = <a href="ident?i=hash">hash</a>;
<a name="L686" href="source/net/ipv4/inet_connection_sock.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/inet_connection_sock.c#L687">687</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;syn_wait_lock);
<a name="L688" href="source/net/ipv4/inet_connection_sock.c#L688">688</a>         <a href="ident?i=req">req</a>-&gt;dl_next = lopt-&gt;syn_table[<a href="ident?i=hash">hash</a>];
<a name="L689" href="source/net/ipv4/inet_connection_sock.c#L689">689</a>         lopt-&gt;syn_table[<a href="ident?i=hash">hash</a>] = <a href="ident?i=req">req</a>;
<a name="L690" href="source/net/ipv4/inet_connection_sock.c#L690">690</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;syn_wait_lock);
<a name="L691" href="source/net/ipv4/inet_connection_sock.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/inet_connection_sock.c#L692">692</a>         <a href="ident?i=mod_timer_pinned">mod_timer_pinned</a>(&amp;<a href="ident?i=req">req</a>-&gt;rsk_timer, <a href="ident?i=jiffies">jiffies</a> + <a href="ident?i=timeout">timeout</a>);
<a name="L693" href="source/net/ipv4/inet_connection_sock.c#L693">693</a> }
<a name="L694" href="source/net/ipv4/inet_connection_sock.c#L694">694</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=reqsk_queue_hash_req">reqsk_queue_hash_req</a>);
<a name="L695" href="source/net/ipv4/inet_connection_sock.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/inet_connection_sock.c#L696">696</a> <b><i>/**</i></b>
<a name="L697" href="source/net/ipv4/inet_connection_sock.c#L697">697</a> <b><i> *      inet_csk_clone_lock - clone an inet socket, and lock its clone</i></b>
<a name="L698" href="source/net/ipv4/inet_connection_sock.c#L698">698</a> <b><i> *      @sk: the socket to clone</i></b>
<a name="L699" href="source/net/ipv4/inet_connection_sock.c#L699">699</a> <b><i> *      @req: request_sock</i></b>
<a name="L700" href="source/net/ipv4/inet_connection_sock.c#L700">700</a> <b><i> *      @priority: for allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)</i></b>
<a name="L701" href="source/net/ipv4/inet_connection_sock.c#L701">701</a> <b><i> *</i></b>
<a name="L702" href="source/net/ipv4/inet_connection_sock.c#L702">702</a> <b><i> *      Caller must unlock socket even in error path (bh_unlock_sock(newsk))</i></b>
<a name="L703" href="source/net/ipv4/inet_connection_sock.c#L703">703</a> <b><i> */</i></b>
<a name="L704" href="source/net/ipv4/inet_connection_sock.c#L704">704</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=inet_csk_clone_lock">inet_csk_clone_lock</a>(const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L705" href="source/net/ipv4/inet_connection_sock.c#L705">705</a>                                  const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L706" href="source/net/ipv4/inet_connection_sock.c#L706">706</a>                                  const <a href="ident?i=gfp_t">gfp_t</a> <a href="ident?i=priority">priority</a>)
<a name="L707" href="source/net/ipv4/inet_connection_sock.c#L707">707</a> {
<a name="L708" href="source/net/ipv4/inet_connection_sock.c#L708">708</a>         struct <a href="ident?i=sock">sock</a> *newsk = <a href="ident?i=sk_clone_lock">sk_clone_lock</a>(sk, <a href="ident?i=priority">priority</a>);
<a name="L709" href="source/net/ipv4/inet_connection_sock.c#L709">709</a> 
<a name="L710" href="source/net/ipv4/inet_connection_sock.c#L710">710</a>         if (newsk) {
<a name="L711" href="source/net/ipv4/inet_connection_sock.c#L711">711</a>                 struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *newicsk = <a href="ident?i=inet_csk">inet_csk</a>(newsk);
<a name="L712" href="source/net/ipv4/inet_connection_sock.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/inet_connection_sock.c#L713">713</a>                 newsk-&gt;<a href="ident?i=sk_state">sk_state</a> = TCP_SYN_RECV;
<a name="L714" href="source/net/ipv4/inet_connection_sock.c#L714">714</a>                 newicsk-&gt;icsk_bind_hash = <a href="ident?i=NULL">NULL</a>;
<a name="L715" href="source/net/ipv4/inet_connection_sock.c#L715">715</a> 
<a name="L716" href="source/net/ipv4/inet_connection_sock.c#L716">716</a>                 <a href="ident?i=inet_sk">inet_sk</a>(newsk)-&gt;<a href="ident?i=inet_dport">inet_dport</a> = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>;
<a name="L717" href="source/net/ipv4/inet_connection_sock.c#L717">717</a>                 <a href="ident?i=inet_sk">inet_sk</a>(newsk)-&gt;<a href="ident?i=inet_num">inet_num</a> = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_num">ir_num</a>;
<a name="L718" href="source/net/ipv4/inet_connection_sock.c#L718">718</a>                 <a href="ident?i=inet_sk">inet_sk</a>(newsk)-&gt;inet_sport = <a href="ident?i=htons">htons</a>(<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_num">ir_num</a>);
<a name="L719" href="source/net/ipv4/inet_connection_sock.c#L719">719</a>                 newsk-&gt;sk_write_space = <a href="ident?i=sk_stream_write_space">sk_stream_write_space</a>;
<a name="L720" href="source/net/ipv4/inet_connection_sock.c#L720">720</a> 
<a name="L721" href="source/net/ipv4/inet_connection_sock.c#L721">721</a>                 newsk-&gt;sk_mark = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;ir_mark;
<a name="L722" href="source/net/ipv4/inet_connection_sock.c#L722">722</a>                 <a href="ident?i=atomic64_set">atomic64_set</a>(&amp;newsk-&gt;<a href="ident?i=sk_cookie">sk_cookie</a>,
<a name="L723" href="source/net/ipv4/inet_connection_sock.c#L723">723</a>                              <a href="ident?i=atomic64_read">atomic64_read</a>(&amp;<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_cookie">ir_cookie</a>));
<a name="L724" href="source/net/ipv4/inet_connection_sock.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/inet_connection_sock.c#L725">725</a>                 newicsk-&gt;icsk_retransmits = 0;
<a name="L726" href="source/net/ipv4/inet_connection_sock.c#L726">726</a>                 newicsk-&gt;icsk_backoff     = 0;
<a name="L727" href="source/net/ipv4/inet_connection_sock.c#L727">727</a>                 newicsk-&gt;icsk_probes_out  = 0;
<a name="L728" href="source/net/ipv4/inet_connection_sock.c#L728">728</a> 
<a name="L729" href="source/net/ipv4/inet_connection_sock.c#L729">729</a>                 <b><i>/* Deinitialize accept_queue to trap illegal accesses. */</i></b>
<a name="L730" href="source/net/ipv4/inet_connection_sock.c#L730">730</a>                 <a href="ident?i=memset">memset</a>(&amp;newicsk-&gt;icsk_accept_queue, 0, sizeof(newicsk-&gt;icsk_accept_queue));
<a name="L731" href="source/net/ipv4/inet_connection_sock.c#L731">731</a> 
<a name="L732" href="source/net/ipv4/inet_connection_sock.c#L732">732</a>                 <a href="ident?i=security_inet_csk_clone">security_inet_csk_clone</a>(newsk, <a href="ident?i=req">req</a>);
<a name="L733" href="source/net/ipv4/inet_connection_sock.c#L733">733</a>         }
<a name="L734" href="source/net/ipv4/inet_connection_sock.c#L734">734</a>         return newsk;
<a name="L735" href="source/net/ipv4/inet_connection_sock.c#L735">735</a> }
<a name="L736" href="source/net/ipv4/inet_connection_sock.c#L736">736</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_clone_lock">inet_csk_clone_lock</a>);
<a name="L737" href="source/net/ipv4/inet_connection_sock.c#L737">737</a> 
<a name="L738" href="source/net/ipv4/inet_connection_sock.c#L738">738</a> <b><i>/*</i></b>
<a name="L739" href="source/net/ipv4/inet_connection_sock.c#L739">739</a> <b><i> * At this point, there should be no process reference to this</i></b>
<a name="L740" href="source/net/ipv4/inet_connection_sock.c#L740">740</a> <b><i> * socket, and thus no user references at all.  Therefore we</i></b>
<a name="L741" href="source/net/ipv4/inet_connection_sock.c#L741">741</a> <b><i> * can assume the socket waitqueue is inactive and nobody will</i></b>
<a name="L742" href="source/net/ipv4/inet_connection_sock.c#L742">742</a> <b><i> * try to jump onto it.</i></b>
<a name="L743" href="source/net/ipv4/inet_connection_sock.c#L743">743</a> <b><i> */</i></b>
<a name="L744" href="source/net/ipv4/inet_connection_sock.c#L744">744</a> void <a href="ident?i=inet_csk_destroy_sock">inet_csk_destroy_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L745" href="source/net/ipv4/inet_connection_sock.c#L745">745</a> {
<a name="L746" href="source/net/ipv4/inet_connection_sock.c#L746">746</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE);
<a name="L747" href="source/net/ipv4/inet_connection_sock.c#L747">747</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD));
<a name="L748" href="source/net/ipv4/inet_connection_sock.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/inet_connection_sock.c#L749">749</a>         <b><i>/* It cannot be in hash table! */</i></b>
<a name="L750" href="source/net/ipv4/inet_connection_sock.c#L750">750</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk));
<a name="L751" href="source/net/ipv4/inet_connection_sock.c#L751">751</a> 
<a name="L752" href="source/net/ipv4/inet_connection_sock.c#L752">752</a>         <b><i>/* If it has not 0 inet_sk(sk)-&gt;inet_num, it must be bound */</i></b>
<a name="L753" href="source/net/ipv4/inet_connection_sock.c#L753">753</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> &amp;&amp; !<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash);
<a name="L754" href="source/net/ipv4/inet_connection_sock.c#L754">754</a> 
<a name="L755" href="source/net/ipv4/inet_connection_sock.c#L755">755</a>         sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=destroy">destroy</a>(sk);
<a name="L756" href="source/net/ipv4/inet_connection_sock.c#L756">756</a> 
<a name="L757" href="source/net/ipv4/inet_connection_sock.c#L757">757</a>         <a href="ident?i=sk_stream_kill_queues">sk_stream_kill_queues</a>(sk);
<a name="L758" href="source/net/ipv4/inet_connection_sock.c#L758">758</a> 
<a name="L759" href="source/net/ipv4/inet_connection_sock.c#L759">759</a>         <a href="ident?i=xfrm_sk_free_policy">xfrm_sk_free_policy</a>(sk);
<a name="L760" href="source/net/ipv4/inet_connection_sock.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/inet_connection_sock.c#L761">761</a>         <a href="ident?i=sk_refcnt_debug_release">sk_refcnt_debug_release</a>(sk);
<a name="L762" href="source/net/ipv4/inet_connection_sock.c#L762">762</a> 
<a name="L763" href="source/net/ipv4/inet_connection_sock.c#L763">763</a>         <a href="ident?i=percpu_counter_dec">percpu_counter_dec</a>(sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;orphan_count);
<a name="L764" href="source/net/ipv4/inet_connection_sock.c#L764">764</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L765" href="source/net/ipv4/inet_connection_sock.c#L765">765</a> }
<a name="L766" href="source/net/ipv4/inet_connection_sock.c#L766">766</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_destroy_sock">inet_csk_destroy_sock</a>);
<a name="L767" href="source/net/ipv4/inet_connection_sock.c#L767">767</a> 
<a name="L768" href="source/net/ipv4/inet_connection_sock.c#L768">768</a> <b><i>/* This function allows to force a closure of a socket after the call to</i></b>
<a name="L769" href="source/net/ipv4/inet_connection_sock.c#L769">769</a> <b><i> * tcp/dccp_create_openreq_child().</i></b>
<a name="L770" href="source/net/ipv4/inet_connection_sock.c#L770">770</a> <b><i> */</i></b>
<a name="L771" href="source/net/ipv4/inet_connection_sock.c#L771">771</a> void <a href="ident?i=inet_csk_prepare_forced_close">inet_csk_prepare_forced_close</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L772" href="source/net/ipv4/inet_connection_sock.c#L772">772</a>         <a href="ident?i=__releases">__releases</a>(&amp;sk-&gt;sk_lock.slock)
<a name="L773" href="source/net/ipv4/inet_connection_sock.c#L773">773</a> {
<a name="L774" href="source/net/ipv4/inet_connection_sock.c#L774">774</a>         <b><i>/* sk_clone_lock locked the socket and set refcnt to 2 */</i></b>
<a name="L775" href="source/net/ipv4/inet_connection_sock.c#L775">775</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L776" href="source/net/ipv4/inet_connection_sock.c#L776">776</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L777" href="source/net/ipv4/inet_connection_sock.c#L777">777</a> 
<a name="L778" href="source/net/ipv4/inet_connection_sock.c#L778">778</a>         <b><i>/* The below has to be done to allow calling inet_csk_destroy_sock */</i></b>
<a name="L779" href="source/net/ipv4/inet_connection_sock.c#L779">779</a>         <a href="ident?i=sock_set_flag">sock_set_flag</a>(sk, SOCK_DEAD);
<a name="L780" href="source/net/ipv4/inet_connection_sock.c#L780">780</a>         <a href="ident?i=percpu_counter_inc">percpu_counter_inc</a>(sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;orphan_count);
<a name="L781" href="source/net/ipv4/inet_connection_sock.c#L781">781</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> = 0;
<a name="L782" href="source/net/ipv4/inet_connection_sock.c#L782">782</a> }
<a name="L783" href="source/net/ipv4/inet_connection_sock.c#L783">783</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_csk_prepare_forced_close">inet_csk_prepare_forced_close</a>);
<a name="L784" href="source/net/ipv4/inet_connection_sock.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/inet_connection_sock.c#L785">785</a> int <a href="ident?i=inet_csk_listen_start">inet_csk_listen_start</a>(struct <a href="ident?i=sock">sock</a> *sk, const int nr_table_entries)
<a name="L786" href="source/net/ipv4/inet_connection_sock.c#L786">786</a> {
<a name="L787" href="source/net/ipv4/inet_connection_sock.c#L787">787</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L788" href="source/net/ipv4/inet_connection_sock.c#L788">788</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L789" href="source/net/ipv4/inet_connection_sock.c#L789">789</a>         int <a href="ident?i=rc">rc</a> = <a href="ident?i=reqsk_queue_alloc">reqsk_queue_alloc</a>(&amp;icsk-&gt;icsk_accept_queue, nr_table_entries);
<a name="L790" href="source/net/ipv4/inet_connection_sock.c#L790">790</a> 
<a name="L791" href="source/net/ipv4/inet_connection_sock.c#L791">791</a>         if (<a href="ident?i=rc">rc</a> != 0)
<a name="L792" href="source/net/ipv4/inet_connection_sock.c#L792">792</a>                 return <a href="ident?i=rc">rc</a>;
<a name="L793" href="source/net/ipv4/inet_connection_sock.c#L793">793</a> 
<a name="L794" href="source/net/ipv4/inet_connection_sock.c#L794">794</a>         sk-&gt;sk_max_ack_backlog = 0;
<a name="L795" href="source/net/ipv4/inet_connection_sock.c#L795">795</a>         sk-&gt;sk_ack_backlog = 0;
<a name="L796" href="source/net/ipv4/inet_connection_sock.c#L796">796</a>         <a href="ident?i=inet_csk_delack_init">inet_csk_delack_init</a>(sk);
<a name="L797" href="source/net/ipv4/inet_connection_sock.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/inet_connection_sock.c#L798">798</a>         <b><i>/* There is race window here: we announce ourselves listening,</i></b>
<a name="L799" href="source/net/ipv4/inet_connection_sock.c#L799">799</a> <b><i>         * but this transition is still not validated by get_port().</i></b>
<a name="L800" href="source/net/ipv4/inet_connection_sock.c#L800">800</a> <b><i>         * It is OK, because this socket enters to hash table only</i></b>
<a name="L801" href="source/net/ipv4/inet_connection_sock.c#L801">801</a> <b><i>         * after validation is complete.</i></b>
<a name="L802" href="source/net/ipv4/inet_connection_sock.c#L802">802</a> <b><i>         */</i></b>
<a name="L803" href="source/net/ipv4/inet_connection_sock.c#L803">803</a>         sk-&gt;<a href="ident?i=sk_state">sk_state</a> = TCP_LISTEN;
<a name="L804" href="source/net/ipv4/inet_connection_sock.c#L804">804</a>         if (!sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=get_port">get_port</a>(sk, inet-&gt;<a href="ident?i=inet_num">inet_num</a>)) {
<a name="L805" href="source/net/ipv4/inet_connection_sock.c#L805">805</a>                 inet-&gt;inet_sport = <a href="ident?i=htons">htons</a>(inet-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L806" href="source/net/ipv4/inet_connection_sock.c#L806">806</a> 
<a name="L807" href="source/net/ipv4/inet_connection_sock.c#L807">807</a>                 <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
<a name="L808" href="source/net/ipv4/inet_connection_sock.c#L808">808</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=hash">hash</a>(sk);
<a name="L809" href="source/net/ipv4/inet_connection_sock.c#L809">809</a> 
<a name="L810" href="source/net/ipv4/inet_connection_sock.c#L810">810</a>                 return 0;
<a name="L811" href="source/net/ipv4/inet_connection_sock.c#L811">811</a>         }
<a name="L812" href="source/net/ipv4/inet_connection_sock.c#L812">812</a> 
<a name="L813" href="source/net/ipv4/inet_connection_sock.c#L813">813</a>         sk-&gt;<a href="ident?i=sk_state">sk_state</a> = TCP_CLOSE;
<a name="L814" href="source/net/ipv4/inet_connection_sock.c#L814">814</a>         <a href="ident?i=__reqsk_queue_destroy">__reqsk_queue_destroy</a>(&amp;icsk-&gt;icsk_accept_queue);
<a name="L815" href="source/net/ipv4/inet_connection_sock.c#L815">815</a>         return -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L816" href="source/net/ipv4/inet_connection_sock.c#L816">816</a> }
<a name="L817" href="source/net/ipv4/inet_connection_sock.c#L817">817</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_listen_start">inet_csk_listen_start</a>);
<a name="L818" href="source/net/ipv4/inet_connection_sock.c#L818">818</a> 
<a name="L819" href="source/net/ipv4/inet_connection_sock.c#L819">819</a> <b><i>/*</i></b>
<a name="L820" href="source/net/ipv4/inet_connection_sock.c#L820">820</a> <b><i> *      This routine closes sockets which have been at least partially</i></b>
<a name="L821" href="source/net/ipv4/inet_connection_sock.c#L821">821</a> <b><i> *      opened, but not yet accepted.</i></b>
<a name="L822" href="source/net/ipv4/inet_connection_sock.c#L822">822</a> <b><i> */</i></b>
<a name="L823" href="source/net/ipv4/inet_connection_sock.c#L823">823</a> void <a href="ident?i=inet_csk_listen_stop">inet_csk_listen_stop</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L824" href="source/net/ipv4/inet_connection_sock.c#L824">824</a> {
<a name="L825" href="source/net/ipv4/inet_connection_sock.c#L825">825</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L826" href="source/net/ipv4/inet_connection_sock.c#L826">826</a>         struct <a href="ident?i=request_sock_queue">request_sock_queue</a> *<a href="ident?i=queue">queue</a> = &amp;icsk-&gt;icsk_accept_queue;
<a name="L827" href="source/net/ipv4/inet_connection_sock.c#L827">827</a>         struct <a href="ident?i=request_sock">request_sock</a> *acc_req;
<a name="L828" href="source/net/ipv4/inet_connection_sock.c#L828">828</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L829" href="source/net/ipv4/inet_connection_sock.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/inet_connection_sock.c#L830">830</a>         <b><i>/* make all the listen_opt local to us */</i></b>
<a name="L831" href="source/net/ipv4/inet_connection_sock.c#L831">831</a>         acc_req = <a href="ident?i=reqsk_queue_yank_acceptq">reqsk_queue_yank_acceptq</a>(<a href="ident?i=queue">queue</a>);
<a name="L832" href="source/net/ipv4/inet_connection_sock.c#L832">832</a> 
<a name="L833" href="source/net/ipv4/inet_connection_sock.c#L833">833</a>         <b><i>/* Following specs, it would be better either to send FIN</i></b>
<a name="L834" href="source/net/ipv4/inet_connection_sock.c#L834">834</a> <b><i>         * (and enter FIN-WAIT-1, it is normal close)</i></b>
<a name="L835" href="source/net/ipv4/inet_connection_sock.c#L835">835</a> <b><i>         * or to send active reset (abort).</i></b>
<a name="L836" href="source/net/ipv4/inet_connection_sock.c#L836">836</a> <b><i>         * Certainly, it is pretty dangerous while synflood, but it is</i></b>
<a name="L837" href="source/net/ipv4/inet_connection_sock.c#L837">837</a> <b><i>         * bad justification for our negligence 8)</i></b>
<a name="L838" href="source/net/ipv4/inet_connection_sock.c#L838">838</a> <b><i>         * To be honest, we are not able to make either</i></b>
<a name="L839" href="source/net/ipv4/inet_connection_sock.c#L839">839</a> <b><i>         * of the variants now.                 --ANK</i></b>
<a name="L840" href="source/net/ipv4/inet_connection_sock.c#L840">840</a> <b><i>         */</i></b>
<a name="L841" href="source/net/ipv4/inet_connection_sock.c#L841">841</a>         <a href="ident?i=reqsk_queue_destroy">reqsk_queue_destroy</a>(<a href="ident?i=queue">queue</a>);
<a name="L842" href="source/net/ipv4/inet_connection_sock.c#L842">842</a> 
<a name="L843" href="source/net/ipv4/inet_connection_sock.c#L843">843</a>         while ((<a href="ident?i=req">req</a> = acc_req) != <a href="ident?i=NULL">NULL</a>) {
<a name="L844" href="source/net/ipv4/inet_connection_sock.c#L844">844</a>                 struct <a href="ident?i=sock">sock</a> *<a href="ident?i=child">child</a> = <a href="ident?i=req">req</a>-&gt;sk;
<a name="L845" href="source/net/ipv4/inet_connection_sock.c#L845">845</a> 
<a name="L846" href="source/net/ipv4/inet_connection_sock.c#L846">846</a>                 acc_req = <a href="ident?i=req">req</a>-&gt;dl_next;
<a name="L847" href="source/net/ipv4/inet_connection_sock.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/inet_connection_sock.c#L848">848</a>                 <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L849" href="source/net/ipv4/inet_connection_sock.c#L849">849</a>                 <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(<a href="ident?i=child">child</a>);
<a name="L850" href="source/net/ipv4/inet_connection_sock.c#L850">850</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(<a href="ident?i=child">child</a>));
<a name="L851" href="source/net/ipv4/inet_connection_sock.c#L851">851</a>                 <a href="ident?i=sock_hold">sock_hold</a>(<a href="ident?i=child">child</a>);
<a name="L852" href="source/net/ipv4/inet_connection_sock.c#L852">852</a> 
<a name="L853" href="source/net/ipv4/inet_connection_sock.c#L853">853</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(<a href="ident?i=child">child</a>, <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a>);
<a name="L854" href="source/net/ipv4/inet_connection_sock.c#L854">854</a> 
<a name="L855" href="source/net/ipv4/inet_connection_sock.c#L855">855</a>                 <a href="ident?i=sock_orphan">sock_orphan</a>(<a href="ident?i=child">child</a>);
<a name="L856" href="source/net/ipv4/inet_connection_sock.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/inet_connection_sock.c#L857">857</a>                 <a href="ident?i=percpu_counter_inc">percpu_counter_inc</a>(sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;orphan_count);
<a name="L858" href="source/net/ipv4/inet_connection_sock.c#L858">858</a> 
<a name="L859" href="source/net/ipv4/inet_connection_sock.c#L859">859</a>                 if (sk-&gt;sk_protocol == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> &amp;&amp; <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;tfo_listener) {
<a name="L860" href="source/net/ipv4/inet_connection_sock.c#L860">860</a>                         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tcp_sk">tcp_sk</a>(<a href="ident?i=child">child</a>)-&gt;fastopen_rsk != <a href="ident?i=req">req</a>);
<a name="L861" href="source/net/ipv4/inet_connection_sock.c#L861">861</a>                         <a href="ident?i=BUG_ON">BUG_ON</a>(sk != <a href="ident?i=req">req</a>-&gt;rsk_listener);
<a name="L862" href="source/net/ipv4/inet_connection_sock.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/inet_connection_sock.c#L863">863</a>                         <b><i>/* Paranoid, to prevent race condition if</i></b>
<a name="L864" href="source/net/ipv4/inet_connection_sock.c#L864">864</a> <b><i>                         * an inbound pkt destined for child is</i></b>
<a name="L865" href="source/net/ipv4/inet_connection_sock.c#L865">865</a> <b><i>                         * blocked by sock lock in tcp_v4_rcv().</i></b>
<a name="L866" href="source/net/ipv4/inet_connection_sock.c#L866">866</a> <b><i>                         * Also to satisfy an assertion in</i></b>
<a name="L867" href="source/net/ipv4/inet_connection_sock.c#L867">867</a> <b><i>                         * tcp_v4_destroy_sock().</i></b>
<a name="L868" href="source/net/ipv4/inet_connection_sock.c#L868">868</a> <b><i>                         */</i></b>
<a name="L869" href="source/net/ipv4/inet_connection_sock.c#L869">869</a>                         <a href="ident?i=tcp_sk">tcp_sk</a>(<a href="ident?i=child">child</a>)-&gt;fastopen_rsk = <a href="ident?i=NULL">NULL</a>;
<a name="L870" href="source/net/ipv4/inet_connection_sock.c#L870">870</a>                 }
<a name="L871" href="source/net/ipv4/inet_connection_sock.c#L871">871</a>                 <a href="ident?i=inet_csk_destroy_sock">inet_csk_destroy_sock</a>(<a href="ident?i=child">child</a>);
<a name="L872" href="source/net/ipv4/inet_connection_sock.c#L872">872</a> 
<a name="L873" href="source/net/ipv4/inet_connection_sock.c#L873">873</a>                 <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(<a href="ident?i=child">child</a>);
<a name="L874" href="source/net/ipv4/inet_connection_sock.c#L874">874</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L875" href="source/net/ipv4/inet_connection_sock.c#L875">875</a>                 <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=child">child</a>);
<a name="L876" href="source/net/ipv4/inet_connection_sock.c#L876">876</a> 
<a name="L877" href="source/net/ipv4/inet_connection_sock.c#L877">877</a>                 <a href="ident?i=sk_acceptq_removed">sk_acceptq_removed</a>(sk);
<a name="L878" href="source/net/ipv4/inet_connection_sock.c#L878">878</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L879" href="source/net/ipv4/inet_connection_sock.c#L879">879</a>         }
<a name="L880" href="source/net/ipv4/inet_connection_sock.c#L880">880</a>         if (<a href="ident?i=queue">queue</a>-&gt;fastopenq) {
<a name="L881" href="source/net/ipv4/inet_connection_sock.c#L881">881</a>                 <b><i>/* Free all the reqs queued in rskq_rst_head. */</i></b>
<a name="L882" href="source/net/ipv4/inet_connection_sock.c#L882">882</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L883" href="source/net/ipv4/inet_connection_sock.c#L883">883</a>                 acc_req = <a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;rskq_rst_head;
<a name="L884" href="source/net/ipv4/inet_connection_sock.c#L884">884</a>                 <a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;rskq_rst_head = <a href="ident?i=NULL">NULL</a>;
<a name="L885" href="source/net/ipv4/inet_connection_sock.c#L885">885</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=queue">queue</a>-&gt;fastopenq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L886" href="source/net/ipv4/inet_connection_sock.c#L886">886</a>                 while ((<a href="ident?i=req">req</a> = acc_req) != <a href="ident?i=NULL">NULL</a>) {
<a name="L887" href="source/net/ipv4/inet_connection_sock.c#L887">887</a>                         acc_req = <a href="ident?i=req">req</a>-&gt;dl_next;
<a name="L888" href="source/net/ipv4/inet_connection_sock.c#L888">888</a>                         <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L889" href="source/net/ipv4/inet_connection_sock.c#L889">889</a>                 }
<a name="L890" href="source/net/ipv4/inet_connection_sock.c#L890">890</a>         }
<a name="L891" href="source/net/ipv4/inet_connection_sock.c#L891">891</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(sk-&gt;sk_ack_backlog);
<a name="L892" href="source/net/ipv4/inet_connection_sock.c#L892">892</a> }
<a name="L893" href="source/net/ipv4/inet_connection_sock.c#L893">893</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_listen_stop">inet_csk_listen_stop</a>);
<a name="L894" href="source/net/ipv4/inet_connection_sock.c#L894">894</a> 
<a name="L895" href="source/net/ipv4/inet_connection_sock.c#L895">895</a> void <a href="ident?i=inet_csk_addr2sockaddr">inet_csk_addr2sockaddr</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>)
<a name="L896" href="source/net/ipv4/inet_connection_sock.c#L896">896</a> {
<a name="L897" href="source/net/ipv4/inet_connection_sock.c#L897">897</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=sin">sin</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)<a href="ident?i=uaddr">uaddr</a>;
<a name="L898" href="source/net/ipv4/inet_connection_sock.c#L898">898</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L899" href="source/net/ipv4/inet_connection_sock.c#L899">899</a> 
<a name="L900" href="source/net/ipv4/inet_connection_sock.c#L900">900</a>         <a href="ident?i=sin">sin</a>-&gt;sin_family         = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L901" href="source/net/ipv4/inet_connection_sock.c#L901">901</a>         <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr    = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L902" href="source/net/ipv4/inet_connection_sock.c#L902">902</a>         <a href="ident?i=sin">sin</a>-&gt;sin_port           = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L903" href="source/net/ipv4/inet_connection_sock.c#L903">903</a> }
<a name="L904" href="source/net/ipv4/inet_connection_sock.c#L904">904</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_addr2sockaddr">inet_csk_addr2sockaddr</a>);
<a name="L905" href="source/net/ipv4/inet_connection_sock.c#L905">905</a> 
<a name="L906" href="source/net/ipv4/inet_connection_sock.c#L906">906</a> #ifdef CONFIG_COMPAT
<a name="L907" href="source/net/ipv4/inet_connection_sock.c#L907">907</a> int <a href="ident?i=inet_csk_compat_getsockopt">inet_csk_compat_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L908" href="source/net/ipv4/inet_connection_sock.c#L908">908</a>                                char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L909" href="source/net/ipv4/inet_connection_sock.c#L909">909</a> {
<a name="L910" href="source/net/ipv4/inet_connection_sock.c#L910">910</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L911" href="source/net/ipv4/inet_connection_sock.c#L911">911</a> 
<a name="L912" href="source/net/ipv4/inet_connection_sock.c#L912">912</a>         if (icsk-&gt;icsk_af_ops-&gt;compat_getsockopt)
<a name="L913" href="source/net/ipv4/inet_connection_sock.c#L913">913</a>                 return icsk-&gt;icsk_af_ops-&gt;compat_getsockopt(sk, <a href="ident?i=level">level</a>, optname,
<a name="L914" href="source/net/ipv4/inet_connection_sock.c#L914">914</a>                                                             optval, <a href="ident?i=optlen">optlen</a>);
<a name="L915" href="source/net/ipv4/inet_connection_sock.c#L915">915</a>         return icsk-&gt;icsk_af_ops-&gt;getsockopt(sk, <a href="ident?i=level">level</a>, optname,
<a name="L916" href="source/net/ipv4/inet_connection_sock.c#L916">916</a>                                              optval, <a href="ident?i=optlen">optlen</a>);
<a name="L917" href="source/net/ipv4/inet_connection_sock.c#L917">917</a> }
<a name="L918" href="source/net/ipv4/inet_connection_sock.c#L918">918</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_compat_getsockopt">inet_csk_compat_getsockopt</a>);
<a name="L919" href="source/net/ipv4/inet_connection_sock.c#L919">919</a> 
<a name="L920" href="source/net/ipv4/inet_connection_sock.c#L920">920</a> int <a href="ident?i=inet_csk_compat_setsockopt">inet_csk_compat_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L921" href="source/net/ipv4/inet_connection_sock.c#L921">921</a>                                char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L922" href="source/net/ipv4/inet_connection_sock.c#L922">922</a> {
<a name="L923" href="source/net/ipv4/inet_connection_sock.c#L923">923</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L924" href="source/net/ipv4/inet_connection_sock.c#L924">924</a> 
<a name="L925" href="source/net/ipv4/inet_connection_sock.c#L925">925</a>         if (icsk-&gt;icsk_af_ops-&gt;compat_setsockopt)
<a name="L926" href="source/net/ipv4/inet_connection_sock.c#L926">926</a>                 return icsk-&gt;icsk_af_ops-&gt;compat_setsockopt(sk, <a href="ident?i=level">level</a>, optname,
<a name="L927" href="source/net/ipv4/inet_connection_sock.c#L927">927</a>                                                             optval, <a href="ident?i=optlen">optlen</a>);
<a name="L928" href="source/net/ipv4/inet_connection_sock.c#L928">928</a>         return icsk-&gt;icsk_af_ops-&gt;<a href="ident?i=setsockopt">setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname,
<a name="L929" href="source/net/ipv4/inet_connection_sock.c#L929">929</a>                                              optval, <a href="ident?i=optlen">optlen</a>);
<a name="L930" href="source/net/ipv4/inet_connection_sock.c#L930">930</a> }
<a name="L931" href="source/net/ipv4/inet_connection_sock.c#L931">931</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_compat_setsockopt">inet_csk_compat_setsockopt</a>);
<a name="L932" href="source/net/ipv4/inet_connection_sock.c#L932">932</a> #endif
<a name="L933" href="source/net/ipv4/inet_connection_sock.c#L933">933</a> 
<a name="L934" href="source/net/ipv4/inet_connection_sock.c#L934">934</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=inet_csk_rebuild_route">inet_csk_rebuild_route</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=flowi">flowi</a> *fl)
<a name="L935" href="source/net/ipv4/inet_connection_sock.c#L935">935</a> {
<a name="L936" href="source/net/ipv4/inet_connection_sock.c#L936">936</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L937" href="source/net/ipv4/inet_connection_sock.c#L937">937</a>         const struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L938" href="source/net/ipv4/inet_connection_sock.c#L938">938</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L939" href="source/net/ipv4/inet_connection_sock.c#L939">939</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L940" href="source/net/ipv4/inet_connection_sock.c#L940">940</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L941" href="source/net/ipv4/inet_connection_sock.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/inet_connection_sock.c#L942">942</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L943" href="source/net/ipv4/inet_connection_sock.c#L943">943</a>         inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L944" href="source/net/ipv4/inet_connection_sock.c#L944">944</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L945" href="source/net/ipv4/inet_connection_sock.c#L945">945</a>                 <a href="ident?i=daddr">daddr</a> = inet_opt-&gt;opt.faddr;
<a name="L946" href="source/net/ipv4/inet_connection_sock.c#L946">946</a>         fl4 = &amp;fl-&gt;u.ip4;
<a name="L947" href="source/net/ipv4/inet_connection_sock.c#L947">947</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=sock_net">sock_net</a>(sk), fl4, sk, <a href="ident?i=daddr">daddr</a>,
<a name="L948" href="source/net/ipv4/inet_connection_sock.c#L948">948</a>                                    inet-&gt;inet_saddr, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>,
<a name="L949" href="source/net/ipv4/inet_connection_sock.c#L949">949</a>                                    inet-&gt;inet_sport, sk-&gt;sk_protocol,
<a name="L950" href="source/net/ipv4/inet_connection_sock.c#L950">950</a>                                    <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L951" href="source/net/ipv4/inet_connection_sock.c#L951">951</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L952" href="source/net/ipv4/inet_connection_sock.c#L952">952</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L953" href="source/net/ipv4/inet_connection_sock.c#L953">953</a>         if (<a href="ident?i=rt">rt</a>)
<a name="L954" href="source/net/ipv4/inet_connection_sock.c#L954">954</a>                 <a href="ident?i=sk_setup_caps">sk_setup_caps</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L955" href="source/net/ipv4/inet_connection_sock.c#L955">955</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L956" href="source/net/ipv4/inet_connection_sock.c#L956">956</a> 
<a name="L957" href="source/net/ipv4/inet_connection_sock.c#L957">957</a>         return &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L958" href="source/net/ipv4/inet_connection_sock.c#L958">958</a> }
<a name="L959" href="source/net/ipv4/inet_connection_sock.c#L959">959</a> 
<a name="L960" href="source/net/ipv4/inet_connection_sock.c#L960">960</a> struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=inet_csk_update_pmtu">inet_csk_update_pmtu</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L961" href="source/net/ipv4/inet_connection_sock.c#L961">961</a> {
<a name="L962" href="source/net/ipv4/inet_connection_sock.c#L962">962</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_check">__sk_dst_check</a>(sk, 0);
<a name="L963" href="source/net/ipv4/inet_connection_sock.c#L963">963</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L964" href="source/net/ipv4/inet_connection_sock.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/inet_connection_sock.c#L965">965</a>         if (!<a href="ident?i=dst">dst</a>) {
<a name="L966" href="source/net/ipv4/inet_connection_sock.c#L966">966</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=inet_csk_rebuild_route">inet_csk_rebuild_route</a>(sk, &amp;inet-&gt;cork.fl);
<a name="L967" href="source/net/ipv4/inet_connection_sock.c#L967">967</a>                 if (!<a href="ident?i=dst">dst</a>)
<a name="L968" href="source/net/ipv4/inet_connection_sock.c#L968">968</a>                         goto <a href="ident?i=out">out</a>;
<a name="L969" href="source/net/ipv4/inet_connection_sock.c#L969">969</a>         }
<a name="L970" href="source/net/ipv4/inet_connection_sock.c#L970">970</a>         <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;update_pmtu(<a href="ident?i=dst">dst</a>, sk, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=mtu">mtu</a>);
<a name="L971" href="source/net/ipv4/inet_connection_sock.c#L971">971</a> 
<a name="L972" href="source/net/ipv4/inet_connection_sock.c#L972">972</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_check">__sk_dst_check</a>(sk, 0);
<a name="L973" href="source/net/ipv4/inet_connection_sock.c#L973">973</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L974" href="source/net/ipv4/inet_connection_sock.c#L974">974</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=inet_csk_rebuild_route">inet_csk_rebuild_route</a>(sk, &amp;inet-&gt;cork.fl);
<a name="L975" href="source/net/ipv4/inet_connection_sock.c#L975">975</a> <a href="ident?i=out">out</a>:
<a name="L976" href="source/net/ipv4/inet_connection_sock.c#L976">976</a>         return <a href="ident?i=dst">dst</a>;
<a name="L977" href="source/net/ipv4/inet_connection_sock.c#L977">977</a> }
<a name="L978" href="source/net/ipv4/inet_connection_sock.c#L978">978</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_csk_update_pmtu">inet_csk_update_pmtu</a>);
<a name="L979" href="source/net/ipv4/inet_connection_sock.c#L979">979</a> </pre></div><p>
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
