#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"
#include "list.h"

bool getArgument(std::stringstream& ss, int& value, const std::string& command) {
    if (!(ss >> value)) {
        std::cerr << "Error: Invalid argument for " << command << std::endl;
        return false;
    }
    return true;
}

int main() {
    Stack* stack = stack_create();
    int vars[4] = { 0, 0, 0, 0 };
    std::string line;
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        std::cout << "Executing: " << command << std::endl;

        if (command == "bipush") {
            int value;
            if (getArgument(ss, value, command)) {
                stack_push(stack, value);
            }
        }
        else if (command == "pop") {
            if (!stack_empty(stack)) {
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty" << std::endl;
            }
        }
        else if (command == "imul" || command == "iand" || command == "ior" || command == "ixor" || command == "iadd" || command == "isub") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    if (command == "imul") {
                        stack_push(stack, op1 * op2);
                    }
                    else if (command == "iand") {
                        stack_push(stack, op1 & op2);
                    }
                    else if (command == "ior") {
                        stack_push(stack, op1 | op2);
                    }
                    else if (command == "ixor") {
                        stack_push(stack, op1 ^ op2);
                    }
                    else if (command == "iadd") {
                        stack_push(stack, op1 + op2);
                    }
                    else if (command == "isub") {
                        stack_push(stack, op1 - op2);
                    }
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for " << command << std::endl;
                    stack_push(stack, op2);
                }
            }
            else {
                std::cerr << "Error: Not enough operands on stack for " << command << std::endl;
            }
        }
        else if (command == "iload_0") {
            stack_push(stack, vars[0]);
        }
        else if (command == "iload_1") {
            stack_push(stack, vars[1]);
        }
        else if (command == "iload_2") {
            stack_push(stack, vars[2]);
        }
        else if (command == "iload_3") {
            stack_push(stack, vars[3]);
        }
        else if (command == "istore_0") {
            if (!stack_empty(stack)) {
                vars[0] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_0)" << std::endl;
            }
        }
        else if (command == "istore_1") {
            if (!stack_empty(stack)) {
                vars[1] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_1)" << std::endl;
            }
        }
        else if (command == "istore_2") {
            if (!stack_empty(stack)) {
                vars[2] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_2)" << std::endl;
            }
        }
        else if (command == "istore_3") {
            if (!stack_empty(stack)) {
                vars[3] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_3)" << std::endl;
            }
        }
        else if (command == "swap") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op2);
                    stack_push(stack, op1);
                }
                else {
                    std::cerr << "Error: Not enough elements on stack for swap" << std::endl;
                    stack_push(stack, op2);
                }
            }
            else {
                std::cerr << "Error: Not enough elements on stack for swap" << std::endl;
            }
        }
        else if (command == "invokestatic") {
            int address;
            if (getArgument(ss, address, command)) {
                std::stringstream ss_addr;
                ss_addr << address << "*";
                int returnAddress;
                ss_addr >> returnAddress;
                stack_push(stack, returnAddress);
                std::cout << "Calling function at address: " << address << std::endl;
            }
        }
        else if (command == "return") {
            if (!stack_empty(stack)) {
                std::stringstream ss_return;
                int returnAddress = stack_get(stack);
                stack_pop(stack);
                ss_return << returnAddress;
                std::string returnAddressStr;
                ss_return >> returnAddressStr;
                if (returnAddressStr.find('*') == std::string::npos) {
                    std::cerr << "Error: Invalid return address: " << returnAddress << std::endl;
                }
                else {
                    std::cout << "Returning from function" << std::endl;
                }
            }
            else {
                std::cerr << "Error: Return address not found on stack" << std::endl;
            }
        }
        else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    inputFile.close();

    std::cout << "stack:" << std::endl;

    while (!stack_empty(stack)) {
        Data value = stack_get(stack);
        std::cout << value << std::endl;
        stack_pop(stack);
    }

    std::cout << "vars:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << vars[i] << std::endl;
    }

    stack_delete(stack);

    return 0;
}
