/*
* clang-bcapi generates xml scheme for Beautiful Capi
* Copyright(C) 2019 Petr Petrovich Petrov
*
* This file is part of clang - bcapi.
*
* clang - bcapi is free software : you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* clang-bcapi is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with clang-bcapi.If not, see < http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>

#include <clang/AST/DeclCXX.h>

namespace structure
{
    struct Base
    {
        Base* parent = nullptr;
        const clang::NamedDecl* decl;
        std::string name;

        Base(const clang::NamedDecl* decl_, Base *parent_ = nullptr, std::string name_ = "") 
            : decl(decl_), parent(parent_), name(name_) {}
    };
}
