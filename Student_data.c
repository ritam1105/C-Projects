#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void StudentData(){
    while(1){
        FILE* ptr;
        int sd;
        ptr = fopen("./name.txt", "a");
        if (ptr == NULL) {
            printf("Error Occurred While writing to a text file!\n");
            exit(1);
        }
        int age;
        int roll;
        float gpa;
        char str[100];
        //inputs  
        printf("Enter Student name: ");
        while (getchar() != '\n');
        fgets(str, sizeof(str), stdin);  
        str[strcspn(str, "\n")] = 0;

        printf("Age: ");
        scanf("%d",&age);

        printf("Roll no: ");
        scanf("%d",&roll);

        while (getchar() != '\n');
        printf("Gpa: ");
        scanf("%f",&gpa);

        fprintf(ptr, "Name: %s\n", str);
        fprintf(ptr, "Age: %d\n", age);
        fprintf(ptr, "Roll: %d\n", roll);
        fprintf(ptr, "GPA: %.2f\n", gpa);
        fprintf(ptr, "Status: %s\n", "Under Graduate");
        fclose(ptr);
        printf("\nData saved successfully\n");
        
        printf("Want to continue-->1  or Quit-->any key\n>>");
        scanf("%d",&sd);
        if(sd==1){
            continue;
        }else{
            break;
        }

    }
}
void Studentinfo(){
    FILE* ptr;
    ptr = fopen("./name.txt", "r");
    if (ptr == NULL) {
        printf("Error Occurred While reading the text file!\n");
        exit(1);
    }
    int roll, searchRoll;
    int age;
    float gpa;
    char name[100];
    char status[50];
    int found = 0;

    printf("Enter Roll number to search: ");
    scanf("%d", &searchRoll);

    while (fscanf(ptr, "Name: %[^\n]\nAge: %d\nRoll: %d\nGPA: %f\nStatus: %[^\n]\n", name, &age, &roll, &gpa, status) != EOF) {
        if (roll == searchRoll) {
            printf("\nStudent Details:\n");
            printf("Name: %s\n", name);
            printf("Age: %d\n", age);
            printf("Roll: %d\n", roll);
            printf("GPA: %.2f\n", gpa);
            printf("Status: %s\n", status);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No student found with Roll number %d\n", searchRoll);
    }

    fclose(ptr);
}
void editdata() {
    int age;
    int roll, rollno;
    float gpa;
    char name[100];
    char status[50];
    int found = 0;
    FILE *ptr, *tempPtr;

    ptr = fopen("./name.txt", "r");
    tempPtr = fopen("./temp.txt", "w");
    if (ptr == NULL || tempPtr == NULL) {
        printf("Error Occurred While accessing the files!\n");
        exit(1);
    }
    printf("Enter Roll number to edit: ");
    scanf("%d", &rollno);
    while (fscanf(ptr, "Name: %[^\n]\nAge: %d\nRoll: %d\nGPA: %f\nStatus: %[^\n]\n", name, &age, &roll, &gpa, status) != EOF) {
        if (roll == rollno) {
            printf("Enter new Student name: ");
            while (getchar() != '\n');
            fgets(name, sizeof(name), stdin);  
            name[strcspn(name, "\n")] = 0;
            printf("New Age: ");
            scanf("%d", &age);
            while (getchar() != '\n');
            printf("New GPA: ");
            scanf("%f", &gpa);

            // Write the updated data to the temp file
            fprintf(tempPtr, "Name: %s\n", name);
            fprintf(tempPtr, "Age: %d\n", age);
            fprintf(tempPtr, "Roll: %d\n", rollno);
            fprintf(tempPtr, "GPA: %.2f\n", gpa);
            fprintf(tempPtr, "Status: %s\n", "Under Graduate");
            found = 1;
        } else {
            // Copy the original data to the temp file
            fprintf(tempPtr, "Name: %s\n", name);
            fprintf(tempPtr, "Age: %d\n", age);
            fprintf(tempPtr, "Roll: %d\n", roll);
            fprintf(tempPtr, "GPA: %.2f\n", gpa);
            fprintf(tempPtr, "Status: %s\n", status);
        }
    }
    fclose(ptr);
    fclose(tempPtr);
    if (found) {
        remove("./name.txt");
        rename("./temp.txt", "./name.txt");
        printf("\nData edited successfully\n");
    } else {
        printf("Roll number %d not found. Try again with a correct Roll number.\n", rollno);
        remove("./temp.txt"); 
    }
}
void deleteData() {
    int roll, rollno;
    int age;
    float gpa;
    char name[100];
    char status[50];
    int found = 0;
    FILE *ptr, *tempPtr;

    ptr = fopen("./name.txt", "r");
    tempPtr = fopen("./temp.txt", "w");
    if (ptr == NULL || tempPtr == NULL) {
        printf("Error Occurred While accessing the files!\n");
        exit(1);
    }

    printf("Enter Roll number to delete: ");
    scanf("%d", &rollno);

    while (fscanf(ptr, "Name: %[^\n]\nAge: %d\nRoll: %d\nGPA: %f\nStatus: %[^\n]\n", name, &age, &roll, &gpa, status) != EOF) {
        if (roll == rollno) {
            found = 1;
            printf("Record with Roll number %d has been deleted.\n", rollno);
            // Skip writing this record to the temp file, effectively deleting it
        } else {
            // Copy the original data to the temp file
            fprintf(tempPtr, "Name: %s\n", name);
            fprintf(tempPtr, "Age: %d\n", age);
            fprintf(tempPtr, "Roll: %d\n", roll);
            fprintf(tempPtr, "GPA: %.2f\n", gpa);
            fprintf(tempPtr, "Status: %s\n", status);
        }
    }

    fclose(ptr);
    fclose(tempPtr);

    if (found) {
        // Replace the original file with the updated temp file
        remove("./name.txt");
        rename("./temp.txt", "./name.txt");
    } else {
        printf("Roll number %d not found. No record deleted.\n", rollno);
        remove("./temp.txt");  // Delete the temporary file if no changes were made
    }
}


int main(){
    FILE* ptr;
    int choi;
    while(1){
        printf("*******************************\n");
        printf("Student data entry-->1\nGet info of a student-->2\nedit student data-->3\nDelete student data-->4\nQuit-->5\n");
        printf("*******************************\n>>");
        scanf("%d",&choi);
        switch(choi){
            case 1:
                StudentData();
                break;
            case 2:
                Studentinfo();
                break;
            case 3:
                editdata();
                break;
            case 4:
                deleteData();
                break;
            case 5:
                break;
            default:
                printf("please enter valid details\n\n");
        }
        if(choi==5){
            break;
        }
    }
return 0;
}
