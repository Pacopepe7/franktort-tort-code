#pragma once
class BSPNode
{
	int data;
	class BSPNode * left;
	class BSPNode * right;
	class BSPNode * parent;
	bool iTerminal;
public:
	BSPNode * Left () 
	{
		return left;	
	};
	BSPNode * Right () 
	{
		return right;	
	};

	BSPNode(void) {
		left = 0;
		right = 0;
		parent = 0;
		iTerminal = true;
	};
	~BSPNode(void){};
};

