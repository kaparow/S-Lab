#pragma once

#include "header.h"


class CS
{
    int number_of_workshops;
    int effectiveness;


public:

    int ID;
    inline static int MaxId = 1000;
    std::string name;
    int workshops_in_operation;

    CS();
    CS(std::string name, int number_of_workshops, int workshops_in_operation, int effectiveness);

    void InputInfo();

    void PrintInfo();

    void Edit();

    void Edit(int active);

    void SetMaxId(int MaxId) { this->MaxId = MaxId; };
    int GetMaxId() { return MaxId; };

    int GetID() { return ID; };

    friend std::ofstream& operator << (std::ofstream& out, const CS& cs);
    friend std::ifstream& operator >> (std::ifstream& file, CS& cs);
};