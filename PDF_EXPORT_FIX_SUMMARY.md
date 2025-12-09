# 📄 PDF Export Improvement - Sales Window

## Problem Fixed 🔧
The previous PDF export had overlapping text and poor formatting because it didn't account for the high resolution (DPI) of the PDF writer. The text was drawn using small pixel increments (e.g., 40px) which resulted in tiny, unreadable, and overlapping lines on a 1200 DPI document.

## Solution Implemented ✅

I completely rewrote the `exportSalesToPdf()` function in `saleswindow.cpp` to:

1.  **High-DPI Scaling**: 
    - Added a helper `mmToPx` to convert millimeters to dots based on the printer's resolution.
    - All dimensions (margins, line heights, font sizes) are now calculated dynamically.

2.  **Structured Table Layout**:
    - Implemented a proper table with defined column widths (ID, Date, Client, Montant, Paiement).
    - Added **borders** to all cells for clarity.
    - Added a **header row** with a light gray background.

3.  **Correct Data Mapping**:
    - Mapped the correct database columns to the PDF columns:
        - **ID** (Column 0)
        - **Date** (Column 3, formatted as dd/MM/yyyy HH:mm)
        - **Client** (Column 1)
        - **Montant** (Column 4, formatted with " DT")
        - **Paiement** (Column 10)

4.  **Pagination**:
    - Added logic to detect when the page is full and automatically create a new page (`writer.newPage()`).
    - The table header is repeated on every new page.

5.  **Professional Styling**:
    - Added a bold title "Rapport des Ventes".
    - Included the date range if a filter is active.
    - Added a footer with the generation timestamp.

## How to Test 🧪

1.  **Build and Run** the application.
2.  Go to the **Ventes** (Sales) window.
3.  Click on the **"Exporter Ventes en PDF"** button (bottom right).
4.  Save the PDF file.
5.  Open the PDF to verify:
    - Text is readable and not overlapping.
    - Data is organized in a clear table with borders.
    - Headers are present and styled.
    - Dates and prices are formatted correctly.

## Files Modified
- `saleswindow.cpp`: Replaced `exportSalesToPdf` function.

The PDF export should now be "pretty good" and professional! 🚀
