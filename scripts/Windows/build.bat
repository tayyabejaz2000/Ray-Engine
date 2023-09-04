@echo off

set ARGS=%*
IF %1==build (
    vendor\premake\bin\Windows\premake5.exe vs2022 %ARGS:~6%
) ELSE (
    vendor\premake\bin\Windows\premake5.exe %ARGS%
)