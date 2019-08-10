# krss
A terminal-based RSS viewer, right now just browses local RSS files

Right now just supports Mac because that's my only dev machine that
I use at the moment, feel free to add Windoze or Linux support I 
suppose. It'll run on Linux, but not all features are supported.

Features:

- Opens local RSS file
- (Mac only) Press "C" to copy the URL of an item
- (Mac only) Press "O" to open the URL with the default OS action (e.g., open 
  web browser)

I'd like to make it a bit more on par with other clients,
w/ downloading RSS files, managing collections, and otherwise
keeping a database.

# Dependencies

- libxml2
	- For RSS file parsing
- ncurses
	- For the TUI
