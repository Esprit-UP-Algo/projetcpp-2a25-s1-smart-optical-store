# 📄 Invoice Export Feature - Sales Window

## New Feature: Single Sale Invoice Export 🧾
I have added a new feature to export a **single selected sale** as a professional PDF invoice. This is distinct from the general sales report export.

## Implementation Details 🛠️

1.  **New Button**: Added "Exporter Facture PDF" button in the Sales History tab.
2.  **Selection Logic**: The user must select a sale from the history table to export it.
3.  **Professional Design**:
    - **Logo**: Includes the SightIQ logo (loaded from resources).
    - **Company Info**: Professional header with address and contact details.
    - **Invoice Details**: Invoice Number, Date, Seller Name.
    - **Client Info**: Dedicated box for client details (Name, ID).
    - **Itemized Table**: Clear table with Reference, Designation, Quantity, Unit Price, and Total.
    - **Totals Section**: Subtotal (HT), Discount (Remise), Tax (TVA), and Grand Total (TTC).
    - **Footer**: Professional footer with legal info placeholders.
4.  **High-DPI Support**: Uses the same robust scaling logic as the sales report to ensure crisp text and lines on all printers/screens.

## How to Use 🚀
1.  Go to the **Ventes** (Sales) window.
2.  Switch to the **Historique** (History) tab.
3.  **Select a sale** from the list (click on a row).
4.  Click the **"Exporter Facture PDF"** button (cyan button).
5.  Save the PDF file.

## Files Modified
- `saleswindow.h`: Added method declarations.
- `saleswindow.cpp`: Added button creation, signal connection, and export logic.

The generated invoice is designed to look like a formal commercial document suitable for printing and giving to customers. ✨
