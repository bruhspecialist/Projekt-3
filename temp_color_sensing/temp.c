#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void calibrate_color(
    uint16_t R,     uint16_t G,     uint16_t B,
    double *r_norm, double *g_norm, double *b_norm
) {
    const double refR = 17506.0, refG = 17156.0, refB = 15056.0;
    *r_norm = R / refR;
    *g_norm = G / refG;
    *b_norm = B / refB;
}

const char* detect_color(double r, double g, double b) {
    const double tol = 0.20;
    if (r > g*(1+tol) && r > b*(1+tol)) return "red";
    if (g > r*(1+tol) && g > b*(1+tol)) return "green";
    if (b > r*(1+tol) && b > g*(1+tol)) return "blue";
    if (r > b && g > b) return "yellow";
    if (r > g && b > g) return "magenta";
    if (g > r && b > r) return "cyan";
    if (r >= g && r >= b) return "red";
    if (g >= r && g >= b) return "green";
    return "blue";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <r> <g> <b>\n", argv[0]);
        return 1;
    }
    int R = atoi(argv[1]);
    int G = atoi(argv[2]);
    int B = atoi(argv[3]);
    double rn, gn, bn;
    calibrate_color(R, G, B, &rn, &gn, &bn);
    printf("Detected color: %s\n", detect_color(rn, gn, bn));

    // uint16_t R = 18000, G = 16000, B = 14000;
    // double rn, gn, bn;
    // calibrate_color(R, G, B, &rn, &gn, &bn);
    // printf("Calibrated → R=%.3f, G=%.3f, B=%.3f\n", rn, gn, bn);
    // printf("Detected color: %s\n", detect_color(rn, gn, bn));

    //printf("Detected color: %s\n", detect_color(100, 100, 100));
    return 0;
}