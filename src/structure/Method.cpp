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

#include "structure/Method.h"

using boost::weak_ptr;
using clang::CXXMethodDecl;
using clang::dyn_cast;

namespace structure
{
    Method::Method(const CXXMethodDecl *decl_, weak_ptr<Class> parent_)
        :Function(decl_, parent_)
    {
        const CXXMethodDecl *method_decl = dyn_cast<CXXMethodDecl>(decl_);
        //this->return_type = method_decl->getReturnType().getAsString();
        this->const_keyword = method_decl->isConst();
    };
}
