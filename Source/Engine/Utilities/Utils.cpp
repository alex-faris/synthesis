#include "Utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::string Engine::readFile(const std::string& kFilePath)
{
  std::ifstream file(kFilePath);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file: [" << kFilePath << "]" << std::endl;
    return "";
  }

  std::stringstream stream;
  stream << file.rdbuf();

  return stream.str();
}
