/* (c) Victor Yodaiken */
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

/* Knuth's "straight" merge sort "Algorithm S"
 * This is written to be as close as possible to the algorithm presented
 * in Art of Programing Volume 3  except modified from the original
 * so arrays start at 0 as they should. The change from the original 
 * C version was annoyingly painful (although the most time consuming part
 * was caused by an erroneous diagnostic).
 *
 * 2. The "scratch" array needed for mergesort is adjacent to the 
 * 	source array - that is the array is 2N+1 elements, 1 to start
 * 	indexing at 1, and 2N for N data elements and N scratch. 
 * 	This is not realistic and is fixable, but I didn't want to
 * 	change anything
 * 3  The same naming of variables.
 *
 * The test frame is elementary just to see if it works and rough
 * timing
 *
 * Usage:  mergesort [number of elements to be sorted]
 *
 */

typedef int sort_t;
void msort(sort_t * x, unsigned int n);
int testsort(sort_t * x, unsigned int n);
void initarray(sort_t * x, unsigned int n);

#define LEQ(x,y) ((x) <= (y))
#define GUARDWORD 0xf1f2f3f4

int debug = 0;

void msort(sort_t * R, unsigned int N)
{
	int state = 1;
	int s = 0;		// 0 means from source to dest, 1 means otherway
	int p;			// number of elements in sublists to merge
	int i, j;		//start of sublist 1 and sublist 2
	int k;			//destination index
	int l;			// end of destination array
	int d;			// direction of merging
	int q, r;		// remaining elements of list 1 and 2 to merge
	do {
		switch (state) {
		case 1:
			s = 0;
			p = 1;
		case 2:
			if (s == 0) {
				i = 0;
				j = N - 1;
				k = N - 1;
				l = (2 * N);
			} else {
				i = N;
				j = 2 * N - 1;
				k = -1;
				l = N;
			}
			d = 1;
			q = p;
			r = p;
		case 3:
			if (!LEQ(R[i], R[j])) {
				state = 8;
				break;
			}
		case 4:
			k += d;
			R[k] = R[i];
		case 5:
			i += 1;
			q -= 1;
			if (q > 0) {
				state = 3;
				break;
			}
		case 6:
			k += d;
			if (k == l) {
				state = 13;
				break;
			} else {
				R[k] = R[j];
			}
		case 7:
			j -= 1;
			r -= 1;
			if (r > 0) {
				state = 6;
				break;
			} else {
				state = 12;
				break;
			}
		case 8:
			k += d;
			R[k] = R[j];
		case 9:
			j -= 1;
			r -= 1;
			if (r > 0) {
				state = 3;
				break;
			}
		case 10:
			k += d;
			if (k == l) {
				state = 13;
				break;
			} else {
				R[k] = R[i];
			}
		case 11:
			i += 1;
			q -= 1;
			if (q > 0) {
				state = 10;
				break;
			}
		case 12:
			q = p;
			r = p;
			d = -d;
			{
				int temp = k;
				k = l;
				l = temp;
			}
			if ((j - i) < p)
				state = 10;
			else
				state = 3;
			break;
		case 13:	//done?
			p = 2 * p;
			if (p < N) {
				s = 1 - s;
				state = 2;
				break;
			} else {
				if (s == 0) {
					for (i = 0; i < N; i++) {
						R[i] = R[i + N];
					}
				}
			}
			return;	//done

		}
	}
	while (1);

}

int testsort(sort_t * x, unsigned int n)
{
	int i;
	for (i = 0; i < n - 1; i++) {
		if (!(LEQ(*(x + i), *(x + i + 1)))) {
			if (debug)
				printf("not in order at element %d\n", i);
			return -1;
		}
	}
	return 1;
}

void initarray(sort_t * x, unsigned int n)
{
	int i;
	for (i = 0; i <= n; i++)
		x[i] = (sort_t) random();
}

int main(int argc, char **argv)
{
	sort_t *x;
	int y = 128;		//default array length.

	if (argc > 1 && isdigit(argv[1][0])) {
		y = atoi(argv[1]);
		if (!y) {
			fprintf(stderr, "cant test a 0 element array\n");
			exit(0);
		}
	}

	x = malloc(sizeof(sort_t) * (2 * y));
	if (!x) {
		fprintf(stderr, "Cannot allocate the array\n");
		exit(0);
	}

	initarray(x, y);	//fill it with random numbers

	if (debug)
		printf("Before sorting testsort returns %d\n", testsort(x, y));

	msort(x, y);

	printf("After sorting %d elements testsort returns %d\n", y,
	       testsort(x, y));

}
