#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>          
#define MAX_MULT (120)

/* Variable Global */
static PGconn * conexion;

/* Estructuras */
struct paciente {
    char * nombre;
    char * apellidop;
    char * apellidom;
    char * sexo;
    char * edad;
    char * telefono;
    char * calle;
    char * numero;
    char * ciudad;
};

struct medico {
    char * nombre;
    char * apellidop;
    char * apellidom;
    char * sexo;
    char * edad;
    char * telefono;
    char * especialidad;
};

struct consulta {
    char * idp;
    char * idm;
};

/* PROTOTIPOS */
void menu ( PGconn * );
void menu_insertar ( PGconn * );
void menu_desplegar ();
void menu_buscar ();
void consultas_unidas(int);
void executeQuery_consulta_unidas(char *, PGconn *, int );
char * query_insert_consulta_unidas(char * idp, int );
void mostrar ( int );
void paginacion_pacientes( int );
void paginacion_medicos( int tipo );
void paginacion_consultas( int tipo );
void insertar_pacientes ( struct paciente, PGconn * );
void executeQuery_pacientes ( struct paciente, PGconn * );
char * query_insert_paciente ( struct paciente );
void insertar_medicos (struct medico, PGconn * );
void executeQuery_medicos (struct medico, PGconn * ); 
char * query_insert_medico (struct medico );
void insertar_consultas ( struct consulta, PGconn * );
void executeQuery_consultas ( struct consulta, PGconn * );
char * query_insert_consultas ( struct consulta );
char * cat_puntero ( char *, char * );
char * convertir_string ( int );
int filas_tablas( int );
void do_exit_res ( PGconn *, PGresult * );
PGconn * conexion_db ();
void comprobar_estadodb ( PGconn * );
void do_exit ( PGconn * );
char * nextLine ( void );
void vacia_buffer ();

int main () {
    
    PGconn * conexion = conexion_db();

    menu(conexion);
    
    printf("\n\n");
    
    return 0;

}

void menu(PGconn * conexion) {
    int opcion = 0;
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Insertar   | 3. Buscar   |");
        printf("\n| 2. Desplegar  | 4. Salir    |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                menu_insertar(conexion);                break;
            case 2:
                menu_desplegar();                       break;
            case 3:
                menu_buscar();                          break;
            case 4:
                printf("\n\nPrograma Finalizado\n");    break;
        }
    }while (opcion != 4);
}

void menu_insertar(PGconn * conexion) {
        int opcion = 0;
        struct paciente nuevoP;
        struct medico nuevoM;
        struct consulta nuevoC;
    do {

        printf("\n|----------------------------|");
        printf("\n|         * Insertar *       |");
        printf("\n|----------------------------|");
        printf("\n| 1. Pacientes | 2. Medicos  |");
        printf("\n| 3. Consultas | 4. Salir    |");
        printf("\n|--------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                insertar_pacientes ( nuevoP, conexion );            break;
            case 2:
                insertar_medicos ( nuevoM, conexion );              break;
            case 3:
                insertar_consultas ( nuevoC, conexion );            break;
            case 4:
                printf("\n\n Salio del Menu de Consultas \n\n");    break;
        }
    }while (opcion != 4);
}

void menu_desplegar() {
    int opcion = 0;
    do {

        printf("\n|----------------------------|");
        printf("\n|        * Consultas *       |");
        printf("\n|----------------------------|");
        printf("\n| 1. Pacientes | 2. Medicos  |");
        printf("\n| 3. Consultas | 4. Salir    |");
        printf("\n|--------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                mostrar(1);                                         break;
            case 2:
                mostrar(2);                                         break;
            case 3:
                mostrar(3);                                         break;
            case 4:
                printf("\n\n Salio del Menu de Consultas \n\n");    break;
        }
    }while (opcion != 4);
}

void menu_buscar() {

    int opcion = 0;
    do {

        printf("\n|----------------------------|");
        printf("\n|          * Buscar *        |");
        printf("\n|----------------------------|");
        printf("\n| 1. Consultas del Paciente  |");
        printf("\n| 2. Consultas del Medico    |");
        printf("\n| 4. Salir                   |");
        printf("\n|--------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                consultas_unidas(1);                               break;
            case 2:
                consultas_unidas(2);                               break;
            case 3:
                printf("\n\n Salio del Menu de Consultas \n\n");   break;
        }
    }while (opcion != 3);

}

void consultas_unidas(int tipo) {
    vacia_buffer();
    if (tipo == 1) {
        printf("ID del Paciente: ");
    }
    else {
        printf("ID del Medico: ");
    }
    char * id = nextLine();

    executeQuery_consulta_unidas ( id, conexion, tipo );
}

void executeQuery_consulta_unidas(char * id, PGconn * conexion, int tipo) {

    PGresult * res = PQexec(conexion, query_insert_consulta_unidas(id, tipo));

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit_res(conexion, res);
    }

    if (PQresultStatus (res) != PGRES_TUPLES_OK) {
        printf ("No se recuperaron datos \n");
        PQclear (res);
        do_exit (conexion);
    }

    int filas = PQntuples (res);
    int i;
    int columnas = PQnfields (res);
    printf("\n%93s", "TABLA CONSULTAS DE PACIENTE");
    printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    char *name = PQfname(res, 0);
    printf("|%-4s|", name);

    name = PQfname(res, 1);
    printf("%-4s|", name);

    name = PQfname(res, 2);
    printf("%-4s|", name);

    name = PQfname(res, 3);
    printf("%-20s|", name);

    name = PQfname(res, 4);
    printf("%-20s|", name);

    name = PQfname(res, 5);
    printf("%-20s|", name);

    name = PQfname(res, 6);
    printf("%-20s|", name);

    name = PQfname(res, 7);
    printf("%-20s|", name);

    name = PQfname(res, 8);
    printf("%-20s|", name);

    name = PQfname(res, 9);
    printf("%-11s|", name);

    printf("\n");
    for (i = 0; i < filas; i ++) {
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|%-4s|%-4s|%-4s|%-20s|%-20s|%-20s|%-20s|%-20s|%-20s|%-11s|\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1)
                      , PQgetvalue(res, i, 2), PQgetvalue(res, i, 3)
                      , PQgetvalue(res, i, 4), PQgetvalue(res, i, 5)
                      , PQgetvalue(res, i, 6), PQgetvalue(res, i, 7)
                      , PQgetvalue(res, i, 8), PQgetvalue(res, i, 9));
    }

    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    PQclear(res);

}


char * query_insert_consulta_unidas(char * id, int tipo) {
  
   char * sql;
   
   if (tipo == 0) {
        sql = "SELECT * FROM consultas_paciente ('";
   } else {
        sql = "SELECT * FROM consultas_medico ('";
   }

   sql = cat_puntero(sql, id);
   sql = cat_puntero(sql, "');");
    
   return sql;
}

void mostrar (int tipo) {
    
    vacia_buffer();
    
    if (tipo == 1) {
        paginacion_pacientes(tipo);
    }
    else if (tipo == 2) {
        paginacion_medicos(tipo);
    }
    else { 
        paginacion_consultas(tipo);
    }

}

void paginacion_pacientes(int tipo) {
    printf("\n\tTotal de Resgistros %i \n", filas_tablas(tipo));

    printf("¿De Cuantos Registros Quieres Ver? ");
    char * registros = nextLine();
    printf("¿Numero de Pagina? ");
    char * pagina = nextLine();

    char * sql;
    sql = "SELECT * FROM consulta_pacientes('";
    sql = cat_puntero(sql, registros);
    sql = cat_puntero (sql, "', '");
    sql = cat_puntero (sql, pagina);
    sql = cat_puntero (sql, "');");

    PGresult * res = PQexec(conexion, sql);

    if (PQresultStatus (res) != PGRES_TUPLES_OK) {
        printf ("No se recuperaron datos \n");
        PQclear (res);
        do_exit (conexion);
    }

    int i;
    int filas = PQntuples(res);
    int columnas = PQnfields (res);
    printf("\n%80s", "TABLA PACIENTES");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    char *name = PQfname(res, 0);
    printf("|%-4s|", name);

    name = PQfname(res, 1);
    printf("%-20s|", name);

    name = PQfname(res, 2);
    printf("%-18s|", name);
    
    name = PQfname(res, 3);
    printf("%-20s|", name);

    name = PQfname(res, 4);
    printf("%-6s|", name);

    name = PQfname(res, 5);
    printf("%-5s|", name);

    name = PQfname(res, 6);
    printf("%-18s|", name);

    name = PQfname(res, 7);
    printf("%-22s|", name);

    name = PQfname(res, 8);
    printf("%-6s|", name);

    name = PQfname(res, 9);
    printf("%-20s|", name);

    printf("\n");

    for (i = 0; i < filas; i ++) {
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|%-4s|%-20s|%-18s|%-20s|%-6s|%-5s|%-18s|%-22s|%-6s|%-20s|\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1)
                      , PQgetvalue(res, i, 2), PQgetvalue(res, i, 3)
                      , PQgetvalue(res, i, 4), PQgetvalue(res, i, 5)
                      , PQgetvalue(res, i, 6), PQgetvalue(res, i, 7)
                      , PQgetvalue(res, i, 8), PQgetvalue(res, i, 9));
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    PQclear (res);

}

void paginacion_medicos( int tipo ) {
    printf("\n\tTotal de Resgistros %i \n", filas_tablas(tipo));

    printf("¿De Cuantos Registros Quieres Ver? ");
    char * registros = nextLine();
    printf("¿Numero de Pagina? ");
    char * pagina = nextLine();

    char * sql;
    sql = "SELECT * FROM consulta_medicos('";
    sql = cat_puntero(sql, registros);
    sql = cat_puntero (sql, "', '");
    sql = cat_puntero (sql, pagina);
    sql = cat_puntero (sql, "');");

    PGresult * res = PQexec(conexion, sql);

    if (PQresultStatus (res) != PGRES_TUPLES_OK) {
        printf ("No se recuperaron datos \n");
        PQclear (res);
        do_exit (conexion);
    }

    int i;
    int filas = PQntuples(res);
    int columnas = PQnfields (res);
    printf("\n%70s", "TABLA MEDICOS");
    printf("\n-------------------------------------------------------------------------------------------------------------------------------\n");

    char *name = PQfname(res, 0);
    printf("|%-4s|", name);

    name = PQfname(res, 1);
    printf("%-20s|", name);

    name = PQfname(res, 2);
    printf("%-18s|", name);

    name = PQfname(res, 3);
    printf("%-20s|", name);

    name = PQfname(res, 4);
    printf("%-6s|", name);

    name = PQfname(res, 5);
    printf("%-5s|", name);

    name = PQfname(res, 6);
    printf("%-20s|", name);

    name = PQfname(res, 7);
    printf("%-25s|", name);

    printf("\n");

    for (i = 0; i < filas; i ++) {
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|%-4s|%-20s|%-18s|%-20s|%-6s|%-5s|%-20s|%-26s|\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1)
                      , PQgetvalue(res, i, 2), PQgetvalue(res, i, 3)
                      , PQgetvalue(res, i, 4), PQgetvalue(res, i, 5)
                      , PQgetvalue(res, i, 6), PQgetvalue(res, i, 7));
    }

    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    PQclear (res);

}

void paginacion_consultas( int tipo ) {
    printf("\n\tTotal de Resgistros %i \n", filas_tablas(tipo));

    printf("¿De Cuantos Registros Quieres Ver? ");
    char * registros = nextLine();
    printf("¿Numero de Pagina? ");
    char * pagina = nextLine();

    char * sql;
    sql = "SELECT * FROM consulta_consultas('";
    sql = cat_puntero(sql, registros);
    sql = cat_puntero (sql, "', '");
    sql = cat_puntero (sql, pagina);
    sql = cat_puntero (sql, "');");

    PGresult * res = PQexec(conexion, sql);

    if (PQresultStatus (res) != PGRES_TUPLES_OK) {
        printf ("No se recuperaron datos \n");
        PQclear (res);
        do_exit (conexion);
    }

    int i;
    int filas = PQntuples(res);
    int columnas = PQnfields (res);
    printf("\n%21s", "TABLA CONSULTAS");
    printf("\n----------------------------\n");

    char *name = PQfname(res, 0);
    printf("|%-4s|", name);

    name = PQfname(res, 1);
    printf("%-4s|", name);

    name = PQfname(res, 2);
    printf("%-4s|", name);

    name = PQfname(res, 3);
    printf("%-11s|", name);

    printf("\n");

    for (i = 0; i < filas; i ++) {
        printf("----------------------------\n");
        printf("|%-4s|%-4s|%-4s|%-11s|\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1)
                               , PQgetvalue(res, i, 2), PQgetvalue(res, i, 3));
    }

    printf("----------------------------\n");

    PQclear (res);
}

void insertar_pacientes (struct paciente nuevo,PGconn * conexion) {

    vacia_buffer();

    printf("Nombre: ");
    nuevo.nombre = nextLine();

    printf("Apellido Paterno: ");
    nuevo.apellidop = nextLine();

    printf("Apellido Materno: ");
    nuevo.apellidom = nextLine();

    printf("Sexo: ");
    nuevo.sexo = nextLine();

    printf("Edad: ");
    nuevo.edad = nextLine();
    
    printf("Telefono: ");
    nuevo.telefono = nextLine();
    
    printf("Calle: ");
    nuevo.calle = nextLine();

    printf("Numero: ");
    nuevo.numero = nextLine();

    printf("Ciudad: ");
    nuevo.ciudad = nextLine();
   
    executeQuery_pacientes(nuevo, conexion);
}

void executeQuery_pacientes(struct paciente nuevo, PGconn * conexion) {

    PGresult * res = PQexec(conexion, query_insert_paciente(nuevo));

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit_res(conexion, res);
    }

    PQclear(res);
    printf("\n Paciente agregado \n");
}


char * query_insert_paciente(struct paciente nuevo) {

   char * sql = "SELECT pacientes ('";

   sql = cat_puntero(sql, nuevo.nombre);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.apellidop);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.apellidom);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.sexo);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.edad);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.telefono);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.calle);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.numero);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.ciudad);
   sql = cat_puntero(sql, "');");
  
   return sql;
}

void insertar_medicos (struct medico nuevo,PGconn * conexion) {

    vacia_buffer();

    printf("Nombre: ");
    nuevo.nombre = nextLine();

    printf("Apellido Paterno: ");
    nuevo.apellidop = nextLine();


    printf("Apellido Materno: ");
    nuevo.apellidom = nextLine();

    printf("Sexo: ");
    nuevo.sexo = nextLine();

    printf("Edad: ");
    nuevo.edad = nextLine();

    printf("Telefono: ");
    nuevo.telefono = nextLine();

    printf("Especialidad: ");
    nuevo.especialidad = nextLine();

    executeQuery_medicos(nuevo, conexion);

}

void executeQuery_medicos(struct medico nuevo, PGconn * conexion) {

    PGresult * res = PQexec(conexion, query_insert_medico(nuevo));

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit_res(conexion, res);
    }

    PQclear(res);
    printf("\n Medico agregado \n");
}

char * query_insert_medico(struct medico nuevo) {

   char * sql = "SELECT medicos ('";

   sql = cat_puntero(sql, nuevo.nombre);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.apellidop);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.apellidom);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.sexo);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.edad);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.telefono);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.especialidad);
   sql = cat_puntero(sql, "');");

   return sql;

}

void insertar_consultas (struct consulta nuevo, PGconn * conexion) {

    vacia_buffer();

    printf("ID Paciente: ");
    nuevo.idp = nextLine();

    printf("ID Medico: ");
    nuevo.idm = nextLine();

    executeQuery_consultas(nuevo, conexion);

}

void executeQuery_consultas(struct consulta nuevo, PGconn * conexion) {

    PGresult * res = PQexec(conexion, query_insert_consultas(nuevo));

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit_res(conexion, res);
    }

    PQclear(res);
    printf("\n Consulta agregada \n");
}

char * query_insert_consultas(struct consulta nuevo) {

   char * sql = "SELECT consultas ('";

   sql = cat_puntero(sql, nuevo.idp);
   sql = cat_puntero(sql, "', '");
   sql = cat_puntero(sql, nuevo.idm);
   sql = cat_puntero(sql, "');");

   return sql;

}

char * cat_puntero(char * p1, char * p2) {
    int i = 0;
    char * p_concatenado = malloc(strlen(p1) + strlen(p2) + 1);

    while(*p1){
      p_concatenado[i++]=*p1++;
    }
    while(*p2){
      p_concatenado[i++]=*p2++;
    }
    p_concatenado[i]='\0';

    return p_concatenado;
}

char * convertir_string(int edad) {

    char string[3];

    sprintf(string, "%d", edad);

    char * cadena = (char *) malloc(sizeof(char));

    cadena = string;

    return cadena;
}

int filas_tablas (int tipo) {

    PGresult * res;
    if (tipo == 1) {
        res = PQexec(conexion, "SELECT * FROM pacientes");
        printf("Pacientes");
    }
    else if (tipo == 2) {
        res = PQexec(conexion, "SELECT * FROM medicos");
    }
    else {
        res = PQexec(conexion, "SELECT * FROM consultas"); 
    }
    return PQntuples (res);

}

PGconn * conexion_db() {

    if (conexion == NULL) {
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=hospitalu user = postgres password=Duran2001");
    }

    comprobar_estadodb(conexion);

    return conexion;
}

void do_exit_res(PGconn *conexion, PGresult *res) {

   fprintf(stderr, "%s\n", PQerrorMessage(conexion));

    PQclear(res);
    PQfinish(conexion);
    exit(1);
 }

void comprobar_estadodb(PGconn * conexion) {

    if (PQstatus (conexion) == CONNECTION_BAD) {
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
        do_exit (conexion);
    }

}

void do_exit(PGconn * conexion) {

    PQfinish(conexion);
    exit(1);

}

char * nextLine(void) {
  int chr = 0, mult = 0, len = 0;
  char *_c = NULL;

  while (1) {
    chr = fgetc(stdin);

    if (chr == EOF || chr == '\n') /* Detente solo si terminamos o si es final de linea */
      break;

    if (mult >= len) { /* pide más memoria si es necesario. */
      char *tmp = realloc(_c, mult + MAX_MULT);
      if (!tmp) /* si fall al pedir memoria, entonces detente ahora */
        break;
      _c = tmp, mult += MAX_MULT;
    }

    _c[len++] = chr; /* finalmente asigna. */
   }

  if (len)
    _c[len] = 0; /* pon el caracter nulo al final si no es NULL nuestra cadena */
  return _c; /* finalmente, devuelvela. */
}

void vacia_buffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}