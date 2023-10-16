#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLocale>
#include <QTranslator>
#include <QApplication>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QScreen>
#include <QScroller>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QtWidgets>

#include <unistd.h>
#include <sys/types.h>

#include <pwd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QFileSystemModel* myFileModel;

private slots:
    void on_pushButtonFind_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;



    QString rootPath;
    QStringList filters;

};
#endif // MAINWINDOW_H
