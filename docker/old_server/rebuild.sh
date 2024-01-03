#!/bin/bash

cd /home/mini/DockerSAMP/old_server
rm ./server_data.tar.gz
tar -I pigz -cf server_data.tar.gz server_data

docker-compose stop old_server
docker-compose build old_server
docker-compose up -d old_server

docker system prune -f

docker-compose ps

exit 0
