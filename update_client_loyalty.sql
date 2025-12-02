-- Script to update client ID 1 to PLATINE loyalty level (highest level - 15% discount)
-- This will allow you to test the loyalty discount system

-- Option 1: Set TOTAL_ACHATS to 10000 DT (minimum for PLATINE level)
-- The system will automatically calculate and set the loyalty level based on this
UPDATE CLIENTS 
SET TOTAL_ACHATS = 10000 
WHERE ID_CLIENT = 1;

-- If the above doesn't work (case sensitivity), try:
-- UPDATE clients SET total_achats = 10000 WHERE id_client = 1;

-- Option 2: Directly set the loyalty level to PLATINE
UPDATE CLIENTS 
SET NIVEAU_FIDELITE = 'PLATINE', TOTAL_ACHATS = 10000 
WHERE ID_CLIENT = 1;

-- If the above doesn't work (case sensitivity), try:
-- UPDATE clients SET niveau_fidelite = 'PLATINE', total_achats = 10000 WHERE id_client = 1;

-- Verify the update
SELECT ID_CLIENT, NOM, PRENOM, TOTAL_ACHATS, NIVEAU_FIDELITE 
FROM CLIENTS 
WHERE ID_CLIENT = 1;

-- If the above doesn't work (case sensitivity), try:
-- SELECT id_client, nom, prenom, total_achats, niveau_fidelite FROM clients WHERE id_client = 1;

COMMIT;

