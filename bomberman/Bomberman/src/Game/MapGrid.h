#pragma once
#ifndef _MAPGRID_H
#define _MAPGRID_H

#include "../Engine/Types.h"
#include "Enums.h"

class MapGrid 
{
private:

    float* viewdiff;
	FillType extendgrid[13][47];

public:

    MapGrid(float* diff);
    ~MapGrid();

    // cria o grid padrão do cenário
    void CreateGrid();
    
    // ocupa a posição do grid dado pelos pontos x e y com o tipo passado
    void OccupyGridPosition(float x, float y, FillType type);
    
    // ocupa a linha e coluna do grid com o tipo passado
    void OccupyGridPosition(int line, int column, FillType type);
    
    // assume a posição do grid dado pelos pontos x e y como vazio
    void ClearGridPosition(float x, float y);
    
    // torna o valor da linha e coluna do grid como vazio
    void ClearGridPosition(int line, int column);
    
    // verifica o valor da posição do grid dada pelos pontos x e y passados
    FillType CheckGridPosition(float x, float y);
    
    // compara o valor da posição do grid dada pelos pontos x e y passados com o tipo passado
    bool CheckGridPosition(float x, float y, FillType type);
    
    // verifica o valor do grid na linha e coluna passados
    FillType CheckGridPosition(int line, int column);
    
    // verifica o valor do grid na linha e coluna desejada com o tipo passado
    bool CheckGridPosition(int line, int column, FillType  type);

};


#endif // !_MAPGRID_H