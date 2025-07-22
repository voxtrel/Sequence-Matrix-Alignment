#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

// Yaniel Gonzalez

std::string printPath(int i, int j, int k, int s_size, std::string& alignPath);  // Function declaration for printPath

std::vector<std::vector<std::vector<std::pair<int, std::string> > > > memoMap;   // 3D-Array for memoization


// Helper function
int alignMatrix_Helper(std::vector<std::vector<int> >& matrixA, int sequence[], int s_size, int k, int m, int n, int i, int j) {

    if((memoMap[i][j][k]).first == -1){              // if not traversed yet do:

        if(k == s_size-1){                           // base case
            return abs(matrixA[i][j] - sequence[k]);
        }

        // initialize value for recursion
        int result = INT_MAX;

        // Difference at current position
        int absDiff = abs(matrixA[i][j] - sequence[k]);

        if(!(j+1>n-1)){         // if right doesn't go out of boundary, recurse right
            int cost = absDiff + abs(alignMatrix_Helper(matrixA, sequence, s_size, k+1, m, n, i,j+1));  
            if(cost < result){
                result = cost;
                memoMap[i][j][k].second = "R";
            }
        }      
        if(!(j-1<0)){           // if left doesn't go out of boundary, recurse left
            int cost = absDiff + abs(alignMatrix_Helper(matrixA, sequence, s_size, k+1, m, n,i,j-1));
            if(cost < result){
                result = cost;
                memoMap[i][j][k].second = "L";
            }
        }
        if(!(i+1>m-1)){         // if down doesn't go out of boundary, recurse down
            int cost = absDiff + abs(alignMatrix_Helper(matrixA, sequence, s_size, k+1, m, n,i+1,j));
            if(cost < result){
                result = cost;
                memoMap[i][j][k].second = "D";
            }
        }
        if(!(i-1<0)){           // if up doesn't go out of boundary, recurse up
            int cost = absDiff + abs(alignMatrix_Helper(matrixA, sequence, s_size, k+1, m, n,i-1,j));
            if(cost < result){
                result = cost;
                memoMap[i][j][k].second = "U";
            }
        }
        // store result in the map
        return (memoMap[i][j][k]).first = result;
    }else{  // Else we have already traversed this point, so return value from memoMap
        return (memoMap[i][j][k]).first;
    }
}


// Wrapper function
void alignMatrix(std::vector<std::vector<int> >& matrixA, int sequence[], int s_size, int m, int n){

    // Initialize the map to sentinel value -1 and empty string
    memoMap.resize(m, std::vector<std::vector<std::pair<int, std::string> > >(n, std::vector<std::pair<int, std::string> >(s_size, std::make_pair(-1, ""))));

    // Go through all starting points of the matrix and find the minimal absolute difference and staring point 
    int absolute = INT_MAX;
    int start_i; 
    int start_j;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            int min  = alignMatrix_Helper(matrixA, sequence, s_size, 0, m, n, i, j);
            if(min < absolute){
                absolute = min;
                start_i = i;
                start_j = j;
            }
        }
    }
    // Trace the alignment path using the starting point found
    std::string alignPath = "";
    printPath(start_i, start_j, 0, s_size, alignPath);      // function call to function that traces the path

    // Write the solutions to the output.txt file
    std::ofstream output("output.txt");
    output << absolute << std::endl;                        // Write absolute difference
    output << start_i+1 << " " << start_j+1 << std::endl;   // Write starting point
    output << alignPath;                                    // Write alignment path
    output.close();
} 

// Function that gets the alignment path using the found starting point
std::string printPath(int i, int j, int k, int s_size, std::string& alignPath) {
    if (k == s_size - 1) { // End of the path
        return alignPath;
    }
    // Recurse to the next position
    if ((memoMap[i][j][k]).second == "R") {
        alignPath += "R ";
        printPath(i, j + 1, k + 1, s_size, alignPath);
    }
    else if ((memoMap[i][j][k]).second == "L") {
        alignPath += "L ";
        printPath(i, j - 1, k + 1, s_size, alignPath);
    }
    else if ((memoMap[i][j][k]).second == "U") {
        alignPath += "U ";
        printPath(i - 1, j, k + 1, s_size, alignPath);
    }
    else if ((memoMap[i][j][k]).second == "D") {
        alignPath += "D ";
        printPath(i + 1, j, k + 1, s_size, alignPath);
    }
    return alignPath;
}

// Get inputs from main which takes the command line arguments
int main(int argc, char* argv[]) {

    // Check command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    
    // get filename from command line
    std::string filename = argv[1]; 

    int s_size;  // size of sequence
    int m;       // number of rows
    int n;       // number of columns

    std::ifstream inputFile(filename);      // read file

    // Check that the file opens correctly
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::string content;                        // variable to hold line

    getline(inputFile, content);                // read first line 
    std::stringstream line(content);            // sting line for content to extract inputs

    line >> s_size >> m >> n;                   // extract inputs

    getline(inputFile, content);                // read second line for for sequence
    std::stringstream line2(content);           // sting line for content to extract sequence

    int sequence[s_size];                       // declare sequence of size s_size
    for(int i = 0; i < (int)content.size(); i++){    // iterate through the content of the second line
        line2 >> sequence[i];                   // fill the sequence from the line
    }

    std::vector<std::vector<int> > matrixA(m, std::vector<int>(n)); // declare the matrix
    for(int i = 0; i < m; i++){                 // iterate through the number of rows
        getline(inputFile, content);            // get new line of data
        std::stringstream data(content);        // stream the data
        for(int j = 0; j < n; j++){             // iterate through the number of columns
            data >> matrixA[i][j];              // fill the matrix
        }
    }

    inputFile.close();                          // close file

    // Function call to align sequence on the Matrix
    alignMatrix(matrixA, sequence, s_size, m, n);
   
    return 0;
}
