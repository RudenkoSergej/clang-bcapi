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
        ptree &namespace_node = cur_node->add("namespace", "");
        ptree *saved_cur_node = cur_node;
        cur_node = &namespace_node;

        namespace_node.put("<xmlattr>.name", namepace_->name);
        for (const auto &it : namepace_->nested_namespaces)
        {
            dumpNamespace(it.second);
        }
        for (const auto &func : namepace_->funtions)
        {
            dumpFunction(func);
        }

        for (const auto &it : namepace_->classes)
        {
            dumpClass(it.second);
        }

        cur_node = saved_cur_node;
    }
}

void Dumper::dumpFunction(shared_ptr<Function> function)
{
    if (function)
    {
        ptree &function_node = cur_node->add("function", "");
        ptree *saved_cur_node = cur_node;
        cur_node = &function_node;

        function_node.put("<xmlattr>.name", function->name);
        function_node.put("<xmlattr>.return", function->return_type);
        if (function->noexcept_keyword)
        {
            function_node.put("<xmlattr>.noexcept", function->noexcept_keyword);
        }
        /* TODO add fields:
        "return_copy_or_add_ref:bool"
        */
        for (auto arg : function->arguments)
        {
            dumpArgument(arg);
        }

        cur_node = saved_cur_node;
    }
}

void Dumper::dumpClass(shared_ptr<Class> class_)
{
    if (class_)
    {
        ptree &class_node = cur_node->add("class", "");
        ptree *saved_cur_node = cur_node;
        cur_node = &class_node;

        class_node.put("<xmlattr>.name", class_->name);
        class_node.put("<xmlattr>.implementation_class_name", class_->implementation_name);
        class_node.put("<xmlattr>.implementation_class_header", class_->implementation_header);

        if (!class_->base.empty())
        {
            class_node.put("<xmlattr>.base", class_->base);
        }
        if (class_->is_abstract)
        {
            class_node.put("<xmlattr>.abstract", class_->is_abstract);
        }
        /* TODO add fields:
        "lifecycle:enum"
        */
        for (const auto &ctor : class_->constructors)
        { 
            dumpConstructor(ctor);
        }
        for (const auto &method : class_->methods)
        {
            dumpMethod(method);
        }

        cur_node = saved_cur_node;
    }
}

void Dumper::dumpMethod(shared_ptr<Method> method)
{
    if (method)
    {
        ptree &method_node = cur_node->add("method", "");
        ptree *saved_cur_node = cur_node;
        cur_node = &method_node;

        method_node.put("<xmlattr>.name", method->name);
        method_node.put("<xmlattr>.return", method->return_type);
        if (method->noexcept_keyword)
        {
            method_node.put("<xmlattr>.noexcept", method->noexcept_keyword);
        }
        if (method->const_keyword)
        {
            method_node.put("<xmlattr>.noexcept", method->const_keyword);
        }
        /* TODO add fields:
        "return_copy_or_add_ref:bool"
        */
        for (auto arg : method->arguments)
        {
            dumpArgument(arg);
        }

        cur_node = saved_cur_node;
    }
}

void Dumper::dumpConstructor(shared_ptr<Constructor> ctor)
{
    if (ctor)
    {
        ptree &ctor_node = cur_node->add("constructor", "");
        ptree *saved_cur_node = cur_node;
        cur_node = &ctor_node;

        ctor_node.put("<xmlattr>.name", ctor->name);
        if (ctor->noexcept_keyword)
        {
            ctor_node.put("<xmlattr>.noexcept", ctor->noexcept_keyword);
        }
        /* TODO add fields:
        "noexcept:bool"
        "explicit::bool"
        */
        for (auto arg : ctor->arguments)
        {
            dumpArgument(arg);
        }

        cur_node = saved_cur_node;
    }
}

void Dumper::dumpArgument(shared_ptr<Argument> argument)
{
    if (argument)
    {
        ptree &argument_node = cur_node->add("argument", "");
        argument_node.put("<xmlattr>.name", argument->name);
        argument_node.put("<xmlattr>.type", argument->type);
        /* TODO add fields:

        */
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
