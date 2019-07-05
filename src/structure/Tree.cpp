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
#include <boost/algorithm/string.hpp>

#include "structure/Tree.h"

using namespace clang;
using namespace boost;

namespace structure
{
    shared_ptr<Class> Tree::GetOrGenClass(const CXXRecordDecl *decl)
    {
        shared_ptr<Class> class_ptr = GetClass(decl);
        if (class_ptr)
        {
            return class_ptr;
        }
        if (decl)
        {
            // TODO process cases with nested classes
            const NamespaceDecl *parent_decl = dyn_cast_or_null<NamespaceDecl>(decl->getParent());
            shared_ptr<Namespace> parent_namespace = GetOrGenNamespace(parent_decl);
            if (parent_namespace)
            {
                shared_ptr<Class> new_class(new Class(decl, parent_namespace));
                parent_namespace->classes[decl->getNameAsString()] = new_class;
                return new_class;
            }
        }
        return nullptr;
    }

    shared_ptr<Class> Tree::GetClass(const CXXRecordDecl *decl)
    {
        if (decl)
        {
            // TODO process cases with nested classes
            const NamespaceDecl *parent_decl = dyn_cast_or_null<NamespaceDecl>(decl->getParent());
            shared_ptr<Namespace> parent_namespace = GetOrGenNamespace(parent_decl);
            if (parent_namespace)
            {
                auto it = parent_namespace->classes.find(decl->getNameAsString());
                if (it != parent_namespace->classes.end())
                {
                    return it->second;
                }
            }
        }
        return nullptr;
    }

    shared_ptr<Namespace> Tree::GetOrGenNamespace(const NamespaceDecl *decl)
    {
        shared_ptr<Namespace> namespace_ptr = GetNamespace(decl);
        if (namespace_ptr)
        {
            return namespace_ptr;
        }
        if (decl)
        {
            const NamespaceDecl *parent_decl = dyn_cast_or_null<NamespaceDecl>(decl->getParent());
            shared_ptr<Namespace> parent_namespace = GetOrGenNamespace(parent_decl);
            std::string name = decl->getNameAsString();
            if (parent_namespace)
            {
                shared_ptr<Namespace> new_namespace(new Namespace(decl, parent_namespace));
                parent_namespace->nested_namespaces[name] = new_namespace;
                return new_namespace;
            }
            else
            {
                shared_ptr<Namespace> new_namespace(new Namespace(decl, parent_namespace));
                root_namespaces[name] = new_namespace;
                return new_namespace;
            }
        }
        return nullptr;
    }
        
    shared_ptr<Namespace> Tree::GetNamespace(const NamespaceDecl *decl) const
    {
        if (decl)
        {
            const NamespaceDecl *parent_decl = dyn_cast_or_null<NamespaceDecl>(decl->getParent());
            std::map<std::string, shared_ptr<Namespace>>::const_iterator it;
            if (parent_decl)
            {
                if (shared_ptr<Namespace> parent_namespace = GetNamespace(parent_decl))
                {
                    it = parent_namespace->nested_namespaces.find(decl->getNameAsString());
                    if (it != parent_namespace->nested_namespaces.end())
                    {
                        return it->second;
                    }
                }
            }
            else
            {
                it = root_namespaces.find(decl->getNameAsString());
                if (it != root_namespaces.end())
                {
                    return it->second;
                }
            }
        }
        return nullptr;
    }


    shared_ptr<Namespace> Tree::GetNamespace(const std::string &fullname) const
    {
        std::vector<std::string> namespaces;
        split(namespaces, fullname, is_any_of("\t "), token_compress_on);
        if (namespaces.size())
        {
            const std::map<std::string, shared_ptr<Namespace>>& root_ns = root_namespaces;
            auto root_ns_it = root_namespaces.find(namespaces[0]);
            if (root_ns_it == root_namespaces.end())
            {
                return nullptr;
            }

            shared_ptr<Namespace> result = root_ns_it->second;
            std::map<std::string, shared_ptr<Namespace>>& current = result->nested_namespaces;
            for (int index = 1; index < namespaces.size(); index++)
            {
                auto nested_ns_it = current.find(namespaces[index]);
                if (nested_ns_it != current.end())
                {
                    result = nested_ns_it->second;
                    current = result->nested_namespaces;
                    continue;
                }
                return nullptr;
            }
            return result;
        }
        return nullptr;
    }
}
