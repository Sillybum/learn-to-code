// 25. 11. 19.
// Mini Project
// TextRPG for console

#include <iostream>
#include <map>
#include <string>
#include <random>
extern "C" int _getch(void);
using namespace std;


/*-----------------게임 상태---------------------*/
bool isRunning = true;
bool isFighting = false;

/*-----------------상수 목록---------------------*/
const int numLocation = 7;
const int numItemType = 8;
const int numEquipmentType = 6;
const int numItemList = 8;
const int numInventorySlot = 10;

/*-----------------콜렉션-----------------------*/
// 유저 위치
enum eLocation {
    TOWN,
    FIELD,
    SHOP,
    STATUS,
    INVENTORY,
    COMBAT,
    REWARD,
    PURCHASER,
};
string aLocation[numLocation] = {
    "마을",
    "사냥터",
    "상점",
    "정보",
    "인벤토리",
    "전투",
    "보상화면",
};
// 유저 착용 스탯
struct sEquippedStat {
    int hp;
    int mp;
    int attack;
    int defense;
};
// 아이템 타입
enum eItemType {
    NOTHING,
    WEAPON,
    HAT,
    ARMOR,
    GLOVES,
    BOOTS,
    CONSUMABLE,
    QUEST,
};
string aItemType[numItemType] = {
    "없음",
    "무기",
    "모자",
    "갑옷",
    "장갑",
    "신발",
    "소비",
    "퀘스트",
};
// 아이템 목록
struct sItemInfo {
    eItemType type;
    int hp;
    int mp;
    int attack;
    int defense;
};
enum eItemList {
    NOITEM,
    SHORTSWORD,
    HELM,
    CHAINMAIL,
    LEATHERGLOVES,
    LEATHERBOOTS,
    POTION,
    DRAGONTEAR,
};
// 아이템 이름
string aItemList[numItemList] = {
    "없음",
    "단검",
    "헬름",
    "체인메일",
    "가죽장갑",
    "가죽부츠",
    "물약",
    "용의눈물",
};
// 아이템 능력치
map<eItemList, sItemInfo> mItemList = {
    { eItemList::NOITEM, { eItemType::NOTHING, 0, 0, 0, 0 }},
    { eItemList::SHORTSWORD, { eItemType::WEAPON, 0, 0, 200, 0 }},
    { eItemList::HELM, { eItemType::HAT, 0, 0, 0, 100 }},
    { eItemList::CHAINMAIL, { eItemType::ARMOR, 0, 0, 0, 100 }},
    { eItemList::LEATHERGLOVES, { eItemType::GLOVES, 0, 0, 0, 100 }},
    { eItemList::LEATHERBOOTS, { eItemType::BOOTS, 0, 0, 0, 100 }},
    { eItemList::POTION, { eItemType::CONSUMABLE, 100, 0, 0, 0 }},
};
int money = 100000;

// 몬스터 구조
struct sMonster {
    string art;
    string name;
    int hp;
    int attack;
};
// 몬스터 종류
sMonster aMonsterList[] = {
    {"(0 _ 0)っ", "슬라임", 500, 5},
    {"(m W m)//", "고블린", 700, 8},
    {",,,(OO-OO),,,", "대왕거미", 1000, 10},
};


/*-------------------클래스----------------------*/
class Inventory {
public:
    eItemList slot[numInventorySlot];
    Inventory() {
        for (int i = 0; i < numInventorySlot; i++) {
            slot[i] = eItemList::NOITEM;
        }
        cout << "@ 인벤토리가 초기화 되었습니다." << endl;
    }
    // 인벤토리에서 아이템 제거
    void RemoveItem(int index) {
        slot[index] = eItemList::NOITEM;
    }
    // 인벤토리에서 아이템 판매
    void SellItem(int index) {
        money += 1000;
        slot[index] = eItemList::NOITEM;
    }
    // 착용중이던 아이템 인벤토리에 저장
    void DepositEquipment(int index, eItemList item) {
        slot[index] = item;
    }
    // 포션 구매
    string PurchasePotion() {
        int emptySlot = -1;
        if (money < 2000) {
            return "돈이 부족합니다.\n\n";
        }
        for (int i = 0; i < numInventorySlot; i++) {
            if (slot[i] == eItemList::NOITEM) {
                emptySlot = i;
                break;
            }
        }
        if (emptySlot == -1) {
            return "인벤토리가 꽉 찼습니다.\n\n";
        }
        else {
            money -= 2000;
            slot[emptySlot] = eItemList::POTION;
            return "포션을 2000골드에 구매하였습니다.\n\n";
        }
    }
};

class Equipment {
public:
    eItemList weapon;
    eItemList hat;
    eItemList armor;
    eItemList gloves;
    eItemList boots;
    
    // 게임 시작시 장비 초기화
    Equipment() {
        cout << "@ 장비가 초기화 되었습니다." << endl;
        weapon = eItemList::NOITEM;
        hat = eItemList::NOITEM;
        armor = eItemList::NOITEM;
        gloves = eItemList::NOITEM;
        boots = eItemList::NOITEM;
    }
    // 무기 슬롯 장착
    string EquipWeapon(eItemList w) {
        weapon = w;
        string log = aItemList[w] + "을/를 착용하였습니다.\n";
        return log;
    }
    // 모자 슬롯 장착
    string EquipHat(eItemList h) {
        hat = h;
        string log = aItemList[h] + "을/를 착용하였습니다.\n";
        return log;
    }
    // 갑옷 슬롯 장착
    string EquipArmor(eItemList a) {
        armor = a;
        string log = aItemList[a] + "을/를 착용하였습니다.\n";
        return log;
    }
    // 장갑 슬롯 장착
    string EquipGloves(eItemList a) {
        gloves = a;
        string log = aItemList[a] + "을/를 착용하였습니다.\n";
        return log;
    }
    // 신발 슬롯 장착
    string EquipBoots(eItemList a) {
        boots = a;
        string log = aItemList[a] + "을/를 착용하였습니다.\n";
        return log;
    }
};

class Monster {
public:
    string art;
    string name;
    int hp;
    int attack;
    
    // 몬스터 리스트에 있는 몬스터 선택 가능
    Monster(int index) {
        sMonster monster = aMonsterList[index];
        art = monster.art;
        name = monster.name;
        hp = monster.hp;
        attack = monster.attack;
    }
    // 전투시 몬스터 정보 출력
    void ShowStatus() {
        cout << art << endl << name << endl << "체력 :" << hp << endl << "공격력 : " << attack << endl;
    }
    // 전투시 몬스터 랜덤 생성
    Monster* RandomGenerate() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 2);
        int random = dist(gen);
        Monster* monster = new Monster(random);
        return monster;
    }
};

class Player {
public:
    string name;
    int money;
    // 순수 스탯
    int baseHp;
    int baseMp;
    int baseAttack;
    int baseDefense;
    // 장비 효과 적용 후 스탯
    int maxHp;
    int maxMp;
    // 현재 스탯
    int hp;
    int mp;
    int attack;
    int defense;
    // 플레이어 정보
    eLocation location;
    eLocation lastLocation;
    Inventory inventory;
    Equipment equipment;
    sEquippedStat equippedStat;

    // 기본 플레이어 생성
    Player(string name) { 
        this->name = name;
        money = 1000;
        // 순수 스탯 초기화
        baseHp = 1000;
        baseMp = 1000;
        baseAttack = 200;
        baseDefense = 100;
        // 장비 착용 후 스탯 초기화
        maxHp = baseHp;
        maxMp = baseMp;
        hp = baseHp;
        mp = baseMp;
        attack = baseAttack;
        defense = baseDefense;
        // 장비 스탯 초기화
        equippedStat.hp = 0;
        equippedStat.mp = 0;
        equippedStat.attack = 0;
        equippedStat.defense = 0;
        // 유저 위치 초기화
        location = eLocation::TOWN;
        lastLocation = eLocation::TOWN;
        // 생성 메세지
        cout <<"@ " << this->name << "님의 캐릭터가 생성되었습니다." << endl;
    }
    // 현재 착용한 장비 스탯 계산
    void CalculateEquippedStat(Equipment* equipment) {
        equippedStat.attack = mItemList[equipment->weapon].attack;
        equippedStat.defense = mItemList[equipment->hat].defense + mItemList[equipment->armor].defense + mItemList[equipment->gloves].defense + mItemList[equipment->boots].defense;
    }
    // 최종 스탯 계산 후 스탯 변화 로그 반환
    string CalculateStat() {
        int tempAttack = attack;
        int tempDefense = defense;
        string log;
        attack = baseAttack + equippedStat.attack;
        defense = baseDefense + equippedStat.defense;

        if (attack < tempAttack) {
            log = "공격 하락: " + to_string(tempAttack - attack);
        }
        else if (attack > tempAttack) {
            log = "공격 상승: " + to_string(attack - tempAttack);
        }
        else if (defense < tempDefense) {
            log = "방어 하락: " + to_string(tempDefense - defense);
        }
        else if (defense > tempDefense) {
            log = "방어 상승: " + to_string(defense - tempDefense);
        }
        log += "\n\n";
        return log;
    }
    // 몬스터 공격
    void AttackMonster(Monster* monster, Player* player) {
        monster->hp -= attack;
        cout << attack << " 데미지로 공격하였다!!!." << endl << endl;
        if (monster->hp <= 0) {
            monster->hp = 0;
            isFighting = false;
            player->location = eLocation::REWARD;
        }
    }
    // 몬스터에게 피격
    void TakeMonsterDamage(Monster* monster, Player* player) {
        int defenseEffect = (int)(1000 / defense);
        int monsterDamage = monster->attack * defenseEffect;
        hp -= monsterDamage;
        cout << "몬스터에게 " << monsterDamage << " 데미지를 입었습니다!!!." << endl << endl;
        // 체력 0이면 사망 후 게임오버
        if (hp <= 0) {
            hp = 0;
            isFighting = false;
            isRunning = false;
            cout << "GAME OVER" << endl;
            cout << "아무 키나 누르시오..";
            _getch();
        }
    }
    // 전투시 캐릭터 정보 출력
    void ShowStatus() {
        cout << "이름 : " << name << endl;
        cout << "체력 : " << hp << "/" << maxHp << endl;
        cout << "마력 : " << mp << "/" << maxMp << endl;
        cout << endl;
    }
};

/*-----------------게임메세지---------------------*/
// 1. 유저 이름 입력
string ChooseYourNameMsg() {
    cout << "RPG 월드에 입장하였습니다." << endl;
    cout << "이름을 입력하세요: ";
    string name;
    cin >> name;
    return name;
}
// 2. 환영 메세지 출력
void WelcomeMsg() {
    cout << endl;
    cout << "환영합니다." << endl;
    cout << "당신은 시작의 마을에 있습니다." << endl;
    cout << "게임을 진행하시려면 아무 키나 누르세요: " << endl;
    _getch();
}
/*-----------------현재 위치별 메세지----------------*/
// 마을 메세지
int TownChoiceMsg() {
    system("cls");
    cout << "당신은 마을에 있습니다.\n\n";
    int choice;
    cout << "상점[1] 사냥터[2] 인벤토리[3] 정보[4] 매입소[5] 종료[6]: ";
    cin >> choice;
    return choice;
}
// 사냥터 메세지
int FieldChoiceMsg() {
    system("cls");
    cout << "당신은 사냥터에 있습니다\n\n";
    int choice;
    cout << "사냥[1] 마을[2] 인벤토리[3] 정보[4] 종료[5]: ";
    cin >> choice;
    return choice;
}
// 상점 메세지
int ShopChoiceMsg() {
    cout << "당신은 상점에 있습니다.\n소유 골드 : " << money << "\n\n";
    int userInput;
    cout << "물약( 2000골드 )구매[1]  돌아가기[11]: ";
    cin >> userInput;
    return userInput;
}
// 캐릭터 정보창 메세지
int StatusChoiceMsg(Player* player) {
    system("cls");
    cout << "이름 : " << player->name << endl;
    cout << "체력 : " << player->hp << endl;
    cout << "마력 : " << player->mp << endl;
    cout << "공격 : " << player->attack << endl;
    cout << "방어 : " << player->defense << endl;
    cout << "-----------재화------------" << endl;
    cout << "골드 : " << money << endl;
    cout << "-----------장비------------" << endl;
    cout << "무기 : " << aItemList[player->equipment.weapon] << endl;
    cout << "모자 : " << aItemList[player->equipment.hat] << endl;
    cout << "갑옷 : " << aItemList[player->equipment.armor] << endl;
    cout << "장갑 : " << aItemList[player->equipment.gloves] << endl;
    cout << "신발 : " << aItemList[player->equipment.boots] << endl;
    cout << endl;

    cout << "돌아가기[11]: ";
    int choice;
    cin >> choice;
    return choice;
}
// 인벤토리 메세지
int InventoryChoiceMsg(Inventory* inventory) {
    cout << "당신은 인벤토리를 열었습니다.\n\n";
    for (int i = 0; i < numInventorySlot; i++) {
        cout << i << " : " << aItemList[inventory->slot[i]] << endl;
    }
    cout << "사용하실 아이템 번호를 선택하세요(돌아가기[11]): ";
    int userInput;
    cin >> userInput;
    return userInput;
}
// 전투 중 메세지
int CombatChoiceMsg(Monster* monster) {
    cout << "공격하기[1] 도망가기[11]: ";
    int userInput;
    cin >> userInput;
    return userInput;
}
// 매입소 메세지
int PurchaserChoiceMsg(Inventory* inventory) {
    cout << "당신은 매입소에 왔습니다.\n\n";
    for (int i = 0; i < numInventorySlot; i++) {
        cout << i << " : " << aItemList[inventory->slot[i]] << endl;
    }
    cout << "판매하실 아이템 번호를 선택하세요(돌아가기[11]): ";
    int userInput;
    cin >> userInput;
    return userInput;
}

/*-----------------게임 로직---------------------*/
// 마을 분기
void TownChoiceProcess(int choice, Player* player) {
    player->lastLocation = eLocation::TOWN;
    switch (choice)
    {
    case 1:
        player->location = eLocation::SHOP;
        break;
    case 2:
        player->location = eLocation::FIELD;
        break;
    case 3:
        player->location = eLocation::INVENTORY;
        break;
    case 4:
        player->location = eLocation::STATUS;
        break;
    case 5:
        player->location = eLocation::PURCHASER;
        break;
    case 6:
        isRunning = false;
        break;
    default:
        break;
    }
    system("cls");
}
// 사냥터 분기
void FieldChoiceProcess(int userInput, Player* player) {
    player->lastLocation = eLocation::FIELD;
    switch (userInput) {
    case 1:
        player->location = eLocation::COMBAT;
        break;
    case 2:
        player->location = eLocation::TOWN;
        break;
    case 3:
        player->location = eLocation::INVENTORY;
        break;
    case 4:
        player->location = eLocation::STATUS;
        break;
    case 5:
        isRunning = false;
        break;
    }
    system("cls");
}
// 상점 분기
string ShopChoiceProcess(int userInput, Player* player, Inventory* inventory) {
    system("cls");
    string log;
    switch (userInput) {
    case 1:
        log = inventory->PurchasePotion();
        break;
    case 11:
        player->location = player->lastLocation;
        break;
    default:
        log = "잘못된 입력입니다.";
    }
    return log;
}
// 캐릭터 정보창 분기
void StatusChoiceProcess(int userInput, Player* player) {
    if (userInput == 11) {
        player->location = player->lastLocation;
    }
    system("cls");
}
// 인벤토리 분기
string InventoryChoiceProcess(int userInput, Inventory* inventory, Equipment* equipment, Player* player) {
    system("cls");
    if (userInput == 11) {
        player->location = player->lastLocation;
        return "인벤토리를 닫았습니다.\n\n";
    }
    string log;
    eItemList chosenInventoryItem = inventory->slot[userInput];
    // 착용한 아이템이 없을 경우 인벤토리에서 제거, 있을 경우 스왑
    // 무기 착용 및 인벤토리 저장
    if (mItemList[chosenInventoryItem].type == eItemType::WEAPON) {
        if (equipment->weapon == eItemList::NOITEM) {
            log = equipment->EquipWeapon(chosenInventoryItem);
            inventory->RemoveItem(userInput);
        }
        else {
            log = equipment->EquipWeapon(chosenInventoryItem);
            inventory->DepositEquipment(userInput, chosenInventoryItem);
        }
    }
    // 모자 착용 및 인벤토리 저장 
    else if (mItemList[chosenInventoryItem].type == eItemType::HAT) {
        if (equipment->hat == eItemList::NOITEM) {
            log = equipment->EquipHat(chosenInventoryItem);
            inventory->RemoveItem(userInput);
        }
        else {
            log = equipment->EquipHat(chosenInventoryItem);
            inventory->DepositEquipment(userInput, chosenInventoryItem);
        }
    }
    // 갑옷 착용 및 인벤토리 저장
    else if (mItemList[chosenInventoryItem].type == eItemType::ARMOR) {
        if (equipment->armor == eItemList::NOITEM) {
            log = equipment->EquipArmor(chosenInventoryItem);
            inventory->RemoveItem(userInput);
        }
        else {
            log = equipment->EquipArmor(chosenInventoryItem);
            inventory->DepositEquipment(userInput, chosenInventoryItem);
        }
    }
    // 장갑 착용 및 인벤토리 저장
    else if (mItemList[chosenInventoryItem].type == eItemType::GLOVES) {
        if (equipment->gloves == eItemList::NOITEM) {
            log = equipment->EquipGloves(chosenInventoryItem);
            inventory->RemoveItem(userInput);
        }
        else {
            log = equipment->EquipGloves(chosenInventoryItem);
            inventory->DepositEquipment(userInput, chosenInventoryItem);
        }
    }
    // 신발 착용 및 인벤토리 저장
    else if (mItemList[chosenInventoryItem].type == eItemType::BOOTS) {
        if (equipment->boots == eItemList::NOITEM) {
            log = equipment->EquipBoots(chosenInventoryItem);
            inventory->RemoveItem(userInput);
        }
        else {
            log = equipment->EquipBoots(chosenInventoryItem);
            inventory->DepositEquipment(userInput, chosenInventoryItem);
        }
    }
    // 물약 사용
    else if (mItemList[chosenInventoryItem].type == eItemType::CONSUMABLE) {
        if (player->hp == player->maxHp) {
            log = "체력이 가득차 있습니다.";
        }
        else {
            player->hp += 500;
            if (player->maxHp < player->hp) {
                player->hp = player->maxHp;
            }
            inventory->RemoveItem(userInput);
            log = "체력이 500 회복되었습니다.";
        }
    }
    // 아이템이 없는 슬롯을 입력했을 때
    else {
        log = "해당 슬롯에 아이템이 없습니다.\n";
    }
    player->CalculateEquippedStat(equipment);
    log += player->CalculateStat();
    return log;
};
// 전투 분기
void CombatChoiceProcess(int userInput, Player* player, Monster* monster) {
    system("cls");
    // 공격하기
    if (userInput == 1) {
        player->AttackMonster(monster, player);
    }
    // 도망가기
    else if (userInput == 11) {
        isFighting = false;
        player->location = eLocation::FIELD;
    }
}
// 전투 랜덤 보상
string RewardDropProcess(Inventory* inventory) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(0.0f, 100.0f);
    float random = dist(gen);
    if (random < 1) {
        int emptySlot = -1;
        for (int i = 0; i < numInventorySlot; i++) {
            if (inventory->slot[i] == eItemList::NOITEM) {
                emptySlot = i;
                break;
            }
        }
        if (emptySlot == -1) {
            return "인벤토리가 꽉 차서 아이템을 획득하지 못했습니다.\n";
        }
        else {
            inventory->slot[emptySlot] = eItemList::DRAGONTEAR;
            return aItemList[eItemList::DRAGONTEAR] + "을 획득하였습니다.\n";
        }
    }
    else if (random < 70) {
        int emptySlot = -1;
        for (int i = 0; i < numInventorySlot; i++) {
            if (inventory->slot[i] == eItemList::NOITEM) {
                emptySlot = i;
                break;
            }
        }
        if (emptySlot == -1) {
            return "인벤토리가 꽉 차서 아이템을 획득하지 못했습니다.\n";
        }
        else {
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(1, 5);
            int random = dist(gen);
            eItemList droppedItem = static_cast<eItemList>(random);
            inventory->slot[emptySlot] = droppedItem;
            return aItemList[droppedItem] + "을 획득하였습니다.\n";
        }
    }
    else {
        return "아이템을 획득하지 못했습니다.";
    }
}
// 매입소 분기
string PurchaserChoiceProcess(int userInput, Inventory* inventory, Player* player) {
    system("cls");
    string log;
    if (userInput == 11) {
        player->location = player->lastLocation;
        log += "매입소를 떠났습니다.\n\n";
    }
    eItemList chosenItem = inventory->slot[userInput];
    if (chosenItem != eItemList::NOITEM) {
        inventory->SellItem(userInput);
        log += aItemList[chosenItem] + "을/를 판매하였습니다.\n1000골드를 획득하였습니다.\n\n";
    } 
    else {
        log += "아이템이 있는 슬롯을 선택하세요.\n\n\n";
    }

    return log;
}

/*=====================================================*/
/*                     메인 함수                       */
/*=====================================================*/
int main() {
    // 1. 유저 이름 입력
    string userName = ChooseYourNameMsg();
    // 2. 유저 캐릭터 생성
    Player player = Player(userName);
    // 3. 환영 메세지 출력
    WelcomeMsg();

    while (isRunning) {
        string log;
        if (player.location == eLocation::TOWN) {
            // 사용자 입력 처리
            TownChoiceProcess(TownChoiceMsg(), &player);
        }
        // 사냥터
        else if (player.location == eLocation::FIELD) {
            int userInput = FieldChoiceMsg();
            FieldChoiceProcess(userInput, &player);
        }
        // 상점
        else if (player.location == eLocation::SHOP) {
            int userInput = ShopChoiceMsg();
            string log = ShopChoiceProcess(userInput, &player, &player.inventory);
            cout << log;
        }
        // 정보
        else if (player.location == eLocation::STATUS) {
            int userInput = StatusChoiceMsg(&player);
            StatusChoiceProcess(userInput, &player);
        }
        // 인벤토리
        else if (player.location == eLocation::INVENTORY) {
            int userInput = InventoryChoiceMsg(&player.inventory);
            string log = InventoryChoiceProcess(userInput, &player.inventory, &player.equipment, &player);
            cout << log;
        }
        // 사냥
        else if (player.location == eLocation::COMBAT) {
            // 랜덤 몬스터 생성기
            Monster generator = Monster(1);
            // 랜덤 생성
            Monster* monster = generator.RandomGenerate();
            isFighting = true;
            // 유저와 몬스터 공격 턴 전환용
            bool isUserTurn = true;
            while (isFighting) {
                if (isUserTurn) {
                    player.ShowStatus();
                    monster->ShowStatus();
                    int userInput = CombatChoiceMsg(monster);
                    CombatChoiceProcess(userInput, &player, monster);
                    isUserTurn = false;
                }
                else {
                    player.TakeMonsterDamage(monster, &player);
                    isUserTurn = true;
                }
            }
            // 전투후 몬스터 메모리 해제
            delete monster;
        }
        // 전투 승리 보상
        else if (player.location == eLocation::REWARD) {
            cout << "전투에서 승리했습니다!!\n*보상*\n100골드\n";
            cout << RewardDropProcess(&player.inventory) << endl;
            money += 100;
            cout << "계속하려면 아무 키나 입력하세요...";
            // 플에이어는 사냥터로 돌아간다.
            player.location = eLocation::FIELD;
            _getch();
        }
        // 매입소 (아이템 판매)
        else if (player.location == eLocation::PURCHASER) {
            int userInput = PurchaserChoiceMsg(&player.inventory);
            string log = PurchaserChoiceProcess(userInput, &player.inventory, &player);
            cout << log;
        }
    }

}