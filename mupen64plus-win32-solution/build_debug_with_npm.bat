echo devenv.com "mupen64plus-script.sln" /clean debug
echo devenv.com "mupen64plus-script.sln" /rebuild debug

cd ..\\mupen64plus-binding-npm
call npm install
call npm run clean
call npm run build
call npm run winpak