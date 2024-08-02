#ifndef COUNT_FARES_H
#define COUNT_FARES_H

#include <all_route.h>

int fare[100];
int fare_id;


int choose_min(int fare[100])
{
    int min = 999999;
    int flag = -1;
    for(int i=0;i<10000;i++)
    {
        if(fare[i] == 0) continue;
        else
        {
            if(fare[i]<min)
            {
                min = fare[i];
                flag = i;
            }
        }
    }
    return flag;
}

int id_to_fare(struct information_of_flight iof[100][100],int id)
{
    for(int i=0;i<=80;i++)
    {
        for(int j=0;j<=80;j++)
        {
            for(int m=1;m <= iof[i][j].flight_num;m++)
            {
                if(id == iof[i][j].th[m])
                {
                    return iof[i][j].fares[m];
                }
            }
        }
    }

    return -999;
}

void count_fares(int dep,int arr,struct information_of_flight iof[100][100])
{

    for(int i=1;i<route_row;i++)
    {
        for(int j=1;j<route_length[i];j++)
        {
            fare[i] += id_to_fare(iof,all_route[i][j]);
        }
    }

    int min_fare_i = choose_min(fare);
    //打印最少花费
    cout<<"MINIMUM FARES : "<<fare[min_fare_i]<<endl;
    //打印对应路径
    cout<<"Flight ID   :";
    for(int result=1;result<route_length[min_fare_i];result++)
    {
        if(result == 1) cout<<all_route[min_fare_i][1];
        else cout<<"->"<<all_route[min_fare_i][result];
    }
    cout<<endl;
}


#endif // COUNT_FARES_H
