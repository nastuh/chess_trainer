#include <QApplication>
#include "gameview.h"
#include "constants.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Chess Game");
    app.setStyle("fusion");

    GameView window;
    window.setWindowTitle("Chess Game");
    window.show();

    return app.exec();
}
