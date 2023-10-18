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
}