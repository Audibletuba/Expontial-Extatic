//System
#include <stdlib.h>

//Engine
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"

//Game
#include "Enemy.h"

namespace df
{
    Enemy::Enemy()
    {
        setType("Enemy");

        setVelocity(Vector(0, -0.25));

        moveToStart();
    }

    void Enemy::moveToStart()
    {
        Vector temp_pos;

        float world_horiz = WM.getBoundary().getHorizontal();
        float world_vert = WM.getBoundary().getVertical();

        temp_pos.setY(world_vert + rand() % (int) world_vert + 3.0f);

        temp_pos.setX(rand() % (int) (world_horiz-1) + 4.0f);

        ObjectList collisions_list = WM.getCollisions(this, temp_pos);
        while(collisions_list.getCount() != 0)
        {
            temp_pos.setY(temp_pos.getY() + 1);
            collisions_list = WM.getCollisions(this, temp_pos);
        }

        WM.moveObject(this, temp_pos);
    }

    void Enemy::out()
    {
        if(getPosition().getY() >= 0)
        {
            return;
        }   
        
        moveToStart();

        new Enemy;
    }

    int Enemy::eventHandler(const Event *p_e)
    {
        return 0;
    }

}//End of namespace df