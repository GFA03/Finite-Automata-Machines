#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <vector>

void graphBuild(std::unordered_map<char, int> Q[], std::vector<int> &F,std::ifstream& f)
{
    int temp, node1, node2;
    char letter;
    std::string s;
    std::getline(f, s);
    std::stringstream ss(s);
    while(ss >> temp)
        F.push_back(temp);
    while(f)
    {   
        f >> node1;
        f >> letter;
        f >> node2;
        Q[node1][letter] = node2;
    }
}

std::string testWord(std::unordered_map<char, int> Q[], std::vector<int> &F, std::string word)
{
    int currentState = 0;
    std::string temp = "0";
    for(auto letter: word)
    {
        currentState = Q[currentState][letter];
        temp = temp + " " + std::to_string(currentState);
    }
    if(std::find(F.begin(), F.end(), currentState) != F.end())
        return temp;
    return "Cuvantul nu este acceptat!";
}

int main()
{
    std::vector<int> F;
    std::unordered_map<char, int> Q[20];
    std::ifstream f1("limbaj1.txt");
    std::ifstream f2("cuvinte1.txt");
    std::string b;
    graphBuild(Q, F, f1);
    while(std::getline(f2, b))
    {
        std::cout << "Pentru cuvantul: " << b << " " << testWord(Q, F, b) << '\n';
    }
    // std::cout << testWord(Q, F, b);
    return 0;
}
    