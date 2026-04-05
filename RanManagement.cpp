#include<iostream>
#include<algorithm>
#include"RanManagement.h"
using namespace std;
void GYMposition::setGYMposition(int index,GYMposition* posList){
    cin>>posList[index].latL>>posList[index].latR>>posList[index].lngL>>posList[index].lngR;
}
StudentInformation::StudentInformation():number(""),beginDate(""),beginTime(""),endDate(""),endTime(""),posNum(0),cnt(0){
    sumTime=0;
};
void StudentInformation::setNumber(int index,StudentInformation* list){
    cin>>list[index].number;
}
void StudentInformation::setTime(int index,StudentInformation* studentList){
    cin>>studentList[index].beginDate>>studentList[index].beginTime>>studentList[index].endDate>>studentList[index].endTime;
}
void StudentInformation::setPos(int cnt){
    pos=new Position [cnt];
    for(int i=0;i<cnt;i++){
        cin>>pos[i].lat>>pos[i].lng;
    }
}
int subTime(const StudentInformation &student){

}
bool StudentInformation::isLegal(string time1,string time2,const StudentInformation &student){
    if(student.beginDate>=time1&&student.endDate<=time2){
        if(student.beginDate==student.endDate){
            if(find(Date.begin(),Date.end(),student.beginDate)==Date.end()){
                if(student.beginTime<student.endTime&&
                   student.beginTime>=time1&&student.endTime<=time2){
                    Date.push_back(student.beginDate);
                    sumTime+=subTime(student);
                    return true;
                }
                else return false;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}