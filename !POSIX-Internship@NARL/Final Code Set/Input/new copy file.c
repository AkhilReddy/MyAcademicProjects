#include<stdio.h>
//#include<process.h>
#include <stdlib.h>
//# include <curses.h>
#include <unistd.h>
 
void main() {
   FILE *fp1, *fp2;
   char a;
   //clrscr();
   system("clear");
 
   fp1 = fopen("15AU2015SASHT1.r1", "r");
   if (fp1 == NULL) {
      puts("cannot open this file");
      exit(1);
   }
 
   fp2 = fopen("test1.txt", "w");
   if (fp2 == NULL) {
      puts("Not able to open this file");
      fclose(fp1);
      exit(1);
   }
 
   do {
      a = fgetc(fp1);
      fputc(a, fp2);
   } while (a != EOF);
 
   fcloseall();
   getchar();
}

FILE *f = fopen("out.txt", "w");
    //fprintf(f, "n = [0:%d];\n", N-1);
    fprintf(f, "Channel %d I data",flag);
    fprintf(f, "real = [ ");

    for (n=0 ; n<N ; ++n) 
     {
      fprintf(f, "%f ", x[n]);
     }
    
    fprintf(f, "];\n");
