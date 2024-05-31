#include <stdio.h>
#include <stdlib.h>
#include "gestor_bbdd.h"
#include <mysql/mysql.h> // Incluye la biblioteca MySQL Connector/C

// Definición de constantes para la conexión
const char *host = "b4p9vmi6pnykocbc3ovr-mysql.services.clever-cloud.com";
const char *user = "utyquf5ripc86mvl";
const char *passw = "8Pmblr0ysW8eW4Nnn4Ot";
const char *dbName = "b4p9vmi6pnykocbc3ovr";

// Función para inicializar la conexión a la base de datos
MYSQL* inicializar_conexion() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar la conexión: %s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

// Función para conectar a la base de datos
void conectar_base_datos(MYSQL *conn) {
    if (mysql_real_connect(conn, host, user, passw, dbName, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
}

// Función para crear la tabla si no existe
void crear_tabla(MYSQL *conn, const char *query) {
    const char *create_table_query = query;
    if (mysql_query(conn, create_table_query)) {
        fprintf(stderr, "Error al crear la tabla: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
}

// Función para insertar datos en la tabla
void insertar_datos(MYSQL *conn, const char *query) {
    const char *insert_query = query;
    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "Error al insertar datos en la tabla: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
}

// Función para ejecutar la consulta SELECT y obtener resultados
MYSQL_RES* ejecutar_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    MYSQL_RES *res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_use_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return res;
}

// Función para imprimir los resultados de la consulta
void imprimir_resultados(MYSQL_RES *res) {
    MYSQL_ROW row;
    unsigned int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);

    // Imprimir los nombres de las columnas
    printf("Resultados de la consulta:\n");

    // Imprimir las filas
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (unsigned int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
}

// Función principal
/*int main() {
    MYSQL *conn = inicializar_conexion();
    conectar_base_datos(conn);
    //crear_tabla(conn, ""CREATE TABLE IF NOT EXISTS login (id INT AUTO_INCREMENT PRIMARY KEY, nombre VARCHAR(255) UNIQUE, email VARCHAR(255) UNIQUE, pass VARCHAR(255))";");
    //insertar_datos(conn, "INSERT INTO login (nombre, email, pass) VALUES ('Ejemplo1', 'email@ejemplo.com', 'password')");

    MYSQL_RES *res = ejecutar_query(conn, "SELECT * FROM login");
    imprimir_resultados(res);

    // Liberar la memoria y cerrar la conexión
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
*/