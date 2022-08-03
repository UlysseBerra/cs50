#include "test.h"

import <cs50.h>
import <stdio.h>

int main(void)
{
    string name = get_string("What's your name?  ");

    print("Hello, %s", name);
}