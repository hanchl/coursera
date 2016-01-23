#pragma once
/// stack.h define C style stack
///author chan 2016-01-07 12:32:54
typedef int bool;

typedef struct
{
	int logLength;
	int allocLength;
	int elemSize;
	void *elems;
	void (*freefn)(void *);
} stack;

void stacknew(stack *s, int elemSize, void (*freefn) (void *));	/// constructor
void stackDispose(stack *s);	///destructor
bool stackEmpty(const stack *s);	/// is this stack empty
void stackPush(stack *s, void *n);///push
void stackPop(stack *s, void *n);	///pop