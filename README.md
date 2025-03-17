# RISC-V Simulator
RISC-V simulator for ECE-586 at PSU

## Goal
The goal of this project is to create a RISC-V simulator that simulates the base integer ISA from the [RISC-V Standard](https://drive.google.com/file/d/1uviu1nH-tScFfgrovvFCrj7Omv8tFtkp/view).
Specifically focusing on 2.2 - 2.6. This simulator is compliant with all instruction set guidelines as well
as providing traps for misalligned jump instructions or retrieving 0x00000000 from the instruction memory cache.
This simulator should provide all register, memory, and PC mappings as expected in a real machine along with setting up
appropriate register mappings and behaviors. Extensive integration and unit testing were provided to give full confidence
in the sytems working behavior.

## Setup
There are two aspects of the project, building the simulator and running unit tests.

### Run Unit Test
`make test`

This will compile all needed files for the unit test and auto run unit testing. It will provide necessary outputs for the
unit tests including any errors and where they were found. This is a self boot strapped unit test as G-Test suite was not
available on the school computers. Future work should include the entire G-Test suite for a more formal unit test framework.

### Run the simulator
`make build` or `make build DEBUG=true`

The former will build the unit tests without the -DDEBUG flag while the latter will. Suggestion is to not run with DEBUG
unless in active development.

To run the simulator you should always provide a flag using `-f`.

EX: `./bin/RVSIM -f <path_to_test>.mem`

This simulator will take files not with the .mem extension but do not expect appropriate behavior. 

You can set the PC with the `-p <value>` flag and the stack pointer (SP) with the `-s <value>` flag. These can take decimal or hexadecimal
values.

There is an active debugger mode called RISC-V Debugger (rdb) that can be activated using the `-d` flag.

For verbose mode use `-v` to get prints per instruction ran along with a printout of the register files.

All information can be found using the help flag by running `./bin/RVSIM -h` which provides helpful examples of how to run the
simulator and what each flag does.
