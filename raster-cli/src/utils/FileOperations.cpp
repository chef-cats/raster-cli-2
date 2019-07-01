#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>

namespace file {
namespace operations {

void file_healthcheck(std::ios& file, const std::string& file_name) {
    if (!file.rdbuf()) {
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

void reopen_as_binary(std::ifstream& file, const std::string& file_path) {
    auto pixel_start = file.tellg();

    file.close();
    file.open(file_path, std::ios::binary);

    file.seekg(pixel_start);
}

void reopen_as_binary(std::ofstream& file, const std::string& file_path) {
    auto pixel_start = file.tellp();

    file.close();
    file.open(file_path, std::ios::binary | std::ios::app);

    file.seekp(pixel_start);
}

} // namespace operations
} // namespace file
