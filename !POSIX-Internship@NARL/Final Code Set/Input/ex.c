
#include <stdio.h>

struct Student
{
int id;
int marks;
};

int main()
{
FILE *fp;

int ivalue,irel;
float fvalue,frel;
char cvalue,crel;
char strvalue[20],strrel[20];
struct Student svalue,srel;

//-------------------------------------------------------------------
fp=fopen("one.txt","w");

//Character Value Read & Write [fputc & fgetc]
//Write:
printf("\n Enter the Character Value:");
scanf("%c",&cvalue);

fputc(cvalue,fp);

fclose(fp);

//Read:
fp=fopen("one.txt","r");

crel=fgetc(fp);

printf("\n The Character value is :%c\n",crel);

fclose(fp);
//-------------------------------------------------------------------
//String Value Read & Write [fprintf & fscanf]
//Write:
fp=fopen("one.txt","w");

printf("\n Enter the String Value:");
scanf("%s",strvalue);

fprintf(fp,"%s",strvalue);

fclose(fp);

//Read:
fp=fopen("one.txt","r");

fscanf(fp,"%s",strrel);

printf("\n The String value is :%s\n",strrel);

fclose(fp);

//-------------------------------------------------------------------
//Structure Value Read & Write [fwrite & fread]
//Write:
fp=fopen("one.dat","wb");

printf("\nEnter the ID:");
scanf("%d",&svalue.id);

printf("\nEnter the Marks:");
scanf("%d",&svalue.marks);

fwrite(&svalue,sizeof(svalue),1,fp);

fclose(fp);

//Read:
fp=fopen("one.dat","rb");

fread(&srel,sizeof(srel),1,fp);

printf("\nThe ID is:%d\n",srel.id);
printf("\nThe Marks is:%d\n",srel.marks);

fclose(fp);
return 0;
}
