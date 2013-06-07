cls
@echo off & setlocal
title [Chuyen file vao dien thoai]
color 1f

start /wait o.f-core.vbs

set /p tenfile=<o.f-coret
echo Ten day du cua file: %tenfile%
set /p outfile="Xong roi thi ten file la gi?: "
cls

echo File se duoc tim thay o: %homedrive%\%outfile%
cls
title [Dang xu li...]

echo Dang xu li, cho mot lat...
cd /d %homedrive%\Program Files\FreeTime\FormatFactory
FormatFactory "All to Mobile Device" "MP4 320x240 MPEG4" "%tenfile%" %homedrive%\%outfile%.mp4

cls
title [Chep vao dien thoai]
echo Dang chep vao dien thoai...
copy %homedrive%\%outfile%.mp4 G:\Videos
del /f %homedrive%\%outfile%.mp4

cls