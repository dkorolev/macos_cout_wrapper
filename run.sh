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
  clang++ -g -O0 $CODE -o .debug/binary
  .debug/binary
elif [ "$MODE" == "release" ] ; then
  mkdir -p .release
  clang++ -O3 $CODE -o .release/binary
  .release/binary
else
  echo '$MODE must be `debug` or `release`.'
  exit 1
fi
