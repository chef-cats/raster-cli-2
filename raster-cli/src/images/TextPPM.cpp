#include <images/TextPPM.h>
#include <utils/FileOperations.hpp>

namespace fop = file::operations;

TextPPM::TextPPM(const std::string& file_name) : PPM(file_name) {}

void TextPPM::load() {
    std::string file_path = get_file_path();

    std::ifstream file(file_path);
    fop::file_healthcheck(file, file_path);

    load_metadata(file);

    read_pixels(file);

    file.clear();
    file.close();
}

void TextPPM::save() const {
    load_check();

    std::string file_path = get_file_path();

    std::ofstream file(file_path, std::ios::trunc);
    fop::file_healthcheck(file, file_path);

    save_metadata(file);

    write_pixels(file);

    file.clear();
    file.close();
}

void TextPPM::read_pixels(std::ifstream& file) {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    std::vector<std::vector<PPM::Pixel>> pixels(height);
    for (size_t i = 0; i < height; ++i) {
        pixels[i].resize(width);
        fop::read_from_text_file(file, width, pixels[i]);
        fop::file_healthcheck(file, file_path);
    }

    set_pixels(std::move(pixels));
}

void TextPPM::write_pixels(std::ofstream& file) const {
    size_t height = get_height();
    size_t width = get_width();
    std::string file_path = get_file_path();

    const auto& pixels = get_pixels();
    for (size_t i = 0; i < height; ++i) {
        fop::write_to_text_file(file, width, pixels[i]);
        fop::file_healthcheck(file, file_path);
    }
}
