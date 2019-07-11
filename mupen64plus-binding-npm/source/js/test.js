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
            console.log('/rdramRead64 [address]');
            console.log('/rdramReadU64 [address]');
            console.log('/rdramWrite64 [address] [value]');
            console.log('/rdramWriteU64 [address] [value]');
            console.log('/rdramRead32 [address]');
            console.log('/rdramReadU32 [address]');
            console.log('/rdramWrite32 [address] [value]');
            console.log('/rdramWriteU32 [address] [value]');
            console.log('/rdramRead16 [address]');
            console.log('/rdramWrite16 [address] [value]');
            console.log('/rdramRead8 [address]');
            console.log('/rdramWrite8 [address] [value]');
            break;
        case '/rdramRead64':
            console.log(m64p.rdramRead64(parseInt(lines[1])));
            break;
        case '/rdramReadU64':
            console.log(m64p.rdramReadU64(parseInt(lines[1])));
            break;
        case '/rdramWrite64':
            console.log(m64p.rdramWrite64(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/rdramWriteU64':
            console.log(m64p.rdramWriteU64(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/rdramRead32':
            console.log(m64p.rdramRead32(parseInt(lines[1])));
            break;
        case '/rdramReadU32':
            console.log(m64p.rdramReadU32(parseInt(lines[1])));
            break;
        case '/rdramWrite32':
            console.log(m64p.rdramWrite32(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/rdramWriteU32':
            console.log(m64p.rdramWriteU32(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/rdramRead16':
            console.log(m64p.rdramRead16(parseInt(lines[1])));
            break;
        case '/rdramWrite16':
            console.log(m64p.rdramWrite16(parseInt(lines[1]), parseInt(lines[2])));
            break;
        case '/rdramRead8':
            console.log(m64p.rdramRead8(parseInt(lines[1])));
            break;
        case '/rdramWrite8':
            console.log(m64p.rdramWrite8(parseInt(lines[1]), parseInt(lines[2])));
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