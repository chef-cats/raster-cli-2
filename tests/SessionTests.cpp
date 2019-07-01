#include <sessions/Session.hpp>

#include <boost/test/unit_test.hpp>

#include <filesystem>
#include <fstream>
#include <iterator>

namespace fs = std::experimental::filesystem;

const std::string pgm_test_data_path = "..\\..\\..\\tests\\TestInput\\PGM\\";

BOOST_AUTO_TEST_SUITE(SessionTests)

BOOST_AUTO_TEST_SUITE(ConstructionTests)

BOOST_AUTO_TEST_CASE(ConstructNoImages) {
    BOOST_CHECK_NO_THROW(Session session(0, {}));
}

BOOST_AUTO_TEST_CASE(ConstructOneImageType) {
    BOOST_CHECK_NO_THROW(Session session(0, {pgm_test_data_path + "coins.pgm"}));
}

BOOST_AUTO_TEST_CASE(ConstructMultiImageTypes) {
    BOOST_CHECK_NO_THROW(Session session(
        0, {pgm_test_data_path + "coins.pgm", pgm_test_data_path + "coins.ascii.pgm"}));
}

BOOST_AUTO_TEST_SUITE_END(/*ConstructionTests*/)

BOOST_AUTO_TEST_SUITE(AddImageTests)

BOOST_AUTO_TEST_CASE(AsciiPGM) {
    Session session(0, {});

    BOOST_REQUIRE_NO_THROW(session.add_image(pgm_test_data_path + "coins.ascii.pgm"));
}

BOOST_AUTO_TEST_CASE(BinaryPGM) {
    Session session(0, {});

    BOOST_REQUIRE_NO_THROW(session.add_image(pgm_test_data_path + "coins.pgm"));
}

BOOST_AUTO_TEST_SUITE_END(/*AddImageTests*/)

BOOST_AUTO_TEST_SUITE(SaveAllTests)

BOOST_AUTO_TEST_CASE(SaveMultipleImages) {
    const std::string original_image_dir = pgm_test_data_path;
    const std::string test_image_dir = pgm_test_data_path + "temp\\";

    if (!fs::copy_file(original_image_dir + "coins.pgm", test_image_dir + "coins.pgm",
                       fs::copy_options::overwrite_existing)) {
        BOOST_FAIL("Can't copy files\n");
    }

    if (!fs::copy_file(original_image_dir + "coins.ascii.pgm",
                       test_image_dir + "coins.ascii.pgm",
                       fs::copy_options::overwrite_existing)) {
        BOOST_FAIL("Can't copy files\n");
    }

    Session session(0,
                    {test_image_dir + "coins.pgm", test_image_dir + "coins.ascii.pgm"});

    BOOST_CHECK_NO_THROW(session.save_all());
}

BOOST_AUTO_TEST_SUITE_END(/*SaveAllTests*/)

BOOST_AUTO_TEST_SUITE_END(/*SessionTests*/)