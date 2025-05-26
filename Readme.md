# `template` — Fast Project Bootstrapping Tool

A lightweight C program to quickly start new projects from templates.
Inspired by tools like `dotnet new`, but works with **any language**.

---

## Installation

Clone the repository:

```sh
git clone https://github.com/codespace0x25/template.git
cd template
```

Then install the binary and available templates:

```sh
make install
make install-templates
```

> Both steps will ask for your **sudo password**.
> **Do not** run these with `sudo` directly.

---

##  Requirements

* [`rsync`](https://rsync.samba.org/) – Used to copy template directories
  Install via your package manager:

```sh
# Debian/Ubuntu
sudo apt install rsync

# Arch
sudo pacman -S rsync

# Fedora
sudo dnf install rsync
```

---

## How It Works

The tool uses predefined templates organized by language and project type.

Example structure:

```
templates/
└── C/
    └── basic/
        ├── makefile
        └── src/
            └── main.c
└── PY/
    └── flask-api/
        ├── app.py
        └── requirements.txt
```

To create a new project:

```sh
template new C basic -o my-new-project
```

This copies the contents of `templates/C/basic` into a folder called `my-new-project`.

---

## Add New Language or Template

No C programming required! Just:

1. Create a language directory (e.g., for Python):

   ```sh
   mkdir -p templates/PY
   ```

2. Add a subfolder for the project type:

   ```sh
   mkdir templates/PY/basic
   ```

3. Set up your boilerplate project in that folder.

4. Register your new templates:

   ```sh
   make install-templates
   ```

---

## Uninstallation (Optional)

To remove the program and templates:

```sh
sudo rm /usr/bin/template
sudo rm -r /usr/share/templates
```

---

Let me know if you'd like:

* Shell autocompletion
* `template list` command help
* A `--force` overwrite flag

Or I can convert this to `man` page style.
