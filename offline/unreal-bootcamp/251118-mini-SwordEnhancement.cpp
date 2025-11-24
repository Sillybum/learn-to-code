// 이 게임은 NBS님의 작품인 '검강화하기 v5.10_1' 플래시 게임의 연습용 클론 코딩입니다.
// This game is a clone coding practice of a game by NBS, '검강화하기 v5.10_1'.
// https://vidkidz.tistory.com/5423


#include <iostream>
#include <random>
using namespace std;

// random.h
random_device rd;

// Constant - number
const int numberOfItem = 21;
const int numberOfShoppingList = 6;
const int numberOfCraftList = 9;

// Item list
enum eItem
{
	낡은단검,쓸만한단검,견고한단검,바이킹소드,불타는검,
	냉기의소드,양날검,심판자의대검,마력의검,타우스워드,
	형광검, 피묻은검, 화염의쌍검, 불꽃마검, 마검아포피스,
	데몬배틀엑스, 투명검, 날렵한용검, 샤이니소드, 왕푸야샤, 다색검
};
// Figure out the string name of each item by passing enum as parameters.
string aItem[numberOfItem]
{
	"낡은단검","쓸만한단검","견고한단검","바이킹소드","불타는검",
	"냉기의소드","양날검","심판자의대검","마력의검","타우스워드",
	"형광검", "피묻은검", "화염의쌍검", "불꽃마검", "마검아포피스",
	"데몬배틀엑스", "투명검", "날렵한용검", "샤이니소드", "왕푸야샤", "다색검",
};

// Shopping list
string aShopingList[numberOfShoppingList]
{
	"+9강 워프권", "+13강 워프권", "+14강 워프권",
	"+15강 워프권", "깨짐 방지권 x 1", "깨짐 방지권 x 3",
};
// Prices of shopping items
int aShoppingCost[numberOfShoppingList]
{
	1000000, 7000000, 10000000,
	1000000, 2500000,15000000,
};

// String array to show item list in the shop
string aCraftList[numberOfCraftList] =
{
	"국적불분명 철조각 8개 / 5개 → 깨짐 방지권 1개        0",
	"타우의 뼈 부스러기 5개 / 3개 → 깨짐 방지권 1개       1",
	"빛 바랜 형광물질 3개 / 2개 → + 13강 불꽃 마검 1개    2",
	"스위스산 철조각 5개 / 3개 → 깨짐 방지권 2개          3",
	"불꽃마검 손잡이 2개 → + 16강 투명 검 1개             4",
	"사악한 영혼 4개 → 깨짐 방지권 4개                    5",
	"사악한 영혼 4개 / 6개 → + 19강 왕푸야샤 1개          6",
	"도끼 가루 6개 → 깨짐 방지권 10개                     7",
	"투명 물질 4개 / 3개 → 깨짐 방지권 11개 / 9개         8",
};

// Initial user status
eItem item = eItem::낡은단검;
int money = 10000000;
string location = "강화소";

// List of items obtained by failing upgrades
enum eMaterial
{
	깨짐방지권, 국적불분명철조각, 타우의뼈부스러기, 빛바랜형광물질, 스위스산철조각, 
	불꽃마검손잡이, 사악한영혼, 도끼가루, 투명물질
};
string aMaterialName[9] =
{
	"깨짐방지권", "국적불분명철조각", "타우의뼈부스러기", "빛바랜형광물질", "스위스산철조각",
	"불꽃마검손잡이", "사악한영혼", "도끼가루", "투명물질",
};
int aMaterial[9] = { 0,0,0,0,0,0,0,0,0 };


// User choices for game loop
enum Choice
{
	UPGRADE,
	SELL,
	SHOP,
	CRAFT,
};

// Selling prices
int itemPrice[numberOfItem] =
{
	0,150,400,600,800,
	1600,3500,6100,10000,20000,
	35100,160000,350000,1000000,3000000,
	7500000,14200000,20000000,30000000,47500000,68300000,
};
// Upgrade cost
int upgradeCost[numberOfItem - 1] =
{
	300,300,500,500,1000,
	1500,2000,2000,3000,5000,
	10900,20000,35000,55000,100000,
	180000,300000,300000,500000,800000,
};
// Upgrade rate(%)
float upgradeRate[numberOfItem - 1] =
{
	100,100,100,95,95,
	90,90,90,85,80,
	80,75,70,70,65,
	60,60,55,50,50, 
};


// 강화 로직 (리턴값은 다른 곳에서 처리)
string Upgrade(float randomNumber)
{
	int cost = upgradeCost[item];
	// 강화 비용이 돈보다 많을 때
	if (money < cost)
	{
		return "돈이 부족합니다.\n\n";
	}
	money -= cost;
	if (randomNumber < upgradeRate[item])
	{
		// 강화 성공시 Enum값에서 오른쪽 한 칸 이동
		item = static_cast<eItem>(item + 1);
		return "강화에 성공했습니다.\n\n";
	}
	else
	{
		string msg;
		// 강화 실패 시
		switch (item)
		{
		case eItem::양날검:
			aMaterial[eMaterial::국적불분명철조각] += 1;
			msg += "국적불분명 철조각 1개 획득\n";
			break;
		case eItem::심판자의대검:
			aMaterial[eMaterial::국적불분명철조각] += 1;
			msg += "국적불분명 철조각 1개 획득\n";
			break;
		case eItem::마력의검:
			aMaterial[eMaterial::국적불분명철조각] += 1;
			msg += "국적불분명 철조각 1개 획득\n";
			break;
		case eItem::타우스워드:
			aMaterial[eMaterial::타우의뼈부스러기] += 1;
			msg += "타우의 뼈 부스러기 1개 획득\n";
			break;
		case eItem::형광검:
			aMaterial[eMaterial::빛바랜형광물질] += 1;
			msg += "빛 바랜 형광물질 1개 획득\n";
			break;
		case eItem::피묻은검:
			aMaterial[eMaterial::스위스산철조각] += 1;
			msg += "스위스산 철조각 1개 획득\n";
			break;
		case eItem::화염의쌍검:
			aMaterial[eMaterial::스위스산철조각] += 1;
			msg += "스위스산 철조각 1개 획득\n";
			break;
		case eItem::불꽃마검:
			aMaterial[eMaterial::불꽃마검손잡이] += 2;
			msg += "불꽃마검 손잡이 2개 획득\n";
			break;
		case eItem::마검아포피스:
			aMaterial[eMaterial::사악한영혼] += 3;
			msg += "사악한 영혼 3개 획득\n";
			break;
		case eItem::데몬배틀엑스:
			aMaterial[eMaterial::도끼가루] += 4;
			msg += "도끼자루 4개 획득\n";
			break;
		case eItem::투명검:
			aMaterial[eMaterial::투명물질] += 7;
			msg += "투명물질 7개 획득\n";
			break;
		}
		item = static_cast<eItem>(0);
		msg += "강화에 실패했습니다.\n\n";
		return msg;
	}
}


/*==================출력용====================*/
// 소지 아이템 출력
void PrintItem()
{
	cout << "소지아이템 : " << aItem[item] << endl << endl;
}
// 강화 비용 출력
void PrintCost()
{
	cout << "강화 비용 : " << upgradeCost[item] << endl<< endl;
}
// 아이템강화 출력
void PrintLevel()
{
	cout << "강화 레벨 : " << item << endl << endl;
}
// 아이템 가격 출력
void PrintItemPrice()
{
	cout << "아이템 가격 : "<< itemPrice[item] << endl << endl;
}
// 소유 돈 출력
void PrintMoney()
{
	cout << "소유 금액 : " << money << endl << endl;
}
// 전체 출력(화면 갱신)
void PrintAll()
{
	PrintMoney();
	PrintItem();
	PrintItemPrice();
	PrintLevel();
	PrintCost();
}

// 샵에 갔을 때 아이템과 가격 출력
void PrintShop()
{
	for (int i = 0; i < numberOfShoppingList; i++)
	{
		cout << aShopingList[i] << "    " << aShoppingCost[i] << "원    " << i << endl;
	}
}

void PrintCraft()
{
	for (int i = 0; i < numberOfCraftList; i++)
	{
		cout << aCraftList[i] << endl;
	}
}

void PrintMaterial()
{
	cout << "=======재료 소유 수량=======" << endl;
	for (int i = 0; i < numberOfCraftList; i++)
	{
		cout << aMaterialName[i] << " : " << aMaterial[i] << "개" << endl;
	}
}

int main()
{
	// 난수 생성
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0, 100);

	// false: 게임 종료
	bool isPlaying = true;

	while (isPlaying)
	{
		float randomNumber = dist(gen);
		// 유저가 강화소에 있을 때
		if (location == "강화소")
		{
			PrintAll();
			// 유저 입력 -> 행동(강화, 판매, 장소 이동)
			cout << "강화[0]  판매[1]  상점[2] 조합소[3]: ";
			int input;
			cin >> input;
			switch (input)
			{
			case Choice::UPGRADE:
				system("cls");
				cout << Upgrade(randomNumber);
				break;
			case Choice::SELL:
				system("cls");
				money += itemPrice[item];
				cout << "아이템을 " << itemPrice[item] << "원에 판매하였습니다.\n\n";
				break;
			case Choice::SHOP:
				system("cls");
				location = "상점";
				break;
			case Choice::CRAFT:
				system("cls");
				location = "조합소";
				break;
			}
		}
		// 유저가 상점에 있을 때
		else if (location == "상점")
		{
			PrintShop();
			int input;
			cout << "아이템 구입[0-5] 강화소로 돌아가기[그 외의 숫자]";
			cin >> input;
			float randomNumber2 = dist(gen);
			if (randomNumber2 < 50) {
				switch (input)
				{
				case 0:
					item = eItem::타우스워드;
					system("cls");
					money -= 1000000;
					cout << "9강 워프에 성공했습니다.\n\n";
					location = "강화소";
					break;
				case 1:
					item = eItem::불꽃마검;
					system("cls");
					money -= 7000000;
					cout << "13강 워프에 성공했습니다.\n\n";
					location = "강화소";
					break;
				case 2:
					item = eItem::마검아포피스;
					system("cls");
					money -= 10000000;
					cout << "14강 워프에 성공했습니다.\n\n";
					location = "강화소";
					break;
				case 3:
					item = eItem::데몬배틀엑스;
					system("cls");
					money -= 15000000;
					cout << "15강 워프에 성공했습니다.\n\n";
					location = "강화소";
					break;
				case 4:
					aMaterial[eMaterial::깨짐방지권] += 1;
					system("cls");
					money -= 1000000;
					cout << "깨짐 방지권 1개를 구입했습니다.\n\n";
					break;
				case 5:
					aMaterial[eMaterial::깨짐방지권] += 3;
					system("cls");
					money -= 2500000;
					cout << "깨짐 방지권 3개를 구입했습니다.\n\n";
					break;
				default:
					system("cls");
					location = "강화소";
					break;
				}
			}
			else
			{
				switch (input)
				{
				case 0:
				case 1:
				case 2:
				case 3:
					system("cls");
					cout << "15강 워프에 실패했습니다!!!!\n\n";
					break;
				case 4:
					system("cls");
					aMaterial[eMaterial::깨짐방지권] += 1;
					cout << "깨짐 방지권 1개를 구입했습니다.\n\n";
					break;
				case 5:
					system("cls");
					aMaterial[eMaterial::깨짐방지권] += 3;
					cout << "깨짐 방지권 3개를 구입했습니다.\n\n";
					break;
				default:
					system("cls");
					location = "강화소";
					break;
				}
			}
		}
		// 유저가 조합소에 있는 경우
		else
		{
			PrintMaterial();
			cout << "\n";
			PrintCraft();
			cout << "조합하기[0-8] 돌아가기[그 외 숫자] : ";
			int input;
			cin >> input;
			switch (input)
			{
			case 0:
				if (aMaterial[eMaterial::국적불분명철조각] >= 5)
				{
					aMaterial[eMaterial::국적불분명철조각] -= 5;
					aMaterial[eMaterial::깨짐방지권] += 1;
					system("cls");
					cout << "국적불분명철조각5개를 깨짐방지권 1개와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "국적불분명철조각 개수가 부족합니다.\n\n";
				}
				break;
			case 1:
				if (aMaterial[eMaterial::타우의뼈부스러기] >= 3)
				{
					aMaterial[eMaterial::타우의뼈부스러기] -= 3;
					aMaterial[eMaterial::깨짐방지권] += 1;
					system("cls");
					cout << "타우의뼈부스러기3개를 깨짐방지권 1개와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "타우의뼈부스러기 개수가 부족합니다.\n\n";
				}
				break;
			case 2:
				if (aMaterial[eMaterial::빛바랜형광물질] >= 2)
				{
					aMaterial[eMaterial::빛바랜형광물질] -= 2;
					item = eItem::불꽃마검;
					system("cls");
					cout << "타우의뼈부스러기3개를 불꽃마검과 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "빛바랜형광물질 개수가 부족합니다.\n\n";
				}
				break;
			case 3:
				if (aMaterial[eMaterial::스위스산철조각] >= 3)
				{
					aMaterial[eMaterial::스위스산철조각] -= 3;
					aMaterial[eMaterial::깨짐방지권] += 2;
					system("cls");
					cout << "스위스산철조각3개를 깨짐방지권2개와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "개수가 부족합니다.\n\n";
				}
				break;
			case 4:
				if (aMaterial[eMaterial::불꽃마검손잡이] >= 2)
				{
					aMaterial[eMaterial::불꽃마검손잡이] -= 2;
					item = eItem::투명검;
					system("cls");
					cout << "불꽃마검손잡이를 투명검과 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "개수가 부족합니다.\n\n";
				}
				break;
			case 5:
				if (aMaterial[eMaterial::사악한영혼] >= 4)
				{
					aMaterial[eMaterial::사악한영혼] -= 4;
					aMaterial[eMaterial::깨짐방지권] += 4;
					system("cls");
					cout << "사악한영혼를 깨짐방지권와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "개수가 부족합니다.\n\n";
				}
				break;
			case 6:
				if (aMaterial[eMaterial::사악한영혼] >= 4)
				{
					aMaterial[eMaterial::사악한영혼] -= 4;
					item = eItem::왕푸야샤;
					system("cls");
					cout << "사악한 영혼을 왕푸야샤와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "개수가 부족합니다.\n\n";
				}
				break;
			case 7:
				if (aMaterial[eMaterial::도끼가루] >= 6)
				{
					aMaterial[eMaterial::도끼가루] -= 6;
					aMaterial[eMaterial::깨짐방지권] += 10;
					system("cls");
					cout << "도끼가루를 깨짐방지권와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "개수가 부족합니다.\n\n";
				}
				break;
			case 8:
				if (aMaterial[eMaterial::투명물질] >= 6)
				{
					aMaterial[eMaterial::투명물질] -= 6;
					aMaterial[eMaterial::깨짐방지권] += 11;
					system("cls");
					cout << "투명물질 깨짐방지권와 교환하였습니다.\n\n";
				}
				else
				{
					system("cls");
					cout << "개수가 부족합니다.\n\n";
				}
				break;
			default:
				location = "강화소";
				system("cls");
			}

		}
	}
}
