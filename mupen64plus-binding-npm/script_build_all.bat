@echo off

cd ..\\mupen64plus-win32-solution
build_release.bat

cd ..\\mupen64plus-binding-npm
script_build_npm.bat