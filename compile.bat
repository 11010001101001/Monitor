@echo off
setlocal enabledelayedexpansion

REM Start date & time
for /F "tokens=2 delims==" %%I in ('wmic OS Get localdatetime /value') do set "start_date=%%I"
set "start_date=%start_date:~0,4%-%start_date:~4,2%-%start_date:~6,2% %start_date:~8,2%:%start_date:~10,2%:%start_date:~12,6%"

REM Compiling
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

REM End date & time
for /F "tokens=2 delims==" %%I in ('wmic OS Get localdatetime /value') do set "end_date=%%I"
set "end_date=%end_date:~0,4%-%end_date:~4,2%-%end_date:~6,2% %end_date:~8,2%:%end_date:~10,2%:%end_date:~12,6%"

REM Duration
powershell -command "&{$start_date1 = [datetime]::parse('%start_date%'); $end_date1 = [datetime]::parse('%end_date%'); Write-Host (-join('Duration in seconds: ', ($end_date1 - $start_date1).TotalSeconds)); }"

endlocal