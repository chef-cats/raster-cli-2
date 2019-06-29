#include <cstdlib>

#include <uis/CLI.hpp>

int main() {
    CLI cli;

	cli.run_event_loop();

    return EXIT_SUCCESS;
}