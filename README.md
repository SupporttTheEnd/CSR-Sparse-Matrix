# CMSC-341-Project1

# CSR Sparse Matrix Implementation

## Overview

This project implements a Compressed Sparse Row (CSR) matrix data structure in C++. It includes classes for representing individual CSR matrices (`CSR`) as well as a linked list to manage multiple matrices (`CSRList`). The CSR matrix is suitable for sparse matrices, where the majority of elements are zero, as it efficiently stores only the non-zero elements.

## Files

- `csr.h`: Header file containing declarations for the `CSR` and `CSRList` classes.
- `csr.cpp`: Implementation file containing definitions for the methods of the `CSR` and `CSRList` classes.
- `mytest.cpp`: Test file demonstrating the usage of the CSR matrix classes.
- `driver.cpp`: Driver file for executing the test cases.
- `Makefile`: Makefile for compiling and linking the project.

## Compilation and Execution

- To compile the project, run `make p`.
- To compile the project with the driver program, run `make d`.
- To clean the compiled files, run `make clean`.
- To run the executable, use the `./proj1` command.
- To run the executable with Valgrind for memory leak detection, use `make v`.

## Usage

- Include `csr.h` in your C++ code where you want to use CSR matrices.
- Create CSR matrices using the `CSR` class and manage multiple matrices using the `CSRList` class.
- Use methods such as `compress`, `getAt`, `operator==`, etc., to manipulate and compare CSR matrices.
