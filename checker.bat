@echo off  
:loop  
    data.exe > in.txt
    a.exe < in.txt > 1.out
    a2.exe < in.txt > 2.out
    fc 1.out 2.out 
if not errorlevel 1 goto loop