#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
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
void inicio ();
void menu_admin ();
void menu_usuario ();
void menu_insertar ();
void menu_consultar ();
void menu_buscar ();
void admin_autenticacion ();
char * query_autenticacion( char *, char * );
void menu_actualizar ();
void menu_eliminar();
void actualizar ( int );
void query_actualizar ( char *,int, int );
char * columna ( int, int );
void eliminar ( int );
int menu_actualizar_columna ( char *, int );
void query_eliminar ( char *, int );
int verificar_id ( char *, int );
void consultas_unidas ( int );
void executeQuery_consulta_unidas (char *, int );
char * query_insert_consulta_unidas (char *, int );
void mostrar ( int );
void paginacion_pacientes ( int );
void paginacion_medicos ( int );
void paginacion_consultas ( int );
void insertar_pacientes ( struct paciente );
void executeQuery_pacientes ( struct paciente );
char * query_insert_paciente ( struct paciente );
void insertar_medicos ( struct medico );
void executeQuery_medicos ( struct medico );
char * query_insert_medico (struct medico );
void insertar_consultas ( struct consulta);
void executeQuery_consultas ( struct consulta);
char * query_insert_consultas ( struct consulta );
void mostrar_especialidad();
char * cat_punteros(char * sql, int cantidad, ...);
char * cat_puntero (char * p1, char * p2);
char * convertir_string ( int );
int filas_tablas ( int );
void do_exit_res ( PGresult * );
PGconn * conexion_db ();
void comprobar_estadodb ();
void do_exit ( PGconn * );
void comprobar_query ( PGresult * , char *);
char * nextLine ( void );
void vacia_buffer ();

int main () {

    conexion = conexion_db();

    inicio ();
    
    printf( "\n\n" );

    do_exit(conexion);

    return 0;

}

void inicio () {

    int opcion = 0;
    do {

        printf("\n|-----------------|");
        printf("\n|    * Incio *    |");
        printf("\n|-----------------|");
        printf("\n| 1. Administrador|");
        printf("\n| 2. Usuario      |");
        printf("\n| 3. Salir        |");
        printf("\n|-----------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                admin_autenticacion();                  break;
            case 2:
                menu_usuario ();                        break;
            case 3:
                printf("\n\nPrograma Finalizado\n");    break;
            default:
                printf("\nOpcion no disponible\n");     break;
        }
    }while (opcion != 3);

}

void menu_admin () {
    int opcion = 0;
    do {
        printf("\n|------------------------------|");
        printf("\n|            * Menu *          |");
        printf("\n|------------------------------|");
        printf("\n| 1. Insertar   | 3. Buscar    |");
        printf("\n| 2. Consultar  | 4. Actualizar|");
        printf("\n| 5. Eliminar   | 6. Salir     |");
        printf("\n|---------------|--------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                menu_insertar();                        break;
            case 2:
                menu_consultar();                       break;
            case 3:
                menu_buscar();                          break;
            case 4:
                menu_actualizar();                      break;
            case 5:
                menu_eliminar();                        break;
            default:
                printf("\nOpcion no disponible\n");     break;
        }
    } while (opcion != 6);
}

void menu_usuario() {
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
                menu_consultar();                       break;
            case 3:
                menu_buscar();                          break;
            case 4:
                printf("\n\nPrograma Finalizado\n");    break;
            default:
                printf("\nOpcion no disponible\n");     break;
        }
    }while (opcion != 4);
}


void menu_insertar() {
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
                insertar_pacientes ( nuevoP );                      break;
            case 2:
                insertar_medicos ( nuevoM );                        break;
            case 3:
                insertar_consultas ( nuevoC );                      break;
            case 4:
                printf("\n\n Salio del Menu de Consultas \n\n");    break;
            default:
                printf("\nOpcion no disponible\n");                 break;
        }
    }while (opcion != 4);
}

void menu_consultar() {
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
                mostrar( 1 );                                         break;
            case 2:
                mostrar( 2 );                                         break;
            case 3:
                mostrar( 3 );                                         break;
            case 4:
                printf("\n\n Salio del Menu de Consultas \n\n");      break;
            default:
                printf("\nOpcion no disponible\n");                   break;
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
        printf("\n| 3. Salir                   |");
        printf("\n|--------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                consultas_unidas( 1 );                               break;
            case 2:
                consultas_unidas( 2 );                               break;
            case 3:
                printf("\n\n Salio del Menu de Consultas \n\n");     break;
            default:
                printf("\nOpcion no disponible\n");                  break;
        }
    }while (opcion != 3);

}

void menu_actualizar () {
    int opcion = 0;
    do {

        printf("\n|----------------------------|");
        printf("\n|        * Actualizar *      |");
        printf("\n|----------------------------|");
        printf("\n| 1. Pacientes | 2. Medicos  |");
        printf("\n| 3. Consultas | 4. Salir    |");
        printf("\n|--------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                actualizar ( 1 );                                   break;
            case 2:
                actualizar ( 2 );                                   break;
            case 3:
                actualizar ( 3 );                                   break;
            case 4:
                printf("\n\n Salio del Menu de Actualizar \n\n");   break;
            default:
                printf("\nOpcion no disponible\n");                 break;
        }
    }while (opcion != 4);
}

void menu_eliminar() {

    int opcion = 0;
    do {

        printf("\n|----------------------------|");
        printf("\n|         * Eliminar *       |");
        printf("\n|----------------------------|");
        printf("\n| 1. Pacientes | 2. Medicos  |");
        printf("\n| 3. Consultas | 4. Salir    |");
        printf("\n|--------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                eliminar ( 1 );                                     break;
            case 2:
                eliminar ( 2 );                                     break;
            case 3:
                eliminar ( 3 );                                     break;
            case 4:
                printf("\n\n Salio del Menu de Actualizar \n\n");   break;
            default:
                printf("\nOpcion no disponible\n");                 break;
        }
    }while (opcion != 4);

}

void admin_autenticacion () {
    vacia_buffer();
    printf("Usuario: ");
    char * user = nextLine();

    printf("Contraseña: ");
    char * pass = nextLine();

    PGresult * res = PQexec( conexion, query_autenticacion( user, pass ) );

    int columnas = PQntuples ( res );

    if (columnas > 0) {
        menu_admin();
    } else {
        printf("Fallo de Autenticación");
        inicio();
    }

    PQclear (res);
}

char * query_autenticacion(char * user, char * pass) {
    char * sql = "SELECT * FROM autenticacion ('";

    sql = cat_punteros(sql, 4, user, "', '", pass, "');");

    return sql;
}

void actualizar(int tipo) {
    vacia_buffer();

    printf("ID: ");
    char * id = nextLine();

    int filas = verificar_id ( id, tipo );

    if (filas > 0) {
       int respuesta = menu_actualizar_columna ( id, tipo );
       query_actualizar ( id, tipo, respuesta );
    }

}

void eliminar (int tipo) {
    vacia_buffer();

    printf("ID: ");
    char * id = nextLine();

    int filas = verificar_id ( id, tipo );

    if (filas > 0) {
       query_eliminar ( id, tipo );
    }

}

int menu_actualizar_columna (char * id, int tipo) {
    PGresult * res;
    if (tipo == 1) {
        res = PQexec( conexion, "SELECT * FROM pacientes WHERE 1<>1" );
    }
    if (tipo == 2) {
        res = PQexec( conexion, "SELECT * FROM medicos WHERE 1<>1" );
    }
    if (tipo == 3) {
        res = PQexec( conexion, "SELECT * FROM consultas WHERE 1<>1" );
    }

    int columnas = PQnfields (res);
    if (tipo != 3) {
        printf("-------------------------------\n");
    } else {
        printf("----------------\n");
    }
    for (int i=1; i <= columnas; i++) {

        char * name = PQfname(res, i-1);

        if(i != 1 && i != 2 && tipo == 1){
            printf("| %-1i. %-10s", i-1, name);
        } else if (i == 2 && tipo == 1) {
            printf("|          %-1i. %-10s      ", i-1, name);
        }

        if (tipo == 2 && i != 1) {
            printf("|%-1i. %-11s", i-1, name);
        }

        if (tipo == 3 && i != 1){
            printf("|%-1i. %-11s", i-1, name);
        }

        if (i%2 == 0 && tipo == 1) {
            printf("%-5c\n", '|');
        }

        if (i%2 == 1 && i != 2 && tipo == 2 && i != 1) {
            printf("%-6c\n", '|');
        } else if (i%2 == 1 && tipo == 2 && i != 1){
            printf("%-6c", '|');
        }

        if (tipo == 3 && i != 1) {
            printf("%-6c\n", '|');
        }

    }
    if (tipo != 3) {
        printf("-------------------------------\n");
    } else {
        printf("----------------\n");
    }

    int respuesta = 0;

    printf("¿Que va actualizar? ");
    scanf("%d", &respuesta);

    PQclear (res);

    return respuesta;
}

void query_eliminar (char * id, int _tabla) {

        char * tabla = " ";
        if (_tabla == 1) {
            tabla = "pacientes";
        } else if (_tabla == 2) {
            tabla = "medicos";
        } else {
            tabla = "consultas";
        }

        char * sql = "SELECT eliminar ('";
        sql = cat_punteros(sql, 4, id, "', '", tabla, "');");

        PGresult * res =  PQexec(conexion, sql);

        PQclear (res);
}

void query_actualizar (char * id, int _tabla, int respuesta) {

    vacia_buffer();

        char * tabla = " ";
        if (_tabla == 1) {
            tabla = "pacientes";
        } else if (_tabla == 2) {
            tabla = "medicos";
        } else {
            tabla = "consultas";
        }

        char * column = columna (respuesta, _tabla);

        char * nuevo = " ";

        if (strcmp(column, "fecha")) {
            printf("Nuevo: ");
            nuevo = nextLine();
        }

        char * sql = "SELECT actualizar ('";
        sql = cat_punteros(sql, 8, column, "', '", nuevo, "', '", id, "', '", tabla, "');");
        
        PGresult * res =  PQexec(conexion, sql);

        comprobar_query(res, "UPDATE");
}

char * columna (int _columna, int tabla) {
    char * columna;
    switch (tabla) {
        case 1:
            switch (_columna) {
                case 1: columna = "nombre"; break;
                case 2: columna = "apellidop"; break;
                case 3: columna = "apellidom"; break;
                case 4: columna = "sexo"; break;
                case 5: columna = "edad"; break;
                case 6: columna = "telefono"; break;
                case 7: columna = "calle"; break;
                case 8: columna = "numero"; break;
                case 9: columna = "ciudad"; break;
            }
            break;
        case 2:
            switch (_columna) {
                case 1: columna = "nombre"; break;
                case 2: columna = "apellidop"; break;
                case 3: columna = "apellidom"; break;
                case 4: columna = "sexo"; break;
                case 5: columna = "edad"; break;
                case 6: columna = "telefono"; break;
            }
            break;
        case 3:
            switch (_columna) {
                case 1: columna =  "idp"; break;
                case 2: columna =  "idm"; break;
                case 3: columna = "fecha"; break;
            }
            break;
    }
    return columna;
}

int verificar_id (char * id, int tipo) {

    char * sql = "SELECT * FROM ";

    if (tipo == 1) {
        sql = cat_puntero(sql, "pacientes ");
    } else if (tipo == 2) {
        sql = cat_puntero(sql, "medicos ");
    } else if (tipo == 3) {
        sql = cat_puntero(sql, "consultas ");
    }

    sql = cat_punteros (sql, 3, "WHERE id = ", id, "::INT;");

    PGresult * res = PQexec(conexion, sql);

    int filas = PQntuples(res);

    PQclear(res);

    return filas;
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

    executeQuery_consulta_unidas ( id, tipo );
}

void executeQuery_consulta_unidas(char * id, int tipo) {

    PGresult * res = PQexec(conexion, query_insert_consulta_unidas(id, tipo));

    int filas = PQntuples (res);
    int i;
    int columnas = PQnfields (res);
    if (tipo == 1)
        printf("\n%93s", "TABLA CONSULTAS DE PACIENTE");
    else
        printf("\n%93s", "TABLA CONSULTAS DE MEDICO");
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

   sql = cat_punteros(sql, 2, id, "');");

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
    sql = "SELECT * FROM consulta_pacientes ('";
    sql = cat_punteros(sql, 4, registros, "', '", pagina, "');");

    PGresult * res = PQexec(conexion, sql);

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
    sql = "SELECT * FROM consulta_medicos ('";
    sql = cat_punteros(sql, 4, registros, "', '", pagina, "');");

    PGresult * res = PQexec(conexion, sql);

    int i;
    int filas = PQntuples(res);
    int columnas = PQnfields (res);
    printf("\n%65s", "TABLA MEDICOS");
    printf("\n--------------------------------------------------------------------------------------------------------------------------\n");

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
    printf("%-20s|", name);

    printf("\n");

    for (i = 0; i < filas; i ++) {
        printf("--------------------------------------------------------------------------------------------------------------------------\n");
        printf("|%-4s|%-20s|%-18s|%-20s|%-6s|%-5s|%-20s|%-21s|\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1)
                      , PQgetvalue(res, i, 2), PQgetvalue(res, i, 3)
                      , PQgetvalue(res, i, 4), PQgetvalue(res, i, 5)
                      , PQgetvalue(res, i, 6), PQgetvalue(res, i, 7));
    }

    printf("--------------------------------------------------------------------------------------------------------------------------\n");

    PQclear (res);

}

void paginacion_consultas( int tipo ) {
    printf("\n\tTotal de Resgistros %i \n", filas_tablas(tipo));

    printf("¿De Cuantos Registros Quieres Ver? ");
    char * registros = nextLine();
    printf("¿Numero de Pagina? ");
    char * pagina = nextLine();

    char * sql;
    sql = "SELECT * FROM consulta_consultas ('";
    sql = cat_punteros(sql, 4, registros, "', '", pagina, "');");

    PGresult * res = PQexec(conexion, sql);

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

void insertar_pacientes (struct paciente nuevo) {

    vacia_buffer();

    printf("Nombre: ");
    nuevo.nombre = nextLine();

    printf("Apellido Paterno: ");
    nuevo.apellidop = nextLine();

    printf("Apellido Materno: ");
    nuevo.apellidom = nextLine();

    printf("Sexo[HM]: ");
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

    executeQuery_pacientes(nuevo);
}

void executeQuery_pacientes(struct paciente nuevo) {

    PGresult * res = PQexec(conexion, query_insert_paciente(nuevo));

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit_res(res);
    }

    PQclear(res);
    printf("\n Paciente agregado \n");
}


char * query_insert_paciente(struct paciente nuevo) {

   char * sql = "SELECT pacientes ('";

   sql = cat_punteros(sql, 18, nuevo.nombre, "', '", nuevo.apellidop
                        , "', '", nuevo.apellidom, "', '", nuevo.sexo
                        , "', '", nuevo.edad, "', '", nuevo.telefono
                        , "', '", nuevo.calle, "', '", nuevo.numero
                        , "', '", nuevo.ciudad, "');");

   return sql;
}

void insertar_medicos (struct medico nuevo) {

    vacia_buffer();

    printf("Nombre: ");
    nuevo.nombre = nextLine();

    printf("Apellido Paterno: ");
    nuevo.apellidop = nextLine();


    printf("Apellido Materno: ");
    nuevo.apellidom = nextLine();

    printf("Sexo [HM]: ");
    nuevo.sexo = nextLine();

    printf("Edad: ");
    nuevo.edad = nextLine();

    printf("Telefono: ");
    nuevo.telefono = nextLine();

    printf("\n");
    mostrar_especialidad();
    printf("\n");

    printf("Especialidad [id]: ");
    nuevo.especialidad = nextLine();

    executeQuery_medicos(nuevo);

}

void executeQuery_medicos(struct medico nuevo) {

    PGresult * res = PQexec(conexion, "BEGIN");

    PQclear(res);
    
    res = PQexec(conexion, query_insert_medico(nuevo));

    res = PQexec (conexion, "SELECT id FROM medicos ORDER BY id DESC LIMIT 1;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        res = PQexec(conexion, "ROLLBACK");
    }
    
    char * idmedico = PQgetvalue(res, 0, 0);

    printf("%s", idmedico);

    char * sql = "SELECT especialidad_medicos ('";

    sql = cat_punteros (sql, 4, idmedico, "', '", nuevo.especialidad, "');");

    res = PQexec (conexion, sql);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        res = PQexec(conexion, "ROLLBACK");
    }

    res = PQexec(conexion, "COMMIT");

    PQclear(res);

    printf("\n Medico agregado \n");

}

char * query_insert_medico(struct medico nuevo) {

   char * sql = "SELECT medicos ('";

   sql = cat_punteros(sql, 12, nuevo.nombre, "', '", nuevo.apellidop
                             , "', '", nuevo.apellidom, "', '", nuevo.sexo
                             , "', '", nuevo.edad, "', '", nuevo.telefono, "');");

   return sql;

}

void insertar_consultas (struct consulta nuevo) {

    vacia_buffer();

    printf("ID Paciente: ");
    nuevo.idp = nextLine();

    printf("ID Medico: ");
    nuevo.idm = nextLine();

    executeQuery_consultas(nuevo);

}

void executeQuery_consultas(struct consulta nuevo) {

    PGresult * res = PQexec(conexion, query_insert_consultas(nuevo));

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit_res(res);
    }

    PQclear(res);
    printf("\n Consulta agregada \n");
}

char * query_insert_consultas(struct consulta nuevo) {

   char * sql = "SELECT consultas ('";

   sql = cat_punteros(sql, 4, nuevo.idp, "', '", nuevo.idm, "');");

   return sql;
}

char * cat_punteros(char * sql, int cantidad, ...) {
   
    va_list lista_argumentos;
    va_start (lista_argumentos, cantidad);
    char * p_concatenado = " ";

    for (int i = 0; i < cantidad; i++) {
        sql = cat_puntero(sql, va_arg(lista_argumentos, char *));
        p_concatenado=cat_puntero(sql, "");
    }

    va_end(lista_argumentos);

    return p_concatenado;
}

void mostrar_especialidad() {
    
    char * sql = "SELECT * FROM especialidad ORDER BY id ASC;";

    PGresult * res = PQexec(conexion, sql);
    
    int filas = PQntuples(res);

    int columnas = PQnfields (res);
    printf("\n    %s", "TABLA ESPECIALIDAD");
    printf("\n--------------------------\n");

    char *name = PQfname(res, 0);
    printf("|%-4s|", name);

    name = PQfname(res, 1);
    printf("%-19s|", name);

    printf("\n");

    for (int i = 0; i < filas; i ++) {
        printf("--------------------------\n");
        printf("|%-4s|%-20s|\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1));
    }

    printf("--------------------------\n");

    PQclear (res);

}

char * cat_puntero (char * p1, char * p2) {
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

void comprobar_query (PGresult * res, char * msj) {

     if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("Fallo, %s no realizado", msj);
     }

    PQclear(res);

}

void do_exit_res(PGresult * res) {

   fprintf(stderr, "%s\n", PQerrorMessage(conexion));

    PQclear(res);
    exit(1);
 }

void comprobar_estadodb() {

    if (PQstatus (conexion) == CONNECTION_BAD) {
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
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
