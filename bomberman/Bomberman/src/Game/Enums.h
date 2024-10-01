#pragma once

#ifndef _ENUMS_H_
#define _ENUMS_H_

    enum ObjTypes {
        PLAYER,
        BOMB,
        BUILDING,
        BLOCK,
        EXPLOSION,
        PORTAL,
        POWERUPS,
        ENEMY
    };

    enum PlayerState { 
        STILL, 
        BORED, 
        WALKUP, 
        WALKDOWN, 
        WALKLEFT, 
        WALKRIGHT, 
        WINNING, 
        DYING 
    };

    enum BombType { 
        NORMAL, 
        R_BOMB, 
        TIMED 
    };

    enum BombState { FUSING, READY };
    enum Directions { 
        UP, 
        DOWN, 
        LEFT, 
        RIGHT 
    };

    enum BlockState { DEFAULT, EXPLODING };
    enum FillType { 
        MPT, // empty  
        PWR, // powerup
        PTL, // portal
        BLK, // block
        WLL  // wall
    };

    enum ExplosionPart { 
        BASE, 
        BODY_V,     BODY_H, 
        TIP_UP,     TIP_DN, 
        TIP_LT,     TIP_RT 
    };

    enum PowerUpType {
        BOMBS,      FIRE,       RED_BOMB,       MAX_PWR,
        BOMBPASS,   SKULL,      INVINCIBLE,     T_BOMB,
        WALLPASS,   SPD_UP,     KICK,           RICE,
        GLOVE,      ONE_UP,     TIME,           LIVES,
        CAKE,       RANDOM,     HAMMER,         APPLE,
        EXTINGUISH, POPSICLE,   ICE_CREAM
    };

#endif