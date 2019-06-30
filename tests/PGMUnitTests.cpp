#include <experimental/filesystem>
#include <fstream>
#include <images/BinaryPGM.hpp>
#include <iterator>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

const std::string path = "..\\..\\..\\tests\\TestInput\\BinaryPGM\\";

const std::vector<std::string> FILE_NAMES = {"coins.pgm", "mona_lisa.pgm"};

const std::string TEMP_FOLDER = path + "temp\\";

namespace fs = std::experimental::filesystem;

BOOST_AUTO_TEST_SUITE(PGMUnitTests)

BOOST_AUTO_TEST_SUITE(BinaryPGMTests)

BOOST_AUTO_TEST_CASE(ReadOneSymbolImage) {
    std::string file_path = path + "OneSymbolImage.pgm";
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

BOOST_DATA_TEST_CASE(LoadImage, FILE_NAMES, file_name) {
    std::string file_path = path + file_name;

    BinaryPGM image(file_path);

    image.load();
}

BOOST_DATA_TEST_CASE(SaveImage, FILE_NAMES, file_name) {
    std::string input_file = path + file_name;
    std::string result_file = TEMP_FOLDER + file_name;

    if (!fs::copy_file(input_file, result_file, fs::copy_options::overwrite_existing)) {
        BOOST_FAIL("Can't copy files\n");
    }

    BinaryPGM image(result_file);

    image.load();
    image.save();

    std::ifstream ifs1(input_file);
    std::ifstream ifs2(result_file);

    std::istream_iterator<char> b1(ifs1), e1;
    std::istream_iterator<char> b2(ifs2), e2;

    BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

BOOST_AUTO_TEST_SUITE_END(/*BinaryPGMTests*/)

BOOST_AUTO_TEST_SUITE_END(/*PGMUnitTests*/)