`sudo apt install mysql-server`
`sudo mysql_secure_installation`
Set root password

`sudo mysql -u root -p`
Enter password

`CREATE DATABASE forklift;`

`CREATE USER 'frontend'@'%' IDENTIFIED BY '**password**';`
`CREATE USER 'backend'@'%' IDENTIFIED BY '**password**';`
`GRANT SELECT ON forklift.* TO 'frontend'@'%' WITH GRANT OPTION;`
`GRANT ALL PRIVILEGES ON forklift.* TO 'backend'@'%' WITH GRANT OPTION;`
`FLUSH PRIVILEGES;`
```
CREATE TABLE `forklift`.`device` (
 `macaddress` VARCHAR(12) NOT NULL,
 `name` VARCHAR(32) NOT NULL,
 `location` VARCHAR(32) NOT NULL,
 PRIMARY KEY (`macaddress`));
```
```
CREATE TABLE `forklift`.`log` (
  `macaddress` VARCHAR(12) NOT NULL,
  `load` TINYINT(1) NOT NULL,
  `start` DATETIME NOT NULL,
  `end` DATETIME NOT NULL,
  PRIMARY KEY (`macaddress`));
```

Exit MySQL

`sudo nano /etc/mysql/mariadb.conf.d/50-server.cnf`
cange `bind-address = 127.0.0.1` to `bind-address = 0.0.0.0`
