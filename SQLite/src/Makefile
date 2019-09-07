include ../Makefile.inc

LINUX_EXE = sqlite_api creat_db_database creat_db_delete creat_db_insert creat_db_update \
			sqlite3_save_db_blob primary_key_with_no_null

EXE =  ${LINUX_EXE}

all : ${EXE}
	graph-easy graph_easy.txt > graph_ascii.txt



clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
