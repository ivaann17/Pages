#include <stdio.h>
#include <string.h>
#include <emscripten/emscripten.h>

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