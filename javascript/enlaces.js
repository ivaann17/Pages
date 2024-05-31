function modificarEnlacesConConsulta() {
    var urlString = window.location.href;
    var result = Module.ccall('obtenerQueryString', 'string', ['string'], [urlString]);
    var enlaceCreativo = document.getElementById('enlaceCreativo');

    if (enlaceCreativo) {
        // Limpiar el atributo href antes de agregar la nueva consulta
        enlaceCreativo.href = enlaceCreativo.href.split('?')[0];
        // Agregar la nueva parte de la consulta
        return enlaceCreativo.href += "?" + result;
    }
}

document.addEventListener("DOMContentLoaded", function() {
    var enlaceCreativo = document.getElementById('enlaceCreativo');
    if (enlaceCreativo) {
        enlaceCreativo.addEventListener("click", function(event) {
            event.preventDefault(); // Evitar el comportamiento predeterminado del enlace
            var result = modificarEnlacesConConsulta();
            window.location.href = result;

            // Después de navegar, la variable result se liberará automáticamente.
        });
    }
});
