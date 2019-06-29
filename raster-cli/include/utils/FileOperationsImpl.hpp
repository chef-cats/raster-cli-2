#pragma once
#include <utils/FileOperations.hpp>

namespace file {
namespace operations {

template <typename Type>
inline void read_from_text_file(std::vector<Type>& data, std::ifstream& file,
                                size_t elem_cnt) {
    data.resize(elem_cnt);
    for (auto& element : data) {
        file >> element;
    }
}

template <typename Type>
inline void write_to_text_file(std::ofstream& file, const std::vector<Type>& data,
                               size_t elem_cnt) {
    --elem_cnt;
    for (size_t i = 0; i < elem_cnt; ++i) {
        file << data[i] << " ";
    }
    file << data[elem_cnt];
}

template <typename Type>
inline void read_from_binary_file(std::ifstream& file, uint64_t bytes_to_read,
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
}

template <typename Type>
inline void write_to_binary_file(std::ofstream& file, uint64_t bytes_to_write,
                                 const std::vector<Type>& container) {
    file.write((const char*)container.data(), bytes_to_write);
}

} // namespace operations
} // namespace file