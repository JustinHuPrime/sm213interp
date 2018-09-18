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

#ifndef SM213INTERP_MODEL_EVALUATOR_H_
#define SM213INTERP_MODEL_EVALUATOR_H_

#include "model/memory.h"

#include <initializer_list>

namespace sm213interp::model {
namespace {
using sm213common::model::Memory;
using std::exception;
using std::initializer_list;
using std::string;
}  // namespace

class IllegalInstruction : public exception {
 public:
  IllegalInstruction(uint32_t addr) noexcept;
  const char* what() const noexcept override;

 protected:
  string msg;
};

void run(Memory& ram, uint32_t);

void checkRegisters(initializer_list<uint8_t>, uint32_t);
uint8_t combineNibbles(uint8_t, uint8_t) noexcept;
}  // namespace sm213interp::model

#endif  // SM213INTERP_MODEL_EVALUATOR_H_