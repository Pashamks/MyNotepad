#include "about_window.h"
#include "ui_about_window.h"

about_window::about_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about_window)
{
    ui->setupUi(this);
}

about_window::~about_window()
{
    delete ui;
}
