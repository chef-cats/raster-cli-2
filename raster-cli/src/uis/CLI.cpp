#include <ui/CLI.hpp>

#include <utils/Formatter.hpp>

#include <iostream>
#include <sstream>

static bool needs_args(const std::string& cmd) {
  return cmd == "load" || cmd == "rotate" || cmd == "load" || cmd == "session"
         || cmd == "switch";
}

static Direction parse_direction(const std::string& direction_token) {
  Direction direction;
  if (direction_token == "left") {
    direction = Direction::LEFT;
  } else if (direction_token == "right") {
    direction = Direction::RIGHT;
  } else {
    throw std::invalid_argument(Formatter()
                                << direction_token << " is not a valid direction!");
  }
  return direction;
}

static std::string get_cmd(std::istream& in) {
  std::string cmd;
  std::cin >> cmd;
  return cmd;
}

static std::vector<std::string> get_args_for(const std::string& cmd, std::istream& in) {
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
  return args;
}

CLI::CLI() : _should_run(true) {}

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
  if (!_last_event) {
    throw std::logic_error("No previous events!");
  }

  const auto& cmd = _last_event->_cmd;
  const auto& args = _last_event->_args;

  if (cmd == "exit") {
    _should_run = false;
    return;
  } else if (cmd == "load") {
    if (args) {
      _sessions.emplace_back(get_unique_session_id(), args.get());
    } else {
      _sessions.emplace_back(get_unique_session_id());
    }

    _current_session = std::prev(_sessions.end());
  } else if (cmd == "grayscale") {
    _current_session->all_to_grayscale();
  } else if (cmd == "monochrome") {
    _current_session->all_to_monochrome();
  } else if (cmd == "negative") {
    _current_session->all_to_negative();
  } else if (cmd == "rotate") {
    if (!args || args->size() == 0) {
      throw std::logic_error("Expected argument to 'rotate' operation!");
    }
    const std::string& direction_token = args->at(0);

    Direction direction = parse_direction(direction_token);
    _current_session->rotate_all(direction);
  } else if (cmd == "undo") {
    /// @todo Implement.
  } else if (cmd == "add") {
    if (!args || args->size() == 0) {
      throw std::logic_error("Expected argument to 'add' operation!");
    }
    const std::string& image = args->at(0);

    _current_session->add_image(image);
  } else if (cmd == "save") {
    _current_session->save_all();
  } else if (cmd == "session") {
    /// @todo Implement.
  } else if (cmd == "switch") {
    if (!args || args->size() == 0) {
      throw std::logic_error("Expected argument to 'switch' operation!");
    }
    const unsigned long long session_id = std::stoull(args->at(0));

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