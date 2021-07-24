# class++

Utility for generating classes for C++  

Can:  
 * Generate any types get/set methods
 * Constructor (Empty,base,copy)
 * Print into console or in file

Written in C++11

## Example

Do in console (Linux):

    class++ -h -c "vec2(int x,int y)"

It prints:

    class vec2{
    private:
        int x;
        int y;
    public:
        vec2(){ // Empty constructor
            this->x = 0;
            this->y = 0;
        }
        vec2(int _x,int _y){ //base constructor
            this->x = _x;
            this->y = _y;
        }
        vec2(const vec2& _c){ //copy constructor
            this->x = _c.getX();
            this->y = _c.getY();
        }
    
        int getX(){return this->x;}
        int getY(){return this->y;}

        int getX() const{return this->x;}
        int getY() const{return this->y;}

        void setX(int _x){this->x = _x;}
        void setY(int _y){this->y = _y;}
    };

## Install 

    git clone https://github.com/lakeFm/classCPP.git
    cd classCPP && mkdir build && cd build
    cmake .. && sudo make install

## Author LakeFm (C) 2021 
 Assembled in CLion 2021.1.3
