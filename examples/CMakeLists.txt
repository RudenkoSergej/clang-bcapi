#
# clang-bcapi generates xml scheme for Beautiful Capi
# Copyright (C) 2019 Petr Petrovich Petrov
#
# This file is part of clang-bcapi.
#
# clang-bcapi is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# clang-bcapi is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with clang-bcapi.  If not, see <http://www.gnu.org/licenses/>.
#

project(example)
cmake_minimum_required(VERSION 3.4)

set(result_xml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/example.xml)
set(input_sources ${CMAKE_CURRENT_LIST_DIR}/example.cpp)

add_custom_target(example DEPENDS ${result_xml})

add_custom_command(TARGET example    
    #OUTPUT
    #    ${result_xml}
    COMMAND
        ClangBcapi
        "TestNS" 
        ${result_xml}
        ${input_sources}
    MAIN_DEPENDENCY
        ${input_sources}
    DEPENDS 
        ClangBcapi
    WORKING_DIRECTORY
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
