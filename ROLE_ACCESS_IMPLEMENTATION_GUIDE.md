# ROLE-BASED ACCESS CONTROL FOR FOURNISSEUR MODULE
## Implementation Guide

This guide shows you how to restrict navigation when a user logs in with the "fournisseur" role.

---

## CHANGES ALREADY MADE ✅

**File: `fournisseurwindow.h`**
- Added `QString userRole;` member variable (line 42)
- Added `void configureRoleBasedAccess();` method declaration

---

## STEP 1: Find Navigation Button Names

**You need to identify the names of navigation buttons in your UI.**

### How to Find Button Names:
1. Open `fournisseurwindow.ui` in Qt Designer (Qt Creator)
2. Look at the left side navigation menu or top menu bar
3. Click on each navigation button
4. Check the **Object Inspector** panel for the object name
5. Write down button names like: `pushButton_stock`, `pushButton_employe`, etc.

**Common button names to look for:**
- Stock/Products: `pushButton_stock`, `pushButton_produit`, `pushButton_inventory`
- Employees: `pushButton_employe`, `pushButton_employee`
- Sales: `pushButton_ventes`, `pushButton_sales`
- Clients: `pushButton_clients`, `pushButton_customer`
- Dashboard: `pushButton_dashboard`, `pushButton_accueil`

---

## STEP 2: Update getInstance() Method

**File: `fournisseurwindow.cpp` (around line 49-75)**

Find this method and ADD the two marked lines:

```cpp
FournisseurWindow* FournisseurWindow::getInstance(const QString &role, QWidget *parent)
{
    if (instance == nullptr)
    {
        instance = new FournisseurWindow(parent);
        instance->userRole = role;  // <-- ADD THIS LINE
        instance->configureRoleBasedAccess();  // <-- ADD THIS LINE
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}
```

---

## STEP 3: Update Constructor

**File: `fournisseurwindow.cpp` (around line 60-70)**

Find the constructor and ADD the userRole initialization:

```cpp
FournisseurWindow::FournisseurWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FournisseurWindow)
    , selectedId(-1)
    , userRole("")  // <-- ADD THIS LINE
{
    ui->setupUi(this);
    afficherFournisseurs();
    ui->pushButton_delete->setEnabled(false);
}
```

---

## STEP 4: Add configureRoleBasedAccess() Method

**File: `fournisseurwindow.cpp` (add at the END of the file, before the closing brace)**

**TEMPLATE - Replace button names with your actual ones:**

```cpp
void FournisseurWindow::configureRoleBasedAccess()
{
    // Restrict access for "fournisseur" role users
    if (userRole.toLower() == "fournisseur")
    {
        qDebug() << "Configuring restricted access for fournisseur role";
        
        // ========================================
        // TODO: REPLACE THESE with YOUR ACTUAL button names!
        // ========================================
        
        // Example - Hide navigation buttons:
        // if (ui->pushButton_stock) ui->pushButton_stock->setVisible(false);
        // if (ui->pushButton_employe) ui->pushButton_employe->setVisible(false);
        // if (ui->pushButton_ventes) ui->pushButton_ventes->setVisible(false);
        // if (ui->pushButton_clients) ui->pushButton_clients->setVisible(false);
        // if (ui->pushButton_dashboard) ui->pushButton_dashboard->setVisible(false);
        
        // OR if using menu bar:
        // if (ui->menuStock) ui->menuStock->setEnabled(false);
        // if (ui->menuEmploye) ui->menuEmploye->setEnabled(false);
        
        // OR if using a list widget for navigation:
        // for (int i = 0; i < ui->listWidget_menu->count(); ++i) {
        //     QListWidgetItem *item = ui->listWidget_menu->item(i);
        //     QString itemText = item->text().toLower();
        //     if (itemText != "fournisseurs" && itemText != "fournisseur") {
        //         item->setHidden(true);
        //         item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        //     }
        // }
        
        QMessageBox::information(this, "Mode Fournisseur",
            "Vous êtes connecté en mode Fournisseur.\n"
            "Accès limité au module de gestion des fournisseurs.");
    }
    else
    {
        // Full access for admin and other roles
        qDebug() << "Full access granted for role:" << userRole;
    }
}
```

---

## STEP 5: Add Role Checks to Navigation Slots (OPTIONAL)

**File: `fournisseurwindow.cpp` (around lines 85-105)**

Find navigation slot methods and ADD role checks at the beginning:

### Example for Stock/MainWindow navigation:

```cpp
void FournisseurWindow::on_pushButton_stock_clicked()  // Use your actual method name
{
    // ADD THIS CHECK at the start
    if (userRole.toLower() == "fournisseur")
    {
        QMessageBox::warning(this, "Accès refusé",
            "Vous n'avez pas l'autorisation d'accéder à ce module.\n"
            "Contactez l'administrateur pour plus d'informations.");
        return;
    }
    
    // Original code continues here
    MainWindow::getInstance();
    this->hide();
}
```

Repeat this check for ALL navigation methods around lines 85-105.

---

## QUICK IMPLEMENTATION CHECKLIST

- [ ] **Step 1:** Open `fournisseurwindow.ui` and write down all navigation button names
- [ ] **Step 2:** Update `getInstance()` method - add 2 lines (userRole = role, configure AccessControl)
- [ ] **Step 3:** Update constructor - add userRole("") initialization
- [ ] **Step 4:** Add `configureRoleBasedAccess()` method with YOUR button names
- [ ] **Step 5:** (Optional) Add role checks to navigation slot methods
- [ ] **Step 6:** Build project (Ctrl+B)
- [ ] **Step 7:** Test with fournisseur role login
- [ ] **Step 8:** Verify navigation is restricted
- [ ] **Step 9:** Test with admin role - verify full access

---

## TESTING

1. **Login as "fournisseur" role user**
   - Should see Fournisseur interface
   - Navigation buttons to other modules should be hidden/disabled
   - All fournisseur features should work normally

2. **Login as "admin" or other role**
   - Should see all navigation options
   - Can navigate to any module

---

## NEED HELP?

If you're not sure about the button names:
1. Take a screenshot of the Fournisseur window showing the navigation menu
2. Or share the content of the navigation section from the UI file
3. I'll help you identify the exact button names to hide

---

**Current Status:**
- ✅ Header file updated with `userRole` and `configureRoleBasedAccess()`
- ⏳ Waiting for you to complete the .cpp implementation
- ⏳ Need actual navigation button names from your UI
