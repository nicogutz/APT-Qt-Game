#ifndef WORLDIMAGEFACTORY_H
#define WORLDIMAGEFACTORY_H

#include <QImage>
#include <QLabel>
#include <QRandomGenerator>
#include "noise/perlinnoise.h"

class WorldImageFactory {
public:
    static void createWorld(int level, int width, int height, double difficulty = 1.0) {
        QImage image(width, height, QImage::Format_Grayscale8);
        int seed = floor(QRandomGenerator::global()->bounded(1, 1000));
        PerlinNoise pn(seed);
        for(int i = 0; i < height; ++i) { // y
            auto pLine = image.scanLine(i);

            for(int j = 0; j < width; ++j) { // x
                double x = (double)j / ((double)width);
                double y = (double)i / ((double)height);

                double n = 0.9 * pn.noise(x * width / 10, y * height / 10, 0.4);

                // Map the values to the [0, 255] interval
                *pLine++ = floor(255 * n);
            }
        }

        image.save(QStringLiteral("./world_%1.png").arg(level), "png", -1);
    }
};

#endif // WORLDIMAGEFACTORY_H
