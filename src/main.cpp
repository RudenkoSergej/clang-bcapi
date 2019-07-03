/* 
* clang - bcapi generates xml scheme for Beautiful Capi
* Copyright(C) 2019 Petr Petrovich Petrov
* 
* This file is part of clang - bcapi.
* 
* clang-bcapi is free software : you can redistribute it and/or modify
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

#include <iostream>


#include <llvm/Support/CommandLine.h>
#include <clang/Frontend/ASTUnit.h>
#include <clang/AST/DeclCXX.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

#include "Processor.h"
#include "Dumper.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace structure;


static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp("usage:\n clang-bcapi <namespaces> <output_xml> <sources>");
static llvm::cl::OptionCategory BcapiToolCategory("clang-bcapi options"); 
llvm::cl::list<std::string> NamespacesList(
    llvm::cl::Positional, 
    llvm::cl::Required, 
    llvm::cl::desc("<root namespaces>"), 
    llvm::cl::OneOrMore);
llvm::cl::opt<std::string> OutputFilename(llvm::cl::Positional, llvm::cl::Required, llvm::cl::desc("<output file>"));

DeclarationMatcher declarationMatcher = clang::ast_matchers::decl().bind("decl");

int main(int argc, const char **argv)
{
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, BcapiToolCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
        OptionsParser.getSourcePathList());

    std::vector<std::string> base_namespaces;
    base_namespaces.reserve(NamespacesList.size());
    for (auto it : NamespacesList)
    {
        base_namespaces.push_back(it);
    }
;
    
    Processor processor;
    clang::ast_matchers::MatchFinder Finder;
    Finder.addMatcher(declarationMatcher, &processor);
    int result = Tool.run(newFrontendActionFactory(&Finder).get());
    if (!result)
    {
        Dumper dumper(base_namespaces, OutputFilename.getValue());
        processor.dump(dumper);
    }

    return result;
}
