#!/bin/bash
#
# Experiment with shell test command

# The test command is used most often with the if command to perform true/false
# decision. The command is unusual in that it has two different syntactic forms:
# First form:
#  test expression
# Second form:
#  [ expression ]
# The test command works simply. If the given expression is true, test exits
# with a status of zero; otherwise it exits with a status of 1. Note the spaces
# before and after expression are required. For a complete list of expression,
# see "man test".

# For example
test 3 -gt 4 && echo True || echo false # false
[ "abc" != "def" ]; echo $?             # 0

# Use with if statement
if [ -f ~/.bash_profile ]; then
  echo "You have a .bash_profile. Things are fine."
else
  echo "Yikes! You have no .bash_profile!"
fi


number=1

# String comparison. Spaces around '=' are required.
if [ "$number" = "1" ]; then
  echo "Number is 1"
fi

# Another string comparison, but this is discouraged.
if [ $number = "1" ]; then
  echo "Number is 1"
fi

# Integer comparison. Spaces around '-eq' are required.
if [ $number -eq 1 ]; then
  echo "Number is 1"
fi


# The test command is very powerful, but somewhat unwieldy given its
# requirement for escaping and given the difference between string and
# arithmetic comparisons. Bash provides two compound command "(( ))"
# and "[[ ]]", which allows more natural syntax.
[[ "abc def d,x" == a[abc]*\ ?d* || 3 -gt 2 ]]; echo $? # 0

if [[ -d "$HOME" ]]; then
  echo "Home is set"
fi
