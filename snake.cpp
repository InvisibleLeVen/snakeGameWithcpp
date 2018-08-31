#pragma comment(lib,"graphics17.lib")
#include <vector>
#include <graphics.h> 
struct location
{
	float x, y;
};
enum direction{up,down,right,left};
class snack
{
	int length;
	float speed;
	direction currentDirection;
	color_t color;

public:
	snack();
	void move();
	void paint();
	void turn(direction dir);
	void snack::eat();
	~snack();
	location head;
	std::vector<location> body;
	void snack::Getfood();
};
class food
{
public:
	food();
	~food();
	void CreateFood();
	void food::Paint();
	void food::Remake();
	location foodLocation;
private:
	color_t foodcolor;
};

food::food()
{
	foodcolor = EGERGB(255, 0, 0);
	CreateFood();
}

food::~food()
{
}

void food::Paint()
{
	setcolor(this->foodcolor);
	setfillcolor(this->foodcolor);

	fillellipse(foodLocation.x, foodLocation.y, 6, 6);
}

void food::CreateFood()
{
	foodLocation.x = random(1000);
	foodLocation.y = random(700);
}
void food::Remake()
{
	foodLocation.x = random(1000);
	foodLocation.y = random(700);
}
snack::snack()
{
	location start;
	start.x = 10, start.y = 10;
	speed = 1;
	body.push_back(start);
	head = start;
	currentDirection = right;
	color = EGERGB(255, 144, 144);
}

void snack::Getfood()
{
	location l;
	std::vector<location>::iterator theiterator = this->body.begin();
	switch (this->currentDirection)
	{
	case up:
		l.y = this->body[0].y+10;
		l.x = this->body[0].x;
		body.insert(theiterator, l);
		break;
	case down:
		l.y = this->body[0].y-10;
		l.x = this->body[0].x;
		body.insert(theiterator, l);
		break;
	case left:
		l.y = this->body[0].y;
		l.x = this->body[0].x-10;
		body.insert(theiterator, l);
		break;
	case right:
		l.y = this->body[0].y;
		l.x = this->body[0].x+10;
		body.insert(theiterator, l);
		break;
	default:
		break;
	}
}

void snack::move()
{
	std::vector<location>::iterator begin = this->body.begin();;
	location l;
	switch (this->currentDirection)
	{
	case up:
	{
		l.y = this->body[0].y - 5;
		l.x = this->body[0].x;
		body.insert(begin, l);
		break;
	}

	case down:
	{
		l.y = this->body[0].y + 5;
		l.x = this->body[0].x;
		body.insert(begin, l);
		break;
	}
	case right:
	{
		l.y = this->body[0].y;
		l.x = this->body[0].x + 5;
		body.insert(begin, l);
		break;
	}
	case left:
	{
		l.y = this->body[0].y;
		l.x = this->body[0].x - 5;
		body.insert(begin, l);
		break;
	}
	default:
		break;
	}
	//std::vector<location>::iterator end = this->body.end();
	body.pop_back();
}
void snack::turn(direction dir)
{
	switch (dir)
	{
	case up: 
		if(this->currentDirection == down)
			 break;
		this->currentDirection = up; break;
	case down: 
		if (this->currentDirection == up)
			break;
		this->currentDirection = down; break;
	case right:
		if (this->currentDirection == left)
			break;
		this->currentDirection = right; break;
	case left:
		if (this->currentDirection == right)
			break;
		this->currentDirection = left; break;
	default:
		break;
	}
}
void snack::paint()
{
	setcolor(this->color);
	setfillcolor(this->color);
	for (int i = 0; i < body.size(); i++)
	{
		fillellipse(body[i].x, body[i].y,6,6);
	}
}

snack::~snack()
{
}
bool ifGetFood(snack s, food f)
{
	/*f.foodLocation.x = 16;
	f.foodLocation.y = 16;*/
	//float a;
	return sqrt((s.body[0].x - f.foodLocation.x)*(s.body[0].x - f.foodLocation.x) + (s.body[0].y - f.foodLocation.y)*(s.body[0].y - f.foodLocation.y)) < 12;
}
bool ifdie(snack s)
{
	return s.body[0].x > 1000 || s.body[0].x < 0 || s.body[0].y > 700 || s.body[0].y < 0;
}
int main()
{
	initgraph(1000, 700);
	snack s = snack();
	food f = food();
	int ch;
	for (; is_run(); delay_fps(60))
	{
		cleardevice();
		setcolor(EGERGB(220, 220, 220));
		setfillcolor(EGERGB(220, 220, 220));
		setlinewidth(20);
		line(0, 0, 1000, 0);
		line(0, 700, 1000, 700);
		line(0, 0, 0, 700);
		line(1000, 0, 1000, 700);
		//setlinewidth(5);

		if (kbhit())
		{
			switch (ch = getch())
			{
				case 0x77:  s.turn(up); break;
				case 0x73:  s.turn(down); break;
				case 0x61:  s.turn(left); break;
				case 0x64:  s.turn(right); break;
				default:
					break;
			}
		}
		if (ifdie(s))
		{
			MessageBox(NULL, "你输了!!!!", "游戏结束", MB_OK);
			break;
		}
		if (ifGetFood(s,f))
		{
			f.Remake();
			s.Getfood();
		}
		
		f.Paint();
		s.move();
		s.paint();
	}
	closegraph();
}
