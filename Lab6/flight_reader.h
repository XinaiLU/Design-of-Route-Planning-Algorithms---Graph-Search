#ifndef FLIGHT_READER_H
#define FLIGHT_READER_H

#pragma once

#include "includes.h"
#include "basic_data_structure.h"

struct information_of_flight info[100][100];

char* fill(char* str)
{
    if(strlen(str)!=2){char after[5] = "0"; strcat(after,str); strcpy(str,after);}
    return str;
}

int num_of_each = 0;

void flight_reader()
{
    fstream ifs;
    ifs.open("C:/Users/Thinkpad/Desktop/flight-data.csv",ios::in);
    //"C:\Users\Thinkpad\Desktop\flight-data.csv"
    if (!ifs.is_open()) {
        cout << "open file failed!" << endl;
        exit(-1);
    }
    //cout << "open the file!" << endl;

    string line;
    int read_line=0;
    while (getline(ifs, line)) {
        if(read_line == 0) {read_line++;}
        else
        {
            const char* split = "/,: ";
            char* p;
            p = strtok((char*)line.c_str(), split);
            char val[50];
            char save[100][100];//暂时存储信息的数组

            // for 切分
            for (int k = 0; p != NULL; k++) {
                sscanf(p, "%s", &val);

                p = strtok(NULL, split);

                if (k == 0) {strcpy(save[0], val);}// printf("ID:%s\n", save[0]);}
                else if (k == 1) {strcpy(save[1], val);}// printf("Dep_month:%s  ", val);}
                else if (k == 2){strcpy(save[2], val);}// printf("Dep_day:%s  ", val);}
                else if (k == 3){strcpy(save[3], val); }//printf("Dep_year:%s  ", val);}
                else if (k == 4){strcpy(save[4], val);}// printf("I_or_D:%s  ", val);}
                else if (k == 5){strcpy(save[5], val); }//printf("Flight_NO:%s  ", val);}
                else if (k == 6){strcpy(save[6], val); }//printf("Dep_airport:%s\n", val);} //第几个横行
                else if (k == 7){strcpy(save[7], val); }//printf("Arr_airport:%s  ", val);} //第几个竖行
                else if (k == 8){strcpy(save[8], val); }//printf("Dep_month:%s  ", val);}
                else if (k == 9){strcpy(save[9], val); }//printf("Dep_day:%s  ", val);}
                else if (k == 10){strcpy(save[10], val); }//printf("Dep_year:%s  ", val);}
                else if (k == 11){strcpy(save[11], val); }//printf("Dep_hour:%s  ", val);}
                else if (k == 12){strcpy(save[12], val); }//printf("Dep_minute:%s\n", val);}
                else if (k == 13){strcpy(save[13], val); }//printf("Arr_month:%s  ", val);}
                else if (k == 14){strcpy(save[14], val); }//printf("Arr_day:%s  ", val);}
                else if (k == 15){strcpy(save[15], val); }//printf("Arr_year:%s  ", val);}
                else if (k == 16){strcpy(save[16], val); }//printf("Arr_hour:%s  ", val);}
                else if (k == 17){strcpy(save[17], val); }//printf("Arr_minute:%s  ", val);}
                else if (k == 18){strcpy(save[18], val); }//printf("Airpiane ID:%s  ", val);}
                else if (k == 19){strcpy(save[19], val); }//printf("Airplane Model:%s  ", val);}
                else if (k == 20){strcpy(save[20], val); }//printf("Fares:%s\n", val);}
                else if (k >= 21)  break;
            }  // end for

            int dep_ap = atoi(save[6]);
            int arr_ap = atoi(save[7]);

            //修改日期、时间格式，例如 6号在前面加 0变成 06
            fill(save[1]);
            fill(save[2]);
            fill(save[8]);
            fill(save[9]);
            fill(save[11]);
            fill(save[12]);
            fill(save[13]);
            fill(save[14]);
            fill(save[16]);
            fill(save[17]);

            strcat(save[1],save[2]);
            strcat(save[3],save[1]);
            char convert_dep_date[100];
            strcpy(convert_dep_date,save[3]);

            //出发时间字符串转化 eg:2017/09/20 14:30
            strcat(save[11],save[12]);//14->1430
            strcat(save[9],save[11]);//1430->201430
            strcat(save[8],save[9]);//09201430
            strcat(save[10],save[8]);//201709201430
            char convert_dep_time[100];//initial
            strcpy(convert_dep_time,save[10]);//strcpy to char*

            //到达时间字符串转化
            strcat(save[16],save[17]);//14->1430
            strcat(save[14],save[16]);//1430->201430
            strcat(save[13],save[14]);//09201430
            strcat(save[15],save[13]);//201709201430
            char convert_arr_time[100];//initial
            strcpy(convert_arr_time,save[15]);//strcpy to char*
            //cout<<convert_arr_time<<endl;

            (info[dep_ap][arr_ap].flight_num)++;//从1开始标号
            num_of_each = info[dep_ap][arr_ap].flight_num;

            info[dep_ap][arr_ap].th[num_of_each] = atoi(save[0]);
            info[dep_ap][arr_ap].airplane_ID[num_of_each] = atoi(save[18]);
            info[dep_ap][arr_ap].flight_NO[num_of_each] = atoi(save[5]);
            strcpy( info[dep_ap][arr_ap].dep_date[num_of_each] , convert_dep_date );
            strcpy( info[dep_ap][arr_ap].dep_time[num_of_each] , convert_dep_time );
            strcpy( info[dep_ap][arr_ap].arr_time[num_of_each] , convert_arr_time );
            info[dep_ap][arr_ap].model[num_of_each] = atoi(save[19]);
            info[dep_ap][arr_ap].fares[num_of_each] = atoi(save[20]);
            info[dep_ap][arr_ap].i_or_d[num_of_each] = atoi(save[4]);

        }  // end while
    }//end else
}

void print_info()
{
    for(int i=1;i<=79;i++)
    {
        for(int j=1;j<=79;j++)
        {
            if(i != j)
            {
                cout<<"__________________________from "<<i<<" to "<<j<<" ____________________________"<<endl;
                for(int s=1; s<=info[i][j].flight_num; s++)
                {
                    cout<<"ID:"<<info[i][j].th[s]<<endl;
                    cout<<"Departure time:"<<info[i][j].dep_time[s]<<endl;
                    cout<<"Arrival time  :"<<info[i][j].arr_time[s]<<endl;
                    cout<<"Fares         :"<<info[i][j].fares[s]<<endl;
                }
            }

            else continue;
        }
    }
}

void write_map()
{
    //1、创建流对象
    fstream fs; //可输入输出
    //2、指定打开方式
    fs.open("C:/Users/Thinkpad/Desktop/Lab6_map.txt", ios::out);
    //3、文件写入
    for(int i=1;i<=79;i++)
    {
        for(int j=1;j<=79;j++)
        {
            if(i != j)
            {
                fs<<"__________________________from "<<i<<" to "<<j<<" ____________________________"<<endl;
                fs<<"flight number:  "<<info[i][j].flight_num<<endl;
                for(int s=1; s<=info[i][j].flight_num; s++)
                {

                    fs<<"ID:"<<info[i][j].th[s]<<endl;
                    fs<<"Departure time:"<<info[i][j].dep_time[s]<<endl;
                    fs<<"Arrival time  :"<<info[i][j].arr_time[s]<<endl;
                    fs<<"Fares         :"<<info[i][j].fares[s]<<endl;
                }
            }

            else continue;
        }
    }
    fs.close();

}
#endif // FLIGHT_READER_H
