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
inline void read_from_binary_file(std::ifstream& file, uint64_t bytes_to_read,
                                      std::vector<Type>& container) {
    file.read((char*)container.data(), bytes_to_read);
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