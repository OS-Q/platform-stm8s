"""
Arduino

Arduino Wiring-based Framework allows writing cross-platform software to
control devices attached to a wide range of Arduino boards to create all
kinds of creative coding, interactive objects, spaces or physical experiences.

http://arduino.cc/en/Reference/HomePage
"""

from os.path import isdir, join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()
board_config = env.BoardConfig()

FRAMEWORK_DIR = platform.get_package_dir("framework-N10")
assert isdir(FRAMEWORK_DIR)

env.Append(
    CPPDEFINES=[
        "ARDUINO_ARCH_STM8",
        ("ARDUINO", 10802),
        ("double", "float"),
        "USE_STDINT",
        "__PROG_TYPES_COMPAT__"
    ],

    CPPPATH=[
        join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core")),
        join(FRAMEWORK_DIR, "STM8S_StdPeriph_Driver", "inc")
    ],

    LIBPATH=[
        join(FRAMEWORK_DIR, "STM8S_StdPeriph_Driver", "lib")
    ],

    LIBS=[board_config.get("build.mcu")[0:8].upper()],

    LIBSOURCE_DIRS=[
        join(FRAMEWORK_DIR, "libraries")
    ]
)

#
# Target: Build Core Library
#

libs = []

if "build.variant" in env.BoardConfig():
    env.Append(
        CPPPATH=[
            join(FRAMEWORK_DIR, "variants",
                 env.BoardConfig().get("build.variant"))
        ]
    )
    libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "FrameworkArduinoVariant"),
        join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"))
    ))

libs.append(env.BuildLibrary(
    join("$BUILD_DIR", "FrameworkArduino"),
    join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core"))
))

env.Prepend(LIBS=libs)
