#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <iostream>

class ControlUnit;

/* To write specific code, the derived classes of Instruction should be used.
 * Each derived class has a specific task,
 * and these tasks are implemented in the executeby functions.
*/

/// Abstract Instruction class
class Instruction{
    int operand;        /// The instruction's address or constant value in case of VAR instruction.
public:
    /// Constructor.
    /// @param operand - address or constant
    Instruction(int operand):operand(operand){}

    /// Get the operand.
    /// @return instruction's address or constant
    int getOperand(){return operand;}

    /// Executes the appropriate instruction.
    /// @param CU - Control Unit to execute the instruction
    virtual void executeby(ControlUnit& CU) = 0;

    /// Creates a dynamic copy of the instruction.
    /// @return pointer to the dynamically created object
    virtual Instruction* clone() = 0;

    /// Default destructor
    virtual ~Instruction() {}
};

/// LOAD class
class LOAD: public Instruction{
public:
    /// Constructor.
    /// @param operand - the address from which the data will be loaded
    LOAD(int operand): Instruction(operand){}

    /// Fetches the operand at the operand address from the Control Unit,
    /// then loads it into the accumulator.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of LOAD.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~LOAD(){}
};

/// STORE class
class STORE: public Instruction{
public:
    /// Constructor.
    /// @param operand - the address where the data will be stored
    STORE(int operand): Instruction(operand){}

    /// Fetches the value from the accumulator, creates a VAR object,
    /// and stores it at the operand address.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of STORE.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~STORE(){}
};

/// ADD class
class ADD: public Instruction{
public:
    /// Constructor.
    /// @param operand - the address of the constant to be added to the accumulator
    ADD(int operand): Instruction(operand){}

    /// Adds the constant at the operand address to the accumulator.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of ADD.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~ADD(){}
};

/// SUB class
class SUB: public Instruction{
public:
    /// Constructor.
    /// @param operand - the address of the constant to be subtracted from the accumulator
    SUB(int operand): Instruction(operand){}

    /// Subtracts the constant at the operand address from the accumulator.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of SUB.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~SUB(){}
};

/// READ class
class READ: public Instruction{
public:
    /// Constructor
    /// @param operand - address where the data will be saved
    READ(int operand): Instruction(operand){}

    /// Reads the input value and stores it as a constant at the operand address.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of READ.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~READ(){}
};

/// PRINT class
class PRINT: public Instruction{
public:
    /// Constructor
    /// @param operand - address whose value needs to be printed
    PRINT(int operand): Instruction(operand){}

    /// Fetches the data at the operand address and prints its value.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of PRINT.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~PRINT(){}
};

/// JUMP class
class JUMP: public Instruction{
public:
    /// Constructor.
    /// @param operand - address of the next instruction to be executed
    JUMP(int operand): Instruction(operand){}

    /// Sets the Program Counter (PC) to the operand's value.
    /// Throws an exception if the jump target is outside the memory range.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of JUMP.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~JUMP(){}
};

/// BRANCHGT class
class BRANCHGT: public Instruction{
public:
    /// Constructor.
    /// @param operand - address of the next instruction to be executed
    BRANCHGT(int operand): Instruction(operand){}

    /// If the accumulator's value is greater than zero, sets the Program Counter (PC)
    /// to the operand's value.
    /// Throws an exception if the jump target is outside the memory range.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU);

    /// Creates a dynamic instance of BRANCHGT.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~BRANCHGT(){}
};

/* Special Instruction to store constants */
/// VAR class
class VAR: public Instruction{
public:
    /// Constructor
    /// @param operand - constant value
    VAR(int operand): Instruction(operand){}

    /// Cannot execute a variable instruction. Throws an exception.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU){ throw "Tried to execute a variable!\n";}

    /// Creates a dynamic instance of VAR.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~VAR(){}
};

/// EXIT class
class EXIT: public Instruction{
public:
    /// Constructor
    /// @param operand - constant value
    EXIT(int operand): Instruction(operand){}

    /// Terminates the program. Throws an exception.
    /// @param CU - Control Unit
    void executeby(ControlUnit& CU){ throw "Code exited\n";}

    /// Creates a dynamic instance of EXIT.
    /// @return pointer to the created instance
    Instruction* clone();

    /// Destructor
    ~EXIT(){}
};


#endif // INSTRUCTION_H_INCLUDED
