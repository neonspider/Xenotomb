@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

rem ************* TODO - LIBRARY COMPILATION ******************
rem
rem go through \src\lib and compile each library into \ir\lib
rem place each compiled library in \acs
rem
rem ***********************************************************

rem ************** MAP SCRIPT COMPILATION *********************
rem
rem go through each directory in \src\maps\
rem for each one with a .wad:
rem if .acs files exist use gdcc-acc
rem else if .c files exist use gdcc-cc
rem else return
rem extract map .wad into \ir\maps\[MAPNAME]
rem compile map script and place BEHAVIOR into \ir\maps\[MAPNAME],
rem overwriting previous BEHAVIOR
rem build .wad in \maps\ using gdcc-ar-wad with following lumps:
rem 	MAP01		empty
rem 	TEXTMAP		extracted TEXTMAP from map .wad
rem 	SCRIPTS		map script source (not 100% necessary)
rem 	BEHAVIOR	compiled map script
rem 	ZNODES		extracted ZNODES from map .wad
rem 	ENDMAP		empty
rem
rem ***********************************************************

rem ************** NOTES ************
rem
rem compiles all C and ACS scripts in map directory
rem assumes GDCC is placed a directory adjacent to xenotomb directory
rem only runs on Win2000/NT or later due to enabledelayedexpansion
rem uses only newest .wad  in each directory
rem
rem **********************************

rem go through each directory in src\maps
FOR /D %%G IN (src\maps\*) DO (
	rem check for .wad files
	IF EXIST %%G\*.wad (
		rem check for scripts
		SET "_script_exist="
		IF EXIST %%G\.acs SET _script_exist=1
		IF EXIST %%G\.c SET _script_exist=1
		
		IF "!_script_exist!"=="1" (
			ECHO map files found in %%G

			rem get immediate map directory			
			SET _wad_path=%%G
			SET _wad_directory=!_wad_path:*src\=!
			
			rem get newest map in folder in case of multiple .wads
			FOR /F %%H IN ('DIR %%G\*.wad /O:D /B') DO SET _newest_map=%%H
			
			rem extract map .wad into \ir directory
			..\GDCC\gdcc-ar-wad.exe wad:"!_newest_map!" --output "ir\!_wad_directory!" --extract
			ECHO extracted map to "ir\maps\!_wad_directory!"
			
			rem compile all acs scripts
			
			rem compile all c scripts
			
			rem link scripts into BEHAVIOR file
			
			rem pack everything into wad file in \maps
			
		) ELSE (
			rem no scripts
			ECHO no scripts exist in %%G
		) 
	) ELSE (
		rem no maps
		ECHO no maps exist in %%G
	)
)
