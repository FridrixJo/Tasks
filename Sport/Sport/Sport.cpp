#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin;
std::ofstream fout("output.txt");

class Sportman {
public:
    std::string country;
    std::string team;
    std::string name;
    int number;
    int age;
    int height;
    int weight;
};

class SportTeam {
private:
    std::vector<Sportman> arr;
    int size;
public:
    enum Actions {
        SHOW = 1,
        ADD,
        DELETE,
        SEARCH,
        CHANGE,
        SORT,
        EXIT
    };

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
            std::cout << "Error!\n";
        }
    }

    void getDate() {
        fin >> size;
        arr.reserve(size);
        for (int i = 0; i < size; i++) {
            Sportman item;
            fin >> item.country;
            fin >> item.team;
            fin >> item.name;
            fin >> item.number;
            fin >> item.age;
            fin >> item.height;
            fin >> item.weight;
            arr.push_back(item);
        }
    }

    bool exception() {
        if (arr.size() > 0) {
            return true;
        }
        else {
            std::cout << "There is no one sportman in this list, add more or exit the program\n";
            fout << "There is no one sportman in this list, add more or exit the program\n";
            return false;
        }
    }

    void print() {
        if (exception()) {
            for (int i = 0; i < arr.size(); i++) {
                std::cout << i + 1 << " sportman : country - " << arr.at(i).country << " team - " << arr.at(i).team << " name - " << arr.at(i).name << " number - " << arr.at(i).number << " age - " << arr.at(i).age << " height - " << arr.at(i).height << " weight - " << arr.at(i).weight << "\n";
                fout << i + 1 << " sportman : country - " << arr.at(i).country << " team - " << arr.at(i).team << " name - " << arr.at(i).name << " number - " << arr.at(i).number << " age - " << arr.at(i).age << " height - " << arr.at(i).height << " weight - " << arr.at(i).weight << "\n";
            }
        }
    }

    void addSportman() {
        std::cout << "Info about new sportman : \n";
        Sportman man;
        std::cout << "country : "; std::cin >> man.country;
        std::cout << "team : "; std::cin >> man.team;
        std::cout << "name : "; std::cin >> man.name;
        std::cout << "number : "; std::cin >> man.number;
        std::cout << "age : "; std::cin >> man.age;
        std::cout << "height : "; std::cin >> man.height;
        std::cout << "weight : "; std::cin >> man.weight;
        arr.push_back(man);

        print();
    }

    void deleteSportman() {
        if (exception()) {
            std::cout << "Choose sportman you want to delete from this list ...\n";
            fout << "Choose sportman you want to delete from this list ...\n";
            int num;
            std::cin >> num;
            if (num > arr.size()) {
                std::cout << "SWR! Try one more time ...\n";
                fout << "SWR! Try one more time ...\n";
                deleteSportman();
            }
            else {
                for (int i = num - 1; i < arr.size() - 1; i++) {
                    std::swap(arr.at(i), arr.at(i + 1));
                }
                arr.pop_back();
                print();
            }
        }
    }

    std::string convert(int a) {
        std::string s = "";
        std::vector<int> v;
        while (a) {
            v.push_back(a % 10);
            a /= 10;
        }

        std::reverse(v.begin(), v.end());

        for (int i = 0; i < v.size(); i++) {
            s.push_back(static_cast<char>(v.at(i) + 48));
        }
        
        return s;
    }

    int convert(std::string s) {
        std::vector<int> v;
        for (int i = 0; i < s.size(); i++) {
            v.push_back(static_cast<int>(s[i] - 48));
        }

        int num = 0;
        int k = 0;
        for (int i = v.size() - 1; i > - 1; i--) {
            num += v.at(i) * std::pow(10, k++);
        }

        return num;
    }

    void search() {
        if (exception()) {
            std::cout << "Write element of sportman for searching : ";
            fout << "Write element of sportman for searching : ";
            std::string s;
            std::cin >> s;
            fout << s << "\n";

            int counter = 0;
            for (int i = 0; i < arr.size(); i++) {
                if (s == arr.at(i).country || s == arr.at(i).team || s == arr.at(i).name || s == convert(arr.at(i).number) || s == convert(arr.at(i).age) || s == convert(arr.at(i).weight) || s == convert(arr.at(i).height)) {
                    counter++;
                    std::cout << counter << " sportman : country - " << arr.at(i).country << " team - " << arr.at(i).team << " name - " << arr.at(i).name << " number - " << arr.at(i).number << " age - " << arr.at(i).age << " height - " << arr.at(i).height << " weight - " << arr.at(i).weight << "\n";
                    fout << counter << " sportman : country - " << arr.at(i).country << " team - " << arr.at(i).team << " name - " << arr.at(i).name << " number - " << arr.at(i).number << " age - " << arr.at(i).age << " height - " << arr.at(i).height << " weight - " << arr.at(i).weight << "\n";
                }
            }
            if (!counter) {
                std::cout << "There is no one sportman with such element ...\n";
                fout << "There is no one sportman with such element ...\n";
            }
        }
    }  

    void changeElement() {
        if (exception()) {
            std::cout << "Write element you want to change : ";
            fout << "Write element you want to change : ";
            std::string s;
            std::cin >> s;
            fout << s << "\n";
            bool status = false;

            for (int i = 0; i < arr.size(); i++) {
                if (s == arr.at(i).country || s == arr.at(i).team || s == arr.at(i).name || s == convert(arr.at(i).number) || s == convert(arr.at(i).age) || s == convert(arr.at(i).weight) || s == convert(arr.at(i).height)) {
                    status = true;
                    std::cout << "Write your new element for " << i + 1 << " sportman : ";
                    fout << "Write your new element for " << i + 1 << " sportman : ";
                    std::string newStr = "";
                    std::cin >> newStr;
                    fout << newStr << "\n";

                    if (s == arr.at(i).country) { arr.at(i).country = newStr; continue; }
                    if (s == arr.at(i).team) { arr.at(i).team = newStr; continue; }
                    if (s == arr.at(i).name) { arr.at(i).name = newStr; continue; }
                    if (s == convert(arr.at(i).number)) { arr.at(i).number = convert(newStr); continue; }
                    if (s == convert(arr.at(i).age)) { arr.at(i).age = convert(newStr); continue; }
                    if (s == convert(arr.at(i).height)) { arr.at(i).height = convert(newStr); continue; }
                    if (s == convert(arr.at(i).weight)) { arr.at(i).weight = convert(newStr); continue; }
                }
            }

            if (!status) {
                std::cout << "There is no one sportman with such element ...\n";
                fout << "There is no one sportman with such element ...\n";
            }
            else {
                print();
            }
        }     
    }

    void sort() {
        if (exception()) {
            std::vector<Sportman> newArr;
            bool status = false;

            for (int i = 0; i < arr.size(); i++) {
                if (arr.at(i).age > 20) {
                    status = true;
                    newArr.push_back(arr.at(i));
                }
            }

            if (status) {
                for (int i = 0; i < newArr.size() - 1; i++) {
                    for (int j = 0; j < newArr.size() - i - 1; j++) {
                        if (newArr.at(j).age > newArr.at(j + 1).age) {
                            std::swap(newArr.at(j), newArr.at(j + 1));
                        }
                    }
                }

                for (int i = 0; i < newArr.size(); i++) {
                    std::cout << i + 1 << " sportman : country - " << newArr.at(i).country << " team - " << newArr.at(i).team << " name - " << newArr.at(i).name << " number - " << newArr.at(i).number << " age - " << newArr.at(i).age << " height - " << newArr.at(i).height << " weight - " << newArr.at(i).weight << "\n";
                    fout << i + 1 << " sportman : country - " << newArr.at(i).country << " team - " << newArr.at(i).team << " name - " << newArr.at(i).name << " number - " << newArr.at(i).number << " age - " << newArr.at(i).age << " height - " << newArr.at(i).height << " weight - " << newArr.at(i).weight << "\n";
                }
            }
        }
    }

    void menu() {
        bool status = true;
        openFile();
        getDate();
        while (status) {
            std::cout << "What you want to do? ...\n";
            std::cout << "1. Show all info about sportmen\n";
            std::cout << "2. Add one more sportman\n";
            std::cout << "3. Delete sportman\n";
            std::cout << "4. Search sportman/sportmen by individual parameters\n";
            std::cout << "5. Change parameter/parameters of sportman/sportmen\n";
            std::cout << "6. Sort ascending list of sportmen (sportmen which are elder than 20)\n";
            std::cout << "7. Exit the program\n";

            fout << "What you want to do? ...\n";
            fout << "1. Show all info about sportmen\n";
            fout << "2. Add one more sportman\n";
            fout << "3. Delete sportman\n";
            fout << "4. Search sportman/sportmen by individual parameters\n";
            fout << "5. Change parameter/parameters of sportman/sportmen\n";
            fout << "6. Sort ascending list of sportmen (sportmen which are elder than 20)\n";
            fout << "7. Exit the program\n";

            int var;
            std::cout << "Your choice : ";
            fout << "Your choice : ";
            std::cin >> var;
            fout << var << "\n";

            switch (var)
            {
            case Actions::SHOW:
                print();
                break;
            case Actions::ADD:
                addSportman();
                break;
            case Actions::DELETE:
                deleteSportman();
                break;
            case Actions::SEARCH:
                search();
                break;
            case Actions::CHANGE:
                changeElement();
                break;
            case Actions::SORT:
                sort();
                break;
            case Actions::EXIT:
                std::cout << "Thanks for using my program , see you ...\n";
                fout << "Thanks for using my program , see you ...\n";
                status = false;
                break;
            default:
                std::cout << "SWR! Try one more time ...\n";
                fout << "SWR! Try one more time ...\n";
                break;
            }

        }
    }

};


int main()
{
    SportTeam A;
    A.menu();

    return 0;
}
