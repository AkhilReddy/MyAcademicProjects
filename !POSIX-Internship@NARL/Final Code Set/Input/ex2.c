

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct emp
{
int id;
char name[20];
int salary;
};

void append();
void display();
void displayAll();
void rname();
void rremove();

void getFirstRecord();
void getLastRecord();
void getRandomRecord();

char fname[]={"one.dat"};

int main()
{
int ch;

while(1)
{
printf("========================================================\n\n");

printf("1. Append\n\n");

printf("2. Get First Record\n\n");
printf("3. Get Last Record\n\n");
printf("4. Get particular position value\n\n");

printf("5. Display\n\n");
printf("6. Display All\n\n");
printf("7. Rename\n\n");
printf("8. Delete File\n\n");
printf("0. Exit\n\n");

printf("========================================================\n\n");

printf("\nPlease enter your Choice:");
scanf("%d",&ch);

switch(ch)
{
case 1: append();
break;

case 2: getFirstRecord();
break;

case 3: getLastRecord();
break;

case 4: getRandomRecord();
break;

case 5: display();
break;

case 6: displayAll();
break;

case 7: rname();
break;

case 8: rremove();
break;

case 0: exit(0);
}
}

return 0;
}

//Add New Record to File
void append()
{
FILE *fp;
struct emp t1;

fp=fopen(fname,"ab");

printf("\nEnter ID:");
scanf("%d",&t1.id);
printf("\nEnter name:");
scanf("%s",t1.name);
printf("\nEnter salary:");
scanf("%d",&t1.salary);
fwrite(&t1,sizeof(t1),1,fp);

fclose(fp);
}

//Rename File
void rname()
{
char name[20];

printf("\nEnter the New File Name:");
fflush(stdin);
scanf("%[^\n]",name);

rename(fname,name);

strcpy(fname,name);
}

//Remove Database File
void rremove()
{
FILE *fp,*fp1;
struct emp t;

char name[20];
char val[20];

printf("\nDo you want to make copy of it (Y/N):");
scanf("%s",val);

if(strcmp(val,"Y")==0)
{

printf("\nEnter the New File Name:");
fflush(stdin);
scanf("%[^\n]",name);

fp=fopen(name,"wb");
fp1=fopen(fname,"rb");

while(1)
{
fread(&t,sizeof(t),1,fp1);

if(feof(fp1))
{
break;
}
fwrite(&t,sizeof(t),1,fp);
}

fclose(fp);
fclose(fp1);

remove(fname);

strcpy(fname,name);
}
else
{
remove(fname);
}
}

//Random Access File
void getFirstRecord()
{
FILE *fp;
struct emp t;

fp=fopen(fname,"rb");

rewind(fp);

fread(&t,sizeof(t),1,fp);

printf("\n========================================================\n\n");
printf("\t\t All Employee Details\n\n");
printf("========================================================\n\n");

printf("ID\tName\tSalary\n\n");

printf("%d\t",t.id);
printf("%s\t",t.name);
printf("%d\t\n\n",t.salary);

fclose(fp);
}

void getLastRecord()
{
FILE *fp;
struct emp t;

fp=fopen(fname,"rb");

fseek(fp,-sizeof(t),2);

fread(&t,sizeof(t),1,fp);

printf("\n========================================================\n\n");
printf("\t\t All Employee Details\n\n");
printf("========================================================\n\n");

printf("ID\tName\tSalary\n\n");

printf("%d\t",t.id);
printf("%s\t",t.name);
printf("%d\t\n\n",t.salary);

fclose(fp);
}

void getRandomRecord()
{
FILE *fp;
struct emp t;
int position,size,count,i;

fp=fopen(fname,"rb");

printf("Enter the position you want to display:");
scanf("%d",&position);

fseek(fp,0,2);
size=ftell(fp);
count=size/sizeof(t);

fseek(fp,0,0);
printf("\n Total object is:%d",count);

for(i=1;i<=count;i++)
{
fread(&t,sizeof(t),1,fp);

if(i==position)
{
printf("\n Current object is:%d",i);
break;
}
}
fclose(fp);

printf("\n========================================================\n\n");
printf("\t\t All Employee Details\n\n");
printf("========================================================\n\n");

printf("ID\tName\tSalary\n\n");

printf("%d\t",t.id);
printf("%s\t",t.name);
printf("%d\t\n\n",t.salary);

}

//Display & Display All Details
void display()
{
FILE *fp;
struct emp t;
int id,found=0;

fp=fopen(fname,"rb");

printf("\nEnter the Emp ID:");
scanf("%d",&id);

while(1)
{
fread(&t,sizeof(t),1,fp);

if(feof(fp))
{
break;
}
if(t.id==id)
{
found=1;
printf("\n========================================================\n\n");
printf("\t\t Employee Details of %d\n\n",t.id);
printf("========================================================\n\n");

printf("Name\tSalary\n\n");

printf("%s\t",t.name);
printf("%d\t\n\n",t.salary);

printf("========================================================\n\n");
}
}
if(found==0)
{
printf("\nSorry No Record Found");
}
fclose(fp);
}

void displayAll()
{
FILE *fp;
struct emp t;

fp=fopen(fname,"rb");

printf("\n========================================================\n\n");
printf("\t\t All Employee Details\n\n");
printf("========================================================\n\n");

printf("ID\tName\tSalary\n\n");

while(1)
{
fread(&t,sizeof(t),1,fp);

if(feof(fp))
{
break;
}
printf("%d\t",t.id);
printf("%s\t",t.name);
printf("%d\t\n\n",t.salary);

}
printf("========================================================\n\n");

fclose(fp);
}
