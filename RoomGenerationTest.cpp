#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define SEED 1234

using int64 = long long;

std::mt19937 Rng(SEED);

struct Pos
{
    int x, y;
};

enum class TileType
{
    Void = 0,
    BasicFloor = 1,
    BasicWall = 2,
    Entrance = 3
};

class RoomGrid
{
    public:
    std::vector<std::vector<TileType>> Grid;
    
    int Width, Height;

    RoomGrid(int w, int h)
    {
        Width = w;
        Height = h;
        Grid = std::vector(w, std::vector(h, TileType::Void));
    }

    void Print()
    {
        for(int i = 0; i < Grid.size(); ++i)
        {
            for(int j = 0; j < Grid[i].size(); ++j)
            {
                std::cout << '[' << (int)Grid[i][j] << ']';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void AddEntrance(const Pos& pos)
    {
        Grid[pos.x][pos.y] = TileType::Entrance;
    }

    bool IsTileValid(const Pos& pos, const std::vector<std::vector<char>>& walked)
    {
        return !(walked[pos.x][pos.y] || Grid[pos.x][pos.y] == TileType::Entrance || (pos.x <= 0 || pos.y <= 0 || pos.x >= Width - 1 || pos.y >= Height - 1));
    }

    void GetNeighborTiles(const Pos& pos, std::vector<Pos>& tiles, const std::vector<std::vector<char>>& walked)
    {
        Pos tile = {pos.x + 1, pos.y};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
        tile = {pos.x - 1, pos.y};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
        tile = {pos.x, pos.y + 1};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
        tile = {pos.x, pos.y - 1};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
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

    void Generate(TileType firstTile, const Pos& start, const std::vector<TileType>& walkableTiles)
    {
        using namespace std;

        for(int i = 0; i < Grid.size(); ++i)
        {
            for(int j = 0; j < Grid[i].size(); ++j)
            {
                if(Grid[i][j] != TileType::Entrance && (i == 0 || j == 0 || i == Width - 1 || j == Height - 1))
                {
                    Grid[i][j] = TileType::BasicWall;
                }
            }
        }
        
        Grid[start.x][start.y] = firstTile;

        vector<Pos> possibleTiles;

        possibleTiles.push_back(start);

        vector<vector<char>> walkedGrid(Width, vector<char>(Height, 0));

        while(1)
        {
            std::vector<Pos> newTiles;

            for_each(possibleTiles.begin(), possibleTiles.end(), [this, &newTiles, &walkedGrid](Pos p)
            {
                walkedGrid[p.x][p.y] = 1;
                if(Rng() % 5)
                {
                    Grid[p.x][p.y] = TileType::BasicFloor;
                    GetNeighborTiles(p, newTiles, walkedGrid);
                }
            });

            possibleTiles = std::move(newTiles);

            Print();

            if(possibleTiles.size() == 0){break;}
        }
    }
};

int main()
{
    RoomGrid room(15, 21);

    room.AddEntrance({0, 10});
    room.AddEntrance({7, 0});
    room.AddEntrance({0, 20});
    room.AddEntrance({14, 10});

    room.Generate(TileType::BasicFloor, {1, 10}, std::vector<TileType>({TileType::BasicFloor}));
}
