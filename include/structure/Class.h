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

#include "Namespace.h"


namespace structure
{
    struct Method;
    struct Constructor;

    struct Class : public Base
    {
        std::string base;
        std::string implementation_name;
        std::string implementation_header;
        bool is_abstract;
        std::vector<boost::shared_ptr<Constructor>> constructors;
        std::vector<boost::shared_ptr<Method>> methods;
        //std::vector<boost::shared_ptr<Enumeration>> enums;
        //std::vector<boost::shared_ptr<Field>> fields;

        Class(const clang::CXXRecordDecl *decl_, boost::weak_ptr<Namespace> parent_);
    };
}
