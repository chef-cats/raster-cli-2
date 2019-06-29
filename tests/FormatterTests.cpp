#include <iomanip>
#include <utils/Formatter.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FormatterUnitTests)

BOOST_AUTO_TEST_CASE(SaveOneString) {
    const std::string message = "some message";
    Formatter f;
    f << message;
    std::string result = f.str();
    BOOST_CHECK_EQUAL(result, message);
    BOOST_CHECK_EQUAL((std::string)f, message);
}

BOOST_AUTO_TEST_CASE(SaveMultipleStrings) {
    const std::string message1 = "message1";
    const std::string delim = ", ";
    const std::string message2 = "message2";
    const std::string expected_result = message1 + delim + message2;

    Formatter f;
    f << message1 << delim << message2;

    BOOST_CHECK_EQUAL(f.str(), expected_result);
    BOOST_CHECK_EQUAL((std::string)f, expected_result);
}

BOOST_AUTO_TEST_CASE(SaveMultipleTypesOfData) {
    const std::string message1 = "message1";
    const std::string delim = " ";
    const int number1 = 5;
    const int number2 = -6;
    const float number3 = 3.14;
    const std::string expected_result = message1 + delim + std::to_string(number1) + delim
                                        + std::to_string(number2) + delim
                                        + std::to_string(number3);

    Formatter f;
    f << message1 << delim << number1 << delim << number2 << delim << std::fixed
      << number3;

    BOOST_CHECK_EQUAL(f.str(), expected_result);
    BOOST_CHECK_EQUAL((std::string)f, expected_result);
}

BOOST_AUTO_TEST_SUITE_END(/*FormatterUnitTests*/)
