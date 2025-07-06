#include "main_window.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("DitherBoy Qt");
    resize(800, 600);
}

MainWindow::~MainWindow() {}
