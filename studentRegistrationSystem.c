/*
==========================================
          CO253 - GROUP PROJECT
------------------------------------------
E/17/370 - Wanninayake R.B.S.W.M.L.R.B
E/17/371 - Warnakulasuriya R
E/17/372 - Warnasooriya W.A.V.G
E/17/374 - Weeerasekara K.A
==========================================   
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define batchSize 420
#define nameSize 69

int mainMenu();
void newRecord();
void printRecord();
void printAll();
void deleteRecord();
void capitalize(char* word);

int batchArray[(batchSize)*4]={0};
int regNoArray[(batchSize)*4]={0};
char* firstNameArray[(batchSize)*4][(nameSize)]={0};
char* lastNameArray[(batchSize)*4][(nameSize)]={0};
float gpaArray[(batchSize)*4]={0};

int main() {
    // printRecord();
    return 0;
}
// generate a text-based main menu and return the selected option
int mainMenu() {
    int option;
    printf("--------------------------------------\nA VOLATILE STUDENT REGISTRATION SYSTEM\n--------------------------------------\n");
    printf("0. Quit\n1. Insert a student record\n2. Print a student record\n3. Print all student records\n4. Delete a student record\n");
    printf("------------------\nENTER OPTION [0-4]\n------------------\n>>> ");
    scanf("%d",&option);
    return option;
}

// make a new student record
void newRecord() {
    char firstName[(nameSize)];
    char lastName[(nameSize)];
    int i;
    // find the first empty record
    for (i=0; i<(batchSize); i++) {

        if (batchArray[i]==0){
            break;
        }
    }
    printf("Enter batch (14/15/16/17): ");
    scanf("%d",batchArray+i);
    printf("Enter registration number: ");
    scanf("%d",regNoArray+i);
    printf("Enter first name         : ");
    scanf("%s",firstName);
    printf("Enter last name          : ");
    scanf("%s",lastName);
    printf("Enter cumulative GPA     : ");
    scanf("%f",gpaArray+i);
    // capitalize firstName and lastName and store
    capitalize(firstName);
    capitalize(lastName);
    memcpy(firstNameArray[i], firstName, sizeof(firstNameArray[i]));
    memcpy(lastNameArray[i], lastName, sizeof(firstNameArray[i]));
}

// print the recored corresponding to a given regNo
void printRecord() {
    char query[9];
    int queryBatch;
    int queryRegNo;
    printf("Enter registration number: ");
    scanf("%s",&query);
    // obtain batch and regNo from search query
    queryBatch=(query[2]-48)*10+(query[3]-48);
    queryRegNo=(query[5]-48)*100+(query[6]-48)*10+(query[7]-48);

    // printf("Student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",firstNameArray[0],lastNameArray[0],batchArray[0],regNoArray[0],gpaArray[0]);
}

// capitalize the first letter of the input string
void capitalize(char* word) {
    int i=1;
    word[0]=toupper(word[0]);

    while (word[i]!=0) {
        word[i]=tolower(word[i]);
        i++;
    }
}
