#include <iostream>   // BIBLIOTECA ESTÁNDAR PARA ENTRADA Y SALIDA
#include <string>     // BIBLIOTECA ESTÁNDAR PARA MANIPULACIÓN DE CADENAS
#include <chrono>     // BIBLIOTECA PARA GESTIONAR TIEMPO
#include <ctime>      // BIBLIOTECA PARA TRABAJAR CON EL TIEMPO DEL SISTEMA
#include <thread>     // BIBLIOTECA PARA TRABAJAR CON SUBPROCESOS

class Logger {
public:
    // ENUM PARA LOS NIVELES DE LOG
    enum Level {
        INFO,
        WARNING,
        ERROR
    };

    // MÉTODO PARA REGISTRAR MENSAJES
    void log(Level level, const std::string& message) {
        std::string levelStr;
        switch (level) {
            case INFO: levelStr = "INFO"; break; // NIVEL INFORMACIÓN
            case WARNING: levelStr = "WARNING"; break; // NIVEL ALERTA
            case ERROR: levelStr = "ERROR"; break; // NIVEL ERROR
        }

        // OBTENER HORA ACTUAL
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::string timeStr = std::ctime(&now_time);
        timeStr.erase(timeStr.length() - 1); // ELIMINAR EL SALTO DE LÍNEA

        // IMPRIMIR EL MENSAJE DE LOG
        std::cout << "[" << timeStr << "][" << levelStr << "] " << message << std::endl;
    }
};

int main() {
    Logger logger;

    // MENSAJE INICIO
    logger.log(Logger::INFO, "El programa ha comenzado.");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // PAUSA 1 SEGUNDO

    // MENSAJE ADVERTENCIA
    logger.log(Logger::WARNING, "Este es un mensaje de advertencia.");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // PAUSA 1 SEGUNDO

    // MENSAJE ERROR
    logger.log(Logger::ERROR, "Se ha producido un error.");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // PAUSA 1 SEGUNDO

    // SIMULACIÓN PROCESO
    for (int i = 0; i < 3; ++i) {
        logger.log(Logger::INFO, "Ejecutando proceso " + std::to_string(i + 1) + " ...");
        std::this_thread::sleep_for(std::chrono::seconds(1)); // PAUSA 1 SEGUNDO
    }

    // MENSAJE FIN
    logger.log(Logger::INFO, "El programa ha terminado.");

    return 0;
}

