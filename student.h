#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string number, name;
    int score1, score2, score3, sum;
    Student *next;
    Student(): number(""), name(""), score1(0), score2(0), score3(0), sum(0), next(nullptr) {}
};

void addStudent(Student *numberList, Student *scoreList);
void modify(Student *numberList, Student *scoreList);
void erase(string number, Student *numberList, Student *scoreList);
void CoutInformation(Student *list);
void findByNumber(string number, Student *list);
void findByName(string name, Student *numberList);
Student* findPrevByNumber(string number, Student *numberList);
Student* findStudentByNumber(string number, Student *numberList);
Student* findNumOrder(string number, Student *numberList);
Student* findScoreOrder(Student *newStudent, Student *scoreList);
void clearStudentList(Student *list);

#endif