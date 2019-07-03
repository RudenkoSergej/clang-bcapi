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

using boost::shared_ptr;
using namespace clang;
using namespace clang::ast_matchers;
using namespace structure;

void Processor::processMethod(const CXXMethodDecl *method_decl)
{
    return;
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

