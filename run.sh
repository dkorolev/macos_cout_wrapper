#!/bin/bash

set -e

MODE=${1:-debug}
CODE=code.cc

if [ "$MODE" == "clean" ] ; then
  rm -rf .debug .release
  exit
fi

echo "Testing $CODE in $MODE mode."
if [ "$MODE" == "debug" ] ; then
  mkdir -p .debug
  clang++ -g -O0 -DDEBUG -std=c++20 $CODE -o .debug/binary -Wno-unqualified-std-cast-call
  .debug/binary
elif [ "$MODE" == "release" ] ; then
  mkdir -p .release
  clang++ -O3 -DNDEBUG -std=c++20 $CODE -o .release/binary -Wno-unqualified-std-cast-call
  .release/binary
else
  echo '$MODE must be `debug` or `release`.'
  exit 1
fi
