#!/bin/bash
#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
set -e
ASTYLE_OPTIONS="--convert-tabs --indent=spaces=4 --indent-classes --indent-switches --indent-preprocessor --style=ansi"

find $1 -name "*.h" -o -name "*.c" -o -name "*.cpp" |
while read filename; do 
    tmpfile=${filename}.astyle.cpp
    astyle ${ASTYLE_OPTIONS} <"${filename}" > "${tmpfile}"
    mv "${tmpfile}" "${filename}"
done
