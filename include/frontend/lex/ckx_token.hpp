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


#ifndef CKX_TOKEN_HPP
#define CKX_TOKEN_HPP

#include "we/defs.hpp"
#include "saber/string_pool.hpp"
#include "saber/c8assert.hpp"
#include "frontend/util/ckx_src_rng.hpp"

namespace ckx
{

open_class ckx_token
{
    enum class type : qchar
    {
        tk_assign,             // =

        tk_add,                // +
        tk_sub,                // -
        tk_mul,                // *
        tk_div,                // /
        tk_mod,                // %

        tk_add_assign,         // +=
        tk_sub_assign,         // -=
        tk_mul_assign,         // *=
        tk_div_assign,         // /=
        tk_mod_assign,         // %=

        tk_inc,                // ++
        tk_dec,                // --

        tk_bit_and,            // &
        tk_bit_or,             // |
        tk_bit_not,            // ~
        tk_bit_xor,            // ^

        tk_logic_and,          // &&
        tk_logic_or,           // ||
        tk_logic_not,          // !
        tk_logic_xor,          // ^^

        tk_lt,                 // <
        tk_eq,                 // ==
        tk_gt,                 // >
        tk_leq,                // <=
        tk_geq,                // >=
        tk_neq,                // !=

        tk_colon,              // :
        tk_scope,              // ::
        tk_semicolon,          // ;
        tk_comma,              // ,
        tk_dot,                // .

        tk_lbrace,             // {
        tk_rbrace,             // }
        tk_lbracket,           // [
        tk_rbracket,           // ]
        tk_arr,                // []
        tk_lparen,             // (
        tk_rparen,             // )

        tk_ques,               // ?

        tk_vi8,               // vi8
        tk_vi16,              // vi16
        tk_vi32,              // vi32
        tk_vi64,              // vi64

        tk_vu8,              // vu8
        tk_vu16,             // vu16
        tk_vu32,             // vu32
        tk_vu64,             // vu64

        tk_vch,              // vch

        tk_vr32,             // vr32
        tk_vr64,             // vr64

        tk_vnullptr_t,        // vnptr_t
        tk_vbool,            // vb1

        tk_void,             // void

        tk_function,           // fn

        tk_struct,             // struct
        tk_variant,            // variant
        tk_enum,               // enum
        tk_alias,              // alias

        tk_const,              // const

        tk_if,                 // if
        tk_else,               // else
        tk_for,                // for
        tk_while,              // while
        tk_do,                 // do
        tk_switch,             // switch
        tk_case,               // case
        tk_return,             // return
        tk_break,              // break
        tk_continue,           // continue

        tk_operator,           // operator

        tk_id,                 // identifier

        tk_vi_literal,         // int literal
        // reserved
        tk_vu_literal,         // unsigned literal
        tk_vr_literal,         // real literal
        tk_vchar_literal,      // char literal
        // reserved
        tk_string_literal,     // string literal
        tk_nullptr,            // nullptr
        tk_true,               // true
        tk_false,              // false

        tk_static_cast,        // static_cast
        tk_reinterpret_cast,   // reinterpret_cast
        tk_const_cast,         // const_cast
        tk_ckx_cast,           // ckx_cast

        tk_sizeof,             // sizeof

        tk_eoi                 // EOI
    };

    ckx_token(ckx_src_rng _rng, type _operator);
    ckx_token(ckx_src_rng _rng, qint64 _int_literal);
    ckx_token(ckx_src_rng _rng, quint64 _unsigned_literal);
    ckx_token(ckx_src_rng _rng, qreal _real_literal);
    ckx_token(ckx_src_rng _rng, qchar _char_literal);
    ckx_token(ckx_src_rng _rng, saber_string_view _id);

    ckx_token() = delete;
    ~ckx_token() = default;

    const ckx_src_rng rng;

    type token_type;
    variant token_value
    {
        const qchar ch;
        const qint64 i64;
        const quint64 u64;
        const qreal r;

        token_value() {}
        token_value(qchar _ch) : ch(_ch) {}
        token_value(qint64 _i64) : i64(_i64) {}
        token_value(quint64 _u64) : u64(_u64) {}
        token_value(qreal _r) : r(_r) {}
        ~token_value() = default;
    } v;
    const saber_string_view str = saber_string_pool::create_view("");
};

struct ckx_token_type_hash
{
    size_t operator() (ckx_token::type _type) const
    {
        return std::hash<qchar>()(static_cast<qchar>(_type));
    }
};

saber_string to_string_helper(ckx_token _token);

} // namespace ckx

#endif // CKX_TOKEN_HPP
