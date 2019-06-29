#pragma once
#include <utils/FileOperations.hpp>

namespace file {
namespace operations {

template <typename Type>
inline void read_from_text_file(std::vector<Type>& data, std::ifstream& file, size_t elem_cnt) {
  data.resize(elem_cnt);
  for (auto& element : data) {
    file >> element;
  }
}

template <typename Type>
inline void write_to_text_file(const std::vector<Type>& data, std::ofstream& file) {
  for (auto& element : data) {
    file << element << " ";
  }
}

template <typename Type>
inline void read_from_binary_file(std::vector<Type>& data, uint64_t bytes_to_read,
                           std::ifstream& file) {}

template <typename Type>
inline void write_to_binary_file(const std::vector<Type>& data, uint64_t bytes_to_read,
                          std::ofstream& file) {}

} // namespace operations
} // namespace file