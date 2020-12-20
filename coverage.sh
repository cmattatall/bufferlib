#!/bin/bash

rm -r build
cmake -S . -B build && cmake --build build
pushd build/test
ctest -V
popd

