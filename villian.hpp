
#ifndef HELLOSFML_VILLIAN_HPP
#define HELLOSFML_VILLIAN_HPP
#
#endif //HELLOSFML_VILLIAN_HPP
#include <SFML/Graphics.hpp>

#pragma once
#include "Map.hpp"
#include "view.h"


namespace vl
{
    class Enemy
    {

    public:
        float dx;
        FloatRect rect;
        Sprite sprite;
        bool life;

        void set(Texture &image, int x, int y)
        {
            sprite.setTexture(image);
            rect = FloatRect(x,y,64,64);
            dx=0.05;
            life=true;
        }

        void update(float time)
        {
            rect.left += dx * time;
            Collision();

            if (dx < 0)
                sprite.setTextureRect(IntRect(64,5,64,54));
            if (dx > 0)
                sprite.setTextureRect(IntRect(64 + 64,5,-64,54));//вправо



            if (!life)
            {
                if(rect.left > 0)//-
                    sprite.setTextureRect(IntRect(0, 0, 98,54));
                if(rect.left > 0)
                    sprite.setTextureRect(IntRect(190 , 5, -56,52));

            }


            sprite.setPosition(rect.left , rect.top );

        }


        void Collision() //ИИ: удар об стену = в другую сторону путь
        {

            for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++)
                for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++)
                    if (mp::TileMap[i][j] =='0')
                    {
                        if (dx>0)
                        {
                            rect.left =  j*32 - rect.width;
                            dx*=-1;
                        }
                        else if (dx<0)
                        {
                            rect.left =  j*32 + 32;
                            dx*=-1;
                        }

                    }
        }
    };

}