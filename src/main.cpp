#include "emerald/Application.hpp"

int main()
{
    emerald::Application app;

    if (app.init() != 0)
        return -1;

    app.run();

    app.shutdown();

    return 0;
}