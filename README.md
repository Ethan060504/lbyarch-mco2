# [LBYARCH] MCO2: x86-to-C Interface Programming Project
* **Specifications:** [DAXPY (Double-precision A·X Plus Y)](./Project%20Specifications.pdf)
* **Course & Section:** LBYARCH - S20A
* **Developer:** Burayag, Ethan Axl S.

## Overview  
This project implements the DAXPY (Double-precision A·X + Y) kernel, forming a linear combination of two input vectors using a scalar multiplier. This is defined as:

```
Z[i] = A·X[i] + Y[i]
```

Where:
- **X, Y, and Z** are double-precision floating-point vectors  
- **A** is a double-precision scalar constant multiplier
- **0 ≤ i < n**, where **n** is the vector length  

This kernel is implemented and executed using two different programming approaches:

- **Standard C implementation**  
- **x86-64 Assembly implementation**, using scalar SIMD floating-point instructions  

The program measures and compares execution performance between both implementations using high-precision timing via `QueryPerformanceCounter()`. Each implementation is executed **30 times**, and average timings are computed to ensure reliable comparison.  

Finally, the program performs output correctness verification by comparing the C and assembly results element-by-element to ensure computational accuracy.

## Development Environment  
This project was created, developed, and tested using the following tools and configurations (as discussed in laboratory sessions):

- **NASM** — for assembling x86-64 assembly source  
- **TDM-GCC (MinGW-w64)** — for compiling the C source code and linking with assembly object files  
- The following executables are included in the system PATH:  
  - `nasm.exe`  
  - `gcc.exe`  
- **build.bat** — a batch script used to automate assembly, compilation, linking, and execution  

## Installation, Compilation, & Execution  
1. Download or clone the complete project folder onto your local machine.  
2. Ensure that **NASM** and **GCC** are installed and accessible through the system PATH.  
3. Open the `program` directory and run `build.bat` (either double-click it or execute via terminal).  
   This script will:  
   - assemble the x86-64 assembly source  
   - compile the C source  
   - link both object files into a single executable  
   - automatically run the final program  

## Disclaimer
The program uses pre-initialized input values for reproducibility during execution and testing. These values (vector size, scalar constant, and vector elements) can be modified and changed directly inside the C file if desired.

## AI Declaration
* ChatGPT was used as assistance in improving project documentation report.


