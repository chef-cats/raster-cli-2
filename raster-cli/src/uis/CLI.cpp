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

static void args_check(const DelayLoad<std::vector<std::string>>& args,
                       const std::string& cmd) {
  if (!args || args->size() == 0) {
    throw std::logic_error(Formatter()
                           << "Expected argument to '" << cmd << "' operation!");
  }
}

/// @todo Implement.
static std::string get_operation_name(const OperationID& operation_id) {
  return "";
}

static void write_session_info(const Session::Info& session_info, std::ostream& out) {
  std::cout << "You switched to session with ID: " << session_info.get_id() << "!"
            << std::endl;
  std::cout << "Name of images in the session:";
  for (const std::string& image : session_info.get_images()) {
    std::cout << " " << image;
  }
  std::cout << std::endl;
  std::cout << "Pending transformations:";
  for (const Session::Info::OperationInfo& operation_info :
       session_info.get_operations_info()) {
    std::cout << " " << operation_info.get_count() << "*"
              << get_operation_name(operation_info.get_id());
  }
  std::cout << std::endl;
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
  const auto& opt_args = _last_event->_args;

  if (needs_args(cmd)) {
    args_check(opt_args, cmd);
  }

  const auto& args = opt_args.get();

  ///  @todo Save operation handling functions in an unordered_map by ID
  if (cmd == "exit") {
    _should_run = false;
    return;
  } else if (cmd == "load") {
    _sessions.emplace_back(get_unique_session_id(), args);
    _current_session = std::prev(_sessions.end());
  } else if (cmd == "grayscale") {
    _current_session->all_to_grayscale();
  } else if (cmd == "monochrome") {
    _current_session->all_to_monochrome();
  } else if (cmd == "negative") {
    _current_session->all_to_negative();
  } else if (cmd == "rotate") {
    const std::string& direction_token = args.at(0);

    Direction direction = parse_direction(direction_token);
    _current_session->rotate_all(direction);
  } else if (cmd == "undo") {
    /// @todo Implement.
  } else if (cmd == "add") {
    const std::string& image = args.at(0);
    _current_session->add_image(image);
  } else if (cmd == "save") {
    _current_session->save_all();
  } else if (cmd == "session") {
    if (args.at(0) == "info") {
      write_session_info(_current_session->get_info(), std::cout);
    } else {
      throw std::logic_error(Formatter()
                             << "Unknown session operation '" << args.at(0) << "'");
    }
  } else if (cmd == "switch") {
    const unsigned long long session_id = std::stoull(args.at(0));
    _current_session = _sessions.begin() + session_id;

    write_session_info(_current_session->get_info(), std::cout);
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