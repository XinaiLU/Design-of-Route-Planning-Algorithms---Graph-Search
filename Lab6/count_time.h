#ifndef COUNT_TIME_H
#define COUNT_TIME_H

#include <all_route.h>

char up[ALL_ROUTE_ROW][5][100];
char down[ALL_ROUTE_ROW][5][100];
int sum_up[ALL_ROUTE_ROW];
int sum_down[ALL_ROUTE_ROW];
int sum_fly[ALL_ROUTE_ROW];


int choose_min_time(int time[100])
{
    int min = 999999999;
    int flag = -1;
    for(int i=0;i<ALL_ROUTE_ROW;i++)
    {
        if(time[i] == 0) continue;
        else
        {
            if(time[i] < min)
            {
                min = time[i];
                flag = i;
            }
        }
    }
    return flag;
}

char* id_to_dep(struct information_of_flight iof[100][100],int id)
{
    //cout<<"in id_to_dep---------"<<endl;
    for(int i=1;i<=80;i++)
    {
        for(int j=1;j<=80;j++)
        {
            for(int m=1;m <= iof[i][j].flight_num;m++)
            {
                if(id == iof[i][j].th[m])
                {
                    //cout<<"1"<<endl;
                    //cout<<"change dep_time: "<<iof[i][j].dep_time[m]<<endl;
                    return iof[i][j].dep_time[m];
                }
            }
        }
    }
    //cout<<"after for"<<endl;
    return NULL;
}

char* id_to_arr(struct information_of_flight iof[100][100],int id)
{
    //cout<<"in id_to_arr---------"<<endl;
    for(int i=0;i<=80;i++)
    {
        for(int j=0;j<=80;j++)
        {
            for(int m=1;m <= iof[i][j].flight_num;m++)
            {
                if(id == iof[i][j].th[m])
                {
                    //cout<<"OK"<<endl;
                    return iof[i][j].arr_time[m];
                }
            }
        }
    }

    return NULL;
}

//将时间字符串换成可以操作计算的 INT 分钟
int timechar_to_minute(char time[100])
{
    //cout<<"in time to min"<<endl;
    //cout<<"time:"<<time<<endl;
    //cout<<"11:"<<time[11];
    //cout<<"6:"<<time[6];
    //cout<<time[6]<<time[7]<<time[8]<<time[9]<<time[10]<<time[11]<<endl;
    return time[11]+time[10]*10+time[9]*60+time[8]*600+time[7]*24*60+time[6]*240*60;
}

//将生成的航线图谱的每一个空格中的 ID 对应的起飞时间和降落时间都存在不同的数组中
//存入 up、down数组中
void save_time(int dep,int arr,
                struct information_of_flight iof[100][100])
{
    //cout<<"in save time"<<endl;
    //cout<<"row:"<<route_row<<endl;
    for(int i=1;i<route_row;i++)
    {
        //cout<<i<<" "<<route_length[i]<<endl;
        for(int j=1;j<route_length[i];j++)
        {

            //cout<<id_to_dep(iof,all_route[i][j])<<endl;
            strcpy(up[i][j],id_to_dep(iof,all_route[i][j]));
            strcpy(down[i][j],id_to_arr(iof,all_route[i][j]));
            //cout<<"up:"<<up[i][j]<<"   down:"<<down[i][j]<<endl;
        }
    }
}

void count_time(int dep,int arr,struct information_of_flight iof[100][100])
{
    //OK
    save_time(dep,arr,iof);

    //cout<<"in count_time"<<endl;
    for(int i=1;i<route_row;i++)
    {
        for(int j=1;j<route_length[i];j++)
        {
            if(j != route_length[i]-1)
            {

                sum_up[i] += (timechar_to_minute(down[i][j]) - timechar_to_minute(up[i][j]));
                sum_down[i] += (timechar_to_minute(up[i][j+1]) - timechar_to_minute(down[i][j]));

            }
            else
            {
                sum_up[i] += (timechar_to_minute(down[i][j]) - timechar_to_minute(up[i][j]));
            }

        }
        sum_fly[i] = sum_up[i]+ sum_down[i];
        //cout<<i<<"  "<<up[i][1]<<"  "<<down[i][route_length[i]-1]<<"  "<<sum_fly[i]<<endl;
    }

    //cout<<"after for"<<endl;
    int min_i = choose_min_time(sum_fly);
    //打印 ID
    cout<<"Flight ID   :";
    for(int result=1;result<route_length[min_i];result++)
    {
        if(result == 1) cout<<all_route[min_i][1];
        else cout<<"->"<<all_route[min_i][result];
    }
    cout<<endl;
    //打印出发时间
    cout<<"FROM AIRPORT(DEPARTURE) "<<dep<<" AT "<<up[min_i][1]<<endl;
    //打印飞行时间
    cout<<"MINIMUM FLYING TIME(IN AEROPLANE): "<<sum_up[choose_min_time(sum_fly)]<<" mins" <<endl;
    //打印换乘时间
    cout<<"TRANSIT WAITING TIME: "<<sum_down[choose_min_time(sum_fly)]<<" mins" <<endl;
    //打印到达时间
    cout<<"ARRIVE AIRPORT "<<arr<<" AT "<<down[min_i][route_length[min_i]-1]<<endl;
    //打印总的飞行时间
    cout<<"TOTAL FLIGHT TIME: "<<sum_fly[min_i]<<" mins" <<endl;
}


#endif // COUNT_TIME_H
