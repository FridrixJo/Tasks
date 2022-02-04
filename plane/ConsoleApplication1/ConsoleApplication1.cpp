#include <fstream>
#include <iostream>
#include <string>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

class Plane {
public:
    std::string point;
    int id;
    std::string surname;
    int time;
};

class Info: public Plane {
private:
    int size;
    Plane* arr;
public:
    void getData() {
        fin >> size;
        arr = new Plane[size];
        for (int i = 0; i < size; i++) {
                fin >> arr[i].point;
                fin >> arr[i].id;
                fin >> arr[i].surname;
                fin >> arr[i].time;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::string equelline = "==============\n";

            std::cout << equelline;
            fout << equelline;

            std::cout << arr[i].point << "\n";
            fout << arr[i].point << "\n";

            std::cout << arr[i].id << "\n";
            fout << arr[i].id << "\n";

            std::cout << arr[i].surname << "\n";
            fout << arr[i].surname << "\n";

            std::cout << arr[i].time <<  "\n";
            fout << arr[i].time << "\n";

            std::cout << equelline << "\n";
            fout << equelline << "\n";
        }
    }

    void addInfo(Plane *&arr,int& size) {
        Plane* newArr = new Plane[size + 1];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        Plane item;
        newArr[size] = item;

        std::cout << "point: ";
        std::cin >> newArr[size].point;
        std::cout << "id: ";
        std::cin >> newArr[size].id;
        std::cout << "surname: ";
        std::cin >> newArr[size].surname;
        std::cout << "time: ";
        std::cin >> newArr[size].time;

        size++;

        delete[] arr;
        arr = newArr;
    }

    void deleteInfo(Plane*& arr, int& size) {
        std::cout << size << " requests\n";
        std::cout<<"Which one you want to delete\n";
        int k;
        std::cin >> k;
        for (int i = k - 1; i < size - 1; i++) {
            std::swap(arr[i], arr[i + 1]);
        }

        Plane* newArr = new Plane[size - 1];
        for (int i = 0; i < size - 1; i++) {
            newArr[i] = arr[i];
        }

        size--;

        delete[] arr;
        arr = newArr;
    }

    void outputModAddedInfo() {
        addInfo(arr, size);
    }

    void outputModDeletedInfo() {
        deleteInfo(arr, size);
    }

};

int main()
{
    if (!fin.is_open()) {
        std::cout << "Error!\n";
    }
    else {
        std::cout << "File was opened\n";
    }

    Info A;
    A.getData();
    A.print();
    A.outputModAddedInfo();
    A.print();
    A.outputModDeletedInfo();
    A.print();

    fin.close();

    return 0;
}
