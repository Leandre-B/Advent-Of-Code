#include <iostream>
#include <fstream>

int move(const char & direction, const int & dpl, int & cur){
    if(direction=='L')
        cur=((cur - dpl) %100 + 100)%100;
    else
        cur=((cur + dpl)%100);

    return cur;
}

void solve(const char & part, uint & password, const std::string & mouvement, int & cur){
    int dpl = std::stoi(mouvement.substr(1));

    if(part=='1'){
        cur = move(mouvement[0], dpl, cur);
        if(cur== 0)
            ++password;
    }else{ //part === 2
        for(int i=0; i<dpl; ++i){
            cur = move(mouvement[0], 1, cur);
            if(cur== 0)
                ++password;
        }
    }
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

            uint password = 0;
            int cur = 50;
            std::string mouvement;
            while(fic.good()){
                std::getline(fic, mouvement);
                
                solve(part, password, mouvement, cur);
            }

            std::cout<<"The password for part "<<part<<" is : "<<password<<"\n";
        }

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}