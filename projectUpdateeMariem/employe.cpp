#include "employe.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlError>

Employe::Employe()
{
    id_employe = 0;
    nom = "";
    prenom = "";
    email = "";
    telephone = "";
    d_naissance = QDate::currentDate();
    adresse = "";
    n_enfant = 0;
    poste = "";
    salaire = 0.0;
    dispo = "O";
}

Employe::Employe(int id, const QString &nom, const QString &prenom, const QString &email, 
                 const QString &telephone, const QDate &dateNaissance, const QString &adresse, 
                 int nEnfant, const QString &poste, double salaire, const QString &dispo)
{
    this->id_employe = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->telephone = telephone;
    this->d_naissance = dateNaissance;
    this->adresse = adresse;
    this->n_enfant = nEnfant;
    this->poste = poste;
    this->salaire = salaire;
    this->dispo = dispo;
}

bool Employe::ajouter()
{
    // Validate disponibilite (should be 'O' or 'N')
    QString disp = dispo.toUpper().trimmed();
    if (disp != "O" && disp != "N") {
        qDebug() << "Erreur: Disponibilite doit être 'O' ou 'N'";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur: connexion base de données invalide ou fermée";
        return false;
    }

    bool inTransaction = false;
    if (db.driver()->hasFeature(QSqlDriver::Transactions)) {
        if (!db.transaction()) {
            qDebug() << "Attention: impossible de démarrer une transaction:" << db.lastError().text();
        } else {
            inTransaction = true;
        }
    }

    QSqlQuery query(db);
    // Try with uppercase first (Oracle standard for unquoted identifiers)
    // Use correct column names: D_NAISSANCE, N_ENFANT, DISPO
    QString sql = "INSERT INTO EMPLOYE (NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO) "
                  "VALUES (:nom, :prenom, :email, :telephone, TO_DATE(:date_naissance, 'YYYY-MM-DD'), :adresse, :poste, :salaire, :n_enfant, :dispo)";
    query.prepare(sql);

    // Required fields should not be NULL
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    // Optional fields - use NULL when empty
    query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
    query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
    query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
    query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
    query.bindValue(":salaire", salaire);
    query.bindValue(":n_enfant", n_enfant);
    query.bindValue(":dispo", disp);

    qDebug() << "Attempting to insert employee:";
    qDebug() << "  Nom:" << nom;
    qDebug() << "  Prenom:" << prenom;
    qDebug() << "  Email:" << email;
    qDebug() << "  Date:" << (d_naissance.isValid() ? d_naissance.toString("yyyy-MM-dd") : "Invalid");
    qDebug() << "  Telephone:" << telephone;
    qDebug() << "  Adresse:" << adresse;
    qDebug() << "  Poste:" << poste;
    qDebug() << "  Salaire:" << salaire;
    qDebug() << "  Nombre_enfants:" << n_enfant;
    qDebug() << "  Disponibilite:" << disp;

    auto handleError = [&](const QSqlError& error, const QString& context) {
        QString errorMsg = error.text();
        QString errorCode = error.nativeErrorCode();
        qDebug() << "=== ERREUR LORS DE L'AJOUT ===";
        qDebug() << "Contexte:" << context;
        qDebug() << "Message d'erreur:" << errorMsg;
        qDebug() << "Code d'erreur natif:" << errorCode;
        qDebug() << "Type d'erreur:" << error.type();
        qDebug() << "SQL préparé:" << sql;
        qDebug() << "Valeurs liées:" << query.boundValues();
        if (inTransaction) {
            db.rollback();
            qDebug() << "Transaction annulée";
        }
    };

    bool execSuccess = query.exec();
    if (!execSuccess) {
        QSqlError error = query.lastError();
        QString errorMsg = error.text();
        QString errorCode = error.nativeErrorCode();

        // If column not found error (ORA-00904), try with D_NAISSANCE instead of DATE_NAISSANCE
        bool isColumnNotFoundError = errorMsg.contains("ORA-00904", Qt::CaseInsensitive) ||
                                     errorCode.contains("00904", Qt::CaseInsensitive) ||
                                     errorMsg.contains("invalid identifier", Qt::CaseInsensitive);

        if (isColumnNotFoundError) {
            qDebug() << "Tentative avec colonnes corrigées (N_ENFANT, DISPO)...";
            query.clear();
            sql = "INSERT INTO EMPLOYE (NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO) "
                  "VALUES (:nom, :prenom, :email, :telephone, TO_DATE(:date_naissance, 'YYYY-MM-DD'), :adresse, :poste, :salaire, :n_enfant, :dispo)";
            query.prepare(sql);
            query.bindValue(":nom", nom);
            query.bindValue(":prenom", prenom);
            query.bindValue(":email", email);
            query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
            query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
            query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
            query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
            query.bindValue(":salaire", salaire);
            query.bindValue(":n_enfant", n_enfant);
            query.bindValue(":dispo", disp);

            if (!query.exec()) {
                // Try with lowercase table name
                query.clear();
                sql = "INSERT INTO employe (nom, prenom, email, telephone, d_naissance, adresse, poste, salaire, n_enfant, dispo) "
                      "VALUES (:nom, :prenom, :email, :telephone, TO_DATE(:date_naissance, 'YYYY-MM-DD'), :adresse, :poste, :salaire, :n_enfant, :dispo)";
                query.prepare(sql);
                query.bindValue(":nom", nom);
                query.bindValue(":prenom", prenom);
                query.bindValue(":email", email);
                query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
                query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
                query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
                query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
                query.bindValue(":salaire", salaire);
                query.bindValue(":n_enfant", n_enfant);
                query.bindValue(":dispo", disp);
                
                if (!query.exec()) {
                    handleError(query.lastError(), "Insertion avec colonnes corrigées");
                    return false;
                }
            }
        } else {
            // If table not found error (ORA-00942), try with quoted identifiers (case-sensitive)
            bool isTableNotFoundError = errorMsg.contains("table", Qt::CaseInsensitive) ||
                                        errorMsg.contains("ORA-00942", Qt::CaseInsensitive) ||
                                        errorCode.contains("00942", Qt::CaseInsensitive) ||
                                        errorMsg.contains("does not exist", Qt::CaseInsensitive) ||
                                        errorMsg.contains("object", Qt::CaseInsensitive);

            if (isTableNotFoundError) {
                qDebug() << "Tentative avec noms de table/colonnes entre guillemets...";
                query.clear();
                sql = "INSERT INTO \"Employe\" (\"Nom\", \"Prenom\", \"Email\", \"Telephone\", \"D_Naissance\", \"Adresse\", \"Poste\", \"Salaire\", \"N_Enfant\", \"Dispo\") "
                      "VALUES (:nom, :prenom, :email, :telephone, TO_DATE(:date_naissance, 'YYYY-MM-DD'), :adresse, :poste, :salaire, :n_enfant, :dispo)";
                query.prepare(sql);
                query.bindValue(":nom", nom);
                query.bindValue(":prenom", prenom);
                query.bindValue(":email", email);
                query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
                query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
                query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
                query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
                query.bindValue(":salaire", salaire);
                query.bindValue(":n_enfant", n_enfant);
                query.bindValue(":dispo", disp);

                if (!query.exec()) {
                    handleError(query.lastError(), "Insertion avec identifiants entre guillemets");
                    return false;
                }
            } else {
                handleError(error, "Insertion standard");
                return false;
            }
        }
    }

    if (inTransaction) {
        if (!db.commit()) {
            qDebug() << "Erreur lors du commit:" << db.lastError().text();
            db.rollback();
            return false;
        }
        qDebug() << "Transaction validée";
    }

    // Retrieve generated ID using CURRVAL (same session) - try both uppercase and quoted
    QSqlQuery idQuery(db);
    QString seqQuery = "SELECT seq_employe.CURRVAL FROM dual";
    if (idQuery.exec(seqQuery) && idQuery.next()) {
        id_employe = idQuery.value(0).toInt();
        qDebug() << "✅ ID généré pour l'employé:" << id_employe;
    } else {
        // Try alternative sequence name
        idQuery.clear();
        seqQuery = "SELECT \"seq_employe\".CURRVAL FROM dual";
        if (idQuery.exec(seqQuery) && idQuery.next()) {
            id_employe = idQuery.value(0).toInt();
            qDebug() << "✅ ID généré pour l'employé:" << id_employe;
        } else {
            // Try with uppercase sequence
            idQuery.clear();
            seqQuery = "SELECT SEQ_EMPLOYE.CURRVAL FROM dual";
            if (idQuery.exec(seqQuery) && idQuery.next()) {
                id_employe = idQuery.value(0).toInt();
                qDebug() << "✅ ID généré pour l'employé:" << id_employe;
            } else {
                // Last resort: try to get the last inserted ID
                idQuery.clear();
                QVariant lastId = query.lastInsertId();
                if (lastId.isValid()) {
                    id_employe = lastId.toInt();
                    qDebug() << "✅ ID récupéré via lastInsertId:" << id_employe;
                } else {
                    qDebug() << "⚠️ Attention: impossible de récupérer l'ID généré. Erreur:" << idQuery.lastError().text();
                    // Don't fail the operation if ID retrieval fails - the insert was successful
                }
            }
        }
    }

    qDebug() << "✅ Employé ajouté avec succès - ID:" << id_employe;
    return true;
}

bool Employe::modifier()
{
    // Validate disponibilite (should be 'O' or 'N')
    QString disp = dispo.toUpper().trimmed();
    if (disp != "O" && disp != "N") {
        qDebug() << "Erreur: Disponibilite doit être 'O' ou 'N'";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur: connexion base de données invalide ou fermée";
        return false;
    }

    bool inTransaction = false;
    if (db.driver()->hasFeature(QSqlDriver::Transactions)) {
        if (!db.transaction()) {
            qDebug() << "Attention: impossible de démarrer une transaction (modifier):" << db.lastError().text();
        } else {
            inTransaction = true;
        }
    }

    QSqlQuery query(db);
    QString sql = "UPDATE EMPLOYE SET NOM=:nom, PRENOM=:prenom, EMAIL=:email, TELEPHONE=:telephone, D_NAISSANCE=TO_DATE(:date_naissance, 'YYYY-MM-DD'), "
                  "ADRESSE=:adresse, POSTE=:poste, SALAIRE=:salaire, N_ENFANT=:n_enfant, DISPO=:dispo WHERE ID_EMPLOYE=:id";
    query.prepare(sql);

    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
    query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
    query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
    query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
    query.bindValue(":salaire", salaire);
    query.bindValue(":n_enfant", n_enfant);
    query.bindValue(":dispo", disp);

    if (!query.exec()) {
        QSqlError error = query.lastError();
        QString errorMsg = error.text();
        QString errorCode = error.nativeErrorCode();
        
        // Check for column not found error
        bool isColumnNotFoundError = errorMsg.contains("ORA-00904", Qt::CaseInsensitive) ||
                                    errorCode.contains("00904", Qt::CaseInsensitive) ||
                                    errorMsg.contains("invalid identifier", Qt::CaseInsensitive);
        
        if (isColumnNotFoundError) {
            // Already using correct column names, try with lowercase
            query.clear();
            sql = "UPDATE employe SET nom=:nom, prenom=:prenom, email=:email, telephone=:telephone, d_naissance=TO_DATE(:date_naissance, 'YYYY-MM-DD'), "
                  "adresse=:adresse, poste=:poste, salaire=:salaire, n_enfant=:n_enfant, dispo=:dispo WHERE id_employe=:id";
            query.prepare(sql);
            query.bindValue(":id", id_employe);
            query.bindValue(":nom", nom);
            query.bindValue(":prenom", prenom);
            query.bindValue(":email", email);
            query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
            query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
            query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
            query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
            query.bindValue(":salaire", salaire);
            query.bindValue(":n_enfant", n_enfant);
            query.bindValue(":dispo", disp);
            
            if (!query.exec()) {
                qDebug() << "Erreur lors de la modification (lowercase):" << query.lastError().text() << "Code:" << query.lastError().nativeErrorCode();
                if (inTransaction) {
                    db.rollback();
                }
                return false;
            }
        } else {
            // Try with quoted identifiers if table not found
            bool isTableNotFoundError = errorMsg.contains("table", Qt::CaseInsensitive) ||
                                        errorMsg.contains("ORA-00942", Qt::CaseInsensitive) ||
                                        errorCode.contains("00942", Qt::CaseInsensitive);
            
            if (isTableNotFoundError) {
                query.clear();
                sql = "UPDATE \"Employe\" SET \"Nom\"=:nom, \"Prenom\"=:prenom, \"Email\"=:email, \"Telephone\"=:telephone, \"D_Naissance\"=TO_DATE(:date_naissance, 'YYYY-MM-DD'), "
                      "\"Adresse\"=:adresse, \"Poste\"=:poste, \"Salaire\"=:salaire, \"N_Enfant\"=:n_enfant, \"Dispo\"=:dispo WHERE \"ID_Employe\"=:id";
                query.prepare(sql);
                query.bindValue(":id", id_employe);
                query.bindValue(":nom", nom);
                query.bindValue(":prenom", prenom);
                query.bindValue(":email", email);
                query.bindValue(":telephone", telephone.isEmpty() ? QVariant(QVariant::String) : QVariant(telephone));
                query.bindValue(":date_naissance", d_naissance.isValid() ? QVariant(d_naissance.toString("yyyy-MM-dd")) : QVariant());
                query.bindValue(":adresse", adresse.isEmpty() ? QVariant(QVariant::String) : QVariant(adresse));
                query.bindValue(":poste", poste.isEmpty() ? QVariant(QVariant::String) : QVariant(poste));
                query.bindValue(":salaire", salaire);
                query.bindValue(":n_enfant", n_enfant);
                query.bindValue(":dispo", disp);
                
                if (!query.exec()) {
                    qDebug() << "Erreur lors de la modification:" << query.lastError().text() << "Code:" << query.lastError().nativeErrorCode();
                    if (inTransaction) {
                        db.rollback();
                    }
                    return false;
                }
            } else {
                qDebug() << "Erreur lors de la modification:" << error.text() << "Code:" << errorCode;
                qDebug() << "SQL:" << sql;
                qDebug() << "Valeurs:" << query.boundValues();
                if (inTransaction) {
                    db.rollback();
                    qDebug() << "Transaction annulée (modifier)";
                }
                return false;
            }
        }
    }

    if (inTransaction) {
        if (!db.commit()) {
            qDebug() << "Erreur lors du commit (modifier):" << db.lastError().text();
            db.rollback();
            return false;
        }
        qDebug() << "Transaction validée (modifier)";
    }

    qDebug() << "Employé modifié avec succès";
    return true;
}

bool Employe::supprimer(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur: connexion base de données invalide ou fermée";
        return false;
    }

    bool inTransaction = false;
    if (db.driver()->hasFeature(QSqlDriver::Transactions)) {
        if (!db.transaction()) {
            qDebug() << "Attention: impossible de démarrer une transaction (supprimer):" << db.lastError().text();
        } else {
            inTransaction = true;
        }
    }

    // Mettre à NULL l'id_employe dans les ventes associées (if table exists)
    QSqlQuery updateQuery(db);
    QString updateSql = "UPDATE VENTE SET ID_EMPLOYE = NULL WHERE ID_EMPLOYE = :id";
    if (!updateQuery.prepare(updateSql)) {
        qDebug() << "Warning: Could not prepare update ventes query";
    } else {
        updateQuery.bindValue(":id", id);
        if (!updateQuery.exec()) {
            // Try with quoted identifiers
            updateQuery.clear();
            updateSql = "UPDATE \"Vente\" SET \"ID_Employe\" = NULL WHERE \"ID_Employe\" = :id";
            updateQuery.prepare(updateSql);
            updateQuery.bindValue(":id", id);
            updateQuery.exec(); // Don't fail if this doesn't work
        }
    }

    QSqlQuery query(db);
    QString sql = "DELETE FROM EMPLOYE WHERE ID_EMPLOYE=:id";
    query.prepare(sql);
    query.bindValue(":id", id);

    if (!query.exec()) {
        QSqlError error = query.lastError();
        QString errorMsg = error.text();
        QString errorCode = error.nativeErrorCode();
        
        // Try with quoted identifiers if table not found
        bool isTableNotFoundError = errorMsg.contains("table", Qt::CaseInsensitive) ||
                                    errorMsg.contains("ORA-00942", Qt::CaseInsensitive) ||
                                    errorCode.contains("00942", Qt::CaseInsensitive);
        
        if (isTableNotFoundError) {
            query.clear();
            sql = "DELETE FROM \"Employe\" WHERE \"ID_Employe\"=:id";
            query.prepare(sql);
            query.bindValue(":id", id);
            
            if (!query.exec()) {
                qDebug() << "Erreur lors de la suppression:" << query.lastError().text() << "Code:" << query.lastError().nativeErrorCode();
                if (inTransaction) {
                    db.rollback();
                }
                return false;
            }
        } else {
            qDebug() << "Erreur lors de la suppression:" << error.text() << "Code:" << errorCode;
            qDebug() << "SQL:" << sql;
            if (inTransaction) {
                db.rollback();
                qDebug() << "Transaction annulée (supprimer)";
            }
            return false;
        }
    }

    if (inTransaction) {
        if (!db.commit()) {
            qDebug() << "Erreur lors du commit (supprimer):" << db.lastError().text();
            db.rollback();
            return false;
        }
        qDebug() << "Transaction validée (supprimer)";
    }

    qDebug() << "Employé supprimé avec succès";
    return true;
}

QSqlQueryModel* Employe::afficher()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Database not connected in afficher()";
        return new QSqlQueryModel(); // Return empty model
    }
    
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query(db);
    
    // Use explicit column order to match database schema
    // Use correct column names: D_NAISSANCE, N_ENFANT, DISPO
    QString sql = "SELECT ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO FROM EMPLOYE ORDER BY ID_EMPLOYE";
    
    if (!query.exec(sql)) {
        qDebug() << "⚠️ Error with uppercase query:" << query.lastError().text();
        qDebug() << "Trying mixed case table name...";
        query.clear();
        sql = "SELECT ID_Employe, Nom, Prenom, Email, Telephone, D_Naissance, Adresse, Poste, Salaire, N_Enfant, Dispo FROM Employe ORDER BY ID_Employe";
        if (!query.exec(sql)) {
            qDebug() << "⚠️ Error with mixed case query:" << query.lastError().text();
            qDebug() << "Trying quoted identifiers...";
            query.clear();
            sql = "SELECT \"ID_Employe\", \"Nom\", \"Prenom\", \"Email\", \"Telephone\", \"D_Naissance\", \"Adresse\", \"Poste\", \"Salaire\", \"N_Enfant\", \"Dispo\" FROM \"Employe\" ORDER BY \"ID_Employe\"";
            query.exec(sql);
        }
    }
    
    model->setQuery(query);
    
    // Final error check
    if (model->lastError().isValid()) {
        qDebug() << "❌ Final error in afficher():" << model->lastError().text();
        qDebug() << "Database error:" << model->lastError().databaseText();
        qDebug() << "Driver error:" << model->lastError().driverText();
    } else {
        qDebug() << "✅ Query successful, found" << model->rowCount() << "employees";
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Nb Enfants"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));

    return model;
}

QSqlQueryModel* Employe::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString sql = "SELECT ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO FROM EMPLOYE "
                  "WHERE ID_EMPLOYE LIKE :critere OR "
                  "NOM LIKE :critere OR "
                  "PRENOM LIKE :critere OR "
                  "EMAIL LIKE :critere OR "
                  "TELEPHONE LIKE :critere OR "
                  "POSTE LIKE :critere OR "
                  "DISPO LIKE :critere";
    query.prepare(sql);
    query.bindValue(":critere", "%" + critere + "%");
    
    if (!query.exec()) {
        // Try with mixed case
        query.clear();
        sql = "SELECT ID_Employe, Nom, Prenom, Email, Telephone, D_Naissance, Adresse, Poste, Salaire, N_Enfant, Dispo FROM Employe "
              "WHERE ID_Employe LIKE :critere OR "
              "Nom LIKE :critere OR "
              "Prenom LIKE :critere OR "
              "Email LIKE :critere OR "
              "Telephone LIKE :critere OR "
              "Poste LIKE :critere OR "
              "Dispo LIKE :critere";
        query.prepare(sql);
        query.bindValue(":critere", "%" + critere + "%");
        query.exec();
    }
    
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Nb Enfants"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));

    return model;
}

// Rechercher un employé par ID
bool Employe::rechercherParId(int id)
{
    QSqlQuery query;
    QString sql = "SELECT ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO FROM EMPLOYE WHERE ID_EMPLOYE=:id";
    query.prepare(sql);
    query.bindValue(":id", id);

    if (!query.exec()) {
        // Try with mixed case
        query.clear();
        sql = "SELECT ID_Employe, Nom, Prenom, Email, Telephone, D_Naissance, Adresse, Poste, Salaire, N_Enfant, Dispo FROM Employe WHERE ID_Employe=:id";
        query.prepare(sql);
        query.bindValue(":id", id);
        query.exec();
    }
    
    if (query.next()) {
        // Column order: ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO
        this->id_employe = query.value(0).toInt();
        this->nom = query.value(1).toString();
        this->prenom = query.value(2).toString();
        this->email = query.value(3).toString();
        this->telephone = query.value(4).toString();
        this->d_naissance = query.value(5).toDate();
        this->adresse = query.value(6).toString();
        this->poste = query.value(7).toString();
        this->salaire = query.value(8).toDouble();
        this->n_enfant = query.value(9).toInt();
        this->dispo = query.value(10).toString();
        return true;
    }
    return false;
}

// Rechercher par nom
QSqlQueryModel* Employe::rechercherParNom(const QString &nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString sql = "SELECT ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO FROM EMPLOYE WHERE NOM LIKE :nom OR PRENOM LIKE :nom OR EMAIL LIKE :nom";
    query.prepare(sql);
    query.bindValue(":nom", "%" + nom + "%");
    
    if (!query.exec()) {
        // Try with mixed case
        query.clear();
        sql = "SELECT ID_Employe, Nom, Prenom, Email, Telephone, D_Naissance, Adresse, Poste, Salaire, N_Enfant, Dispo FROM Employe WHERE Nom LIKE :nom OR Prenom LIKE :nom OR Email LIKE :nom";
        query.prepare(sql);
        query.bindValue(":nom", "%" + nom + "%");
        query.exec();
    }
    
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Nb Enfants"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));

    return model;
}

// Trier par nom
QSqlQueryModel* Employe::trierParNom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString sql = "SELECT ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO FROM EMPLOYE ORDER BY NOM ASC";
    model->setQuery(sql);
    
    // If query fails, try with mixed case
    if (model->lastError().isValid()) {
        sql = "SELECT ID_Employe, Nom, Prenom, Email, Telephone, D_Naissance, Adresse, Poste, Salaire, N_Enfant, Dispo FROM Employe ORDER BY Nom ASC";
        model->setQuery(sql);
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Nb Enfants"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));

    return model;
}

// Trier par salaire
QSqlQueryModel* Employe::trierParSalaire()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString sql = "SELECT ID_EMPLOYE, NOM, PRENOM, EMAIL, TELEPHONE, D_NAISSANCE, ADRESSE, POSTE, SALAIRE, N_ENFANT, DISPO FROM EMPLOYE ORDER BY SALAIRE DESC";
    model->setQuery(sql);
    
    // If query fails, try with mixed case
    if (model->lastError().isValid()) {
        sql = "SELECT ID_Employe, Nom, Prenom, Email, Telephone, D_Naissance, Adresse, Poste, Salaire, N_Enfant, Dispo FROM Employe ORDER BY Salaire DESC";
        model->setQuery(sql);
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Nb Enfants"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));

    return model;
}

QSqlQueryModel* Employe::afficherVentesParEmploye(int idEmploye)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString sql = "SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                  "v.date_vente, v.prix_ttc, v.statut_vente, v.statut_paiement "
                  "FROM vente v "
                  "LEFT JOIN clients c ON v.id_client = c.id_client "
                  "WHERE v.id_employe = :id_employe "
                  "ORDER BY v.date_vente DESC";
    
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id_employe", idEmploye);
    
    if (!query.exec()) {
        // Try with uppercase
        query.clear();
        sql = "SELECT v.ID_VENTE, c.NOM || ' ' || c.PRENOM AS CLIENT, "
              "v.DATE_VENTE, v.PRIX_TTC, v.STATUT_VENTE, v.STATUT_PAIEMENT "
              "FROM VENTE v "
              "LEFT JOIN CLIENT c ON v.ID_CLIENT = c.ID_CLIENT "
              "WHERE v.ID_EMPLOYE = :id_employe "
              "ORDER BY v.DATE_VENTE DESC";
        query.prepare(sql);
        query.bindValue(":id_employe", idEmploye);
        query.exec();
    }
    
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Vente"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));

    return model;
}

double Employe::calculerCommission(int idEmploye, const QDate &debut, const QDate &fin, double tauxCommission)
{
    QSqlQuery query;
    double totalVentes = 0.0;

    QString sql = "SELECT SUM(prix_ttc) FROM vente "
                  "WHERE id_employe = :id_employe "
                  "AND date_vente BETWEEN :debut AND :fin "
                  "AND statut_paiement = 'Payé'";
    query.prepare(sql);
    query.bindValue(":id_employe", idEmploye);
    query.bindValue(":debut", debut);
    query.bindValue(":fin", fin);

    if (!query.exec()) {
        // Try with uppercase
        query.clear();
        sql = "SELECT SUM(PRIX_TTC) FROM VENTE "
              "WHERE ID_EMPLOYE = :id_employe "
              "AND DATE_VENTE BETWEEN :debut AND :fin "
              "AND STATUT_PAIEMENT = 'Payé'";
        query.prepare(sql);
        query.bindValue(":id_employe", idEmploye);
        query.bindValue(":debut", debut);
        query.bindValue(":fin", fin);
        query.exec();
    }

    if (query.next()) {
        totalVentes = query.value(0).toDouble();
    }

    return totalVentes * tauxCommission;
}
