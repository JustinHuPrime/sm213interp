// Copyright 2018 Justin Hu
//
// This file is part of the SM213 interpreter.
//
// The SM213 interpreter is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// The SM213 interpreter is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// the SM213 interpreter.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SM213INTERP_IO_IO_H_
#define SM213INTERP_IO_IO_H_

#include "model/memory.h"

namespace sm213interp::io {
namespace {
using sm213common::model::Memory;
}

// takes stdin as raw data
void read(Memory& ram);
// outputs ram to stdout as raw data
void dump(const Memory& ram) noexcept;
}  // namespace sm213interp::io

#endif  // SM213INTERP_IO_IO_H_