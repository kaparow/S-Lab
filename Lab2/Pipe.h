#pragma once
#include "header.h"



class Pipe
{
    float length;
    int diameter;


public:

    int ID;
    inline static int MaxId = 0;
    std::string name;
    bool in_repairing;

    Pipe();
    Pipe(const std::string name, const float length, const int diameter, const bool in_repairing);


    void InputInfo();

    void PrintInfo();

    void Edit();

    void Edit(int status);

    void SetMaxId(int MaxId) { this->MaxId = MaxId; };
    int GetMaxId() { return MaxId; };

    int GetID() { return ID; };

    friend std::ofstream& operator << (std::ofstream& out, const Pipe& pipe);
    friend std::ifstream& operator >> (std::ifstream& file, Pipe& pipe);
};