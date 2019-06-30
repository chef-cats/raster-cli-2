#include <sessions/Session.hpp>

#include "OperationsMock.hpp"

Session::Session(uint64_t id, const std::vector<std::string>& images) : _id(id) {
    _records.reserve(images.size());
    for (size_t index = 0; index < images.size(); ++index) {
        add_image(images[index]);
    }
}

void Session::all_to_grayscale() {
    add_operation_to_all(ToGrayscale());
}

void Session::all_to_monochrome() {
    add_operation_to_all(ToMonochrome());
}

void Session::all_to_negative() {
    add_operation_to_all(ToNegative());
}

void Session::rotate_all(Direction direction) {
    add_operation_to_all(Rotate(direction));
}

void Session::undo_last_operation() {
    for (auto& record : _records) {
        record.remove_last_operation();
	}
}

void Session::add_image(const std::string& image) {
    _records.emplace_back(image);
}

void Session::save_all() {
    for (auto& record : _records) {
        record.execute_operations();
    }
}

void Session::add_operation_to_all(const Operation& operation) {
    for (auto& record : _records) {
        record.add_operation(operation);
    }
}

Session::OperationsRecord::OperationsRecord(const std::string& image)
    : _image(create_image(image)) {}

void Session::OperationsRecord::remove_last_operation() {
    _operations.pop_back();
}

void Session::OperationsRecord::add_operation(const Operation& operation) {
    _operations.emplace_back(new Operation(operation));
}

void Session::OperationsRecord::execute_operations() {
    for (const auto& operation : _operations) {
        _image->apply(*operation);
	}
}

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