
// Función para dividir cada letra en un span
function animarTexto(selector) {
    var elementosTextoAnimado = document.querySelectorAll(selector);

    elementosTextoAnimado.forEach(function(elemento) {
        var texto = elemento.innerText;
        elemento.innerHTML = '';

        for (var i = 0; i < texto.length; i++) {
            var letra = texto.charAt(i);

            // Crear un span para cada letra
            var letraSpan = document.createElement("span");
            letraSpan.classList.add("letra-animada");
            letraSpan.textContent = letra;
            letraSpan.style.animationDelay = (i * 0.15) + "s";

            // Verificar si agregar un salto de línea
            if (letra === ' ' || letra === '\n' || (i > 0 && letraSpan.offsetLeft >= elemento.offsetWidth)) {
                elemento.appendChild(document.createElement("br"));
            }

            // Agregar la letra al elemento padre
            elemento.appendChild(letraSpan);
        }
    });
}



document.addEventListener("DOMContentLoaded", function() {
    animarTexto(".texto-animado");

});