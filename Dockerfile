FROM debian:bookworm-slim

RUN apt-get update --fix-missing && apt-get install -y --no-install-recommends git cmake \
  ninja-build gperf ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel python3-venv \
  xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1 minicom xxd usbutils

ARG ZEPHYR_ROOT=/opt/zephyrproject
ARG APP_PATH=${ZEPHYR_ROOT}/zephyr/workdir

ENV ZEPHYR_ROOT=${ZEPHYR_ROOT}
ENV APP_PATH=${APP_PATH}

COPY scripts/install-zephyr.sh /install-zephyr.sh

RUN chmod +x /install-zephyr.sh

RUN /install-zephyr.sh

WORKDIR ${APP_PATH}

COPY scripts/container-entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]
