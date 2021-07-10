#include "note_window.h"
#include "ui_note_window.h"
#include "about_window.h"

Note_Window::Note_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Note_Window)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->my_text_space);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(ShowConMen(QPoint)));
        ui->actionUndo->setDisabled(true);
        ui->actionRedo->setDisabled(true);
}
bool temp_un = 0, temp_re=0;
Note_Window::~Note_Window()
{
    delete ui;
}

void Note_Window:: ShowConMen(const QPoint &point)
{
    QMenu *menu = new QMenu(this);
    QAction *Copy = new QAction("Copy\tCtrl+C", this);
    connect(Copy, &QAction::triggered, this, &Note_Window::on_actionCopy_triggered);
    QAction *Paste = new QAction("Paste\tCtrl+V", this);
    connect(Paste, &QAction::triggered, this, &Note_Window::on_actionPaste_triggered);
    QAction *Undo = new QAction("Undo\tCtrl+F", this);
    connect(Undo, &QAction::triggered, this, &Note_Window::on_actionUndo_triggered);
    QAction *Redo = new QAction("Redo\tCtrl+J", this);
    connect(Redo, &QAction::triggered, this, &Note_Window::on_actionRedo_triggered);
    QAction *Cut = new QAction("Cut\tCtrl+G", this);
    connect(Cut, &QAction::triggered, this, &Note_Window::on_actionCut_triggered);
    if(temp_un==0){
       Undo->setDisabled(true);
    }
    if(temp_un){
        Undo->setEnabled(true);
    }
    if(temp_re==0){
       Redo->setDisabled(true);
    }
    if(temp_re){
        Redo->setEnabled(true);
    }
    menu->addAction(Copy);
    menu->addAction(Paste);
    menu->addAction(Undo);
    menu->addAction(Redo);
    menu->addAction(Cut);
    menu->popup(mapToGlobal(point));
}

void Note_Window::on_actionNew_triggered()
{
    if(file_now!=""||ui->my_text_space->toPlainText()!="")
    {
        QMessageBox:: StandardButton val = QMessageBox::question(this, "Що робити?", "Зберегти зміни у минулому файлі?",
                              QMessageBox:: Yes |QMessageBox:: No);
        if(val==QMessageBox:: Yes)
        {
            on_actionSave_triggered();
        }

    }
    file_now.clear();
    ui->my_text_space->setText(QString());
    this->setWindowTitle("Note_Window");

}

void Note_Window::on_actionOpen_triggered()
{
    if(file_now!="")
    {
        QMessageBox:: StandardButton val = QMessageBox::question(this, "Що робити?", "Зберегти зміни у минулому файлі?",
                              QMessageBox:: Yes |QMessageBox:: No);
        if(val==QMessageBox:: Yes)
        {
            on_actionSave_triggered();
        }

    }
        QString FileName = QFileDialog::getOpenFileName(this,"Open the file ");
        QFile file(FileName);
        if(!file.open(QIODevice:: ReadOnly | QFile ::Text)){
            QMessageBox::warning(this, "Попередження!", "Не можемо відкрити файл : " + file.errorString());
            return;
        }
        file_now = FileName;
        QTextStream in(&file);
        QString text = in.readAll();
        ui->my_text_space->setText(text);
        this->setWindowTitle(file_now);
        file.close();

}

void Note_Window::on_actionSave_as_triggered()
{
    QString FileName = QFileDialog::getSaveFileName(this, tr("Save as"), "",
                                                    tr("Text Files (*.txt)"));
    QFile file(FileName);
    if(!file.open(QFile:: WriteOnly | QFile ::Text)){
        QMessageBox::warning(this, "Попередження!", "Не можемо зберегти файл : " + file.errorString());
        return;
    }
    file_now = FileName;
    QTextStream out(&file);
    QString text = ui->my_text_space->toPlainText();
    out << text;
    this->setWindowTitle(file_now);
    file.close();
}

void Note_Window::on_actionExit_triggered()
{
    QMessageBox:: StandardButton val = QMessageBox::question(this, "Що робити?", "Зберегти зміни у файлі?",
                              QMessageBox:: Yes |QMessageBox:: No);
        if(val==QMessageBox:: Yes)
        {
            on_actionSave_triggered();
        }
    QApplication:: quit();
}

void Note_Window::on_actionCopy_triggered()
{
    ui->my_text_space->copy();
}

void Note_Window::on_actionPaste_triggered()
{
    ui->my_text_space->paste();
}

void Note_Window::on_actionCut_triggered()
{
    ui->my_text_space->cut();
}

void Note_Window::on_actionUndo_triggered()
{
    ui->my_text_space->undo();
    ui->actionRedo->setEnabled(true);
    temp_re=1;
}

void Note_Window::on_actionRedo_triggered()
{
    ui->my_text_space->redo();
}

void Note_Window::on_actioncertificate_triggered()
{
   about_window window;
   window.setModal(true);
   window.exec();
}

void Note_Window::on_actionSave_triggered()
{
    if(file_now=="")
            on_actionSave_as_triggered();
    else{
        QFile file(file_now);
        if(!file.open(QFile:: WriteOnly | QFile ::Text)){
            QMessageBox::warning(this, "Попередження!", "Не можемо зберегти файл : " + file.errorString());
            return;
        }
        QTextStream out(&file);
        QString text = ui->my_text_space->toPlainText();
        out << text;
        file.flush();
        this->setWindowTitle(file_now);
        file.close();
    }

}

void Note_Window::on_my_text_space_textChanged()
{
    if(file_now!="")
     this->setWindowTitle(file_now + "*");
    else{
        this->setWindowTitle("Note_Window*");
    }
    ui->actionUndo->setEnabled(true);
    temp_un=1;
}
