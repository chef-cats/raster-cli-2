#include <fstream>+

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
 * Skips all white spaces and read the next symbol. After that it unread it
 * because in this way it will the next symbol which we will read.
 * File must be clear after this operations because :
 *    - we can get the eof symbol - the file will have a eof flag and fail flag
 *    - read a wrong format - the file will have fail flag
 */
void skip_whitespace(std::ifstream& file);

/**
 * Skip the sequence of lines start with special_symbol. After this operation the seekg
 * will at the last whitespace symbol. At the next get it's guarantee that it won't be
 * read a whitespace.
 */
void skip_lines(std::ifstream& file, const std::string& file_name, char special_symbol);

/**
 * This function required Type to has operator >>
 */
template <typename Type>
void read_from_text_file(std::vector<Type>& data, std::ifstream& file, size_t elem_cnt);

/**
 * This function writes a data which is save into the a vector, into a file.
 * After each of the elements will be written a space except the last one. After the last
 * element won't have any whitespace symbol.
 *
 * The function required Type to has operator <<
 *
 * @param [in] file - open file to write the data
 * @param [in] data - container with data to be written into file
 * @param [in] elem_cnt - count of the element from data which want to write into the file
 */
template <typename Type>
void write_to_text_file(std::ofstream& file, const std::vector<Type>& data,
                        size_t elem_cnt);

/**
 * This function read bytes for a binary file and save it into a vector. The function 
 * doesn't end before the reading of the exact count of bytes. The vector must be 
 * allocated before using of this function.
 * After an invoking of this function you have to check the file health.
 * If the file is not good, the data may not be read from the file because some error.
 * If the Type has a virtual methods the function doesn't work.
 * Please, make a specification for you Type
 *
 * @param [in] file
 * @param [in] bytes_to_read - the bytes which must be read. The function doesn't end before
 *                             the reading of the exact count of bytes. 
 * @param [out] container
 */
template <typename Type>
void read_from_binary_file(std::ifstream& file, uint64_t bytes_to_read,
                           std::vector<Type>& container);

/**
 * If the Type has a virtual methods the function doesn't work
 * Please, make a specification for you Type
 */
template <typename Type>
void write_to_binary_file(std::ofstream& file, uint64_t bytes_to_write,
                          const std::vector<Type>& container);

} // namespace operations
} // namespace file

#include "FileOperationsImpl.hpp"