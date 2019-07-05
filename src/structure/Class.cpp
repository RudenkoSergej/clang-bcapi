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

#include "structure/Class.h"

using boost::weak_ptr;
using clang::CXXRecordDecl;

namespace structure
{
    Class::Class(const CXXRecordDecl *decl_, weak_ptr<Namespace> parent_)
        :Base(decl_, parent_, decl_->getNameAsString())
    {
        auto base_it = decl_->bases_begin();
        if (base_it != decl_->bases_end())
        this->base = base_it != decl_->bases_end()? base_it->getTypeSourceInfo()->getType().getAsString() : "";
        this->implementation_name = decl_->getQualifiedNameAsString();
        //TODO get the path relative to the output file
        this->implementation_header = decl_->getASTContext().getSourceManager().getFilename(decl_->getLocation()).str();
        this->is_abstract = decl_->isAbstract();
    }
}
