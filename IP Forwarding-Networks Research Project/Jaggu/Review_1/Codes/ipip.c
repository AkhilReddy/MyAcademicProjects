<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ipip.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ipip.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ipip.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ipip.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ipip.c">ipip.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ipip.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ipip.c#L2">2</a> <b><i> *      Linux NET3:     IP/IP protocol decoder.</i></b>
  <a name="L3" href="source/net/ipv4/ipip.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/ipip.c#L4">4</a> <b><i> *      Authors:</i></b>
  <a name="L5" href="source/net/ipv4/ipip.c#L5">5</a> <b><i> *              Sam Lantinga (slouken@cs.ucdavis.edu)  02/01/95</i></b>
  <a name="L6" href="source/net/ipv4/ipip.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/ipip.c#L7">7</a> <b><i> *      Fixes:</i></b>
  <a name="L8" href="source/net/ipv4/ipip.c#L8">8</a> <b><i> *              Alan Cox        :       Merged and made usable non modular (its so tiny its silly as</i></b>
  <a name="L9" href="source/net/ipv4/ipip.c#L9">9</a> <b><i> *                                      a module taking up 2 pages).</i></b>
 <a name="L10" href="source/net/ipv4/ipip.c#L10">10</a> <b><i> *              Alan Cox        :       Fixed bug with 1.3.18 and IPIP not working (now needs to set skb-&gt;h.iph)</i></b>
 <a name="L11" href="source/net/ipv4/ipip.c#L11">11</a> <b><i> *                                      to keep ip_forward happy.</i></b>
 <a name="L12" href="source/net/ipv4/ipip.c#L12">12</a> <b><i> *              Alan Cox        :       More fixes for 1.3.21, and firewall fix. Maybe this will work soon 8).</i></b>
 <a name="L13" href="source/net/ipv4/ipip.c#L13">13</a> <b><i> *              Kai Schulte     :       Fixed #defines for IP_FIREWALL-&gt;FIREWALL</i></b>
 <a name="L14" href="source/net/ipv4/ipip.c#L14">14</a> <b><i> *              David Woodhouse :       Perform some basic ICMP handling.</i></b>
 <a name="L15" href="source/net/ipv4/ipip.c#L15">15</a> <b><i> *                                      IPIP Routing without decapsulation.</i></b>
 <a name="L16" href="source/net/ipv4/ipip.c#L16">16</a> <b><i> *              Carlos Picoto   :       GRE over IP support</i></b>
 <a name="L17" href="source/net/ipv4/ipip.c#L17">17</a> <b><i> *              Alexey Kuznetsov:       Reworked. Really, now it is truncated version of ipv4/ip_gre.c.</i></b>
 <a name="L18" href="source/net/ipv4/ipip.c#L18">18</a> <b><i> *                                      I do not want to merge them together.</i></b>
 <a name="L19" href="source/net/ipv4/ipip.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/ipip.c#L20">20</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
 <a name="L21" href="source/net/ipv4/ipip.c#L21">21</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L22" href="source/net/ipv4/ipip.c#L22">22</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L23" href="source/net/ipv4/ipip.c#L23">23</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L24" href="source/net/ipv4/ipip.c#L24">24</a> <b><i> *</i></b>
 <a name="L25" href="source/net/ipv4/ipip.c#L25">25</a> <b><i> */</i></b>
 <a name="L26" href="source/net/ipv4/ipip.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/ipip.c#L27">27</a> <b><i>/* tunnel.c: an IP tunnel driver</i></b>
 <a name="L28" href="source/net/ipv4/ipip.c#L28">28</a> <b><i></i></b>
 <a name="L29" href="source/net/ipv4/ipip.c#L29">29</a> <b><i>        The purpose of this driver is to provide an IP tunnel through</i></b>
 <a name="L30" href="source/net/ipv4/ipip.c#L30">30</a> <b><i>        which you can tunnel network traffic transparently across subnets.</i></b>
 <a name="L31" href="source/net/ipv4/ipip.c#L31">31</a> <b><i></i></b>
 <a name="L32" href="source/net/ipv4/ipip.c#L32">32</a> <b><i>        This was written by looking at Nick Holloway's dummy driver</i></b>
 <a name="L33" href="source/net/ipv4/ipip.c#L33">33</a> <b><i>        Thanks for the great code!</i></b>
 <a name="L34" href="source/net/ipv4/ipip.c#L34">34</a> <b><i></i></b>
 <a name="L35" href="source/net/ipv4/ipip.c#L35">35</a> <b><i>                -Sam Lantinga   (slouken@cs.ucdavis.edu)  02/01/95</i></b>
 <a name="L36" href="source/net/ipv4/ipip.c#L36">36</a> <b><i></i></b>
 <a name="L37" href="source/net/ipv4/ipip.c#L37">37</a> <b><i>        Minor tweaks:</i></b>
 <a name="L38" href="source/net/ipv4/ipip.c#L38">38</a> <b><i>                Cleaned up the code a little and added some pre-1.3.0 tweaks.</i></b>
 <a name="L39" href="source/net/ipv4/ipip.c#L39">39</a> <b><i>                dev-&gt;hard_header/hard_header_len changed to use no headers.</i></b>
 <a name="L40" href="source/net/ipv4/ipip.c#L40">40</a> <b><i>                Comments/bracketing tweaked.</i></b>
 <a name="L41" href="source/net/ipv4/ipip.c#L41">41</a> <b><i>                Made the tunnels use dev-&gt;name not tunnel: when error reporting.</i></b>
 <a name="L42" href="source/net/ipv4/ipip.c#L42">42</a> <b><i>                Added tx_dropped stat</i></b>
 <a name="L43" href="source/net/ipv4/ipip.c#L43">43</a> <b><i></i></b>
 <a name="L44" href="source/net/ipv4/ipip.c#L44">44</a> <b><i>                -Alan Cox       (alan@lxorguk.ukuu.org.uk) 21 March 95</i></b>
 <a name="L45" href="source/net/ipv4/ipip.c#L45">45</a> <b><i></i></b>
 <a name="L46" href="source/net/ipv4/ipip.c#L46">46</a> <b><i>        Reworked:</i></b>
 <a name="L47" href="source/net/ipv4/ipip.c#L47">47</a> <b><i>                Changed to tunnel to destination gateway in addition to the</i></b>
 <a name="L48" href="source/net/ipv4/ipip.c#L48">48</a> <b><i>                        tunnel's pointopoint address</i></b>
 <a name="L49" href="source/net/ipv4/ipip.c#L49">49</a> <b><i>                Almost completely rewritten</i></b>
 <a name="L50" href="source/net/ipv4/ipip.c#L50">50</a> <b><i>                Note:  There is currently no firewall or ICMP handling done.</i></b>
 <a name="L51" href="source/net/ipv4/ipip.c#L51">51</a> <b><i></i></b>
 <a name="L52" href="source/net/ipv4/ipip.c#L52">52</a> <b><i>                -Sam Lantinga   (slouken@cs.ucdavis.edu) 02/13/96</i></b>
 <a name="L53" href="source/net/ipv4/ipip.c#L53">53</a> <b><i></i></b>
 <a name="L54" href="source/net/ipv4/ipip.c#L54">54</a> <b><i>*/</i></b>
 <a name="L55" href="source/net/ipv4/ipip.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/ipip.c#L56">56</a> <b><i>/* Things I wish I had known when writing the tunnel driver:</i></b>
 <a name="L57" href="source/net/ipv4/ipip.c#L57">57</a> <b><i></i></b>
 <a name="L58" href="source/net/ipv4/ipip.c#L58">58</a> <b><i>        When the tunnel_xmit() function is called, the skb contains the</i></b>
 <a name="L59" href="source/net/ipv4/ipip.c#L59">59</a> <b><i>        packet to be sent (plus a great deal of extra info), and dev</i></b>
 <a name="L60" href="source/net/ipv4/ipip.c#L60">60</a> <b><i>        contains the tunnel device that _we_ are.</i></b>
 <a name="L61" href="source/net/ipv4/ipip.c#L61">61</a> <b><i></i></b>
 <a name="L62" href="source/net/ipv4/ipip.c#L62">62</a> <b><i>        When we are passed a packet, we are expected to fill in the</i></b>
 <a name="L63" href="source/net/ipv4/ipip.c#L63">63</a> <b><i>        source address with our source IP address.</i></b>
 <a name="L64" href="source/net/ipv4/ipip.c#L64">64</a> <b><i></i></b>
 <a name="L65" href="source/net/ipv4/ipip.c#L65">65</a> <b><i>        What is the proper way to allocate, copy and free a buffer?</i></b>
 <a name="L66" href="source/net/ipv4/ipip.c#L66">66</a> <b><i>        After you allocate it, it is a "0 length" chunk of memory</i></b>
 <a name="L67" href="source/net/ipv4/ipip.c#L67">67</a> <b><i>        starting at zero.  If you want to add headers to the buffer</i></b>
 <a name="L68" href="source/net/ipv4/ipip.c#L68">68</a> <b><i>        later, you'll have to call "skb_reserve(skb, amount)" with</i></b>
 <a name="L69" href="source/net/ipv4/ipip.c#L69">69</a> <b><i>        the amount of memory you want reserved.  Then, you call</i></b>
 <a name="L70" href="source/net/ipv4/ipip.c#L70">70</a> <b><i>        "skb_put(skb, amount)" with the amount of space you want in</i></b>
 <a name="L71" href="source/net/ipv4/ipip.c#L71">71</a> <b><i>        the buffer.  skb_put() returns a pointer to the top (#0) of</i></b>
 <a name="L72" href="source/net/ipv4/ipip.c#L72">72</a> <b><i>        that buffer.  skb-&gt;len is set to the amount of space you have</i></b>
 <a name="L73" href="source/net/ipv4/ipip.c#L73">73</a> <b><i>        "allocated" with skb_put().  You can then write up to skb-&gt;len</i></b>
 <a name="L74" href="source/net/ipv4/ipip.c#L74">74</a> <b><i>        bytes to that buffer.  If you need more, you can call skb_put()</i></b>
 <a name="L75" href="source/net/ipv4/ipip.c#L75">75</a> <b><i>        again with the additional amount of space you need.  You can</i></b>
 <a name="L76" href="source/net/ipv4/ipip.c#L76">76</a> <b><i>        find out how much more space you can allocate by calling</i></b>
 <a name="L77" href="source/net/ipv4/ipip.c#L77">77</a> <b><i>        "skb_tailroom(skb)".</i></b>
 <a name="L78" href="source/net/ipv4/ipip.c#L78">78</a> <b><i>        Now, to add header space, call "skb_push(skb, header_len)".</i></b>
 <a name="L79" href="source/net/ipv4/ipip.c#L79">79</a> <b><i>        This creates space at the beginning of the buffer and returns</i></b>
 <a name="L80" href="source/net/ipv4/ipip.c#L80">80</a> <b><i>        a pointer to this new space.  If later you need to strip a</i></b>
 <a name="L81" href="source/net/ipv4/ipip.c#L81">81</a> <b><i>        header from a buffer, call "skb_pull(skb, header_len)".</i></b>
 <a name="L82" href="source/net/ipv4/ipip.c#L82">82</a> <b><i>        skb_headroom() will return how much space is left at the top</i></b>
 <a name="L83" href="source/net/ipv4/ipip.c#L83">83</a> <b><i>        of the buffer (before the main data).  Remember, this headroom</i></b>
 <a name="L84" href="source/net/ipv4/ipip.c#L84">84</a> <b><i>        space must be reserved before the skb_put() function is called.</i></b>
 <a name="L85" href="source/net/ipv4/ipip.c#L85">85</a> <b><i>        */</i></b>
 <a name="L86" href="source/net/ipv4/ipip.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/ipip.c#L87">87</a> <b><i>/*</i></b>
 <a name="L88" href="source/net/ipv4/ipip.c#L88">88</a> <b><i>   This version of net/ipv4/ipip.c is cloned of net/ipv4/ip_gre.c</i></b>
 <a name="L89" href="source/net/ipv4/ipip.c#L89">89</a> <b><i></i></b>
 <a name="L90" href="source/net/ipv4/ipip.c#L90">90</a> <b><i>   For comments look at net/ipv4/ip_gre.c --ANK</i></b>
 <a name="L91" href="source/net/ipv4/ipip.c#L91">91</a> <b><i> */</i></b>
 <a name="L92" href="source/net/ipv4/ipip.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/ipip.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ipip.c#L94">94</a> #include &lt;linux/capability.h&gt;
 <a name="L95" href="source/net/ipv4/ipip.c#L95">95</a> #include &lt;linux/module.h&gt;
 <a name="L96" href="source/net/ipv4/ipip.c#L96">96</a> #include &lt;linux/types.h&gt;
 <a name="L97" href="source/net/ipv4/ipip.c#L97">97</a> #include &lt;linux/kernel.h&gt;
 <a name="L98" href="source/net/ipv4/ipip.c#L98">98</a> #include &lt;linux/slab.h&gt;
 <a name="L99" href="source/net/ipv4/ipip.c#L99">99</a> #include &lt;asm/uaccess.h&gt;
<a name="L100" href="source/net/ipv4/ipip.c#L100">100</a> #include &lt;linux/skbuff.h&gt;
<a name="L101" href="source/net/ipv4/ipip.c#L101">101</a> #include &lt;linux/netdevice.h&gt;
<a name="L102" href="source/net/ipv4/ipip.c#L102">102</a> #include &lt;linux/in.h&gt;
<a name="L103" href="source/net/ipv4/ipip.c#L103">103</a> #include &lt;linux/tcp.h&gt;
<a name="L104" href="source/net/ipv4/ipip.c#L104">104</a> #include &lt;linux/udp.h&gt;
<a name="L105" href="source/net/ipv4/ipip.c#L105">105</a> #include &lt;linux/if_arp.h&gt;
<a name="L106" href="source/net/ipv4/ipip.c#L106">106</a> #include &lt;linux/mroute.h&gt;
<a name="L107" href="source/net/ipv4/ipip.c#L107">107</a> #include &lt;linux/init.h&gt;
<a name="L108" href="source/net/ipv4/ipip.c#L108">108</a> #include &lt;linux/netfilter_ipv4.h&gt;
<a name="L109" href="source/net/ipv4/ipip.c#L109">109</a> #include &lt;linux/if_ether.h&gt;
<a name="L110" href="source/net/ipv4/ipip.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/ipip.c#L111">111</a> #include &lt;net/sock.h&gt;
<a name="L112" href="source/net/ipv4/ipip.c#L112">112</a> #include &lt;net/ip.h&gt;
<a name="L113" href="source/net/ipv4/ipip.c#L113">113</a> #include &lt;net/icmp.h&gt;
<a name="L114" href="source/net/ipv4/ipip.c#L114">114</a> #include &lt;net/ip_tunnels.h&gt;
<a name="L115" href="source/net/ipv4/ipip.c#L115">115</a> #include &lt;net/inet_ecn.h&gt;
<a name="L116" href="source/net/ipv4/ipip.c#L116">116</a> #include &lt;net/xfrm.h&gt;
<a name="L117" href="source/net/ipv4/ipip.c#L117">117</a> #include &lt;net/net_namespace.h&gt;
<a name="L118" href="source/net/ipv4/ipip.c#L118">118</a> #include &lt;net/netns/generic.h&gt;
<a name="L119" href="source/net/ipv4/ipip.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/ipip.c#L120">120</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=log_ecn_error">log_ecn_error</a> = <a href="ident?i=true">true</a>;
<a name="L121" href="source/net/ipv4/ipip.c#L121">121</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=log_ecn_error">log_ecn_error</a>, <a href="ident?i=bool">bool</a>, 0644);
<a name="L122" href="source/net/ipv4/ipip.c#L122">122</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=log_ecn_error">log_ecn_error</a>, <i>"Log packets received with corrupted ECN"</i>);
<a name="L123" href="source/net/ipv4/ipip.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/ipip.c#L124">124</a> static int ipip_net_id <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L125" href="source/net/ipv4/ipip.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/ipip.c#L126">126</a> static int <a href="ident?i=ipip_tunnel_init">ipip_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>);
<a name="L127" href="source/net/ipv4/ipip.c#L127">127</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> ipip_link_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L128" href="source/net/ipv4/ipip.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/ipip.c#L129">129</a> static int <a href="ident?i=ipip_err">ipip_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L130" href="source/net/ipv4/ipip.c#L130">130</a> {
<a name="L131" href="source/net/ipv4/ipip.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/ipip.c#L132">132</a> <b><i>/* All the routers (except for Linux) return only</i></b>
<a name="L133" href="source/net/ipv4/ipip.c#L133">133</a> <b><i>   8 bytes of packet payload. It means, that precise relaying of</i></b>
<a name="L134" href="source/net/ipv4/ipip.c#L134">134</a> <b><i>   ICMP in the real Internet is absolutely infeasible.</i></b>
<a name="L135" href="source/net/ipv4/ipip.c#L135">135</a> <b><i> */</i></b>
<a name="L136" href="source/net/ipv4/ipip.c#L136">136</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L137" href="source/net/ipv4/ipip.c#L137">137</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ipip_net_id);
<a name="L138" href="source/net/ipv4/ipip.c#L138">138</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L139" href="source/net/ipv4/ipip.c#L139">139</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>;
<a name="L140" href="source/net/ipv4/ipip.c#L140">140</a>         int <a href="ident?i=err">err</a>;
<a name="L141" href="source/net/ipv4/ipip.c#L141">141</a>         const int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L142" href="source/net/ipv4/ipip.c#L142">142</a>         const int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L143" href="source/net/ipv4/ipip.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/ipip.c#L144">144</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L145" href="source/net/ipv4/ipip.c#L145">145</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(itn, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=TUNNEL_NO_KEY">TUNNEL_NO_KEY</a>,
<a name="L146" href="source/net/ipv4/ipip.c#L146">146</a>                              iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, 0);
<a name="L147" href="source/net/ipv4/ipip.c#L147">147</a>         if (!<a href="ident?i=t">t</a>)
<a name="L148" href="source/net/ipv4/ipip.c#L148">148</a>                 goto <a href="ident?i=out">out</a>;
<a name="L149" href="source/net/ipv4/ipip.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/ipip.c#L150">150</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) {
<a name="L151" href="source/net/ipv4/ipip.c#L151">151</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=info">info</a>,
<a name="L152" href="source/net/ipv4/ipip.c#L152">152</a>                                  <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>, 0, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>, 0);
<a name="L153" href="source/net/ipv4/ipip.c#L153">153</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L154" href="source/net/ipv4/ipip.c#L154">154</a>                 goto <a href="ident?i=out">out</a>;
<a name="L155" href="source/net/ipv4/ipip.c#L155">155</a>         }
<a name="L156" href="source/net/ipv4/ipip.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/ipip.c#L157">157</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>) {
<a name="L158" href="source/net/ipv4/ipip.c#L158">158</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>, 0,
<a name="L159" href="source/net/ipv4/ipip.c#L159">159</a>                               <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>, 0);
<a name="L160" href="source/net/ipv4/ipip.c#L160">160</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L161" href="source/net/ipv4/ipip.c#L161">161</a>                 goto <a href="ident?i=out">out</a>;
<a name="L162" href="source/net/ipv4/ipip.c#L162">162</a>         }
<a name="L163" href="source/net/ipv4/ipip.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/ipip.c#L164">164</a>         if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> == 0)
<a name="L165" href="source/net/ipv4/ipip.c#L165">165</a>                 goto <a href="ident?i=out">out</a>;
<a name="L166" href="source/net/ipv4/ipip.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/ipip.c#L167">167</a>         <a href="ident?i=err">err</a> = 0;
<a name="L168" href="source/net/ipv4/ipip.c#L168">168</a>         if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=ttl">ttl</a> == 0 &amp;&amp; <a href="ident?i=type">type</a> == <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>)
<a name="L169" href="source/net/ipv4/ipip.c#L169">169</a>                 goto <a href="ident?i=out">out</a>;
<a name="L170" href="source/net/ipv4/ipip.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/ipip.c#L171">171</a>         if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, <a href="ident?i=t">t</a>-&gt;err_time + <a href="ident?i=IPTUNNEL_ERR_TIMEO">IPTUNNEL_ERR_TIMEO</a>))
<a name="L172" href="source/net/ipv4/ipip.c#L172">172</a>                 <a href="ident?i=t">t</a>-&gt;err_count++;
<a name="L173" href="source/net/ipv4/ipip.c#L173">173</a>         else
<a name="L174" href="source/net/ipv4/ipip.c#L174">174</a>                 <a href="ident?i=t">t</a>-&gt;err_count = 1;
<a name="L175" href="source/net/ipv4/ipip.c#L175">175</a>         <a href="ident?i=t">t</a>-&gt;err_time = <a href="ident?i=jiffies">jiffies</a>;
<a name="L176" href="source/net/ipv4/ipip.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/ipip.c#L177">177</a> <a href="ident?i=out">out</a>:
<a name="L178" href="source/net/ipv4/ipip.c#L178">178</a>         return <a href="ident?i=err">err</a>;
<a name="L179" href="source/net/ipv4/ipip.c#L179">179</a> }
<a name="L180" href="source/net/ipv4/ipip.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/ipip.c#L181">181</a> static const struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> <a href="ident?i=tpi">tpi</a> = {
<a name="L182" href="source/net/ipv4/ipip.c#L182">182</a>         <b><i>/* no tunnel info required for ipip. */</i></b>
<a name="L183" href="source/net/ipv4/ipip.c#L183">183</a>         .<a href="ident?i=proto">proto</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>),
<a name="L184" href="source/net/ipv4/ipip.c#L184">184</a> };
<a name="L185" href="source/net/ipv4/ipip.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/ipip.c#L186">186</a> static int <a href="ident?i=ipip_rcv">ipip_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L187" href="source/net/ipv4/ipip.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/ipip.c#L188">188</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L189" href="source/net/ipv4/ipip.c#L189">189</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ipip_net_id);
<a name="L190" href="source/net/ipv4/ipip.c#L190">190</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel;
<a name="L191" href="source/net/ipv4/ipip.c#L191">191</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L192" href="source/net/ipv4/ipip.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/ipip.c#L193">193</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L194" href="source/net/ipv4/ipip.c#L194">194</a>         tunnel = <a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(itn, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=TUNNEL_NO_KEY">TUNNEL_NO_KEY</a>,
<a name="L195" href="source/net/ipv4/ipip.c#L195">195</a>                         iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, 0);
<a name="L196" href="source/net/ipv4/ipip.c#L196">196</a>         if (tunnel) {
<a name="L197" href="source/net/ipv4/ipip.c#L197">197</a>                 if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
<a name="L198" href="source/net/ipv4/ipip.c#L198">198</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L199" href="source/net/ipv4/ipip.c#L199">199</a>                 if (<a href="ident?i=iptunnel_pull_header">iptunnel_pull_header</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=tpi">tpi</a>.<a href="ident?i=proto">proto</a>))
<a name="L200" href="source/net/ipv4/ipip.c#L200">200</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L201" href="source/net/ipv4/ipip.c#L201">201</a>                 return <a href="ident?i=ip_tunnel_rcv">ip_tunnel_rcv</a>(tunnel, <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tpi">tpi</a>, <a href="ident?i=log_ecn_error">log_ecn_error</a>);
<a name="L202" href="source/net/ipv4/ipip.c#L202">202</a>         }
<a name="L203" href="source/net/ipv4/ipip.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ipip.c#L204">204</a>         return -1;
<a name="L205" href="source/net/ipv4/ipip.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/ipip.c#L206">206</a> <a href="ident?i=drop">drop</a>:
<a name="L207" href="source/net/ipv4/ipip.c#L207">207</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L208" href="source/net/ipv4/ipip.c#L208">208</a>         return 0;
<a name="L209" href="source/net/ipv4/ipip.c#L209">209</a> }
<a name="L210" href="source/net/ipv4/ipip.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/ipip.c#L211">211</a> <b><i>/*</i></b>
<a name="L212" href="source/net/ipv4/ipip.c#L212">212</a> <b><i> *      This function assumes it is being called from dev_queue_xmit()</i></b>
<a name="L213" href="source/net/ipv4/ipip.c#L213">213</a> <b><i> *      and that skb is filled properly by that function.</i></b>
<a name="L214" href="source/net/ipv4/ipip.c#L214">214</a> <b><i> */</i></b>
<a name="L215" href="source/net/ipv4/ipip.c#L215">215</a> static <a href="ident?i=netdev_tx_t">netdev_tx_t</a> <a href="ident?i=ipip_tunnel_xmit">ipip_tunnel_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L216" href="source/net/ipv4/ipip.c#L216">216</a> {
<a name="L217" href="source/net/ipv4/ipip.c#L217">217</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L218" href="source/net/ipv4/ipip.c#L218">218</a>         const struct <a href="ident?i=iphdr">iphdr</a>  *tiph = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L219" href="source/net/ipv4/ipip.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/ipip.c#L220">220</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)))
<a name="L221" href="source/net/ipv4/ipip.c#L221">221</a>                 goto <a href="ident?i=tx_error">tx_error</a>;
<a name="L222" href="source/net/ipv4/ipip.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/ipip.c#L223">223</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=iptunnel_handle_offloads">iptunnel_handle_offloads</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=false">false</a>, SKB_GSO_IPIP);
<a name="L224" href="source/net/ipv4/ipip.c#L224">224</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=skb">skb</a>))
<a name="L225" href="source/net/ipv4/ipip.c#L225">225</a>                 goto <a href="ident?i=out">out</a>;
<a name="L226" href="source/net/ipv4/ipip.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/ipip.c#L227">227</a>         <a href="ident?i=skb_set_inner_ipproto">skb_set_inner_ipproto</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>);
<a name="L228" href="source/net/ipv4/ipip.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/ipip.c#L229">229</a>         <a href="ident?i=ip_tunnel_xmit">ip_tunnel_xmit</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, tiph, tiph-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L230" href="source/net/ipv4/ipip.c#L230">230</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L231" href="source/net/ipv4/ipip.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/ipip.c#L232">232</a> <a href="ident?i=tx_error">tx_error</a>:
<a name="L233" href="source/net/ipv4/ipip.c#L233">233</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L234" href="source/net/ipv4/ipip.c#L234">234</a> <a href="ident?i=out">out</a>:
<a name="L235" href="source/net/ipv4/ipip.c#L235">235</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_errors++;
<a name="L236" href="source/net/ipv4/ipip.c#L236">236</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L237" href="source/net/ipv4/ipip.c#L237">237</a> }
<a name="L238" href="source/net/ipv4/ipip.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/ipip.c#L239">239</a> static int
<a name="L240" href="source/net/ipv4/ipip.c#L240">240</a> <a href="ident?i=ipip_tunnel_ioctl">ipip_tunnel_ioctl</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=ifreq">ifreq</a> *ifr, int <a href="ident?i=cmd">cmd</a>)
<a name="L241" href="source/net/ipv4/ipip.c#L241">241</a> {
<a name="L242" href="source/net/ipv4/ipip.c#L242">242</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L243" href="source/net/ipv4/ipip.c#L243">243</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L244" href="source/net/ipv4/ipip.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/ipip.c#L245">245</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=p">p</a>, ifr-&gt;ifr_ifru.ifru_data, sizeof(<a href="ident?i=p">p</a>)))
<a name="L246" href="source/net/ipv4/ipip.c#L246">246</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L247" href="source/net/ipv4/ipip.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/ipip.c#L248">248</a>         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCADDTUNNEL">SIOCADDTUNNEL</a> || <a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCCHGTUNNEL">SIOCCHGTUNNEL</a>) {
<a name="L249" href="source/net/ipv4/ipip.c#L249">249</a>                 if (<a href="ident?i=p">p</a>.iph.<a href="ident?i=version">version</a> != 4 || <a href="ident?i=p">p</a>.iph.<a href="ident?i=protocol">protocol</a> != <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a> ||
<a name="L250" href="source/net/ipv4/ipip.c#L250">250</a>                     <a href="ident?i=p">p</a>.iph.ihl != 5 || (<a href="ident?i=p">p</a>.iph.frag_off&amp;<a href="ident?i=htons">htons</a>(~IP_DF)))
<a name="L251" href="source/net/ipv4/ipip.c#L251">251</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L252" href="source/net/ipv4/ipip.c#L252">252</a>         }
<a name="L253" href="source/net/ipv4/ipip.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/ipip.c#L254">254</a>         <a href="ident?i=p">p</a>.i_key = <a href="ident?i=p">p</a>.o_key = <a href="ident?i=p">p</a>.i_flags = <a href="ident?i=p">p</a>.o_flags = 0;
<a name="L255" href="source/net/ipv4/ipip.c#L255">255</a>         if (<a href="ident?i=p">p</a>.iph.<a href="ident?i=ttl">ttl</a>)
<a name="L256" href="source/net/ipv4/ipip.c#L256">256</a>                 <a href="ident?i=p">p</a>.iph.frag_off |= <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L257" href="source/net/ipv4/ipip.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/ipip.c#L258">258</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_ioctl">ip_tunnel_ioctl</a>(<a href="ident?i=dev">dev</a>, &amp;<a href="ident?i=p">p</a>, <a href="ident?i=cmd">cmd</a>);
<a name="L259" href="source/net/ipv4/ipip.c#L259">259</a>         if (<a href="ident?i=err">err</a>)
<a name="L260" href="source/net/ipv4/ipip.c#L260">260</a>                 return <a href="ident?i=err">err</a>;
<a name="L261" href="source/net/ipv4/ipip.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/ipip.c#L262">262</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(ifr-&gt;ifr_ifru.ifru_data, &amp;<a href="ident?i=p">p</a>, sizeof(<a href="ident?i=p">p</a>)))
<a name="L263" href="source/net/ipv4/ipip.c#L263">263</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L264" href="source/net/ipv4/ipip.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/ipip.c#L265">265</a>         return 0;
<a name="L266" href="source/net/ipv4/ipip.c#L266">266</a> }
<a name="L267" href="source/net/ipv4/ipip.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/ipip.c#L268">268</a> static const struct <a href="ident?i=net_device_ops">net_device_ops</a> <a href="ident?i=ipip_netdev_ops">ipip_netdev_ops</a> = {
<a name="L269" href="source/net/ipv4/ipip.c#L269">269</a>         .ndo_init       = <a href="ident?i=ipip_tunnel_init">ipip_tunnel_init</a>,
<a name="L270" href="source/net/ipv4/ipip.c#L270">270</a>         .ndo_uninit     = <a href="ident?i=ip_tunnel_uninit">ip_tunnel_uninit</a>,
<a name="L271" href="source/net/ipv4/ipip.c#L271">271</a>         .ndo_start_xmit = <a href="ident?i=ipip_tunnel_xmit">ipip_tunnel_xmit</a>,
<a name="L272" href="source/net/ipv4/ipip.c#L272">272</a>         .ndo_do_ioctl   = <a href="ident?i=ipip_tunnel_ioctl">ipip_tunnel_ioctl</a>,
<a name="L273" href="source/net/ipv4/ipip.c#L273">273</a>         .ndo_change_mtu = <a href="ident?i=ip_tunnel_change_mtu">ip_tunnel_change_mtu</a>,
<a name="L274" href="source/net/ipv4/ipip.c#L274">274</a>         .ndo_get_stats64 = <a href="ident?i=ip_tunnel_get_stats64">ip_tunnel_get_stats64</a>,
<a name="L275" href="source/net/ipv4/ipip.c#L275">275</a>         .ndo_get_iflink = <a href="ident?i=ip_tunnel_get_iflink">ip_tunnel_get_iflink</a>,
<a name="L276" href="source/net/ipv4/ipip.c#L276">276</a> };
<a name="L277" href="source/net/ipv4/ipip.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/ipip.c#L278">278</a> #define <a href="ident?i=IPIP_FEATURES">IPIP_FEATURES</a> (<a href="ident?i=NETIF_F_SG">NETIF_F_SG</a> |             \
<a name="L279" href="source/net/ipv4/ipip.c#L279">279</a>                        <a href="ident?i=NETIF_F_FRAGLIST">NETIF_F_FRAGLIST</a> |       \
<a name="L280" href="source/net/ipv4/ipip.c#L280">280</a>                        <a href="ident?i=NETIF_F_HIGHDMA">NETIF_F_HIGHDMA</a> |        \
<a name="L281" href="source/net/ipv4/ipip.c#L281">281</a>                        <a href="ident?i=NETIF_F_GSO_SOFTWARE">NETIF_F_GSO_SOFTWARE</a> |   \
<a name="L282" href="source/net/ipv4/ipip.c#L282">282</a>                        <a href="ident?i=NETIF_F_HW_CSUM">NETIF_F_HW_CSUM</a>)
<a name="L283" href="source/net/ipv4/ipip.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/ipip.c#L284">284</a> static void <a href="ident?i=ipip_tunnel_setup">ipip_tunnel_setup</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L285" href="source/net/ipv4/ipip.c#L285">285</a> {
<a name="L286" href="source/net/ipv4/ipip.c#L286">286</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>         = &amp;<a href="ident?i=ipip_netdev_ops">ipip_netdev_ops</a>;
<a name="L287" href="source/net/ipv4/ipip.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/ipip.c#L288">288</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>               = <a href="ident?i=ARPHRD_TUNNEL">ARPHRD_TUNNEL</a>;
<a name="L289" href="source/net/ipv4/ipip.c#L289">289</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>              = <a href="ident?i=IFF_NOARP">IFF_NOARP</a>;
<a name="L290" href="source/net/ipv4/ipip.c#L290">290</a>         <a href="ident?i=dev">dev</a>-&gt;addr_len           = 4;
<a name="L291" href="source/net/ipv4/ipip.c#L291">291</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>           |= <a href="ident?i=NETIF_F_LLTX">NETIF_F_LLTX</a>;
<a name="L292" href="source/net/ipv4/ipip.c#L292">292</a>         <a href="ident?i=netif_keep_dst">netif_keep_dst</a>(<a href="ident?i=dev">dev</a>);
<a name="L293" href="source/net/ipv4/ipip.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/ipip.c#L294">294</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>           |= <a href="ident?i=IPIP_FEATURES">IPIP_FEATURES</a>;
<a name="L295" href="source/net/ipv4/ipip.c#L295">295</a>         <a href="ident?i=dev">dev</a>-&gt;hw_features        |= <a href="ident?i=IPIP_FEATURES">IPIP_FEATURES</a>;
<a name="L296" href="source/net/ipv4/ipip.c#L296">296</a>         <a href="ident?i=ip_tunnel_setup">ip_tunnel_setup</a>(<a href="ident?i=dev">dev</a>, ipip_net_id);
<a name="L297" href="source/net/ipv4/ipip.c#L297">297</a> }
<a name="L298" href="source/net/ipv4/ipip.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/ipip.c#L299">299</a> static int <a href="ident?i=ipip_tunnel_init">ipip_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L300" href="source/net/ipv4/ipip.c#L300">300</a> {
<a name="L301" href="source/net/ipv4/ipip.c#L301">301</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L302" href="source/net/ipv4/ipip.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/ipip.c#L303">303</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;dev_addr, &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a>, 4);
<a name="L304" href="source/net/ipv4/ipip.c#L304">304</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>, 4);
<a name="L305" href="source/net/ipv4/ipip.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/ipip.c#L306">306</a>         tunnel-&gt;tun_hlen = 0;
<a name="L307" href="source/net/ipv4/ipip.c#L307">307</a>         tunnel-&gt;hlen = tunnel-&gt;tun_hlen + tunnel-&gt;encap_hlen;
<a name="L308" href="source/net/ipv4/ipip.c#L308">308</a>         tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L309" href="source/net/ipv4/ipip.c#L309">309</a>         return <a href="ident?i=ip_tunnel_init">ip_tunnel_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L310" href="source/net/ipv4/ipip.c#L310">310</a> }
<a name="L311" href="source/net/ipv4/ipip.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/ipip.c#L312">312</a> static void <a href="ident?i=ipip_netlink_parms">ipip_netlink_parms</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[],
<a name="L313" href="source/net/ipv4/ipip.c#L313">313</a>                                struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>)
<a name="L314" href="source/net/ipv4/ipip.c#L314">314</a> {
<a name="L315" href="source/net/ipv4/ipip.c#L315">315</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=parms">parms</a>, 0, sizeof(*<a href="ident?i=parms">parms</a>));
<a name="L316" href="source/net/ipv4/ipip.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/ipip.c#L317">317</a>         <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=version">version</a> = 4;
<a name="L318" href="source/net/ipv4/ipip.c#L318">318</a>         <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
<a name="L319" href="source/net/ipv4/ipip.c#L319">319</a>         <a href="ident?i=parms">parms</a>-&gt;iph.ihl = 5;
<a name="L320" href="source/net/ipv4/ipip.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/ipip.c#L321">321</a>         if (!<a href="ident?i=data">data</a>)
<a name="L322" href="source/net/ipv4/ipip.c#L322">322</a>                 return;
<a name="L323" href="source/net/ipv4/ipip.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/ipip.c#L324">324</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_LINK])
<a name="L325" href="source/net/ipv4/ipip.c#L325">325</a>                 <a href="ident?i=parms">parms</a>-&gt;<a href="ident?i=link">link</a> = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_LINK]);
<a name="L326" href="source/net/ipv4/ipip.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/ipip.c#L327">327</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_LOCAL])
<a name="L328" href="source/net/ipv4/ipip.c#L328">328</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_LOCAL]);
<a name="L329" href="source/net/ipv4/ipip.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/ipip.c#L330">330</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_REMOTE])
<a name="L331" href="source/net/ipv4/ipip.c#L331">331</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_REMOTE]);
<a name="L332" href="source/net/ipv4/ipip.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/ipip.c#L333">333</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_TTL]) {
<a name="L334" href="source/net/ipv4/ipip.c#L334">334</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=ttl">ttl</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_TTL]);
<a name="L335" href="source/net/ipv4/ipip.c#L335">335</a>                 if (<a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=ttl">ttl</a>)
<a name="L336" href="source/net/ipv4/ipip.c#L336">336</a>                         <a href="ident?i=parms">parms</a>-&gt;iph.frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L337" href="source/net/ipv4/ipip.c#L337">337</a>         }
<a name="L338" href="source/net/ipv4/ipip.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/ipip.c#L339">339</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_TOS])
<a name="L340" href="source/net/ipv4/ipip.c#L340">340</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.tos = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_TOS]);
<a name="L341" href="source/net/ipv4/ipip.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/ipip.c#L342">342</a>         if (!<a href="ident?i=data">data</a>[IFLA_IPTUN_PMTUDISC] || <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_PMTUDISC]))
<a name="L343" href="source/net/ipv4/ipip.c#L343">343</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L344" href="source/net/ipv4/ipip.c#L344">344</a> }
<a name="L345" href="source/net/ipv4/ipip.c#L345">345</a> 
<a name="L346" href="source/net/ipv4/ipip.c#L346">346</a> <b><i>/* This function returns true when ENCAP attributes are present in the nl msg */</i></b>
<a name="L347" href="source/net/ipv4/ipip.c#L347">347</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ipip_netlink_encap_parms">ipip_netlink_encap_parms</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[],
<a name="L348" href="source/net/ipv4/ipip.c#L348">348</a>                                      struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *ipencap)
<a name="L349" href="source/net/ipv4/ipip.c#L349">349</a> {
<a name="L350" href="source/net/ipv4/ipip.c#L350">350</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L351" href="source/net/ipv4/ipip.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/ipip.c#L352">352</a>         <a href="ident?i=memset">memset</a>(ipencap, 0, sizeof(*ipencap));
<a name="L353" href="source/net/ipv4/ipip.c#L353">353</a> 
<a name="L354" href="source/net/ipv4/ipip.c#L354">354</a>         if (!<a href="ident?i=data">data</a>)
<a name="L355" href="source/net/ipv4/ipip.c#L355">355</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L356" href="source/net/ipv4/ipip.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/ipip.c#L357">357</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_TYPE]) {
<a name="L358" href="source/net/ipv4/ipip.c#L358">358</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L359" href="source/net/ipv4/ipip.c#L359">359</a>                 ipencap-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=nla_get_u16">nla_get_u16</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_TYPE]);
<a name="L360" href="source/net/ipv4/ipip.c#L360">360</a>         }
<a name="L361" href="source/net/ipv4/ipip.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/ipip.c#L362">362</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_FLAGS]) {
<a name="L363" href="source/net/ipv4/ipip.c#L363">363</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L364" href="source/net/ipv4/ipip.c#L364">364</a>                 ipencap-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=nla_get_u16">nla_get_u16</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_FLAGS]);
<a name="L365" href="source/net/ipv4/ipip.c#L365">365</a>         }
<a name="L366" href="source/net/ipv4/ipip.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/ipip.c#L367">367</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_SPORT]) {
<a name="L368" href="source/net/ipv4/ipip.c#L368">368</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L369" href="source/net/ipv4/ipip.c#L369">369</a>                 ipencap-&gt;sport = <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_SPORT]);
<a name="L370" href="source/net/ipv4/ipip.c#L370">370</a>         }
<a name="L371" href="source/net/ipv4/ipip.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/ipip.c#L372">372</a>         if (<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_DPORT]) {
<a name="L373" href="source/net/ipv4/ipip.c#L373">373</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L374" href="source/net/ipv4/ipip.c#L374">374</a>                 ipencap-&gt;dport = <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_IPTUN_ENCAP_DPORT]);
<a name="L375" href="source/net/ipv4/ipip.c#L375">375</a>         }
<a name="L376" href="source/net/ipv4/ipip.c#L376">376</a> 
<a name="L377" href="source/net/ipv4/ipip.c#L377">377</a>         return <a href="ident?i=ret">ret</a>;
<a name="L378" href="source/net/ipv4/ipip.c#L378">378</a> }
<a name="L379" href="source/net/ipv4/ipip.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/ipip.c#L380">380</a> static int <a href="ident?i=ipip_newlink">ipip_newlink</a>(struct <a href="ident?i=net">net</a> *src_net, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L381" href="source/net/ipv4/ipip.c#L381">381</a>                         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L382" href="source/net/ipv4/ipip.c#L382">382</a> {
<a name="L383" href="source/net/ipv4/ipip.c#L383">383</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L384" href="source/net/ipv4/ipip.c#L384">384</a>         struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> ipencap;
<a name="L385" href="source/net/ipv4/ipip.c#L385">385</a> 
<a name="L386" href="source/net/ipv4/ipip.c#L386">386</a>         if (<a href="ident?i=ipip_netlink_encap_parms">ipip_netlink_encap_parms</a>(<a href="ident?i=data">data</a>, &amp;ipencap)) {
<a name="L387" href="source/net/ipv4/ipip.c#L387">387</a>                 struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L388" href="source/net/ipv4/ipip.c#L388">388</a>                 int <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_encap_setup">ip_tunnel_encap_setup</a>(<a href="ident?i=t">t</a>, &amp;ipencap);
<a name="L389" href="source/net/ipv4/ipip.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/ipip.c#L390">390</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L391" href="source/net/ipv4/ipip.c#L391">391</a>                         return <a href="ident?i=err">err</a>;
<a name="L392" href="source/net/ipv4/ipip.c#L392">392</a>         }
<a name="L393" href="source/net/ipv4/ipip.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/ipip.c#L394">394</a>         <a href="ident?i=ipip_netlink_parms">ipip_netlink_parms</a>(<a href="ident?i=data">data</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L395" href="source/net/ipv4/ipip.c#L395">395</a>         return <a href="ident?i=ip_tunnel_newlink">ip_tunnel_newlink</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L396" href="source/net/ipv4/ipip.c#L396">396</a> }
<a name="L397" href="source/net/ipv4/ipip.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/ipip.c#L398">398</a> static int <a href="ident?i=ipip_changelink">ipip_changelink</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L399" href="source/net/ipv4/ipip.c#L399">399</a>                            struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L400" href="source/net/ipv4/ipip.c#L400">400</a> {
<a name="L401" href="source/net/ipv4/ipip.c#L401">401</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L402" href="source/net/ipv4/ipip.c#L402">402</a>         struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> ipencap;
<a name="L403" href="source/net/ipv4/ipip.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/ipip.c#L404">404</a>         if (<a href="ident?i=ipip_netlink_encap_parms">ipip_netlink_encap_parms</a>(<a href="ident?i=data">data</a>, &amp;ipencap)) {
<a name="L405" href="source/net/ipv4/ipip.c#L405">405</a>                 struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L406" href="source/net/ipv4/ipip.c#L406">406</a>                 int <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_encap_setup">ip_tunnel_encap_setup</a>(<a href="ident?i=t">t</a>, &amp;ipencap);
<a name="L407" href="source/net/ipv4/ipip.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/ipip.c#L408">408</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L409" href="source/net/ipv4/ipip.c#L409">409</a>                         return <a href="ident?i=err">err</a>;
<a name="L410" href="source/net/ipv4/ipip.c#L410">410</a>         }
<a name="L411" href="source/net/ipv4/ipip.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/ipip.c#L412">412</a>         <a href="ident?i=ipip_netlink_parms">ipip_netlink_parms</a>(<a href="ident?i=data">data</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L413" href="source/net/ipv4/ipip.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/ipip.c#L414">414</a>         if (((<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>) &amp;&amp; !<a href="ident?i=p">p</a>.iph.<a href="ident?i=daddr">daddr</a>) ||
<a name="L415" href="source/net/ipv4/ipip.c#L415">415</a>             (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>) &amp;&amp; <a href="ident?i=p">p</a>.iph.<a href="ident?i=daddr">daddr</a>))
<a name="L416" href="source/net/ipv4/ipip.c#L416">416</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L417" href="source/net/ipv4/ipip.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/ipip.c#L418">418</a>         return <a href="ident?i=ip_tunnel_changelink">ip_tunnel_changelink</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L419" href="source/net/ipv4/ipip.c#L419">419</a> }
<a name="L420" href="source/net/ipv4/ipip.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/ipip.c#L421">421</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=ipip_get_size">ipip_get_size</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L422" href="source/net/ipv4/ipip.c#L422">422</a> {
<a name="L423" href="source/net/ipv4/ipip.c#L423">423</a>         return
<a name="L424" href="source/net/ipv4/ipip.c#L424">424</a>                 <b><i>/* IFLA_IPTUN_LINK */</i></b>
<a name="L425" href="source/net/ipv4/ipip.c#L425">425</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L426" href="source/net/ipv4/ipip.c#L426">426</a>                 <b><i>/* IFLA_IPTUN_LOCAL */</i></b>
<a name="L427" href="source/net/ipv4/ipip.c#L427">427</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L428" href="source/net/ipv4/ipip.c#L428">428</a>                 <b><i>/* IFLA_IPTUN_REMOTE */</i></b>
<a name="L429" href="source/net/ipv4/ipip.c#L429">429</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L430" href="source/net/ipv4/ipip.c#L430">430</a>                 <b><i>/* IFLA_IPTUN_TTL */</i></b>
<a name="L431" href="source/net/ipv4/ipip.c#L431">431</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(1) +
<a name="L432" href="source/net/ipv4/ipip.c#L432">432</a>                 <b><i>/* IFLA_IPTUN_TOS */</i></b>
<a name="L433" href="source/net/ipv4/ipip.c#L433">433</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(1) +
<a name="L434" href="source/net/ipv4/ipip.c#L434">434</a>                 <b><i>/* IFLA_IPTUN_PMTUDISC */</i></b>
<a name="L435" href="source/net/ipv4/ipip.c#L435">435</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(1) +
<a name="L436" href="source/net/ipv4/ipip.c#L436">436</a>                 <b><i>/* IFLA_IPTUN_ENCAP_TYPE */</i></b>
<a name="L437" href="source/net/ipv4/ipip.c#L437">437</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L438" href="source/net/ipv4/ipip.c#L438">438</a>                 <b><i>/* IFLA_IPTUN_ENCAP_FLAGS */</i></b>
<a name="L439" href="source/net/ipv4/ipip.c#L439">439</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L440" href="source/net/ipv4/ipip.c#L440">440</a>                 <b><i>/* IFLA_IPTUN_ENCAP_SPORT */</i></b>
<a name="L441" href="source/net/ipv4/ipip.c#L441">441</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L442" href="source/net/ipv4/ipip.c#L442">442</a>                 <b><i>/* IFLA_IPTUN_ENCAP_DPORT */</i></b>
<a name="L443" href="source/net/ipv4/ipip.c#L443">443</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L444" href="source/net/ipv4/ipip.c#L444">444</a>                 0;
<a name="L445" href="source/net/ipv4/ipip.c#L445">445</a> }
<a name="L446" href="source/net/ipv4/ipip.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/ipip.c#L447">447</a> static int <a href="ident?i=ipip_fill_info">ipip_fill_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L448" href="source/net/ipv4/ipip.c#L448">448</a> {
<a name="L449" href="source/net/ipv4/ipip.c#L449">449</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L450" href="source/net/ipv4/ipip.c#L450">450</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parm">parm</a> = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>;
<a name="L451" href="source/net/ipv4/ipip.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/ipip.c#L452">452</a>         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_LINK, <a href="ident?i=parm">parm</a>-&gt;<a href="ident?i=link">link</a>) ||
<a name="L453" href="source/net/ipv4/ipip.c#L453">453</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_LOCAL, <a href="ident?i=parm">parm</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>) ||
<a name="L454" href="source/net/ipv4/ipip.c#L454">454</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_REMOTE, <a href="ident?i=parm">parm</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>) ||
<a name="L455" href="source/net/ipv4/ipip.c#L455">455</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_TTL, <a href="ident?i=parm">parm</a>-&gt;iph.<a href="ident?i=ttl">ttl</a>) ||
<a name="L456" href="source/net/ipv4/ipip.c#L456">456</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_TOS, <a href="ident?i=parm">parm</a>-&gt;iph.tos) ||
<a name="L457" href="source/net/ipv4/ipip.c#L457">457</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_PMTUDISC,
<a name="L458" href="source/net/ipv4/ipip.c#L458">458</a>                        !!(<a href="ident?i=parm">parm</a>-&gt;iph.frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>))))
<a name="L459" href="source/net/ipv4/ipip.c#L459">459</a>                 goto nla_put_failure;
<a name="L460" href="source/net/ipv4/ipip.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/ipip.c#L461">461</a>         if (<a href="ident?i=nla_put_u16">nla_put_u16</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_ENCAP_TYPE,
<a name="L462" href="source/net/ipv4/ipip.c#L462">462</a>                         tunnel-&gt;encap.<a href="ident?i=type">type</a>) ||
<a name="L463" href="source/net/ipv4/ipip.c#L463">463</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_ENCAP_SPORT,
<a name="L464" href="source/net/ipv4/ipip.c#L464">464</a>                          tunnel-&gt;encap.sport) ||
<a name="L465" href="source/net/ipv4/ipip.c#L465">465</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_ENCAP_DPORT,
<a name="L466" href="source/net/ipv4/ipip.c#L466">466</a>                          tunnel-&gt;encap.dport) ||
<a name="L467" href="source/net/ipv4/ipip.c#L467">467</a>             <a href="ident?i=nla_put_u16">nla_put_u16</a>(<a href="ident?i=skb">skb</a>, IFLA_IPTUN_ENCAP_FLAGS,
<a name="L468" href="source/net/ipv4/ipip.c#L468">468</a>                         tunnel-&gt;encap.<a href="ident?i=flags">flags</a>))
<a name="L469" href="source/net/ipv4/ipip.c#L469">469</a>                 goto nla_put_failure;
<a name="L470" href="source/net/ipv4/ipip.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/ipip.c#L471">471</a>         return 0;
<a name="L472" href="source/net/ipv4/ipip.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/ipip.c#L473">473</a> nla_put_failure:
<a name="L474" href="source/net/ipv4/ipip.c#L474">474</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L475" href="source/net/ipv4/ipip.c#L475">475</a> }
<a name="L476" href="source/net/ipv4/ipip.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/ipip.c#L477">477</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=ipip_policy">ipip_policy</a>[<a href="ident?i=IFLA_IPTUN_MAX">IFLA_IPTUN_MAX</a> + 1] = {
<a name="L478" href="source/net/ipv4/ipip.c#L478">478</a>         [IFLA_IPTUN_LINK]               = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L479" href="source/net/ipv4/ipip.c#L479">479</a>         [IFLA_IPTUN_LOCAL]              = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L480" href="source/net/ipv4/ipip.c#L480">480</a>         [IFLA_IPTUN_REMOTE]             = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L481" href="source/net/ipv4/ipip.c#L481">481</a>         [IFLA_IPTUN_TTL]                = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L482" href="source/net/ipv4/ipip.c#L482">482</a>         [IFLA_IPTUN_TOS]                = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L483" href="source/net/ipv4/ipip.c#L483">483</a>         [IFLA_IPTUN_PMTUDISC]           = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L484" href="source/net/ipv4/ipip.c#L484">484</a>         [IFLA_IPTUN_ENCAP_TYPE]         = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L485" href="source/net/ipv4/ipip.c#L485">485</a>         [IFLA_IPTUN_ENCAP_FLAGS]        = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L486" href="source/net/ipv4/ipip.c#L486">486</a>         [IFLA_IPTUN_ENCAP_SPORT]        = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L487" href="source/net/ipv4/ipip.c#L487">487</a>         [IFLA_IPTUN_ENCAP_DPORT]        = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L488" href="source/net/ipv4/ipip.c#L488">488</a> };
<a name="L489" href="source/net/ipv4/ipip.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/ipip.c#L490">490</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> ipip_link_ops <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L491" href="source/net/ipv4/ipip.c#L491">491</a>         .kind           = <i>"ipip"</i>,
<a name="L492" href="source/net/ipv4/ipip.c#L492">492</a>         .maxtype        = <a href="ident?i=IFLA_IPTUN_MAX">IFLA_IPTUN_MAX</a>,
<a name="L493" href="source/net/ipv4/ipip.c#L493">493</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=ipip_policy">ipip_policy</a>,
<a name="L494" href="source/net/ipv4/ipip.c#L494">494</a>         .priv_size      = sizeof(struct <a href="ident?i=ip_tunnel">ip_tunnel</a>),
<a name="L495" href="source/net/ipv4/ipip.c#L495">495</a>         .<a href="ident?i=setup">setup</a>          = <a href="ident?i=ipip_tunnel_setup">ipip_tunnel_setup</a>,
<a name="L496" href="source/net/ipv4/ipip.c#L496">496</a>         .newlink        = <a href="ident?i=ipip_newlink">ipip_newlink</a>,
<a name="L497" href="source/net/ipv4/ipip.c#L497">497</a>         .changelink     = <a href="ident?i=ipip_changelink">ipip_changelink</a>,
<a name="L498" href="source/net/ipv4/ipip.c#L498">498</a>         .dellink        = <a href="ident?i=ip_tunnel_dellink">ip_tunnel_dellink</a>,
<a name="L499" href="source/net/ipv4/ipip.c#L499">499</a>         .<a href="ident?i=get_size">get_size</a>       = <a href="ident?i=ipip_get_size">ipip_get_size</a>,
<a name="L500" href="source/net/ipv4/ipip.c#L500">500</a>         .fill_info      = <a href="ident?i=ipip_fill_info">ipip_fill_info</a>,
<a name="L501" href="source/net/ipv4/ipip.c#L501">501</a>         .get_link_net   = <a href="ident?i=ip_tunnel_get_link_net">ip_tunnel_get_link_net</a>,
<a name="L502" href="source/net/ipv4/ipip.c#L502">502</a> };
<a name="L503" href="source/net/ipv4/ipip.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/ipip.c#L504">504</a> static struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> ipip_handler <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L505" href="source/net/ipv4/ipip.c#L505">505</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=ipip_rcv">ipip_rcv</a>,
<a name="L506" href="source/net/ipv4/ipip.c#L506">506</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=ipip_err">ipip_err</a>,
<a name="L507" href="source/net/ipv4/ipip.c#L507">507</a>         .<a href="ident?i=priority">priority</a>       =       1,
<a name="L508" href="source/net/ipv4/ipip.c#L508">508</a> };
<a name="L509" href="source/net/ipv4/ipip.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/ipip.c#L510">510</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipip_init_net">ipip_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L511" href="source/net/ipv4/ipip.c#L511">511</a> {
<a name="L512" href="source/net/ipv4/ipip.c#L512">512</a>         return <a href="ident?i=ip_tunnel_init_net">ip_tunnel_init_net</a>(<a href="ident?i=net">net</a>, ipip_net_id, &amp;ipip_link_ops, <i>"tunl0"</i>);
<a name="L513" href="source/net/ipv4/ipip.c#L513">513</a> }
<a name="L514" href="source/net/ipv4/ipip.c#L514">514</a> 
<a name="L515" href="source/net/ipv4/ipip.c#L515">515</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipip_exit_net">ipip_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L516" href="source/net/ipv4/ipip.c#L516">516</a> {
<a name="L517" href="source/net/ipv4/ipip.c#L517">517</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ipip_net_id);
<a name="L518" href="source/net/ipv4/ipip.c#L518">518</a>         <a href="ident?i=ip_tunnel_delete_net">ip_tunnel_delete_net</a>(itn, &amp;ipip_link_ops);
<a name="L519" href="source/net/ipv4/ipip.c#L519">519</a> }
<a name="L520" href="source/net/ipv4/ipip.c#L520">520</a> 
<a name="L521" href="source/net/ipv4/ipip.c#L521">521</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipip_net_ops">ipip_net_ops</a> = {
<a name="L522" href="source/net/ipv4/ipip.c#L522">522</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipip_init_net">ipip_init_net</a>,
<a name="L523" href="source/net/ipv4/ipip.c#L523">523</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipip_exit_net">ipip_exit_net</a>,
<a name="L524" href="source/net/ipv4/ipip.c#L524">524</a>         .<a href="ident?i=id">id</a>   = &amp;ipip_net_id,
<a name="L525" href="source/net/ipv4/ipip.c#L525">525</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a>),
<a name="L526" href="source/net/ipv4/ipip.c#L526">526</a> };
<a name="L527" href="source/net/ipv4/ipip.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/ipip.c#L528">528</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipip_init">ipip_init</a>(void)
<a name="L529" href="source/net/ipv4/ipip.c#L529">529</a> {
<a name="L530" href="source/net/ipv4/ipip.c#L530">530</a>         int <a href="ident?i=err">err</a>;
<a name="L531" href="source/net/ipv4/ipip.c#L531">531</a> 
<a name="L532" href="source/net/ipv4/ipip.c#L532">532</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"ipip: IPv4 over IPv4 tunneling driver\n"</i>);
<a name="L533" href="source/net/ipv4/ipip.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/ipip.c#L534">534</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_device">register_pernet_device</a>(&amp;<a href="ident?i=ipip_net_ops">ipip_net_ops</a>);
<a name="L535" href="source/net/ipv4/ipip.c#L535">535</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L536" href="source/net/ipv4/ipip.c#L536">536</a>                 return <a href="ident?i=err">err</a>;
<a name="L537" href="source/net/ipv4/ipip.c#L537">537</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm4_tunnel_register">xfrm4_tunnel_register</a>(&amp;ipip_handler, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L538" href="source/net/ipv4/ipip.c#L538">538</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L539" href="source/net/ipv4/ipip.c#L539">539</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't register tunnel\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L540" href="source/net/ipv4/ipip.c#L540">540</a>                 goto xfrm_tunnel_failed;
<a name="L541" href="source/net/ipv4/ipip.c#L541">541</a>         }
<a name="L542" href="source/net/ipv4/ipip.c#L542">542</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtnl_link_register">rtnl_link_register</a>(&amp;ipip_link_ops);
<a name="L543" href="source/net/ipv4/ipip.c#L543">543</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L544" href="source/net/ipv4/ipip.c#L544">544</a>                 goto rtnl_link_failed;
<a name="L545" href="source/net/ipv4/ipip.c#L545">545</a> 
<a name="L546" href="source/net/ipv4/ipip.c#L546">546</a> <a href="ident?i=out">out</a>:
<a name="L547" href="source/net/ipv4/ipip.c#L547">547</a>         return <a href="ident?i=err">err</a>;
<a name="L548" href="source/net/ipv4/ipip.c#L548">548</a> 
<a name="L549" href="source/net/ipv4/ipip.c#L549">549</a> rtnl_link_failed:
<a name="L550" href="source/net/ipv4/ipip.c#L550">550</a>         <a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>(&amp;ipip_handler, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L551" href="source/net/ipv4/ipip.c#L551">551</a> xfrm_tunnel_failed:
<a name="L552" href="source/net/ipv4/ipip.c#L552">552</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=ipip_net_ops">ipip_net_ops</a>);
<a name="L553" href="source/net/ipv4/ipip.c#L553">553</a>         goto <a href="ident?i=out">out</a>;
<a name="L554" href="source/net/ipv4/ipip.c#L554">554</a> }
<a name="L555" href="source/net/ipv4/ipip.c#L555">555</a> 
<a name="L556" href="source/net/ipv4/ipip.c#L556">556</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ipip_fini">ipip_fini</a>(void)
<a name="L557" href="source/net/ipv4/ipip.c#L557">557</a> {
<a name="L558" href="source/net/ipv4/ipip.c#L558">558</a>         <a href="ident?i=rtnl_link_unregister">rtnl_link_unregister</a>(&amp;ipip_link_ops);
<a name="L559" href="source/net/ipv4/ipip.c#L559">559</a>         if (<a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>(&amp;ipip_handler, <a href="ident?i=AF_INET">AF_INET</a>))
<a name="L560" href="source/net/ipv4/ipip.c#L560">560</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't deregister tunnel\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L561" href="source/net/ipv4/ipip.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/ipip.c#L562">562</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=ipip_net_ops">ipip_net_ops</a>);
<a name="L563" href="source/net/ipv4/ipip.c#L563">563</a> }
<a name="L564" href="source/net/ipv4/ipip.c#L564">564</a> 
<a name="L565" href="source/net/ipv4/ipip.c#L565">565</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ipip_init">ipip_init</a>);
<a name="L566" href="source/net/ipv4/ipip.c#L566">566</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ipip_fini">ipip_fini</a>);
<a name="L567" href="source/net/ipv4/ipip.c#L567">567</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L568" href="source/net/ipv4/ipip.c#L568">568</a> <a href="ident?i=MODULE_ALIAS_RTNL_LINK">MODULE_ALIAS_RTNL_LINK</a>(<i>"ipip"</i>);
<a name="L569" href="source/net/ipv4/ipip.c#L569">569</a> <a href="ident?i=MODULE_ALIAS_NETDEV">MODULE_ALIAS_NETDEV</a>(<i>"tunl0"</i>);
<a name="L570" href="source/net/ipv4/ipip.c#L570">570</a> </pre></div><p>
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
