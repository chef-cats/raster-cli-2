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
void file_healthcheck(std::ios& file, const std::string& file_name);

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
 *
 * @return  the count of the read elements
 */
template <typename Type>
uint64_t read_from_text_file(std::ifstream& file, uint64_t elem_cnt, std::vector<Type>& data);

/**
 * This function writes a data which is save into the a vector, into a file.
 * After each of the elements will be written a space except the last one. After the last
 * element won't have any whitespace symbol.
 *
 * The function required Type to has operator <<
 *
 * @param [in] file - open file to write the data
 * @param [in] elem_cnt - count of the element from data which want to write into the file
 * @param [in] data - container with data to be written into file
 *
 * @return  the count of the written elements
 */
template <typename Type>
uint64_t write_to_text_file(std::ofstream& file, uint64_t elem_cnt,
                        const std::vector<Type>& data);

/**
 * This function read bytes from a binary file and save it into a vector. The function
 * doesn't end before the reading of the exact count of bytes. The vector must be
 * allocated before using of this function.
 * After an invoking of this function you have to check the file health.
 * If the file is not good, the data may not be read from the file because some error.
 * If the Type has a virtual methods the function doesn't work.
 * Please, make a specification for you Type
 *
 * @param [in] file
 * @param [in] bytes_to_read - the bytes which must be read. The function doesn't end
 * before the reading of the exact count of bytes.
 * @param [out] container
 *
 * @return the count of the read bytes
 */
template <typename Type>
uint64_t read_from_binary_file(std::ifstream& file, uint64_t bytes_to_read,
                               std::vector<Type>& container);

/**
 * This function write bytes from a vector and save it into a binary file.
 * After an invoking of this function you have to check the file health.
 * If the file is not good, the data may not be read from the file because some error
 *
 * If the Type has a virtual methods the function doesn't work
 * Please, make a specification for you Type
 *
 * @return the count of the written bytes
 */
template <typename Type>
uint64_t write_to_binary_file(std::ofstream& file, uint64_t bytes_to_write,
                              const std::vector<Type>& container);

/**
 * Reopen text file to binary. The current possition into the file is saved.
 */
void reopen_as_binary(std::ifstream& file, const std::string& file_path);

/**
 * Reopen text file to binary. The current possition into the file is saved.
 */
void reopen_as_binary(std::ofstream& file, const std::string& file_path);
} // namespace operations
} // namespace file

#include "FileOperationsImpl.hpp"