#include <operations/OperationsMock.hpp>

#include <sessions/Session.hpp>
#include <utils/HelperFunctions.hpp>

#include <unordered_map>

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
    std::unordered_map<TransformationID, size_t> op_count;

    for (auto& record : _records) {
        images.emplace_back(record.get_image().get_file_path());

        const std::vector<std::unique_ptr<Operation>>& op_log = record.get_log();
        for (const std::unique_ptr<Operation>& op : op_log) {
            TransformationID op_id = get_trans_id(op.get());

            ++op_count[op_id];
        }
    }

    std::vector<Session::Info::TransformationInfo> op_info;
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
                    const std::vector<Session::Info::TransformationInfo>& op_info)
    : _id(id), _images(images), _trans_info(op_info) {}

uint64_t Session::Info::get_id() const {
    return _id;
}

const std::vector<std::string>& Session::Info::get_images() const {
    return _images;
}

const std::vector<Session::Info::TransformationInfo>&
Session::Info::get_transformations_info() const {
    return _trans_info;
}

Session::Info::TransformationInfo::TransformationInfo(TransformationID id, size_t count)
    : _id(id), _count(count) {}

size_t Session::Info::TransformationInfo::get_count() const {
    return _count;
}

TransformationID Session::Info::TransformationInfo::get_id() const {
    return _id;
}