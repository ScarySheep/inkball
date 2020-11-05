#ifndef AREACOVERAGE_H
#define AREACOVERAGE_H
class AREA
{
    int screen_width;
    int screen_height;
    double x1,y1;
    double x2,y2;
    double m;//slope
    int gap;
    int area_total;
    char storge[40][45];

public:

    AREA();
    void setNewPosition(double ,double );
    void check_and_storge();
    int GetArea();

};

#endif
