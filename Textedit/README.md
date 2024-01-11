# Textedit
- Basic terminal text editor
- Similar to vi(m)
- My first attempt of text edit of any kind without any inspiration from code

## Instalation
 - Simply git clone and run `make` in this directory

## Keybinds
### Normal mode
- Default mode
- `w` to write to disk
- `q` to quit
- `d` to delete line
- `i` to enter insert mode

### Insert mode
- Character ` to exit this mode (key under esc)
- `ENTER` adds linebreak
- `BACKSPACE` deletes character before cursor
- Editor should accept any other character, `TAB` seems broken though and will probably need preprocessing in code

## Features:
#### Name and current line/total number of lines

![](https://github.com/Hikari03/personal_programs/assets/39591367/e8967f7b-d9ae-4d39-a0c0-813df9a6ecdc)

#### Current mode

![](https://github.com/Hikari03/personal_programs/assets/39591367/ecba457d-ae02-4e9b-80b9-8d3c7073edf8)

#### State of save (on right from mode display)

- `red` file doesn't exist on disk
- `blue` file is edited
- `green` file is saved

![](https://github.com/Hikari03/personal_programs/assets/39591367/13e44963-b9d0-455b-b72a-bf6b2e147a93)

## TODO

- [ ] Try to rewrite using curses library to reduce render overhead and maybe use esc to exit insert mode
