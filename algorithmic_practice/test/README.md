

## 生成文件箭头上显示箭头指向的方式

```graph
[ time_t-->struct tm ] { shape: edge; }
[time] -- [ time_t-->struct tm ]  --> [gmtime]
```
- 执行之后

```bash
+------+      time_t-->struct tm        +--------+
| time | -----------------------------> | gmtime |
+------+                                +--------+
```

- simple

```
[ car ] { shape: edge; }

[ Bonn ] -- train --> [ Berlin ] -- [ car ] --> [ Ulm ]

[ rented ] --> [ car ]
```
graph
```
+------+  train   +--------+      car           +-----+
| Bonn | -------> | Berlin | -----------------> | Ulm |
+------+          +--------+                    +-----+
                                   ^
                                   |
                                   |
                                 +--------+
                                 | rented |
                                 +--------+
```

```
[ time_t-->struct tm ] { shape: edge; }
[ struct tm-->formit tm to string ] { shape: edge; }

[ time ] -- [ time_t-->struct tm ]  --> [ localtime ]
--[ struct tm-->formit tm to string ]--> [ strftime ]
```

```
+------+      time_t-->struct tm        +-----------+      struct tm-->formit tm to string        +----------+
| time | -----------------------------> | localtime | ------------------------------------------> | strftime |
+------+                                +-----------+                                             +----------+
```




