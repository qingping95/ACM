// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
Some positive integers, not necessarily distinct, are written on a blackboard.
You are given these integers in a format that is specified at the end of this statement.


You are allowed to change the numbers on the blackboard in a sequence of steps.
In each step, you have to execute the following actions, in order:

Erase x and y. (Erase exactly two numbers. If there are other copies of these numbers on the blackboard, leave them untouched.)
Write two new integers onto the blackboard: gcd(x,y) and lcm(x,y).

(Above, gcd(x,y) denotes the greatest common divisor and lcm(x,y) the least common multiple of x and y.)



You may perform arbitrarily many steps (possibly even zero).
Your goal is to maximize the sum of numbers written on the blackboard.
Let S be the largest possible sum.
Compute and return the value (S modulo 1,000,000,007).



You are given the int[]s start, d, and cnt, each with the same number of elements.
Use the following pseudocode to generate the numbers on the blackboard:



L = length(start)
for i = 0 .. L-1:
    for j = 0 .. cnt[i]-1:
        write the number (start[i] + j * d[i]) onto the blackboard


DEFINITION
Class:GCDLCM2
Method:getMaximalSum
Parameters:int[], int[], int[]
Returns:int
Method signature:int getMaximalSum(int[] start, int[] d, int[] cnt)


NOTES
-Note that you are maximizing the sum S. You are not maximizing the return value.


CONSTRAINTS
-start, d and cnt will have the same number of elements.
-start will contain between 1 and 500 elements, inclusive.
-Each element of start and cnt will be between 1 and 10,000,000, inclusive.
-Each element of d will be between 0 and 10,000,000, inclusive.
-For each valid i, start[i] + d[i] * (cnt[i] - 1) will be at most 10,000,000.
-The sum of all cnt[i] will be between 1 and 100,000, inclusive.


EXAMPLES

0)
{1}
{1}
{3}

Returns: 8

 


There are three numbers on the blackboard: 1, 2 and 3. You can replace numbers 2 and 3 with numbers 1 and 6.


Then sum is 1 + 1 + 6 = 8 (which can be proved to be maximal). The answer is (8 modulo 1,000,000,007) = 8.


1)
{3}
{0}
{5}

Returns: 15

There are five numbers 3 on the blackboard. It's impossible to perform even a single operation so the maximal sum is 15. 

2)
{2}
{2}
{4}

Returns: 32

Numbers on the blackboard are 2, 4, 6, 8.

3)
{1, 2}
{2, 3}
{2, 2}

Returns: 33

Numbers on the blackboard are 1, 3, 2, 5.

4)
{5 ,6}
{23, 45}
{50000, 50000}

Returns: 804225394



// END CUT HERE
import java.util.*;
public class GCDLCM2 {
	public int getMaximalSum(int[] start, int[] d, int[] cnt) {
		
	}
	public static void main(String[] args) {
		GCDLCM2 temp = new GCDLCM2();
		System.out.println(temp.getMaximalSum(int[] start, int[] d, int[] cnt));
	}
}
