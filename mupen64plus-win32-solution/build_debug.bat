@echo off

SET dev_86="C:\\Program Files\\Microsoft Visual Studio\\2017\\Community\\Common7\\IDE\\devenv.com"
SET dev_64="C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\Common7\\IDE\\devenv.com"

IF EXIST %dev_86% ( 
  %dev_86% "mupen64plus-script.sln" /clean debug
  %dev_86% "mupen64plus-script.sln" /rebuild debug
) ELSE IF EXIST %dev_64% (
  %dev_64% "mupen64plus-script.sln" /clean debug
  %dev_64% "mupen64plus-script.sln" /rebuild debug
) ELSE (
  ECHO "Visual Studio 2017 and/or Build Tools (VC141) installation not found!"
  EXIT /B 0 
)
