# BLOOD TYPE by G2 from G3 EMSI
## Description
This project is an academic exercise aimed at managing a simple blood donation system. The program allows users to:

+ Add new users with their names, ages, and blood types.
+ Find compatible blood donors for a given recipient.
+ Find compatible recipients for a given donor.
+ List all registered users with their details.

## Features

+ Validation for user input (names, ages, and blood types).
+ A predefined blood compatibility matrix to determine donors and recipients.
+ Uses file manipulation to store and retrieve user data.

## Compatibility Rules

### The program follows standard blood compatibility rules:

| Blood Type        | Can Donate To     | Can Receive From   |
|     :---:         |     :---:         |     :---:          |
| AB+               | AB+               | All types          |
| AB-               | AB+, AB-          | AB-, A-, B-, O-    |
| A+                | A+, AB+           | A+, A-, O+, O-     |
| A-                | A+, A-, AB+, AB-  | A-, O-             |
| B+                | B+, AB+           | B+, B-, O+, O-     |
| B-                | B+, B-, AB+, AB-  | B-, O-             |
| O+                | O+, A+, B+, AB+   | O+, O-             |
| O-                | All types         | O-                 |