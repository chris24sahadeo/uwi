

struct Pixel{
    int r, g, b;
};


Pixel color(Pixel pixel, int r, int g, int b){
    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    return pixel;
}


Pixel p;
p = color(p, 218, 112, 214);


Pixels picture[100][150];


for(int i = 0; i < 100; i++){
    for(int j = 0; j < 150; j++){
        int newColour = 0.3*picture[i][j].r + 0.59*picture[i][j].g + 0.11*picture[i][j].b;
        picture[i][j] = color(picture[i][j], newColour, newColour, newColour);
    }
}


int i = 0;
int j = 99;
while(i < j){
    for(int k = 0; k < 150; k++){
        Pixel temp = picture[i][k];
        picture[i][k] = picture[j][k];
        picture[j][k] = temp;
    }
    i++;
    j--;
}
