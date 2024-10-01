/**********************************************************************************
// Enemy (C�digo Fonte)
//
// Cria��o:     17 Set 2024
// Atualiza��o: 19 Set 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Super classe de inimigos
//
**********************************************************************************/

#include "EnemyFactory.h"


EnemyFactory::EnemyFactory()
{
}

EnemyFactory::~EnemyFactory()
{
}

template<class T>
void EnemyFactory::CreateEnemy(float x, float y, Scene * scene, bool invulnerable)
{
	T* enemy = new T(x, y, scene, invulnerable);
	scene->Add(enemy, MOVING);
}

void EnemyFactory::CreateEnemy(uint enemyType, float x, float y, Scene* scene, bool invulnerable)
{
	switch (enemyType)
	{
	case PUROPEN: {
		Puropen* puropen = new Puropen(x, y, scene, invulnerable);
		scene->Add(puropen, MOVING);
		break;
	}
	case DENKYUN: {
		Denkyun* denkyun = new Denkyun(x, y, scene, invulnerable);
		scene->Add(denkyun, MOVING);
		break;
	}
	default:
		break;
	}		
}