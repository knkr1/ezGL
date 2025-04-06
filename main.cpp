#include <iostream>

#include "easyGL.hpp"


int main()
{
    Size windowSize{800,600};
    Window window(windowSize,"hi",false,false);


    while (!window.shouldClose())
    {
        window.update();
    }

    return 0;
}
