#pragma once

class dynamic_libs
{
    public:
        dynamic_libs() {};
        virtual         ~dynamic_libs() {};
        
        // virtual bool    Init();
        // virtual void    Render();
        // virtual int     Input(int &dir, int &lib);

        virtual bool    Init() = 0;
        virtual int    Render() = 0;
        virtual int     Input(int &lib) = 0;
};

typedef                 dynamic_libs* create_t();
typedef void            destroy_t(dynamic_libs*);
