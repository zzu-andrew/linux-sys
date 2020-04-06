[TOC]



# U-boot Makefile国建过程



## 主机构建环境配置过程

### 定义主机系统架构

```bash
HOSTARCH := $(shell uname -m | \
		sed -e s/i.86/i386/ \
	    -e s/sun4u/sparc64/ \
	    -e s/arm.*/arm/ \
	    -e s/sa110/arm/ \
	    -e s/powerpc/ppc/ \
	    -e s/ppc64/ppc/ \
	    -e s/macppc/ppc/)
```

`$(shell xxx)`是shell后面的语句，按照shell脚本进行执行

`sed -e s/in/out/`是将输入的`in`替换成`out`

运行示例：

```bash
andrew@andrew-Thurley:~/work/test$ uname -m
x86_64
# .为单个字符的通配符
andrew@andrew-Thurley:~/work/test$ uname -m |sed -e s/x86.64/x86/ 
x86
```

### 定义主机操作系统类型

```bash
HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')
```

`tr '[:upper:]' '[:lower:]'`的作用是将标准输入中的所有大写字母转换为小写字母

**执行示例**

```bash
andrew@andrew-Thurley:~/work/test$ uname -s | tr '[:upper:]' '[:lower:]' | sed -e 's/\(cygwin\).*/cygwin/'
linux
```

### 定义SHELL脚本的解释器

  `uboot`顶层的`Makefile`通过如下代码定义了`shell`脚本的解释器`SHELL`。"$$BASH"的作用实质上是生成字符串"$BASH"   ,前一个`$`的作用是说明第二个`$`是普通字符。

```bash
# Set shell to bash if possible, otherwise fall back to sh
SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	else if [ -x /bin/bash ]; then echo /bin/bash; \
	else echo sh; fi; fi)
```

  上述脚本的作用为，若当前`Makefile`的`shell`中定义了`$BASH`环境变量，且文件`$BASH`是可执行文件，则`SHELL`的值为`”$BASH“`，若`/bin/bash`是可执行文件，则`SHELL`的值为`"/bin/bash"`。若以上两者都不成立，将`sh`赋值给`SHELL`变量。

### 设定编译输出目录

```bash
ifdef O
ifeq ("$(origin O)", "command line")
BUILD_DIR := $(O)
endif
endif
```
`$(origin O)`表示，`(origin O)`函数的输出，`$(origin variable)`的输出是结果是一个字符串，由变量`variable`定义的方式决定，若`variable`是作为`make`的参数时，`$(origin variable)`输出`commond line`字符串。
  以上方式实现的效果为 `make O=/tmp/buildall`, 因为，O作为make的参数，所以`$(origin variable)`输出`commond line`， `BUILD_DIR`为`/tmp/buildall`。

  

接下来的配置如下：
```bash
ifneq ($(BUILD_DIR),) #如果目录存在，就将目录赋值给saved-output
saved-output := $(BUILD_DIR)

# Attempt to create a output directory.
# 目录存在接着执行，目录不存在创建目录
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR})

# Verify if it was successful.
# 确保目录存在
BUILD_DIR := $(shell cd $(BUILD_DIR) && /bin/pwd)
# 对目录进行检测
$(if $(BUILD_DIR),,$(error output directory "$(saved-output)" does not exist))
endif # ifneq ($(BUILD_DIR),)
```

CURDIR表示的是当前目录
OBJTREE 若是没有定义BUILD_DIR，则输出目录就是CURDIR，也就是执行make的地方，这就是执行make没有指定目录的时候生成的u-boot会在顶层目录上。
`$(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))`如果第BUILD_DIR存在就BUILD_DIR，入股不存在就使用CURDIR
```bash

OBJTREE		:= $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))
SRCTREE		:= $(CURDIR)
TOPDIR		:= $(SRCTREE)
LNDIR		:= $(OBJTREE)
export	TOPDIR SRCTREE OBJTREE

MKCONFIG	:= $(SRCTREE)/mkconfig
export MKCONFIG

ifneq ($(OBJTREE),$(SRCTREE))
REMOTE_BUILD	:= 1
export REMOTE_BUILD
endif

```

在没有包含config.mk之前先将obj,src变量定义好，并临时放到环境中
`export obj src`
```bash
# $(obj) and (src) are defined in config.mk but here in main Makefile
# we also need them before config.mk is included which is the case for
# some targets like unconfig, clean, clobber, distclean, etc.
ifneq ($(OBJTREE),$(SRCTREE))
obj := $(OBJTREE)/
src := $(SRCTREE)/
else
obj :=
src :=
endif
export obj src
```

### 目标机相关配置过程

顶层`Makefile`存在与具体开发板的相关配置，其中`@`的作用就执行该命令时不显示`obj`是编译输出的目录，因此`unconfig`的作用就是清楚上次执行`make *_config`命令生成的配置文件。
`$(@:_config=)`将传进来的所有参数的`_config`替换为空，其中`@`是指规则的目标，使用的语法为`@(text:patternA=patternB)`这样的语法，将`text`中所有以`patternA`结尾的文本替换为`patternB`，因此`$(@:_config=)`的作用是将`smdk2410_config`后面的`_config`去掉，得到`smdk2410`    

最终的效果相当于：
`@$(MKCONFIG) $(@:_config=) arm arm920t smdk2410 samsung s3c24x0`
==>
`./mkconfig smdk2410 arm arm920t smdk2410 samsung s3c24x0`

这种使用方法在`mkconfig`中有给出
`# Parameters:  Target  Architecture  CPU  Board [VENDOR] [SOC]`


```bash
unconfig:
	@rm -f $(obj)include/config.h $(obj)include/config.mk \
		$(obj)board/*/config.tmp $(obj)board/*/*/config.tmp \
		$(obj)include/autoconf.mk $(obj)include/autoconf.mk.dep

smdk2410_config	:	unconfig
	@$(MKCONFIG) $(@:_config=) arm arm920t smdk2410 samsung s3c24x0


```

## mkconfig脚本

### 传递给mkconfig脚本参数
传递给`mkconfig`脚本的含义如下：

- smdk2410, Target(目标板的型号)
- arm, Architecture(目标板的CPU架构)
- arm920t, CPU(CPU使用的具体CPU型号)
- smdk2410，开发板名称
- samsung,VENDOR生产厂家名称
- s3c24x0,SOC(片上系统)

其中环境变量`$#`表示传递给脚本的的参数的个数，
`shift`的作用是原来的参数`$1`将丢失，并将后面的参数向前进行平移，


```bash
APPEND=no	# Default: Create new config file
BOARD_NAME=""	# Name to print in make output
TARGETS=""

while [ $# -gt 0 ] ; do
	case "$1" in
	--) shift ; break ;;
	-a) shift ; APPEND=yes ;;
	-n) shift ; BOARD_NAME="${1%%_config}" ; shift ;;
	-t) shift ; TARGETS="`echo $1 | sed 's:_: :g'` ${TARGETS}" ; shift ;;
	*)  break ;;
	esac
done

[ "${BOARD_NAME}" ] || BOARD_NAME="$1"
```
上述代码执行结束之后  `BOARD_NAME = smdk2410`,因为顶层Makefile构造的`mkconfig执行语句为` ：`./mkconfig smdk2410 arm arm920t smdk2410 samsung s3c24x0`

### 检查参数合法性
   下面的代码用于检查参数的合法性，参数的个数少于4个和多于6个都将认为是不合法的

```bash
[ $# -lt 4 ] && exit 1
[ $# -gt 6 ] && exit 1

if [ "${ARCH}" -a "${ARCH}" != "$2" ]; then
	echo "Failed: \$ARCH=${ARCH}, should be '$2' for ${BOARD_NAME}" 1>&2
	exit 1
fi
```

### 创建到目录板相关目录的链接

   若编译输出到外部目录，则下面代码游戏哦啊。
   `"$SRCTREE" != "$OBJTREE"`条件成立的时候，就是外部定义了输出外部目录的时候

```bash
#
# Create link to architecture specific headers
#
if [ "$SRCTREE" != "$OBJTREE" ] ; then
	mkdir -p ${OBJTREE}/include
	mkdir -p ${OBJTREE}/include2
	cd ${OBJTREE}/include2
	rm -f asm
	ln -s ${SRCTREE}/include/asm-$2 asm
	LNPREFIX="../../include2/asm/"
	cd ../include
	rm -rf asm-$2
	rm -f asm
	mkdir asm-$2
	ln -s asm-$2 asm
```

 若将目标文件设定为输出到源文件所在目录，就在顶层目录中的include目录下建立到`asm-arm`目录的符号连接，代码如下，其中的`ln -s asm-$2 asm`即 `ln -s asm-arm asm`
```bash
else
	cd ./include
	rm -f asm
	ln -s asm-$2 asm
fi
```

 紧接着该脚本通过下面的代码建立符号链接`include/asm-arm/arch`，若`&6`(SOC)为空，则其链接到`include/asm-arm/arch-arm920t`目录，否则使其链接到`include/asm-arm/arch-s3cx0`目录，事实上`include/asm-arm/arch-arm920t`并不存在，因此第六个参数必须填写。，否则会编译失效。

```bash
rm -f asm-$2/arch

if [ -z "$6" -o "$6" = "NULL" ] ; then
	ln -s ${LNPREFIX}arch-$3 asm-$2/arch
else
	ln -s ${LNPREFIX}arch-$6 asm-$2/arch
fi
```

开发板是`arm`架构 proc链接到`proc-armv`下。
```bash
if [ "$2" = "arm" ] ; then
	rm -f asm-$2/proc
	ln -s ${LNPREFIX}proc-armv asm-$2/proc
fi
```

### 构建`include/config.mk`文件

```bash
#
# Create include file for Make
#
echo "ARCH   = $2" >  config.mk
echo "CPU    = $3" >> config.mk
echo "BOARD  = $4" >> config.mk

[ "$5" ] && [ "$5" != "NULL" ] && echo "VENDOR = $5" >> config.mk

[ "$6" ] && [ "$6" != "NULL" ] && echo "SOC    = $6" >> config.mk
```
上面代码实现的内容
```bash
ARCH   = arm
CPU    = arm920t
BOARD  = smdk2410
VENDOR = samsung
SOC    = s3c24x0
```

### 构建`include/config.h`文件


```bash
#
# Create board specific header file
#
if [ "$APPEND" = "yes" ]	# Append to existing config file
then
	echo >> config.h  #加个回车键
else
	> config.h		# Create new config file
fi
echo "/* Automatically generated - do not edit */" >>config.h

for i in ${TARGETS} ; do
	echo "#define CONFIG_MK_${i} 1" >>config.h ;
done

echo "#include <configs/$1.h>" >>config.h
echo "#include <asm/config.h>" >>config.h

exit 0

```

## make命令执行过程
 在搞清楚主机的构建环境和目标机相关配置之后，下面来分析执行`make`命令并最终生成`u-boot`镜像的过程。


正常的执行`make smdk2410_config`时会进入到`ifeq`的目录。

若主机和开发板的环境一样，则使用主机编译器，交叉编译工具定义为空
```bash
# set default to nothing for native builds
ifeq ($(HOSTARCH),$(ARCH))
CROSS_COMPILE ?=
endif
```

紧接着包含顶层目录下的`config.mk`
```bash
# load other configuration
include $(TOPDIR)/config.mk
```

```bash

# The "tools" are needed early, so put this first
# Don't include stuff already done in $(LIBS)
SUBDIRS	= tools \
	  examples/standalone \
	  examples/api

.PHONY : $(SUBDIRS)

ifeq ($(obj)include/config.mk,$(wildcard $(obj)include/config.mk))

# Include autoconf.mk before config.mk so that the config options are available
# to all top level build files.  We need the dummy all: target to prevent the
# dependency target in autoconf.mk.dep from being the default.
all:
sinclude $(obj)include/autoconf.mk.dep
sinclude $(obj)include/autoconf.mk

# load ARCH, BOARD, and CPU configuration
include $(obj)include/config.mk
export	ARCH CPU BOARD VENDOR SOC

# set default to nothing for native builds
ifeq ($(HOSTARCH),$(ARCH))
CROSS_COMPILE ?=
endif

# load other configuration
include $(TOPDIR)/config.mk

#########################################################################
# U-Boot objects....order is important (i.e. start must be first)

OBJS  = cpu/$(CPU)/start.o
ifeq ($(CPU),i386)
OBJS += cpu/$(CPU)/start16.o
OBJS += cpu/$(CPU)/resetvec.o
endif
ifeq ($(CPU),ppc4xx)
OBJS += cpu/$(CPU)/resetvec.o
endif
ifeq ($(CPU),mpc85xx)
OBJS += cpu/$(CPU)/resetvec.o
endif

OBJS := $(addprefix $(obj),$(OBJS))

LIBS  = lib_generic/libgeneric.a
LIBS += lib_generic/lzma/liblzma.a
LIBS += lib_generic/lzo/liblzo.a
LIBS += $(shell if [ -f board/$(VENDOR)/common/Makefile ]; then echo \
	"board/$(VENDOR)/common/lib$(VENDOR).a"; fi)
LIBS += cpu/$(CPU)/lib$(CPU).a
ifdef SOC
LIBS += cpu/$(CPU)/$(SOC)/lib$(SOC).a
endif
ifeq ($(CPU),ixp)
LIBS += cpu/ixp/npe/libnpe.a
endif
LIBS += lib_$(ARCH)/lib$(ARCH).a
LIBS += fs/cramfs/libcramfs.a fs/fat/libfat.a fs/fdos/libfdos.a fs/jffs2/libjffs2.a \
	fs/reiserfs/libreiserfs.a fs/ext2/libext2fs.a fs/yaffs2/libyaffs2.a \
	fs/ubifs/libubifs.a
LIBS += net/libnet.a
LIBS += disk/libdisk.a
LIBS += drivers/bios_emulator/libatibiosemu.a
LIBS += drivers/block/libblock.a
LIBS += drivers/dma/libdma.a
LIBS += drivers/fpga/libfpga.a
LIBS += drivers/gpio/libgpio.a
LIBS += drivers/hwmon/libhwmon.a
LIBS += drivers/i2c/libi2c.a
LIBS += drivers/input/libinput.a
LIBS += drivers/misc/libmisc.a
LIBS += drivers/mmc/libmmc.a
LIBS += drivers/mtd/libmtd.a
LIBS += drivers/mtd/nand/libnand.a
LIBS += drivers/mtd/onenand/libonenand.a
LIBS += drivers/mtd/ubi/libubi.a
LIBS += drivers/mtd/spi/libspi_flash.a
LIBS += drivers/net/libnet.a
LIBS += drivers/net/phy/libphy.a
LIBS += drivers/net/sk98lin/libsk98lin.a
LIBS += drivers/pci/libpci.a
LIBS += drivers/pcmcia/libpcmcia.a
LIBS += drivers/power/libpower.a
LIBS += drivers/spi/libspi.a
ifeq ($(CPU),mpc83xx)
LIBS += drivers/qe/qe.a
endif
ifeq ($(CPU),mpc85xx)
LIBS += drivers/qe/qe.a
LIBS += cpu/mpc8xxx/ddr/libddr.a
LIBS += cpu/mpc8xxx/lib8xxx.a
TAG_SUBDIRS += cpu/mpc8xxx
endif
ifeq ($(CPU),mpc86xx)
LIBS += cpu/mpc8xxx/ddr/libddr.a
LIBS += cpu/mpc8xxx/lib8xxx.a
TAG_SUBDIRS += cpu/mpc8xxx
endif
LIBS += drivers/rtc/librtc.a
LIBS += drivers/serial/libserial.a
LIBS += drivers/twserial/libtws.a
LIBS += drivers/usb/gadget/libusb_gadget.a
LIBS += drivers/usb/host/libusb_host.a
LIBS += drivers/usb/musb/libusb_musb.a
LIBS += drivers/video/libvideo.a
LIBS += drivers/watchdog/libwatchdog.a
LIBS += common/libcommon.a
LIBS += libfdt/libfdt.a
LIBS += api/libapi.a
LIBS += post/libpost.a

LIBS := $(addprefix $(obj),$(LIBS))
.PHONY : $(LIBS) $(TIMESTAMP_FILE) $(VERSION_FILE)

LIBBOARD = board/$(BOARDDIR)/lib$(BOARD).a
LIBBOARD := $(addprefix $(obj),$(LIBBOARD))

# Add GCC lib
ifdef USE_PRIVATE_LIBGCC
ifeq ("$(USE_PRIVATE_LIBGCC)", "yes")
PLATFORM_LIBGCC = -L $(OBJTREE)/lib_$(ARCH) -lgcc
else
PLATFORM_LIBGCC = -L $(USE_PRIVATE_LIBGCC) -lgcc
endif
else
PLATFORM_LIBGCC = -L $(shell dirname `$(CC) $(CFLAGS) -print-libgcc-file-name`) -lgcc
endif
PLATFORM_LIBS += $(PLATFORM_LIBGCC)
export PLATFORM_LIBS

# Special flags for CPP when processing the linker script.
# Pass the version down so we can handle backwards compatibility
# on the fly.
LDPPFLAGS += \
	-include $(TOPDIR)/include/u-boot/u-boot.lds.h \
	$(shell $(LD) --version | \
	  sed -ne 's/GNU ld version \([0-9][0-9]*\)\.\([0-9][0-9]*\).*/-DLD_MAJOR=\1 -DLD_MINOR=\2/p')

ifeq ($(CONFIG_NAND_U_BOOT),y)
NAND_SPL = nand_spl
U_BOOT_NAND = $(obj)u-boot-nand.bin
endif

ifeq ($(CONFIG_ONENAND_U_BOOT),y)
ONENAND_IPL = onenand_ipl
U_BOOT_ONENAND = $(obj)u-boot-onenand.bin
ONENAND_BIN ?= $(obj)onenand_ipl/onenand-ipl-2k.bin
endif

__OBJS := $(subst $(obj),,$(OBJS))
__LIBS := $(subst $(obj),,$(LIBS)) $(subst $(obj),,$(LIBBOARD))

#########################################################################
#########################################################################

# Always append ALL so that arch config.mk's can add custom ones
ALL += $(obj)u-boot.srec $(obj)u-boot.bin $(obj)System.map $(U_BOOT_NAND) $(U_BOOT_ONENAND)

all:		$(ALL)

$(obj)u-boot.hex:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@

$(obj)u-boot.srec:	$(obj)u-boot
		$(OBJCOPY) -O srec $< $@

$(obj)u-boot.bin:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O binary $< $@

$(obj)u-boot.ldr:	$(obj)u-boot
		$(obj)tools/envcrc --binary > $(obj)env-ldr.o
		$(LDR) -T $(CONFIG_BFIN_CPU) -c $@ $< $(LDR_FLAGS)

$(obj)u-boot.ldr.hex:	$(obj)u-boot.ldr
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@ -I binary

$(obj)u-boot.ldr.srec:	$(obj)u-boot.ldr
		$(OBJCOPY) ${OBJCFLAGS} -O srec $< $@ -I binary

$(obj)u-boot.img:	$(obj)u-boot.bin
		./tools/mkimage -A $(ARCH) -T firmware -C none \
		-a $(TEXT_BASE) -e 0 \
		-n $(shell sed -n -e 's/.*U_BOOT_VERSION//p' $(VERSION_FILE) | \
			sed -e 's/"[	 ]*$$/ for $(BOARD) board"/') \
		-d $< $@

$(obj)u-boot.kwb:       $(obj)u-boot.bin
		$(obj)tools/mkimage -n $(KWD_CONFIG) -T kwbimage \
		-a $(TEXT_BASE) -e $(TEXT_BASE) -d $< $@

$(obj)u-boot.sha1:	$(obj)u-boot.bin
		$(obj)tools/ubsha1 $(obj)u-boot.bin

$(obj)u-boot.dis:	$(obj)u-boot
		$(OBJDUMP) -d $< > $@

GEN_UBOOT = \
		UNDEF_SYM=`$(OBJDUMP) -x $(LIBBOARD) $(LIBS) | \
		sed  -n -e 's/.*\($(SYM_PREFIX)__u_boot_cmd_.*\)/-u\1/p'|sort|uniq`;\
		cd $(LNDIR) && $(LD) $(LDFLAGS) $$UNDEF_SYM $(__OBJS) \
			--start-group $(__LIBS) --end-group $(PLATFORM_LIBS) \
			-Map u-boot.map -o u-boot
$(obj)u-boot:	depend $(SUBDIRS) $(OBJS) $(LIBBOARD) $(LIBS) $(LDSCRIPT) $(obj)u-boot.lds
		$(GEN_UBOOT)
ifeq ($(CONFIG_KALLSYMS),y)
		smap=`$(call SYSTEM_MAP,u-boot) | \
			awk '$$2 ~ /[tTwW]/ {printf $$1 $$3 "\\\\000"}'` ; \
		$(CC) $(CFLAGS) -DSYSTEM_MAP="\"$${smap}\"" \
			-c common/system_map.c -o $(obj)common/system_map.o
		$(GEN_UBOOT) $(obj)common/system_map.o
endif

$(OBJS):	depend
		$(MAKE) -C cpu/$(CPU) $(if $(REMOTE_BUILD),$@,$(notdir $@))

$(LIBS):	depend $(SUBDIRS)
		$(MAKE) -C $(dir $(subst $(obj),,$@))

$(LIBBOARD):	depend $(LIBS)
		$(MAKE) -C $(dir $(subst $(obj),,$@))

$(SUBDIRS):	depend
		$(MAKE) -C $@ all

$(LDSCRIPT):	depend
		$(MAKE) -C $(dir $@) $(notdir $@)

$(obj)u-boot.lds: $(LDSCRIPT)
		$(CPP) $(CPPFLAGS) $(LDPPFLAGS) -ansi -D__ASSEMBLY__ -P - <$^ >$@

$(NAND_SPL):	$(TIMESTAMP_FILE) $(VERSION_FILE) $(obj)include/autoconf.mk
		$(MAKE) -C nand_spl/board/$(BOARDDIR) all

$(U_BOOT_NAND):	$(NAND_SPL) $(obj)u-boot.bin
		cat $(obj)nand_spl/u-boot-spl-16k.bin $(obj)u-boot.bin > $(obj)u-boot-nand.bin

$(ONENAND_IPL):	$(TIMESTAMP_FILE) $(VERSION_FILE) $(obj)include/autoconf.mk
		$(MAKE) -C onenand_ipl/board/$(BOARDDIR) all

$(U_BOOT_ONENAND):	$(ONENAND_IPL) $(obj)u-boot.bin
		cat $(ONENAND_BIN) $(obj)u-boot.bin > $(obj)u-boot-onenand.bin

$(VERSION_FILE):
		@( printf '#define U_BOOT_VERSION "U-Boot %s%s"\n' "$(U_BOOT_VERSION)" \
		 '$(shell $(TOPDIR)/tools/setlocalversion $(TOPDIR))' ) > $@.tmp
		@cmp -s $@ $@.tmp && rm -f $@.tmp || mv -f $@.tmp $@

$(TIMESTAMP_FILE):
		@date +'#define U_BOOT_DATE "%b %d %C%y"' > $@
		@date +'#define U_BOOT_TIME "%T"' >> $@

gdbtools:
		$(MAKE) -C tools/gdb all || exit 1

updater:
		$(MAKE) -C tools/updater all || exit 1

env:
		$(MAKE) -C tools/env all MTD_VERSION=${MTD_VERSION} || exit 1

depend dep:	$(TIMESTAMP_FILE) $(VERSION_FILE) $(obj)include/autoconf.mk
		for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir _depend ; done

TAG_SUBDIRS += include
TAG_SUBDIRS += lib_generic board/$(BOARDDIR)
TAG_SUBDIRS += cpu/$(CPU)
TAG_SUBDIRS += lib_$(ARCH)
TAG_SUBDIRS += fs/cramfs
TAG_SUBDIRS += fs/fat
TAG_SUBDIRS += fs/fdos
TAG_SUBDIRS += fs/jffs2
TAG_SUBDIRS += fs/yaffs2
TAG_SUBDIRS += net
TAG_SUBDIRS += disk
TAG_SUBDIRS += common
TAG_SUBDIRS += drivers/bios_emulator
TAG_SUBDIRS += drivers/block
TAG_SUBDIRS += drivers/gpio
TAG_SUBDIRS += drivers/hwmon
TAG_SUBDIRS += drivers/i2c
TAG_SUBDIRS += drivers/input
TAG_SUBDIRS += drivers/misc
TAG_SUBDIRS += drivers/mmc
TAG_SUBDIRS += drivers/mtd
TAG_SUBDIRS += drivers/mtd/nand
TAG_SUBDIRS += drivers/mtd/onenand
TAG_SUBDIRS += drivers/mtd/spi
TAG_SUBDIRS += drivers/net
TAG_SUBDIRS += drivers/net/sk98lin
TAG_SUBDIRS += drivers/pci
TAG_SUBDIRS += drivers/pcmcia
TAG_SUBDIRS += drivers/qe
TAG_SUBDIRS += drivers/rtc
TAG_SUBDIRS += drivers/serial
TAG_SUBDIRS += drivers/spi
TAG_SUBDIRS += drivers/usb
TAG_SUBDIRS += drivers/video

tags ctags:
		ctags -w -o $(obj)ctags `find $(SUBDIRS) $(TAG_SUBDIRS) \
						-name '*.[ch]' -print`

etags:
		etags -a -o $(obj)etags `find $(SUBDIRS) $(TAG_SUBDIRS) \
						-name '*.[ch]' -print`
cscope:
		find $(SUBDIRS) $(TAG_SUBDIRS) -name '*.[ch]' -print \
						> cscope.files
		cscope -b -q -k

SYSTEM_MAP = \
		$(NM) $1 | \
		grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | \
		LC_ALL=C sort
$(obj)System.map:	$(obj)u-boot
		@$(call SYSTEM_MAP,$<) > $(obj)System.map

#
# Auto-generate the autoconf.mk file (which is included by all makefiles)
#
# This target actually generates 2 files; autoconf.mk and autoconf.mk.dep.
# the dep file is only include in this top level makefile to determine when
# to regenerate the autoconf.mk file.
$(obj)include/autoconf.mk.dep: $(obj)include/config.h include/common.h
	@$(XECHO) Generating $@ ; \
	set -e ; \
	: Generate the dependancies ; \
	$(CC) -x c -DDO_DEPS_ONLY -M $(HOSTCFLAGS) $(CPPFLAGS) \
		-MQ $(obj)include/autoconf.mk include/common.h > $@

$(obj)include/autoconf.mk: $(obj)include/config.h
	@$(XECHO) Generating $@ ; \
	set -e ; \
	: Extract the config macros ; \
	$(CPP) $(CFLAGS) -DDO_DEPS_ONLY -dM include/common.h | \
		sed -n -f tools/scripts/define2mk.sed > $@.tmp && \
	mv $@.tmp $@

#########################################################################
else	# !config.mk
all $(obj)u-boot.hex $(obj)u-boot.srec $(obj)u-boot.bin \
$(obj)u-boot.img $(obj)u-boot.dis $(obj)u-boot \
$(SUBDIRS) $(TIMESTAMP_FILE) $(VERSION_FILE) gdbtools updater env depend \
dep tags ctags etags cscope $(obj)System.map:
	@echo "System not configured - see README" >&2
	@ exit 1
endif	# config.mk

```


## 顶层目录`config,mk`分析


**设置编译选项**

```bash
# clean the slate ...
PLATFORM_RELFLAGS =
PLATFORM_CPPFLAGS =
PLATFORM_LDFLAGS =
```
检查编译器是否支持某些选项的函数定义

```bash
#########################################################################
#
# Option checker (courtesy linux kernel) to ensure
# only supported compiler options are used
#
cc-option = $(shell if $(CC) $(CFLAGS) $(1) -S -o /dev/null -xc /dev/null \
		> /dev/null 2>&1; then echo "$(1)"; else echo "$(2)"; fi ;)
```
函数使用
可以向这样调用cc-option函数
GFLAGS += $(call cc-option, option1, option2)

```bash
CFLAGS += $(call cc-option,-fno-stack-protector)
```


**执行交叉编译工具**
```bash
#
# Include the make variables (CC, etc...)
#
AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
CPP	= $(CC) -E
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
LDR	= $(CROSS_COMPILE)ldr
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)RANLIB
```


对于arm开发板，上面代码中的CROSS_COMPILE在lib_arm/config.mk中定义
`CROSS_COMPILE ?= arm-linux-`

### 包含与开发板相关的配置文件

在下面的代码中，`$(ARCH)`的值为"arm"，因此将`lib_arm/config.mk`包含进来
```bash
# Load generated board configuration
sinclude $(OBJTREE)/include/autoconf.mk

ifdef	ARCH
sinclude $(TOPDIR)/lib_$(ARCH)/config.mk	# include architecture dependend rules
endif
```

depend的作用是，生成depend依赖，执行该命令将一次进入`$(SUBDIRS)`表示的子目录中，并执行，`make _depend`命令，生成各个子目录中的.depend文件，在.depend文件中列出每个目标文件的依赖文件
```bash
$(obj)u-boot:	depend $(SUBDIRS) $(OBJS) $(LIBBOARD) $(LIBS) $(LDSCRIPT) $(obj)u-boot.lds
		$(GEN_UBOOT)
```




### `u-boot.lds`文件

```bash
# 指定输出的可执行文件是32位的ARM指令，小端模式的ELF格式
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
# 指定输出可执行平台为ARM
OUTPUT_ARCH(arm)

# 指定程序的入口为_start
ENTRY(_start)
SECTIONS
{
    # 指定目标代码的起始地址从0x00开始，"."代表当前位置
	. = 0x00000000;
    # 标示4字节对齐
	. = ALIGN(4);
	.text :
	{
        # 表明 start.o是代码段的第一个.o文件
		cpu/arm920t/start.o	(.text)
        # 代码段的其余部分
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(4);
    # 数据段
	.data : { *(.data) }

	. = ALIGN(4);
	.got : { *(.got) }

	. = .;
	__u_boot_cmd_start = .;
	.u_boot_cmd : { *(.u_boot_cmd) }
	__u_boot_cmd_end = .;

	. = ALIGN(4);
    # __bss_start 标号指向bss段的开始位置
	__bss_start = .;
    # 这里是bss段 存放程序中位初始化变量的一块内存
	.bss (NOLOAD) : { *(.bss) . = ALIGN(4); }
	_end = .;
}
```