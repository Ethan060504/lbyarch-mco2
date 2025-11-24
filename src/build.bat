nasm -f win64 asm_file.asm -o asm_file.obj
gcc -c c_file.c -o c_file.obj -m64
gcc c_file.obj asm_file.obj -o c_file.exe -m64
c_file.exe
pause