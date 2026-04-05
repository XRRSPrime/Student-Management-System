#ifndef RANMANAGEMENT_H
#define RANMANAGEMENT_H
#include<string>
#include<vector>
class GYMposition{
    int latL,latR,lngL,lngR;
public:
    void setGYMposition(int index,GYMposition* posList);
};
struct Position{
    int lat,lng;
    Position():lat(0),lng(0){}
};
class StudentInformation{
private:
    std::string number,beginDate,beginTime,endDate,endTime;
    std::vector<std::string>Date;
    int posNum,cnt;
    Position* pos;
    static int sumTime;
public:
    bool isLegal(std::string time1,std::string time2,const StudentInformation &student);    //看看是否在系统开始和结束之间的时间段
    void setNumber(int index,StudentInformation* list);   //设置学号
    void setTime(int index,StudentInformation* studentList);     //设置时间
    void setPos(int cnt);      //设置场地
};
#endif