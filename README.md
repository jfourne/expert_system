# expert_system

Implementation of a backward-chaining inference engigne.
The program takes one parameter which is the input file.
It will contain a list of rules, a list of initial facts then a list of queries.
By default all facts are false and can only be made true by the initial facts statement or 
by application of a rule.

Example :
B => A
D + E => B
G + H => F
I + J => G
G => H
L + M => K
O + P => L + N
N => M

=DEIJP

?AFKP

With =DEIJOP, AFKP is true
With =DEIKP, AFP is true, K is false

'+' is for AND
'|' is for OR
'^' is for XOR
