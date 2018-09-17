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

#include "memory.h"

namespace model {
namespace {
using model::Memory;
}

class IllegalInstruction : public exception {
 public:
  IllegalInstruction(int32_t addr) noexcept;
  const char* what() const noexcept override;

 protected:
  string msg;
};

void run(Memory& ram);
}  // namespace model