#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <string>

#include <cairo.h>

#include "app.h"
#include "backend/cairo.h"
#include "backend/sfml.h"

int main(int argc, char **argv) {
    int size = (argc>=2)?atoi(argv[1]):500;
    int npoints = (argc>=3)?atoi(argv[2]):10;

    if (size <= 0) return -1;

    srand(time(NULL));

    printf("running..\n");

    // CairoBackend backend("frames/frame.%03d.png", 500, 50);
    // App app(backend);
    // app.randomPoints(10);
    // app.run();

    SfmlBackend backend(size, 50);
    App app(backend);
    app.randomPoints(npoints);
    backend.onLeftClick([&](double x, double y) {
        printf("left click at %g, %g\n", x, y);
        app.addPoint(x, y);
        app.run();
    });
    backend.onRightClick([&](double x, double y) {
        printf("right click at %g, %g\n", x, y);
        app.removePoint(x, y);
        app.run();
    });
    backend.start();
}
