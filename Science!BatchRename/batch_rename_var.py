from pathlib import Path
import shutil
import os

a = 'first'
b = 'second'
dir = 'data'
new_dir = 'ArcWand Batch Script output directory'
err_dir = 'ArcWand Batch Script error directory'

if a == '-' or b == '-':
    a = input('First word:  ')
    b = input('Second word: ')
    print()

if dir == '.':
    print('The script will look for the files in the current directory.')
    print('If the files are not in the current directory, enter the path of the directory with the files.')
    print('Leave blank to use current directory. Press enter to continue')
    d = input('Directory: ')
    if d == '':
        print('Using current directory.')
    else:
        dir = d
        print(f'Using \'{d}\'')
    print()

if new_dir == 'ArcWand Batch Script output directory':
    print(f'Renamed files will be copied to \'{new_dir}\'')
    print('If you want a different output directory, provide it below.')
    print('Leave blank to use current directory. Press enter to continue')
    d = input('Directory: ')
    if d != '':
        new_dir = d
    print(f'Using \'{os.path.join(dir, new_dir)}\'')
    if not os.path.exists(os.path.join(dir, new_dir)):
        os.mkdir(os.path.join(dir, new_dir))
    print()

if err_dir == 'ArcWand Batch Script error directory':
    print(f'Files not following the naming convention will be copied to \'{new_dir}\'')
    print('If you want a different error handling directory, provide it below.')
    print('Leave blank to use current directory. Press enter to continue')
    d = input('Directory: ')
    if d != '':
        err_dir = d
    print(f'Using \'{os.path.join(dir, err_dir)}\'')
    if not os.path.exists(os.path.join(dir, err_dir)):
        os.mkdir(os.path.join(dir, err_dir))
    print()

os.chdir(dir)
for f in os.listdir():
    if not os.path.isfile(f):
        continue

    basename = Path(f).stem
    ext = Path(f).suffix
    parts = basename.split('-')
    
    if len(parts) < 4 or (not a in parts) or (not b in parts):
        shutil.copyfile(f, os.path.join(err_dir, f))
        continue
    
    parts.insert(parts.index(b)-1, parts.pop(0))
    
    new = '-'.join(parts) + ext
    shutil.copyfile(f, os.path.join(new_dir, new))

print('Done!')
