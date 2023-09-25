#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

// Function to parse a row from a string
Row parseRow(const string& str) {
    Row row;
    stringstream ss(str);
    double value;

    while (ss >> value) {
        row.push_back(value);
    }

    return row;
}

// Function to display a row
void displayRow(const Row& row) {
    for (double value : row) {
        cout << value << " ";
    }
    cout << endl;
}

// Function to parse a matrix from a file
Matrix parseMatrixFromFile(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error: Failed to open the input file." << endl;
        exit(1);
    }

    Matrix matrix;
    string line;

    while (getline(inputFile, line)) {
        Row row = parseRow(line);
        matrix.push_back(row);
    }

    inputFile.close();

    return matrix;
}

// Function to display a matrix
void displayMatrix(const Matrix& matrix) {
    for (const Row& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Function to perform the elementary row operation - Multiply a row by a scalar
void multiplyRowByScalar(Row& row, double scalar) {
    for (double& value : row) {
        value *= scalar;
    }
}

// Function to perform the elementary row operation - Add a multiple of one row to another row
void addMultipleOfRowToRow(Row& row1, const Row& row2, double scalar) {
    for (size_t i = 0; i < row1.size(); i++) {
        row1[i] += scalar * row2[i];
    }
}

// Function to find the pivot element index in a column for Gaussian elimination
int findPivotElement(const Matrix& matrix, size_t columnIndex, size_t startRow) {
    int pivotIndex = -1;
    double pivotValue = 0.0;

    for (size_t i = startRow; i < matrix.size(); i++) {
        double value = fabs(matrix[i][columnIndex]);

        if (value > pivotValue) {
            pivotValue = value;
            pivotIndex = static_cast<int>(i);
        }
    }

    return pivotIndex;
}

// Function to perform Gaussian elimination on the matrix
void performGaussianElimination(Matrix& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    size_t lead = 0;

    for (size_t r = 0; r < rows; r++) {
        if (lead >= cols) {
            break;
        }

        int pivotIndex = findPivotElement(matrix, lead, r);

        if (pivotIndex != -1) {
            swap(matrix[pivotIndex], matrix[r]);
            multiplyRowByScalar(matrix[r], 1.0 / matrix[r][lead]);

            for (size_t i = 0; i < rows; i++) {
                if (i != r) {
                    addMultipleOfRowToRow(matrix[i], matrix[r], -matrix[i][lead]);
                }
            }

            lead++;
        }
    }
}

// Function to perform Gauss-Jordan elimination on the matrix
void performGaussJordanElimination(Matrix& matrix) {
    performGaussianElimination(matrix);

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    for (size_t r = 0; r < rows; r++) {
        int pivotColumn = -1;

        for (size_t c = 0; c < cols; c++) {
            if (matrix[r][c] != 0.0) {
                pivotColumn = static_cast<int>(c);
                break;
            }
        }

        if (pivotColumn != -1) {
            multiplyRowByScalar(matrix[r], 1.0 / matrix[r][pivotColumn]);
        }
    }
}

// Function to check if the matrix is in row echelon form
bool isRowEchelonForm(const Matrix& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    int lastPivotIndex = -1;

    for (size_t r = 0; r < rows; r++) {
        bool foundPivot = false;

        for (size_t c = 0; c < cols; c++) {
            if (matrix[r][c] != 0.0) {
                if (c > lastPivotIndex) {
                    foundPivot = true;
                    lastPivotIndex = static_cast<int>(c);
                }
                else {
                    return false;
                }
            }
        }

        if (!foundPivot && matrix[r][cols - 1] != 0.0) {
            return false;
        }
    }

    return true;
}

// Function to check if the matrix is in reduced row echelon form
bool isReducedRowEchelonForm(const Matrix& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    if (!isRowEchelonForm(matrix)) {
        return false;
    }

    for (size_t r = 0; r < rows; r++) {
        int pivotColumn = -1;

        for (size_t c = 0; c < cols; c++) {
            if (matrix[r][c] != 0.0) {
                pivotColumn = static_cast<int>(c);
                break;
            }
        }

        if (pivotColumn != -1) {
            for (size_t i = 0; i < rows; i++) {
                if (i != r && matrix[i][pivotColumn] != 0.0) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    string filename = "Gaussian.txt";
    Matrix matrix = parseMatrixFromFile(filename);

    cout << "Original Matrix:" << endl;
    displayMatrix(matrix);

    char operation;
    cout << "\nSelect an operation:\n";
    cout << "1. Multiply a row by a scalar\n";
    cout << "2. Add a multiple of one row to another row\n";
    cout << "3. Convert to Reduced Row Echelon Form\n";
    cout << "Enter operation number (1, 2, or 3): ";
    cin >> operation;

    while (operation != '3') {
        size_t row1, row2;
        double scalar;

        switch (operation) {
        case '1':
            cout << "Enter row number: ";
            cin >> row1;
            cout << "Enter scalar value: ";
            cin >> scalar;

            multiplyRowByScalar(matrix[row1 - 1], scalar);
            break;

        case '2':
            cout << "Enter first row number: ";
            cin >> row1;
            cout << "Enter second row number: ";
            cin >> row2;
            cout << "Enter scalar value: ";
            cin >> scalar;

            addMultipleOfRowToRow(matrix[row1 - 1], matrix[row2 - 1], scalar);
            break;

        default:
            cout << "Invalid operation. Please try again." << endl;
            break;
        }

        cout << "\nMatrix after the operation:" << endl;
        displayMatrix(matrix);

        cout << "\nSelect the next operation (1, 2, or 3): ";
        cin >> operation;
    }

    cout << "\nConverting to Reduced Row Echelon Form..." << endl;
    performGaussJordanElimination(matrix);

    cout << "\nMatrix in Reduced Row Echelon Form:" << endl;
    displayMatrix(matrix);

    if (isRowEchelonForm(matrix)) {
        cout << "\nThe matrix is in Row Echelon Form." << endl;
    }

    if (isReducedRowEchelonForm(matrix)) {
        cout << "\nThe matrix is in Reduced Row Echelon Form." << endl;
    }

    return 0;
}
