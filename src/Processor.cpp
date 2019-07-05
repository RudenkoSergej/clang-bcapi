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

#include <boost/shared_ptr.hpp>

#include "Processor.h"
#include "structure/Tree.h"
#include "structure/Base.h"
#include "structure/Namespace.h"
#include "structure/Function.h"
#include "structure/Class.h"
#include "structure/Method.h"
#include "structure/Constructor.h"

using boost::shared_ptr;
using namespace clang;
using namespace clang::ast_matchers;
using namespace structure;

void Processor::processConstructor(const CXXConstructorDecl *ctor_decl)
{
    const DeclContext *decl = ctor_decl->getParent();
    if (decl)
    {
        if (ctor_decl->isCopyOrMoveConstructor())
        {
            return;
        }
        const CXXRecordDecl *class_decl = dyn_cast<CXXRecordDecl>(decl);
        shared_ptr<Class> parent_class = namespaces.GetOrGenClass(class_decl);
        if (parent_class && ctor_decl->getAccess() == AccessSpecifier::AS_public)
        {
            shared_ptr<Constructor> ctor(new Constructor(ctor_decl, parent_class));
            parent_class->constructors.push_back(ctor);
            bool first_arg = true;
            for (const auto &param : ctor_decl->parameters())
            {
                if (first_arg)
                {
                    first_arg = false;
                    continue;
                }
                shared_ptr<Argument> argument(new Argument(param, ctor));
                ctor->arguments.push_back(argument);
            }
        }
    }
}

void Processor::processMethod(const CXXMethodDecl *method_decl)
{
    const DeclContext *decl = method_decl->getParent();
    if (decl && isa<CXXRecordDecl>(decl))
    {
        const CXXRecordDecl *class_decl = dyn_cast<CXXRecordDecl>(decl);
        shared_ptr<Class> parent_class = namespaces.GetOrGenClass(class_decl);
        if (parent_class && method_decl->getAccess() == AccessSpecifier::AS_public)
        {
            if (isa<CXXConstructorDecl>(method_decl))
            {
                processConstructor(dyn_cast<CXXConstructorDecl>(method_decl));
                return;
            }
            // skip operators
            // FIXME find better way to determine if the method is an operator
            if (method_decl->getNameAsString().find("operator") == 0)
            {
                return;
            }
            // skip destructor
            if (isa<CXXDestructorDecl>(method_decl))
            {
                return;
            }
            shared_ptr<Method> method(new Method(method_decl, parent_class));
            parent_class->methods.push_back(method);
            for (const auto &param : method_decl->parameters())
            {
                shared_ptr<Argument> argument(new Argument(param, method));
                method->arguments.push_back(argument);
            }
        }
    }
}

void Processor::processFunction(const FunctionDecl *func_decl)
{
    const DeclContext *decl = func_decl->getParent();
    if (decl && isa<NamespaceDecl>(decl))
    {
        const NamespaceDecl *namespace_decl = dyn_cast<NamespaceDecl>(decl);
        shared_ptr<Namespace> parent_namespace = namespaces.GetOrGenNamespace(namespace_decl);
        //ignore global functions
        if (parent_namespace)
        {
            shared_ptr<Function> function(new Function(func_decl, parent_namespace));
            parent_namespace->funtions.push_back(function);
            for (const auto &param : func_decl->parameters())
            {
                shared_ptr<Argument> argument(new Argument(param, function));
                function->arguments.push_back(argument);
            }
        }
    }
}
void Processor::run(const MatchFinder::MatchResult &Result)
{
    const Decl *decl = Result.Nodes.getNodeAs<Decl>("decl");
    if (isa<FunctionDecl>(decl)) {
        if (isa<CXXMethodDecl>(decl))
        {
            const CXXMethodDecl *method_decl = dyn_cast<CXXMethodDecl>(decl);
            this->processMethod(method_decl);
        }
        else
        {
            const FunctionDecl *func_decl = dyn_cast<FunctionDecl>(decl);
            this->processFunction(func_decl);
        }
    }
}

void Processor::dump(Dumper &dumper) const
{
    dumper.dump(namespaces);
}
