#pragma once
#include <utils/FileOperations.hpp>

namespace file {
namespace operations {

template <typename Type>
void read_from_text_file(std::vector<Type>& data, uint64_t bytes_to_read,
                         std::ifstream& file) {}

template <typename Type>
void read_from_binary_file(std::vector<Type>& data, uint64_t bytes_to_read,
                           std::ifstream& file) {}

template <typename Type>
void write_to_binary_file(const std::vector<Type>& data, uint64_t bytes_to_read,
                          std::ofstream& file) {}

} // namespace operations
} // namespace file