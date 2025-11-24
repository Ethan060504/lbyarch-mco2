// x86-to-C Interface Programming Project
// Burayag, Ethan Axl S. - S20A
// C File

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern void DAXPY_x86 (int n, double* X, double* Y, double* Z, double A);

void DAXPY_C (int n, double* X, double* Y, double* Z, double A) {
	int i;
	
	for (i = 0; i + 1 <= n; i++) {
		Z[i] = A * X[i] + Y[i];
	}
}

void print_divider () {
	printf("\n=======================================================================================\n\n");
}

int main () {
	print_divider();
	printf("Project:          x86-to-C Interface Programming\n");
	printf("Specifications:   DAXPY (Double-precision A x X Plus Y)\n");
	printf("Course & Section: LBYARCH - S20A\n");
	printf("Developer:        Burayag, Ethan Axl S.\n");
	print_divider();
	
	printf("Note: Program input values have been initialized already and directly into the program. \n      These can be changed by modifying the values in the program.\n\n");
	
	int n = 1 << 20;
	printf("Vector Length (n): %d\n", n);
	
	double A = 2.0;
	printf("Scalar Variable (A): %.3lf\n", A);
	
	print_divider();
	double* X = (double*) malloc (n * sizeof(double));
	if (X == NULL) {
		printf("ERROR: Vector X Memory Allocation!\n");
		exit(1);
	}
	
	double* Y = (double*) malloc (n * sizeof(double));
	if (Y == NULL) {
		printf("ERROR: Vector Y Memory Allocation!\n");
		exit(1);
	}
	
	double* Z_C = (double*) malloc (n * sizeof(double));
	if (Z_C == NULL) {
		printf("ERROR: Vector Z (C) Memory Allocation!\n");
		exit(1);
	}
	
	double* Z_x86 = (double*) malloc (n * sizeof(double));
	if (Z_x86 == NULL) {
		printf("ERROR: Vector Z (x86-64) Memory Allocation!\n");
		exit(1);
	}
	
	printf("DONE: Vector Memory Allocation.\n");
	print_divider();
	
	printf("Vector Variables (X & Y):\n");
	printf("Note: Display of vector elements has been limited to a maximum of 10 rows with each \n      value truncated to 3 decimal places for presentation purposes.\n\n");
	printf("+=======+============+============+\n");
	printf("| INDEX |  Vector X  |  Vector Y  |\n");
	printf("+=======+============+============+\n");	
	
	int i;
	double j = 1.0;
	for (i = 0; i + 1 <= n; i++) {
		X[i] = 1.0 + j;
		Y[i] = 2.0 + j;
		
		if (i + 1 <= 10) {
			printf("| %5d | %10.3lf | %10.3lf |\n", i, X[i], Y[i]);
		}
		
		j = j + 0.1;
	}
	
	printf("+=======+============+============+\n");	

	print_divider();
	printf("DONE: Vector Values Initialization.\n");
	
	LARGE_INTEGER freq, start, end;
	double elapsed;
	int run_max = 30;
	int run_count = 1;
	double total_asm = 0.0, avg_asm = 0.0;
	double total_c = 0.0, avg_c = 0.0;
	
	QueryPerformanceFrequency(&freq);
	
	print_divider();
	printf("PROGRESS: DAXPY (x86-64 ASM) Function Execution (%d Runs)...\n\n", run_max);	
	
	printf("+=====+=============================+\n");
	printf("| RUN | (x86-64 ASM) Execution Time |\n");
	printf("+=====+=============================+\n");
	
	for (run_count = 0; run_count < run_max; run_count++) {
		QueryPerformanceCounter(&start);
		DAXPY_x86 (n, X, Y, Z_x86, A);
		QueryPerformanceCounter(&end);	

		elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
		printf("| %3d | %27lf |\n", run_count + 1, elapsed);
		
		total_asm += elapsed;
	}
	printf("+=====+=============================+\n");

	print_divider();
	printf("DONE: DAXPY (x86-64 ASM) Function Total Execution Time: %lf seconds\n", total_asm);
	avg_asm = total_asm / run_count;
	printf("DONE: DAXPY (x86-64 ASM) Function Average Execution Time Over %d Runs: %lf seconds.\n", run_count, avg_asm);
	
	print_divider();
	printf("PROGRESS: DAXPY (C) Function Execution (%d Runs)...\n\n", run_max);	

	printf("+=====+=============================+\n");
	printf("| RUN |      (C) Execution Time     |\n");
	printf("+=====+=============================+\n");
	
	for (run_count = 0; run_count < run_max; run_count++) {
		QueryPerformanceCounter(&start);
		DAXPY_C (n, X, Y, Z_C, A);
		QueryPerformanceCounter(&end);	

		elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
		printf("| %3d | %27lf |\n", run_count + 1, elapsed);

		total_c += elapsed;
	}
	printf("+=====+=============================+\n");
	
	print_divider();
	printf("DONE: DAXPY (C) Function Total Execution Time: %lf seconds\n", total_c);
	avg_c = total_c / run_count;
	printf("DONE: DAXPY (C) Function Average Execution Time Over %d Runs: %lf seconds.\n", run_count, avg_c);
	
	double ratio = avg_c / avg_asm;
	double percentage = (1.0 - ratio) * 100.0;
	
	print_divider();
	printf("C to x86-64 ASM Function Average Execution Time Results:\n");
	printf("C is %lf%% faster than x86-64 ASM.\n", percentage);
	
	print_divider();
	printf("Program Results for Vector Z (Both C and x86-64 Function Implementation):\n");
	printf("Note: Display of results is limited to the 1st 10 elements of Vector Z based on project \n      specifications.\n\n");
	printf("+=======+==========+============+============+=============+================+=========+\n");
	printf("| INDEX | Scalar A |  Vector X  |  Vector Y  | Vector Z(C) |  Vector Z(x86) | CORRECT |\n");
	printf("+=======+==========+============+============+=============+================+=========+\n");
	
	int correct;
	int correct_count = 0;
	int wrong_count = 0;
	for (i = 0; i + 1 <= n; i++) {
		if (Z_C[i] == Z_x86[i]) {
			correct = 1;
			correct_count++;
		}
		else {
			correct = 0;
			wrong_count++;	
		}		
		
		if (i + 1 <= 10) 
			printf("| %5d | %8.3f | %10.3f | %10.3f | %11.3f | %14.3f | %7d |\n", i, A, X[i], Y[i], Z_C[i], Z_x86[i], correct);
	}
	printf("+=======+==========+============+============+=============+================+=========+\n");

	printf("\nCorrectness Check (All Elements)");
	printf("\nCorrect Count: %d", correct_count);
	printf("\nWrong Count: %d\n", wrong_count);

	print_divider();
	printf("END: Program Termination.\n");
	print_divider();
	 
	return 0;
}
