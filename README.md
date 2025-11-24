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
3. Open the `src` directory and run `build.bat` (either double-click it or execute via terminal).  
   This script will:  
   1. assemble the x86-64 assembly source, 
   2. compile the C source,  
   3. link both object files into a single executable, and  
   4. automatically run the final program.  

## Disclaimer
The program uses pre-initialized input values for reproducibility during execution and testing. These values (vector size, scalar constant, and vector elements) can be modified and changed directly inside the C file if desired.

## Program Execution Output
The program execution below explains and shows the flow and sample output of the program:

---

### Input Values Initialization  
This section displays the initialized input values for the program, including the vector length (`n`), the scalar constant (`A`), and the contents of vectors `X` and `Y`.  
For readability, only the 1st 10 elements of each vector are shown in the program output.  
*(For this sample run, `n = 2^20`.)*  

![Input Values Initialization](./img/input_values_initialization.png)

---

### x86-64 Kernel Execution  
This section shows the execution of the DAXPY kernel using the x86-64 assembly implementation.  
The program performs the kernel execution **30 times**, records each execution time, and then calculates the total and average execution duration.  

![x86-64 Kernel Implementation Execution Time](./img/x86_implementation.png)

---

### C Kernel Execution  
This section shows the execution of the DAXPY kernel using the C implementation.  
Similar to the assembly execution, the kernel is run **30 times**, with execution times captured for each run, along with total and average runtime.  

![C Kernel Implementation Execution Time](./img/c_implementation.png)

---

### Execution Time Comparison  
This section presents the computed speedup comparison between the C and x86-64 implementations.  
The detailed interpretation and performance analysis will be discussed in the next section of this document.

![Execution Time Result Comparison](./img/comparison_results.png)

---

### Output Correctness Check
This screenshot displays a result-by-result correctness check between the C and x86-64 outputs.  
The program compares each element of `Z_C[i]` and `Z_x86[i]` to ensure mathematical equality.  
In the correct column:  
- `1` indicates values match  
- `0` indicates a mismatch  

Per the project specifications, only the 1st 10 elements need to be displayed in the program.

![Output Correctness Verification](./img/correctness_verification.png)

Based on the results of this program run, both C and x86-64 outputs produce the same and correct answers.

## Performance Analysis  

The DAXPY kernel was executed using three different vector sizes:  
- `n = 2^20`  
- `n = 2^24`  
- `n = 2^29`

For each implementation (C and x86-64 ASM), the kernel was executed 30 times, and the execution time was measured.
This section presents the raw measured runtimes, followed by computed averages and interpreted performance results.

---

### x86-64 ASM Implementation - Execution Time (seconds)

| Run # | 2^20 Time (sec) | 2^24 Time (sec) | 2^29 Time (sec) |
|-------|-----------------|-----------------|-----------------|
| 1  | 0.002899 | 0.043260 | 26.572782 |
| 2  | 0.001929 | 0.028171 | 72.010110 |
| 3  | 0.002433 | 0.029253 | 43.729105 |
| 4  | 0.001989 | 0.030693 | 36.716959 |
| 5  | 0.001868 | 0.030001 | 37.055581 |
| 6  | 0.002412 | 0.028983 | 36.937941 |
| 7  | 0.001702 | 0.028474 | 38.901797 |
| 8  | 0.002069 | 0.028098 | 38.067594 |
| 9  | 0.002227 | 0.029013 | 36.814180 |
| 10 | 0.001781 | 0.029518 | 46.450958 |
| 11 | 0.002647 | 0.028559 | 39.758271 |
| 12 | 0.001721 | 0.030626 | 38.601894 |
| 13 | 0.002087 | 0.029988 | 37.008749 |
| 14 | 0.001957 | 0.030121 | 37.643912 |
| 15 | 0.001843 | 0.029856 | 36.264551 |
| 16 | 0.002539 | 0.028920 | 38.411004 |
| 17 | 0.002695 | 0.029054 | 36.928800 |
| 18 | 0.002242 | 0.028920 | 36.661871 |
| 19 | 0.001945 | 0.028388 | 37.639188 |
| 20 | 0.001792 | 0.027725 | 35.956295 |
| 21 | 0.002532 | 0.029238 | 37.311513 |
| 22 | 0.001576 | 0.028096 | 35.820581 |
| 23 | 0.001822 | 0.028460 | 36.798529 |
| 24 | 0.002172 | 0.028836 | 35.528020 |
| 25 | 0.001888 | 0.028225 | 40.256273 |
| 26 | 0.002677 | 0.029431 | 38.046998 |
| 27 | 0.001799 | 0.027408 | 45.801159 |
| 28 | 0.001603 | 0.028304 | 36.485567 |
| 29 | 0.001914 | 0.027295 | 39.625678 |
| 30 | 0.001676 | 0.028898 | 35.146151 |
| **TOTAL**   | **0.062436** | **0.881810** | **1168.952010** |
| **AVERAGE** | **0.002081** | **0.029394** | **38.965067** |


--- 

### C Implementation - Execution Time (seconds)

| Run # | 2^20 Time (sec) | 2^24 Time (sec) | 2^29 Time (sec) |
|-------|-----------------|-----------------|-----------------|
| 1  | 0.003348 | 0.040551 | 69.382460 |
| 2  | 0.001726 | 0.024921 | 146.038143 |
| 3  | 0.002045 | 0.025886 | 30.214253 |
| 4  | 0.001939 | 0.025322 | 44.410646 |
| 5  | 0.001806 | 0.026890 | 26.615705 |
| 6  | 0.001714 | 0.026786 | 22.466619 |
| 7  | 0.001426 | 0.027231 | 20.170993 |
| 8  | 0.001681 | 0.027991 | 11.373193 |
| 9  | 0.001849 | 0.029524 | 9.424474 |
| 10 | 0.001599 | 0.025641 | 1.901584 |
| 11 | 0.001455 | 0.025276 | 0.778096 |
| 12 | 0.001927 | 0.024669 | 0.799184 |
| 13 | 0.001900 | 0.025791 | 0.799185 |
| 14 | 0.001707 | 0.027175 | 0.776839 |
| 15 | 0.001504 | 0.029452 | 0.782444 |
| 16 | 0.001854 | 0.024818 | 0.778968 |
| 17 | 0.001761 | 0.027557 | 0.773842 |
| 18 | 0.001603 | 0.028544 | 0.800068 |
| 19 | 0.001835 | 0.028491 | 0.834535 |
| 20 | 0.001723 | 0.028303 | 0.801076 |
| 21 | 0.001603 | 0.025525 | 0.785015 |
| 22 | 0.001955 | 0.027016 | 0.772360 |
| 23 | 0.001881 | 0.026061 | 0.774567 |
| 24 | 0.001403 | 0.027024 | 0.762676 |
| 25 | 0.002020 | 0.026456 | 0.780049 |
| 26 | 0.001720 | 0.024403 | 0.792829 |
| 27 | 0.001384 | 0.025102 | 0.790502 |
| 28 | 0.001763 | 0.025403 | 0.769065 |
| 29 | 0.001412 | 0.026194 | 0.776213 |
| 30 | 0.001899 | 0.027130 | 0.765519 |
| **TOTAL**   | **0.053441** | **0.811137** | **397.691096** |
| **AVERAGE** | **0.001781** | **0.027038** | **13.256370** |

---
### Execution Time Summary

| Vector Size | C Avg Time (sec) | ASM Avg Time (sec) | C Faster Than ASM (%) |
|-------------|------------------|--------------------|------------------------|
| 2^20        | 0.001781         | 0.002081           | 14.405815%            |
| 2^24        | 0.027038         | 0.029394           | 8.014551%             |
| 2^29        | 13.256370        | 38.965067          | 65.978835%            |

---

## Project Video Presentation and Demonstration
The link for the project video presentation and demonstration can be found here: <link>

## AI Declaration
* ChatGPT was used as assistance in improving project documentation report.


