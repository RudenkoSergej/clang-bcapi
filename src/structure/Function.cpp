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

using boost::shared_ptr;
using boost::weak_ptr;
using clang::FunctionDecl;
using clang::dyn_cast;

namespace structure
{
    Function::Function(const FunctionDecl *decl_, weak_ptr<Base> parent_)
        :Base(decl_, parent_, decl_->getNameAsString())
    {
        const FunctionDecl *func_decl = dyn_cast<FunctionDecl>(decl_);
        this->return_type = func_decl->getReturnType().getAsString();
        this->noexcept_keyword = 
            func_decl->getExceptionSpecType() == clang::ExceptionSpecificationType::EST_BasicNoexcept;
    };
}
