#ifndef NOTE_WINDOW_H
#define NOTE_WINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include<QPrintDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Note_Window; }
QT_END_NAMESPACE

class Note_Window : public QMainWindow
{
    Q_OBJECT

public:
    Note_Window(QWidget *parent = nullptr);
    ~Note_Window();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actioncertificate_triggered();

    void on_actionSave_triggered();

    void on_my_text_space_textChanged();

    void ShowConMen(const QPoint &point);

private:
    Ui::Note_Window *ui;
    QString file_now = "";
};
#endif // NOTE_WINDOW_H
