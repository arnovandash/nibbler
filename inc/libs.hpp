#pragma once
#include <iostream>
#include <vector>


struct Part{
	unsigned int     x;
	unsigned int     y;
	Part(unsigned int col, unsigned int row);
	Part();
};



class dynamic_libs
{
    public:
        dynamic_libs() {};
        virtual         ~dynamic_libs() {};
        
        // virtual bool    Init();
        // virtual void    Render();
        // virtual int     Input(int &dir, int &lib);

        virtual bool    Init(int Width, int Height) = 0;
        
		virtual int    Render(int foodX, int foodY, std::vector<Part> snake) = 0;
//        virtual int     Input(int &lib) = 0;
};

typedef                 dynamic_libs* create_t();
typedef void            destroy_t(dynamic_libs*);
