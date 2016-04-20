#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char dimension_vars[] = {'x', 'y', 'z', 'w', 'u'};

double deter(double* matrix, unsigned int dimension) {
	if (dimension == 2) return matrix[0]*matrix[3] - matrix[1]*matrix[2];
	double* sub = (double *)malloc((dimension - 1) * (dimension - 1) * sizeof(double));
	double* sptr = sub;
	double det = 0;
	for (int i = 0; i < dimension; i++) {
		for (int j = 1; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				if (k == i) continue;
				*sptr++ = matrix[k + j*dimension];
			}
		}
		sptr = sub;
		det += matrix[i] * deter(sub, dimension - 1) * (!(i % 2) ? 1 : -1);
	}
	free(sub);
	return det;
}

double* solve(double* matrix, double* solutions, unsigned int dimension) {
	double det = deter(matrix, dimension);
	if (det == 0) return NULL;
	size_t width = dimension * dimension;
	double* copy = (double *)malloc(width * sizeof(double));
	double* final = (double *)malloc((dimension + 1) * sizeof(double));
	final[0] = det;
	memcpy(copy, matrix, width * sizeof(double));
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i + j*dimension] = solutions[j];	
		}
		final[i + 1] = deter(matrix, dimension);
		memcpy(matrix, copy, width * sizeof(double));
	}
	free(copy);
	return final;
}

int main(int argc, char** argv) {

	unsigned int dimension;
	double* matrix;
	double* solutions;
	double* final;
	
	printf("dimensions?\n");	
	scanf("%d", &dimension);

	matrix = (double *)malloc(dimension * dimension * sizeof(double));
	solutions = (double *)malloc(dimension * sizeof(double));

	printf("\nmatrix?\n");

	for (int i = 0; i < dimension * dimension; i++) {
		scanf("%lf", &matrix[i]);
	}

	printf("solutions?\n");

	for (int i = 0; i < dimension; i++) {
		scanf("%lf", &solutions[i]);
	}

	final = solve(matrix, solutions, dimension);
	if (!final) return printf("no solutions\n");
	
	printf("D = %f\n", final[0]);
	for (int i = 0; i < dimension; i++) {
		printf("%c = %f\n", dimension_vars[i], final[i + 1]);
	}

	return 0;

}
