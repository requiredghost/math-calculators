#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

// Quaternion structure
struct Quaternion {
    double w, x, y, z;
};

// Function to parse a quaternion from a string
Quaternion parseQuaternion(const string& str) {
    Quaternion quaternion;
    stringstream ss(str);
    char dummy;
    ss >> dummy >> quaternion.w >> dummy >> quaternion.x >> dummy >> quaternion.y >> dummy >> quaternion.z >> dummy;
    return quaternion;
}

// Function to display a quaternion
void displayQuaternion(const Quaternion& quaternion) {
    cout << quaternion.w << " + " << quaternion.x << "i + " << quaternion.y << "j + " << quaternion.z << "k" << endl;
}

// Function to convert a quaternion to its induced matrix
vector<vector<double>> quaternionToMatrix(const Quaternion& quaternion) {
    vector<vector<double>> matrix(3, vector<double>(3));

    double w = quaternion.w;
    double x = quaternion.x;
    double y = quaternion.y;
    double z = quaternion.z;

    matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
    matrix[0][1] = 2 * x * y - 2 * w * z;
    matrix[0][2] = 2 * x * z + 2 * w * y;
    matrix[1][0] = 2 * x * y + 2 * w * z;
    matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
    matrix[1][2] = 2 * y * z - 2 * w * x;
    matrix[2][0] = 2 * x * z - 2 * w * y;
    matrix[2][1] = 2 * y * z + 2 * w * x;
    matrix[2][2] = 1 - 2 * x * x - 2 * y * y;

    return matrix;
}

// Function to multiply two matrices
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    size_t m1 = matrix1.size();
    size_t n1 = matrix1[0].size();
    size_t m2 = matrix2.size();
    size_t n2 = matrix2[0].size();

    if (n1 != m2) {
        cerr << "Error: Incompatible matrix dimensions for multiplication." << endl;
        exit(1);
    }

    vector<vector<double>> result(m1, vector<double>(n2));

    for (size_t i = 0; i < m1; i++) {
        for (size_t j = 0; j < n2; j++) {
            double sum = 0.0;

            for (size_t k = 0; k < n1; k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }

            result[i][j] = sum;
        }
    }

    return result;
}

// Function to perform quaternion Slerp interpolation
Quaternion slerp(const Quaternion& quaternionA, const Quaternion& quaternionB, double t) {
    double cosTheta = quaternionA.w * quaternionB.w + quaternionA.x * quaternionB.x + quaternionA.y * quaternionB.y + quaternionA.z * quaternionB.z;

    if (cosTheta < 0) {
        // Invert one of the quaternions to take the shortest path
        cosTheta = -cosTheta;
        Quaternion invertedQuaternionB = { -quaternionB.w, -quaternionB.x, -quaternionB.y, -quaternionB.z };
        return slerp(quaternionA, invertedQuaternionB, t);
    }

    double theta = acos(cosTheta);
    double sinTheta = sqrt(1 - cosTheta * cosTheta);

    if (fabs(sinTheta) < 0.001) {
        // Quaternions are very close, use linear interpolation
        double s = 1 - t;
        double w = s * quaternionA.w + t * quaternionB.w;
        double x = s * quaternionA.x + t * quaternionB.x;
        double y = s * quaternionA.y + t * quaternionB.y;
        double z = s * quaternionA.z + t * quaternionB.z;
        double norm = sqrt(w * w + x * x + y * y + z * z);
        return { w / norm, x / norm, y / norm, z / norm };
    }

    double s1 = sin((1 - t) * theta);
    double s2 = sin(t * theta);

    double w = (s1 * quaternionA.w + s2 * quaternionB.w) / sinTheta;
    double x = (s1 * quaternionA.x + s2 * quaternionB.x) / sinTheta;
    double y = (s1 * quaternionA.y + s2 * quaternionB.y) / sinTheta;
    double z = (s1 * quaternionA.z + s2 * quaternionB.z) / sinTheta;
    double norm = sqrt(w * w + x * x + y * y + z * z);

    return { w / norm, x / norm, y / norm, z / norm };
}

int main() {
    string filename = "Slerp.txt";
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error: Failed to open input file." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    Quaternion quaternionA = parseQuaternion(line);

    getline(inputFile, line);
    Quaternion quaternionB = parseQuaternion(line);

    getline(inputFile, line);
    double t = stod(line);

    cout << "Quaternion A: ";
    displayQuaternion(quaternionA);

    cout << "Quaternion B: ";
    displayQuaternion(quaternionB);

    cout << "Interpolation Parameter t: " << t << endl;

    Quaternion slerpResult = slerp(quaternionA, quaternionB, t);

    cout << "\nSlerp Result: ";
    displayQuaternion(slerpResult);

    cout << "\nInduced Matrix of Quaternion A:\n";
    vector<vector<double>> matrixA = quaternionToMatrix(quaternionA);
    for (const auto& row : matrixA) {
        for (double element : row) {
            cout << element << "\t";
        }
        cout << endl;
    }

    cout << "\nInduced Matrix of Quaternion B:\n";
    vector<vector<double>> matrixB = quaternionToMatrix(quaternionB);
    for (const auto& row : matrixB) {
        for (double element : row) {
            cout << element << "\t";
        }
        cout << endl;
    }

    cout << "\nInduced Matrix of Slerp Result:\n";
    vector<vector<double>> matrixSlerp = quaternionToMatrix(slerpResult);
    for (const auto& row : matrixSlerp) {
        for (double element : row) {
            cout << element << "\t";
        }
        cout << endl;
    }

    return 0;
}
