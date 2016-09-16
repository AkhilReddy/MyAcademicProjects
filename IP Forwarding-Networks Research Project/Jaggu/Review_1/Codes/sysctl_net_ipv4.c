<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/sysctl_net_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/sysctl_net_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/sysctl_net_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/sysctl_net_ipv4.c">sysctl_net_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/sysctl_net_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/sysctl_net_ipv4.c#L2">2</a> <b><i> * sysctl_net_ipv4.c: sysctl interface to net IPV4 subsystem.</i></b>
  <a name="L3" href="source/net/ipv4/sysctl_net_ipv4.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/sysctl_net_ipv4.c#L4">4</a> <b><i> * Begun April 1, 1996, Mike Shaver.</i></b>
  <a name="L5" href="source/net/ipv4/sysctl_net_ipv4.c#L5">5</a> <b><i> * Added /proc/sys/net/ipv4 directory entry (empty =) ). [MS]</i></b>
  <a name="L6" href="source/net/ipv4/sysctl_net_ipv4.c#L6">6</a> <b><i> */</i></b>
  <a name="L7" href="source/net/ipv4/sysctl_net_ipv4.c#L7">7</a> 
  <a name="L8" href="source/net/ipv4/sysctl_net_ipv4.c#L8">8</a> #include &lt;linux/mm.h&gt;
  <a name="L9" href="source/net/ipv4/sysctl_net_ipv4.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/sysctl_net_ipv4.c#L10">10</a> #include &lt;linux/sysctl.h&gt;
 <a name="L11" href="source/net/ipv4/sysctl_net_ipv4.c#L11">11</a> #include &lt;linux/igmp.h&gt;
 <a name="L12" href="source/net/ipv4/sysctl_net_ipv4.c#L12">12</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L13" href="source/net/ipv4/sysctl_net_ipv4.c#L13">13</a> #include &lt;linux/seqlock.h&gt;
 <a name="L14" href="source/net/ipv4/sysctl_net_ipv4.c#L14">14</a> #include &lt;linux/init.h&gt;
 <a name="L15" href="source/net/ipv4/sysctl_net_ipv4.c#L15">15</a> #include &lt;linux/slab.h&gt;
 <a name="L16" href="source/net/ipv4/sysctl_net_ipv4.c#L16">16</a> #include &lt;linux/nsproxy.h&gt;
 <a name="L17" href="source/net/ipv4/sysctl_net_ipv4.c#L17">17</a> #include &lt;linux/swap.h&gt;
 <a name="L18" href="source/net/ipv4/sysctl_net_ipv4.c#L18">18</a> #include &lt;net/snmp.h&gt;
 <a name="L19" href="source/net/ipv4/sysctl_net_ipv4.c#L19">19</a> #include &lt;net/icmp.h&gt;
 <a name="L20" href="source/net/ipv4/sysctl_net_ipv4.c#L20">20</a> #include &lt;net/ip.h&gt;
 <a name="L21" href="source/net/ipv4/sysctl_net_ipv4.c#L21">21</a> #include &lt;net/route.h&gt;
 <a name="L22" href="source/net/ipv4/sysctl_net_ipv4.c#L22">22</a> #include &lt;net/tcp.h&gt;
 <a name="L23" href="source/net/ipv4/sysctl_net_ipv4.c#L23">23</a> #include &lt;net/udp.h&gt;
 <a name="L24" href="source/net/ipv4/sysctl_net_ipv4.c#L24">24</a> #include &lt;net/cipso_ipv4.h&gt;
 <a name="L25" href="source/net/ipv4/sysctl_net_ipv4.c#L25">25</a> #include &lt;net/inet_frag.h&gt;
 <a name="L26" href="source/net/ipv4/sysctl_net_ipv4.c#L26">26</a> #include &lt;net/ping.h&gt;
 <a name="L27" href="source/net/ipv4/sysctl_net_ipv4.c#L27">27</a> #include &lt;net/tcp_memcontrol.h&gt;
 <a name="L28" href="source/net/ipv4/sysctl_net_ipv4.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/sysctl_net_ipv4.c#L29">29</a> static int <a href="ident?i=zero">zero</a>;
 <a name="L30" href="source/net/ipv4/sysctl_net_ipv4.c#L30">30</a> static int <a href="ident?i=one">one</a> = 1;
 <a name="L31" href="source/net/ipv4/sysctl_net_ipv4.c#L31">31</a> static int <a href="ident?i=four">four</a> = 4;
 <a name="L32" href="source/net/ipv4/sysctl_net_ipv4.c#L32">32</a> static int <a href="ident?i=gso_max_segs">gso_max_segs</a> = <a href="ident?i=GSO_MAX_SEGS">GSO_MAX_SEGS</a>;
 <a name="L33" href="source/net/ipv4/sysctl_net_ipv4.c#L33">33</a> static int <a href="ident?i=tcp_retr1_max">tcp_retr1_max</a> = 255;
 <a name="L34" href="source/net/ipv4/sysctl_net_ipv4.c#L34">34</a> static int <a href="ident?i=ip_local_port_range_min">ip_local_port_range_min</a>[] = { 1, 1 };
 <a name="L35" href="source/net/ipv4/sysctl_net_ipv4.c#L35">35</a> static int <a href="ident?i=ip_local_port_range_max">ip_local_port_range_max</a>[] = { 65535, 65535 };
 <a name="L36" href="source/net/ipv4/sysctl_net_ipv4.c#L36">36</a> static int <a href="ident?i=tcp_adv_win_scale_min">tcp_adv_win_scale_min</a> = -31;
 <a name="L37" href="source/net/ipv4/sysctl_net_ipv4.c#L37">37</a> static int <a href="ident?i=tcp_adv_win_scale_max">tcp_adv_win_scale_max</a> = 31;
 <a name="L38" href="source/net/ipv4/sysctl_net_ipv4.c#L38">38</a> static int <a href="ident?i=ip_ttl_min">ip_ttl_min</a> = 1;
 <a name="L39" href="source/net/ipv4/sysctl_net_ipv4.c#L39">39</a> static int <a href="ident?i=ip_ttl_max">ip_ttl_max</a> = 255;
 <a name="L40" href="source/net/ipv4/sysctl_net_ipv4.c#L40">40</a> static int <a href="ident?i=tcp_syn_retries_min">tcp_syn_retries_min</a> = 1;
 <a name="L41" href="source/net/ipv4/sysctl_net_ipv4.c#L41">41</a> static int <a href="ident?i=tcp_syn_retries_max">tcp_syn_retries_max</a> = <a href="ident?i=MAX_TCP_SYNCNT">MAX_TCP_SYNCNT</a>;
 <a name="L42" href="source/net/ipv4/sysctl_net_ipv4.c#L42">42</a> static int <a href="ident?i=ip_ping_group_range_min">ip_ping_group_range_min</a>[] = { 0, 0 };
 <a name="L43" href="source/net/ipv4/sysctl_net_ipv4.c#L43">43</a> static int <a href="ident?i=ip_ping_group_range_max">ip_ping_group_range_max</a>[] = { <a href="ident?i=GID_T_MAX">GID_T_MAX</a>, <a href="ident?i=GID_T_MAX">GID_T_MAX</a> };
 <a name="L44" href="source/net/ipv4/sysctl_net_ipv4.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/sysctl_net_ipv4.c#L45">45</a> <b><i>/* Update system visible IP port range */</i></b>
 <a name="L46" href="source/net/ipv4/sysctl_net_ipv4.c#L46">46</a> static void <a href="ident?i=set_local_port_range">set_local_port_range</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int <a href="ident?i=range">range</a>[2])
 <a name="L47" href="source/net/ipv4/sysctl_net_ipv4.c#L47">47</a> {
 <a name="L48" href="source/net/ipv4/sysctl_net_ipv4.c#L48">48</a>         <a href="ident?i=write_seqlock">write_seqlock</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
 <a name="L49" href="source/net/ipv4/sysctl_net_ipv4.c#L49">49</a>         <a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=range">range</a>[0] = <a href="ident?i=range">range</a>[0];
 <a name="L50" href="source/net/ipv4/sysctl_net_ipv4.c#L50">50</a>         <a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=range">range</a>[1] = <a href="ident?i=range">range</a>[1];
 <a name="L51" href="source/net/ipv4/sysctl_net_ipv4.c#L51">51</a>         <a href="ident?i=write_sequnlock">write_sequnlock</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
 <a name="L52" href="source/net/ipv4/sysctl_net_ipv4.c#L52">52</a> }
 <a name="L53" href="source/net/ipv4/sysctl_net_ipv4.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/sysctl_net_ipv4.c#L54">54</a> <b><i>/* Validate changes from /proc interface. */</i></b>
 <a name="L55" href="source/net/ipv4/sysctl_net_ipv4.c#L55">55</a> static int <a href="ident?i=ipv4_local_port_range">ipv4_local_port_range</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>, int <a href="ident?i=write">write</a>,
 <a name="L56" href="source/net/ipv4/sysctl_net_ipv4.c#L56">56</a>                                  void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>,
 <a name="L57" href="source/net/ipv4/sysctl_net_ipv4.c#L57">57</a>                                  <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
 <a name="L58" href="source/net/ipv4/sysctl_net_ipv4.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/sysctl_net_ipv4.c#L59">59</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> =
 <a name="L60" href="source/net/ipv4/sysctl_net_ipv4.c#L60">60</a>                 <a href="ident?i=container_of">container_of</a>(<a href="ident?i=table">table</a>-&gt;<a href="ident?i=data">data</a>, struct <a href="ident?i=net">net</a>, ipv4.ip_local_ports.<a href="ident?i=range">range</a>);
 <a name="L61" href="source/net/ipv4/sysctl_net_ipv4.c#L61">61</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L62" href="source/net/ipv4/sysctl_net_ipv4.c#L62">62</a>         int <a href="ident?i=range">range</a>[2];
 <a name="L63" href="source/net/ipv4/sysctl_net_ipv4.c#L63">63</a>         struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=tmp">tmp</a> = {
 <a name="L64" href="source/net/ipv4/sysctl_net_ipv4.c#L64">64</a>                 .<a href="ident?i=data">data</a> = &amp;<a href="ident?i=range">range</a>,
 <a name="L65" href="source/net/ipv4/sysctl_net_ipv4.c#L65">65</a>                 .maxlen = sizeof(<a href="ident?i=range">range</a>),
 <a name="L66" href="source/net/ipv4/sysctl_net_ipv4.c#L66">66</a>                 .<a href="ident?i=mode">mode</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=mode">mode</a>,
 <a name="L67" href="source/net/ipv4/sysctl_net_ipv4.c#L67">67</a>                 .extra1 = &amp;<a href="ident?i=ip_local_port_range_min">ip_local_port_range_min</a>,
 <a name="L68" href="source/net/ipv4/sysctl_net_ipv4.c#L68">68</a>                 .extra2 = &amp;<a href="ident?i=ip_local_port_range_max">ip_local_port_range_max</a>,
 <a name="L69" href="source/net/ipv4/sysctl_net_ipv4.c#L69">69</a>         };
 <a name="L70" href="source/net/ipv4/sysctl_net_ipv4.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/sysctl_net_ipv4.c#L71">71</a>         <a href="ident?i=inet_get_local_port_range">inet_get_local_port_range</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=range">range</a>[0], &amp;<a href="ident?i=range">range</a>[1]);
 <a name="L72" href="source/net/ipv4/sysctl_net_ipv4.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/sysctl_net_ipv4.c#L73">73</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>(&amp;<a href="ident?i=tmp">tmp</a>, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
 <a name="L74" href="source/net/ipv4/sysctl_net_ipv4.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/sysctl_net_ipv4.c#L75">75</a>         if (<a href="ident?i=write">write</a> &amp;&amp; <a href="ident?i=ret">ret</a> == 0) {
 <a name="L76" href="source/net/ipv4/sysctl_net_ipv4.c#L76">76</a>                 if (<a href="ident?i=range">range</a>[1] &lt; <a href="ident?i=range">range</a>[0])
 <a name="L77" href="source/net/ipv4/sysctl_net_ipv4.c#L77">77</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L78" href="source/net/ipv4/sysctl_net_ipv4.c#L78">78</a>                 else
 <a name="L79" href="source/net/ipv4/sysctl_net_ipv4.c#L79">79</a>                         <a href="ident?i=set_local_port_range">set_local_port_range</a>(<a href="ident?i=net">net</a>, <a href="ident?i=range">range</a>);
 <a name="L80" href="source/net/ipv4/sysctl_net_ipv4.c#L80">80</a>         }
 <a name="L81" href="source/net/ipv4/sysctl_net_ipv4.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/sysctl_net_ipv4.c#L82">82</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L83" href="source/net/ipv4/sysctl_net_ipv4.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/sysctl_net_ipv4.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/sysctl_net_ipv4.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/sysctl_net_ipv4.c#L86">86</a> static void <a href="ident?i=inet_get_ping_group_range_table">inet_get_ping_group_range_table</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>, <a href="ident?i=kgid_t">kgid_t</a> *low, <a href="ident?i=kgid_t">kgid_t</a> *<a href="ident?i=high">high</a>)
 <a name="L87" href="source/net/ipv4/sysctl_net_ipv4.c#L87">87</a> {
 <a name="L88" href="source/net/ipv4/sysctl_net_ipv4.c#L88">88</a>         <a href="ident?i=kgid_t">kgid_t</a> *<a href="ident?i=data">data</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=data">data</a>;
 <a name="L89" href="source/net/ipv4/sysctl_net_ipv4.c#L89">89</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> =
 <a name="L90" href="source/net/ipv4/sysctl_net_ipv4.c#L90">90</a>                 <a href="ident?i=container_of">container_of</a>(<a href="ident?i=table">table</a>-&gt;<a href="ident?i=data">data</a>, struct <a href="ident?i=net">net</a>, ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=range">range</a>);
 <a name="L91" href="source/net/ipv4/sysctl_net_ipv4.c#L91">91</a>         unsigned int <a href="ident?i=seq">seq</a>;
 <a name="L92" href="source/net/ipv4/sysctl_net_ipv4.c#L92">92</a>         do {
 <a name="L93" href="source/net/ipv4/sysctl_net_ipv4.c#L93">93</a>                 <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
 <a name="L94" href="source/net/ipv4/sysctl_net_ipv4.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/sysctl_net_ipv4.c#L95">95</a>                 *low = <a href="ident?i=data">data</a>[0];
 <a name="L96" href="source/net/ipv4/sysctl_net_ipv4.c#L96">96</a>                 *<a href="ident?i=high">high</a> = <a href="ident?i=data">data</a>[1];
 <a name="L97" href="source/net/ipv4/sysctl_net_ipv4.c#L97">97</a>         } while (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>, <a href="ident?i=seq">seq</a>));
 <a name="L98" href="source/net/ipv4/sysctl_net_ipv4.c#L98">98</a> }
 <a name="L99" href="source/net/ipv4/sysctl_net_ipv4.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/sysctl_net_ipv4.c#L100">100</a> <b><i>/* Update system visible IP port range */</i></b>
<a name="L101" href="source/net/ipv4/sysctl_net_ipv4.c#L101">101</a> static void <a href="ident?i=set_ping_group_range">set_ping_group_range</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>, <a href="ident?i=kgid_t">kgid_t</a> low, <a href="ident?i=kgid_t">kgid_t</a> <a href="ident?i=high">high</a>)
<a name="L102" href="source/net/ipv4/sysctl_net_ipv4.c#L102">102</a> {
<a name="L103" href="source/net/ipv4/sysctl_net_ipv4.c#L103">103</a>         <a href="ident?i=kgid_t">kgid_t</a> *<a href="ident?i=data">data</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L104" href="source/net/ipv4/sysctl_net_ipv4.c#L104">104</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> =
<a name="L105" href="source/net/ipv4/sysctl_net_ipv4.c#L105">105</a>                 <a href="ident?i=container_of">container_of</a>(<a href="ident?i=table">table</a>-&gt;<a href="ident?i=data">data</a>, struct <a href="ident?i=net">net</a>, ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=range">range</a>);
<a name="L106" href="source/net/ipv4/sysctl_net_ipv4.c#L106">106</a>         <a href="ident?i=write_seqlock">write_seqlock</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
<a name="L107" href="source/net/ipv4/sysctl_net_ipv4.c#L107">107</a>         <a href="ident?i=data">data</a>[0] = low;
<a name="L108" href="source/net/ipv4/sysctl_net_ipv4.c#L108">108</a>         <a href="ident?i=data">data</a>[1] = <a href="ident?i=high">high</a>;
<a name="L109" href="source/net/ipv4/sysctl_net_ipv4.c#L109">109</a>         <a href="ident?i=write_sequnlock">write_sequnlock</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
<a name="L110" href="source/net/ipv4/sysctl_net_ipv4.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/sysctl_net_ipv4.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/sysctl_net_ipv4.c#L112">112</a> <b><i>/* Validate changes from /proc interface. */</i></b>
<a name="L113" href="source/net/ipv4/sysctl_net_ipv4.c#L113">113</a> static int <a href="ident?i=ipv4_ping_group_range">ipv4_ping_group_range</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>, int <a href="ident?i=write">write</a>,
<a name="L114" href="source/net/ipv4/sysctl_net_ipv4.c#L114">114</a>                                  void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>,
<a name="L115" href="source/net/ipv4/sysctl_net_ipv4.c#L115">115</a>                                  <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L116" href="source/net/ipv4/sysctl_net_ipv4.c#L116">116</a> {
<a name="L117" href="source/net/ipv4/sysctl_net_ipv4.c#L117">117</a>         struct <a href="ident?i=user_namespace">user_namespace</a> *<a href="ident?i=user_ns">user_ns</a> = <a href="ident?i=current_user_ns">current_user_ns</a>();
<a name="L118" href="source/net/ipv4/sysctl_net_ipv4.c#L118">118</a>         int <a href="ident?i=ret">ret</a>;
<a name="L119" href="source/net/ipv4/sysctl_net_ipv4.c#L119">119</a>         <a href="ident?i=gid_t">gid_t</a> urange[2];
<a name="L120" href="source/net/ipv4/sysctl_net_ipv4.c#L120">120</a>         <a href="ident?i=kgid_t">kgid_t</a> low, <a href="ident?i=high">high</a>;
<a name="L121" href="source/net/ipv4/sysctl_net_ipv4.c#L121">121</a>         struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=tmp">tmp</a> = {
<a name="L122" href="source/net/ipv4/sysctl_net_ipv4.c#L122">122</a>                 .<a href="ident?i=data">data</a> = &amp;urange,
<a name="L123" href="source/net/ipv4/sysctl_net_ipv4.c#L123">123</a>                 .maxlen = sizeof(urange),
<a name="L124" href="source/net/ipv4/sysctl_net_ipv4.c#L124">124</a>                 .<a href="ident?i=mode">mode</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=mode">mode</a>,
<a name="L125" href="source/net/ipv4/sysctl_net_ipv4.c#L125">125</a>                 .extra1 = &amp;<a href="ident?i=ip_ping_group_range_min">ip_ping_group_range_min</a>,
<a name="L126" href="source/net/ipv4/sysctl_net_ipv4.c#L126">126</a>                 .extra2 = &amp;<a href="ident?i=ip_ping_group_range_max">ip_ping_group_range_max</a>,
<a name="L127" href="source/net/ipv4/sysctl_net_ipv4.c#L127">127</a>         };
<a name="L128" href="source/net/ipv4/sysctl_net_ipv4.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/sysctl_net_ipv4.c#L129">129</a>         <a href="ident?i=inet_get_ping_group_range_table">inet_get_ping_group_range_table</a>(<a href="ident?i=table">table</a>, &amp;low, &amp;<a href="ident?i=high">high</a>);
<a name="L130" href="source/net/ipv4/sysctl_net_ipv4.c#L130">130</a>         urange[0] = <a href="ident?i=from_kgid_munged">from_kgid_munged</a>(<a href="ident?i=user_ns">user_ns</a>, low);
<a name="L131" href="source/net/ipv4/sysctl_net_ipv4.c#L131">131</a>         urange[1] = <a href="ident?i=from_kgid_munged">from_kgid_munged</a>(<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=high">high</a>);
<a name="L132" href="source/net/ipv4/sysctl_net_ipv4.c#L132">132</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>(&amp;<a href="ident?i=tmp">tmp</a>, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L133" href="source/net/ipv4/sysctl_net_ipv4.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/sysctl_net_ipv4.c#L134">134</a>         if (<a href="ident?i=write">write</a> &amp;&amp; <a href="ident?i=ret">ret</a> == 0) {
<a name="L135" href="source/net/ipv4/sysctl_net_ipv4.c#L135">135</a>                 low = <a href="ident?i=make_kgid">make_kgid</a>(<a href="ident?i=user_ns">user_ns</a>, urange[0]);
<a name="L136" href="source/net/ipv4/sysctl_net_ipv4.c#L136">136</a>                 <a href="ident?i=high">high</a> = <a href="ident?i=make_kgid">make_kgid</a>(<a href="ident?i=user_ns">user_ns</a>, urange[1]);
<a name="L137" href="source/net/ipv4/sysctl_net_ipv4.c#L137">137</a>                 if (!<a href="ident?i=gid_valid">gid_valid</a>(low) || !<a href="ident?i=gid_valid">gid_valid</a>(<a href="ident?i=high">high</a>) ||
<a name="L138" href="source/net/ipv4/sysctl_net_ipv4.c#L138">138</a>                     (urange[1] &lt; urange[0]) || <a href="ident?i=gid_lt">gid_lt</a>(<a href="ident?i=high">high</a>, low)) {
<a name="L139" href="source/net/ipv4/sysctl_net_ipv4.c#L139">139</a>                         low = <a href="ident?i=make_kgid">make_kgid</a>(&amp;<a href="ident?i=init_user_ns">init_user_ns</a>, 1);
<a name="L140" href="source/net/ipv4/sysctl_net_ipv4.c#L140">140</a>                         <a href="ident?i=high">high</a> = <a href="ident?i=make_kgid">make_kgid</a>(&amp;<a href="ident?i=init_user_ns">init_user_ns</a>, 0);
<a name="L141" href="source/net/ipv4/sysctl_net_ipv4.c#L141">141</a>                 }
<a name="L142" href="source/net/ipv4/sysctl_net_ipv4.c#L142">142</a>                 <a href="ident?i=set_ping_group_range">set_ping_group_range</a>(<a href="ident?i=table">table</a>, low, <a href="ident?i=high">high</a>);
<a name="L143" href="source/net/ipv4/sysctl_net_ipv4.c#L143">143</a>         }
<a name="L144" href="source/net/ipv4/sysctl_net_ipv4.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/sysctl_net_ipv4.c#L145">145</a>         return <a href="ident?i=ret">ret</a>;
<a name="L146" href="source/net/ipv4/sysctl_net_ipv4.c#L146">146</a> }
<a name="L147" href="source/net/ipv4/sysctl_net_ipv4.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/sysctl_net_ipv4.c#L148">148</a> static int <a href="ident?i=proc_tcp_congestion_control">proc_tcp_congestion_control</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>, int <a href="ident?i=write">write</a>,
<a name="L149" href="source/net/ipv4/sysctl_net_ipv4.c#L149">149</a>                                        void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>, <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L150" href="source/net/ipv4/sysctl_net_ipv4.c#L150">150</a> {
<a name="L151" href="source/net/ipv4/sysctl_net_ipv4.c#L151">151</a>         char <a href="ident?i=val">val</a>[<a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>];
<a name="L152" href="source/net/ipv4/sysctl_net_ipv4.c#L152">152</a>         struct <a href="ident?i=ctl_table">ctl_table</a> tbl = {
<a name="L153" href="source/net/ipv4/sysctl_net_ipv4.c#L153">153</a>                 .<a href="ident?i=data">data</a> = <a href="ident?i=val">val</a>,
<a name="L154" href="source/net/ipv4/sysctl_net_ipv4.c#L154">154</a>                 .maxlen = <a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>,
<a name="L155" href="source/net/ipv4/sysctl_net_ipv4.c#L155">155</a>         };
<a name="L156" href="source/net/ipv4/sysctl_net_ipv4.c#L156">156</a>         int <a href="ident?i=ret">ret</a>;
<a name="L157" href="source/net/ipv4/sysctl_net_ipv4.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/sysctl_net_ipv4.c#L158">158</a>         <a href="ident?i=tcp_get_default_congestion_control">tcp_get_default_congestion_control</a>(<a href="ident?i=val">val</a>);
<a name="L159" href="source/net/ipv4/sysctl_net_ipv4.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/sysctl_net_ipv4.c#L160">160</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dostring">proc_dostring</a>(&amp;tbl, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L161" href="source/net/ipv4/sysctl_net_ipv4.c#L161">161</a>         if (<a href="ident?i=write">write</a> &amp;&amp; <a href="ident?i=ret">ret</a> == 0)
<a name="L162" href="source/net/ipv4/sysctl_net_ipv4.c#L162">162</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=tcp_set_default_congestion_control">tcp_set_default_congestion_control</a>(<a href="ident?i=val">val</a>);
<a name="L163" href="source/net/ipv4/sysctl_net_ipv4.c#L163">163</a>         return <a href="ident?i=ret">ret</a>;
<a name="L164" href="source/net/ipv4/sysctl_net_ipv4.c#L164">164</a> }
<a name="L165" href="source/net/ipv4/sysctl_net_ipv4.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/sysctl_net_ipv4.c#L166">166</a> static int <a href="ident?i=proc_tcp_available_congestion_control">proc_tcp_available_congestion_control</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>,
<a name="L167" href="source/net/ipv4/sysctl_net_ipv4.c#L167">167</a>                                                  int <a href="ident?i=write">write</a>,
<a name="L168" href="source/net/ipv4/sysctl_net_ipv4.c#L168">168</a>                                                  void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>, <a href="ident?i=size_t">size_t</a> *lenp,
<a name="L169" href="source/net/ipv4/sysctl_net_ipv4.c#L169">169</a>                                                  <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L170" href="source/net/ipv4/sysctl_net_ipv4.c#L170">170</a> {
<a name="L171" href="source/net/ipv4/sysctl_net_ipv4.c#L171">171</a>         struct <a href="ident?i=ctl_table">ctl_table</a> tbl = { .maxlen = <a href="ident?i=TCP_CA_BUF_MAX">TCP_CA_BUF_MAX</a>, };
<a name="L172" href="source/net/ipv4/sysctl_net_ipv4.c#L172">172</a>         int <a href="ident?i=ret">ret</a>;
<a name="L173" href="source/net/ipv4/sysctl_net_ipv4.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/sysctl_net_ipv4.c#L174">174</a>         tbl.<a href="ident?i=data">data</a> = <a href="ident?i=kmalloc">kmalloc</a>(tbl.maxlen, <a href="ident?i=GFP_USER">GFP_USER</a>);
<a name="L175" href="source/net/ipv4/sysctl_net_ipv4.c#L175">175</a>         if (!tbl.<a href="ident?i=data">data</a>)
<a name="L176" href="source/net/ipv4/sysctl_net_ipv4.c#L176">176</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L177" href="source/net/ipv4/sysctl_net_ipv4.c#L177">177</a>         <a href="ident?i=tcp_get_available_congestion_control">tcp_get_available_congestion_control</a>(tbl.<a href="ident?i=data">data</a>, <a href="ident?i=TCP_CA_BUF_MAX">TCP_CA_BUF_MAX</a>);
<a name="L178" href="source/net/ipv4/sysctl_net_ipv4.c#L178">178</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dostring">proc_dostring</a>(&amp;tbl, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L179" href="source/net/ipv4/sysctl_net_ipv4.c#L179">179</a>         <a href="ident?i=kfree">kfree</a>(tbl.<a href="ident?i=data">data</a>);
<a name="L180" href="source/net/ipv4/sysctl_net_ipv4.c#L180">180</a>         return <a href="ident?i=ret">ret</a>;
<a name="L181" href="source/net/ipv4/sysctl_net_ipv4.c#L181">181</a> }
<a name="L182" href="source/net/ipv4/sysctl_net_ipv4.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/sysctl_net_ipv4.c#L183">183</a> static int <a href="ident?i=proc_allowed_congestion_control">proc_allowed_congestion_control</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>,
<a name="L184" href="source/net/ipv4/sysctl_net_ipv4.c#L184">184</a>                                            int <a href="ident?i=write">write</a>,
<a name="L185" href="source/net/ipv4/sysctl_net_ipv4.c#L185">185</a>                                            void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>, <a href="ident?i=size_t">size_t</a> *lenp,
<a name="L186" href="source/net/ipv4/sysctl_net_ipv4.c#L186">186</a>                                            <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L187" href="source/net/ipv4/sysctl_net_ipv4.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/sysctl_net_ipv4.c#L188">188</a>         struct <a href="ident?i=ctl_table">ctl_table</a> tbl = { .maxlen = <a href="ident?i=TCP_CA_BUF_MAX">TCP_CA_BUF_MAX</a> };
<a name="L189" href="source/net/ipv4/sysctl_net_ipv4.c#L189">189</a>         int <a href="ident?i=ret">ret</a>;
<a name="L190" href="source/net/ipv4/sysctl_net_ipv4.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/sysctl_net_ipv4.c#L191">191</a>         tbl.<a href="ident?i=data">data</a> = <a href="ident?i=kmalloc">kmalloc</a>(tbl.maxlen, <a href="ident?i=GFP_USER">GFP_USER</a>);
<a name="L192" href="source/net/ipv4/sysctl_net_ipv4.c#L192">192</a>         if (!tbl.<a href="ident?i=data">data</a>)
<a name="L193" href="source/net/ipv4/sysctl_net_ipv4.c#L193">193</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L194" href="source/net/ipv4/sysctl_net_ipv4.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/sysctl_net_ipv4.c#L195">195</a>         <a href="ident?i=tcp_get_allowed_congestion_control">tcp_get_allowed_congestion_control</a>(tbl.<a href="ident?i=data">data</a>, tbl.maxlen);
<a name="L196" href="source/net/ipv4/sysctl_net_ipv4.c#L196">196</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dostring">proc_dostring</a>(&amp;tbl, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L197" href="source/net/ipv4/sysctl_net_ipv4.c#L197">197</a>         if (<a href="ident?i=write">write</a> &amp;&amp; <a href="ident?i=ret">ret</a> == 0)
<a name="L198" href="source/net/ipv4/sysctl_net_ipv4.c#L198">198</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=tcp_set_allowed_congestion_control">tcp_set_allowed_congestion_control</a>(tbl.<a href="ident?i=data">data</a>);
<a name="L199" href="source/net/ipv4/sysctl_net_ipv4.c#L199">199</a>         <a href="ident?i=kfree">kfree</a>(tbl.<a href="ident?i=data">data</a>);
<a name="L200" href="source/net/ipv4/sysctl_net_ipv4.c#L200">200</a>         return <a href="ident?i=ret">ret</a>;
<a name="L201" href="source/net/ipv4/sysctl_net_ipv4.c#L201">201</a> }
<a name="L202" href="source/net/ipv4/sysctl_net_ipv4.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/sysctl_net_ipv4.c#L203">203</a> static int <a href="ident?i=proc_tcp_fastopen_key">proc_tcp_fastopen_key</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=ctl">ctl</a>, int <a href="ident?i=write">write</a>,
<a name="L204" href="source/net/ipv4/sysctl_net_ipv4.c#L204">204</a>                                  void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>, <a href="ident?i=size_t">size_t</a> *lenp,
<a name="L205" href="source/net/ipv4/sysctl_net_ipv4.c#L205">205</a>                                  <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L206" href="source/net/ipv4/sysctl_net_ipv4.c#L206">206</a> {
<a name="L207" href="source/net/ipv4/sysctl_net_ipv4.c#L207">207</a>         struct <a href="ident?i=ctl_table">ctl_table</a> tbl = { .maxlen = (<a href="ident?i=TCP_FASTOPEN_KEY_LENGTH">TCP_FASTOPEN_KEY_LENGTH</a> * 2 + 10) };
<a name="L208" href="source/net/ipv4/sysctl_net_ipv4.c#L208">208</a>         struct <a href="ident?i=tcp_fastopen_context">tcp_fastopen_context</a> *<a href="ident?i=ctxt">ctxt</a>;
<a name="L209" href="source/net/ipv4/sysctl_net_ipv4.c#L209">209</a>         int <a href="ident?i=ret">ret</a>;
<a name="L210" href="source/net/ipv4/sysctl_net_ipv4.c#L210">210</a>         <a href="ident?i=u32">u32</a>  user_key[4]; <b><i>/* 16 bytes, matching TCP_FASTOPEN_KEY_LENGTH */</i></b>
<a name="L211" href="source/net/ipv4/sysctl_net_ipv4.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/sysctl_net_ipv4.c#L212">212</a>         tbl.<a href="ident?i=data">data</a> = <a href="ident?i=kmalloc">kmalloc</a>(tbl.maxlen, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L213" href="source/net/ipv4/sysctl_net_ipv4.c#L213">213</a>         if (!tbl.<a href="ident?i=data">data</a>)
<a name="L214" href="source/net/ipv4/sysctl_net_ipv4.c#L214">214</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L215" href="source/net/ipv4/sysctl_net_ipv4.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/sysctl_net_ipv4.c#L216">216</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L217" href="source/net/ipv4/sysctl_net_ipv4.c#L217">217</a>         <a href="ident?i=ctxt">ctxt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=tcp_fastopen_ctx">tcp_fastopen_ctx</a>);
<a name="L218" href="source/net/ipv4/sysctl_net_ipv4.c#L218">218</a>         if (<a href="ident?i=ctxt">ctxt</a>)
<a name="L219" href="source/net/ipv4/sysctl_net_ipv4.c#L219">219</a>                 <a href="ident?i=memcpy">memcpy</a>(user_key, <a href="ident?i=ctxt">ctxt</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=TCP_FASTOPEN_KEY_LENGTH">TCP_FASTOPEN_KEY_LENGTH</a>);
<a name="L220" href="source/net/ipv4/sysctl_net_ipv4.c#L220">220</a>         else
<a name="L221" href="source/net/ipv4/sysctl_net_ipv4.c#L221">221</a>                 <a href="ident?i=memset">memset</a>(user_key, 0, sizeof(user_key));
<a name="L222" href="source/net/ipv4/sysctl_net_ipv4.c#L222">222</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L223" href="source/net/ipv4/sysctl_net_ipv4.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/sysctl_net_ipv4.c#L224">224</a>         <a href="ident?i=snprintf">snprintf</a>(tbl.<a href="ident?i=data">data</a>, tbl.maxlen, <i>"%08x-%08x-%08x-%08x"</i>,
<a name="L225" href="source/net/ipv4/sysctl_net_ipv4.c#L225">225</a>                 user_key[0], user_key[1], user_key[2], user_key[3]);
<a name="L226" href="source/net/ipv4/sysctl_net_ipv4.c#L226">226</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proc_dostring">proc_dostring</a>(&amp;tbl, <a href="ident?i=write">write</a>, <a href="ident?i=buffer">buffer</a>, lenp, <a href="ident?i=ppos">ppos</a>);
<a name="L227" href="source/net/ipv4/sysctl_net_ipv4.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/sysctl_net_ipv4.c#L228">228</a>         if (<a href="ident?i=write">write</a> &amp;&amp; <a href="ident?i=ret">ret</a> == 0) {
<a name="L229" href="source/net/ipv4/sysctl_net_ipv4.c#L229">229</a>                 if (<a href="ident?i=sscanf">sscanf</a>(tbl.<a href="ident?i=data">data</a>, <i>"%x-%x-%x-%x"</i>, user_key, user_key + 1,
<a name="L230" href="source/net/ipv4/sysctl_net_ipv4.c#L230">230</a>                            user_key + 2, user_key + 3) != 4) {
<a name="L231" href="source/net/ipv4/sysctl_net_ipv4.c#L231">231</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L232" href="source/net/ipv4/sysctl_net_ipv4.c#L232">232</a>                         goto bad_key;
<a name="L233" href="source/net/ipv4/sysctl_net_ipv4.c#L233">233</a>                 }
<a name="L234" href="source/net/ipv4/sysctl_net_ipv4.c#L234">234</a>                 <b><i>/* Generate a dummy secret but don't publish it. This</i></b>
<a name="L235" href="source/net/ipv4/sysctl_net_ipv4.c#L235">235</a> <b><i>                 * is needed so we don't regenerate a new key on the</i></b>
<a name="L236" href="source/net/ipv4/sysctl_net_ipv4.c#L236">236</a> <b><i>                 * first invocation of tcp_fastopen_cookie_gen</i></b>
<a name="L237" href="source/net/ipv4/sysctl_net_ipv4.c#L237">237</a> <b><i>                 */</i></b>
<a name="L238" href="source/net/ipv4/sysctl_net_ipv4.c#L238">238</a>                 <a href="ident?i=tcp_fastopen_init_key_once">tcp_fastopen_init_key_once</a>(<a href="ident?i=false">false</a>);
<a name="L239" href="source/net/ipv4/sysctl_net_ipv4.c#L239">239</a>                 <a href="ident?i=tcp_fastopen_reset_cipher">tcp_fastopen_reset_cipher</a>(user_key, <a href="ident?i=TCP_FASTOPEN_KEY_LENGTH">TCP_FASTOPEN_KEY_LENGTH</a>);
<a name="L240" href="source/net/ipv4/sysctl_net_ipv4.c#L240">240</a>         }
<a name="L241" href="source/net/ipv4/sysctl_net_ipv4.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/sysctl_net_ipv4.c#L242">242</a> bad_key:
<a name="L243" href="source/net/ipv4/sysctl_net_ipv4.c#L243">243</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"proc FO key set 0x%x-%x-%x-%x &lt;- 0x%s: %u\n"</i>,
<a name="L244" href="source/net/ipv4/sysctl_net_ipv4.c#L244">244</a>                user_key[0], user_key[1], user_key[2], user_key[3],
<a name="L245" href="source/net/ipv4/sysctl_net_ipv4.c#L245">245</a>                (char *)tbl.<a href="ident?i=data">data</a>, <a href="ident?i=ret">ret</a>);
<a name="L246" href="source/net/ipv4/sysctl_net_ipv4.c#L246">246</a>         <a href="ident?i=kfree">kfree</a>(tbl.<a href="ident?i=data">data</a>);
<a name="L247" href="source/net/ipv4/sysctl_net_ipv4.c#L247">247</a>         return <a href="ident?i=ret">ret</a>;
<a name="L248" href="source/net/ipv4/sysctl_net_ipv4.c#L248">248</a> }
<a name="L249" href="source/net/ipv4/sysctl_net_ipv4.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/sysctl_net_ipv4.c#L250">250</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ipv4_table">ipv4_table</a>[] = {
<a name="L251" href="source/net/ipv4/sysctl_net_ipv4.c#L251">251</a>         {
<a name="L252" href="source/net/ipv4/sysctl_net_ipv4.c#L252">252</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_timestamps"</i>,
<a name="L253" href="source/net/ipv4/sysctl_net_ipv4.c#L253">253</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_timestamps">sysctl_tcp_timestamps</a>,
<a name="L254" href="source/net/ipv4/sysctl_net_ipv4.c#L254">254</a>                 .maxlen         = sizeof(int),
<a name="L255" href="source/net/ipv4/sysctl_net_ipv4.c#L255">255</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L256" href="source/net/ipv4/sysctl_net_ipv4.c#L256">256</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L257" href="source/net/ipv4/sysctl_net_ipv4.c#L257">257</a>         },
<a name="L258" href="source/net/ipv4/sysctl_net_ipv4.c#L258">258</a>         {
<a name="L259" href="source/net/ipv4/sysctl_net_ipv4.c#L259">259</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_window_scaling"</i>,
<a name="L260" href="source/net/ipv4/sysctl_net_ipv4.c#L260">260</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_window_scaling">sysctl_tcp_window_scaling</a>,
<a name="L261" href="source/net/ipv4/sysctl_net_ipv4.c#L261">261</a>                 .maxlen         = sizeof(int),
<a name="L262" href="source/net/ipv4/sysctl_net_ipv4.c#L262">262</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L263" href="source/net/ipv4/sysctl_net_ipv4.c#L263">263</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L264" href="source/net/ipv4/sysctl_net_ipv4.c#L264">264</a>         },
<a name="L265" href="source/net/ipv4/sysctl_net_ipv4.c#L265">265</a>         {
<a name="L266" href="source/net/ipv4/sysctl_net_ipv4.c#L266">266</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_sack"</i>,
<a name="L267" href="source/net/ipv4/sysctl_net_ipv4.c#L267">267</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_sack">sysctl_tcp_sack</a>,
<a name="L268" href="source/net/ipv4/sysctl_net_ipv4.c#L268">268</a>                 .maxlen         = sizeof(int),
<a name="L269" href="source/net/ipv4/sysctl_net_ipv4.c#L269">269</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L270" href="source/net/ipv4/sysctl_net_ipv4.c#L270">270</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L271" href="source/net/ipv4/sysctl_net_ipv4.c#L271">271</a>         },
<a name="L272" href="source/net/ipv4/sysctl_net_ipv4.c#L272">272</a>         {
<a name="L273" href="source/net/ipv4/sysctl_net_ipv4.c#L273">273</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_retrans_collapse"</i>,
<a name="L274" href="source/net/ipv4/sysctl_net_ipv4.c#L274">274</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_retrans_collapse">sysctl_tcp_retrans_collapse</a>,
<a name="L275" href="source/net/ipv4/sysctl_net_ipv4.c#L275">275</a>                 .maxlen         = sizeof(int),
<a name="L276" href="source/net/ipv4/sysctl_net_ipv4.c#L276">276</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L277" href="source/net/ipv4/sysctl_net_ipv4.c#L277">277</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L278" href="source/net/ipv4/sysctl_net_ipv4.c#L278">278</a>         },
<a name="L279" href="source/net/ipv4/sysctl_net_ipv4.c#L279">279</a>         {
<a name="L280" href="source/net/ipv4/sysctl_net_ipv4.c#L280">280</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_default_ttl"</i>,
<a name="L281" href="source/net/ipv4/sysctl_net_ipv4.c#L281">281</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_ip_default_ttl">sysctl_ip_default_ttl</a>,
<a name="L282" href="source/net/ipv4/sysctl_net_ipv4.c#L282">282</a>                 .maxlen         = sizeof(int),
<a name="L283" href="source/net/ipv4/sysctl_net_ipv4.c#L283">283</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L284" href="source/net/ipv4/sysctl_net_ipv4.c#L284">284</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L285" href="source/net/ipv4/sysctl_net_ipv4.c#L285">285</a>                 .extra1         = &amp;<a href="ident?i=ip_ttl_min">ip_ttl_min</a>,
<a name="L286" href="source/net/ipv4/sysctl_net_ipv4.c#L286">286</a>                 .extra2         = &amp;<a href="ident?i=ip_ttl_max">ip_ttl_max</a>,
<a name="L287" href="source/net/ipv4/sysctl_net_ipv4.c#L287">287</a>         },
<a name="L288" href="source/net/ipv4/sysctl_net_ipv4.c#L288">288</a>         {
<a name="L289" href="source/net/ipv4/sysctl_net_ipv4.c#L289">289</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_syn_retries"</i>,
<a name="L290" href="source/net/ipv4/sysctl_net_ipv4.c#L290">290</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_syn_retries">sysctl_tcp_syn_retries</a>,
<a name="L291" href="source/net/ipv4/sysctl_net_ipv4.c#L291">291</a>                 .maxlen         = sizeof(int),
<a name="L292" href="source/net/ipv4/sysctl_net_ipv4.c#L292">292</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L293" href="source/net/ipv4/sysctl_net_ipv4.c#L293">293</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L294" href="source/net/ipv4/sysctl_net_ipv4.c#L294">294</a>                 .extra1         = &amp;<a href="ident?i=tcp_syn_retries_min">tcp_syn_retries_min</a>,
<a name="L295" href="source/net/ipv4/sysctl_net_ipv4.c#L295">295</a>                 .extra2         = &amp;<a href="ident?i=tcp_syn_retries_max">tcp_syn_retries_max</a>
<a name="L296" href="source/net/ipv4/sysctl_net_ipv4.c#L296">296</a>         },
<a name="L297" href="source/net/ipv4/sysctl_net_ipv4.c#L297">297</a>         {
<a name="L298" href="source/net/ipv4/sysctl_net_ipv4.c#L298">298</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_synack_retries"</i>,
<a name="L299" href="source/net/ipv4/sysctl_net_ipv4.c#L299">299</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_synack_retries">sysctl_tcp_synack_retries</a>,
<a name="L300" href="source/net/ipv4/sysctl_net_ipv4.c#L300">300</a>                 .maxlen         = sizeof(int),
<a name="L301" href="source/net/ipv4/sysctl_net_ipv4.c#L301">301</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L302" href="source/net/ipv4/sysctl_net_ipv4.c#L302">302</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L303" href="source/net/ipv4/sysctl_net_ipv4.c#L303">303</a>         },
<a name="L304" href="source/net/ipv4/sysctl_net_ipv4.c#L304">304</a>         {
<a name="L305" href="source/net/ipv4/sysctl_net_ipv4.c#L305">305</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_max_orphans"</i>,
<a name="L306" href="source/net/ipv4/sysctl_net_ipv4.c#L306">306</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_max_orphans">sysctl_tcp_max_orphans</a>,
<a name="L307" href="source/net/ipv4/sysctl_net_ipv4.c#L307">307</a>                 .maxlen         = sizeof(int),
<a name="L308" href="source/net/ipv4/sysctl_net_ipv4.c#L308">308</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L309" href="source/net/ipv4/sysctl_net_ipv4.c#L309">309</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L310" href="source/net/ipv4/sysctl_net_ipv4.c#L310">310</a>         },
<a name="L311" href="source/net/ipv4/sysctl_net_ipv4.c#L311">311</a>         {
<a name="L312" href="source/net/ipv4/sysctl_net_ipv4.c#L312">312</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_max_tw_buckets"</i>,
<a name="L313" href="source/net/ipv4/sysctl_net_ipv4.c#L313">313</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_max_tw_buckets,
<a name="L314" href="source/net/ipv4/sysctl_net_ipv4.c#L314">314</a>                 .maxlen         = sizeof(int),
<a name="L315" href="source/net/ipv4/sysctl_net_ipv4.c#L315">315</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L316" href="source/net/ipv4/sysctl_net_ipv4.c#L316">316</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L317" href="source/net/ipv4/sysctl_net_ipv4.c#L317">317</a>         },
<a name="L318" href="source/net/ipv4/sysctl_net_ipv4.c#L318">318</a>         {
<a name="L319" href="source/net/ipv4/sysctl_net_ipv4.c#L319">319</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_early_demux"</i>,
<a name="L320" href="source/net/ipv4/sysctl_net_ipv4.c#L320">320</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_ip_early_demux">sysctl_ip_early_demux</a>,
<a name="L321" href="source/net/ipv4/sysctl_net_ipv4.c#L321">321</a>                 .maxlen         = sizeof(int),
<a name="L322" href="source/net/ipv4/sysctl_net_ipv4.c#L322">322</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L323" href="source/net/ipv4/sysctl_net_ipv4.c#L323">323</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L324" href="source/net/ipv4/sysctl_net_ipv4.c#L324">324</a>         },
<a name="L325" href="source/net/ipv4/sysctl_net_ipv4.c#L325">325</a>         {
<a name="L326" href="source/net/ipv4/sysctl_net_ipv4.c#L326">326</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_dynaddr"</i>,
<a name="L327" href="source/net/ipv4/sysctl_net_ipv4.c#L327">327</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_ip_dynaddr">sysctl_ip_dynaddr</a>,
<a name="L328" href="source/net/ipv4/sysctl_net_ipv4.c#L328">328</a>                 .maxlen         = sizeof(int),
<a name="L329" href="source/net/ipv4/sysctl_net_ipv4.c#L329">329</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L330" href="source/net/ipv4/sysctl_net_ipv4.c#L330">330</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L331" href="source/net/ipv4/sysctl_net_ipv4.c#L331">331</a>         },
<a name="L332" href="source/net/ipv4/sysctl_net_ipv4.c#L332">332</a>         {
<a name="L333" href="source/net/ipv4/sysctl_net_ipv4.c#L333">333</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_keepalive_time"</i>,
<a name="L334" href="source/net/ipv4/sysctl_net_ipv4.c#L334">334</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_keepalive_time">sysctl_tcp_keepalive_time</a>,
<a name="L335" href="source/net/ipv4/sysctl_net_ipv4.c#L335">335</a>                 .maxlen         = sizeof(int),
<a name="L336" href="source/net/ipv4/sysctl_net_ipv4.c#L336">336</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L337" href="source/net/ipv4/sysctl_net_ipv4.c#L337">337</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L338" href="source/net/ipv4/sysctl_net_ipv4.c#L338">338</a>         },
<a name="L339" href="source/net/ipv4/sysctl_net_ipv4.c#L339">339</a>         {
<a name="L340" href="source/net/ipv4/sysctl_net_ipv4.c#L340">340</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_keepalive_probes"</i>,
<a name="L341" href="source/net/ipv4/sysctl_net_ipv4.c#L341">341</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_keepalive_probes">sysctl_tcp_keepalive_probes</a>,
<a name="L342" href="source/net/ipv4/sysctl_net_ipv4.c#L342">342</a>                 .maxlen         = sizeof(int),
<a name="L343" href="source/net/ipv4/sysctl_net_ipv4.c#L343">343</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L344" href="source/net/ipv4/sysctl_net_ipv4.c#L344">344</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L345" href="source/net/ipv4/sysctl_net_ipv4.c#L345">345</a>         },
<a name="L346" href="source/net/ipv4/sysctl_net_ipv4.c#L346">346</a>         {
<a name="L347" href="source/net/ipv4/sysctl_net_ipv4.c#L347">347</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_keepalive_intvl"</i>,
<a name="L348" href="source/net/ipv4/sysctl_net_ipv4.c#L348">348</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_keepalive_intvl">sysctl_tcp_keepalive_intvl</a>,
<a name="L349" href="source/net/ipv4/sysctl_net_ipv4.c#L349">349</a>                 .maxlen         = sizeof(int),
<a name="L350" href="source/net/ipv4/sysctl_net_ipv4.c#L350">350</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L351" href="source/net/ipv4/sysctl_net_ipv4.c#L351">351</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L352" href="source/net/ipv4/sysctl_net_ipv4.c#L352">352</a>         },
<a name="L353" href="source/net/ipv4/sysctl_net_ipv4.c#L353">353</a>         {
<a name="L354" href="source/net/ipv4/sysctl_net_ipv4.c#L354">354</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_retries1"</i>,
<a name="L355" href="source/net/ipv4/sysctl_net_ipv4.c#L355">355</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_retries1">sysctl_tcp_retries1</a>,
<a name="L356" href="source/net/ipv4/sysctl_net_ipv4.c#L356">356</a>                 .maxlen         = sizeof(int),
<a name="L357" href="source/net/ipv4/sysctl_net_ipv4.c#L357">357</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L358" href="source/net/ipv4/sysctl_net_ipv4.c#L358">358</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L359" href="source/net/ipv4/sysctl_net_ipv4.c#L359">359</a>                 .extra2         = &amp;<a href="ident?i=tcp_retr1_max">tcp_retr1_max</a>
<a name="L360" href="source/net/ipv4/sysctl_net_ipv4.c#L360">360</a>         },
<a name="L361" href="source/net/ipv4/sysctl_net_ipv4.c#L361">361</a>         {
<a name="L362" href="source/net/ipv4/sysctl_net_ipv4.c#L362">362</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_retries2"</i>,
<a name="L363" href="source/net/ipv4/sysctl_net_ipv4.c#L363">363</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_retries2">sysctl_tcp_retries2</a>,
<a name="L364" href="source/net/ipv4/sysctl_net_ipv4.c#L364">364</a>                 .maxlen         = sizeof(int),
<a name="L365" href="source/net/ipv4/sysctl_net_ipv4.c#L365">365</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L366" href="source/net/ipv4/sysctl_net_ipv4.c#L366">366</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L367" href="source/net/ipv4/sysctl_net_ipv4.c#L367">367</a>         },
<a name="L368" href="source/net/ipv4/sysctl_net_ipv4.c#L368">368</a>         {
<a name="L369" href="source/net/ipv4/sysctl_net_ipv4.c#L369">369</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_fin_timeout"</i>,
<a name="L370" href="source/net/ipv4/sysctl_net_ipv4.c#L370">370</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_fin_timeout">sysctl_tcp_fin_timeout</a>,
<a name="L371" href="source/net/ipv4/sysctl_net_ipv4.c#L371">371</a>                 .maxlen         = sizeof(int),
<a name="L372" href="source/net/ipv4/sysctl_net_ipv4.c#L372">372</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L373" href="source/net/ipv4/sysctl_net_ipv4.c#L373">373</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L374" href="source/net/ipv4/sysctl_net_ipv4.c#L374">374</a>         },
<a name="L375" href="source/net/ipv4/sysctl_net_ipv4.c#L375">375</a> #ifdef CONFIG_SYN_COOKIES
<a name="L376" href="source/net/ipv4/sysctl_net_ipv4.c#L376">376</a>         {
<a name="L377" href="source/net/ipv4/sysctl_net_ipv4.c#L377">377</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_syncookies"</i>,
<a name="L378" href="source/net/ipv4/sysctl_net_ipv4.c#L378">378</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a>,
<a name="L379" href="source/net/ipv4/sysctl_net_ipv4.c#L379">379</a>                 .maxlen         = sizeof(int),
<a name="L380" href="source/net/ipv4/sysctl_net_ipv4.c#L380">380</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L381" href="source/net/ipv4/sysctl_net_ipv4.c#L381">381</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L382" href="source/net/ipv4/sysctl_net_ipv4.c#L382">382</a>         },
<a name="L383" href="source/net/ipv4/sysctl_net_ipv4.c#L383">383</a> #endif
<a name="L384" href="source/net/ipv4/sysctl_net_ipv4.c#L384">384</a>         {
<a name="L385" href="source/net/ipv4/sysctl_net_ipv4.c#L385">385</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_fastopen"</i>,
<a name="L386" href="source/net/ipv4/sysctl_net_ipv4.c#L386">386</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a>,
<a name="L387" href="source/net/ipv4/sysctl_net_ipv4.c#L387">387</a>                 .maxlen         = sizeof(int),
<a name="L388" href="source/net/ipv4/sysctl_net_ipv4.c#L388">388</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L389" href="source/net/ipv4/sysctl_net_ipv4.c#L389">389</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L390" href="source/net/ipv4/sysctl_net_ipv4.c#L390">390</a>         },
<a name="L391" href="source/net/ipv4/sysctl_net_ipv4.c#L391">391</a>         {
<a name="L392" href="source/net/ipv4/sysctl_net_ipv4.c#L392">392</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_fastopen_key"</i>,
<a name="L393" href="source/net/ipv4/sysctl_net_ipv4.c#L393">393</a>                 .<a href="ident?i=mode">mode</a>           = 0600,
<a name="L394" href="source/net/ipv4/sysctl_net_ipv4.c#L394">394</a>                 .maxlen         = ((<a href="ident?i=TCP_FASTOPEN_KEY_LENGTH">TCP_FASTOPEN_KEY_LENGTH</a> * 2) + 10),
<a name="L395" href="source/net/ipv4/sysctl_net_ipv4.c#L395">395</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_tcp_fastopen_key">proc_tcp_fastopen_key</a>,
<a name="L396" href="source/net/ipv4/sysctl_net_ipv4.c#L396">396</a>         },
<a name="L397" href="source/net/ipv4/sysctl_net_ipv4.c#L397">397</a>         {
<a name="L398" href="source/net/ipv4/sysctl_net_ipv4.c#L398">398</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_tw_recycle"</i>,
<a name="L399" href="source/net/ipv4/sysctl_net_ipv4.c#L399">399</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_tw_recycle,
<a name="L400" href="source/net/ipv4/sysctl_net_ipv4.c#L400">400</a>                 .maxlen         = sizeof(int),
<a name="L401" href="source/net/ipv4/sysctl_net_ipv4.c#L401">401</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L402" href="source/net/ipv4/sysctl_net_ipv4.c#L402">402</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L403" href="source/net/ipv4/sysctl_net_ipv4.c#L403">403</a>         },
<a name="L404" href="source/net/ipv4/sysctl_net_ipv4.c#L404">404</a>         {
<a name="L405" href="source/net/ipv4/sysctl_net_ipv4.c#L405">405</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_abort_on_overflow"</i>,
<a name="L406" href="source/net/ipv4/sysctl_net_ipv4.c#L406">406</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_abort_on_overflow">sysctl_tcp_abort_on_overflow</a>,
<a name="L407" href="source/net/ipv4/sysctl_net_ipv4.c#L407">407</a>                 .maxlen         = sizeof(int),
<a name="L408" href="source/net/ipv4/sysctl_net_ipv4.c#L408">408</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L409" href="source/net/ipv4/sysctl_net_ipv4.c#L409">409</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L410" href="source/net/ipv4/sysctl_net_ipv4.c#L410">410</a>         },
<a name="L411" href="source/net/ipv4/sysctl_net_ipv4.c#L411">411</a>         {
<a name="L412" href="source/net/ipv4/sysctl_net_ipv4.c#L412">412</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_stdurg"</i>,
<a name="L413" href="source/net/ipv4/sysctl_net_ipv4.c#L413">413</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_stdurg">sysctl_tcp_stdurg</a>,
<a name="L414" href="source/net/ipv4/sysctl_net_ipv4.c#L414">414</a>                 .maxlen         = sizeof(int),
<a name="L415" href="source/net/ipv4/sysctl_net_ipv4.c#L415">415</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L416" href="source/net/ipv4/sysctl_net_ipv4.c#L416">416</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L417" href="source/net/ipv4/sysctl_net_ipv4.c#L417">417</a>         },
<a name="L418" href="source/net/ipv4/sysctl_net_ipv4.c#L418">418</a>         {
<a name="L419" href="source/net/ipv4/sysctl_net_ipv4.c#L419">419</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_rfc1337"</i>,
<a name="L420" href="source/net/ipv4/sysctl_net_ipv4.c#L420">420</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_rfc1337">sysctl_tcp_rfc1337</a>,
<a name="L421" href="source/net/ipv4/sysctl_net_ipv4.c#L421">421</a>                 .maxlen         = sizeof(int),
<a name="L422" href="source/net/ipv4/sysctl_net_ipv4.c#L422">422</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L423" href="source/net/ipv4/sysctl_net_ipv4.c#L423">423</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L424" href="source/net/ipv4/sysctl_net_ipv4.c#L424">424</a>         },
<a name="L425" href="source/net/ipv4/sysctl_net_ipv4.c#L425">425</a>         {
<a name="L426" href="source/net/ipv4/sysctl_net_ipv4.c#L426">426</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_max_syn_backlog"</i>,
<a name="L427" href="source/net/ipv4/sysctl_net_ipv4.c#L427">427</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_max_syn_backlog">sysctl_max_syn_backlog</a>,
<a name="L428" href="source/net/ipv4/sysctl_net_ipv4.c#L428">428</a>                 .maxlen         = sizeof(int),
<a name="L429" href="source/net/ipv4/sysctl_net_ipv4.c#L429">429</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L430" href="source/net/ipv4/sysctl_net_ipv4.c#L430">430</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L431" href="source/net/ipv4/sysctl_net_ipv4.c#L431">431</a>         },
<a name="L432" href="source/net/ipv4/sysctl_net_ipv4.c#L432">432</a>         {
<a name="L433" href="source/net/ipv4/sysctl_net_ipv4.c#L433">433</a>                 .<a href="ident?i=procname">procname</a>       = <i>"igmp_max_memberships"</i>,
<a name="L434" href="source/net/ipv4/sysctl_net_ipv4.c#L434">434</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_igmp_max_memberships">sysctl_igmp_max_memberships</a>,
<a name="L435" href="source/net/ipv4/sysctl_net_ipv4.c#L435">435</a>                 .maxlen         = sizeof(int),
<a name="L436" href="source/net/ipv4/sysctl_net_ipv4.c#L436">436</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L437" href="source/net/ipv4/sysctl_net_ipv4.c#L437">437</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L438" href="source/net/ipv4/sysctl_net_ipv4.c#L438">438</a>         },
<a name="L439" href="source/net/ipv4/sysctl_net_ipv4.c#L439">439</a>         {
<a name="L440" href="source/net/ipv4/sysctl_net_ipv4.c#L440">440</a>                 .<a href="ident?i=procname">procname</a>       = <i>"igmp_max_msf"</i>,
<a name="L441" href="source/net/ipv4/sysctl_net_ipv4.c#L441">441</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_igmp_max_msf">sysctl_igmp_max_msf</a>,
<a name="L442" href="source/net/ipv4/sysctl_net_ipv4.c#L442">442</a>                 .maxlen         = sizeof(int),
<a name="L443" href="source/net/ipv4/sysctl_net_ipv4.c#L443">443</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L444" href="source/net/ipv4/sysctl_net_ipv4.c#L444">444</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L445" href="source/net/ipv4/sysctl_net_ipv4.c#L445">445</a>         },
<a name="L446" href="source/net/ipv4/sysctl_net_ipv4.c#L446">446</a> #ifdef CONFIG_IP_MULTICAST
<a name="L447" href="source/net/ipv4/sysctl_net_ipv4.c#L447">447</a>         {
<a name="L448" href="source/net/ipv4/sysctl_net_ipv4.c#L448">448</a>                 .<a href="ident?i=procname">procname</a>       = <i>"igmp_qrv"</i>,
<a name="L449" href="source/net/ipv4/sysctl_net_ipv4.c#L449">449</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>,
<a name="L450" href="source/net/ipv4/sysctl_net_ipv4.c#L450">450</a>                 .maxlen         = sizeof(int),
<a name="L451" href="source/net/ipv4/sysctl_net_ipv4.c#L451">451</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L452" href="source/net/ipv4/sysctl_net_ipv4.c#L452">452</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L453" href="source/net/ipv4/sysctl_net_ipv4.c#L453">453</a>                 .extra1         = &amp;<a href="ident?i=one">one</a>
<a name="L454" href="source/net/ipv4/sysctl_net_ipv4.c#L454">454</a>         },
<a name="L455" href="source/net/ipv4/sysctl_net_ipv4.c#L455">455</a> #endif
<a name="L456" href="source/net/ipv4/sysctl_net_ipv4.c#L456">456</a>         {
<a name="L457" href="source/net/ipv4/sysctl_net_ipv4.c#L457">457</a>                 .<a href="ident?i=procname">procname</a>       = <i>"inet_peer_threshold"</i>,
<a name="L458" href="source/net/ipv4/sysctl_net_ipv4.c#L458">458</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=inet_peer_threshold">inet_peer_threshold</a>,
<a name="L459" href="source/net/ipv4/sysctl_net_ipv4.c#L459">459</a>                 .maxlen         = sizeof(int),
<a name="L460" href="source/net/ipv4/sysctl_net_ipv4.c#L460">460</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L461" href="source/net/ipv4/sysctl_net_ipv4.c#L461">461</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L462" href="source/net/ipv4/sysctl_net_ipv4.c#L462">462</a>         },
<a name="L463" href="source/net/ipv4/sysctl_net_ipv4.c#L463">463</a>         {
<a name="L464" href="source/net/ipv4/sysctl_net_ipv4.c#L464">464</a>                 .<a href="ident?i=procname">procname</a>       = <i>"inet_peer_minttl"</i>,
<a name="L465" href="source/net/ipv4/sysctl_net_ipv4.c#L465">465</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=inet_peer_minttl">inet_peer_minttl</a>,
<a name="L466" href="source/net/ipv4/sysctl_net_ipv4.c#L466">466</a>                 .maxlen         = sizeof(int),
<a name="L467" href="source/net/ipv4/sysctl_net_ipv4.c#L467">467</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L468" href="source/net/ipv4/sysctl_net_ipv4.c#L468">468</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L469" href="source/net/ipv4/sysctl_net_ipv4.c#L469">469</a>         },
<a name="L470" href="source/net/ipv4/sysctl_net_ipv4.c#L470">470</a>         {
<a name="L471" href="source/net/ipv4/sysctl_net_ipv4.c#L471">471</a>                 .<a href="ident?i=procname">procname</a>       = <i>"inet_peer_maxttl"</i>,
<a name="L472" href="source/net/ipv4/sysctl_net_ipv4.c#L472">472</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=inet_peer_maxttl">inet_peer_maxttl</a>,
<a name="L473" href="source/net/ipv4/sysctl_net_ipv4.c#L473">473</a>                 .maxlen         = sizeof(int),
<a name="L474" href="source/net/ipv4/sysctl_net_ipv4.c#L474">474</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L475" href="source/net/ipv4/sysctl_net_ipv4.c#L475">475</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L476" href="source/net/ipv4/sysctl_net_ipv4.c#L476">476</a>         },
<a name="L477" href="source/net/ipv4/sysctl_net_ipv4.c#L477">477</a>         {
<a name="L478" href="source/net/ipv4/sysctl_net_ipv4.c#L478">478</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_orphan_retries"</i>,
<a name="L479" href="source/net/ipv4/sysctl_net_ipv4.c#L479">479</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_orphan_retries">sysctl_tcp_orphan_retries</a>,
<a name="L480" href="source/net/ipv4/sysctl_net_ipv4.c#L480">480</a>                 .maxlen         = sizeof(int),
<a name="L481" href="source/net/ipv4/sysctl_net_ipv4.c#L481">481</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L482" href="source/net/ipv4/sysctl_net_ipv4.c#L482">482</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L483" href="source/net/ipv4/sysctl_net_ipv4.c#L483">483</a>         },
<a name="L484" href="source/net/ipv4/sysctl_net_ipv4.c#L484">484</a>         {
<a name="L485" href="source/net/ipv4/sysctl_net_ipv4.c#L485">485</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_fack"</i>,
<a name="L486" href="source/net/ipv4/sysctl_net_ipv4.c#L486">486</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_fack">sysctl_tcp_fack</a>,
<a name="L487" href="source/net/ipv4/sysctl_net_ipv4.c#L487">487</a>                 .maxlen         = sizeof(int),
<a name="L488" href="source/net/ipv4/sysctl_net_ipv4.c#L488">488</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L489" href="source/net/ipv4/sysctl_net_ipv4.c#L489">489</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L490" href="source/net/ipv4/sysctl_net_ipv4.c#L490">490</a>         },
<a name="L491" href="source/net/ipv4/sysctl_net_ipv4.c#L491">491</a>         {
<a name="L492" href="source/net/ipv4/sysctl_net_ipv4.c#L492">492</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_reordering"</i>,
<a name="L493" href="source/net/ipv4/sysctl_net_ipv4.c#L493">493</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>,
<a name="L494" href="source/net/ipv4/sysctl_net_ipv4.c#L494">494</a>                 .maxlen         = sizeof(int),
<a name="L495" href="source/net/ipv4/sysctl_net_ipv4.c#L495">495</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L496" href="source/net/ipv4/sysctl_net_ipv4.c#L496">496</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L497" href="source/net/ipv4/sysctl_net_ipv4.c#L497">497</a>         },
<a name="L498" href="source/net/ipv4/sysctl_net_ipv4.c#L498">498</a>         {
<a name="L499" href="source/net/ipv4/sysctl_net_ipv4.c#L499">499</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_max_reordering"</i>,
<a name="L500" href="source/net/ipv4/sysctl_net_ipv4.c#L500">500</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_max_reordering">sysctl_tcp_max_reordering</a>,
<a name="L501" href="source/net/ipv4/sysctl_net_ipv4.c#L501">501</a>                 .maxlen         = sizeof(int),
<a name="L502" href="source/net/ipv4/sysctl_net_ipv4.c#L502">502</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L503" href="source/net/ipv4/sysctl_net_ipv4.c#L503">503</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L504" href="source/net/ipv4/sysctl_net_ipv4.c#L504">504</a>         },
<a name="L505" href="source/net/ipv4/sysctl_net_ipv4.c#L505">505</a>         {
<a name="L506" href="source/net/ipv4/sysctl_net_ipv4.c#L506">506</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_dsack"</i>,
<a name="L507" href="source/net/ipv4/sysctl_net_ipv4.c#L507">507</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_dsack">sysctl_tcp_dsack</a>,
<a name="L508" href="source/net/ipv4/sysctl_net_ipv4.c#L508">508</a>                 .maxlen         = sizeof(int),
<a name="L509" href="source/net/ipv4/sysctl_net_ipv4.c#L509">509</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L510" href="source/net/ipv4/sysctl_net_ipv4.c#L510">510</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L511" href="source/net/ipv4/sysctl_net_ipv4.c#L511">511</a>         },
<a name="L512" href="source/net/ipv4/sysctl_net_ipv4.c#L512">512</a>         {
<a name="L513" href="source/net/ipv4/sysctl_net_ipv4.c#L513">513</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_mem"</i>,
<a name="L514" href="source/net/ipv4/sysctl_net_ipv4.c#L514">514</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>),
<a name="L515" href="source/net/ipv4/sysctl_net_ipv4.c#L515">515</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>,
<a name="L516" href="source/net/ipv4/sysctl_net_ipv4.c#L516">516</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L517" href="source/net/ipv4/sysctl_net_ipv4.c#L517">517</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_doulongvec_minmax">proc_doulongvec_minmax</a>,
<a name="L518" href="source/net/ipv4/sysctl_net_ipv4.c#L518">518</a>         },
<a name="L519" href="source/net/ipv4/sysctl_net_ipv4.c#L519">519</a>         {
<a name="L520" href="source/net/ipv4/sysctl_net_ipv4.c#L520">520</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_wmem"</i>,
<a name="L521" href="source/net/ipv4/sysctl_net_ipv4.c#L521">521</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>,
<a name="L522" href="source/net/ipv4/sysctl_net_ipv4.c#L522">522</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>),
<a name="L523" href="source/net/ipv4/sysctl_net_ipv4.c#L523">523</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L524" href="source/net/ipv4/sysctl_net_ipv4.c#L524">524</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L525" href="source/net/ipv4/sysctl_net_ipv4.c#L525">525</a>                 .extra1         = &amp;<a href="ident?i=one">one</a>,
<a name="L526" href="source/net/ipv4/sysctl_net_ipv4.c#L526">526</a>         },
<a name="L527" href="source/net/ipv4/sysctl_net_ipv4.c#L527">527</a>         {
<a name="L528" href="source/net/ipv4/sysctl_net_ipv4.c#L528">528</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_notsent_lowat"</i>,
<a name="L529" href="source/net/ipv4/sysctl_net_ipv4.c#L529">529</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_notsent_lowat">sysctl_tcp_notsent_lowat</a>,
<a name="L530" href="source/net/ipv4/sysctl_net_ipv4.c#L530">530</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_tcp_notsent_lowat">sysctl_tcp_notsent_lowat</a>),
<a name="L531" href="source/net/ipv4/sysctl_net_ipv4.c#L531">531</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L532" href="source/net/ipv4/sysctl_net_ipv4.c#L532">532</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L533" href="source/net/ipv4/sysctl_net_ipv4.c#L533">533</a>         },
<a name="L534" href="source/net/ipv4/sysctl_net_ipv4.c#L534">534</a>         {
<a name="L535" href="source/net/ipv4/sysctl_net_ipv4.c#L535">535</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_rmem"</i>,
<a name="L536" href="source/net/ipv4/sysctl_net_ipv4.c#L536">536</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>,
<a name="L537" href="source/net/ipv4/sysctl_net_ipv4.c#L537">537</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>),
<a name="L538" href="source/net/ipv4/sysctl_net_ipv4.c#L538">538</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L539" href="source/net/ipv4/sysctl_net_ipv4.c#L539">539</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L540" href="source/net/ipv4/sysctl_net_ipv4.c#L540">540</a>                 .extra1         = &amp;<a href="ident?i=one">one</a>,
<a name="L541" href="source/net/ipv4/sysctl_net_ipv4.c#L541">541</a>         },
<a name="L542" href="source/net/ipv4/sysctl_net_ipv4.c#L542">542</a>         {
<a name="L543" href="source/net/ipv4/sysctl_net_ipv4.c#L543">543</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_app_win"</i>,
<a name="L544" href="source/net/ipv4/sysctl_net_ipv4.c#L544">544</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_app_win">sysctl_tcp_app_win</a>,
<a name="L545" href="source/net/ipv4/sysctl_net_ipv4.c#L545">545</a>                 .maxlen         = sizeof(int),
<a name="L546" href="source/net/ipv4/sysctl_net_ipv4.c#L546">546</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L547" href="source/net/ipv4/sysctl_net_ipv4.c#L547">547</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L548" href="source/net/ipv4/sysctl_net_ipv4.c#L548">548</a>         },
<a name="L549" href="source/net/ipv4/sysctl_net_ipv4.c#L549">549</a>         {
<a name="L550" href="source/net/ipv4/sysctl_net_ipv4.c#L550">550</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_adv_win_scale"</i>,
<a name="L551" href="source/net/ipv4/sysctl_net_ipv4.c#L551">551</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_adv_win_scale">sysctl_tcp_adv_win_scale</a>,
<a name="L552" href="source/net/ipv4/sysctl_net_ipv4.c#L552">552</a>                 .maxlen         = sizeof(int),
<a name="L553" href="source/net/ipv4/sysctl_net_ipv4.c#L553">553</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L554" href="source/net/ipv4/sysctl_net_ipv4.c#L554">554</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L555" href="source/net/ipv4/sysctl_net_ipv4.c#L555">555</a>                 .extra1         = &amp;<a href="ident?i=tcp_adv_win_scale_min">tcp_adv_win_scale_min</a>,
<a name="L556" href="source/net/ipv4/sysctl_net_ipv4.c#L556">556</a>                 .extra2         = &amp;<a href="ident?i=tcp_adv_win_scale_max">tcp_adv_win_scale_max</a>,
<a name="L557" href="source/net/ipv4/sysctl_net_ipv4.c#L557">557</a>         },
<a name="L558" href="source/net/ipv4/sysctl_net_ipv4.c#L558">558</a>         {
<a name="L559" href="source/net/ipv4/sysctl_net_ipv4.c#L559">559</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_tw_reuse"</i>,
<a name="L560" href="source/net/ipv4/sysctl_net_ipv4.c#L560">560</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_tw_reuse">sysctl_tcp_tw_reuse</a>,
<a name="L561" href="source/net/ipv4/sysctl_net_ipv4.c#L561">561</a>                 .maxlen         = sizeof(int),
<a name="L562" href="source/net/ipv4/sysctl_net_ipv4.c#L562">562</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L563" href="source/net/ipv4/sysctl_net_ipv4.c#L563">563</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L564" href="source/net/ipv4/sysctl_net_ipv4.c#L564">564</a>         },
<a name="L565" href="source/net/ipv4/sysctl_net_ipv4.c#L565">565</a>         {
<a name="L566" href="source/net/ipv4/sysctl_net_ipv4.c#L566">566</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_frto"</i>,
<a name="L567" href="source/net/ipv4/sysctl_net_ipv4.c#L567">567</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_frto">sysctl_tcp_frto</a>,
<a name="L568" href="source/net/ipv4/sysctl_net_ipv4.c#L568">568</a>                 .maxlen         = sizeof(int),
<a name="L569" href="source/net/ipv4/sysctl_net_ipv4.c#L569">569</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L570" href="source/net/ipv4/sysctl_net_ipv4.c#L570">570</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L571" href="source/net/ipv4/sysctl_net_ipv4.c#L571">571</a>         },
<a name="L572" href="source/net/ipv4/sysctl_net_ipv4.c#L572">572</a>         {
<a name="L573" href="source/net/ipv4/sysctl_net_ipv4.c#L573">573</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_low_latency"</i>,
<a name="L574" href="source/net/ipv4/sysctl_net_ipv4.c#L574">574</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_low_latency">sysctl_tcp_low_latency</a>,
<a name="L575" href="source/net/ipv4/sysctl_net_ipv4.c#L575">575</a>                 .maxlen         = sizeof(int),
<a name="L576" href="source/net/ipv4/sysctl_net_ipv4.c#L576">576</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L577" href="source/net/ipv4/sysctl_net_ipv4.c#L577">577</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L578" href="source/net/ipv4/sysctl_net_ipv4.c#L578">578</a>         },
<a name="L579" href="source/net/ipv4/sysctl_net_ipv4.c#L579">579</a>         {
<a name="L580" href="source/net/ipv4/sysctl_net_ipv4.c#L580">580</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_no_metrics_save"</i>,
<a name="L581" href="source/net/ipv4/sysctl_net_ipv4.c#L581">581</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_nometrics_save">sysctl_tcp_nometrics_save</a>,
<a name="L582" href="source/net/ipv4/sysctl_net_ipv4.c#L582">582</a>                 .maxlen         = sizeof(int),
<a name="L583" href="source/net/ipv4/sysctl_net_ipv4.c#L583">583</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L584" href="source/net/ipv4/sysctl_net_ipv4.c#L584">584</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L585" href="source/net/ipv4/sysctl_net_ipv4.c#L585">585</a>         },
<a name="L586" href="source/net/ipv4/sysctl_net_ipv4.c#L586">586</a>         {
<a name="L587" href="source/net/ipv4/sysctl_net_ipv4.c#L587">587</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_moderate_rcvbuf"</i>,
<a name="L588" href="source/net/ipv4/sysctl_net_ipv4.c#L588">588</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_moderate_rcvbuf">sysctl_tcp_moderate_rcvbuf</a>,
<a name="L589" href="source/net/ipv4/sysctl_net_ipv4.c#L589">589</a>                 .maxlen         = sizeof(int),
<a name="L590" href="source/net/ipv4/sysctl_net_ipv4.c#L590">590</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L591" href="source/net/ipv4/sysctl_net_ipv4.c#L591">591</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L592" href="source/net/ipv4/sysctl_net_ipv4.c#L592">592</a>         },
<a name="L593" href="source/net/ipv4/sysctl_net_ipv4.c#L593">593</a>         {
<a name="L594" href="source/net/ipv4/sysctl_net_ipv4.c#L594">594</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_tso_win_divisor"</i>,
<a name="L595" href="source/net/ipv4/sysctl_net_ipv4.c#L595">595</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_tso_win_divisor">sysctl_tcp_tso_win_divisor</a>,
<a name="L596" href="source/net/ipv4/sysctl_net_ipv4.c#L596">596</a>                 .maxlen         = sizeof(int),
<a name="L597" href="source/net/ipv4/sysctl_net_ipv4.c#L597">597</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L598" href="source/net/ipv4/sysctl_net_ipv4.c#L598">598</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L599" href="source/net/ipv4/sysctl_net_ipv4.c#L599">599</a>         },
<a name="L600" href="source/net/ipv4/sysctl_net_ipv4.c#L600">600</a>         {
<a name="L601" href="source/net/ipv4/sysctl_net_ipv4.c#L601">601</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_congestion_control"</i>,
<a name="L602" href="source/net/ipv4/sysctl_net_ipv4.c#L602">602</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L603" href="source/net/ipv4/sysctl_net_ipv4.c#L603">603</a>                 .maxlen         = <a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>,
<a name="L604" href="source/net/ipv4/sysctl_net_ipv4.c#L604">604</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_tcp_congestion_control">proc_tcp_congestion_control</a>,
<a name="L605" href="source/net/ipv4/sysctl_net_ipv4.c#L605">605</a>         },
<a name="L606" href="source/net/ipv4/sysctl_net_ipv4.c#L606">606</a>         {
<a name="L607" href="source/net/ipv4/sysctl_net_ipv4.c#L607">607</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_workaround_signed_windows"</i>,
<a name="L608" href="source/net/ipv4/sysctl_net_ipv4.c#L608">608</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_workaround_signed_windows">sysctl_tcp_workaround_signed_windows</a>,
<a name="L609" href="source/net/ipv4/sysctl_net_ipv4.c#L609">609</a>                 .maxlen         = sizeof(int),
<a name="L610" href="source/net/ipv4/sysctl_net_ipv4.c#L610">610</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L611" href="source/net/ipv4/sysctl_net_ipv4.c#L611">611</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L612" href="source/net/ipv4/sysctl_net_ipv4.c#L612">612</a>         },
<a name="L613" href="source/net/ipv4/sysctl_net_ipv4.c#L613">613</a>         {
<a name="L614" href="source/net/ipv4/sysctl_net_ipv4.c#L614">614</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_limit_output_bytes"</i>,
<a name="L615" href="source/net/ipv4/sysctl_net_ipv4.c#L615">615</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_limit_output_bytes">sysctl_tcp_limit_output_bytes</a>,
<a name="L616" href="source/net/ipv4/sysctl_net_ipv4.c#L616">616</a>                 .maxlen         = sizeof(int),
<a name="L617" href="source/net/ipv4/sysctl_net_ipv4.c#L617">617</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L618" href="source/net/ipv4/sysctl_net_ipv4.c#L618">618</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L619" href="source/net/ipv4/sysctl_net_ipv4.c#L619">619</a>         },
<a name="L620" href="source/net/ipv4/sysctl_net_ipv4.c#L620">620</a>         {
<a name="L621" href="source/net/ipv4/sysctl_net_ipv4.c#L621">621</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_challenge_ack_limit"</i>,
<a name="L622" href="source/net/ipv4/sysctl_net_ipv4.c#L622">622</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_challenge_ack_limit">sysctl_tcp_challenge_ack_limit</a>,
<a name="L623" href="source/net/ipv4/sysctl_net_ipv4.c#L623">623</a>                 .maxlen         = sizeof(int),
<a name="L624" href="source/net/ipv4/sysctl_net_ipv4.c#L624">624</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L625" href="source/net/ipv4/sysctl_net_ipv4.c#L625">625</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L626" href="source/net/ipv4/sysctl_net_ipv4.c#L626">626</a>         },
<a name="L627" href="source/net/ipv4/sysctl_net_ipv4.c#L627">627</a>         {
<a name="L628" href="source/net/ipv4/sysctl_net_ipv4.c#L628">628</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_slow_start_after_idle"</i>,
<a name="L629" href="source/net/ipv4/sysctl_net_ipv4.c#L629">629</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_slow_start_after_idle">sysctl_tcp_slow_start_after_idle</a>,
<a name="L630" href="source/net/ipv4/sysctl_net_ipv4.c#L630">630</a>                 .maxlen         = sizeof(int),
<a name="L631" href="source/net/ipv4/sysctl_net_ipv4.c#L631">631</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L632" href="source/net/ipv4/sysctl_net_ipv4.c#L632">632</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L633" href="source/net/ipv4/sysctl_net_ipv4.c#L633">633</a>         },
<a name="L634" href="source/net/ipv4/sysctl_net_ipv4.c#L634">634</a> #ifdef CONFIG_NETLABEL
<a name="L635" href="source/net/ipv4/sysctl_net_ipv4.c#L635">635</a>         {
<a name="L636" href="source/net/ipv4/sysctl_net_ipv4.c#L636">636</a>                 .<a href="ident?i=procname">procname</a>       = <i>"cipso_cache_enable"</i>,
<a name="L637" href="source/net/ipv4/sysctl_net_ipv4.c#L637">637</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=cipso_v4_cache_enabled">cipso_v4_cache_enabled</a>,
<a name="L638" href="source/net/ipv4/sysctl_net_ipv4.c#L638">638</a>                 .maxlen         = sizeof(int),
<a name="L639" href="source/net/ipv4/sysctl_net_ipv4.c#L639">639</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L640" href="source/net/ipv4/sysctl_net_ipv4.c#L640">640</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L641" href="source/net/ipv4/sysctl_net_ipv4.c#L641">641</a>         },
<a name="L642" href="source/net/ipv4/sysctl_net_ipv4.c#L642">642</a>         {
<a name="L643" href="source/net/ipv4/sysctl_net_ipv4.c#L643">643</a>                 .<a href="ident?i=procname">procname</a>       = <i>"cipso_cache_bucket_size"</i>,
<a name="L644" href="source/net/ipv4/sysctl_net_ipv4.c#L644">644</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=cipso_v4_cache_bucketsize">cipso_v4_cache_bucketsize</a>,
<a name="L645" href="source/net/ipv4/sysctl_net_ipv4.c#L645">645</a>                 .maxlen         = sizeof(int),
<a name="L646" href="source/net/ipv4/sysctl_net_ipv4.c#L646">646</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L647" href="source/net/ipv4/sysctl_net_ipv4.c#L647">647</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L648" href="source/net/ipv4/sysctl_net_ipv4.c#L648">648</a>         },
<a name="L649" href="source/net/ipv4/sysctl_net_ipv4.c#L649">649</a>         {
<a name="L650" href="source/net/ipv4/sysctl_net_ipv4.c#L650">650</a>                 .<a href="ident?i=procname">procname</a>       = <i>"cipso_rbm_optfmt"</i>,
<a name="L651" href="source/net/ipv4/sysctl_net_ipv4.c#L651">651</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=cipso_v4_rbm_optfmt">cipso_v4_rbm_optfmt</a>,
<a name="L652" href="source/net/ipv4/sysctl_net_ipv4.c#L652">652</a>                 .maxlen         = sizeof(int),
<a name="L653" href="source/net/ipv4/sysctl_net_ipv4.c#L653">653</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L654" href="source/net/ipv4/sysctl_net_ipv4.c#L654">654</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L655" href="source/net/ipv4/sysctl_net_ipv4.c#L655">655</a>         },
<a name="L656" href="source/net/ipv4/sysctl_net_ipv4.c#L656">656</a>         {
<a name="L657" href="source/net/ipv4/sysctl_net_ipv4.c#L657">657</a>                 .<a href="ident?i=procname">procname</a>       = <i>"cipso_rbm_strictvalid"</i>,
<a name="L658" href="source/net/ipv4/sysctl_net_ipv4.c#L658">658</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=cipso_v4_rbm_strictvalid">cipso_v4_rbm_strictvalid</a>,
<a name="L659" href="source/net/ipv4/sysctl_net_ipv4.c#L659">659</a>                 .maxlen         = sizeof(int),
<a name="L660" href="source/net/ipv4/sysctl_net_ipv4.c#L660">660</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L661" href="source/net/ipv4/sysctl_net_ipv4.c#L661">661</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L662" href="source/net/ipv4/sysctl_net_ipv4.c#L662">662</a>         },
<a name="L663" href="source/net/ipv4/sysctl_net_ipv4.c#L663">663</a> #endif <b><i>/* CONFIG_NETLABEL */</i></b>
<a name="L664" href="source/net/ipv4/sysctl_net_ipv4.c#L664">664</a>         {
<a name="L665" href="source/net/ipv4/sysctl_net_ipv4.c#L665">665</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_available_congestion_control"</i>,
<a name="L666" href="source/net/ipv4/sysctl_net_ipv4.c#L666">666</a>                 .maxlen         = <a href="ident?i=TCP_CA_BUF_MAX">TCP_CA_BUF_MAX</a>,
<a name="L667" href="source/net/ipv4/sysctl_net_ipv4.c#L667">667</a>                 .<a href="ident?i=mode">mode</a>           = 0444,
<a name="L668" href="source/net/ipv4/sysctl_net_ipv4.c#L668">668</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_tcp_available_congestion_control">proc_tcp_available_congestion_control</a>,
<a name="L669" href="source/net/ipv4/sysctl_net_ipv4.c#L669">669</a>         },
<a name="L670" href="source/net/ipv4/sysctl_net_ipv4.c#L670">670</a>         {
<a name="L671" href="source/net/ipv4/sysctl_net_ipv4.c#L671">671</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_allowed_congestion_control"</i>,
<a name="L672" href="source/net/ipv4/sysctl_net_ipv4.c#L672">672</a>                 .maxlen         = <a href="ident?i=TCP_CA_BUF_MAX">TCP_CA_BUF_MAX</a>,
<a name="L673" href="source/net/ipv4/sysctl_net_ipv4.c#L673">673</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L674" href="source/net/ipv4/sysctl_net_ipv4.c#L674">674</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_allowed_congestion_control">proc_allowed_congestion_control</a>,
<a name="L675" href="source/net/ipv4/sysctl_net_ipv4.c#L675">675</a>         },
<a name="L676" href="source/net/ipv4/sysctl_net_ipv4.c#L676">676</a>         {
<a name="L677" href="source/net/ipv4/sysctl_net_ipv4.c#L677">677</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_thin_linear_timeouts"</i>,
<a name="L678" href="source/net/ipv4/sysctl_net_ipv4.c#L678">678</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_thin_linear_timeouts">sysctl_tcp_thin_linear_timeouts</a>,
<a name="L679" href="source/net/ipv4/sysctl_net_ipv4.c#L679">679</a>                 .maxlen         = sizeof(int),
<a name="L680" href="source/net/ipv4/sysctl_net_ipv4.c#L680">680</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L681" href="source/net/ipv4/sysctl_net_ipv4.c#L681">681</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L682" href="source/net/ipv4/sysctl_net_ipv4.c#L682">682</a>         },
<a name="L683" href="source/net/ipv4/sysctl_net_ipv4.c#L683">683</a>         {
<a name="L684" href="source/net/ipv4/sysctl_net_ipv4.c#L684">684</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_thin_dupack"</i>,
<a name="L685" href="source/net/ipv4/sysctl_net_ipv4.c#L685">685</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_thin_dupack">sysctl_tcp_thin_dupack</a>,
<a name="L686" href="source/net/ipv4/sysctl_net_ipv4.c#L686">686</a>                 .maxlen         = sizeof(int),
<a name="L687" href="source/net/ipv4/sysctl_net_ipv4.c#L687">687</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L688" href="source/net/ipv4/sysctl_net_ipv4.c#L688">688</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L689" href="source/net/ipv4/sysctl_net_ipv4.c#L689">689</a>         },
<a name="L690" href="source/net/ipv4/sysctl_net_ipv4.c#L690">690</a>         {
<a name="L691" href="source/net/ipv4/sysctl_net_ipv4.c#L691">691</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_early_retrans"</i>,
<a name="L692" href="source/net/ipv4/sysctl_net_ipv4.c#L692">692</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_early_retrans">sysctl_tcp_early_retrans</a>,
<a name="L693" href="source/net/ipv4/sysctl_net_ipv4.c#L693">693</a>                 .maxlen         = sizeof(int),
<a name="L694" href="source/net/ipv4/sysctl_net_ipv4.c#L694">694</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L695" href="source/net/ipv4/sysctl_net_ipv4.c#L695">695</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L696" href="source/net/ipv4/sysctl_net_ipv4.c#L696">696</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>,
<a name="L697" href="source/net/ipv4/sysctl_net_ipv4.c#L697">697</a>                 .extra2         = &amp;<a href="ident?i=four">four</a>,
<a name="L698" href="source/net/ipv4/sysctl_net_ipv4.c#L698">698</a>         },
<a name="L699" href="source/net/ipv4/sysctl_net_ipv4.c#L699">699</a>         {
<a name="L700" href="source/net/ipv4/sysctl_net_ipv4.c#L700">700</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_min_tso_segs"</i>,
<a name="L701" href="source/net/ipv4/sysctl_net_ipv4.c#L701">701</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_min_tso_segs">sysctl_tcp_min_tso_segs</a>,
<a name="L702" href="source/net/ipv4/sysctl_net_ipv4.c#L702">702</a>                 .maxlen         = sizeof(int),
<a name="L703" href="source/net/ipv4/sysctl_net_ipv4.c#L703">703</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L704" href="source/net/ipv4/sysctl_net_ipv4.c#L704">704</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L705" href="source/net/ipv4/sysctl_net_ipv4.c#L705">705</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>,
<a name="L706" href="source/net/ipv4/sysctl_net_ipv4.c#L706">706</a>                 .extra2         = &amp;<a href="ident?i=gso_max_segs">gso_max_segs</a>,
<a name="L707" href="source/net/ipv4/sysctl_net_ipv4.c#L707">707</a>         },
<a name="L708" href="source/net/ipv4/sysctl_net_ipv4.c#L708">708</a>         {
<a name="L709" href="source/net/ipv4/sysctl_net_ipv4.c#L709">709</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_autocorking"</i>,
<a name="L710" href="source/net/ipv4/sysctl_net_ipv4.c#L710">710</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_autocorking">sysctl_tcp_autocorking</a>,
<a name="L711" href="source/net/ipv4/sysctl_net_ipv4.c#L711">711</a>                 .maxlen         = sizeof(int),
<a name="L712" href="source/net/ipv4/sysctl_net_ipv4.c#L712">712</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L713" href="source/net/ipv4/sysctl_net_ipv4.c#L713">713</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L714" href="source/net/ipv4/sysctl_net_ipv4.c#L714">714</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>,
<a name="L715" href="source/net/ipv4/sysctl_net_ipv4.c#L715">715</a>                 .extra2         = &amp;<a href="ident?i=one">one</a>,
<a name="L716" href="source/net/ipv4/sysctl_net_ipv4.c#L716">716</a>         },
<a name="L717" href="source/net/ipv4/sysctl_net_ipv4.c#L717">717</a>         {
<a name="L718" href="source/net/ipv4/sysctl_net_ipv4.c#L718">718</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_invalid_ratelimit"</i>,
<a name="L719" href="source/net/ipv4/sysctl_net_ipv4.c#L719">719</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_tcp_invalid_ratelimit">sysctl_tcp_invalid_ratelimit</a>,
<a name="L720" href="source/net/ipv4/sysctl_net_ipv4.c#L720">720</a>                 .maxlen         = sizeof(int),
<a name="L721" href="source/net/ipv4/sysctl_net_ipv4.c#L721">721</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L722" href="source/net/ipv4/sysctl_net_ipv4.c#L722">722</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_ms_jiffies">proc_dointvec_ms_jiffies</a>,
<a name="L723" href="source/net/ipv4/sysctl_net_ipv4.c#L723">723</a>         },
<a name="L724" href="source/net/ipv4/sysctl_net_ipv4.c#L724">724</a>         {
<a name="L725" href="source/net/ipv4/sysctl_net_ipv4.c#L725">725</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_msgs_per_sec"</i>,
<a name="L726" href="source/net/ipv4/sysctl_net_ipv4.c#L726">726</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_icmp_msgs_per_sec">sysctl_icmp_msgs_per_sec</a>,
<a name="L727" href="source/net/ipv4/sysctl_net_ipv4.c#L727">727</a>                 .maxlen         = sizeof(int),
<a name="L728" href="source/net/ipv4/sysctl_net_ipv4.c#L728">728</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L729" href="source/net/ipv4/sysctl_net_ipv4.c#L729">729</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L730" href="source/net/ipv4/sysctl_net_ipv4.c#L730">730</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>,
<a name="L731" href="source/net/ipv4/sysctl_net_ipv4.c#L731">731</a>         },
<a name="L732" href="source/net/ipv4/sysctl_net_ipv4.c#L732">732</a>         {
<a name="L733" href="source/net/ipv4/sysctl_net_ipv4.c#L733">733</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_msgs_burst"</i>,
<a name="L734" href="source/net/ipv4/sysctl_net_ipv4.c#L734">734</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_icmp_msgs_burst">sysctl_icmp_msgs_burst</a>,
<a name="L735" href="source/net/ipv4/sysctl_net_ipv4.c#L735">735</a>                 .maxlen         = sizeof(int),
<a name="L736" href="source/net/ipv4/sysctl_net_ipv4.c#L736">736</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L737" href="source/net/ipv4/sysctl_net_ipv4.c#L737">737</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L738" href="source/net/ipv4/sysctl_net_ipv4.c#L738">738</a>                 .extra1         = &amp;<a href="ident?i=zero">zero</a>,
<a name="L739" href="source/net/ipv4/sysctl_net_ipv4.c#L739">739</a>         },
<a name="L740" href="source/net/ipv4/sysctl_net_ipv4.c#L740">740</a>         {
<a name="L741" href="source/net/ipv4/sysctl_net_ipv4.c#L741">741</a>                 .<a href="ident?i=procname">procname</a>       = <i>"udp_mem"</i>,
<a name="L742" href="source/net/ipv4/sysctl_net_ipv4.c#L742">742</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>,
<a name="L743" href="source/net/ipv4/sysctl_net_ipv4.c#L743">743</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>),
<a name="L744" href="source/net/ipv4/sysctl_net_ipv4.c#L744">744</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L745" href="source/net/ipv4/sysctl_net_ipv4.c#L745">745</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_doulongvec_minmax">proc_doulongvec_minmax</a>,
<a name="L746" href="source/net/ipv4/sysctl_net_ipv4.c#L746">746</a>         },
<a name="L747" href="source/net/ipv4/sysctl_net_ipv4.c#L747">747</a>         {
<a name="L748" href="source/net/ipv4/sysctl_net_ipv4.c#L748">748</a>                 .<a href="ident?i=procname">procname</a>       = <i>"udp_rmem_min"</i>,
<a name="L749" href="source/net/ipv4/sysctl_net_ipv4.c#L749">749</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_udp_rmem_min">sysctl_udp_rmem_min</a>,
<a name="L750" href="source/net/ipv4/sysctl_net_ipv4.c#L750">750</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_udp_rmem_min">sysctl_udp_rmem_min</a>),
<a name="L751" href="source/net/ipv4/sysctl_net_ipv4.c#L751">751</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L752" href="source/net/ipv4/sysctl_net_ipv4.c#L752">752</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L753" href="source/net/ipv4/sysctl_net_ipv4.c#L753">753</a>                 .extra1         = &amp;<a href="ident?i=one">one</a>
<a name="L754" href="source/net/ipv4/sysctl_net_ipv4.c#L754">754</a>         },
<a name="L755" href="source/net/ipv4/sysctl_net_ipv4.c#L755">755</a>         {
<a name="L756" href="source/net/ipv4/sysctl_net_ipv4.c#L756">756</a>                 .<a href="ident?i=procname">procname</a>       = <i>"udp_wmem_min"</i>,
<a name="L757" href="source/net/ipv4/sysctl_net_ipv4.c#L757">757</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=sysctl_udp_wmem_min">sysctl_udp_wmem_min</a>,
<a name="L758" href="source/net/ipv4/sysctl_net_ipv4.c#L758">758</a>                 .maxlen         = sizeof(<a href="ident?i=sysctl_udp_wmem_min">sysctl_udp_wmem_min</a>),
<a name="L759" href="source/net/ipv4/sysctl_net_ipv4.c#L759">759</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L760" href="source/net/ipv4/sysctl_net_ipv4.c#L760">760</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_minmax">proc_dointvec_minmax</a>,
<a name="L761" href="source/net/ipv4/sysctl_net_ipv4.c#L761">761</a>                 .extra1         = &amp;<a href="ident?i=one">one</a>
<a name="L762" href="source/net/ipv4/sysctl_net_ipv4.c#L762">762</a>         },
<a name="L763" href="source/net/ipv4/sysctl_net_ipv4.c#L763">763</a>         { }
<a name="L764" href="source/net/ipv4/sysctl_net_ipv4.c#L764">764</a> };
<a name="L765" href="source/net/ipv4/sysctl_net_ipv4.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/sysctl_net_ipv4.c#L766">766</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ipv4_net_table">ipv4_net_table</a>[] = {
<a name="L767" href="source/net/ipv4/sysctl_net_ipv4.c#L767">767</a>         {
<a name="L768" href="source/net/ipv4/sysctl_net_ipv4.c#L768">768</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_echo_ignore_all"</i>,
<a name="L769" href="source/net/ipv4/sysctl_net_ipv4.c#L769">769</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_icmp_echo_ignore_all,
<a name="L770" href="source/net/ipv4/sysctl_net_ipv4.c#L770">770</a>                 .maxlen         = sizeof(int),
<a name="L771" href="source/net/ipv4/sysctl_net_ipv4.c#L771">771</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L772" href="source/net/ipv4/sysctl_net_ipv4.c#L772">772</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L773" href="source/net/ipv4/sysctl_net_ipv4.c#L773">773</a>         },
<a name="L774" href="source/net/ipv4/sysctl_net_ipv4.c#L774">774</a>         {
<a name="L775" href="source/net/ipv4/sysctl_net_ipv4.c#L775">775</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_echo_ignore_broadcasts"</i>,
<a name="L776" href="source/net/ipv4/sysctl_net_ipv4.c#L776">776</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_icmp_echo_ignore_broadcasts,
<a name="L777" href="source/net/ipv4/sysctl_net_ipv4.c#L777">777</a>                 .maxlen         = sizeof(int),
<a name="L778" href="source/net/ipv4/sysctl_net_ipv4.c#L778">778</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L779" href="source/net/ipv4/sysctl_net_ipv4.c#L779">779</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L780" href="source/net/ipv4/sysctl_net_ipv4.c#L780">780</a>         },
<a name="L781" href="source/net/ipv4/sysctl_net_ipv4.c#L781">781</a>         {
<a name="L782" href="source/net/ipv4/sysctl_net_ipv4.c#L782">782</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_ignore_bogus_error_responses"</i>,
<a name="L783" href="source/net/ipv4/sysctl_net_ipv4.c#L783">783</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_icmp_ignore_bogus_error_responses,
<a name="L784" href="source/net/ipv4/sysctl_net_ipv4.c#L784">784</a>                 .maxlen         = sizeof(int),
<a name="L785" href="source/net/ipv4/sysctl_net_ipv4.c#L785">785</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L786" href="source/net/ipv4/sysctl_net_ipv4.c#L786">786</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L787" href="source/net/ipv4/sysctl_net_ipv4.c#L787">787</a>         },
<a name="L788" href="source/net/ipv4/sysctl_net_ipv4.c#L788">788</a>         {
<a name="L789" href="source/net/ipv4/sysctl_net_ipv4.c#L789">789</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_errors_use_inbound_ifaddr"</i>,
<a name="L790" href="source/net/ipv4/sysctl_net_ipv4.c#L790">790</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_icmp_errors_use_inbound_ifaddr,
<a name="L791" href="source/net/ipv4/sysctl_net_ipv4.c#L791">791</a>                 .maxlen         = sizeof(int),
<a name="L792" href="source/net/ipv4/sysctl_net_ipv4.c#L792">792</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L793" href="source/net/ipv4/sysctl_net_ipv4.c#L793">793</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L794" href="source/net/ipv4/sysctl_net_ipv4.c#L794">794</a>         },
<a name="L795" href="source/net/ipv4/sysctl_net_ipv4.c#L795">795</a>         {
<a name="L796" href="source/net/ipv4/sysctl_net_ipv4.c#L796">796</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_ratelimit"</i>,
<a name="L797" href="source/net/ipv4/sysctl_net_ipv4.c#L797">797</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_icmp_ratelimit,
<a name="L798" href="source/net/ipv4/sysctl_net_ipv4.c#L798">798</a>                 .maxlen         = sizeof(int),
<a name="L799" href="source/net/ipv4/sysctl_net_ipv4.c#L799">799</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L800" href="source/net/ipv4/sysctl_net_ipv4.c#L800">800</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_ms_jiffies">proc_dointvec_ms_jiffies</a>,
<a name="L801" href="source/net/ipv4/sysctl_net_ipv4.c#L801">801</a>         },
<a name="L802" href="source/net/ipv4/sysctl_net_ipv4.c#L802">802</a>         {
<a name="L803" href="source/net/ipv4/sysctl_net_ipv4.c#L803">803</a>                 .<a href="ident?i=procname">procname</a>       = <i>"icmp_ratemask"</i>,
<a name="L804" href="source/net/ipv4/sysctl_net_ipv4.c#L804">804</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_icmp_ratemask,
<a name="L805" href="source/net/ipv4/sysctl_net_ipv4.c#L805">805</a>                 .maxlen         = sizeof(int),
<a name="L806" href="source/net/ipv4/sysctl_net_ipv4.c#L806">806</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L807" href="source/net/ipv4/sysctl_net_ipv4.c#L807">807</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L808" href="source/net/ipv4/sysctl_net_ipv4.c#L808">808</a>         },
<a name="L809" href="source/net/ipv4/sysctl_net_ipv4.c#L809">809</a>         {
<a name="L810" href="source/net/ipv4/sysctl_net_ipv4.c#L810">810</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ping_group_range"</i>,
<a name="L811" href="source/net/ipv4/sysctl_net_ipv4.c#L811">811</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=range">range</a>,
<a name="L812" href="source/net/ipv4/sysctl_net_ipv4.c#L812">812</a>                 .maxlen         = sizeof(<a href="ident?i=gid_t">gid_t</a>)*2,
<a name="L813" href="source/net/ipv4/sysctl_net_ipv4.c#L813">813</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L814" href="source/net/ipv4/sysctl_net_ipv4.c#L814">814</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=ipv4_ping_group_range">ipv4_ping_group_range</a>,
<a name="L815" href="source/net/ipv4/sysctl_net_ipv4.c#L815">815</a>         },
<a name="L816" href="source/net/ipv4/sysctl_net_ipv4.c#L816">816</a>         {
<a name="L817" href="source/net/ipv4/sysctl_net_ipv4.c#L817">817</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_ecn"</i>,
<a name="L818" href="source/net/ipv4/sysctl_net_ipv4.c#L818">818</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_tcp_ecn,
<a name="L819" href="source/net/ipv4/sysctl_net_ipv4.c#L819">819</a>                 .maxlen         = sizeof(int),
<a name="L820" href="source/net/ipv4/sysctl_net_ipv4.c#L820">820</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L821" href="source/net/ipv4/sysctl_net_ipv4.c#L821">821</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L822" href="source/net/ipv4/sysctl_net_ipv4.c#L822">822</a>         },
<a name="L823" href="source/net/ipv4/sysctl_net_ipv4.c#L823">823</a>         {
<a name="L824" href="source/net/ipv4/sysctl_net_ipv4.c#L824">824</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_local_port_range"</i>,
<a name="L825" href="source/net/ipv4/sysctl_net_ipv4.c#L825">825</a>                 .maxlen         = sizeof(<a href="ident?i=init_net">init_net</a>.ipv4.ip_local_ports.<a href="ident?i=range">range</a>),
<a name="L826" href="source/net/ipv4/sysctl_net_ipv4.c#L826">826</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.ip_local_ports.<a href="ident?i=range">range</a>,
<a name="L827" href="source/net/ipv4/sysctl_net_ipv4.c#L827">827</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L828" href="source/net/ipv4/sysctl_net_ipv4.c#L828">828</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=ipv4_local_port_range">ipv4_local_port_range</a>,
<a name="L829" href="source/net/ipv4/sysctl_net_ipv4.c#L829">829</a>         },
<a name="L830" href="source/net/ipv4/sysctl_net_ipv4.c#L830">830</a>         {
<a name="L831" href="source/net/ipv4/sysctl_net_ipv4.c#L831">831</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_local_reserved_ports"</i>,
<a name="L832" href="source/net/ipv4/sysctl_net_ipv4.c#L832">832</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_local_reserved_ports,
<a name="L833" href="source/net/ipv4/sysctl_net_ipv4.c#L833">833</a>                 .maxlen         = 65536,
<a name="L834" href="source/net/ipv4/sysctl_net_ipv4.c#L834">834</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L835" href="source/net/ipv4/sysctl_net_ipv4.c#L835">835</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_do_large_bitmap">proc_do_large_bitmap</a>,
<a name="L836" href="source/net/ipv4/sysctl_net_ipv4.c#L836">836</a>         },
<a name="L837" href="source/net/ipv4/sysctl_net_ipv4.c#L837">837</a>         {
<a name="L838" href="source/net/ipv4/sysctl_net_ipv4.c#L838">838</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_no_pmtu_disc"</i>,
<a name="L839" href="source/net/ipv4/sysctl_net_ipv4.c#L839">839</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_ip_no_pmtu_disc,
<a name="L840" href="source/net/ipv4/sysctl_net_ipv4.c#L840">840</a>                 .maxlen         = sizeof(int),
<a name="L841" href="source/net/ipv4/sysctl_net_ipv4.c#L841">841</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L842" href="source/net/ipv4/sysctl_net_ipv4.c#L842">842</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L843" href="source/net/ipv4/sysctl_net_ipv4.c#L843">843</a>         },
<a name="L844" href="source/net/ipv4/sysctl_net_ipv4.c#L844">844</a>         {
<a name="L845" href="source/net/ipv4/sysctl_net_ipv4.c#L845">845</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_forward_use_pmtu"</i>,
<a name="L846" href="source/net/ipv4/sysctl_net_ipv4.c#L846">846</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_ip_fwd_use_pmtu,
<a name="L847" href="source/net/ipv4/sysctl_net_ipv4.c#L847">847</a>                 .maxlen         = sizeof(int),
<a name="L848" href="source/net/ipv4/sysctl_net_ipv4.c#L848">848</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L849" href="source/net/ipv4/sysctl_net_ipv4.c#L849">849</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L850" href="source/net/ipv4/sysctl_net_ipv4.c#L850">850</a>         },
<a name="L851" href="source/net/ipv4/sysctl_net_ipv4.c#L851">851</a>         {
<a name="L852" href="source/net/ipv4/sysctl_net_ipv4.c#L852">852</a>                 .<a href="ident?i=procname">procname</a>       = <i>"ip_nonlocal_bind"</i>,
<a name="L853" href="source/net/ipv4/sysctl_net_ipv4.c#L853">853</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_ip_nonlocal_bind,
<a name="L854" href="source/net/ipv4/sysctl_net_ipv4.c#L854">854</a>                 .maxlen         = sizeof(int),
<a name="L855" href="source/net/ipv4/sysctl_net_ipv4.c#L855">855</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L856" href="source/net/ipv4/sysctl_net_ipv4.c#L856">856</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>
<a name="L857" href="source/net/ipv4/sysctl_net_ipv4.c#L857">857</a>         },
<a name="L858" href="source/net/ipv4/sysctl_net_ipv4.c#L858">858</a>         {
<a name="L859" href="source/net/ipv4/sysctl_net_ipv4.c#L859">859</a>                 .<a href="ident?i=procname">procname</a>       = <i>"fwmark_reflect"</i>,
<a name="L860" href="source/net/ipv4/sysctl_net_ipv4.c#L860">860</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_fwmark_reflect,
<a name="L861" href="source/net/ipv4/sysctl_net_ipv4.c#L861">861</a>                 .maxlen         = sizeof(int),
<a name="L862" href="source/net/ipv4/sysctl_net_ipv4.c#L862">862</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L863" href="source/net/ipv4/sysctl_net_ipv4.c#L863">863</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L864" href="source/net/ipv4/sysctl_net_ipv4.c#L864">864</a>         },
<a name="L865" href="source/net/ipv4/sysctl_net_ipv4.c#L865">865</a>         {
<a name="L866" href="source/net/ipv4/sysctl_net_ipv4.c#L866">866</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_fwmark_accept"</i>,
<a name="L867" href="source/net/ipv4/sysctl_net_ipv4.c#L867">867</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_tcp_fwmark_accept,
<a name="L868" href="source/net/ipv4/sysctl_net_ipv4.c#L868">868</a>                 .maxlen         = sizeof(int),
<a name="L869" href="source/net/ipv4/sysctl_net_ipv4.c#L869">869</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L870" href="source/net/ipv4/sysctl_net_ipv4.c#L870">870</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L871" href="source/net/ipv4/sysctl_net_ipv4.c#L871">871</a>         },
<a name="L872" href="source/net/ipv4/sysctl_net_ipv4.c#L872">872</a>         {
<a name="L873" href="source/net/ipv4/sysctl_net_ipv4.c#L873">873</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_mtu_probing"</i>,
<a name="L874" href="source/net/ipv4/sysctl_net_ipv4.c#L874">874</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_tcp_mtu_probing,
<a name="L875" href="source/net/ipv4/sysctl_net_ipv4.c#L875">875</a>                 .maxlen         = sizeof(int),
<a name="L876" href="source/net/ipv4/sysctl_net_ipv4.c#L876">876</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L877" href="source/net/ipv4/sysctl_net_ipv4.c#L877">877</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L878" href="source/net/ipv4/sysctl_net_ipv4.c#L878">878</a>         },
<a name="L879" href="source/net/ipv4/sysctl_net_ipv4.c#L879">879</a>         {
<a name="L880" href="source/net/ipv4/sysctl_net_ipv4.c#L880">880</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_base_mss"</i>,
<a name="L881" href="source/net/ipv4/sysctl_net_ipv4.c#L881">881</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_tcp_base_mss,
<a name="L882" href="source/net/ipv4/sysctl_net_ipv4.c#L882">882</a>                 .maxlen         = sizeof(int),
<a name="L883" href="source/net/ipv4/sysctl_net_ipv4.c#L883">883</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L884" href="source/net/ipv4/sysctl_net_ipv4.c#L884">884</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L885" href="source/net/ipv4/sysctl_net_ipv4.c#L885">885</a>         },
<a name="L886" href="source/net/ipv4/sysctl_net_ipv4.c#L886">886</a>         {
<a name="L887" href="source/net/ipv4/sysctl_net_ipv4.c#L887">887</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_probe_threshold"</i>,
<a name="L888" href="source/net/ipv4/sysctl_net_ipv4.c#L888">888</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_tcp_probe_threshold,
<a name="L889" href="source/net/ipv4/sysctl_net_ipv4.c#L889">889</a>                 .maxlen         = sizeof(int),
<a name="L890" href="source/net/ipv4/sysctl_net_ipv4.c#L890">890</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L891" href="source/net/ipv4/sysctl_net_ipv4.c#L891">891</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L892" href="source/net/ipv4/sysctl_net_ipv4.c#L892">892</a>         },
<a name="L893" href="source/net/ipv4/sysctl_net_ipv4.c#L893">893</a>         {
<a name="L894" href="source/net/ipv4/sysctl_net_ipv4.c#L894">894</a>                 .<a href="ident?i=procname">procname</a>       = <i>"tcp_probe_interval"</i>,
<a name="L895" href="source/net/ipv4/sysctl_net_ipv4.c#L895">895</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=init_net">init_net</a>.ipv4.sysctl_tcp_probe_interval,
<a name="L896" href="source/net/ipv4/sysctl_net_ipv4.c#L896">896</a>                 .maxlen         = sizeof(int),
<a name="L897" href="source/net/ipv4/sysctl_net_ipv4.c#L897">897</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L898" href="source/net/ipv4/sysctl_net_ipv4.c#L898">898</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L899" href="source/net/ipv4/sysctl_net_ipv4.c#L899">899</a>         },
<a name="L900" href="source/net/ipv4/sysctl_net_ipv4.c#L900">900</a>         { }
<a name="L901" href="source/net/ipv4/sysctl_net_ipv4.c#L901">901</a> };
<a name="L902" href="source/net/ipv4/sysctl_net_ipv4.c#L902">902</a> 
<a name="L903" href="source/net/ipv4/sysctl_net_ipv4.c#L903">903</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=ipv4_sysctl_init_net">ipv4_sysctl_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L904" href="source/net/ipv4/sysctl_net_ipv4.c#L904">904</a> {
<a name="L905" href="source/net/ipv4/sysctl_net_ipv4.c#L905">905</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>;
<a name="L906" href="source/net/ipv4/sysctl_net_ipv4.c#L906">906</a> 
<a name="L907" href="source/net/ipv4/sysctl_net_ipv4.c#L907">907</a>         <a href="ident?i=table">table</a> = <a href="ident?i=ipv4_net_table">ipv4_net_table</a>;
<a name="L908" href="source/net/ipv4/sysctl_net_ipv4.c#L908">908</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>)) {
<a name="L909" href="source/net/ipv4/sysctl_net_ipv4.c#L909">909</a>                 int <a href="ident?i=i">i</a>;
<a name="L910" href="source/net/ipv4/sysctl_net_ipv4.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/sysctl_net_ipv4.c#L911">911</a>                 <a href="ident?i=table">table</a> = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=table">table</a>, sizeof(<a href="ident?i=ipv4_net_table">ipv4_net_table</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L912" href="source/net/ipv4/sysctl_net_ipv4.c#L912">912</a>                 if (!<a href="ident?i=table">table</a>)
<a name="L913" href="source/net/ipv4/sysctl_net_ipv4.c#L913">913</a>                         goto err_alloc;
<a name="L914" href="source/net/ipv4/sysctl_net_ipv4.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/sysctl_net_ipv4.c#L915">915</a>                 <b><i>/* Update the variables to point into the current struct net */</i></b>
<a name="L916" href="source/net/ipv4/sysctl_net_ipv4.c#L916">916</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=ipv4_net_table">ipv4_net_table</a>) - 1; <a href="ident?i=i">i</a>++)
<a name="L917" href="source/net/ipv4/sysctl_net_ipv4.c#L917">917</a>                         <a href="ident?i=table">table</a>[<a href="ident?i=i">i</a>].<a href="ident?i=data">data</a> += (void *)<a href="ident?i=net">net</a> - (void *)&amp;<a href="ident?i=init_net">init_net</a>;
<a name="L918" href="source/net/ipv4/sysctl_net_ipv4.c#L918">918</a>         }
<a name="L919" href="source/net/ipv4/sysctl_net_ipv4.c#L919">919</a> 
<a name="L920" href="source/net/ipv4/sysctl_net_ipv4.c#L920">920</a>         <a href="ident?i=net">net</a>-&gt;ipv4.ipv4_hdr = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(<a href="ident?i=net">net</a>, <i>"net/ipv4"</i>, <a href="ident?i=table">table</a>);
<a name="L921" href="source/net/ipv4/sysctl_net_ipv4.c#L921">921</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.ipv4_hdr)
<a name="L922" href="source/net/ipv4/sysctl_net_ipv4.c#L922">922</a>                 goto err_reg;
<a name="L923" href="source/net/ipv4/sysctl_net_ipv4.c#L923">923</a> 
<a name="L924" href="source/net/ipv4/sysctl_net_ipv4.c#L924">924</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_local_reserved_ports = <a href="ident?i=kzalloc">kzalloc</a>(65536 / 8, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L925" href="source/net/ipv4/sysctl_net_ipv4.c#L925">925</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_local_reserved_ports)
<a name="L926" href="source/net/ipv4/sysctl_net_ipv4.c#L926">926</a>                 goto err_ports;
<a name="L927" href="source/net/ipv4/sysctl_net_ipv4.c#L927">927</a> 
<a name="L928" href="source/net/ipv4/sysctl_net_ipv4.c#L928">928</a>         return 0;
<a name="L929" href="source/net/ipv4/sysctl_net_ipv4.c#L929">929</a> 
<a name="L930" href="source/net/ipv4/sysctl_net_ipv4.c#L930">930</a> err_ports:
<a name="L931" href="source/net/ipv4/sysctl_net_ipv4.c#L931">931</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.ipv4_hdr);
<a name="L932" href="source/net/ipv4/sysctl_net_ipv4.c#L932">932</a> err_reg:
<a name="L933" href="source/net/ipv4/sysctl_net_ipv4.c#L933">933</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L934" href="source/net/ipv4/sysctl_net_ipv4.c#L934">934</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=table">table</a>);
<a name="L935" href="source/net/ipv4/sysctl_net_ipv4.c#L935">935</a> err_alloc:
<a name="L936" href="source/net/ipv4/sysctl_net_ipv4.c#L936">936</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L937" href="source/net/ipv4/sysctl_net_ipv4.c#L937">937</a> }
<a name="L938" href="source/net/ipv4/sysctl_net_ipv4.c#L938">938</a> 
<a name="L939" href="source/net/ipv4/sysctl_net_ipv4.c#L939">939</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=ipv4_sysctl_exit_net">ipv4_sysctl_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L940" href="source/net/ipv4/sysctl_net_ipv4.c#L940">940</a> {
<a name="L941" href="source/net/ipv4/sysctl_net_ipv4.c#L941">941</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *<a href="ident?i=table">table</a>;
<a name="L942" href="source/net/ipv4/sysctl_net_ipv4.c#L942">942</a> 
<a name="L943" href="source/net/ipv4/sysctl_net_ipv4.c#L943">943</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_local_reserved_ports);
<a name="L944" href="source/net/ipv4/sysctl_net_ipv4.c#L944">944</a>         <a href="ident?i=table">table</a> = <a href="ident?i=net">net</a>-&gt;ipv4.ipv4_hdr-&gt;ctl_table_arg;
<a name="L945" href="source/net/ipv4/sysctl_net_ipv4.c#L945">945</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.ipv4_hdr);
<a name="L946" href="source/net/ipv4/sysctl_net_ipv4.c#L946">946</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=table">table</a>);
<a name="L947" href="source/net/ipv4/sysctl_net_ipv4.c#L947">947</a> }
<a name="L948" href="source/net/ipv4/sysctl_net_ipv4.c#L948">948</a> 
<a name="L949" href="source/net/ipv4/sysctl_net_ipv4.c#L949">949</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipv4_sysctl_ops">ipv4_sysctl_ops</a> = {
<a name="L950" href="source/net/ipv4/sysctl_net_ipv4.c#L950">950</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipv4_sysctl_init_net">ipv4_sysctl_init_net</a>,
<a name="L951" href="source/net/ipv4/sysctl_net_ipv4.c#L951">951</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipv4_sysctl_exit_net">ipv4_sysctl_exit_net</a>,
<a name="L952" href="source/net/ipv4/sysctl_net_ipv4.c#L952">952</a> };
<a name="L953" href="source/net/ipv4/sysctl_net_ipv4.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/sysctl_net_ipv4.c#L954">954</a> static <a href="ident?i=__init">__init</a> int <a href="ident?i=sysctl_ipv4_init">sysctl_ipv4_init</a>(void)
<a name="L955" href="source/net/ipv4/sysctl_net_ipv4.c#L955">955</a> {
<a name="L956" href="source/net/ipv4/sysctl_net_ipv4.c#L956">956</a>         struct <a href="ident?i=ctl_table_header">ctl_table_header</a> *<a href="ident?i=hdr">hdr</a>;
<a name="L957" href="source/net/ipv4/sysctl_net_ipv4.c#L957">957</a> 
<a name="L958" href="source/net/ipv4/sysctl_net_ipv4.c#L958">958</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(&amp;<a href="ident?i=init_net">init_net</a>, <i>"net/ipv4"</i>, <a href="ident?i=ipv4_table">ipv4_table</a>);
<a name="L959" href="source/net/ipv4/sysctl_net_ipv4.c#L959">959</a>         if (!<a href="ident?i=hdr">hdr</a>)
<a name="L960" href="source/net/ipv4/sysctl_net_ipv4.c#L960">960</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L961" href="source/net/ipv4/sysctl_net_ipv4.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/sysctl_net_ipv4.c#L962">962</a>         if (<a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ipv4_sysctl_ops">ipv4_sysctl_ops</a>)) {
<a name="L963" href="source/net/ipv4/sysctl_net_ipv4.c#L963">963</a>                 <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=hdr">hdr</a>);
<a name="L964" href="source/net/ipv4/sysctl_net_ipv4.c#L964">964</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L965" href="source/net/ipv4/sysctl_net_ipv4.c#L965">965</a>         }
<a name="L966" href="source/net/ipv4/sysctl_net_ipv4.c#L966">966</a> 
<a name="L967" href="source/net/ipv4/sysctl_net_ipv4.c#L967">967</a>         return 0;
<a name="L968" href="source/net/ipv4/sysctl_net_ipv4.c#L968">968</a> }
<a name="L969" href="source/net/ipv4/sysctl_net_ipv4.c#L969">969</a> 
<a name="L970" href="source/net/ipv4/sysctl_net_ipv4.c#L970">970</a> <a href="ident?i=__initcall">__initcall</a>(<a href="ident?i=sysctl_ipv4_init">sysctl_ipv4_init</a>);
<a name="L971" href="source/net/ipv4/sysctl_net_ipv4.c#L971">971</a> </pre></div><p>
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
