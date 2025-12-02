-- ============================================
-- ADD MISSING COLUMN TO FOURNISSEUR TABLE
-- ============================================
-- Run this to fix the "historique de commande passée" error

-- Add the missing column with spaces in the name
ALTER TABLE "fournisseur" 
ADD "historique de commande passée" CLOB;

-- Verify the change
SELECT column_name 
FROM user_tab_columns 
WHERE table_name = 'fournisseur'
ORDER BY column_id;

-- Test that it works
SELECT * FROM "fournisseur";

COMMIT;
