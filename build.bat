@ECHO off

rem change to working directory
CD /D %~dp0

TITLE Xenotomb Build Process

IF NOT EXIST ..\7z\ (
	ECHO(
	ECHO 7zip must be in a directory adjacent
	ECHO to this script for building to work!
	
	EXIT /B
)

rem mostly stolen from wolfendoom boa build.bat
FOR /F %%I IN ('GIT --git-dir=".\.git" rev-parse --short HEAD') DO SET _git_commit_hash=%%I


FOR /F %%I IN ('GIT --git-dir=".\.git" rev-list --count HEAD') DO SET _git_commit_num=%%I

SET "_xeno_version="
		IF EXIST VERSION.txt (
			FOR /F %%I IN (VERSION.txt) DO (
				SET _xeno_version=%%I
			)
		)

SET _build_name_rel=Xenotomb-%_xeno_version%-%_git_commit_num%-%_git_commit_hash%.pk3
SET _build_name_deb=Xenotomb-debug-%_xeno_version%-%_git_commit_num%-%_git_commit_hash%.pk3
IF EXIST ..\%_build_name_rel% DEL ..\%_build_name_rel%
IF EXIST ..\%_build_name_deb% DEL ..\%_build_name_deb%

rem force libc recompilation
IF EXIST acs\libc.lib DEL acs\libc.lib

rem ********** RELEASE BUILD **********
ECHO(
ECHO Release build started.
rem use < nul to suppress "press any key to continue" messages
CALL compile.bat < nul

START "Xenotomb Build Process" /B /WAIT "..\7z\7za.exe" a -r -tzip -x@".7zignore" "..\%_build_name_rel%" ".\*"

rem *********** DEBUG BUILD ***********
ECHO(
ECHO Debug build started.
rem use < nul to suppress "press any key to continue" messages
CALL compile.bat /D < nul

START "Xenotomb Build Process" /B /WAIT "..\7z\7za.exe" a -r -tzip -x@".7zignore" "..\%_build_name_deb%" ".\*"

ECHO(
ECHO Xenotomb build %_xeno_version%-%_git_commit_num%-%_git_commit_hash% completed.

PAUSE
