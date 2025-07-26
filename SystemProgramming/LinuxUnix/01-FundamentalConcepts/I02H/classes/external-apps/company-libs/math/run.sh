#!/bin/bash

mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/hypernex-libs/math
cmake --build .
sudo cmake --install .
