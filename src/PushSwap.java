import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;
import java.util.ListIterator;
import java.lang.Exception;

public class PushSwap
{
	public PushSwap(String[] args) throws Exception
	{
		this.checkInput(args);
	}

	private void checkInput(String[] args) throws Exception
	{
		double number;

		if (args.length == 0)
			throw new Exception("Error: no arguments");
		
		for (int i = 0; i < args.length; i++)
		{
			System.out.println("args[" + i + "]: " + args[i]);
			if (!isValidNumber(args[i]))
				throw new Exception("Error: invalid argument");

			number = Double.parseDouble(args[i]);
			if (number > Integer.MAX_VALUE || number < Integer.MIN_VALUE)
				throw new Exception("Error: argument out of range");
		}
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
}