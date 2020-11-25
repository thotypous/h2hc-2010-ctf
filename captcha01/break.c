#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <jpeglib.h>

typedef struct {
    float mean;
    float std;
} gaussian_t;

typedef struct {
    const char *text;
    gaussian_t w;
    gaussian_t h;
    gaussian_t aspect;
    gaussian_t fracdim;
    gaussian_t backg;
    gaussian_t holes[10];
} entry_t;

#define N 10

static entry_t entries[N] = {
  { "aalii", { 91.7240005, 8.9746698 }, { 20.4346000, 2.3176479 }, { 4.5438946, 0.7032023 }, { 1.7240507, 0.0338760 }, { 12430.1200000, 174.2557477 }, { { 24.9200000, 4.1753563 }, { 1.0141338, 0.2343344 }, { -40.2400000, 73.4015150 }, { -59.2379673, 49.9247042 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, } },
  { "aardvark", { 74.5051431, 8.4312972 }, { 29.9961999, 2.2935614 }, { 2.4974923, 0.3357365 }, { 1.7047997, 0.0372076 }, { 12035.1600000, 204.2366627 }, { { 18.0000000, 5.1768716 }, { 1.2208367, 0.7498855 }, { 51.0800000, 13.8157012 }, { 2.9781838, 1.5462769 }, { 75.2800000, 39.2953127 }, { -2.7850251, 19.8541335 }, { -64.3200000, 72.3644775 }, { -79.7977270, 40.4046284 }, { -94.1200000, 28.8059994 }, { -95.8400000, 20.3797547 }, } },
  { "aardwolf", { 78.9944098, 9.6498457 }, { 30.5699999, 2.8881231 }, { 2.6000369, 0.3653788 }, { 1.7124354, 0.0368138 }, { 11935.8260870, 180.4173066 }, { { 18.2173913, 7.7904988 }, { 1.2121671, 1.0328766 }, { 49.9130435, 19.0375214 }, { 2.9197588, 1.6230567 }, { 66.3478261, 54.0640592 }, { -6.3947383, 28.9030005 }, { 11.4347826, 97.8454087 }, { -42.1686903, 50.7308408 }, { -72.4347826, 71.2740126 }, { -86.6971329, 34.3489021 }, } },
  { "aaronic", { 71.9812493, 7.7960188 }, { 25.7862502, 2.3647540 }, { 2.7983940, 0.2576545 }, { 1.6804939, 0.0546420 }, { 12249.0000000, 256.4683216 }, { { 19.1875000, 4.3188359 }, { 1.0768425, 0.3029327 }, { 55.3750000, 12.1288654 }, { 2.4502776, 1.3557529 }, { -20.0000000, 91.4227816 }, { -55.5001342, 50.4612133 }, { -88.1250000, 45.9916772 }, { -93.6527778, 24.5826860 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, } },
  { "aaronite", { 72.7995540, 7.4530606 }, { 25.4393750, 2.0806910 }, { 2.8756832, 0.3345716 }, { 1.6824954, 0.0579520 }, { 12271.2500000, 217.9187062 }, { { 19.6250000, 9.3332403 }, { 1.1998528, 0.7632970 }, { 54.6250000, 19.8742138 }, { 3.2651463, 1.9110712 }, { 81.1562500, 60.5960546 }, { -8.1790013, 29.5444910 }, { -59.6875000, 83.9532748 }, { -81.0763392, 39.3933999 }, { -100.0000000, 0.0000000 }, { -100.0000000, 0.0000000 }, } },
  { "ababdeh", { 88.7028574, 7.6816571 }, { 33.0763998, 2.8678307 }, { 2.6945399, 0.2621216 }, { 1.7219681, 0.0489212 }, { 11493.7600000, 276.2810569 }, { { 17.9600000, 5.8956255 }, { 3.0021903, 1.7620215 }, { 40.3600000, 9.2081703 }, { 1.3202698, 0.6714227 }, { 60.1600000, 10.2671515 }, { 3.0874455, 1.8110309 }, { 81.6000000, 12.8561269 }, { 3.0988446, 1.7988131 }, { 87.8000000, 57.0620715 }, { -6.6543613, 27.5419537 }, } },
  { "ababua", { 93.3164287, 10.8839827 }, { 30.4960000, 2.4234258 }, { 3.0794274, 0.4383605 }, { 1.7333101, 0.0484095 }, { 11634.5500000, 230.0861741 }, { { 23.1000000, 7.0703607 }, { 2.9200385, 1.3018055 }, { 44.4500000, 8.6975571 }, { 1.1320503, 0.5999738 }, { 66.4000000, 16.5087855 }, { 2.9890685, 1.9141328 }, { 94.2500000, 49.1974339 }, { -3.7931837, 22.0760968 }, { -71.8500000, 67.3871464 }, { -84.8931348, 35.9621735 }, } },
  { "abaca", { 96.6992477, 10.0302965 }, { 26.6363161, 2.1715703 }, { 3.6500283, 0.4408141 }, { 1.7244195, 0.0583953 }, { 11938.3157895, 289.6962207 }, { { 24.0000000, 4.8231896 }, { 3.3053942, 1.6770880 }, { 49.3157895, 8.6514534 }, { 1.0875062, 0.3710297 }, { 76.2105263, 44.8794631 }, { -3.7312775, 22.7450943 }, { -60.1578947, 77.2318881 }, { -78.1806432, 42.3043803 }, { -89.6315789, 43.9894850 }, { -94.6289474, 22.7874464 }, } },
  { "abacate", { 86.2229584, 9.9947932 }, { 28.2242859, 2.1245365 }, { 3.0624389, 0.3473530 }, { 1.7253366, 0.0433000 }, { 11965.3214286, 200.9790418 }, { { 21.6428571, 6.5749214 }, { 3.1520312, 1.6752575 }, { 42.1785714, 10.0144666 }, { 1.1166631, 0.4300736 }, { 76.1071429, 18.5305525 }, { 1.2527797, 0.5726892 }, { 84.2142857, 66.9500652 }, { -9.6731678, 31.2984654 }, { -64.1071429, 77.4515237 }, { -81.9105790, 38.8015037 }, } },
  { "abacay", { 97.5630951, 10.5741781 }, { 29.2058331, 1.5825740 }, { 3.3424154, 0.3374382 }, { 1.7238673, 0.0289189 }, { 11808.1666667, 114.9034619 }, { { 17.5000000, 6.1305247 }, { 2.8367402, 1.9161614 }, { 43.5833333, 9.6992984 }, { 1.0819271, 0.6402605 }, { 73.7500000, 16.0370664 }, { 1.7689920, 2.2416774 }, { -2.9166667, 97.3930681 }, { -49.3134750, 50.6881737 }, { -48.0833333, 89.9504107 }, { -74.6183578, 43.9639216 }, } },
};

static void dbgPnm(int *img, int w, int h, const char *outfile) {
#if 0
    FILE *fp;
    int x, y, i = 0;
    assert((fp = fopen(outfile, "wb")));
    fprintf(fp, "P1\n%d %d\n", w, h);
    for(y = 0; y < h; y++) {
        for(x = 0; x < w; x++) {
            fprintf(fp, "%d ", img[i++]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
#endif
}

static float getUsefulWidth(int *img, int w, int h) {
    int x, y;
    float usefulWidth = 0.;
    int tmpWidth;
    for(y = 0; y < h; y++) {
        for(x = 0  ; x <  w && !img[w*y+x]; x++);
        tmpWidth = x;
        for(x = w-1; x >= 0 &&  img[w*y+x]; x++);
        tmpWidth = x - tmpWidth;
        usefulWidth += tmpWidth;
    }
    usefulWidth /= h;
    return usefulWidth;
}

static float getUsefulHeight(int *img, int w, int h) {
    int x, y;
    float usefulHeight = 0.;
    int tmpHeight;
    for(x = 0; x < w; x++) {
        for(y = 0;   y <  h && !img[w*y+x]; y++);
        tmpHeight = y;
        for(y = h-1; y >= 0 &&  img[w*y+x]; y++);
        tmpHeight = y - tmpHeight;
        usefulHeight += tmpHeight;
    }
    usefulHeight /= w;
    return usefulHeight;
}

static int boxCount(int *img, int w, int h, int l) {
    int epsilon = h/l;
    int x0, y0, x1, y1, i;
    int numBoxes = 0;
    for(y0 = 0; y0 < h; y0+=epsilon) {
        for(x0 = 0; x0 < w; x0+=epsilon) {
            for(y1 = 0; y1 < epsilon && (y0+y1)<h; y1++) {
                i = (y0+y1)*w + x0;
                for(x1 = 0; x1 < epsilon && (x0+x1)<w; x1++) {
                    if(img[i]) {
                        numBoxes++;
                        goto boxCount_endBox;
                    }
                    i++;
                }
            }
boxCount_endBox:;
        }
    }
    return numBoxes;
}

static float calcFractalDim(int *img, int w, int h) {
    double meanxy=0., meanx=0., meany=0., meanx2=0.;
    int l;
    for(l = 1; l <= h; l++) {
        double x = log(l);
        double y = log(boxCount(img, w, h, l));
        meanxy += x*y;
        meanx2 += x*x;
        meanx  += x;
        meany  += y;
    }
    meanxy /= l;
    meanx2 /= l;
    meanx  /= l;
    meany  /= l;
    return (meanxy-meanx*meany)/(meanx2 - meanx*meanx);
}

static int floodFill(int *img, int w, int h, int x, int y) {
    int numFilled = 1;
    if(img[w*y+x])
        return 0;
    img[w*y+x] = 1;
    if(x > 0) {
        numFilled += floodFill(img, w, h, x-1, y);
        if(y > 0)
            numFilled += floodFill(img, w, h, x-1, y-1);
        if(y < h-1)
            numFilled += floodFill(img, w, h, x-1, y+1);
    }
    if(x < w-1) {
        numFilled += floodFill(img, w, h, x+1, y);
        if(y > 0)
            numFilled += floodFill(img, w, h, x+1, y-1);
        if(y < h-1)
            numFilled += floodFill(img, w, h, x+1, y+1);
    }
    if(y > 0)
        numFilled += floodFill(img, w, h, x, y-1);
    if(y < h-1)
        numFilled += floodFill(img, w, h, x, y+1);
    return numFilled;
}

static int findHoles(int *img, int w, int h, int x0, int *lX, int *area) {
    int x, y, i, columnHasHole, firstX, lastX, holeY;
    for(x = x0; x < w; x++) {
        columnHasHole = 0;
        for(y = 0, i = x; y < h; y++, i+=w) {
            if(!img[i]) {
                holeY = y;
                columnHasHole = 1;
                break;
            }
        }
        if(columnHasHole)
            break;
    }
    if(!columnHasHole)
        return -1;
    *area = floodFill(img, w, h, x, holeY);
    firstX = x;
    for(; x < w; x++) {
        columnHasHole = 0;
        for(y = 0, i = x; y < h; y++, i+=w) {
            if(!img[i]) {
                columnHasHole = 1;
                break;
            }
        }
        if(!columnHasHole)
            break;
    }
    lastX = x-1;
    *lX = lastX+1;
    return (firstX + lastX) / 2;
}

static float calcG(gaussian_t *g, float x) {
    float xu = x - g->mean;
    return exp(-xu*xu/(2.*g->std));
}

static void breakCaptcha(int *img, int w, int h) {
    float usefulWidth  = getUsefulWidth (img, w, h);
    float usefulHeight = getUsefulHeight(img, w, h);
    float aspectRatio  = usefulWidth / usefulHeight;
    float fractalDim   = calcFractalDim(img, w, h);
    float backgArea;
    int holesPos[6], holesArea[6];
    float holesfArea[6];
    double maxProb = 0.;
    int entryMaxProb = 0;
    int i, j, k, area, lasti=-100;
    dbgPnm(img, w, h, "beforeflood.pnm");
    backgArea    = floodFill(img, w, h, 0, 0);
    j = 0; k = 0;
    dbgPnm(img, w, h, "beforeholes.pnm");
    while(1) {
        i = findHoles(img, w, h, j, &j, &area);
        if(i < 0 || k >= 6)
            break;
        if(area <= 5 || (i-lasti<=3))
            continue;
        lasti = i;
        holesPos [k  ] = i;
        holesArea[k++] = area;
        img[i] = 0;
    }
    for(i = 1; i < k; i++) {
        holesPos[i] -= holesPos[0];
        holesfArea[i] = ((float)holesArea[i]) / ((float)holesArea[0]);
    }
    for(; i < 6; i++) {
        holesPos[i] = -100;
        holesfArea[i] = -100.;
    }
#if 0
    dbgPnm(img, w, h, "afterholes.pnm");
    printf("%.7f\t%.7f\t%.7f\t%.7f\t%.7f", usefulWidth, usefulHeight, aspectRatio, fractalDim, backgArea);
    for(i = 1; i < 6; i++) {
        printf("\t%.7f\t%.7f", (double)holesPos[i], (double)holesfArea[i]);
    }
    printf("\n");
#endif
#if 1
    for(i = 0; i < N; i++) {
        double thisEntryProb = 1.;
        thisEntryProb *= 10. * calcG(&entries[i].w, usefulWidth);
        thisEntryProb *= 10. * calcG(&entries[i].h, usefulHeight);
        thisEntryProb *= 10. * calcG(&entries[i].aspect, aspectRatio);
        thisEntryProb *= 10. * calcG(&entries[i].fracdim, fractalDim);
        /*thisEntryProb *= 10. * calcG(&entries[i].backg, backgArea);*/
        j = 0;
        for(k = 1; k < 6; k++) {
            float tmp;
            //printf("->%d %.7f\n", k, thisEntryProb);
            tmp = 10. * calcG(&entries[i].holes[j++], holesPos[k]);
            if(!isnan(tmp))
                thisEntryProb *= tmp;
            tmp = 10. * calcG(&entries[i].holes[j++], holesfArea[k]);
            if(!isnan(tmp))
                thisEntryProb *= tmp;
        }
        //printf("%.7e %s\n", thisEntryProb, entries[i].text);
        if(thisEntryProb > maxProb) {
            entryMaxProb = i;
            maxProb = thisEntryProb;
        }
    }
#endif
    printf("%s\n", entries[entryMaxProb].text); 
}

static int *openJpeg(FILE *fp, int thresold, int *w, int *h) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    int *img;
    int i, j = 0;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fp);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    assert(cinfo.num_components == 3);
    img = (int *)malloc(cinfo.output_width*cinfo.output_height*sizeof(int));
    row_pointer[0] = (uint8_t *)malloc(3*cinfo.output_width);

    *w = cinfo.output_width;
    *h = cinfo.output_height;

    while(cinfo.output_scanline < cinfo.image_height) {
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
        for(i = 0; i < 3*cinfo.image_width; i+=3) {
			img[j++] = (row_pointer[0][i+0] +
                        row_pointer[0][i+1] +
                        row_pointer[0][i+2]) < thresold;
        }
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(row_pointer[0]);

    return img;
}

int main(int argc, char **argv) {
    FILE *fp;
    int *img, w, h;
    assert(argc == 2);
    assert((fp = fopen(argv[1], "rb")));
    img = openJpeg(fp, 630, &w, &h);
    fclose(fp);
    breakCaptcha(img, w, h);
    free(img);
    return 0;
}
