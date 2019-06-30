#include <sessions/Session.hpp>

Session::Session(uint64_t id, const std::vector<std::string>& images) : _id(id) {
    _records.reserve(images.size());
    for (size_t index = 0; index < images.size(); ++index) {
        _records.emplace_back(images[index]);
    }
}

void Session::all_to_grayscale() {}

void Session::all_to_monochrome() {}

void Session::all_to_negative() {}

void Session::rotate_all(Direction direction) {}

void Session::undo_last_operation() {}

void Session::add_image(const std::string& image) {}

void Session::remove_image() {}

void Session::save_all() {}

Session::OperationsRecord::OperationsRecord(const std::string& image)
    : _image(create_image(image)) {}

uint64_t Session::Info::get_id() const {
    return 0;
}

const std::vector<std::string>& Session::Info::get_images() const {
    return std::vector<std::string>();
}

size_t Session::Info::OperationInfo::get_count() const {
    return 0;
}

OperationID Session::Info::OperationInfo::get_id() const {
    return OperationID();
}

const std::vector<Session::Info::OperationInfo>&
Session::Info::get_operations_info() const {
    return std::vector<OperationInfo>();
}

Session::Info Session::get_info() const {
    return Info();
}