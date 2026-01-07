#include "dma.h"
#include<cstring>

baseDMA::baseDMA(const char * l, int r){
    label = new char[std::strlen(l)+1];
    std::strcpy(label, l);
    rating = r;
}

baseDMA::~baseDMA(){
    delete [] label;
}

baseDMA & baseDMA::operator=(const baseDMA & rs){
    if (this == &rs)
        return *this;
    delete [] label;
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
    return *this;
}

std::ostream & operator<<(std::ostream & os, const baseDMA & rs){
    os << "Label: " << rs.label << std::endl;
    os << "Rating: " << rs.rating << std::endl;
    return os;
}

lacksDMA::lacksDMA(const char * c, const char * l, int r)
                : baseDMA(l,r)
{
    std::strncpy(color, c, 39);
    color[39] = '\0';
}

std::ostream & operator<<(std::ostream & os, const lacksDMA & ls){
    os << (const baseDMA &) ls << std::endl;
    os << "Color: " << ls.color << std::endl;
    return os;
}