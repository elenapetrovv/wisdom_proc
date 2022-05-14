#include "Header.h"
#include <string>
using namespace std;

void In(ifstream& ifst, aphorism_wisdom& f) {

	ifst >> f.author;
}
void Out(ofstream& ofst, aphorism_wisdom& f) {
	ofst << "It is an aphorism. Author: " << f.author << endl;
}
void In(ifstream& ifst, saying_wisdom& f) {
	ifst >> f.country;
}
void Out(ofstream& ofst, saying_wisdom& f) {
	ofst << "It is a saying. Country: " << f.country << endl;
}
void In(ifstream& ifst, riddle_wisdom& f) {
	ifst >> f.answer;
}
void Out(ofstream& ofst, riddle_wisdom& f) {
	ofst << "It is a riddle. Answer: " << f.answer << endl;
}

wisdom* InWisdom(ifstream& ifst) {
	wisdom* sh;
	int k = 0;
	ifst >> k;
	//aphorism_wisdom* a;
	//saying_wisdom* s;
	switch (k) {
	case 1:
		sh = new wisdom;
		sh->key = wisdom::type::aphorism;
		ifst >> sh->text;
		In(ifst, sh->a);
		break;
	case 2:
		sh = new wisdom;
		sh->key = wisdom::type::saying;
		ifst >> sh->text;
		In(ifst, sh->s);
		break;
	case 3:
		sh = new wisdom;
		sh->key = wisdom::type::riddle;
		ifst >> sh->text;
		In(ifst, sh->s);
		break;
	default:
		return 0;
	}
	ifst >> sh->rate;
	return sh;
}
void OutWisdom(ofstream& ofst, Node* container)
{
	ofst << "Text: " << container->thought->text << endl;
	if (container->thought->key == wisdom::type::aphorism)
	{
		//aphorism_wisdom* aw;
		//aw = (aphorism_wisdom*)(c->current->thought->aphorism);
		//aw = (aphorism_wisdom*)(c->current->thought);
		Out(ofst, container->thought->a);
	}
	else if (container->thought->key == wisdom::type::saying)
	{
		//saying_wisdom* sw;
		//sw = (saying_wisdom*)(c->current->thought->saying);
		//sw = (saying_wisdom*)(c->current->thought);
		Out(ofst, container->thought->s);
	}
	else
	{
		Out(ofst, container->thought->r);
	}
	ofst << "Subjective assessment on a ten-point scale: " << container->thought->rate << "/10 " << endl;
	ofst << "count of punctuation marks: " << CountSymbols(*container->thought) << endl;
}

void Clear(container* c) {
	c->current = NULL;
	c->size = 0;
	c->head = 0;
}

void InCont(ifstream& ifst, container* c) {
	while (!ifst.eof()) {

		Node* newNode = new Node;
		newNode->thought = InWisdom(ifst);
		//aphorism_wisdom* sh = (aphorism_wisdom*)newNode->sh->a;
		if (c->head == NULL)
		{
			c->head = newNode;
			c->head->next = newNode;
			c->head->prev = newNode;
			c->size = 1;
		}
		else
		{
			c->current = c->head;
			while (c->current->next != c->head)
			{
				c->current = c->current->next;
			}
			c->current->next = newNode;
			c->current->next->prev = c->current;
			c->current = c->current->next;
			c->current->next = c->head;
			c->head->prev = c->current;
			c->size++;
		}
	}
}
void OutCont(ofstream& ofst, container* c) {
	ofst << "Container contents " << c->size << " elements." << endl;

	int i = 1;
	if (c->head == NULL)
	{
		return;
	}
	//Sort(*c);
	c->current = c->head;
	do
	{
		ofst << i << ": ";
		OutWisdom(ofst, c->current);
		c->current = c->current->next;
		i++;
	} while (c->current != c->head);
}

int CountSymbols(wisdom& s) {
	int cnt = 0;
	string symbols = ".,!?;";
	for (int i = 0; i < s.text.length(); i++)
	{
		if (symbols.find(s.text[i]) < symbols.length())cnt++;
	}
	return cnt;
}

bool Compare(Node* w1, Node* w2)
{
	return CountSymbols(*w1->thought) < CountSymbols(*w2->thought);
}
void Sort(container& c)
{
	Node* curr1 = c.head;
	Node* curr2 = c.head;
	do {
		curr2 = curr1->next;
		while (curr2 != c.head) {
			if (Compare(curr1, curr2))
			{
				swap(curr1->thought, curr2->thought);
			}
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	} while (curr1 != c.head);
}
void OutAphorisms(ofstream& ofst, container* c)
{
	ofst << "Only Aphorisms: " << endl;
	int i = 1;
	if (c->head == NULL)
	{
		return;
	}
	c->current = c->head;
	do
	{
		ofst << i << ": ";
		if (c->current->thought->key == wisdom::type::aphorism)
		{
			//ofst << "Text: " << c->current->thought->text << endl;
			OutWisdom(ofst, c->current);
		}
		else
		{
			ofst << endl;
		}
		c->current = c->current->next;
		i++;
	} while (c->current != c->head);
}
bool fileCheck(ifstream& ifst, ofstream& ofst)
{
	bool result = true;
	string digits = "0123456789";
	char tmp[100];
	string tmps;

	if (!ifst.is_open())
	{
		cout << "Input file was not found.";
		exit(1);
	}
	if (!ofst.is_open())
	{
		cout << "Output file was not found.";
		exit(1);
	}
	int cnt = 1;
	//type check
	while (!ifst.eof())
	{
		ifst.getline(tmp, 100, '\n');
		tmps = (tmp);
		if (tmps == "")
		{
			cout << cnt << " Error: Type is a blank string.\n";
			result = false;
			exit(1);
		}
		for (int i = 0; i < tmps.length(); i++)
		{
			if (!(digits.find(tmps[i]) < digits.length()))
			{
				cout << cnt << " Error: Type definition contains incorrect characters.\n";
				result = false;
				exit(1);
			}
		}
		int type = std::stoi(tmps);
		if (type <= 0 || type > 3)
		{
			cout << cnt << " Error: Type is out of range.\n";
			result = false;
			exit(1);
		}
		//
		//text
		ifst.getline(tmp, 100, '\n');
		tmps = (tmp);
		if (tmps == "")
		{
			cout << cnt << " Error: Text is a blank string.\n";
			result = false;
			exit(1);
		}
		//
		//for different types
		switch (type)
		{
		case 1:
		{
			//aphorism - author
			ifst.getline(tmp, 100, '\n');
			tmps = (tmp);
			if (tmps == "")
			{
				cout << cnt << " Error: The aphorism's author is a blank string.\n";
				result = false;
				exit(1);
			}
			for (int i = 0; i < tmps.length(); i++)
			{
				if (tmps[i] >= '0' && tmps[i] <= '9')
				{
					cout << cnt << " Error: The aphorism's author contains incorrect characters.\n";
					result = false;
					exit(1);
				}
			}
			break;
		}
		case 2:
		{
			//saying - country
			ifst.getline(tmp, 100, '\n');
			tmps = (tmp);
			if (tmps == "")
			{
				cout << cnt << " Error: The country is a blank string.\n";
				result = false;
				exit(1);
			}
			for (int i = 0; i < tmps.length(); i++)
			{
				if (tmps[i] >= '0' && tmps[i] <= '9')
				{
					cout << cnt << " Error: The saying's country contains incorrect characters.\n";
					result = false;
					exit(1);
				}
			}
			break;
		}
		case 3:
		{
			// riddle - answer
			ifst.getline(tmp, 100, '\n');
			tmps = (tmp);
			if (tmps == "")
			{
				cout << cnt << " Error: The answer is a blank string.\n";
				result = false;
				exit(1);
			}
			for (int i = 0; i < tmps.length(); i++)
			{
				if (tmps[i] >= '0' && tmps[i] <= '9')
				{
					cout << cnt << " Error: The riddle's answer contains incorrect characters.\n";
					result = false;
					exit(1);
				}
			}
			break;
		}
		}
		//
		//rate
		ifst.getline(tmp, 100, '\n');
		tmps = (tmp);
		if (tmps == "")
		{
			cout << cnt << " Error: The rate is a blank string.\n";
			result = false;
			exit(1);
		}
		for (int i = 0; i < tmps.length(); i++)
		{
			if (!(digits.find(tmps[i]) < digits.length()))
			{
				cout << cnt << " Error: The origin contains incorrect characters.\n";
				result = false;
				exit(1);
			}
		}
		int rate = std::stoi(tmps);
		if (rate < 0 || rate > 10)
		{
			cout << cnt << " Error: The rate is out of range.\n";
			result = false;
			exit(1);
		}
		//
		cnt++;
	}
}