@echo off

pushd ..\
call Dependencies\bin\premake\premake5.exe vs2019
popd
PAUSE