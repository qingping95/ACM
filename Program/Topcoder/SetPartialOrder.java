// BEGIN CUT HERE
// PROBLEM STATEMENT
// In math, we sometimes define a partial order on some objects.
In this problem we will take a look at one possible way how to define a partial order on sets of integers.

Consider two sets of integers: X and Y.
These two sets can be related to each other in four possible ways:


X is equal to Y if each element of X is also an element of Y and vice versa.
X is less than Y if X is not equal to Y (see previous item) and each element of X is also an element of Y.
X is greater than Y if Y is less than X.
In all other cases X and Y are incomparable.


In other words:
X is less than Y if and only if X is a proper subset of Y.
Two sets are incomparable if neither is a subset of the other.

You are given two int[]s a and b.
The elements of a form the set X.
The elements of b form the set Y.
Compare X to Y and return the correct one of the following four strings: "EQUAL", "LESS", "GREATER", or "INCOMPARABLE".

(The string "LESS" means that X is less than Y, the string "GREATER" means that X is greater than Y.
Quotes are for clarity only.
Note that the return value is case-sensitive.)

DEFINITION
Class:SetPartialOrder
Method:compareSets
Parameters:int[], int[]
Returns:String
Method signature:String compareSets(int[] a, int[] b)


CONSTRAINTS
-Each of arrays a and b will have length between 1 and 50, inclusive.
-Each element of arrays a and b will be between 1 and 100, inclusive.
-In each of arrays a and b all elements are distinct.


EXAMPLES

0)
{1, 2, 3, 5, 8}
{8, 5, 1, 3, 2}

Returns: "EQUAL"

The order of elements in a and b does not matter. The two sets X and Y are equal.

1)
{2, 3, 5, 7}
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

Returns: "LESS"

Each number that occurs in a does also occur in b.

2)
{2, 4, 6, 8, 10, 12, 14, 16}
{2, 4, 8, 16}

Returns: "GREATER"



3)
{42, 23, 17}
{15, 23, 31}

Returns: "INCOMPARABLE"



// END CUT HERE
import java.util.*;
public class SetPartialOrder {
	public String compareSets(int[] a, int[] b) {
		
	}
	public static void main(String[] args) {
		SetPartialOrder temp = new SetPartialOrder();
		System.out.println(temp.compareSets(int[] a, int[] b));
	}
}
