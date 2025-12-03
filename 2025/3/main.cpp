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
    std::cout<<sol<<"\n";
    return (std::stoi(sol));
}

uint maxIndex(const std::string & str){
    uint max = 0;
    for(int i=1; i<str.length()-1; ++i){
        if(str[max]<str[i])
            max = i;
    }
    return max;
}

uint largestJoltagePart2(const std::string & bank){
    std::string sol ="";
    uint max_index = 0;
    for(int i=11; i<=0; ++i){
        max_index = maxIndex(std::substr(max_index, bank.length()-i))
        sol+= bank[max_index];
    }
    std::cout<<sol<<"\n";
    return (std::stoi(sol));
}

int main(){
    std::string file_name = "input.txt";
    std::ifstream fic;
    fic.open(file_name);
    if(fic.is_open()){
        char part;
        std::cout<<"What part do you want to solve ? ";
        std::cin>>part;
        if(part!='1' and part!='2')
            std::cout<<"Invalide, enter a proper part value !\n";
        else{
            std::string bank;
            uint answer = 0;

            while(fic.good()){
                std::getline(fic, bank);
                std::cout<<bank<<"\n";
                answer += largestJoltagePart2(bank);
            }

            std::cout<<"The answer for part "<<part<<" is : "<<answer<<"\n";
        }

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}
