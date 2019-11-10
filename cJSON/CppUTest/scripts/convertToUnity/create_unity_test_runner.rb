#!/bin/ruby
#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
require File.join(File.dirname(__FILE__),  'cpp_u_test_to_unity_utils.rb')
include CppUTestToUnityUtils
  
in_file = ARGV[0]
test_lines = File.open(in_file).collect
out_file = File.open(File.basename(in_file, ".c") + "_runner.c", 'w')

group_runner = generate_group_runner_plainUnity("unity", test_lines)
write_lines_to_file(out_file, group_runner)
out_file.close()

