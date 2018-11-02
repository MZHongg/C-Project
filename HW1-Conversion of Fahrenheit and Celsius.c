#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
 float temperature;
 float R_CtoF,R_FtoC;//temperature一開始輸入的溫度, 
 float F_CtoF(float );//轉換成華氏的函數
 float F_FtoC(float); //轉換成攝氏的函數 
 printf("please input the temperature\n");
 scanf("%f",&temperature);
 	
 
 if(temperature>=20&&temperature<=45)// 若是讀取的數值介於20（含）到45（含）之間，就是攝氏，要將其轉成華氏度 ，用round四捨五入到整數 
 {
     printf("the temperature you input is in degree Celsius.\n");
     R_CtoF= F_CtoF(temperature); 
     printf("%f 攝氏度等於 %f 華氏度 .\n",temperature,round(R_CtoF));                             
 }
 else if(temperature>=68&&temperature<=113)//若是若是讀取的數值介於68（含）到113（含）之間，就是華氏，要將其轉成攝氏度，用round四捨五入到整數  
 {
      printf("the temperature you input is in degree Fahrenheit.\n");
     R_FtoC= F_FtoC(temperature);
     printf("%f 華氏度等於 %f 攝氏度 .\n",temperature,round(R_FtoC));    
}
//輸入的溫度若不在20至45之間，也不在68至113之間，則是不合理的輸入其餘則為不合理輸入 
 else{
      printf("illegal input\n");    
}
 

 system("pause");
 return 0;
}

float F_CtoF(float temperature )//轉換成華氏的函數 
{
      float R_CtoF;
      R_CtoF= temperature*9/5+32;
      return R_CtoF;   
} 

float F_FtoC(float temperature)//轉換成攝氏的函數 
{
      float R_FtoC;
      R_FtoC=(temperature-32)*5/9;
      return R_FtoC;
}








