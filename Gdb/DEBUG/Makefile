# Makefile to build all programs in all subdirectories
#
# DIRS is a list of all subdirectories containing makefiles
#(The library directory is first so that the library gets built first)
#

DIRS = segmentation \



BUILD_DIRS = $(DIRS)




all :
	@ echo "要编译的文件夹" 
	@ echo ${BUILD_DIRS}
	@ echo 
	@ echo 
	@ echo 'make sure you have set "ulimit -c unlimited"'
	@ echo 
	@ echo 
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE});\
		if test $$? -ne 0; then break; fi; done


clean:
	@ for dir in ${BUILD_DIRS}; do (cd $${dir};${MAKE} clean); done




