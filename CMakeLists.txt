# This file is part of MSGPU project. 
# Copyright (C) 2021 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.9)

project (pico_audio NONE) 

find_package (Python3 COMPONENTS Interpreter) 

include(FetchContent)

FetchContent_Declare(
  mspkg
  GIT_REPOSITORY https://github.com/matgla/mspkg.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(mspkg)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${mspkg_SOURCE_DIR}/cmake)
include (mspkg)

setup_mspkg(${mspkg_SOURCE_DIR})

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pico-extras REQUIRED)
find_package(pico-sdk REQUIRED)

set (PICO_SDK_PATH ${pico-sdk_SOURCE_DIR})
include (cmake/preload/toolchains/pico_arm_gcc)
include (pico_sdk_init)
enable_language(ASM C CXX) 


set (PICO_EXTRAS_PATH ${pico-extras_SOURCE_DIR})
include (external/pico_extras_import)

pico_sdk_init()

add_library(common_flags INTERFACE)
add_library(common_flags_pico INTERFACE)

target_compile_options(common_flags_pico
    INTERFACE 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wfloat-equal -Wshadow -Wundef -Wpointer-arith -Wcast-align -Wconversion -Wall -fno-exceptions>
    $<$<CONFIG:DEBUG>:-Og -g> 
    $<$<CONFIG:RELEASE>:-Os>
)

target_compile_options(common_flags
    INTERFACE 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wfloat-equal -Wshadow -Wundef -Wpointer-arith -Wcast-align -Wconversion -Wall
    -Wpedantic -Wextra -Werror -fno-exceptions>
    $<$<CONFIG:DEBUG>:-Og -g> 
    $<$<CONFIG:RELEASE>:-Os>
)


add_subdirectory(src)
