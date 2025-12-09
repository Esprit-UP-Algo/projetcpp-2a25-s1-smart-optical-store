#ifndef GCLIENT1_H
#define GCLIENT1_H

// Include precompiled header first
#include "pch.h"

// Forward declare QtCharts classes
namespace QtCharts {
    class QChartView;
    class QChart;
    class QLineSeries;
    class QPieSeries;
    class QPieSlice;
    class QBarSeries;
    class QBarSet;
    class QBarCategoryAxis;
    class QValueAxis;
    class QDateTimeAxis;
    class QLegend;
}

QT_BEGIN_NAMESPACE
namespace Ui {
    class GestionClients;
}
QT_END_NAMESPACE

// In Qt 6, we'll use the QtCharts namespace explicitly in the implementation

class Gclient1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gclient1(QWidget *parent = nullptr);
    ~Gclient1();
    void loadClients();  // Méthode publique pour charger les clients
    
    // Singleton pattern
    static Gclient1* getInstance(QWidget *parent = nullptr);
    static Gclient1* instance;

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();
    void on_btnDelete_clicked();
    void on_btnExport_clicked();
    void on_tableWidgetClients_cellDoubleClicked(int row, int column);
    void on_lineEditSearch_textChanged(const QString &text);
    void on_comboBoxTri_currentIndexChanged(int index);
    void on_tabWidgetMain_currentChanged(int index);
    
    // Navigation buttons
    void on_b1_clicked(); // Stock
    void on_b2_clicked(); // Ventes
    void on_b3_clicked(); // Employes
    void on_b4_clicked(); // Clients (self)
    void on_b5_clicked(); // Fournisseur

private:
    Ui::GestionClients *ui;
    bool isEditing;
    int currentClientId;
    
    // Chart views
    QChartView *genderChartView;
    QChartView *ageChartView;
    QChartView *addressChartView;
    
    // UI elements for dashboard cards
    QLabel *lblTotalClientsValue;
    QLabel *lblGenderValue;
    
    // Dashboard methods
    void updateDashboard();
    void setupDashboardUI();
    void updateDashboardCards();
    void updateCharts();
    void updateGenderChart();
    void updateAgeDistributionChart();
    void updateAddressDistributionChart();
    
    // Data retrieval methods
    int getTotalClients();
    int getActiveClients();
    int getNewClientsThisMonth();
    int getAppointmentsCount();
    int getClientCount();
    int getInactiveClientCount();
    
    // Distribution methods
    QMap<QString, int> getGenderDistribution();
    QMap<QString, int> getAgeDistributionByDecade();
    QMap<QString, double> getAgeDistribution();
    QMap<QString, double> getAddressDistribution();
    QMap<QString, int> getClientGrowthData();
    
    // Helper methods for charts
    void setupChart(QChartView *chartView, QChart *chart, const QString &title = QString());
    QString getDecadeFromAge(int age);
    
    // UI update methods
    void updateStatistics();
    void updateClientGrowthChart();
    void updateGenderDistributionChart();
    
    // Helper methods
    QFrame* createStatCard(const QString &title, const QString &value, const QString &icon, const QColor &color);
    void applyShadowEffect(QWidget *widget);
    bool eventFilter(QObject *obj, QEvent *event) override;
    void clearForm();
    void fillForm(int row);
    void refreshTable(const QString &searchText = "", int sortIndex = -1);
    
    // Simple controls table
    void setupSimpleControlsTable();
    void refreshSimpleControlsTable();
    
    // Control management methods
    void onCallClient(const QString &phoneNumber);
    void onMessageClient(const QString &phoneNumber);
    void onRenewControl(int clientId, int row);
    QDate calculateNextControlDate(int clientId) const;
    QString getControlStatus(const QDate &nextControlDate) const;
    QString getControlStatusStyle(const QDate &nextControlDate) const;
    void showControlsContextMenu(const QPoint &pos);
    void updateStatusBar();
    
private:
    // Statistics display labels
    QLabel *lblAgeDistribution = nullptr;
    QLabel *lblAddressDistribution = nullptr;
};

#endif // GCLIENT1_H
