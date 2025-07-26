#!/bin/bash
set -e

mkdir -p build && cd build

cmake .. \
	-DCMAKE_PREFIX_PATH=/opt/hypernex-libs/math \
	-DCMAKE_INSTALL_PREFIX=/opt/hypernex-libs/ml

cmake --build .
sudo cmake --install .

