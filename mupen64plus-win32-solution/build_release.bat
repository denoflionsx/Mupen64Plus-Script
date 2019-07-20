@echo off

SET dev_86="%ProgramFiles%\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.com"
SET dev_64="%ProgramFiles(x86)%\\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.com"

IF EXIST %dev_86% ( 
  %dev_86% "mupen64plus-script.sln" /clean release
  %dev_86% "mupen64plus-script.sln" /rebuild release
) ELSE IF EXIST %dev_64% (
  %dev_64% "mupen64plus-script.sln" /clean release
  %dev_64% "mupen64plus-script.sln" /rebuild release
) ELSE (
  ECHO "Visual Studio 2017 and/or Build Tools (VC141) installation not found!"
  EXIT /B 0 
)