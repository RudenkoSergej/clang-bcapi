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
#include "structure/Tree.h"

class Dumper 
{
private:
    std::string filename;
    const std::vector<std::string> &namespaces;
    boost::property_tree::ptree tree;
    boost::property_tree::ptree *cur_node;
    std::string project_name = "Example";

    void dumpNamespace(structure::Namespace* namepace_);
    void dumpFunction(structure::Function* function);

public:
    Dumper(const std::vector<std::string> &namespaces_, std::string filename_);
    void dump(const structure::Tree &tree);
};