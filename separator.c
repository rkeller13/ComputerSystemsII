//Robert Keller
//CSC 407 HW3

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define STRING_LEN 100


struct Word {
  char* textPtr_;
  struct Word*	nextPtr_;
};

struct Word* obtainCommaSeparatedList (const char* inputString) {

	char* commaPtr = strchr(inputString,',');
	char* remainingString;
	char* eachWord;
	size_t length = strlen(inputString);
	size_t wordLength;
	struct Word* toReturn = (struct Word*)malloc(sizeof(struct Word));

	toReturn -> textPtr_ = eachWord;

	if (commaPtr == NULL) {
		wordLength = length;
		remainingString = inputString;
		eachWord = (char*)malloc(wordLength + 1);
		strncpy(eachWord, inputString, wordLength);
		toReturn -> textPtr_ = eachWord;
		toReturn -> nextPtr_ = NULL;
		return(toReturn);
	}
	else {
		wordLength = commaPtr - inputString;
		remainingString = (char*)malloc(length - wordLength);
		eachWord = (char*)malloc(wordLength + 1);
		strncpy(eachWord, inputString, wordLength);
		toReturn -> textPtr_ = eachWord;
		commaPtr++;
		strncpy(remainingString, commaPtr, (length - wordLength + 1));
		toReturn -> nextPtr_ = obtainCommaSeparatedList(remainingString);
	}

	return(toReturn);
}

void printCommaSeparatedList (const struct Word* inputList) {
	printf("%s\n", inputList -> textPtr_);
	if (inputList -> nextPtr_ == NULL) {
		return;
	}
	else {
		printCommaSeparatedList(inputList->nextPtr_);
	}
}

void freeCommaSeparatedList (struct Word* inputList) {
	if (inputList -> nextPtr_ == NULL) {
		free(inputList -> textPtr_);
		return;
	}
	else {
		free(inputList -> textPtr_);
		freeCommaSeparatedList(inputList -> nextPtr_);
	}
}

int main() {
	char textInput[STRING_LEN];
	char* cPtr;
	struct Word* separatedList;


	printf("Please enter a line of text: ");
	fgets(textInput, STRING_LEN, stdin);
	cPtr = strchr(textInput, '\n');
	if (cPtr != NULL) {
		*cPtr = '\0';
		separatedList = obtainCommaSeparatedList(textInput);
		printCommaSeparatedList(separatedList);
		freeCommaSeparatedList(separatedList);
	}

	return(EXIT_SUCCESS);
}


