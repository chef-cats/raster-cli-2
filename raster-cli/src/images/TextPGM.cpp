#include "utils/Formatter.hpp"
#include <images/TextPGM.hpp>
#include <utils/FileOperations.hpp>

#include <fstream>

namespace fop = file::operations;

TextPGM::TextPGM(const std::string& file_name) : PGM(file_name) {}

void TextPGM::load() {
    std::string file_path = get_file_path();

    std::ifstream file(file_path);
    fop::file_healthcheck(file, file_path);

    load_metadata(file);

    read_pixels(file);

    file.clear();
    file.close();
}

void TextPGM::save() const {
    load_check();

    std::string file_path = get_file_path();

    std::ofstream file(file_path, std::ios::trunc);
    fop::file_healthcheck(file, file_path);

    save_metadata(file);

    write_pixels(file);

    file.clear();
    file.close();
}

void TextPGM::read_pixels(std::ifstream& file) {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    std::vector<std::vector<PGM::Pixel>> pixels(height);
    for (size_t i = 0; i < height; ++i) {
        pixels[i].resize(width);
        fop::read_from_text_file(file, width, pixels[i]);
        fop::file_healthcheck(file, file_path);
    }

    set_pixels(std::move(pixels));
}

void TextPGM::write_pixels(std::ofstream& file) const {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    const auto& pixels = get_pixels();
    for (size_t i = 0; i < height; ++i) {
        fop::write_to_text_file(file, width, pixels[i]);
        fop::file_healthcheck(file, file_path);
    }
}
