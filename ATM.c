#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
int otpGenarator(){
    srand(time(0));
    int part1 = rand() % 1000;    
    int part2 = rand() % 1000;    
    int part3 = rand() % 1000;    
    int part4 = rand() % 1000;    
    int otp1 = (part1 * 1000) + part2 + part3 + part4;
    // printf("Your 6-digit OTP is: %6d\n", otp1);
    return otp1;
}
int limitPin(){
    char input[5];
    int number;
    scanf("%4s", input); 
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 4) {
        return -1; 
    }
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return -1; 
        }
    }
    number = atoi(input);
    return number;
}

struct ATM{
    int pin;
    char name[30];
    int balance;
    int wcash;
    int dcash;
}p1,p2;
int main(){
    p1.pin=1236;
    p1.balance=0;
    strcpy(p1.name, "Ritam Majumdar");
    int log,new,votp,otp,pass1,pass2;
    printf("*******************************\n");
    printf("New customer-->1\nOld customer-->Any key\n");
    printf("*******************************\n>>");
    scanf("%d",&log);
    getchar();
    if(log==1){
        while(1){
            printf("*******************************\n");
            printf("Generate OTP-->1\nEnter OTP-->2\nquit-->3\n");
            printf("*******************************\n>>");
            scanf("%d",&new);
            switch(new){
                case 1:
                   otp=otpGenarator();
                   printf("Your OTP is: %d\n",otp);
                    break;
                case 2:
                    printf("Enter OTP: ");
                    scanf("%d",&votp);
                    if(otp==votp){
                        printf("\nEnter 4-digit pin: ");
                        pass1=limitPin();
                        if (pass1 != -1) {
                            printf("Re-enter the pin: ");
                            scanf("%d", &pass2);
                            getchar(); 
                             if (pass1 == pass2) {
                                p2.pin = pass1; 
                                printf("\nAccount PIN successfully generated.\n");
                                break;
                            } else {
                                printf("\nPins do not match. Try again.\n");
                            }
                        } else {
                            printf("\nInvalid PIN format. Try again.\n");
                        }
                    }else{
                        printf("\nOTP does not match!!");
                    }
                    break;
                case 3:
                    return 0;
                default:
                    printf("Invalid details!!\n");
            }
        }
    }else{
        int pin1,amount,dep;
        printf("Enter your 4-digit Pin: ");
        scanf("%d",&pin1);
        if(p1.pin==pin1){
            while(1){
                int choice;
                printf("*******************************\n");
                printf("Name:%s",p1.name);
                printf("\nBalance->1\nwithdrawal->2\nDeposite->3\nquit->4\n");
                printf("*******************************\n>>");
                scanf("%d",&choice);
                switch(choice){
                    case 1:
                        printf("Your balance: %d\n",p1.balance);
                        break;
                    case 2://withdrawal
                        printf("\nEnter amount for withdrawal: ");
                        scanf("%d",&amount);
                        if(p1.balance>=amount ){
                            printf("\nPlease wait transaction is on process\n");
                            p1.balance=p1.balance-amount;
                        }else{
                            printf("\nInvalid amount\n");
                        }
                        break;
                    case 3://deposite
                        printf("\nEnter Amount for deposite: ");
                        scanf("%d",&dep);
                        p1.balance=p1.balance+dep;
                        break;
                    case 4:
                        return 0;
                    default:
                        printf("\nInvalid details!");
                        break;       
            }
            }
        }
        else{
            printf("\nInvalid pin\n");
        }
        printf("\nThank You\n");
    }
    return 0;  
}