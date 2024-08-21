/**********************************************************************************
// TileSet (Código Fonte)
// 
// Criação:     17 Abr 2012
// Atualização: 07 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Representa uma folha de sprites
//
**********************************************************************************/

#include "TileSet.h"
#include "Image.h"

// -------------------------------------------------------------------------------

TileSet::TileSet(string filename, uint tileWidth, uint tileHeight, uint numCols, uint numTiles) : 
    image(new Image(filename)), 
    width(tileWidth), 
    height(tileHeight), 
    columns(numCols),    
    size(numTiles)
{
}

// -------------------------------------------------------------------------------

TileSet::~TileSet()
{
    // libera memória ocupada pela imagem
    if (image)
    {
         delete image;
    }
}

// -------------------------------------------------------------------------------