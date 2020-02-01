#pragma once
#ifndef MATRIX

#define MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define SIZEOFCOMMAND 512 /*size of command*/
#define TOTAL 6 /*Total Matrixes*/
#define SIZE 4/*the size of matrix (4x4)*/
#define CHECKS 6/*numbers of command checks*/

#define TOINDEX(ch) ch-'A' /*Macro For Converting A-F Matrixes to Indexes (0-5)*/

typedef bool(*CallFunc)(char *);/*pointer to functions of checking inputs*/

typedef struct mat {
	double mat[TOTAL][SIZE][SIZE];/*6 2D Arrays*/
	bool sizes[TOTAL];/*Array to help us if the matrix is empty or not (Zeros or no)*/
}Matrix;

static inline void *MallocOrDie(size_t MemSize);/*checking the dynamic allocation if it fails*/

void initializeAllMatrixes(Matrix *data);/*initialize all the Matrixes to Zero*/

void pointToFunctionsOfChecks(CallFunc *functions);

int getFunction(char *command, bool *update);/*this function gets the Current Command function and checks if its valid*/

char *getMatrixes(char *command);/*this functions checks if the matrixes are in range A-F and gets them from the command in an array of chars*/
double *getNumbers(char *command, int *size);/*this functions gets the numbers that has been passed from the read_mat function only and checks if the input is valid*/
double getMul(char *command);/*this function gets the multiplication number from the mul_scalar and returns it*/

void initializeMatrix(Matrix *data, char mat); /*initialize a specific matrix by its index, for re-input*/

void readMat(Matrix *data, double *numbers, int numbersSize, char mat);/*this function gets the numbers that has been passed
through getNumbers and puts them in the given matrix*/

void printMat(char mat, Matrix data);/*prints the Matrix by it's Index (A-F) , (0-5)*/

void addMat(Matrix data, char mat, char mat1);/*this function does addition to two matrix by its index and prints the result*/

void addUpdateMat(Matrix *data, char mat, char mat1, char updated);/*puts the result of addition in the updated matrix index*/

void subMat(Matrix data, char mat, char mat1);/*this function does substraction to two matrix by its index and prints the result*/

void subUpdateMat(Matrix *data, char mat, char mat1, char updated);/*puts the result of substraction in the updated matrix index*/

void mulScalar(Matrix data, double mul, char mat);/*multiplie the matrix by a number and print the result*/

void mulUpdateScalar(Matrix *data, double mul, char mat, char updated);/*multiplie the matrix by a number and puts the resut in the updated matrix*/

void transMat(Matrix data, char mat);/*transpose the specific matrix and print the result*/

void transUpdateMat(Matrix *data, char mat, char updated);

/*Check Commands Per Function*/
void checkIfUpdate(char *command, bool *update, int index);/*checks if the current command is for update , changes values etc..*/

void removeSpaces(char* str); /*removes spaces from a the string , for input check..*/

bool checkEnd(char *sub);/*checks ends of command if there any empty , after or some invalid input*/

bool readMatSubString(char *subStr);/*read in bettwen each comma in the read mat function*/

bool checkReadMat(char *command);/*checking the read_mat function*/

bool checkAddSubMat(char *command);/*checking the add_mat function*/

bool checkSubMul(char *command, bool check);/*checking the sub_mat function*/

bool checkMulScalar(char *command);/*checking the mul_scalar function*/

bool checkTransMat(char *command);/*checking the trans_mat function*/

bool checkPrintMat(char *command);/*checking the print_mat function*/

bool commaCheck(char *command);/*checks in between commas*/

bool checkStopFunction(char *command);/*checks stop command input*/

#endif