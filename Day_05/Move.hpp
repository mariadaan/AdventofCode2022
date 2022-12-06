class Move
{
public:
	Move(int amountInput, int fromPosInput, int toPosInput) : amount(amountInput), fromPos(fromPosInput), toPos(toPosInput){}
	int amount;
	int fromPos;
	int toPos;
};