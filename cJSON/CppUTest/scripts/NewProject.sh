#!/bin/bash
#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---

PROJECT_NAME=$1
CODE_LEGAL_PROJECT_NAME=$(echo $PROJECT_NAME | sed 's/-/_/g')
TEMPLATE_DIR=${CPPUTEST_HOME}/scripts/templates
ORIGINAL_DIR=$(pwd)

if [ -e ${PROJECT_NAME} ] ; then
	echo "The directory ${PROJECT_NAME} already exists"
	exit 1;
fi

echo "Copy template project"
cp -R ${TEMPLATE_DIR}/ProjectTemplate ${PROJECT_NAME}
find ${PROJECT_NAME} -name \.svn | xargs rm -rf

cd ${PROJECT_NAME}

ls

changeProjectName() {
    echo Change Name $1/Project$2 to $3$2
    sed "-e s/Project/$3/g" $1/Project$2 | tr -d "\r" >$1/$3$2
    rm $1/Project$2 
}

changeProjectName . Makefile ${CODE_LEGAL_PROJECT_NAME}
changeProjectName . .project ${PROJECT_NAME}
changeProjectName src/util BuildTime.cpp  ${CODE_LEGAL_PROJECT_NAME}
changeProjectName include/util BuildTime.h ${CODE_LEGAL_PROJECT_NAME}
changeProjectName tests/util BuildTimeTest.cpp ${CODE_LEGAL_PROJECT_NAME}
mv ${CODE_LEGAL_PROJECT_NAME}Makefile Makefile
mv ${PROJECT_NAME}.project .project
mv Project.cproject .cproject

cd ${ORIGINAL_DIR}
echo "You might want to modify the path for CPPUTEST_HOME in the Makefile."
