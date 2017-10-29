
#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//sorts through the data and makes tokens

char** tokenizer(char* tp, size_t numc){
    
    
    int i = 0;
    int j = 0;
    int k = 0;
    
    char** str =(char**)malloc(sizeof(char*)* (numc + 1)); 
    char* tmp =(char*)malloc(500);
	size_t quote=1;
	

    while(i<strlen(tp)){
				
		if(tp[i]=='"' && quote==1){
			quote=0;
		
		}
				
		else if(tp[i]=='"' && quote==0){
			
			str[k] = (char*)malloc((100)* sizeof(char));
			
			strcpy(str[k],tmp);
			
			memset(&tmp[0],0,strlen(tmp));
			quote=1;
			j=0;
			k++;
			i++;
		}

		
        else if((tp[i]==',' || i ==strlen(tp)-1) && quote==1){
            
            if(!tmp){
                tmp[0] = '\0';
			}
			if(i == strlen(tp)-1 && tp[i]!='\n'){
				tmp[j] = tp[i];
				j++;
			}
           
			str[k] = (char*)malloc((j+1) * sizeof(char));

			strcpy(str[k],tmp);
			memset(&tmp[0],0,strlen(tmp));			
            j = 0;
			k++;
			

        }else{

			if(j==0){
				if(tp[i]==' '){
					i++;
					continue;
				}				
			}
            tmp[j] = tp[i];
			j++;
		}
        i++;
	} 
	i = 0;
	

    return str;
}
//creates and stores
int tokens(FILE *fp,row* data,int numc){
	row tmpRow;
	tmpRow.rText = (char*) malloc (sizeof(char) * 1500);
	size_t curr_col =0;
	size_t atRow=0; 
	int i =0;
	while(fgets(tmpRow.rText, 1500-1, fp) != NULL){
		tmpRow.rowL =strlen(tmpRow.rText);
		tmpRow.rToken =(char**) malloc(sizeof(char *)* (numc+1));
		tmpRow.rToken =tokenizer(tmpRow.rText,numc);
		




/*
	while(i < numc){

char *txt = tmpRow.rToken;
int l =	strlen(tmpRow.rToken);
char *end;
while(isspace(*txt)){
txt++;
}
if(*txt==0){
tmpRow.rToken[i] =txt;
}else{
end = txt +l;
while(end>txt && isspace(*end)){
end--;
}
	*(end+1)=0;
tmpRow.rToken =txt;
}


	



*/













i = 0;
			
		data[atRow++] = tmpRow;		
	}
	return atRow;
}

int main (int argc, char* argv[]){

	FILE *fp;
	fp = stdin;
	int j = 0;
	  //first row:
	row header;
	char *token;
	size_t numc = 1;

//get stdin input and make tokens
	header.rText = (char*) malloc (sizeof(char) * 1500);		
	fgets(header.rText, 1500-1, fp);
	header.rowL = strlen(header.rText);
	header.rToken = (char**) malloc(sizeof(char *) * header.rowL);
	token = strtok(header.rText, ",");
	header.rToken[0] = token;


	while(token = strtok(NULL, ",")){
			
header.rToken[numc++] = token;	
	}
	header.numc = numc;

	
	int length = strlen(header.rToken[numc - 1]);
	if(header.rToken[numc - 1][length - 1] == '\n'){
		header.rToken[numc - 1][length - 2] = '\0';
	}

	int i = 0;
//trim white space
	while(i < numc){

char *txt = header.rToken[i];
int l =	strlen(header.rToken[i])-1;
char *end;
while(isspace(*txt)){
txt++;
}
if(*txt==0){
header.rToken[i] =txt;
}else{
end = txt +l;
while(end>txt && isspace(*end)){
end--;
}
	*(end+1)=0;
header.rToken[i] =txt;
}



	//printf("====%s====/n", header.rToken[i]);
		i++;
	}

	row *data;
	int rows; 
	data = (row*) malloc (sizeof(row) * 10000);
	rows = tokens(fp, data, numc);
	///printf("%i\n",rows);
	char* input;
	if(argv[2]){
		input = argv[2];	
//printf("\n%s\n",input);
	}else{
		
		exit(1);
	}
	
	//find the input column 
	int inputf = 0;

	
	while(inputf < header.numc){
		if(strcmp(header.rToken[inputf], input) == 0){
			break;
		}
		inputf++;
	}

	//printf("%d\n", inputf);
	mergeSort(data, inputf, rows);
// compare middle rows
int lx = rows/2;
	

	

		row* L = (row*)malloc(100 * sizeof(row));   
    row* R = (row*)malloc((100) * sizeof(row));
	        L[1] = data[(lx-1)];
		        R[1] = data[lx];


int loc = 0;
     i = 0;
     j = 0; 
int y =2;


char* strl =L[1].rToken[inputf];
char* strr=R[1].rToken[inputf];
if(isNum(L[1].rToken[inputf])==1 && isNum(R[1].rToken[inputf])==1){//5
float sl = atof(strl);
float sr=atof(strr);
	if(sl<=sr){
y=0;
}else{
y=1;
}

} else{//5

if(strcmp(strl, strr)<=0){
//
("\n%s=0=%s\n",strl,strr);

y=0;

}else{
y=1;
//printf("\n%s=1=%s\n",strl,strr);
}

} 

if(y==1){
  data[(lx-1)]=R[1];
		         data[lx]=L[1];


}

 L[2] = data[lx];
		        R[2] = data[(lx+1)];

 loc = 0;
     i = 0;
     j = 0; 
 y =2;



char* strl2 =L[2].rToken[inputf];
char* strr2=R[2].rToken[inputf];
if(isNum(L[2].rToken[inputf])==1 && isNum(R[2].rToken[inputf])==1){//5
float sl2 = atof(strl2);
float sr2=atof(strr2);
	if(sl2<=sr2){
y=0;
}else{
y=1;
}

} else{//5

if(strcmp(strl2, strr2)<=0){
//printf("\n%s=0=%s\n",strl,strr);

y=0;

}else{
y=1;
//printf("\n%s=1=%s\n",strl,strr);
}

} 

if(y==1){

  data[lx]=R[2];
		        data[(lx+1)]=L[2];
  


}






 


		//printf("\nqq%s\n",data[0].rText);
		
	
	i = 0;
	//print 
	while(i < numc){
		printf("%s",header.rToken[i]);
		if(i != numc - 1){
			printf(",");
		}else{
			printf("\n");
		}
		i++;
	}








	//print all other rows
	i = 0;
	 j = 0;
	while(i < rows){
		while(j < numc){



	/*	char *p=data[i].rToken[j];
//printf("==%s==\n",p);
//char *p = "wwe ";
 
int l2 = strlen(p);

char w[strlen(p)-1];
int mv =1;
strcpy(w,p);

 
	char *a = p+l2-1;
	
	//e[strlen(e)-1]="r";

//printf("\n==%s==\n",a);
if(strcmp(a," ")==0){
printf("\nquack\n");
//mv++; 
//a = e+l2-(int)mv;
w[strlen(p)-1]=0;
//printf("\n%s===\n",w);
}
    

//data[i].rToken[j]=p;*/
				
			printf("%s",data[i].rToken[j]);
			//printf("\n%i %i",i,j);
			if(j != numc - 1){
				printf(",");
			}else{
				printf("\n");
			}
			j++;
		}
		i++;
		j = 0;
	}
	
	return 0;
}
