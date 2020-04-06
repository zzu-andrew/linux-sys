

ifdef O
ifeq ("$(origin O)", "command line")
    BUILD_DIR := $(O)
endif
endif




