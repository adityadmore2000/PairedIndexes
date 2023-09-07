#include "Coordinates.h"

int Coordinates::unique_id = 0;

void Coordinates::setX(int x) {
    this->x = x;
}
void Coordinates::setY(int y) {
    this->y = y;
}
void Coordinates::setZ(int z) {
    this->z = z;
}
float Coordinates::getX() {
    return this->x;
}
float Coordinates::getY() {
    return this->y;
}
float Coordinates:: getZ() {
    return this->z;

}