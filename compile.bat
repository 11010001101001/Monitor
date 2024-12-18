@echo off
cd E:\Developer\Development\C++\Monitor
setlocal enabledelayedexpansion

echo Compiling:
echo.

set /a file_count=0
set files=
for /r %%i in (*.cpp) do (
    set files=!files! %%i
    set /a file_count+=1
    echo %%~nxi
)

set include_path=E:\Developer\Development\C++\Monitor\header

g++ -I %include_path% %files% -o Monitor -lgdi32

echo.
echo Compiled files count: %file_count%
echo Success, enjoy
endlocal