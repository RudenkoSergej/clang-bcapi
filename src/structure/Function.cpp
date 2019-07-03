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

#include "structure/Function.h"

using namespace clang;

namespace structure
{
    Function::Function(const FunctionDecl* decl_, Namespace *parent_)
        :Base(decl_, parent_, decl_->getNameAsString())
    {
        const FunctionDecl* func_decl = dyn_cast<FunctionDecl>(decl);
        return_type = func_decl->getReturnType().getAsString();
        for (const auto &param : func_decl->parameters())
        {
            Argument* argument = new Argument(param, this);
            arguments.push_back(argument);
        }
    };
}
