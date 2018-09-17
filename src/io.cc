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

#include "io.h"

#include <iostream>

namespace io {
namespace {
using model::Segfault;
using std::cin;
using std::cout;
}  // namespace
void read(Memory& ram) {
  char c;
  int32_t curr = 0;
  while (cin.get(c)) {
    if (curr >= ram.size())
      throw Segfault(curr);
    else
      ram.set(static_cast<uint8_t>(c), curr++);
  }
}
void dump(const Memory& ram) noexcept {
  cout.write(ram.c_str_rep(), ram.size()).flush();
}
}  // namespace io