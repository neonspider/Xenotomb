@echo off
cd ..\..\GDCC
if not exist ..\xenotomb\acs mkdir ..\xenotomb\acs
if not exist ..\xenotomb\ir mkdir ..\xenotomb\ir

if not exist ..\xenotomb\acs\libc.bin (
   echo Building libc . . . 
   gdcc-makelib.exe --bc-target=ZDoom --bc-zdacs-init-delay --alloc-min Sta "" 1000000000 libGDCC libc -o ..\xenotomb\acs\libc.bin
)

echo Building game lib . . . 
gdcc-cc.exe --warn-all --bc-target=ZDoom -c ..\xenotomb\src\*.c ..\xenotomb\ir\game.ir
echo Linking game lib . . . 
gdcc-ld.exe --bc-target=ZDoom --bc-zdacs-init-delay -llibc ..\xenotomb\ir\game.ir ..\xenotomb\acs\behavior.bin

echo Press any key to exit . . . 
pause >> nul
