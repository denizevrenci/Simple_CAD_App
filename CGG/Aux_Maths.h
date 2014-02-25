namespace CGG {
	System::Double Factorial(System::Double i);
	void SwapRows(System::Double** arr, System::UInt32 row0, System::UInt32 row1);
	void GJElimination(cli::array<System::Double, 2>^ lhs, cli::array<System::Double, 2>^ rhs, System::UInt32 nrows, System::UInt32 ncolsrhs);
}