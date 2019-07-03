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
#include <map>

#include <boost/shared_ptr.hpp>

#include "Base.h"


namespace structure
{
    struct Function;

    struct Namespace : public Base
    {
        std::map<std::string, boost::shared_ptr<Namespace>> nested_namespaces;
        //std::map<std::string, Class*> classes;
        std::vector<boost::shared_ptr<Function>> funtions;
        //std::vector<Enumeration*> enums;
        //std::vector<Template*> templates;

        Namespace(const clang::NamespaceDecl *decl_, boost::weak_ptr<Namespace> parent_);
    };
}
