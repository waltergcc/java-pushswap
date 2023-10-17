import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;
import java.util.ListIterator;
import java.lang.Exception;

public class PushSwap
{
	private Deque<Info> stackA;
	private Deque<Info> stackB;

	public PushSwap(String[] args) throws Exception
	{
		stackA = new ArrayDeque<Info>();
		stackB = new ArrayDeque<Info>();

		checkInput(args);
	}

	public void print()
	{
		Iterator<Info> it = stackA.iterator();
		while (it.hasNext())
		{
			System.out.print(it.next().number + " ");
		}
		System.out.println();
		Iterator<Info> it2 = stackB.iterator();
		while (it2.hasNext())
		{
			System.out.print(it2.next().number + " ");
		}
	}

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


}