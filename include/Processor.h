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

#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/AST/DeclCXX.h>

#include "Dumper.h"
#include "structure/Tree.h"

class Processor : public clang::ast_matchers::MatchFinder::MatchCallback {
private:
    structure::Tree namespaces;

    void processMethod(const clang::CXXMethodDecl* method_decl);
    void processFunction(const clang::FunctionDecl* func_decl);

public:
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result) override;
    void dump(Dumper &dumper) const;
};