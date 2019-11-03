
{
    "targets": [{
        "target_name": "eopsparser",
        "cflags!": ["-fno-exceptions", "-fno-rtti"],
        "cflags_cc!": ["-fno-exceptions", "-fno-rtti"],
        "sources": [
            "<!@(node -p \"require('recursive-readdir-sync')('lib').filter(x => x.includes('.cpp')).join(' ')\")",
            "<!@(node -p \"require('recursive-readdir-sync')('src').filter(x => x.includes('.cpp')).join(' ')\")"
        ],
        'include_dirs': [
            "<!@(node -p \"require('glob').sync('lib/**/include')\")",
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [
        ],
        'conditions': [
            ['OS=="mac"', {
                'xcode_settings': {
                    'OTHER_CFLAGS': [
                        "-std=c++17",
                        "-stdlib=libc++"
                    ],
            }}]],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS']
    }]
}