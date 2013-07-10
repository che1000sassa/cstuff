/*
 * dbtools.c
 *
 *  Created on: 23.05.2013
 *      Author: cke
 */
#include <stdio.h>
#include <stdlib.h>
#include "dbtools.h"


/* Bricht bei Fehler (mysql_error != 0) das Programm ab. */
void check_error(MYSQL *handle) {
	if (mysql_errno(handle) != 0) {
		fprintf(stderr, "Fehler: %s\n", mysql_error(handle));
		exit(EXIT_FAILURE);
	}
}


/* Baut eine Verbindung zum Datenbankserver auf.*/
MYSQL *msql_connect(void) {
	MYSQL *handle;
	handle = mysql_init(NULL);
	check_error(handle);
	mysql_real_connect(handle, "localhost", "root", NULL, NULL, 0, NULL, 0);
	check_error(handle);
	return handle;
}

/* Serververbindung wieder schließen und den Speicher für die
 * Struktur MYSQL wieder freigeben */
void msql_disconnect(MYSQL *handle) {
	mysql_close(handle);
}
/* Falls die Datenbank bei der Funktion verbinden() nicht
 * angegeben wurde oder Sie die Datenbank wechseln wollen, dann
 * verwenden Sie diese Funktion. */
void db_waehlen(MYSQL *handle, char *db) {
	mysql_select_db(handle, db);
	check_error(handle);
}

void insert_eprofile(MYSQL *handle, EPROFILE *eprof) {
   unsigned long  anzahl_reihen;
   unsigned int i;
   MYSQL_ROW  row;
   MYSQL_RES  *mysql_res;

   char *query, *string;
   char *select = "SELECT * FROM eanl WHERE anlage='";
   string = malloc(strlen(eprof)+2);
   strcpy(string,eprof);
   strcat(string, "'");
   query = malloc(strlen(select)+strlen(string)+1);
   strcpy(query, select);
   strcat(query, string);

   /* jetzt die Anfrage an den Datenbankserver */
   mysql_real_query(handle, query, strlen(query));
   check_error(handle);
   /* Daten der Anfrage abholen */
   mysql_res = mysql_store_result(handle);
   check_error(handle);
   /* Anzahl der gefundenen Datensätze ermitteln */
   anzahl_reihen = (unsigned long) mysql_num_rows (mysql_res);
   printf ("Anzahl gefunden: %lu\n\n", anzahl_reihen);
   /* gefundenen Datensatz bzw. Datensätze ausgeben */
   while ((row = mysql_fetch_row (mysql_res)) != NULL) {
      /* Einzelne Spalten der Zeile ausgeben */
      for (i = 0;  i < mysql_num_fields(mysql_res);  i ++)
         printf ("%s ",row[i]);
      printf("\n");
   }
   /* Speicherplatz wieder freigeben */
   mysql_free_result(mysql_res);
   free(string);
   free(query);
}


void eanl_display(MYSQL *handle, char *name) {
   unsigned long  anzahl_reihen;
   unsigned int i;
   MYSQL_ROW  row;
   MYSQL_RES  *mysql_res;

   char *query, *string;
   char *select = "SELECT * FROM eanl WHERE anlage='";
   string = malloc(strlen(name)+2);
   strcpy(string,name);
   strcat(string, "'");
   query = malloc(strlen(select)+strlen(string)+1);
   strcpy(query, select);
   strcat(query, string);

   /* jetzt die Anfrage an den Datenbankserver */
   mysql_real_query(handle, query, strlen(query));
   check_error(handle);
   /* Daten der Anfrage abholen */
   mysql_res = mysql_store_result(handle);
   check_error(handle);
   /* Anzahl der gefundenen Datensätze ermitteln */
   anzahl_reihen = (unsigned long) mysql_num_rows (mysql_res);
   printf ("Anzahl gefunden: %lu\n\n", anzahl_reihen);
   /* gefundenen Datensatz bzw. Datensätze ausgeben */
   while ((row = mysql_fetch_row (mysql_res)) != NULL) {
      /* Einzelne Spalten der Zeile ausgeben */
      for (i = 0;  i < mysql_num_fields(mysql_res);  i ++)
         printf ("%s ",row[i]);
      printf("\n");
   }
   /* Speicherplatz wieder freigeben */
   mysql_free_result(mysql_res);
   free(string);
   free(query);
}

void wrichter_display(MYSQL *handle) {
   unsigned long  anzahl_reihen;
   unsigned int i;
   MYSQL_ROW  row;
   MYSQL_RES  *mysql_res;

   char *query;
   char *select = "SELECT * FROM wrichter";
   query = malloc(strlen(select)+1);
   strcpy(query, select);

   /* jetzt die Anfrage an den Datenbankserver */
   mysql_real_query(handle, query, strlen(query));
   check_error(handle);
   /* Daten der Anfrage abholen */
   mysql_res = mysql_store_result(handle);
   check_error(handle);
   /* Anzahl der gefundenen Datensätze ermitteln */
   anzahl_reihen = (unsigned long) mysql_num_rows (mysql_res);
   printf ("Anzahl gefunden: %lu\n\n", anzahl_reihen);
   /* gefundenen Datensatz bzw. Datensätze ausgeben */
   while ((row = mysql_fetch_row (mysql_res)) != NULL) {
      /* Einzelne Spalten der Zeile ausgeben */
      for (i = 0;  i < mysql_num_fields(mysql_res);  i ++)
         printf ("%s ",row[i]);
      printf("\n");
   }
   /* Speicherplatz wieder freigeben */
   mysql_free_result(mysql_res);
   free(query);
}
