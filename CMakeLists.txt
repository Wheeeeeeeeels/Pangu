cmake_minimum_required(VERSION 3.23)
project(pangu)

set(CMAKE_CXX_STANDARD 14)

add_executable(pangu main.cpp src/engine/pangu.h src/animation/animation.h src/animation/animation.cpp src/audio/audio_device.h src/editor/gizmo.h src/editor/prefab_system.h src/editor/settings.h src/editor/wordeditor.h src/editor/utils.h src/lua_script/lua_script_system.h src/gui/gui_system.h src/gui/gui_system.cpp)
