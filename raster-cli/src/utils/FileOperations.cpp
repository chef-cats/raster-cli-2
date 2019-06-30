#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>

namespace file {
namespace operations {

void file_healthcheck(std::ifstream& file, const std::string& file_name) {
    if (!file.is_open()) {
        throw std::ios_base::failure(Formatter()
                                     << "The file: " << file_name << " is not open.");
    }
    if (file.fail()) {
        file.clear();
        throw std::ios_base::failure((
            Formatter() << "Some of the data is not into the correct type into the file: "
                        << file_name << "!"));
    }
    if (file.bad()) {
        file.clear();
        throw std::ios_base::failure(Formatter() << "File: " << file_name
                                                 << " has broken during reading");
    }
}

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
    while (file.peek() == special_symbol) {
        read_line(file, buffer);
        file_healthcheck(file, file_name);
    }
}

} // namespace operations
} // namespace file
