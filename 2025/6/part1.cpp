#include <iostream>
#include <fstream>
#include <vector>


void ope(long & n, const long to_add, std::string ope){
    if(ope=="+")
        n+=to_add;
    else if(ope=="-")
        n-=to_add;
    else if(ope=="*")
        n*=to_add;
}


long solve(const std::vector <std::string> & input){
    uint n_col = 0;
    int i=input.size()-1;
    while(input[i]=="+" or input[i]=="-" or input[i]=="*"){
        ++n_col;
        --i;
    }

    long answer=0;
    uint n_ligne = (input.size())/n_col;

    std::cout<<n_col<<" "<<n_ligne<<"\n";
    for(int j=0; j<n_col; ++j){
        long intermediate = std::stol(input[j]);
        for(int k=1; k<n_ligne-1; ++k){

            std::cout<<intermediate<<" "<<

            input[n_col*n_ligne - n_col +j]<<" "<<

            input[((n_col)*k)+(j)]<<std::endl;


            ope(intermediate,
                std::stol(input[((n_col)*k)+(j)]),
                input[n_col*n_ligne - n_col +j]);
        }
        //std::cout<<intermediate<<"\n";
        answer+=intermediate;
    }

    return answer;
}

int main(){
    std::string file_name = "input.txt";
    std::ifstream fic;
    fic.open(file_name);
    if(fic.is_open()){
        long answer = 0;
        std::vector <std::string> input;
        while(fic.good()){
            std::string ligne;
            fic>>ligne;
            input.push_back(ligne);
        }
        answer = solve(input);
        std::cout<<"The answer is : "<<answer<<"\n";

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}