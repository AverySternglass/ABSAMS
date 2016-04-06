@ECHO off
:start
set choice=
set /p choice= Sure you want to delete debug files?(y/n)
if not '%choice%'=='y' goto end



del /S *.obj
del /S *.sbr
del /S *.bsc
del /S *.exe
del /S *.exp
del /S *.ilk
del /S *.lib
del /S *.pch
del /S *.pdb
del /S *.res
del /S *.idb
del /S *.lib
del /S *.bmp
del /S *.mhl
:end	