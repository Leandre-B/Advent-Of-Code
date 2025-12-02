#include <iostream>
#include <fstream>


/*
 i -> size of pattern we're looking for in str
    so str[0...i[ is a pattern
    
 j -> start of the index of str where we're checking is the pattern exist
*/
long long existPatern(const std::string & str){
    for(int i=1; i<=str.length()/2; ++i){
        //if a pattern is possible (i * number of patterns == str.length())
        if(str.length()%i==0){
            std::string pattern = str.substr(0,i);
            bool is_pattern = true;
            int j=i;
            while(j<=str.length()-i and is_pattern){
                /*
                 I misunderstood part1 and did it as part2
                 but I write by mistake 'pattern!= str.substr(j,j+i)'
                 and this gave me the good awnser for part1 LOL.
                 So i was confused when part2 ask me for something I tought
                 I already did + the fact that it work for part1 but that it
                 "shoudln't have to".....
                 
                 So  part1  works for 'pattern!= str.substr(j,j+i))'
                 and part2  works for 'pattern!= str.substr(j,  i))'
                */
                if(pattern!= str.substr(j,i))
                    is_pattern = false;
                j+=i;
            }
            if(is_pattern){
                //std::cout<<std::stoll(str)<<"\n";
                return std::stoll(str);
            }
        }
    }
    return 0;
}

void getInvalidId(const std::string & start,
                  const std::string & end,
                  long long & answer)
{
    long long s = std::stoll(start);
    long long e = std::stoll(end);

    for(long long i=s; i<=e; ++i)
        answer+=existPatern(std::to_string(i));
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
            char dummy;
            std::string start, end;
            long long answer = 0;

            while(fic.good()){
                std::getline(fic, start, '-');
                std::getline(fic, end, ',');
                //std::cout<<start<<"-"<<end<<"\n";
                getInvalidId(start, end, answer);
            }

            std::cout<<"The answer for part "<<part<<" is : "<<answer<<"\n";
        }

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}