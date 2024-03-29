#include <uis/CLI.hpp>

#include "CLIUtils.hpp"
#include <utils/HelperFunctions.hpp>

CLI::CLI() : _should_run(true) {
    init_handlers();
}

void CLI::capture_event() {
    std::string cmd = get_cmd(std::cin);
    std::vector<std::string> args = get_args_for(cmd, std::cin);

    if (args.size() != 0) {
        _last_event = Event(cmd, args);
    } else {
        _last_event = Event(cmd);
    }
}

void CLI::handle_last_event() {
    const auto& cmd = get_cmd_alias();
    const auto& handler_it = _handlers.find(cmd);

    if (handler_it == _handlers.cend()) {
        throw std::invalid_argument(Formatter() << "Unknown operation'" << cmd << "'");
    } else {
        const auto& handler = handler_it->second;

        handler();
    }
}

void CLI::run_event_loop() {
    welcome();

    while (_should_run) {
        prompt();
        capture_event();
        handle_last_event();
    }
}

uint64_t CLI::get_unique_session_id() const {
    return _sessions.size();
}

void CLI::init_handlers() {

    _handlers["exit"] = [this]() { _should_run = false; };

    _handlers["load"] = [this]() {
        const auto& args = get_args_alias();

        _sessions.emplace_back(get_unique_session_id(), args);
        _current_session = std::prev(_sessions.end());
    };

    _handlers["grayscale"] = [this]() {
        _current_session->apply_transformation(TransformationID::TO_GRAYSCALE);
    };

    _handlers["monochrome"] = [this]() {
        _current_session->apply_transformation(TransformationID::TO_MONOCHROME);
    };

    _handlers["negative"] = [this]() {
        _current_session->apply_transformation(TransformationID::TO_NEGATIVE);
    };

    _handlers["rotate"] = [this]() {
        const auto& args = get_args_alias();

        const std::string& direction_token = args.at(0);

        Direction direction = parse_direction(direction_token);
        _current_session->apply_transformation(direction == Direction::LEFT
                                                   ? TransformationID::ROTATE_LEFT
                                                   : TransformationID::ROTATE_RIGHT);
    };

    _handlers["undo"] = [this]() { _current_session->undo_last_operation(); };

    _handlers["add"] = [this]() {
        const auto& args = get_args_alias();

        const std::string& image = args.at(0);
        _current_session->add_image(image);
    };

    _handlers["save"] = [this]() { _current_session->save_all(); };

    _handlers["session"] = [this]() {
        const auto& args = get_args_alias();

        if (args.at(0) == "info") {
            write_session_info(_current_session->get_info(), std::cout);
        } else {
            throw std::logic_error(Formatter()
                                   << "Unknown session operation '" << args.at(0) << "'");
        }
    };

    _handlers["switch"] = [this]() {
        const auto& args = get_args_alias();

        const uint64_t session_id = std::stoull(args.at(0));
        _current_session = _sessions.begin() + session_id;

        write_session_info(_current_session->get_info(), std::cout);
    };

    /// @todo Add 'help' operation.
}

const std::string& CLI::get_cmd_alias() const {
    if (!_last_event) {
        throw std::logic_error("No previous events!");
    }

    return _last_event->get_cmd();
}

const std::vector<std::string>& CLI::get_args_alias() const {
    if (!_last_event) {
        throw std::logic_error("No previous events!");
    }

    return _last_event->get_args();
}

CLI::Event::Event(const std::string& cmd) : _cmd(cmd) {}

CLI::Event::Event(const std::string& cmd, const std::vector<std::string>& args)
    : _cmd(cmd), _args(args) {}

const std::string& CLI::Event::get_cmd() const {
    return _cmd;
}

const std::vector<std::string>& CLI::Event::get_args() const {
    if (!_args) {
        throw std::logic_error("No arguments");
    }

    return _args.get();
}
