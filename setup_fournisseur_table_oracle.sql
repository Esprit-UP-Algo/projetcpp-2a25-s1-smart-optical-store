-- ============================================
-- Fournisseur Table Setup Script (Oracle)
-- ============================================
-- This script creates the fournisseur table for Oracle database

-- Drop table if exists (optional - uncomment if you want to recreate)
-- DROP TABLE "fournisseur" CASCADE CONSTRAINTS;

-- Create fournisseur table
CREATE TABLE "fournisseur" (
    "id_fournisseur" NUMBER PRIMARY KEY,
    "nom_entreprise" VARCHAR2(255) NOT NULL,
    "nom_contact" VARCHAR2(255),
    "email" VARCHAR2(255),
    "telephone" VARCHAR2(20),
    "type_produit_fournis" VARCHAR2(255),
    "condition_paiement" NUMBER DEFAULT 0,
    "historique" CLOB,
    CONSTRAINT chk_condition_paiement CHECK ("condition_paiement" IN (0, 1))
);

-- Create sequence for auto-incrementing ID
CREATE SEQUENCE fournisseur_id_seq 
    START WITH 1 
    INCREMENT BY 1
    NOCACHE
    NOCYCLE;

-- Create indexes for faster searches
CREATE INDEX idx_fournisseur_email ON "fournisseur"("email");
CREATE INDEX idx_fournisseur_nom ON "fournisseur"("nom_entreprise");

-- Create trigger for auto-increment (optional but recommended)
CREATE OR REPLACE TRIGGER fournisseur_id_trigger
BEFORE INSERT ON "fournisseur"
FOR EACH ROW
BEGIN
    IF :NEW."id_fournisseur" IS NULL THEN
        SELECT fournisseur_id_seq.NEXTVAL INTO :NEW."id_fournisseur" FROM DUAL;
    END IF;
END;
/

-- Sample data (optional - uncomment to insert test data)
/*
INSERT INTO "fournisseur" ("id_fournisseur", "nom_entreprise", "nom_contact", "email", "telephone", "type_produit_fournis", "condition_paiement", "historique")
VALUES 
    (1, 'OpticalSupplies Inc', 'John Smith', 'john@opticalsupplies.com', '12345678', 'Frames', 1, 'Reliable supplier since 2020');

INSERT INTO "fournisseur" ("id_fournisseur", "nom_entreprise", "nom_contact", "email", "telephone", "type_produit_fournis", "condition_paiement", "historique")
VALUES 
    (2, 'LensMasters Co', 'Jane Doe', 'jane@lensmasters.com', '87654321', 'Lenses', 0, 'Premium lens supplier');

INSERT INTO "fournisseur" ("id_fournisseur", "nom_entreprise", "nom_contact", "email", "telephone", "type_produit_fournis", "condition_paiement", "historique")
VALUES 
    (3, 'EyewearPro', 'Bob Johnson', 'bob@eyewearpro.com', '11223344', 'Accessories', 1, 'Fast delivery');
*/

COMMIT;
