#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "instruction.h"
#include "controlUnit.h"
#include "gtest_lite.h"

int main()
{
    std::cout << "Testing....." << std::endl;

    // Initializes the testing framework
    GTINIT(std::cin);

    // Test case to check if an error is thrown when trying to open a non-existing file
    TEST(MemoryUnit, BeolvasHiba)
    {
        MemoryUnit MemoryUnit("nem_letezik");  // Non-existent file

        // Verifies that the memory unit reports an invalid memory
        EXPECT_EQ(true, MemoryUnit.NotValidMemory());
    }
    END

    // Creates a Control Unit (CU) to execute the instructions from the Fibonacci file
    ControlUnit CU("Fb.txt");

    // Test case to check if the instructions are correctly read from the file
    TEST(Fibonaccisorozat, fajlbeolvas)
    {
        // Verifies the correctness of the Fibonacci sequence fetched from the file
        EXPECT_EQ(35, CU.fetch(0)->getOperand());
        EXPECT_EQ(30, CU.fetch(1)->getOperand());
        EXPECT_EQ(34, CU.fetch(2)->getOperand());
        EXPECT_EQ(31, CU.fetch(3)->getOperand());
        EXPECT_EQ(1, CU.fetch(34)->getOperand());
    }
    END

    // Test cases for checking the execution of different instructions (LOAD, STORE, ADD, SUB, etc.)
    TEST(LOAD, executeby)
    {
        // Tests the LOAD instruction execution
        LOAD load1(2);
        LOAD load2(34);
        load1.executeby(CU);
        EXPECT_EQ(34, CU.getAcc());  // Verifies accumulator value after loading operand
        load2.executeby(CU);
        EXPECT_EQ(1, CU.getAcc());  // Verifies accumulator value after second load
    }
    END

    TEST(STORE, executeby)
    {
        CU.setACC(15);  // Sets the accumulator value to 15
        STORE store1(3);
        store1.executeby(CU);  // Executes the STORE instruction
        EXPECT_EQ(15, CU.fetch(3)->getOperand());  // Verifies if the value is correctly stored
        CU.setACC(6);
        STORE store2(6);
        store2.executeby(CU);
        EXPECT_EQ(6, CU.fetch(6)->getOperand());
    }
    END

    TEST(ADD, executeby)
    {
        CU.setACC(5);  // Sets the accumulator value to 5
        ADD add1(2);
        add1.executeby(CU);  // Adds the operand value to the accumulator
        EXPECT_EQ(39, CU.getAcc());  // Verifies the updated accumulator value
        CU.setACC(10);
        ADD add2(0);
        add2.executeby(CU);
        EXPECT_EQ(45, CU.getAcc());
    }
    END

    TEST(SUB, executeby)
    {
        CU.setACC(15);
        SUB sub1(1);
        sub1.executeby(CU);  // Subtracts the operand value from the accumulator
        EXPECT_EQ(-15, CU.getAcc());  // Verifies the result after subtraction
        CU.setACC(40);
        SUB sub(35);
        sub.executeby(CU);
        EXPECT_EQ(40, CU.getAcc());
    }
    END

    TEST(JUMP, executeby)
    {
        // Tests the behavior of the JUMP instruction
        JUMP jump1(4);
        jump1.executeby(CU);
        EXPECT_EQ(4, CU.getPC());  // Verifies if the program counter is set correctly
        JUMP jump2(-2);  // Invalid jump (negative address)
        try
        {
            EXPECT_THROW_THROW(jump2.executeby(CU), const char *);
        }
        catch (const char *p)
        {
            EXPECT_STREQ("Cant jump here\n", p);  // Verifies the exception for invalid jump
        }
        JUMP jump3(100);  // Invalid jump (out of bounds)
        try
        {
            EXPECT_THROW_THROW(jump3.executeby(CU), const char *);
        }
        catch (const char *p)
        {
            EXPECT_STREQ("Cant jump here\n", p);
        }
    }
    END

    TEST(BRANCHGT, executeby)
    {
        // Tests the behavior of the BRANCHGT (branch if greater than zero) instruction
        CU.setACC(10);
        BRANCHGT branch(6);
        branch.executeby(CU);
        EXPECT_EQ(6, CU.getPC());  // Verifies the program counter after conditional jump
        CU.setACC(0);
        CU.setPC(10);
        BRANCHGT branch2(8);
        branch2.executeby(CU);  // No jump because the accumulator is not greater than 0
        EXPECT_EQ(10, CU.getPC());
        BRANCHGT branch3(-2);  // Invalid jump
        try
        {
            EXPECT_THROW_THROW(branch3.executeby(CU), const char *);
        }
        catch (const char *p)
        {
            EXPECT_STREQ("Cant jump here\n", p);
        }
        BRANCHGT branch4(100);  // Invalid jump (out of bounds)
        try
        {
            EXPECT_THROW_THROW(branch4.executeby(CU), const char *);
        }
        catch (const char *p)
        {
            EXPECT_STREQ("Cant jump here\n", p);
        }
    }
    END

    TEST(VAR, executeby)
    {
        // Tests if a variable instruction throws an exception when executed
        VAR var(10);
        try
        {
            EXPECT_THROW_THROW(var.executeby(CU), const char *);
        }
        catch (const char *p)
        {
            EXPECT_STREQ("Tried to execute a variable!\n", p);
        }
    }
    END

    TEST(EXIT, executeby)
    {
        // Tests if the EXIT instruction throws the correct exception
        EXIT exit(10);
        try
        {
            EXPECT_THROW_THROW(exit.executeby(CU), const char *);
        }
        catch (const char *p)
        {
            EXPECT_STREQ("Code exited\n", p);
        }
    }
    END

    // Test cases for PRINT and READ instructions with different ControlUnits
    TEST(READ, executeby)
    {
        // Tests the READ instruction functionality with different inputs
        std::istringstream input1("4");
        ControlUnit CU1("Fb.txt", std::cout, input1);
        READ read1(13);
        read1.executeby(CU1);
        EXPECT_EQ(4, CU1.fetch(13)->getOperand());  // Verifies the value read into memory
        std::istringstream input2("120");
        ControlUnit CU2("Fb.txt", std::cout, input2);
        READ read2(0);
        read2.executeby(CU2);
        EXPECT_EQ(120, CU2.fetch(0)->getOperand());
    }
    END

    TEST(PRINT, executeby)
    {
        // Tests the PRINT instruction functionality with output capture
        std::ostringstream output;
        ControlUnit CU("Fb.txt", output);
        PRINT print(19);
        print.executeby(CU);
        PRINT print2(34);
        print2.executeby(CU);
        std::istringstream expect(output.str());
        int val;
        expect >> val;
        EXPECT_EQ(32, val);  // Verifies the first printed value
        expect >> val;
        EXPECT_EQ(1, val);  // Verifies the second printed value
    }
    END

    // Tests the Fibonacci sequence with different values of 'n' (0, 1, 3, 9)
    TEST(Fibonacci, n = 0)
    {
        std::istringstream input1("0");
        std::ostringstream output;
        int val;
        ControlUnit CU1("Fb.txt", output, input1);
        while (true)
        {
            CU1.cycle();  // Executes one cycle of the control unit
            if (CU1.fetch(CU1.getPC())->getOperand() == 0)
            {
                std::istringstream expect(output.str());
                expect >> val;
                break;
            }
        }
        EXPECT_EQ(0, val);  // Verifies the correct Fibonacci value for n = 0
    }
    END

    // More Fibonacci tests for n = 1, n = 3, and n = 9 with expected results
    TEST(Fibonacci, n = 1)
    {
        std::istringstream input1("1");
        std::ostringstream output;
        int val;
        ControlUnit CU1("Fb.txt", output, input1);
        while (true)
        {
            CU1.cycle();
            if (CU1.fetch(CU1.getPC())->getOperand() == 0)
            {
                std::istringstream expect(output.str());
                expect >> val;
                break;
            }
        }
        EXPECT_EQ(1, val);  // Verifies the correct Fibonacci value for n = 1
    }
    END

    TEST(Fibonacc, n = 3)
    {
        std::istringstream input1("3");
        std::ostringstream output;
        int val;
        ControlUnit CU1("Fb.txt", output, input1);
        while (true)
        {
            CU1.cycle();
            if (CU1.fetch(CU1.getPC())->getOperand() == 0)
            {
                std::istringstream expect(output.str());
                expect >> val;
                break;
            }
        }
        EXPECT_EQ(2, val);  // Verifies the correct Fibonacci value for n = 3
    }
    END

    TEST(Fibonacc, n = 9)
    {
        std::istringstream input1("9");
        std::ostringstream output;
        int val;
        ControlUnit CU1("Fb.txt", output, input1);
        while (true)
        {
            CU1.cycle();
            if (CU1.fetch(CU1.getPC())->getOperand() == 0)
            {
                std::istringstream expect(output.str());
                expect >> val;
                break;
            }
        }
        EXPECT_EQ(34, val);  // Verifies the correct Fibonacci value for n = 9
    }
    END

    std::cout
        << "Testing done" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    // Main loop for interactive testing with user input
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
        ControlUnit CUmain(file);  // Initializes the control unit with the input file
        bool cycleexit = CUmain.NotValidMemory();
        while (!cycleexit)
        {
            try
            {
                CUmain.cycle();  // Executes one cycle of the control unit
            }
            catch (const char *e)
            {
                std::cout << e << '\n';
                cycleexit = true;  // Exits cycle if an exception occurs
            }
        }
    }

    GTEND(std::cerr);  // Ends the testing framework

    return 0;
}
