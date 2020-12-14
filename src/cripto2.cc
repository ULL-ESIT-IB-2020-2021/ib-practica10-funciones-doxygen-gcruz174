/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @file cripto.cc
 * @author Ginés Cruz Chávez
 * @date 7.dec.2020
 * @brief Encripta o desencripta un archivo dado mediante el método XOR o César,
 * guardando la salida en otro archivo.
 *
 */

#include <cstdlib>  /// exit
#include <fstream>
#include <iostream>
#include <sstream>

#include "funciones_cripto2.h"

/** Función principal
 *  @param[in] argc Número de parámetros de línea de comandos
 *  @param[in] argv Vector (char*) que contiene los parámetros
 */
int main(int argc, char* argv[]) {
  Usage(argc, argv);
  if (!AreParametersValid(argv)) {
    std::cout << "Alguno de los parametros introducidos es invalido. "
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream input_file(argv[1], std::ifstream::in);
  std::ofstream output_file(argv[2], std::ofstream::out);

  std::stringstream buffer;
  buffer << input_file.rdbuf();

  std::string message{buffer.str()};
  std::string key{argv[4]};
  std::string output{""};

  if (argv[3][0] == '2') {
    int caesar_constant{std::stoi(key)};

    if (argv[5][0] == '+') {
      output = CaesarCipher(message, caesar_constant);
    } else if (argv[5][0] == '-') {
      output = CaesarCipher(message, -caesar_constant);
    }
  } else if (argv[3][0] == '1') {
    output = XORCipher(message, key);
  }

  WordCount(argv[1]);

  output_file << output;
  output_file.close();

  return 0;
}
