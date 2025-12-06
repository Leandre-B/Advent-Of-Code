#include <iostream>
#include <fstream>
#include <vector>



void calcul(long & n, const long to_add, char ope){
    if(ope=='+')
        n+=to_add;
    else if(ope=='-')
        n-=to_add;
    else if(ope=='*')
        n*=to_add;
}

int main(){
    std::ifstream fic {"input.txt"};
    std::vector<std::string> lignes;

    std::string ligne;
    while (std::getline(fic, ligne))
    {
        lignes.push_back((ligne));
    }


    //on créer un vector d'opérations
    std::vector<char> operations;
    for(int i=0; i<lignes[lignes.size()-1].length(); ++i){
        char c =lignes[lignes.size()-1][i];
        if(c=='+' or c=='-' or c=='*')
            operations.push_back(c);
    }


    //on check la longueur de la plus grande ligne
    uint most_long_line = 0;
    for(int i=0; i<lignes.size()-1; ++i){
        uint size =lignes[i].length();
        most_long_line = std::max(most_long_line, size);
    }

    //on complete les lignes avec des espaces
    for(int i=0; i<lignes.size()-1; ++i){
        if(lignes[i].length()<most_long_line){
            for(uint j=lignes[i].length(); j<most_long_line; ++j)
                lignes[i]+=" ";
        }
    }

    long answer=0;

    uint index_ope = operations.size() -1;
    long intermediate;
    if(operations[index_ope]=='*')
        intermediate = 1;
    else
        intermediate =0;

    for(int x=most_long_line-1; x>=0; --x){
        std::string num="";
        for(int y=0; y<lignes.size()-1; ++y){
            //std::cout<<lignes[y][x];
            num+=lignes[y][x];
        }
        bool space = true;
        for(int i=0; i<num.length(); ++i){
            if(num[i]!=' ')
                space = false;
        }
        if(space){
            --index_ope;
            std::cout<<intermediate<<"\n";
            answer+=intermediate;
            if(operations[index_ope]=='*')
                intermediate = 1;
            else
                intermediate =0;
        }else{
            std::cout<<intermediate<<" "<<operations[index_ope]<<" "<<std::stoll(num)<<std::endl;
            calcul(intermediate, std::stoll(num), operations[index_ope]);
        }
    }

    std::cout<<answer+intermediate<<"\n";

    return 0;
}
