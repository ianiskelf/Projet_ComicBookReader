#include "mainwindow.h"
#include "./ui_mainwindow.h"

// On utilise le logiciel Qt_Creator pour produire une interface 
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
