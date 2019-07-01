#include "Constants.hpp"
#include "TestHelpers.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <images/TextPPM.hpp>
#include <iterator>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

namespace fs = std::experimental::filesystem;

BOOST_AUTO_TEST_SUITE(PPMUnitTests)

BOOST_AUTO_TEST_SUITE(BinaryPPMTests)

BOOST_AUTO_TEST_CASE(ReadOnePixelImage) {
    std::string file_path = ppm_path + "OneSymbolImage.ascii.ppm";
    std::string file_format = "P3";
    size_t height = 1;
    size_t width = 1;
    size_t max_value = 255;
    char red = 24;
    char green = 54;
    char blue = 48;

    TextPPM image(file_path);

    image.load();

    BOOST_CHECK_EQUAL(image.get_format_id(), file_format);
    BOOST_CHECK_EQUAL(image.get_height(), height);
    BOOST_CHECK_EQUAL(image.get_width(), width);
    BOOST_CHECK_EQUAL(image.get_max_value(), max_value);

    PPM::Pixel pixel = image.get_pixel(0, 0);
    BOOST_CHECK_EQUAL(pixel.get_red(), red);
    BOOST_CHECK_EQUAL(pixel.get_green(), green);
    BOOST_CHECK_EQUAL(pixel.get_blue(), blue);
}

BOOST_DATA_TEST_CASE(LoadImage, PPM_ASCII_FILE_NAMES, file_name) {
    std::string file_path = ppm_path + file_name;

    TextPPM image(file_path);

    image.load();
}

BOOST_DATA_TEST_CASE(SaveImage, PPM_ASCII_FILE_NAMES, file_name) {
    std::string input_file = ppm_path + file_name;
    std::string result_file = ppm_temp_folder + file_name;

    if (!fs::copy_file(input_file, result_file, fs::copy_options::overwrite_existing)) {
        BOOST_FAIL("Can't copy files\n");
    }

    TextPPM image(result_file);

    image.load();
    image.save();

    TextPPM new_image(result_file);
    new_image.load();

    const auto& image_pixels = image.get_pixels();
    const auto& original_pixels = new_image.get_pixels();

    BOOST_CHECK_EQUAL_COLLECTIONS(image_pixels.cbegin(), image_pixels.cend(),
                                  original_pixels.cbegin(), original_pixels.cend());
}

BOOST_AUTO_TEST_SUITE_END(/*BinaryPPMTests*/)

BOOST_AUTO_TEST_SUITE_END(/*PPMUnitTests*/)