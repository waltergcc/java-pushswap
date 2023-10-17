import java.util.*;
import java.lang.*;
import java.io.*;

public class Main
{
	public static void main (String[] args) throws java.lang.Exception
	{
		try
		{
			PushSwap pushswap = new PushSwap(args);
		}
		catch (Exception e)
		{
			System.out.println(e);
			System.exit(1);
		}
	}
}