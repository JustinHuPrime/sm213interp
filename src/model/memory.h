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

#ifndef SM213COMMON_MODEL_MEMORY_H_
#define SM213COMMON_MODEL_MEMORY_H_

#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <string>

namespace sm213interp::model {
namespace {
using std::exception;
using std::string;
}  // namespace

class Segfault : public exception {
 public:
  explicit Segfault(uint32_t attemptLocation) noexcept;
  Segfault(const Segfault&) noexcept = default;
  Segfault& operator=(const Segfault&) noexcept = default;

  const char* what() const noexcept override;

 private:
  string msg;
};

class Memory {
 public:
  explicit Memory(uint32_t size) noexcept;
  Memory(Memory&&) noexcept = default;

  ~Memory() noexcept;

  Memory& operator=(Memory&&) noexcept = default;

  uint8_t get(uint32_t);
  void set(uint8_t data, uint32_t location);
  uint32_t getn(uint32_t);
  void setn(uint32_t data, uint32_t location);

  uint32_t size() const noexcept;
  const char* c_str_rep() const noexcept;

 private:
  uint8_t* arena;
  uint32_t arenaSize;
};
}  // namespace sm213interp::model

#endif  // SM213COMMON_MODEL_MEMORY_H_
