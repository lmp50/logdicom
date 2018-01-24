#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void slotOpenFile();
    void slotOpenFolder();
    void slotExit();

    void slotContents();
    void slotAbout();

private:
    Ui::MainWindow *ui;
    bool readDataElement(QByteArray line, QFile *file, int &iDataElementNo, quint64 &i64Pos);
};

#endif // MAINWINDOW_H
