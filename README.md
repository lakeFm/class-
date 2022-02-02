# class++

Utility for generating classes for C++  

Can:  
 * Generate any types get/set methods
 * Constructor (Empty,base,copy)
 * Print into console or in file

Written in C++11

## Example

Do in console (Linux):

    class++ -hc "vec2(float x,float y)"

It prints:

    #ifndef VEC2_H
    #define VEC2_H
    
    class vec2{
    private:
        float x;
        float y;
    public:
    
        vec2(){
            this->x = 0.0f;
            this->y = 0.0f;
        }
        vec2(float _x, float _y){
            this->x = _x;
            this->y = _y;
        }
        vec2(const vec2& _v){
            this->x = _v.getX();
            this->y = _v.getY();
        }
        
        void setX(float _x){ this->x = _x;}
        float getX(){ return this->x;}
        float getX() const{ return this->x;}
        
        void setY(float _y){ this->y = _y;}
        float getY(){ return this->y;}
        float getY() const{ return this->y;}
    
    };
    
    #endif

## Install 

    git clone https://github.com/lakeFm/classCPP.git
    cd classCPP && mkdir build && cd build
    cmake .. && sudo make install

## Author
Maks Makuta  aka  ``` maksmakuta ``` (C) 2022    
Assembled in CLion 2021.2
