#include <string>
using namespace std;
#include "mylog.h"

int main()
{
    string dir = "logs";
    string name = "file";

    init_log(dir, name);

    for (int i = 0; i != 100000; i++)
    {
        LOG(trace) << "Message 1";
        LOG(debug) << "Message 2";
        LOG(info) << "Message 3";
        LOG(warning) << "Message 4";
        LOG(error) << "Message 5";
        LOG(fatal) << "Message 6";
    }
}
