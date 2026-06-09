#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

struct Tile {
	int x;
	int y;
};


long long area(const Tile & A, const Tile & B) {
    return 1LL * (std::abs(A.x - B.x) + 1) * (std::abs(A.y - B.y) + 1);
}

int main() {

	std::vector<Tile> tiles;

	std::ifstream fic{"input.txt"};
	std::string ligne;
	while (std::getline(fic, ligne, ',')) {
		Tile t;
		t.x = std::stoi(ligne);
		std::getline(fic, ligne);
		t.y = std::stoi(ligne);
		tiles.push_back(t);
	}
	// for (Tile t : tiles) {
	// 	std::cout << t.x << ", " << t.y << "\n";
	// }

    // long long maxArea = 0;
	// for (unsigned int i = 0; i < tiles.size() - 1; ++i) {
	// 	for (unsigned int j = i + 1; j < tiles.size(); ++j) {
    //         long long cur_area = area(tiles[i], tiles[j]);
    //         if(cur_area>maxArea)
    //             maxArea = cur_area;
	// 	}
	// }
    // std::cout<<maxArea<<"\n";

	long long maxArea = 0;
	std::map<long, std::vector<std::array<Tile, 2>>> lignes;
	std::map<long, std::vector<std::array<Tile, 2>>> colonnes;
	for (unsigned int i = 0; i < tiles.size() - 1; ++i) {
			for (unsigned int j = i + 1; j < tiles.size(); ++j) {
				if(tiles[i].x==tiles[j].x){
					colonnes[tiles[i].x].push_back({tiles[i], tiles[j]});
				}else{ //.y==.y
					lignes[tiles[i].y].push_back({tiles[i], tiles[j]});
				}
			}
		}

	for (unsigned int i = 0; i < tiles.size() - 1; ++i) {
		for (unsigned int j = i + 1; j < tiles.size(); ++j) {
            bool out = false;

			long minX = std::min(tiles[i].x, tiles[j].x);
			long minY = std::min(tiles[i].y, tiles[j].y);
			long maxX = std::max(tiles[i].x, tiles[j].x);
			long maxY = std::max(tiles[i].y, tiles[j].y);

			for(int l=minX; l<maxX && !out; ++l){
				if(colonnes.find(l) != colonnes.end()){
					for(std::array<Tile, 2> c : colonnes[l]){
						if(	(minY >= std::min(c[0].y, c[1].y ) &&
							 minY <= std::max(c[0].y, c[1].y ) ) or
							(maxY <= std::min(c[0].y, c[1].y ) &&
							 maxY >= std::max(c[0].y, c[1].y ) )
						){
							out = true;
						}
					}
				}
			}

			for(int l=minY; l<maxY && !out; ++l){
				if(lignes.find(l) != lignes.end()){
					for(std::array<Tile, 2> c : lignes[l]){
						if(	(minX <= std::min(c[0].x, c[1].x ) &&
							 minX >= std::max(c[0].x, c[1].x ) ) or
							(maxX <= std::min(c[0].x, c[1].x ) &&
							 maxX >= std::max(c[0].x, c[1].x ) )
						){
							out = true;
						}
					}
				}
			}


			if(!out)
				maxArea = std::max(area(tiles[i], tiles[j]), maxArea);
			
		}
	}
	std::cout<<maxArea<<"\n";



	int a = 5;
	int c = a = a + 2;
	c = a = 2;




    
}




