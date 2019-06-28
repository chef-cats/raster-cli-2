#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>
#include "FileOperationsImpl.hpp"

namespace file {
namespace operations {

void file_healthcheck(std::ifstream& file, const std::string& file_name) {
  if (!file.is_open()) {
    throw std::ios_base::failure(Formatter()
                                 << "The file: " << file_name << " is not open.");
  }
  if (file.fail()) {
    throw std::ios_base::failure(
        (Formatter() << "Some of the data is not into the correct type into the file: "
                     << file_name << "!"));
  }
  if (file.bad()) {
    throw std::ios_base::failure(Formatter() << "File: " << file_name
                                             << " has broken during reading");
  }
}

/**
 * Skips all white spaces and read the next symbol. After that it unread it
 * because in this way it will the next symbol which we will read.
 * File must be clear after this operations because :
 *    - we can get the eof symbol - the file will have a eof flag and fail flag
 *    - read a wrong format - the file will have fail flag
 */
void skip_whitespace(std::ifstream& file) {
  char symbol;
  file >> symbol;
  file.unget();
  file.clear();
}

void read_line(std::ifstream& file, std::string& result) {
  std::getline(file, result);
  skip_whitespace(file);
}

void skip_lines(std::ifstream& file, const std::string& file_name, char special_symbol) {
  std::string buffer;
  char symbol;
  do {
    file.get(symbol);
    if (symbol == special_symbol) {
      read_line(file, buffer);
    } else {
      file.unget();
      file.clear();
    }
    file_healthcheck(file, file_name);
  } while (symbol == special_symbol);
}

void write_to_text_file(const PGM& image, std::ofstream& file) {
  // TODO
}

} // namespace operations
} // namespace file
