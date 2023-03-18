#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void graphBuild(std::unordered_map<char, std::unordered_set<int>> Q[], std::vector<int> &F,std::ifstream& f)
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
        Q[node1][letter].insert(node2);
    }
}

std::vector<int> result[1000];
int k = 0;
void depthSearch(std::unordered_map<char, std::unordered_set<int>> Q[],const std::vector<int> &F, std::vector<int> &path,std::unordered_set<int> currentState, int depth, std::string word)
{
    std::unordered_set<int> temp;
    // for(auto state: currentState)
    //     std::cout << state << " ";
    // std::cout << '\n';
    for(auto state: currentState)
    {
        temp.insert(Q[state][word[depth]].begin(),Q[state][word[depth]].end());
        path[depth] = state;
        if(depth <= word.length())
        {
            if(depth == word.length())
            {
                // std::cout << "depth: " << depth << " vector: ";
                // for(auto elem: path)
                //     std::cout << elem << " ";
                // std::cout << '\n';
                if(std::find(F.begin(), F.end(), path.back()) != F.end())
                    result[k++] = path;
            }
            else{
                // std::cout << "depth: " << depth << " vector: ";
                // for(auto elem: path)
                //     std::cout << elem << " ";
                // std::cout << '\n';
                depthSearch(Q, F, path, temp, depth+1, word);
            }
        temp.clear();
        }
    }
}

std::string testWord(std::unordered_map< char, std::unordered_set<int> > Q[], std::vector<int> &F, std::string word)
{
    std::unordered_set<int> currentState = {0};
    std::string temp = "0";
    for(auto letter: word)
    {
        std::unordered_set<int> temp2;
        for(auto state: currentState)
            temp2.insert(Q[state][letter].begin(), Q[state][letter].end());
        currentState = temp2;
    }
    for(auto state: currentState)
        if(std::find(F.begin(), F.end(), state) != F.end())
            return "Cuvantul este acceptat!";
    return "Cuvantul nu este acceptat!";
}

/*
contor pt cate path-uri ai deschise..
cand dai de o litera prin care nu ai path inchizi vectorul ( Ai un bool care retine daca a fost inchis vreun vector)
daca un vector a fost inchis reordonezi vectorii astfel incat sa fie in memorie continua
*/

int main()
{
    std::vector<int> F, path;
    std::unordered_map<char, std::unordered_set<int>> Q[20];
    // std::unordered_set<int> initialState;
    std::ifstream f1("limbaj1.txt");
    std::ifstream f2("cuvinte2.txt");
    std::string b;

    graphBuild(Q, F, f1);
    int nrStates = 0;
    while(!Q[nrStates].empty())
        nrStates++;
    int i = 0;
    while(std::getline(f2, b))
    {
        // initialState.insert(Q[0][b[0]].begin(),Q[0][b[0]].end());
        path.assign(b.length()+1, -1);
        std::cout << "Pentru cuvantul: " << b << '\n';
        depthSearch(Q, F, path, {0}, 0, b);
        while(!result[i].empty())
        {   
            for(auto elem: result[i])
                std:: cout << elem << " ";
            std::cout << '\n';
            i++;
        }
    }
    return 0;
}
    
    // for(int i = 0; i <= 3; ++i)
    // {
    //     for(auto pair: Q[i])
    //     {
    //         std::cout << pair.first << " ";
    //         for(auto elem: pair.second)
    //             std::cout << elem << " ";
    //         std::cout << '\n';
    //     }
    //     std::cout << '\n';
    // }