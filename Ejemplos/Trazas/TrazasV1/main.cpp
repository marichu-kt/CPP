/*---------------------------------------------------------------------------------
Una traza es un registro o log que muestra información sobre la ejecución de 
un programa en un momento dado. Se utiliza para entender el flujo del programa, 
identificar problemas o verificar que se estén ejecutando las operaciones esperadas. 
-----------------------------------------------------------------------------------
Un punto de interrupción es una marca que se establece en el código para pausar 
la ejecución del programa en una línea específica. Esto permite al examinar el 
estado del programa.
---------------------------------------------------------------------------------*/

#include <iostream> // PARA LA ENTRADA SALIDA ESTÁNDAR
#include <thread>  // PARA SIMULAR LA ESPERA CON "sleep_for"
#include <chrono>  // PARA EL TIEMPO "seconds"

// FUNCIÓN MOSTRAR BARRA DE PROGRESO
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
    std::cout << "Iniciando simulacion de descarga ..." << std::endl;

    // BUCLE SIMULAR PROGRESO (10 en 10)
    for (int progreso = 0; progreso <= tamanoTotal; progreso += 10) {
        mostrarProgreso(progreso);  // ACTUALIZA BARRA PROGRESO
        std::this_thread::sleep_for(std::chrono::seconds(1));  // SIMULA TIEMPO DESCARGA
    }

    std::cout << std::endl << "Descarga completada!" << std::endl;  // FINALIZA PROGRAMA

    return 0;
}
