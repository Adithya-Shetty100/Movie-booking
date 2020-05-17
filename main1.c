#include<stdio.h>
#include<stdlib.h>
#include"moviedetails1.c"
#include"declaration1.c" 
#include<string.h>


struct moviedetails person[300];
int count=0,id2,id4,id5;

void counter()
{	FILE *fp2;
	char ch;
	fp2=fopen("file1.txt","r");
	if(fp2==NULL)
	{printf("Cant open file 1");exit(1);}
	int ctr=0;
	while((ch=fgetc(fp2))!= EOF)
	{
		if(ch=='\n')
			ctr++;}
	fclose(fp2);
	id2=1000+ctr;
}

void counter1()
{	FILE *fp2;
	char ch;
	fp2=fopen("file2.txt","r");
	if(fp2==NULL)
	{printf("Cant open file 2");exit(2);}
	int ctr=0;
	while((ch=fgetc(fp2))!= EOF)
	{
		if(ch=='\n')
			ctr++;}
	fclose(fp2);
	id4=1000+ctr;
}

void counter2()
{	FILE *fp2;
	char ch;
	fp2=fopen("file3.txt","r");
	if(fp2==NULL)
	{printf("Cant open file 3");exit(3);}
	int ctr=0;
	while((ch=fgetc(fp2))!= EOF)
	{
		if(ch=='\n')
			ctr++;}
	fclose(fp2);
	id5=1000+ctr;
}


int main()
{
	int **seat,choice,price=200,slection,i;
	seat=(int **)calloc(3,sizeof(int *));//seat array stores address of 100 element array  seat=(int **)calloc(101,sizeof(int *));
	for (i=0;i<3;i++)
		*(seat+i)=(int *)calloc(101,sizeof(int ));
	int x;
	counter();
	counter1();
	counter2();
	while(x!=5)
	{
		choice=choice1();
		switch(choice)
		{
			case 1:
				price=changeprize(price);
				break;
			case 2:
				details();
				break;	
			case 3:	
				slection=movie();
				reservation(seat[slection-1],price,slection);	//seat[0] is for avengers, seat[1] for captain marvel
				count++;
				break;
			case 4:
				slection=cmovie();	
				cancel(seat[slection-1],slection);	
				break;
			case 5:
				x=5;
				break;
			default: 
				printf("Choice not available\n");
				break;	
		}
	}
}


int changeprize(int prize)
{
	char pass[10],pak[10]="pass";
	printf("Enter the password to change price of ticket: ");
	scanf("%s",pass);
	if (strcmp(pass,pak)==0)
	{
		printf("Please enter new price: ");
		scanf("%d",&prize);
		printf("\nTHE PRICE HAS BEEN CHANGED SUCCESSFULLY!!\n");
		return prize;
	}
	else 
	{	printf("The entered password is wrong! \n");
		prize=changeprize(prize); //recursive function
		return prize;
	}
	
}


void reservation(int *array,int price,int slection)
{          
		int i,j;
		printf("\n%40s\n\n\n","SCREEN");
		for (i=1;i<=100;i++)
		{
			if (array[i]==0)
				printf("%d\t",i);
			else 
				printf("%d\t",i);	
			if(i%10==0)
				printf("\n\n");
		}
		printf("Please enter your name: ");
		scanf(" %s",person[count].name);
		printf("Please enter your phone number: ");
		scanf("%s",person[count].phone);
		printf("Which seat number you want? ");
		scanf("%d",&j);
		if (j>100||j<1)
			{
				printf("Seat number is unavailable in this theater\n");
				printf("Please re-enter seat number between 1 & 100: ");
				scanf("%d",&j);}
		
		FILE *fp;
		if (slection==1)
			fp=fopen("file1.txt","r");
		else if (slection==2)
			fp=fopen("file2.txt","r"); 
		else 
			fp=fopen("file3.txt","r");
		if(fp==NULL)
		{printf("Cant open file");exit(4);}

		char buff[20];int s;
		while((fscanf(fp,"%*s\t%s\t%*s\t%*s\t%*s\n",buff))!=EOF)
		{
			s=atoi(buff);
			if (s!=0)
				array[s]=1;}
		fclose(fp);

		while(1)
		{
			if (array[j]==0)
			{
				array[j]=1;
				break;}
			else
			{
				printf("Sorry, this ticket is already booked! Please choose another seat.\n");
				scanf("%d",&j);}							
		}
		person[count].seat=j;
		if (slection==1)
			ticket1(j,person[count].name,id2,price);
		else if (slection==2) 	
			ticket2(j,person[count].name,id4,price);
		else 
			ticket3(j,person[count].name,id5,price);					
}


int choice1(void)
{
	int choice;
	printf("\n");
	printf("                 Simple Movie Ticket Booking System\n");
	printf(" ==================================================================\n");
	printf("||             1- To edit price of ticket (only admin):           ||\n");
	printf("||             2- To view transactions (only admin):              ||\n");
	printf("||             3- To purchase ticket:                             ||\n");
	printf("||             4- To cancel the seat:                             ||\n");
	printf("||             5- Exit system:                                    ||\n");
	printf("||================================================================||\n");
	printf("\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	printf("\n");
	return choice;
}


void cancel(int *array,int index)
{
	FILE *fp,*ft;
	if(index==1)
		fp=fopen("file1.txt","r");
	else if(index==2)
		fp=fopen("file2.txt","r");
	else
		fp=fopen("file3.txt","r");
	if(fp==NULL)
	{printf("Cant open file");exit(5);}
	
	int id3;
	ft=fopen("temp.txt","w");
	printf("Please enter ID number of ticket: ");
	scanf("%d",&id3);
	char buff[8],ph[15];
	int n=1000,id,seat,prices;
	while((fscanf(fp,"%d\t%d\t%s\t%s\t%d",&id,&seat,buff,ph,&prices))!=EOF)
	{	
		if(n==id3)
		{
			array[seat]=0;
			fprintf(ft,"%d\t%d\t%s\t%s\t%d\n",id,0,"C","CANCELLED",0);
			printf("\n%s, your seat has been cancelled...\n",buff);
		}
		else
	 		fprintf(ft,"%d\t%d\t%s\t%s\t%d\n",id,seat,buff,ph,prices);
		n++;
	}

	fclose(fp);
	fclose(ft);
	
	if(index==1)
	{	remove("file1.txt");
		rename("temp.txt","file1.txt" );}
	else if(index==2)
	{	remove("file2.txt");
		rename("temp.txt","file2.txt" );}
	else
	{	remove("file3.txt");
		rename("temp.txt","file3.txt" );}
	if (id3>=n)	
		printf("Ticket ID number is incorrect.Your ticket hasn't been cancelled\n PLEASE TRY AGAIN!!\n");
	
}


void ticket1(int choice,char name[10],int id2,int price)
{
	printf("\n\n");
        printf("\t--------------------------------THEATER BOOKING TICKET----------------------\n");
        printf("\t=====================================================================================\n");
        printf("\t Booking ID : %d \t\t\tShow Name : Avengers: EndGame\n",id2);
        printf("\t Customer  : %s\n",name);
        printf("\t\t\t                              Date      :  8-04-2019\n");
        printf("\t                                              Time      :  4:00pm\n");
        printf("\t                                              Hall      : 02\n");
        printf("\t                                              Seat No.  : %d  \n",choice);
        printf("\t                                              Price .   : Rs.%d  \n\n",price);	
        printf("\t=====================================================================================\n");
	person[count].cost=price;
	person[count].id=id2;
	id2++;

	FILE *fp1;
	fp1=fopen("file1.txt","a");
	if(fp1==NULL)
	{
		printf("Cant append file 1");
		exit(6);}

	fprintf(fp1,"%d\t%d\t%s\t%s\t%d\n",person[count].id,person[count].seat,person[count].name,person[count].phone,person[count].cost);
	fclose(fp1);
	return;
}


void details(void)
{
	int i;
	char pass[10],pak[10]="pass";
	printf("Enter the password to see details: ");
	scanf("%s",pass);
	if (strcmp(pass,pak)==0)
	{
		//MOVIE 1
		printf("\nAvengers: EndGame\n");
		printf("-------------------------------------------------\n");		
		printf("%s\t%s\t%s\t%s\t\t%s\n","Id","Seat","Name","Ph","Price");
		printf("-------------------------------------------------\n");
		FILE *fp;char ch;
		fp=fopen("file1.txt","r");
		while(1)
		{
			ch=fgetc(fp);
			if (ch==EOF)
				break;
			printf("%c",ch);}
		fclose(fp);
		fp=fopen("file1.txt","r");
		int total1=0,grand=0,bill;char name[20];
		while((fscanf(fp,"%*s\t%*s\t%*s\t%*s\t%s",name))!=EOF)
		{
			bill=atoi(name);
			total1+=bill;}
		printf("\nTotal= Rs.%d\n\n",total1);
		fclose(fp);

		//MOVIE 2
		printf("Captain Marvel\n");
		printf("-------------------------------------------------------------\n");		
		printf("%s\t%s\t%s\t%s\t\t%s\n","Id","Seat","Name","Ph","Price");
		printf("-------------------------------------------------------------\n");

		fp=fopen("file2.txt","r");
		while(1)
		{
			ch=fgetc(fp);
			if (ch==EOF)
				break;
			printf("%c",ch);}
		fclose(fp);
		fp=fopen("file2.txt","r");
		int total2=0;
		while((fscanf(fp,"%*s\t%*s\t%*s\t%*s\t%s",name))!=EOF)
		{
			bill=atoi(name);
			total2+=bill;}
		printf("\nTotal= Rs.%d\n\n",total2);
		fclose(fp);

		//MOVIE 3
		printf("Spider-Man: Far From Home\n");
		printf("-------------------------------------------------------------\n");		
		printf("%s\t%s\t%s\t%s\t\t%s\n","Id","Seat","Name","Ph","Price");
		printf("-------------------------------------------------------------\n");

		fp=fopen("file3.txt","r");
		while(1)
		{
			ch=fgetc(fp);
			if (ch==EOF)
				break;
			printf("%c",ch);}
		fclose(fp);
		fp=fopen("file3.txt","r");
		int total3=0;
		while((fscanf(fp,"%*s\t%*s\t%*s\t%*s\t%s",name))!=EOF)
		{
			bill=atoi(name);
			total3+=bill;}
		printf("\nTotal= Rs.%d\n\n",total3);
		fclose(fp);
		
		grand=total1+total2+total3;
		printf("------------------------------------------------------------\n");
		printf("GRAND TOTAL= Rs.%d\n",grand);

	}
	else                                                 
	{	printf("Entered password is wrong \n");
		details();}
	
} 

            
int movie(void)
{
	int i;
	printf("\t\t\tWhich movie do you want to see tomorrow?\n");
	printf("\t\t\t-------------------------------------------------------\n\n");
	printf("\t\t\tpress 1 for Avengers: EndGame at 4pm\n\n");
	printf("\t\t\tpress 2 for Captain Marvel at 8pm\n\n");
	printf("\t\t\tpress 3 for Spider-Man: Far From Home at 10pm\n");
	printf("\nPlease enter your choice:");
	scanf("%d",&i);
	return i;
}

void ticket2(int choice,char name[10],int id2,int price)
{
	printf("\n\n");
        printf("\t------------------------------THEATER BOOKING TICKET-------------------\n");
        printf("\t=====================================================================================\n");
        printf("\t Booking ID : %d \t\t\tShow Name : Captain Marvel\n",id4);
        printf("\t Customer  : %s\n",name);
        printf("\t\t\t                              Date      :  8-04-2019\n");
        printf("\t                                              Time      : 8:00pm\n");
        printf("\t                                              Hall      : 01\n");
        printf("\t                                              Seat No.  : %d  \n",choice);
        printf("\t                                              Price .   : Rs.%d  \n\n",price);
        printf("\t======================================================================================\n");
	person[count].cost=price;
	person[count].id=id4;
	id4++;

	FILE *fp1;
	fp1=fopen("file2.txt","a");
	if(fp1==NULL)
	{
		printf("Cant append file 2");exit(8);}
	fprintf(fp1,"%d\t%d\t%s\t%s\t%d\n",person[count].id,person[count].seat,person[count].name,person[count].phone,person[count].cost);
	fclose(fp1);
        return;
}

int cmovie(void)
{
	int i;
	printf("\t\t\tWhich movie ticket you want to cancel??\n");
	printf("\t\t\t-------------------------------------\n");
	printf("\t\t\tpress 1 for Avengers: EndGame\n\n");
	printf("\t\t\tpress 2 for Captain Marvel\n\n");
	printf("\t\t\tpress 3 for Spider-Man: Far From Home\n");
	printf("\nPlease enter your choice:");
	scanf("%d",&i);
	return i;		
}

void ticket3(int choice,char name[10],int id2,int price)
{
	printf("\n\n");
        printf("\t------------------------------THEATER BOOKING TICKET----------------------------\n");
        printf("\t=========================================================================================\n");
        printf("\t Booking ID : %d \t\t\tShow Name : Spider-Man: Far From Home \n",id5);
        printf("\t Customer  : %s\n",name);
        printf("\t\t\t                              Date      : 8-04-2019\n");
        printf("\t                                              Time      : 10:00pm\n");
        printf("\t                                              Hall      : 02\n");
        printf("\t                                              Seat No.  : %d  \n",choice);
        printf("\t                                              Price     : Rs.%d  \n\n",price);
        printf("\t==========================================================================================\n");
	person[count].cost=price;
	person[count].id=id5;
	id5++;

	FILE *fp1;
	fp1=fopen("file3.txt","a");
	if(fp1==NULL)
	{
		printf("Cant append file 3");exit(9);}
	fprintf(fp1,"%d\t%d\t%s\t%s\t%d\n",person[count].id,person[count].seat,person[count].name,person[count].phone,person[count].cost);
	fclose(fp1);
        return;
}
