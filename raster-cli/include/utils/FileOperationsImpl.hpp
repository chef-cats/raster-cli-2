#pragma once
#include <utils/FileOperations.hpp>

namespace file {
namespace operations {

template <typename Type>
inline uint64_t read_from_text_file(std::ifstream& file, uint64_t elem_cnt,
                                    std::vector<Type>& data) {
    data.resize(elem_cnt);
    uint64_t element_id = 0;
    for (element_id; file && element_id < elem_cnt; ++element_id) {
        file >> data[element_id];
    }

    return element_id;
}

template <typename Type>
inline uint64_t write_to_text_file(std::ofstream& file, uint64_t elem_cnt,
                                   const std::vector<Type>& data) {
    --elem_cnt;
    uint64_t element_id = 0;
    for (element_id; file && element_id < elem_cnt; ++element_id) {
        file << data[element_id] << " ";
    }

    if (file) {
        file << data[element_id++];
    }

    file << std::endl;

    return element_id;
}

template <typename Type>
inline uint64_t read_from_binary_file(std::ifstream& file, uint64_t bytes_to_read,
                                      std::vector<Type>& container) {
    uint64_t read_bytes;
    uint64_t left_bytes = bytes_to_read;
    std::streampos start_pos = file.tellg();
    std::streampos current_pos = start_pos;

    while (file && left_bytes != 0) {
        start_pos = current_pos;

        file.read((char*)container.data(), left_bytes);

        current_pos = file.tellg();
        read_bytes = current_pos - start_pos;
        left_bytes -= read_bytes;
    }

    return bytes_to_read - left_bytes;
}

template <typename Type>
inline uint64_t write_to_binary_file(std::ofstream& file, uint64_t bytes_to_write,
                                     const std::vector<Type>& container) {
    std::streampos start_pos = file.tellp();

    file.write((const char*)container.data(), bytes_to_write);

    return file.tellp() - start_pos;
}

} // namespace operations
} // namespace file