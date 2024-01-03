MySQL root password: ```RootPasswd```<br />

Database name: ```dayz_old```<br />
MySQL user name: ```user```<br />
MySQL user password: ```passwd```<br />


Main server source file: ```DayZ+.pwn```<br />
Server port: ```7780```<br />


Install:

1. Build MySQL server: <br />
```$ docker-compose build mariadb```<br />
2. Create database:<br />
```$ mysql -h 127.0.0.1 -u root -p```<br />
#input password: ```RootPasswd```<br />
#run into MySQL command line:<br />
```> create database dayz_old;```<br />
```> GRANT ALL PRIVILEGES ON dayz_old.* TO 'user'@'%' IDENTIFIED BY 'passwd';```<br />
3. Init database:<br />
```$ cd docker/old_server```<br />
```$ ./reload_db.sh```<br />
#input password: ```passwd```<br />
4. Build and run server:<br />
```$ ./rebuild.sh```<br />
