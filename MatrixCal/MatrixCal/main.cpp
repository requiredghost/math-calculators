#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to display a matrix
void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Function to calculate the determinant of a 2x2 matrix
int calculateDeterminant(const vector<vector<int>>& matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to transpose a matrix
vector<vector<int>> transposeMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> result(cols, vector<int>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

// Function to calculate the inverse of a matrix
vector<vector<int>> calculateInverse(const vector<vector<int>>& matrix) {
    int determinant = calculateDeterminant(matrix);

    if (determinant == 0) {
        cerr << "Error: Matrix is not invertible." << endl;
        exit(1);
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> inverse(rows, vector<int>(cols));

    inverse[0][0] = matrix[1][1];
    inverse[0][1] = -matrix[0][1];
    inverse[1][0] = -matrix[1][0];
    inverse[1][1] = matrix[0][0];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inverse[i][j] /= determinant;
        }
    }

    return inverse;
}

// Function to multiply a matrix by a scalar value
vector<vector<int>> multiplyByScalar(const vector<vector<int>>& matrix, int scalar) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> result(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }

    return result;
}

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    vector<vector<int>> result(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    vector<vector<int>> result(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    return result;
}

// Function to multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        cerr << "Error: Matrix dimensions are not compatible for multiplication." << endl;
        exit(1);
    }

    vector<vector<int>> result(rows1, vector<int>(cols2));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Function to generate an identity matrix
vector<vector<int>> generateIdentityMatrix(int size) {
    vector<vector<int>> identity(size, vector<int>(size));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            identity[i][j] = (i == j) ? 1 : 0;
        }
    }

    return identity;
}

int main() {
    ifstream inputFile("Matrix.txt");

    if (!inputFile) {
        cerr << "Error: Failed to open the input file." << endl;
        return 1;
    }

    vector<vector<int>> matrixA;
    vector<vector<int>> matrixB;
    int scalar;

    // Read matrix A
    for (int i = 0; i < 4; i++) {
        vector<int> row;
        for (int j = 0; j < 4; j++) {
            int element;
            inputFile >> element;
            row.push_back(element);
        }
        matrixA.push_back(row);
    }

    // Read matrix B
    for (int i = 0; i < 4; i++) {
        vector<int> row;
        for (int j = 0; j < 4; j++) {
            int element;
            inputFile >> element;
            row.push_back(element);
        }
        matrixB.push_back(row);
    }

    // Read scalar value
    inputFile >> scalar;

    inputFile.close();

    // Perform operations
    cout << "|A|:" << endl;
    int determinantA = calculateDeterminant(matrixA);
    cout << determinantA << endl;

    cout << "AT:" << endl;
    vector<vector<int>> transposeA = transposeMatrix(matrixA);
    displayMatrix(transposeA);

    cout << "A-1:" << endl;
    vector<vector<int>> inverseA = calculateInverse(matrixA);
    displayMatrix(inverseA);

    cout << "Multiply A by scalar:" << endl;
    vector<vector<int>> scalarMultiplicationA = multiplyByScalar(matrixA, scalar);
    displayMatrix(scalarMultiplicationA);

    cout << "A + B:" << endl;
    vector<vector<int>> additionAB = addMatrices(matrixA, matrixB);
    displayMatrix(additionAB);

    cout << "A - B:" << endl;
    vector<vector<int>> subtractionAB = subtractMatrices(matrixA, matrixB);
    displayMatrix(subtractionAB);

    cout << "A * B:" << endl;
    vector<vector<int>> multiplicationAB = multiplyMatrices(matrixA, matrixB);
    displayMatrix(multiplicationAB);

    cout << "B * A:" << endl;
    vector<vector<int>> multiplicationBA = multiplyMatrices(matrixB, matrixA);
    displayMatrix(multiplicationBA);

    cout << "Identity Matrix:" << endl;
    vector<vector<int>> identityMatrix = generateIdentityMatrix(4);
    displayMatrix(identityMatrix);

    return 0;
}
