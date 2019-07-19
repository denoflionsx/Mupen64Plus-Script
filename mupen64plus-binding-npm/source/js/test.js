//###################################
//## Functions for later use
//###################################

function toHex(byteArray) {
    return Array.from(byteArray, function(byte) {
      return ('0' + (byte & 0xFF).toString(16)).slice(-2);
    }).join('')
} 

function cbFrame(frameIndex) { 
    console.log("Frames: ", frameIndex);
}

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
errCode = m64p.initialize();

// Activate emulator with rom
errCode = m64p.loadRom("mupen64plus.v64");
errCode = m64p.runEmulator(true);

// Activate callbacks
m64p.setFrameCallback(cbFrame);

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
            console.log('');
            console.log('Memory Commands (In shorthand):');
            console.log("/rdramRead(Command)");
            console.log("/rdramWrite(Command)");
            console.log("/romRead(Command)");
            console.log("/romWrite(Command)");
            console.log('');
            console.log('---Replace "(Command)" with one of the following types--');
            console.log('Buffer');
            console.log('64');
            console.log('U64');
            console.log('32');
            console.log('U32');
            console.log('16');
            console.log('8');
            console.log('');
            console.log('Read Commands take [address] param');
            console.log('Write Commands take [address] [value] params');
            console.log('-EG: /rdramRead8 0x40');
            console.log('     /rdramWrite8 0x40 0x3c');
            console.log('');
            console.log('NOTE: Buffer functionality is not complete for rdram');
            console.log('and not implemented for rom yet.');
            console.log('');
            console.log('----------------------------------');
            console.log('');
            console.log('Other Commands:');
            console.log('/refreshHack');
            console.log('[Debug/Experimental]');
            console.log('/readwrite [readAddress] [value] [writeAddress]');
            console.log(''); break;

        case '/rdramReadBuffer': console.log(toHexString(m64p.rdramReadBuffer(parseInt(lines[1]), parseInt(lines[2])))); break;
        case '/rdramRead64': console.log(m64p.rdramRead64(parseInt(lines[1])).toString(16)); break;
        case '/rdramReadU64': console.log(m64p.rdramReadU64(parseInt(lines[1])).toString(16)); break;
        case '/rdramRead32': console.log(m64p.rdramRead32(parseInt(lines[1])).toString(16)); break;
        case '/rdramReadU32': console.log(m64p.rdramReadU32(parseInt(lines[1])).toString(16)); break;
        case '/rdramRead16': console.log(m64p.rdramRead16(parseInt(lines[1])).toString(16)); break;
        case '/rdramRead8': console.log(m64p.rdramRead8(parseInt(lines[1])).toString(16)); break;
        
        case '/rdramWrite64': console.log(m64p.rdramWrite64(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/rdramWriteU64': console.log(m64p.rdramWriteU64(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/rdramWrite32': console.log(m64p.rdramWrite32(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/rdramWriteU32': console.log(m64p.rdramWriteU32(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/rdramWrite16': console.log(m64p.rdramWrite16(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/rdramWrite8': console.log(m64p.rdramWrite8(parseInt(lines[1]), parseInt(lines[2]))); break;
        
        case '/romRead64': console.log(m64p.romRead64(parseInt(lines[1])).toString(16)); break;
        case '/romReadU64': console.log(m64p.romReadU64(parseInt(lines[1])).toString(16)); break;
        case '/romRead32': console.log(m64p.romRead32(parseInt(lines[1])).toString(16)); break;
        case '/romReadU32': console.log(m64p.romReadU32(parseInt(lines[1])).toString(16)); break;
        case '/romRead16': console.log(m64p.romRead16(parseInt(lines[1])).toString(16)); break;
        case '/romRead8': console.log(m64p.romRead8(parseInt(lines[1])).toString(16)); break;
        
        case '/romWrite64': console.log(m64p.romWrite64(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/romWriteU64': console.log(m64p.romWriteU64(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/romWrite32': console.log(m64p.romWrite32(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/romWriteU32': console.log(m64p.romWriteU32(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/romWrite16': console.log(m64p.romWrite16(parseInt(lines[1]), parseInt(lines[2]))); break;
        case '/romWrite8': console.log(m64p.romWrite8(parseInt(lines[1]), parseInt(lines[2]))); break;
        
        case '/refreshHack':
            m64p.savestatesRefreshHack();
            break;

        case '/readwrite':
            let arr = m64p.rdramReadBuffer(parseInt(lines[1]), parseInt(lines[2]));
            m64p.rdramWriteBuffer(parseInt(lines[3]), arr);

        case '/exit':
            console.log('Ending Emulation...');
            m64p.stopEmulator();
            process.exit(0);
            break;
        default:
            console.log('Invalid input [' + line.trim() + '].');
            console.log('Type /help for a list of commands.');
            break;
    }
    rl.prompt();
}).on('exit', function() {
    m64p.stopEmulator();
    process.exit(0);
});

module.exports = m64p;