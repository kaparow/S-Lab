#include "Pipe.h"

int Pipe::MaxId = 0;

Pipe::Pipe() {
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repairing = 0;
    ID = ++MaxId;
}

Pipe::Pipe(string name, double length, int diameter, bool in_repairing) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repairing = in_repairing;
}

void Pipe::InputPipeInfo() {
    cout << "Введите название трубы: ";
    cin.ignore(INT_MAX, '\n');
    getline(cin, name);

    cout << "Введите длину трубы: ";
    length = CorrectNumber(0.0, DBL_MAX);

    cout << "Введите диаметр трубы: ";
    diameter = CorrectNumber(0, INT_MAX);

    cout << "Выберите состояние трубы(0 - в ремонте, 1 - В эксплуатации): " << endl;
    in_repairing = CorrectNumber(0, 1);
}

void Pipe::PrintInfo() {
    cout << "Название: " << name << endl;
    cout << "Длина: " << length << endl;
    cout << "Диаметр: " << diameter << endl;
    cout << "Состояние(0 - в ремонте, 1 - в эксплуатации): " << (in_repairing) << endl;
    cout << "ID" << ID << endl;
}

void Pipe::Edit(const int answer) {
    if (answer) in_repairing = true;
    else in_repairing = false;
}

void Pipe::editInRepairStatus()
{
    PrintInfo();
    cout << "Введите состояние трубы(0 - в ремонте, 1 - в эксплуатации):" << endl;
    Edit(CorrectNumber(0, 1));
}


ostream& operator << (ostream& out, const Pipe& pipe)
{

    return out;
}
istream& operator >> (istream& in, Pipe& pipe)
{
    return in;
}

ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_repairing << endl;
        file << pipe.ID << endl;
    }
    return file;
}

ifstream& operator >> (ifstream& file, Pipe& pipe) {
    if (file.is_open()) {
        file >> pipe.name;
        file >> pipe.length;
        file >> pipe.diameter;
        file >> pipe.in_repairing;
        file >> pipe.ID;
    }
    return file;
}