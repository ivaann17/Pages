function bloquear_url(){
    if (!sessionStorage.getItem("logged")){
        window.location = "index.html";
    }
}

document.addEventListener("DOMContentLoaded", function() {
    bloquear_url();

});