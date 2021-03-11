#include "StudentUndo.h"

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) 
{
	ActionObj act(action, row, col, ch);
	S.push(act);
}

StudentUndo::Action StudentUndo::get(int &row, int &col, int& count, std::string& text) {
    if (S.empty()) return Action::ERROR;
	while (!S.empty())
	{
		ActionObj act = S.top();
		S.pop();
		switch (act.action)
		{
		case Action::INSERT:
			count = batch(act, row, col, text);
			return Action::DELETE;
			break;
		case Action::DELETE:
			count = batch(act, row, col, text);
			return Action::INSERT;
			break;
		case Action::JOIN:
			break;
		case Action::SPLIT:
			break;
		}
	}
}

void StudentUndo::clear() {
	while (!S.empty())
		S.pop();
}

int StudentUndo::batch(ActionObj act, int& row, int& col, std::string& text)
{
	int count = 1;
	row = act.row;
	col = act.col;
	if (act.action == Action::DELETE) text += act.data;
	while (!S.empty() && act.isBatchable(S.top()))
	{
		ActionObj batch_act = S.top();
		S.pop();
		if (act.action == Action::DELETE)
		{
			text += batch_act.data;
			count++;
		}
		else if (act.action == Action::INSERT)
		{
			count++;
			row = batch_act.row;
			col = batch_act.col;
		}
		act = batch_act;
	}
	return count;
}
