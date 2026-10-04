# PAP521S_GROUP_PROJECT_PART_A
MUNICIPALITY FINANCIAL MANAGEMENT SYSTEM 
## Group Members & Responsibilities
| Student Name | Student Number | Assigned Role | Primary Responsibility & Modules |
| :--- | :--- | :--- | :--- |
| SELMA PAULUS | 224028243 | Lead Developer | Employee Management (`employees.c`, `employees.h`) |
| LAMEK HIDENGWA| 226135764| Developer | Budget Management (`budget.c`, `budget.h`) |
| IIYAMBO NANGOMBE| 224049844| Developer | Supplier Management (`suppliers.c`, `suppliers.h`) |
| ANDREAS SHIKONGO | 226035271 | Developer | Asset Management (`assets.c`, `assets.h`) |
| ALZAREO DAWEB|226010935| Developer | Reports Module (`reports.c`, `reports.h`) |
| MUYAKALE | 226161730 | Systems Analyst | Integration, Main Menu, & Data Validation (`utils.c`) |
| JAMES KAMBARA | 226169057| QA & Admin | GitHub Lead, Testing, & Technical Documentation |

### Project description
The Municipal Financial Management System (MFMS) is a foundational, menu-driven C application designed to assist municipal administration in managing core operational and financial data. Built using standard C (C99), the system provides an integrated solution for employee payroll calculations, departmental budget tracking, supplier directory management, municipal asset recording, and financial summary reporting.   This project serves as the Stage A foundation for the municipality's software architecture, demonstrating core C programming concepts such as modular function design, dynamic input validation, array processing, struct data management, and string manipulation. 
#### System features
### System Features

| Module | Sub-Module / Feature | Description & Functionality |
| :--- | :--- | :--- |
| **Main Menu** | Navigation | Provides a menu-driven interface for selecting system modules[cite: 2]. |
| | Input Validation | Catches invalid menu options and numerical entry errors gracefully[cite: 6]. |
| **Employee Management** | Record Entry | Captures Employee ID, Name, Department, Basic Salary, Housing Allowance, and Transport Allowance[cite: 2, 3]. |
| | Payroll Calculation | Computes total gross salary automatically based on basic pay and allowances[cite: 2]. |
| | Search & Display | Tabulates all employee records and supports ID lookup via string comparison (`strcmp`)[cite: 2, 5]. |
| **Budget Management** | Allocation Tracking | Records departmental allocated budgets and operational expenditures[cite: 3]. |
| | Balance Calculation | Computes remaining balances and flags over-budget departments (`EXCEEDED` vs `WITHIN BUDGET`)[cite: 3]. |
| | Financial Summary | Displays clear departmental budget statuses for municipal oversight[cite: 3]. |
| **Supplier Management** | Directory | Stores Supplier ID, Supplier Name, Email, Telephone Number, and Location/Town[cite: 3]. |
| | Lookup & Display | Displays active suppliers and supports string search by supplier name[cite: 4]. |
| **Asset Management** | Asset Register | Tracks municipal assets including vehicles, computers, buildings, equipment, and office furniture[cite: 4]. |
| | Record Fields | Captures Asset ID, Name, Type, Purchase Value, Department, and Condition[cite: 4]. |
| | Search & Display | Displays complete asset listings and supports search by Asset ID[cite: 4]. |
| **Reports** | Employee Report | Summarizes total headcount, average salary, highest salary, and lowest salary[cite: 4]. |
| | Budget Report | Summarizes total allocated budget, total expenditure, remaining balance, and over-budget count[cite: 4, 5]. |
| | Supplier & Asset Reports | Displays registered supplier counts, asset counts, and total asset portfolio valuation[cite: 5]. |
| | Full Summary | Generates a consolidated financial and operational summary report[cite: 4, 5]. |
| **Data Validation** | Input Safeguards | Blocks negative inputs for salaries, budgets, expenditures, and asset prices[cite: 6]. |
