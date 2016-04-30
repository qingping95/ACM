// BEGIN CUT HERE
// PROBLEM STATEMENT
// A set of positive integers is called k-smooth if each pair (A,B) of elements of the set satisfies A <= k * B.
For example, the set {3,4,7,9} is 3-smooth but the set {30,60,100} is not: 100 is strictly more than 3 * 30.

Hero likes some sets of integers.
In order to determine whether he likes a set S, Hero uses the following procedure:

Form a new set D of pairwise differences of elements in S. In other words: for each pair of elements A, B in S, put the number |A-B| into D.
Hero likes the original set S if and only if the new set D is k-smooth.


You are given a int[] a containing a set of distinct integers.
You are also given the int k Hero uses while determining whether he likes a set of integers.

Select the largest subset of a Hero likes.
Return the number of elements in that subset.

DEFINITION
Class:CliqueParty
Method:maxsize
Parameters:int[], int
Returns:int
Method signature:int maxsize(int[] a, int k)


CONSTRAINTS
-Number of elements in a will be between 2 and 50, inclusive.
-Each elements in a will be between 1 and 1,000,000,000, inclusive.
-All elements in a will be distinct.
-k will be between 1 and 1,000,000,000, inclusive.


EXAMPLES

0)
{1,2,3}
2

Returns: 3

Hero likes the entire set a.

1)
{1,2,3}
1

Returns: 2

Here, Hero does not like the entire set a, but he does like, for example, the subset {1,3}.

2)
{4,10,5,6}
2

Returns: 3



3)
{1,2,3,4,5,6}
3

Returns: 4



4)
{10,9,25,24,23,30}
7

Returns: 4



// END CUT HERE
import java.util.*;
public class CliqueParty {
	public int maxsize(int[] a, int k) {
		
	}
	public static void main(String[] args) {
		CliqueParty temp = new CliqueParty();
		System.out.println(temp.maxsize(int[] a, int k));
	}
}
