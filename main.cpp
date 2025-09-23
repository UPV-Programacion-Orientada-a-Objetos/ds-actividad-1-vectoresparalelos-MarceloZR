#include <iostream>
#include <fstream>   // Para leer/escribir archivos
#include <sstream>   // Para separar por comas
#include <string>
#include <limits>    // Para limpiar buffer si es necesario

int main() {

    const int MAX_ATLETAS = 500; // espacio máximo (seguro para la práctica)
    std::string nombres[MAX_ATLETAS];
    std::string paises[MAX_ATLETAS];
    std::string disciplinas[MAX_ATLETAS];
    char generos[MAX_ATLETAS];
    int medallas[MAX_ATLETAS];
    int total = 0; // número real de atletas 

    std::cout << "Programa de Atletas Olimpicos" << std::endl;

    std::ifstream entrada("data1.csv");
    if (entrada) {
        std::string linea;
        // Leemos encabezado (si existe) y lo ignoramos
        if (std::getline(entrada, linea)) {
            // suponer que la primera línea es encabezado; si no lo es, se sobrescribe
        }
        // Leer cada línea y parsearla
        while (std::getline(entrada, linea) && total < MAX_ATLETAS) {
            if (linea.size() == 0) continue; // saltar líneas vacías
            std::stringstream ss(linea);
            std::string campo;

            if (!std::getline(ss, campo, ',')) continue;
            nombres[total] = campo;

            if (!std::getline(ss, campo, ',')) continue;
            paises[total] = campo;

            if (!std::getline(ss, campo, ',')) continue;
            disciplinas[total] = campo;

            if (!std::getline(ss, campo, ',')) continue;
            generos[total] = (campo.size() > 0) ? campo[0] : ' ';

            if (!std::getline(ss, campo, ',')) continue;
            try {
                medallas[total] = std::stoi(campo);
            } catch (...) {
                medallas[total] = 0; // si falla, poner 0
            }

            total++;
        }
        entrada.close();
        std::cout << "Se cargaron " << total << " atletas desde data1.csv" << std::endl;
    } else {
        std::cout << "No se encontro data1.csv. Puedes registrar atletas manualmente." << std::endl;
    }

    int opcion = 0;
    do {
        std::cout << "\nMenu de opciones:" << std::endl;
        std::cout << "1. Registrar atleta" << std::endl;
        std::cout << "2. Buscar atleta por nombre" << std::endl;
        std::cout << "3. Calcular medallas por pais" << std::endl;
        std::cout << "4. Mostrar atleta con mas medallas" << std::endl;
        std::cout << "5. Mostrar todos los atletas" << std::endl;
        std::cout << "6. Salir" << std::endl;

        std::cout << "Elige una opcion: ";
        if (!(std::cin >> opcion)) {
   
            std::cout << "Entrada invalida. Intenta de nuevo." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Limpieza de buffer antes de getline si vamos a leer cadenas completas
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                // Registrar un nuevo atleta 
                if (total >= MAX_ATLETAS) {
                    std::cout << "Capacidad maxima alcanzada. No se puede registrar mas atletas." << std::endl;
                    break;
                }

                std::string nombre, pais, disciplina;
                char genero = ' ';
                int numMedallas = 0;

                std::cout << "Ingrese nombre completo: ";
                std::getline(std::cin, nombre);

                std::cout << "Ingrese pais: ";
                std::getline(std::cin, pais);

                std::cout << "Ingrese disciplina: ";
                std::getline(std::cin, disciplina);

                std::cout << "Ingrese genero (M/F): ";
                std::string tmpGenero;
                std::getline(std::cin, tmpGenero);
                if (tmpGenero.size() > 0) genero = tmpGenero[0];

                std::cout << "Ingrese numero de medallas de oro: ";
                std::string tmpMed;
                std::getline(std::cin, tmpMed);
                try {
                    numMedallas = std::stoi(tmpMed);
                } catch (...) {
                    numMedallas = 0;
                }

                // Guardar en arrays
                nombres[total] = nombre;
                paises[total] = pais;
                disciplinas[total] = disciplina;
                generos[total] = genero;
                medallas[total] = numMedallas;
                total++;

                // También anexamos la línea al archivo CSV para persistencia
                std::ofstream salida("data.csv", std::ios::app);
                if (salida) {
                    salida << nombre << "," << pais << "," << disciplina << "," << genero << "," << numMedallas << "\n";
                    salida.close();
                    std::cout << "Atleta registrado y guardado en data1.csv" << std::endl;
                } else {
                    std::cout << "Atleta registrado en memoria, pero NO se pudo abrir data1.csv para guardar." << std::endl;
                }

                break;
            }
            case 2: {
                // Buscar por nombre 
                std::cout << "Ingresa el nombre (o primera palabra) a buscar: ";
                std::string buscado;
                std::getline(std::cin, buscado);

                bool encontrado = false;
                for (int i = 0; i < total; i++) {
                    if (nombres[i] == buscado) {
                        std::cout << "Atleta encontrado: " << nombres[i] << " | "
                                  << paises[i] << " | " << disciplinas[i] << " | "
                                  << generos[i] << " | " << medallas[i] << " medallas" << std::endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "No se encontro ningun atleta con ese nombre exacto." << std::endl;
                }
                break;
            }
            case 3: {
                // Calcular medallas totales por pais
                std::cout << "Ingresa el nombre del pais: ";
                std::string paisBuscado;
                std::getline(std::cin, paisBuscado);

                int suma = 0;
                for (int i = 0; i < total; i++) {
                    if (paises[i] == paisBuscado) suma += medallas[i];
                }
                std::cout << "Total de medallas de oro para " << paisBuscado << ": " << suma << std::endl;
                break;
            }
            case 4: {
                // Encontrar atleta con más medallas
                if (total == 0) {
                    std::cout << "No hay atletas registrados." << std::endl;
                    break;
                }
                int indiceMax = 0;
                int maxMed = medallas[0];
                for (int i = 1; i < total; i++) {
                    if (medallas[i] > maxMed) {
                        maxMed = medallas[i];
                        indiceMax = i;
                    }
                }
                std::cout << "Atleta con mas medallas: " << nombres[indiceMax]
                          << " | " << paises[indiceMax] << " | " << disciplinas[indiceMax]
                          << " | " << generos[indiceMax] << " | " << medallas[indiceMax] << " medallas" << std::endl;
                break;
            }
            case 5: {
                // Mostrar todos los atletas 
                if (total == 0) {
                    std::cout << "No hay atletas registrados." << std::endl;
                } else {
                    std::cout << "Lista de atletas (" << total << "):" << std::endl;
                    for (int i = 0; i < total; i++) {
                        std::cout << (i+1) << ". " << nombres[i] << " | " << paises[i]
                                  << " | " << disciplinas[i] << " | " << generos[i]
                                  << " | " << medallas[i] << " medallas" << std::endl;
                    }
                }
                break;
            }
            case 6:
                std::cout << "Saliendo del programa. " << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intenta otra vez." << std::endl;
        }

    } while (opcion != 6);

    return 0;
}