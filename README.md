MySQL root password: RootPasswd

Database name: dayz_old
MySQL user name: user
MySQL user password: passwd


Main server source file: DayZ+.pwn


Install:

1. Build MySql server: 
```$ docker-compose build mariadb```
2. Create database:
```$ mysql -h 127.0.0.1 -u root -p```
#input password: "RootPasswd"
#run into MySql command line:
```> create database dayz_old;
> GRANT ALL PRIVILEGES ON dayz_old.* TO 'user'@'%' IDENTIFIED BY 'passwd';```
3. Init database:
```$ cd docker/old_server 
$ ./reload_db.sh```
4. Build server:
```$ ./rebuild.sh```
