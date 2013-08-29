#include <stdio.h>
#include <mysql.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "c.h"
#define STRING_SIZE 1024

/*
MYSQL_TYPE_TIMESTAMP    TIMESTAMP field
MYSQL_TYPE_DATE         DATE field
MYSQL_TYPE_TIME         TIME field
MYSQL_TYPE_DATETIME     DATETIME field
*/

#define DROP_SAMPLE_TABLE "DROP TABLE IF EXISTS SMALL111"
#define CREATE_SAMPLE_TABLE "CREATE TABLE SMALL111(col1 bigint, col2 int, col21 varchar(40), col22 varchar(40), col3 SMALLINT, col4 TIMESTAMP, col5 datetime, col6 date, col7 time)"
#define INSERT_SAMPLE "INSERT INTO SMALL111(col1,col2,col3, col4, col5, col6, col7, col21, col22) VALUES(10,2,1,1,1,1,1,1,1)"
#define INSERT_SAMPLE1 "INSERT INTO SMALL111(col1,col2,col3, col4, col5, col6, col7, col21, col22) VALUES(2,2,1,1,1,1,1,1,1)"

int main (int argc, char *argv[]) {

    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    my_bool reconnect = 0;
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);

    //CONN(0);
    mysql_real_connect(mysql, "10.250.7.14", "test", "test", "test", 3306, NULL, 0);

    mysql_query(mysql, DROP_SAMPLE_TABLE);
    mysql_query(mysql, CREATE_SAMPLE_TABLE);
    mysql_query(mysql, INSERT_SAMPLE);
    mysql_query(mysql, INSERT_SAMPLE1);

    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind[1];
    MYSQL_BIND    bResult[1];
    unsigned long length[1];
    my_ulonglong  affected_rows;
    int           param_count;
    short         small_data;
    //long int_data;
    char int_data[100] = "abc";
    char          str_data[STRING_SIZE];
    unsigned long str_length;
    my_bool       is_null[1];

    is_null[0] = 0;
    stmt = mysql_stmt_init(mysql);
    if (!stmt)
    {
      fprintf(stderr, " mysql_stmt_init(), out of memory\n");
      exit(0);
    }

    #define SELECT_EXAMPLE "select '111'" 

    mysql_query(mysql, SELECT_EXAMPLE);

    result = mysql_store_result(mysql);
    while(mysql_fetch_row(result));

    mysql_stmt_prepare(stmt, SELECT_EXAMPLE, strlen(SELECT_EXAMPLE));

    mysql_stmt_execute(stmt);

while(!mysql_stmt_fetch(stmt)) {
    printf("aaaa\n");
}
    sleep(3);
}
