// BEGIN CUT HERE
// PROBLEM STATEMENT
// Your university is holding a programming competition and your team is going to compete.

There are 3*N students in the university. They are numbered from 0 to 3*N-1. Each student has a certain strength which is a positive integer that characterizes his/her programming skills. You are given a int[] strength. The strength of student i is equal to strength[i].

Your team will consist of students 0, 1 and 2. Other 3*N-3 students will form N-1 more teams so that each team has exactly 3 members. The exact composition of other teams is not known yet. Each team has a strength that is calculated as follows: if it consists of members with strengths X, Y and Z, then the team's strength is equal to max{X, Y, Z} + min{X, Y, Z}.

You are interested how your team will rank by strength among the other teams. Formally, the rank of your team is defined as 1 + (the number of other teams that have a strictly greater strength than the strength of your team).

Return the maximum possible rank that your team may have after all students split into teams.

DEFINITION
Class:TeamContest
Method:worstRank
Parameters:int[]
Returns:int
Method signature:int worstRank(int[] strength)


CONSTRAINTS
-strength will contain between 3 and 48 elements, inclusive.
-The number of elements in strength will be divisible by 3.
-Each element of strength will be between 1 and 1,000,000, inclusive.


EXAMPLES

0)
{5, 7, 3, 5, 7, 3, 5, 7, 3}

Returns: 2

The strength of your team is max{5, 7, 3} + min{5, 7, 3} = 10. It is possible that one of the other teams will be stronger than your team. For example, if it consists of students with strengths 5, 7 and 7, then its strength will be 12. However, it is not possible that both other teams will be stronger than your team.


1)
{5, 7, 3}


Returns: 1

Just your team. No rivals.

2)
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

Returns: 1

All teams (including yours) will have the same strength: 2.

3)
{3,9,4,6,2,6,1,6,9,1,4,1,3,8,5}


Returns: 3



4)
{53,47,88,79,99,75,28,54,65,14,22,13,11,31,43}


Returns: 3



// END CUT HERE
import java.util.*;
public class TeamContest {
	public int worstRank(int[] strength) {
		
	}
	public static void main(String[] args) {
		TeamContest temp = new TeamContest();
		System.out.println(temp.worstRank(int[] strength));
	}
}
