#pragma once

#include <sessions/Session.hpp>

#include <unordered_map>

/// @todo Implement generic UI interface class and inherit it.
class CLI {
  public:
    static CLI* get_instance();

    CLI();

    void run_event_loop();

  private:
    void welcome() const;

    void prompt() const;

    void capture_event();

    void handle_last_event();

    unsigned long long get_unique_session_id() const;

    void init_handlers();

    const std::string& get_cmd_alias() const;

    const std::vector<std::string>& get_args_alias() const;

    struct Event {
        Event(const std::string& cmd);
        Event(const std::string& cmd, const std::vector<std::string>& args);

        std::string _cmd;
        boost::optional<std::vector<std::string>> _args;
    };

    bool _should_run;
    DelayLoad<Event> _last_event;
    std::vector<Session> _sessions;
    std::vector<Session>::iterator _current_session;
    std::unordered_map<std::string, std::function<void()>> _handlers;
};