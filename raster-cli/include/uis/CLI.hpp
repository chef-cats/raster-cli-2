#pragma once

#include <sessions/Session.hpp>

#include <unordered_map>

/**
 * Represents a command line interface.
 */
class CLI {
  public:
    CLI();

    void run_event_loop();

  private:
    void capture_event();

    void handle_last_event();

    unsigned long long get_unique_session_id() const;

    void init_handlers();

    const std::string& get_cmd_alias() const;

    const std::vector<std::string>& get_args_alias() const;

    /**
     * Represents an event that can be handled by the CLI.
     *
     * The CLI has the ability to capture text. Because of that the events handled by it
     * represent a command and its arguments. 
     */
    struct Event {
        Event(const std::string& cmd);
        Event(const std::string& cmd, const std::vector<std::string>& args);

		const std::string& get_cmd() const;
        const std::vector<std::string>& get_args() const;

      private:
        std::string _cmd;
        boost::optional<std::vector<std::string>> _args;
    };

    bool _should_run; ///< If the event loop should stop or continue. Defaults to true.
    DelayLoad<Event> _last_event;   ///< Holds the last captured event.
    std::vector<Session> _sessions; ///< Holds the currently opened sessions.
    std::vector<Session>::iterator
        _current_session; ///< Points to the currently focused session.
    std::unordered_map<std::string, std::function<void()>>
        _handlers; ///< A map to the handlers for different operations.
};