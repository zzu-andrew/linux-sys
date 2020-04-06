[TOC]

# 命令基础

## `find`查找文件指定文件类型之后重命名

```bash
#!/bin/bash
#文件名: rename.sh
#用途: 重命名 .jpg 和 .png 文件
count=1;
for img in `find . -iname '*.png' -o -iname '*.jpg' -type f -maxdepth 1`
do
new=image-$count.${img##*.}
echo "Renaming $img to $new"
mv "$img" "$new"
let count++
done
```



## 结合 `&`使用 多核对文件进行`md5sum`计算

```bash
#/bin/bash
#文件名: generate_checksums.sh
PIDARRAY=()
for file in File1.iso File2.iso
do
md5sum $file &
PIDARRAY+=("$!")
done
wait ${PIDARRAY[@]}
```

- 我们利用了Bash的操作符 & ,它使得`shell`将命令置于后台并继续执行脚本。这意味着一旦循
  环结束,脚本就会退出,而 `md5sum` 进程仍在后台运行。为了避免这种情况,我们使用 `$!` 来获得
  进程的`PID`,在Bash中, `$!` 保存着最近一个后台进程的`PID`。我们将这些`PID`放入数组,然后使用
  wait 命令等待这些进程结束

## 生成任意大小的文件

- 创建**环回文件**，环回文件自身包含文件系统，这种文件可以像物理设备一样使用`mount`进行挂载

- 创建特定大小的文件，最为简单的方法就是使用`dd`命令，`dd`命令会克隆给定的输入内容，然后将一模一样的副本输写入到输出。`stdin`、设备文件、普通文件等都可以作为输入，`stdout`、设备文件、普通文件等都可以作为输出。

```bash
$ dd if=/dev/zero of=junk.data bs=1M count=1
1+0 records in
1+0 records out
1048576 bytes (1.0 MB) copied, 0.00767266 s, 137 MB/s
```

- 该命令会创建一个内容全部为零的1MB大小的文件junk.data。

  来看一下命令参数:
   if 表示输入文件(input file)
   of 表示输出文件(output file)
   bs 指定了以字节为单位的块大小(block size)
   count 表示需要被复制的块数。

> 在上面的例子中,我们将 `bs` 指定为`1MB`, `count` 指定为1,于是得到了一个大
> 小为`1MB`的文件。如果把 `bs` 设为`2MB`, `count` 设为`2`,那么总文件大小就是`4MB`。


| 单元大小       | 代码 |
| -------------- | ---- |
| 字节(1B)       | C    |
| 字(2B)         | W    |
| 块(512B)       | B    |
| 千字节(1024B)  | K    |
| 兆字节(1024KB) | M    |
| 吉字节(1024MB) | G    |

> 如果不指定输入`if dd`会从`stdio`中读取输入，如果不指定输出参数`of`，则`dd`会使用`stdout`



## 使用环回文件

- 使用`dd`命令创建一个`1GB`大小的文件

```bash
$ dd if=/dev/zero of=loobackfile.img bs=1G count=1
1024+0 records in
1024+0 records out
1073741824 bytes (1.1 GB) copied, 37.3155 s, 28.8 MB/s
```

> 你会发现创建好的文件大小超过了1GB。这是因为作为块设备,硬盘是按照块大小的整
> 数倍来分配存储空间的

- 用`mkfs`命令将`1GB`的文件格式化为`ext4`文件系统：

```bash
$ mkfs.ext4 loopbackfile.img
```

- 使用`file`命令检查文件系统

```bash
$ file loobackfile.img
loobackfile.img: Linux rev 1.0 ext4 filesystem data,
UUID=c9d56c42-
f8e6-4cbd-aeab-369d5056660a (extents) (large files) (huge files)
```

- 使用`mkdir`创建挂在点，并挂载环回文件

```bash
# mkdir /mnt/loopback
# mount -o loop loopbackfile.img /mnt/loopback
```

> 选项 -o loop 用来挂载环回文件系统。
> 这里用的实际上是一种快捷方式,可以将环回文件系统附加到(attach)由操作系统选定
> 的设备上,这些设备的名称类似于 `/dev/loop1` 或 `/dev/loop2 `。





































