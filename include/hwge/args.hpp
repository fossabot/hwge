#include <algorithm>
#include <string>

namespace HWGE {
    class Args {
    private:
        char** begin;
        char** end;
    
    public:
        Args(int argc, char** argv);
        std::string getOption(const std::string &option);
        bool hasOption(const std::string &option);
    };
};