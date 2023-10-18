import java.lang.Exception;

public class Main
{
	public static void main (String[] args) throws Exception
	{
		try
		{
			PushSwap pushswap = new PushSwap(args);
			pushswap.run();
			pushswap.printList(true);
		}
		catch (Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}