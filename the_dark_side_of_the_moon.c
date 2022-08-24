#include <FPT.h>
#include <stdlib.h>
#include <math.h>

#define FRAME_SIZE 500
#define PRISM_WIDTH 10
#define INCOMING_LIGHT_WIDTH 3
#define COL_WIDTH 5 

// takes in an int frame_size as parameter and create a square frame which the
// background is black and width and height equals to frame_size
static void InitFrame(int frame_size);

// draws a prism in the center of the frame in aqua, the width of the side of
// prism equals to prism_width
static int DrawPrism(int frame_size, int prism_width);

// draws incoming light with given width
static void DrawIncomingLight(int frame_size, int incoming_light_width, int prism_size);

// draws color stripes representing the spectrum
static void DrawSpectrum(double color[], int frame_size, int prism_size,
                            double offset[], int color_width);

// draws the refrection inside prism
static void DrawRefraction(int frame_size, int prism_size, int col_width);

int main(int argc, char** argv) {
    double n;  // input for next step
    double q;  // input for exit
    
    InitFrame(FRAME_SIZE);  // init frame
    n = G_wait_key();  // wait for keyboard input to continue

    int prism_size = DrawPrism(FRAME_SIZE, PRISM_WIDTH);  // draw prism
    n = G_wait_key();  // wait for keyboard input to continue

    // draw incoming light
    DrawIncomingLight(FRAME_SIZE, INCOMING_LIGHT_WIDTH, prism_size);
    n = G_wait_key();  // wait for keyboard input to continue

    // draw refraction
    DrawRefraction(FRAME_SIZE, prism_size, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // red strip
    double offset[] = {FRAME_SIZE / 2.0 + prism_size / 4.0 - COL_WIDTH,
                        FRAME_SIZE / 2.0 + COL_WIDTH * sqrt(3),
                        FRAME_SIZE / 2.0 + COL_WIDTH * sqrt(3) -
                            prism_size / 10.0};
    double red[] = {1, 0, 0};
    DrawSpectrum(red, FRAME_SIZE, prism_size, offset, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // Orange strip
    double org[] = {1, 0.5, 0};
    DrawSpectrum(org, FRAME_SIZE, prism_size, offset, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // Yellow strip
    double yel[] = {1, 1, 0};
    DrawSpectrum(yel, FRAME_SIZE, prism_size, offset, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // Green strip
    double gre[] = {0, 1, 0};
    DrawSpectrum(gre, FRAME_SIZE, prism_size, offset, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // Blue strip
    double blu[] = {0, 0.5, 1};
    DrawSpectrum(blu, FRAME_SIZE, prism_size, offset, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // Purple strip
    double pur[] = {0.5, 0, 1};
    DrawSpectrum(pur, FRAME_SIZE, prism_size, offset, COL_WIDTH);
    n = G_wait_key();  // wait for keyboard input to continue

    // draw string
    G_draw_string("Pink Floyd: The Dark Side of the Moon", 5, 5);

    q = G_wait_key();
    G_close();
}

static void InitFrame(int frame_size) {
    // init frame
    G_init_graphics(frame_size, frame_size);

    // set background to black
    G_rgb(0, 0, 0);
    G_fill_rectangle(0, 0, frame_size, frame_size);
}

static int DrawPrism(int frame_size, int prism_width) {
    // the length of sides of prism
    int prism_size = frame_size / 10 * 3;
    // x coord of bottom left vertex of prism
    double x_prism_bot_l = frame_size / 2.0 - prism_size / 2.0;
    // y coord of bottom left vertex of prism
    double y_prism_bot_l = frame_size / 2.0 - prism_size / 4.0 * sqrt(3);
    // x coord of bottom right vertex of prism
    double x_prism_bot_r = frame_size / 2.0 + prism_size / 2.0;
    // x coord of top vertex of prism
    double x_prism_top = frame_size / 2.0;
    // y coord of top vertex of prism
    double y_prism_top = frame_size / 2.0 + prism_size / 4.0 * sqrt(3);

    // draw triangle in aqua
    for (int i = 0; i < prism_width; i++) {
        // change the color of triangles to produce a fading effect
        G_rgb(0, 1 - i * 1.0 / prism_width, 1 - i * 1.0 / prism_width);
        // draw triangles inside the prism border
        G_triangle(x_prism_bot_l + i * sqrt(3), y_prism_bot_l + i,
                    x_prism_bot_r - i * sqrt(3), y_prism_bot_l + i,
                    x_prism_top, y_prism_top - i * 2);
    }

    return prism_size;
}

static void DrawIncomingLight(int frame_size, int incoming_light_width,
                                int prism_size){
    // set color to white
    G_rgb(1, 1, 1);
    // initial y coord of incoming light
    double y_init_offset = (frame_size / 2.0 - prism_size / 4.0 * sqrt(3))
                            + prism_size / 10.0;
    // ending x coord of incoming light
    double x_end_offset = (frame_size / 2.0 - prism_size / 2.0)
                            + prism_size / 4.0;
    // ending y coord of incoming light
    double y_end_offset = frame_size / 2.0;

    // draw 2 lines each time to filling the blanks
    for (int i = 0; i < INCOMING_LIGHT_WIDTH - 1 / 2; i++) {
        G_line(0, y_init_offset + 0.5 * i * sqrt(3), x_end_offset + 0.5 * i, y_end_offset + 0.5 * i * sqrt(3));
        G_line(0, y_init_offset - 0.5 * i * sqrt(3), x_end_offset - 0.5 * i, y_end_offset - 0.5 * i * sqrt(3));
    }
}

static void DrawSpectrum(double color[], int frame_size, int prism_size,
                            double offset[], int color_width) {
    G_rgb(color[0], color[1], color[2]);
    double x_offset = offset[0];
    double y_offset = offset[1];
    double y_end = offset[2]; 
    double x[4], y[4];
    x[0] = x_offset;
    y[0] = y_offset;
    x[1] = frame_size;
    y[1] = y_end;
    x[2] = frame_size;
    y[2] = y_end - 2 * color_width;
    x[3] = x_offset + color_width / sqrt(3);
    y[3] = y_offset - color_width;
    G_fill_polygon(x, y, 4);

    offset[0] = x[3];
    offset[1] = y[3];
    offset[2] = y[2];
}

static void DrawRefraction(int frame_size, int prism_size, int col_width) {
    double x_offset = (frame_size / 2.0 - prism_size / 2.0) + prism_size / 4.0;
    double y_offset = frame_size / 2.0 + col_width * sqrt(3);
    for (int i = 0; i < frame_size / 2 - x_offset; i++) {
        G_rgb(1 - i * 0.03, 1 - i * 0.03, 1 - i * 0.03);
        G_line(i + x_offset, frame_size / 2.0 + i / (y_offset - frame_size / 2.0),
                i + x_offset, frame_size / 2.0 - i / (y_offset - frame_size / 2.0));
    }
}