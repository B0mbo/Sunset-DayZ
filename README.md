Sunset DayZ v0.6.3

MySQL root password: ```RootPasswd```<br />

Database name: ```dayz_old```<br />
MySQL user name: ```user```<br />
MySQL user password: ```passwd```<br />


Main server source file: ```DayZ+.pwn```<br />
Server port: ```7780```<br />


Install:

1. Build MySQL server: <br />
```$ docker-compose build mariadb```<br />
```$ docker compose up -d mariadb```<br />
2. Create database:<br />
```$ docker exec -it $(docker ps | grep "0.0.0.0:3306" | awk -F " " '{print $1}') bash```<br />
#run commands into docker mariadb container:<br />
```# mysql -h 127.0.0.1 -u root -p```<br />
#input password: ```RootPasswd```<br />
```> create database dayz_old;```<br />
```> GRANT ALL PRIVILEGES ON dayz_old.* TO 'user'@'%' IDENTIFIED BY 'passwd';```<br />
```> QUIT```<br />
3. Init database (into mariadb docker container):<br />
```# cd /old_server```<br />
```# ./reload_db.sh```<br />
```# Ctrl+D```<br />
#input password: ```passwd```<br />
4. Build and run server:<br />
```$ ./rebuild.sh```<br />
