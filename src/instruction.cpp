#include "instruction.h"
#include "controlUnit.h"

void LOAD::executeby(ControlUnit& CU){
    // Fetches the instruction from memory using the operand address
    // and loads its operand into the accumulator.
    Instruction* var = CU.fetch(getOperand());
    CU.setACC(var->getOperand());
}

Instruction* LOAD::clone(){
    return new LOAD(*this);
}

void STORE::executeby(ControlUnit& CU){
    // Stores the value from the accumulator into memory at the operand address.
    CU.setMAR(getOperand());
    int val = CU.getAcc();
    VAR var(val);
    CU.setMDR(var.clone());
    CU.writeEnable(); // Enables the memory write operation
}

Instruction* STORE::clone(){
    return new STORE(*this);
}

void ADD::executeby(ControlUnit& CU){
    // Adds the value from memory at the operand address to the accumulator.
    Instruction* var = CU.fetch(getOperand());
    CU.add(var->getOperand());
}

Instruction* ADD::clone(){
    return new ADD(*this);
}

void SUB::executeby(ControlUnit& CU){
    // Subtracts the value from memory at the operand address from the accumulator.
    Instruction* var = CU.fetch(getOperand());
    CU.sub(var->getOperand());
}

Instruction* SUB::clone(){
    return new SUB(*this);
}

void READ::executeby(ControlUnit& CU){
    // Reads a value from input and stores it at the operand address in memory.
    int val = CU.read();
    VAR var(val);
    CU.setMAR(getOperand());
    CU.setMDR(var.clone());
    CU.writeEnable(); // Enables the memory write operation
}

Instruction* READ::clone(){
    return new READ(*this);
}

void PRINT::executeby(ControlUnit& CU){
    // Prints the value stored in memory at the operand address.
    Instruction* var = CU.fetch(getOperand());
    CU.print(var->getOperand());
}

Instruction* PRINT::clone(){
    return new PRINT(*this);
}

void JUMP::executeby(ControlUnit& CU){
    // Checks if the operand is within valid memory bounds and sets the Program Counter (PC).
    if(getOperand() < 0 || static_cast<size_t>(getOperand()) >= CU.getStorage())
        throw "Can't jump here\n"; // Invalid jump address
    CU.setPC(getOperand());
}

Instruction* JUMP::clone(){
    return new JUMP(*this);
}

void BRANCHGT::executeby(ControlUnit& CU){
    // Checks if the operand is within valid memory bounds and conditionally jumps if the accumulator > 0.
    if(getOperand() < 0 || static_cast<size_t>(getOperand()) >= CU.getStorage())
        throw "Can't jump here\n"; // Invalid jump address
    if(CU.getAcc() > 0)  // Only jumps if the accumulator's value is greater than 0
        CU.setPC(getOperand());
}

Instruction* BRANCHGT::clone(){
    return new BRANCHGT(*this);
}

Instruction* VAR::clone(){
    return new VAR(*this);
}

Instruction* EXIT::clone(){
    return new EXIT(*this);
}
