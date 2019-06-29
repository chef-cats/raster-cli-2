#pragma once

#include <fstream>
#include <string>

/**
 * Reads a type ID from the first whitespace separated string in file.
 *
 * @param file_path [in] Path to file.
 * @returns The format ID of @ref file_path.
 * @throws std::logic_error if @ref file_path is not open
 */
static std::string load_format_id(const std::string& file_path) {
    std::ifstream in(file_path);
    if (!in.is_open()) {
        throw std::logic_error("file can not be opened for writing");
    }

    std::string format_id;
    in >> format_id;

    return format_id;
}

template <typename UnsignedType>
static unsigned char high_bit_offset() {
    UnsignedType bits_count = (CHAR_BIT * sizeof(UnsignedType));

    return bits_count - 1;
}
