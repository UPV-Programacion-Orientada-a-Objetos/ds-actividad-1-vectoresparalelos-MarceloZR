#include <iostream>
#include <fstream>
#include <string>
#include <limits>

const int max_atletas = 100;

std::string nombres[max_atletas];
std::string paises[max_atletas];
std::string disciplinas[max_atletas];
char generos[max_atletas];
int medallas[max_atletas];
int total = 0;

void cargarArchivo() {
    std::ifstream entrada("data1.csv");
    if (!entrada) {
        std::cout << "no se pudo abrir el archivo data1.csv" << std::endl;
        return;
    }

    std::string linea;
    std::getline(entrada, linea); // ignorar encabezado

    while (entrada.good() && total < max_atletas) {
        std::string nombre, pais, disciplina, generoStr, medallasStr;

        if (!std::getline(entrada, nombre, ',')) break;
        if (!std::getline(entrada, pais, ',')) break;
        if (!std::getline(entrada, disciplina, ',')) break;
        if (!std::getline(entrada, generoStr, ',')) break;
        if (!std::getline(entrada, medallasStr, '\n')) break;

        nombres[total] = nombre;
        paises[total] = pais;
        disciplinas[total] = disciplina;
        generos[total] = generoStr[0];
        medallas[total] = std::stoi(medallasStr);

        total++;
    }

    entrada.close();
    std::cout << "se cargaron " << total << " atletas desde data1.csv" << std::endl;
}

void registrarAtleta() {
    if (total >= max_atletas) {
        std::cout << "no se pueden registrar mas atletas" << std::endl;
        return;
    }

    std::string nombre, pais, disciplina, generoStr;
    int numMedallas = 0;

    std::cout << "nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "pais: ";
    std::getline(std::cin, pais);
    std::cout << "disciplina: ";
    std::getline(std::cin, disciplina);
    std::cout << "genero (M/F): ";
    std::getline(std::cin, generoStr);
    std::cout << "numero de medallas: ";
    std::cin >> numMedallas;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    nombres[total] = nombre;
    paises[total] = pais;
    disciplinas[total] = disciplina;
    generos[total] = generoStr[0];
    medallas[total] = numMedallas;
    total++;

    std::cout << "atleta registrado en memoria" << std::endl;
}

void buscarAtleta() {
    std::cout << "nombre a buscar: ";
    std::string buscado;
    std::getline(std::cin, buscado);

    bool encontrado = false;
    for (int i = 0; i < total; i++) {
        if (nombres[i] == buscado) {
            std::cout << nombres[i] << " | " << paises[i] << " | " 
                      << disciplinas[i] << " | " << generos[i] << " | " 
                      << medallas[i] << std::endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "no se encontro el atleta" << std::endl;
    }
}

void medallasPorPais() {
    std::cout << "pais a buscar: ";
    std::string paisBuscado;
    std::getline(std::cin, paisBuscado);

    int suma = 0;
    for (int i = 0; i < total; i++) {
        if (paises[i] == paisBuscado) suma += medallas[i];
    }

    std::cout << "total de medallas para " << paisBuscado << ": " << suma << std::endl;
}

void atletaMasMedallas() {
    if (total == 0) {
        std::cout << "no hay atletas" << std::endl;
        return;
    }

    int indiceMax = 0;
    for (int i = 1; i < total; i++) {
        if (medallas[i] > medallas[indiceMax]) {
            indiceMax = i;
        }
    }

    std::cout << "atleta con mas medallas: " << nombres[indiceMax] 
              << " | " << paises[indiceMax] << " | " << disciplinas[indiceMax] 
              << " | " << generos[indiceMax] << " | " << medallas[indiceMax] << std::endl;
}

void mostrarTodos() {
    if (total == 0) {
        std::cout << "no hay atletas" << std::endl;
        return;
    }

    for (int i = 0; i < total; i++) {
        std::cout << (i+1) << ". " << nombres[i] << " | " << paises[i]
                  << " | " << disciplinas[i] << " | " << generos[i]
                  << " | " << medallas[i] << std::endl;
    }
}

int main() {
    std::cout << "programa de atletas olimpicos" << std::endl;
    cargarArchivo();

    int opcion = 0;
    do {
        std::cout << "\nmenu:\n";
        std::cout << "1. registrar atleta\n";
        std::cout << "2. buscar atleta por nombre\n";
        std::cout << "3. calcular medallas por pais\n";
        std::cout << "4. atleta con mas medallas\n";
        std::cout << "5. mostrar todos los atletas\n";
        std::cout << "6. salir\n";
        std::cout << "opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: registrarAtleta(); break;
            case 2: buscarAtleta(); break;
            case 3: medallasPorPais(); break;
            case 4: atletaMasMedallas(); break;
            case 5: mostrarTodos(); break;
            case 6: std::cout << "saliendo\n"; break;
            default: std::cout << "opcion invalida\n";
        }

    } while (opcion != 6);

    return 0;
}