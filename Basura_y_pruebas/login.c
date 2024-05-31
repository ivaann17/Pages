#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Definición de constantes
#define DATABASE_NAME "users.db"

// Prototipos de funciones
sqlite3 *open_database();
int execute_query_login(sqlite3 *db, const char *query, const char *param1, const char *param2);
int execute_query_registro(sqlite3 *db, const char *query, const char *param1, const char *param2, const char *param3);

// Función de apertura de la base de datos
sqlite3 *open_database() {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se puede acceder a la base de datos: %s.\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    return db;
}

// Función para ejecutar una consulta
int execute_query_login(sqlite3 *db, const char *query, const char *param1, const char *param2) {
    int rc;
    sqlite3_stmt *stmt;

    // Consulta preparada
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    // Bind de parámetros
    rc = sqlite3_bind_text(stmt, 1, param1, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al vincular el primer parámetro: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    rc = sqlite3_bind_text(stmt, 2, param2, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al vincular el segundo parámetro: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    // Ejecutar la consulta preparada
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    } else {
        sqlite3_finalize(stmt);
        return 0;
    }
}

int execute_query_registro(sqlite3 *db, const char *query, const char *param1, const char *param2, const char *param3) {
    int rc;
    sqlite3_stmt *stmt;

    // Consulta preparada
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    // Bind de parámetros
    rc = sqlite3_bind_text(stmt, 1, param1, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al vincular el primer parámetro: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    rc = sqlite3_bind_text(stmt, 2, param2, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al vincular el segundo parámetro: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    rc = sqlite3_bind_text(stmt, 3, param3, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al vincular el segundo parámetro: %s.\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    // Ejecutar la consulta preparada
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    } else {
        sqlite3_finalize(stmt);
        return 0;
    }
}

// Función de login que verifica el usuario y la contraseña
int login(const char *username, const char *password) {
    sqlite3 *db;
    int rc;

    db = open_database();
    if (db == NULL) {
        return 1;
    }

    printf("Intento de inicio de sesión - Usuario: %s, Contraseña: %s\n", username, password);

    // Ejecutar la consulta
    int result = execute_query_login(db, "SELECT * FROM users WHERE correo=? AND pass=?", username, password);

    // Cerrar la base de datos
    sqlite3_close(db);

    return result;
}

int registro(const char *username, const char *email, const char *password) {
    sqlite3 *db;
    int rc;

    db = open_database();
    if (db == NULL) {
        return 1;
    }

    printf("Intento de registro: - Usuario: %s, Email: %s, Contraseña: %s\n", username, email, password);

    // Ejecutar la consulta
    int result = execute_query_registro(db, "INSERT INTO users (nombre, correo, pass) VALUES (?, ?, ?);", username, email, password);

    // Cerrar la base de datos
    sqlite3_close(db);

    return result;
}

// Función principal
int main() {
    printf("WebAssembly module loaded\n");
    return 0;
}
