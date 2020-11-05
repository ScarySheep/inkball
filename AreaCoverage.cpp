#include "AreaCoverage.h"
#include<iostream>
#include<cmath>
using namespace std;

AREA::AREA()
    {
        screen_width=840;
        screen_height=680;
        gap=20;
        area_total=0;
        m=0;
        for(int j=0;j<40;j++)
        {
            for(int i=0;i<45;i++)
            {
                storge[j][i]='0';
            }
        }
        x1=45;y1=45;  //(x1,y1)=(0,0)
        x2=45;y2=45;  //(x2,y2)=(0,0)

    }





void AREA::setNewPosition(double x,double y)
    {
        x1=x2;
        y1=y2;
        x2=x;
        y2=y;
        m=abs((double)(y2-y1)/(x2-x1));
        check_and_storge();
    }


void AREA::check_and_storge()
    {

        double* temp  = NULL;temp  = new double;
        double* px1  = NULL;px1  = new double;   *px1=(0.1*10*x1/(double)gap);
        double* py1  = NULL;py1  = new double;   *py1=(0.1*10*y1/(double)gap);
        double* px2  = NULL;px2  = new double;   *px2=(0.1*10*x2/(double)gap);
        double* py2  = NULL;py2  = new double;   *py2=(0.1*10*y2/(double)gap);
        int* upper  = NULL;upper  = new int;
        int* lower  = NULL;lower  = new int;
        int* right  = NULL;right  = new int;
        int* left  = NULL;left  = new int;
        double* delta  = NULL;delta  = new double;
        double* delta_x  = NULL;delta_x  = new double;

        if((*px1)>(*px2))
        {
            (*temp)=(*px1);
            (*px1)=(*px2);
            (*px2)=(*temp);
            (*temp)=(*py1);
            (*py1)=(*py2);
            (*py2)=(*temp);

        }
        if(((y2-y1)/(x2-x1))>0)
        {
            //  [lower + left] VS [upper + right]
            *lower=floor(*py1);
            *left=floor(*px1);
            *right=ceil(*px2);
            *upper=ceil(*py2);
            storge[(*lower)][(*left)]='1';
            storge[*upper][*right]='1';

            for(int j=(*lower);j<=(*upper);j++)
                {
                    for(int i=(*left);i<=(*right);i++)
                    {

                        if( storge[j][i]=='0')
                        {
                            *delta=m+1;
                            *delta_x=-(*py1)+m*(*px1)+i+j+1;
                            if((((*delta_x)/(*delta))>=i)&&(((*delta_x)/(*delta))<=(i+1))){storge[j][i]='1'; /*cout<<"i = "<<i<<"\tj = "<<j<<endl;*/ }
                        }


                    }
                }
        }
        else if(((y2-y1)/(x2-x1))<0)
        {
            //  [upper + left] VS [lower + right]
            *upper=ceil(*py1);
            *left=floor(*px1);
            *right=ceil(*px2);
            *lower=floor(*py2);
            storge[*upper][*left]='1';
            storge[*lower][*right]='1';
            for(int j=(*lower);j<=(*upper);j++)
            {
                for(int i=(*right);i>=(*left);i--)
                {
                    if( storge[j][i]=='0')
                    {
                        *delta=-m-1;
                        *delta_x=-(*py1)-m*(*px1)+j-i+1;
                        if(((*delta_x)/(*delta))>=i&&((*delta_x)/(*delta))<=(i+1)){storge[j][i]='1';  /*cout<<"i = "<<i<<"\tj = "<<j<<endl; */}
                    }


                }
            }
        }
        delete temp;
        delete px1;
        delete px2;
        delete py1;
        delete py2;
        delete upper;
        delete lower;
        delete right;
        delete left;
        delete delta;
        delete delta_x;
    }



int AREA::GetArea()
    {
        area_total=0;
        for(int j=0;j<=(screen_height/gap);j++)
        {
                for(int i=0;i<=(screen_width/gap);i++)
                {
                    if( storge[j][i]=='1')
                    {
                        area_total+=(gap*gap);
                    }
                }


        }

        return area_total;
    }
