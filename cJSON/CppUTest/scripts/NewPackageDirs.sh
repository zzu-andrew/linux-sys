#!/bin/bash
#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
package=$1

for dir in src include tests ; do
    packageDir=${dir}/${package}
    if [ ! -d "$packageDir" ] ; then
       echo "creating $packageDir"
       mkdir $packageDir
    fi
done

