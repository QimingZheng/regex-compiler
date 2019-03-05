#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "src/UnitTest/UnitTest.h"
#include "src/Regex/RegexExpression.h"
#include "src/Regex/RegexWriter.h"
#include "src/Regex/RegexPure.h"
#include "src/Regex/RegexRich.h"
#include "src/Regex/Regex.h"
#include "src/Stream/FileStream.h"
#include "src/Stream/CharFormat.h"
#include "src/Stream/Accessor.h"
#include "src/Collections/OperationCopyFrom.h"

using namespace vl;
using namespace vl::collections;
using namespace vl::regex;
using namespace vl::regex_internal;
using namespace vl::stream;
using namespace std;


void NormalizedRegexAssert(const wchar_t* input, RegexNode node)
{
	CharRange::List subsets;
	Expression::Ref exp = ParseExpression(input);
	exp->NormalizeCharSet(subsets);
	TEST_ASSERT(exp->IsEqual(node.expression.Obj()));

	subsets.Clear();
	exp->CollectCharSet(subsets);
	exp->ApplyCharSet(subsets);
	TEST_ASSERT(exp->IsEqual(node.expression.Obj()));
}

void PrintAutomaton(string fileName, Automaton::Ref automaton)
{
	ofstream fout(fileName);

	wchar_t intbuf[100] = { 0 };
	for (vint i = 0; i < automaton->states.Count(); i++)
	{
		State* state = automaton->states[i].Obj();
		
		if (automaton->startState == state)
		{
			fout<<i<<" : initial\n";
		}
		if (state->finalState)
		{
			fout<<i<<" : accepting 1\n";
		}
		for (vint j = 0; j < state->transitions.Count(); j++)
		{
			Transition* transition = state->transitions[j];
			if (transition->type != Transition::Chars && transition->type!=Transition::Nop) 
				continue;
			fout<<i<<" -> "<<automaton->states.IndexOf(transition->target)<<" : ";
			switch (transition->type)
			{
			case Transition::Chars:
				fout<<transition->range.begin<<"|"<<transition->range.end<<"\n";
				break;
			case Transition::Epsilon:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::BeginString:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::EndString:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::Nop:
				fout<<"NOP\n";
				break;
			case Transition::Capture:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::Match:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::Positive:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::Negative:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::NegativeFail:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			case Transition::End:
				cout<<"error code = -1\n";
				exit(-1);
				break;
			}
		}
	}
}

void PrintRegex(string name, char *rule)
{
	size_t cSize = strlen(rule)+1;
    wchar_t code[cSize];
    mbstowcs (code, rule, cSize);
	//WString code = wc;
	RegexExpression::Ref regex = ParseRegexExpression(code);
	Expression::Ref expression = regex->Merge();
	CharRange::List subsets;
	expression->NormalizeCharSet(subsets);

	Dictionary<State*, State*> nfaStateMap;
	Group<State*, State*> dfaStateMap;
	Automaton::Ref eNfa = expression->GenerateEpsilonNfa();
	Automaton::Ref nfa = EpsilonNfaToNfa(eNfa, RichEpsilonChecker, nfaStateMap);

	PrintAutomaton(name, nfa);
}

int Hex2ascii(char *szHex)
{
	int re=0;
    int i;
    for(i=0; i<2; i++)
    {
        if(*(szHex + i) >='0' && *(szHex + i) <= '9')
            re = re*16 + (*(szHex + i) - '0');
        else if(*(szHex + i) >='a' && *(szHex + i) <= 'f')
            re = re*16 + (*(szHex + i) - 'a' + 10);
		else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
            re = re*16 + (*(szHex + i) - 'A' + 10);
        else{
			cout<<"error code = -2\n";
            exit(-2);
		}
    }
	return re;
}


char *preprocess_snort_rule(char *str){
	int len = strlen(str);
	int from = 1;
	int to = 0;
	for (int i=len-1;i>=0;i--){
		if (str[i]=='/'){
			to = i-1;
			break;
		}
	}
	if (to<from) to =len-1;
	string tmp = "";
	if (str[from] =='^') from+=1;
	for (int i=from; i <=to; i++){
		if (str[i]=='$') {tmp+="\n";continue;}
		if (str[i]=='\\' && str[i+1]=='x') {tmp=tmp+char(Hex2ascii(&str[i+2])); i+=3;continue;}
		tmp = tmp+str[i];
	}
	char *cstr = new char[tmp.length() + 1];
	strcpy(cstr, tmp.c_str());
	return cstr;
}

int main(int argc, char * argv[]){
	PrintRegex(argv[2], preprocess_snort_rule(argv[1]));
}