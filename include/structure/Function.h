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
#include <vector>

#include <boost/shared_ptr.hpp>

#include "Base.h"
#include "Argument.h"
#include "Namespace.h"


namespace structure
{
    struct Function : public Base
    {
        std::vector<boost::shared_ptr<Argument>> arguments;
        std::string return_type;

        Function(const clang::FunctionDecl *decl_, boost::weak_ptr<Namespace> parent_);

    };
}
