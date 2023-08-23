#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct login
{
    char fname[30];
    char lname[30];
    char username[30];
    char password[20];
}login1;

typedef struct student{
	int rno;
	char name[20];
	char address[25];
	struct subject{
		//int subcode;
		char subname[15];
		int marks;
	}sub[3];
	int total;
	float per;
}student;

void create()
{
	student *s;   //here pointer is crested so that we can take any number of input
	FILE *fp;
	int n,i,j;
	printf("\n\tPLEASE, ENTER THE NUMBER OF STUDENTS : ");
	scanf("%d",&n);
	
	s = (student*) calloc(n, sizeof(student));
	fp =fopen("mystudents.txt","w");
	
	for(i=0;i<n;i++)
	{
		s[i].total=0;
		s[i].per=0;
		printf("\tEnter Details of Student %d",i+1);
		printf("\n\tRoll Number: ");
		scanf("%d",&s[i].rno);
		fflush(stdin);
		printf("\tName: ");
		scanf("%s",s[i].name);
		printf("\tAddress: ");
		scanf("%s",s[i].address);
		
		for(j=0;j<3;j++)
		{
			printf("\tMarks in subject %d: ",j+1);
			scanf("%d",&s[i].sub[j].marks);
			s[i].total+= s[i].sub[j].marks;
		}
		s[i].per=s[i].total/3.0 ;
		fwrite(&s[i],sizeof(student),1,fp);
	}
	fclose(fp);
	system("cls");
}
void display()
{
	student s1;
	FILE *fp;
	int j;
	printf("%-3s %-12s %-15s %-15s %-15s %-12s %-10s %-10s\n" ,"R.N","Name","Address","Maths","physics","Computer"," 	 Total","Percentage" );
	fp = fopen("mystudents.txt","r");
	while(fread(&s1,sizeof(student),1,fp))
	{
	
		printf("%-3d %-12s %-15s",s1.rno,s1.name,s1.address);
		
		for(j=0;j<3;j++)
		{
			printf("%-17d",s1.sub[j].marks);
		}
		printf("%-8d %6.2f\n",s1.total,s1.per);
	}
	printf("\n\n");
	fclose(fp);
}
void append()
{
	
	student *s;   //here pointer is crested so that we can take any number of input
	FILE *fp;
	int n,i,j;
	printf("\tEnter no of students:");
	scanf("%d",&n);
	
	s = (student*) calloc(n, sizeof(student));
	fp =fopen("mystudents.txt","a");
	
	for(i=0;i<n;i++)
	{
		s[i].total=0;
		s[i].per=0;
		printf("\n\tEnter details of Student %d",i+1);
		printf("\n\t Roll No: ");
		scanf("%d",&s[i].rno);
		fflush(stdin);
		printf("\tName: ");
		scanf("%[^\n]s",s[i].name);
		printf("\tAddress: ");
		scanf("%s",s[i].address);
		
		for(j=0;j<3;j++)
		{
			printf("\tMarks in Subject %d :",j+1);
			scanf("%d",&s[i].sub[j].marks);
			s[i].total+= s[i].sub[j].marks;
		}
		s[i].per=s[i].total/3.0 ;
		fwrite(&s[i],sizeof(student),1,fp);
	}
	fclose(fp);
	system("cls");
}
void noofrec(){
	student s1;
	FILE * fp;
	fp = fopen("mystudents.txt","r");
	fseek(fp,0,SEEK_END);
	int n= ftell (fp)/ sizeof(student);
	printf("\n\n No of records is :%d\n\n ",n);
	fclose(fp);
	//system("cls");
}

void search()
{
	char sname[20];
	student s1;
	FILE *fp;
	int j, rno, found=0 , i;
	fp = fopen("mystudents.txt","r");
	printf("\t 1.search by name: \n\t 2.roll number:\n");
	scanf("%d",&i);
	if(i==1){
	printf("\tEnter name to search:\n");
	scanf("%s",&sname);
	}
   if(i==2)
	{
	printf("\tEnter a roll number to search:\n");
	scanf("%d",&rno);
	}
	while(fread(&s1,sizeof(student),1,fp))
	{
		if(s1.rno == rno || strcmp(sname,s1.name)== 0)
		{
		found=1;
		printf("%-3s %-12s %-15s %-15s %-15s %-12s %-10s %-10s\n" ,"R.N","Name","Address","Maths","physics","Computer"," 	 Total","Percentage" );
		//printf("\n R.N	Name		Address	     Math   Physics  Computer		Total	Percentage(%)");
		//printf("\n %d	%s		%s",s1.rno,s1.name,s1.address);
		printf("%-3d %-12s %-15s",s1.rno,s1.name,s1.address);
	    for(j=0;j<3;j++)
		{
			//printf("       %d",s1.sub[j].marks);
				printf("%-17d",s1.sub[j].marks);
		}
	//	printf("		%d	%.2f",s1.total,s1.per);
		printf("%-8d %6.2f\n",s1.total,s1.per);
		}
	}
	if(!found)
	printf("\n\nRecord not found!\n\n");
	printf("\n\n");
	fclose(fp);
	
}

void update()
{
	student s1;
	FILE *fp, *fp1;
	int j, rno, found=0;
	
	fp = fopen("mystudents.txt","r");
	fp1= fopen("temp.txt","w");
	printf("enter a roll number to update:");
	scanf("%d",&rno);
	while(fread(&s1,sizeof(student),1,fp))
	{
		if(s1.rno == rno)
		{
		s1.total = 0;
		s1.per = 0;
		found=1;
		fflush(stdin);
		printf("enter new name: ");
		scanf("%[^\n]s",s1.name);
		for(j=0;j<3;j++)
		{
			printf("enter new marks of subject %d :",j+1);
			scanf("%d",&s1.sub[j].marks);
			s1.total += s1.sub[j].marks;
		}
		s1.per= s1.total/ 3.0;
	}
	fwrite(&s1,sizeof(student),1,fp1);
   }
	fclose(fp);
	fclose(fp1);
	system("cls");
	if(found)
	{
		fp1= fopen("temp.txt","r");
		fp= fopen("mystudents.txt","w");
		
		while(fread(&s1,sizeof(student),1,fp1)){
			fwrite(&s1,sizeof(student),1,fp);
		}
		
		fclose(fp);
		fclose(fp1);
}
	
	else
	printf("\n Record not found\n");
}

void delete_rec()
{
	student s1;
	FILE *fp, *fp1;
	int j, rno, found=0;
	
	fp = fopen("mystudents.txt","r");
	fp1= fopen("temp.txt","w");
	printf("enter a roll number to delete:");
	scanf("%d",&rno);
	while(fread(&s1,sizeof(student),1,fp))
	{
		if(s1.rno == rno)
		{
		found=1;
	    }
	    else
			fwrite(&s1,sizeof(student),1,fp1);
    }
	fclose(fp);
	fclose(fp1);
	
	if(found)
	{
		fp1= fopen("temp.txt","r");
		fp= fopen("mystudents.txt","w");
		
		while(fread(&s1,sizeof(student),1,fp1)){
			fwrite(&s1,sizeof(student),1,fp);
		}
		
		fclose(fp);
		fclose(fp1);
}
	
	else{
		printf("\n Record not found\n");
	}
	
	printf("\n Record deleted successfully.");
}


	void welcome()
	{
		system("cls");
		int ch;
	printf("\n\t\t\t\t\t PASHCHIMANCHAL CAMPUS ADMINISRATION DASHBOARD\n");
	printf("\n\t\t\t\t\t\t STUDENT DATABASE SYSTEM \n ");
	printf("\n\t\t\t\t\t\t\t WELCOME  ");
	printf("\n________________________________________________________________________________________________________________________ \n");
	do{
		printf("\n\t1.CREATE A FILE");
		printf("\n\t2.DISPLAY");
		printf("\n\t3.APPEND");
		printf("\n\t4.NO OF RECORD");
		printf("\n\t5.SEARCH");
		printf("\n\t6.UPDATE");
		printf("\n\t7.DELETE RECORD");
	//	printf("\n\t8.ACCOUNT");
		printf("\n\t0.EXIT\n");
		
		printf("\n\tSELECT THE OPERATION TO PERFORM :-> \n");
		scanf("%d",&ch);
		
		switch(ch){
			case 1:
				create();
				break;
				
			case 2:
				display();
				break;	
				
			case 3:
				append();
				break;
			
			case 4:
				noofrec();
				break;
				
			case 5:
				search();
				break;
				
			case 6:
				update();
				break;	
				
			case 7:
			delete_rec();
			break;
			
			/*case 8:
			account();
			break;
				*/
     	}
	}while(ch!=0);

	}
//else
//	printf("\n\tInvalid Password!!\n\tAccess denied.\n");
	
	//}

 void login()
{
    char username[30],password[20];
    FILE *log;
    log=fopen("login.txt","r");
    struct login l;

    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:  ");
    
    scanf("%s",&username);
    printf("\nPassword: ");
    scanf("%s",&password);

    while(fread(&l,sizeof(l),1,log))
        {
        if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)

            {   
                printf("\nSuccessful Login\n");
                welcome();
            }
        else 
            {
                printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
            }
}

fclose(log);
}

registration()
{
    char firstname[15];
    FILE *log;
    log=fopen("login.txt","w");
    struct login l;

    printf("\nWelcome to your online database Management System. We need to enter some details for registration.\n\n");
    printf("\nEnter First Name:");
    scanf("%s",l.fname);
    printf("\nEnter Surname:");
    scanf("%s",l.lname);

    printf("Thank you.\nNow please choose a username and password as credentials for system login.\nEnsure the username is no more than 30 characters long.\nEnsure your password is at least 8 characters long and contains lowercase, uppercase, numerical and special character values.\n"); 

    printf("\nEnter Username: ");
    scanf("%s",l.username);
    printf("\nEnter Password: ");
    scanf("%s",l.password);


    fwrite(&l,sizeof(l),1,log);
    fclose(log);

    printf("\nConfirming details...\n...\nWelcome, %c!\n\n",firstname);
    printf("\nRegistration Successful!\n");
    
        getchar();
    system("CLS");
    login();
}





	
//main section

	int main()
	{
		
	
	 int option;

    printf("Press '1' to Register\nPress '2' to Login\n\n");
    scanf("%d",&option);

    if(option == 1)
        {
            system("CLS");
            registration();
        }

    else if(option == 2)
        {
            system("CLS");
            login();
        }	
	
}


			
			
