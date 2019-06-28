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

void write_to_text_file(const PGM& image, std::ofstream& file) {
  // TODO
}

} // namespace operations
} // namespace file
