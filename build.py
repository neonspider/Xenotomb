from pathlib import Path
import sys
import subprocess

path_7z = Path('..', '7z', '7za.exe')

if not path_7z.is_file():
	print('\n7-zip must be in a directory adjacent to this script for building to work!')
	sys.exit()

git_commit_hash = subprocess.getoutput('GIT --git-dir=\"' + os.path.join('.', '.git') + '\"rev-parse --short HEAD')

xeno_version = ""
version_path = Path('VERSION.txt')
if version_path.is_file():
	with version_path.open() as f:
		xeno_version = f.read_text()

build_name_rel = str.join('Xenotomb-', xeno_version, '-', git_commit_hash, '.pk3')
build_name_deb = str.join('Xenotomb-debug-', xeno_version, '-', git_commit_hash, '.pk3')

try:
    os.remove(os.path.join('..', build_name_rel))
except OSError:
    pass
	
try:
    os.remove(os.path.join('..', build_name_deb))
except OSError:
    pass

# force libc recompilation
try:
    os.remove(os.path.join('acs', 'libc.c'))
except OSError:
    pass

# ********** RELEASE BUILD **********
print('\nRelease build started.')
# use < nul to suppress "press any key to continue" messages
CALL compile.bat < nul

START "Xenotomb Build Process" /B /WAIT "..\7z\7za.exe" a -r -tzip -x@".7zignore" "..\%_build_name_rel%" ".\*"

# *********** DEBUG BUILD ***********
print('\nDebug build started.'
# use < nul to suppress "press any key to continue" messages
CALL compile.bat /D < nul

START "Xenotomb Build Process" /B /WAIT "..\7z\7za.exe" a -r -tzip -x@".7zignore" "..\%_build_name_deb%" ".\*"

ECHO(
ECHO Xenotomb build %_xeno_version%-%_git_commit_hash% completed.

PAUSE
