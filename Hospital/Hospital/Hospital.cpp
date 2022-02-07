#include <iostream>
#include <fstream>
#include <typeinfo>

std::ifstream fin;
std::ofstream fout("output.txt");

class Patient {
public:
    std::string name;
    std::string sex;
    int age;
    std::string diagnosis;
    int number;
};

class PatientArr :public Patient {
private:
    Patient* arr;
    int size;
public:
    void openFile() {
        fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            std::cout << "Trying to open file ...\n";
            fin.open("input.txt");
            std::cout << "File was opened\n";
        }
        catch (const std::ifstream::failure& ex)
        {
            std::cout << ex.what() << "\n";
            std::cout << ex.code() << "\n";
            std::cout << "Error ...\n";
        }
    }

    void getData() {
        fin >> size;
        arr = new Patient[size];
        for (int i = 0; i < size; i++) {
            fin >> arr[i].name;
            fin >> arr[i].sex;
            fin >> arr[i].age;
            fin >> arr[i].diagnosis;
        }
        fin.close();
    }

    void print() {
        for (int i = 0; i < size; i++) {

            std::cout << i + 1 << " patient : " << "name - " << arr[i].name << "  sex - " << arr[i].sex << "  age - " << arr[i].age << "  diagnosis - " << arr[i].diagnosis << "  number - " << arr[i].number << "\n";
            fout << i + 1 << " patient : " << "name - " << arr[i].name << "  sex - " << arr[i].sex << "  age - " << arr[i].age << "  diagnosis - " << arr[i].diagnosis << "  number - " << arr[i].number << "\n";
        }
    }

    void getNumber() {
        for (int i = 0; i < size; i++) {
            arr[i].number = rand() % 100 + 1;
        }
    }

    void currectNumber() {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (arr[i].diagnosis == arr[j].diagnosis && arr[i].sex == arr[j].sex) {
                    arr[j].number = arr[i].number;
                }
            }
        }
    }

    void deletePatient(Patient*& arr,int &size, int &num) {

        Patient* newArr = new Patient[size - 1];

        for (int i = num - 1; i < size - 1; i++) {
            std::swap(arr[i], arr[i + 1]);
        }

        for (int i = 0; i < size - 1; i++) {
            newArr[i] = arr[i];
        }

        size--;

        delete[] arr;
        arr = newArr;
    }

    void deleteItem() {
        std::cout << "What patient you want to delete from your list?\n";
        int delPatient;
        std::cin >> delPatient;
        deletePatient(arr, size, delPatient);
    }

    void addPatient(Patient*& arr, int& size) {
        Patient* newArr = new Patient[size + 1];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        Patient item;

        std::cout << "Give us info about new patient\n";
        std::cout << "name - "; std::cin >> item.name;
        std::cout << "sex - "; std::cin >> item.sex;
        std::cout << "age - "; std::cin >> item.age;
        std::cout << "diagnosis - "; std::cin >> item.diagnosis;
        item.number = rand() % 100 + 1;

        newArr[size++] = item;

        delete[] arr;
        arr = newArr;
    }

    void addItem() {
        addPatient(arr, size);
        currectNumber();
    }

    void search(std::string str) {
        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i].name == str || arr[i].diagnosis == str) {
                std::cout << i + 1 << " patient : " << "name - " << arr[i].name << "  sex - " << arr[i].sex << "  age - " << arr[i].age << "  diagnosis - " << arr[i].diagnosis << "  number - " << arr[i].number << "\n";
                fout << i + 1 << " patient : " << "name - " << arr[i].name << "  sex - " << arr[i].sex << "  age - " << arr[i].age << "  diagnosis - " << arr[i].diagnosis << "  number - " << arr[i].number << "\n";
            }
            else {
                counter++;
            }
        }
        if (counter == size) {
            std::cout << "There is no one such patient\n";
            fout << "There is no one such patient\n";
        }
    }

    void search(int number) {
        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i].number == number) {
                std::cout << i + 1 << " patient : " << "name - " << arr[i].name << "  sex - " << arr[i].sex << "  age - " << arr[i].age << "  diagnosis - " << arr[i].diagnosis << "  number - " << arr[i].number << "\n";
                fout << i + 1 << " patient : " << "name - " << arr[i].name << "  sex - " << arr[i].sex << "  age - " << arr[i].age << "  diagnosis - " << arr[i].diagnosis << "  number - " << arr[i].number << "\n";
            }
            else {
                counter++;
            }
        }
        if (counter == size) {
            std::cout << "There is no one such patient\n";
            fout << "There is no one such patient\n";
        }
    }

};

int main()
{
    srand(time(NULL));
    PatientArr A;
    A.openFile();
    A.getData();
    A.getNumber();
    A.print();
    std::cout << "\n";
    fout << "Currecting numbers ...\n";
    A.currectNumber();
    A.print();

    fout << "Deleting element ...\n";
    A.deleteItem();
    A.print();

    fout << "Adding new element ...\n";
    A.addItem();
    A.print();

    Patient B;
    std::cout << "Give us info about patient you want to find\n";
    std::cout << "name - "; std::cin >> B.name;
    std::cout << "diagnosis - "; std::cin >> B.diagnosis;
    std::cout << "number - "; std::cin >> B.number;

    std::cout << "Searching by name " << B.name << " ...\n";
    fout << "Searching by name " << B.name << " ...\n";
    A.search(B.name);

    std::cout << "Searching by diagnosis " << B.diagnosis << " ...\n";
    fout << "Searching by diagnosis " << B.diagnosis << " ...\n";
    A.search(B.diagnosis);

    std::cout << "Searching by number " << B.number << " ...\n";
    fout << "Searching by number " << B.number << " ...\n";
    A.search(B.number);

    return 0;
}
