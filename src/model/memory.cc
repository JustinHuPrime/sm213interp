// Copyright 2018 Justin Hu
//
// This file is part of the SM213 common library.
//
// The SM213 common library is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// The SM213 common library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// the SM213 common library.  If not, see <https://www.gnu.org/licenses/>.

#include "model/memory.h"

#include <sstream>
#include <stdexcept>

namespace sm213common::model {
namespace {
using std::invalid_argument;
using std::max;
using std::stringstream;
using std::to_string;
}  // namespace

Segfault::Segfault(uint32_t attemptLocation) noexcept {
  stringstream ss;
  ss << "Invalid access to location 0x" << std::hex << attemptLocation << ".";
  msg = ss.str();
}
const char* Segfault::what() const noexcept { return msg.c_str(); }

Memory::Memory(uint32_t size) noexcept
    : arena{new uint8_t[size]}, arenaSize{size} {}
Memory::~Memory() noexcept { delete[] arena; }

uint8_t Memory::get(uint32_t location) {
  if (location >= arenaSize)
    throw Segfault(location);
  else
    return arena[location];
}
void Memory::set(uint8_t data, uint32_t location) {
  if (location >= arenaSize)
    throw Segfault(location);
  else
    arena[location] = data;
}
int32_t Memory::getn(uint32_t location) {
  if (location + 4 >= arenaSize)
    throw Segfault(location);
  else
    return arena[location + 0] * 0x1000000 + arena[location + 1] * 0x10000 +
           arena[location + 2] * 0x100 + arena[location + 3] * 0x1;
}
void Memory::setn(int32_t data, uint32_t location) {
  if (location + 4 >= arenaSize) {
    throw Segfault(location);
  } else {
    arena[location + 0] = (data >> 3 * 8) & 0xff;
    arena[location + 1] = (data >> 2 * 8) & 0xff;
    arena[location + 2] = (data >> 1 * 8) & 0xff;
    arena[location + 3] = (data >> 0 * 8) & 0xff;
  }
}

uint32_t Memory::size() const noexcept { return arenaSize; }

const char* Memory::c_str_rep() const noexcept {
  return reinterpret_cast<char*>(arena);
}
}  // namespace sm213common::model
