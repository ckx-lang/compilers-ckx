﻿/**
    The Opensource Compiler CKX -- for my honey ChenKX
    Copyright (C) 2017  CousinZe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
  */

/// @note This file contains a MANUAL test. Debuggers should read the log
/// themselves and manually detect bugs.

#include "frontend/parse/ckx_parser_impl.hpp"
#include "saber/memory.hpp"
#include "saber/c8assert.hpp"

using namespace ckx;

class ckx_test_filereader final implements we::we_file_reader
{
public:
    ckx_test_filereader(saber_string&& _str) : str(saber::move(_str)) {}
    ~ckx_test_filereader() = default;
    qchar get_next_char(void) override final
    {
        pos++;
        if (pos-1 < str.size()) return str[pos-1];
        else return static_cast<qchar>(saber::char_traits<qchar>::eof());
    }

private:
    qsizet pos = 0;
    saber_string str;
};


class ckx_parser_impl_test final :
        public detail::ckx_parser_impl
{
    using base = detail::ckx_parser_impl;

public:
    void test_parse_expr_stmt();
    void test_parse_if_stmt();
    void test_parse_while_stmt();
    void test_parse_do_while_stmt();
    void test_parse_for_stmt();
    void test_parse_break_stmt();
    void test_parse_continue_stmt();
    void test_parse_return_stmt();
    void test_parse_compound_stmt();

private:
    void initialize_test(const char *_parse_string);
    void cleanup_test();

    we::we_file_reader *reader;
    we::we_fp_writer writer { stdout };
};



int main()
{
    ckx_parser_impl_test test;
    test.test_parse_expr_stmt();
    test.test_parse_if_stmt();
    test.test_parse_while_stmt();
    test.test_parse_do_while_stmt();
    test.test_parse_for_stmt();
    test.test_parse_break_stmt();
    test.test_parse_continue_stmt();
    test.test_parse_return_stmt();
    test.test_parse_compound_stmt();

    return 0;
}



void
ckx_parser_impl_test::test_parse_expr_stmt()
{
    {
        initialize_test("a = 3 + 2; b = a + 3;");
        ckx_ast_expr_stmt *expr_stmt = base::parse_expr_stmt();
        expr_stmt->ast_dump(writer, 0);
        delete expr_stmt;
        expr_stmt = base::parse_expr_stmt();
        expr_stmt->ast_dump(writer, 0);
        delete expr_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }

    {
        initialize_test("a = b>c?(a*b-c):(a-c);");
        ckx_ast_expr_stmt *expr_stmt = base::parse_expr_stmt();
        expr_stmt->ast_dump(writer, 0);
        delete expr_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_if_stmt()
{
    {
        const char* str =
R"lyp(
                if (a > b) covariant_studio();
)lyp";
        initialize_test(str);
        ckx_ast_if_stmt *if_stmt = base::parse_if_stmt();
        if_stmt->ast_dump(writer, 0);
        delete if_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }

    {
        const char* str =
R"lyp(
                if (a > b) covariant_studio();
                else dragon_vm(libkernelpanic, mikecovlee, ILoveChenKX);
)lyp";
        initialize_test(str);
        ckx_ast_if_stmt *if_stmt = base::parse_if_stmt();
        if_stmt->ast_dump(writer, 0);
        delete if_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_while_stmt()
{
    {
        initialize_test("while (cpp_is_fuck()) make_cpp_more_fucking();");
        ckx_ast_while_stmt *while_stmt = base::parse_while_stmt();
        while_stmt->ast_dump(writer, 0);
        delete while_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_do_while_stmt()
{
    {
        initialize_test("do make_cpp_more_fucking(); while (cpp_is_fuck());");
        ckx_ast_do_while_stmt *do_while_stmt = base::parse_do_while_stmt();
        do_while_stmt->ast_dump(writer, 0);
        delete do_while_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_for_stmt()
{
    {
        initialize_test("for (i = 0; i < 10; ++i) print(array[i]);");
        ckx_ast_for_stmt *for_stmt = base::parse_for_stmt();
        for_stmt->ast_dump(writer, 0);
        delete for_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }

    {
        initialize_test("for (;;) fuck(&cpp);");
        ckx_ast_for_stmt *for_stmt = base::parse_for_stmt();
        for_stmt->ast_dump(writer, 0);
        delete for_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }

    {
        initialize_test("for (; it != end(list); it = next(it)) print(*it);");
        ckx_ast_for_stmt *for_stmt = base::parse_for_stmt();
        for_stmt->ast_dump(writer, 0);
        delete for_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_break_stmt()
{
    {
        initialize_test("break; break;");
        ckx_ast_break_stmt *break_stmt = base::parse_break_stmt();
        break_stmt->ast_dump(writer, 0);
        delete break_stmt;
        break_stmt = base::parse_break_stmt();
        break_stmt->ast_dump(writer, 0);
        delete break_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_continue_stmt()
{
    {
        initialize_test("continue; continue;");
        ckx_ast_continue_stmt *continue_stmt = base::parse_continue_stmt();
        continue_stmt->ast_dump(writer, 0);
        delete continue_stmt;
        continue_stmt = base::parse_continue_stmt();
        continue_stmt->ast_dump(writer, 0);
        delete continue_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_return_stmt()
{
    {
        initialize_test("return;");
        ckx_ast_return_stmt *return_stmt = base::parse_return_stmt();
        return_stmt->ast_dump(writer, 0);
        delete return_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }

    {
        initialize_test("return how_fuck_cpp_is(cpp_std::cpp17);");
        base::typename_table.add_typename(
            saber_string_pool::create_view("cpp_std"));
        ckx_ast_return_stmt *return_stmt = base::parse_return_stmt();
        return_stmt->ast_dump(writer, 0);
        delete return_stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::test_parse_compound_stmt()
{
    {
        const char* str =
R"(
{
    vi8 a, b, c;
    input (&a);
    input (&b);
    c = (a + b) * (a - b);
    print(c);
}
)";

        initialize_test(str);
        ckx_ast_compound_stmt *stmt = base::parse_compound_stmt();
        stmt->ast_dump(writer, 0);
        delete stmt;
        C8ASSERT(base::error_list.empty());
        C8ASSERT(base::warn_list.empty());
        cleanup_test();
    }
}


void
ckx_parser_impl_test::initialize_test(const char* _parse_string)
{
    reader = new ckx_test_filereader(_parse_string);
    base::token_stream = new ckx_token_stream(*reader);
}


void
ckx_parser_impl_test::cleanup_test()
{
    base::typename_table.cleanup();
    delete reader;
    delete base::token_stream;
}

