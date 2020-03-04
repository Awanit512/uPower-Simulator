# uPowerSim

## Assembler:

The assembler is a simple two pass assembler where each pass has a specific function:

1.Pass 1:

- Text Segment: Here, for every label we encounter, an entry is added into the symbol table. Each entry in the symbol table consists of the name of the label and the relative address of the instruction it is referring to with respect to the first instruction in the text segment.

- Data Segment: Each label in the data segment corresponds to a particular space in memory, specifically static memory. We collect all these labels and add them into another symbol table which stores the name of the memory space, the type of data in the memory space and the data stored in it.

These tables are then written to a file (eg. 'file1.sym') in the same directory as the assembly file.

2.Pass 2:

- This is dedicated to converting the text commands to binary, written to a file as hex.


## Memory Management:

- Static Memory: The memory declared in the data section is allocated in the static memory space of the process. Details regarding allocating this memory is stored in the symbol table for data. These details are used by the simulator to allocate the memory for the process of the binary to be run.

- Dynamic Memory: As of now, there is no dynamic memory possible in the simulator. The stack memory of the process is resizable but is not technically 'dynamic' in the classic definition of that type of memory. The stack memory is accessed using the stack pointer, held in a general purpose register decided by the ISA.