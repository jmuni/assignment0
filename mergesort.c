#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//checks if string is number or not
int isNum(char* string){
    int i = 0;
    
    int dec = 0; 
    
    if(string == NULL || strcmp(string, "") == 0){
        return 0;
    }
  
    
    while(i < strlen(string)){        
        if( !isdigit(string[i])){
            if(dec){ 
                if(string[i] == '.'){
dec++;

}else{
return 0;
}
             
            }else{ // ie
return 0;
}
          //  return 0;
        }   //if digit
        i++;
    }//big while
    return 1; //is int

 
}    


//executes mergesort

void exec(row* L, row* R, int left, int right, int col, row* dat){  




  int i = 0;
  int j = 0;
  int loc = 0;
  int y =2;

   
    while(i < left && j < right){
char* strl =L[i].rToken[col];
char* strr=R[i].rToken[col];
if(isNum(L[i].rToken[col])==1 && isNum(R[i].rToken[col])==1){//5
float sl = atof(strl);
float sr=atof(strr);
	if(sl<sr){
//printf("\n%f=0=%f\n",sl,sr);
y=0;
}else{
//printf("\n%f=1=%f\n",sl,sr);
y=1;
}

} else{//5

// string comparison
if(strcmp(strl, strr)<=0){ 
//printf("\n%s=0=%s\n",strl,strr);

y=0;

}else{
y=1;
//printf("\n%s=1=%s\n",strl,strr);
}

}   //5   


if(!L[i].rToken[col]){
y=0;
}else{
if(!R[i].rToken[col]){
y=1;
}
}  



 if(y==0){
            dat[loc] = L[i];
            loc++;
            i++;
        }else{
            dat[loc] = R[j];
            loc++;
            j++;
        }
    }

//merge
    while(i < left){
        dat[loc] = L[i];
        i++;
        loc++;
    }
    while(j < right){
        dat[loc] = R[j];
        j++;
        loc++;
    }
    i = 0;
    while(i < loc){
        i++;
    }

}

void mergeSort(row* data, int col, int n){
//printf("hello\n");
    	int i;
	int mid;

    if(n<2){     
        return;
    }
    
    mid = n/2;


    row* L = (row*)malloc(1500 * sizeof(row));   
    row* R = (row*)malloc(1500 * sizeof(row));


    for(i =0;i<mid;i++){
        L[i] = data[i];
    } 
    for(i=mid;i<n;i++){
        R[i-mid]=data[i];
    }


    mergeSort(L,col, mid);
    mergeSort(R,col, n-mid);
   exec(L,R,mid,n-mid,col,data);


    free(L);
    free(R);

}



