
function bloquear_url(){
    if (!sessionStorage.getItem("logged")){
        window.location = "index.html";
    }
}


// Función para dividir cada letra en un span
function animarTexto(selector) {
    var elementosTextoAnimado = document.querySelectorAll(selector);

    elementosTextoAnimado.forEach(function(elemento) {
        var texto = elemento.innerText;
        elemento.innerHTML = '';
        for (var i = 0; i < texto.length; i++) {
            var span = document.createElement("span");
            span.classList.add("letra-animada");
            span.textContent = texto.charAt(i);
            span.style.animationDelay = (i * 0.15) + "s";
            elemento.appendChild(span);
        }
    });
}

function agregarConsultaAEnlaces() {
    // Obtener la parte de la consulta de la URL actual
    var queryParte = window.location.search;

    // Obtener los elementos de anclaje
    var enlaceCreativo = document.getElementById('enlaceCreativo');

    // Verificar si el elemento de anclaje existe
    if (enlaceCreativo) {
        // Agregar la parte de la consulta a la URL de destino de cada enlace
        enlaceCreativo.href += queryParte;
    }
}


document.addEventListener("DOMContentLoaded", function() {
    bloquear_url();
    animarTexto(".texto-animado");

});


