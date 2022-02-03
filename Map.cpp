#include "Map.h"

// ����������� ��� ���������� ������ Timer
Map::Timer::Timer() {
	this->presentValue = this->initValue = 0;
	this->activity = false;
}

// ����������� � ����� ���������� ������ Timer
Map::Timer::Timer(int value) {
	this->presentValue = this->initValue = value;
	this->activity = false;
}

// ���������� ��������� ������������ ��� �������� ������ Timer
Map::Timer& Map::Timer::operator=(const Map::Timer& timer) {
	this->initValue = timer.initValue;
	this->presentValue = timer.presentValue;
	this->clock = timer.clock;
	return *this;
}

// ������ �������
void Map::Timer::startTimer(void) {
	if (this->activity == false) {
		this->clock.restart();
		this->activity = true;
	}
	if (this->presentValue > 0) {
		this->presentValue = this->initValue - (int)this->clock.getElapsedTime().asSeconds();
	}
	else {
		(*this).stopTimer();
	}

}

// ��������� �������
void Map::Timer::stopTimer(void) {
	this->activity = false;
	this->initValue = this->presentValue;
}

bool Map::Timer::getActivity(void) {
	return this->activity;
}

// �������� ������� �������� �������
int Map::Timer::getPresentValue(void) {
	return this->presentValue;
}

// ������ ��������� �������� �������
void Map::Timer::setInitValue(int value) {
	this->presentValue = this->initValue = value;
}

// ����������� � ����� ���������� ������ Map
Map::Map(String fileMap) {
	Timer timerGame(120);
	this->timerGame = timerGame;
	this->fileMap = fileMap;
	this->image.loadFromFile("images/" + this->fileMap);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(texture);
	this->bonusDoubleDamage = false;
	this->bonusShield = false;
	this->bonusUpTime = false;
	(*this).randomMapGenerate();
}

// ���������� �����
void Map::draw(RenderWindow& window) {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			if (this->tileMap[i][j] == ' ') {
				this->sprite.setTextureRect(IntRect(0, 0, 60, 60));
			}
			else if (this->tileMap[i][j] == 'w') {
				this->sprite.setTextureRect(IntRect(60, 0, 60, 60));
			}
			else if (this->tileMap[i][j] == 's') {
				this->sprite.setTextureRect(IntRect(120, 0, 60, 60));
			}
			else if (this->tileMap[i][j] == 'd') {
				this->sprite.setTextureRect(IntRect(180, 0, 60, 60));
			}
			else if (this->tileMap[i][j] == 't') {
				this->sprite.setTextureRect(IntRect(240, 0, 60, 60));
			}
			this->sprite.setPosition(j * 60, i * 60);
			window.draw(this->sprite);
		}
	}
	(*this).drawTimer(window);
}

// ���������� ������ �� �����
void Map::drawTimer(RenderWindow& window) {
	this->timerGame.startTimer();
	// ������� ����� ���������� ������
	Font font;
	font.loadFromFile("other/Arial.ttf");
	Text text("", font, 40);
	text.setOutlineColor(Color::Black);
	text.setFillColor(Color::Black);
	text.setStyle(Text::Bold);
	// ����� ������� ����
	text.setPosition(60,this->width-5);
	std::ostringstream textTimerGame;
	textTimerGame << this->timerGame.getPresentValue();
	text.setString("Game:" + textTimerGame.str());
	window.draw(text);
	// ����� ������� ������
	text.setPosition(this->height * 57, this->width-5);
	std::ostringstream textTimerBonus;
	textTimerBonus << this->timerBonus.getPresentValue();
	text.setString("Bonus:" + textTimerBonus.str());
	window.draw(text);
}

// ��������� ��������� �������� �� �����
void Map::randomMapGenerate(void) {

	int randomElementX = 0;
	int randomElementY = 0;
	srand(time(0));

	// ���������� �� ����� ���� ������� "������� ����"
	int counter = 2;
	while (counter > 0) {
		randomElementX = 1 + rand() % (this->width - 1);
		randomElementY = 1 + rand() % (this->height- 1);

		if (tileMap[randomElementY][randomElementX] == ' ') {
			tileMap[randomElementY][randomElementX] = 'd';
			counter--;
		}
	}

	// ���������� �� ����� ���� ������� "���"
	counter = 2;
	while (counter > 0) {
		randomElementX = 1 + rand() % (this->width - 1);
		randomElementY = 1 + rand() % (this->height - 1);

		if (tileMap[randomElementY][randomElementX] == ' ') {
			tileMap[randomElementY][randomElementX] = 's';
			counter--;
		}
	}

	// ���������� �� ����� ������ ������ "��������� ������� �� 20 ������"
	counter = 1;
	while (counter > 0) {
		randomElementX = 1 + rand() % (this->width - 1);
		randomElementY = 1 + rand() % (this->height - 1);

		if (tileMap[randomElementY][randomElementX] == ' ') {
			tileMap[randomElementY][randomElementX] = 't';
			counter--;
		}
	}
}

// �������� ������ �����
int Map::getHeight(void) {
	return this->height;
}

// �������� ������ �����
int Map::getWidth(void) {
	return this->width;
}

// ������ ���������� ������ � �����
void Map::printAmountOfHealthHero(int amountOfHealth, RenderWindow& window) {
	Font font;
	font.loadFromFile("other/Arial.ttf");
	Text text("", font, 40);
	text.setOutlineColor(Color::Black);
	text.setFillColor(Color::Black);
	text.setStyle(Text::Bold);
	text.setPosition(60, this->width * 39 - 5);
	std::ostringstream textAmountOfHealth;
	if (amountOfHealth > 0) {
		textAmountOfHealth << amountOfHealth;
	}
	else {
		textAmountOfHealth << 0;
	}
	text.setString("Player:" + textAmountOfHealth.str());
	window.draw(text);
}

// ������ ���������� ������ � �����
void Map::printAmountOfHealthEnemy(int amountOfHealth, RenderWindow& window) {
	Font font;
	font.loadFromFile("other/Arial.ttf");
	Text text("", font, 40);
	text.setOutlineColor(Color::Black);
	text.setFillColor(Color::Black);
	text.setStyle(Text::Bold);
	text.setPosition(this->height * 57, this->width * 39 - 5);
	std::ostringstream textAmountOfHealth;
	if (amountOfHealth > 0) {
		textAmountOfHealth << amountOfHealth;
	}
	else {
		textAmountOfHealth << 0;
	}
	text.setString("Enemy:" + textAmountOfHealth.str());
	window.draw(text);
}

// �������� ������� �������� �������
int Map::getPresentValueTimer(void) {
	return this->timerGame.getPresentValue();
}