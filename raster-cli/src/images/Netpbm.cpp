#include <images/Netpbm.hpp>
#include <utils/Constants.hpp>
#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>

#include <operations/Operation.hpp>

namespace fop = file::operations;

Netpbm::Netpbm(const std::string& file_path) : Image(file_path) {}

void Netpbm::load_metadata(std::ifstream& file) {
    std::string file_name = get_file_path();
    fop::file_healthcheck(file, file_name);

    std::string buffer;

    fop::read_line(file, buffer);
    set_format_id(buffer);

    fop::skip_lines(file, file_name, COMMENT_SYMBOL);

    size_t height;
    file >> height;
    set_height(height);

    size_t width;
    file >> width;
    set_width(width);

    fop::skip_lines(file, file_name, COMMENT_SYMBOL);
    fop::file_healthcheck(file, file_name);
    fop::skip_whitespace(file);
}

/**
 * Kind of an assertion. Checks if the image is loaded.
 *
 * @throws std::logic_error - if the image is not loaded.
 */
void Netpbm::metadata_check() const {
    std::string message = Formatter()
                          << "Image metadata" << get_file_path() << " is not loaded!";
    if (!_format_id) {
        throw std::logic_error("Format id " + message);
    } else if (!_width) {
        throw std::logic_error("Width " + message);
    } else if (!_height) {
        throw std::logic_error("Height " + message);
    }
}

/**
 * Open the image file and reads only the metadata
 */
void Netpbm::load() {
    std::string file_name = get_file_path();
    std::ifstream file(file_name);
    fop::file_healthcheck(file, file_name);

    load_metadata(file);
}

void Netpbm::load_check() const {
    Netpbm::metadata_check();
}

/**
 * Get the magic number which represent the format of the image
 *
 * @throws std::logic_error - if the image is not loaded.
 */
const std::string& Netpbm::get_format_id() const {
    metadata_check();

    return _format_id.get();
}

/// @see metadata_check
const size_t Netpbm::get_width() const {
    metadata_check();

    return _width.get();
}

/// @see metadata_check
const size_t Netpbm::get_height() const {
    metadata_check();

    return _height.get();
}

/**
 * Set the magic number which represent the format of the image
 */
void Netpbm::set_format_id(const std::string& format_id) {
    _format_id = format_id;
}

void Netpbm::set_width(size_t width) {
    _width = width;
}

void Netpbm::set_height(size_t height) {
    _height = height;
}
