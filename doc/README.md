# Overview
The goal of this project was to create a RISC-V ISA simulator that simulates the base integer instruction set from the [standard](https://drive.google.com/file/d/1uviu1nH-tScFfgrovvFCrj7Omv8tFtkp/view).
Specifically the base goal was to focus on sub-sections 2.2-2.6 and to implement all expected behavior based on the spec. The simulator
model should also appropriately model the register files, memory, and program counter (PC) and the appropriate interactions.
This means the simulator needed to appropriately simulate the fetch/decode/execute loop of a modern processor and handle all instructions
found within the base spec. The simulator had to verify expected behavior via robust unit testing and integration testing where actual
assembler code was written and verified using the GCC RISC-V toolchain. This simulator was built using modern C++20 and the standard
library. 

# Design
## Overview
The simulator used modern C++20 and a modular approach to build the system. An Object Oriented Programming (OOP) style was chosen that
grouped data based on unit functionality [EX: instruction opcodes determined data groupings]. Classes were broken up by headers and
source files that are grouped accordingly in the `include/` and `src/` dirctories. Inheritance was used for instruction classes
where the base class included virtual `decode(uint32_t)` and `execute()` methods that were expanded based on instruction behavior,
allowing abstraction of the instruction mapping. The standard library was heavily used to take advantage of containers as well as
compiler time checks to provide memory safety, [RAII standard practice](https://en.cppreference.com/w/cpp/language/raii), and ease
common programming mistakes during development. [Make](https://www.gnu.org/software/make/) was the chosen build system for the project
where unit testing was a custom boot-strapped system. A [V-model approach](https://dorleco.com/v-model-development-techniques-to-design/) 
was taken for design and testing.

## Main Entry Design
The project uses the `getopt()` operator from the base C-library to parse all command line arguments. A user can query command line
arguments using the `-h` flag to see all possible options.

The program then initializes the register class and memory class with the provided PC, SP, and file respectively. If no value is given
then the PC is set to 0, SP is set to 64Ki, and the file is `images/program.mem`. The register and memory object are implemented as 
unique_pointers to allow for better program safety over raw pointers and follow RAII standard. The program constructs the instruction map from the
`src/processor.cpp` file and begins the fetch/decode/execute loop along with the debugger if the mode was chosen. This runs in a hot
loop until the appropriate action is given to end the simulation or a trap is encountered. Finally, if verbose mode was not set, the register
file including the PC are printed out before exiting the program.

### Command line Flags
`-v` = verbose mode

`-p <value>` = PC

`-s <value>` = stack pointer

`-f <path/to/file>.mem` = test file to simulate

`-d` = run RISC-V debugger

## Processor
The processor is the main fetch/decode/execute entry point and the workhorse of the simulator. It uses the singelton register and memory
object pointers to get the PC, update the PC, and to read the instruction from memory. One of the major components of the processor is
the instruction map that takes a base instruction and places it into the hash table using the instruction opcode as the key. This allows
for easy flexibility for extending the instruction map as well as reusability if we wanted to simulate a multi-core processor. In the
`fetch()` function we run the fetch/decode/execute loop. As stated above we grab the instruction from memory using the PC, we then use
the lower 7 bits of the instruction to get the key for the instruction map. From this we return a reference (all instructions are stored
as smart pointers owned by the map so we do not want to transfer ownership in our design) to then execute the decode of the instruction
and execute the instruction. This modularity choice of separating instructions into classes in a hash map allows for ease of understanding
and debugging, as we can isolate failing instructions into a separate class allowing for debugging using integration and unit testing
techniques.

## Instructions
Instructions needed to satisfy the [RISC-V standard](https://drive.google.com/file/d/1uviu1nH-tScFfgrovvFCrj7Omv8tFtkp/view) for the base integer instruction class.
Because the project decided on an OOP approach, a decision had to be made on how to group data. We could group by execution unit (ALU and MEM), instruction encoding
(S-type, R-type, I-type), or opcode (seen on pg 571 of the standard). We decided on opcode because it eased translation layer for the map at
the expense of maybe redundant encoding types (multiple I-type encoded instructions are different data classes). Because we wanted easy
reuse and extension only, all classes inherit from a base class that includes three public functions: a `decode(uint32_t)`, `execute()`, and
destructor methods. Each instruction to inhereit form `instr.hpp` (it is a header only class) would then implement those 3 base types
per the spec. The project ended up with 9-base instruction classes:

`alu.cpp`

`alui.cpp`

`auipc.cpp`

`branch.cpp`

`jal.cpp`

`jalr.cpp`

`load.cpp`

`lui.cpp`

`store.cpp`

Again these were grouped by instruction opcode that can be found on pg.571 of the standard. These then implemented the base instructions
provided by the standard for each data grouping, using decode to select and then execute to follow through with the actual implementation
details of the instruction. This could then be easily expanded to future uses within the standard for non-base instructions such as
multiply or floating point. This polymorphism allowed for simpler code, code reuse, and makes additions to the existing project
seamless.

## Register and Memory
Register and Memory are singleton objects used throughout this project. They need to be a single living source of true information used by
every other part of the simulator. The implementation of these also used the standard library to ease common coding mistakes and nasty bugs.
The memory is a wrapper class around a hash map. This associative array allows the memory to grow as neeeded. The memory class does not protect
you from writing past the SP or reading from a memory location that hasn't been accessed yet. The register map uses the array container which 
provides built in safe guards for bounds checking. This also allows us to interact as if a normal raw-array in C without the pitfalls of checks
and uninitialized values.

# Testing
For this project we used the [V-model approach](https://dorleco.com/v-model-development-techniques-to-design/) which included integration and unit testing.

## Integration Testing
Our integration test can be found a [here](ECE586-project-Testplan.pdf). For the integration testing we used exclusively assembly code,
as C-code was decided didn't give enough of a benefit to mix and match the two possible test cases. Assembly code was not grouped by
objects but instead used the groupings per section header and sub headers between 2.2-2.6 inclusive. Therefore, when reading the testplan
beaware that [2.4.2] refers to the section | sub-section | tertiary-section of the provided standard. There you can see the tests. Case
analysis was used to the best of the groups ability to cover all possible edge cases. Integration tests can be found under the
`images/integration/` section, as the `test/` directory is reserved specifically for unit tests (NOTE: The Makefile makes it clear why
this distinction was made).

The integration test plan and testing team were two different groups with one overlap between a design member and test member to make sure
standardized communication was used. All PRs were reviewed by the design team after being reviewed informally by the test team. This allowed
for better pushback and error detection by separating these responsibilities and made sure everyone had clear ownership.

## Unit Testing
Unit testing was used to quickly verify and find bugs during design the design process. Thinking being, the quicker we shift testing
and debugging left, the quicker we can correct mistakes for cheaper. Unit testing was taken in two approaches:

1) Create a boot-strapped unit test framework using `make test` and the `test/` directory

2) Create custom .mem files where memory transitions were more applicable and use debugging tools to verify

### Boot-strapped test
The unit testing framework chose a boot-strapped approach because G-Test was not available on the design computers. We did not want separate
enviornments so it was important that the build server was unifrom among all team members. The boot-strapped unit tests are heavily
influenced by G-Test and common unit testing practices. Each object has its own test suite with a single entry point, each test entry point
has multiple sub-set tests it runs. Error is returned as a simple 0 (passed) or -1 (failed). This is bitwise OR'd through the process, allowing
for multiple tests and failures to happen, without preventing further tests down stream. Having a single test block all others from running
seemed counter productive to speed an the V-model. 6 major classes were tested using the boot-strapped unit tests.

### Specialized .mem unit test
Some classes were easier to create custom .mem files to test. This may have been because of memory, lack of mature testing framework at the
time, or designer choice. We did not want to prescribe such hard rules to the design team, so this was a perfectly acceptable method and
allowed us to catch some small integration bugs early. Users who created .mem tests were required to come up with an explanation framework
so the .mem could be easily interpreted from the results. Below are the .mem test excells that can be found under the `images/` root folder.

# Extra Credit
EC was attempted in this project by the team. Currently here is the list of EC that was completed:

1) Debugger with single step, print register, memory, and display current instruction (for separate commands)
    RISC-V debugger is set using the `-d` flag on the command line. When on the debugger use: `rdb> h` to get
    a list of possible run commands.
