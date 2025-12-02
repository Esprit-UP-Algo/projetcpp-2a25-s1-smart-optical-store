-- ============================================
-- FINAL FIX - Run this EXACT script in Oracle SQL Developer
-- ============================================
-- This creates the table with LOWERCASE name as required by the C++ code

-- Step 1: Create the table (with LOWERCASE quoted name)
CREATE TABLE "fournisseur" (
    "id_fournisseur" NUMBER,
    "nom_entreprise" VARCHAR2(255) NOT NULL,
    "nom_contact" VARCHAR2(255),
    "email" VARCHAR2(255),
    "telephone" VARCHAR2(20),
    "type_produit_fournis" VARCHAR2(255),
    "condition_paiement" NUMBER DEFAULT 0,
    "historique" CLOB
);

-- Step 2: Add primary key
ALTER TABLE "fournisseur" 
ADD CONSTRAINT pk_fournisseur PRIMARY KEY ("id_fournisseur");

-- Step 3: Add check constraint (as table constraint, not column constraint)
ALTER TABLE "fournisseur"
ADD CONSTRAINT chk_condition_paiement CHECK ("condition_paiement" IN (0, 1));

-- Step 4: Create sequence for auto-incrementing ID
CREATE SEQUENCE "fournisseur_id_seq"
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

-- Step 5: Create indexes
CREATE INDEX "idx_fournisseur_email" ON "fournisseur"("email");
CREATE INDEX "idx_fournisseur_nom" ON "fournisseur"("nom_entreprise");

-- Step 6: Create trigger for auto-increment
CREATE OR REPLACE TRIGGER "fournisseur_id_trigger"
BEFORE INSERT ON "fournisseur"
FOR EACH ROW
BEGIN
    IF :NEW."id_fournisseur" IS NULL THEN
        SELECT "fournisseur_id_seq".NEXTVAL INTO :NEW."id_fournisseur" FROM DUAL;
    END IF;
END;
/

-- Step 7: Verify table exists
SELECT * FROM "fournisseur";

-- Step 8: Insert test data (optional)
INSERT INTO "fournisseur" ("nom_entreprise", "nom_contact", "email", "telephone", "type_produit_fournis", "condition_paiement", "historique")
VALUES ('Test Supplier', 'John Doe', 'test@supplier.com', '12345678', 'Optical Frames', 1, 'Initial test entry');

COMMIT;

-- Finished! Now restart your Qt application and try accessing the fournisseur interface
