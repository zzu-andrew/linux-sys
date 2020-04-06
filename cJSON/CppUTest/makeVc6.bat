
REM Excerpted from "Test-Driven Development for Embedded C",
REM published by The Pragmatic Bookshelf.
REM Copyrights apply to this code. It may not be used to create training material, 
REM courses, books, articles, and the like. Contact us if you are in doubt.
REM We make no guarantees that this code is fit for any purpose. 
REM Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.

rem ****
rem * Command line build - For CppUTest - Run from dsw directory
rem * 
rem * A single parameter is suported and it is the last parameter of msdev
rem * for example:
rem * 	/clean
rem * make sure to use the the slash

rem * this needs to be in your path 
rem ****PATH=C:\Program Files\Microsoft Visual Studio\VC98\Bin;%PATH%

msdev CppUTest.dsp /MAKE "CppUTest - Debug" %1
msdev tests\AllTests.dsp /MAKE "AllTests - Debug" %1
if "%1" EQU "/clean" goto end
if "%1" EQU "/CLEAN" goto end
tests\Debug\AllTests
:end
