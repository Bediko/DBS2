#include <stdlib.h>
#include <libpq-fe.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "db.h"

extern PGconn *db;
extern PGresult *res;
extern string user,password,host,dbname;
extern bool deletedb;

PGconn *db;
PGresult *res;
string user,password,host,dbname;
bool deletedb=false;


int db_login(const string &user, const string &password, const string &host, const string &dbname){
  string conn="user="+user+" password="+password+" host="+host+" dbname="+dbname;
  db=PQconnectdb(conn.c_str());
  if(PQstatus(db) != CONNECTION_OK){
    return 1;
  }
  return 0;
}

void db_logout(){
  PQfinish(db);
}

int db_begin(){
  res=PQexec(db,"BEGIN");
  if(PQresultStatus(res) != PGRES_COMMAND_OK){
    printf("BEGIN failed.");
    PQclear(res);
    return 1;
  }
  return 0;
}

int db_commit(){
  res=PQexec(db,"COMMIT");
  if(PQresultStatus(res) != PGRES_COMMAND_OK){
    printf("COMMIT failed.");
    PQclear(res);
    return 1;
  }
  return 0;
}

int db_rollback(){
  res=PQexec(db,"ROLLBACK");
  if(PQresultStatus(res) != PGRES_COMMAND_OK){
    printf("ROLLBACK failed.");
    PQclear(res);
    return 1;
  }
  return 0;
}

int db_mtnrpresent(const string &mtnr){
  string statement="SELECT mtnr FROM student where mtnr=\'"+mtnr+"\'";
  res=PQexec(db,statement.c_str());
  if(PQresultStatus(res) != PGRES_TUPLES_OK){
    printf("Fehler bei Überprüfung von Matrikelnr %s\n",mtnr.c_str());
    printf("%s",PQresultErrorMessage(res));
    PQclear(res);
    return -1;
  }
  else if(PQntuples(res)==0){
    PQclear(res);
    return 0;
  }
  else{
    PQclear(res);
    return 1;
  }
}

int db_insert(const string &mtnr, const string &vorname, const string &nachname, const string &geburt){
  db_begin();
  string statement="INSERT INTO student VALUES(\'"+mtnr+"\',\'"+vorname+"\',\'"+nachname+"\',\'"+geburt+"\')";
  if(db_mtnrpresent(mtnr)==0){
    res=PQexec(db,statement.c_str());
    if(PQresultStatus(res) != PGRES_COMMAND_OK){
      printf("%s",PQresultErrorMessage(res));
      db_rollback();
      return 1;
    }
    db_commit();
    return 0;
  }
  else{
    db_rollback();
    return 1;
  }
}

int db_delete(){
  db_begin();
  string statement="DELETE FROM student";
  res=PQexec(db,statement.c_str());
  if(PQresultStatus(res) != PGRES_COMMAND_OK){
    printf("%s",PQresultErrorMessage(res));
    db_rollback();
    return 1;
  }
  db_commit();
  return 0;
}


bool test(){
  bool ok=true;
  if(db_login("bediko","test","localhost","bediko")){ //anpassen auf lokale Datenbank
    printf("db_login error\n");
    ok=false;
  }
  if(db_begin()){
    printf("db_begin error\n");
    ok=false;
    }
  if(db_commit()){
    printf("db_commit error\n");
    ok=false;
  }
  if(db_begin()){
    printf("db_begin error\n");
    ok=false;
  }
  if(db_rollback()){
    printf("db_rollback error\n");
    ok=false;
  }
  if(db_mtnrpresent("100000")){
    printf("db_mtnpresent error\n");
    ok=false;
  }
  if(db_insert("100000","Rainer","Zufall","21.12.2112")){
    printf("db_insert error inserting new data\n");
    ok=false;
  }
  if(!db_mtnrpresent("100000")){
    printf("db_mtnpresent error duplicates\n");
    ok=false;
  }

  if(!db_insert("100000","Rainer","Zufall","21.12.2112")){
    printf("db_insert error inserting double data\n");
    ok=false;
  }
  if(db_delete()){
    printf("db_delete error\n");
    ok=false;
  }
  db_logout();
  return ok;
}