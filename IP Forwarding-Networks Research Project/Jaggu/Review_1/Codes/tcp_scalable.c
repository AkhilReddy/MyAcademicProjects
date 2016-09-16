<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_scalable.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_scalable.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_scalable.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_scalable.c">tcp_scalable.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_scalable.c#L1">1</a> <b><i>/* Tom Kelly's Scalable TCP</i></b>
  <a name="L2" href="source/net/ipv4/tcp_scalable.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/tcp_scalable.c#L3">3</a> <b><i> * See <a href="http://www.deneholme.net/tom/scalable/">http://www.deneholme.net/tom/scalable/</a></i></b>
  <a name="L4" href="source/net/ipv4/tcp_scalable.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/tcp_scalable.c#L5">5</a> <b><i> * John Heffner &lt;jheffner@sc.edu&gt;</i></b>
  <a name="L6" href="source/net/ipv4/tcp_scalable.c#L6">6</a> <b><i> */</i></b>
  <a name="L7" href="source/net/ipv4/tcp_scalable.c#L7">7</a> 
  <a name="L8" href="source/net/ipv4/tcp_scalable.c#L8">8</a> #include &lt;linux/module.h&gt;
  <a name="L9" href="source/net/ipv4/tcp_scalable.c#L9">9</a> #include &lt;net/tcp.h&gt;
 <a name="L10" href="source/net/ipv4/tcp_scalable.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/tcp_scalable.c#L11">11</a> <b><i>/* These factors derived from the recommended values in the aer:</i></b>
 <a name="L12" href="source/net/ipv4/tcp_scalable.c#L12">12</a> <b><i> * .01 and and 7/8. We use 50 instead of 100 to account for</i></b>
 <a name="L13" href="source/net/ipv4/tcp_scalable.c#L13">13</a> <b><i> * delayed ack.</i></b>
 <a name="L14" href="source/net/ipv4/tcp_scalable.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/tcp_scalable.c#L15">15</a> #define <a href="ident?i=TCP_SCALABLE_AI_CNT">TCP_SCALABLE_AI_CNT</a>     50U
 <a name="L16" href="source/net/ipv4/tcp_scalable.c#L16">16</a> #define <a href="ident?i=TCP_SCALABLE_MD_SCALE">TCP_SCALABLE_MD_SCALE</a>   3
 <a name="L17" href="source/net/ipv4/tcp_scalable.c#L17">17</a> 
 <a name="L18" href="source/net/ipv4/tcp_scalable.c#L18">18</a> static void <a href="ident?i=tcp_scalable_cong_avoid">tcp_scalable_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
 <a name="L19" href="source/net/ipv4/tcp_scalable.c#L19">19</a> {
 <a name="L20" href="source/net/ipv4/tcp_scalable.c#L20">20</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L21" href="source/net/ipv4/tcp_scalable.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/tcp_scalable.c#L22">22</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
 <a name="L23" href="source/net/ipv4/tcp_scalable.c#L23">23</a>                 return;
 <a name="L24" href="source/net/ipv4/tcp_scalable.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_scalable.c#L25">25</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
 <a name="L26" href="source/net/ipv4/tcp_scalable.c#L26">26</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
 <a name="L27" href="source/net/ipv4/tcp_scalable.c#L27">27</a>         else
 <a name="L28" href="source/net/ipv4/tcp_scalable.c#L28">28</a>                 <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=TCP_SCALABLE_AI_CNT">TCP_SCALABLE_AI_CNT</a>),
 <a name="L29" href="source/net/ipv4/tcp_scalable.c#L29">29</a>                                   1);
 <a name="L30" href="source/net/ipv4/tcp_scalable.c#L30">30</a> }
 <a name="L31" href="source/net/ipv4/tcp_scalable.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/tcp_scalable.c#L32">32</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_scalable_ssthresh">tcp_scalable_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L33" href="source/net/ipv4/tcp_scalable.c#L33">33</a> {
 <a name="L34" href="source/net/ipv4/tcp_scalable.c#L34">34</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L35" href="source/net/ipv4/tcp_scalable.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tcp_scalable.c#L36">36</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd - (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd&gt;&gt;<a href="ident?i=TCP_SCALABLE_MD_SCALE">TCP_SCALABLE_MD_SCALE</a>), 2U);
 <a name="L37" href="source/net/ipv4/tcp_scalable.c#L37">37</a> }
 <a name="L38" href="source/net/ipv4/tcp_scalable.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/tcp_scalable.c#L39">39</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_scalable <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L40" href="source/net/ipv4/tcp_scalable.c#L40">40</a>         .ssthresh       = <a href="ident?i=tcp_scalable_ssthresh">tcp_scalable_ssthresh</a>,
 <a name="L41" href="source/net/ipv4/tcp_scalable.c#L41">41</a>         .cong_avoid     = <a href="ident?i=tcp_scalable_cong_avoid">tcp_scalable_cong_avoid</a>,
 <a name="L42" href="source/net/ipv4/tcp_scalable.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/tcp_scalable.c#L43">43</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L44" href="source/net/ipv4/tcp_scalable.c#L44">44</a>         .<a href="ident?i=name">name</a>           = <i>"scalable"</i>,
 <a name="L45" href="source/net/ipv4/tcp_scalable.c#L45">45</a> };
 <a name="L46" href="source/net/ipv4/tcp_scalable.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/tcp_scalable.c#L47">47</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_scalable_register">tcp_scalable_register</a>(void)
 <a name="L48" href="source/net/ipv4/tcp_scalable.c#L48">48</a> {
 <a name="L49" href="source/net/ipv4/tcp_scalable.c#L49">49</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_scalable);
 <a name="L50" href="source/net/ipv4/tcp_scalable.c#L50">50</a> }
 <a name="L51" href="source/net/ipv4/tcp_scalable.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/tcp_scalable.c#L52">52</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_scalable_unregister">tcp_scalable_unregister</a>(void)
 <a name="L53" href="source/net/ipv4/tcp_scalable.c#L53">53</a> {
 <a name="L54" href="source/net/ipv4/tcp_scalable.c#L54">54</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_scalable);
 <a name="L55" href="source/net/ipv4/tcp_scalable.c#L55">55</a> }
 <a name="L56" href="source/net/ipv4/tcp_scalable.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/tcp_scalable.c#L57">57</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_scalable_register">tcp_scalable_register</a>);
 <a name="L58" href="source/net/ipv4/tcp_scalable.c#L58">58</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_scalable_unregister">tcp_scalable_unregister</a>);
 <a name="L59" href="source/net/ipv4/tcp_scalable.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/tcp_scalable.c#L60">60</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"John Heffner"</i>);
 <a name="L61" href="source/net/ipv4/tcp_scalable.c#L61">61</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L62" href="source/net/ipv4/tcp_scalable.c#L62">62</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Scalable TCP"</i>);
 <a name="L63" href="source/net/ipv4/tcp_scalable.c#L63">63</a> </pre></div><p>
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
