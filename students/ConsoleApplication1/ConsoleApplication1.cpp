#include <fstream>
#include <iostream>
#include <string>

std::ifstream fin;
std::ofstream fout("output.txt");

class Student {
public:
    std::string name;
    int year;
    double reating;
};

class Stud :public Student {
private:
    Student* arr;
    int size;
public:

    void openFile() {
        fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            std::cout << "Trying to open fail ...\n";
            fin.open("input.txt");
            std::cout << "File was opened\n";
        }
        catch (const std::ifstream::failure ex)
        {
            std::cout << ex.what() << "\n";
            std::cout << ex.code() << "\n";
            std::cout << "Error\n";
        }
    }

    void getData() {
        fin >> size;
        arr = new Student[size];
        for (int i = 0; i < size; i++) {
            fin >> arr[i].name;
            fin >> arr[i].year;
            fin >> arr[i].reating;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {

            std::string line = "============\n";

            std::cout << line;
            fout << line;

            std::cout << arr[i].name << "\n";
            fout << arr[i].name << "\n";

            std::cout << arr[i].year << "\n";
            fout << arr[i].year << "\n";

            std::cout << arr[i].reating << "\n";
            fout << arr[i].reating << "\n";

            std::cout << line << "\n";
            fout << line << "\n";
        }
    }

    void sort(Student* arr, const int& size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[i + 1].name[0] < arr[i].name[0]) {
                    std::swap(arr[i], arr[i + 1]);
                }
            }
        }
    }

    void modSort(Student*& arr, int& size) {
        double averangeMark = 0;
        for (int i = 0; i < size; i++) {
            averangeMark += arr[i].reating;
        }
        averangeMark /= size;

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j + 1].reating > arr[j].reating) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }

        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (!(arr[i].reating > averangeMark)) {
                counter++;
            }
        }

        size -= counter;

        sort(arr, size);

        Student* newArr = new Student[size];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;

    }

    void getSort() {
        sort(arr, size);
    }

    void getModSort() {
        modSort(arr, size);
        std::cout << "ModSort\n";
    }

    ~Stud() {
        delete[] arr;
    }

};

int main()
{
    Stud A;
    A.openFile();
    A.getData();
    A.print();
    A.getSort();
    A.print();
    A.getModSort();
    A.print();

    fin.close();
    return 0;
}