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

namespace TestNS
{
    namespace NestedNS
    {
        class TestClass
        {
        public:
        
            class IgnoringClass
            {
                public:
                int x;
            };
            
            TestClass &operator += (const TestClass &rhs) {return *this;};
            
            int field;
            virtual void method() { return ; };            
        };

        void function(int argument) { return ; };

        enum enumeration { value };
    }
    
    class TestClass
    {
    public:
        TestClass(): private_field(NestedNS::TestClass()) {};
        int field;
        NestedNS::TestClass method() { return private_field;};
    private:
        NestedNS::TestClass private_field;
        void private_method() const {};
    
    };

    class ChildClass : public TestClass
    {
        void private_method() const {};
    };
    
    int function(int argument) noexcept { return 0; };

    enum enumeration{ value };
}
