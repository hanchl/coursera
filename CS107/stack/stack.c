#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#include"stack.h"

void stacknew(stack *s, int elemSize, void (*freefn) (void *))
{
	s->logLength = 0;
	s->allocLength = 4;
	s->elemSize = elemSize;
	s->elems = malloc(4 * elemSize);

	s->freefn = freefn;
}

void stackDispose(stack *s)
{
	if (s->freefn != NULL)
	{
		for (int i = 0; i < s->logLength; ++i)
		{
			s->freefn((char *)s->elems + i * s->elemSize);
		}
	}

	s->logLength = 0;
	s->allocLength = 0;
	s->elemSize = 0;
	free(s->elems);
}
bool stackEmpty(const stack * s)
{
	return s->logLength == 0;
}
static void stackGrow(stack *s)
{
	s->allocLength *= 2;
	s->elems = realloc(s->elems, s->allocLength * s->elemSize);
	assert(s->elems != NULL);
}

void stackPush(stack *s, void *n)
{
	if (s->logLength == s->allocLength)
	{
		stackGrow(s);
	}

	memcpy((char *)s->elems + s->logLength * s->elemSize, n, s->elemSize);
	s->logLength++;
}

void stackPop(stack *s, void *elemAddr)
{
	assert(s->logLength > 0);
	s->logLength--;

	memcpy(elemAddr, (char *)s->elems + s->logLength * s->elemSize, s->elemSize);
} 
