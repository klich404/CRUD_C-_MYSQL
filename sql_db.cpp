#include <iostream>
#include "sql_db.h"

using namespace std;

sql_db :: sql_db (char *server, char *user, char * pass, char *db)
{
    this->server = server;
    this->user = user;
    this->pass = pass;
    this->db = db;

    //initialice MySQL
    if(!(objData = mysql_init(0))) {
        cout << "Error: can't create the objData object." << endl;
        exit(1); 
    }

    //there must be a root user with access to the pass
    if(!mysql_real_connect(objData, this->server, this->user, this->pass, this->db, 0, NULL, 0)) {
        cout << "imposible connect with the mysql server in the port "
             << MYSQL_PORT << " ERROR: " << mysql_error(objData) << endl;
        mysql_close(objData);
        rewind(stdin);
        exit(2);
    }
}

sql_db :: ~sql_db()
{
    this->sql_close();
}

//close connection
void sql_db :: sql_close()
{
    mysql_close(this->objData);
}

MYSQL_RES *sql_db :: run_sql(char *sql)
{
    //reconnect the connection if it is lost
    if(mysql_ping(objData)) {
        cout << "Error: lose conection" << endl;
        this->sql_close();
    }

    //run the sql query
    if(mysql_query(objData, sql)) {
        cout << "Error: " << mysql_error(objData) << endl;
        this->sql_close();
        rewind(stdin);
        exit(2);
    }

    return  mysql_store_result(objData);
}

//return the number of rows
int sql_db :: n_rows(MYSQL_RES *res)
{
    return mysql_num_rows(res);
}

//return the rows affected
int sql_db :: affected_rows()
{
    return mysql_affected_rows(this->objData);
}

//return the number of columns
int sql_db :: n_columns(MYSQL_RES *res)
{
    return mysql_num_fields(res);
}

//return the name of the column
const char *sql_db :: column_name(MYSQL_RES *res, int index)
{
    return mysql_fetch_field_direct(res, index)->name;
}

//return the length of the column
int sql_db :: column_long(MYSQL_RES *res, int index)
{
    return mysql_fetch_field_direct(res, index)->length;
}

//return the default column value
const char *sql_db :: column_value(MYSQL_RES *res, int index)
{
    MYSQL_FIELD *col = mysql_fetch_field_direct(res, index);
    return col->def ? col->def : "NULL";
}

//get the result row
MYSQL_ROW sql_db :: get_row(MYSQL_RES *res)
{
    return mysql_fetch_row(res);
}

// set the result row in an index
void sql_db :: set_row(MYSQL_RES *res, int index)
{
    mysql_data_seek(res, index);
}

//get the id of the last consult
unsigned long sql_db :: last_id()
{
    return (unsigned long)mysql_insert_id(this->objData);
}
