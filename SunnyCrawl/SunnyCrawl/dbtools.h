/*
 * dbtools.h
 *
 *  Created on: 16.04.2013
 *      Author: cke
 */

#ifndef MYSQL_BASE_H_
#define MYSQL_BASE_H_

#if defined __WIN32__ || _MSC_VER
#include <winsock2.h>
#include <mysql.h>
#else
#include <mysql.h>
#endif

typedef char tim_t[6]; //'HH:MM'
typedef char dat_t[11]; //'YYYY-MM-DD'

struct eprofile {
	char anlage[2];
	char sn[11];
	dat_t dat; //'YYYY-MM-DD'
	tim_t tim; //'HH:MM'
	char kw[10];
};
typedef struct eprofile EPROFILE;


/* Bricht bei Fehler (mysql_error != 0) das Programm ab. */
extern void check_error(MYSQL *mysql);

/* Baut eine Verbindung zum Datenbankserver auf.*/
extern MYSQL * msql_connect(void);

/* Serververbindung wieder schließen und den Speicher für die
 * Struktur MYSQL wieder freigeben */
extern void msql_disconnect(MYSQL *handle);

/* Falls die Datenbank bei der Funktion verbinden() nicht
 * angegeben wurde oder Sie die Datenbank wechseln wollen, dann
 * verwenden Sie diese Funktion. */
extern void db_waehlen(MYSQL *handle, char *db);

extern void insert_eprofile(MYSQL *handle, EPROFILE *eprof);

extern void eanl_display(MYSQL *handle, char *name);

extern void wrichter_display(MYSQL *handle);

#endif /* MYSQL_BASE_H_ */
