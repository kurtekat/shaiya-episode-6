# SetItemTool

## Environment

Windows 10

Visual Studio 2022

C# 7.3

.NET Framework 4.8

# How-to-use

Open the project with Visual Studio. Go to the **Solution Explorer** tab, right-click the solution and choose **Restore NuGet Packages** to install [Parsec](https://github.com/matigramirez/Parsec). Build the project and copy **SetItem.SData** to the output directory (e.g. bin/Release). Run the application and follow the prompts.

## Code Page Identifiers

https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers

## Client Format

The output file will be encrypted.

## Server Format

The application will extract the file to a format that is easy to read and edit.

```json
"synergies": [
  {
    "strength": 0,
    "dexterity": 0,
    "intelligence": 0,
    "wisdom": 0,
    "reaction": 0,
    "luck": 0,
    "health": 0,
    "mana": 0,
    "stamina": 0,
    "attackPower": 0,
    "rangedAttackPower": 0,
    "magicPower": 0
  },
```

When you are done, run the application again, choose the compile option, and then choose the server format. Copy the output file to **PSM_Client/Bin/Data**. The output file will be not be encrypted.
