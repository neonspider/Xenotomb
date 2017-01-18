@ECHO off

TITLE Xenotomb Compilation Process

SETLOCAL ENABLEDELAYEDEXPANSION

SET "_xenotomb_debug=--define NDEBUG"
IF /I "%1"=="/D" SET "_xenotomb_debug=--define XENO_DEBUG"

rem change to working directory
CD /D %~dp0

rem check gdcc
IF NOT EXIST ..\GDCC\ (
	ECHO GDCC must be in a directory adjacent
	ECHO to this script for compilation to work!
	
	EXIT /B
)

rem delete all binaries and maps
ECHO(
ECHO Clearing intermediary compilation files...
IF EXIST ir\         RD /Q /S ir\
IF EXIST maps\       RD /Q /S maps\
IF EXIST LOADACS.txt DEL /Q LOADACS.txt

rem delete all libraries except for libc
FOR %%I IN (acs\*) DO IF NOT %%I == acs\libc.lib DEL /Q %%I

rem LIB COMPILATION
rem go through each directory in src\lib
ECHO(
ECHO Compiling libraries...

FOR /D %%G IN (src\lib\*) DO (
	rem check for scripts
	
	ECHO(
	
	SET "_lib_script_exist="
	
	IF EXIST %%G\*.acs	SET _lib_script_exist=1
	IF EXIST %%G\*.c	SET _lib_script_exist=1
	
	IF "!_lib_script_exist!"=="1" (
		ECHO Scripts found in %%G.
	
		rem get immediate map directory			
		SET _lib_path=%%G
		SET _lib_full_path=%%~fG
		SET _lib_directory=!_lib_path:*src\=!
		SET _lib_name=!_lib_path:*lib\=!
		
		IF NOT EXIST ir\!_lib_directory! MKDIR ir\!_lib_directory!
		IF NOT EXIST acs\ MKDIR acs\
		
		rem check AUTOLOAD.txt for libraries to load
		SET "_link_param="
		IF EXIST !_lib_path!\AUTOLOAD.txt (
			FOR /F %%I IN (!_lib_path!\AUTOLOAD.txt) DO (
				ECHO Autoloading library %%I.
				SET _link_param=!_link_param! -l%%I
			)
		)
		
		SET "_link_libc="
		
		rem compile all acs scripts
		IF EXIST %%G\*.acs (
			ECHO Compiling ACS scripts...
			..\GDCC\gdcc-acc.exe --warn-all --bc-target=ZDoom !_link_param! -c !_lib_path!\*.acs ir\!_lib_directory!\acs.obj
			
			IF NOT EXIST ir\!_lib_directory!\acs.obj GOTO :BUILD_FAIL
		)
		
		SET "_link_libc="
		
		rem compile all c scripts
		IF EXIST %%G\*.c (
			CALL :BUILD_LIBC
			
			SET _link_libc="-llibc"
			
			ECHO Compiling C scripts...
			
			..\GDCC\gdcc-cc.exe --warn-all --bc-target=ZDoom !_link_libc! !_link_param! -c !_lib_path!\*.c ir\!_lib_directory!\c.obj
			
			IF NOT EXIST ir\!_lib_directory!\c.obj GOTO :BUILD_FAIL
		)
		
		rem link scripts into BEHAVIOR file
		ECHO Linking scripts...
		..\GDCC\gdcc-ld.exe --warn-all --bc-target=ZDoom --bc-zdacs-init-delay !_link_libc! !_link_param! ir\!_lib_directory!\*.obj acs\!_lib_name!.lib
		
		IF NOT EXIST acs\!_lib_name!.lib GOTO :BUILD_FAIL
		
		IF EXIST !_lib_path!\.LOADACS (
			ECHO !_lib_name!> LOADACS.txt
		)
		
		ECHO Library '!_lib_name!' compiled.
	) ELSE (
		ECHO No scripts found in %%G.
	)
)

rem MAP COMPILATION
ECHO(
ECHO Compiling maps...
rem go through each directory in src\maps
FOR /D %%G IN (src\maps\*) DO (
	ECHO(

	rem check for .wad files
	IF EXIST %%G\*.wad (
		IF NOT EXIST maps\ MKDIR maps\

		rem get immediate map directory			
		SET _wad_path=%%G
		SET _wad_full_path=%%~fG
		SET _wad_directory=!_wad_path:*src\=!
		
		rem get newest map in folder in case of multiple .wads
		SET _wad_amount=0
		FOR /F %%H IN ('DIR %%G\*.wad /O:D /B') DO (
			SET _newest_map=%%~nxH
			SET /A "_wad_amount+=1"
		)
		
		SET _newest_map_full_path=!_wad_full_path!\!_newest_map!
		SET _newest_map_log_path=!_wad_path!\!_newest_map!
		
		IF !_wad_amount! GTR 1 (
			ECHO Multple maps found in %%G.
		) ELSE (
			ECHO Map file found in %%G.
		)
		
		ECHO Using map file !_newest_map_log_path!
		
		rem check for scripts
		SET "_script_exist="
		
		IF EXIST %%G\*.acs	SET _script_exist=1
		IF EXIST %%G\*.c	SET _script_exist=1
		
		IF "!_script_exist!"=="1" (
			ECHO Found scripts in %%G.
			
			rem extract map .wad into \ir directory
			ECHO Extracting map to ir\!_wad_directory!...
			IF NOT EXIST ir\!_wad_directory! MKDIR ir\!_wad_directory!
			..\GDCC\gdcc-ar-wad.exe wad:"!_newest_map_full_path!" --output "ir\!_wad_directory!" --extract
			
			IF NOT EXIST ir\!_wad_directory!\MAP01 GOTO :BUILD_FAIL
			
			SET "_link_param="
			IF EXIST !_wad_path!\AUTOLOAD.txt (
				FOR /F %%I IN (!_wad_path!\AUTOLOAD.txt) DO (
					ECHO Autoloading library %%I.
					SET _link_param=!_link_param! -l%%I
				)
			)
			
			SET "_link_libc="
			
			rem compile all acs scripts
			IF EXIST %%G\*.acs (
				ECHO Compiling ACS scripts...
				..\GDCC\gdcc-acc.exe --warn-all --bc-target=ZDoom !_link_param! -c !_wad_path!\*.acs ir\!_wad_directory!\acs.obj
				
				IF NOT EXIST ir\!_wad_directory!\acs.obj GOTO :BUILD_FAIL
			)
			
			rem compile all c scripts
			IF EXIST %%G\*.c (
				IF NOT EXIST acs\ MKDIR acs\
			
				CALL :BUILD_LIBC
				
				SET "_link_libc=-llibc"
				
				ECHO Compiling C scripts...
				..\GDCC\gdcc-cc.exe %_xenotomb_debug% --warn-all --bc-target=ZDoom !_link_libc! !_link_param! -c !_wad_path!\*.c ir\!_wad_directory!\c.obj
				
				IF NOT EXIST ir\!_wad_directory!\c.obj GOTO :BUILD_FAIL
			)
			
			rem link scripts into BEHAVIOR file
			ECHO Linking scripts...
			..\GDCC\gdcc-ld.exe --warn-all --bc-target=ZDoom --bc-zdacs-init-delay !_link_libc! !_link_param! ir\!_wad_directory!\*.obj ir\!_wad_directory!\behavior.lib
			
			IF NOT EXIST ir\!_wad_directory!\behavior.lib GOTO :BUILD_FAIL
			
			rem pack everything into wad file in \maps
			
rem 	MAP01		empty
rem 	TEXTMAP		extracted TEXTMAP from map .wad
rem 	SCRIPTS		map script source (not 100% necessary)
rem 	BEHAVIOR	compiled map script
rem 	ZNODES		extracted ZNODES from map .wad
rem 	ENDMAP		empty

			ECHO Packing files into maps\!_newest_map!...
			..\GDCC\gdcc-ar-wad.exe file:MAP01="ir\!_wad_directory!\MAP01\MAP01" file:TEXTMAP="ir\!_wad_directory!\MAP01\TEXTMAP" file:BEHAVIOR="ir\!_wad_directory!\behavior.lib" file:ZNODES="ir\!_wad_directory!\MAP01\ZNODES" file:ENDMAP="ir\!_wad_directory!\MAP01\ENDMAP" --output "maps\!_newest_map!"
			
			IF NOT EXIST maps\!_newest_map! GOTO :BUILD_FAIL
			
		) ELSE (
			rem no scripts
			ECHO No scripts found in %%G.
			
			ECHO Moving map file...
			
			MOVE "!_newest_map_full_path!" "maps\!_newest_map!"
		)
	SET _echo_map_dir=%%G
	SET _echo_map_name=!_echo_map_dir:*src\maps\=!
		
	ECHO Map '!_echo_map_name!' compiled.
	) ELSE (
		rem no maps
		ECHO No maps found in %%G.
	)
)

ECHO(
ECHO Compilation complete.

PAUSE

GOTO :EOF

:BUILD_LIBC
IF NOT EXIST acs\libc.lib (
	ECHO Compiling libc...
	..\GDCC\gdcc-makelib.exe --bc-target=ZDoom --bc-zdacs-init-delay --alloc-min Sta "" 1000000000 libGDCC libc -o acs\libc.lib
) ELSE (
	ECHO libc already exists.
)

EXIT /B

:BUILD_FAIL
ECHO(
ECHO Compilation failed, aborting.

PAUSE

EXIT /B
