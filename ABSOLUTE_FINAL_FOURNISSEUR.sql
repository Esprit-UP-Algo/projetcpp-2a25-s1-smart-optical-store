-- ============================================
-- ABSOLUTE FINAL CORRECT FOURNISSEUR TABLE
-- ============================================
-- Based on actual fournisseur.cpp INSERT statement (line 85-89)
-- Column names extracted from the C++ code:
-- "ID-fournisseur", "nom de l'entreprise", "nom du contact", 
-- "email", "telephone", "type de produit fournis", 
-- "condition de paiement", "historique de commande passée"

-- Step 1: Drop existing table if it exists
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE "fournisseur" CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/

BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE "fournisseur_id_seq"';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/

-- Step 2: Create table with EXACT column names from fournisseur.cpp
CREATE TABLE "fournisseur" (
    "ID-fournisseur" NUMBER,
    "nom de l'entreprise" VARCHAR2(255) NOT NULL,
    "nom du contact" VARCHAR2(255),
    "email" VARCHAR2(255),
    "telephone" VARCHAR2(20),
    "type de produit fournis" VARCHAR2(255),
    "condition de paiement" NUMBER DEFAULT 0,
    "historique de commande passée" CLOB
);

-- Step 3: Add primary key constraint
ALTER TABLE "fournisseur" 
ADD CONSTRAINT pk_fournisseur PRIMARY KEY ("ID-fournisseur");

-- Step 4: Add check constraint for condition de paiement
ALTER TABLE "fournisseur"
ADD CONSTRAINT chk_condition_paiement CHECK ("condition de paiement" IN (0, 1));

-- Step 5: Create sequence for auto-increment
CREATE SEQUENCE "fournisseur_id_seq"
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

-- Step 6: Create indexes for performance
CREATE INDEX "idx_fournisseur_email" ON "fournisseur"("email");
CREATE INDEX "idx_fournisseur_nom" ON "fournisseur"("nom de l'entreprise");

-- Step 7: Create trigger for auto-increment ID
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
SELECT column_name, data_type, data_length, nullable
FROM user_tab_columns
WHERE table_name = 'fournisseur'
ORDER BY column_id;

-- Step 9: Insert test data
INSERT INTO "fournisseur" 
    ("nom de l'entreprise", "nom du contact", "email", "telephone", 
     "type de produit fournis", "condition de paiement", "historique de commande passée")
VALUES 
    ('Optical Supplies SARL', 'Jean Dupont', 'contact@optical.fr', '12345678', 
     'Montures et verres', 1, 'Nouveau fournisseur - première commande en attente');

-- Step 10: Verify the insert worked
SELECT "ID-fournisseur", "nom de l'entreprise", "email", "telephone" 
FROM "fournisseur";

COMMIT;

-- ============================================
-- SUCCESS! Table created with exact column names:
-- ✓ "ID-fournisseur" (hyphen, not underscore)
-- ✓ "nom de l'entreprise" (with apostrophe!)
-- ✓ "nom du contact" (spaces)
-- ✓ "email" (lowercase, no special chars)
-- ✓ "telephone" (NO accent!)
-- ✓ "type de produit fournis" (spaces)
-- ✓ "condition de paiement" (spaces)
-- ✓ "historique de commande passée" (spaces + accent)
-- ============================================
-- NOW RESTART YOUR QT APPLICATION!
-- ============================================
