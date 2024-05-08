# Sequence-Matrix Alignment

Sequence-Matrix Alignment is a C++ program designed to find the optimal way to align a given sequence into a matrix, minimizing the absolute sum of the differences between the integers of the sequence and the matrix. It employs recursion and dynamic programming to traverse all possible paths efficiently.

## About the Project

The project aims to solve the alignment problem by considering four directions: up, down, left, and right, at any point. The program accepts input from a file provided via the command line. The input file format includes the size of the sequence, the number of rows, and the number of columns on the first line. The second line contains the sequence, and the subsequent lines contain the values in the matrix.

### Sample Inputs

Two sample inputs, `sample1.txt` and `sample2.txt`, are provided with the project. These files represent the problem instances. The problem input and expected solutions for these samples are also provided.

- `sample1.txt` Problem:
  
  `6 1 3`

  `2 1 14 1 14 1`

  `2 1 14`

- `sample1.txt` Solution:
  
  `0`

  `1 1`

  `R R L R L`

- `sample2.txt` Problem:

  `5 5 5`
  
  `1 4 1 16 20`
  
  `4 1 20 16 1`
  
  `1 5 16 5 8`
  
  `1 8 1 4 19`
  
  `4 20 5 1 16`
  
  `14 5 4 4 1`

- `sample2.txt` Solution:

  `0`
  
  `3 3`
  
  `R L U U`

## Implementation Details

The program utilizes recursion to traverse through all possible starting points of the sequence and travel all possible paths to find the best candidate. To optimize performance, it employs a dynamic programming approach. Results from function calls are stored in an array-based map to avoid redundant computations.

## Usage

1. Compile the C++ source code.
2. Run the compiled executable from the command line, passing the input file as an argument.

   `g++ MatrixAlign.cpp -o alignment_solver`
   
   `./alignment_solver input_file.txt`

4. The program will output the result in a file named `output.txt`, which includes:
- The absolute sum of the alignment on the first line.
- The starting point (assuming the origin of the matrix is 1,1) on the second line.
- The directions that the path took, represented as:
  - `R` for right
  - `L` for left
  - `U` for up
  - `D` for down

## Author:
Yaniel Gonzalez

## Contributing

Contributions to enhance the program's efficiency or add new features are welcome. Feel free to fork the repository and submit pull requests.
