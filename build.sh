#!/usr/bin/env bash

set -e

echo "==> Generating project files with Premake..."
./tools/premake5 gmake

echo "==> Building project..."
make

echo "==> Build finished!"

echo "Running..."

LD_LIBRARY_PATH=libs/raylib/lib ./build/bin/Debug/Game