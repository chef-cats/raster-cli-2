#include <operations/TransformationFactory.hpp>

#include <sessions/Session.hpp>
#include <utils/HelperFunctions.hpp>

#include <unordered_map>

Session::Session(uint64_t id, const std::vector<std::string>& images) : _id(id), _session_info(id) {
    _pending_image_transformations.reserve(images.size());
    for (size_t index = 0; index < images.size(); ++index) {
        add_image(images[index]);
    }
}

void Session::apply_transformation(TransformationID id) {
    std::unique_ptr<const Operation> transformation = create_transformation(id);
    add_transformation_to_all_images(std::move(transformation));
    _session_info.add_transformation(id);
}

void Session::undo_last_operation() {
    for (auto& record : _pending_image_transformations) {
        record.cancel_last_transformation();
    }
    _session_info.remove_last_transformation_info();
}

void Session::add_image(const std::string& image) {
    _pending_image_transformations.emplace_back(image);
}

void Session::save_all() {
    for (auto& record : _pending_image_transformations) {
        record.execute_transformations();
    }
    _session_info.remove_transformations_info();
}

SessionInfo Session::get_info() const {
    return _session_info;
}

void Session::add_transformation_to_all_images(std::unique_ptr<const Operation> operation) {
    for (auto& record : _pending_image_transformations) {
        record.add_transformation(std::move(operation));
    }
}

Session::PendingImageTransformations::PendingImageTransformations(const std::string& image)
    : _image(create_image(image)) {}

void Session::PendingImageTransformations::cancel_last_transformation() {
    _operations.pop_back();
}

void Session::PendingImageTransformations::add_transformation(
    std::unique_ptr<const Operation> operation) {
    _operations.emplace_back(std::move(operation));
}

void Session::PendingImageTransformations::execute_transformations() {
    for (const auto& operation : _operations) {
        _image->apply(*operation);
    }
}

const Image& Session::PendingImageTransformations::get_image() const {
    return *_image;
}
