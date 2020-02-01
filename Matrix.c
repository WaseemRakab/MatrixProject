#include "Matrix.h"

/*all legal functions*/
const char *commands[] = { "read_mat","print_mat","add_mat","sub_mat","mul_scalar","trans_mat" };

void pointToFunctionsOfChecks(CallFunc *functions) {/*point to functions to check the commands*/
	functions[0] = checkReadMat;
	functions[1] = checkPrintMat;
	functions[2] = checkAddSubMat;
	functions[3] = checkAddSubMat;
	functions[4] = checkMulScalar;
	functions[5] = checkTransMat;
}

void readMat(Matrix *data, double *numbers, int numbersSize, char ch) {
	if (numbers == NULL) { (*data).sizes[ch] = true; return; }
	int numIdx = 0;
	if ((*data).sizes[ch] == true) {/*if it had numbers before , it will initialize the matrix again*/
		initializeMatrix(data, ch);
	}
	else (*data).sizes[ch] = true;
	for (int j = 0; j < SIZE && numIdx < numbersSize; j++) {
		for (int i = 0; i < SIZE && numIdx < numbersSize; i++) {
			(*data).mat[ch][i][j] = numbers[numIdx++];
		}
	}
}

void printMat(char ch, Matrix data) {/*prints the matrix*/
	if (!data.sizes[ch]) {
		printf("This Matrix Is Empty!\n");
		return;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %8.2lf", data.mat[ch][i][j]);
		}
		printf("\n");
	}
}

void addMat(Matrix data, char mat, char mat1) {
	if (!data.sizes[mat] || !data.sizes[mat1]) {
		printf("One or more of The Matrixes is Empty!\n");
		return;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %8.2lf", data.mat[mat][i][j] + data.mat[mat1][i][j]);
		}
		printf("\n");
	}
}

void addUpdateMat(Matrix *data, char mat, char mat1, char updated) {
	if (!(*data).sizes[mat] || !(*data).sizes[mat1]) {
		printf("One or more of The Matrixes is Empty!\n");
		return;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			(*data).mat[updated][i][j] = ((*data).mat[mat][i][j] + (*data).mat[mat1][i][j]);
		}
	}
	(*data).sizes[updated] = true;
}

void subMat(Matrix data, char mat, char mat1) {
	if (!data.sizes[mat] || !data.sizes[mat1]) {
		printf("One or more of The Matrixes is Empty!\n");
		return;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %8.2lf", data.mat[mat][i][j] - data.mat[mat1][i][j]);
		}
		printf("\n");
	}
}

void subUpdateMat(Matrix *data, char mat, char mat1, char updated) {
	if (!(*data).sizes[mat] || !(*data).sizes[mat1]) {
		printf("One or more of The Matrixes is Empty!\n");
		return;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			(*data).mat[updated][i][j] = ((*data).mat[mat][i][j] - (*data).mat[mat1][i][j]);
		}
	}
	(*data).sizes[updated] = true;
}

void mulScalar(Matrix data, double mul, char mat) {
	if (!data.sizes[mat]) {
		printf("The Matrix is Empty!\n");
		return;
	}
	if (!mul) { initializeMatrix(&data, mat); printMat(mat, data); return; }
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %8.2lf", data.mat[mat][i][j] * mul);
		}
		printf("\n");
	}
}

void mulUpdateScalar(Matrix *data, double mul, char mat, char updated) {
	if (!(*data).sizes[mat]) {
		printf("The Matrix is Empty!\n");
		return;
	}
	if (!mul) { initializeMatrix(data, updated); }
	else {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				(*data).mat[updated][i][j] = (*data).mat[mat][i][j] * mul;
			}
		}
	}
	(*data).sizes[updated] = true;
}

void transMat(Matrix data, char mat) {
	if (!data.sizes[mat]) {
		printf("The Matrix is Empty!\n");
		return;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = i + 1; j < SIZE; j++) {
			double temp = data.mat[mat][i][j];
			data.mat[mat][i][j] = data.mat[mat][j][i];
			data.mat[mat][j][i] = temp;
		}
	}
	printMat(mat, data);
}

void transUpdateMat(Matrix *data, char mat, char updated) {
	if (!(*data).sizes[mat]) {
		printf("The Matrix is Empty!\n");
		return;
	}
	if (mat == updated) {  //if trans_mat A,A
		for (int i = 0; i < SIZE; i++) {
			for (int j = i + 1; j < SIZE; j++) {
				double temp = (*data).mat[mat][i][j];
				(*data).mat[mat][i][j] = (*data).mat[mat][j][i];
				(*data).mat[mat][j][i] = temp;
			}
		}
	}
	else {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				(*data).mat[updated][i][j] = (*data).mat[mat][j][i];
			}
		}
		(*data).sizes[updated] = true;
	}
}

static inline void *MallocOrDie(size_t MemSize) {/*checking the malloc if it fails by some chance*/
	void *AllocMem = malloc(MemSize);
	if (!AllocMem && MemSize) {/*if memsize was 0 , it's obvious malloc wont do memmory allocation and returns null*/
		printf("Could not allocate memory!");
		exit(-1); /*could not continue program*/
	}
	return AllocMem;
}
/*check sub string from , to ,*/
bool readMatSubString(char *subStr) {
	int i = 0, j;
	char *temp = MallocOrDie(sizeof(char)*strlen(subStr) + 1), *prev = NULL;
	while (subStr[i]) {
		j = 0;
		while (subStr[i] && subStr[i] == ' ')i++;//skips spaces
		while (subStr[i] && subStr[i] != ' ' && !isalpha(subStr[i])) {/*gets the subString bettwen ,     ,*/
			temp[j++] = subStr[i++];
		}
		while (subStr[i] && subStr[i] == ' ')i++;//skips spaces
		temp[j] = '\0';
		removeSpaces(subStr), removeSpaces(temp);/*checking if they are same after removing spaces*/
		if (strcmp(temp, subStr) || !temp) {
			return false;
		}
		double d = strtod(temp, &prev);
		/*if there is any number after the current number in the specific substring*/
		if (d == 0 && prev && *prev != '\0' && *prev != ' ') { free(temp); return false; }/*if the it was 0..25*/
		if (prev && *prev != '\0' && *prev != ' ') { free(temp); return false; }/*or 1.25. o anything */
		/*if the pointer to the next substring is anything except space and null terminator*/
		/*like this     ,    65     87   ,*//*or 65../*returns false*/
	}
	if (!(*subStr)) { free(temp); return false; }/*no value in bettwen two commas ,nothing,*/
	free(temp);
	return true;
}

bool checkReadMat(char *command) {
	char subStringBetween[SIZEOFCOMMAND / 2];
	int i = 0, count = 0, j;
	bool end = false;
	while (*command && i < 8) { *command++; i++; }/*skips read_mat (already checked)*/
	i = 0;
	while (command[i] && (isalpha(command[i]) || command[i] == ' ')) {
		if (isalpha(command[i])) {/*counts how many matrixes there is in read_mat (for ex read_mat A B 25.... returns false*/
			count++;
			if (command[i + 1] != ' ')/* if it was read_mat A5 or anything else except space returns false*/
				return false;
		}
		if (count > 1)return false;/*if the user inputed more than 1 matrix in read_mat*/
		i++;
	}
	while (command[i]) { // start checking after read_mat A
		j = 0;
		while (command[i] && command[i] != ',') {/*checks every substring bettwen two commas if there is wrong input*/
			subStringBetween[j++] = command[i++];
		}
		subStringBetween[j] = '\0';
		if (!readMatSubString(subStringBetween))
			return false;
		if (strtod(subStringBetween, NULL) == -1) { end = true; break; }/*reaches -1 ends checking input*/
		i++;
	}
	if (!end && command[i] == ',')return false;
	if (strtod(subStringBetween, NULL) != -1)return false;/*in the end of command there was not a -1 , returns false*/
	return true;
}

void checkIfUpdate(char *command, bool *update, int index) {
	if (index <= 1)return;/*print_mat and read_mat does not require an update or not*/
	/*checks the command if it requires an update or not*/
	char *tempCommand = MallocOrDie(sizeof(char)*(strlen(command) + 1)), *ptr;
	strcpy(tempCommand, command);/*for using the command in strtok*/
	int count = 0, i = 0;
	ptr = strtok(tempCommand, " ABCDEF,");
	if (strcmp(commands[index], "mul_scalar")) {//mul_scalar has numbers in the command
		while (ptr != NULL && !strtod(ptr, NULL)) {/*not skipping numbers*/
			ptr = strtok(NULL, " , ");
			count++;
		}
	}
	else {/*checks except mul_scalar*/
		while (ptr != NULL) {/*skips numbers*/
			ptr = strtok(NULL, " , ");
			count++; /*checks how many matrixes there , if its for update or no*/
		}
	}
	/*update in transmat requires only 2 matrixes*/
	if (count - 1 == 2 && !strcmp(commands[index], "trans_mat"))
		*update = true;
	/*update is on when we have 3 matrixes*/
	else if (count - 1 == 3)
		*update = true;
	free(tempCommand);
}

bool checkPrintMat(char *command) {
	char *tempCommand = MallocOrDie(sizeof(char)*(strlen(command) + 1));
	strcpy(tempCommand, command);
	int i = 0;
	while (i < 9) i++; /*print_mat function's length is 9*/
	removeSpaces(tempCommand + i);/*removes spaces for checking the print mat*/
	bool res = checkEnd(tempCommand + i) && strlen(tempCommand + i) == 1;/*if after print mat the length is 1 only and it has no additional commas after or anything else*/
	free(tempCommand);
	return res;
}

bool checkEnd(char *sub) {
	/*checks ends of command if there any empty , after or some invalid input*/
	while (*sub) {
		if (!(*sub == ',') && !isalpha(*sub))
			return false;
		*sub++;
	}
	if (*(sub - 1) == ',')/*if there was comma in the end of command*/
		return false;
	return true;
}

bool checkAddSubMat(char *command) {
	char *tempCommand = MallocOrDie(sizeof(char)*(strlen(command) + 1));
	strcpy(tempCommand, command);
	int i = 0;
	while (i < 7)i++;/*add_mat function's length*/
	removeSpaces(tempCommand + i);/*removes spaces*/
	/*checks if the length is diffrent than 3 or 5 or it has diffrent things except comma*/
	bool res = checkEnd(tempCommand + i) && (strlen(tempCommand + i) == 5 || strlen(tempCommand + i) == 3);
	free(tempCommand);
	return res;
}

bool checkSubMul(char *subStr, bool flag) {/*flag is used to determine if the substring is number or alphabetic*/
	if (flag) {/*if the substring is alphabetic*/
		return (isalpha(*subStr) && strlen(subStr) == 1);
	}
	else {
		if (*subStr == '0' && strlen(subStr) == 1)return true;
		char *ptr;/*if after B, 25 54,A there two numbers , returns false*/
		strtod(subStr, &ptr);
		if (!strcmp(subStr, ptr))return false;/*if ptr was the same as substr , (there was no number)*/
		if ((*ptr != '\0' && *ptr != ' ') || (isalpha(*ptr)) || strtod(ptr, NULL))/*mul_scalar A , 2 5 ,B*/
			return false;
		return true;
	}
}

bool commaCheck(char *command) {
	char *tempCommand = MallocOrDie(sizeof(char)*(strlen(command) + 1));
	strcpy(tempCommand, command);
	char right = ' ';//using temp value for once
	removeSpaces(tempCommand);/*removes spaces*/
	int i = 0;
	while (tempCommand[i]) {/*checks mul_scalar commas */
		if (tempCommand[i] == ',') {/*checks the right value of end of command if there was empty comma returns false*/
			right = tempCommand[i + 1];
		}
		if (right == '\0') {/*checks if theres a comma in the end of the command*/
			free(tempCommand);
			return false;
		}
		i++;
	}
	free(tempCommand);
	return true;
}

bool checkMulScalar(char *command) {
	int i = 0, count = 0, j = 0;
	bool flag = true;
	char *temp = MallocOrDie(sizeof(char)*strlen(command) + 1);
	while (*command && i < 10) { *command++; i++; }/*skip mul_scalar (already check)*/
	i = 0;
	while (command[i]) {
		j = 0;
		while (command[i] && command[i] != ',') {
			temp[j++] = command[i++];
		}
		temp[j] = '\0';
		if (flag == true)removeSpaces(temp);/*if it was alphabetic check (for A-F argument)*/
		if (!checkSubMul(temp, flag)) { free(temp); return false; }/*true is Alphabetic , false is number*/
		flag = !flag;/*switching flags boolean value ..... A , 25 , B (check switch)*/
		i++;
		count++;
	}
	if (!commaCheck(command))return false;/*explained above(in function)*/
	if (count != 3 && count != 2)return false;/*if mul_scalar arguments more than 3 or less than 3 and valid command , returns false*/
	free(temp);
	return true;
}

bool checkTransMat(char *command) {
	char *tempCommand = MallocOrDie(sizeof(char)*(strlen(command) + 1));
	strcpy(tempCommand, command);
	int i = 0;
	while (i < 9)i++;/*trans_mat function's length is 9*/
	removeSpaces(tempCommand + i);/*checks trans_mat input*/
	bool res = checkEnd(tempCommand + i) && (strlen(tempCommand + i) == 1 || strlen(tempCommand + i) == 3);
	free(tempCommand);
	return res;
}

void removeSpaces(char *str) {/*removes spaces from a string*/
	int i, j;
	int len = strlen(str);
	for (i = 0, j = 0; i < len; i++) {
		str[i - j] = str[i];
		if (str[i] == ' ')/*count how many spaces in string to remove them in the end*/
			j++;
	}
	str[i - j] = '\0';
}

bool checkStopFunction(char *command) {
	/*check if first four letters is stop*/
	return command[0] == 's' && command[1] == 't' && command[2] == 'o' && command[3] == 'p';
}

void initializeAllMatrixes(Matrix *data) {/*initialize all matrixes to Zero!*/
	for (int x = 0; x < TOTAL; x++) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				(*data).mat[x][i][j] = 0;
			}
		}
		(*data).sizes[x] = false;
	}
}

int getFunction(char *command, bool *update) {
	/*return the function that user inputed and check if its legal and checks if it requires update*/
	char tempCommand[SIZEOFCOMMAND];
	bool flag = false;
	int i, j = 0, count = 0;
	for (int x = 0; command[x] && command[x] != ' '; x++) { tempCommand[j++] = command[x]; }
	tempCommand[j] = '\0';
	for (i = 0; i < TOTAL; i++) {
		if (!strcmp(tempCommand, commands[i])) {
			flag = true;
			break;
		}
	}
	if (!flag)/*no legal function found*/
		return -1;
	checkIfUpdate(command, update, i);
	return i;
}

char *getMatrixes(char *command) {
	/*check if the matrix is legal and returns the matrix*/
	int j = 0, i;
	char tempCommand[SIZEOFCOMMAND];
	strcpy(tempCommand, command);
	char *indexs = MallocOrDie(sizeof(char) * 3), *ptr;
	if (indexs == NULL)
		return NULL;
	ptr = strtok(tempCommand, "ABCDEF ");
	for (i = 0; i < SIZE && ptr; i++) {
		if (ptr) {/*if the ptr is not null*/
			ptr = strtok(NULL, " , ");
			if (ptr && !strtod(ptr, NULL) && (*ptr <= 'F' && *ptr >= 'A'))/*if the char in range of A-F and its not a number*/
				indexs[j++] = TOINDEX(*ptr);
			else if (ptr && strlen(ptr) == 1 && !isdigit(*ptr) && !(*ptr <= 'F' && *ptr >= 'A')) {
				/*if the string's length is 1 and not a digit and not in range of A-F , no such matrix*/
				free(indexs);
				return NULL;
			}
		}
	}
	if ((j == 0 && ptr != NULL) || i <= 1) {/*nothing in indexes array of chars (no char in the command)*/
		free(indexs);
		return NULL;
	}
	return indexs;/*returns all the matrixes in the command that are valid*/
}

double *getNumbers(char *command, int *length) {
	/*returns The Numbers in the command*/
	char tempCommand[SIZEOFCOMMAND];
	double *numbers = MallocOrDie(sizeof(double) * 16);
	int count = 0; // Length
	bool checkEndOfInput = false;/*checks if there is -1 at the end of the command*/
	strcpy(tempCommand, command);/*temp command for use*/
	char *getnum = strtok(tempCommand, "ABCDEF");
	getnum = strtok(NULL, ",");
	if (getnum && strtod(getnum, NULL) != -1)/*if its not -1 in the frst time it will stop*/
		numbers[count++] = strtod(getnum, NULL);
	else { free(numbers); return NULL; }/*no can do*/
	while (getnum) {
		getnum = strtok(NULL, ",");
		if (getnum && strtod(getnum, NULL) == -1) {/*if found -1 , ends the function.*/
			checkEndOfInput = true;
			break;
		}
		else if (getnum != NULL && count < 16) {/*gets the 16 or less numbers only in the command*/
			numbers[count++] = strtod(getnum, NULL);
		}
	}
	*length = count;
	return numbers;
}

double getMul(char *command) {
	/*returns the number in mul_scalar comand*/
	double mul;
	char tempCommand[SIZEOFCOMMAND], * prevPointer = NULL;
	strcpy(tempCommand, command);
	char *ptr = strtok(tempCommand, "ABCDEF ");
	while (ptr && !strtod(ptr, &prevPointer)) {
		ptr = strtok(NULL, " , ");
	}
	if (!ptr && prevPointer)
		mul = strtod(prevPointer, NULL);
	else mul = strtod(ptr, NULL);
	return mul;
}

void initializeMatrix(Matrix *data, char mat) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			(*data).mat[mat][i][j] = 0;
		}
	}
}