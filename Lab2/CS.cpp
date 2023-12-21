#include "CS.h"

using namespace std;

CS::CS() {
    name = "Non";
    number_of_workshops = 0;
    workshops_in_operation = 0;
    effectiveness = 0;
    ID = ++MaxId;
}

CS::CS(string name, int number_of_workshops, int workshops_in_operation, int effectiveness) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->workshops_in_operation = workshops_in_operation;
    this->effectiveness = effectiveness;
}

void CS::InputInfo() {

    cout << "Введите название КС: ";
    name = input_string(cin);

    cout << "Введите количество цехов КС: ";
    number_of_workshops = CorrectNumber(cin, 0, 50);

    cout << "Введите количество цехов в работе: ";
    workshops_in_operation = CorrectNumber(cin, 0, number_of_workshops);

    cout << "Укажите эффективность(1,2,3)" << endl;
    effectiveness = CorrectNumber(cin, 1, 3);
}


void CS::PrintInfo() {

    cout << "КС: " << name << endl;
    cout << "Количество цехов: " << number_of_workshops << endl;
    cout << "Количество цехов в работе: " << workshops_in_operation << endl;
    cout << "Эффективность: " << effectiveness << endl;
    cout << "ID" << ID << endl;
}

void CS::Edit(int active) {
    workshops_in_operation = active;
}


void CS::Edit()
{

    PrintInfo();
    cout << "Изменить количество цехов в работе:" << endl;
    int answer = CorrectNumber(cin, 0, number_of_workshops);
    Edit(answer);
}

ofstream& operator << (ofstream& file, const CS& cs) {
    if (file.is_open()) {
        file << cs.name << endl;
        file << cs.number_of_workshops << endl;
        file << cs.workshops_in_operation << endl;
        file << cs.effectiveness << endl;
        file << cs.ID << endl;
    }
    return file;
}


ifstream& operator >> (ifstream& file, CS& cs) {
    if (file.is_open()) {
        file >> ws;
        getline(file, cs.name);
        file >> cs.number_of_workshops;
        file >> cs.workshops_in_operation;
        file >> cs.effectiveness;
        file >> cs.ID;

    }
    return file;
}