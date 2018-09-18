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

// SM213 interpreter takes one command line argument - memory size in bytes,
// then generates a memory area of that size. The program is then read in from
// standard input, passed through the assembler into machine code (in simulated
// memory), then executed.

#include "io/io.h"
#include "model/evaluator.h"
#include "model/memory.h"

#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
using sm213common::model::Memory;
using sm213common::model::Segfault;
using sm213interp::io::dump;
using sm213interp::io::read;
using sm213interp::model::run;
using std::cerr;
using std::invalid_argument;
using std::numeric_limits;
using std::stoul;
using std::string;
}  // namespace

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Expected memory size (in bytes) and starting pc as arguments.\n";
    return EXIT_FAILURE;
  }

  unsigned long buffer;
  uint32_t memsize, startingPc;

  try {
    buffer = stoul(string(argv[1]));
    if (memsize > numeric_limits<uint32_t>().max()) throw invalid_argument("");
    memsize = static_cast<uint32_t>(buffer);
  } catch (const invalid_argument&) {
    cerr << "Expected memory size to be a valid and positive integer. Found '"
         << argv[1] << "' instead.\n";
    return EXIT_FAILURE;
  }

  try {
    buffer = stoul(string(argv[2]));
    if (memsize > numeric_limits<uint32_t>().max()) throw invalid_argument("");
    startingPc = static_cast<uint32_t>(buffer);
  } catch (const invalid_argument&) {
    cerr << "Expected starting pc to be a valid and positive integer. Found '"
         << argv[2] << "' instead.\n";
    return EXIT_FAILURE;
  }

  Memory ram(memsize);

  try {
    read(ram);
  } catch (const Segfault&) {
    cerr << "Input too long - out of memory.\n";
    return EXIT_FAILURE;
  }
  try {
    run(ram, startingPc);
  } catch (const Segfault& e) {
    cerr << e.what() << "\n";
  }
  dump(ram);

  return EXIT_SUCCESS;
}