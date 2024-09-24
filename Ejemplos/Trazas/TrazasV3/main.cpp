#include <iostream>   // ENTRADA Y SALIDA
#include <iomanip>    // MANIPULACIÓN DE FORMATO
#include <thread>     // SUBPROCESOS
#include <chrono>     // CLASE CHRONO

// FUNCIÓN REGISTRA MENSAJES TRAZAS
void trace(const std::string& message) {
    std::cout << "[TRACE] " << message << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // RETRASO 0.5 SEGUNDOS
}

// FUNCIÓN SUMA DOS NÚMEROS
int suma(int a, int b) {
    trace("ENTRANDO EN LA FUNCION SUMA");
    trace("PARAMETROS: a = " + std::to_string(a) + ", b = " + std::to_string(b));
    int result = a + b; // REALIZA SUMA
    trace("RESULTADO: " + std::to_string(result));
    return result; // DEVUELVE RESULTADO
}

// FUNCIÓN RESTA DOS NÚMEROS
int resta(int a, int b) {
    trace("ENTRANDO EN LA FUNCION RESTA");
    trace("PARAMETROS: a = " + std::to_string(a) + ", b = " + std::to_string(b));
    int result = a - b; // REALIZA RESTA
    trace("RESULTADO: " + std::to_string(result));
    return result; // DEVUELVE RESULTADO
}

// FUNCIÓN PRINCIPAL
int main() {
    int num1 = 10; // PRIMER NÚMERO
    int num2 = 5;  // SEGUNDO NÚMERO

    trace("INICIANDO CALCULOS");
    int sum = suma(num1, num2); // LLAMA A LA FUNCIÓN SUMA
    int diferencia = resta(num1, num2); // LLAMA A LA FUNCIÓN RESTA

    trace("CALCULOS REALIZADOS");
    trace("SUMA: " + std::to_string(sum)); // MUESTRA RESULTADO DE SUMA
    trace("DIFERENCIA: " + std::to_string(diferencia)); // MUESTRA RESULTADO DE RESTA

    return 0; // FINALIZA PROGRAMA
}