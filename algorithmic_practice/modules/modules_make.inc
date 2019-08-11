# Makefile.inc - common definitions used by all makefiles

#DIR
TLPI_DIR = ../..
TLPI_LIB_DIR = -L${TLPI_DIR}/lib -L${TLPI_DIR}/libs

TLPI_INCL_DIR += -I${TLPI_DIR}/include
TLPI_INCL_DIR += -I${TLPI_DIR}/lib
TLPI_INCL_DIR += -I./
TLPI_INCL_DIR += -I./include

TLPI_LIB = -lsys_man
DBLIB = -lsqlite3

LINUX_LIBRT = -lrt
LINUX_LIBDL = -ldl
LINUX_LIBACL = -lacl
LINUX_LIBCRYPT = -lcrypt
LINUX_LIBCAP = -lcap


IMPL_CFLAGS = -std=c99 -D_XOPEN_SOURCE=600 \
	        -D_DEFAULT_SOURCE \
		-g ${TLPI_INCL_DIR} \
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

IMPL_LDLIBS =  ${TLPI_LIB} ${DBLIB} -lm

# makefile隐含规则
LDLIBS = ${TLPI_LIB_DIR} ${IMPL_LDLIBS}

RM = rm -f
