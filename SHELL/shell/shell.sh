3. 特殊字符
用在脚本和其他地方的特殊字符
#
注释. 行首以#(#!是个例外)开头是注释.
1 # This line is a comment.
注释也可以放在于本行命令的后边.
1 echo "A comment will follow." # 注释在这里.
2 # ^ 注意#前边的空白
注释也可以放在本行行首空白的后面.
1 # A tab precedes this comment.
命令是不能放在同一行上注释的后边的. 因为没有办法把注释结束掉, 好让
同一行上后边的"代码生效". 只能够另起一行来使用下一个命令.
当然, 在echo中转义的#是不能作为注释的. 同样的, #也可以出现在特定的
参数替换结构中, 或者是出现在数字常量表达式中.
1 echo "The # here does not begin a comment."
2 echo 'The # here does not begin a comment.'
3 echo The \# here does not begin a comment.
4 echo The # 这里开始一个注释.
5
6 echo ${PATH#*:} # 参数替换, 不是一个注释.
7 echo $(( 2#101011 )) # 数制转换, 不是一个注释.
8
9 # 感谢, S.C.
标准的引用和转义字符(" ' \)可以用来转义#.
某些特定的模式匹配操作也可以使用#.
;
命令分隔符[分号, 即;]. 可以在同一行上写两个或两个以上的命令.
1 echo hello; echo there
2
3
4 if [ -x "$filename" ]; then # 注意: "if"和"then"需要分隔.
5 # 为什么?
6 echo "File $filename exists."; cp $filename $filename.bak
7 else
8 echo "File $filename not found."; touch $filename
9 fi; echo "File test complete."
注意一下";"某些情况下需要转义.
;;
终止case选项[双分号, 即;;].
1 case "$variable" in
2 abc) echo "\$variable = abc" ;;
3 xyz) echo "\$variable = xyz" ;;
4 esac
.
"点"命令[句点, 即.]. 等价于source命令(参见 例子 11-21). 这是一个bash的内建命令.
.
"点"作为文件名的一部分. 如果点放在文件名的开头的话, 那么这个文件将会成为"隐藏"文件,
并且ls命令将不会正常的显示出这个文件.
bash$ touch .hidden-file
bash$ ls -l
total 10
-rw-r--r-- 1 bozo 4034 Jul 18 22:04 data1.addressbook
-rw-r--r-- 1 bozo 4602 May 25 13:58 data1.addressbook.bak
-rw-r--r-- 1 bozo 877 Dec 17 2000 employment.addressbook
bash$ ls -al
total 14
drwxrwxr-x 2 bozo bozo 1024 Aug 29 20:54 ./
drwx------ 52 bozo bozo 3072 Aug 29 20:51 ../
-rw-r--r-- 1 bozo bozo 4034 Jul 18 22:04 data1.addressbook
-rw-r--r-- 1 bozo bozo 4602 May 25 13:58
data1.addressbook.bak
-rw-r--r-- 1 bozo bozo 877 Dec 17 2000
employment.addressbook
-rw-rw-r-- 1 bozo bozo 0 Aug 29 20:54 .hidden-file
如果作为目录名的话, 一个单独的点代表当前的工作目录, 而两个点表示上一级目录.
bash$ pwd
/home/bozo/projects
bash$ cd .
bash$ pwd
/home/bozo/projects
bash$ cd ..
bash$ pwd
/home/bozo/
点经常会出现在文件移动命令的目的参数(目录)的位置上.
bash$ cp /home/bozo/current_work/junk/* .
.
"点"字符匹配. 当用作匹配字符的作用时, 通常都是作为正则表达式的一部分来使用, "点"用来
匹配任何的单个字符.
"
部分引用[双引号, 即"]. "STRING"将会阻止(解释)STRING中大部分特殊的字符. 参见 5.
'
全引用[单引号, 即']. 'STRING'将会阻止STRING中所有特殊字符的解释. 这是一种比使用"更强
烈的形式. 参见 5.
,
逗号操作符. 逗号操作符链接了一系列的算术操作. 虽然里边所有的内容都被运行了,但只有最后
一项被返回.
1 let "t2 = ((a = 9, 15 / 3))" # Set "a = 9" and "t2 = 15 / 3"
\
转义符[反斜线, 即\]. 一种对单字符的引用机制.
\X将会"转义"字符X. 这等价于"X", 也等价于'X'. \通常用来转义"和', 这样双引号和但引号就
不会被解释成特殊含义了.
参见 5来深入地了解转义符的详细解释.
/
文件名路径分隔符[斜线, 即/]. 分隔文件名不同的部分(比如 /home/bozo/projects/Makefile).
也可以用来作为除法算术操作符.
`
命令替换. `command`结构可以将命令的输出赋值到一个变量中去. 我们在后边的后置引用
(backquotes)或后置标记(backticks)中也会讲解.
:
空命令[冒号, 即:]. 等价于"NOP" (no op, 一个什么也不干的命令). 也可以被认为与shell的
内建命令true作用相同. ":"命令是一个bash的内建命令, 它的退出码(exit
status)是"true"(0).
1 :
2 echo $? # 0
死循环:
1 while :
2 do
3 operation-1
4 operation-2
5 ...
6 operation-n
7 done
8
9 # 与下边相同:
10 # while true
11 # do
12 # ...
13 # done
在if/then中的占位符:
1 if condition
2 then : # 什么都不做,引出分支.
3 else
4 take-some-action
5 fi
在一个二元命令中提供一个占位符, 具体参见例子 8-2, 和默认参数.
1 : ${username=`whoami`}
2 # ${username=`whoami`} 如果没有开头的":"的话, 将会给出一个错误,
3# 除非"username"是一个命令或者内建命令...
在here document中提供一个命令所需的占位符. 参见例子 17-10.
使用参数替换来评估字符串变量 (参见例子 9-15).
1 : ${HOSTNAME?} ${USER?} ${MAIL?}
2 # 如果一个或多个必要的环境变量没被设置的话,
3 #+ 就打印错误信息.
变量扩展/子串替换.
在与>重定向操作符结合使用时, 将会把一个文件清空, 但是并不会修改这个文件的权限. 如果之
前这个文件并不存在, 那么就创建这个文件.
1 : > data.xxx # 文件"data.xxx"现在被清空了.
2
3 # 与 cat /dev/null >data.xxx 的作用相同
4 # 然而,这并不会产生一个新的进程, 因为":"是一个内建命令.
参见例子 12-14.
在与>>重定向操作符结合使用时, 将不会对预先存在的目标文件(: >> target_file)产生任何影
响. 如果这个文件之前并不存在, 那么就创建它.
这只适用于正规文件, 而不适用于管道, 符号连接, 和某些特殊文件.
也可能用来作为注释行, 虽然我们不推荐这么做. 使用#来注释的话, 将关闭剩余行的错误检查,
所以可以在注释行中写任何东西. 然而, 使用:的话将不会这样.
1 : This is a comment that generates an error, ( if [ $x -eq 3] ).
":"还用来在/etc/passwd和$PATH变量中做分隔符.
bash$ echo $PATH
/usr/local/bin:/bin:/usr/bin:/usr/X11R6/bin:/sbin:/usr/sbin:/usr/games
!
取反操作符[叹号, 即!]. !操作符将会反转命令的退出码的结果, (具体参见例子 6-2). 也会反
转测试操作符的意义, 比如修改"等号"( = )为"不等号"( != ). !操作符是Bash的关键字.
在一个不同的上下文中, !也会出现在变量的间接引用中.
在另一种上下文中, 如命令行模式下, !还能反转bash的历史机制 (参见Appendix J). 需要注意
的是, 在一个脚本中, 历史机制是被禁用的.
*
通配符[星号, 即*]. *可以用来做文件名匹配(这个东西有个专有名词叫globbing)的"通配符".
含义是, 可以用来匹配给定目录下的任何文件名.
bash$ echo *
abs-book.sgml add-drive.sh agram.sh alias.sh
*也可以用在正则表达式中, 用来匹配任意个数(包含0个)的字符.
*
算术操作符. 在算术操作符的上下文中, *号表示乘法运算.
如果要做求幂运算, 使用**, 这是求幂操作符.
?
测试操作符. 在一个特定的表达式中, ?用来测试一个条件的结果.
在一个双括号结构中, ?就是C语言的三元操作符. 参见例子 9-31.
在参数替换表达式中, ?用来测试一个变量是否被set了. .
?
通配符. ?在通配(globbing)中, 用来做匹配单个字符的"通配符", 在正则表达式中, 也是用
来表示一个字符.
$
变量替换(引用变量的内容).
1 var1=5
2 var2=23skidoo
3
4 echo $var1 # 5
5 echo $var2 # 23skidoo
在一个变量前面加上$用来引用这个变量的值.
$
行结束符. 在正则表达式中, "$"表示行结束符.
${}
参数替换.
$*, $@
位置参数.
$?
退出状态码变量. $? 变量 保存了一个命令, 一个函数, 或者是脚本本身的退出状态码.
$$
进程ID变量. 这个$$ 变量 保存了它所在脚本的进程 ID [1]
()
命令组.
1 (a=hello; echo $a)
在括号中的命令列表, 将会作为一个子shell来运行.
在括号中的变量,由于是在子shell中,所以对于脚本剩下的部分是不可用的.
父进程, 也就是脚本本身, 将不能够读取在子进程中创建的变量, 也就是在
子shell中创建的变量.
1 a=123
2 ( a=321; )
3
4 echo "a = $a" # a = 123
5 # 在圆括号中a变量, 更像是一个局部变量.
初始化数组.
1 Array=(element1 element2 element3)
{xxx,yyy,zzz,...}
大括号扩展.
1 cat {file1,file2,file3} > combined_file
2 # 把file1, file2, file3连接在一起, 并且重定向到combined_file中.
3
4
5 cp file22.{txt,backup}
6 # 拷贝"file22.txt"到"file22.backup"中
一个命令可能会对大括号 [2] 中的以逗号分割的文件列表起作用. (通配(globbing))将对大括号
中的文件名做扩展.
在大括号中, 不允许有空白, 除非这个空白被引用或转义.
echo {file1,file2}\ :{\ A," B",' C'}
file1 : A file1 : B file1 : C file2 : A file2 : B file2 : C
{}
代码块[大括号, 即{}]. 又被称为内部组, 这个结构事实上创建了一个匿名函数(一个没有名字的
函数). 然而, 与"标准"函数不同的是, 在其中声明的变量,对于脚本其他部分的代码来说还是可
见的.
bash$ { local a;
a=123; }
bash: local: can only be used in a
function
1 a=123
2 { a=321; }
3 echo "a = $a" # a = 321 (说明在代码块中对变量a所作的修改, 影响了外边的
变量)
4
5 # 感谢, S.C.
下边的代码展示了在大括号结构中代码的I/O 重定向.
例子 3-1. 代码块和I/O重定向
1 #!/bin/bash
2 # 从/etc/fstab中读行.
3
4 File=/etc/fstab
5
6 {
7 read line1
8 read line2
9 } < $File
10
11 echo "First line in $File is:"
12 echo "$line1"
13 echo
14 echo "Second line in $File is:"
15 echo "$line2"
16
17 exit 0
18
19 # 现在, 你怎么分析每行的分割域?
20 # 小提示: 使用awk.
例子 3-2. 将一个代码块的结果保存到文件
1 #!/bin/bash
2 # rpm-check.sh
3
4 # 这个脚本的目的是为了描述, 列表, 和确定是否可以安装一个rpm包.
5 # 在一个文件中保存输出.
6 #
7 # 这个脚本使用一个代码块来展示.
8
9 SUCCESS=0
10 E_NOARGS=65
11
12 if [ -z "$1" ]
13 then
14 echo "Usage: `basename $0` rpm-file"
15 exit $E_NOARGS
16 fi
17
18 {
19 echo
20 echo "Archive Description:"
21 rpm -qpi $1 # 查询说明.
22 echo
23 echo "Archive Listing:"
24 rpm -qpl $1 # 查询列表.
25 echo
26 rpm -i --test $1 # 查询rpm包是否可以被安装.
27 if [ "$?" -eq $SUCCESS ]
28 then
29 echo "$1 can be installed."
30 else
31 echo "$1 cannot be installed."
32 fi
33 echo
34 } > "$1.test" # 把代码块中的所有输出都重定向到文件中.
35
36 echo "Results of rpm test in file $1.test"
37
38 # 查看rpm的man页来查看rpm的选项.
39
40 exit 0
与上面所讲到的()中的命令组不同的是, {大括号}中的代码块将不会开启一
个新的子shell. [3]
{} \;
路径名. 一般都在find命令中使用. 这不是一个shell内建命令.
";"用来结束find命令序列的-exec选项. 它需要被保护以防止被shell所解
释.
[ ]
条件测试.
条件测试表达式放在[ ]中. 值得注意的是[是shell内建test命令的一部分, 并不
是/usr/bin/test中的外部命令的一个链接.
[[ ]]
测试.
测试表达式放在[[ ]]中. (shell关键字).
具体参见关于[[ ... ]]结构的讨论.
[ ]
数组元素.
在一个array结构的上下文中, 中括号用来引用数组中每个元素的编号.
1 Array[1]=slot_1
2 echo ${Array[1]}
[ ]
字符范围.
用作正则表达式的一部分, 方括号描述一个匹配的字符范围.
(( ))
整数扩展.
扩展并计算在(( ))中的整数表达式.
请参考关于(( ... )) 结构的讨论.
> &> >& >> < <>
重定向.
scriptname >filename 重定向scriptname的输出到文件filename中. 如果filename存在的话, 那
么将会被覆盖.
command &>filename 重定向command的stdout和stderr到filename中.
command >&2 重定向command的stdout到stderr中.
scriptname >>filename 把scriptname的输出追加到文件filename中. 如果filename不存在的话,
将会被创建.
[i]<>filename 打开文件filename用来读写, 并且分配文件描述符i给这个文件. 如果filename不
存在, 这个文件将会被创建.
进程替换.
(command)>
<(command)
在一种不同的上下文中, "<"和">"可用来做 字符串比较操作.
在另一种上下文中, "<"和">"可用来做 整数比较操作. 参见例子 12-9.
<<
用在here document中的重定向.
<<<
用在here string中的重定向.
<, >
ASCII comparison.
1 veg1=carrots
2 veg2=tomatoes
3
4 if [[ "$veg1" < "$veg2" ]]
5 then
6 echo "Although $veg1 precede $veg2 in the dictionary,"
7 echo "this implies nothing about my culinary preferences."
8 else
9 echo "What kind of dictionary are you using, anyhow?"
10 fi
\<, \>
正则表达式中的单词边界 .
bash$ grep '\<the\>' textfile
|
管道. 分析前边命令的输出, 并将输出作为后边命令的输入. 这是一种产生命令链的好方法.
1 echo ls -l | sh
2 # 传递"echo ls -l"的输出到shell中,
3 #+ 与一个简单的"ls -l"结果相同.
4
5
6 cat *.lst | sort | uniq
7 # 合并和排序所有的".lst"文件, 然后删除所有重复的行.
管道是进程间通讯的一个典型办法, 将一个进程的stdout放到另一个进程的stdin中. 标
准的方法是将一个一般命令的输出, 比如cat或者echo, 传递到一个 "过滤命令"(在这个
过滤命令中将处理输入)中, 然后得到结果.
cat $filename1 $filename2 | grep $search_word
当然输出的命令也可以传递到脚本中.
1 #!/bin/bash
2 # uppercase.sh : 修改输入, 全部转换为大写.
3
4 tr 'a-z' 'A-Z'
5 # 字符范围必须被""引用起来
6 #+ 来阻止产生单字符的文件名.
7
8 exit 0
现在让我们输送ls -l的输出到一个脚本中.
bash$ ls -l | ./uppercase.sh
-RW-RW-R-- 1 BOZO BOZO 109 APR 7 19:49 1.TXT
-RW-RW-R-- 1 BOZO BOZO 109 APR 14 16:48 2.TXT
-RW-R--R-- 1 BOZO BOZO 725 APR 20 20:56 DATA-FILE
管道中的每个进程的stdout比须被下一个进程作为stdin来读入. 否则, 数
据流会阻塞, 并且管道将产生一些非预期的行为.
1 cat file1 file2 | ls -l | sort
2 # 从"cat file1 file2"中的输出并没出现.
作为子进程的运行的管道, 不能够改变脚本的变量.
1 variable="initial_value"
2 echo "new_value" | read variable
3 echo "variable = $variable" # variable =
initial_value
如果管道中的某个命令产生了一个异常,并中途失败,那么这个管道将过早的
终止. 这种行为被叫做broken pipe, 并且这种状态下将发送一个SIGPIPE
信号.
>|
强制重定向(即使设置了noclobber选项 -- 就是-C选项). 这将强制的覆盖一个现存文件.
||
或-逻辑操作. 在一个条件测试结构中, 如果条件测试结构两边中的任意一边结果为true的话,
||操作就会返回0(代表执行成功).
&
后台运行命令. 一个命令后边跟一个& 表示在后台运行.
bash$ sleep 10 &
[1] 850
[1]+ Done sleep 10
在一个脚本中,命令和循环都可能运行在后台.
例子 3-3. 在后台运行一个循环
1 #!/bin/bash
2 # background-loop.sh
3
4 for i in 1 2 3 4 5 6 7 8 9 10 # 第一个循环.
5 do
6 echo -n "$i "
7 done & # 在后台运行这个循环.
8 # 在第2个循环之后, 将在某些时候执行.
9
10 echo # 这个'echo'某些时候将不会显示.
11
12 for i in 11 12 13 14 15 16 17 18 19 20 # 第二个循环.
13 do
14 echo -n "$i "
15 done
16
17 echo # 这个'echo'某些时候将不会显示.
18
19 # ======================================================
20
21 # 期望的输出应该是:
22 # 1 2 3 4 5 6 7 8 9 10
23 # 11 12 13 14 15 16 17 18 19 20
24
25 # 然而实际的结果有可能是:
26 # 11 12 13 14 15 16 17 18 19 20
27 # 1 2 3 4 5 6 7 8 9 10 bozo $
28 # (第2个'echo'没执行, 为什么?)
29
30 # 也可能是:
31 # 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
32 # (第1个'echo'没执行, 为什么?)
33
34 # 非常少见的执行结果, 也有可能是:
35 # 11 12 13 1 2 3 4 5 6 7 8 9 10 14 15 16 17 18 19 20
36 # 前台的循环先于后台的执行.
37
38 exit 0
39
40 # Nasimuddin Ansari 建议加一句 sleep 1
41 #+ 在6行和14行的 echo -n "$i" 之后加这句.
42 #+ 为了真正的乐趣.
在一个脚本内后台运行一个命令,有可能造成这个脚本的挂起,等待一个按键
响应. 幸运的是, 我们有针对这个问题的解决办法.
&&
与-逻辑操作. 在一个条件测试结构中, 只有在条件测试结构的两边结果都为true的时候, &&操作
才会返回0(代表sucess).
-
选项, 前缀. 在所有的命令内如果想使用选项参数的话,前边都要加上"-".
COMMAND -[Option1][Option2][...]
ls -al
sort -dfu $filename
set -- $variable
1 if [ $file1 -ot $file2 ]
2 then
3 echo "File $file1 is older than $file2."
4 fi
5
6 if [ "$a" -eq "$b" ]
7 then
8 echo "$a is equal to $b."
9 fi
10
11 if [ "$c" -eq 24 -a "$d" -eq 47 ]
12 then
13 echo "$c equals 24 and $d equals 47."
14 fi
-
用于重定向stdin或stdout[破折号, 即-].
1 (cd /source/directory && tar cf - . ) | (cd /dest/directory && tar
xpvf -)
2 # 从一个目录移动整个目录树到另一个目录
3 # [感谢Alan Cox <a.cox@swansea.ac.uk>, 走出了部分修改]
4
5 # 1) cd /source/directory 源目录
6 # 2) && "与列表": 如果'cd'命令成功了, 那么就执行下边的
命令.
7 # 3) tar cf - . 'c'创建一个新文档, 'f'后边跟'-'指定目标文件
作为stdout
8 # '-'后边的'f'(file)选项, 指明作为stdout的目
标文件.
9# 并且在当前目录('.')执行.
10 # 4) | 管道...
11 # 5) ( ... ) 一个子shell
12 # 6) cd /dest/directory 改变当前目录到目标目录.
13 # 7) && "与列表", 同上
14 # 8) tar xpvf - 'x'解档, 'p'保证所有权和文件属性,
15 # 'v'发完整消息到stdout,
16 # 'f'后边跟'-',从stdin读取数据.
17 #
18 # :'x' , 'p', 'v', 'f' .
注意是一个命令是选项
19 # Whew!
20
21
22
23 # 更优雅的写法应该是:
24 # cd source/directory
25 # tar cf - . | (cd ../dest/directory; tar xpvf -)
26 #
27 # 当然也可以这么写:
28 # cp -a /source/directory/* /dest/directory
29 # 或者:
30 # cp -a /source/directory/* /source/directory/.[^.]* /dest/directory
31 # 如果在/source/directory中有隐藏文件的话.
1 bunzip2 -c linux-2.6.16.tar.bz2 | tar xvf -
2 # --未解压的tar文件-- | --然后把它传递到"tar"中--
3 # 如果 "tar" 没能够正常的处理"bunzip2",
4 #+ 这就需要使用管道来执行2个单独的步骤来完成它.
5 # 这个练习的目的是解档"bzipped"的kernel源文件.
注意, 在这个上下文中"-"本身并不是一个Bash操作, 而是一个可以被特定的UNIX工具识别的选
项, 这些特定的UNIX工具特指那些可以写输出到stdout的工具, 比如tar, cat, 等等.
bash$ echo "whatever" | cat -
whatever
在需要一个文件名的位置, -重定向输出到stdout(有时候会在tar和cf中出现), 或者从stdin接受
输入, 而不是从一个文件中接受输入. 这是在管道中使用文件导向(file-oriented)工具来作为过
滤器的一种方法.
bash$ file
Usage: file [-bciknvzL] [-f namefile] [-m magicfiles] file...
在命令行上单独给出一个file, 会给出一个错误信息.
添加一个"-"将得到一个更有用的结果. 这会使shell等待用户输入.
bash$ file -
abc
standard input: ASCII text
bash$ file -
#!/bin/bash
standard input: Bourne-Again shell script text executable
现在命令从stdin中接受了输入, 并分析它.
"-"可以被用来将stdout通过管道传递到其他命令中. 这样就允许使用在一个文件开头添加几行的
技巧.
使用diff命令来和另一个文件的某一段进行比较:
grep Linux file1 | diff file2 -
最后, 来展示一个使用-的tar命令的一个真实的例子.
例子 3-4. 备份最后一天所有修改的文件
1 #!/bin/bash
2
3 # 在一个"tarball"中(经过tar和gzip处理过的文件)
4 #+ 备份最后24小时当前目录下d所有修改的文件.
5
6 BACKUPFILE=backup-$(date +%m-%d-%Y)
7# 在备份文件中嵌入时间.
8 # Thanks, Joshua Tschida, for the idea.
9 archive=${1:-$BACKUPFILE}
10 # 如果在命令行中没有指定备份文件的文件名,
11 #+ 那么将默认使用"backup-MM-DD-YYYY.tar.gz".
12
13 tar cvf - `find . -mtime -1 -type f -print` > $archive.tar
14 gzip $archive.tar
15 echo "Directory $PWD backed up in archive file \"$archive.tar.gz\"."
16
17
18 # Stephane Chazelas指出上边代码,
19 #+ 如果在发现太多的文件的时候, 或者是如果文件
20 #+ 名包括空格的时候, 将执行失败.
21
22 # Stephane Chazelas建议使用下边的两种代码之一:
23 # -----------------------------------------------------------------
--
24 # find . -mtime -1 -type f -print0 | xargs -0 tar rvf
"$archive.tar"
25 # 使用gnu版本的"find".
26
27
28 # find . -mtime -1 -type f -exec tar rvf "$archive.tar" '{}' \;
29 # 对于其他风格的UNIX便于移植, 但是比较慢.
30 # -----------------------------------------------------------------
--
31
32
33 exit 0
以"-"开头的文件名在使用"-"作为重定向操作符的时候, 可能会产生问题.
应该写一个脚本来检查这个问题, 并给这个文件加上合适的前缀. 比如:
./-FILENAME, $PWD/-FILENAME, 或者 $PATHNAME/-FILENAME.
如果变量以-开头进行命名, 可能也会引起问题.
1 var="-n"
2 echo $var
3 # 具有"echo -n"的效果了,这样什么都不会输出的.
-
先前的工作目录. cd -将会回到先前的工作目录. 它使用了$OLDPWD 环境变量.
不要混淆这里所使用的"-"和先前我们所讨论的"-"重定向操作符. 对于"-
"的具体解释只能依赖于具体的上下文.
-
减号. 减号属于算术操作.
=
等号. 赋值操作
1 a=28
2 echo $a # 28
在另一种上下文环境中, "="也用来做字符串比较操作.
+
加号. 加法算术操作.
在另一种上下文环境中, +也是一种正则表达式操作.
+
选项. 一个命令或者过滤器的选项标记.
某些命令内建命令使用+来打开特定的选项, 用-来禁用这些特定的选项.
%
取模. 取模(一次除法的余数)算术操作.
在不同的上下文中, %也是一种模式匹配操作.
~
home目录[波浪号, 即~]. 相当于$HOME内部变量. ~bozo是bozo的home目录, 并且ls ~bozo将列
出其中的内容. ~/就是当前用户的home目录, 并且ls ~/将列出其中的内容.
bash$ echo ~bozo
/home/bozo
bash$ echo ~
/home/bozo
bash$ echo ~/
/home/bozo/
bash$ echo ~:
/home/bozo:
bash$ echo ~nonexistent-user
~nonexistent-user
~+
当前工作目录. 相当于$PWD内部变量.
~-
先前的工作目录. 相当于$OLDPWD内部变量.
=~
正则表达式匹配. 这个操作将会在version 3版本的Bash部分进行讲解.
^
行首. 在正则表达式中, "^"表示定位到文本行的行首.
控制字符
修改终端或文本显示的行为. . 控制字符以CONTROL + key这种方式进行组合(同时按下). 控制
字符也可以使用8进制或16进制表示法来进行表示, 但是前边必须要加上转义符.
控制字符在脚本中不能正常使用.
Ctl-B
退格(非破坏性的), 就是退格但是不删掉前面的字符.
Ctl-C
break. 终结一个前台作业.
Ctl-D
从一个shell中登出(与exit很相像).
"EOF"(文件结束). 这也能从stdin中终止输入.
在console或者在xterm窗口中输入的时候, Ctl-D将删除光标下字符. 当没有字符时, Ctl-
D将退出当前会话, 在一个xterm窗口中, 则会产生关闭此窗口的效果.
Ctl-G
"哔" (beep). 在一些老式的打字机终端上, 它会响一下铃.
Ctl-H
"退格"(破坏性的), 就是在退格之后, 还要删掉前边的字符.
1 #!/bin/bash
2 # Embedding Ctl-H in a string.
3
4 a="^H^H" # 两个 Ctl-H's (backspaces).
5 echo "abcdef" # abcdef
6 echo -n "abcdef$a " # abcd f
7 # Space at end ^ ^ 两次退格.
8 echo -n "abcdef$a" # abcdef
9 # 结尾没有空格没有 backspace 的效果了(why?).
10 # 结果并不像期望的那样.
11 echo; echo
Ctl-I
水平制表符.
Ctl-J
重起一行(换一行并到行首). 在脚本中, 也可以使用8进制表示法 -- '\012' 或者16进制
表示法 -- '\x0a' 来表示.
Ctl-K
垂直制表符.
当在console或者xterm窗口中输入文本时, Ctl-K将会删除从光标所在处到行为的全部字
符. 在脚本中, Ctl-K的行为有些不同, 具体请参见下边的Lee Maschmeyer的例子程序.
Ctl-L
清屏(清除终端的屏幕显示). 在终端中, 与clear命令的效果相同. 当发送到打印机上时,
Ctl-L会让打印机将打印纸卷到最后.
Ctl-M
回车.
1 #!/bin/bash
2 # Thank you, Lee Maschmeyer, for this example.
3
4 read -n 1 -s -p $'Control-M leaves cursor at beginning of this
line. Press Enter. \x0d'
5 # 当然, '0d'就是二进制的回车.
6 echo >&2 # '-s'参数使得任何输入都不将回显出来.
7 #+ 所以, 明确的重起一行是必要的.
8
9 read -n 1 -s -p $'Control-J leaves cursor on next line. \x0a'
10 # '0a' 等价于Control-J, 换行.
11 echo >&2
12
13 ###
14
15 read -n 1 -s -p $'And Control-K\x0bgoes straight down.'
16 echo >&2 # Control-K 是垂直制表符.
17
18 # 关于垂直制表符效果的一个更好的例子见下边:
19
20 var=$'\x0aThis is the bottom line\x0bThis is the top line\x0a'
21 echo "$var"
22 # 这句与上边的例子使用的是同样的办法, 然而:
23 echo "$var" | col
24 # 这将造成垂直制表符右边的部分比左边部分高.
25 # 这也解释了为什么我们要在行首和行尾加上一个换行符 --
26 #+ 这样可以避免屏幕显示混乱.
27
28 # Lee Maschmeyer的解释:
29 # --------------------------
30 # 在这里[第一个垂直制表符的例子中] . . .
31 #+ 这个垂直制表符使得还没回车就直接打印下来.
32 # 这只能在那些不能"后退"的设备中才行,
33 #+ 比如说Linux的console.
34 # 垂直制表符的真正意义是向上移, 而不是向下.
35 # 它可以用来让打印机打印上标.
36 # col工具可以模拟垂直制表符的正确行为.
37
38 exit 0
Ctl-Q
恢复(XON).
在一个终端中恢复stdin.
Ctl-S
挂起(XOFF).
在一个终端中冻结stdin. (使用Ctl-Q可以恢复输入.)
Ctl-U
删除光标到行首的所有字符. 在某些设置下, 不管光标的所在位置Ctl-U都将删除整行输
入.
Ctl-V
当输入字符时, Ctl-V允许插入控制字符. 比如, 下边的两个例子是等价的:
1 echo -e '\x0a'
2 echo <Ctl-V><Ctl-J>
Ctl-V主要用于文本编辑.
Ctl-W
当在控制台或一个xterm窗口敲入文本时, Ctl-W将会删除当前光标到左边最近一个空格间
的全部字符. 在某些设置下, Ctl-W将会删除当前光标到左边第一个非字母或数字之间的全
部字符.
Ctl-Z
暂停前台作业.
空白
用来分隔函数, 命令或变量. . 空白包含空格, tab, 空行, 或者是它们之间任意的组合体. [4]
在某些上下文中, 比如变量赋值, 空白是不被允许的, 会产生语法错误.
空行不会影响脚本的行为, 因此使用空行可以很好的划分独立的函数段以增加可读性.
特殊变量$IFS用来做一些输入命令的分隔符, 默认情况下是空白.
如果想在字符串或变量中使用空白, 那么应该使用引用.
注意事项
[1] PID, 或进程 ID, 是分配给运行进程的一个数字. 要想察看所有运行进程的PID可以使
用ps命令.
[2] The shell does the brace expansion. The command itself acts upon the result of
the expansion.
[3] 例外: 在pipe中的一个大括号中的代码段可能运行在一个 子shell中.
1 ls | { read firstline; read secondline; }
2 # 错误. 在大括号中的代码段, 将运行到子shell中,
3 #+ 所以"ls"的输出将不能传递到代码块中.
4 echo "First line is $firstline; second line is $secondline" # 不能工
作.
5
6 # 感谢, S.C.
[4] 一个换行符("重起一行")也被认为是空白符. 这也就解释了为什么一个只包含换行符的空
行也被认为是空白.
前一页首页下一页