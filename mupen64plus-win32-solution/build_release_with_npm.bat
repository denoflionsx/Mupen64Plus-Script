echo devenv.com "mupen64plus-script.sln" /clean release
echo devenv.com "mupen64plus-script.sln" /rebuild release

cd ..\\mupen64plus-binding-npm
call npm install
call npm run clean
call npm run build
call npm run winpak