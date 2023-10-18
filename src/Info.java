public class Info
{
	public int number;
	public int index;
	public int pos;
	public int whereFit;
	public int movesInA;
	public int movesInB;

	public Info(int number)
	{
		this.number = number;
		this.index = 0;
		this.pos = -1;
		this.whereFit = -1;
		this.movesInA = -1;
		this.movesInB = -1;
	}

	public void setIndex(int index)
	{
		this.index = index;
	}

	public void setPos(int pos)
	{
		this.pos = pos;
	}

	public void setWhereFit(int whereFit)
	{
		this.whereFit = whereFit;
	}

	public void setMovesInA(int movesInA)
	{
		this.movesInA = movesInA;
	}

	public void setMovesInB(int movesInB)
	{
		this.movesInB = movesInB;
	}
}