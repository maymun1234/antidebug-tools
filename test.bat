@echo off
setlocal enabledelayedexpansion

:: Derleyici ve çıkış ismi
set COMPILER=g++
set OUTPUT=program.exe

:: Derleme için kullanılacak cpp dosyaları toplanıyor
set SOURCES=

for /r %%f in (*.cpp) do (
    echo %%f | findstr /i "\\hashid\\" >nul
    if errorlevel 1 (
        set SOURCES=!SOURCES! "%%f"
    )
)

echo [INFO] Derleme başlıyor...
%COMPILER% %SOURCES% -o %OUTPUT% -lBcrypt -mconsole

if %errorlevel%==0 (
    echo [SUCCESS] Derleme tamamlandı: %OUTPUT%
) else (
    echo [ERROR] Derleme hatası!
)

pause
