#ifndef GESTOR_BBDD_H
#define GESTOR_BBDD_H

#include <mysql/mysql.h>

// Definición de constantes para la conexión
extern const char *host;
extern const char *user;
extern const char *passw;
extern const char *dbName;

// Función para inicializar la conexión a la base de datos
MYSQL* inicializar_conexion();

// Función para conectar a la base de datos
void conectar_base_datos(MYSQL *conn);

// Función para crear la tabla si no existe
void crear_tabla(MYSQL *conn, const char *query);

// Función para insertar datos en la tabla
void insertar_datos(MYSQL *conn, const char *query);

// Función para ejecutar cualquier consulta y obtener resultados
MYSQL_RES* ejecutar_query(MYSQL *conn, const char *query);

// Función para imprimir los resultados de la consulta
void imprimir_resultados(MYSQL_RES *res);

#endif /* MYSQL_FUNCTIONS_H */
