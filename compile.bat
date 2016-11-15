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
		IF NOT EXIST maps\ MKDIR maps\
		
		ECHO map files found in %%G

		rem get immediate map directory			
		SET _wad_path=%%G
		SET _wad_full_path=%%~fG
		SET _wad_directory=!_wad_path:*src\=!
			
		rem get newest map in folder in case of multiple .wads
		FOR /F %%H IN ('DIR %%G\*.wad /O:D /B') DO (
			SET _newest_map=%%~nxH
		)
			
		SET _newest_map_full_path=!_wad_full_path!\!_newest_map!
			
		ECHO using map file !_newest_map_full_path!
			
		REM ECHO _wad_path = !_wad_path!
		REM ECHO _wad_full_path = !_wad_full_path!
		REM ECHO _wad_directory = !_wad_directory!
		REM ECHO _newest_map = !_newest_map!
		REM ECHO _newest_map_full_path = !_newest_map_full_path!
		
		rem check for scripts
		SET "_script_exist="
		
		IF EXIST %%G\*.acs	SET _script_exist=1
		IF EXIST %%G\*.c	SET _script_exist=1
		
		ECHO _script_exist = !_script_exist!
		
		IF "!_script_exist!"=="1" (	
			rem extract map .wad into \ir directory
			IF NOT EXIST ir\!_wad_directory! MKDIR ir\!_wad_directory!
			..\GDCC\gdcc-ar-wad.exe wad:"!_newest_map_full_path!" --output "ir\!_wad_directory!" --extract
			ECHO extracted map to "ir\!_wad_directory!"
			
			rem compile all acs scripts
			IF EXIST %%G\*.acs (
				ECHO compiling ACS scripts...
				..\GDCC\gdcc-acc.exe --warn-all --bc-target=ZDoom -c !_wad_path!\*.acs ir\!_wad_directory!\acs.obj
			)
			
			rem compile all c scripts
			IF EXIST %%G\*.c (
				IF NOT EXIST acs\ MKDIR acs\
			
				IF NOT EXIST acs\libc.lib (
					ECHO compiling LIBC...
					..\GDCC\gdcc-makelib.exe --bc-target=ZDoom --bc-zdacs-init-delay --alloc-min Sta "" 1000000000 libGDCC libc -o acs\libc.lib
				)
				
				ECHO compiling C scripts...
				..\GDCC\gdcc-cc.exe --warn-all --bc-target=ZDoom -c !_wad_path!\*.c ir\!_wad_directory!\c.obj
			)
			
			rem link scripts into BEHAVIOR file
			ECHO linking scripts...
			..\GDCC\gdcc-ld.exe --warn-all --bc-target=ZDoom --bc-zdacs-init-delay -llibc ir\!_wad_directory!\*.obj ir\!_wad_directory!\behavior.lib
			
			rem pack everything into wad file in \maps
			
rem 	MAP01		empty
rem 	TEXTMAP		extracted TEXTMAP from map .wad
rem 	SCRIPTS		map script source (not 100% necessary)
rem 	BEHAVIOR	compiled map script
rem 	ZNODES		extracted ZNODES from map .wad
rem 	ENDMAP		empty

			ECHO packing into maps\!_newest_map!
			..\GDCC\gdcc-ar-wad.exe file:MAP01="ir\!_wad_directory!\MAP01\MAP01" file:TEXTMAP="ir\!_wad_directory!\MAP01\TEXTMAP" file:BEHAVIOR="ir\!_wad_directory!\behavior.lib" file:ZNODES="ir\!_wad_directory!\MAP01\ZNODES" file:ENDMAP="ir\!_wad_directory!\MAP01\ENDMAP" --output "maps\!_newest_map!"
			
		) ELSE (
			rem no scripts
			ECHO no scripts exist in %%G
			
			MOVE "!_newest_map_full_path!" "maps\!_newest_map!"
		) 
	) ELSE (
		rem no maps
		ECHO no maps exist in %%G
	)
)
