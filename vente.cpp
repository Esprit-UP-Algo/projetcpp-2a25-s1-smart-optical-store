#include "vente.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QDateTime>
#include <QStringList>

Vente::Vente()
{
    id_vente = 0;
    id_client = 0;
    id_employe = 0;
    date_vente = QDate::currentDate();
    prix_ttc = 0.0;
    prix_ht = 0.0;
    remise = 0.0;
    tva = 0.0;
    statut_vente = "En attente";
    statut_paiement = "Non payé";
    mode_paiement = "";
    date_livraison = QDate::currentDate().addDays(7);
}

Vente::Vente(int id, int idClient, int idEmploye, const QDate &dateVente, 
             double prixTtc, double prixHt, double remise, double tva, 
             const QString &statutVente, const QString &statutPaiement, 
             const QString &modePaiement, const QDate &dateLivraison)
{
    this->id_vente = id;
    this->id_client = idClient;
    this->id_employe = idEmploye;
    this->date_vente = dateVente;
    this->prix_ttc = prixTtc;
    this->prix_ht = prixHt;
    this->remise = remise;
    this->tva = tva;
    this->statut_vente = statutVente;
    this->statut_paiement = statutPaiement;
    this->mode_paiement = modePaiement;
    this->date_livraison = dateLivraison;
}

bool Vente::ajouter()
{
    lastError.clear();  // Clear previous error
    // First, verify that the client exists
    QSqlQuery clientCheck;
    QString clientSql = "SELECT id_client FROM clients WHERE id_client = :id_client";
    clientCheck.prepare(clientSql);
    clientCheck.bindValue(":id_client", id_client);
    
    if (!clientCheck.exec()) {
        qDebug() << "Erreur lors de la vérification du client:" << clientCheck.lastError().text();
        qDebug() << "Tentative avec CLIENTS...";
        clientCheck.clear();
        clientSql = "SELECT ID_CLIENT FROM CLIENTS WHERE ID_CLIENT = :id_client";
        clientCheck.prepare(clientSql);
        clientCheck.bindValue(":id_client", id_client);
        if (!clientCheck.exec()) {
            lastError = "Erreur lors de la vérification du client: " + clientCheck.lastError().text();
            qDebug() << "Erreur avec CLIENTS:" << clientCheck.lastError().text();
            return false;
        }
    }
    
    if (!clientCheck.next()) {
        lastError = QString("Le client avec l'ID %1 n'existe pas dans la base de données").arg(id_client);
        qDebug() << "Erreur: Client avec ID" << id_client << "n'existe pas dans la base de données";
        return false;
    }
    qDebug() << "Client vérifié avec succès, ID:" << id_client;
    
    // If employee ID is provided, verify that the employee exists
    if (id_employe > 0) {
        QSqlQuery employeeCheck;
        QString empSql = "SELECT id_employe FROM employe WHERE id_employe = :id_employe";
        employeeCheck.prepare(empSql);
        employeeCheck.bindValue(":id_employe", id_employe);
        
        if (!employeeCheck.exec()) {
            qDebug() << "Erreur lors de la vérification de l'employé:" << employeeCheck.lastError().text();
            qDebug() << "Tentative avec EMPLOYE...";
            employeeCheck.clear();
            empSql = "SELECT ID_EMPLOYE FROM EMPLOYE WHERE ID_EMPLOYE = :id_employe";
            employeeCheck.prepare(empSql);
            employeeCheck.bindValue(":id_employe", id_employe);
            if (!employeeCheck.exec()) {
                qDebug() << "Erreur avec EMPLOYE:" << employeeCheck.lastError().text();
                return false;
            }
        }
        
        if (!employeeCheck.next()) {
            qDebug() << "Erreur: Employé avec ID" << id_employe << "n'existe pas dans la base de données";
            return false;
        }
        qDebug() << "Employé vérifié avec succès, ID:" << id_employe;
    } else {
        qDebug() << "Aucun employé spécifié (id_employe = 0), la vente sera enregistrée sans employé";
    }
    
    QSqlQuery query;
    QString insertSql;
    
    // Ensure dates are valid
    QDate validDateVente = date_vente.isValid() ? date_vente : QDate::currentDate();
    QDate validDateLivraison = date_livraison.isValid() ? date_livraison : QDate::currentDate().addDays(1);
    
    // Store date strings for fallback
    QString dateVenteStr = validDateVente.toString("yyyy-MM-dd");
    QString dateLivraisonStr = validDateLivraison.toString("yyyy-MM-dd");
    
    // Validate numeric values to ensure they're within reasonable ranges
    // This helps catch potential data type issues before they cause Oracle errors
    if (prix_ttc < 0 || prix_ht < 0 || remise < 0 || tva < 0) {
        lastError = QString("Erreur: Les valeurs numériques ne peuvent pas être négatives.\nPrix TTC: %1\nPrix HT: %2\nRemise: %3\nTVA: %4")
                    .arg(prix_ttc).arg(prix_ht).arg(remise).arg(tva);
        qDebug() << "❌" << lastError;
        return false;
    }
    
    // Round values to 2 decimal places to match Oracle NUMBER precision
    // This prevents ORA-01438 errors when values have too many decimal places
    prix_ttc = qRound(prix_ttc * 100.0) / 100.0;
    prix_ht = qRound(prix_ht * 100.0) / 100.0;
    remise = qRound(remise * 100.0) / 100.0;
    tva = qRound(tva * 100.0) / 100.0;
    
    // Validate that values don't exceed reasonable maximums
    // Assuming columns are now NUMBER(10,2) after ALTER TABLE modification
    // NUMBER(10,2) allows values up to 99,999,999.99
    const double MAX_VALUE = 99999999.99;  // Limit for NUMBER(10,2)
    if (prix_ttc > MAX_VALUE || prix_ht > MAX_VALUE || remise > MAX_VALUE || tva > MAX_VALUE) {
        lastError = QString("ERREUR: Les montants dépassent la limite maximale autorisée.\n\n"
                           "Valeurs actuelles:\n"
                           "  Prix TTC: %.2f DT\n"
                           "  Prix HT: %.2f DT\n"
                           "  Remise: %.2f DT\n"
                           "  TVA: %.2f DT\n\n"
                           "Limite maximale (NUMBER(10,2)): %.2f DT\n\n"
                           "Si vous avez modifié les colonnes avec ALTER TABLE, vérifiez que les modifications ont été appliquées correctement.")
                    .arg(prix_ttc).arg(prix_ht).arg(remise).arg(tva).arg(MAX_VALUE);
        qDebug() << "❌" << lastError;
        return false;
    }
    
    qDebug() << "Valeurs numériques arrondies - Prix TTC:" << prix_ttc << "Prix HT:" << prix_ht << "Remise:" << remise << "TVA:" << tva;
    
    // Get database connection
    QSqlDatabase db = QSqlDatabase::database();
    bool inTransaction = false;
    
    // Start transaction for atomicity (especially important for Oracle)
    if (db.driver()->hasFeature(QSqlDriver::Transactions)) {
        if (db.transaction()) {
            inTransaction = true;
            qDebug() << "Transaction démarrée pour l'insertion de la vente";
    } else {
            qDebug() << "⚠️ Impossible de démarrer une transaction, continuation sans transaction";
        }
    }
    
    // Oracle-compatible INSERT: Try multiple approaches for maximum compatibility
    // First, try without ID_VENTE (assuming it's auto-generated via sequence or trigger)
    // Pass values directly - they're already rounded to 2 decimal places
    insertSql = "INSERT INTO vente (id_client, id_employe, date_vente, prix_ttc, prix_ht, "
                "remise, tva, statut_vente, statut_paiement, mode_paiement, date_livraison) "
                "VALUES (:id_client, :id_employe, :date_vente, :prix_ttc, :prix_ht, "
                ":remise, :tva, :statut_vente, :statut_paiement, :mode_paiement, :date_livraison)";
    
    query.prepare(insertSql);
    query.bindValue(":id_client", id_client);
    // For Oracle, bind NULL as QVariant(QVariant::Int) instead of NULL literal
    if (id_employe > 0) {
        query.bindValue(":id_employe", id_employe);
    } else {
        query.bindValue(":id_employe", QVariant(QVariant::Int));  // NULL for Oracle
    }
    
    // Bind dates directly - Qt/QODBC should handle the conversion
    query.bindValue(":date_vente", validDateVente);
    // Use explicit numeric binding with rounded values to ensure proper precision for Oracle
    // Round to 2 decimal places to match NUMBER(10,2) or similar precision
    query.bindValue(":prix_ttc", QVariant(prix_ttc));
    query.bindValue(":prix_ht", QVariant(prix_ht));
    query.bindValue(":remise", QVariant(remise));
    query.bindValue(":tva", QVariant(tva));
    query.bindValue(":statut_vente", statut_vente);
    query.bindValue(":statut_paiement", statut_paiement);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":date_livraison", validDateLivraison);
    
    qDebug() << "Tentative d'insertion de la vente...";
    qDebug() << "  Client ID:" << id_client;
    qDebug() << "  Employé ID:" << id_employe << (id_employe == 0 ? "(NULL)" : "");
    qDebug() << "  Date vente:" << dateVenteStr;
    qDebug() << "  Date livraison:" << dateLivraisonStr;
    qDebug() << "  Prix TTC:" << prix_ttc;
    qDebug() << "  Prix HT:" << prix_ht;
    qDebug() << "  Remise:" << remise;
    qDebug() << "  TVA:" << tva;
    qDebug() << "  Statut vente:" << statut_vente;
    qDebug() << "  Statut paiement:" << statut_paiement;
    qDebug() << "  Mode paiement:" << mode_paiement;
    qDebug() << "  SQL:" << insertSql;
    
    if (!query.exec()) {
        QString errorText = query.lastError().text();
        QString dbError = query.lastError().databaseText();
        QString driverError = query.lastError().driverText();
        QString nativeError = query.lastError().nativeErrorCode();
        
        lastError = QString("Erreur lors de l'ajout de la vente:\n%1\n\nErreur base de données: %2\nErreur driver: %3\nCode erreur natif: %4")
                    .arg(errorText)
                    .arg(dbError)
                    .arg(driverError)
                    .arg(nativeError);
        qDebug() << "❌ Erreur lors de l'ajout de la vente: " << errorText;
        qDebug() << "❌ Erreur détaillée - Database:" << dbError;
        qDebug() << "❌ Erreur détaillée - Driver:" << driverError;
        qDebug() << "❌ Code erreur natif:" << nativeError;
        qDebug() << "❌ Valeurs tentées - Prix TTC:" << prix_ttc << "Prix HT:" << prix_ht << "TVA:" << tva;
        qDebug() << "Tentative avec VENTE en majuscules...";
        
        // Try with uppercase table name (Oracle standard) - try direct date binding first
        query.clear();
        
        // Note: Don't rollback yet - we'll try uppercase first
        insertSql = "INSERT INTO VENTE (ID_CLIENT, ID_EMPLOYE, DATE_VENTE, PRIX_TTC, PRIX_HT, "
                    "REMISE, TVA, STATUT_VENTE, STATUT_PAIEMENT, MODE_PAIEMENT, DATE_LIVRAISON) "
                    "VALUES (:id_client, :id_employe, :date_vente, :prix_ttc, :prix_ht, "
                    ":remise, :tva, :statut_vente, :statut_paiement, :mode_paiement, :date_livraison)";
        
        query.prepare(insertSql);
        query.bindValue(":id_client", id_client);
        if (id_employe > 0) {
            query.bindValue(":id_employe", id_employe);
        } else {
            query.bindValue(":id_employe", QVariant(QVariant::Int));  // NULL for Oracle
        }
        query.bindValue(":date_vente", validDateVente);
        query.bindValue(":prix_ttc", prix_ttc);
        query.bindValue(":prix_ht", prix_ht);
        query.bindValue(":remise", remise);
        query.bindValue(":tva", tva);
        query.bindValue(":statut_vente", statut_vente);
        query.bindValue(":statut_paiement", statut_paiement);
        query.bindValue(":mode_paiement", mode_paiement);
        query.bindValue(":date_livraison", validDateLivraison);
        
        if (!query.exec()) {
            // Last resort: try with TO_DATE and string dates
            qDebug() << "Tentative avec TO_DATE et dates en format string...";
            query.clear();
            insertSql = "INSERT INTO VENTE (ID_CLIENT, ID_EMPLOYE, DATE_VENTE, PRIX_TTC, PRIX_HT, "
                        "REMISE, TVA, STATUT_VENTE, STATUT_PAIEMENT, MODE_PAIEMENT, DATE_LIVRAISON) "
                        "VALUES (:id_client, :id_employe, TO_DATE(:date_vente, 'YYYY-MM-DD'), :prix_ttc, :prix_ht, "
                        ":remise, :tva, :statut_vente, :statut_paiement, :mode_paiement, TO_DATE(:date_livraison, 'YYYY-MM-DD'))";
            
            query.prepare(insertSql);
            query.bindValue(":id_client", id_client);
            if (id_employe > 0) {
                query.bindValue(":id_employe", id_employe);
            } else {
                query.bindValue(":id_employe", QVariant(QVariant::Int));
            }
            query.bindValue(":date_vente", dateVenteStr);
            query.bindValue(":prix_ttc", prix_ttc);
            query.bindValue(":prix_ht", prix_ht);
            query.bindValue(":remise", remise);
            query.bindValue(":tva", tva);
            query.bindValue(":statut_vente", statut_vente);
            query.bindValue(":statut_paiement", statut_paiement);
            query.bindValue(":mode_paiement", mode_paiement);
            query.bindValue(":date_livraison", dateLivraisonStr);
            
            if (!query.exec()) {
                // Last resort: Try to get the next ID manually using MAX() + 1
                qDebug() << "Tentative avec génération manuelle de l'ID_VENTE...";
                query.clear();
                
                // Get the next ID by finding MAX and adding 1
                QString maxIdSql = "SELECT NVL(MAX(ID_VENTE), 0) + 1 FROM VENTE";
                QSqlQuery maxQuery;
                int nextId = 1;
                
                if (maxQuery.exec(maxIdSql) && maxQuery.next()) {
                    nextId = maxQuery.value(0).toInt();
                    qDebug() << "Prochain ID_VENTE calculé:" << nextId;
                } else {
                    // Try with lowercase
                    maxQuery.clear();
                    maxIdSql = "SELECT COALESCE(MAX(id_vente), 0) + 1 FROM vente";
                    if (maxQuery.exec(maxIdSql) && maxQuery.next()) {
                        nextId = maxQuery.value(0).toInt();
                        qDebug() << "Prochain ID_VENTE calculé (minuscules):" << nextId;
                    } else {
                        qDebug() << "⚠️ Impossible de calculer le prochain ID, utilisation de 1";
                    }
                }
                
                // Try INSERT with explicit ID
                query.clear();
                insertSql = "INSERT INTO VENTE (ID_VENTE, ID_CLIENT, ID_EMPLOYE, DATE_VENTE, PRIX_TTC, PRIX_HT, "
                            "REMISE, TVA, STATUT_VENTE, STATUT_PAIEMENT, MODE_PAIEMENT, DATE_LIVRAISON) "
                            "VALUES (:id_vente, :id_client, :id_employe, TO_DATE(:date_vente, 'YYYY-MM-DD'), :prix_ttc, :prix_ht, "
                            ":remise, :tva, :statut_vente, :statut_paiement, :mode_paiement, TO_DATE(:date_livraison, 'YYYY-MM-DD'))";
                
                query.prepare(insertSql);
                query.bindValue(":id_vente", nextId);
                query.bindValue(":id_client", id_client);
                if (id_employe > 0) {
                    query.bindValue(":id_employe", id_employe);
                } else {
                    query.bindValue(":id_employe", QVariant(QVariant::Int));
                }
                query.bindValue(":date_vente", dateVenteStr);
                query.bindValue(":prix_ttc", QVariant(prix_ttc));
                query.bindValue(":prix_ht", QVariant(prix_ht));
                query.bindValue(":remise", QVariant(remise));
                query.bindValue(":tva", QVariant(tva));
                query.bindValue(":statut_vente", statut_vente);
                query.bindValue(":statut_paiement", statut_paiement);
                query.bindValue(":mode_paiement", mode_paiement);
                query.bindValue(":date_livraison", dateLivraisonStr);
                
                if (!query.exec()) {
                    lastError = QString("Erreur avec VENTE en majuscules (avec ID explicite):\n%1\n\nErreur base de données: %2\nErreur driver: %3\nCode erreur natif: %4")
                                .arg(query.lastError().text())
                                .arg(query.lastError().databaseText())
                                .arg(query.lastError().driverText())
                                .arg(query.lastError().nativeErrorCode());
                    qDebug() << "Erreur avec VENTE en majuscules (ID explicite):" << query.lastError().text();
                    qDebug() << "Erreur détaillée - Database:" << query.lastError().databaseText();
                    qDebug() << "Erreur détaillée - Driver:" << query.lastError().driverText();
                    qDebug() << "Code erreur natif:" << query.lastError().nativeErrorCode();
                    
                    // Rollback transaction if it was started
                    if (inTransaction) {
                        db.rollback();
                        qDebug() << "Transaction annulée";
                    }
                    return false;
                } else {
                    qDebug() << "✅ Insertion réussie avec ID_VENTE explicite:" << nextId;
                    // Set the ID for later retrieval
                    id_vente = nextId;
                }
            }
        }
    }
    
    // Commit transaction if it was started
    if (inTransaction) {
        if (!db.commit()) {
            qDebug() << "❌ Erreur lors du commit de la transaction:" << db.lastError().text();
            db.rollback();
            lastError = QString("Erreur lors de la validation de la transaction:\n%1").arg(db.lastError().text());
            return false;
        }
        qDebug() << "Transaction validée";
    }
    
    qDebug() << "Vente insérée avec succès!";
    
    // If we manually set the ID during insertion, we'll use it below
    
    // Récupérer l'ID de la vente qui vient d'être créée
    QVariant lastId = query.lastInsertId();
    qlonglong generatedId = -1;
    bool ok = false;
    
    if (lastId.isValid()) {
        generatedId = lastId.toLongLong(&ok);
        if (!ok) {
            generatedId = lastId.toString().toLongLong(&ok, 10);
        }
    }
    
    if (!ok || generatedId <= 0) {
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery idQuery(db);
        
        // Essayer différentes méthodes selon le SGBD
        const QStringList identityQueries = {
            QStringLiteral("SELECT SCOPE_IDENTITY()"),         // SQL Server
            QStringLiteral("SELECT @@IDENTITY"),               // SQL Server (fallback)
            QStringLiteral("SELECT IDENT_CURRENT('vente')"),   // SQL Server (table scoped)
            QStringLiteral("SELECT LAST_INSERT_ID()"),         // MySQL
            QStringLiteral("SELECT last_insert_rowid()")       // SQLite
        };
        
        for (const QString &identitySql : identityQueries) {
            if (idQuery.exec(identitySql) && idQuery.next()) {
                QVariant identityValue = idQuery.value(0);
                generatedId = identityValue.toLongLong(&ok);
                if (!ok) {
                    generatedId = identityValue.toString().toLongLong(&ok, 10);
                }
                if (ok && generatedId > 0) {
                    break;
                }
            } else {
                idQuery.clear();
            }
        }
    }
    
    if ((!ok || generatedId <= 0)) {
        // Dernier recours : récupérer la valeur maximale dans la table
        QSqlQuery maxQuery;
        QString maxSql = "SELECT MAX(id_vente) FROM vente";
        if (!maxQuery.exec(maxSql)) {
            qDebug() << "Erreur avec vente en minuscules pour MAX:" << maxQuery.lastError().text();
            maxQuery.clear();
            maxSql = "SELECT MAX(ID_VENTE) FROM VENTE";
            if (!maxQuery.exec(maxSql)) {
                qDebug() << "Erreur avec VENTE en majuscules pour MAX:" << maxQuery.lastError().text();
            }
        }
        if (maxQuery.next()) {
            QVariant maxValue = maxQuery.value(0);
            if (!maxValue.isNull()) {
                generatedId = maxValue.toLongLong(&ok);
            if (!ok) {
                    generatedId = maxValue.toString().toLongLong(&ok, 10);
            }
            if (ok && generatedId > 0) {
                qDebug() << "ID de vente récupéré via MAX:" << generatedId;
                }
            }
        }
    }
    
    // If we manually set the ID during insertion, use it; otherwise use the retrieved ID
    if (id_vente > 0) {
        qDebug() << "✅ ID de vente utilisé (défini manuellement):" << id_vente;
    } else if (ok && generatedId > 0) {
        id_vente = static_cast<int>(generatedId);
        qDebug() << "✅ ID de vente récupéré avec succès:" << id_vente;
    } else {
        qDebug() << "⚠️ Impossible de récupérer l'ID via lastInsertId ou MAX, tentative avec requête de recherche...";
    }
    
    // Si on n'a toujours pas d'ID, essayer une dernière fois avec une requête directe
    if (id_vente <= 0) {
        qDebug() << "⚠️ Tentative finale de récupération de l'ID...";
        QSqlQuery finalQuery;
        QString finalSql = "SELECT id_vente FROM vente WHERE id_client = :id_client AND date_vente = :date_vente AND prix_ttc = :prix_ttc ORDER BY id_vente DESC";
        finalQuery.prepare(finalSql);
        finalQuery.bindValue(":id_client", id_client);
        finalQuery.bindValue(":date_vente", date_vente);
        finalQuery.bindValue(":prix_ttc", prix_ttc);
        
        if (!finalQuery.exec()) {
            qDebug() << "Erreur avec requête finale en minuscules:" << finalQuery.lastError().text();
            finalQuery.clear();
            finalSql = "SELECT ID_VENTE FROM VENTE WHERE ID_CLIENT = :id_client AND DATE_VENTE = :date_vente AND PRIX_TTC = :prix_ttc ORDER BY ID_VENTE DESC";
            finalQuery.prepare(finalSql);
            finalQuery.bindValue(":id_client", id_client);
            finalQuery.bindValue(":date_vente", date_vente);
            finalQuery.bindValue(":prix_ttc", prix_ttc);
            if (!finalQuery.exec()) {
                qDebug() << "Erreur avec requête finale en majuscules:" << finalQuery.lastError().text();
            }
        }
        
        if (finalQuery.next()) {
            id_vente = finalQuery.value(0).toInt();
            qDebug() << "✅ ID de vente récupéré via requête finale:" << id_vente;
        } else {
            qDebug() << "❌ Échec final de récupération de l'ID.";
            // Vérifier si la vente a vraiment été insérée en comptant les ventes récentes
            QSqlQuery countQuery;
            QString countSql = "SELECT COUNT(*) FROM vente WHERE id_client = :id_client AND date_vente = :date_vente";
            countQuery.prepare(countSql);
            countQuery.bindValue(":id_client", id_client);
            countQuery.bindValue(":date_vente", date_vente);
            if (!countQuery.exec()) {
                countQuery.clear();
                countSql = "SELECT COUNT(*) FROM VENTE WHERE ID_CLIENT = :id_client AND DATE_VENTE = :date_vente";
                countQuery.prepare(countSql);
                countQuery.bindValue(":id_client", id_client);
                countQuery.bindValue(":date_vente", date_vente);
                countQuery.exec();
            }
            if (countQuery.next() && countQuery.value(0).toInt() > 0) {
                qDebug() << "⚠️ La vente semble avoir été créée mais l'ID n'a pas pu être récupéré. Tentative de récupération du dernier ID...";
                // Essayer de récupérer le dernier ID créé pour ce client aujourd'hui
                QSqlQuery lastIdQuery;
                QString lastIdSql = "SELECT id_vente FROM vente WHERE id_client = :id_client ORDER BY id_vente DESC";
                lastIdQuery.prepare(lastIdSql);
                lastIdQuery.bindValue(":id_client", id_client);
                if (!lastIdQuery.exec()) {
                    lastIdQuery.clear();
                    lastIdSql = "SELECT ID_VENTE FROM VENTE WHERE ID_CLIENT = :id_client ORDER BY ID_VENTE DESC";
                    lastIdQuery.prepare(lastIdSql);
                    lastIdQuery.bindValue(":id_client", id_client);
                    lastIdQuery.exec();
                }
                if (lastIdQuery.next()) {
                    id_vente = lastIdQuery.value(0).toInt();
                    qDebug() << "✅ ID de vente récupéré via dernier ID du client:" << id_vente;
                } else {
                    qDebug() << "❌ Impossible de récupérer l'ID de la vente. La vente n'a peut-être pas été créée.";
                    return false;
                }
            } else {
                qDebug() << "❌ La vente n'a pas été créée dans la base de données.";
                return false;
            }
        }
    }
    
    return true;
}

bool Vente::modifier()
{
    QSqlQuery query;
    
    qDebug() << "Vente::modifier() called for sale ID:" << id_vente;
    qDebug() << "  Client:" << id_client << "Employee:" << id_employe;
    qDebug() << "  Date vente:" << date_vente << "Date livraison:" << date_livraison;
    qDebug() << "  Prix HT:" << prix_ht << "Prix TTC:" << prix_ttc << "TVA:" << tva << "Remise:" << remise;
    qDebug() << "  Statut:" << statut_vente << "Paiement:" << statut_paiement << "Mode:" << mode_paiement;
    
    query.prepare("UPDATE vente SET id_client = :id_client, id_employe = :id_employe, "
                  "date_vente = :date_vente, prix_ttc = :prix_ttc, prix_ht = :prix_ht, "
                  "remise = :remise, tva = :tva, statut_vente = :statut_vente, "
                  "statut_paiement = :statut_paiement, mode_paiement = :mode_paiement, "
                  "date_livraison = :date_livraison "
                  "WHERE id_vente = :id_vente");
    
    query.bindValue(":id_vente", id_vente);
    query.bindValue(":id_client", id_client);
    if (id_employe == 0) {
        query.bindValue(":id_employe", QVariant(QVariant::Int));
    } else {
        query.bindValue(":id_employe", id_employe);
    }
    
    // Ensure dates are valid before binding
    if (date_vente.isValid()) {
        query.bindValue(":date_vente", date_vente);
    } else {
        qDebug() << "Warning: Invalid sale date, using current date";
        query.bindValue(":date_vente", QDate::currentDate());
    }
    
    if (date_livraison.isValid()) {
        query.bindValue(":date_livraison", date_livraison);
    } else {
        qDebug() << "Warning: Invalid delivery date, using sale date + 1 day";
        query.bindValue(":date_livraison", date_vente.isValid() ? date_vente.addDays(1) : QDate::currentDate().addDays(1));
    }
    
    query.bindValue(":prix_ttc", prix_ttc);
    query.bindValue(":prix_ht", prix_ht);
    query.bindValue(":remise", remise);
    query.bindValue(":tva", tva);
    query.bindValue(":statut_vente", statut_vente);
    query.bindValue(":statut_paiement", statut_paiement);
    query.bindValue(":mode_paiement", mode_paiement);
    
    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug() << "Error updating sale #" << id_vente << ":";
        qDebug() << "  Database error:" << error.databaseText();
        qDebug() << "  Driver error:" << error.driverText();
        qDebug() << "  Error type:" << error.type();
        return false;
    }
    
    qDebug() << "Sale #" << id_vente << "updated successfully";
    return true;
}

bool Vente::supprimer(int id)
{
    QSqlQuery query;
    
    // D'abord supprimer les entrées dans la table contenir
    query.prepare("DELETE FROM contenir WHERE id_vente = :id");
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des produits de la vente: " << query.lastError().text();
        return false;
    }
    
    // Ensuite supprimer la vente
    query.prepare("DELETE FROM vente WHERE id_vente = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

QSqlQueryModel* Vente::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "e.nom || ' ' || e.prenom AS employe, v.date_vente, "
                    "v.prix_ttc, v.prix_ht, v.remise, v.tva, "
                    "v.statut_vente, v.statut_paiement, v.mode_paiement, v.date_livraison "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "LEFT JOIN employe e ON v.id_employe = e.id_employe "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    return model;
}

QSqlQueryModel* Vente::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "e.nom || ' ' || e.prenom AS employe, v.date_vente, "
                    "v.prix_ttc, v.prix_ht, v.remise, v.tva, "
                    "v.statut_vente, v.statut_paiement, v.mode_paiement, v.date_livraison "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "LEFT JOIN employe e ON v.id_employe = e.id_employe "
                    "WHERE v.id_vente LIKE '%" + critere + "%' OR "
                    "c.nom LIKE '%" + critere + "%' OR "
                    "c.prenom LIKE '%" + critere + "%' OR "
                    "e.nom LIKE '%" + critere + "%' OR "
                    "e.prenom LIKE '%" + critere + "%' OR "
                    "v.statut_vente LIKE '%" + critere + "%' OR "
                    "v.statut_paiement LIKE '%" + critere + "%' OR "
                    "v.mode_paiement LIKE '%" + critere + "%' "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    return model;
}

QSqlQueryModel* Vente::filtrerParDate(const QDate &debut, const QDate &fin)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "e.nom || ' ' || e.prenom AS employe, v.date_vente, "
                    "v.prix_ttc, v.prix_ht, v.remise, v.tva, "
                    "v.statut_vente, v.statut_paiement, v.mode_paiement, v.date_livraison "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "LEFT JOIN employe e ON v.id_employe = e.id_employe "
                    "WHERE v.date_vente BETWEEN '" + debut.toString("yyyy-MM-dd") + "' AND '" + fin.toString("yyyy-MM-dd") + "' "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    return model;
}

bool Vente::ajouterProduitVente(int idVente, int refProduit, int quantite, double prixUnitaire)
{
    if (idVente <= 0) {
        qDebug() << "❌ Erreur: ID de vente invalide:" << idVente;
        return false;
    }
    
    if (refProduit <= 0) {
        qDebug() << "❌ Erreur: Référence produit invalide:" << refProduit;
        return false;
    }
    
    if (quantite <= 0) {
        qDebug() << "❌ Erreur: Quantité invalide:" << quantite;
        return false;
    }
    
    // First, verify that the sale exists
    QSqlQuery saleCheck;
    QString saleCheckSql = "SELECT id_vente FROM vente WHERE id_vente = :id_vente";
    saleCheck.prepare(saleCheckSql);
    saleCheck.bindValue(":id_vente", idVente);
    
    if (!saleCheck.exec()) {
        qDebug() << "Erreur lors de la vérification de la vente:" << saleCheck.lastError().text();
        saleCheck.clear();
        saleCheckSql = "SELECT ID_VENTE FROM VENTE WHERE ID_VENTE = :id_vente";
        saleCheck.prepare(saleCheckSql);
        saleCheck.bindValue(":id_vente", idVente);
        if (!saleCheck.exec()) {
            qDebug() << "❌ Erreur: Impossible de vérifier l'existence de la vente #" << idVente;
            return false;
        }
    }
    
    if (!saleCheck.next()) {
        qDebug() << "❌ Erreur: La vente #" << idVente << "n'existe pas dans la base de données";
        return false;
    }
    
    // Verify that the product exists
    QSqlQuery productCheck;
    QString productCheckSql = "SELECT reference FROM produit WHERE reference = :reference";
    productCheck.prepare(productCheckSql);
    productCheck.bindValue(":reference", refProduit);
    
    if (!productCheck.exec()) {
        qDebug() << "Erreur lors de la vérification du produit:" << productCheck.lastError().text();
        productCheck.clear();
        productCheckSql = "SELECT REFERENCE FROM PRODUIT WHERE REFERENCE = :reference";
        productCheck.prepare(productCheckSql);
        productCheck.bindValue(":reference", refProduit);
        if (!productCheck.exec()) {
            qDebug() << "❌ Erreur: Impossible de vérifier l'existence du produit #" << refProduit;
            return false;
        }
    }
    
    if (!productCheck.next()) {
        qDebug() << "❌ Erreur: Le produit #" << refProduit << "n'existe pas dans la base de données";
        return false;
    }
    
    // Check if this product is already in contenir for this sale (to handle unique constraint)
    QSqlQuery checkExisting;
    QString checkSql = "SELECT quantite FROM contenir WHERE id_vente = :id_vente AND reference = :reference";
    checkExisting.prepare(checkSql);
    checkExisting.bindValue(":id_vente", idVente);
    checkExisting.bindValue(":reference", refProduit);
    
    bool productExists = false;
    int existingQuantity = 0;
    
    if (checkExisting.exec() && checkExisting.next()) {
        productExists = true;
        existingQuantity = checkExisting.value(0).toInt();
        qDebug() << "⚠️ Produit déjà présent dans contenir - Quantité existante:" << existingQuantity;
    } else {
        // Try with uppercase
        checkExisting.clear();
        checkSql = "SELECT QUANTITE FROM CONTENIR WHERE ID_VENTE = :id_vente AND REFERENCE = :reference";
        checkExisting.prepare(checkSql);
        checkExisting.bindValue(":id_vente", idVente);
        checkExisting.bindValue(":reference", refProduit);
        if (checkExisting.exec() && checkExisting.next()) {
            productExists = true;
            existingQuantity = checkExisting.value(0).toInt();
            qDebug() << "⚠️ Produit déjà présent dans CONTENIR - Quantité existante:" << existingQuantity;
        }
    }
    
    // Now insert into contenir table
    QSqlQuery query;
    
    // Validate values before attempting insert
    if (quantite <= 0) {
        qDebug() << "❌ Erreur: Quantité doit être > 0, valeur:" << quantite;
        return false;
    }
    if (prixUnitaire < 0) {
        qDebug() << "❌ Erreur: Prix unitaire ne peut pas être négatif, valeur:" << prixUnitaire;
        return false;
    }
    
    // If product already exists, update quantity instead of inserting
    if (productExists) {
        qDebug() << "Mise à jour de la quantité existante au lieu d'insérer un nouveau enregistrement";
        QString updateSql = "UPDATE contenir SET quantite = quantite + :quantite WHERE id_vente = :id_vente AND reference = :reference";
        query.prepare(updateSql);
        query.bindValue(":id_vente", idVente);
        query.bindValue(":reference", refProduit);
        query.bindValue(":quantite", quantite);
        
        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour, tentative avec CONTENIR en majuscules...";
            query.clear();
            updateSql = "UPDATE CONTENIR SET QUANTITE = QUANTITE + :quantite WHERE ID_VENTE = :id_vente AND REFERENCE = :reference";
            query.prepare(updateSql);
            query.bindValue(":id_vente", idVente);
            query.bindValue(":reference", refProduit);
            query.bindValue(":quantite", quantite);
            
            if (!query.exec()) {
                qDebug() << "❌ Erreur lors de la mise à jour de la quantité:" << query.lastError().text();
                return false;
            }
        }
        qDebug() << "✅ Quantité mise à jour avec succès dans contenir";
    } else {
        // Insert new record
    QString insertSql = "INSERT INTO contenir (id_vente, reference, quantite, prix_unitaire) "
                        "VALUES (:id_vente, :reference, :quantite, :prix_unitaire)";
    query.prepare(insertSql);
    
    query.bindValue(":id_vente", idVente);
    query.bindValue(":reference", refProduit);
    query.bindValue(":quantite", quantite);
        // Use explicit QVariant for price to ensure proper precision for Oracle
        query.bindValue(":prix_unitaire", QVariant(prixUnitaire));
    
        qDebug() << "Tentative d'ajout du produit à la vente dans la table contenir:";
    qDebug() << "  ID Vente:" << idVente;
    qDebug() << "  Référence produit:" << refProduit;
    qDebug() << "  Quantité:" << quantite;
    qDebug() << "  Prix unitaire:" << prixUnitaire;
        qDebug() << "  Total:" << (quantite * prixUnitaire);
    
    if (!query.exec()) {
            QString errorText = query.lastError().text();
            QString dbError = query.lastError().databaseText();
            QString driverError = query.lastError().driverText();
            QString nativeError = query.lastError().nativeErrorCode();
            
            qDebug() << "❌ Erreur lors de l'ajout du produit à la vente: " << errorText;
            qDebug() << "  Database error:" << dbError;
            qDebug() << "  Driver error:" << driverError;
            qDebug() << "  Native error code:" << nativeError;
        qDebug() << "Tentative avec CONTENIR en majuscules...";
        
        // Try with uppercase table name
        query.clear();
        insertSql = "INSERT INTO CONTENIR (ID_VENTE, REFERENCE, QUANTITE, PRIX_UNITAIRE) "
                    "VALUES (:id_vente, :reference, :quantite, :prix_unitaire)";
        query.prepare(insertSql);
        query.bindValue(":id_vente", idVente);
        query.bindValue(":reference", refProduit);
        query.bindValue(":quantite", quantite);
            query.bindValue(":prix_unitaire", QVariant(prixUnitaire));
        
        if (!query.exec()) {
                qDebug() << "❌ Erreur avec CONTENIR en majuscules:" << query.lastError().text();
                qDebug() << "  Database error:" << query.lastError().databaseText();
                qDebug() << "  Driver error:" << query.lastError().driverText();
                qDebug() << "  Native error code:" << query.lastError().nativeErrorCode();
                
                // Check for common Oracle error codes
                if (nativeError.contains("02290") || errorText.contains("check constraint")) {
                    qDebug() << "⚠️ Erreur de contrainte CHECK détectée - Vérifiez les contraintes sur QUANTITE ou PRIX_UNITAIRE";
                } else if (nativeError.contains("01400") || errorText.contains("not null")) {
                    qDebug() << "⚠️ Erreur NOT NULL détectée - Un champ requis est manquant";
                } else if (nativeError.contains("01438") || errorText.contains("value larger than")) {
                    qDebug() << "⚠️ Erreur de taille de valeur - La valeur dépasse la taille du champ";
                } else if (nativeError.contains("00001") || errorText.contains("unique constraint")) {
                    qDebug() << "⚠️ Erreur de contrainte UNIQUE - Cette combinaison existe déjà";
                    qDebug() << "⚠️ Tentative de mise à jour au lieu d'insertion...";
                    
                    // Try to update instead
                    query.clear();
                    QString updateSql = "UPDATE CONTENIR SET QUANTITE = QUANTITE + :quantite WHERE ID_VENTE = :id_vente AND REFERENCE = :reference";
                    query.prepare(updateSql);
                    query.bindValue(":id_vente", idVente);
                    query.bindValue(":reference", refProduit);
                    query.bindValue(":quantite", quantite);
                    
                    if (query.exec()) {
                        qDebug() << "✅ Produit mis à jour avec succès (au lieu d'insérer)";
                    } else {
                        qDebug() << "❌ Échec de la mise à jour également:" << query.lastError().text();
                        return false;
                    }
                } else {
            return false;
                }
            }
        }
    }
    
    qDebug() << "✅ Produit ajouté à la vente avec succès dans la table contenir!";
    
    // Mettre à jour le stock du produit
    query.clear();
    QString updateSql = "UPDATE produit SET quantite = quantite - :quantite WHERE reference = :reference";
    query.prepare(updateSql);
    query.bindValue(":reference", refProduit);
    query.bindValue(":quantite", quantite);
    
    if (!query.exec()) {
        qDebug() << "⚠️ Erreur lors de la mise à jour du stock:" << query.lastError().text();
        qDebug() << "Tentative avec PRODUIT en majuscules...";
        
        query.clear();
        updateSql = "UPDATE PRODUIT SET QUANTITE = QUANTITE - :quantite WHERE REFERENCE = :reference";
        query.prepare(updateSql);
        query.bindValue(":reference", refProduit);
        query.bindValue(":quantite", quantite);
        
        if (!query.exec()) {
            qDebug() << "⚠️ Erreur avec PRODUIT en majuscules:" << query.lastError().text();
            // Ne pas retourner false car le produit est déjà ajouté à la vente dans contenir
            // Juste loguer l'erreur - le stock sera mis à jour manuellement si nécessaire
            qDebug() << "⚠️ Le produit a été ajouté à la vente mais le stock n'a pas été mis à jour automatiquement.";
        } else {
            qDebug() << "✅ Stock mis à jour avec succès!";
        }
    } else {
        qDebug() << "✅ Stock mis à jour avec succès!";
    }
    
    return true;
}

QSqlQueryModel* Vente::afficherProduitsVente(int idVente)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    qDebug() << "afficherProduitsVente called for sale ID:" << idVente;
    
    // First, try simple query without complex string concatenation
    QString queryStr = QString("SELECT c.reference, p.designation, "
                    "c.prix_unitaire, c.quantite, "
                    "(c.prix_unitaire * c.quantite) AS total "
                    "FROM contenir c "
                    "LEFT JOIN produit p ON c.reference = p.reference "
                    "WHERE c.id_vente = %1").arg(idVente);
    
    qDebug() << "Executing query:" << queryStr;
    model->setQuery(queryStr);
    
    // Check for query errors
    if (model->lastError().isValid()) {
        QString errorText = model->lastError().text();
        qDebug() << "Erreur lors de la récupération des produits de la vente #" << idVente << ":" << errorText;
        qDebug() << "Requête SQL:" << queryStr;
        
        // Try with parameterized query as fallback
        QString paramQueryStr = QString("SELECT c.reference, p.designation, "
                         "c.prix_unitaire, c.quantite, "
                         "(c.prix_unitaire * c.quantite) AS total "
                         "FROM contenir c "
                         "LEFT JOIN produit p ON c.reference = p.reference "
                         "WHERE c.id_vente = %1").arg(idVente);
        
        qDebug() << "Trying fallback query:" << paramQueryStr;
        model->setQuery(paramQueryStr);
        
        if (model->lastError().isValid()) {
            qDebug() << "Fallback query also failed:" << model->lastError().text();
        } else {
            qDebug() << "Fallback query succeeded, row count:" << model->rowCount();
        }
    } else {
        qDebug() << "Query succeeded, row count:" << model->rowCount();
    }
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix unitaire"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Total"));
    
    return model;
}

double Vente::calculerTotal(int idVente)
{
    QSqlQuery query;
    double total = 0.0;
    
    query.prepare("SELECT SUM(prix_unitaire * quantite) FROM contenir WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", idVente);
    
    if (query.exec() && query.next()) {
        total = query.value(0).toDouble();
    }
    
    return total;
}

bool Vente::mettreAJourStatutVente(int idVente, const QString &nouveauStatut)
{
    QSqlQuery query;
    
    query.prepare("UPDATE vente SET statut_vente = :statut WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", idVente);
    query.bindValue(":statut", nouveauStatut);
    
    return query.exec();
}

bool Vente::mettreAJourStatutPaiement(int idVente, const QString &nouveauStatut)
{
    QSqlQuery query;
    
    query.prepare("UPDATE vente SET statut_paiement = :statut WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", idVente);
    query.bindValue(":statut", nouveauStatut);
    
    return query.exec();
}
