// ANIMACIONES
function ver_form_olvidado_Click() {
    var contenedorLogin = document.getElementById('form-login');
    var contenedorOlvidado = document.getElementById('form-olvidado');

    document.getElementById('olvidar').addEventListener('click', function(event) {
        event.preventDefault();
        
        contenedorLogin.classList.add('fade-out');
        contenedorLogin.addEventListener('transitionend', function handleTransitionEnd() {
            contenedorLogin.removeEventListener('transitionend', handleTransitionEnd);
            
            contenedorLogin.style.display = 'none';
            contenedorOlvidado.style.display = 'flex';
            contenedorLogin.classList.remove('fade-out');
        });
    });
}


function ver_form_registrar_Click() {
    var contenedorLogin = document.getElementById('form-login');
    var contenedorRegistro = document.getElementById('form-registro');

    document.getElementById('registrar').addEventListener('click', function(event) {
        event.preventDefault();
        
        contenedorLogin.classList.add('fade-out');
        contenedorLogin.addEventListener('transitionend', function handleTransitionEnd() {
            contenedorLogin.removeEventListener('transitionend', handleTransitionEnd);
            
            contenedorLogin.style.display = 'none';
            contenedorRegistro.style.display = 'flex';
            contenedorLogin.classList.remove('fade-out');
        });
    });
}

function ver_form_login_Click() {
    var contenedorRegistro = document.getElementById('form-registro');
    var contenedorLogin = document.getElementById('form-login');

    document.getElementById('login').addEventListener('click', function(event) {
        event.preventDefault();
        
        contenedorRegistro.classList.add('fade-out');
        contenedorRegistro.addEventListener('transitionend', function handleTransitionEnd() {
            contenedorRegistro.removeEventListener('transitionend', handleTransitionEnd);
            
            contenedorRegistro.style.display = 'none';
            contenedorLogin.style.display = 'flex';
            contenedorRegistro.classList.remove('fade-out');
        });
    });
}

function animacion_exito(formularioId, siguientePag) {
    var contenedorFormulario = document.getElementById(formularioId);
    if (contenedorFormulario) {
        contenedorFormulario.classList.add('success');

        // Agregar un listener para detectar el final de la animación
        contenedorFormulario.addEventListener('transitionend', function() {
            // Una vez que la transición haya terminado, ocultar el formulario
            contenedorFormulario.style.display = 'none';
            window.location.href = siguientePag;
        });
        setTimeout(function() {
            // Eliminar la clase de éxito después de 1 segundo
            contenedorFormulario.classList.remove('success');
        }, 1000);
    } else {
        console.error('Error: No se encontró el contenedor del formulario con el ID', formularioId);
    }
}


function animacion_error(formularioId, contraInputId, labelEmailId, labelPassId, labelUserId) {
    var contenedorFormulario = document.getElementById(formularioId);
    if (contenedorFormulario) {
        contenedorFormulario.classList.add('shake'); // Agrega la clase shake para indicar un error

        // Obtener los elementos del formulario
        var inputPass = document.getElementById(contraInputId);
        var lblEmail = document.getElementById(labelEmailId);
        var lblPass = document.getElementById(labelPassId);

        setTimeout(function() {
            inputPass.value = '';
            lblEmail.style.color = 'red';  
            lblPass.style.color = 'red';
            if (labelUserId) { // Verifica si labelUserId no es null ni undefined
                var lblUser = document.getElementById(labelUserId);
                if (lblUser) { // Verifica si lblUser existe antes de intentar cambiar su estilo
                    lblUser.style.color = 'red';
                }
            }
            contenedorFormulario.classList.remove('shake'); // Elimina la clase shake después de 1 segundo
        }, 1000);
    } else {
        console.error('Error: No se encontró el contenedor del formulario con el ID', formularioId);
    }
}




// FUNCIONES PHP PARA BASE DE DATOS

function comprobar_login() {
    const formLogin = document.getElementById("form-log");
    const btnAcceder = document.getElementById("btn_acceder");
    const email = document.getElementById("email");
    const password = document.getElementById("password");


    btnAcceder.addEventListener('click', event => {
        event.preventDefault();
        
        if (email.value.trim() === "" || password.value.trim() === "") {
            animacion_error("form-login","password","lblEmail","lblContra", null);
        }

        else {

        const form = new FormData(formLogin);
        form.append("funcion", "solicitud_login"); // Cambiado de 'accion' a 'funcion'

        fetch("php/bbdd.php", {
            method: "POST",
            body: form
        })
        .then(response => response.text())
        .then(text => {
            // Procesar la respuesta del script PHP
            let respuesta = text.split(',');
            if (respuesta[0] === "0") {
                animacion_error("form-login","password","lblEmail","lblContra", null);
            } else if (respuesta[0] === "1") {
                animacion_exito("form-login", "lenguajes.html");
                if (respuesta[1] === "1") {
                    sessionStorage.setItem("logged", "Estudiante");
                }
                else {
                    sessionStorage.setItem("logged", "Profesor");
                }
                // Redirecciona a lenguajes.html
            }
        })
        .catch(error => {
            console.error('Fetch error:', error);
        });
    }
    });
}


function registrar() {
    // Llama a la función de inicio de sesión de C cuando se hace clic en el botón de acceder
    const formRegistro = document.getElementById("form-reg");
    const btnReg = document.getElementById("btn_registrarse");
    const usuario = document.getElementById("user_reg");
    const email = document.getElementById("email_reg");
    const password = document.getElementById("pass_reg");

    btnReg.addEventListener('click', event => {
        event.preventDefault();
        
        if (usuario.value.trim() === "" || email.value.trim() === "" || password.value.trim() === "") {
            animacion_error("form-registro","pass_reg","lblMail","lblPassReg", "lblUsuario");
        }

        else {

        const form = new FormData(formRegistro);
        form.append("funcion", "solicitud_registro"); // Cambiado de 'accion' a 'funcion'

        fetch("/php/bbdd.php", {
            method: "POST",
            body: form
        })
        .then(response => response.text())
        .then(text => {
            // Procesar la respuesta del script PHP
            if (text.trim() === "0") {
                animacion_error("form-registro","pass_reg","lblMail","lblPassReg", "lblUsuario");
            } else if (text.trim() === "1") {
                animacion_exito("form-registro", "lenguajes.html");
            } else {
                animacion_error("form-registro","pass_reg","lblMail","lblPassReg", "lblUsuario");
                console.error('Error desconocido en bbdd:', text);
            }
        })
        .catch(error => {
            console.error('Fetch error:', error);
        });
    }
    });
}





document.addEventListener("DOMContentLoaded", function(event) {
    ver_form_registrar_Click();
    ver_form_login_Click();
    ver_form_olvidado_Click();
    comprobar_login();
    registrar();
});
