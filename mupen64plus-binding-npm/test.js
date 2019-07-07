//###################################
//## Handle emulator setup
//###################################

// Move to emulator directory
process.chdir('./bin');

// Script begin
const m64p = require('./bin/node/m64pnpm.node');

// Initialization
m64p.setCoreLib("mupen64plus.dll");
m64p.setConfigDir("./");
m64p.setDataDir("./");

m64p.setPluginDir("./");
m64p.setPluginAudio("mupen64plus-audio-sdl.dll");
m64p.setPluginGFX("mupen64plus-video-rice.dll");
m64p.setPluginInput("mupen64plus-input-sdl.dll");
m64p.setPluginRSP("mupen64plus-rsp-hle.dll");

// Activate emulator with rom
m64p.runEmulator("mupen64plus.v64");

module.exports = m64p;