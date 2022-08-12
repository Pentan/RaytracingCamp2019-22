#ifndef PINKYPI_CONFIG_H
#define PINKYPI_CONFIG_H

#include <string>
#include <pinkycore/pptypes.h>

namespace PinkyPi {
    class Config {
    public:
        int width;
        int height;
        
        int frames;
        double framesPerSecond;
        
        double exposureSecond;
        int exposureSlice;
        
        int samplesPerPixel;
        int pixelSubSamples;
        
        int minDepth;
        int maxDepth;
        float minRussianRouletteCutOff;
        
        int framebufferStockCount;
        int tileSize;
        bool scrambleTile;
        
        double limitSec;
        double progressIntervalSec;
        int maxThreads;
        
        bool quietProgress;
        bool waitUntilFinish;
        
        std::string inputFile;
        std::string outputDir;
        std::string outputName;
        std::string outputExt;

    public:
        Config():
            width(320),
            height(270),
            frames(1),
            framesPerSecond(30.0),
            exposureSecond(0.0),
            exposureSlice(1),
            samplesPerPixel(4),
            pixelSubSamples(2),
            minDepth(1),
            maxDepth(4),
            minRussianRouletteCutOff(0.005f),
            framebufferStockCount(3),
            tileSize(64),
            scrambleTile(true),
            limitSec(60.0),
            progressIntervalSec(-1.0),
            maxThreads(0),
            quietProgress(false),
            waitUntilFinish(true),
            inputFile(""),
            outputDir("output"),
            outputName("output"),
            outputExt("png")
        {
        }
        
        bool load(const std::string& path);
    };
}

#endif
