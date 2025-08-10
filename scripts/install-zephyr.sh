#!/bin/bash

echo "Step 1/1 - Install Python Dependencies"

mkdir -p ${ZEPHYR_ROOT}

pushd ${ZEPHYR_ROOT}
  python3 -m venv .venv
  source .venv/bin/activate
  pip install west
popd

echo "Step 1/1 - Done!"
