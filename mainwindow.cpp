#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // init settings
    move(screen()->geometry().center() -frameGeometry().center());
    ui->listView->setToolTip("Здесь отображается результат поиска");

    // Инициализация файловой модели
    myFileModel = new QFileSystemModel(this);
    // Установка отображения всех файлов, всключая скрытые. NoDotAndDotDot убирает странные . и .. во всех папках
    myFileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);

    // Поиск пути к профилю текущего пользователя
    struct passwd *pw = getpwuid(getuid());
    // Установка названия окна
    this->setWindowTitle("Файлы пользователя: " + QString::fromStdString(pw->pw_name));

    // Установка корневой директории
    const char *homedir = pw->pw_dir;
    myFileModel->setRootPath(QDir::cleanPath(homedir));
    ui->treeView->setModel(myFileModel);


    // Установка отображаемой директории
    if (homedir != NULL){
        rootPath = QString::fromStdString(homedir);
    }
    else {
        rootPath = QDir::currentPath();
    }
    QModelIndex rootObjectIndex = myFileModel->index(QDir::cleanPath(rootPath));
    ui->treeView->setRootIndex(rootObjectIndex);

    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonFind_clicked()
{
    QStringListModel *modelFind = new QStringListModel(this);
    QStringList listFind;

    QDirIterator it(rootPath, QStringList() << ui->lineEdit->text(), (QDir::AllEntries | QDir::Hidden), QDirIterator::Subdirectories);
    while(it.hasNext()){
        listFind.append(it.next());
    }
    modelFind->setStringList(listFind);
    ui->listView->setModel(modelFind);
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QModelIndex currentObjectIndex = myFileModel->index(QDir::cleanPath(index.data(Qt::DisplayRole).toString()));
    ui->treeView->setCurrentIndex(currentObjectIndex);
}


void MainWindow::on_lineEdit_returnPressed()
{
    emit MainWindow::on_pushButtonFind_clicked();
}

