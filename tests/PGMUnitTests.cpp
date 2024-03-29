#include <experimental/filesystem>
#include <fstream>
#include <images/BinaryPGM.hpp>
#include <images/TextPGM.hpp>
#include <iterator>
#include "TestHelpers.hpp"
#include "Constants.hpp"

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

namespace fs = std::experimental::filesystem;

BOOST_AUTO_TEST_SUITE(PGMUnitTests)

BOOST_AUTO_TEST_SUITE(BinaryPGMTests)

BOOST_AUTO_TEST_CASE(ReadOneSymbolImage) {
    std::string file_path = pgm_path + "OneSymbolImage.pgm";
    std::string file_format = "P5";
    size_t height = 1;
    size_t width = 1;
    size_t max_value = 255;
    char content = 'I';

    BinaryPGM image(file_path);

    image.load();

    BOOST_CHECK_EQUAL(image.get_format_id(), file_format);
    BOOST_CHECK_EQUAL(image.get_height(), height);
    BOOST_CHECK_EQUAL(image.get_width(), width);
    BOOST_CHECK_EQUAL(image.get_max_value(), max_value);
    BOOST_CHECK_EQUAL(image.get_pixel(0, 0), content);
}

BOOST_DATA_TEST_CASE(LoadImage, PGM_BINARY_FILE_NAMES, file_name) {
    std::string file_path = pgm_path + file_name;

    BinaryPGM image(file_path);

    image.load();
}

BOOST_DATA_TEST_CASE(SaveImage, PGM_BINARY_FILE_NAMES, file_name) {
    std::string input_file = pgm_path + file_name;
    std::string result_file = pgm_temp_folder + file_name;

    if (!fs::copy_file(input_file, result_file, fs::copy_options::overwrite_existing)) {
        BOOST_FAIL("Can't copy files\n");
    }

    BinaryPGM image(result_file);

    image.load();
    image.save();

    BinaryPGM new_image(result_file);
    new_image.load();

    BOOST_CHECK_EQUAL_COLLECTIONS(image.get_pixels().cbegin(), image.get_pixels().cend(),
                                  new_image.get_pixels().cbegin(),
                                  new_image.get_pixels().cend());
}

BOOST_AUTO_TEST_SUITE_END(/*BinaryPGMTests*/)

BOOST_AUTO_TEST_SUITE(TextPGMTests)

BOOST_AUTO_TEST_CASE(ReadOneSymbolImage) {
    std::string file_path = pgm_path + "OneSymbolImage.ascii.pgm";
    std::string file_format = "P2";
    size_t height = 1;
    size_t width = 1;
    size_t max_value = 255;
    int content = 24;

    TextPGM image(file_path);

    image.load();

    BOOST_CHECK_EQUAL(image.get_format_id(), file_format);
    BOOST_CHECK_EQUAL(image.get_height(), height);
    BOOST_CHECK_EQUAL(image.get_width(), width);
    BOOST_CHECK_EQUAL(image.get_max_value(), max_value);
    BOOST_CHECK_EQUAL(image.get_pixel(0, 0), content);
}

BOOST_DATA_TEST_CASE(LoadImage, PGM_ASCII_FILE_NAMES, file_name) {
    std::string file_path = pgm_path + file_name;

    TextPGM image(file_path);

    image.load();
}

BOOST_DATA_TEST_CASE(SaveImage, PGM_ASCII_FILE_NAMES, file_name) {
    std::string input_file = pgm_path + file_name;
    std::string result_file = pgm_temp_folder + file_name;

    if (!fs::copy_file(input_file, result_file, fs::copy_options::overwrite_existing)) {
        BOOST_FAIL("Can't copy files\n");
    }

    TextPGM image(result_file);

    image.load();
    image.save();

    TextPGM new_image(result_file);
    new_image.load();

    const auto& image_pixels = image.get_pixels();
    const auto& original_pixels = new_image.get_pixels();

    BOOST_CHECK_EQUAL_COLLECTIONS(image_pixels.cbegin(), image_pixels.cend(),
                                  original_pixels.cbegin(), original_pixels.cend());
}

BOOST_AUTO_TEST_SUITE_END(/*TextPGMTests*/)

BOOST_AUTO_TEST_SUITE_END(/*PGMUnitTests*/)