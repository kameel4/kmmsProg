@echo off
chcp 1251 > log
del log

set NAME=04_ctrlx_ctrlv

:: -fexec-charset-utf-8 в Windows не работает
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %NAME%.exe del %NAME%.exe

g++ "%CHARSET%" %NAME%.cpp -o %NAME%

%NAME%
