#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Boss.h"
#include "PlayerLife.h"
#include "Map.h"
#include "Timer.h"

#include "List.h"
#include <random>


PlayerLife::PlayerLife() : Entity(EntityType::PLAYERLIFE)
{
	name.Create("playerlife");
}

PlayerLife::~PlayerLife() {}

bool PlayerLife::Awake() {

	return true;
}

bool PlayerLife::Start() {

	/*newmap = true;
	app->SaveRequest();
	app->LoadRequest();
	newmap = false;*/
	reLoadXML();
	lifebar_head_tail_texture = app->tex->Load(lifebar_head_tail_texture_Path);

	lifebar_mid_texture = app->tex->Load(lifebar_mid_texture_Path);

	lifebar_icon_texture = app->tex->Load(lifebar_icon_texture_Path);

	currentAnimation1 = &Head_idle;


	currentAnimation3 = &Tail_idle;



	lifeMark = life;

	lifebar = life - 2;

	for (int i = 0; i < lifebar; i++)
	{
		currentAnimation2.Add(&Middle_idle[i]);
		rect_2.Add(currentAnimation2[i]->GetCurrentFrame());
	}
	currentAnimation4 = &Glass_idle;
	return true;
}

bool PlayerLife::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

		if (life != 0) {
			life--;
			playerTakeDmg_Animation = true;
			playerTakeDmg = true;
		}

		if (life == 0) {
			app->scene->GetPlayer()->isDead = true;
		}
	}


	if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {

		if (life != lifeMark) {
			life++;
			playerTakeHeal = true;
		}
	}

	updateHeadAnimations();
	updateMiddleAnimations();
	updateTailAnimation();
	lifebarstate();



	rect_4 = currentAnimation4->GetCurrentFrame();
	app->render->DrawTexture(lifebar_icon_texture, 0, -20, 1.5, SDL_FLIP_NONE, &rect_4, 0, 0);
	currentAnimation4->Update();




	return true;
}

bool PlayerLife::CleanUp()
{

	if (lifebar_head_tail_texture) {
		SDL_DestroyTexture(lifebar_head_tail_texture);
		lifebar_head_tail_texture = nullptr;
	}

	if (lifebar_mid_texture) {
		SDL_DestroyTexture(lifebar_mid_texture);
		lifebar_mid_texture = nullptr;
	}

	if (lifebar_icon_texture) {
		SDL_DestroyTexture(lifebar_icon_texture);
		lifebar_icon_texture = nullptr;
	}

	return true;
}


void PlayerLife::resetAnimation(Animation& ani)
{
	ani.Reset();
}

void PlayerLife::playerGetHit()
{
	if (life != 0) {
		life--;
		playerTakeDmg_Animation = true;
		playerTakeDmg = true;
	}

	if (life == 0) {
		app->scene->GetPlayer()->isDead = true;
	}


	if (playerTakeBossDmg == false) {
		playerTakeBossDmg = true;
	}


}

void PlayerLife::playerGetHeal()
{
	if (life != lifeMark) {
		life++;
		playerTakeHeal = true;
	}
}

void PlayerLife::updateHeadAnimations()
{
	lifePos_X = posXinicio;
	rect_1 = currentAnimation1->GetCurrentFrame();
	app->render->DrawTexture(lifebar_head_tail_texture, lifePos_X, lifePos_Y, 2, SDL_FLIP_NONE, &rect_1, 0, 0);
	currentAnimation1->Update();

	if (currentAnimation1->HasFinished()) {
		playerTakeDmg = false;
		playerTakeHeal = false;
		resetAnimation(Head_takehit);
		resetAnimation(Head_treatment);
	}

}

void PlayerLife::updateMiddleAnimations()
{
	for (int i = 0; i < lifebar; i++)
	{

		if (app->scene->GetPlayer()->isDead) {
			currentAnimation2[i] = &Middle_die[i];
		}
		else {
			if (playerTakeDmg == false && playerTakeHeal == false) {
				if (life > i + 1) {
					currentAnimation2[i] = &Middle_idle[i];
				}
				else {
					currentAnimation2[i] = &Middle_idle_nb[i];
				}
			}
			else if (playerTakeDmg) {
				if (life != lifeMark) {

					if (life == i + 1) {
						currentAnimation2[i] = &Middle_takehit_ab[i];
					}
					else if (life > i + 1) {
						currentAnimation2[i] = &Middle_takehit_wb[i];
					}
					else {
						currentAnimation2[i] = &Middle_takehit_nb[i];
					}
				}
			}
			else if (playerTakeHeal) {
				if (life != lifeMark) {
					if (life == i + 2) {
						currentAnimation2[i] = &Middle_treatment_ab[i];
					}
					else if (life > i + 1) {
						currentAnimation2[i] = &Middle_treatment_wb[i];
					}
					else {
						currentAnimation2[i] = &Middle_treatment_nb[i];
					}
				}
				else {
					currentAnimation2[i] = &Middle_treatment_wb[i];
				}
			}
		}
		lifePos_X = posXinicio + 36 + i * 30;
		rect_2[i] = currentAnimation2[i]->GetCurrentFrame();
		app->render->DrawTexture(lifebar_mid_texture, lifePos_X, lifePos_Y, 2, SDL_FLIP_NONE, &rect_2[i], 0, 0);
		currentAnimation2[i]->Update();
		if (currentAnimation2[i]->HasFinished()) {
			Middle_takehit_ab[i].Reset();
			Middle_takehit_wb[i].Reset();
			Middle_takehit_nb[i].Reset();
			Middle_treatment_ab[i].Reset();
			Middle_treatment_wb[i].Reset();
			Middle_treatment_nb[i].Reset();
		}

	}
}

void PlayerLife::updateTailAnimation()
{

	rect_3 = currentAnimation3->GetCurrentFrame();
	app->render->DrawTexture(lifebar_head_tail_texture, lifePos_X + 30, lifePos_Y, 2, SDL_FLIP_NONE, &rect_3, 0, 0);
	currentAnimation3->Update();

	if (currentAnimation3->HasFinished()) {
		resetAnimation(Tail_takehit_nb);
		resetAnimation(Tail_takehit_ab);
		resetAnimation(Tail_treatment_nb);
		resetAnimation(Tail_treatment_ab);

	}
}

void PlayerLife::lifebarstate()
{
	if (app->scene->GetPlayer()->isDead) {
		playerTakeDmg = false;
		lifebarState = EntityLifeBarState::DIE;
		getStateAnimation(lifebarState);
	}
	else if (playerTakeHeal) {
		lifebarState = EntityLifeBarState::TREATMENT;
		getStateAnimation(lifebarState);
	}
	else if (playerTakeDmg) {
		lifebarState = EntityLifeBarState::TAKEHIT;
		getStateAnimation(lifebarState);
	}
	else {
		lifebarState = EntityLifeBarState::IDLE;
		getStateAnimation(lifebarState);
	}
}


void PlayerLife::getStateAnimation(EntityLifeBarState state)
{
	switch (state)
	{
	case EntityLifeBarState::IDLE:

		currentAnimation1 = &Head_idle;
		if (life != lifeMark) {
			currentAnimation3 = &Tail_idle_nb;
		}
		else {
			currentAnimation3 = &Tail_idle;
		}
		currentAnimation4 = &Glass_idle;
		Glass_broke.Reset();

		break;
	case EntityLifeBarState::DIE:
		currentAnimation1 = &Head_die;
		currentAnimation3 = &Tail_die;
		currentAnimation4 = &Glass_broke;
		break;
	case EntityLifeBarState::TAKEHIT:
		if (life != 0) {
			currentAnimation1 = &Head_takehit;
		}

		if (life == lifebar + 1) {
			currentAnimation3 = &Tail_takehit_ab;
		}
		else {
			currentAnimation3 = &Tail_takehit_nb;
		}
		break;
	case EntityLifeBarState::TREATMENT:

		currentAnimation1 = &Head_treatment;

		if (life == lifeMark) {
			currentAnimation3 = &Tail_treatment_ab;
		}
		else {
			currentAnimation3 = &Tail_treatment_nb;
		}

		break;
	case EntityLifeBarState::UNKNOWN:
		break;
	default:
		break;
	}

}


void PlayerLife::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void PlayerLife::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;


	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void PlayerLife::reLoadXML()
{
	pugi::xml_document configFile;



	lifebar_head_tail_texture_Path = parameters.child("lifebar_head_tail").attribute("texturepath").as_string();
	TSprite = parameters.child("lifebar_head_tail").attribute("Tsprite").as_int();
	SpriteX = parameters.child("lifebar_head_tail").attribute("x").as_int();
	SpriteY = parameters.child("lifebar_head_tail").attribute("y").as_int();
	PhotoWeight = parameters.child("lifebar_head_tail").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	//Head
	Head_idle.LoadAnim("PlayerLife_head", "Head_idle", spritePositions);
	Head_treatment.LoadAnim("PlayerLife_head", "Head_treatment", spritePositions);
	Head_takehit.LoadAnim("PlayerLife_head", "Head_takehit", spritePositions);
	Head_die.LoadAnim("PlayerLife_head", "Head_die", spritePositions);
	//Tail
	Tail_treatment_nb.LoadAnim("PlayerLife_head", "Tail_treatment_nb", spritePositions);
	Tail_treatment_ab.LoadAnim("PlayerLife_head", "Tail_treatment_ab", spritePositions);
	Tail_takehit_nb.LoadAnim("PlayerLife_head", "Tail_takehit_nb", spritePositions);
	Tail_takehit_ab.LoadAnim("PlayerLife_head", "Tail_takehit_ab", spritePositions);
	Tail_die.LoadAnim("PlayerLife_head", "Tail_die", spritePositions);
	Tail_idle.LoadAnim("PlayerLife_head", "Tail_idle", spritePositions);
	Tail_idle_nb.LoadAnim("PlayerLife_head", "Tail_idle_nb", spritePositions);



	lifebar_mid_texture_Path = parameters.child("lifebar_mid").attribute("texturepath").as_string();
	TSprite = parameters.child("lifebar_mid").attribute("Tsprite").as_int();
	SpriteX = parameters.child("lifebar_mid").attribute("x").as_int();
	SpriteY = parameters.child("lifebar_mid").attribute("y").as_int();
	PhotoWeight = parameters.child("lifebar_mid").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);




	for (int i = 0; i < lifebar; i++)
	{
		Middle_idle.Add(inicializaAnimation);
		Middle_idle_nb.Add(inicializaAnimation);
		Middle_treatment_wb.Add(inicializaAnimation);
		Middle_treatment_nb.Add(inicializaAnimation);
		Middle_treatment_ab.Add(inicializaAnimation);
		Middle_takehit_wb.Add(inicializaAnimation);
		Middle_takehit_nb.Add(inicializaAnimation);
		Middle_takehit_ab.Add(inicializaAnimation);
		Middle_die.Add(inicializaAnimation);

		Middle_idle[i].LoadAnim("PlayerLife_mid", "Middle_idle", spritePositions);
		Middle_idle_nb[i].LoadAnim("PlayerLife_mid", "Middle_idle_nb", spritePositions);
		Middle_treatment_wb[i].LoadAnim("PlayerLife_mid", "Middle_treatment_wb", spritePositions);
		Middle_treatment_nb[i].LoadAnim("PlayerLife_mid", "Middle_treatment_nb", spritePositions);
		Middle_treatment_ab[i].LoadAnim("PlayerLife_mid", "Middle_treatment_ab", spritePositions);
		Middle_takehit_wb[i].LoadAnim("PlayerLife_mid", "Middle_takehit_wb", spritePositions);
		Middle_takehit_nb[i].LoadAnim("PlayerLife_mid", "Middle_takehit_nb", spritePositions);
		Middle_takehit_ab[i].LoadAnim("PlayerLife_mid", "Middle_takehit_ab", spritePositions);
		Middle_die[i].LoadAnim("PlayerLife_mid", "Middle_die", spritePositions);

	}

	lifebar_icon_texture_Path = parameters.child("lifebar_glass").attribute("texturepath").as_string();
	TSprite = parameters.child("lifebar_glass").attribute("Tsprite").as_int();
	SpriteX = parameters.child("lifebar_glass").attribute("x").as_int();
	SpriteY = parameters.child("lifebar_glass").attribute("y").as_int();
	PhotoWeight = parameters.child("lifebar_glass").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	Glass_idle.LoadAnim("PlayerLife_mid", "lifebar_glass_idle", spritePositions);
	Glass_broke.LoadAnim("PlayerLife_mid", "lifebar_glass_broke", spritePositions);


}
