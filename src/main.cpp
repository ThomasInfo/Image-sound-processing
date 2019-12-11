#include <iostream>
#include "Run.h"

using namespace cimg_library;
using namespace std;


int main() {

    Run program;

    //Program setup
    string filepath = program.chooseImagePath();
    bool color = program.isColored();
    int process = program.askUser();

    //Run
    program.run(process, color, filepath);

    return 0;
}

