#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include "Connection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Initialize database connection
    Connection c;
    if (!c.createconnect()) {
        qDebug() << "Failed to connect to database";
        return -1;
    }
    
    qDebug() << "=== Testing Loyalty and Promo Code System ===";
    
    // Test 1: Check if loyalty columns exist in CLIENTS table
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM USER_TAB_COLUMNS WHERE TABLE_NAME = 'CLIENTS' AND COLUMN_NAME IN ('TOTAL_ACHATS', 'NIVEAU_FIDELITE')");
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count >= 2) {
            qDebug() << "✓ Loyalty columns exist in CLIENTS table";
        } else {
            qDebug() << "✗ Loyalty columns missing from CLIENTS table";
        }
    }
    
    // Test 2: Check if CODE_PROMO table exists
    query.prepare("SELECT COUNT(*) FROM USER_TABLES WHERE TABLE_NAME = 'CODE_PROMO'");
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            qDebug() << "✓ CODE_PROMO table exists";
        } else {
            qDebug() << "✗ CODE_PROMO table missing";
        }
    }
    
    // Test 3: Check if NIVEAU_FIDELITE table exists and has data
    query.prepare("SELECT COUNT(*) FROM USER_TABLES WHERE TABLE_NAME = 'NIVEAU_FIDELITE'");
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            qDebug() << "✓ NIVEAU_FIDELITE table exists";
            
            // Check if it has data
            query.prepare("SELECT COUNT(*) FROM NIVEAU_FIDELITE");
            if (query.exec() && query.next()) {
                int dataCount = query.value(0).toInt();
                if (dataCount >= 4) {
                    qDebug() << "✓ NIVEAU_FIDELITE table has default loyalty levels";
                } else {
                    qDebug() << "✗ NIVEAU_FIDELITE table missing default loyalty levels";
                }
            }
        } else {
            qDebug() << "✗ NIVEAU_FIDELITE table missing";
        }
    }
    
    // Test 4: Insert a test promo code
    query.prepare("INSERT INTO CODE_PROMO (CODE, DESCRIPTION, POURCENTAGE_REMISE, DATE_DEBUT, DATE_FIN, ACTIF) "
                  "VALUES (:code, :description, :discount, :start_date, :end_date, :active)");
    query.bindValue(":code", "TEST123");
    query.bindValue(":description", "Test Promo Code");
    query.bindValue(":discount", 10.5);
    query.bindValue(":start_date", QDate::currentDate());
    query.bindValue(":end_date", QDate::currentDate().addDays(30));
    query.bindValue(":active", 1);
    
    if (query.exec()) {
        qDebug() << "✓ Test promo code inserted successfully";
        
        // Clean up test data
        query.prepare("DELETE FROM CODE_PROMO WHERE CODE = 'TEST123'");
        if (query.exec()) {
            qDebug() << "✓ Test data cleaned up";
        }
    } else {
        qDebug() << "✗ Failed to insert test promo code:" << query.lastError().text();
    }
    
    qDebug() << "=== Test completed ===";
    
    return 0;
}