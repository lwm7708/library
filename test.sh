#!/usr/bin/env bash

set -e

echo

clang++ "-I$(pwd)" -O2 -Wall -Wextra -Wfloat-equal -Wshadow -std=c++17 "test.cpp"

./a.out

rm "a.out"
