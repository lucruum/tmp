@echo off

set command= ^
    cls ^& ^
    g++ algorithms.cpp ^&^& ^
    a.exe

python -m on_touch algorithms.cpp "%command%"
