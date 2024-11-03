#include "MapGrid.h"
#include "Enums.h"


MapGrid::MapGrid(float* diff) 
{
    viewdiff = diff;
	CreateGrid();
}


MapGrid::~MapGrid() {}


// ----------------------------------------------------------------------------
void MapGrid::OccupyGridPosition(float x, float y, FillType type)
{
    int line = (y - 32) / 16;
    int column = ((x-16)+*viewdiff) / 16;
    extendgrid[line][column] = type;
}


// ----------------------------------------------------------------------------
void MapGrid::OccupyGridPosition(int line, int column, FillType type)
{extendgrid[line][column] = type;}


// ----------------------------------------------------------------------------
void MapGrid::ClearGridPosition(float x, float y)
{
    
    int line = (y - 32) / 16;
    int column = ((x-16)+*viewdiff) / 16;

    extendgrid[line][column] = MPT;
}


// ----------------------------------------------------------------------------
void MapGrid::ClearGridPosition(int line, int column)
{extendgrid[line][column] = MPT;}


// ----------------------------------------------------------------------------
FillType MapGrid::CheckGridPosition(float x, float y)
{
    int line = (y - 32) / 16;
    int column = ((x-16)+*viewdiff) / 16;

    return extendgrid[line][column];
}


// ----------------------------------------------------------------------------
bool MapGrid::CheckGridPosition(float x, float y, FillType type)
{
    int line = (y - 32) / 16;
    int column = ((x-16)+*viewdiff) / 16;
    return extendgrid[line][column] == type;
}


// ----------------------------------------------------------------------------
FillType MapGrid::CheckGridPosition(int line, int column)
{return extendgrid[line][column];}


// ----------------------------------------------------------------------------
bool MapGrid::CheckGridPosition(int line, int column, FillType type)
{return extendgrid[line][column] == type;}


// ----------------------------------------------------------------------------
inline void MapGrid::CreateGrid() {
    for (auto lin = 0; lin < 13; lin++)
    {
        for (auto col = 0; col < 47; col++)
        {
            // primeira e última linha
            if (lin == 0 || lin == 12)
                extendgrid[lin][col] = FillType::WLL;
            // linhas restantes
            else
            {
                // linhas impares
                if ((lin % 2 != 0))
                    extendgrid[lin][col] = FillType::MPT;
                // linhas pares
                else
                {
                    extendgrid[lin][col] = FillType::MPT;

                    if (col % 2 == 0)
                        extendgrid[lin][col] = FillType::WLL;
                }

                // primeiro e último espaço de cada coluna
                if (col == 0 || col == 46)                  // isso garante o bloqueio das bordas do mapa
                    extendgrid[lin][col] = FillType::WLL;
            }
        }
    }
}