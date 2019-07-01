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

#include "llvm/Support/CommandLine.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/AST/DeclCXX.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;


static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp(
    "\tFor example, to run clang-bcapi on all files in a subtree of the\n"
    "\tsource tree, use:\n"
    "\n"
    "\t  find path/in/subtree -name '*.cpp'|xargs clang-check\n"
    "\n"
    "\tor using a specific build path:\n"
    "\n"
    "\t  find path/in/subtree -name '*.cpp'|xargs clang-check -p build/path\n"
    "\n"
    "\tNote, that path/in/subtree and current directory should follow the\n"
    "\trules described above.\n"
    "\n"
);
static llvm::cl::OptionCategory BcapiToolCategory("clang-bcapi options"); 
llvm::cl::list<std::string> 
NamespacesList(llvm::cl::Positional, llvm::cl::Required, llvm::cl::desc("<root namespaces>"), llvm::cl::OneOrMore);
llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional, llvm::cl::Required, llvm::cl::desc("<output file>"));

DeclarationMatcher methodMatcher = clang::ast_matchers::decl().bind("decl");

class Dumper : public clang::ast_matchers::MatchFinder::MatchCallback {
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result) {
        if (const CXXMethodDecl *md = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("decl")) {
            std::cout << md->getQualifiedNameAsString() << std::endl;
        }
    }
};



int main(int argc, const char **argv)
{
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, BcapiToolCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
        OptionsParser.getSourcePathList());

    // TODO get namespaces from console arguments
    std::vector<std::string> base_namespaces = { "TestNS" };
        
    //std::vector<std::unique_ptr<clang::ASTUnit>> asts;
    //int result = Tool.buildASTs(asts);
    //for (auto const &ast: asts)
    //{
    //    const clang::ASTContext &context = ast->getASTContext();

    //}
    
    Dumper dumper;
    clang::ast_matchers::MatchFinder Finder;
    Finder.addMatcher(methodMatcher, &dumper);
    int result = Tool.run(newFrontendActionFactory(&Finder).get());
    return result;
}
