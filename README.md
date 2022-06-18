# CRUD_C++_MYSQL
## Create, read, update and delete system, building with c++ and mysql.
This program allows you to manage a database in which you can insert new information, edit it, read it or delete it according to your needs.

## Requeriments 📋
```sh
g++   == 9.4.0
mysql == 8.0.29
mysql-client
```

## Use 💻
you need to have a mysql database (you can run the `scrtip.sql` file to get a test one), then you can make the respective changes to your mysql server in the `crud.cpp` file (lines 17-20) and in the same file They can also change the query fields to those of your database (not needed if you use database `script.cpp`).

When everything is adequate we must compile the program
`g++ -o crud crud.cpp sql_db.cpp sql_db.h -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient`
This will leave us an executable file called `crud`, we just have to execute it `./crud`.

You can now interact with your crud system.

## Authors 🖋
**Carlos Cruz** - [klich404](https://github.com/klich404)
