#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 
#include <string>

// Структура для представления трубы 
struct Pipe {
    std::string id;
    std::string name;
    double length;
    double diameter;
    bool inRepair;

    void readFromConsole() {
        std::cout << "Enter Pipe ID: ";
        std::cin >> id;
        std::cout << "Enter Pipe Name: ";
        std::cin >> name;
        std::cout << "Enter Pipe Length (in kilometers): ";
        std::cin >> length;
        std::cout << "Enter Pipe Diameter: ";
        std::cin >> diameter;
        std::cout << "Is the pipe under repair? (1 - yes, 0 - no): ";
        std::cin >> inRepair;
    }

    void printToConsole() {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Length (km): " << length << std::endl;
        std::cout << "Diameter: " << diameter << std::endl;
        std::cout << "Under repair: " << (inRepair ? "Yes" : "No") << std::endl;
    }
};

// Структура для представления КС 
struct CompressorStation {
    std::string id;
    std::string name;
    int workshopCount;
    int activeWorkshops;
    double efficiency;

    void readFromConsole() {
        std::cout << "Enter Compressor Station ID: ";
        std::cin >> id;
        std::cout << "Enter Compressor Station Name: ";
        std::cin >> name;
        std::cout << "Enter the number of workshops: ";
        std::cin >> workshopCount;
        std::cout << "Enter the number of active workshops: ";
        std::cin >> activeWorkshops;
        std::cout << "Enter the efficiency rating: ";
        std::cin >> efficiency;
    }

    void printToConsole() {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Number of Workshops: " << workshopCount << std::endl;
        std::cout << "Active Workshops: " << activeWorkshops << std::endl;
        std::cout << "Efficiency: " << efficiency << std::endl;
    }
};

// Функция для сохранения данных в файл 
void saveData(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& stations, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << pipes.size() << std::endl;
        for (const auto& pipe : pipes) {
            file << pipe.id << std::endl;
            file << pipe.name << std::endl;
            file << pipe.length << std::endl;
            file << pipe.diameter << std::endl;
            file << pipe.inRepair << std::endl;
        }

        file << stations.size() << std::endl;
        for (const auto& station : stations) {
            file << station.id << std::endl;
            file << station.name << std::endl;
            file << station.workshopCount << std::endl;
            file << station.activeWorkshops << std::endl;
            file << station.efficiency << std::endl;
        }

        file.close();
        std::cout << "Data saved to the file." << std::endl;
    }
    else {
        std::cout << "Failed to open the file for saving data." << std::endl;
    }
}

// Функция для загрузки данных из файла 
void loadData(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();

        int pipeCount;
        file >> pipeCount;
        file.ignore();

        for (int i = 0; i < pipeCount; ++i) {
            Pipe pipe;
            std::getline(file, pipe.id);
            std::getline(file, pipe.name);
            file >> pipe.length;
            file >> pipe.diameter;
            file >> pipe.inRepair;
            file.ignore();
            pipes.push_back(pipe);
        }

        int         stationCount;
        file >> stationCount;
        file.ignore();

        for (int i = 0; i < stationCount; ++i) {
            CompressorStation station;
            std::getline(file, station.id);
            std::getline(file, station.name);
            file >> station.workshopCount;
            file >> station.activeWorkshops;
            file >> station.efficiency;
            file.ignore();
            stations.push_back(station);
        }

        std::cout << "Data loaded from the file." << std::endl;
    }
    else {
        std::cout << "Failed to open the file for loading data." << std::endl;
    }
}

// Функция для поиска трубы по названию 
std::vector<Pipe> findPipesByName(const std::vector<Pipe>& pipes, const std::string& name) {
    std::vector<Pipe> foundPipes;
    for (const auto& pipe : pipes) {
        if (pipe.name == name) {
            foundPipes.push_back(pipe);
        }
    }
    return foundPipes;
}

// Функция для поиска трубы по признаку "в ремонте" 
std::vector<Pipe> findPipesInRepair(const std::vector<Pipe>& pipes, bool inRepair) {
    std::vector<Pipe> foundPipes;
    for (const auto& pipe : pipes) {
        if (pipe.inRepair == inRepair) {
            foundPipes.push_back(pipe);
        }
    }
    return foundPipes;
}

// Функция для поиска КС по названию 
std::vector<CompressorStation> findStationsByName(const std::vector<CompressorStation>& stations, const std::string& name) {
    std::vector<CompressorStation> foundStations;
    for (const auto& station : stations) {
        if (station.name == name) {
            foundStations.push_back(station);
        }
    }
    return foundStations;
}

// Функция для поиска КС по проценту незадействованных цехов 
std::vector<CompressorStation> findStationsByUnusedWorkshops(const std::vector<CompressorStation>& stations, double unusedPercentage) {
    std::vector<CompressorStation> foundStations;
    for (const auto& station : stations) {
        double unusedWorkshops = station.workshopCount - station.activeWorkshops;
        double percentage = (unusedWorkshops / station.workshopCount) * 100.0;
        if (percentage >= unusedPercentage) {
            foundStations.push_back(station);
        }
    }
    return foundStations;
}

// Функция для пакетного редактирования труб 
void editPipes(std::vector<Pipe>& pipes) {
    std::string name;
    std::cout << "Enter the name of the pipes for editing: ";
    std::cin >> name;

    std::vector<Pipe> foundPipes = findPipesByName(pipes, name);
    if (foundPipes.empty()) {
        std::cout << "Pipes with the specified name were not found." << std::endl;
        return;
    }

    int choice;
    std::cout << "Choose an action for editing:" << std::endl;
    std::cout << "1. Change length" << std::endl;
    std::cout << "2. Change diameter" << std::endl;
    std::cout << "3. Change repair status" << std::endl;
    std::cout << "4. Delete" << std::endl;
    std::cout << "Choose an action: ";
    std::cin >> choice;

    if (choice == 1) {
        double newLength;
        std::cout << "Enter the new length: ";
        std::cin >> newLength;

        for (auto& pipe : foundPipes) {
            pipe.length = newLength;
        }
    }
    else if (choice == 2) {
        double newDiameter;
        std::cout << "Enter the new diameter: ";
        std::cin >> newDiameter;

        for (auto& pipe : foundPipes) {
            pipe.diameter = newDiameter;
        }
    }
    else if (choice == 3) {
        bool newInRepair;
        std::cout << "Is the pipe under repair? (1 - yes, 0 - no): ";

        std::cout << "Is the pipe under repair? (1 - yes, 0 - no): ";
        std::cin >> newInRepair;

        for (auto& pipe : foundPipes) {
            pipe.inRepair = newInRepair;
        }
    }
    else if (choice == 4) {
        // Удалить найденные трубы 
        pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [&name](const Pipe& pipe) { return pipe.name == name; }), pipes.end());
    }
    else {
        std::cout << "Wrong choise." << std::endl;
    }
}

int main() {
    std::vector<Pipe> pipes;
    std::vector<CompressorStation> stations;

    int choice;
    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add pipe" << std::endl;
        std::cout << "2. Add compressor station" << std::endl;
        std::cout << "3. View all objects" << std::endl;
        std::cout << "4. Edit pipe" << std::endl;
        std::cout << "5. Edit compressor station" << std::endl;
        std::cout << "6. Save" << std::endl;
        std::cout << "7. Load" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an action: ";
        std::cin >> choice;

        if (choice == 1) {
            Pipe pipe;
            pipe.readFromConsole();
            pipes.push_back(pipe);
        }
        else if (choice == 2) {
            CompressorStation station;
            station.readFromConsole();
            stations.push_back(station);
        }
        else if (choice == 3) {
            // Вывод всех объектов 
            std::cout << "Pipes:" << std::endl;
            for (auto& pipe : pipes) {
                pipe.printToConsole();
                std::cout << std::endl;
            }

            std::cout << "Compressor Stations:" << std::endl;
            for (auto& station : stations) {
                station.printToConsole();
                std::cout << std::endl;
            }
        }
        else if (choice == 4) {
            editPipes(pipes);
        }
        else if (choice == 5) {
            // Редактирование КС 
            // Аналогично пакетному редактированию труб 
        }
        else if (choice == 6) {
            std::string filename;
            std::cout << "Enter the file name for saving: ";
            std::cin >> filename;
            saveData(pipes, stations, filename);
        }
        else if (choice == 7) {
            std::string filename;
            std::cout << "Enter the file name for loading: ";

            std::cin >> filename;
            loadData(pipes, stations, filename);
        }
        else if (choice == 0) {
            break;
        }
        else {
            std::cout << "Wrong choise" << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}