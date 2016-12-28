#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M 1500
int dist[M][M];
int operation[M][M];

/* 
* compute edit distance from a to b. 
* dist[i][j] denotes the edit distance you need in order to change string with length i to string with length j. 
* operation[i][j] denotes the operation while processing. 
* 0:right;1:replace;2:insert;3:delete
*/

int edit_distance(char *a,char *b)  
{  
    int len_a=strlen(a);  
    int len_b=strlen(b); 
     
    //printf("%d\n",len_a);
    //b is an empty string, in order to change a to b, b need to delete char.
    for (int i=0;i<=len_a;i++)  
    {  
        dist[i][0]=i*2;  
        operation[i][0]=3;  
    }  
  
    //a is an empty string, in order to change a to b, b need to add char.  
    for (int j=0;j<=len_b;j++)  
    {  
        dist[0][j]=j*3;  
        operation[0][j]=2;  
    }  
  
    operation[0][0]=0;  
    
    
    for (int i=1;i<=len_a;i++)  
    {  
        for (int j=1;j<=len_b;j++)  
        {  
            int cost = (a[i-1] == b[j-1] ? 0 : 1);     
  
            int deletion = dist[i-1][j] + 2;     
            int insertion = dist[i][j-1] + 3;     
            int substitution = dist[i-1][j-1] + cost*4;     
 
            if(deletion>insertion)  
            {  
                if(substitution>insertion)  
                {  
                    dist[i][j]=insertion;  
                    operation[i][j]=2;  
                }  
                else 
                {  
                    dist[i][j]=substitution;  
                    operation[i][j]=cost; 
                } 
            }  
            else  
            {  
                if(substitution>deletion)  
                {  
                    dist[i][j]=deletion;  
                    operation[i][j]=3; 
                }  
                else  
                {  
                    dist[i][j]=substitution;  
                    operation[i][j]=cost; 
                }  
            }  
        }  
    }  

//  record the each operation
    
    int substit=0,delet=0,insert=0,right=0;
    int f=len_a+len_b;
    int oper[f],edit[f];
	oper[0]=0;
	edit[0]=0;
    int k=0;
    for (int i=len_a,j=len_b;i>=0&&j>=0;)  
    {  
        switch(operation[i][j])  
        {  
        case 0:           
         //   printf("pos %d right\t",i);  
            i--;  
            j--;  
	    right++;
	    k++;
	    oper[k]=0;
	    edit[k]=0;
	 //   printf("operation=%d\n",operation[i+1][j+1]);
            continue;  
        case 1:       
          //  printf("pos %d substitute (%c-->%c)\t",i,a[i-1],b[j-1]);  
            i--;  
            j--;  
            substit++;
  	    k++; 
	    oper[k]=1;
	    edit[k]=4;
	//printf("operation=%d\n",operation[i+1][j+1]); 
            continue;  
        case 2:       
           // printf("pos %d insert (%c)\t",i,b[j-1]);  
            j--;  
            insert++;  
	    k++;
	    oper[k]=2;
	    edit[k]=3;
	  //  printf("operation=%d\n",operation[i][j+1]);
            continue;  
        case 3:          
          //  printf("pos %d delete (%c)\t",i,a[i-1]);  
            i--;  
            delet++;  
	    k++;
	    oper[k]=3;
	    edit[k]=2;
	 //   printf("operation=%d\n",operation[i+1][j]);
            continue;  
        }  
    }  
	
//  print the output file

    char *stack_1=a;
    char  stack_2[f]={};
    char *stack_b=b;
    int t=0,sum=0;

    FILE *fpt = fopen("output 1.txt", "w");

    printf("x: %s\n",a);
    printf("y: %s\n",b);
    printf("Edit_Distance:  %d\n",dist[len_a][len_b]);
    printf("operation | cost | toal |  z\n") ;
    printf("initial   |  0   |    0 |  *%s\n",a);

    fprintf(fpt, "x: %s\n", a);
    fprintf(fpt, "y: %s\n", b);
    fprintf(fpt, "Edit_Distance:  %d\n", dist[len_a][len_b]);
    fprintf(fpt, "operation | cost | toal |  z\n");
    fprintf(fpt, "initial   |  0   |    0 |  *%s\n", a);

    k--;
    int m=k;
    for(int i=0;i<m;i++)
    {
	if(oper[k]==0)
	{ 
	    sum += edit[k];
	    printf("right     |  %d   | %4d |  ",edit[k],sum);
		fprintf(fpt, "right     |  %d   | %4d |  ", edit[k], sum);
 	    stack_2[t]=stack_1[0];
	    strcat(stack_2,"*");
	    printf("%s",stack_2); 
		fprintf(fpt, "%s", stack_2);
	    stack_1++;
	    printf("%s\n",stack_1);
		fprintf(fpt, "%s\n", stack_1);
	    stack_b++;
	    t++;
	    k--;
	}
	else if(oper[k]==1)
	{
	    sum += edit[k];
	    printf("replace   |  %d   | %4d |  ",edit[k],sum);
		fprintf(fpt, "replace   |  %d   | %4d |  ", edit[k], sum);
	    stack_2[t]=stack_b[0];
	    strcat(stack_2,"*");
	    printf("%s",stack_2);
		fprintf(fpt, "%s", stack_2);
	    stack_1++;
	    printf("%s\n",stack_1);
		fprintf(fpt, "%s\n", stack_1);
	    stack_b++;
 	    t++;
  	    k--;
	}
	else if(oper[k]==2)
	{
	    sum +=edit[k];
	    printf("insert    |  %d   | %4d |  ",edit[k],sum);
		fprintf(fpt, "insert    |  %d   | %4d |  ", edit[k], sum);
	    stack_2[t]=stack_b[0];
	    strcat(stack_2,"*");
	    printf("%s",stack_2);
	    printf("%s\n",stack_1);
		fprintf(fpt, "%s", stack_2);
		fprintf(fpt, "%s\n", stack_1);
	    stack_b++;
	    t++;
	    k--;
	} 
	else
	{
	    sum += edit[k];
	    printf("delete    |  %d   | %4d |  ",edit[k],sum); 
	    printf("%s",stack_2);
		fprintf(fpt, "delete    |  %d   | %4d |  ", edit[k], sum);
		fprintf(fpt, "%s", stack_2);
	    stack_1++;
	    printf("%s\n",stack_1);
	    fprintf(fpt, "%s\n", stack_1);
	    k--;
	}	
    }
    fclose(fpt);
    fpt=NULL;
    //printf("right:%d,insert:%d,delete:%d,substitute:%d\n",right,insert,delet,substit);
    return dist[len_a][len_b];  
}
// INPUT FILES  

int main()
{	
    char str1[M];
    char str2[M];
    char mun1[100];
    char mun2[100];
    FILE*fp=NULL;
    fp=fopen("input1.txt","r");
    int len1;
    int len2;

    fgets(mun1,100,fp);

    fgets(str1,M,fp);
    len1 = strlen(str1);
    str1[len1-1] = '\0';  //delete '\0'

    fgets(mun2,100,fp);

    fgets(str2,M,fp);
    len2 = strlen(str2);
    str2[len2-1] = '\0';  //delete '\0'

    fclose(fp);
    fp=NULL;
		
    int edit=0;
    edit = edit_distance(str1, str2);
		
    return 0;
}

//For question 1
/*int main()
{ 
  char str1[]="electrical engineering,";
  char str2[]="computer science.";
		
    int edit=0;
    edit = edit_distance(str1, str2);
		
    return 0;
}
*/

//my little SAMPLE!
/*int main()
{
    char str1[]="C is a relatively \"low level\" language.";
    char str2[]="Java is an object-oriented language.";
		
    int edit=0;
    edit = edit_distance(str1, str2);
		
    return 0;
}
*/

