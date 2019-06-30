#pragma once

#include <utils/Formatter.hpp>
#include <utils/Types.hpp>

#include <sessions/Session.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @returns true if the command requires arguments.
 */
static bool needs_args(const std::string& cmd) {
    return cmd == "load" || cmd == "rotate" || cmd == "session" || cmd == "add"
           || cmd == "switch";
}

/**
 * Get a command @param cmd.
 */
static std::string get_cmd(std::istream& in) {
    std::string cmd;
    std::cin >> cmd;
    return cmd;
}

/**
 * Get the appropriate arguments from @param in for the command @param cmd.
 */
static std::vector<std::string> get_args_for(const std::string& cmd, std::istream& in) {
    std::vector<std::string> args;
    if (needs_args(cmd)) {
        std::string args_line;
        getline(std::cin, args_line);
        std::stringstream args_parser(args_line);

        std::string arg;
        while (args_parser >> arg) {
            args.push_back(arg);
        }
    }
    return args;
}

/**
 * Check if @params args has at least one element.
 *
 * @throws std::logic_error if args doesn't have at least one element.
 */
static void args_check(const DelayLoad<std::vector<std::string>>& args,
                       const std::string& cmd) {
    if (!args || args->size() == 0) {
        throw std::logic_error(Formatter()
                               << "Expected argument to '" << cmd << "' operation!");
    }
}

/**
 * Get string representation of @param operation_id
 */
static std::string get_operation_name(TransformationID operation_id) {
    switch (operation_id) {
    default:
        throw std::invalid_argument("Unknown operation!");
    }
}

/**
 * Writes information about a session to the output.
 *
 * @param [in] session_info Info for session in generic format.
 * @param [in] out Where to output.
 */
static void write_session_info(const Session::Info& session_info, std::ostream& out) {
    std::cout << "You switched to session with ID: " << session_info.get_id() << "!"
              << std::endl;

    std::cout << "Name of images in the session:";
    for (const std::string& image : session_info.get_images()) {
        std::cout << " " << image;
    }
    std::cout << std::endl;

    std::cout << "Pending transformations:";
    for (const auto& operation_info : session_info.get_transformations_info()) {
        std::cout << " " << operation_info.get_count() << "*"
                  << get_operation_name(operation_info.get_id());
    }
    std::cout << std::endl;
}

/**
 * Prints a welcome message.
 */
void welcome() {
    std::cout << "Welcome to Raster CLI!" << std::endl;
    std::cout << "An application developed by Yoanna Nikolova and Ivan Mollov."
              << std::endl;

    std::cout << std::endl;

    std::cout << "Tips: " << std::endl;
    std::cout << "* If you're in trouble you can use the 'help' command." << std::endl;
    std::cout
        << "* If you need info for a particular command you can run 'help <command>'."
        << std::endl;
    std::cout << std::endl;
}

/**
 * Prints prompt to the standard output.
 */
void prompt() {
    std::cout << "> ";
}
