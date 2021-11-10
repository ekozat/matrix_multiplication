//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~ Group 7 ~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~ Eric Morse (1141504)        ~~~~//
//~~~~ Cavaari Taylor (1159034)    ~~~~//
//~~~~ Andrew Linington (1060878)  ~~~~//
//~~~~ Syed Ahmed (1135518)        ~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include "RotationInYTests.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~ Tests ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// ~~~~~~ Get Point Tests ~~~~~~ //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int compareFloat(float x, float y, float acceptedDistance) {
    float difference = fabs(x - y);
    if (difference > acceptedDistance) {
        return 1;
    }
    return 0;
}

// Dirty Test
// Tests if Get Point handles negative index values
int testGetPointReturnsNullWhenIndexIsNeagtive() {
    return getPoint(-1) == NULL;
}

// Dirty Test
// Tests When the value of the index exceeds the max length
int testGetPointReturnsNullWhenIndexIsGreaterThanLength() {
    return getPoint(inputShape->numOfPoints) == NULL;
}

// Clean Test
//  Tests when getting the value it matches the expected value
int testGetPointReturnsMatchingPoint() {
    struct point *testPoint = inputShape->points[0];
    return testPoint == getPoint(0);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// ~~~~~~ Set Point Tests ~~~~~~ //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Clean Test
// Tests When a point is added that the point is stored in the global shape object
int testSetPointIfPointAddedAtIndex() {
    // create null ptr to point
    struct point *newPoint = malloc(sizeof(struct point));
    int index = 1;

    // fill point
    for (int i = 0; i < 4; i++) {
        newPoint->element[i] = (float)1;
    }

    // store current point
    struct point *tempPoint = getPoint(index);

    // set point
    setPoint(index, newPoint);

    // check if new point is added
    if (inputShape->points[1] == newPoint) {
        free(newPoint);

        // put original point back
        setPoint(index, tempPoint);

        return 1;
    }

    // put original point back
    inputShape->points[1] = tempPoint;

    // free
    free(newPoint);
    return 0;
}

// Dirty Test
// Tests when a point is added out of range (negative) that code does not crash
int testSetPointReturn0WhenIndexIsNegative() {
    // index and point
    struct point *newPoint = malloc(sizeof(struct point));
    int index = -1;

    // fill point
    for (int i = 0; i < 4; i++) {
        newPoint->element[i] = (float)1;
    }

    // store current point
    // getPoint(index);

    // set point
    setPoint(index, newPoint);

    free(newPoint);
    return 1;
}

// Dirty Test
// Tests when a point is added out of range that code does not crash
int testSetPointReturn0WhenIndexIsGreaterThenLength() {
    // index and point
    struct point *newPoint = malloc(sizeof(struct point));
    int index = inputShape->numOfPoints;

    // fill point
    for (int i = 0; i < 4; i++) {
        newPoint->element[i] = (float)1;
    }

    // set point
    setPoint(index, newPoint);

    free(newPoint);

    return 1;
}

// Dirty Test
// Tests whether setPoint can handle a struct point pointer pointing to null when passed in, or if it crashes.
int testSetPointReturn0IfPointIsNull() {
    // index and point
    struct point *newPoint = NULL;
    int index = 1;

    // set point
    setPoint(index, newPoint);

    return 1;
}

// getYRotation Tests
// will test if get y rotation works.
int testGetYRotation() {
    inputShape->rotation[1] = 10;

    if (getYRotation() == 10) {
        return 1;
    }

    return 0;
}

// setYRotation Tests
// will test if set y rotation works.
int testSetYRotationWhenAngleIsValid() {
    setYRotation(10);

    if (inputShape->rotation[1] == 10) {
        return 1;
    }

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// ~~~~~~ generateYRotationMatrix Tests ~~~~~~ //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
/*
// Will test generate Y rotation matrix when the matrix was null before running the func.
int testGenerateYRotationMatrixWhenTransformationMatrixIsNull() {
    float **oldMatrix = transformationMatrix;
    float theta = 0;

    // set the matrix to null
    transformationMatrix = NULL;
    // test generate
    generateYRotationMatrix(theta);

    // set the matrix back
    transformationMatrix = oldMatrix;

    // return 1 because it didn't crash. yay!
    return 1;
}

// Will test generate y rotaion matrix when some of the elements are null before running the func.
int testGenerateYRotationMatrixWhenElementOfTransformationMatrixIsNull() {
    float oldMatrix[4][4];
    float theta = 0;

    // copy the matrix to save it for later
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            oldMatrix[i][j] = transformationMatrix[i][j];
        }
    }

    // preserve column 2 so we don't segfault later
    float *col2 = transformationMatrix[2];

    // set a column to null then test the program, the revert the column back
    transformationMatrix[2] = NULL;
    generateYRotationMatrix(theta);
    transformationMatrix[2] = col2;

    // loop through the matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // if something has changed, return 0
            if (transformationMatrix[i][j] != oldMatrix[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}
*/
// Will test generate y rotaiton matrix with theta 0.
int testGenerateYRotationMatrixWhenAngleIs0() {
    float theta = 0;
    // generate the matrix
    generateYRotationMatrix(theta);
    // set the expected matrix
    float expectedMatrix[4][4] = {
        cos(theta), 0, sin(theta), 0,
        0, 1, 0, 0,
        -sin(theta), 0, cos(theta), 0,
        0, 0, 0, 1};

    // loop through the matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // is something doesn't match return 0
            if (expectedMatrix[i][j] != transformationMatrix[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

// Will test gnereate y rotaiton matrix when theta -10.
int testGenerateYRotationMatrixWhenAngleIsNegative() {
    float theta = -10;
    // generate the matrix
    generateYRotationMatrix(theta);

    // set the expected matrix
    float expectedMatrix[4][4] = {
        cos(theta), 0, sin(theta), 0,
        0, 1, 0, 0,
        -sin(theta), 0, cos(theta), 0,
        0, 0, 0, 1};

    // loop through the matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // if something isn't matching, return 0
            if (expectedMatrix[i][j] != transformationMatrix[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Will test gerneate y roataiton matrix with a positive angle, or 10.6 in this case.
int testGenerateYRotationMatrixWhenAngleIsPositiveGreaterThanTwoPi() {
    float theta = (2 * 3.14156942) * 1.69;
    // generate the rotation matrix
    generateYRotationMatrix(theta);

    // set the expected matrix
    float expectedMatrix[4][4] = {
        cos(theta), 0, sin(theta), 0,
        0, 1, 0, 0,
        -sin(theta), 0, cos(theta), 0,
        0, 0, 0, 1};

    // loop through the matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // if something doesn't match return 0
            if (expectedMatrix[i][j] != transformationMatrix[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// ~~~ Matrix Multiplication ~~~ //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Dirty Test

// This tests check whether the function point is NULL
int testMatrixMultiplicationWhenPointIsNull() {
    struct point *tempPoint = NULL;

    multiplyMatrix(tempPoint, transformationMatrix);

    return 1;
}

// Clean Test

// This function tests whether the point is valid by looping through the //matrix
int testMatrixMultiplicationWhenPointIsValid() {
    struct point *tempPoint = malloc(sizeof(struct point));

    // set transform here
    float theta = 10;
    // loop through the matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transformationMatrix[i][j] = 0;
        }
    }
    // set transformation matrix equal to identity matrix
    for (int i = 0; i < 4; i++) {
        transformationMatrix[i][i] = i;
    }

    // set tempPoint to to point to current point
    for (int i = 0; i < 4; i++) {
        tempPoint->element[i] = (float)1;
    }

    multiplyMatrix(tempPoint, transformationMatrix);

    // loops through and free tempPoint
    for (int i = 0; i < 4; i++) {
        if (tempPoint->element[i] != i) {
            free(tempPoint);
            return 0;
        }
    }

    free(tempPoint);
    return 1;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// ~~~~~~ YRotation Tests ~~~~~~ //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Clean Test
// Tests all points in the shape strucure such that they are rotated by 0 radians around Y
int testYRotationWhenAngleIs0() {
    struct point **expected = malloc(sizeof(struct point *) * 5);

    // instantiating the expected result
    for (int i = 0; i < 5; i++) {
        expected[i] = malloc(sizeof(struct point));
        for (int j = 0; j < 3; j++) {
            expected[i]->element[j] = j + i;
        }
        expected[i]->element[3] = 1;
    }

    yRotation();

    for (int i = 0; i < inputShape->numOfPoints; i++) {
        for (int j = 0; j < 4; j++) {
            if (expected[i]->element[j] != inputShape->points[i]->element[j]) {
                for (int i = 0; i < 5; i++) {
                    free(expected[i]);
                }
                free(expected);
                return 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(expected[i]);
    }
    free(expected);
    return 1;
}

// Dirty Test
// Tests all points in the shape strucure such that they are rotated by -PI/2 radians around Y properly for the negative angle
int testYRotationWhenAngleIsNegative() {
    struct point **expected = malloc(sizeof(struct point *) * 5);
    inputShape->rotation[1] = (-(0.5) * 3.14159265359);

    // instantiating the expected result
    for (int i = 0; i < 5; i++) {
        expected[i] = malloc(sizeof(struct point));
        expected[i]->element[0] = (i + 2) * -sin(inputShape->rotation[1]);
        expected[i]->element[1] = 1 + i;
        expected[i]->element[2] = (i)*sin(inputShape->rotation[1]);
        expected[i]->element[3] = 1;
    }

    yRotation();

    // seing if the results match
    for (int i = 0; i < inputShape->numOfPoints; i++) {
        for (int j = 0; j < 4; j++) {
            if (compareFloat(expected[i]->element[j], inputShape->points[i]->element[j], 0.000001)) {
                for (int i = 0; i < 5; i++) {
                    free(expected[i]);
                }
                free(expected);
                return 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(expected[i]);
    }
    free(expected);
    return 1;
}

// Dirty Test
// Tests all points in the shape strucure such that they are rotated by (5 * PI)/2 radians around Y properly for the large angle
int testYRotationWhenAngleIsPositiveGreaterThanTwoPi() {
    struct point **expected = malloc(sizeof(struct point *) * 5);
    inputShape->rotation[1] = ((2.5) * 3.14159265359);

    // instantiating the expected result
    for (int i = 0; i < 5; i++) {
        expected[i] = malloc(sizeof(struct point));
        expected[i]->element[0] = (i + 2) * -sin(inputShape->rotation[1]);
        expected[i]->element[1] = 1 + i;
        expected[i]->element[2] = (i)*sin(inputShape->rotation[1]);
        expected[i]->element[3] = 1;
    }

    yRotation();

    // seeing if the results match
    for (int i = 0; i < inputShape->numOfPoints; i++) {
        for (int j = 0; j < 4; j++) {
            if (compareFloat(expected[i]->element[j], inputShape->points[i]->element[j], 0.000001)) {
                for (int i = 0; i < 5; i++) {
                    free(expected[i]);
                }
                free(expected);
                return 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(expected[i]);
    }
    free(expected);
    return 1;
}
/*
// Dirty Test
// Tests when a Null Matrix is found that nothing is changed for the points
int testYRotationHandlesNullMatrix() {
    float **temp = transformationMatrix;
    transformationMatrix = NULL;
    struct point **expected = malloc(sizeof(struct point *) * 5);
    inputShape->rotation[1] = 0;

    // instantiating the expected result
    for (int i = 0; i < 5; i++) {
        expected[i] = malloc(sizeof(struct point));
        for (int j = 0; j < 3; j++) {
            expected[i]->element[j] = j + i;
        }
        expected[i]->element[3] = 1;
    }

    yRotation();

    transformationMatrix = temp;
    for (int i = 0; i < inputShape->numOfPoints; i++) {
        for (int j = 0; j < 4; j++) {
            if (compareFloat(expected[i]->element[j], inputShape->points[i]->element[j], 0.000001)) {
                for (int i = 0; i < 5; i++) {
                    free(expected[i]);
                }
                free(expected);
                return 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(expected[i]);
    }
    free(expected);
    return 1;
}

// Dirty Test
// Tests when a Null Element of a Matrix is found that nothing is changed for the points
int testYRotationHandlesNullElementOfMatrix() {
    float *temp = transformationMatrix[0];
    transformationMatrix[0] = NULL;
    struct point **expected = malloc(sizeof(struct point *) * 5);
    inputShape->rotation[1] = 0;

    // instantiating the expected result
    for (int i = 0; i < 5; i++) {
        expected[i] = malloc(sizeof(struct point));
        for (int j = 0; j < 3; j++) {
            expected[i]->element[j] = j + i;
        }
        expected[i]->element[3] = 1;
    }

    yRotation();

    transformationMatrix[0] = temp;
    for (int i = 0; i < inputShape->numOfPoints; i++) {
        for (int j = 0; j < 4; j++) {
            if (compareFloat(expected[i]->element[j], inputShape->points[i]->element[j], 0.000001)) {
                for (int i = 0; i < 5; i++) {
                    free(expected[i]);
                }
                free(expected);
                return 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(expected[i]);
    }
    free(expected);
    return 1;
}

// Dirty Test
// Tests when a Null Matrix is found that nothing is changed for the points after the Null
int testYRotationHandlesNullPoint() {
    struct point *temp = inputShape->points[1];
    inputShape->points[1] = NULL;
    struct point **expected = malloc(sizeof(struct point *) * 5);
    inputShape->rotation[1] = ((0.5) * 3.14159265359);

    // instantiating the expected result
    for (int i = 0; i < 5; i++) {
        expected[i] = malloc(sizeof(struct point));
        for (int j = 0; j < 3; j++) {
            expected[i]->element[j] = j + i;
        }
        expected[i]->element[3] = 1;
    }
    // only alters the first one given a point is NULL
    expected[0]->element[0] = -2;
    expected[0]->element[2] = 0;

    yRotation();

    inputShape->points[1] = temp;
    for (int i = 0; i < inputShape->numOfPoints; i++) {
        for (int j = 0; j < 4; j++) {
            if (compareFloat(expected[i]->element[j], inputShape->points[i]->element[j], 0.000001)) {
                printf("%d %d %f %f\n", i, j, expected[i]->element[j], inputShape->points[i]->element[j]);
                for (int i = 0; i < 5; i++) {
                    free(expected[i]);
                }
                free(expected);
                return 0;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(expected[i]);
    }
    free(expected);
    return 1;
}
*/
// Dirty
// Tests when all points are Null that nothing changes foir the value
int testYRotationHandlesNullPoints() {
    struct point **temp = inputShape->points;
    inputShape->points = NULL;
    inputShape->rotation[1] = ((0.5) * 3.14159265359);

    yRotation();

    if (inputShape->points == NULL) {
        inputShape->points = temp;
        return 1;
    }
    inputShape->points = temp;
    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~ //
// ~~~~~~ Other Funcs ~~~~~~ //
// ~~~~~~~~~~~~~~~~~~~~~~~~~ //
void setup() {
    inputShape->numOfPoints = 5;
    inputShape->rotation[1] = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            inputShape->points[i]->element[j] = j + i;
        }
        inputShape->points[i]->element[3] = 1;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transformationMatrix[i][j] = i + j;
        }
    }
}

void group7TestHandler(int (*test)(), char *testString) {
    // fixes any values that may have been changed from previous test
    setup();

    if (!test()) {
        printf("%s failed\n", testString);
    }
}

void runGroup7Tests() {
    // getPoint Tests //

    // Dirty Tests
    group7TestHandler(testGetPointReturnsNullWhenIndexIsNeagtive, "Test Get Point Returns Null When Index Is Negative");

    group7TestHandler(testGetPointReturnsNullWhenIndexIsGreaterThanLength, "Test Get Point Returns Null When Index Is Greater Then Length");

    // Clean Tests
    group7TestHandler(testGetPointReturnsMatchingPoint, "Test Get Point Returns Matching Point ");

    // setPoint Tests //

    // Dirty Tests
    group7TestHandler(testSetPointReturn0WhenIndexIsNegative, "Test Set Point If Returns 0 When Index Negative.");

    group7TestHandler(testSetPointReturn0WhenIndexIsGreaterThenLength, "Test Set Point If Returns 0 When Index Greater Than Length.");

    group7TestHandler(testSetPointReturn0IfPointIsNull, "Test Set Point If Returns 0 When Point is Null");

    // Clean Tests
    group7TestHandler(testSetPointIfPointAddedAtIndex, "Test Set Point If Point Added At Index");

    // getYRotation Tests //

    group7TestHandler(testGetYRotation, "Test Get Y Rotation");

    // setYRotation Tests
    group7TestHandler(testSetYRotationWhenAngleIsValid, "Test Set Y Rotation When Angle Is valid");

    // generateYRotationMatrix tests
    // group7TestHandler(testGenerateYRotationMatrixWhenTransformationMatrixIsNull, "Test Generate Y Rotation Matrix When Transformation Matrix is Null");

    // group7TestHandler(testGenerateYRotationMatrixWhenElementOfTransformationMatrixIsNull, "Test Generate Y Rotation Matrix When Element Of Transformation Matrix Is Null");

    group7TestHandler(testGenerateYRotationMatrixWhenAngleIs0, "Test Generate Y Rotation Matrix When Angle Is 0");

    group7TestHandler(testGenerateYRotationMatrixWhenAngleIsNegative, "Test Generate Y Rotation Matrix When Angle Is Negative");

    group7TestHandler(testGenerateYRotationMatrixWhenAngleIsPositiveGreaterThanTwoPi, "Test Generate Y Rotation Matrix When Angle Is Positive Greater Then Two Pi");

    // Matrix Multiplication Tests //

    // Dirty tests
    group7TestHandler(testMatrixMultiplicationWhenPointIsNull, "Test Matrix Multiplication To Check For NULL Point ");

    // Clean tests
    group7TestHandler(testMatrixMultiplicationWhenPointIsValid, "Test Matrix Multiplication Points Are Valid ");

    // Dirty YRotation Tests
    group7TestHandler(testYRotationHandlesNullPoints, "Test Y Rotation Handles Null Points ");

    // group7TestHandler(testYRotationHandlesNullPoint, "Test Y Rotation Handles Null Point ");

    // group7TestHandler(testYRotationHandlesNullMatrix, "Test Y Rotation Handles Null Matrix ");

    // group7TestHandler(testYRotationHandlesNullElementOfMatrix, "Test Y Rotation Handles Null Element Of Matrix ");

    group7TestHandler(testYRotationWhenAngleIsPositiveGreaterThanTwoPi, "Test Y Rotation When Angle Is Positive Greater Than Two Pi ");

    group7TestHandler(testYRotationWhenAngleIsNegative, "Test Y Rotation When Angle Is Negative ");

    // Clean YRotation Tests
    group7TestHandler(testYRotationWhenAngleIs0, "Test Y Rotation When Angle Is 0 ");
}
