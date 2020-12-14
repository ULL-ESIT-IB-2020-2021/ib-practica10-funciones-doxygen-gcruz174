/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Ginés Cruz Chávez
 * @date 7.dec.2020
 * @brief Funciones utilizadas en el programa cripto.cc
 *
 */

#include "funciones_cripto2.h"

#include <cstdlib>  // exit
#include <fstream>
#include <iostream>
#include <sstream>

/** Muestra el modo de uso correcto del programa
 *  En caso de que el uso no sea el correcto, muestra el mensaje y finaliza
 *  la ejecución del programa.
 *  El programa precisa de 5 parámetros para su ejecución:
 *  1. Fichero de entrada
 *  2. Fichero de salida
 *  3. Método de cifrado
 *  4. Password
 *  5. Operación a usar (+: cifrar, -: descifrar)
 *
 *  @param[in] argc Número de parámetros de línea de comandos
 *  @param[in] argv Vector (char*) que contiene los parámetros
 */
void Usage(int argc, char *argv[]) {
  if (argc == 2) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << argv[0] << " -- Cifrado de ficheros" << std::endl;
      std::cout << "Modo de uso: " << argv[0]
                << " fichero_entrada fichero_salida método password operación"
                << std::endl;
      std::cout << kHelpText << std::endl;
      exit(EXIT_SUCCESS);
    }
  }
  if (argc == 1 || argc != 6) {
    std::cout << argv[0] << " -- Cifrado de ficheros" << std::endl;
    std::cout << "Modo de uso: " << argv[0]
              << " fichero_entrada fichero_salida método password operación"
              << std::endl;
    std::cout << "Pruebe " << argv[0] << " --help para más información"
              << std::endl;
    exit(EXIT_SUCCESS);
  }
}

/** Comprueba si los parámetros introducidos al programa son de formato válido.
 *
 *  @param[in] argv Vector (char*) que contiene los parámetros
 *  @return si los parámetros son válidos
 */
bool AreParametersValid(char *argv[]) {
  if (argv[3][0] != '1' && argv[3][0] != '2') return false;

  std::string parameter_4{argv[4]};
  if (argv[3][0] == '2' && !IsInteger(parameter_4)) {
    return false;
  }

  if (argv[5][0] != '+' && argv[5][0] != '-') return false;

  return true;
}

/** Comprueba si la string introducida es un número entero.
 *
 *  @param[in] number String que contiene el número.
 *  @return si el número es un entero.
 */
bool IsInteger(std::string number) {
  for (auto c : number) {
    if (c < 48 || c > 57) return false;
  }

  return true;
}

/** Efectúa el cifrado/descifrado XOR sobre una cadena de texto dada una palabra
 * clave. Previamente al cifrado del mensaje, se efectúa el XOR en la clave con
 * la constante 128.
 *
 *  @param[in] message String que contiene el mensaje.
 *  @param[in] key String que contiene la key.
 *  @return Mensaje cifrado/descifrado utilizando XOR.
 */
std::string XORCipher(std::string message, std::string key) {
  std::string encrypted_key{""};
  std::string encrypted_message{""};

  for (size_t i = 0; i < key.length(); i++) {
    char xored_char = key.at(i) ^ (char)128;

    encrypted_key.push_back(xored_char);
  }

  for (size_t i = 0; i < message.length(); i++) {
    char xored_char =
        message.at(i) ^ encrypted_key.at(i % encrypted_key.length());

    encrypted_message.push_back(xored_char);
  }

  return encrypted_message;
}

/** Efectúa el cifrado/descifrado césar sobre una cadena de texto dada la
 * constante de rotación k. Previamente al cifrado del mensaje, se efectúa el
 * XOR en la clave con la constante 128.
 *
 *  @param[in] message String que contiene el mensaje.
 *  @param[in] k constante de rotación
 *  @return Mensaje cifrado/descifrado utilizando César
 */
std::string CaesarCipher(std::string message, int k) {
  std::string encrypted_message{""};
  for (auto c : message) {
    encrypted_message.push_back(c + (char)k);
  }

  return encrypted_message;
}

void WordCount(std::string filename) {
  std::ifstream input_file(filename, std::ifstream::in);

  std::stringstream buffer;
  buffer << input_file.rdbuf();
  std::string file{buffer.str()};

  int count{1};
  for (size_t i = 0; i < file.length(); i++) {
    if (i == 0) continue;

    if (file[i] == ' ' && file[i - 1] != ' ') count++;
  }

  if (file.empty()) count = 0;

  std::cout << "Número de palabras: " << count << std::endl;
}
