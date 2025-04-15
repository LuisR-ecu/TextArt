# 🎨 TextArt

TextArt is a simple ASCII art editor built with C++. It allows users to load `.txt` files into a character-based canvas, edit the characters interactively using arrow keys and keyboard input, and save the result back to a file.

It’s a lightweight console-based tool ideal for learning file I/O, 2D arrays, and raw keyboard input handling in C++.

---

## 🧠 Features

- 🖋️ Edit ASCII art interactively in a grid layout (22x80)
- 💾 Load and save `.txt` art files to/from a canvas
- ⌨️ Navigate and modify characters using arrow keys and typing
- 📁 Reads and writes files from a local `SavedFiles/` folder
- 🔒 Handles invalid file access gracefully with error messages

---

## 🧰 Technologies Used

- C++ (Standard + Windows-specific headers)
- Console-based UI via `<conio.h>` and `<windows.h>`
- Basic file handling via `<fstream>`

---

## 🚀 How to Build and Run

1. Open `TextArt.sln` in Visual Studio
2. Build the solution (Debug or Release)
3. Run the program in the terminal window
4. Use your keyboard to edit the canvas, then save your changes

> ⚠️ Note: This program is designed for **Windows** environments due to its use of `conio.h` and `getch()` for real-time input.

---

## 📁 Folder Structure

```
TextArt/
├── TextArt.cpp              # Main ASCII art editor
├── TextArt.sln              # Visual Studio solution
├── TextArt.vcxproj          # VS project file
├── SavedFiles/              # Where edited .txt art is saved
└── .gitignore               # Ignores temp & build files
```

---

## 📸 Example Use

- Load an ASCII file into the canvas
- Use arrow keys to move your cursor
- Type characters to draw or erase
- Press `ESC` to exit or trigger save prompt

---

## 👤 Author

**Luis Ramirez**  
Undergraduate Research Assistant  
[B.A. in Computer Science - East Carolina University (2023–2026)](https://github.com/LuisR-ecu)  
📄 [Resume / Research Profile](www.linkedin.com/in/ramirez-luis-hernandez)

---

## 📌 Notes

- Be sure your terminal window is at least 80 characters wide for proper display.
- Files are stored in `SavedFiles/` relative to the executable.
- You can easily extend this to support different canvas sizes, colors, or file formats.

---
