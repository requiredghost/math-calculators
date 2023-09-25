#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Function to display a matrix in column-major form
void displayMatrixColumnMajor(const vector<vector<double>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    for (size_t j = 0; j < cols; j++) {
        for (size_t i = 0; i < rows; i++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to display a matrix in row-major form
void displayMatrixRowMajor(const vector<vector<double>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to perform scaling transformation
vector<vector<double>> scale(const vector<vector<double>>& matrix, double scaleX, double scaleY, double scaleZ) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    vector<vector<double>> result(rows, vector<double>(cols));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (i == j) {
                result[i][j] = scaleX * matrix[i][j];
            }
            else if (i == rows - 1 && j == cols - 1) {
                result[i][j] = matrix[i][j];  // Preserve the homogeneous coordinate
            }
            else {
                result[i][j] = 0.0;
            }
        }
    }

    return result;
}

// Function to perform translation transformation
vector<vector<double>> translate(const vector<vector<double>>& matrix, double translateX, double translateY, double translateZ) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    vector<vector<double>> result(rows, vector<double>(cols));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (i == j) {
                if (i == rows - 1 && j != cols - 1) {
                    result[i][j] = matrix[i][j] + translateX;
                }
                else if (i == rows - 1 && j == cols - 1) {
                    result[i][j] = matrix[i][j];  // Preserve the homogeneous coordinate
                }
                else {
                    result[i][j] = matrix[i][j];
                }
            }
            else if (i == rows - 1 && j != cols - 1) {
                result[i][j] = matrix[i][j] + translateY;
            }
            else if (i == rows - 1 && j == cols - 1) {
                result[i][j] = matrix[i][j] + translateZ;
            }
            else {
                result[i][j] = 0.0;
            }
        }
    }

    return result;
}

// Function to perform rotation transformation around the X-axis
vector<vector<double>> rotateX(const vector<vector<double>>& matrix, double angle) {
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    vector<vector<double>> rotationMatrix = {
        {1, 0, 0},
        {0, cosTheta, -sinTheta},
        {0, sinTheta, cosTheta}
    };

    return multiplyMatrices(rotationMatrix, matrix);
}

// Function to perform rotation transformation around the Y-axis
vector<vector<double>> rotateY(const vector<vector<double>>& matrix, double angle) {
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    vector<vector<double>> rotationMatrix = {
        {cosTheta, 0, sinTheta},
        {0, 1, 0},
        {-sinTheta, 0, cosTheta}
    };

    return multiplyMatrices(rotationMatrix, matrix);
}

// Function to perform rotation transformation around the Z-axis
vector<vector<double>> rotateZ(const vector<vector<double>>& matrix, double angle) {
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    vector<vector<double>> rotationMatrix = {
        {cosTheta, -sinTheta, 0},
        {sinTheta, cosTheta, 0},
        {0, 0, 1}
    };

    return multiplyMatrices(rotationMatrix, matrix);
}

// Function to perform projection transformation about the X-axis
vector<vector<double>> projectX(const vector<vector<double>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    vector<vector<double>> result(rows, vector<double>(cols));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (i == j) {
                if (i == rows - 2 && j != cols - 1) {
                    result[i][j] = matrix[i][j] / matrix[rows - 1][j];
                }
                else if (i == rows - 1 && j == cols - 1) {
                    result[i][j] = 1.0;  // Preserve the homogeneous coordinate
                }
                else {
                    result[i][j] = 0.0;
                }
            }
            else if (i == rows - 2 && j != cols - 1) {
                result[i][j] = matrix[i][j] / matrix[rows - 1][j];
            }
            else if (i == rows - 1 && j != cols - 1) {
                result[i][j] = 0.0;
            }
            else {
                result[i][j] = matrix[i][j];
            }
        }
    }

    return result;
}

// Function to perform projection transformation about the Y-axis
vector<vector<double>> projectY(const vector<vector<double>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    vector<vector<double>> result(rows, vector<double>(cols));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (i == j) {
                if (i == rows - 2 && j != cols - 1) {
                    result[i][j] = matrix[i][j] / matrix[rows - 1][j];
                }
                else if (i == rows - 1 && j == cols - 1) {
                    result[i][j] = 1.0;  // Preserve the homogeneous coordinate
                }
                else {
                    result[i][j] = 0.0;
                }
            }
            else if (i == rows - 2 && j != cols - 1) {
                result[i][j] = 0.0;
            }
            else if (i == rows - 1 && j != cols - 1) {
                result[i][j] = matrix[i][j] / matrix[rows - 1][j];
            }
            else {
                result[i][j] = matrix[i][j];
            }
        }
    }

    return result;
}

// Function to perform projection transformation about the Z-axis
vector<vector<double>> projectZ(const vector<vector<double>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    vector<vector<double>> result(rows, vector<double>(cols));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (i == j) {
                if (i != rows - 1 && j != cols - 1) {
                    result[i][j] = matrix[i][j] / matrix[rows - 1][j];
                }
                else if (i == rows - 1 && j == cols - 1) {
                    result[i][j] = 1.0;  // Preserve the homogeneous coordinate
                }
                else {
                    result[i][j] = 0.0;
                }
            }
            else if (i != rows - 1 && j != cols - 1) {
                result[i][j] = matrix[i][j] / matrix[rows - 1][j];
            }
            else if (i != rows - 1 && j == cols - 1) {
                result[i][j] = 0.0;
            }
            else {
                result[i][j] = matrix[i][j];
            }
        }
    }

    return result;
}

// Function to multiply two matrices
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    size_t rows1 = matrix1.size();
    size_t cols1 = matrix1[0].size();
    size_t rows2 = matrix2.size();
    size_t cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        cerr << "Error: Cannot multiply matrices. Invalid dimensions." << endl;
        return {};
    }

    vector<vector<double>> result(rows1, vector<double>(cols2));

    for (size_t i = 0; i < rows1; i++) {
        for (size_t j = 0; j < cols2; j++) {
            for (size_t k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Function to concatenate multiple transformations
vector<vector<double>> concatenateTransformations(const vector<vector<double>>&... transformations) {
    vector<vector<double>> result = transformations[sizeof...(transformations) - 1];

    // Multiply the transformations in reverse order
    ((result = multiplyMatrices(transformations[sizeof...(transformations) - 2 - sizeof...(transformations)], result)), ...);

    return result;
}

int main() {
    // Transformation matrix for scaling
    double scaleX, scaleY, scaleZ;
    cout << "Scaling Transformation" << endl;
    cout << "Enter scaling factors for X, Y, and Z axes: ";
    cin >> scaleX >> scaleY >> scaleZ;

    vector<vector<double>> scalingMatrix = {
        {scaleX, 0, 0, 0},
        {0, scaleY, 0, 0},
        {0, 0, scaleZ, 0},
        {0, 0, 0, 1}
    };

    // Transformation matrix for translation
    double translateX, translateY, translateZ;
    cout << "Translation Transformation" << endl;
    cout << "Enter translation values for X, Y, and Z axes: ";
    cin >> translateX >> translateY >> translateZ;

    vector<vector<double>> translationMatrix = {
        {1, 0, 0, translateX},
        {0, 1, 0, translateY},
        {0, 0, 1, translateZ},
        {0, 0, 0, 1}
    };

    // Transformation matrix for rotation around X-axis
    double angleX;
    cout << "Rotation around X-axis" << endl;
    cout << "Enter rotation angle (in radians): ";
    cin >> angleX;

    vector<vector<double>> rotationXMatrix = {
        {1, 0, 0, 0},
        {0, cos(angleX), -sin(angleX), 0},
        {0, sin(angleX), cos(angleX), 0},
        {0, 0, 0, 1}
    };

    // Transformation matrix for rotation around Y-axis
    double angleY;
    cout << "Rotation around Y-axis" << endl;
    cout << "Enter rotation angle (in radians): ";
    cin >> angleY;

    vector<vector<double>> rotationYMatrix = {
        {cos(angleY), 0, sin(angleY), 0},
        {0, 1, 0, 0},
        {-sin(angleY), 0, cos(angleY), 0},
        {0, 0, 0, 1}
    };

    // Transformation matrix for rotation around Z-axis
    double angleZ;
    cout << "Rotation around Z-axis" << endl;
    cout << "Enter rotation angle (in radians): ";
    cin >> angleZ;

    vector<vector<double>> rotationZMatrix = {
        {cos(angleZ), -sin(angleZ), 0, 0},
        {sin(angleZ), cos(angleZ), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Transformation matrix for projection about X-axis
    vector<vector<double>> projectionXMatrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Transformation matrix for projection about Y-axis
    vector<vector<double>> projectionYMatrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Transformation matrix for projection about Z-axis
    vector<vector<double>> projectionZMatrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Concatenate multiple transformations
    vector<vector<double>> resultMatrix = concatenateTransformations(
        scalingMatrix,
        translationMatrix,
        rotationXMatrix,
        rotationYMatrix,
        rotationZMatrix,
        projectionXMatrix,
        projectionYMatrix,
        projectionZMatrix
    );

    // Display the resultant matrices
    cout << endl << "Resultant Matrix (Column Major):" << endl;
    displayMatrixColumnMajor(resultMatrix);

    cout << endl << "Resultant Matrix (Row Major):" << endl;
    displayMatrixRowMajor(resultMatrix);

    return 0;
}
