#ifndef DFS_AND_BFS_H
#define DFS_AND_BFS_H

#include "includes.h"
#include "basic_data_structure.h"

//访问标志数组，初值全为0，表示所有顶点都没有被访问过
int visited[100]={0};
int bfs_vst[100]={0};

//辅助数组，记录每一次入栈的结构体采用的是哪个时间的航班
char time_char[100][100];
char time_char_bfs[100][100];
int dfs_print[100];
int bfs_print[100];

//判断两个机场之间路线、时间是否连通,并记录最终取arrival的到达时间
bool if_connected (int dep_apt_num,int arr_apt_num,char last_arr_time[100],
                struct information_of_flight iof[100][100])
{
    if(iof[dep_apt_num][arr_apt_num].flight_num != 0)//如果两地之间有飞机
    {
        for(int i=1;i<=iof[dep_apt_num][arr_apt_num].flight_num;i++)//遍历两地之间的航班
        {
            if(strcmp(last_arr_time,iof[dep_apt_num][arr_apt_num].dep_time[i])<=0)
                //找到两地之间符合时间要求的最早航班
            {
                //记录到达终点机场的最早航班的到达时间进入数组
                 return true;
            }//end if strcmp
        }//end for

        return false;
    }//end if !=0

    else return false;
}//end bool

void stack_route_print(stack<int> dfs_stack)
{
    int save[100];
    int ini_size = dfs_stack.size();

    //如果只剩下出发点，不打印
    if(ini_size == 1)
    {
        //void
    }
    else
    {
        for(int i=1;i <= ini_size;i++)
        {
            save[i] = dfs_stack.top();
            dfs_stack.pop();
        }

        for(int j=ini_size;j>=1;j--)
        {
            if(j == ini_size)
            {
                cout<<save[j];
                dfs_stack.push(save[j]);
            }
            else
            {
                cout<<"->"<<save[j];
            }
        }
    }//不是出发点
}

//DFS
void dfsVisit(struct information_of_flight iof[100][100],int dep_apt)
{
    stack<int> dfs_stack;//栈

    cout<<"The DFS departure id:"<<endl;
    visited[dep_apt] = 1;
    strcpy(time_char[dep_apt],"000000000000");//出发机场的到达时间为0，初始化
    dfs_stack.push(dep_apt);
    //whole_dfs
    //cout<<dep_apt;
    int pop_ele = 0;

    while(!dfs_stack.empty())
    {
        pop_ele = dfs_stack.top();
        for(int i=1;i<=80;i++)//遍历 pop_ele的邻接,获得 pop_ele的第一个未访问过的邻接
        {
            if(if_connected(pop_ele,i,time_char[pop_ele],iof) && visited[i] == 0 )
            {
                visited[i] = 1;
                dfs_stack.push(i);
                //whole dfs
                //cout<<"->"<<i;
                pop_ele = dfs_stack.top();
                break;
            }//end if

            if(i == 80)//不存在相邻且未访问的节点
            {
                //打印存储全部栈内容，即要达到出栈点的详细全部路径
                dfs_print[0] = dfs_stack.size();
                stack_route_print(dfs_stack);
                //dfs基本操作
                cout<<endl;
                dfs_stack.pop();
            }//in if == 80
        }//end for
    }//end while
}//end dfsVisit


//BFS
void bfsVisit(struct information_of_flight iof[100][100],int dep_apt)
{
    queue<int> bfs_queue;

    cout<<endl;
    cout<<endl;
    cout<<"The BFS departure id:"<<endl;

    bfs_vst[dep_apt] = 1;
    strcpy(time_char_bfs[dep_apt],"000000000000");//出发机场的到达时间为0，初始化
    bfs_queue.push(dep_apt);
    int pop_ele2 = 0;

    while(!bfs_queue.empty())
    {
        int num = 0;
        pop_ele2 = bfs_queue.front();
        cout<<pop_ele2<<"->";
        bfs_vst[pop_ele2] = 1;
        bfs_queue.pop();

        for(int i=1;i<=80;i++)
        {
            if(if_connected(pop_ele2,i,time_char_bfs[pop_ele2],iof) && bfs_vst[i] == 0 )
            {
                bfs_vst[i] = 1;
                bfs_queue.push(i);
                num++;
            }
        }
        if(num == 0)
        {
            //void
        }
    }
}


#endif // DFS_AND_BFS_H
