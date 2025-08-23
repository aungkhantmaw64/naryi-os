#!/bin/bash

source ${ZEPHYR_ROOT}/.venv/bin/activate

if [ ! -d ".west" ]; then
  echo "Initilizing west for the first time"
  rm -rf ${ZEPHYR_ROOT}/.west
  west init -l naryi-os
  west update
  west zephyr-export
fi

echo "Zephyr Project dev environment is ready!"
exec "$@"
