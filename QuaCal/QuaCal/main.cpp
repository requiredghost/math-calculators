#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Structure to represent a quaternion
struct Quaternion {
    double scalar;
    double i;
    double j;
    double k;

    Quaternion(double s = 0.0, double i = 0.0, double j = 0.0, double k = 0.0)
        : scalar(s), i(i), j(j), k(k) {}
};

// Function to parse a quaternion from a string
Quaternion parseQuaternion(const string& str) {
    stringstream ss(str);
    Quaternion quaternion;

    char skipChar;
    ss >> quaternion.scalar >> skipChar >> quaternion.i >> skipChar >> quaternion.j >> skipChar >> quaternion.k;

    return quaternion;
}

// Function to display a quaternion
void displayQuaternion(const Quaternion& quaternion) {
    cout << quaternion.scalar << " + " << quaternion.i << "i + " << quaternion.j << "j + " << quaternion.k << "k" << endl;
}

// Function to add two quaternions
Quaternion addQuaternions(const Quaternion& a, const Quaternion& b) {
    return Quaternion(a.scalar + b.scalar, a.i + b.i, a.j + b.j, a.k + b.k);
}

// Function to subtract two quaternions
Quaternion subtractQuaternions(const Quaternion& a, const Quaternion& b) {
    return Quaternion(a.scalar - b.scalar, a.i - b.i, a.j - b.j, a.k - b.k);
}

// Function to multiply two quaternions
Quaternion multiplyQuaternions(const Quaternion& a, const Quaternion& b) {
    double scalar = a.scalar * b.scalar - a.i * b.i - a.j * b.j - a.k * b.k;
    double i = a.scalar * b.i + a.i * b.scalar + a.j * b.k - a.k * b.j;
    double j = a.scalar * b.j - a.i * b.k + a.j * b.scalar + a.k * b.i;
    double k = a.scalar * b.k + a.i * b.j - a.j * b.i + a.k * b.scalar;

    return Quaternion(scalar, i, j, k);
}

// Function to calculate the dot product of two quaternions
double calculateDotProduct(const Quaternion& a, const Quaternion& b) {
    return a.scalar * b.scalar + a.i * b.i + a.j * b.j + a.k * b.k;
}

// Function to calculate the conjugate of a quaternion
Quaternion calculateConjugate(const Quaternion& quaternion) {
    return Quaternion(quaternion.scalar, -quaternion.i, -quaternion.j, -quaternion.k);
}

// Function to calculate the inverse of a quaternion
Quaternion calculateInverse(const Quaternion& quaternion) {
    double normSquared = quaternion.scalar * quaternion.scalar + quaternion.i * quaternion.i +
        quaternion.j * quaternion.j + quaternion.k * quaternion.k;

    if (normSquared == 0.0) {
        cerr << "Error: Quaternion is not invertible." << endl;
        exit(1);
    }

    double factor = 1.0 / normSquared;
    return calculateConjugate(quaternion) * factor;
}

// Function to multiply a quaternion by a scalar value
Quaternion multiplyByScalar(const Quaternion& quaternion, double scalar) {
    return Quaternion(quaternion.scalar * scalar, quaternion.i * scalar, quaternion.j * scalar, quaternion.k * scalar);
}

// Function to multiply a quaternion by a scalar value from the right
Quaternion multiplyScalarFromRight(const Quaternion& quaternion, double scalar) {
    return multiplyByScalar(quaternion, scalar);
}

// Function to multiply a quaternion by a scalar value from the left
Quaternion multiplyScalarFromLeft(double scalar, const Quaternion& quaternion) {
    return multiplyByScalar(quaternion, scalar);
}

int main() {
    ifstream inputFile("Quaternion.txt");

    if (!inputFile) {
        cerr << "Error: Failed to open the input file." << endl;
        return 1;
    }

    string quaternionStrA, quaternionStrB;
    double scalar;

    // Read quaternion A
    getline(inputFile, quaternionStrA);

    // Read quaternion B
    getline(inputFile, quaternionStrB);

    // Read scalar value
    inputFile >> scalar;

    inputFile.close();

    // Parse quaternions from strings
    Quaternion quaternionA = parseQuaternion(quaternionStrA);
    Quaternion quaternionB = parseQuaternion(quaternionStrB);

    // Perform operations
    cout << "a + b:" << endl;
    Quaternion additionAB = addQuaternions(quaternionA, quaternionB);
    displayQuaternion(additionAB);

    cout << "a - b:" << endl;
    Quaternion subtractionAB = subtractQuaternions(quaternionA, quaternionB);
    displayQuaternion(subtractionAB);

    cout << "b - a:" << endl;
    Quaternion subtractionBA = subtractQuaternions(quaternionB, quaternionA);
    displayQuaternion(subtractionBA);

    cout << "a * b:" << endl;
    Quaternion multiplicationAB = multiplyQuaternions(quaternionA, quaternionB);
    displayQuaternion(multiplicationAB);

    cout << "b * a:" << endl;
    Quaternion multiplicationBA = multiplyQuaternions(quaternionB, quaternionA);
    displayQuaternion(multiplicationBA);

    cout << "a . b:" << endl;
    double dotProductAB = calculateDotProduct(quaternionA, quaternionB);
    cout << dotProductAB << endl;

    cout << "a*:" << endl;
    Quaternion conjugateA = calculateConjugate(quaternionA);
    displayQuaternion(conjugateA);

    cout << "a-1:" << endl;
    Quaternion inverseA = calculateInverse(quaternionA);
    displayQuaternion(inverseA);

    cout << "ta:" << endl;
    Quaternion scalarMultiplicationA = multiplyScalarFromLeft(scalar, quaternionA);
    displayQuaternion(scalarMultiplicationA);

    return 0;
}
