This is a DEMO pharmacy app to demonstrate C++ knowledge and organization skill.

It uses Qt Creator for IDE and GUI development, and PostgreSQL for the database.

Current functionality includes:
    Adding and editing a doctor
    Adding and editing a customer who includes a doctor

TODO items:
    Add layered exception handling
    Add more robust logging techniques.
    Add Unit Tests.
    
    Add doctor edit dialog.
    Add input validation and bad user request. (trying to delete a customer that has a doctor assigned)
    Refactor assignments/conversions on UI to use ui adaptors.
    Maybe mark files/Folders that are C++ only and restructure/rename if needed.
    ManageCustomersWindow and ManageCustomersWindow
        refactor on_edit... and on_add... into reusable/shareable subroutines.
    Qsqlrepostiries
        Maybe return Q types instead of list (see getAllCustomersData) or move conversions to helper.
    Choose between #pragma or #ifndef for consistency
    Remove unnecessary 'main' branch.
