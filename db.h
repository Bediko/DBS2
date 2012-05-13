//
// DBS-Praktikum Aufgabe 2
//    Header abstraktes DB-Interface
//
// Christoph Dalitz
// Hochschule Niederrhein
// 2012/03/13
//

#ifndef DB_H
#define DB_H

#include <string>

using namespace std;

extern PGconn *db;
extern PGresult *res;
extern string user,password,host,dbname;
extern bool deletedb;


// Datenbank-Login
// rc: 0 = ok, 1 = error
int db_login(const string &user, const string &password, const string &host, const string &dbname);

// Datenbank-Logout
void db_logout();

// Transaktionsbefehle
// rc: 0 = ok, 1 = error
int db_begin();
int db_commit();
int db_rollback();

// Matrikelnummer schon vorhanden
// rc: 0 = noch nicht da, 1 = schon da, -1 = error
int db_mtnrpresent(const string &mtnr);

// Einfuegen Datensatz
// rc: 0 = ok, 1 = error
int db_insert(const string &mtnr, const string &vorname, const string &nachname, const string &geburt);

// Loeschen des kompletten Tabelleninhalts
// rc: 0 = ok, 1 = error
int db_delete();

#endif
