#pragma once

#include "header.h"


using namespace std;


class CS {
    int number_of_workshops;
    int effectiveness;

public:
    int ID;
    static int MaxId;

    string name;
    int workshops_in_operation;

    CS();
    CS(string name, int number_of_workshops, int workshops_in_operation, int effectiveness);

    void inputCSInfo();

    void PrintInfo();

    void EditCS();

    void Edit(int active);

    friend ofstream& operator << (ofstream& out, const CS& cs);
    friend ifstream& operator >> (ifstream& file, CS& cs);
};