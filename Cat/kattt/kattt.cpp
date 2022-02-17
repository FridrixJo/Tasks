#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ifstream fin;
std::ofstream fout("output.txt");

void getData(std::vector<std::string> &strVec) {
    bool status = true;
    while (status) {
        if (fin.eof()) {
            status = false;
            break;
        }
        std::string temp = "";
        std::getline(fin, temp);
        strVec.push_back(temp);
    }
}

int checkFirstSpace(std::string s) {
    int k = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] > ' ') {
            return k;
        }else {
            k++;
        }
    }
    return k;
}

int checkLastSpace(std::string s) {
    int k = 0;
    for (int i = s.size() - 1; i > - 1; i--) {
        if (s[i] > ' ') {
            return k;
        }
        else {
            k++;
        }
    }
    return k;
}




void deleteFirstAndLastSpaces(std::vector<std::string>& strVec) {
    for (int i = 0; i < strVec.size(); i++) {
        for (int j = 0; j < strVec.at(i).size(); j++) {
             
            if (checkFirstSpace(strVec.at(i))) {
                int k = checkFirstSpace(strVec.at(i));
                strVec.at(i).erase(0, k);
            }  

            if (checkLastSpace(strVec.at(i))) {
                int k = checkFirstSpace(strVec.at(j));
                strVec.at(i).erase(strVec.at(i).size() - 1 - k);
            }
    
        }
    }
}

void deleteBetweenSpaces(std::vector<std::string>& strVec) {
    for (int i = 0; i < strVec.size(); i++) {
        for (int j = 0; j < strVec.at(i).size() - 1; j++) {
            if (strVec.at(i)[j] == ' ' && strVec.at(i)[j + 1] == ' ') {
                for (int u = j; u < strVec.at(i).size() - 1; u++) {
                    std::swap(strVec.at(i)[u], strVec.at(i)[u + 1]);
                }
            }
        }
    }
}

int main()
{
    std::string s = "yae";
    std::swap(s[0], s[1]);
    std::cout << s <<"\n";
    bool status = false;
    fin.open("input.txt");
    if (fin.is_open()) {
        std::cout << "File was opened\n";
        status = true;
    }
    else {
        std::cout << "Try again\n";
    }
    std::vector<std::string> strVec;
    if (status) {
        
        getData(strVec);
    }

    deleteFirstAndLastSpaces(strVec);

    for (int i = 0; i < 10; i++) {
        deleteBetweenSpaces(strVec);
    }

    std::cout << "Result : \n";
    fout << "Result : \n";

    for (int i = 0; i < strVec.size(); i++) {
        std::cout << strVec.at(i) << "\n";
        fout << strVec.at(i) << "\n";;
    }

    return 0;
}

