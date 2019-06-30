#include "utils/Formatter.hpp"
#include <images/BinaryPGM.hpp>
#include <utils/FileOperations.hpp>

#include <fstream>

BinaryPGM::BinaryPGM(const std::string& file_name) : PGM(file_name) {}

void BinaryPGM::load() {
    PGM::load();
    PGM::allocate_pixels();

    std::string file_path = get_file_path();

    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::ios_base::failure(Formatter()
                                     << "Can't open the file with name: " << file_path);
    }

    read_pixels(file);

    file.clear();
    file.close();
}

void BinaryPGM::save() const {}

void BinaryPGM::read_pixels(std::ifstream& file) {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    std::vector<std::vector<PGMPixel>> pixels(height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            pixels[i].resize(width);
            file::operations::read_from_binary_file(file, width * sizeof(PGMPixel),
                                                    pixels[i]);
            file::operations::file_healthcheck(file, file_path);
        }
    }

    set_pixels(std::move(pixels));
}
