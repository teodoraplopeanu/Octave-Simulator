// Plopeanu Teodora-Anca 312CAa 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define mod 10007

int modulo(int x)
{
	return (mod + x % mod) % mod;
}

int ***load(int ***a, int count, int ***dims, int *ok)
{
	int m, n;
	scanf("%d%d", &m, &n);
	// Check if we have previously loaded other matrices
	if (count == 0 && *ok == 1) {
		*ok = 0;
		a = malloc(sizeof(int **));
		*dims = malloc(sizeof(int *));
	} else {
		a = realloc(a, (count + 1) * sizeof(int **));
		*dims = realloc(*dims, (count + 1) * sizeof(int *));
	}
	if (!a || !(*dims)) {
		perror("Memory allocation failed");
		exit(-1);
	}
	// Allocate memory for array of dimensions
	(*dims)[count] = malloc(2 * sizeof(int));
	(*dims)[count][0] = m;
	(*dims)[count][1] = n;
	// Allocate memory for the matrix
	a[count] = malloc(m * sizeof(int *));
	for (int i = 0; i < m; i++)
		a[count][i] = malloc(n * sizeof(int));
	// Scan the matrix
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[count][i][j]);

	return a;
}

void dimensions(int index, int **dims, int count)
{
	// Check if the matrix index is valid
	if (index < 0 || index >= count) {
		printf("No matrix with the given index\n");
		return;
	}
	// Prints the dimensions from the array
	printf("%d %d\n", dims[index][0], dims[index][1]);
}

void print(int ***a, int index, int **dims, int count)
{
	// Check if the matrix index is valid
	if (index < 0 || index >= count) {
		printf("No matrix with the given index\n");
		return;
	}
	// Number of rows and columns
	int rows = dims[index][0];
	int columns = dims[index][1];
	// Print the matrix
	for (int i = 0; i < rows; i++, printf("\n"))
		for (int j = 0; j < columns; j++)
			printf("%d ", a[index][i][j]);
}

int ***multiply(int ***a, int index1, int index2, int ***dims, int *count)
{
	// Check if the matrix index is valid
	if (index1 < 0 || index1 >= *count || index2 < 0 || index2 >= *count) {
		printf("No matrix with the given index\n");
		return a;
	}
	// Check if the dimensions are compatible
	if ((*dims)[index1][1] != (*dims)[index2][0]) {
		printf("Cannot perform matrix multiplication\n");
		return a;
	}

	// Allocate memory for the result matrix
	if (count == 0) {
		a = malloc(sizeof(int **));
		(*dims) = malloc(sizeof(int *));
	} else {
		a = realloc(a, ((*count) + 1) * sizeof(int **));
		(*dims) = realloc((*dims), ((*count) + 1) * sizeof(int *));
	}
	if (!a || !(*dims)) {
		perror("Memory allocation failed");
		exit(-1);
	}
	(*dims)[*count] = malloc(2 * sizeof(int));
	if (!(*dims)[*count]) {
		perror("Memory allocation failed");
		exit(-1);
	}

	// Set dimensions for the result matrix
	(*dims)[*count][0] = (*dims)[index1][0];
	(*dims)[*count][1] = (*dims)[index2][1];

	// Allocate memory for the result matrix
	a[*count] = malloc((*dims)[*count][0] * sizeof(int *));
	for (int i = 0; i < (*dims)[*count][0]; i++)
		a[*count][i] = malloc((*dims)[*count][1] * sizeof(int));
	if (!a[*count]) {
		perror("Memory allocation failed");
		exit(-1);
	}
	// Compute the product matrix
	for (int i = 0; i < (*dims)[*count][0]; i++) {
		for (int j = 0; j < (*dims)[*count][1]; j++) {
			a[*count][i][j] = 0;
			for (int k = 0; k < (*dims)[index1][1]; k++) {
				a[*count][i][j] += a[index1][i][k] * a[index2][k][j];
				a[*count][i][j] = modulo(a[*count][i][j]);
			}
		}
	}
	(*count)++;
	return a;
}

void transpose(int ***a, int index, int count, int ***dims)
{
	// Check if the matrix index is valid
	if (index < 0 || index >= count) {
		printf("No matrix with the given index\n");
		return;
	}
	int rows = (*dims)[index][1], cols = (*dims)[index][0], nr;
	// Allocate memory for auxiliary matrix
	int **aux = malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
		aux[i] = malloc(cols * sizeof(int));
	if (!aux) {
		perror("Memory allocation failed");
		exit(-1);
	}
	// Transpose the matrix
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			aux[i][j] = a[index][j][i];

	// Free the memory of the original matrix
	for (int i = 0; i < (*dims)[index][0]; i++)
		free(a[index][i]);
	free(a[index]);

	// Reallocate memory for the original matrix
	a[index] = malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
		a[index][i] = malloc(cols * sizeof(int));
	if (!a[index]) {
		perror("Memory allocation failed");
		exit(-1);
	}
	// Copy the transposed matrix back to the original matrix
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			a[index][i][j] = aux[i][j];

	// Update the dimensions
	nr = (*dims)[index][1];
	(*dims)[index][1] = (*dims)[index][0];
	(*dims)[index][0] = nr;

	// Free memory for the transpose matrix
	for (int i = 0; i < rows; i++)
		free(aux[i]);
	free(aux);
}

void redim(int ***a, int index, int ***dims, int count)
{
	int l, c, *rows, *cols;

	// Read the rows and the columns by which we resize the matrix
	scanf("%d", &l);

	rows = malloc(l * sizeof(int));
	for (int i = 0; i < l; i++)
		scanf("%d", &rows[i]);
	if (!rows) {
		perror("Memory allocation failed");
		exit(-1);
	}
	scanf("%d", &c);

	cols = malloc(c * sizeof(int));
	for (int i = 0; i < c; i++)
		scanf("%d", &cols[i]);
	if (!cols) {
		perror("Memory allocation failed");
		exit(-1);
	}
	// Check if the matrix index is valid
	if (index < 0 || index >= count) {
		printf("No matrix with the given index\n");
		free(rows);
		free(cols);
		return;
	}

	// Allocate memory for the auxiliary matrix
	int **aux = malloc(l * sizeof(int *));
	if (!aux) {
		perror("Memory allocation failed");
		exit(-1);
	}
	for (int i = 0; i < l; i++)
		aux[i] = malloc(c * sizeof(int));
	// Build the resized matrix
	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++)
			aux[i][j]  = a[index][rows[i]][cols[j]];
	// Free the memory of the original matrix
	for (int i = 0; i < (*dims)[index][0]; i++)
		free(a[index][i]);
	free(a[index]);

	a[index] = aux;

	(*dims)[index][0] = l;
	(*dims)[index][1] = c;
	free(rows);
	free(cols);
}

void sort_matrices(int ***a, int count, int ***dims)
{
	int *sums = malloc(count * sizeof(int)), sum, temp_sum;
	int ok, **temp_matrix, *temp_dims;
	// Build an array that contains
	// the sum of every matrix
	for (int index = 0; index < count; index++) {
		sum = 0;
		for (int i = 0; i < (*dims)[index][0]; i++)
			for (int j = 0; j < (*dims)[index][1]; j++) {
				sum += a[index][i][j];
				sum = modulo(sum);
			}
		sums[index] = sum;
	}

	// Bubble Sort
	do {
		ok = 1;
		for (int i = 0; i < count - 1; i++)
			if (sums[i] > sums[i + 1]) {
				ok = 0;

				temp_sum = sums[i];
				sums[i] = sums[i + 1];
				sums[i + 1] = temp_sum;

				temp_matrix = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp_matrix;

				temp_dims = (*dims)[i];
				(*dims)[i] = (*dims)[i + 1];
				(*dims)[i + 1] = temp_dims;
			}
	} while (!ok);

	free(sums);
}

void power(int ***a, int **dims, int count, int index, int pow)
{
	if (index < 0 || index >= count) {
		printf("No matrix with the given index\n");
		return;
	}
	if (pow < 0) {
		printf("Power should be positive\n");
		return;
	}
	if (dims[index][0] != dims[index][1]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	// Allocate memory and build auxiliary matrices
	int **backup = malloc(dims[index][0] * sizeof(int *));
	int **temp = malloc(dims[index][0] * sizeof(int *));
	int sum;
	if (!backup || !temp) {
		perror("Memory allocation failed");
		exit(-1);
	}
	for (int i = 0; i < dims[index][0]; i++) {
		backup[i] = malloc(dims[index][1] * sizeof(int));
		temp[i] = malloc(dims[index][1] * sizeof(int));
	} // Copy a[index] to backup
	for (int i = 0; i < dims[index][0]; i++)
		for (int j = 0; j < dims[index][1]; j++)
			backup[i][j] = a[index][i][j];
	for (int i = 0; i < dims[index][0]; i++) // Build identity matrix
		for (int j = 0; j < dims[index][1]; j++)
			if (i == j)
				a[index][i][j] = 1;
			else
				a[index][i][j] = 0;
	// Compute the power
	while (pow) {
		// Power even
		if (pow % 2 == 0) {
			// Square backup
			for (int i = 0; i < dims[index][0]; i++)
				for (int j = 0 ; j < dims[index][1]; j++) {
					sum = 0;
					for (int k = 0; k < dims[index][0]; k++) {
						sum += backup[i][k] * backup[k][j];
						sum = modulo(sum);
					}
					temp[i][j] = sum;
				}
			for (int i = 0; i < dims[index][0]; i++)
				for (int j = 0; j < dims[index][1]; j++)
					backup[i][j] = temp[i][j];
			// Divide pow by 2
			pow /= 2;
		} else {
			// Power odd
			// Multiply a[index] and backup
			for (int i = 0; i < dims[index][0]; i++)
				for (int j = 0 ; j < dims[index][1]; j++) {
					sum = 0;
					for (int k = 0; k < dims[index][0]; k++) {
						sum +=  backup[i][k] * a[index][k][j];
						sum = modulo(sum);
					}
					temp[i][j] = sum;
				}
			for (int i = 0; i < dims[index][0]; i++)
				for (int j = 0; j < dims[index][1]; j++)
					a[index][i][j] = temp[i][j];
			// Decrement pow
			pow--;
		}
	}
	// Free the resources
	for (int i = 0; i < dims[index][0]; i++) {
		free(backup[i]);
		free(temp[i]);
	}
	free(backup);
	free(temp);
}

void free_matrix(int ***a, int index, int *count, int ***dims)
{
	// Check if the matrix index is valid
	if (index < 0 || index >= *count) {
		printf("No matrix with the given index\n");
		return;
	}
	// Free memory for matrix of index and its dimensions
	for (int i = 0; i < (*dims)[index][0]; i++)
		free(a[index][i]);
	free(a[index]);
	free((*dims)[index]);
	// Update the array
	for (int i = index; i < *count - 1; i++) {
		a[i] = a[i + 1];
		(*dims)[i] = (*dims)[i + 1];
	}
	// Update count
	(*count)--;
}

void quit(int ***a, int ***dims, int count)
{
	// Free the whole array of matrices
	// And of dimensions
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < (*dims)[i][0]; j++)
			free(a[i][j]);
		free(a[i]);
		free((*dims)[i]);
	}
	free(a);
	free((*dims));
}

int main(void)
{
	char command;
	int ***a = NULL, **dims, count = 0;
	int index, index1, index2, pow, ok = 1;

	while (scanf(" %c", &command) != EOF) {
		switch (command) {
		case 'L':
			a = load(a, count, &dims, &ok);
			count++;
			continue;

		case 'D':
			scanf("%d", &index);
			dimensions(index, dims, count);
			continue;

		case 'P':
			scanf("%d", &index);
			print(a, index, dims, count);
			continue;

		case 'C':
			scanf("%d", &index);
			redim(a, index, &dims, count);
			continue;

		case 'M':
			scanf("%d%d", &index1, &index2);
			a = multiply(a, index1, index2, &dims, &count);
			continue;

		case 'O':
			sort_matrices(a, count, &dims);
			continue;

		case 'T':
			scanf("%d", &index);
			transpose(a, index, count, &dims);
			continue;

		case 'R':
			scanf("%d%d", &index, &pow);
			power(a, dims, count, index, pow);
			continue;

		case 'F':
			scanf("%d", &index);
			free_matrix(a, index, &count, &dims);
			continue;

		case 'S':
			scanf("%d%d", &index1, &index2);
			a = multiply(a, index1, index2, &dims, &count);
			continue;

		case 'Q':
			quit(a, &dims, count);
			return 0;

		default:
			if (command >= 'A' && command <= 'Z')
				printf("Unrecognized command\n");
			continue;
		}
	}

	return 0;
}
