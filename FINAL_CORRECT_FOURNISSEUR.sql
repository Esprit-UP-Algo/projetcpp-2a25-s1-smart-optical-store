-- ============================================
-- COMPLETE FIX - DROP AND RECREATE WITH CORRECT COLUMN NAMES
-- ============================================
-- The C++ code uses column names with HYPHENS and SPACES!
-- This script creates the table with the EXACT correct column names

-- Step 1: Drop existing table (if exists)
DROP TABLE "fournisseur" CASCADE CONSTRAINTS;
DROP SEQUENCE "fournisseur_id_seq";

-- Step 2: Create table with CORRECT column names (hyphens, spaces, etc.)
CREATE TABLE "fournisseur" (
    "ID-fournisseur" NUMBER,
    "nom-entreprise" VARCHAR2(255) NOT NULL,
    "nom de contact" VARCHAR2(255),
    "email" VARCHAR2(255),
    "téléphone" VARCHAR2(20),
    "type de produit fournis" VARCHAR2(255),
    "condition de paiement" NUMBER DEFAULT 0,
    "historique de commande passée" CLOB
);

-- Step 3: Add primary key
ALTER TABLE "fournisseur" 
ADD CONSTRAINT pk_fournisseur PRIMARY KEY ("ID-fournisseur");

-- Step 4: Add check constraint
ALTER TABLE "fournisseur"
ADD CONSTRAINT chk_condition_paiement CHECK ("condition de paiement" IN (0, 1));

-- Step 5: Create sequence
CREATE SEQUENCE "fournisseur_id_seq"
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

-- Step 6: Create indexes
CREATE INDEX "idx_fournisseur_email" ON "fournisseur"("email");
CREATE INDEX "idx_fournisseur_nom" ON "fournisseur"("nom-entreprise");

-- Step 7: Create auto-increment trigger
CREATE OR REPLACE TRIGGER "fournisseur_id_trigger"
BEFORE INSERT ON "fournisseur"
FOR EACH ROW
BEGIN
    IF :NEW."ID-fournisseur" IS NULL THEN
        SELECT "fournisseur_id_seq".NEXTVAL INTO :NEW."ID-fournisseur" FROM DUAL;
    END IF;
END;
/

-- Step 8: Verify table structure
SELECT column_name, data_type, data_length
FROM user_tab_columns
WHERE table_name = 'fournisseur'
ORDER BY column_id;

-- Step 9: Insert test data
INSERT INTO "fournisseur" ("nom-entreprise", "nom de contact", "email", "téléphone", "type de produit fournis", "condition de paiement", "historique de commande passée")
VALUES ('Test Optical Supplies', 'Jean Dupont', 'jean@optical.com', '12345678', 'Lunettes', 1, 'Premier fournisseur test');

-- Step 10: Test SELECT
SELECT * FROM "fournisseur";

COMMIT;

-- ============================================
-- FINISHED! Now restart your Qt application
-- ============================================
