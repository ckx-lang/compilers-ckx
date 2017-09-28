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


#include "ckx_ast_node.hpp"

namespace ckx
{

ckx_ast_node::ckx_ast_node(saber_ptr<ckx_token> _at_token) :
    at_token(_at_token)
{}

saber_ptr<ckx_token> ckx_ast_node::get_at_token()
{ return at_token; }

ckx_ast_translation_unit::ckx_ast_translation_unit(
        saber_ptr<ckx_token> _at_token) :
    ckx_ast_node(_at_token),
    global_table(new ckx_env(nullptr))
{}

ckx_ast_translation_unit::~ckx_ast_translation_unit()
{
    for (auto it = stmts.begin(); it != stmts.end(); ++it)
    {
        delete *it;
    }

    delete global_table;
}

void
ckx_ast_translation_unit::add_new_stmt(ckx_ast_stmt *_stmt)
{
    stmts.push_back(_stmt);
}

ckx_ast_stmt::ckx_ast_stmt(saber_ptr<ckx_token> _at_token) :
    ckx_ast_node(_at_token)
{}

ckx_ast_stmt::~ckx_ast_stmt() {}

ckx_ast_compound_stmt::ckx_ast_compound_stmt(
        saber_ptr<ckx_token> _at_token,
        ckx_env *_table) :
    ckx_ast_stmt(_at_token),
    local_table(_table)
{}

ckx_ast_compound_stmt::~ckx_ast_compound_stmt()
{
    for (ckx_ast_stmt* x : stmts)
        delete x;
    delete local_table;
}

void
ckx_ast_compound_stmt::add_new_stmt(ckx_ast_stmt* _stmt)
{
    stmts.push_back(_stmt);
}

ckx_ast_if_stmt::ckx_ast_if_stmt(saber_ptr<ckx_token> _at_token,
                                 ckx_ast_expr *_condition,
                                 ckx_ast_stmt *_then_clause,
                                 ckx_ast_stmt *_else_clause) :
    ckx_ast_stmt(_at_token),
    condition(_condition),
    then_clause(_then_clause),
    else_clause(_else_clause)
{}

ckx_ast_if_stmt::~ckx_ast_if_stmt()
{
    delete condition;
    delete then_clause;
    delete else_clause;
}

ckx_ast_while_stmt::ckx_ast_while_stmt(saber_ptr<ckx_token> _at_token,
                                       ckx_ast_expr *_condition,
                                       ckx_ast_stmt *_clause) :
    ckx_ast_stmt(_at_token),
    condition(_condition),
    clause(_clause)
{}

ckx_ast_while_stmt::~ckx_ast_while_stmt()
{
    delete condition;
    delete clause;
}

ckx_ast_do_while_stmt::ckx_ast_do_while_stmt(saber_ptr<ckx_token> _at_token,
                                             ckx_ast_expr *_condition,
                                             ckx_ast_stmt *_clause) :
    ckx_ast_stmt(_at_token),
    condition(_condition),
    clause(_clause)
{}

ckx_ast_do_while_stmt::~ckx_ast_do_while_stmt()
{
    delete condition;
    delete clause;
}

ckx_ast_for_stmt::ckx_ast_for_stmt(saber_ptr<ckx_token> _at_token,
                                   ckx_ast_expr *_init,
                                   ckx_ast_expr *_condition,
                                   ckx_ast_expr *_incr,
                                   ckx_ast_stmt *_clause) :
    ckx_ast_stmt(_at_token),
    init(_init),
    condition(_condition),
    incr(_incr),
    clause(_clause)
{}

ckx_ast_for_stmt::~ckx_ast_for_stmt()
{
    delete init;
    delete condition;
    delete incr;
    delete clause;
}

ckx_ast_break_stmt::ckx_ast_break_stmt(saber_ptr<ckx_token> _at_token) :
    ckx_ast_stmt(_at_token)
{}

ckx_ast_continue_stmt::ckx_ast_continue_stmt(saber_ptr<ckx_token> _at_token) :
    ckx_ast_stmt(_at_token)
{}

ckx_ast_return_stmt::ckx_ast_return_stmt(saber_ptr<ckx_token> _at_token,
                                         ckx_ast_expr *_return_expr) :
    ckx_ast_stmt(_at_token),
    return_expr(_return_expr)
{}

ckx_ast_decl_stmt::ckx_ast_decl_stmt(saber_ptr<ckx_token> _at_token) :
    ckx_ast_stmt(_at_token)
{}

void
ckx_ast_decl_stmt::add_decl(ckx_ast_init_decl *_decl)
{
    decls.push_back(_decl);
}

ckx_ast_decl_stmt::~ckx_ast_decl_stmt()
{
    for (auto it = decls.begin(); it != decls.end(); ++it) delete *it;
}

ckx_ast_expr_stmt::ckx_ast_expr_stmt(saber_ptr<ckx_token> _at_token,
                                     ckx_ast_expr *_expr) :
    ckx_ast_stmt(_at_token),
    expr(_expr)
{}

ckx_ast_expr_stmt::~ckx_ast_expr_stmt()
{
    delete expr;
}



ckx_ast_func_stmt::ckx_ast_func_stmt(
        saber_ptr<ckx_token> _at_token,
        ckx_func_entry *_entry,
        ckx_env *_param_env_table,
        saber::vector<ckx_ast_init_decl *> &&_param_decls) :
    ckx_ast_stmt(_at_token),
    entry(_entry),
    param_env_table(_param_env_table),
    param_decls(saber::move(_param_decls))
{}

ckx_ast_func_stmt::~ckx_ast_func_stmt()
{
    delete param_env_table;
    for (auto& param_decl : param_decls)
        delete param_decl;
}

void ckx_ast_func_stmt::define(ckx_ast_compound_stmt *_fnbody)
{
    fnbody = _fnbody;
}

ckx_ast_init_decl::ckx_ast_init_decl(saber_ptr<ckx_token> _at_token,
                                     ckx_var_entry* _entry,
                                     ckx_ast_expr *_init) :
    ckx_ast_node(_at_token),
    entry(_entry),
    init(_init)
{}

ckx_ast_init_decl::~ckx_ast_init_decl()
{
    delete init;
}

ckx_ast_struct_stmt::ckx_ast_struct_stmt(saber_ptr<ckx_token> _at_token,
                               ckx_type_entry *_entry) :
    ckx_ast_stmt(_at_token),
    entry(_entry)
{}

ckx_ast_struct_stmt::~ckx_ast_struct_stmt() {}

ckx_ast_variant_stmt::ckx_ast_variant_stmt(saber_ptr<ckx_token> _at_token,
                                 ckx_type_entry *_entry) :
    ckx_ast_stmt(_at_token),
    entry(_entry)
{}

ckx_ast_variant_stmt::~ckx_ast_variant_stmt() {}

ckx_ast_enum_stmt::ckx_ast_enum_stmt(saber_ptr<ckx_token> _at_token,
                           ckx_type_entry *_entry) :
    ckx_ast_stmt(_at_token),
    entry(_entry)
{}

ckx_ast_enum_stmt::~ckx_ast_enum_stmt() {}



ckx_ast_expr::ckx_ast_expr(saber_ptr<ckx_token> _at_token) :
    ckx_ast_node(_at_token)
{}

ckx_ast_expr::~ckx_ast_expr() {}

ckx_ast_binary_expr::ckx_ast_binary_expr(saber_ptr<ckx_token> _at_token,
                                         ckx_op _opercode,
                                         ckx_ast_expr *_loperand,
                                         ckx_ast_expr *_roperand) :
    ckx_ast_expr(_at_token),
    opercode(_opercode),
    loperand(_loperand),
    roperand(_roperand)
{}

ckx_ast_binary_expr::~ckx_ast_binary_expr()
{
    delete loperand;
    delete roperand;
}

ckx_ast_unary_expr::ckx_ast_unary_expr(saber_ptr<ckx_token> _at_token,
                                       ckx_op _opercode,
                                       ckx_ast_expr *_operand) :
    ckx_ast_expr(_at_token),
    opercode(_opercode),
    operand(_operand)
{}

ckx_ast_unary_expr::~ckx_ast_unary_expr()
{
    delete operand;
}

ckx_ast_subscript_expr::ckx_ast_subscript_expr(saber_ptr<ckx_token> _at_token,
                                               ckx_ast_expr *_base,
                                               ckx_ast_expr *_subscript) :
    ckx_ast_expr(_at_token),
    base(_base),
    subscript(_subscript)
{}

ckx_ast_subscript_expr::~ckx_ast_subscript_expr()
{
    delete base;
    delete subscript;
}

ckx_ast_invoke_expr::ckx_ast_invoke_expr(
        saber_ptr<ckx_token> _at_token,
        ckx_ast_expr *_invokable,
        saber::vector<ckx_ast_expr *> &&_args) :
    ckx_ast_expr(_at_token),
    invokable(_invokable),
    args(saber::move(_args))
{
}

ckx_ast_invoke_expr::~ckx_ast_invoke_expr()
{
    delete invokable;
    for (auto& arg : args) delete arg;
}

ckx_ast_cond_expr::ckx_ast_cond_expr(saber_ptr<ckx_token> _at_token,
                                     ckx_ast_expr *_cond_expr,
                                     ckx_ast_expr *_then_expr,
                                     ckx_ast_expr *_else_expr) :
    ckx_ast_expr(_at_token),
    cond_expr(_cond_expr),
    then_expr(_then_expr),
    else_expr(_else_expr)
{}

ckx_ast_cond_expr::~ckx_ast_cond_expr()
{
    delete cond_expr;
    delete then_expr;
    delete else_expr;
}

ckx_ast_id_expr::ckx_ast_id_expr(saber_ptr<ckx_token> _at_token,
                                 ckx_var_entry *_entry) :
    ckx_ast_expr(_at_token),
    entry(_entry)
{}

ckx_ast_id_expr::~ckx_ast_id_expr()
{}

ckx_ast_cast_expr::ckx_ast_cast_expr(saber_ptr<ckx_token> _at_token,
                                     castop _op,
                                     saber_ptr<ckx_type> _desired_type,
                                     ckx_ast_expr *_expr) :
    ckx_ast_expr(_at_token),
    op(_op),
    desired_type(_desired_type),
    expr(_expr)
{}

ckx_ast_cast_expr::~ckx_ast_cast_expr()
{
    delete expr;
}

ckx_ast_sizeof_expr::ckx_ast_sizeof_expr(saber_ptr<ckx_token> _at_token,
                                         saber_ptr<ckx_type> _type) :
    ckx_ast_expr(_at_token),
    type(_type)
{}

} // namespace ckx
