[TOC]



# PlantUML

## 时序图

### 简单的时序图

```bash
@startuml simple 
' 你可以用 -> 来绘制参与者之间传递的消息,而不必显式地声明参与者。
' 你也可以使用 --> 绘制一个虚线箭头。
' 另外,你还能用 <- 和 <--,这不影响绘图,但可以提高可读性。注意:仅适用于时序图,对于其它示意
' 图,规则是不同的。

Alice -> Bob: Authentication Request
Bob --> Alice: Authentication Response

Alice -> Bob: Another authentication Request
Alice <-- Bob: another authentication Response


@enduml 
```



![](/work/linux-sys/UML/out/时序图/simple/simple.png)





### participant改变先后顺序

关键字 participant 用于改变参与者的先后顺序。
你也可以使用其它关键字来声明参与者:
• actor
• boundary
• control
• entity
• database

```bash
@startuml participant

actor Foo1
boundary Foo2
control Foo3
entity Foo4
database Foo5 

collections Foo6
Foo1 -> Foo2 : To boundary
Foo1 -> Foo3 : To control
Foo1 -> Foo4 : To entity
Foo1 -> Foo5 : To database
Foo1 -> Foo6 : To collections

@enduml
```



![](/work/linux-sys/UML/out/时序图/useparticipant/participant.png)



### 使用as重命名参与者

```bash
@startuml sequence_as
actor Bob #red
' The only difference between actor
' and participant is the drawing
participant Alice
participant "I have a really\nlong name" as L #99FF99
/' You can also declare:
participant L as "I have a really\nlong name" #99FF99
'/
Alice->Bob: Authentication Request
Bob->Alice: Authentication Response
Bob->L: Log transaction
@enduml
```



![](/work/linux-sys/UML/out/时序图/sequence_as/sequence_as.png)





### order改变参与者的顺序

​    使用`order`改变参与者的顺序，`order`的顺序越小越靠前

```bash
@startuml sequence_order
' 通过order 定义参与者顺序
participant Last order 30
participant Middle order 20
participant First order 10
@enduml
```





![](/work/linux-sys/UML/out/时序图/sequence_order/sequence_order.png)

### 使用非字母符号

```bash
@startuml sequence_no_alphabet
' 引号中可以使用非字母符号
' 你可以使用引号定义参与者，还可以使用关键字 as 给参与者定义别名
Alice -> "Bob()" : Hello
"Bob()" -> "This is very\nlong" as Long
' You can also declare:
' "Bob()" -> Long as "This is very\nlong"
Long --> "Bob()" : ok

@enduml 

```



![](/work/linux-sys/UML/out/时序图/sequence_no_alphabet/sequence_no_alphabet.png)

### 修改箭头样式

​    使用不同样式的箭头

```bash
@startuml arrow_num

' • 表示一条丢失的消息:末尾加 x
' • 让箭头只有上半部分或者下半部分:将 < 和 > 替换成 \ 或者 /
' • 细箭头:将箭头标记写两次 (如 >> 或 //)
' • 虚线箭头:用 -- 替代 -
' • 箭头末尾加圈:->o
' • 双向箭头:<->

Bob ->x Alice : 末尾加 x
Bob -> Alice : 常规箭头
Bob ->> Alice : 细箭头
Bob -\ Alice : 粗箭头只保留上半部分
Bob \\- Alice : 细箭头 只保留下半部分
Bob //-- Alice  : 细箭头只保留上半部分
Bob ->o Alice : 实线箭头  带圆圈
Bob o\\-- Alice : 虚线细箭头 只保留一半 带圆圈
Bob <-> Alice : 双向实线箭头
Bob <->o Alice : 双向实线箭头  右侧带圆圈

@enduml 
```

![](/work/linux-sys/UML/out/时序图/sequence_arrow/arrow_num.png)



### 修改箭头的箭头的颜色

```bash
@startuml  change_arrow_color
Bob -[#red]> Alice : hello
Alice -[#0000FF]->Bob : ok
@enduml
```



![](/work/linux-sys/UML/out/时序图/sequence_change_arrow_color/change_arrow_color.png)

### 对消息序列进行编号

```bash
@startuml  autonumber
autonumber
Bob -> Alice : Authentication Request
Bob <- Alice : Authentication Response
@enduml
```





![](/work/linux-sys/UML/out/时序图/sequence_autonumber/autonumber.png)





```bash
@startuml autonumber_start_increment

' 语句 autonumber start 用于指定编号的初始值,而 autonumber start increment 可以同时指定编号
' 的初始值和每次增加的值。
autonumber
Bob -> Alice : Authentication Request
Bob <- Alice : Authentication Response
autonumber 15
Bob -> Alice : Another authentication Request
Bob <- Alice : Another authentication Response
autonumber 40 10
Bob -> Alice : Yet another authentication Request
Bob <- Alice : Yet another authentication Response

@enduml 
```



![](/work/linux-sys/UML/out/时序图/sequence_start_increment/autonumber_start_increment.png)























