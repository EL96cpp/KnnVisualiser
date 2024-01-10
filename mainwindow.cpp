#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new Model(this))
{
    ui->setupUi(this);
    setWindowTitle("KnnVisualiser");

    connect(this, &MainWindow::setKernelType, model, &Model::onSetKernelType);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_kernelComboBox_currentTextChanged(const QString &kernel_string) {

    qDebug() << kernel_string;

    if (kernel_string == "Прямоугольное") {

        emit setKernelType(KernelType::RECTANGULAR);

    } else if (kernel_string == "Треугольное") {

        emit setKernelType(KernelType::TRIANGLE);

    } else if (kernel_string == "Ядро Епанченкова") {

        emit setKernelType(KernelType::EPANCHENKOV);

    } else if (kernel_string == "Биквадратное") {

        emit setKernelType(KernelType::BIQUADRATIC);

    } else if (kernel_string == "Гауссовское") {

        emit setKernelType(KernelType::GAUSSIAN);

    }

}

