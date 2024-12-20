@echo off
setlocal enabledelayedexpansion

echo ^---^> Compiling:

set /a file_count=0
set files=
for /r %%i in (*.cpp) do (
    set files=!files! %%i
    set /a file_count+=1
    echo ^- %%~nxi
)

set include_path=header

g++ -g -I %include_path% %files% -o Monitor -lgdi32

echo ^---^> Success, files: %file_count%
endlocal