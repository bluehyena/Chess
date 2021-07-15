#include <fstream>
#include <string>
#include "Game.h"

#define MAX_NUM_OF_HORSE 32
#define KIND_OF_HORSE 12
#define MAX_BOUNDARY_OF_TILE 8

void chess::MainMenu(std::istream& is, std::ostream& os) {
	os << "***************************\n";
	os << "* *************************\n";
	os << "*   ***********************\n";
	os << "*     *********************\n";
	os << "*       *******************\n";
	os << "*         *****************\n";
	os << "*           ***************\n";
	os << "*             *************\n";
	os << "*               ***********\n";
	os << "*                 *********\n";
	os << "*                   *******\n";
	os << "*                     *****\n";
	os << "*                       ***\n";
	os << "*                         *\n";
	os << "***************************\n";
	os << "* SWTube CHESS ENGINE     *\n";
	os << "* Minha Ju                *\n";
	os << "* 2021 / 07 / 05          *\n";
	os << "***************************\n\n";
	os << "***************************\n";

	int menuNum = 0;
	bool wantToContinue = true;

	while (wantToContinue)
	{
		os << "* 1. PrintBoard           *\n";
		os << "* 2. LoadBoard            *\n";
		os << "* 3. PrintGameInformation *\n";
		os << "* 4. Exit                 *\n";
		os << "*-------------------------*\n";
		os << "  Command:  ";
		is >> menuNum;
		switch (menuNum)
		{
		case 1: { // PrintInitialBoard
			PrintInitialBoard(std::cout);
			break;
		}
		case 2: { // Load Board
			std::string fileName;
			is >> fileName;
			std::ifstream readFile(fileName);
			if (readFile.fail()) {
				os << "\n*-------------------------*\n";
				os << "* INVALID INPUT!          *\n";
				os << "* PLEASE TRY AGAIN!       *\n";
				os << "*-------------------------*\n";
			}
			else {
				LoadBoard(readFile, std::cout);
			}
			break;
		}
		case 3: { // PrintGameInformation
			std::string fileName;
			is >> fileName;
			std::ifstream readFile(fileName);
			if (readFile.fail()) {
				os << "\n*-------------------------*\n";
				os << "* INVALID INPUT!          *\n";
				os << "* PLEASE TRY AGAIN!       *\n";
				os << "*-------------------------*\n";
			}
			else {
				PrintGameInformation(readFile, std::cout);
			}
			break;
		}
		case 4: { // Exit
			os << "\n*-------------------------*\n";
			os << "* THANK YOU FOR PLAYING!  *\n";
			os << "***************************\n";
			wantToContinue = false;
			break;
		}
		default: // Invalid input
			while (getchar() != '\n');
			os << "\n*-------------------------*\n";
			os << "* INVALID INPUT!          *\n";
			os << "* PLEASE TRY AGAIN!       *\n";
			os << "*-------------------------*\n";
			break;
		}
	}
}

void chess::PrintInitialBoard(std::ostream& os) { // 1. PrintBoard
	os << "\n*-------------------------*\n";
	os << "*   abcdefgh              *\n";
	os << "*  +--------+             *\n";
	os << "* 0|RNBKQBNR|             *\n";
	os << "* 1|PPPPPPPP|             *\n";
	os << "* 2|        |             *\n";
	os << "* 3|        |             *\n";
	os << "* 4|        |             *\n";
	os << "* 5|        |             *\n";
	os << "* 6|pppppppp|             *\n";
	os << "* 7|rnbkqbnr|             *\n";
	os << "*  +--------+             *\n";
}

void chess::LoadBoard(std::istream& is, std::ostream& os) {
	// 말 :r n b k q p R N B K Q P
	// 가로좌표 : a b c d e f g h
	// 세로좌표 : 0 1 2 3 4 5 6 7
	char chessTable[MAX_BOUNDARY_OF_TILE][MAX_BOUNDARY_OF_TILE];

	for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
		for (int j = 0; j < MAX_BOUNDARY_OF_TILE; ++j) {
			chessTable[i][j] = ' ';
		}
	}

	int numOfAvailableBlackPawns = 8;
	int numOfAvailableBlackRocks = 2;
	int numOfAvailableBlackKnights = 2;
	int numOfAvailableBlackBishops = 2;
	int numOfAvailableBlackQueen = 1;
	int numOfAvailableBlackKing = 1;

	int numOfAvailableWhitePawns = 8;
	int numOfAvailableWhiteRocks = 2;
	int numOfAvailableWhiteKnights = 2;
	int numOfAvailableWhiteBishops = 2;
	int numOfAvailableWhiteQueen = 1;
	int numOfAvailableWhiteKing = 1;

	const char possibleHorse[KIND_OF_HORSE] = { 'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' };
	const int possibleRow[MAX_BOUNDARY_OF_TILE] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	const char possibleColumn[MAX_BOUNDARY_OF_TILE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' , 'h' };

	char horse[MAX_NUM_OF_HORSE];
	int row[MAX_BOUNDARY_OF_TILE]; // 숫자, 가로
	char column[MAX_NUM_OF_HORSE]; // 알파벳, 세로

	while (!is.eof()) {
		char temporaryHorse;
		int temporayRow;
		char temporayColumn;
		bool possible = true;
		bool didMinus = false;

		is >> temporaryHorse;
		if (is.fail()) {
			is.clear();
			std::string dummy;
			is >> dummy;
		}
		else {
			break;
		}

		is >> temporayColumn;

		if (is.fail()) {
			is.clear();
			std::string dummy;
			is >> dummy;
		}
		else {
			break;
		}

		is >> temporayRow;

		if (is.fail()) {
			is.clear();
			std::string dummy;
			is >> dummy;
		}
		else {
			break;
		}

		if (temporayColumn >= 'A' && temporayColumn <= 'H') {
			temporayColumn = std::tolower(temporayColumn);
		}

		for (int i = 0; i < KIND_OF_HORSE; ++i) {
			if (temporaryHorse == possibleHorse[i]) {
				break;
			}
			else if (i == KIND_OF_HORSE - 1 && temporaryHorse != possibleHorse[i]) {
				possible = false;
			}
		}
		if (possible) {
			for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
				if (temporayRow == possibleRow[i]) {
					break;
				}
				else if (i == MAX_BOUNDARY_OF_TILE - 1 && temporayRow != possibleRow[i]) {
					possible = false;
				}
			}
		}
		if (possible) {
			for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
				if (temporayColumn == possibleColumn[i]) {
					break;
				}
				else if (i == MAX_BOUNDARY_OF_TILE - 1 && temporayColumn != possibleColumn[i]) {
					possible = false;
				}
			}
		}
		if (possible) {
			switch (temporaryHorse) //'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' 소문자가 White, 대문자가 Black
			{
			case 'r': {
				if (numOfAvailableWhiteRocks > 0) {
					--numOfAvailableWhiteRocks;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'n': {
				if (numOfAvailableWhiteKnights > 0) {
					--numOfAvailableWhiteKnights;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'b': {
				if (numOfAvailableWhiteBishops > 0) {
					--numOfAvailableWhiteBishops;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'k': {
				if (numOfAvailableWhiteKing > 0) {
					--numOfAvailableWhiteKing;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'q': {
				if (numOfAvailableWhiteQueen > 0) {
					--numOfAvailableWhiteQueen;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'p': {
				if (numOfAvailableWhitePawns > 0) {
					--numOfAvailableWhitePawns;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'R': {
				if (numOfAvailableBlackRocks > 0) {
					--numOfAvailableBlackRocks;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'N': {
				if (numOfAvailableBlackKnights > 0) {
					--numOfAvailableBlackKnights;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'B': {
				if (numOfAvailableBlackBishops > 0) {
					--numOfAvailableBlackBishops;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'K': {
				if (numOfAvailableBlackKing > 0) {
					--numOfAvailableBlackKing;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'Q': {
				if (numOfAvailableBlackQueen > 0) {
					--numOfAvailableBlackQueen;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'P': {
				if (numOfAvailableBlackPawns > 0) {
					--numOfAvailableBlackPawns;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			default:
				break;
			}
		}
		if (possible) {
			switch (temporayColumn)
			{
			case 'a': {
				if (chessTable[temporayRow][0] == ' ') {
					chessTable[temporayRow][0] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'b': {
				if (chessTable[temporayRow][1] == ' ') {
					chessTable[temporayRow][1] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'c': {
				if (chessTable[temporayRow][2] == ' ') {
					chessTable[temporayRow][2] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'd': {
				if (chessTable[temporayRow][3] = ' ') {
					chessTable[temporayRow][3] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'e': {
				if (chessTable[temporayRow][4] = ' ') {
					chessTable[temporayRow][4] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'f': {
				if (chessTable[temporayRow][5] = ' ') {
					chessTable[temporayRow][5] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'g': {
				if (chessTable[temporayRow][6] = ' ') {
					chessTable[temporayRow][6] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'h': {
				if (chessTable[temporayRow][7] = ' ') {
					chessTable[temporayRow][7] = temporaryHorse;
				}
				else {
					possible = false;
				}
				break;
			}
			default:
				break;
			}
		}
		// Revert Availabe Value, If Impossible Input
		if (!possible && didMinus) {
			switch (temporaryHorse) //'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' 소문자가 White, 대문자가 Black
			{
			case 'r': {
				++numOfAvailableWhiteRocks;
				break;
			}
			case 'n': {
				++numOfAvailableWhiteKnights;
				break;
			}
			case 'b': {
				++numOfAvailableWhiteBishops;
				break;
			}
			case 'k': {
				++numOfAvailableWhiteKing;
				break;
			}
			case 'q': {
				++numOfAvailableWhiteQueen;
				break;
			}
			case 'p': {
				++numOfAvailableWhitePawns;
				break;
			}
			case 'R': {
				++numOfAvailableBlackRocks;
				break;
			}
			case 'N': {
				++numOfAvailableBlackKnights;
				break;
			}
			case 'B': {
				++numOfAvailableBlackBishops;
				break;
			}
			case 'K': {
				++numOfAvailableBlackKing;
				break;
			}
			case 'Q': {
				++numOfAvailableBlackQueen;
				break;
			}
			case 'P': {
				++numOfAvailableBlackPawns;
				break;
			}
			default:
				break;
			}
		}
	}

	os << "*-------------------------*\n";
	os << "*   abcdefgh              *\n";
	os << "*  +--------+             *\n";
	for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
		os << "* " << i << "|";
		for (int j = 0; j < MAX_BOUNDARY_OF_TILE; ++j) {
			os << chessTable[i][j];
		}
		os << "|             *\n";
	}
	os << "*  +--------+             *\n";
}

void chess::PrintGameInformation(std::istream& is, std::ostream& os) {
	const char possibleHorse[KIND_OF_HORSE] = { 'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' };
	const int possibleRow[MAX_BOUNDARY_OF_TILE] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	const char possibleColumn[MAX_BOUNDARY_OF_TILE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' , 'h' };

	bool chessTable[MAX_BOUNDARY_OF_TILE][MAX_BOUNDARY_OF_TILE];

	for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
		for (int j = 0; j < MAX_BOUNDARY_OF_TILE; ++j) {
			chessTable[i][j] = true;
		}
	}

	int blackScore = 0;
	int whiteScore = 0;

	int blackPawns = 0;
	int blackRocks = 0;
	int blackKnights = 0;
	int blackBishops = 0;
	int blackQueen = 0;
	int blackKing = 0;

	int whitePawns = 0;
	int whiteRocks = 0;
	int whiteKnights = 0;
	int whiteBishops = 0;
	int whiteQueen = 0;
	int whiteKing = 0;

	int numOfAvailableBlackPawns = 8;
	int numOfAvailableBlackRocks = 2;
	int numOfAvailableBlackKnights = 2;
	int numOfAvailableBlackBishops = 2;
	int numOfAvailableBlackQueen = 1;
	int numOfAvailableBlackKing = 1;

	int numOfAvailableWhitePawns = 8;
	int numOfAvailableWhiteRocks = 2;
	int numOfAvailableWhiteKnights = 2;
	int numOfAvailableWhiteBishops = 2;
	int numOfAvailableWhiteQueen = 1;
	int numOfAvailableWhiteKing = 1;

	std::string result = "ON GOING GAME";
	std::string whoIsWinning = "NONE";

	while (!is.eof()) {
		char temporaryHorse;
		int temporayRow;
		char temporayColumn;
		bool didMinus = false;
		bool possible = true;

		is >> temporaryHorse;
		if (is.fail()) {
			is.clear();
			std::string dummy;
			is >> dummy;
		}
		else {
			break;
		}

		is >> temporayColumn;

		if (is.fail()) {
			is.clear();
			std::string dummy;
			is >> dummy;
		}
		else {
			break;
		}

		is >> temporayRow;

		if (is.fail()) {
			is.clear();
			std::string dummy;
			is >> dummy;
		}
		else {
			break;
		}

		if (temporayColumn >= 'A' && temporayColumn <= 'H') {
			temporayColumn = std::tolower(temporayColumn);
		}

		// Check Input is Available
		for (int i = 0; i < KIND_OF_HORSE; ++i) {
			if (temporaryHorse == possibleHorse[i]) {
				break;
			}
			else if (i == KIND_OF_HORSE - 1 && temporaryHorse != possibleHorse[i]) {
				possible = false;
			}
		}
		if (possible) {
			for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
				if (temporayRow == possibleRow[i]) {
					break;
				}
				else if (i == MAX_BOUNDARY_OF_TILE - 1 && temporayRow != possibleRow[i]) {
					possible = false;
				}
			}
		}
		if (possible) {
			for (int i = 0; i < MAX_BOUNDARY_OF_TILE; ++i) {
				if (temporayColumn == possibleColumn[i]) {
					break;
				}
				else if (i == MAX_BOUNDARY_OF_TILE - 1 && temporayColumn != possibleColumn[i]) {
					possible = false;
				}
			}
		}
		if (possible) {
			switch (temporaryHorse) //'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' 소문자가 White, 대문자가 Black
			{
			case 'r': {
				if (numOfAvailableWhiteRocks > 0) {
					--numOfAvailableWhiteRocks;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'n': {
				if (numOfAvailableWhiteKnights > 0) {
					--numOfAvailableWhiteKnights;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'b': {
				if (numOfAvailableWhiteBishops > 0) {
					--numOfAvailableWhiteBishops;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'k': {
				if (numOfAvailableWhiteKing > 0) {
					--numOfAvailableWhiteKing;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'q': {
				if (numOfAvailableWhiteQueen > 0) {
					--numOfAvailableWhiteQueen;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'p': {
				if (numOfAvailableWhitePawns > 0) {
					--numOfAvailableWhitePawns;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'R': {
				if (numOfAvailableBlackRocks > 0) {
					--numOfAvailableBlackRocks;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'N': {
				if (numOfAvailableBlackKnights > 0) {
					--numOfAvailableBlackKnights;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'B': {
				if (numOfAvailableBlackBishops > 0) {
					--numOfAvailableBlackBishops;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'K': {
				if (numOfAvailableBlackKing > 0) {
					--numOfAvailableBlackKing;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'Q': {
				if (numOfAvailableBlackQueen > 0) {
					--numOfAvailableBlackQueen;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'P': {
				if (numOfAvailableBlackPawns > 0) {
					--numOfAvailableBlackPawns;
					didMinus = true;
				}
				else {
					possible = false;
				}
				break;
			}
			default:
				break;
			}
		}
		if (possible) {
			switch (temporayColumn)
			{
			case 'a': {
				if (chessTable[temporayRow][0]) {
					chessTable[temporayRow][0] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'b': {
				if (chessTable[temporayRow][1]) {
					chessTable[temporayRow][1] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'c': {
				if (chessTable[temporayRow][2]) {
					chessTable[temporayRow][2] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'd': {
				if (chessTable[temporayRow][3]) {
					chessTable[temporayRow][3] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'e': {
				if (chessTable[temporayRow][4]) {
					chessTable[temporayRow][4] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'f': {
				if (chessTable[temporayRow][5]) {
					chessTable[temporayRow][5] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'g': {
				if (chessTable[temporayRow][6]) {
					chessTable[temporayRow][6] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			case 'h': {
				if (chessTable[temporayRow][7]) {
					chessTable[temporayRow][7] = false;
				}
				else {
					possible = false;
				}
				break;
			}
			default:
				break;
			}
		}
		if (!possible && didMinus) {
			switch (temporaryHorse) //'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' 소문자가 White, 대문자가 Black
			{
			case 'r': {
				++numOfAvailableWhiteRocks;
				break;
			}
			case 'n': {
				++numOfAvailableWhiteKnights;
				break;
			}
			case 'b': {
				++numOfAvailableWhiteBishops;
				break;
			}
			case 'k': {
				++numOfAvailableWhiteKing;
				break;
			}
			case 'q': {
				++numOfAvailableWhiteQueen;
				break;
			}
			case 'p': {
				++numOfAvailableWhitePawns;
				break;
			}
			case 'R': {
				++numOfAvailableBlackRocks;
				break;
			}
			case 'N': {
				++numOfAvailableBlackKnights;
				break;
			}
			case 'B': {
				++numOfAvailableBlackBishops;
				break;
			}
			case 'K': {
				++numOfAvailableBlackKing;
				break;
			}
			case 'Q': {
				++numOfAvailableBlackQueen;
				break;
			}
			case 'P': {
				++numOfAvailableBlackPawns;
				break;
			}
			default:
				break;
			}
		}
		if (possible) {
			switch (temporaryHorse) //'r', 'n', 'b', 'k', 'q', 'p', 'R', 'N', 'B', 'K','Q', 'P' 소문자가 White, 대문자가 Black
			{
			case 'r': {
				++whiteRocks;
				break;
			}
			case 'n': {
				++whiteKnights;
				break;
			}
			case 'b': {
				++whiteBishops;
				break;
			}
			case 'k': {
				++whiteKing;
				break;
			}
			case 'q': {
				++whiteQueen;
				break;
			}
			case 'p': {
				++whitePawns;
				break;
			}
			case 'R': {
				++blackRocks;
				break;
			}
			case 'N': {
				++blackKnights;
				break;
			}
			case 'B': {
				++blackBishops;
				break;
			}
			case 'K': {
				++blackKing;
				break;
			}
			case 'Q': {
				++blackQueen;
				break;
			}
			case 'P': {
				++blackPawns;
				break;
			}
			default:
				break;
			}
		}
	}

	// Caculate Score
	blackScore += (blackPawns * 100) + (blackKnights * 320) + (blackBishops * 330) + (blackRocks * 500) + (blackQueen * 900) + (blackKing * 20000);
	whiteScore += (whitePawns * 100) + (whiteKnights * 320) + (whiteBishops * 330) + (whiteRocks * 500) + (whiteQueen * 900) + (whiteKing * 20000);

	if (whiteScore > blackScore) {
		whoIsWinning = "WHITE";
	}
	else if (whiteScore < blackScore) {
		whoIsWinning = "BLACK";
	}

	if (blackKing == 0) {
		result = "WHITE WIN";
	}
	else if (whiteKing == 0) {
		result == "BLACK WIN";
	}

	os << "*-------------------------*\n";
	os << "* Black pawns:   " << blackPawns << "        *\n";
	os << "* Black rocks:   " << blackRocks << "        *\n";
	os << "* Black knights: " << blackKnights << "        *\n";
	os << "* Black bishops: " << blackBishops << "        *\n";
	os << "* Black queen:   " << blackQueen << "        *\n";
	os << "* Black king:    " << blackKing << "        *\n";
	os << "* White pawns:   " << whitePawns << "        *\n";
	os << "* White rocks:   " << whiteRocks << "        *\n";
	os << "* White knights: " << whiteKnights << "        *\n";
	os << "* White bishops: " << whiteBishops << "        *\n";
	os << "* White queen:   " << whiteQueen << "        *\n";
	os << "* White king:    " << whiteKing << "        *\n";

	if (result == "ON GOING GAME") {
		os << "* Result: " << result << "   *\n";
	}
	else if (result == "WHITE WIN") {
		os << "* Result: " << result << "       *\n";
	}
	else if (result == "BLACK WIN") {
		os << "* Result: " << result << "       *\n";
	}
	if (whoIsWinning == "NONE") {
		os << "* Who is winning?: " << whoIsWinning << "   *\n";
	}
	else if (whoIsWinning == "WHITE") {
		os << "* Who is winning?: " << whoIsWinning << "  *\n";
	}
	else if (whoIsWinning == "BLACK") {
		os << "* Who is winning?: " << whoIsWinning << "  *\n";
	}
}
