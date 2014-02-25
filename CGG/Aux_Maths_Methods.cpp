#include <stdafx.h>

namespace CGG {
	System::Double Factorial(System::Double i){
		return((i <= 1) ? 1 : (i * Factorial(i-1)));
	}

	/******************************************************************************/
	/* Perform Gauss-Jordan elimination with row-pivoting to obtain the solution to 
	 * the system of linear equations
	 * A X = B
	 * 
	 * Arguments:
	 * 		lhs		-	left-hand side of the equation, matrix A
	 * 		rhs		-	right-hand side of the equation, matrix B
	 * 		nrows	-	number of rows in the arrays lhs and rhs
	 * 		ncolsrhs-	number of columns in the array rhs
	 * 
	 * The function uses Gauss-Jordan elimination with pivoting.  The solution X to 
	 * the linear system winds up stored in the array rhs; create a copy to pass to
	 * the function if you wish to retain the original RHS array.
	 * 
	 * Passing the identity matrix as the rhs argument results in the inverse of 
	 * matrix A, if it exists.
	 * 
	 * No library or header dependencies, but requires the function SwapRows, which 
	 * is included here.
	 */

	//  SwapRows - exchanges the contents of row0 and row1 in a 2D array
	void SwapRows(System::Double** arr, System::UInt32 row0, System::UInt32 row1){
		System::Double* temp;
		temp=arr[row0];
		arr[row0]=arr[row1];
		arr[row1]=temp;
	}

	//	GJElimination 
	void GJElimination(cli::array<System::Double, 2>^ lhs, cli::array<System::Double, 2>^ rhs, System::UInt32 nrows, System::UInt32 ncolsrhs){
		//	augment lhs array with rhs array and store in arr2
		System::UInt32 row;
		System::UInt32 col;
		System::UInt32 dindex;
		System::Double** arr2 = new System::Double*[nrows];
		for (row = 0; row < nrows; ++row)
			arr2[row] = new System::Double[nrows + ncolsrhs];

		for (row = 0; row < nrows; ++row) {
			for (col = 0; col < nrows; ++col) {
				arr2[row][col] = lhs[row, col];
			}
			for (col = nrows; col < (nrows + ncolsrhs); ++col) {
				arr2[row][col] = rhs[row, (col - nrows)];
			}
		}
		//	perform forward elimination to get arr2 in row-echelon form
		for (dindex = 0; dindex < nrows; ++dindex) {
			//	run along diagonal, swapping rows to move zeros in working position 
			//	(along the diagonal) downwards
			if ((dindex == (nrows - 1)) && (arr2[dindex][dindex] == 0)) {
				return; //  no solution
			} else if (arr2[dindex][dindex] == 0) {
				SwapRows(arr2, dindex, dindex+1);
			}
			//	divide working row by value of working position to get a 1 on the
			//	diagonal
			if (arr2[dindex][dindex] == 0.0) {
				return;
			} else {
				System::Double tempval = arr2[dindex][dindex];
				for (col = 0; col < (nrows + ncolsrhs); ++col) {
					arr2[dindex][col] /= tempval;
				}
			}
			//	eliminate value below working position by subtracting a multiple of 
			//	the current row
			for (row = dindex + 1; row < nrows; ++row) {
				System::Double wval = arr2[row][dindex];
				for (col = 0; col < (nrows + ncolsrhs); ++col) {
					arr2[row][col] -= wval * arr2[dindex][col];
				}
			}
		}
		//	backward substitution steps
		for (dindex = nrows; dindex > 0;) {
			//	eliminate value above working position by subtracting a multiple of 
			//	the current row
			dindex--;
			for (row = dindex; row > 0;) {
				row--;
				System::Double wval=arr2[row][dindex];
				for (col = 0; col < (nrows + ncolsrhs); ++col) {
					arr2[row][col] -= wval * arr2[dindex][col];
				}
			}
		}
		//	assign result to replace rhs
		for (row = 0; row < nrows; ++row) {
			for (col = 0; col < ncolsrhs; ++col) {
				rhs[row, col] = arr2[row][col + nrows];
			}
		}
		for (row = 0; row < nrows; ++row)
			delete[] arr2[row];
		delete[] arr2;
	}
}