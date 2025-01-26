#ifndef CONTROLUNIT_H_INCLUDED
#define CONTROLUNIT_H_INCLUDED

#include "Instruction.h"
#include <iostream>

/// MemoryUnit class
/* This class contains a heterogeneous collection that stores instructions.
 * The array contains instructions in one segment, followed by constants.
 */
class MemoryUnit{
    int MAR;                    /// Memory Address Register
    Instruction* MDR;           /// Memory Data Register
    Instruction** memory;       /// Memory, stores instructions
    size_t storage;             /// Memory size
public:
    /// Constructor.
    /// Reads data from a file and stores it in dynamically allocated memory.
    /// @param filename - the file from which to read the data
    MemoryUnit(std::string filename);

    /// Strips leading zeros from a string and converts it to an integer.
    /// @param hex - the string to be converted to an integer
    /// @return the integer after removing leading zeros
    int HextoInt(std::string hex);

    /// Set MAR.
    /// @param address - the address to read or write
    void setMAR(int address){ MAR=address; }

    /// Set MDR.
    /// @param mdr - temporarily stores the current memory operation
    void setMDR(Instruction* mdr){ MDR=mdr; }

    /// Get MDR.
    /// @return the current value of MDR
    Instruction* getMDR(){ return MDR; }

    /// Reads the instruction at the MAR address into the MDR.
    void readEnable(){ MDR=memory[MAR]; }

    /// Writes the MDR content to the MAR address.
    void writeEnable(){ delete memory[MAR]; memory[MAR] = MDR; }

    /// Get storage.
    /// @return the current value of storage
    size_t getStorage(){ return storage;}

    /// Reads data from the specified file and stores it in the memory.
    /// @param filename - the name of the file to read from
    void FileReader(std::string filename);

    /// Checks if the memory has been allocated properly.
    /// @return true if the memory has not been allocated (nullptr), false if memory is allocated
    bool NotValidMemory(){
        if(memory == nullptr){
            return true;
        }
        return false;
    }

    /// Deletes dynamically allocated memory.
    ~MemoryUnit();
};

/// ProcessingUnit class
class ProcessingUnit{
    int ACC;     /// Accumulator, temporarily stores calculated results and loaded constants
public:
    /// Set ACC.
    /// @param acc - the current constant
    void setACC(int acc){ ACC = acc; }

    /// Get ACC.
    /// @return the current value of ACC
    int getAcc(){ return ACC;}

    /// Adds the given value to the ACC.
    /// @param value - value to add
    void add(int value){ ACC = ACC + value; }

    /// Subtracts the given value from the ACC.
    /// @param value - value to subtract
    void sub(int value){ ACC = ACC - value; }
};

/// IOUnit class
class IOUnit{
    std::ostream& os;   /// Reference to an output stream to write data to
    std::istream& is;   /// Reference to an input stream to read data from
public:
    /// Constructor.
    /// @param os - output stream
    /// @param is - input stream
    IOUnit(std::ostream& os, std::istream& is): os(os), is(is){}

    /// Prints a constant to the output stream.
    /// @param var - the constant to be printed
    void print(int var);

    /// Reads an integer from the input stream.
    /// @return the read integer
    int read();
};

/// ControlUnit class
class ControlUnit: public ProcessingUnit, public MemoryUnit, public IOUnit{
    int PC=0;               /// Program Counter, indicates the next instruction address
    Instruction* IR=0;      /// Stores the current instruction to be executed
public:
    /// Constructor.
    /// @param filename - the file to read
    /// @param os - the stream to write to
    /// @param is - the stream to read from
    ControlUnit(std::string filename, std::ostream& os=std::cout, std::istream& is=std::cin):MemoryUnit(filename), IOUnit(os, is){}

    /// Set PC.
    /// @param val - the next instruction address
    void setPC(int val){ PC=val; }

    /// Get PC.
    /// @return the current value of PC
    int getPC() {return PC;}

    /// Fetches the instruction based on the program counter and executes it.
    void cycle();

    /// Fetches the instruction from memory using the given address.
    /// @param address - the instruction address
    /// @return a pointer to the instruction
    Instruction* fetch(int address);
};

#endif // CONTROLUNIT_H_INCLUDED
