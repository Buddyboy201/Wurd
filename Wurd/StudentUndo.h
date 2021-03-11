#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <list>
#include <stack>
#include <cmath>

class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
	class ActionObj
	{
	public:
		ActionObj(Action A, int R, int C, char ch)
			: action(A), row(R), col(C), data(ch)
		{}

		bool isBatchable(ActionObj other_act)
		{
			switch (action)
			{
			case Action::DELETE:
			case Action::INSERT:
				return (row == other_act.row && abs(col - other_act.col) <= 1
					&& action == other_act.action);
			default:
				return false;
			}
		}

		Action action;
		int row;
		int col;
		char data;
	};

	int batch(ActionObj act, int& row, int& col, std::string& text);



	std::stack<ActionObj> S;
};

#endif // STUDENTUNDO_H_
