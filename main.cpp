#include <iostream>
#include <stdlib.h>
#include "MultiPlayer.h"
#include "GameView.h"
#include "optionparser.h"

using namespace std;

enum optionIndex {HELP, COUNT, FIRST, SECOND};
const option::Descriptor usage[] = {
        {HELP, 0, "h", "help", option::Arg::None, "  --help  \tPrint usage and exit."},
        {COUNT, 1, "c", "count", option::Arg::Optional, }
};

int main(int argc, char* argv[]) {
    argc -= (argc > 0);
    argv += (argc>0); // skip program name argv[0] if present
    option::Stats stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);
    if (parse.error()) {
        return 1;
    }

    if (options[HELP]) {
        std::cout << "help";
        return 0;
    }

    GameView gameView;
    gameView.startScreen();
    return 0;
}