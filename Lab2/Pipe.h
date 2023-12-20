#pragma once
#include "header.h"

using namespace std;

class Pipe {
    double length;
    int diameter;


public:
    int ID;
    static int MaxId;

    string name;
    bool in_repairing;

    Pipe();
    Pipe(const string name, const double length, const int diameter, const bool in_repairing);

    void InputPipeInfo();

    void PrintInfo();

    void editInRepairStatus();

    void Edit(const int answer);

    friend ostream& operator << (ostream& out, const Pipe& pipe);
    friend istream& operator >> (istream& file, Pipe& pipe);

    friend ofstream& operator << (ofstream& out, const Pipe& pipe);
    friend ifstream& operator >> (ifstream& file, Pipe& pipe);
};