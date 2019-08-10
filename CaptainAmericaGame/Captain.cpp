#include "Captain.h"

vector<Animation *> Captain::animations = vector<Animation *>();
Captain *Captain::__instance = NULL;

Captain::Captain()
{
	LoadResources();

	state = CaptainState::GetInstance(this);

	shield = new Shield();

	this->x = 250;
	this->y = 200;
	this->width = CAPTAIN_SPRITE_WIDTH;
	this->height = CAPTAIN_SPRITE_HEIGHT;

	collider.x = x - 10;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = CAPTAIN_SPRITE_WIDTH - 10;
	collider.height = CAPTAIN_SPRITE_HEIGHT;
}

Captain *Captain::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Captain();
	}
	return __instance;
}

void Captain::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// CAPTAIN_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_STADING_UP
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_WALK
	anim = new Animation(100);
	for (int i = 1; i < 5; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);

	}
	animations.push_back(anim);

	// CAPTAIN_ANI_JUMP
	anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);

	}
	animations.push_back(anim);

	// CAPTAIN_ANI_JUMP_ROLE
	anim = new Animation(50);
	for (int i = 8; i < 10; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH
	anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SWIM
	anim = new Animation(100);
	for (int i = 44; i < 46; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_THROW_SHIELD
	anim = new Animation(100);

	Sprite * sprite3 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[11], TEXTURE_TRANS_COLOR);
	sprite3->SetOffSetX(-4);
	anim->AddFrame(sprite3);

	Sprite * sprite4 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[12], TEXTURE_TRANS_COLOR);

	sprite4->SetOffSetX(12);
	anim->AddFrame(sprite4);

	animations.push_back(anim);

	// CAPTAIN_ANI_PUNCH
	anim = new Animation(100);

	Sprite * sprite1 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[13], TEXTURE_TRANS_COLOR);
	sprite1->SetOffSetX(12);
	anim->AddFrame(sprite1);

	Sprite * sprite2 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[14], TEXTURE_TRANS_COLOR);
	sprite2->SetOffSetX(3);
	anim->AddFrame(sprite2);

	animations.push_back(anim);

	// CAPTAIN_ANI_KICK
	anim = new Animation(500);
	for (int i = 10; i < 11; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);

		sprite->SetOffSetX(12);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH_PUNCH
	anim = new Animation(100);

	Sprite * sprite5 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[15], TEXTURE_TRANS_COLOR);
	sprite5->SetOffSetX(9);
	anim->AddFrame(sprite5);

	Sprite * sprite6 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[16], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite6);

	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH_SHIELD
	anim = new Animation(300);
	for (int i = 19; i < 20; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DASH
	anim = new Animation(300);
	for (int i = 18; i < 19; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_THROW_SHIELD_2
	anim = new Animation(300);
	for (int i = 11; i < 13; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_BLEEING
	anim = new Animation(100);
	for (int i = 33; i < 34; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DIEING
	anim = new Animation(300);
	for (int i = 34; i < 36; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DIVING
	anim = new Animation(200);
	for (int i = 41; i < 44; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SWING
	anim = new Animation(200);

	Sprite * sprite9 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[27], TEXTURE_TRANS_COLOR);
	sprite9->SetOffSetX(4);
	anim->AddFrame(sprite9);

	Sprite * sprite10 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[28], TEXTURE_TRANS_COLOR);
	sprite10->SetOffSetX(5);
	anim->AddFrame(sprite10);

	Sprite * sprite11 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[29], TEXTURE_TRANS_COLOR);
	sprite11->SetOffSetX(1);
	anim->AddFrame(sprite11);

	animations.push_back(anim);

	// CAPTAIN_ANI_BLEEING_2
	anim = new Animation(10);

	Sprite * sprite7 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[30], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite7);

	Sprite * sprite8 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite8);
	animations.push_back(anim);
}

void Captain::Reset()
{
	this->SetPositionX(200);
	this->SetPositionY(200);
	Viewport::GetInstance()->Reset();
}

void Captain::Update(DWORD dt)
{
	timeCount += dt;
	// Xử lý chuyển màn
	if (this->GetSpeedX() > 0 && this->GetPositionX() > TileMap2::GetInstance()->currentMap->size * 16 - 50)
	{
		if (Game::GetInstance()->GetStage() < 4)
		{
			Game::GetInstance()->SetStage(Game::GetInstance()->GetStage() + 1);
			if (STAGE_BOSS_1 == Game::GetInstance()->GetStage())
			{
				Grid2::GetInstance()->DisableAllObject();
				Grid2::GetInstance()->spawnboss = true;
				this->SetPositionX(50);
				this->SetPositionY(100);
				Viewport::GetInstance()->Reset();
				TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_1);
				Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
			}
			if (STAGE_2 == Game::GetInstance()->GetStage())
			{
				this->SetPositionX(280);
				this->SetPositionY(900);
				Viewport::GetInstance()->Reset();
				TileMap2::GetInstance()->SetCurrentMap(STAGE_2);
				Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
			}
			if (STAGE_BOSS_2 == Game::GetInstance()->GetStage())
			{
				this->SetPositionX(100);
				this->SetPositionY(100);
				Viewport::GetInstance()->Reset();
				TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_2);
				Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
			}
		}
		else this->SetSpeedX(0);
	}

	//Chuyển màn nhanh bằng phím
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F1))
	{
		Grid2::GetInstance()->DisableAllObject();
		Game::GetInstance()->SetStage(STAGE_1);
		this->SetPositionX(50);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_1);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F2))
	{
		Grid2::GetInstance()->DisableAllObject();
		Game::GetInstance()->SetStage(STAGE_BOSS_1);
		Grid2::GetInstance()->spawnboss = true;
		Grid2::GetInstance()->DisableAllObject();
		this->SetPositionX(50);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_1);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F3))
	{
		Grid2::GetInstance()->DisableAllObject();
		Game::GetInstance()->SetStage(STAGE_2);
		this->SetPositionX(280);
		this->SetPositionY(900);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_2);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F4))
	{
		Grid2::GetInstance()->DisableAllObject();
		Game::GetInstance()->SetStage(STAGE_BOSS_2);
		this->SetPositionX(100);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_2);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
		Grid2::GetInstance()->isDisableBoss2 = false;
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F5))
	{
		trueImortal = !trueImortal;
	}

	//Colision với state để riêng ra
	vector<ColliedEvent*> coEvents;
	vector<ColliedEvent*> coEventsResult;

#pragma region	Collide with map
	vector<Tile2 *> tiles = Grid2::GetInstance()->GetNearbyTiles(this->GetRect());

	coEvents.clear();
	this->SetDt(dt);
	this->UpdateObjectCollider();
	this->collider.x += 5;
	this->MapCollisions(tiles, coEvents);

	if (coEvents.size() == 0)
	{
		float moveX = trunc(this->GetSpeedX()* dt);
		float moveY = trunc(this->GetSpeedY()* dt);
		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		Collision::GetInstance()->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				this->SetIsGrounded(true);
			}
		}

		if (coEventsResult[0]->collisionID == 2)
		{
			if (ny == 1)
			{
				this->SetIsGrounded(false);
				this->SetIsSwimming(true);
				this->SetPositionX(this->GetPositionX() - 1);
			}
		}

		if (coEventsResult[0]->collisionID == 3)
		{
			if (ny == 1)
			{
				this->SetIsSwing(true);
			}
		}

		if (coEventsResult[0]->collisionID == 4)
		{
			if (ny == 1)
			{
				this->SetIsGrounded(true);
				this->SetIsBleeding(true);
			}
		}

		if (coEventsResult[0]->collisionID == 5)
		{
			if (nx == 1 || nx == -1)
			{
				this->SetIsGrounded(true); //xét tạm
			}
		}
	}
	for (int i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
	shield->UpdateObjectCollider();
	shield->Update(dt);
	state->Colision();
	state->Update(dt);


}
void Captain::UpdateCollision(DWORD dt)
{
	if (trueImortal)
		return;

	if (bImortal)
	{
		if (timeCount > 700)
		{
			timeCount = 0;
			bImortal = false;
		}
		return;
	}

	//Collide with enemy
	vector<OnUpdateObject> listUpdateObject = Grid2::GetInstance()->GetListUpdateObject();

	for (int i = 0; i < listUpdateObject.size(); i++)
	{
		if (listUpdateObject.at(i).disable || listUpdateObject.at(i).object->disable)
			continue;

		float normalX = 0;
		float normalY = 0;
		float time = Collision::GetInstance()->SweptAABB(this->GetCollider(), listUpdateObject.at(i).object->GetCollider(), normalX, normalY);
		bool isCollide = Collision::GetInstance()->AABB(this->GetCollider(), listUpdateObject.at(i).object->GetCollider());
		bool isCollideShield = Collision::GetInstance()->AABB(shield->GetCollider(), listUpdateObject.at(i).object->GetCollider());
		//if (time < 0 || time >= 1)

		if (isCollideShield) {
			switch (listUpdateObject.at(i).tile->SpawnObjectID)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 7:
			case 15:
			case 16:
			case 11:
			case 12:
			case 13:
			case 14:
				listUpdateObject.at(i).object->OnCollision();
				break;
			case 17:
				//chưa biết xử lý sao
				listUpdateObject.at(i).object->OnCollision();
				break;
			case 6:
			case 18:
				if (shield->IsFlying())
					listUpdateObject.at(i).object->OnCollision();
				break;
			}
		}


		if (!isCollide)
			continue;

		switch (listUpdateObject.at(i).tile->SpawnObjectID)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			((CaptainState*)state)->timeCount = 0;
			this->SetIsBleeding(true);
			bImortal = true;
			return;
		}
	}


	//Collide with bullets
	vector<Bullet*> listBullet = SpawnProjectTile::GetInstance()->listBullet;
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (listBullet.at(i)->disable)
			continue;
		bool isCollideShield = Collision::GetInstance()->AABB(shield->GetCollider(), listBullet.at(i)->GetCollider());

		//Test
		if (isCollideShield)
		{
			if (listBullet.at(i)->GetBulletType() == BULLET_NORMAL)
			{
				listBullet.at(i)->SetSpeedX(0);
				listBullet.at(i)->SetSpeedY(BULLET_NORMAL_SPEED);
			}
		}

		bool isCollide = Collision::GetInstance()->AABB(this->GetCollider(), listBullet.at(i)->GetCollider());

		if (isCollide)
		{
			switch (listBullet.at(i)->GetBulletType())
			{
			case BulletType::BULLET_BOSS2:
			case BulletType::BARREL:
			case BulletType::GIGIROCKET:
			case BulletType::ROCKET:
				listBullet.at(i)->disableTimeCount = 0;
				listBullet.at(i)->OnCollision();
				break;
			case BulletType::BULLET_NORMAL:
			case BulletType::BULLET_NORMAL_BOSS1:
			case BulletType::BULLET_SPECIAL_BOSS1:
			case BulletType::BULLET_TANK:
				listBullet.at(i)->Disable();
				break;
			}

			((CaptainState*)state)->timeCount = 0;
			this->SetIsBleeding(true);
			bImortal = true;
			return;
		}
	}


	//Collide with items
	vector<Item*> listItem = SpawnProjectTile::GetInstance()->listItem;
	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem.at(i)->disable)
			continue;
		bool isCollide = Collision::GetInstance()->AABB(this->GetCollider(), listItem.at(i)->GetCollider());

		if (isCollide)
		{
			listItem.at(i)->Disable();
		}
	}
}
void Captain::Render()
{
	state->Render();
	shield->Render();
}