@ECHO off
rem assumes 7zip Extras is placed into a directory adjacent to this directory

rem works for now but creates empty .git and ir directories - need to create exclude list

rem change to working directory
CD /D %~dp0

rem force libc recompilation
IF EXIST acs\libc.lib DEL acs\libc.lib

CALL compile.bat

TITLE Xenotomb Build Process

IF NOT EXIST ..\7z\ (
	ECHO(
	ECHO 7zip must be in a directory adjacent
	ECHO to this script for building to work!
	
	EXIT /B
)

rem mostly stolen from wolfendoom boa build.bat
FOR /F %%I IN ('GIT --git-dir=".\.git" rev-parse --short HEAD') DO SET _git_commit_hash=%%I

SET _build_name=Xenotomb-%_git_commit_hash%.pk3
IF EXIST ..\%_build_name% DEL ..\%_build_name%

START "Xenotomb Build Process" /B /WAIT "..\7z\7za.exe" a -r -tzip -x@".7zignore" "..\%_build_name%" ".\*"

ECHO(
ECHO Xenotomb build %_git_commit_hash% completed.

PAUSE
