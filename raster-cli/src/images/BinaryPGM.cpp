#include "utils/Formatter.hpp"
#include <images/BinaryPGM.hpp>
#include <utils/FileOperations.hpp>

#include <fstream>

BinaryPGM::BinaryPGM(const std::string& file_name) : PGM(file_name) {}

void BinaryPGM::load() {
    std::string file_path = get_file_path();

    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::ios_base::failure(Formatter()
                                     << "Can't open the file with name: " << file_path);
    }

    PGM::load_metadata(file);
    PGM::allocate_pixels();

    read_pixels(file);

    file.clear();
    file.close();
}

void BinaryPGM::save() const {
    load_check();

    std::string file_path = get_file_path();

    std::ofstream file(file_path, std::ios::trunc);
    if (!file) {
        throw std::ios_base::failure(Formatter()
                                     << "Can't open the file with name: " << file_path);
    }

    save_metadata(file);
    write_pixels(file);

    file.clear();
    file.close();
}

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

void BinaryPGM::write_pixels(std::ofstream& file) const {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    const auto& pixels = get_pixels();
    for (size_t i = 0; i < height; ++i) {
         file::operations::write_to_binary_file(file, width * sizeof(PGMPixel),
                                                   pixels[i]);
         file::operations::file_healthcheck(file, file_path);
    }
}
