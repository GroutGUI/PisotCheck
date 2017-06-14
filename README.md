# PisotCheck
Code for computational search for counterexamples to the strong coincidence conjecture.

The code is comprised of two parts:

--The first is a set of MATLAB functions which generate irreducible Pisot matrices.  To use, place all of the MATLAB (.m) files in a single directory and run Pisot_Matrix.m.  A sample output of this code is given in data.txt.

--The second part of the code is the C++ code given in main.cpp.  This code takes a data.txt file, comprised of 8x8 irreducible matrices, and randomly samples realsiations of subsitutions from them.  For each substitution, it then checks for strong coincidence.  To use, place the data.txt file in the same directory as main.cpp, compile the C++ code and run (sample compiler command given in the header of main.cpp).
