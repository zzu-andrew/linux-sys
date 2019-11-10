#!/usr/bin/ruby
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
create_group_runner_file(in_file)
unity_runner_filename = convert_test_filename_to_unity_testrunner_filename(in_file)
puts "Creating test runner for :" + in_file + "\n"
puts "              Generating :" + unity_filename + "\n"

test_lines = File.open(in_file).readlines
out_unity_runner_file = File.open(unity_runner_filename, 'w')

test_group = get_test_group(test_lines)
group_runner = generate_group_runner(test_group, test_lines)
write_lines_to_file(out_unity_runner_file, group_runner)
out_unity_runner_file.close()
