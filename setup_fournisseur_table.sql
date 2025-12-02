-- ============================================
-- Fournisseur Table Setup Script
-- ============================================
-- This script creates the fournisseur table if it doesn't exist
-- Run this in your Oracle/PostgreSQL database

-- Drop table if you want to recreate it (uncomment if needed)
-- DROP TABLE "fournisseur" CASCADE;

-- Create fournisseur table
CREATE TABLE IF NOT EXISTS "fournisseur" (
    "id_fournisseur" INTEGER PRIMARY KEY,
    "nom_entreprise" VARCHAR(255) NOT NULL,
    "nom_contact" VARCHAR(255),
    "email" VARCHAR(255),
    "telephone" VARCHAR(20),
    "type_produit_fournis" VARCHAR(255),
    "condition_paiement" INTEGER DEFAULT 0 CHECK (condition_paiement IN (0, 1)),
    "historique" TEXT
);

-- Create sequence for auto-incrementing ID (if using PostgreSQL/Oracle)
-- For Oracle:
-- CREATE SEQUENCE fournisseur_id_seq START WITH 1 INCREMENT BY 1;

-- Create index on email for faster searches
CREATE INDEX IF NOT EXISTS idx_fournisseur_email ON "fournisseur"("email");

-- Create index on nom_entreprise for faster searches
CREATE INDEX IF NOT EXISTS idx_fournisseur_nom ON "fournisseur"("nom_entreprise");

-- Sample data (optional - uncomment to insert test data)
/*
INSERT INTO "fournisseur" ("id_fournisseur", "nom_entreprise", "nom_contact", "email", "telephone", "type_produit_fournis", "condition_paiement", "historique")
VALUES 
    (1, 'OpticalSupplies Inc', 'John Smith', 'john@opticalsupplies.com', '12345678', 'Frames', 1, 'Reliable supplier since 2020'),
    (2, 'LensMasters Co', 'Jane Doe', 'jane@lensmasters.com', '87654321', 'Lenses', 0, 'Premium lens supplier'),
    (3, 'EyewearPro', 'Bob Johnson', 'bob@eyewearpro.com', '11223344', 'Accessories', 1, 'Fast delivery');
*/

-- Grant permissions (adjust as needed for your database user)
-- GRANT ALL PRIVILEGES ON "fournisseur" TO your_user;

COMMIT;
