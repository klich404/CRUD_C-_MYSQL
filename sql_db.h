#ifndef SQLDB_H
#define SQLDB_H

#include <iostream>
#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>

class sql_db {

    private:
        char *server, *user, *pass, *db;
        MYSQL *objData;

    public:
        sql_db (char *server, char *user, char * pass, char *db);
        ~sql_db();
        void sql_close();
        MYSQL_RES *run_sql(char *sql);
        int n_rows(MYSQL_RES *res);
        int affected_rows();
        int n_columns(MYSQL_RES *res);
        const char *column_name(MYSQL_RES *res, int index);
        int column_long(MYSQL_RES *res, int index);
        const char *column_value(MYSQL_RES *res, int index);
        MYSQL_ROW get_row(MYSQL_RES *res);
        void set_row(MYSQL_RES *res, int index);
        unsigned long last_id();
};

#endif
