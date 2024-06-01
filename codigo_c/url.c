#include <stdio.h>
#include <string.h>
#include <emscripten/emscripten.h>

char* obtenerQueryString(const char *url);
char* elegirQuizzForm(char* result, char* enlaceId);


EMSCRIPTEN_KEEPALIVE
char* obtenerQueryString(const char *url) {
    // Encontrar la posición del caracter '?'
    char *queryStart = strchr(url, '?');
    if (queryStart != NULL) {
        // Retornar la parte de la URL después del '?'
        return queryStart + 1;
    } else {
        // No hay '?' en la URL, retornar una cadena vacía
        return "";
    }
}

char* elegirQuizzForm(char* result, char* enlaceId) {
    // Declaramos una variable para almacenar el href resultante
    char* href = NULL;

    // Comparamos el ID del enlace
    if (strcmp(enlaceId, "enlaceQuizz") == 0) {
        // Asignamos el href según el resultado
        if (strcmp(result, "lang=java") == 0) {
            href = "menuJ.html"; // Href para Java
        } else if (strcmp(result, "lang=c") == 0) {
            href = "menuC.html"; // Href para C
        } else if (strcmp(result, "lang=cpp") == 0) {
            href = "menuCpp.html"; // Href para C++
        } else if (strcmp(result, "lang=python") == 0) {
            href = "menuP.html"; // Href para Python
        }
    }
    else {
        href = "compi.html";
    }

    // Devolvemos el href resultante
    return href;
}