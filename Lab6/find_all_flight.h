#ifndef FIND_ALL_FLIGHT_H
#define FIND_ALL_FLIGHT_H
#pragma once

#include "includes.h"
#include "dfs_and_bfs.h"

#define ALL_ROUTE_ROW 10000
#define ALL_ROUTE_LEN 50

//记录一个节点下面的所有分支（时间）是否被访问过
int faf_visited[100][100][100];
//用于判断是否连接的存时间的数组，功能和纯DFS差不多
char time_faf[100][100];
//用于存储 departure 到 arrival 的所有路径的数组
int all_route[ALL_ROUTE_ROW][ALL_ROUTE_LEN];
int route_length[ALL_ROUTE_ROW];
int route_len_max = -1;

//已知起点、要判断是否连通的下一节点、到起点采用的是哪个到达时间、下一节点遍历到哪一个时间分支的序号
bool plus_connected(int dep_apt_num,int arr_apt_num,char last_arr_time[100],
                    int each,struct information_of_flight iof[100][100])
{
    //cout<<"in connected"<<endl;
    if(iof[dep_apt_num][arr_apt_num].flight_num != 0)//如果两地之间有飞机
    {
        if(strcmp(last_arr_time,iof[dep_apt_num][arr_apt_num].dep_time[each])<=0)
        {
            return true;
        }//end if strcmp

    return false;
    }//end if !=0

    else return false;
}//end bool


void delete_all_flag(int faf,struct information_of_flight iof[100][100])
{
    for(int i=1;i<=79;i++)
    {
        for(int each=1;each<=iof[faf][i].flight_num; each++)
        {
            faf_visited[faf][i][each] = 0;
        }
    }
}


//faf新进栈的航班不能出现在已存在的栈路径中
bool judge_repete(int faf,stack<int> faf_stack)
{
    int faf_save[100];
    int ini_size = faf_stack.size();

    if(ini_size == 1)
    {
        //void
        return true;
    }

    else
    {
        for(int i=1;i <= ini_size;i++)
        {
            faf_save[i] = faf_stack.top();
            faf_stack.pop();
        }

        for(int j=ini_size;j>=1;j--)
        {
            if(j == ini_size)
            {
                faf_stack.push(faf_save[j]);
            }
            else
            {
                faf_stack.push(faf_save[j]);
            }
        }
    }//不是出发点

    for(int m=1;m<=ini_size;m++)
    {
        if(faf == faf_save[m]) return false;

    }

    return true;
}

//打印栈中内容，即栈顶退栈时，所走的路径
int route_row = 1;//目前存的是第几条路径
fstream fs;

void faf_stack_route_print(int dep,int arr,stack<int> faf_stack,stack<int> faf_help,
                           struct information_of_flight iof[100][100])
{
    int faf_save[100];
    int help_save[100];
    int ini_size = faf_stack.size();
    int route_col = 1;

    //如果只剩下出发点，不打印
    if(ini_size == 1)
    {
        //void
    }
    else
    {
        for(int i=1;i <= ini_size;i++)
        {
            faf_save[i] = faf_stack.top();
            help_save[i] = faf_help.top();
            faf_stack.pop();
            faf_help.pop();
        }

        for(int j=ini_size;j>=1;j--)
        {
            if(j == ini_size)
            {
                //原函数中直接打印路径
                //cout<<"from "<<faf_save[j];
                //cout<<help_save[j]<<endl;
                //cout<<"ID:"<<iof[faf_save[j]][faf_save[j-1]].th[help_save[j-1]];
                fs<<"ID:"<<iof[faf_save[j]][faf_save[j-1]].th[help_save[j-1]];
                //save
                all_route[route_row][route_col] = iof[faf_save[j]][faf_save[j-1]].th[help_save[j-1]];

                route_col ++;
                faf_stack.push(faf_save[j]);
                faf_help.push(help_save[j]);
            }
            else
            {
                faf_stack.push(faf_save[j]);
                faf_help.push(help_save[j]);
                //cout<<"next"<<endl;
                //save
                if(j!=1)
                {
                    //cout<<" ->"<<"ID:"<<iof[faf_save[j]][faf_save[j-1]].th[help_save[j-1]];
                    fs<<"->"<<"ID:"<<iof[faf_save[j]][faf_save[j-1]].th[help_save[j-1]];
                    all_route[route_row][route_col] = iof[faf_save[j]][faf_save[j-1]].th[help_save[j-1]];
                }
                route_col ++;
            }
        }
        route_length[route_row] = ini_size;
        //route_len_max = max(route_col,route_len_max);

        route_row ++;
        //cout<<endl;
        fs<<endl;
    }//不是出发点
}

void find_all_filght(int dep_id,int arr_id,struct information_of_flight info[100][100],
                        char pre_time_order[100],char aft_time_order[100])
{

    //cout<<"in find all flight"<<endl;
    strcpy(time_faf[dep_id],"000000000000");

    //主栈里面存放邻接的机场ID
    stack<int> faf_stack;
    //辅助栈中存放主栈对应的机场的第N次航班信息
    stack<int> faf_help;

    // 没有含义，占位
    faf_stack.push(dep_id);
    faf_help.push(0);

    int faf = 0; //栈顶元素
    int help = 0; //help栈顶元素

    if(dep_id == arr_id)//输入限制
    {
        cout<<"You are at your target airport!"<<endl;
    }

    else
    {
        //栈深搜，打印所有路径
        while(!faf_stack.empty())
        {
            if(faf_stack.size()==1)//如果回到起始点是因为退栈，新一轮深搜
            {
                strcpy(time_faf[dep_id],"000000000000");
            }
            faf = faf_stack.top();
            help = faf_help.top();

            if(faf == arr_id)//如果栈顶元素是要到达的机场，那么打印栈里面的对应路径
            {
                //cout<<"find!"<<endl;
                faf_stack_route_print(dep_id,arr_id,faf_stack,faf_help,info);
                //dfs基本操作
                //cout<<endl;
                //delete_all_flag(faf,info);
                faf_stack.pop();//弹出栈顶元素
                faf_help.pop();//弹出栈顶元素
            }

            else
            {
                for(int i=1;i<=80;i++)//遍历每一个邻接点
                {
                    if( faf == i ) continue;
                    int cir_flag = 0;//用于跳出两层循环

                    for(int each=1;each <= info[faf][i].flight_num;each++)//遍历邻接点中的每一个
                    {
                        if(faf_stack.size()>1 || (faf_stack.size() == 1 &&
                                                  strcmp(info[faf][i].dep_time[each],pre_time_order)>=0
                                                  && strcmp(info[faf][i].dep_time[each],aft_time_order)<=0))
                        {
                            //cout<<"i:"<<i<<"  each:"<<each<<endl;
                            if(plus_connected(faf,i,time_faf[faf],each,info) && faf_visited[faf][i][each] == 0
                                    && judge_repete(i,faf_stack) && faf_stack.size() <=2 )
                            {

                                //cout<<"in if"<<endl;
                                //cout<<"i:"<<i<<"  each:"<<each<<endl;
                                //cout<<"size:"<<faf_stack.size()<<endl;
                                //cout<<pre_time_order<<"  "<<aft_time_order<<endl;

                                faf_visited[faf][i][each] = 1;//标记被访问过的路径

                                strcpy(time_faf[i],info[faf][i].arr_time[each]);
                                //cout<<"flag:"<<info[49][57].arr_time[1]<<endl;


                                faf_stack.push(i);
                                faf_help.push(each);

                                faf = faf_stack.top();
                                help = faf_help.top();

                                //cout<<1<<endl;

                                cir_flag = 1;
                                break;
                            }


                        }//if

                    }//for each

                if(cir_flag == 1) break;

                if(i==80)
                {
                    //去除即将出栈点到后面的所有路径
                    faf = faf_stack.top();
                    help = faf_help.top();
                    delete_all_flag(faf,info);
                    //出栈
                    faf_stack.pop();
                    faf_help.pop();
                    //break;

                }//if i==80

                }//for i

            }//else

        }//while

        //cout<<"There's no route !"<<endl;

    }//else
}//find all filghts


#endif // FIND_ALL_FLIGHT_H
