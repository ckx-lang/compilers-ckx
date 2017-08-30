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

#ifndef CKX_ERROR_HPP
#define CKX_ERROR_HPP

#include "defs.hpp"
#include "string.hpp"
#include "memory.hpp"

namespace ckx
{

class ckx_error
{
public:
    ckx_error(const qcoord& _pos, saber::string&& _desc, bool _is_fatal) :
        pos(_pos), desc(saber::move(_desc)), is_fatal(_is_fatal) {}

    qcoord pos;
    saber::string desc;
    bool is_fatal;
};

}
#endif // CKX_ERROR_HPP
