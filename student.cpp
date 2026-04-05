#include "student.h"
#include <limits>

static Student* cloneStudent(const Student* source) {
    Student* node = new Student(*source);
    node->next = nullptr;
    return node;
}

Student* findPrevByNumber(string number, Student* list) {
    Student* prev = list;
    while (prev->next != nullptr && prev->next->number != number) {
        prev = prev->next;
    }
    return prev;
}

Student* findStudentByNumber(string number, Student* numberList) {
    Student* position = numberList->next;
    while (position != nullptr) {
        if (position->number == number) {
            return position;
        }
        position = position->next;
    }
    return nullptr;
}

Student* findNumOrder(string number, Student* numberList) {
    Student* prev = numberList;
    while (prev->next != nullptr && prev->next->number < number) {
        prev = prev->next;
    }
    return prev;
}

Student* findScoreOrder(Student* newStudent, Student* scoreList) {
    Student* prev = scoreList;
    while (prev->next != nullptr) {
        if (prev->next->sum > newStudent->sum) {
            prev = prev->next;
        } else if (prev->next->sum == newStudent->sum && prev->next->number < newStudent->number) {
            prev = prev->next;
        } else {
            break;
        }
    }
    return prev;
}

void CoutInformation(Student* list) {
    Student* position = list->next;
    if (position == nullptr) {
        cout << "当前列表为空。" << endl;
        return;
    }
    cout << "学号\t姓名\t成绩1\t成绩2\t成绩3\t总分" << endl;
    while (position != nullptr) {
        cout << position->number << '\t'
             << position->name << '\t'
             << position->score1 << '\t'
             << position->score2 << '\t'
             << position->score3 << '\t'
             << position->sum << endl;
        position = position->next;
    }
}

void findByNumber(string number, Student* numberList) {
    Student* position = findStudentByNumber(number, numberList);
    if (position == nullptr) {
        cout << "未找到学号为 " << number << " 的学生。" << endl;
        return;
    }
    cout << "找到学生：" << position->number << ' ' << position->name << ' '
         << position->score1 << ' ' << position->score2 << ' ' << position->score3 << " 总分=" << position->sum << endl;
}

void findByName(string name, Student* numberList) {
    Student* position = numberList->next;
    bool found = false;
    while (position != nullptr) {
        if (name.empty() || position->name.find(name) != string::npos) {
            found = true;
            cout << position->number << ' ' << position->name << ' '
                 << position->score1 << ' ' << position->score2 << ' '
                 << position->score3 << " 总分=" << position->sum << endl;
        }
        position = position->next;
    }
    if (!found) {
        cout << "未找到姓名包含 '" << name << "' 的学生。" << endl;
    }
}

void addStudent(Student* numberList, Student* scoreList) {
    Student* newStudent = new Student();
    cin >> newStudent->number >> newStudent->score1 >> newStudent->score2 >> newStudent->score3;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent->name);
    newStudent->sum = newStudent->score1 + newStudent->score2 + newStudent->score3;

    if (newStudent->number.empty() || newStudent->name.empty()) {
        cout << "输入信息不完整，添加失败。" << endl;
        delete newStudent;
        return;
    }

    if (newStudent->score1 < 0 || newStudent->score2 < 0 || newStudent->score3 < 0) {
        cout << "成绩不能为负数，添加失败。" << endl;
        delete newStudent;
        return;
    }

    Student* existStudent = findStudentByNumber(newStudent->number, numberList);
    if (existStudent != nullptr) {
        existStudent->name = newStudent->name;
        existStudent->score1 = newStudent->score1;
        existStudent->score2 = newStudent->score2;
        existStudent->score3 = newStudent->score3;
        existStudent->sum = newStudent->sum;

        Student* scorePrev = findPrevByNumber(newStudent->number, scoreList);
        if (scorePrev->next != nullptr) {
            Student* moved = scorePrev->next;
            scorePrev->next = moved->next;
            moved->next = nullptr;
            moved->name = newStudent->name;
            moved->score1 = newStudent->score1;
            moved->score2 = newStudent->score2;
            moved->score3 = newStudent->score3;
            moved->sum = newStudent->sum;
            Student* scorePos = findScoreOrder(moved, scoreList);
            moved->next = scorePos->next;
            scorePos->next = moved;
        }

        cout << "已更新学生 " << newStudent->number << " 的信息。" << endl;
        delete newStudent;
        return;
    }

    Student* numNode = cloneStudent(newStudent);
    Student* scoreNode = cloneStudent(newStudent);

    Student* numPos = findNumOrder(newStudent->number, numberList);
    numNode->next = numPos->next;
    numPos->next = numNode;

    Student* scorePos = findScoreOrder(newStudent, scoreList);
    scoreNode->next = scorePos->next;
    scorePos->next = scoreNode;

    cout << "已添加学生 " << newStudent->number << "。" << endl;
    delete newStudent;
}

void modify(Student* numberList, Student* scoreList) {
    string number, name;
    int s1, s2, s3;
    cin >> number >> s1 >> s2 >> s3;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    Student* position = findStudentByNumber(number, numberList);
    if (position == nullptr) {
        cout << "未找到学号为 " << number << " 的学生，修改失败。" << endl;
        return;
    }
    if (name.empty()) {
        cout << "姓名不能为空，修改失败。" << endl;
        return;
    }

    position->name = name;
    position->score1 = s1;
    position->score2 = s2;
    position->score3 = s3;
    position->sum = s1 + s2 + s3;

    Student* scorePrev = findPrevByNumber(number, scoreList);
    if (scorePrev->next != nullptr) {
        Student* moved = scorePrev->next;
        scorePrev->next = moved->next;
        moved->next = nullptr;
        moved->name = name;
        moved->score1 = s1;
        moved->score2 = s2;
        moved->score3 = s3;
        moved->sum = position->sum;
        Student* scorePos = findScoreOrder(moved, scoreList);
        moved->next = scorePos->next;
        scorePos->next = moved;
    }

    cout << "已修改学生 " << number << " 的信息。" << endl;
}

void erase(string number, Student* numberList, Student* scoreList) {
    Student* prevNum = findPrevByNumber(number, numberList);
    if (prevNum->next != nullptr) {
        Student* tempNumber = prevNum->next;
        prevNum->next = tempNumber->next;
        delete tempNumber;
        cout << "学生 " << number << " 已从学号列表删除。" << endl;
    } else {
        cout << "未在学号列表找到学号 " << number << "。" << endl;
    }

    Student* prevScore = findPrevByNumber(number, scoreList);
    if (prevScore->next != nullptr) {
        Student* tempScore = prevScore->next;
        prevScore->next = tempScore->next;
        delete tempScore;
        cout << "学生 " << number << " 已从成绩列表删除。" << endl;
    } else {
        cout << "未在成绩列表找到学号 " << number << "。" << endl;
    }
}

void clearStudentList(Student* list) {
    Student* current = list->next;
    while (current != nullptr) {
        Student* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    list->next = nullptr;
}
