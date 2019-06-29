#include <cstdlib>

#include <uis/CLI.hpp>

#include <memory>

int main() {
    CLI* cli = CLI::get_instance();

	cli->run_event_loop();

    return EXIT_SUCCESS;
}