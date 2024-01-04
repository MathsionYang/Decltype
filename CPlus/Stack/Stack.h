#pragma once
#include "CPlus/Global.h"
#include <iostream>
#define MAXSIZE 100
namespace CPlus
{
	namespace Stack
	{
		struct SeqStack
		{
			int data[MAXSIZE];
			int top;
		};
		class StackAlg
		{
			void InitStack(SeqStack* seq)
			{
				seq->top = -1;
			}
			bool StackEmpty(SeqStack* s) {
				return (s->top == -1);
			}
			bool StackFull(SeqStack* s)
			{
				return(s->top == MAXSIZE - 1);
			}
			int Push(SeqStack* s, int x)
			{
				if (StackFull(s))  //ÅÐ¶ÏÕ»ÊÇ·ñÂúÒç
					return 0;
				s->data[++s->top] = x;
				return 1;
			}
			int Pop(SeqStack* s)
			{
				if (StackEmpty(s)) //ÅÐ¶ÏÕ»ÊÇ·ñÎª¿Õ
					return 0;
				return(s->data[s->top--]);
			}
		};
	}
}