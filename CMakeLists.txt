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

project(ClangBcapi)
cmake_minimum_required(VERSION 3.4)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}/bin)

find_package(LLVM REQUIRED CONFIG)
find_package(CLANG REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

message(STATUS "Found CLANG ${CLANG_PACKAGE_VERSION}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")

include_directories(
  ${LLVM_INCLUDE_DIRS}
  ${CLANG_INCLUDE_DIRS}
)
add_definitions(
  ${LLVM_DEFINITIONS}
  ${CLANG_DEFINITIONS}
)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

message(STATUS "libs ${LLVM_LIBS} ${CLANG_LIBS}")
link_directories(${LLVM_LIBS} ${CLANG_LIBS})

set(SOURCES 
	src/main.cpp
)

add_executable(clang-bcapi ${SOURCES})

llvm_map_components_to_libnames(llvm_libs support core irreader )

target_link_libraries(clang-bcapi
  clangAST
  clangBasic
  clangFrontend
  clangTooling
  clangToolingCore
  clangRewrite
  clangDriver
  ${llvm_libs} 
)