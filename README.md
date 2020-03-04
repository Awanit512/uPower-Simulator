# uPowerSimulator

uPowerSimulator is the Instruction Set Simulator for the new **uPower** ISA, a subset of the **Power ISA** developed by the OpenPOWER Foundation, led by IBM. This is a course project done as a part of the course Computer Organization and Architecture (CS250), Department of Computer Science and Engineering, NITK Surathkal.

## Preliminaries:
- The project is written entirely in C.
- There are mainly two components: The Assembler and the Simulator.
- The code uses the Linux kernel coding style (https://www.kernel.org/doc/html/v4.10/process/coding-style.html).

## Adding New Instructions:

- Add a new if condition to the function `translate_instr()` funcition `src/uPowerSim.c`.
- Add a new translating function to the `src/instr_translator.c` with return type `int32_t` and an array of strings as parameter.
- The array contains the tokenized string instruction. For example, if the string instruction is `add R1, R2, R3` then the array is `instr_v`:
```C
1. instr_v[0] = "add",
2. instr_v[1] = "R1",
3. instr_v[2] = "R2",
4. instr_v[3] = "R3",
5. instr_v[4] = NULL.
```
- The function also takes `instr_c`, the number of elements in `instr_v`, which in this example is 4.
- For reference, the `add` function is written in the exact same format(Without the implementation). Contributors could follow  this format.

### Contributors:
- Suhas K S (181CO253) - https://github.com/suhasks123
- Sai Krishna Anand (181CO244) - https://github.com/CyberSkam
- Dhanwin Rao (181CO217) - https://github.com/dhanwin247
- Arnav Nair (181CO209) - https://github.com/ArnavNair
