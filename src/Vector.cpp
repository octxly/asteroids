#ifndef VECTOR
#define VECTOR

#define MFACTOR 100

struct Vector2F{
  float x;
  float y;

  Vector2F(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Vector2S {
  short x;
  short y;

  Vector2S(short x = 0, short y = 0) : x(x * MFACTOR), y(y * MFACTOR) {}

  void setX(short x){ this->x = x * MFACTOR; }
  float getX(){ return ((float) this->x) / (float) MFACTOR; }

  void setY(short y){ this->y = y * MFACTOR; }
  float getY(){ return ((float) this->y) / (float) MFACTOR; }

  Vector2S& operator=(const Vector2F& other){
    this->setX(other.x);
    this->setY(other.y);
    return *this;
  }
};

#endif