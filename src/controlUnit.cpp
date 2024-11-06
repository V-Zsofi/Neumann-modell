#include "controlUnit.h"
#include <iostream>
#include <fstream>

/// Prints the result or the value based on the output stream.
void IOUnit::print(int var)
{
    if(&os == &std::cout){
        os << "Result: " << var << std::endl;
    }
    else{
        os << var << std::endl;
    }
}

/// Reads an integer from the input, handles invalid input, and returns the integer.
int IOUnit::read()
{
    int val = 0;
    std::string wrongI;
    if (&is == &std::cin)
        os << "input: ";  // Prompt user for input if from std::cin
    
    is >> val;

    if (is.fail())  // Check for failed input (invalid data)
    {
        is.clear();  // Clear the input stream's error state
        is >> wrongI;  // Read the invalid input as a string
        std::cerr << "[" + wrongI + "]" + " is a wrong input\n";  // Print error message
        return val;  // Return current (possibly invalid) value
    }

    return val;  // Return valid input
}

/// Executes a single cycle, fetching and executing the next instruction.
void ControlUnit::cycle()
{
    IR = fetch(PC);  // Fetch instruction at the current PC
    PC++;  // Increment program counter
    if (IR != nullptr)
        IR->executeby(*this);  // Execute the fetched instruction
}

/// Fetches an instruction from memory based on the current PC.
Instruction *ControlUnit::fetch(int address)
{
    setMAR(address);  // Set the memory address register
    readEnable();     // Enable reading from memory
    return getMDR();  // Return the instruction stored in the MDR
}

/// Converts a hexadecimal string (e.g., "0x0010") to an integer, ignoring leading zeros.
int MemoryUnit::HextoInt(std::string hex)
{
    size_t i = 2;  // Skip "0x" prefix
    while (i < hex.length() && hex[i] == '0')  // Skip leading zeros
        i++;
    int result = 0;
    while (i < hex.length())  // Convert the remaining characters to an integer
    {
        result = result * 10 + (hex[i] - '0');  // Convert each character to a numeric value
        i++;
    }
    return result;  // Return the integer value
}

/// Constructor for MemoryUnit, reads file content into memory.
MemoryUnit::MemoryUnit(std::string filename)
{
    try
    {
        FileReader(filename);  // Read the file and initialize memory
    }
    catch (const char *e)
    {
        std::cout << e << '\n';  // Output error if file reading fails
    }
}

/// Reads instructions from the file and populates the memory array.
void MemoryUnit::FileReader(std::string filename)
{
    std::ifstream file;
    file.open("input\\" + filename);  // Open file from the "input" directory
    if (!file){
        memory = nullptr;  // If file fails to open, set memory to nullptr
        throw "File open failed.\n";  // Throw an error message
    }

    std::string op = "0x0000";
    file >> op;
    storage = HextoInt(op);  // Set storage size from the file content
    memory = new Instruction *[storage];  // Allocate memory for instructions
    for (size_t i = 0; i < storage; i++)
        memory[i] = nullptr;  // Initialize all memory slots to nullptr

    std::string position;
    std::string instructionType;

    // Read instructions and store them in memory
    while (file >> position >> instructionType >> op)
    {
        if (instructionType == "STORE")
            memory[HextoInt(position)] = STORE(HextoInt(op)).clone();
        else if (instructionType == "READ")
            memory[HextoInt(position)] = READ(HextoInt(op)).clone();
        else if (instructionType == "ADD")
            memory[HextoInt(position)] = ADD(HextoInt(op)).clone();
        else if (instructionType == "SUB")
            memory[HextoInt(position)] = SUB(HextoInt(op)).clone();
        else if (instructionType == "BRANCHGT")
            memory[HextoInt(position)] = BRANCHGT(HextoInt(op)).clone();
        else if (instructionType == "JUMP")
            memory[HextoInt(position)] = JUMP(HextoInt(op)).clone();
        else if (instructionType == "PRINT")
            memory[HextoInt(position)] = PRINT(HextoInt(op)).clone();
        else if (instructionType == "LOAD")
            memory[HextoInt(position)] = LOAD(HextoInt(op)).clone();
        else if (instructionType == "VAR")
            memory[HextoInt(position)] = VAR(HextoInt(op)).clone();
        else if (instructionType == "EXIT")
            memory[HextoInt(position)] = EXIT(HextoInt(op)).clone();
    }
    file.close();  // Close the file after reading
}

/// Destructor to clean up dynamically allocated memory.
MemoryUnit::~MemoryUnit()
{
    if (memory != nullptr)
    {
        for (size_t i = 0; i < storage; i++)
        {
            delete memory[i];  // Delete each instruction in memory
        }
        delete[] memory;  // Delete the memory array itself
    }
}
