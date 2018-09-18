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

#include "model/evaluator.h"

#include <array>
#include <sstream>

namespace sm213interp::model {
namespace {
using std::array;
using std::stringstream;
using std::to_string;
}  // namespace

IllegalInstruction::IllegalInstruction(uint32_t addr) noexcept {
  stringstream sstream;
  sstream << std::hex << addr;

  msg = "Attempted to execute illegal instruction at " + sstream.str() + ".";
}
const char* IllegalInstruction::what() const noexcept { return msg.c_str(); }

void run(Memory& ram, uint32_t pc) {
  array<int32_t, 8> registers;

  while (true) {
    uint16_t opCode = ram.get(pc++);
    opCode <<= 8;
    opCode |= ram.get(pc++);
    uint8_t opCode0 = (opCode >> 3 * 4) & 0xf;
    uint8_t opCode1 = (opCode >> 2 * 4) & 0xf;
    uint8_t opCode2 = (opCode >> 1 * 4) & 0xf;
    uint8_t opCode3 = (opCode >> 0 * 4) & 0xf;

    // pc gets updated before any instructions are evaluated.

    switch (opCode0) {
      case 0x0: {  // load immediate
        checkRegisters({opCode1}, pc);
        registers[opCode1] = ram.getn(pc);
        pc += 4;
        break;
      }
      case 0x1: {  // load base+offset
        checkRegisters({opCode2, opCode3}, pc);
        registers[opCode3] =
            ram.getn(opCode1 * 4U + static_cast<uint32_t>(registers[opCode2]));
        break;
      }
      case 0x2: {  // load indexed
        checkRegisters({opCode1, opCode2, opCode3}, pc);
        registers[opCode3] =
            ram.getn(static_cast<uint32_t>(registers[opCode1]) +
                     static_cast<uint32_t>(registers[opCode2]) * 4U);
        break;
      }
      case 0x3: {  // store base + offset
        checkRegisters({opCode1, opCode3}, pc);
        ram.setn(registers[opCode1],
                 opCode2 * 4U + static_cast<uint32_t>(registers[opCode3]));
        break;
      }
      case 0x4: {  // store indexed
        checkRegisters({opCode1, opCode2, opCode3}, pc);
        ram.setn(registers[opCode1],
                 static_cast<uint32_t>(registers[opCode2]) +
                     static_cast<uint32_t>(registers[opCode3]) * 4U);
        break;
      }
      case 0x5: {  // nothing starts with 5!
        throw IllegalInstruction(pc - 2);
      }
      case 0x6: {  // arithmetic
        checkRegisters({opCode3}, pc);
        switch (opCode1) {
          case 0x0: {  // assignment
            checkRegisters({opCode2}, pc);
            registers[opCode3] = registers[opCode2];
            break;
          }
          case 0x1: {  // addition
            checkRegisters({opCode2}, pc);
            registers[opCode3] += registers[opCode2];
            break;
          }
          case 0x2: {  // bitwise and
            checkRegisters({opCode2}, pc);
            registers[opCode3] &= registers[opCode2];
            break;
          }
          case 0x3: {  // increment
            registers[opCode3] += 1;
            break;
          }
          case 0x4: {  // increment by 4
            registers[opCode3] += 4;
            break;
          }
          case 0x5: {  // decrement
            registers[opCode3] -= 1;
            break;
          }
          case 0x6: {  // decrement by 4
            registers[opCode3] -= 4;
            break;
          }
          case 0x7: {  // bitwise not
            registers[opCode3] = ~registers[opCode3];
            break;
          }
          case 0xf: {  // get pc
            registers[opCode3] = static_cast<int32_t>(pc + 2U * opCode2);
            break;
          }
          default: { throw IllegalInstruction(pc - 2); }
        }
        break;
      }
      case 0x7: {  // shift
        checkRegisters({opCode1}, pc);
        int8_t shiftAmount =
            static_cast<int8_t>(combineNibbles(opCode2, opCode3));
        if (shiftAmount < 0)
          registers[opCode1] >>= -shiftAmount;
        else
          registers[opCode1] <<= shiftAmount;
        break;
      }
      case 0x8: {  // branch
        pc += 2U * combineNibbles(opCode2, opCode3);
        break;
      }
      case 0x9: {  // branch if equal
        checkRegisters({opCode1}, pc);
        if (registers[opCode1] == 0)
          pc += 2U * combineNibbles(opCode2, opCode3);
        break;
      }
      case 0xa: {  // branch if greater
        checkRegisters({opCode1}, pc);
        if (registers[opCode1] > 0) pc += 2U * combineNibbles(opCode2, opCode3);
        break;
      }
      case 0xb: {  // unconditional jump
        pc = static_cast<uint32_t>(ram.getn(pc));
        break;
      }
      case 0xc: {  // jump indirect
        checkRegisters({opCode1}, pc);
        pc = static_cast<uint32_t>(registers[opCode1]) +
             2U * combineNibbles(opCode2, opCode3);
        break;
      }
      case 0xd: {  // jump double indirect, base plus offset
        checkRegisters({opCode1}, pc);
        pc = ram.get(combineNibbles(opCode2, opCode3) +
                     static_cast<uint32_t>(registers[opCode1]));
        break;
      }
      case 0xe: {  // jump double indirect, indexed
        checkRegisters({opCode1, opCode2}, pc);
        pc = ram.get(4U * static_cast<uint32_t>(registers[opCode1]) +
                     static_cast<uint32_t>(registers[opCode2]));
        break;
      }
      case 0xf: {  // nop and halt
        if (opCode2 != 0 || opCode3 != 0) throw IllegalInstruction(pc - 2);
        if (opCode1 == 0x0)  // halt
          return;
        else if (opCode1 == 0xf)  // nop
          break;
        else
          throw IllegalInstruction(pc - 2);
      }
      default: { abort(); }  // something is horribly wrong!
    }
  }
}

void checkRegisters(initializer_list<uint8_t> registers, uint32_t currPC) {
  for (uint8_t iter : registers) {
    if (iter > 7) throw IllegalInstruction(currPC - 2);
  }
}

uint8_t combineNibbles(uint8_t nibble1, uint8_t nibble2) noexcept {
  uint8_t temp = 0;
  temp |= nibble1;
  temp <<= 4;
  temp |= nibble2;
  return temp;
}
}  // namespace sm213interp::model