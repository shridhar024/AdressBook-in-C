# 📒 AddressBook — Terminal Address Book in C

A lightweight, terminal-based address book application written in C.  
Store, search, edit, and delete contacts — all from your command line, with data saved persistently across sessions.

---

## ✨ Features

- ➕ **Add contacts** — with input validation (no digits in names, no letters in phone numbers, valid email format)
- 📋 **List contacts** — view all saved contacts in a clean numbered format
- 🔍 **Search contacts** — case-insensitive partial search by name or phone number
- ✏️ **Edit contacts** — update any field while keeping others unchanged
- 🗑️ **Delete contacts** — with confirmation prompt before removal
- 💾 **Persistent storage** — contacts are saved to a binary file and reloaded on every run
- 🎨 **Coloured terminal output** — uses ANSI escape codes for a better user experience

---

## 🗂️ Project Structure

```
AddressBook/
├── src/
│   ├── main.c              # Entry point, menu loop
│   └── add_contacts.c      # All contact operations + file I/O
├── include/
│   ├── contacts.h          # Struct definition & function declarations
│   └── coloured_text.h     # ANSI colour macros
├── build/                  # Compiled binary goes here
├── Makefile
└── README.md
```

---

## 🛠️ Requirements

- GCC (GNU C Compiler)
- Linux or macOS terminal
- `make`

---

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/address-book-c.git
cd address-book-c
```

### 2. Create the build directory

```bash
mkdir -p build
```

### 3. Compile

```bash
make
```

Or manually:

```bash
gcc -Wall -Iinclude src/main.c src/add_contacts.c -o build/addressbook
```

### 4. Run

```bash
./build/addressbook
```

---

## 📸 Preview

```
-----Address Book-----
1. Create Contact
2. List Contacts
3. Search for a contact
4. Edit a contact
5. Delete a contact
6. Exit
Enter your choice:
```

---

## 💡 How It Works

- Contacts are stored in a binary file `contacts.dat` using `fwrite` / `fread`
- On every launch, existing contacts are automatically loaded from the file
- On every add, edit, or delete — the file is auto-saved
- Each contact holds: **Name**, **Phone Number**, and **Email**
- Maximum of **100 contacts** supported (`MAX_CONTACTS` in `contacts.h`)

---

## 📋 Input Validation

| Field  | Rule |
|--------|------|
| Name   | No digits allowed |
| Phone  | No letters allowed |
| Email  | Must contain `@` and `.` |

If invalid input is entered, the user is prompted to retry or cancel.

---

## 🧹 .gitignore (recommended)

```
build/addressbook
*.o
contacts.dat
```

---

## 🤝 Contributing

Pull requests are welcome! If you find a bug or want to add a feature (e.g. sorting contacts, exporting to CSV), feel free to open an issue or PR.

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

> Built with ❤️ in C — keeping it simple and fast.
