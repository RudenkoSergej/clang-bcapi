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
#include <boost/property_tree/ptree.hpp>

#include "structure/Function.h"
#include "structure/Namespace.h"
#include "structure/Method.h"
#include "structure/Constructor.h"
#include "structure/Class.h"
#include "structure/Tree.h"

class Dumper 
{
    std::string filename;
    const std::vector<std::string> &namespaces;
    boost::property_tree::ptree tree;
    boost::property_tree::ptree *cur_node;
    std::string project_name = "Example";

    void dumpNamespace(boost::shared_ptr<structure::Namespace> namepace_);
    void dumpFunction(boost::shared_ptr<structure::Function> function);
    void dumpClass(boost::shared_ptr<structure::Class> class_);
    void dumpMethod(boost::shared_ptr<structure::Method> method); 
    void dumpArgument(boost::shared_ptr<structure::Argument> argument);
    void dumpConstructor(boost::shared_ptr<structure::Constructor> ctor);
public:
    Dumper(const std::vector<std::string> &namespaces_, std::string filename_);
    void dump(const structure::Tree &tree);
};
