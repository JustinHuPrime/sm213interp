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

namespace sm213common::model {
namespace {
using std::exception;
using std::string;
}  // namespace

class Segfault : public exception {
 public:
  Segfault(int32_t attemptLocation) noexcept;
  const char* what() const noexcept override;

 private:
  string msg;
};

class Memory {
 public:
  explicit Memory(int32_t size) noexcept;
  ~Memory() noexcept;

  uint8_t get(int32_t);
  void set(uint8_t data, int32_t location);
  int32_t getn(int32_t);
  void setn(int32_t data, int32_t location);

  int32_t size() const noexcept;
  const char* c_str_rep() const noexcept;

 private:
  uint8_t* arena;
  int32_t arenaSize;
};
}  // namespace sm213common::model

#endif  // SM213COMMON_MODEL_MEMORY_H_
