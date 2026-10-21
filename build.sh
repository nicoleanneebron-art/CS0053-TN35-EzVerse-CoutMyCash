#!/usr/bin/env bash

set -euo pipefail

if ! command -v g++ >/dev/null 2>&1; then
    echo "Error: g++ was not found. Install a C++ compiler and add it to PATH." >&2
    exit 1
fi

mkdir -p build

g++ -std=c++17 -Iinclude src/*.cpp -o build/CountMyCash

echo "Build complete: build/CountMyCash"
