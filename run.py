import subprocess
import os.path

print('Running GZDoom...')

subprocess.call(os.path.join('..', '..', '..', 'games', 'gzdoom', 'gzdoom.exe') + ' -nostartup -iwad doom2 -file \"projects\\Xenotomb\\xenotomb\" +logfile \"F:\\Doom Ports\\Projects\\Xenotomb\\xenotomb\\log.txt\" +map gui_test')

print('\nDone!')
