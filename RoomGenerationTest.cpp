#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define SEED 1234

std::mt19937 Rng(SEED);

struct Pos
{
    int x, y;
};

enum class TileType
{
    BasicFloor = 0,
    BasicWall = 1,
    Water = 2
};

class RoomGrid 
{
    private:
    std::vector<std::vector<TileType>> Grid;
    
    public:
    int Width, Height;

    RoomGrid(int w, int h)
    {
        Width = w;
        Height = h;
        Grid = std::vector(w, std::vector(h, TileType::BasicFloor));
    }

    bool TryPathfind(const Pos& start, const Pos& end, const std::vector<TileType> walkableTiles)
    {
        using namespace std;
        vector<Pos> possibleTiles(1, start);

        vector<vector<char>> walkedGrid(Width, vector<char>(Height, 0));

        while(1)
        {
            std::vector<Pos> newTiles;
            for_each(possibleTiles.begin(), possibleTiles.end(),
            [&newTiles, &walkedGrid, walkableTiles, this](Pos pos)
            {
                if(
                    !walkedGrid[pos.x + 1][pos.y + 1] &&
                    any_of(walkableTiles.begin(), walkableTiles.end(), [pos, this](TileType t)
                    {
                        TileType tile = Grid[pos.x + 1][pos.y + 1];
                        return t == tile;
                    }))
                {
                    walkedGrid[pos.x + 1][pos.y + 1] = 1;
                    newTiles.push_back({pos.x + 1, pos.y + 1});
                }else
                {
                    walkedGrid[pos.x + 1][pos.y + 1] = -1;
                }
                if(
                    !walkedGrid[pos.x - 1][pos.y + 1] &&
                    any_of(walkableTiles.begin(), walkableTiles.end(), [pos, this](TileType t)
                    {
                        TileType tile = Grid[pos.x - 1][pos.y + 1];
                        return t == tile;
                    }))
                {
                    walkedGrid[pos.x - 1][pos.y + 1] = 1;
                    newTiles.push_back({pos.x - 1, pos.y + 1});
                }else
                {
                    walkedGrid[pos.x - 1][pos.y + 1] = -1;
                }
                if(
                    !walkedGrid[pos.x + 1][pos.y - 1] &&
                    any_of(walkableTiles.begin(), walkableTiles.end(), [pos, this](TileType t)
                    {
                        TileType tile = Grid[pos.x + 1][pos.y - 1];
                        return t == tile;
                    }))
                {
                    walkedGrid[pos.x + 1][pos.y - 1] = 1;
                    newTiles.push_back({pos.x + 1, pos.y - 1});
                }else
                {
                    walkedGrid[pos.x + 1][pos.y - 1] = -1;
                }
                if(
                    !walkedGrid[pos.x - 1][pos.y - 1] &&
                    any_of(walkableTiles.begin(), walkableTiles.end(), [pos, this](TileType t)
                    {
                        TileType tile = Grid[pos.x - 1][pos.y - 1];
                        return t == tile;
                    }))
                {
                    walkedGrid[pos.x - 1][pos.y - 1] = 1;
                    newTiles.push_back({pos.x - 1, pos.y - 1});
                }else
                {
                    walkedGrid[pos.x - 1][pos.y - 1] = -1;
                }
            });

            possibleTiles = std::move(newTiles);

            if(walkedGrid[end.x][end.y] == 1){return true;}
            if(possibleTiles.size() == 0){return false;}
        }
    }
};

class Room
{

};

int main()
{

}