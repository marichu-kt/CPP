/*---------------------------------------------------------------------------------
UNA TRAZA ES UN REGISTRO O LOG QUE MUESTRA INFORMACIÓN SOBRE LA EJECUCIÓN DE 
UN PROGRAMA EN UN MOMENTO DADO. SE UTILIZA PARA ENTENDER EL FLUJO DEL PROGRAMA, 
IDENTIFICAR PROBLEMAS O VERIFICAR QUE SE ESTÉN EJECUTANDO LAS OPERACIONES ESPERADAS. 
-----------------------------------------------------------------------------------
UN PUNTO DE INTERRUPCIÓN ES UNA MARCA QUE SE ESTABLECE EN EL CÓDIGO PARA PAUSAR 
LA EJECUCIÓN DEL PROGRAMA EN UNA LÍNEA ESPECÍFICA. ESTO PERMITE EXAMINAR EL 
ESTADO DEL PROGRAMA.
---------------------------------------------------------------------------------*/

#include <iostream>     // PARA ENTRADA/SALIDA ESTÁNDAR
#include <fstream>      // PARA ESCRIBIR EN ARCHIVOS (LOGGING)
#include <thread>       // PARA SIMULAR ESPERA CON "SLEEP_FOR"
#include <chrono>       // PARA EL TIEMPO "SECONDS"
#include <string>       // PARA MANIPULAR CADENAS DE TEXTO
#include <ctime>        // PARA OBTENER FECHA Y HORA

// FUNCIÓN PARA REGISTRAR TRAZAS EN UN ARCHIVO
void registrarTrazas(const std::string& mensaje) {
    std::ofstream archivoLog("log.txt"); // ABRE ARCHIVO EN MODO POR DEFECTO (SOBRESCRIBIR)
    if (archivoLog.is_open()) {
        // OBTENER LA FECHA Y HORA ACTUAL
        std::time_t tiempoActual = std::time(nullptr);
        std::string tiempoFormateado = std::asctime(std::localtime(&tiempoActual));
        
        // ELIMINAR EL SALTO DE LÍNEA AL FINAL DE LA FECHA
        tiempoFormateado.erase(tiempoFormateado.length() - 1);

        archivoLog << "[" << tiempoFormateado << "] " << mensaje << std::endl;  // ESCRIBE EL MENSAJE EN EL ARCHIVO
    } else {
        std::cerr << "ERROR AL ABRIR EL ARCHIVO log.txt" << std::endl;
    }
}

// FUNCIÓN PARA MOSTRAR BARRA DE PROGRESO
void mostrarProgreso(int porcentaje) {
    const int barraLongitud = 30;  // LONGITUD DE LA BARRA DE PROGRESO
    int numHashes = (porcentaje * barraLongitud) / 100;  // CUÁNTOS "#" MOSTRAR
    
    // IMPRIMIR PORCENTAJE Y BARRA DE PROGRESO
    std::cout << "\rProgress: [" << porcentaje << "%]  [";
    
    // IMPRIMIR CARACTERES "#"
    for (int i = 0; i < numHashes; ++i) {
        std::cout << "#";
    }
    
    // IMPRIMIR CARACTERES "."
    for (int i = numHashes; i < barraLongitud; ++i) {
        std::cout << ".";
    }
    
    std::cout << "]" << std::flush;  // ASEGURAR QUE LA LÍNEA SE IMPRIMA INMEDIATAMENTE
}

int main() {
    int tamanoTotal = 100;  // SIMULANDO TAMAÑO DE LA DESCARGA (100%)

    // TRAZA INICIAL
    registrarTrazas("INICIANDO SIMULACION DE DESCARGA...");
    std::cout << "Iniciando simulacion de descarga ..." << std::endl;

    // BUCLE PARA SIMULAR EL PROGRESO (10 EN 10)
    for (int progreso = 0; progreso <= tamanoTotal; progreso += 10) {
        mostrarProgreso(progreso);  // ACTUALIZA BARRA DE PROGRESO
        registrarTrazas("Progreso: " + std::to_string(progreso) + "%");  // TRAZA DEL PROGRESO
        std::this_thread::sleep_for(std::chrono::seconds(1));  // SIMULA TIEMPO DE DESCARGA
    }

    // TRAZA FINAL
    registrarTrazas("Descarga completada!");
    std::cout << std::endl << "Descarga completada!" << std::endl;

    return 0;
}

