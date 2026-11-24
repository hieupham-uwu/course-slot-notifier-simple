@echo off
rem Double-click file nay de build va chay demo, cua so se dung lai cho doc ket qua.
cd /d "%~dp0"

mingw32-make demo
if errorlevel 1 (
    echo.
    echo Build failed. Xem loi ben tren.
    pause
    exit /b 1
)

demo.exe
echo.
pause
