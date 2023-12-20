#pragma once

#include "CS.h"
#include "Pipe.h"
#include "header.h"



using namespace std;


template <typename T>
void ViewComponents(unordered_map<int, T>& map);


template <typename T>
map<int, int> Create_Console_Map(const unordered_map<int, T>& conteiner);

void View(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations);


void EditPipeline(unordered_map<int, Pipe>& pipes);


void EditCopressorStation(unordered_map<int, CS>& stations);


void SaveConfiguration(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations);


void LoadConfiguration(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations);


void SearchPipes(unordered_map<int, Pipe>& pipes);


void SearchCS(unordered_map<int, CS>& stations);