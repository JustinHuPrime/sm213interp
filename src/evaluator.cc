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

#include "evaluator.h"

#include <array>

namespace model {
namespace {
using std::array;
}
void run(Memory& ram) {
  int32_t pc = 0;
  array<int32_t, 8> registers;

  while (true) {
    uint16_t opCode = ram.get(pc);
    opCode <<= 8;
    opCode |= ram.get(pc + 1);
    uint8_t opCode0 = (opCode >> 3 * 4) & 0xf;
    uint8_t opCode1 = (opCode >> 2 * 4) & 0xf;
    uint8_t opCode2 = (opCode >> 1 * 4) & 0xf;
    uint8_t opCode3 = (opCode >> 0 * 4) & 0xf;

    switch (opCode0) {
      case 0x0: {
        break;
      }
      case 0x1: {
        break;
      }
      case 0x2: {
        break;
      }
      case 0x3: {
        break;
      }
      case 0x4: {
        break;
      }
      case 0x5: {
        break;
      }
      case 0x6: {
        break;
      }
      case 0x7: {
        break;
      }
      case 0x8: {
        break;
      }
      case 0x9: {
        break;
      }
      case 0xa: {
        break;
      }
      case 0xb: {
        break;
      }
      case 0xc: {
        break;
      }
      case 0xd: {
        break;
      }
      case 0xe: {
        break;
      }
      case 0xf: {
        break;
      }
    }

    pc += 2;
  }
}
}  // namespace model