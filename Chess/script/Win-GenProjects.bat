@echo off
pushd ..\
call script\bin\premake5.exe vs2022
popd
PAUSE