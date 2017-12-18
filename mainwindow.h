#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include <QActionGroup>
#include <QAction>
#include <QLabel>
#include <QToolBar>
#include <QStatusBar>
#include <QFormLayout>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QEvent>
#include "student.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Students all;
    bool is_changed;
    QLineEdit *mainnoline;
    QLineEdit *mainnameline;
    QComboBox *mainsexline;
    QDateEdit *maindateline;
    QLineEdit *mainplaceline;
    QLineEdit *mainmajorline;
    QComboBox *mainsortline;
    QComboBox *mainorderline;

public slots:
    void OpenActionTriggered();
    void NewActionTriggered();
    void SaveActionTriggered();
    void AddActionTriggered();
    void ModifyActionTriggered();
    void DeleteActionTriggered(); 
    void SortActionTriggered();
    void AboutActionTriggered();
    void AddInfo();
    void ModifyInfo();
    void SortInfo();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    void NewWindow(QString *info, int lineno); //lineno=-1 for add, else for modify
    void LoadTable();
    void SaveToFile(const char *Log);
};

#endif // MAINWINDOW_H
