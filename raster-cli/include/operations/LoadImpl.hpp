#pragma once
#include <operations/Load.hpp>

template <typename ImageType>
inline void Load::read_from_text_file(ImageType& image, uint64_t bytes_to_read,
                                      std::ifstream& file) const {}

template <typename ImageType>
inline void Load::read_from_binary_file(ImageType& image, uint64_t bytes_to_read,
                                        std::ifstream& file) const {}