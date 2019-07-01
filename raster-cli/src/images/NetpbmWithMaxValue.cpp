#include <images/NetpbmWithMaxValue.hpp>
#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>

namespace fop = file::operations;

NetpbmWithMaxValue::NetpbmWithMaxValue(const std::string& file_name)
    : Netpbm(file_name) {}

size_t NetpbmWithMaxValue::get_max_value() const {
    metadata_check();
    return *_max_value;
}

void NetpbmWithMaxValue::metadata_check() const {
    Netpbm::metadata_check();
    if (!_max_value) {
        throw std::logic_error(
            Formatter() << "The max value is not load, but the other metadata is. File: "
                        << get_file_path());
    }
}

void NetpbmWithMaxValue::load_metadata(std::ifstream& file) {
    std::string file_path = get_file_path();
    Netpbm::load_metadata(file);

    size_t max_value;
    file >> max_value;
    set_max_value(max_value);

    fop::skip_lines(file, file_path, COMMENT_SYMBOL);
    fop::file_healthcheck(file, file_path);
    fop::skip_whitespace(file);
}

void NetpbmWithMaxValue::save_metadata(std::ofstream& file) const {
    Netpbm::save_metadata(file);

    file << get_max_value();
    file << std::endl;

    fop::file_healthcheck(file, get_file_path());
}

/**
 * throw std::logic_error - when you try to change the max value for the second time
 */
void NetpbmWithMaxValue::set_max_value(size_t max_value) {
    if (_max_value) {
        throw std::logic_error(Formatter() << "The max value is already set. File: "
                                           << get_file_path());
    } else {
        _max_value = max_value;
    }
}
