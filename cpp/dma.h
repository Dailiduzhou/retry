#ifndef DMA_H_
#define DMA_H_
#include<iostream>

class baseDMA
{
    private:
        char * label;
        int rating;
    
    public:
        baseDMA(const char * l = "null", int r = 0);
        virtual ~baseDMA();
        baseDMA & operator=(const baseDMA &rs);
        friend std::ostream & operator<<(std::ostream & os, const baseDMA & rs);
};

class lacksDMA :public baseDMA
{
    private:
        enum {COL_LEN = 40};
        char color[COL_LEN];
    public:
        lacksDMA(const char * c = "blank", const char * l = "null", int r = 0);
        friend std::ostream & operator<<(std::ostream & os, const lacksDMA & rs);
};


#endif