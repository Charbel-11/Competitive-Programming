#include <stdio.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include<string>
using namespace std;
//typedefs
typedef char WORD;
typedef std::vector<WORD> instruction_t;
typedef instruction_t::iterator instruction_pointer;

typedef std::vector<WORD> memory_t;
typedef memory_t::iterator memory_pointer;


//structs
struct environment
{
	memory_t memory;
	instruction_t instructions;

	instruction_pointer ip;
	memory_pointer mp;

	environment() : memory(3000)
	{
		clear();
		mp = memory.begin();
	}
	void clear()
	{
		instructions.clear();
		ip = instructions.begin();
	}
};

//prototypes
void interpret(environment& env);
int from_stream(environment& env, string& s, int open_brackets = 0);
void print_word(WORD word);

void solve() {
	environment env;
	string s = ">,<>>,>,<[->->+<><<]+->>[-<<+>>]<+-><><<<[-+->-<+-<+>]<[->+<]><>>>>>><>++->>+->>>>>+[>><>>>[-]<[-<>-+]<<>[-+-]-++-+-<[-]<><<>[+---+]<><<<<+-<<<<>-+<><<<><+-<<[->>>>>>>+>>>>>-+>+<<<><<<><<<<<<<<<]>[->>>>><><>><>>+>>>>>>+<<<<<><<<<<+-<<<<]>[->>>>>>><>+>>>>-+><>>+<<<<<<+-<<<<><<<<-+><]>>-++-+>+-+[<-]<[->><>++-<<<]>>>>[-<<<+--+<<<<+>><>>>>>>]>[-<<-+<<<<<+<>>+->>>>>>]>[-<<<<><<<><<+>>>>>>>]>>>>>><>>+[-<<<<+--+<><+-<<<<<<[->>+>>+<<<<]+->[->>+>>+-+<<<<]>[-<<+>>]>[-<<+>>]+[[<>-]-++>[<-]<+-[+--><>><>-<<<]>>-+->>>+>[<-]<+-[->+>[-<-]<[>>[-<<-+->]-<<[->><->+->-+-<<<<]]<]>>-<<<<<+>[><<-]<[>+->[-+<<->]<<[<]]>-+-]>>>>><>>>><>+]-<<<>+-<<<>+>-++[<-]<[-+>>+[<<<>->-+]<<[>>>+[<-+<<->>]<<<[<]]]>-]>>>>[-]<<<<<<<-+<><<<<<<<[-]>>+>+[<-]<[->>+<><<<]>+>[<-]<[>>[<<->]<<[<]]>-[+>>>>>>><++-+++++++++<<<<<<+>+-[<<>-]<[>>[<<->]<<[<]]>-[++>[<-]<[->>-<<<]>>->>+>>+>-[<-]<[<<[->>>+<<><<]+->>>>>+>+[<><-]<><[->>+<<<]<<-<]<<<<+>[<-]<[>>[<<->]<<[<]]>-]>>++++++++[->++++++<]>[-<<<<+>>>>]>>>>>+><>-+[<-]<[>>[<<->]<<[<]]>-[++>[<-]<[->>-<<<]>>-<<<<<<<<+>+[<-]<[->>+<<<]>>>>>>>>+>[<-]<[>>[<<->]<<[<]]>-]<<[-]<<<<<+>[<-]<[>>[<<->]<<[<]]>-]<<[.<]!";

	int open_brackets = from_stream(env, s);
	interpret(env);
	cout << '\n';
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		solve();
	}
	return 0;
}

void print_word(WORD word)
{
	if (isprint(word))
		std::cout << word;
	else
		std::cout << "0x" << std::hex << (int)word << std::dec;
}


int from_stream(environment& env, string& s, int open_brackets)
{
	if (open_brackets == 0)
		env.instructions.push_back('\0');
	WORD word;
	for (int i = 0; i < s.size(); i++) {
		word = s[i];
		switch (word)
		{
		case '<': case '>': case '+': case '-': case ',': case '.':
			env.instructions.push_back(word);
			break;
		case '[':
			open_brackets++;
			env.instructions.push_back(word);
			break;
		case ']':
			open_brackets--;
			env.instructions.push_back(word);
			break;
		default:
			break;
		}
	}
	if (open_brackets == 0)
		env.instructions.push_back('\0');
	return open_brackets;
}



void find_closing(environment& env)
{
	int balance = 1;
	do
	{
		env.ip++;
		if (*env.ip == '[')
			balance++;
		else if (*env.ip == ']')
			balance--;

	} while (balance != 0);
}

void find_opening(environment& env)
{
	int balance = 0;
	do
	{
		if (*env.ip == '[')
			balance++;
		else if (*env.ip == ']')
			balance--;
		env.ip--;
	} while (balance != 0);
}


void interpret(environment& env)
{
	env.ip = env.instructions.begin();
	while (env.ip != env.instructions.end())
	{
		switch (*env.ip)
		{
		case '+':
			(*env.mp)++;
			env.ip++;
			break;
		case '-':
			(*env.mp)--;
			env.ip++;
			break;
		case '>':
			if (env.mp != (env.memory.end()--))
				env.mp++;
			env.ip++;
			break;
		case '<':
			if (env.mp != env.memory.begin())
				env.mp--;
			env.ip++;
			break;
		case '.':
			print_word(*env.mp);
			env.ip++;
			break;
		case ',':
			WORD word;
			std::cin >> word;
			(*env.mp) = word;
			env.ip++;
			break;
		case '[':
			if (!(*env.mp))
				find_closing(env);
			env.ip++;
			break;
		case ']':
			find_opening(env);
			env.ip++;
			break;
		case '\0':
			env.ip++;
			break;
		}
	}
}
