{
    "targets": [{
        "target_name": "m64pnpm",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        'dependencies': [ "<!(node -p \"require('node-addon-api').gyp\")" ],
        'libraries': [ "<(module_root_dir)/source/mupen64plus-binding-shell.lib" ],
        "sources": [ 
            "source/cpp/m64b_node.cpp",
            "source/cpp/m64b_interface.cpp",
            "source/cpp/m64b_memory.cpp"
        ],

        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "<(module_root_dir)/../mupen64plus-binding-shell/src/api",
            "<(module_root_dir)/../mupen64plus-core/src/api"
        ],
        
        'conditions': [        
            ['OS=="win"', {
                "defines": [ "WIN32", "NDEBUG", "_CONSOLE", "_CRT_SECURE_NO_DEPRECATE" ]
            }]
        ]
    }]
}