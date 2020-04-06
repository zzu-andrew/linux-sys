# Makefile.inc - common definitions used by all makefiles

UNIX_NET_DIR = ..
UNIX_NET_LIB = ${UNIX_NET_DIR}/lib/unix_net_lib.a
UNIX_NET_INCL_DIR = ${UNIX_NET_DIR}/inc

LINUX_LIBRT = -lrt
LINUX_LIBDL = -ldl
LINUX_LIBACL = -lacl
LINUX_LIBCRYPT = -lcrypt
LINUX_LIBCAP = -lcap


IMPL_CFLAGS = -std=c99 -O0 -D_XOPEN_SOURCE=600 \
	        -D_DEFAULT_SOURCE \
		-g -I${UNIX_NET_INCL_DIR} \
		-pedantic \
		-Wall \
		-W \
		-Wmissing-prototypes \
		-Wno-sign-compare \
		-Wno-unused-parameter

# makefile隐含规则
CC = gcc
# makefile隐含规则
CFLAGS = ${IMPL_CFLAGS}

IMPL_THREAD_FLAGS = -pthread

IMPL_LDLIBS = ${UNIX_NET_LIB} -lm

# makefile隐含规则
LDLIBS = ${IMPL_LDLIBS}

RM = rm -f
