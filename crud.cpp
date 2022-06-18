#include <iostream>
#include <cstring>
#include "sql_db.h"

using namespace std;

//define the structure
struct employee
{
    char name[50];
    int age;
    char position[50];
};

typedef struct employee Employee;

//mysql config
char server[] = ""; //fill me up
char user[] = ""; //fill me up
char pass[] = ""; //fill me up
char db[] = ""; //fill me up
//global object
sql_db obj_mysql(server, user, pass, db);

//methods prototypes
void get_into(), insert(Employee info), search();
void modify(), update(Employee info, int id), del(); 
void sort(), show(), pause();
char menu(void);

//main function
int main(int argc, char *argv[])
{
    char op;

    for (;;)
    {
        fflush(stdin);
        switch (op = menu())
        {
        case '1':
            get_into();
            pause();
            break;
        case '2':
            search();
            pause();
            break;
        case '3':
            modify();
            pause();
            break;
        case '4':
            del();
            pause();
            break;
        case '5':
            show();
            pause();
            break;
        case '6':
            break;
        default:
            cout << "Invalid option";
            pause();
            break;
        }

        if(op == '6') {
            break;
        }
    }

    return 0;
}

//get info for insert
void get_into() 
{
    Employee info;

    cout << "Enter name: ";
    cin >> info.name;
    cout << "Enter age: ";
    cin >> info.age;
    cout << "Enter position: ";
    cin >> info.position;
    insert(info);
    cout << "Employee successfully entered";
}

//create a new employee in table
void insert(Employee info)
{
    char *consult;
    char query[] = "INSERT INTO employees (NAME, AGE, POSITION) VALUES (\'%s\', \'%d\', \'%s\')";

    consult = new char[strlen(query) + sizeof(Employee) - sizeof(int)];
    sprintf(consult, query, info.name, info.age, info.position);

    obj_mysql.run_sql(consult);
}

//search a specific employee in table
void search()
{
    char name[50];
    char *consult;
    char query[] = "SELECT * FROM employees WHERE NAME=\'%s\'";
    MYSQL_RES *res;
    MYSQL_ROW row;

    cout << "Enter a name: ";
    cin >> name;

    consult = new char[strlen(query) + strlen(name)];
    sprintf(consult, query, name);
    res = obj_mysql.run_sql(consult);

    if(obj_mysql.affected_rows() > 0) {
        row = obj_mysql.get_row(res);
        cout << "ID: " << row[0] << endl;
        cout << "NAME: " << row[1] << endl;
        cout << "AGE: " << row[2] << endl;
        cout << "POSITION: " << row[3] << endl;
    } else {
        cout << "Employee not found" << endl;
    }
}

//search employee to modify and get the new info
void modify()
{
    char name[50];
    char *consult;
    char *temp;
    int id;
    char query[] = "SELECT * FROM employees WHERE NAME=\'%s\'";
    MYSQL_RES *res;
    MYSQL_ROW row;
    Employee info;

    cout << "Enter employee name to modify: ";
    cin >> name;

    consult = new char[strlen(query) + strlen(name)];
    sprintf(consult, query, name);
    res = obj_mysql.run_sql(consult);

    if(obj_mysql.affected_rows() > 0)
    {
        row = obj_mysql.get_row(res);
        id = atoi(row[0]);
        cout << "Enter new name: ";
        cin >> info.name;
        cout << "Enter new age: ";
        cin >> info.age;
        cout << "Enter new position: ";
        cin >> info.position;
        update(info, id);
        cout << "Data updated successfully" << endl;
    } else {
        cout << "Employee not found" << endl;
    }
}

//update the select employee
void update(Employee info, int id)
{
    char name[50];
    char *consult;
    char query[] = "UPDATE employees SET NAME=\'%s\', AGE=\'%d\', POSITION=\'%s\' WHERE ID=\'%d\'";

    consult = new char[strlen(query) + strlen(name)];
    sprintf(consult, query, info.name, info.age, info.position, id);
    obj_mysql.run_sql(consult);
}

//delete the select employee
void del()
{
    char name[50];
    char *consult;
    char *temp;
    char search_query[] = "SELECT * FROM employees WHERE NAME=\'%s\'";
    char delete_query[] = "DELETE FROM employees WHERE ID=%d";
    MYSQL_RES *res;
    MYSQL_ROW row;
    Employee info;

    cout << "Enter name to delete: ";
    cin >> name;

    consult = new char[strlen(search_query) + strlen(name)];
    sprintf(consult, search_query, name);
    res = obj_mysql.run_sql(consult);

    if(obj_mysql.affected_rows() > 0)
    {   
        row = obj_mysql.get_row(res);
        temp = row[0];
        int id = atoi(temp);
        consult = new char[strlen(delete_query) + sizeof(int)];
        sprintf(consult, delete_query, id);
        obj_mysql.run_sql(consult);
        cout << "Data deleted successfully" << endl;
    } else {
        cout << "Employee not found" << endl;
    }
}

//ignore this function, is not implemented
void sort()
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    int rows, columns;
    char query[] = "SELECT * FROM employees ORDER BY NAME";

    res = obj_mysql.run_sql(query);
    rows = obj_mysql.n_rows(res);
    columns = obj_mysql.n_columns(res);

    cout << "--- LIST OF EMPLOYEES (" << rows << ") ---" << endl;

    for (int i = 0; i < columns; i++)
        cout << obj_mysql.column_name(res, i) << " - ";
    cout << endl;

    while (row = obj_mysql.get_row(res))
    {
        for(int i = 0; i < columns; i++)
        {
            cout << row[i] << ", ";
        }
        cout << endl;
    }
    cout << "Records have been sorted by: name" << endl;
}

//show all the employees in the table
void show()
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    int rows, columns;
    char query[] = "SELECT * FROM employees";

    res = obj_mysql.run_sql(query);
    rows = obj_mysql.n_rows(res);
    columns = obj_mysql.n_columns(res);

    cout << "--- LIST OF EMPLOYEES (" << rows << ") ---" << endl;

    for (int i = 0; i < columns; i++)
        cout << obj_mysql.column_name(res, i) << " - ";
    cout << endl;

    while (row = obj_mysql.get_row(res))
    {
        for(int i = 0; i < columns; i++)
        {
            cout << row[i] << ", ";
        }
        cout << endl;
    }
}

//show the menu and get the new instrucction to execute
char menu(void)
{
    char c;
    cout << "(1)CREATE" << endl;
    cout << "(2)SEARCH" << endl;
    cout << "(3)MODIFY" << endl;
    cout << "(4)DELETE" << endl;
    cout << "(5)READ LIST" << endl;
    cout << "(6)EXIT" << endl;

    cin >> c;
    return c;
}

void pause()
{
    cout << endl;
    cout << endl;
}
