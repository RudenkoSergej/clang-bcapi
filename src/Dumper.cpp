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

#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>

#include "Dumper.h"

using namespace structure;
using namespace boost::property_tree;
using boost::shared_ptr;

Dumper::Dumper(const std::vector<std::string> &namespaces_, std::string filename_)
    :namespaces(namespaces_), filename(filename_), cur_node(&this->tree)
{

}

void Dumper::dumpNamespace(shared_ptr<Namespace> namepace_)
{
    if (namepace_)
    {
        ptree *saved_cur_node = cur_node;
        ptree &namespace_node = cur_node->add("namespace", "");
        namespace_node.put("<xmlattr>.name", namepace_->name);
        cur_node = &namespace_node;
        for (const auto &it : namepace_->nested_namespaces)
        {
            dumpNamespace(it.second);
        }
        for (const auto &func : namepace_->funtions)
        {
            dumpFunction(func);
        }

        cur_node = saved_cur_node;
    }
}

void Dumper::dumpFunction(shared_ptr<Function> function)
{
    ptree &function_node = cur_node->add("function", ""); 
    function_node.put("<xmlattr>.name", function->name);
    function_node.put("<xmlattr>.return", function->return_type);
    /* TODO add fields:
    "noexcept:bool"
    "return_copy_or_add_ref:bool"
    */
    for (auto arg : function->arguments)
    {
        ptree &argument_node = function_node.add("argument", "");
        argument_node.put("<xmlattr>.name", arg->name);
        argument_node.put("<xmlattr>.type", arg->type);
    }
}

void Dumper::dump(const Tree &tree)
{
    std::string lower_project_name = boost::algorithm::to_lower_copy(project_name);
    ptree &root_node = this->tree.add(lower_project_name + ":api", "");
    
    root_node.put("<xmlattr>.xmlns:" + lower_project_name, "http://gkmsoft.ru/beautifulcapi");
    root_node.add("<xmlattr>.project_name", project_name);
    
    cur_node = &root_node;
    for (const auto &ns : namespaces)
    {
        dumpNamespace(tree.GetNamespace(ns));
    }
    xml_parser::xml_writer_settings<std::string> settings(' ', 4);
    write_xml(filename, this->tree, std::locale(), settings );
}
