#include <SFML/Graphics.hpp>

#ifndef HELLOSFML_PLAYER_HPP
#define HELLOSFML_PLAYER_HPP
#pragma once
#endif //HELLOSFML_PLAYER_HPP
#include "Map.hpp"
#include "view.h"

namespace pl
{
    class Player
    {
    public:

        float dx, dy;//кординаты
        FloatRect rect;
        int health ;//здоровье игрока
        int coin = 0;//количество собранных монет
        bool life;//жизнь игрока
        bool onGround;//если на земле, то true, в ином случае false
        Sprite sprite;
        float AnimationHero;//анимация

        Player(Texture &t)
        {
            sprite.setTexture(t);//загрузка картинки игрока в спрайт
            rect = FloatRect(50,700,40,50);//x,y - координаты начала персонажа, rectw и recth - его размеры
            dx = dy = 0.1 ;//начальная координата персонажа
            AnimationHero = 0;//анимация персонажа
            health = 100;
            life = true;
        }



        void update(float time)//анимация персонажа в разные стороны,его движениe
        {

            rect.left += dx * time;//координата х персонажа

            Collision(0);

            if (!onGround)
                dy = dy + 0.00009*time;;//если не на земле, то координата меняется со скоростью суммы начальной координаты и ускорения (высота 5 блоков)

            rect.top += dy * time;//координата у персонажа

            onGround = false;

            Collision(1);

            AnimationHero += 0.002*time;; //скорость анимации персонажа
            if(AnimationHero > 6)
                AnimationHero -= 6;



            if (dx>0)
                sprite.setTextureRect(IntRect(40*int(AnimationHero),244,40,50));
            if (dx<0)
                sprite.setTextureRect(IntRect(40*int(AnimationHero)+40,244,-40,50));

            sprite.setPosition(rect.left,rect.top);//выводим позицию персонажа по х и у + учитыванием движение карты
            dx = 0;
            if(health <= 0)
            {
                life = false;
                dx = 0;
            }

        }


        float getplayercoordinateX()//этим методом будем забирать координату Х
        {
            return rect.left;
        }
        float getplayercoordinateY()//этим методом будем забирать координату Y
        {
            return rect.top;
        }

        void Collision(int dir)//взаимодействие с картой
        {
            for (int i= rect.top/32; i<(rect.top + rect.height)/32; i++)//проходим по циклу карты,где он соприкасается
            {
                for (int j = rect.left/32; j<(rect.left + rect.width)/32; j++)
                {
                    if(mp::TileMap[i][j] == '0')
                    {
                        if((dx > 0) && ( dir == 0))
                            rect.left = j * 32 - rect.width;
                        if((dx < 0) && ( dir == 0))
                            rect.left = j * 32 + 32;
                        if((dy > 0) && ( dir == 1))
                        {
                            rect.top = i * 32 - rect.height;
                            dy = 0 ;
                            onGround = true;
                        }
                        if((dy < 0) && ( dir == 1))
                        {
                            rect.top = i * 32 + 32;
                            dy = 0;
                        }
                    }
                    if(mp::TileMap[i][j] == 'B') //если персонаж пересекает  территории с аптекой, то они исчезают, а персонажу прибавляется здоровье
                    {
                        mp::TileMap[i][j] = ' ';
                        health +=20;

                    }
                    if((mp::TileMap[i][j] == 'K') ||(mp::TileMap[i][j] == 'L'))
                    {
                        health -=0.0000001;
                        dy= -0.1;
                    }
                    if(mp::TileMap[i][j] == 'E')
                    {
                        rect.left = 2000 ;
                        rect.top = 250;
                    }
                    if(mp::TileMap[i][j] == 'M')
                    {
                        coin++;
                        mp::TileMap[i][j] = ' ';
                    }
                    if(mp::TileMap[i][j] == 'Z')
                    {
                        rect.left = 3700;
                        rect.top = 150;
                    }
                    if(mp::TileMap[i][j] == 'S')
                    {
                        mp::TileMap[i][j] = ' ';
                    }

                    if((mp::TileMap[i][j] == 'Q')||(mp::TileMap[i][j] == 'W'))
                    {
                        coin = coin + 13748;
                    }
                }
            }
        }
    };
}