#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE 1
#define ARRIVAL 2
#define DEPT 3
#define LIMITS 100.0


//宣告資料結構，此資料結構包含時間及事件的類型(抵達或�肮O離開) 
typedef struct _Entity {
    int type;
    float time;
} Entity;


Entity event[100]; //此陣列有100個變數 
Entity queue[100]; //此陣列有100個變數 
int seed = 23456789;//種子的��始值是23456789 


int main(void){
    int num_events = 0, num_queue = 0; //宣告事件數及排隊人數，並設定��始值為0 
    float next_time;                   //還要過多久下個顧客才會到   
    float time = 0.0;                  //目前的時間 
    int Server_Is_Idle = TRUE;          
    float arrival_rate;                //抵達率(平均一小時抵達多少人) 
    float service_rate;                //服務率(平均一小時可以服務多少人) 
    int type;                          //事件的類型 
//計算系統內平均人數。
//計算系統內平均等候（排隊）人數。
    
    printf(" please input arrival rate per hour:  \n"); //'讓使用�芨擗J抵達率 
    scanf("%f",&arrival_rate);
    printf(" please input service rate per hour: \n");  //讓使用�芨擗J服務率 
    scanf("%f",&service_rate);

    
    
    void GenerateFirstEvent(float, float, int *);  //宣告產生第一個事件的函數 
    float GenerateTime(float);                     //宣告產生時間的函數 
    void InsertEvent(float, int *, float, int);    //宣告插入事件的函數  
    void PutInQueue(int *, float);                 //宣告排隊的函數 
    void GetFromQueue(float, int *, int *, float); //宣告有人從排隊中離開的函數  
    void DeleteFirstEvent(int *);                  //刪掉第一個事件函數 
    void PrintEvent(int), PrintQueue(int);         // 印出事件跟排隊事件 
    
    int Nt=0,Qt=0;                                  //系統內的總人數,排隊的總人數
    float Avg_Nt=0,Avg_Qt=0;                          //平均系統人數,平均排隊人數
    float total_Nt = 0.0,total_Qt=0;                //時間加權系統內的總人數,時間加權排隊的總人數
    
    
    
    
    GenerateFirstEvent(time, arrival_rate, &num_events);//產生第一個事件，事件數會改變
    printf("cehck GenerateFirstEvent\n");
    PrintEvent(num_events);                            //先印出來檢查程式有無打錯 
    PrintQueue(num_queue);                             //先印出來檢查程式有無打錯
   // printf("cehck GenerateFirstEvent over\n");
    
    
   
  while(time <= LIMITS){
        total_Nt = total_Nt+(event[0].time - time)*Nt;//時間加權系統內的總人數
		total_Qt = total_Qt+(event[0].time - time)*Qt;//時間加權排隊的總人數       
        time = event[0].time; // 取出第一個事件：目前的時間等於第一個事件的時間 
        type = event[0].type; // 取出第一個事件：此事件的類型 
        DeleteFirstEvent(&num_events);//因為拿出來了第一個事件，要刪掉 
        PrintEvent(num_events); //看看目前事件數是否是0(因為刪掉了) 
        
        
        if(type == ARRIVAL){
            Nt++;                                    //有人進來系統了,系統人數+1  
            next_time = GenerateTime(arrival_rate);  //第一個事件抵達時的時間 
            InsertEvent(time, &num_events, next_time, ARRIVAL);  //插入事件 
            PrintEvent(num_events);
            
            //如果服務人員現在有空 
            if(Server_Is_Idle == TRUE){
                next_time = GenerateTime(service_rate);
                InsertEvent(time,&num_events, next_time, DEPT);
                Server_Is_Idle = FALSE;//因為服務員正在服務客人，沒空 
                PrintEvent(num_events);
            }
            //如果服務人員現在「沒」有空  
            else{
                 Qt++;                             //如果系統正在忙碌,排隊人數+1 
                
                PrintQueue(num_queue);
                PutInQueue(&num_queue, time);//如果服務員沒空，就去排隊，&num_queue→改變排隊人數 
                PrintQueue(num_queue);
            }
        }
        //如果是離開事件 
        else if(type ==DEPT){
             Nt--;                         //系統人數-1                                    
            //如果排隊人數不等於0，那有人就要從排隊中離開，去給服務員服務(因為有人被服務員服務完畢後，離開) 
            if(num_queue != 0){ 
                Qt--;
                PrintEvent(num_events);
                PrintQueue(num_queue);
                GetFromQueue(time, &num_events, &num_queue, service_rate);//有人要從排隊中離開，去給服務員服務(因為有人被服務員服務完畢後，離開)
                PrintEvent(num_events);  
                PrintQueue(num_queue); 
            }else
              //如果沒有人在排隊，那麼現在服務員就是空閒的  
              {
                Server_Is_Idle = TRUE;
              }
        }
    }   
    
  
    Avg_Nt=(total_Nt/event[0].time);
    Avg_Qt=(total_Qt/event[0].time);
    printf("The average number of customer in system is: %f\n",Avg_Nt);
    printf("The average queneing number of customer in system is: %f\n",Avg_Qt);
    system("pause");
}
 

//產生第一個事件 GenerateFirstEvent(time, arrival_rate, &num_events)
void GenerateFirstEvent(float time, float rate, int *num){
    float GenerateTime(float);
    void PrintEvent(int);
    
    event[0].time = time + GenerateTime(rate); // 第一個事件的抵達時間會等於目前時間加上經過多久後會抵達的時間(用抵達率算) 
    event[0].type = ARRIVAL;                   //第一個事件的類型是抵達事件  
    
    (*num)++; //原本事件數是0，再產生一個新事件後，目前事件數為1 
}


void PrintEvent(int num){
    int i;
    
    printf("*** total event number is %d ***\n",num);
    
    for(i = 0; i < num; i++){
        printf("type is %d, time is %f\n", event[i].type, event[i].time);
    }
}



void PrintQueue(int num){
    int i;
    
    printf("*** total queue number is %d ***\n", num);
    
    for(i = 0; i < num; i++){
        printf("type is %d, time is %f\n", queue[i].type, queue[i].time);
    }
}





//刪掉第一個事件 
void DeleteFirstEvent(int *num){
    int i;
    
    for(i = 0; i < *num; i++){
        event[i].type = event[i+1].type;
        event[i].time = event[i+1].time;
    }
    (*num)--;//因為刪掉事件，所以事件數減1 
}





float GenerateTime(float rate){
    float rn, time;
    float GetRandomNumber(void);
    float GetExponential(float, float);
    
    rn = GetRandomNumber();
    time = GetExponential(rn, rate);
    return(time);
}





// InsertEvent(time, &num_events, next_time, ARRIVAL) 
void InsertEvent(float time, int *num, float next_time, int type){
    int target;
    float value = time + next_time;//第二個事件抵達時的時間 
                
    if(*num == 0){
        event[0].time = value;
        event[0].type = type;
        *num = 1;
        return;
    }
    
   // PrintEvent(*num);
    
    target = *num - 1;
    
    //一直做到target小於0，也就是事件數小於1， 
    while(target >= 0 && event[target].time > value){
        event[target+1].time = event[target].time;
        event[target+1].type = event[target].type;
        target--;
    }
    event[target+1].time = value;
    event[target+1].type = type;
    
    (*num)++;                //插入一個事件後，目前的事件數要加一 
}


//排隊 PutInQueue(&num_queue, time)
void PutInQueue(int *num_queue, float time){
    queue[*num_queue].type = ARRIVAL;
    queue[*num_queue].time = time;
    (*num_queue)++;          //排隊人數增加一人 
}


// GetFromQueue(time, &num_events, &num_queue, service_rate) 
void GetFromQueue(float time, int *num_events, int *num_queue, float service_rate){
    float next;
    float GenerateTime(float);
    void InsertEvent(float, int *, float, int);
    int i;
    
    next = GenerateTime(service_rate); // 
    InsertEvent(time, num_events, next, DEPT); //(float time, int *num, float next_time, int type) 
    
    for(i = 0; i < *num_queue-1; i++){
        queue[i].type = queue[i+1].type; //把後面的移到前面 
        queue[i].time = queue[i+1].time;
    }
    (*num_queue)--; //排隊人數少掉一個人 
}


float GetRandomNumber(void){
    float random;
    
    seed = fmod((double)16807*seed, (double)2147483647);
    random = (float)seed/2147483647;
    return(random);
}


float GetExponential(float rn, float rate){    
    return(log((1.0 - rn))/(-1.0 * rate));
}
