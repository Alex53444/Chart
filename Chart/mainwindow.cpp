#include "mainwindow.h"
#include "ChartForm.h"
#include "ChartFormSource.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chart");

    ChartForm *chart = new ChartForm();
    chart->Init();

    ChartFormSource *pSource1 = NULL;
    chart->CreateSource(&pSource1);
    pSource1->Init();

    ChartFormSource *pSource2 = NULL;
    chart->CreateSource(&pSource2);
    pSource2->Init();
    pSource2->SetRoot(true);

    setCentralWidget(chart);
}

MainWindow::~MainWindow()
{

}

