-- ============================================
-- FOURNISSEUR TABLE DIAGNOSTIC AND FIX SCRIPT
-- ============================================
-- Execute these commands ONE BY ONE to diagnose and fix the issue

-- STEP 1: Check if the table already exists
-- Run this first to see current state:
SELECT table_name FROM user_tables WHERE table_name = 'fournisseur';
-- If it returns a row, the table exists (might have wrong structure)
-- If it returns no rows, the table doesn't exist

-- STEP 2: Check if uppercase version exists
SELECT table_name FROM user_tables WHERE UPPER(table_name) = 'FOURNISSEUR';
-- Oracle is case-sensitive with quoted identifiers

-- STEP 3: See ALL your tables (to verify connection)
SELECT table_name FROM user_tables ORDER BY table_name;

-- ============================================
-- STEP 4: DROP EXISTING TABLE (if it exists with issues)
-- ============================================
-- Only run this if table exists but has wrong structure:
-- DROP TABLE "fournisseur" CASCADE CONSTRAINTS;
-- DROP TABLE FOURNISSEUR CASCADE CONSTRAINTS;
-- DROP SEQUENCE fournisseur_id_seq;

-- ============================================
-- STEP 5: CREATE TABLE (Simplified Version - NO Quotes)
-- ============================================
-- Try without quotes first (Oracle will uppercase the names):
CREATE TABLE FOURNISSEUR (
    ID_FOURNISSEUR NUMBER PRIMARY KEY,
    NOM_ENTREPRISE VARCHAR2(255) NOT NULL,
    NOM_CONTACT VARCHAR2(255),
    EMAIL VARCHAR2(255),
    TELEPHONE VARCHAR2(20),
    TYPE_PRODUIT_FOURNIS VARCHAR2(255),
    CONDITION_PAIEMENT NUMBER DEFAULT 0,
    HISTORIQUE CLOB,
    CONSTRAINT chk_condition_paiement CHECK (CONDITION_PAIEMENT IN (0, 1))
);

-- STEP 6: Create sequence
CREATE SEQUENCE FOURNISSEUR_ID_SEQ 
    START WITH 1 
    INCREMENT BY 1
    NOCACHE
    NOCYCLE;

-- STEP 7: Create indexes
CREATE INDEX IDX_FOURNISSEUR_EMAIL ON FOURNISSEUR(EMAIL);
CREATE INDEX IDX_FOURNISSEUR_NOM ON FOURNISSEUR(NOM_ENTREPRISE);

-- STEP 8: Create auto-increment trigger
CREATE OR REPLACE TRIGGER FOURNISSEUR_ID_TRIGGER
BEFORE INSERT ON FOURNISSEUR
FOR EACH ROW
BEGIN
    IF :NEW.ID_FOURNISSEUR IS NULL THEN
        SELECT FOURNISSEUR_ID_SEQ.NEXTVAL INTO :NEW.ID_FOURNISSEUR FROM DUAL;
    END IF;
END;
/

-- STEP 9: Verify table was created
SELECT table_name, column_name, data_type, data_length 
FROM user_tab_columns 
WHERE table_name = 'FOURNISSEUR'
ORDER BY column_id;

-- STEP 10: Test with sample insert
INSERT INTO FOURNISSEUR (NOM_ENTREPRISE, NOM_CONTACT, EMAIL, TELEPHONE, TYPE_PRODUIT_FOURNIS, CONDITION_PAIEMENT, HISTORIQUE)
VALUES ('Test Supplier', 'John Doe', 'test@example.com', '12345678', 'Frames', 1, 'Test entry');

-- STEP 11: Verify data was inserted
SELECT * FROM FOURNISSEUR;

-- STEP 12: Clean up test data (optional)
-- DELETE FROM FOURNISSEUR WHERE NOM_ENTREPRISE = 'Test Supplier';

COMMIT;
