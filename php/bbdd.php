<?php
session_start();
// Establecer la conexión a la base de datos
function establecer_conexion() {
    $servername = "b4p9vmi6pnykocbc3ovr-mysql.services.clever-cloud.com";
    $database = "b4p9vmi6pnykocbc3ovr";
    $username = "utyquf5ripc86mvl";
    $password = "8Pmblr0ysW8eW4Nnn4Ot";

    try {
        $conexion = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
        $conexion->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        return $conexion;
    } catch (PDOException $e) {
        // Manejar cualquier error de conexión a la base de datos
        echo "Hubo un error: " . $e->getMessage();
        return null;
    }
}

// Preparar la consulta SQL
function preparar_consulta_login($conexion) {
    return $conexion->prepare("SELECT 1 FROM login WHERE email = :email AND pass = :pass LIMIT 1");
}

// Función para manejar la solicitud
function comprobar_login($conexion, $query) {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $email = $_POST["email"];
        $pass = $_POST["password"];

        // Ejecutar la consulta preparada
        $query->bindParam(":email", $email);
        $query->bindParam(":pass", $pass);
        $query->execute();

        // Devolver el resultado de la consulta
        $result = $query->fetch(PDO::FETCH_COLUMN);
        if ($result !== false) {
            echo 1;
        } else {
            echo 0;
        }
    } else {
        echo "Método de solicitud inválido";
    }
}

function preparar_consulta_registro($conexion) {
    return $conexion->prepare("INSERT INTO login (usuario, email, pass, esProfesor) VALUES (:nombre, :email, :pass, :profe)");
}

function realizar_registro($conexion) {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $nombre = $_POST["user_reg"];
        $email = $_POST["email_reg"];
        $pass = $_POST["pass_reg"];

        // Verificar si el checkbox está marcado
        $profe = isset($_POST["switch"]) ? 1 : 0; // Si está marcado, $profe es true; de lo contrario, es false

        try {
            // Preparar la consulta
            $query = preparar_consulta_registro($conexion);

            // Ejecutar la consulta preparada
            $query->bindParam(":nombre", $nombre);
            $query->bindParam(":email", $email);
            $query->bindParam(":pass", $pass);
            // Vincular el parámetro $profe como un tipo booleano
            $query->bindParam(":profe", $profe, PDO::PARAM_BOOL); 
            
            $result = $query->execute();

            if ($result) {
                echo 1,$profe; // INSERT CORRECTO
            } else {
                echo 0; // NO CORRECTO
            }
        } catch (PDOException $e) {
            // Manejar cualquier error de base de datos
            echo "Error al realizar el registro: " . $e->getMessage();
        }
    } else {
        echo "Método de solicitud inválido";
    }
}



// Manejar la solicitud
if(isset($_POST['funcion'])) {
    $funcion = $_POST['funcion'];
    $conexion = establecer_conexion();
    if ($conexion) {
        if($funcion === 'solicitud_login') {
            $query = preparar_consulta_login($conexion);
            if ($query) {
                comprobar_login($conexion, $query);
            }
        } elseif($funcion === 'solicitud_registro') {
            $query = preparar_consulta_registro($conexion);
            if ($query) {
                realizar_registro($conexion, $query);
                
            }

        } else {
            echo "Función no válida";
        }
    }
} else {
    echo "No se proporcionó ninguna función";
}
?>
