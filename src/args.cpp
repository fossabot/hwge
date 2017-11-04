#include <hwge/args.hpp>

HWGE::Args::Args(int argc, char** argv) {
    begin = argv;
    end = argv + argc;
}

std::string HWGE::Args::getOption(const std::string &option) {
    char** itr = std::find(begin, end, option);

    if(itr != end && ++itr != end) {
        return *itr;
    }

    return 0;
}

bool HWGE::Args::hasOption(const std::string &option) {
    return std::find(begin, end, option) != end;
}