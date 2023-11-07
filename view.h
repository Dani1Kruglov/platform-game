#include <SFML/Graphics.hpp>


#ifndef HELLOSFML_VIEW_H
#define HELLOSFML_VIEW_H
#pragma once

#endif //HELLOSFML_VIEW_H

using namespace sf;

namespace vw
{
    View view;

    void PlayerCoordinate(float x,float y) //чтение координат игрока
    {
        float a = x,b = y;
        if (x < 500)
            a = 500;
        if(x > 4550)
            a = 4550;
        if (y < 400)
            b = 400;
        if( y > 400)
            b = 400;
        view.setCenter(a , b);
    }
}
