#include <stdio.h>
#include <stdlib.h>

int main(void)
{
       
FILE *out, *in;

int num;//宣告陣列的個數 
int s[100];//陣列有100個數字 
int i;
void BubbleSort(int[], int);//宣告泡沫排序函數 
float average(int[],int);//宣告平均數函數 
float variance(int [],int,float);//宣告變異數函數 
float average_result,variance_result;//宣告平均數,變異數 

out = fopen("output.dat", "w");//將結果寫入output檔 
in = fopen("input.dat", "r");//讀取input檔 
fscanf(in, "%d\n", &num);//讀取陣列的個數 

for (i =0; i <num; i++) // 讀取input.dat第二行的數字
{				
    fscanf(in,"%d",&s[i]);				 				
}




BubbleSort(s, num); //執行泡沫排序函數
fprintf(out,"數字由小到大是 " );
for(i=1; i<=num;i++){                                     //寫入output檔 
             fprintf(out,"%d ",s[i-1] );
			
    }

average_result=average(s,num);//算平均數

variance_result=variance(s,num,average_result);//算變異數 


fprintf(out,"\n average=%.2f\n ",average_result);//印變異數及平均數 
fprintf(out,"variance=%.2f \n",variance_result);


fclose(in);
fclose(out);
 
  
  system("PAUSE");	
  return 0;
}

//Bubblesort排序法 將數字由小到大排列 
void BubbleSort(int data[], int num){
    int i, j, temp;
    for (i = num; i > 1; i--){
       for (j = 1; j < i; j++){
          if (data[j-1] >data[j]){
             temp = data[j-1];
             data[j-1] = data[j];
             data[j] = temp;
          }
       }
    }
}

//平均數函數 
float average  (int s[ ],int num){                      
      float   answer=0;
      float   sum=0;
      int i;
      for(i=1;i<=num;i++){
               sum +=  s[i-1];
      }
      
      answer = (float)sum/num;
      return answer;
}

 
//變異數函數 
float variance(int s[ ],int num,float average){       
      
      float  answer=0;
      float  sum=0;
      int i;
      for(i=1; i<=num;i++){
               sum +=  (s[i-1]-average)*(s[i-1]-average);
      }
      
      
      
      answer = (float)sum / (float)num;
      return answer;
}
