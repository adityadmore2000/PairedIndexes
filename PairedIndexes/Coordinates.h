#pragma once

class Coordinates
{

    float x;
    float y;
    float z;
    static int unique_id;
public:
    Coordinates(float x, float y, float z) :x(x), y(y), z(z) {
        unique_id++;
    }

    void setX(int x);
    void setY(int y);
    void setZ(int z);
    float getX();
    float getY();
    float getZ();
};