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
#include <stdbool.h>
#define batchSize 420
#define nameSize 69

//record management functions
int mainMenu();
void newRecord();
void printRecord(int recordIndex);
void printAllRecords();
void deleteRecord();

//misc functions
void capitalize(char* word);
int findIndex();
void clearInputBuffer();
void generateDemoRecord();

int batchArray[batchSize*4]={0};
int regNoArray[batchSize*4]={0};
char* firstNameArray[batchSize*4][nameSize]={0};
char* lastNameArray[batchSize*4][nameSize]={0};
float gpaArray[batchSize*4]={0};

int main() {
    // generateDemoRecord();
    printf("--------------------------------------------\nA VOLATILE STUDENT RECORD MAINTENANCE SYSTEM\n--------------------------------------------\n");
    printf("0. Quit\n1. Insert a Student Record\n2. Print a Student Record\n3. Print all Student Records\n4. Delete a Student Record\n");
    bool loop=1;

    while (loop) {

        switch(mainMenu()) {

            case 0:
                loop=0;
                break;

            case 1:
                newRecord();
                printf("\n");
                break;

            case 2:
                printRecord(findIndex());
                printf("\n");
                break;

            case 3:
                printAllRecords();
                printf("\n");
                break;

            case 4:
                deleteRecord(findIndex());
                printf("\n");
                break;

            default:;
        }
    }
    return 0;
}
//generate a text-based main menu and return the selected option
int mainMenu() {
    int option;
    printf("------------------\nENTER OPTION [0-4]\n------------------\n");
    scanf("%d",&option);
    clearInputBuffer();
    return option;
}
//make a new student record
void newRecord() {
    int batch;
    int regNo;
    char firstName[nameSize];
    char lastName[nameSize];
    float gpa;
    int i;
    int j;
    bool recordExists=0;
    //find the first empty record
    for (i=0; i<batchSize; i++) {

        if (batchArray[i]==0){
            break;
        }
    }
    //get student ID
    printf("Enter the batch (14/15/16/17): ");
    scanf("%d",&batch);
    clearInputBuffer();
    printf("Enter the registration number: ");
    scanf("%d",&regNo);
    clearInputBuffer();

    //check for duplicate student ID
    for (j=0; j<batchSize*4; j++) {
        
        if (regNoArray[j]==regNo && batchArray[j]==batch) {
            recordExists=1;
            break;
        }
    }
    if (recordExists) {
        printf("Duplicate student ID. Record already exists.");
    }
    else {
        //contunue collecting data
        printf("Enter the first name         : ");
        scanf("%[^\n]s",firstName); //include everything except newline character in scanset
        clearInputBuffer();
        printf("Enter the last name          : ");
        scanf("%[^\n]s",lastName);
        clearInputBuffer();
        printf("Enter the cumulative GPA     : ");
        scanf("%f",&gpa);
        clearInputBuffer();
        //process and store data
        batchArray[i]=batch;
        regNoArray[i]=regNo;
        capitalize(firstName);
        capitalize(lastName);
        memcpy(firstNameArray[i], firstName, sizeof(firstNameArray[i]));
        memcpy(lastNameArray[i], lastName, sizeof(firstNameArray[i]));
        gpaArray[i]=gpa;
    }
}
//print the recored with given regNo
void printRecord(int recordIndex) {

    if (recordIndex==-1) {
        printf("No student with the given registration number!\n");
    }
    else {
        printf("The student %s %s (E/%02d/%03d) has a cumulative GPA of %.2f\n",firstNameArray[recordIndex],lastNameArray[recordIndex],batchArray[recordIndex],regNoArray[recordIndex],gpaArray[recordIndex]);
    }
}
//print all existing records
void printAllRecords() {
    int i;
    
    for (i=0; i<batchSize*4; i++) {

        if (batchArray[i]!=0) {
            printRecord(i);
        }
    }
}
//delete the record with given regNo
void deleteRecord(int recordIndex) {

    if (recordIndex==-1) {
        printf("No student with the given registration number!\n");
    }
    else {
        int i;
        batchArray[recordIndex]=0;
        regNoArray[recordIndex]=0;
        gpaArray[recordIndex]=0;

        for (i=0; i<nameSize; i++) {
            firstNameArray[recordIndex][i]=0;
            lastNameArray[recordIndex][i]=0;
        }
        printf("Delete successful!\n");
    }    
}
//capitalize the first letter of the input string
void capitalize(char* word) {
    int i=0;
    bool firstLetter=1;

    while (word[i]!='\0') {

        if (word[i]==' ') {
            firstLetter=1;
        }
        else {
            
            if (firstLetter) {
               word[i]=toupper(word[i]);
            }
            else {
                word[i]=tolower(word[i]);
            }
            firstLetter=0;
        }
        i++;
    }
}
//get query e no. and find corresponding array index
int findIndex() {
    char query[9];
    char queryFaculty;
    int queryBatch;
    int queryRegNo;
    int i;
    bool recordExists=0;
    printf("Enter registration number: ");
    scanf("%s",&query);
    clearInputBuffer();
    //obtain faculty, batch, and regNo from search query
    queryFaculty=toupper(query[0]);
    queryBatch=(query[2]-48)*10+(query[3]-48);
    queryRegNo=(query[5]-48)*100+(query[6]-48)*10+(query[7]-48);
    
    //find idex of matching regNo and batch
    for (i=0; i<batchSize*4; i++) {
        
        if (queryFaculty=='E' && regNoArray[i]==queryRegNo && batchArray[i]==queryBatch) {
            recordExists=1;
            break;
        }
    }
    if (recordExists) {
        return i;
    }
    else {
        return -1;
    }
}
//clear input buffer until newline character is encountered
void clearInputBuffer() {
    while (getchar() != '\n' && getchar() != EOF);
}
//creat example record entries for testing/debugging
void generateDemoRecord() {
    //demo record 1
    batchArray[4]=17;
    regNoArray[4]=371;
    memcpy(firstNameArray[4], "Rasika", sizeof(firstNameArray[4]));
    memcpy(lastNameArray[4], "Warnakulasuriya", sizeof(firstNameArray[4]));
    gpaArray[4]=3.9;
    //demo record 2
    batchArray[2]=17;
    regNoArray[2]=370;
    memcpy(firstNameArray[2], "Lahiru", sizeof(firstNameArray[2]));
    memcpy(lastNameArray[2], "Range", sizeof(firstNameArray[2]));
    gpaArray[2]=3.8;
    //demo record 3
    batchArray[1]=17;
    regNoArray[1]=372;
    memcpy(firstNameArray[1], "Vano", sizeof(firstNameArray[1]));
    memcpy(lastNameArray[1], "Warna", sizeof(firstNameArray[1]));
    gpaArray[1]=3.7;
    //demo record 4
    batchArray[6]=17;
    regNoArray[6]=374;
    memcpy(firstNameArray[6], "Aveesha", sizeof(firstNameArray[6]));
    memcpy(lastNameArray[6], "Upasaka", sizeof(firstNameArray[6]));
    gpaArray[6]=3.6;
    //demo record 5
    batchArray[8]=1;
    regNoArray[8]=1;
    memcpy(firstNameArray[8], "A", sizeof(firstNameArray[8]));
    memcpy(lastNameArray[8], "B", sizeof(firstNameArray[8]));
    gpaArray[8]=1;
}