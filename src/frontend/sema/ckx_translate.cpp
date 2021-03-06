﻿#include "frontend/AST/ckx_ast_node.hpp"
#include "frontend/sema/ckx_sema.hpp"
#include "frontend/sema/ckx_sema_result.hpp"

namespace ckx
{

/// @todo this is just for suppressing warnings.
using bwsb = saber::optional<ckx_expr_result>;

void ckx_ast_translation_unit::accept(ckx_sema_engine &_sema)
{
    _sema.visit_translation_unit(this);
}

void ckx_ast_compound_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_compound_stmt(this);
}

void ckx_ast_if_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_if_stmt(this);
}

void ckx_ast_while_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_while_stmt(this);
}

void ckx_ast_do_while_stmt::accept(ckx_sema_engine&) {}
void ckx_ast_for_stmt::accept(ckx_sema_engine&) {}
void ckx_ast_break_stmt::accept(ckx_sema_engine&) {}
void ckx_ast_continue_stmt::accept(ckx_sema_engine&) {}

void ckx_ast_return_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_return_stmt(this);
}

void ckx_ast_decl_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_decl_stmt(this);
}

void ckx_ast_expr_stmt::accept(ckx_sema_engine& _sema)
{
    expr->accept(_sema);
}

void ckx_ast_func_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_func_stmt(this);
}

void ckx_ast_record_stmt::accept(ckx_sema_engine& _sema)
{
    _sema.visit_record_stmt(this);
}

void ckx_ast_alias_stmt::accept(ckx_sema_engine&) {}
void ckx_ast_enum_stmt::accept(ckx_sema_engine&) {}

saber::optional<ckx_expr_result>
ckx_ast_binary_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_binary_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_unary_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_unary_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_subscript_expr::accept(ckx_sema_engine&) { return bwsb(); }

saber::optional<ckx_expr_result>
ckx_ast_invoke_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_invoke_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_extract_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_extract_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_enumerator_expr::accept(ckx_sema_engine&) { return bwsb(); }
saber::optional<ckx_expr_result>
ckx_ast_cond_expr::accept(ckx_sema_engine&) { return bwsb(); }

saber::optional<ckx_expr_result>
ckx_ast_id_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_id_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_cast_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_cast_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_sizeof_expr::accept(ckx_sema_engine&) { return bwsb(); }

saber::optional<ckx_expr_result>
ckx_ast_vi_literal_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_vi_literal_node(this);
}

saber::optional<ckx_expr_result>
ckx_ast_vr_literal_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_vr_literal_node(this);
}

saber::optional<ckx_expr_result>
ckx_ast_bool_literal_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_vbool_literal_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_nullptr_expr::accept(ckx_sema_engine& _sema)
{
    return _sema.visit_nullptr_expr(this);
}

saber::optional<ckx_expr_result>
ckx_ast_array_expr::accept(ckx_sema_engine&) { return bwsb(); }

} // namespace ckx
