#include "test.h"
#include <iostream>
#include "instruction.h"
#include "controlUnit.h"
#include <algorithm>


int main()
{
    RunTest();
    bool exit = false;
    while (!exit)
    {
        std::cout << "Type exit to exit the program" << std::endl;
        std::string file;
        std::cout << "Filename: ";
        std::cin >> file;
        std::string tmpexit;
        tmpexit.resize(file.size());
        transform(file.begin(), file.end(), tmpexit.begin(), ::tolower);
        if (tmpexit == "exit")
        {
            break;
            exit = true;
        }
        ControlUnit CUmain(file); // Initializes the control unit with the input file
        bool cycleexit = CUmain.NotValidMemory();
        while (!cycleexit)
        {
            try
            {
                CUmain.cycle(); // Executes one cycle of the control unit
            }
            catch (const char *e)
            {
                std::cout << e << '\n';
                cycleexit = true; // Exits cycle if an exception occurs
            }
        }
    }

    return 0;
}