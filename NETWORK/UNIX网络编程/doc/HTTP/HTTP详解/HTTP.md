# HTTP协议详解

## HTTP的主要特点

- 支持客户/服务器模式。
- 简单快速:客户向服务器请求服务时,只需传送请求方法和路径。请求方法常用的有 GET、HEAD、
  POST。每种方法规定了客户与服务器联系的类型不同。由于 HTTP 协议简单,使得 HTTP 服务器的程序规
  模小,因而通信速度很快。
- 灵活:HTTP 允许传输任意类型的数据对象。正在传输的类型由 Content-Type 加以标记。
- 无连接:无连接的含义是限制每次连接只处理一个请求。服务器处理完客户的请求,并收到客户的
  应答后,即断开连接。采用这种方式可以节省传输时间。
- 无状态:HTTP 协议是无状态协议。无状态是指协议对于事务处理没有记忆能力。缺少状态意味着
  如果后续处理需要前面的信息,则它必须重传,这样可能导致每次连接传送的数据量增大。另一方面,在
  服务器不需要先前信息时它的应答就较快。

## `HTTP`协议之`URL`

`http`(超文本传输协议)是一个基于请求与响应模式的、无状态的、应用层的协议,常基于 `TCP` 的
连接方式,`HTTP1.1` 版本中给出一种持续连接的机制,绝大多数的 Web 开发,都是构建在 `HTTP` 协议之
上的 `Web` 应用。

`HTTP　URL`(URL是一种特殊类型的URI，它包含了查找某个资源足够的信息)的格式如下：

```bash
http://host[":"port][abs_path]
http 表示要通过 HTTP 协议来定位网络资源;host 表示合法的 Internet 主机域名或者 IP 地址;
port 指定一个端口号,为空则使用缺省端口 80;abs_path 指定请求资源的 URI;如果 URL 中没有给
出 abs_path,那么当它作为请求 URI 时,必须以“/”的形式给出,通常这个工作浏览器自动帮我们完成。
eg:
1、输入:www.guet.edu.cn
浏览器自动转换成:http://www.guet.edu.cn/
2、http:192.168.0.116:8080/index.jsp
```

## `HTTP`协议详解之请求篇

`http`由三部份组成，分别是：请求行，消息报头，请求正文

1. 请求以一个方法符号开头，以空格分开，后面跟着`URI`和协议的版本，格式如下：`Method Request-URI HTTP-Version CRLT`

​    其中`Method`标示请求方法；`Request-URI`是一个统一资源标识符；`HTTP Vewrsion`表示请求`HTTP`协议版本；`CRLF`标示回车和换行(除了作为结尾的`CRLF`外，不允许出现单独的`CR`   或   `LF`字符)

<font size=3 color=red>请求方法</font>(所有的方法全为大写)有多种，各种方法的解析如下：

`GET` 请求获取`Request-URI`所标识的资源

`POST` 在`Request-URI`所标识的资源后附加新数据

`HEAD` 请求获取由`Request-URI`所标识的的资源的响应消息报头

`PUT` 请求服务器存储一个资源，并用`Request-URI`作为其标识

`DELETE` 请求服务器删除`Ruquest-URI`所标识的资源

`TRACE`　请求服务器回收收到的请求信息，主要用于测试或诊断

`CONNECT` 保留将来使用

`OPTIONS`　请求查询服务器的性能，或者查询与资源相关的选项和需求



###　<font color=red>应用举例</font>

`GET`方法:在浏览器的地址栏中输入网址的方式访问网页时，浏览器采用`GET`方法向服务器获取资源

`eg:GET /from.html HTTP/1.1(CRLF)`

`POST`方法要求被请求的服务器接受附在请求后面的数据，常用语提交表单

```javascript
POST /reg.jsp HTTP(CRLF)
Accept:image/gif, image/x-xbit, ...(CRLF)
...
HOST:www.guet.edu.cn(CRLF)
Content-Length:22(CRLF)
Connection:keep-Alive(CRLF)
Cache-Control:no-cache(CRLF)
(CRLF)//该CRLF标示消息报头已经结束，在此之前为消息报头
user=jeffrey&pwd=1234//此行为提交的数据
```

`HEAD`方法与`GET`方法几乎是一样的，对于`HEAD`的请求的回应部分来说，他的`HTTP`头部中包含的信息与通过`GET`请求所得到的信息是相同的。利用这个方法，不必传输整个资源的内容，就可以得到`Request-URI`锁标识的资源信息，该方法常用语测试超链接的有效性，是否可以访问，以及最近是否更新。

2. 请求报头后述
3. 请求正文

## `HTTP`协议详解只响应篇

在接收和解释请求消息后，服务器返回与一个`HTTP`响应消息。

`HTTP`响应也是由三个部分组成，分别是:状态行、消息报头、响应正文

1. 状态行格式如下:

`HTTP-Version Status-Code Reason-Phrase CRLF`

其中，`HTTP-Version`表示服务`HTTP`协议的版本；`Status-Code`表示服务器发回的响应状态代码；`Reason-Phrase`表示状态代码的文本描述。

状态代码有三位数字组成，第一个数字定义了响应的类型，且有五种可能取值：

`1XX`: 指示信息－－表示请求已接收，继续处理

`2XX`: 成功－－表示请求已被成功接收、理解、接受

`3XX`: 重定向--要完成请求必须进行更进一步的操作

`4XX`: 客户端错误－－请求有语法错误或请求无法实现

`5XX`: 服务器端错误－－服务器未能实现合法的请求

常见状态码、状态描述、说明：

```bash
200 OK //客户端请求成功
400　Bad Request //客户端请求有语法错误，不能被服务器所理解
401 unauthorized //骑牛未经授权，这个状态码必须和www-Authenticate报头域一起使用
403 Forbidden //服务器收到请求，但是拒绝提供服务
404 Not Fount //请求资源不存在，eg:输入了错误的URL
500　Internal Server Error //服务器发生不可预期的错误
503 Server unavailable //服务器当前不能处理客户端的请求，一段时间后，可能恢复正常
eg:HTTP/1.1 200 OK (CRLF)
```

2. 响应后的描述
3. 响应正文就是服务器返回的资源内容

## HTTP协议详解之消息报头篇

HTTP消息由客户端到服务器的求情和服务器到客户端的响应组成。请求和响应消息都是由开始行(对于请求消息，开始行就是请求行，对于响应消息，开始行就是状态行)，消息报头(可选)，空行(只有`CRLF`的行)，消息正文(可选)组成。

> HTTP消息报头包括普通报头、请求报头、响应报头、实体报头。
>
> 每个报头的域都是由名字+": " "+空格＋值",组成，消息报头域的名字是大小写无光的。



### 普通报头

在普通报头中，有少数的报头域用于所有的请求和响应消息，但并不用于被传输的实体，只用于传输的消息。

`eg:`

`Cache-Ctrol`用于指定缓存指令，缓存指令是单向的(响应中出现的缓存指令在请求中未必实现)，且是独立的(一个消息的缓存指令不会影响另一个消息处理的缓存机制)，`HTTP1.0`使用类似的报头域为`pragma`。

请求时的缓存指令包括:`no-cache`(用于指示请求或响应的消息不能缓存)、`no-store`、`max-age`、`max-statle`、`min-frash`、`only-if-cached`;

响应时的缓存指令包括：`public`、`private`、`no-cache`、`no-store`、`no-transform`、`must-revalidate`、`proxy-revalidate`、`max-age`、`no-cache`。

`eg:`为了指示`IE`浏览器(客户端)不要缓存页面，服务器端的`JSP`程序可以编写如下：`response.setHeader("Cache-Control","no-cahce")`;

```
//response.setHeader("Pragma", "no-cache");作用相当于上述代码
```

`Date`普通报头域，表示消息产生的日期和时间

`Connection`普通报头域，允许发送指定连接的选项，例如指定连接是连续，或者指定`close`选项，通知服务器，在相应完成后，关闭连接。

### 请求报头

请求报头允许客户端向服务器传递请求的附加信息以及客户端自身的信息。

常用的请求报头:

`Accept`

`Accept`请求报头域用于指定客户端接受哪些类型的信息。

```
eg:
Accept: image/gif
```

表明客户端希望接受`GIF`图片格式的资源;

```
Accept: text/html,表明客户端希望接受html文本。
```

`Accept-Charset`

`Accept-Charset`请求报头域用于指定客户端接受的字符集。`eg:Accept-Charset:iso-8859-1,gb2312`.如果在请求消息中没有设置这个域，缺省是任何字符集够可以接受。

`Accept-Encoding`

`Accept-Language`请求域类似于`Accept`，但是它是用于指定一种自然语言。`eg:Accept-Language:zh-cn.`如果请求消息中没有设置这个报头域，服务器假定客户端对各种语言都可以接受。

`Authorization`

`Authorization`请求报头域，主要用于证明客户端有权查看某个资源，当浏览器访问一个页面时，如果收到服务器的响应代码为`401`(未授权)，可以发送一个包含`Authrization`请求报头域的请求，要求服务器对其进行验证。

`Host`(发送请求时，该报头域是必需的)

`Host`请求报头域主要用于指定被请求资源的`Internet`主机和端口号，它通常从`HTTP URL`中提取出来的，

```
eg:
我们在浏览器中输入：http://www.guet.edu.cn/index.html
浏览器发送的请求消息中，就会包含Host请求报头域，如下：
Host:www.guet.edu.cn
此处使用缺省端口号80,若指定了端口号，则变成:Host.guet.edu.cn:指定端口号
```

`User-Agent`

我们上网登陆论坛的时候,往往会看到一些欢迎信息,其中列出了你的操作系统的名称和版本,你所
使用的浏览器的名称和版本,这往往让很多人感到很神奇,实际上,服务器应用程序就是从 User-Agent
这个请求报头域中获取到这些信息。User-Agent 请求报头域允许客户端将它的操作系统、浏览器和其它
属性告诉服务器。不过,这个报头域不是必需的,如果我们自己编写一个浏览器,不使用 User-Agent
请求报头域,那么服务器端就无法得知我们的信息了。

请求报头举例:

```js
GET /form.html HTTP/1.1 (CRLF)
Accept:image/gif,image/x-xbitmap,image/jpeg,application/x-shockwave-flas
h,application/vnd.ms-excel,application/vnd.ms-powerpoint,application/msword,
*/* (CRLF)
Accept-Language:zh-cn (CRLF)
Accept-Encoding:gzip,deflate (CRLF)
If-Modified-Since:Wed,05 Jan 2007 11:21:25 GMT (CRLF)
If-None-Match:W/"80b1a4c018f3c41:8317" (CRLF)
User-Agent:Mozilla/4.0(compatible;MSIE6.0;Windows NT 5.0) (CRLF)
Host:www.guet.edu.cn (CRLF)
Connection:Keep-Alive (CRLF)
(CRLF)
```



### 相应报头

响应报头允许服务器传递不能放在状态行中的附加响应信息 , 以及关于服务器的信息和对
`Request-URI` 所标识的资源进行下一步访问的信息。
常用的响应报头
`Location`
`Location` 响应报头域用于重定向接受者到一个新的位置。 `Location` 响应报头域常用在更换域名的
时候。
`Server`
`Server` 响应报头域包含了服务器用来处理请求的软件信息。与 `User`-Agent 请求报头域是相对应
的。下面是`Server` 响应报头域的一个例子:
`Server:Apache-Coyote/1.1`
`WWW-Authenticate`
`WWW-Authenticate` 响应报头域必须被包含在 `401`(未授权的)响应消息中,客户端收到 `401` 响应
消息时候,并发送 `Authorization` 报头域请求服务器对其进行验证时,服务端响应报头就包含该报头域。
`eg:WWW-Authenticate:Basic realm="Basic Auth Test!"` //可以看出服务器对请求资
源采用的是基本验证机制。

### 实体报头

请求和响应消息都可以传送一个实体。一个实体由实体报头域和实体正文组成,但并不是说实体报头域和实体正文要在一起发送,可以只发送实体报头域。实体报头定义了关于实体正文(`eg:`有无实体正文)和请求所标识的资源的元信息。
常用的实体报头
`Content-Encoding`
`Content-Encoding` 实体报头域被用作媒体类型的修饰符,它的值指示了已经被应用到实体正文的附加内容的编码,因而要获得 `Content-Type` 报头域中所引用的媒体类型,必须采用相应的解码机制。
`Content-Encoding` 这样用于记录文档的压缩方法`,eg:Content-Encoding:gzip`
`Content-Language`
`Content-Language` 实体报头域描述了资源所用的自然语言。没有设置该域则认为实体内容将提供给所有的语言阅读
者。`eg:Content-Language:da`
`Content-Length`
`Content-Length` 实体报头域用于指明实体正文的长度,以字节方式存储的十进制数字来表示。
`Content-Type`
`Content-Type` 实体报头域用语指明发送给接收者的实体正文的媒体类型。

`eg:`
`Content-Type:text/html;charset=ISO-8859-1`
`Content-Type:text/html;charset=GB231`

`Last-Modified`

`Last-Modified` 实体报头域用于指示资源的最后修改日期和时间。
`Expires`
`Expires` 实体报头域给出响应过期的日期和时间。为了让代理服务器或浏览器在一段时间以后更新
缓存中(再次访问曾访问过的页面时,直接从缓存中加载,缩短响应时间和降低服务器负载)的页面,我们
可以使用 `Expires` 实体报头域指定页面过期的时间。`eg:Expires:Thu,15 Sep 2006 16:23:12 GMT`
`HTTP1.1` 的客户端和缓存必须将其他非法的日期格式(包括 0)看作已经过期。`eg:`为了让浏览器
不 要 缓 存 页 面 , 我 们 也 可 以 利 用~ Expires~ 实 体 报 头 域 , 设 置 为 0 , `jsp` 中 程 序 如 下 :
`response.setDateHeader("Expires","0");`

## 利用`Telnet`观察`http`协议通讯的过程

利用`telnet`会将对话的过程显示出来，就能只管的看，`http`协议的交互过程

###  1.打开`telnet`

```bash
telnet
＃开启回显功能
telnet> set echo on
echo character is 'o'.
```

### 连接服务器并发送请求

```
open www.xxx.xx port
```





