# QUICK COPY-PASTE GUIDE - Role-Based Access Control

## ✅ Header File Already Done!
The file `fournisseurwindow.h` is already updated with:
- `QString userRole;` member variable
- `void configureRoleBasedAccess();` method declaration

---

## 📝 Now Edit `fournisseurwindow.cpp`

### STEP 1: Update `getInstance()` Method

**Find around line 49-75:**
```cpp
FournisseurWindow* FournisseurWindow::getInstance(const QString &role, QWidget *parent)
{
    if (instance == nullptr)
    {
        instance = new FournisseurWindow(parent);
        // ADD THESE 2 LINES ↓↓↓
        instance->userRole = role;
        instance->configureRoleBasedAccess();
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}
```

---

### STEP 2: Update Constructor

**Find around line 60-70:**
```cpp
FournisseurWindow::FournisseurWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FournisseurWindow)
    , selectedId(-1)
    , userRole("")  // ADD THIS LINE (with comma above!)
{
    ui->setupUi(this);
    afficherFournisseurs();
    ui->pushButton_delete->setEnabled(false);
}
```

---

### STEP 3: Add New Method at End of File

**Scroll to the VERY BOTTOM of `fournisseurwindow.cpp` and add this method BEFORE the last `}`:**

```cpp
void FournisseurWindow::configureRoleBasedAccess()
{
    qDebug() << "Configuring access for role:" << userRole;
    
    if (userRole.toLower() == "fournisseur")
    {
        // Hide navigation buttons
        ui->pushButton->setVisible(false);      // Stock
        ui->pushButton_2->setVisible(false);    // Ventes
        ui->pushButton_3->setVisible(false);    // Clients
        ui->pushButton_4->setVisible(false);    // Employés
        
        qDebug() << "Navigation restricted for fournisseur role";
        
        QMessageBox::information(this, "Mode Fournisseur",
            "Vous êtes connecté en mode Fournisseur.\n"
            "Accès limité au module de gestion des fournisseurs.");
    }
    else
    {
        qDebug() << "Full access granted for role:" << userRole;
    }
}
```

---

## 🔨 BUILD & TEST

1. **Save** the file (Ctrl+S)
2. **Clean** the project: Build → Clean All
3. **Rebuild**: Build → Rebuild All (Ctrl+Shift+B)
4. **Run** the application
5. **Login** with fournisseur role
6. **Check**: Navigation buttons should be HIDDEN!

---

## 🎯 WHAT WILL HAPPEN

### Before (Current):
- Fournisseur user sees ALL navigation buttons (Stock, Ventes, Clients, Employés, Fournisseur)
- Can navigate to any module ❌

### After (With Fix):
- Fournisseur user sees ONLY Fournisseur-related content
- Navigation buttons (Stock, Ventes, Clients, Employés) are HIDDEN ✅
- Popup message: "Mode Fournis seur - accès limité" ✅

---

## 📍 EXACT LOCATIONS IN YOUR FILE

Open `fournisseurwindow.cpp` and use **Ctrl+G** (Go to Line):

| What to Add | Approximate Line | Method Name |
|-------------|------------------|-------------|
| 2 lines in getInstance() | Line 49-75 | `FournisseurWindow::getInstance()` |
| 1 line in constructor | Line 60-70 | `FournisseurWindow::FournisseurWindow()` |
| New method at end | Last lines | `configureRoleBasedAccess()` |

---

## ❓ TROUBLESHOOTING

### Issue: Can't find getInstance() method
**Solution:** Press Ctrl+F, search for: `getInstance(const QString`

### Issue: Can't find constructor
**Solution:** Press Ctrl+F, search for: `FournisseurWindow::FournisseurWindow(QWidget`

### Issue: Buttons still visible
**Solution:** 
1. Check that you saved the file
2. Make sure you rebuilt (not just build)
3. Check that login is passing "fournisseur" as the role parameter
4. Add `qDebug() << "Role received:" << role;` in getInstance to verify

---

## ✅ FILES TO EDIT

- ✅ `fournisseurwindow.h` - ALREADY DONE
- ⏳ `fournisseurwindow.cpp` - YOU NEED TO EDIT (3 simple changes)

---

**All the code you need is in `EXACT_CODE_TO_COPY.txt`!**

Just copy-paste the 3 sections and you're done! 🎉
