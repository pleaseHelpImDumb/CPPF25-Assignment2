#include "bmp.hpp"
#include <iostream>
#include <time.h>

color mix_color(color c1, color c2, float dx, float dy){
    color pixel_color((c2.r*((dx+dy)/2)+(c1.r*(1-((dx+dy)/2)))), 
                      (c2.g*((dx+dy)/2)+(c1.g*(1-((dx+dy)/2)))), 
                      (c2.b*((dx+dy)/2)+(c1.b*(1-((dx+dy)/2)))));
    return pixel_color;
}

void draw_rectangle(BMP &bmp,int x, int y, int l, int h, int b, color c ){
    for(int i=0;i<=l;i++){
        for(int ii=0;ii<=b;ii++){
        bmp.set_pixel(i+x, y+ii, c.r,c.g,c.b);
        bmp.set_pixel(i+x, y+h-ii, c.r, c.g,c.b);
        }
    }

    for(int j=0;j<=h;j++){
        for(int ii=0;ii<=b;ii++){
            bmp.set_pixel(x+ii, y+j, c.r,c.g,c.b);
            bmp.set_pixel(x+l-ii, y+j,c.r, c.g,c.b);
        }
    }
}

// gradient fill
void draw_gradient_rectangle(BMP &bmp,int x, int y, int l, int h, color c1, color c2 ){
    //for each pixel
    for(int i = x; i < x+l; i++){
        for(int j = y; j < y+h; j++){
            //somehow gradient color from (x,y) to (x+l, y+h)
            int r_diff = c1.r-c2.r;
            (r_diff < 0)? r_diff = r_diff*-1:r_diff=r_diff;
            int g_diff = c1.g-c2.g;
            (g_diff < 0)? g_diff = g_diff*-1:g_diff=g_diff;
            int b_diff = c1.b-c2.b;
            (b_diff < 0)? b_diff = b_diff*-1:b_diff=b_diff;
            
            float dx = (float(i)-float(x))/float(l);
            float dy = (float(j)-float(y))/float(h);

            color c3(mix_color(c1, c2, dx, dy));
            bmp.set_pixel(i, j, c3.r, c3.g, c3.b);
        }
    }
}

// triangle

int main() {
    
    BMP bmp(500, 500); 
    srand(static_cast<unsigned int>(time(0)));
    
    //draw 5 randoms rectangles
    color c(0,255,0);
    color c1(0,0,255);
    /*
    for(int i=0;i<10;i++){
        uint8_t x=rand()%500;
        uint8_t y=rand()%500;
        uint8_t l=rand()%500;
        uint8_t h=rand()%500;
        
        draw_rectangle(bmp,x,y,l,h,rand()%10,c);
    }
    */
   //draw border
    draw_rectangle(bmp,1,1,500,500,10,color{255,0,0});
    
    draw_gradient_rectangle(bmp, 20, 20, 250, 250, c, c1);
    bmp.write("gradient_rect.bmp"); // Save the image to a file

    return 0;
}