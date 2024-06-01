function modificarEnlacesConConsulta(enlaceId) {
    var urlString = window.location.href;
    var result = Module.ccall('obtenerQueryString', 'string', ['string'], [urlString]);
    var enlace = document.getElementById(enlaceId);

    if (enlace) {
        // Limpiar el atributo href antes de agregar la nueva consulta
        enlace.href = enlace.href.split('?')[0];
        // Agregar la nueva parte de la consulta
    
        var form = Module.ccall('elegirQuizzForm', 'string', ['string','string'], [result,enlace.id]);
        enlace.href=form;
        return enlace.href += "?" + result;
    } 
}

function pulsarIconos(idEnlace) {
    var enlace = document.getElementById(idEnlace);
    enlace.addEventListener("click", function(event) {
        event.preventDefault(); // Evitar el comportamiento predeterminado del enlace
        var result = modificarEnlacesConConsulta(idEnlace);
        window.location.href = result;
    });
}
document.addEventListener("DOMContentLoaded", function() {
    pulsarIconos('enlaceCreativo');
    pulsarIconos('enlaceQuizz');
})