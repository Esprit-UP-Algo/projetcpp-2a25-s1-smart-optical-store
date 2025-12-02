#ifndef FOURNISSEURWINDOW_H
#define FOURNISSEURWINDOW_H

#include <QMainWindow>
#include "fournisseur.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FournisseurWindow;
}
QT_END_NAMESPACE

class FournisseurWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FournisseurWindow(QWidget *parent = nullptr);
    ~FournisseurWindow();

    // Singleton
    static FournisseurWindow* getInstance(const QString &role = QString(), QWidget *parent = nullptr);
    static FournisseurWindow* instance;

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_tableWidget_2_itemClicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_38_clicked();      // SMS fournisseur

    void on_pushButton_modifier_3_clicked(); // <<==== RECHERCHE PAR ID

private:
    Ui::FournisseurWindow *ui;
    Fournisseur Ftmp;
    int selectedId;                            // ID de la ligne sélectionnée
    QString userRole;                          // Role de l'utilisateur connecté

    void afficherFournisseurs();
    void ecrireHistorique(const QString &action, int id, const QString &nomEntreprise);
    void configureRoleBasedAccess();           // Configure l'accès basé sur le rôle

    // ==== Fonction SMS fournisseur (Twilio) ====
    bool envoyerSmsFournisseur(const QString &numero, const QString &message);
};

#endif // FOURNISSEURWINDOW_H
