#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

#define MAX_YR 9999
#define MIN_YR 1900

#define FILE_NAME *Bankmanagementsystem.bin*
#define MAX_NAME 100
#define MAX_DOB 50
#define FILE_HEADER_SIZE sizeof(sFileHeader)

//to store house address
typedef struct
{
    int street_num;
    char street_name;
    char state;
}HA;

//store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
}Date;

typedef struct
{
    unsigned int citizenship_number;
    unsigned int account_number;
    float amount_deposit[50];
    char name[MAX_NAME];
    Date date_of_birth;
    HA house_address;
    Date deposit;
    Date withdrawal;
}bank_account_info,transaction;

void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      BANK management System Project in C       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
void welcomeMessage()
{
    headMessage("MADE BY FEYIN");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 BANK                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;

void new_acc()
{
    int days;
    bank_account_info addbankInfoIntoDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD ACCOUNT INFO");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tCITIZENSHIP NUMBER = ");
    fflush(stdin);
    scanf("%u",&addbankInfoIntoDataBase.citizenship_number);
    do
    {
        printf("\n\t\t\ Name  = ");
        fflush(stdin);
        fgets(addbankInfoInDataBase.name,MAX_NAME,stdin);
        status = isNameValid(addbankInfoIntoDataBase.name);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tACCOUNT NUMBER = ");
        fflush(stdin);
        scanf("%u",&addbankInfoIntoDataBase.account_number,stdin);
    }
    while(!status);


    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date of birth in format (day/month/year): ");
        scanf("%d/%d/%d",&addbankInfoIntoDataBase.date_of_birth.dd,&addbankInfoIntoDataBase.date_of_birth.mm,&addbankInfoIntoDataBase.date_of_birth.yyyy);
        //check date validity
        status = isValidDate(&addbankInfoIntoDataBase.date_of_birth);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    do{



        printf("\n\t\t\tEnter house address in format(street number/street name/state): ");
        scanf("%d/%s/%s",&addbankInfoIntoDataBase.house_address.street_num,&addbankInfoIntoDataBase.house_address.street_name,&addbankInfoIntoDataBase.house_address.state);
        //check date validity

    }
    do{
        printf("\n\t\t DEPOSIT AMMOUNT= ");
        scanf("%f",&addbankInfoIntoDataBase.amount_deposit);
        printf("\n\t\t ENTER DEPOSIT DATE IN (day/month/year)");
        scanf("%d%d%d",&addbankInfoIntoDataBase.deposit.dd,&addbankInfoIntoDataBase.deposit.mm,&addbankInfoIntoDataBase.deposit.yyyy);
    }
    while(!status);
    fwrite(&addbankInfoIntoDataBase,sizeof(addbankInfoIntoDataBase), 1, fp);
    fclose(fp);


void transaction()
{
    int choice=0;
    int test=0;
    bank_account_info addbankInfoIntoDataBase={0};
    char name[MAX_NAME]={0};
    found=0;
    FILE *fp,*tmpFp;
    fp=fopen("FILE_NAME","rb");
    tmpFp=fopen("tmp.bin","wb");


    headMessage("TRANSACTION");
    printf("\n ENTER ACCOUNT NAME = ");
    fgets(name,MAX_NAME,stdin);
    while(fread(&addbankInfoIntoDataBase,sizeof(addbankInfoIntoDataBase),1,fp))
    {
        if(!strcmp(addbankInfoIntoDataBase.name,name))
        {
            found=1;
            break;
        }
    }
    if(found)
    {
        printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
                scanf("%d",&choice);
                if (choice==1)
                {
                    printf("Enter the amount you want to deposit:$ ");
                    scanf("%f",&transaction.amount_deposit);
                    addbankInfoIntoDataBase.amount_deposit+=transaction.amount_deposit;
                    fprintf(newrec,"%d%d%d",&addbankInfoIntoDataBase.deposit.dd,&addbankInfoIntoDataBase.deposit.mm,&addbankInfoIntoDataBase.deposit.yyyy);
                    printf("\n\nDeposited successfully!");
                }
                else
                {
                    printf("Enter the amount you want to withdraw:$ ");
                    scanf("%f",&transaction.amount_deposit);
                    addbankInfoIntoDataBase.amount_deposit-=transaction.amount_deposit;
                    fprintf(newrec,"%d%d%d",&addbankInfoIntoDataBase.withdrawal.dd,&addbankInfoIntoDataBase.withdrawal.mm,&addbankInfoIntoDataBase.withdrawal.yyyy);
                    printf("\n\nWithdrawn successfully!");
                }

            }
            else
            {
                fprintf(newrec,"%d%d%d",&addbankInfoIntoDataBase.deposit.dd,&addbankInfoIntoDataBase.deposit.mm,&addbankInfoIntoDataBase.deposit.yyyy);
            }
    }
    fclose(fp);
   fclose(tmpFp);
   remove("FILE_NAME");
   rename("tmp.bin","FILE_NAME");

   printf("\n\t\t press any key to go to main menu");
fflush(stdin);
getchar();


}

check_balance()
{
    int foiund=0;
    char name[MAX_NAME]={0};
    bank_account_info addbankInfoIntoDataBase={0};
    transaction transactionamount={0};
    File *fp=NULL;
    unsigned int countbank=1;

    headMessage(CHECK BALANCE);
    fp=fopen(FILE_NAME,"rb");
    if (fp==NULL)
    {
        printf("FILE IS NOT OPENED\n");
        exit(1);
    }
    printf("enter account name= ");
    fflush(stdin);
    fgets(name,MAX_NAME,stdin);

    while(fread(&addbankInfoIntoDataBase,sizeof(addbankInfoIntoDataBase),1,fp))
    {
        if(!strcmp(addbankInfoIntoDataBase.name,name))
        {
            found=1;
            break;
        }
    }
    if(found)
    {
        printf("%s your account balance is %f",addbankInfoIntoDataBase.name,addbankInfoIntoDataBase.amount_deposit);

    }
    else
    {
        printf("\n\t\t no record");
    }
    fclose(fp);
    printf("\n\t\t\t press any key to go to main menu");
    getchar();
}

oid menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.NEW ACCOUNT");
        printf("\n\t\t\t2.TRANSACTION");
        printf("\n\t\t\t3.CHECK BALANCE");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            new_acc();
            break;
        case 2:
            transaction();
            break;
        case 3:
            checkBalance();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}

int isFileExist(const char* path)
{
    //try to open file
    FILE *fp=fopen(path,"rb");
    int status=0;
    //if file does not exist
    if(fp!=NULL)
    {
        status=1;
        //if file exists hence close file
        fclose(fp);
    }
    return status;
}

//create file
void init()
{
    FILE *fp=NULL;
    int status=0;

    status=isFileExist(FILE_NAME);
    if(!status)
    {
        fp=fopen(FILE_NAME, "wb");
        if(fp!=NULL)
        {
            fwrite(&FILE_NAME,sizeof(FILE_NAME),1,fp);
            fclose(fp);
        }
    }
}
int main()
{
    init();
    welcomeMessage();
    return 0;
}

