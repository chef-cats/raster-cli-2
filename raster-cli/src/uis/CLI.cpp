#include <ui/CLI.hpp>

#include <iostream>
#include <sstream>

static bool needs_args(const std::string& cmd) {
  return cmd == "load" || cmd == "rotate" || cmd == "load" || cmd == "session"
         || cmd == "switch";
}

CLI::CLI() : _should_run(true) {}

void CLI::capture_event() {
  std::string cmd;
  std::cin >> cmd;

  std::vector<std::string> args;
  if (needs_args(cmd)) {
    std::string args_line;
    getline(std::cin, args_line);
    std::stringstream args_parser(args_line);

    while (args_parser) {
      std::string arg;
      std::cin >> arg;
      args.push_back(arg);
    }
  }

  if (args.size() != 0) {
    _last_event = Event(cmd, args);
  } else {
    _last_event = Event(cmd);
  }
}

void CLI::handle_last_event() {
  if (!_last_event) {
    throw std::logic_error("No previous events!");
  } else if (_last_event->_cmd == "exit") {
    _should_run = false;
    return;
  } else if (_last_event->_cmd == "load") {
    if (_last_event->_args) {
      _sessions.emplace_back(get_unique_session_id(), _last_event->_args.get());
    } else {
      _sessions.emplace_back(get_unique_session_id());
    }

    _current_session = std::prev(_sessions.end());
  } else if (_last_event->_cmd == "grayscale") {
    _current_session->all_to_grayscale();
  } else if (_last_event->_cmd == "monochrome") {
    _current_session->all_to_monochrome();
  } else if (_last_event->_cmd == "negative") {
    _current_session->all_to_negative();
  } else if (_last_event->_cmd == "rotate") {
    Direction direction;
    if (!_last_event->_args) {
      throw std::logic_error("Expected argument to rotate operation!");
    } else if (_last_event->_args->at(0) == "left") {
      direction = Direction::LEFT;
    } else if (_last_event->_args->at(0) == "right") {
      direction = Direction::RIGHT;
    }
    /// @todo Validate args size.

    _current_session->rotate_all(direction);
  } else if (_last_event->_cmd == "undo") {
    /// @todo Implement.
  } else if (_last_event->_cmd == "add") {
    /// @todo Validation
    _current_session->add_image(_last_event->_args->at(0));
  } else if (_last_event->_cmd == "save") {
    _current_session->save_all();
  } else if (_last_event->_cmd == "session") {
    /// @todo Implement.

  } else if (_last_event->_cmd == "switch") {
    /// @todo Validate.
    const unsigned long long session_id = std::stoull(_last_event->_args->at(0));
    _current_session = _sessions.begin() + session_id;
  }
}

void CLI::run_event_loop() {
  while (_should_run) {
    handle_last_event();
  }
}

unsigned long long CLI::get_unique_session_id() const {
  return _sessions.size();
}

CLI::Event::Event(const std::string& cmd) : _cmd(cmd) {}

CLI::Event::Event(const std::string& cmd, const std::vector<std::string>& args)
    : _cmd(cmd), _args(args) {}