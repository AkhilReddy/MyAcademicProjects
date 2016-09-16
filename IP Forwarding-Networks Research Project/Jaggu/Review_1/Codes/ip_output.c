<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_output.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_output.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_output.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_output.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_output.c">ip_output.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_output.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_output.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ip_output.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ip_output.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ip_output.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_output.c#L6">6</a> <b><i> *              The Internet Protocol (IP) output module.</i></b>
  <a name="L7" href="source/net/ipv4/ip_output.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_output.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/ip_output.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/ip_output.c#L10">10</a> <b><i> *              Donald Becker, &lt;becker@super.org&gt;</i></b>
 <a name="L11" href="source/net/ipv4/ip_output.c#L11">11</a> <b><i> *              Alan Cox, &lt;Alan.Cox@linux.org&gt;</i></b>
 <a name="L12" href="source/net/ipv4/ip_output.c#L12">12</a> <b><i> *              Richard Underwood</i></b>
 <a name="L13" href="source/net/ipv4/ip_output.c#L13">13</a> <b><i> *              Stefan Becker, &lt;stefanb@yello.ping.de&gt;</i></b>
 <a name="L14" href="source/net/ipv4/ip_output.c#L14">14</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L15" href="source/net/ipv4/ip_output.c#L15">15</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L16" href="source/net/ipv4/ip_output.c#L16">16</a> <b><i> *              Hirokazu Takahashi, &lt;taka@valinux.co.jp&gt;</i></b>
 <a name="L17" href="source/net/ipv4/ip_output.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/ip_output.c#L18">18</a> <b><i> *      See ip_input.c for original log</i></b>
 <a name="L19" href="source/net/ipv4/ip_output.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/ip_output.c#L20">20</a> <b><i> *      Fixes:</i></b>
 <a name="L21" href="source/net/ipv4/ip_output.c#L21">21</a> <b><i> *              Alan Cox        :       Missing nonblock feature in ip_build_xmit.</i></b>
 <a name="L22" href="source/net/ipv4/ip_output.c#L22">22</a> <b><i> *              Mike Kilburn    :       htons() missing in ip_build_xmit.</i></b>
 <a name="L23" href="source/net/ipv4/ip_output.c#L23">23</a> <b><i> *              Bradford Johnson:       Fix faulty handling of some frames when</i></b>
 <a name="L24" href="source/net/ipv4/ip_output.c#L24">24</a> <b><i> *                                      no route is found.</i></b>
 <a name="L25" href="source/net/ipv4/ip_output.c#L25">25</a> <b><i> *              Alexander Demenshin:    Missing sk/skb free in ip_queue_xmit</i></b>
 <a name="L26" href="source/net/ipv4/ip_output.c#L26">26</a> <b><i> *                                      (in case if packet not accepted by</i></b>
 <a name="L27" href="source/net/ipv4/ip_output.c#L27">27</a> <b><i> *                                      output firewall rules)</i></b>
 <a name="L28" href="source/net/ipv4/ip_output.c#L28">28</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L29" href="source/net/ipv4/ip_output.c#L29">29</a> <b><i> *              Alexey Kuznetsov:       use new route cache</i></b>
 <a name="L30" href="source/net/ipv4/ip_output.c#L30">30</a> <b><i> *              Andi Kleen:             Fix broken PMTU recovery and remove</i></b>
 <a name="L31" href="source/net/ipv4/ip_output.c#L31">31</a> <b><i> *                                      some redundant tests.</i></b>
 <a name="L32" href="source/net/ipv4/ip_output.c#L32">32</a> <b><i> *      Vitaly E. Lavrov        :       Transparent proxy revived after year coma.</i></b>
 <a name="L33" href="source/net/ipv4/ip_output.c#L33">33</a> <b><i> *              Andi Kleen      :       Replace ip_reply with ip_send_reply.</i></b>
 <a name="L34" href="source/net/ipv4/ip_output.c#L34">34</a> <b><i> *              Andi Kleen      :       Split fast and slow ip_build_xmit path</i></b>
 <a name="L35" href="source/net/ipv4/ip_output.c#L35">35</a> <b><i> *                                      for decreased register pressure on x86</i></b>
 <a name="L36" href="source/net/ipv4/ip_output.c#L36">36</a> <b><i> *                                      and more readibility.</i></b>
 <a name="L37" href="source/net/ipv4/ip_output.c#L37">37</a> <b><i> *              Marc Boucher    :       When call_out_firewall returns FW_QUEUE,</i></b>
 <a name="L38" href="source/net/ipv4/ip_output.c#L38">38</a> <b><i> *                                      silently drop skb instead of failing with -EPERM.</i></b>
 <a name="L39" href="source/net/ipv4/ip_output.c#L39">39</a> <b><i> *              Detlev Wengorz  :       Copy protocol for fragments.</i></b>
 <a name="L40" href="source/net/ipv4/ip_output.c#L40">40</a> <b><i> *              Hirokazu Takahashi:     HW checksumming for outgoing UDP</i></b>
 <a name="L41" href="source/net/ipv4/ip_output.c#L41">41</a> <b><i> *                                      datagrams.</i></b>
 <a name="L42" href="source/net/ipv4/ip_output.c#L42">42</a> <b><i> *              Hirokazu Takahashi:     sendfile() on UDP works now.</i></b>
 <a name="L43" href="source/net/ipv4/ip_output.c#L43">43</a> <b><i> */</i></b>
 <a name="L44" href="source/net/ipv4/ip_output.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/ip_output.c#L45">45</a> #include &lt;asm/uaccess.h&gt;
 <a name="L46" href="source/net/ipv4/ip_output.c#L46">46</a> #include &lt;linux/module.h&gt;
 <a name="L47" href="source/net/ipv4/ip_output.c#L47">47</a> #include &lt;linux/types.h&gt;
 <a name="L48" href="source/net/ipv4/ip_output.c#L48">48</a> #include &lt;linux/kernel.h&gt;
 <a name="L49" href="source/net/ipv4/ip_output.c#L49">49</a> #include &lt;linux/mm.h&gt;
 <a name="L50" href="source/net/ipv4/ip_output.c#L50">50</a> #include &lt;linux/string.h&gt;
 <a name="L51" href="source/net/ipv4/ip_output.c#L51">51</a> #include &lt;linux/errno.h&gt;
 <a name="L52" href="source/net/ipv4/ip_output.c#L52">52</a> #include &lt;linux/highmem.h&gt;
 <a name="L53" href="source/net/ipv4/ip_output.c#L53">53</a> #include &lt;linux/slab.h&gt;
 <a name="L54" href="source/net/ipv4/ip_output.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/ip_output.c#L55">55</a> #include &lt;linux/socket.h&gt;
 <a name="L56" href="source/net/ipv4/ip_output.c#L56">56</a> #include &lt;linux/sockios.h&gt;
 <a name="L57" href="source/net/ipv4/ip_output.c#L57">57</a> #include &lt;linux/in.h&gt;
 <a name="L58" href="source/net/ipv4/ip_output.c#L58">58</a> #include &lt;linux/inet.h&gt;
 <a name="L59" href="source/net/ipv4/ip_output.c#L59">59</a> #include &lt;linux/netdevice.h&gt;
 <a name="L60" href="source/net/ipv4/ip_output.c#L60">60</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L61" href="source/net/ipv4/ip_output.c#L61">61</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L62" href="source/net/ipv4/ip_output.c#L62">62</a> #include &lt;linux/stat.h&gt;
 <a name="L63" href="source/net/ipv4/ip_output.c#L63">63</a> #include &lt;linux/init.h&gt;
 <a name="L64" href="source/net/ipv4/ip_output.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/ip_output.c#L65">65</a> #include &lt;net/snmp.h&gt;
 <a name="L66" href="source/net/ipv4/ip_output.c#L66">66</a> #include &lt;net/ip.h&gt;
 <a name="L67" href="source/net/ipv4/ip_output.c#L67">67</a> #include &lt;net/protocol.h&gt;
 <a name="L68" href="source/net/ipv4/ip_output.c#L68">68</a> #include &lt;net/route.h&gt;
 <a name="L69" href="source/net/ipv4/ip_output.c#L69">69</a> #include &lt;net/xfrm.h&gt;
 <a name="L70" href="source/net/ipv4/ip_output.c#L70">70</a> #include &lt;linux/skbuff.h&gt;
 <a name="L71" href="source/net/ipv4/ip_output.c#L71">71</a> #include &lt;net/sock.h&gt;
 <a name="L72" href="source/net/ipv4/ip_output.c#L72">72</a> #include &lt;net/arp.h&gt;
 <a name="L73" href="source/net/ipv4/ip_output.c#L73">73</a> #include &lt;net/icmp.h&gt;
 <a name="L74" href="source/net/ipv4/ip_output.c#L74">74</a> #include &lt;net/checksum.h&gt;
 <a name="L75" href="source/net/ipv4/ip_output.c#L75">75</a> #include &lt;net/inetpeer.h&gt;
 <a name="L76" href="source/net/ipv4/ip_output.c#L76">76</a> #include &lt;linux/igmp.h&gt;
 <a name="L77" href="source/net/ipv4/ip_output.c#L77">77</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L78" href="source/net/ipv4/ip_output.c#L78">78</a> #include &lt;linux/netfilter_bridge.h&gt;
 <a name="L79" href="source/net/ipv4/ip_output.c#L79">79</a> #include &lt;linux/mroute.h&gt;
 <a name="L80" href="source/net/ipv4/ip_output.c#L80">80</a> #include &lt;linux/netlink.h&gt;
 <a name="L81" href="source/net/ipv4/ip_output.c#L81">81</a> #include &lt;linux/tcp.h&gt;
 <a name="L82" href="source/net/ipv4/ip_output.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/ip_output.c#L83">83</a> int <a href="ident?i=sysctl_ip_default_ttl">sysctl_ip_default_ttl</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=IPDEFTTL">IPDEFTTL</a>;
 <a name="L84" href="source/net/ipv4/ip_output.c#L84">84</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_ip_default_ttl">sysctl_ip_default_ttl</a>);
 <a name="L85" href="source/net/ipv4/ip_output.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/ip_output.c#L86">86</a> <b><i>/* Generate a checksum for an outgoing IP datagram. */</i></b>
 <a name="L87" href="source/net/ipv4/ip_output.c#L87">87</a> void <a href="ident?i=ip_send_check">ip_send_check</a>(struct <a href="ident?i=iphdr">iphdr</a> *iph)
 <a name="L88" href="source/net/ipv4/ip_output.c#L88">88</a> {
 <a name="L89" href="source/net/ipv4/ip_output.c#L89">89</a>         iph-&gt;<a href="ident?i=check">check</a> = 0;
 <a name="L90" href="source/net/ipv4/ip_output.c#L90">90</a>         iph-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=ip_fast_csum">ip_fast_csum</a>((unsigned char *)iph, iph-&gt;ihl);
 <a name="L91" href="source/net/ipv4/ip_output.c#L91">91</a> }
 <a name="L92" href="source/net/ipv4/ip_output.c#L92">92</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_send_check">ip_send_check</a>);
 <a name="L93" href="source/net/ipv4/ip_output.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ip_output.c#L94">94</a> int <a href="ident?i=__ip_local_out_sk">__ip_local_out_sk</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L95" href="source/net/ipv4/ip_output.c#L95">95</a> {
 <a name="L96" href="source/net/ipv4/ip_output.c#L96">96</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L97" href="source/net/ipv4/ip_output.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/ip_output.c#L98">98</a>         iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
 <a name="L99" href="source/net/ipv4/ip_output.c#L99">99</a>         <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L100" href="source/net/ipv4/ip_output.c#L100">100</a>         return <a href="ident?i=nf_hook">nf_hook</a>(NFPROTO_IPV4, NF_INET_LOCAL_OUT, sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L101" href="source/net/ipv4/ip_output.c#L101">101</a>                        <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=dst_output_sk">dst_output_sk</a>);
<a name="L102" href="source/net/ipv4/ip_output.c#L102">102</a> }
<a name="L103" href="source/net/ipv4/ip_output.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/ip_output.c#L104">104</a> int <a href="ident?i=__ip_local_out">__ip_local_out</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L105" href="source/net/ipv4/ip_output.c#L105">105</a> {
<a name="L106" href="source/net/ipv4/ip_output.c#L106">106</a>         return <a href="ident?i=__ip_local_out_sk">__ip_local_out_sk</a>(<a href="ident?i=skb">skb</a>-&gt;sk, <a href="ident?i=skb">skb</a>);
<a name="L107" href="source/net/ipv4/ip_output.c#L107">107</a> }
<a name="L108" href="source/net/ipv4/ip_output.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/ip_output.c#L109">109</a> int <a href="ident?i=ip_local_out_sk">ip_local_out_sk</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L110" href="source/net/ipv4/ip_output.c#L110">110</a> {
<a name="L111" href="source/net/ipv4/ip_output.c#L111">111</a>         int <a href="ident?i=err">err</a>;
<a name="L112" href="source/net/ipv4/ip_output.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/ip_output.c#L113">113</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__ip_local_out">__ip_local_out</a>(<a href="ident?i=skb">skb</a>);
<a name="L114" href="source/net/ipv4/ip_output.c#L114">114</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=err">err</a> == 1))
<a name="L115" href="source/net/ipv4/ip_output.c#L115">115</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=dst_output_sk">dst_output_sk</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L116" href="source/net/ipv4/ip_output.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/ip_output.c#L117">117</a>         return <a href="ident?i=err">err</a>;
<a name="L118" href="source/net/ipv4/ip_output.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/ip_output.c#L119">119</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_local_out_sk">ip_local_out_sk</a>);
<a name="L120" href="source/net/ipv4/ip_output.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/ip_output.c#L121">121</a> static inline int <a href="ident?i=ip_select_ttl">ip_select_ttl</a>(struct <a href="ident?i=inet_sock">inet_sock</a> *inet, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L122" href="source/net/ipv4/ip_output.c#L122">122</a> {
<a name="L123" href="source/net/ipv4/ip_output.c#L123">123</a>         int <a href="ident?i=ttl">ttl</a> = inet-&gt;uc_ttl;
<a name="L124" href="source/net/ipv4/ip_output.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/ip_output.c#L125">125</a>         if (<a href="ident?i=ttl">ttl</a> &lt; 0)
<a name="L126" href="source/net/ipv4/ip_output.c#L126">126</a>                 <a href="ident?i=ttl">ttl</a> = <a href="ident?i=ip4_dst_hoplimit">ip4_dst_hoplimit</a>(<a href="ident?i=dst">dst</a>);
<a name="L127" href="source/net/ipv4/ip_output.c#L127">127</a>         return <a href="ident?i=ttl">ttl</a>;
<a name="L128" href="source/net/ipv4/ip_output.c#L128">128</a> }
<a name="L129" href="source/net/ipv4/ip_output.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/ip_output.c#L130">130</a> <b><i>/*</i></b>
<a name="L131" href="source/net/ipv4/ip_output.c#L131">131</a> <b><i> *              Add an ip header to a skbuff and send it out.</i></b>
<a name="L132" href="source/net/ipv4/ip_output.c#L132">132</a> <b><i> *</i></b>
<a name="L133" href="source/net/ipv4/ip_output.c#L133">133</a> <b><i> */</i></b>
<a name="L134" href="source/net/ipv4/ip_output.c#L134">134</a> int <a href="ident?i=ip_build_and_send_pkt">ip_build_and_send_pkt</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L135" href="source/net/ipv4/ip_output.c#L135">135</a>                           <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt)
<a name="L136" href="source/net/ipv4/ip_output.c#L136">136</a> {
<a name="L137" href="source/net/ipv4/ip_output.c#L137">137</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L138" href="source/net/ipv4/ip_output.c#L138">138</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L139" href="source/net/ipv4/ip_output.c#L139">139</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L140" href="source/net/ipv4/ip_output.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/ip_output.c#L141">141</a>         <b><i>/* Build the IP header. */</i></b>
<a name="L142" href="source/net/ipv4/ip_output.c#L142">142</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + (opt ? opt-&gt;opt.<a href="ident?i=optlen">optlen</a> : 0));
<a name="L143" href="source/net/ipv4/ip_output.c#L143">143</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L144" href="source/net/ipv4/ip_output.c#L144">144</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L145" href="source/net/ipv4/ip_output.c#L145">145</a>         iph-&gt;<a href="ident?i=version">version</a>  = 4;
<a name="L146" href="source/net/ipv4/ip_output.c#L146">146</a>         iph-&gt;ihl      = 5;
<a name="L147" href="source/net/ipv4/ip_output.c#L147">147</a>         iph-&gt;tos      = inet-&gt;tos;
<a name="L148" href="source/net/ipv4/ip_output.c#L148">148</a>         if (<a href="ident?i=ip_dont_fragment">ip_dont_fragment</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>))
<a name="L149" href="source/net/ipv4/ip_output.c#L149">149</a>                 iph-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L150" href="source/net/ipv4/ip_output.c#L150">150</a>         else
<a name="L151" href="source/net/ipv4/ip_output.c#L151">151</a>                 iph-&gt;frag_off = 0;
<a name="L152" href="source/net/ipv4/ip_output.c#L152">152</a>         iph-&gt;<a href="ident?i=ttl">ttl</a>      = <a href="ident?i=ip_select_ttl">ip_select_ttl</a>(inet, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L153" href="source/net/ipv4/ip_output.c#L153">153</a>         iph-&gt;<a href="ident?i=daddr">daddr</a>    = (opt &amp;&amp; opt-&gt;opt.<a href="ident?i=srr">srr</a> ? opt-&gt;opt.faddr : <a href="ident?i=daddr">daddr</a>);
<a name="L154" href="source/net/ipv4/ip_output.c#L154">154</a>         iph-&gt;<a href="ident?i=saddr">saddr</a>    = <a href="ident?i=saddr">saddr</a>;
<a name="L155" href="source/net/ipv4/ip_output.c#L155">155</a>         iph-&gt;<a href="ident?i=protocol">protocol</a> = sk-&gt;sk_protocol;
<a name="L156" href="source/net/ipv4/ip_output.c#L156">156</a>         <a href="ident?i=ip_select_ident">ip_select_ident</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>, sk);
<a name="L157" href="source/net/ipv4/ip_output.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/ip_output.c#L158">158</a>         if (opt &amp;&amp; opt-&gt;opt.<a href="ident?i=optlen">optlen</a>) {
<a name="L159" href="source/net/ipv4/ip_output.c#L159">159</a>                 iph-&gt;ihl += opt-&gt;opt.<a href="ident?i=optlen">optlen</a>&gt;&gt;2;
<a name="L160" href="source/net/ipv4/ip_output.c#L160">160</a>                 <a href="ident?i=ip_options_build">ip_options_build</a>(<a href="ident?i=skb">skb</a>, &amp;opt-&gt;opt, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=rt">rt</a>, 0);
<a name="L161" href="source/net/ipv4/ip_output.c#L161">161</a>         }
<a name="L162" href="source/net/ipv4/ip_output.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/ip_output.c#L163">163</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = sk-&gt;sk_priority;
<a name="L164" href="source/net/ipv4/ip_output.c#L164">164</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> = sk-&gt;sk_mark;
<a name="L165" href="source/net/ipv4/ip_output.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/ip_output.c#L166">166</a>         <b><i>/* Send it out. */</i></b>
<a name="L167" href="source/net/ipv4/ip_output.c#L167">167</a>         return <a href="ident?i=ip_local_out">ip_local_out</a>(<a href="ident?i=skb">skb</a>);
<a name="L168" href="source/net/ipv4/ip_output.c#L168">168</a> }
<a name="L169" href="source/net/ipv4/ip_output.c#L169">169</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_build_and_send_pkt">ip_build_and_send_pkt</a>);
<a name="L170" href="source/net/ipv4/ip_output.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/ip_output.c#L171">171</a> static inline int <a href="ident?i=ip_finish_output2">ip_finish_output2</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L172" href="source/net/ipv4/ip_output.c#L172">172</a> {
<a name="L173" href="source/net/ipv4/ip_output.c#L173">173</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L174" href="source/net/ipv4/ip_output.c#L174">174</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=dst">dst</a>;
<a name="L175" href="source/net/ipv4/ip_output.c#L175">175</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L176" href="source/net/ipv4/ip_output.c#L176">176</a>         unsigned int hh_len = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>);
<a name="L177" href="source/net/ipv4/ip_output.c#L177">177</a>         struct <a href="ident?i=neighbour">neighbour</a> *neigh;
<a name="L178" href="source/net/ipv4/ip_output.c#L178">178</a>         <a href="ident?i=u32">u32</a> nexthop;
<a name="L179" href="source/net/ipv4/ip_output.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/ip_output.c#L180">180</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_type == RTN_MULTICAST) {
<a name="L181" href="source/net/ipv4/ip_output.c#L181">181</a>                 <a href="ident?i=IP_UPD_PO_STATS">IP_UPD_PO_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUTMCAST, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L182" href="source/net/ipv4/ip_output.c#L182">182</a>         } else if (<a href="ident?i=rt">rt</a>-&gt;rt_type == RTN_BROADCAST)
<a name="L183" href="source/net/ipv4/ip_output.c#L183">183</a>                 <a href="ident?i=IP_UPD_PO_STATS">IP_UPD_PO_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUTBCAST, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L184" href="source/net/ipv4/ip_output.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/ip_output.c#L185">185</a>         <b><i>/* Be paranoid, rather than too clever. */</i></b>
<a name="L186" href="source/net/ipv4/ip_output.c#L186">186</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>) &lt; hh_len &amp;&amp; <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=header_ops">header_ops</a>)) {
<a name="L187" href="source/net/ipv4/ip_output.c#L187">187</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb2;
<a name="L188" href="source/net/ipv4/ip_output.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/ip_output.c#L189">189</a>                 skb2 = <a href="ident?i=skb_realloc_headroom">skb_realloc_headroom</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>));
<a name="L190" href="source/net/ipv4/ip_output.c#L190">190</a>                 if (!skb2) {
<a name="L191" href="source/net/ipv4/ip_output.c#L191">191</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L192" href="source/net/ipv4/ip_output.c#L192">192</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L193" href="source/net/ipv4/ip_output.c#L193">193</a>                 }
<a name="L194" href="source/net/ipv4/ip_output.c#L194">194</a>                 if (<a href="ident?i=skb">skb</a>-&gt;sk)
<a name="L195" href="source/net/ipv4/ip_output.c#L195">195</a>                         <a href="ident?i=skb_set_owner_w">skb_set_owner_w</a>(skb2, <a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L196" href="source/net/ipv4/ip_output.c#L196">196</a>                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L197" href="source/net/ipv4/ip_output.c#L197">197</a>                 <a href="ident?i=skb">skb</a> = skb2;
<a name="L198" href="source/net/ipv4/ip_output.c#L198">198</a>         }
<a name="L199" href="source/net/ipv4/ip_output.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/ip_output.c#L200">200</a>         <a href="ident?i=rcu_read_lock_bh">rcu_read_lock_bh</a>();
<a name="L201" href="source/net/ipv4/ip_output.c#L201">201</a>         nexthop = (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>) <a href="ident?i=rt_nexthop">rt_nexthop</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L202" href="source/net/ipv4/ip_output.c#L202">202</a>         neigh = <a href="ident?i=__ipv4_neigh_lookup_noref">__ipv4_neigh_lookup_noref</a>(<a href="ident?i=dev">dev</a>, nexthop);
<a name="L203" href="source/net/ipv4/ip_output.c#L203">203</a>         if (<a href="ident?i=unlikely">unlikely</a>(!neigh))
<a name="L204" href="source/net/ipv4/ip_output.c#L204">204</a>                 neigh = <a href="ident?i=__neigh_create">__neigh_create</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;nexthop, <a href="ident?i=dev">dev</a>, <a href="ident?i=false">false</a>);
<a name="L205" href="source/net/ipv4/ip_output.c#L205">205</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(neigh)) {
<a name="L206" href="source/net/ipv4/ip_output.c#L206">206</a>                 int <a href="ident?i=res">res</a> = <a href="ident?i=dst_neigh_output">dst_neigh_output</a>(<a href="ident?i=dst">dst</a>, neigh, <a href="ident?i=skb">skb</a>);
<a name="L207" href="source/net/ipv4/ip_output.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/ip_output.c#L208">208</a>                 <a href="ident?i=rcu_read_unlock_bh">rcu_read_unlock_bh</a>();
<a name="L209" href="source/net/ipv4/ip_output.c#L209">209</a>                 return <a href="ident?i=res">res</a>;
<a name="L210" href="source/net/ipv4/ip_output.c#L210">210</a>         }
<a name="L211" href="source/net/ipv4/ip_output.c#L211">211</a>         <a href="ident?i=rcu_read_unlock_bh">rcu_read_unlock_bh</a>();
<a name="L212" href="source/net/ipv4/ip_output.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/ip_output.c#L213">213</a>         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"%s: No header cache and no neighbour!\n"</i>,
<a name="L214" href="source/net/ipv4/ip_output.c#L214">214</a>                             <a href="ident?i=__func__">__func__</a>);
<a name="L215" href="source/net/ipv4/ip_output.c#L215">215</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L216" href="source/net/ipv4/ip_output.c#L216">216</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L217" href="source/net/ipv4/ip_output.c#L217">217</a> }
<a name="L218" href="source/net/ipv4/ip_output.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/ip_output.c#L219">219</a> static int <a href="ident?i=ip_finish_output_gso">ip_finish_output_gso</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L220" href="source/net/ipv4/ip_output.c#L220">220</a> {
<a name="L221" href="source/net/ipv4/ip_output.c#L221">221</a>         <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>;
<a name="L222" href="source/net/ipv4/ip_output.c#L222">222</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *segs;
<a name="L223" href="source/net/ipv4/ip_output.c#L223">223</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L224" href="source/net/ipv4/ip_output.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/ip_output.c#L225">225</a>         <b><i>/* common case: locally created skb or seglen is &lt;= mtu */</i></b>
<a name="L226" href="source/net/ipv4/ip_output.c#L226">226</a>         if (((<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_FORWARDED">IPSKB_FORWARDED</a>) == 0) ||
<a name="L227" href="source/net/ipv4/ip_output.c#L227">227</a>               <a href="ident?i=skb_gso_network_seglen">skb_gso_network_seglen</a>(<a href="ident?i=skb">skb</a>) &lt;= <a href="ident?i=ip_skb_dst_mtu">ip_skb_dst_mtu</a>(<a href="ident?i=skb">skb</a>))
<a name="L228" href="source/net/ipv4/ip_output.c#L228">228</a>                 return <a href="ident?i=ip_finish_output2">ip_finish_output2</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L229" href="source/net/ipv4/ip_output.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/ip_output.c#L230">230</a>         <b><i>/* Slowpath -  GSO segment length is exceeding the dst MTU.</i></b>
<a name="L231" href="source/net/ipv4/ip_output.c#L231">231</a> <b><i>         *</i></b>
<a name="L232" href="source/net/ipv4/ip_output.c#L232">232</a> <b><i>         * This can happen in two cases:</i></b>
<a name="L233" href="source/net/ipv4/ip_output.c#L233">233</a> <b><i>         * 1) TCP GRO packet, DF bit not set</i></b>
<a name="L234" href="source/net/ipv4/ip_output.c#L234">234</a> <b><i>         * 2) skb arrived via virtio-net, we thus get TSO/GSO skbs directly</i></b>
<a name="L235" href="source/net/ipv4/ip_output.c#L235">235</a> <b><i>         * from host network stack.</i></b>
<a name="L236" href="source/net/ipv4/ip_output.c#L236">236</a> <b><i>         */</i></b>
<a name="L237" href="source/net/ipv4/ip_output.c#L237">237</a>         <a href="ident?i=features">features</a> = <a href="ident?i=netif_skb_features">netif_skb_features</a>(<a href="ident?i=skb">skb</a>);
<a name="L238" href="source/net/ipv4/ip_output.c#L238">238</a>         segs = <a href="ident?i=skb_gso_segment">skb_gso_segment</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a> &amp; ~NETIF_F_GSO_MASK);
<a name="L239" href="source/net/ipv4/ip_output.c#L239">239</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(segs)) {
<a name="L240" href="source/net/ipv4/ip_output.c#L240">240</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L241" href="source/net/ipv4/ip_output.c#L241">241</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L242" href="source/net/ipv4/ip_output.c#L242">242</a>         }
<a name="L243" href="source/net/ipv4/ip_output.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/ip_output.c#L244">244</a>         <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L245" href="source/net/ipv4/ip_output.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/ip_output.c#L246">246</a>         do {
<a name="L247" href="source/net/ipv4/ip_output.c#L247">247</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *nskb = segs-&gt;<a href="ident?i=next">next</a>;
<a name="L248" href="source/net/ipv4/ip_output.c#L248">248</a>                 int <a href="ident?i=err">err</a>;
<a name="L249" href="source/net/ipv4/ip_output.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/ip_output.c#L250">250</a>                 segs-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L251" href="source/net/ipv4/ip_output.c#L251">251</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_fragment">ip_fragment</a>(sk, segs, <a href="ident?i=ip_finish_output2">ip_finish_output2</a>);
<a name="L252" href="source/net/ipv4/ip_output.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/ip_output.c#L253">253</a>                 if (<a href="ident?i=err">err</a> &amp;&amp; <a href="ident?i=ret">ret</a> == 0)
<a name="L254" href="source/net/ipv4/ip_output.c#L254">254</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=err">err</a>;
<a name="L255" href="source/net/ipv4/ip_output.c#L255">255</a>                 segs = nskb;
<a name="L256" href="source/net/ipv4/ip_output.c#L256">256</a>         } while (segs);
<a name="L257" href="source/net/ipv4/ip_output.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/ip_output.c#L258">258</a>         return <a href="ident?i=ret">ret</a>;
<a name="L259" href="source/net/ipv4/ip_output.c#L259">259</a> }
<a name="L260" href="source/net/ipv4/ip_output.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/ip_output.c#L261">261</a> static int <a href="ident?i=ip_finish_output">ip_finish_output</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L262" href="source/net/ipv4/ip_output.c#L262">262</a> {
<a name="L263" href="source/net/ipv4/ip_output.c#L263">263</a> #if defined(CONFIG_NETFILTER) &amp;&amp; defined(CONFIG_XFRM)
<a name="L264" href="source/net/ipv4/ip_output.c#L264">264</a>         <b><i>/* Policy lookup after SNAT yielded a new policy */</i></b>
<a name="L265" href="source/net/ipv4/ip_output.c#L265">265</a>         if (<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;xfrm) {
<a name="L266" href="source/net/ipv4/ip_output.c#L266">266</a>                 <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_REROUTED">IPSKB_REROUTED</a>;
<a name="L267" href="source/net/ipv4/ip_output.c#L267">267</a>                 return <a href="ident?i=dst_output_sk">dst_output_sk</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L268" href="source/net/ipv4/ip_output.c#L268">268</a>         }
<a name="L269" href="source/net/ipv4/ip_output.c#L269">269</a> #endif
<a name="L270" href="source/net/ipv4/ip_output.c#L270">270</a>         if (<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>))
<a name="L271" href="source/net/ipv4/ip_output.c#L271">271</a>                 return <a href="ident?i=ip_finish_output_gso">ip_finish_output_gso</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L272" href="source/net/ipv4/ip_output.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/ip_output.c#L273">273</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=ip_skb_dst_mtu">ip_skb_dst_mtu</a>(<a href="ident?i=skb">skb</a>))
<a name="L274" href="source/net/ipv4/ip_output.c#L274">274</a>                 return <a href="ident?i=ip_fragment">ip_fragment</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=ip_finish_output2">ip_finish_output2</a>);
<a name="L275" href="source/net/ipv4/ip_output.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/ip_output.c#L276">276</a>         return <a href="ident?i=ip_finish_output2">ip_finish_output2</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L277" href="source/net/ipv4/ip_output.c#L277">277</a> }
<a name="L278" href="source/net/ipv4/ip_output.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/ip_output.c#L279">279</a> int <a href="ident?i=ip_mc_output">ip_mc_output</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L280" href="source/net/ipv4/ip_output.c#L280">280</a> {
<a name="L281" href="source/net/ipv4/ip_output.c#L281">281</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L282" href="source/net/ipv4/ip_output.c#L282">282</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L283" href="source/net/ipv4/ip_output.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/ip_output.c#L284">284</a>         <b><i>/*</i></b>
<a name="L285" href="source/net/ipv4/ip_output.c#L285">285</a> <b><i>         *      If the indicated interface is up and running, send the packet.</i></b>
<a name="L286" href="source/net/ipv4/ip_output.c#L286">286</a> <b><i>         */</i></b>
<a name="L287" href="source/net/ipv4/ip_output.c#L287">287</a>         <a href="ident?i=IP_UPD_PO_STATS">IP_UPD_PO_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUT, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L288" href="source/net/ipv4/ip_output.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/ip_output.c#L289">289</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L290" href="source/net/ipv4/ip_output.c#L290">290</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L291" href="source/net/ipv4/ip_output.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/ip_output.c#L292">292</a>         <b><i>/*</i></b>
<a name="L293" href="source/net/ipv4/ip_output.c#L293">293</a> <b><i>         *      Multicasts are looped back for other local users</i></b>
<a name="L294" href="source/net/ipv4/ip_output.c#L294">294</a> <b><i>         */</i></b>
<a name="L295" href="source/net/ipv4/ip_output.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/ip_output.c#L296">296</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags&amp;<a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>) {
<a name="L297" href="source/net/ipv4/ip_output.c#L297">297</a>                 if (<a href="ident?i=sk_mc_loop">sk_mc_loop</a>(sk)
<a name="L298" href="source/net/ipv4/ip_output.c#L298">298</a> #ifdef CONFIG_IP_MROUTE
<a name="L299" href="source/net/ipv4/ip_output.c#L299">299</a>                 <b><i>/* Small optimization: do not loopback not local frames,</i></b>
<a name="L300" href="source/net/ipv4/ip_output.c#L300">300</a> <b><i>                   which returned after forwarding; they will be  dropped</i></b>
<a name="L301" href="source/net/ipv4/ip_output.c#L301">301</a> <b><i>                   by ip_mr_input in any case.</i></b>
<a name="L302" href="source/net/ipv4/ip_output.c#L302">302</a> <b><i>                   Note, that local frames are looped back to be delivered</i></b>
<a name="L303" href="source/net/ipv4/ip_output.c#L303">303</a> <b><i>                   to local recipients.</i></b>
<a name="L304" href="source/net/ipv4/ip_output.c#L304">304</a> <b><i></i></b>
<a name="L305" href="source/net/ipv4/ip_output.c#L305">305</a> <b><i>                   This check is duplicated in ip_mr_input at the moment.</i></b>
<a name="L306" href="source/net/ipv4/ip_output.c#L306">306</a> <b><i>                 */</i></b>
<a name="L307" href="source/net/ipv4/ip_output.c#L307">307</a>                     &amp;&amp;
<a name="L308" href="source/net/ipv4/ip_output.c#L308">308</a>                     ((<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>) ||
<a name="L309" href="source/net/ipv4/ip_output.c#L309">309</a>                      !(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_FORWARDED">IPSKB_FORWARDED</a>))
<a name="L310" href="source/net/ipv4/ip_output.c#L310">310</a> #endif
<a name="L311" href="source/net/ipv4/ip_output.c#L311">311</a>                    ) {
<a name="L312" href="source/net/ipv4/ip_output.c#L312">312</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *newskb = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L313" href="source/net/ipv4/ip_output.c#L313">313</a>                         if (newskb)
<a name="L314" href="source/net/ipv4/ip_output.c#L314">314</a>                                 <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_POST_ROUTING,
<a name="L315" href="source/net/ipv4/ip_output.c#L315">315</a>                                         sk, newskb, <a href="ident?i=NULL">NULL</a>, newskb-&gt;<a href="ident?i=dev">dev</a>,
<a name="L316" href="source/net/ipv4/ip_output.c#L316">316</a>                                         <a href="ident?i=dev_loopback_xmit">dev_loopback_xmit</a>);
<a name="L317" href="source/net/ipv4/ip_output.c#L317">317</a>                 }
<a name="L318" href="source/net/ipv4/ip_output.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/ip_output.c#L319">319</a>                 <b><i>/* Multicasts with ttl 0 must not go beyond the host */</i></b>
<a name="L320" href="source/net/ipv4/ip_output.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/ip_output.c#L321">321</a>                 if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a> == 0) {
<a name="L322" href="source/net/ipv4/ip_output.c#L322">322</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L323" href="source/net/ipv4/ip_output.c#L323">323</a>                         return 0;
<a name="L324" href="source/net/ipv4/ip_output.c#L324">324</a>                 }
<a name="L325" href="source/net/ipv4/ip_output.c#L325">325</a>         }
<a name="L326" href="source/net/ipv4/ip_output.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/ip_output.c#L327">327</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags&amp;<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>) {
<a name="L328" href="source/net/ipv4/ip_output.c#L328">328</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *newskb = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L329" href="source/net/ipv4/ip_output.c#L329">329</a>                 if (newskb)
<a name="L330" href="source/net/ipv4/ip_output.c#L330">330</a>                         <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_POST_ROUTING, sk, newskb,
<a name="L331" href="source/net/ipv4/ip_output.c#L331">331</a>                                 <a href="ident?i=NULL">NULL</a>, newskb-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=dev_loopback_xmit">dev_loopback_xmit</a>);
<a name="L332" href="source/net/ipv4/ip_output.c#L332">332</a>         }
<a name="L333" href="source/net/ipv4/ip_output.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/ip_output.c#L334">334</a>         return <a href="ident?i=NF_HOOK_COND">NF_HOOK_COND</a>(NFPROTO_IPV4, NF_INET_POST_ROUTING, sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>,
<a name="L335" href="source/net/ipv4/ip_output.c#L335">335</a>                             <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=ip_finish_output">ip_finish_output</a>,
<a name="L336" href="source/net/ipv4/ip_output.c#L336">336</a>                             !(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_REROUTED">IPSKB_REROUTED</a>));
<a name="L337" href="source/net/ipv4/ip_output.c#L337">337</a> }
<a name="L338" href="source/net/ipv4/ip_output.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/ip_output.c#L339">339</a> int <a href="ident?i=ip_output">ip_output</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L340" href="source/net/ipv4/ip_output.c#L340">340</a> {
<a name="L341" href="source/net/ipv4/ip_output.c#L341">341</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>;
<a name="L342" href="source/net/ipv4/ip_output.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/ip_output.c#L343">343</a>         <a href="ident?i=IP_UPD_PO_STATS">IP_UPD_PO_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_OUT, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L344" href="source/net/ipv4/ip_output.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/ip_output.c#L345">345</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L346" href="source/net/ipv4/ip_output.c#L346">346</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L347" href="source/net/ipv4/ip_output.c#L347">347</a> 
<a name="L348" href="source/net/ipv4/ip_output.c#L348">348</a>         return <a href="ident?i=NF_HOOK_COND">NF_HOOK_COND</a>(NFPROTO_IPV4, NF_INET_POST_ROUTING, sk, <a href="ident?i=skb">skb</a>,
<a name="L349" href="source/net/ipv4/ip_output.c#L349">349</a>                             <a href="ident?i=NULL">NULL</a>, <a href="ident?i=dev">dev</a>,
<a name="L350" href="source/net/ipv4/ip_output.c#L350">350</a>                             <a href="ident?i=ip_finish_output">ip_finish_output</a>,
<a name="L351" href="source/net/ipv4/ip_output.c#L351">351</a>                             !(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_REROUTED">IPSKB_REROUTED</a>));
<a name="L352" href="source/net/ipv4/ip_output.c#L352">352</a> }
<a name="L353" href="source/net/ipv4/ip_output.c#L353">353</a> 
<a name="L354" href="source/net/ipv4/ip_output.c#L354">354</a> <b><i>/*</i></b>
<a name="L355" href="source/net/ipv4/ip_output.c#L355">355</a> <b><i> * copy saddr and daddr, possibly using 64bit load/stores</i></b>
<a name="L356" href="source/net/ipv4/ip_output.c#L356">356</a> <b><i> * Equivalent to :</i></b>
<a name="L357" href="source/net/ipv4/ip_output.c#L357">357</a> <b><i> *   iph-&gt;saddr = fl4-&gt;saddr;</i></b>
<a name="L358" href="source/net/ipv4/ip_output.c#L358">358</a> <b><i> *   iph-&gt;daddr = fl4-&gt;daddr;</i></b>
<a name="L359" href="source/net/ipv4/ip_output.c#L359">359</a> <b><i> */</i></b>
<a name="L360" href="source/net/ipv4/ip_output.c#L360">360</a> static void <a href="ident?i=ip_copy_addrs">ip_copy_addrs</a>(struct <a href="ident?i=iphdr">iphdr</a> *iph, const struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L361" href="source/net/ipv4/ip_output.c#L361">361</a> {
<a name="L362" href="source/net/ipv4/ip_output.c#L362">362</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(typeof(*fl4), <a href="ident?i=daddr">daddr</a>) !=
<a name="L363" href="source/net/ipv4/ip_output.c#L363">363</a>                      <a href="ident?i=offsetof">offsetof</a>(typeof(*fl4), <a href="ident?i=saddr">saddr</a>) + sizeof(fl4-&gt;<a href="ident?i=saddr">saddr</a>));
<a name="L364" href="source/net/ipv4/ip_output.c#L364">364</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, &amp;fl4-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L365" href="source/net/ipv4/ip_output.c#L365">365</a>                sizeof(fl4-&gt;<a href="ident?i=saddr">saddr</a>) + sizeof(fl4-&gt;<a href="ident?i=daddr">daddr</a>));
<a name="L366" href="source/net/ipv4/ip_output.c#L366">366</a> }
<a name="L367" href="source/net/ipv4/ip_output.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/ip_output.c#L368">368</a> <b><i>/* Note: skb-&gt;sk can be different from sk, in case of tunnels */</i></b>
<a name="L369" href="source/net/ipv4/ip_output.c#L369">369</a> int <a href="ident?i=ip_queue_xmit">ip_queue_xmit</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=flowi">flowi</a> *fl)
<a name="L370" href="source/net/ipv4/ip_output.c#L370">370</a> {
<a name="L371" href="source/net/ipv4/ip_output.c#L371">371</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L372" href="source/net/ipv4/ip_output.c#L372">372</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L373" href="source/net/ipv4/ip_output.c#L373">373</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L374" href="source/net/ipv4/ip_output.c#L374">374</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L375" href="source/net/ipv4/ip_output.c#L375">375</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L376" href="source/net/ipv4/ip_output.c#L376">376</a>         int <a href="ident?i=res">res</a>;
<a name="L377" href="source/net/ipv4/ip_output.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/ip_output.c#L378">378</a>         <b><i>/* Skip all of this if the packet is already routed,</i></b>
<a name="L379" href="source/net/ipv4/ip_output.c#L379">379</a> <b><i>         * f.e. by something like SCTP.</i></b>
<a name="L380" href="source/net/ipv4/ip_output.c#L380">380</a> <b><i>         */</i></b>
<a name="L381" href="source/net/ipv4/ip_output.c#L381">381</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L382" href="source/net/ipv4/ip_output.c#L382">382</a>         inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L383" href="source/net/ipv4/ip_output.c#L383">383</a>         fl4 = &amp;fl-&gt;u.ip4;
<a name="L384" href="source/net/ipv4/ip_output.c#L384">384</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L385" href="source/net/ipv4/ip_output.c#L385">385</a>         if (<a href="ident?i=rt">rt</a>)
<a name="L386" href="source/net/ipv4/ip_output.c#L386">386</a>                 goto packet_routed;
<a name="L387" href="source/net/ipv4/ip_output.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/ip_output.c#L388">388</a>         <b><i>/* Make sure we can route this packet. */</i></b>
<a name="L389" href="source/net/ipv4/ip_output.c#L389">389</a>         <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=__sk_dst_check">__sk_dst_check</a>(sk, 0);
<a name="L390" href="source/net/ipv4/ip_output.c#L390">390</a>         if (!<a href="ident?i=rt">rt</a>) {
<a name="L391" href="source/net/ipv4/ip_output.c#L391">391</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>;
<a name="L392" href="source/net/ipv4/ip_output.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/ip_output.c#L393">393</a>                 <b><i>/* Use correct destination address if we have options. */</i></b>
<a name="L394" href="source/net/ipv4/ip_output.c#L394">394</a>                 <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L395" href="source/net/ipv4/ip_output.c#L395">395</a>                 if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L396" href="source/net/ipv4/ip_output.c#L396">396</a>                         <a href="ident?i=daddr">daddr</a> = inet_opt-&gt;opt.faddr;
<a name="L397" href="source/net/ipv4/ip_output.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/ip_output.c#L398">398</a>                 <b><i>/* If this fails, retransmit mechanism of transport layer will</i></b>
<a name="L399" href="source/net/ipv4/ip_output.c#L399">399</a> <b><i>                 * keep trying until route appears or the connection times</i></b>
<a name="L400" href="source/net/ipv4/ip_output.c#L400">400</a> <b><i>                 * itself out.</i></b>
<a name="L401" href="source/net/ipv4/ip_output.c#L401">401</a> <b><i>                 */</i></b>
<a name="L402" href="source/net/ipv4/ip_output.c#L402">402</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=sock_net">sock_net</a>(sk), fl4, sk,
<a name="L403" href="source/net/ipv4/ip_output.c#L403">403</a>                                            <a href="ident?i=daddr">daddr</a>, inet-&gt;inet_saddr,
<a name="L404" href="source/net/ipv4/ip_output.c#L404">404</a>                                            inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>,
<a name="L405" href="source/net/ipv4/ip_output.c#L405">405</a>                                            inet-&gt;inet_sport,
<a name="L406" href="source/net/ipv4/ip_output.c#L406">406</a>                                            sk-&gt;sk_protocol,
<a name="L407" href="source/net/ipv4/ip_output.c#L407">407</a>                                            <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk),
<a name="L408" href="source/net/ipv4/ip_output.c#L408">408</a>                                            sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L409" href="source/net/ipv4/ip_output.c#L409">409</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L410" href="source/net/ipv4/ip_output.c#L410">410</a>                         goto no_route;
<a name="L411" href="source/net/ipv4/ip_output.c#L411">411</a>                 <a href="ident?i=sk_setup_caps">sk_setup_caps</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L412" href="source/net/ipv4/ip_output.c#L412">412</a>         }
<a name="L413" href="source/net/ipv4/ip_output.c#L413">413</a>         <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L414" href="source/net/ipv4/ip_output.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/ip_output.c#L415">415</a> packet_routed:
<a name="L416" href="source/net/ipv4/ip_output.c#L416">416</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.is_strictroute &amp;&amp; <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway)
<a name="L417" href="source/net/ipv4/ip_output.c#L417">417</a>                 goto no_route;
<a name="L418" href="source/net/ipv4/ip_output.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/ip_output.c#L419">419</a>         <b><i>/* OK, we know where to send it, allocate and build IP header. */</i></b>
<a name="L420" href="source/net/ipv4/ip_output.c#L420">420</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + (inet_opt ? inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a> : 0));
<a name="L421" href="source/net/ipv4/ip_output.c#L421">421</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L422" href="source/net/ipv4/ip_output.c#L422">422</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L423" href="source/net/ipv4/ip_output.c#L423">423</a>         *((<a href="ident?i=__be16">__be16</a> *)iph) = <a href="ident?i=htons">htons</a>((4 &lt;&lt; 12) | (5 &lt;&lt; 8) | (inet-&gt;tos &amp; 0xff));
<a name="L424" href="source/net/ipv4/ip_output.c#L424">424</a>         if (<a href="ident?i=ip_dont_fragment">ip_dont_fragment</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>) &amp;&amp; !<a href="ident?i=skb">skb</a>-&gt;ignore_df)
<a name="L425" href="source/net/ipv4/ip_output.c#L425">425</a>                 iph-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L426" href="source/net/ipv4/ip_output.c#L426">426</a>         else
<a name="L427" href="source/net/ipv4/ip_output.c#L427">427</a>                 iph-&gt;frag_off = 0;
<a name="L428" href="source/net/ipv4/ip_output.c#L428">428</a>         iph-&gt;<a href="ident?i=ttl">ttl</a>      = <a href="ident?i=ip_select_ttl">ip_select_ttl</a>(inet, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L429" href="source/net/ipv4/ip_output.c#L429">429</a>         iph-&gt;<a href="ident?i=protocol">protocol</a> = sk-&gt;sk_protocol;
<a name="L430" href="source/net/ipv4/ip_output.c#L430">430</a>         <a href="ident?i=ip_copy_addrs">ip_copy_addrs</a>(iph, fl4);
<a name="L431" href="source/net/ipv4/ip_output.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/ip_output.c#L432">432</a>         <b><i>/* Transport layer set skb-&gt;h.foo itself. */</i></b>
<a name="L433" href="source/net/ipv4/ip_output.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/ip_output.c#L434">434</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>) {
<a name="L435" href="source/net/ipv4/ip_output.c#L435">435</a>                 iph-&gt;ihl += inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a> &gt;&gt; 2;
<a name="L436" href="source/net/ipv4/ip_output.c#L436">436</a>                 <a href="ident?i=ip_options_build">ip_options_build</a>(<a href="ident?i=skb">skb</a>, &amp;inet_opt-&gt;opt, inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>, <a href="ident?i=rt">rt</a>, 0);
<a name="L437" href="source/net/ipv4/ip_output.c#L437">437</a>         }
<a name="L438" href="source/net/ipv4/ip_output.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/ip_output.c#L439">439</a>         <a href="ident?i=ip_select_ident_segs">ip_select_ident_segs</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>, sk,
<a name="L440" href="source/net/ipv4/ip_output.c#L440">440</a>                              <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs ?: 1);
<a name="L441" href="source/net/ipv4/ip_output.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/ip_output.c#L442">442</a>         <b><i>/* TODO : should we use skb-&gt;sk here instead of sk ? */</i></b>
<a name="L443" href="source/net/ipv4/ip_output.c#L443">443</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = sk-&gt;sk_priority;
<a name="L444" href="source/net/ipv4/ip_output.c#L444">444</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> = sk-&gt;sk_mark;
<a name="L445" href="source/net/ipv4/ip_output.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/ip_output.c#L446">446</a>         <a href="ident?i=res">res</a> = <a href="ident?i=ip_local_out">ip_local_out</a>(<a href="ident?i=skb">skb</a>);
<a name="L447" href="source/net/ipv4/ip_output.c#L447">447</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L448" href="source/net/ipv4/ip_output.c#L448">448</a>         return <a href="ident?i=res">res</a>;
<a name="L449" href="source/net/ipv4/ip_output.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/ip_output.c#L450">450</a> no_route:
<a name="L451" href="source/net/ipv4/ip_output.c#L451">451</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L452" href="source/net/ipv4/ip_output.c#L452">452</a>         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), IPSTATS_MIB_OUTNOROUTES);
<a name="L453" href="source/net/ipv4/ip_output.c#L453">453</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L454" href="source/net/ipv4/ip_output.c#L454">454</a>         return -<a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L455" href="source/net/ipv4/ip_output.c#L455">455</a> }
<a name="L456" href="source/net/ipv4/ip_output.c#L456">456</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_queue_xmit">ip_queue_xmit</a>);
<a name="L457" href="source/net/ipv4/ip_output.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/ip_output.c#L458">458</a> static void <a href="ident?i=ip_copy_metadata">ip_copy_metadata</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *to, struct <a href="ident?i=sk_buff">sk_buff</a> *from)
<a name="L459" href="source/net/ipv4/ip_output.c#L459">459</a> {
<a name="L460" href="source/net/ipv4/ip_output.c#L460">460</a>         to-&gt;pkt_type = from-&gt;pkt_type;
<a name="L461" href="source/net/ipv4/ip_output.c#L461">461</a>         to-&gt;<a href="ident?i=priority">priority</a> = from-&gt;<a href="ident?i=priority">priority</a>;
<a name="L462" href="source/net/ipv4/ip_output.c#L462">462</a>         to-&gt;<a href="ident?i=protocol">protocol</a> = from-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L463" href="source/net/ipv4/ip_output.c#L463">463</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(to);
<a name="L464" href="source/net/ipv4/ip_output.c#L464">464</a>         <a href="ident?i=skb_dst_copy">skb_dst_copy</a>(to, from);
<a name="L465" href="source/net/ipv4/ip_output.c#L465">465</a>         to-&gt;<a href="ident?i=dev">dev</a> = from-&gt;<a href="ident?i=dev">dev</a>;
<a name="L466" href="source/net/ipv4/ip_output.c#L466">466</a>         to-&gt;<a href="ident?i=mark">mark</a> = from-&gt;<a href="ident?i=mark">mark</a>;
<a name="L467" href="source/net/ipv4/ip_output.c#L467">467</a> 
<a name="L468" href="source/net/ipv4/ip_output.c#L468">468</a>         <b><i>/* Copy the flags to each fragment. */</i></b>
<a name="L469" href="source/net/ipv4/ip_output.c#L469">469</a>         <a href="ident?i=IPCB">IPCB</a>(to)-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=IPCB">IPCB</a>(from)-&gt;<a href="ident?i=flags">flags</a>;
<a name="L470" href="source/net/ipv4/ip_output.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/ip_output.c#L471">471</a> #ifdef CONFIG_NET_SCHED
<a name="L472" href="source/net/ipv4/ip_output.c#L472">472</a>         to-&gt;tc_index = from-&gt;tc_index;
<a name="L473" href="source/net/ipv4/ip_output.c#L473">473</a> #endif
<a name="L474" href="source/net/ipv4/ip_output.c#L474">474</a>         <a href="ident?i=nf_copy">nf_copy</a>(to, from);
<a name="L475" href="source/net/ipv4/ip_output.c#L475">475</a> #if defined(CONFIG_IP_VS) || defined(CONFIG_IP_VS_MODULE)
<a name="L476" href="source/net/ipv4/ip_output.c#L476">476</a>         to-&gt;ipvs_property = from-&gt;ipvs_property;
<a name="L477" href="source/net/ipv4/ip_output.c#L477">477</a> #endif
<a name="L478" href="source/net/ipv4/ip_output.c#L478">478</a>         <a href="ident?i=skb_copy_secmark">skb_copy_secmark</a>(to, from);
<a name="L479" href="source/net/ipv4/ip_output.c#L479">479</a> }
<a name="L480" href="source/net/ipv4/ip_output.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/ip_output.c#L481">481</a> <b><i>/*</i></b>
<a name="L482" href="source/net/ipv4/ip_output.c#L482">482</a> <b><i> *      This IP datagram is too large to be sent in one piece.  Break it up into</i></b>
<a name="L483" href="source/net/ipv4/ip_output.c#L483">483</a> <b><i> *      smaller pieces (each of size equal to IP header plus</i></b>
<a name="L484" href="source/net/ipv4/ip_output.c#L484">484</a> <b><i> *      a block of the data of the original IP data part) that will yet fit in a</i></b>
<a name="L485" href="source/net/ipv4/ip_output.c#L485">485</a> <b><i> *      single device frame, and queue such a frame for sending.</i></b>
<a name="L486" href="source/net/ipv4/ip_output.c#L486">486</a> <b><i> */</i></b>
<a name="L487" href="source/net/ipv4/ip_output.c#L487">487</a> 
<a name="L488" href="source/net/ipv4/ip_output.c#L488">488</a> int <a href="ident?i=ip_fragment">ip_fragment</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L489" href="source/net/ipv4/ip_output.c#L489">489</a>                 int (*<a href="ident?i=output">output</a>)(struct <a href="ident?i=sock">sock</a> *, struct <a href="ident?i=sk_buff">sk_buff</a> *))
<a name="L490" href="source/net/ipv4/ip_output.c#L490">490</a> {
<a name="L491" href="source/net/ipv4/ip_output.c#L491">491</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L492" href="source/net/ipv4/ip_output.c#L492">492</a>         int <a href="ident?i=ptr">ptr</a>;
<a name="L493" href="source/net/ipv4/ip_output.c#L493">493</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L494" href="source/net/ipv4/ip_output.c#L494">494</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *skb2;
<a name="L495" href="source/net/ipv4/ip_output.c#L495">495</a>         unsigned int <a href="ident?i=mtu">mtu</a>, hlen, <a href="ident?i=left">left</a>, <a href="ident?i=len">len</a>, ll_rs;
<a name="L496" href="source/net/ipv4/ip_output.c#L496">496</a>         int <a href="ident?i=offset">offset</a>;
<a name="L497" href="source/net/ipv4/ip_output.c#L497">497</a>         <a href="ident?i=__be16">__be16</a> not_last_frag;
<a name="L498" href="source/net/ipv4/ip_output.c#L498">498</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L499" href="source/net/ipv4/ip_output.c#L499">499</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L500" href="source/net/ipv4/ip_output.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/ip_output.c#L501">501</a>         <a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L502" href="source/net/ipv4/ip_output.c#L502">502</a> 
<a name="L503" href="source/net/ipv4/ip_output.c#L503">503</a>         <b><i>/*</i></b>
<a name="L504" href="source/net/ipv4/ip_output.c#L504">504</a> <b><i>         *      Point into the IP datagram header.</i></b>
<a name="L505" href="source/net/ipv4/ip_output.c#L505">505</a> <b><i>         */</i></b>
<a name="L506" href="source/net/ipv4/ip_output.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/ip_output.c#L507">507</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L508" href="source/net/ipv4/ip_output.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/ip_output.c#L509">509</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=ip_skb_dst_mtu">ip_skb_dst_mtu</a>(<a href="ident?i=skb">skb</a>);
<a name="L510" href="source/net/ipv4/ip_output.c#L510">510</a>         if (<a href="ident?i=unlikely">unlikely</a>(((iph-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>)) &amp;&amp; !<a href="ident?i=skb">skb</a>-&gt;ignore_df) ||
<a name="L511" href="source/net/ipv4/ip_output.c#L511">511</a>                      (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_max_size &amp;&amp;
<a name="L512" href="source/net/ipv4/ip_output.c#L512">512</a>                       <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_max_size &gt; <a href="ident?i=mtu">mtu</a>))) {
<a name="L513" href="source/net/ipv4/ip_output.c#L513">513</a>                 <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGFAILS);
<a name="L514" href="source/net/ipv4/ip_output.c#L514">514</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>,
<a name="L515" href="source/net/ipv4/ip_output.c#L515">515</a>                           <a href="ident?i=htonl">htonl</a>(<a href="ident?i=mtu">mtu</a>));
<a name="L516" href="source/net/ipv4/ip_output.c#L516">516</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L517" href="source/net/ipv4/ip_output.c#L517">517</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L518" href="source/net/ipv4/ip_output.c#L518">518</a>         }
<a name="L519" href="source/net/ipv4/ip_output.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/ip_output.c#L520">520</a>         <b><i>/*</i></b>
<a name="L521" href="source/net/ipv4/ip_output.c#L521">521</a> <b><i>         *      Setup starting values.</i></b>
<a name="L522" href="source/net/ipv4/ip_output.c#L522">522</a> <b><i>         */</i></b>
<a name="L523" href="source/net/ipv4/ip_output.c#L523">523</a> 
<a name="L524" href="source/net/ipv4/ip_output.c#L524">524</a>         hlen = iph-&gt;ihl * 4;
<a name="L525" href="source/net/ipv4/ip_output.c#L525">525</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=mtu">mtu</a> - hlen;       <b><i>/* Size of data space */</i></b>
<a name="L526" href="source/net/ipv4/ip_output.c#L526">526</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_BRIDGE_NETFILTER)
<a name="L527" href="source/net/ipv4/ip_output.c#L527">527</a>         if (<a href="ident?i=skb">skb</a>-&gt;nf_bridge)
<a name="L528" href="source/net/ipv4/ip_output.c#L528">528</a>                 <a href="ident?i=mtu">mtu</a> -= <a href="ident?i=nf_bridge_mtu_reduction">nf_bridge_mtu_reduction</a>(<a href="ident?i=skb">skb</a>);
<a name="L529" href="source/net/ipv4/ip_output.c#L529">529</a> #endif
<a name="L530" href="source/net/ipv4/ip_output.c#L530">530</a>         <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_FRAG_COMPLETE">IPSKB_FRAG_COMPLETE</a>;
<a name="L531" href="source/net/ipv4/ip_output.c#L531">531</a> 
<a name="L532" href="source/net/ipv4/ip_output.c#L532">532</a>         <b><i>/* When frag_list is given, use it. First, check its validity:</i></b>
<a name="L533" href="source/net/ipv4/ip_output.c#L533">533</a> <b><i>         * some transformers could create wrong frag_list or break existing</i></b>
<a name="L534" href="source/net/ipv4/ip_output.c#L534">534</a> <b><i>         * one, it is not prohibited. In this case fall back to copying.</i></b>
<a name="L535" href="source/net/ipv4/ip_output.c#L535">535</a> <b><i>         *</i></b>
<a name="L536" href="source/net/ipv4/ip_output.c#L536">536</a> <b><i>         * LATER: this step can be merged to real generation of fragments,</i></b>
<a name="L537" href="source/net/ipv4/ip_output.c#L537">537</a> <b><i>         * we can switch to copy when see the first bad fragment.</i></b>
<a name="L538" href="source/net/ipv4/ip_output.c#L538">538</a> <b><i>         */</i></b>
<a name="L539" href="source/net/ipv4/ip_output.c#L539">539</a>         if (<a href="ident?i=skb_has_frag_list">skb_has_frag_list</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L540" href="source/net/ipv4/ip_output.c#L540">540</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=frag">frag</a>, *frag2;
<a name="L541" href="source/net/ipv4/ip_output.c#L541">541</a>                 int first_len = <a href="ident?i=skb_pagelen">skb_pagelen</a>(<a href="ident?i=skb">skb</a>);
<a name="L542" href="source/net/ipv4/ip_output.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/ip_output.c#L543">543</a>                 if (first_len - hlen &gt; <a href="ident?i=mtu">mtu</a> ||
<a name="L544" href="source/net/ipv4/ip_output.c#L544">544</a>                     ((first_len - hlen) &amp; 7) ||
<a name="L545" href="source/net/ipv4/ip_output.c#L545">545</a>                     <a href="ident?i=ip_is_fragment">ip_is_fragment</a>(iph) ||
<a name="L546" href="source/net/ipv4/ip_output.c#L546">546</a>                     <a href="ident?i=skb_cloned">skb_cloned</a>(<a href="ident?i=skb">skb</a>))
<a name="L547" href="source/net/ipv4/ip_output.c#L547">547</a>                         goto slow_path;
<a name="L548" href="source/net/ipv4/ip_output.c#L548">548</a> 
<a name="L549" href="source/net/ipv4/ip_output.c#L549">549</a>                 <a href="ident?i=skb_walk_frags">skb_walk_frags</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=frag">frag</a>) {
<a name="L550" href="source/net/ipv4/ip_output.c#L550">550</a>                         <b><i>/* Correct geometry. */</i></b>
<a name="L551" href="source/net/ipv4/ip_output.c#L551">551</a>                         if (<a href="ident?i=frag">frag</a>-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=mtu">mtu</a> ||
<a name="L552" href="source/net/ipv4/ip_output.c#L552">552</a>                             ((<a href="ident?i=frag">frag</a>-&gt;<a href="ident?i=len">len</a> &amp; 7) &amp;&amp; <a href="ident?i=frag">frag</a>-&gt;<a href="ident?i=next">next</a>) ||
<a name="L553" href="source/net/ipv4/ip_output.c#L553">553</a>                             <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=frag">frag</a>) &lt; hlen)
<a name="L554" href="source/net/ipv4/ip_output.c#L554">554</a>                                 goto slow_path_clean;
<a name="L555" href="source/net/ipv4/ip_output.c#L555">555</a> 
<a name="L556" href="source/net/ipv4/ip_output.c#L556">556</a>                         <b><i>/* Partially cloned skb? */</i></b>
<a name="L557" href="source/net/ipv4/ip_output.c#L557">557</a>                         if (<a href="ident?i=skb_shared">skb_shared</a>(<a href="ident?i=frag">frag</a>))
<a name="L558" href="source/net/ipv4/ip_output.c#L558">558</a>                                 goto slow_path_clean;
<a name="L559" href="source/net/ipv4/ip_output.c#L559">559</a> 
<a name="L560" href="source/net/ipv4/ip_output.c#L560">560</a>                         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=frag">frag</a>-&gt;sk);
<a name="L561" href="source/net/ipv4/ip_output.c#L561">561</a>                         if (<a href="ident?i=skb">skb</a>-&gt;sk) {
<a name="L562" href="source/net/ipv4/ip_output.c#L562">562</a>                                 <a href="ident?i=frag">frag</a>-&gt;sk = <a href="ident?i=skb">skb</a>-&gt;sk;
<a name="L563" href="source/net/ipv4/ip_output.c#L563">563</a>                                 <a href="ident?i=frag">frag</a>-&gt;destructor = <a href="ident?i=sock_wfree">sock_wfree</a>;
<a name="L564" href="source/net/ipv4/ip_output.c#L564">564</a>                         }
<a name="L565" href="source/net/ipv4/ip_output.c#L565">565</a>                         <a href="ident?i=skb">skb</a>-&gt;truesize -= <a href="ident?i=frag">frag</a>-&gt;truesize;
<a name="L566" href="source/net/ipv4/ip_output.c#L566">566</a>                 }
<a name="L567" href="source/net/ipv4/ip_output.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/ip_output.c#L568">568</a>                 <b><i>/* Everything is OK. Generate! */</i></b>
<a name="L569" href="source/net/ipv4/ip_output.c#L569">569</a> 
<a name="L570" href="source/net/ipv4/ip_output.c#L570">570</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L571" href="source/net/ipv4/ip_output.c#L571">571</a>                 <a href="ident?i=offset">offset</a> = 0;
<a name="L572" href="source/net/ipv4/ip_output.c#L572">572</a>                 <a href="ident?i=frag">frag</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_list;
<a name="L573" href="source/net/ipv4/ip_output.c#L573">573</a>                 <a href="ident?i=skb_frag_list_init">skb_frag_list_init</a>(<a href="ident?i=skb">skb</a>);
<a name="L574" href="source/net/ipv4/ip_output.c#L574">574</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a> = first_len - <a href="ident?i=skb_headlen">skb_headlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L575" href="source/net/ipv4/ip_output.c#L575">575</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> = first_len;
<a name="L576" href="source/net/ipv4/ip_output.c#L576">576</a>                 iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(first_len);
<a name="L577" href="source/net/ipv4/ip_output.c#L577">577</a>                 iph-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_MF">IP_MF</a>);
<a name="L578" href="source/net/ipv4/ip_output.c#L578">578</a>                 <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L579" href="source/net/ipv4/ip_output.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/ip_output.c#L580">580</a>                 for (;;) {
<a name="L581" href="source/net/ipv4/ip_output.c#L581">581</a>                         <b><i>/* Prepare header of the next frame,</i></b>
<a name="L582" href="source/net/ipv4/ip_output.c#L582">582</a> <b><i>                         * before previous one went down. */</i></b>
<a name="L583" href="source/net/ipv4/ip_output.c#L583">583</a>                         if (<a href="ident?i=frag">frag</a>) {
<a name="L584" href="source/net/ipv4/ip_output.c#L584">584</a>                                 <a href="ident?i=frag">frag</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L585" href="source/net/ipv4/ip_output.c#L585">585</a>                                 <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=frag">frag</a>);
<a name="L586" href="source/net/ipv4/ip_output.c#L586">586</a>                                 <a href="ident?i=__skb_push">__skb_push</a>(<a href="ident?i=frag">frag</a>, hlen);
<a name="L587" href="source/net/ipv4/ip_output.c#L587">587</a>                                 <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=frag">frag</a>);
<a name="L588" href="source/net/ipv4/ip_output.c#L588">588</a>                                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=frag">frag</a>), iph, hlen);
<a name="L589" href="source/net/ipv4/ip_output.c#L589">589</a>                                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=frag">frag</a>);
<a name="L590" href="source/net/ipv4/ip_output.c#L590">590</a>                                 iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=frag">frag</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L591" href="source/net/ipv4/ip_output.c#L591">591</a>                                 <a href="ident?i=ip_copy_metadata">ip_copy_metadata</a>(<a href="ident?i=frag">frag</a>, <a href="ident?i=skb">skb</a>);
<a name="L592" href="source/net/ipv4/ip_output.c#L592">592</a>                                 if (<a href="ident?i=offset">offset</a> == 0)
<a name="L593" href="source/net/ipv4/ip_output.c#L593">593</a>                                         <a href="ident?i=ip_options_fragment">ip_options_fragment</a>(<a href="ident?i=frag">frag</a>);
<a name="L594" href="source/net/ipv4/ip_output.c#L594">594</a>                                 <a href="ident?i=offset">offset</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - hlen;
<a name="L595" href="source/net/ipv4/ip_output.c#L595">595</a>                                 iph-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=offset">offset</a>&gt;&gt;3);
<a name="L596" href="source/net/ipv4/ip_output.c#L596">596</a>                                 if (<a href="ident?i=frag">frag</a>-&gt;<a href="ident?i=next">next</a>)
<a name="L597" href="source/net/ipv4/ip_output.c#L597">597</a>                                         iph-&gt;frag_off |= <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_MF">IP_MF</a>);
<a name="L598" href="source/net/ipv4/ip_output.c#L598">598</a>                                 <b><i>/* Ready, complete checksum */</i></b>
<a name="L599" href="source/net/ipv4/ip_output.c#L599">599</a>                                 <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L600" href="source/net/ipv4/ip_output.c#L600">600</a>                         }
<a name="L601" href="source/net/ipv4/ip_output.c#L601">601</a> 
<a name="L602" href="source/net/ipv4/ip_output.c#L602">602</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=output">output</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L603" href="source/net/ipv4/ip_output.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/ip_output.c#L604">604</a>                         if (!<a href="ident?i=err">err</a>)
<a name="L605" href="source/net/ipv4/ip_output.c#L605">605</a>                                 <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGCREATES);
<a name="L606" href="source/net/ipv4/ip_output.c#L606">606</a>                         if (<a href="ident?i=err">err</a> || !<a href="ident?i=frag">frag</a>)
<a name="L607" href="source/net/ipv4/ip_output.c#L607">607</a>                                 break;
<a name="L608" href="source/net/ipv4/ip_output.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/ip_output.c#L609">609</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=frag">frag</a>;
<a name="L610" href="source/net/ipv4/ip_output.c#L610">610</a>                         <a href="ident?i=frag">frag</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L611" href="source/net/ipv4/ip_output.c#L611">611</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L612" href="source/net/ipv4/ip_output.c#L612">612</a>                 }
<a name="L613" href="source/net/ipv4/ip_output.c#L613">613</a> 
<a name="L614" href="source/net/ipv4/ip_output.c#L614">614</a>                 if (<a href="ident?i=err">err</a> == 0) {
<a name="L615" href="source/net/ipv4/ip_output.c#L615">615</a>                         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGOKS);
<a name="L616" href="source/net/ipv4/ip_output.c#L616">616</a>                         return 0;
<a name="L617" href="source/net/ipv4/ip_output.c#L617">617</a>                 }
<a name="L618" href="source/net/ipv4/ip_output.c#L618">618</a> 
<a name="L619" href="source/net/ipv4/ip_output.c#L619">619</a>                 while (<a href="ident?i=frag">frag</a>) {
<a name="L620" href="source/net/ipv4/ip_output.c#L620">620</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=frag">frag</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L621" href="source/net/ipv4/ip_output.c#L621">621</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=frag">frag</a>);
<a name="L622" href="source/net/ipv4/ip_output.c#L622">622</a>                         <a href="ident?i=frag">frag</a> = <a href="ident?i=skb">skb</a>;
<a name="L623" href="source/net/ipv4/ip_output.c#L623">623</a>                 }
<a name="L624" href="source/net/ipv4/ip_output.c#L624">624</a>                 <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGFAILS);
<a name="L625" href="source/net/ipv4/ip_output.c#L625">625</a>                 return <a href="ident?i=err">err</a>;
<a name="L626" href="source/net/ipv4/ip_output.c#L626">626</a> 
<a name="L627" href="source/net/ipv4/ip_output.c#L627">627</a> slow_path_clean:
<a name="L628" href="source/net/ipv4/ip_output.c#L628">628</a>                 <a href="ident?i=skb_walk_frags">skb_walk_frags</a>(<a href="ident?i=skb">skb</a>, frag2) {
<a name="L629" href="source/net/ipv4/ip_output.c#L629">629</a>                         if (frag2 == <a href="ident?i=frag">frag</a>)
<a name="L630" href="source/net/ipv4/ip_output.c#L630">630</a>                                 break;
<a name="L631" href="source/net/ipv4/ip_output.c#L631">631</a>                         frag2-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L632" href="source/net/ipv4/ip_output.c#L632">632</a>                         frag2-&gt;destructor = <a href="ident?i=NULL">NULL</a>;
<a name="L633" href="source/net/ipv4/ip_output.c#L633">633</a>                         <a href="ident?i=skb">skb</a>-&gt;truesize += frag2-&gt;truesize;
<a name="L634" href="source/net/ipv4/ip_output.c#L634">634</a>                 }
<a name="L635" href="source/net/ipv4/ip_output.c#L635">635</a>         }
<a name="L636" href="source/net/ipv4/ip_output.c#L636">636</a> 
<a name="L637" href="source/net/ipv4/ip_output.c#L637">637</a> slow_path:
<a name="L638" href="source/net/ipv4/ip_output.c#L638">638</a>         <b><i>/* for offloaded checksums cleanup checksum before fragmentation */</i></b>
<a name="L639" href="source/net/ipv4/ip_output.c#L639">639</a>         if ((<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) &amp;&amp; <a href="ident?i=skb_checksum_help">skb_checksum_help</a>(<a href="ident?i=skb">skb</a>))
<a name="L640" href="source/net/ipv4/ip_output.c#L640">640</a>                 goto <a href="ident?i=fail">fail</a>;
<a name="L641" href="source/net/ipv4/ip_output.c#L641">641</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L642" href="source/net/ipv4/ip_output.c#L642">642</a> 
<a name="L643" href="source/net/ipv4/ip_output.c#L643">643</a>         <a href="ident?i=left">left</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - hlen;         <b><i>/* Space per frame */</i></b>
<a name="L644" href="source/net/ipv4/ip_output.c#L644">644</a>         <a href="ident?i=ptr">ptr</a> = hlen;             <b><i>/* Where to start from */</i></b>
<a name="L645" href="source/net/ipv4/ip_output.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/ip_output.c#L646">646</a>         ll_rs = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L647" href="source/net/ipv4/ip_output.c#L647">647</a> 
<a name="L648" href="source/net/ipv4/ip_output.c#L648">648</a>         <b><i>/*</i></b>
<a name="L649" href="source/net/ipv4/ip_output.c#L649">649</a> <b><i>         *      Fragment the datagram.</i></b>
<a name="L650" href="source/net/ipv4/ip_output.c#L650">650</a> <b><i>         */</i></b>
<a name="L651" href="source/net/ipv4/ip_output.c#L651">651</a> 
<a name="L652" href="source/net/ipv4/ip_output.c#L652">652</a>         <a href="ident?i=offset">offset</a> = (<a href="ident?i=ntohs">ntohs</a>(iph-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>) &lt;&lt; 3;
<a name="L653" href="source/net/ipv4/ip_output.c#L653">653</a>         not_last_frag = iph-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_MF">IP_MF</a>);
<a name="L654" href="source/net/ipv4/ip_output.c#L654">654</a> 
<a name="L655" href="source/net/ipv4/ip_output.c#L655">655</a>         <b><i>/*</i></b>
<a name="L656" href="source/net/ipv4/ip_output.c#L656">656</a> <b><i>         *      Keep copying data until we run out.</i></b>
<a name="L657" href="source/net/ipv4/ip_output.c#L657">657</a> <b><i>         */</i></b>
<a name="L658" href="source/net/ipv4/ip_output.c#L658">658</a> 
<a name="L659" href="source/net/ipv4/ip_output.c#L659">659</a>         while (<a href="ident?i=left">left</a> &gt; 0) {
<a name="L660" href="source/net/ipv4/ip_output.c#L660">660</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=left">left</a>;
<a name="L661" href="source/net/ipv4/ip_output.c#L661">661</a>                 <b><i>/* IF: it doesn't fit, use 'mtu' - the data space left */</i></b>
<a name="L662" href="source/net/ipv4/ip_output.c#L662">662</a>                 if (<a href="ident?i=len">len</a> &gt; <a href="ident?i=mtu">mtu</a>)
<a name="L663" href="source/net/ipv4/ip_output.c#L663">663</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=mtu">mtu</a>;
<a name="L664" href="source/net/ipv4/ip_output.c#L664">664</a>                 <b><i>/* IF: we are not sending up to and including the packet end</i></b>
<a name="L665" href="source/net/ipv4/ip_output.c#L665">665</a> <b><i>                   then align the next start on an eight byte boundary */</i></b>
<a name="L666" href="source/net/ipv4/ip_output.c#L666">666</a>                 if (<a href="ident?i=len">len</a> &lt; <a href="ident?i=left">left</a>) {
<a name="L667" href="source/net/ipv4/ip_output.c#L667">667</a>                         <a href="ident?i=len">len</a> &amp;= ~7;
<a name="L668" href="source/net/ipv4/ip_output.c#L668">668</a>                 }
<a name="L669" href="source/net/ipv4/ip_output.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/ip_output.c#L670">670</a>                 <b><i>/* Allocate buffer */</i></b>
<a name="L671" href="source/net/ipv4/ip_output.c#L671">671</a>                 skb2 = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=len">len</a> + hlen + ll_rs, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L672" href="source/net/ipv4/ip_output.c#L672">672</a>                 if (!skb2) {
<a name="L673" href="source/net/ipv4/ip_output.c#L673">673</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L674" href="source/net/ipv4/ip_output.c#L674">674</a>                         goto <a href="ident?i=fail">fail</a>;
<a name="L675" href="source/net/ipv4/ip_output.c#L675">675</a>                 }
<a name="L676" href="source/net/ipv4/ip_output.c#L676">676</a> 
<a name="L677" href="source/net/ipv4/ip_output.c#L677">677</a>                 <b><i>/*</i></b>
<a name="L678" href="source/net/ipv4/ip_output.c#L678">678</a> <b><i>                 *      Set up data on packet</i></b>
<a name="L679" href="source/net/ipv4/ip_output.c#L679">679</a> <b><i>                 */</i></b>
<a name="L680" href="source/net/ipv4/ip_output.c#L680">680</a> 
<a name="L681" href="source/net/ipv4/ip_output.c#L681">681</a>                 <a href="ident?i=ip_copy_metadata">ip_copy_metadata</a>(skb2, <a href="ident?i=skb">skb</a>);
<a name="L682" href="source/net/ipv4/ip_output.c#L682">682</a>                 <a href="ident?i=skb_reserve">skb_reserve</a>(skb2, ll_rs);
<a name="L683" href="source/net/ipv4/ip_output.c#L683">683</a>                 <a href="ident?i=skb_put">skb_put</a>(skb2, <a href="ident?i=len">len</a> + hlen);
<a name="L684" href="source/net/ipv4/ip_output.c#L684">684</a>                 <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(skb2);
<a name="L685" href="source/net/ipv4/ip_output.c#L685">685</a>                 skb2-&gt;transport_header = skb2-&gt;network_header + hlen;
<a name="L686" href="source/net/ipv4/ip_output.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/ip_output.c#L687">687</a>                 <b><i>/*</i></b>
<a name="L688" href="source/net/ipv4/ip_output.c#L688">688</a> <b><i>                 *      Charge the memory for the fragment to any owner</i></b>
<a name="L689" href="source/net/ipv4/ip_output.c#L689">689</a> <b><i>                 *      it might possess</i></b>
<a name="L690" href="source/net/ipv4/ip_output.c#L690">690</a> <b><i>                 */</i></b>
<a name="L691" href="source/net/ipv4/ip_output.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/ip_output.c#L692">692</a>                 if (<a href="ident?i=skb">skb</a>-&gt;sk)
<a name="L693" href="source/net/ipv4/ip_output.c#L693">693</a>                         <a href="ident?i=skb_set_owner_w">skb_set_owner_w</a>(skb2, <a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L694" href="source/net/ipv4/ip_output.c#L694">694</a> 
<a name="L695" href="source/net/ipv4/ip_output.c#L695">695</a>                 <b><i>/*</i></b>
<a name="L696" href="source/net/ipv4/ip_output.c#L696">696</a> <b><i>                 *      Copy the packet header into the new buffer.</i></b>
<a name="L697" href="source/net/ipv4/ip_output.c#L697">697</a> <b><i>                 */</i></b>
<a name="L698" href="source/net/ipv4/ip_output.c#L698">698</a> 
<a name="L699" href="source/net/ipv4/ip_output.c#L699">699</a>                 <a href="ident?i=skb_copy_from_linear_data">skb_copy_from_linear_data</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_network_header">skb_network_header</a>(skb2), hlen);
<a name="L700" href="source/net/ipv4/ip_output.c#L700">700</a> 
<a name="L701" href="source/net/ipv4/ip_output.c#L701">701</a>                 <b><i>/*</i></b>
<a name="L702" href="source/net/ipv4/ip_output.c#L702">702</a> <b><i>                 *      Copy a block of the IP datagram.</i></b>
<a name="L703" href="source/net/ipv4/ip_output.c#L703">703</a> <b><i>                 */</i></b>
<a name="L704" href="source/net/ipv4/ip_output.c#L704">704</a>                 if (<a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ptr">ptr</a>, <a href="ident?i=skb_transport_header">skb_transport_header</a>(skb2), <a href="ident?i=len">len</a>))
<a name="L705" href="source/net/ipv4/ip_output.c#L705">705</a>                         <a href="ident?i=BUG">BUG</a>();
<a name="L706" href="source/net/ipv4/ip_output.c#L706">706</a>                 <a href="ident?i=left">left</a> -= <a href="ident?i=len">len</a>;
<a name="L707" href="source/net/ipv4/ip_output.c#L707">707</a> 
<a name="L708" href="source/net/ipv4/ip_output.c#L708">708</a>                 <b><i>/*</i></b>
<a name="L709" href="source/net/ipv4/ip_output.c#L709">709</a> <b><i>                 *      Fill in the new header fields.</i></b>
<a name="L710" href="source/net/ipv4/ip_output.c#L710">710</a> <b><i>                 */</i></b>
<a name="L711" href="source/net/ipv4/ip_output.c#L711">711</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(skb2);
<a name="L712" href="source/net/ipv4/ip_output.c#L712">712</a>                 iph-&gt;frag_off = <a href="ident?i=htons">htons</a>((<a href="ident?i=offset">offset</a> &gt;&gt; 3));
<a name="L713" href="source/net/ipv4/ip_output.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/ip_output.c#L714">714</a>                 <b><i>/* ANK: dirty, but effective trick. Upgrade options only if</i></b>
<a name="L715" href="source/net/ipv4/ip_output.c#L715">715</a> <b><i>                 * the segment to be fragmented was THE FIRST (otherwise,</i></b>
<a name="L716" href="source/net/ipv4/ip_output.c#L716">716</a> <b><i>                 * options are already fixed) and make it ONCE</i></b>
<a name="L717" href="source/net/ipv4/ip_output.c#L717">717</a> <b><i>                 * on the initial skb, so that all the following fragments</i></b>
<a name="L718" href="source/net/ipv4/ip_output.c#L718">718</a> <b><i>                 * will inherit fixed options.</i></b>
<a name="L719" href="source/net/ipv4/ip_output.c#L719">719</a> <b><i>                 */</i></b>
<a name="L720" href="source/net/ipv4/ip_output.c#L720">720</a>                 if (<a href="ident?i=offset">offset</a> == 0)
<a name="L721" href="source/net/ipv4/ip_output.c#L721">721</a>                         <a href="ident?i=ip_options_fragment">ip_options_fragment</a>(<a href="ident?i=skb">skb</a>);
<a name="L722" href="source/net/ipv4/ip_output.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/ip_output.c#L723">723</a>                 <b><i>/*</i></b>
<a name="L724" href="source/net/ipv4/ip_output.c#L724">724</a> <b><i>                 *      Added AC : If we are fragmenting a fragment that's not the</i></b>
<a name="L725" href="source/net/ipv4/ip_output.c#L725">725</a> <b><i>                 *                 last fragment then keep MF on each bit</i></b>
<a name="L726" href="source/net/ipv4/ip_output.c#L726">726</a> <b><i>                 */</i></b>
<a name="L727" href="source/net/ipv4/ip_output.c#L727">727</a>                 if (<a href="ident?i=left">left</a> &gt; 0 || not_last_frag)
<a name="L728" href="source/net/ipv4/ip_output.c#L728">728</a>                         iph-&gt;frag_off |= <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_MF">IP_MF</a>);
<a name="L729" href="source/net/ipv4/ip_output.c#L729">729</a>                 <a href="ident?i=ptr">ptr</a> += <a href="ident?i=len">len</a>;
<a name="L730" href="source/net/ipv4/ip_output.c#L730">730</a>                 <a href="ident?i=offset">offset</a> += <a href="ident?i=len">len</a>;
<a name="L731" href="source/net/ipv4/ip_output.c#L731">731</a> 
<a name="L732" href="source/net/ipv4/ip_output.c#L732">732</a>                 <b><i>/*</i></b>
<a name="L733" href="source/net/ipv4/ip_output.c#L733">733</a> <b><i>                 *      Put this fragment into the sending queue.</i></b>
<a name="L734" href="source/net/ipv4/ip_output.c#L734">734</a> <b><i>                 */</i></b>
<a name="L735" href="source/net/ipv4/ip_output.c#L735">735</a>                 iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=len">len</a> + hlen);
<a name="L736" href="source/net/ipv4/ip_output.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/ip_output.c#L737">737</a>                 <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L738" href="source/net/ipv4/ip_output.c#L738">738</a> 
<a name="L739" href="source/net/ipv4/ip_output.c#L739">739</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=output">output</a>(sk, skb2);
<a name="L740" href="source/net/ipv4/ip_output.c#L740">740</a>                 if (<a href="ident?i=err">err</a>)
<a name="L741" href="source/net/ipv4/ip_output.c#L741">741</a>                         goto <a href="ident?i=fail">fail</a>;
<a name="L742" href="source/net/ipv4/ip_output.c#L742">742</a> 
<a name="L743" href="source/net/ipv4/ip_output.c#L743">743</a>                 <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGCREATES);
<a name="L744" href="source/net/ipv4/ip_output.c#L744">744</a>         }
<a name="L745" href="source/net/ipv4/ip_output.c#L745">745</a>         <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L746" href="source/net/ipv4/ip_output.c#L746">746</a>         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGOKS);
<a name="L747" href="source/net/ipv4/ip_output.c#L747">747</a>         return <a href="ident?i=err">err</a>;
<a name="L748" href="source/net/ipv4/ip_output.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/ip_output.c#L749">749</a> <a href="ident?i=fail">fail</a>:
<a name="L750" href="source/net/ipv4/ip_output.c#L750">750</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L751" href="source/net/ipv4/ip_output.c#L751">751</a>         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), IPSTATS_MIB_FRAGFAILS);
<a name="L752" href="source/net/ipv4/ip_output.c#L752">752</a>         return <a href="ident?i=err">err</a>;
<a name="L753" href="source/net/ipv4/ip_output.c#L753">753</a> }
<a name="L754" href="source/net/ipv4/ip_output.c#L754">754</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_fragment">ip_fragment</a>);
<a name="L755" href="source/net/ipv4/ip_output.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/ip_output.c#L756">756</a> int
<a name="L757" href="source/net/ipv4/ip_output.c#L757">757</a> <a href="ident?i=ip_generic_getfrag">ip_generic_getfrag</a>(void *from, char *to, int <a href="ident?i=offset">offset</a>, int <a href="ident?i=len">len</a>, int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L758" href="source/net/ipv4/ip_output.c#L758">758</a> {
<a name="L759" href="source/net/ipv4/ip_output.c#L759">759</a>         struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a> = from;
<a name="L760" href="source/net/ipv4/ip_output.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/ip_output.c#L761">761</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) {
<a name="L762" href="source/net/ipv4/ip_output.c#L762">762</a>                 if (<a href="ident?i=copy_from_iter">copy_from_iter</a>(to, <a href="ident?i=len">len</a>, &amp;<a href="ident?i=msg">msg</a>-&gt;msg_iter) != <a href="ident?i=len">len</a>)
<a name="L763" href="source/net/ipv4/ip_output.c#L763">763</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L764" href="source/net/ipv4/ip_output.c#L764">764</a>         } else {
<a name="L765" href="source/net/ipv4/ip_output.c#L765">765</a>                 <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a> = 0;
<a name="L766" href="source/net/ipv4/ip_output.c#L766">766</a>                 if (<a href="ident?i=csum_and_copy_from_iter">csum_and_copy_from_iter</a>(to, <a href="ident?i=len">len</a>, &amp;<a href="ident?i=csum">csum</a>, &amp;<a href="ident?i=msg">msg</a>-&gt;msg_iter) != <a href="ident?i=len">len</a>)
<a name="L767" href="source/net/ipv4/ip_output.c#L767">767</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L768" href="source/net/ipv4/ip_output.c#L768">768</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_add">csum_block_add</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>, <a href="ident?i=csum">csum</a>, odd);
<a name="L769" href="source/net/ipv4/ip_output.c#L769">769</a>         }
<a name="L770" href="source/net/ipv4/ip_output.c#L770">770</a>         return 0;
<a name="L771" href="source/net/ipv4/ip_output.c#L771">771</a> }
<a name="L772" href="source/net/ipv4/ip_output.c#L772">772</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_generic_getfrag">ip_generic_getfrag</a>);
<a name="L773" href="source/net/ipv4/ip_output.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/ip_output.c#L774">774</a> static inline <a href="ident?i=__wsum">__wsum</a>
<a name="L775" href="source/net/ipv4/ip_output.c#L775">775</a> <a href="ident?i=csum_page">csum_page</a>(struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>, int <a href="ident?i=offset">offset</a>, int <a href="ident?i=copy">copy</a>)
<a name="L776" href="source/net/ipv4/ip_output.c#L776">776</a> {
<a name="L777" href="source/net/ipv4/ip_output.c#L777">777</a>         char *kaddr;
<a name="L778" href="source/net/ipv4/ip_output.c#L778">778</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a>;
<a name="L779" href="source/net/ipv4/ip_output.c#L779">779</a>         kaddr = <a href="ident?i=kmap">kmap</a>(<a href="ident?i=page">page</a>);
<a name="L780" href="source/net/ipv4/ip_output.c#L780">780</a>         <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_partial">csum_partial</a>(kaddr + <a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>, 0);
<a name="L781" href="source/net/ipv4/ip_output.c#L781">781</a>         <a href="ident?i=kunmap">kunmap</a>(<a href="ident?i=page">page</a>);
<a name="L782" href="source/net/ipv4/ip_output.c#L782">782</a>         return <a href="ident?i=csum">csum</a>;
<a name="L783" href="source/net/ipv4/ip_output.c#L783">783</a> }
<a name="L784" href="source/net/ipv4/ip_output.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/ip_output.c#L785">785</a> static inline int <a href="ident?i=ip_ufo_append_data">ip_ufo_append_data</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L786" href="source/net/ipv4/ip_output.c#L786">786</a>                         struct <a href="ident?i=sk_buff_head">sk_buff_head</a> *<a href="ident?i=queue">queue</a>,
<a name="L787" href="source/net/ipv4/ip_output.c#L787">787</a>                         int getfrag(void *from, char *to, int <a href="ident?i=offset">offset</a>, int <a href="ident?i=len">len</a>,
<a name="L788" href="source/net/ipv4/ip_output.c#L788">788</a>                                int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>),
<a name="L789" href="source/net/ipv4/ip_output.c#L789">789</a>                         void *from, int <a href="ident?i=length">length</a>, int hh_len, int fragheaderlen,
<a name="L790" href="source/net/ipv4/ip_output.c#L790">790</a>                         int transhdrlen, int maxfraglen, unsigned int <a href="ident?i=flags">flags</a>)
<a name="L791" href="source/net/ipv4/ip_output.c#L791">791</a> {
<a name="L792" href="source/net/ipv4/ip_output.c#L792">792</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L793" href="source/net/ipv4/ip_output.c#L793">793</a>         int <a href="ident?i=err">err</a>;
<a name="L794" href="source/net/ipv4/ip_output.c#L794">794</a> 
<a name="L795" href="source/net/ipv4/ip_output.c#L795">795</a>         <b><i>/* There is support for UDP fragmentation offload by network</i></b>
<a name="L796" href="source/net/ipv4/ip_output.c#L796">796</a> <b><i>         * device, so create one single skb packet containing complete</i></b>
<a name="L797" href="source/net/ipv4/ip_output.c#L797">797</a> <b><i>         * udp datagram</i></b>
<a name="L798" href="source/net/ipv4/ip_output.c#L798">798</a> <b><i>         */</i></b>
<a name="L799" href="source/net/ipv4/ip_output.c#L799">799</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek_tail">skb_peek_tail</a>(<a href="ident?i=queue">queue</a>);
<a name="L800" href="source/net/ipv4/ip_output.c#L800">800</a>         if (!<a href="ident?i=skb">skb</a>) {
<a name="L801" href="source/net/ipv4/ip_output.c#L801">801</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_alloc_send_skb">sock_alloc_send_skb</a>(sk,
<a name="L802" href="source/net/ipv4/ip_output.c#L802">802</a>                         hh_len + fragheaderlen + transhdrlen + 20,
<a name="L803" href="source/net/ipv4/ip_output.c#L803">803</a>                         (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>), &amp;<a href="ident?i=err">err</a>);
<a name="L804" href="source/net/ipv4/ip_output.c#L804">804</a> 
<a name="L805" href="source/net/ipv4/ip_output.c#L805">805</a>                 if (!<a href="ident?i=skb">skb</a>)
<a name="L806" href="source/net/ipv4/ip_output.c#L806">806</a>                         return <a href="ident?i=err">err</a>;
<a name="L807" href="source/net/ipv4/ip_output.c#L807">807</a> 
<a name="L808" href="source/net/ipv4/ip_output.c#L808">808</a>                 <b><i>/* reserve space for Hardware header */</i></b>
<a name="L809" href="source/net/ipv4/ip_output.c#L809">809</a>                 <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hh_len);
<a name="L810" href="source/net/ipv4/ip_output.c#L810">810</a> 
<a name="L811" href="source/net/ipv4/ip_output.c#L811">811</a>                 <b><i>/* create space for UDP/IP header */</i></b>
<a name="L812" href="source/net/ipv4/ip_output.c#L812">812</a>                 <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, fragheaderlen + transhdrlen);
<a name="L813" href="source/net/ipv4/ip_output.c#L813">813</a> 
<a name="L814" href="source/net/ipv4/ip_output.c#L814">814</a>                 <b><i>/* initialize network header pointer */</i></b>
<a name="L815" href="source/net/ipv4/ip_output.c#L815">815</a>                 <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L816" href="source/net/ipv4/ip_output.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/ip_output.c#L817">817</a>                 <b><i>/* initialize protocol header pointer */</i></b>
<a name="L818" href="source/net/ipv4/ip_output.c#L818">818</a>                 <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header + fragheaderlen;
<a name="L819" href="source/net/ipv4/ip_output.c#L819">819</a> 
<a name="L820" href="source/net/ipv4/ip_output.c#L820">820</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L821" href="source/net/ipv4/ip_output.c#L821">821</a> 
<a name="L822" href="source/net/ipv4/ip_output.c#L822">822</a>                 <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(<a href="ident?i=queue">queue</a>, <a href="ident?i=skb">skb</a>);
<a name="L823" href="source/net/ipv4/ip_output.c#L823">823</a>         } else if (<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L824" href="source/net/ipv4/ip_output.c#L824">824</a>                 goto <a href="ident?i=append">append</a>;
<a name="L825" href="source/net/ipv4/ip_output.c#L825">825</a>         }
<a name="L826" href="source/net/ipv4/ip_output.c#L826">826</a> 
<a name="L827" href="source/net/ipv4/ip_output.c#L827">827</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L828" href="source/net/ipv4/ip_output.c#L828">828</a>         <b><i>/* specify the length of each IP datagram fragment */</i></b>
<a name="L829" href="source/net/ipv4/ip_output.c#L829">829</a>         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_size = maxfraglen - fragheaderlen;
<a name="L830" href="source/net/ipv4/ip_output.c#L830">830</a>         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type = SKB_GSO_UDP;
<a name="L831" href="source/net/ipv4/ip_output.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/ip_output.c#L832">832</a> <a href="ident?i=append">append</a>:
<a name="L833" href="source/net/ipv4/ip_output.c#L833">833</a>         return <a href="ident?i=skb_append_datato_frags">skb_append_datato_frags</a>(sk, <a href="ident?i=skb">skb</a>, getfrag, from,
<a name="L834" href="source/net/ipv4/ip_output.c#L834">834</a>                                        (<a href="ident?i=length">length</a> - transhdrlen));
<a name="L835" href="source/net/ipv4/ip_output.c#L835">835</a> }
<a name="L836" href="source/net/ipv4/ip_output.c#L836">836</a> 
<a name="L837" href="source/net/ipv4/ip_output.c#L837">837</a> static int <a href="ident?i=__ip_append_data">__ip_append_data</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L838" href="source/net/ipv4/ip_output.c#L838">838</a>                             struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L839" href="source/net/ipv4/ip_output.c#L839">839</a>                             struct <a href="ident?i=sk_buff_head">sk_buff_head</a> *<a href="ident?i=queue">queue</a>,
<a name="L840" href="source/net/ipv4/ip_output.c#L840">840</a>                             struct <a href="ident?i=inet_cork">inet_cork</a> *cork,
<a name="L841" href="source/net/ipv4/ip_output.c#L841">841</a>                             struct <a href="ident?i=page_frag">page_frag</a> *pfrag,
<a name="L842" href="source/net/ipv4/ip_output.c#L842">842</a>                             int getfrag(void *from, char *to, int <a href="ident?i=offset">offset</a>,
<a name="L843" href="source/net/ipv4/ip_output.c#L843">843</a>                                         int <a href="ident?i=len">len</a>, int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>),
<a name="L844" href="source/net/ipv4/ip_output.c#L844">844</a>                             void *from, int <a href="ident?i=length">length</a>, int transhdrlen,
<a name="L845" href="source/net/ipv4/ip_output.c#L845">845</a>                             unsigned int <a href="ident?i=flags">flags</a>)
<a name="L846" href="source/net/ipv4/ip_output.c#L846">846</a> {
<a name="L847" href="source/net/ipv4/ip_output.c#L847">847</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L848" href="source/net/ipv4/ip_output.c#L848">848</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L849" href="source/net/ipv4/ip_output.c#L849">849</a> 
<a name="L850" href="source/net/ipv4/ip_output.c#L850">850</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = cork-&gt;opt;
<a name="L851" href="source/net/ipv4/ip_output.c#L851">851</a>         int hh_len;
<a name="L852" href="source/net/ipv4/ip_output.c#L852">852</a>         int exthdrlen;
<a name="L853" href="source/net/ipv4/ip_output.c#L853">853</a>         int <a href="ident?i=mtu">mtu</a>;
<a name="L854" href="source/net/ipv4/ip_output.c#L854">854</a>         int <a href="ident?i=copy">copy</a>;
<a name="L855" href="source/net/ipv4/ip_output.c#L855">855</a>         int <a href="ident?i=err">err</a>;
<a name="L856" href="source/net/ipv4/ip_output.c#L856">856</a>         int <a href="ident?i=offset">offset</a> = 0;
<a name="L857" href="source/net/ipv4/ip_output.c#L857">857</a>         unsigned int maxfraglen, fragheaderlen, maxnonfragsize;
<a name="L858" href="source/net/ipv4/ip_output.c#L858">858</a>         int csummode = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L859" href="source/net/ipv4/ip_output.c#L859">859</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)cork-&gt;<a href="ident?i=dst">dst</a>;
<a name="L860" href="source/net/ipv4/ip_output.c#L860">860</a>         <a href="ident?i=u32">u32</a> tskey = 0;
<a name="L861" href="source/net/ipv4/ip_output.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/ip_output.c#L862">862</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek_tail">skb_peek_tail</a>(<a href="ident?i=queue">queue</a>);
<a name="L863" href="source/net/ipv4/ip_output.c#L863">863</a> 
<a name="L864" href="source/net/ipv4/ip_output.c#L864">864</a>         exthdrlen = !<a href="ident?i=skb">skb</a> ? <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=header_len">header_len</a> : 0;
<a name="L865" href="source/net/ipv4/ip_output.c#L865">865</a>         <a href="ident?i=mtu">mtu</a> = cork-&gt;fragsize;
<a name="L866" href="source/net/ipv4/ip_output.c#L866">866</a>         if (cork-&gt;tx_flags &amp; <a href="ident?i=SKBTX_ANY_SW_TSTAMP">SKBTX_ANY_SW_TSTAMP</a> &amp;&amp;
<a name="L867" href="source/net/ipv4/ip_output.c#L867">867</a>             sk-&gt;sk_tsflags &amp; SOF_TIMESTAMPING_OPT_ID)
<a name="L868" href="source/net/ipv4/ip_output.c#L868">868</a>                 tskey = sk-&gt;sk_tskey++;
<a name="L869" href="source/net/ipv4/ip_output.c#L869">869</a> 
<a name="L870" href="source/net/ipv4/ip_output.c#L870">870</a>         hh_len = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L871" href="source/net/ipv4/ip_output.c#L871">871</a> 
<a name="L872" href="source/net/ipv4/ip_output.c#L872">872</a>         fragheaderlen = sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + (opt ? opt-&gt;<a href="ident?i=optlen">optlen</a> : 0);
<a name="L873" href="source/net/ipv4/ip_output.c#L873">873</a>         maxfraglen = ((<a href="ident?i=mtu">mtu</a> - fragheaderlen) &amp; ~7) + fragheaderlen;
<a name="L874" href="source/net/ipv4/ip_output.c#L874">874</a>         maxnonfragsize = <a href="ident?i=ip_sk_ignore_df">ip_sk_ignore_df</a>(sk) ? 0xFFFF : <a href="ident?i=mtu">mtu</a>;
<a name="L875" href="source/net/ipv4/ip_output.c#L875">875</a> 
<a name="L876" href="source/net/ipv4/ip_output.c#L876">876</a>         if (cork-&gt;<a href="ident?i=length">length</a> + <a href="ident?i=length">length</a> &gt; maxnonfragsize - fragheaderlen) {
<a name="L877" href="source/net/ipv4/ip_output.c#L877">877</a>                 <a href="ident?i=ip_local_error">ip_local_error</a>(sk, <a href="ident?i=EMSGSIZE">EMSGSIZE</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>,
<a name="L878" href="source/net/ipv4/ip_output.c#L878">878</a>                                <a href="ident?i=mtu">mtu</a> - (opt ? opt-&gt;<a href="ident?i=optlen">optlen</a> : 0));
<a name="L879" href="source/net/ipv4/ip_output.c#L879">879</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L880" href="source/net/ipv4/ip_output.c#L880">880</a>         }
<a name="L881" href="source/net/ipv4/ip_output.c#L881">881</a> 
<a name="L882" href="source/net/ipv4/ip_output.c#L882">882</a>         <b><i>/*</i></b>
<a name="L883" href="source/net/ipv4/ip_output.c#L883">883</a> <b><i>         * transhdrlen &gt; 0 means that this is the first fragment and we wish</i></b>
<a name="L884" href="source/net/ipv4/ip_output.c#L884">884</a> <b><i>         * it won't be fragmented in the future.</i></b>
<a name="L885" href="source/net/ipv4/ip_output.c#L885">885</a> <b><i>         */</i></b>
<a name="L886" href="source/net/ipv4/ip_output.c#L886">886</a>         if (transhdrlen &amp;&amp;
<a name="L887" href="source/net/ipv4/ip_output.c#L887">887</a>             <a href="ident?i=length">length</a> + fragheaderlen &lt;= <a href="ident?i=mtu">mtu</a> &amp;&amp;
<a name="L888" href="source/net/ipv4/ip_output.c#L888">888</a>             <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=NETIF_F_V4_CSUM">NETIF_F_V4_CSUM</a> &amp;&amp;
<a name="L889" href="source/net/ipv4/ip_output.c#L889">889</a>             !exthdrlen)
<a name="L890" href="source/net/ipv4/ip_output.c#L890">890</a>                 csummode = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L891" href="source/net/ipv4/ip_output.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/ip_output.c#L892">892</a>         cork-&gt;<a href="ident?i=length">length</a> += <a href="ident?i=length">length</a>;
<a name="L893" href="source/net/ipv4/ip_output.c#L893">893</a>         if (((<a href="ident?i=length">length</a> &gt; <a href="ident?i=mtu">mtu</a>) || (<a href="ident?i=skb">skb</a> &amp;&amp; <a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>))) &amp;&amp;
<a name="L894" href="source/net/ipv4/ip_output.c#L894">894</a>             (sk-&gt;sk_protocol == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>) &amp;&amp;
<a name="L895" href="source/net/ipv4/ip_output.c#L895">895</a>             (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=NETIF_F_UFO">NETIF_F_UFO</a>) &amp;&amp; !<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=header_len">header_len</a> &amp;&amp;
<a name="L896" href="source/net/ipv4/ip_output.c#L896">896</a>             (sk-&gt;sk_type == SOCK_DGRAM)) {
<a name="L897" href="source/net/ipv4/ip_output.c#L897">897</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_ufo_append_data">ip_ufo_append_data</a>(sk, <a href="ident?i=queue">queue</a>, getfrag, from, <a href="ident?i=length">length</a>,
<a name="L898" href="source/net/ipv4/ip_output.c#L898">898</a>                                          hh_len, fragheaderlen, transhdrlen,
<a name="L899" href="source/net/ipv4/ip_output.c#L899">899</a>                                          maxfraglen, <a href="ident?i=flags">flags</a>);
<a name="L900" href="source/net/ipv4/ip_output.c#L900">900</a>                 if (<a href="ident?i=err">err</a>)
<a name="L901" href="source/net/ipv4/ip_output.c#L901">901</a>                         goto <a href="ident?i=error">error</a>;
<a name="L902" href="source/net/ipv4/ip_output.c#L902">902</a>                 return 0;
<a name="L903" href="source/net/ipv4/ip_output.c#L903">903</a>         }
<a name="L904" href="source/net/ipv4/ip_output.c#L904">904</a> 
<a name="L905" href="source/net/ipv4/ip_output.c#L905">905</a>         <b><i>/* So, what's going on in the loop below?</i></b>
<a name="L906" href="source/net/ipv4/ip_output.c#L906">906</a> <b><i>         *</i></b>
<a name="L907" href="source/net/ipv4/ip_output.c#L907">907</a> <b><i>         * We use calculated fragment length to generate chained skb,</i></b>
<a name="L908" href="source/net/ipv4/ip_output.c#L908">908</a> <b><i>         * each of segments is IP fragment ready for sending to network after</i></b>
<a name="L909" href="source/net/ipv4/ip_output.c#L909">909</a> <b><i>         * adding appropriate IP header.</i></b>
<a name="L910" href="source/net/ipv4/ip_output.c#L910">910</a> <b><i>         */</i></b>
<a name="L911" href="source/net/ipv4/ip_output.c#L911">911</a> 
<a name="L912" href="source/net/ipv4/ip_output.c#L912">912</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L913" href="source/net/ipv4/ip_output.c#L913">913</a>                 goto alloc_new_skb;
<a name="L914" href="source/net/ipv4/ip_output.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/ip_output.c#L915">915</a>         while (<a href="ident?i=length">length</a> &gt; 0) {
<a name="L916" href="source/net/ipv4/ip_output.c#L916">916</a>                 <b><i>/* Check if the remaining data fits into current packet. */</i></b>
<a name="L917" href="source/net/ipv4/ip_output.c#L917">917</a>                 <a href="ident?i=copy">copy</a> = <a href="ident?i=mtu">mtu</a> - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L918" href="source/net/ipv4/ip_output.c#L918">918</a>                 if (<a href="ident?i=copy">copy</a> &lt; <a href="ident?i=length">length</a>)
<a name="L919" href="source/net/ipv4/ip_output.c#L919">919</a>                         <a href="ident?i=copy">copy</a> = maxfraglen - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L920" href="source/net/ipv4/ip_output.c#L920">920</a>                 if (<a href="ident?i=copy">copy</a> &lt;= 0) {
<a name="L921" href="source/net/ipv4/ip_output.c#L921">921</a>                         char *<a href="ident?i=data">data</a>;
<a name="L922" href="source/net/ipv4/ip_output.c#L922">922</a>                         unsigned int datalen;
<a name="L923" href="source/net/ipv4/ip_output.c#L923">923</a>                         unsigned int fraglen;
<a name="L924" href="source/net/ipv4/ip_output.c#L924">924</a>                         unsigned int fraggap;
<a name="L925" href="source/net/ipv4/ip_output.c#L925">925</a>                         unsigned int alloclen;
<a name="L926" href="source/net/ipv4/ip_output.c#L926">926</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *skb_prev;
<a name="L927" href="source/net/ipv4/ip_output.c#L927">927</a> alloc_new_skb:
<a name="L928" href="source/net/ipv4/ip_output.c#L928">928</a>                         skb_prev = <a href="ident?i=skb">skb</a>;
<a name="L929" href="source/net/ipv4/ip_output.c#L929">929</a>                         if (skb_prev)
<a name="L930" href="source/net/ipv4/ip_output.c#L930">930</a>                                 fraggap = skb_prev-&gt;<a href="ident?i=len">len</a> - maxfraglen;
<a name="L931" href="source/net/ipv4/ip_output.c#L931">931</a>                         else
<a name="L932" href="source/net/ipv4/ip_output.c#L932">932</a>                                 fraggap = 0;
<a name="L933" href="source/net/ipv4/ip_output.c#L933">933</a> 
<a name="L934" href="source/net/ipv4/ip_output.c#L934">934</a>                         <b><i>/*</i></b>
<a name="L935" href="source/net/ipv4/ip_output.c#L935">935</a> <b><i>                         * If remaining data exceeds the mtu,</i></b>
<a name="L936" href="source/net/ipv4/ip_output.c#L936">936</a> <b><i>                         * we know we need more fragment(s).</i></b>
<a name="L937" href="source/net/ipv4/ip_output.c#L937">937</a> <b><i>                         */</i></b>
<a name="L938" href="source/net/ipv4/ip_output.c#L938">938</a>                         datalen = <a href="ident?i=length">length</a> + fraggap;
<a name="L939" href="source/net/ipv4/ip_output.c#L939">939</a>                         if (datalen &gt; <a href="ident?i=mtu">mtu</a> - fragheaderlen)
<a name="L940" href="source/net/ipv4/ip_output.c#L940">940</a>                                 datalen = maxfraglen - fragheaderlen;
<a name="L941" href="source/net/ipv4/ip_output.c#L941">941</a>                         fraglen = datalen + fragheaderlen;
<a name="L942" href="source/net/ipv4/ip_output.c#L942">942</a> 
<a name="L943" href="source/net/ipv4/ip_output.c#L943">943</a>                         if ((<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_MORE">MSG_MORE</a>) &amp;&amp;
<a name="L944" href="source/net/ipv4/ip_output.c#L944">944</a>                             !(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>&amp;<a href="ident?i=NETIF_F_SG">NETIF_F_SG</a>))
<a name="L945" href="source/net/ipv4/ip_output.c#L945">945</a>                                 alloclen = <a href="ident?i=mtu">mtu</a>;
<a name="L946" href="source/net/ipv4/ip_output.c#L946">946</a>                         else
<a name="L947" href="source/net/ipv4/ip_output.c#L947">947</a>                                 alloclen = fraglen;
<a name="L948" href="source/net/ipv4/ip_output.c#L948">948</a> 
<a name="L949" href="source/net/ipv4/ip_output.c#L949">949</a>                         alloclen += exthdrlen;
<a name="L950" href="source/net/ipv4/ip_output.c#L950">950</a> 
<a name="L951" href="source/net/ipv4/ip_output.c#L951">951</a>                         <b><i>/* The last fragment gets additional space at tail.</i></b>
<a name="L952" href="source/net/ipv4/ip_output.c#L952">952</a> <b><i>                         * Note, with MSG_MORE we overallocate on fragments,</i></b>
<a name="L953" href="source/net/ipv4/ip_output.c#L953">953</a> <b><i>                         * because we have no idea what fragment will be</i></b>
<a name="L954" href="source/net/ipv4/ip_output.c#L954">954</a> <b><i>                         * the last.</i></b>
<a name="L955" href="source/net/ipv4/ip_output.c#L955">955</a> <b><i>                         */</i></b>
<a name="L956" href="source/net/ipv4/ip_output.c#L956">956</a>                         if (datalen == <a href="ident?i=length">length</a> + fraggap)
<a name="L957" href="source/net/ipv4/ip_output.c#L957">957</a>                                 alloclen += <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.trailer_len;
<a name="L958" href="source/net/ipv4/ip_output.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/ip_output.c#L959">959</a>                         if (transhdrlen) {
<a name="L960" href="source/net/ipv4/ip_output.c#L960">960</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_alloc_send_skb">sock_alloc_send_skb</a>(sk,
<a name="L961" href="source/net/ipv4/ip_output.c#L961">961</a>                                                 alloclen + hh_len + 15,
<a name="L962" href="source/net/ipv4/ip_output.c#L962">962</a>                                                 (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>), &amp;<a href="ident?i=err">err</a>);
<a name="L963" href="source/net/ipv4/ip_output.c#L963">963</a>                         } else {
<a name="L964" href="source/net/ipv4/ip_output.c#L964">964</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L965" href="source/net/ipv4/ip_output.c#L965">965</a>                                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc) &lt;=
<a name="L966" href="source/net/ipv4/ip_output.c#L966">966</a>                                     2 * sk-&gt;sk_sndbuf)
<a name="L967" href="source/net/ipv4/ip_output.c#L967">967</a>                                         <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_wmalloc">sock_wmalloc</a>(sk,
<a name="L968" href="source/net/ipv4/ip_output.c#L968">968</a>                                                            alloclen + hh_len + 15, 1,
<a name="L969" href="source/net/ipv4/ip_output.c#L969">969</a>                                                            sk-&gt;sk_allocation);
<a name="L970" href="source/net/ipv4/ip_output.c#L970">970</a>                                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=skb">skb</a>))
<a name="L971" href="source/net/ipv4/ip_output.c#L971">971</a>                                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L972" href="source/net/ipv4/ip_output.c#L972">972</a>                         }
<a name="L973" href="source/net/ipv4/ip_output.c#L973">973</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L974" href="source/net/ipv4/ip_output.c#L974">974</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L975" href="source/net/ipv4/ip_output.c#L975">975</a> 
<a name="L976" href="source/net/ipv4/ip_output.c#L976">976</a>                         <b><i>/*</i></b>
<a name="L977" href="source/net/ipv4/ip_output.c#L977">977</a> <b><i>                         *      Fill in the control structures</i></b>
<a name="L978" href="source/net/ipv4/ip_output.c#L978">978</a> <b><i>                         */</i></b>
<a name="L979" href="source/net/ipv4/ip_output.c#L979">979</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = csummode;
<a name="L980" href="source/net/ipv4/ip_output.c#L980">980</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L981" href="source/net/ipv4/ip_output.c#L981">981</a>                         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hh_len);
<a name="L982" href="source/net/ipv4/ip_output.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/ip_output.c#L983">983</a>                         <b><i>/* only the initial fragment is time stamped */</i></b>
<a name="L984" href="source/net/ipv4/ip_output.c#L984">984</a>                         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;tx_flags = cork-&gt;tx_flags;
<a name="L985" href="source/net/ipv4/ip_output.c#L985">985</a>                         cork-&gt;tx_flags = 0;
<a name="L986" href="source/net/ipv4/ip_output.c#L986">986</a>                         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;tskey = tskey;
<a name="L987" href="source/net/ipv4/ip_output.c#L987">987</a>                         tskey = 0;
<a name="L988" href="source/net/ipv4/ip_output.c#L988">988</a> 
<a name="L989" href="source/net/ipv4/ip_output.c#L989">989</a>                         <b><i>/*</i></b>
<a name="L990" href="source/net/ipv4/ip_output.c#L990">990</a> <b><i>                         *      Find where to start putting bytes.</i></b>
<a name="L991" href="source/net/ipv4/ip_output.c#L991">991</a> <b><i>                         */</i></b>
<a name="L992" href="source/net/ipv4/ip_output.c#L992">992</a>                         <a href="ident?i=data">data</a> = <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, fraglen + exthdrlen);
<a name="L993" href="source/net/ipv4/ip_output.c#L993">993</a>                         <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, exthdrlen);
<a name="L994" href="source/net/ipv4/ip_output.c#L994">994</a>                         <a href="ident?i=skb">skb</a>-&gt;transport_header = (<a href="ident?i=skb">skb</a>-&gt;network_header +
<a name="L995" href="source/net/ipv4/ip_output.c#L995">995</a>                                                  fragheaderlen);
<a name="L996" href="source/net/ipv4/ip_output.c#L996">996</a>                         <a href="ident?i=data">data</a> += fragheaderlen + exthdrlen;
<a name="L997" href="source/net/ipv4/ip_output.c#L997">997</a> 
<a name="L998" href="source/net/ipv4/ip_output.c#L998">998</a>                         if (fraggap) {
<a name="L999" href="source/net/ipv4/ip_output.c#L999">999</a>                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=skb_copy_and_csum_bits">skb_copy_and_csum_bits</a>(
<a name="L1000" href="source/net/ipv4/ip_output.c#L1000">1000</a>                                         skb_prev, maxfraglen,
<a name="L1001" href="source/net/ipv4/ip_output.c#L1001">1001</a>                                         <a href="ident?i=data">data</a> + transhdrlen, fraggap, 0);
<a name="L1002" href="source/net/ipv4/ip_output.c#L1002">1002</a>                                 skb_prev-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_sub">csum_sub</a>(skb_prev-&gt;<a href="ident?i=csum">csum</a>,
<a name="L1003" href="source/net/ipv4/ip_output.c#L1003">1003</a>                                                           <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>);
<a name="L1004" href="source/net/ipv4/ip_output.c#L1004">1004</a>                                 <a href="ident?i=data">data</a> += fraggap;
<a name="L1005" href="source/net/ipv4/ip_output.c#L1005">1005</a>                                 <a href="ident?i=pskb_trim_unique">pskb_trim_unique</a>(skb_prev, maxfraglen);
<a name="L1006" href="source/net/ipv4/ip_output.c#L1006">1006</a>                         }
<a name="L1007" href="source/net/ipv4/ip_output.c#L1007">1007</a> 
<a name="L1008" href="source/net/ipv4/ip_output.c#L1008">1008</a>                         <a href="ident?i=copy">copy</a> = datalen - transhdrlen - fraggap;
<a name="L1009" href="source/net/ipv4/ip_output.c#L1009">1009</a>                         if (<a href="ident?i=copy">copy</a> &gt; 0 &amp;&amp; getfrag(from, <a href="ident?i=data">data</a> + transhdrlen, <a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>, fraggap, <a href="ident?i=skb">skb</a>) &lt; 0) {
<a name="L1010" href="source/net/ipv4/ip_output.c#L1010">1010</a>                                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1011" href="source/net/ipv4/ip_output.c#L1011">1011</a>                                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1012" href="source/net/ipv4/ip_output.c#L1012">1012</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L1013" href="source/net/ipv4/ip_output.c#L1013">1013</a>                         }
<a name="L1014" href="source/net/ipv4/ip_output.c#L1014">1014</a> 
<a name="L1015" href="source/net/ipv4/ip_output.c#L1015">1015</a>                         <a href="ident?i=offset">offset</a> += <a href="ident?i=copy">copy</a>;
<a name="L1016" href="source/net/ipv4/ip_output.c#L1016">1016</a>                         <a href="ident?i=length">length</a> -= datalen - fraggap;
<a name="L1017" href="source/net/ipv4/ip_output.c#L1017">1017</a>                         transhdrlen = 0;
<a name="L1018" href="source/net/ipv4/ip_output.c#L1018">1018</a>                         exthdrlen = 0;
<a name="L1019" href="source/net/ipv4/ip_output.c#L1019">1019</a>                         csummode = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L1020" href="source/net/ipv4/ip_output.c#L1020">1020</a> 
<a name="L1021" href="source/net/ipv4/ip_output.c#L1021">1021</a>                         <b><i>/*</i></b>
<a name="L1022" href="source/net/ipv4/ip_output.c#L1022">1022</a> <b><i>                         * Put the packet on the pending queue.</i></b>
<a name="L1023" href="source/net/ipv4/ip_output.c#L1023">1023</a> <b><i>                         */</i></b>
<a name="L1024" href="source/net/ipv4/ip_output.c#L1024">1024</a>                         <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(<a href="ident?i=queue">queue</a>, <a href="ident?i=skb">skb</a>);
<a name="L1025" href="source/net/ipv4/ip_output.c#L1025">1025</a>                         continue;
<a name="L1026" href="source/net/ipv4/ip_output.c#L1026">1026</a>                 }
<a name="L1027" href="source/net/ipv4/ip_output.c#L1027">1027</a> 
<a name="L1028" href="source/net/ipv4/ip_output.c#L1028">1028</a>                 if (<a href="ident?i=copy">copy</a> &gt; <a href="ident?i=length">length</a>)
<a name="L1029" href="source/net/ipv4/ip_output.c#L1029">1029</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=length">length</a>;
<a name="L1030" href="source/net/ipv4/ip_output.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/ip_output.c#L1031">1031</a>                 if (!(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>&amp;<a href="ident?i=NETIF_F_SG">NETIF_F_SG</a>)) {
<a name="L1032" href="source/net/ipv4/ip_output.c#L1032">1032</a>                         unsigned int <a href="ident?i=off">off</a>;
<a name="L1033" href="source/net/ipv4/ip_output.c#L1033">1033</a> 
<a name="L1034" href="source/net/ipv4/ip_output.c#L1034">1034</a>                         <a href="ident?i=off">off</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1035" href="source/net/ipv4/ip_output.c#L1035">1035</a>                         if (getfrag(from, <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=copy">copy</a>),
<a name="L1036" href="source/net/ipv4/ip_output.c#L1036">1036</a>                                         <a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>, <a href="ident?i=off">off</a>, <a href="ident?i=skb">skb</a>) &lt; 0) {
<a name="L1037" href="source/net/ipv4/ip_output.c#L1037">1037</a>                                 <a href="ident?i=__skb_trim">__skb_trim</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a>);
<a name="L1038" href="source/net/ipv4/ip_output.c#L1038">1038</a>                                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1039" href="source/net/ipv4/ip_output.c#L1039">1039</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L1040" href="source/net/ipv4/ip_output.c#L1040">1040</a>                         }
<a name="L1041" href="source/net/ipv4/ip_output.c#L1041">1041</a>                 } else {
<a name="L1042" href="source/net/ipv4/ip_output.c#L1042">1042</a>                         int <a href="ident?i=i">i</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags;
<a name="L1043" href="source/net/ipv4/ip_output.c#L1043">1043</a> 
<a name="L1044" href="source/net/ipv4/ip_output.c#L1044">1044</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1045" href="source/net/ipv4/ip_output.c#L1045">1045</a>                         if (!<a href="ident?i=sk_page_frag_refill">sk_page_frag_refill</a>(sk, pfrag))
<a name="L1046" href="source/net/ipv4/ip_output.c#L1046">1046</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L1047" href="source/net/ipv4/ip_output.c#L1047">1047</a> 
<a name="L1048" href="source/net/ipv4/ip_output.c#L1048">1048</a>                         if (!<a href="ident?i=skb_can_coalesce">skb_can_coalesce</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, pfrag-&gt;<a href="ident?i=page">page</a>,
<a name="L1049" href="source/net/ipv4/ip_output.c#L1049">1049</a>                                               pfrag-&gt;<a href="ident?i=offset">offset</a>)) {
<a name="L1050" href="source/net/ipv4/ip_output.c#L1050">1050</a>                                 <a href="ident?i=err">err</a> = -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1051" href="source/net/ipv4/ip_output.c#L1051">1051</a>                                 if (<a href="ident?i=i">i</a> == <a href="ident?i=MAX_SKB_FRAGS">MAX_SKB_FRAGS</a>)
<a name="L1052" href="source/net/ipv4/ip_output.c#L1052">1052</a>                                         goto <a href="ident?i=error">error</a>;
<a name="L1053" href="source/net/ipv4/ip_output.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/ip_output.c#L1054">1054</a>                                 <a href="ident?i=__skb_fill_page_desc">__skb_fill_page_desc</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, pfrag-&gt;<a href="ident?i=page">page</a>,
<a name="L1055" href="source/net/ipv4/ip_output.c#L1055">1055</a>                                                      pfrag-&gt;<a href="ident?i=offset">offset</a>, 0);
<a name="L1056" href="source/net/ipv4/ip_output.c#L1056">1056</a>                                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags = ++<a href="ident?i=i">i</a>;
<a name="L1057" href="source/net/ipv4/ip_output.c#L1057">1057</a>                                 <a href="ident?i=get_page">get_page</a>(pfrag-&gt;<a href="ident?i=page">page</a>);
<a name="L1058" href="source/net/ipv4/ip_output.c#L1058">1058</a>                         }
<a name="L1059" href="source/net/ipv4/ip_output.c#L1059">1059</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=copy">copy</a>, pfrag-&gt;<a href="ident?i=size">size</a> - pfrag-&gt;<a href="ident?i=offset">offset</a>);
<a name="L1060" href="source/net/ipv4/ip_output.c#L1060">1060</a>                         if (getfrag(from,
<a name="L1061" href="source/net/ipv4/ip_output.c#L1061">1061</a>                                     <a href="ident?i=page_address">page_address</a>(pfrag-&gt;<a href="ident?i=page">page</a>) + pfrag-&gt;<a href="ident?i=offset">offset</a>,
<a name="L1062" href="source/net/ipv4/ip_output.c#L1062">1062</a>                                     <a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, <a href="ident?i=skb">skb</a>) &lt; 0)
<a name="L1063" href="source/net/ipv4/ip_output.c#L1063">1063</a>                                 goto error_efault;
<a name="L1064" href="source/net/ipv4/ip_output.c#L1064">1064</a> 
<a name="L1065" href="source/net/ipv4/ip_output.c#L1065">1065</a>                         pfrag-&gt;<a href="ident?i=offset">offset</a> += <a href="ident?i=copy">copy</a>;
<a name="L1066" href="source/net/ipv4/ip_output.c#L1066">1066</a>                         <a href="ident?i=skb_frag_size_add">skb_frag_size_add</a>(&amp;<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frags[<a href="ident?i=i">i</a> - 1], <a href="ident?i=copy">copy</a>);
<a name="L1067" href="source/net/ipv4/ip_output.c#L1067">1067</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> += <a href="ident?i=copy">copy</a>;
<a name="L1068" href="source/net/ipv4/ip_output.c#L1068">1068</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a> += <a href="ident?i=copy">copy</a>;
<a name="L1069" href="source/net/ipv4/ip_output.c#L1069">1069</a>                         <a href="ident?i=skb">skb</a>-&gt;truesize += <a href="ident?i=copy">copy</a>;
<a name="L1070" href="source/net/ipv4/ip_output.c#L1070">1070</a>                         <a href="ident?i=atomic_add">atomic_add</a>(<a href="ident?i=copy">copy</a>, &amp;sk-&gt;sk_wmem_alloc);
<a name="L1071" href="source/net/ipv4/ip_output.c#L1071">1071</a>                 }
<a name="L1072" href="source/net/ipv4/ip_output.c#L1072">1072</a>                 <a href="ident?i=offset">offset</a> += <a href="ident?i=copy">copy</a>;
<a name="L1073" href="source/net/ipv4/ip_output.c#L1073">1073</a>                 <a href="ident?i=length">length</a> -= <a href="ident?i=copy">copy</a>;
<a name="L1074" href="source/net/ipv4/ip_output.c#L1074">1074</a>         }
<a name="L1075" href="source/net/ipv4/ip_output.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/ip_output.c#L1076">1076</a>         return 0;
<a name="L1077" href="source/net/ipv4/ip_output.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/ip_output.c#L1078">1078</a> error_efault:
<a name="L1079" href="source/net/ipv4/ip_output.c#L1079">1079</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1080" href="source/net/ipv4/ip_output.c#L1080">1080</a> <a href="ident?i=error">error</a>:
<a name="L1081" href="source/net/ipv4/ip_output.c#L1081">1081</a>         cork-&gt;<a href="ident?i=length">length</a> -= <a href="ident?i=length">length</a>;
<a name="L1082" href="source/net/ipv4/ip_output.c#L1082">1082</a>         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), IPSTATS_MIB_OUTDISCARDS);
<a name="L1083" href="source/net/ipv4/ip_output.c#L1083">1083</a>         return <a href="ident?i=err">err</a>;
<a name="L1084" href="source/net/ipv4/ip_output.c#L1084">1084</a> }
<a name="L1085" href="source/net/ipv4/ip_output.c#L1085">1085</a> 
<a name="L1086" href="source/net/ipv4/ip_output.c#L1086">1086</a> static int <a href="ident?i=ip_setup_cork">ip_setup_cork</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_cork">inet_cork</a> *cork,
<a name="L1087" href="source/net/ipv4/ip_output.c#L1087">1087</a>                          struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> *ipc, struct <a href="ident?i=rtable">rtable</a> **rtp)
<a name="L1088" href="source/net/ipv4/ip_output.c#L1088">1088</a> {
<a name="L1089" href="source/net/ipv4/ip_output.c#L1089">1089</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt;
<a name="L1090" href="source/net/ipv4/ip_output.c#L1090">1090</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1091" href="source/net/ipv4/ip_output.c#L1091">1091</a> 
<a name="L1092" href="source/net/ipv4/ip_output.c#L1092">1092</a>         <b><i>/*</i></b>
<a name="L1093" href="source/net/ipv4/ip_output.c#L1093">1093</a> <b><i>         * setup for corking.</i></b>
<a name="L1094" href="source/net/ipv4/ip_output.c#L1094">1094</a> <b><i>         */</i></b>
<a name="L1095" href="source/net/ipv4/ip_output.c#L1095">1095</a>         opt = ipc-&gt;opt;
<a name="L1096" href="source/net/ipv4/ip_output.c#L1096">1096</a>         if (opt) {
<a name="L1097" href="source/net/ipv4/ip_output.c#L1097">1097</a>                 if (!cork-&gt;opt) {
<a name="L1098" href="source/net/ipv4/ip_output.c#L1098">1098</a>                         cork-&gt;opt = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(struct <a href="ident?i=ip_options">ip_options</a>) + 40,
<a name="L1099" href="source/net/ipv4/ip_output.c#L1099">1099</a>                                             sk-&gt;sk_allocation);
<a name="L1100" href="source/net/ipv4/ip_output.c#L1100">1100</a>                         if (<a href="ident?i=unlikely">unlikely</a>(!cork-&gt;opt))
<a name="L1101" href="source/net/ipv4/ip_output.c#L1101">1101</a>                                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1102" href="source/net/ipv4/ip_output.c#L1102">1102</a>                 }
<a name="L1103" href="source/net/ipv4/ip_output.c#L1103">1103</a>                 <a href="ident?i=memcpy">memcpy</a>(cork-&gt;opt, &amp;opt-&gt;opt, sizeof(struct <a href="ident?i=ip_options">ip_options</a>) + opt-&gt;opt.<a href="ident?i=optlen">optlen</a>);
<a name="L1104" href="source/net/ipv4/ip_output.c#L1104">1104</a>                 cork-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPCORK_OPT">IPCORK_OPT</a>;
<a name="L1105" href="source/net/ipv4/ip_output.c#L1105">1105</a>                 cork-&gt;<a href="ident?i=addr">addr</a> = ipc-&gt;<a href="ident?i=addr">addr</a>;
<a name="L1106" href="source/net/ipv4/ip_output.c#L1106">1106</a>         }
<a name="L1107" href="source/net/ipv4/ip_output.c#L1107">1107</a>         <a href="ident?i=rt">rt</a> = *rtp;
<a name="L1108" href="source/net/ipv4/ip_output.c#L1108">1108</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=rt">rt</a>))
<a name="L1109" href="source/net/ipv4/ip_output.c#L1109">1109</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1110" href="source/net/ipv4/ip_output.c#L1110">1110</a>         <b><i>/*</i></b>
<a name="L1111" href="source/net/ipv4/ip_output.c#L1111">1111</a> <b><i>         * We steal reference to this route, caller should not release it</i></b>
<a name="L1112" href="source/net/ipv4/ip_output.c#L1112">1112</a> <b><i>         */</i></b>
<a name="L1113" href="source/net/ipv4/ip_output.c#L1113">1113</a>         *rtp = <a href="ident?i=NULL">NULL</a>;
<a name="L1114" href="source/net/ipv4/ip_output.c#L1114">1114</a>         cork-&gt;fragsize = <a href="ident?i=ip_sk_use_pmtu">ip_sk_use_pmtu</a>(sk) ?
<a name="L1115" href="source/net/ipv4/ip_output.c#L1115">1115</a>                          <a href="ident?i=dst_mtu">dst_mtu</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>) : <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>;
<a name="L1116" href="source/net/ipv4/ip_output.c#L1116">1116</a>         cork-&gt;<a href="ident?i=dst">dst</a> = &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L1117" href="source/net/ipv4/ip_output.c#L1117">1117</a>         cork-&gt;<a href="ident?i=length">length</a> = 0;
<a name="L1118" href="source/net/ipv4/ip_output.c#L1118">1118</a>         cork-&gt;<a href="ident?i=ttl">ttl</a> = ipc-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L1119" href="source/net/ipv4/ip_output.c#L1119">1119</a>         cork-&gt;tos = ipc-&gt;tos;
<a name="L1120" href="source/net/ipv4/ip_output.c#L1120">1120</a>         cork-&gt;<a href="ident?i=priority">priority</a> = ipc-&gt;<a href="ident?i=priority">priority</a>;
<a name="L1121" href="source/net/ipv4/ip_output.c#L1121">1121</a>         cork-&gt;tx_flags = ipc-&gt;tx_flags;
<a name="L1122" href="source/net/ipv4/ip_output.c#L1122">1122</a> 
<a name="L1123" href="source/net/ipv4/ip_output.c#L1123">1123</a>         return 0;
<a name="L1124" href="source/net/ipv4/ip_output.c#L1124">1124</a> }
<a name="L1125" href="source/net/ipv4/ip_output.c#L1125">1125</a> 
<a name="L1126" href="source/net/ipv4/ip_output.c#L1126">1126</a> <b><i>/*</i></b>
<a name="L1127" href="source/net/ipv4/ip_output.c#L1127">1127</a> <b><i> *      ip_append_data() and ip_append_page() can make one large IP datagram</i></b>
<a name="L1128" href="source/net/ipv4/ip_output.c#L1128">1128</a> <b><i> *      from many pieces of data. Each pieces will be holded on the socket</i></b>
<a name="L1129" href="source/net/ipv4/ip_output.c#L1129">1129</a> <b><i> *      until ip_push_pending_frames() is called. Each piece can be a page</i></b>
<a name="L1130" href="source/net/ipv4/ip_output.c#L1130">1130</a> <b><i> *      or non-page data.</i></b>
<a name="L1131" href="source/net/ipv4/ip_output.c#L1131">1131</a> <b><i> *</i></b>
<a name="L1132" href="source/net/ipv4/ip_output.c#L1132">1132</a> <b><i> *      Not only UDP, other transport protocols - e.g. raw sockets - can use</i></b>
<a name="L1133" href="source/net/ipv4/ip_output.c#L1133">1133</a> <b><i> *      this interface potentially.</i></b>
<a name="L1134" href="source/net/ipv4/ip_output.c#L1134">1134</a> <b><i> *</i></b>
<a name="L1135" href="source/net/ipv4/ip_output.c#L1135">1135</a> <b><i> *      LATER: length must be adjusted by pad at tail, when it is required.</i></b>
<a name="L1136" href="source/net/ipv4/ip_output.c#L1136">1136</a> <b><i> */</i></b>
<a name="L1137" href="source/net/ipv4/ip_output.c#L1137">1137</a> int <a href="ident?i=ip_append_data">ip_append_data</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L1138" href="source/net/ipv4/ip_output.c#L1138">1138</a>                    int getfrag(void *from, char *to, int <a href="ident?i=offset">offset</a>, int <a href="ident?i=len">len</a>,
<a name="L1139" href="source/net/ipv4/ip_output.c#L1139">1139</a>                                int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>),
<a name="L1140" href="source/net/ipv4/ip_output.c#L1140">1140</a>                    void *from, int <a href="ident?i=length">length</a>, int transhdrlen,
<a name="L1141" href="source/net/ipv4/ip_output.c#L1141">1141</a>                    struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> *ipc, struct <a href="ident?i=rtable">rtable</a> **rtp,
<a name="L1142" href="source/net/ipv4/ip_output.c#L1142">1142</a>                    unsigned int <a href="ident?i=flags">flags</a>)
<a name="L1143" href="source/net/ipv4/ip_output.c#L1143">1143</a> {
<a name="L1144" href="source/net/ipv4/ip_output.c#L1144">1144</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1145" href="source/net/ipv4/ip_output.c#L1145">1145</a>         int <a href="ident?i=err">err</a>;
<a name="L1146" href="source/net/ipv4/ip_output.c#L1146">1146</a> 
<a name="L1147" href="source/net/ipv4/ip_output.c#L1147">1147</a>         if (<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=MSG_PROBE">MSG_PROBE</a>)
<a name="L1148" href="source/net/ipv4/ip_output.c#L1148">1148</a>                 return 0;
<a name="L1149" href="source/net/ipv4/ip_output.c#L1149">1149</a> 
<a name="L1150" href="source/net/ipv4/ip_output.c#L1150">1150</a>         if (<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;sk-&gt;sk_write_queue)) {
<a name="L1151" href="source/net/ipv4/ip_output.c#L1151">1151</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_setup_cork">ip_setup_cork</a>(sk, &amp;inet-&gt;cork.<a href="ident?i=base">base</a>, ipc, rtp);
<a name="L1152" href="source/net/ipv4/ip_output.c#L1152">1152</a>                 if (<a href="ident?i=err">err</a>)
<a name="L1153" href="source/net/ipv4/ip_output.c#L1153">1153</a>                         return <a href="ident?i=err">err</a>;
<a name="L1154" href="source/net/ipv4/ip_output.c#L1154">1154</a>         } else {
<a name="L1155" href="source/net/ipv4/ip_output.c#L1155">1155</a>                 transhdrlen = 0;
<a name="L1156" href="source/net/ipv4/ip_output.c#L1156">1156</a>         }
<a name="L1157" href="source/net/ipv4/ip_output.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/ip_output.c#L1158">1158</a>         return <a href="ident?i=__ip_append_data">__ip_append_data</a>(sk, fl4, &amp;sk-&gt;sk_write_queue, &amp;inet-&gt;cork.<a href="ident?i=base">base</a>,
<a name="L1159" href="source/net/ipv4/ip_output.c#L1159">1159</a>                                 <a href="ident?i=sk_page_frag">sk_page_frag</a>(sk), getfrag,
<a name="L1160" href="source/net/ipv4/ip_output.c#L1160">1160</a>                                 from, <a href="ident?i=length">length</a>, transhdrlen, <a href="ident?i=flags">flags</a>);
<a name="L1161" href="source/net/ipv4/ip_output.c#L1161">1161</a> }
<a name="L1162" href="source/net/ipv4/ip_output.c#L1162">1162</a> 
<a name="L1163" href="source/net/ipv4/ip_output.c#L1163">1163</a> <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=ip_append_page">ip_append_page</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=flowi4">flowi4</a> *fl4, struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>,
<a name="L1164" href="source/net/ipv4/ip_output.c#L1164">1164</a>                        int <a href="ident?i=offset">offset</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>, int <a href="ident?i=flags">flags</a>)
<a name="L1165" href="source/net/ipv4/ip_output.c#L1165">1165</a> {
<a name="L1166" href="source/net/ipv4/ip_output.c#L1166">1166</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1167" href="source/net/ipv4/ip_output.c#L1167">1167</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1168" href="source/net/ipv4/ip_output.c#L1168">1168</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1169" href="source/net/ipv4/ip_output.c#L1169">1169</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1170" href="source/net/ipv4/ip_output.c#L1170">1170</a>         struct <a href="ident?i=inet_cork">inet_cork</a> *cork;
<a name="L1171" href="source/net/ipv4/ip_output.c#L1171">1171</a>         int hh_len;
<a name="L1172" href="source/net/ipv4/ip_output.c#L1172">1172</a>         int <a href="ident?i=mtu">mtu</a>;
<a name="L1173" href="source/net/ipv4/ip_output.c#L1173">1173</a>         int <a href="ident?i=len">len</a>;
<a name="L1174" href="source/net/ipv4/ip_output.c#L1174">1174</a>         int <a href="ident?i=err">err</a>;
<a name="L1175" href="source/net/ipv4/ip_output.c#L1175">1175</a>         unsigned int maxfraglen, fragheaderlen, fraggap, maxnonfragsize;
<a name="L1176" href="source/net/ipv4/ip_output.c#L1176">1176</a> 
<a name="L1177" href="source/net/ipv4/ip_output.c#L1177">1177</a>         if (inet-&gt;hdrincl)
<a name="L1178" href="source/net/ipv4/ip_output.c#L1178">1178</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1179" href="source/net/ipv4/ip_output.c#L1179">1179</a> 
<a name="L1180" href="source/net/ipv4/ip_output.c#L1180">1180</a>         if (<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=MSG_PROBE">MSG_PROBE</a>)
<a name="L1181" href="source/net/ipv4/ip_output.c#L1181">1181</a>                 return 0;
<a name="L1182" href="source/net/ipv4/ip_output.c#L1182">1182</a> 
<a name="L1183" href="source/net/ipv4/ip_output.c#L1183">1183</a>         if (<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;sk-&gt;sk_write_queue))
<a name="L1184" href="source/net/ipv4/ip_output.c#L1184">1184</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1185" href="source/net/ipv4/ip_output.c#L1185">1185</a> 
<a name="L1186" href="source/net/ipv4/ip_output.c#L1186">1186</a>         cork = &amp;inet-&gt;cork.<a href="ident?i=base">base</a>;
<a name="L1187" href="source/net/ipv4/ip_output.c#L1187">1187</a>         <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)cork-&gt;<a href="ident?i=dst">dst</a>;
<a name="L1188" href="source/net/ipv4/ip_output.c#L1188">1188</a>         if (cork-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPCORK_OPT">IPCORK_OPT</a>)
<a name="L1189" href="source/net/ipv4/ip_output.c#L1189">1189</a>                 opt = cork-&gt;opt;
<a name="L1190" href="source/net/ipv4/ip_output.c#L1190">1190</a> 
<a name="L1191" href="source/net/ipv4/ip_output.c#L1191">1191</a>         if (!(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>&amp;<a href="ident?i=NETIF_F_SG">NETIF_F_SG</a>))
<a name="L1192" href="source/net/ipv4/ip_output.c#L1192">1192</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L1193" href="source/net/ipv4/ip_output.c#L1193">1193</a> 
<a name="L1194" href="source/net/ipv4/ip_output.c#L1194">1194</a>         hh_len = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L1195" href="source/net/ipv4/ip_output.c#L1195">1195</a>         <a href="ident?i=mtu">mtu</a> = cork-&gt;fragsize;
<a name="L1196" href="source/net/ipv4/ip_output.c#L1196">1196</a> 
<a name="L1197" href="source/net/ipv4/ip_output.c#L1197">1197</a>         fragheaderlen = sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + (opt ? opt-&gt;<a href="ident?i=optlen">optlen</a> : 0);
<a name="L1198" href="source/net/ipv4/ip_output.c#L1198">1198</a>         maxfraglen = ((<a href="ident?i=mtu">mtu</a> - fragheaderlen) &amp; ~7) + fragheaderlen;
<a name="L1199" href="source/net/ipv4/ip_output.c#L1199">1199</a>         maxnonfragsize = <a href="ident?i=ip_sk_ignore_df">ip_sk_ignore_df</a>(sk) ? 0xFFFF : <a href="ident?i=mtu">mtu</a>;
<a name="L1200" href="source/net/ipv4/ip_output.c#L1200">1200</a> 
<a name="L1201" href="source/net/ipv4/ip_output.c#L1201">1201</a>         if (cork-&gt;<a href="ident?i=length">length</a> + <a href="ident?i=size">size</a> &gt; maxnonfragsize - fragheaderlen) {
<a name="L1202" href="source/net/ipv4/ip_output.c#L1202">1202</a>                 <a href="ident?i=ip_local_error">ip_local_error</a>(sk, <a href="ident?i=EMSGSIZE">EMSGSIZE</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>,
<a name="L1203" href="source/net/ipv4/ip_output.c#L1203">1203</a>                                <a href="ident?i=mtu">mtu</a> - (opt ? opt-&gt;<a href="ident?i=optlen">optlen</a> : 0));
<a name="L1204" href="source/net/ipv4/ip_output.c#L1204">1204</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1205" href="source/net/ipv4/ip_output.c#L1205">1205</a>         }
<a name="L1206" href="source/net/ipv4/ip_output.c#L1206">1206</a> 
<a name="L1207" href="source/net/ipv4/ip_output.c#L1207">1207</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek_tail">skb_peek_tail</a>(&amp;sk-&gt;sk_write_queue);
<a name="L1208" href="source/net/ipv4/ip_output.c#L1208">1208</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1209" href="source/net/ipv4/ip_output.c#L1209">1209</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1210" href="source/net/ipv4/ip_output.c#L1210">1210</a> 
<a name="L1211" href="source/net/ipv4/ip_output.c#L1211">1211</a>         cork-&gt;<a href="ident?i=length">length</a> += <a href="ident?i=size">size</a>;
<a name="L1212" href="source/net/ipv4/ip_output.c#L1212">1212</a>         if ((<a href="ident?i=size">size</a> + <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=mtu">mtu</a>) &amp;&amp;
<a name="L1213" href="source/net/ipv4/ip_output.c#L1213">1213</a>             (sk-&gt;sk_protocol == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>) &amp;&amp;
<a name="L1214" href="source/net/ipv4/ip_output.c#L1214">1214</a>             (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=NETIF_F_UFO">NETIF_F_UFO</a>)) {
<a name="L1215" href="source/net/ipv4/ip_output.c#L1215">1215</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_size = <a href="ident?i=mtu">mtu</a> - fragheaderlen;
<a name="L1216" href="source/net/ipv4/ip_output.c#L1216">1216</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type = SKB_GSO_UDP;
<a name="L1217" href="source/net/ipv4/ip_output.c#L1217">1217</a>         }
<a name="L1218" href="source/net/ipv4/ip_output.c#L1218">1218</a> 
<a name="L1219" href="source/net/ipv4/ip_output.c#L1219">1219</a>         while (<a href="ident?i=size">size</a> &gt; 0) {
<a name="L1220" href="source/net/ipv4/ip_output.c#L1220">1220</a>                 int <a href="ident?i=i">i</a>;
<a name="L1221" href="source/net/ipv4/ip_output.c#L1221">1221</a> 
<a name="L1222" href="source/net/ipv4/ip_output.c#L1222">1222</a>                 if (<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>))
<a name="L1223" href="source/net/ipv4/ip_output.c#L1223">1223</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=size">size</a>;
<a name="L1224" href="source/net/ipv4/ip_output.c#L1224">1224</a>                 else {
<a name="L1225" href="source/net/ipv4/ip_output.c#L1225">1225</a> 
<a name="L1226" href="source/net/ipv4/ip_output.c#L1226">1226</a>                         <b><i>/* Check if the remaining data fits into current packet. */</i></b>
<a name="L1227" href="source/net/ipv4/ip_output.c#L1227">1227</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=mtu">mtu</a> - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1228" href="source/net/ipv4/ip_output.c#L1228">1228</a>                         if (<a href="ident?i=len">len</a> &lt; <a href="ident?i=size">size</a>)
<a name="L1229" href="source/net/ipv4/ip_output.c#L1229">1229</a>                                 <a href="ident?i=len">len</a> = maxfraglen - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1230" href="source/net/ipv4/ip_output.c#L1230">1230</a>                 }
<a name="L1231" href="source/net/ipv4/ip_output.c#L1231">1231</a>                 if (<a href="ident?i=len">len</a> &lt;= 0) {
<a name="L1232" href="source/net/ipv4/ip_output.c#L1232">1232</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *skb_prev;
<a name="L1233" href="source/net/ipv4/ip_output.c#L1233">1233</a>                         int alloclen;
<a name="L1234" href="source/net/ipv4/ip_output.c#L1234">1234</a> 
<a name="L1235" href="source/net/ipv4/ip_output.c#L1235">1235</a>                         skb_prev = <a href="ident?i=skb">skb</a>;
<a name="L1236" href="source/net/ipv4/ip_output.c#L1236">1236</a>                         fraggap = skb_prev-&gt;<a href="ident?i=len">len</a> - maxfraglen;
<a name="L1237" href="source/net/ipv4/ip_output.c#L1237">1237</a> 
<a name="L1238" href="source/net/ipv4/ip_output.c#L1238">1238</a>                         alloclen = fragheaderlen + hh_len + fraggap + 15;
<a name="L1239" href="source/net/ipv4/ip_output.c#L1239">1239</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_wmalloc">sock_wmalloc</a>(sk, alloclen, 1, sk-&gt;sk_allocation);
<a name="L1240" href="source/net/ipv4/ip_output.c#L1240">1240</a>                         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=skb">skb</a>)) {
<a name="L1241" href="source/net/ipv4/ip_output.c#L1241">1241</a>                                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1242" href="source/net/ipv4/ip_output.c#L1242">1242</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L1243" href="source/net/ipv4/ip_output.c#L1243">1243</a>                         }
<a name="L1244" href="source/net/ipv4/ip_output.c#L1244">1244</a> 
<a name="L1245" href="source/net/ipv4/ip_output.c#L1245">1245</a>                         <b><i>/*</i></b>
<a name="L1246" href="source/net/ipv4/ip_output.c#L1246">1246</a> <b><i>                         *      Fill in the control structures</i></b>
<a name="L1247" href="source/net/ipv4/ip_output.c#L1247">1247</a> <b><i>                         */</i></b>
<a name="L1248" href="source/net/ipv4/ip_output.c#L1248">1248</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L1249" href="source/net/ipv4/ip_output.c#L1249">1249</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L1250" href="source/net/ipv4/ip_output.c#L1250">1250</a>                         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hh_len);
<a name="L1251" href="source/net/ipv4/ip_output.c#L1251">1251</a> 
<a name="L1252" href="source/net/ipv4/ip_output.c#L1252">1252</a>                         <b><i>/*</i></b>
<a name="L1253" href="source/net/ipv4/ip_output.c#L1253">1253</a> <b><i>                         *      Find where to start putting bytes.</i></b>
<a name="L1254" href="source/net/ipv4/ip_output.c#L1254">1254</a> <b><i>                         */</i></b>
<a name="L1255" href="source/net/ipv4/ip_output.c#L1255">1255</a>                         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, fragheaderlen + fraggap);
<a name="L1256" href="source/net/ipv4/ip_output.c#L1256">1256</a>                         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1257" href="source/net/ipv4/ip_output.c#L1257">1257</a>                         <a href="ident?i=skb">skb</a>-&gt;transport_header = (<a href="ident?i=skb">skb</a>-&gt;network_header +
<a name="L1258" href="source/net/ipv4/ip_output.c#L1258">1258</a>                                                  fragheaderlen);
<a name="L1259" href="source/net/ipv4/ip_output.c#L1259">1259</a>                         if (fraggap) {
<a name="L1260" href="source/net/ipv4/ip_output.c#L1260">1260</a>                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=skb_copy_and_csum_bits">skb_copy_and_csum_bits</a>(skb_prev,
<a name="L1261" href="source/net/ipv4/ip_output.c#L1261">1261</a>                                                                    maxfraglen,
<a name="L1262" href="source/net/ipv4/ip_output.c#L1262">1262</a>                                                     <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>),
<a name="L1263" href="source/net/ipv4/ip_output.c#L1263">1263</a>                                                                    fraggap, 0);
<a name="L1264" href="source/net/ipv4/ip_output.c#L1264">1264</a>                                 skb_prev-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_sub">csum_sub</a>(skb_prev-&gt;<a href="ident?i=csum">csum</a>,
<a name="L1265" href="source/net/ipv4/ip_output.c#L1265">1265</a>                                                           <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>);
<a name="L1266" href="source/net/ipv4/ip_output.c#L1266">1266</a>                                 <a href="ident?i=pskb_trim_unique">pskb_trim_unique</a>(skb_prev, maxfraglen);
<a name="L1267" href="source/net/ipv4/ip_output.c#L1267">1267</a>                         }
<a name="L1268" href="source/net/ipv4/ip_output.c#L1268">1268</a> 
<a name="L1269" href="source/net/ipv4/ip_output.c#L1269">1269</a>                         <b><i>/*</i></b>
<a name="L1270" href="source/net/ipv4/ip_output.c#L1270">1270</a> <b><i>                         * Put the packet on the pending queue.</i></b>
<a name="L1271" href="source/net/ipv4/ip_output.c#L1271">1271</a> <b><i>                         */</i></b>
<a name="L1272" href="source/net/ipv4/ip_output.c#L1272">1272</a>                         <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(&amp;sk-&gt;sk_write_queue, <a href="ident?i=skb">skb</a>);
<a name="L1273" href="source/net/ipv4/ip_output.c#L1273">1273</a>                         continue;
<a name="L1274" href="source/net/ipv4/ip_output.c#L1274">1274</a>                 }
<a name="L1275" href="source/net/ipv4/ip_output.c#L1275">1275</a> 
<a name="L1276" href="source/net/ipv4/ip_output.c#L1276">1276</a>                 <a href="ident?i=i">i</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags;
<a name="L1277" href="source/net/ipv4/ip_output.c#L1277">1277</a>                 if (<a href="ident?i=len">len</a> &gt; <a href="ident?i=size">size</a>)
<a name="L1278" href="source/net/ipv4/ip_output.c#L1278">1278</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=size">size</a>;
<a name="L1279" href="source/net/ipv4/ip_output.c#L1279">1279</a>                 if (<a href="ident?i=skb_can_coalesce">skb_can_coalesce</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>)) {
<a name="L1280" href="source/net/ipv4/ip_output.c#L1280">1280</a>                         <a href="ident?i=skb_frag_size_add">skb_frag_size_add</a>(&amp;<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frags[<a href="ident?i=i">i</a>-1], <a href="ident?i=len">len</a>);
<a name="L1281" href="source/net/ipv4/ip_output.c#L1281">1281</a>                 } else if (<a href="ident?i=i">i</a> &lt; <a href="ident?i=MAX_SKB_FRAGS">MAX_SKB_FRAGS</a>) {
<a name="L1282" href="source/net/ipv4/ip_output.c#L1282">1282</a>                         <a href="ident?i=get_page">get_page</a>(<a href="ident?i=page">page</a>);
<a name="L1283" href="source/net/ipv4/ip_output.c#L1283">1283</a>                         <a href="ident?i=skb_fill_page_desc">skb_fill_page_desc</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=len">len</a>);
<a name="L1284" href="source/net/ipv4/ip_output.c#L1284">1284</a>                 } else {
<a name="L1285" href="source/net/ipv4/ip_output.c#L1285">1285</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1286" href="source/net/ipv4/ip_output.c#L1286">1286</a>                         goto <a href="ident?i=error">error</a>;
<a name="L1287" href="source/net/ipv4/ip_output.c#L1287">1287</a>                 }
<a name="L1288" href="source/net/ipv4/ip_output.c#L1288">1288</a> 
<a name="L1289" href="source/net/ipv4/ip_output.c#L1289">1289</a>                 if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>) {
<a name="L1290" href="source/net/ipv4/ip_output.c#L1290">1290</a>                         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a>;
<a name="L1291" href="source/net/ipv4/ip_output.c#L1291">1291</a>                         <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_page">csum_page</a>(<a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=len">len</a>);
<a name="L1292" href="source/net/ipv4/ip_output.c#L1292">1292</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_add">csum_block_add</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>, <a href="ident?i=csum">csum</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1293" href="source/net/ipv4/ip_output.c#L1293">1293</a>                 }
<a name="L1294" href="source/net/ipv4/ip_output.c#L1294">1294</a> 
<a name="L1295" href="source/net/ipv4/ip_output.c#L1295">1295</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> += <a href="ident?i=len">len</a>;
<a name="L1296" href="source/net/ipv4/ip_output.c#L1296">1296</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a> += <a href="ident?i=len">len</a>;
<a name="L1297" href="source/net/ipv4/ip_output.c#L1297">1297</a>                 <a href="ident?i=skb">skb</a>-&gt;truesize += <a href="ident?i=len">len</a>;
<a name="L1298" href="source/net/ipv4/ip_output.c#L1298">1298</a>                 <a href="ident?i=atomic_add">atomic_add</a>(<a href="ident?i=len">len</a>, &amp;sk-&gt;sk_wmem_alloc);
<a name="L1299" href="source/net/ipv4/ip_output.c#L1299">1299</a>                 <a href="ident?i=offset">offset</a> += <a href="ident?i=len">len</a>;
<a name="L1300" href="source/net/ipv4/ip_output.c#L1300">1300</a>                 <a href="ident?i=size">size</a> -= <a href="ident?i=len">len</a>;
<a name="L1301" href="source/net/ipv4/ip_output.c#L1301">1301</a>         }
<a name="L1302" href="source/net/ipv4/ip_output.c#L1302">1302</a>         return 0;
<a name="L1303" href="source/net/ipv4/ip_output.c#L1303">1303</a> 
<a name="L1304" href="source/net/ipv4/ip_output.c#L1304">1304</a> <a href="ident?i=error">error</a>:
<a name="L1305" href="source/net/ipv4/ip_output.c#L1305">1305</a>         cork-&gt;<a href="ident?i=length">length</a> -= <a href="ident?i=size">size</a>;
<a name="L1306" href="source/net/ipv4/ip_output.c#L1306">1306</a>         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), IPSTATS_MIB_OUTDISCARDS);
<a name="L1307" href="source/net/ipv4/ip_output.c#L1307">1307</a>         return <a href="ident?i=err">err</a>;
<a name="L1308" href="source/net/ipv4/ip_output.c#L1308">1308</a> }
<a name="L1309" href="source/net/ipv4/ip_output.c#L1309">1309</a> 
<a name="L1310" href="source/net/ipv4/ip_output.c#L1310">1310</a> static void <a href="ident?i=ip_cork_release">ip_cork_release</a>(struct <a href="ident?i=inet_cork">inet_cork</a> *cork)
<a name="L1311" href="source/net/ipv4/ip_output.c#L1311">1311</a> {
<a name="L1312" href="source/net/ipv4/ip_output.c#L1312">1312</a>         cork-&gt;<a href="ident?i=flags">flags</a> &amp;= ~IPCORK_OPT;
<a name="L1313" href="source/net/ipv4/ip_output.c#L1313">1313</a>         <a href="ident?i=kfree">kfree</a>(cork-&gt;opt);
<a name="L1314" href="source/net/ipv4/ip_output.c#L1314">1314</a>         cork-&gt;opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1315" href="source/net/ipv4/ip_output.c#L1315">1315</a>         <a href="ident?i=dst_release">dst_release</a>(cork-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1316" href="source/net/ipv4/ip_output.c#L1316">1316</a>         cork-&gt;<a href="ident?i=dst">dst</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1317" href="source/net/ipv4/ip_output.c#L1317">1317</a> }
<a name="L1318" href="source/net/ipv4/ip_output.c#L1318">1318</a> 
<a name="L1319" href="source/net/ipv4/ip_output.c#L1319">1319</a> <b><i>/*</i></b>
<a name="L1320" href="source/net/ipv4/ip_output.c#L1320">1320</a> <b><i> *      Combined all pending IP fragments on the socket as one IP datagram</i></b>
<a name="L1321" href="source/net/ipv4/ip_output.c#L1321">1321</a> <b><i> *      and push them out.</i></b>
<a name="L1322" href="source/net/ipv4/ip_output.c#L1322">1322</a> <b><i> */</i></b>
<a name="L1323" href="source/net/ipv4/ip_output.c#L1323">1323</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=__ip_make_skb">__ip_make_skb</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1324" href="source/net/ipv4/ip_output.c#L1324">1324</a>                               struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L1325" href="source/net/ipv4/ip_output.c#L1325">1325</a>                               struct <a href="ident?i=sk_buff_head">sk_buff_head</a> *<a href="ident?i=queue">queue</a>,
<a name="L1326" href="source/net/ipv4/ip_output.c#L1326">1326</a>                               struct <a href="ident?i=inet_cork">inet_cork</a> *cork)
<a name="L1327" href="source/net/ipv4/ip_output.c#L1327">1327</a> {
<a name="L1328" href="source/net/ipv4/ip_output.c#L1328">1328</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, *tmp_skb;
<a name="L1329" href="source/net/ipv4/ip_output.c#L1329">1329</a>         struct <a href="ident?i=sk_buff">sk_buff</a> **tail_skb;
<a name="L1330" href="source/net/ipv4/ip_output.c#L1330">1330</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1331" href="source/net/ipv4/ip_output.c#L1331">1331</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1332" href="source/net/ipv4/ip_output.c#L1332">1332</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1333" href="source/net/ipv4/ip_output.c#L1333">1333</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)cork-&gt;<a href="ident?i=dst">dst</a>;
<a name="L1334" href="source/net/ipv4/ip_output.c#L1334">1334</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1335" href="source/net/ipv4/ip_output.c#L1335">1335</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=df">df</a> = 0;
<a name="L1336" href="source/net/ipv4/ip_output.c#L1336">1336</a>         <a href="ident?i=__u8">__u8</a> <a href="ident?i=ttl">ttl</a>;
<a name="L1337" href="source/net/ipv4/ip_output.c#L1337">1337</a> 
<a name="L1338" href="source/net/ipv4/ip_output.c#L1338">1338</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(<a href="ident?i=queue">queue</a>);
<a name="L1339" href="source/net/ipv4/ip_output.c#L1339">1339</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1340" href="source/net/ipv4/ip_output.c#L1340">1340</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1341" href="source/net/ipv4/ip_output.c#L1341">1341</a>         tail_skb = &amp;(<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_list);
<a name="L1342" href="source/net/ipv4/ip_output.c#L1342">1342</a> 
<a name="L1343" href="source/net/ipv4/ip_output.c#L1343">1343</a>         <b><i>/* move skb-&gt;data to ip header from ext header */</i></b>
<a name="L1344" href="source/net/ipv4/ip_output.c#L1344">1344</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> &lt; <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>))
<a name="L1345" href="source/net/ipv4/ip_output.c#L1345">1345</a>                 <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>));
<a name="L1346" href="source/net/ipv4/ip_output.c#L1346">1346</a>         while ((tmp_skb = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(<a href="ident?i=queue">queue</a>)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1347" href="source/net/ipv4/ip_output.c#L1347">1347</a>                 <a href="ident?i=__skb_pull">__skb_pull</a>(tmp_skb, <a href="ident?i=skb_network_header_len">skb_network_header_len</a>(<a href="ident?i=skb">skb</a>));
<a name="L1348" href="source/net/ipv4/ip_output.c#L1348">1348</a>                 *tail_skb = tmp_skb;
<a name="L1349" href="source/net/ipv4/ip_output.c#L1349">1349</a>                 tail_skb = &amp;(tmp_skb-&gt;<a href="ident?i=next">next</a>);
<a name="L1350" href="source/net/ipv4/ip_output.c#L1350">1350</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> += tmp_skb-&gt;<a href="ident?i=len">len</a>;
<a name="L1351" href="source/net/ipv4/ip_output.c#L1351">1351</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a> += tmp_skb-&gt;<a href="ident?i=len">len</a>;
<a name="L1352" href="source/net/ipv4/ip_output.c#L1352">1352</a>                 <a href="ident?i=skb">skb</a>-&gt;truesize += tmp_skb-&gt;truesize;
<a name="L1353" href="source/net/ipv4/ip_output.c#L1353">1353</a>                 tmp_skb-&gt;destructor = <a href="ident?i=NULL">NULL</a>;
<a name="L1354" href="source/net/ipv4/ip_output.c#L1354">1354</a>                 tmp_skb-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L1355" href="source/net/ipv4/ip_output.c#L1355">1355</a>         }
<a name="L1356" href="source/net/ipv4/ip_output.c#L1356">1356</a> 
<a name="L1357" href="source/net/ipv4/ip_output.c#L1357">1357</a>         <b><i>/* Unless user demanded real pmtu discovery (IP_PMTUDISC_DO), we allow</i></b>
<a name="L1358" href="source/net/ipv4/ip_output.c#L1358">1358</a> <b><i>         * to fragment the frame generated here. No matter, what transforms</i></b>
<a name="L1359" href="source/net/ipv4/ip_output.c#L1359">1359</a> <b><i>         * how transforms change size of the packet, it will come out.</i></b>
<a name="L1360" href="source/net/ipv4/ip_output.c#L1360">1360</a> <b><i>         */</i></b>
<a name="L1361" href="source/net/ipv4/ip_output.c#L1361">1361</a>         <a href="ident?i=skb">skb</a>-&gt;ignore_df = <a href="ident?i=ip_sk_ignore_df">ip_sk_ignore_df</a>(sk);
<a name="L1362" href="source/net/ipv4/ip_output.c#L1362">1362</a> 
<a name="L1363" href="source/net/ipv4/ip_output.c#L1363">1363</a>         <b><i>/* DF bit is set when we want to see DF on outgoing frames.</i></b>
<a name="L1364" href="source/net/ipv4/ip_output.c#L1364">1364</a> <b><i>         * If ignore_df is set too, we still allow to fragment this frame</i></b>
<a name="L1365" href="source/net/ipv4/ip_output.c#L1365">1365</a> <b><i>         * locally. */</i></b>
<a name="L1366" href="source/net/ipv4/ip_output.c#L1366">1366</a>         if (inet-&gt;pmtudisc == <a href="ident?i=IP_PMTUDISC_DO">IP_PMTUDISC_DO</a> ||
<a name="L1367" href="source/net/ipv4/ip_output.c#L1367">1367</a>             inet-&gt;pmtudisc == <a href="ident?i=IP_PMTUDISC_PROBE">IP_PMTUDISC_PROBE</a> ||
<a name="L1368" href="source/net/ipv4/ip_output.c#L1368">1368</a>             (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= <a href="ident?i=dst_mtu">dst_mtu</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>) &amp;&amp;
<a name="L1369" href="source/net/ipv4/ip_output.c#L1369">1369</a>              <a href="ident?i=ip_dont_fragment">ip_dont_fragment</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>)))
<a name="L1370" href="source/net/ipv4/ip_output.c#L1370">1370</a>                 <a href="ident?i=df">df</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L1371" href="source/net/ipv4/ip_output.c#L1371">1371</a> 
<a name="L1372" href="source/net/ipv4/ip_output.c#L1372">1372</a>         if (cork-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPCORK_OPT">IPCORK_OPT</a>)
<a name="L1373" href="source/net/ipv4/ip_output.c#L1373">1373</a>                 opt = cork-&gt;opt;
<a name="L1374" href="source/net/ipv4/ip_output.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/ip_output.c#L1375">1375</a>         if (cork-&gt;<a href="ident?i=ttl">ttl</a> != 0)
<a name="L1376" href="source/net/ipv4/ip_output.c#L1376">1376</a>                 <a href="ident?i=ttl">ttl</a> = cork-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L1377" href="source/net/ipv4/ip_output.c#L1377">1377</a>         else if (<a href="ident?i=rt">rt</a>-&gt;rt_type == RTN_MULTICAST)
<a name="L1378" href="source/net/ipv4/ip_output.c#L1378">1378</a>                 <a href="ident?i=ttl">ttl</a> = inet-&gt;mc_ttl;
<a name="L1379" href="source/net/ipv4/ip_output.c#L1379">1379</a>         else
<a name="L1380" href="source/net/ipv4/ip_output.c#L1380">1380</a>                 <a href="ident?i=ttl">ttl</a> = <a href="ident?i=ip_select_ttl">ip_select_ttl</a>(inet, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1381" href="source/net/ipv4/ip_output.c#L1381">1381</a> 
<a name="L1382" href="source/net/ipv4/ip_output.c#L1382">1382</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1383" href="source/net/ipv4/ip_output.c#L1383">1383</a>         iph-&gt;<a href="ident?i=version">version</a> = 4;
<a name="L1384" href="source/net/ipv4/ip_output.c#L1384">1384</a>         iph-&gt;ihl = 5;
<a name="L1385" href="source/net/ipv4/ip_output.c#L1385">1385</a>         iph-&gt;tos = (cork-&gt;tos != -1) ? cork-&gt;tos : inet-&gt;tos;
<a name="L1386" href="source/net/ipv4/ip_output.c#L1386">1386</a>         iph-&gt;frag_off = <a href="ident?i=df">df</a>;
<a name="L1387" href="source/net/ipv4/ip_output.c#L1387">1387</a>         iph-&gt;<a href="ident?i=ttl">ttl</a> = <a href="ident?i=ttl">ttl</a>;
<a name="L1388" href="source/net/ipv4/ip_output.c#L1388">1388</a>         iph-&gt;<a href="ident?i=protocol">protocol</a> = sk-&gt;sk_protocol;
<a name="L1389" href="source/net/ipv4/ip_output.c#L1389">1389</a>         <a href="ident?i=ip_copy_addrs">ip_copy_addrs</a>(iph, fl4);
<a name="L1390" href="source/net/ipv4/ip_output.c#L1390">1390</a>         <a href="ident?i=ip_select_ident">ip_select_ident</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, sk);
<a name="L1391" href="source/net/ipv4/ip_output.c#L1391">1391</a> 
<a name="L1392" href="source/net/ipv4/ip_output.c#L1392">1392</a>         if (opt) {
<a name="L1393" href="source/net/ipv4/ip_output.c#L1393">1393</a>                 iph-&gt;ihl += opt-&gt;<a href="ident?i=optlen">optlen</a>&gt;&gt;2;
<a name="L1394" href="source/net/ipv4/ip_output.c#L1394">1394</a>                 <a href="ident?i=ip_options_build">ip_options_build</a>(<a href="ident?i=skb">skb</a>, opt, cork-&gt;<a href="ident?i=addr">addr</a>, <a href="ident?i=rt">rt</a>, 0);
<a name="L1395" href="source/net/ipv4/ip_output.c#L1395">1395</a>         }
<a name="L1396" href="source/net/ipv4/ip_output.c#L1396">1396</a> 
<a name="L1397" href="source/net/ipv4/ip_output.c#L1397">1397</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = (cork-&gt;tos != -1) ? cork-&gt;<a href="ident?i=priority">priority</a>: sk-&gt;sk_priority;
<a name="L1398" href="source/net/ipv4/ip_output.c#L1398">1398</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> = sk-&gt;sk_mark;
<a name="L1399" href="source/net/ipv4/ip_output.c#L1399">1399</a>         <b><i>/*</i></b>
<a name="L1400" href="source/net/ipv4/ip_output.c#L1400">1400</a> <b><i>         * Steal rt from cork.dst to avoid a pair of atomic_inc/atomic_dec</i></b>
<a name="L1401" href="source/net/ipv4/ip_output.c#L1401">1401</a> <b><i>         * on dst refcount</i></b>
<a name="L1402" href="source/net/ipv4/ip_output.c#L1402">1402</a> <b><i>         */</i></b>
<a name="L1403" href="source/net/ipv4/ip_output.c#L1403">1403</a>         cork-&gt;<a href="ident?i=dst">dst</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1404" href="source/net/ipv4/ip_output.c#L1404">1404</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1405" href="source/net/ipv4/ip_output.c#L1405">1405</a> 
<a name="L1406" href="source/net/ipv4/ip_output.c#L1406">1406</a>         if (iph-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>)
<a name="L1407" href="source/net/ipv4/ip_output.c#L1407">1407</a>                 <a href="ident?i=icmp_out_count">icmp_out_count</a>(<a href="ident?i=net">net</a>, ((struct <a href="ident?i=icmphdr">icmphdr</a> *)
<a name="L1408" href="source/net/ipv4/ip_output.c#L1408">1408</a>                         <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>))-&gt;<a href="ident?i=type">type</a>);
<a name="L1409" href="source/net/ipv4/ip_output.c#L1409">1409</a> 
<a name="L1410" href="source/net/ipv4/ip_output.c#L1410">1410</a>         <a href="ident?i=ip_cork_release">ip_cork_release</a>(cork);
<a name="L1411" href="source/net/ipv4/ip_output.c#L1411">1411</a> <a href="ident?i=out">out</a>:
<a name="L1412" href="source/net/ipv4/ip_output.c#L1412">1412</a>         return <a href="ident?i=skb">skb</a>;
<a name="L1413" href="source/net/ipv4/ip_output.c#L1413">1413</a> }
<a name="L1414" href="source/net/ipv4/ip_output.c#L1414">1414</a> 
<a name="L1415" href="source/net/ipv4/ip_output.c#L1415">1415</a> int <a href="ident?i=ip_send_skb">ip_send_skb</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1416" href="source/net/ipv4/ip_output.c#L1416">1416</a> {
<a name="L1417" href="source/net/ipv4/ip_output.c#L1417">1417</a>         int <a href="ident?i=err">err</a>;
<a name="L1418" href="source/net/ipv4/ip_output.c#L1418">1418</a> 
<a name="L1419" href="source/net/ipv4/ip_output.c#L1419">1419</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_local_out">ip_local_out</a>(<a href="ident?i=skb">skb</a>);
<a name="L1420" href="source/net/ipv4/ip_output.c#L1420">1420</a>         if (<a href="ident?i=err">err</a>) {
<a name="L1421" href="source/net/ipv4/ip_output.c#L1421">1421</a>                 if (<a href="ident?i=err">err</a> &gt; 0)
<a name="L1422" href="source/net/ipv4/ip_output.c#L1422">1422</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=net_xmit_errno">net_xmit_errno</a>(<a href="ident?i=err">err</a>);
<a name="L1423" href="source/net/ipv4/ip_output.c#L1423">1423</a>                 if (<a href="ident?i=err">err</a>)
<a name="L1424" href="source/net/ipv4/ip_output.c#L1424">1424</a>                         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_OUTDISCARDS);
<a name="L1425" href="source/net/ipv4/ip_output.c#L1425">1425</a>         }
<a name="L1426" href="source/net/ipv4/ip_output.c#L1426">1426</a> 
<a name="L1427" href="source/net/ipv4/ip_output.c#L1427">1427</a>         return <a href="ident?i=err">err</a>;
<a name="L1428" href="source/net/ipv4/ip_output.c#L1428">1428</a> }
<a name="L1429" href="source/net/ipv4/ip_output.c#L1429">1429</a> 
<a name="L1430" href="source/net/ipv4/ip_output.c#L1430">1430</a> int <a href="ident?i=ip_push_pending_frames">ip_push_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L1431" href="source/net/ipv4/ip_output.c#L1431">1431</a> {
<a name="L1432" href="source/net/ipv4/ip_output.c#L1432">1432</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1433" href="source/net/ipv4/ip_output.c#L1433">1433</a> 
<a name="L1434" href="source/net/ipv4/ip_output.c#L1434">1434</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=ip_finish_skb">ip_finish_skb</a>(sk, fl4);
<a name="L1435" href="source/net/ipv4/ip_output.c#L1435">1435</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1436" href="source/net/ipv4/ip_output.c#L1436">1436</a>                 return 0;
<a name="L1437" href="source/net/ipv4/ip_output.c#L1437">1437</a> 
<a name="L1438" href="source/net/ipv4/ip_output.c#L1438">1438</a>         <b><i>/* Netfilter gets whole the not fragmented skb. */</i></b>
<a name="L1439" href="source/net/ipv4/ip_output.c#L1439">1439</a>         return <a href="ident?i=ip_send_skb">ip_send_skb</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>);
<a name="L1440" href="source/net/ipv4/ip_output.c#L1440">1440</a> }
<a name="L1441" href="source/net/ipv4/ip_output.c#L1441">1441</a> 
<a name="L1442" href="source/net/ipv4/ip_output.c#L1442">1442</a> <b><i>/*</i></b>
<a name="L1443" href="source/net/ipv4/ip_output.c#L1443">1443</a> <b><i> *      Throw away all pending data on the socket.</i></b>
<a name="L1444" href="source/net/ipv4/ip_output.c#L1444">1444</a> <b><i> */</i></b>
<a name="L1445" href="source/net/ipv4/ip_output.c#L1445">1445</a> static void <a href="ident?i=__ip_flush_pending_frames">__ip_flush_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1446" href="source/net/ipv4/ip_output.c#L1446">1446</a>                                       struct <a href="ident?i=sk_buff_head">sk_buff_head</a> *<a href="ident?i=queue">queue</a>,
<a name="L1447" href="source/net/ipv4/ip_output.c#L1447">1447</a>                                       struct <a href="ident?i=inet_cork">inet_cork</a> *cork)
<a name="L1448" href="source/net/ipv4/ip_output.c#L1448">1448</a> {
<a name="L1449" href="source/net/ipv4/ip_output.c#L1449">1449</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1450" href="source/net/ipv4/ip_output.c#L1450">1450</a> 
<a name="L1451" href="source/net/ipv4/ip_output.c#L1451">1451</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_dequeue_tail">__skb_dequeue_tail</a>(<a href="ident?i=queue">queue</a>)) != <a href="ident?i=NULL">NULL</a>)
<a name="L1452" href="source/net/ipv4/ip_output.c#L1452">1452</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1453" href="source/net/ipv4/ip_output.c#L1453">1453</a> 
<a name="L1454" href="source/net/ipv4/ip_output.c#L1454">1454</a>         <a href="ident?i=ip_cork_release">ip_cork_release</a>(cork);
<a name="L1455" href="source/net/ipv4/ip_output.c#L1455">1455</a> }
<a name="L1456" href="source/net/ipv4/ip_output.c#L1456">1456</a> 
<a name="L1457" href="source/net/ipv4/ip_output.c#L1457">1457</a> void <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1458" href="source/net/ipv4/ip_output.c#L1458">1458</a> {
<a name="L1459" href="source/net/ipv4/ip_output.c#L1459">1459</a>         <a href="ident?i=__ip_flush_pending_frames">__ip_flush_pending_frames</a>(sk, &amp;sk-&gt;sk_write_queue, &amp;<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;cork.<a href="ident?i=base">base</a>);
<a name="L1460" href="source/net/ipv4/ip_output.c#L1460">1460</a> }
<a name="L1461" href="source/net/ipv4/ip_output.c#L1461">1461</a> 
<a name="L1462" href="source/net/ipv4/ip_output.c#L1462">1462</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=ip_make_skb">ip_make_skb</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1463" href="source/net/ipv4/ip_output.c#L1463">1463</a>                             struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L1464" href="source/net/ipv4/ip_output.c#L1464">1464</a>                             int getfrag(void *from, char *to, int <a href="ident?i=offset">offset</a>,
<a name="L1465" href="source/net/ipv4/ip_output.c#L1465">1465</a>                                         int <a href="ident?i=len">len</a>, int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>),
<a name="L1466" href="source/net/ipv4/ip_output.c#L1466">1466</a>                             void *from, int <a href="ident?i=length">length</a>, int transhdrlen,
<a name="L1467" href="source/net/ipv4/ip_output.c#L1467">1467</a>                             struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> *ipc, struct <a href="ident?i=rtable">rtable</a> **rtp,
<a name="L1468" href="source/net/ipv4/ip_output.c#L1468">1468</a>                             unsigned int <a href="ident?i=flags">flags</a>)
<a name="L1469" href="source/net/ipv4/ip_output.c#L1469">1469</a> {
<a name="L1470" href="source/net/ipv4/ip_output.c#L1470">1470</a>         struct <a href="ident?i=inet_cork">inet_cork</a> cork;
<a name="L1471" href="source/net/ipv4/ip_output.c#L1471">1471</a>         struct <a href="ident?i=sk_buff_head">sk_buff_head</a> <a href="ident?i=queue">queue</a>;
<a name="L1472" href="source/net/ipv4/ip_output.c#L1472">1472</a>         int <a href="ident?i=err">err</a>;
<a name="L1473" href="source/net/ipv4/ip_output.c#L1473">1473</a> 
<a name="L1474" href="source/net/ipv4/ip_output.c#L1474">1474</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PROBE">MSG_PROBE</a>)
<a name="L1475" href="source/net/ipv4/ip_output.c#L1475">1475</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1476" href="source/net/ipv4/ip_output.c#L1476">1476</a> 
<a name="L1477" href="source/net/ipv4/ip_output.c#L1477">1477</a>         <a href="ident?i=__skb_queue_head_init">__skb_queue_head_init</a>(&amp;<a href="ident?i=queue">queue</a>);
<a name="L1478" href="source/net/ipv4/ip_output.c#L1478">1478</a> 
<a name="L1479" href="source/net/ipv4/ip_output.c#L1479">1479</a>         cork.<a href="ident?i=flags">flags</a> = 0;
<a name="L1480" href="source/net/ipv4/ip_output.c#L1480">1480</a>         cork.<a href="ident?i=addr">addr</a> = 0;
<a name="L1481" href="source/net/ipv4/ip_output.c#L1481">1481</a>         cork.opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1482" href="source/net/ipv4/ip_output.c#L1482">1482</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_setup_cork">ip_setup_cork</a>(sk, &amp;cork, ipc, rtp);
<a name="L1483" href="source/net/ipv4/ip_output.c#L1483">1483</a>         if (<a href="ident?i=err">err</a>)
<a name="L1484" href="source/net/ipv4/ip_output.c#L1484">1484</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L1485" href="source/net/ipv4/ip_output.c#L1485">1485</a> 
<a name="L1486" href="source/net/ipv4/ip_output.c#L1486">1486</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__ip_append_data">__ip_append_data</a>(sk, fl4, &amp;<a href="ident?i=queue">queue</a>, &amp;cork,
<a name="L1487" href="source/net/ipv4/ip_output.c#L1487">1487</a>                                &amp;<a href="ident?i=current">current</a>-&gt;task_frag, getfrag,
<a name="L1488" href="source/net/ipv4/ip_output.c#L1488">1488</a>                                from, <a href="ident?i=length">length</a>, transhdrlen, <a href="ident?i=flags">flags</a>);
<a name="L1489" href="source/net/ipv4/ip_output.c#L1489">1489</a>         if (<a href="ident?i=err">err</a>) {
<a name="L1490" href="source/net/ipv4/ip_output.c#L1490">1490</a>                 <a href="ident?i=__ip_flush_pending_frames">__ip_flush_pending_frames</a>(sk, &amp;<a href="ident?i=queue">queue</a>, &amp;cork);
<a name="L1491" href="source/net/ipv4/ip_output.c#L1491">1491</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L1492" href="source/net/ipv4/ip_output.c#L1492">1492</a>         }
<a name="L1493" href="source/net/ipv4/ip_output.c#L1493">1493</a> 
<a name="L1494" href="source/net/ipv4/ip_output.c#L1494">1494</a>         return <a href="ident?i=__ip_make_skb">__ip_make_skb</a>(sk, fl4, &amp;<a href="ident?i=queue">queue</a>, &amp;cork);
<a name="L1495" href="source/net/ipv4/ip_output.c#L1495">1495</a> }
<a name="L1496" href="source/net/ipv4/ip_output.c#L1496">1496</a> 
<a name="L1497" href="source/net/ipv4/ip_output.c#L1497">1497</a> <b><i>/*</i></b>
<a name="L1498" href="source/net/ipv4/ip_output.c#L1498">1498</a> <b><i> *      Fetch data from kernel space and fill in checksum if needed.</i></b>
<a name="L1499" href="source/net/ipv4/ip_output.c#L1499">1499</a> <b><i> */</i></b>
<a name="L1500" href="source/net/ipv4/ip_output.c#L1500">1500</a> static int <a href="ident?i=ip_reply_glue_bits">ip_reply_glue_bits</a>(void *dptr, char *to, int <a href="ident?i=offset">offset</a>,
<a name="L1501" href="source/net/ipv4/ip_output.c#L1501">1501</a>                               int <a href="ident?i=len">len</a>, int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1502" href="source/net/ipv4/ip_output.c#L1502">1502</a> {
<a name="L1503" href="source/net/ipv4/ip_output.c#L1503">1503</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a>;
<a name="L1504" href="source/net/ipv4/ip_output.c#L1504">1504</a> 
<a name="L1505" href="source/net/ipv4/ip_output.c#L1505">1505</a>         <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_partial_copy_nocheck">csum_partial_copy_nocheck</a>(dptr+<a href="ident?i=offset">offset</a>, to, <a href="ident?i=len">len</a>, 0);
<a name="L1506" href="source/net/ipv4/ip_output.c#L1506">1506</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_add">csum_block_add</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>, <a href="ident?i=csum">csum</a>, odd);
<a name="L1507" href="source/net/ipv4/ip_output.c#L1507">1507</a>         return 0;
<a name="L1508" href="source/net/ipv4/ip_output.c#L1508">1508</a> }
<a name="L1509" href="source/net/ipv4/ip_output.c#L1509">1509</a> 
<a name="L1510" href="source/net/ipv4/ip_output.c#L1510">1510</a> <b><i>/*</i></b>
<a name="L1511" href="source/net/ipv4/ip_output.c#L1511">1511</a> <b><i> *      Generic function to send a packet as reply to another packet.</i></b>
<a name="L1512" href="source/net/ipv4/ip_output.c#L1512">1512</a> <b><i> *      Used to send some TCP resets/acks so far.</i></b>
<a name="L1513" href="source/net/ipv4/ip_output.c#L1513">1513</a> <b><i> */</i></b>
<a name="L1514" href="source/net/ipv4/ip_output.c#L1514">1514</a> void <a href="ident?i=ip_send_unicast_reply">ip_send_unicast_reply</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1515" href="source/net/ipv4/ip_output.c#L1515">1515</a>                            const struct <a href="ident?i=ip_options">ip_options</a> *sopt,
<a name="L1516" href="source/net/ipv4/ip_output.c#L1516">1516</a>                            <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L1517" href="source/net/ipv4/ip_output.c#L1517">1517</a>                            const struct <a href="ident?i=ip_reply_arg">ip_reply_arg</a> *<a href="ident?i=arg">arg</a>,
<a name="L1518" href="source/net/ipv4/ip_output.c#L1518">1518</a>                            unsigned int <a href="ident?i=len">len</a>)
<a name="L1519" href="source/net/ipv4/ip_output.c#L1519">1519</a> {
<a name="L1520" href="source/net/ipv4/ip_output.c#L1520">1520</a>         struct <a href="ident?i=ip_options_data">ip_options_data</a> replyopts;
<a name="L1521" href="source/net/ipv4/ip_output.c#L1521">1521</a>         struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> ipc;
<a name="L1522" href="source/net/ipv4/ip_output.c#L1522">1522</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1523" href="source/net/ipv4/ip_output.c#L1523">1523</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L1524" href="source/net/ipv4/ip_output.c#L1524">1524</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1525" href="source/net/ipv4/ip_output.c#L1525">1525</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
<a name="L1526" href="source/net/ipv4/ip_output.c#L1526">1526</a>         int <a href="ident?i=err">err</a>;
<a name="L1527" href="source/net/ipv4/ip_output.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/ip_output.c#L1528">1528</a>         if (<a href="ident?i=__ip_options_echo">__ip_options_echo</a>(&amp;replyopts.opt.opt, <a href="ident?i=skb">skb</a>, sopt))
<a name="L1529" href="source/net/ipv4/ip_output.c#L1529">1529</a>                 return;
<a name="L1530" href="source/net/ipv4/ip_output.c#L1530">1530</a> 
<a name="L1531" href="source/net/ipv4/ip_output.c#L1531">1531</a>         ipc.<a href="ident?i=addr">addr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L1532" href="source/net/ipv4/ip_output.c#L1532">1532</a>         ipc.opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1533" href="source/net/ipv4/ip_output.c#L1533">1533</a>         ipc.tx_flags = 0;
<a name="L1534" href="source/net/ipv4/ip_output.c#L1534">1534</a>         ipc.<a href="ident?i=ttl">ttl</a> = 0;
<a name="L1535" href="source/net/ipv4/ip_output.c#L1535">1535</a>         ipc.tos = -1;
<a name="L1536" href="source/net/ipv4/ip_output.c#L1536">1536</a> 
<a name="L1537" href="source/net/ipv4/ip_output.c#L1537">1537</a>         if (replyopts.opt.opt.<a href="ident?i=optlen">optlen</a>) {
<a name="L1538" href="source/net/ipv4/ip_output.c#L1538">1538</a>                 ipc.opt = &amp;replyopts.opt;
<a name="L1539" href="source/net/ipv4/ip_output.c#L1539">1539</a> 
<a name="L1540" href="source/net/ipv4/ip_output.c#L1540">1540</a>                 if (replyopts.opt.opt.<a href="ident?i=srr">srr</a>)
<a name="L1541" href="source/net/ipv4/ip_output.c#L1541">1541</a>                         <a href="ident?i=daddr">daddr</a> = replyopts.opt.opt.faddr;
<a name="L1542" href="source/net/ipv4/ip_output.c#L1542">1542</a>         }
<a name="L1543" href="source/net/ipv4/ip_output.c#L1543">1543</a> 
<a name="L1544" href="source/net/ipv4/ip_output.c#L1544">1544</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(&amp;fl4, <a href="ident?i=arg">arg</a>-&gt;bound_dev_if,
<a name="L1545" href="source/net/ipv4/ip_output.c#L1545">1545</a>                            <a href="ident?i=IP4_REPLY_MARK">IP4_REPLY_MARK</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>),
<a name="L1546" href="source/net/ipv4/ip_output.c#L1546">1546</a>                            <a href="ident?i=RT_TOS">RT_TOS</a>(<a href="ident?i=arg">arg</a>-&gt;tos),
<a name="L1547" href="source/net/ipv4/ip_output.c#L1547">1547</a>                            RT_SCOPE_UNIVERSE, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>,
<a name="L1548" href="source/net/ipv4/ip_output.c#L1548">1548</a>                            <a href="ident?i=ip_reply_arg_flowi_flags">ip_reply_arg_flowi_flags</a>(<a href="ident?i=arg">arg</a>),
<a name="L1549" href="source/net/ipv4/ip_output.c#L1549">1549</a>                            <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>,
<a name="L1550" href="source/net/ipv4/ip_output.c#L1550">1550</a>                            <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;source, <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dest">dest</a>);
<a name="L1551" href="source/net/ipv4/ip_output.c#L1551">1551</a>         <a href="ident?i=security_skb_classify_flow">security_skb_classify_flow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4));
<a name="L1552" href="source/net/ipv4/ip_output.c#L1552">1552</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L1553" href="source/net/ipv4/ip_output.c#L1553">1553</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1554" href="source/net/ipv4/ip_output.c#L1554">1554</a>                 return;
<a name="L1555" href="source/net/ipv4/ip_output.c#L1555">1555</a> 
<a name="L1556" href="source/net/ipv4/ip_output.c#L1556">1556</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;tos = <a href="ident?i=arg">arg</a>-&gt;tos;
<a name="L1557" href="source/net/ipv4/ip_output.c#L1557">1557</a> 
<a name="L1558" href="source/net/ipv4/ip_output.c#L1558">1558</a>         sk-&gt;sk_priority = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a>;
<a name="L1559" href="source/net/ipv4/ip_output.c#L1559">1559</a>         sk-&gt;sk_protocol = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L1560" href="source/net/ipv4/ip_output.c#L1560">1560</a>         sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> = <a href="ident?i=arg">arg</a>-&gt;bound_dev_if;
<a name="L1561" href="source/net/ipv4/ip_output.c#L1561">1561</a>         sk-&gt;sk_sndbuf = <a href="ident?i=sysctl_wmem_default">sysctl_wmem_default</a>;
<a name="L1562" href="source/net/ipv4/ip_output.c#L1562">1562</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_append_data">ip_append_data</a>(sk, &amp;fl4, <a href="ident?i=ip_reply_glue_bits">ip_reply_glue_bits</a>, <a href="ident?i=arg">arg</a>-&gt;iov-&gt;iov_base,
<a name="L1563" href="source/net/ipv4/ip_output.c#L1563">1563</a>                              <a href="ident?i=len">len</a>, 0, &amp;ipc, &amp;<a href="ident?i=rt">rt</a>, <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>);
<a name="L1564" href="source/net/ipv4/ip_output.c#L1564">1564</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>)) {
<a name="L1565" href="source/net/ipv4/ip_output.c#L1565">1565</a>                 <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(sk);
<a name="L1566" href="source/net/ipv4/ip_output.c#L1566">1566</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1567" href="source/net/ipv4/ip_output.c#L1567">1567</a>         }
<a name="L1568" href="source/net/ipv4/ip_output.c#L1568">1568</a> 
<a name="L1569" href="source/net/ipv4/ip_output.c#L1569">1569</a>         nskb = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_write_queue);
<a name="L1570" href="source/net/ipv4/ip_output.c#L1570">1570</a>         if (nskb) {
<a name="L1571" href="source/net/ipv4/ip_output.c#L1571">1571</a>                 if (<a href="ident?i=arg">arg</a>-&gt;csumoffset &gt;= 0)
<a name="L1572" href="source/net/ipv4/ip_output.c#L1572">1572</a>                         *((<a href="ident?i=__sum16">__sum16</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(nskb) +
<a name="L1573" href="source/net/ipv4/ip_output.c#L1573">1573</a>                           <a href="ident?i=arg">arg</a>-&gt;csumoffset) = <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=csum_add">csum_add</a>(nskb-&gt;<a href="ident?i=csum">csum</a>,
<a name="L1574" href="source/net/ipv4/ip_output.c#L1574">1574</a>                                                                 <a href="ident?i=arg">arg</a>-&gt;<a href="ident?i=csum">csum</a>));
<a name="L1575" href="source/net/ipv4/ip_output.c#L1575">1575</a>                 nskb-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L1576" href="source/net/ipv4/ip_output.c#L1576">1576</a>                 <a href="ident?i=skb_set_queue_mapping">skb_set_queue_mapping</a>(nskb, <a href="ident?i=skb_get_queue_mapping">skb_get_queue_mapping</a>(<a href="ident?i=skb">skb</a>));
<a name="L1577" href="source/net/ipv4/ip_output.c#L1577">1577</a>                 <a href="ident?i=ip_push_pending_frames">ip_push_pending_frames</a>(sk, &amp;fl4);
<a name="L1578" href="source/net/ipv4/ip_output.c#L1578">1578</a>         }
<a name="L1579" href="source/net/ipv4/ip_output.c#L1579">1579</a> <a href="ident?i=out">out</a>:
<a name="L1580" href="source/net/ipv4/ip_output.c#L1580">1580</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1581" href="source/net/ipv4/ip_output.c#L1581">1581</a> }
<a name="L1582" href="source/net/ipv4/ip_output.c#L1582">1582</a> 
<a name="L1583" href="source/net/ipv4/ip_output.c#L1583">1583</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=ip_init">ip_init</a>(void)
<a name="L1584" href="source/net/ipv4/ip_output.c#L1584">1584</a> {
<a name="L1585" href="source/net/ipv4/ip_output.c#L1585">1585</a>         <a href="ident?i=ip_rt_init">ip_rt_init</a>();
<a name="L1586" href="source/net/ipv4/ip_output.c#L1586">1586</a>         <a href="ident?i=inet_initpeers">inet_initpeers</a>();
<a name="L1587" href="source/net/ipv4/ip_output.c#L1587">1587</a> 
<a name="L1588" href="source/net/ipv4/ip_output.c#L1588">1588</a> #if defined(CONFIG_IP_MULTICAST)
<a name="L1589" href="source/net/ipv4/ip_output.c#L1589">1589</a>         <a href="ident?i=igmp_mc_init">igmp_mc_init</a>();
<a name="L1590" href="source/net/ipv4/ip_output.c#L1590">1590</a> #endif
<a name="L1591" href="source/net/ipv4/ip_output.c#L1591">1591</a> }
<a name="L1592" href="source/net/ipv4/ip_output.c#L1592">1592</a> </pre></div><p>
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
