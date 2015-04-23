/********************************************
*
*http://web.archive.org/web/20071214140839/http://www.seanet.com/~brucemo/topics/0x88.htm
*/

#include "ChessGame.h"


/*********************************************
* Did last move left me in check?
ctm is still in check?
*/

bool ChessGame::isPositionValid(ChessMove cm)
{
	// was this move (to OR from) on the same line, rank or diagonal as the king?
	//if (getToSquare(state[ply].m_LastMove) == KingPos(opp))
	//did the opponent just left his king in check?
	//if (ply != 0 && isEnPassant(state[ply - 1].m_LastMove))
	//return !isAttacked(KingPos(opp), ctm);
	if (PiecesThatCanAttack(getFromSquare(state[ply - 1].m_LastMove), KingPos(opp)))
		return !isAttacked(KingPos(opp), ctm);
	if (PiecesThatCanAttack(getToSquare(state[ply - 1].m_LastMove), KingPos(opp)))
		return !isAttacked(KingPos(opp), ctm);	
	if (PiecesThatCanAttack(getFromSquare(state[ply ].m_LastMove), KingPos(opp)))
		return !isAttacked(KingPos(opp), ctm);
	if (PiecesThatCanAttack(getToSquare(state[ply ].m_LastMove), KingPos(opp)))
		return !isAttacked(KingPos(opp), ctm);
	return true;
}

/***********************************************************
* Does not check for interposing pieces
*/
Piece ChessGame::PiecesThatCanAttack(Square s1, Square s2)
{

	//ASSERT ( isSquare(s1) && "PiecesThatCanAttack: s1 not a Square" );
	//ASSERT ( isSquare(s2) && "PiecesThatCanAttack: s2 not a Square");
	int diff = s2 - s1;
	return Attacks0x88[diff + ATTACKTABLEINDEXOFFSET];
}
/***********************************************************
*
*/
bool ChessGame::isAttackedbyPiece ( Square from, Square to, Color side, Piece p )
{

	//ASSERT( isSquare(from) && "isAttackedbyPiece: " );
	//ASSERT( isSquare(to)  && "isAttackedbyPiece: ");
	//ASSERT ( !isEmpty( from )  && "isAttackedbyPiece: ");
	//ASSERT( p  && "isAttackedbyPiece: ");

	Piece PiecesAbleToAttack = PiecesThatCanAttack(from, to);
	if ( ! PiecesAbleToAttack )
		return false;
	int c;
	Square sq;

	if ( !(p & PiecesAbleToAttack))
		return false;

	if ( p & ( KING | KNIGHT ))
		return true;
	if ( p & PAWN)
	{
		if ( side == WHITE )
		{
			if ((to - from == NORTHWEST) | (to - from == NORTHEAST))
				return true;
		}
		else
		{
			if ((to - from == SOUTHWEST) | (to - from == SOUTHEAST))
				return true;
		}
	}

	//if there is an interposing piece (of any color), then return false
	for ( c = 0; c < 8; c++){
		//PrintBoard();
		for ( sq = from + queenvectors[c]; isSquare(sq) && isEmpty(sq) && !(sq == to) ; sq += queenvectors[c]);
		{
			if ( sq == to) // we have a hit!
			{
				if ( p == QUEEN)
					return true;
				if ( c % 2 == 0)
					return p == ROOK;
				return p == BISHOP;
			}
		}
	}
	return false;
} 
/**************************************************************
*Prints attack map 
*/
void ChessGame::PrintAttackMap(Color co)
{
	int c, i= 63;
	cout << "Attack map for " << (co == BLACK? "BLACK" : "WHITE" )<< endl;
	/*for (c = 0; c < 8; c++)
	{
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0");
		cout << (AttackMap[co][i--] ? "1" : "0") << endl;

	}*/
	for (c = 0; c < 128; c++)
		if (isSquare(c)){
			if (AttackMap[co][c])
				cout << "Attacked " << not(c) << endl;
		}


}
/**************************************************************
*Builds attack map for side to move (ctm)
*/
void ChessGame::BuildAttackMap(void)
{
	int i, c;
	Square curr, sq;
	Color AMfor = opp;
	//ClearAttackMap()
	for (i = 0; i < MAXBOARDARRAY; i++){
		AttackMap[AMfor][i] = false;
		AttackMap[ctm][i] = false;
	}
	//PrintAttackMap(opp);	
	//PrintAttackMap(ctm);
	for (i = 0; i < maxpieces[AMfor]; i++)
	{
		if (!pieces[i][AMfor].piece)
			continue;
		curr = pieces[i][AMfor].square;
		switch (pieces[i][AMfor].piece)
		{
		case PAWN:
			sq = curr + pawndirection[AMfor];
			//cout << "Pawn on " << not(curr) << endl;
			if (isSquare(sq + EAST))
				AttackMap[AMfor][sq + EAST] = true;
			if (isSquare(sq + WEST))
				AttackMap[AMfor][sq + WEST] = true;
			//PrintAttackMap(ctm);
			//PrintAttackMap(opp);
			//cout << "Pause" << endl;
			break;
		case KNIGHT:
			for (c = 0; c < 8; c++)
			{
				//cout << "curent square " << not(curr) << endl;
				sq = curr + knightvectors[c];
				
				if (isSquare(sq))
				{
					//cout << "checking square " << not(sq) << endl;
					//if (isEmpty(sq) || isOpponent(sq))
					{
						//cout << "Flagging " << not(sq) << endl;
						AttackMap[AMfor][sq] = true;
					}
				}
			}
			//PrintAttackMap(AMfor);
			//PrintAttackMap(opp);
			break;
		case BISHOP:
			for (c = 0; c < 4; c++)
			{
				for (sq = curr + bishopvectors[c]; isSquare(sq) && isEmpty(sq); sq += bishopvectors[c])
					AttackMap[AMfor][sq] = true;
				if (isSquare(sq) )
					AttackMap[AMfor][sq] = true;
			}
			//PrintAttackMap(AMfor);
			break;
		case ROOK:
			for (c = 0; c < 4; c++)
			{
				for (sq = curr + rookvectors[c]; isSquare(sq) && isEmpty(sq); sq += rookvectors[c])
					AttackMap[AMfor][sq] = true;
				if (isSquare(sq) )
					AttackMap[AMfor][sq] = true;
			}
			//PrintAttackMap(AMfor);
			break;
		case QUEEN:
			for (c = 0; c < 8; c++)
			{
				for (sq = curr + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c])
					AttackMap[AMfor][sq] = true;
				if (isSquare(sq) )
					AttackMap[AMfor][sq] = true;
			}
			//PrintAttackMap(AMfor);
			break;
		case KING:
			for (c = 0; c < 8; c++)
			{
				sq = curr + kingvectors[c];
				if (isSquare(sq))
				{
					
						AttackMap[AMfor][sq] = true;
				}
			}
			//PrintAttackMap(AMfor);
			break;
		default:
			cout << "Should never get here!" << endl;
			break;

		}
	}
	//PrintAttackMap(AMfor);
	//PrintAttackMap(opp);
	//PrintBoard();
	//cout << "Pause" << endl;
	return;
}

bool ChessGame::NeedToRunIsAttacked(Square target, Color co)
{
	int c;
	Piece p;
	Square sq;
	for (c = 0; c < maxpieces[co]; c++)
	{
		p = pieces[c][co].piece;
		sq = pieces[c][co].square;
		if (p & PiecesThatCanAttack(target, sq))
			return true;
	}
	return false;
}



/**************************************************************
* square "target" is attacked by "co"
*/
bool ChessGame::isAttacked(Square target, Color co)
{

	if (! NeedToRunIsAttacked(target, co))
		return false;

	//PrintBoard();
	static Square sq;
	static int c, i;
	bool found = false;
	//Piece PiecesAbleToAttack;

	//check for pawns, kings and knights
	//Pawns
	if (co == WHITE)
	{
		if (isPieceColor(target + SOUTHWEST, PAWN, co))
			return true;
		if (isPieceColor(target + SOUTHEAST, PAWN, co))
			return true;
	}
	else
	{
		if (isPieceColor(target + NORTHWEST, PAWN, co))
			return true;
		if (isPieceColor(target + NORTHEAST, PAWN, co))
			return true;
	}

	//King
	for (c = 0; c < 8; c++)
	{
		if (isPieceColor(target + kingvectors[c], KING, co))
			return true;
	}
	//Knight
	for (c = 0; c < 8; c++)
	{
		if (isPieceColor(target + knightvectors[c], KNIGHT, co))
			return true;
	}


	// check for sliding pieces.
	for ( c = 0; c < 8; c++){

		for ( sq = target + queenvectors[c]; isSquare(sq) && isEmpty(sq) ; sq += queenvectors[c]);
		{
			if ( isSquare(sq) && isColor(sq, co) ) // we have a hit!
			{
				if ( getPiece(sq) == QUEEN)
					return true;
				if ( c % 2 == 0 && getPiece(sq) == ROOK)
					return  true;
				if ( c % 2 == 1 && getPiece(sq) == BISHOP)
					return true ;
			}
		}
	}



	return false;
}

bool ChessGame::PawnsAttackingLargePieces(ChessMove cm)
{
	Square pawnsq = getToSquare(cm);
	Square sq;
	Piece p = getPiece(pawnsq);
	if ( p != PAWN)
		return false;
	Rank r = getRank(pawnsq);
	if ( r != pawnsecondrank[ctm] && r !=  pawnthirdrank[ctm] )
		return false;

	sq = pawnsq + pawndirection[opp] + EAST ;
	if ( isSquare(sq) && !isEmpty(sq) && isOurs(sq))
	{
		if (  getPiece(sq) & ( ROOK | QUEEN | BISHOP | KNIGHT ) )
			return true;
	}
	sq = pawnsq + pawndirection[opp] + WEST ;
	if ( isSquare(sq) && !isEmpty(sq) && isOurs(sq))
	{
		if ( getPiece(sq) & ( ROOK | QUEEN | BISHOP | KNIGHT ) )
			return true;
	}
	return false;
}