import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;
import java.lang.Exception;
import java.util.Scanner;

public class PushSwap
{
	// ---> Attributes ---------------------------------------------------------

	private Deque<Info> stackA;
	private Deque<Info> stackB;
	private int			tmpMovesInA;
	private int			tmpMovesInB;
	private int			countMoves;

	private static Scanner scanner = new Scanner(System.in);

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
		
		printList(false);

		printTitle();
		System.out.println("Moves:\n");

		countMoves = 0;

		if (stackA.size() == 2)
			sa(true);
		else if (stackA.size() == 3)
			sortSmall();
		else
			sortBig();
		
		System.out.println("\nTotal moves: " + countMoves);
		pressEnter();
		scanner.close();
	}

	public void printList(boolean sorted)
	{
		printTitle();

		if (sorted == true)
			System.out.println("Sorted list:\n");
		else
			System.out.println("Input list:\n");
		
		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			System.out.print(node.number + " ");
		}
		System.out.println();
		pressEnter();
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

	// ---> Private print Auxiliary methods -------------------------------

	private void printTitle()
	{
		System.out.print("\033c");
		System.out.println("*********************************");
		System.out.println("*        JAVA PUSH SWAP         *");
		System.out.println("*********************************");
		System.out.println();
	}

	private void pressEnter()
	{
		System.out.println("\nPress ENTER to continue");
		scanner.nextLine();
		System.out.println("\033c");
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
		if (!isSorted())
			lastSort();
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

		if (max != Integer.MAX_VALUE)
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
		}

		if (tmpMovesInA < 0 && tmpMovesInB < 0)
			reverseBoth();
		else if (tmpMovesInA > 0 && tmpMovesInB > 0)
			rotateBoth();
		rotateA();
		rotateB();

		pa();
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
		if (tmpMovesInA == 0)
			return;

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
		if (tmpMovesInB == 0)
			return;
		
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

	private void lastSort()
	{
		int size = stackA.size();
		int position = getLowerPosition();

		if (position > size / 2)
		{
			while (position++ < size)
				rra(true);
		}
		else
		{
			while (position-- > 0)
				ra(true);
		}
	}

	private int getLowerPosition()
	{
		int minIndex = Integer.MAX_VALUE;
		getCurrentPositions(stackA);

		int lowPosition = stackA.peek().pos;
		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			Info node = it.next();
			if (node.index < minIndex)
			{
				minIndex = node.index;
				lowPosition = node.pos;
			}
		}
		return lowPosition;
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
		{
			System.out.println("sa");
			countMoves++;
		}
	}

	private void ra(boolean print)
	{
		Info first = stackA.pop();
		stackA.addLast(first);

		if (print)
		{
			System.out.println("ra");
			countMoves++;
		}
	}

	private void rb(boolean print)
	{
		Info first = stackB.pop();
		stackB.addLast(first);

		if (print)
		{
			System.out.println("rb");
			countMoves++;
		}
	}

	private void rr()
	{
		ra(false);
		rb(false);
		System.out.println("rr");
		countMoves++;
	}

	private void rra(boolean print)
	{
		Info last = stackA.removeLast();
		stackA.push(last);

		if (print)
		{
			System.out.println("rra");
			countMoves++;
		}
	}

	private void rrb(boolean print)
	{
		Info last = stackB.removeLast();
		stackB.push(last);

		if (print)
		{
			System.out.println("rrb");
			countMoves++;
		}
	}

	private void rrr()
	{
		rra(false);
		rrb(false);
		System.out.println("rrr");
		countMoves++;
	}

	private void pa()
	{
		Info first = stackB.pop();
		stackA.push(first);
		System.out.println("pa");
		countMoves++;
	}

	private void pb()
	{
		Info first = stackA.pop();
		stackB.push(first);
		System.out.println("pb");
		countMoves++;
	}
}