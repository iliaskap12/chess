#!/bin/bash

## Tested with:
## Ubuntu 21.04 hirsute hippo
## g++11
## -std=c++20
## cmake version 3.22.1
## either unzip code or git clone https://github.com/iliaskap12/chess.git
## sgg library fetched using fetch content - no dependencies issued faced with that approach

cd chess && \
mkdir cmake-build-release && \
cmake -S . -B cmake-build-release -DCMAKE_CXX_STANDARD=20 -DCMAKE_CXX_STANDARD_REQUIRED=ON -DCMAKE_BUILD_TYPE=Release \
 -DCMAKE_CXX_EXTENSIONS=OFF -G Ninja && \
cmake --build cmake-build-release --target chess
