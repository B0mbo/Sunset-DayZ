MySQL root password: RootPasswd

Database name: dayz_old<br />
MySQL user name: user<br />
MySQL user password: passwd<br />


Main server source file: DayZ+.pwn<br />


Install:

1. Build MySql server: <br />
```$ docker-compose build mariadb```<br />
2. Create database:<br />
```$ mysql -h 127.0.0.1 -u root -p```<br />
#input password: "RootPasswd"<br />
#run into MySql command line:<br />
```> create database dayz_old;```<br />
```> GRANT ALL PRIVILEGES ON dayz_old.* TO 'user'@'%' IDENTIFIED BY 'passwd';```<br />
3. Init database:<br />
```$ cd docker/old_server```<br />
```$ ./reload_db.sh```<br />
4. Build server:<br />
```$ ./rebuild.sh```<br />
