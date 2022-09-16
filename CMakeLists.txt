cmake_minimum_required(VERSION 3.23)
project(pangu)

set(CMAKE_CXX_STANDARD 14)

include_directories(include/imgui)

add_executable(pangu main.cpp
               include/imgui/imgui_draw.cpp
               include/imgui/imgui.cpp
               include/imgui/imgui_demo.cpp
               include/imgui/imgui_draw.cpp
               include/imgui/imgui_tables.cpp
               include/imgui/imgui_widgets.cpp
               include/glfw3.h
               src/engine/pangu.h
               src/animation/animation.h
               src/animation/animation.cpp
               src/audio/audio_device.h
               src/editor/gizmo.h
               src/editor/prefab_system.h
               src/editor/settings.h
               src/editor/wordeditor.h
               src/editor/utils.h
               src/lua_script/lua_script_system.h
               src/gui/gui_system.h
               src/gui/gui_system.cpp
               src/engine/allocators.h
               src/engine/allocators.cpp
               src/engine/log.cpp
               src/engine/log.h
               src/engine/thread.h
               src/engine/string.cpp
               src/engine/string.h src/engine/command_line_parser.h src/engine/control_device.h src/engine/core.cpp src/engine/core.h src/engine/resource_manager.cpp src/engine/resource_manager.h src/engine/sync.h src/engine/geometry.cpp src/engine/geometry.h src/engine/hash.cpp src/engine/hash.h src/engine/input_system.cpp src/engine/input_system.h src/engine/plugin.cpp src/engine/plugin.h src/engine/prefab.cpp src/engine/prefab.h src/engine/reflection.cpp src/engine/reflection.h)
