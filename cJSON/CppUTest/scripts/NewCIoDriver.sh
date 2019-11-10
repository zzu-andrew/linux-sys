#!/bin/bash
#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
TEMPLATE_DIR=${CPP_U_TEST}/scripts/templates
source ${CPP_U_TEST}/scripts/GenerateSrcFiles.sh ClassNameCIoDriver c NoMock $1 $2

