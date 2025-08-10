#!/bin/bash

source ${ZEPHYR_ROOT}/.venv/bin/activate

if [ ! -d ".west" ]; then
  echo "Initilizing west for the first time"
  west init -l naryi-os
  west update
  west zephyr-export
  west packages pip --install
  pushd zephyr
  echo "Install zephyr sdk with west"
  west sdk install
  popd
fi

echo "Zephyr Project dev environment is ready!"
exec "$@"
