import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;
import java.util.ListIterator;
import java.lang.Exception;

public class PushSwap
{
	// ---> Attributes ---------------------------------------------------------

	private Deque<Info> stackA;
	private Deque<Info> stackB;
	private int			tmpMovesInA;
	private int			tmpMovesInB;

	// ---> Constructor --------------------------------------------------------

	public PushSwap(String[] args) throws Exception
	{
		stackA = new ArrayDeque<Info>();
		stackB = new ArrayDeque<Info>();

		checkInput(args);
		setStackAIndex();
	}

	// ---> Public methods -----------------------------------------------------

	public void run() throws Exception
	{
		if (isSorted())
			throw new Exception("List is already sorted");
		
		if (stackA.size() == 2)
			sa(true);
		else if (stackA.size() == 3)
			sortSmall();
		else
			sortBig();
	}

	public void print()
	{
		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			System.out.print(node.number + " ");
		}
		System.out.println();
		Iterator<Info> it2 = stackB.iterator();
		while (it2.hasNext())
		{
			Info node = it2.next();
			System.out.print(node.number + " ");
		}
		System.out.println();
	}

	// ---> Private Constructor Auxiliary methods ------------------------------

	private void checkInput(String[] args) throws Exception
	{
		double number;

		if (args.length == 0)
			throw new Exception("Error: no arguments");
		
		for (int i = 0; i < args.length; i++)
		{
			if (!isValidNumber(args[i]))
				throw new Exception("Error: invalid argument");

			number = Double.parseDouble(args[i]);
			if (number > Integer.MAX_VALUE || number < Integer.MIN_VALUE)
				throw new Exception("Error: argument out of range");
			
			if (hasDuplicates((int)number))
				throw new Exception("Error: duplicate argument");
			
			stackA.addLast(new Info((int)number));
		}
		if (stackA.size() == 1)
			throw new Exception("Error: Not enough arguments");
	}

	private boolean isValidNumber(String s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (i == 0 && (s.charAt(i) == '-' || s.charAt(i) == '+'))
				continue;
			if (!Character.isDigit(s.charAt(i)))
				return false;
		}
		return true;
	}

	private boolean hasDuplicates(int number)
	{
		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			if (it.next().number == number)
				return true;
		}
		return false;
	}

	private void setStackAIndex()
	{
		for (int i = stackA.size(); i > 0; i--)
		{
			Iterator<Info> it = stackA.iterator();
			int max = Integer.MIN_VALUE;
			Info tmp = null;
			while (it.hasNext())
			{
				Info node = it.next();
				if (node.index == 0 && node.number > max)
				{
					max = node.number;
					tmp = node;
				}
			}
			tmp.setIndex(i);
		}
	}

	// ---> Private Run Auxiliary methods --------------------------------------

	private boolean isSorted()
	{
		Iterator<Info> it = stackA.descendingIterator();
		int prev = Integer.MAX_VALUE;
		while (it.hasNext())
		{
			Info node = it.next();
			if (node.number > prev)
				return false;
			prev = node.number;
		}
		return true;
	}

	private int getMaxID()
	{
		int max = 0;
		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			if (node.index > max)
				max = node.index;
		}
		return max;
	}

	private int checkFrontValues()
	{
		int maxID = getMaxID();
		int selector = 0;

		Info first = stackA.pop();
		Info second = stackA.pop();

		if (first.index == maxID)
			selector = 1;
		else if (second.index == maxID)
			selector = 2;

		stackA.push(second);
		stackA.push(first);

		return selector;
	}

	private boolean firstIsGreater()
	{
		Info first = stackA.pop();
		Info second = stackA.pop();
		stackA.push(second);
		stackA.push(first);

		if (first.index > second.index)
			return true;
		return false;
	}

	private void getCurrentPositions(Deque<Info> s)
	{
		int pos = 0;
		Iterator<Info> it = s.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			node.setPos(pos);
			pos++;
		}
	}
	
	// ---> Private Sort Big methods -------------------------------------------

	private void sortBig()
	{
		pushAllSave3();

		while (!stackB.isEmpty())
		{
			whereItFitInA();
			calculateMoves();
			doMoves();
		}
	}

	private void pushAllSave3()
	{
		int size = stackA.size();
		int moves = 0;

		for (int i = 0; size > 6 && i < size && moves < size / 2; i++)
		{
			if (stackA.peek().index <= size / 2)
			{
				pb();
				moves++;
			}
			else
				ra(true);
		}

		for (; size - moves > 3; moves++)
			pb();
		
		sortSmall();
	}

	private void whereItFitInA()
	{
		getCurrentPositions(stackA);
		getCurrentPositions(stackB);

		Iterator<Info> it = stackB.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			node.setWhereFit(getTargetPosition(node.index));
		}
	}

	private int getTargetPosition(int index)
	{
		int max = Integer.MAX_VALUE;
		int target = -1;

		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			if (node.index > index && node.index < max)
			{
				max = node.index;
				target = node.pos;
			}
		}

		if (target != Integer.MAX_VALUE)
			return target;
		
		it = stackA.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			if (node.index < max)
			{
				max = node.index;
				target = node.pos;
			}
		}
		return target;
	}

	private void calculateMoves()
	{
		int sizeA = stackA.size();
		int sizeB = stackB.size();

		Iterator<Info> it = stackB.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			node.setMovesInB(node.pos);
			if (node.pos > sizeB / 2)
				node.setMovesInB((sizeB - node.pos) * -1);
			node.setMovesInA(node.whereFit);
			if (node.whereFit > sizeA / 2)
				node.setMovesInA((sizeA - node.whereFit) * -1);
		}
	}

	private void doMoves()
	{
		int less = Integer.MAX_VALUE;
		tmpMovesInA = 0;
		tmpMovesInB = 0;

		Iterator<Info> it = stackB.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			if (Math.abs(node.movesInA) + Math.abs(node.movesInB) < Math.abs(less))
			{
				less = Math.abs(node.movesInA) + Math.abs(node.movesInB);
				tmpMovesInA = node.movesInA;
				tmpMovesInB = node.movesInB;
			}

			if (tmpMovesInA < 0 && tmpMovesInB < 0)
				reverseBoth();
			else if (tmpMovesInA > 0 && tmpMovesInB > 0)
				rotateBoth();
			rotateA();
			rotateB();

			pa();
		}
	}

	private void reverseBoth()
	{
		while (tmpMovesInA < 0 && tmpMovesInB < 0)
		{
			tmpMovesInA++;
			tmpMovesInB++;
			rrr();
		}
	}

	private void rotateBoth()
	{
		while (tmpMovesInA > 0 && tmpMovesInB > 0)
		{
			tmpMovesInA--;
			tmpMovesInB--;
			rr();
		}
	}

	private void rotateA()
	{
		while (tmpMovesInA != 0)
		{
			if (tmpMovesInA > 0)
			{
				tmpMovesInA--;
				ra(true);
			}
			else if (tmpMovesInA < 0)
			{
				tmpMovesInA++;
				rra(true);
			}
		}
	}

	private void rotateB()
	{
		while (tmpMovesInB != 0)
		{
			if (tmpMovesInB > 0)
			{
				tmpMovesInB--;
				rb(true);
			}
			else if (tmpMovesInB < 0)
			{
				tmpMovesInB++;
				rrb(true);
			}
		}
	}

	// ---> Private Moves methods ----------------------------------------------

	private void sortSmall()
	{
		if (isSorted())
			return;
		
		int selector = checkFrontValues();

		if (selector == 1)
			ra(true);
		else if (selector == 2)
			rra(true);
		
		if (firstIsGreater())
			sa(true);
	}

	private void sa(boolean print)
	{
		Info first = stackA.pop();
		Info second = stackA.pop();
		stackA.push(first);
		stackA.push(second);

		if (print)
			System.out.println("sa");
	}

	private void sb(boolean print)
	{
		Info first = stackB.pop();
		Info second = stackB.pop();
		stackB.push(first);
		stackB.push(second);

		if (print)
			System.out.println("sb");
	}

	private void ss()
	{
		sa(false);
		sb(false);
		System.out.println("ss");
	}

	private void ra(boolean print)
	{
		Info first = stackA.pop();
		stackA.addLast(first);

		if (print)
			System.out.println("ra");
	}

	private void rb(boolean print)
	{
		Info first = stackB.pop();
		stackB.addLast(first);

		if (print)
			System.out.println("rb");
	}

	private void rr()
	{
		ra(false);
		rb(false);
		System.out.println("rr");
	}

	private void rra(boolean print)
	{
		Info last = stackA.removeLast();
		stackA.push(last);

		if (print)
			System.out.println("rra");
	}

	private void rrb(boolean print)
	{
		Info last = stackB.removeLast();
		stackB.push(last);

		if (print)
			System.out.println("rrb");
	}

	private void rrr()
	{
		rra(false);
		rrb(false);
		System.out.println("rrr");
	}

	private void pa()
	{
		Info first = stackB.pop();
		stackA.push(first);
		System.out.println("pa");
	}

	private void pb()
	{
		Info first = stackA.pop();
		stackB.push(first);
		System.out.println("pb");
	}
}