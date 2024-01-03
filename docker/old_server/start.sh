#!/bin/bash

cd /home/mini/DockerSAMP/old_server

docker-compose up -d old_server
docker-compose ps

exit 0
