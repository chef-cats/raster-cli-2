#include "utils/Formatter.hpp"
#include <images/BinaryPGM.hpp>
#include <utils/FileOperations.hpp>

#include <fstream>

namespace fop = file::operations;

BinaryPGM::BinaryPGM(const std::string& file_name) : PGM(file_name) {}

void BinaryPGM::load() {
    std::string file_path = get_file_path();

    std::ifstream file(file_path);
    fop::file_healthcheck(file, file_path);

    PGM::load_metadata(file);

    fop::reopen_as_binary(file, file_path);
    
    read_pixels(file);

    file.clear();
    file.close();
}

void BinaryPGM::save() const {
    load_check();

    std::string file_path = get_file_path();

    std::ofstream file(file_path, std::ios::trunc);
    fop::file_healthcheck(file, file_path);

    save_metadata(file);

    fop::reopen_as_binary(file, file_path);

    write_pixels(file);

    file.clear();
    file.close();
}

void BinaryPGM::read_pixels(std::ifstream& file) {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    std::vector<std::vector<PGM::Pixel>> pixels(height);
    for (size_t i = 0; i < height; ++i) {
        pixels[i].resize(width);
        fop::read_from_binary_file(file, width * sizeof(PGM::Pixel), pixels[i]);
        if (file.eof()) {
            break;
		}
        fop::file_healthcheck(file, file_path);
    }

    set_pixels(std::move(pixels));
}

void BinaryPGM::write_pixels(std::ofstream& file) const {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    const auto& pixels = get_pixels();
    for (size_t i = 0; i < height; ++i) {
        fop::write_to_binary_file(file, width * sizeof(PGM::Pixel), pixels[i]);
        fop::file_healthcheck(file, file_path);
    }
}
