#pragma once

#include <sessions/Session.hpp>

/// @todo Implement generic UI interface class and inherit it.
class CLI {
  public:
    CLI();

    void capture_event();

    void handle_last_event();

    void run_event_loop();

  private:
    unsigned long long get_unique_session_id() const;

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
};