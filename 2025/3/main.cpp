#include <fstream>
#include <iostream>


uint largestJoltagePart1(const std::string & bank){
    char first_max = bank[0];
    char second_max = bank[1];

    for(int i=1; i<bank.length()-1; ++i){
        if(first_max<bank[i]){
            first_max = bank[i];
            second_max = bank[i+1];
        }
        else if(second_max < bank[i+1])
            second_max = bank[i+1];
    }
    //opti : stoui ??
    std::string sol ="";
    sol+=first_max; sol+=second_max;
    std::cout<<"sol : "<<sol<<"\n";
    return (std::stoi(sol));
}

uint maxIndex(const std::string & str){
    uint max = 0;
    for(int i=1; i<str.length(); ++i){
        if(str[max]<str[i])
            max = i;
    }
    return max;
}

long long largestJoltagePart2(const std::string & bank){
    std::string sol ="";
    uint max_index = 0;
    std::string fenetre;
    for(uint i=12; i>0; --i){
        //std::cout<<"max index : "<<max_index<<"\n";
        if(i==12){
            fenetre = bank.substr(max_index, bank.length() -i -max_index +1);
            max_index = maxIndex(fenetre);
        }
        else{
            fenetre = bank.substr(max_index+1, bank.length() -i -max_index);
            max_index = maxIndex(fenetre)+max_index+1;
        }
        sol+= bank[max_index];
        std::cout<<"fenetre : "<<fenetre<<"\n";
    }
    std::cout<<"sol : \""<<sol<<"\"\n";
    return (std::stoll(sol));
}

int main(){
    std::string file_name = "input.txt";
    std::ifstream fic;
    fic.open(file_name);
    if(fic.is_open()){
        std::string bank;
        long long answer = 0;

        while(fic.good()){
            std::getline(fic, bank);
            //std::cout<<bank<<"\n";
            answer += largestJoltagePart2(bank);
        }

        std::cout<<"The answer is : "<<answer<<"\n";

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}
