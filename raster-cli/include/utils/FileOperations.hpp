#include <fstream>
#include <images/PGM.hpp>
#include <vector>

namespace file {
namespace operations {
/**
 * Checks whether the file into a good state
 *
 * throws std::ios_base::failure - the file is not opened or the was 
 *                   reading has fail or the file is not available anymore
 */
void file_healthcheck(std::ifstream& file, const std::string& file_name);

/**
 * Read one line skip all whitespace symbols after it
 */
void read_line(std::ifstream& file, std::string& result);

/**
 * Skip the sequence of lines start with special_symbol. After this operation the seekg
 * will at the last whitespace symbol. At the next get it's guarantee that it won't be read
 * a whitespace.
 */
void skip_lines(std::ifstream& file, const std::string& file_name, char special_symbol);

template <typename Type>
void read_from_text_file(std::vector<Type>& data, uint64_t bytes_to_read,
                         std::ifstream& file);

void write_to_text_file(const PGM& image, std::ofstream& file);

/**
 * If the Type has a virtual methods the function doesn't work
 * Please, make a specification for you Type
 */
template <typename Type>
void read_from_binary_file(std::vector<Type>& data, uint64_t bytes_to_read,
                           std::ifstream& file);

/**
 * If the Type has a virtual methods the function doesn't work
 * Please, make a specification for you Type
 */
template <typename Type>
void write_to_binary_file(const std::vector<Type>& data, uint64_t bytes_to_read,
                          std::ofstream& file);

} // namespace operations
} // namespace file