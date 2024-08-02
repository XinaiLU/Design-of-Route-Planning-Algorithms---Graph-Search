#pragma once

#ifndef BASIC_DATA_STRUCTURE_H
#define BASIC_DATA_STRUCTURE_H



#define FLIGHT_SUM 100
#define CHAR_LENGTH 200

int flight_sum = 0;

struct information_of_flight
{
    int flight_num;//任意时间，机场A到机场B的所有直达航班数量
    //int flight_num;//区分这些不同时间直达航班的编号

    int th[FLIGHT_SUM];//总编号
    int airplane_ID[FLIGHT_SUM];//飞机编号
    int flight_NO[FLIGHT_SUM];

    char dep_date[FLIGHT_SUM][CHAR_LENGTH];//出发日期
    char dep_time[FLIGHT_SUM][CHAR_LENGTH];//出发时间，转换格式为“201705070420”
    char arr_time[FLIGHT_SUM][CHAR_LENGTH];//到达时间

    int model[FLIGHT_SUM];//飞机类型
    int fares[FLIGHT_SUM];//票价
    int i_or_d[FLIGHT_SUM];// 1为Intl国际航班，0为Dome国内航班

};



struct flight_map
{
    int airport_NO[100];
    struct information_of_flight info[100][100];
    int num_of_airport;
    int num_of_filght;
};


#endif // BASIC_DATA_STRUCTURE_H
