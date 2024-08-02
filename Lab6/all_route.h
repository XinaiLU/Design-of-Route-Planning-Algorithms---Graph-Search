#ifndef ALL_ROUTE_H
#define ALL_ROUTE_H
#pragma once

#include <find_all_flight.h>

void print_all_route(int dep,int arr,int all_route[ALL_ROUTE_ROW][ALL_ROUTE_LEN])
{
    for(int i=1;i<route_row;i++)
    {
        for(int j=1;j<route_length[i];j++)
        {
            if(j == 1)
                cout<<all_route[i][j];
            else
                //cout<<"->"<<all_route[dep][arr][i][j];
                cout<<"->"<<all_route[i][j];

        }
        cout<<endl;
    }
}

void judge_twice(int dep,int arr,int all_route[ALL_ROUTE_ROW][ALL_ROUTE_LEN])
{
    int judge = 0;
    for(int i=1;i<route_row;i++)
    {
        if(route_length[i]<=3)//因为之前的函数 length 总是比真实的多1位
        {
            //cout<<"in if"<<endl;
            judge = 1;
            for(int j=1;j<route_length[i];j++)
            {
                if(j == 1)
                    cout<<all_route[i][j];
                else
                    cout<<"->"<<all_route[i][j];
            }
            cout<<endl;
        }

        else continue;
    }

    if(judge == 0) cout<<"There's no suitable flight!"<<endl;
}

#endif // ALL_ROUTE_H
