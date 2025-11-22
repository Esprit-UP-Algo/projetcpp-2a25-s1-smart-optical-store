#ifndef SALESSTATISTIQUE_H
#define SALESSTATISTIQUE_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
class QChart;
class QChartView;
class QPieSeries;
class QBarSeries;
QT_END_NAMESPACE

namespace Ui {
class SalesStatistique;
}

class SalesStatistique : public QDialog
{
    Q_OBJECT

public:
    explicit SalesStatistique(QWidget *parent = nullptr);
    ~SalesStatistique();
    
    void loadSalesStatistics();
    static SalesStatistique* getInstance(QWidget *parent = nullptr);
    static void refreshIfOpen();

private slots:
    void on_refreshButton_clicked();
    void on_exportButton_clicked();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::SalesStatistique *ui;
    void updateStatistics();
    static SalesStatistique* instance;
};

#endif // SALESSTATISTIQUE_H

