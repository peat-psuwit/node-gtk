{
    "targets": [
        {
<<<<<<< HEAD
            "target_name": "node-gtk",
=======
            "target_name": "gi",
>>>>>>> gnode/master
            "sources": [
                "src/loop.cc",
                "src/gi.cc",
                "src/value.cc",
                "src/function.cc",
                "src/gobject.cc",
                "src/closure.cc",
            ],
            "cflags": [
                "<!@(pkg-config --cflags gobject-introspection-1.0) -Wall -Werror",
            ],
            "ldflags": [
                "<!@(pkg-config --libs gobject-introspection-1.0)",
            ],
<<<<<<< HEAD
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                    "destination": "<(module_path)"
                }
            ]
=======
>>>>>>> gnode/master
        }
    ]
}
