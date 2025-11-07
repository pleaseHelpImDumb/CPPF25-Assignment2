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

void draw_line(BMP &bmp, int x1, int y1, int x2, int y2, color c){

    // find slope
    int dx = x2 - x1;   
    int dy = y2 - y1;   
    
    // find # of steps (the bigger difference - aka which direction steps go in)
    int step = std::max(abs(dx), abs(dy)); //steps = 150

    // find 'ratio' - how much x and y moves
    float x_step = (float)dx / step;      
    float y_step = (float)dy / step;      
    
    // draw line
    float x = x1;
    float y = y1;
    for(int i = 0; i <= step; i++) {
        bmp.set_pixel((int)x, (int)y, c.r, c.g, c.b);
        x += x_step;    // ex: if steeper, x < 1 so x might be a value like 100.33. when cast to int, it will always round down
        y += y_step;
    }
}

// triangle
void draw_triangle(BMP &bmp, int x1, int y1, int x2, int y2, int x3, int y3, color c){
    draw_line(bmp, x1, y1, x2, y2, c);
    draw_line(bmp, x1, y1, x3, y3, c);
    draw_line(bmp, x2, y2, x3, y3, c);
}

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
    
    
    //draw_gradient_rectangle(bmp, 20, 20, 250, 250, c, c1);
    // bmp.write("gradient_rect.bmp"); // Save the image to a file


    draw_line(bmp, 250, 250, 300, 400, color{0,0,0});
    draw_triangle(bmp, 100, 100, 200, 100, 150, 400, color{255,0,0});
    bmp.write("triangle.bmp"); // Save the image to a file


    return 0;
}