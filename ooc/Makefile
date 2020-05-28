# Makefile to build all programs in all subdirectories
#
# DIRS is a list of all subdirectories containing makefiles
# (The library directory is first so that the library gets built first)
#

DIRS = 	src test

# The "namespaces" and "seccomp" directories are deliberately excluded from
# the above list because much of the code in those directories requires a
# relatively recent kernel and userspace to build. Nevertheless, each of
# those directories contains a Makefile.

BUILD_DIRS = ${DIRS}


# Dummy targets for building and clobbering everything in all subdirectories

all: 	
	@ echo ${BUILD_DIRS}
	@ for dir in ${BUILD_DIRS};\
	 	do (cd $${dir}; \
		 	${MAKE}) ; \
		if test $$? -ne 0; \
			then break; \
		fi; \
	   done

allgen: 
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE} allgen) ; done

clean: 
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
