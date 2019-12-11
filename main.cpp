#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "optionparser.h"
#include "GamePlay.h"

using namespace std;

struct Arg: public option::Arg {
    static void printError(const char* msg1, const option::Option& opt, const char* msg2) {
        fprintf(stderr, "%s", msg1);
        fwrite(opt.name, opt.namelen, 1, stderr);
        fprintf(stderr, "%s", msg2);
        std::cin.get();
    }

    static option::ArgStatus gamerType(const option::Option& option, bool msg) {
        if (strcmp(option.arg, "console") == 0 || strcmp(option.arg, "random") == 0 || strcmp(option.arg, "smart") == 0)
            return option::ARG_OK;

        if (msg) printError("Option '", option, "' requires a 'console', 'random' or 'smart' argument\n");
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus Numeric(const option::Option& option, bool msg) {
        char* endptr = 0;
        if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
        if (endptr != option.arg && *endptr == 0)
            return option::ARG_OK;

        if (msg) printError("Option '", option, "' requires a numeric argument\n");
        return option::ARG_ILLEGAL;
    }
};

enum optionIndex {HELP, COUNT, FIRST, SECOND};
const option::Descriptor usage[] = {
        {HELP, 0, "h", "help", Arg::None},
        {COUNT, 0, "c", "count", Arg::Numeric},
        {FIRST, 0, "f", "first", Arg::gamerType},
        {SECOND, 0, "s", "second", Arg::gamerType},
        { 0, 0, 0, 0, 0, 0 }
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
        GameView::printHelp();
        return 0;
    }

    int typeFirst = 2, typeSecond = 2, count = 1;

    if (options[FIRST]) {
        string typeFirst_s = options[FIRST].first()->arg;
        if (typeFirst_s == "console") {
            typeFirst = 1;
        }
        else if (typeFirst_s == "smart") {
            typeFirst = 3;
        }
    }

    if (options[SECOND]) {
        string typeSecond_s = options[SECOND].first()->arg;
        if (typeSecond_s == "console") {
            typeSecond = 1;
        }
        else if (typeSecond_s == "smart") {
            typeSecond = 3;
        }
    }

    if (options[COUNT]) {
        count = atoi(options[COUNT].first()->arg);
    }

    GamePlay gamePlay(typeFirst, typeSecond, count);
    gamePlay.startGame();

    return 0;
}