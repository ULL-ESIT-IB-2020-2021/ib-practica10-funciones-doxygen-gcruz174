/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Ginés Cruz Chávez
 * @date 7.dec.2020
 * @brief This file declares the "Help Text" constant and five functions
 *
 */

#include <iostream>

const std::string kHelpText = R"(fichero_entrada: Fichero a codificar
fichero_salida:  Fichero codificado
método:          Indica el método de encriptado
                   1: Cifrado xor
                   2: Cifrado de César
password:        Palabra secreta en el caso de método 1, Valor de K en el método 2
operación:       Operación a realizar en el fichero
                   +: encriptar el fichero
                   -: desencriptar el fichero)";

void Usage(int argc, char *argv[]);
bool AreParametersValid(char *argv[]);
bool IsInteger(const std::string str);
std::string XORCipher(std::string message, std::string key);
std::string CaesarCipher(std::string message, int key);
void WordCount(std::string filename);
