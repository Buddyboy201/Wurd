#include "EditorGui.h"
#include "TextIO.h"
#include "StudentTextEditor.h"
#include "StudentUndo.h"
#include <iostream>
#include <string>

// Do not change anything in this file other than these initializer values
const std::string DICTIONARYPATH = "C:/dev/CS32/winskel/winskel/Wurd/Wurd/dictionary.txt";
const int FOREGROUND_COLOR = COLOR_WHITE;
const int BACKGROUND_COLOR = COLOR_BLACK;
const int HIGHLIGHT_COLOR  = COLOR_RED;
// Choices are COLOR_x, where x is WHITE, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN

int main(int argc, char* argv[]) {
	TextIO ti(FOREGROUND_COLOR, BACKGROUND_COLOR, HIGHLIGHT_COLOR);

	EditorGui editor(LINES, COLS);

	/*if (!editor.loadDictionary(DICTIONARYPATH)) {
		editor.writeStatus("Error: Can not load dictionary " + DICTIONARYPATH);
	}
	if (argc == 2) {
		editor.loadFileToEdit(argv[1]);
	}*/
	//editor.loadFileToEdit("C:/dev/CS32/winskel/winskel/Wurd/Wurd/civildis.txt");
	//editor.run();
	StudentUndo undo;
	undo.submit(StudentUndo::Action::DELETE, 0, 0, 'a');
	undo.submit(StudentUndo::Action::DELETE, 0, 1, 'b');
	undo.submit(StudentUndo::Action::DELETE, 0, 2, 'c');
	int count, row, col;
	std::string text;
	StudentUndo::Action act = undo.get(row, col, count, text);
	std::cout << text << std::endl;
	std::cout << count << std::endl;
	std::cout << row << " " << col;
}       
