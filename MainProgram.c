#include "Matrix.h"
/*Waseem Rkab And Hisham Mansour*/

int main()
{
	Matrix data;
	CallFunc checkCommands[CHECKS];
	bool update = false;
	int size, result = -1;
	char *inputedMatrix, command[SIZEOFCOMMAND];
	double *arrD;
	pointToFunctionsOfChecks(checkCommands);
	initializeAllMatrixes(&data);
	while (true) {
		printf("%s", "Enter a command: ->");
		fgets(command, sizeof command, stdin);
		command[strcspn(command, "\n")] = '\0';
		if (checkStopFunction(command)) {
			removeSpaces(command);/*removes spaces*/
			if (!strcmp(command, "stop")) /*end of program*/
				break;
			else printf("No Such Command\n");
		}
		else if ((result = getFunction(command, &update)) == -1) /*if theres no command , (ilegal command) that getfunction returns*/
			printf("No Such Command\n");
		else if (checkCommands[result](command) == false)  // invalid command-input
			printf("No Such Command\n");
		else if ((inputedMatrix = getMatrixes(command)) == NULL) // not in the A-F matrixes range found
			printf("No Such Matrix\n");
		else {
			switch (result) {// based on the function 
			case 0:
				arrD = getNumbers(command, &size); /*gets the numbers in the read_mat command */
				readMat(&data, arrD, size, inputedMatrix[0]);/*reads the array of numbers and adds to the matrix */
				free(arrD);
				break;
			case 1:	/*prints the matrix*/
				printMat(inputedMatrix[0], data);
				break;
			case 2:
				if (update) { /*requires update or not*//*add between two matrix puts the result in the second matrix*/
					addUpdateMat(&data, inputedMatrix[0], inputedMatrix[1], inputedMatrix[2]);
				}
				else addMat(data, inputedMatrix[0], inputedMatrix[1]);	/*add between two matrix prints the result*/
				break;
			case 3:
				if (update) {/*requires update or not*/
					/*sub between two matrix puts the result in the second matrix*/
					subUpdateMat(&data, inputedMatrix[0], inputedMatrix[1], inputedMatrix[2]);
				}
				/*sub between two matrix prints the result*/
				else subMat(data, inputedMatrix[0], inputedMatrix[1]);
				break;
			case 4:
				if (update) {/*requires update or not*//*multiple with scalar and puts result on the second matrix inputed*/
					mulUpdateScalar(&data, getMul(command), inputedMatrix[0], inputedMatrix[1]);
				}
				/*multiple with scalar and prints the result*/
				else mulScalar(data, getMul(command), inputedMatrix[0]);
				break;
			case 5:
				if (update) {/*requires update or not*//*transpose the matrix and puts result on the second matrix inputed*/
					transUpdateMat(&data, inputedMatrix[0], inputedMatrix[1]);
				}/*transpose and prints the result*/
				else transMat(data, inputedMatrix[0]);
				break;
			}
		}
		update = false;
	}
	return 0;
}