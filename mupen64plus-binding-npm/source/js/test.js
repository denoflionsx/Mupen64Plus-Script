//###################################
//## Handle emulator setup
//###################################

// Move to emulator directory
process.chdir('./bin');

// Script begin
const m64p = require('../../bin/node/m64pnpm.node');

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
m64p.runEmulatorAsync("mupen64plus.v64");

//###################################
//## Handle input loop for testing
//###################################

var readline = require('readline'),
rl = readline.createInterface(process.stdin, process.stdout);

rl.setPrompt('Enter a command> ');
rl.prompt();

rl.on('line', function(line) {
    var lines = line.trim().split(' ');
    switch(lines[0]) {
        case '/help':
            console.log('Available Commands:');
            console.log('/memRead64 [address]');
            console.log('/memReadU64 [address]');
            console.log('/memWrite64 [address] [value]');
            console.log('/memWriteU64 [address] [value]');
            console.log('/memRead32 [address]');
            console.log('/memReadU32 [address]');
            console.log('/memWrite32 [address] [value]');
            console.log('/memWriteU32 [address] [value]');
            console.log('/memRead16 [address]');
            console.log('/memWrite16 [address] [value]');
            console.log('/memRead8 [address]');
            console.log('/memWrite8 [address] [value]');
            break;
        case '/memRead64':
            console.log(m64p.memRead64(parseInt(lines[1])));
            break;
        case '/memReadU64':
            console.log(m64p.memReadU64(parseInt(lines[1])));
            break;
        case '/memWrite64':
            console.log(m64p.memWrite64(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/memWriteU64':
            console.log(m64p.memWriteU64(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/memRead32':
            console.log(m64p.memRead32(parseInt(lines[1])));
            break;
        case '/memReadU32':
            console.log(m64p.memReadU32(parseInt(lines[1])));
            break;
        case '/memWrite32':
            console.log(m64p.memWrite32(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/memWriteU32':
            console.log(m64p.memWriteU32(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/memRead16':
            console.log(m64p.memRead16(parseInt(lines[1])));
            break;
        case '/memWrite16':
            console.log(m64p.memWrite16(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/memRead8':
            console.log(m64p.memRead8(parseInt(lines[1])));
            break;
        case '/memWrite8':
            console.log(m64p.memWrite8(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/exit':
            console.log('Ending Emulation...');
            process.exit(0);
            break;
        default:
            console.log('Invalid input [' + line.trim() + '].');
            console.log('Type /help for a list of commands.');
            break;
    }
    rl.prompt();
}).on('exit', function() {
    process.exit(0);
});

module.exports = m64p;