#include <iostream>
#include <fstream>
#include <vector>

struct FreshRange{
    long long start;
    long long end;
};


bool is_fresh(std::vector <FreshRange> & fresh_ranges, const long long & id){
    std::cout<<id<<std::endl;
    for(int i=0; i<fresh_ranges.size(); ++i){
        if(id>= fresh_ranges[i].start and id<=fresh_ranges[i].end){
            //std::cout<<fresh_ranges[i].start<<" "<<fresh_ranges[i].end<<" "<<id<<std::endl;
            return true;
        }
    }
    return false;
}

void check_overlap(std::vector <FreshRange> & fresh_ranges, FreshRange & range){
    if(fresh_ranges.size()==0)
        fresh_ranges.push_back(range);
    else{
        bool merge=true;
        while(merge){
            merge = false;
            int i=0;
            while(i<fresh_ranges.size()){

                //si on peut fusionner les intervalles
                if(!(range.start>fresh_ranges[i].end or
                range.end<fresh_ranges[i].start))
                {
                    range.start = std::min(fresh_ranges[i].start, range.start);
                    range.end = std::max(fresh_ranges[i].end, range.end);

                    fresh_ranges.erase(fresh_ranges.begin()+i);
                    merge = true;
                }else
                    ++i;
            }
        }
        fresh_ranges.push_back(range);
    }
}

long long numberOfFreshId(const std::vector <FreshRange> & fresh_ranges){
    long long answer=0;
    for(int i=0; i<fresh_ranges.size(); ++i){
        //std::cout<<fresh_ranges[i].start<<" "<<fresh_ranges[i].end<<std::endl;
        answer=(fresh_ranges[i].end - fresh_ranges[i].start +1) + answer;
    }
    return answer;
}


int main(){
    std::string file_name = "input.txt";
    std::ifstream fic;
    fic.open(file_name);
    if(fic.is_open()){
        std::vector <FreshRange> fresh_ranges;
        std::string str;
        //bool range = true;
        long long answer;
        while(fic.good()){
            std::getline(fic, str);
            if(str==""){
                fic.close();
            }else{
                uint dashIndex = str.find('-');
                FreshRange range;
                range.start = std::stoll(str.substr(0, dashIndex));
                range.end = std::stoll(str.substr(dashIndex+1, str.length()-dashIndex -1));

                check_overlap(fresh_ranges, range);
            }
        }

        answer = numberOfFreshId(fresh_ranges);
        std::cout<<"The answer is : "<<answer<<"\n";

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}

/* PART 1
std::getline(fic, str);
if(str==""){
    range=false;
}else{
    if(range){
        uint dashIndex = str.find('-');
        FreshRange range;
        range.start = std::stoll(str.substr(0, dashIndex));
        range.end = std::stoll(str.substr(dashIndex+1, str.length()-dashIndex -1));

        fresh_ranges.push_back(range);
    }else{
        if(is_fresh(fresh_ranges, std::stoll(str)))
            ++answer;*/
