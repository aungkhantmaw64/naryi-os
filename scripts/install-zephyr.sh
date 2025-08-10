#!/bin/bash

echo "Install Python Dependencies"

mkdir -p ${ZEPHYR_ROOT}

pushd ${ZEPHYR_ROOT}
  python3 -m venv .venv
  source .venv/bin/activate
  pip install west
popd

echo "Done!"
