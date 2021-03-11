#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo), m_row(0), m_col(0) {
}

StudentTextEditor::~StudentTextEditor()
{
	// TODO
}

bool StudentTextEditor::load(std::string file) // TODO: handle '\r' characters
{
	std::ifstream infile(file);
	if (!infile) return false;
	std::string line;
	while (std::getline(infile, line))
	{
		m_lines.push_back(line);
	}
	m_it = m_lines.begin();
	return true;
}

bool StudentTextEditor::save(std::string file) {
	std::ofstream outfile(file);
	if (!outfile) return false;
	for (std::list<std::string>::iterator i = m_lines.begin(); i != m_lines.end(); i++)
		outfile << *i << std::endl;
	return true;
}

void StudentTextEditor::reset() 
{
	m_col = 0;
	m_row = 0;
	m_lines.clear();
	m_it = m_lines.begin();
	getUndo()->clear();
}

void StudentTextEditor::move(Dir dir) 
{
	switch (dir)
	{
	case Dir::UP:
		if (m_row > 0)
		{
			--m_row;
			--m_it;
		}
		break;
	case Dir::DOWN:
		if (m_row < m_lines.size() - 1)
		{
			++m_row;
			++m_it;
		}
		break;
	case Dir::LEFT:
		if (m_col == 0 && m_row != 0)
		{
			--m_it;
			--m_row;
			m_col = (*m_it).size();
		}
		else if (m_col > 0)
			m_col--;
		break;
	case Dir::RIGHT:
		if (m_col == (*m_it).size() && m_row < m_lines.size()-1)
		{
			++m_it;
			++m_row;
			m_col = 0;
		}
		else if (m_col < (*m_it).size())
			m_col++;
		break;
	case Dir::HOME:
		m_it = m_lines.begin();
		m_col = 0;
		m_row = 0;
		break;
	case Dir::END:
		m_it = m_lines.end();
		--m_it;
		m_row = m_lines.size() - 1;
		m_col = (*m_it).size();
		break;
	}
}

void StudentTextEditor::del() // TODO: undo stack
{
	if (m_col == (*m_it).size() && m_row < m_lines.size() - 1)
	{
		std::string line = *++m_it;
		m_it = m_lines.erase(m_it);
		(*--m_it) += line;
	}
	else
	{
		(*m_it).erase(m_col, 1);
	}
}

void StudentTextEditor::backspace() { // TODO: undo stack
	if (m_col > 0)
	{
		(*m_it).erase(m_col - 1, 1);
		move(Dir::LEFT);
	}
	else if (m_col == 0 && m_row > 0)
	{
		std::string line = *m_it;
		m_it = m_lines.erase(m_it);
		m_col = (*--m_it).size();
		(*m_it) += line;
		--m_row;
	}
}

void StudentTextEditor::insert(char ch)  // TODO: undo stack
{
	if (!(m_col <= (*m_it).size())) return;
	int num_insert = 1;
	char ch_insert = ch;
	if (ch == '\t')
	{
		num_insert = 4;
		ch_insert = ' ';
	}
	(*m_it).insert(m_col, num_insert, ch_insert);
	m_col += num_insert;
}

void StudentTextEditor::enter()  // TODO: undo stack
{
	std::string line1 = (*m_it).substr(0, m_col);
	std::string line2 = (*m_it).substr(m_col, (*m_it).size());
	*m_it = line1;
	m_it++;
	m_it = m_lines.insert(m_it, line2);
	m_col = 0;
	m_row++;
}

void StudentTextEditor::getPos(int& row, int& col) const {
	row = m_row;
	col = m_col;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const 
{
	if (startRow > m_lines.size() || startRow < 0 || numRows < 0) return -1;
	lines.clear();
	std::list<std::string>::const_iterator i = m_lines.begin();
	int count = 0;
	for (; i != m_lines.end() && count < startRow; i++, count++);
	for (count = 0; i != m_lines.end() && count < numRows; i++, count++)
		lines.push_back(*i);
	return lines.size();
}

void StudentTextEditor::undo() 
{
	
}