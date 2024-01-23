#include <set>
#include <iostream>
#include <vector>
#include <random>

// Deals 4*num_disks random tiles from integers 0,...,99 without replacment
// then arranges them into d disks with 4 tiles each.
// The disks are described as vectors with five integer components
// where each component is the number of tiles on the disk
// of each of the five colors.
// Then detect duplicate disks with:
//  AzulDealer dealer(num_disks);
//  dealer.detectDups();
class AzulDealer {
public:
    int num_disks;
    std::vector<int> tiles;
    std::vector<std::vector<int>> disks;

    AzulDealer(int d) : num_disks(d), 
        disks(num_disks, std::vector<int>(5,0)),
        engine(time(0)) 
    {
        dealMethod();
        processDeal();
    }

    // Detects duplicate disks in the given dealt tiles
    bool detectDups() {
        std::set<std::vector<int>> diskTypes;
        for (std::vector<int> disk : disks) {
            if (diskTypes.find(disk) != diskTypes.end()) {
                return true;
            } else {
                diskTypes.insert(disk);
            }
        }
        return false;
    }

private:
    std::mt19937 engine;

    // Deals the tiles
    void dealMethod() {
        std::set<int> selected;
        std::uniform_int_distribution<> distr(0, 100);

        while (tiles.size() < 4*num_disks) {
            int number = distr(engine);

            if (selected.find(number) == selected.end()) {
                selected.insert(number);
                tiles.push_back(number);
            }
        }
    }

    // Processes the deal into disks
    void processDeal() {
        // Check if deal size is a multiple of 4
        if (tiles.size() % 4 != 0) {
            throw std::invalid_argument("Deal not multiple of 4!");
        }
    
        // The color of the tile is the remainder modulo 5
        for (size_t i = 0; i < tiles.size(); ++i) {
            int entry = tiles[i];
            disks[i/4][entry%5]++;
        }
    }
};



int main() {
    AzulDealer dealer(9);
    std::cout << dealer.detectDups();
    return 0;
}
