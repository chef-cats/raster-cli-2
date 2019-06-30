#include "OperationsMock.hpp"

#include <sessions/Session.hpp>

#include <unordered_map>

static OperationID get_op_id(const Operation* operation) {
    if (dynamic_cast<const ToGrayscale*>(operation)) {
        return OperationID::TO_GRAYSCALE;
    }
    if (dynamic_cast<const ToMonochrome*>(operation)) {
        return OperationID::TO_MONOCHROME;
    }
    if (dynamic_cast<const ToNegative*>(operation)) {
        return OperationID::TO_NEGATIVE;
    }

    const Rotate* rotate = dynamic_cast<const Rotate*>(operation);
    if (rotate) {
        if (rotate->get_direction() == Direction::LEFT) {
            return OperationID::ROTATE_LEFT;
        }
        if (rotate->get_direction() == Direction::RIGHT) {
            return OperationID::ROTATE_RIGHT;
        }
    }

    throw std::invalid_argument("Unknown operation!");
}

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

Session::Info Session::get_info() const {
    std::vector<std::string> images;
    std::unordered_map<OperationID, size_t> op_count;

    for (auto& record : _records) {
        images.emplace_back(record.get_image().get_file_path());

        const std::vector<std::unique_ptr<Operation>>& op_log = record.get_log();
        for (const std::unique_ptr<Operation>& op : op_log) {
            OperationID op_id = get_op_id(op.get());

            ++op_count[op_id];
        }
    }

    std::vector<Session::Info::OperationInfo> op_info;
    for (const auto& op_iter : op_count) {
        op_info.emplace_back(op_iter.first, op_iter.second);
    }
    return Info(_id, images, op_info);
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

const Image& Session::OperationsRecord::get_image() const {
    return *_image;
}

const std::vector<std::unique_ptr<Operation>>&
Session::OperationsRecord::get_log() const {
    return _operations;
}

Session::Info::Info(uint64_t id, const std::vector<std::string>& images,
                    const std::vector<Session::Info::OperationInfo>& op_info)
    : _id(id), _images(images), _op_info(op_info) {}

uint64_t Session::Info::get_id() const {
    return _id;
}

const std::vector<std::string>& Session::Info::get_images() const {
    return _images;
}

const std::vector<Session::Info::OperationInfo>&
Session::Info::get_operations_info() const {
    return _op_info;
}

Session::Info::OperationInfo::OperationInfo(OperationID id, size_t count)
    : _id(id), _count(count) {}

size_t Session::Info::OperationInfo::get_count() const {
    return _count;
}

OperationID Session::Info::OperationInfo::get_id() const {
    return _id;
}