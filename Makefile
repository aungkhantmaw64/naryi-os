DOCKER_IMG_NAME=zephyr-project
ZEPHYR_ROOT=/opt/zephyrproject
APP_PATH=${ZEPHYR_ROOT}/zephyr/workdir

docker-dev-install:
	docker build -t ${DOCKER_IMG_NAME} --progress tty .

docker-dev-cli:
	docker container run --rm -it --privileged -v ${PWD}:${APP_PATH} -w ${APP_PATH} ${DOCKER_IMG_NAME} bash
