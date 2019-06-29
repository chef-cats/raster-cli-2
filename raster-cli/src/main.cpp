#include <cstdlib>

#include <uis/CLI.hpp>

#include <memory>

int main() {
    CLI cli;

	cli.run_event_loop();

    return EXIT_SUCCESS;
}
