#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE 1
#define ARRIVAL 2
#define DEPT 3
#define LIMITS 100.0


//«Å§i¸ê®Æµ²ºc¡A¦¹¸ê®Æµ²ºc¥]§t®É¶¡¤Î¨Æ¥óªºÃş«¬(©è¹F©ÎÍ¬OÂ÷¶}) 
typedef struct _Entity {
    int type;
    float time;
} Entity;


Entity event[100]; //¦¹°}¦C¦³100­ÓÅÜ¼Æ 
Entity queue[100]; //¦¹°}¦C¦³100­ÓÅÜ¼Æ 
int seed = 23456789;//ºØ¤lªºş©l­È¬O23456789 


int main(void){
    int num_events = 0, num_queue = 0; //«Å§i¨Æ¥ó¼Æ¤Î±Æ¶¤¤H¼Æ¡A¨Ã³]©wş©l­È¬°0 
    float next_time;                   //ÁÙ­n¹L¦h¤[¤U­ÓÅU«È¤~·|¨ì   
    float time = 0.0;                  //¥Ø«eªº®É¶¡ 
    int Server_Is_Idle = TRUE;          
    float arrival_rate;                //©è¹F²v(¥­§¡¤@¤p®É©è¹F¦h¤Ö¤H) 
    float service_rate;                //ªA°È²v(¥­§¡¤@¤p®É¥i¥HªA°È¦h¤Ö¤H) 
    int type;                          //¨Æ¥óªºÃş«¬ 
//­pºâ¨t²Î¤º¥­§¡¤H¼Æ¡C
//­pºâ¨t²Î¤º¥­§¡µ¥­Ô¡]±Æ¶¤¡^¤H¼Æ¡C
    
    printf(" please input arrival rate per hour:  \n"); //'Åı¨Ï¥ÎÍ¿é¤J©è¹F²v 
    scanf("%f",&arrival_rate);
    printf(" please input service rate per hour: \n");  //Åı¨Ï¥ÎÍ¿é¤JªA°È²v 
    scanf("%f",&service_rate);

    
    
    void GenerateFirstEvent(float, float, int *);  //«Å§i²£¥Í²Ä¤@­Ó¨Æ¥óªº¨ç¼Æ 
    float GenerateTime(float);                     //«Å§i²£¥Í®É¶¡ªº¨ç¼Æ 
    void InsertEvent(float, int *, float, int);    //«Å§i´¡¤J¨Æ¥óªº¨ç¼Æ  
    void PutInQueue(int *, float);                 //«Å§i±Æ¶¤ªº¨ç¼Æ 
    void GetFromQueue(float, int *, int *, float); //«Å§i¦³¤H±q±Æ¶¤¤¤Â÷¶}ªº¨ç¼Æ  
    void DeleteFirstEvent(int *);                  //§R±¼²Ä¤@­Ó¨Æ¥ó¨ç¼Æ 
    void PrintEvent(int), PrintQueue(int);         // ¦L¥X¨Æ¥ó¸ò±Æ¶¤¨Æ¥ó 
    
    int Nt=0,Qt=0;                                  //¨t²Î¤ºªºÁ`¤H¼Æ,±Æ¶¤ªºÁ`¤H¼Æ
    float Avg_Nt=0,Avg_Qt=0;                          //¥­§¡¨t²Î¤H¼Æ,¥­§¡±Æ¶¤¤H¼Æ
    float total_Nt = 0.0,total_Qt=0;                //®É¶¡¥[Åv¨t²Î¤ºªºÁ`¤H¼Æ,®É¶¡¥[Åv±Æ¶¤ªºÁ`¤H¼Æ
    
    
    
    
    GenerateFirstEvent(time, arrival_rate, &num_events);//²£¥Í²Ä¤@­Ó¨Æ¥ó¡A¨Æ¥ó¼Æ·|§ïÅÜ
    printf("cehck GenerateFirstEvent\n");
    PrintEvent(num_events);                            //¥ı¦L¥X¨ÓÀË¬dµ{¦¡¦³µL¥´¿ù 
    PrintQueue(num_queue);                             //¥ı¦L¥X¨ÓÀË¬dµ{¦¡¦³µL¥´¿ù
   // printf("cehck GenerateFirstEvent over\n");
    
    
   
  while(time <= LIMITS){
        total_Nt = total_Nt+(event[0].time - time)*Nt;//®É¶¡¥[Åv¨t²Î¤ºªºÁ`¤H¼Æ
		total_Qt = total_Qt+(event[0].time - time)*Qt;//®É¶¡¥[Åv±Æ¶¤ªºÁ`¤H¼Æ       
        time = event[0].time; // ¨ú¥X²Ä¤@­Ó¨Æ¥ó¡G¥Ø«eªº®É¶¡µ¥©ó²Ä¤@­Ó¨Æ¥óªº®É¶¡ 
        type = event[0].type; // ¨ú¥X²Ä¤@­Ó¨Æ¥ó¡G¦¹¨Æ¥óªºÃş«¬ 
        DeleteFirstEvent(&num_events);//¦]¬°®³¥X¨Ó¤F²Ä¤@­Ó¨Æ¥ó¡A­n§R±¼ 
        PrintEvent(num_events); //¬İ¬İ¥Ø«e¨Æ¥ó¼Æ¬O§_¬O0(¦]¬°§R±¼¤F) 
        
        
        if(type == ARRIVAL){
            Nt++;                                    //¦³¤H¶i¨Ó¨t²Î¤F,¨t²Î¤H¼Æ+1  
            next_time = GenerateTime(arrival_rate);  //²Ä¤@­Ó¨Æ¥ó©è¹F®Éªº®É¶¡ 
            InsertEvent(time, &num_events, next_time, ARRIVAL);  //´¡¤J¨Æ¥ó 
            PrintEvent(num_events);
            
            //¦pªGªA°È¤H­û²{¦b¦³ªÅ 
            if(Server_Is_Idle == TRUE){
                next_time = GenerateTime(service_rate);
                InsertEvent(time,&num_events, next_time, DEPT);
                Server_Is_Idle = FALSE;//¦]¬°ªA°È­û¥¿¦bªA°È«È¤H¡A¨SªÅ 
                PrintEvent(num_events);
            }
            //¦pªGªA°È¤H­û²{¦b¡u¨S¡v¦³ªÅ  
            else{
                 Qt++;                             //¦pªG¨t²Î¥¿¦b¦£¸L,±Æ¶¤¤H¼Æ+1 
                
                PrintQueue(num_queue);
                PutInQueue(&num_queue, time);//¦pªGªA°È­û¨SªÅ¡A´N¥h±Æ¶¤¡A&num_queue¡÷§ïÅÜ±Æ¶¤¤H¼Æ 
                PrintQueue(num_queue);
            }
        }
        //¦pªG¬OÂ÷¶}¨Æ¥ó 
        else if(type ==DEPT){
             Nt--;                         //¨t²Î¤H¼Æ-1                                    
            //¦pªG±Æ¶¤¤H¼Æ¤£µ¥©ó0¡A¨º¦³¤H´N­n±q±Æ¶¤¤¤Â÷¶}¡A¥hµ¹ªA°È­ûªA°È(¦]¬°¦³¤H³QªA°È­ûªA°È§¹²¦«á¡AÂ÷¶}) 
            if(num_queue != 0){ 
                Qt--;
                PrintEvent(num_events);
                PrintQueue(num_queue);
                GetFromQueue(time, &num_events, &num_queue, service_rate);//¦³¤H­n±q±Æ¶¤¤¤Â÷¶}¡A¥hµ¹ªA°È­ûªA°È(¦]¬°¦³¤H³QªA°È­ûªA°È§¹²¦«á¡AÂ÷¶})
                PrintEvent(num_events);  
                PrintQueue(num_queue); 
            }else
              //¦pªG¨S¦³¤H¦b±Æ¶¤¡A¨º»ò²{¦bªA°È­û´N¬OªÅ¶¢ªº  
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
 

//²£¥Í²Ä¤@­Ó¨Æ¥ó GenerateFirstEvent(time, arrival_rate, &num_events)
void GenerateFirstEvent(float time, float rate, int *num){
    float GenerateTime(float);
    void PrintEvent(int);
    
    event[0].time = time + GenerateTime(rate); // ²Ä¤@­Ó¨Æ¥óªº©è¹F®É¶¡·|µ¥©ó¥Ø«e®É¶¡¥[¤W¸g¹L¦h¤[«á·|©è¹Fªº®É¶¡(¥Î©è¹F²vºâ) 
    event[0].type = ARRIVAL;                   //²Ä¤@­Ó¨Æ¥óªºÃş«¬¬O©è¹F¨Æ¥ó  
    
    (*num)++; //­ì¥»¨Æ¥ó¼Æ¬O0¡A¦A²£¥Í¤@­Ó·s¨Æ¥ó«á¡A¥Ø«e¨Æ¥ó¼Æ¬°1 
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





//§R±¼²Ä¤@­Ó¨Æ¥ó 
void DeleteFirstEvent(int *num){
    int i;
    
    for(i = 0; i < *num; i++){
        event[i].type = event[i+1].type;
        event[i].time = event[i+1].time;
    }
    (*num)--;//¦]¬°§R±¼¨Æ¥ó¡A©Ò¥H¨Æ¥ó¼Æ´î1 
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
    float value = time + next_time;//²Ä¤G­Ó¨Æ¥ó©è¹F®Éªº®É¶¡ 
                
    if(*num == 0){
        event[0].time = value;
        event[0].type = type;
        *num = 1;
        return;
    }
    
   // PrintEvent(*num);
    
    target = *num - 1;
    
    //¤@ª½°µ¨ìtarget¤p©ó0¡A¤]´N¬O¨Æ¥ó¼Æ¤p©ó1¡A 
    while(target >= 0 && event[target].time > value){
        event[target+1].time = event[target].time;
        event[target+1].type = event[target].type;
        target--;
    }
    event[target+1].time = value;
    event[target+1].type = type;
    
    (*num)++;                //´¡¤J¤@­Ó¨Æ¥ó«á¡A¥Ø«eªº¨Æ¥ó¼Æ­n¥[¤@ 
}


//±Æ¶¤ PutInQueue(&num_queue, time)
void PutInQueue(int *num_queue, float time){
    queue[*num_queue].type = ARRIVAL;
    queue[*num_queue].time = time;
    (*num_queue)++;          //±Æ¶¤¤H¼Æ¼W¥[¤@¤H 
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
        queue[i].type = queue[i+1].type; //§â«á­±ªº²¾¨ì«e­± 
        queue[i].time = queue[i+1].time;
    }
    (*num_queue)--; //±Æ¶¤¤H¼Æ¤Ö±¼¤@­Ó¤H 
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
