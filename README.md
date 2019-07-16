# mupen64plus-script

## Requirements (m64p-script):
- Visual Studio 2017 + VC++(v141) Tools.
- Windows 10 SDK (Any Version Works, 10.0.17763.0 is set by default)

### Build instructions:
Navigate to the mupen64plus-win32-solution directory
and open the .sln file with Visual Studio 2017. If
you have a version of Windows 10 SDK but not the
version listed above, right click each project
in the solution and go to properties, then change
the windows sdk to target a version you have installed.
After, it is as simple as the 'Build' tab at the top
of the window and selecting 'Build Solution'.

## Requirements (m64p-script):
- Node 10.16.0
- Python 2.7

### Build instructions:
After compiling the m64p-script with visual studio,
open a command-prompt or power-shell and navigate to
the mupen64plus-binding-npm directory. Then type the
following commands in order:
- npm run build
- npm run winpak
- npm run test

If you have just pulled/downloaded the package from git
you will be missing some dependancies. These can aquired
by running 'npm install' before running the commands
above.

### DISCLAIMER:
I do not own the rights to any of the software provided.
The original sources can be found on the official mupen
development git: https://github.com/mupen64plus

Lua implementation borrowed from the works of:
https://github.com/RenaKunisaki