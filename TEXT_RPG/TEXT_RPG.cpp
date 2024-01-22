#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <map>
#include <Windows.h>

using namespace std;

// ===============================================
// класс Hero будем родственником для последующих классов рас
class Hero
{
protected:
	// задаем начальные параметры любого героя
	// параметры находятся в блоке private чтобы нечестный игрок не мог их изменить
	// для хранения параметров задаем словарь
	map <string, int> stats = { {"strength", 5},
								{"perception", 5},
								{"endurance", 5},
								{"charisma", 5},
								{"agility", 5},
								{"luck", 5} };
	// имя персонажа
	string hero_name = "";
	// переменная, которая отвечает за защиту персонажа. Врагу надо выбросить значение больше или равное защите чтобы попасть по вам
	int defence = 0;
	// переменная которая отвечает за здоровье персонажа
	int health = 0;
	// аттака героя
	int attack = 0;
	// шанс попадания героя
	int hero_hit_chance = 0;
	// защищенный метод для модификации параметров героя (при выборе расы, дает буст или дебафф к параметрам)
	void HeroChangeStats(int s = 0, int p = 0, int e = 0, int c = 0, int a = 0, int l = 0)
	{
		stats["strength"] += s;
		stats["perception"] += p;
		stats["endurance"] += e;
		stats["charisma"] += c;
		stats["agility"] += a;
		stats["luck"] += l;
	}
	void HeroSetHealth(int h = 0)
	{
		health = h;
	}
public:
	Hero()
	{
		// по умолчанию безымянный герой
		hero_name = "Nameless";
	};
	~Hero()
	{

	};
	// реализуме базовые методы доступные каждой расе
	string GetName()
	{
		return hero_name;
	}
	// получить параметры пользователя (силу, внимание, выносливость и т.д.).
	void GetHeroStats()
	{
		cout << GetName() << endl;
		// вывод словаря с нашими параметрами на экран 
		for (auto [stat, value] : stats)
			cout << stat << ": " << value << endl;
	}
	int GetHeroCharisma()
	{
		return stats["charisma"];
	}
	int HeroAttack()
	{
		// атака героя по врагу (зависит только от параметров героя). Атака проходит если hit_chance героя больше чем defence у противника
		if (stats["strength"] > stats["agility"])
		{
			attack = stats["strength"] * 4 + (rand() % (stats["luck"] - 0 + 1) + 0) * 2;
		}
		else
		{
			attack = stats["agility"] * 4 + (rand() % (stats["luck"] - 0 + 1) + 0) * 2;
		}
		return attack;
	}
	int HeroHitChance()
	{
		hero_hit_chance = stats["perception"] / 2 + rand() % (5 - 0 + 1) + 0;
		return hero_hit_chance;
	}
	int HeroDamageResistance()
	{
		// атака врага по герою (если параметр defence у героя выше чем hit_chance у противника то атака не пройдет)
		defence = stats["agility"] / 2 + stats["endurance"] / 2;
		return defence;
	}
	int HeroDamage(int enemy_attack)
	{
		health -= enemy_attack;
		return health;
	}
	int HeroGetHealth()
	{
		return health;
	}
};
// ===============================================
// создаем классы для расы героя, которые будут являться дочерними к классу героя
class Dwarf : public Hero
{
public:
	Dwarf()
	{
		// задаем модификаторы
		// сила += 1, внимание += 0, выносливость += 2, харизма += 0, ловкость -= 1, удача += 0 
		HeroChangeStats(1, 0, 2, 0, -1, 0);
		HeroSetHealth(100);
	};
	Dwarf(string name)
	{
		// задаем модификаторы
		// сила += 1, внимание += 0, выносливость += 2, харизма += 0, ловкость -= 1, удача += 0 
		HeroChangeStats(1, 0, 2, 0, -1, 0);
		HeroSetHealth(100);
		hero_name = name;
	};
	~Dwarf()
	{

	};
	// зададим методы, описывающие способности гнома 
	int StoneArmor()
	{
		// возвращает значение 2, которое мы затем прибавим к расчету формулы защиты
		return 2;
	}
	int AncestorsFury()
	{
		// возвращает значение 3, которое мы затем прибавим к атаке
		return 3;
	}
	int DwarfSong()
	{
		// возвращает значение 2, которое мы затем прибавим к харизме
		return 2;
	}
};

class Human : public Hero
{
public:
	Human()
	{
		// задаем модификаторы
		// сила += 0, внимание += 0, выносливость += 0, харизма += 2, ловкость += 0, удача += 1 
		HeroChangeStats(0, 0, 0, 2, 0, 1);
		HeroSetHealth(80);
	};
	Human(string name)
	{
		// задаем модификаторы
		// сила += 0, внимание += 0, выносливость += 0, харизма += 2, ловкость += 0, удача += 1 
		HeroChangeStats(0, 0, 0, 2, 0, 1);
		HeroSetHealth(80);
		hero_name = name;
	};
	~Human()
	{

	};
	// зададим методы, описывающие способности человека (не забыть вернуть характеристики в начальное состояние после вызова метод GrimDetermination())
	void GrimDetermination()
	{
		// повыжение силы и понижение защиты до конца битвы с врагом
		defence -= 2;
		stats["strength"] += 2;
	}
	void AntiGrimDetermination()
	{
		defence += 2;
		stats["strength"] -= 2;
	}
	int FateDice()
	{
		// возвращает значение 2, которое затем будет прибавлено к удаче
		return 2;
	}
	int ForTheEmperor()
	{
		// возвращает значение 2, которое затем будет прибавлено к харизме
		return 2;
	};
};

class Elf : public Hero
{
public:
	Elf()
	{
		// задаем модификаторы
		// сила -= 1, внимание += 2, выносливость += 0, харизма += 0, ловкость += 1, удача += 0 
		HeroChangeStats(-1, 2, 0, 0, 1, 0);
		HeroSetHealth(70);
	};
	Elf(string name)
	{
		// задаем модификаторы
		// сила += 0, внимание += 0, выносливость += 0, харизма += 0, ловкость += 1, удача += 0 
		HeroChangeStats(-1, 2, 0, 0, 1, 0);
		HeroSetHealth(70);
		hero_name = name;
	};
	~Elf()
	{

	}
	// зададим методы, описывающие способности эльфа 
	int DexterityStrike()
	{
		// возвращает значение 2, которое затем будет прибавлено к ловкости
		return 1;
	}
	int ElvenEye()
	{
		// возвращает значение 2, которое затем будет прибавлено к вниманию
		return 2;
	}
};
// ===============================================
// класс Enemy, который будет  наследоваться всеми остальными врагами
class Enemy
{
protected:
	int health = 0;
	int attack = 0;
	int defence = 0;
	int hit_chance = 0;
	string enemy_name = "";
	// метод для изменения параметров врагов
	void EnemyChangeStats(int h, int a, int d, int h_c)
	{
		health = h + rand() % (20 - 10 + 1) + 10;
		attack = a + rand() % (10 - 0 + 1) + 0;
		defence = d + rand() % (2 - 0 + 1) + 0;
		hit_chance = h_c + rand() % (2 - 0 + 1) + 0;
	}
public:
	Enemy()
	{
		enemy_name = "HostileEntity";
	}
	~Enemy()
	{

	}
	// основные методы болванчиков: атака, защита от атаки, получение урона, оставшееся здоровье
	int EnemyAttack()
	{
		return attack;
	}
	int EnemyDefence()
	{
		return defence;
	}
	int EnemyGetDamage(int damage)
	{
		health -= damage;
		return health;
	}
	int EnemyHealth()
	{
		return health;
	}
	int EnemyHitChance()
	{
		return hit_chance;
	}
	void EnemyReduceDefence()
	{
		defence -= 2;
	}
};
// ===============================================
// класса врагов, которые являются дочерьними к классу Enemy
class Goblin : public Enemy
{
public:
	Goblin()
	{
		enemy_name = "Goblin";
		// здоровье, атака, защита, шанс попадания
		EnemyChangeStats(30, 10, 2, 3);
	}
	~Goblin()
	{

	}
};

class Bandit : public Enemy
{
public:
	Bandit()
	{
		enemy_name = "Bandit";
		// здоровье, атака, защита, шанс попадания
		EnemyChangeStats(45, 15, 3, 4);
	}
	~Bandit()
	{

	}
};

class Orc : public Enemy
{
public:
	Orc()
	{
		enemy_name = "Orc";
		// здоровье, атака, защита, шанс попадания
		EnemyChangeStats(55, 20, 4, 5);
	}
	~Orc()
	{

	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	// для корректного отображения кириллицы в консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// для корректного отображения кириллицы в консоли
	string your_hero_name = "";
	string hero_race = "";
	cout << "Введите имя персонажа: ";
	cin >> your_hero_name;
	// до тех пор пока не будет выбрана одна из предложенных рас вам будут предлагать совершить выбор
	boolean race_flag_repeater = true;
	while (race_flag_repeater)
	{
		cout << "Выберите расу персонажа(Дварф, Эльф, Человек): ";
		cin >> hero_race;
		switch (hero_race.length())
		{
			// реализовано сверх коряво, подумать как исправить
		case 4:
		{
			Elf hero = Elf(your_hero_name);
			cout << "Вы выбрали расу Эльф" << endl;
			hero.GetHeroStats();
			cout << "Данная раса обладает следующими способностями" << endl;
			cout << "Эльфийский взор дает +2 к вниманию на следующую атаку это может помочь попасть по врагу" << endl;
			cout << "Ловкий удар дает +2 к ловкости это может помочь нанести больший урон" << endl;
			race_flag_repeater = false;
			boolean game_over = false;
			// пока не победите 5 врагов вас не выпустят из подземелья
			for (int enemy_counter = 0; enemy_counter < 5; enemy_counter++)
			{
				// рандомайзер врагов
				int random_enemy = (rand() % (3 - 1 + 1) + 1);
				if (game_over == true) break;
				if (random_enemy == 1)
				{
					Goblin enemy_goblin = Goblin();
					cout << "Вашим врагом будет гоблин" << endl;
					while (enemy_goblin.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Ловкий удар - 1), (Эльфийский взор - 2): ";
						cin >> ability;
						if (ability == 1)
						{
							if (hero.HeroHitChance() > enemy_goblin.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.DexterityStrike();
								cout << "Здоровье врага: " << enemy_goblin.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_goblin.EnemyGetDamage(attack) << endl;
								if (enemy_goblin.EnemyHealth() <= 0)
								{
									cout << "=========================Гоблин повержен!=========================" << endl;
									break;
								}
							}
							else
							{
								cout << "Промах!" << endl;
							}
						}
						else if (ability == 2)
						{
							if (hero.HeroHitChance() + hero.ElvenEye() > enemy_goblin.EnemyDefence())
							{
								attack = hero.HeroAttack();
								cout << "Здоровье врага: " << enemy_goblin.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_goblin.EnemyGetDamage(attack) << endl;
								if (enemy_goblin.EnemyHealth() <= 0)
								{
									cout << "=========================Гоблин повержен!=========================" << endl;
									break;
								}
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() > enemy_goblin.EnemyHitChance())
						{
							cout << "Гоблин промахнулся!" << endl;
						}
						else
						{
							cout << "Гоблин попадает и наносит " << enemy_goblin.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_goblin.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
				else if (random_enemy == 2)
				{
					Orc enemy_orc = Orc();
					cout << "Вашим врагом будет орк" << endl;
					while (enemy_orc.EnemyHealth() * hero.HeroGetHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Ловкий удар - 1), (Эльфийский взор - 2): ";
						cin >> ability;
						if (ability == 1)
						{
							if (hero.HeroHitChance() > enemy_orc.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.DexterityStrike();
								cout << "Здоровье врага: " << enemy_orc.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_orc.EnemyGetDamage(attack) << endl;
								if (enemy_orc.EnemyHealth() <= 0)
								{
									cout << "=========================Орк повержен!=========================" << endl;
									break;
								}
							}
							else
							{
								cout << "Промах!" << endl;
							}
						}
						else if (ability == 2)
						{
							if (hero.HeroHitChance() + hero.ElvenEye() > enemy_orc.EnemyDefence())
							{
								attack = hero.HeroAttack();
								cout << "Здоровье врага: " << enemy_orc.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_orc.EnemyGetDamage(attack) << endl;
								if (enemy_orc.EnemyHealth() <= 0)
								{
									cout << "=========================Орк повержен!=========================" << endl;
									break;
								}
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() > enemy_orc.EnemyHitChance())
						{
							cout << "Орк промахнулся!" << endl;
						}
						else
						{
							cout << "Орк попадает и наносит " << enemy_orc.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_orc.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
				else if (random_enemy == 3)
				{
					Bandit enemy_bandit = Bandit();
					cout << "Вашим врагом будет бандит" << endl;
					while (enemy_bandit.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Ловкий удар - 1), (Эльфийский взор - 2): ";
						cin >> ability;
						if (ability == 1)
						{
							if (hero.HeroHitChance() > enemy_bandit.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.DexterityStrike();
								cout << "Здоровье врага: " << enemy_bandit.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_bandit.EnemyGetDamage(attack) << endl;
								if (enemy_bandit.EnemyHealth() <= 0)
								{
									cout << "=========================Бандит повержен!=========================" << endl;
									break;
								}
							}
							else
							{
								cout << "Промах!" << endl;
							}
						}
						else if (ability == 2)
						{
							if (hero.HeroHitChance() + hero.ElvenEye() > enemy_bandit.EnemyDefence())
							{
								attack = hero.HeroAttack();
								cout << "Здоровье врага: " << enemy_bandit.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_bandit.EnemyGetDamage(attack) << endl;
								if (enemy_bandit.EnemyHealth() <= 0)
								{
									cout << "=========================Бандит повержен!=========================" << endl;
									break;
								}
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() > enemy_bandit.EnemyHitChance())
						{
							cout << "Бандит промахнулся!" << endl;
						}
						else
						{
							cout << "Бандит попадает и наносит " << enemy_bandit.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_bandit.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		case 5:
		{
			Dwarf hero = Dwarf(your_hero_name);
			cout << "Вы выбрали расу дворф." << endl;
			hero.GetHeroStats();
			cout << "Данная раса обладает следующими способностями." << endl;
			cout << "Каменная броня при использовании дает +2 к защите, благодаря чему враги могут по вам не попасть" << endl;
			cout << "Ярость предков позволяет увеличить урон на заданный модификатор, но при этом пострадает точность" << endl;
			cout << "Гномья залихватская песня позволяет получить бонус +2 к харизме. В случае если общее значение харизмы будет >= случайному числу то защита врага существенно ослабнет" << endl;
			boolean game_over = false;
			race_flag_repeater = false;
			// пока не победите 5 врагов вас не выпустят из подземелья
			for (int enemy_counter = 0; enemy_counter < 5; enemy_counter++)
			{
				int random_enemy = (rand() % (3 - 1 + 1) + 1);
				if (game_over == true) break;
				if (random_enemy == 1)
				{
					Goblin enemy_goblin = Goblin();
					cout << "Вашим врагом будет гоблин" << endl;
					while (enemy_goblin.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Каменная броня - 1), (Ярость предков - 2), (Гномья залихватская песня - 3): ";
						cin >> ability;
						if (hero.HeroHitChance() > enemy_goblin.EnemyDefence())
						{
							attack = hero.HeroAttack();
							cout << "Здоровье врага: " << enemy_goblin.EnemyHealth() << endl;
							cout << "Вы нанесли " << attack << "урона" << endl;
							cout << "Оставшьеся здоровье: " << enemy_goblin.EnemyGetDamage(attack) << endl;
							if (enemy_goblin.EnemyHealth() <= 0)
							{
								cout << "=========================Гоблин повержен!=========================" << endl;
								break;
							}
						}
						else
						{
							cout << "Промах!" << endl;
						}
						if (ability == 2)
						{
							if (hero.HeroHitChance() - 1 > enemy_goblin.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.AncestorsFury() * (rand() % (20 - 10 + 1) + 10);
								cout << "Здоровье врага: " << enemy_goblin.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << "урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_goblin.EnemyGetDamage(attack) << endl;
								if (enemy_goblin.EnemyHealth() <= 0)
								{
									cout << "=========================Гоблин повержен!=========================" << endl;
									break;
								}
							}
						}
						else if (ability == 3)
						{
							if ((hero.GetHeroCharisma() + hero.DwarfSong()) >= (rand() % (10 - 0 + 1) + 0))
							{
								enemy_goblin.EnemyReduceDefence();
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() + (ability == 1 ? hero.StoneArmor() : 0) > enemy_goblin.EnemyHitChance())
						{
							cout << "Гоблин промахнулся!" << endl;
						}
						else
						{
							cout << "Гоблин попадает и наносит " << enemy_goblin.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_goblin.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
				else if (random_enemy == 2)
				{
					Orc enemy_orc = Orc();
					cout << "Вашим врагом будет гоблин" << endl;
					while (enemy_orc.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Каменная броня - 1), (Ярость предков - 2), (Гномья залихватская песня - 3): ";
						cin >> ability;
						if (hero.HeroHitChance() > enemy_orc.EnemyDefence())
						{
							attack = hero.HeroAttack();
							cout << "Здоровье врага: " << enemy_orc.EnemyHealth() << endl;
							cout << "Вы нанесли " << attack << " урона" << endl;
							cout << "Оставшьеся здоровье: " << enemy_orc.EnemyGetDamage(attack) << endl;
							if (enemy_orc.EnemyHealth() <= 0)
							{
								cout << "=========================Гоблин повержен!=========================" << endl;
								break;
							}
						}
						else
						{
							cout << "Промах!" << endl;
						}
						if (ability == 2)
						{
							if (hero.HeroHitChance() - 1 > enemy_orc.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.AncestorsFury() * (rand() % (20 - 10 + 1) + 10);
								cout << "Здоровье врага: " << enemy_orc.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_orc.EnemyGetDamage(attack) << endl;
								if (enemy_orc.EnemyHealth() <= 0)
								{
									cout << "=========================Орк повержен!=========================" << endl;
									break;
								}
							}
						}
						else if (ability == 3)
						{
							if ((hero.GetHeroCharisma() + hero.DwarfSong()) >= (rand() % (10 - 0 + 1) + 0))
							{
								enemy_orc.EnemyReduceDefence();
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() + (ability == 1 ? hero.StoneArmor() : 0) > enemy_orc.EnemyHitChance())
						{
							cout << "Орк промахнулся!" << endl;
						}
						else
						{
							cout << "Орк попадает и наносит " << enemy_orc.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_orc.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
				else if (random_enemy == 3)
				{
					Bandit enemy_bandit = Bandit();
					cout << "Вашим врагом будет гоблин" << endl;
					while (enemy_bandit.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Каменная броня - 1), (Ярость предков - 2), (Гномья залихватская песня - 3): ";
						cin >> ability;
						if (hero.HeroHitChance() > enemy_bandit.EnemyDefence())
						{
							attack = hero.HeroAttack();
							cout << "Здоровье врага: " << enemy_bandit.EnemyHealth() << endl;
							cout << "Вы нанесли " << attack << "урона" << endl;
							cout << "Оставшьеся здоровье: " << enemy_bandit.EnemyGetDamage(attack) << endl;
							if (enemy_bandit.EnemyHealth() <= 0)
							{
								cout << "=========================Бандит повержен!=========================" << endl;
								break;
							}
						}
						else
						{
							cout << "Промах!" << endl;
						}
						if (ability == 2)
						{
							if (hero.HeroHitChance() - 1 > enemy_bandit.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.AncestorsFury() * (rand() % (20 - 10 + 1) + 10);
								cout << "Здоровье врага: " << enemy_bandit.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_bandit.EnemyGetDamage(attack) << endl;
								if (enemy_bandit.EnemyHealth() <= 0)
								{
									cout << "=========================Бандит повержен!=========================" << endl;
									break;
								}
							}
						}
						else if (ability == 3)
						{
							if ((hero.GetHeroCharisma() + hero.DwarfSong()) >= (rand() % (10 - 0 + 1) + 0))
							{
								enemy_bandit.EnemyReduceDefence();
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() + (ability == 1 ? hero.StoneArmor() : 0) > enemy_bandit.EnemyHitChance())
						{
							cout << "Бандит промахнулся!" << endl;
						}
						else
						{
							cout << "Бандит попадает и наносит " << enemy_bandit.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_bandit.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		case 7:
		{
			Human hero = Human(your_hero_name);
			cout << "Вы выбрали расу человек" << endl;
			hero.GetHeroStats();
			cout << "Данная раса обладает следующими способностями." << endl;
			cout << "Мрачная решимость понижает защиту на 2, но взамен повышает силу на 2 до конца текущего боя с врагом." << endl;
			cout << "Кости судьбы повышают удачу на 2" << endl;
			cout << "Способность \"За императора\" повышает харизму на 2" << endl;
			boolean game_over = false;
			race_flag_repeater = false;
			// пока не победите 5 врагов вас не выпустят из подземелья
			for (int enemy_counter = 0; enemy_counter < 5; enemy_counter++)
			{
				// рандомайзер врагов
				int random_enemy = (rand() % (3 - 1 + 1) + 1);
				if (game_over == true) break;
				if (random_enemy == 1)
				{
					Goblin enemy_goblin = Goblin();
					boolean grim_determination_flag = false;
					cout << "Вашим врагом будет гоблин" << endl;
					while (enemy_goblin.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Мрачная решимость - 1), (Кости судьбы - 2), (За императора! - 3): ";
						cin >> ability;
						if (ability == 1)
						{
							grim_determination_flag = true;
							hero.GrimDetermination();
							if (hero.HeroHitChance() > enemy_goblin.EnemyDefence())
							{
								attack = hero.HeroAttack();
								cout << "Здоровье врага: " << enemy_goblin.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_goblin.EnemyGetDamage(attack) << endl;
								if (enemy_goblin.EnemyHealth() <= 0)
								{
									hero.AntiGrimDetermination();
									grim_determination_flag = false;
									cout << "=========================Гоблин повержен!=========================" << endl;
									break;
								}
							}
							else
							{
								cout << "Промах!" << endl;
							}
						}
						else if (ability == 2)
						{
							if (hero.HeroHitChance() > enemy_goblin.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.FateDice();
								cout << "Здоровье врага: " << enemy_goblin.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_goblin.EnemyGetDamage(attack) << endl;
								if (enemy_goblin.EnemyHealth() <= 0)
								{
									if (grim_determination_flag == true)
									{
										hero.AntiGrimDetermination();
										grim_determination_flag = false;
									}
									cout << "=========================Гоблин повержен!=========================" << endl;
									break;
								}
							}
						}
						else if (ability == 3)
						{
							if ((hero.GetHeroCharisma() + hero.ForTheEmperor()) >= (rand() % (10 - 0 + 1) + 0))
							{
								enemy_goblin.EnemyReduceDefence();
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() > enemy_goblin.EnemyHitChance())
						{
							cout << "Гоблин промахнулся!" << endl;
						}
						else
						{
							cout << "Гоблин попадает и наносит " << enemy_goblin.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_goblin.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
				else if (random_enemy == 2)
				{
					Orc enemy_orc = Orc();
					boolean grim_determination_flag = false;
					cout << "Вашим врагом будет орк" << endl;
					while (enemy_orc.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Мрачная решимость - 1), (Кости судьбы - 2), (За императора! - 3): ";
						cin >> ability;
						if (ability == 1)
						{
							grim_determination_flag = true;
							hero.GrimDetermination();
							if (hero.HeroHitChance() > enemy_orc.EnemyDefence())
							{
								attack = hero.HeroAttack();
								cout << "Здоровье врага: " << enemy_orc.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_orc.EnemyGetDamage(attack) << endl;
								if (enemy_orc.EnemyHealth() <= 0)
								{
									hero.AntiGrimDetermination();
									grim_determination_flag = false;
									cout << "=========================Орк повержен!=========================" << endl;
									break;
								}
							}
							else
							{
								cout << "Промах!" << endl;
							}
						}
						else if (ability == 2)
						{
							if (hero.HeroHitChance() > enemy_orc.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.FateDice();
								cout << "Здоровье врага: " << enemy_orc.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << " урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_orc.EnemyGetDamage(attack) << endl;
								if (enemy_orc.EnemyHealth() <= 0)
								{
									if (grim_determination_flag == true)
									{
										hero.AntiGrimDetermination();
										grim_determination_flag = false;
									}
									cout << "=========================Орк повержен!=========================" << endl;
									break;
								}
							}
						}
						else if (ability == 3)
						{
							if ((hero.GetHeroCharisma() + hero.ForTheEmperor()) >= (rand() % (10 - 0 + 1) + 0))
							{
								enemy_orc.EnemyReduceDefence();
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() > enemy_orc.EnemyHitChance())
						{
							cout << "Орк промахнулся!" << endl;
						}
						else
						{
							cout << "Орк попадает и наносит " << enemy_orc.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_orc.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
				else if (random_enemy == 3)
				{
					Bandit enemy_bandit = Bandit();
					boolean grim_determination_flag = false;
					cout << "Вашим врагом будет бандит" << endl;
					while (enemy_bandit.EnemyHealth() > 0)
					{
						int ability = 0;
						int attack = 0;
						cout << "Какую способность вы хотите использовать ? (Мрачная решимость - 1), (Кости судьбы - 2), (За императора! - 3): ";
						cin >> ability;
						if (ability == 1)
						{
							grim_determination_flag = true;
							hero.GrimDetermination();
							if (hero.HeroHitChance() > enemy_bandit.EnemyDefence())
							{
								attack = hero.HeroAttack();
								cout << "Здоровье врага: " << enemy_bandit.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << "урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_bandit.EnemyGetDamage(attack) << endl;
								if (enemy_bandit.EnemyHealth() <= 0)
								{
									hero.AntiGrimDetermination();
									grim_determination_flag = false;
									cout << "=========================Бандит повержен!=========================" << endl;
									break;
								}
							}
							else
							{
								cout << "Промах!" << endl;
							}
						}
						else if (ability == 2)
						{
							if (hero.HeroHitChance() > enemy_bandit.EnemyDefence())
							{
								attack = hero.HeroAttack() + hero.FateDice();
								cout << "Здоровье врага: " << enemy_bandit.EnemyHealth() << endl;
								cout << "Вы нанесли " << attack << "урона" << endl;
								cout << "Оставшьеся здоровье: " << enemy_bandit.EnemyGetDamage(attack) << endl;
								if (enemy_bandit.EnemyHealth() <= 0)
								{
									if (grim_determination_flag == true)
									{
										hero.AntiGrimDetermination();
										grim_determination_flag = false;
									}
									cout << "=========================Бандит повержен!=========================" << endl;
									break;
								}
							}
						}
						else if (ability == 3)
						{
							if ((hero.GetHeroCharisma() + hero.ForTheEmperor()) >= (rand() % (10 - 0 + 1) + 0))
							{
								enemy_bandit.EnemyReduceDefence();
							}
						}
						cout << "Настала очередь врага атаковать" << endl;
						if (hero.HeroDamageResistance() > enemy_bandit.EnemyHitChance())
						{
							cout << "Бандит промахнулся!" << endl;
						}
						else
						{
							cout << "Бандит попадает и наносит " << enemy_bandit.EnemyAttack() << " урона" << endl;
							cout << "Ваше здоровье: " << hero.HeroDamage(enemy_bandit.EnemyAttack()) << endl;
							if (hero.HeroGetHealth() < 0)
							{
								cout << "!!!!!!!!!!!!!!!!!!!!!!Герой погиб!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
								game_over = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		default:
			cout << "Вы ввели неверные данные. Повторите попытку." << endl;
		};

	}
}