#include "includes.h"
#include "basic_data_structure.h"
#include "flight_reader.h"
#include "dfs_and_bfs.h"
#include "find_all_flight.h"
#include "all_route.h"
#include "count_fares.h"
#include "count_time.h"

int main()
{
    flight_reader();
    write_map();
    int dep_id;
    int arr_id;
    char pre_ord[100];
    char aft_ord[100];

    //选择功能
    int choice;
    cout<<"---------------------------Welcome to Flight Tracker!---------------------------"<<endl<<endl;
    cout<<"(DIRECTIONS)"<<endl;
    cout<<"1 for only dfs, inputting your departure id, and I offer all airports you can reach;"<<endl;
    cout<<"2 for only bfs, inputting your departure id, and I give you another algorithm;"<<endl;
    cout<<"3 for fetching all route (direct flight or one stopover), "<<
          endl<<"inputting your departure and arrival id, "
          "and I offer you all the route you can choose;"<<endl;
    cout<<"4 for minimum flight time,"<<endl<<"inputting your departure and arrival id, "
          "I count for the minimum time you need to spend;"<<endl;
    cout<<"5 for specific time intervals, "<<endl<<"inputting two IDs and departure time interval"
          "and I offer you all the route you can choose;"<<endl;
    cout<<"6 for minimum cost, inputting your departure and arrival id,"
          "I count for the minimum fares you need to cost;"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl<<endl;

    //输入并调用相应功能
    cout<<"NOW INPUT YOUR CHOICE OF FUNCTION :"<<endl<<endl<<"number:";
    cin>>choice;
    cout<<endl;
    cout<<endl;

    if(choice == 1)//1 for only dfs
    {
        cout<<"The DFS departure id : ";
        cin>>dep_id;
        cout<<endl;
        cout<<"The dfs routes if the airport are:"<<endl;
        cout<<endl;
        if(dep_id>79)
        {
            cout<<"There's no such airport!"<<endl;
        }
       else
        {
                dfsVisit(info,dep_id);
        }
    }

    else if(choice == 2)//2 for only bfs
    {
        cout<<"The BFS departure id : ";
        cin>>dep_id;
        cout<<endl;
        cout<<"The bfs routes if the airport are:"<<endl;
        cout<<endl;
        if(dep_id>79)
        {
            cout<<"There's no such airport!"<<endl;
        }
       else
        {
                bfsVisit(info,dep_id);
        }
    }

    else if(choice == 3)//3 for fetching all route (direct flight or one stopover)
    {
        cout<<"DEPARTURE ID: "<<endl;
        cin>>dep_id;
        cout<<"ARRIVAL   ID: "<<endl;
        cin>>arr_id;

        fs.open("C:/Users/Thinkpad/Desktop/result for all route (direct flight or one stopover).txt",ios::out);
        find_all_filght(dep_id,arr_id,info,"000000000000","999999999999");
    }

    else if(choice == 4)//4 for minimum flight time
    {
        cout<<"DEPARTURE ID: "<<endl;
        cin>>dep_id;
        cout<<"ARRIVAL   ID: "<<endl;
        cin>>arr_id;

        fs.open("C:/Users/Thinkpad/Desktop/result for all route (direct flight or one stopover).txt",ios::out);
        find_all_filght(dep_id,arr_id,info,"000000000000","999999999999");
        count_time(dep_id,arr_id,info);
        //cout<<endl;
    }

    else if(choice == 5)//5 for specific time intervals
    {
        cout<<"DEPARTURE ID: "<<endl;
        cin>>dep_id;
        cout<<"ARRIVAL   ID: "<<endl;
        cin>>arr_id;
        cout<<endl;
        cout<<"Departure time no earlier than: ";
        cin>>pre_ord;
        cout<<"Departure time no later than: ";
        cin>>aft_ord;
        cout<<endl;

        fs.open("C:/Users/Thinkpad/Desktop/result for specific time intervals.txt",ios::out);
        find_all_filght(dep_id,arr_id,info,pre_ord,aft_ord);
    }

    else if(choice == 6)//6 for minimum cost
    {
        cout<<"DEPARTURE ID: "<<endl;
        cin>>dep_id;
        cout<<"ARRIVAL   ID: "<<endl;
        cin>>arr_id;
        cout<<endl;
        cout<<"Departure time no earlier than: ";
        cin>>pre_ord;
        cout<<"Departure time no later than: ";
        cin>>aft_ord;
        cout<<endl;

        fs.open("C:/Users/Thinkpad/Desktop/result for specific time intervals.txt",ios::out);
        find_all_filght(dep_id,arr_id,info,pre_ord,aft_ord);
        count_fares(dep_id,arr_id,info);
    }

    else
    {
        cout<<"PLEASE enter the serial numbers 1-6 as required !"<<endl;
    }

    cout<<"PROGRAM OVER!"<<endl;
    return 0;
}

