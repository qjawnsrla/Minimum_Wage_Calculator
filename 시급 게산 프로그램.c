#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

int leaf_year(int year);
int month_12(int year, int month);
int get_day(int year, int month);
void calendar(int start_day, int day_num);
double money(int sum);
double week_money(int week_time);
void money_print(int month, int sum, int a_number, int a_i[], double a_money[], double week_money_sum);
void calculate(int year,int month);
int calculate_time(int start_time, int end_time, int* h_s, int* h_e, int* m_s, int* m_e);
void calculate_time_print(int start_time, int end_time);
void loop(int month, int s_t, int e_t,int number, int a, int num, int n, int m, int* day, int* sum, int* a_number, int (*a_i)[6], double (*a_money)[6], int day_num, int x);

int main(void)
{
    int year,month;
    printf("년도 입력: ");
    scanf("%d",&year);
    printf("월 입력: ");
    scanf("%d",&month);
    int start_day = get_day(year,month);
    int day_num = month_12(year,month);
    calendar(start_day, day_num);
    printf("\n\n시간에 '-1' 입력시 프로그램 강제종료\n");
    calculate(year,month);
    return 0;
}

int month_12(int year, int month)
{
    int month_12[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    month_12[1] += leaf_year(year);
    return month_12[month-1];
}

int leaf_year(int year)
{
    if(year%400==0){
        return 1;
    }
    if((year%100!=0) && (year%4==0)){
        return 1;
    }
    return 0;
}

int get_day(int year, int month)
{
    int past = 0;
    for(int y=1; y<year; y++){
        past = past + 365 + leaf_year(y);
    }
    for(int m=1; m<month; m++){
        past = past + month_12(year,m);
    }
    return (1+past) % 7;
}

void calendar(int start_day, int day_num){
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");
    for(int i=0; i<start_day; i++){
        printf("    ");
    }
    for(int day=1,ke=start_day; day<=day_num; day++, ke++){
        printf("%4d",day);
        if(ke%7 ==6){
            printf("\n");
        }
    }
}
void loop(int month, int s_t, int e_t,int number, int a, int num, int n, int m, int* day, int* sum, int* a_number, int (*a_i)[6], double (*a_money)[6], int day_num, int x)
{
    char week[]="월화수목금토일월화수목금토일";
    *day = day_num;
    int h_s,h_e,m_s,m_e;
    int ar_i[6];
    double ar_money[6];
    if(x==0){
        *sum = 0;
        *a_number = 0;
    }
    for(int i=0; i<a; i++){
        printf("\n%d주차\n",num);
        int week_time=0;
        for(int j=0; j<n; j++){
            printf("%d월 %d일 %c%c%c요일\n",month,*day+m+j,week[number+12],week[number+13],week[number+14]);
            while(1){
                printf("시작시간: ");
                scanf("%d",&s_t);
                printf("종료시간: ");
                scanf("%d",&e_t);
                calculate_time(s_t,e_t,&h_s,&h_e,&m_s,&m_e);
                if(s_t==-1 || e_t==-1){
                    printf("프로그램을 종료합니다.\n");
                    exit(0);
                }
                if( s_t>0 && e_t>0 && ((h_s>=0)&&(h_s<=24)) && ((h_e>=0)&&(h_e<24)) && (h_e>=h_s) && ((m_s>=0)&&(m_s<=60)) && ((m_e>=0)&&(m_e<60)) ){
                    break;
                }
                printf("잘못된 시간을 입력하였습니다.\n");
            }
            printf("일한시간: ");
            calculate_time_print(s_t,e_t);
            printf("\n");
            *sum += calculate_time(s_t,e_t,&h_s,&h_e,&m_s,&m_e);
            week_time += calculate_time(s_t,e_t,&h_s,&h_e,&m_s,&m_e);
            number+=3;
        }
        if(week_time<900){
            printf("%d주차 총 일한시간 %d시간 %d분, 주휴수당에 해당하지 않음\n",num,week_time/60,week_time%60);
        }
        if(week_time>=900){
            printf("%d주차 총 일한시간 %d시간 %d분, 주휴수당에 해당함\n",num,week_time/60,week_time%60);
            ar_i[*a_number] = num;
            ar_money[*a_number] = week_money(week_time);
            *a_number+=1;
        }
        num+=1;
        *day +=7; 
        number-=9;      
    }
    for(int j=0; j<*a_number; j++){
        (*a_i)[j] = ar_i[j];
        (*a_money)[j] = ar_money[j];
    }
}

void calculate(int year,int month)
{
    int num = get_day(year,month);
    char week[]="월화수목금토일월화수목금토일";
    int a_i[6];
    double a_money[6];
    int day, sum, a_number;
    double week_money_sum=0;
    int s_t,e_t;
    int leaf = leaf_year(year);

    //1일이 일요일일때 
    if(num==0){
        loop(month,s_t,e_t,6,1,1,1,0,&day,&sum,&a_number,&a_i,&a_money,1,0);
        //윤년이 아닐때
        if(leaf == 0){
            if(month !=2){
                loop(month,s_t,e_t,0,4,2,3,5,&day,&sum,&a_number,&a_i,&a_money,1,1);
            }
            if(month==2){
                loop(month,s_t,e_t,0,3,2,3,5,&day,&sum,&a_number,&a_i,&a_money,1,1);
                loop(month,s_t,e_t,0,1,5,2,5,&day,&sum,&a_number,&a_i,&a_money,22,1);
            }
        }
        //윤년일때 
        if(leaf == 1){
            loop(month,s_t,e_t,0,4,1,3,5,&day,&sum,&a_number,&a_i,&a_money,1,1);
        }
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);
    }
    //1일이 월요일일때     
    if(num==1){
        loop(month,s_t,e_t,0,4,1,3,4,&day,&sum,&a_number,&a_i,&a_money,1,0);
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);       
    }
    //1일이 화요일일때 
    if(num==2){
        loop(month,s_t,e_t,0,4,1,3,3,&day,&sum,&a_number,&a_i,&a_money,1,0);
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);               
    }
    //1일이 수요일일때 
    if(num==3){
        loop(month,s_t,e_t,0,4,1,3,2,&day,&sum,&a_number,&a_i,&a_money,1,0);
        //31일까지 있는 달 계산
        if((month==1) || (month==3) || (month==5) || (month==7) || (month==8) || (month==10) || (month==12)){
            loop(month,s_t,e_t,0,1,5,1,2,&day,&sum,&a_number,&a_i,&a_money,29,1);
        }
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);              
    }
    //1일이 목요일일때 
    if(num==4){
        loop(month,s_t,e_t,0,4,1,3,1,&day,&sum,&a_number,&a_i,&a_money,1,0);
        //31일까지 있는 달 계산
        if((month==1) || (month==3) || (month==5) || (month==7) || (month==8) || (month==10) || (month==12)){
            loop(month,s_t,e_t,0,1,5,2,1,&day,&sum,&a_number,&a_i,&a_money,29,1);
        }
        //31일까지 있는 달을 뺀, 30일까지 있는 달 계산
        if((month==4) || (month==6) || (month==9) || (month==11)){
            loop(month,s_t,e_t,0,1,5,1,1,&day,&sum,&a_number,&a_i,&a_money,29,1);
        }
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);                
    }
    //1일이 금요일일때 
    if(num==5){
        loop(month,s_t,e_t,0,4,1,3,0,&day,&sum,&a_number,&a_i,&a_money,1,0);
        //윤년일 때
        if(leaf==1){
            if(month!=2){
                if((month==1) || (month==3) || (month==5) || (month==7) || (month==8) || (month==10) || (month==12)){
                    loop(month,s_t,e_t,0,1,5,3,0,&day,&sum,&a_number,&a_i,&a_money,29,1);
                }
                if((month==4) || (month==6) || (month==9) || (month==11)){
                    loop(month,s_t,e_t,0,1,5,2,0,&day,&sum,&a_number,&a_i,&a_money,29,1);
                }                   
            }
            if(month==2){
                loop(month,s_t,e_t,0,1,5,1,0,&day,&sum,&a_number,&a_i,&a_money,29,1);
            }
        }
        //윤년이 아닐때
        if(leaf==0){
            if((month==1) || (month==3) || (month==5) || (month==7) || (month==8) || (month==10) || (month==12)){
                loop(month,s_t,e_t,0,1,5,3,0,&day,&sum,&a_number,&a_i,&a_money,29,1);
            }
            if((month==4) || (month==6) || (month==9) || (month==11)){
                loop(month,s_t,e_t,0,1,5,2,0,&day,&sum,&a_number,&a_i,&a_money,29,1);
            }                              
        }
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);     
    }
    //1일이 토요일일때 
    if(num==6){
        loop(month,s_t,e_t,3,1,1,2,0,&day,&sum,&a_number,&a_i,&a_money,1,0);
        //윤년이 아닐때
        if(leaf == 0){
            if(month !=2){
                loop(month,s_t,e_t,0,4,2,3,0,&day,&sum,&a_number,&a_i,&a_money,7,1);               
            }
            if(month == 2){
                loop(month,s_t,e_t,0,3,2,3,0,&day,&sum,&a_number,&a_i,&a_money,7,1);
                loop(month,s_t,e_t,0,1,5,1,0,&day,&sum,&a_number,&a_i,&a_money,28,1);                                     
            }
        }
        //윤년일때 
        if(leaf == 1){
            if(month !=2){
                loop(month,s_t,e_t,0,4,2,3,0,&day,&sum,&a_number,&a_i,&a_money,7,1);              
            }
            if(month==2){
                loop(month,s_t,e_t,0,3,2,3,0,&day,&sum,&a_number,&a_i,&a_money,7,1);
                loop(month,s_t,e_t,0,1,5,2,0,&day,&sum,&a_number,&a_i,&a_money,28,1);                               
            }
        }
        money_print(month,sum,a_number,a_i,a_money,week_money_sum);            
    }                
}

double money(int sum){
    double result = round((double)sum*10)/10/60 * 10000;
    return result;
}

double week_money(int week_time){
    double result = ((double)week_time/60)/40 * 8 * 10000;
    return result;
}

void money_print(int month, int sum, int a_number, int a_i[], double a_money[], double week_money_sum){
    printf("\n\n%d월 총 일한시간 %d시간 %d분, 월급: %d원\n",month,sum/60,sum%60,(int)money(sum));
    if(a_number>0){
        for(int i=0; i<a_number; i++){
            printf("%d주차 15시간 초과, 주휴수당 %.0f원\n",a_i[i],a_money[i]);
            week_money_sum += a_money[i];
        }
        printf("주휴수당 포함한 총 월급: %d원\n",(int)(round(week_money_sum*10)/10+round(money(sum*10))/10) );
    }    
}

int calculate_time(int start_time, int end_time, int* h_s, int* h_e, int* m_s, int* m_e){
    int h,m =0;
    int h_s_1 = start_time/1000;
    int h_s_2 = (start_time%1000)/100;
    *h_s = h_s_1*10 + h_s_2;

    int h_e_1 = end_time/1000;
    int h_e_2 = (end_time%1000)/100;
    *h_e = h_e_1*10 + h_e_2;

    int m_s_1 = ((start_time%1000)%100)/10;
    int m_s_2 = ((start_time%1000)%100)%10;
    *m_s = m_s_1*10 + m_s_2;

    int m_e_1 = ((end_time%1000)%100)/10;
    int m_e_2 = ((end_time%1000)%100)%10;
    *m_e = m_e_1*10 + m_e_2;

    if(*m_s<=*m_e){
        h = *h_e-*h_s;
        m = *m_e-*m_s;
    }
    else if(*m_s>*m_e){
        if(*h_e-*h_s>1){
            h = *h_e-*h_s-1;
            m = *m_e+60-*m_s;
        }
        else if(*h_e-*h_s<=1){
            h = 0;
            m = *m_e+60-*m_s;
        }
    }
    int time = h*60 + m;
    return time;
}

void calculate_time_print(int start_time, int end_time){
    int h_s,h_e,m_s,m_e;
    int time = calculate_time(start_time,end_time,&h_s,&h_e,&m_s,&m_e);
    int h = time/60;
    int m = time%60;
    printf("%d시간 %d분",h,m);
}
